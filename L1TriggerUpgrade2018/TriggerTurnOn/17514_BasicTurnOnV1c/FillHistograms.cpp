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

#include "Messenger.h"

#include "Histograms.h"

#define QUAL_NONE -1
#define QUAL_ODD -2

int main(int argc, char *argv[]);
FourVector BestInRange(vector<FourVector> &List, double AbsEta);
GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MaxEta = 999, double DRMax = 0.5, int Qual = QUAL_NONE);
FourVector CalculateHT(vector<FourVector> &GenJets, double Eta, double PT);
FourVector CalculateMHT(vector<FourVector> &GenJets, double Eta, double PT);
void FillHistograms(Histograms &HistogramMatch, Histograms &HistogramNoMatch,
   FourVector &Object, FourVector &Reference, double Isolation = -1);
void FillHistograms(Histograms &Histogram, FourVector &Object, double Isolation = -1);
vector<FourVector> ClusterJets(vector<FourVector> &Particles);
double CalculateGenIsolation(FourVector &P, vector<FourVector> &Particles, double DR = 0.3);

int main(int argc, char *argv[])
{
   fastjet::ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   // Some root styling
   SetThesisStyle();

   // Get arguments
   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");

   // Input File
   TFile File(InputFileName.c_str());

   // Messengers
   L1GenMessenger MGen(File, "l1GeneratorTree/L1GenTree");
   L1PhaseIITreeV1cMessenger MPhaseII(File, "l1PhaseIITree/L1PhaseIITree");

   if(MGen.Tree == NULL)
      return -1;

   // Output File and directories for better organization
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TDirectory *GenElectronDirectory     = OutputFile.mkdir("GenElectron",     "Gen electron");
   TDirectory *GenPhotonDirectory       = OutputFile.mkdir("GenPhoton",       "Gen photon");
   TDirectory *IsoGenElectronDirectory  = OutputFile.mkdir("IsoGenElectron",  "Isolated gen electron");
   TDirectory *IsoGenPhotonDirectory    = OutputFile.mkdir("IsoGenPhoton",    "Isolated gen photon");

   TDirectory *JetDirectory             = OutputFile.mkdir("Jet",             "Jet (Gen jet)");
   TDirectory *TkJetDirectory           = OutputFile.mkdir("TkJet",           "TkJet (Gen jet)");
   TDirectory *TkJetChargedDirectory    = OutputFile.mkdir("TkJetCharged",    "TkJet (Charged jet)");
   TDirectory *TkCaloJetDirectory       = OutputFile.mkdir("TkCaloJet",       "TkCaloJet (Gen jet)");
   TDirectory *PuppiJetWideDirectory    = OutputFile.mkdir("PuppiJetWide",    "PuppiJet (eta 4.7)");
   TDirectory *PuppiJetDirectory        = OutputFile.mkdir("PuppiJet",        "PuppiJet (eta 2.4)");

   TDirectory *MuonDirectory            = OutputFile.mkdir("Muon",            "Muon (Muon)");
   TDirectory *MuonKFDirectory          = OutputFile.mkdir("MuonKF",          "MuonKF (Muon)");
   TDirectory *TkGlbMuonDirectory          = OutputFile.mkdir("TkGlbMuon",          "TkGlbMuon (Muon)");

   TDirectory *EGDirectory              = OutputFile.mkdir("EG",              "EG (Electron)");
   TDirectory *TkEGDirectory            = OutputFile.mkdir("TkEG",            "TkEG (Electron)");
   TDirectory *TkEMDirectory            = OutputFile.mkdir("TkEM",            "TkEM (Photon)");
   TDirectory *TkEGIsoDirectory         = OutputFile.mkdir("TkEGIso",         "TkEG (Isolated electron)");
   TDirectory *TkEMIsoDirectory         = OutputFile.mkdir("TkEMIso",         "TkEM (Isolated photon)");
   TDirectory *TkIsoEGIsoDirectory      = OutputFile.mkdir("TkIsoEGIso",      "TkIsoEG (Isolated electron)");
   TDirectory *TkIsoEMIsoDirectory      = OutputFile.mkdir("TkIsoEMIso",      "TkIsoEM (Isolated photon)");

   TDirectory *TkHT1Directory           = OutputFile.mkdir("TkHT1",           "HT from TkJet (1)");
   TDirectory *TkMHT1Directory          = OutputFile.mkdir("TkMHT1",          "MHT from TkJet (1)");
   TDirectory *TkHT2Directory           = OutputFile.mkdir("TkHT2",           "HT from TkJet (2)");
   TDirectory *TkMHT2Directory          = OutputFile.mkdir("TkMHT2",          "MHT from TkJet (2)");
   TDirectory *TkHT3Directory           = OutputFile.mkdir("TkHT3",           "HT from TkJet (3)");
   TDirectory *TkMHT3Directory          = OutputFile.mkdir("TkMHT3",          "MHT from TkJet (3)");
   TDirectory *TkHT4Directory           = OutputFile.mkdir("TkHT4",           "HT from TkJet (4)");
   TDirectory *TkMHT4Directory          = OutputFile.mkdir("TkMHT4",          "MHT from TkJet (4)");
   TDirectory *TkHT5Directory           = OutputFile.mkdir("TkHT5",           "HT from TkJet (5)");
   TDirectory *TkMHT5Directory          = OutputFile.mkdir("TkMHT5",          "MHT from TkJet (5)");
   TDirectory *TkMETDirectory           = OutputFile.mkdir("TkMET",           "MET from Tk");
   TDirectory *PuppiHT1Directory        = OutputFile.mkdir("PuppiHT1",        "HT from PuppiJet (1)");
   TDirectory *PuppiMHT1Directory       = OutputFile.mkdir("PuppiMHT1",       "MHT from PuppiJet (1)");
   TDirectory *PuppiHT2Directory        = OutputFile.mkdir("PuppiHT2",        "HT from PuppiJet (2)");
   TDirectory *PuppiMHT2Directory       = OutputFile.mkdir("PuppiMHT2",       "MHT from PuppiJet (2)");
   TDirectory *PuppiHT3Directory        = OutputFile.mkdir("PuppiHT3",        "HT from PuppiJet (3)");
   TDirectory *PuppiMHT3Directory       = OutputFile.mkdir("PuppiMHT3",       "MHT from PuppiJet (3)");
   TDirectory *PuppiMETDirectory        = OutputFile.mkdir("PuppiMET",        "MET from Puppi");

   // Create histograms
   vector<double> GenEGThresholds = {0};
   vector<double> JetThresholds = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60,
      75, 80, 85, 90, 100, 125, 150, 175, 200, 225, 250, 275, 300};
   vector<double> MuonThresholds = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30};
   vector<double> EGThresholds = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30};
   vector<double> HTThresholds = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 125, 150,
      175, 200, 225, 250, 300, 325, 350, 375, 400, 425, 450, 475, 500};
   
   Histograms HGenElectron        (200, 0, 150,  50, -3.5, 3.5, 200, 0, 5.0, GenEGThresholds, "GenElectron");
   Histograms HGenPhoton          (200, 0, 150,  50, -3.5, 3.5, 200, 0, 5.0, GenEGThresholds, "GenPhoton");
   Histograms HIsoGenElectron     (200, 0, 150,  50, -3.5, 3.5, 200, 0, 0.2, GenEGThresholds, "IsoGenElectron");
   Histograms HIsoGenPhoton       (200, 0, 150,  50, -3.5, 3.5, 200, 0, 0.2, GenEGThresholds, "IsoGenPhoton");
   
   Histograms HJet                (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,   "Jet");
   Histograms HJetNoMatch         (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,   "JetNoMatch");

   Histograms HTkJet              (200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,   "TkJet");
   Histograms HTkJetNoMatch       (200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,   "TkJetNoMatch");

   Histograms HTkJetCharged       (200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,   "TkJetCharged");
   Histograms HTkJetChargedNoMatch(200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,   "TkJetChargedNoMatch");

   Histograms HTkCaloJet          (500, 0, 500,  50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,   "TkCaloJet");
   Histograms HTkCaloJetNoMatch   (500, 0, 500,  50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,   "TkCaloJetNoMatch");

   Histograms HPuppiJetWide       (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,   "PuppiJetWide");
   Histograms HPuppiJetWideNoMatch(200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,   "PuppiJetWideNoMatch");

   Histograms HPuppiJet           (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,   "PuppiJet");
   Histograms HPuppiJetNoMatch    (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,   "PuppiJetNoMatch");

   Histograms HMuon               (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, MuonThresholds,  "Muon");
   Histograms HMuonNoMatch        (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, MuonThresholds,  "MuonNoMatch");

   Histograms HMuonKF             (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, MuonThresholds,  "MuonKF");
   Histograms HMuonKFNoMatch      (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, MuonThresholds,  "MuonKFNoMatch");

   Histograms HTkGlbMuon          (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, MuonThresholds,  "TkGlbMuon");
   Histograms HTkGlbMuonNoMatch   (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, MuonThresholds,  "TkGlbMuonNoMatch");

   Histograms HEG                 (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, EGThresholds,    "EG");
   Histograms HEGNoMatch          (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, EGThresholds,    "EGNoMatch");

   Histograms HTkEG               (75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,    "TkEG");
   Histograms HTkEGNoMatch        (75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,    "TkEGNoMatch");

   Histograms HTkEM               (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.3, EGThresholds,    "TkEM");
   Histograms HTkEMNoMatch        (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.3, EGThresholds,    "TkEMNoMatch");

   Histograms HTkEGIso            (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,    "TkEGIso");
   Histograms HTkEGIsoNoMatch     (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,    "TkEGIsoNoMatch");

   Histograms HTkEMIso            (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.3, EGThresholds,    "TkEMIso");
   Histograms HTkEMIsoNoMatch     (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.3, EGThresholds,    "TkEMIsoNoMatch");

   Histograms HTkIsoEGIso         (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,    "TkIsoEGIso");
   Histograms HTkIsoEGIsoNoMatch  (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,    "TkIsoEGIsoNoMatch");

   Histograms HTkIsoEMIso         (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.3, EGThresholds,    "TkIsoEMIso");
   Histograms HTkIsoEMIsoNoMatch  (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.3, EGThresholds,    "TkIsoEMIsoNoMatch");

   Histograms HTkHT1              (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT1");
   Histograms HTkHT1NoMatch       (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT1NoMatch");

   Histograms HTkMHT1             (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT1");
   Histograms HTkMHT1NoMatch      (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT1NoMatch");

   Histograms HTkHT2              (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT2");
   Histograms HTkHT2NoMatch       (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT2NoMatch");

   Histograms HTkMHT2             (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT2");
   Histograms HTkMHT2NoMatch      (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT2NoMatch");

   Histograms HTkHT3              (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT3");
   Histograms HTkHT3NoMatch       (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT3NoMatch");

   Histograms HTkMHT3             (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT3");
   Histograms HTkMHT3NoMatch      (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT3NoMatch");

   Histograms HTkHT4              (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT4");
   Histograms HTkHT4NoMatch       (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT4NoMatch");

   Histograms HTkMHT4             (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT4");
   Histograms HTkMHT4NoMatch      (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT4NoMatch");

   Histograms HTkHT5              (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT5");
   Histograms HTkHT5NoMatch       (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT5NoMatch");

   Histograms HTkMHT5             (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT5");
   Histograms HTkMHT5NoMatch      (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT5NoMatch");

   Histograms HTkMET              (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMET");
   Histograms HTkMETNoMatch       (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMETNoMatch");

   Histograms HPuppiHT1           (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiHT1");
   Histograms HPuppiHT1NoMatch    (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiHT1NoMatch");

   Histograms HPuppiMHT1          (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMHT1");
   Histograms HPuppiMHT1NoMatch   (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMHT1NoMatch");

   Histograms HPuppiHT2           (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiHT2");
   Histograms HPuppiHT2NoMatch    (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiHT2NoMatch");

   Histograms HPuppiMHT2          (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMHT2");
   Histograms HPuppiMHT2NoMatch   (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMHT2NoMatch");

   Histograms HPuppiHT3           (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiHT3");
   Histograms HPuppiHT3NoMatch    (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiHT3NoMatch");

   Histograms HPuppiMHT3          (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMHT3");
   Histograms HPuppiMHT3NoMatch   (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMHT3NoMatch");

   Histograms HPuppiMET           (200, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMET");
   Histograms HPuppiMETNoMatch    (200, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMETNoMatch");

   // Loop over events
   int EntryCount = MGen.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MGen.GetEntry(iE);
      MPhaseII.GetEntry(iE);

      vector<FourVector> Electrons;
      vector<FourVector> Photons;
      vector<FourVector> Muons;
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

         if(MGen.GenStatus[i] == 1)   // we only want final state particles here
            Particles.push_back(MGen.GenP[i]);
         if(MGen.GenStatus[i] == 1 && MGen.GenCharge[i] != 0)
            ChargedParticles.push_back(MGen.GenP[i]);
      }

      // Cluster jets
      vector<FourVector> GenJets        = ClusterJets(Particles);
      vector<FourVector> ChargedGenJets = ClusterJets(ChargedParticles);

      // Reference objects
      FourVector BestGenJet        = BestInRange(GenJets,           4.7);
      FourVector BestCentralGenJet = BestInRange(GenJets,           2.4);
      FourVector BestBarrelGenJet  = BestInRange(GenJets,           1.5);
      FourVector BestChargedGenJet = BestInRange(ChargedGenJets,    2.4);

      FourVector BestMuonWide      = BestInRange(Muons,             2.4);
      FourVector BestMuonBarrel    = BestInRange(Muons,             1.5);

      FourVector BestElectron      = BestInRange(Electrons,         3.0);
      FourVector BestPhoton        = BestInRange(Photons,           3.0);

      FourVector GenHTForTk1       = CalculateHT(ChargedGenJets,    2.4, 5);
      FourVector GenMHTForTk1      = CalculateMHT(ChargedGenJets,   2.4, 5);
      FourVector GenHTForTk2       = CalculateHT(ChargedGenJets,    2.4, 10);
      FourVector GenMHTForTk2      = CalculateMHT(ChargedGenJets,   2.4, 10);
      FourVector GenHTForTk3       = CalculateHT(ChargedGenJets,    2.4, 15);
      FourVector GenMHTForTk3      = CalculateMHT(ChargedGenJets,   2.4, 15);
      FourVector GenHTForTk4       = CalculateHT(ChargedGenJets,    2.4, 20);
      FourVector GenMHTForTk4      = CalculateMHT(ChargedGenJets,   2.4, 20);
      FourVector GenHTForTk5       = CalculateHT(ChargedGenJets,    2.4, 30);
      FourVector GenMHTForTk5      = CalculateMHT(ChargedGenJets,   2.4, 30);
      FourVector GenMETForTk       = CalculateMHT(ChargedParticles, 2.4, 0);
      FourVector GenHTForPuppi1    = CalculateHT(GenJets,           2.4, 15);
      FourVector GenMHTForPuppi1   = CalculateMHT(GenJets,          2.4, 15);
      FourVector GenHTForPuppi2    = CalculateHT(GenJets,           2.4, 20);
      FourVector GenMHTForPuppi2   = CalculateMHT(GenJets,          2.4, 20);
      FourVector GenHTForPuppi3    = CalculateHT(GenJets,           2.4, 30);
      FourVector GenMHTForPuppi3   = CalculateMHT(GenJets,          2.4, 30);
      FourVector GenMETForPuppi    = CalculateMHT(Particles,        2.4, 0);

      // Gen isolations
      double GenElectronIsolation  = CalculateGenIsolation(BestElectron, Particles, 0.3);
      double GenPhotonIsolation    = CalculateGenIsolation(BestPhoton,   Particles, 0.3);

      FourVector BestIsoElectron(-1, 0, 0, 0);
      FourVector BestIsoPhoton(-1, 0, 0, 0);

      if(GenElectronIsolation < 0.15)
         BestIsoElectron = BestElectron;
      if(GenPhotonIsolation < 0.15)
         BestIsoPhoton = BestPhoton;

      // Best L1 objects
      GenericObject BestL1Jet             = BestInRange(MPhaseII.Jet,         BestGenJet,        4.7, 0.5, -1);
      GenericObject BestL1TkJet           = BestInRange(MPhaseII.TrackerJet,  BestCentralGenJet, 2.4, 0.5, -1);
      GenericObject BestL1TkJetCharged    = BestInRange(MPhaseII.TrackerJet,  BestChargedGenJet, 2.4, 0.5, -1);
      GenericObject BestL1TkCaloJet       = BestInRange(MPhaseII.TkCaloJet,   BestBarrelGenJet,  1.5, 0.5, -1);
      GenericObject BestL1PuppiJet        = BestInRange(MPhaseII.PuppiJet,    BestGenJet,        4.7, 0.5, -1);
      GenericObject BestL1CenPuppiJet     = BestInRange(MPhaseII.PuppiJet,    BestCentralGenJet, 2.4, 0.5, -1);

      GenericObject BestL1Muon            = BestInRange(MPhaseII.Muon,        BestMuonWide,      2.4, 0.3, -1);
      GenericObject BestL1MuonKF          = BestInRange(MPhaseII.MuonKF,      BestMuonBarrel,    1.5, 0.3, -1);
      GenericObject BestL1TkGlbMuon       = BestInRange(MPhaseII.TkGlbMuon,   BestMuonWide,      2.4, 0.3, -1);

      GenericObject BestL1EG              = BestInRange(MPhaseII.EG,          BestElectron,      3.0, 0.2, QUAL_ODD);
      GenericObject BestL1TkEG            = BestInRange(MPhaseII.TkEG,        BestElectron,      3.0, 0.2, QUAL_ODD);
      GenericObject BestL1TkEM            = BestInRange(MPhaseII.TkEM,        BestPhoton,        3.0, 0.2, QUAL_ODD);
      GenericObject BestL1TkEGIso         = BestInRange(MPhaseII.TkEG,        BestElectron,      3.0, 0.2, QUAL_ODD);
      GenericObject BestL1TkEMIso         = BestInRange(MPhaseII.TkEM,        BestPhoton,        3.0, 0.2, QUAL_ODD);

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
      FourVector PuppiHT1 =  MPhaseII.TrackerHT[0].P;
      FourVector PuppiMHT1 = MPhaseII.TrackerMHT[0].P;
      FourVector PuppiHT2 =  MPhaseII.TrackerHT[1].P;
      FourVector PuppiMHT2 = MPhaseII.TrackerMHT[1].P;
      FourVector PuppiHT3 =  MPhaseII.TrackerHT[2].P;
      FourVector PuppiMHT3 = MPhaseII.TrackerMHT[2].P;
      FourVector PuppiMET =  MPhaseII.PuppiMET[0].P;

      // Fill Histograms
      FillHistograms(HGenElectron,    BestElectron,         GenElectronIsolation);
      FillHistograms(HGenPhoton,      BestPhoton,           GenPhotonIsolation);
      FillHistograms(HIsoGenElectron, BestIsoElectron,      GenElectronIsolation);
      FillHistograms(HIsoGenPhoton,   BestIsoPhoton,        GenPhotonIsolation);
      
      FillHistograms(HJet,            HJetNoMatch,          BestL1Jet.P,         BestGenJet);
      FillHistograms(HTkJet,          HTkJetNoMatch,        BestL1TkJet.P,       BestCentralGenJet);
      FillHistograms(HTkJetCharged,   HTkJetChargedNoMatch, BestL1TkJet.P,       BestChargedGenJet);
      FillHistograms(HTkCaloJet,      HTkCaloJetNoMatch,    BestL1TkCaloJet.P,   BestGenJet);
      FillHistograms(HPuppiJetWide,   HPuppiJetWideNoMatch, BestL1PuppiJet.P,    BestGenJet);
      FillHistograms(HPuppiJet,       HPuppiJetNoMatch,     BestL1CenPuppiJet.P, BestCentralGenJet);

      FillHistograms(HMuon,           HMuonNoMatch,         BestL1Muon.P,        BestMuonWide);
      FillHistograms(HMuonKF,         HMuonKFNoMatch,       BestL1MuonKF.P,      BestMuonBarrel);
      FillHistograms(HTkGlbMuon,      HTkGlbMuonNoMatch,    BestL1TkGlbMuon.P,   BestMuonWide);

      FillHistograms(HEG,             HEGNoMatch,           BestL1EG.P,          BestElectron,    BestL1EG.Iso);
      FillHistograms(HTkEG,           HTkEGNoMatch,         BestL1TkEG.P,        BestElectron,    BestL1TkEG.Iso);
      FillHistograms(HTkEM,           HTkEMNoMatch,         BestL1TkEM.P,        BestPhoton,      BestL1TkEM.Iso);
      FillHistograms(HTkEGIso,        HTkEGIsoNoMatch,      BestL1TkEG.P,        BestIsoElectron, BestL1TkEG.Iso);
      FillHistograms(HTkEMIso,        HTkEMIsoNoMatch,      BestL1TkEM.P,        BestIsoPhoton,   BestL1TkEM.Iso);
      if(BestL1TkEG.Iso < 0.01)
      FillHistograms(HTkIsoEGIso,     HTkIsoEGIsoNoMatch,   BestL1TkEG.P,        BestIsoElectron, BestL1TkEG.Iso);
      if(BestL1TkEM.Iso < 0.01)
      FillHistograms(HTkIsoEMIso,     HTkIsoEMIsoNoMatch,   BestL1TkEM.P,        BestIsoPhoton,   BestL1TkEM.Iso);

      FillHistograms(HTkHT1,          HTkHT1NoMatch,        TkHT1,               GenHTForTk1);
      FillHistograms(HTkMHT1,         HTkMHT1NoMatch,       TkMHT1,              GenMHTForTk1);
      FillHistograms(HTkHT2,          HTkHT2NoMatch,        TkHT2,               GenHTForTk2);
      FillHistograms(HTkMHT2,         HTkMHT2NoMatch,       TkMHT2,              GenMHTForTk2);
      FillHistograms(HTkHT3,          HTkHT3NoMatch,        TkHT3,               GenHTForTk3);
      FillHistograms(HTkMHT3,         HTkMHT3NoMatch,       TkMHT3,              GenMHTForTk3);
      FillHistograms(HTkHT4,          HTkHT4NoMatch,        TkHT4,               GenHTForTk4);
      FillHistograms(HTkMHT4,         HTkMHT4NoMatch,       TkMHT4,              GenMHTForTk4);
      FillHistograms(HTkHT5,          HTkHT5NoMatch,        TkHT5,               GenHTForTk5);
      FillHistograms(HTkMHT5,         HTkMHT5NoMatch,       TkMHT5,              GenMHTForTk5);
      FillHistograms(HTkMET,          HTkMETNoMatch,        TkMET,               GenMETForTk);
      
      FillHistograms(HPuppiHT1,       HPuppiHT1NoMatch,     PuppiHT1,            GenHTForPuppi1);
      FillHistograms(HPuppiMHT1,      HPuppiMHT1NoMatch,    PuppiMHT1,           GenMHTForPuppi1);
      FillHistograms(HPuppiHT2,       HPuppiHT2NoMatch,     PuppiHT2,            GenHTForPuppi2);
      FillHistograms(HPuppiMHT2,      HPuppiMHT2NoMatch,    PuppiMHT2,           GenMHTForPuppi2);
      FillHistograms(HPuppiHT3,       HPuppiHT3NoMatch,     PuppiHT3,            GenHTForPuppi3);
      FillHistograms(HPuppiMHT3,      HPuppiMHT3NoMatch,    PuppiMHT3,           GenMHTForPuppi3);
      FillHistograms(HPuppiMET,       HPuppiMETNoMatch,     PuppiMET,            GenMETForPuppi);
   }

   // Write result to file
   HGenElectron.Write(GenElectronDirectory);
   HGenPhoton.Write(GenPhotonDirectory);
   HIsoGenElectron.Write(IsoGenElectronDirectory);
   HIsoGenPhoton.Write(IsoGenPhotonDirectory);
   HJet.Write(JetDirectory);
   HJetNoMatch.Write(JetDirectory);
   HTkJet.Write(TkJetDirectory);
   HTkJetNoMatch.Write(TkJetDirectory);
   HTkJetCharged.Write(TkJetChargedDirectory);
   HTkJetChargedNoMatch.Write(TkJetChargedDirectory);
   HTkCaloJet.Write(TkCaloJetDirectory);
   HTkCaloJetNoMatch.Write(TkCaloJetDirectory);
   HPuppiJetWide.Write(PuppiJetWideDirectory);
   HPuppiJetWideNoMatch.Write(PuppiJetWideDirectory);
   HPuppiJet.Write(PuppiJetDirectory);
   HPuppiJetNoMatch.Write(PuppiJetDirectory);
   HMuon.Write(MuonDirectory);
   HMuonNoMatch.Write(MuonDirectory);
   HMuonKF.Write(MuonKFDirectory);
   HMuonKFNoMatch.Write(MuonKFDirectory);
   HEG.Write(EGDirectory);
   HEGNoMatch.Write(EGDirectory);
   HTkEG.Write(TkEGDirectory);
   HTkEGNoMatch.Write(TkEGDirectory);
   HTkEM.Write(TkEMDirectory);
   HTkEMNoMatch.Write(TkEMDirectory);
   HTkEGIso.Write(TkEGIsoDirectory);
   HTkEGIsoNoMatch.Write(TkEGIsoDirectory);
   HTkEMIso.Write(TkEMIsoDirectory);
   HTkEMIsoNoMatch.Write(TkEMIsoDirectory);
   HTkIsoEGIso.Write(TkIsoEGIsoDirectory);
   HTkIsoEGIsoNoMatch.Write(TkIsoEGIsoDirectory);
   HTkIsoEMIso.Write(TkIsoEMIsoDirectory);
   HTkIsoEMIsoNoMatch.Write(TkIsoEMIsoDirectory);
   HTkGlbMuon.Write(TkGlbMuonDirectory);
   HTkGlbMuonNoMatch.Write(TkGlbMuonDirectory);
   HTkHT1.Write(TkHT1Directory);
   HTkHT1NoMatch.Write(TkHT1Directory);
   HTkMHT1.Write(TkMHT1Directory);
   HTkMHT1NoMatch.Write(TkMHT1Directory);
   HTkHT2.Write(TkHT2Directory);
   HTkHT2NoMatch.Write(TkHT2Directory);
   HTkMHT2.Write(TkMHT2Directory);
   HTkMHT2NoMatch.Write(TkMHT2Directory);
   HTkHT3.Write(TkHT3Directory);
   HTkHT3NoMatch.Write(TkHT3Directory);
   HTkMHT3.Write(TkMHT3Directory);
   HTkMHT3NoMatch.Write(TkMHT3Directory);
   HTkHT4.Write(TkHT4Directory);
   HTkHT4NoMatch.Write(TkHT4Directory);
   HTkMHT4.Write(TkMHT4Directory);
   HTkMHT4NoMatch.Write(TkMHT4Directory);
   HTkHT5.Write(TkHT5Directory);
   HTkHT5NoMatch.Write(TkHT5Directory);
   HTkMHT5.Write(TkMHT5Directory);
   HTkMHT5NoMatch.Write(TkMHT5Directory);
   HTkMET.Write(TkMETDirectory);
   HTkMETNoMatch.Write(TkMETDirectory);
   HPuppiHT1.Write(PuppiHT1Directory);
   HPuppiHT1NoMatch.Write(PuppiHT1Directory);
   HPuppiMHT1.Write(PuppiMHT1Directory);
   HPuppiMHT1NoMatch.Write(PuppiMHT1Directory);
   HPuppiHT2.Write(PuppiHT2Directory);
   HPuppiHT2NoMatch.Write(PuppiHT2Directory);
   HPuppiMHT2.Write(PuppiMHT2Directory);
   HPuppiMHT2NoMatch.Write(PuppiMHT2Directory);
   HPuppiHT3.Write(PuppiHT3Directory);
   HPuppiHT3NoMatch.Write(PuppiHT3Directory);
   HPuppiMHT3.Write(PuppiMHT3Directory);
   HPuppiMHT3NoMatch.Write(PuppiMHT3Directory);
   HPuppiMET.Write(PuppiMETDirectory);
   HPuppiMETNoMatch.Write(PuppiMETDirectory);

   // Clean up
   OutputFile.Close();

   File.Close();

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

GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MaxEta, double DRMax, int Qual)
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

void FillHistograms(Histograms &HistogramMatch, Histograms &HistogramNoMatch,
   FourVector &Object, FourVector &Reference, double Isolation)
{
   if(Reference[0] > 0 && Object[0] > 0)
      HistogramMatch.Fill(Object, Reference, Isolation);
   if(Reference[0] > 0)
      HistogramNoMatch.Fill(Object, Reference, Isolation);
}

void FillHistograms(Histograms &Histogram, FourVector &Object, double Isolation)
{
   if(Object[0] > 0)
      Histogram.Fill(Object, Object, Isolation);
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










