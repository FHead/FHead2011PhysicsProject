#include <iostream>
#include <cmath>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TH2D.h"

#include "CommandLine.h"

#include "Messenger.h"
#include "BasicUtilities.h"
#include "SetStyle.h"

struct EventCoordinate;
int main(int argc, char *argv[]);

struct EventCoordinate
{
   long long Run;
   long long Lumi;
   long long Event;
   EventCoordinate(long long run, long long lumi, long long event)
   {
      Run = run;
      Lumi = lumi;
      Event = event;
   }
   bool operator <(const EventCoordinate &other) const
   {
      if(Run < other.Run)         return true;
      if(Run > other.Run)         return false;
      if(Lumi < other.Lumi)       return true;
      if(Lumi > other.Lumi)       return false;
      if(Event < other.Event)     return true;
      if(Event > other.Event)     return false;
      return false;
   }
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string HLTFileName = CL.Get("HLT");
   string OutputFileName = CL.Get("Output");
   string JetCollectionName = CL.Get("Jet", "akPu4PFJetAnalyzer/t");
   vector<string> TriggerList = CL.GetStringVector("Trigger");

   TFile InputFile(InputFileName.c_str());
   TFile HLTFile(HLTFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetCollectionName);
   GenParticleTreeMessenger MGen(InputFile);
   TrackTreeMessenger MTrack(InputFile);
   TriggerTreeMessenger MHLT(HLTFile, "hltbitanalysis/HltTree");
   vector<TriggerObjectTreeMessenger *> MObject;
   for(string Trigger : TriggerList)
   {
      Trigger.pop_back();
      MObject.push_back(new TriggerObjectTreeMessenger(HLTFile, "hltobject/" + Trigger));
   }

   if(MHiEvent.Tree == NULL)      return -1;
   if(MHLT.Tree == NULL)          return -1;

   double HFBins[101] = {0};
   for(int i = 0; i <= 100; i++)
      HFBins[i] = exp((log(7000) - log(8)) * i / 100 + log(8));

   vector<TH1D *> HDR, HResolution, HResolutionC0, HResolutionC1, HResolutionC2, HResolutionC3, HResolutionC4;
   vector<TProfile *> HMatchPT, HMatchEta;
   vector<TH2D *> HPTPT, HResolutionEta, HResolutionTrack, HResolutionLogHF;
   for(string Trigger : TriggerList)
   {
      HDR.push_back(new TH1D(Form("HDR_%s", Trigger.c_str()), ";#DeltaR;", 100, 0, 0.5));
      HMatchPT.push_back(new TProfile(Form("HMatchPT_%s", Trigger.c_str()), ";p_{T};Efficiency", 100, 0, 250));
      HMatchEta.push_back(new TProfile(Form("HMatchEta_%s", Trigger.c_str()), ";#eta;Efficiency", 100, -5.2, 5.2));
      HResolution.push_back(new TH1D(Form("HResolution_%s", Trigger.c_str()), ";HLT/Reco;", 100, 0, 2.5));
      HResolutionC0.push_back(new TH1D(Form("HResolutionC0_%s", Trigger.c_str()), ";HLT/Reco;", 100, 0, 2.5));
      HResolutionC1.push_back(new TH1D(Form("HResolutionC1_%s", Trigger.c_str()), ";HLT/Reco;", 100, 0, 2.5));
      HResolutionC2.push_back(new TH1D(Form("HResolutionC2_%s", Trigger.c_str()), ";HLT/Reco;", 100, 0, 2.5));
      HResolutionC3.push_back(new TH1D(Form("HResolutionC3_%s", Trigger.c_str()), ";HLT/Reco;", 100, 0, 2.5));
      HResolutionC4.push_back(new TH1D(Form("HResolutionC4_%s", Trigger.c_str()), ";HLT/Reco;", 100, 0, 2.5));
      HPTPT.push_back(new TH2D(Form("HPTPT_%s", Trigger.c_str()), ";HLT;Reco", 100, 0, 250, 100, 0, 250));
      HResolutionEta.push_back(new TH2D(Form("HResolutionEta_%s", Trigger.c_str()), ";#eta;HLT/Reco", 100, -5.2, 5.2, 100, 0, 2.5));
      HResolutionTrack.push_back(new TH2D(Form("HResolutionTrack_%s", Trigger.c_str()), ";track count;HLT/Reco", 100, 0, 18000, 100, 0, 2.5));
      HResolutionLogHF.push_back(new TH2D(Form("HResolutionLogHF_%s", Trigger.c_str()), ";HF Energy;HLT/Reco", 100, HFBins, 100, 0, 2.5));
   }

   map<EventCoordinate, int> HLTIndex;
   for(int iE = 0; iE < MHLT.Tree->GetEntries(); iE++)
   {
      MHLT.GetEntry(iE);
      HLTIndex.insert(pair<EventCoordinate, int>(EventCoordinate(MHLT.Run, MHLT.Lumi, MHLT.Event), iE));
   }

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHiEvent.GetEntry(iE);
      MGen.GetEntry(iE);
      MJet.GetEntry(iE);
      MTrack.GetEntry(iE);

      bool HasMuon = false, HasElectron = false;
      for(int ID : (*MGen.ID))
      {
         if(ID == 13 || ID == -13)
            HasMuon = true;
         if(ID == 11 || ID == -11)
            HasElectron = true;
      }
      if(HasMuon == true || HasElectron == true)
         continue;

      EventCoordinate E(MHiEvent.Run, MHiEvent.Lumi, MHiEvent.Event);
      if(HLTIndex.find(E) == HLTIndex.end())   // event not run in the HLT job, skip
         continue;

      MHLT.GetEntry(HLTIndex[E]);
      for(auto Messenger : MObject)
         if(Messenger != NULL)
            Messenger->GetEntry(HLTIndex[E]);

      int BestJetIndex = -1;
      for(int i = 0; i < MJet.JetCount; i++)
      {
         if(fabs(MJet.JetEta[i]) > 5.1)
            continue;
         if(BestJetIndex < 0 || MJet.JetPT[i] > MJet.JetPT[BestJetIndex])
            BestJetIndex = i;
      }
      if(BestJetIndex < 0)   // no jets??
         continue;

      for(int i = 0; i < (int)TriggerList.size(); i++)
      {
         auto M = MObject[i];
         if(M == NULL)
            continue;

         int BestIndex = -1;
         double BestDR = -1;
         for(int j = 0; j < M->PT->size(); j++)
         {
            double DR = GetDR((*M->Eta)[j], (*M->Phi)[j], MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
            if(BestDR < 0 || DR < BestDR)
            {
               BestDR = DR;
               BestIndex = j;
            }
         }

         if(HDR[i] != NULL)         HDR[i]->Fill(BestDR);
         if(HMatchPT[i] != NULL)    HMatchPT[i]->Fill(MJet.JetPT[BestJetIndex], BestDR > 0 && BestDR < 0.2);
         if(HMatchEta[i] != NULL)   HMatchEta[i]->Fill(MJet.JetEta[BestJetIndex], BestDR > 0 && BestDR < 0.2);

         if(BestDR > 0 && BestDR < 0.2)
         {
            if(HResolution[i] != NULL)
               HResolution[i]->Fill((*M->PT)[BestIndex] / MJet.JetPT[BestJetIndex]);
            if(HResolutionC4[i] != NULL && MHiEvent.hiHF <= 63.26)
               HResolutionC4[i]->Fill((*M->PT)[BestIndex] / MJet.JetPT[BestJetIndex]);
            else if(HResolutionC3[i] != NULL && MHiEvent.hiHF <= 357.5)
               HResolutionC3[i]->Fill((*M->PT)[BestIndex] / MJet.JetPT[BestJetIndex]);
            else if(HResolutionC2[i] != NULL && MHiEvent.hiHF <= 1028)
               HResolutionC2[i]->Fill((*M->PT)[BestIndex] / MJet.JetPT[BestJetIndex]);
            else if(HResolutionC1[i] != NULL && MHiEvent.hiHF <= 2505)
               HResolutionC1[i]->Fill((*M->PT)[BestIndex] / MJet.JetPT[BestJetIndex]);
            else if(HResolutionC0[i] != NULL)
               HResolutionC0[i]->Fill((*M->PT)[BestIndex] / MJet.JetPT[BestJetIndex]);
            if(HPTPT[i] != NULL)
               HPTPT[i]->Fill((*M->PT)[BestIndex], MJet.JetPT[BestJetIndex]);
            if(HResolutionEta[i] != NULL)
               HResolutionEta[i]->Fill(MJet.JetEta[BestJetIndex], (*M->PT)[BestIndex] / MJet.JetPT[BestJetIndex]);
            if(HResolutionTrack[i] != NULL)
               HResolutionTrack[i]->Fill(MTrack.TrackCount, (*M->PT)[BestIndex] / MJet.JetPT[BestJetIndex]);
            if(HResolutionLogHF[i] != NULL && MHiEvent.hiHF > 0)
               HResolutionLogHF[i]->Fill(MHiEvent.hiHF, (*M->PT)[BestIndex] / MJet.JetPT[BestJetIndex]);
         }
      }
   }

   for(auto Messenger : MObject)
      if(Messenger != NULL)
         delete Messenger;

   for(auto H : HDR)                if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HMatchPT)           if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HMatchEta)          if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HResolution)        if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HResolutionC0)      if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HResolutionC1)      if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HResolutionC2)      if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HResolutionC3)      if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HResolutionC4)      if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HPTPT)              if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HResolutionEta)     if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HResolutionTrack)   if(H != NULL)  H->SetStats(0), H->Write();
   for(auto H : HResolutionLogHF)   if(H != NULL)  H->SetStats(0), H->Write();

   OutputFile.Close();
   HLTFile.Close();
   InputFile.Close();

   return 0;
}

