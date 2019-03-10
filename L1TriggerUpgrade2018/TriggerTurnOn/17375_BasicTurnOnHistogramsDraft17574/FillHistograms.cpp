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
GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference);

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
   L1PhaseIITreeDraft17374Messenger MPhaseII(File, "l1PhaseIITree/L1PhaseIITree");

   if(MGen.Tree == NULL)
      return -1;

   // Output File and directories for better organization
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TDirectory *EGDirectory          = OutputFile.mkdir("EG",          "Histograms for EG (Photon)");
   TDirectory *TkEGDirectory        = OutputFile.mkdir("TkEG",        "Histograms for tkEG (Electron)");
   TDirectory *TkEMDirectory        = OutputFile.mkdir("TkEM",        "Histograms for tkEM (Photon)");
   TDirectory *EGCrystalDirectory   = OutputFile.mkdir("EGCrystal",   "Histograms for EGCrystal (Photon)");
   TDirectory *TkEGCrystalDirectory = OutputFile.mkdir("TkEGCrystal", "Histograms for tkEGCrystal (Electron)");
   TDirectory *TkEMCrystalDirectory = OutputFile.mkdir("TkEMCrystal", "Histograms for tkEMCrystal (Photon)");
   TDirectory *JetDirectory         = OutputFile.mkdir("Jet",         "Histograms for jets (Gen Jet)");
   TDirectory *TkJetDirectory       = OutputFile.mkdir("TkJet",       "Histograms for tk jets (Gen Jet)");

   // Create histograms
   vector<double> EGThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HEG(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, EGThresholds, "EG");
   Histograms HEGNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, EGThresholds, "EGNoMatching");

   vector<double> TkEGThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HTkEG(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEGThresholds, "TkEG");
   Histograms HTkEGNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEGThresholds, "TkEGNoMatching");

   vector<double> TkEMThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HTkEM(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEMThresholds, "TkEM");
   Histograms HTkEMNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEMThresholds, "TkEMNoMatching");

   vector<double> EGCrystalThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HEGCrystal(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, EGCrystalThresholds, "EGCrystal");
   Histograms HEGCrystalNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, EGCrystalThresholds, "EGCrystalNoMatching");

   vector<double> TkEGCrystalThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HTkEGCrystal(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEGCrystalThresholds, "TkEGCrystal");
   Histograms HTkEGCrystalNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEGCrystalThresholds, "TkEGCrystalNoMatching");

   vector<double> TkEMCrystalThresholds = {0, 12, 15, 20, 25, 30};
   Histograms HTkEMCrystal(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEMCrystalThresholds, "TkEMCrystal");
   Histograms HTkEMCrystalNoMatching(75, 0, 150, 30, -3.5, 3.5,  2000, 0, 5, TkEMCrystalThresholds, "TkEMCrystalNoMatching");

   vector<double> JetThresholds = {0, 25, 50, 75, 100, 150, 200, 250, 300};
   Histograms HJet(500, 0, 1000, 50, -3, 3,  2000, 0, 5, JetThresholds, "Jet");
   Histograms HJetNoMatching(500, 0, 1000, 50, -3, 3,  2000, 0, 5, JetThresholds, "JetNoMatching");

   vector<double> TkJetThresholds = {0, 25, 50, 75, 100, 150, 200, 250, 300};
   Histograms HTkJet(500, 0, 1000, 50, -3, 3,  2000, 0, 5, TkJetThresholds, "TkJet");
   Histograms HTkJetNoMatching(500, 0, 1000, 50, -3, 3,  2000, 0, 5, TkJetThresholds, "TkJetNoMatching");

   // Loop over events
   int EntryCount = MGen.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MGen.GetEntry(iE);
      MPhaseII.GetEntry(iE);

      vector<FourVector> Partons;
      vector<FourVector> FinalPartons;
      vector<FourVector> Electrons;
      vector<FourVector> Photons;
      vector<FourVector> Particles;

      // Collect gen-particles
      for(int i = 0; i < (int)MGen.GenP.size(); i++)
      {
         int AbsID = MGen.GenID[i];
         if(AbsID < 0)
            AbsID = -AbsID;

         if(AbsID == 11)
            Electrons.push_back(MGen.GenP[i]);
         if(AbsID == 22)
            Photons.push_back(MGen.GenP[i]);

         if(MGen.GenStatus[i] == 1)   // we only want final state particles here (Pythia6)
         {
            if((AbsID >= 1 && AbsID <= 5) || AbsID == 21)
               FinalPartons.push_back(MGen.GenP[i]);
            Particles.push_back(MGen.GenP[i]);
         }
         if(MGen.GenStatus[i] == 3)   // Huh?
            if((AbsID >= 1 && AbsID <= 5) || AbsID == 21)
               Partons.push_back(MGen.GenP[i]);
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
      FourVector BestParton        = BestInRange(Partons,   3.0);
      FourVector BestGenJet        = BestInRange(GenJets,   3.0);
      FourVector BestElectron      = BestInRange(Electrons, 2.4);
      FourVector BestPhoton        = BestInRange(Photons,   2.4);

      // Best L1 objects
      GenericObject BestL1JetGen      = BestInRange(MPhaseII.Jet,         BestGenJet);
      GenericObject BestL1TkJetGen    = BestInRange(MPhaseII.TkJet,       BestGenJet);
      GenericObject BestL1EG          = BestInRange(MPhaseII.EG,          BestPhoton);
      GenericObject BestL1TkEG        = BestInRange(MPhaseII.TkEG,        BestElectron);
      GenericObject BestL1TkEM        = BestInRange(MPhaseII.TkEM,        BestPhoton);
      GenericObject BestL1EGCrystal   = BestInRange(MPhaseII.EGCrystal,   BestPhoton);
      GenericObject BestL1TkEGCrystal = BestInRange(MPhaseII.TkEGCrystal, BestElectron);
      GenericObject BestL1TkEMCrystal = BestInRange(MPhaseII.TkEMCrystal, BestPhoton);

      // Fill Histograms
      if(BestPhoton[0] > 0 && BestL1EG.P[0] > 0)
         HEG.Fill(BestL1EG.P, BestPhoton, -1);
      if(BestPhoton[0] > 0)
         HEGNoMatching.Fill(BestL1EG.P, BestPhoton, -1);

      if(BestElectron[0] > 0 && BestL1TkEG.P[0] > 0)
         HTkEG.Fill(BestL1TkEG.P, BestElectron, BestL1TkEG.Iso);
      if(BestElectron[0] > 0)
         HTkEGNoMatching.Fill(BestL1TkEG.P, BestElectron, BestL1TkEG.Iso);

      if(BestPhoton[0] > 0 && BestL1TkEM.P[0] > 0)
         HTkEM.Fill(BestL1TkEM.P, BestPhoton, BestL1TkEM.Iso);
      if(BestPhoton[0] > 0)
         HTkEMNoMatching.Fill(BestL1TkEM.P, BestPhoton, BestL1TkEM.Iso);

      if(BestPhoton[0] > 0 && BestL1EGCrystal.P[0] > 0)
         HEGCrystal.Fill(BestL1EGCrystal.P, BestPhoton, -1);
      if(BestPhoton[0] > 0)
         HEGCrystalNoMatching.Fill(BestL1EGCrystal.P, BestPhoton, -1);

      if(BestElectron[0] > 0 && BestL1TkEGCrystal.P[0] > 0)
         HTkEGCrystal.Fill(BestL1TkEGCrystal.P, BestElectron, BestL1TkEGCrystal.Iso);
      if(BestElectron[0] > 0)
         HTkEGCrystalNoMatching.Fill(BestL1TkEGCrystal.P, BestElectron, BestL1TkEGCrystal.Iso);

      if(BestPhoton[0] > 0 && BestL1TkEMCrystal.P[0] > 0)
         HTkEMCrystal.Fill(BestL1TkEMCrystal.P, BestPhoton, BestL1TkEMCrystal.Iso);
      if(BestPhoton[0] > 0)
         HTkEMCrystalNoMatching.Fill(BestL1TkEMCrystal.P, BestPhoton, BestL1TkEMCrystal.Iso);

      if(BestGenJet[0] > 0 && BestL1JetGen.P[0] > 0)
         HJet.Fill(BestL1JetGen.P, BestGenJet, -1);
      if(BestGenJet[0] > 0)
         HJetNoMatching.Fill(BestL1JetGen.P, BestGenJet, -1);

      if(BestGenJet[0] > 0 && BestL1TkJetGen.P[0] > 0)
         HTkJet.Fill(BestL1TkJetGen.P, BestGenJet, -1);
      if(BestGenJet[0] > 0)
         HTkJetNoMatching.Fill(BestL1TkJetGen.P, BestGenJet, -1);
   }

   // Write result to file
   HEG.Write(EGDirectory);
   HEGNoMatching.Write(EGDirectory);
   HTkEG.Write(TkEGDirectory);
   HTkEGNoMatching.Write(TkEGDirectory);
   HTkEM.Write(TkEMDirectory);
   HTkEMNoMatching.Write(TkEMDirectory);
   HEGCrystal.Write(EGCrystalDirectory);
   HEGCrystalNoMatching.Write(EGCrystalDirectory);
   HTkEGCrystal.Write(TkEGCrystalDirectory);
   HTkEGCrystalNoMatching.Write(TkEGCrystalDirectory);
   HTkEMCrystal.Write(TkEMCrystalDirectory);
   HTkEMCrystalNoMatching.Write(TkEMCrystalDirectory);
   HJet.Write(JetDirectory);
   HJetNoMatching.Write(JetDirectory);
   HTkJet.Write(TkJetDirectory);
   HTkJetNoMatching.Write(TkJetDirectory);

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

GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference)
{
   GenericObject Best;
   Best.P = FourVector(-1, 0, 0, 0);
   Best.Iso = -1;
   for(int i = 0; i < (int)List.size(); i++)
      if(GetDR(List[i].P, Reference) <= 0.5)
         if(Best.P.GetPT() < List[i].P.GetPT())
            Best = List[i];
   return Best;
}














