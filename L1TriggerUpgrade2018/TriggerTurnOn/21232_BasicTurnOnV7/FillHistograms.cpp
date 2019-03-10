#include <iostream>
#include <vector>
using namespace std;

#include "fastjet/ClusterSequence.hh"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TDirectory.h"

#include "Code/TauHelperFunctions3.h"
#include "SetStyle.h"
#include "CommandLine.h"
#include "ProgressBar.h"
#include "CustomAssert.h"

#include "Messenger.h"

#include "Histograms.h"

#define QUAL_NONE -1
#define QUAL_ODD -2
#define QUAL_12 -3
#define QUAL_BARRELODDENDCAP2 -4
#define QUAL_USEFLAG -5

int main(int argc, char *argv[]);
FourVector BestInRange(vector<FourVector> &List, double AbsEta);
GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MaxEta = 999, double DRMax = 0.5, int Qual = QUAL_NONE, int Type = -1);
FourVector CalculateHT(vector<FourVector> &GenJets, double Eta, double PT);
FourVector CalculateMHT(vector<FourVector> &GenJets, double Eta, double PT);
void FillHistograms(Histograms &Histogram, FourVector &Object, FourVector &Reference, double Isolation = -1, int Type = -1);
void FillHistograms(Histograms &Histogram, FourVector &Object, double Isolation = -1, int Type = -1);
vector<FourVector> ClusterJets(vector<FourVector> &Particles);
double CalculateGenIsolation(FourVector &P, vector<FourVector> &Particles, double DR = 0.3);
vector<FourVector> CleanUpTaus(vector<FourVector> &Taus, vector<FourVector> &Avoid, double DR = 0.3);
FourVector GetVisTau(L1GenMessenger &MGen, int Index);
FourVector GetVisTauAdhoc(L1GenMessenger &MGen, int Index);

int main(int argc, char *argv[])
{
   fastjet::ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   // Some root styling
   SetThesisStyle();

   // Get arguments
   vector<string> InputFileNames = CL.GetStringVector("input", ',');
   string OutputFileName         = CL.Get("output");
   bool UseStoredGen             = CL.GetBool("StoredGen", true);
   bool DoChargedJet             = CL.GetBool("DoCharged", false);

   // Output File and directories for better organization
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   typedef TDirectory TD;

   TD *GenElectronDirectory        = OutputFile.mkdir("GenElectron",            "Gen electron");
   TD *GenPhotonDirectory          = OutputFile.mkdir("GenPhoton",              "Gen photon");
   TD *GenMuonDirectory            = OutputFile.mkdir("GenMuon",                "Gen Muon");
   TD *GenTauDirectory             = OutputFile.mkdir("GenTau",                 "Gen Tau");
   TD *IsoGenElectronDirectory     = OutputFile.mkdir("IsoGenElectron",         "Isolated gen electron");
   TD *IsoGenPhotonDirectory       = OutputFile.mkdir("IsoGenPhoton",           "Isolated gen photon");
   TD *IsoGenMuonDirectory         = OutputFile.mkdir("IsoGenMuon",             "Isolated gen Muon");

   TD *JetDirectory                = OutputFile.mkdir("Jet",                    "Jet (Gen jet)");
   TD *TkJetDirectory              = OutputFile.mkdir("TkJet",                  "TkJet (Gen jet)");
   TD *TkJetChargedDirectory       = OutputFile.mkdir("TkJetCharged",           "TkJet (Charged jet)");
   TD *TkCaloJetDirectory          = OutputFile.mkdir("TkCaloJet",              "TkCaloJet (Gen jet)");
   TD *PuppiJetWideDirectory       = OutputFile.mkdir("PuppiJetWide",           "PuppiJet (eta 4.7)");
   TD *PuppiJetDirectory           = OutputFile.mkdir("PuppiJet",               "PuppiJet (eta 2.4)");
   
   TD *TkJetLDRDirectory           = OutputFile.mkdir("TkJetLargeDR",           "TkJet (Gen jet)");
   TD *TkCaloJetLDRDirectory       = OutputFile.mkdir("TkCaloJetLargeDR",       "TkCaloJet (Gen jet)");
   TD *PuppiJetLDRDirectory        = OutputFile.mkdir("PuppiJetLargeDR",        "PuppiJet (eta 2.4)");

   TD *MuonDirectory               = OutputFile.mkdir("Muon",                   "Muon (Muon)");
   TD *TkMuonDirectory             = OutputFile.mkdir("TkMuon",                 "TkMuon (Muon)");
   TD *TkMuonEDirectory            = OutputFile.mkdir("TkMuonE",                "TkMuon (Muon, EMTF)");
   TD *TkMuonBDirectory            = OutputFile.mkdir("TkMuonB",                "TkMuon (Muon, non-EMTF)");
   TD *TkMuonODirectory            = OutputFile.mkdir("TkMuonO",                "TkMuon (Muon, non-EMTF)");
   TD *TkMuonStubDirectory         = OutputFile.mkdir("TkMuonStub",             "TkMuonStub (Muon)");
   TD *TkGlbMuonDirectory          = OutputFile.mkdir("TkGlbMuon",              "TkGlbMuon (Muon)");
   TD *PFMuonDirectory             = OutputFile.mkdir("PFMuon",                 "PFMuon (Muon)");
   TD *MuonIsoDirectory            = OutputFile.mkdir("MuonIso",                "Muon (Isolated muon)");
   TD *TkMuonIsoDirectory          = OutputFile.mkdir("TkMuonIso",              "TkMuon (Isolated muon)");
   TD *TkMuonEIsoDirectory         = OutputFile.mkdir("TkMuonEIso",             "TkMuonE (Isolated muon)");
   TD *TkMuonBIsoDirectory         = OutputFile.mkdir("TkMuonBIso",             "TkMuonB (Isolated muon)");
   TD *TkMuonOIsoDirectory         = OutputFile.mkdir("TkMuonOIso",             "TkMuonO (Isolated muon)");
   TD *TkMuonSTubIsoDirectory      = OutputFile.mkdir("TkMuonStubIso",          "TkMuonStub (Isolated muon)");
   TD *TkGlbMuonIsoDirectory       = OutputFile.mkdir("TkGlbMuonIso",           "TkGlbMuon (Isolated muon)");
   TD *PFMuonIsoDirectory          = OutputFile.mkdir("PFMuonIso",              "PFMuon (Isolated muon)");

   TD *MuonLDRDirectory            = OutputFile.mkdir("MuonLargeDR",            "Muon (Muon)");
   TD *TkMuonLDRDirectory          = OutputFile.mkdir("TkMuonLargeDR",          "TkMuon (Muon)");
   TD *TkMuonELDRDirectory         = OutputFile.mkdir("TkMuonELargeDR",         "TkMuonE (Muon)");
   TD *TkMuonBLDRDirectory         = OutputFile.mkdir("TkMuonBLargeDR",         "TkMuonB (Muon)");
   TD *TkMuonOLDRDirectory         = OutputFile.mkdir("TkMuonOLargeDR",         "TkMuonO (Muon)");
   TD *TkMuonStubLDRDirectory      = OutputFile.mkdir("TkMuonStubLargeDR",      "TkMuonStub (Muon)");
   TD *TkGlbMuonLDRDirectory       = OutputFile.mkdir("TkGlbMuonLargeDR",       "TkGlbMuon (Muon)");
   TD *PFMuonLDRDirectory          = OutputFile.mkdir("PFMuonLargeDR",          "PFMuon (Muon)");

   TD *TauDirectory                = OutputFile.mkdir("Tau",                    "Tau (Tau)");
   TD *TkTauDirectory              = OutputFile.mkdir("TkTau",                  "TkTau (Tau)");
   TD *PFTauDirectory              = OutputFile.mkdir("PFTau",                  "PFTau (Tau)");
   TD *PFIsoTauDirectory           = OutputFile.mkdir("PFIsoTau",               "PFIsoTau (Tau)");
   TD *TauLDRDirectory             = OutputFile.mkdir("TauLargeDR",             "Tau (Tau)");
   TD *TkTauLDRDirectory           = OutputFile.mkdir("TkTauLargeDR",           "TkTau (Tau)");
   TD *PFTauLDRDirectory           = OutputFile.mkdir("PFTauLargeDR",           "PFTau (Tau)");
   TD *PFIsoTauLDRDirectory        = OutputFile.mkdir("PFIsoTauLargeDR",        "PFIsoTau (Tau)");

   TD *EGElectronDirectory         = OutputFile.mkdir("EGElectron",             "EG (Electron)");
   TD *EGPhotonDirectory           = OutputFile.mkdir("EGPhoton",               "EG (Photon)");
   TD *TkElectronDirectory         = OutputFile.mkdir("TkElectron",             "TkElectron (Electron)");
   TD *TkElectronLooseDirectory    = OutputFile.mkdir("TkElectronLoose",        "TkElectronLoose (Electron)");
   TD *TkPhotonDirectory           = OutputFile.mkdir("TkPhoton",               "TkPhoton (Photon)");
   TD *TkElectronIsoDirectory      = OutputFile.mkdir("TkElectronIso",          "TkElectron (Iso electron)");
   TD *TkElectronLooseIsoDirectory = OutputFile.mkdir("TkElectronLooseIso",     "TkElectronLoose (Iso electron)");
   TD *TkPhotonIsoDirectory        = OutputFile.mkdir("TkPhotonIso",            "TkPhoton (Iso photon)");
   TD *TkIsoEGIsoDirectory         = OutputFile.mkdir("TkIsoEGIso",             "TkIsoEG (Iso electron)");
   TD *TkIsoEGLooseIsoDirectory    = OutputFile.mkdir("TkIsoEGLooseIso",        "TkIsoEGLoose (Iso electron)");
   TD *TkIsoEMIsoDirectory         = OutputFile.mkdir("TkIsoEMIso",             "TkIsoEM (Iso photon)");
   
   TD *EGElectronLDRDirectory      = OutputFile.mkdir("EGElectronLargeDR",      "EG (Electron)");
   TD *EGPhotonLDRDirectory        = OutputFile.mkdir("EGPhotonLargeDR",        "EG (Photon)");
   TD *TkElectronLDRDirectory      = OutputFile.mkdir("TkElectronLargeDR",      "TkElectron (Electron)");
   TD *TkElectronLooseLDRDirectory = OutputFile.mkdir("TkElectronLooseLargeDR", "TkElectronLoose (Electron)");
   TD *TkPhotonLDRDirectory        = OutputFile.mkdir("TkPhotonLargeDR",        "TkPhoton (Photon)");

   TD *TkHT1Directory              = OutputFile.mkdir("TkHT1",                  "HT from TkJet (1)");
   TD *TkMHT1Directory             = OutputFile.mkdir("TkMHT1",                 "MHT from TkJet (1)");
   TD *TkHT2Directory              = OutputFile.mkdir("TkHT2",                  "HT from TkJet (2)");
   TD *TkMHT2Directory             = OutputFile.mkdir("TkMHT2",                 "MHT from TkJet (2)");
   TD *TkHT3Directory              = OutputFile.mkdir("TkHT3",                  "HT from TkJet (3)");
   TD *TkMHT3Directory             = OutputFile.mkdir("TkMHT3",                 "MHT from TkJet (3)");
   TD *TkHT4Directory              = OutputFile.mkdir("TkHT4",                  "HT from TkJet (4)");
   TD *TkMHT4Directory             = OutputFile.mkdir("TkMHT4",                 "MHT from TkJet (4)");
   TD *TkHT5Directory              = OutputFile.mkdir("TkHT5",                  "HT from TkJet (5)");
   TD *TkMHT5Directory             = OutputFile.mkdir("TkMHT5",                 "MHT from TkJet (5)");
   TD *TkMETDirectory              = OutputFile.mkdir("TkMET",                  "MET from Tk");
   TD *PuppiHT1Directory           = OutputFile.mkdir("PuppiHT1",               "HT from PuppiJet (1)");
   TD *PuppiMHT1Directory          = OutputFile.mkdir("PuppiMHT1",              "MHT from PuppiJet (1)");
   TD *PuppiHT2Directory           = OutputFile.mkdir("PuppiHT2",               "HT from PuppiJet (2)");
   TD *PuppiMHT2Directory          = OutputFile.mkdir("PuppiMHT2",              "MHT from PuppiJet (2)");
   TD *PuppiHT3Directory           = OutputFile.mkdir("PuppiHT3",               "HT from PuppiJet (3)");
   TD *PuppiMHT3Directory          = OutputFile.mkdir("PuppiMHT3",              "MHT from PuppiJet (3)");
   TD *PuppiMETDirectory           = OutputFile.mkdir("PuppiMET",               "MET from Puppi");

   // Create histograms
   vector<double> GenThresholds  = {0};
   vector<double> JetThresholds  = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60,
      75, 80, 85, 90, 100, 125, 150, 175, 200, 225, 250, 275, 300};
   vector<double> MuonThresholds = {0, 3, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30};
   vector<double> TauThresholds  = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30, 40, 50, 60, 70, 80, 90, 100};
   vector<double> EGThresholds   = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30};
   vector<double> HTThresholds   = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 125, 150,
      175, 200, 225, 250, 300, 325, 350, 375, 400, 425, 450, 475, 500};
   
   Histograms HGenElectron       (200, 0, 150,  50, -3.5, 3.5, 200, 0, 5.0, GenThresholds,  "GenElectron");
   Histograms HGenPhoton         (200, 0, 150,  50, -3.5, 3.5, 200, 0, 5.0, GenThresholds,  "GenPhoton");
   Histograms HGenMuon           (200, 0, 150,  50, -3.5, 3.5, 200, 0, 5.0, GenThresholds,  "GenMuon");
   Histograms HGenTau            (200, 0, 150,  50, -3.5, 3.5, 200, 0, 5.0, GenThresholds,  "GenTau");
   Histograms HIsoGenElectron    (200, 0, 150,  50, -3.5, 3.5, 200, 0, 0.2, GenThresholds,  "IsoGenElectron");
   Histograms HIsoGenPhoton      (200, 0, 150,  50, -3.5, 3.5, 200, 0, 0.2, GenThresholds,  "IsoGenPhoton");
   Histograms HIsoGenMuon        (200, 0, 150,  50, -3.5, 3.5, 200, 0, 0.2, GenThresholds,  "IsoGenMuon");
   
   Histograms HJet               (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "Jet");
   Histograms HTkJet             (200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,  "TkJet");
   Histograms HTkJetCharged      (200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,  "TkJetCharged");
   Histograms HTkCaloJet         (500, 0, 500,  50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "TkCaloJet");
   Histograms HPuppiJetWide      (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "PuppiJetWide");
   Histograms HPuppiJet          (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "PuppiJet");

   Histograms HTkJetLDR          (200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,  "TkJetLargeDR");
   Histograms HTkCaloJetLDR      (500, 0, 500,  50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "TkCaloJetLargeDR");
   Histograms HPuppiJetLDR       (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "PuppiJetLargeDR");

   Histograms HTkMuon            (150, 0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuon");
   Histograms HTkMuonE           (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonE");
   Histograms HTkMuonB           (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonB");
   Histograms HTkMuonO           (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonO");
   Histograms HTkMuonStub        (150, 0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonStub");
   Histograms HTkGlbMuon         (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkGlbMuon");
   Histograms HPFMuon            (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "PFMuon");
   Histograms HTkMuonIso         (150, 0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonIso");
   Histograms HTkMuonEIso        (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonEIso");
   Histograms HTkMuonBIso        (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonBIso");
   Histograms HTkMuonOIso        (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonOIso");
   Histograms HTkMuonStubIso     (150, 0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonStubIso");
   Histograms HTkGlbMuonIso      (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkGlbMuonIso");
   Histograms HPFMuonIso         (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "PFMuonIso");

   Histograms HTkMuonLDR         (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonLargeDR");
   Histograms HTkMuonELDR        (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonELargeDR");
   Histograms HTkMuonBLDR        (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonBLargeDR");
   Histograms HTkMuonOLDR        (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonOLargeDR");
   Histograms HTkMuonStubLDR     (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkMuonStubLargeDR");
   Histograms HTkGlbMuonLDR      (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkGlbMuonLargeDR");
   Histograms HPFMuonLDR         (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "PFMuonLargeDR");
   
   Histograms HTau               (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, TauThresholds,  "Tau");
   Histograms HTkTau             (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, TauThresholds,  "TkTau");
   Histograms HPFTau             (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, TauThresholds,  "PFTau");
   Histograms HPFIsoTau          (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, TauThresholds,  "PFIsoTau");
   
   Histograms HTauLDR            (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, TauThresholds,  "TauLargeDR");
   Histograms HTkTauLDR          (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, TauThresholds,  "TkTauLargeDR");
   Histograms HPFTauLDR          (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, TauThresholds,  "PFTauLargeDR");
   Histograms HPFIsoTauLDR       (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, TauThresholds,  "PFIsoTauLargeDR");

   Histograms HEGElectron        (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, EGThresholds,   "EGElectron");
   Histograms HEGPhoton          (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, EGThresholds,   "EGPhoton");

   Histograms HTkElectron        (75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,   "TkElectron");
   Histograms HTkElectronLoose   (75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,   "TkElectronLoose");
   Histograms HTkPhoton          (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "TkPhoton");
   Histograms HTkElectronIso     (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,   "TkElectronIso");
   Histograms HTkElectronLooseIso(75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,   "TkElectronLooseIso");
   Histograms HTkPhotonIso       (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "TkPhotonIso");
   Histograms HTkIsoEGIso        (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,   "TkIsoEGIso");
   Histograms HTkIsoEGLooseIso   (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,   "TkIsoEGLooseIso");
   Histograms HTkIsoEMIso        (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "TkIsoEMIso");

   Histograms HEGElectronLDR     (75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,   "EGElectronLargeDR");
   Histograms HEGPhotonLDR       (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "EGPhotonLargeDR");
   Histograms HTkElectronLDR     (75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,   "TkElectronLargeDR");
   Histograms HTkElectronLooseLDR(75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,   "TkElectronLooseLargeDR");
   Histograms HTkPhotonLDR       (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "TkPhotonLargeDR");

   Histograms HTkHT1             (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT1");
   Histograms HTkMHT1            (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT1");
   Histograms HTkHT2             (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT2");
   Histograms HTkMHT2            (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT2");
   Histograms HTkHT3             (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT3");
   Histograms HTkMHT3            (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT3");
   Histograms HTkHT4             (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT4");
   Histograms HTkMHT4            (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT4");
   Histograms HTkHT5             (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT5");
   Histograms HTkMHT5            (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT5");
   Histograms HTkMET             (500, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMET");

   Histograms HPuppiHT1          (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiHT1");
   Histograms HPuppiMHT1         (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiMHT1");
   Histograms HPuppiHT2          (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiHT2");
   Histograms HPuppiMHT2         (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiMHT2");
   Histograms HPuppiHT3          (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiHT3");
   Histograms HPuppiMHT3         (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiMHT3");
   Histograms HPuppiMET          (200, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiMET");

   for(string InputFileName : InputFileNames)
   {
      cout << "Processing file " << InputFileName << endl;

      // Input File
      TFile File(InputFileName.c_str());

      // Messengers
      L1GenMessenger MGen(File, "genTree/L1GenTree");
      L1PhaseIITreeV7Messenger MPhaseII(File, "l1PhaseIITree/L1PhaseIITree");

      if(MGen.Tree == NULL)
         return -1;

      // Loop over events
      int EntryCount = MGen.Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         Bar.Print();

         MGen.GetEntry(iE);
         MPhaseII.GetEntry(iE);

         vector<FourVector> Electrons;
         vector<FourVector> Photons;
         vector<FourVector> Muons;
         vector<FourVector> Taus;
         vector<FourVector> ChargedParticles;
         vector<FourVector> Particles;

         // Collect gen-particles
         for(int i = 0; i < (int)MGen.GenP.size(); i++)
         {
            int AbsID = MGen.GenID[i];
            if(AbsID < 0)
               AbsID = -AbsID;

            if(AbsID == 12 || AbsID == 14 || AbsID == 16)
               continue;

            if(AbsID == 11)
               Electrons.push_back(MGen.GenP[i]);
            if(AbsID == 22)
               Photons.push_back(MGen.GenP[i]);
            if(AbsID == 13)
               Muons.push_back(MGen.GenP[i]);
            if(AbsID == 15)
            {
               FourVector P = GetVisTauAdhoc(MGen, i);
               if(P[0] > 0)
                  Taus.push_back(P);
            }

            if(MGen.GenStatus[i] == 1)   // we only want final state particles here
               Particles.push_back(MGen.GenP[i]);
            if(MGen.GenStatus[i] == 1 && MGen.GenCharge[i] != 0)
               ChargedParticles.push_back(MGen.GenP[i]);
         }

         // Taus = CleanUpTaus(Taus, Electrons);
         // Taus = CleanUpTaus(Taus, Muons);

         // Cluster jets
         vector<FourVector> GenJets        = (UseStoredGen ? MGen.GenJet : ClusterJets(Particles));
         vector<FourVector> ChargedGenJets = ClusterJets(ChargedParticles);

         // Reference objects
         FourVector BestGenJet        = BestInRange(GenJets,           4.7);
         FourVector BestCentralGenJet = BestInRange(GenJets,           2.4);
         FourVector BestBarrelGenJet  = BestInRange(GenJets,           1.5);
         FourVector BestChargedGenJet = BestInRange(ChargedGenJets,    2.4);

         FourVector BestElectron      = BestInRange(Electrons,         2.4);
         FourVector BestPhoton        = BestInRange(Photons,           2.4);
         FourVector BestMuon          = BestInRange(Muons,             2.4);
         FourVector BestMuonBarrel    = BestInRange(Muons,             1.0);
         FourVector BestTau           = BestInRange(Taus,              2.1);
         FourVector BestTauBarrel     = BestInRange(Taus,              1.5);

         FourVector GenHTForPuppi1    = CalculateHT(GenJets,           2.4, 15);
         FourVector GenMHTForPuppi1   = CalculateMHT(GenJets,          2.4, 15);
         FourVector GenHTForPuppi2    = CalculateHT(GenJets,           2.4, 20);
         FourVector GenMHTForPuppi2   = CalculateMHT(GenJets,          2.4, 20);
         FourVector GenHTForPuppi3    = CalculateHT(GenJets,           2.4, 30);
         FourVector GenMHTForPuppi3   = CalculateMHT(GenJets,          2.4, 30);
         FourVector GenMETForPuppi    = (UseStoredGen ? MGen.GenMETTrue : CalculateMHT(Particles, 2.4, 0));
         FourVector GenHTForTk1       = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets),    2.4, 5);
         FourVector GenMHTForTk1      = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets),   2.4, 5);
         FourVector GenHTForTk2       = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets),    2.4, 10);
         FourVector GenMHTForTk2      = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets),   2.4, 10);
         FourVector GenHTForTk3       = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets),    2.4, 15);
         FourVector GenMHTForTk3      = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets),   2.4, 15);
         FourVector GenHTForTk4       = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets),    2.4, 20);
         FourVector GenMHTForTk4      = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets),   2.4, 20);
         FourVector GenHTForTk5       = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets),    2.4, 30);
         FourVector GenMHTForTk5      = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets),   2.4, 30);
         FourVector GenMETForTk       = (DoChargedJet ? CalculateMHT(ChargedParticles, 2.4, 0) : GenMETForPuppi);

         // Gen Isolations
         double GenElectronIsolation   = CalculateGenIsolation(BestElectron,   Particles, 0.3);
         double GenPhotonIsolation     = CalculateGenIsolation(BestPhoton,     Particles, 0.3);
         double GenMuonIsolation       = CalculateGenIsolation(BestMuon,       Particles, 0.3);
         double GenMuonBarrelIsolation = CalculateGenIsolation(BestMuonBarrel, Particles, 0.3);
         double GenTauIsolation        = CalculateGenIsolation(BestTau,        Particles, 0.3);
         double GenTauBarrelIsolation  = CalculateGenIsolation(BestTauBarrel,  Particles, 0.3);

         FourVector BestIsoElectron(-1, 0, 0, 0);
         FourVector BestIsoPhoton(-1, 0, 0, 0);
         FourVector BestIsoMuon(-1, 0, 0, 0);
         FourVector BestIsoMuonBarrel(-1, 0, 0, 0);

         if(GenElectronIsolation < 0.15)
            BestIsoElectron = BestElectron;
         if(GenPhotonIsolation < 0.15)
            BestIsoPhoton = BestPhoton;
         if(GenMuonIsolation < 0.15)
            BestIsoMuon = BestMuon;
         if(GenMuonBarrelIsolation < 0.15)
            BestIsoMuonBarrel = BestMuonBarrel;

         typedef GenericObject GO;

         // Best L1 objects
         int Qual = QUAL_NONE;
         GO BestL1Jet                = BestInRange(MPhaseII.Jet,             BestGenJet,        4.7, 0.3, Qual);
         GO BestL1TkJet              = BestInRange(MPhaseII.TrackerJet,      BestCentralGenJet, 2.4, 0.3, Qual);
         GO BestL1TkJetCharged       = BestInRange(MPhaseII.TrackerJet,      BestChargedGenJet, 2.4, 0.3, Qual);
         GO BestL1TkCaloJet          = BestInRange(MPhaseII.TkCaloJet,       BestBarrelGenJet,  1.5, 0.3, Qual);
         GO BestL1PuppiJet           = BestInRange(MPhaseII.PuppiJet,        BestGenJet,        4.7, 0.3, Qual);
         GO BestL1CenPuppiJet        = BestInRange(MPhaseII.PuppiJet,        BestCentralGenJet, 2.4, 0.3, Qual);
         
         Qual = QUAL_NONE;
         GO BestL1TkJetLDR           = BestInRange(MPhaseII.TrackerJet,      BestCentralGenJet, 2.4, 1.0, Qual);
         GO BestL1TkCaloJetLDR       = BestInRange(MPhaseII.TkCaloJet,       BestBarrelGenJet,  1.5, 1.0, Qual);
         GO BestL1CenPuppiJetLDR     = BestInRange(MPhaseII.PuppiJet,        BestCentralGenJet, 2.4, 1.0, Qual);

         Qual = QUAL_12;
         GO BestL1TkMuon             = BestInRange(MPhaseII.TkMuon,          BestMuon,          2.4, 0.1, Qual);
         GO BestL1TkMuonE            = BestInRange(MPhaseII.TkMuon,          BestMuon,          2.4, 0.1, Qual, 3);
         GO BestL1TkMuonB            = BestInRange(MPhaseII.TkMuon,          BestMuon,          2.4, 0.1, Qual, 1);
         GO BestL1TkMuonO            = BestInRange(MPhaseII.TkMuon,          BestMuon,          2.4, 0.1, Qual, 2);
         GO BestL1TkMuonIso          = BestInRange(MPhaseII.TkMuon,          BestIsoMuon,       2.4, 0.1, Qual);
         GO BestL1TkMuonEIso         = BestInRange(MPhaseII.TkMuon,          BestIsoMuon,       2.4, 0.1, Qual, 3);
         GO BestL1TkMuonBIso         = BestInRange(MPhaseII.TkMuon,          BestIsoMuon,       2.4, 0.1, Qual, 1);
         GO BestL1TkMuonOIso         = BestInRange(MPhaseII.TkMuon,          BestIsoMuon,       2.4, 0.1, Qual, 2);
         GO BestL1TkMuonStub         = BestInRange(MPhaseII.TkMuonStub,      BestMuon,          2.4, 0.1, Qual);
         GO BestL1TkMuonStubIso      = BestInRange(MPhaseII.TkMuonStub,      BestIsoMuon,       2.4, 0.1, Qual);
         GO BestL1TkGlbMuon          = BestInRange(MPhaseII.TkGlbMuon,       BestMuon,          2.4, 0.1, Qual);
         GO BestL1TkGlbMuonIso       = BestInRange(MPhaseII.TkGlbMuon,       BestIsoMuon,       2.4, 0.1, Qual);
         Qual = QUAL_NONE;
         GO BestL1PFMuon             = BestInRange(MPhaseII.PFMuon,          BestMuon,          2.4, 0.1, Qual);
         GO BestL1PFMuonIso          = BestInRange(MPhaseII.PFMuon,          BestIsoMuon,       2.4, 0.1, Qual);

         Qual = QUAL_12;
         GO BestL1TkMuonLDR          = BestInRange(MPhaseII.TkMuon,          BestMuon,          2.4, 1.0, Qual);
         GO BestL1TkMuonELDR         = BestInRange(MPhaseII.TkMuon,          BestMuon,          2.4, 1.0, Qual, 3);
         GO BestL1TkMuonBLDR         = BestInRange(MPhaseII.TkMuon,          BestMuon,          2.4, 1.0, Qual, 1);
         GO BestL1TkMuonOLDR         = BestInRange(MPhaseII.TkMuon,          BestMuon,          2.4, 1.0, Qual, 2);
         GO BestL1TkMuonStubLDR      = BestInRange(MPhaseII.TkMuonStub,      BestMuon,          2.4, 1.0, Qual);
         GO BestL1TkGlbMuonLDR       = BestInRange(MPhaseII.TkGlbMuon,       BestMuon,          2.4, 1.0, Qual);
         Qual = QUAL_NONE;
         GO BestL1PFMuonLDR          = BestInRange(MPhaseII.PFMuon,          BestMuon,          2.4, 1.0, Qual);

         Qual = QUAL_NONE;
         GO BestL1Tau                = BestInRange(MPhaseII.Tau,             BestTauBarrel,     1.5, 0.2, Qual);
         GO BestL1TkTau              = BestInRange(MPhaseII.TkTau,           BestTauBarrel,     1.5, 0.15, Qual);
         GO BestL1PFTau              = BestInRange(MPhaseII.PFTau,           BestTau,           2.1, 0.3, Qual);

         Qual = QUAL_NONE;
         GO BestL1TauLDR             = BestInRange(MPhaseII.Tau,             BestTauBarrel,     1.5, 1.0, Qual);
         GO BestL1TkTauLDR           = BestInRange(MPhaseII.TkTau,           BestTauBarrel,     1.5, 1.0, Qual);
         GO BestL1PFTauLDR           = BestInRange(MPhaseII.PFTau,           BestTau,           2.1, 1.0, Qual);

         Qual = QUAL_USEFLAG;
         GO BestL1EGElectron         = BestInRange(MPhaseII.EG,              BestElectron,      2.4, 0.2, Qual);
         GO BestL1EGPhoton           = BestInRange(MPhaseII.EG,              BestPhoton,        2.4, 0.2, Qual);
         GO BestL1TkElectron         = BestInRange(MPhaseII.TkElectron,      BestElectron,      2.4, 0.2, Qual);
         GO BestL1TkElectronLoose    = BestInRange(MPhaseII.TkElectronLoose, BestElectron,      2.4, 0.2, Qual);
         GO BestL1TkPhoton           = BestInRange(MPhaseII.TkPhoton,        BestPhoton,        2.4, 0.2, Qual);
         GO BestL1TkElectronIso      = BestInRange(MPhaseII.TkElectron,      BestElectron,      2.4, 0.2, Qual);
         GO BestL1TkElectronLooseIso = BestInRange(MPhaseII.TkElectronLoose, BestElectron,      2.4, 0.2, Qual);
         GO BestL1TkPhotonIso        = BestInRange(MPhaseII.TkPhoton,        BestPhoton,        2.4, 0.2, Qual);

         Qual = QUAL_USEFLAG;
         GO BestL1EGElectronLDR      = BestInRange(MPhaseII.EG,              BestElectron,      2.4, 1.0, Qual);
         GO BestL1EGPhotonLDR        = BestInRange(MPhaseII.EG,              BestPhoton,        2.4, 1.0, Qual);
         GO BestL1TkElectronLDR      = BestInRange(MPhaseII.TkElectron,      BestElectron,      2.4, 1.0, Qual);
         GO BestL1TkElectronLooseLDR = BestInRange(MPhaseII.TkElectronLoose, BestElectron,      2.4, 1.0, Qual);
         GO BestL1TkPhotonLDR        = BestInRange(MPhaseII.TkPhoton,        BestPhoton,        2.4, 1.0, Qual);

         // Some HT four-vectors
         FourVector TkHT1 =     MPhaseII.TrackerHT[0].P;
         FourVector TkMHT1 =    MPhaseII.TrackerMHT[0].P;
         FourVector TkHT2 =     MPhaseII.TrackerHT[1].P;
         FourVector TkMHT2 =    MPhaseII.TrackerMHT[1].P;
         FourVector TkHT3 =     MPhaseII.TrackerHT[2].P;
         FourVector TkMHT3 =    MPhaseII.TrackerMHT[2].P;
         FourVector TkHT4 =     MPhaseII.TrackerHT[3].P;
         FourVector TkMHT4 =    MPhaseII.TrackerMHT[3].P;
         FourVector TkHT5 =     MPhaseII.TrackerHT[4].P;
         FourVector TkMHT5 =    MPhaseII.TrackerMHT[4].P;
         FourVector TkMET =     MPhaseII.TrackerMET[0].P;
         FourVector PuppiHT1 =  MPhaseII.PuppiHT[0].P;
         FourVector PuppiMHT1 = MPhaseII.PuppiMHT[0].P;
         FourVector PuppiHT2 =  MPhaseII.PuppiHT[1].P;
         FourVector PuppiMHT2 = MPhaseII.PuppiMHT[1].P;
         FourVector PuppiHT3 =  MPhaseII.PuppiHT[2].P;
         FourVector PuppiMHT3 = MPhaseII.PuppiMHT[2].P;
         FourVector PuppiMET =  MPhaseII.PuppiMET[0].P;

         bool PassL1TkElectronIso = false;
         bool PassL1TkElectronLooseIso = false;
         bool PassL1TkPhotonIso = false;
         bool PassL1PFTauIso = (BestL1PFTau.Flag > 3);
         if(BestL1TkElectron.P.GetAbsEta() < 1.5 && BestL1TkElectron.Iso < 0.12)             PassL1TkElectronIso = true;
         if(BestL1TkElectron.P.GetAbsEta() > 1.5 && BestL1TkElectron.Iso < 0.30)             PassL1TkElectronIso = true;
         if(BestL1TkElectronLoose.P.GetAbsEta() < 1.5 && BestL1TkElectronLoose.Iso < 0.34)   PassL1TkElectronLooseIso = true;
         if(BestL1TkElectronLoose.P.GetAbsEta() > 1.5 && BestL1TkElectronLoose.Iso < 0.34)   PassL1TkElectronLooseIso = true;
         if(BestL1TkPhoton.P.GetAbsEta() < 1.5 && BestL1TkPhoton.Iso < 0.28)             PassL1TkPhotonIso = true;
         if(BestL1TkPhoton.P.GetAbsEta() > 1.5 && BestL1TkPhoton.Iso < 0.36)             PassL1TkPhotonIso = true;

         // Fill Histograms
         FillHistograms(HGenElectron,        BestElectron,               GenElectronIsolation);
         FillHistograms(HGenPhoton,          BestPhoton,                 GenPhotonIsolation);
         FillHistograms(HGenMuon,            BestMuon,                   GenMuonIsolation);
         FillHistograms(HGenTau,             BestTau,                    GenTauIsolation);
         FillHistograms(HIsoGenElectron,     BestIsoElectron,            GenElectronIsolation);
         FillHistograms(HIsoGenPhoton,       BestIsoPhoton,              GenPhotonIsolation);
         FillHistograms(HIsoGenMuon,         BestIsoMuon,                GenMuonIsolation);

         FillHistograms(HJet,                BestL1Jet.P,                BestGenJet);
         FillHistograms(HTkJet,              BestL1TkJet.P,              BestCentralGenJet);
         FillHistograms(HTkJetCharged,       BestL1TkJet.P,              BestChargedGenJet);
         FillHistograms(HTkCaloJet,          BestL1TkCaloJet.P,          BestBarrelGenJet);
         FillHistograms(HPuppiJetWide,       BestL1PuppiJet.P,           BestGenJet);
         FillHistograms(HPuppiJet,           BestL1CenPuppiJet.P,        BestCentralGenJet);
         
         FillHistograms(HTkJetLDR,           BestL1TkJetLDR.P,           BestCentralGenJet);
         FillHistograms(HTkCaloJetLDR,       BestL1TkCaloJetLDR.P,       BestBarrelGenJet);
         FillHistograms(HPuppiJetLDR,        BestL1CenPuppiJetLDR.P,     BestCentralGenJet);

         FillHistograms(HTkMuon,             BestL1TkMuon.P,             BestMuon,        BestL1TkMuon.Iso);
         FillHistograms(HTkMuonE,            BestL1TkMuonE.P,            BestMuon,        BestL1TkMuonE.Iso);
         FillHistograms(HTkMuonB,            BestL1TkMuonB.P,            BestMuon,        BestL1TkMuonB.Iso);
         FillHistograms(HTkMuonO,            BestL1TkMuonO.P,            BestMuon,        BestL1TkMuonO.Iso);
         FillHistograms(HTkMuonStub,         BestL1TkMuonStub.P,         BestMuon,        BestL1TkMuonStub.Iso);
         FillHistograms(HTkGlbMuon,          BestL1TkGlbMuon.P,          BestMuon,        BestL1TkGlbMuon.Iso);
         FillHistograms(HPFMuon,             BestL1PFMuon.P,             BestMuon,        BestL1PFMuon.Iso);
         FillHistograms(HTkMuonIso,          BestL1TkMuon.P,             BestIsoMuon,     BestL1TkMuon.Iso);
         FillHistograms(HTkMuonEIso,         BestL1TkMuonE.P,            BestIsoMuon,     BestL1TkMuonE.Iso);
         FillHistograms(HTkMuonBIso,         BestL1TkMuonB.P,            BestIsoMuon,     BestL1TkMuonB.Iso);
         FillHistograms(HTkMuonOIso,         BestL1TkMuonO.P,            BestIsoMuon,     BestL1TkMuonO.Iso);
         FillHistograms(HTkMuonIso,          BestL1TkMuonStub.P,         BestIsoMuon,     BestL1TkMuonStub.Iso);
         FillHistograms(HTkGlbMuonIso,       BestL1TkGlbMuon.P,          BestIsoMuon,     BestL1TkGlbMuon.Iso);
         FillHistograms(HPFMuonIso,          BestL1PFMuon.P,             BestIsoMuon,     BestL1PFMuon.Iso);

         FillHistograms(HTkMuonLDR,          BestL1TkMuonLDR.P,          BestMuon,        BestL1TkMuon.Iso);
         FillHistograms(HTkMuonELDR,         BestL1TkMuonELDR.P,         BestMuon,        BestL1TkMuonE.Iso);
         FillHistograms(HTkMuonBLDR,         BestL1TkMuonBLDR.P,         BestMuon,        BestL1TkMuonB.Iso);
         FillHistograms(HTkMuonOLDR,         BestL1TkMuonOLDR.P,         BestMuon,        BestL1TkMuonO.Iso);
         FillHistograms(HTkMuonStubLDR,      BestL1TkMuonStubLDR.P,      BestMuon,        BestL1TkMuonStub.Iso);
         FillHistograms(HTkGlbMuonLDR,       BestL1TkGlbMuonLDR.P,       BestMuon,        BestL1TkGlbMuon.Iso);
         FillHistograms(HPFMuonLDR,          BestL1PFMuonLDR.P,          BestMuon,        BestL1PFMuon.Iso);
         
         FillHistograms(HTau,                BestL1Tau.P,                BestTauBarrel,   BestL1Tau.Iso);
         FillHistograms(HTkTau,              BestL1TkTau.P,              BestTauBarrel,   BestL1TkTau.Iso);
         FillHistograms(HPFTau,              BestL1PFTau.P,              BestTau,         BestL1PFTau.Iso);
         if(PassL1PFTauIso)
         FillHistograms(HPFIsoTau,           BestL1PFTau.P,              BestTau,         BestL1PFTau.Iso);
         
         FillHistograms(HTauLDR,             BestL1TauLDR.P,             BestTauBarrel,   BestL1Tau.Iso);
         FillHistograms(HTkTauLDR,           BestL1TkTauLDR.P,           BestTauBarrel,   BestL1TkTau.Iso);
         FillHistograms(HPFTauLDR,           BestL1PFTauLDR.P,           BestTau,         BestL1PFTau.Iso);
         if(PassL1PFTauIso)
         FillHistograms(HPFIsoTauLDR,        BestL1PFTauLDR.P,           BestTau,         BestL1PFTau.Iso);

         FillHistograms(HEGElectron,         BestL1EGElectron.P,         BestElectron,    BestL1EGElectron.Iso, BestL1EGElectron.Type);
         FillHistograms(HEGPhoton,           BestL1EGPhoton.P,           BestPhoton,      BestL1EGPhoton.Iso, BestL1EGPhoton.Type);
         FillHistograms(HTkElectron,         BestL1TkElectron.P,         BestElectron,    BestL1TkElectron.Iso, BestL1TkElectron.Type);
         FillHistograms(HTkElectronLoose,    BestL1TkElectronLoose.P,    BestElectron,    BestL1TkElectronLoose.Iso, BestL1TkElectronLoose.Type);
         FillHistograms(HTkPhoton,           BestL1TkPhoton.P,           BestPhoton,      BestL1TkPhoton.Iso, BestL1TkPhoton.Type);
         FillHistograms(HTkElectronIso,      BestL1TkElectron.P,         BestIsoElectron, BestL1TkElectron.Iso, BestL1TkElectron.Type);
         FillHistograms(HTkElectronLooseIso, BestL1TkElectronLoose.P,    BestIsoElectron, BestL1TkElectronLoose.Iso, BestL1TkElectronLoose.Type);
         FillHistograms(HTkPhotonIso,        BestL1TkPhoton.P,           BestIsoPhoton,   BestL1TkPhoton.Iso, BestL1TkPhoton.Type);
         if(PassL1TkElectronIso)
         FillHistograms(HTkIsoEGIso,         BestL1TkElectron.P,         BestIsoElectron, BestL1TkElectron.Iso, BestL1TkElectron.Type);
         if(PassL1TkElectronLooseIso)
         FillHistograms(HTkIsoEGLooseIso,    BestL1TkElectronLoose.P,    BestIsoElectron, BestL1TkElectronLoose.Iso, BestL1TkElectronLoose.Type);
         if(PassL1TkPhotonIso)
         FillHistograms(HTkIsoEMIso,         BestL1TkPhoton.P,           BestIsoPhoton,   BestL1TkPhoton.Iso, BestL1TkPhoton.Type);

         FillHistograms(HEGElectronLDR,      BestL1EGElectronLDR.P,      BestElectron,    BestL1EGElectronLDR.Iso, BestL1EGElectronLDR.Type);
         FillHistograms(HEGPhotonLDR,        BestL1EGPhotonLDR.P,        BestPhoton,      BestL1EGPhotonLDR.Iso, BestL1EGPhotonLDR.Type);
         FillHistograms(HTkElectronLDR,      BestL1TkElectronLDR.P,      BestElectron,    BestL1TkElectronLDR.Iso, BestL1TkElectronLDR.Type);
         FillHistograms(HTkElectronLooseLDR, BestL1TkElectronLooseLDR.P, BestElectron,                            BestL1TkElectronLooseLDR.Iso, BestL1TkElectronLooseLDR.Type);
         FillHistograms(HTkPhotonLDR,        BestL1TkPhotonLDR.P,        BestPhoton,      BestL1TkPhotonLDR.Iso, BestL1TkPhotonLDR.Type);

         FillHistograms(HTkHT1,           TkHT1,                  GenHTForTk1);
         FillHistograms(HTkMHT1,          TkMHT1,                 GenMHTForTk1);
         FillHistograms(HTkHT2,           TkHT2,                  GenHTForTk2);
         FillHistograms(HTkMHT2,          TkMHT2,                 GenMHTForTk2);
         FillHistograms(HTkHT3,           TkHT3,                  GenHTForTk3);
         FillHistograms(HTkMHT3,          TkMHT3,                 GenMHTForTk3);
         FillHistograms(HTkHT4,           TkHT4,                  GenHTForTk4);
         FillHistograms(HTkMHT4,          TkMHT4,                 GenMHTForTk4);
         FillHistograms(HTkHT5,           TkHT5,                  GenHTForTk5);
         FillHistograms(HTkMHT5,          TkMHT5,                 GenMHTForTk5);
         FillHistograms(HTkMET,           TkMET,                  GenMETForTk);
         
         FillHistograms(HPuppiHT1,        PuppiHT1,               GenHTForPuppi1);
         FillHistograms(HPuppiMHT1,       PuppiMHT1,              GenMHTForPuppi1);
         FillHistograms(HPuppiHT2,        PuppiHT2,               GenHTForPuppi2);
         FillHistograms(HPuppiMHT2,       PuppiMHT2,              GenMHTForPuppi2);
         FillHistograms(HPuppiHT3,        PuppiHT3,               GenHTForPuppi3);
         FillHistograms(HPuppiMHT3,       PuppiMHT3,              GenMHTForPuppi3);
         FillHistograms(HPuppiMET,        PuppiMET,               GenMETForPuppi);
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   // Write result to file
   HGenElectron.Write(GenElectronDirectory);
   HGenPhoton.Write(GenPhotonDirectory);
   HGenMuon.Write(GenMuonDirectory);
   HGenTau.Write(GenTauDirectory);
   HIsoGenElectron.Write(IsoGenElectronDirectory);
   HIsoGenPhoton.Write(IsoGenPhotonDirectory);
   HIsoGenMuon.Write(IsoGenMuonDirectory);
   HJet.Write(JetDirectory);
   HTkJet.Write(TkJetDirectory);
   HTkJetCharged.Write(TkJetChargedDirectory);
   HTkCaloJet.Write(TkCaloJetDirectory);
   HPuppiJetWide.Write(PuppiJetWideDirectory);
   HPuppiJet.Write(PuppiJetDirectory);
   HTkJetLDR.Write(TkJetLDRDirectory);
   HTkCaloJetLDR.Write(TkCaloJetLDRDirectory);
   HPuppiJetLDR.Write(PuppiJetLDRDirectory);
   HTkMuon.Write(TkMuonDirectory);
   HTkMuonE.Write(TkMuonEDirectory);
   HTkMuonB.Write(TkMuonBDirectory);
   HTkMuonO.Write(TkMuonODirectory);
   HTkGlbMuon.Write(TkGlbMuonDirectory);
   HPFMuon.Write(PFMuonDirectory);
   HTkMuonIso.Write(TkMuonIsoDirectory);
   HTkMuonEIso.Write(TkMuonEIsoDirectory);
   HTkMuonBIso.Write(TkMuonBIsoDirectory);
   HTkMuonOIso.Write(TkMuonOIsoDirectory);
   HTkGlbMuonIso.Write(TkGlbMuonIsoDirectory);
   HPFMuonIso.Write(PFMuonIsoDirectory);
   HTkMuonLDR.Write(TkMuonLDRDirectory);
   HTkMuonELDR.Write(TkMuonELDRDirectory);
   HTkMuonBLDR.Write(TkMuonBLDRDirectory);
   HTkMuonOLDR.Write(TkMuonOLDRDirectory);
   HTkGlbMuonLDR.Write(TkGlbMuonLDRDirectory);
   HPFMuonLDR.Write(PFMuonLDRDirectory);
   HTau.Write(TauDirectory);
   HTkTau.Write(TkTauDirectory);
   HPFTau.Write(PFTauDirectory);
   HPFIsoTau.Write(PFIsoTauDirectory);
   HTauLDR.Write(TauLDRDirectory);
   HTkTauLDR.Write(TkTauLDRDirectory);
   HPFTauLDR.Write(PFTauLDRDirectory);
   HPFIsoTauLDR.Write(PFIsoTauLDRDirectory);
   HEGElectron.Write(EGElectronDirectory);
   HEGPhoton.Write(EGPhotonDirectory);
   HTkElectron.Write(TkElectronDirectory);
   HTkElectronLoose.Write(TkElectronLooseDirectory);
   HTkPhoton.Write(TkPhotonDirectory);
   HTkElectronIso.Write(TkElectronIsoDirectory);
   HTkElectronLooseIso.Write(TkElectronLooseIsoDirectory);
   HTkPhotonIso.Write(TkPhotonIsoDirectory);
   HTkIsoEGIso.Write(TkIsoEGIsoDirectory);
   HTkIsoEGLooseIso.Write(TkIsoEGLooseIsoDirectory);
   HTkIsoEMIso.Write(TkIsoEMIsoDirectory);
   HEGElectronLDR.Write(EGElectronLDRDirectory);
   HEGPhotonLDR.Write(EGPhotonLDRDirectory);
   HTkElectronLDR.Write(TkElectronLDRDirectory);
   HTkElectronLooseLDR.Write(TkElectronLooseLDRDirectory);
   HTkPhotonLDR.Write(TkPhotonLDRDirectory);
   HTkHT1.Write(TkHT1Directory);
   HTkMHT1.Write(TkMHT1Directory);
   HTkHT2.Write(TkHT2Directory);
   HTkMHT2.Write(TkMHT2Directory);
   HTkHT3.Write(TkHT3Directory);
   HTkMHT3.Write(TkMHT3Directory);
   HTkHT4.Write(TkHT4Directory);
   HTkMHT4.Write(TkMHT4Directory);
   HTkHT5.Write(TkHT5Directory);
   HTkMHT5.Write(TkMHT5Directory);
   HTkMET.Write(TkMETDirectory);
   HPuppiHT1.Write(PuppiHT1Directory);
   HPuppiMHT1.Write(PuppiMHT1Directory);
   HPuppiHT2.Write(PuppiHT2Directory);
   HPuppiMHT2.Write(PuppiMHT2Directory);
   HPuppiHT3.Write(PuppiHT3Directory);
   HPuppiMHT3.Write(PuppiMHT3Directory);
   HPuppiMET.Write(PuppiMETDirectory);

   // Clean up
   OutputFile.Close();

   // Yay
   return 0;
}

FourVector BestInRange(vector<FourVector> &List, double AbsEta)
{
   FourVector Best = FourVector(-1, 0, 0, 0);
   for(int i = 0; i < (int)List.size(); i++)
      if(List[i].GetAbsEta() < AbsEta)
         if(Best.GetPT() < List[i].GetPT())
            Best = List[i];
   return Best;
}

GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MaxEta, double DRMax, int Qual, int Type)
{
   GenericObject Best;
   Best.P = FourVector(-1, 0, 0, 0);
   Best.Iso = -1;
   for(int i = 0; i < (int)List.size(); i++)
   {
      if(List[i].P.GetAbsEta() > MaxEta)
         continue;
      if(Qual >= 0 && List[i].Qual != Qual)
         continue;
      if(Qual == QUAL_ODD && List[i].Qual % 2 == 0)
         continue;
      if(Qual == QUAL_12 && List[i].Qual < 12)
         continue;
      if(Qual == QUAL_BARRELODDENDCAP2 && List[i].Type == 0 && List[i].Qual % 2 == 0)
         continue;
      if(Qual == QUAL_BARRELODDENDCAP2 && List[i].Type == 1 && List[i].Qual != 2)
         continue;
      if(Qual == QUAL_USEFLAG && List[i].Flag == false)
         continue;
      if(Type >= 0 && List[i].Type != Type)
         continue;
      if(GetDR(List[i].P, Reference) <= DRMax)
         if(Best.P.GetPT() < List[i].P.GetPT())
            Best = List[i];
   }
   return Best;
}

FourVector CalculateHT(vector<FourVector> &GenJets, double Eta, double PT)
{
   double HT = 0;

   for(auto Jet : GenJets)
   {
      if(Jet.GetAbsEta() > Eta)
         continue;
      if(Jet.GetPT() < PT)
         continue;

      HT = HT + Jet.GetPT();
   }

   FourVector Result;
   Result.SetPtEtaPhi(HT, 0, 0);
   return Result;
}

FourVector CalculateMHT(vector<FourVector> &GenJets, double Eta, double PT)
{
   FourVector Result;

   for(auto Jet : GenJets)
   {
      if(Jet.GetAbsEta() > Eta)
         continue;
      if(Jet.GetPT() < PT)
         continue;

      Result = Result + Jet;
   }

   return Result;
}

void FillHistograms(Histograms &Histogram, FourVector &Object, FourVector &Reference, double Isolation, int Type)
{
   Histogram.Fill(Object, Reference, Isolation, Type);
}

void FillHistograms(Histograms &Histogram, FourVector &Object, double Isolation, int Type)
{
   Histogram.Fill(Object, Object, Isolation, Type);
}

vector<FourVector> ClusterJets(vector<FourVector> &Particles)
{
   vector<fastjet::PseudoJet> Candidates;
   for(auto P : Particles)
      Candidates.push_back(fastjet::PseudoJet(P[1], P[2], P[3], P[0]));

   fastjet::JetDefinition Definition(fastjet::antikt_algorithm, 0.4);
   fastjet::ClusterSequence Sequence(Candidates, Definition);
   vector<fastjet::PseudoJet> Jets = Sequence.inclusive_jets();

   vector<FourVector> GenJets;
   for(auto J : Jets)
      GenJets.push_back(FourVector(J.e(), J.px(), J.py(), J.pz()));
   return GenJets;
}

double CalculateGenIsolation(FourVector &P, vector<FourVector> &Particles, double DR)
{
   double Isolation = 0;

   for(auto G : Particles)
   {
      if(GetDR(G, P) < DR)
         Isolation = Isolation + G.GetPT();
   }

   return Isolation / P.GetPT() - 1;
}

vector<FourVector> CleanUpTaus(vector<FourVector> &Taus, vector<FourVector> &Avoid, double DR)
{
   for(int i = 0; i < (int)Taus.size(); i++)
   {
      bool HasSomethingClose = false;
      FourVector P = Taus[i];

      for(FourVector Q : Avoid)
         if(GetDR(P, Q) < DR)
            HasSomethingClose = true;

      if(HasSomethingClose == true)
      {
         Taus.erase(Taus.begin() + i);
         i = i - 1;
      }
   }

   return Taus;
}

FourVector GetVisTau(L1GenMessenger &MGen, int Index)
{
   vector<int> Indices;
   Indices.push_back(Index);

   int N = MGen.GenP.size();

   FourVector P;

   bool LeptonicDecay = false;

   while(Indices.size() > 0)
   {
      int Current = Indices[0];
      Indices.erase(Indices.begin());

      // cout << Current << endl;

      int DaughterCount = MGen.GenDaughter[Current].size();

      for(int i = 0; i < DaughterCount; i++)
      {
         int j = MGen.GenDaughter[Current][i];

         if(MGen.GenID[j] == 12 || MGen.GenID[j] == -12)
            continue;
         if(MGen.GenID[j] == 14 || MGen.GenID[j] == -14)
            continue;
         if(MGen.GenID[j] == 16 || MGen.GenID[j] == -16)
            continue;
         
         Indices.push_back(j);
      }

      if(DaughterCount == 0)   // we found a leaf!
      {
         P = P + MGen.GenP[Current];
         if(MGen.GenID[Current] == 11 || MGen.GenID[Current] == -11)
            LeptonicDecay = true;
         if(MGen.GenID[Current] == 13 || MGen.GenID[Current] == -13)
            LeptonicDecay = true;
      }
   }

   if(LeptonicDecay == false)
      return P;
   return FourVector(-1, 0, 0, 0);
}

FourVector GetVisTauAdhoc(L1GenMessenger &MGen, int Index)
{
   int ID = MGen.GenID[Index];

   FourVector P;
   bool LeptonicDecay = false;

   for(int i = 0; i < (int)MGen.GenID.size(); i++)
   {
      if(MGen.GenParent[i] != ID)
         continue;

      if(MGen.GenID[i] == 11 || MGen.GenID[i] == -11)
         LeptonicDecay = true;
      if(MGen.GenID[i] == 13 || MGen.GenID[i] == -13)
         LeptonicDecay = true;

      if(MGen.GenID[i] == 12 || MGen.GenID[i] == -12)
         continue;
      if(MGen.GenID[i] == 14 || MGen.GenID[i] == -14)
         continue;
      if(MGen.GenID[i] == 16 || MGen.GenID[i] == -16)
         continue;

      P = P + MGen.GenP[i];
   }

   if(LeptonicDecay == true)
      return FourVector(-1, 0, 0, 0);
   return P;
}






