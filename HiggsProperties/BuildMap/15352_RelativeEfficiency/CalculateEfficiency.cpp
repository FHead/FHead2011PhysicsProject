#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "AngleConversion.h"
#include "Cuts.h"

int main(int argc, char *argv[])
{
   if(argc == 1)
   {
      cerr << "Usage: " << argv[0] << " RootFile" << endl;
      return -1;
   }

   string FileName = argv[1];

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("Tree");

   double L1PT, L1Eta, L1Phi, L1ID;
   double L2PT, L2Eta, L2Phi, L2ID;
   double L3PT, L3Eta, L3Phi, L3ID;
   double L4PT, L4Eta, L4Phi, L4ID;
   Tree->SetBranchAddress("L1PT", &L1PT);
   Tree->SetBranchAddress("L1Eta", &L1Eta);
   Tree->SetBranchAddress("L1Phi", &L1Phi);
   Tree->SetBranchAddress("L1ID", &L1ID);
   Tree->SetBranchAddress("L2PT", &L2PT);
   Tree->SetBranchAddress("L2Eta", &L2Eta);
   Tree->SetBranchAddress("L2Phi", &L2Phi);
   Tree->SetBranchAddress("L2ID", &L2ID);
   Tree->SetBranchAddress("L3PT", &L3PT);
   Tree->SetBranchAddress("L3Eta", &L3Eta);
   Tree->SetBranchAddress("L3Phi", &L3Phi);
   Tree->SetBranchAddress("L3ID", &L3ID);
   Tree->SetBranchAddress("L4PT", &L4PT);
   Tree->SetBranchAddress("L4Eta", &L4Eta);
   Tree->SetBranchAddress("L4Phi", &L4Phi);
   Tree->SetBranchAddress("L4ID", &L4ID);

   vector<int> Counts(13);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      if(L1ID != L3ID)
         Leptons = Leptons.ReorderLeptons2e2mu();
      else
         Leptons = Leptons.ReorderLeptons4e();

      vector<bool> PassCuts = PassPairingCuts(Leptons);

      for(int i = 0; i < 13; i++)
         Counts[i] = Counts[i] + PassCuts[i];
   }

   cout << FileName << " " << EntryCount;
   for(int i = 0; i < 13; i++)
      cout << " " << Counts[i];
   cout << endl;

   File.Close();

   return 0;
}



