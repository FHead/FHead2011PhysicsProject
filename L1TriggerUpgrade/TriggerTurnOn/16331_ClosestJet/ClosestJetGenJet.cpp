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

   TTree OutputTree("T", "T");

   double GenJetPT, GenJetEta, GenJetPhi;
   double JetPT, JetEta, JetPhi;
   double BestDR;

   OutputTree.Branch("GenJetPT", &GenJetPT, "GenJetPT/D");
   OutputTree.Branch("GenJetEta", &GenJetEta, "GenJetEta/D");
   OutputTree.Branch("GenJetPhi", &GenJetPhi, "GenJetPhi/D");
   OutputTree.Branch("JetPT", &JetPT, "JetPT/D");
   OutputTree.Branch("JetEta", &JetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &JetPhi, "JetPhi/D");
   OutputTree.Branch("BestDR", &BestDR, "BestDR/D");

   // Loop over events
   int EntryCount = ML1.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      ML1.GetEntry(iE);
      MExtra.GetEntry(iE);

      // Cluster all final state particles into gen-jets
      vector<fastjet::PseudoJet> FinalParticles;
      for(int i = 0; i < (int)ML1.GenP.size(); i++)
      {
         if(ML1.GenStatus[i] != 1)
            continue;

         int AbsID = ML1.GenID[i];
         if(AbsID < 0)
            AbsID = -AbsID;

         if(AbsID == 12 || AbsID == 14 || AbsID == 16)   // neutrinos - ignore
            continue;

         FourVector &P = ML1.GenP[i];
         FinalParticles.push_back(fastjet::PseudoJet(P[1], P[2], P[3], P[0]));
      }
      fastjet::JetDefinition Definition(fastjet::antikt_algorithm, 0.4);
      fastjet::ClusterSequence Sequence(FinalParticles, Definition);
      vector<fastjet::PseudoJet> Jets = Sequence.inclusive_jets();

      vector<FourVector> GenJets;
      for(int i = 0; i < (int)Jets.size(); i++)
         GenJets.push_back(FourVector(Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()));

      // Best PT gen-jet
      FourVector BestGenJet = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)GenJets.size(); i++)
         if(GenJets[i].GetAbsEta() < 3)
            if(BestGenJet.GetPT() < GenJets[i].GetPT())
               BestGenJet = GenJets[i];

      // Best L1TkJet
      FourVector BestL1TkJet = FourVector(-1, 0, 0, 0);
      BestDR = -1;
      for(int i = 0; i < (int)MExtra.TkJet.size(); i++)
      {
         double DR = GetDR(MExtra.TkJet[i].P, BestGenJet);
         if(BestDR < 0 || DR < BestDR)
         {
            BestL1TkJet = MExtra.TkJet[i].P;
            BestDR = DR;
         }
      }

      // Profit!
      GenJetPT = BestGenJet.GetPT();
      GenJetEta = BestGenJet.GetEta();
      GenJetPhi = BestGenJet.GetPhi();
      JetPT = BestL1TkJet.GetPT();
      JetEta = BestL1TkJet.GetEta();
      JetPhi = BestL1TkJet.GetPhi();
      
      OutputTree.Fill();
   }

   // Write result to file
   OutputTree.Write();

   // Clean up
   OutputFile.Close();

   File.Close();

   // Yay
   return 0;
}
















