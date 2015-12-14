#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

#include "TChain.h"
#include "TH1D.h"
#include "TFile.h"

#include "TauHelperFunctions2.h"

#include "ChainAll.h"
#include "ReadLQ3Tree.h"

int main();
void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min = 0.25);

int main()
{
   CheckSampleEfficiency("T2bbList", 1, 0.25);

   return 0;
}

void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min)
{
   // TChain Tree("LQ3Tree", "LQ3Tree");
   // Tree.AddFile(InputFile.c_str());

   TChain *Tree = ChainAll(InputFile.c_str(), "LQ3Tree");

   TreeRecord M;
   M.SetBranchAddress(Tree);

   Tree->SetBranchStatus("PFJet*", false);
   Tree->SetBranchStatus("CaloJetCSVTag", false);
   Tree->SetBranchStatus("CaloJetCSVMTag", false);
   Tree->SetBranchStatus("CaloJetTCHPTag", false);

   map<pair<int, int>, double> AllEvents;
   map<pair<int, int>, double> PassedEvents;
   
   map<pair<int, int>, TH1D *> AllEventsPT;
   map<pair<int, int>, TH1D *> PassedEventsPT;
   map<pair<int, int>, TH1D *> HMR;
   map<pair<int, int>, TH1D *> HR2;
   map<pair<int, int>, TH1D *> HR;
   map<pair<int, int>, TH1D *> HMR_R2020;
   map<pair<int, int>, TH1D *> HR2_MR400;
   map<pair<int, int>, TH1D *> HR_MR400;
   map<pair<int, int>, TH1D *> HMET_Used;
   map<pair<int, int>, TH1D *> HMET;

   TFile F("Output.root", "RECREATE");

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      pair<int, int> Model((int)(M.m0 + 0.0001), (int)(M.m12 + 0.0001));
      if(AllEvents.find(Model) == AllEvents.end())
      {
         AllEvents.insert(pair<pair<int, int>, double>(Model, 0));
         PassedEvents.insert(pair<pair<int, int>, double>(Model, 0));
         
         AllEventsPT.insert(pair<pair<int, int>, TH1D *>(Model, NULL));
         PassedEventsPT.insert(pair<pair<int, int>, TH1D *>(Model, NULL));
         HMR.insert(pair<pair<int, int>, TH1D *>(Model, NULL));
         HR2.insert(pair<pair<int, int>, TH1D *>(Model, NULL));
         HR.insert(pair<pair<int, int>, TH1D *>(Model, NULL));
         HMR_R2020.insert(pair<pair<int, int>, TH1D *>(Model, NULL));
         HR2_MR400.insert(pair<pair<int, int>, TH1D *>(Model, NULL));
         HR_MR400.insert(pair<pair<int, int>, TH1D *>(Model, NULL));
         HMET_Used.insert(pair<pair<int, int>, TH1D *>(Model, NULL));
         HMET.insert(pair<pair<int, int>, TH1D *>(Model, NULL));

         AllEventsPT[Model] = new TH1D(Form("AllEventsPT_%04d_%04d", Model.first, Model.second),
            Form("PT of all events for mass point (%d, %d)", Model.first, Model.second),
            100, 0, 1000);
         PassedEventsPT[Model] = new TH1D(Form("PassedEventsPT_%04d_%04d", Model.first, Model.second),
            Form("PT of passed events for mass point (%d, %d)", Model.first, Model.second),
            100, 0, 1000);
         HMR[Model] = new TH1D(Form("HMR_%04d_%04d", Model.first, Model.second),
            Form("MR distribution for mass point(%d, %d)", Model.first, Model.second),
            25, 0, 1500);
         HR2[Model] = new TH1D(Form("HR2_%04d_%04d", Model.first, Model.second),
            Form("R^{2} distribution for mass point(%d, %d)", Model.first, Model.second),
            25, 0, 1.5);
         HR[Model] = new TH1D(Form("HR_%04d_%04d", Model.first, Model.second),
            Form("R distribution for mass point(%d, %d)", Model.first, Model.second),
            25, 0, 1.5);
         HMR_R2020[Model] = new TH1D(Form("HMR_R2020_%04d_%04d", Model.first, Model.second),
            Form("MR distribution (R^{2} > 0.14) for mass point(%d, %d)", Model.first, Model.second),
            25, 0, 1500);
         HR2_MR400[Model] = new TH1D(Form("HR2_MR400_%04d_%04d", Model.first, Model.second),
            Form("R^{2} distribution (MR > 400) for mass point(%d, %d)", Model.first, Model.second),
            25, 0, 1.5);
         HR_MR400[Model] = new TH1D(Form("HR_MR400_%04d_%04d", Model.first, Model.second),
            Form("R distribution (MR > 400) for mass point(%d, %d)", Model.first, Model.second),
            25, 0, 1.5);
         HMET_Used[Model] = new TH1D(Form("HMET_Used_%04d_%04d", Model.first, Model.second),
            Form("MET distribution (MR > 400 and R^{2} > 0.25) for mass point(%d, %d)", Model.first, Model.second),
            25, 0, 1500);
         HMET[Model] = new TH1D(Form("HMET_%04d_%04d", Model.first, Model.second),
            Form("MET distribution for mass point(%d, %d)", Model.first, Model.second),
            25, 0, 1500);
      }

      int CaloJetCount60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] <= -3 || M.CaloJetEta[i] >= 3)
            continue;

         if(M.CaloJetPT[i] > 60)
            CaloJetCount60 = CaloJetCount60 + 1;
      }

      int JetPassBTagLoose = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] <= -3 || M.CaloJetEta[i] >= 3)
            continue;
         if(M.CaloJetTCHETag[i] <= 3.3)
            continue;

         if(M.CaloJetPT[i] > 80)
            JetPassBTagLoose = JetPassBTagLoose + 1;
      }

      vector<FourVector> CaloJets;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         if(M.CaloJetPT[i] > 40)
            CaloJets.push_back(NewJet);
      }

      vector<FourVector> Hemispheres;
      if(CaloJets.size() >= 2)
         Hemispheres = SplitIntoGroups(CaloJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      PFMET[0] = PFMET.GetPT();

      double MR = 0;
      double R = 0;

      if(Hemispheres.size() == 2)
      {
         MR = Get2011MR(Hemispheres[0], Hemispheres[1]);
         R = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      }

      double R2 = R * R;

      FourVector SB1P, SB2P;
      SB1P.SetPtEtaPhi(M.SB1PT, M.SB1Eta, M.SB1Phi);
      SB2P.SetPtEtaPhi(M.SB2PT, M.SB2Eta, M.SB2Phi);
      double HardProcessPT = (SB1P + SB2P).GetPT();

      AllEvents[Model] = AllEvents[Model] + 1;
      AllEventsPT[Model]->Fill(HardProcessPT);

      if(M.GoodElectronCount == 0 && M.GoodMuonCount == 0 && CaloJetCount60 >= 2
         && JetPassBTagLoose >= 2 && R2 >= R2Min && MR >= 400)
      {
         PassedEvents[Model] = PassedEvents[Model] + 1;
         PassedEventsPT[Model]->Fill(HardProcessPT);
      }

      HMR[Model]->Fill(MR);
      HR2[Model]->Fill(R2);
      HR[Model]->Fill(R);
      if(R2 > 0.20)
         HMR_R2020[Model]->Fill(MR);
      if(MR > 400)
         HR2_MR400[Model]->Fill(R2);
      if(MR > 400)
         HR_MR400[Model]->Fill(R);
      if(R2 > 0.25 && MR > 400)
         HMET_Used[Model]->Fill(PFMET.GetPT());
      HMET[Model]->Fill(PFMET.GetPT());
   }
   
   for(map<pair<int, int>, double>::iterator iter = AllEvents.begin(); iter != AllEvents.end(); iter++)
   {
      AllEventsPT[iter->first]->Write();
      PassedEventsPT[iter->first]->Write();
      HMR[iter->first]->Write();
      HR2[iter->first]->Write();
      HR[iter->first]->Write();
      HMR_R2020[iter->first]->Write();
      HR2_MR400[iter->first]->Write();
      HR_MR400[iter->first]->Write();
      HMET_Used[iter->first]->Write();
      HMET[iter->first]->Write();
   }

   for(map<pair<int, int>, double>::iterator iter = AllEvents.begin(); iter != AllEvents.end(); iter++)
   {
      delete AllEventsPT[iter->first];
      delete PassedEventsPT[iter->first];
      delete HMR[iter->first];
      delete HR2[iter->first];
      delete HR[iter->first];
      delete HMR_R2020[iter->first];
      delete HR2_MR400[iter->first];
      delete HR_MR400[iter->first];
      delete HMET_Used[iter->first];
      delete HMET[iter->first];
   }
   
   F.Close();
}





