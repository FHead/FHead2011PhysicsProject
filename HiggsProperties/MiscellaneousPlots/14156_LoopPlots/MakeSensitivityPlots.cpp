#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TGaxis.h"

#include "SetStyle.h"

int main()
{
   TFile File("AllGraphs.root");
   TGraph *YT_FloatZZ = (TGraph *)File.Get("Loop_YT_Both_J_Count_YYYYYNNN_WithSquare_NNNNN_PointA");
   TGraph *YT_FixedZZ = (TGraph *)File.Get("Loop_YT_Both_J_Count_NNNYYNNN_WithSquare_NNNNN_PointA");
   TGraph *YTA_FloatZZ = (TGraph *)File.Get("Loop_YTA_Both_J_Count_YYYYYNNN_WithSquare_NNNNN_PointA");
   TGraph *YTA_FixedZZ = (TGraph *)File.Get("Loop_YTA_Both_J_Count_NNNYYNNN_WithSquare_NNNNN_PointA");

   YT_FloatZZ->SetLineWidth(2);
   YT_FixedZZ->SetLineWidth(2);
   YT_FloatZZ->SetLineStyle(kSolid);
   YT_FixedZZ->SetLineStyle(kDashed);
   YT_FloatZZ->SetLineColor(kRed);
   YT_FixedZZ->SetLineColor(kRed);
   YTA_FloatZZ->SetLineWidth(2);
   YTA_FixedZZ->SetLineWidth(2);
   YTA_FloatZZ->SetLineStyle(kSolid);
   YTA_FixedZZ->SetLineStyle(kDashed);
   YTA_FloatZZ->SetLineColor(kBlue);
   YTA_FixedZZ->SetLineColor(kBlue);

   TGraph GSM;
   GSM.SetPoint(0, 0, 1);
   GSM.SetPoint(1, 100000, 1);
   GSM.SetLineStyle(kDotted);

   SetThesisBigStyle();

   double Bottom = 0.2;
   double Top = 30;
   double Left = 80;
   double Right = 12500;

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

   TCanvas C;

   C.SetTickx(0);

   TH2D HWorld("HWorld", ";N_{S};#sigma(y_{t}) or #sigma(#tilde{y}_{t})", 100, Left, Right, 100, Bottom, Top);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetTitleOffset(1.4);

   HWorld.Draw();
   YT_FloatZZ->Draw("pl");
   YT_FixedZZ->Draw("pl");
   YTA_FloatZZ->Draw("pl");
   YTA_FixedZZ->Draw("pl");
   GSM.Draw("l");

   GAxis.Draw();

   TLegend Legend(0.4, 0.85, 0.85, 0.6);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(YT_FloatZZ, "y_{t} (float ZZ couplings)", "l");
   Legend.AddEntry(YT_FixedZZ, "y_{t} (fix ZZ couplings)", "l");
   Legend.AddEntry(YTA_FloatZZ, "#tilde{y}_{t} (float ZZ couplings)", "l");
   Legend.AddEntry(YTA_FixedZZ, "#tilde{y}_{t} (fix ZZ couplings)", "l");
   Legend.Draw();

   AddHeader("This is the scaled version!", false);

   C.SetLogx();
   C.SetLogy();
   C.SaveAs("FigureSensitivity.png");
   C.SaveAs("FigureSensitivity.C");
   C.SaveAs("FigureSensitivity.eps");
   C.SaveAs("FigureSensitivity.pdf");

   return 0;
}

