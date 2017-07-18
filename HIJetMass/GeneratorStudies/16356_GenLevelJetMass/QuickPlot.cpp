#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void Normalize(TH1D &H);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Meow.pdf");
   PdfFile.AddTextPage("Meow");

   TFile FG("Graphs_SD0_MC_16354AA6DijetCymbal_16354PP6Dijet.root");
   TFile FG2("Graphs_SD0_MC_16354AA6DijetCymbal_16354PassThroughPP6Dijet.root");

   TFile F1("ScaledResult/AA6DijetCymbal.root");
   TFile F2("ScaledResult/PP6Dijet.root");

   TTree *T1 = (TTree *)F1.Get("GenJetTree");
   TTree *T2 = (TTree *)F2.Get("GenJetTree");

   PdfFile.AddPlot(T1, "PTHat", "MCWeight * (abs(JetEta) < 1.3 && Centrality > 0.8)", "", "AA;PTHat;", 100, 50, 600, true);
   PdfFile.AddPlot(T2, "PTHat", "MCWeight * (abs(JetEta) < 1.3)", "", "PP;PTHat;", 100, 50, 600, true);
   
   PdfFile.AddPlot(T1, "SubJetDR0", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && Centrality > 0.8)", "", "AA;DR (SD0);", 20, 0.0, 0.5, true);
   PdfFile.AddPlot(T2, "SubJetDR0", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3)", "", "PP;DR (SD0);", 20, 0.0, 0.5, true);
   
   PdfFile.AddPlot(T1, "SDMass0/JetPT", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && SubJetDR0 > 0.1 && Centrality > 0.8)", "", "AA;Mass/PT (SD0);", 20, 0.0, 0.3, true);
   PdfFile.AddPlot(T2, "SDMass0/JetPT", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && SubJetDR0 > 0.1)", "", "PP;Mass/PT (SD0);", 20, 0.0, 0.3, true);
   
   PdfFile.AddPlot(T1, "SDMass0/JetPT", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && SubJetDR0 > 0.1 && Centrality > 0.8)", "", "AA;Mass/PT (SD0);", 20, 0.0, 0.3, false);
   PdfFile.AddPlot(T2, "SDMass0/JetPT", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && SubJetDR0 > 0.1)", "", "PP;Mass/PT (SD0);", 20, 0.0, 0.3, false);

   double BinEdge[] = {0.00, 0.04, 0.06, 0.08, 0.10, 0.12, 0.15, 0.18, 0.21, 0.26};
   TH1D H1("H1", ";Mass/PT;", 9, BinEdge);
   TH1D H2("H2", ";Mass/PT;", 9, BinEdge);

   H1.SetStats(0);

   H1.SetLineColor(kRed);
   H2.SetLineColor(kBlue);
   H1.SetMarkerColor(kRed);
   H2.SetMarkerColor(kBlue);
   
   H1.SetLineStyle(kDashed);
   H2.SetLineStyle(kDashed);
   H1.SetMarkerStyle(24);
   H2.SetMarkerStyle(24);

   T1->Draw("SDMass0/JetPT>>H1", "MCWeight * (JetPT > 140 && JetPT < 160 && abs(JetEta) < 1.3 && Centrality > 0.8 && SubJetDR0 > 0.1 && PTHat > 100)");
   T2->Draw("SDMass0/JetPT>>H2", "MCWeight * (JetPT > 140 && JetPT < 160 && abs(JetEta) < 1.3 && Centrality < 0.8 && SubJetDR0 > 0.1 && PTHat > 100)");

   Normalize(H1);
   Normalize(H2);

   TCanvas C;

   H1.SetMaximum(15);

   H1.Draw("");
   H2.Draw("same");

   TGraphAsymmErrors *GAA = (TGraphAsymmErrors *)FG.Get("MassData_4_2");
   TGraphAsymmErrors *GPP = (TGraphAsymmErrors *)FG.Get("MassSmear_4_2");
   TGraphAsymmErrors *GPP2 = (TGraphAsymmErrors *)FG2.Get("MassSmear_4_2");

   GAA->Draw("p");
   GPP->Draw("p");
   GPP2->Draw("p");

   GAA->SetLineColor(kRed);
   GPP->SetLineColor(kBlue);
   GPP2->SetLineColor(kBlack);
   GAA->SetMarkerColor(kRed);
   GPP->SetMarkerColor(kBlue);
   GPP2->SetMarkerColor(kBlack);

   TLegend Legend(0.50, 0.85, 0.80, 0.55);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   Legend.SetTextFont(42);
   Legend.AddEntry(&H1, "AA (Gen)", "pl");
   Legend.AddEntry(&H2, "PP (Gen)", "pl");
   Legend.AddEntry(GAA, "AA+CS (Reco)", "pl");
   Legend.AddEntry(GPP, "PP+MB+CS (Reco)", "pl");
   Legend.AddEntry(GPP2, "PP (Reco)", "pl");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   C.SetLogy();
   H1.SetMaximum(100);
   H1.SetMinimum(0.1);

   PdfFile.AddCanvas(C);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   F2.Close();
   F1.Close();

   FG2.Close();
   FG.Close();

   return 0;
}

void Normalize(TH1D &H)
{
   double Total = H.Integral();

   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      double Min = H.GetXaxis()->GetBinLowEdge(i);
      double Max = H.GetXaxis()->GetBinUpEdge(i);

      H.SetBinContent(i, H.GetBinContent(i) / Total / (Max - Min));
      H.SetBinError(i, H.GetBinError(i) / Total / (Max - Min));
   }
}



