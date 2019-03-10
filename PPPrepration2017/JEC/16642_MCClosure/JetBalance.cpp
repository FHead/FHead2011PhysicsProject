#include <iostream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "BasicUtilities.h"
#include "Messenger.h"

#include "JetCorrectorParameters.h"
#include "FactorizedJetCorrector.h"

class EventCoordinate;
class SimpleMessenger;
int main(int argc, char *argv[]);

class EventCoordinate
{
public:
   int Run;
   int Event;
   int Lumi;
public:
   EventCoordinate() : Run(0), Event(0), Lumi(0) {}
   EventCoordinate(int run, int event, int lumi) : Run(run), Event(event), Lumi(lumi) {}
   bool operator <(const EventCoordinate &other) const
   {
      if(Run < other.Run)   return true;
      if(Run > other.Run)   return false;
      
      if(Event < other.Event)   return true;
      if(Event > other.Event)   return false;
      
      if(Lumi < other.Lumi)   return true;
      if(Lumi > other.Lumi)   return false;

      return false;
   }
};

class SimpleMessenger
{
public:
   TTree *Tree;
   int Run;
   int Event;
   int Lumi;
   int JetCount;
   double PT[1000];
   double Eta[1000];
   double Phi[1000];
public:
   SimpleMessenger(TFile &File)
   {
      Tree = (TTree *)File.Get("T");
      Initialize();
   }
   SimpleMessenger(TFile *File)
   {
      if(File == NULL)
         Tree = NULL;
      else
      {
         Tree = (TTree *)File->Get("T");
         Initialize();
      }
   }
   SimpleMessenger(TTree *T)
   {
      Tree = T;
      Initialize();
   }
   bool Initialize()
   {
      if(Tree == NULL)
         return false;

      Tree->SetBranchAddress("Run", &Run);
      Tree->SetBranchAddress("Event", &Event);
      Tree->SetBranchAddress("Lumi", &Lumi);
      Tree->SetBranchAddress("JetCount", &JetCount);
      Tree->SetBranchAddress("PT", &PT);
      Tree->SetBranchAddress("Eta", &Eta);
      Tree->SetBranchAddress("Phi", &Phi);

      return true;
   }
   bool GetEntry(int iEntry)
   {
      if(Tree == NULL)
         return false;

      Tree->GetEntry(iEntry);

      return true;
   }
};

int main(int argc, char *argv[])
{
   string ForestFileName = "GeorgeSamples/Dijet80/HiForestAOD_Dijet_20171009.root";
   string OutputFileName = "Output.root";

   TFile *ForestFile = TFile::Open(ForestFileName.c_str());
   TFile HLTPFFile("PFJets.root");
   TFile HLTRawPFFile("PFRawJets.root");

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree Tree("T", "T");

   double GenEta, GenPhi, GenPT;
   Tree.Branch("GenEta",      &GenEta,      "GenEta/D");
   Tree.Branch("GenPhi",      &GenPhi,      "GenPhi/D");
   Tree.Branch("GenPT",       &GenPT,       "GenPT/D");
   double PFRawPT, PFCorrPT, PFHLTCorrPT, PFRawEta, PFRawPhi;
   Tree.Branch("PFRawEta",    &PFRawEta,    "PFRawEta/D");
   Tree.Branch("PFRawPhi",    &PFRawPhi,    "PFRawPhi/D");
   Tree.Branch("PFRawPT",     &PFRawPT,     "PFRawPT/D");
   Tree.Branch("PFCorrPT",    &PFCorrPT,    "PFCorrPT/D");
   Tree.Branch("PFHLTCorrPT", &PFHLTCorrPT, "PFCorrPT/D");
   double CaloRawPT, CaloCorrPT, CaloRawEta, CaloRawPhi;
   Tree.Branch("CaloRawEta",  &CaloRawEta,  "CaloRawEta/D");
   Tree.Branch("CaloRawPhi",  &CaloRawPhi,  "CaloRawPhi/D");
   Tree.Branch("CaloRawPT",   &CaloRawPT,   "CaloRawPT/D");
   Tree.Branch("CaloCorrPT",  &CaloCorrPT,  "CaloCorrPT/D");
   double HLTPFPT, HLTPFEta, HLTPFPhi, HLTPFDR;
   Tree.Branch("HLTPFEta",      &HLTPFEta,      "HLTPFEta/D");
   Tree.Branch("HLTPFPhi",      &HLTPFPhi,      "HLTPFPhi/D");
   Tree.Branch("HLTPFPT",       &HLTPFPT,       "HLTPFPT/D");
   Tree.Branch("HLTPFDR",       &HLTPFDR,       "HLTPFDR/D");
   double HLTRawPFPT, HLTCorrPFPT, HLTCorr2PFPT, HLTRawPFEta, HLTRawPFPhi, HLTRawPFDR;
   Tree.Branch("HLTRawPFEta",      &HLTRawPFEta,      "HLTRawPFEta/D");
   Tree.Branch("HLTRawPFPhi",      &HLTRawPFPhi,      "HLTRawPFPhi/D");
   Tree.Branch("HLTRawPFPT",       &HLTRawPFPT,       "HLTRawPFPT/D");
   Tree.Branch("HLTRawPFDR",       &HLTRawPFDR,       "HLTRawPFDR/D");
   Tree.Branch("HLTCorrPFPT",      &HLTCorrPFPT,      "HLTCorrPFPT/D");
   Tree.Branch("HLTCorr2PFPT",     &HLTCorr2PFPT,     "HLTCorr2PFPT/D");

   HiEventTreeMessenger MHiEvent(ForestFile);
   GGTreeMessenger MGG(ForestFile);
   SimpleMessenger MHLTPF(HLTPFFile);
   SimpleMessenger MHLTRawPF(HLTRawPFFile);

   map<EventCoordinate, int> HLTPFIndex, HLTRawPFIndex;

   int EntryCount = MHLTPF.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHLTPF.GetEntry(iE);
      HLTPFIndex.insert(pair<EventCoordinate, int>(EventCoordinate(MHLTPF.Run, MHLTPF.Event, MHLTPF.Lumi), iE));
   }
   EntryCount = MHLTRawPF.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHLTRawPF.GetEntry(iE);
      HLTRawPFIndex.insert(pair<EventCoordinate, int>(EventCoordinate(MHLTRawPF.Run, MHLTRawPF.Event, MHLTRawPF.Lumi), iE));
   }

   JetCorrectorParameters PFResJetPar("92X_upgrade2017_realistic_v11_L2L3Residual_AK4PF.txt");
   JetCorrectorParameters PFL3JetPar("92X_upgrade2017_realistic_v11_L3Absolute_AK4PF.txt");
   JetCorrectorParameters PFL2JetPar("92X_upgrade2017_realistic_v11_L2Relative_AK4PF.txt");
   JetCorrectorParameters PFL1JetPar("92X_upgrade2017_realistic_v11_L1FastJet_AK4PF.txt");
   JetCorrectorParameters PFHLTResJetPar("92X_upgrade2017_realistic_v11_L2L3Residual_AK4PFHLT.txt");
   JetCorrectorParameters PFHLTL3JetPar("92X_upgrade2017_realistic_v11_L3Absolute_AK4PFHLT.txt");
   JetCorrectorParameters PFHLTL2JetPar("92X_upgrade2017_realistic_v11_L2Relative_AK4PFHLT.txt");
   JetCorrectorParameters PFHLTL1JetPar("92X_upgrade2017_realistic_v11_L1FastJet_AK4PFHLT.txt");
   JetCorrectorParameters PFHLT2ResJetPar("92X_dataRun2_HLT_v7_L2L3Residual_AK4PFHLT.txt");
   JetCorrectorParameters PFHLT2L3JetPar("92X_dataRun2_HLT_v7_L3Absolute_AK4PFHLT.txt");
   JetCorrectorParameters PFHLT2L2JetPar("92X_dataRun2_HLT_v7_L2Relative_AK4PFHLT.txt");
   JetCorrectorParameters PFHLT2L1JetPar("92X_dataRun2_HLT_v7_L1FastJet_AK4PFHLT.txt");
   JetCorrectorParameters CaloResJetPar("92X_upgrade2017_realistic_v11_L2L3Residual_AK4Calo.txt");
   JetCorrectorParameters CaloL3JetPar("92X_upgrade2017_realistic_v11_L3Absolute_AK4Calo.txt");
   JetCorrectorParameters CaloL2JetPar("92X_upgrade2017_realistic_v11_L2Relative_AK4Calo.txt");
   JetCorrectorParameters CaloL1JetPar("92X_upgrade2017_realistic_v11_L1FastJet_AK4Calo.txt");

   vector<JetCorrectorParameters> PFPar;
   PFPar.push_back(PFL1JetPar);
   PFPar.push_back(PFL2JetPar);
   PFPar.push_back(PFL3JetPar);
   PFPar.push_back(PFResJetPar);
   vector<JetCorrectorParameters> PFHLTPar;
   PFHLTPar.push_back(PFHLTL1JetPar);
   PFHLTPar.push_back(PFHLTL2JetPar);
   PFHLTPar.push_back(PFHLTL3JetPar);
   PFHLTPar.push_back(PFHLTResJetPar);
   vector<JetCorrectorParameters> PFHLT2Par;
   PFHLT2Par.push_back(PFHLT2L1JetPar);
   PFHLT2Par.push_back(PFHLT2L2JetPar);
   PFHLT2Par.push_back(PFHLT2L3JetPar);
   PFHLT2Par.push_back(PFHLT2ResJetPar);
   vector<JetCorrectorParameters> CaloPar;
   CaloPar.push_back(CaloL1JetPar);
   CaloPar.push_back(CaloL2JetPar);
   CaloPar.push_back(CaloL3JetPar);
   CaloPar.push_back(CaloResJetPar);

   FactorizedJetCorrector PFJetCorrector(PFPar);
   FactorizedJetCorrector PFHLTJetCorrector(PFHLTPar);
   FactorizedJetCorrector PFHLT2JetCorrector(PFHLT2Par);
   FactorizedJetCorrector CaloJetCorrector(CaloPar);

   EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if((iE + 1) % 10000 == 0)
         cerr << "Processing event " << iE + 1 << "/" << EntryCount << endl;
   
      MHiEvent.GetEntry(iE);
      MGG.GetEntry(iE);

      bool HasHLT = false;
      bool HasHLTRaw = false;

      EventCoordinate C(MHiEvent.Run, MHiEvent.Event, MHiEvent.Lumi);

      if(HLTPFIndex.find(C) != HLTPFIndex.end() && HLTPFIndex[C] >= 0)
         HasHLT = true;
      if(HLTRawPFIndex.find(C) != HLTRawPFIndex.end() && HLTRawPFIndex[C] >= 0)
         HasHLTRaw = true;

      if(HasHLT == true)
         MHLTPF.GetEntry(HLTPFIndex[C]);
      if(HasHLTRaw == true)
         MHLTRawPF.GetEntry(HLTRawPFIndex[C]);

      vector<int> BestGenJetPFIndex(MGG.GenJetCount, -1);
      vector<int> BestPFJetGenIndex(MGG.PFJetCount, -1);
      vector<int> BestGenJetCaloIndex(MGG.GenJetCount, -1);
      vector<int> BestCaloJetGenIndex(MGG.CaloJetCount, -1);
      vector<int> BestGenJetHLTPFIndex(MGG.GenJetCount, -1);
      vector<int> BestHLTPFJetGenIndex;
      vector<int> BestGenJetHLTRawPFIndex(MGG.GenJetCount, -1);
      vector<int> BestHLTRawPFJetGenIndex;

      if(HasHLT == true)
         BestHLTPFJetGenIndex.resize(MHLTPF.JetCount, -1);
      if(HasHLTRaw == true)
         BestHLTRawPFJetGenIndex.resize(MHLTRawPF.JetCount, -1);

      for(int i = 0; i < MGG.GenJetCount; i++)
      {
         int BestIndex = -1;
         double BestDR2 = -1;
         for(int j = 0; j < MGG.PFJetCount; j++)
         {
            double DR2 = GetDR2((*MGG.GenJetEta)[i], (*MGG.GenJetPhi)[i], (*MGG.PFJetEta)[j], (*MGG.PFJetPhi)[j]);
            if(BestDR2 < 0 || DR2 < BestDR2)
            {
               BestDR2 = DR2;
               BestIndex = j;
            }
         }
         BestGenJetPFIndex[i] = BestIndex;
      }
      for(int i = 0; i < MGG.PFJetCount; i++)
      {
         int BestIndex = -1;
         double BestDR2 = -1;
         for(int j = 0; j < MGG.GenJetCount; j++)
         {
            double DR2 = GetDR2((*MGG.GenJetEta)[j], (*MGG.GenJetPhi)[j], (*MGG.PFJetEta)[i], (*MGG.PFJetPhi)[i]);
            if(BestDR2 < 0 || DR2 < BestDR2)
            {
               BestDR2 = DR2;
               BestIndex = j;
            }
         }
         BestPFJetGenIndex[i] = BestIndex;
      }
      for(int i = 0; i < MGG.GenJetCount; i++)
      {
         int BestIndex = -1;
         double BestDR2 = -1;
         for(int j = 0; j < MGG.CaloJetCount; j++)
         {
            double DR2 = GetDR2((*MGG.GenJetEta)[i], (*MGG.GenJetPhi)[i], (*MGG.CaloJetEta)[j], (*MGG.CaloJetPhi)[j]);
            if(BestDR2 < 0 || DR2 < BestDR2)
            {
               BestDR2 = DR2;
               BestIndex = j;
            }
         }
         BestGenJetCaloIndex[i] = BestIndex;
      }
      for(int i = 0; i < MGG.CaloJetCount; i++)
      {
         int BestIndex = -1;
         double BestDR2 = -1;
         for(int j = 0; j < MGG.GenJetCount; j++)
         {
            double DR2 = GetDR2((*MGG.GenJetEta)[j], (*MGG.GenJetPhi)[j], (*MGG.CaloJetEta)[i], (*MGG.CaloJetPhi)[i]);
            if(BestDR2 < 0 || DR2 < BestDR2)
            {
               BestDR2 = DR2;
               BestIndex = j;
            }
         }
         BestCaloJetGenIndex[i] = BestIndex;
      }
      if(HasHLT == true)
      {
         for(int i = 0; i < MGG.GenJetCount; i++)
         {
            int BestIndex = -1;
            double BestDR2 = -1;
            for(int j = 0; j < MHLTPF.JetCount; j++)
            {
               double DR2 = GetDR2((*MGG.GenJetEta)[i], (*MGG.GenJetPhi)[i], MHLTPF.Eta[j], MHLTPF.Phi[j]);
               if(BestDR2 < 0 || DR2 < BestDR2)
               {
                  BestDR2 = DR2;
                  BestIndex = j;
               }
            }
            BestGenJetHLTPFIndex[i] = BestIndex;
         }
         for(int i = 0; i < MHLTPF.JetCount; i++)
         {
            int BestIndex = -1;
            double BestDR2 = -1;
            for(int j = 0; j < MGG.GenJetCount; j++)
            {
               double DR2 = GetDR2((*MGG.GenJetEta)[j], (*MGG.GenJetPhi)[j], MHLTPF.Eta[i], MHLTPF.Phi[i]);
               if(BestDR2 < 0 || DR2 < BestDR2)
               {
                  BestDR2 = DR2;
                  BestIndex = j;
               }
            }
            BestHLTPFJetGenIndex[i] = BestIndex;
         }
      }
      if(HasHLTRaw == true)
      {
         for(int i = 0; i < MGG.GenJetCount; i++)
         {
            int BestIndex = -1;
            double BestDR2 = -1;
            for(int j = 0; j < MHLTRawPF.JetCount; j++)
            {
               double DR2 = GetDR2((*MGG.GenJetEta)[i], (*MGG.GenJetPhi)[i], MHLTRawPF.Eta[j], MHLTRawPF.Phi[j]);
               if(BestDR2 < 0 || DR2 < BestDR2)
               {
                  BestDR2 = DR2;
                  BestIndex = j;
               }
            }
            BestGenJetHLTRawPFIndex[i] = BestIndex;
         }
         for(int i = 0; i < MHLTRawPF.JetCount; i++)
         {
            int BestIndex = -1;
            double BestDR2 = -1;
            for(int j = 0; j < MGG.GenJetCount; j++)
            {
               double DR2 = GetDR2((*MGG.GenJetEta)[j], (*MGG.GenJetPhi)[j], MHLTRawPF.Eta[i], MHLTRawPF.Phi[i]);
               if(BestDR2 < 0 || DR2 < BestDR2)
               {
                  BestDR2 = DR2;
                  BestIndex = j;
               }
            }
            BestHLTRawPFJetGenIndex[i] = BestIndex;
         }
      }

      for(int i = 0; i < MGG.GenJetCount; i++)
      {
         GenPT = (*MGG.GenJetPT)[i];
         GenEta = (*MGG.GenJetEta)[i];
         GenPhi = (*MGG.GenJetPhi)[i];
         PFRawPT = -1;
         PFRawEta = 0;
         PFRawPhi = 0;
         PFCorrPT = -1;
         PFHLTCorrPT = -1;
         CaloRawPT = -1;
         CaloRawEta = 0;
         CaloRawPhi = 0;
         CaloCorrPT = -1;
         HLTPFPT = -1;
         HLTPFEta = -1;
         HLTPFPT = -1;
         HLTRawPFPT = -1;
         HLTRawPFEta = -1;
         HLTRawPFPhi = -1;
         HLTCorrPFPT = -1;

         int BestIndex = BestGenJetPFIndex[i];
         if(BestIndex >= 0 && BestPFJetGenIndex[BestIndex] == i)
         {
            PFRawPT = (*MGG.PFJetPT)[BestIndex];
            PFRawEta = (*MGG.PFJetEta)[BestIndex];
            PFRawPhi = (*MGG.PFJetPhi)[BestIndex];

            PFJetCorrector.setRho(1);
            PFJetCorrector.setJetA(0.4 * 0.4 * M_PI);
            PFJetCorrector.setJetEta(PFRawEta);
            PFJetCorrector.setJetPt(PFRawPT);
            PFCorrPT = PFRawPT * PFJetCorrector.getCorrection();
            
            PFHLTJetCorrector.setRho(1);
            PFHLTJetCorrector.setJetA(0.4 * 0.4 * M_PI);
            PFHLTJetCorrector.setJetEta(PFRawEta);
            PFHLTJetCorrector.setJetPt(PFRawPT);
            PFHLTCorrPT = PFRawPT * PFHLTJetCorrector.getCorrection();
         }

         BestIndex = BestGenJetCaloIndex[i];
         if(BestIndex >= 0 && BestCaloJetGenIndex[BestIndex] == i)
         {
            CaloRawPT = (*MGG.CaloJetPT)[BestIndex];
            CaloRawEta = (*MGG.CaloJetEta)[BestIndex];
            CaloRawPhi = (*MGG.CaloJetPhi)[BestIndex];

            CaloJetCorrector.setRho(1);
            CaloJetCorrector.setJetA(0.4 * 0.4 * M_PI);
            CaloJetCorrector.setJetEta(CaloRawEta);
            CaloJetCorrector.setJetPt(CaloRawPT);
            CaloCorrPT = CaloRawPT * CaloJetCorrector.getCorrection();
         }

         if(HasHLT == true)
         {
            BestIndex = BestGenJetHLTPFIndex[i];
            if(BestIndex >= 0 && BestHLTPFJetGenIndex[BestIndex] == i)
            {
               HLTPFPT = MHLTPF.PT[BestIndex];
               HLTPFEta = MHLTPF.Eta[BestIndex];
               HLTPFPhi = MHLTPF.Phi[BestIndex];
               HLTPFDR = sqrt(GetDR2(MHLTPF.Eta[BestIndex], MHLTPF.Phi[BestIndex], (*MGG.GenJetEta)[i], (*MGG.GenJetPhi)[i]));
            }
         }
         if(HasHLTRaw == true)
         {
            BestIndex = BestGenJetHLTRawPFIndex[i];
            if(BestIndex >= 0 && BestHLTRawPFJetGenIndex[BestIndex] == i)
            {
               HLTRawPFPT = MHLTRawPF.PT[BestIndex];
               HLTRawPFEta = MHLTRawPF.Eta[BestIndex];
               HLTRawPFPhi = MHLTRawPF.Phi[BestIndex];
               HLTRawPFDR = sqrt(GetDR2(MHLTRawPF.Eta[BestIndex], MHLTRawPF.Phi[BestIndex], (*MGG.GenJetEta)[i], (*MGG.GenJetPhi)[i]));

               PFHLTJetCorrector.setRho(1);
               PFHLTJetCorrector.setJetA(0.4 * 0.4 * M_PI);
               PFHLTJetCorrector.setJetEta(HLTRawPFEta);
               PFHLTJetCorrector.setJetPt(HLTRawPFPT);
               HLTCorrPFPT = HLTRawPFPT * PFHLTJetCorrector.getCorrection();

               PFHLT2JetCorrector.setRho(1);
               PFHLT2JetCorrector.setJetA(0.4 * 0.4 * M_PI);
               PFHLT2JetCorrector.setJetEta(HLTRawPFEta);
               PFHLT2JetCorrector.setJetPt(HLTRawPFPT);
               HLTCorr2PFPT = HLTRawPFPT * PFHLT2JetCorrector.getCorrection();
            }
         }

         Tree.Fill();
      }
   }

   Tree.Write();

   OutputFile.Close();

   ForestFile->Close();

   delete ForestFile;

   return 0;
}




