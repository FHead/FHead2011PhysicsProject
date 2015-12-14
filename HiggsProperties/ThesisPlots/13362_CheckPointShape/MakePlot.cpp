#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisBigStyle();

   TFile F1("A1ZZ_2e2mu_Smeared_2.root");
   TFile F2("A1ZZ_2e2mu_Smeared_1.root");
   TFile F3("A1ZZ_2e2mu_Smeared_0.root");
   TFile F4("A1ZZ_2e2mu_Smeared_-1.root");
   TFile F5("A1ZZ_2e2mu_Smeared_-2.root");

   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("Tree");
   TTree *T3 = (TTree *)F3.Get("Tree");
   TTree *T4 = (TTree *)F4.Get("Tree");
   TTree *T5 = (TTree *)F5.Get("Tree");

   TH1D H1("H1", ";m_{1};a.u.", 100, 40, 110);
   TH1D H2("H2", ";m_{1};a.u.", 100, 40, 110);
   TH1D H3("H3", ";m_{1};a.u.", 100, 40, 110);
   TH1D H4("H4", ";m_{1};a.u.", 100, 40, 110);
   TH1D H5("H5", ";m_{1};a.u.", 100, 40, 110);

   T1->Draw("sqrt(2*L1PT*L2PT)*sqrt(cosh(L1Eta-L2Eta)-cos(L1Phi-L2Phi))>>H1");
   T2->Draw("sqrt(2*L1PT*L2PT)*sqrt(cosh(L1Eta-L2Eta)-cos(L1Phi-L2Phi))>>H2");
   T3->Draw("sqrt(2*L1PT*L2PT)*sqrt(cosh(L1Eta-L2Eta)-cos(L1Phi-L2Phi))>>H3");
   T4->Draw("sqrt(2*L1PT*L2PT)*sqrt(cosh(L1Eta-L2Eta)-cos(L1Phi-L2Phi))>>H4");
   T5->Draw("sqrt(2*L1PT*L2PT)*sqrt(cosh(L1Eta-L2Eta)-cos(L1Phi-L2Phi))>>H5");

   H1.Scale(1/H1.Integral());
   H2.Scale(1/H2.Integral());
   H3.Scale(1/H3.Integral());
   H4.Scale(1/H4.Integral());
   H5.Scale(1/H5.Integral());

   H1.SetStats(0);
   H1.SetMaximum(0.1);

   H1.SetLineColor(kBlack);
   H2.SetLineColor(kBlue);
   H3.SetLineColor(kGreen - 3);
   H4.SetLineColor(kRed);
   H5.SetLineColor(kYellow + 3);

   H1.SetLineWidth(2);
   H2.SetLineWidth(2);
   H3.SetLineWidth(2);
   H4.SetLineWidth(2);
   H5.SetLineWidth(2);

   TCanvas C;

   H1.Draw();
   H2.Draw("same");
   H3.Draw("same");
   H4.Draw("same");
   H5.Draw("same");

   double x1, x2, y1, y2;
   x1 = ThesisNDCMappingBigX(0.2);
   x2 = ThesisNDCMappingBigX(0.5);
   y1 = ThesisNDCMappingBigY(0.8);
   y2 = ThesisNDCMappingBigY(0.5);

   TLegend Legend(x1, y1, x2, y2);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&H1, "-2 #sigma", "l");
   Legend.AddEntry(&H2, "-1 #sigma", "l");
   Legend.AddEntry(&H3, " 0 #sigma", "l");
   Legend.AddEntry(&H4, "+1 #sigma", "l");
   Legend.AddEntry(&H5, "+2 #sigma", "l");
   Legend.Draw();

   C.SaveAs("MultiDimensionalDetails-Systematics-CheckPointExample.png");
   C.SaveAs("MultiDimensionalDetails-Systematics-CheckPointExample.C");
   C.SaveAs("MultiDimensionalDetails-Systematics-CheckPointExample.eps");
   C.SaveAs("MultiDimensionalDetails-Systematics-CheckPointExample.pdf");

   return 0;
}








