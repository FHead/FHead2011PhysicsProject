#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TH2D.h"

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

void SimultaneousFit();
void SimultaneousFit_FloatAll(string RootFile = "Samples/DataAll.root", int LastJetBin = 5,
   string JetFlavor = "Calo", double AlphaLValue = 0.522, string TreeName = "EfficiencyTreeOriginal");

void SimultaneousFit()
{
   SimultaneousFit_FloatAll("Samples/ZJetsAll.root", 4, "Calo", 0.522, "OutTreeNoIsolation");
}

void SimultaneousFit_FloatAll(string RootFile, int LastJetBin, string JetFlavor, double AlphaLValue, string TreeName)
{
   // Dependent variables
   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJet(Form("N%sJet", JetFlavor.c_str()), "Count of jets", 0, 20);
   RooRealVar Muon1PT("Muon1PT", 0, 1000);
   RooRealVar Muon1Isolation("Muon1CombinedIsolation", 0, 1000);
   RooRealVar Muon2PT("Muon2PT", 0, 1000);
   RooRealVar Muon2Isolation("Muon2CombinedIsolation", 0, 1000);
   RooArgSet TreeVarSet(ZMass, NJet, Muon1PT, Muon1Isolation, Muon2PT, Muon2Isolation);

   // Import data
   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get(TreeName.c_str());
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet);
   
   RooDataSet *ReducedDataSet =
      (RooDataSet *)DataSet.reduce(Form("N%sJet >= 1 && (Muon2CombinedIsolation > Muon2PT * 0.3 || Muon1CombinedIsolation > Muon1PT * 0.3)", JetFlavor.c_str()));
   double DataSetTotalEntry = ReducedDataSet->sumEntries();

   // Shape variable and top-level yield variables
   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90.11, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.438);
   RooRealVar AlphaL("AlphaL", "AlphaL", AlphaLValue);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.351);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.119);

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
   
   // Plotting various stuff
   PsFileHelper PsFile("ResultPlots_FloatAll_" + JetFlavor + "_" + TreeName + ".ps");
   PsFile.AddTextPage("Fit results, on data");

   // shape parameters and alpha/beta   
   RooPlot *ParametersPlot1 = ZMass.frame(Bins(50), Name("ZMassParameters1"), Title("Fit results"));
   FinalModel.paramOn(ParametersPlot1, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.9, 0.9),
      Parameters(RooArgSet(PeakPosition, AlphaL, AlphaR, SigmaL, SigmaR)));
   PsFile.AddPlot(ParametersPlot1, "", false);
   
   // background-related parameters
   RooPlot *ParametersPlot2 = ZMass.frame(Bins(50), Name("ZMassParameters2"), Title("Fit results"));
   FinalModel.paramOn(ParametersPlot2, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.9, 0.9),
      Parameters(RooArgSet(BackgroundYields, BackgroundExps)));
   PsFile.AddPlot(ParametersPlot2, "", false);

   // signal yields
   RooPlot *ParametersPlot3 = ZMass.frame(Bins(50), Name("ZMassParameters3"), Title("Fit results"));
   FinalModel.paramOn(ParametersPlot3, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.9, 0.9),
      Parameters(RooArgSet(SignalJetInclusiveYieldSet)));
   PsFile.AddPlot(ParametersPlot3, "", false);

   // all signal curves plotted together
   RooPlot *FinalResultPlot = ZMass.frame(Bins(50), Name("ZMassAllResults"), Title("Mass of lepton pair"));
   ReducedDataSet->plotOn(FinalResultPlot);
   FinalModel.plotOn(FinalResultPlot, LineColor(1));
   for(int N = 1; N <= LastJetBin; N++)
      FinalModel.plotOn(FinalResultPlot, Components(*SignalJets[N-1]), LineColor(N + 1));
   PsFile.AddPlot(FinalResultPlot, "", true);

   // each jet bin plotted separately   
   for(int N = 1; N <= LastJetBin; N++)
   {
      RooPlot *SeparateResultJetPlot;
      if(N != LastJetBin)
         SeparateResultJetPlot = ZMass.frame(Bins(50), Name(Form("SeparateResult%dJetPlot", N)),
            Title(Form("Exclusive %d jet", N)));
      else
         SeparateResultJetPlot = ZMass.frame(Bins(50), Name(Form("SeparateResult%dJetPlot", N)),
            Title(Form("Inclusive %d jet", N)));

      FinalModel.plotOn(SeparateResultJetPlot, Components(RooArgSet(*BackgroundJets[N-1], *SignalJets[N-1])),
         LineColor(N + 1), Normalization(DataSetTotalEntry));
      FinalModel.plotOn(SeparateResultJetPlot, Components(*BackgroundJets[N-1]), LineColor(N + 1),
         Normalization(DataSetTotalEntry));

      RooDataSet *ReducedJetDataSet;
      if(N != LastJetBin)
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%sJet == %d", JetFlavor.c_str(), N));
      else
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%sJet >= %d", JetFlavor.c_str(), N));

      ReducedJetDataSet->plotOn(SeparateResultJetPlot);

      PsFile.AddPlot(SeparateResultJetPlot, "", true);

      // TCanvas TempCanvas("TempCanvas", "TempCanvas", 0, 0, 1024, 768);
      // SeparateResultJetPlot->Draw();
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.png", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.eps", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.C", N));
   }

   TH2D SummaryPlot("SummaryPlot", "Summary Plot", LastJetBin + 1, 0.5, LastJetBin + 1.5, 4, -0.5, 3.5);

   SummaryPlot.GetYaxis()->SetBinLabel(4, "Signal exclusive");
   SummaryPlot.GetYaxis()->SetBinLabel(3, "Background exclusive");
   SummaryPlot.GetYaxis()->SetBinLabel(2, "Signal inclusive");
   SummaryPlot.GetYaxis()->SetBinLabel(1, "Background inclusive");

   double TotalBackgroundSoFar = 0;
   double BackgroundError2SoFar = 0;

   for(int N = LastJetBin; N >= 1; N--)
   {
      SummaryPlot.GetXaxis()->SetBinLabel(N, Form("%d", N));

      SummaryPlot.SetBinContent(N, 4, SignalJetYields[N-1]->getVal());
      SummaryPlot.SetBinError(N, 4, 0);

      SummaryPlot.SetBinContent(N, 3, BackgroundJetYields[N-1]->getVal());
      SummaryPlot.SetBinError(N, 3, BackgroundJetYields[N-1]->getError());

      SummaryPlot.SetBinContent(N, 2, SignalJetInclusiveYields[N-1]->getVal());
      SummaryPlot.SetBinError(N, 2, SignalJetInclusiveYields[N-1]->getError());
      
      TotalBackgroundSoFar = TotalBackgroundSoFar + BackgroundJetYields[N-1]->getVal();
      BackgroundError2SoFar = BackgroundError2SoFar
         + BackgroundJetYields[N-1]->getError() * BackgroundJetYields[N-1]->getError();

      SummaryPlot.SetBinContent(N, 1, TotalBackgroundSoFar);
      SummaryPlot.SetBinError(N, 1, sqrt(BackgroundError2SoFar));
   }

   SummaryPlot.SetStats(0);
   SummaryPlot.SetMarkerSize(2);

   PsFile.AddPlot(SummaryPlot, "text0 error");

   TCanvas Canvas("Canvas", "Canvas", 0, 0, 1024, 768);
   Canvas.SetLeftMargin(0.2);

   SummaryPlot.Draw("text0 error");

   Canvas.SaveAs(Form("SummaryPlot_FloatAll_%s.C", JetFlavor.c_str()));
   Canvas.SaveAs(Form("SummaryPlot_FloatAll_%s.png", JetFlavor.c_str()));
   Canvas.SaveAs(Form("SummaryPlot_FloatAll_%s.eps", JetFlavor.c_str()));

   // Pretty plots
   TCanvas Canvas2("Canvas2", "Canvas2", 0, 0, 1024, 768);

   // Canvas2.Divide(1, 2);

   TH1D HInclusiveYields("HInclusiveYields", Form("Inclusive yields for %s jets;Inclusive jet count;Yield", JetFlavor.c_str()), LastJetBin, 0.5, LastJetBin + 0.5);
   TH1D HRatio("HRatio", Form(";N (Inclusive jet count);#frac{Z + N Jets}{Z + (N+1) Jets}"), LastJetBin, 0.5, LastJetBin + 0.5);

   HInclusiveYields.GetYaxis()->SetRangeUser(0.3, SignalJetInclusiveYields[0]->getVal() * 3);

   HInclusiveYields.SetStats(0);
   HRatio.SetStats(0);

   for(int N = 1; N <= LastJetBin; N++)
   {
      HInclusiveYields.SetBinContent(N, SignalJetInclusiveYields[N-1]->getVal());
      HInclusiveYields.SetBinError(N, SignalJetInclusiveYields[N-1]->getError());

      if(N < LastJetBin)
      {
         HRatio.SetBinContent(N, SignalJetInclusiveYields[N-1]->getVal() / SignalJetInclusiveYields[N]->getVal());
         HRatio.SetBinError(N, SignalJetInclusiveYields[N-1]->getVal() / SignalJetInclusiveYields[N]->getVal()
            * sqrt((SignalJetInclusiveYields[N-1]->getError() / SignalJetInclusiveYields[N-1]->getVal()) * (SignalJetInclusiveYields[N-1]->getError() / SignalJetInclusiveYields[N-1]->getVal())
               + (SignalJetInclusiveYields[N]->getError() / SignalJetInclusiveYields[N]->getVal()) * (SignalJetInclusiveYields[N]->getError() / SignalJetInclusiveYields[N]->getVal())));
      }
   }

   Canvas2.cd();
   TPad *Canvas2_1 = new TPad("Canvas2_1", "Canvas2_1", 0, 0.4, 1, 1);
   Canvas2_1->Draw();
   Canvas2_1->cd();
   Canvas2_1->SetFillColor(0);
   Canvas2_1->SetBorderMode(0);
   Canvas2_1->SetBorderSize(2);
   Canvas2_1->SetLogy();

   HInclusiveYields.GetYaxis()->SetTitleOffset(HInclusiveYields.GetYaxis()->GetTitleOffset() / 2);
   HInclusiveYields.GetXaxis()->SetLabelSize(0.05);
   HInclusiveYields.GetXaxis()->SetTitleSize(0.05);
   HInclusiveYields.GetYaxis()->SetLabelSize(0.05);
   HInclusiveYields.GetYaxis()->SetTitleSize(0.05);
   HInclusiveYields.Draw("error");

   Canvas2.cd();
   TPad *Canvas2_2 = new TPad("Canvas2_2", "Canvas2_2", 0, 0.0, 1, 0.4);
   Canvas2_2->SetBottomMargin(0.25);
   Canvas2_2->Draw();
   Canvas2_2->cd();
   Canvas2_2->SetFillColor(0);
   Canvas2_2->SetBorderMode(0);
   Canvas2_2->SetBorderSize(2);
   
   HRatio.GetYaxis()->SetTitleOffset(0.4);
   HRatio.GetXaxis()->SetLabelSize(0.07);
   HRatio.GetXaxis()->SetTitleSize(0.07);
   HRatio.GetYaxis()->SetLabelSize(0.07);
   HRatio.GetYaxis()->SetTitleSize(0.07);
   HRatio.Draw("error");

   Canvas2.SaveAs(Form("FinalPlot_FloatAll_%s.C", JetFlavor.c_str()));
   Canvas2.SaveAs(Form("FinalPlot_FloatAll_%s.png", JetFlavor.c_str()));
   Canvas2.SaveAs(Form("FinalPlot_FloatAll_%s.eps", JetFlavor.c_str()));

   PsFile.AddCanvas(Canvas2);

   HRatio.Fit("pol1");

   // write results for latex table
   TFile F(Form("FitResult_%s.root", JetFlavor.c_str()), "RECREATE");

   SummaryPlot.Clone("ResultSummary")->Write();

   F.Close();

   // done!
   PsFile.AddTimeStampPage();
   PsFile.Close();

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
}

