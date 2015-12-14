#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TList.h"

#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   if(argc < 2)
   {
      cout << "Usage: " << argv[0] << " SourceFile" << endl;
      return -1;
   }

   string SourceFileName = argv[1];

   TFile Source(SourceFileName.c_str());

   TTree *OldTree = (TTree *)Source.Get("LQ3Tree");

   TreeRecord M;
   M.SetBranchAddress(OldTree);

   int EntryCount = OldTree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 100000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      OldTree->GetEntry(iEntry);

      if(M.PassNoiseFilter == false)
         continue;

      int CaloJet60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            CaloJet60 = CaloJet60 + 1;
      if(CaloJet60 < 2)
         continue;

      /*
      int LooseCount = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3 && M.CaloJetTCHETag[i] > 1.7)
            LooseCount = LooseCount + 1;
      if(LooseCount < 2)
         continue;
      */

      /*
      if(M.GoodMuonCount >= 1)
         continue;
      if(M.GoodElectronCount >= 1)
         continue;
      */

      FourVector LeptonP(0, 0, 0, 0);
      if(M.GoodMuonCount >= 1)
         LeptonP.SetPtEtaPhi(M.Muon1PT, M.Muon1Eta, M.Muon1Phi);

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount && i < 100; i++)
      {
         if(M.CaloJetPT[i] < 40)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         GoodJets.push_back(NewJet);
      }
      if(GoodJets.size() > 20)
         continue;
      if(GoodJets.size() < 2)
         continue;

      vector<FourVector> Hemispheres = SplitIntoGroups(GoodJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      PFMET = PFMET + LeptonP;

      double MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
      double RNew = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      double R2New = RNew * RNew;

      if(M.EventNumber < 0)
         cerr << "[ERROR] Event number smaller than zero!!!" << endl;

      if(MRNew > 300 && R2New > 0.14)
         cout << "[R1] " << (int)M.RunNumber << " " << (long long)M.EventNumber << " " << (int)M.LumiSection << endl;
      if(MRNew > 400 && R2New > 0.20)
         cout << "[R2] " << (int)M.RunNumber << " " << (long long)M.EventNumber << " " << (int)M.LumiSection << endl;
   }

   Source.Close();

   return 0;
}

