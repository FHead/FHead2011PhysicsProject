#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TGraphErrors.h"

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
#include "DataHelper.h"

using namespace RooFit;

struct FitResult;
void FitZPeak(string RootFile = "Samples/DataAll.root", string OutputBase = "DataFitTightIsolation",
   string JetFlavor = "Calo", double Isolation = 0.05, int Threshold = 30,
   string DataHelperFile = "Samples/DataAll.dh", int JetCount = 1);
FitResult FitZPeak(string RootFile, PsFileHelper &PsFile, int JetCount, double Isolation, string JetFlavor,
   int Threshold, bool Exclusive = false);

struct FitResult
{
   double Mass[2];
   double AlphaL[2];
   double AlphaR[2];
   double SigmaL[2];
   double SigmaR[2];
};

void FitZPeak(string RootFile, string OutputBase, string JetFlavor, double Isolation, int Threshold,
   string DataHelperFile, int JetCount)
{
   char ThresholdString[] = "";
   sprintf(ThresholdString, "%d", Threshold);
   
   PsFileHelper PsFile(OutputBase + "_" + JetFlavor + "_" + ThresholdString + ".ps");
   PsFile.AddTextPage("Fit Z peak floating everything");

   FitResult Result = FitZPeak(RootFile, PsFile, JetCount, Isolation, JetFlavor, Threshold, false);
   FitResult ResultZeroJetBin = FitZPeak(RootFile, PsFile, 0, Isolation, JetFlavor, Threshold, true);

   DataHelper DHFile(DataHelperFile);

   char state[1000] = "";
   if(JetCount == 1)
      sprintf(state, "%s Jet, %d, Eta range all, Isolation %.2f",
         JetFlavor.c_str(), Threshold, Isolation);
   else
      sprintf(state, "%s Jet, %d, Jet Count %d, Eta range all, Isolation %.2f",
         JetFlavor.c_str(), Threshold, JetCount, Isolation);

   DHFile[state]["Mass"] = Result.Mass[0];
   DHFile[state]["MassError"] = Result.Mass[1];
   DHFile[state]["AlphaL"] = Result.AlphaL[0];
   DHFile[state]["AlphaLError"] = Result.AlphaL[1];
   DHFile[state]["AlphaR"] = Result.AlphaR[0];
   DHFile[state]["AlphaRError"] = Result.AlphaR[1];
   DHFile[state]["SigmaL"] = Result.SigmaL[0];
   DHFile[state]["SigmaLError"] = Result.SigmaL[1];
   DHFile[state]["SigmaR"] = Result.SigmaR[0];
   DHFile[state]["SigmaRError"] = Result.SigmaR[1];

   sprintf(state, "%s Jet, %d, Eta range all, Isolation %.2f",
      JetFlavor.c_str(), Threshold, Isolation);

   DHFile[state]["ZeroJetBinMass"] = ResultZeroJetBin.Mass[0];
   DHFile[state]["ZeroJetBinMassError"] = ResultZeroJetBin.Mass[1];
   DHFile[state]["ZeroJetBinAlphaL"] = ResultZeroJetBin.AlphaL[0];
   DHFile[state]["ZeroJetBinAlphaLError"] = ResultZeroJetBin.AlphaL[1];
   DHFile[state]["ZeroJetBinAlphaR"] = ResultZeroJetBin.AlphaR[0];
   DHFile[state]["ZeroJetBinAlphaRError"] = ResultZeroJetBin.AlphaR[1];
   DHFile[state]["ZeroJetBinSigmaL"] = ResultZeroJetBin.SigmaL[0];
   DHFile[state]["ZeroJetBinSigmaLError"] = ResultZeroJetBin.SigmaL[1];
   DHFile[state]["ZeroJetBinSigmaR"] = ResultZeroJetBin.SigmaR[0];
   DHFile[state]["ZeroJetBinSigmaRError"] = ResultZeroJetBin.SigmaR[1];

   DHFile.SaveToFile(DataHelperFile);

   cout << "Mass:" << Result.Mass[0] << " " << Result.Mass[1] << endl;
   cout << "AlphaL: " << Result.AlphaL[0] << " " << Result.AlphaL[1] << endl;
   cout << "AlphaR: " << Result.AlphaR[0] << " " << Result.AlphaR[1] << endl;
   cout << "SigmaL: " << Result.SigmaL[0] << " " << Result.SigmaL[1] << endl;
   cout << "SigmaR: " << Result.SigmaR[0] << " " << Result.SigmaR[1] << endl;

   TFile F((OutputBase + "_" + JetFlavor + "_" + ThresholdString + ".root").c_str(), "RECREATE");

   TH2D ResultSummary("ResultSummary", "Summary of results", 5, -0.5, 4.5, 1, -0.5, 0.5);

   ResultSummary.GetXaxis()->SetBinLabel(1, "Mass");
   ResultSummary.GetXaxis()->SetBinLabel(2, "AlphaL");
   ResultSummary.GetXaxis()->SetBinLabel(3, "AlphaR");
   ResultSummary.GetXaxis()->SetBinLabel(4, "SigmaL");
   ResultSummary.GetXaxis()->SetBinLabel(5, "SigmaR");

   ResultSummary.SetBinContent(1, 1, Result.Mass[0]);
   ResultSummary.SetBinContent(2, 1, Result.AlphaL[0]);
   ResultSummary.SetBinContent(3, 1, Result.AlphaR[0]);
   ResultSummary.SetBinContent(4, 1, Result.SigmaL[0]);
   ResultSummary.SetBinContent(5, 1, Result.SigmaR[0]);
   
   ResultSummary.SetBinError(1, 1, Result.Mass[1]);
   ResultSummary.SetBinError(2, 1, Result.AlphaL[1]);
   ResultSummary.SetBinError(3, 1, Result.AlphaR[1]);
   ResultSummary.SetBinError(4, 1, Result.SigmaL[1]);
   ResultSummary.SetBinError(5, 1, Result.SigmaR[1]);

   ResultSummary.Write();

   F.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

FitResult FitZPeak(string RootFile, PsFileHelper &PsFile, int JetCount, double Isolation, string JetFlavor,
   int Threshold, bool Exclusive)
{
   RooRealVar ZMass("Z_mass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NCaloJets(Form("N%s_%d", JetFlavor.c_str(), Threshold), "Count of jets", 0, 100000);
   RooRealVar Muon1Isolation("Iso_pf_relpt", "Muon1 isolation", 0, 100000);
   RooRealVar Category("cat_idx", "category", -10, 10);
   RooArgSet TreeVarSet(ZMass, NCaloJets, Muon1Isolation, Category);

   TFile F(RootFile.c_str());
   TTree *ZTree = (TTree *)F.Get("noweight");
   RooDataSet dataset("ZCandidates", "ZCandidates", ZTree, TreeVarSet);

   TCut NumberOfJetCut = "";
   if(Exclusive == false)
      NumberOfJetCut = Form("N%s_%d >= %d", JetFlavor.c_str(), Threshold, JetCount);
   else
      NumberOfJetCut = Form("N%s_%d == %d", JetFlavor.c_str(), Threshold, JetCount);

   TCut IsolationCut = Form("Iso_pf_relpt < %f", Isolation);
   TCut CategoryCut = "cat_idx == 1";
   TCut ZMassRange = "Z_mass > 60 && Z_mass < 120";
   RooDataSet *ReducedDataSet = (RooDataSet *)dataset.reduce(NumberOfJetCut && IsolationCut
      && CategoryCut && ZMassRange);

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 91.000, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.435, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.508, 0.01, 1000000);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.189, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.349, 0.01, 1000000);
   RooCruijff MainZPeak("MainZPeak", "MainZPeak", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);

   cout << "!" << endl;

   MainZPeak.fitTo(*ReducedDataSet);
   
   cout << "!!" << endl;

   RooPlot *Parameters = ZMass.frame(Bins(50), Name("MLL"), Title("Mass of lepton pair"));
   MainZPeak.paramOn(Parameters, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9));
   PsFile.AddPlot(Parameters, "", false);

   RooPlot *FinalResult = ZMass.frame(Bins(50), Name("MLL"), Title("Mass of lepton pair"));
   ReducedDataSet->plotOn(FinalResult, MarkerSize(0.9));
   MainZPeak.plotOn(FinalResult, LineColor(kRed));
   PsFile.AddPlot(FinalResult, "", false);

   // TCanvas Canvas("Canvas", "Canvas", 0, 0, 1024, 768);
   // FinalResult->Draw();
   // Canvas.SaveAs("DataTightIsolationFit.png");
   // Canvas.SaveAs("DataTightIsolationFit.C");
   // Canvas.SaveAs("DataTightIsolationFit.eps");

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

