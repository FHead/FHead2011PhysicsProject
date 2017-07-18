#include <iostream>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void ComparePlots(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title, int Bin, double Min, double Max);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("SmearTreeComparison.pdf");
   PdfFile.AddTextPage("Smear tree comparison");

   TFile F1("Pass1/PP6Dijet120.root");
   TFile F2("Smear120.root");

   TTree *T1 = (TTree *)F1.Get("OutputTree");
   TTree *T2 = (TTree *)F2.Get("OutputTree");

   ComparePlots(PdfFile, T1, T2,
      "JetPT", "abs(JetEta) < 1.3",
      "Pre-smear Jet PT;Jet PT;", 50, 0, 400);
   ComparePlots(PdfFile, T1, T2,
      "JetPT", "Centrality < 10 && abs(JetEta) < 1.3",
      "Pre-smear Jet PT (Centrality < 10%);Jet PT;", 50, 0, 400);
   ComparePlots(PdfFile, T1, T2,
      "PTHat", "",
      "PT Hat;PT Hat;", 50, 0, 400);
   ComparePlots(PdfFile, T1, T2,
      "Centrality", "",
      "Centrality;Centrality;", 50, 0, 100);
   ComparePlots(PdfFile, T1, T2,
      "BestJetPT", "Centrality < 10 && abs(BestJetEta) < 1.3",
      "Post-smear Jet PT;Jet PT;", 50, 0, 400);
   ComparePlots(PdfFile, T1, T2,
      "BestJetSDPT/BestJetPT", "Centrality < 10 && abs(BestJetEta) < 1.3",
      "Groomed PT / Jet PT (0.1, 0.0);PT Ratio;", 50, 0, 1);
   ComparePlots(PdfFile, T1, T2,
      "BestJetSDPT/BestJetPT", "Centrality < 10 && abs(BestJetEta) < 1.3 && BestJetPT > 120",
      "Groomed PT / Jet PT (0.1, 0.0), post-smear PT > 120;PT Ratio;", 50, 0, 1);
   ComparePlots(PdfFile, T1, T2,
      "BestJetDR", "Centrality < 10 && BestJetPT > 120 && abs(BestJetEta) < 1.3",
      "DR (0.1, 0.0);DR;", 25, 0, 0.5);
   ComparePlots(PdfFile, T1, T2,
      "BestJetZG", "Centrality < 10 && BestJetPT > 120 && BestJetDR > 0.1 && abs(BestJetEta) < 1.3",
      "ZG (0.1, 0.0);ZG;", 25, 0, 0.5);
   ComparePlots(PdfFile, T1, T2,
      "BestJetSDMass/BestJetPT", "Centrality < 10 && BestJetPT > 120 && BestJetDR > 0.1 && abs(BestJetEta) < 1.3",
      "Mass/PT (0.1, 0.0);Mass/PT;", 25, 0, 0.3);
   ComparePlots(PdfFile, T1, T2,
      "BestJetSDPT2/BestJetPT", "Centrality < 10 && abs(BestJetEta) < 1.3",
      "Groomed PT / Jet PT (0.5, 1.5);PT Ratio;", 50, 0, 1);
   ComparePlots(PdfFile, T1, T2,
      "BestJetDR2", "Centrality < 10 && BestJetPT > 120 && abs(BestJetEta) < 1.3",
      "DR (0.5, 1.5);DR;", 25, 0, 0.5);
   ComparePlots(PdfFile, T1, T2,
      "BestJetZG2", "Centrality < 10 && BestJetPT > 120 && BestJetDR2 > 0.1 && abs(BestJetEta) < 1.3",
      "ZG (0.5, 1.5);ZG;", 25, 0, 0.5);
   ComparePlots(PdfFile, T1, T2,
      "BestJetSDMass2/BestJetPT", "Centrality < 10 && BestJetPT > 120 && BestJetDR2 > 0.1 && abs(BestJetEta) < 1.3",
      "Mass/PT (0.5, 1.5);Mass/PT;", 25, 0, 0.3);
   ComparePlots(PdfFile, T1, T2,
      "TotalPTInJet", "Centrality < 10 && BestJetPT > 120 && abs(BestJetEta) < 1.3",
      "Added PT in jet cone;PT;", 50, 0, 400);
   ComparePlots(PdfFile, T1, T2,
      "Rho", "Centrality < 10",
      "Rho (Centrality < 10%);Rho;", 50, 50, 600);
   ComparePlots(PdfFile, T1, T2,
      "TotalStuffInJet", "abs(JetEta) < 1.3",
      "Total PF PT (pre-smear) in jet cone;PT;", 50, 0, 400);
   ComparePlots(PdfFile, T1, T2,
      "TotalStuffInJet", "Centrality < 10 && abs(JetEta) < 1.3",
      "Total PF PT (pre-smear) in jet cone (Centrality < 10%);PT;", 50, 0, 400);
   ComparePlots(PdfFile, T1, T2,
      "TotalStuffInJet", "Centrality < 10 && BestJetPT > 120 && abs(BestJetEta) < 1.3",
      "Total PF PT (pre-smear) in jet cone (Centrality < 10%, post-smear PT > 120);PT;", 50, 0, 400);
   ComparePlots(PdfFile, T1, T2,
      "TotalPT", "Centrality < 10 && BestJetPT > 120 && abs(BestJetEta) < 1.3",
      "Total added PT in operation area;PT;", 50, 0, 3500);

   F2.Close();
   F1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void ComparePlots(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title, int Bin, double Min, double Max)
{
   TH1D H1("H1", Title.c_str(), Bin, Min, Max);
   TH1D H2("H2", Title.c_str(), Bin, Min, Max);

   H1.SetStats(0);

   H1.Sumw2();
   H2.Sumw2();

   TCanvas C;

   T1->Draw(Form("%s>>H1", ToPlot.c_str()), Selection.c_str());
   T2->Draw(Form("%s>>H2", ToPlot.c_str()), Selection.c_str());

   H1.Draw();
   H2.Draw("same");

   H1.SetLineColor(kBlack);
   H1.SetMarkerColor(kBlack);
   
   H2.SetLineColor(kRed);
   H2.SetMarkerColor(kRed);

   double BinSize = (Max - Min) / Bin;
   H1.Scale(1 / H1.Integral() / BinSize);
   H2.Scale(1 / H2.Integral() / BinSize);

   H1.SetMaximum(max(H1.GetMaximum(), H2.GetMaximum()) * 1.1);

   TLegend Legend(0.3, 0.8, 0.6, 0.65);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1, "Batch-run", "lp");
   Legend.AddEntry(&H2, "Local-run", "lp");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   H1.Divide(&H2);
   H1.SetMaximum(2);

   H1.Draw();

   TGraph G;
   G.SetPoint(0, 0, 1);
   G.SetPoint(1, 100000, 1);
   G.Draw("l");

   PdfFile.AddCanvas(C);
}







