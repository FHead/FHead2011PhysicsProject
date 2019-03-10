#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "SetStyle.h"

#include "JetCorrector.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   JetCorrector JEC2017B("Fall17_17Nov2017B_V32_DATA_L2Residual_AK4PFchs.txt");
   JetCorrector JEC2017C("Fall17_17Nov2017C_V32_DATA_L2Residual_AK4PFchs.txt");
   JetCorrector JEC2017DE("Fall17_17Nov2017DE_V32_DATA_L2Residual_AK4PFchs.txt");
   JetCorrector JEC2017F("Fall17_17Nov2017F_V32_DATA_L2Residual_AK4PFchs.txt");
   JetCorrector JEC2018A("Autumn18_RunA_V5_DATA_L2Residual_AK4PFchs.txt");
   JetCorrector JEC2018B("Autumn18_RunB_V5_DATA_L2Residual_AK4PFchs.txt");
   JetCorrector JEC2018C("Autumn18_RunC_V5_DATA_L2Residual_AK4PFchs.txt");

   TH1D H2017B("H2017B", ";#eta;Correction", 1000, -5.2, 5.2);
   TH1D H2017C("H2017C", ";#eta;Correction", 1000, -5.2, 5.2);
   TH1D H2017DE("H2017DE", ";#eta;Correction", 1000, -5.2, 5.2);
   TH1D H2017F("H2017F", ";#eta;Correction", 1000, -5.2, 5.2);
   TH1D H2018A("H2018A", ";#eta;Correction", 1000, -5.2, 5.2);
   TH1D H2018B("H2018B", ";#eta;Correction", 1000, -5.2, 5.2);
   TH1D H2018C("H2018C", ";#eta;Correction", 1000, -5.2, 5.2);

   for(int i = 1; i <= 1000; i++)
   {
      double Eta = H2017B.GetXaxis()->GetBinCenter(i);
      double PT = 100;

      JEC2017B.SetJetEta(Eta);
      JEC2017B.SetJetPT(PT);
      JEC2017B.SetJetPhi(0);
      H2017B.SetBinContent(i, JEC2017B.GetCorrection());

      JEC2017C.SetJetEta(Eta);
      JEC2017C.SetJetPT(PT);
      JEC2017C.SetJetPhi(0);
      H2017C.SetBinContent(i, JEC2017C.GetCorrection());

      JEC2017DE.SetJetEta(Eta);
      JEC2017DE.SetJetPT(PT);
      JEC2017DE.SetJetPhi(0);
      H2017DE.SetBinContent(i, JEC2017DE.GetCorrection());

      JEC2017F.SetJetEta(Eta);
      JEC2017F.SetJetPT(PT);
      JEC2017F.SetJetPhi(0);
      H2017F.SetBinContent(i, JEC2017F.GetCorrection());

      JEC2018A.SetJetEta(Eta);
      JEC2018A.SetJetPT(PT);
      JEC2018A.SetJetPhi(0);
      H2018A.SetBinContent(i, JEC2018A.GetCorrection());

      JEC2018B.SetJetEta(Eta);
      JEC2018B.SetJetPT(PT);
      JEC2018B.SetJetPhi(0);
      H2018B.SetBinContent(i, JEC2018B.GetCorrection());

      JEC2018C.SetJetEta(Eta);
      JEC2018C.SetJetPT(PT);
      JEC2018C.SetJetPhi(0);
      H2018C.SetBinContent(i, JEC2018C.GetCorrection());
   }

   H2017B.SetLineWidth(2);
   H2017B.SetLineColor(kBlack);
   H2017B.SetLineStyle(kSolid);
   H2017C.SetLineWidth(2);
   H2017C.SetLineColor(kGreen + 2);
   H2017C.SetLineStyle(kSolid);
   H2017DE.SetLineWidth(2);
   H2017DE.SetLineColor(kYellow + 2);
   H2017DE.SetLineStyle(kSolid);
   H2017F.SetLineWidth(2);
   H2017F.SetLineColor(kRed + 2);
   H2017F.SetLineStyle(kSolid);
   H2018A.SetLineWidth(2);
   H2018A.SetLineColor(kRed);
   H2018A.SetLineStyle(kDashed);
   H2018B.SetLineWidth(2);
   H2018B.SetLineColor(kGreen);
   H2018B.SetLineStyle(kDashed);
   H2018C.SetLineWidth(2);
   H2018C.SetLineColor(kMagenta);
   H2018C.SetLineStyle(kDashed);

   TH2D HWorld("HWorld", "p_{T}^{Reco} = 100 GeV/c;#eta;Correction", 100, 0, 5.18, 100, 0.9, 1.25);
   HWorld.SetStats(0);

   TCanvas Canvas;
   HWorld.Draw();

   H2017B.Draw("same");
   H2017C.Draw("same");
   H2017DE.Draw("same");
   H2017F.Draw("same");
   H2018A.Draw("same");
   H2018B.Draw("same");
   H2018C.Draw("same");

   TLegend Legend(0.15, 0.50, 0.45, 0.80);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H2017B, "2017B", "l");
   Legend.AddEntry(&H2017C, "2017C", "l");
   Legend.AddEntry(&H2017DE, "2017DE", "l");
   Legend.AddEntry(&H2017F, "2017F", "l");
   Legend.AddEntry(&H2018A, "2018A", "l");
   Legend.AddEntry(&H2018B, "2018B", "l");
   Legend.AddEntry(&H2018C, "2018C", "l");
   Legend.Draw();

   Canvas.SaveAs("JECL2Res.pdf");

   return 0;
}





