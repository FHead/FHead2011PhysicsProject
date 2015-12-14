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
#include "TF1.h"

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
#include "DrawRandom.h"

void SimultaneousFit_FloatAll(string RootFile = "Samples/DataAll.root", int LastJetBin = 4,
   string JetFlavor = "PF", int EnergyThreshold = 30, string DataHelperFile = "Samples/DataAll.dh");

void SimultaneousFit_FloatAll(string RootFile, int LastJetBin, string JetFlavor,
   int EnergyThreshold, string DataHelperFile)
{
   // Get numbers from dh file
   DataHelper DHFile(DataHelperFile);

   char StateString[1000];
   sprintf(StateString, "%s Jet, %d, Eta range all, Isolation 0.05", JetFlavor.c_str(), EnergyThreshold);

   if(DHFile.Exist(StateString) == false)
   {
      cout << "Please fit with tight isolation first!" << endl;
      return;
   }
   if(DHFile[StateString].Exist("AlphaL") == false)
   {
      cout << "Please fit with tight isolation first!" << endl;
      return;
   }

   double AlphaLValue = DHFile[StateString]["AlphaL"].GetDouble();
   cout << "Extracted AlphaL = " << AlphaLValue << endl;

   sprintf(StateString, "%s Jet, %d, Eta range all, Isolation none", JetFlavor.c_str(), EnergyThreshold);

   if(DHFile.Exist(StateString) == false)
   {
      cout << "Please do the constrained fit first!" << endl;
      return;
   }

   if(DHFile[StateString].Exist("ConstrainedFitAlpha") == false
      || DHFile[StateString].Exist("ConstrainedFitBeta") == false
      || DHFile[StateString].Exist("ConstrainedFitAlphaError") == false
      || DHFile[StateString].Exist("ConstrainedFitBetaError") == false
      || DHFile[StateString].Exist("ConstrainedFitAlphaBetaCorrelation") == false)
   {
      cout << "Please do the constrained fit first!" << endl;
      return;
   }

   double AlphaFromComplicatedFit = DHFile[StateString]["ConstrainedFitAlpha"].GetDouble();
   double SigmaAlphaFromComplicatedFit = DHFile[StateString]["ConstrainedFitAlphaError"].GetDouble();
   double BetaFromComplicatedFit = DHFile[StateString]["ConstrainedFitBeta"].GetDouble();
   double SigmaBetaFromComplicatedFit = DHFile[StateString]["ConstrainedFitBetaError"].GetDouble();
   double ComplicatedCorrelation = DHFile[StateString]["ConstrainedFitAlphaBetaCorrelation"].GetDouble();

   cout << "Extracted constrained fit alpha = " << AlphaFromComplicatedFit << " +- "
      << SigmaAlphaFromComplicatedFit << endl;
   cout << "Extracted constrained fit beta = " << BetaFromComplicatedFit << " +- "
      << SigmaBetaFromComplicatedFit << endl;
   cout << "Correlation = " << ComplicatedCorrelation << endl;

   // Dependent variables
   RooRealVar ZMass("Z_mass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJet(Form("N%s_%d", JetFlavor.c_str(), EnergyThreshold), "Count of jets", 0, 20);
   RooRealVar Category("cat_idx", "Category", -10, 10);
   RooArgSet TreeVarSet(ZMass, NJet, Category);

   // Import data
   TFile F1(RootFile.c_str());
   TTree *ZTree1 = (TTree *)F1.Get("noweight");
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree1, TreeVarSet);
   
   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(Form("N%s_%d >= 1 && cat_idx == 1 && Z_mass < 120 && Z_mass > 60", JetFlavor.c_str(), EnergyThreshold));
   double DataSetTotalEntry = ReducedDataSet->sumEntries();

   cout << "Number of events = " << DataSetTotalEntry << endl;

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
         Form("Signal inclusive yield, %d jet", N), CurrentGuess * (1 + DrawGaussian(0.05)), 0, 10000000));
      SignalJetInclusiveYieldSet.add(*SignalJetInclusiveYields[N-1]);
      
      CurrentGuess = CurrentGuess / (AlphaFromComplicatedFit + BetaFromComplicatedFit * N);
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
         Form("Background exp, %d jet", N), -0.02, -1.0, 0.0));
      BackgroundJetShape.push_back(new RooExponential(Form("Background%dJetShape", N),
         Form("Background%dJetShape", N), ZMass, *BackgroundExpJet[N-1]));

      // constrain each one to the right number of bins
      BackgroundJets.push_back(new RooProdPdf(Form("Background%dJet", N), Form("Background, %d jet", N),
         RooArgSet(*BackgroundJetShape[N-1], *Constrains[N-1])));

      // background yields
      int UpperBound = 1000;
      BackgroundJetYields.push_back(new RooRealVar(Form("Background%dJetYield", N),
         Form("Background yield, %d jet", N), 1, 0, UpperBound));

      // argument sets for adding
      TopLevelModels.add(*BackgroundJets[N-1]);
      TopLevelYields.add(*BackgroundJetYields[N-1]);
      BackgroundYields.add(*BackgroundJetYields[N-1]);
      BackgroundExps.add(*BackgroundExpJet[N-1]);
   }

   // Add pdfs together
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   // Fit!
   RooFitResult *FitResult = FinalModel.fitTo(*ReducedDataSet, Verbose(false), Save(true));

   BackgroundJetYields[0]->setConstant(true);
   FitResult = FinalModel.fitTo(*ReducedDataSet, Verbose(false), Save(true));
   
   BackgroundJetYields[0]->setConstant(false);
   if(BackgroundJetYields[0]->getError() > BackgroundJetYields[0]->getVal() * 10)
      BackgroundJetYields[0]->setMax(BackgroundJetYields[0]->getMax() / 10);
   // BackgroundJetYields[0]->setVal(0.01);
   // BackgroundJetYields[0]->setError(0.01);
   FitResult = FinalModel.fitTo(*ReducedDataSet, Verbose(false), Save(true));
   
   // Plotting various stuff
   char ThresholdString[1000] = "";
   sprintf(ThresholdString, "%d", EnergyThreshold);
   PsFileHelper PsFile("ResultPlots_FloatAll_" + JetFlavor + "_" + ThresholdString + ".ps");
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

   TCanvas FirstFourBinCanvas("FirstFourBinCanvas", "", 0, 0, 1024, 1024);
   FirstFourBinCanvas.Divide(2, 2);

   // each jet bin plotted separately   
   for(int N = 1; N <= LastJetBin; N++)
   {
      RooPlot *SeparateResultJetPlot;
      if(N != LastJetBin)
         SeparateResultJetPlot = ZMass.frame(Bins(25), Name(Form("SeparateResult%dJetPlot", N)),
            Title(Form("Exclusive %d jet", N)));
      else
         SeparateResultJetPlot = ZMass.frame(Bins(25), Name(Form("SeparateResult%dJetPlot", N)),
            Title(Form("Inclusive %d jet", N)));

      FinalModel.plotOn(SeparateResultJetPlot, Components(RooArgSet(*BackgroundJets[N-1], *SignalJets[N-1])),
         Normalization(DataSetTotalEntry));
      FinalModel.plotOn(SeparateResultJetPlot, Components(*BackgroundJets[N-1]), Normalization(DataSetTotalEntry));

      RooDataSet *ReducedJetDataSet;
      if(N != LastJetBin)
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%s_%d == %d", JetFlavor.c_str(), EnergyThreshold, N));
      else
         ReducedJetDataSet = (RooDataSet *)ReducedDataSet->reduce(Form("N%s_%d >= %d", JetFlavor.c_str(), EnergyThreshold, N));

      ReducedJetDataSet->plotOn(SeparateResultJetPlot);

      PsFile.AddPlot(SeparateResultJetPlot, "", false);

      if(N <= 4)
      {
         FirstFourBinCanvas.cd(N);
         SeparateResultJetPlot->Draw();
      }

      // TCanvas TempCanvas("TempCanvas", "TempCanvas", 0, 0, 1024, 768);
      // SeparateResultJetPlot->Draw();
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.png", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.eps", N));
      // TempCanvas.SaveAs(Form("ComplicatedFit_%dJet.C", N));
   }

   PsFile.AddCanvas(FirstFourBinCanvas);
   FirstFourBinCanvas.SaveAs(Form("FitPlot_%s_%d.C", JetFlavor.c_str(), EnergyThreshold));
   FirstFourBinCanvas.SaveAs(Form("FitPlot_%s_%d.eps", JetFlavor.c_str(), EnergyThreshold));
   FirstFourBinCanvas.SaveAs(Form("FitPlot_%s_%d.png", JetFlavor.c_str(), EnergyThreshold));

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

   Canvas.SaveAs(Form("SummaryPlot_FloatAll_%s_%d.C", JetFlavor.c_str(), EnergyThreshold));
   Canvas.SaveAs(Form("SummaryPlot_FloatAll_%s_%d.png", JetFlavor.c_str(), EnergyThreshold));
   Canvas.SaveAs(Form("SummaryPlot_FloatAll_%s_%d.eps", JetFlavor.c_str(), EnergyThreshold));

   // Pretty plots
   TCanvas Canvas2("Canvas2", "Canvas2", 0, 0, 1024, 768);

   TH1D HInclusiveYields("HInclusiveYields", Form("Inclusive yields for %s jets;Inclusive jet count;Yield", JetFlavor.c_str()), LastJetBin, 0.5, LastJetBin + 0.5);
   TH1D HRatio("HRatio", Form(";N (Inclusive jet count);#frac{Z + N Jets}{Z + (N+1) Jets}"), LastJetBin, 0.5, LastJetBin + 0.5);
  
   TGraphErrors GInclusiveYields;
   GInclusiveYields.SetName("GInclusiveYields");
   GInclusiveYields.SetLineWidth(2);
   TGraphErrors GRatio;
   GRatio.SetNameTitle("GRatio", Form(";N (Inclusive jet count);#frac{Z + N Jets}{Z + (N+1) Jets}"));
   GRatio.SetLineWidth(2);
   
   TGraphErrors BandFromComplicatedFit;
   BandFromComplicatedFit.SetNameTitle("BandFromComplicatedFit", "BandFromComplicatedFit");
   TGraph LineFromComplicatedFit;
   LineFromComplicatedFit.SetNameTitle("LineFromComplicatedFit", "LineFromComplicatedFit");

   if(AlphaFromComplicatedFit > 0)
   {
      int PointCount = 0;
      for(double x = 0; x < LastJetBin + 10; x = x + 0.05)
      {
         BandFromComplicatedFit.SetPoint(PointCount, x, AlphaFromComplicatedFit + BetaFromComplicatedFit * x);
         BandFromComplicatedFit.SetPointError(PointCount, 0, sqrt(SigmaAlphaFromComplicatedFit * SigmaAlphaFromComplicatedFit + SigmaBetaFromComplicatedFit * SigmaBetaFromComplicatedFit * x * x + 2 * x * SigmaAlphaFromComplicatedFit * SigmaBetaFromComplicatedFit * ComplicatedCorrelation));
         LineFromComplicatedFit.SetPoint(PointCount, x, AlphaFromComplicatedFit + BetaFromComplicatedFit * x);
         PointCount = PointCount + 1;
      }

      BandFromComplicatedFit.SetFillColor(kYellow);
      // BandFromComplicatedFit.SetFillStyle(3001);
      LineFromComplicatedFit.SetLineColor(kRed);
   }

   HInclusiveYields.GetYaxis()->SetRangeUser(0.3, SignalJetInclusiveYields[0]->getVal() * 3);

   HInclusiveYields.SetStats(0);
   HRatio.SetStats(0);

   for(int N = 1; N <= LastJetBin; N++)
   {
      HInclusiveYields.SetBinContent(N, SignalJetInclusiveYields[N-1]->getVal());
      HInclusiveYields.SetBinError(N, SignalJetInclusiveYields[N-1]->getError());
      
      GInclusiveYields.SetPoint(N - 1, N, SignalJetInclusiveYields[N-1]->getVal());
      GInclusiveYields.SetPointError(N - 1, 0, SignalJetInclusiveYields[N-1]->getError());

      if(N < LastJetBin)
      {
         double Ratio = SignalJetInclusiveYields[N-1]->getVal() / SignalJetInclusiveYields[N]->getVal();
         double RelativeError1 = SignalJetInclusiveYields[N-1]->getError() / SignalJetInclusiveYields[N-1]->getVal();
         double RelativeError2 = SignalJetInclusiveYields[N]->getError() / SignalJetInclusiveYields[N]->getVal();
         double Correlation = FitResult->correlation(*SignalJetInclusiveYields[N-1], *SignalJetInclusiveYields[N]);

         cout << "Correlation between bin " << N << " and bin " << N + 1 << " is " << Correlation << endl;

         HRatio.SetBinContent(N, Ratio);
         HRatio.SetBinError(N, Ratio * sqrt(RelativeError1 * RelativeError1 + RelativeError2 * RelativeError2
            - 2 * RelativeError1 * RelativeError2 * Correlation));

         GRatio.SetPoint(N - 1, N, Ratio);
         GRatio.SetPointError(N - 1, 0, Ratio * sqrt(RelativeError1 * RelativeError1 + RelativeError2 * RelativeError2
            - 2 * RelativeError1 * RelativeError2 * Correlation));
      }
   }

   TF1 LinearFit("LinearFit", "pol1", 0, LastJetBin + 1);
   HRatio.Fit(&LinearFit);

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
   HInclusiveYields.SetLineColor(0);
   HInclusiveYields.Draw("error");

   GInclusiveYields.Draw("ep");

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
   HRatio.SetLineWidth(2);
   HRatio.SetLineColor(0);
   HRatio.Draw("error");

   if(AlphaFromComplicatedFit > 0)
   {
      BandFromComplicatedFit.Draw("l3");
      LineFromComplicatedFit.Draw("l");
   }

   GRatio.Draw("ep");

   LinearFit.SetLineStyle(2);
   LinearFit.SetLineWidth(1);
   LinearFit.Draw("same");

   Canvas2.SaveAs(Form("FinalPlot_FloatAll_%s_%d.C", JetFlavor.c_str(), EnergyThreshold));
   Canvas2.SaveAs(Form("FinalPlot_FloatAll_%s_%d.png", JetFlavor.c_str(), EnergyThreshold));
   Canvas2.SaveAs(Form("FinalPlot_FloatAll_%s_%d.eps", JetFlavor.c_str(), EnergyThreshold));
   PsFile.AddCanvas(Canvas2);

   HRatio.Fit("pol1");
   HRatio.Fit("pol0");

   // write results for latex table
   TFile F(Form("FitResult_%s_%d.root", JetFlavor.c_str(), EnergyThreshold), "RECREATE");

   SummaryPlot.Clone("ResultSummary")->Write();

   HInclusiveYields.Clone("InclusiveYieldsHistogram")->Write();
   GInclusiveYields.Clone("InclusiveYieldsGraph")->Write();
   BandFromComplicatedFit.Clone("BandFromComplicatedFitGraph")->Write();
   LineFromComplicatedFit.Clone("LineFromComplicatedFitGraph")->Write();
   GRatio.Clone("RatioGraph")->Write();
   HRatio.Clone("RatioHistogram")->Write();
   LinearFit.Clone("LinearFit")->Write();

   F.Close();

   // Writing out results
   TFile ResultFile(Form("ResultFile_%s_%d.root", JetFlavor.c_str(), EnergyThreshold), "RECREATE");

   // make a copy of inclusive yields
   TH1D HResultInclusiveYields("HResultInclusiveYields",
      Form("Inclusive yields for %s jets;Inclusive jet count;Yield", JetFlavor.c_str()),
      LastJetBin, 0.5, LastJetBin + 0.5);
   for(int N = 1; N <= LastJetBin; N++)
   {
      HResultInclusiveYields.SetBinContent(N, SignalJetInclusiveYields[N-1]->getVal());
      HResultInclusiveYields.SetBinError(N, SignalJetInclusiveYields[N-1]->getError());
   }
   HResultInclusiveYields.Write();

   // Get correlation matrix
   TH2D HResultCorrelationMatrix("HResultCorrelationMatrix",
      Form("Correlation matrix for %s jets;Inclusive Jet Count;Inclusive Jet Count", JetFlavor.c_str()),
      LastJetBin, 0.5, LastJetBin + 0.5,
      LastJetBin, 0.5, LastJetBin + 0.5);
   for(int N1 = 1; N1 <= LastJetBin; N1++)
      for(int N2 = 1; N2 <= LastJetBin; N2++)
         HResultCorrelationMatrix.SetBinContent(N1, N2,
            FitResult->correlation(*SignalJetInclusiveYields[N1-1], *SignalJetInclusiveYields[N2-1]));
   HResultCorrelationMatrix.Write();

   // make a histogram of exclusive yields
   TH1D HResultExclusiveYields("HResultExclusiveYields",
      Form("Exclusive yields for %s jets;Exclusive jet count (except the last one);Yield", JetFlavor.c_str()),
      LastJetBin, 0.5, LastJetBin + 0.5);
   for(int N = 1; N < LastJetBin; N++)
   {
      double Value1 = SignalJetInclusiveYields[N-1]->getVal();
      double Error1 = SignalJetInclusiveYields[N-1]->getError();
      double Value2 = SignalJetInclusiveYields[N]->getVal();
      double Error2 = SignalJetInclusiveYields[N]->getError();
      double Correlation = FitResult->correlation(*SignalJetInclusiveYields[N-1], *SignalJetInclusiveYields[N]);

      double Variance = Error1 * Error1 + Error2 * Error2 - 2 * Error1 * Error2 * Correlation;
      
      HResultExclusiveYields.SetBinContent(N, Value1 - Value2);
      HResultExclusiveYields.SetBinError(N, sqrt(Variance));
   }
   HResultExclusiveYields.SetBinContent(LastJetBin, SignalJetInclusiveYields[LastJetBin-1]->getVal());
   HResultExclusiveYields.SetBinError(LastJetBin, SignalJetInclusiveYields[LastJetBin-1]->getError());
   HResultExclusiveYields.Write();

   // Write fit result object
   FitResult->Clone("UnconstrainedFitResult")->Write();

   ResultFile.Close();

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

