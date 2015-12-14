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

#include "DrawRandom.h"
#include "PlotHelper.h"

void SimultaneousFit_FloatAll(string RootFile = "Samples/ToyForCaloJet.root", int LastJetBin = 5,
   string JetFlavor = "Calo", double AlphaLValue = 0.522, string OutputRootFile = "CaloFitResult_00501_001000.root",
   int Start = 501, int End = 1000);

void SimultaneousFit_FloatAll(string RootFile, int LastJetBin, string JetFlavor, double AlphaLValue,
   string OutputRootFile, int Start, int End)
{
   TFile InputFile(RootFile.c_str());

   TFile OutputFile(OutputRootFile.c_str(), "RECREATE");

   TTree ResultTree("ResultTree", "ResultTree");

   double InclusiveSignalCountBranch[10] = {0};
   double InclusiveSignalErrorBranch[10] = {0};
   double BackgroundCountBranch[10] = {0};
   double BackgroundErrorBranch[10] = {0};
   double BackgroundExpBranch[10] = {0};
   double BackgroundExpErrorBranch[10] = {0};
   double AlphaLBranch[2] = {0};
   double AlphaRBranch[2] = {0};
   double SigmaLBranch[2] = {0};
   double SigmaRBranch[2] = {0};
   double MassBranch[2] = {0};

   for(int N = 1; N <= LastJetBin; N++)
   {
      ResultTree.Branch(Form("InclusiveSignal%d", N), &InclusiveSignalCountBranch[N-1], Form("InclusiveSignal%d/D", N));
      ResultTree.Branch(Form("InclusiveSignal%dError", N), &InclusiveSignalErrorBranch[N-1],
         Form("InclusiveSignal%dError/D", N));
      ResultTree.Branch(Form("Background%d", N), &BackgroundCountBranch[N-1], Form("Background%d/D", N));
      ResultTree.Branch(Form("Background%dError", N), &BackgroundErrorBranch[N-1], Form("Background%dError/D", N));
      ResultTree.Branch(Form("Background%dExp", N), &BackgroundExpBranch[N-1], Form("Background%dExp/D", N));
      ResultTree.Branch(Form("Background%dExpError", N),
         &BackgroundExpErrorBranch[N-1], Form("Background%dExpError/D", N));
   }
   ResultTree.Branch("AlphaL", &AlphaLBranch[0], "AlphaL/D");
   ResultTree.Branch("AlphaLError", &AlphaLBranch[1], "AlphaLError/D");
   ResultTree.Branch("AlphaR", &AlphaRBranch[0], "AlphaR/D");
   ResultTree.Branch("AlphaRError", &AlphaRBranch[1], "AlphaRError/D");
   ResultTree.Branch("SigmaL", &SigmaLBranch[0], "SigmaL/D");
   ResultTree.Branch("SigmaLError", &SigmaLBranch[1], "SigmaLError/D");
   ResultTree.Branch("SigmaR", &SigmaRBranch[0], "SigmaR/D");
   ResultTree.Branch("SigmaRError", &SigmaRBranch[1], "SigmaRError/D");
   ResultTree.Branch("Mass", &MassBranch[0], "Mass/D");
   ResultTree.Branch("MassError", &MassBranch[1], "MassError/D");

   for(int iCount = Start - 1; iCount < End; iCount++)
   {
      // Dependent variables
      RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
      RooRealVar NJet(Form("N%sJet", JetFlavor.c_str()), "Count of jets", 1, 20);
      RooArgSet TreeVarSet(ZMass, NJet);

      // Get dataset
      RooDataSet *DataSet = (RooDataSet *)InputFile.Get(Form("ToyExperiment%d", iCount + 1));
      double DataSetTotalEntry = DataSet->sumEntries();

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
            Form("Signal inclusive yield, %d jet", N), CurrentGuess, 0, 10000000));
         SignalJetInclusiveYieldSet.add(*SignalJetInclusiveYields[N-1]);

         CurrentGuess = CurrentGuess * 0.2;
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
            Constrains.push_back(new RooAtLeast(Form("Constrain%dJet", LastJetBin),
               Form("At least %d jets", LastJetBin),
               NJet, LastJetBin - 0.001));

         // final pdf for each jet bin
         SignalJets.push_back(new RooProdPdf(Form("Signal%dJet", N), Form("Signal, %d jet", N),
            RooArgSet(*SignalShapes[N-1], *Constrains[N-1])));

         // exclusive jet yields
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
         TopLevelModels.add(*BackgroundJets[N-1]);
         TopLevelYields.add(*BackgroundJetYields[N-1]);
         BackgroundYields.add(*BackgroundJetYields[N-1]);
         BackgroundExps.add(*BackgroundExpJet[N-1]);
      }

      // Add pdfs together
      RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

      // Fit!
      FinalModel.fitTo(*DataSet, Verbose(false));

      // Print something so that we know it works
      cout << "Inclusive yields:" << endl;
      for(int i = 0; i < (int)SignalJetInclusiveYields.size(); i++)
         cout << "   " << SignalJetInclusiveYields[i]->getVal() << " +- "
            << SignalJetInclusiveYields[i]->getError() << endl;
      cout << endl;

      // Save to tree
      for(int N = 1; N <= LastJetBin; N++)
      {
         InclusiveSignalCountBranch[N-1] = SignalJetInclusiveYields[N-1]->getVal();
         InclusiveSignalErrorBranch[N-1] = SignalJetInclusiveYields[N-1]->getError();
         BackgroundCountBranch[N-1] = BackgroundJetYields[N-1]->getVal();
         BackgroundErrorBranch[N-1] = BackgroundJetYields[N-1]->getError();
         BackgroundExpBranch[N-1] = BackgroundExpJet[N-1]->getVal();
         BackgroundExpErrorBranch[N-1] = BackgroundExpJet[N-1]->getError();
      }
      AlphaLBranch[0] = AlphaLValue;
      AlphaLBranch[1] = 0;
      AlphaRBranch[0] = AlphaR.getVal();
      AlphaRBranch[1] = AlphaR.getError();
      SigmaLBranch[0] = SigmaL.getVal();
      SigmaLBranch[1] = SigmaL.getError();
      SigmaRBranch[0] = SigmaR.getVal();
      SigmaRBranch[1] = SigmaR.getError();
      MassBranch[0] = PeakPosition.getVal();
      MassBranch[1] = PeakPosition.getError();

      ResultTree.Fill();

      // Delete transient stuff
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

   ResultTree.Write();

   OutputFile.Close();

   InputFile.Close();
}

