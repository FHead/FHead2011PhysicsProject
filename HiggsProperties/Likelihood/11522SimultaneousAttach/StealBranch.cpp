#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

int main(int argc, char *argv[])
{
   string SourceFileName = "BatchResult/HZZ4l_Prophecy4f_125_100K_tree_11521_EffMEE.root";
   string SourceTreeName = "zz4lTree/probe_tree";
   string TargetFileName = "HZZ4l_Prophecy4f_125_100K_tree_11521.root";
   string TargetDirectoryName = "zz4lTree";
   string TargetTreeName = "probe_tree";
   string BranchName = "Likelihood_EffMEE";

   if(argc != 7)
   {
      cerr << "Usage: " << argv[0]
         << " SourceFileName SourceTreeName TargetFileName TargetDirectoryName TargetTreeName BranchName"
         << endl;
      cerr << "Put \"NULL\" if the tree is at the base directory" << endl;
      return -1;
   }

   SourceFileName = argv[1];
   SourceTreeName = argv[2];
   TargetFileName = argv[3];
   TargetDirectoryName = argv[4];
   TargetTreeName = argv[5];
   BranchName = argv[6];

   TFile SourceFile(SourceFileName.c_str());
   TFile TargetFile(TargetFileName.c_str(), "update");

   TTree *SourceTree = (TTree *)SourceFile.Get(SourceTreeName.c_str());
   TTree *TargetTree = (TTree *)TargetFile.Get(TargetTreeName.c_str());

   TDirectory *TargetDirectory = NULL;
   if(TargetDirectoryName != "NULL")
      TargetDirectory = (TDirectory *)TargetFile.Get(TargetDirectoryName.c_str());

   if(SourceTree == NULL)
   {
      cerr << "Source tree " << SourceTreeName << " not found in file " << SourceFileName << endl;
      cerr << "Exiting..." << endl;
      return -1;
   }
   if(TargetTree == NULL)
   {
      cerr << "Target tree " << TargetTreeName << " not found in file " << TargetFileName << endl;
      cerr << "Exiting..." << endl;
      return -1;
   }

   double BranchValue = 0;
   SourceTree->SetBranchAddress(BranchName.c_str(), &BranchValue);
   TBranch *Branch = TargetTree->Branch(BranchName.c_str(), &BranchValue, (BranchName + "/D").c_str());

   int EntryCount = min(SourceTree->GetEntries(), TargetTree->GetEntries());
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      SourceTree->GetEntry(iEntry);
      Branch->Fill();
   }

   if(TargetDirectory != NULL)
      TargetDirectory->cd();
   TargetTree->Write("", TObject::kOverwrite);

   TargetFile.Close();
   SourceFile.Close();

   return 0;
}









