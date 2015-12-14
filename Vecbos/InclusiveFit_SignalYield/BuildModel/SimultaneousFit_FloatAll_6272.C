#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TH2D.h"

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

void SimultaneousFit_FloatAll(string RootFile = "Samples/DataAll.root", int LastJetBin = 4,
   string JetFlavor = "PF", double AlphaLValue = 0.485);

void SimultaneousFit_FloatAll(string RootFile, int LastJetBin, string JetFlavor, double AlphaLValue)
{
   // Dependent variables
   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJet(Form("N%sJet", JetFlavor.c_str()), "Count of jets", 0, 20);
   RooArgSet TreeVarSet(ZMass, NJet);

   // Import data
   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get("outTree");
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet);
   
   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(Form("N%sJet >= 1", JetFlavor.c_str()));
   double DataSetTotalEntry = ReducedDataSet->sumEntries();

   // Shape variable and top-level yield variables
   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.11, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.438, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", AlphaLValue);
   RooRealVar Sigma("Sigma", "Sigma", 2.30, 0.01, 1000000);

   RooRealVar SignalInclusiveYield("SignalInclusiveYield", "Signal yield for >= 1 jet",
      DataSetTotalEntry, 1, 10000000);
   RooRealVar BackgroundInclusiveYield("BackgroundInclusiveYield", "BackgroundInclusiveYield", 1.0, 0.0, 10000.0);
   RooFormulaVar TotalYield("TotalYield", "Total Yield", "@0+@1",
      RooArgList(SignalInclusiveYield, BackgroundInclusiveYield));
  
   RooArgSet TopLevelModels;
   RooArgSet TopLevelYields;

   // Build signal pdf
   vector<RooAbsPdf *> SignalShapes;
   vector<RooAbsPdf *> Constrains;
   vector<RooAbsPdf *> SignalJets;
   vector<RooRealVar *> SignalJetInclusiveYields;
   vector<RooFormulaVar *> SignalJetYields;
   RooArgSet SignalModels;
   RooArgSet SignalRelativeYields;
   RooArgSet SignalJetInclusiveYieldSet;

   double CurrentGuess = DataSetTotalEntry;

   // SignalJetInclusiveYields.push_back(new RooRealVar("SignalInclusiveYield%dJet", LasJettBin),
   //    Form("Signal inclusive yield, %d jet", LastBin), 10, 0.00001, 10000000);
   for(int N = 1; N <= LastJetBin; N++)
   {
      SignalJetInclusiveYields.push_back(new RooRealVar(Form("SignalInclusiveYield%dJet", N),
         Form("Signal inclusive yield, %d jet", N), CurrentGuess, 0, 10000000));
      SignalJetInclusiveYieldSet.add(*SignalJetInclusiveYields[N-1]);
      
      CurrentGuess = CurrentGuess * 0.2;
   }

   for(int N = 1; N <= LastJetBin; N++)
   {
      // cruijff for each jet bin
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
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N == %d", N),
            "@0 - @1", RooArgSet(*SignalJetInclusiveYields[N-1], *SignalJetInclusiveYields[N])));
      else
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N >= %d", N),
            "@0", RooArgSet(*SignalJetInclusiveYields[N-1])));

      // argument sets for adding
      SignalModels.add(*SignalJets[N-1]);
      TopLevelModels.add(*SignalJets[N-1]);
      SignalRelativeYields.add(*SignalJetYields[N-1]);
      TopLevelYields.add(*SignalJetYields[N-1]);
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
         Form("Background exp, %d jet", N), 0.000, -1.0, 0.0));
      BackgroundJetShape.push_back(new RooExponential(Form("Background%dJetShape", N),
         Form("Background%dJetShape", N), ZMass, *BackgroundExpJet[N-1]));

      // constrain each one to the right number of bins
      BackgroundJets.push_back(new RooProdPdf(Form("Background%dJet", N), Form("Background, %d jet", N),
         RooArgSet(*BackgroundJetShape[N-1], *Constrains[N-1])));

      // background yields
      BackgroundJetYields.push_back(new RooRealVar(Form("Background%dJetYield", N),
         Form("Background yield, %d jet", N), 0, 0, 10000000));

      // argument sets for adding
      BackgroundModels.add(*BackgroundJets[N-1]);
      TopLevelModels.add(*BackgroundJets[N-1]);
      BackgroundYields.add(*BackgroundJetYields[N-1]);
      TopLevelYields.add(*BackgroundJetYields[N-1]);
      BackgroundExps.add(*BackgroundExpJet[N-1]);
   }

   // final background pdf
   RooAddPdf BackgroundModel("BackgroundModel", "Background model", BackgroundModels, BackgroundYields);
   
   // Add pdfs together
   // RooArgSet TopLevelModels(SignalModel, BackgroundModel);
   // RooArgSet TopLevelYields(SignalInclusiveYield, BackgroundInclusiveYield);
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   // Fit!
   FinalModel.fitTo(*ReducedDataSet, Verbose(false));
   
   // Plotting various stuff
   PsFileHelper PsFile("ResultPlots_FloatAll_" + JetFlavor + ".ps");
   PsFile.AddTextPage("Fit results, on data");

   // notice
   // vector<string> Notice;
   // Notice.push_back("Notice:");
   // Notice.push_back("- Ignore background yields!");
   // PsFile.AddTextPage(Notice);

   // shape parameters and alpha/beta   
   RooPlot *ParametersPlot1 = ZMass.frame(Bins(50), Name("ZMassParameters1"), Title("Fit results"));
   FinalModel.paramOn(ParametersPlot1, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.9, 0.9),
      Parameters(RooArgSet(PeakPosition, AlphaL, AlphaR, Sigma, SignalInclusiveYield,
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
      Parameters(RooArgSet(SignalJetInclusiveYieldSet)));
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

      // FinalModel.plotOn(SeparateResultJetPlot, Components(RooArgSet(*BackgroundJets[N-1], *SignalJets[N-1])),
      //    LineColor(N + 1), Normalization(SignalJetInclusiveYields[N-1]->getVal()));
      // FinalModel.plotOn(SeparateResultJetPlot, Components(*BackgroundJets[N-1]), LineColor(N + 1));
      
      FinalModel.plotOn(SeparateResultJetPlot, Components(RooArgSet(*BackgroundJets[N-1], *SignalJets[N-1])),
         LineColor(N + 1), Normalization(TotalYield.getVal()));
      FinalModel.plotOn(SeparateResultJetPlot, Components(*BackgroundJets[N-1]), LineColor(N + 1),
         Normalization(TotalYield.getVal()));

      RooDataSet *ReducedJetDataSet;
      if(N != LastJetBin)
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%sJet == %d", JetFlavor.c_str(), N));
      else
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%sJet >= %d", JetFlavor.c_str(), N));

      ReducedJetDataSet->plotOn(SeparateResultJetPlot);

      PsFile.AddPlot(SeparateResultJetPlot, "", false);

      // TCanvas TempCanvas("TempCanvas", "TempCanvas", 0, 0, 1024, 768);
      // SeparateResultJetPlot->Draw();
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.png", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.eps", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.C", N));
   }

   /*
   // plots with x axis = NJets
   TGraphErrors SignalYieldGraph;
   SignalYieldGraph.SetNameTitle("SignalYieldGraph", "Fitted signal yields");
   for(int N = 1; N <= LastJetBin; N++)
   {
      SignalYieldGraph.SetPoint(N - 1, N, SignalJetInclusiveYields[N-1]->getVal());
      SignalYieldGraph.SetPointError(N - 1, 0, SignalJetInclusiveYields[N-1]->getError());
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
      RooDataSet *ReducedInclusiveDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%sJet >= %d", JetFlavor.c_str(), N));
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
   */

   TH2D SummaryPlot("SummaryPlot", "Summary Plot", LastJetBin, 0.5, LastJetBin + 0.5, 4, -0.5, 3.5);

   SummaryPlot.GetYaxis()->SetBinLabel(4, "Signal exclusive");
   SummaryPlot.GetYaxis()->SetBinLabel(3, "Background exclusive");
   SummaryPlot.GetYaxis()->SetBinLabel(2, "Signal inclusive");
   SummaryPlot.GetYaxis()->SetBinLabel(1, "Background inclusive");

   double FittedSignalInclusiveYield = SignalInclusiveYield.getVal();
   double FittedSignalWithJetInclusiveYield = SignalJetInclusiveYields[0]->getVal();
   double SignalFactor = FittedSignalInclusiveYield / FittedSignalWithJetInclusiveYield;
   SignalFactor = 1;

   double FittedBackgroundInclusiveYield = BackgroundInclusiveYield.getVal();
   double FittedBackgroundWithJetInclusiveYield = 0;
   for(int N = 1; N <= LastJetBin; N++)
      FittedBackgroundWithJetInclusiveYield = FittedBackgroundWithJetInclusiveYield
         + BackgroundJetYields[N-1]->getVal();
   double BackgroundFactor = FittedBackgroundInclusiveYield / FittedBackgroundWithJetInclusiveYield;
   BackgroundFactor = 1;

   double TotalBackgroundSoFar = 0;
   double BackgroundError2SoFar = 0;

   for(int N = LastJetBin; N >= 1; N--)
   {
      SummaryPlot.GetXaxis()->SetBinLabel(N, Form("%d", N));

      SummaryPlot.SetBinContent(N, 4, SignalJetYields[N-1]->getVal() * SignalFactor);
      SummaryPlot.SetBinError(N, 4, 0);

      SummaryPlot.SetBinContent(N, 3, BackgroundJetYields[N-1]->getVal() * BackgroundFactor);
      SummaryPlot.SetBinError(N, 3, BackgroundJetYields[N-1]->getError() * BackgroundFactor);

      SummaryPlot.SetBinContent(N, 2, SignalJetInclusiveYields[N-1]->getVal() * SignalFactor);
      SummaryPlot.SetBinError(N, 2, SignalJetInclusiveYields[N-1]->getError() * SignalFactor);
      
      TotalBackgroundSoFar = TotalBackgroundSoFar + BackgroundJetYields[N-1]->getVal();
      BackgroundError2SoFar = BackgroundError2SoFar
         + BackgroundJetYields[N-1]->getError() * BackgroundJetYields[N-1]->getError();

      SummaryPlot.SetBinContent(N, 1, TotalBackgroundSoFar * BackgroundFactor);
      SummaryPlot.SetBinError(N, 1, sqrt(BackgroundError2SoFar) * BackgroundFactor);
   }

   SummaryPlot.SetStats(0);
   SummaryPlot.SetMarkerSize(2);

   PsFile.AddPlot(SummaryPlot, "text0 error");

   // TCanvas Canvas(0, 0, 1024, 768);
   // Canvas.SaveAs("");

   // done!
   PsFile.AddTimeStampPage();
   PsFile.Close();

   // delete transient stuff
   for(int N = 1; N <= LastJetBin; N++)
   {
      delete BackgroundJetYields[N-1];
      delete BackgroundJets[N-1];
      delete BackgroundJetShape[N-1];
      delete BackgroundExpJet[N-1];
      delete SignalJetInclusiveYields[N-1];
      delete SignalJetYields[N-1];
      delete SignalJets[N-1];
      delete Constrains[N-1];
      delete SignalShapes[N-1];
   }
}

