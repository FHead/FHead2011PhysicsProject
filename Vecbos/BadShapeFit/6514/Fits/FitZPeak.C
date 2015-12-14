#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"

#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooArgSet.h"
#include "RooRealVar.h"
#include "RooLorentzian.h"
#include "RooVoigtian.h"
#include "RooAddPdf.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooPlot.h"
#include "RooBifurGauss.h"
#include "RooCruijff.h"
#include "RooExtendPdf.h"
#include "RooCBShape.h"
#include "RooReverseLandau.h"

using namespace RooFit;

void FitZPeak(string OutputFileName = "3000.root", int Start = 0, int End = 10, double AlphaLMultiplier = 1,
      double AlphaRMultiplier = 1, double SigmaLMultiplier = 1, double SigmaRMultiplier = 1);
RooFitResult *FitZPeak_Cruijff(string Rootfile, double AlphaLValue, double AlphaRValue, double SigmaLValue,
   double SigmaRValue);

void FitZPeak(string OutputFileName, int Start, int End, double AlphaLMultiplier, double AlphaRMultiplier,
   double SigmaLMultiplier, double SigmaRMultiplier)
{
   TFile OutputFile(OutputFileName.c_str(), "Update");

   double AlphaL = 0.49 * AlphaLMultiplier;
   double AlphaR = 0.45 * AlphaRMultiplier;
   double SigmaL = 2.50 * SigmaLMultiplier;
   double SigmaR = 2.05 * SigmaRMultiplier;

   for(int i = Start; i <= End; i++)
   {
      char InputName[1024] = "";
      sprintf(InputName, "Samples/Signal_1_%d.root", i);

      FitZPeak_Cruijff(InputName, AlphaL, AlphaR, SigmaL, SigmaR)->Clone(Form("Result%d", i))->Write();
   }

   OutputFile.Close();
}

RooFitResult *FitZPeak_Cruijff(string RootFile, double AlphaLValue, double AlphaRValue, double SigmaLValue,
   double SigmaRValue)
{
   RooRealVar mll("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooArgSet TreeVarSet(mll);

   TChain ZTree("MllTree", "MllTree");
   ZTree.AddFile(RootFile.c_str());
   RooDataSet dataset("ZCandidates", "ZCandidates", &ZTree, TreeVarSet);

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.97, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", AlphaRValue);
   RooRealVar AlphaL("AlphaL", "AlphaL", AlphaLValue);
   RooRealVar SigmaR("SigmaR", "SigmaR", SigmaRValue);
   RooRealVar SigmaL("SigmaL", "SigmaL", SigmaLValue);
   RooCruijff MainZPeak("MainZPeak", "MainZPeak", mll, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooRealVar SignalYield("SignalYield", "number of signal events in signalRange",500, 0., 10000);

   RooRealVar BackgroundExp("BackgroundExp", "Background exp", -0.009, -10.0, 0.0);
   RooExponential Background("Background", "Background", mll, BackgroundExp);
   RooRealVar BackgroundYield("BackgroundYield", "Background Yield", 100, 0, 1000000);

   RooArgList Distributions(MainZPeak, Background);
   RooArgList Yields(SignalYield, BackgroundYield);
   RooAddPdf TotalPDF("TotalPDF", "Fit function!", Distributions, Yields);

   RooFitResult *fitresult = TotalPDF.fitTo(dataset, Save(), Extended(true));

   return fitresult;
}



