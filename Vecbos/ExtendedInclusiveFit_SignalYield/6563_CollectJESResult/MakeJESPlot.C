#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

void MakeJESPlot(string Threshold = "30")
{
   vector<RooFitResult *> Results;

   TFile F1(("Normal/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F2(("Minus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F3(("Plus/ResultFileW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F1.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F2.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F3.Get("UnconstrainedFitResult"));

   TH1D NormalHistogram("HNormalHistogram", ";Inclusive numer of jets;Events", 5, 0, 5);
   TH1D MinusHistogram("HMinusHistogram", ";Inclusive numer of jets;Events", 5, 0, 5);
   TH1D PlusHistogram("HPlusHistogram", ";Inclusive numer of jets;Events", 5, 0, 5);

   for(int j = 0; j <= 4; j++)
   {
      double NormalValue =
         ((RooRealVar *)(Results[0]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
      double NormalError =
         ((RooRealVar *)(Results[0]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getError();
      double MinusValue =
         ((RooRealVar *)(Results[1]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
      double PlusValue =
         ((RooRealVar *)(Results[2]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();

      NormalHistogram.SetBinContent(j + 1, NormalValue);
      NormalHistogram.SetBinError(j + 1, NormalError);
      MinusHistogram.SetBinContent(j + 1, MinusValue);
      PlusHistogram.SetBinContent(j + 1, PlusValue);
   }

   TCanvas Canvas("C", "C");

   PlusHistogram.SetStats(0);
   PlusHistogram.SetFillColor(kBlue);
   PlusHistogram.Draw("bar");
   
   MinusHistogram.SetStats(0);
   MinusHistogram.SetFillColor(kWhite);
   MinusHistogram.Draw("bar same");

   NormalHistogram.SetStats(0);
   NormalHistogram.SetLineColor(kRed);
   NormalHistogram.Draw("hist error same");

   Canvas.SetLogy();
   Canvas.SaveAs(("JES_" + Threshold + ".png").c_str());
   Canvas.SaveAs(("JES_" + Threshold + ".eps").c_str());
   Canvas.SaveAs(("JES_" + Threshold + ".C").c_str());
         
   F3.Close();
   F2.Close();
   F1.Close();
}



