#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH3D.h"
#include "TH2D.h"

#include "ProgressBar.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[]);
double GetLikelihood(double LL1, double LL2, double LL3, double LL12, double LL13, double LL23,
   double I1, double I2, double I3, double I12, double I23, double I13,
   double A1, double A2, double A3);
void SynthesizeHistogram(TH2D &H);
void SynthesizeHistogram(TH1D &H);

int main(int argc, char *argv[])
{
   srand(time(NULL));

   // Input parameters
   string FileName = "Samples/hzzTree_id8125.root";
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
   int DatasetSize = 1000;

   if(argc > 1)
      DatasetSize = atoi(argv[1]);

   // Our glorious histogram(s) and output files
   TFile OutputFile(Form("%s_%d.root", OutputFileName.c_str(), DatasetSize), "RECREATE");

   TH1D HCenter1(Form("HCenter1_%d", DatasetSize),
      Form("Best fit value of each event (dataset size %d)", DatasetSize), 100, -100, 100);
   TH1D HCenter2(Form("HCenter2_%d", DatasetSize),
      Form("Best fit value of each event (dataset size %d)", DatasetSize), 100, -50, 50);
   TH1D HCenter3(Form("HCenter3_%d", DatasetSize),
      Form("Best fit value of each event (dataset size %d)", DatasetSize), 100, -5, 5);
   
   TH1D HCenter4(Form("HCenter4_%d", DatasetSize),
      Form("Best fit value of each event (dataset size %d);atan(A3/A1/5)", DatasetSize), 100, -PI / 2, PI / 2);

   // Initialize stuff
   TFile InputFile(FileName.c_str());
   TDirectoryFile *Directory = (TDirectoryFile *)InputFile.Get(DirectoryName.c_str());
   TTree *Tree = (TTree *)Directory->Get(TreeName.c_str());

   Tree->SetBranchStatus("*", false);

   Tree->SetBranchStatus("Likelihood_ExtSig1", true);
   Tree->SetBranchStatus("Likelihood_ExtSig2", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3", true);
   Tree->SetBranchStatus("Likelihood_ExtSig12", true);
   Tree->SetBranchStatus("Likelihood_ExtSig13", true);
   Tree->SetBranchStatus("Likelihood_ExtSig23", true);
   Tree->SetBranchStatus("Likelihood_ExtSig1_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig2_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig12_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig13_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig23_Integral", true);

   double L1, L2, L3, L12, L23, L13;
   double I1, I2, I3, I12, I23, I13;
   Tree->SetBranchAddress("Likelihood_ExtSig1", &L1);
   Tree->SetBranchAddress("Likelihood_ExtSig2", &L2);
   Tree->SetBranchAddress("Likelihood_ExtSig3", &L3);
   Tree->SetBranchAddress("Likelihood_ExtSig12", &L12);
   Tree->SetBranchAddress("Likelihood_ExtSig13", &L13);
   Tree->SetBranchAddress("Likelihood_ExtSig23", &L23);
   Tree->SetBranchAddress("Likelihood_ExtSig1_Integral", &I1);
   Tree->SetBranchAddress("Likelihood_ExtSig2_Integral", &I2);
   Tree->SetBranchAddress("Likelihood_ExtSig3_Integral", &I3);
   Tree->SetBranchAddress("Likelihood_ExtSig12_Integral", &I12);
   Tree->SetBranchAddress("Likelihood_ExtSig13_Integral", &I13);
   Tree->SetBranchAddress("Likelihood_ExtSig23_Integral", &I23);
   
   ProgressBar Bar(cout, Tree->GetEntries() * 2);
   Bar.SetStyle(1);

   vector<double> VL1(DatasetSize), VL2(DatasetSize), VL3(DatasetSize),
      VL12(DatasetSize), VL13(DatasetSize), VL23(DatasetSize);

   // This is to reduce correlation between different dataset sizes
   vector<int> Indices(Tree->GetEntries());
   for(int i = 0; i < (int)Indices.size(); i++)
      Indices[i] = i;

   random_shuffle(Indices.begin(), Indices.end());
   random_shuffle(Indices.begin(), Indices.end());
   random_shuffle(Indices.begin(), Indices.end());
   random_shuffle(Indices.begin(), Indices.end());
   random_shuffle(Indices.begin(), Indices.end());
   
   // First do a loop and get values
   vector<double> TL1(Indices.size()), TL2(Indices.size()), TL3(Indices.size()),
      TL12(Indices.size()), TL13(Indices.size()), TL23(Indices.size());
   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(iEntry % 1000 == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }
      
      Tree->GetEntry(iEntry);
      TL1[iEntry] = L1;
      TL2[iEntry] = L2;
      TL3[iEntry] = L3;
      TL12[iEntry] = L12;
      TL13[iEntry] = L13;
      TL23[iEntry] = L23;
   }

   // really Loop over things!
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(iEntry % 1000 == 0)
      {
         Bar.Update(iEntry + EntryCount);
         Bar.Print();
      }

      int Index = iEntry % DatasetSize;
      VL1[Index] = TL1[Indices[iEntry]];
      VL2[Index] = TL2[Indices[iEntry]];
      VL3[Index] = TL3[Indices[iEntry]];
      VL12[Index] = TL12[Indices[iEntry]];
      VL13[Index] = TL13[Indices[iEntry]];
      VL23[Index] = TL23[Indices[iEntry]];

      if((iEntry + 1) % DatasetSize != 0)
         continue;

      // Do scan for events
      double Left = SearchLeft, Right = SearchRight;

      int NumberOfTries = 0;
      while(Right - Left > SearchTolerance)
      {
         int BestIndex = -1;
         double BestValue = 0;

         for(int iStep = 0; iStep <= SearchStepCount; iStep++)
         {
            double FinalLikelihood = 0;

            for(int i = 0; i < DatasetSize; i++)
            {
               double A1 = 1;
               double A2 = 0;
               double A3 = (Right - Left) / SearchStepCount * iStep + Left;

               FinalLikelihood = FinalLikelihood + GetLikelihood(VL1[i], VL2[i], VL3[i], VL12[i], VL13[i], VL23[i],
                  I1, I2, I3, I12, I23, I13, A1, A2, A3);
            }

            if(FinalLikelihood > BestValue || BestIndex == -1)
            {
               BestIndex = iStep;
               BestValue = FinalLikelihood;
            }
         }

         if(BestIndex == 0)
         {
            double TempLeft = Left - (Right - Left) * 0.8;
            double TempRight = Left + (Right - Left) * 0.2;
            Left = TempLeft;
            Right = TempRight;
         }
         else if(BestIndex == SearchStepCount)
         {
            double TempLeft = Right - (Right - Left) * 0.2;
            double TempRight = Right + (Right - Left) * 0.8;
            Left = TempLeft;
            Right = TempRight;
         }
         else
         {
            double TempLeft = (Right - Left) / SearchStepCount * (BestIndex - 1) + Left;
            double TempRight = (Right - Left) / SearchStepCount * (BestIndex + 1) + Left;
            Left = TempLeft;
            Right = TempRight;
         }

         NumberOfTries = NumberOfTries + 1;
         if(NumberOfTries > MaxTries)
            break;
      }

      // if(NumberOfTries <= MaxTries)
      {
         HCenter1.Fill((Right + Left) / 2);
         HCenter2.Fill((Right + Left) / 2);
         HCenter3.Fill((Right + Left) / 2);
         HCenter4.Fill(atan((Right + Left) / 2 / 5.1));
      }
   }

   Bar.Update(EntryCount * 2);
   Bar.Print();
   Bar.PrintLine();

   InputFile.Close();

   // Write histograms
   OutputFile.cd();

   HCenter1.Write();
   HCenter2.Write();
   HCenter3.Write();
   HCenter4.Write();

   OutputFile.Close();

   return 0;
}

double GetLikelihood(double LL1, double LL2, double LL3, double LL12, double LL13, double LL23,
   double I1, double I2, double I3, double I12, double I23, double I13,
   double A1, double A2, double A3)
{
   double CombinedIntegral = 0;
   CombinedIntegral = CombinedIntegral + I1 * A1 * A1;
   CombinedIntegral = CombinedIntegral + I2 * A2 * A2;
   CombinedIntegral = CombinedIntegral + I3 * A3 * A3;
   CombinedIntegral = CombinedIntegral + I12 * A1 * A2;
   CombinedIntegral = CombinedIntegral + I13 * A1 * A3;
   CombinedIntegral = CombinedIntegral + I23 * A2 * A3;

   double CombinedValue = 0;
   CombinedValue = CombinedValue + LL1 * I1 * A1 * A1;
   CombinedValue = CombinedValue + LL2 * I2 * A2 * A2;
   CombinedValue = CombinedValue + LL3 * I3 * A3 * A3;
   CombinedValue = CombinedValue + LL12 * I12 * A1 * A2;
   CombinedValue = CombinedValue + LL13 * I13 * A1 * A3;
   CombinedValue = CombinedValue + LL23 * I23 * A2 * A3;

   if(CombinedIntegral * CombinedValue < 0)   // error!
      return -999999;

   return log(fabs(CombinedValue)) - log(fabs(CombinedIntegral));
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







