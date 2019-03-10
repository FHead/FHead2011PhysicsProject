#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#include "TH1D.h"

#include "Code/DrawRandom.h"
#include "CommandLine.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
double GiveMeGenPT(double k, double min, double max);
double GiveMeSigma(double PT, double C0, double C1, double C2);
void Symmetrize(vector<double> &V);
double GetMean(vector<double> &V);
double GetRMS(vector<double> &V, double Mean);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   int Tries = CL.GetInt("tries", 1000000);
   double k = CL.GetDouble("k", 2);
   double Min = CL.GetDouble("min", 50);
   double Max = CL.GetDouble("max", 300);
   string OutputFileName = CL.Get("output", "ToyResult.pdf");
   double C0 = CL.GetDouble("c0", 0.00155);
   double C1 = CL.GetDouble("c1", 0.08802);
   double C2 = CL.GetDouble("c2", 13.41);
   double BinMin = CL.GetDouble("binmin", 100);
   double BinMax = CL.GetDouble("binmax", 120);
   double Exclude = CL.GetDouble("exclude", 0.015);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Toy perfect dijet studies for JER");

   vector<string> Inputs(10);
   Inputs[0] = Form("Gen jet spectrum = PT^%.3f", k);
   Inputs[1] = Form("Gen jet range = %.1f - %.1f", Min, Max);
   Inputs[2] = Form("True variance = (%.4f + %.4f / PT + %.4f / PT^2)", C0, C1, C2);
   Inputs[3] = Form("AvePT bin range: %.2f - %.2f", BinMin, BinMax);
   Inputs[4] = Form("Tail exclusion percentage: %.2f%%", Exclude * 100);
   PdfFile.AddTextPage(Inputs);

   double RangeMin = Min - (Max - Min) * 0.05;
   double RangeMax = Max + (Max - Min) * 0.05;
   double BinRangeMin = BinMin - (BinMax - BinMin) * 2;
   double BinRangeMax = BinMax + (BinMax - BinMin) * 2;

   TH1D HGenPT("HGenPT", "Gen Jet PT Spectrum;Gen PT;#", 1000, RangeMin, RangeMax);
   TH1D HRecoPT("HRecoPT", "Reco Jet PT Spectrum;Reco PT;#", 1000, RangeMin, RangeMax);
   TH1D HRecoPT1("HRecoPT1", "Reco Jet1 PT Spectrum;Reco PT;#", 1000, RangeMin, RangeMax);
   TH1D HRecoPT2("HRecoPT2", "Reco Jet2 PT Spectrum;Reco PT;#", 1000, RangeMin, RangeMax);
   TH1D HRecoPT1Selected("HRecoPT1Selected", "Reco Jet1 PT Spectrum (selected);Reco PT;#", 1000, BinRangeMin, BinRangeMax);
   TH1D HRecoPT2Selected("HRecoPT2Selected", "Reco Jet2 PT Spectrum (selected);Reco PT;#", 1000, BinRangeMin, BinRangeMax);
   TH1D HAsymmetry("HAsymmetry", "Asymmetry;A;#", 1000, 0, 0.2);
   TH1D HAsymmetryCut("HAsymmetryCut", "Asymmetry after tail cut;A;#", 1000, 0, 0.2);

   vector<double> As;

   for(int iT = 0; iT < Tries; iT++)
   {
      double GenPT = GiveMeGenPT(k, Min, Max);

      HGenPT.Fill(GenPT);

      double RecoPT1 = GenPT * DrawGaussian(1, GiveMeSigma(GenPT, C0, C1, C2));
      double RecoPT2 = GenPT * DrawGaussian(1, GiveMeSigma(GenPT, C0, C1, C2));

      if(RecoPT1 < RecoPT2)
         swap(RecoPT1, RecoPT2);

      HRecoPT.Fill(RecoPT1);
      HRecoPT.Fill(RecoPT2);
      HRecoPT1.Fill(RecoPT1);
      HRecoPT2.Fill(RecoPT2);

      if(RecoPT1 + RecoPT2 < BinMin * 2 || RecoPT1 + RecoPT2 > BinMax * 2)
         continue;

      HRecoPT1Selected.Fill(RecoPT1);
      HRecoPT2Selected.Fill(RecoPT2);

      double A = (RecoPT1 - RecoPT2) / (RecoPT1 + RecoPT2);
      HAsymmetry.Fill(A);
      As.push_back(A);
   }

   sort(As.begin(), As.end());
   As.erase(As.begin() + int(As.size() * (1 - Exclude)), As.end());
   for(int i = 0; i < (int)As.size(); i++)
      HAsymmetryCut.Fill(As[i]);

   PdfFile.AddPlot(HGenPT);
   PdfFile.AddPlot(HGenPT, "", true);
   PdfFile.AddPlot(HRecoPT, "", true);
   PdfFile.AddPlot(HRecoPT1, "", true);
   PdfFile.AddPlot(HRecoPT2, "", true);
   PdfFile.AddPlot(HRecoPT1Selected, "", true);
   PdfFile.AddPlot(HRecoPT2Selected, "", true);
   PdfFile.AddPlot(HAsymmetry, "", true);
   PdfFile.AddPlot(HAsymmetryCut, "", true);

   HAsymmetryCut.Fit("gaus");
   
   PdfFile.AddPlot(HAsymmetryCut, "", true);
   
   vector<double> SAs = As;
   Symmetrize(SAs);

   double RMS = GetRMS(As, GetMean(As));
   double SymmetrizedRMS = GetRMS(SAs, GetMean(SAs));

   vector<string> SummaryInfo(10);
   SummaryInfo[0] = "Inputs:";
   SummaryInfo[1] = Form("Resolution at Gen PT %.0f = %.4f", BinMin, GiveMeSigma(BinMin, C0, C1, C2));
   SummaryInfo[2] = Form("Resolution at Gen PT %.0f = %.4f", BinMax, GiveMeSigma(BinMax, C0, C1, C2));
   SummaryInfo[3] = "";
   SummaryInfo[4] = "Results:";
   SummaryInfo[5] = Form("RMS of the asymmetry = %.4f", RMS);
   SummaryInfo[6] = Form("RMS of the two-sided asymmetry = %.4f", SymmetrizedRMS);
   SummaryInfo[7] = Form("Estimated resolution = %.4f", SymmetrizedRMS * sqrt(2));

   PdfFile.AddTextPage(SummaryInfo);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double GiveMeGenPT(double k, double min, double max)
{
   // Following http://mathworld.wolfram.com/RandomNumber.html
   return pow((pow(max, -k + 1) - pow(min, -k + 1)) * DrawRandom(0, 1) + pow(min, -k + 1), 1 / (-k + 1));
}

double GiveMeSigma(double PT, double C0, double C1, double C2)
{
   return sqrt(C0 + C1 / PT + C2 / PT / PT);
}

void Symmetrize(vector<double> &V)
{
   for(int i = 0; i < (int)V.size(); i++)
      if(i % 2 == 0)
         V[i] = -V[i];
}

double GetMean(vector<double> &V)
{
   double X = 0;
   int N = 0;

   for(int i = 0; i < (int)V.size(); i++)
   {
      X = X + V[i];
      N = N + 1;
   }

   return X / N;
}

double GetRMS(vector<double> &V, double Mean)
{
   double XX = 0;
   double X = 0;
   int N = 0;

   for(int i = 0; i < (int)V.size(); i++)
   {
      XX = XX + V[i] * V[i];
      X = X + V[i];
      N = N + 1;
   }

   return sqrt((XX - Mean * Mean * N) / (N - 1));
}




