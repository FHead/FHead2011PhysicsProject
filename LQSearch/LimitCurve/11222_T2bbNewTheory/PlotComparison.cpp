#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TFile.h"
#include "TH1D.h"

int main()
{
   TFile FLQ("Graphs.root");
   TFile FSMS("Histograms.root");

   TGraph *GLQ = (TGraph *)FLQ.Get("Expected");
   TGraph *GT2bb50 = (TGraph *)FSMS.Get("GExpectedNeutralino50");
   TGraph *GT2bb75 = (TGraph *)FSMS.Get("GExpectedNeutralino75");
   TGraph *GT2bb100 = (TGraph *)FSMS.Get("GExpectedNeutralino100");

   TH1D HWorld("HWorld",
      "Comparison of LQ limits and T2bb limits;LQ or sbottom mass (GeV);Expected limit on cross section (pb)",
      100, 220, 570);
   HWorld.SetStats(0);
   HWorld.SetMinimum(0.15);
   HWorld.SetMaximum(7);

   GLQ->SetLineWidth(2);
   GLQ->SetLineColor(kBlue);
   GLQ->SetMarkerColor(kBlue);
   GLQ->SetMarkerStyle(20);
   GLQ->SetMarkerSize(1.4);

   GT2bb50->SetLineWidth(2);
   GT2bb50->SetLineColor(kMagenta);
   GT2bb50->SetMarkerColor(kMagenta);
   GT2bb50->SetMarkerStyle(20);
   GT2bb50->SetMarkerSize(1.4);
   
   GT2bb75->SetLineWidth(2);
   GT2bb75->SetLineColor(kRed);
   GT2bb75->SetMarkerColor(kRed);
   GT2bb75->SetMarkerStyle(20);
   GT2bb75->SetMarkerSize(1.4);
   
   GT2bb100->SetLineWidth(2);
   GT2bb100->SetLineColor(kBlack);
   GT2bb100->SetMarkerColor(kBlack);
   GT2bb100->SetMarkerStyle(20);
   GT2bb100->SetMarkerSize(1.4);

   TCanvas C("C", "C", 1024, 1024);
   HWorld.Draw();
   GLQ->Draw("pl");
   GT2bb50->Draw("pl");
   GT2bb75->Draw("pl");
   GT2bb100->Draw("pl");

   TLegend Legend(0.35, 0.65, 0.85, 0.85);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(GLQ, "LQ3 (neutrino mass = 0 GeV)", "lp");
   Legend.AddEntry(GT2bb50, "Neutralino mass = 50 GeV", "lp");
   Legend.AddEntry(GT2bb75, "Neutralino mass = 75 GeV", "lp");
   Legend.AddEntry(GT2bb100, "Neutralino mass = 100 GeV", "lp");
   Legend.Draw();

   C.SetLogy();
   C.SaveAs("ComparisonOfLQAndT2bb.png");
   C.SaveAs("ComparisonOfLQAndT2bb.C");
   C.SaveAs("ComparisonOfLQAndT2bb.eps");
   C.SaveAs("ComparisonOfLQAndT2bb.pdf");

   FSMS.Close();
   FLQ.Close();

   return 0;
}




