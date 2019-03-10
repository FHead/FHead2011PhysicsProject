#include "TFile.h"
#include "TTree.h"

void CheckRate(string name)
{
   TFile File("/tmp/chenyi/Meow.root");

   TTree *Tree = (TTree *)File.Get("hltbitanalysis/HltTree");

   double Passed = Tree->GetEntries(name.c_str());
   double All = Tree->GetEntries();

   cout << name << ": " << Passed << " / " << All
      << " = " << Passed / All
      << " -> " << Passed / All * 20000000 * 2 << endl;
}
