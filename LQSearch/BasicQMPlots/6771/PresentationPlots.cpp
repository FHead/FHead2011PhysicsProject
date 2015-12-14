#include "TROOT.h"
#include "TFile.h"
#include "TStyle.h"

#include "SetStyle.h"
#include "SlidePreparationHelper.h"

int main()
{
   SetStyle();

   TFile FLQ450("Samples/LQ450_LQ3Tree.root");
   TFile FTTbar("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_all.root");

   CreateTwoPanelPlot(
      PlotRecord(&FLQ450, "HCaloMRStarVsRStar", "Razor variables for LQ (450 GeV)", "MR*", "R*", "", "colz"),
      PlotRecord(&FTTbar, "HCaloMRStarVsRStar", "Razor variables for TTbar", "MR*", "R*", "", "colz"),
      "CaloMRStarVsRStar_SignalTTbarComparison");

   FTTbar.Close();
   FLQ450.Close();
}


