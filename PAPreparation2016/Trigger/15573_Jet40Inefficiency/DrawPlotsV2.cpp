#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"

int main();
void ExportCurve(TFile &File, vector<string> H1, vector<string> H2, vector<string> Label,
   string OutputBase, bool IsCSV = false);
pair<double, double> BinomialRange(int x, int N);
pair<double, double> BinomialRange2(int x, int N);
double LogBinomial(int x, int N, double r);
double IntBinomial(int x, int N, double r);
double JntBinomial(int x, int N, double r);
double LogFactorial(int N);

int main()
{
   SetThesisStyle();

   // cout << JntBinomial(5, 10, 0.4) << endl;

   TFile File("Output.root");

   string CaloJetBestCSVPassed[3] = {"HCaloJetBestCSV_Passed40", "HCaloJetBestCSV_Passed60", "HCaloJetBestCSV_Passed80"};
   string CaloJetBestCSVAll[3] = {"HCaloJetBestCSV_All40", "HCaloJetBestCSV_All60", "HCaloJetBestCSV_All80"};
   string CaloJetBestPTPassed[3] = {"HCaloJetBestPT_Passed40", "HCaloJetBestPT_Passed60", "HCaloJetBestPT_Passed80"};
   string CaloJetBestPTAll[3] = {"HCaloJetBestPT_All", "HCaloJetBestPT_All", "HCaloJetBestPT_All"};
   string CaloJetNames[3] = {"HLT_PAAK4CaloJetCSV40_v1", "HLT_PAAK4CaloJetCSV60_v1", "HLT_PAAK4CaloJetCSV80_v1"};
   string PFJetBestCSVPassed[3] = {"HPFJetBestCSV_Passed40", "HPFJetBestCSV_Passed60", "HPFJetBestCSV_Passed80"};
   string PFJetBestCSVAll[3] = {"HPFJetBestCSV_All40", "HPFJetBestCSV_All60", "HPFJetBestCSV_All80"};
   string PFJetBestPTPassed[3] = {"HPFJetBestPT_Passed40", "HPFJetBestPT_Passed60", "HPFJetBestPT_Passed80"};
   string PFJetBestPTAll[3] = {"HPFJetBestPT_All", "HPFJetBestPT_All", "HPFJetBestPT_All"};
   string PFJetNames[3] = {"HLT_PAAK4PFJetCSV40_v1", "HLT_PAAK4PFJetCSV60_v1", "HLT_PAAK4PFJetCSV80_v1"};

   ExportCurve(File, vector<string>(CaloJetBestCSVAll, CaloJetBestCSVAll + 3),
      vector<string>(CaloJetBestCSVPassed, CaloJetBestCSVPassed + 3),
      vector<string>(CaloJetNames, CaloJetNames + 3),
      "Plots/CaloJetCSV",
      true);
   ExportCurve(File, vector<string>(CaloJetBestPTAll, CaloJetBestPTAll + 3),
      vector<string>(CaloJetBestPTPassed, CaloJetBestPTPassed + 3),
      vector<string>(CaloJetNames, CaloJetNames + 3),
      "Plots/CaloJetPT",
      false);
   ExportCurve(File, vector<string>(PFJetBestCSVAll, PFJetBestCSVAll + 3),
      vector<string>(PFJetBestCSVPassed, PFJetBestCSVPassed + 3),
      vector<string>(PFJetNames, PFJetNames + 3),
      "Plots/PFJetCSV",
      true);
   ExportCurve(File, vector<string>(PFJetBestPTAll, PFJetBestPTAll + 3),
      vector<string>(PFJetBestPTPassed, PFJetBestPTPassed + 3),
      vector<string>(PFJetNames, PFJetNames + 3),
      "Plots/PFJetPT",
      false);

   return 0;
}

void ExportCurve(TFile &File, vector<string> H1Name, vector<string> H2Name, vector<string> Names,
   string OutputBase, bool IsCSV)
{
   TCanvas C;

   int N = H1Name.size();
   if(H1Name.size() != H2Name.size())
      return;
   if(H1Name.size() != Names.size())
      return;

   vector<TH1D *> H1(N);
   vector<TH1D *> H2(N);
   vector<TGraphAsymmErrors> G(N);

   for(int i = 0; i < N; i++)
   {
      H1[i] = (TH1D *)File.Get(H1Name[i].c_str());
      H2[i] = (TH1D *)File.Get(H2Name[i].c_str());

      if(H1[i] == NULL || H2[i] == NULL)
      {
         cerr << "[ExportCurve] Histogram " << H1Name[i] << " or " << H2Name[i] << " not found!" << endl;
         return;
      }

      H1[i] = (TH1D *)H1[i]->Clone(Form("H1%d", i));
      H2[i] = (TH1D *)H2[i]->Clone(Form("H2%d", i));
      
      H1[i]->SetStats(0);
      H2[i]->SetStats(0);

      H1[i]->SetMinimum(0);

      H2[i]->SetLineColor(kRed);
   
      H1[i]->Rebin(5);
      H2[i]->Rebin(5);

      for(int j = 1; j <= H1[i]->GetNbinsX(); j++)
      {
         double x = H2[i]->GetBinContent(j);
         double N = H1[i]->GetBinContent(j);

         pair<double, double> Range = BinomialRange2((int)x, (int)N);

         G[i].SetPoint(j - 1, H1[i]->GetXaxis()->GetBinCenter(j), x / N);
         G[i].SetPointError(j - 1, 0, 0, x / N - Range.first, Range.second - x / N);
      }
   }

   TH2D *HWorld;
   if(IsCSV == true)
      HWorld = new TH2D("HWorld", ";CSV;Efficiency", 100, 0, 1, 100, 0, 1.5);
   else
      HWorld = new TH2D("HWorld", ";Jet PT;Efficiency", 100, 0, 150, 100, 0, 1.5);
   HWorld->SetStats(0);
   HWorld->Draw();

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, 1000, 1);
   GLine.Draw("l");

   TLegend Legend(0.15, 0.65, 0.5, 0.85);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int i = 0; i < N; i++)
      Legend.AddEntry(&G[i], Names[i].c_str(), "pl");
   Legend.Draw();

   int Colors[3] = {kBlack, kRed, kBlue};

   for(int i = 0; i < N; i++)
   {
      G[i].SetLineColor(Colors[i]);
      G[i].SetMarkerColor(Colors[i]);
      G[i].SetMarkerStyle(11);
      G[i].SetMarkerSize(2);
      
      G[i].Draw("p");
   }

   C.SaveAs(Form("%s_TurnOn.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOn.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOn.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOn.pdf", OutputBase.c_str()));

   delete HWorld;

   for(int i = 0; i < N; i++)
   {
      delete H1[i];
      delete H2[i];
   }
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

      double Check = JntBinomial(x, N, Range.second) - JntBinomial(x, N, Range.first);
      if(Check < 0.90 * Max)   // Range too small, lower height
         LogHeightR = LogHeightC;
      else
         LogHeightL = LogHeightC;
   }
      
   // cout << x << " " << N << " "
   //    << Range.first << " " << Range.second << " " << JntBinomial(x, N, Range.first) / Max
   //    << " " << JntBinomial(x, N, Range.second) / Max << endl;

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
   // This calculates C(N,x) * \int r^x (1-r)^(N-x) dr using a recursion relationship

   if(r == 0)
      return 0;

   if(x == 0)
      return (1 - pow(1 - r, N + 1)) / (N + 1);

   double LogExtraTerm = x * log(r) + (N - x + 1) * log(1 - r);
   LogExtraTerm = LogExtraTerm + LogFactorial(N);
   LogExtraTerm = LogExtraTerm - LogFactorial(x);
   LogExtraTerm = LogExtraTerm - LogFactorial(N - x + 1);

   if(r == 1)   // there is no extra term when r = 1
      return JntBinomial(x - 1, N, r);

   return JntBinomial(x - 1, N, r) - exp(LogExtraTerm);
}

double LogFactorial(int N)
{
   static double Result[100000] = {0};

   if(N == 0)   // log(0) = 0
      return 0;
   if(N == 1)   // log(1) = 0
      return 0;

   if(Result[N] == 0)
   {
      double Answer = LogFactorial(N - 1) + log(N);
      Result[N] = Answer;
      return Answer;
   }

   return Result[N];
}


