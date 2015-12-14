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
   // A0 cut is the I cut

   SetThesisStyle();

   TFile File("AllGraphs.root");

   TGraphErrors *A2AA_EM = (TGraphErrors *)File.Get("A2AA_EMS_I_Count_FloatA2A3");
   TGraphErrors *A2AA_EE = (TGraphErrors *)File.Get("A2AA_EES_I_Count_FloatA2A3");

   A2AA_EM->SetLineWidth(2);
   A2AA_EM->SetLineColor(kBlue);
   A2AA_EE->SetLineWidth(2);
   A2AA_EE->SetLineColor(kRed);

   TGraph G;
   G.SetPoint(0, 0, 0.008);
   G.SetPoint(1, 100000, 0.008);

   G.SetLineWidth(2);
   G.SetLineColor(kGreen - 3);
   G.SetLineStyle(9);

   TH2D HWorld("HWorld", ";N_{S};#sigma(A_{2}^{#gamma#gamma})", 100, 80, 10000, 100, 0.001, 0.2);
   HWorld.SetStats(0);

   TCanvas Canvas;
   Canvas.SetLogx();
   Canvas.SetLogy();

   HWorld.Draw();

   G.Draw("l");
   A2AA_EM->Draw("pl");
   A2AA_EE->Draw("pl");

   double x1 = ThesisNDCMappingX(0.6);
   double y1 = ThesisNDCMappingY(0.8);
   double x2 = ThesisNDCMappingX(0.9);
   double y2 = ThesisNDCMappingY(0.6);

   TLegend Legend(x1, y1, x2, y2);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(A2AA_EM, "2e2#mu", "l");
   Legend.AddEntry(A2AA_EE, "4e", "l");
   Legend.Draw();

   Canvas.SaveAs("Figure3.png");
   Canvas.SaveAs("Figure3.C");
   Canvas.SaveAs("Figure3.eps");
   Canvas.SaveAs("Figure3.pdf");

   return 0;
}





