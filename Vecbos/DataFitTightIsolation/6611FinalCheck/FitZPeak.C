#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TF1.h"
#include "TStyle.h"
#include "TPaveText.h"

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

void FitZPeak(string RootFile = "Samples/DataAll.root", int LastJetBin = 4,
   string JetFlavor = "PF", int EnergyThreshold = 30, string DataHelperFile = "Samples/DataAll.dh",
   bool Weighted = false, string SmearingMatrixFile = "PF30SmearingMatrix", double Isolation = 0.05);
vector<vector<double> > ReadSmearingMatrix(string SmearingMatrixFile);

void FitZPeak(string RootFile, int LastJetBin, string JetFlavor,
   int EnergyThreshold, string DataHelperFile, bool Weighted, string SmearingMatrixFile, double Isolation)
{
   string WeightString = "";
   if(Weighted == true)
      WeightString = "W";
   else
      WeightString = "U";

   // Upper-case jet flavor string
   string UppercaseJetFlavor = JetFlavor;
   for(int i = 0; i < (int)UppercaseJetFlavor.size(); i++)
   {
      if(UppercaseJetFlavor[i] >= 'a' && UppercaseJetFlavor[i] <= 'z')
         UppercaseJetFlavor[i] = 'A' + (UppercaseJetFlavor[i] - 'a');
   }

   // Read smearing matrix
   vector<vector<double> > SmearingMatrix = ReadSmearingMatrix(SmearingMatrixFile);

   // Dependent variables
   RooRealVar ZMass("Z_mass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJet(Form("N%s_%d", JetFlavor.c_str(), EnergyThreshold), "Count of jets", 0, 20);
   RooRealVar Category("cat_idx", "Category", -10, 10);
   RooRealVar W("W", "Weight", -10000, 10000);
   RooRealVar Iso_pf_relpt("Iso_pf_relpt", "Iso_pf_relpt", -10000, 100000);
   RooRealVar Mu2Eta("mu2Eta", "second muon eta", -500, 500);
   RooArgSet TreeVarSet(ZMass, NJet, Category, W, Iso_pf_relpt, Mu2Eta);

   // Import data
   string TreeName = "";
   if(Weighted == true)
      TreeName = "weighted";
   else
      TreeName = "unweighted";

   string WeightBranch = "";
   if(Weighted == false)
      WeightBranch = "";
   else
      WeightBranch = "W";
   
   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get(TreeName.c_str());
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet, "", WeightBranch.c_str());
   
   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(Form("N%s_%d >= 0 && cat_idx == 1 && Z_mass < 120 && Z_mass > 60 && Iso_pf_relpt < %f && mu2Eta < 2.1 && mu2Eta > -2.1", JetFlavor.c_str(), EnergyThreshold, Isolation));
   double DataSetTotalEntry = ReducedDataSet->sumEntries();

   cout << "Number of events = " << DataSetTotalEntry << endl;

   // Shape variable and top-level yield variables
   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.11, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.438, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.5, 0.01, 1000000);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.30, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.30, 0.01, 1000000);

   RooRealVar ZeroJetBinPeakPosition("ZeroJetBinPeakPosition", "Z position (first bin)", 90.11, 80, 100, "GeV/c^2");
   RooRealVar ZeroJetBinAlphaR("ZeroJetBinAlphaR", "ZeroJetBinAlphaR", 0.438, 0.01, 1000000);
   RooRealVar ZeroJetBinAlphaL("ZeroJetBinAlphaL", "ZeroJetBinAlphaL", 0.5, 0.01, 1000000);
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
         Form("Signal inclusive yield, %d jet", N), CurrentGuess * (1 + DrawGaussian(0.05)), 0, 10000000));
      SignalJetInclusiveYieldSet.add(*SignalJetInclusiveYields[N]);

      CurrentGuess = CurrentGuess / 4;
   }

   for(int N = 0; N <= LastJetBin; N++)
   {
      // cruijff for each jet bin
      if(N == 0)
         SignalShapes.push_back(new RooCruijff(Form("Signal%dJetShape", N), Form("Signal, %d jet", N),
            ZMass, ZeroJetBinPeakPosition, ZeroJetBinSigmaR, ZeroJetBinAlphaR, ZeroJetBinSigmaL, ZeroJetBinAlphaL));
      else
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
         RooArgSet(*SignalShapes[N], *Constrains[N])));

      // relative yields - include unfolding
      stringstream str;
      for(int N2 = 0; N2 <= LastJetBin; N2++)
      {
         if(N2 != 0)
            str << " + ";

         str << SmearingMatrix[N][N2] << " * ";

         if(N2 != LastJetBin)
            str << "(@" << N2 << " - " << "@" << N2 + 1 << ")";
         else
            str << "@" << N2;
      }

      cout << "Signal yield: " << N << " ---- " << str.str() << endl;

      if(N != LastJetBin)
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N == %d", N),
            str.str().c_str(), SignalJetInclusiveYieldSet));
      else
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N >= %d", N),
            str.str().c_str(), SignalJetInclusiveYieldSet));

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
         Form("Background exp, %d jet", N), -0.02, -0.4, 0.0));
      BackgroundJetShape.push_back(new RooExponential(Form("Background%dJetShape", N),
         Form("Background%dJetShape", N), ZMass, *BackgroundExpJet[N]));

      // constrain each one to the right number of bins
      BackgroundJets.push_back(new RooProdPdf(Form("Background%dJet", N), Form("Background, %d jet", N),
         RooArgSet(*BackgroundJetShape[N], *Constrains[N])));

      // background yields
      int UpperBound = 100;
      BackgroundJetYields.push_back(new RooRealVar(Form("Background%dJetYield", N),
         Form("Background yield, %d jet", N), 0.3, 0, UpperBound));

      // argument sets for adding
      BackgroundYields.add(*BackgroundJetYields[N]);
      BackgroundExps.add(*BackgroundExpJet[N]);
   }

   // Add pdfs together
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   // Fit!
   RooFitResult *FitResult = FinalModel.fitTo(*ReducedDataSet, Verbose(false), Save(true), SumW2Error(Weighted));

   // Write to DH file
   DataHelper DHFile(DataHelperFile);

   char StateString[1000];
   sprintf(StateString, "%s Jet, %d, Eta range all, Isolation %.2f", JetFlavor.c_str(), EnergyThreshold, Isolation);

   DHFile[StateString]["AlphaL"] = AlphaL.getVal();
   DHFile[StateString]["AlphaLError"] = AlphaL.getError();
   DHFile[StateString]["AlphaR"] = AlphaR.getVal();
   DHFile[StateString]["AlphaRError"] = AlphaR.getError();
   DHFile[StateString]["SigmaL"] = SigmaL.getVal();
   DHFile[StateString]["SigmaLError"] = SigmaL.getError();
   DHFile[StateString]["SigmaR"] = SigmaR.getVal();
   DHFile[StateString]["SigmaRError"] = SigmaR.getError();
   DHFile[StateString]["Mass"] = PeakPosition.getVal();
   DHFile[StateString]["MassError"] = PeakPosition.getError();
   DHFile[StateString]["ZeroJetBinAlphaL"] = ZeroJetBinAlphaL.getVal();
   DHFile[StateString]["ZeroJetBinAlphaLError"] = ZeroJetBinAlphaL.getError();
   DHFile[StateString]["ZeroJetBinAlphaR"] = ZeroJetBinAlphaR.getVal();
   DHFile[StateString]["ZeroJetBinAlphaRError"] = ZeroJetBinAlphaR.getError();
   DHFile[StateString]["ZeroJetBinSigmaL"] = ZeroJetBinSigmaL.getVal();
   DHFile[StateString]["ZeroJetBinSigmaLError"] = ZeroJetBinSigmaL.getError();
   DHFile[StateString]["ZeroJetBinSigmaR"] = ZeroJetBinSigmaR.getVal();
   DHFile[StateString]["ZeroJetBinSigmaRError"] = ZeroJetBinSigmaR.getError();
   DHFile[StateString]["ZeroJetBinMass"] = ZeroJetBinPeakPosition.getVal();
   DHFile[StateString]["ZeroJetBinMassError"] = ZeroJetBinPeakPosition.getError();

   DHFile.SaveToFile(DataHelperFile);

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

vector<vector<double> > ReadSmearingMatrix(string SmearingMatrixFile)
{
   // TODO: Add protections here and there

   vector<vector<double> > Result;

   int Dimension = 0;
   ifstream in(SmearingMatrixFile.c_str());;
   in >> Dimension;

   Result.resize(Dimension);

   for(int i = 0; i < Dimension; i++)
   {
      Result[i].resize(Dimension);
      for(int j = 0; j < Dimension; j++)
         in >> Result[i][j];
   }

   return Result;
}


