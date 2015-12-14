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

   TGraph *G1J = (TGraph *)File.Get("Loop_LWW_Both_J_Count_NNNNNNYN_WithSquare_NNNNN_PointA");
   TGraph *G2J = (TGraph *)File.Get("Loop_LWW_Both_J_Count_NNNYNNYN_WithSquare_NNNNN_PointA");
   TGraph *G3J = (TGraph *)File.Get("Loop_LWW_Both_J_Count_NNNNYNYN_WithSquare_NNNNN_PointA");
   TGraph *G4J = (TGraph *)File.Get("Loop_LWW_Both_J_Count_YYYYYNYN_WithSquare_NNNNN_PointA");
   TGraph *G5J = (TGraph *)File.Get("Loop_LWW_Both_J_Count_YYYNYNYN_WithSquare_NNNNN_PointA");

   G1J->SetLineWidth(2);
   G2J->SetLineWidth(2);
   G3J->SetLineWidth(2);
   G4J->SetLineWidth(2);
   G5J->SetLineWidth(2);
   G1J->SetLineColor(kBlack);
   G2J->SetLineColor(kRed - 3);
   G3J->SetLineColor(kYellow - 3);
   G4J->SetLineColor(kMagenta - 3);
   G5J->SetLineColor(kGreen - 3);

   TCanvas C;

   TH2D HWorld("HWorld", ";N_{S};#sigma(#lambda_{W})", 100, 80, 30000, 100, 0.05, 50);
   HWorld.SetStats(0);

   HWorld.Draw();

   G1J->Draw("l");
   G2J->Draw("l");
   G3J->Draw("l");
   G4J->Draw("l");
   G5J->Draw("l");

   TLegend Legend(0.45, 0.85, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(G1J, "#lambda_{W}", "l");
   Legend.AddEntry(G2J, "#lambda_{W} + y_{t}", "l");
   Legend.AddEntry(G3J, "#lambda_{W} + #tilde{y}_{t}", "l");
   Legend.AddEntry(G4J, "#lambda_{W} + ZZ + y_{t} + #tilde{y}_{t}", "l");
   Legend.AddEntry(G5J, "#lambda_{W} + ZZ + #tilde{y}_{t}", "l");
   Legend.Draw();

   C.SetLogx();
   C.SetLogy();

   AddHeader("", true);

   C.SaveAs("FigureA.png");
   C.SaveAs("FigureA.C");
   C.SaveAs("FigureA.eps");
   C.SaveAs("FigureA.pdf");

   return 0;
}



