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
#include "RooGaussian.h"
using namespace RooFit;

#include "PlotHelper2.h"
#include "DrawRandom.h"
#include "SetStyle.h"

struct SingleFitResult;
int main(int argc, char *argv[]);
SingleFitResult FitWithRCut(PsFileHelper &PsFile, string FileName, double RCut);
RooFitResult *FitWithRCut(PsFileHelper &PsFile, string FileName, vector<double> RCuts);

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
   SetStyle();

   int NumberOfTries = 20;

   vector<RooFitResult *> FitResultsData;
   vector<RooFitResult *> FitResultsW;

   for(int i = 0; i < NumberOfTries; i++)
   {
      vector<double> CutsToTry;
      CutsToTry.push_back(DrawRandom(0.20, 0.21));
      // CutsToTry.push_back(DrawRandom(0.25, 0.26));
      CutsToTry.push_back(DrawRandom(0.30, 0.31));
      // CutsToTry.push_back(DrawRandom(0.35, 0.36));
      CutsToTry.push_back(DrawRandom(0.40, 0.41));

      PsFileHelper PsFile(Form("DataMultiFit%d.ps", i));
      PsFile.AddTextPage("Fit data in the muon box");
      RooFitResult *Result = FitWithRCut(PsFile, "DataPlots.root", CutsToTry);
      PsFile.AddTimeStampPage();
      PsFile.Close();

      FitResultsData.push_back(Result);
   }

   for(int i = 0; i < NumberOfTries; i++)
   {
      vector<double> CutsToTry;
      CutsToTry.push_back(DrawRandom(0.20, 0.21));
      // CutsToTry.push_back(DrawRandom(0.25, 0.26));
      CutsToTry.push_back(DrawRandom(0.30, 0.31));
      // CutsToTry.push_back(DrawRandom(0.35, 0.36));
      CutsToTry.push_back(DrawRandom(0.40, 0.41));
   
      PsFileHelper PsFile(Form("WMultiFit%d.ps", i));
      PsFile.AddTextPage("Fit W in the muon box");
      RooFitResult *Result = FitWithRCut(PsFile, "W.root", CutsToTry);
      PsFile.AddTimeStampPage();
      PsFile.Close();

      FitResultsW.push_back(Result);
   }

   TFile F("YAYAYA.root", "recreate");

   PsFileHelper PsFile("TotalPlot.ps");

   vector<double> DataAValues1;
   vector<double> DataBValues1;
   vector<double> DataAValues2;
   vector<double> DataBValues2;
   vector<double> WAValues1;
   vector<double> WBValues1;
   vector<double> WAValues2;
   vector<double> WBValues2;

   double DataA1;
   double DataB1;
   double DataA2;
   double DataB2;
   double WA1;
   double WB1;
   double WA2;
   double WB2;

   RooPlot ParameterABPlot1(0.008, 0.016, 0.001, 0.02);
   RooPlot ParameterABPlot2(0.004, 0.008, 0.001, 0.04);
   ParameterABPlot1.GetXaxis()->SetTitle("Parameter A1");
   ParameterABPlot1.GetYaxis()->SetTitle("Parameter B1");
   ParameterABPlot2.GetXaxis()->SetTitle("Parameter A2");
   ParameterABPlot2.GetYaxis()->SetTitle("Parameter B2");
   ParameterABPlot1.SetTitle("Summary of fits to data and W in muon selection (anti-loose-30)");
   ParameterABPlot2.SetTitle("Summary of fits to data and W in muon selection (anti-loose-30)");
   for(int i = 0; i < NumberOfTries; i++)
   {
      double x = ((RooRealVar *)FitResultsData[i]->floatParsFinal().find("ParameterA1"))->getVal();
      double y = ((RooRealVar *)FitResultsData[i]->floatParsFinal().find("ParameterB1"))->getVal();
      double ex = ((RooRealVar *)FitResultsData[i]->floatParsFinal().find("ParameterA1"))->getError();
      double ey = ((RooRealVar *)FitResultsData[i]->floatParsFinal().find("ParameterB1"))->getError();
      double rho = FitResultsData[i]->correlation("ParameterA1", "ParameterB1");
      RooEllipse *Contour = new RooEllipse(Form("DataEllipse%d", i), x, y, ex, ey, rho);
      Contour->SetLineWidth(2);
      Contour->SetLineColor(kBlue);
      ParameterABPlot1.addPlotable(Contour);

      DataAValues1.push_back(x);
      DataBValues1.push_back(y);
      DataA1 = DataA1 + x / NumberOfTries;
      DataB1 = DataB1 + y / NumberOfTries;
      
      x = ((RooRealVar *)FitResultsData[i]->floatParsFinal().find("ParameterA2"))->getVal();
      y = ((RooRealVar *)FitResultsData[i]->floatParsFinal().find("ParameterB2"))->getVal();
      ex = ((RooRealVar *)FitResultsData[i]->floatParsFinal().find("ParameterA2"))->getError();
      ey = ((RooRealVar *)FitResultsData[i]->floatParsFinal().find("ParameterB2"))->getError();
      rho = FitResultsData[i]->correlation("ParameterA2", "ParameterB2");
      Contour = new RooEllipse(Form("DataEllipse%d", i), x, y, ex, ey, rho);
      Contour->SetLineWidth(2);
      Contour->SetLineColor(kBlue);
      ParameterABPlot2.addPlotable(Contour);

      DataAValues2.push_back(x);
      DataBValues2.push_back(y);
      DataA2 = DataA2 + x / NumberOfTries;
      DataB2 = DataB2 + y / NumberOfTries;
      
      x = ((RooRealVar *)FitResultsW[i]->floatParsFinal().find("ParameterA1"))->getVal();
      y = ((RooRealVar *)FitResultsW[i]->floatParsFinal().find("ParameterB1"))->getVal();
      ex = ((RooRealVar *)FitResultsW[i]->floatParsFinal().find("ParameterA1"))->getError();
      ey = ((RooRealVar *)FitResultsW[i]->floatParsFinal().find("ParameterB1"))->getError();
      rho = FitResultsW[i]->correlation("ParameterA1", "ParameterB1");
      Contour = new RooEllipse(Form("WEllipse%d", i), x, y, ex, ey, rho);
      Contour->SetLineWidth(2);
      Contour->SetLineColor(kRed);
      ParameterABPlot1.addPlotable(Contour);
      
      WAValues1.push_back(x);
      WBValues1.push_back(y);
      WA1 = WA1 + x / NumberOfTries;
      WB1 = WB1 + y / NumberOfTries;
      
      x = ((RooRealVar *)FitResultsW[i]->floatParsFinal().find("ParameterA2"))->getVal();
      y = ((RooRealVar *)FitResultsW[i]->floatParsFinal().find("ParameterB2"))->getVal();
      ex = ((RooRealVar *)FitResultsW[i]->floatParsFinal().find("ParameterA2"))->getError();
      ey = ((RooRealVar *)FitResultsW[i]->floatParsFinal().find("ParameterB2"))->getError();
      rho = FitResultsW[i]->correlation("ParameterA2", "ParameterB2");
      Contour = new RooEllipse(Form("WEllipse%d", i), x, y, ex, ey, rho);
      Contour->SetLineWidth(2);
      Contour->SetLineColor(kRed);
      ParameterABPlot2.addPlotable(Contour);
      
      WAValues2.push_back(x);
      WBValues2.push_back(y);
      WA2 = WA2 + x / NumberOfTries;
      WB2 = WB2 + y / NumberOfTries;
   }
   ParameterABPlot1.Write();
   ParameterABPlot2.Write();

   sort(DataAValues1.begin(), DataAValues1.end());
   sort(DataBValues1.begin(), DataBValues1.end());
   sort(WAValues1.begin(), WAValues1.end());
   sort(WBValues1.begin(), WBValues1.end());
   sort(DataAValues2.begin(), DataAValues2.end());
   sort(DataBValues2.begin(), DataBValues2.end());
   sort(WAValues2.begin(), WAValues2.end());
   sort(WBValues2.begin(), WBValues2.end());

   double DataAMedian1 = DataAValues1[DataAValues1.size()/2];
   double DataBMedian1 = DataBValues1[DataBValues1.size()/2];
   double WAMedian1 = WAValues1[WAValues1.size()/2];
   double WBMedian1 = WBValues1[WBValues1.size()/2];
   double DataAMedian2 = DataAValues2[DataAValues2.size()/2];
   double DataBMedian2 = DataBValues2[DataBValues2.size()/2];
   double WAMedian2 = WAValues2[WAValues2.size()/2];
   double WBMedian2 = WBValues2[WBValues2.size()/2];

   TGraph DataHorizontalLine1, DataVerticalLine1;
   DataHorizontalLine1.SetPoint(0, -100, DataBMedian1);
   DataHorizontalLine1.SetPoint(1, 100, DataBMedian1);
   DataVerticalLine1.SetPoint(0, DataAMedian1, -100);
   DataVerticalLine1.SetPoint(1, DataAMedian1, 100);

   TGraph DataHorizontalLineAverage1, DataVerticalLineAverage1;
   DataHorizontalLineAverage1.SetPoint(0, -100, DataB1);
   DataHorizontalLineAverage1.SetPoint(1, 100, DataB1);
   DataVerticalLineAverage1.SetPoint(0, DataA1, -100);
   DataVerticalLineAverage1.SetPoint(1, DataA1, 100);

   TGraph DataHorizontalLine2, DataVerticalLine2;
   DataHorizontalLine2.SetPoint(0, -100, DataBMedian2);
   DataHorizontalLine2.SetPoint(1, 100, DataBMedian2);
   DataVerticalLine2.SetPoint(0, DataAMedian2, -100);
   DataVerticalLine2.SetPoint(1, DataAMedian2, 100);

   TGraph DataHorizontalLineAverage2, DataVerticalLineAverage2;
   DataHorizontalLineAverage2.SetPoint(0, -100, DataB2);
   DataHorizontalLineAverage2.SetPoint(1, 100, DataB2);
   DataVerticalLineAverage2.SetPoint(0, DataA2, -100);
   DataVerticalLineAverage2.SetPoint(1, DataA2, 100);

   TGraph WHorizontalLine1, WVerticalLine1;
   WHorizontalLine1.SetPoint(0, -100, WBMedian1);
   WHorizontalLine1.SetPoint(1, 100, WBMedian1);
   WVerticalLine1.SetPoint(0, WAMedian1, -100);
   WVerticalLine1.SetPoint(1, WAMedian1, 100);

   TGraph WHorizontalLineAverage1, WVerticalLineAverage1;
   WHorizontalLineAverage1.SetPoint(0, -100, WB1);
   WHorizontalLineAverage1.SetPoint(1, 100, WB1);
   WVerticalLineAverage1.SetPoint(0, WA1, -100);
   WVerticalLineAverage1.SetPoint(1, WA1, 100);

   TGraph WHorizontalLine2, WVerticalLine2;
   WHorizontalLine2.SetPoint(0, -100, WBMedian2);
   WHorizontalLine2.SetPoint(1, 100, WBMedian2);
   WVerticalLine2.SetPoint(0, WAMedian2, -100);
   WVerticalLine2.SetPoint(1, WAMedian2, 100);

   TGraph WHorizontalLineAverage2, WVerticalLineAverage2;
   WHorizontalLineAverage2.SetPoint(0, -100, WB2);
   WHorizontalLineAverage2.SetPoint(1, 100, WB2);
   WVerticalLineAverage2.SetPoint(0, WA2, -100);
   WVerticalLineAverage2.SetPoint(1, WA2, 100);

   DataHorizontalLine1.SetLineColor(kBlue);
   DataVerticalLine1.SetLineColor(kBlue);
   WHorizontalLine1.SetLineColor(kRed);
   WVerticalLine1.SetLineColor(kRed);
   DataHorizontalLine2.SetLineColor(kBlue);
   DataVerticalLine2.SetLineColor(kBlue);
   WHorizontalLine2.SetLineColor(kRed);
   WVerticalLine2.SetLineColor(kRed);
   
   DataHorizontalLineAverage1.SetLineColor(kBlue);
   DataVerticalLineAverage1.SetLineColor(kBlue);
   WHorizontalLineAverage1.SetLineColor(kRed);
   WVerticalLineAverage1.SetLineColor(kRed);
   DataHorizontalLineAverage2.SetLineColor(kBlue);
   DataVerticalLineAverage2.SetLineColor(kBlue);
   WHorizontalLineAverage2.SetLineColor(kRed);
   WVerticalLineAverage2.SetLineColor(kRed);
   
   DataHorizontalLine1.SetLineWidth(2);
   DataVerticalLine1.SetLineWidth(2);
   WHorizontalLine1.SetLineWidth(2);
   WVerticalLine1.SetLineWidth(2);
   DataHorizontalLine2.SetLineWidth(2);
   DataVerticalLine2.SetLineWidth(2);
   WHorizontalLine2.SetLineWidth(2);
   WVerticalLine2.SetLineWidth(2);
   
   DataHorizontalLineAverage1.SetLineWidth(2);
   DataVerticalLineAverage1.SetLineWidth(2);
   WHorizontalLineAverage1.SetLineWidth(2);
   WVerticalLineAverage1.SetLineWidth(2);
   DataHorizontalLineAverage2.SetLineWidth(2);
   DataVerticalLineAverage2.SetLineWidth(2);
   WHorizontalLineAverage2.SetLineWidth(2);
   WVerticalLineAverage2.SetLineWidth(2);

   DataHorizontalLineAverage1.SetLineStyle(10);
   DataVerticalLineAverage1.SetLineStyle(10);
   WHorizontalLineAverage1.SetLineStyle(10);
   WVerticalLineAverage1.SetLineStyle(10);
   DataHorizontalLineAverage2.SetLineStyle(10);
   DataVerticalLineAverage2.SetLineStyle(10);
   WHorizontalLineAverage2.SetLineStyle(10);
   WVerticalLineAverage2.SetLineStyle(10);

   TLegend legend(0.6, 0.6, 0.85, 0.7);
   legend.SetFillColor(0);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.AddEntry(&DataHorizontalLine1, "Data", "l");
   legend.AddEntry(&WHorizontalLine1, "W", "l");
   
   TGraph ExampleMedian, ExampleAverage;
   ExampleMedian.SetLineWidth(2);
   ExampleAverage.SetLineWidth(2);
   ExampleAverage.SetLineStyle(10);

   TLegend legend2(0.6, 0.75, 0.85, 0.85);
   legend2.SetFillColor(0);
   legend2.SetFillStyle(0);
   legend2.SetBorderSize(0);
   legend2.AddEntry(&ExampleMedian, "Median", "l");
   legend2.AddEntry(&ExampleAverage, "Average", "l");

   TCanvas ParameterABCanvas;
   ParameterABPlot1.Draw();
   DataHorizontalLine1.Draw("l");
   DataVerticalLine1.Draw("l");
   WHorizontalLine1.Draw("l");
   WVerticalLine1.Draw("l");
   DataHorizontalLineAverage1.Draw("l");
   DataVerticalLineAverage1.Draw("l");
   WHorizontalLineAverage1.Draw("l");
   WVerticalLineAverage1.Draw("l");
   legend.Draw();
   legend2.Draw();
   PsFile.AddCanvas(ParameterABCanvas);
   
   TCanvas ParameterABCanvas2;
   ParameterABPlot2.Draw();
   DataHorizontalLine2.Draw("l");
   DataVerticalLine2.Draw("l");
   WHorizontalLine2.Draw("l");
   WVerticalLine2.Draw("l");
   DataHorizontalLineAverage2.Draw("l");
   DataVerticalLineAverage2.Draw("l");
   WHorizontalLineAverage2.Draw("l");
   WVerticalLineAverage2.Draw("l");
   legend.Draw();
   legend2.Draw();
   PsFile.AddCanvas(ParameterABCanvas2);
   
   /*
   RooPlot ParameterABPlot2(0.003, 0.01, 0, 0.04);
   for(int i = 0; i < NumberOfTries; i++)
   {
      if(FitResultsData[i] != NULL)
         FitResultsData[i]->plotOn(&ParameterABPlot2, "ParameterA1", "ParameterB1", "M");
      if(FitResultsW[i] != NULL)
         FitResultsW[i]->plotOn(&ParameterABPlot2, "ParameterA1", "ParameterB1", "M");
   }
   PsFile.AddPlot(ParameterABPlot2);
   ParameterABPlot2.Write();
   */
   
   F.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

SingleFitResult FitWithRCut(PsFileHelper &PsFile, string FileName, double RCut)
{
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return SingleFitResult();

   double MRLowerBound = 250;
   double MRUpperBound = 1500;

   string MRString = "MR";
   string RString = "R";

   RooRealVar MR(MRString.c_str(), "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R(RString.c_str(), "Chris' another kinematic variable", -200, 200);
   RooArgSet TreeVarSet(MR, R);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, Form("%s > %f", RString.c_str(), RCut));

   RooRealVar S1("S1", "first exponent of the tail", -0.01, -1.0, 0.0);
   RooExponential Component1("Component1", "First component", MR, S1);
   
   RooRealVar S2("S2", "second exponent of the tail", -0.003, -1.0, 0.0);
   RooExponential Component2("Component2", "Second component", MR, S2);

   RooRealVar Fraction("Fraction", "Fraction of the second component at zero", 0.7, 0, 1);
   RooAddPdf *Model = new RooAddPdf("Model", "Model", Component1, Component2, Fraction);

   // RooFitResult *FitResult = Model->fitTo(Dataset, Save(true));
   // Component1.fitTo(Dataset);
   Model->fitTo(Dataset);

   stringstream Subtitle;
   Subtitle << "Fitting with R cut = " << RCut;
   PsFile.AddTextPage(Subtitle.str());

   RooPlot *ParameterPlot = MR.frame(Bins(50), Name("FitParameters"), Title("Fit parameters"));
   Model->paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.4, 0.9));
   PsFile.AddPlot(ParameterPlot, "", false);

   RooPlot *FinalResultPlot = MR.frame(Bins(50), Name("FitResults"), Title("MR"), AutoRange(Dataset));
   Dataset.plotOn(FinalResultPlot, MarkerSize(0.9));
   Model->plotOn(FinalResultPlot, LineColor(kBlue));
   Model->plotOn(FinalResultPlot, LineColor(kGreen), Components(Component1));
   Model->plotOn(FinalResultPlot, LineColor(kRed), Components(Component2));
   // Component1.plotOn(FinalResultPlot, LineColor(kBlue));
   // Component1.plotOn(FinalResultPlot, LineColor(kGreen), Components(Component1));
   PsFile.AddPlot(FinalResultPlot, "", true);

   SingleFitResult result;

   result.S1 = -S1.getVal();
   result.S1Error = S1.getError();
   result.S2 = -S2.getVal();
   result.S2Error = S2.getError();
   result.F = 1 - Fraction.getVal();
   result.FError = Fraction.getError();

   if(result.S1 < result.S2)
   {
      swap(result.S1, result.S2);
      swap(result.S1Error, result.S2Error);
      result.F = 1 - result.F;
   }

   delete Model;

   F.Close();

   return result;
}

RooFitResult *FitWithRCut(PsFileHelper &PsFile, string FileName, vector<double> RCuts)
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
      SingleFitResults[i] = FitWithRCut(PsFile, FileName, RCuts[i]);

   PsFile.AddTextPage("Putting everything together");

   TGraphErrors SingleCentralValues1;
   SingleCentralValues1.SetNameTitle("SingleCentralValues1", "Central values from single fits, component 1");
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      SingleCentralValues1.SetPoint(i, RCuts[i] * RCuts[i], SingleFitResults[i].S1);
      SingleCentralValues1.SetPointError(i, 0, SingleFitResults[i].S1Error);
   }

   TGraphErrors SingleCentralValues2;
   SingleCentralValues2.SetNameTitle("SingleCentralValues2", "Central values from single fits, component 2");
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      SingleCentralValues2.SetPoint(i, RCuts[i] * RCuts[i], SingleFitResults[i].S2);
      SingleCentralValues2.SetPointError(i, 0, SingleFitResults[i].S2Error);
   }

   TGraphErrors SingleFraction;
   SingleFraction.SetNameTitle("SingleFraction", "Central values from single fits, fraction");
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      SingleFraction.SetPoint(i, RCuts[i] * RCuts[i], SingleFitResults[i].F);
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

   double ParameterA1Value = InitialParameterValues1.GetParameter(0);
   double ParameterB1Value = InitialParameterValues1.GetParameter(1);
   double ParameterA2Value = InitialParameterValues2.GetParameter(0);
   double ParameterB2Value = InitialParameterValues2.GetParameter(1);
   double FractionValue = InitialFraction.GetParameter(0);

   SingleCentralValues1.SetLineWidth(2);
   SingleCentralValues1.SetMarkerStyle(1);
   PsFile.AddPlot(SingleCentralValues1, "ap");
   
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
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return NULL;

   double MRLowerBound = DrawRandom(250, 251);
   double MRUpperBound = 1500;

   string MRString = "MR";
   string RString = "R";

   RooRealVar MR(MRString.c_str(), "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R(RString.c_str(), "Chris' another kinematic variable", -200, 200);
   RooArgSet TreeVarSet(MR, R);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, Form("%s > %f", RString.c_str(), RCuts[0]));

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
         Form("-1 * @0 - %f * @1", RCuts[i] * RCuts[i]), RooArgList(ParameterA1, ParameterB1)));
      S2.push_back(new RooFormulaVar(Form("S2_%d", i),
         Form("exponent 2 of the tail, R > %f", RCuts[i]),
         Form("-1 * @0 - %f * @1", RCuts[i] * RCuts[i]), RooArgList(ParameterA2, ParameterB2)));

      Component1Models.push_back(new RooExponential(Form("Model1_%d", i), Form("First model for R > %f", RCuts[i]),
         MR, *S1[i]));
      Component2Models.push_back(new RooExponential(Form("Model2_%d", i), Form("Second model for R > %f", RCuts[i]),
         MR, *S2[i]));
   
      
      Fraction.push_back(new RooRealVar(Form("Fraction_%d", i), Form("Fraction_%d", i),
         1 - FractionValue, 0.0, 1.0));

      // Models.push_back(Component1Models[i]);
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

   RooAddPdf AlmostFinalModel("AlmostFinalModel", "Almost-final model!", ModelList, YieldList);

   RooRealVar ParameterA1Var("ParameterA1Var", "ParameterA1Var", 0.010);
   RooRealVar ParameterA2Var("ParameterA2Var", "ParameterA2Var", 0.006);
   RooRealVar ParameterB1Var("ParameterB1Var", "ParameterB1Var", 0.054);
   RooRealVar ParameterB2Var("ParameterB2Var", "ParameterB2Var", 0.016);
   RooRealVar ParameterA1Error("ParameterA1Error", "ParameterA1Error", 0.001);
   RooRealVar ParameterA2Error("ParameterA2Error", "ParameterA2Error", 0.001);
   RooRealVar ParameterB1Error("ParameterB1Error", "ParameterB1Error", 0.010);
   RooRealVar ParameterB2Error("ParameterB2Error", "ParameterB2Error", 0.005);
   RooGaussian ParameterA1Penalty("ParameterA1Penalty", "Parameter A1 Penalty",
      ParameterA1, ParameterA1Var, ParameterA1Error);
   RooGaussian ParameterA2Penalty("ParameterA2Penalty", "Parameter A2 Penalty",
      ParameterA2, ParameterA2Var, ParameterA2Error);
   RooGaussian ParameterB1Penalty("ParameterB1Penalty", "Parameter B1 Penalty",
      ParameterB1, ParameterB1Var, ParameterB1Error);
   RooGaussian ParameterB2Penalty("ParameterB2Penalty", "Parameter B2 Penalty",
      ParameterB2, ParameterB2Var, ParameterB2Error);
   RooProdPdf FinalModel("FinalModel", "Final model!!!",
      RooArgSet(AlmostFinalModel, ParameterA1Penalty, ParameterA2Penalty, ParameterB1Penalty, ParameterB2Penalty));

   RooFitResult *FitResult = FinalModel.fitTo(Dataset, Save(true), PrintEvalErrors(-1), NumCPU(3));
   
   PsFile.AddTextPage("Simultaneous fit!");

   // Total model vs. total data
   RooPlot *FinalResultPlot = MR.frame(Bins(50), Name("FitResults"), Title("MR, Simultaneous fit, total model"));
   Dataset.plotOn(FinalResultPlot, MarkerSize(0.9));
   FinalModel.plotOn(FinalResultPlot, LineColor(kBlue));
   PsFile.AddPlot(FinalResultPlot, "", true);

   // Each bin, model vs. data
   RooPlot *FinalResultPlot2 = MR.frame(Bins(50), Name("FitResults2"), Title("MR, Simultaneous fit"));
   Dataset.plotOn(FinalResultPlot2, MarkerSize(0.9), MarkerColor(1));
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      RooArgList ComponentsToAdd;
      for(int j = i; j < (int)RCuts.size(); j++)
         ComponentsToAdd.add(*TopLevelModels[j]);
      FinalModel.plotOn(FinalResultPlot2, LineColor(kBlue), Components(ComponentsToAdd), LineColor(i + 1));
   }
   for(int i = 1; i < (int)RCuts.size(); i++)
      Dataset.reduce(Cut(Form("%s > %f", RString.c_str(), RCuts[i])))->plotOn(FinalResultPlot2,
      MarkerSize(0.9), MarkerColor(i + 1));

   TCanvas FinalResultCanvas2;

   FinalResultPlot2->Draw();

   vector<TH1D *> DummyHistograms;   
   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.SetFillColor(0);
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      DummyHistograms.push_back(new TH1D(Form("DummyHistogram_%d", i), "Dummy!", 2, 0, 1));
      DummyHistograms[i]->SetLineColor(i + 1);
      DummyHistograms[i]->SetLineWidth(2);
      legend.AddEntry(DummyHistograms[i], Form("R > %f", RCuts[i]), "l");
   }
   legend.Draw();

   FinalResultCanvas2.SetLogy();

   PsFile.AddCanvas(FinalResultCanvas2);

   for(int i = 0; i < (int)RCuts.size(); i++)
      delete DummyHistograms[i];
   DummyHistograms.clear();
   
   // simultaneous fit vs. normal fit
   TGraphErrors ABBand1, ABBand2;
   ABBand1.SetNameTitle("ABBand1", "Comparison between simple fit and simultaneous fit, component 1");
   ABBand2.SetNameTitle("ABBand2", "Comparison between simple fit and simultaneous fit, component 2");
   int ABBandCounter = 0;
   double R2Begin = RCuts[0] * RCuts[0] - 0.03;
   double R2End = RCuts[RCuts.size()-1] * RCuts[RCuts.size()-1] + 0.03;
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
      double FitCentral1 = ParameterA1Value + ParameterB1Value * RCuts[i] * RCuts[i];
      double FitCentral2 = ParameterA2Value + ParameterB2Value * RCuts[i] * RCuts[i];

      SingleRatioPoint1.SetPoint(i, RCuts[i] * RCuts[i], SingleFitResults[i].S1 / FitCentral1);
      SingleRatioPoint1.SetPointError(i, 0, SingleFitResults[i].S1Error / FitCentral1);
      SingleRatioPoint2.SetPoint(i, RCuts[i] * RCuts[i], SingleFitResults[i].S2 / FitCentral2);
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
      if(Models[i] != NULL)   delete Models[i];
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










