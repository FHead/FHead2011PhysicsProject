#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

int main()
{
   TChain InputTree("MRTree", "MRTree");
   InputTree.AddFile("Histograms/ElectronHadRun2011All.root");

   TFile OutputFile("ElectronReducedTree.root", "recreate");

   TTree Tree("ReducedMRTree", "asdgasdgasdg");

   double MR, R;
   InputTree.SetBranchAddress("MRL", &MR);
   InputTree.SetBranchAddress("RL", &R);

   int GoodMuonCountLoose, GoodElectronCountTight, MediumBTagCount;
   InputTree.SetBranchAddress("GoodMuonCountLoose", &GoodMuonCountLoose);
   InputTree.SetBranchAddress("GoodElectronCountTight", &GoodElectronCountTight);
   InputTree.SetBranchAddress("MediumBTagCount", &MediumBTagCount);
   
   Tree.Branch("MRL", &MR, "MRL/D");
   Tree.Branch("RL", &R, "RL/D");

   int EventCount = InputTree.GetEntries();
   for(int iEvent = 0; iEvent < EventCount; iEvent++)
   {
      if(iEvent % 1000000 == 999999)
         cout << "Processing event " << iEvent + 1 << "/" << EventCount << endl;

      InputTree.GetEntry(iEvent);

      if(GoodMuonCountLoose != 0 || GoodElectronCountTight == 0)
         continue;
      if(MediumBTagCount <= 1)
         continue;
      if(MR < 400 || R * R < 0.20)
         continue;

      Tree.Fill();
   }

   Tree.Write();

   OutputFile.Close();

   return 0;
}



