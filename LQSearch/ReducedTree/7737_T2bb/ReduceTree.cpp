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

   TH1D HPileUpCount("HPileUpCount", "Pileups", 202, -1.5, 200.5);

   TTree OutputTree("ReducedTree", "ReducedTree 7737 with m0/m12");

   double MR, R, MR11, R11, MRPhoton, RPhoton;
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");
   OutputTree.Branch("MR11", &MR11, "MR11/D");
   OutputTree.Branch("R11", &R11, "R11/D");
   OutputTree.Branch("MRPhoton", &MRPhoton, "MRPhoton/D");
   OutputTree.Branch("RPhoton", &RPhoton, "RPhoton/D");

   int LooseBTagCount, MediumBTagCount, TightBTagCount;
   OutputTree.Branch("LooseBTagCount", &LooseBTagCount, "LooseBTagCount/I");
   OutputTree.Branch("MediumBTagCount", &MediumBTagCount, "MediumBTagCount/I");
   OutputTree.Branch("TightBTagCount", &TightBTagCount, "TightBTagCount/I");

   int JetCount80;
   OutputTree.Branch("JetCount80", &JetCount80, "JetCount80/I");

   int PileupCount = 0;
   OutputTree.Branch("PileupCount", &PileupCount, "PileupCount/I");

   OutputTree.Branch("GoodMuonCountTight", &M.GoodMuonCountTight, "GoodMuonCountTight/I");
   OutputTree.Branch("GoodMuonCountLoose", &M.GoodMuonCountLoose, "GoodMuonCountLoose/I");
   OutputTree.Branch("GoodElectronCountTight", &M.GoodElectronCount80, "GoodElectronCountTight/I");
   OutputTree.Branch("GoodElectronCountLoose", &M.GoodElectronCount95, "GoodElectronCountLoose/I");

   double PhotonPT, PhotonEta;
   OutputTree.Branch("MuonPT", &M.Muon1PT, "MuonPT/D");
   OutputTree.Branch("MuonEta", &M.Muon1Eta, "MuonEta/D");
   OutputTree.Branch("MuonPhi", &M.Muon1Phi, "MuonPhi/D");
   OutputTree.Branch("Muon2PT", &M.Muon2PT, "Muon2PT/D");
   OutputTree.Branch("Muon2Eta", &M.Muon2Eta, "Muon2Eta/D");
   OutputTree.Branch("Muon2Phi", &M.Muon2Phi, "Muon2Phi/D");
   OutputTree.Branch("ElectronPT", &M.Electron1PT, "ElectronPT/D");
   OutputTree.Branch("ElectronEta", &M.Electron1Eta, "ElectronEta/D");
   OutputTree.Branch("Jet1PT", &M.CaloJetPT[0], "Jet1PT/D");
   OutputTree.Branch("Jet1Eta", &M.CaloJetEta[0], "Jet1Eta/D");
   OutputTree.Branch("PhotonPT", &PhotonPT, "PhotonPT/D");
   OutputTree.Branch("PhotonEta", &PhotonEta, "PhotonEta/D");

   OutputTree.Branch("Rho", &M.Rho, "Rho/D");

   OutputTree.Branch("m0", &M.m0, "m0/D");
   OutputTree.Branch("m12", &M.m12, "m12/D");

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << "...." << endl;

      InputTree.GetEntry(iEntry);

      // if(M.PassNoiseFilter == false)
      //    continue;

      PileupCount = M.PileUp;
      HPileUpCount.Fill(M.PileUp);

      int JetCountAbove60 = 0;
      JetCount80 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 60)
            continue;

         JetCountAbove60 = JetCountAbove60 + 1;

         if(M.CaloJetPT[i] > 80)
            JetCount80 = JetCount80 + 1;
      }
      if(JetCountAbove60 < 2)
         continue;

      LooseBTagCount = 0;
      MediumBTagCount = 0;
      TightBTagCount = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 80)
            continue;

         if(M.CaloJetTCHETag[i] > 1.7)
            LooseBTagCount = LooseBTagCount + 1;
         if(M.CaloJetTCHETag[i] > 3.3)
            MediumBTagCount = MediumBTagCount + 1;
         if(M.CaloJetTCHETag[i] > 10.2)
            TightBTagCount = TightBTagCount + 1;
      }

      FourVector PhotonP(0, 0, 0, 0);
      PhotonPT = 0;
      PhotonEta = 0;
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

      FourVector BJet1, BJet2;

      if(BJetSorterA.size() >= 2)
      {
         multimap<double, FourVector>::iterator iter = BJetSorterA.begin();
         BJet1 = iter->second;
         iter++;
         BJet2 = iter->second;
      }
      else if(BJetSorterA.size() == 1)
      {
         multimap<double, FourVector>::iterator iter = BJetSorterA.begin();
         BJet1 = iter->second;
         iter = BJetSorterB.begin();
         BJet2 = iter->second;
      }
      else
      {
         multimap<double, FourVector>::iterator iter = BJetSorterB.begin();
         BJet1 = iter->second;
         iter++;
         BJet2 = iter->second;
      }

      FourVector ISR(0, 0, 0, 0);
      for(multimap<double, FourVector>::iterator iter = BJetSorterA.begin(); iter != BJetSorterA.end(); iter++)
         ISR = ISR + iter->second;
      for(multimap<double, FourVector>::iterator iter = BJetSorterB.begin(); iter != BJetSorterB.end(); iter++)
         ISR = ISR + iter->second;
      ISR = ISR - BJet1 - BJet2;

      if(M.GoodMuonCount >= 1)
      {
         FourVector MuonP;
         MuonP.SetPtEtaPhi(M.Muon1PT, M.Muon1Eta, M.Muon1Phi);
         ISR = ISR + MuonP;
      }
      if(M.GoodMuonCount >= 2)
      {
         FourVector MuonP;
         MuonP.SetPtEtaPhi(M.Muon2PT, M.Muon2Eta, M.Muon2Phi);
         ISR = ISR + MuonP;
      }
      if(M.GoodMuonCount >= 3)
      {
         FourVector MuonP;
         MuonP.SetPtEtaPhi(M.Muon3PT, M.Muon3Eta, M.Muon3Phi);
         ISR = ISR + MuonP;
      }
      
      if(M.GoodElectronCount >= 1)
      {
         FourVector ElectronP;
         ElectronP.SetPtEtaPhi(M.Electron1PT, M.Electron1Eta, M.Electron1Phi);
         ISR = ISR + ElectronP;
      }
      if(M.GoodElectronCount >= 2)
      {
         FourVector ElectronP;
         ElectronP.SetPtEtaPhi(M.Electron2PT, M.Electron2Eta, M.Electron2Phi);
         ISR = ISR + ElectronP;
      }
      if(M.GoodElectronCount >= 3)
      {
         FourVector ElectronP;
         ElectronP.SetPtEtaPhi(M.Electron3PT, M.Electron3Eta, M.Electron3Phi);
         ISR = ISR + ElectronP;
      }

      MR11 = GetISR2011MR(BJet1, BJet2, ME, ISR, 11);
      R11 = GetISR2011R(BJet1, BJet2, ME, ISR, 11, 'g');

      OutputTree.Fill();
   }

   OutputTree.Write();
   HPileUpCount.Write();

   OutputFile.Close();

   return 0;
}







