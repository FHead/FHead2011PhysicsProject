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

   // Output File and Tree
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("T", "T");

   int Run, Event, Lumi;
   double GenE, GenPT, GenEta, GenPhi;
   double L1E, L1PT, L1Eta, L1Phi;

   OutputTree.Branch("Run", &Run, "Run/I");
   OutputTree.Branch("Event", &Event, "Event/I");
   OutputTree.Branch("Lumi", &Lumi, "Lumi/I");
   OutputTree.Branch("GenE", &GenE, "GenE/D");
   OutputTree.Branch("GenPT", &GenPT, "GenPT/D");
   OutputTree.Branch("GenEta", &GenEta, "GenEta/D");
   OutputTree.Branch("GenPhi", &GenPhi, "GenPhi/D");
   OutputTree.Branch("L1E", &L1E, "L1E/D");
   OutputTree.Branch("L1PT", &L1PT, "L1PT/D");
   OutputTree.Branch("L1Eta", &L1Eta, "L1Eta/D");
   OutputTree.Branch("L1Phi", &L1Phi, "L1Phi/D");

   // Loop over events
   int EntryCount = ML1.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      ML1.GetEntry(iE);
      MExtra.GetEntry(iE);

      Run = ML1.Event->run;
      Event = ML1.Event->event;
      Lumi = ML1.Event->lumi;

      vector<FourVector> Electrons;

      // Collect gen-particles
      for(int i = 0; i < (int)ML1.GenP.size(); i++)
      {
         int AbsID = ML1.GenID[i];
         if(AbsID < 0)
            AbsID = -AbsID;

         if(AbsID == 11)
            Electrons.push_back(ML1.GenP[i]);
      }

      // Best PT electron that's within our acceptance
      FourVector BestElectron = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)Electrons.size(); i++)
         if(Electrons[i].GetAbsEta() < 2.4)
            if(BestElectron.GetPT() < Electrons[i].GetPT())
               BestElectron = Electrons[i];

      // Best L1EGEle
      FourVector BestL1EGEle = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.EG.size(); i++)
         if(GetDR(MExtra.EG[i].P, BestElectron) <= 0.5)
            if(BestL1EGEle.GetPT() < MExtra.EG[i].P.GetPT())
               BestL1EGEle = MExtra.EG[i].P;

      // Fill tree
      GenE   = BestElectron[0];
      GenPT  = BestElectron.GetPT();
      GenEta = BestElectron.GetEta();
      GenPhi = BestElectron.GetPhi();
      L1E    = BestL1EGEle[0];
      L1PT   = BestL1EGEle.GetPT();
      L1Eta  = BestL1EGEle.GetEta();
      L1Phi  = BestL1EGEle.GetPhi();

      if(GenE > 0)
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
















