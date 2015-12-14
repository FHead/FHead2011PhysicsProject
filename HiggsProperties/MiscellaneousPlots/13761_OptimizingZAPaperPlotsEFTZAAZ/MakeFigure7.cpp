#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   // I cut = A0, J cut = Full' - Upsilon, H cut = Full'

   SetThesisStyle();

   TFile File("AllGraphs.root");

   TGraphErrors *A2AA_AS = (TGraphErrors *)File.Get("A2AA_BothS_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_AB = (TGraphErrors *)File.Get("A2AA_Both_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_JS = (TGraphErrors *)File.Get("A2AA_BothS_H_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_JB = (TGraphErrors *)File.Get("A2AA_Both_H_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_AS = (TGraphErrors *)File.Get("A2ZA_BothS_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_AB = (TGraphErrors *)File.Get("A2ZA_Both_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_JS = (TGraphErrors *)File.Get("A2ZA_BothS_H_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_JB = (TGraphErrors *)File.Get("A2ZA_Both_H_Lumi_YYNYYNYY_Point0");

   A2AA_AS->SetLineWidth(2);
   A2AA_AB->SetLineWidth(2);
   A2AA_JS->SetLineWidth(2);
   A2AA_JB->SetLineWidth(2);
   A2ZA_AS->SetLineWidth(2);
   A2ZA_AB->SetLineWidth(2);
   A2ZA_JS->SetLineWidth(2);
   A2ZA_JB->SetLineWidth(2);
   
   A2AA_AS->SetLineColor(kBlue);
   A2AA_AB->SetLineColor(kBlue);
   A2AA_JS->SetLineColor(kRed);
   A2AA_JB->SetLineColor(kRed);
   A2ZA_AS->SetLineColor(kBlue);
   A2ZA_AB->SetLineColor(kBlue);
   A2ZA_JS->SetLineColor(kRed);
   A2ZA_JB->SetLineColor(kRed);

   A2AA_AS->SetLineStyle(1);
   A2AA_AB->SetLineStyle(2);
   A2AA_JS->SetLineStyle(1);
   A2AA_JB->SetLineStyle(2);
   A2ZA_AS->SetLineStyle(1);
   A2ZA_AB->SetLineStyle(2);
   A2ZA_JS->SetLineStyle(1);
   A2ZA_JB->SetLineStyle(2);

   TGraph GAA, GZA;
   GAA.SetPoint(0, 0, 0.008);
   GAA.SetPoint(1, 100000, 0.008);
   GZA.SetPoint(0, 0, 0.014);
   GZA.SetPoint(1, 100000, 0.014);

   GAA.SetLineWidth(2);
   GAA.SetLineColor(kGreen - 3);
   GAA.SetLineStyle(9);
   GZA.SetLineWidth(2);
   GZA.SetLineColor(kGreen - 3);
   GZA.SetLineStyle(9);

   TH2D HWorldAA("HWorldAA", ";N_{S} / #epsilon;#sigma(A_{2}^{#gamma#gamma})", 100, 180, 10000, 100, 0.002, 0.4);
   TH2D HWorldZA("HWorldZA", ";N_{S} / #epsilon;#sigma(A_{2}^{Z#gamma})", 100, 180, 10000, 100, 0.008, 0.5);
   
   HWorldAA.SetStats(0);
   HWorldZA.SetStats(0);

   TCanvas Canvas;
   Canvas.SetLogx();
   Canvas.SetLogy();

   HWorldAA.Draw();

   GAA.Draw("l");
   A2AA_AS->Draw("pl");
   A2AA_AB->Draw("pl");
   A2AA_JS->Draw("pl");
   A2AA_JB->Draw("pl");

   double x1 = ThesisNDCMappingX(0.45);
   double y1 = ThesisNDCMappingY(0.8);
   double x2 = ThesisNDCMappingX(0.85);
   double y2 = ThesisNDCMappingY(0.5);

   TLegend Legend(x1, y1, x2, y2);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(A2AA_AS, "CMS - tight (S)", "l");
   Legend.AddEntry(A2AA_AB, "CMS - tight (S+B)", "l");
   Legend.AddEntry(A2AA_JS, "Relaxed (S)", "l");
   Legend.AddEntry(A2AA_JB, "Relaxed (S+B)", "l");
   Legend.Draw();

   Canvas.SaveAs("Figure7AA.png");
   Canvas.SaveAs("Figure7AA.C");
   Canvas.SaveAs("Figure7AA.eps");
   Canvas.SaveAs("Figure7AA.pdf");
 
   HWorldZA.Draw();

   GZA.Draw("l");
   A2ZA_AS->Draw("pl");
   A2ZA_AB->Draw("pl");
   A2ZA_JS->Draw("pl");
   A2ZA_JB->Draw("pl");

   Legend.Draw();

   Canvas.SaveAs("Figure7ZA.png");
   Canvas.SaveAs("Figure7ZA.C");
   Canvas.SaveAs("Figure7ZA.eps");
   Canvas.SaveAs("Figure7ZA.pdf");

   return 0;
}





