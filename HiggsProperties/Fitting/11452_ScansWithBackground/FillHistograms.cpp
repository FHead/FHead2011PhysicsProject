#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH3D.h"
#include "TH2D.h"
#include "TNtuple.h"

#include "PlotHelper2.h"
#include "ProgressBar.h"

#define PI 3.14159265358979323846264338327950288479716939937510

struct Likelihoods;
int main(int argc, char *argv[]);
double GetLogLikelihood(const Likelihoods &M, double A1, double A3, double F);
void SynthesizeHistogram(TH2D &H);
void SynthesizeHistogram(TH1D &H);
void BranchAddresses(TTree *T, Likelihoods &M);

struct Likelihoods
{
   double L1, L3, L13;
   double I1, I3, I13;
   double LB;
   float Mass;
};

int main(int argc, char *argv[])
{
   srand(time(NULL));

   // Input parameters
   string SignalFileName = "Samples/hzzTree_id1125.root";
   string BackgroundFileName = "Samples/hzzTree_id103.root";
   string DirectoryName = "zz4lTree";
   string TreeName = "probe_tree";

   // Output parameters
   string OutputFileName = "Likelihoods";
   int A1ZZBins = 100, A2ZZBins = 100, A3ZZBins = 100;
   double A1ZZMin = -2, A2ZZMin = -2, A3ZZMin = -5;
   double A1ZZMax = 2, A2ZZMax = 2, A3ZZMax = 5;

   // Other parameters
   double SearchLeft = -10, SearchRight = 10, SearchTolerance = 1e-5;
   int SearchStepCount = 10;
   int MaxTries = 1000;
   int SignalSize = 30, BackgroundSize = 5;

   if(argc > 1)
      SignalSize = atoi(argv[1]);
   if(argc > 2)
      BackgroundSize = atoi(argv[2]);
   if(argc > 3)
      SignalFileName = string("Samples/hzzTree_id") + argv[3] + ".root";

   cout << "Starting job with " << SignalSize << " signals and " << BackgroundSize << " backgrounds." << endl;

   // Our glorious histogram(s) and output files
   TFile OutputFile(Form("/wntmp/yichen/%s_%d_%d.root", OutputFileName.c_str(), SignalSize, BackgroundSize), "RECREATE");

   TH1D HCenter1(Form("HCenter1_%d_%d", SignalSize, BackgroundSize),
      Form("Best fit value of each event (dataset size %d & %d);atan(A3/A1/5)", SignalSize, BackgroundSize),
      100, -PI / 2, PI / 2);
   TH1D HCenter2(Form("HCenter2_%d_%d", SignalSize, BackgroundSize),
      Form("Best fit value of each event (dataset size %d & %d);Fraction", SignalSize, BackgroundSize),
      100, 0, 1);

   PsFileHelper PsFile(Form("%s_%d_%d.ps", OutputFileName.c_str(), SignalSize, BackgroundSize));
   PsFile.AddTextPage("ABCDE");

   // Initialize stuff
   Likelihoods M;
   
   TFile SignalInputFile(SignalFileName.c_str());
   TDirectoryFile *Directory = (TDirectoryFile *)SignalInputFile.Get(DirectoryName.c_str());
   TTree *SignalTree = (TTree *)Directory->Get(TreeName.c_str());
   BranchAddresses(SignalTree, M);

   TFile BackgroundInputFile(BackgroundFileName.c_str());
   Directory = (TDirectoryFile *)BackgroundInputFile.Get(DirectoryName.c_str());
   TTree *BackgroundTree = (TTree *)Directory->Get(TreeName.c_str());
   BranchAddresses(BackgroundTree, M);

   ProgressBar Bar(cout, SignalTree->GetEntries() * 2);
   Bar.SetStyle(1);

   vector<Likelihoods> CurrentDataset(SignalSize + BackgroundSize);

   // First do a loop and get values - signals
   vector<Likelihoods> SignalLikelihoods(SignalTree->GetEntries());

   int SignalEntryCount = SignalTree->GetEntries();
   for(int iEntry = 0; iEntry < SignalEntryCount; iEntry++)
   {
      if(iEntry % 1000 == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      SignalTree->GetEntry(iEntry);
      M.LB = M.LB / 4;
      
      SignalLikelihoods[iEntry] = M;
   }
   random_shuffle(SignalLikelihoods.begin(), SignalLikelihoods.end());
   random_shuffle(SignalLikelihoods.begin(), SignalLikelihoods.end());
   random_shuffle(SignalLikelihoods.begin(), SignalLikelihoods.end());
   random_shuffle(SignalLikelihoods.begin(), SignalLikelihoods.end());
   random_shuffle(SignalLikelihoods.begin(), SignalLikelihoods.end());

   // backgrounds
   vector<Likelihoods> BackgroundLikelihoods;

   int BackgroundEntryCount = BackgroundTree->GetEntries();
   for(int iEntry = 0; iEntry < BackgroundEntryCount; iEntry++)
   {
      BackgroundTree->GetEntry(iEntry);
      M.LB = M.LB / 4;

      if(M.Mass > 120 && M.Mass < 130)
         BackgroundLikelihoods.push_back(M);
   }
   random_shuffle(BackgroundLikelihoods.begin(), BackgroundLikelihoods.end());
   random_shuffle(BackgroundLikelihoods.begin(), BackgroundLikelihoods.end());
   random_shuffle(BackgroundLikelihoods.begin(), BackgroundLikelihoods.end());
   random_shuffle(BackgroundLikelihoods.begin(), BackgroundLikelihoods.end());
   random_shuffle(BackgroundLikelihoods.begin(), BackgroundLikelihoods.end());

   // really Loop over things!
   int NumberOfTries = (int)SignalLikelihoods.size() / SignalSize;
   int BackgroundOffset = 0;
   int CurrentIndex = 0;
   vector<double> BestFitFractions;
   for(int iEntry = 0; iEntry < SignalEntryCount; iEntry++)
   {
      if(iEntry % 1000 == 0)
      {
         Bar.Update(iEntry + SignalEntryCount);
         Bar.Print();
      }

      int Index = iEntry % SignalSize;
      CurrentDataset[Index] = SignalLikelihoods[iEntry];

      if((iEntry + 1) % SignalSize != 0)
         continue;
      CurrentIndex = CurrentIndex + 1;

      for(int iB = 0; iB < BackgroundSize; iB++)
         CurrentDataset[SignalSize+iB] = BackgroundLikelihoods[(iB+BackgroundOffset)%BackgroundLikelihoods.size()];
      BackgroundOffset = BackgroundOffset + BackgroundSize;
      BackgroundOffset = BackgroundOffset % BackgroundLikelihoods.size();

      // For the first few plots, do a complete scan and show the likelihood profile
      TH2D HLikelihoodScan("HLikelihoodScan",
         "Scan of likelihoods for a pseudo-dataset;F;atan(A3/(5.1 A1))", 100, 0, 1, 100, -PI / 2, PI / 2);

      double BestF = 0;
      double BestA = 0;
      double BestValue = -999999;

      for(int iF = 1; iF <= 100; iF++)
      {
         for(int iA = 1; iA <= 100; iA++)
         {
            double F = HLikelihoodScan.GetXaxis()->GetBinCenter(iF);
            double A1 = 1;
            double A3 = tan(HLikelihoodScan.GetYaxis()->GetBinCenter(iA)) * 5.1;

            double FinalLikelihood = 0;
            for(int i = 0; i < SignalSize + BackgroundSize; i++)
               FinalLikelihood = FinalLikelihood + GetLogLikelihood(CurrentDataset[i], A1, A3, F);

            HLikelihoodScan.SetBinContent(iF, iA, FinalLikelihood);

            if(FinalLikelihood > BestValue)
            {
               BestF = HLikelihoodScan.GetXaxis()->GetBinCenter(iF);
               BestA = HLikelihoodScan.GetYaxis()->GetBinCenter(iA);
               BestValue = FinalLikelihood;
            }
         }
      }

      HLikelihoodScan.Scale(-1);
      SynthesizeHistogram(HLikelihoodScan);
      HLikelihoodScan.SetStats(0);

      if(CurrentIndex <= 10)
      {
         PsFile.AddPlot(HLikelihoodScan, "colz");

         /*
         TCanvas Canvas("Canvas", "", 1024, 1024);
         HLikelihoodScan.Draw("colz");
         Canvas.SaveAs(Form("ScanLikelihood_%d_%d_%d.png", SignalSize, BackgroundSize, CurrentIndex));
         Canvas.SaveAs(Form("ScanLikelihood_%d_%d_%d.C", SignalSize, BackgroundSize, CurrentIndex));
         Canvas.SaveAs(Form("ScanLikelihood_%d_%d_%d.eps", SignalSize, BackgroundSize, CurrentIndex));
         Canvas.SaveAs(Form("ScanLikelihood_%d_%d_%d.pdf", SignalSize, BackgroundSize, CurrentIndex));
         */
      }

      double StepSizeA = PI / 100;   // default to histogram bin width
      double StepSizeF = 2.0 / 100;
      for(int iTry = 0; iTry < 10; iTry++)
      {
         double CurrentBestA = BestA;
         double CurrentBestF = BestF;
         double CurrentBestValue = BestValue;

         for(int iA = -2; iA <= 2; iA++)
         {
            for(int iF = -2; iF <= 2; iF++)
            {
               double F = BestF + iF * 0.5 * StepSizeF;
               double A1 = 1;
               double A3 = tan(BestA + iA * 0.5 * StepSizeA) * 5.1;

               double FinalLikelihood = 0;
               for(int i = 0; i < SignalSize + BackgroundSize; i++)
                  FinalLikelihood = FinalLikelihood + GetLogLikelihood(CurrentDataset[i], A1, A3, F);
               
               if(FinalLikelihood > CurrentBestValue)
               {
                  CurrentBestA = BestA + iA * 0.5 * StepSizeA;
                  CurrentBestF = BestF + iF * 0.5 * StepSizeF;
                  CurrentBestValue = BestValue;
               }
            }
         }

         BestA = CurrentBestA;
         BestF = CurrentBestF;
         BestValue = CurrentBestValue;

         StepSizeA = StepSizeA / 2;
         StepSizeF = StepSizeF / 2;
      }

      HCenter1.Fill(BestA);
      HCenter2.Fill(BestF);

      BestFitFractions.push_back(BestF);
   }

   sort(BestFitFractions.begin(), BestFitFractions.end());

   Bar.Update(SignalEntryCount * 2);
   Bar.Print();
   Bar.PrintLine();

   SignalInputFile.Close();
   BackgroundInputFile.Close();

   // Write histograms and output
   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.cd();

   TNtuple Tree("ResultTree", "Title!",
      "SignalSize:BackgroundSize:MedianFraction:PlusFraction:MinusFraction:MeanFraction:RMSFraction");
   Tree.Fill(SignalSize, BackgroundSize,
      BestFitFractions[BestFitFractions.size()*0.5000],
      BestFitFractions[BestFitFractions.size()*0.8413],
      BestFitFractions[BestFitFractions.size()*0.1587],
      HCenter2.GetMean(), HCenter2.GetRMS());
   Tree.Write();

   HCenter1.Write();
   HCenter2.Write();

   OutputFile.Close();

   return 0;
}

double GetLogLikelihood(const Likelihoods &M, double A1, double A3, double F)
{
   double CombinedIntegral = 0;
   CombinedIntegral = CombinedIntegral + M.I1 * A1 * A1;
   CombinedIntegral = CombinedIntegral + M.I3 * A3 * A3;
   CombinedIntegral = CombinedIntegral + M.I13 * A1 * A3;

   double CombinedValue = 0;
   CombinedValue = CombinedValue + M.L1 * M.I1 * A1 * A1;
   CombinedValue = CombinedValue + M.L3 * M.I3 * A3 * A3;
   CombinedValue = CombinedValue + M.L13 * M.I13 * A1 * A3;

   if(CombinedIntegral * CombinedValue < 0)   // error!
      return -999999;

   double SignalLikelihood = CombinedValue / CombinedIntegral;

   return log(SignalLikelihood * (1 - F) + M.LB * F);
}

void SynthesizeHistogram(TH1D &H)
{
   double Minimum = H.GetMinimum();
   for(int i = 1; i <= H.GetNbinsX(); i++)
      H.SetBinContent(i, H.GetBinContent(i) - Minimum);
}

void SynthesizeHistogram(TH2D &H)
{
   double Minimum = H.GetMinimum();
   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      for(int j = 1; j <= H.GetNbinsY(); j++)
         H.SetBinContent(i, j, H.GetBinContent(i, j) - Minimum);
   }
}

void BranchAddresses(TTree *T, Likelihoods &M)
{
   T->SetBranchStatus("*", false);
   T->SetBranchStatus("Likelihood_ExtSig1", true);
   T->SetBranchStatus("Likelihood_ExtSig3", true);
   T->SetBranchStatus("Likelihood_ExtSig13", true);
   T->SetBranchStatus("Likelihood_EffMEE", true);
   T->SetBranchStatus("Likelihood_ExtSig1_Integral", true);
   T->SetBranchStatus("Likelihood_ExtSig3_Integral", true);
   T->SetBranchStatus("Likelihood_ExtSig13_Integral", true);
   T->SetBranchStatus("mass", true);

   T->SetBranchAddress("Likelihood_ExtSig1", &M.L1);
   T->SetBranchAddress("Likelihood_ExtSig3", &M.L3);
   T->SetBranchAddress("Likelihood_ExtSig13", &M.L13);
   T->SetBranchAddress("Likelihood_EffMEE", &M.LB);
   T->SetBranchAddress("Likelihood_ExtSig1_Integral", &M.I1);
   T->SetBranchAddress("Likelihood_ExtSig3_Integral", &M.I3);
   T->SetBranchAddress("Likelihood_ExtSig13_Integral", &M.I13);
   T->SetBranchAddress("mass", &M.Mass);
}






