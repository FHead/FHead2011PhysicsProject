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
#include "TGraphErrors.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooTwoSideGaussianWithAnExponentialTail.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooFormulaVar.h"
#include "RooFitResult.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooSameAs.h"
#include "RooAtLeast.h"
#include "RooAbsPdf.h"
using namespace RooFit;

#include "PlotHelper2.h"

struct SingleFitResult;
int main(int argc, char *argv[]);
SingleFitResult FitWithRCut(PsFileHelper &PsFile, string Filename, double RCut);
void FitWithRCut(PsFileHelper &PsFile, string Filename, vector<double> RCuts);

struct SingleFitResult
{
   double X0;
   double SigmaL;
   double SigmaR;
   double S;
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

   PsFileHelper PsFile("DevelopFit.ps");

   vector<double> CutsToTry;
   // CutsToTry.push_back(0.15);
   // CutsToTry.push_back(0.20);
   // CutsToTry.push_back(0.25);
   CutsToTry.push_back(0.30);
   // CutsToTry.push_back(0.35);
   CutsToTry.push_back(0.40);
   // CutsToTry.push_back(0.45);
   CutsToTry.push_back(0.50);
   
   FitWithRCut(PsFile, "TTbar_MRTree.root", CutsToTry);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

SingleFitResult FitWithRCut(PsFileHelper &PsFile, string Filename, double RCut)
{
   TFile F(Filename.c_str());
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return SingleFitResult();

   RooRealVar MR("MR", "Chris' kinematic variable", 150, 1250, "GeV");
   RooRealVar R("R", "Chris' another kinematic variable", -200, 200);
   RooArgSet TreeVarSet(MR, R);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, Form("R > %f", RCut));

   RooRealVar X0("X0", "gaussian mean", 200, 0, 5000, "GeV");
   RooRealVar SigmaL("SigmaL", "left-hand side gaussian width", 50, 0, 5000, "GeV");
   RooRealVar SigmaR("SigmaR", "right-hand side gaussian width", 50, 0, 5000, "GeV");
   RooRealVar S("S", "exponent of the tail", 0.01, 0, 0.5);
   RooTwoSideGaussianWithAnExponentialTail Model("Model", "Model", MR, X0, SigmaL, SigmaR, S);

   RooFitResult *FitResult = Model.fitTo(Dataset, Save(true));

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

   SingleFitResult result;

   result.X0 = X0.getVal();
   result.SigmaL = SigmaL.getVal();
   result.SigmaR = SigmaR.getVal();
   result.S = S.getVal();

   return result;
}

void FitWithRCut(PsFileHelper &PsFile, string Filename, vector<double> RCuts)
{
   if(RCuts.size() == 0)
      return;
   // if(RCuts.size() == 1)
   // {
   //    cout << "If you want to fit with just one R-cut, use the easy version!" << endl;
   //    return;
   // }

   sort(RCuts.begin(), RCuts.end());

   vector<SingleFitResult> SingleFitResults;
   for(int i = 0; i < (int)RCuts.size(); i++)
      SingleFitResults.push_back(FitWithRCut(PsFile, Filename, RCuts[i]));

   PsFile.AddTextPage("Putting everything together");

   TGraph SingleCentralValues;
   SingleCentralValues.SetNameTitle("SingleCentralValues", "Central values from single fits");
   for(int i = 0; i < (int)RCuts.size(); i++)
      SingleCentralValues.SetPoint(i, RCuts[i] * RCuts[i], SingleFitResults[i].S);

   TF1 InitialParameterValues("InitialParameterValues", "pol1");
   SingleCentralValues.Fit(&InitialParameterValues);

   double ParameterAValue = InitialParameterValues.GetParameter(0);
   double ParameterBValue = InitialParameterValues.GetParameter(1);

   SingleCentralValues.SetMarkerStyle(8);
   PsFile.AddPlot(SingleCentralValues, "ap");

   vector<string> SingleFitParameterExplanation;
   stringstream ParameterAString;
   ParameterAString << "Parameter A from single fit: " << ParameterAValue << " +- "
      << InitialParameterValues.GetParError(0);
   SingleFitParameterExplanation.push_back(ParameterAString.str());
   stringstream ParameterBString;
   ParameterBString << "Parameter B from single fit: " << ParameterBValue << " +- "
      << InitialParameterValues.GetParError(1);
   SingleFitParameterExplanation.push_back(ParameterBString.str());
   SingleFitParameterExplanation.push_back("Friendly reminder: s = a + b * (R cut)^2");
   SingleFitParameterExplanation.push_back("Exponential part in the fit is exp(-s * MR)");
   PsFile.AddTextPage(SingleFitParameterExplanation);

   TFile F(Filename.c_str());
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return;

   RooRealVar MR("MR", "Chris' kinematic variable", 150, 1500, "GeV");
   RooRealVar R("R", "Chris' another kinematic variable", -200, 200);
   RooArgSet TreeVarSet(MR, R);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, Form("R > %f", RCuts[0]));

   RooRealVar ParameterA("ParameterA", "s = \"a\" + b R^2", ParameterAValue, 0, 0.1);
   RooRealVar ParameterB("ParameterB", "s = a + \"b\" R^2", ParameterBValue, 0, 1);

   vector<RooRealVar *> X0;
   vector<RooRealVar *> SigmaL;
   vector<RooRealVar *> SigmaR;
   vector<RooFormulaVar *> S;
   vector<RooRealVar *> Yields;
   vector<RooFormulaVar *> NegativeYields;
   vector<RooFormulaVar *> NormalizedYields;
   vector<RooFormulaVar *> NormalizedNegativeYields;

   vector<RooTwoSideGaussianWithAnExponentialTail *> Models;

   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      double GuessYield = Dataset.reduce(Cut(Form("R > %f", RCuts[i])))->sumEntries();

      X0.push_back(new RooRealVar(Form("X0_%d", i),
         Form("gaussian mean, R > %f", RCuts[i]), SingleFitResults[i].X0, 0, 500, "GeV"));
      SigmaL.push_back(new RooRealVar(Form("SigmaL_%d", i),
         Form("left-hand side gaussian width, R > %f", RCuts[i]), SingleFitResults[i].SigmaL, 0, 500, "GeV"));
      SigmaR.push_back(new RooRealVar(Form("SigmaR_%d", i),
         Form("right-hand side gaussian width, R > %f", RCuts[i]), SingleFitResults[i].SigmaR, 0, 500, "GeV"));
      S.push_back(new RooFormulaVar(Form("S_%d", i),
         Form("exponent of the tail, R > %f", RCuts[i]),
         Form("@0 + %f * @1", RCuts[i] * RCuts[i]), RooArgList(ParameterA, ParameterB)));
      Yields.push_back(new RooRealVar(Form("Yield_%d", i),
         Form("Yield with R above %f", RCuts[i]), GuessYield));
      NegativeYields.push_back(new RooFormulaVar(Form("NYield_%d", i),
         "Negative yield", "-1 * @0", RooArgList(*Yields[i])));

      Models.push_back(new RooTwoSideGaussianWithAnExponentialTail(Form("Model_%d", i),
         Form("Model for R > %f", RCuts[i]), MR, *X0[i], *SigmaL[i], *SigmaR[i], *S[i]));
   }

   for(int i = 0; i < (int)RCuts.size() - 1; i++)
   {
      NormalizedYields.push_back(new RooFormulaVar(Form("NormalizedYield_%d", i),
         "Yield", "@0 / (@0 - @1)", RooArgList(*Yields[i], *Yields[i+1])));
      NormalizedNegativeYields.push_back(new RooFormulaVar(Form("NormalizedNegativeYield_%d", i),
         "Yield", "-@1 / (@0 - @1)", RooArgList(*Yields[i], *Yields[i+1])));
      
      // NormalizedYields.push_back(new RooFormulaVar(Form("NormalizedYield_%d", i),
      //    "Yield", "@0", RooArgList(*Yields[i], *Yields[i+1])));
      // NormalizedNegativeYields.push_back(new RooFormulaVar(Form("NormalizedNegativeYield_%d", i),
      //    "Yield", "-@1", RooArgList(*Yields[i], *Yields[i+1])));
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
      
      // if(i == RCuts.size() - 1)
      //    TopLevelYields.push_back(Yields[i]);
      // else
      //    TopLevelYields.push_back(new RooRealVar(Form("DummyYield_%d", i), "Dummy variable", 1));

      ModelList.add(*TopLevelModels[i]);
      YieldList.add(*TopLevelYields[i]);
   }

   RooAddPdf FinalModel("Final model", "Final model!", ModelList, YieldList);

   FinalModel.printMultiline(cout, 1);

   RooFitResult *FitResult = FinalModel.fitTo(Dataset, Save(true));

   PsFile.AddTextPage("Simultaneous fit!");

   RooPlot *ParameterPlot = MR.frame(Bins(50), Name("FitParameters"), Title("Fit parameters"));
   FinalModel.paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.4, 0.9));
   PsFile.AddPlot(ParameterPlot, "", false);

   RooPlot *FinalResultPlot = MR.frame(Bins(50), Name("FitResults"), Title("MR"));
   Dataset.plotOn(FinalResultPlot, MarkerSize(0.9));
   FinalModel.plotOn(FinalResultPlot, LineColor(kBlue));
   PsFile.AddPlot(FinalResultPlot, "", true);

   RooPlot *FinalResultPlot2 = MR.frame(Bins(50), Name("FitResults2"), Title("MR"));
   Dataset.plotOn(FinalResultPlot2, MarkerSize(0.9));
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      RooArgList ComponentsToAdd;
      for(int j = i; j < (int)RCuts.size(); j++)
         ComponentsToAdd.add(*TopLevelModels[j]);
      FinalModel.plotOn(FinalResultPlot2, LineColor(kBlue), Components(ComponentsToAdd));
   }
   for(int i = 1; i < (int)RCuts.size(); i++)
      Dataset.reduce(Cut(Form("R > %f", RCuts[i])))->plotOn(FinalResultPlot2, MarkerSize(0.9));
   PsFile.AddPlot(FinalResultPlot2, "", true);
   
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      RooArgList ComponentsToAdd;
      for(int j = i; j < (int)RCuts.size(); j++)
         ComponentsToAdd.add(*TopLevelModels[j]);

      RooPlot *FinalResultPlotN = MR.frame(Bins(50), Name("FitResultsN"),
         Title(Form("i = %d", i)), AutoRange(Dataset));
      Dataset.reduce(Cut(Form("R > %f", RCuts[i])))->plotOn(FinalResultPlotN, MarkerSize(0.9));
      FinalModel.plotOn(FinalResultPlot2, LineColor(kBlue), Components(ComponentsToAdd));
      PsFile.AddPlot(FinalResultPlotN, "", true);
   }

   vector<string> FinalResultExplanation;
   stringstream FitParameterAStream;
   FitParameterAStream << "Parameter A from simultaneous fit = "
      << ParameterA.getVal() << " +- " << ParameterA.getError();
   FinalResultExplanation.push_back(FitParameterAStream.str());
   stringstream FitParameterBStream;
   FitParameterBStream << "Parameter B from simultaneous fit = "
      << ParameterB.getVal() << " +- " << ParameterB.getError();
   FinalResultExplanation.push_back(FitParameterBStream.str());
   PsFile.AddTextPage(FinalResultExplanation);
   
   FinalModel.printMultiline(cout, 1);

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

      delete Models[i];
      delete Yields[i];
      delete S[i];
      delete SigmaR[i];
      delete SigmaL[i];
      delete X0[i];
   }

   TopLevelModels.clear();
   ModelBeforeConstraint.clear();
   Constraint.clear();
   TopLevelYields.clear();

   NormalizedYields.clear();
   NormalizedNegativeYields.clear();

   Models.clear();
   Yields.clear();
   S.clear();
   SigmaR.clear();
   SigmaL.clear();
   X0.clear();
}





