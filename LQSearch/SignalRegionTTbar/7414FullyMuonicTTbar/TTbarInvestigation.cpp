#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TChain.h"

#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

#include "ReadNTPTreeV4.h"

int main();
vector<int> CountWMuNuFromTTbar(NTPTreeMessenger &M, int X = 13);

int main()
{
   TChain Tree("ntp1", "ntp1");
   Tree.AddFile("Samples/default_MC_181_0_HPz.root");
   Tree.AddFile("Samples/default_MC_176_0_H7L.root");
   Tree.AddFile("Samples/default_MC_383_0_APM.root");
   Tree.AddFile("Samples/default_MC_9_0_3KI.root");
   Tree.AddFile("Samples/default_MC_38_0_51d.root");
   Tree.AddFile("Samples/default_MC_198_0_K0K.root");

   NTPTreeMessenger M;
   M.SetBranchAddress(&Tree);

   TH1D HMuonCount("HMuonCount", "Muon count (from W from t)", 5, -0.5, 4.5);
   TH1D HMuonInAcceptanceCount("HMuonInAcceptanceCount", "Muon count (in acceptance)", 3, -0.5, 2.5);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree.GetEntry(iEntry);

      vector<int> MuonIndex = CountWMuNuFromTTbar(M, 13);
      vector<int> ElectronIndex = CountWMuNuFromTTbar(M, 11);
      vector<int> TauIndex = CountWMuNuFromTTbar(M, 15);

      HMuonCount.Fill(MuonIndex.size());

      if(MuonIndex.size() != 2)   // want fully muonic ttbars
         continue;

      const double EtaBoundary = 2.4;

      int MuonInAcceptance = 0;
      for(int i = 0; i < (int)MuonIndex.size(); i++)
         if(fabs(M.etaMc[MuonIndex[i]]) < EtaBoundary && M.pMc[MuonIndex[i]] / cosh(M.etaMc[MuonIndex[i]]) > 20)
            MuonInAcceptance = MuonInAcceptance + 1;

      HMuonInAcceptanceCount.Fill(MuonInAcceptance);
   }

   PsFileHelper PsFile("TTbarInvestigation.ps");
   PsFile.AddTextPage("TTbar!");

   PsFile.AddPlot(HMuonCount, "hist text00", true);
   PsFile.AddPlot(HMuonInAcceptanceCount, "hist text00", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

vector<int> CountWMuNuFromTTbar(NTPTreeMessenger &M, int X)
{
   map<double, int> PTToMuonIndex;

   for(int i = 0; i < M.nMc; i++)
   {
      if(M.idMc[i] != X && M.idMc[i] != -X)
         continue;
      if(M.mothMc[i] < 0)
         continue;
      if(M.idMc[M.mothMc[i]] != 24 && M.idMc[M.mothMc[i]] != -24)
         continue;
      if(M.mothMc[M.mothMc[i]] < 0)
         continue;
      if(M.idMc[M.mothMc[M.mothMc[i]]] != 6 && M.idMc[M.mothMc[M.mothMc[i]]] != -6)
         continue;

      PTToMuonIndex.insert(pair<double, int>(M.pMc[i] / cosh(M.etaMc[i]), i));
   }

   vector<int> Results;
   for(map<double, int>::iterator iter = PTToMuonIndex.begin(); iter != PTToMuonIndex.end(); iter++)
      Results.push_back(iter->second);

   return Results;
}





