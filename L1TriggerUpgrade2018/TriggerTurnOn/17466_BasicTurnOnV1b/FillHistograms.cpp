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
GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MaxEta = 999);
FourVector CalculateHT(vector<FourVector> &GenJets, double Eta, double PT);
FourVector CalculateMHT(vector<FourVector> &GenJets, double Eta, double PT);

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

   TDirectory *JetDirectory         = OutputFile.mkdir("Jet",         "Histograms for Jet (Gen jet)");
   TDirectory *MuonDirectory        = OutputFile.mkdir("Muon",        "Histograms for Muon (Muon)");
   TDirectory *MuonKFDirectory      = OutputFile.mkdir("MuonKF",      "Histograms for MuonKF (Muon)");
   TDirectory *EGDirectory          = OutputFile.mkdir("EG",          "Histograms for EG (Electron)");
   TDirectory *TkEGDirectory        = OutputFile.mkdir("TkEG",        "Histograms for TkEG (Electron)");
   TDirectory *TkEMDirectory        = OutputFile.mkdir("TkEM",        "Histograms for TkEM (Photon)");
   TDirectory *TkJetDirectory       = OutputFile.mkdir("TkJet",       "Histograms for TkJet (Gen jet)");
   TDirectory *TkCaloJetDirectory   = OutputFile.mkdir("TkCaloJet",   "Histograms for TkCaloJet (Gen jet)");
   TDirectory *TkMuonDirectory      = OutputFile.mkdir("TkMuon",      "Histograms for TkMuon (Muon)");
   TDirectory *PuppiJetDirectory    = OutputFile.mkdir("PuppiJet",    "Histograms for PuppiJet (Gen jet)");
   TDirectory *TkHTDirectory        = OutputFile.mkdir("TkHT",        "Histograms for HT from TkJet");
   TDirectory *TkMHTDirectory       = OutputFile.mkdir("TkMHT",       "Histograms for MHT from TkJet");
   TDirectory *TkMETDirectory       = OutputFile.mkdir("TkMET",       "Histograms for MET from Tk");
   TDirectory *PuppiHTDirectory     = OutputFile.mkdir("PuppiHT",     "Histograms for HT from PuppiJet");
   TDirectory *PuppiMHTDirectory    = OutputFile.mkdir("PuppiMHT",    "Histograms for MHT from PuppiJet");
   TDirectory *PuppiMETDirectory    = OutputFile.mkdir("PuppiMET",    "Histograms for MET from Puppi");

   // Create histograms
   vector<double> JetThresholds = {0, 25, 50, 75, 100, 150, 200, 250, 300};
   Histograms HJet          (200, 0, 1000, 50, -3, 3,  2000, 0, 5, JetThresholds, "Jet");
   Histograms HJetNoMatching(200, 0, 1000, 50, -3, 3,  2000, 0, 5, JetThresholds, "JetNoMatching");

   vector<double> MuonThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HMuon          (75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, MuonThresholds, "Muon");
   Histograms HMuonNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, MuonThresholds, "MuonNoMatching");

   vector<double> MuonKFThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HMuonKF          (75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, MuonKFThresholds, "MuonKF");
   Histograms HMuonKFNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, MuonKFThresholds, "MuonKFNoMatching");

   vector<double> EGThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HEG          (75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, EGThresholds, "EG");
   Histograms HEGNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, EGThresholds, "EGNoMatching");

   vector<double> TkEGThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HTkEG          (75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEGThresholds, "TkEG");
   Histograms HTkEGNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEGThresholds, "TkEGNoMatching");

   vector<double> TkEMThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HTkEM          (75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEMThresholds, "TkEM");
   Histograms HTkEMNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEMThresholds, "TkEMNoMatching");

   vector<double> TkJetThresholds = {0, 25, 50, 75, 100, 150, 200, 250, 300};
   Histograms HTkJet          (200, 0, 1000, 50, -2.2, 2.2,  2000, 0, 5, TkJetThresholds, "TkJet");
   Histograms HTkJetNoMatching(200, 0, 1000, 50, -2.2, 2.2,  2000, 0, 5, TkJetThresholds, "TkJetNoMatching");
   
   vector<double> TkCaloJetThresholds = {0, 25, 50, 75, 100, 150, 200, 250, 300};
   Histograms HTkCaloJet          (200, 0, 1000, 50, -3, 3,  2000, 0, 5, TkCaloJetThresholds, "TkCaloJet");
   Histograms HTkCaloJetNoMatching(200, 0, 1000, 50, -3, 3,  2000, 0, 5, TkCaloJetThresholds, "TkCaloJetNoMatching");

   vector<double> TkMuonThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HTkMuon          (75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkMuonThresholds, "TkMuon");
   Histograms HTkMuonNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkMuonThresholds, "TkMuonNoMatching");

   vector<double> PuppiJetThresholds = {0, 25, 50, 75, 100, 150, 200, 250, 300};
   Histograms HPuppiJet          (200, 0, 1000, 50, -3, 3,  2000, 0, 5, PuppiJetThresholds, "PuppiJet");
   Histograms HPuppiJetNoMatching(200, 0, 1000, 50, -3, 3,  2000, 0, 5, PuppiJetThresholds, "PuppiJetNoMatching");

   vector<double> TkHTThresholds = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
   Histograms HTkHT          (200, 0, 2000, 50, -3, 3,  2000, 0, 5, TkHTThresholds, "TkHT");
   Histograms HTkHTNoMatching(200, 0, 2000, 50, -3, 3,  2000, 0, 5, TkHTThresholds, "TkHTNoMatching");

   vector<double> TkMHTThresholds = {0, 20, 40, 60, 80, 100, 125, 150};
   Histograms HTkMHT          (200, 0, 1000, 50, -3, 3,  2000, 0, 5, TkMHTThresholds, "TkMHT");
   Histograms HTkMHTNoMatching(200, 0, 1000, 50, -3, 3,  2000, 0, 5, TkMHTThresholds, "TkMHTNoMatching");

   vector<double> TkMETThresholds = {0, 20, 40, 60, 80, 100, 125, 150};
   Histograms HTkMET          (200, 0, 1000, 50, -3, 3,  2000, 0, 5, TkMETThresholds, "TkMET");
   Histograms HTkMETNoMatching(200, 0, 1000, 50, -3, 3,  2000, 0, 5, TkMETThresholds, "TkMETNoMatching");

   vector<double> PuppiHTThresholds = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
   Histograms HPuppiHT          (200, 0, 750, 50, -3, 3,  2000, 0, 5, PuppiHTThresholds, "PuppiHT");
   Histograms HPuppiHTNoMatching(200, 0, 750, 50, -3, 3,  2000, 0, 5, PuppiHTThresholds, "PuppiHTNoMatching");

   vector<double> PuppiMHTThresholds = {0, 20, 40, 60, 80, 100, 125, 150};
   Histograms HPuppiMHT          (200, 0, 750, 50, -3, 3,  2000, 0, 5, PuppiMHTThresholds, "PuppiMHT");
   Histograms HPuppiMHTNoMatching(200, 0, 750, 50, -3, 3,  2000, 0, 5, PuppiMHTThresholds, "PuppiMHTNoMatching");

   vector<double> PuppiMETThresholds = {0, 20, 40, 60, 80, 100, 125, 150};
   Histograms HPuppiMET          (200, 0, 750, 50, -3, 3,  2000, 0, 5, PuppiMETThresholds, "PuppiMET");
   Histograms HPuppiMETNoMatching(200, 0, 750, 50, -3, 3,  2000, 0, 5, PuppiMETThresholds, "PuppiMETNoMatching");

   // Loop over events
   int EntryCount = MGen.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MGen.GetEntry(iE);
      MPhaseII.GetEntry(iE);

      vector<FourVector> Electrons;
      vector<FourVector> Photons;
      vector<FourVector> Muons;
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

         if(MGen.GenStatus[i] == 1)   // we only want final state particles here (Pythia6)
            Particles.push_back(MGen.GenP[i]);
      }

      // Cluster gen jets
      vector<fastjet::PseudoJet> Candidates;
      for(int i = 0; i < (int)Particles.size(); i++)
         Candidates.push_back(fastjet::PseudoJet(Particles[i][1], Particles[i][2], Particles[i][3], Particles[i][0]));
      fastjet::JetDefinition Definition(fastjet::antikt_algorithm, 0.4);
      fastjet::ClusterSequence Sequence(Candidates, Definition);
      vector<fastjet::PseudoJet> Jets = Sequence.inclusive_jets();
      vector<FourVector> GenJets;
      for(int i = 0; i < (int)Jets.size(); i++)
         GenJets.push_back(FourVector(Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()));

      // Best reference objects
      FourVector BestGenJet        = BestInRange(GenJets,    4.7);
      FourVector BestCenGenJet     = BestInRange(GenJets,    2.2);
      FourVector BestElectron      = BestInRange(Electrons,  3.0);
      FourVector BestPhoton        = BestInRange(Photons,    3.0);
      FourVector BestMuon          = BestInRange(Muons,      2.1);
      FourVector GenHTForTk        = CalculateHT(GenJets,    2.2, 15);
      FourVector GenMHTForTk       = CalculateMHT(GenJets,   2.2, 15);
      FourVector GenMETForTk       = CalculateMHT(Particles, 2.2, 0);
      FourVector GenHTForPuppi     = CalculateHT(GenJets,    4.7, 30);
      FourVector GenMHTForPuppi    = CalculateMHT(GenJets,   4.7, 30);
      FourVector GenMETForPuppi    = CalculateMHT(Particles, 4.7, 0);

      // Best L1 objects
      GenericObject BestL1Jet         = BestInRange(MPhaseII.Jet,         BestGenJet,    4.7);
      GenericObject BestL1Muon        = BestInRange(MPhaseII.Muon,        BestMuon,      2.1);
      GenericObject BestL1MuonKF      = BestInRange(MPhaseII.MuonKF,      BestMuon,      2.1);
      GenericObject BestL1EG          = BestInRange(MPhaseII.EG,          BestElectron,  3.0);
      GenericObject BestL1TkEG        = BestInRange(MPhaseII.TkEG,        BestElectron,  3.0);
      GenericObject BestL1TkEM        = BestInRange(MPhaseII.TkEM,        BestPhoton,    3.0);
      GenericObject BestL1TkJet       = BestInRange(MPhaseII.TrackerJet,  BestCenGenJet, 2.2);
      GenericObject BestL1TkCaloJet   = BestInRange(MPhaseII.TkCaloJet,   BestGenJet,    4.7);
      GenericObject BestL1TkMuon      = BestInRange(MPhaseII.TkMuon,      BestMuon,      2.1);
      GenericObject BestL1PuppiJet    = BestInRange(MPhaseII.PuppiJet,    BestGenJet,    4.7);

      // Fill Histograms
      if(BestGenJet[0] > 0 && BestL1Jet.P[0] > 0)
         HJet.Fill(BestL1Jet.P, BestGenJet, -1);
      if(BestGenJet[0] > 0)
         HJetNoMatching.Fill(BestL1Jet.P, BestGenJet, -1);
      
      if(BestMuon[0] > 0 && BestL1Muon.P[0] > 0)
         HMuon.Fill(BestL1Muon.P, BestMuon, -1);
      if(BestMuon[0] > 0)
         HMuonNoMatching.Fill(BestL1Muon.P, BestMuon, -1);
      
      if(BestMuon[0] > 0 && BestL1MuonKF.P[0] > 0)
         HMuonKF.Fill(BestL1MuonKF.P, BestMuon, -1);
      if(BestMuon[0] > 0)
         HMuonKFNoMatching.Fill(BestL1MuonKF.P, BestMuon, -1);
      
      if(BestElectron[0] > 0 && BestL1EG.P[0] > 0)
         HEG.Fill(BestL1EG.P, BestElectron, -1);
      if(BestElectron[0] > 0)
         HEGNoMatching.Fill(BestL1EG.P, BestElectron, -1);
      
      if(BestElectron[0] > 0 && BestL1TkEG.P[0] > 0)
         HTkEG.Fill(BestL1TkEG.P, BestElectron, -1);
      if(BestElectron[0] > 0)
         HTkEGNoMatching.Fill(BestL1TkEG.P, BestElectron, -1);
      
      if(BestPhoton[0] > 0 && BestL1TkEM.P[0] > 0)
         HTkEM.Fill(BestL1TkEM.P, BestPhoton, -1);
      if(BestPhoton[0] > 0)
         HTkEMNoMatching.Fill(BestL1TkEM.P, BestPhoton, -1);
      
      if(BestCenGenJet[0] > 0 && BestL1TkJet.P[0] > 0)
         HTkJet.Fill(BestL1TkJet.P, BestCenGenJet, -1);
      if(BestCenGenJet[0] > 0)
         HTkJetNoMatching.Fill(BestL1TkJet.P, BestCenGenJet, -1);
      
      if(BestGenJet[0] > 0 && BestL1TkCaloJet.P[0] > 0)
         HTkCaloJet.Fill(BestL1TkCaloJet.P, BestGenJet, -1);
      if(BestGenJet[0] > 0)
         HTkCaloJetNoMatching.Fill(BestL1TkCaloJet.P, BestGenJet, -1);
      
      if(BestMuon[0] > 0 && BestL1TkMuon.P[0] > 0)
         HTkMuon.Fill(BestL1TkMuon.P, BestMuon, -1);
      if(BestMuon[0] > 0)
         HTkMuonNoMatching.Fill(BestL1TkMuon.P, BestMuon, -1);

      if(BestGenJet[0] > 0 && BestL1PuppiJet.P[0] > 0)
         HPuppiJet.Fill(BestL1PuppiJet.P, BestGenJet, -1);
      if(BestGenJet[0] > 0)
         HPuppiJetNoMatching.Fill(BestL1PuppiJet.P, BestGenJet, -1);

      FourVector TkHT;
      TkHT.SetPtEtaPhi(MPhaseII.TrackerMHT[0].PET, 0, 0);
      HTkHT.Fill(TkHT.P, GenHTForTk, -1);
      HTkHTNoMatching.Fill(TkHT.P, GenHTForTk, -1);
      HTkMHT.Fill(MPhaseII.TrackerMHT[0].P, GenMHTForTk, -1);
      HTkMHTNoMatching.Fill(MPhaseII.TrackerMHT[0].P, GenMHTForTk, -1);
      HTkMET.Fill(MPhaseII.TrackerMET[0].P, GenMETForTk, -1);
      HTkMETNoMatching.Fill(MPhaseII.TrackerMET[0].P, GenMETForTk, -1);
      
      FourVector PuppiHT;
      PuppiHT.SetPtEtaPhi(MPhaseII.PuppiMHT[0].PET, 0, 0);
      HPuppiHT.Fill(PuppiHT.P, GenHTForPuppi, -1);
      HPuppiHTNoMatching.Fill(PuppiHT.P, GenHTForPuppi, -1);
      HPuppiMHT.Fill(MPhaseII.PuppiMHT[0].P, GenMHTForPuppi, -1);
      HPuppiMHTNoMatching.Fill(MPhaseII.PuppiMHT[0].P, GenMHTForPuppi, -1);
      HPuppiMET.Fill(MPhaseII.PuppiMET[0].P, GenMETForPuppi, -1);
      HPuppiMETNoMatching.Fill(MPhaseII.PuppiMET[0].P, GenMETForPuppi, -1);
   }

   // Write result to file
   HJet.Write(JetDirectory);
   HJetNoMatching.Write(JetDirectory);
   HMuon.Write(MuonDirectory);
   HMuonNoMatching.Write(MuonDirectory);
   HMuonKF.Write(MuonKFDirectory);
   HMuonKFNoMatching.Write(MuonKFDirectory);
   HEG.Write(EGDirectory);
   HEGNoMatching.Write(EGDirectory);
   HTkEG.Write(TkEGDirectory);
   HTkEGNoMatching.Write(TkEGDirectory);
   HTkEM.Write(TkEMDirectory);
   HTkEMNoMatching.Write(TkEMDirectory);
   HTkJet.Write(TkJetDirectory);
   HTkJetNoMatching.Write(TkJetDirectory);
   HTkCaloJet.Write(TkCaloJetDirectory);
   HTkCaloJetNoMatching.Write(TkCaloJetDirectory);
   HTkMuon.Write(TkMuonDirectory);
   HTkMuonNoMatching.Write(TkMuonDirectory);
   HPuppiJet.Write(PuppiJetDirectory);
   HPuppiJetNoMatching.Write(PuppiJetDirectory);
   HTkHT.Write(TkHTDirectory);
   HTkHTNoMatching.Write(TkHTDirectory);
   HTkMHT.Write(TkMHTDirectory);
   HTkMHTNoMatching.Write(TkMHTDirectory);
   HTkMET.Write(TkMETDirectory);
   HTkMETNoMatching.Write(TkMETDirectory);
   HPuppiHT.Write(PuppiHTDirectory);
   HPuppiHTNoMatching.Write(PuppiHTDirectory);
   HPuppiMHT.Write(PuppiMHTDirectory);
   HPuppiMHTNoMatching.Write(PuppiMHTDirectory);
   HPuppiMET.Write(PuppiMETDirectory);
   HPuppiMETNoMatching.Write(PuppiMETDirectory);

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

GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MaxEta)
{
   GenericObject Best;
   Best.P = FourVector(-1, 0, 0, 0);
   Best.Iso = -1;
   for(int i = 0; i < (int)List.size(); i++)
   {
      if(List[i].P.GetAbsEta() > MaxEta)
         continue;
      if(GetDR(List[i].P, Reference) <= 0.5)
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













