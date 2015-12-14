#include <algorithm>
#include <iostream>
#include <fstream>
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

struct Event;
int main(int argc, char *argv[]);
vector<Event> ReadBadList(string FileName = "BadList");

struct Event
{
public:
   long long RunNumber;
   long long EventNumber;
   long long LumiSection;
public:
   bool operator <(const Event other) const
   {
      if(RunNumber < other.RunNumber)   return true;
      if(RunNumber > other.RunNumber)   return false;

      if(EventNumber < other.EventNumber)   return true;
      if(EventNumber > other.EventNumber)   return false;

      if(LumiSection < other.LumiSection)   return true;
      if(LumiSection > other.LumiSection)   return false;

      return false;
   }
};

int main(int argc, char *argv[])
{
   if(argc <= 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputFile BadList" << endl;
      return -1;
   }

   vector<Event> BadList = ReadBadList(argv[3]);
   cout << "Number of bad events read " << BadList.size() << endl;

   TChain InputTree("LQ3Tree", "LQ3Tree");
   InputTree.AddFile(argv[1]);

   TreeRecord M;
   M.SetBranchAddress(&InputTree);

   TFile OutputFile(argv[2], "RECREATE");

   TH1D HPileUpCount("HPileUpCount", "Pileups", 202, -1.5, 200.5);

   TTree OutputTree("ReducedTree", "TriggerTree 7764");

   double MR, R, MR11, R11, MRPhoton, RPhoton, MRL, RL, MRJJ, RJJ;
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");
   OutputTree.Branch("MR11", &MR11, "MR11/D");
   OutputTree.Branch("R11", &R11, "R11/D");
   OutputTree.Branch("MRPhoton", &MRPhoton, "MRPhoton/D");
   OutputTree.Branch("RPhoton", &RPhoton, "RPhoton/D");
   OutputTree.Branch("MRL", &MRL, "MRL/D");
   OutputTree.Branch("RL", &RL, "RL/D");
   OutputTree.Branch("MRJJ", &MRJJ, "MRJJ/D");
   OutputTree.Branch("RJJ", &RJJ, "RJJ/D");

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

   OutputTree.Branch("PassR014MR150", &M.PassR014MR150, "PassR014MR150/O");
   OutputTree.Branch("PassR020MR150", &M.PassR020MR150, "PassR020MR150/O");
   OutputTree.Branch("PassR025MR150", &M.PassR025MR150, "PassR025MR150/O");
   OutputTree.Branch("PassR020MR500", &M.PassR020MR500, "PassR020MR500/O");
   OutputTree.Branch("PassR020MR550", &M.PassR020MR550, "PassR020MR550/O");
   OutputTree.Branch("PassR023MR550", &M.PassR023MR550, "PassR023MR550/O");
   OutputTree.Branch("PassR025MR400", &M.PassR025MR400, "PassR025MR400/O");
   OutputTree.Branch("PassR025MR450", &M.PassR025MR450, "PassR025MR450/O");
   OutputTree.Branch("PassR029MR450", &M.PassR029MR450, "PassR029MR450/O");
   OutputTree.Branch("PassR033MR300", &M.PassR033MR300, "PassR033MR300/O");
   OutputTree.Branch("PassR033MR350", &M.PassR033MR350, "PassR033MR350/O");
   OutputTree.Branch("PassR036MR350", &M.PassR036MR350, "PassR036MR350/O");
   OutputTree.Branch("PassR038MR200", &M.PassR038MR200, "PassR038MR200/O");
   OutputTree.Branch("PassR038MR250", &M.PassR038MR250, "PassR038MR250/O");
   OutputTree.Branch("PassR042MR250", &M.PassR042MR250, "PassR042MR250/O");

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << "...." << endl;

      InputTree.GetEntry(iEntry);

      if(M.PassNoiseFilter == false)
         continue;

      Event Record;
      Record.RunNumber = M.RunNumber;
      Record.EventNumber = M.EventNumber;
      Record.LumiSection = M.LumiSection;

      if(binary_search(BadList.begin(), BadList.end(), Record) == true)
      {
         cout << "Run " << Record.RunNumber << " Event " << Record.EventNumber
            << " Lumi " << Record.LumiSection << " rejected because of noise" << endl;
         continue;
      }

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
      multimap<double, FourVector, greater<double> > JetSorter;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 40)
            continue;

         FourVector JetP;
         JetP.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         GoodJets.push_back(JetP);
         JetSorter.insert(pair<double, FourVector>(JetP.GetPT(), JetP));

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

      MRJJ = 0;
      RJJ = 0;
      if(JetSorter.size() >= 2)
      {
         multimap<double, FourVector, greater<double> >::iterator JetIterator = JetSorter.begin();
         FourVector Jet1 = JetIterator->second;
         JetIterator++;
         FourVector Jet2 = JetIterator->second;

         MRJJ = Get2011MR(Jet1, Jet2);
         RJJ = Get2011R(Jet1, Jet2, ME);
      }

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

      vector<FourVector> GoodElectrons;
      FourVector MEL = ME;

      if(M.GoodMuonCount >= 1)
      {
         FourVector MuonP;
         MuonP.SetPtEtaPhi(M.Muon1PT, M.Muon1Eta, M.Muon1Phi);
         ISR = ISR + MuonP;
         if(MuonP.GetPT() > 20)
            MEL = MEL + MuonP;
      }
      if(M.GoodMuonCount >= 2)
      {
         FourVector MuonP;
         MuonP.SetPtEtaPhi(M.Muon2PT, M.Muon2Eta, M.Muon2Phi);
         ISR = ISR + MuonP;
         if(MuonP.GetPT() > 20)
            MEL = MEL + MuonP;
      }
      if(M.GoodMuonCount >= 3)
      {
         FourVector MuonP;
         MuonP.SetPtEtaPhi(M.Muon3PT, M.Muon3Eta, M.Muon3Phi);
         ISR = ISR + MuonP;
         if(MuonP.GetPT() > 20)
            MEL = MEL + MuonP;
      }
      
      if(M.GoodElectronCount >= 1)
      {
         FourVector ElectronP;
         ElectronP.SetPtEtaPhi(M.Electron1PT, M.Electron1Eta, M.Electron1Phi);
         ISR = ISR + ElectronP;
         if(ElectronP.GetPT() > 20)
         {
            MEL = MEL + ElectronP;
            GoodElectrons.push_back(ElectronP);
         }
      }
      if(M.GoodElectronCount >= 2)
      {
         FourVector ElectronP;
         ElectronP.SetPtEtaPhi(M.Electron2PT, M.Electron2Eta, M.Electron2Phi);
         ISR = ISR + ElectronP;
         if(ElectronP.GetPT() > 20)
         {
            MEL = MEL + ElectronP;
            GoodElectrons.push_back(ElectronP);
         }
      }
      if(M.GoodElectronCount >= 3)
      {
         FourVector ElectronP;
         ElectronP.SetPtEtaPhi(M.Electron3PT, M.Electron3Eta, M.Electron3Phi);
         ISR = ISR + ElectronP;
         if(ElectronP.GetPT() > 20)
         {
            MEL = MEL + ElectronP;
            GoodElectrons.push_back(ElectronP);
         }
      }

      MR11 = GetISR2011MR(BJet1, BJet2, ME, ISR, 11);
      R11 = GetISR2011R(BJet1, BJet2, ME, ISR, 11, 'g');
      
      vector<FourVector> GoodJetsL;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 40)
            continue;

         FourVector JetP;
         JetP.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         GoodJets.push_back(JetP);

         bool CloseToElectron = false;
         for(int j = 0; j < (int)GoodElectrons.size(); j++)
         {
            if(GetDR(GoodElectrons[j], JetP) < 0.3)
               CloseToElectron = true;
         }

         if(CloseToElectron == false)
            GoodJetsL.push_back(JetP);
      }
      vector<FourVector> GroupsL = SplitIntoGroups(GoodJetsL, true);

      MRL = Get2011MR(GroupsL[0], GroupsL[1]);
      RL = Get2011R(GroupsL[0], GroupsL[1], MEL);

      OutputTree.Fill();
   }

   OutputTree.Write();
   HPileUpCount.Write();

   OutputFile.Close();

   return 0;
}

vector<Event> ReadBadList(string FileName)
{
   vector<Event> List;

   ifstream in(FileName.c_str());

   while(in)
   {
      long long RunNumber = 0;
      long long EventNumber = 0;
      long long LumiSection = 0;

      in >> RunNumber >> LumiSection >> EventNumber;

      if(RunNumber == 0)
         continue;

      Event Record;
      Record.RunNumber = RunNumber;
      Record.EventNumber = EventNumber;
      Record.LumiSection = LumiSection;

      List.push_back(Record);
   }

   sort(List.begin(), List.end());

   in.close();

   return List;
}






