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
   // The seven cuts are - I, A, B, C, D, H, J

   SetThesisStyle();

   TFile File("AllGraphs.root");

   TGraphErrors *A2AA_1 = (TGraphErrors *)File.Get("A2AA_BothS_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_2 = (TGraphErrors *)File.Get("A2AA_BothS_A_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_3 = (TGraphErrors *)File.Get("A2AA_BothS_B_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_4 = (TGraphErrors *)File.Get("A2AA_BothS_C_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_5 = (TGraphErrors *)File.Get("A2AA_BothS_D_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_6 = (TGraphErrors *)File.Get("A2AA_BothS_H_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_7 = (TGraphErrors *)File.Get("A2AA_BothS_J_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_1 = (TGraphErrors *)File.Get("A2ZA_BothS_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_2 = (TGraphErrors *)File.Get("A2ZA_BothS_A_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_3 = (TGraphErrors *)File.Get("A2ZA_BothS_B_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_4 = (TGraphErrors *)File.Get("A2ZA_BothS_C_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_5 = (TGraphErrors *)File.Get("A2ZA_BothS_D_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_6 = (TGraphErrors *)File.Get("A2ZA_BothS_H_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_7 = (TGraphErrors *)File.Get("A2ZA_BothS_J_Lumi_YYNYYNYY_Point0");

   A2AA_1->SetLineWidth(2);
   A2AA_2->SetLineWidth(2);
   A2AA_3->SetLineWidth(2);
   A2AA_4->SetLineWidth(2);
   A2AA_5->SetLineWidth(2);
   A2AA_6->SetLineWidth(2);
   A2AA_7->SetLineWidth(2);
   A2ZA_1->SetLineWidth(2);
   A2ZA_2->SetLineWidth(2);
   A2ZA_3->SetLineWidth(2);
   A2ZA_4->SetLineWidth(2);
   A2ZA_5->SetLineWidth(2);
   A2ZA_6->SetLineWidth(2);
   A2ZA_7->SetLineWidth(2);
   
   A2AA_1->SetLineColor(kBlue);
   A2AA_2->SetLineColor(kMagenta - 3);
   A2AA_3->SetLineColor(kGreen);
   A2AA_4->SetLineColor(kYellow - 3);
   A2AA_5->SetLineColor(kBlack);
   A2AA_6->SetLineColor(kCyan - 3);
   A2AA_7->SetLineColor(kRed);
   A2ZA_1->SetLineColor(kBlue);
   A2ZA_2->SetLineColor(kMagenta - 3);
   A2ZA_3->SetLineColor(kGreen);
   A2ZA_4->SetLineColor(kYellow - 3);
   A2ZA_5->SetLineColor(kBlack);
   A2ZA_6->SetLineColor(kCyan - 3);
   A2ZA_7->SetLineColor(kRed);

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

   TH2D HWorldAA("HWorldAA", ";N_{S} / #epsilon;#sigma(A_{2}^{#gamma#gamma})", 100, 180, 10000, 100, 0.001, 0.2);
   TH2D HWorldZA("HWorldZA", ";N_{S} / #epsilon;#sigma(A_{2}^{Z#gamma})", 100, 180, 10000, 100, 0.004, 0.5);
   
   HWorldAA.SetStats(0);
   HWorldZA.SetStats(0);

   TCanvas Canvas;
   Canvas.SetLogx();
   Canvas.SetLogy();

   HWorldAA.Draw();

   GAA.Draw("l");
   A2AA_1->Draw("pl");
   A2AA_2->Draw("pl");
   A2AA_3->Draw("pl");
   A2AA_4->Draw("pl");
   A2AA_5->Draw("pl");
   A2AA_6->Draw("pl");
   A2AA_7->Draw("pl");

   double x1 = ThesisNDCMappingX(0.5);
   double y1 = ThesisNDCMappingY(0.8);
   double x2 = ThesisNDCMappingX(0.9);
   double y2 = ThesisNDCMappingY(0.5);

   TLegend Legend(x1, y1, x2, y2);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(A2AA_1, "CMS - tight", "l");
   Legend.AddEntry(A2AA_2, "CMS - loose", "l");
   Legend.AddEntry(A2AA_3, "Opposite", "l");
   Legend.AddEntry(A2AA_4, "Same", "l");
   Legend.AddEntry(A2AA_5, "Combined", "l");
   Legend.AddEntry(A2AA_6, "Relaxed", "l");
   Legend.AddEntry(A2AA_7, "Relaxed - #Upsilon", "l");
   Legend.Draw();

   Canvas.SaveAs("Figure5AA.png");
   Canvas.SaveAs("Figure5AA.C");
   Canvas.SaveAs("Figure5AA.eps");
   Canvas.SaveAs("Figure5AA.pdf");
 
   HWorldZA.Draw();

   GZA.Draw("l");
   A2ZA_1->Draw("pl");
   A2ZA_2->Draw("pl");
   A2ZA_3->Draw("pl");
   A2ZA_4->Draw("pl");
   A2ZA_5->Draw("pl");
   A2ZA_6->Draw("pl");
   A2ZA_7->Draw("pl");

   Legend.Draw();

   Canvas.SaveAs("Figure5ZA.png");
   Canvas.SaveAs("Figure5ZA.C");
   Canvas.SaveAs("Figure5ZA.eps");
   Canvas.SaveAs("Figure5ZA.pdf");

   return 0;
}





