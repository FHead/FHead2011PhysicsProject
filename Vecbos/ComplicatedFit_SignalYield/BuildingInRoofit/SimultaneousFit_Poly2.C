#include <string>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TGraphErrors.h"

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

struct BackgroundParameters
{
   double A0;
   double A1;
   double A2;
   double Yield;
};

void SimultaneousFit_Poly2(string RootFile = "Samples/ZJetsAll.root",
   string BackgroundRootFile = "Samples/TTbarAll.root");
double GetSignalInclusiveCount(int jet, double SignalInclusiveYield, double Alpha, double Beta);
double GetSignalInclusiveError(int jet, double SignalInclusiveYield, double Alpha, double Beta,
   double SignalInclusiveYieldError, double AlphaError, double BetaError);
BackgroundParameters GuessBackgroundInitialValue(RooDataSet &DataSet, RooRealVar &ZMass,
   int jet, bool inclusive = false);

void SimultaneousFit_Poly2(string RootFile, string BackgroundRootFile)
{
   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NCaloJet("NCaloJet", "Count of jets", 0, 20);
   RooArgSet TreeVarSet(ZMass, NCaloJet);

   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get("outTree");
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet);
   
   TFile F2(BackgroundRootFile.c_str());
   TTree *ZTree2 = (TTree *)F2.Get("outTree");
   RooDataSet BackgroundDataSet("FakeZCandidates", "FakeZCandidates", ZTree2, TreeVarSet);
   DataSet.append(BackgroundDataSet);

   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce("NCaloJet >= 1");

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.11, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.438, 50.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.581, 50.01, 1000000);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.30, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.07, 0.01, 1000000);

   RooCruijff Signal1JetShape("Signal1JetShape", "Signal, 1 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooCruijff Signal2JetShape("Signal2JetShape", "Signal, 2 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooCruijff Signal3JetShape("Signal3JetShape", "Signal, 3 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooCruijff Signal4JetShape("Signal4JetShape", "Signal, 4 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooCruijff Signal5JetShape("Signal5JetShape", "Signal, >= 5 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);

   RooSameAs Constrain1Jet("Constrain1Jet", "Delta function at 1 jet", NCaloJet, 1, 0.5);
   RooSameAs Constrain2Jet("Constrain2Jet", "Delta function at 2 jet", NCaloJet, 2, 0.5);
   RooSameAs Constrain3Jet("Constrain3Jet", "Delta function at 3 jet", NCaloJet, 3, 0.5);
   RooSameAs Constrain4Jet("Constrain4Jet", "Delta function at 4 jet", NCaloJet, 4, 0.5);
   RooAtLeast Constrain5Jet("Constrain5Jet", "At least 5 jets", NCaloJet, 5 - 0.001);

   RooProdPdf Signal1Jet("Signal1Jet", "Signal, 1 jet", RooArgSet(Signal1JetShape, Constrain1Jet));
   RooProdPdf Signal2Jet("Signal2Jet", "Signal, 2 jet", RooArgSet(Signal2JetShape, Constrain2Jet));
   RooProdPdf Signal3Jet("Signal3Jet", "Signal, 3 jet", RooArgSet(Signal3JetShape, Constrain3Jet));
   RooProdPdf Signal4Jet("Signal4Jet", "Signal, 4 jet", RooArgSet(Signal4JetShape, Constrain4Jet));
   RooProdPdf Signal5Jet("Signal5Jet", "Signal, 5 jet", RooArgSet(Signal5JetShape, Constrain5Jet));

   RooRealVar SignalInclusiveYield("SignalInclusiveYield", "Signal yield for >= 1 jet", 1000, 1, 10000000);
   RooRealVar Alpha("Alpha", "Alpha parameter in signal yield", 0.209, 0.0001, 0.5);
   RooRealVar Beta("Beta", "Beta parameter in signal yield", -1e-4, -0.1, 0.1);

   RooFormulaVar Signal1JetYield("Signal1JetYield", "N = 1",
      "(1-@0-2*@1)", RooArgList(Alpha, Beta));
   RooFormulaVar Signal2JetYield("Signal2JetYield", "N = 2",
      "(@0+2*@1)*(1-@0-3*@1)", RooArgList(Alpha, Beta));
   RooFormulaVar Signal3JetYield("Signal3JetYield", "N = 3",
      "(@0+2*@1)*(@0+3*@1)*(1-@0-4*@1)", RooArgList(Alpha, Beta));
   RooFormulaVar Signal4JetYield("Signal4JetYield", "N = 4",
      "(@0+2*@1)*(@0+3*@1)*(@0+4*@1)*(1-@0-5*@1)", RooArgList(Alpha, Beta));
   RooFormulaVar Signal5JetYield("Signal5JetYield", "N >= 5",
      "(@0+2*@1)*(@0+3*@1)*(@0+4*@1)*(@0+5*@1)", RooArgList(Alpha, Beta));

   RooArgSet SignalModels(Signal1Jet, Signal2Jet, Signal3Jet, Signal4Jet, Signal5Jet);
   RooArgSet SignalRelativeYields(Signal1JetYield, Signal2JetYield, Signal3JetYield, Signal4JetYield, Signal5JetYield);
   RooAddPdf SignalModel("SignalModel", "Signal model", SignalModels, SignalRelativeYields);

   BackgroundParameters Guess1Jet = GuessBackgroundInitialValue(*ReducedDataSet, ZMass, 1, false);
   BackgroundParameters Guess2Jet = GuessBackgroundInitialValue(*ReducedDataSet, ZMass, 2, false);
   BackgroundParameters Guess3Jet = GuessBackgroundInitialValue(*ReducedDataSet, ZMass, 3, false);
   BackgroundParameters Guess4Jet = GuessBackgroundInitialValue(*ReducedDataSet, ZMass, 4, false);
   BackgroundParameters Guess5Jet = GuessBackgroundInitialValue(*ReducedDataSet, ZMass, 5, true);

   RooRealVar Background1JetA0("Background1JetA0", "Background a0, 1 jet", Guess1Jet.A0);
   RooRealVar Background2JetA0("Background2JetA0", "Background a0, 2 jet", Guess2Jet.A0);
   RooRealVar Background3JetA0("Background3JetA0", "Background a0, 3 jet", Guess3Jet.A0);
   RooRealVar Background4JetA0("Background4JetA0", "Background a0, 4 jet", Guess4Jet.A0);
   RooRealVar Background5JetA0("Background5JetA0", "Background a0, 5 jet", Guess5Jet.A0);

   RooRealVar Background1JetA1("Background1JetA1", "Background a1, 1 jet", Guess1Jet.A1, -0.0083, 0.0);
   RooRealVar Background2JetA1("Background2JetA1", "Background a1, 2 jet", Guess2Jet.A1, -0.0083, 0.0);
   RooRealVar Background3JetA1("Background3JetA1", "Background a1, 3 jet", Guess3Jet.A1, -0.0083, 0.0);
   RooRealVar Background4JetA1("Background4JetA1", "Background a1, 4 jet", Guess4Jet.A1, -0.0083, 0.0);
   RooRealVar Background5JetA1("Background5JetA1", "Background a1, 5 jet", Guess5Jet.A1, -0.0083, 0.0);

   RooRealVar Background1JetA2("Background1JetA2", "Background a2, 1 jet", Guess1Jet.A2);
   RooRealVar Background2JetA2("Background2JetA2", "Background a2, 2 jet", Guess2Jet.A2);
   RooRealVar Background3JetA2("Background3JetA2", "Background a2, 3 jet", Guess3Jet.A2);
   RooRealVar Background4JetA2("Background4JetA2", "Background a2, 4 jet", Guess4Jet.A2);
   RooRealVar Background5JetA2("Background5JetA2", "Background a2, 5 jet", Guess5Jet.A2);
   
   RooPolynomial Background1JetShape("Background1JetShape", "Background1JetShape",
      ZMass, RooArgList(Background1JetA0, Background1JetA1, Background1JetA2), 0);
   RooPolynomial Background2JetShape("Background2JetShape", "Background2JetShape",
      ZMass, RooArgList(Background2JetA0, Background2JetA1, Background2JetA2), 0);
   RooPolynomial Background3JetShape("Background3JetShape", "Background3JetShape",
      ZMass, RooArgList(Background3JetA0, Background3JetA1, Background3JetA2), 0);
   RooPolynomial Background4JetShape("Background4JetShape", "Background4JetShape",
      ZMass, RooArgList(Background4JetA0, Background4JetA1, Background4JetA2), 0);
   RooPolynomial Background5JetShape("Background5JetShape", "Background5JetShape",
      ZMass, RooArgList(Background5JetA0, Background5JetA1, Background5JetA2), 0);
   
   RooProdPdf Background1Jet("Background1Jet", "Background, 1 jet", RooArgSet(Background1JetShape, Constrain1Jet));
   RooProdPdf Background2Jet("Background2Jet", "Background, 2 jet", RooArgSet(Background2JetShape, Constrain2Jet));
   RooProdPdf Background3Jet("Background3Jet", "Background, 3 jet", RooArgSet(Background3JetShape, Constrain3Jet));
   RooProdPdf Background4Jet("Background4Jet", "Background, 4 jet", RooArgSet(Background4JetShape, Constrain4Jet));
   RooProdPdf Background5Jet("Background5Jet", "Background, >= 5 jet", RooArgSet(Background5JetShape, Constrain5Jet));

   RooRealVar Background1JetYield("Background1JetYield", "Background yield, 1 jet", Guess1Jet.Yield, 0, 1000000);
   RooRealVar Background2JetYield("Background2JetYield", "Background yield, 2 jet", Guess2Jet.Yield, 0, 1000000);
   RooRealVar Background3JetYield("Background3JetYield", "Background yield, 3 jet", Guess3Jet.Yield, 0, 1000000);
   RooRealVar Background4JetYield("Background4JetYield", "Background yield, 4 jet", Guess4Jet.Yield, 0, 1000000);
   RooRealVar Background5JetYield("Background5JetYield", "Background yield, >= 5 jet", Guess5Jet.Yield, 0, 1000000);

   RooArgSet BackgroundModels(Background1Jet, Background2Jet, Background3Jet, Background4Jet, Background5Jet);
   RooArgSet BackgroundYields(Background1JetYield, Background2JetYield, Background3JetYield,
      Background4JetYield, Background5JetYield);
   RooAddPdf BackgroundModel("BackgroundModel", "Background model", BackgroundModels, BackgroundYields);

   RooRealVar BackgroundInclusiveYield("BackgroundInclusiveYield", "BackgroundInclusiveYield", 1.0, 0.0, 10000000.0);

   // RooFormulaVar TotalYield("TotalYield", "Total yield", "@0", RooArgList(BackgroundInclusiveYield));
   RooFormulaVar TotalYield("TotalYield", "Total yield", "@0+@1",
      RooArgList(BackgroundInclusiveYield, SignalInclusiveYield));

   RooArgSet TopLevelModels(SignalModel, BackgroundModel);
   RooArgSet TopLevelYields(SignalInclusiveYield, BackgroundInclusiveYield);
   // RooArgSet TopLevelModels(BackgroundModel);
   // RooArgSet TopLevelYields(BackgroundInclusiveYield);
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   FinalModel.fitTo(*ReducedDataSet, Verbose(false));

   // Fit Results...plotting
   PsFileHelper PsFile("ResultPlots.ps");
   PsFile.AddTextPage("Fit results~");
   
   RooPlot *ParametersPlot = ZMass.frame(Bins(50), Name("ZMassParameters"), Title("Fit results"));
   FinalModel.paramOn(ParametersPlot, Format("NELU", AutoPrecision(2), Layout(0.1, 0.4, 0.9)));
   PsFile.AddPlot(ParametersPlot, "", false);

   RooPlot *FinalResultPlot = ZMass.frame(Bins(50), Name("ZMassAllResults"), Title("Mass of lepton pair"));
   ReducedDataSet->plotOn(FinalResultPlot);
   FinalModel.plotOn(FinalResultPlot, LineColor(kYellow));
   FinalModel.plotOn(FinalResultPlot, Components(Signal1Jet), LineColor(kGreen));
   FinalModel.plotOn(FinalResultPlot, Components(Signal2Jet), LineColor(kBlue));
   FinalModel.plotOn(FinalResultPlot, Components(Signal3Jet), LineColor(kBlack));
   FinalModel.plotOn(FinalResultPlot, Components(Signal4Jet), LineColor(kRed));
   FinalModel.plotOn(FinalResultPlot, Components(Signal5Jet), LineColor(kMagenta));
   PsFile.AddPlot(FinalResultPlot, "", true);

   RooPlot *SeparateResult1JetPlot = ZMass.frame(Bins(50), Name("SeparateResult1JetPlot"), Title("Exclusive 1 jet"));
   FinalModel.plotOn(SeparateResult1JetPlot, Components(Signal1Jet), LineColor(kGreen),
      Normalization(TotalYield.getVal()));
   FinalModel.plotOn(SeparateResult1JetPlot, Components(Background1Jet),
      Normalization(TotalYield.getVal()));
   RooDataSet *Reduced1JetDataSet = (RooDataSet *)ReducedDataSet->reduce("NCaloJet == 1");
   Reduced1JetDataSet->plotOn(SeparateResult1JetPlot);
   PsFile.AddPlot(SeparateResult1JetPlot, "", true);

   RooPlot *SeparateResult2JetPlot = ZMass.frame(Bins(50), Name("SeparateResult2JetPlot"), Title("Exclusive 2 jets"));
   FinalModel.plotOn(SeparateResult2JetPlot, Components(Signal2Jet), LineColor(kBlue),
      Normalization(TotalYield.getVal()));
   FinalModel.plotOn(SeparateResult2JetPlot, Components(Background2Jet),
      Normalization(TotalYield.getVal()));
   RooDataSet *Reduced2JetDataSet = (RooDataSet *)ReducedDataSet->reduce("NCaloJet == 2");
   Reduced2JetDataSet->plotOn(SeparateResult2JetPlot);
   PsFile.AddPlot(SeparateResult2JetPlot, "", true);

   RooPlot *SeparateResult3JetPlot = ZMass.frame(Bins(50), Name("SeparateResult3JetPlot"), Title("Exclusive 3 jets"));
   FinalModel.plotOn(SeparateResult3JetPlot, Components(Signal3Jet), LineColor(kBlack),
      Normalization(TotalYield.getVal()));
   FinalModel.plotOn(SeparateResult3JetPlot, Components(Background3Jet),
      Normalization(TotalYield.getVal()));
   RooDataSet *Reduced3JetDataSet = (RooDataSet *)ReducedDataSet->reduce("NCaloJet == 3");
   Reduced3JetDataSet->plotOn(SeparateResult3JetPlot);
   PsFile.AddPlot(SeparateResult3JetPlot, "", true);

   RooPlot *SeparateResult4JetPlot = ZMass.frame(Bins(50), Name("SeparateResult4JetPlot"), Title("Exclusive 4 jets"));
   FinalModel.plotOn(SeparateResult4JetPlot, Components(RooArgSet(Background4Jet, Signal4Jet)), LineColor(kRed),
      Normalization(TotalYield.getVal()));
   FinalModel.plotOn(SeparateResult4JetPlot, Components(Signal4Jet), LineColor(kRed),
      Normalization(TotalYield.getVal()));
   FinalModel.plotOn(SeparateResult4JetPlot, Components(Background4Jet),
      Normalization(TotalYield.getVal()));
   RooDataSet *Reduced4JetDataSet = (RooDataSet *)ReducedDataSet->reduce("NCaloJet == 4");
   Reduced4JetDataSet->plotOn(SeparateResult4JetPlot);
   PsFile.AddPlot(SeparateResult4JetPlot, "", true);

   RooPlot *SeparateResult5JetPlot = ZMass.frame(Bins(50), Name("SeparateResult5JetPlot"), Title("Inclusive 5 jets"));
   FinalModel.plotOn(SeparateResult5JetPlot, Components(Signal5Jet), LineColor(kMagenta),
      Normalization(TotalYield.getVal()));
   FinalModel.plotOn(SeparateResult5JetPlot, Components(Background5Jet),
      Normalization(TotalYield.getVal()));
   RooDataSet *Reduced5JetDataSet = (RooDataSet *)ReducedDataSet->reduce("NCaloJet >= 5");
   Reduced5JetDataSet->plotOn(SeparateResult5JetPlot);
   PsFile.AddPlot(SeparateResult5JetPlot, "", true);

   TGraphErrors SignalYieldGraph;
   SignalYieldGraph.SetNameTitle("SignalYieldGraph", "Fitted signal yields");
   SignalYieldGraph.SetPoint(0, 1,
      GetSignalInclusiveCount(1, SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal()));
   SignalYieldGraph.SetPoint(1, 2,
      GetSignalInclusiveCount(2, SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal()));
   SignalYieldGraph.SetPoint(2, 3,
      GetSignalInclusiveCount(3, SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal()));
   SignalYieldGraph.SetPoint(3, 4,
      GetSignalInclusiveCount(4, SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal()));
   SignalYieldGraph.SetPoint(4, 5,
      GetSignalInclusiveCount(5, SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal()));
   SignalYieldGraph.SetPointError(0, 0, GetSignalInclusiveError(1,
      SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal(),
      SignalInclusiveYield.getError(), Alpha.getError(), Beta.getError()));
   SignalYieldGraph.SetPointError(1, 0, GetSignalInclusiveError(2,
      SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal(),
      SignalInclusiveYield.getError(), Alpha.getError(), Beta.getError()));
   SignalYieldGraph.SetPointError(2, 0, GetSignalInclusiveError(3,
      SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal(),
      SignalInclusiveYield.getError(), Alpha.getError(), Beta.getError()));
   SignalYieldGraph.SetPointError(3, 0, GetSignalInclusiveError(4,
      SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal(),
      SignalInclusiveYield.getError(), Alpha.getError(), Beta.getError()));
   SignalYieldGraph.SetPointError(4, 0, GetSignalInclusiveError(5,
      SignalInclusiveYield.getVal(), Alpha.getVal(), Beta.getVal(),
      SignalInclusiveYield.getError(), Alpha.getError(), Beta.getError()));

   double B1 = Background1JetYield.getVal();
   double B2 = Background2JetYield.getVal();
   double B3 = Background3JetYield.getVal();
   double B4 = Background4JetYield.getVal();
   double B5 = Background5JetYield.getVal();

   TGraphErrors BackgroundYieldGraph;
   BackgroundYieldGraph.SetNameTitle("BackgroundYieldGraph", "Fitted Background yields");
   BackgroundYieldGraph.SetPoint(0, 1, B1 + B2 + B3 + B4 + B5);
   BackgroundYieldGraph.SetPoint(1, 2, B2 + B3 + B4 + B5);
   BackgroundYieldGraph.SetPoint(2, 3, B3 + B4 + B5);
   BackgroundYieldGraph.SetPoint(3, 4, B4 + B5);
   BackgroundYieldGraph.SetPoint(4, 5, B5);

   double I1 = Reduced1JetDataSet->numEntries();
   double I2 = Reduced2JetDataSet->numEntries();
   double I3 = Reduced3JetDataSet->numEntries();
   double I4 = Reduced4JetDataSet->numEntries();
   double I5 = Reduced5JetDataSet->numEntries();

   TH1D InputCountHistogram("InputCountHistogram", "Input!;Inclusive Jet;Count", 5, 0.5, 5.5);
   InputCountHistogram.Fill(1, I1 + I2 + I3 + I4 + I5);
   InputCountHistogram.Fill(2, I2 + I3 + I4 + I5);
   InputCountHistogram.Fill(3, I3 + I4 + I5);
   InputCountHistogram.Fill(4, I4 + I5);
   InputCountHistogram.Fill(5, I5);

   TCanvas YieldCanvas("YieldCanvas", "YieldCanvas", 0, 0, 1024, 768);

   InputCountHistogram.Draw();

   SignalYieldGraph.SetLineColor(kGreen);
   SignalYieldGraph.Draw("pl");

   BackgroundYieldGraph.SetLineColor(kRed);
   BackgroundYieldGraph.Draw("pl");

   YieldCanvas.SetLogy();

   PsFile.AddCanvas(YieldCanvas);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();
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

BackgroundParameters GuessBackgroundInitialValue(RooDataSet &DataSet, RooRealVar &ZMass, int jet, bool inclusive)
{
   TCut CutString;
   if(inclusive == false)
      CutString = Form("NCaloJet == %d && ZMass < 75 && ZMass > 105", jet);
   else
      CutString = Form("NCaloJet >= %d", jet);

   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(CutString);

   RooRealVar A0(Form("A0_BackgroundEstimate%dJet", jet), "A0", 1);
   RooRealVar A1(Form("A1_BackgroundEstimate%dJet", jet), "A1", -0.006, -0.0083, 0.0);
   RooPolynomial Linear(Form("Polynomial_BackgroundEstimate%dJet", jet), "Polynomial", ZMass, RooArgList(A0, A1), 0);

   RooRealVar Yield(Form("Yield_BackgruondEstimate%dJet", jet), "Yield", 100, 0, 10000000);

   RooAddPdf Model(Form("Model_BackgroundEstimate%dJet", jet), "Model", RooArgSet(Linear), RooArgSet(Yield));

   Model.fitTo(*ReducedDataSet);

   BackgroundParameters result;
   result.A0 = 1;
   result.A1 = A1.getVal();
   result.A2 = 0;
   result.Yield = Yield.getVal();

   return result;
}


