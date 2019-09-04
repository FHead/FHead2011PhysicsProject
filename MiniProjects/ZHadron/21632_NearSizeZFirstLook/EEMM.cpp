#include <iostream>
#include <cmath>
using namespace std;

#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);
   string EEFile = CL.Get("EE", "PlotsEE.root");
   string MMFile = CL.Get("MM", "PlotsMM.root");
   string Histogram = CL.Get("Histogram", "HDPhiCent0030Subtracted");
   string Output = CL.Get("Output", "Meow.pdf");

   TFile FEE(EEFile.c_str());
   TFile FMM(MMFile.c_str());

   TH1D *HEE = (TH1D *)FEE.Get(Histogram.c_str());
   TH1D *HMM = (TH1D *)FMM.Get(Histogram.c_str());

   TH2D HWorld("HWorld", ";#Delta#phi_{trkZ} = |#phi^{trk} - #phi^{Z}|;Normalized per Z", 100, 0, M_PI, 100, 0, 25);
   HWorld.SetStats(0);

   HEE->SetMarkerStyle(20);
   HEE->SetMarkerSize(2);
   HEE->SetMarkerColor(kBlue);
   HEE->SetLineColor(kBlue);
   HMM->SetMarkerStyle(20);
   HMM->SetMarkerSize(2);
   HMM->SetMarkerColor(kBlack);
   HMM->SetLineColor(kBlack);

   TLegend Legend(0.15, 0.25, 0.70, 0.80);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(HEE);

   TCanvas Canvas;

   HWorld.Draw("AXIS");
   HEE->Draw("SAME");
   HMM->Draw("SAME");
   // HEE->Draw("SAME");
   // HMM->Draw("SAME");

   Canvas.SaveAs(Output.c_str());
}



