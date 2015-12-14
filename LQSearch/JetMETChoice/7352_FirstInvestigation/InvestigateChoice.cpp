#include <iostream>
#include <vector>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TNtuple.h"

#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"

int main()
{
   cout << "Hello World!" << endl;

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root");

   TreeRecord M;
   M.SetBranchAddress(&Tree);

   TFile F("OutputFile.root", "recreate");

   TNtuple OutputTree("OutputTree", "OutputTree", "CaloMR:PFMR:CaloCaloR:CaloPFR:PFPFR");

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree.GetEntry(iEntry);

      vector<FourVector> GoodCaloJets;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 40)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector Jet;
         Jet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);
         GoodCaloJets.push_back(Jet);
      }
      vector<FourVector> CaloGroups;
      if(GoodCaloJets.size() >= 2 && GoodCaloJets.size() < 20)
         CaloGroups = SplitIntoGroups(GoodCaloJets, true);
      
      vector<FourVector> GoodPFJets;
      for(int i = 0; i < M.PFJetCount; i++)
      {
         if(M.PFJetPT[i] < 40)
            continue;
         if(M.PFJetEta[i] < -3 || M.PFJetEta[i] > 3)
            continue;

         FourVector Jet;
         Jet.SetPtEtaPhi(M.PFJetPT[i], M.PFJetEta[i], M.PFJetPhi[i]);
         GoodPFJets.push_back(Jet);
      }
      vector<FourVector> PFGroups;
      if(GoodPFJets.size() >= 2 && GoodPFJets.size() < 20)
         PFGroups = SplitIntoGroups(GoodPFJets, true);

      FourVector CaloMET(0, M.CaloMET[0], M.CaloMET[1], 0);
      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);

      double CaloMR = -1;
      double PFMR = -1;
      
      double CaloCaloR = -1;
      double CaloPFR = -1;
      double PFPFR = -1;

      if(CaloGroups.size() == 2)
         CaloMR = Get2011MR(CaloGroups[0], CaloGroups[1]);
      if(PFGroups.size() == 2)
         PFMR = Get2011MR(PFGroups[0], PFGroups[1]);

      if(CaloGroups.size() == 2)
         CaloCaloR = Get2011R(CaloGroups[0], CaloGroups[1], CaloMET);
      if(CaloGroups.size() == 2)
         CaloPFR = Get2011R(CaloGroups[0], CaloGroups[1], PFMET);
      if(PFGroups.size() == 2)
         PFPFR = Get2011R(PFGroups[0], PFGroups[1], PFMET);

      OutputTree.Fill(CaloMR, PFMR, CaloCaloR, CaloPFR, PFPFR);
   }

   OutputTree.Write();
   F.Close();

   return 0;
}



