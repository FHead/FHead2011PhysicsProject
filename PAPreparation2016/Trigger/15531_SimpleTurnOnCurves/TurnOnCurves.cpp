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
   string ForestFileName = "root://xrootd17.cmsaf.mit.edu//store/user/krajczar/forestpPb_merged/ReggeGribovPartonMCpPb_MinBias_8016GeV_EposLHC/HiForest_MB_merged_10M.root";
   string IndexFileName = "Index.root";
   string HLTFileName = "openHLT.root";
   string OutputFileName = "Output.root";

   TFile *ForestFile = TFile::Open(ForestFileName.c_str());
   TFile *IndexFile = TFile::Open(IndexFileName.c_str());
   TFile *HLTFile = TFile::Open(HLTFileName.c_str());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TriggerTreeMessenger MTrigger(*HLTFile, "hltbitanalysis/HltTree");

   HiEventTreeMessenger MHiEvent(*ForestFile);
   JetTreeMessenger MJet(*ForestFile, "ak4PFJetAnalyzer/t");

   map<EventCoordinate, int> Location;

   int EntryCount = MTrigger.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      MTrigger.GetEntry(i);

      EventCoordinate E(MTrigger.Run, MTrigger.Event, MTrigger.Lumi);
      Location.insert(pair<EventCoordinate, int>(E, -1));
   }

   TTree *IndexTree = (TTree *)IndexFile->Get("IndexTree");
   int Run;           IndexTree->SetBranchAddress("Run", &Run);
   long long Event;   IndexTree->SetBranchAddress("Event", &Event);
   int Lumi;          IndexTree->SetBranchAddress("Lumi", &Lumi);
   int Index;         IndexTree->SetBranchAddress("Index", &Index);

   EntryCount = IndexTree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      if((i + 1) % 10000 == 0)
         cerr << "Indexing event " << i + 1 << "/" << EntryCount << endl;

      IndexTree->GetEntry(i);

      EventCoordinate E(Run, Event, Lumi);
      if(Location.find(E) == Location.end())
         continue;

      Location[E] = Index;
   }

   TH1D HJetPT_All("HJetPT_All", ";Jet PT;", 100, 0, 300);
   TH1D HJetPT_PAAK4PFJet40("HJetPT_PAAK4PFJet40", ";Jet PT;", 100, 0, 300);
   TH1D HJetPT_PAAK4PFJet60("HJetPT_PAAK4PFJet60", ";Jet PT;", 100, 0, 300);
   TH1D HJetPT_PAAK4PFJet80("HJetPT_PAAK4PFJet80", ";Jet PT;", 100, 0, 300);

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
      MJet.GetEntry(I);

      int LeadingIndex = -1;
      for(int j = 0; j < MJet.JetCount; j++)
      {
         if(MJet.JetEta[j] < -5.1 || MJet.JetEta[j] > 5.1)
            continue;
         if(LeadingIndex < 0 || MJet.JetPT[LeadingIndex] < MJet.JetPT[j])
            LeadingIndex = j;
      }

      if(LeadingIndex < 0)
         continue;

      HJetPT_All.Fill(MJet.JetPT[LeadingIndex]);
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1v2") == true)
         HJetPT_PAAK4PFJet40.Fill(MJet.JetPT[LeadingIndex]);
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v2") == true)
         HJetPT_PAAK4PFJet60.Fill(MJet.JetPT[LeadingIndex]);
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v2") == true)
         HJetPT_PAAK4PFJet80.Fill(MJet.JetPT[LeadingIndex]);
   }

   HJetPT_All.Write();
   HJetPT_PAAK4PFJet40.Write();
   HJetPT_PAAK4PFJet60.Write();
   HJetPT_PAAK4PFJet80.Write();

   OutputFile.Close();

   HLTFile->Close();
   IndexFile->Close();
   ForestFile->Close();

   delete HLTFile;
   delete IndexFile;
   delete ForestFile;

   return 0;
}









