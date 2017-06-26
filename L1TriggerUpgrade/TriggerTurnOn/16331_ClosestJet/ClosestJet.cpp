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

   double PartonPT, PartonEta, PartonPhi;
   double JetPT, JetEta, JetPhi;
   double BestDR;

   OutputTree.Branch("PartonPT", &PartonPT, "PartonPT/D");
   OutputTree.Branch("PartonEta", &PartonEta, "PartonEta/D");
   OutputTree.Branch("PartonPhi", &PartonPhi, "PartonPhi/D");
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

      vector<FourVector> Partons;
      vector<FourVector> Electrons;
      vector<FourVector> Photons;

      // Collect gen-particles
      for(int i = 0; i < (int)ML1.GenP.size(); i++)
      {
         if(ML1.GenStatus[i] != 3)   // only look at the "reference" particles....?
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

      // Best L1TkJet
      FourVector BestL1TkJet = FourVector(-1, 0, 0, 0);
      BestDR = -1;
      for(int i = 0; i < (int)MExtra.TkJet.size(); i++)
      {
         double DR = GetDR(MExtra.TkJet[i].P, BestParton);
         if(BestDR < 0 || DR < BestDR)
         {
            BestL1TkJet = MExtra.TkJet[i].P;
            BestDR = DR;
         }
      }

      // Profit!
      PartonPT = BestParton.GetPT();
      PartonEta = BestParton.GetEta();
      PartonPhi = BestParton.GetPhi();
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
















