#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"

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

struct ValuesForLimit;
int main();
ValuesForLimit PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB,
   double S, double SigmaS, double Total, bool LogNormal = false);
double EstimatePValue(double TestStatistics, vector<double> &Samples);

struct ValuesForLimit
{
   double SBValues[3];   // -1 sigma, median, +1 sigma
   double BValues[3];   // -1 sigma, median, +1 sigma
   double CLsValues[3];   // -1 sigma, median, +1 sigma
   double BadCLsValues[3];   // -1 sigma, median, +1 sigma
   double S;
   double SError;
};

int main()
{
   PsFileHelper PsFile("Limit4.ps");
   PsFile.AddTextPage("Expected limits!!!");

   vector<ValuesForLimit> Results;

   double SignalRelativeError = 0.117;
   // double SignalRelativeError = 0.125;
   for(double S = 30; S <= 80; S = S + 5)
      Results.push_back(PlotStatistics(PsFile, 274.45 * 1.05, 23.28,
         S, S * SignalRelativeError, 274.45 * 1.05 + S, false));

   PsFile.AddTextPage("Graphs to get the expected limits!!!!!");

   TGraph FivePercentLine;
   FivePercentLine.SetNameTitle("FivePercentLine", "A line showing position of 5%");
   FivePercentLine.SetLineWidth(2);
   FivePercentLine.SetLineStyle(5);
   FivePercentLine.SetPoint(0, 0, 0.05);
   FivePercentLine.SetPoint(1, 10000, 0.05);
   
   TGraph BMedianGraph;
   TGraph BPlusGraph;
   TGraph BMinusGraph;
   TGraph CLsMedianGraph;
   TGraph CLsPlusGraph;
   TGraph CLsMinusGraph;
   TGraph BadCLsMedianGraph;
   TGraph BadCLsPlusGraph;
   TGraph BadCLsMinusGraph;
   
   BMedianGraph.SetNameTitle("BMedianGraph", "Background median p-value (evaluated on S+B);Signal count;p-value");
   BPlusGraph.SetNameTitle("BPlusGraph", "Background +sigma p-value (evaluated on S+B);Signal count;p-value");
   BMinusGraph.SetNameTitle("BMinusGraph", "Background -sigma p-value (evaluated on S+B);Signal count;p-value");
   CLsMedianGraph.SetNameTitle("CLsMedianGraph", "CLs median;Signal count;CLs");
   CLsPlusGraph.SetNameTitle("CLsPlusGraph", "CLs +sigma;Signal count;CLs");
   CLsMinusGraph.SetNameTitle("CLsMinusGraph", "CLs -sigma;Signal count;CLs");
   BadCLsMedianGraph.SetNameTitle("BadCLsMedianGraph", "Bad CLs median;Signal count;Bad CLs");
   BadCLsPlusGraph.SetNameTitle("BadCLsPlusGraph", "Bad CLs +sigma;Signal count;Bad CLs");
   BadCLsMinusGraph.SetNameTitle("BadCLsMinusGraph", "Bad CLs -sigma;Signal count;Bad CLs");

   for(int i = 0; i < (int)Results.size(); i++)
   {
      BMedianGraph.SetPoint(i, Results[i].S, Results[i].BValues[1]);
      BPlusGraph.SetPoint(i, Results[i].S, Results[i].BValues[2]);
      BMinusGraph.SetPoint(i, Results[i].S, Results[i].BValues[0]);
      CLsMedianGraph.SetPoint(i, Results[i].S, Results[i].CLsValues[1]);
      CLsPlusGraph.SetPoint(i, Results[i].S, Results[i].CLsValues[2]);
      CLsMinusGraph.SetPoint(i, Results[i].S, Results[i].CLsValues[0]);
      BadCLsMedianGraph.SetPoint(i, Results[i].S, Results[i].BadCLsValues[1]);
      BadCLsPlusGraph.SetPoint(i, Results[i].S, Results[i].BadCLsValues[2]);
      BadCLsMinusGraph.SetPoint(i, Results[i].S, Results[i].BadCLsValues[0]);
   }

   BMedianGraph.SetMarkerStyle(11);
   BPlusGraph.SetMarkerStyle(11);
   BMinusGraph.SetMarkerStyle(11);
   CLsMedianGraph.SetMarkerStyle(11);
   CLsPlusGraph.SetMarkerStyle(11);
   CLsMinusGraph.SetMarkerStyle(11);
   BadCLsMedianGraph.SetMarkerStyle(11);
   BadCLsPlusGraph.SetMarkerStyle(11);
   BadCLsMinusGraph.SetMarkerStyle(11);

   BMedianGraph.SetLineColor(kBlue - 3);
   BPlusGraph.SetLineColor(kGreen - 3);
   BMinusGraph.SetLineColor(kRed - 3);
   CLsMedianGraph.SetLineColor(kBlue - 3);
   CLsPlusGraph.SetLineColor(kGreen - 3);
   CLsMinusGraph.SetLineColor(kRed - 3);
   BadCLsMedianGraph.SetLineColor(kBlue - 3);
   BadCLsPlusGraph.SetLineColor(kGreen - 3);
   BadCLsMinusGraph.SetLineColor(kRed - 3);

   TLegend Legend(0.5, 0.8, 0.9, 0.6);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(&BMedianGraph, "Median", "l");
   Legend.AddEntry(&BPlusGraph, "+1 #sigma", "l");
   Legend.AddEntry(&BMinusGraph, "-1 #sigma", "l");
   Legend.AddEntry(&FivePercentLine, "95% C.L. line", "l");

   TCanvas BCanvas;
   BMedianGraph.SetTitle("Background expected p-value (evaluated on S+B);Signal count;p-value");
   BMedianGraph.Draw("apl");
   BPlusGraph.Draw("pl");
   BMinusGraph.Draw("pl");
   FivePercentLine.Draw("l");
   Legend.Draw();
   PsFile.AddCanvas(BCanvas);
   BCanvas.SetLogy();
   PsFile.AddCanvas(BCanvas);
   
   TCanvas CLsCanvas;
   CLsMedianGraph.SetTitle("Expected CLs value;Signal count;CLs");
   CLsMedianGraph.Draw("apl");
   CLsPlusGraph.Draw("pl");
   CLsMinusGraph.Draw("pl");
   FivePercentLine.Draw("l");
   Legend.Draw();
   PsFile.AddCanvas(CLsCanvas);
   CLsCanvas.SetLogy();
   PsFile.AddCanvas(CLsCanvas);
   
   TCanvas BadCLsCanvas;
   BadCLsMedianGraph.SetTitle("Expected bad CLs value;Signal count;Bad CLs");
   BadCLsMedianGraph.Draw("apl");
   BadCLsPlusGraph.Draw("pl");
   BadCLsMinusGraph.Draw("pl");
   FivePercentLine.Draw("l");
   Legend.Draw();
   PsFile.AddCanvas(BadCLsCanvas);
   BadCLsCanvas.SetLogy();
   PsFile.AddCanvas(BadCLsCanvas);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

ValuesForLimit PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB, double S, double SigmaS,
   double Total, bool LogNormal)
{
   PsFile.AddTextPage("Start running a point");

   const int NumberOfTries = 10000;
   const int BaseSampleCount = 10000;

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
   TH1D HBadCLs("HBadCLs", "Bad CLs distribution for this set of models", 100, 0, 5);

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

   // RooFormulaVar TotalError("TotalError", "Yay", "sqrt(TotalCount)", RooArgSet(TotalCount));
   // RooFormulaVar BackgroundError2("BackgroundError2", "Yay", "sqrt(BackgroundCount)", RooArgSet(BackgroundCount));

   // RooGaussian Model3("Model3", "core model", TotalNumber, TotalCount, TotalError);
   // RooGaussian BModel3("BModel3", "backgroudn core model", TotalNumber, BackgroundCount, BackgroundError2);
   RooPoisson Model3("Model3", "core model", TotalNumber, TotalCount);
   RooPoisson BModel3("BModel3", "backgroudn core model", TotalNumber, BackgroundCount);

   RooProdPdf Model("Model", "final model", RooArgList(*Model1, *Model2, Model3));
   RooProdPdf BModel("BModel", "background model", RooArgList(*Model1, BModel3));

   RooDataSet FakeData("FakeData", "Fake data constraining total count", RooArgSet(TotalNumber));
   TotalNumber.setVal(S + B);
   FakeData.add(RooArgSet(TotalNumber));
   Model.createNLL(FakeData)->createProfile(RooArgSet())->getVal();
   
   // Get minimum LL - or not
   RooArgSet TempObservables(TotalNumber);
   RooDataSet MinimumData("MinimumData", "Fake data constraining total count", TempObservables);
   MinimumData.add(TempObservables);
   double ReferenceNLL = Model.createNLL(MinimumData)->getVal();
   cout << "ReferenceNLL = " << ReferenceNLL << endl;

   // Generate toy datasets and evaluate log likelihood difference
   RooArgSet Observables(TotalNumber);
   vector<double> SBBaseSamples;
   SBBaseSamples.reserve(BaseSampleCount);
   cout << "Start generating S+B base sample" << endl;
   for(int i = 0; i < BaseSampleCount; i++)
   {
      BackgroundCount.setVal(B);
      RooDataSet *ToyDataSetB = (RooDataSet *)Model1->generate(RooArgSet(BackgroundCount), 1);
      BackgroundCount.setVal(((RooRealVar *)ToyDataSetB->get(0)->find("BackgroundCount"))->getVal());
      SignalCount.setVal(S);
      RooDataSet *ToyDataSetS = (RooDataSet *)Model2->generate(RooArgSet(SignalCount), 1);
      SignalCount.setVal(((RooRealVar *)ToyDataSetS->get(0)->find("SignalCount"))->getVal());      
      RooDataSet *ToyDataSet = (RooDataSet *)Model.generate(Observables, 1);
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      SBBaseSamples.push_back(ToyNLL - ReferenceNLL);
      delete NLLVar;
      delete ToyDataSet;
      delete ToyDataSetS;
      delete ToyDataSetB;
   }
   sort(SBBaseSamples.begin(), SBBaseSamples.end());

   vector<double> BBaseSamples;
   BBaseSamples.reserve(BaseSampleCount);
   cout << "Start generating B base sample" << endl;
   for(int i = 0; i < BaseSampleCount; i++)
   {
      BackgroundCount.setVal(B);
      RooDataSet *ToyDataSetB = (RooDataSet *)Model1->generate(RooArgSet(BackgroundCount), 1);
      BackgroundCount.setVal(((RooRealVar *)ToyDataSetB->get(0)->find("BackgroundCount"))->getVal());
      RooDataSet *ToyDataSet = (RooDataSet *)BModel.generate(Observables, 1);
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      BBaseSamples.push_back(ToyNLL - ReferenceNLL);
      delete NLLVar;
      delete ToyDataSet;
      delete ToyDataSetB;
   }
   sort(BBaseSamples.begin(), BBaseSamples.end());

   vector<double> SBSamples;
   SBSamples.reserve(NumberOfTries);
   cout << "Start generating S+B sample" << endl;
   for(int i = 0; i < NumberOfTries; i++)
   {
      BackgroundCount.setVal(B);
      RooDataSet *ToyDataSetB = (RooDataSet *)Model1->generate(RooArgSet(BackgroundCount), 1);
      BackgroundCount.setVal(((RooRealVar *)ToyDataSetB->get(0)->find("BackgroundCount"))->getVal());
      SignalCount.setVal(S);
      RooDataSet *ToyDataSetS = (RooDataSet *)Model2->generate(RooArgSet(SignalCount), 1);
      SignalCount.setVal(((RooRealVar *)ToyDataSetS->get(0)->find("SignalCount"))->getVal());      
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
      delete ToyDataSetS;
      delete ToyDataSetB;
   }

   vector<double> BSamples;
   BSamples.reserve(NumberOfTries);
   cout << "Start generating B sample" << endl;
   for(int i = 0; i < NumberOfTries; i++)
   {
      BackgroundCount.setVal(B);
      RooDataSet *ToyDataSetB = (RooDataSet *)Model1->generate(RooArgSet(BackgroundCount), 1);
      BackgroundCount.setVal(((RooRealVar *)ToyDataSetB->get(0)->find("BackgroundCount"))->getVal());
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
      delete ToyDataSetB;
   }

   // Calculate p-value distributions
   vector<double> SBPValues;
   vector<double> BPValues;
   vector<double> CLsValues;
   vector<double> BadCLsValues;
   for(int i = 0; i < NumberOfTries; i++)
   {
      SBPValues.push_back(EstimatePValue(SBSamples[i], SBBaseSamples));
      BPValues.push_back(EstimatePValue(BSamples[i], SBBaseSamples));
      CLsValues.push_back(BPValues[i] / EstimatePValue(BSamples[i], BBaseSamples));
      BadCLsValues.push_back(BPValues[i] / SBPValues[i]);
   }
   for(int i = 0; i < NumberOfTries; i++)
   {
      HSBPValues.Fill(SBPValues[i]);
      HBPValues.Fill(BPValues[i]);
      HCLs.Fill(CLsValues[i]);
      HBadCLs.Fill(BadCLsValues[i]);
   }

   sort(SBPValues.begin(), SBPValues.end());
   sort(BPValues.begin(), BPValues.end());
   sort(CLsValues.begin(), CLsValues.end());
   sort(BadCLsValues.begin(), BadCLsValues.end());

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

   cout << "Median p(s+b,s+b) = " << SBPValues[Median] << endl;
   cout << "-1 sigma p(s+b,s+b) = " << SBPValues[SigmaDown] << endl;
   cout << "+1 sigma p(s+b,s+b) = " << SBPValues[SigmaUp] << endl;

   cout << "Median p(b,s+b) = " << BPValues[Median] << endl;
   cout << "-1 sigma p(b,s+b) = " << BPValues[SigmaDown] << endl;
   cout << "+1 sigma p(b,s+b) = " << BPValues[SigmaUp] << endl;

   cout << "Median CLs = " << CLsValues[Median] << endl;
   cout << "-1 sigma CLs = " << CLsValues[SigmaDown] << endl;
   cout << "+1 sigma CLs = " << CLsValues[SigmaUp] << endl;

   cout << "Median bad CLs = " << BadCLsValues[Median] << endl;
   cout << "-1 sigma bad CLs = " << BadCLsValues[SigmaDown] << endl;
   cout << "+1 sigma bad CLs = " << BadCLsValues[SigmaUp] << endl;

   delete Model1, Model2;

   RooMsgService::instance().setGlobalKillBelow(level);

   ValuesForLimit Result;

   Result.SBValues[0] = SBPValues[SigmaDown];
   Result.SBValues[1] = SBPValues[Median];
   Result.SBValues[2] = SBPValues[SigmaUp];

   Result.BValues[0] = BPValues[SigmaDown];
   Result.BValues[1] = BPValues[Median];
   Result.BValues[2] = BPValues[SigmaUp];

   Result.CLsValues[0] = CLsValues[SigmaDown];
   Result.CLsValues[1] = CLsValues[Median];
   Result.CLsValues[2] = CLsValues[SigmaUp];

   Result.BadCLsValues[0] = BadCLsValues[SigmaDown];
   Result.BadCLsValues[1] = BadCLsValues[Median];
   Result.BadCLsValues[2] = BadCLsValues[SigmaUp];

   Result.S = S;
   Result.SError = SError;

   return Result;
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




