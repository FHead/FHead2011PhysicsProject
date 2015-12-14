#include <iostream>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main();
void PrepareHistogram(TH1D *H, int Color);

int main()
{
   SetThesisRegularStyle();

   TFile File("AllHistograms.root");

   TH1D *HM21 = (TH1D *)File.Get("HM21");
   TH1D *HM22 = (TH1D *)File.Get("HM22");
   TH1D *HM23 = (TH1D *)File.Get("HM23");
   TH1D *HM24 = (TH1D *)File.Get("HM24");
   TH1D *HPhi1 = (TH1D *)File.Get("HPhi1");
   TH1D *HPhi2 = (TH1D *)File.Get("HPhi2");
   TH1D *HPhi3 = (TH1D *)File.Get("HPhi3");
   TH1D *HPhi4 = (TH1D *)File.Get("HPhi4");

   PrepareHistogram(HM21, kBlack);
   PrepareHistogram(HM22, kRed);
   PrepareHistogram(HM23, kGreen - 3);
   PrepareHistogram(HM24, kMagenta - 3);
   PrepareHistogram(HPhi1, kBlack);
   PrepareHistogram(HPhi2, kRed);
   PrepareHistogram(HPhi3, kGreen - 3);
   PrepareHistogram(HPhi4, kMagenta - 3);

   TCanvas C;

   TH2D HM2World("HM2World", ";m_{2};a.u.", 100, 12, 70, 100, 0, 0.1);
   HM2World.SetStats(0);

   TLegend M2Legend(0.5 / 1.05, 0.8, 0.8 / 1.05, 0.6);
   M2Legend.SetBorderSize(0);
   M2Legend.SetTextFont(42);
   M2Legend.SetTextSize(0.035);
   M2Legend.SetFillStyle(0);
   M2Legend.AddEntry(HM21, "A^{2}_{ZZ} / A^{1}_{ZZ} = 0", "l");
   M2Legend.AddEntry(HM22, "A^{2}_{ZZ} / A^{1}_{ZZ} = 3.3", "l");
   M2Legend.AddEntry(HM23, "A^{2}_{ZZ} / A^{1}_{ZZ} = 10", "l");

   HM2World.Draw();
   HM21->Draw("same");
   HM22->Draw("same");
   HM23->Draw("same");
   // HM24->Draw("same");
   M2Legend.Draw();

   C.SaveAs("MultiDimensionalResult-MainResult-A2FeatureM2.png");
   C.SaveAs("MultiDimensionalResult-MainResult-A2FeatureM2.C");
   C.SaveAs("MultiDimensionalResult-MainResult-A2FeatureM2.eps");
   C.SaveAs("MultiDimensionalResult-MainResult-A2FeatureM2.pdf");

   TH2D HPhiWorld("HPhiWorld", ";#phi;a.u.", 100, 0, 2 * PI, 100, 0, 0.38);
   HPhiWorld.SetStats(0);

   TLegend PhiLegend(0.5 / 1.05, 0.8, 0.8 / 1.05, 0.6);
   PhiLegend.SetBorderSize(0);
   PhiLegend.SetTextFont(42);
   PhiLegend.SetTextSize(0.035);
   PhiLegend.SetFillStyle(0);
   PhiLegend.AddEntry(HPhi1, "A^{2}_{ZZ} / A^{1}_{ZZ} = 0", "l");
   PhiLegend.AddEntry(HPhi4, "A^{2}_{ZZ} / A^{1}_{ZZ} = 2.5", "l");
   PhiLegend.AddEntry(HPhi3, "A^{2}_{ZZ} / A^{1}_{ZZ} = 10", "l");

   HPhiWorld.Draw();
   HPhi1->Draw("same");
   // HPhi2->Draw("same");
   HPhi3->Draw("same");
   HPhi4->Draw("same");
   PhiLegend.Draw();

   C.SaveAs("MultiDimensionalResult-MainResult-A2FeaturePhi.png");
   C.SaveAs("MultiDimensionalResult-MainResult-A2FeaturePhi.C");
   C.SaveAs("MultiDimensionalResult-MainResult-A2FeaturePhi.eps");
   C.SaveAs("MultiDimensionalResult-MainResult-A2FeaturePhi.pdf");

   File.Close();

   return 0;
}

void PrepareHistogram(TH1D *H, int Color)
{
   int Bin = H->GetNbinsX();
   double Min = H->GetXaxis()->GetBinLowEdge(1);
   double Max = H->GetXaxis()->GetBinUpEdge(Bin);

   H->Scale(1 / H->Integral() * Bin / (Max - Min));

   H->SetLineWidth(2);
   H->SetLineColor(Color);
}








