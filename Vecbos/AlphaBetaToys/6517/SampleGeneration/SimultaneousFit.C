#include <string>
#include <iostream>
#include <vector>
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
#include "RooFitResult.h"
using namespace RooFit;

#include "PlotHelper.h"
#include "DataHelper.h"

void SimultaneousFit(string RootFile = "Samples/data_w30_unweighted.root",
   int LastJetBin = 4, string JetFlavor = "pf",
   int EnergyThreshold = 30, string DataHelperFile = "Samples/DataAll.dh");
double GetSignalInclusiveCount(int jet, double SignalInclusiveYield, double Alpha, double Beta);
double GetSignalInclusiveError(int jet, double SignalInclusiveYield, double Alpha, double Beta,
   double SignalInclusiveYieldError, double AlphaError, double BetaError);
string GetSignalYieldString(int jet, bool Inclusive = false);

void SimultaneousFit(string RootFile, int LastJetBin, string JetFlavor, int EnergyThreshold,
   string DataHelperFile)
{
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
   RooArgSet TreeVarSet(ZMass, NJet, Category);

   // Import data
   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get("unweighted");
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet);

   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(Form("N%s_%d >= 1 && cat_idx == 1 && Z_mass < 120 && Z_mass > 60", JetFlavor.c_str(), EnergyThreshold));
   double DataSetTotalEntry = ReducedDataSet->sumEntries();

   cout << "Number of entries = " << DataSetTotalEntry << endl;

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
   
   RooRealVar Alpha("Alpha", "Alpha parameter in signal yield", 4.8, 1, 10);
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
         Form("Background exp, %d jet", N), -0.009, -1.0, -0.001));
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
      BackgroundExps.add(*BackgroundExpJet[N-1]);
      BackgroundYields.add(*BackgroundJetYields[N-1]);
   }

   // Add pdfs together
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   // Fit!
   RooFitResult *FitResult = FinalModel.fitTo(*ReducedDataSet, Verbose(false), Save(true));
   
   // Beta.setVal(0);
   // Beta.setConstant(true);
   // FitResult = FinalModel.fitTo(*ReducedDataSet, Verbose(false), Save(true));

   // Generate samples
   TFile F(Form("Samples_%d.root", EnergyThreshold), "RECREATE");

   FitResult->Clone("InitialResult")->Write();

   for(int i = 0; i < 5000; i++)
   {
      RooDataSet *NewDataSet = (RooDataSet *)FinalModel.generate(RooArgSet(ZMass, NJet), (int)DataSetTotalEntry);
      NewDataSet->SetName(Form("Sample_%d", i));
      NewDataSet->Write();
   }

   F.Close();
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


