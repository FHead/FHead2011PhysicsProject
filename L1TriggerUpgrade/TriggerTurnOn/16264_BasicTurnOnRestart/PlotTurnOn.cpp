#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TDirectory.h"

#include "Code/TauHelperFunctions3.h"

#include "Messenger.h"

#include "Histograms.h"

int main(int argc, char *argv[])
{
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
   TDirectory *TkIsoEGDirectory = OutputFile.mkdir("TkIsoEG", "tkIsoEG!");
   TDirectory *JetDirectory     = OutputFile.mkdir("TkJet", "Histograms for tk jets");

   // Create histograms
   vector<double> TkEGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkEG(25, 0, 50, 30, -3, 3, TkEGThresholds, "TkEG");
   Histograms HTkEGNoMatching(25, 0, 50, 30, -3, 3, TkEGThresholds, "TkEGNoMatching");
   
   vector<double> TkIsoEGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms HTkIsoEG(25, 0, 50, 30, -3, 3, TkIsoEGThresholds, "TkIsoEG");
   Histograms HTkIsoEGNoMatching(25, 0, 50, 30, -3, 3, TkIsoEGThresholds, "TkIsoEGNoMatching");

   vector<double> TkJetThresholds = ToVector(9, 0, 25, 50, 75, 100, 150, 200, 250, 300);
   Histograms HTkJet(100, 0, 1000, 50, -5, 5, TkJetThresholds, "TkJet");
   Histograms HTkJetNoMatching(100, 0, 1000, 50, -5, 5, TkJetThresholds, "TkJetNoMatching");

   // Loop over events
   int EntryCount = ML1.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      ML1.GetEntry(iE);
      MExtra.GetEntry(iE);

      vector<FourVector> Partons;
      vector<FourVector> Electrons;

      // Collect gen-particles
      for(int i = 0; i < (int)ML1.GenP.size(); i++)
      {
         if(ML1.GenStatus[i] != 3)   // we only want final state particles here (Pythia6)
            continue;

         if((abs(ML1.GenID[i]) >= 1 && abs(ML1.GenID[i]) <= 5) || abs(ML1.GenID[i]) == 21)
            Partons.push_back(ML1.GenP[i]);
         if(abs(ML1.GenID[i]) == 11)
            Electrons.push_back(ML1.GenP[i]);
      }

      // Best PT parton
      FourVector BestParton = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)Partons.size(); i++)
         if(BestParton.GetPT() < Partons[i].GetPT())
            BestParton = Partons[i];

      // Best PT electron that's within our acceptance
      FourVector BestElectron = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)Electrons.size(); i++)
         if(Electrons[i].GetAbsEta() < 2.4)
            if(BestElectron.GetPT() < Electrons[i].GetPT())
               BestElectron = Electrons[i];

      // Best L1TkJet
      FourVector BestL1TkJet = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkJet.size(); i++)
         if(GetDR(MExtra.TkJet[i].P, BestParton) <= 0.5)
            if(BestL1TkJet.GetPT() < MExtra.TkJet[i].P.GetPT())
               BestL1TkJet = MExtra.TkJet[i].P;

      // Best L1TkEG
      FourVector BestL1TkEG = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkEG.size(); i++)
         if(GetDR(MExtra.TkEG[i].P, BestParton) <= 0.5)
            if(BestL1TkEG.GetPT() < MExtra.TkEG[i].P.GetPT())
               BestL1TkEG = MExtra.TkEG[i].P;

      // Best L1TkIsoEG
      FourVector BestL1TkIsoEG = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkIsoEG.size(); i++)
         if(GetDR(MExtra.TkIsoEG[i].P, BestParton) <= 0.5)
            if(BestL1TkIsoEG.GetPT() < MExtra.TkIsoEG[i].P.GetPT())
               BestL1TkIsoEG = MExtra.TkIsoEG[i].P;

      // Fill Histograms
      if(BestElectron[0] > 0 && BestL1TkEG[0] > 0)
         HTkEG.Fill(BestL1TkEG.GetPT(), BestElectron.GetPT(), BestElectron.GetEta());
      if(BestElectron[0] > 0)
         HTkEGNoMatching.Fill(BestL1TkEG.GetPT(), BestElectron.GetPT(), BestElectron.GetEta());
      
      if(BestElectron[0] > 0 && BestL1TkIsoEG[0] > 0)
         HTkIsoEG.Fill(BestL1TkIsoEG.GetPT(), BestElectron.GetPT(), BestElectron.GetEta());
      if(BestElectron[0] > 0)
         HTkIsoEGNoMatching.Fill(BestL1TkIsoEG.GetPT(), BestElectron.GetPT(), BestElectron.GetEta());
      
      if(BestParton[0] > 0 && BestL1TkJet[0] > 0)
         HTkJet.Fill(BestL1TkJet.GetPT(), BestParton.GetPT(), BestParton.GetEta());
      if(BestParton[0] > 0)
         HTkJetNoMatching.Fill(BestL1TkJet.GetPT(), BestParton.GetPT(), BestParton.GetEta());
   }

   // Write result to file
   HTkEG.Write(TkEGDirectory);
   HTkEGNoMatching.Write(TkEGDirectory);
   HTkIsoEG.Write(TkIsoEGDirectory);
   HTkIsoEGNoMatching.Write(TkIsoEGDirectory);
   HTkJet.Write(JetDirectory);
   HTkJetNoMatching.Write(JetDirectory);

   // Clean up
   OutputFile.Close();

   File.Close();

   // Yay
   return 0;
}
















