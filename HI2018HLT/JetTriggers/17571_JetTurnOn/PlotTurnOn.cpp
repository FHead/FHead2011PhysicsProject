#include <iostream>
#include <map>
#include <cassert>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "CommandLine.h"

#include "Messenger.h"

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
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string HLTFileName = CL.Get("HLT");
   string OutputFileName = CL.Get("Output");
   string JetCollectionName = CL.Get("Jet");
   vector<string> TriggerList = CL.GetStringVector("Trigger");
   bool UseRefPT = CL.GetBool("UseRefPT", false);

   TFile InputFile(InputFileName.c_str());
   TFile HLTFile(HLTFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetCollectionName);
   GenParticleTreeMessenger MGen(InputFile);
   TriggerTreeMessenger MHLT(HLTFile, "hltbitanalysis/HltTree");
   
   assert(MHiEvent.Tree != NULL);
   assert(MHLT.Tree != NULL);

   map<EventCoordinate, int> HLTIndex;
   for(int iE = 0; iE < MHLT.Tree->GetEntries(); iE++)
   {
      MHLT.GetEntry(iE);
      HLTIndex.insert(pair<EventCoordinate, int>(EventCoordinate(MHLT.Run, MHLT.Lumi, MHLT.Event), iE));
   }

   TH1D HJetPT("HJetPT", ";PT;", 75, 0, 250);
   TH1D HJetPTC0("HJetPTC0", ";PT;", 75, 0, 250);
   TH1D HJetPTC1("HJetPTC1", ";PT;", 75, 0, 250);
   TH1D HJetPTC2("HJetPTC2", ";PT;", 75, 0, 250);
   TH1D HJetPTC3("HJetPTC3", ";PT;", 75, 0, 250);
   TH1D HJetPTC4("HJetPTC4", ";PT;", 75, 0, 250);
   TH1D HFJetPT("HFJetPT", ";PT;", 25, 0, 250);
   TH1D HFJetPTC0("HFJetPTC0", ";PT;", 25, 0, 250);
   TH1D HFJetPTC1("HFJetPTC1", ";PT;", 25, 0, 250);
   TH1D HFJetPTC2("HFJetPTC2", ";PT;", 25, 0, 250);
   TH1D HFJetPTC3("HFJetPTC3", ";PT;", 25, 0, 250);
   TH1D HFJetPTC4("HFJetPTC4", ";PT;", 25, 0, 250);
   TH1D HForwardJetPT("HForwardJetPT", ";PT;", 75, 0, 250);
   TH1D HForwardJetPTC0("HForwardJetPTC0", ";PT;", 75, 0, 250);
   TH1D HForwardJetPTC1("HForwardJetPTC1", ";PT;", 75, 0, 250);
   TH1D HForwardJetPTC2("HForwardJetPTC2", ";PT;", 75, 0, 250);
   TH1D HForwardJetPTC3("HForwardJetPTC3", ";PT;", 75, 0, 250);
   TH1D HForwardJetPTC4("HForwardJetPTC4", ";PT;", 75, 0, 250);
   TH1D HCentralJetPT("HCentralJetPT", ";PT;", 75, 0, 250);
   TH1D HCentralJetPTC0("HCentralJetPTC0", ";PT;", 75, 0, 250);
   TH1D HCentralJetPTC1("HCentralJetPTC1", ";PT;", 75, 0, 250);
   TH1D HCentralJetPTC2("HCentralJetPTC2", ";PT;", 75, 0, 250);
   TH1D HCentralJetPTC3("HCentralJetPTC3", ";PT;", 75, 0, 250);
   TH1D HCentralJetPTC4("HCentralJetPTC4", ";PT;", 75, 0, 250);
   TH1D HVeryCentralJetPT("HVeryCentralJetPT", ";PT;", 25, 0, 250);
   TH1D HVeryCentralJetPTC0("HVeryCentralJetPTC0", ";PT;", 25, 0, 250);
   TH1D HVeryCentralJetPTC1("HVeryCentralJetPTC1", ";PT;", 25, 0, 250);
   TH1D HVeryCentralJetPTC2("HVeryCentralJetPTC2", ";PT;", 25, 0, 250);
   TH1D HVeryCentralJetPTC3("HVeryCentralJetPTC3", ";PT;", 25, 0, 250);
   TH1D HVeryCentralJetPTC4("HVeryCentralJetPTC4", ";PT;", 25, 0, 250);
   vector<TH1D *> HJetPTs, HJetPTsC0, HJetPTsC1, HJetPTsC2, HJetPTsC3, HJetPTsC4;
   vector<TH1D *> HFJetPTs, HFJetPTsC0, HFJetPTsC1, HFJetPTsC2, HFJetPTsC3, HFJetPTsC4;
   vector<TH1D *> HForwardJetPTs, HForwardJetPTsC0, HForwardJetPTsC1, HForwardJetPTsC2, HForwardJetPTsC3, HForwardJetPTsC4;
   vector<TH1D *> HCentralJetPTs, HCentralJetPTsC0, HCentralJetPTsC1, HCentralJetPTsC2, HCentralJetPTsC3, HCentralJetPTsC4;
   vector<TH1D *> HVeryCentralJetPTs, HVeryCentralJetPTsC0, HVeryCentralJetPTsC1, HVeryCentralJetPTsC2, HVeryCentralJetPTsC3, HVeryCentralJetPTsC4;
   for(int i = 0; i < (int)TriggerList.size(); i++)
   {
      HJetPTs.push_back(new TH1D(Form("HJetPT_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HJetPTsC0.push_back(new TH1D(Form("HJetPTC0_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HJetPTsC1.push_back(new TH1D(Form("HJetPTC1_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HJetPTsC2.push_back(new TH1D(Form("HJetPTC2_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HJetPTsC3.push_back(new TH1D(Form("HJetPTC3_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HJetPTsC4.push_back(new TH1D(Form("HJetPTC4_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HFJetPTs.push_back(new TH1D(Form("HFJetPT_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HFJetPTsC0.push_back(new TH1D(Form("HFJetPTC0_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HFJetPTsC1.push_back(new TH1D(Form("HFJetPTC1_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HFJetPTsC2.push_back(new TH1D(Form("HFJetPTC2_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HFJetPTsC3.push_back(new TH1D(Form("HFJetPTC3_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HFJetPTsC4.push_back(new TH1D(Form("HFJetPTC4_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HForwardJetPTs.push_back(new TH1D(Form("HForwardJetPT_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HForwardJetPTsC0.push_back(new TH1D(Form("HForwardJetPTC0_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HForwardJetPTsC1.push_back(new TH1D(Form("HForwardJetPTC1_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HForwardJetPTsC2.push_back(new TH1D(Form("HForwardJetPTC2_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HForwardJetPTsC3.push_back(new TH1D(Form("HForwardJetPTC3_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HForwardJetPTsC4.push_back(new TH1D(Form("HForwardJetPTC4_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HCentralJetPTs.push_back(new TH1D(Form("HCentralJetPT_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HCentralJetPTsC0.push_back(new TH1D(Form("HCentralJetPTC0_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HCentralJetPTsC1.push_back(new TH1D(Form("HCentralJetPTC1_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HCentralJetPTsC2.push_back(new TH1D(Form("HCentralJetPTC2_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HCentralJetPTsC3.push_back(new TH1D(Form("HCentralJetPTC3_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HCentralJetPTsC4.push_back(new TH1D(Form("HCentralJetPTC4_%s", TriggerList[i].c_str()), ";PT;", 75, 0, 250));
      HVeryCentralJetPTs.push_back(new TH1D(Form("HVeryCentralJetPT_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HVeryCentralJetPTsC0.push_back(new TH1D(Form("HVeryCentralJetPTC0_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HVeryCentralJetPTsC1.push_back(new TH1D(Form("HVeryCentralJetPTC1_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HVeryCentralJetPTsC2.push_back(new TH1D(Form("HVeryCentralJetPTC2_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HVeryCentralJetPTsC3.push_back(new TH1D(Form("HVeryCentralJetPTC3_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
      HVeryCentralJetPTsC4.push_back(new TH1D(Form("HVeryCentralJetPTC4_%s", TriggerList[i].c_str()), ";PT;", 25, 0, 250));
   }

   float *MJetPT = MJet.JetPT;
   if(UseRefPT == true)
      MJetPT = MJet.RefPT;

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHiEvent.GetEntry(iE);
      MGen.GetEntry(iE);
      MJet.GetEntry(iE);
      
      bool HasMuon = false, HasElectron = false;
      for(int ID : (*MGen.ID))
      {
         if(ID == 13 || ID == -13)
            HasMuon = true;
         if(ID == 11 || ID == -11)
            HasElectron = true;
      }
      if(HasMuon == true)
         continue;

      EventCoordinate E(MHiEvent.Run, MHiEvent.Lumi, MHiEvent.Event);
      if(HLTIndex.find(E) == HLTIndex.end())   // event not run in the HLT job, skip
         continue;

      int CBin = 0;
      if(MHiEvent.hiHF < 63.26)        CBin = 4;
      else if(MHiEvent.hiHF < 357.5)   CBin = 3;
      else if(MHiEvent.hiHF < 1028)    CBin = 2;
      else if(MHiEvent.hiHF < 2505)    CBin = 1;
      else                             CBin = 0;

      MHLT.GetEntry(HLTIndex[E]);

      int BestJetIndex = -1;
      int BestFJetIndex = -1;
      for(int i = 0; i < MJet.JetCount; i++)
      {
         double AbsEta = fabs(MJet.JetEta[i]);

         if(AbsEta < 5.1 && (BestJetIndex < 0 || MJetPT[i] > MJet.JetPT[BestJetIndex]))
            BestJetIndex = i;
         if((AbsEta > 2.7) && (BestFJetIndex < 0 || MJetPT[i] > MJet.JetPT[BestFJetIndex]))
            BestFJetIndex = i;
      }

      double BestJetEta = fabs(MJet.JetEta[BestJetIndex]);
      double BestFJetEta = fabs(MJet.JetEta[BestFJetIndex]);

      if(BestJetIndex >= 0 && BestJetEta < 5.1)
      {
         HJetPT.Fill(MJetPT[BestJetIndex]);
         for(int i = 0; i < (int)TriggerList.size(); i++)
            if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
               HJetPTs[i]->Fill(MJetPT[BestJetIndex]);

         if(CBin == 0)
         {
            HJetPTC0.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HJetPTsC0[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 1)
         {
            HJetPTC1.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HJetPTsC1[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 2)
         {
            HJetPTC2.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HJetPTsC2[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 3)
         {
            HJetPTC3.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HJetPTsC3[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 4)
         {
            HJetPTC4.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HJetPTsC4[i]->Fill(MJetPT[BestJetIndex]);
         }
      }
      if(BestFJetIndex >= 0 && BestFJetEta < 5.1)
      {
         HFJetPT.Fill(MJetPT[BestFJetIndex]);
         for(int i = 0; i < (int)TriggerList.size(); i++)
            if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
               HFJetPTs[i]->Fill(MJetPT[BestFJetIndex]);

         if(CBin == 0)
         {
            HFJetPTC0.Fill(MJetPT[BestFJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HFJetPTsC0[i]->Fill(MJetPT[BestFJetIndex]);
         }
         if(CBin == 1)
         {
            HFJetPTC1.Fill(MJetPT[BestFJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HFJetPTsC1[i]->Fill(MJetPT[BestFJetIndex]);
         }
         if(CBin == 2)
         {
            HFJetPTC2.Fill(MJetPT[BestFJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HFJetPTsC2[i]->Fill(MJetPT[BestFJetIndex]);
         }
         if(CBin == 3)
         {
            HFJetPTC3.Fill(MJetPT[BestFJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HFJetPTsC3[i]->Fill(MJetPT[BestFJetIndex]);
         }
         if(CBin == 4)
         {
            HFJetPTC4.Fill(MJetPT[BestFJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HFJetPTsC4[i]->Fill(MJetPT[BestFJetIndex]);
         }
      }
      if(BestFJetIndex >= 0 && BestFJetEta > 2.7 && BestFJetEta < 5.1)
      {
         HForwardJetPT.Fill(MJetPT[BestJetIndex]);
         for(int i = 0; i < (int)TriggerList.size(); i++)
            if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
               HForwardJetPTs[i]->Fill(MJetPT[BestJetIndex]);
         
         if(CBin == 0)
         {
            HForwardJetPTC0.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HForwardJetPTsC0[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 1)
         {
            HForwardJetPTC1.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HForwardJetPTsC1[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 2)
         {
            HForwardJetPTC2.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HForwardJetPTsC2[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 3)
         {
            HForwardJetPTC3.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HForwardJetPTsC3[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 4)
         {
            HForwardJetPTC4.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HForwardJetPTsC4[i]->Fill(MJetPT[BestJetIndex]);
         }
      }
      if(BestJetIndex >= 0 && BestJetEta < 2.4)
      {
         HCentralJetPT.Fill(MJetPT[BestJetIndex]);
         for(int i = 0; i < (int)TriggerList.size(); i++)
            if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
               HCentralJetPTs[i]->Fill(MJetPT[BestJetIndex]);
         
         if(CBin == 0)
         {
            HCentralJetPTC0.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HCentralJetPTsC0[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 1)
         {
            HCentralJetPTC1.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HCentralJetPTsC1[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 2)
         {
            HCentralJetPTC2.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HCentralJetPTsC2[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 3)
         {
            HCentralJetPTC3.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HCentralJetPTsC3[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 4)
         {
            HCentralJetPTC4.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HCentralJetPTsC4[i]->Fill(MJetPT[BestJetIndex]);
         }
      }
      if(BestJetIndex >= 0 && BestJetEta < 1.5)
      {
         HVeryCentralJetPT.Fill(MJetPT[BestJetIndex]);
         for(int i = 0; i < (int)TriggerList.size(); i++)
         {
            if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
               HVeryCentralJetPTs[i]->Fill(MJetPT[BestJetIndex]);
            else if(MJetPT[BestJetIndex] > 150)
               cout << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event
                  << " " << CBin << " " << TriggerList[i] << " " << MJetPT[BestJetIndex] << endl;
         }

         if(CBin == 0)
         {
            HVeryCentralJetPTC0.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HVeryCentralJetPTsC0[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 1)
         {
            HVeryCentralJetPTC1.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HVeryCentralJetPTsC1[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 2)
         {
            HVeryCentralJetPTC2.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HVeryCentralJetPTsC2[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 3)
         {
            HVeryCentralJetPTC3.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HVeryCentralJetPTsC3[i]->Fill(MJetPT[BestJetIndex]);
         }
         if(CBin == 4)
         {
            HVeryCentralJetPTC4.Fill(MJetPT[BestJetIndex]);
            for(int i = 0; i < (int)TriggerList.size(); i++)
               if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
                  HVeryCentralJetPTsC4[i]->Fill(MJetPT[BestJetIndex]);
         }
      }
   }

   HJetPT.Write();
   HJetPTC0.Write();
   HJetPTC1.Write();
   HJetPTC2.Write();
   HJetPTC3.Write();
   HJetPTC4.Write();
   HFJetPT.Write();
   HFJetPTC0.Write();
   HFJetPTC1.Write();
   HFJetPTC2.Write();
   HFJetPTC3.Write();
   HFJetPTC4.Write();
   HForwardJetPT.Write();
   HForwardJetPTC0.Write();
   HForwardJetPTC1.Write();
   HForwardJetPTC2.Write();
   HForwardJetPTC3.Write();
   HForwardJetPTC4.Write();
   HCentralJetPT.Write();
   HCentralJetPTC0.Write();
   HCentralJetPTC1.Write();
   HCentralJetPTC2.Write();
   HCentralJetPTC3.Write();
   HCentralJetPTC4.Write();
   HVeryCentralJetPT.Write();
   HVeryCentralJetPTC0.Write();
   HVeryCentralJetPTC1.Write();
   HVeryCentralJetPTC2.Write();
   HVeryCentralJetPTC3.Write();
   HVeryCentralJetPTC4.Write();
   for(TH1D *H : HJetPTs)            H->Write();
   for(TH1D *H : HJetPTsC0)          H->Write();
   for(TH1D *H : HJetPTsC1)          H->Write();
   for(TH1D *H : HJetPTsC2)          H->Write();
   for(TH1D *H : HJetPTsC3)          H->Write();
   for(TH1D *H : HJetPTsC4)          H->Write();
   for(TH1D *H : HFJetPTs)           H->Write();
   for(TH1D *H : HFJetPTsC0)         H->Write();
   for(TH1D *H : HFJetPTsC1)         H->Write();
   for(TH1D *H : HFJetPTsC2)         H->Write();
   for(TH1D *H : HFJetPTsC3)         H->Write();
   for(TH1D *H : HFJetPTsC4)         H->Write();
   for(TH1D *H : HForwardJetPTs)     H->Write();
   for(TH1D *H : HForwardJetPTsC0)   H->Write();
   for(TH1D *H : HForwardJetPTsC1)   H->Write();
   for(TH1D *H : HForwardJetPTsC2)   H->Write();
   for(TH1D *H : HForwardJetPTsC3)   H->Write();
   for(TH1D *H : HForwardJetPTsC4)   H->Write();
   for(TH1D *H : HCentralJetPTs)     H->Write();
   for(TH1D *H : HCentralJetPTsC0)   H->Write();
   for(TH1D *H : HCentralJetPTsC1)   H->Write();
   for(TH1D *H : HCentralJetPTsC2)   H->Write();
   for(TH1D *H : HCentralJetPTsC3)   H->Write();
   for(TH1D *H : HCentralJetPTsC4)   H->Write();
   for(TH1D *H : HVeryCentralJetPTs)     H->Write();
   for(TH1D *H : HVeryCentralJetPTsC0)   H->Write();
   for(TH1D *H : HVeryCentralJetPTsC1)   H->Write();
   for(TH1D *H : HVeryCentralJetPTsC2)   H->Write();
   for(TH1D *H : HVeryCentralJetPTsC3)   H->Write();
   for(TH1D *H : HVeryCentralJetPTsC4)   H->Write();

   OutputFile.Close();
   HLTFile.Close();
   InputFile.Close();

   return 0;
}




