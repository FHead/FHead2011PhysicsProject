#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

#include "Messenger.h"

class EventCoordinate;
int main(int argc, char *argv[]);

class EventCoordinate
{
public:
   long long Run;
   long long Event;
   long long Lumi;
   int Data;
public:
   EventCoordinate() : Run(0), Event(0), Lumi(0), Data(-1) {}
   EventCoordinate(long long run, long long event, long long lumi, int data)
      : Run(run), Event(event), Lumi(lumi), Data(data) {}
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

int main(int argc, char *argv[])
{
   double EtaRange = 5.1;

   string ForestFileName = "Forest.root";
   string HLTFileName = "openHLT.root";
   string OutputFileName = "Output.root";

   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " Forest.root OpenHLT.root Output.root" << endl;
      return -1;
   }

   ForestFileName = argv[1];
   HLTFileName = argv[2];
   OutputFileName = argv[3];

   TFile *ForestFile = TFile::Open(ForestFileName.c_str());
   TFile *HLTFile = TFile::Open(HLTFileName.c_str());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TriggerTreeMessenger MTrigger(*HLTFile, "hltbitanalysis/HltTree");

   HiEventTreeMessenger MHiEvent(*ForestFile);
   JetTreeMessenger MCaloJet(*ForestFile, "ak4CaloJetAnalyzer/t");
   JetTreeMessenger MPFJet(*ForestFile, "ak4PFJetAnalyzer/t");

   // map<EventCoordinate, int> Location;
   vector<EventCoordinate> Location(MTrigger.Tree->GetEntries());

   int EntryCount = MTrigger.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      MTrigger.GetEntry(i);

      EventCoordinate E(MTrigger.Run, MTrigger.Event, MTrigger.Lumi, -1);
      // Location.insert(pair<EventCoordinate, int>(E, -1));
      Location[i] = E;
   }

   sort(Location.begin(), Location.end());

   EntryCount = MHiEvent.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      if((i + 1) % 100000 == 0)
         cerr << "Indexing event " << i + 1 << "/" << EntryCount << endl;

      MHiEvent.GetEntry(i);

      EventCoordinate E(MHiEvent.Run, MHiEvent.Event, MHiEvent.Lumi, i);
      // if(Location.find(E) == Location.end())
      //    continue;
      if(binary_search(Location.begin(), Location.end(), E) == false)
         continue;

      // Location[E] = i;
      vector<EventCoordinate>::iterator iter = lower_bound(Location.begin(), Location.end(), E);
      iter->Data = i;
   }

   TH1D HAllCaloJets("HAllCaloJets", ";pt;", 100, 0, 150);
   TH1D HPass40CaloJets("HPass40CaloJets", ";pt;", 100, 0, 150);
   TH1D HPass60CaloJets("HPass60CaloJets", ";pt;", 100, 0, 150);
   TH1D HPass80CaloJets("HPass80CaloJets", ";pt;", 100, 0, 150);
   
   TH1D HAllPFJets("HAllPFJets", ";pt;", 100, 0, 150);
   TH1D HPass40PFJets("HPass40PFJets", ";pt;", 100, 0, 150);
   TH1D HPass60PFJets("HPass60PFJets", ";pt;", 100, 0, 150);
   TH1D HPass80PFJets("HPass80PFJets", ";pt;", 100, 0, 150);

   TH2D HAllPFJetsPTEta("HAllPFJetsPTEta", ";pt;eta", 100, 0, 150, 100, -5.1, 5.1);
   TH2D HPass40PFJetsPTEta("HPass40PFJetsPTEta", ";pt;eta", 100, 0, 150, 100, -5.1, 5.1);
   TH2D HPass60PFJetsPTEta("HPass60PFJetsPTEta", ";pt;eta", 100, 0, 150, 100, -5.1, 5.1);
   TH2D HPass80PFJetsPTEta("HPass80PFJetsPTEta", ";pt;eta", 100, 0, 150, 100, -5.1, 5.1);

   EntryCount = MTrigger.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      MTrigger.GetEntry(i);

      EventCoordinate E(MTrigger.Run, MTrigger.Event, MTrigger.Lumi, -1);
      vector<EventCoordinate>::iterator iter = lower_bound(Location.begin(), Location.end(), E);
      if(iter == Location.end())
         continue;
      if(iter->Data == -1)
         continue;

      int I = iter->Data;

      MHiEvent.GetEntry(I);
      MCaloJet.GetEntry(I);
      MPFJet.GetEntry(I);

      int BestCaloJetPTIndex = -1;
      int BestPFJetPTIndex = -1;

      for(int j = 0; j < MCaloJet.JetCount; j++)
      {
         if(MCaloJet.JetEta[j] < -EtaRange || MCaloJet.JetEta[j] > EtaRange)
            continue;
         if(MCaloJet.EcalSum[j] == 0)
            continue;
         if(BestCaloJetPTIndex < 0 || MCaloJet.JetRawPT[BestCaloJetPTIndex] < MCaloJet.JetRawPT[j])
            BestCaloJetPTIndex = j;
      }
      for(int j = 0; j < MPFJet.JetCount; j++)
      {
         if(MPFJet.JetEta[j] < -EtaRange || MPFJet.JetEta[j] > EtaRange)
            continue;
         if(MPFJet.EcalSum[j] == 0)
            continue;
         if(BestPFJetPTIndex < 0 || MPFJet.JetPT[BestPFJetPTIndex] < MPFJet.JetPT[j])
            BestPFJetPTIndex = j;
      }

      if(BestCaloJetPTIndex >= 0 && fabs(MCaloJet.JetEta[BestCaloJetPTIndex]) < 5.1)
      {
         HAllCaloJets.Fill(MCaloJet.JetRawPT[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet40_Eta5p1_v1") == 1)
            HPass40CaloJets.Fill(MCaloJet.JetRawPT[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta5p1_v1") == 1)
            HPass60CaloJets.Fill(MCaloJet.JetRawPT[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta5p1_v1") == 1)
            HPass80CaloJets.Fill(MCaloJet.JetRawPT[BestCaloJetPTIndex]);
      }
      if(BestPFJetPTIndex >= 0 && fabs(MPFJet.JetEta[BestPFJetPTIndex]) < 5.1)
      {
         HAllPFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1_v1") == 1)
            HPass40PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v1") == 1)
            HPass60PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v1") == 1)
            HPass80PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
      }
      if(BestPFJetPTIndex >= 0 && fabs(MPFJet.JetEta[BestPFJetPTIndex]) < 5.1)
      {
         HAllPFJetsPTEta.Fill(MPFJet.JetPT[BestPFJetPTIndex], MPFJet.JetEta[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1_v1") == 1)
            HPass40PFJetsPTEta.Fill(MPFJet.JetPT[BestPFJetPTIndex], MPFJet.JetEta[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v1") == 1)
            HPass60PFJetsPTEta.Fill(MPFJet.JetPT[BestPFJetPTIndex], MPFJet.JetEta[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v1") == 1)
            HPass80PFJetsPTEta.Fill(MPFJet.JetPT[BestPFJetPTIndex], MPFJet.JetEta[BestPFJetPTIndex]);

         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1_v1") != 1 && MPFJet.JetPT[BestPFJetPTIndex] > 80)
         {
            cout << "Jet40 " << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event
               << " " << MPFJet.JetPT[BestPFJetPTIndex] << endl;
         }
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v1") != 1 && MPFJet.JetPT[BestPFJetPTIndex] > 100)
         {
            cout << "Jet60 " << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event
               << " " << MPFJet.JetPT[BestPFJetPTIndex] << endl;
         }
      }
   }

   HAllCaloJets.Write();
   HPass40CaloJets.Write();
   HPass60CaloJets.Write();
   HPass80CaloJets.Write();

   HAllPFJets.Write();
   HPass40PFJets.Write();
   HPass60PFJets.Write();
   HPass80PFJets.Write();

   HAllPFJetsPTEta.Write();
   HPass40PFJetsPTEta.Write();
   HPass60PFJetsPTEta.Write();
   HPass80PFJetsPTEta.Write();

   OutputFile.Close();

   HLTFile->Close();
   ForestFile->Close();

   delete HLTFile;
   delete ForestFile;

   return 0;
}









