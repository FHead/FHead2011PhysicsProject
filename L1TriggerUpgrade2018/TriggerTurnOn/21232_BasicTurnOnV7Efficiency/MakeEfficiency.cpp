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
   bool DoT = CL.GetBool("DoT", false);

   bool DoEBReport = CL.GetBool("DoEBReport", false);
   bool DoEEReport = CL.GetBool("DoEEReport", false);
   bool DoMReport  = CL.GetBool("DoMReport", false);
   bool DoMEReport = CL.GetBool("DoMEReport", false);
   bool DoMBReport = CL.GetBool("DoMBReport", false);
   bool DoMOReport = CL.GetBool("DoMOReport", false);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Efficiency plots: " + InputFileName);

   TFile File(InputFileName.c_str());

   if(DoEBReport == true)
   {
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DRPT10Eta15_000000");
      PdfFile.AddTextPage("Isolation Plots");
      AddIsolationPlot(PdfFile, File, "GenElectron/GenElectron_TkIso_000000",         -1);
      AddIsolationPlot(PdfFile, File, "TkElectronIso/TkElectronIso_TkIsoPT10Eta15_000000",        0.982);
      AddIsolationPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_TkIsoPT10Eta15_000000",        0.982);
      PdfFile.AddTextPage("EG plots");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronIso/TkIsoElectronIso_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronIso/TkIsoElectronIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLooseIso/TkIsoElectronLooseIso_PTEta15_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLooseIso/TkIsoElectronLooseIso_EtaPT25_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_EtaPT25_000000");
      PdfFile.AddTextPage("Response plots");
      AddSimplePlot(PdfFile, File, "TkIsoElectronIso/TkIsoElectronIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectronLooseIso/TkIsoElectronLooseIso_ResponsePT10Eta15_000000");
   }
   if(DoEEReport == true)
   {
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DRPT10EtaLarge_000000");
      PdfFile.AddTextPage("Isolation Plots");
      AddIsolationPlot(PdfFile, File, "GenElectron/GenElectron_TkIso_000000",         -1);
      AddIsolationPlot(PdfFile, File, "TkElectronIso/TkElectronIso_TkIsoPT10EtaLarge_000000",        0.982);
      AddIsolationPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_TkIsoPT10EtaLarge_000000",        0.982);
      PdfFile.AddTextPage("EG plots");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronIso/TkIsoElectronIso_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronIso/TkIsoElectronIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLooseIso/TkIsoElectronLooseIso_PTEtaLarge_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLooseIso/TkIsoElectronLooseIso_EtaPT25_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_EtaPT25_000000");
      PdfFile.AddTextPage("Response plots");
      AddSimplePlot(PdfFile, File, "TkIsoElectronIso/TkIsoElectronIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectronLooseIso/TkIsoElectronLooseIso_ResponsePT10EtaLarge_000000");
   }
   if(DoE == true)
   {
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR/TkElectronLDR_DRPT20EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseLDR/TkElectronLooseLDR_DRPT20EtaLarge_000000");
      PdfFile.AddTextPage("Isolation Plots");
      AddIsolationPlot(PdfFile, File, "TkElectronIso/TkElectronIso_TkIso_000000",                   0.982);
      AddIsolationPlot(PdfFile, File, "TkElectronIso/TkElectronIso_TkIsoEta15_000000",              0.982);
      AddIsolationPlot(PdfFile, File, "TkElectronIso/TkElectronIso_TkIsoEtaLarge_000000",           0.982);
      AddIsolationPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_TkIso_000000",         0.982);
      AddIsolationPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_TkIsoEta15_000000",    0.982);
      AddIsolationPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_TkIsoEtaLarge_000000", 0.982);
      PdfFile.AddTextPage("Efficiency plots");
      AddEfficiencyPlot(PdfFile, File, "TkElectronIso/TkElectronIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronIso/TkElectronIso_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronIso/TkElectronIso_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronIso/TkElectronIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronIso/TkElectronIso_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronIso/TkElectronIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronIso/TkElectronIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron/TkIsoElectron_PT_000000",
                                       "TkElectronIso/TkElectronIsoNoMatch_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron/TkIsoElectron_PTEta15_000000",
                                       "TkElectronIso/TkElectronIsoNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron/TkIsoElectron_PTEtaLarge_000000",
                                       "TkElectronIso/TkElectronIsoNoMatch_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron/TkIsoElectron_Eta_000000",
                                       "TkElectronIso/TkElectronIsoNoMatch_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron/TkIsoElectron_EtaPT20_000000",
                                       "TkElectronIso/TkElectronIsoNoMatch_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron/TkIsoElectron_EtaPT25_000000",
                                       "TkElectronIso/TkElectronIsoNoMatch_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron/TkIsoElectron_EtaPT200_000000",
                                       "TkElectronIso/TkElectronIsoNoMatch_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLoose/TkIsoElectronLoose_PT_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLoose/TkIsoElectronLoose_PTEta15_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLoose/TkIsoElectronLoose_PTEtaLarge_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLoose/TkIsoElectronLoose_Eta_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLoose/TkIsoElectronLoose_EtaPT20_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLoose/TkIsoElectronLoose_EtaPT25_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronLoose/TkIsoElectronLoose_EtaPT200_000000",
                                       "TkElectronLooseIso/TkElectronLooseIsoNoMatch_EtaPT200_000000");
      PdfFile.AddTextPage("Response plots");
      AddSimplePlot(PdfFile, File, "TkElectronIso/TkElectronIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronIso/TkElectronIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectronIso/TkIsoElectronIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectronIso/TkIsoElectronIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLooseIso/TkElectronLooseIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectronLoose/TkIsoElectronLoose_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectronLoose/TkIsoElectronLoose_ResponsePT10EtaLarge_000000");
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
      AddSimplePlot(PdfFile, File, "EGPhotonLDR/EGPhotonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLDR/EGPhotonLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLDR/EGPhotonLDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLDR/EGPhotonLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLDR/EGPhotonLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLDR/EGPhotonLDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLDR/EGPhotonLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLDR/EGPhotonLDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGPhotonLDR/EGPhotonLDR_DRPT20EtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonIso/TkPhotonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonIso/TkPhotonIso_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonIso/TkPhotonIso_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonIso/TkPhotonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonIso/TkPhotonIso_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonIso/TkPhotonIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonIso/TkPhotonIso_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonIso/TkIsoPhotonIso_PT_000000",
                                       "TkPhotonIso/TkPhotonIsoNoMatch_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonIso/TkIsoPhotonIso_PTEta15_000000",
                                       "TkPhotonIso/TkPhotonIsoNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonIso/TkIsoPhotonIso_PTEtaLarge_000000",
                                       "TkPhotonIso/TkPhotonIsoNoMatch_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonIso/TkIsoPhotonIso_Eta_000000",
                                       "TkPhotonIso/TkPhotonIsoNoMatch_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonIso/TkIsoPhotonIso_EtaPT20_000000",
                                       "TkPhotonIso/TkPhotonIsoNoMatch_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonIso/TkIsoPhotonIso_EtaPT25_000000",
                                       "TkPhotonIso/TkPhotonIsoNoMatch_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonIso/TkIsoPhotonIso_EtaPT200_000000",
                                       "TkPhotonIso/TkPhotonIsoNoMatch_EtaPT200_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonIso/TkPhotonIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonIso/TkPhotonIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonIso/TkIsoPhotonIso_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonIso/TkIsoPhotonIso_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonLDR/TkPhotonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonLDR/TkPhotonLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonLDR/TkPhotonLDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonLDR/TkPhotonLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonLDR/TkPhotonLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonLDR/TkPhotonLDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonLDR/TkPhotonLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonLDR/TkPhotonLDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonLDR/TkPhotonLDR_DRPT20EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonLDR/TkIsoPhotonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonLDR/TkIsoPhotonLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonLDR/TkIsoPhotonLDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonLDR/TkIsoPhotonLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonLDR/TkIsoPhotonLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonLDR/TkIsoPhotonLDR_DRPT20Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonLDR/TkIsoPhotonLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonLDR/TkIsoPhotonLDR_DRPT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonLDR/TkIsoPhotonLDR_DRPT20EtaLarge_000000");
   }
   if(DoM == true)
   {
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "GlobalMuonLDR/GlobalMuonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "GlobalMuonLDR/GlobalMuonLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "StandaloneMuonLDR/StandaloneMuonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "StandaloneMuonLDR/StandaloneMuonLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkMuonLDR/TkMuonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkMuonLDR/TkMuonLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkMuonStubLDR/TkMuonStubLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkMuonStubLDR/TkMuonStubLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkGlbMuonLDR/TkGlbMuonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkGlbMuonLDR/TkGlbMuonLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "PFMuonLDR/PFMuonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "PFMuonLDR/PFMuonLDR_DRPT10_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "GlobalMuonIso/GlobalMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "GlobalMuonIso/GlobalMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "GlobalMuonIso/GlobalMuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneMuonIso/StandaloneMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneMuonIso/StandaloneMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneMuonIso/StandaloneMuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso/TkMuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubIso/TkMuonStubIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubIso/TkMuonStubIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubIso/TkMuonStubIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkGlbMuonIso/TkGlbMuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PFMuonIso/PFMuonIso_EtaPT15_000000");
   }
   if(DoT == true)
   {
      PdfFile.AddTextPage("Tau Isolation Plots");
      AddIsolationPlot(PdfFile, File, "GenTau/GenTau_TkIso_000000", -1);
      AddIsolationPlot(PdfFile, File, "GenTau/GenTau_TkIsoPT10_000000", -1);
      AddIsolationPlot(PdfFile, File, "GenTau/GenTau_TkIsoPT20_000000", -1);
      AddIsolationPlot(PdfFile, File, "GenTau/GenTau_TkIsoPT30_000000", -1);
      AddIsolationPlot(PdfFile, File, "GenTau/GenTau_TkIsoPT40_000000", -1);
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "TauLDR/TauLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TauLDR/TauLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkTauLDR/TkTauLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkTauLDR/TkTauLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "PFTauLDR/PFTauLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "PFTauLDR/PFTauLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "PFIsoTauLDR/PFIsoTauLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "PFIsoTauLDR/PFIsoTauLDR_DRPT10_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "Tau/Tau_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "Tau/Tau_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "Tau/Tau_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "Tau/Tau_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "Tau/Tau_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "Tau/Tau_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "Tau/Tau_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "TkTau/TkTau_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkTau/TkTau_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkTau/TkTau_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkTau/TkTau_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkTau/TkTau_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "TkTau/TkTau_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "TkTau/TkTau_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "PFTau/PFTau_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PFTau/PFTau_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PFTau/PFTau_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "PFTau/PFTau_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "PFTau/PFTau_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "PFTau/PFTau_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "PFTau/PFTau_EtaPT200_000000");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau/PFIsoTau_PT_000000",
                                       "PFTau/PFTauNoMatch_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau/PFIsoTau_PTEta15_000000",
                                       "PFTau/PFTauNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau/PFIsoTau_PTEtaLarge_000000",
                                       "PFTau/PFTauNoMatch_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau/PFIsoTau_Eta_000000",
                                       "PFTau/PFTauNoMatch_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau/PFIsoTau_EtaPT20_000000",
                                       "PFTau/PFTauNoMatch_EtaPT20_000000");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau/PFIsoTau_EtaPT25_000000",
                                       "PFTau/PFTauNoMatch_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau/PFIsoTau_EtaPT200_000000",
                                       "PFTau/PFTauNoMatch_EtaPT200_000000");
   }
   if(DoJ == true)
   {
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "TkJetLDR/TkJetLDR_DR_000000");
      // AddSimplePlot(PdfFile, File, "TkJetLDR/TkJetLDR_DRPT10_000000");
      // AddSimplePlot(PdfFile, File, "TkJetLDR/TkJetLDR_DRPT20_000000");
      // AddSimplePlot(PdfFile, File, "TkJetLDR/TkJetLDR_DRPT50_000000");
      AddSimplePlot(PdfFile, File, "TkCaloJetLDR/TkCaloJetLDR_DR_000000");
      // AddSimplePlot(PdfFile, File, "TkCaloJetLDR/TkCaloJetLDR_DRPT10_000000");
      // AddSimplePlot(PdfFile, File, "TkCaloJetLDR/TkCaloJetLDR_DRPT20_000000");
      // AddSimplePlot(PdfFile, File, "TkCaloJetLDR/TkCaloJetLDR_DRPT50_000000");
      AddSimplePlot(PdfFile, File, "PuppiJetLDR/PuppiJetLDR_DR_000000");
      // AddSimplePlot(PdfFile, File, "PuppiJetLDR/PuppiJetLDR_DRPT10_000000");
      // AddSimplePlot(PdfFile, File, "PuppiJetLDR/PuppiJetLDR_DRPT20_000000");
      // AddSimplePlot(PdfFile, File, "PuppiJetLDR/PuppiJetLDR_DRPT50_000000");
      PdfFile.AddTextPage("Efficiency vs PT");
      AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_PT_000000");
      PdfFile.AddTextPage("Efficiency vs Eta");
      // AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_Eta_000000");
      // AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT15_000000");
      // AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT20_000000");
      // AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT100_000000");
      // AddEfficiencyPlot(PdfFile, File, "TkJet/TkJet_EtaPT200_000000");
      // AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_Eta_000000");
      // AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT15_000000");
      // AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT20_000000");
      // AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT100_000000");
      // AddEfficiencyPlot(PdfFile, File, "TkCaloJet/TkCaloJet_EtaPT200_000000");
      // AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_Eta_000000");
      // AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT15_000000");
      // AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT20_000000");
      // AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT30_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT100_000000");
      // AddEfficiencyPlot(PdfFile, File, "PuppiJet/PuppiJet_EtaPT200_000000");
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


