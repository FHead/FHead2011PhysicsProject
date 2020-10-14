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

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output", "RandomConePlots.pdf");
   string CurvesFileName = CL.Get("curves", "Curves.root");

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

      TGraphAsymmErrors G50, G68, G95, GMean;

      double Max95 = 0;

      for(int iC = 0; iC < CentralityBinCount; iC++)
      {
         sort(Sums[iC].begin(), Sums[iC].end());

         double Median = Sums[iC][Sums[iC].size()*0.5000];
         double Up68   = Sums[iC][Sums[iC].size()*0.8425];
         double Down68 = Sums[iC][Sums[iC].size()*0.1575];
         double Up95   = Sums[iC][Sums[iC].size()*0.9750];
         double Down95 = Sums[iC][Sums[iC].size()*0.0250];

         double Total = 0;
         for(int iS = 0; iS < (int)Sums[iC].size(); iS++)
            Total = Total + Sums[iC][iS];
         double SMean = Total / Sums[iC].size();

         if(Up95 > Max95)
            Max95 = Up95;

         double CLow   = ((CentralityMax - CentralityMin) / CentralityBinCount * (iC + 0) + CentralityMin) * 100;
         double CHigh  = ((CentralityMax - CentralityMin) / CentralityBinCount * (iC + 1) + CentralityMin) * 100;
         double CMean  = (CLow + CHigh) / 2;
         double CWidth = CHigh - CLow;

         GMean.SetPoint(iC, CMean, SMean);
         G50.SetPoint(iC, CMean, Median);
         G68.SetPoint(iC, CMean, Median);
         G68.SetPointError(iC, CWidth * 0.5, CWidth * 0.5, Median - Down68, Up68 - Median);
         G95.SetPoint(iC, CMean, Median);
         G95.SetPointError(iC, CWidth * 0.5, CWidth * 0.5, Median - Down95, Up95 - Median);
      }

      G68.SetFillColor(kAzure);
      G95.SetFillColor(kCyan);
      G50.SetLineColor(kBlack);
      G68.SetLineColor(kBlack);
      G95.SetLineColor(kBlack);
      GMean.SetLineColor(kRed);
      GMean.SetLineStyle(kDashed);
      GMean.SetLineWidth(2);

      TLegend Legend(0.55, 0.85, 0.80, 0.70);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetFillColor(kWhite);
      Legend.AddEntry(&G68, "68%", "lf");
      Legend.AddEntry(&G95, "95%", "lf");
      Legend.AddEntry(&GMean, "Mean", "lf");

      TH2D HWorld("HWorld", Form("R = %.02f;Centrality (%);Random cone p_{T} (GeV)", Radius[iR]),
         100, CentralityMin * 100, CentralityMax * 100, 100, 0, Max95 * 1.10);
      HWorld.SetStats(0);
      
      TH2D HWorldLog("HWorldLog", Form("R = %.02f;Centrality (%);Random cone p_{T} (GeV)", Radius[iR]),
         100, CentralityMin * 100, CentralityMax * 100, 100, 0.5, Max95 * 2);
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

      G95.SetName(Form("G95_%.02f", Radius[iR]));
      G68.SetName(Form("G68_%.02f", Radius[iR]));
      G50.SetName(Form("G50_%.02f", Radius[iR]));
      GMean.SetName(Form("GMean_%.02f", Radius[iR]));

      CurvesFile.cd();

      G95.Write();
      G68.Write();
      G50.Write();
      GMean.Write();
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   CurvesFile.Close();

   return 0;
}






