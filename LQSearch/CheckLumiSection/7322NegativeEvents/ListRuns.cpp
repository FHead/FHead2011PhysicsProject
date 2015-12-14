#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[])
{
   string InputFileName = "Samples/DoubleMuMay10ReRecov1_All.root";
   if(argc > 1)
      InputFileName = argv[1];

   TFile F(InputFileName.c_str());
   TTree *Tree = (TTree *)F.Get("LQ3Tree");
   if(Tree == NULL)
      return -1;

   TreeRecord M;
   M.SetBranchAddress(Tree);
   
   Tree->SetBranchStatus("*", false);
   Tree->SetBranchStatus("RunNumber", true);
   Tree->SetBranchStatus("LumiSection", true);
   Tree->SetBranchStatus("EventNumber", true);

   map<int, int> NegativeEntries;

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Currently reading entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      int RunNumber = (int)(M.RunNumber + 0.0001);   // to avoid downward fluctuation errors

      if(M.EventNumber < 0)
         NegativeEntries[RunNumber] = NegativeEntries[RunNumber] + 1;
   }

   cout << endl;
   for(map<int, int>::iterator iter = NegativeEntries.begin(); iter != NegativeEntries.end(); iter++)
   {
      int RunNumber = iter->first;
      int Count = iter->second;

      if(Count == 0)
         continue;

      cout << "Run " << RunNumber << " has " << Count << " negative events." << endl;
   }

   return 0;
}





