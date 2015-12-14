#include <iostream>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

int main()
{
   TChain InputTree("MRTree", "MRTree");
   InputTree.AddFile("Histograms/MuHadRun2011All.root");

   double MRL, RL;
   int GoodMuonCountLoose, GoodMuonCountTight, GoodElectronCountLoose;
   int LooseBTagCount, MediumBTagCount;

   InputTree.SetBranchAddress("MRL", &MRL);
   InputTree.SetBranchAddress("RL", &RL);
   InputTree.SetBranchAddress("GoodMuonCountLoose", &GoodMuonCountLoose);
   InputTree.SetBranchAddress("GoodMuonCountTight", &GoodMuonCountTight);
   InputTree.SetBranchAddress("GoodElectronCountLoose", &GoodElectronCountLoose);
   InputTree.SetBranchAddress("LooseBTagCount", &LooseBTagCount);
   InputTree.SetBranchAddress("MediumBTagCount", &MediumBTagCount);

   TFile OutputFile("MuHadReducedTree.root", "recreate");

   TTree TightMuL("TightMuL", "");
   TTree LooseMuL("LooseMuL", "");
   TTree LooseMuL2("LooseMuL2", "");
   TTree LooseMuMM("LooseMuMM", "");
   TTree TightMuMM("TightMuMM", "");
   TTree LooseMuLL("LooseMuLL", "");
   TTree LooseMuLL2("LooseMuLL2", "");
   TTree TightMuLL("TightMuLL", "");

   TightMuL.Branch("MRL", &MRL, "MRL/D");
   TightMuL.Branch("RL", &RL, "RL/D");
   LooseMuL.Branch("MRL", &MRL, "MRL/D");
   LooseMuL.Branch("RL", &RL, "RL/D");
   LooseMuL2.Branch("MRL", &MRL, "MRL/D");
   LooseMuL2.Branch("RL", &RL, "RL/D");
   LooseMuMM.Branch("MRL", &MRL, "MRL/D");
   LooseMuMM.Branch("RL", &RL, "RL/D");
   TightMuMM.Branch("MRL", &MRL, "MRL/D");
   TightMuMM.Branch("RL", &RL, "RL/D");
   LooseMuLL.Branch("MRL", &MRL, "MRL/D");
   LooseMuLL.Branch("RL", &RL, "RL/D");
   LooseMuLL2.Branch("MRL", &MRL, "MRL/D");
   LooseMuLL2.Branch("RL", &RL, "RL/D");
   TightMuLL.Branch("MRL", &MRL, "MRL/D");
   TightMuLL.Branch("RL", &RL, "RL/D");

   int EntryCount = InputTree.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      InputTree.GetEntry(i);

      if(MRL >= 400 && RL * RL >= 0.14 && GoodElectronCountLoose == 0)
      {
         if(GoodMuonCountTight == 1 && LooseBTagCount >= 1)
            TightMuL.Fill();
         if(GoodMuonCountLoose == 1 && LooseBTagCount >= 1)
            LooseMuL.Fill();
         if(GoodMuonCountLoose == 1 && LooseBTagCount >= 1 && LooseMuL2.GetEntries() < 5000)
            LooseMuL2.Fill();
         if(GoodMuonCountLoose == 1 && MediumBTagCount >= 2)
            LooseMuMM.Fill();
         if(GoodMuonCountTight == 1 && MediumBTagCount >= 2)
            TightMuMM.Fill();
         if(GoodMuonCountLoose == 1 && LooseBTagCount >= 2)
            LooseMuLL.Fill();
         if(GoodMuonCountLoose == 1 && LooseBTagCount >= 2 && LooseMuLL2.GetEntries() < 4000)
            LooseMuLL2.Fill();
         if(GoodMuonCountTight == 1 && LooseBTagCount >= 2)
            TightMuLL.Fill();
      }
   }

   TightMuL.Write();
   LooseMuL.Write();
   LooseMuL2.Write();
   LooseMuMM.Write();
   TightMuMM.Write();
   LooseMuLL.Write();
   LooseMuLL2.Write();
   TightMuLL.Write();
   
   OutputFile.Close();

   return 0;
}





