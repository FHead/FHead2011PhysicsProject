#include <algorithm>
#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TH2D.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"
#include "ProgressBar.h"

int main(int argc, char *argv[]);
void AppendPlot(PdfFileHelper &PdfFile, vector<vector<double>> &Sums,
   int CBin, double CMin, double CMax, string Tag, string Title);
void AppendPlot(PdfFileHelper &PdfFile, vector<vector<double>> &Sums,
   vector<double> CBin, string Tag, string Title);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output", "RandomConePlots.pdf");
   string CurvesFileName = CL.Get("curves", "Curves.root");
   double Fraction = CL.GetDouble("fraction", 1.0);

   bool DoRadius = true;
   bool DoCentralityPerEta = true;
   bool DoCentralityPerLargeEta = true;
   bool DoEta = true;

   vector<double> Radius = {0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};

   double CentralityBinWidth = 0.01;
   double CentralityMin = 0.00;
   double CentralityMax = 1.00;
   int CentralityBinCount = (CentralityMax - CentralityMin) / CentralityBinWidth;

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Random cones");

   TFile CurvesFile(CurvesFileName.c_str(), "RECREATE");

   TFile File(InputFileName.c_str());
   TTree *Tree = (TTree *)File.Get("RandomConeTree");
   if(Tree == nullptr)
      return -1;

   double Eta, Phi, Centrality;
   Tree->SetBranchAddress("Eta", &Eta);
   Tree->SetBranchAddress("Phi", &Phi);
   Tree->SetBranchAddress("Centrality", &Centrality);

   int NRho;
   double Rho[100];
   Tree->SetBranchAddress("NRho", &NRho);
   Tree->SetBranchAddress("Rho", &Rho);

   vector<double> EtaBins =
   {
      0.000, -0.087, -0.174, -0.261, -0.348, -0.435,
      -0.522, -0.609, -0.696, -0.783, -0.870,
      -0.957, -1.044, -1.131, -1.218, -1.305,
      -1.392, -1.479, -1.566, -1.653, -1.740,
      -1.830, -1.930, -2.043, -2.172, -2.322,
      -2.500, -2.650, -2.853, -3.000, -3.139,
      -3.314, -3.489, -3.664, -3.839, -4.013,
      -4.191, -4.363, -4.538, -4.716, -4.889,
      -5.191, 0.087, 0.174, 0.261, 0.348,
      0.435, 0.522, 0.609, 0.696, 0.783,
      0.870, 0.957, 1.044, 1.131, 1.218,
      1.305, 1.392, 1.479, 1.566, 1.653,
      1.740, 1.830, 1.930, 2.043, 2.172,
      2.322, 2.500, 2.650, 2.853, 3.000,
      3.139, 3.314, 3.489, 3.664, 3.839,
      4.013, 4.191, 4.363, 4.538, 4.716, 4.889, 5.191
   };
   sort(EtaBins.begin(), EtaBins.end());
   int EtaBinCount = EtaBins.size() - 1;

   if(DoCentralityPerEta)
   {
      vector<vector<vector<double>>> EtaSums(EtaBinCount);   // index: eta, centrality, event
      for(auto &v : EtaSums)
         v.resize(CentralityBinCount);

      int EntryCount = Tree->GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         if(EntryCount < 300 || iE % 200 == 0)
            Bar.Print();

         Tree->GetEntry(iE);

         int CentralityBin = (Centrality - CentralityMin) / CentralityBinWidth;
         if(CentralityBin < 0 || CentralityBin >= CentralityBinCount)
            continue;

         for(int iEta = 0; iEta < EtaBinCount && iEta < NRho; iEta++)
            EtaSums[iEta][CentralityBin].push_back(Rho[iEta]);
      }
      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      CurvesFile.cd();
      for(int iEta = 0; iEta < EtaBinCount; iEta++)
         AppendPlot(PdfFile, EtaSums[iEta], CentralityBinCount, CentralityMin * 100, CentralityMax * 100,
            Form("Eta%d", iEta),
            Form("Eta [%.03f, %.03f];Centrality (%);#rho (GeV/area)", EtaBins[iEta], EtaBins[iEta+1]));
   }

   if(DoCentralityPerLargeEta)
   {
      // The four bins are 0, 1.305, 2.500, 3.000, 5.191
      vector<vector<vector<double>>> LargeEtaSums(4);   // index: eta, centrality, event
      for(auto &v : LargeEtaSums)
         v.resize(CentralityBinCount);

      int EntryCount = Tree->GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         if(EntryCount < 300 || iE % 200 == 0)
            Bar.Print();

         Tree->GetEntry(iE);

         int CentralityBin = (Centrality - CentralityMin) / CentralityBinWidth;
         if(CentralityBin < 0 || CentralityBin >= CentralityBinCount)
            continue;

         double SumEta0 = 0;
         double SumEta1 = 0;
         double SumEta2 = 0;
         double SumEta3 = 0;

         for(int iEta = 0; iEta < EtaBinCount && iEta < NRho; iEta++)
         {
            double EtaMean = fabs((EtaBins[iEta] + EtaBins[iEta+1]) / 2);
            if(EtaMean < 1.305)        SumEta0 = SumEta0 + Rho[iEta] * (EtaBins[iEta+1] - EtaBins[iEta]);
            else if(EtaMean < 2.500)   SumEta1 = SumEta1 + Rho[iEta] * (EtaBins[iEta+1] - EtaBins[iEta]);
            else if(EtaMean < 3.000)   SumEta2 = SumEta2 + Rho[iEta] * (EtaBins[iEta+1] - EtaBins[iEta]);
            else if(EtaMean < 5.191)   SumEta3 = SumEta3 + Rho[iEta] * (EtaBins[iEta+1] - EtaBins[iEta]);
         }

         // cout << LargeEtaSums.size() << endl;
         // cout << CentralityBin << " " << LargeEtaSums[0].size() << " " << LargeEtaSums[0][0].size() << endl;

         LargeEtaSums[0][CentralityBin].push_back(SumEta0 / (1.305 - 0.000) / 2);
         LargeEtaSums[1][CentralityBin].push_back(SumEta1 / (2.500 - 1.305) / 2);
         LargeEtaSums[2][CentralityBin].push_back(SumEta2 / (3.000 - 2.500) / 2);
         LargeEtaSums[3][CentralityBin].push_back(SumEta3 / (5.191 - 3.000) / 2);
      }
      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      CurvesFile.cd();
      AppendPlot(PdfFile, LargeEtaSums[0], CentralityBinCount, CentralityMin * 100, CentralityMax * 100,
          "LargeEta0", "|Eta| [0.000, 1.305];Centrality (%);#rho (GeV/area)");
      AppendPlot(PdfFile, LargeEtaSums[1], CentralityBinCount, CentralityMin * 100, CentralityMax * 100,
          "LargeEta1", "|Eta| [1.305, 2.500];Centrality (%);#rho (GeV/area)");
      AppendPlot(PdfFile, LargeEtaSums[2], CentralityBinCount, CentralityMin * 100, CentralityMax * 100,
          "LargeEta2", "|Eta| [2.500, 3.000];Centrality (%);#rho (GeV/area)");
      AppendPlot(PdfFile, LargeEtaSums[3], CentralityBinCount, CentralityMin * 100, CentralityMax * 100,
          "LargeEta3", "|Eta| [3.000, 5.191];Centrality (%);#rho (GeV/area)");
   }

   if(DoEta)
   {
      vector<vector<double>> EtaC0Sums(EtaBinCount);   // 0-5%
      vector<vector<double>> EtaC1Sums(EtaBinCount);   // 5-10%
      vector<vector<double>> EtaC2Sums(EtaBinCount);   // 10-20%
      vector<vector<double>> EtaC3Sums(EtaBinCount);   // 20-30%
      vector<vector<double>> EtaC4Sums(EtaBinCount);   // 30-40%
      vector<vector<double>> EtaC5Sums(EtaBinCount);   // 40-50%
      vector<vector<double>> EtaC6Sums(EtaBinCount);   // 50-60%
      vector<vector<double>> EtaC7Sums(EtaBinCount);   // 60-70%
      vector<vector<double>> EtaC8Sums(EtaBinCount);   // 70-80%

      int EntryCount = Tree->GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         if(EntryCount < 300 || iE % 200 == 0)
            Bar.Print();

         Tree->GetEntry(iE);

         int CentralityBin = (Centrality - CentralityMin) / CentralityBinWidth;
         if(CentralityBin < 0 || CentralityBin >= CentralityBinCount)
            continue;

         for(int iEta = 0; iEta < EtaBinCount && iEta < NRho; iEta++)
         {
            if(Centrality < 0.05)        EtaC0Sums[iEta].push_back(Rho[iEta]);
            else if(Centrality < 0.10)   EtaC1Sums[iEta].push_back(Rho[iEta]);
            else if(Centrality < 0.20)   EtaC2Sums[iEta].push_back(Rho[iEta]);
            else if(Centrality < 0.30)   EtaC3Sums[iEta].push_back(Rho[iEta]);
            else if(Centrality < 0.40)   EtaC4Sums[iEta].push_back(Rho[iEta]);
            else if(Centrality < 0.50)   EtaC5Sums[iEta].push_back(Rho[iEta]);
            else if(Centrality < 0.60)   EtaC6Sums[iEta].push_back(Rho[iEta]);
            else if(Centrality < 0.70)   EtaC7Sums[iEta].push_back(Rho[iEta]);
            else if(Centrality < 0.80)   EtaC8Sums[iEta].push_back(Rho[iEta]);
         }
      }
      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      CurvesFile.cd();
      AppendPlot(PdfFile, EtaC0Sums, EtaBins, "VsEtaC0", "Centrality: 0-5%;#eta;#rho (GeV/area)");
      AppendPlot(PdfFile, EtaC1Sums, EtaBins, "VsEtaC1", "Centrality: 5-10%;#eta;#rho (GeV/area)");
      AppendPlot(PdfFile, EtaC2Sums, EtaBins, "VsEtaC2", "Centrality: 10-20%;#eta;#rho (GeV/area)");
      AppendPlot(PdfFile, EtaC3Sums, EtaBins, "VsEtaC3", "Centrality: 20-30%;#eta;#rho (GeV/area)");
      AppendPlot(PdfFile, EtaC4Sums, EtaBins, "VsEtaC4", "Centrality: 30-40%;#eta;#rho (GeV/area)");
      AppendPlot(PdfFile, EtaC5Sums, EtaBins, "VsEtaC5", "Centrality: 40-50%;#eta;#rho (GeV/area)");
      AppendPlot(PdfFile, EtaC6Sums, EtaBins, "VsEtaC6", "Centrality: 50-60%;#eta;#rho (GeV/area)");
      AppendPlot(PdfFile, EtaC7Sums, EtaBins, "VsEtaC7", "Centrality: 60-70%;#eta;#rho (GeV/area)");
      AppendPlot(PdfFile, EtaC8Sums, EtaBins, "VsEtaC8", "Centrality: 70-80%;#eta;#rho (GeV/area)");
   }

   if(DoRadius)
   {
      for(int iR = 0; iR < (int)Radius.size(); iR++)
      {
         double Sum;
         Tree->SetBranchAddress(Form("R%03dSum", (int)(Radius[iR] * 100)), &Sum);

         vector<vector<double>> Sums(CentralityBinCount);

         int EntryCount = Tree->GetEntries();
         for(int iE = 0; iE < EntryCount; iE++)
         {
            Tree->GetEntry(iE);

            int CentralityBin = (Centrality - CentralityMin) / CentralityBinWidth;
            if(CentralityBin < 0 || CentralityBin >= CentralityBinCount)
               continue;

            Sums[CentralityBin].push_back(Sum);
         }

         CurvesFile.cd();
         AppendPlot(PdfFile, Sums, CentralityBinCount, CentralityMin * 100, CentralityMax * 100,
            Form("%.02f", Radius[iR]), Form("R = %.02f;Centrality (%);Random cone p_{T} (GeV)", Radius[iR]));

         Sums.clear();
      }
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   CurvesFile.Close();

   return 0;
}

void AppendPlot(PdfFileHelper &PdfFile, vector<vector<double>> &Sums,
   int CBin, double CMin, double CMax, string Tag, string Title)
{
   vector<double> CBins(CBin + 1);
   for(int i = 0; i <= CBin; i++)
      CBins[i] = (CMax - CMin) / CBin * i + CMin;
   AppendPlot(PdfFile, Sums, CBins, Tag, Title);
}

void AppendPlot(PdfFileHelper &PdfFile, vector<vector<double>> &Sums,
   vector<double> CBin, string Tag, string Title)
{
   sort(CBin.begin(), CBin.end());

   TGraphAsymmErrors G50, G68, G95, GMean, GRMS, G68Dist, G95Dist;

   double Max95 = 0;
   double Max95Dist = 0;

   int NCBin = CBin.size() - 1;
   for(int iC = 0; iC < NCBin; iC++)
   {
      if(Sums[iC].size() < 100)
         continue;

      sort(Sums[iC].begin(), Sums[iC].end());

      double Median = Sums[iC][Sums[iC].size()*0.5000];
      double Up68   = Sums[iC][Sums[iC].size()*0.8425];
      double Down68 = Sums[iC][Sums[iC].size()*0.1575];
      double Up95   = Sums[iC][Sums[iC].size()*0.9750];
      double Down95 = Sums[iC][Sums[iC].size()*0.0250];

      double Total = 0, Total2 = 0;
      for(int iS = 0; iS < (int)Sums[iC].size(); iS++)
      {
         Total = Total + Sums[iC][iS];
         Total2 = Total2 + Sums[iC][iS] * Sums[iC][iS];
      }
      int Count = Sums[iC].size();
      double SMean = Total / Count;
      double SRMS = sqrt((Total2 - Total * Total / Count) / Count);

      if(Up95 > Max95)
         Max95 = Up95;
      if(Up95 - Down95 > Max95Dist)
         Max95Dist = Up95 - Down95;

      double CLow   = CBin[iC];
      double CHigh  = CBin[iC+1];
      double CMean  = (CLow + CHigh) / 2;
      double CWidth = CHigh - CLow;

      int N = GMean.GetN();
      GMean.SetPoint(N, CMean, SMean);
      GRMS.SetPoint(N, CMean, SRMS);
      G50.SetPoint(N, CMean, Median);
      G68.SetPoint(N, CMean, Median);
      G68.SetPointError(N, CWidth * 0.5, CWidth * 0.5, Median - Down68, Up68 - Median);
      G95.SetPoint(N, CMean, Median);
      G95.SetPointError(N, CWidth * 0.5, CWidth * 0.5, Median - Down95, Up95 - Median);
      G68Dist.SetPoint(N, CMean, Up68 - Down68);
      G95Dist.SetPoint(N, CMean, Up95 - Down95);
   }

   if(GMean.GetN() < 5)
      return;

   G68.SetFillColor(kAzure);
   G95.SetFillColor(kCyan);
   G50.SetLineColor(kBlack);
   G68.SetLineColor(kBlack);
   G95.SetLineColor(kBlack);
   GMean.SetLineColor(kRed);
   GMean.SetLineStyle(kDashed);
   GMean.SetLineWidth(2);
   
   G68Dist.SetLineColor(kAzure);
   G95Dist.SetLineColor(kBlack);
   G68Dist.SetLineWidth(2);
   G95Dist.SetLineWidth(2);
   GRMS.SetLineColor(kRed);
   GRMS.SetLineStyle(kDashed);
   GRMS.SetLineWidth(2);

   TLegend Legend(0.55, 0.85, 0.80, 0.70);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillColor(kWhite);
   Legend.AddEntry(&G68, "68%", "lf");
   Legend.AddEntry(&G95, "95%", "lf");
   Legend.AddEntry(&GMean, "Mean", "lf");

   TH2D HWorld("HWorld", Title.c_str(),
      100, CBin.front(), CBin.back(), 100, 0, Max95 * 1.10);
   HWorld.SetStats(0);

   TH2D HWorldLog("HWorldLog", Title.c_str(),
      100, CBin.front(), CBin.back(), 100, 0.5, Max95 * 2);
   HWorldLog.SetStats(0);

   TCanvas Canvas;
   Canvas.SetGridx();
   Canvas.SetGridy();

   HWorld.Draw("axis");
   G95.Draw("3");
   G68.Draw("3");
   G50.Draw("l");
   GMean.Draw("l");
   HWorld.Draw("axis same");

   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   HWorldLog.Draw("axis");
   G95.Draw("3");
   G68.Draw("3");
   G50.Draw("l");
   GMean.Draw("l");
   HWorldLog.Draw("axis same");

   Legend.Draw();

   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   
   TLegend Legend2(0.55, 0.85, 0.80, 0.70);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetFillColor(kWhite);
   Legend2.AddEntry(&G68Dist, "68% range", "lf");
   Legend2.AddEntry(&G95Dist, "95% range", "lf");
   Legend2.AddEntry(&GRMS, "RMS", "lf");

   TH2D HWorld3("HWorld3", Title.c_str(), 100, CBin.front(), CBin.back(), 100, 0, Max95Dist * 1.2);
   HWorld3.SetStats(0);
   HWorld3.GetYaxis()->SetTitle(Form("Fluctuation: %s", HWorld3.GetYaxis()->GetTitle()));

   HWorld3.Draw("axis");
   GRMS.Draw("l");
   G68Dist.Draw("l");
   G95Dist.Draw("l");

   Legend2.Draw();

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   G95.SetName(Form("G95_%s", Tag.c_str()));
   G68.SetName(Form("G68_%s", Tag.c_str()));
   G50.SetName(Form("G50_%s", Tag.c_str()));
   GMean.SetName(Form("GMean_%s", Tag.c_str()));
   G95Dist.SetName(Form("G95Dist_%s", Tag.c_str()));
   G68Dist.SetName(Form("G68Dist_%s", Tag.c_str()));
   GRMS.SetName(Form("GRMS_%s", Tag.c_str()));

   G95.Write();
   G68.Write();
   G50.Write();
   GMean.Write();
   G95Dist.Write();
   G68Dist.Write();
   GRMS.Write();
}





