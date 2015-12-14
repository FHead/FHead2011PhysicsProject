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
   // I cut = A0, J cut = Full - Upsilon

   SetThesisStyle();

   TFile File("AllGraphs.root");

   TGraphErrors *A2AA_IS = (TGraphErrors *)File.Get("A2AA_BothS_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_IB = (TGraphErrors *)File.Get("A2AA_Both_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_JS = (TGraphErrors *)File.Get("A2AA_BothS_J_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_JB = (TGraphErrors *)File.Get("A2AA_Both_J_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2AA_JH = (TGraphErrors *)File.Get("A2AA_BothHalf_J_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_IS = (TGraphErrors *)File.Get("A2ZA_BothS_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_IB = (TGraphErrors *)File.Get("A2ZA_Both_I_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_JS = (TGraphErrors *)File.Get("A2ZA_BothS_J_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_JB = (TGraphErrors *)File.Get("A2ZA_Both_J_Lumi_YYNYYNYY_Point0");
   TGraphErrors *A2ZA_JH = (TGraphErrors *)File.Get("A2ZA_BothHalf_J_Lumi_YYNYYNYY_Point0");

   A2AA_IS->SetLineWidth(2);
   A2AA_IB->SetLineWidth(2);
   A2AA_JS->SetLineWidth(2);
   A2AA_JB->SetLineWidth(2);
   A2AA_JH->SetLineWidth(2);
   A2ZA_IS->SetLineWidth(2);
   A2ZA_IB->SetLineWidth(2);
   A2ZA_JS->SetLineWidth(2);
   A2ZA_JB->SetLineWidth(2);
   A2ZA_JH->SetLineWidth(2);
   
   A2AA_IS->SetLineColor(kBlue);
   A2AA_IB->SetLineColor(kBlue);
   A2AA_JS->SetLineColor(kRed);
   A2AA_JB->SetLineColor(kRed);
   A2AA_JH->SetLineColor(kRed);
   A2ZA_IS->SetLineColor(kBlue);
   A2ZA_IB->SetLineColor(kBlue);
   A2ZA_JS->SetLineColor(kRed);
   A2ZA_JB->SetLineColor(kRed);
   A2ZA_JH->SetLineColor(kRed);

   A2AA_IS->SetLineStyle(1);
   A2AA_IB->SetLineStyle(2);
   A2AA_JS->SetLineStyle(1);
   A2AA_JB->SetLineStyle(2);
   A2AA_JH->SetLineStyle(9);
   A2ZA_IS->SetLineStyle(1);
   A2ZA_IB->SetLineStyle(2);
   A2ZA_JS->SetLineStyle(1);
   A2ZA_JB->SetLineStyle(2);
   A2ZA_JH->SetLineStyle(9);

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
   A2AA_IS->Draw("pl");
   A2AA_IB->Draw("pl");
   A2AA_JS->Draw("pl");
   A2AA_JB->Draw("pl");
   A2AA_JH->Draw("pl");

   double x1 = ThesisNDCMappingX(0.45);
   double y1 = ThesisNDCMappingY(0.8);
   double x2 = ThesisNDCMappingX(0.85);
   double y2 = ThesisNDCMappingY(0.5);

   TLegend Legend(x1, y1, x2, y2);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(A2AA_IS, "CMS - tight (S)", "l");
   Legend.AddEntry(A2AA_IB, "CMS - tight (S+B)", "l");
   Legend.AddEntry(A2AA_JS, "Relaxed - #Upsilon (S)", "l");
   Legend.AddEntry(A2AA_JH, "Relaxed - #Upsilon (S+0.5 B)", "l");
   Legend.AddEntry(A2AA_JB, "Relaxed - #Upsilon (S+B)", "l");
   Legend.Draw();

   Canvas.SaveAs("Figure7PrimeAA.png");
   Canvas.SaveAs("Figure7PrimeAA.C");
   Canvas.SaveAs("Figure7PrimeAA.eps");
   Canvas.SaveAs("Figure7PrimeAA.pdf");
 
   HWorldZA.Draw();

   GZA.Draw("l");
   A2ZA_IS->Draw("pl");
   A2ZA_IB->Draw("pl");
   A2ZA_JS->Draw("pl");
   A2ZA_JB->Draw("pl");
   A2ZA_JH->Draw("pl");

   Legend.Draw();

   Canvas.SaveAs("Figure7PrimeZA.png");
   Canvas.SaveAs("Figure7PrimeZA.C");
   Canvas.SaveAs("Figure7PrimeZA.eps");
   Canvas.SaveAs("Figure7PrimeZA.pdf");

   return 0;
}





