#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "TH1D.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TROOT.h"
#include "TColor.h"
#include "TStyle.h"

#include "PlotHelper2.h"
#include "DataHelper.h"
#include "SlidePreparationHelper.h"
#include "SetStyle.h"

int main()
{
   SetStyle();

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   gStyle->SetOptFit(111);
  
   TGraph RealA;
   TGraph RealB;

   RealA.SetPoint(0, 0, 0.00452278);
   RealA.SetPoint(1, 100000, 0.00452278);
   RealB.SetPoint(0, 0, 0.0526323);
   RealB.SetPoint(1, 100000, 0.0526323);

   DataHelper Original("Summary.dh");

   TFile FOriginal("ResultPlots.root");

   CreateTwoByTwoPanelPlot(
      PlotRecord(&FOriginal, "HParameterA1Pull", "Pull on A1", "", "", ""),
      PlotRecord(&FOriginal, "HParameterB1Pull", "Pull on B1", "", "", ""),
      PlotRecord(&FOriginal, "HParameterA2Pull", "Pull on A2", "", "", ""),
      PlotRecord(&FOriginal, "HParameterB2Pull", "Pull on B2", "", "", ""),
      "ParameterABPull"
   );
   
   FOriginal.Close();

   return 0;
}







