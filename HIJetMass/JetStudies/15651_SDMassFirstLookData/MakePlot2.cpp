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

   TFile FPAData285530("Output-285530.root");

   TTree *PATree285530 = (TTree *)FPAData285530.Get("Tree");

   TFile FPP8("ScaledResult2/PP8Dijet.root");
   TFile FAA8("ScaledResult2/AA8Dijet.root");

   TTree *TPP = (TTree *)FPP8.Get("Tree");
   TTree *TAA = (TTree *)FAA8.Get("Tree");

   TPP->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   TPP->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   TPP->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   TPP->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   TPP->SetAlias("Baseline", "(JetShift < 0.05 && NewJetPT/JetPT > 0.8 && JetSDZG > 0)");
   TAA->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   TAA->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   TAA->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   TAA->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   TAA->SetAlias("Baseline", "(JetShift < 0.05 && NewJetPT/JetPT > 0.8 && JetSDZG > 0)");

   TH1D HPP("HPP", ";;", 50, 0, 0.5);
   TH1D HAA("HAA", ";;", 50, 0, 0.5);

   TAA->Draw("SDMass[7]/NewJetPT>>HAA", "MCWeight * (Baseline && NewJetPT > 120 && SDRecoDR[7] > 0.1)");
   TPP->Draw("SDMass[7]/NewJetPT>>HPP", "MCWeight * (Baseline && NewJetPT > 120 && SDRecoDR[7] > 0.1)");

   HPP.Scale(1 / HPP.Integral());
   HAA.Scale(1 / HAA.Integral());

   TCanvas Canvas;

   double BinSize = 1;
   
   TH1D HTemp285530("HTemp285530", "z_{cut} = 0.5, #beta = 1.5;Soft drop mass / jet PT;", 50, 0, 0.5);
   HTemp285530.SetStats(0);
   HTemp285530.Sumw2();
   HTemp285530.SetMarkerStyle(8);
   HTemp285530.SetMarkerColor(kCyan);
   HTemp285530.SetLineColor(kCyan);
   // PATree285530->Draw("JetSDMass/JetConePT>>HTemp285530", "(JetConePT > 120 && JetRecoDR > 0.1)", "");
   PATree285530->Draw("JetSDMass2/JetPT>>HTemp285530", "(JetPT > 120 && JetRecoDR2 > 0.1)", "");
   
   HTemp285530.Draw("same");

   HPP.Scale(HTemp285530.Integral() * BinSize);
   HAA.Scale(HTemp285530.Integral() * BinSize);
   HPP.Draw("same hist");
   HAA.Draw("same hist");

   HPP.SetLineColor(kRed);
   HAA.SetLineColor(kBlue);

   TLegend Legend(0.35, 0.80, 0.65, 0.60);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&HTemp285530, "PAEGJet (Prompt 285530)", "pl");
   Legend.AddEntry(&HPP, "pp dijet", "l");
   Legend.AddEntry(&HAA, "AA dijet", "l");
   Legend.Draw();

   Canvas.SaveAs("FirstComparison4.png");
   Canvas.SaveAs("FirstComparison4.C");
   Canvas.SaveAs("FirstComparison4.eps");
   Canvas.SaveAs("FirstComparison4.pdf");

   TH1D HTemp2("HTemp2", ";Soft drop mass / jet PT;", 50, 0, 0.5);
   for(int i = 1; i <= 50; i++)
      HTemp2.SetBinContent(i, HAA.GetBinContent(i));

   HTemp285530.Divide(&HTemp2);

   HTemp285530.SetMinimum(0.1);
   HTemp285530.SetMaximum(10);

   HTemp285530.Draw();

   TGraph G;
   G.SetPoint(0, 0, 1);
   G.SetPoint(1, 100, 1);
   G.Draw("l");

   HTemp285530.GetYaxis()->SetTitle("Data / pythia");

   Canvas.SetLogy();

   Canvas.SaveAs("FirstComparisonRatio4.png");
   Canvas.SaveAs("FirstComparisonRatio4.C");
   Canvas.SaveAs("FirstComparisonRatio4.eps");
   Canvas.SaveAs("FirstComparisonRatio4.pdf");
   
   return 0;
}

