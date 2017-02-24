#include <iostream>
using namespace std;

#include "TFile.h"
#include "TDirectoryFile.h"
#include "TTree.h"

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " Input Output" << endl;
      return -1;
   }

   TFile InputFile(argv[1]);

   TFile OutputFile(argv[2], "RECREATE");

   TTree *Tree = (TTree *)InputFile.Get("hltanalysis/HltTree");

   Tree = Tree->CloneTree();

   OutputFile.mkdir("hltbitanalysis");
   OutputFile.cd("hltbitanalysis");
   Tree->Write();

   OutputFile.Close();

   InputFile.Close();

   return 0;
}







