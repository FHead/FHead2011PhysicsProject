#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"

int main(int argc, char *argv[])
{
   string FileName = "";
   if(argc > 1)
      FileName = argv[1];

   TFile F(FileName.c_str());

   TTree *Tree = (TTree *)F.Get("RunLumi");

   int Run, Lumi;
   Tree->SetBranchAddress("RunNumber", &Run);
   Tree->SetBranchAddress("LumiSection", &Lumi);

   map<int, vector<int> > MasterMap;

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      if(MasterMap.find(Run) != MasterMap.end())
         MasterMap.insert(pair<int, vector<int> >(Run, vector<int>()));
      MasterMap[Run].push_back(Lumi);
   }

   F.Close();

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




