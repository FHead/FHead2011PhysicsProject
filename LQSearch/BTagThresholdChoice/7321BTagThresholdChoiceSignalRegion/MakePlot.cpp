#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetStyle();

   TFile FLQ("LQ350.root");
   TFile FW("WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root");

   TH1D *HLQ = (TH1D *)FLQ.Get("HYieldPassTCHELTCHEL");
   TH1D *HW = (TH1D *)FW.Get("HYieldPassTCHELTCHEL");

   TCanvas C("C", "C", 1024, 1024);

   TH1D HWorld("HWorld", "", 1, 0, 200);
   HWorld.SetMinimum(0);
   HWorld.SetMaximum(200);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetTitle("Jet PT threshold (GeV/c)");
   HWorld.GetYaxis()->SetTitle("Yield remaining after requiring b-tagging (a.u.)");

   HWorld.Draw();

   HLQ->SetLineWidth(2);
   HLQ->SetLineColor(kBlue);
   
   HW->SetLineWidth(2);
   HW->SetLineColor(kRed);

   HLQ->Draw("same");
   HW->Draw("same");

   TLegend Legend(0.25, 0.85, 0.85, 0.7);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(HLQ, "LQ with M_{LQ} = 350 GeV/c^{2}", "l");
   Legend.AddEntry(HW, "W + jets", "l");
   Legend.Draw();

   AddCMSSimulation(0.1, 0.92);

   C.SaveAs("BTagThreshold.png");
   C.SaveAs("BTagThreshold.C");
   C.SaveAs("BTagThreshold.eps");
   C.SaveAs("BTagThreshold.pdf");

   FW.Close();
   FLQ.Close();

   return 0;
}





