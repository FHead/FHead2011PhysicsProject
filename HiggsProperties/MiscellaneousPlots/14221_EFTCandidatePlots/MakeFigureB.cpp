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

   TGraph *G1J = (TGraph *)File.Get("AVV_A2ZZ_Both_J_Count_YYYYYYYY_WithSquare_YNNYN_PointA");
   TGraph *G2J = (TGraph *)File.Get("AVV_A3ZZ_Both_J_Count_YYYYYYYY_WithSquare_YNNYN_PointA");
   TGraph *G3J = (TGraph *)File.Get("AVV_A4ZZ_Both_J_Count_YYYYYYYY_WithSquare_YNNYN_PointA");
   TGraph *G4J = (TGraph *)File.Get("AVV_A2ZA_Both_J_Count_YYYYYYYY_WithSquare_YNNYN_PointA");
   TGraph *G5J = (TGraph *)File.Get("AVV_A3ZA_Both_J_Count_YYYYYYYY_WithSquare_YNNYN_PointA");
   TGraph *G6J = (TGraph *)File.Get("AVV_A4ZA_Both_J_Count_YYYYYYYY_WithSquare_YNNYN_PointA");
   TGraph *G7J = (TGraph *)File.Get("AVV_A2AA_Both_J_Count_YYYYYYYY_WithSquare_YNNYN_PointA");
   TGraph *G8J = (TGraph *)File.Get("AVV_A3AA_Both_J_Count_YYYYYYYY_WithSquare_YNNYN_PointA");

   G1J->SetLineWidth(2);
   G2J->SetLineWidth(2);
   G3J->SetLineWidth(2);
   G4J->SetLineWidth(2);
   G5J->SetLineWidth(2);
   G6J->SetLineWidth(2);
   G7J->SetLineWidth(2);
   G8J->SetLineWidth(2);
   G1J->SetLineColor(kBlack);
   G2J->SetLineColor(kRed - 3);
   G3J->SetLineColor(kYellow - 3);
   G4J->SetLineColor(kMagenta - 3);
   G5J->SetLineColor(kGreen - 3);
   G6J->SetLineColor(kBlue - 3);
   G7J->SetLineColor(kCyan - 3);
   G8J->SetLineColor(kCyan - 7);

   TCanvas C;

   TH2D HWorld("HWorld", ";N_{S};#sigma(A_{n}^{ij})", 100, 80, 30000, 100, 0.001, 500);
   HWorld.SetStats(0);

   HWorld.Draw();

   G1J->Draw("l");
   G2J->Draw("l");
   G3J->Draw("l");
   G4J->Draw("l");
   G5J->Draw("l");
   G6J->Draw("l");
   G7J->Draw("l");
   G8J->Draw("l");

   TLegend Legend1(0.45, 0.85, 0.65, 0.60);
   TLegend Legend2(0.55, 0.85, 0.75, 0.60);
   TLegend Legend3(0.65, 0.85, 0.85, 0.60);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetBorderSize(0);
   Legend1.SetFillStyle(0);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetBorderSize(0);
   Legend2.SetFillStyle(0);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.035);
   Legend3.SetBorderSize(0);
   Legend3.SetFillStyle(0);
   Legend1.AddEntry(G1J, "A_{2}^{ZZ}", "l");
   Legend1.AddEntry(G2J, "A_{3}^{ZZ}", "l");
   Legend1.AddEntry(G3J, "A_{4}^{ZZ}", "l");
   Legend2.AddEntry(G4J, "A_{2}^{Z#gamma}", "l");
   Legend2.AddEntry(G5J, "A_{3}^{Z#gamma}", "l");
   Legend2.AddEntry(G6J, "A_{4}^{Z#gamma}", "l");
   Legend3.AddEntry(G7J, "A_{2}^{#gamma#gamma}", "l");
   Legend3.AddEntry(G8J, "A_{3}^{#gamma#gamma}", "l");
   Legend3.AddEntry("", "", "");
   Legend1.Draw();
   Legend2.Draw();
   Legend3.Draw();

   C.SetLogx();
   C.SetLogy();

   AddHeader("Preliminary.", true);

   C.SaveAs("FigureB.png");
   C.SaveAs("FigureB.C");
   C.SaveAs("FigureB.eps");
   C.SaveAs("FigureB.pdf");

   return 0;
}



