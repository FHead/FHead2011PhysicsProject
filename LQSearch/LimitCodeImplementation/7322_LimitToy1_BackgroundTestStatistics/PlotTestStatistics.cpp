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
using namespace RooFit;

#include "PlotHelper2.h"

int main();
TH1D *PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB, bool LogNormal = false);

int main()
{
   PsFileHelper PsFile("LimitToy1_Result.ps");
   PsFile.AddTextPage("Test statistics distribution of background-only model");

   PsFile.AddTextPage("Gaussian modeling");
   
   TH1D *H[5];
   H[0] = PlotStatistics(PsFile, 10, 1);
   H[1] = PlotStatistics(PsFile, 10, sqrt(10));
   H[2] = PlotStatistics(PsFile, 10, 10);
   H[3] = PlotStatistics(PsFile, 10, 20);
   H[4] = PlotStatistics(PsFile, 10, 50);
   
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
   
   TH1D *G[5];
   G[0] = PlotStatistics(PsFile, 10, 10);
   G[1] = PlotStatistics(PsFile, 20, 10);
   G[2] = PlotStatistics(PsFile, 40, 10);
   G[3] = PlotStatistics(PsFile, 80, 10);
   G[4] = PlotStatistics(PsFile, 160, 10);

   TCanvas Canvas2;
   for(int i = 0; i < 5; i++)
   {
      G[i]->SetStats(0);
      G[i]->SetLineColor(i + 1);
      if(i == 0)
         G[i]->Draw();
      else
         G[i]->Draw("same");
   }
   Canvas2.SetLogy();
   PsFile.AddCanvas(Canvas2);

   PsFile.AddTextPage("Log-normal modeling");

   TH1D *I[7];
   I[0] = PlotStatistics(PsFile, 10, 1, true);
   I[1] = PlotStatistics(PsFile, 10, 2, true);
   I[2] = PlotStatistics(PsFile, 10, 4, true);
   I[3] = PlotStatistics(PsFile, 10, 8, true);
   I[4] = PlotStatistics(PsFile, 10, 16, true);
   I[5] = PlotStatistics(PsFile, 10, 24, true);
   I[6] = PlotStatistics(PsFile, 10, 32, true);
   
   TCanvas Canvas3;
   for(int i = 0; i < 7; i++)
   {
      I[i]->SetStats(0);
      I[i]->SetLineColor(i + 1);
      if(i == 0)
         I[i]->Draw();
      else
         I[i]->Draw("same");
   }
   Canvas3.SetLogy();
   PsFile.AddCanvas(Canvas3);

   PsFile.Close();

   for(int i = 0; i < 5; i++)
      delete H[i];
   for(int i = 0; i < 5; i++)
      delete G[i];
   for(int i = 0; i < 7; i++)
      delete I[i];

   return 0;
}

TH1D *PlotStatistics(PsFileHelper &PsFile, double B, double SigmaB, bool LogNormal)
{
   MsgLevel level = RooMsgService::instance().globalKillBelow();
   RooMsgService::instance().setGlobalKillBelow(ERROR);

   static int HistogramIndex = 0;
   HistogramIndex = HistogramIndex + 1;
   
   TH1D *HLogLikelihoodRatio = new TH1D(Form("HLogLikelihoodRatio%d", HistogramIndex),
      Form("Log likelihood ratio for B = %f +- %f", B, SigmaB), 100, 0, 10);
   TH1D HToyDistribution("HToyDistribution", Form("Toy distribution, B = %f +- %f", B, SigmaB),
      100, B - SigmaB * 5, B + SigmaB * 5);
   TH2D HDataVsNLL("HDataVsNLL",
      Form("Data vs. likelihood ratio;data;log likelihood ratio, B = %f +- %f", B, SigmaB),
      100, B - SigmaB * 5, B + SigmaB * 5, 100, 0, 10);

   double BValue = B;
   double BError = SigmaB;
   if(LogNormal == true)
   {
      BValue = log(B);
      BError = SigmaB / B;
   }

   RooRealVar BackgroundPrediction("BackgroundPrediction", "BackgroundPrediction", BValue);
   RooRealVar BackgroundError("BackgroundError", "BackgroundError", BError);
   RooRealVar Count("Count", "event count", 0, B * 10000 + SigmaB * 10000);
   RooFormulaVar LogCount("LogCount", "log(count)", "log(Count)", RooArgList(Count));
   RooGaussian *Model;
   if(LogNormal == false)
      Model = new RooGaussian("Model", "model", Count, BackgroundPrediction, BackgroundError);
   else
      Model = new RooGaussian("Model", "model", LogCount, BackgroundPrediction, BackgroundError);

   RooArgSet Observables(Count);

   // Get minimum LL
   RooDataSet MinimumData("MinimumData", "Data at minimum", Observables);
   Count.setVal(B);
   MinimumData.add(Observables);
   double MinNLL = Model->createNLL(MinimumData)->getVal();
   cout << "MinNLL = " << MinNLL << endl;

   // Generate toy datasets and evaluate log likelihood difference
   for(int i = 0; i < 10000; i++)
   {
      RooDataSet *ToyDataSet = (RooDataSet *)Model->generate(Observables, 1);
      RooAbsReal *NLLVar = Model->createNLL(*ToyDataSet);
      double ToyNLL = NLLVar->getVal();
      HLogLikelihoodRatio->Fill(ToyNLL - MinNLL);
      const RooArgSet *Set = ToyDataSet->get(0);
      HToyDistribution.Fill(((const RooRealVar *)Set->find("Count"))->getVal());
      HDataVsNLL.Fill(((const RooRealVar *)Set->find("Count"))->getVal(), ToyNLL - MinNLL);
      // cout << ((const RooRealVar *)Set->find("Count"))->getVal() << endl;
      delete ToyDataSet;
      delete NLLVar;
   }

   PsFile.AddPlot(HToyDistribution, "", true);
   // PsFile.AddPlot(HLogLikelihoodRatio, "");
   PsFile.AddPlot(HLogLikelihoodRatio, "", true);
   PsFile.AddPlot(HDataVsNLL, "colz", false, true);

   delete Model;

   RooMsgService::instance().setGlobalKillBelow(level);
   
   return HLogLikelihoodRatio;
}

