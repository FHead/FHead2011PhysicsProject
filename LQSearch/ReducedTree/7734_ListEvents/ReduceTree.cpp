#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   if(argc <= 2)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputFile" << endl;
      return -1;
   }

   TChain InputTree("LQ3Tree", "LQ3Tree");
   InputTree.AddFile(argv[1]);

   TreeRecord M;
   M.SetBranchAddress(&InputTree);

   TFile OutputFile(argv[2], "RECREATE");

   TTree OutputTree("SuperReducedTree", "SuperReducedTree 7734");

   double MR, R, MRPhoton, RPhoton;
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");
   OutputTree.Branch("MRPhoton", &MRPhoton, "MRPhoton/D");
   OutputTree.Branch("RPhoton", &RPhoton, "RPhoton/D");

   int LooseBTagCount;
   OutputTree.Branch("TagCount", &LooseBTagCount, "TagCount/I");

   long long RunNumber, EventNumber;
   int LumiSection;
   OutputTree.Branch("RunNumber", &RunNumber, "RunNumber/LL");
   OutputTree.Branch("EventNumber", &EventNumber, "EventNumber/LL");
   OutputTree.Branch("LumiSection", &LumiSection, "LumiSection/I");

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << "...." << endl;

      InputTree.GetEntry(iEntry);

      if(M.PassNoiseFilter == false)
         continue;

      RunNumber = M.RunNumber;
      EventNumber = M.EventNumber;
      LumiSection = M.LumiSection;

      int JetCountAbove60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 60)
            continue;

         JetCountAbove60 = JetCountAbove60 + 1;
      }
      if(JetCountAbove60 < 2)
         continue;

      LooseBTagCount = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 80)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         if(M.CaloJetTCHETag[i] < 1.7)
            continue;

         LooseBTagCount = LooseBTagCount + 1;
      }

      FourVector PhotonP(0, 0, 0, 0);
      double PhotonPT = 0;
      double PhotonEta = 0;
      for(int i = 0; i < M.PhotonCount; i++)
      {
         FourVector P;
         P.SetPtEtaPhi(M.PhotonPT[i], M.PhotonEta[i], M.PhotonPhi[i]);

         if(M.PhotonPixelSeed[i] == true)
            continue;
         if(M.PhotonPT[i] < 30)
            continue;
         if(fabs(M.PhotonEta[i]) > 1.5)
            continue;
         if(M.PhotonEcalIsolation[i] + M.PhotonHcalIsolation[i] + M.PhotonTrackIsolation[i]
            - M.Rho * PI * 0.4 * 0.4 > 6)
            continue;
         if(M.PhotonR9[i] < 0.8 || M.PhotonR9[i] > 1)
            continue;
         if(M.PhotonSigmaIEtaIEta[i] > 0.11)
            continue;
         if(M.PhotonHOverE[i] > 0.05)
            continue;

         PhotonP = P;
         PhotonPT = PhotonP.GetPT();
         PhotonEta = PhotonP.GetEta();
         break;
      }

      vector<FourVector> GoodJets;
      vector<FourVector> GoodNonPhotonJets;
      multimap<double, FourVector, greater<double> > BJetSorterA;
      multimap<double, FourVector, greater<double> > BJetSorterB;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 40)
            continue;

         FourVector JetP;
         JetP.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         GoodJets.push_back(JetP);

         if(PhotonP.GetPT() < 1)   // no photon
            GoodNonPhotonJets.push_back(JetP);
         else if(GetDR(PhotonP, JetP) > 0.3)   // not close to the photon
            GoodNonPhotonJets.push_back(JetP);

         if(M.CaloJetPT[i] > 80)
            BJetSorterA.insert(pair<double, FourVector>(M.CaloJetTCHETag[i], JetP));
         else
            BJetSorterB.insert(pair<double, FourVector>(M.CaloJetTCHETag[i], JetP));
      }
      if(GoodJets.size() > 10)
      {
         cout << M.RunNumber << " " << M.EventNumber << " has " << GoodJets.size() << " good jets." << endl;
         continue;
      }
      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      FourVector ME(0, M.PFMET[0], M.PFMET[1], 0);

      MR = Get2011MR(Groups[0], Groups[1]);
      R = Get2011R(Groups[0], Groups[1], ME);

      MRPhoton = 0;
      RPhoton = 0;
      if(GoodNonPhotonJets.size() >= 2)
      {
         vector<FourVector> NonPhotonGroups = SplitIntoGroups(GoodNonPhotonJets, true);
         FourVector MEWithPhoton = ME + PhotonP;
         MRPhoton = Get2011MR(NonPhotonGroups[0], NonPhotonGroups[1]);
         RPhoton = Get2011R(NonPhotonGroups[0], NonPhotonGroups[1], MEWithPhoton);
      }

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}







