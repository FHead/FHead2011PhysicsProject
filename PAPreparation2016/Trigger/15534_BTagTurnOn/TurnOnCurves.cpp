#include <iostream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "Messenger.h"

class EventCoordinate;
int main(int argc, char *argv[]);

class EventCoordinate
{
public:
   long long Run;
   long long Event;
   long long Lumi;
public:
   EventCoordinate() : Run(0), Event(0), Lumi(0) {}
   EventCoordinate(long long run, long long event, long long lumi)
      : Run(run), Event(event), Lumi(lumi) {}
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
   string ForestFileName = "HiForestAOD.root";
   string HLTFileName = "openHLT.root";
   string OutputFileName = "Output.root";

   TFile *ForestFile = TFile::Open(ForestFileName.c_str());
   TFile *HLTFile = TFile::Open(HLTFileName.c_str());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TriggerTreeMessenger MTrigger(*HLTFile, "hltbitanalysis/HltTree");

   HiEventTreeMessenger MHiEvent(*ForestFile);
   JetTreeMessenger MCaloJet(*ForestFile, "ak4CaloJetAnalyzer/t");
   JetTreeMessenger MPFJet(*ForestFile, "ak4PFJetAnalyzer/t");

   map<EventCoordinate, int> Location;

   int EntryCount = MTrigger.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      MTrigger.GetEntry(i);

      EventCoordinate E(MTrigger.Run, MTrigger.Event, MTrigger.Lumi);
      Location.insert(pair<EventCoordinate, int>(E, -1));
   }

   EntryCount = MHiEvent.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      if((i + 1) % 10000 == 0)
         cerr << "Indexing event " << i + 1 << "/" << EntryCount << endl;

      MHiEvent.GetEntry(i);

      EventCoordinate E(MHiEvent.Run, MHiEvent.Event, MHiEvent.Lumi);
      if(Location.find(E) == Location.end())
         continue;

      Location[E] = i;
   }

   // "V1V2" = trigger V1, offline V2, and similarly for others
   TH1D HJetBestCSVV1V1_All("HJetBestCSVV1V1_All", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HJetBestCSVV1V1_Passed("HJetBestCSVV1V1_Passed", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HJetBestCSVV1V2_All("HJetBestCSVV1V2_All", "Trigger V1, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HJetBestCSVV1V2_Passed("HJetBestCSVV1V2_Passed", "Trigger V1, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HJetBestCSVV2V1_All("HJetBestCSVV2V1_All", "Trigger V2, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HJetBestCSVV2V1_Passed("HJetBestCSVV2V1_Passed", "Trigger V2, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HJetBestCSVV2V2_All("HJetBestCSVV2V2_All", "Trigger V2, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HJetBestCSVV2V2_Passed("HJetBestCSVV2V2_Passed", "Trigger V2, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_All("HPFJetBestCSV_All", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_Passed("HPFJetBestCSV_Passed", ";Discriminant Value;", 100, 0, 1);

   EntryCount = MTrigger.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      MTrigger.GetEntry(i);

      EventCoordinate E(MTrigger.Run, MTrigger.Event, MTrigger.Lumi);
      if(Location.find(E) == Location.end())
         continue;
      if(Location[E] == -1)
         continue;

      int I = Location[E];

      MHiEvent.GetEntry(I);
      MCaloJet.GetEntry(I);
      MPFJet.GetEntry(I);

      int BestCSVV1Index = -1;
      int BestCSVV2Index = -1;
      int BestPFCSVIndex = -1;

      for(int j = 0; j < MCaloJet.JetCount; j++)
      {
         if(MCaloJet.JetEta[j] < -2.1 || MCaloJet.JetEta[j] > 2.1)
            continue;
         if(MCaloJet.JetPT[j] < 60)
            continue;
         if(BestCSVV1Index < 0 || MCaloJet.JetCSVV1P[BestCSVV1Index] < MCaloJet.JetCSVV1P[j])
            BestCSVV1Index = j;
         if(BestCSVV2Index < 0 || MCaloJet.JetCSVV2P[BestCSVV2Index] < MCaloJet.JetCSVV2P[j])
            BestCSVV2Index = j;
      }
      for(int j = 0; j < MPFJet.JetCount; j++)
      {
         if(MPFJet.JetEta[j] < -2.1 || MPFJet.JetEta[j] > 2.1)
            continue;
         if(MPFJet.JetPT[j] < 60)
            continue;
         if(BestPFCSVIndex < 0 || MPFJet.JetCSVV2[BestPFCSVIndex] < MPFJet.JetCSVV2[j])
         {
            if(MPFJet.JetCSVV2[BestPFCSVIndex] < 1000)
               BestPFCSVIndex = j;
         }
      }

      if(BestCSVV1Index >= 0)
      {
         HJetBestCSVV1V1_All.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index]);
         HJetBestCSVV2V1_All.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1") == 1)
            HJetBestCSVV1V1_Passed.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1") == 1)
            HJetBestCSVV2V1_Passed.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index]);
      }
      if(BestCSVV2Index >= 0)
      {
         HJetBestCSVV1V2_All.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index]);
         HJetBestCSVV2V2_All.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1") == 1)
            HJetBestCSVV1V2_Passed.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1") == 1)
            HJetBestCSVV2V2_Passed.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index]);
      }
      if(BestPFCSVIndex >= 0)
      {
         HPFJetBestCSV_All.Fill(MPFJet.JetCSVV2[BestPFCSVIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJetCSV60_Eta2p1_v2") == 1)
            HPFJetBestCSV_Passed.Fill(MPFJet.JetCSVV2[BestPFCSVIndex]);
      }
   }

   HJetBestCSVV1V1_All.Write();
   HJetBestCSVV1V1_Passed.Write();
   HJetBestCSVV1V2_All.Write();
   HJetBestCSVV1V2_Passed.Write();
   HJetBestCSVV2V1_All.Write();
   HJetBestCSVV2V1_Passed.Write();
   HJetBestCSVV2V2_All.Write();
   HJetBestCSVV2V2_Passed.Write();
   HPFJetBestCSV_All.Write();
   HPFJetBestCSV_Passed.Write();

   OutputFile.Close();

   HLTFile->Close();
   ForestFile->Close();

   delete HLTFile;
   delete ForestFile;

   return 0;
}









