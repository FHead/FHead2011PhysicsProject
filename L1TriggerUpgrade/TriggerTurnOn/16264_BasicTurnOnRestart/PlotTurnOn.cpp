#include <iostream>
#include <vector>
using namespace std;

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

   TDirectory *TkEGDirectory    = OutputFile.mkdir("TkEG", "Histograms for tkEG plots");
   TDirectory *TkEG2Directory   = OutputFile.mkdir("TkEG2", "Histograms for tkEG2 plots");
   TDirectory *TkIsoEGDirectory = OutputFile.mkdir("TkIsoEG", "tkIsoEG!");
   TDirectory *TkEMDirectory    = OutputFile.mkdir("TkEM", "Histograms for tkEM plots");
   TDirectory *JetDirectory     = OutputFile.mkdir("Jet", "Histograms for jets");
   TDirectory *TkJetDirectory   = OutputFile.mkdir("TkJet", "Histograms for tk jets");

   // Create histograms
   vector<double> TkEGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkEG(75, 0, 150, 30, -2.4, 2.4, TkEGThresholds, "TkEG");
   Histograms HTkEGNoMatching(75, 0, 150, 30, -2.4, 2.4, TkEGThresholds, "TkEGNoMatching");
   Histograms HTkEGFirst(75, 0, 150, 30, -2.4, 2.4, TkEGThresholds, "TkEGFirst");

   vector<double> TkEG2Thresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkEG2(75, 0, 150, 30, -2.4, 2.4, TkEG2Thresholds, "TkEG2");
   Histograms HTkEG2NoMatching(75, 0, 150, 30, -2.4, 2.4, TkEG2Thresholds, "TkEG2NoMatching");
   Histograms HTkEG2First(75, 0, 150, 30, -2.4, 2.4, TkEG2Thresholds, "TkEG2First");

   vector<double> TkIsoEGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkIsoEG(75, 0, 150, 30, -2.4, 2.4, TkIsoEGThresholds, "TkIsoEG");
   Histograms HTkIsoEGNoMatching(75, 0, 150, 30, -2.4, 2.4, TkIsoEGThresholds, "TkIsoEGNoMatching");
   Histograms HTkIsoEGFirst(75, 0, 150, 30, -2.4, 2.4, TkIsoEGThresholds, "TkIsoEGFirst");

   vector<double> TkEMThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkEM(75, 0, 150, 30, -2.4, 2.4, TkEMThresholds, "TkEM");
   Histograms HTkEMNoMatching(75, 0, 150, 30, -2.4, 2.4, TkEMThresholds, "TkEMNoMatching");
   Histograms HTkEMFirst(75, 0, 150, 30, -2.4, 2.4, TkEMThresholds, "TkEMFirst");

   vector<double> JetThresholds = ToVector(9, 0, 25, 50, 75, 100, 150, 200, 250, 300);
   Histograms HJet(100, 0, 1000, 50, -5, 5, JetThresholds, "Jet");
   Histograms HJetNoMatching(100, 0, 1000, 50, -3, 3, JetThresholds, "JetNoMatching");
   Histograms HJetFirst(100, 0, 1000, 50, -3, 3, JetThresholds, "JetFirst");

   vector<double> TkJetThresholds = ToVector(9, 0, 25, 50, 75, 100, 150, 200, 250, 300);
   Histograms HTkJet(100, 0, 1000, 50, -5, 5, TkJetThresholds, "TkJet");
   Histograms HTkJetNoMatching(100, 0, 1000, 50, -3, 3, TkJetThresholds, "TkJetNoMatching");
   Histograms HTkJetFirst(100, 0, 1000, 50, -3, 3, TkJetThresholds, "TkJetFirst");

   // Loop over events
   int EntryCount = ML1.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      ML1.GetEntry(iE);
      MExtra.GetEntry(iE);

      vector<FourVector> Partons;
      vector<FourVector> Electrons;
      vector<FourVector> Photons;

      // Collect gen-particles
      for(int i = 0; i < (int)ML1.GenP.size(); i++)
      {
         if(ML1.GenStatus[i] != 3)   // we only want final state particles here (Pythia6)
            continue;

         int AbsID = ML1.GenID[i];
         if(AbsID < 0)
            AbsID = -AbsID;

         if((AbsID >= 1 && AbsID <= 5) || AbsID == 21)
            Partons.push_back(ML1.GenP[i]);
         if(AbsID == 11)
            Electrons.push_back(ML1.GenP[i]);
         if(AbsID == 22)
            Photons.push_back(ML1.GenP[i]);
      }

      // Best PT parton
      FourVector BestParton = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)Partons.size(); i++)
         if(Partons[i].GetAbsEta() < 3)
            if(BestParton.GetPT() < Partons[i].GetPT())
               BestParton = Partons[i];

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

      // Best L1TkEG
      FourVector FirstL1TkEG = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkEG = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkEG.size(); i++)
      {
         if(GetDR(MExtra.TkEG[i].P, BestElectron) <= 0.5)
         {
            if(i == 0 && FirstL1TkEG.GetPT() < MExtra.TkEG[i].P.GetPT())
               FirstL1TkEG = MExtra.TkEG[i].P;
            if(BestL1TkEG.GetPT() < MExtra.TkEG[i].P.GetPT())
               BestL1TkEG = MExtra.TkEG[i].P;
         }
      }

      // Best L1TkEG2
      FourVector FirstL1TkEG2 = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkEG2 = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkEG2.size(); i++)
      {
         if(GetDR(MExtra.TkEG2[i].P, BestElectron) <= 0.5)
         {
            if(i == 0 && FirstL1TkEG2.GetPT() < MExtra.TkEG2[i].P.GetPT())
               FirstL1TkEG2 = MExtra.TkEG2[i].P;
            if(BestL1TkEG2.GetPT() < MExtra.TkEG2[i].P.GetPT())
               BestL1TkEG2 = MExtra.TkEG2[i].P;
         }
      }

      // Best L1TkIsoEG
      FourVector FirstL1TkIsoEG = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkIsoEG = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkIsoEG.size(); i++)
      {
         if(GetDR(MExtra.TkIsoEG[i].P, BestElectron) <= 0.5)
         {
            if(i == 0 && FirstL1TkIsoEG.GetPT() < MExtra.TkIsoEG[i].P.GetPT())
               FirstL1TkIsoEG = MExtra.TkIsoEG[i].P;
            if(BestL1TkIsoEG.GetPT() < MExtra.TkIsoEG[i].P.GetPT())
               BestL1TkIsoEG = MExtra.TkIsoEG[i].P;
         }
      }

      // Best L1TkEM
      FourVector FirstL1TkEM = FourVector(-1, 0, 0, 0);
      FourVector BestL1TkEM = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkEM.size(); i++)
      {
         if(GetDR(MExtra.TkEM[i].P, BestPhoton) <= 0.5)
         {
            if(i == 0 && FirstL1TkEM.GetPT() < MExtra.TkEM[i].P.GetPT())
               FirstL1TkEM = MExtra.TkEM[i].P;
            if(BestL1TkEM.GetPT() < MExtra.TkEM[i].P.GetPT())
               BestL1TkEM = MExtra.TkEM[i].P;
         }
      }

      // Fill Histograms
      if(BestElectron[0] > 0 && BestL1TkEG[0] > 0)
         HTkEG.Fill(BestL1TkEG, BestElectron);
      if(BestElectron[0] > 0)
         HTkEGNoMatching.Fill(FirstL1TkEG, BestElectron);
      if(BestElectron[0] > 0 && FirstL1TkEG[0] > 0)
         HTkEGFirst.Fill(FirstL1TkEG, BestElectron);

      if(BestElectron[0] > 0 && BestL1TkEG2[0] > 0)
         HTkEG2.Fill(BestL1TkEG2, BestElectron);
      if(BestElectron[0] > 0)
         HTkEG2NoMatching.Fill(FirstL1TkEG2, BestElectron);
      if(BestElectron[0] > 0 && FirstL1TkEG2[0] > 0)
         HTkEG2First.Fill(FirstL1TkEG2, BestElectron);

      if(BestElectron[0] > 0 && BestL1TkIsoEG[0] > 0)
         HTkIsoEG.Fill(BestL1TkIsoEG, BestElectron);
      if(BestElectron[0] > 0)
         HTkIsoEGNoMatching.Fill(FirstL1TkIsoEG, BestElectron);
      if(BestElectron[0] > 0 && FirstL1TkIsoEG[0] > 0)
         HTkIsoEGFirst.Fill(FirstL1TkIsoEG, BestElectron);

      if(BestPhoton[0] > 0 && BestL1TkEM[0] > 0)
         HTkEM.Fill(BestL1TkEM, BestPhoton);
      if(BestPhoton[0] > 0)
         HTkEMNoMatching.Fill(FirstL1TkEM, BestPhoton);
      if(BestPhoton[0] > 0 && FirstL1TkEM[0] > 0)
         HTkEMFirst.Fill(FirstL1TkEM, BestPhoton);

      if(BestParton[0] > 0 && BestL1Jet[0] > 0)
         HJet.Fill(BestL1Jet, BestParton);
      if(BestParton[0] > 0)
         HJetNoMatching.Fill(FirstL1Jet, BestParton);
      if(BestParton[0] > 0 && FirstL1Jet[0] > 0)
         HJetFirst.Fill(FirstL1Jet, BestParton);

      if(BestParton[0] > 0 && BestL1TkJet[0] > 0)
         HTkJet.Fill(BestL1TkJet, BestParton);
      if(BestParton[0] > 0)
         HTkJetNoMatching.Fill(FirstL1TkJet, BestParton);
      if(BestParton[0] > 0 && FirstL1TkJet[0] > 0)
         HTkJetFirst.Fill(FirstL1TkJet, BestParton);
   }

   // Write result to file
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

   // Clean up
   OutputFile.Close();

   File.Close();

   // Yay
   return 0;
}
















