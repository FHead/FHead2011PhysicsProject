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

   TH1D HJetPT_All("HJetPT_All", ";Jet PT;", 100, 0, 300);

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

      int LeadingIndex = -1;
      for(int j = 0; j < MCaloJet.JetCount; j++)
      {
         if(MCaloJet.JetEta[j] < -2.1 || MCaloJet.JetEta[j] > 2.1)
            continue;
         if(LeadingIndex < 0 || MCaloJet.JetPT[LeadingIndex] < MCaloJet.JetPT[j])
            LeadingIndex = j;
      }

      if(LeadingIndex < 0)
         continue;

      HJetPT_All.Fill(MCaloJet.JetPT[LeadingIndex]);
   }

   HJetPT_All.Write();

   OutputFile.Close();

   HLTFile->Close();
   ForestFile->Close();

   delete HLTFile;
   delete ForestFile;

   return 0;
}









