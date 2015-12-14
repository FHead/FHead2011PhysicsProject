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
#include "RooLognormal.h"
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
   
   Results.push_back(PlotStatistics(PsFile, 274.45 * 1.05, 23.28 * 1.05,
      90.2, 90.2 * SignalRelativeError, 274.45 * 1.05 + 90.2, true));

   // double SignalRelativeError = 0.125;
   for(double S = 30; S <= 87.5; S = S + 5)
   {
      if(S > 79.9 && S < 80.1)
         S = S + 0.1;
      Results.push_back(PlotStatistics(PsFile, 274.45 * 1.05, 23.28 * 1.05,
         S, S * SignalRelativeError, 274.45 * 1.05 + S, true));
   }
   Results.push_back(Results[0]);
   Results.erase(Results.begin());

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

   TLegend Legend(0.15, 0.15, 0.55, 0.35);
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

   TCanvas CLsCanvasSquare("CLsCanvasSquare", "", 1024, 1024);
   TH1D HWorld("HWorld", "Expected CLs Value", 10, 25, 95);
   HWorld.GetXaxis()->SetTitle("Signal count");
   HWorld.GetYaxis()->SetTitle("CLs");
   HWorld.SetMinimum(0.002);
   HWorld.SetMaximum(1.000);
   HWorld.SetStats(0);
   HWorld.Draw();
   CLsMedianGraph.SetLineWidth(2);
   CLsMedianGraph.Draw("pl");
   CLsPlusGraph.SetLineWidth(2);
   CLsPlusGraph.Draw("pl");
   CLsMinusGraph.SetLineWidth(2);
   CLsMinusGraph.Draw("pl");
   FivePercentLine.Draw("l");
   Legend.Draw();
   CLsCanvasSquare.SaveAs("CLsPlot.png");
   CLsCanvasSquare.SaveAs("CLsPlot.C");
   CLsCanvasSquare.SaveAs("CLsPlot.eps");
   CLsCanvasSquare.SaveAs("CLsPlot.pdf");
   CLsCanvasSquare.SetLogy();
   CLsCanvasSquare.SaveAs("CLsPlotLog.png");
   CLsCanvasSquare.SaveAs("CLsPlotLog.C");
   CLsCanvasSquare.SaveAs("CLsPlotLog.eps");
   CLsCanvasSquare.SaveAs("CLsPlotLog.pdf");
 
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
   PsFile.AddTextPage(Form("Start running point with S = %.2f +- %.2f", S, SigmaS));

   const int NumberOfTries = 10000;
   const int BaseSampleCount = 10000;

   cout << "Starting function with B = " << B << " +- " << SigmaB
      << ", S = " << S << " +- " << SigmaS
      << ", Total = " << Total << " " << endl;

   MsgLevel level = RooMsgService::instance().globalKillBelow();
   RooMsgService::instance().setGlobalKillBelow(ERROR);

   TH1D HLogLikelihoodRatio("HLogLikelihoodRatio", "Log likelihood ratio (S+B on S+B)", 100, 0, 30);
   TH1D HToyDistribution("HToyDistribution", "Toy distribution", 150, 0, 600);
   TH1D HBDistribution("HBDistribution", "B distribution", 150, 0, 600);
   TH1D HBPriorDistribution("HBPriorDistribution", "B prior distribution", 150, 0, 600);
   TH1D HBLikelihoodRatio("HBLikelihoodRatio", "B likelihood ratio", 100, 0, 30);
   TH1D HSBPValues("HSBPValues", "p-value distribution on S+B model", 100, 0, 1);
   TH1D HBPValues("HBPValues", "p-value distribution on B model", 100, 0, 1);
   TH1D HBPValuesOnB("HBPValuesOnB", "p-value distribution on B model evaluated with B model", 100, 0, 1);
   TH1D HCLs("HCLs", "CLs distribution for this set of models", 100, 0, 5);
   TH1D HBadCLs("HBadCLs", "Bad CLs distribution for this set of models", 100, 0, 5);

   double BValue = B;
   double BError = SigmaB;
   double SValue = S;
   double SError = SigmaS;
   if(LogNormal == true)
   {
      BError = SigmaB / B + 1;
      SError = SigmaS / S + 1;
   }

   RooRealVar BackgroundPrediction("BackgroundPrediction", "BackgroundPrediction", BValue);
   RooRealVar BackgroundError("BackgroundError", "BackgroundError", BError);
   RooRealVar BackgroundCount("BackgroundCount", "event count", BValue, 0, 10000);

   RooRealVar SignalPrediction("SignalPrediction", "SignalPrediction", SValue);
   RooRealVar SignalError("SignalError", "SignalError", SError);
   RooRealVar SignalCount("SignalCount", "event count", SValue, 0, 10000);

   RooRealVar TotalNumber("TotalNumber", "TotalNumber", Total, 0, 100000);
   RooFormulaVar TotalCount("TotalCount", "event count", "BackgroundCount + SignalCount",
      RooArgList(BackgroundCount, SignalCount));

   RooFormulaVar LogBackgroundCount("LogBackgroundCount", "log(count)",
      "log(BackgroundCount)", RooArgList(BackgroundCount));
   RooFormulaVar LogSignalCount("LogSignalCount", "log(count)", "log(SignalCount)", RooArgList(SignalCount));
   
   RooAbsPdf *Model1, *Model2;
   if(LogNormal == false)
   {
      Model1 = new RooGaussian("Model1", "model1", BackgroundCount, BackgroundPrediction, BackgroundError);
      Model2 = new RooGaussian("Model2", "model2", SignalCount, SignalPrediction, SignalError);
   }
   else
   {
      Model1 = new RooLognormal("Model1", "model1", BackgroundCount, BackgroundPrediction, BackgroundError);
      Model2 = new RooLognormal("Model2", "model2", SignalCount, SignalPrediction, SignalError);
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
      // if((i + 1) % 2500 == 0)
      //    cout << i + 1 << endl;

      BackgroundCount.setVal(B);
      RooDataSet *ToyDataSetB = (RooDataSet *)Model1->generate(RooArgSet(BackgroundCount), 1);
      const RooArgSet *BSet = ToyDataSetB->get(0);
      const RooRealVar *BVar = (RooRealVar *)BSet->find("BackgroundCount");
      BackgroundCount.setVal(BVar->getVal());
   
      SignalCount.setVal(S);
      RooDataSet *ToyDataSetS = (RooDataSet *)Model2->generate(RooArgSet(SignalCount), 1);
      const RooArgSet *SSet = ToyDataSetS->get(0);
      const RooRealVar *SVar = (RooRealVar *)SSet->find("SignalCount");
      SignalCount.setVal(SVar->getVal());      
   
      RooDataSet *ToyDataSet = (RooDataSet *)Model.generate(Observables, 1);
   
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      RooAbsReal *Profile = NLLVar->createProfile(RooArgSet());
      Profile->getVal();
      double ToyNLL = NLLVar->getVal();
      // cout << SignalCount.getVal() << endl;
      if(SignalCount.getVal() > S)
         ToyNLL = ReferenceNLL;
      
      SBBaseSamples.push_back(ToyNLL - ReferenceNLL);
      delete Profile;
      delete NLLVar;
      delete ToyDataSet;
      delete SSet;
      delete ToyDataSetS;
      delete BSet;
      delete ToyDataSetB;
   }
   sort(SBBaseSamples.begin(), SBBaseSamples.end());

   vector<double> BBaseSamples;
   BBaseSamples.reserve(BaseSampleCount);
   cout << "Start generating B base sample" << endl;
   for(int i = 0; i < BaseSampleCount; i++)
   {
      // if((i + 1) % 2500 == 0)
      //    cout << i + 1 << endl;

      BackgroundCount.setVal(B);
      RooDataSet *ToyDataSetB = (RooDataSet *)Model1->generate(RooArgSet(BackgroundCount), 1);
      BackgroundCount.setVal(((RooRealVar *)ToyDataSetB->get(0)->find("BackgroundCount"))->getVal());

      HBPriorDistribution.Fill(BackgroundCount.getVal());
      RooDataSet *ToyDataSet = (RooDataSet *)BModel.generate(Observables, 1);
      BackgroundCount.setVal(B);

      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      
      RooAbsReal *Profile = NLLVar->createProfile(RooArgSet());
      Profile->getVal();
      double ToyNLL = NLLVar->getVal();
      BBaseSamples.push_back(ToyNLL - ReferenceNLL);
      
      delete Profile;
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
      // if((i + 1) % 2500 == 0)
      //    cout << i + 1 << endl;

      BackgroundCount.setVal(B);
      RooDataSet *ToyDataSetB = (RooDataSet *)Model1->generate(RooArgSet(BackgroundCount), 1);
      BackgroundCount.setVal(((RooRealVar *)ToyDataSetB->get(0)->find("BackgroundCount"))->getVal());
      
      SignalCount.setVal(S);
      RooDataSet *ToyDataSetS = (RooDataSet *)Model2->generate(RooArgSet(SignalCount), 1);
      SignalCount.setVal(((RooRealVar *)ToyDataSetS->get(0)->find("SignalCount"))->getVal());      
      
      RooDataSet *ToyDataSet = (RooDataSet *)Model.generate(Observables, 1);
      
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      RooAbsReal *Profile = NLLVar->createProfile(RooArgSet());
      Profile->getVal();
      double ToyNLL = NLLVar->getVal();
      if(SignalCount.getVal() > S)
         ToyNLL = ReferenceNLL;
      
      HLogLikelihoodRatio.Fill(ToyNLL - ReferenceNLL);
      
      const RooArgSet *Set = ToyDataSet->get(0);
      double SBCount = ((const RooRealVar *)Set->find("TotalNumber"))->getVal();
      HToyDistribution.Fill(SBCount);
      SBSamples.push_back(ToyNLL - ReferenceNLL);
      
      delete Set;
      delete Profile;
      delete NLLVar;
      delete ToyDataSet;
      delete ToyDataSetS;
      delete ToyDataSetB;
   }
   sort(SBSamples.begin(), SBSamples.end());

   vector<double> BSamples;
   BSamples.reserve(NumberOfTries);
   cout << "Start generating B sample" << endl;
   for(int i = 0; i < NumberOfTries; i++)
   {
      // if((i + 1) % 2500 == 0)
      //    cout << i + 1 << endl;

      BackgroundCount.setVal(B);
      RooDataSet *ToyDataSetB = (RooDataSet *)Model1->generate(RooArgSet(BackgroundCount), 1);
      BackgroundCount.setVal(((RooRealVar *)ToyDataSetB->get(0)->find("BackgroundCount"))->getVal());
      
      RooDataSet *ToyDataSet = (RooDataSet *)BModel.generate(Observables, 1);
      BackgroundCount.setVal(B);
      
      RooAbsReal *NLLVar = Model.createNLL(*ToyDataSet);
      RooAbsReal *Profile = NLLVar->createProfile(RooArgSet());
      Profile->getVal();
      double ToyNLL = NLLVar->getVal();
      HBLikelihoodRatio.Fill(ToyNLL - ReferenceNLL);
      
      const RooArgSet *Set = ToyDataSet->get(0);
      double SBCount = ((const RooRealVar *)Set->find("TotalNumber"))->getVal();
      HBDistribution.Fill(SBCount);
      BSamples.push_back(ToyNLL - ReferenceNLL);
      
      delete Set;
      delete Profile;
      delete NLLVar;
      delete ToyDataSet;
      delete ToyDataSetB;
   }
   sort(BSamples.begin(), BSamples.end());

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
      HBPValuesOnB.Fill(EstimatePValue(BSamples[i], BBaseSamples));
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
   PsFile.AddPlot(HBPriorDistribution, "", true);
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

   TCanvas CSquare("CSquare", "", 1024, 1024);
   HLogLikelihoodRatio.GetXaxis()->SetTitle("#Lambda");
   HLogLikelihoodRatio.Draw();
   HBLikelihoodRatio.Draw("same");
   legend.Draw();
   CSquare.SetLogy();
   CSquare.SaveAs(Form("LikelihoodRatioPlot_%d.png", (int)S));
   CSquare.SaveAs(Form("LikelihoodRatioPlot_%d.C", (int)S));
   CSquare.SaveAs(Form("LikelihoodRatioPlot_%d.eps", (int)S));
   CSquare.SaveAs(Form("LikelihoodRatioPlot_%d.pdf", (int)S));

   HSBPValues.SetMinimum(0.1);
   PsFile.AddPlot(HSBPValues, "", false);
   PsFile.AddPlot(HSBPValues, "", true);
   HBPValues.SetMinimum(0.1);
   PsFile.AddPlot(HBPValues, "", false);
   PsFile.AddPlot(HBPValues, "", true);
   HBPValuesOnB.SetMinimum(0.1);
   PsFile.AddPlot(HBPValuesOnB, "", false);
   PsFile.AddPlot(HBPValuesOnB, "", true);
   HCLs.SetMinimum(0.1);
   PsFile.AddPlot(HCLs, "", false);
   PsFile.AddPlot(HCLs, "", true);

   int Median = (int)(NumberOfTries / 2);   // not exactly; number is even, but, ok
   int SigmaDown = (int)(NumberOfTries * (1 - 0.682689492137) / 2);
   int SigmaUp = (int)(NumberOfTries * (1 + 0.682689492137) / 2);

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

   double CountAbove = (double)Samples.size() - MaxIndex;
   return CountAbove / Samples.size();
}




