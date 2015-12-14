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
   string BranchNameFile = "BranchNames1e-6";
   string ValueFile = "LOG_HZZ4l";
   string FileName = "HZZ4l_Prophecy4f_125_100K_tree_11521.root";

   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " BranchNames Values FileName" << endl;
      return -1;
   }

   BranchNameFile = argv[1];
   ValueFile = argv[2];
   FileName = argv[3];

   // Get list of branches to add
   vector<string> BranchNames;
   ifstream in(BranchNameFile.c_str());
   while(in)
   {
      string Temp = "";
      in >> Temp;
      if(Temp != "")
         BranchNames.push_back(Temp);
   }
   in.close();

   // Read in all the branch values
   map<int, vector<double> > BranchValues;
   ifstream in2(ValueFile.c_str());
   while(in2)
   {
      int Index = -1;
      vector<double> Values(BranchNames.size());
      for(int i = 0; i < (int)BranchNames.size(); i++)
         Values[i] = -9999;
      
      char ch[10240] = "";
      in2.getline(ch, 10239, '\n');
      stringstream line(ch);

      line >> Index;
      for(int i = 0; i < (int)BranchNames.size(); i++)
         line >> Values[i];

      bool Good = true;
      if(Index < 0)
         Good = false;
      for(int i = 0; i < (int)BranchNames.size(); i++)
         if(Values[i] < -9998)
            Good = false;
      if(Good == false)
         continue;

      BranchValues.insert(pair<int, vector<double> >(Index, Values));
   }
   in2.close();

   TFile File(FileName.c_str(), "update");
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      return -1;

   // Setup new branches
   vector<double> TreeVector(BranchNames.size());
   vector<TBranch *> Branches(BranchNames.size());
   for(int i = 0; i < (int)BranchNames.size(); i++)
      Branches[i] = Tree->Branch(BranchNames[i].c_str(), &TreeVector[i], (BranchNames[i] + "/D").c_str());

   // Loop over trees
   ProgressBar Bar(cout, Tree->GetEntries());
   Bar.SetStyle(2);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(iEntry % (EntryCount / 1000) == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      Tree->GetEntry(iEntry);

      for(int i = 0; i < (int)BranchNames.size(); i++)
         TreeVector[i] = 1;

      if(BranchValues.find(iEntry) != BranchValues.end())
         for(int i = 0; i < (int)BranchNames.size(); i++)
            TreeVector[i] = BranchValues[iEntry][i];

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









