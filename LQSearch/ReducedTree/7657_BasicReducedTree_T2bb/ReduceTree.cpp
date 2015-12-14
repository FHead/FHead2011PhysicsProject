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

   int TargetM0 = 350;
   int TargetM12 = 100;

   TChain InputTree("LQ3Tree", "LQ3Tree");
   InputTree.AddFile(argv[1]);

   TreeRecord M;
   M.SetBranchAddress(&InputTree);

   TFile OutputFile(argv[2], "RECREATE");

   TH1D HPileUpCount("HPileUpCount", "Pileups", 202, -1.5, 200.5);

   TTree OutputTree("ReducedTree", "ReducedTree 7621");

   double MR, R, MR11, R11;
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");
   OutputTree.Branch("MR11", &MR11, "MR11/D");
   OutputTree.Branch("R11", &R11, "R11/D");

   int LooseBTagCount, MediumBTagCount, TightBTagCount;
   OutputTree.Branch("LooseBTagCount", &LooseBTagCount, "LooseBTagCount/I");
   OutputTree.Branch("MediumBTagCount", &MediumBTagCount, "MediumBTagCount/I");
   OutputTree.Branch("TightBTagCount", &TightBTagCount, "TightBTagCount/I");

   int PileupCount = 0;
   OutputTree.Branch("PileupCount", &PileupCount, "PileupCount/I");

   OutputTree.Branch("GoodMuonCountTight", &M.GoodMuonCountTight, "GoodMuonCountTight/I");
   OutputTree.Branch("GoodMuonCountLoose", &M.GoodMuonCountLoose, "GoodMuonCountLoose/I");
   OutputTree.Branch("GoodElectronCountTight", &M.GoodElectronCount80, "GoodElectronCountTight/I");
   OutputTree.Branch("GoodElectronCountLoose", &M.GoodElectronCount95, "GoodElectronCountLoose/I");

   OutputTree.Branch("MuonPT", &M.Muon1PT, "MuonPT/D");
   OutputTree.Branch("MuonEta", &M.Muon1Eta, "MuonEta/D");
   OutputTree.Branch("ElectronPT", &M.Electron1PT, "ElectronPT/D");
   OutputTree.Branch("ElectronEta", &M.Electron1Eta, "ElectronEta/D");
   OutputTree.Branch("Jet1PT", &M.CaloJetPT[0], "Jet1PT/D");
   OutputTree.Branch("Jet1Eta", &M.CaloJetEta[0], "Jet1Eta/D");

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << "...." << endl;

      InputTree.GetEntry(iEntry);

      if(M.m0 != TargetM0 || M.m12 != TargetM12)   // bad practice
         continue;

      if(M.PassNoiseFilter == false)
         continue;

      PileupCount = M.PileUp;
      HPileUpCount.Fill(M.PileUp);

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

      vector<FourVector> GoodJets;
      multimap<double, FourVector, greater<double> > BJetSorter;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 40)
            continue;

         FourVector JetP;
         JetP.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);
         GoodJets.push_back(JetP);

         BJetSorter.insert(pair<double, FourVector>(M.CaloJetTCHETag[i], JetP));
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

      multimap<double, FourVector>::iterator iter = BJetSorter.begin();
      FourVector BJet1 = iter->second;
      iter++;
      FourVector BJet2 = iter->second;

      FourVector ISR(0, 0, 0, 0);
      for(iter = BJetSorter.begin(); iter != BJetSorter.end(); iter++)
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







