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
#include "TF1.h"

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
#include "DrawRandom.h"

void SimultaneousFit_FloatAll(string RootFile = "Samples/DataAll.root", int LastJetBin = 4,
   string JetFlavor = "PF", int EnergyThreshold = 30, string DataHelperFile = "Samples/DataAll.dh", int RunNumber = 0);

void SimultaneousFit_FloatAll(string RootFile, int LastJetBin, string JetFlavor,
   int EnergyThreshold, string DataHelperFile, int RunNumber)
{
   // Get numbers from dh file
   DataHelper DHFile(DataHelperFile);

   char StateString[1000];
   sprintf(StateString, "%s Jet, %d, Eta range all, Isolation 0.05", JetFlavor.c_str(), EnergyThreshold);

   if(DHFile.Exist(StateString) == false)
   {
      cout << "Please fit with tight isolation first!" << endl;
      return;
   }
   if(DHFile[StateString].Exist("AlphaL") == false)
   {
      cout << "Please fit with tight isolation first!" << endl;
      return;
   }

   double AlphaLValue = DHFile[StateString]["AlphaL"].GetDouble();
   cout << "Extracted AlphaL = " << AlphaLValue << endl;

   sprintf(StateString, "%s Jet, %d, Eta range all, Isolation none", JetFlavor.c_str(), EnergyThreshold);

   if(DHFile.Exist(StateString) == false)
   {
      cout << "Please do the constrained fit first!" << endl;
      return;
   }

   if(DHFile[StateString].Exist("ConstrainedFitAlpha") == false
      || DHFile[StateString].Exist("ConstrainedFitBeta") == false
      || DHFile[StateString].Exist("ConstrainedFitAlphaError") == false
      || DHFile[StateString].Exist("ConstrainedFitBetaError") == false
      || DHFile[StateString].Exist("ConstrainedFitAlphaBetaCorrelation") == false)
   {
      cout << "Please do the constrained fit first!" << endl;
      return;
   }

   double AlphaFromComplicatedFit = DHFile[StateString]["ConstrainedFitAlpha"].GetDouble();
   double SigmaAlphaFromComplicatedFit = DHFile[StateString]["ConstrainedFitAlphaError"].GetDouble();
   double BetaFromComplicatedFit = DHFile[StateString]["ConstrainedFitBeta"].GetDouble();
   double SigmaBetaFromComplicatedFit = DHFile[StateString]["ConstrainedFitBetaError"].GetDouble();
   double ComplicatedCorrelation = DHFile[StateString]["ConstrainedFitAlphaBetaCorrelation"].GetDouble();

   cout << "Extracted constrained fit alpha = " << AlphaFromComplicatedFit << " +- "
      << SigmaAlphaFromComplicatedFit << endl;
   cout << "Extracted constrained fit beta = " << BetaFromComplicatedFit << " +- "
      << SigmaBetaFromComplicatedFit << endl;
   cout << "Correlation = " << ComplicatedCorrelation << endl;

   // Dependent variables
   RooRealVar ZMass("Z_mass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJet(Form("N%s_%d", JetFlavor.c_str(), EnergyThreshold), "Count of jets", 0, 20);
   RooArgSet TreeVarSet(ZMass, NJet);

   // Import data
   TFile F1(RootFile.c_str());
   RooDataSet *DataSet = (RooDataSet *)F1.Get(Form("Sample_%d", RunNumber));
   
   double DataSetTotalEntry = DataSet->sumEntries();

   cout << "Number of events = " << DataSetTotalEntry << endl;

   // Shape variable and top-level yield variables
   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.11, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.438, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", AlphaLValue);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.30, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.30, 0.01, 1000000);

   RooArgSet TopLevelModels;
   RooArgSet TopLevelYields;

   // Build signal pdf
   vector<RooAbsPdf *> SignalShapes;
   vector<RooAbsPdf *> Constrains;
   vector<RooAbsPdf *> SignalJets;
   vector<RooRealVar *> SignalJetInclusiveYields;
   vector<RooFormulaVar *> SignalJetYields;
   
   RooArgSet SignalJetInclusiveYieldSet;

   double CurrentGuess = DataSetTotalEntry;

   for(int N = 1; N <= LastJetBin; N++)
   {
      SignalJetInclusiveYields.push_back(new RooRealVar(Form("SignalInclusiveYield%dJet", N),
         Form("Signal inclusive yield, %d jet", N), CurrentGuess * (1 + DrawGaussian(0.05)), 0, 10000000));
      SignalJetInclusiveYieldSet.add(*SignalJetInclusiveYields[N-1]);
      
      CurrentGuess = CurrentGuess / (AlphaFromComplicatedFit + BetaFromComplicatedFit * N);
   }

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
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N == %d", N),
            "@0 - @1", RooArgSet(*SignalJetInclusiveYields[N-1], *SignalJetInclusiveYields[N])));
      else
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N >= %d", N),
            "@0", RooArgSet(*SignalJetInclusiveYields[N-1])));

      // argument sets for adding
      TopLevelModels.add(*SignalJets[N-1]);
      TopLevelYields.add(*SignalJetYields[N-1]);
   }

   // Build background pdf
   vector<RooRealVar *> BackgroundExpJet;
   vector<RooAbsPdf *> BackgroundJetShape;
   vector<RooAbsPdf *> BackgroundJets;
   vector<RooRealVar *> BackgroundJetYields;

   RooArgSet BackgroundYields;
   RooArgSet BackgroundExps;

   for(int N = 1; N <= LastJetBin; N++)
   {
      // one exp. for each jet bin: parameter and pdf
      BackgroundExpJet.push_back(new RooRealVar(Form("BackgroundExp%dJet", N),
         Form("Background exp, %d jet", N), -0.02, -1.0, 0.0));
      BackgroundJetShape.push_back(new RooExponential(Form("Background%dJetShape", N),
         Form("Background%dJetShape", N), ZMass, *BackgroundExpJet[N-1]));

      // constrain each one to the right number of bins
      BackgroundJets.push_back(new RooProdPdf(Form("Background%dJet", N), Form("Background, %d jet", N),
         RooArgSet(*BackgroundJetShape[N-1], *Constrains[N-1])));

      // background yields
      int UpperBound = 200;
      if(N == 1)
         UpperBound = 50;
      BackgroundJetYields.push_back(new RooRealVar(Form("Background%dJetYield", N),
         Form("Background yield, %d jet", N), 1, 0, UpperBound));

      // argument sets for adding
      TopLevelModels.add(*BackgroundJets[N-1]);
      TopLevelYields.add(*BackgroundJetYields[N-1]);
      BackgroundYields.add(*BackgroundJetYields[N-1]);
      BackgroundExps.add(*BackgroundExpJet[N-1]);
   }

   // Add pdfs together
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   // Fit!
   RooFitResult *FitResult = FinalModel.fitTo(*DataSet, Verbose(false), Save(true));

   // Write out fit result
   TFile ResultFile(Form("FitResult_%d.root", EnergyThreshold), "UPDATE");
   FitResult->Clone(Form("FitResult%d", RunNumber))->Write();
   ResultFile.Close();
   
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

   F1.Close();
}

