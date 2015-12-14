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
#include "DataHelper.h"

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

   string Tag = "";
   string InputFile = "";
   double MRMin = 100;
   if(argc >= 3)
   {
      Tag = argv[1];
      stringstream ExtractMin(argv[2]);
      ExtractMin >> MRMin;

      InputFile = Tag + "_MRTree_All.root";
   }
   else
   {
      cerr << "Usage: " << argv[0] << " Tag MinimumMR [DoDoubleExponential]" << endl;
      return -1;
   }
      
   bool DoubleExponential = false;
   if(argc >= 4 && string(argv[3]) == "--double")
      DoubleExponential = true;

   PsFileHelper PsFile("FitBackground_" + Tag + ".ps");
   PsFile.AddTextPage("Developing MR scaling fit (not simultaneous)");

   TGraphErrors SGraph2;
   SGraph2.SetNameTitle("SGraph2", "Exponent summary plot (cov. qual = 2)");
   int PointCount2 = 0;
   
   TGraphErrors SGraph3;
   SGraph3.SetNameTitle("SGraph3", "Exponent summary plot (cov. qual = 3)");
   int PointCount3 = 0;
   
   TGraphErrors SGraphOther;
   SGraphOther.SetNameTitle("SGraphOther", "Exponent summary plot (cov. qual != 2, 3)");
   int PointCountOther = 0;

   DataHelper DHFile("AllFitResults.dh");

   for(double RCut = 0.30; RCut <= 0.50; RCut = RCut + 0.01)
   {
      MRFitSingleFitResult result = FitWithRCut(&PsFile, InputFile, RCut, "MRTree", "MR", "R",
         MRMin, 1500, MRFit_Strategy_IgnoreGaussian, DoubleExponential, true, 3);

      if(result.CovQual == 2)
      {
         SGraph2.SetPoint(PointCount2, RCut * RCut, -result.S);
         SGraph2.SetPointError(PointCount2, 0, result.SError);
         PointCount2 = PointCount2 + 1;
      }
      else if(result.CovQual == 3 && fabs(result.SError / result.S) > 0.01)
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

      stringstream KeyPrefixStream;
      KeyPrefixStream << "RCut " << RCut << ", ";
      string KeyPrefix = KeyPrefixStream.str();

      DHFile[Tag][KeyPrefix + "S"] = result.S;
      DHFile[Tag][KeyPrefix + "SError"] = result.SError;
      DHFile[Tag][KeyPrefix + "CovQual"] = result.CovQual;
      DHFile[Tag][KeyPrefix + "DoubleExponential"] = "no";

      if(DoubleExponential == true)
      {
         DHFile[Tag][KeyPrefix + "S2"] = result.S2;
         DHFile[Tag][KeyPrefix + "S2Error"] = result.S2Error;
         DHFile[Tag][KeyPrefix + "Fraction"] = result.Fraction;
         DHFile[Tag][KeyPrefix + "FractionError"] = result.FractionError;
         DHFile[Tag][KeyPrefix + "DoubleExponential"] = "yes";
      }

      if(result.Strategy == MRFit_Strategy_Normal)
      {
         DHFile[Tag][KeyPrefix + "Strategy"] = "Normal";
         DHFile[Tag][KeyPrefix + "X0"] = result.X0;
         DHFile[Tag][KeyPrefix + "SigmaL"] = result.SigmaL;
         DHFile[Tag][KeyPrefix + "SigmaR"] = result.SigmaR;
      }
      if(result.Strategy == MRFit_Strategy_IgnoreLeft)
      {
         DHFile[Tag][KeyPrefix + "Strategy"] = "Ignore left sigma";
         DHFile[Tag][KeyPrefix + "X0"] = result.X0;
         DHFile[Tag][KeyPrefix + "SigmaR"] = result.SigmaR;
      }
      if(result.Strategy == MRFit_Strategy_IgnoreGaussian)
         DHFile[Tag][KeyPrefix + "Strategy"] = "Simple exponential";
   }

   PsFile.AddTextPage("Summary graphs");
   PsFile.AddPlot(SGraph2, "ap");
   PsFile.AddPlot(SGraph3, "ap");
   PsFile.AddPlot(SGraphOther, "ap");

   TF1 MegaFit("MegaFit", "pol1");
   SGraph3.Fit(&MegaFit);
   PsFile.AddPlot(SGraph3, "ap");

   DHFile[Tag]["FinalFitA"] = MegaFit.GetParameter(0);
   DHFile[Tag]["FinalFitAError"] = MegaFit.GetParError(0);
   DHFile[Tag]["FinalFitB"] = MegaFit.GetParameter(1);
   DHFile[Tag]["FinalFitBError"] = MegaFit.GetParError(1);

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

   DHFile.SaveToFile("AllFitResults.dh");
}

