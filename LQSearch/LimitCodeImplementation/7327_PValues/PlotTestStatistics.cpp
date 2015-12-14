#include <iostream>
#include <vector>
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
double EstimatePValue(double TestStatistics, vector<double> &Samples);

int main()
{
   PsFileHelper PsFile("Limit3.ps");
   PsFile.AddTextPage("p-Value distributions");

   PlotStatistics(PsFile, 30, 6, 10, 4, 40, false);
   PlotStatistics(PsFile, 30, 6, 20, 8, 50, false);
   PlotStatistics(PsFile, 30, 6, 40, 16, 70, false);

   PsFile.Close();

   return 0;
}

void PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB, double S, double SigmaS,
   double Total, bool LogNormal)
{
   int NumberOfTries = 10000;

   cout << "Starting function with B = " << B << " +- " << SigmaB
      << ", S = " << S << " +- " << SigmaS
      << ", Total = " << Total << " " << endl;

   MsgLevel level = RooMsgService::instance().globalKillBelow();
   RooMsgService::instance().setGlobalKillBelow(ERROR);

   TH1D HLogLikelihoodRatio("HLogLikelihoodRatio", "Log likelihood ratio (S+B on S+B)", 100, -5, 95);
   TH1D HToyDistribution("HToyDistribution", "Toy distribution", 150, 0, 150);
   TH1D HBDistribution("HBDistribution", "B distribution", 150, 0, 150);
   TH1D HBLikelihoodRatio("HBLikelihoodRatio", "B likelihood ratio", 100, -5, 95);
   TH1D HSBPValues("HSBPValues", "p-value distribution on S+B model", 100, 0, 1);
   TH1D HBPValues("HBPValues", "p-value distribution on B model", 100, 0, 1);
   TH1D HCLs("HCLs", "CLs distribution for this set of models", 100, 0, 5);

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

   RooGaussian Model3("Model3", "core model", TotalNumber, TotalCount, TotalError);
   RooGaussian BModel3("BModel3", "backgroudn core model", TotalNumber, BackgroundCount, BackgroundError2);
   // RooPoisson Model3("Model3", "core model", TotalNumber, TotalCount);
   // RooPoisson BModel3("BModel3", "backgroudn core model", TotalNumber, BackgroundCount);

   RooProdPdf Model("Model", "final model", RooArgList(*Model1, *Model2, Model3));
   RooProdPdf BModel("BModel", "background model", RooArgList(*Model1, BModel3));

   RooDataSet FakeData("FakeData", "Fake data constraining total count", RooArgSet(TotalNumber));
   TotalNumber.setVal(Total);
   FakeData.add(RooArgSet(TotalNumber));
   Model.createNLL(FakeData)->createProfile(RooArgSet())->getVal();
   
   // Get minimum LL - or not
   RooArgSet Observables(TotalNumber);
   RooDataSet MinimumData("MinimumData", "Fake data constraining total count", RooArgSet(TotalNumber));
   MinimumData.add(Observables);
   double ReferenceNLL = Model.createNLL(MinimumData)->getVal();
   cout << "ReferenceNLL = " << ReferenceNLL << endl;

   // Generate toy datasets and evaluate log likelihood difference
   vector<double> SBBaseSamples;
   for(int i = 0; i < 100000; i++)
   {
      RooDataSet *ToyDataSet = (RooDataSet *)Model.generate(Observables, 1);
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      SBBaseSamples.push_back(ToyNLL - ReferenceNLL);
      delete NLLVar;
      delete ToyDataSet;
   }
   sort(SBBaseSamples.begin(), SBBaseSamples.end());

   vector<double> SBSamples;
   for(int i = 0; i < NumberOfTries; i++)
   {
      RooDataSet *ToyDataSet = (RooDataSet *)Model.generate(Observables, 1);
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      HLogLikelihoodRatio.Fill(ToyNLL - ReferenceNLL);
      const RooArgSet *Set = ToyDataSet->get(0);
      double SBCount = ((const RooRealVar *)Set->find("TotalNumber"))->getVal();
      HToyDistribution.Fill(SBCount);
      SBSamples.push_back(ToyNLL - ReferenceNLL);
      delete Set;
      delete NLLVar;
      delete ToyDataSet;
   }
   
   vector<double> BSamples;
   for(int i = 0; i < NumberOfTries; i++)
   {
      RooDataSet *ToyDataSet = (RooDataSet *)BModel.generate(Observables, 1);
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      HBLikelihoodRatio.Fill(ToyNLL - ReferenceNLL);
      const RooArgSet *Set = ToyDataSet->get(0);
      double SBCount = ((const RooRealVar *)Set->find("TotalNumber"))->getVal();
      HBDistribution.Fill(SBCount);
      BSamples.push_back(ToyNLL - ReferenceNLL);
      delete Set;
      delete NLLVar;
      delete ToyDataSet;
   }

   // Calculate p-value distributions
   vector<double> SBPValues;
   vector<double> BPValues;
   vector<double> CLsValues;
   for(int i = 0; i < NumberOfTries; i++)
   {
      SBPValues.push_back(EstimatePValue(SBSamples[i], SBBaseSamples));
      BPValues.push_back(EstimatePValue(BSamples[i], SBBaseSamples));
      CLsValues.push_back(BPValues[i] / SBPValues[i]);
   }
   for(int i = 0; i < NumberOfTries; i++)
   {
      HSBPValues.Fill(SBPValues[i]);
      HBPValues.Fill(BPValues[i]);
      HCLs.Fill(BPValues[i] / SBPValues[i]);
   }

   sort(SBPValues.begin(), SBPValues.end());
   sort(BPValues.begin(), BPValues.end());
   sort(CLsValues.begin(), CLsValues.end());

   PsFile.AddPlot(HToyDistribution, "", true);
   PsFile.AddPlot(HLogLikelihoodRatio, "", true);
   PsFile.AddPlot(HBDistribution, "", true);
   PsFile.AddPlot(HBLikelihoodRatio, "", true);

   TLegend legend(0.4, 0.8, 0.9, 0.6);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(&HLogLikelihoodRatio, "S+B evaluated on S+B", "l");
   legend.AddEntry(&HBLikelihoodRatio, "B evaluated on S+B", "l");

   TCanvas C;
   HLogLikelihoodRatio.SetTitle("S+B vs. B test statistics");
   HLogLikelihoodRatio.SetStats(0);
   HLogLikelihoodRatio.Draw();
   HBLikelihoodRatio.SetLineColor(kRed);
   HBLikelihoodRatio.SetStats(0);
   HBLikelihoodRatio.Draw("same");
   legend.Draw();
   C.SetLogy();
   PsFile.AddCanvas(C);

   HSBPValues.SetMinimum(0);
   PsFile.AddPlot(HSBPValues, "", false);
   HBPValues.SetMinimum(0);
   PsFile.AddPlot(HBPValues, "", false);
   HCLs.SetMinimum(0);
   PsFile.AddPlot(HCLs, "", false);

   int Median = (int)(NumberOfTries / 2);   // not exactly; number is even, but, ok
   int SigmaDown = (int)(NumberOfTries * 0.317);
   int SigmaUp = (int)(NumberOfTries * 0.683);

   cout << "Median CL(s+b) = " << SBPValues[Median] << endl;
   cout << "-1 sigma CL(s+b) = " << SBPValues[SigmaDown] << endl;
   cout << "+1 sigma CL(s+b) = " << SBPValues[SigmaUp] << endl;

   cout << "Median CL(b) = " << BPValues[Median] << endl;
   cout << "-1 sigma CL(b) = " << BPValues[SigmaDown] << endl;
   cout << "+1 sigma CL(b) = " << BPValues[SigmaUp] << endl;

   cout << "Median CLs = " << CLsValues[Median] << endl;
   cout << "-1 sigma CLs = " << CLsValues[SigmaDown] << endl;
   cout << "+1 sigma CLs = " << CLsValues[SigmaUp] << endl;

   delete Model1, Model2;

   RooMsgService::instance().setGlobalKillBelow(level);
}

double EstimatePValue(double TestStatistics, vector<double> &Samples)
{
   // Assume the input vector is sorted

   if(TestStatistics <= Samples[0])
      return 1;
   if(TestStatistics > Samples[Samples.size()-1])
      return 0;

   int MinIndex = 0;
   int MaxIndex = Samples.size();
   while(MaxIndex - MinIndex > 1)
   {
      int Probe = (MaxIndex + MinIndex) / 2;

      if(Samples[MaxIndex] == Samples[Probe])
      {
         MaxIndex = Probe;
         continue;
      }
      
      if(Samples[MinIndex] == Samples[Probe])
      {
         MinIndex = Probe;
         continue;
      }

      if(TestStatistics <= Samples[Probe])
         MaxIndex = Probe;
      else
         MinIndex = Probe;
   }

   double CountAbove = Samples.size() - MaxIndex;
   return CountAbove / Samples.size();
}




