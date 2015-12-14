#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TGaxis.h"

#include "SetStyle.h"

int main()
{
   // Full'-Upsilon cut is the J cut
   // Full' is the H cut

   SetThesisStyle();

   TFile File("AllGraphs.root");

   TGraphErrors *A2ZZ = (TGraphErrors *)File.Get("A2ZZ_Both_H_Count_YYNYYNYY_Point0");
   TGraphErrors *A3ZZ = (TGraphErrors *)File.Get("A3ZZ_Both_H_Count_YYNYYNYY_Point0");
   TGraphErrors *A2ZA = (TGraphErrors *)File.Get("A2ZA_Both_H_Count_YYNYYNYY_Point0");
   TGraphErrors *A3ZA = (TGraphErrors *)File.Get("A3ZA_Both_H_Count_YYNYYNYY_Point0");
   TGraphErrors *A2AA = (TGraphErrors *)File.Get("A2AA_Both_H_Count_YYNYYNYY_Point0");
   TGraphErrors *A3AA = (TGraphErrors *)File.Get("A3AA_Both_H_Count_YYNYYNYY_Point0");

   A2ZZ->SetLineWidth(2);
   A3ZZ->SetLineWidth(2);
   A2ZA->SetLineWidth(2);
   A3ZA->SetLineWidth(2);
   A2AA->SetLineWidth(2);
   A3AA->SetLineWidth(2);
   
   A2ZZ->SetLineColor(kBlack);
   A3ZZ->SetLineColor(kRed);
   A2ZA->SetLineColor(kYellow - 3);
   A3ZA->SetLineColor(kGreen);
   A2AA->SetLineColor(kCyan - 3);
   A3AA->SetLineColor(kMagenta);

   TGraph G, G2;
   G.SetPoint(0, 0, 0.008);
   G.SetPoint(1, 100000, 0.008);
   G2.SetPoint(0, 0, 0.014);
   G2.SetPoint(1, 100000, 0.014);

   G.SetLineWidth(2);
   G.SetLineColor(kGreen - 3);
   G.SetLineStyle(9);
   G2.SetLineWidth(2);
   G2.SetLineColor(kBlue - 3);
   G2.SetLineStyle(9);

   double Left = 80;
   double Right = 10000;
   double Bottom = 0.001;
   double Top = 40;
   TH2D HWorld("HWorld", ";N_{S};#sigma(A_{n}^{ij})", 100, Left, Right, 100, Bottom, Top);
   HWorld.SetStats(0);

   double Efficiency = 0.46218;
   double CrossSection = 4.18 + 49.85;
   double BranchingRatio = 1.25e-4;
   double HZZ = CrossSection * BranchingRatio;
   // double TopLeft = Left / Efficiency / HZZ / 1000;
   // double TopRight = Right / Efficiency / HZZ / 1000;
   double TopLeft = Left / HZZ / 1000;
   double TopRight = Right / HZZ / 1000;

   TGaxis GAxis(Left, Top, Right, Top, TopLeft, TopRight, 510, "-G");
   GAxis.SetLabelFont(42);
   GAxis.SetLabelSize(0.035);
   // GAxis.SetLabelOffset(1.00);
   GAxis.SetTitleFont(42);
   GAxis.SetTitleSize(0.035);
   GAxis.SetTitleOffset(1.10);
   GAxis.SetTitle("L^{14 TeV} #times #epsilon (fb^{-1})");

   TCanvas Canvas;
   Canvas.SetLogx();
   Canvas.SetLogy();
   Canvas.SetTickx(0);

   HWorld.Draw();
   GAxis.Draw();

   G.Draw("l");
   G2.Draw("l");
   A2ZZ->Draw("pl");
   A3ZZ->Draw("pl");
   A2ZA->Draw("pl");
   A3ZA->Draw("pl");
   A2AA->Draw("pl");
   A3AA->Draw("pl");

   double x1 = ThesisNDCMappingX(0.65);
   double y1 = ThesisNDCMappingY(0.85);
   double x2 = ThesisNDCMappingX(0.75);
   double y2 = ThesisNDCMappingY(0.65);
   double x3 = ThesisNDCMappingX(0.85);

   TLegend Legend1(x1, y1, x2, y2);
   TLegend Legend2(x2, y1, x3, y2);
   Legend1.SetFillStyle(0);
   Legend1.SetBorderSize(0);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend1.AddEntry(A2ZZ, "A_{2}^{ZZ}", "l");
   Legend2.AddEntry(A3ZZ, "A_{3}^{ZZ}", "l");
   Legend1.AddEntry(A2ZA, "A_{2}^{Z#gamma}", "l");
   Legend2.AddEntry(A3ZA, "A_{3}^{Z#gamma}", "l");
   Legend1.AddEntry(A2AA, "A_{2}^{#gamma#gamma}", "l");
   Legend2.AddEntry(A3AA, "A_{3}^{#gamma#gamma}", "l");
   Legend1.Draw();
   Legend2.Draw();

   Canvas.SaveAs("Figure8.png");
   Canvas.SaveAs("Figure8.C");
   Canvas.SaveAs("Figure8.eps");
   Canvas.SaveAs("Figure8.pdf");

   return 0;
}





