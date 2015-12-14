#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TGraphErrors.h"

#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooTwoSideGaussianWithTwoExponentialTails.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
using namespace RooFit;

#include "PlotHelper.h"
#include "SetStyle.h"

struct SimpleFitResult
{
   double Exp1;
   double Exp1Error;
   double Exp2;
   double Exp2Error;
   double Fraction;
   double FractionError;
};

int main();
SimpleFitResult MRSimpleFit(PsFileHelper &PsFile, double MinR);
SimpleFitResult R2SimpleFit(PsFileHelper &PsFile, double MinMR);

int main()
{
   SetStyle();

   PsFileHelper PsFile("FitResult.ps");
   PsFile.AddTextPage("Yay");

   TGraphErrors MRFitExp1;
   TGraphErrors MRFitExp2;
   TGraphErrors MRFitFraction;

   double RCuts[] = {0.3, 0.32, 0.34, 0.36, 0.38, 0.4, 0.42, 0.44, 0.46, 0.48, 0.5, 0.52};
   for(int i = 0; i < 12; i++)
   {
      SimpleFitResult result = MRSimpleFit(PsFile, RCuts[i]);

      MRFitExp1.SetPoint(i, RCuts[i] * RCuts[i], result.Exp1);
      MRFitExp1.SetPointError(i, 0, result.Exp1Error);
      MRFitExp2.SetPoint(i, RCuts[i] * RCuts[i], result.Exp2);
      MRFitExp2.SetPointError(i, 0, result.Exp2Error);
      MRFitFraction.SetPoint(i, RCuts[i] * RCuts[i], result.Fraction);
      MRFitFraction.SetPointError(i, 0, result.FractionError);
   }

   PsFile.AddPlot(MRFitExp1, "ape");
   PsFile.AddPlot(MRFitExp2, "ape");
   PsFile.AddPlot(MRFitFraction, "ape");

   MRFitExp1.Fit("pol1");
   MRFitExp2.Fit("pol1");

   TGraphErrors R2FitExp1;
   TGraphErrors R2FitExp2;
   TGraphErrors R2FitFraction;

   double MRCuts[] = {300, 320, 340, 360, 380, 400, 420, 440};
   for(int i = 0; i < 8; i++)
   {
      SimpleFitResult result = R2SimpleFit(PsFile, MRCuts[i]);

      R2FitExp1.SetPoint(i, MRCuts[i], result.Exp1);
      R2FitExp1.SetPointError(i, 0, result.Exp1Error);
      R2FitExp2.SetPoint(i, MRCuts[i], result.Exp2);
      R2FitExp2.SetPointError(i, 0, result.Exp2Error);
      R2FitFraction.SetPoint(i, MRCuts[i], result.Fraction);
      R2FitFraction.SetPointError(i, 0, result.FractionError);
   }
   
   PsFile.AddPlot(R2FitExp1, "ape");
   PsFile.AddPlot(R2FitExp2, "ape");
   PsFile.AddPlot(R2FitFraction, "ape");
   
   R2FitExp1.Fit("pol1");
   R2FitExp2.Fit("pol1");
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

SimpleFitResult MRSimpleFit(PsFileHelper &PsFile, double MinR)
{
   RooRealVar MR("MR", "MR", 300.0, 3500.0, "GeV");
   RooRealVar R("R", "R", MinR, 2.0);

   MR.setRange("FitRange", 300, 3500);
   R.setRange("FitRange", MinR, 2.0);
   
   TFile F("TTJets_TuneZ2_7TeV-madgraph-tauola_MR200.0_R0.2_Had.root");
   RooDataSet *DataSet = (RooDataSet *)F.Get("RMRTree");
   if(DataSet == NULL)
      return SimpleFitResult();

   RooRealVar Exp1("Exp1", "Exp1", -0.0106029, -1.0, 0.0);
   RooExponential Component1("Component1", "Component1", MR, Exp1);

   RooRealVar Exp2("Exp2", "Exp2", -0.00534574, -1.0, 0.0);
   RooExponential Component2("Component2", "Component2", MR, Exp2);

   RooRealVar Fraction("Fraction", "Fraction", 0.804495, 0, 1);
   RooAddPdf Model("Model", "Model", Component1, Component2, Fraction);

   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet->reduce(Form("R > %f", MinR));
   Model.fitTo(*ReducedDataSet, Range("FitRange"));

   RooPlot *ResultPlot = MR.frame(Bins(100), Name("FitResult"), Title("MR!!!!!"));
   ReducedDataSet->plotOn(ResultPlot, MarkerColor(1), MarkerSize(0.8));
   Model.plotOn(ResultPlot, LineColor(kBlue));
   ResultPlot->SetMinimum(0.3);
   PsFile.AddPlot(ResultPlot, "", true);

   SimpleFitResult Result;
   Result.Exp1 = Exp1.getVal();
   Result.Exp1Error = Exp1.getError();
   Result.Exp2 = Exp2.getVal();
   Result.Exp2Error = Exp2.getError();
   Result.Fraction = Fraction.getVal();
   Result.FractionError = Fraction.getError();

   if(Result.Exp1 > Result.Exp2)
   {
      swap(Result.Exp1, Result.Exp2);
      swap(Result.Exp1Error, Result.Exp2Error);
      Result.Fraction = 1 - Result.Fraction;
   }

   F.Close();

   return Result;
}

SimpleFitResult R2SimpleFit(PsFileHelper &PsFile, double MinMR)
{
   RooRealVar MR("MR", "MR", MinMR, 3500.0, "GeV");
   RooRealVar Rsq("Rsq", "Rsq", 0.09, 2.0);

   MR.setRange("FitRange", MinMR, 3500);
   Rsq.setRange("FitRange", 0.09, 4.0);
   
   TFile F("TTJets_TuneZ2_7TeV-madgraph-tauola_MR200.0_R0.2_Had.root");
   RooDataSet *DataSet = (RooDataSet *)F.Get("RMRTree");
   if(DataSet == NULL)
      return SimpleFitResult();

   RooRealVar Exp1("Exp1", "Exp1", -0.0106029, -50.0, 0.0);
   RooExponential Component1("Component1", "Component1", Rsq, Exp1);

   RooRealVar Exp2("Exp2", "Exp2", -0.00534574, -50.0, 0.0);
   RooExponential Component2("Component2", "Component2", Rsq, Exp2);

   RooRealVar Fraction("Fraction", "Fraction", 0.804495, 0, 1);
   RooAddPdf Model("Model", "Model", Component1, Component2, Fraction);

   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet->reduce(Form("MR > %f", MinMR));
   Model.fitTo(*ReducedDataSet, Range("FitRange"));

   RooPlot *ResultPlot = Rsq.frame(Bins(100), Name("FitResult"), Title("R*R!!!!!"));
   ReducedDataSet->plotOn(ResultPlot, MarkerColor(1), MarkerSize(0.8));
   Model.plotOn(ResultPlot, LineColor(kBlue));
   ResultPlot->SetMinimum(0.3);
   PsFile.AddPlot(ResultPlot, "", true);

   SimpleFitResult Result;
   Result.Exp1 = Exp1.getVal();
   Result.Exp1Error = Exp1.getError();
   Result.Exp2 = Exp2.getVal();
   Result.Exp2Error = Exp2.getError();
   Result.Fraction = Fraction.getVal();
   Result.FractionError = Fraction.getError();

   if(Result.Exp1 > Result.Exp2)
   {
      swap(Result.Exp1, Result.Exp2);
      swap(Result.Exp1Error, Result.Exp2Error);
      Result.Fraction = 1 - Result.Fraction;
   }

   F.Close();

   return Result;
}









