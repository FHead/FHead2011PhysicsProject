#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void AddPlot(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title,
   int Bin, double Min, double Max);

int main()
{
   SetThesisStyle();

   TFile F1("Samples/AA6Dijet220.root");
   TFile F2("Samples/AA6Dijet220Cymbal.root");

   TTree *T1 = (TTree *)F1.Get("T");
   TTree *T2 = (TTree *)F2.Get("T");

   PdfFileHelper PdfFile("JetPlots.pdf");
   PdfFile.AddTextPage("Jet Plots");

   AddPlot(PdfFile, T1, T2, "JetCSPT", "abs(JetEta) < 1.3 && Centrality > 0.8", "80-100%;CS Jet PT;", 30, 0, 500);
   AddPlot(PdfFile, T1, T2, "JetCSPT", "abs(JetEta) < 1.3 && Centrality < 0.1", "0-10%;CS Jet PT;", 30, 0, 500);
   AddPlot(PdfFile, T1, T2, "JetCSPT", "abs(JetEta) < 1.3 && Centrality < 0.1", "0-10%;CS Jet PT;", 30, 100, 500);
   AddPlot(PdfFile, T1, T2, "JetCSPT", "abs(JetEta) < 1.3 && Centrality < 0.1", "0-10%;CS Jet PT;", 30, 0, 100);
   AddPlot(PdfFile, T1, T2, "JetCSPT > 100", "abs(JetEta) < 1.3 && Centrality < 0.1", "0-10%;CS Jet PT > 100?;", 2, 0, 2);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   F2.Close();
   F1.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title,
   int Bin, double Min, double Max)
{
   TCanvas C;

   TH1D H1("H1", Title.c_str(), Bin, Min, Max);   H1.Sumw2();
   TH1D H2("H2", Title.c_str(), Bin, Min, Max);   H2.Sumw2();

   T1->Draw((ToPlot + ">>H1").c_str(), Selection.c_str());
   T2->Draw((ToPlot + ">>H2").c_str(), Selection.c_str());

   H1.SetStats(0);

   double BinWidth = (Max - Min) / Bin;
   H1.Scale(1 / H1.Integral() / BinWidth);
   H2.Scale(1 / H2.Integral() / BinWidth);

   H1.SetLineColor(kRed);
   H2.SetLineColor(kGreen);
   H1.SetMarkerColor(kRed);
   H2.SetMarkerColor(kGreen);

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1, "Drum", "lp");
   Legend.AddEntry(&H2, "Cymbal", "lp");

   H1.Draw();
   H2.Draw("same");
   H1.Draw("hist same");
   H2.Draw("same hist");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   H1.Divide(&H2);

   H1.GetYaxis()->SetTitle("Ratio");
   H1.Draw();
   H1.SetMinimum(0);
   H1.SetMaximum(3);

   TGraph G;
   G.SetPoint(0, Min, 1);
   G.SetPoint(1, Max, 1);
   G.Draw("l");

   PdfFile.AddCanvas(C);
}




