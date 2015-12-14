#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

#include "PlotHelper2.h"

#define PI 3.1415926535897932384626433832795028847971693993751058209749445923078164

struct Likelihoods;
struct ParameterizedLikelihoods;
int main(int argc, char *argv[]);
void SetBranchAddresses(TTree *Tree, Likelihoods &M);
ParameterizedLikelihoods FindParameters(Likelihoods M);
double CalculateLogLikelihood(ParameterizedLikelihoods P, double A1, double A3, double NuisanceParameter);
void SynthesizeHistogram(TH2D &H);

struct Likelihoods
{
   double L1, L3, L13;
   double I1, I3, I13;
   double L1Up, L3Up, L13Up;
   double I1Up, I3Up, I13Up;
   double L1Down, L3Down, L13Down;
   double I1Down, I3Down, I13Down;
};

struct ParameterizedLikelihoods
{
   double V1A, V3A, V13A;
   double V1B, V3B, V13B;
   double I1A, I3A, I13A;
   double I1B, I3B, I13B;
};

int main(int argc, char *argv[])
{
   srand(time(NULL));

   // Input parameters
   string Sample = (argc > 2 ? argv[2] : "1125");
   string FileName = "Samples/hzzTree_id" + Sample + ".root";
   string DirectoryName = "zz4lTree";
   string TreeName = "probe_tree";

   // Output parameters
   string OutputFileName = "FitResults" + Sample;

   // Other parameters
   int DatasetSize = (argc > 1 ? atoi(argv[1]) : 30);

   cout << "Start to run with dataset size " << DatasetSize << " and sample ID " << Sample << endl;

   // Output files and histograms and trees
   TFile OutputFile(Form("%s_%d.root", OutputFileName.c_str(), DatasetSize), "RECREATE");

   TH2D HBestValues(Form("HBestValues_%d", DatasetSize), "Best fit values;atan(A3/5.1A1);Nuisance parameter",
      100, -PI / 2, PI / 2, 100, -1, 1);
   TH1D HBestValuesA3A1(Form("HBestValuesA3A1_%d", DatasetSize), "Best fit values;atan(A3/5.1A1)",
      100, -PI / 2, PI / 2);
   TH1D HBestValuesA3A1Real(Form("HBestValuesA3A1Real_%d", DatasetSize), "Best fit values;A3/A1",
      100, -100, 100);
   TH1D HBestValuesNuisance(Form("HBestValuesNuisance_%d", DatasetSize), "Best fit values;Nuisance parameter",
      100, -1, 1);

   PsFileHelper PsFile(Form("%s_%d.ps", OutputFileName.c_str(), DatasetSize));
   PsFile.AddTextPage("Fits with nuisance parameters!");

   // Initialize trees
   Likelihoods M;

   TFile InputFile(FileName.c_str());
   TTree *SignalTree = (TTree *)InputFile.Get((DirectoryName + "/" + TreeName).c_str());
   SetBranchAddresses(SignalTree, M);

   // Collect signal likelihoods and randomize
   int EntryCount = SignalTree->GetEntries();
   vector<Likelihoods> AllLikelihoods(EntryCount);
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      SignalTree->GetEntry(iEntry);
      AllLikelihoods[iEntry] = M;
   }
   random_shuffle(AllLikelihoods.begin(), AllLikelihoods.end());
   random_shuffle(AllLikelihoods.begin(), AllLikelihoods.end());
   random_shuffle(AllLikelihoods.begin(), AllLikelihoods.end());
   random_shuffle(AllLikelihoods.begin(), AllLikelihoods.end());
   random_shuffle(AllLikelihoods.begin(), AllLikelihoods.end());

   // Fits, scans, etc.
   vector<ParameterizedLikelihoods> CurrentDataset(DatasetSize);
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      CurrentDataset[iEntry%DatasetSize] = FindParameters(AllLikelihoods[iEntry]);

      if((iEntry + 1) % DatasetSize != 0)
         continue;

      TH2D HLikelihoodScan("HLikelihoodScan", ";atan(A3 / (5.1 A1));Nuisance parameter",
         50, -PI / 2, PI / 2, 50, -2, 2);

      double BestA3A1 = 0;
      double BestN = 0;
      double BestValue = 1;

      for(int iX = 1; iX <= 50; iX++)
      {
         for(int iY = 1; iY <= 50; iY++)
         {
            double A1 = 1;
            double A3 = tan(HLikelihoodScan.GetXaxis()->GetBinCenter(iX)) * 5.1;
            double N = HLikelihoodScan.GetYaxis()->GetBinCenter(iY);

            double TotalLikelihood = 0;
            for(int i = 0; i < DatasetSize; i++)
               TotalLikelihood = TotalLikelihood + CalculateLogLikelihood(CurrentDataset[i], A1, A3, N);

            HLikelihoodScan.SetBinContent(iX, iY, TotalLikelihood);

            if(BestValue > 0 || TotalLikelihood > BestValue)
            {
               BestA3A1 = HLikelihoodScan.GetXaxis()->GetBinCenter(iX);
               BestN = N;
               BestValue = TotalLikelihood;
            }
         }
      }

      if(iEntry < DatasetSize * 20)
      {
         HLikelihoodScan.Scale(-1);
         SynthesizeHistogram(HLikelihoodScan);
         HLikelihoodScan.SetStats(0);
         HLikelihoodScan.SetMaximum(20);
         PsFile.AddPlot(HLikelihoodScan, "colz");

         // TCanvas C;
         // HLikelihoodScan.Draw("colz");
         // C.SaveAs(Form("A1A3NFit_LikelihoodExample_%d.png", iEntry / DatasetSize));
         // C.SaveAs(Form("A1A3NFit_LikelihoodExample_%d.C", iEntry / DatasetSize));
         // C.SaveAs(Form("A1A3NFit_LikelihoodExample_%d.eps", iEntry / DatasetSize));
         // C.SaveAs(Form("A1A3NFit_LikelihoodExample_%d.pdf", iEntry / DatasetSize));
      }

      double ProbeBinWidthX = PI / HLikelihoodScan.GetNbinsX();
      double ProbeBinWidthY = 4.0 / HLikelihoodScan.GetNbinsY();

      for(int iTry = 0; iTry < 20; iTry++)
      {
         double CenterA3A1 = BestA3A1;
         double CenterN = BestN;

         for(int i = -2; i <= 2; i++)
         {
            for(int j = -2; j <= 2; j++)
            {
               double A1 = 1;
               double A3 = tan(CenterA3A1 + ProbeBinWidthX * i / 2) * 5.1;
               double N = CenterN + ProbeBinWidthY * j / 2;

               double TotalLikelihood = 0;
               for(int k = 0; k < DatasetSize; k++)
                  TotalLikelihood = TotalLikelihood + CalculateLogLikelihood(CurrentDataset[k], A1, A3, N);

               if(TotalLikelihood > BestValue)
               {
                  BestA3A1 = CenterA3A1 + ProbeBinWidthX * i / 2;
                  BestN = N;
                  BestValue = TotalLikelihood;
               }
            }
         }

         ProbeBinWidthX = ProbeBinWidthX / 2;
         ProbeBinWidthY = ProbeBinWidthY / 2;
      }

      HBestValues.Fill(BestA3A1, BestN);
      HBestValuesA3A1.Fill(BestA3A1);
      HBestValuesA3A1Real.Fill(tan(BestA3A1) * 5.1);
      HBestValuesNuisance.Fill(BestN);
   }

   InputFile.Close();
   
   OutputFile.cd();

   HBestValues.Write();
   HBestValuesA3A1.Write();
   HBestValuesA3A1Real.Write();
   HBestValuesNuisance.Write();

   OutputFile.Close();

   PsFile.AddPlot(HBestValues, "colz");
   PsFile.AddPlot(HBestValuesA3A1, "");
   PsFile.AddPlot(HBestValuesA3A1Real, "");
   PsFile.AddPlot(HBestValuesNuisance, "");

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
   Tree->SetBranchStatus("LikelihoodUp_ExtSig1", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig3", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig13", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig1", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig3", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig13", true);
   Tree->SetBranchStatus("Likelihood_ExtSig1_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig13_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig1_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig3_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig13_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig1_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig3_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig13_Integral", true);
   
   Tree->SetBranchAddress("Likelihood_ExtSig1", &M.L1);
   Tree->SetBranchAddress("Likelihood_ExtSig3", &M.L3);
   Tree->SetBranchAddress("Likelihood_ExtSig13", &M.L13);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig1", &M.L1Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig3", &M.L3Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig13", &M.L13Up);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig1", &M.L1Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig3", &M.L3Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig13", &M.L13Down);
   Tree->SetBranchAddress("Likelihood_ExtSig1_Integral", &M.I1);
   Tree->SetBranchAddress("Likelihood_ExtSig3_Integral", &M.I3);
   Tree->SetBranchAddress("Likelihood_ExtSig13_Integral", &M.I13);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig1_Integral", &M.I1Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig3_Integral", &M.I3Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig13_Integral", &M.I13Up);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig1_Integral", &M.I1Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig3_Integral", &M.I3Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig13_Integral", &M.I13Down);
}

ParameterizedLikelihoods FindParameters(Likelihoods M)
{
   ParameterizedLikelihoods P;

   P.V1A = (M.L1Up * M.I1Up - M.L1Down * M.I1Down) / 2;
   P.V3A = (M.L3Up * M.I3Up - M.L3Down * M.I3Down) / 2;
   P.V13A = (M.L13Up * M.I13Up - M.L13Down * M.I13Down) / 2;
   
   P.V1B = (M.L1Up * M.I1Up + M.L1 * M.I1 + M.L1Down * M.I1Down) / 3;
   P.V3B = (M.L3Up * M.I3Up + M.L3 * M.I3 + M.L3Down * M.I3Down) / 3;
   P.V13B = (M.L13Up * M.I13Up + M.L13 * M.I13 + M.L13Down * M.I13Down) / 3;

   P.I1A = (M.I1Up - M.I1Down) / 2;
   P.I3A = (M.I3Up - M.I3Down) / 2;
   P.I13A = (M.I13Up - M.I13Down) / 2;
   
   P.I1B = (M.I1Up + M.I1 + M.I1Down) / 3;
   P.I3B = (M.I3Up + M.I3 + M.I3Down) / 3;
   P.I13B = (M.I13Up + M.I13 + M.I13Down) / 3;

   return P;
}

double CalculateLogLikelihood(ParameterizedLikelihoods P, double A1, double A3, double NuisanceParameter)
{
   double CombinedIntegral = 0;
   CombinedIntegral = CombinedIntegral + (P.I1A * NuisanceParameter + P.I1B) * A1 * A1;
   CombinedIntegral = CombinedIntegral + (P.I3A * NuisanceParameter + P.I3B) * A3 * A3;
   CombinedIntegral = CombinedIntegral + (P.I13A * NuisanceParameter + P.I13B) * A1 * A3;

   double CombinedValue = 0;
   CombinedValue = CombinedValue + (P.V1A * NuisanceParameter + P.V1B) * A1 * A1;
   CombinedValue = CombinedValue + (P.V3A * NuisanceParameter + P.V3B) * A3 * A3;
   CombinedValue = CombinedValue + (P.V13A * NuisanceParameter + P.V13B) * A1 * A3;

   if(CombinedIntegral * CombinedValue < 0)
      return -9999999;

   static const double Sigma = 2;
   return log(CombinedValue) - log(CombinedIntegral) - NuisanceParameter * NuisanceParameter / 2 / (Sigma * Sigma);
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







