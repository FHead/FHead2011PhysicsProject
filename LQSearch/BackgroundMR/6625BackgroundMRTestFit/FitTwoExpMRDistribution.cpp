#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TGraphErrors.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooTwoSideGaussianWithTwoExponentialTails.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooFormulaVar.h"
#include "RooFitResult.h"
using namespace RooFit;

#include "PlotHelper2.h"

struct MRFitResult;
int main(int argc, char *argv[]);
MRFitResult FitWithRCut(PsFileHelper &PsFile, string Filename, double RCut);

struct MRFitResult
{
   double Exponent1;
   double ExponentError1;
   double Exponent2;
   double ExponentError2;
   double Fraction;
   double FractionError;
};

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

   PsFileHelper PsFile("TwoExpDevelopFit.ps");

   vector<double> CutsToTry;
   CutsToTry.push_back(0.10);
   CutsToTry.push_back(0.12);
   CutsToTry.push_back(0.14);
   CutsToTry.push_back(0.16);
   CutsToTry.push_back(0.18);
   CutsToTry.push_back(0.20);
   CutsToTry.push_back(0.22);
   CutsToTry.push_back(0.24);
   CutsToTry.push_back(0.26);
   CutsToTry.push_back(0.28);
   CutsToTry.push_back(0.30);
   CutsToTry.push_back(0.32);
   CutsToTry.push_back(0.34);
   CutsToTry.push_back(0.36);
   CutsToTry.push_back(0.38);
   CutsToTry.push_back(0.40);
   CutsToTry.push_back(0.42);
   CutsToTry.push_back(0.44);
   CutsToTry.push_back(0.46);
   CutsToTry.push_back(0.48);
   CutsToTry.push_back(0.50);
   
   /*
   CutsToTry.push_back(0.52);
   CutsToTry.push_back(0.54);
   CutsToTry.push_back(0.56);
   CutsToTry.push_back(0.58);
   CutsToTry.push_back(0.60);
   CutsToTry.push_back(0.62);
   CutsToTry.push_back(0.64);
   CutsToTry.push_back(0.66);
   CutsToTry.push_back(0.68);
   CutsToTry.push_back(0.70);
   CutsToTry.push_back(0.72);
   CutsToTry.push_back(0.74);
   CutsToTry.push_back(0.76);
   CutsToTry.push_back(0.78);
   CutsToTry.push_back(0.80);
   */

   TGraphErrors SummaryGraph1;
   SummaryGraph1.SetNameTitle("SummaryGraph1", "(R Cut)^2 vs. exponent 1");
   SummaryGraph1.SetMarkerStyle(8);
   SummaryGraph1.SetLineWidth(2);
   SummaryGraph1.GetXaxis()->SetTitle("(R cut)^2");
   SummaryGraph1.GetYaxis()->SetTitle("Exponent");

   TGraphErrors SummaryGraph2;
   SummaryGraph2.SetNameTitle("SummaryGraph2", "(R Cut)^2 vs. exponent 2");
   SummaryGraph2.SetMarkerStyle(8);
   SummaryGraph2.SetLineWidth(2);
   SummaryGraph2.GetXaxis()->SetTitle("(R cut)^2");
   SummaryGraph2.GetYaxis()->SetTitle("Exponent");

   TGraphErrors SecondComponentFractionGraph;
   SecondComponentFractionGraph.SetNameTitle("SecondComponentFracionGraph", "Fraction of second component");
   SecondComponentFractionGraph.SetMarkerStyle(8);
   SecondComponentFractionGraph.SetLineWidth(2);

   for(int i = 0; i < CutsToTry.size(); i++)
   {
      MRFitResult result = FitWithRCut(PsFile, "TTJets_TuneD6T_MRTree.root", CutsToTry[i]);
      SummaryGraph1.SetPoint(i, CutsToTry[i] * CutsToTry[i], result.Exponent1);
      SummaryGraph1.SetPointError(i, 0, result.ExponentError1);
      SummaryGraph2.SetPoint(i, CutsToTry[i] * CutsToTry[i], result.Exponent2);
      SummaryGraph2.SetPointError(i, 0, result.ExponentError2);
      SecondComponentFractionGraph.SetPoint(i, CutsToTry[i] * CutsToTry[i], result.Fraction);
      SecondComponentFractionGraph.SetPointError(i, 0, result.FractionError);
   }

   PsFile.AddTextPage("Summary of all the fits!");
   PsFile.AddPlot(SummaryGraph1, "ap", false, false, true);
   PsFile.AddPlot(SummaryGraph2, "ap", false, false, true);
   PsFile.AddPlot(SecondComponentFractionGraph, "ap", false, false, true);

   SummaryGraph1.Fit("pol1");
   PsFile.AddPlot(SummaryGraph1, "ap", false, false, true);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

MRFitResult FitWithRCut(PsFileHelper &PsFile, string Filename, double RCut)
{
   TFile F(Filename.c_str());
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return MRFitResult();

   RooRealVar MR("GroupPFMR", "Chris' kinematic variable", 150, 1500, "GeV");
   RooRealVar R("GroupPFR", "Chris' another kinematic variable", -200, 200);
   RooArgSet TreeVarSet(MR, R);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, Form("GroupPFR > %f", RCut));

   RooRealVar X0("X0", "gaussian mean", 200, 0, 5000, "GeV");
   RooRealVar SigmaL("SigmaL", "left-hand side gaussian width", 50, 0, 5000, "GeV");
   RooRealVar SigmaR("SigmaR", "right-hand side gaussian width", 50, 0, 5000, "GeV");
   RooRealVar S1("S1", "exponent 1 of the tail", 0.01, 0, 0.5);
   RooRealVar S2("S2", "exponent 2 of the tail", 0.01, 0, 0.5);
   RooRealVar Fraction("F", "size of second component", 0.001, 0, 0.2);
   RooTwoSideGaussianWithTwoExponentialTails Model("Model", "Model", MR, X0, SigmaL, SigmaR, S1, S2, Fraction);

   Model.fitTo(Dataset, Save(true));

   stringstream Subtitle;
   Subtitle << "Fitting with R cut = " << RCut;
   PsFile.AddTextPage(Subtitle.str());

   RooPlot *ParameterPlot = MR.frame(Bins(50), Name("FitParameters"), Title("Fit parameters"));
   Model.paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.4, 0.9));
   PsFile.AddPlot(ParameterPlot, "", false);

   RooPlot *FinalResultPlot = MR.frame(Bins(50), Name("FitResults"), Title("MR"), AutoRange(Dataset));
   Dataset.plotOn(FinalResultPlot, MarkerSize(0.9));
   Model.plotOn(FinalResultPlot, LineColor(kBlue));
   PsFile.AddPlot(FinalResultPlot, "", true);

   MRFitResult Result;
   Result.Exponent1 = -S1.getVal();
   Result.ExponentError1 = S1.getError();
   Result.Exponent2 = -S2.getVal();
   Result.ExponentError2 = S2.getError();
   Result.Fraction = Fraction.getVal();
   Result.FractionError = Fraction.getError();

   return Result;
}





