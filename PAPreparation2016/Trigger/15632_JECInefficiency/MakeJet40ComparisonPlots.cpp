#include <iostream>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   TFile F1("CurvesGT.root");
   TFile F2("CurvesJEC.root");

   TGraphAsymmErrors *G1 = (TGraphAsymmErrors *)F1.Get("G_1_0");
   TGraphAsymmErrors *G2 = (TGraphAsymmErrors *)F2.Get("G_1_0");

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";Jet PT;Efficiency", 100, 0, 150, 100, 0, 1.2);
   HWorld.SetStats(0);
   HWorld.Draw();

   TLegend Legend(0.4, 0.25, 0.8, 0.4);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(G1, "Jet 40 (original)", "l");
   Legend.AddEntry(G2, "Jet 40 (new JEC)", "l");
   Legend.Draw();

   G1->SetLineColor(kRed);
   G1->SetMarkerColor(kRed);
   G1->Draw("pl");
   G2->Draw("pl");

   Canvas.SaveAs("CaloJetComparison.png");
   Canvas.SaveAs("CaloJetComparison.C");
   Canvas.SaveAs("CaloJetComparison.eps");
   Canvas.SaveAs("CaloJetComparison.pdf");
   
   G1 = (TGraphAsymmErrors *)F1.Get("G_2_0");
   G2 = (TGraphAsymmErrors *)F2.Get("G_2_0");
   
   HWorld.Draw();

   Legend.Draw();
   
   G1->SetLineColor(kRed);
   G1->SetMarkerColor(kRed);
   G1->Draw("pl");
   G2->Draw("pl");

   Canvas.SaveAs("PFJetComparison.png");
   Canvas.SaveAs("PFJetComparison.C");
   Canvas.SaveAs("PFJetComparison.eps");
   Canvas.SaveAs("PFJetComparison.pdf");

   return 0;
}



