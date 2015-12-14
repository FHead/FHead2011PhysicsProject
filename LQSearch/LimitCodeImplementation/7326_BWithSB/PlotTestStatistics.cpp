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
void PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB,
   double S, double SigmaS, double Total, bool LogNormal = false);

int main()
{
   PsFileHelper PsFile("LimitToy2_Result.ps");
   PsFile.AddTextPage("Test statistics distribution of background-only model");

   PlotStatistics(PsFile, 30, 8, 40, 8, 70, false);

   PsFile.Close();

   return 0;
}

void PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB, double S, double SigmaS,
   double Total, bool LogNormal)
{
   cout << "Starting function with B = " << B << " +- " << SigmaB
      << ", S = " << S << " +- " << SigmaS
      << ", Total = " << Total << " " << endl;

   MsgLevel level = RooMsgService::instance().globalKillBelow();
   RooMsgService::instance().setGlobalKillBelow(ERROR);

   TH1D HLogLikelihoodRatio("HLogLikelihoodRatio", "Log likelihood ratio (S+B on S+B)", 100, -5, 95);
   TH1D HToyDistribution("HToyDistribution", "Toy distribution", 150, 0, 150);
   TH2D HDataVsNLL("HDataVsNLL", "Data vs. likelihood ratio;data;log likelihood ratio", 100, 0, 150, 100, -5, 95);
   TH1D HBDistribution("HBDistribution", "B distribution", 150, 0, 150);
   TH1D HBLikelihoodRatio("HBLikelihoodRatio", "B likelihood ratio", 100, -5, 95);

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
   RooRealVar BackgroundCount("BackgroundCount", "event count", 100, 0, 10000);

   RooRealVar SignalPrediction("SignalPrediction", "SignalPrediction", SValue);
   RooRealVar SignalError("SignalError", "SignalError", SError);
   RooRealVar SignalCount("SignalCount", "event count", 100, 0, 10000);

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

   RooFormulaVar TotalError("TotalError", "Yay", "sqrt(TotalCount)", RooArgSet(TotalCount));
   RooFormulaVar BackgroundError2("BackgroundError2", "Yay", "sqrt(BackgroundCount)", RooArgSet(BackgroundCount));

   // RooGaussian Model3("Model3", "core model", TotalNumber, TotalCount, TotalError);
   // RooGaussian BModel3("BModel3", "backgroudn core model", TotalNumber, BackgroundCount, BackgroundError2);
   RooPoisson Model3("Model3", "core model", TotalNumber, TotalCount);
   RooPoisson BModel3("BModel3", "backgroudn core model", TotalNumber, BackgroundCount);
   cout << "Use Poisson statistics for code modelling" << endl;

   RooProdPdf Model("Model", "final model", RooArgList(*Model1, *Model2, Model3));
   RooProdPdf BModel("BModel", "background model", RooArgList(*Model1, BModel3));

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
      RooDataSet *ToyDataSet = (RooDataSet *)Model.generate(Observables, 1);
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      HLogLikelihoodRatio.Fill(ToyNLL - ReferenceNLL);
      const RooArgSet *Set = ToyDataSet->get(0);
      double SBCount = ((const RooRealVar *)Set->find("TotalNumber"))->getVal();
      HToyDistribution.Fill(SBCount);
      HDataVsNLL.Fill(SBCount, ToyNLL - ReferenceNLL);
      delete Set;
      delete NLLVar;
      delete ToyDataSet;
   }
   
   for(int i = 0; i < 10000; i++)
   {
      RooDataSet *ToyDataSet = (RooDataSet *)BModel.generate(Observables, 1);
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      HBLikelihoodRatio.Fill(ToyNLL - ReferenceNLL);
      const RooArgSet *Set = ToyDataSet->get(0);
      double SBCount = ((const RooRealVar *)Set->find("TotalNumber"))->getVal();
      HBDistribution.Fill(SBCount);
      delete Set;
      delete NLLVar;
      delete ToyDataSet;
   }

   PsFile.AddPlot(HToyDistribution, "", true);
   PsFile.AddPlot(HLogLikelihoodRatio, "");
   PsFile.AddPlot(HBDistribution, "", true);
   PsFile.AddPlot(HBLikelihoodRatio, "", true);
   PsFile.AddPlot(HDataVsNLL, "colz", false, true);

   TLegend legend(0.3, 0.8, 0.8, 0.6);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(&HLogLikelihoodRatio, "S+B evaluated on S+B", "l");
   legend.AddEntry(&HBLikelihoodRatio, "B evaluated on S+B", "l");

   TCanvas C;
   HLogLikelihoodRatio.SetStats(0);
   HLogLikelihoodRatio.Draw();
   HBLikelihoodRatio.SetLineColor(kRed);
   HBLikelihoodRatio.SetStats(0);
   HBLikelihoodRatio.Draw("same");
   legend.Draw();
   C.SetLogy();
   PsFile.AddCanvas(C);

   delete Model1, Model2;

   RooMsgService::instance().setGlobalKillBelow(level);
}

