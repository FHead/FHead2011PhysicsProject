#include <iostream>
#include <fstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputList = CL.Get("Input");
   string InputFile = CL.Get("OpenHLT");
   string TreeName = CL.Get("TreeName", "hltbitanalysis/HltTree");
   double Rate = CL.GetDouble("Rate", 10000);

   TFile File(InputFile.c_str());

   TTree *Tree = (TTree *)File.Get(TreeName.c_str());
   assert(Tree != NULL);

   int TotalEntry = Tree->GetEntries();

   ifstream in(InputList.c_str());

   while(in)
   {
      string Trigger = "";
      in >> Trigger;

      if(Trigger == "")
         continue;

      int Count = Tree->GetEntries(Trigger.c_str());
      cout << Trigger << " " << Count << " " << TotalEntry
         << " " << (double)Count / TotalEntry * Rate << endl;
   }

   in.close();

   File.Close();

   return 0;
}




