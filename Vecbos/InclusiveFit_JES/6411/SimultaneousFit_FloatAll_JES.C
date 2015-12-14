#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH2D.h"
#include "TLegend.h"

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
using namespace RooFit;

#include "PlotHelper.h"

struct FitResult;
void SimultaneousFit_FloatAll_JES();
void FitAndAddPlot(PsFileHelper &PsFile, string JetFlavor = "Calo", string JetEnergy = "30",
   double AlphaLValue = 0.485, int LastJetBin = 4);
FitResult SimultaneousFit_FloatAll(string RootFile = "Samples/DataAll.root", int LastJetBin = 4,
   string JetFlavor = "PF", string JetAppendix = "20", double AlphaLValue = 0.485);

struct FitResult
{
   vector<double> SignalInclusiveYield;
   vector<double> SignalInclusiveYieldError;
   vector<double> BackgroundExclusiveYield;
   vector<double> BackgroundExclusiveYieldError;
};

void SimultaneousFit_FloatAll_JES()
{
   PsFileHelper PsFile("JES.ps");

   PsFile.AddTextPage("");

   FitAndAddPlot(PsFile, "Calo", "", 0.522, 5);
   FitAndAddPlot(PsFile, "PF", "", 0.488, 4);
   // FitAndAddPlot(PsFile, "Track", "", 0.493, 4);
   // FitAndAddPlot(PsFile, "UncorrectedCalo", "", 0.510, 4);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

void FitAndAddPlot(PsFileHelper &PsFile, string JetFlavor, string JetEnergy, double AlphaLValue, int LastJetBin)
{
   FitResult Nominal = SimultaneousFit_FloatAll("Samples/DataAll.root", LastJetBin, JetFlavor,
      JetEnergy, AlphaLValue);
   FitResult High = SimultaneousFit_FloatAll("Samples/DataAll.root", LastJetBin, JetFlavor,
      "HighThreshold" + JetEnergy, AlphaLValue);
   FitResult Low = SimultaneousFit_FloatAll("Samples/DataAll.root", LastJetBin, JetFlavor,
      "LowThreshold" + JetEnergy, AlphaLValue);
   FitResult HighEta = SimultaneousFit_FloatAll("Samples/DataAll.root", LastJetBin, JetFlavor,
      "HighEtaThreshold" + JetEnergy, AlphaLValue);
   FitResult LowEta = SimultaneousFit_FloatAll("Samples/DataAll.root", LastJetBin, JetFlavor,
      "LowEtaThreshold" + JetEnergy, AlphaLValue);
   
   TH2D SummaryPlot("SummaryPlot", Form("Summary plot - %s jet %s GeV/c", JetFlavor.c_str(), JetEnergy.c_str()),
      LastJetBin, -0.5, LastJetBin - 0.5, 5, -0.5, 4.5);
   
   SummaryPlot.GetYaxis()->SetBinLabel(1, "Low Eta");
   SummaryPlot.GetYaxis()->SetBinLabel(2, "High Eta");
   SummaryPlot.GetYaxis()->SetBinLabel(3, "Low");
   SummaryPlot.GetYaxis()->SetBinLabel(4, "High");
   SummaryPlot.GetYaxis()->SetBinLabel(5, "Normal");
   
   for(int N = 1; N <= LastJetBin; N++)
   {
      SummaryPlot.GetXaxis()->SetBinLabel(N, Form("%d", N));

      SummaryPlot.SetBinContent(N, 5, Nominal.SignalInclusiveYield[N-1]);
      SummaryPlot.SetBinError(N, 5, Nominal.SignalInclusiveYieldError[N-1]);
      SummaryPlot.SetBinContent(N, 4, High.SignalInclusiveYield[N-1]);
      SummaryPlot.SetBinError(N, 4, High.SignalInclusiveYieldError[N-1]);
      SummaryPlot.SetBinContent(N, 3, Low.SignalInclusiveYield[N-1]);
      SummaryPlot.SetBinError(N, 3, Low.SignalInclusiveYieldError[N-1]);
      SummaryPlot.SetBinContent(N, 2, HighEta.SignalInclusiveYield[N-1]);
      SummaryPlot.SetBinError(N, 2, HighEta.SignalInclusiveYieldError[N-1]);
      SummaryPlot.SetBinContent(N, 1, LowEta.SignalInclusiveYield[N-1]);
      SummaryPlot.SetBinError(N, 1, LowEta.SignalInclusiveYieldError[N-1]);
   }
   
   SummaryPlot.SetStats(0);
   SummaryPlot.SetMarkerSize(2);

   TCanvas SummaryCanvas("SummaryCanvas", "SummaryCanvas", 0, 0, 1024, 768);
   SummaryPlot.Draw("text0 error");
   SummaryCanvas.SaveAs(Form("%sJet%s_JES.png", JetFlavor.c_str(), JetEnergy.c_str()));
   SummaryCanvas.SaveAs(Form("%sJet%s_JES.C", JetFlavor.c_str(), JetEnergy.c_str()));
   SummaryCanvas.SaveAs(Form("%sJet%s_JES.eps", JetFlavor.c_str(), JetEnergy.c_str()));

   PsFile.AddPlot(SummaryPlot, "text0 error");
   
   TGraphAsymmErrors SummaryGraphOverall;
   SummaryGraphOverall.SetName("SummaryGraphOverall");
   SummaryGraphOverall.SetTitle(Form("Summary graph (overall) - %s jet %s GeV/c",
      JetFlavor.c_str(), JetEnergy.c_str()));

   TGraphAsymmErrors SummaryGraphEta;
   SummaryGraphEta.SetName("SummaryGraphEta");
   SummaryGraphEta.SetTitle(Form("Summary graph (eta dependent) - %s jet %s GeV/c",
      JetFlavor.c_str(), JetEnergy.c_str()));

   TGraphAsymmErrors SummaryGraphOverallAndEta;
   SummaryGraphOverallAndEta.SetName("SummaryGraphOverallAndEta");
   SummaryGraphOverallAndEta.SetTitle(Form("Jet energy scale uncertainty band - %s jet", JetFlavor.c_str()));
   SummaryGraphOverallAndEta.GetXaxis()->SetTitle("Inclusive Jet Count");
   SummaryGraphOverallAndEta.GetYaxis()->SetTitle("Yield");

   for(int N = 1; N <= LastJetBin; N++)
   {
      SummaryGraphOverall.SetPoint(N - 1, N, Nominal.SignalInclusiveYield[N-1]);
      SummaryGraphOverall.SetPointError(N - 1, 0.5, 0.5,
         Low.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1],
         Nominal.SignalInclusiveYield[N-1] - High.SignalInclusiveYield[N-1]);

      SummaryGraphEta.SetPoint(N - 1, N, Nominal.SignalInclusiveYield[N-1]);
      SummaryGraphEta.SetPointError(N - 1, 0.5, 0.5,
         LowEta.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1],
         Nominal.SignalInclusiveYield[N-1] - HighEta.SignalInclusiveYield[N-1]);
      
      SummaryGraphOverallAndEta.SetPoint(N - 1, N, Nominal.SignalInclusiveYield[N-1]);
      SummaryGraphOverallAndEta.SetPointError(N - 1, 0.5, 0.5,
         sqrt((LowEta.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])
            * (LowEta.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])
            + (Low.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])
            * (Low.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])),
         sqrt((Nominal.SignalInclusiveYield[N-1] - HighEta.SignalInclusiveYield[N-1])
            * (Nominal.SignalInclusiveYield[N-1] - HighEta.SignalInclusiveYield[N-1])
            + (Nominal.SignalInclusiveYield[N-1] - High.SignalInclusiveYield[N-1])
            * (Nominal.SignalInclusiveYield[N-1] - High.SignalInclusiveYield[N-1])));
   }

   SummaryGraphOverall.SetFillColor(kBlue);
   SummaryGraphEta.SetFillColor(kBlue);
   SummaryGraphOverallAndEta.SetFillColor(kRed);

   TCanvas Canvas("Canvas", "Canvas", 0, 0, 1024, 768);

   SummaryGraphOverallAndEta.Draw("a3");
   // SummaryGraphOverall.Draw("p3");
   SummaryGraphEta.Draw("p3");

   TLegend legend(0.5, 0.8, 0.8, 0.6);
   legend.AddEntry(&SummaryGraphEta, "Eta-dependent", "lf");
   legend.AddEntry(&SummaryGraphOverallAndEta, "Both", "lf");
   legend.SetFillColor(0);
   legend.Draw();

   Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
   
   Canvas.SaveAs(Form("Summary_%sJet_JES.png", JetFlavor.c_str()));
   Canvas.SaveAs(Form("Summary_%sJet_JES.C", JetFlavor.c_str()));
   Canvas.SaveAs(Form("SummarY_%sJet_JES.eps", JetFlavor.c_str()));


   // Pretty plots
   TCanvas Canvas2("Canvas2", "Canvas2", 0, 0, 1024, 768);

   TGraphAsymmErrors HRatioEta;
   HRatioEta.SetName("HRatioEta");
   HRatioEta.SetTitle("");
   HRatioEta.SetFillColor(kBlue);
   
   TGraphAsymmErrors HRatioOverallAndEta;
   HRatioOverallAndEta.SetName("HRatioOverallAndEta");
   HRatioOverallAndEta.SetTitle("");
   HRatioOverallAndEta.SetFillColor(kRed);

   for(int N = 1; N < LastJetBin; N++)
   {
      double CentralValue = Nominal.SignalInclusiveYield[N-1] / Nominal.SignalInclusiveYield[N];
      double LowEtaValue = LowEta.SignalInclusiveYield[N-1] / LowEta.SignalInclusiveYield[N];
      double HighEtaValue = HighEta.SignalInclusiveYield[N-1] / HighEta.SignalInclusiveYield[N];

      double LowAllYieldsBefore = -sqrt((LowEta.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])
         * (LowEta.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])
         + (Low.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])
         * (Low.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])) + Nominal.SignalInclusiveYield[N-1];
      double HighAllYieldsBefore = sqrt((HighEta.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])
         * (HighEta.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])
         + (High.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])
         * (High.SignalInclusiveYield[N-1] - Nominal.SignalInclusiveYield[N-1])) + Nominal.SignalInclusiveYield[N-1];
      double LowAllYieldsAfter = -sqrt((LowEta.SignalInclusiveYield[N] - Nominal.SignalInclusiveYield[N])
         * (LowEta.SignalInclusiveYield[N] - Nominal.SignalInclusiveYield[N])
         + (Low.SignalInclusiveYield[N] - Nominal.SignalInclusiveYield[N])
         * (Low.SignalInclusiveYield[N] - Nominal.SignalInclusiveYield[N])) + Nominal.SignalInclusiveYield[N];
      double HighAllYieldsAfter = sqrt((HighEta.SignalInclusiveYield[N] - Nominal.SignalInclusiveYield[N])
         * (HighEta.SignalInclusiveYield[N] - Nominal.SignalInclusiveYield[N])
         + (High.SignalInclusiveYield[N] - Nominal.SignalInclusiveYield[N])
         * (High.SignalInclusiveYield[N] - Nominal.SignalInclusiveYield[N])) + Nominal.SignalInclusiveYield[N];
      double LowAllValue = LowAllYieldsBefore / LowAllYieldsAfter;
      double HighAllValue = HighAllYieldsBefore / HighAllYieldsAfter;

      cout << CentralValue << " " << LowEtaValue << " " << HighEtaValue << endl; 
      cout << CentralValue << " " << LowAllValue << " " << HighAllValue << endl; 

      HRatioEta.SetPoint(N - 1, N, CentralValue);
      HRatioEta.SetPointError(N - 1, 0.5, 0.5, fabs(CentralValue - LowEtaValue),
         fabs(HighEtaValue - CentralValue));
      
      HRatioOverallAndEta.SetPoint(N - 1, N, CentralValue);
      HRatioOverallAndEta.SetPointError(N - 1, 0.5, 0.5, fabs(LowAllValue - CentralValue),
         fabs(CentralValue - HighAllValue));
   }


   Canvas2.cd();
   TPad *Canvas2_1 = new TPad("Canvas2_1", "Canvas2_1", 0, 0.4, 1, 1);
   Canvas2_1->Draw();
   Canvas2_1->cd();
   Canvas2_1->SetFillColor(0);
   Canvas2_1->SetBorderMode(0);
   Canvas2_1->SetBorderSize(2);
   Canvas2_1->SetLogy();

   SummaryGraphOverallAndEta.Draw("a3");
   SummaryGraphEta.Draw("p3");

   TLegend legend2(0.5, 0.8, 0.8, 0.6);
   legend2.AddEntry(&SummaryGraphEta, "Eta-dependent", "lf");
   legend2.AddEntry(&SummaryGraphOverallAndEta, "Both", "lf");
   legend2.SetFillColor(0);
   legend2.Draw();

   Canvas2.cd();
   TPad *Canvas2_2 = new TPad("Canvas2_2", "Canvas2_2", 0, 0.0, 1, 0.4);
   Canvas2_2->SetBottomMargin(0.25);
   Canvas2_2->Draw();
   Canvas2_2->cd();
   Canvas2_2->SetFillColor(0);
   Canvas2_2->SetBorderMode(0);
   Canvas2_2->SetBorderSize(2);

   HRatioOverallAndEta.Draw("a3");
   HRatioEta.Draw("p3");

   Canvas2.SaveAs(Form("SummaryWithRatio_%sJet_JES.png", JetFlavor.c_str()));
   Canvas2.SaveAs(Form("SummaryWithRatio_%sJet_JES.C", JetFlavor.c_str()));
   Canvas2.SaveAs(Form("SummaryWithRatio_%sJet_JES.eps", JetFlavor.c_str()));
   
   PsFile.AddCanvas(Canvas2);
}

FitResult SimultaneousFit_FloatAll(string RootFile, int LastJetBin, string JetFlavor,
      string JetAppendix, double AlphaLValue)
{
   // Dependent variables
   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJet(Form("N%sJet%s", JetFlavor.c_str(), JetAppendix.c_str()), "Count of jets", 0, 20);
   RooArgSet TreeVarSet(ZMass, NJet);

   // Import data
   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get("outTree");
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet);
   
   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(Form("N%sJet%s >= 1", JetFlavor.c_str(),
      JetAppendix.c_str()));
   double DataSetTotalEntry = ReducedDataSet->sumEntries();

   // Shape variable and top-level yield variables
   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.11, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.438, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", AlphaLValue);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.30, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.30, 0.01, 1000000);

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

   for(int N = 1; N <= LastJetBin; N++)
   {
      SignalJetInclusiveYields.push_back(new RooRealVar(Form("SignalInclusiveYield%dJet", N),
         Form("Signal inclusive yield, %d jet", N), CurrentGuess, 0, 10000000));
      SignalJetInclusiveYieldSet.add(*SignalJetInclusiveYields[N-1]);
      
      CurrentGuess = CurrentGuess * 0.2;
   }

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
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N == %d", N),
            "@0 - @1", RooArgSet(*SignalJetInclusiveYields[N-1], *SignalJetInclusiveYields[N])));
      else
         SignalJetYields.push_back(new RooFormulaVar(Form("Signal%dJetYield", N), Form("N >= %d", N),
            "@0", RooArgSet(*SignalJetInclusiveYields[N-1])));

      // argument sets for adding
      TopLevelModels.add(*SignalJets[N-1]);
      TopLevelYields.add(*SignalJetYields[N-1]);
   }

   // Build background pdf
   vector<RooRealVar *> BackgroundExpJet;
   vector<RooAbsPdf *> BackgroundJetShape;
   vector<RooAbsPdf *> BackgroundJets;
   vector<RooRealVar *> BackgroundJetYields;

   RooArgSet BackgroundYields;
   RooArgSet BackgroundExps;

   for(int N = 1; N <= LastJetBin; N++)
   {
      // one exp. for each jet bin: parameter and pdf
      BackgroundExpJet.push_back(new RooRealVar(Form("BackgroundExp%dJet", N),
         Form("Background exp, %d jet", N), 0.000, -1.0, 0.0));
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
      BackgroundYields.add(*BackgroundJetYields[N-1]);
      BackgroundExps.add(*BackgroundExpJet[N-1]);
   }

   // Add pdfs together
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   // Fit!
   FinalModel.fitTo(*ReducedDataSet, Verbose(false));
   
   // Output
   FitResult result;

   result.SignalInclusiveYield.resize(LastJetBin);
   result.SignalInclusiveYieldError.resize(LastJetBin);
   result.BackgroundExclusiveYield.resize(LastJetBin);
   result.BackgroundExclusiveYieldError.resize(LastJetBin);
   
   for(int N = 1; N <= LastJetBin; N++)
   {
      result.SignalInclusiveYield[N-1] = SignalJetInclusiveYields[N-1]->getVal();
      result.SignalInclusiveYieldError[N-1] = SignalJetInclusiveYields[N-1]->getError();

      result.BackgroundExclusiveYield[N-1] = BackgroundJetYields[N-1]->getVal();
      result.BackgroundExclusiveYieldError[N-1] = BackgroundJetYields[N-1]->getError();
   }

   // delete transient stuff
   for(int N = 1; N <= LastJetBin; N++)
   {
      delete BackgroundJetYields[N-1];
      delete BackgroundJets[N-1];
      delete BackgroundJetShape[N-1];
      delete BackgroundExpJet[N-1];
      delete SignalJetInclusiveYields[N-1];
      delete SignalJetYields[N-1];
      delete SignalJets[N-1];
      delete Constrains[N-1];
      delete SignalShapes[N-1];
   }

   return result;
}

