#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

int main()
{
   TFile File("openHLT.root", "UPDATE");

   TDirectoryFile *Dir = (TDirectoryFile *)File.Get("hltbitanalysis");

   TTree *Tree = (TTree *)Dir->Get("HltTree");

   if(Tree == NULL)
      return -1;

   int SingleJet8;
   int SingleJet12;
   int SingleJet24;
   int DMeson15;
   int HighPT18;
   int HighPT26;
   int HighPT36;

   Tree->SetBranchAddress("L1_SingleJet8_BptxAND", &SingleJet8);
   Tree->SetBranchAddress("L1_SingleJet12_BptxAND", &SingleJet12);
   Tree->SetBranchAddress("L1_SingleJet24_BptxAND", &SingleJet24);
   Tree->SetBranchAddress("HLT_PADmesonPPTrackingGlobal_Dpt15_v1", &DMeson15);
   Tree->SetBranchAddress("HLT_PAFullTracks_HighPt18_v1", &HighPT18);
   Tree->SetBranchAddress("HLT_PAFullTracks_HighPt26_v1", &HighPT26);
   Tree->SetBranchAddress("HLT_PAFullTracks_HighPt36_v1", &HighPT36);

   int NewBit;
   int NewBit18;
   int NewBit26;
   int NewBit36;

   TBranch *Branch = (TBranch *)Tree->Branch("HLT_PADmesonPPTrackingGlobal_Dpt15_v1_SeededOnSingleJet8", &NewBit, "HLT_PADmesonPPTrackingGlobal_Dpt15_v1_SeededOnSingleJet8/I");
   TBranch *Branch18 = (TBranch *)Tree->Branch("HLT_PAFullTracks_HighPt18_v1_SeededOnSingleJet8", &NewBit18, "HLT_PAFullTracks_HighPt18_v1_SeededOnSingleJet8/I");
   TBranch *Branch26 = (TBranch *)Tree->Branch("HLT_PAFullTracks_HighPt26_v1_SeededOnSingleJet12", &NewBit26, "HLT_PAFullTracks_HighPt26_v1_SeededOnSingleJet12/I");
   TBranch *Branch36 = (TBranch *)Tree->Branch("HLT_PAFullTracks_HighPt36_v1_SeededOnSingleJet24", &NewBit36, "HLT_PAFullTracks_HighPt36_v1_SeededOnSingleJet24/I");

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      NewBit = SingleJet8 * DMeson15;
      NewBit18 = SingleJet8 * HighPT18;
      NewBit26 = SingleJet12 * HighPT26;
      NewBit36 = SingleJet24 * HighPT36;

      Branch->Fill();
      Branch18->Fill();
      Branch26->Fill();
      Branch36->Fill();
   }

   Dir->cd();
   Tree->Write();

   Dir->Delete("HltTree;1");

   File.Close();

   return 0;
}




