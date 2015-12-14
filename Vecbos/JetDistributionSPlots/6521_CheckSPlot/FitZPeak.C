#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"

#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooRealVar.h"
#include "RooLorentzian.h"
#include "RooAddPdf.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooCruijff.h"
#include "RooPlot.h"

#include "PlotHelper.h"

using namespace RooFit;

struct FitResult;
FitResult FitZPeak(string RootFile = "Samples/SFile.root");

struct FitResult
{
   double Mass[2];
   double AlphaL[2];
   double AlphaR[2];
   double SigmaL[2];
   double SigmaR[2];
};

FitResult FitZPeak(string RootFile)
{
   RooRealVar ZMass("Z_mass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJets("Npf_30", "Count of jets", 0, 100000);
   RooRealVar Weight("SignalInclusiveYield0Jet_sw", "Weight", -1000000, 1000000);
   RooArgSet TreeVarSet(ZMass, NJets, Weight);

   TFile F(RootFile.c_str());
   TTree *ZTree = (TTree *)F.Get("SWeightTree");
   RooDataSet dataset("ZCandidates", "ZCandidates", ZTree, TreeVarSet, "", "SignalInclusiveYield0Jet_sw");

   RooDataSet *ReducedDataSet = (RooDataSet *)dataset.reduce("Z_mass < 120 && Z_mass > 60 && Npf_30 > 0");

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.9304, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.44076, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.521317);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.1059, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.0947, 0.01, 1000000);
   RooCruijff MainZPeak("MainZPeak", "MainZPeak", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);

   MainZPeak.fitTo(*ReducedDataSet, SumW2Error(kTRUE));

   RooPlot *FinalResult = ZMass.frame(Bins(50), Name("MLL"), Title("Mass of lepton pair"));

   ReducedDataSet->plotOn(FinalResult, MarkerSize(0.9));

   MainZPeak.paramOn(FinalResult, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9));

   MainZPeak.plotOn(FinalResult, LineColor(kRed));

   TCanvas Canvas("c1", "c1", 0, 0, 1024, 768);
   FinalResult->Draw();
   // Canvas.SaveAs(Form("FitResult_%sJet%d.png", JetFlavor.c_str(), JetCount));
   // Canvas.SaveAs(Form("FitResult_%sJet%d.C", JetFlavor.c_str(), JetCount));
   // Canvas.SaveAs(Form("FitResult_%sJet%d.eps", JetFlavor.c_str(), JetCount));

   PsFileHelper PsFile("Result.ps");
   PsFile.AddCanvas(Canvas);
   PsFile.Close();

   FitResult Result;

   Result.Mass[0] = PeakPosition.getVal();
   Result.Mass[1] = PeakPosition.getError();
   Result.AlphaL[0] = AlphaL.getVal();
   Result.AlphaL[1] = AlphaL.getError();
   Result.AlphaR[0] = AlphaR.getVal();
   Result.AlphaR[1] = AlphaR.getError();
   Result.SigmaL[0] = SigmaL.getVal();
   Result.SigmaL[1] = SigmaL.getError();
   Result.SigmaR[0] = SigmaR.getVal();
   Result.SigmaR[1] = SigmaR.getError();

   return Result;
}

