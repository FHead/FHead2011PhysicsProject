#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TF1.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"

int main();
void ExportCurve(TFile &File, string H1, string H2, string OutputBase, bool IsCSV = false);
pair<double, double> BinomialRange(int x, int N);
pair<double, double> BinomialRange2(int x, int N);
double LogBinomial(int x, int N, double r);
double IntBinomial(int x, int N, double r);
double JntBinomial(int x, int N, double r);

int main()
{
   SetThesisStyle();

   cout << 10 << " " << 10 << " " << 0.5 << " " << IntBinomial(10, 10, 0.5) << " " <<
      JntBinomial(10, 10, 0.5) << endl;

   return 0;

   TFile File("Output.root");

   ExportCurve(File, "HCaloJetBestCSVV1V1_All60", "HCaloJetBestCSVV1V1_Passed60", "Plots/CaloJetCSVV1V160", true);
   ExportCurve(File, "HCaloJetBestCSVV1V1_All80", "HCaloJetBestCSVV1V1_Passed80", "Plots/CaloJetCSVV1V180", true);
   ExportCurve(File, "HCaloJetBestCSVV1V1_All100", "HCaloJetBestCSVV1V1_Passed100", "Plots/CaloJetCSVV1V1100", true);
   // ExportCurve(File, "HCaloJetBestCSVV1V2_All60", "HCaloJetBestCSVV1V2_Passed60", "Plots/CaloJetCSVV1V260", true);
   // ExportCurve(File, "HCaloJetBestCSVV1V2_All80", "HCaloJetBestCSVV1V2_Passed80", "Plots/CaloJetCSVV1V280", true);
   // ExportCurve(File, "HCaloJetBestCSVV1V2_All100", "HCaloJetBestCSVV1V2_Passed100", "Plots/CaloJetCSVV1V2100", true);
   // ExportCurve(File, "HCaloJetBestCSVV2V1_All60", "HCaloJetBestCSVV2V1_Passed60", "Plots/CaloJetCSVV2V160", true);
   // ExportCurve(File, "HCaloJetBestCSVV2V1_All80", "HCaloJetBestCSVV2V1_Passed80", "Plots/CaloJetCSVV2V180", true);
   // ExportCurve(File, "HCaloJetBestCSVV2V1_All100", "HCaloJetBestCSVV2V1_Passed100", "Plots/CaloJetCSVV2V1100", true);
   ExportCurve(File, "HCaloJetBestCSVV2V2_All60", "HCaloJetBestCSVV2V2_Passed60", "Plots/CaloJetCSVV2V260", true);
   ExportCurve(File, "HCaloJetBestCSVV2V2_All80", "HCaloJetBestCSVV2V2_Passed80", "Plots/CaloJetCSVV2V280", true);
   ExportCurve(File, "HCaloJetBestCSVV2V2_All100", "HCaloJetBestCSVV2V2_Passed100", "Plots/CaloJetCSVV2V2100", true);

   ExportCurve(File, "HPFJetBestCSV_All60", "HPFJetBestCSV_Passed60", "Plots/PFJetCSV60", true);
   ExportCurve(File, "HPFJetBestCSV_All80", "HPFJetBestCSV_Passed80", "Plots/PFJetCSV80", true);
   ExportCurve(File, "HPFJetBestCSV_All100", "HPFJetBestCSV_Passed100", "Plots/PFJetCSV100", true);
   
   ExportCurve(File, "HCaloJetBestPT_All", "HCaloJetBestPT_Passed60", "Plots/CaloJetPT60", false);
   ExportCurve(File, "HCaloJetBestPT_All", "HCaloJetBestPT_Passed80", "Plots/CaloJetPT80", false);
   ExportCurve(File, "HCaloJetBestPT_All", "HCaloJetBestPT_Passed100", "Plots/CaloJetPT100", false);
   
   ExportCurve(File, "HPFJetBestPT_All", "HPFJetBestPT_Passed60", "Plots/PFJetPT60", false);
   ExportCurve(File, "HPFJetBestPT_All", "HPFJetBestPT_Passed80", "Plots/PFJetPT80", false);
   ExportCurve(File, "HPFJetBestPT_All", "HPFJetBestPT_Passed100", "Plots/PFJetPT100", false);

   return 0;
}

void ExportCurve(TFile &File, string H1Name, string H2Name, string OutputBase, bool IsCSV)
{
   TCanvas C;

   TH1D *H1 = (TH1D *)File.Get(H1Name.c_str());
   TH1D *H2 = (TH1D *)File.Get(H2Name.c_str());

   if(H1 == NULL || H2 == NULL)
      return;

   H1->SetStats(0);
   H2->SetStats(0);

   H1->SetMinimum(0);

   H2->SetLineColor(kRed);

   H1->Draw();
   H2->Draw("same");

   C.SaveAs(Form("%s_Distribution.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_Distribution.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_Distribution.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_Distribution.pdf", OutputBase.c_str()));

   TH1D *H1C = (TH1D *)H1->Clone(Form("H1"));
   TH1D *H2C = (TH1D *)H2->Clone(Form("H2"));

   // H1C->Sumw2();
   // H2C->Sumw2();

   H1C->Rebin(10);
   H2C->Rebin(10);

   TGraphAsymmErrors G;
   
   for(int i = 1; i <= H1->GetNbinsX(); i++)
   {
      double x = H2C->GetBinContent(i);
      double N = H1C->GetBinContent(i);

      pair<double, double> Range = BinomialRange2((int)x, (int)N);

      G.SetPoint(i - 1, H1C->GetXaxis()->GetBinCenter(i), x / N);
      G.SetPointError(i - 1, 0, 0, x / N - Range.first, Range.second - x / N);
   }

   H2C->Divide(H1C);
   
   H2C->SetMarkerColor(kBlack);
   H2C->SetMarkerStyle(11);
   H2C->SetMarkerSize(2);
   
   G.SetMarkerColor(kBlack);
   G.SetMarkerStyle(11);
   G.SetMarkerSize(2);

   H2C->SetMinimum(0);
   H2C->SetMaximum(1.1);

   H2C->Draw("point");
   // H2C->Draw("error same");

   // H2C->Draw("axis");
   G.Draw("p");

   TF1 F("F", "[0]+[1]*erf((x-[2])*[3])");
   if(IsCSV == true)
   {
      F.SetParameter(0, 0.6);
      F.SetParameter(1, 0.3);
      F.SetParameter(2, 0.8);
      F.SetParameter(3, 1);
   }
   else
   {
      F.SetParameter(0, 0.6);
      F.SetParameter(1, 0.3);
      F.SetParameter(2, 50);
      F.SetParameter(3, 0.1);
   }
   H2C->Fit(&F);

   H2C->SetTitle("");

   C.SaveAs(Form("%s_TurnOn.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOn.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOn.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOn.pdf", OutputBase.c_str()));

   delete H1C;
   delete H2C;
}

pair<double, double> BinomialRange(int x, int N)
{
   pair<double, double> Result;

   double MaxR = (double)x / N;
   double MaxLogB = LogBinomial(x, N, MaxR);

   int Count = 1000;
   vector<double> R(Count);

   for(int i = 0; i < Count; i++)
   {
      bool Good = false;
      while(Good == false)
      {
         double r = DrawRandom(max(0.0001, MaxR - 1.0 / N), min(0.9999, MaxR + 1.0 / N));
         double f = LogBinomial(x, N, r);
         if(DrawRandom(0, 1) < exp(f - MaxLogB))
         {
            Good = true;
            R[i] = r;
         }
      }
   }

   sort(R.begin(), R.end());

   Result.first = R[Count*0.1585];
   Result.second = R[Count*0.8415];

   return Result;
}

pair<double, double> BinomialRange2(int x, int N)
{
   double Max = JntBinomial(x, N, 1);

   double BestR = (double)x / N;
   double LogBestHeight = x * log(BestR) + (N - x) * log(1 - BestR);
   if(x == 0)
      LogBestHeight = (N - x) * log(1 - BestR);
   if(x == N)
      LogBestHeight = x * log(BestR);

   pair<double, double> Range(0, 1);

   double LogHeightL = LogBestHeight - 20, LogHeightR = LogBestHeight;
   while(LogHeightR - LogHeightL > 1e-6)
   {
      double LogHeightC = (LogHeightL + LogHeightR) / 2;

      double L = 0, R = BestR;
      while(R - L > 1e-8)
      {
         double C = (L + R) / 2;
         double LH = x * log(C) + (N - x) * log(1 - C);
         if(LH < LogHeightC)
            L = C;
         else
            R = C;
      }
      Range.first = (L + R) / 2;

      L = BestR, R = 1;
      while(R - L > 1e-8)
      {
         double C = (L + R) / 2;
         double LH = x * log(C) + (N - x) * log(1 - C);
         if(LH >= LogHeightC)
            L = C;
         else
            R = C;
      }
      Range.second = (L + R) / 2;

      cout << x << " " << N << " "
         << Range.first << " " << Range.second << " " << JntBinomial(x, N, Range.first)
         << " " << JntBinomial(x, N, Range.second) << " " << Max << endl;

      double Check = JntBinomial(x, N, Range.second) - JntBinomial(x, N, Range.first);
      if(Check < 0.68 * Max)   // Range too small, lower height
         LogHeightR = LogHeightC;
      else
         LogHeightL = LogHeightC;
   }

   return Range;
}

double LogBinomial(int x, int N, double r)
{
   double Result = 1;

   for(int i = 1; i <= N; i++)
      Result = Result - log(i);
   for(int i = 1; i <= x; i++)
      Result = Result + log(i);
   for(int i = x + 1; i <= N; i++)
      Result = Result + log(N-i+1);

   Result = Result + x * log(r);
   Result = Result + (N - x) * log(1 - r);

   return Result;
}

double IntBinomial(int x, int N, double r)
{
   // This calculates \int r^x (1-r)^(N-x) dr using a recursion relationship

   if(r == 0)
      return 0;
   if(x == 0)
      return (1 - pow(1 - r, N + 1)) / (N + 1);
   
   return (IntBinomial(x - 1, N ,r) * x - pow(r, x) * pow(1 - r, N - x + 1)) / (N - x + 1);
}

double JntBinomial(int x, int N, double r)
{
   // This calculates (N-x+1) * \int r^x (1-r)^(N-x) dr using a recursion relationship

   if(r == 0)
      return 0;

   if(x == 0)
      return 1 - pow(1 - r, N + 1);
   
   return JntBinomial(x - 1, N ,r) * x / (N - x + 2) - pow(r, x) * pow(1 - r, N - x + 1);
}



