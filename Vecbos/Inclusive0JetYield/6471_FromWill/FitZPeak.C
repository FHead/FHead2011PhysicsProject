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
void FitZPeak(string RootFile = "Samples/DataAll.root", string OutputBase = "AllInclusive",
   string JetFlavor = "pf", double Isolation = 9999.0, int Threshold = 30,
   string DataHelperFile = "Samples/DataAll.dh");
FitResult FitZPeak(string RootFile, PsFileHelper &PsFile, int JetCount, double Isolation, string JetFlavor,
   int Threshold, double AlphaLValue);

struct FitResult
{
   double Mass[2];
   double AlphaL[2];
   double AlphaR[2];
   double SigmaL[2];
   double SigmaR[2];
   double Yield[2];
   double BackgroundYield[2];
};

void FitZPeak(string RootFile, string OutputBase, string JetFlavor, double Isolation, int Threshold,
   string DataHelperFile)
{
   char ThresholdString[] = "";
   sprintf(ThresholdString, "%d", Threshold);
   
   int JetCount = 0;
   
   PsFileHelper PsFile(OutputBase + "_" + JetFlavor + "_" + ThresholdString + ".ps");
   PsFile.AddTextPage("Find all-inclusive signal yield");

   DataHelper DHFile(DataHelperFile);

   char state[1000] = "";
   sprintf(state, "%s Jet, %d, Jet Count 0, Eta range all, Isolation 0.05", JetFlavor.c_str(), Threshold);

   if(DHFile.Exist(state) == false)
   {
      cout << "Please fit with tight isolation first!!" << endl;
      return;
   }
   if(DHFile[state].Exist("AlphaL") == false)
   {
      cout << "Please fit with tight isolation first!!" << endl;
      return;
   }

   double AlphaLValue = DHFile[state]["AlphaL"].GetDouble();

   FitResult Result = FitZPeak(RootFile, PsFile, JetCount, Isolation, JetFlavor, Threshold, AlphaLValue);

   sprintf(state, "%s Jet, %d, Jet Count 0, Eta range all, Isolation all", JetFlavor.c_str(), Threshold);
   
   DHFile[state]["SimpleIncluisveFitMass"] = Result.Mass[0];
   DHFile[state]["SimpleInclusiveFitMassError"] = Result.Mass[1];
   DHFile[state]["SimpleIncluisveFitAlphaL"] = Result.AlphaL[0];
   DHFile[state]["SimpleIncluisveFitAlphaLError"] = Result.AlphaL[1];
   DHFile[state]["SimpleIncluisveFitAlphaR"] = Result.AlphaR[0];
   DHFile[state]["SimpleIncluisveFitAlphaRError"] = Result.AlphaR[1];
   DHFile[state]["SimpleIncluisveFitSigmaL"] = Result.SigmaL[0];
   DHFile[state]["SimpleIncluisveFitSigmaLError"] = Result.SigmaL[1];
   DHFile[state]["SimpleIncluisveFitSigmaR"] = Result.SigmaR[0];
   DHFile[state]["SimpleIncluisveFitSigmaRError"] = Result.SigmaR[1];
   DHFile[state]["SimpleIncluisveFitSignalYield"] = Result.Yield[0];
   DHFile[state]["SimpleIncluisveFitSignalYieldError"] = Result.Yield[1];
   DHFile[state]["SimpleInclusiveFitBackgroundYield"] = Result.BackgroundYield[0];
   DHFile[state]["SimpleInclusiveFitBackgroundYieldError"] = Result.BackgroundYield[1];

   DHFile.SaveToFile(DataHelperFile);

   cout << "Mass:" << Result.Mass[0] << " " << Result.Mass[1] << endl;
   cout << "AlphaL: " << Result.AlphaL[0] << " " << Result.AlphaL[1] << endl;
   cout << "AlphaR: " << Result.AlphaR[0] << " " << Result.AlphaR[1] << endl;
   cout << "SigmaL: " << Result.SigmaL[0] << " " << Result.SigmaL[1] << endl;
   cout << "SigmaR: " << Result.SigmaR[0] << " " << Result.SigmaR[1] << endl;
   cout << "Signal Yield: " << Result.Yield[0] << " " << Result.Yield[1] << endl;
   cout << "Background Yield: " << Result.BackgroundYield[0] << " " << Result.BackgroundYield[1] << endl;

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
   int Threshold, double AlphaLValue)
{
   RooRealVar ZMass("Z_mass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NCaloJets(Form("N%s_%d", JetFlavor.c_str(), Threshold), "Count of jets", 0, 100000);
   RooRealVar Muon1Isolation("Iso_pf_relpt", "Muon1 isolation", 0, 100000);
   RooRealVar Category("cat_idx", "category", -10, 10);
   RooArgSet TreeVarSet(ZMass, NCaloJets, Muon1Isolation, Category);

   TFile F(RootFile.c_str());
   TTree *ZTree = (TTree *)F.Get("noweight");
   RooDataSet dataset("ZCandidates", "ZCandidates", ZTree, TreeVarSet);

   TCut NumberOfJetCut = Form("N%s_%d >= %d", JetFlavor.c_str(), Threshold, JetCount);
   TCut IsolationCut = Form("Iso_pf_relpt < %f", Isolation);
   TCut CategoryCut = "cat_idx == 1";
   TCut ZMassRange = "Z_mass > 60 && Z_mass < 120";
   RooDataSet *ReducedDataSet = (RooDataSet *)dataset.reduce(NumberOfJetCut && IsolationCut
      && CategoryCut && ZMassRange);

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 91.000, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.435, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", AlphaLValue);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.189, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.349, 0.01, 1000000);
   RooCruijff MainZPeak("MainZPeak", "MainZPeak", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooRealVar SignalYield("SignalYield", "Signal yield", 5000, 0, 100000);

   RooRealVar BackgroundExp("BackgroundExp", "Background exp", -0.009, -10, 10);
   RooExponential BackgroundShape("BackgroundShape", "Background shape", ZMass, BackgroundExp);
   RooRealVar BackgroundYield("BackgroundYield", "Backgroudn yield", 1, 0, 100000);

   RooArgSet Shapes(MainZPeak, BackgroundShape);
   RooArgSet Yields(SignalYield, BackgroundYield);
   RooAddPdf FinalModel("FinalModel", "FinalModel", Shapes, Yields);

   cout << "!" << endl;

   FinalModel.fitTo(*ReducedDataSet);
   
   cout << "!!" << endl;

   RooPlot *Parameters = ZMass.frame(Bins(50), Name("MLL"), Title("Mass of lepton pair"));
   FinalModel.paramOn(Parameters, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9));
   PsFile.AddPlot(Parameters, "", false);

   RooPlot *FinalResult = ZMass.frame(Bins(50), Name("MLL"), Title("Mass of lepton pair"));
   ReducedDataSet->plotOn(FinalResult, MarkerSize(0.9));
   FinalModel.plotOn(FinalResult, LineColor(kBlue));
   FinalModel.plotOn(FinalResult, LineColor(kBlue), Components(BackgroundShape));
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
   Result.Yield[0] = SignalYield.getVal();
   Result.Yield[1] = SignalYield.getError();
   Result.BackgroundYield[0] = BackgroundYield.getVal();
   Result.BackgroundYield[1] = BackgroundYield.getError();

   return Result;
}

