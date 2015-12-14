#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisBigStyle();

   TFile F("AllGraphs.root");

   TGraphErrors *GYT_A  = (TGraphErrors *)F.Get("YT_BothS_A_Lumi_NNNYYN_PointA");
   TGraphErrors *GYT_J  = (TGraphErrors *)F.Get("YT_BothS_J_Lumi_NNNYYN_PointA");
   TGraphErrors *GYTA_A = (TGraphErrors *)F.Get("YTA_BothS_A_Lumi_NNNYYN_PointA");
   TGraphErrors *GYTA_J = (TGraphErrors *)F.Get("YTA_BothS_J_Lumi_NNNYYN_PointA");

   GYT_A->SetLineWidth(2);
   GYT_J->SetLineWidth(2);
   GYTA_A->SetLineWidth(2);
   GYTA_J->SetLineWidth(2);

   GYT_A->SetLineColor(kRed - 3);
   GYT_J->SetLineColor(kBlue - 3);
   GYTA_A->SetLineColor(kRed - 3);
   GYTA_J->SetLineColor(kBlue - 3);

   GYT_A->SetLineStyle(kSolid);
   GYT_J->SetLineStyle(kSolid);
   GYTA_A->SetLineStyle(kDashed);
   GYTA_J->SetLineStyle(kDashed);

   TH2D HWorld("HWorld", ";N_{S} / #epsilon;#sigma(y_{t}) or #sigma(#tilde{y}_{t})", 100, 200, 10000, 100, 0.3, 30);
   HWorld.SetStats(0);

   TCanvas C;
   C.SetLogy();
   C.SetLogx();

   double x1 = ThesisNDCMappingBigX(0.500);
   double y1 = ThesisNDCMappingBigY(0.825);
   double x2 = ThesisNDCMappingBigX(0.800);
   double y2 = ThesisNDCMappingBigY(0.625);

   TLegend Legend(x1, y1, x2, y2);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(GYT_A, "y_{t}, CMS - loose", "l");
   Legend.AddEntry(GYTA_A, "#tilde{y}_{t}, CMS - loose", "l");
   Legend.AddEntry(GYT_J, "y_{t}, Relaxed - #Upsilon", "l");
   Legend.AddEntry(GYTA_J, "#tilde{y}_{t}, Relaxed - #Upsilon", "l");

   HWorld.Draw();
   GYT_A->Draw("pl");
   GYT_J->Draw("pl");
   GYTA_A->Draw("pl");
   GYTA_J->Draw("pl");

   Legend.Draw();

   C.SaveAs("FigureAlpha.png");
   C.SaveAs("FigureAlpha.C");
   C.SaveAs("FigureAlpha.eps");
   C.SaveAs("FigureAlpha.pdf");

   return 0;
}






