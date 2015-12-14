#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   // SetStyle();

   TFile FTTbar("TTbar.root");
   TFile FQCD("QCDAll.root");

   TH1D *HQCDR010 = (TH1D *)FQCD.Get("HMRNew_R2New010");
   TH1D *HQCDR020 = (TH1D *)FQCD.Get("HMRNew_R2New020");
   TH1D *HTTbarR010 = (TH1D *)FTTbar.Get("HMRNew_R2New010");
   TH1D *HTTbarR020 = (TH1D *)FTTbar.Get("HMRNew_R2New020");

   HQCDR010->SetStats(0);
   HQCDR020->SetStats(0);
   HTTbarR010->SetStats(0);
   HTTbarR020->SetStats(0);

   HQCDR010->SetLineColor(kBlue);
   HQCDR020->SetLineColor(kBlue);
   HTTbarR010->SetLineColor(kRed);
   HTTbarR020->SetLineColor(kRed);
   
   HQCDR010->SetLineWidth(2);
   HQCDR020->SetLineWidth(2);
   HTTbarR010->SetLineWidth(2);
   HTTbarR020->SetLineWidth(2);

   HQCDR010->GetXaxis()->SetTitle("MR");
   HQCDR020->GetXaxis()->SetTitle("MR");

   TLegend legend(0.6, 0.8, 0.8, 0.6);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(HQCDR010, "QCD", "l");
   legend.AddEntry(HTTbarR010, "TTbar", "l");

   TCanvas C1("C1", "C1", 1024, 1024);
   HQCDR010->SetTitle("MR, R^{2} > 0.10");
   HQCDR010->SetMinimum(0.3);
   HQCDR010->Draw();
   HTTbarR010->Draw("same");
   C1.SetLogy();
   legend.Draw();
   C1.SaveAs("ComparisonR010.png");
   C1.SaveAs("ComparisonR010.C");
   C1.SaveAs("ComparisonR010.eps");
   C1.SaveAs("ComparisonR010.pdf");
   
   TCanvas C2("C2", "C2", 1024, 1024);
   HQCDR020->SetTitle("MR, R^{2} > 0.20");
   HQCDR020->SetMinimum(0.3);
   HQCDR020->Draw();
   HTTbarR020->Draw("same");
   legend.Draw();
   C2.SetLogy();
   C2.SaveAs("ComparisonR020.png");
   C2.SaveAs("ComparisonR020.C");
   C2.SaveAs("ComparisonR020.eps");
   C2.SaveAs("ComparisonR020.pdf");

   HQCDR020->Scale(1.0 / HQCDR020->Integral(21, 40));
   HTTbarR020->Scale(1.0 / HTTbarR020->Integral(21, 40));

   TCanvas C3("C3", "C3", 1024, 1024);
   HQCDR020->SetTitle("MR, R^{2} > 0.20, tail-normalized");
   HQCDR020->GetYaxis()->SetTitle("a.u.");
   HQCDR020->SetMinimum(0.001);
   HQCDR020->Draw();
   HTTbarR020->Draw("same");
   legend.Draw();
   C3.SetLogy();
   C3.SaveAs("TailNormalizedR020.png");
   C3.SaveAs("TailNormalizedR020.C");
   C3.SaveAs("TailNormalizedR020.eps");
   C3.SaveAs("TailNormalizedR020.pdf");
   
   FQCD.Close();
   FTTbar.Close();

   return 0;
}





