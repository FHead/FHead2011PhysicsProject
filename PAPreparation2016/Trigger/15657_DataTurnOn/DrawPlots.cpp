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

int main(int argc, char *argv[]);
void ExportCurve(TFile &File, vector<string> H1, vector<string> H2, vector<string> Label,
   string OutputBase, bool DoError = true);
pair<double, double> BinomialRange(int x, int N);
pair<double, double> BinomialRange2(int x, int N);
double LogBinomial(int x, int N, double r);
double IntBinomial(int x, int N, double r);
double JntBinomial(int x, int N, double r);
double LogFactorial(int N);

int main(int argc, char *argv[])
{
   string Tag = "15624";
   
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " Tag" << endl;
      return -1;
   }

   Tag = argv[1];

   SetThesisStyle();

   TFile File(("CombinedResult/Output_" + Tag + ".root").c_str());

   TFile OutputFile(("Curves" + Tag + ".root").c_str(), "RECREATE");

   string L1JetBestPTPassed[5] = {"HPassL112CaloJets", "HPassL116CaloJets", "HPassL124CaloJets", "HPassL136CaloJets", "HPassL152CaloJets"};
   string L1JetBestPTAll[5] = {"HAllCaloJets", "HAllCaloJets", "HAllCaloJets", "HAllCaloJets", "HAllCaloJets"};
   string L1JetNames[5] = {"L1_SingleJet12_BptxAND", "L1_SingleJet16_BptxAND", "L1_SingleJet24_BptxAND", "L1_SingleJet36_BptxAND", "L1_SingleJet52_BptxAND"};
   ExportCurve(File, vector<string>(L1JetBestPTAll, L1JetBestPTAll + 5),
      vector<string>(L1JetBestPTPassed, L1JetBestPTPassed + 5),
      vector<string>(L1JetNames, L1JetNames + 5),
      "Plots/L1JetPT-" + Tag + "-", true);

   string L1FJetBestPTPassed[3] = {"HPassL112F1CaloJets", "HPassL112F2CaloJets", "HPassL124F1CaloJets"};
   string L1FJetBestPTAll[3] = {"HAllCaloJetsF1", "HAllCaloJetsF2", "HAllCaloJetsF1"};
   string L1FJetNames[3] = {"L1_SingleJet12_ForEta1p5_BptxAND", "L1_SingleJet12_ForEta2p5_BptxAND", "L1_SingleJet24_ForEta1p5_BptxAND"};
   ExportCurve(File, vector<string>(L1FJetBestPTAll, L1FJetBestPTAll + 3),
      vector<string>(L1FJetBestPTPassed, L1FJetBestPTPassed + 3),
      vector<string>(L1FJetNames, L1FJetNames + 3),
      "Plots/L1FJetPT-" + Tag + "-", true);
   
   string CaloJetBestPTPassed[4] = {"HPass40CaloJets", "HPass60CaloJets", "HPass80CaloJets", "HPass100CaloJets"};
   string CaloJetBestPTAll[4] = {"HFireL112CaloJets", "HFireL124CaloJets", "HFireL136CaloJets", "HFireL152CaloJets"};
   string CaloJetNames[4] = {"HLT_PAAK4CaloJet40", "HLT_PAAK4CaloJet60", "HLT_PAAK4CaloJet80", "HLT_PAAK4CaloJet100"};
   ExportCurve(File, vector<string>(CaloJetBestPTAll, CaloJetBestPTAll + 4),
      vector<string>(CaloJetBestPTPassed, CaloJetBestPTPassed + 4),
      vector<string>(CaloJetNames, CaloJetNames + 4),
      "Plots/CaloJetPT-" + Tag + "-", false);

   string PFJetBestPTPassed[5] = {"HPass40PFJets", "HPass60PFJets", "HPass80PFJets", "HPass100PFJets", "HPass120PFJets"};
   string PFJetBestPTAll[5] = {"HFireL112PFJets", "HFireL116PFJets", "HFireL124PFJets", "HFireL136PFJets", "HFireL152PFJets"};
   string PFJetNames[5] = {"HLT_PAAK4PFJet40", "HLT_PAAK4PFJet60", "HLT_PAAK4PFJet80", "HLT_PAAK4PFJet100", "HLT_PAAK4PFJet120"};
   ExportCurve(File, vector<string>(PFJetBestPTAll, PFJetBestPTAll + 5),
      vector<string>(PFJetBestPTPassed, PFJetBestPTPassed + 5),
      vector<string>(PFJetNames, PFJetNames + 5),
      "Plots/PFJetPT-" + Tag + "-", false);

   OutputFile.Close();

   return 0;
}

void ExportCurve(TFile &File, vector<string> H1Name, vector<string> H2Name, vector<string> Names,
   string OutputBase, bool DoError)
{
   static int Count = 0;
   Count = Count + 1;

   TCanvas C;
   C.SetGridx();
   C.SetGridy();

   int N = H1Name.size();
   if(H1Name.size() != H2Name.size())
      return;
   if(H1Name.size() != Names.size())
      return;

   vector<TH1D *> H1(N);
   vector<TH1D *> H2(N);
   vector<TGraphAsymmErrors> G(N);
   vector<TGraphAsymmErrors> G2(N);

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
   
      H1[i]->Rebin(2);
      H2[i]->Rebin(2);

      G[i].SetNameTitle(Form("G_%d_%d", Count, i), "");
      G2[i].SetNameTitle(Form("G2_%d_%d", Count, i), "");

      for(int j = 1; j <= H1[i]->GetNbinsX(); j++)
      {
         double x = H2[i]->GetBinContent(j);
         double N = H1[i]->GetBinContent(j);

         if(N > 0)
         {
            if(DoError == true)
            {
               pair<double, double> Range = BinomialRange2((int)x, (int)N);

               G[i].SetPoint(j - 1, H1[i]->GetXaxis()->GetBinCenter(j), x / N);
               G[i].SetPointError(j - 1, 0, 0, x / N - Range.first, Range.second - x / N);

               pair<double, double> Range2 = BinomialRange2((int)(N - x), (int)N);

               G2[i].SetPoint(j - 1, H1[i]->GetXaxis()->GetBinCenter(j), (N - x) / N);
               G2[i].SetPointError(j - 1, 0, 0, (N - x) / N - Range2.first, Range2.second - (N - x) / N);
            }
            else
            {
               G[i].SetPoint(j - 1, H1[i]->GetXaxis()->GetBinCenter(j), x / N);
               G2[i].SetPoint(j - 1, H1[i]->GetXaxis()->GetBinCenter(j), (N - x) / N);
            }
         }
         else
         {
            G[i].SetPoint(j - 1, H1[i]->GetXaxis()->GetBinCenter(j), -1);
            G2[i].SetPoint(j - 1, H1[i]->GetXaxis()->GetBinCenter(j), -1);
         }
      }
   }

   TH2D HWorld("HWorld", ";Jet PT;Efficiency", 100, 0, 200, 100, 0, 1.5);
   HWorld.SetStats(0);
   HWorld.Draw();

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

   int Colors[5] = {kBlack, kRed, kBlue, kYellow + 3, kCyan};

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
   
   TH2D HWorld3("HWorld3", ";Jet PT;Efficiency", 100, 0, 100, 100, 0, 1.5);
   HWorld3.SetStats(0);
   HWorld3.Draw();
   
   GLine.Draw("l");
   
   Legend.Draw();
   
   for(int i = 0; i < N; i++)
      G[i].Draw("p");

   C.SaveAs(Form("%s_TurnOnZoomed.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOnZoomed.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOnZoomed.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOnZoomed.pdf", OutputBase.c_str()));

   TH2D HWorld2("HWorld2", ";Jet PT;Inefficiency", 100, 0, 200, 100, 0.00001, 10);
   HWorld2.SetStats(0);
   HWorld2.Draw();

   TLegend Legend2(0.5, 0.65, 0.85, 0.85);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetBorderSize(0);
   Legend2.SetFillStyle(0);
   for(int i = 0; i < N; i++)
      Legend2.AddEntry(&G[i], Names[i].c_str(), "pl");
   Legend2.Draw();

   for(int i = 0; i < N; i++)
   {
      G2[i].SetLineColor(Colors[i]);
      G2[i].SetMarkerColor(Colors[i]);
      G2[i].SetMarkerStyle(11);
      G2[i].SetMarkerSize(2);
      
      G2[i].Draw("p");
   }

   C.SetLogy();

   C.SaveAs(Form("%s_Inefficiency.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_Inefficiency.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_Inefficiency.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_Inefficiency.pdf", OutputBase.c_str()));

   for(int i = 0; i < N; i++)
   {
      delete H1[i];
      delete H2[i];
   }

   for(int i = 0; i < N; i++)
   {
      G[i].Write();
      G2[i].Write();
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
   if(N > 5000)
   {
      pair<double, double> FakeRange;
      double r = (double)x / N;
      FakeRange.first = max(0.0, r - r * (1 / sqrt(max(x, 1)) + 1 / sqrt(N)));
      FakeRange.second = min(1.0, r + r * (1 / sqrt(max(x, 1)) + 1 / sqrt(N)));
      return FakeRange;
   }

   if(x > N)
   {
      return pair<double, double>(x / N, x / N);
   }

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

   if(N < 0)
   {
      cerr << "WTF! log(" << N << "!) requested!" << endl;
      return 0;
   }
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


