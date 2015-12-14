#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH3D.h"
#include "TH2D.h"

#include "ProgressBar.h"

int main(int argc, char *argv[]);
double GetLikelihood(double LL1, double LL2, double LL3, double LL12, double LL13, double LL23,
   double I1, double I2, double I3, double I12, double I23, double I13,
   double A1, double A2, double A3);
void SynthesizeHistogram(TH2D &H);
void SynthesizeHistogram(TH1D &H);

int main(int argc, char *argv[])
{
   // Input parameters
   string FileName = "Samples/hzzTree_id1125.root";
   string DirectoryName = "zz4lTree";
   string TreeName = "probe_tree";
   int IndexStart = 1200;
   int IndexEnd = IndexStart + 40;

   // Output parameters
   string OutputFileName = "Likelihoods.root";
   int A1ZZBins = 100, A2ZZBins = 100, A3ZZBins = 100;
   double A1ZZMin = -2, A2ZZMin = -2, A3ZZMin = -5;
   double A1ZZMax = 2, A2ZZMax = 2, A3ZZMax = 5;

   // Our glorious histogram(s) and output files
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH3D HLogLikelihood("HLogLikelihood", "Log likelihood for each parameter in space;A1ZZ;A2ZZ;A3ZZ",
      A1ZZBins, A1ZZMin, A1ZZMax, A2ZZBins, A2ZZMin, A2ZZMax, A3ZZBins, A3ZZMin, A3ZZMax);
   TH2D HLogLikelihood_UnitA1("HLogLikelihood_UnitA1",
      "Log likelihood for each parameter in space;A2ZZ/A1ZZ;A3ZZ/A1ZZ",
      A2ZZBins, A2ZZMin, A2ZZMax, A3ZZBins, A3ZZMin, A3ZZMax);
   TH2D HLogLikelihood_ZeroA2("HLogLikelihood_ZeroA2", "Log likelihood for each parameter in space;A1ZZ;A3ZZ",
      A1ZZBins, A1ZZMin, A1ZZMax, A3ZZBins, A3ZZMin, A3ZZMax);
   TH2D HLogLikelihood_ZeroA3("HLogLikelihood_ZeroA3", "Log likelihood for each parameter in space;A1ZZ;A2ZZ",
      A1ZZBins, A1ZZMin, A1ZZMax, A2ZZBins, A2ZZMin, A2ZZMax);
   TH1D HA3Scan_UnitA1("HA3Scan_UnitA1", ";A3ZZ/A1ZZ", A3ZZBins * 10, A3ZZMin, A3ZZMax);

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
   
   ProgressBar Bar(cout, IndexEnd, IndexStart);
   Bar.SetStyle(1);

   // Loop over things and fill in the log likelihood histogram
   int EntryCount = Tree->GetEntries();
   for(int iEntry = IndexStart; iEntry < IndexEnd && iEntry < EntryCount; iEntry++)
   {
      Tree->GetEntry(iEntry);

      Bar.Update(iEntry);
      Bar.Print();

      /*
      for(int i1 = 0; i1 < A1ZZBins; i1++)
      {
         for(int i2 = 0; i2 < A2ZZBins; i2++)
         {
            for(int i3 = 0; i3 < A3ZZBins; i3++)
            {
               double A1 = (A1ZZMax - A1ZZMin) * (i1 + 0.5) / A1ZZBins + A1ZZMin;
               double A2 = (A2ZZMax - A2ZZMin) * (i2 + 0.5) / A2ZZBins + A2ZZMin;
               double A3 = (A3ZZMax - A3ZZMin) * (i3 + 0.5) / A3ZZBins + A3ZZMin;
   
               double FinalLikelihood = GetLikelihood(L1, L2, L3, L12, L13, L23,
                  I1, I2, I3, I12, I23, I13, A1, A2, A3);

               double ValueSoFar = HLogLikelihood.GetBinContent(i1 + 1, i2 + 1, i3 + 1);
               HLogLikelihood.SetBinContent(i1 + 1, i2 + 1, i3 + 1, ValueSoFar + FinalLikelihood);
            }
         }
      }
      */
      
      for(int i2 = 0; i2 < A2ZZBins; i2++)
      {
         for(int i3 = 0; i3 < A3ZZBins; i3++)
         {
            double A1 = 1;
            double A2 = (A2ZZMax - A2ZZMin) * (i2 + 0.5) / A2ZZBins + A2ZZMin;
            double A3 = (A3ZZMax - A3ZZMin) * (i3 + 0.5) / A3ZZBins + A3ZZMin;

            double FinalLikelihood = GetLikelihood(L1, L2, L3, L12, L13, L23,
               I1, I2, I3, I12, I23, I13, A1, A2, A3);

            double ValueSoFar = HLogLikelihood_UnitA1.GetBinContent(i2 + 1, i3 + 1);
            HLogLikelihood_UnitA1.SetBinContent(i2 + 1, i3 + 1, ValueSoFar + FinalLikelihood);
         }
      }
       
      for(int i1 = 0; i1 < A1ZZBins; i1++)
      {
         for(int i2 = 0; i2 < A2ZZBins; i2++)
         {
            double A1 = (A1ZZMax - A1ZZMin) * (i1 + 0.5) / A1ZZBins + A1ZZMin;
            double A2 = (A2ZZMax - A2ZZMin) * (i2 + 0.5) / A2ZZBins + A2ZZMin;
            double A3 = 0;

            double FinalLikelihood = GetLikelihood(L1, L2, L3, L12, L13, L23,
               I1, I2, I3, I12, I23, I13, A1, A2, A3);

            double ValueSoFar = HLogLikelihood_ZeroA3.GetBinContent(i1 + 1, i2 + 1);
            HLogLikelihood_ZeroA3.SetBinContent(i1 + 1, i2 + 1, ValueSoFar + FinalLikelihood);
         }
      }
      
      for(int i1 = 0; i1 < A1ZZBins; i1++)
      {
         for(int i3 = 0; i3 < A3ZZBins; i3++)
         {
            double A1 = (A1ZZMax - A1ZZMin) * (i1 + 0.5) / A1ZZBins + A1ZZMin;
            double A2 = 0;
            double A3 = (A3ZZMax - A3ZZMin) * (i3 + 0.5) / A3ZZBins + A3ZZMin;

            double FinalLikelihood = GetLikelihood(L1, L2, L3, L12, L13, L23,
               I1, I2, I3, I12, I23, I13, A1, A2, A3);

            double ValueSoFar = HLogLikelihood_ZeroA2.GetBinContent(i1 + 1, i3 + 1);
            HLogLikelihood_ZeroA2.SetBinContent(i1 + 1, i3 + 1, ValueSoFar + FinalLikelihood);
         }
      }

      for(int i3 = 0; i3 < A3ZZBins * 10; i3++)
      {
         double A1 = 1;
         double A2 = 0;
         double A3 = (A3ZZMax - A3ZZMin) * (i3 + 0.5) / A3ZZBins / 10 + A3ZZMin;
            
         double FinalLikelihood = GetLikelihood(L1, L2, L3, L12, L13, L23,
            I1, I2, I3, I12, I23, I13, A1, A2, A3);

         double ValueSoFar = HA3Scan_UnitA1.GetBinContent(i3+  1);
         HA3Scan_UnitA1.SetBinContent(i3 + 1, ValueSoFar + FinalLikelihood);
      }
   }

   Bar.Update(IndexEnd);
   Bar.Print();
   Bar.PrintLine();

   InputFile.Close();

   // Write histograms
   OutputFile.cd();

   HA3Scan_UnitA1.Scale(-1);
   HLogLikelihood_UnitA1.Scale(-1);
   HLogLikelihood_ZeroA2.Scale(-1);
   HLogLikelihood_ZeroA3.Scale(-1);

   SynthesizeHistogram(HA3Scan_UnitA1);
   SynthesizeHistogram(HLogLikelihood_UnitA1);
   SynthesizeHistogram(HLogLikelihood_ZeroA2);
   SynthesizeHistogram(HLogLikelihood_ZeroA3);

   HA3Scan_UnitA1.Write();
   HLogLikelihood.Write();
   HLogLikelihood_UnitA1.Write();
   HLogLikelihood_ZeroA2.Write();
   HLogLikelihood_ZeroA3.Write();

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







