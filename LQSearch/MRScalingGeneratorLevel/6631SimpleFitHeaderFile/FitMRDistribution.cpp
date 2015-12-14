#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "MRFitHelperFunctions.h"
#include "PlotHelper2.h"

struct SingleFitResult;
int main(int argc, char *argv[]);
void FitWithRCut(PsFileHelper &PsFile, string Filename, vector<double> RCuts);

int main(int argc, char *argv[])
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

   PsFileHelper PsFile("DevelopFit.ps");
   PsFile.AddTextPage("Developing MR scaling fit (simultaneous)");

   // vector<string> Explanations;
   // Explanations.push_back("");
   // PsFile.AddTextPage(Explanations);

   TGraphErrors SGraph2;
   SGraph2.SetNameTitle("SGraph2", "Exponent summary plot (cov. qual = 2)");
   int PointCount2 = 0;
   
   TGraphErrors SGraph3;
   SGraph3.SetNameTitle("SGraph3", "Exponent summary plot (cov. qual = 3)");
   int PointCount3 = 0;
   
   TGraphErrors SGraphOther;
   SGraphOther.SetNameTitle("SGraphOther", "Exponent summary plot (cov. qual != 2, 3)");
   int PointCountOther = 0;

   for(double RCut = 0.20; RCut <= 0.75; RCut = RCut + 0.001)
   {
      MRFitSingleFitResult result = FitWithRCut(&PsFile, "TTbar_MRTree.root", RCut, "MRTree", "MR", "R",
         150, 1500, MRFit_Strategy_Normal, false, true);

      if(result.CovQual == 2)
      {
         SGraph2.SetPoint(PointCount2, RCut * RCut, -result.S);
         SGraph2.SetPointError(PointCount2, 0, result.SError);
         PointCount2 = PointCount2 + 1;
      }
      else if(result.CovQual == 3 && fabs(result.SError / result.S) > 0.005)
      {
         SGraph3.SetPoint(PointCount3, RCut * RCut, -result.S);
         SGraph3.SetPointError(PointCount3, 0, result.SError);
         PointCount3 = PointCount3 + 1;
      }
      else
      {
         SGraphOther.SetPoint(PointCountOther, RCut * RCut, -result.S);
         SGraphOther.SetPointError(PointCountOther, 0, result.SError);
         PointCountOther = PointCountOther + 1;
      }
   }

   PsFile.AddTextPage("Summary graphs");
   PsFile.AddPlot(SGraph2, "ap");
   PsFile.AddPlot(SGraph3, "ap");
   PsFile.AddPlot(SGraphOther, "ap");

   TF1 MegaFit("MegaFit", "pol1");
   SGraph3.Fit(&MegaFit);
   PsFile.AddPlot(SGraph3, "ap");

   TH1D HPull("HPull", "Pull distribution of the fit", 100, -10, 10);

   TGraphErrors RatioGraph;
   RatioGraph.SetNameTitle("RatioGraph", "Ratio of point to line");
   for(int i = 0; i < SGraph3.GetN(); i++)
   {
      double x = 0, y = 0;
      SGraph3.GetPoint(i, x, y);
      RatioGraph.SetPoint(i, x, y / MegaFit.Eval(x));
      RatioGraph.SetPointError(i, 0, SGraph3.GetErrorY(i) / fabs(MegaFit.Eval(x)));

      HPull.Fill((y - MegaFit.Eval(x)) / SGraph3.GetErrorY(i));
   }
   RatioGraph.SetLineWidth(2);
   PsFile.AddPlot(RatioGraph, "ap");

   PsFile.AddPlot(HPull, "", false);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

