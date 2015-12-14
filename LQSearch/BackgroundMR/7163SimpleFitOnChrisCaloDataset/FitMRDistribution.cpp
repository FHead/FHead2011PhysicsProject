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
using namespace RooFit;

#include "SetStyle.h"
#include "PlotHelper2.h"
#include "DataHelper.h"

struct SingleFitResult;
int main(int argc, char *argv[]);
SingleFitResult FitWithRCut(PsFileHelper &PsFile, string FileName, double RCut, double MRLowerBound, double MRUpperBound,
   int BoxNumber, bool OneComponent, int BTagRequirement);
void FitWithRCut(PsFileHelper &PsFile, string FileName, vector<double> RCuts, DataHelper &DHFile, string State,
   double MRLowerBound = 250, double MRUpperBound = 1400, int BoxNumber = 4, bool OneComponent = false,
   int BTagRequirement = -1);

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

   DataHelper DHFile("Results.dh");

   PsFileHelper PsFile("FitResult.ps");

   vector<double> CutsToTry;
   CutsToTry.push_back(0.15);
   CutsToTry.push_back(0.20);
   CutsToTry.push_back(0.25);
   CutsToTry.push_back(0.30);
   // FitWithRCut(PsFile, "Samples/ELE_noTRIG_Prompt.root", CutsToTry, DHFile, "E", 200, 800, 4, false, -1);
   
   CutsToTry.clear();
   CutsToTry.push_back(0.15);
   CutsToTry.push_back(0.20);
   CutsToTry.push_back(0.25);
   CutsToTry.push_back(0.30);
   // FitWithRCut(PsFile, "Samples/MU_noTRIG_Prompt.root", CutsToTry, DHFile, "Mu", 200, 800, 3, true, -1);
   // FitWithRCut(PsFile, "Samples/MU_noTRIG_Prompt.root", CutsToTry, DHFile, "MuNoBTag", 200, 800, 3, true, 0);
   // FitWithRCut(PsFile, "Samples/MU_noTRIG_Prompt.root", CutsToTry, DHFile, "MuHigh", 400, 800, 3, true, -1);
   // FitWithRCut(PsFile, "Samples/MU_noTRIG_Prompt.root", CutsToTry, DHFile, "MuHighNoBTag", 400, 800, 3, true, 0);
   
   CutsToTry.clear();
   CutsToTry.push_back(0.15);
   CutsToTry.push_back(0.20);
   CutsToTry.push_back(0.25);
   CutsToTry.push_back(0.30);
   // FitWithRCut(PsFile, "Samples/MU-MU_noTRIG_Total.root", CutsToTry, DHFile, "DoubleMu", 200, 800, 1, true, -1);
   // FitWithRCut(PsFile, "Samples/MU-MU_noTRIG_Total.root", CutsToTry, DHFile, "DoubleMuNoBTag", 200, 800, 1, true, 0);
   
   CutsToTry.clear();
   CutsToTry.push_back(0.20 * 0.20);
   CutsToTry.push_back(0.25 * 0.25);
   CutsToTry.push_back(0.30 * 0.30);
   CutsToTry.push_back(0.35 * 0.35);
   FitWithRCut(PsFile, "Samples/ELE-ELE_noTRIG_Total.root", CutsToTry, DHFile, "DoubleE", 200, 800, 2, false, -1);
   FitWithRCut(PsFile, "Samples/ELE-ELE_noTRIG_Total.root", CutsToTry, DHFile, "DoubleENoBTag", 200, 800, 2, false, 0);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   DHFile.SaveToFile("Results.dh");
}

SingleFitResult FitWithRCut(PsFileHelper &PsFile, string FileName, double RCut, double MRLowerBound, double MRUpperBound,
   int BoxNumber, bool OneComponent, int BTagRequirement)
{
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("EVENTS");
   if(Tree == NULL)
      return SingleFitResult();

   RooRealVar MR("MR", "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R("RSQ", "Chris' another kinematic variable", RCut, 200);
   RooRealVar BOX_NUM("BOX_NUM", "Box number", -100, 100);
   RooRealVar BTAG_NUM("BTAG_NUM", "BTag number", -100, 100);
   RooArgSet TreeVarSet(MR, R, BOX_NUM, BTAG_NUM);

   MR.setRange("FitRange", MRLowerBound, MRUpperBound);
   R.setRange("FitRange", RCut, 200);

   string BTagString = "";
   if(BTagRequirement < 0)
      BTagString = "BTAG_NUM > -100 && BTAG_NUM < 100";
   else if(BTagRequirement == 0)
      BTagString = "BTAG_NUM == 0";
   else if(BTagRequirement == 1)
      BTagString = "BTAG_NUM == 1";
   else if(BTagRequirement == 2)
      BTagString = "BTAG_NUM == 2";

   RooDataSet FullDataset("Dataset", "MR Dataset", Tree, TreeVarSet);
   RooDataSet *Dataset = (RooDataSet *)FullDataset.reduce(Form("BOX_NUM == %d && RSQ > %f && %s", BoxNumber, RCut,
      BTagString.c_str()));

   cout << "Number of entries in the dataset = " << Dataset->sumEntries() << endl;

   RooRealVar S1("S1", "first exponent of the tail", -0.02, -1.0, 0.0);
   RooExponential Component1("Component1", "First component", MR, S1);
   
   RooRealVar S2("S2", "second exponent of the tail", -0.008, -1.0, 0.0);
   RooExponential Component2("Component2", "Second component", MR, S2);

   RooRealVar Fraction("Fraction", "Fraction of the second component at zero", 0.003, 0, 1);
   RooAddPdf *Model = new RooAddPdf("Model", "Model", Component1, Component2, Fraction);

   // RooFitResult *FitResult = Model->fitTo(Dataset, Save(true));
   if(OneComponent == true)
      Component1.fitTo(*Dataset, Range("FitRange"));
   else
      Model->fitTo(*Dataset, Range("FitRange"));

   stringstream Subtitle;
   Subtitle << "Fitting with R cut = " << RCut;
   PsFile.AddTextPage(Subtitle.str());

   RooPlot *ParameterPlot = MR.frame(Bins(50), Name("FitParameters"), Title("Fit parameters"));
   Model->paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.4, 0.9));
   PsFile.AddPlot(ParameterPlot, "", false);

   RooPlot *FinalResultPlot = MR.frame(Bins(50), Name("FitResults"), Title("MR"), AutoRange(*Dataset));
   Dataset->plotOn(FinalResultPlot, MarkerSize(0.9));
   if(OneComponent == true)
      Component1.plotOn(FinalResultPlot, LineColor(kBlue));
   else
   {
      Model->plotOn(FinalResultPlot, LineColor(kBlue));
      Model->plotOn(FinalResultPlot, LineColor(kGreen), Components(Component1));
      Model->plotOn(FinalResultPlot, LineColor(kRed), Components(Component2));
   }
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

void FitWithRCut(PsFileHelper &PsFile, string FileName, vector<double> RCuts, DataHelper &DHFile, string State,
   double MRLowerBound, double MRUpperBound, int BoxNumber, bool OneComponent, int BTagRequirement)
{
   if(RCuts.size() == 0)
      return;
   if(RCuts.size() == 1)
   {
      cout << "If you want to fit with just one R-cut, use the easy version!" << endl;
      return;
   }

   sort(RCuts.begin(), RCuts.end());

   vector<SingleFitResult> SingleFitResults(RCuts.size());

   for(int i = 0; i < (int)RCuts.size(); i++)
      SingleFitResults[i] = FitWithRCut(PsFile, FileName, RCuts[i], MRLowerBound, MRUpperBound, BoxNumber, OneComponent,
         BTagRequirement);

   PsFile.AddTextPage("Putting everything together");

   TGraphErrors SingleCentralValues1;
   SingleCentralValues1.SetNameTitle("SingleCentralValues1", "Central values from single fits, component 1");
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      SingleCentralValues1.SetPoint(i, RCuts[i], SingleFitResults[i].S1);
      SingleCentralValues1.SetPointError(i, 0, SingleFitResults[i].S1Error);
   }

   TGraphErrors SingleCentralValues2;
   SingleCentralValues2.SetNameTitle("SingleCentralValues2", "Central values from single fits, component 2");
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      SingleCentralValues2.SetPoint(i, RCuts[i], SingleFitResults[i].S2);
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
   TTree *Tree = (TTree *)F.Get("EVENTS");
   if(Tree == NULL)
      return;

   RooRealVar MR("MR", "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R("RSQ", "Chris' another kinematic variable", -200, 200);
   RooRealVar BOX_NUM("BOX_NUM", "Box number", -100, 100);
   RooRealVar BTAG_NUM("BTAG_NUM", "BTag number", -100, 100);
   RooArgSet TreeVarSet(MR, R, BOX_NUM, BTAG_NUM);

   string BTagString = "";
   if(BTagRequirement < 0)
      BTagString = "BTAG_NUM > -100 && BTAG_NUM < 100";
   else if(BTagRequirement == 0)
      BTagString = "BTAG_NUM == 0";
   else if(BTagRequirement == 1)
      BTagString = "BTAG_NUM == 1";
   else if(BTagRequirement == 2)
      BTagString = "BTAG_NUM == 2";

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet,
      Form("RSQ > %f && BOX_NUM == %d && MR > %f && MR < %f && %s",
      RCuts[0], BoxNumber, MRLowerBound, MRUpperBound, BTagString.c_str()));

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
         GuessYield = Dataset.reduce(Cut(Form("RSQ > %f && RSQ <= %f", RCuts[i], RCuts[i+1])))->sumEntries();
      else
         GuessYield = Dataset.reduce(Cut(Form("RSQ > %f", RCuts[i])))->sumEntries();

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

   RooAddPdf FinalModel("Final model", "Final model!", ModelList, YieldList);

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
      Dataset.reduce(Cut(Form("RSQ > %f", RCuts[i])))->plotOn(FinalResultPlot2, MarkerSize(0.9), MarkerColor(i + 1));

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

   // Write result to DHFile
   DHFile[State]["SingleA1"] = InitialParameterValues1.GetParameter(0);
   DHFile[State]["SingleA1Error"] = InitialParameterValues1.GetParError(0);
   DHFile[State]["SingleB1"] = InitialParameterValues1.GetParameter(1);
   DHFile[State]["SingleB1Error"] = InitialParameterValues1.GetParError(1);
   DHFile[State]["SingleA2"] = InitialParameterValues2.GetParameter(0);
   DHFile[State]["SingleA2Error"] = InitialParameterValues2.GetParError(0);
   DHFile[State]["SingleB2"] = InitialParameterValues2.GetParameter(1);
   DHFile[State]["SingleB2Error"] = InitialParameterValues2.GetParError(1);
   DHFile[State]["SingleF"] = InitialFraction.GetParameter(0);
   DHFile[State]["SingleFError"] = InitialFraction.GetParError(0);
   DHFile[State]["SimultaneousA1"] = ParameterA1.getVal();
   DHFile[State]["SimultaneousA1Error"] = ParameterA1.getError();
   DHFile[State]["SimultaneousB1"] = ParameterB1.getVal();
   DHFile[State]["SimultaneousB1Error"] = ParameterB1.getError();
   DHFile[State]["SimultaneousA2"] = ParameterA2.getVal();
   DHFile[State]["SimultaneousA2Error"] = ParameterA2.getError();
   DHFile[State]["SimultaneousB2"] = ParameterB2.getVal();
   DHFile[State]["SimultaneousB2Error"] = ParameterB2.getError();
   // DHFile[State]["SimultaneousF"] = Fraction.getVal();
   // DHFile[State]["SimultaneousFError"] = Fraction.getError();
   DHFile[State]["SimultaneousCorrelation1"] = FitResult->correlation("ParameterA1", "ParameterB1");
   DHFile[State]["SimultaneousCorrelation2"] = FitResult->correlation("ParameterA2", "ParameterB2");
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      stringstream NumberToString;
      NumberToString << i + 1;
      DHFile[State]["SingleBin" + NumberToString.str() + "S1"] = SingleFitResults[i].S1;
      DHFile[State]["SingleBin" + NumberToString.str() + "S1Error"] = SingleFitResults[i].S1Error;
      DHFile[State]["SingleBin" + NumberToString.str() + "S2"] = SingleFitResults[i].S2;
      DHFile[State]["SingleBin" + NumberToString.str() + "S2Error"] = SingleFitResults[i].S2Error;
      DHFile[State]["SingleBin" + NumberToString.str() + "F"] = SingleFitResults[i].F;
      DHFile[State]["SingleBin" + NumberToString.str() + "FError"] = SingleFitResults[i].FError;
   }
   
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

      if(OneComponent == false)
         if(Models[i] != NULL)
            delete Models[i];

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
}










