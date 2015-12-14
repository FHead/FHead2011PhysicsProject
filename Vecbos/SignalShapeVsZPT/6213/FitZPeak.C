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
FitResult FitZPeak(string RootFile, int JetCount, double ZPTMin, double ZPTMax, PsFileHelper &PsFile);

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
   vector<double> ZPTs;

   ZPTs.push_back(0);
   ZPTs.push_back(5);
   ZPTs.push_back(10);
   ZPTs.push_back(15);
   ZPTs.push_back(20);
   ZPTs.push_back(25);
   ZPTs.push_back(30);
   ZPTs.push_back(35);
   ZPTs.push_back(40);
   ZPTs.push_back(45);
   ZPTs.push_back(50);
   ZPTs.push_back(55);
   ZPTs.push_back(60);
   ZPTs.push_back(65);
   ZPTs.push_back(70);
   ZPTs.push_back(75);
   ZPTs.push_back(80);
   ZPTs.push_back(85);
   ZPTs.push_back(90);
   ZPTs.push_back(95);
   ZPTs.push_back(100);
   ZPTs.push_back(110);
   ZPTs.push_back(120);
   ZPTs.push_back(130);
   ZPTs.push_back(140);
   ZPTs.push_back(150);
   ZPTs.push_back(160);

   vector<FitResult> Results(ZPTs.size());

   PsFileHelper FitPlots("FitPlots.ps");
   FitPlots.AddTextPage("Fits!");

   for(unsigned int i = 0; i < ZPTs.size() - 1; i++)
      Results[i] = FitZPeak(RootFile, 1, ZPTs[i], ZPTs[i+1], FitPlots);

   FitPlots.AddTimeStampPage();
   FitPlots.Close();

   TFile F("Output.root", "RECREATE");

   TGraphErrors GAlphaL;
   GAlphaL.SetNameTitle("GAlphaL", "AlphaL");
   TGraphErrors GAlphaR;
   GAlphaR.SetNameTitle("GAlphaR", "AlphaR");
   TGraphErrors GSigmaL;
   GSigmaL.SetNameTitle("GSigmaL", "SigmaL");
   TGraphErrors GSigmaR;
   GSigmaR.SetNameTitle("GSigmaR", "SigmaR");
   TGraphErrors GMass;
   GMass.SetNameTitle("GMass", "Mass");

   for(unsigned int i = 0; i < ZPTs.size() - 1; i++)
   {
      GAlphaL.SetPoint(i, (ZPTs[i] + ZPTs[i+1]) / 2, Results[i].AlphaL[0]);
      GAlphaL.SetPointError(i, (ZPTs[i+1] - ZPTs[i]) / 2, Results[i].AlphaL[1]);
      GAlphaR.SetPoint(i, (ZPTs[i] + ZPTs[i+1]) / 2, Results[i].AlphaR[0]);
      GAlphaR.SetPointError(i, (ZPTs[i+1] - ZPTs[i]) / 2, Results[i].AlphaR[1]);
      GSigmaL.SetPoint(i, (ZPTs[i] + ZPTs[i+1]) / 2, Results[i].SigmaL[0]);
      GSigmaL.SetPointError(i, (ZPTs[i+1] - ZPTs[i]) / 2, Results[i].SigmaL[1]);
      GSigmaR.SetPoint(i, (ZPTs[i] + ZPTs[i+1]) / 2, Results[i].SigmaR[0]);
      GSigmaR.SetPointError(i, (ZPTs[i+1] - ZPTs[i]) / 2, Results[i].SigmaR[1]);
      GMass.SetPoint(i, (ZPTs[i] + ZPTs[i+1]) / 2, Results[i].Mass[0]);
      GMass.SetPointError(i, (ZPTs[i+1] - ZPTs[i]) / 2, Results[i].Mass[1]);
   }

   GAlphaL.Write();
   GAlphaR.Write();
   GSigmaL.Write();
   GSigmaR.Write();
   GMass.Write();

   PsFileHelper PsFile("ShapeDifference.ps");

   /*
   TCanvas canvas("c", "C");
   GAlphaL.Draw("ap");
   GAlphaL.GetXaxis()->SetTitle("Yo");
   GAlphaL.GetYaxis()->SetTitle("Yo");
   canvas.SetLogx();
   PsFile.AddCanvas(canvas);
   */

   GAlphaL.GetHistogram()->GetXaxis()->SetTitle("Z PT");
   GAlphaL.GetHistogram()->GetYaxis()->SetTitle("AlphaL");
   GAlphaR.GetHistogram()->GetXaxis()->SetTitle("Z PT");
   GAlphaR.GetHistogram()->GetYaxis()->SetTitle("AlphaR");
   GSigmaL.GetHistogram()->GetXaxis()->SetTitle("Z PT");
   GSigmaL.GetHistogram()->GetYaxis()->SetTitle("SigmaL");
   GSigmaR.GetHistogram()->GetXaxis()->SetTitle("Z PT");
   GSigmaR.GetHistogram()->GetYaxis()->SetTitle("SigmaR");
   GMass.GetHistogram()->GetXaxis()->SetTitle("Z PT");
   GMass.GetHistogram()->GetYaxis()->SetTitle("Mass");
   
   PsFile.AddPlot(GAlphaL, "ap", false, false, false, false);
   PsFile.AddPlot(GAlphaR, "ap", false, false, false, false);
   PsFile.AddPlot(GSigmaL, "ap", false, false, false, false);
   PsFile.AddPlot(GSigmaR, "ap", false, false, false, false);
   PsFile.AddPlot(GMass, "ap", false, false, false, false);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

FitResult FitZPeak(string RootFile, int JetCount, double ZPTMin, double ZPTMax, PsFileHelper &PsFile)
{
   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NCaloJets("NCaloJet", "Count of jets", 0, 100000);
   RooRealVar Muon1CombinedIsolation("Muon1CombinedIsolation", "Muon1 Combined Isolation", 0, 100000);
   RooRealVar Muon1PT("Muon1PT", "Muon1 PT", 0, 100000);
   RooRealVar Muon2CombinedIsolation("Muon2CombinedIsolation", "Muon2 Combined Isolation", 0, 100000);
   RooRealVar Muon2PT("Muon2PT", "Muon2 PT", 0, 100000);
   RooRealVar ZPT("ZPT", "Z PT", 0, 100000);
   RooArgSet TreeVarSet(ZMass, NCaloJets, Muon1CombinedIsolation, Muon1PT, Muon2CombinedIsolation, Muon2PT, ZPT);

   TFile F(RootFile.c_str());
   TTree *ZTree = (TTree *)F.Get("outTree");
   RooDataSet dataset("ZCandidates", "ZCandidates", ZTree, TreeVarSet);

   TCut NumberOfJetCut = Form("NCaloJet >= %d", JetCount);
   TCut IsolationCut = Form("Muon1CombinedIsolation < Muon1PT * 0.3");
   TCut ZPTCut = Form("ZPT < %f && ZPT > %f", ZPTMax, ZPTMin);
   RooDataSet *ReducedDataSet = (RooDataSet *)dataset.reduce(NumberOfJetCut && IsolationCut && ZPTCut);

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 91.000, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.435, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.508, 0.01, 1000000);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.189, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.349, 0.01, 1000000);
   RooCruijff MainZPeak("MainZPeak", "MainZPeak", ZMass, PeakPosition, SigmaL, AlphaR, SigmaL, AlphaL);

   MainZPeak.fitTo(*ReducedDataSet);

   RooPlot *FinalResult = ZMass.frame(Bins(50), Name("MLL"),
      Title(Form("Mass of lepton pair, Z pt = %f - %f", ZPTMin, ZPTMax)));

   ReducedDataSet->plotOn(FinalResult, MarkerSize(0.9));

   MainZPeak.paramOn(FinalResult, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9));

   MainZPeak.plotOn(FinalResult, LineColor(kRed));

   static int Count = 0;
   Count = Count + 1;

   TCanvas Canvas("c1", "c1", 0, 0, 1024, 768);
   FinalResult->Draw();

   PsFile.AddCanvas(Canvas);

   /*
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



