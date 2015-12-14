#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

#include "ProgressBar.h"

int main(int argc, char *argv[])
{
   // Default input parameters
   string BranchName = "BranchNames1e-6";
   string FileName = "HZZ4l_Prophecy4f_125_100K_tree_11521.root";

   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " BranchName FileName" << endl;
      return -1;
   }

   BranchName = argv[1];
   FileName = argv[2];

   vector<string> BranchNames;
   BranchNames.push_back(BranchName);

   TFile File(FileName.c_str(), "update");
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("zz4lTree");
   if(Tree == NULL)
      return -1;

   // Setup new branches
   vector<double> TreeVector(BranchNames.size());
   vector<TBranch *> Branches(BranchNames.size());
   for(int i = 0; i < (int)BranchNames.size(); i++)
      Branches[i] = Tree->Branch(BranchNames[i].c_str(), &TreeVector[i], (BranchNames[i] + "/F").c_str());

   // Loop over trees
   ProgressBar Bar(cout, Tree->GetEntries());
   Bar.SetStyle(2);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(EntryCount < 1000 || (iEntry % (EntryCount / 1000) == 0))
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      Tree->GetEntry(iEntry);

      for(int i = 0; i < (int)BranchNames.size(); i++)
         TreeVector[i] = 1;

      for(int i = 0; i < (int)BranchNames.size(); i++)
         Branches[i]->Fill();
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   // ((TDirectoryFile *)(File.Get("zz4lTree")))->cd();
   
   Tree->Write("", TObject::kOverwrite);

   File.Close();

   return 0;
}









