#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
using namespace std;

#include "TF1.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"

#include "Code/DrawRandom.h"
#include "PlotHelper2.h"

int main();
double CalculateSpread(vector<double> &Values, int Size);
pair<double, double> EstimateRMSError(int Count);

int main()
{
   srand(time(NULL));

   // Initialize inputs
   int ColumnCount = 16;
   string ColumnNames[] = {"Background", "A1", "A2R", "A2I", "A3R", "A3I", "A1-A2R", "A1-A2I",
      "A1-A3R", "A1-A3I", "A2R-A2I", "A2R-A3R", "A2R-A3I", "A2I-A3R", "A2I-A3I", "A3R-A3I"};
   string FileName = "ProcessedEvents";

   // Mark the ones we want to calculate
   vector<int> Sizes;
   for(int i = 1000; i <= 100000; i = i * 10)
      for(int j = 1; j <= 9; j++)
         Sizes.push_back(i * j);
   Sizes.push_back(1000000);

   // Declare histogram vectors
   vector<TH1D *> HIntegrals;
   vector<TGraphAsymmErrors *> HSpreads;

   // Histogram settings
   int Colors[] = {1, 4, 2, 3, 7, 6, 40, 41, 42, 36, 30, 31, 33, 38, 20, 29};

   // Actually do the works
   for(int Column = 1; Column <= ColumnCount; Column++)
   {
      // First let's declare the plots
      HIntegrals.push_back(new TH1D(Form("H%dIntegral", Column),
         Form("Integral for component %s", ColumnNames[Column-1].c_str()), ColumnCount, 0, ColumnCount));

      HSpreads.push_back(new TGraphAsymmErrors);
      HSpreads[Column-1]->SetNameTitle(Form("H%dSpread", Column),
         Form("Spread vs. sample size for component %s", ColumnNames[Column-1].c_str()));

      // Reserve a huge array
      vector<double> Values;
      Values.reserve(2000000);

      // Read from file and calculate average along the way
      double Mean = 0;

      ifstream in(FileName.c_str());
      while(in)
      {
         char ch[10240] = "";
         in.getline(ch, 10239, '\n');

         double Temp = 0;

         stringstream str(ch);
         for(int i = 0; i < Column - 1; i++)
            str >> Temp;
         str >> Temp;
         Values.push_back(Temp);

         Mean = Mean + Temp;
      }
      in.close();

      Mean = Mean / Values.size();
      HIntegrals[Column-1]->SetBinContent(Column, fabs(Mean));

      // Now we're in a position to calculate the spread
      for(int i = 0; i < (int)Sizes.size(); i++)
      {
         double Spread = CalculateSpread(Values, Sizes[i]);
         cout << Column << " " << Sizes[i] << " " << Mean << " " << Spread << endl;

         if(Spread > 0)
         {
            HSpreads[Column-1]->SetPoint(i, Sizes[i], Spread);
            pair<double, double> RMSError = EstimateRMSError(Values.size() / Sizes[i]);
            HSpreads[Column-1]->SetPointError(i, 0, 0, Spread * RMSError.first, Spread * RMSError.second);
         }
      }
   }

   // Start the plotting section
   PsFileHelper PsFile("SpreadSummary.ps");
   PsFile.AddTextPage("Study the amount of samples needed to do integral");

   // Add the first plot!  Summary of integrals
   {
      TH1D HWorld("HWorld", "Summary of abs(integrals)", ColumnCount, 0, ColumnCount);

      for(int i = 1; i <= ColumnCount; i++)
         HWorld.GetXaxis()->SetBinLabel(i, ColumnNames[i-1].c_str());
      HWorld.SetStats(0);

      double MaxMean = 0;
      for(int i = 1; i <= ColumnCount; i++)
         if(MaxMean < HIntegrals[i-1]->GetBinContent(i))
            MaxMean = HIntegrals[i-1]->GetBinContent(i);
      HWorld.SetMaximum(MaxMean * 10);
      HWorld.SetMinimum(MaxMean / 100000);

      TCanvas C;
      HWorld.Draw();

      for(int i = 1; i <= ColumnCount; i++)
      {
         HIntegrals[i-1]->SetFillColor(Colors[i-1]);
         HIntegrals[i-1]->Draw("same");
      }

      C.SetLogy();

      PsFile.AddCanvas(C);
   }
      
   // Now, one by one RMS/|Mean| vs. sample size - fill projection histograms along the way
   TH1D H1M("H1M", "Projection to 1M events", ColumnCount, 0, ColumnCount);
   TH1D H10M("H10M", "Projection to 10M events", ColumnCount, 0, ColumnCount);
   TH1D H100M("H100M", "Projection to 100M events", ColumnCount, 0, ColumnCount);

   for(int i = 1; i <= ColumnCount; i++)
   {
      gStyle->SetOptFit(1111);

      HSpreads[i-1]->SetMarkerStyle(20);
      HSpreads[i-1]->SetMarkerColor(Colors[i-1]);

      double FirstX, FirstY;
      HSpreads[i-1]->GetPoint(0, FirstX, FirstY);

      TF1 F("F", "[0]*x^[1]");
      F.SetParameter(0, FirstX * 30);   // initial parameters
      F.SetParameter(1, -0.5);
      HSpreads[i-1]->Fit(&F);

      TCanvas C;
      HSpreads[i-1]->Draw("ap");
      HSpreads[i-1]->GetXaxis()->SetTitle("Number of samples");
      HSpreads[i-1]->GetYaxis()->SetTitle("RMS / |Mean|");

      H1M.SetBinContent(i, F.Eval(1000000) * HIntegrals[i-1]->GetBinContent(i));
      H10M.SetBinContent(i, F.Eval(10000000) * HIntegrals[i-1]->GetBinContent(i));
      H100M.SetBinContent(i, F.Eval(100000000) * HIntegrals[i-1]->GetBinContent(i));

      C.Update();
      C.SetLogx();
      C.SetLogy();
      C.SetGridx();
      C.SetGridy();

      PsFile.AddCanvas(C);
   }

   // Integral vs. projection to 1e6 and 1e7 and 1e8
   {
      TH1D HWorld("HWorld", "Summary of abs(integrals)", ColumnCount, 0, ColumnCount);

      for(int i = 1; i <= ColumnCount; i++)
         HWorld.GetXaxis()->SetBinLabel(i, ColumnNames[i-1].c_str());
      HWorld.SetStats(0);

      double MaxMean = 0;
      for(int i = 1; i <= ColumnCount; i++)
         if(MaxMean < HIntegrals[i-1]->GetBinContent(i))
            MaxMean = HIntegrals[i-1]->GetBinContent(i);
      HWorld.SetMaximum(MaxMean * 10);
      HWorld.SetMinimum(MaxMean / 1000000);

      TCanvas C;
      HWorld.Draw();

      for(int i = 1; i <= ColumnCount; i++)
      {
         HIntegrals[i-1]->SetFillColor(Colors[i-1]);
         HIntegrals[i-1]->Draw("same");
      }

      H1M.SetLineWidth(2);
      H10M.SetLineWidth(2);
      H100M.SetLineWidth(2);
      H1M.SetLineColor(kRed + 2);
      H10M.SetLineColor(kRed + 2);
      H100M.SetLineColor(kRed + 2);
      H1M.SetLineStyle(2);
      H10M.SetLineStyle(7);
      H100M.SetLineStyle(10);
      
      H1M.Draw("same");
      H10M.Draw("same");
      H100M.Draw("same");

      TLegend Legend(0.45, 0.85, 0.85, 0.65);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.SetTextFont(42);
      Legend.AddEntry(&H1M, "Expected spread at 10^{6} events", "l");
      Legend.AddEntry(&H10M, "Expected spread at 10^{7} events", "l");
      Legend.AddEntry(&H100M, "Expected spread at 10^{8} events", "l");
      Legend.Draw();

      C.SetLogy();

      PsFile.AddCanvas(C);
   }

   // Close files
   PsFile.AddTimeStampPage();
   PsFile.Close();

   // Clean-up
   for(int i = 0; i < ColumnCount; i++)
   {
      if(HIntegrals[i] != NULL)   delete HIntegrals[i];
      if(HSpreads[i] != NULL)     delete HSpreads[i];
   }

   return 0;
}

double CalculateSpread(vector<double> &Values, int Size)
{
   // Shuffle the samples to reduce potential weird correlations between different sizes
   random_shuffle(Values.begin(), Values.end());

   vector<double> Array(Size);
   vector<double> MeanValues;

   int NumberCount = Values.size();
   for(int i = 0; i < NumberCount; i++)
   {
      Array[i%Size] = Values[i];

      if((i + 1) % Size != 0)
         continue;

      double Sum = 0;
      for(int j = 0; j < Size; j++)
         Sum = Sum + Array[j];

      MeanValues.push_back(Sum / Size);
   }

   if(MeanValues.size() < 5)
      return -1;

   int DatasetCount = MeanValues.size();

   double Sum = 0;
   double Sum2 = 0;
   for(int i = 0; i < DatasetCount; i++)
   {
      Sum = Sum + MeanValues[i];
      Sum2 = Sum2 + MeanValues[i] * MeanValues[i];
   }

   return sqrt(Sum2 / DatasetCount - Sum * Sum / DatasetCount / DatasetCount) / fabs(Sum / DatasetCount);
}

pair<double, double> EstimateRMSError(int Count)
{
   int NumberOfTries = 1000;
   vector<double> RMSs(NumberOfTries);

   for(int i = 0; i < NumberOfTries; i++)
   {
      double Sum = 0;
      double Sum2 = 0;

      for(int j = 0; j < Count; j++)
      {
         double Sample = DrawGaussian(0, 1);
         Sum = Sum + Sample;
         Sum2 = Sum2 + Sample * Sample;
      }

      double Mean = Sum / Count;
      double RMS = sqrt(Sum2 / Count - Mean * Mean);

      RMSs[i] = RMS;
   }

   sort(RMSs.begin(), RMSs.end());

   double LowPercentage = 0.1538;
   double HighPercentage = 0.8462;

   return pair<double, double>(fabs(RMSs[NumberOfTries*LowPercentage] - 1), fabs(RMSs[NumberOfTries*HighPercentage] - 1));
}


