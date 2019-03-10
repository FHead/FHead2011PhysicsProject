#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void AddPlot(PdfFileHelper &PdfFile,
   TTree *T1, string ToPlot1, string Cut1, TTree *T2, string ToPlot2, string Cut2,
   string Title, int N, double Min, double Max);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("QuickPlot.pdf");
   PdfFile.AddTextPage("Comparison: mixed and embedded samples");

   TFile File1("ScaledResult/PP6Dijet.root");
   TFile File2("../16731_CSPlainTree/ScaledResult/AA6DijetCymbalV2.root");

   TTree *T1 = (TTree *)File1.Get("OutputTree");
   TTree *T2 = (TTree *)File2.Get("T");

   T1->SetAlias("CWeight", "(6.88866-21.0648*Centrality+24.4310*Centrality*Centrality)");

   AddPlot(PdfFile, T1, "BestJetPT", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3)",
      T2, "JetCSRawPT", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3)",
      ";Raw PT;", 50, 180, 1500);
   AddPlot(PdfFile, T1, "BestJetPT", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "JetCSRawPT", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%;Raw PT;", 50, 180, 1500);
   AddPlot(PdfFile, T1, "PTHat", "MCWeight * (abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "PTHat", "MCWeight * (abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      ";PTHat;", 50, 0, 800);
   AddPlot(PdfFile, T1, "PTHat", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "PTHat", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%;PTHat;", 50, 0, 800);
   AddPlot(PdfFile, T1, "PTHat", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1) * CWeight",
      T2, "PTHat", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%, Centrality Weighted;PTHat;", 50, 0, 800);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%;DR (z = 0.1);", 50, -1.5, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%;DR (z = 0.1);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%;DR (z = 0.1);", 40, 0.1, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "SubJetDR0", "MCWeight * (MatchPT > 180 && abs(JetEta) < 1.3 && Centrality < 0.1)",
      "0-10%;DR (z = 0.1);", 40, 0.1, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.8 && Centrality > 0.5)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.8 && Centrality > 0.5)",
      "50-80%;DR (z = 0.1);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.8 && Centrality > 0.5)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.8 && Centrality > 0.5)",
      "50-80%;DR (z = 0.1);", 40, 0.1, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.8 && Centrality > 0.5)",
      T2, "SubJetDR0", "MCWeight * (MatchPT > 180 && abs(JetEta) < 1.3 && Centrality < 0.8 && Centrality > 0.5)",
      "50-80%;DR (z = 0.1);", 100, -1.2, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.5 && Centrality > 0.3)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.5 && Centrality > 0.3)",
      "30-50%;DR (z = 0.1);", 40, 0.0, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.5 && Centrality > 0.3)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.5 && Centrality > 0.3)",
      "30-50%;DR (z = 0.1);", 35, 0.1, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.5 && Centrality > 0.3)",
      T2, "SubJetDR0", "MCWeight * (MatchPT > 180 && abs(JetEta) < 1.3 && Centrality < 0.5 && Centrality > 0.3)",
      "30-50%;DR (z = 0.1);", 80, -1.2, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1 && PTHat > 300)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1 && PTHat > 300)",
      "0-10%, PTHat > 300;DR (z = 0.1);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1 && PTHat > 300) * CWeight",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1 && PTHat > 300)",
      "0-10%, PTHat > 300, Centrality weighted;DR (z = 0.1);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.05 && PTHat > 250)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.05 && PTHat > 250)",
      "0-5%, PTHat > 250;DR (z = 0.1);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "BestJetDR", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1 && PTHat < 250)",
      T2, "SubJetDR0", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1 && PTHat < 250)",
      "0-10%, PTHat < 250;DR (z = 0.1);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "BestJetSJ2PT/BestJetSJ1PT", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1 && BestJetDR > 0.1)",
      T2, "(SubJet2PT0/SubJet1PT0)", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1 && SubJetDR0 > 0.1)",
      "0-10%, DR > 0.1;PT2/PT1 (z = 0.1);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "BestJetSDMass/BestJetPT", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "SDMass0/JetCSRawPT", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%;Mass/PT (z = 0.1);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "BestJetSDMass/BestJetPT", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1 && BestJetDR > 0.1)",
      T2, "SDMass0/JetCSRawPT", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1 && SubJetDR0 > 0.1)",
      "0-10%, DR > 0.1;Mass/PT (z = 0.1);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "SubJetDRs[0]", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "SubJetDRs[0]", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%;DR (z = 0.2);", 50, -1.5, 0.5);
   AddPlot(PdfFile, T1, "SubJetDRs[0]", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "SubJetDRs[0]", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%;DR (z = 0.2);", 50, 0.0, 0.5);
   AddPlot(PdfFile, T1, "SubJetDRs[0]", "MCWeight * (BestJetPT > 180 && abs(BestJetEta) < 1.3 && Centrality < 0.1)",
      T2, "SubJetDRs[0]", "MCWeight * (JetCSRawPT > 180 && abs(JetCSEta) < 1.3 && Centrality < 0.1)",
      "0-10%;DR (z = 0.2);", 40, 0.1, 0.5);

   File2.Close();
   File1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile,
   TTree *T1, string ToPlot1, string Cut1, TTree *T2, string ToPlot2, string Cut2,
   string Title, int N, double Min, double Max)
{
   TCanvas C;

   TH1D H1("H1", Title.c_str(), N, Min, Max);
   TH1D H2("H2", Title.c_str(), N, Min, Max);

   T1->Draw((ToPlot1 + ">>H1").c_str(), Cut1.c_str());
   T2->Draw((ToPlot2 + ">>H2").c_str(), Cut2.c_str());

   H1.SetStats(0);
   H2.SetStats(0);

   double BinSize = (Max - Min) / N;
   H1.Scale(1 / H1.Integral() / BinSize);
   H2.Scale(1 / H2.Integral() / BinSize);

   H1.SetMarkerColor(kRed);
   H1.SetLineColor(kRed);
   H2.SetMarkerColor(kBlue);
   H2.SetLineColor(kBlue);

   H1.Draw();
   H2.Draw("same");

   PdfFile.AddCanvas(C);

   C.SetLogy();

   H1.Draw();
   H2.Draw("same");

   PdfFile.AddCanvas(C);

   H1.Divide(&H2);

   H1.Draw();
   H1.GetYaxis()->SetTitle("Ratio: smeared pp / PbPb");
   H1.SetMinimum(0);
   H1.SetMaximum(2);

   TGraph G;
   G.SetPoint(0, -1000, 1);
   G.SetPoint(1, +1000, 1);
   G.Draw("l");

   C.SetLogy(false);

   PdfFile.AddCanvas(C);
}



