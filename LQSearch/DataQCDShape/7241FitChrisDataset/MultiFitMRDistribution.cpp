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
#include "TChain.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooFormulaVar.h"
#include "RooFitResult.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooSameAs.h"
#include "RooAtLeast.h"
#include "RooAbsPdf.h"
#include "RooExponential.h"
#include "RooEllipse.h"
using namespace RooFit;

#include "PlotHelper2.h"
#include "DrawRandom.h"

struct SingleFitResult;
int main(int argc, char *argv[]);
SingleFitResult FitWithRCut(PsFileHelper &PsFile, string FileName, double RCut, int BoxNumber, int BTagRequirement,
   double MRMin, bool OneComponent);
RooFitResult *FitWithRCut(PsFileHelper &PsFile, string FileName, vector<double> RCuts, int BoxNumber,
   int BTagRequirement, double MRMin, bool OneComponent, string OutputBase = "");
int GetInteger(string str);
double GetDouble(string str);

class SingleFitResult
{
public:
   double S1;
   double S1Error;
   double S2;
   double S2Error;
   double F;
   double FError;
public:
   SingleFitResult &operator =(const SingleFitResult &other)
   {
      S1 = other.S1;
      S1Error = other.S1Error;
      S2 = other.S2;
      S2Error = other.S2Error;
      F = other.F;
      FError = other.FError;

      return *this;
   }
};

int main(int argc, char *argv[])
{
   string InputFile = "Samples/Wjets.root";
   string OutputBase = "WJetMuBox";
   int BTagRequirement = 0;
   int BoxNumber = 3;   // 3 = mu box, 4 = electron box
   double MRMin = 200;
   int NumberOfTries = 30;
   bool OneComponent = false;
   
   if(argc < 7)
   {
      cout << "Usage: " << argv[0] << " InputFile OutputBase BTag Box MRMin NumberOfTries [0/1]" << endl;
      cout << "Last parameter 0 means two components, and 1 means one component only" << endl;
      return -1;
   }

   InputFile = argv[1];
   OutputBase = argv[2];
   BTagRequirement = GetInteger(argv[3]);
   BoxNumber = GetInteger(argv[4]);
   MRMin = GetDouble(argv[5]);
   NumberOfTries = GetInteger(argv[6]);

   if(argc >= 8 && argv[7][0] == '1')
      OneComponent = true;

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   vector<RooFitResult *> FitResults;

   TFile F(Form("%s.root", OutputBase.c_str()), "recreate");

   for(int i = 0; i < NumberOfTries; i++)
   {
      vector<double> CutsToTry;
      CutsToTry.push_back(DrawRandom(0.01, 0.02));
      CutsToTry.push_back(DrawRandom(0.03, 0.04));
      CutsToTry.push_back(DrawRandom(0.06, 0.07));
      CutsToTry.push_back(DrawRandom(0.09, 0.10));
      CutsToTry.push_back(DrawRandom(0.12, 0.14));
      // CutsToTry.push_back(DrawRandom(0.60, 0.62));
      
      PsFileHelper PsFile(Form("%sMultiFit%d.ps", OutputBase.c_str(), i));
      PsFile.AddTextPage("Fit!!");
      RooFitResult *Result = FitWithRCut(PsFile, InputFile, CutsToTry, BoxNumber, BTagRequirement, MRMin, OneComponent);
      PsFile.AddTimeStampPage();
      PsFile.Close();

      FitResults.push_back(Result);
   }

   vector<double> CutsToTry;
   CutsToTry.push_back(0.01);
   CutsToTry.push_back(0.04);
   CutsToTry.push_back(0.09);
   PsFileHelper PsFileNominal(Form("%sMultiFitNominal.ps", OutputBase.c_str()));
   PsFileNominal.AddTextPage("Fit!!");
   RooFitResult *NominalResult = FitWithRCut(PsFileNominal, InputFile, CutsToTry, BoxNumber, BTagRequirement, MRMin, OneComponent, "NominalFitResult");
   PsFileNominal.AddTimeStampPage();
   PsFileNominal.Close();
   FitResults.push_back(NominalResult);
   
   CutsToTry.clear();
   CutsToTry.push_back(0.01);
   CutsToTry.push_back(0.02);
   CutsToTry.push_back(0.03);
   CutsToTry.push_back(0.04);
   CutsToTry.push_back(0.05);
   CutsToTry.push_back(0.06);
   CutsToTry.push_back(0.07);
   // CutsToTry.push_back(0.08);
   // CutsToTry.push_back(0.09);
   PsFileHelper PsFileNominal2(Form("%sMultiFitNominal2.ps", OutputBase.c_str()));
   PsFileNominal2.AddTextPage("Fit!!");
   RooFitResult *NominalResult2 = FitWithRCut(PsFileNominal2, InputFile, CutsToTry, BoxNumber, BTagRequirement, MRMin, OneComponent, "NominalFitResult2");
   PsFileNominal2.AddTimeStampPage();
   PsFileNominal2.Close();
   FitResults.push_back(NominalResult2);

   F.cd();
   for(int i = 0; i < NumberOfTries; i++)
      FitResults[i]->Write();

   PsFileHelper PsFile(OutputBase + ".ps");

   vector<double> AValues;
   vector<double> BValues;
   vector<double> AValues2;
   vector<double> BValues2;

   double A = 0;
   double B = 0;
   double A2 = 0;
   double B2 = 0;

   double A1PlotMin = 99999;
   double A1PlotMax = -99999;
   double B1PlotMin = 99999;
   double B1PlotMax = -99999;
   double A2PlotMin = 99999;
   double A2PlotMax = -99999;
   double B2PlotMin = 99999;
   double B2PlotMax = -99999;

   for(int i = 0; i < NumberOfTries; i++)
   {
      double x1 = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterA1"))->getVal();
      double y1 = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterB1"))->getVal();
      double ex1 = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterA1"))->getError();
      double ey1 = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterB1"))->getError();

      if(ex1 > 10 * x1 || ey1 > 10 * y1 || ey1 > 0.1)   // potentially bad fit
         continue;

      if(x1 - 3.5 * ex1 < A1PlotMin)
         A1PlotMin = x1 - 3.5 * ex1;
      if(x1 + 3.5 * ex1 > A1PlotMax)
         A1PlotMax = x1 + 3.5 * ex1;
      if(y1 - 3.5 * ey1 < B1PlotMin)
         B1PlotMin = y1 - 3.5 * ey1;
      if(y1 + 3.5 * ey1 > B1PlotMax)
         B1PlotMax = y1 + 3.5 * ey1;

      if(OneComponent == false)
      {
         double x2 = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterA2"))->getVal();
         double y2 = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterB2"))->getVal();
         double ex2 = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterA2"))->getError();
         double ey2 = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterB2"))->getError();
         if(x2 - 3.5 * ex2 < A2PlotMin)
            A2PlotMin = x2 - 3.5 * ex2;
         if(x2 + 3.5 * ex2 > A2PlotMax)
            A2PlotMax = x2 + 3.5 * ex2;
         if(y2 - 3.5 * ey2 < B2PlotMin)
            B2PlotMin = y2 - 3.5 * ey2;
         if(y2 + 3.5 * ey2 > B2PlotMax)
            B2PlotMax = y2 + 3.5 * ey2;
      }
   }

   RooPlot ParameterABPlot(A1PlotMin, A1PlotMax, 0.2, 0.4);
   if(OneComponent == false)
   {
      ParameterABPlot.GetXaxis()->SetTitle("Parameter A1");
      ParameterABPlot.GetYaxis()->SetTitle("Parameter B1");
      ParameterABPlot.SetTitle("Summary of fits (first component)");
   }
   else
   {
      ParameterABPlot.GetXaxis()->SetTitle("Parameter a");
      ParameterABPlot.GetYaxis()->SetTitle("Parameter b");
      ParameterABPlot.SetTitle("Summary of fits (single component)");
   }
   for(int i = 0; i < NumberOfTries; i++)
   {
      double x = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterA1"))->getVal();
      double y = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterB1"))->getVal();
      double ex = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterA1"))->getError();
      double ey = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterB1"))->getError();
      double rho = FitResults[i]->correlation("ParameterA1", "ParameterB1");
      RooEllipse *Contour = new RooEllipse(Form("Ellipse%d", i), x, y, ex, ey, rho);
      
      if(ey < 0.1)
      { 
         Contour->SetLineWidth(2);
         Contour->SetLineColor(kRed);
         ParameterABPlot.addPlotable(Contour);

         AValues.push_back(x);
         BValues.push_back(y);
         A = A + x / NumberOfTries;
         B = B + y / NumberOfTries;
      }
   }
   ParameterABPlot.Write();

   A = A * NumberOfTries / AValues.size();
   B = B * NumberOfTries / BValues.size();
   
   RooPlot ParameterAB2Plot(A2PlotMin, A2PlotMax, 0.2, 0.4);
   ParameterAB2Plot.GetXaxis()->SetTitle("Parameter A2");
   ParameterAB2Plot.GetYaxis()->SetTitle("Parameter B2");
   ParameterAB2Plot.SetTitle("Summary of fits (second component)");
   for(int i = 0; i < NumberOfTries; i++)
   {
      if(OneComponent == false)
      {
         double x = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterA2"))->getVal();
         double y = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterB2"))->getVal();
         double ex = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterA2"))->getError();
         double ey = ((RooRealVar *)FitResults[i]->floatParsFinal().find("ParameterB2"))->getError();
         double rho = FitResults[i]->correlation("ParameterA2", "ParameterB2");
         RooEllipse *Contour = new RooEllipse(Form("Ellipse%d", i), x, y, ex, ey, rho);
         Contour->SetLineWidth(2);
         Contour->SetLineColor(kBlue);
         ParameterAB2Plot.addPlotable(Contour);

         if(ey < 0.3)
         {
            AValues2.push_back(x);
            BValues2.push_back(y);
            A2 = A2 + x / NumberOfTries;
            B2 = B2 + y / NumberOfTries;
         }
      }
      else
      {
         AValues2.push_back(0);
         BValues2.push_back(0);
      }
   }
   ParameterAB2Plot.Write();

   A2 = A2 * NumberOfTries / AValues.size();
   B2 = B2 * NumberOfTries / BValues.size();
   
   sort(AValues.begin(), AValues.end());
   sort(BValues.begin(), BValues.end());
   sort(AValues2.begin(), AValues2.end());
   sort(BValues2.begin(), BValues2.end());

   double AMedian = AValues[AValues.size()/2];
   double BMedian = BValues[BValues.size()/2];
   double A2Median = AValues2[AValues2.size()/2];
   double B2Median = BValues2[BValues2.size()/2];

   TGraph HorizontalLine, VerticalLine;
   HorizontalLine.SetPoint(0, -100, BMedian);
   HorizontalLine.SetPoint(1, 100, BMedian);
   VerticalLine.SetPoint(0, AMedian, -100);
   VerticalLine.SetPoint(1, AMedian, 100);

   TGraph HorizontalLine2, VerticalLine2;
   HorizontalLine2.SetPoint(0, -100, B2Median);
   HorizontalLine2.SetPoint(1, 100, B2Median);
   VerticalLine2.SetPoint(0, A2Median, -100);
   VerticalLine2.SetPoint(1, A2Median, 100);

   TGraph HorizontalLineAverage, VerticalLineAverage;
   HorizontalLineAverage.SetPoint(0, -100, B);
   HorizontalLineAverage.SetPoint(1, 100, B);
   VerticalLineAverage.SetPoint(0, A, -100);
   VerticalLineAverage.SetPoint(1, A, 100);

   TGraph HorizontalLineAverage2, VerticalLineAverage2;
   HorizontalLineAverage2.SetPoint(0, -100, B2);
   HorizontalLineAverage2.SetPoint(1, 100, B2);
   VerticalLineAverage2.SetPoint(0, A2, -100);
   VerticalLineAverage2.SetPoint(1, A2, 100);

   HorizontalLine.SetLineColor(kRed);
   VerticalLine.SetLineColor(kRed);
   HorizontalLine2.SetLineColor(kBlue);
   VerticalLine2.SetLineColor(kBlue);
   
   HorizontalLineAverage.SetLineColor(kRed);
   VerticalLineAverage.SetLineColor(kRed);
   HorizontalLineAverage2.SetLineColor(kBlue);
   VerticalLineAverage2.SetLineColor(kBlue);
   
   HorizontalLine.SetLineWidth(2);
   VerticalLine.SetLineWidth(2);
   HorizontalLine2.SetLineWidth(2);
   VerticalLine2.SetLineWidth(2);
   
   HorizontalLineAverage.SetLineWidth(2);
   VerticalLineAverage.SetLineWidth(2);
   HorizontalLineAverage2.SetLineWidth(2);
   VerticalLineAverage2.SetLineWidth(2);

   HorizontalLineAverage.SetLineStyle(10);
   VerticalLineAverage.SetLineStyle(10);
   HorizontalLineAverage2.SetLineStyle(10);
   VerticalLineAverage2.SetLineStyle(10);

   /*
   TLegend legend(0.6, 0.6, 0.85, 0.7);
   legend.SetFillColor(0);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(&HorizontalLine, "", "l");
   */
   
   TGraph ExampleMedian, ExampleAverage;
   ExampleMedian.SetLineWidth(2);
   ExampleAverage.SetLineWidth(2);
   ExampleAverage.SetLineStyle(10);

   TLegend legend2(0.6, 0.75, 0.85, 0.85);
   legend2.SetFillColor(0);
   legend2.SetFillStyle(0);
   legend2.SetBorderSize(0);
   legend2.SetTextFont(42);
   legend2.AddEntry(&ExampleMedian, "Median", "l");
   legend2.AddEntry(&ExampleAverage, "Average", "l");

   TCanvas ParameterABCanvas;
   ParameterABPlot.Draw();
   HorizontalLine.Draw("l");
   VerticalLine.Draw("l");
   HorizontalLineAverage.Draw("l");
   VerticalLineAverage.Draw("l");
   // legend.Draw();
   legend2.Draw();
   PsFile.AddCanvas(ParameterABCanvas);

   TCanvas ParameterAB2Canvas;
   ParameterAB2Plot.Draw();
   HorizontalLine2.Draw("l");
   VerticalLine2.Draw("l");
   HorizontalLineAverage2.Draw("l");
   VerticalLineAverage2.Draw("l");
   // legend.Draw();
   legend2.Draw();
   PsFile.AddCanvas(ParameterAB2Canvas);

   RooPlot ParameterABPlot2(0.003, 0.01, 0, 0.04);
   for(int i = 0; i < NumberOfTries; i++)
      if(FitResults[i] != NULL)
         FitResults[i]->plotOn(&ParameterABPlot2, "ParameterA1", "ParameterB1", "M");
   PsFile.AddPlot(ParameterABPlot2);
   ParameterABPlot2.Write();
   
   RooPlot ParameterABPlot3(0.003, 0.01, 0, 0.04);
   for(int i = 0; i < NumberOfTries; i++)
   {
      if(FitResults[i] != NULL)
         FitResults[i]->plotOn(&ParameterABPlot3, "ParameterA1", "ParameterB1", "M");
   }
   PsFile.AddPlot(ParameterABPlot3);
   ParameterABPlot3.Write();
   
   F.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

SingleFitResult FitWithRCut(PsFileHelper &PsFile, string FileName, double RCut, int Box, int BTagRequirement,
   double MRMin, bool OneComponent)
{
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("EVENTS");
   if(Tree == NULL)
      return SingleFitResult();

   double MRLowerBound = MRMin;
   double MRUpperBound = 400;

   string MRString = "MR";
   string RString = "RSQ";

   RooRealVar MR(MRString.c_str(), "MR", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R(RString.c_str(), "R^{2}", -200, 200);
   RooRealVar BoxNumber("BOX_NUM", "box number", -10, 10);
   RooRealVar BTagNumber("BTAG_NUM", "b-tag count", -10, 10);
   RooRealVar WPU("WPU", "WPU", 0, 10000);
   RooArgSet TreeVarSet(MR, R, BoxNumber, BTagNumber, WPU);

   string BTagString = "BTAG_NUM > -1";
   if(BTagRequirement == 0)
      BTagString = "BTAG_NUM == 0";
   else if(BTagRequirement > 0)
      BTagString = "BTAG_NUM > 0";

   /*
   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet,
      Form("%s > %f && %s < 0.5 && BOX_NUM == %d && %s", RString.c_str(), RCut, RString.c_str(),
      Box, BTagString.c_str()), "WPU");
   */
   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet,
      Form("%s > %f && %s < 0.5 && BOX_NUM == %d && %s", RString.c_str(), RCut, RString.c_str(),
      Box, BTagString.c_str()), "");

   RooRealVar S1("S1", "first exponent of the tail", -0.022, -1.0, 0.0);
   RooExponential Component1("Component1", "First component", MR, S1);
   
   RooRealVar S2("S2", "second exponent of the tail", -0.007, -1.0, 0.0);
   RooExponential Component2("Component2", "Second component", MR, S2);

   RooRealVar Fraction("Fraction", "Fraction of the second component at zero", 0.7, 0, 1);
   RooAddPdf *Model = new RooAddPdf("Model", "Model", Component1, Component2, Fraction);

   // RooFitResult *FitResult = Model->fitTo(Dataset, Save(true));
   if(OneComponent == true)
      Component1.fitTo(Dataset, SumW2Error(true));
   else
      Model->fitTo(Dataset, SumW2Error(true));

   stringstream Subtitle;
   Subtitle << "Fitting with R^{2} cut = " << RCut;
   PsFile.AddTextPage(Subtitle.str());

   RooPlot *ParameterPlot = MR.frame(Bins(50), Name("FitParameters"), Title("Fit parameters"));
   Model->paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.4, 0.9));
   ParameterPlot->getAttText()->SetTextFont(42);
   PsFile.AddPlot(ParameterPlot, "", false);

   RooPlot *FinalResultPlot = MR.frame(Bins(50), Name("FitResults"), Title("MR"), AutoRange(Dataset));
   Dataset.plotOn(FinalResultPlot, MarkerSize(0.9), DataError(RooAbsData::SumW2));
   if(OneComponent == false)
   {
      Model->plotOn(FinalResultPlot, LineColor(kBlue));
      Model->plotOn(FinalResultPlot, LineColor(kGreen), Components(Component1));
      Model->plotOn(FinalResultPlot, LineColor(kRed), Components(Component2));
   }
   else
   {
      Component1.plotOn(FinalResultPlot, LineColor(kBlue));
      Component1.plotOn(FinalResultPlot, LineColor(kGreen), Components(Component1));
      Component1.plotOn(FinalResultPlot, LineColor(kRed), Components(Component2));
   }
   PsFile.AddPlot(FinalResultPlot, "", true);

   SingleFitResult result;

   if(Fraction.getVal() > 0.5)
   {
      result.S1 = -S1.getVal();
      result.S1Error = S1.getError();
      result.S2 = -S2.getVal();
      result.S2Error = S2.getError();
      result.F = 1 - Fraction.getVal();
      result.FError = Fraction.getError();
   }
   else
   {
      result.S1 = -S2.getVal();
      result.S1Error = S2.getError();
      result.S2 = -S1.getVal();
      result.S2Error = S1.getError();
      result.F = Fraction.getVal();
      result.FError = Fraction.getError();
   }

   delete Model;

   F.Close();

   return result;
}

RooFitResult *FitWithRCut(PsFileHelper &PsFile, string FileName, vector<double> RCuts, int Box, int BTagRequirement,
   double MRMin, bool OneComponent, string OutputBase)
{
   if(RCuts.size() == 0)
      return NULL;
   if(RCuts.size() == 1)
   {
      cout << "If you want to fit with just one R-cut, use the easy version!" << endl;
      return NULL;
   }

   sort(RCuts.begin(), RCuts.end());

   vector<SingleFitResult> SingleFitResults(RCuts.size());

   for(int i = 0; i < (int)RCuts.size(); i++)
      SingleFitResults[i] = FitWithRCut(PsFile, FileName, RCuts[i], Box, BTagRequirement, MRMin, OneComponent);

   PsFile.AddTextPage("Putting everything together");

   TGraphErrors SingleCentralValues1;
   SingleCentralValues1.SetNameTitle("SingleCentralValues1", "Central values from single fits, component 1");
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      SingleCentralValues1.SetPoint(i, RCuts[i], -SingleFitResults[i].S1);
      SingleCentralValues1.SetPointError(i, 0, SingleFitResults[i].S1Error);
   }

   TGraphErrors SingleCentralValues2;
   SingleCentralValues2.SetNameTitle("SingleCentralValues2", "Central values from single fits, component 2");
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      SingleCentralValues2.SetPoint(i, RCuts[i], -SingleFitResults[i].S2);
      SingleCentralValues2.SetPointError(i, 0, SingleFitResults[i].S2Error);
   }

   TGraphErrors SingleFraction;
   SingleFraction.SetNameTitle("SingleFraction", "Central values from single fits, fraction");
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      SingleFraction.SetPoint(i, RCuts[i], SingleFitResults[i].F);
      SingleFraction.SetPointError(i, 0, SingleFitResults[i].FError);
   }

   TF1 InitialParameterValues1("InitialParameterValues1", "pol1");
   SingleCentralValues1.Fit(&InitialParameterValues1);
   InitialParameterValues1.SetLineWidth(1);
   
   TF1 InitialParameterValues2("InitialParameterValues2", "pol1");
   SingleCentralValues2.Fit(&InitialParameterValues2);
   InitialParameterValues2.SetLineWidth(1);
   
   TF1 InitialFraction("InitialFraction", "pol0");
   SingleFraction.Fit(&InitialFraction);
   InitialFraction.SetLineWidth(1);

   double ParameterA1Value = -InitialParameterValues1.GetParameter(0);
   double ParameterB1Value = -InitialParameterValues1.GetParameter(1);
   double ParameterA2Value = -InitialParameterValues2.GetParameter(0);
   double ParameterB2Value = -InitialParameterValues2.GetParameter(1);
   double FractionValue = InitialFraction.GetParameter(0);

   SingleCentralValues1.SetLineWidth(2);
   SingleCentralValues1.SetMarkerStyle(1);
   PsFile.AddPlot(SingleCentralValues1, "ap");

   if(OutputBase != "")
   {
      TCanvas C("C", "C", 1024, 1024);
      SingleCentralValues1.SetTitle("");
      SingleCentralValues1.Draw("ap");
      SingleCentralValues1.GetXaxis()->SetTitle("(R Cut)^{2}");
      SingleCentralValues1.GetYaxis()->SetTitle("Slope Parameter [1/GeV]");
      C.SaveAs(Form("%s_SingleFitResult.png", OutputBase.c_str()));
      C.SaveAs(Form("%s_SingleFitResult.C", OutputBase.c_str()));
      C.SaveAs(Form("%s_SingleFitResult.eps", OutputBase.c_str()));
      C.SaveAs(Form("%s_SingleFitResult.pdf", OutputBase.c_str()));
   }

   SingleCentralValues2.SetLineWidth(2);
   SingleCentralValues2.SetMarkerStyle(1);
   PsFile.AddPlot(SingleCentralValues2, "ap");
   
   SingleFraction.SetLineWidth(2);
   SingleFraction.SetMarkerStyle(1);
   PsFile.AddPlot(SingleFraction, "ap");
   
   vector<string> SingleFitParameterExplanation;
   stringstream ParameterA1String;
   ParameterA1String << "Parameter A1 from single fit: " << ParameterA1Value << " +- "
      << InitialParameterValues1.GetParError(0);
   SingleFitParameterExplanation.push_back(ParameterA1String.str());
   stringstream ParameterB1String;
   ParameterB1String << "Parameter B1 from single fit: " << ParameterB1Value << " +- "
      << InitialParameterValues1.GetParError(1);
   SingleFitParameterExplanation.push_back(ParameterB1String.str());
   stringstream ParameterA2String;
   ParameterA2String << "Parameter A2 from single fit: " << ParameterA2Value << " +- "
      << InitialParameterValues2.GetParError(0);
   SingleFitParameterExplanation.push_back(ParameterA2String.str());
   stringstream ParameterB2String;
   ParameterB2String << "Parameter B2 from single fit: " << ParameterB2Value << " +- "
      << InitialParameterValues2.GetParError(1);
   SingleFitParameterExplanation.push_back(ParameterB2String.str());
   stringstream FractionString;
   FractionString << "Average fraction from single fit: " << FractionValue << " +- "
      << InitialFraction.GetParError(0);
   SingleFitParameterExplanation.push_back(FractionString.str());
   SingleFitParameterExplanation.push_back("Friendly reminder: s = a + b * (R cut)^2");
   SingleFitParameterExplanation.push_back("Exponential part in the fit is exp(-s * MR)");
   PsFile.AddTextPage(SingleFitParameterExplanation);
   
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("EVENTS");
   if(Tree == NULL)
      return NULL;

   double MRLowerBound = MRMin;
   double MRUpperBound = 400;

   string MRString = "MR";
   string RString = "RSQ";

   RooRealVar MR(MRString.c_str(), "MR", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R(RString.c_str(), "R^{2}", -200, 200);
   RooRealVar BoxNumber("BOX_NUM", "Box number", -10, 10);
   RooRealVar BTagNumber("BTAG_NUM", "B-tag count", -10, 10);
   RooRealVar WPU("WPU", "WPU", 0, 10000);
   RooArgSet TreeVarSet(MR, R, BoxNumber, BTagNumber, WPU);

   string BTagString = "BTAG_NUM > -1";
   if(BTagRequirement == 0)
      BTagString = "BTAG_NUM == 0";
   else if(BTagRequirement > 0)
      BTagString = "BTAG_NUM > 0";

   /*
   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet,
      Form("%s > %f && %s < 0.5 && BOX_NUM == %d && %s", RString.c_str(), RCuts[0], RString.c_str(),
      Box, BTagString.c_str()), "WPU");
   */
   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet,
      Form("%s > %f && %s < 0.5 && BOX_NUM == %d && %s", RString.c_str(), RCuts[0], RString.c_str(),
      Box, BTagString.c_str()), "");

   RooRealVar ParameterA1("ParameterA1", "s1 = \"a1\" + b1 R^2", ParameterA1Value, -0.1, 0.1);
   RooRealVar ParameterB1("ParameterB1", "s1 = a1 + \"b1\" R^2", ParameterB1Value, -1, 1);
   RooRealVar ParameterA2("ParameterA2", "s2 = \"a2\" + b2 R^2", ParameterA2Value, -0.1, 0.1);
   RooRealVar ParameterB2("ParameterB2", "s2 = a2 + \"b2\" R^2", ParameterB2Value, -1, 1);

   vector<RooFormulaVar *> S1;
   vector<RooFormulaVar *> S2;
   vector<RooRealVar *> SingleBinYields;
   vector<RooFormulaVar *> Yields;
   vector<RooFormulaVar *> NegativeYields;
   vector<RooFormulaVar *> NormalizedYields;
   vector<RooFormulaVar *> NormalizedNegativeYields;

   vector<RooAbsPdf *> Component1Models;
   vector<RooAbsPdf *> Component2Models;
   vector<RooAbsPdf *> Models;

   vector<RooRealVar *> Fraction;

   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      double GuessYield = 0;
      if(i != RCuts.size() - 1)
         GuessYield = Dataset.reduce(Cut(Form("%s > %f && %s <= %f", RString.c_str(), RCuts[i],
         RString.c_str(), RCuts[i+1])))->sumEntries();
      else
         GuessYield = Dataset.reduce(Cut(Form("%s > %f", RString.c_str(), RCuts[i])))->sumEntries();

      cout << "Guess yield for bin " << i << " is " << GuessYield << endl;
         
      SingleBinYields.push_back(new RooRealVar(Form("SingleBinYield_%d", i),
         Form("Yield with R in bin %d", i), GuessYield, 0, GuessYield * 10));
   }

   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      S1.push_back(new RooFormulaVar(Form("S1_%d", i),
         Form("exponent 1 of the tail, R > %f", RCuts[i]),
         Form("-1 * @0 - %f * @1", RCuts[i]), RooArgList(ParameterA1, ParameterB1)));
      S2.push_back(new RooFormulaVar(Form("S2_%d", i),
         Form("exponent 2 of the tail, R > %f", RCuts[i]),
         Form("-1 * @0 - %f * @1", RCuts[i]), RooArgList(ParameterA2, ParameterB2)));

      Component1Models.push_back(new RooExponential(Form("Model1_%d", i), Form("First model for R > %f", RCuts[i]),
         MR, *S1[i]));
      Component2Models.push_back(new RooExponential(Form("Model2_%d", i), Form("Second model for R > %f", RCuts[i]),
         MR, *S2[i]));
   
      Fraction.push_back(new RooRealVar(Form("Fraction_%d", i), Form("Fraction_%d", i),
         1 - FractionValue, 0.0, 1.0));

      if(OneComponent == true)
         Models.push_back(Component1Models[i]);
      else
         Models.push_back(new RooAddPdf(Form("Model_%d", i), Form("Total model for R > %f", RCuts[i]),
            *Component1Models[i], *Component2Models[i], *Fraction[i]));
   }

   Yields.push_back(new RooFormulaVar(Form("Yield_%d", RCuts.size() - 1), "Last bin yield",
      "@0", RooArgList(*SingleBinYields[SingleBinYields.size()-1])));
   for(int i = (int)RCuts.size() - 1 - 1; i >= 0; i--)
      Yields.push_back(new RooFormulaVar(Form("Yield_%d", i), Form("Yield with R above %f", RCuts[i]),
         "@0 + @1", RooArgList(*Yields[Yields.size()-1], *SingleBinYields[i])));
   reverse(Yields.begin(), Yields.end());

   for(int i = 0; i < (int)RCuts.size(); i++)
      cout << "Yields[" << i << "] has initial value " << Yields[i]->getVal() << endl;
   
   for(int i = 0; i < (int)RCuts.size(); i++)
      NegativeYields.push_back(new RooFormulaVar(Form("NYield_%d", i),
         "Negative yield", "-1 * @0", RooArgList(*Yields[i])));

   for(int i = 0; i < (int)RCuts.size() - 1; i++)
   {
      NormalizedYields.push_back(new RooFormulaVar(Form("NormalizedYield_%d", i),
         "Yield", "@0 / (@0 - @1)", RooArgList(*Yields[i], *Yields[i+1])));
      NormalizedNegativeYields.push_back(new RooFormulaVar(Form("NormalizedNegativeYield_%d", i),
         "Yield", "-@1 / (@0 - @1)", RooArgList(*Yields[i], *Yields[i+1])));
   }

   vector<RooAbsPdf *> ModelBeforeConstraint;
   vector<RooAbsPdf *> Constraint;
   vector<RooAbsPdf *> TopLevelModels;
   vector<RooAbsReal *> TopLevelYields;

   RooArgList ModelList;
   RooArgList YieldList;

   for(int i = 0; i < (int)RCuts.size(); i++)   // ps. last bin is special
   {
      if(i == RCuts.size() - 1)
         ModelBeforeConstraint.push_back(Models[i]);
      else
         ModelBeforeConstraint.push_back(new RooAddPdf(Form("ModelBeforeConstraint_%d", i),
            Form("Model before constraint (bin %d)", i), RooArgList(*Models[i], *Models[i+1]),
            RooArgList(*NormalizedYields[i], *NormalizedNegativeYields[i])));

      if(i == RCuts.size() - 1)
         Constraint.push_back(new RooAtLeast(Form("Constraint_%d", i), "Last bin constraint", R, RCuts[i]));
      else
         Constraint.push_back(new RooSameAs(Form("Constraint_%d", i),
            Form("Constraint R = %f - %f", RCuts[i], RCuts[i+1]), R,
            (RCuts[i+1] + RCuts[i]) / 2, (RCuts[i+1] - RCuts[i]) / 2));

      if(i == RCuts.size() - 1)
         TopLevelModels.push_back(new RooProdPdf(Form("TopLevelModel_%d", i),
            Form("Top level model for bin with R > %f", RCuts[i]),
            RooArgList(*ModelBeforeConstraint[i], *Constraint[i])));
      else
         TopLevelModels.push_back(new RooProdPdf(Form("TopLevelModel_%d", i),
            Form("Top level model for bin with R = %f - %f", RCuts[i], RCuts[i+1]),
            RooArgList(*ModelBeforeConstraint[i], *Constraint[i])));

      if(i == RCuts.size() - 1)
         TopLevelYields.push_back(Yields[i]);
      else
         TopLevelYields.push_back(new RooFormulaVar(Form("BinYield_%d", i), "Bin yield variable",
            "@0 - @1", RooArgList(*Yields[i], *Yields[i+1])));
      
      ModelList.add(*TopLevelModels[i]);
      YieldList.add(*TopLevelYields[i]);
   }

   RooAddPdf FinalModel("FinalModel", "Final model!", ModelList, YieldList);

   RooFitResult *FitResult = FinalModel.fitTo(Dataset, Save(true), PrintEvalErrors(-1), NumCPU(3), SumW2Error(true));
   
   PsFile.AddTextPage("Simultaneous fit!");

   // Total model vs. total data
   RooPlot *FinalResultPlot = MR.frame(Bins(50), Name("FitResults"), Title("MR, Simultaneous fit, total model"));
   Dataset.plotOn(FinalResultPlot, MarkerSize(0.9), DataError(RooAbsData::SumW2));
   FinalModel.plotOn(FinalResultPlot, LineColor(kBlue));
   PsFile.AddPlot(FinalResultPlot, "", true);

   // Each bin, model vs. data
   RooPlot *FinalResultPlot2 = MR.frame(Bins(50), Name("FitResults2"), Title("   "));
   Dataset.plotOn(FinalResultPlot2, MarkerSize(0.9), MarkerColor(1), DataError(RooAbsData::SumW2));
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      RooArgList ComponentsToAdd;
      for(int j = i; j < (int)RCuts.size(); j++)
         ComponentsToAdd.add(*TopLevelModels[j]);
      FinalModel.plotOn(FinalResultPlot2, LineColor(kBlue), Components(ComponentsToAdd), LineColor(i + 1));
   }
   for(int i = 1; i < (int)RCuts.size(); i++)
      Dataset.reduce(Cut(Form("%s > %f", RString.c_str(), RCuts[i])))->plotOn(FinalResultPlot2,
         MarkerSize(0.9), MarkerColor(i + 1), DataError(RooAbsData::SumW2));

   TCanvas FinalResultCanvas2;

   FinalResultPlot2->Draw();

   vector<TH1D *> DummyHistograms;   
   TLegend legend(0.7, 0.85, 0.9, 0.65);
   legend.SetTextFont(42);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      DummyHistograms.push_back(new TH1D(Form("DummyHistogram_%d", i), "Dummy!", 2, 0, 1));
      DummyHistograms[i]->SetLineColor(i + 1);
      DummyHistograms[i]->SetLineWidth(2);
      legend.AddEntry(DummyHistograms[i], Form("R^{2} > %.2f", RCuts[i]), "l");
   }
   legend.Draw();

   FinalResultCanvas2.SetLogy();

   PsFile.AddCanvas(FinalResultCanvas2);

   if(OutputBase != "")
   {
      TCanvas FinalResultCanvas2_Output("C", "C", 1024, 1024);
      FinalResultPlot2->Draw();
      legend.Draw();
      FinalResultCanvas2_Output.SetLogy();
      FinalResultCanvas2_Output.SaveAs(Form("%s_FitResult.png", OutputBase.c_str()));
      FinalResultCanvas2_Output.SaveAs(Form("%s_FitResult.C", OutputBase.c_str()));
      FinalResultCanvas2_Output.SaveAs(Form("%s_FitResult.eps", OutputBase.c_str()));
      FinalResultCanvas2_Output.SaveAs(Form("%s_FitResult.pdf", OutputBase.c_str()));
   }

   for(int i = 0; i < (int)RCuts.size(); i++)
      delete DummyHistograms[i];
   DummyHistograms.clear();
   
   // simultaneous fit vs. normal fit
   TGraphErrors ABBand1, ABBand2;
   ABBand1.SetNameTitle("ABBand1", "Comparison between simple fit and simultaneous fit, component 1");
   ABBand2.SetNameTitle("ABBand2", "Comparison between simple fit and simultaneous fit, component 2");
   int ABBandCounter = 0;
   double R2Begin = RCuts[0] - 0.03;
   double R2End = RCuts[RCuts.size()-1] + 0.03;
   for(double x = R2Begin; x <= R2End; x = x + (R2End - R2Begin) / 100)
   {
      double Correlation1 = FitResult->correlation("ParameterA1", "ParameterB1");
      double Correlation2 = FitResult->correlation("ParameterA2", "ParameterB2");
      double Value1 = ParameterA1.getVal() + ParameterB1.getVal() * x;
      double Value2 = ParameterA2.getVal() + ParameterB2.getVal() * x;
      double Error1 = sqrt(ParameterA1.getError() * ParameterA1.getError()
         + ParameterB1.getError() * ParameterB1.getError() * x * x
         + 2 * ParameterA1.getError() * ParameterB1.getError() * x * Correlation1);
      double Error2 = sqrt(ParameterA2.getError() * ParameterA2.getError()
         + ParameterB2.getError() * ParameterB2.getError() * x * x
         + 2 * ParameterA2.getError() * ParameterB2.getError() * x * Correlation1);

      ABBand1.SetPoint(ABBandCounter, x, Value1);
      ABBand1.SetPointError(ABBandCounter, 0, Error1);
      ABBand2.SetPoint(ABBandCounter, x, Value2);
      ABBand2.SetPointError(ABBandCounter, 0, Error2);
      ABBandCounter = ABBandCounter + 1;
   }

   TCanvas ABBand1Canvas;
   ABBand1.SetFillColor(kCyan - 3);
   ABBand1.SetFillStyle(3144);
   ABBand1.Draw("a3");
   ABBand1.GetXaxis()->SetTitle("(R cut)^2");
   ABBand1.GetYaxis()->SetTitle("Exponent");
   SingleCentralValues1.Draw("p");
   PsFile.AddCanvas(ABBand1Canvas);
   
   TCanvas ABBand2Canvas;
   ABBand2.SetFillColor(kCyan - 3);
   ABBand2.SetFillStyle(3144);
   ABBand2.Draw("a3");
   ABBand2.GetXaxis()->SetTitle("(R cut)^2");
   ABBand2.GetYaxis()->SetTitle("Exponent");
   SingleCentralValues2.Draw("p");
   PsFile.AddCanvas(ABBand2Canvas);

   // Ratio plots for easier comparison
   TGraphErrors SimpleFitRatioBand1, SimpleFitRatioBand2;
   TGraphErrors ABRatioBand1, ABRatioBand2;
   TGraph ABRatioLine1, ABRatioLine2;
   TGraphErrors SingleRatioPoint1, SingleRatioPoint2;

   SimpleFitRatioBand1.SetNameTitle("SimpleFitRatioBand1",
      "Comparison between simple fit and simultaneous fit, first component");
   SimpleFitRatioBand2.SetNameTitle("SimpleFitRatioBand2",
      "Comparison between simple fit and simultaneous fit, second component");
   ABRatioBand1.SetNameTitle("ABRatioBand1",
      "Comparison between simple fit and simultaneous fit, first component");
   ABRatioBand2.SetNameTitle("ABRatioBand2",
      "Comparison between simple fit and simultaneous fit, second component");
   ABRatioLine1.SetNameTitle("ABRatioLine1",
      "Comparison between simple fit and simultaneous fit, first component");
   ABRatioLine2.SetNameTitle("ABRatioLine2",
      "Comparison between simple fit and simultaneous fit, second component");
   SingleRatioPoint1.SetNameTitle("SingleRatioPoint1",
      "Comparison between simple fit and simultaneous fit, first component");
   SingleRatioPoint2.SetNameTitle("SingleRatioPoint2",
      "Comparison between simple fit and simultaneous fit, second component");

   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      double FitCentral1 = ParameterA1Value + ParameterB1Value * RCuts[i];
      double FitCentral2 = ParameterA2Value + ParameterB2Value * RCuts[i];

      SingleRatioPoint1.SetPoint(i, RCuts[i], SingleFitResults[i].S1 / FitCentral1);
      SingleRatioPoint1.SetPointError(i, 0, SingleFitResults[i].S1Error / FitCentral1);
      SingleRatioPoint2.SetPoint(i, RCuts[i], SingleFitResults[i].S2 / FitCentral2);
      SingleRatioPoint2.SetPointError(i, 0, SingleFitResults[i].S2Error / FitCentral2);
   }

   int ABRatioBandCounter = 0;
   for(double x = R2Begin; x <= R2End; x = x + (R2End - R2Begin) / 100)
   {
      double FitCentral1 = ParameterA1Value + ParameterB1Value * x;
      double FitCentral2 = ParameterA2Value + ParameterB2Value * x;

      double ParErrorA1 = InitialParameterValues1.GetParError(0);
      double ParErrorB1 = InitialParameterValues1.GetParError(1);
      double ParErrorA2 = InitialParameterValues2.GetParError(0);
      double ParErrorB2 = InitialParameterValues2.GetParError(1);

      double SimpleFitValue1 = 1;
      double SimpleFitError1 = sqrt(ParErrorA1 * ParErrorA1 + ParErrorB1 * ParErrorB1 * x * x) / FitCentral1;
      double SimpleFitValue2 = 1;
      double SimpleFitError2 = sqrt(ParErrorA2 * ParErrorA2 + ParErrorB2 * ParErrorB2 * x * x) / FitCentral2;

      SimpleFitRatioBand1.SetPoint(ABRatioBandCounter, x, SimpleFitValue1);
      SimpleFitRatioBand1.SetPointError(ABRatioBandCounter, 0, SimpleFitError1);
      SimpleFitRatioBand2.SetPoint(ABRatioBandCounter, x, SimpleFitValue2);
      SimpleFitRatioBand2.SetPointError(ABRatioBandCounter, 0, SimpleFitError2);
      
      double Correlation1 = FitResult->correlation("ParameterA1", "ParameterB1");
      double Correlation2 = FitResult->correlation("ParameterA2", "ParameterB2");
      double Value1 = ParameterA1.getVal() + ParameterB1.getVal() * x;
      double Value2 = ParameterA2.getVal() + ParameterB2.getVal() * x;
      double Error1 = sqrt(ParameterA1.getError() * ParameterA1.getError()
         + ParameterB1.getError() * ParameterB1.getError() * x * x
         + 2 * ParameterA1.getError() * ParameterB1.getError() * x * Correlation1);
      double Error2 = sqrt(ParameterA2.getError() * ParameterA2.getError()
         + ParameterB2.getError() * ParameterB2.getError() * x * x
         + 2 * ParameterA2.getError() * ParameterB2.getError() * x * Correlation2);

      ABRatioBand1.SetPoint(ABRatioBandCounter, x, Value1 / FitCentral1);
      ABRatioBand1.SetPointError(ABRatioBandCounter, 0, Error1 / FitCentral1);
      ABRatioBand2.SetPoint(ABRatioBandCounter, x, Value2 / FitCentral2);
      ABRatioBand2.SetPointError(ABRatioBandCounter, 0, Error2 / FitCentral2);

      ABRatioLine1.SetPoint(ABRatioBandCounter, x, Value1 / FitCentral1);
      ABRatioLine2.SetPoint(ABRatioBandCounter, x, Value2 / FitCentral2);

      ABRatioBandCounter = ABRatioBandCounter + 1;
   }

   TCanvas RatioBandCanvas1;

   SimpleFitRatioBand1.SetFillColor(8);
   SimpleFitRatioBand1.SetFillStyle(3344);
   SimpleFitRatioBand1.SetMinimum(0.8);
   SimpleFitRatioBand1.SetMaximum(1.2);
   SimpleFitRatioBand1.Draw("a3");
   SimpleFitRatioBand1.GetXaxis()->SetTitle("(R Cut)^2");
   SimpleFitRatioBand1.GetYaxis()->SetTitle("Exponent / Simple fit central value");
  
   ABRatioBand1.SetFillColor(kCyan - 3);
   ABRatioBand1.SetFillStyle(3144);
   ABRatioBand1.SetLineColor(kBlue);
   ABRatioBand1.SetLineWidth(2);
   ABRatioBand1.Draw("3");
   
   ABRatioLine1.SetLineColor(kBlue);
   ABRatioLine1.SetLineWidth(2);
   ABRatioLine1.Draw("l");

   SingleRatioPoint1.SetLineWidth(2);
   SingleRatioPoint1.Draw("p");

   TLegend RatioLegend(0.65, 0.95, 0.95, 0.75);
   RatioLegend.SetTextFont(42);
   RatioLegend.SetFillColor(0);
   RatioLegend.AddEntry(&SingleRatioPoint1, "Points from simple fit", "lp");
   RatioLegend.AddEntry(&SimpleFitRatioBand1, "Band from simple fit", "f");
   RatioLegend.AddEntry(&ABRatioBand1, "Band from simultaneous fit", "lf");
   RatioLegend.Draw();

   PsFile.AddCanvas(RatioBandCanvas1);
   
   TCanvas RatioBandCanvas2;

   SimpleFitRatioBand2.SetFillColor(8);
   SimpleFitRatioBand2.SetFillStyle(3344);
   SimpleFitRatioBand2.SetMinimum(0.5);
   SimpleFitRatioBand2.SetMaximum(1.5);
   SimpleFitRatioBand2.Draw("a3");
   SimpleFitRatioBand2.GetXaxis()->SetTitle("(R Cut)^2");
   SimpleFitRatioBand2.GetYaxis()->SetTitle("Exponent / Simple fit central value");
  
   ABRatioBand2.SetFillColor(kCyan - 3);
   ABRatioBand2.SetFillStyle(3144);
   ABRatioBand2.SetLineColor(kBlue);
   ABRatioBand2.SetLineWidth(2);
   ABRatioBand2.Draw("3");

   ABRatioLine2.SetLineColor(kBlue);
   ABRatioLine2.SetLineWidth(2);
   ABRatioLine2.Draw("l");

   SingleRatioPoint2.SetLineWidth(2);
   SingleRatioPoint2.Draw("p");
   
   RatioLegend.Draw();

   PsFile.AddCanvas(RatioBandCanvas2);
   
   // parameters a and b
   vector<string> FinalResultExplanation;
   stringstream FitParameterA1Stream;
   FitParameterA1Stream << "Parameter A1 from simultaneous fit = "
      << ParameterA1.getVal() << " +- " << ParameterA1.getError();
   FinalResultExplanation.push_back(FitParameterA1Stream.str());
   stringstream FitParameterB1Stream;
   FitParameterB1Stream << "Parameter B1 from simultaneous fit = "
      << ParameterB1.getVal() << " +- " << ParameterB1.getError();
   FinalResultExplanation.push_back(FitParameterB1Stream.str());
   stringstream FitParameterA2Stream;
   FitParameterA2Stream << "Parameter A2 from simultaneous fit = "
      << ParameterA2.getVal() << " +- " << ParameterA2.getError();
   FinalResultExplanation.push_back(FitParameterA2Stream.str());
   stringstream FitParameterB2Stream;
   FitParameterB2Stream << "Parameter B2 from simultaneous fit = "
      << ParameterB2.getVal() << " +- " << ParameterB2.getError();
   FinalResultExplanation.push_back(FitParameterB2Stream.str());
   // stringstream FitFractionStream;
   // FitFractionStream << "Fraction from simultaneous fit = "
   //    << 1 - Fraction.getVal() << " +- " << Fraction.getError();
   // FinalResultExplanation.push_back(FitFractionStream.str());
   stringstream FitParameterCorrelationStream;
   FitParameterCorrelationStream << "Correlation(a1, b1) = "
      << FitResult->correlation("ParameterA1", "ParameterB1") << ", "
      << "Correlation(a2, b2) = " << FitResult->correlation("ParameterA2", "ParameterB2");
   FinalResultExplanation.push_back(FitParameterCorrelationStream.str());
   FinalResultExplanation.push_back("");
   FinalResultExplanation.push_back(ParameterA1String.str());
   FinalResultExplanation.push_back(ParameterB1String.str());
   FinalResultExplanation.push_back(ParameterA2String.str());
   FinalResultExplanation.push_back(ParameterB2String.str());
   // FinalResultExplanation.push_back(FractionString.str());
   PsFile.AddTextPage(FinalResultExplanation);

   // 2D plot of A and B
   RooPlot ParameterA1B1Plot(ParameterA1, ParameterB1,
      ParameterA1.getVal() * 0.8, ParameterA1.getVal() * 1.2,
      ParameterB1.getVal() * 0.8, ParameterB1.getVal() * 1.2);
   FitResult->plotOn(&ParameterA1B1Plot, ParameterA1, ParameterB1, "ME");
   PsFile.AddPlot(ParameterA1B1Plot);
   
   RooPlot ParameterA2B2Plot(ParameterA2, ParameterB2,
      ParameterA2.getVal() * 0.5, ParameterA2.getVal() * 1.5,
      ParameterB2.getVal() * 0.5, ParameterB2.getVal() * 1.5);
   FitResult->plotOn(&ParameterA2B2Plot, ParameterA2, ParameterB2, "ME");
   PsFile.AddPlot(ParameterA2B2Plot);
   
   RooPlot ParameterA1A2Plot(ParameterA1, ParameterA2,
      ParameterA1.getVal() * 0.8, ParameterA1.getVal() * 1.2,
      ParameterA2.getVal() * 0.5, ParameterA2.getVal() * 1.5);
   FitResult->plotOn(&ParameterA1A2Plot, ParameterA1, ParameterA2, "ME");
   PsFile.AddPlot(ParameterA1A2Plot);
   
   RooPlot ParameterB1B2Plot(ParameterB1, ParameterB2,
      ParameterB1.getVal() * 0.8, ParameterB1.getVal() * 1.2,
      ParameterB2.getVal() * 0.5, ParameterB2.getVal() * 1.5);
   FitResult->plotOn(&ParameterB1B2Plot, ParameterB1, ParameterB2, "ME");
   PsFile.AddPlot(ParameterB1B2Plot);

   // Cleaning....
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      delete TopLevelModels[i];
      if(i != (int)RCuts.size() - 1)
         delete ModelBeforeConstraint[i];
      delete Constraint[i];
      if(i != (int)RCuts.size() - 1)
         delete TopLevelYields[i];

      if(i != (int)RCuts.size() - 1)
      {
         delete NormalizedYields[i];
         delete NormalizedNegativeYields[i];
      }

      if(Component1Models[i] != NULL) delete Component1Models[i];
      if(Component2Models[i] != NULL) delete Component2Models[i];
      if(OneComponent == false && Models[i] != NULL)   delete Models[i];
      if(Yields[i] != NULL)   delete Yields[i];
      if(S1[i] != NULL)       delete S1[i];
      if(S2[i] != NULL)       delete S2[i];
      if(Fraction[i] != NULL) delete Fraction[i];
   }

   TopLevelModels.clear();
   ModelBeforeConstraint.clear();
   Constraint.clear();
   TopLevelYields.clear();

   NormalizedYields.clear();
   NormalizedNegativeYields.clear();

   Component1Models.clear();
   Component2Models.clear();
   Models.clear();
   Yields.clear();
   S1.clear();
   S2.clear();
   Fraction.clear();

   F.Close();

   return FitResult;
}

int GetInteger(string str)
{
   int result = 0;
   stringstream stream(str);
   stream >> result;
   return result;
}

double GetDouble(string str)
{
   double result = 0;
   stringstream stream(str);
   stream >> result;
   return result;
}








