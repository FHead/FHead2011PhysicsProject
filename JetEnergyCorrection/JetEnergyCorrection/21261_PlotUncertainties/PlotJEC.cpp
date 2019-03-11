#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "SetStyle.h"
#include "PlotHelper3.h"

#include "JetCorrector.h"
#include "JetUncertainty.h"

int main(int argc, char *argv[]);
void PlotEtaDependence(PdfFileHelper &PdfFile, double JetPT, JetCorrector &JEC, JetUncertainty &JU, string Label,
   string Title, int Bin, double Min, double Max);
void PlotPTDependence(PdfFileHelper &PdfFile, double JetEta, JetCorrector &JEC, JetUncertainty &JU, string Label,
   string Title, int Bin, double Min, double Max);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string L2L3ResFileName = CL.Get("L2L3");
   string UncertaintyFileName = CL.Get("Uncertainty");
   string Label = CL.Get("Label", "Some JEC");
   string OutputFileName = CL.Get("Output", "L2L3Res.pdf");

   SetThesisStyle();

   JetCorrector JEC(L2L3ResFileName);
   JetUncertainty JU(UncertaintyFileName);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage(Label);

   int BinCount = 1000;
   PlotEtaDependence(PdfFile, 10,  JEC, JU, Label, "p_{T}^{RECO} = 10 GeV/c;#eta;L2L3Res",  BinCount, 0, 5.18);
   PlotEtaDependence(PdfFile, 30,  JEC, JU, Label, "p_{T}^{RECO} = 30 GeV/c;#eta;L2L3Res",  BinCount, 0, 5.18);
   PlotEtaDependence(PdfFile, 50,  JEC, JU, Label, "p_{T}^{RECO} = 50 GeV/c;#eta;L2L3Res",  BinCount, 0, 5.18);
   PlotEtaDependence(PdfFile, 100, JEC, JU, Label, "p_{T}^{RECO} = 100 GeV/c;#eta;L2L3Res", BinCount, 0, 5.18);
   PlotEtaDependence(PdfFile, 200, JEC, JU, Label, "p_{T}^{RECO} = 200 GeV/c;#eta;L2L3Res", BinCount, 0, 5.18);
   PlotEtaDependence(PdfFile, 500, JEC, JU, Label, "p_{T}^{RECO} = 500 GeV/c;#eta;L2L3Res", BinCount, 0, 5.18);
   
   PlotPTDependence(PdfFile, 0.0, JEC, JU, Label, "#eta^{RECO} = 0.0;p_{T};L2L3Res", BinCount, 10, 1000);
   PlotPTDependence(PdfFile, 0.5, JEC, JU, Label, "#eta^{RECO} = 0.5;p_{T};L2L3Res", BinCount, 10, 1000);
   PlotPTDependence(PdfFile, 1.0, JEC, JU, Label, "#eta^{RECO} = 1.0;p_{T};L2L3Res", BinCount, 10, 1000);
   PlotPTDependence(PdfFile, 1.3, JEC, JU, Label, "#eta^{RECO} = 1.3;p_{T};L2L3Res", BinCount, 10, 1000);
   PlotPTDependence(PdfFile, 2.0, JEC, JU, Label, "#eta^{RECO} = 2.0;p_{T};L2L3Res", BinCount, 10, 1000);
   PlotPTDependence(PdfFile, 2.5, JEC, JU, Label, "#eta^{RECO} = 2.5;p_{T};L2L3Res", BinCount, 10, 1000);
   PlotPTDependence(PdfFile, 2.9, JEC, JU, Label, "#eta^{RECO} = 2.9;p_{T};L2L3Res", BinCount, 10, 1000);
   PlotPTDependence(PdfFile, 3.0, JEC, JU, Label, "#eta^{RECO} = 3.0;p_{T};L2L3Res", BinCount, 10, 1000);
   PlotPTDependence(PdfFile, 4.0, JEC, JU, Label, "#eta^{RECO} = 4.0;p_{T};L2L3Res", BinCount, 10, 1000);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PlotEtaDependence(PdfFileHelper &PdfFile, double JetPT, JetCorrector &JEC, JetUncertainty &JU, string Label,
   string Title, int Bin, double Min, double Max)
{
   TH1D HJEC("HJEC", ";#eta;Correction", Bin, Min, Max);
   TH1D HJECUp("HJECUp", ";#eta;Correction", Bin, Min, Max);
   TH1D HJECDown("HJECDown", ";#eta;Correction", Bin, Min, Max);

   for(int i = 1; i <= Bin; i++)
   {
      double Eta = HJEC.GetXaxis()->GetBinCenter(i);
      double PT = JetPT;

      JEC.SetJetEta(Eta);
      JEC.SetJetPT(PT);
      JEC.SetJetPhi(0);
      JU.SetJetEta(Eta);
      JU.SetJetPT(PT);
      JU.SetJetPhi(0);

      double jec = JEC.GetCorrection();
      pair<double, double> uncertainty = JU.GetUncertainty();

      HJEC.SetBinContent(i, jec);
      HJECUp.SetBinContent(i, jec + uncertainty.second);
      HJECDown.SetBinContent(i, jec - uncertainty.first);
   }

   HJEC.SetLineWidth(2);
   HJEC.SetLineColor(kBlack);
   HJEC.SetLineStyle(kSolid);
   HJEC.SetMarkerStyle(1);
   HJEC.SetMarkerColor(kBlue);
   
   HJECUp.SetFillStyle(3144);
   HJECUp.SetFillColor(38);
   HJECUp.SetLineColor(38);
   HJECDown.SetFillStyle(1001);
   HJECDown.SetFillColor(10);
   HJECDown.SetLineColor(38);

   TH2D HWorld("HWorld", Title.c_str(), Bin, Min, Max, 100, 0.65, 1.45);
   HWorld.SetStats(0);

   TCanvas Canvas;
   HWorld.Draw();

   HJECUp.Draw("same hist");
   HJECDown.Draw("same hist");
   HJEC.Draw("same");
   HWorld.Draw("axis same");

   TLegend Legend(0.15, 0.50, 0.45, 0.80);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HJEC, Label.c_str(), "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}

void PlotPTDependence(PdfFileHelper &PdfFile, double JetEta, JetCorrector &JEC, JetUncertainty &JU, string Label,
   string Title, int Bin, double Min, double Max)
{
   double Bins[102400];
   for(int i = 0; i <= Bin; i++)
      Bins[i] = exp(log(Min) + (log(Max) - log(Min)) / Bin * i);

   TH1D HJEC("HJEC", ";;Correction", Bin, Bins);
   TH1D HJECUp("HJECUp", ";;Correction", Bin, Bins);
   TH1D HJECDown("HJECDown", ";;Correction", Bin, Bins);

   for(int i = 1; i <= Bin; i++)
   {
      double Eta = JetEta;
      double PT = HJEC.GetXaxis()->GetBinCenter(i);

      JEC.SetJetEta(Eta);
      JEC.SetJetPT(PT);
      JEC.SetJetPhi(0);
      JU.SetJetEta(Eta);
      JU.SetJetPT(PT);
      JU.SetJetPhi(0);
      
      double jec = JEC.GetCorrection();
      pair<double, double> uncertainty = JU.GetUncertainty();

      HJEC.SetBinContent(i, jec);
      HJECUp.SetBinContent(i, jec + uncertainty.second);
      HJECDown.SetBinContent(i, jec - uncertainty.first);
   }

   HJEC.SetLineWidth(2);
   HJEC.SetLineColor(kBlack);
   HJEC.SetLineStyle(kSolid);
   HJEC.SetMarkerStyle(1);
   HJEC.SetMarkerColor(kBlue);
   
   HJECUp.SetFillStyle(3144);
   HJECUp.SetFillColor(38);
   HJECUp.SetLineColor(38);
   HJECDown.SetFillStyle(1001);
   HJECDown.SetFillColor(10);
   HJECDown.SetLineColor(38);

   TH2D HWorld("HWorld", Title.c_str(), Bin, Bins, 100, 0.65, 1.45);
   HWorld.SetStats(0);

   TCanvas Canvas;
   HWorld.Draw();

   HJECUp.Draw("same hist");
   HJECDown.Draw("same hist");
   HJEC.Draw("same");
   HWorld.Draw("axis same");

   TLegend Legend(0.15, 0.50, 0.45, 0.80);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HJEC, Label.c_str(), "l");
   Legend.Draw();

   Canvas.SetLogx();
   PdfFile.AddCanvas(Canvas);
}


