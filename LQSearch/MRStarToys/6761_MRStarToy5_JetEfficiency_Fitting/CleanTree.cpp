#include <string>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"

int main();
void CleanTree(string Input, string Output);

int main()
{
   CleanTree("Samples/FlatOneJet.root", "FlatOneJet.root");
   CleanTree("Samples/FlatTwoJet.root", "FlatTwoJet.root");
   CleanTree("Samples/RoughlyTCHELOneJet.root", "RoughlyTCHELOneJet.root");
   CleanTree("Samples/RoughlyTCHELTwoJet.root", "RoughlyTCHELTwoJet.root");
   CleanTree("Samples/RoughlyTCHELOneJetModerateDrop.root", "RoughlyTCHELOneJetModerateDrop.root");
   CleanTree("Samples/RoughlyTCHELTwoJetModerateDrop.root", "RoughlyTCHELTwoJetModerateDrop.root");
   CleanTree("Samples/BetterHighPTOneJet.root", "BetterHighPTOneJet.root");
   CleanTree("Samples/BetterHighPTTwoJet.root", "BetterHighPTTwoJet.root");
   CleanTree("Samples/WorseHighPTOneJet.root", "WorseHighPTOneJet.root");
   CleanTree("Samples/WorseHighPTTwoJet.root", "WorseHighPTTwoJet.root");
   CleanTree("Samples/NoHighPTOneJet.root", "NoHighPTOneJet.root");
   CleanTree("Samples/NoHighPTTwoJet.root", "NoHighPTTwoJet.root");
   CleanTree("Samples/ExtremeDropOneJet.root", "ExtremeDropOneJet.root");
   CleanTree("Samples/ExtremeDropTwoJet.root", "ExtremeDropTwoJet.root");
}

void CleanTree(string Input, string Output)
{
   TChain Tree("OutputTree", "OutputTree");
   Tree.AddFile(Input.c_str());
   
   TFile OutputFile(Output.c_str(), "RECREATE");
   TTree OutputTree("CleanedTree", "CleanedTree");

   double MRStar;
   double RStar;
   double GammaRStar;
   bool PassTagging;
   int IntegerPassTagging;

   Tree.SetBranchAddress("MRStar", &MRStar);
   Tree.SetBranchAddress("RStar", &RStar);
   Tree.SetBranchAddress("GammaRStar", &GammaRStar);
   Tree.SetBranchAddress("PassTagging", &PassTagging);
   
   OutputTree.Branch("MRStar", &MRStar, "MRStar/D");
   OutputTree.Branch("RStar", &RStar, "RStar/D");
   OutputTree.Branch("GammaRStar", &GammaRStar, "GammaRStar/D");
   OutputTree.Branch("PassTagging", &IntegerPassTagging, "PassTagging/I");

   int NumberOfEntries = Tree.GetEntries();
   for(int i = 0; i < NumberOfEntries; i++)
   {
      Tree.GetEntry(i);

      if(MRStar != MRStar)   continue;
      if(RStar != RStar)     continue;

      IntegerPassTagging = PassTagging;

      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();
}
















