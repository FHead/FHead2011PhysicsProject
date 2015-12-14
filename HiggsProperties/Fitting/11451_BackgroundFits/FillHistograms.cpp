#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH2D.h"

#include "PlotHelper2.h"

int main(int argc, char *argv[])
{
   srand(time(NULL));

   // Input parameters
   string SignalFileName = "Samples/hzzTree_id1125.root";
   string BackgroundFileName = "Samples/hzzTree_id103.root";   // for now...
   string DirectoryName = "zz4lTree";
   string TreeName = "probe_tree";

   // Output parameters
   string OutputFileBase = "Likelihoods";
   int FBins = 500;   // f is the background fraction that we want to measure
   double FMin = 0, FMax = 1;

   // Other parameters
   double SearchTolerance = 1e-5;
   int SearchStepCount = 10;
   int MaxTries = 1000;
   int SignalSize = 25, BackgroundSize = 5;

   if(argc > 1)
      SignalSize = atoi(argv[1]);
   if(argc > 2)
      BackgroundSize = atoi(argv[2]);

   cout << "Start job with " << SignalSize << " signal events and " << BackgroundSize << " background events" << endl;

   // Output files and histograms
   TFile OutputFile(Form("%s_%d_%d.root", OutputFileBase.c_str(), SignalSize, BackgroundSize), "RECREATE");

   TNtuple OutputTree("OutputTree", "OutputTree", "Signal:Background:Left:Middle:Right:Statistics:Mean:RMS");

   TH1D HBestFitPosition(Form("HBestFitPosition_%d_%d", SignalSize, BackgroundSize),
      "Best fit positions for fraction", 10000, 0, 1);

   PsFileHelper PsFile(Form("%s_%d_%d.ps", OutputFileBase.c_str(), SignalSize, BackgroundSize));
   PsFile.AddTextPage("Let's see if we can extract background");

   // Initialize stuff
   TFile SignalFile(SignalFileName.c_str());
   TFile BackgroundFile(BackgroundFileName.c_str());

   TDirectoryFile *Directory = (TDirectoryFile *)SignalFile.Get(DirectoryName.c_str());
   TTree *SignalTree = (TTree *)Directory->Get(TreeName.c_str());
   Directory = (TDirectoryFile *)BackgroundFile.Get(DirectoryName.c_str());
   TTree *BackgroundTree = (TTree *)Directory->Get(TreeName.c_str());

   SignalTree->SetBranchStatus("*", false);
   BackgroundTree->SetBranchStatus("*", false);

   SignalTree->SetBranchStatus("Likelihood_ExtSig1", true);
   SignalTree->SetBranchStatus("Likelihood_EffMEE", true);
   BackgroundTree->SetBranchStatus("Likelihood_ExtSig1", true);
   BackgroundTree->SetBranchStatus("Likelihood_EffMEE", true);
   BackgroundTree->SetBranchStatus("mass", true);

   double LS, LB;   // (L)ikelihood, (S)ignal, (B)ackground
   float Mass;
   SignalTree->SetBranchAddress("Likelihood_ExtSig1", &LS);
   SignalTree->SetBranchAddress("Likelihood_EffMEE", &LB);
   BackgroundTree->SetBranchAddress("Likelihood_ExtSig1", &LS);
   BackgroundTree->SetBranchAddress("Likelihood_EffMEE", &LB);
   BackgroundTree->SetBranchAddress("mass", &Mass);

   // Now, first let's do some loops and collect likelihoods
   vector<pair<double, double> > SignalLikelihood(SignalTree->GetEntries());
   vector<pair<double, double> > BackgroundLikelihood;

   int SignalEntryCount = SignalTree->GetEntries();
   for(int iEntry = 0; iEntry < SignalEntryCount; iEntry++)
   {
      SignalTree->GetEntry(iEntry);
      SignalLikelihood[iEntry].first = LS;
      SignalLikelihood[iEntry].second = LB / 4;
      // the factor 4 comes from different binnings in signal and background maps
   }
   random_shuffle(SignalLikelihood.begin(), SignalLikelihood.end());
   random_shuffle(SignalLikelihood.begin(), SignalLikelihood.end());
   random_shuffle(SignalLikelihood.begin(), SignalLikelihood.end());
   random_shuffle(SignalLikelihood.begin(), SignalLikelihood.end());
   random_shuffle(SignalLikelihood.begin(), SignalLikelihood.end());
   
   int BackgroundEntryCount = BackgroundTree->GetEntries();
   for(int iEntry = 0; iEntry < BackgroundEntryCount; iEntry++)
   {
      BackgroundTree->GetEntry(iEntry);

      if(Mass > 120 && Mass < 130)   // For now...
         BackgroundLikelihood.push_back(pair<double, double>(LS, LB / 4));
   }
   random_shuffle(BackgroundLikelihood.begin(), BackgroundLikelihood.end());
   random_shuffle(BackgroundLikelihood.begin(), BackgroundLikelihood.end());
   random_shuffle(BackgroundLikelihood.begin(), BackgroundLikelihood.end());
   random_shuffle(BackgroundLikelihood.begin(), BackgroundLikelihood.end());
   random_shuffle(BackgroundLikelihood.begin(), BackgroundLikelihood.end());

   // Then, scan some likelihoods
   vector<double> BestPositions;
   
   int NumberOfTries = min((int)BackgroundLikelihood.size() / BackgroundSize,
      (int)SignalLikelihood.size() / SignalSize);
   for(int iTry = 0; iTry < NumberOfTries; iTry++)
   {
      TH1D HLikelihood("HLikelihood", "Likelihood scan for background fraction;f", FBins, FMin, FMax);

      HLikelihood.SetStats(0);

      for(int iBin = 1; iBin <= FBins; iBin++)
      {
         double Fraction = HLikelihood.GetXaxis()->GetBinCenter(iBin);

         double LogLikelihood = 0;
         for(int iS = SignalSize * iTry; iS < SignalSize * (iTry + 1); iS++)
            LogLikelihood = LogLikelihood
               + log(SignalLikelihood[iS].first * (1 - Fraction) + SignalLikelihood[iS].second * Fraction);
         for(int iB = BackgroundSize * iTry; iB < BackgroundSize * (iTry + 1); iB++)
            LogLikelihood = LogLikelihood
               + log(BackgroundLikelihood[iB].first * (1 - Fraction) + BackgroundLikelihood[iB].second * Fraction);

         HLikelihood.SetBinContent(iBin, LogLikelihood);
      }

      if(iTry < 10)
         PsFile.AddPlot(HLikelihood);

      int BestBin = HLikelihood.GetMaximumBin();
      double BestFraction = HLikelihood.GetBinCenter(BestBin);

      HBestFitPosition.Fill(BestFraction);
      BestPositions.push_back(BestFraction);
   }

   sort(BestPositions.begin(), BestPositions.end());
   OutputTree.Fill(SignalSize, BackgroundSize, BestPositions[NumberOfTries*0.1587],
      BestPositions[NumberOfTries*0.5000], BestPositions[NumberOfTries*0.8413], NumberOfTries,
      HBestFitPosition.GetMean(), HBestFitPosition.GetRMS());

   // Write histograms and close things
   BackgroundFile.Close();
   SignalFile.Close();

   PsFile.AddPlot(HBestFitPosition, "", false);
   PsFile.AddPlot(HBestFitPosition, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.cd();

   HBestFitPosition.Write();
   OutputTree.Write();

   OutputFile.Close();

   return 0;
}









