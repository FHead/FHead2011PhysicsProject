#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGAxis.h"

#include "SetStyle.h"

int main()
{
   SetThesisBigStyle();

   TFile F("AllGraphs.root");

   TGraphErrors *GA2  = (TGraphErrors *)F.Get("A2_Both_J_Count_YYYYYN_PointA");
   TGraphErrors *GA3  = (TGraphErrors *)F.Get("A3_Both_J_Count_YYYYYN_PointA");
   TGraphErrors *GA4  = (TGraphErrors *)F.Get("A4_Both_J_Count_YYYYYN_PointA");
   TGraphErrors *GYT  = (TGraphErrors *)F.Get("YT_Both_J_Count_YYYYYN_PointA");
   TGraphErrors *GYTA = (TGraphErrors *)F.Get("YTA_Both_J_Count_YYYYYN_PointA");

   GA2->SetLineWidth(2);
   GA3->SetLineWidth(2);
   GA4->SetLineWidth(2);
   GYT->SetLineWidth(2);
   GYTA->SetLineWidth(2);

   GA2->SetLineColor(kYellow - 3);
   GA3->SetLineColor(kCyan - 3);
   GA4->SetLineColor(kGreen - 3);
   GYT->SetLineColor(kRed - 3);
   GYTA->SetLineColor(kBlue - 3);

   double Left = 80;
   double Right = 10000;
   double Bottom = 0.06;
   double Top = 30;
   TH2D HWorld("HWorld", ";N_{S};#sigma(A_{n}^{ZZ}), #sigma(y_{t}), #sigma(#tilde{y}_{t})", 100, Left, Right, 100, Bottom, Top);
   HWorld.SetStats(0);

   double Efficiency = 0.46218;
   double CrossSection = 4.18 + 49.85;
   double BranchingRatio = 1.25e-4;
   double HZZ = CrossSection * BranchingRatio;
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

   TCanvas C;
   C.SetLogy();
   C.SetLogx();
   C.SetTickx(0);

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
   Legend1.AddEntry(GA2,  "A_{2}^{ZZ}", "l");
   Legend1.AddEntry(GA3,  "A_{3}^{ZZ}", "l");
   Legend1.AddEntry(GA4,  "A_{4}^{ZZ}", "l");
   Legend2.AddEntry(GYT,  "y_{t}", "l");
   Legend2.AddEntry(GYTA, "#tilde{y}_{t}", "l");
   Legend2.AddEntry("", "", "");

   HWorld.Draw();
   GA2->Draw("lp");
   GA3->Draw("lp");
   GA4->Draw("lp");
   GYT->Draw("lp");
   GYTA->Draw("lp");

   Legend1.Draw();
   Legend2.Draw();
   GAxis.Draw();

   C.SaveAs("FigureBeta.png");
   C.SaveAs("FigureBeta.C");
   C.SaveAs("FigureBeta.eps");
   C.SaveAs("FigureBeta.pdf");

   return 0;
}






