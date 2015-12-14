#include <iostream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooFormulaVar.h"
#include "RooMsgService.h"
#include "RooProdPdf.h"
using namespace RooFit;

#include "PlotHelper2.h"

int main();
TH1D *PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB,
   double S, double SigmaS, double Total, double SigmaTotal, bool LogNormal = false);

int main()
{
   PsFileHelper PsFile("LimitToy2_Result.ps");
   PsFile.AddTextPage("Test statistics distribution of background-only model");

   PsFile.AddTextPage("Gaussian modeling");
   
   TH1D *H[5];
   H[0] = PlotStatistics(PsFile, 20, 5, 5, 3, 25, 7);
   H[1] = PlotStatistics(PsFile, 20, 5, 10, 3, 30, 8);
   H[2] = PlotStatistics(PsFile, 20, 5, 15, 4, 35, 9);
   H[3] = PlotStatistics(PsFile, 20, 5, 20, 5, 40, 10);
   H[4] = PlotStatistics(PsFile, 20, 5, 25, 5, 45, 10);

   TCanvas Canvas1;
   for(int i = 0; i < 5; i++)
   {
      H[i]->SetStats(0);
      H[i]->SetLineColor(i + 1);
      if(i == 0)
         H[i]->Draw();
      else
         H[i]->Draw("same");
   }
   Canvas1.SetLogy();
   PsFile.AddCanvas(Canvas1);
   
   PsFile.Close();

   for(int i = 0; i < 5; i++)
      delete H[i];

   return 0;
}

TH1D *PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB, double S, double SigmaS,
   double Total, double SigmaTotal, bool LogNormal)
{
   cout << B << " " << SigmaB << " " << S << " " << SigmaS << " " << Total << " " << SigmaTotal << endl;

   MsgLevel level = RooMsgService::instance().globalKillBelow();
   RooMsgService::instance().setGlobalKillBelow(ERROR);

   static int HistogramIndex = 0;
   HistogramIndex = HistogramIndex + 1;
   
   TH1D *HLogLikelihoodRatio = new TH1D(Form("HLogLikelihoodRatio%d", HistogramIndex),
      Form("Log likelihood ratio for B = %.2f +- %.2f, S = %.2f +- %.2f, S+B = %.2f +- %.2f",
      B, SigmaB, S, SigmaS, Total, SigmaTotal), 100, -20, 20);
   TH1D HToyDistribution("HToyDistribution", Form("Toy distribution, B = %f +- %f", B, SigmaB),
      100, B - SigmaB * 5, B + SigmaB * 5);
   TH2D HDataVsNLL("HDataVsNLL",
      Form("Data vs. likelihood ratio;data;log likelihood ratio, B = %f +- %f", B, SigmaB),
      100, B - SigmaB * 5, B + SigmaB * 5, 100, -20, 20);

   double BValue = B;
   double BError = SigmaB;
   double SValue = S;
   double SError = SigmaS;
   double SBValue = Total;
   double SBError = SigmaTotal;
   if(LogNormal == true)
   {
      BValue = log(B);
      BError = SigmaB / B;
      SValue = log(S);
      SError = SigmaS / S;
      SBValue = log(Total);
      SBError = SigmaTotal / Total;
   }

   RooRealVar BackgroundPrediction("BackgroundPrediction", "BackgroundPrediction", BValue);
   RooRealVar BackgroundError("BackgroundError", "BackgroundError", BError);
   RooRealVar BackgroundCount("BackgroundCount", "event count", B, 0, 1000);

   RooRealVar SignalPrediction("SignalPrediction", "SignalPrediction", SValue);
   RooRealVar SignalError("SignalError", "SignalError", SError);
   RooRealVar SignalCount("SignalCount", "event count", S, 0, 1000);

   RooRealVar TotalPrediction("TotalPrediction", "TotalPrediction", SBValue);
   RooRealVar TotalError("TotalError", "TotalError", SBError);
   RooFormulaVar TotalCount("TotalCount", "event count", "BackgroundCount + SignalCount",
      RooArgList(BackgroundCount, SignalCount));

   RooFormulaVar LogBackgroundCount("LogBackgroundCount", "log(count)",
      "log(BackgroundCount)", RooArgList(BackgroundCount));
   RooFormulaVar LogSignalCount("LogSignalCount", "log(count)", "log(SignalCount)", RooArgList(SignalCount));
   RooFormulaVar LogTotalCount("LogTotalCount", "log(count)", "log(TotalCount)", RooArgList(TotalCount));
   
   RooGaussian *Model1, *Model2, *Model3;
   if(LogNormal == false)
   {
      Model1 = new RooGaussian("Model1", "model1", BackgroundCount, BackgroundPrediction, BackgroundError);
      Model3 = new RooGaussian("Model2", "model2", SignalCount, SignalPrediction, SignalError);
      Model2 = new RooGaussian("Model3", "model3", TotalCount, TotalPrediction, TotalError);
   }
   else
   {
      Model1 = new RooGaussian("Model1", "model1", LogBackgroundCount, BackgroundPrediction, BackgroundError);
      Model2 = new RooGaussian("Model2", "model2", LogSignalCount, SignalPrediction, SignalError);
      Model3 = new RooGaussian("Model3", "model3", LogTotalCount, TotalPrediction, TotalError);
   }

   RooProdPdf Model("Model", "final model", RooArgList(*Model1, *Model2, *Model3));

   RooDataSet *Toy = (RooDataSet *)Model.generate(RooArgSet(SignalCount, BackgroundCount), 1);
   Model.createNLL(*Toy)->getVal();

   cout << SignalCount.getVal() << " " << BackgroundCount.getVal() << endl;

   RooDataSet FakeData("FakeData", "Fake data constraining total count", RooArgSet(SignalCount, BackgroundCount));
   FakeData.add(RooArgSet(SignalCount, BackgroundCount));
   Model.createNLL(FakeData)->createProfile(RooArgSet())->getVal();
   
   cout << SignalCount.getVal() << " " << BackgroundCount.getVal() << endl;

   // Get minimum LL - or not
   RooArgSet Observables(BackgroundCount, SignalCount);
   RooDataSet MinimumData("MinimumData", "Data at minimum", Observables);
   MinimumData.add(Observables);
   double ReferenceNLL = Model.createNLL(MinimumData)->getVal();
   cout << "ReferenceNLL = " << ReferenceNLL << endl;

   // Generate toy datasets and evaluate log likelihood difference
   for(int i = 0; i < 10000; i++)
   {
      // cout << "Running " << i << "-th toy" << endl;
      RooDataSet *ToyDataSet = (RooDataSet *)Model.generate(Observables, 1);
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      HLogLikelihoodRatio->Fill(ToyNLL - ReferenceNLL);
      const RooArgSet *Set = ToyDataSet->get(0);
      double BCount = ((const RooRealVar *)Set->find("BackgroundCount"))->getVal();
      double SCount = ((const RooRealVar *)Set->find("SignalCount"))->getVal();
      HToyDistribution.Fill(BCount + SCount);
      HDataVsNLL.Fill(BCount + SCount, ToyNLL - ReferenceNLL);
      delete Set;
      delete NLLVar;
      delete ToyDataSet;
   }

   PsFile.AddPlot(HToyDistribution, "", true);
   // PsFile.AddPlot(HLogLikelihoodRatio, "");
   PsFile.AddPlot(HLogLikelihoodRatio, "", true);
   PsFile.AddPlot(HDataVsNLL, "colz", false, true);

   delete Model1, Model2, Model3;

   RooMsgService::instance().setGlobalKillBelow(level);

   return HLogLikelihoodRatio;
}

