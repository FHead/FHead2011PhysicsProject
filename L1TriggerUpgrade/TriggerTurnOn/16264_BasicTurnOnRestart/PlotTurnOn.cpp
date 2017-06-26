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

#include "Messenger.h"

#include "Histograms.h"

int main(int argc, char *argv[])
{
   // Some root styling
   SetThesisStyle();

   // Print usage
   if(argc != 3 || (argc > 1 && string(argv[1]) == "-h"))
   {
      cerr << "Usage: " << argv[0] << " Input Output" << endl;
      return -1;
   }

   // Get arguments
   string InputFileName = "Samples/WToENu200PU/WToENu_99.root";
   string OutputFileName = "OutputHistograms.root";

   InputFileName = argv[1];
   OutputFileName = argv[2];

   // Input File
   TFile File(InputFileName.c_str());

   // Messengers
   L1NTupleMessenger ML1(File, "l1NtupleProducer/L1Tree");
   L1ExtraUpgradeTreeMessenger MExtra(File, "l1ExtraUpgradeTreeProducer/L1ExtraUpgradeTree");

   if(ML1.Tree == NULL)
      return -1;

   // Output File and directories for better organization
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TDirectory *EGDirectory       = OutputFile.mkdir("EG",       "Histograms for EG plots (Photon)");
   TDirectory *EGEleDirectory    = OutputFile.mkdir("EGEle",    "Histograms for EG plots (Electron)");
   TDirectory *IsoEGDirectory    = OutputFile.mkdir("IsoEG",    "Histograms for IsoEG plots (Photon)");
   TDirectory *IsoEGEleDirectory = OutputFile.mkdir("IsoEGEle", "Histograms for IsoEG plots (Electron)");
   TDirectory *TkEGDirectory     = OutputFile.mkdir("TkEG",     "Histograms for tkEG plots (Electron)");
   TDirectory *TkEG2Directory    = OutputFile.mkdir("TkEG2",    "Histograms for tkEG2 plots (Electron)");
   TDirectory *TkIsoEGDirectory  = OutputFile.mkdir("TkIsoEG",  "tkIsoEG! (Electron)");
   TDirectory *TkEMDirectory     = OutputFile.mkdir("TkEM",     "Histograms for tkEM plots (Photon)");
   TDirectory *JetDirectory      = OutputFile.mkdir("Jet",      "Histograms for jets (Parton)");
   TDirectory *TkJetDirectory    = OutputFile.mkdir("TkJet",    "Histograms for tk jets (Parton)");
   TDirectory *JetGenDirectory   = OutputFile.mkdir("JetGen",   "Histograms for Jets (gen jet)");
   TDirectory *TkJetGenDirectory = OutputFile.mkdir("TkJetGen", "Histograms for tk Jets (gen jet)");

   // Create histograms
   vector<double> EGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HEG(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, EGThresholds, "EG");
   Histograms HEGNoMatching(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, EGThresholds, "EGNoMatching");
   Histograms HEGFirst(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, EGThresholds, "EGFirst");

   vector<double> EGEleThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HEGEle(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, EGEleThresholds, "EGEle");
   Histograms HEGEleNoMatching(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, EGEleThresholds, "EGEleNoMatching");
   Histograms HEGEleFirst(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, EGEleThresholds, "EGEleFirst");

   vector<double> IsoEGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HIsoEG(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, IsoEGThresholds, "IsoEG");
   Histograms HIsoEGNoMatching(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, IsoEGThresholds, "IsoEGNoMatching");
   Histograms HIsoEGFirst(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, IsoEGThresholds, "IsoEGFirst");

   vector<double> IsoEGEleThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HIsoEGEle(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, IsoEGEleThresholds, "IsoEGEle");
   Histograms HIsoEGEleNoMatching(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, IsoEGEleThresholds, "IsoEGEleNoMatching");
   Histograms HIsoEGEleFirst(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, IsoEGEleThresholds, "IsoEGEleFirst");

   vector<double> TkEGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkEG(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkEGThresholds, "TkEG");
   Histograms HTkEGNoMatching(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkEGThresholds, "TkEGNoMatching");
   Histograms HTkEGFirst(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkEGThresholds, "TkEGFirst");

   vector<double> TkEG2Thresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkEG2(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkEG2Thresholds, "TkEG2");
   Histograms HTkEG2NoMatching(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkEG2Thresholds, "TkEG2NoMatching");
   Histograms HTkEG2First(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkEG2Thresholds, "TkEG2First");

   vector<double> TkIsoEGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkIsoEG(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkIsoEGThresholds, "TkIsoEG");
   Histograms HTkIsoEGNoMatching(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkIsoEGThresholds, "TkIsoEGNoMatching");
   Histograms HTkIsoEGFirst(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkIsoEGThresholds, "TkIsoEGFirst");

   vector<double> TkEMThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkEM(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkEMThresholds, "TkEM");
   Histograms HTkEMNoMatching(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkEMThresholds, "TkEMNoMatching");
   Histograms HTkEMFirst(75, 0, 150, 30, -2.4, 2.4,  2000, 0, 5, TkEMThresholds, "TkEMFirst");

   vector<double> JetThresholds = ToVector(9, 0, 25, 50, 75, 100, 150, 200, 250, 300);
   Histograms HJet(500, 0, 1000, 50, -3, 3,  2000, 0, 5, JetThresholds, "Jet");
   Histograms HJetNoMatching(500, 0, 1000, 50, -3, 3,  2000, 0, 5, JetThresholds, "JetNoMatching");
   Histograms HJetFirst(500, 0, 1000, 50, -3, 3,  2000, 0, 5, JetThresholds, "JetFirst");

   vector<double> TkJetThresholds = ToVector(9, 0, 25, 50, 75, 100, 150, 200, 250, 300);
   Histograms HTkJet(500, 0, 1000, 50, -3, 3,  2000, 0, 5, TkJetThresholds, "TkJet");
   Histograms HTkJetNoMatching(500, 0, 1000, 50, -3, 3,  2000, 0, 5, TkJetThresholds, "TkJetNoMatching");
   Histograms HTkJetFirst(500, 0, 1000, 50, -3, 3,  2000, 0, 5, TkJetThresholds, "TkJetFirst");

   vector<double> JetGenThresholds = ToVector(9, 0, 25, 50, 75, 100, 150, 200, 250, 300);
   Histograms HJetGen(500, 0, 1000, 50, -3, 3,  2000, 0, 5, JetGenThresholds, "JetGen");
   Histograms HJetGenNoMatching(500, 0, 1000, 50, -3, 3,  2000, 0, 5, JetGenThresholds, "JetGenNoMatching");
   Histograms HJetGenFirst(500, 0, 1000, 50, -3, 3,  2000, 0, 5, JetGenThresholds, "JetGenFirst");

   vector<double> TkJetGenThresholds = ToVector(9, 0, 25, 50, 75, 100, 150, 200, 250, 300);
   Histograms HTkJetGen(500, 0, 1000, 50, -3, 3,  2000, 0, 5, TkJetGenThresholds, "TkJetGen");
   Histograms HTkJetGenNoMatching(500, 0, 1000, 50, -3, 3,  2000, 0, 5, TkJetGenThresholds, "TkJetGenNoMatching");
   Histograms HTkJetGenFirst(500, 0, 1000, 50, -3, 3, 2000, 0, 5, TkJetGenThresholds, "TkJetGenFirst");

   // Loop over events
   int EntryCount = ML1.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      ML1.GetEntry(iE);
      MExtra.GetEntry(iE);

      vector<FourVector> Partons;
      vector<FourVector> FinalPartons;
      vector<FourVector> Electrons;
      vector<FourVector> Photons;
      vector<FourVector> Particles;

      // Collect gen-particles
      for(int i = 0; i < (int)ML1.GenP.size(); i++)
      {
         int AbsID = ML1.GenID[i];
         if(AbsID < 0)
            AbsID = -AbsID;

         if(AbsID == 11)
            Electrons.push_back(ML1.GenP[i]);
         if(AbsID == 22)
            Photons.push_back(ML1.GenP[i]);

         if(ML1.GenStatus[i] == 1)   // we only want final state particles here (Pythia6)
         {
            if((AbsID >= 1 && AbsID <= 5) || AbsID == 21)
               FinalPartons.push_back(ML1.GenP[i]);
            Particles.push_back(ML1.GenP[i]);
         }
         if(ML1.GenStatus[i] == 3)   // Huh?
            if((AbsID >= 1 && AbsID <= 5) || AbsID == 21)
               Partons.push_back(ML1.GenP[i]);
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

      // Best PT parton
      FourVector BestParton = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)Partons.size(); i++)
         if(Partons[i].GetAbsEta() < 3)
            if(BestParton.GetPT() < Partons[i].GetPT())
               BestParton = Partons[i];

      // Best Gen Jet
      FourVector BestGenJet = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)GenJets.size(); i++)
         if(GenJets[i].GetAbsEta() < 3)
            if(BestGenJet.GetPT() < GenJets[i].GetPT())
               BestGenJet = GenJets[i];

      // Best PT electron that's within our acceptance
      FourVector BestElectron = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)Electrons.size(); i++)
         if(Electrons[i].GetAbsEta() < 2.4)
            if(BestElectron.GetPT() < Electrons[i].GetPT())
               BestElectron = Electrons[i];
      
      // Best photon
      FourVector BestPhoton = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)Photons.size(); i++)
         if(Photons[i].GetAbsEta() < 2.4)
            if(BestPhoton.GetPT() < Photons[i].GetPT())
               BestPhoton = Photons[i];

      // Best L1Jet
      FourVector FirstL1Jet = FourVector(-1, 0, 0, 0);
      FourVector BestL1Jet = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.Jet.size(); i++)
      {
         if(GetDR(MExtra.Jet[i].P, BestParton) <= 0.5)
         {
            if(i == 0 && FirstL1Jet.GetPT() < MExtra.Jet[i].P.GetPT())
               FirstL1Jet = MExtra.Jet[i].P;
            if(BestL1Jet.GetPT() < MExtra.Jet[i].P.GetPT())
               BestL1Jet = MExtra.Jet[i].P;
         }
      }

      // Best L1TkJet
      FourVector FirstL1TkJet = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkJet = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkJet.size(); i++)
      {
         if(GetDR(MExtra.TkJet[i].P, BestParton) <= 0.5)
         {
            if(i == 0 && FirstL1TkJet.GetPT() < MExtra.TkJet[i].P.GetPT())
               FirstL1TkJet = MExtra.TkJet[i].P;
            if(BestL1TkJet.GetPT() < MExtra.TkJet[i].P.GetPT())
               BestL1TkJet = MExtra.TkJet[i].P;
         }
      }

      // Best L1Jet - gen
      FourVector FirstL1JetGen = FourVector(-1, 0, 0, 0);
      FourVector BestL1JetGen = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.Jet.size(); i++)
      {
         if(GetDR(MExtra.Jet[i].P, BestGenJet) <= 0.5)
         {
            if(i == 0 && FirstL1JetGen.GetPT() < MExtra.Jet[i].P.GetPT())
               FirstL1JetGen = MExtra.Jet[i].P;
            if(BestL1JetGen.GetPT() < MExtra.Jet[i].P.GetPT())
               BestL1JetGen = MExtra.Jet[i].P;
         }
      }

      // Best L1TkJet - gen
      FourVector FirstL1TkJetGen = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkJetGen = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkJet.size(); i++)
      {
         if(GetDR(MExtra.TkJet[i].P, BestGenJet) <= 0.5)
         {
            if(i == 0 && FirstL1TkJetGen.GetPT() < MExtra.TkJet[i].P.GetPT())
               FirstL1TkJetGen = MExtra.TkJet[i].P;
            if(BestL1TkJetGen.GetPT() < MExtra.TkJet[i].P.GetPT())
               BestL1TkJetGen = MExtra.TkJet[i].P;
         }
      }

      // Best L1EG
      FourVector FirstL1EG = FourVector(-1, 0, 0, 0);
      FourVector BestL1EG = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.EG.size(); i++)
      {
         if(GetDR(MExtra.EG[i].P, BestPhoton) <= 0.5)
         {
            if(i == 0 && FirstL1EG.GetPT() < MExtra.EG[i].P.GetPT())
               FirstL1EG = MExtra.EG[i].P;
            if(BestL1EG.GetPT() < MExtra.EG[i].P.GetPT())
               BestL1EG = MExtra.EG[i].P;
         }
      }

      // Best L1EGEle
      FourVector FirstL1EGEle = FourVector(-1, 0, 0, 0);
      FourVector BestL1EGEle = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.EG.size(); i++)
      {
         if(GetDR(MExtra.EG[i].P, BestElectron) <= 0.5)
         {
            if(i == 0 && FirstL1EGEle.GetPT() < MExtra.EG[i].P.GetPT())
               FirstL1EGEle = MExtra.EG[i].P;
            if(BestL1EGEle.GetPT() < MExtra.EG[i].P.GetPT())
               BestL1EGEle = MExtra.EG[i].P;
         }
      }

      // Best L1IsoEG
      FourVector FirstL1IsoEG = FourVector(-1, 0, 0, 0);
      FourVector BestL1IsoEG = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.IsoEG.size(); i++)
      {
         if(GetDR(MExtra.IsoEG[i].P, BestPhoton) <= 0.5)
         {
            if(i == 0 && FirstL1IsoEG.GetPT() < MExtra.IsoEG[i].P.GetPT())
               FirstL1IsoEG = MExtra.IsoEG[i].P;
            if(BestL1IsoEG.GetPT() < MExtra.IsoEG[i].P.GetPT())
               BestL1IsoEG = MExtra.IsoEG[i].P;
         }
      }

      // Best L1IsoEGEle
      FourVector FirstL1IsoEGEle = FourVector(-1, 0, 0, 0);
      FourVector BestL1IsoEGEle = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.IsoEG.size(); i++)
      {
         if(GetDR(MExtra.IsoEG[i].P, BestElectron) <= 0.5)
         {
            if(i == 0 && FirstL1IsoEGEle.GetPT() < MExtra.IsoEG[i].P.GetPT())
               FirstL1IsoEGEle = MExtra.IsoEG[i].P;
            if(BestL1IsoEGEle.GetPT() < MExtra.IsoEG[i].P.GetPT())
               BestL1IsoEGEle = MExtra.IsoEG[i].P;
         }
      }

      // Best L1TkEG
      FourVector FirstL1TkEG = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkEG = FourVector(-1, 0, 0, 0);
      int BestL1TkEGIndex = 0;
      for(int i = 0; i < (int)MExtra.TkEG.size(); i++)
      {
         if(GetDR(MExtra.TkEG[i].P, BestElectron) <= 0.5)
         {
            if(i == 0 && FirstL1TkEG.GetPT() < MExtra.TkEG[i].P.GetPT())
               FirstL1TkEG = MExtra.TkEG[i].P;
            if(BestL1TkEG.GetPT() < MExtra.TkEG[i].P.GetPT())
               BestL1TkEG = MExtra.TkEG[i].P, BestL1TkEGIndex = i;
         }
      }

      // Best L1TkEG2
      FourVector FirstL1TkEG2 = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkEG2 = FourVector(-1, 0, 0, 0);
      int BestL1TkEG2Index = 0;
      for(int i = 0; i < (int)MExtra.TkEG2.size(); i++)
      {
         if(GetDR(MExtra.TkEG2[i].P, BestElectron) <= 0.5)
         {
            if(i == 0 && FirstL1TkEG2.GetPT() < MExtra.TkEG2[i].P.GetPT())
               FirstL1TkEG2 = MExtra.TkEG2[i].P;
            if(BestL1TkEG2.GetPT() < MExtra.TkEG2[i].P.GetPT())
               BestL1TkEG2 = MExtra.TkEG2[i].P, BestL1TkEG2Index = i;
         }
      }

      // Best L1TkIsoEG
      FourVector FirstL1TkIsoEG = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkIsoEG = FourVector(-1, 0, 0, 0);
      int BestL1TkIsoEGIndex = 0;
      for(int i = 0; i < (int)MExtra.TkIsoEG.size(); i++)
      {
         if(GetDR(MExtra.TkIsoEG[i].P, BestElectron) <= 0.5)
         {
            if(i == 0 && FirstL1TkIsoEG.GetPT() < MExtra.TkIsoEG[i].P.GetPT())
               FirstL1TkIsoEG = MExtra.TkIsoEG[i].P;
            if(BestL1TkIsoEG.GetPT() < MExtra.TkIsoEG[i].P.GetPT())
               BestL1TkIsoEG = MExtra.TkIsoEG[i].P, BestL1TkIsoEGIndex = i;
         }
      }

      // Best L1TkEM
      FourVector FirstL1TkEM = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkEM = FourVector(-1, 0, 0, 0);
      int BestL1TkEMIndex = 0;
      for(int i = 0; i < (int)MExtra.TkEM.size(); i++)
      {
         if(GetDR(MExtra.TkEM[i].P, BestPhoton) <= 0.5)
         {
            if(i == 0 && FirstL1TkEM.GetPT() < MExtra.TkEM[i].P.GetPT())
               FirstL1TkEM = MExtra.TkEM[i].P;
            if(BestL1TkEM.GetPT() < MExtra.TkEM[i].P.GetPT())
               BestL1TkEM = MExtra.TkEM[i].P, BestL1TkEMIndex = i;
         }
      }

      // Fill Histograms
      if(BestPhoton[0] > 0 && BestL1EG[0] > 0)
         HEG.Fill(BestL1EG, BestPhoton, -1);
      if(BestPhoton[0] > 0)
         HEGNoMatching.Fill(FirstL1EG, BestPhoton, -1);
      if(BestPhoton[0] > 0 && FirstL1EG[0] > 0)
         HEGFirst.Fill(FirstL1EG, BestPhoton, -1);

      if(BestElectron[0] > 0 && BestL1EGEle[0] > 0)
         HEGEle.Fill(BestL1EGEle, BestElectron, -1);
      if(BestElectron[0] > 0)
         HEGEleNoMatching.Fill(FirstL1EGEle, BestElectron, -1);
      if(BestElectron[0] > 0 && FirstL1EGEle[0] > 0)
         HEGEleFirst.Fill(FirstL1EGEle, BestElectron, -1);

      if(BestPhoton[0] > 0 && BestL1IsoEG[0] > 0)
         HIsoEG.Fill(BestL1IsoEG, BestPhoton, -1);
      if(BestPhoton[0] > 0)
         HIsoEGNoMatching.Fill(FirstL1IsoEG, BestPhoton, -1);
      if(BestPhoton[0] > 0 && FirstL1IsoEG[0] > 0)
         HIsoEGFirst.Fill(FirstL1IsoEG, BestPhoton, -1);

      if(BestElectron[0] > 0 && BestL1IsoEGEle[0] > 0)
         HIsoEGEle.Fill(BestL1IsoEGEle, BestPhoton, -1);
      if(BestElectron[0] > 0)
         HIsoEGEleNoMatching.Fill(FirstL1IsoEGEle, BestPhoton, -1);
      if(BestElectron[0] > 0 && FirstL1IsoEGEle[0] > 0)
         HIsoEGEleFirst.Fill(FirstL1IsoEGEle, BestPhoton, -1);

      if(BestElectron[0] > 0 && BestL1TkEG[0] > 0)
         HTkEG.Fill(BestL1TkEG, BestElectron, MExtra.TkEG[BestL1TkEGIndex].Iso);
      if(BestElectron[0] > 0)
         HTkEGNoMatching.Fill(FirstL1TkEG, BestElectron, (BestL1TkEG[0] > 0) ? MExtra.TkEG[BestL1TkEGIndex].Iso : -1);
      if(BestElectron[0] > 0 && FirstL1TkEG[0] > 0)
         HTkEGFirst.Fill(FirstL1TkEG, BestElectron, MExtra.TkEG[BestL1TkEGIndex].Iso);

      if(BestElectron[0] > 0 && BestL1TkEG2[0] > 0)
         HTkEG2.Fill(BestL1TkEG2, BestElectron, MExtra.TkEG2[BestL1TkEG2Index].Iso);
      if(BestElectron[0] > 0)
         HTkEG2NoMatching.Fill(FirstL1TkEG2, BestElectron, (BestL1TkEG2[0] > 0) ? MExtra.TkEG2[BestL1TkEG2Index].Iso : -1);
      if(BestElectron[0] > 0 && FirstL1TkEG2[0] > 0)
         HTkEG2First.Fill(FirstL1TkEG2, BestElectron, MExtra.TkEG2[BestL1TkEG2Index].Iso);

      if(BestElectron[0] > 0 && BestL1TkIsoEG[0] > 0)
         HTkIsoEG.Fill(BestL1TkIsoEG, BestElectron, MExtra.TkIsoEG[BestL1TkIsoEGIndex].Iso);
      if(BestElectron[0] > 0)
         HTkIsoEGNoMatching.Fill(FirstL1TkIsoEG, BestElectron, (BestL1TkIsoEG[0] > 0) ? MExtra.TkIsoEG[BestL1TkIsoEGIndex].Iso : -1);
      if(BestElectron[0] > 0 && FirstL1TkIsoEG[0] > 0)
         HTkIsoEGFirst.Fill(FirstL1TkIsoEG, BestElectron, MExtra.TkIsoEG[BestL1TkIsoEGIndex].Iso);

      if(BestPhoton[0] > 0 && BestL1TkEM[0] > 0)
         HTkEM.Fill(BestL1TkEM, BestPhoton, MExtra.TkEM[BestL1TkEMIndex].Iso);
      if(BestPhoton[0] > 0)
         HTkEMNoMatching.Fill(FirstL1TkEM, BestPhoton, (BestL1TkEM[0] > 0) ? MExtra.TkEM[BestL1TkEMIndex].Iso : -1);
      if(BestPhoton[0] > 0 && FirstL1TkEM[0] > 0)
         HTkEMFirst.Fill(FirstL1TkEM, BestPhoton, MExtra.TkEM[BestL1TkEMIndex].Iso);

      if(BestParton[0] > 0 && BestL1Jet[0] > 0)
         HJet.Fill(BestL1Jet, BestParton, -1);
      if(BestParton[0] > 0)
         HJetNoMatching.Fill(FirstL1Jet, BestParton, -1);
      if(BestParton[0] > 0 && FirstL1Jet[0] > 0)
         HJetFirst.Fill(FirstL1Jet, BestParton, -1);

      if(BestParton[0] > 0 && BestL1TkJet[0] > 0)
         HTkJet.Fill(BestL1TkJet, BestParton, -1);
      if(BestParton[0] > 0)
         HTkJetNoMatching.Fill(FirstL1TkJet, BestParton, -1);
      if(BestParton[0] > 0 && FirstL1TkJet[0] > 0)
         HTkJetFirst.Fill(FirstL1TkJet, BestParton, -1);

      if(BestGenJet[0] > 0 && BestL1JetGen[0] > 0)
         HJetGen.Fill(BestL1JetGen, BestGenJet, -1);
      if(BestGenJet[0] > 0)
         HJetGenNoMatching.Fill(FirstL1JetGen, BestGenJet, -1);
      if(BestGenJet[0] > 0 && FirstL1JetGen[0] > 0)
         HJetGenFirst.Fill(FirstL1JetGen, BestGenJet, -1);

      if(BestGenJet[0] > 0 && BestL1TkJetGen[0] > 0)
         HTkJetGen.Fill(BestL1TkJetGen, BestGenJet, -1);
      if(BestGenJet[0] > 0)
         HTkJetGenNoMatching.Fill(FirstL1TkJetGen, BestGenJet, -1);
      if(BestGenJet[0] > 0 && FirstL1TkJetGen[0] > 0)
         HTkJetGenFirst.Fill(FirstL1TkJetGen, BestGenJet, -1);
   }

   // Write result to file
   HEG.Write(EGDirectory);
   HEGNoMatching.Write(EGDirectory);
   HEGFirst.Write(EGDirectory);
   HEGEle.Write(EGEleDirectory);
   HEGEleNoMatching.Write(EGEleDirectory);
   HEGEleFirst.Write(EGEleDirectory);
   HIsoEG.Write(IsoEGDirectory);
   HIsoEGNoMatching.Write(IsoEGDirectory);
   HIsoEGFirst.Write(IsoEGDirectory);
   HIsoEGEle.Write(IsoEGEleDirectory);
   HIsoEGEleNoMatching.Write(IsoEGEleDirectory);
   HIsoEGEleFirst.Write(IsoEGEleDirectory);
   HTkEG.Write(TkEGDirectory);
   HTkEGNoMatching.Write(TkEGDirectory);
   HTkEGFirst.Write(TkEGDirectory);
   HTkEG2.Write(TkEG2Directory);
   HTkEG2NoMatching.Write(TkEG2Directory);
   HTkEG2First.Write(TkEG2Directory);
   HTkIsoEG.Write(TkIsoEGDirectory);
   HTkIsoEGNoMatching.Write(TkIsoEGDirectory);
   HTkIsoEGFirst.Write(TkIsoEGDirectory);
   HTkEM.Write(TkEMDirectory);
   HTkEMNoMatching.Write(TkEMDirectory);
   HTkEMFirst.Write(TkEMDirectory);
   HJet.Write(JetDirectory);
   HJetNoMatching.Write(JetDirectory);
   HJetFirst.Write(JetDirectory);
   HTkJet.Write(TkJetDirectory);
   HTkJetNoMatching.Write(TkJetDirectory);
   HTkJetFirst.Write(TkJetDirectory);
   HJetGen.Write(JetGenDirectory);
   HJetGenNoMatching.Write(JetGenDirectory);
   HJetGenFirst.Write(JetGenDirectory);
   HTkJetGen.Write(TkJetGenDirectory);
   HTkJetGenNoMatching.Write(TkJetGenDirectory);
   HTkJetGenFirst.Write(TkJetGenDirectory);

   // Clean up
   OutputFile.Close();

   File.Close();

   // Yay
   return 0;
}
















