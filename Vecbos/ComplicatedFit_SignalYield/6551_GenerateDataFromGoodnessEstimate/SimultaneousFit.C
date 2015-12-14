#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLegend.h"

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
#include "RooFitResult.h"
using namespace RooFit;

#include "PlotHelper.h"
#include "DataHelper.h"

void SimultaneousFit(string RootFile = "Samples/DataAll.root", int LastJetBin = 4, string JetFlavor = "Track",
   int EnergyThreshold = 30, string DataHelperFile = "Samples/DataAll.dh", bool Weighted = false);
double GetSignalInclusiveCount(int jet, double SignalInclusiveYield, double Alpha, double Beta);
double GetSignalInclusiveError(int jet, double SignalInclusiveYield, double Alpha, double Beta,
   double SignalInclusiveYieldError, double AlphaError, double BetaError);
string GetSignalYieldString(int jet, bool Inclusive = false);

void SimultaneousFit(string RootFile, int LastJetBin, string JetFlavor, int EnergyThreshold,
   string DataHelperFile, bool Weighted)
{
   string WeightedTag = "";
   if(Weighted == true)
      WeightedTag = "W";
   else
      WeightedTag = "U";

   // Get AlphaL value
   char StateString[1000];
   sprintf(StateString, "%s Jet, %d, Eta range all, Isolation 0.05", JetFlavor.c_str(), EnergyThreshold);

   DataHelper DHFile(DataHelperFile);

   cout << DHFile.GetListOfKeys().size() << endl;

   if(DHFile.Exist(StateString) == false)
   {
      cout << "Error!  State not found.  Run the tight isolation fit first." << endl;
      return;
   }
   if(DHFile[StateString].Exist("AlphaL") == false)
   {
      cout << "Error!  Field not found.  Run the tight isolation fit first." << endl;
      return;
   }

   double AlphaLValue = DHFile[StateString]["AlphaL"].GetDouble();

   cout << "Extracted alphaL = " << AlphaLValue << endl;

   // Dependent variables
   RooRealVar ZMass("Z_mass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJet(Form("N%s_%d", JetFlavor.c_str(), EnergyThreshold), "Count of jets", 0, 20);
   RooRealVar Category("cat_idx", "Category", -10, 10);
   RooRealVar W("W", "Weight", -10000, 10000);
   RooArgSet TreeVarSet(ZMass, NJet, Category, W);

   // Import data
   string WeightString = "";
   if(Weighted == false)
      WeightString = "";
   else
      WeightString = "W";

   string TreeName = "";
   if(Weighted == false)
      TreeName = "unweighted";
   else
      TreeName = "weighted";

   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get(TreeName.c_str());
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet, "", WeightString.c_str());

   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(Form("N%s_%d >= 1 && cat_idx == 1 && Z_mass < 120 && Z_mass > 60", JetFlavor.c_str(), EnergyThreshold));
   double DataSetTotalEntry = ReducedDataSet->sumEntries();

   cout << "Number of entries = " << DataSetTotalEntry << endl;

   ReducedDataSet->Print();

   // Shape variable and top-level yield variables
   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.11, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.438, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", AlphaLValue);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.30, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.30, 0.01, 1000000);

   RooArgSet TopLevelModels;
   RooArgSet TopLevelYields;

   RooRealVar SignalInclusiveYield("SignalInclusiveYield", "Signal yield for >= 1 jet",
      DataSetTotalEntry, 1, 10000000);
   RooRealVar BackgroundInclusiveYield("BackgroundInclusiveYield", "BackgroundInclusiveYield", 1.0, 0.0, 10000.0);
   RooFormulaVar TotalYield("TotalYield", "Total Yield", "@0+@1",
      RooArgList(SignalInclusiveYield, BackgroundInclusiveYield));
   
   RooRealVar Alpha("Alpha", "Alpha parameter in signal yield", 3.13, 1, 10);
   RooRealVar Beta("Beta", "Beta parameter in signal yield", 0.10, -3, 3);
   
   // Build signal pdf
   vector<RooAbsPdf *> SignalShapes;
   vector<RooAbsPdf *> Constrains;
   vector<RooAbsPdf *> SignalJets;
   vector<RooFormulaVar *> SignalJetYields;

   RooArgSet SignalJetInclusiveYieldSet;
   SignalJetInclusiveYieldSet.add(SignalInclusiveYield);
   
   for(int N = 1; N <= LastJetBin; N++)
   {
      // cruijff for each jet bin
      SignalShapes.push_back(new RooCruijff(Form("Signal%dJetShape", N), Form("Signal, %d jet", N),
         ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL));

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
            GetSignalYieldString(N, false).c_str(), RooArgList(Alpha, Beta, SignalInclusiveYield)));
      else
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", LastJetBin), Form("N = %d", LastJetBin),
            GetSignalYieldString(LastJetBin, true).c_str(), RooArgList(Alpha, Beta, SignalInclusiveYield)));

      // argument sets for adding
      TopLevelModels.add(*SignalJets[N-1]);
      TopLevelYields.add(*SignalJetYields[N-1]);
      SignalJetInclusiveYieldSet.add(*SignalJetYields[N-1]);
   }

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
         Form("Background exp, %d jet", N), -0.009, -0.4, -0.001));
      BackgroundJetShape.push_back(new RooExponential(Form("Background%dJetShape", N),
         Form("Background%dJetShape", N), ZMass, *BackgroundExpJet[N-1]));

      // constrain each one to the right number of bins
      BackgroundJets.push_back(new RooProdPdf(Form("Background%dJet", N), Form("Background, %d jet", N),
         RooArgSet(*BackgroundJetShape[N-1], *Constrains[N-1])));

      // background yields
      double UpperBound = 1000;
      if(N == 1)
         UpperBound = 50;
      BackgroundJetYields.push_back(new RooRealVar(Form("Background%dJetYield", N),
         Form("Background yield, %d jet", N), 1, 0.2, UpperBound));

      // argument sets for adding
      TopLevelModels.add(*BackgroundJets[N-1]);
      TopLevelYields.add(*BackgroundJetYields[N-1]);
      BackgroundExps.add(*BackgroundExpJet[N-1]);
      BackgroundYields.add(*BackgroundJetYields[N-1]);
   }

   // Add pdfs together
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   // Fit!
   RooFitResult *FitResult = FinalModel.fitTo(*ReducedDataSet, Verbose(false), Save(true), SumW2Error(Weighted));
   
   // generate samples
   TFile FF(Form("Dataset%d.root", EnergyThreshold), "recreate");

   RooDataSet *NewDataSet = (RooDataSet *)FinalModel.generate(RooArgSet(ZMass, NJet), (int)DataSetTotalEntry * 10);
   NewDataSet->SetName("Dataset generated with 10x statistics at fit minimum");
   NewDataSet->Write();

   FF.Close();

   // Plotting various stuff
   char EnergyThresholdString[1000] = "";
   sprintf(EnergyThresholdString, "%d", EnergyThreshold);
   PsFileHelper PsFile("ResultPlots" + WeightedTag + "_" + JetFlavor + "_" + EnergyThresholdString + ".ps");
   PsFile.AddTextPage("Fit results, on data");

   // shape parameters and alpha/beta   
   RooPlot *ParametersPlot1 = ZMass.frame(Bins(50), Name("ZMassParameters1"), Title("Fit results"));
   FinalModel.paramOn(ParametersPlot1, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.9, 0.9),
      Parameters(RooArgSet(PeakPosition, AlphaL, AlphaR, SigmaL, SigmaR, Alpha, Beta, SignalInclusiveYield,
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
      Parameters(SignalJetInclusiveYieldSet));
   PsFile.AddPlot(ParametersPlot3, "", false);

   // all signal curves plotted together
   RooPlot *FinalResultPlot = ZMass.frame(Bins(50), Name("ZMassAllResults"), Title("Mass of lepton pair"));
   if(Weighted == false)
      ReducedDataSet->plotOn(FinalResultPlot);
   else
      ReducedDataSet->plotOn(FinalResultPlot, DataError(RooAbsData::SumW2));
   FinalModel.plotOn(FinalResultPlot, LineColor(1));
   for(int N = 1; N <= LastJetBin; N++)
      FinalModel.plotOn(FinalResultPlot, Components(*SignalJets[N-1]), LineColor(N + 1));
   PsFile.AddPlot(FinalResultPlot, "", true);

   TCanvas FourPanelCanvas("FourPanelCanvas", "FourPanelCanvas", 0, 0, 1024, 768);
   FourPanelCanvas.Divide(2, 2);

   // each jet bin plotted separately   
   for(int N = 1; N <= LastJetBin; N++)
   {
      RooPlot *SeparateResultJetPlot;

      if(N != LastJetBin)
         SeparateResultJetPlot = ZMass.frame(Bins(25), Name(Form("SeparateResult%dJetPlot", N)),
            Title(Form("Exclusive %d jet", N)));
      else
         SeparateResultJetPlot = ZMass.frame(Bins(25), Name(Form("SeparateResult%dJetPlot", N)),
            Title(Form("Inclusive %d jet", N)));

      FinalModel.plotOn(SeparateResultJetPlot, Components(RooArgSet(*BackgroundJets[N-1], *SignalJets[N-1])),
         LineColor(N + 1), Normalization(TotalYield.getVal()));
      FinalModel.plotOn(SeparateResultJetPlot, Components(*BackgroundJets[N-1]), LineColor(N + 1),
         Normalization(TotalYield.getVal()));

      RooDataSet *ReducedJetDataSet;
     
      if(N != LastJetBin)
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%s_%d == %d", JetFlavor.c_str(), EnergyThreshold, N));
      else
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%s_%d >= %d", JetFlavor.c_str(), EnergyThreshold, N));

      if(Weighted == false)
         ReducedJetDataSet->plotOn(SeparateResultJetPlot);
      else
         ReducedJetDataSet->plotOn(SeparateResultJetPlot, DataError(RooAbsData::SumW2));

      PsFile.AddPlot(SeparateResultJetPlot, "", false);

      // TCanvas TempCanvas("TempCanvas", "TempCanvas", 0, 0, 1024, 768);
      // SeparateResultJetPlot->Draw();
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.png", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.eps", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.C", N));

      if(N <= 4)
      {
         FourPanelCanvas.cd(N);
         SeparateResultJetPlot->Draw();
      }
   }

   FourPanelCanvas.SaveAs(Form("ComplicatedFit%s_%s_%d_AllJets.png", WeightedTag.c_str(),
      JetFlavor.c_str(), EnergyThreshold));
   FourPanelCanvas.SaveAs(Form("ComplicatedFit%s_%s_%d_AllJets.C", WeightedTag.c_str(),
      JetFlavor.c_str(), EnergyThreshold));
   FourPanelCanvas.SaveAs(Form("ComplicatedFit%s_%s_%d_AllJets.eps", WeightedTag.c_str(),
      JetFlavor.c_str(), EnergyThreshold));

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
      RooDataSet *ReducedInclusiveDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%s_%d >= %d", JetFlavor.c_str(), EnergyThreshold, N));
      InputCountHistogram.Fill(N, ReducedInclusiveDataSet->sumEntries());
   }

   TCanvas YieldCanvas("YieldCanvas", "YieldCanvas", 0, 0, 1024, 768);

   InputCountHistogram.SetMarkerSize(2);
   InputCountHistogram.SetStats(0);
   InputCountHistogram.Draw("hist text0 error");

   SignalYieldGraph.SetLineColor(kBlue);
   SignalYieldGraph.Draw("pl");

   BackgroundYieldGraph.SetLineColor(kRed);
   BackgroundYieldGraph.Draw("pl");

   TLegend legend(0.5, 0.8, 0.8, 0.6);
   legend.SetFillColor(0);
   legend.AddEntry(&InputCountHistogram, "Data", "l");
   legend.AddEntry(&SignalYieldGraph, "Signal yield", "l");
   legend.AddEntry(&BackgroundYieldGraph, "Background yield", "l");
   legend.Draw();

   YieldCanvas.SetLogy();
   YieldCanvas.SaveAs(Form("FitYieldsData%s.png", WeightedTag.c_str()));
   YieldCanvas.SaveAs(Form("FitYieldsData%s.C", WeightedTag.c_str()));
   YieldCanvas.SaveAs(Form("FitYieldsData%s.eps", WeightedTag.c_str()));

   PsFile.AddCanvas(YieldCanvas);

   cout << "Correlation between alpha and beta = " << FitResult->correlation(Alpha, Beta) << endl;

   vector<string> SummaryValueTexts;
   char ch[1024] = "";
   sprintf(ch, "Alpha = %f +- %f", Alpha.getVal(), Alpha.getError());
   SummaryValueTexts.push_back(ch);
   sprintf(ch, "Beta = %f +- %f", Beta.getVal(), Beta.getError());
   SummaryValueTexts.push_back(ch);
   sprintf(ch, "Correlation between alpha and beta = %f", FitResult->correlation(Alpha, Beta));
   SummaryValueTexts.push_back(ch);
   PsFile.AddTextPage(SummaryValueTexts);

   // write numbers out to DH file
   sprintf(StateString, "%s Jet, %d, Eta range all, Isolation none", JetFlavor.c_str(), EnergyThreshold);
   DHFile[StateString]["ConstrainedFitAlpha"] = Alpha.getVal();
   DHFile[StateString]["ConstrainedFitAlphaError"] = Alpha.getError();
   DHFile[StateString]["ConstrainedFitBeta"] = Beta.getVal();
   DHFile[StateString]["ConstrainedFitBetaError"] = Beta.getError();
   DHFile[StateString]["ConstrainedFitAlphaBetaCorrelation"] = FitResult->correlation(Alpha, Beta);
   DHFile[StateString]["ConstrainedFitYield"] = SignalInclusiveYield.getVal();
   DHFile[StateString]["ConstrainedFitYieldError"] = SignalInclusiveYield.getError();
   DHFile[StateString]["ConstrainedFitAlphaL"] = AlphaL.getVal();
   DHFile[StateString]["ConstrainedFitAlphaLError"] = AlphaL.getError();
   DHFile[StateString]["ConstrainedFitAlphaR"] = AlphaR.getVal();
   DHFile[StateString]["ConstrainedFitAlphaRError"] = AlphaR.getError();
   DHFile[StateString]["ConstrainedFitSigmaL"] = SigmaL.getVal();
   DHFile[StateString]["ConstrainedFitSigmaLError"] = SigmaL.getError();
   DHFile[StateString]["ConstrainedFitSigmaR"] = SigmaR.getVal();
   DHFile[StateString]["ConstrainedFitSigmaRError"] = SigmaR.getError();
   DHFile[StateString]["ConstrainedFitMass"] = PeakPosition.getVal();
   DHFile[StateString]["ConstrainedFitMassError"] = PeakPosition.getError();
   DHFile[StateString]["ConstrainedFitMaxN"] = LastJetBin;

   DHFile.SaveToFile(DataHelperFile);

   // done!
   PsFile.AddTimeStampPage();
   PsFile.Close();

   // write out fit result
   TFile ResultFile(("ResultPlots" + WeightedTag + "_" + JetFlavor + "_" + EnergyThresholdString + ".root").c_str(),
      "RECREATE");

   FitResult->Clone("ConstrainedResult")->Write();

   ResultFile.Close();

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
}

double GetSignalInclusiveCount(int jet, double SignalInclusiveYield, double Alpha, double Beta)
{
   if(jet == 0)
      return 0;
   if(jet == 1)
      return SignalInclusiveYield;

   double Yield = SignalInclusiveYield;
   for(int i = 1; i < jet; i++)
      Yield = Yield / (Alpha + i * Beta);

   return Yield;
}

double GetSignalInclusiveError(int jet, double SignalInclusiveYield, double Alpha, double Beta,
   double SignalInclusiveYieldError, double AlphaError, double BetaError)
{
   return 0;   // later....

   /*
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
   */
}

string GetSignalYieldString(int jet, bool Inclusive)
{
   if(jet <= 0)
      return "";

   if(jet == 1 && Inclusive == false)
   {
      cout << 1 << " @2*(@0+@1-1)/(@0+@1)" << endl;
      return "@2*(@0+@1-1)/(@0+@1)";
   }
   if(jet == 1 && Inclusive == true)
      return "@2";

   string Result = "@2";
   for(int i = 1; i < jet; i++)
   {
      char ch[1024];
      sprintf(ch, "(@0+%d*@1)", i);

      Result = Result + "/" + ch;
   }

   if(Inclusive == false)
   {
      char ch[1024];
      sprintf(ch, "(@0+%d*@1-1)/(@0+%d*@1)", jet, jet);

      Result = Result + "*" + ch;
   }

   cout << jet << " " << Result << endl;

   return Result;
}


