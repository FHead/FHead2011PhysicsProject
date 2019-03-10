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

int main(int argc, char *argv[]);
FourVector BestInRange(vector<FourVector> &List, double AbsEta);
GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MaxEta = 999, double DRMax = 0.5);
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
   L1PhaseIITreeV1bMessenger MPhaseII(File, "l1PhaseIITree/L1PhaseIITree");

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
   TDirectory *TkMuonDirectory          = OutputFile.mkdir("TkMuon",          "TkMuon (Muon)");

   TDirectory *EGDirectory              = OutputFile.mkdir("EG",              "EG (Electron)");
   TDirectory *TkEGDirectory            = OutputFile.mkdir("TkEG",            "TkEG (Electron)");
   TDirectory *TkEMDirectory            = OutputFile.mkdir("TkEM",            "TkEM (Photon)");
   TDirectory *TkEGIsoDirectory         = OutputFile.mkdir("TkEGIso",         "TkEG (Isolated electron)");
   TDirectory *TkEMIsoDirectory         = OutputFile.mkdir("TkEMIso",         "TkEM (Isolated photon)");
   TDirectory *TkIsoEGIsoDirectory      = OutputFile.mkdir("TkIsoEGIso",      "TkIsoEG (Isolated electron)");
   TDirectory *TkIsoEMIsoDirectory      = OutputFile.mkdir("TkIsoEMIso",      "TkIsoEM (Isolated photon)");

   TDirectory *TkHTDirectory            = OutputFile.mkdir("TkHT",            "HT from TkJet");
   TDirectory *TkMHTDirectory           = OutputFile.mkdir("TkMHT",           "MHT from TkJet");
   TDirectory *TkMETDirectory           = OutputFile.mkdir("TkMET",           "MET from Tk");
   TDirectory *PuppiHTDirectory         = OutputFile.mkdir("PuppiHT",         "HT from PuppiJet");
   TDirectory *PuppiMHTDirectory        = OutputFile.mkdir("PuppiMHT",        "MHT from PuppiJet");
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

   Histograms HTkMuon             (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, MuonThresholds,  "TkMuon");
   Histograms HTkMuonNoMatch      (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, MuonThresholds,  "TkMuonNoMatch");

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

   Histograms HTkHT               (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHT");
   Histograms HTkHTNoMatch        (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkHTNoMatch");

   Histograms HTkMHT              (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHT");
   Histograms HTkMHTNoMatch       (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMHTNoMatch");

   Histograms HTkMET              (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMET");
   Histograms HTkMETNoMatch       (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "TkMETNoMatch");

   Histograms HPuppiHT            (200, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiHT");
   Histograms HPuppiHTNoMatch     (200, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiHTNoMatch");

   Histograms HPuppiMHT           (200, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMHT");
   Histograms HPuppiMHTNoMatch    (200, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,    "PuppiMHTNoMatch");

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

      FourVector GenHTForTk        = CalculateHT(ChargedGenJets,    2.2, 15);
      FourVector GenMHTForTk       = CalculateMHT(ChargedGenJets,   2.2, 15);
      FourVector GenMETForTk       = CalculateMHT(ChargedParticles, 2.2, 0);
      FourVector GenHTForPuppi     = CalculateHT(GenJets,           4.7, 30);
      FourVector GenMHTForPuppi    = CalculateMHT(GenJets,          4.7, 30);
      FourVector GenMETForPuppi    = CalculateMHT(Particles,        4.7, 0);

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
      GenericObject BestL1Jet             = BestInRange(MPhaseII.Jet,         BestGenJet,        4.7, 0.5);
      GenericObject BestL1TkJet           = BestInRange(MPhaseII.TrackerJet,  BestCentralGenJet, 2.4, 0.5);
      GenericObject BestL1TkJetCharged    = BestInRange(MPhaseII.TrackerJet,  BestChargedGenJet, 2.4, 0.5);
      GenericObject BestL1TkCaloJet       = BestInRange(MPhaseII.TkCaloJet,   BestBarrelGenJet,  1.5, 0.5);
      GenericObject BestL1PuppiJet        = BestInRange(MPhaseII.PuppiJet,    BestGenJet,        4.7, 0.5);
      GenericObject BestL1CenPuppiJet     = BestInRange(MPhaseII.PuppiJet,    BestCentralGenJet, 2.4, 0.5);

      GenericObject BestL1Muon            = BestInRange(MPhaseII.Muon,        BestMuonWide,      2.4, 0.3);
      GenericObject BestL1MuonKF          = BestInRange(MPhaseII.MuonKF,      BestMuonBarrel,    1.5, 0.3);
      GenericObject BestL1TkMuon          = BestInRange(MPhaseII.TkMuon,      BestMuonWide,      2.4, 0.3);

      GenericObject BestL1EG              = BestInRange(MPhaseII.EG,          BestElectron,      3.0, 0.2);
      GenericObject BestL1TkEG            = BestInRange(MPhaseII.TkEG,        BestElectron,      3.0, 0.2);
      GenericObject BestL1TkEM            = BestInRange(MPhaseII.TkEM,        BestPhoton,        3.0, 0.2);
      GenericObject BestL1TkEGIso         = BestInRange(MPhaseII.TkEG,        BestElectron,      3.0, 0.2);
      GenericObject BestL1TkEMIso         = BestInRange(MPhaseII.TkEM,        BestPhoton,        3.0, 0.2);

      // Some HT four-vectors
      FourVector TkHT;      TkHT.SetPtEtaPhi(MPhaseII.TrackerMHT[0].PET, 0, 0);
      FourVector TkMHT =    MPhaseII.TrackerMHT[0].P;
      FourVector TkMET =    MPhaseII.TrackerMET[0].P;
      FourVector PuppiHT;   PuppiHT.SetPtEtaPhi(MPhaseII.PuppiMHT[0].PET, 0, 0);
      FourVector PuppiMHT = MPhaseII.PuppiMHT[0].P;
      FourVector PuppiMET = MPhaseII.PuppiMET[0].P;

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
      FillHistograms(HTkMuon,         HTkMuonNoMatch,       BestL1TkMuon.P,      BestMuonWide);

      FillHistograms(HEG,             HEGNoMatch,           BestL1EG.P,          BestElectron,    BestL1EG.Iso);
      FillHistograms(HTkEG,           HTkEGNoMatch,         BestL1TkEG.P,        BestElectron,    BestL1TkEG.Iso);
      FillHistograms(HTkEM,           HTkEMNoMatch,         BestL1TkEM.P,        BestPhoton,      BestL1TkEM.Iso);
      FillHistograms(HTkEGIso,        HTkEGIsoNoMatch,      BestL1TkEG.P,        BestIsoElectron, BestL1TkEG.Iso);
      FillHistograms(HTkEMIso,        HTkEMIsoNoMatch,      BestL1TkEM.P,        BestIsoPhoton,   BestL1TkEM.Iso);
      if(BestL1TkEG.Iso < 0.01)
      FillHistograms(HTkIsoEGIso,     HTkIsoEGIsoNoMatch,   BestL1TkEG.P,        BestIsoElectron, BestL1TkEG.Iso);
      if(BestL1TkEM.Iso < 0.01)
      FillHistograms(HTkIsoEMIso,     HTkIsoEMIsoNoMatch,   BestL1TkEM.P,        BestIsoPhoton,   BestL1TkEM.Iso);

      FillHistograms(HTkHT,           HTkHTNoMatch,         TkHT,                GenHTForTk);
      FillHistograms(HTkMHT,          HTkMHTNoMatch,        TkMHT,               GenMHTForTk);
      FillHistograms(HTkMET,          HTkMETNoMatch,        TkMET,               GenMETForTk);
      FillHistograms(HPuppiHT,        HPuppiHTNoMatch,      PuppiHT,             GenHTForPuppi);
      FillHistograms(HPuppiMHT,       HPuppiMHTNoMatch,     PuppiMHT,            GenMHTForPuppi);
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
   HTkMuon.Write(TkMuonDirectory);
   HTkMuonNoMatch.Write(TkMuonDirectory);
   HTkHT.Write(TkHTDirectory);
   HTkHTNoMatch.Write(TkHTDirectory);
   HTkMHT.Write(TkMHTDirectory);
   HTkMHTNoMatch.Write(TkMHTDirectory);
   HTkMET.Write(TkMETDirectory);
   HTkMETNoMatch.Write(TkMETDirectory);
   HPuppiHT.Write(PuppiHTDirectory);
   HPuppiHTNoMatch.Write(PuppiHTDirectory);
   HPuppiMHT.Write(PuppiMHTDirectory);
   HPuppiMHTNoMatch.Write(PuppiMHTDirectory);
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

GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MaxEta, double DRMax)
{
   GenericObject Best;
   Best.P = FourVector(-1, 0, 0, 0);
   Best.Iso = -1;
   for(int i = 0; i < (int)List.size(); i++)
   {
      if(List[i].P.GetAbsEta() > MaxEta)
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










