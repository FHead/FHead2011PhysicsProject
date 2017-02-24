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
   int DMeson15;

   Tree->SetBranchAddress("L1_SingleJet8_BptxAND", &SingleJet8);
   Tree->SetBranchAddress("HLT_PADmesonPPTrackingGlobal_Dpt15_v1", &DMeson15);

   int NewBit;

   TBranch *Branch = (TBranch *)Tree->Branch("HLT_PADmesonPPTrackingGlobal_Dpt15_v1_SeededOnSingleJet8", &NewBit, "HLT_PADmesonPPTrackingGlobal_Dpt15_v1_SeededOnSingleJet8/I");

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      NewBit = SingleJet8 * DMeson15;

      Branch->Fill();
   }

   Dir->cd();
   Tree->Write();

   Dir->Delete("HltTree;1");

   File.Close();

   return 0;
}




