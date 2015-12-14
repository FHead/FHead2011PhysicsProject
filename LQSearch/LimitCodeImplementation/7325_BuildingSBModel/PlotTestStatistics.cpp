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
#include "RooPoisson.h"
using namespace RooFit;

#include "PlotHelper2.h"

int main();
TH1D *PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB,
   double S, double SigmaS, double Total, bool LogNormal = false);

int main()
{
   PsFileHelper PsFile("LimitToy2_Result.ps");
   PsFile.AddTextPage("Test statistics distribution of background-only model");

   PsFile.AddTextPage("Gaussian modeling");
   
   TH1D *H[5];
   H[0] = PlotStatistics(PsFile, 2, 1, 5, 1, 7, true);
   H[1] = PlotStatistics(PsFile, 2, 2, 5, 2, 7, true);
   H[2] = PlotStatistics(PsFile, 2, 4, 5, 4, 7, true);
   H[3] = PlotStatistics(PsFile, 2, 8, 5, 8, 7, true);
   H[4] = PlotStatistics(PsFile, 2, 16, 5, 16, 7, true);

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
   double Total, bool LogNormal)
{
   cout << "Starting function with B = " << B << " +- " << SigmaB
      << ", S = " << S << " +- " << SigmaS
      << ", Total = " << Total << " " << endl;

   MsgLevel level = RooMsgService::instance().globalKillBelow();
   RooMsgService::instance().setGlobalKillBelow(ERROR);

   static int HistogramIndex = 0;
   HistogramIndex = HistogramIndex + 1;
   
   TH1D *HLogLikelihoodRatio = new TH1D(Form("HLogLikelihoodRatio%d", HistogramIndex),
      Form("Log likelihood ratio for B = %.2f +- %.2f, S = %.2f +- %.2f, Total = %.2f",
      B, SigmaB, S, SigmaS, Total), 100, -2, 15);
   TH1D HToyDistribution("HToyDistribution", Form("Toy distribution, B = %f +- %f", B, SigmaB),
      100, -5, 95);
   TH2D HDataVsNLL("HDataVsNLL",
      Form("Data vs. likelihood ratio;data;log likelihood ratio, B = %f +- %f", B, SigmaB),
      100, -5, 95, 100, -2, 15);

   double BValue = B;
   double BError = SigmaB;
   double SValue = S;
   double SError = SigmaS;
   if(LogNormal == true)
   {
      BValue = log(B);
      BError = SigmaB / B;
      SValue = log(S);
      SError = SigmaS / S;
   }

   RooRealVar BackgroundPrediction("BackgroundPrediction", "BackgroundPrediction", BValue);
   RooRealVar BackgroundError("BackgroundError", "BackgroundError", BError);
   RooRealVar BackgroundCount("BackgroundCount", "event count", 100, 0, 1000);

   RooRealVar SignalPrediction("SignalPrediction", "SignalPrediction", SValue);
   RooRealVar SignalError("SignalError", "SignalError", SError);
   RooRealVar SignalCount("SignalCount", "event count", 100, 0, 1000);

   RooRealVar TotalNumber("TotalNumber", "TotalNumber", Total, 0, 100000);
   RooFormulaVar TotalCount("TotalCount", "event count", "BackgroundCount + SignalCount",
      RooArgList(BackgroundCount, SignalCount));

   RooFormulaVar LogBackgroundCount("LogBackgroundCount", "log(count)",
      "log(BackgroundCount)", RooArgList(BackgroundCount));
   RooFormulaVar LogSignalCount("LogSignalCount", "log(count)", "log(SignalCount)", RooArgList(SignalCount));
   
   RooGaussian *Model1, *Model2;
   if(LogNormal == false)
   {
      Model1 = new RooGaussian("Model1", "model1", BackgroundCount, BackgroundPrediction, BackgroundError);
      Model2 = new RooGaussian("Model2", "model2", SignalCount, SignalPrediction, SignalError);
   }
   else
   {
      Model1 = new RooGaussian("Model1", "model1", LogBackgroundCount, BackgroundPrediction, BackgroundError);
      Model2 = new RooGaussian("Model2", "model2", LogSignalCount, SignalPrediction, SignalError);
   }

   RooPoisson Model3("Model3", "core model", TotalNumber, TotalCount);

   RooProdPdf Model("Model", "final model", RooArgList(*Model1, *Model2, Model3));

   // cout << "S = " << SignalCount.getVal() << ", B = " << BackgroundCount.getVal() << endl;

   RooDataSet FakeData("FakeData", "Fake data constraining total count", RooArgSet(TotalNumber));
   TotalNumber.setVal(Total);
   FakeData.add(RooArgSet(TotalNumber));
   Model.createNLL(FakeData)->createProfile(RooArgSet())->getVal();
   
   cout << "S = " << SignalCount.getVal() << ", B = " << BackgroundCount.getVal() << endl;

   // Get minimum LL - or not
   RooArgSet Observables(TotalNumber);
   RooDataSet MinimumData("MinimumData", "Fake data constraining total count", RooArgSet(TotalNumber));
   MinimumData.add(Observables);
   double ReferenceNLL = Model.createNLL(MinimumData)->getVal();
   cout << "ReferenceNLL = " << ReferenceNLL << endl;

   // Generate toy datasets and evaluate log likelihood difference
   for(int i = 0; i < 100000; i++)
   {
      // cout << "Running " << i << "-th toy" << endl;
      RooDataSet *ToyDataSet = (RooDataSet *)Model.generate(Observables, 1);
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      HLogLikelihoodRatio->Fill(ToyNLL - ReferenceNLL);
      const RooArgSet *Set = ToyDataSet->get(0);
      double SBCount = ((const RooRealVar *)Set->find("TotalNumber"))->getVal();
      // double BCount = ((const RooRealVar *)Set->find("BackgroundCount"))->getVal();
      // double SCount = ((const RooRealVar *)Set->find("SignalCount"))->getVal();
      HToyDistribution.Fill(SBCount);
      HDataVsNLL.Fill(SBCount, ToyNLL - ReferenceNLL);
      delete Set;
      delete NLLVar;
      delete ToyDataSet;
   }

   PsFile.AddPlot(HToyDistribution, "", true);
   // PsFile.AddPlot(HLogLikelihoodRatio, "");
   PsFile.AddPlot(HLogLikelihoodRatio, "", true);
   PsFile.AddPlot(HDataVsNLL, "colz", false, true);

   delete Model1, Model2;

   RooMsgService::instance().setGlobalKillBelow(level);

   return HLogLikelihoodRatio;
}

