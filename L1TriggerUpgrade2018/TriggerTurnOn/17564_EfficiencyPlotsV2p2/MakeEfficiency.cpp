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
void AddEfficiencyPlot(PdfFileHelper &PdfFile, TFile &F, string HMatch, string HNoMatch);
void AddEfficiencyPlot(PdfFileHelper &PdfFile, TFile &F, string HMatch);
void AddIsolationPlot(PdfFileHelper &PdfFile, TFile &F, string HistogramName, double Level = 1.00);
void AddSimplePlot(PdfFileHelper &PdfFile, TFile &F, string HName);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   bool DoE = CL.GetBool("DoE", false);
   bool DoG = CL.GetBool("DoG", false);
   bool DoJ = CL.GetBool("DoJ", false);
   bool DoM = CL.GetBool("DoM", false);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Efficiency plots: " + InputFileName);

   TFile File(InputFileName.c_str());

   if(DoE == true)
   {
      PdfFile.AddTextPage("Generator plots");
      AddEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "EGElectron/EGElectron_EtaPT200_000000");
      AddSimplePlot(PdfFile, File, "EGElectron/EGElectron_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGElectron/EGElectron_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGElectronLargeDR/EGElectronLargeDR_DRPT20EtaLarge_000000");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkEGLargeDR/TkEGLargeDR_DRPT20EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseLargeDR/TkEGLooseLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseLargeDR/TkEGLooseLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseLargeDR/TkEGLooseLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseLargeDR/TkEGLooseLargeDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseLargeDR/TkEGLooseLargeDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseLargeDR/TkEGLooseLargeDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseLargeDR/TkEGLooseLargeDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseLargeDR/TkEGLooseLargeDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseLargeDR/TkEGLooseLargeDR_DRPT20EtaLarge_000000");
      PdfFile.AddTextPage("Isolation Plots");
      AddIsolationPlot(PdfFile, File, "GenElectron/GenElectron_TkIso_000000",         -1);
      AddIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIso_000000",                 0.982);
      AddIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT10_000000",             0.982);
      AddIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT20_000000",             0.982);
      AddIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT30_000000",             0.982);
      AddIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT40_000000",             0.982);
      AddIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoEta15_000000",            0.982);
      AddIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoEtaLarge_000000",         0.982);
      AddIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT10Eta15_000000",        0.982);
      AddIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT10EtaLarge_000000",     0.982);
      AddIsolationPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_TkIso_000000",                 0.982);
      AddIsolationPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_TkIsoPT10_000000",             0.982);
      AddIsolationPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_TkIsoPT20_000000",             0.982);
      AddIsolationPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_TkIsoPT30_000000",             0.982);
      AddIsolationPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_TkIsoPT40_000000",             0.982);
      AddIsolationPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_TkIsoEta15_000000",            0.982);
      AddIsolationPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_TkIsoEtaLarge_000000",         0.982);
      AddIsolationPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_TkIsoPT10Eta15_000000",        0.982);
      AddIsolationPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_TkIsoPT10EtaLarge_000000",     0.982);
      PdfFile.AddTextPage("EG plots");
      AddEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGIso/TkEGIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGLooseIso/TkIsoEGLooseIso_PT_000000",
                                       "TkEGLooseIso/TkEGLooseIsoNoMatch_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGLooseIso/TkIsoEGLooseIso_PTEta15_000000",
                                       "TkEGLooseIso/TkEGLooseIsoNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGLooseIso/TkIsoEGLooseIso_PTEtaLarge_000000",
                                       "TkEGLooseIso/TkEGLooseIsoNoMatch_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGLooseIso/TkIsoEGLooseIso_Eta_000000",
                                       "TkEGLooseIso/TkEGLooseIsoNoMatch_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGLooseIso/TkIsoEGLooseIso_EtaPT20_000000",
                                       "TkEGLooseIso/TkEGLooseIsoNoMatch_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGLooseIso/TkIsoEGLooseIso_EtaPT25_000000",
                                       "TkEGLooseIso/TkEGLooseIsoNoMatch_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoEGLooseIso/TkIsoEGLooseIso_EtaPT200_000000",
                                       "TkEGLooseIso/TkEGLooseIsoNoMatch_EtaPT200_000000");
      PdfFile.AddTextPage("Response plots");
      AddSimplePlot(PdfFile, File, "TkEGIso/TkEGIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkEGIso/TkEGIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoEGIso/TkIsoEGIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkEGLooseIso/TkEGLooseIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoEGLooseIso/TkIsoEGLooseIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoEGLooseIso/TkIsoEGLooseIso_ResponsePT10EtaLarge_000000");
   }
   if(DoG == true)
   {
      AddEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "EGPhoton/EGPhoton_EtaPT200_000000");
      AddSimplePlot(PdfFile, File, "EGPhoton/EGPhoton_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGPhoton/EGPhoton_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLargeDR/EGPhotonLargeDR_DRPT20EtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkEMIso/TkEMIso_EtaPT200_000000");
      AddSimplePlot(PdfFile, File, "TkEMIso/TkEMIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkEMIso/TkEMIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoEMIso/TkIsoEMIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoEMIso/TkIsoEMIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkEMLargeDR/TkEMLargeDR_DRPT20EtaLarge_000000");
   }
   if(DoM == true)
   {
      PdfFile.AddTextPage("Gen Isolation Plots");
      AddIsolationPlot(PdfFile, File, "GenMuon/GenMuon_TkIso_000000", -1);
      AddIsolationPlot(PdfFile, File, "GenMuon/GenMuon_TkIsoPT10_000000", -1);
      AddIsolationPlot(PdfFile, File, "GenMuon/GenMuon_TkIsoPT20_000000", -1);
      AddIsolationPlot(PdfFile, File, "GenMuon/GenMuon_TkIsoPT30_000000", -1);
      AddIsolationPlot(PdfFile, File, "GenMuon/GenMuon_TkIsoPT40_000000", -1);
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "MuonLargeDR/MuonLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "MuonLargeDR/MuonLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "MuonLargeDR/MuonLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "MuonLargeDR/MuonLargeDR_DRPT50_000000");
      AddSimplePlot(PdfFile, File, "MuonKFLargeDR/MuonKFLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "MuonKFLargeDR/MuonKFLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "MuonKFLargeDR/MuonKFLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "MuonKFLargeDR/MuonKFLargeDR_DRPT50_000000");
      AddSimplePlot(PdfFile, File, "TkMuonLargeDR/TkMuonLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkMuonLargeDR/TkMuonLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkMuonLargeDR/TkMuonLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkMuonLargeDR/TkMuonLargeDR_DRPT50_000000");
      AddSimplePlot(PdfFile, File, "TkGlbMuonLargeDR/TkGlbMuonLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkGlbMuonLargeDR/TkGlbMuonLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkGlbMuonLargeDR/TkGlbMuonLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkGlbMuonLargeDR/TkGlbMuonLargeDR_DRPT50_000000");
      AddSimplePlot(PdfFile, File, "PFMuonLargeDR/PFMuonLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "PFMuonLargeDR/PFMuonLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "PFMuonLargeDR/PFMuonLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "PFMuonLargeDR/PFMuonLargeDR_DRPT50_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "MuonIso/MuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonIso/MuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonIso/MuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonIso/MuonIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonIso/MuonIso_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonIso/MuonIso_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonIso/MuonIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonKFIso/MuonKFIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonKFIso/MuonKFIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonKFIso/MuonKFIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonKFIso/MuonKFIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonKFIso/MuonKFIso_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonKFIso/MuonKFIso_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "MuonKFIso/MuonKFIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_EtaPT200_000000");
   }
   if(DoJ == true)
   {
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "TkJetLargeDR/TkJetLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkJetLargeDR/TkJetLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkJetLargeDR/TkJetLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkJetLargeDR/TkJetLargeDR_DRPT50_000000");
      AddSimplePlot(PdfFile, File, "TkCaloJetLargeDR/TkCaloJetLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkCaloJetLargeDR/TkCaloJetLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkCaloJetLargeDR/TkCaloJetLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkCaloJetLargeDR/TkCaloJetLargeDR_DRPT50_000000");
      AddSimplePlot(PdfFile, File, "PuppiJetLargeDR/PuppiJetLargeDR_DR_000000");
      AddSimplePlot(PdfFile, File, "PuppiJetLargeDR/PuppiJetLargeDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "PuppiJetLargeDR/PuppiJetLargeDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "PuppiJetLargeDR/PuppiJetLargeDR_DRPT50_000000");
      PdfFile.AddTextPage("Efficiency vs PT");
      AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_PT_000000");
      PdfFile.AddTextPage("Efficiency vs Eta");
      AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT200_000000");
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddEfficiencyPlot(PdfFileHelper &PdfFile, TFile &F, string HMatch, string HNoMatch)
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
   Ratio.GetXaxis()->SetTitle(H1->GetXaxis()->GetTitle());
   Ratio.GetYaxis()->SetTitle("Efficiency");
   PdfFile.AddPlot(Ratio);
}

void AddEfficiencyPlot(PdfFileHelper &PdfFile, TFile &F, string HMatch)
{
   string HNoMatch = HMatch;

   for(int i = 0; i < (int)HNoMatch.size(); i++)
   {
      if(HNoMatch[i] == '_')
      {
         HNoMatch.insert(i, "NoMatch");
         break;
      }
   }

   AddEfficiencyPlot(PdfFile, F, HMatch, HNoMatch);
}

void AddSimplePlot(PdfFileHelper &PdfFile, TFile &F, string HName)
{
   PdfFile.AddTextPage(HName);

   TH1D *H = (TH1D *)F.Get(HName.c_str());
   if(H == NULL)
      return;

   H->SetStats(0);

   PdfFile.AddPlot(H, "", false);
   PdfFile.AddPlot(H, "", true);
}

void AddIsolationPlot(PdfFileHelper &PdfFile, TFile &F, string HistogramName, double Level)
{
   PdfFile.AddTextPage(HistogramName);

   TH1D *H = (TH1D *)F.Get(HistogramName.c_str());
   if(H == NULL)
      return;

   TH1D *HCumulative = (TH1D *)H->Clone("HCumulative");

   for(int i = 1; i <= HCumulative->GetNbinsX() + 1; i++)
      HCumulative->SetBinContent(i, HCumulative->GetBinContent(i) + HCumulative->GetBinContent(i - 1));
   HCumulative->Scale(1 / HCumulative->GetBinContent(HCumulative->GetNbinsX() + 1));

   H->SetTitle("");
   HCumulative->SetTitle("");

   HCumulative->GetYaxis()->SetTitle("Efficiency");

   H->SetStats(0);
   HCumulative->SetStats(0);

   PdfFile.AddPlot(H, "", false);
   PdfFile.AddPlot(H, "", true);

   TGraph Graph;
   Graph.SetPoint(0, 0, Level);
   Graph.SetPoint(1, 1000, Level);

   TCanvas Canvas;
   HCumulative->Draw();
   Graph.Draw("l");
   PdfFile.AddCanvas(Canvas);
}


