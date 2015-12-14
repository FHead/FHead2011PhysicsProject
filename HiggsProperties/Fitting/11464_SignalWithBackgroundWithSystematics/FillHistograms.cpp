#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH2D.h"

#include "PlotHelper2.h"
#include "ProgressBar.h"

#define PI 3.1415926535897932384626433832795028847971693993751058209749445923078164

struct Likelihoods;
struct ParameterizedLikelihoods;
int main(int argc, char *argv[]);
void SetBranchAddresses(TTree *Tree, Likelihoods &M);
ParameterizedLikelihoods FindParameters(Likelihoods M);
double CalculateLogLikelihood(ParameterizedLikelihoods P, double A1, double A3, double F, double NuisanceParameter);
void SynthesizeHistogram(TH2D &H);

struct Likelihoods
{
   double L1, L3, L13, LB;
   double I1, I3, I13, IB;
   double L1Up, L3Up, L13Up, LBUp;
   double I1Up, I3Up, I13Up, IBUp;
   double L1Down, L3Down, L13Down, LBDown;
   double I1Down, I3Down, I13Down, IBDown;
};

struct ParameterizedLikelihoods
{
   double V1A, V3A, V13A, VBA;
   double V1B, V3B, V13B, VBB;
   double I1A, I3A, I13A, IBA;
   double I1B, I3B, I13B, IBB;
};

int main(int argc, char *argv[])
{
   srand(time(NULL));

   // Input parameters
   string SignalSample = (argc > 3 ? argv[3] : "1125");
   string BackgroundSample = "103";
   string SignalFileName = "Samples/hzzTree_id" + SignalSample + ".root";
   string BackgroundFileName = "Samples/hzzTree_id" + BackgroundSample + ".root";
   string DirectoryName = "zz4lTree";
   string TreeName = "probe_tree";

   // Output parameters
   string OutputFileName = "FitResults" + SignalSample;

   // Other parameters
   int SignalDatasetSize = (argc > 1 ? atoi(argv[1]) : 30);
   int BackgroundDatasetSize = (argc > 2 ? atoi(argv[2]) : 5);

   cout << "Start to run with dataset size " << SignalDatasetSize << " + " << BackgroundDatasetSize
      << " and sample ID " << SignalSample << " and " << BackgroundSample << endl;

   // Output files and histograms and trees
   string Tag = Form("%03d_%03d", SignalDatasetSize, BackgroundDatasetSize);
   TFile OutputFile(Form("%s_%s.root", OutputFileName.c_str(), Tag.c_str()), "RECREATE");

   TH2D HBest(Form("HBest_%s", Tag.c_str()), "Best fit;atan(A3/5.1A1);Fraction",
      100, -PI / 2, PI / 2, 100, 0, 1);
   TH1D HBestA3A1(Form("HBestA3A1_%s", Tag.c_str()), "Best fit;atan(A3/5.1A1)",
      100, -PI / 2, PI / 2);
   TH1D HBestA3A1Real(Form("HBestA3A1Real_%s", Tag.c_str()), "Best fit;A3/A1",
      100, -100, 100);
   TH1D HBestNuisance(Form("HBestNuisance_%s", Tag.c_str()), "Best fit;Nuisance parameter",
      100, -5, 5);
   TH1D HBestFraction(Form("HBestFraction_%s", Tag.c_str()), "Best fit;Fraction",
      100, 0, 1);

   TNtuple OutputTree("OutputTree", "THIS IS TITLE!",
      "SignalSize:BackgroundSize:MedianFraction:PlusFraction:MinusFraction:MeanFraction:RMSFraction");

   PsFileHelper PsFile(Form("%s_%s.ps", OutputFileName.c_str(), Tag.c_str()));
   PsFile.AddTextPage("Fits with nuisance parameters!");

   // Initialize trees
   Likelihoods M;

   TFile SignalInputFile(SignalFileName.c_str());
   TTree *SignalTree = (TTree *)SignalInputFile.Get((DirectoryName + "/" + TreeName).c_str());
   SetBranchAddresses(SignalTree, M);
   
   TFile BackgroundInputFile(BackgroundFileName.c_str());
   TTree *BackgroundTree = (TTree *)BackgroundInputFile.Get((DirectoryName + "/" + TreeName).c_str());
   SetBranchAddresses(BackgroundTree, M);
   
   float Mass = 0;
   BackgroundTree->SetBranchStatus("mass", true);
   BackgroundTree->SetBranchAddress("mass", &Mass);

   // Collect signal likelihoods and randomize
   int SignalEntryCount = SignalTree->GetEntries();
   vector<Likelihoods> AllSignalLikelihoods(SignalEntryCount);
   for(int iEntry = 0; iEntry < SignalEntryCount; iEntry++)
   {
      SignalTree->GetEntry(iEntry);
      M.LB = M.LB / 4;
      M.LBUp = M.LBUp / 4;
      M.LBDown = M.LBDown / 4;
      
      AllSignalLikelihoods[iEntry] = M;
   }
   cout << "Number of selected signal events: " << AllSignalLikelihoods.size() << endl;
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());

   int BackgroundEntryCount = BackgroundTree->GetEntries();
   vector<Likelihoods> AllBackgroundLikelihoods;
   for(int iEntry = 0; iEntry < BackgroundEntryCount; iEntry++)
   {
      BackgroundTree->GetEntry(iEntry);
      M.LB = M.LB / 4;
      M.LBUp = M.LBUp / 4;
      M.LBDown = M.LBDown / 4;

      if(Mass > 120 && Mass < 130)
         AllBackgroundLikelihoods.push_back(M);
   }
   cout << "Number of selected background events: " << AllBackgroundLikelihoods.size() << endl;
   random_shuffle(AllBackgroundLikelihoods.begin(), AllBackgroundLikelihoods.end());
   random_shuffle(AllBackgroundLikelihoods.begin(), AllBackgroundLikelihoods.end());
   random_shuffle(AllBackgroundLikelihoods.begin(), AllBackgroundLikelihoods.end());
   random_shuffle(AllBackgroundLikelihoods.begin(), AllBackgroundLikelihoods.end());
   random_shuffle(AllBackgroundLikelihoods.begin(), AllBackgroundLikelihoods.end());

   // Fits, scans, etc.
   ProgressBar Bar(cout, SignalEntryCount);
   Bar.SetStyle(4);
   Bar.Print();

   vector<ParameterizedLikelihoods> CurrentDataset(SignalDatasetSize + BackgroundDatasetSize);
   int BackgroundOffset = 0;
   vector<double> BestFitFractions;

   for(int iEntry = 0; iEntry < SignalEntryCount; iEntry++)
   {
      if(iEntry % 100 == 0 && iEntry > SignalDatasetSize * 20)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }
      
      CurrentDataset[iEntry%SignalDatasetSize] = FindParameters(AllSignalLikelihoods[iEntry]);
      
      if((iEntry + 1) % SignalDatasetSize != 0)
         continue;

      for(int iB = 0; iB < BackgroundDatasetSize; iB++)
      {
         int Index = (iB + BackgroundOffset) % AllBackgroundLikelihoods.size();
         CurrentDataset[SignalDatasetSize+iB] = FindParameters(AllBackgroundLikelihoods[Index]);
      }
      BackgroundOffset = BackgroundOffset + BackgroundDatasetSize;

      int BinCount = 20;
      if(iEntry < SignalDatasetSize * 2)
         BinCount = 100;
      else if(iEntry < SignalDatasetSize * 10)
         BinCount = 50;
      else
         BinCount = 20;

      TH2D HLikelihoodScan("HLikelihoodScan", "Likelihood;atan(A3 / (5.1 A1));Background fraction",
         BinCount, -PI / 2, PI / 2, BinCount, 0, 1);
      TH2D HNuisanceParameterPosition("HNuisanceParameterPosition",
         "Best nuisance parameter position;atan(A3 / (5.1 A1));Background fraction",
         BinCount, -PI / 2, PI / 2, BinCount, 0, 1);

      double BestA3A1 = 0;
      double BestF = 0;
      double GlobalBestN = 0;
      double BestValue = 1;

      for(int iX = 1; iX <= BinCount; iX++)
      {
         for(int iY = 1; iY <= BinCount; iY++)
         {
            double A1 = 1;
            double A3 = tan(HLikelihoodScan.GetXaxis()->GetBinCenter(iX)) * 5.1;
            double F = HLikelihoodScan.GetYaxis()->GetBinCenter(iY);

            double BestN = 0;
            double BestValueN = 1;

            double CenterN = 0;
            double StepSize = 5;

            for(int iTry = 0; iTry < 5; iTry++)
            {
               for(int iS = -5; iS <= 5; iS++)
               {
                  double N = CenterN + StepSize * iS / 5;

                  double TotalLikelihood = 0;
                  for(int i = 0; i < SignalDatasetSize + BackgroundDatasetSize; i++)
                     TotalLikelihood = TotalLikelihood + CalculateLogLikelihood(CurrentDataset[i], A1, A3, F, N);

                  if(BestValueN > 0 || TotalLikelihood > BestValueN)
                  {
                     BestN = N;
                     BestValueN = TotalLikelihood;
                  }

                  if(BestValue > 0 || TotalLikelihood > BestValue)
                  {
                     BestA3A1 = HLikelihoodScan.GetXaxis()->GetBinCenter(iX);
                     BestF = F;
                     BestValue = TotalLikelihood;
                     GlobalBestN = N;
                  }
               }

               CenterN = BestN;
               StepSize = StepSize / 5;
            }
                  
            HLikelihoodScan.SetBinContent(iX, iY, BestValueN);
            HNuisanceParameterPosition.SetBinContent(iX, iY, BestN);
         }
      }

      if(iEntry < SignalDatasetSize * 20)
      {
         HLikelihoodScan.Scale(-1);
         SynthesizeHistogram(HLikelihoodScan);
         HLikelihoodScan.SetStats(0);
         PsFile.AddPlot(HLikelihoodScan, "colz");

         HNuisanceParameterPosition.SetStats(0);
         PsFile.AddPlot(HNuisanceParameterPosition, "colz");
      }

      double ProbeBinWidthX = PI / HLikelihoodScan.GetNbinsX();   // -PI/2 ~ PI/2 for atan(...)
      double ProbeBinWidthY = 1.0 / HLikelihoodScan.GetNbinsY();   // 0 ~ 1 for fraction
      
      for(int iTry = 0; iTry < 20; iTry++)
      {
         double CenterA3A1 = BestA3A1;
         double CenterF = BestF;

         for(int i = -2; i <= 2; i++)
         {
            for(int j = -2; j <= 2; j++)
            {
               double A1 = 1;
               double A3 = tan(CenterA3A1 + ProbeBinWidthX * i / 2) * 5.1;
               double F = CenterF + ProbeBinWidthY * j / 2;

               double BestN = 0;
               double BestValueN = 0;

               double CenterN = 0;
               double StepSize = 5;

               for(int iTryN = 0; iTryN < 10; iTryN++)
               {
                  for(int iS = -5; iS <= 5; iS++)
                  {
                     double N = CenterN + StepSize * iS / 5;

                     double TotalLikelihood = 0;
                     for(int iD = 0; iD < SignalDatasetSize + BackgroundDatasetSize; iD++)
                        TotalLikelihood = TotalLikelihood + CalculateLogLikelihood(CurrentDataset[iD], A1, A3, F, N);

                     if(BestValueN > 0 || TotalLikelihood > BestValueN)
                     {
                        BestN = N;
                        BestValueN = TotalLikelihood;
                     }

                     if(TotalLikelihood > BestValue)
                     {
                        BestA3A1 = CenterA3A1 + ProbeBinWidthX * i / 2;
                        BestF = F;
                        BestValue = TotalLikelihood;
                        GlobalBestN = N;
                     }
                  }

                  CenterN = BestN;
                  StepSize = StepSize / 5;
               }
            }
         }

         ProbeBinWidthX = ProbeBinWidthX / 2;
         ProbeBinWidthY = ProbeBinWidthY / 2;
      }

      HBest.Fill(BestA3A1, BestF);
      HBestA3A1.Fill(BestA3A1);
      HBestA3A1Real.Fill(tan(BestA3A1) * 5.1);
      HBestNuisance.Fill(GlobalBestN);
      HBestFraction.Fill(BestF);

      BestFitFractions.push_back(BestF);
   }

   Bar.Update(SignalEntryCount);
   Bar.Print();
   Bar.PrintLine();

   sort(BestFitFractions.begin(), BestFitFractions.end());

   SignalInputFile.Close();
   BackgroundInputFile.Close();
   
   OutputFile.cd();

   HBest.Write();
   HBestA3A1.Write();
   HBestA3A1Real.Write();
   HBestNuisance.Write();
   HBestFraction.Write();

   OutputTree.Fill(SignalDatasetSize, BackgroundDatasetSize,
      BestFitFractions[BestFitFractions.size()*0.5000],
      BestFitFractions[BestFitFractions.size()*0.8413],
      BestFitFractions[BestFitFractions.size()*0.1587],
      HBestFraction.GetMean(), HBestFraction.GetRMS());
   OutputTree.Write();

   PsFile.AddPlot(HBest, "colz");
   PsFile.AddPlot(HBestA3A1, "");
   PsFile.AddPlot(HBestA3A1Real, "");
   PsFile.AddPlot(HBestNuisance, "");
   PsFile.AddPlot(HBestFraction, "");

   OutputFile.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void SetBranchAddresses(TTree *Tree, Likelihoods &M)
{
   Tree->SetBranchStatus("*", false);
   Tree->SetBranchStatus("Likelihood_ExtSig1", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3", true);
   Tree->SetBranchStatus("Likelihood_ExtSig13", true);
   Tree->SetBranchStatus("Likelihood_EffMEE", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig1", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig3", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig13", true);
   Tree->SetBranchStatus("LikelihoodUp_EffMEE", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig1", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig3", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig13", true);
   Tree->SetBranchStatus("LikelihoodDown_EffMEE", true);
   Tree->SetBranchStatus("Likelihood_ExtSig1_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig13_Integral", true);
   Tree->SetBranchStatus("Likelihood_EffMEE_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig1_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig3_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig13_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_EffMEE_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig1_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig3_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig13_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_EffMEE_Integral", true);
   
   Tree->SetBranchAddress("Likelihood_ExtSig1", &M.L1);
   Tree->SetBranchAddress("Likelihood_ExtSig3", &M.L3);
   Tree->SetBranchAddress("Likelihood_ExtSig13", &M.L13);
   Tree->SetBranchAddress("Likelihood_EffMEE", &M.LB);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig1", &M.L1Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig3", &M.L3Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig13", &M.L13Up);
   Tree->SetBranchAddress("LikelihoodUp_EffMEE", &M.LBUp);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig1", &M.L1Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig3", &M.L3Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig13", &M.L13Down);
   Tree->SetBranchAddress("LikelihoodDown_EffMEE", &M.LBDown);
   Tree->SetBranchAddress("Likelihood_ExtSig1_Integral", &M.I1);
   Tree->SetBranchAddress("Likelihood_ExtSig3_Integral", &M.I3);
   Tree->SetBranchAddress("Likelihood_ExtSig13_Integral", &M.I13);
   Tree->SetBranchAddress("Likelihood_EffMEE_Integral", &M.IB);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig1_Integral", &M.I1Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig3_Integral", &M.I3Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig13_Integral", &M.I13Up);
   Tree->SetBranchAddress("LikelihoodUp_EffMEE_Integral", &M.IBUp);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig1_Integral", &M.I1Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig3_Integral", &M.I3Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig13_Integral", &M.I13Down);
   Tree->SetBranchAddress("LikelihoodDown_EffMEE_Integral", &M.IBDown);
}

ParameterizedLikelihoods FindParameters(Likelihoods M)
{
   ParameterizedLikelihoods P;

   P.V1A = (M.L1Up * M.I1Up - M.L1Down * M.I1Down) / 2;
   P.V3A = (M.L3Up * M.I3Up - M.L3Down * M.I3Down) / 2;
   P.V13A = (M.L13Up * M.I13Up - M.L13Down * M.I13Down) / 2;
   P.VBA = (M.LBUp * M.IBUp - M.LBDown * M.IBDown) / 2;
   
   P.V1B = (M.L1Up * M.I1Up + M.L1 * M.I1 + M.L1Down * M.I1Down) / 3;
   P.V3B = (M.L3Up * M.I3Up + M.L3 * M.I3 + M.L3Down * M.I3Down) / 3;
   P.V13B = (M.L13Up * M.I13Up + M.L13 * M.I13 + M.L13Down * M.I13Down) / 3;
   P.VBB = (M.LBUp * M.IBUp + M.LB * M.IB + M.LBDown * M.IBDown) / 3;

   P.I1A = (M.I1Up - M.I1Down) / 2;
   P.I3A = (M.I3Up - M.I3Down) / 2;
   P.I13A = (M.I13Up - M.I13Down) / 2;
   P.IBA = (M.IBUp - M.IBDown) / 2;
   
   P.I1B = (M.I1Up + M.I1 + M.I1Down) / 3;
   P.I3B = (M.I3Up + M.I3 + M.I3Down) / 3;
   P.I13B = (M.I13Up + M.I13 + M.I13Down) / 3;
   P.IBB = (M.IBUp + M.IB + M.IBDown) / 3;

   return P;
}

double CalculateLogLikelihood(ParameterizedLikelihoods P, double A1, double A3, double F, double NuisanceParameter)
{
   double CombinedIntegral = 0;
   CombinedIntegral = CombinedIntegral + (P.I1A * NuisanceParameter + P.I1B) * A1 * A1;
   CombinedIntegral = CombinedIntegral + (P.I3A * NuisanceParameter + P.I3B) * A3 * A3;
   CombinedIntegral = CombinedIntegral + (P.I13A * NuisanceParameter + P.I13B) * A1 * A3;

   double CombinedValue = 0;
   CombinedValue = CombinedValue + (P.V1A * NuisanceParameter + P.V1B) * A1 * A1;
   CombinedValue = CombinedValue + (P.V3A * NuisanceParameter + P.V3B) * A3 * A3;
   CombinedValue = CombinedValue + (P.V13A * NuisanceParameter + P.V13B) * A1 * A3;

   double SignalLikelihood = CombinedValue / CombinedIntegral;
   double BackgroundLikelihood = (P.VBA * NuisanceParameter + P.VBB) / (P.IBA * NuisanceParameter + P.IBB);
   
   if(SignalLikelihood < 0)
      return -9999999;
   if(BackgroundLikelihood < 0)
      return -9999999;

   static const double Sigma = 1;
   return log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F)
      - NuisanceParameter * NuisanceParameter / (2 * Sigma * Sigma);
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







