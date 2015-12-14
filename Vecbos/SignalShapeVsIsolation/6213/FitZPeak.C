#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
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

using namespace RooFit;

struct FitResult;
void FitZPeak(string RootFile = "Samples/ZJetsAll.root");
FitResult FitZPeak(string RootFile, int JetCount, double Isolation);

struct FitResult
{
   double Mass[2];
   double AlphaL[2];
   double AlphaR[2];
   double SigmaL[2];
   double SigmaR[2];
};

void FitZPeak(string RootFile)
{
   vector<double> Cuts;

   Cuts.push_back(0.0001);
   Cuts.push_back(0.0002);
   Cuts.push_back(0.0004);
   Cuts.push_back(0.0008);
   Cuts.push_back(0.001);
   Cuts.push_back(0.002);
   Cuts.push_back(0.005);
   Cuts.push_back(0.004);
   Cuts.push_back(0.008);
   Cuts.push_back(0.01);
   Cuts.push_back(0.02);
   Cuts.push_back(0.05);
   Cuts.push_back(0.04);
   Cuts.push_back(0.08);
   Cuts.push_back(0.1);
   Cuts.push_back(0.15);
   Cuts.push_back(0.2);
   Cuts.push_back(0.3);
   Cuts.push_back(0.4);
   Cuts.push_back(0.5);
   Cuts.push_back(0.8);
   Cuts.push_back(1);
   Cuts.push_back(2);
   Cuts.push_back(4);
   Cuts.push_back(8);
   Cuts.push_back(999);

   vector<FitResult> Results(Cuts.size());
   
   for(unsigned int i = 0; i < Cuts.size(); i++)
      Results[i] = FitZPeak(RootFile, 1, Cuts[i]);

   TFile F("Output.root", "RECREATE");

   TGraphErrors GAlphaL;
   GAlphaL.SetNameTitle("GAlphaL", "AlphaL");
   TGraphErrors GAlphaR;
   GAlphaR.SetNameTitle("GAlphaR", "AlphaR");
   TGraphErrors GSigmaL;
   GSigmaL.SetNameTitle("GSigmaL", "SigmaL");
   TGraphErrors GSigmaR;
   GSigmaR.SetNameTitle("GSigmaR", "SigmaR");

   for(unsigned int i = 0; i < Cuts.size(); i++)
   {
      GAlphaL.SetPoint(i, Cuts[i], Results[i].AlphaL[0]);
      GAlphaL.SetPointError(i, 0, Results[i].AlphaL[1]);
      GAlphaR.SetPoint(i, Cuts[i], Results[i].AlphaR[0]);
      GAlphaR.SetPointError(i, 0, Results[i].AlphaR[1]);
      GSigmaL.SetPoint(i, Cuts[i], Results[i].SigmaL[0]);
      GSigmaL.SetPointError(i, 0, Results[i].SigmaL[1]);
      GSigmaR.SetPoint(i, Cuts[i], Results[i].SigmaR[0]);
      GSigmaR.SetPointError(i, 0, Results[i].SigmaR[1]);
   }

   GAlphaL.Write();
   GAlphaR.Write();
   GSigmaL.Write();
   GSigmaR.Write();

   PsFileHelper PsFile("ShapeDifference.ps");

   /*
   TCanvas canvas("c", "C");
   GAlphaL.Draw("ap");
   GAlphaL.GetXaxis()->SetTitle("Yo");
   GAlphaL.GetYaxis()->SetTitle("Yo");
   canvas.SetLogx();
   PsFile.AddCanvas(canvas);
   */

   GAlphaL.GetHistogram()->GetXaxis()->SetTitle("Isolation (on both legs)");
   GAlphaL.GetHistogram()->GetYaxis()->SetTitle("AlphaL");
   GAlphaR.GetHistogram()->GetXaxis()->SetTitle("Isolation (on both legs)");
   GAlphaR.GetHistogram()->GetYaxis()->SetTitle("AlphaR");
   GSigmaL.GetHistogram()->GetXaxis()->SetTitle("Isolation (on both legs)");
   GSigmaL.GetHistogram()->GetYaxis()->SetTitle("SigmaL");
   GSigmaR.GetHistogram()->GetXaxis()->SetTitle("Isolation (on both legs)");
   GSigmaR.GetHistogram()->GetYaxis()->SetTitle("SigmaR");
   
   PsFile.AddPlot(GAlphaL, "ap", false, false, false, true);
   PsFile.AddPlot(GAlphaR, "ap", false, false, false, true);
   PsFile.AddPlot(GSigmaL, "ap", false, false, false, true);
   PsFile.AddPlot(GSigmaR, "ap", false, false, false, true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

FitResult FitZPeak(string RootFile, int JetCount, double Isolation)
{
   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NCaloJets("NCaloJet", "Count of jets", 0, 100000);
   RooRealVar Muon1CombinedIsolation("Muon1CombinedIsolation", "Muon1 Combined Isolation", 0, 100000);
   RooRealVar Muon1PT("Muon1PT", "Muon1 PT", 0, 100000);
   RooRealVar Muon2CombinedIsolation("Muon2CombinedIsolation", "Muon2 Combined Isolation", 0, 100000);
   RooRealVar Muon2PT("Muon2PT", "Muon2 PT", 0, 100000);
   RooArgSet TreeVarSet(ZMass, NCaloJets, Muon1CombinedIsolation, Muon1PT, Muon2CombinedIsolation, Muon2PT);

   TFile F(RootFile.c_str());
   TTree *ZTree = (TTree *)F.Get("OutTreeNoIsolation");
   RooDataSet dataset("ZCandidates", "ZCandidates", ZTree, TreeVarSet);

   TCut NumberOfJetCut = Form("NCaloJet >= %d", JetCount);
   TCut IsolationCut = Form("Muon1CombinedIsolation < Muon1PT * %f", Isolation);
   // TCut IsolationCut = Form("Muon1CombinedIsolation < Muon1PT * %f && Muon2CombinedIsolation < Muon2PT * %f",
   //    Isolation, Isolation);
   RooDataSet *ReducedDataSet = (RooDataSet *)dataset.reduce(NumberOfJetCut && IsolationCut);

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 91.000, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.435, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.508, 0.01, 1000000);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.189, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.349, 0.01, 1000000);
   RooCruijff MainZPeak("MainZPeak", "MainZPeak", ZMass, PeakPosition, SigmaL, AlphaR, SigmaL, AlphaL);

   MainZPeak.fitTo(*ReducedDataSet);

   /*
   RooPlot *FinalResult = ZMass.frame(Bins(50), Name("MLL"), Title("Mass of lepton pair"));

   ReducedDataSet->plotOn(FinalResult, MarkerSize(0.9));

   MainZPeak.paramOn(FinalResult, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9));

   MainZPeak.plotOn(FinalResult, LineColor(kRed));

   static int Count = 0;
   Count = Count + 1;

   TCanvas Canvas("c1", "c1", 0, 0, 1024, 768);
   FinalResult->Draw();
   Canvas.SaveAs(Form("FitResult_CaloJet%d.png", Count));
   Canvas.SaveAs(Form("FitResult_CaloJet%d.C", Count));
   Canvas.SaveAs(Form("FitResult_CaloJet%d.eps", Count));
   */

   FitResult Result;

   Result.Mass[0] = PeakPosition.getVal();
   Result.Mass[1] = PeakPosition.getError();
   Result.AlphaL[0] = AlphaL.getVal();
   Result.AlphaL[1] = AlphaL.getError();
   Result.AlphaR[0] = AlphaR.getVal();
   Result.AlphaR[1] = AlphaR.getError();
   Result.SigmaL[0] = SigmaL.getVal();
   Result.SigmaL[1] = SigmaL.getError();
   Result.SigmaR[0] = SigmaL.getVal();
   Result.SigmaR[1] = SigmaL.getError();

   return Result;
}

