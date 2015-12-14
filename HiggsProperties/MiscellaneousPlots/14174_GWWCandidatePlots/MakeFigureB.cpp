#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TGraph.h"
#include "TFile.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisBigStyle();

   TFile File("AllGraphs.root");

   TGraph *G1J = (TGraph *)File.Get("Loop_LWW_Both_J_Count_NNNNYNYN_WithSquare_NNNNN_PointA");
   TGraph *G2J = (TGraph *)File.Get("Loop_LWW_Both_J_Count_NNNYYNYN_WithSquare_NNNNN_PointA");
   TGraph *G3J = (TGraph *)File.Get("Loop_LWW_Both_A_Count_NNNNYNYN_WithSquare_NNNNN_PointA");
   TGraph *G4J = (TGraph *)File.Get("Loop_LWW_Both_A_Count_NNNYYNYN_WithSquare_NNNNN_PointA");

   G1J->SetLineWidth(2);
   G2J->SetLineWidth(2);
   G3J->SetLineWidth(2);
   G4J->SetLineWidth(2);
   G1J->SetLineColor(kBlack);
   G2J->SetLineColor(kRed - 3);
   G3J->SetLineColor(kBlack);
   G4J->SetLineColor(kRed - 3);
   G1J->SetLineStyle(kSolid);
   G2J->SetLineStyle(kSolid);
   G3J->SetLineStyle(kDashed);
   G4J->SetLineStyle(kDashed);

   TCanvas C;

   TH2D HWorld("HWorld", ";N_{S};#sigma(#lambda_{W})", 100, 80, 10000, 100, 0.1, 150);
   HWorld.SetStats(0);

   HWorld.Draw();

   G1J->Draw("l");
   G2J->Draw("l");
   G3J->Draw("l");
   G4J->Draw("l");

   TLegend Legend(0.35, 0.85, 0.70, 0.60);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(G1J, "#lambda_{W} + #tilde{y}_{t} (Relaxed - #Upsilon)", "l");
   Legend.AddEntry(G2J, "#lambda_{W} + y_{t} + #tilde{y}_{t} (Relaxed - #Upsilon)", "l");
   Legend.AddEntry(G3J, "#lambda_{W} + #tilde{y}_{t} (CMS - tight)", "l");
   Legend.AddEntry(G4J, "#lambda_{W} + y_{t} + #tilde{y}_{t} (CMS - tight)", "l");
   Legend.Draw();

   C.SetLogx();
   C.SetLogy();

   AddHeader("Needs to be beautified!", true);

   C.SaveAs("FigureB.png");
   C.SaveAs("FigureB.C");
   C.SaveAs("FigureB.eps");
   C.SaveAs("FigureB.pdf");

   return 0;
}



