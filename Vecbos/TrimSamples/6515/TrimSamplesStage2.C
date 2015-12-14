#include <string>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

void TrimSamplesStage2(string Input = "Samples/ZJetsAll.root", string Output = "TrimmedStage2.root",
   string TreeName = "outTree")
{
   TFile In(Input.c_str());

   TTree *Tree = (TTree *)In.Get(TreeName.c_str());

   TFile Out(Output.c_str(), "RECREATE");

   TTree NewTree("outTree", "outTree");

   double ZMass;
   int NCaloJet;
   int NCaloJet30;
   int NPFJet;
   int NPFJet20;
   int NUncorrectedCaloJet;
   int NUncorrectedCaloJet20;
   int NTrackJet;
   int NTrackJet20;
   double Muon1CombinedIsolation;
   double Muon2CombinedIsolation;
   double Muon1PT;
   double Muon2PT;

   Tree->SetBranchAddress("ZMass", &ZMass);
   Tree->SetBranchAddress("NCaloJet", &NCaloJet);
   Tree->SetBranchAddress("NCaloJet30", &NCaloJet30);
   Tree->SetBranchAddress("NPFJet", &NPFJet);
   Tree->SetBranchAddress("NPFJet20", &NPFJet20);
   Tree->SetBranchAddress("NUncorrectedCaloJet", &NUncorrectedCaloJet);
   Tree->SetBranchAddress("NUncorrectedCaloJet20", &NUncorrectedCaloJet20);
   Tree->SetBranchAddress("NTrackJet", &NTrackJet);
   Tree->SetBranchAddress("NTrackJet20", &NTrackJet20);
   Tree->SetBranchAddress("Muon1CombinedIsolation", &Muon1CombinedIsolation);
   Tree->SetBranchAddress("Muon2CombinedIsolation", &Muon2CombinedIsolation);
   Tree->SetBranchAddress("Muon1PT", &Muon1PT);
   Tree->SetBranchAddress("Muon2PT", &Muon2PT);

   NewTree.Branch("ZMass", &ZMass, "ZMass/D");
   NewTree.Branch("NCaloJet", &NCaloJet, "NCaloJet/I");
   NewTree.Branch("NCaloJet30", &NCaloJet30, "NCaloJet30/I");
   NewTree.Branch("NPFJet", &NPFJet, "NPFJet/I");
   NewTree.Branch("NPFJet20", &NPFJet20, "NPFJet20/I");
   NewTree.Branch("NUncorrectedCaloJet", &NUncorrectedCaloJet, "NUncorrectedCaloJet/I");
   NewTree.Branch("NUncorrectedCaloJet20", &NUncorrectedCaloJet20, "NUncorrectedCaloJet20/I");
   NewTree.Branch("NTrackJet", &NTrackJet, "NTrackJet/I");
   NewTree.Branch("NTrackJet20", &NTrackJet20, "NTrackJet20/I");
   NewTree.Branch("Muon1CombinedIsolation", &Muon1CombinedIsolation, "Muon1CombinedIsolation/D");
   NewTree.Branch("Muon2CombinedIsolation", &Muon2CombinedIsolation, "Muon2CombinedIsolation/D");
   NewTree.Branch("Muon1PT", &Muon1PT, "Muon1PT/D");
   NewTree.Branch("Muon2PT", &Muon2PT, "Muon2PT/D");

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      if(i % 5000 == 0)
         cout << "Processing entry #" << i << "/" << EntryCount << endl;

      Tree->GetEntry(i);
      NewTree.Fill();
   }

   NewTree.Write();

   Out.Close();

   In.Close();
}

