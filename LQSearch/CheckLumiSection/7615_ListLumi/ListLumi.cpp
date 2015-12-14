#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"

int main(int argc, char *argv[])
{
   string InputFileName = "Samples/DoubleMuMay10ReRecov1_All.root";
   if(argc > 1)
      InputFileName = argv[1];
   string OutputFileName = "RunLumi.root";
   if(argc > 2)
      OutputFileName = argv[2];

   TFile F(InputFileName.c_str());
   TTree *Tree = (TTree *)F.Get("LQ3Tree");
   if(Tree == NULL)
      return -1;

   double TreeRunNumber = 0;
   double TreeLumiSection = 0;

   Tree->SetBranchAddress("RunNumber", &TreeRunNumber);
   Tree->SetBranchAddress("LumiSection", &TreeLumiSection);

   map<int, vector<int> > MasterMap;   // key = run number, value = vector of lumi sections

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Currently reading entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      int RunNumber = (int)(TreeRunNumber + 0.0001);   // to avoid downward fluctuation errors
      int LumiSection = (int)(TreeLumiSection + 0.0001);

      if(MasterMap.find(RunNumber) == MasterMap.end())
         MasterMap.insert(pair<int, vector<int> >(RunNumber, vector<int>()));
      MasterMap[RunNumber].push_back(LumiSection);

      if(MasterMap[RunNumber].size() > 10000)   // to reduce memory usage
      {
         vector<int> &Vector = MasterMap[RunNumber];
         sort(Vector.begin(), Vector.end());
         vector<int>::iterator iter = unique(Vector.begin(), Vector.end());
         Vector.erase(iter, Vector.end());
      }
   }

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("RunLumi", "Run and lumi");

   int RunNumber = 0;
   int LumiSection = 0;

   OutputTree.Branch("RunNumber", &RunNumber, "RunNumber/I");
   OutputTree.Branch("LumiSection", &LumiSection, "LumiSection/I");

   for(map<int, vector<int> >::iterator iter = MasterMap.begin(); iter != MasterMap.end(); iter++)
   {
      RunNumber = iter->first;

      vector<int> &Vector = MasterMap[RunNumber];
      sort(Vector.begin(), Vector.end());
      vector<int>::iterator iter2 = unique(Vector.begin(), Vector.end());
      Vector.erase(iter2, Vector.end());

      for(int i = 0; i < (int)Vector.size(); i++)
      {
         LumiSection = Vector[i];

         OutputTree.Fill();
      }
   }

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}





