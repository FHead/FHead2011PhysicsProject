#include <string>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"

void MakeYieldPlot(string RootFile = "ResultTable.root")
{
   gROOT->SetStyle("Plain");
   // TStyle gStyle;
   gStyle->SetPaintTextFormat(".3g");

   TFile F(RootFile.c_str());

   TH2D *HCalo = (TH2D *)F.Get("HAbsoluteYieldTable_Calo");
   TH2D *HUncorrectedCalo = (TH2D *)F.Get("HAbsoluteYieldTable_UncorrectedCalo");
   TH2D *HPF = (TH2D *)F.Get("HAbsoluteYieldTable_PF");
   TH2D *HTrack = (TH2D *)F.Get("HAbsoluteYieldTable_Track");

   HCalo->SetMarkerSize(3);
   HUncorrectedCalo->SetMarkerSize(3);
   HPF->SetMarkerSize(3);
   HTrack->SetMarkerSize(3);

   HCalo->GetYaxis()->SetRangeUser(2, 5);
   HUncorrectedCalo->GetYaxis()->SetRangeUser(2, 5);
   HPF->GetYaxis()->SetRangeUser(2, 5);
   HTrack->GetYaxis()->SetRangeUser(2, 5);

   TCanvas canvas("canvas", "canvas", 0, 0, 1024, 768);

   canvas.Divide(2, 2);

   canvas.cd(1);
   HCalo->Draw("text0");
   
   canvas.cd(2);
   HUncorrectedCalo->Draw("text0");
   
   canvas.cd(3);
   HPF->Draw("text0");
   
   canvas.cd(4);
   HTrack->Draw("text0");

   canvas.SaveAs("JetYield.png");
   canvas.SaveAs("JetYield.C");
   canvas.SaveAs("JetYield.eps");
}

