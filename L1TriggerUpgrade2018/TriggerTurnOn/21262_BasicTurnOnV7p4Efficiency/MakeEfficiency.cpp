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
void AddEfficiencyPlotNoExpand(PdfFileHelper &PdfFile, TFile &F, string HMatch, string HNoMatch);
void AddEfficiencyPlotNoExpand(PdfFileHelper &PdfFile, TFile &F, string HMatch);
void AddIsolationPlotNoExpand(PdfFileHelper &PdfFile, TFile &F, string HistogramName, double Level = 1.00);
void AddSimplePlotNoExpand(PdfFileHelper &PdfFile, TFile &F, string HName);
string ExpandName(string Name);
string StripFolder(string Name);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   
   bool DoSTAMuon          = CL.GetBool("DoSTAMuon", false);
   bool DoSTADisplacedMuon = CL.GetBool("DoSTADisplacedMuon", false);
   bool DoTkMuon           = CL.GetBool("DoTkMuon", false);
   bool DoTkMuonStub       = CL.GetBool("DoTkMuonStub", false);
   bool DoEG               = CL.GetBool("DoEG", false);
   bool DoEGTrack          = CL.GetBool("DoEGTrack", false);
   bool DoElectron         = CL.GetBool("DoElectron", false);
   bool DoIsoElectron      = CL.GetBool("DoIsoElectron", false);
   bool DoPhoton           = CL.GetBool("DoPhoton", false);
   bool DoPhotonPV         = CL.GetBool("DoPhotonPV", false);
   bool DoElectronPV       = CL.GetBool("DoElectronPV", false);
   bool DoPuppiJet         = CL.GetBool("DoPuppiJet", false);
   bool DoPuppiJetForMET   = CL.GetBool("DoPuppiJetForMET", false);
   bool DoPuppiHT          = CL.GetBool("DoPuppiHT", false);
   bool DoPuppiMET         = CL.GetBool("DoPuppiMET", false);
   bool DoPFTau            = CL.GetBool("DoPFTau", false);
   bool DoPFIsoTau         = CL.GetBool("DoPFIsoTau", false);
   bool DoCaloJet          = CL.GetBool("DoCaloJet", false);
   bool DoCaloHT           = CL.GetBool("DoCaloHT", false);
   bool DoTrackerJet       = CL.GetBool("DoTrackerJet", false);
   bool DoTrackerHT        = CL.GetBool("DoTrackerHT", false);
   bool DoTrackerMET       = CL.GetBool("DoTrackerMET", false);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Efficiency from " + InputFileName);

   TFile File(InputFileName.c_str());

   if(DoSTAMuon == true)
   {
      PdfFile.AddTextPage("Standalone Muons");
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "StandaloneMuonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "StandaloneMuonLDR_DRPT10_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "StandaloneMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneMuonIso_EtaPT15_000000");
   }
   if(DoSTADisplacedMuon == true)
   {
      PdfFile.AddTextPage("Standalone Displaced Muons");
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "StandaloneDisplacedMuonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "StandaloneDisplacedMuonLDR_DRPT10_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonBarrelIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonBarrelIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonBarrelIso_EtaPT15_000000");
      PdfFile.AddTextPage("Efficiency plots with DXY cut");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonDXYIso_PT_000000",
                                       "StandaloneDisplacedMuonIsoNoMatch_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonDXYIso_Eta_000000",
                                       "StandaloneDisplacedMuonIsoNoMatch_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonDXYIso_EtaPT15_000000",
                                       "StandaloneDisplacedMuonIsoNoMatch_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonBarrelDXYIso_PT_000000",
                                       "StandaloneDisplacedMuonBarrelIsoNoMatch_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonBarrelDXYIso_Eta_000000",
                                       "StandaloneDisplacedMuonBarrelIsoNoMatch_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "StandaloneDisplacedMuonBarrelDXYIso_EtaPT15_000000",
                                       "StandaloneDisplacedMuonBarrelIsoNoMatch_EtaPT15_000000");
   }
   if(DoTkMuon == true)
   {
      PdfFile.AddTextPage("TkMuons");
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "TkMuonLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkMuonLDR_DRPT10_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonIso_EtaPT3to15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonBarrelIso_EtaPT3to15_000000");
   }
   if(DoTkMuonStub == true)
   {
      PdfFile.AddTextPage("TkMuonStubs");
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "TkMuonStubLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkMuonStubLDR_DRPT10_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubIso_EtaPT3to15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubBarrelIso_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubBarrelIso_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubBarrelIso_EtaPT15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkMuonStubBarrelIso_EtaPT3to15_000000");
   }
   if(DoEG == true)
   {
      PdfFile.AddTextPage("EG (photon ID)");
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "EGLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "EGLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "EGLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "EGLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGLDR_DRPT10EtaLarge_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "EG_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "EG_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "EG_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "EG_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "EG_EtaPT20_000000");
   }
   if(DoEGTrack == true)
   {
      PdfFile.AddTextPage("EG (track ID)");
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "EGTrackIDLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "EGTrackIDLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "EGTrackIDLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "EGTrackIDLDR_DRPT10EtaLarge_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "EGTrackID_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "EGTrackID_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "EGTrackID_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "EGTrackID_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "EGTrackID_EtaPT20_000000");
   }
   if(DoElectron == true)
   {
      PdfFile.AddTextPage("TkElectron");
      PdfFile.AddTextPage("DR Plots");
      AddSimplePlot(PdfFile, File, "TkElectronTrackIDLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TkElectronTrackIDLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronTrackIDLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronTrackIDLDR_DRPT10_000000");
      AddSimplePlot(PdfFile, File, "TkElectronTrackIDLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronTrackIDLDR_DRPT10EtaLarge_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "TkElectronTrackID_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronTrackID_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronTrackID_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronTrackID_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronTrackID_EtaPT20_000000");
      PdfFile.AddTextPage("Response plots");
      AddSimplePlot(PdfFile, File, "TkElectronTrackID_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronTrackID_ResponsePT10EtaLarge_000000");
   }
   if(DoIsoElectron == true)
   {
      PdfFile.AddTextPage("TkIsoElectron");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "TkElectronLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronLDR_DRPT10EtaLarge_000000");
      PdfFile.AddTextPage("Isolation Plots");
      AddIsolationPlot(PdfFile, File, "TkElectronIso_TkIsoPT10Eta15_000000",    0.982);
      AddIsolationPlot(PdfFile, File, "TkElectronIso_TkIsoPT10EtaLarge_000000", 0.982);
      PdfFile.AddTextPage("Efficiency plots");
      AddEfficiencyPlot(PdfFile, File, "TkElectron_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectron_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectron_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron_EtaPT25_000000",
                                       "TkElectronIsoNoMatch_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron_PTEta15_000000",
                                       "TkElectronIsoNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectron_PTEtaLarge_000000",
                                       "TkElectronIsoNoMatch_PTEtaLarge_000000");
      PdfFile.AddTextPage("Response plots");
      AddSimplePlot(PdfFile, File, "TkElectron_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectron_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectron_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectron_ResponsePT10EtaLarge_000000");
   }
   if(DoPhoton == true)
   {
      PdfFile.AddTextPage("TkPhoton");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "TkPhotonTrackIDLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonTrackIDLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonTrackIDLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonTrackIDLDR_DRPT10EtaLarge_000000");
      PdfFile.AddTextPage("Isolation Plots");
      AddIsolationPlot(PdfFile, File, "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000",    0.946);
      AddIsolationPlot(PdfFile, File, "TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000", 0.946);
      PdfFile.AddTextPage("Efficiency plots");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonTrackID_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonTrackID_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonTrackID_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonTrackID_EtaPT25_000000",
                                       "TkPhotonTrackIDIsoNoMatch_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonTrackID_PTEta15_000000",
                                       "TkPhotonTrackIDIsoNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonTrackID_PTEtaLarge_000000",
                                       "TkPhotonTrackIDIsoNoMatch_PTEtaLarge_000000");
      PdfFile.AddTextPage("Response plots");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonTrackID_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonTrackID_ResponsePT10EtaLarge_000000");
   }
   if(DoPhotonPV == true)
   {
      PdfFile.AddTextPage("TkPhoton (PV)");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "TkPhotonPVTrackIDLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonPVTrackIDLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonPVTrackIDLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkPhotonPVTrackIDLDR_DRPT10EtaLarge_000000");
      PdfFile.AddTextPage("Isolation Plots");
      AddIsolationPlot(PdfFile, File, "TkPhotonPVTrackIDIso_TkIsoPT10Eta15_000000",    0.946);
      AddIsolationPlot(PdfFile, File, "TkPhotonPVTrackIDIso_TkIsoPT10EtaLarge_000000", 0.946);
      PdfFile.AddTextPage("Efficiency plots");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonPVTrackIDIso_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonPVTrackIDIso_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkPhotonPVTrackIDIso_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonPVTrackID_EtaPT25_000000",
                                       "TkPhotonPVTrackIDIsoNoMatch_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonPVTrackID_PTEta15_000000",
                                       "TkPhotonPVTrackIDIsoNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoPhotonPVTrackID_PTEtaLarge_000000",
                                       "TkPhotonPVTrackIDIsoNoMatch_PTEtaLarge_000000");
      PdfFile.AddTextPage("Response plots");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonPVTrackID_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoPhotonPVTrackID_ResponsePT10EtaLarge_000000");
   }
   if(DoElectronPV == true)
   {
      PdfFile.AddTextPage("Complicated stuff");

      PdfFile.AddTextPage("TkIsoElectronPV");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "TkElectronPVLDR_DREta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronPVLDR_DREtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkElectronPVLDR_DRPT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronPVLDR_DRPT10EtaLarge_000000");
      PdfFile.AddTextPage("Isolation Plots");
      AddIsolationPlot(PdfFile, File, "TkElectronPVIso_TkIsoPT10Eta15_000000",    0.982);
      AddIsolationPlot(PdfFile, File, "TkElectronPVIso_TkIsoPT10EtaLarge_000000", 0.982);
      PdfFile.AddTextPage("Efficiency plots");
      AddEfficiencyPlot(PdfFile, File, "TkElectronPV_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronPV_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkElectronPV_PTEtaLarge_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronPV_EtaPT25_000000",
                                       "TkElectronPVIsoNoMatch_EtaPT25_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronPV_PTEta15_000000",
                                       "TkElectronPVIsoNoMatch_PTEta15_000000");
      AddEfficiencyPlot(PdfFile, File, "TkIsoElectronPV_PTEtaLarge_000000",
                                       "TkElectronPVIsoNoMatch_PTEtaLarge_000000");
      PdfFile.AddTextPage("Response plots");
      AddSimplePlot(PdfFile, File, "TkElectronPV_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkElectronPV_ResponsePT10EtaLarge_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectronPV_ResponsePT10Eta15_000000");
      AddSimplePlot(PdfFile, File, "TkIsoElectronPV_ResponsePT10EtaLarge_000000");
   }
   if(DoPuppiJet == true)
   {
      PdfFile.AddTextPage("PuppiJet");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "PuppiJetLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "PuppiJetLDR_DRPT50_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJet_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetWide_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetWide_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetWide_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForward_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForward_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForward_EtaPT100_000000");
   }
   if(DoPuppiJetForMET == true)
   {
      PdfFile.AddTextPage("PuppiJetForMET");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "PuppiJetForMETLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "PuppiJetForMETLDR_DRPT50_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForMET_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForMET_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForMET_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForMETWide_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForMETWide_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForMETWide_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForMETForward_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForMETForward_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PuppiJetForMETForward_EtaPT100_000000");
   }
   if(DoPuppiHT == true)
   {
      PdfFile.AddTextPage("PuppiHT");
      PdfFile.AddTextPage("There's no matching");
   }
   if(DoPuppiMET == true)
   {
      PdfFile.AddTextPage("PuppiMET");
      PdfFile.AddTextPage("There's no matching");
   }
   if(DoPFTau == true)
   {
      PdfFile.AddTextPage("PFTau");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "PFTauLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "PFTauLDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "PFTauLDR_DRPT50_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "PFTau_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PFTau_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PFTau_EtaPT30_000000");
   }
   if(DoPFIsoTau == true)
   {
      PdfFile.AddTextPage("PFIsoTau");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "PFTauLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "PFTauLDR_DRPT20_000000");
      AddSimplePlot(PdfFile, File, "PFTauLDR_DRPT50_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau_PT_000000",
                                       "PFTauIsoNoMatch_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau_Eta_000000",
                                       "PFTauIsoNoMatch_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "PFIsoTau_EtaPT30_000000",
                                       "PFTauIsoNoMatch_EtaPT30_000000");
   }
   if(DoCaloJet == true)
   {
      PdfFile.AddTextPage("CaloJet");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "CaloJetLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "CaloJetLDR_DRPT50_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "CaloJetWide_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "CaloJetWide_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "CaloJetWide_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "CaloJetBarrel_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "CaloJetEndcap_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "CaloJetFoward_PT_000000");
   }
   if(DoCaloHT == true)
   {
      PdfFile.AddTextPage("CaloHT");
      PdfFile.AddTextPage("There's no matching");
   }
   if(DoTrackerJet == true)
   {
      PdfFile.AddTextPage("TrackerJet");
      PdfFile.AddTextPage("DR plots");
      AddSimplePlot(PdfFile, File, "TrackerJetLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TrackerJetLDR_DRPT50_000000");
      AddSimplePlot(PdfFile, File, "TrackerJetChargedLDR_DR_000000");
      AddSimplePlot(PdfFile, File, "TrackerJetChargedLDR_DRPT50_000000");
      PdfFile.AddTextPage("Efficiency Plots");
      AddEfficiencyPlot(PdfFile, File, "TrackerJet_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TrackerJet_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "TrackerJet_PT_000000");
      AddEfficiencyPlot(PdfFile, File, "TrackerJetCharged_Eta_000000");
      AddEfficiencyPlot(PdfFile, File, "TrackerJetCharged_EtaPT100_000000");
      AddEfficiencyPlot(PdfFile, File, "TrackerJetCharged_PT_000000");
   }
   if(DoTrackerHT == true)
   {
      PdfFile.AddTextPage("TrackerHT");
      PdfFile.AddTextPage("There's no matching");
   }
   if(DoTrackerMET == true)
   {
      PdfFile.AddTextPage("TrackerMET");
      PdfFile.AddTextPage("There's no matching");
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddEfficiencyPlot(PdfFileHelper &PdfFile, TFile &F, string HMatch, string HNoMatch)
{
   AddEfficiencyPlotNoExpand(PdfFile, F, ExpandName(HMatch), ExpandName(HNoMatch));
}

void AddEfficiencyPlot(PdfFileHelper &PdfFile, TFile &F, string HMatch)
{
   AddEfficiencyPlotNoExpand(PdfFile, F, ExpandName(HMatch));
}

void AddIsolationPlot(PdfFileHelper &PdfFile, TFile &F, string HistogramName, double Level)
{
   AddIsolationPlotNoExpand(PdfFile, F, ExpandName(HistogramName), Level);
}

void AddSimplePlot(PdfFileHelper &PdfFile, TFile &F, string HName)
{
   AddSimplePlotNoExpand(PdfFile, F, ExpandName(HName));
}

void AddEfficiencyPlotNoExpand(PdfFileHelper &PdfFile, TFile &F, string HMatch, string HNoMatch)
{
   PdfFile.AddTextPage(StripFolder(HMatch));

   TH1D *H1 = (TH1D *)F.Get(HMatch.c_str());
   TH1D *H2 = (TH1D *)F.Get(HNoMatch.c_str());
   if(H1 == NULL || H2 == NULL)
   {
      PdfFile.AddTextPage("HISTOGRAM NOT FOUND");
      return;
   }

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

void AddEfficiencyPlotNoExpand(PdfFileHelper &PdfFile, TFile &F, string HMatch)
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

   AddEfficiencyPlotNoExpand(PdfFile, F, HMatch, HNoMatch);
}

void AddSimplePlotNoExpand(PdfFileHelper &PdfFile, TFile &F, string HName)
{
   PdfFile.AddTextPage(StripFolder(HName));

   TH1D *H = (TH1D *)F.Get(HName.c_str());
   if(H == NULL)
      return;

   H->SetStats(0);

   PdfFile.AddPlot(H, "", false);
   PdfFile.AddPlot(H, "", true);
}

void AddIsolationPlotNoExpand(PdfFileHelper &PdfFile, TFile &F, string HistogramName, double Level)
{
   PdfFile.AddTextPage(StripFolder(HistogramName));

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

   HCumulative->SetMaximum(1.00);
   HCumulative->SetMinimum(0.90);
   HCumulative->Draw();
   Graph.Draw("l");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
}

string ExpandName(string Name)
{
   string TempString = Name;
   for(char &c : TempString)
      if(c == '_')
         c = ' ';
   stringstream str(TempString);

   string Folder = "";
   str >> Folder;

   int Pos = Folder.find("NoMatch");
   if(Pos != string::npos)
      Folder.erase(Folder.begin() + Pos, Folder.begin() + Pos + 7);

   return Folder + "/" + Name;
}

string StripFolder(string Name)
{
   for(char &c : Name)
      if(c == '/')
         c = ' ';
   stringstream str(Name);

   string Temp = "";
   while(str)
      str >> Temp;
   return Temp;
}

