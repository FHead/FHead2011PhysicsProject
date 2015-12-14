#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooCruijff.h"
#include "RooArgSet.h"
#include "RooProdPdf.h"
#include "RooSameAs.h"
#include "RooAtLeast.h"
#include "RooFormulaVar.h"
#include "RooExponential.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
using namespace RooFit;

#include "PlotHelper.h"

struct FitResult;
void SimultaneousFit_FixRelation(string RootFile = "Samples/DataAll.root", int LastJetBin = 4,
   string JetFlavor = "PF", double AlphaLValue = 0.423);
FitResult SimultaneousFit(string RootFile = "Samples/DataAll.root", int LastJetBin = 4,
   string JetFlavor = "PF", double AlphaLValue = 0.423, string JetAppendix = "");
double GetSignalInclusiveCount(int jet, double SignalInclusiveYield, double Alpha, double Beta);
double GetSignalInclusiveError(int jet, double SignalInclusiveYield, double Alpha, double Beta,
   double SignalInclusiveYieldError, double AlphaError, double BetaError);
string GetSignalYieldString(int jet, bool Inclusive = false);

struct FitResult
{
   double Alpha[2];
   double Beta[2];
   double SignalInclusiveCount[2];
};

void SimultaneousFit_FixRelation(string RootFile, int LastJetBin, string JetFlavor, double AlphaLValue)
{
   FitResult Normal = SimultaneousFit(RootFile, LastJetBin, JetFlavor, AlphaLValue, "");
   FitResult LowThreshold = SimultaneousFit(RootFile, LastJetBin, JetFlavor, AlphaLValue, "LowThreshold");
   FitResult HighThreshold = SimultaneousFit(RootFile, LastJetBin, JetFlavor, AlphaLValue, "HighThreshold");
   FitResult LowEtaThreshold = SimultaneousFit(RootFile, LastJetBin, JetFlavor, AlphaLValue, "LowEtaThreshold");
   FitResult HighEtaThreshold = SimultaneousFit(RootFile, LastJetBin, JetFlavor, AlphaLValue, "HighEtaThreshold");

   PsFileHelper PsFile("JES_" + JetFlavor + ".ps");
   PsFile.AddTextPage("JES, " + JetFlavor);

   TGraphAsymmErrors EtaGraph;
   TGraphAsymmErrors ScaleGraph;

   EtaGraph.SetNameTitle("EtaGraph", "Eta-dependent scale");
   ScaleGraph.SetNameTitle("ScaleGraph", "absolute scale");

   EtaGraph.

   for(int i = 1; i <= 4; i++)
   {
      double CentralValue = GetSignalInclusiveCount(i, Normal.SignalInclusiveCount[0],
         Normal.Alpha[0], Normal.Beta[0]);
      double LowValue = GetSignalInclusiveCount(i, LowThreshold.SignalInclusiveCount[0],
         LowThreshold.Alpha[0], LowThreshold.Beta[0]);
      double HighValue = GetSignalInclusiveCount(i, HighThreshold.SignalInclusiveCount[0],
         HighThreshold.Alpha[0], HighThreshold.Beta[0]);
      double LowEtaValue = GetSignalInclusiveCount(i, LowEtaThreshold.SignalInclusiveCount[0],
         LowEtaThreshold.Alpha[0], LowEtaThreshold.Beta[0]);
      double HighEtaValue = GetSignalInclusiveCount(i, HighEtaThreshold.SignalInclusiveCount[0],
         HighEtaThreshold.Alpha[0], HighEtaThreshold.Beta[0]);

      EtaGraph.SetPoint(i - 1, i, CentralValue);
      EtaGraph.SetPointError(i - 1, 0, 0, fabs(CentralValue - LowEtaValue), fabs(HighEtaValue - CentralValue));
      ScaleGraph.SetPoint(i - 1, i, CentralValue);
      ScaleGraph.SetPointError(i - 1, 0, 0, fabs(CentralValue - LowValue), fabs(HighValue - CentralValue));
   }

   PsFile.AddPlot(EtaGraph, "a3", true);
   PsFile.AddPlot(ScaleGraph, "a3", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

FitResult SimultaneousFit(string RootFile, int LastJetBin, string JetFlavor, double AlphaLValue,
   string JetAppendix)
{
   // Dependent variables
   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJet(Form("N%sJet%s", JetFlavor.c_str(), JetAppendix.c_str()), "Count of jets", 0, 20);
   RooArgSet TreeVarSet(ZMass, NJet);

   // Import data
   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get("outTree");
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet);
   
   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(Form("N%sJet%s >= 1", JetFlavor.c_str(),
      JetAppendix.c_str()));

   // Shape variable and top-level yield variables
   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.11, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.438, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", AlphaLValue, 50.01, 1000000);
   RooRealVar Sigma("Sigma", "Sigma", 2.30, 0.01, 1000000);

   RooRealVar SignalInclusiveYield("SignalInclusiveYield", "Signal yield for >= 1 jet", 1000, 1, 10000000);
   RooRealVar BackgroundInclusiveYield("BackgroundInclusiveYield", "BackgroundInclusiveYield", 1.0, 0.0, 10000.0);
   RooFormulaVar TotalYield("TotalYield", "Total Yield", "@0+@1",
      RooArgList(SignalInclusiveYield, BackgroundInclusiveYield));
   
   RooRealVar Alpha("Alpha", "Alpha parameter in signal yield", 0.2843, 0.01, 0.5);
   RooRealVar Beta("Beta", "Beta parameter in signal yield", -1e-4, -0.1, 0.1);
   
   // Build signal pdf
   vector<RooAbsPdf *> SignalShapes;
   vector<RooAbsPdf *> Constrains;
   vector<RooAbsPdf *> SignalJets;
   vector<RooFormulaVar *> SignalJetYields;
   RooArgSet SignalModels;
   RooArgSet SignalRelativeYields;
   
   for(int N = 1; N <= LastJetBin; N++)
   {
      // cruijff for each jet bin with same shape
      SignalShapes.push_back(new RooCruijff(Form("Signal%dJetShape", N), Form("Signal, %d jet", N),
         ZMass, PeakPosition, Sigma, AlphaR, Sigma, AlphaL));

      // constrain each jet bin shape to the righ number of jets
      if(N != LastJetBin)
         Constrains.push_back(new RooSameAs(Form("Constrain%dJet", N),
            Form("Delta function at %d jet", N), NJet, N, 0.5));
      else
         Constrains.push_back(new RooAtLeast(Form("Constrain%dJet", LastJetBin), Form("At least %d jets", LastJetBin),
            NJet, LastJetBin - 0.001));

      // final pdf for each jet bin
      SignalJets.push_back(new RooProdPdf(Form("Signal%dJet", N), Form("Signal, %d jet", N),
         RooArgSet(*SignalShapes[N-1], *Constrains[N-1])));

      // relative yields
      if(N != LastJetBin)
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N = %d", N),
            GetSignalYieldString(N, false).c_str(), RooArgList(Alpha, Beta)));
      else
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", LastJetBin), Form("N = %d", LastJetBin),
            GetSignalYieldString(LastJetBin, false).c_str(), RooArgList(Alpha, Beta)));
      // SignalJetYields.push_back(new RooRealVar(Form("Signal%dJetYield", N), Form("N = %d", N), 10, 0, 1000000));

      // argument sets for adding
      SignalModels.add(*SignalJets[N-1]);
      SignalRelativeYields.add(*SignalJetYields[N-1]);
   }

   // final signal pdf
   RooAddPdf SignalModel("SignalModel", "Signal model", SignalModels, SignalRelativeYields);

   // Build background pdf
   vector<RooRealVar *> BackgroundExpJet;
   vector<RooAbsPdf *> BackgroundJetShape;
   vector<RooAbsPdf *> BackgroundJets;
   vector<RooRealVar *> BackgroundJetYields;
   RooArgSet BackgroundModels;
   RooArgSet BackgroundYields;
   RooArgSet BackgroundExps;

   for(int N = 1; N <= LastJetBin; N++)
   {
      // one exp. for each jet bin: parameter and pdf
      BackgroundExpJet.push_back(new RooRealVar(Form("BackgroundExp%dJet", N),
         Form("Background exp, %d jet", N), -0.009, -1.0, 0.0));
      BackgroundJetShape.push_back(new RooExponential(Form("Background%dJetShape", N),
         Form("Background%dJetShape", N), ZMass, *BackgroundExpJet[N-1]));

      // constrain each one to the right number of bins
      BackgroundJets.push_back(new RooProdPdf(Form("Background%dJet", N), Form("Background, %d jet", N),
         RooArgSet(*BackgroundJetShape[N-1], *Constrains[N-1])));

      // background yields
      BackgroundJetYields.push_back(new RooRealVar(Form("Background%dJetYield", N),
         Form("Background yield, %d jet", N), 10, 0, 10000000));

      // argument sets for adding
      BackgroundModels.add(*BackgroundJets[N-1]);
      BackgroundYields.add(*BackgroundJetYields[N-1]);
      BackgroundExps.add(*BackgroundExpJet[N-1]);
   }

   // final background pdf
   RooAddPdf BackgroundModel("BackgroundModel", "Background model", BackgroundModels, BackgroundYields);
   
   // Add pdfs together
   RooArgSet TopLevelModels(SignalModel, BackgroundModel);
   RooArgSet TopLevelYields(SignalInclusiveYield, BackgroundInclusiveYield);
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   // Fit!
   FinalModel.fitTo(*ReducedDataSet, Verbose(false));
   
   // Plotting various stuff
   PsFileHelper PsFile("ResultPlots_FixRelation_" + JetFlavor + "_" + JetAppendix + ".ps");
   PsFile.AddTextPage("Fit results, on data");

   // notice
   vector<string> Notice;
   Notice.push_back("Notice:");
   Notice.push_back("- Ignore background yields!");
   PsFile.AddTextPage(Notice);

   // shape parameters and alpha/beta   
   RooPlot *ParametersPlot1 = ZMass.frame(Bins(50), Name("ZMassParameters1"), Title("Fit results"));
   FinalModel.paramOn(ParametersPlot1, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.9, 0.9),
      Parameters(RooArgSet(PeakPosition, AlphaL, AlphaR, Sigma, Alpha, Beta, SignalInclusiveYield,
      BackgroundInclusiveYield)));
   PsFile.AddPlot(ParametersPlot1, "", false);
   
   // background-related parameters
   RooPlot *ParametersPlot2 = ZMass.frame(Bins(50), Name("ZMassParameters2"), Title("Fit results"));
   FinalModel.paramOn(ParametersPlot2, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.9, 0.9),
      Parameters(RooArgSet(BackgroundYields, BackgroundExps)));
   PsFile.AddPlot(ParametersPlot2, "", false);

   // signal yields
   RooPlot *ParametersPlot3 = ZMass.frame(Bins(50), Name("ZMassParameters3"), Title("Fit results"));
   FinalModel.paramOn(ParametersPlot3, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.9, 0.9),
      Parameters(RooArgSet(SignalRelativeYields)));
   PsFile.AddPlot(ParametersPlot3, "", false);

   // all signal curves plotted together
   RooPlot *FinalResultPlot = ZMass.frame(Bins(50), Name("ZMassAllResults"), Title("Mass of lepton pair"));
   ReducedDataSet->plotOn(FinalResultPlot);
   FinalModel.plotOn(FinalResultPlot, LineColor(1));
   for(int N = 1; N <= LastJetBin; N++)
      FinalModel.plotOn(FinalResultPlot, Components(*SignalJets[N-1]), LineColor(N + 1));
   PsFile.AddPlot(FinalResultPlot, "", true);

   // each jet bin plotted separately   
   for(int N = 1; N <= LastJetBin; N++)
   {
      RooPlot *SeparateResultJetPlot;

      if(N != LastJetBin)
         SeparateResultJetPlot = ZMass.frame(Bins(50), Name(Form("SeparateResult%dJetPlot", N)),
            Title(Form("Exclusive %d jet", N)));
      else
         SeparateResultJetPlot = ZMass.frame(Bins(50), Name(Form("SeparateResult%dJetPlot", N)),
            Title(Form("Inclusive %d jet", N)));

      FinalModel.plotOn(SeparateResultJetPlot, Components(RooArgSet(*BackgroundJets[N-1], *SignalJets[N-1])),
         LineColor(N + 1), Normalization(TotalYield.getVal()));
      FinalModel.plotOn(SeparateResultJetPlot, Components(*BackgroundJets[N-1]), LineColor(N + 1),
         Normalization(TotalYield.getVal()));

      RooDataSet *ReducedJetDataSet;
     
      if(N != LastJetBin)
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%sJet%s == %d", JetFlavor.c_str(),
            JetAppendix.c_str(), N));
      else
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%sJet%s >= %d", JetFlavor.c_str(),
            JetAppendix.c_str(), N));

      ReducedJetDataSet->plotOn(SeparateResultJetPlot);

      PsFile.AddPlot(SeparateResultJetPlot, "", false);

      // TCanvas TempCanvas("TempCanvas", "TempCanvas", 0, 0, 1024, 768);
      // SeparateResultJetPlot->Draw();
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.png", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.eps", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.C", N));
   }

   // plots with x axis = NJets
   TGraphErrors SignalYieldGraph;
   SignalYieldGraph.SetNameTitle("SignalYieldGraph", "Fitted signal yields");
   for(int N = 1; N <= LastJetBin; N++)
   {
      SignalYieldGraph.SetPoint(N - 1, N,
         GetSignalInclusiveCount(N, SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal()));
      SignalYieldGraph.SetPointError(N - 1, 0, GetSignalInclusiveError(N,
         SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal(),
         SignalInclusiveYield.getError(), Alpha.getError(), Beta.getError()));
   }

   TGraphErrors BackgroundYieldGraph;
   BackgroundYieldGraph.SetNameTitle("BackgroundYieldGraph", "Fitted Background yields");
   double BackgroundYieldSoFar = 0;
   for(int N = LastJetBin; N >= 1; N--)
   {
      BackgroundYieldSoFar = BackgroundYieldSoFar + BackgroundJetYields[N-1]->getVal();
      BackgroundYieldGraph.SetPoint(N - 1, N, BackgroundYieldSoFar);
   }

   TH1D InputCountHistogram("InputCountHistogram", "Data vs. fit output;Inclusive Jet;Count",
      LastJetBin, 0.5, LastJetBin + 0.5);
   for(int N = 1; N <= LastJetBin; N++)
   {
      RooDataSet *ReducedInclusiveDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%sJet%s >= %d",
         JetFlavor.c_str(), JetAppendix.c_str(), N));
      InputCountHistogram.Fill(N, ReducedInclusiveDataSet->numEntries());
   }

   TCanvas YieldCanvas("YieldCanvas", "YieldCanvas", 0, 0, 1024, 768);

   InputCountHistogram.SetMarkerSize(2);
   InputCountHistogram.Draw("hist text0");

   SignalYieldGraph.SetLineColor(kBlue);
   SignalYieldGraph.Draw("pl");

   // BackgroundYieldGraph.SetLineColor(kRed);
   // BackgroundYieldGraph.Draw("pl");

   YieldCanvas.SetLogy();
   // YieldCanvas.SaveAs("FitYieldsData.png");
   // YieldCanvas.SaveAs("FitYieldsData.C");
   // YieldCanvas.SaveAs("FitYieldsData.eps");

   PsFile.AddCanvas(YieldCanvas);

   // done!
   PsFile.AddTimeStampPage();
   PsFile.Close();

   // return answer
   FitResult Result;
   Result.Alpha[0] = Alpha.getVal();
   Result.Alpha[1] = Alpha.getError();
   Result.Beta[0] = Beta.getVal();
   Result.Beta[1] = Beta.getError();
   Result.SignalInclusiveCount[0] = SignalInclusiveYield.getVal();
   Result.SignalInclusiveCount[1] = SignalInclusiveYield.getError();

   // delete transient stuff
   for(int N = 1; N <= LastJetBin; N++)
   {
      delete BackgroundJetYields[N-1];
      delete BackgroundJets[N-1];
      delete BackgroundJetShape[N-1];
      delete BackgroundExpJet[N-1];
      delete SignalJetYields[N-1];
      delete SignalJets[N-1];
      delete Constrains[N-1];
      delete SignalShapes[N-1];
   }

   // really done!
   return Result;
}

double GetSignalInclusiveCount(int jet, double SignalInclusiveYield, double Alpha, double Beta)
{
   if(jet == 0)
      return 0;
   if(jet == 1)
      return SignalInclusiveYield;

   double Yield = SignalInclusiveYield;
   for(int i = 2; i <= jet; i++)
      Yield = Yield * (Alpha + i * Beta);

   return Yield;
}

double GetSignalInclusiveError(int jet, double SignalInclusiveYield, double Alpha, double Beta,
   double SignalInclusiveYieldError, double AlphaError, double BetaError)
{
   if(jet == 0)
      return 0;
   if(jet == 1)
      return SignalInclusiveYieldError;

   double Yield = GetSignalInclusiveCount(jet, SignalInclusiveYield, Alpha, Beta);

   double dfdS = Yield / SignalInclusiveYield;
   double dfdA = 0;
   double dfdB = 0;

   for(int i = 2; i <= jet; i++)
   {
      dfdA = dfdA + 1 / (Alpha + Beta * i);
      dfdB = dfdB + i / (Alpha + Beta * i);
   }

   dfdA = dfdA * Yield;
   dfdB = dfdB * Yield;

   double SigmaF2 = dfdS * dfdS * SignalInclusiveYieldError * SignalInclusiveYieldError
      + dfdA * dfdA * AlphaError * AlphaError
      + dfdB * dfdB * BetaError * BetaError;

   return sqrt(SigmaF2);
}

string GetSignalYieldString(int jet, bool Inclusive)
{
   if(jet <= 0)
      return "";

   if(jet == 1 && Inclusive == false)
      return "(1-@0-2*@1)";
   if(jet == 1 && Inclusive == true)
      return "1";

   string Result;
   for(int i = 2; i <= jet; i++)
   {
      char ch[1024];
      sprintf(ch, "(@0+%d*@1)", i);

      if(i == 2)
         Result = ch;
      else
         Result = Result + "*" + ch;
   }

   if(Inclusive == false)
   {
      char ch[1024];
      sprintf(ch, "(1-@0-%d*@1)", jet + 1);

      Result = Result + "*" + ch;
   }

   return Result;
}


