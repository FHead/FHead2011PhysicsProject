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
   JetCorrector &JEC1, JetCorrector &JEC2, JetCorrector &JEC3, JetCorrector &JEC4,
   string Title, int Bin, double Min, double Max, vector<string> Labels);
void PlotEtaDependence(PdfFileHelper &PdfFile, double PT,
   JetCorrector &JEC1, JetCorrector &JEC2, JetCorrector &JEC3, JetCorrector &JEC4,
   string Title, int Bin, double Min, double Max, vector<string> Labels);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileNameJEC1 = CL.Get("jec1", "Summer16_07Aug16_lowPU_lowpT_MPF_FLAT_L2Residual_AK4PFCHS.txt");
   string FileNameJEC2 = CL.Get("jec2", "Summer16_07Aug16_lowPU_lowpT_MPF_FLAT_NOKFSR_L2Residual_AK4PFCHS.txt");
   string FileNameJEC3 = CL.Get("jec3", "Summer16_07Aug16_lowPU_lowpT_MPF_LOGLIN_L2Residual_AK4PFCHS.txt");
   string FileNameJEC4 = CL.Get("jec4", "Summer16_07Aug16_lowPU_lowpT_MPF_LOGLIN_NOKFSR_L2Residual_AK4PFCHS.txt");
   string OutputFileName = CL.Get("output", "JEC.pdf");
   vector<string> Labels = CL.GetStringVector("label", {"A", "B", "C", "D"});

   JetCorrector JEC1(FileNameJEC1);
   JetCorrector JEC2(FileNameJEC2);
   JetCorrector JEC3(FileNameJEC3);
   JetCorrector JEC4(FileNameJEC4);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("JEC L2Res");

   PlotPTDependence(PdfFile, 0.0, JEC1, JEC2, JEC3, JEC4, "eta = 0.0;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   PlotPTDependence(PdfFile, 0.5, JEC1, JEC2, JEC3, JEC4, "eta = 0.5;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   PlotPTDependence(PdfFile, 1.0, JEC1, JEC2, JEC3, JEC4, "eta = 1.0;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   PlotPTDependence(PdfFile, 1.5, JEC1, JEC2, JEC3, JEC4, "eta = 1.5;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   PlotPTDependence(PdfFile, 2.0, JEC1, JEC2, JEC3, JEC4, "eta = 2.0;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   PlotPTDependence(PdfFile, 2.5, JEC1, JEC2, JEC3, JEC4, "eta = 2.5;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   PlotPTDependence(PdfFile, 3.0, JEC1, JEC2, JEC3, JEC4, "eta = 3.0;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   PlotPTDependence(PdfFile, 3.5, JEC1, JEC2, JEC3, JEC4, "eta = 3.5;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   PlotPTDependence(PdfFile, 4.0, JEC1, JEC2, JEC3, JEC4, "eta = 4.0;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   PlotPTDependence(PdfFile, 4.5, JEC1, JEC2, JEC3, JEC4, "eta = 4.5;p_{T}^{reco};Correction", 1000, 6, 200, Labels);
   
   PlotEtaDependence(PdfFile, 10,  JEC1, JEC2, JEC3, JEC4, "p_{T}^{reco} = 10;#eta;Correction",  1000, -5, 5, Labels);
   PlotEtaDependence(PdfFile, 30,  JEC1, JEC2, JEC3, JEC4, "p_{T}^{reco} = 30;#eta;Correction",  1000, -5, 5, Labels);
   PlotEtaDependence(PdfFile, 50,  JEC1, JEC2, JEC3, JEC4, "p_{T}^{reco} = 50;#eta;Correction",  1000, -5, 5, Labels);
   PlotEtaDependence(PdfFile, 70,  JEC1, JEC2, JEC3, JEC4, "p_{T}^{reco} = 70;#eta;Correction",  1000, -5, 5, Labels);
   PlotEtaDependence(PdfFile, 100, JEC1, JEC2, JEC3, JEC4, "p_{T}^{reco} = 100;#eta;Correction", 1000, -5, 5, Labels);
   PlotEtaDependence(PdfFile, 150, JEC1, JEC2, JEC3, JEC4, "p_{T}^{reco} = 150;#eta;Correction", 1000, -5, 5, Labels);
   PlotEtaDependence(PdfFile, 200, JEC1, JEC2, JEC3, JEC4, "p_{T}^{reco} = 200;#eta;Correction", 1000, -5, 5, Labels);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PlotPTDependence(PdfFileHelper &PdfFile, double Eta,
   JetCorrector &JEC1, JetCorrector &JEC2, JetCorrector &JEC3, JetCorrector &JEC4,
   string Title, int Bin, double Min, double Max, vector<string> Labels)
{
   double Bins[10000];
   for(int i = 0; i <= Bin; i++)
      Bins[i] = exp((log(Max) - log(Min)) / Bin * i + log(Min));

   TH1D HResponse1("HResponse1", Title.c_str(), Bin, Bins);
   TH1D HResponse2("HResponse2", Title.c_str(), Bin, Bins);
   TH1D HResponse3("HResponse3", Title.c_str(), Bin, Bins);
   TH1D HResponse4("HResponse4", Title.c_str(), Bin, Bins);

   for(int i = 1; i <= 1000; i++)
   {
      double X = HResponse1.GetBinCenter(i);

      JEC1.SetJetPT(X);
      JEC1.SetJetEta(Eta);
      JEC1.SetJetPhi(0);
      JEC2.SetJetPT(X);
      JEC2.SetJetEta(Eta);
      JEC2.SetJetPhi(0);
      JEC3.SetJetPT(X);
      JEC3.SetJetEta(Eta);
      JEC3.SetJetPhi(0);
      JEC4.SetJetPT(X);
      JEC4.SetJetEta(Eta);
      JEC4.SetJetPhi(0);

      HResponse1.SetBinContent(i, JEC1.GetCorrection());
      HResponse2.SetBinContent(i, JEC2.GetCorrection());
      HResponse3.SetBinContent(i, JEC3.GetCorrection());
      HResponse4.SetBinContent(i, JEC4.GetCorrection());
   }

   HResponse1.SetLineColor(kBlack);
   HResponse2.SetLineColor(kGreen + 3);
   HResponse3.SetLineColor(kRed);
   HResponse4.SetLineColor(kMagenta);

   TH2D HWorld("HWorld", Title.c_str(), Bin, Min, Max, 100, 0.85, 1.10);
   HWorld.SetStats(0);

   TCanvas Canvas;
   Canvas.SetLogx();

   HWorld.Draw("axis");

   HResponse1.Draw("same");
   HResponse2.Draw("same");
   HResponse3.Draw("same");
   HResponse4.Draw("same");

   TLegend Legend(0.4, 0.4, 0.8, 0.15);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HResponse1, Labels[0].c_str(), "l");
   Legend.AddEntry(&HResponse2, Labels[1].c_str(), "l");
   Legend.AddEntry(&HResponse3, Labels[2].c_str(), "l");
   Legend.AddEntry(&HResponse4, Labels[3].c_str(), "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}

void PlotEtaDependence(PdfFileHelper &PdfFile, double PT,
   JetCorrector &JEC1, JetCorrector &JEC2, JetCorrector &JEC3, JetCorrector &JEC4,
   string Title, int Bin, double Min, double Max, vector<string> Labels)
{
   TH1D HResponse1("HResponse1", Title.c_str(), Bin, Min, Max);
   TH1D HResponse2("HResponse2", Title.c_str(), Bin, Min, Max);
   TH1D HResponse3("HResponse3", Title.c_str(), Bin, Min, Max);
   TH1D HResponse4("HResponse4", Title.c_str(), Bin, Min, Max);

   for(int i = 1; i <= 1000; i++)
   {
      double X = HResponse1.GetBinCenter(i);

      JEC1.SetJetPT(PT);
      JEC1.SetJetEta(X);
      JEC1.SetJetPhi(0);
      JEC2.SetJetPT(PT);
      JEC2.SetJetEta(X);
      JEC2.SetJetPhi(0);
      JEC3.SetJetPT(PT);
      JEC3.SetJetEta(X);
      JEC3.SetJetPhi(0);
      JEC4.SetJetPT(PT);
      JEC4.SetJetEta(X);
      JEC4.SetJetPhi(0);

      HResponse1.SetBinContent(i, JEC1.GetCorrection());
      HResponse2.SetBinContent(i, JEC2.GetCorrection());
      HResponse3.SetBinContent(i, JEC3.GetCorrection());
      HResponse4.SetBinContent(i, JEC4.GetCorrection());
   }

   HResponse1.SetLineColor(kBlack);
   HResponse2.SetLineColor(kGreen + 3);
   HResponse3.SetLineColor(kRed);
   HResponse4.SetLineColor(kMagenta);

   TH2D HWorld("HWorld", Title.c_str(), Bin, Min, Max, 100, 0.85, 1.10);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.Draw("axis");

   HResponse1.Draw("same");
   HResponse2.Draw("same");
   HResponse3.Draw("same");
   HResponse4.Draw("same");

   TLegend Legend(0.4, 0.4, 0.8, 0.15);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HResponse1, Labels[0].c_str(), "l");
   Legend.AddEntry(&HResponse2, Labels[1].c_str(), "l");
   Legend.AddEntry(&HResponse3, Labels[2].c_str(), "l");
   Legend.AddEntry(&HResponse4, Labels[3].c_str(), "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}
