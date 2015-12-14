#include <string>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

void TrimSamplesStage2(string Input = "Samples/DataAll.root", string Output = "DataAllTrimmedStage2.root",
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
   int NPFJet15;
   int NPFJet16;
   int NPFJet17;
   int NPFJet18;
   int NPFJet19;
   int NPFJet20;
   int NPFJet21;
   int NPFJet22;
   int NPFJet23;
   int NPFJet24;
   int NPFJet25;
   int NPFJet26;
   int NPFJet27;
   int NPFJet28;
   int NPFJet29;
   int NPFJet30;
   int NPFJet31;
   int NPFJet32;
   int NPFJet33;
   int NPFJet34;
   int NPFJet35;
   int NPFJet36;
   int NPFJet37;
   int NPFJet38;
   int NPFJet39;
   int NPFJet40;
   int NPFJet41;
   int NPFJet42;
   int NPFJet43;
   int NPFJet44;
   int NPFJet45;
   int NPFJet46;
   int NPFJet47;
   int NPFJet48;
   int NPFJet49;
   int NPFJet50;
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
   Tree->SetBranchAddress("NPFJet15", &NPFJet15);
   Tree->SetBranchAddress("NPFJet16", &NPFJet16);
   Tree->SetBranchAddress("NPFJet17", &NPFJet17);
   Tree->SetBranchAddress("NPFJet18", &NPFJet18);
   Tree->SetBranchAddress("NPFJet19", &NPFJet19);
   Tree->SetBranchAddress("NPFJet20", &NPFJet20);
   Tree->SetBranchAddress("NPFJet21", &NPFJet21);
   Tree->SetBranchAddress("NPFJet22", &NPFJet22);
   Tree->SetBranchAddress("NPFJet23", &NPFJet23);
   Tree->SetBranchAddress("NPFJet24", &NPFJet24);
   Tree->SetBranchAddress("NPFJet25", &NPFJet25);
   Tree->SetBranchAddress("NPFJet26", &NPFJet26);
   Tree->SetBranchAddress("NPFJet27", &NPFJet27);
   Tree->SetBranchAddress("NPFJet28", &NPFJet28);
   Tree->SetBranchAddress("NPFJet29", &NPFJet29);
   Tree->SetBranchAddress("NPFJet30", &NPFJet30);
   Tree->SetBranchAddress("NPFJet31", &NPFJet31);
   Tree->SetBranchAddress("NPFJet32", &NPFJet32);
   Tree->SetBranchAddress("NPFJet33", &NPFJet33);
   Tree->SetBranchAddress("NPFJet34", &NPFJet34);
   Tree->SetBranchAddress("NPFJet35", &NPFJet35);
   Tree->SetBranchAddress("NPFJet36", &NPFJet36);
   Tree->SetBranchAddress("NPFJet37", &NPFJet37);
   Tree->SetBranchAddress("NPFJet38", &NPFJet38);
   Tree->SetBranchAddress("NPFJet39", &NPFJet39);
   Tree->SetBranchAddress("NPFJet40", &NPFJet40);
   Tree->SetBranchAddress("NPFJet41", &NPFJet41);
   Tree->SetBranchAddress("NPFJet42", &NPFJet42);
   Tree->SetBranchAddress("NPFJet43", &NPFJet43);
   Tree->SetBranchAddress("NPFJet44", &NPFJet44);
   Tree->SetBranchAddress("NPFJet45", &NPFJet45);
   Tree->SetBranchAddress("NPFJet46", &NPFJet46);
   Tree->SetBranchAddress("NPFJet47", &NPFJet47);
   Tree->SetBranchAddress("NPFJet48", &NPFJet48);
   Tree->SetBranchAddress("NPFJet49", &NPFJet49);
   Tree->SetBranchAddress("NPFJet50", &NPFJet50);
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
   NewTree.Branch("NPFJet15", &NPFJet15, "NPFJet15/I");
   NewTree.Branch("NPFJet16", &NPFJet16, "NPFJet16/I");
   NewTree.Branch("NPFJet17", &NPFJet17, "NPFJet17/I");
   NewTree.Branch("NPFJet18", &NPFJet18, "NPFJet18/I");
   NewTree.Branch("NPFJet19", &NPFJet19, "NPFJet19/I");
   NewTree.Branch("NPFJet20", &NPFJet20, "NPFJet20/I");
   NewTree.Branch("NPFJet21", &NPFJet21, "NPFJet21/I");
   NewTree.Branch("NPFJet22", &NPFJet22, "NPFJet22/I");
   NewTree.Branch("NPFJet23", &NPFJet23, "NPFJet23/I");
   NewTree.Branch("NPFJet24", &NPFJet24, "NPFJet24/I");
   NewTree.Branch("NPFJet25", &NPFJet25, "NPFJet25/I");
   NewTree.Branch("NPFJet26", &NPFJet26, "NPFJet26/I");
   NewTree.Branch("NPFJet27", &NPFJet27, "NPFJet27/I");
   NewTree.Branch("NPFJet28", &NPFJet28, "NPFJet28/I");
   NewTree.Branch("NPFJet29", &NPFJet29, "NPFJet29/I");
   NewTree.Branch("NPFJet30", &NPFJet30, "NPFJet30/I");
   NewTree.Branch("NPFJet31", &NPFJet31, "NPFJet31/I");
   NewTree.Branch("NPFJet32", &NPFJet32, "NPFJet32/I");
   NewTree.Branch("NPFJet33", &NPFJet33, "NPFJet33/I");
   NewTree.Branch("NPFJet34", &NPFJet34, "NPFJet34/I");
   NewTree.Branch("NPFJet35", &NPFJet35, "NPFJet35/I");
   NewTree.Branch("NPFJet36", &NPFJet36, "NPFJet36/I");
   NewTree.Branch("NPFJet37", &NPFJet37, "NPFJet37/I");
   NewTree.Branch("NPFJet38", &NPFJet38, "NPFJet38/I");
   NewTree.Branch("NPFJet39", &NPFJet39, "NPFJet39/I");
   NewTree.Branch("NPFJet40", &NPFJet40, "NPFJet40/I");
   NewTree.Branch("NPFJet41", &NPFJet41, "NPFJet41/I");
   NewTree.Branch("NPFJet42", &NPFJet42, "NPFJet42/I");
   NewTree.Branch("NPFJet43", &NPFJet43, "NPFJet43/I");
   NewTree.Branch("NPFJet44", &NPFJet44, "NPFJet44/I");
   NewTree.Branch("NPFJet45", &NPFJet45, "NPFJet45/I");
   NewTree.Branch("NPFJet46", &NPFJet46, "NPFJet46/I");
   NewTree.Branch("NPFJet47", &NPFJet47, "NPFJet47/I");
   NewTree.Branch("NPFJet48", &NPFJet48, "NPFJet48/I");
   NewTree.Branch("NPFJet49", &NPFJet49, "NPFJet49/I");
   NewTree.Branch("NPFJet50", &NPFJet50, "NPFJet50/I");
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

