#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TCanvas Canvas;

   // SubJetRecoDR vs. DRMax regions
   TH2D HRecoSubJetDRVsSubJetDRMaxRegion("HRecoSubJetDRVsSubJetDRMaxRegion",
      ";Matching Delta R Max;Reco Subjet Delta R", 100, 0, 0.5, 100, 0, 0.5);
   HRecoSubJetDRVsSubJetDRMaxRegion.SetStats(0);
   HRecoSubJetDRVsSubJetDRMaxRegion.Draw();

   TGraph GRecoSubJetDRVsSubJetDRMax0, GRecoSubJetDRVsSubJetDRMax1;
   GRecoSubJetDRVsSubJetDRMax0.SetPoint(0, 0, 0.1);
   GRecoSubJetDRVsSubJetDRMax0.SetPoint(1, 0.5, 0.1);
   GRecoSubJetDRVsSubJetDRMax1.SetPoint(0, 0.05, 0.1);
   GRecoSubJetDRVsSubJetDRMax1.SetPoint(1, 0.25, 0.5);
   GRecoSubJetDRVsSubJetDRMax0.SetLineWidth(2);
   GRecoSubJetDRVsSubJetDRMax1.SetLineWidth(2);
   GRecoSubJetDRVsSubJetDRMax0.Draw("l");
   GRecoSubJetDRVsSubJetDRMax1.Draw("l");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(22);
   Latex.DrawLatex(0.10, 0.40, "I");
   Latex.DrawLatex(0.30, 0.25, "II");
   Latex.DrawLatex(0.25, 0.05, "III");

   Canvas.SaveAs("Plots/RecoSubJetDRVsSubJetDRMaxRegions.png");
   Canvas.SaveAs("Plots/RecoSubJetDRVsSubJetDRMaxRegions.C");
   Canvas.SaveAs("Plots/RecoSubJetDRVsSubJetDRMaxRegions.eps");
   Canvas.SaveAs("Plots/RecoSubJetDRVsSubJetDRMaxRegions.pdf");

   return 0;
}




