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

int main()
{
   gROOT->SetStyle("Plain");

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

   double EventCount = 17594;

   TGraphErrors ParameterA;
   TGraphErrors ParameterB;
   TGraphErrors ParameterAError;
   TGraphErrors ParameterBError;

   DataHelper Quarter("Quarter/Summary.dh");
   DataHelper Half("Half/Summary.dh");
   DataHelper Original("Original/Summary.dh");
   DataHelper Double("Double/Summary.dh");

   TFile FQuarter("Quarter/ResultPlots.root");
   TFile FHalf("Half/ResultPlots.root");
   TFile FOriginal("Original/ResultPlots.root");
   TFile FDouble("Double/ResultPlots.root");

   ParameterA.SetPoint(0, EventCount / 4, Quarter["A"]["Mean"].GetDouble());
   ParameterA.SetPointError(0, 0, Quarter["A"]["Sigma"].GetDouble());
   ParameterA.SetPoint(1, EventCount / 2, Half["A"]["Mean"].GetDouble());
   ParameterA.SetPointError(1, 0, Half["A"]["Sigma"].GetDouble());
   ParameterA.SetPoint(2, EventCount, Original["A"]["Mean"].GetDouble());
   ParameterA.SetPointError(2, 0, Original["A"]["Sigma"].GetDouble());
   ParameterA.SetPoint(3, EventCount * 2, Double["A"]["Mean"].GetDouble());
   ParameterA.SetPointError(3, 0, Double["A"]["Sigma"].GetDouble());
   ParameterA.SetLineWidth(2);
   
   ParameterB.SetPoint(0, EventCount / 4, Quarter["B"]["Mean"].GetDouble());
   ParameterB.SetPointError(0, 0, Quarter["B"]["Sigma"].GetDouble());
   ParameterB.SetPoint(1, EventCount / 2, Half["B"]["Mean"].GetDouble());
   ParameterB.SetPointError(1, 0, Half["B"]["Sigma"].GetDouble());
   ParameterB.SetPoint(2, EventCount, Original["B"]["Mean"].GetDouble());
   ParameterB.SetPointError(2, 0, Original["B"]["Sigma"].GetDouble());
   ParameterB.SetPoint(3, EventCount * 2, Double["B"]["Mean"].GetDouble());
   ParameterB.SetPointError(3, 0, Double["B"]["Sigma"].GetDouble());
   ParameterB.SetLineWidth(2);
   
   ParameterAError.SetPoint(0, EventCount / 4, Quarter["AError"]["Sigma"].GetDouble());
   ParameterAError.SetPointError(0, 0, Quarter["AError"]["SigmaError"].GetDouble());
   ParameterAError.SetPoint(1, EventCount / 2, Half["AError"]["Sigma"].GetDouble());
   ParameterAError.SetPointError(1, 0, Half["AError"]["SigmaError"].GetDouble());
   ParameterAError.SetPoint(2, EventCount, Original["AError"]["Sigma"].GetDouble());
   ParameterAError.SetPointError(2, 0, Original["AError"]["SigmaError"].GetDouble());
   ParameterAError.SetPoint(3, EventCount * 2, Double["AError"]["Sigma"].GetDouble());
   ParameterAError.SetPointError(3, 0, Double["AError"]["SigmaError"].GetDouble());
   ParameterAError.SetLineWidth(2);
   
   ParameterBError.SetPoint(0, EventCount / 4, Quarter["BError"]["Sigma"].GetDouble());
   ParameterBError.SetPointError(0, 0, Quarter["BError"]["SigmaError"].GetDouble());
   ParameterBError.SetPoint(1, EventCount / 2, Half["BError"]["Sigma"].GetDouble());
   ParameterBError.SetPointError(1, 0, Half["BError"]["SigmaError"].GetDouble());
   ParameterBError.SetPoint(2, EventCount, Original["BError"]["Sigma"].GetDouble());
   ParameterBError.SetPointError(2, 0, Original["BError"]["SigmaError"].GetDouble());
   ParameterBError.SetPoint(3, EventCount * 2, Double["BError"]["Sigma"].GetDouble());
   ParameterBError.SetPointError(3, 0, Double["BError"]["SigmaError"].GetDouble());
   ParameterBError.SetLineWidth(2);

   CreateTwoByTwoPanelPlot(
      PlotList(
         PlotRecord(&ParameterA, "A", "Statistics", "A", "", "ap", false, false, false, true),
         PlotRecord(&RealA, "", "", "", "", "l")),
      PlotList(
         PlotRecord(&ParameterB, "B", "Statistics", "B", "", "ap", false, false, false, true),
         PlotRecord(&RealB, "", "", "", "", "l")),
      PlotRecord(&ParameterAError, "Error on A", "Statistics", "A error", "", "ap", true, false, false, true),
      PlotRecord(&ParameterBError, "Error on B", "Statistics", "B error", "", "ap", true, false, false, true),
      "ParameterEvolution"
   );

   CreateTwoByTwoPanelPlot(
      PlotRecord(&FQuarter, "HParameterAPull", "Smallest statistics", "", "", ""),
      PlotRecord(&FHalf, "HParameterAPull", "Smaller statistics", "", "", ""),
      PlotRecord(&FOriginal, "HParameterAPull", "Medium statistics", "", "", ""),
      PlotRecord(&FDouble, "HParameterAPull", "Larger statistics", "", "", ""),
      "ParameterAPull"
   );
   
   CreateTwoByTwoPanelPlot(
      PlotRecord(&FQuarter, "HParameterBPull", "Smallest statistics", "", "", ""),
      PlotRecord(&FHalf, "HParameterBPull", "Smaller statistics", "", "", ""),
      PlotRecord(&FOriginal, "HParameterBPull", "Medium statistics", "", "", ""),
      PlotRecord(&FDouble, "HParameterBPull", "Larger statistics", "", "", ""),
      "ParameterBPull"
   );

   FDouble.Close();
   FOriginal.Close();
   FHalf.Close();
   FQuarter.Close();

   return 0;
}







