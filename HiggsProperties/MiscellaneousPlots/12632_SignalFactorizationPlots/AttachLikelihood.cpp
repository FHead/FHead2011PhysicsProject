#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"

#include "PTYFunctions.h"

int main(int argc, char *argv[])
{
   string FileName = "Toys.root";
   if(argc == 1)
   {
      cerr << "Usage: " << argv[0] << " FileName" << endl;
      return -1;
   }
   FileName = argv[1];

   double s = 126 * 126;

   float pt, y, pty;

   TFile File(FileName.c_str(), "update");
   TTree *Tree = (TTree *)File.Get("ProductionSpectrumTree");

   Tree->SetBranchAddress("pt", &pt);
   Tree->SetBranchAddress("y", &y);
   TBranch *Branch = Tree->Branch("pty", &pty, "pty/F");

   int EntryCount = Tree->GetEntries();

   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      pty = GetPTYDensity8TeVSignal(pt, y, s);

      Branch->Fill();
   }

   Tree->Write();

   File.Close();
}







