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

   map<int, vector<int> > MasterMap;   // key = run number, value = vector of lumi sections

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Currently reading entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      int RunNumber = (int)(M.RunNumber + 0.0001);   // to avoid downward fluctuation errors
      int LumiSection = (int)(M.LumiSection + 0.0001);

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

   cout << endl;
   cout << "Summary of lumi sections for file \"" << InputFileName << "\":" << endl;
   cout << endl;
   for(map<int, vector<int> >::iterator iter = MasterMap.begin(); iter != MasterMap.end(); iter++)
   {
      int RunNumber = iter->first;
      vector<int> Vector = iter->second;   // changing value of map shouldn't alter stuff...but just to be cautious
      sort(Vector.begin(), Vector.end());
      vector<int>::iterator iter2 = unique(Vector.begin(), Vector.end());
      Vector.erase(iter2, Vector.end());

      if(Vector.size() == 0)
         continue;
      if(Vector.size() == 1)
      {
         cout << RunNumber << "(1): " << Vector[0] << "-" << Vector[0] << endl;
         continue;
      }

      cout << RunNumber << "(" << Vector.size() << "): ";

      int Start = 0;
      for(int i = 1; i < (int)Vector.size(); i++)
      {
         if(Vector[i] == Vector[i-1] + 1)
            continue;

         cout << Vector[Start] << "-" << Vector[i-1] << ", ";
         Start = i;
      }

      cout << Vector[Start] << "-" << Vector[Vector.size()-1] << endl;
   }

   cout << endl;
   cout << "JSON File:" << endl;
   cout << endl;

   bool First = true;
   cout << "{";
   for(map<int, vector<int> >::iterator iter = MasterMap.begin(); iter != MasterMap.end(); iter++)
   {
      int RunNumber = iter->first;
      vector<int> Vector = iter->second;   // changing value of map shouldn't alter stuff...but just to be cautious
      sort(Vector.begin(), Vector.end());
      vector<int>::iterator iter2 = unique(Vector.begin(), Vector.end());
      Vector.erase(iter2, Vector.end());

      if(Vector.size() == 0)
         continue;

      if(First == true)
         First = false;
      else
         cout << ", ";
      
      if(Vector.size() == 1)
      {
         cout << "\"" << RunNumber << "\": [[" << Vector[0] << ", " << Vector[0] << "]]";
         continue;
      }

      cout << "\"" << RunNumber << "\": [";

      int Start = 0;
      for(int i = 1; i < (int)Vector.size(); i++)
      {
         if(Vector[i] == Vector[i-1] + 1)
            continue;

         cout << "[" << Vector[Start] << ", " << Vector[i-1] << "], ";
         Start = i;
      }

      cout << "[" << Vector[Start] << ", " << Vector[Vector.size()-1] << "]]";
   }
   cout << "}" << endl;

   return 0;
}





