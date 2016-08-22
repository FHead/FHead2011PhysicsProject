#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("FigureMGraphs.root");

   TGraphAsymmErrors *G1 = (TGraphAsymmErrors *)File.Get("ERR_Both_J_N");
   TGraphAsymmErrors *G2 = (TGraphAsymmErrors *)File.Get("ERR_Both_J_Y");
   TGraphAsymmErrors *G3 = (TGraphAsymmErrors *)File.Get("ERR_Both_A_N");

   // for(int i = 0; i < (int)G1->GetN(); i++)
   // {
   //    G1->SetPointError(i, 0, 0, G1->GetErrorYhigh(i), G1->GetErrorYlow(i));
   //    G2->SetPointError(i, 0, 0, G2->GetErrorYhigh(i), G2->GetErrorYlow(i));
   //    G3->SetPointError(i, 0, 0, G3->GetErrorYhigh(i), G3->GetErrorYlow(i));
   // }

   G1->SetLineWidth(4);
   G2->SetLineWidth(3);
   G3->SetLineWidth(2);

   G1->SetLineColor(9);
   G2->SetLineColor(30);
   G3->SetLineColor(46);

   G1->SetMarkerColor(9);
   G2->SetMarkerColor(30);
   G3->SetMarkerColor(46);

   G1->SetMarkerStyle(6);
   G2->SetMarkerStyle(6);
   G3->SetMarkerStyle(6);

   G1->Set(8);
   G2->Set(8);
   G3->Set(8);

   TCanvas C;

   TH2D HWorld("HWorld", ";Integrated Luminosity (fb^{-1});Model separation p-value", 100, 25 * 0.8, 3200 / 0.8, 100, 0.001, 1);
   HWorld.SetStats(0);

   HWorld.Draw();
   G1->Draw("pl");
   G2->Draw("pl");
   G3->Draw("pl");

   TGraph GLine;
   GLine.SetPoint(0, 0, 0.05);
   GLine.SetPoint(1, 10000000, 0.05);
   GLine.SetLineStyle(kDashed);
   GLine.Draw("l");

   TLegend Legend(0.15, 0.45, 0.55, 0.20);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.AddEntry(G1, "Loose cut, y_{t} integrated", "l");
   Legend.AddEntry(G2, "Loose cut, y_{t} fixed", "l");
   Legend.AddEntry(G3, "Run I CMS-like cut, y_{t} integrated", "l");
   Legend.Draw();

   C.SetLogx();
   C.SetLogy();

   C.SaveAs("Plots/FigureO.png");
   C.SaveAs("Plots/FigureO.C");
   C.SaveAs("Plots/FigureO.eps");
   C.SaveAs("Plots/FigureO.pdf");

   File.Close();

   return 0;
}




