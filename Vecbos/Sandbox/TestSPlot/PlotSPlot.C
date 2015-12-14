#include <iostream>
using namespace std;

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "RooRealVar.h"
#include "RooCruijff.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooFitResult.h"

using namespace RooFit;

#include "PlotHelper.h"

#include "MLSPlot.hh"

void PlotSPlot()
{
   RooRealVar ZMass("ZMass", "ZMass", 90, 60, 120, "GeV/c^2");
   RooRealVar NCaloJet("NCaloJet", "NCaloJet", 0, 1000);
   RooRealVar CaloJet1PT("CaloJet1PT", "CaloJet1PT", 0, 100000, "GeV/c");
   RooArgSet TreeVariables(ZMass, NCaloJet, CaloJet1PT);

   string FileName = "Samples/DataAll.root";
   TChain ch("outTree", "outTree");
   ch.AddFile(FileName.c_str());
   RooDataSet DataSet("DataSet", "DataSet", &ch, TreeVariables,
      "NCaloJet > 0");

   RooRealVar Mean("Mean", "Mean", 90, 80, 120);
   RooRealVar Sigma("Sigma", "Sigma", 2.3, 0.001, 100);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.581);
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.4, 0.001, 100);
   RooCruijff SignalShape("SignalShape", "SignalShape", ZMass, Mean,
      Sigma, AlphaR, Sigma, AlphaL);
   RooRealVar SignalYield("SignalYield", "SignalYield", 10, 1, 1000000);

   RooRealVar Exp("Exp", "Exp", -0.009, -10, 0.0);
   RooExponential BackgroundShape("BackgroundShape", "BackgroundShape",
      ZMass, Exp);
   RooRealVar BackgroundYield("BackgroundYield", "BackgroundYield", 10,
      0, 1000000);

   RooArgList Shapes(SignalShape, BackgroundShape);
   RooArgList Yields(SignalYield, BackgroundYield);
   RooAddPdf Model("Model", "Model", Shapes, Yields);

   RooFitResult *NominalFitResult = Model.fitTo(DataSet, Save());

   AlphaL.setConstant(kTRUE);
   AlphaR.setConstant(kTRUE);
   Sigma.setConstant(kTRUE);
   Mean.setConstant(kTRUE);
   Exp.setConstant(kTRUE);

   RooFitResult *YieldOnlyResult = Model.fitTo(DataSet, Save());

   MLSPlot SPlot("SPlot", "SPlot", 40, 0, 200);

   SPlot.fillSPlot(CaloJet1PT, ZMass, DataSet, *YieldOnlyResult,
      Shapes, Yields, Model, true, RooArgSet(ZMass));

   PsFileHelper PsFile("Result.ps");
   PsFile.AddTextPage("Meow");

   PsFile.AddPlot(SPlot, "", true);

   TFile F("Samples/ZJetsAll.root");
   TH1D *ZSampleCaloJet = (TH1D *)F.Get("HCaloJetLeadingPt");
   ZSampleCaloJet->SetLineColor(kRed);
   ZSampleCaloJet->Rebin(5);
   PsFile.AddPlot(ZSampleCaloJet, "", true);

   TCanvas Canvas("Canvas", "Canvas", 0, 0, 1024, 768);
   SPlot.DrawNormalized();
   ZSampleCaloJet->DrawNormalized("same");
   Canvas.SetLogy();
   PsFile.AddCanvas(Canvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}



