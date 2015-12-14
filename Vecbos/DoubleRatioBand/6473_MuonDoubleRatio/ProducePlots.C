#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
using namespace RooFit;

#include "PlotHelper.h"

#include "CalculateBand.h"

void ProducePlots();
void ProducePlots(RooFitResult *WUnconstrained, RooFitResult *WConstrained,
   RooFitResult *ZUnconstrained, RooFitResult *ZConstrained);

void ProducePlots()
{
   TFile FWUnconstrained("WmunuUnconstrained_PF30.root");
   TFile FZUnconstrained("ResultFile_pf_30.root");
   TFile FWConstrained("combined-sim-poly.root");
   TFile FZConstrained("Result_PF30_Constrained.root");

   RooFitResult *WUnconstrained = (RooFitResult *)FWUnconstrained.Get("nll_myFit_data");
   RooFitResult *ZUnconstrained = (RooFitResult *)FZUnconstrained.Get("UnconstrainedFitResult");
   RooFitResult *WConstrained = (RooFitResult *)FWConstrained.Get("nll_myFit_data");
   RooFitResult *ZConstrained = (RooFitResult *)FZConstrained.Get("ConstrainedResult");

   ProducePlots(WUnconstrained, WConstrained, ZUnconstrained, ZConstrained);

   FZConstrained.Close();
   FWConstrained.Close();
   FZUnconstrained.Close();
   FWUnconstrained.Close();
}

void ProducePlots(RooFitResult *WUnconstrained, RooFitResult *WConstrained,
   RooFitResult *ZUnconstrained, RooFitResult *ZConstrained)
{
   // Output file!
   PsFileHelper PsFile("DoubleRatioPlots.ps");
   PsFile.AddTextPage("Double-ratio plots!");

   // Short explanation of plots that follow
   vector<string> Texts;
   Texts.push_back("Quick overview of plots:");
   Texts.push_back("   W inclusive yields: from unconstrained fit");
   Texts.push_back("   W inclusive ratio: from unconstrained fit, divide yields directly");
   Texts.push_back("   Z inclusive yields: from unconstrained fit");
   Texts.push_back("   Z inclusive ratio: from unconstrained fit, divide yields directly");
   Texts.push_back("   W/Z inclusive ratio: from unconstrained fit, assuming W/Z independent");
   Texts.push_back("   Polynomial ratio band: from constrained fit, dividing polynomials");
   Texts.push_back("   Double-ratio from inclusive yields: divide unconstrained ratio");
   Texts.push_back("   Last: overlay of band and points (previous two pages)");
   PsFile.AddTextPage(Texts);

   // Get inclusive yields for W
   TGraphErrors WInclusiveYields;
   WInclusiveYields.SetNameTitle("WInclusiveYields", "W inclusive yields");

   vector<string> WBinNames;
   WBinNames.push_back("N_sigInc_1j");
   WBinNames.push_back("N_sigInc_2j");
   WBinNames.push_back("N_sigInc_3j");
   WBinNames.push_back("N_sigInc_4j");

   for(int i = 0; i < 4; i++)
   {
      WInclusiveYields.SetPoint(i, i + 1,
         ((RooRealVar *)(WUnconstrained->floatParsFinal().find(WBinNames[i].c_str())))->getVal());
      WInclusiveYields.SetPointError(i, 0,
         ((RooRealVar *)(WUnconstrained->floatParsFinal().find(WBinNames[i].c_str())))->getError());
   }

   TCanvas WInclusiveYieldsCanvas("WInclusiveYieldsCanvas", "", 0, 0, 1024, 768);
   WInclusiveYields.Draw("ap");
   WInclusiveYields.GetXaxis()->SetTitle("Inclusive jet count (N)");
   WInclusiveYields.GetYaxis()->SetTitle("W+N Jet inclusive yield");
   WInclusiveYieldsCanvas.SetLogy();
   PsFile.AddCanvas(WInclusiveYieldsCanvas);
   
   // Get ratio for W
   TGraphErrors WInclusiveRatio;
   WInclusiveRatio.SetNameTitle("WInclusiveRatio", "W inclusive ratio");

   for(int i = 0; i < 3; i++)
   {
      double W1 = ((RooRealVar *)(WUnconstrained->floatParsFinal().find(WBinNames[i].c_str())))->getVal();
      double WError1 = ((RooRealVar *)(WUnconstrained->floatParsFinal().find(WBinNames[i].c_str())))->getError();
      double W2 = ((RooRealVar *)(WUnconstrained->floatParsFinal().find(WBinNames[i+1].c_str())))->getVal();
      double WError2 = ((RooRealVar *)(WUnconstrained->floatParsFinal().find(WBinNames[i+1].c_str())))->getError();
      double Correlation = WUnconstrained->correlation(WBinNames[i].c_str(), WBinNames[i+1].c_str());

      double Ratio = W1 / W2;
      double Error = Ratio * sqrt((WError1 / W1) * (WError1 / W1)
         + (WError2 / W2) * (WError2 / W2) - 2 * (WError1 / W1) * (WError2 / W2) * Correlation);

      WInclusiveRatio.SetPoint(i, i + 1, Ratio);
      WInclusiveRatio.SetPointError(i, 0, Error);
   }

   TCanvas WInclusiveRatioCanvas("WInclusiveRatioCanvas", "", 0, 0, 1024, 768);
   WInclusiveRatio.Draw("ap");
   WInclusiveRatio.GetXaxis()->SetTitle("Inclusive jet count (N)");
   WInclusiveRatio.GetYaxis()->SetTitle("#frac{W+N Jet}{W+(N+1) Jet}");
   PsFile.AddCanvas(WInclusiveRatioCanvas);

   // Get inclusive yields for Z
   TGraphErrors ZInclusiveYields;
   ZInclusiveYields.SetNameTitle("ZInclusiveYields", "Z inclusive yields");

   vector<string> ZBinNames;
   ZBinNames.push_back("SignalInclusiveYield1Jet");
   ZBinNames.push_back("SignalInclusiveYield2Jet");
   ZBinNames.push_back("SignalInclusiveYield3Jet");
   ZBinNames.push_back("SignalInclusiveYield4Jet");
   
   for(int i = 0; i < 4; i++)
   {
      ZInclusiveYields.SetPoint(i, i + 1,
         ((RooRealVar *)(ZUnconstrained->floatParsFinal().find(ZBinNames[i].c_str())))->getVal());
      ZInclusiveYields.SetPointError(i, 0,
         ((RooRealVar *)(ZUnconstrained->floatParsFinal().find(ZBinNames[i].c_str())))->getError());
   }
   
   TCanvas ZInclusiveYieldsCanvas("ZInclusiveYieldsCanvas", "", 0, 0, 1024, 768);
   ZInclusiveYields.Draw("ap");
   ZInclusiveYields.GetXaxis()->SetTitle("Inclusive jet count (N)");
   ZInclusiveYields.GetYaxis()->SetTitle("Z+N Jet inclusive yield");
   ZInclusiveYieldsCanvas.SetLogy();
   PsFile.AddCanvas(ZInclusiveYieldsCanvas);

   // Get ratio for Z
   TGraphErrors ZInclusiveRatio;
   ZInclusiveRatio.SetNameTitle("ZInclusiveRatio", "Z inclusive ratio");

   for(int i = 0; i < 3; i++)
   {
      double Z1 = ((RooRealVar *)(ZUnconstrained->floatParsFinal().find(ZBinNames[i].c_str())))->getVal();
      double ZError1 = ((RooRealVar *)(ZUnconstrained->floatParsFinal().find(ZBinNames[i].c_str())))->getError();
      double Z2 = ((RooRealVar *)(ZUnconstrained->floatParsFinal().find(ZBinNames[i+1].c_str())))->getVal();
      double ZError2 = ((RooRealVar *)(ZUnconstrained->floatParsFinal().find(ZBinNames[i+1].c_str())))->getError();
      double Correlation = ZUnconstrained->correlation(ZBinNames[i].c_str(), ZBinNames[i+1].c_str());

      double Ratio = Z1 / Z2;
      double Error = Ratio * sqrt((ZError1 / Z1) * (ZError1 / Z1)
         + (ZError2 / Z2) * (ZError2 / Z2) - 2 * (ZError1 / Z1) * (ZError2 / Z2) * Correlation);

      ZInclusiveRatio.SetPoint(i, i + 1, Ratio);
      ZInclusiveRatio.SetPointError(i, 0, Error);
   }

   TCanvas ZInclusiveRatioCanvas("ZInclusiveRatioCanvas", "", 0, 0, 1024, 768);
   ZInclusiveRatio.Draw("ap");
   ZInclusiveRatio.GetXaxis()->SetTitle("Inclusive jet count (N)");
   ZInclusiveRatio.GetYaxis()->SetTitle("#frac{Z+N Jet}{Z+(N+1) Jet}");
   PsFile.AddCanvas(ZInclusiveRatioCanvas);

   // Calculate inclusive ratio for W/Z assuming two numbers are uncorrelated
   TGraphErrors WZInclusiveRatio;
   WZInclusiveRatio.SetNameTitle("WZInclusiveRatio", "W/Z inclusive yield ratio");

   for(int i = 0; i < 4; i++)
   {
      double Dummy = 0;
      double Z = 1;
      double W = 1;
      double ZError = 0;
      double WError = 0;

      ZInclusiveYields.GetPoint(i, Dummy, Z);
      WInclusiveYields.GetPoint(i, Dummy, W);
      ZError = ZInclusiveYields.GetErrorY(i);
      WError = WInclusiveYields.GetErrorY(i);

      double Ratio = W / Z;
      double RatioError = Ratio * sqrt((ZError / Z) * (ZError / Z) + (WError / W) * (WError / W));

      WZInclusiveRatio.SetPoint(i, i + 1, Ratio);
      WZInclusiveRatio.SetPointError(i, 0, RatioError);
   }

   TCanvas WZInclusiveRatioCanvas("WZInclusiveRatioCanvas", "WZInclusiveRatioCanvas", 0, 0, 1024, 768);
   WZInclusiveRatio.Draw("ap");
   WZInclusiveRatio.GetXaxis()->SetTitle("Inclusive jet count");
   WZInclusiveRatio.GetYaxis()->SetTitle("Ratio of inclusive yields (W/Z)");
   PsFile.AddCanvas(WZInclusiveRatioCanvas);

   // calculate bands from constrained fits
   vector<string> Names;
   Names.push_back("alphaR_sigInc_");
   Names.push_back("betaR_sigInc_");
   Names.push_back("Alpha");
   Names.push_back("Beta");

   TGraphAsymmErrors ConstrainedRatioBandGraph = CalculateBand(WConstrained, ZConstrained, Names);
   ConstrainedRatioBandGraph.SetNameTitle("ConstrainedRatioBandGraph", "Polynomial ratio band from constrained fit");

   TCanvas ConstrainedRatioBandGraphCanvas("ConstrainedRatioBandGraphCanvas", "", 0, 0, 1024, 768);
   ConstrainedRatioBandGraph.Draw("apl");
   ConstrainedRatioBandGraph.GetXaxis()->SetTitle("Jet count (N)");
   ConstrainedRatioBandGraph.GetYaxis()->SetTitle("#frac{#alpha_{W} + #beta_{W} N}{#alpha_{Z} + #beta_{Z} N}");
   PsFile.AddCanvas(ConstrainedRatioBandGraphCanvas);

   // Get double-ratio plot
   TGraphErrors WZInclusiveDoubleRatio;
   WZInclusiveDoubleRatio.SetNameTitle("WZInclusiveDoubleRatio", "Double-ratio from inclusive yields");

   for(int i = 0; i < 3; i++)
   {
      double Dummy = 0;
      double W = 1;
      double WError = 1;
      double Z = 1;
      double ZError = 1;

      ZInclusiveRatio.GetPoint(i, Dummy, Z);
      WInclusiveRatio.GetPoint(i, Dummy, W);
      ZError = ZInclusiveRatio.GetErrorY(i);
      WError = WInclusiveRatio.GetErrorY(i);

      double DoubleRatio = W / Z;
      double DoubleRatioError = DoubleRatio * sqrt((ZError / Z) * (ZError / Z) + (WError / W) * (WError / W));

      WZInclusiveDoubleRatio.SetPoint(i, i + 1, DoubleRatio);
      WZInclusiveDoubleRatio.SetPointError(i, 0, DoubleRatioError);
   }

   TCanvas WZInclusiveDoubleRatioCanvas("WZInclusiveDoubleRatioCanvas",
      "WZInclusiveDoubleRatioCanvas", 0, 0, 1024, 768);
   WZInclusiveDoubleRatio.Draw("ap");
   WZInclusiveDoubleRatio.GetXaxis()->SetTitle("Jet count (N)");
   WZInclusiveDoubleRatio.GetYaxis()->SetTitle("Double ratio (#frac{(W+N Jet)/(W+(N+1) Jet)}{(Z+N Jet)/(Z+(N+1) Jet)})");
   PsFile.AddCanvas(WZInclusiveDoubleRatioCanvas);

   // overlay to get final plot
   TCanvas canvas("C", "C", 0, 0, 1024, 768);
   ConstrainedRatioBandGraph.SetFillStyle(3001);
   ConstrainedRatioBandGraph.SetFillColor(8);
   ConstrainedRatioBandGraph.SetLineColor(1);
   ConstrainedRatioBandGraph.SetLineWidth(1);
   ConstrainedRatioBandGraph.SetTitle("Double Ratio Summary Plot (W/Z)");
   ConstrainedRatioBandGraph.Draw("al3");
   ConstrainedRatioBandGraph.GetXaxis()->SetTitle("Jet count (N)");
   ConstrainedRatioBandGraph.GetYaxis()->SetTitle("Double ratio (#frac{(W+N Jet)/(W+(N+1) Jet)}{(Z+N Jet)/(Z+(N+1) Jet)})");
   WZInclusiveDoubleRatio.SetLineWidth(2);
   WZInclusiveDoubleRatio.Draw("p");
   PsFile.AddCanvas(canvas);

   canvas.SaveAs("DoubleRatioSummaryPlot.C");
   canvas.SaveAs("DoubleRatioSummaryPlot.png");
   canvas.SaveAs("DoubleRatioSummaryPlot.eps");

   PsFile.AddTimeStampPage();
   PsFile.Close();
}








