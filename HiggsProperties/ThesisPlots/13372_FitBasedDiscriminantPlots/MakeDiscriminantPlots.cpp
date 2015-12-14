#include <iostream>
using namespace std;

#include "SetStyle.h"
#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"

int main();
void PrepareHistogram(TH2D *H, string Label);

int main()
{
   SetStyle();

   TFile FS("PlotsFromFirstData50ns6723/SingleMu_All.root");
   TFile FM("PlotsFromFirstData50ns6723/METBTag_All.root");

   TH2D *HSLinear = (TH2D *)FS.Get("HLambdaDLinearVsTotalCharge");
   TH2D *HMLinear = (TH2D *)FM.Get("HLambdaDLinearVsTotalCharge");
   TH2D *HSSpike = (TH2D *)FS.Get("HLambdaDRMS8MaxVsTotalCharge");
   TH2D *HMSpike = (TH2D *)FM.Get("HLambdaDRMS8MaxVsTotalCharge");

   TGraph *GLinear = (TGraph *)FS.Get("LinearCut");
   TGraph *GSpike = (TGraph *)FS.Get("SpikeCut");

   PrepareHistogram(HSLinear, "#Lambda_{flat}");
   PrepareHistogram(HMLinear, "#Lambda_{flat}");
   PrepareHistogram(HSSpike, "#Lambda_{spike}");
   PrepareHistogram(HMSpike, "#Lambda_{spike}");

   GLinear->SetLineWidth(3);
   GLinear->SetLineColor(kRed);
   GSpike->SetLineWidth(3);
   GSpike->SetLineColor(kRed);

   TCanvas C1("C1", "C1", 1024, 1024);

   HSLinear->Draw("colz");
   GLinear->Draw("l");

   C1.SetLogz();
   C1.SaveAs("HcalNoise-FitBasedFilter-Discriminants1.png");
   C1.SaveAs("HcalNoise-FitBasedFilter-Discriminants1.C");
   C1.SaveAs("HcalNoise-FitBasedFilter-Discriminants1.eps");
   C1.SaveAs("HcalNoise-FitBasedFilter-Discriminants1.pdf");

   TCanvas C2("C2", "C2", 1024, 1024);
   
   HMLinear->Draw("colz");
   GLinear->Draw("l");

   C2.SetLogz();
   C2.SaveAs("HcalNoise-FitBasedFilter-Discriminants2.png");
   C2.SaveAs("HcalNoise-FitBasedFilter-Discriminants2.C");
   C2.SaveAs("HcalNoise-FitBasedFilter-Discriminants2.eps");
   C2.SaveAs("HcalNoise-FitBasedFilter-Discriminants2.pdf");

   TCanvas C3("C3", "C3", 1024, 1024);

   HSSpike->Draw("colz");
   GSpike->Draw("l");

   C3.SetLogz();
   C3.SaveAs("HcalNoise-FitBasedFilter-Discriminants3.png");
   C3.SaveAs("HcalNoise-FitBasedFilter-Discriminants3.C");
   C3.SaveAs("HcalNoise-FitBasedFilter-Discriminants3.eps");
   C3.SaveAs("HcalNoise-FitBasedFilter-Discriminants3.pdf");

   TCanvas C4("C4", "C4", 1024, 1024);
   
   HMSpike->Draw("colz");
   GSpike->Draw("l");

   C4.SetLogz();
   C4.SaveAs("HcalNoise-FitBasedFilter-Discriminants4.png");
   C4.SaveAs("HcalNoise-FitBasedFilter-Discriminants4.C");
   C4.SaveAs("HcalNoise-FitBasedFilter-Discriminants4.eps");
   C4.SaveAs("HcalNoise-FitBasedFilter-Discriminants4.pdf");

   FM.Close();
   FS.Close();

   return 0;
}

void PrepareHistogram(TH2D *H, string Label)
{
   if(H == NULL)
      return;

   H->SetTitle("");
   H->SetStats(0);
   H->GetXaxis()->SetTitle(Label.c_str());
   H->GetYaxis()->SetTitle("Total charge (fC)");
   H->GetXaxis()->SetTitleOffset(1.1);
   H->GetYaxis()->SetTitleOffset(1.4);
   H->GetXaxis()->SetTitleSize(0.035);
   H->GetYaxis()->SetTitleSize(0.035);
   H->GetZaxis()->SetTitleSize(0.035);
   H->GetXaxis()->SetLabelSize(0.035);
   H->GetYaxis()->SetLabelSize(0.035);
   H->GetZaxis()->SetLabelSize(0.035);
   H->GetXaxis()->SetLabelFont(42);
   H->GetYaxis()->SetLabelFont(42);
   H->GetZaxis()->SetLabelFont(42);
   H->GetXaxis()->SetTitleFont(42);
   H->GetYaxis()->SetTitleFont(42);
   H->GetZaxis()->SetTitleFont(42);
}




