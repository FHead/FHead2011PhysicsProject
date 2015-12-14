#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH3D.h"
#include "TH2D.h"
#include "TEllipse.h"

#include "PlotHelper2.h"
#include "ProgressBar.h"
#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[]);
double GetLikelihood(double LL1, double LL3R, double LL3I, double LL13R, double LL13I, double LL3R3I,
   double I1, double I3R, double I3I, double I13R, double I13I, double I3R3I,
   double A1, double A3R, double A3I);
void SynthesizeHistogram(TH2D &H);
void SynthesizeHistogram(TH1D &H);

int main(int argc, char *argv[])
{
   SetStyle();

   srand(time(NULL));

   // Input parameters
   string FileName = "Samples/hzzTree_id8125.root";
   string DirectoryName = "zz4lTree";
   string TreeName = "probe_tree";

   // Output parameters
   string OutputFileName = "Likelihoods";
   int A1ZZBins = 100, A3RZZBins = 100, A3IZZBins = 100;
   double A1ZZMin = -2, A3RZZMin = -20, A3IZZMin = -20;
   double A1ZZMax = 2, A3RZZMax = 20, A3IZZMax = 20;

   // Other parameters
   double SearchTolerance = 3e-4;
   int DatasetSize = 40;
   bool WriteLikelihoodPlot = false;

   if(argc > 1)
      DatasetSize = atoi(argv[1]);

   // Our glorious histogram(s) and output files
   TFile OutputFile(Form("%s_%d.root", OutputFileName.c_str(), DatasetSize), "RECREATE");

   TH2D HCenter1(Form("HCenter1_%d", DatasetSize), "Center!",
      A3RZZBins, A3RZZMin, A3RZZMax, A3IZZBins, A3IZZMin, A3IZZMax);
   TH2D HCenter2(Form("HCenter2_%d", DatasetSize), "Center!",
      A3RZZBins, A3RZZMin / 4, A3RZZMax / 4, A3IZZBins, A3IZZMin / 4, A3IZZMax / 4);
   TH2D HCenter4(Form("HCenter4_%d", DatasetSize), "Center!", 100, -PI / 2, PI / 2, 100, -PI / 2, PI / 2);

   PsFileHelper PsFile(Form("Log_%s_%d.ps", OutputFileName.c_str(), DatasetSize));
   PsFile.AddTextPage("Meow!");
   int WrittenOut = 0;

   // Initialize stuff
   TFile InputFile(FileName.c_str());
   TDirectoryFile *Directory = (TDirectoryFile *)InputFile.Get(DirectoryName.c_str());
   TTree *Tree = (TTree *)Directory->Get(TreeName.c_str());

   Tree->SetBranchStatus("*", false);

   Tree->SetBranchStatus("Likelihood_ExtSig1", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3", true);
   Tree->SetBranchStatus("Likelihood_ExtSig4", true);
   Tree->SetBranchStatus("Likelihood_ExtSig13", true);
   Tree->SetBranchStatus("Likelihood_ExtSig14", true);
   Tree->SetBranchStatus("Likelihood_ExtSig34", true);
   Tree->SetBranchStatus("Likelihood_ExtSig1_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig4_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig13_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig14_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig34_Integral", true);

   double L1, L3R, L3I, L13R, L13I, L3R3I;
   double I1, I3R, I3I, I13R, I13I, I3R3I;
   Tree->SetBranchAddress("Likelihood_ExtSig1", &L1);
   Tree->SetBranchAddress("Likelihood_ExtSig3", &L3R);
   Tree->SetBranchAddress("Likelihood_ExtSig4", &L3I);
   Tree->SetBranchAddress("Likelihood_ExtSig13", &L13R);
   Tree->SetBranchAddress("LikelihoodNew_ExtSig14", &L13I);
   Tree->SetBranchAddress("LikelihoodNew_ExtSig34", &L3R3I);
   Tree->SetBranchAddress("Likelihood_ExtSig1_Integral", &I1);
   Tree->SetBranchAddress("Likelihood_ExtSig3_Integral", &I3R);
   Tree->SetBranchAddress("Likelihood_ExtSig4_Integral", &I3I);
   Tree->SetBranchAddress("Likelihood_ExtSig13_Integral", &I13R);
   Tree->SetBranchAddress("LikelihoodNew_ExtSig14_Integral", &I13I);
   Tree->SetBranchAddress("LikelihoodNew_ExtSig34_Integral", &I3R3I);
   
   ProgressBar Bar(cout, Tree->GetEntries() * 2);
   Bar.SetStyle(1);

   vector<double> VL1(DatasetSize), VL3R(DatasetSize), VL3I(DatasetSize),
      VL13R(DatasetSize), VL13I(DatasetSize), VL3R3I(DatasetSize);

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
   vector<double> TL1(Indices.size()), TL3R(Indices.size()), TL3I(Indices.size()),
      TL13R(Indices.size()), TL13I(Indices.size()), TL3R3I(Indices.size());
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
      TL3R[iEntry] = L3R;
      TL3I[iEntry] = L3I;
      TL13R[iEntry] = L13R;
      TL13I[iEntry] = L13I;
      TL3R3I[iEntry] = L3R3I;
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
      VL3R[Index] = TL3R[Indices[iEntry]];
      VL3I[Index] = TL3I[Indices[iEntry]];
      VL13R[Index] = TL13R[Indices[iEntry]];
      VL13I[Index] = TL13I[Indices[iEntry]];
      VL3R3I[Index] = TL3R3I[Indices[iEntry]];

      if((iEntry + 1) % DatasetSize != 0)
         continue;

      TH2D HLikelihoodScan("HLikelihoodScan", "Likelihood scan;real(A3);imag(A3)",
         A3RZZBins, A3RZZMin, A3RZZMax, A3IZZBins, A3IZZMin, A3IZZMax);

      for(int x = 1; x <= HLikelihoodScan.GetNbinsX(); x++)
      {
         for(int y = 1; y <= HLikelihoodScan.GetNbinsY(); y++)
         {
            double TotalLikelihood = 0;

            double A1 = 1;
            double A3R = HLikelihoodScan.GetXaxis()->GetBinCenter(x);
            double A3I = HLikelihoodScan.GetYaxis()->GetBinCenter(y);
            
            for(int i = 0; i < DatasetSize; i++)
            {
               double Likelihood = GetLikelihood(VL1[i], VL3R[i], VL3I[i], VL13R[i], VL13I[i], VL3R3I[i],
                  I1, I3R, I3I, I13R, I13I, I3R3I, A1, A3R, A3I);

               TotalLikelihood = TotalLikelihood + Likelihood;
            }

            HLikelihoodScan.SetBinContent(x, y, TotalLikelihood);
         }
      }

      HLikelihoodScan.Scale(-1);
      SynthesizeHistogram(HLikelihoodScan);

      if(WrittenOut < 200 && WriteLikelihoodPlot == true)
      {
         HLikelihoodScan.SetStats(0);

         TEllipse HalfwayContour(0, 0, 5.1);
         HalfwayContour.SetLineWidth(3);
         HalfwayContour.SetLineStyle(kDashed);
         HalfwayContour.SetFillStyle(0);

         TCanvas Canvas;
   
         HLikelihoodScan.Draw("colz");
         HalfwayContour.Draw();

         PsFile.AddCanvas(Canvas);

         WrittenOut = WrittenOut + 1;
      }
      
      // Find the current minimum
      double MinX = 0, MinY = 0;
      double MinSoFar = 10000;

      for(int x = 1; x <= HLikelihoodScan.GetNbinsX(); x++)
      {
         for(int y = 1; y <= HLikelihoodScan.GetNbinsY(); y++)
         {
            if(HLikelihoodScan.GetBinContent(x, y) < MinSoFar)
            {
               MinX = x;
               MinY = y;
               MinSoFar = HLikelihoodScan.GetBinContent(x, y);
            }
         }
      }

      MinX = HLikelihoodScan.GetXaxis()->GetBinCenter(MinX);
      MinY = HLikelihoodScan.GetXaxis()->GetBinCenter(MinY);

      // Search in the same-side
      double SearchStepX = (A3RZZMax - A3RZZMin) / A3RZZBins;
      double SearchStepY = (A3IZZMax - A3IZZMin) / A3IZZBins;

      double CenterX = MinX, CenterY = MinY, CenterBest = 0;
      for(int i = 0; i < DatasetSize; i++)
         CenterBest = CenterBest + GetLikelihood(VL1[i], VL3R[i], VL3I[i], VL13R[i], VL13I[i], VL3R3I[i],
            I1, I3R, I3I, I13R, I13I, I3R3I, 1, CenterX, CenterY);

      while(SearchStepX > SearchTolerance || SearchStepY > SearchTolerance)
      {
         double TempX = CenterX, TempY = CenterY, TempBest = CenterBest;

         for(double x = -1; x <= 1; x = x + 0.5)
         {
            for(double y = -1; y <= 1; y = y + 0.5)
            {
               if(x == 0 && y == 0)
                  continue;

               double Temp = 0;
               for(int i = 0; i < DatasetSize; i++)
                  Temp = Temp + GetLikelihood(VL1[i], VL3R[i], VL3I[i], VL13R[i], VL13I[i], VL3R3I[i],
                     I1, I3R, I3I, I13R, I13I, I3R3I, 1, CenterX + SearchStepX * x, CenterY + SearchStepY * y);

               if(Temp > TempBest)
               {
                  TempX = CenterX + SearchStepX * x;
                  TempY = CenterY + SearchStepY * y;
                  TempBest = Temp;
               }
            }
         }

         CenterX = TempX;
         CenterY = TempY;
         CenterBest = TempBest;

         SearchStepX = SearchStepX / 2;
         SearchStepY = SearchStepY / 2;
      }

      MinX = CenterX;
      MinY = CenterY;
      double MaxSoFar = CenterBest;
      
      // Search in the opposite side
      SearchStepX = (A3RZZMax - A3RZZMin) / A3RZZBins;
      SearchStepY = (A3IZZMax - A3IZZMin) / A3IZZBins;

      CenterX = MinX, CenterY = -MinY, CenterBest = 0;
      for(int i = 0; i < DatasetSize; i++)
         CenterBest = CenterBest + GetLikelihood(VL1[i], VL3R[i], VL3I[i], VL13R[i], VL13I[i], VL3R3I[i],
            I1, I3R, I3I, I13R, I13I, I3R3I, 1, CenterX, CenterY);

      while(SearchStepX > SearchTolerance || SearchStepY > SearchTolerance)
      {
         double TempX = CenterX, TempY = CenterY, TempBest = CenterBest;

         for(double x = -1; x <= 1; x = x + 0.5)
         {
            for(double y = -1; y <= 1; y = y + 0.5)
            {
               if(x == 0 && y == 0)
                  continue;

               double Temp = 0;
               for(int i = 0; i < DatasetSize; i++)
                  Temp = Temp + GetLikelihood(VL1[i], VL3R[i], VL3I[i], VL13R[i], VL13I[i], VL3R3I[i],
                     I1, I3R, I3I, I13R, I13I, I3R3I, 1, CenterX + SearchStepX * x, CenterY + SearchStepY * y);

               // cout << CenterX + SearchStepX * x << " " << CenterY + SearchStepY * y
               //    << " " << Temp << " " << TempBest << endl;

               if(Temp > TempBest)
               {
                  TempX = CenterX + SearchStepX * x;
                  TempY = CenterY + SearchStepY * y;
                  TempBest = Temp;
               }
            }
         }

         CenterX = TempX;
         CenterY = TempY;
         CenterBest = TempBest;

         SearchStepX = SearchStepX / 2;
         SearchStepY = SearchStepY / 2;
      } 

      if(CenterBest > MaxSoFar)
      {
         MinX = CenterX;
         MinY = CenterY;
      }

      // Now, fill final histogram
      HCenter1.Fill(MinX, MinY);
      HCenter2.Fill(MinX, MinY);
      HCenter4.Fill(atan(MinX / 5.1), atan(MinY / 5.1));
   }

   Bar.Update(EntryCount * 2);
   Bar.Print();
   Bar.PrintLine();

   InputFile.Close();

   // Write histograms
   OutputFile.cd();

   HCenter1.Write();
   HCenter2.Write();
   HCenter4.Write();

   OutputFile.Close();

   return 0;
}

double GetLikelihood(double LL1, double LL3R, double LL3I, double LL13R, double LL13I, double LL3R3I,
   double I1, double I3R, double I3I, double I13R, double I13I, double I3R3I,
   double A1, double A3R, double A3I)
{
   double CombinedIntegral = 0;
   CombinedIntegral = CombinedIntegral + I1 * A1 * A1;
   CombinedIntegral = CombinedIntegral + I3R * A3R * A3R;
   CombinedIntegral = CombinedIntegral + I3I * A3I * A3I;
   CombinedIntegral = CombinedIntegral + I13R * A1 * A3R;
   CombinedIntegral = CombinedIntegral + I13I * A1 * A3I;
   CombinedIntegral = CombinedIntegral + I3R3I * A3R * A3I;

   double CombinedValue = 0;
   CombinedValue = CombinedValue + LL1 * I1 * A1 * A1;
   CombinedValue = CombinedValue + LL3R * I3R * A3R * A3R;
   CombinedValue = CombinedValue + LL3I * I3I * A3I * A3I;
   CombinedValue = CombinedValue + LL13R * I13R * A1 * A3R;
   CombinedValue = CombinedValue + LL13I * I13I * A1 * A3I;
   CombinedValue = CombinedValue + LL3R3I * I3R3I * A3R * A3I;

   if(CombinedIntegral * CombinedValue < 0)   // error!   total is negative!
   {
      cout << LL1 * I1 * A1 * A1 << " " << LL3R * I3R * A3R * A3R
         << " " << LL3I * I3I * A3I * A3I
         << " " << LL13R * I13R * A1 * A3R
         << " " << LL13I * I13I * A1 * A3I
         << " " << LL3R3I * I3R3I * A3R * A3I << endl;
      return -999999;
   }

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







