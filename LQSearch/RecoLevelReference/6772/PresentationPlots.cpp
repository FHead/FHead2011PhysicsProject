#include "TFile.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TROOT.h"

#include "SlidePreparationHelper.h"

int main()
{
   gStyle->SetFrameBorderMode(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadColor(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetStatColor(0);
   gStyle->SetFillColor(0);

   gStyle->SetPaperSize(20,26);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadRightMargin(0.05);
   gStyle->SetPadBottomMargin(0.16);
   gStyle->SetPadLeftMargin(0.12);

   gStyle->SetTextFont(132);
   gStyle->SetTextSize(0.08);
   gStyle->SetLabelFont(132,"x");
   gStyle->SetLabelFont(132,"y");
   gStyle->SetLabelFont(132,"z");
   gStyle->SetLabelSize(0.05,"x");
   gStyle->SetTitleSize(0.06,"x");
   gStyle->SetLabelSize(0.05,"y");
   gStyle->SetTitleSize(0.06,"y");
   gStyle->SetLabelSize(0.05,"z");
   gStyle->SetTitleSize(0.06,"z");

   gStyle->SetMarkerStyle(20);
   gStyle->SetHistLineWidth(1.85);
   // gStyle->SetHistLineWidth(3.85);
   gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

   gStyle->SetErrorX(0.001);

   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);

   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);

   gROOT->SetStyle("Plain");
   gStyle->SetOptStat(1100);
   gStyle->SetOptStat(1);
   gStyle->SetOptFit(1111);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);

   TFile F("LQ450_Histograms.root");

   CreateTwoPanelPlot(
      PlotRecord(&F, "HLeadingAK5JetPT", "Leading Calo Jet PT", "PT (GeV)", "", "", "", true),
      PlotRecord(&F, "HCaloMET", "Calo MET", "MET (GeV)", "", "", "", true),
      "PTAndMETFromSignalSample");

   F.Close();
}


