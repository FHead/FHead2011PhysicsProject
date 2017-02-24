#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile FPAData285216("Output-285216.root");
   TFile FPAData285530("Output-285530.root");

   TTree *PATree285216 = (TTree *)FPAData285216.Get("Tree");
   TTree *PATree285530 = (TTree *)FPAData285530.Get("Tree");

   TFile FPP6("ScaledResult/PP6Dijet.root");
   TFile FPP8("ScaledResult/PP8Dijet.root");

   TH1D *H6PT = (TH1D *)FPP6.Get("HSDMass_CBin0_PTBin2");
   TH1D *H8PT = (TH1D *)FPP8.Get("HSDMass_CBin0_PTBin2");

   cout << H6PT->GetTitle() << endl;

   H6PT->Scale(1 / H6PT->Integral() / 0.5);   // 0.5 is bin size
   H8PT->Scale(1 / H8PT->Integral() / 0.5);

   TCanvas Canvas;

   double BinSize = 1;
   TH1D HTemp285216("HTemp285216", ";Soft drop mass;", 50, 0, 50);
   HTemp285216.SetStats(0);
   HTemp285216.Sumw2();
   HTemp285216.SetMarkerStyle(8);
   HTemp285216.SetMarkerColor(kBlack);
   HTemp285216.SetLineColor(kBlack);
   PATree285216->Draw("JetSDMass>>HTemp285216", "(JetConePT - 2 > 120 && JetConePT - 2 < 140 && JetRecoDR > 0.1 && Lumi > 40)", "");
   
   TH1D HTemp285530("HTemp285530", ";Soft drop mass;", 50, 0, 50);
   HTemp285530.SetStats(0);
   HTemp285530.Sumw2();
   HTemp285530.SetMarkerStyle(8);
   HTemp285530.SetMarkerColor(kCyan);
   HTemp285530.SetLineColor(kCyan);
   PATree285530->Draw("JetSDMass>>HTemp285530", "(JetConePT > 120 && JetConePT < 140 && JetRecoDR > 0.1 && Lumi > 40)", "same");
   
   // HTemp285530.Scale(HTemp285216.Integral() / HTemp285530.GetEntries());
   // HTemp285216.Scale(HTemp285530.GetEntries() / HTemp285216.GetEntries());

   HTemp285216.Draw();
   // HTemp285530.Draw("same");

   H6PT->Scale(HTemp285216.Integral() * BinSize);
   H8PT->Scale(HTemp285216.Integral() * BinSize);
   H6PT->Draw("same hist");
   H8PT->Draw("same hist");

   H6PT->SetLineColor(kRed);
   H8PT->SetLineColor(kBlue);

   TLegend Legend(0.35, 0.80, 0.65, 0.60);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&HTemp285216, "PAEGJet (Prompt 285216)", "pl");
   // Legend.AddEntry(&HTemp285530, "PAEGJet (Prompt 285530)", "pl");
   Legend.AddEntry(H6PT, "Pythia 6 Dijet", "l");
   Legend.AddEntry(H8PT, "Pythia 8 Dijet", "l");
   Legend.Draw();

   Canvas.SaveAs("FirstComparison.png");
   Canvas.SaveAs("FirstComparison.C");
   Canvas.SaveAs("FirstComparison.eps");
   Canvas.SaveAs("FirstComparison.pdf");

   H8PT->Rebin(2 * BinSize);
   H8PT->Scale(0.5 / BinSize);

   TH1D HTemp2("HTemp2", ";Soft drop mass;", 50, 0, 50);
   for(int i = 1; i <= 50; i++)
      HTemp2.SetBinContent(i, H8PT->GetBinContent(i));

   HTemp285216.Divide(&HTemp2);
   HTemp285530.Divide(&HTemp2);

   HTemp285216.SetMinimum(0.1);
   HTemp285216.SetMaximum(10);

   HTemp285216.Draw();
   // HTemp285530.Draw("same");

   TGraph G;
   G.SetPoint(0, 0, 1);
   G.SetPoint(1, 100, 1);
   G.Draw("l");

   HTemp285216.GetYaxis()->SetTitle("Data / pythia8");

   Canvas.SetLogy();

   Canvas.SaveAs("FirstComparisonRatio.png");
   Canvas.SaveAs("FirstComparisonRatio.C");
   Canvas.SaveAs("FirstComparisonRatio.eps");
   Canvas.SaveAs("FirstComparisonRatio.pdf");
   
   return 0;
}

