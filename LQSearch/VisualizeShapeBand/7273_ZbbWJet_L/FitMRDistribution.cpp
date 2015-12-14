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
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TH2D.h"
#include "TH1D.h"

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
#include "SetStyle.h"
#include "DataHelper.h"

struct SingleFitResult;
int main(int argc, char *argv[]);
SingleFitResult FitWithRCut(PsFileHelper &PsFile, string FileName, double RCut);
RooFitResult *FitWithRCut(PsFileHelper &PsFile, string FileName, vector<double> RCuts);
void PlotBands(PsFileHelper &PsFile, double Min, double Maxt, RooFitResult *Result,
   vector<RooRealVar *> FloatParameters, vector<string> FloatNames,
   RooAbsPdf &PDF, RooRealVar &MR, RooRealVar &R,
   double WeightedYields, vector<double> RCuts,
   string Tag, double SigmaA = 0, double SigmaB = 0, double Correlation = 0);

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

   vector<double> CutsToTry;
   CutsToTry.push_back(sqrt(0.07));
   CutsToTry.push_back(sqrt(0.11));
   CutsToTry.push_back(sqrt(0.14));
   CutsToTry.push_back(sqrt(0.20));
   CutsToTry.push_back(sqrt(0.25));
   CutsToTry.push_back(sqrt(0.30));
   CutsToTry.push_back(sqrt(0.35));
   CutsToTry.push_back(sqrt(0.38));
   CutsToTry.push_back(sqrt(0.42));
   
   PsFileHelper PsFile("WJetFitResultExportBand.ps");
   PsFile.AddTextPage("Fit W+Jet (actually Z+bb) in the signal selection");

   RooFitResult *Result = FitWithRCut(PsFile, "ZbbPlots.root", CutsToTry);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();
}

SingleFitResult FitWithRCut(PsFileHelper &PsFile, string FileName, double RCut)
{
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return SingleFitResult();

   double MRLowerBound = 400;
   double MRUpperBound = 3500;

   string MRString = "MR";
   string RString = "R";

   RooRealVar MR(MRString.c_str(), "MR", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R(RString.c_str(), "R", -200, 200);
   RooArgSet TreeVarSet(MR, R);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, Form("%s > %f", RString.c_str(), RCut));

   RooRealVar S1("S1", "first exponent of the tail", -0.01, -1.0, 0.0);
   RooExponential Component1("Component1", "First component", MR, S1);
   
   RooRealVar S2("S2", "second exponent of the tail", -0.003, -1.0, 0.0);
   RooExponential Component2("Component2", "Second component", MR, S2);

   RooRealVar Fraction("Fraction", "Fraction of the second component at zero", 0.7, 0, 1);
   RooAddPdf *Model = new RooAddPdf("Model", "Model", Component1, Component2, Fraction);

   RooFitResult *FitResult = Model->fitTo(Dataset, Save(true));
   // Component1.fitTo(Dataset);

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

   if(result.S2 > result.S1)
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

   double MRLowerBound = 400;
   double MRUpperBound = 3500;

   string MRString = "MR";
   string RString = "R";

   RooRealVar MR(MRString.c_str(), "MR", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R(RString.c_str(), "R", 0, 1.5);
   RooRealVar Factor("Factor", "Factor", 0, 10000);
   RooArgSet TreeVarSet(MR, R, Factor);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, Form("%s > %f", RString.c_str(), RCuts[0]), "");

   if(ParameterA2Value > ParameterA1Value)
      swap(ParameterA1Value, ParameterA2Value);
   if(ParameterB2Value > ParameterB1Value)
      swap(ParameterB1Value, ParameterB2Value);

   RooRealVar ParameterA1("ParameterA1", "s1 = \"a1\" + b1 R^2", ParameterA1Value, -0.1, 0.1);
   RooRealVar ParameterB1("ParameterB1", "s1 = a1 + \"b1\" R^2", 0.013, -1, 1);
   RooRealVar ParameterA2("ParameterA2", "s2 = \"a2\" + b2 R^2", ParameterA2Value, -0.1, 0.1);
   RooRealVar ParameterB2("ParameterB2", "s2 = a2 + \"b2\" R^2", 0.009, -1, 1);

   vector<RooRealVar *> FloatParameters;
   vector<string> FloatNames;

   FloatParameters.push_back(&ParameterA1);
   FloatParameters.push_back(&ParameterB1);
   FloatParameters.push_back(&ParameterA2);
   FloatParameters.push_back(&ParameterB2);
   FloatNames.push_back("ParameterA1");
   FloatNames.push_back("ParameterB1");
   FloatNames.push_back("ParameterA2");
   FloatNames.push_back("ParameterB2");

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
      
      FloatParameters.push_back(SingleBinYields[i]);
      FloatNames.push_back(Form("SingleBinYield_%d", i));
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
      // Fraction.push_back(new RooRealVar(Form("Fraction_%d", i), Form("Fraction_%d", i), 0.0));

      FloatParameters.push_back(Fraction[i]);
      FloatNames.push_back(Form("Fraction_%d", i));

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

   RooAddPdf FinalModel("FinalModel", "Final model!", ModelList, YieldList);

   RooFitResult *FitResult = FinalModel.fitTo(Dataset, Save(true), PrintEvalErrors(-1), NumCPU(3));
   
   DataHelper DHFile("FitResult.dh");

   DHFile["CentralValue"]["ParameterA1"] = ParameterA1.getVal();
   DHFile["CentralValue"]["ParameterA2"] = ParameterA2.getVal();
   DHFile["CentralValue"]["ParameterB1"] = ParameterB1.getVal();
   DHFile["CentralValue"]["ParameterB2"] = ParameterB2.getVal();
   for(int i = 0; i < (int)RCuts.size(); i++)
      DHFile["CentralValue"][SingleBinYields[i]->GetName()] = SingleBinYields[i]->getVal();
   for(int i = 0; i < (int)RCuts.size(); i++)
      DHFile["CentralValue"][Fraction[i]->GetName()] = Fraction[i]->getVal();
   for(int i = 0; i < (int)RCuts.size(); i++)
      DHFile["CentralValue"][Form("R2Cut%d", i)] = RCuts[i] * RCuts[i];

   DHFile.SaveToFile("FitResult.dh");

   PsFile.AddTextPage("Simultaneous fit!");

   // Total model vs. total data
   RooPlot *FinalResultPlot = MR.frame(Bins(50), Name("FitResults"), Title("MR, Simultaneous fit, total model"));
   Dataset.plotOn(FinalResultPlot, MarkerSize(0.9));
   FinalModel.plotOn(FinalResultPlot, LineColor(kBlue));
   // FinalResultPlot->SetMinimum(0.0001);
   FinalResultPlot->SetMinimum(0.1);
   PsFile.AddPlot(FinalResultPlot, "", true);

   TCanvas FinalResultCanvas1Square("FinalResultcanvas1Square", "", 1024, 1024);
   FinalResultPlot->Draw();
   FinalResultCanvas1Square.SetLogy();
   FinalResultCanvas1Square.SaveAs("FinalResultCanvas1Square.png");
   FinalResultCanvas1Square.SaveAs("FinalResultCanvas1Square.C");
   FinalResultCanvas1Square.SaveAs("FinalResultCanvas1Square.eps");
   FinalResultCanvas1Square.SaveAs("FinalResultCanvas1Square.pdf");

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

   // FinalResultPlot2->SetMinimum(0.0001);
   FinalResultPlot2->SetMinimum(0.1);
   FinalResultPlot2->Draw();

   vector<TH1D *> DummyHistograms;   
   TLegend legend(0.6, 0.9, 0.9, 0.7);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
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

   TCanvas FinalResultCanvas2Square("FinalResultcanvas2Square", "", 1024, 1024);
   FinalResultPlot2->Draw();
   FinalResultCanvas2Square.SetLogy();
   legend.Draw();
   FinalResultCanvas2Square.SaveAs("FinalResultCanvas2Square.png");
   FinalResultCanvas2Square.SaveAs("FinalResultCanvas2Square.C");
   FinalResultCanvas2Square.SaveAs("FinalResultCanvas2Square.eps");
   FinalResultCanvas2Square.SaveAs("FinalResultCanvas2Square.pdf");

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

   TFile BandFile("Bands.root", "recreate");

   PsFile.AddTextPage("Now, try to get ALL the bands");

   double TotalSingleBinYield = 0;
   double RestrictedSingleBinYield = 0;
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      TotalSingleBinYield = TotalSingleBinYield + SingleBinYields[i]->getVal();
      if(RCuts[i] * RCuts[i] > 0.199)
         RestrictedSingleBinYield = RestrictedSingleBinYield + SingleBinYields[i]->getVal();
   }

   cout << "Total single bin yield = " << TotalSingleBinYield << endl;
   cout << "Restricted single bin yield = " << RestrictedSingleBinYield << endl;

   // double WJetRestrictedYield = 466.044;   // electron, R2 > 0.20, MR > 400
   // double WJetRestrictedYield = 378.322;   // electron, R2 > 0.20, MR > 400
   // double WJetRestrictedYield = 590.047 + 1104.532;   // Had+1L, R2 > 0.20, MR > 400
   // double WJetRestrictedYield = 414.890 + 776.648;   // Had+1L, R2 > 0.20, MR > 400
   
   double WJetRestrictedYield = 1818.072 + 842.937;   // Had+1L, R2 > 0.20, MR > 400

   double WeightedYields = TotalSingleBinYield / RestrictedSingleBinYield * WJetRestrictedYield;

   PsFile.AddTextPage("Fit-band");
   PlotBands(PsFile, MRLowerBound, MRUpperBound, FitResult, FloatParameters, FloatNames,
      FinalModel, MR, R, WeightedYields, RCuts, "Fit");
   
   /*
   PsFile.AddTextPage("Smear A only");
   PlotBands(PsFile, MRLowerBound, MRUpperBound, FitResult, FloatParameters, FloatNames,
      FinalModel, MR, R, WeightedYields, RCuts, "SmearA", 0.1, 0, 0);
   */
   
   PsFile.AddTextPage("Smear A and B with full correlation");
   PlotBands(PsFile, MRLowerBound, MRUpperBound, FitResult, FloatParameters, FloatNames,
      FinalModel, MR, R, WeightedYields, RCuts, "FullCorrelation", 0.1, 0.4, 1);
   
   /*
   PsFile.AddTextPage("Smear A and B with no correlation");
   PlotBands(PsFile, MRLowerBound, MRUpperBound, FitResult, FloatParameters, FloatNames,
      FinalModel, MR, R, WeightedYields, RCuts, "NoCorrelation", 0.1, 0.4, 0);
   */
   
   PsFile.AddTextPage("Smear A and B");
   PlotBands(PsFile, MRLowerBound, MRUpperBound, FitResult, FloatParameters, FloatNames,
      FinalModel, MR, R, WeightedYields, RCuts, "SmearAB", 0.1, 0.4, -0.85);

   BandFile.Close();

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

void PlotBands(PsFileHelper &PsFile, double Min, double Max, RooFitResult *Result,
   vector<RooRealVar *> FloatParameters, vector<string> FloatNames,
   RooAbsPdf &PDF, RooRealVar &MR, RooRealVar &R,
   double WeightedYields, vector<double> RCuts,
   string Tag, double SigmaA, double SigmaB, double Correlation)
{
   cout << "Start to plot bands with tag \"" << Tag << "\"" << endl;

   const int BinCount = 100;
   
   int Tries = 1000;

   vector<vector<double> > Bins[10];
   for(int i = 0; i < (int)RCuts.size(); i++)
      Bins[i].resize(BinCount);

   for(int i = 0; i < (int)RCuts.size(); i++)
      RCuts[i] = RCuts[i] * RCuts[i];

   double ABound = SigmaA * 5;
   double BBound = SigmaB * 5;
   if(ABound == 0)   ABound = 1;
   if(BBound == 0)   BBound = 1;

   TH2D HChangeAB(Form("HChangeAB_%s", Tag.c_str()), Form("Percentage change in A and B (%s);A;B", Tag.c_str()),
      50, -ABound, ABound, 50, -BBound, BBound);
   TH1D HChangeA(Form("HChangeA_%s", Tag.c_str()), "Percentage change in A", 50, -ABound, ABound);
   TH1D HChangeB(Form("HChangeB_%s", Tag.c_str()), "Percentage change in B", 50, -BBound, BBound);

   for(int i = 0; i < Tries; i++)
   {
      if((i + 1) % 100 == 0)
         cout << "Starting toy " << i + 1 << "...." << endl;

      const RooArgList Parameters = Result->randomizePars();

      double ChangeA1 = 0;
      double ChangeB1 = 0;
      double ChangeC1 = 0;
      double ChangeA2 = 0;
      double ChangeB2 = 0;
      double ChangeC2 = 0;

      if(SigmaA > 0)
      {
         ChangeA1 = DrawGaussian(SigmaA);
         ChangeC1 = DrawGaussian(sqrt(1 - Correlation * Correlation) * SigmaB);
         ChangeB1 = ChangeA1 * Correlation * SigmaB / SigmaA + ChangeC1;
         ChangeA2 = DrawGaussian(SigmaA);
         ChangeC2 = DrawGaussian(sqrt(1 - Correlation * Correlation) * SigmaB);
         ChangeB2 = ChangeA2 * Correlation * SigmaB / SigmaA + ChangeC2;

         HChangeAB.Fill(ChangeA1, ChangeB1);
         HChangeA.Fill(ChangeA1);
         HChangeB.Fill(ChangeB1);
      }

      double A1Value = ((RooAbsReal *)Parameters.find("ParameterA1"))->getVal() * (1 + ChangeA1);
      double B1Value = ((RooAbsReal *)Parameters.find("ParameterB1"))->getVal() * (1 + ChangeB1);
      // double A2Value = 0;
      // double B2Value = 0;
      double A2Value = ((RooAbsReal *)Parameters.find("ParameterA2"))->getVal() * (1 + ChangeA2);
      double B2Value = ((RooAbsReal *)Parameters.find("ParameterB2"))->getVal() * (1 + ChangeB2);

      if(A1Value + B1Value * RCuts[RCuts.size()-1] < 0 || A2Value + B2Value * RCuts[RCuts.size()-1] < 0)
      {
         i = i - 1;
         continue;
      }

      for(int j = 0; j < (int)FloatParameters.size(); j++)
      {
         if(FloatParameters[j] == NULL || Parameters.find(FloatNames[j].c_str()) == NULL)
            cout << FloatNames[j] << " not found!" << endl;
         else if(FloatNames[j] == "ParameterA1")
            FloatParameters[j]->setVal(A1Value);
         else if(FloatNames[j] == "ParameterB1")
            FloatParameters[j]->setVal(B1Value);
         else if(FloatNames[j] == "ParameterA2")
            FloatParameters[j]->setVal(A2Value);
         else if(FloatNames[j] == "ParameterB2")
            FloatParameters[j]->setVal(B2Value);
         else
            FloatParameters[j]->setVal(((RooAbsReal *)Parameters.find(FloatNames[j].c_str()))->getVal());
      }

      RooDataSet *ToyDataSet = (RooDataSet *)PDF.generate(RooArgSet(R, MR), (long long)DrawPoisson(WeightedYields));
      ToyDataSet->SetName(Form("ToyDataSet_%s_%d", Tag.c_str(), i + 1));

      /*
      for(int j = 0; j < (int)RCuts.size(); j++)
      {
         for(int k = 0; k < BinCount; k++)
         {
            double MRMin = k * (Max - Min) / BinCount + Min;
            double MRMax = (k + 1) * (Max - Min) / BinCount + Min;
            Bins[j][k].push_back(ToyDataSet->sumEntries(Form("MR >= %f && MR < %f && R * R > %f",
               MRMin, MRMax, RCuts[j])));
         }
      }
      */

      ToyDataSet->Write();

      delete ToyDataSet;
   }

   /*
   for(int i = 0; i < (int)RCuts.size(); i++)
      for(int j = 0; j < BinCount; j++)
         sort(Bins[i][j].begin(), Bins[i][j].end());

   TGraphAsymmErrors OneSigmaBand[10], TwoSigmaBand[10];
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      OneSigmaBand[i].SetNameTitle(Form("OneSigma_%s_R%d", Tag.c_str(), i + 1),
         Form("One sigma band (%s), R%d", Tag.c_str(), i + 1));
      TwoSigmaBand[i].SetNameTitle(Form("TwoSigma_%s_R%d", Tag.c_str(), i + 1),
         Form("Two sigma band (%s), R%d", Tag.c_str(), i + 1));
   }

   int Center = (int)(Tries * 0.500);
   int UpOneSigma = (int)(Tries * 0.683);
   int DownOneSigma = (int)(Tries * 0.317);
   int UpTwoSigma = (int)(Tries * 0.950);
   int DownTwoSigma = (int)(Tries * 0.050);
  
   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      for(int j = 0; j < BinCount; j++)
      {
         double MRValue = Min + (j + 0.5) * (Max - Min) / BinCount;

         OneSigmaBand[i].SetPoint(j, MRValue, Bins[i][j][Center]);
         OneSigmaBand[i].SetPointError(j, 0, 0,
            Bins[i][j][UpOneSigma] - Bins[i][j][Center], Bins[i][j][Center] - Bins[i][j][DownOneSigma]);
         TwoSigmaBand[i].SetPoint(j, MRValue, Bins[i][j][Center]);
         TwoSigmaBand[i].SetPointError(j, 0, 0,
            Bins[i][j][UpTwoSigma] - Bins[i][j][Center], Bins[i][j][Center] - Bins[i][j][DownTwoSigma]);
      }
   }

   for(int i = 0; i < (int)RCuts.size(); i++)
   {
      OneSigmaBand[i].SetMarkerStyle(1);
      PsFile.AddPlot(OneSigmaBand[i], "ape", false);

      TwoSigmaBand[i].SetMarkerStyle(1);
      PsFile.AddPlot(TwoSigmaBand[i], "ape", false);

      OneSigmaBand[i].SetFillColor(kBlue);
      TwoSigmaBand[i].SetFillColor(kGreen - 3);
   
      TH1D HFrame("HFrame", ";MR;Count", 100, 300, 1500);
      HFrame.SetMaximum(3000);
      HFrame.SetMinimum(0.3);
      HFrame.SetStats(0);

      TCanvas SigmaBandCanvas;
      HFrame.Draw();
      TwoSigmaBand[i].Draw("3");
      OneSigmaBand[i].Draw("3");
      SigmaBandCanvas.SetLogy();
      PsFile.AddCanvas(SigmaBandCanvas);
   
      OneSigmaBand[i].Write();
      TwoSigmaBand[i].Write();
   }
   */

   PsFile.AddPlot(HChangeA, "", true);
   PsFile.AddPlot(HChangeB, "", true);
   PsFile.AddPlot(HChangeAB, "colz", false);

   HChangeA.Write();
   HChangeB.Write();
   HChangeAB.Write();
}










