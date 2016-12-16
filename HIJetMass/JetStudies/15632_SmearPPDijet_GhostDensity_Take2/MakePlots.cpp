#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetStyle();

   TFile F1("ScaledResult_001/PP6Dijet.root");
   TFile F2("ScaledResult_002/PP6Dijet.root");
   TFile F3("ScaledResult_004/PP6Dijet.root");
   TFile F4("ScaledResult_007/PP6Dijet.root");
   TFile F5("ScaledResult_010/PP6Dijet.root");

   TH1D *H1 = (TH1D *)F1.Get("HNewSDMass");
   TH1D *H2 = (TH1D *)F2.Get("HNewSDMass");
   TH1D *H3 = (TH1D *)F3.Get("HNewSDMass");
   TH1D *H4 = (TH1D *)F4.Get("HNewSDMass");
   TH1D *H5 = (TH1D *)F5.Get("HNewSDMass");

   TCanvas Canvas;

   H1->SetLineColor(kBlack);
   H2->SetLineColor(kRed);
   H3->SetLineColor(kBlue);
   H4->SetLineColor(kGreen);
   H5->SetLineColor(kYellow + 3);

   H1->Rebin(2);
   H2->Rebin(2);
   H3->Rebin(2);
   H4->Rebin(2);
   H5->Rebin(2);

   H1->Draw();
   H2->Draw("same");
   H3->Draw("same");
   H4->Draw("same");
   H5->Draw("same");

   Canvas.SaveAs("NewSDMassComparison.png");
   Canvas.SaveAs("NewSDMassComparison.C");
   Canvas.SaveAs("NewSDMassComparison.eps");
   Canvas.SaveAs("NewSDMassComparison.pdf");

   F5.Close();
   F4.Close();
   F3.Close();
   F2.Close();
   F1.Close();

   return 0;
}





