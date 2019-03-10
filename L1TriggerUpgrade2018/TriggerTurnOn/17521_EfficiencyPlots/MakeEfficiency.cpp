#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"

#include "SetStyle.h"
#include "PlotHelper3.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
void AttachEfficiencyPlot(PdfFileHelper &PdfFile, TFile &F, string HMatch, string HNoMatch);
void AttachSimplePlot(PdfFileHelper &PdfFile, TFile &F, string HName);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   bool DoE = CL.GetBool("doe", false);
   bool DoG = CL.GetBool("dog", false);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Isolation plots: " + InputFileName);

   TFile File(InputFileName.c_str());

   if(DoE == true)
   {
      AttachEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_PT_000000",         "EGElectron/EGElectronNoMatch_PT_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_PTEta15_000000",    "EGElectron/EGElectronNoMatch_PTEta15_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_PTEtaLarge_000000", "EGElectron/EGElectronNoMatch_PTEtaLarge_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_Eta_000000",        "EGElectron/EGElectronNoMatch_Eta_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_EtaPT20_000000",    "EGElectron/EGElectronNoMatch_EtaPT20_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_EtaPT25_000000",    "EGElectron/EGElectronNoMatch_EtaPT25_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_EtaPT200_000000",   "EGElectron/EGElectronNoMatch_EtaPT200_000000");
      AttachSimplePlot(PdfFile, File, "EGElectron/EGElectron_ResponsePT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "EGElectron/EGElectron_ResponsePT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DR_000000");
      AttachSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT10_000000");
      AttachSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT20_000000");
      AttachSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DREta15_000000");
      AttachSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT20Eta15_000000");
      AttachSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DREtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT20EtaLarge_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_PT_000000",         "TkEGIso/TkEGIsoNoMatch_PT_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_PTEta15_000000",    "TkEGIso/TkEGIsoNoMatch_PTEta15_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_PTEtaLarge_000000", "TkEGIso/TkEGIsoNoMatch_PTEtaLarge_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_Eta_000000",        "TkEGIso/TkEGIsoNoMatch_Eta_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_EtaPT20_000000",    "TkEGIso/TkEGIsoNoMatch_EtaPT20_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_EtaPT25_000000",    "TkEGIso/TkEGIsoNoMatch_EtaPT25_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_EtaPT200_000000",   "TkEGIso/TkEGIsoNoMatch_EtaPT200_000000");
      AttachSimplePlot(PdfFile, File, "TkEGIso/TkEGIso_ResponsePT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "TkEGIso/TkEGIso_ResponsePT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_ResponsePT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_ResponsePT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DR_000000");
      AttachSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT10_000000");
      AttachSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT20_000000");
      AttachSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DREta15_000000");
      AttachSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT20Eta15_000000");
      AttachSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DREtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT20EtaLarge_000000");
   }
   if(DoG == true)
   {
      AttachEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_PT_000000",         "EGPhoton/EGPhotonNoMatch_PT_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_PTEta15_000000",    "EGPhoton/EGPhotonNoMatch_PTEta15_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_PTEtaLarge_000000", "EGPhoton/EGPhotonNoMatch_PTEtaLarge_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_Eta_000000",        "EGPhoton/EGPhotonNoMatch_Eta_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_EtaPT20_000000",    "EGPhoton/EGPhotonNoMatch_EtaPT20_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_EtaPT25_000000",    "EGPhoton/EGPhotonNoMatch_EtaPT25_000000");
      AttachEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_EtaPT200_000000",   "EGPhoton/EGPhotonNoMatch_EtaPT200_000000");
      AttachSimplePlot(PdfFile, File, "EGPhoton/EGPhoton_ResponsePT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "EGPhoton/EGPhoton_ResponsePT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DR_000000");
      AttachSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT10_000000");
      AttachSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT20_000000");
      AttachSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DREta15_000000");
      AttachSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT20Eta15_000000");
      AttachSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DREtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT20EtaLarge_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_PT_000000",         "TkEMIso/TkEMIsoNoMatch_PT_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_PTEta15_000000",    "TkEMIso/TkEMIsoNoMatch_PTEta15_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_PTEtaLarge_000000", "TkEMIso/TkEMIsoNoMatch_PTEtaLarge_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_Eta_000000",        "TkEMIso/TkEMIsoNoMatch_Eta_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_EtaPT20_000000",    "TkEMIso/TkEMIsoNoMatch_EtaPT20_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_EtaPT25_000000",    "TkEMIso/TkEMIsoNoMatch_EtaPT25_000000");
      AttachEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_EtaPT200_000000",   "TkEMIso/TkEMIsoNoMatch_EtaPT200_000000");
      AttachSimplePlot(PdfFile, File, "TkEMIso/TkEMIso_ResponsePT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "TkEMIso/TkEMIso_ResponsePT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "TkIsoEMIso/TkIsoEMIso_ResponsePT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "TkIsoEMIso/TkIsoEMIso_ResponsePT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DR_000000");
      AttachSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT10_000000");
      AttachSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT20_000000");
      AttachSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DREta15_000000");
      AttachSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT10Eta15_000000");
      AttachSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT20Eta15_000000");
      AttachSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DREtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT10EtaLarge_000000");
      AttachSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT20EtaLarge_000000");
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AttachEfficiencyPlot(PdfFileHelper &PdfFile, TFile &F, string HMatch, string HNoMatch)
{
   PdfFile.AddTextPage(HMatch);

   TH1D *H1 = (TH1D *)F.Get(HMatch.c_str());
   TH1D *H2 = (TH1D *)F.Get(HNoMatch.c_str());
   if(H1 == NULL || H2 == NULL)
      return;

   H1->SetStats(0);
   H2->SetStats(0);

   H1->SetLineColor(kRed);
   H1->SetMarkerColor(kRed);

   TCanvas Canvas;
   H2->Draw();
   H1->Draw("same");
   PdfFile.AddCanvas(Canvas);

   TGraphAsymmErrors Ratio;
   Ratio.Divide(H1, H2);
   PdfFile.AddPlot(Ratio);
}

void AttachSimplePlot(PdfFileHelper &PdfFile, TFile &F, string HName)
{
   PdfFile.AddTextPage(HName);

   TH1D *H = (TH1D *)F.Get(HName.c_str());
   if(H == NULL)
      return;

   H->SetStats(0);

   PdfFile.AddPlot(H, "", false);
   PdfFile.AddPlot(H, "", true);
}



