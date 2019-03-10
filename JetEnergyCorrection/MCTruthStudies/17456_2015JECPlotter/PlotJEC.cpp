#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

#include "JetCorrector.h"

int main(int argc, char *argv[]);
void PlotPTDependence(PdfFileHelper &PdfFile, double Eta,
   JetCorrector &J1L1, JetCorrector &J1L2, JetCorrector &J2L1, JetCorrector &J2L2, JetCorrector &J1, JetCorrector &J2,
   string Title, int Bin, double Min, double Max);
void PlotEtaDependence(PdfFileHelper &PdfFile, double PT,
   JetCorrector &J1L1, JetCorrector &J1L2, JetCorrector &J2L1, JetCorrector &J2L2, JetCorrector &J1, JetCorrector &J2,
   string Title, int Bin, double Min, double Max);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DefaultFileName1L1 = CL.Get("jec1l1", "Fall15_25nsV2_MC_L1FastJet_AK4PF.txt");
   string DefaultFileName2L1 = CL.Get("jec2l1", "Fall15_25nsV2_MC_L1FastJet_AK4PFchs.txt");
   string DefaultFileName1L2 = CL.Get("jec1l2", "Fall15_25nsV2_MC_L2Relative_AK4PF.txt");
   string DefaultFileName2L2 = CL.Get("jec2l2", "Fall15_25nsV2_MC_L2Relative_AK4PFchs.txt");
   string NewFileName1 = CL.Get("jec1", "ParallelMC_L2Relative_AK4PF.txt");
   string NewFileName2 = CL.Get("jec2", "ParallelMC_L2Relative_AK4PFchs.txt");
   string OutputFileName = CL.Get("output", "JEC.pdf");

   JetCorrector JC1L1(DefaultFileName1L1);
   JetCorrector JC2L1(DefaultFileName2L1);
   JetCorrector JC1L2(DefaultFileName1L2);
   JetCorrector JC2L2(DefaultFileName2L2);
   JetCorrector JC1(NewFileName1);
   JetCorrector JC2(NewFileName2);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("JEC 2015");

   PlotPTDependence(PdfFile, 0.0, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 0.0;p_{T}^{reco};Correction", 1000, 10, 200);
   PlotPTDependence(PdfFile, 0.5, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 0.5;p_{T}^{reco};Correction", 1000, 10, 200);
   PlotPTDependence(PdfFile, 1.0, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 1.0;p_{T}^{reco};Correction", 1000, 10, 200);
   PlotPTDependence(PdfFile, 1.5, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 1.5;p_{T}^{reco};Correction", 1000, 10, 200);
   PlotPTDependence(PdfFile, 2.0, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 2.0;p_{T}^{reco};Correction", 1000, 10, 200);
   PlotPTDependence(PdfFile, 2.5, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 2.5;p_{T}^{reco};Correction", 1000, 10, 200);
   PlotPTDependence(PdfFile, 3.0, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 3.0;p_{T}^{reco};Correction", 1000, 10, 200);
   PlotPTDependence(PdfFile, 3.5, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 3.5;p_{T}^{reco};Correction", 1000, 10, 200);
   PlotPTDependence(PdfFile, 4.0, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 4.0;p_{T}^{reco};Correction", 1000, 10, 200);
   PlotPTDependence(PdfFile, 4.5, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "eta = 4.5;p_{T}^{reco};Correction", 1000, 10, 200);
   
   PlotEtaDependence(PdfFile, 10, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "p_{T}^{reco} = 10;#eta;Correction", 1000, -5, 5);
   PlotEtaDependence(PdfFile, 30, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "p_{T}^{reco} = 30;#eta;Correction", 1000, -5, 5);
   PlotEtaDependence(PdfFile, 50, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "p_{T}^{reco} = 50;#eta;Correction", 1000, -5, 5);
   PlotEtaDependence(PdfFile, 70, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "p_{T}^{reco} = 70;#eta;Correction", 1000, -5, 5);
   PlotEtaDependence(PdfFile, 100, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "p_{T}^{reco} = 100;#eta;Correction", 1000, -5, 5);
   PlotEtaDependence(PdfFile, 150, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "p_{T}^{reco} = 150;#eta;Correction", 1000, -5, 5);
   PlotEtaDependence(PdfFile, 200, JC1L1, JC1L2, JC2L1, JC2L2, JC1, JC2, "p_{T}^{reco} = 200;#eta;Correction", 1000, -5, 5);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PlotPTDependence(PdfFileHelper &PdfFile, double Eta,
   JetCorrector &J1L1, JetCorrector &J1L2, JetCorrector &J2L1, JetCorrector &J2L2, JetCorrector &J1, JetCorrector &J2,
   string Title, int Bin, double Min, double Max)
{
   TH1D HResponseD1("HResponseD1", Title.c_str(), Bin, Min, Max);
   TH1D HResponseD2("HResponseD2", Title.c_str(), Bin, Min, Max);
   TH1D HResponseN1("HResponseN1", Title.c_str(), Bin, Min, Max);
   TH1D HResponseN2("HResponseN2", Title.c_str(), Bin, Min, Max);

   for(int i = 1; i <= 1000; i++)
   {
      double X = HResponseD1.GetBinCenter(i);

      J1L1.SetJetPT(X);
      J1L1.SetJetEta(Eta);
      J1L1.SetJetPhi(0);
      J1L1.SetJetArea(0.5);
      J1L1.SetRho(1);
      J2L1.SetJetPT(X);
      J2L1.SetJetEta(Eta);
      J2L1.SetJetPhi(0);
      J2L1.SetJetArea(0.5);
      J2L1.SetRho(1);

      J1L2.SetJetPT(J1L1.GetCorrectedPT());
      J1L2.SetJetEta(Eta);
      J1L2.SetJetPhi(0);
      J2L2.SetJetPT(J2L2.GetCorrectedPT());
      J2L2.SetJetEta(Eta);
      J2L2.SetJetPhi(0);

      J1.SetJetPT(X);
      J1.SetJetEta(Eta);
      J1.SetJetPhi(0);
      J2.SetJetPT(X);
      J2.SetJetEta(Eta);
      J2.SetJetPhi(0);

      HResponseD1.SetBinContent(i, J1L1.GetCorrection() * J1L2.GetCorrection());
      HResponseD2.SetBinContent(i, J2L1.GetCorrection() * J2L2.GetCorrection());
      HResponseN1.SetBinContent(i, J1.GetCorrection());
      HResponseN2.SetBinContent(i, J2.GetCorrection());
   }

   HResponseD1.SetLineColor(kBlack);
   HResponseD2.SetLineColor(kGreen + 3);
   HResponseN1.SetLineColor(kRed);
   HResponseN2.SetLineColor(kMagenta);

   TH2D HWorld("HWorld", Title.c_str(), Bin, Min, Max, 100, 0.5, 1.5);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.Draw("axis");

   HResponseD1.Draw("same");
   HResponseD2.Draw("same");
   HResponseN1.Draw("same");
   HResponseN2.Draw("same");

   TLegend Legend(0.4, 0.4, 0.8, 0.15);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HResponseD1, "Default AK4PF", "l");
   Legend.AddEntry(&HResponseD2, "Default AK4PFchs", "l");
   Legend.AddEntry(&HResponseN1, "Rederived AK4PF", "l");
   Legend.AddEntry(&HResponseN2, "Rederived AK4PFchs", "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}

void PlotEtaDependence(PdfFileHelper &PdfFile, double PT,
   JetCorrector &J1L1, JetCorrector &J1L2, JetCorrector &J2L1, JetCorrector &J2L2, JetCorrector &J1, JetCorrector &J2,
   string Title, int Bin, double Min, double Max)
{
   TH1D HResponseD1("HResponseD1", Title.c_str(), Bin, Min, Max);
   TH1D HResponseD2("HResponseD2", Title.c_str(), Bin, Min, Max);
   TH1D HResponseN1("HResponseN1", Title.c_str(), Bin, Min, Max);
   TH1D HResponseN2("HResponseN2", Title.c_str(), Bin, Min, Max);

   for(int i = 1; i <= 1000; i++)
   {
      double X = HResponseD1.GetBinCenter(i);

      J1L1.SetJetPT(PT);
      J1L1.SetJetEta(X);
      J1L1.SetJetPhi(0);
      J1L1.SetJetArea(0.5);
      J1L1.SetRho(1);
      J2L1.SetJetPT(PT);
      J2L1.SetJetEta(X);
      J2L1.SetJetPhi(0);
      J2L1.SetJetArea(0.5);
      J2L1.SetRho(1);

      J1L2.SetJetPT(J1L1.GetCorrectedPT());
      J1L2.SetJetEta(X);
      J1L2.SetJetPhi(0);
      J2L2.SetJetPT(J2L2.GetCorrectedPT());
      J2L2.SetJetEta(X);
      J2L2.SetJetPhi(0);

      J1.SetJetPT(PT);
      J1.SetJetEta(X);
      J1.SetJetPhi(0);
      J2.SetJetPT(PT);
      J2.SetJetEta(X);
      J2.SetJetPhi(0);

      HResponseD1.SetBinContent(i, J1L1.GetCorrection() * J1L2.GetCorrection());
      HResponseD2.SetBinContent(i, J2L1.GetCorrection() * J2L2.GetCorrection());
      HResponseN1.SetBinContent(i, J1.GetCorrection());
      HResponseN2.SetBinContent(i, J2.GetCorrection());
   }

   HResponseD1.SetLineColor(kBlack);
   HResponseD2.SetLineColor(kGreen + 3);
   HResponseN1.SetLineColor(kRed);
   HResponseN2.SetLineColor(kMagenta);

   TH2D HWorld("HWorld", Title.c_str(), Bin, Min, Max, 100, 0.5, 1.5);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.Draw("axis");

   HResponseD1.Draw("same");
   HResponseD2.Draw("same");
   HResponseN1.Draw("same");
   HResponseN2.Draw("same");

   TLegend Legend(0.4, 0.4, 0.8, 0.15);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HResponseD1, "Default AK4PF", "l");
   Legend.AddEntry(&HResponseD2, "Default AK4PFchs", "l");
   Legend.AddEntry(&HResponseN1, "Rederived AK4PF", "l");
   Legend.AddEntry(&HResponseN2, "Rederived AK4PFchs", "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}
