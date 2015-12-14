#include <iostream>
#include <vector>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include "TauHelperFunctions2.h"

int main()
{
   TChain Tree("ntp1", "ntp1");
   Tree.AddFile("Samples/default_MC_10_2_7vf.root");

   int sign = -1;

   int nMc;
   int idMc[2000];
   float etaMc[2000];
   float pMc[2000];
   float energyMc[2000];
   float phiMc[2000];
   int mothMc[2000];
   int statusMc[2000];

   Tree.SetBranchAddress("nMc", &nMc);
   Tree.SetBranchAddress("idMc", idMc);
   Tree.SetBranchAddress("etaMc", etaMc);
   Tree.SetBranchAddress("phiMc", phiMc);
   Tree.SetBranchAddress("pMc", pMc);
   Tree.SetBranchAddress("energyMc", energyMc);
   Tree.SetBranchAddress("mothMc", mothMc);
   Tree.SetBranchAddress("statusMc", statusMc);

   TFile OutputFile("Output2.root", "RECREATE");

   TTree OutputTree("Tree", "Tree");

   double NuPT, TauPT;
   OutputTree.Branch("NuPT", &NuPT, "NuPT/D");
   OutputTree.Branch("TauPT", &TauPT, "TauPT/D");

   int EntryCount = Tree.GetEntries();
   cout << "Number of entries = " << EntryCount << endl;
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree.GetEntry(iEntry);

      int WTauIndex = -1;
      int WIndex = -1;

      for(int i = 0; i < nMc; i++)
      {
         if(idMc[i] == 15 * sign && mothMc[i] >= 0 && idMc[mothMc[i]] == -24 * sign)   // found!
            WTauIndex = i;
         if(WTauIndex >= 0)
            break;
      }

      if(WTauIndex == -1)
         continue;
      WIndex = mothMc[WTauIndex];

      vector<int> TauIndices;
      TauIndices.push_back(WTauIndex);
      for(int i = 0; i < (int)TauIndices.size(); i++)
      {
         for(int j = 0; j < nMc; j++)
         {
            bool Visited = false;
            for(int k = 0; k < (int)TauIndices.size(); k++)
               if(TauIndices[k] == j)
                  Visited = true;
            if(Visited == true)
               continue;

            if(idMc[j] != 15 * sign)
               continue;
            if(mothMc[j] == TauIndices[i] || mothMc[j] == WIndex)
               TauIndices.push_back(j);
         }
      }

      int TauNuIndex = -1;
      int TauLIndex = -1;
      for(int i = 0; i < nMc; i++)
      {
         bool MotherTau = false;
         for(int j = 0; j < (int)TauIndices.size(); j++)
            if(mothMc[i] == TauIndices[j])
               MotherTau = true;
         
         if(MotherTau == true && idMc[i] == 16 * sign && TauNuIndex == -1)
            TauNuIndex = i;
         if(MotherTau == true && ((idMc[i] >= 11 && idMc[i] <= 14) || (idMc[i] >= -14 && idMc[i] <= -11)))
            TauLIndex = i;
      }

      if(TauLIndex != -1)
         continue;
      if(TauNuIndex == -1)
         continue;

      FourVector TauP, NuP;
      TauP.SetSizeEtaPhi(pMc[WTauIndex], etaMc[WTauIndex], phiMc[WTauIndex]);
      TauP[0] = energyMc[WTauIndex];
      NuP.SetSizeEtaPhi(pMc[TauNuIndex], etaMc[TauNuIndex], phiMc[TauNuIndex]);
      NuP[0] = energyMc[TauNuIndex];

      NuPT = NuP.GetPT();
      TauPT = TauP.GetPT();
      
      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();

   return 0;
}






