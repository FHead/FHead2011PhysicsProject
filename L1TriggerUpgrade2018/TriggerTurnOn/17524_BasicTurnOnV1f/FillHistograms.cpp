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

#include "Messenger.h"

#include "Histograms.h"

#define QUAL_NONE -1
#define QUAL_ODD -2

int main(int argc, char *argv[]);
FourVector BestInRange(vector<FourVector> &List, double AbsEta);
GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MaxEta = 999, double DRMax = 0.5, int Qual = QUAL_NONE);
FourVector CalculateHT(vector<FourVector> &GenJets, double Eta, double PT);
FourVector CalculateMHT(vector<FourVector> &GenJets, double Eta, double PT);
void FillHistograms(Histograms &Histogram, FourVector &Object, FourVector &Reference, double Isolation = -1);
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
   vector<string> InputFileNames = CL.GetStringVector("input", ',');
   string OutputFileName = CL.Get("output");
   bool UseStoredGen = CL.GetBool("StoredGen", true);
   bool DoChargedJet = CL.GetBool("DoCharged", false);

   // Output File and directories for better organization
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TDirectory *GenElectronDirectory      = OutputFile.mkdir("GenElectron",        "Gen electron");
   TDirectory *GenPhotonDirectory        = OutputFile.mkdir("GenPhoton",          "Gen photon");
   TDirectory *GenMuonDirectory          = OutputFile.mkdir("GenMuon",            "Gen Muon");
   TDirectory *IsoGenElectronDirectory   = OutputFile.mkdir("IsoGenElectron",     "Isolated gen electron");
   TDirectory *IsoGenPhotonDirectory     = OutputFile.mkdir("IsoGenPhoton",       "Isolated gen photon");
   TDirectory *IsoGenMuonDirectory       = OutputFile.mkdir("IsoGenMuon",         "Isolated gen Muon");

   TDirectory *JetDirectory              = OutputFile.mkdir("Jet",                "Jet (Gen jet)");
   TDirectory *TkJetDirectory            = OutputFile.mkdir("TkJet",              "TkJet (Gen jet)");
   TDirectory *TkJetChargedDirectory     = OutputFile.mkdir("TkJetCharged",       "TkJet (Charged jet)");
   TDirectory *TkCaloJetDirectory        = OutputFile.mkdir("TkCaloJet",          "TkCaloJet (Gen jet)");
   TDirectory *PuppiJetWideDirectory     = OutputFile.mkdir("PuppiJetWide",       "PuppiJet (eta 4.7)");
   TDirectory *PuppiJetDirectory         = OutputFile.mkdir("PuppiJet",           "PuppiJet (eta 2.4)");
   
   TDirectory *TkJetLDRDirectory         = OutputFile.mkdir("TkJetLargeDR",       "TkJet (Gen jet)");
   TDirectory *TkCaloJetLDRDirectory     = OutputFile.mkdir("TkCaloJetLargeDR",   "TkCaloJet (Gen jet)");
   TDirectory *PuppiJetLDRDirectory      = OutputFile.mkdir("PuppiJetLargeDR",    "PuppiJet (eta 2.4)");

   TDirectory *MuonDirectory             = OutputFile.mkdir("Muon",               "Muon (Muon)");
   TDirectory *MuonKFDirectory           = OutputFile.mkdir("MuonKF",             "MuonKF (Muon)");
   TDirectory *TkGlbMuonDirectory        = OutputFile.mkdir("TkGlbMuon",          "TkGlbMuon (Muon)");
   TDirectory *MuonIsoDirectory          = OutputFile.mkdir("MuonIso",            "Muon (Isolated muon)");
   TDirectory *MuonKFIsoDirectory        = OutputFile.mkdir("MuonKFIso",          "MuonKF (Isolated muon)");
   TDirectory *TkGlbMuonIsoDirectory     = OutputFile.mkdir("TkGlbMuonIso",       "TkGlbMuon (Isolated muon)");

   TDirectory *MuonLDRDirectory          = OutputFile.mkdir("MuonLargeDR",        "Muon (Muon)");
   TDirectory *MuonKFLDRDirectory        = OutputFile.mkdir("MuonKFLargeDR",      "MuonKF (Muon)");
   TDirectory *TkGlbMuonLDRDirectory     = OutputFile.mkdir("TkGlbMuonLargeDR",   "TkGlbMuon (Muon)");

   TDirectory *EGElectronDirectory       = OutputFile.mkdir("EGElectron",         "EG (Electron)");
   TDirectory *EGPhotonDirectory         = OutputFile.mkdir("EGPhoton",           "EG (Photon)");
   TDirectory *TkEGDirectory             = OutputFile.mkdir("TkEG",               "TkEG (Electron)");
   TDirectory *TkEMDirectory             = OutputFile.mkdir("TkEM",               "TkEM (Photon)");
   TDirectory *TkEGIsoDirectory          = OutputFile.mkdir("TkEGIso",            "TkEG (Isolated electron)");
   TDirectory *TkEMIsoDirectory          = OutputFile.mkdir("TkEMIso",            "TkEM (Isolated photon)");
   TDirectory *TkIsoEGIsoDirectory       = OutputFile.mkdir("TkIsoEGIso",         "TkIsoEG (Isolated electron)");
   TDirectory *TkIsoEMIsoDirectory       = OutputFile.mkdir("TkIsoEMIso",         "TkIsoEM (Isolated photon)");
   
   TDirectory *EGElectronLDRDirectory    = OutputFile.mkdir("EGElectronLargeDR",  "EG (Electron)");
   TDirectory *EGPhotonLDRDirectory      = OutputFile.mkdir("EGPhotonLargeDR",    "EG (Photon)");
   TDirectory *TkEGLDRDirectory          = OutputFile.mkdir("TkEGLargeDR",        "TkEG (Electron)");
   TDirectory *TkEMLDRDirectory          = OutputFile.mkdir("TkEMLargeDR",        "TkEM (Photon)");

   TDirectory *TkHT1Directory            = OutputFile.mkdir("TkHT1",              "HT from TkJet (1)");
   TDirectory *TkMHT1Directory           = OutputFile.mkdir("TkMHT1",             "MHT from TkJet (1)");
   TDirectory *TkHT2Directory            = OutputFile.mkdir("TkHT2",              "HT from TkJet (2)");
   TDirectory *TkMHT2Directory           = OutputFile.mkdir("TkMHT2",             "MHT from TkJet (2)");
   TDirectory *TkHT3Directory            = OutputFile.mkdir("TkHT3",              "HT from TkJet (3)");
   TDirectory *TkMHT3Directory           = OutputFile.mkdir("TkMHT3",             "MHT from TkJet (3)");
   TDirectory *TkHT4Directory            = OutputFile.mkdir("TkHT4",              "HT from TkJet (4)");
   TDirectory *TkMHT4Directory           = OutputFile.mkdir("TkMHT4",             "MHT from TkJet (4)");
   TDirectory *TkHT5Directory            = OutputFile.mkdir("TkHT5",              "HT from TkJet (5)");
   TDirectory *TkMHT5Directory           = OutputFile.mkdir("TkMHT5",             "MHT from TkJet (5)");
   TDirectory *TkMETDirectory            = OutputFile.mkdir("TkMET",              "MET from Tk");
   TDirectory *PuppiHT1Directory         = OutputFile.mkdir("PuppiHT1",           "HT from PuppiJet (1)");
   TDirectory *PuppiMHT1Directory        = OutputFile.mkdir("PuppiMHT1",          "MHT from PuppiJet (1)");
   TDirectory *PuppiHT2Directory         = OutputFile.mkdir("PuppiHT2",           "HT from PuppiJet (2)");
   TDirectory *PuppiMHT2Directory        = OutputFile.mkdir("PuppiMHT2",          "MHT from PuppiJet (2)");
   TDirectory *PuppiHT3Directory         = OutputFile.mkdir("PuppiHT3",           "HT from PuppiJet (3)");
   TDirectory *PuppiMHT3Directory        = OutputFile.mkdir("PuppiMHT3",          "MHT from PuppiJet (3)");
   TDirectory *PuppiMETDirectory         = OutputFile.mkdir("PuppiMET",           "MET from Puppi");

   // Create histograms
   vector<double> GenThresholds = {0};
   vector<double> JetThresholds = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60,
      75, 80, 85, 90, 100, 125, 150, 175, 200, 225, 250, 275, 300};
   vector<double> MuonThresholds = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30};
   vector<double> EGThresholds = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30};
   vector<double> HTThresholds = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 125, 150,
      175, 200, 225, 250, 300, 325, 350, 375, 400, 425, 450, 475, 500};
   
   Histograms HGenElectron   (200, 0, 150,  50, -3.5, 3.5, 200, 0, 5.0, GenThresholds,  "GenElectron");
   Histograms HGenPhoton     (200, 0, 150,  50, -3.5, 3.5, 200, 0, 5.0, GenThresholds,  "GenPhoton");
   Histograms HGenMuon       (200, 0, 150,  50, -3.5, 3.5, 200, 0, 5.0, GenThresholds,  "GenMuon");
   Histograms HIsoGenElectron(200, 0, 150,  50, -3.5, 3.5, 200, 0, 0.2, GenThresholds,  "IsoGenElectron");
   Histograms HIsoGenPhoton  (200, 0, 150,  50, -3.5, 3.5, 200, 0, 0.2, GenThresholds,  "IsoGenPhoton");
   Histograms HIsoGenMuon    (200, 0, 150,  50, -3.5, 3.5, 200, 0, 0.2, GenThresholds,  "IsoGenMuon");
   
   Histograms HJet           (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "Jet");
   Histograms HTkJet         (200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,  "TkJet");
   Histograms HTkJetCharged  (200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,  "TkJetCharged");
   Histograms HTkCaloJet     (500, 0, 500,  50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "TkCaloJet");
   Histograms HPuppiJetWide  (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "PuppiJetWide");
   Histograms HPuppiJet      (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "PuppiJet");

   Histograms HTkJetLDR      (200, 0, 1000, 50, -2.2, 2.2, 200, 0, 5.0, JetThresholds,  "TkJetLargeDR");
   Histograms HTkCaloJetLDR  (500, 0, 500,  50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "TkCaloJetLargeDR");
   Histograms HPuppiJetLDR   (200, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, JetThresholds,  "PuppiJetLargeDR");

   Histograms HMuon          (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "Muon");
   Histograms HMuonKF        (75,  0, 150,  30, -1.2, 1.2, 200, 0, 5.0, MuonThresholds, "MuonKF");
   Histograms HTkGlbMuon     (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkGlbMuon");
   Histograms HMuonIso       (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "MuonIso");
   Histograms HMuonKFIso     (75,  0, 150,  30, -1.2, 1.2, 200, 0, 5.0, MuonThresholds, "MuonKFIso");
   Histograms HTkGlbMuonIso  (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkGlbMuonIso");

   Histograms HMuonLDR       (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "MuonLargeDR");
   Histograms HMuonKFLDR     (75,  0, 150,  30, -1.2, 1.2, 200, 0, 5.0, MuonThresholds, "MuonKFLargeDR");
   Histograms HTkGlbMuonLDR  (75,  0, 150,  30, -2.5, 2.5, 200, 0, 5.0, MuonThresholds, "TkGlbMuonLargeDR");

   Histograms HEGElectron    (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, EGThresholds,   "EGElectron");
   Histograms HEGPhoton      (75,  0, 150,  30, -3.5, 3.5, 200, 0, 5.0, EGThresholds,   "EGPhoton");

   Histograms HTkEG          (75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,   "TkEG");
   Histograms HTkEM          (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "TkEM");
   Histograms HTkEGIso       (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,   "TkEGIso");
   Histograms HTkEMIso       (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "TkEMIso");
   Histograms HTkIsoEGIso    (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.5, EGThresholds,   "TkIsoEGIso");
   Histograms HTkIsoEMIso    (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "TkIsoEMIso");

   Histograms HEGElectronLDR (75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,   "EGElectronLargeDR");
   Histograms HEGPhotonLDR   (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "EGPhotonLargeDR");
   Histograms HTkEGLDR       (75,  0, 150,  30, -3.5, 3.5, 200, 0, 2.5, EGThresholds,   "TkEGLargeDR");
   Histograms HTkEMLDR       (75,  0, 150,  30, -3.5, 3.5, 200, 0, 0.8, EGThresholds,   "TkEMLargeDR");

   Histograms HTkHT1         (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT1");
   Histograms HTkMHT1        (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT1");
   Histograms HTkHT2         (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT2");
   Histograms HTkMHT2        (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT2");
   Histograms HTkHT3         (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT3");
   Histograms HTkMHT3        (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT3");
   Histograms HTkHT4         (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT4");
   Histograms HTkMHT4        (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT4");
   Histograms HTkHT5         (200, 0, 2000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkHT5");
   Histograms HTkMHT5        (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMHT5");
   Histograms HTkMET         (300, 0, 1000, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "TkMET");

   Histograms HPuppiHT1      (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiHT1");
   Histograms HPuppiMHT1     (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiMHT1");
   Histograms HPuppiHT2      (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiHT2");
   Histograms HPuppiMHT2     (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiMHT2");
   Histograms HPuppiHT3      (200, 0, 1500, 50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiHT3");
   Histograms HPuppiMHT3     (300, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiMHT3");
   Histograms HPuppiMET      (200, 0, 750,  50, -3.0, 3.0, 200, 0, 5.0, HTThresholds,   "PuppiMET");

   for(string InputFileName : InputFileNames)
   {
      cout << "Processing file " << InputFileName << endl;

      // Input File
      TFile File(InputFileName.c_str());

      // Messengers
      L1GenMessenger MGen(File, "genTree/L1GenTree");
      L1PhaseIITreeV1cMessenger MPhaseII(File, "l1PhaseIITree/L1PhaseIITree");

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

         // Best L1 objects
         int Qual = QUAL_NONE;
         GenericObject BestL1Jet            = BestInRange(MPhaseII.Jet,         BestGenJet,        4.7, 0.3, Qual);
         GenericObject BestL1TkJet          = BestInRange(MPhaseII.TrackerJet,  BestCentralGenJet, 2.4, 0.3, Qual);
         GenericObject BestL1TkJetCharged   = BestInRange(MPhaseII.TrackerJet,  BestChargedGenJet, 2.4, 0.3, Qual);
         GenericObject BestL1TkCaloJet      = BestInRange(MPhaseII.TkCaloJet,   BestBarrelGenJet,  1.5, 0.3, Qual);
         GenericObject BestL1PuppiJet       = BestInRange(MPhaseII.PuppiJet,    BestGenJet,        4.7, 0.3, Qual);
         GenericObject BestL1CenPuppiJet    = BestInRange(MPhaseII.PuppiJet,    BestCentralGenJet, 2.4, 0.3, Qual);
         
         Qual = QUAL_NONE;
         GenericObject BestL1TkJetLDR       = BestInRange(MPhaseII.TrackerJet,  BestCentralGenJet, 2.4, 1.0, Qual);
         GenericObject BestL1TkCaloJetLDR   = BestInRange(MPhaseII.TkCaloJet,   BestBarrelGenJet,  1.5, 1.0, Qual);
         GenericObject BestL1CenPuppiJetLDR = BestInRange(MPhaseII.PuppiJet,    BestCentralGenJet, 2.4, 1.0, Qual);

         Qual = QUAL_NONE;
         GenericObject BestL1Muon           = BestInRange(MPhaseII.Muon,        BestMuon,          2.4, 0.3, Qual);
         GenericObject BestL1MuonKF         = BestInRange(MPhaseII.MuonKF,      BestMuonBarrel,    1.0, 0.3, Qual);
         GenericObject BestL1TkGlbMuon      = BestInRange(MPhaseII.TkGlbMuon,   BestMuon,          2.4, 0.1, Qual);
         GenericObject BestL1MuonIso        = BestInRange(MPhaseII.Muon,        BestIsoMuon,       2.4, 0.3, Qual);
         GenericObject BestL1MuonKFIso      = BestInRange(MPhaseII.MuonKF,      BestIsoMuonBarrel, 1.0, 0.3, Qual);
         GenericObject BestL1TkGlbMuonIso   = BestInRange(MPhaseII.TkGlbMuon,   BestIsoMuon,       2.4, 0.1, Qual);

         Qual = QUAL_NONE;
         GenericObject BestL1MuonLDR        = BestInRange(MPhaseII.Muon,        BestMuon,          2.4, 1.0, Qual);
         GenericObject BestL1MuonKFLDR      = BestInRange(MPhaseII.MuonKF,      BestMuonBarrel,    1.0, 1.0, Qual);
         GenericObject BestL1TkGlbMuonLDR   = BestInRange(MPhaseII.TkGlbMuon,   BestMuon,          2.4, 1.0, Qual);

         Qual = QUAL_ODD;
         GenericObject BestL1EGElectron     = BestInRange(MPhaseII.EG,          BestElectron,      2.4, 0.2, Qual);
         GenericObject BestL1EGPhoton       = BestInRange(MPhaseII.EG,          BestPhoton,        2.4, 0.2, Qual);
         GenericObject BestL1TkEG           = BestInRange(MPhaseII.TkEG,        BestElectron,      2.4, 0.2, Qual);
         GenericObject BestL1TkEM           = BestInRange(MPhaseII.TkEM,        BestPhoton,        2.4, 0.2, Qual);
         GenericObject BestL1TkEGIso        = BestInRange(MPhaseII.TkEG,        BestElectron,      2.4, 0.2, Qual);
         GenericObject BestL1TkEMIso        = BestInRange(MPhaseII.TkEM,        BestPhoton,        2.4, 0.2, Qual);

         Qual = QUAL_ODD;
         GenericObject BestL1EGElectronLDR  = BestInRange(MPhaseII.EG,          BestElectron,      2.4, 1.0, Qual);
         GenericObject BestL1EGPhotonLDR    = BestInRange(MPhaseII.EG,          BestPhoton,        2.4, 1.0, Qual);
         GenericObject BestL1TkEGLDR        = BestInRange(MPhaseII.TkEG,        BestElectron,      2.4, 1.0, Qual);
         GenericObject BestL1TkEMLDR        = BestInRange(MPhaseII.TkEM,        BestPhoton,        2.4, 1.0, Qual);

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

         bool PassL1TkEGIso = false;
         bool PassL1TkEMIso = false;
         if(BestL1TkEG.P.GetAbsEta() < 1.5 && BestL1TkEG.Iso < 0.12)   PassL1TkEGIso = true;
         if(BestL1TkEG.P.GetAbsEta() > 1.5 && BestL1TkEG.Iso < 0.30)   PassL1TkEGIso = true;
         if(BestL1TkEM.P.GetAbsEta() < 1.5 && BestL1TkEM.Iso < 0.28)   PassL1TkEMIso = true;
         if(BestL1TkEM.P.GetAbsEta() > 1.5 && BestL1TkEM.Iso < 0.36)   PassL1TkEMIso = true;

         // Fill Histograms
         FillHistograms(HGenElectron,    BestElectron,           GenElectronIsolation);
         FillHistograms(HGenPhoton,      BestPhoton,             GenPhotonIsolation);
         FillHistograms(HGenMuon,        BestMuon,               GenMuonIsolation);
         FillHistograms(HIsoGenElectron, BestIsoElectron,        GenElectronIsolation);
         FillHistograms(HIsoGenPhoton,   BestIsoPhoton,          GenPhotonIsolation);
         FillHistograms(HIsoGenMuon,     BestIsoMuon,            GenMuonIsolation);

         FillHistograms(HJet,            BestL1Jet.P,            BestGenJet);
         FillHistograms(HTkJet,          BestL1TkJet.P,          BestCentralGenJet);
         FillHistograms(HTkJetCharged,   BestL1TkJet.P,          BestChargedGenJet);
         FillHistograms(HTkCaloJet,      BestL1TkCaloJet.P,      BestBarrelGenJet);
         FillHistograms(HPuppiJetWide,   BestL1PuppiJet.P,       BestGenJet);
         FillHistograms(HPuppiJet,       BestL1CenPuppiJet.P,    BestCentralGenJet);
         
         FillHistograms(HTkJetLDR,       BestL1TkJetLDR.P,       BestCentralGenJet);
         FillHistograms(HTkCaloJetLDR,   BestL1TkCaloJetLDR.P,   BestBarrelGenJet);
         FillHistograms(HPuppiJetLDR,    BestL1CenPuppiJetLDR.P, BestCentralGenJet);

         FillHistograms(HMuon,           BestL1Muon.P,           BestMuon,          BestL1Muon.Iso);
         FillHistograms(HMuonKF,         BestL1MuonKF.P,         BestMuonBarrel,    BestL1MuonKF.Iso);
         FillHistograms(HTkGlbMuon,      BestL1TkGlbMuon.P,      BestMuon,          BestL1TkGlbMuon.Iso);
         FillHistograms(HMuonIso,        BestL1Muon.P,           BestIsoMuon,       BestL1Muon.Iso);
         FillHistograms(HMuonKFIso,      BestL1MuonKF.P,         BestIsoMuonBarrel, BestL1MuonKF.Iso);
         FillHistograms(HTkGlbMuonIso,   BestL1TkGlbMuon.P,      BestIsoMuon,       BestL1TkGlbMuon.Iso);

         FillHistograms(HMuonLDR,        BestL1MuonLDR.P,        BestMuon,          BestL1Muon.Iso);
         FillHistograms(HMuonKFLDR,      BestL1MuonKFLDR.P,      BestMuonBarrel,    BestL1MuonKF.Iso);
         FillHistograms(HTkGlbMuonLDR,   BestL1TkGlbMuonLDR.P,   BestMuon,          BestL1TkGlbMuon.Iso);

         FillHistograms(HEGElectron,     BestL1EGElectron.P,     BestElectron,      BestL1EGElectron.Iso);
         FillHistograms(HEGPhoton,       BestL1EGPhoton.P,       BestPhoton,        BestL1EGPhoton.Iso);
         FillHistograms(HTkEG,           BestL1TkEG.P,           BestElectron,      BestL1TkEG.Iso);
         FillHistograms(HTkEM,           BestL1TkEM.P,           BestPhoton,        BestL1TkEM.Iso);
         FillHistograms(HTkEGIso,        BestL1TkEG.P,           BestIsoElectron,   BestL1TkEG.Iso);
         FillHistograms(HTkEMIso,        BestL1TkEM.P,           BestIsoPhoton,     BestL1TkEM.Iso);
         if(PassL1TkEGIso)
         FillHistograms(HTkIsoEGIso,     BestL1TkEG.P,           BestIsoElectron,   BestL1TkEG.Iso);
         if(PassL1TkEMIso)
         FillHistograms(HTkIsoEMIso,     BestL1TkEM.P,           BestIsoPhoton,     BestL1TkEM.Iso);

         FillHistograms(HEGElectronLDR,  BestL1EGElectronLDR.P,  BestElectron,      BestL1EGElectronLDR.Iso);
         FillHistograms(HEGPhotonLDR,    BestL1EGPhotonLDR.P,    BestPhoton,        BestL1EGPhotonLDR.Iso);
         FillHistograms(HTkEGLDR,        BestL1TkEGLDR.P,        BestElectron,      BestL1TkEGLDR.Iso);
         FillHistograms(HTkEMLDR,        BestL1TkEMLDR.P,        BestPhoton,        BestL1TkEMLDR.Iso);

         FillHistograms(HTkHT1,          TkHT1,                  GenHTForTk1);
         FillHistograms(HTkMHT1,         TkMHT1,                 GenMHTForTk1);
         FillHistograms(HTkHT2,          TkHT2,                  GenHTForTk2);
         FillHistograms(HTkMHT2,         TkMHT2,                 GenMHTForTk2);
         FillHistograms(HTkHT3,          TkHT3,                  GenHTForTk3);
         FillHistograms(HTkMHT3,         TkMHT3,                 GenMHTForTk3);
         FillHistograms(HTkHT4,          TkHT4,                  GenHTForTk4);
         FillHistograms(HTkMHT4,         TkMHT4,                 GenMHTForTk4);
         FillHistograms(HTkHT5,          TkHT5,                  GenHTForTk5);
         FillHistograms(HTkMHT5,         TkMHT5,                 GenMHTForTk5);
         FillHistograms(HTkMET,          TkMET,                  GenMETForTk);
         
         FillHistograms(HPuppiHT1,       PuppiHT1,               GenHTForPuppi1);
         FillHistograms(HPuppiMHT1,      PuppiMHT1,              GenMHTForPuppi1);
         FillHistograms(HPuppiHT2,       PuppiHT2,               GenHTForPuppi2);
         FillHistograms(HPuppiMHT2,      PuppiMHT2,              GenMHTForPuppi2);
         FillHistograms(HPuppiHT3,       PuppiHT3,               GenHTForPuppi3);
         FillHistograms(HPuppiMHT3,      PuppiMHT3,              GenMHTForPuppi3);
         FillHistograms(HPuppiMET,       PuppiMET,               GenMETForPuppi);
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
   HMuon.Write(MuonDirectory);
   HMuonKF.Write(MuonKFDirectory);
   HTkGlbMuon.Write(TkGlbMuonDirectory);
   HMuonIso.Write(MuonIsoDirectory);
   HMuonKFIso.Write(MuonKFIsoDirectory);
   HTkGlbMuonIso.Write(TkGlbMuonIsoDirectory);
   HMuonLDR.Write(MuonLDRDirectory);
   HMuonKFLDR.Write(MuonKFLDRDirectory);
   HTkGlbMuonLDR.Write(TkGlbMuonLDRDirectory);
   HEGElectron.Write(EGElectronDirectory);
   HEGPhoton.Write(EGPhotonDirectory);
   HTkEG.Write(TkEGDirectory);
   HTkEM.Write(TkEMDirectory);
   HTkEGIso.Write(TkEGIsoDirectory);
   HTkEMIso.Write(TkEMIsoDirectory);
   HTkIsoEGIso.Write(TkIsoEGIsoDirectory);
   HTkIsoEMIso.Write(TkIsoEMIsoDirectory);
   HEGElectronLDR.Write(EGElectronLDRDirectory);
   HEGPhotonLDR.Write(EGPhotonLDRDirectory);
   HTkEGLDR.Write(TkEGLDRDirectory);
   HTkEMLDR.Write(TkEMLDRDirectory);
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

void FillHistograms(Histograms &Histogram, FourVector &Object, FourVector &Reference, double Isolation)
{
   Histogram.Fill(Object, Reference, Isolation);
}

void FillHistograms(Histograms &Histogram, FourVector &Object, double Isolation)
{
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










