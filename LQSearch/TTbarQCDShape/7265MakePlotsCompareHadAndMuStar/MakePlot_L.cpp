#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

int main()
{
   TFile FHad("Had.root");
   TFile FMu("MuStar.root");

   TH1D *HHad1 = (TH1D *)FHad.Get("HMRNew_R2New015_L");
   TH1D *HMu1 = (TH1D *)FMu.Get("HMRNew_R2New015_L");
   TH1D *HHad2 = (TH1D *)FHad.Get("HMRNew_R2New025_L");
   TH1D *HMu2 = (TH1D *)FMu.Get("HMRNew_R2New025_L");
   TH1D *HHad3 = (TH1D *)FHad.Get("HR2New_MRNew400_L");
   TH1D *HMu3 = (TH1D *)FMu.Get("HR2New_MRNew400_L");
   TH1D *HHad4 = (TH1D *)FHad.Get("HR2New_MRNew500_L");
   TH1D *HMu4 = (TH1D *)FMu.Get("HR2New_MRNew500_L");

   TLegend legend(0.6, 0.9, 0.9, 0.7);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(HHad1, "Signal selection", "l");
   legend.AddEntry(HMu1, "Muon selection", "l");

   HHad1->SetStats(0);
   HMu1->SetStats(0);
   HHad2->SetStats(0);
   HMu2->SetStats(0);
   HHad3->SetStats(0);
   HMu3->SetStats(0);
   HHad4->SetStats(0);
   HMu4->SetStats(0);

   HHad1->SetLineColor(kBlue);
   HMu1->SetLineColor(kRed);
   HHad2->SetLineColor(kBlue);
   HMu2->SetLineColor(kRed);
   HHad3->SetLineColor(kBlue);
   HMu3->SetLineColor(kRed);
   HHad4->SetLineColor(kBlue);
   HMu4->SetLineColor(kRed);

   HHad1->SetLineWidth(2);
   HMu1->SetLineWidth(2);
   HHad2->SetLineWidth(2);
   HMu2->SetLineWidth(2);
   HHad3->SetLineWidth(2);
   HMu3->SetLineWidth(2);
   HHad4->SetLineWidth(2);
   HMu4->SetLineWidth(2);

   TCanvas C1("C1", "C1", 1024, 1024);
   HMu1->SetTitle("MR, R^{2} > 0.15 (single loose tag)");
   HMu1->GetXaxis()->SetTitle("MR");
   HMu1->Draw("");
   HHad1->Draw("same");
   legend.Draw();
   C1.SetLogy();
   C1.SaveAs("Plot1L.png");
   C1.SaveAs("Plot1L.C");
   C1.SaveAs("Plot1L.eps");
   C1.SaveAs("Plot1L.pdf");

   TCanvas C2("C2", "C2", 1024, 1024);
   HMu2->SetTitle("MR, R^{2} > 0.25 (single loose tag)");
   HMu2->GetXaxis()->SetTitle("MR");
   HMu2->Draw("");
   HHad2->Draw("same");
   legend.Draw();
   C2.SetLogy();
   C2.SaveAs("Plot2L.png");
   C2.SaveAs("Plot2L.C");
   C2.SaveAs("Plot2L.eps");
   C2.SaveAs("Plot2L.pdf");

   TCanvas C3("C3", "C3", 1024, 1024);
   HMu3->SetTitle("R^{2}, MR > 400 (single loose tag)");
   HMu3->GetXaxis()->SetTitle("R^{2}");
   HMu3->Scale(1.0 / HMu3->Integral(8, 999));
   HMu3->Draw("");
   HHad3->Scale(1.0 / HHad3->Integral(8, 999));
   HHad3->Draw("same");
   legend.Draw();
   C3.SetLogy();
   C3.SaveAs("Plot3L.png");
   C3.SaveAs("Plot3L.C");
   C3.SaveAs("Plot3L.eps");
   C3.SaveAs("Plot3L.pdf");
   
   TCanvas C4("C4", "C4", 1024, 1024);
   HMu4->SetTitle("R^{2}, MR > 500 (single loose tag)");
   HMu4->GetXaxis()->SetTitle("R^{2}");
   HMu4->Scale(1.0 / HMu4->Integral(8, 999));
   HMu4->Draw("");
   HHad4->Scale(1.0 / HHad4->Integral(8, 999));
   HHad4->Draw("same");
   legend.Draw();
   C4.SetLogy();
   C4.SaveAs("Plot4L.png");
   C4.SaveAs("Plot4L.C");
   C4.SaveAs("Plot4L.eps");
   C4.SaveAs("Plot4L.pdf");

   FMu.Close();
   FHad.Close();

   return 0;
}






