#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile F1("ScaledResult_001/PP6Dijet.root");
   TFile F2("ScaledResult_002/PP6Dijet.root");
   TFile F3("ScaledResult_004/PP6Dijet.root");
   TFile F4("ScaledResult_007/PP6Dijet.root");
   TFile F5("ScaledResult_010/PP6Dijet.root");

   TH1D *H1 = (TH1D *)F1.Get("HNewSDMass");
   TH1D *H2 = (TH1D *)F2.Get("HNewSDMass");
   TH1D *H3 = (TH1D *)F3.Get("HNewSDMass");
   TH1D *H4 = (TH1D *)F4.Get("HNewSDMass");
   TH1D *H5 = (TH1D *)F5.Get("HNewSDMass");

   TCanvas Canvas;

   H1->SetLineColor(kBlack);
   H2->SetLineColor(kRed);
   H3->SetLineColor(kBlue);
   H4->SetLineColor(kGreen);
   H5->SetLineColor(kYellow + 3);

   H1->Rebin(2);
   H2->Rebin(2);
   H3->Rebin(2);
   H4->Rebin(2);
   H5->Rebin(2);

   H1->SetTitle("");
   H1->SetStats(0);

   H1->Draw();
   H2->Draw("same");
   H3->Draw("same");
   H4->Draw("same");
   H5->Draw("same");

   TLegend Legend(0.4, 0.8, 0.7, 0.5);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(H1, "Ghost area = 0.01 ^{2}", "l");
   Legend.AddEntry(H2, "Ghost area = 0.02 ^{2}", "l");
   Legend.AddEntry(H3, "Ghost area = 0.04 ^{2}", "l");
   Legend.AddEntry(H4, "Ghost area = 0.07 ^{2}", "l");
   Legend.AddEntry(H5, "Ghost area = 0.10 ^{2}", "l");
   Legend.Draw();

   Canvas.SaveAs("15633_PPSmearingToys_GhostAreaComparison.png");
   Canvas.SaveAs("15633_PPSmearingToys_GhostAreaComparison.C");
   Canvas.SaveAs("15633_PPSmearingToys_GhostAreaComparison.eps");
   Canvas.SaveAs("15633_PPSmearingToys_GhostAreaComparison.pdf");

   F5.Close();
   F4.Close();
   F3.Close();
   F2.Close();
   F1.Close();

   return 0;
}





