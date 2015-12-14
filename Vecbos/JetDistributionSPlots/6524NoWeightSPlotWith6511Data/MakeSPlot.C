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

#include "RooStats/SPlot.h"
using namespace RooStats;

#include "PlotHelper.h"
#include "DataHelper.h"
#include "DrawRandom.h"

void SimultaneousFit_FloatAll(string RootFile = "Samples/DataAll.root", int LastJetBin = 4,
   string JetFlavor = "PF", int EnergyThreshold = 30, string DataHelperFile = "Samples/DataAll.dh");

void SimultaneousFit_FloatAll(string RootFile, int LastJetBin, string JetFlavor,
   int EnergyThreshold, string DataHelperFile)
{
   // Upper-case jet flavor string
   string UppercaseJetFlavor = JetFlavor;
   for(int i = 0; i < (int)UppercaseJetFlavor.size(); i++)
   {
      if(UppercaseJetFlavor[i] >= 'a' && UppercaseJetFlavor[i] <= 'z')
         UppercaseJetFlavor[i] = 'A' + (UppercaseJetFlavor[i] - 'a');
   }

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
   if(DHFile[StateString].Exist("ZeroJetBinAlphaL") == false)
   {
      cout << "Please fit the 0-jet bin with tight isolation first!" << endl;
      return;
   }

   double AlphaLValue = DHFile[StateString]["AlphaL"].GetDouble();
   cout << "Extracted AlphaL = " << AlphaLValue << endl;

   double ZeroJetBinAlphaLValue = DHFile[StateString]["ZeroJetBinAlphaL"].GetDouble();
   cout << "Extracted AlphaL for 0-jet bin = " << ZeroJetBinAlphaLValue << endl;

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
   RooRealVar Category("cat_idx", "Category", -10, 10);
   RooRealVar FirstJetPT("firstJet_pt", "First jet PT", -100000, 100000);
   RooRealVar SecondJetPT("secondJet_pt", "Second jet PT", -100000, 100000);
   RooRealVar Mu1PT("muPt", "Muon 1 PT", -1000000, 1000000);
   RooRealVar Mu2PT("mu2Pt", "Muon 2 PT", -1000000, 1000000);
   RooRealVar Mu1Eta("muEta", "Muon 1 Eta", -1000000, 1000000);
   RooRealVar Mu2Eta("mu2Eta", "Muon 2 Eta", -1000000, 1000000);
   RooRealVar ZPT("Z_pt", "Z PT", -10000000, 10000000);
   RooRealVar ZEta("Z_eta", "Z Eta", -10000000, 10000000);
   RooRealVar ZPhi("Z_phi", "Z Phi", -10000000, 10000000);
   RooRealVar Dxy("Dxy", "Dxy", -100000000, 1000000);
   RooRealVar Dz("Dz", "Dz", -100000000, 1000000);
   RooRealVar Isolation("Iso_pf_relpt", "Muon isolation", -100000000, 100000000);
   // RooRealVar W("W", "Weight", -10000, 10000);
   RooArgSet TreeVarSet(ZMass, NJet, Category, FirstJetPT, SecondJetPT);
   TreeVarSet.add(Mu1PT);
   TreeVarSet.add(Mu2PT);
   TreeVarSet.add(Mu1Eta);
   TreeVarSet.add(Mu2Eta);
   TreeVarSet.add(ZPT);
   TreeVarSet.add(ZEta);
   TreeVarSet.add(ZPhi);
   TreeVarSet.add(Dxy);
   TreeVarSet.add(Dz);
   TreeVarSet.add(Isolation);

   // Import data
   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get("unweighted");
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet);   // unweighted
   
   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce("cat_idx == 1 && Z_mass < 120 && Z_mass > 60");
   double DataSetTotalEntry = ReducedDataSet->sumEntries();

   cout << "Number of events = " << DataSetTotalEntry << endl;

   // Shape variable and top-level yield variables
   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.11, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.438, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", AlphaLValue);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.30, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.30, 0.01, 1000000);

   RooRealVar ZeroJetBinPeakPosition("ZeroJetBinPeakPosition", "Z position (first bin)", 90.11, 80, 100, "GeV/c^2");
   RooRealVar ZeroJetBinAlphaR("ZeroJetBinAlphaR", "ZeroJetBinAlphaR", 0.438, 0.01, 1000000);
   RooRealVar ZeroJetBinAlphaL("ZeroJetBinAlphaL", "ZeroJetBinAlphaL", ZeroJetBinAlphaLValue);
   RooRealVar ZeroJetBinSigmaR("ZeroJetBinSigmaR", "ZeroJetBinSigmaR", 2.30, 0.01, 1000000);
   RooRealVar ZeroJetBinSigmaL("ZeroJetBinSigmaL", "ZeroJetBinSigmaL", 2.30, 0.01, 1000000);

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

   for(int N = 0; N <= LastJetBin; N++)
   {
      SignalJetInclusiveYields.push_back(new RooRealVar(Form("SignalInclusiveYield%dJet", N),
         Form("Signal inclusive yield, %d jet", N), CurrentGuess * (1 + DrawGaussian(0.05)), 0, 20000));
      SignalJetInclusiveYieldSet.add(*SignalJetInclusiveYields[N]);
      
      CurrentGuess = CurrentGuess / (AlphaFromComplicatedFit + BetaFromComplicatedFit * N);
   }

   for(int N = 0; N <= LastJetBin; N++)
   {
      // cruijff for each jet bin
      if(N == 0)
         SignalShapes.push_back(new RooCruijff(Form("Signal%dJetShape", N), Form("Signal, %d jet", N),
            ZMass, ZeroJetBinPeakPosition, ZeroJetBinSigmaR, ZeroJetBinAlphaR, ZeroJetBinSigmaL, ZeroJetBinAlphaL));
      else
         SignalShapes.push_back(new RooCruijff(Form("Signal%dJetShape", N), Form("Signal, %d jet", N),
            ZMass, PeakPosition, SigmaR, AlphaR, SigmaR, AlphaL));

      // constrain each jet bin shape to the righ number of jets
      if(N != LastJetBin)
         Constrains.push_back(new RooSameAs(Form("Constrain%dJet", N),
            Form("Delta function at %d jet", N), NJet, N, 0.5));
      else
         Constrains.push_back(new RooAtLeast(Form("Constrain%dJet", LastJetBin), Form("At least %d jets", LastJetBin),
            NJet, LastJetBin - 0.5));

      // final pdf for each jet bin
      SignalJets.push_back(new RooProdPdf(Form("Signal%dJet", N), Form("Signal, %d jet", N),
         RooArgSet(*SignalShapes[N], *Constrains[N])));

      // relative yields
      if(N != LastJetBin)
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N == %d", N),
            "@0 - @1", RooArgSet(*SignalJetInclusiveYields[N], *SignalJetInclusiveYields[N+1])));
      else
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N >= %d", N),
            "@0", RooArgSet(*SignalJetInclusiveYields[N])));

      // argument sets for adding
      TopLevelModels.add(*SignalJets[N]);
      TopLevelYields.add(*SignalJetYields[N]);
   }

   // Build background pdf
   vector<RooRealVar *> BackgroundExpJet;
   vector<RooAbsPdf *> BackgroundJetShape;
   vector<RooAbsPdf *> BackgroundJets;
   vector<RooRealVar *> BackgroundJetYields;

   RooArgSet BackgroundYields;
   RooArgSet BackgroundExps;

   for(int N = 0; N <= LastJetBin; N++)
   {
      // one exp. for each jet bin: parameter and pdf
      BackgroundExpJet.push_back(new RooRealVar(Form("BackgroundExp%dJet", N),
         Form("Background exp, %d jet", N), -0.02, -1.0, 0.0));
      BackgroundJetShape.push_back(new RooExponential(Form("Background%dJetShape", N),
         Form("Background%dJetShape", N), ZMass, *BackgroundExpJet[N]));

      // constrain each one to the right number of bins
      BackgroundJets.push_back(new RooProdPdf(Form("Background%dJet", N), Form("Background, %d jet", N),
         RooArgSet(*BackgroundJetShape[N], *Constrains[N])));

      // background yields
      int UpperBound = 200;
      if(N <= 1)
         UpperBound = 20;
      BackgroundJetYields.push_back(new RooRealVar(Form("Background%dJetYield", N),
         Form("Background yield, %d jet", N), 1, 0, UpperBound));

      // argument sets for adding
      TopLevelModels.add(*BackgroundJets[N]);
      TopLevelYields.add(*BackgroundJetYields[N]);
      BackgroundYields.add(*BackgroundJetYields[N]);
      BackgroundExps.add(*BackgroundExpJet[N]);
   }

   // Add pdfs together
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   // Fit!
   RooFitResult *FitResult = FinalModel.fitTo(*ReducedDataSet, Verbose(false), Save(true), SumW2Error(false));

   // set everything (except yields) to constant
   PeakPosition.setConstant(true);
   AlphaR.setConstant(true);
   SigmaR.setConstant(true);
   SigmaL.setConstant(true);
   ZeroJetBinPeakPosition.setConstant(true);
   ZeroJetBinAlphaR.setConstant(true);
   ZeroJetBinSigmaR.setConstant(true);
   ZeroJetBinSigmaL.setConstant(true);
   for(int i = 0; i < (int)BackgroundExpJet.size(); i++)
      BackgroundExpJet[i]->setConstant(true);

   // Make a list of yields
   RooArgList ParameterList;
   for(int i = 0; i < (int)SignalJetInclusiveYields.size(); i++)
      ParameterList.add(*SignalJetInclusiveYields[i]);
   for(int i = 0; i < (int)BackgroundJetYields.size(); i++)
      ParameterList.add(*BackgroundJetYields[i]);

   ReducedDataSet->Print();
   FinalModel.Print("v");
   FitResult->Print("v");

   // Calculate s-Weight
   SPlot *SData = new SPlot("sData", "An SPlot", *ReducedDataSet, &FinalModel, ParameterList);

   TFile SFile("SFile.root", "RECREATE");
   ReducedDataSet->Clone("SWeight")->Write();
   ReducedDataSet->tree()->Clone("SWeightTree")->Write();
   FitResult->Clone("InitialResult")->Write();
   SFile.Close();

   // delete transient stuff
   for(int N = 0; N <= LastJetBin; N++)
   {
      delete BackgroundJetYields[N];
      delete BackgroundJets[N];
      delete BackgroundJetShape[N];
      delete BackgroundExpJet[N];
      delete SignalJetInclusiveYields[N];
      delete SignalJetYields[N];
      delete SignalJets[N];
      delete Constrains[N];
      delete SignalShapes[N];
   }
}

