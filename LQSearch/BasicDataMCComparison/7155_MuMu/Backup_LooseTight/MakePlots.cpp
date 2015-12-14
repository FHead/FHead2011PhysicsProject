#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper2.h"
#include "SlidePreparationHelper.h"

int main()
{
   SetStyle();

   TFile FData("DataPlots.root");
   TFile FTTbar("TTbar.root");

   TH1D *HData = (TH1D *)FData.Get("HPFJetGammaMRStar_RStar03");
   TH1D *HTTbar = (TH1D *)FTTbar.Get("HPFJetGammaMRStar_RStar03");

   HData->Sumw2();
   HData->SetMarkerStyle(11);
   HTTbar->SetLineColor(2);

   HData->SetStats(0);
   HTTbar->SetStats(0);

   TLegend legend(0.5, 0.8, 0.8, 0.6);
   legend.AddEntry(HData, "Normalized data", "p");
   legend.AddEntry(HTTbar, "Normalized ttbar", "l");
   legend.SetFillColor(0);

   TCanvas C("C", "C", 0, 0, 1024, 1024);
   HData->DrawNormalized("point error");
   HTTbar->DrawNormalized("same");
   legend.Draw();
   C.SetLogy();
   C.SaveAs("R03Comparison.png");
   C.SaveAs("R03Comparison.C");
   C.SaveAs("R03Comparison.eps");

   FData.Close();
   FTTbar.Close();

   return 0;
}




