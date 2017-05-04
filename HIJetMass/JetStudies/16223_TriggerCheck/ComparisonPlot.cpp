#include <iostream>
using namespace std;

#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "SetStyle.h"
#include "ProgressBar.h"

int main();
void DoComparison(PdfFileHelper &PdfFile, double PTMin, double PTMax, double CentralityMin, double CentralityMax);
void FillHistogram(TChain &T, TH1D &H0, TH1D &H7, TH1D &HZG0, TH1D &HZG7,
   double PTMin, double PTMax, double CentralityMin, double CentralityMax);
void NormalizeHistogram(TH1D &H);
void ComparisonPlot(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, bool UpperRight);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Jet100Jet80Comparison.pdf");
   PdfFile.AddTextPage("Difference between Jet100 and Jet80");

   DoComparison(PdfFile, 140, 160, 0.0, 0.1);
   DoComparison(PdfFile, 140, 160, 0.1, 0.3);
   DoComparison(PdfFile, 140, 160, 0.3, 0.5);
   DoComparison(PdfFile, 140, 160, 0.5, 0.8);
   DoComparison(PdfFile, 160, 180, 0.0, 0.1);
   DoComparison(PdfFile, 160, 180, 0.1, 0.3);
   DoComparison(PdfFile, 160, 180, 0.3, 0.5);
   DoComparison(PdfFile, 160, 180, 0.5, 0.8);
   DoComparison(PdfFile, 180, 200, 0.0, 0.1);
   DoComparison(PdfFile, 180, 200, 0.1, 0.3);
   DoComparison(PdfFile, 180, 200, 0.3, 0.5);
   DoComparison(PdfFile, 180, 200, 0.5, 0.8);
   DoComparison(PdfFile, 200, 300, 0.0, 0.1);
   DoComparison(PdfFile, 200, 300, 0.1, 0.3);
   DoComparison(PdfFile, 200, 300, 0.3, 0.5);
   DoComparison(PdfFile, 200, 300, 0.5, 0.8);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void FillHistogram(TChain &T, TH1D &H0, TH1D &H7, TH1D &HZG0, TH1D &HZG7,
   double PTMin, double PTMax, double CentralityMin, double CentralityMax)
{
   double PT, Eta, Centrality, DR;
   double SD0, DR0, SD7, DR7;
   double J10, J20, J17, J27;

   T.SetBranchAddress("MatchPT", &PT);
   T.SetBranchAddress("JetEta", &Eta);
   T.SetBranchAddress("Centrality", &Centrality);
   T.SetBranchAddress("MatchDR", &DR);
   T.SetBranchAddress("SDMass0", &SD0);
   T.SetBranchAddress("SubJetDR0", &DR0);
   T.SetBranchAddress("SDMass7", &SD7);
   T.SetBranchAddress("SubJetDR7", &DR7);
   T.SetBranchAddress("SubJet1PT0", &J10);
   T.SetBranchAddress("SubJet2PT0", &J20);
   T.SetBranchAddress("SubJet1PT7", &J17);
   T.SetBranchAddress("SubJet2PT7", &J27);

   int EntryCount = T.GetEntries();

   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(3);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      T.GetEntry(iE);

      double ZG0 = min(J10, J20) / (J10 + J20);
      double ZG7 = min(J17, J27) / (J17 + J27);

      if(EntryCount < 200 || (iE % (EntryCount / 200) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }

      if(Centrality > CentralityMax || Centrality < CentralityMin)
         continue;

      if(Eta < -1.3 || Eta > 1.3)
         continue;
      if(PT < PTMin || PT > PTMax)
         continue;
      if(DR > 0.1)
         continue;

      if(DR0 > 0.1)
         H0.Fill(SD0 / PT);
      if(DR7 > 0.1)
         H7.Fill(SD7 / PT);

      if(DR0 > 0.1)
         HZG0.Fill(ZG0);
      if(DR7 > 0.1)
         HZG7.Fill(ZG7);
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();
}

void DoComparison(PdfFileHelper &PdfFile, double PTMin, double PTMax, double CentralityMin, double CentralityMax)
{
   PdfFile.AddTextPage(Form("PT = %.0f-%.0f, Centrality = %.2f-%.2f", PTMin, PTMax, CentralityMin, CentralityMax));

   TChain T1("T");
   TChain T2("T");

   T1.AddFile("AAData/AAData.root");
   T2.AddFile("AADataPrescale/AADataPrescale.root");

   TH1D H01("H01",     "(0.1, 0.0), Jet100;Mass/PT;", 20, 0.0, 0.26);
   TH1D H02("H02",     "(0.1, 0.0), Jet80;Mass/PT;",  20, 0.0, 0.26);
   TH1D H71("H71",     "(0.5, 1.5), Jet100;Mass/PT;", 20, 0.0, 0.26);
   TH1D H72("H72",     "(0.5, 1.5), Jet80;Mass/PT;",  20, 0.0, 0.26);
   TH1D HZG01("HZG01", "(0.1, 0.0), Jet100;ZG;",      20, 0.0, 0.50);
   TH1D HZG02("HZG02", "(0.1, 0.0), Jet80;ZG;",       20, 0.0, 0.50);
   TH1D HZG71("HZG71", "(0.5, 1.5), Jet100;ZG;",      20, 0.0, 0.50);
   TH1D HZG72("HZG72", "(0.5, 1.5), Jet80;ZG;",       20, 0.0, 0.50);

   H01.Sumw2();
   H02.Sumw2();
   H71.Sumw2();
   H72.Sumw2();
   HZG01.Sumw2();
   HZG02.Sumw2();
   HZG71.Sumw2();
   HZG72.Sumw2();

   FillHistogram(T1, H01, H71, HZG01, HZG71, PTMin, PTMax, CentralityMin, CentralityMax);
   FillHistogram(T2, H02, H72, HZG02, HZG72, PTMin, PTMax, CentralityMin, CentralityMax);

   PdfFile.AddTextPage("Individual plots");

   PdfFile.AddPlot(H01);
   PdfFile.AddPlot(H02);
   PdfFile.AddPlot(H71);
   PdfFile.AddPlot(H72);
   PdfFile.AddPlot(HZG01);
   PdfFile.AddPlot(HZG02);
   PdfFile.AddPlot(HZG71);
   PdfFile.AddPlot(HZG72);

   PdfFile.AddTextPage("Comparison plots");

   ComparisonPlot(PdfFile, H01, H02, false);
   ComparisonPlot(PdfFile, H71, H72, true);
   ComparisonPlot(PdfFile, HZG01, HZG02, true);
   ComparisonPlot(PdfFile, HZG71, HZG72, true);
}

void NormalizeHistogram(TH1D &H)
{
   int BinCount = H.GetNbinsX();
   double BinSize = (H.GetXaxis()->GetBinUpEdge(BinCount) - H.GetXaxis()->GetBinLowEdge(1)) / BinCount;
   H.Scale(1 / H.Integral() / BinSize);
}

void ComparisonPlot(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, bool UpperRight)
{
   NormalizeHistogram(H1);
   NormalizeHistogram(H2);

   H1.SetLineColor(kBlue);
   H2.SetLineColor(kRed);
   H1.SetMarkerColor(kBlue);
   H2.SetMarkerColor(kRed);

   H1.SetStats(0);
   H2.SetStats(0);

   H1.SetTitle("");
   H2.SetTitle("");

   TCanvas C;
   H1.Draw();
   H2.Draw("same");

   double L = 0.4, R = 0.7, T = 0.6, B = 0.4;
   if(UpperRight == true)
      L = 0.5, R = 0.8, T = 0.8, B = 0.6;

   TLegend Legend(L, T, R, B);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&H1, "Jet 100", "pl");
   Legend.AddEntry(&H2, "Jet 80", "pl");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   TGraph G;
   G.SetPoint(0, -10000, 1);
   G.SetPoint(1, 10000, 1);

   H1.Divide(&H2);

   H1.SetMinimum(0);
   H1.SetMaximum(2);

   H1.Draw();
   G.Draw("l");

   H1.SetTitle("");
   H1.GetYaxis()->SetTitle("#frac{Jet100}{Jet80}");

   PdfFile.AddCanvas(C);
}


