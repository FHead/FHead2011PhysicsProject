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
   string JetCollectionName = CL.Get("Jet", "akPu4PFJetAnalyzer/t");
   vector<string> TriggerList = CL.GetStringVector("Trigger");

   TFile InputFile(InputFileName.c_str());
   TFile HLTFile(HLTFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   GGTreeMessenger MHiEvent(InputFile);
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

   TH1D HJetPT("HJetPT", ";PT;", 100, 0, 200);
   TH1D HCentralJetPT("HCentralJetPT", ";PT;", 100, 0, 200);
   vector<TH1D *> HJetPTs;
   vector<TH1D *> HCentralJetPTs;
   for(int i = 0; i < (int)TriggerList.size(); i++)
   {
      HJetPTs.push_back(new TH1D(Form("HJetPT_%s", TriggerList[i].c_str()), ";PT;", 100, 0, 200));
      HCentralJetPTs.push_back(new TH1D(Form("HCentralJetPT_%s", TriggerList[i].c_str()), ";PT;", 100, 0, 200));
   }

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

      MHLT.GetEntry(HLTIndex[E]);

      int BestJetIndex = -1;
      int BestCentralJetIndex = -1;
      for(int i = 0; i < MJet.JetCount; i++)
      {
         if(fabs(MJet.JetEta[i]) > 5.1)
            continue;
         if(BestJetIndex < 0 || MJet.JetPT[i] > MJet.JetPT[BestJetIndex])
            BestJetIndex = i;

         if(fabs(MJet.JetEta[i]) > 2.4)
            continue;
         if(BestCentralJetIndex < 0 || MJet.JetPT[i] > MJet.JetPT[BestCentralJetIndex])
            BestCentralJetIndex = i;
      }

      if(BestJetIndex >= 0)
      {
         HJetPT.Fill(MJet.JetPT[BestJetIndex]);
         for(int i = 0; i < (int)TriggerList.size(); i++)
            if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
               HJetPTs[i]->Fill(MJet.JetPT[BestJetIndex]);
      }
      if(BestCentralJetIndex >= 0)
      {
         HCentralJetPT.Fill(MJet.JetPT[BestCentralJetIndex]);
         for(int i = 0; i < (int)TriggerList.size(); i++)
            if(MHLT.CheckTrigger(TriggerList[i]) > 0)   // passed!
               HCentralJetPTs[i]->Fill(MJet.JetPT[BestCentralJetIndex]);
      }
   }

   HJetPT.Write();
   HCentralJetPT.Write();
   for(TH1D *H : HJetPTs)          H->Write();
   for(TH1D *H : HCentralJetPTs)   H->Write();

   OutputFile.Close();
   HLTFile.Close();
   InputFile.Close();

   return 0;
}




