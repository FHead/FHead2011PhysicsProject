#include <iostream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "Messenger.h"

int main(int argc, char *argv[])
{
   string ForestFileName = "root://xrootd17.cmsaf.mit.edu//store/user/krajczar/forestpPb_merged/ReggeGribovPartonMCpPb_MinBias_8016GeV_EposLHC/HiForest_MB_merged_10M.root";
   string OutputFileName = "Index.root";

   TFile *ForestFile = TFile::Open(ForestFileName.c_str());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree Tree("IndexTree", "IndexTree");
   int Run;
   long long Event;
   int Lumi;
   int Index;
   Tree.Branch("Run", &Run, "Run/I");
   Tree.Branch("Event", &Event, "Event/LL");
   Tree.Branch("Lumi", &Lumi, "Lumi/I");
   Tree.Branch("Index", &Index, "Index/I");

   HiEventTreeMessenger MHiEvent(*ForestFile);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      if((i + 1) % 10000 == 0)
         cerr << "Indexing event " << i + 1 << "/" << EntryCount << endl;

      MHiEvent.GetEntry(i);

      Run = MHiEvent.Run;
      Event = MHiEvent.Event;
      Lumi = MHiEvent.Lumi;
      Index = i;

      Tree.Fill();
   }

   Tree.Write();

   OutputFile.Close();

   ForestFile->Close();

   delete ForestFile;

   return 0;
}









