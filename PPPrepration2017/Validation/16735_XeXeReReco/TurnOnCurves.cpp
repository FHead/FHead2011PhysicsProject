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
   string ForestFileName = "GeorgeSamples/Dijet80/HiForestAOD_Dijet_20171009.root";
   string HLTFileName = "~/EOSHome/PPTrigger2017/OpenHLT/MenuV9_GeorgeDijet.root";
   string OutputFileName = "Output.root";

   TFile *ForestFile = TFile::Open(ForestFileName.c_str());
   TFile *HLTFile = TFile::Open(HLTFileName.c_str());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TriggerTreeMessenger MTrigger(HLTFile, "hltbitanalysis/HltTree");

   HiEventTreeMessenger MHiEvent(ForestFile);
   GGTreeMessenger MGG(ForestFile);

   map<EventCoordinate, int> Location;

   int EntryCount = MTrigger.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      if((i + 1) % 10000 == 0)
         cerr << "Looping over event " << i + 1 << "/" << EntryCount << endl;
      
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

   TH1D HCaloJet_All("HCaloJet_All", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_PassL116("HCaloJet_PassL116", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_PassL120("HCaloJet_PassL120", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_PassL128("HCaloJet_PassL128", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_PassL140("HCaloJet_PassL140", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_PassL160("HCaloJet_PassL160", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_Pass30("HCaloJet_Pass30", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_Pass40("HCaloJet_Pass40", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_Pass50("HCaloJet_Pass50", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_Pass80("HCaloJet_Pass80", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_Pass100("HCaloJet_Pass100", ";Raw Jet PT;", 100, 0, 150);
   TH1D HCaloJet_Pass120("HCaloJet_Pass120", ";Raw Jet PT;", 100, 0, 150);

   TH1D HPFJet_All("HPFJet_All", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_PassL116("HPFJet_PassL116", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_PassL120("HPFJet_PassL120", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_PassL128("HPFJet_PassL128", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_PassL140("HPFJet_PassL140", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_PassL160("HPFJet_PassL160", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_Pass30("HPFJet_Pass30", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_Pass50("HPFJet_Pass50", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_Pass80("HPFJet_Pass80", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_Pass100("HPFJet_Pass100", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJet_Pass120("HPFJet_Pass120", ";Raw Jet PT;", 100, 0, 200);

   TH1D HPFJetFWD_All("HPFJetFWD_All", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJetFWD_PassL135("HPFJetFWD_PassL135", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJetFWD_PassL140("HPFJetFWD_PassL140", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJetFWD_PassL150("HPFJetFWD_PassL150", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJetFWD_PassL160("HPFJetFWD_PassL160", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJetFWD_Pass30("HPFJetFWD_Pass30", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJetFWD_Pass50("HPFJetFWD_Pass50", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJetFWD_Pass60("HPFJetFWD_Pass60", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJetFWD_Pass70("HPFJetFWD_Pass70", ";Raw Jet PT;", 100, 0, 200);
   TH1D HPFJetFWD_Pass80("HPFJetFWD_Pass80", ";Raw Jet PT;", 100, 0, 200);

   EntryCount = MTrigger.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      if((i + 1) % 10000 == 0)
         cerr << "Processing event " << i + 1 << "/" << EntryCount << endl;
      
      MTrigger.GetEntry(i);

      EventCoordinate E(MTrigger.Run, MTrigger.Event, MTrigger.Lumi);
      if(Location.find(E) == Location.end())
         continue;
      if(Location[E] == -1)
         continue;

      int I = Location[E];

      MHiEvent.GetEntry(I);
      MGG.GetEntry(I);

      int BestCaloJetPTIndex = -1;
      int BestPFJetPTIndex = -1;
      int BestForwardPFJetPTIndex = -1;

      for(int j = 0; j < MGG.CaloJetCount; j++)
      {
         if((*MGG.CaloJetEta)[j] < -5.0 || (*MGG.CaloJetEta)[j] > 5.0)
            continue;
         if(BestCaloJetPTIndex < 0 || (*MGG.CaloJetPT)[BestCaloJetPTIndex] < (*MGG.CaloJetPT)[j])
            BestCaloJetPTIndex = j;
      }
      for(int j = 0; j < MGG.PFJetCount; j++)
      {
         if((*MGG.PFJetEta)[j] < -5.0 || (*MGG.PFJetEta)[j] > 5.0)
            continue;
         if(BestPFJetPTIndex < 0 || (*MGG.PFJetPT)[BestPFJetPTIndex] < (*MGG.PFJetPT)[j])
            BestPFJetPTIndex = j;
      }
      for(int j = 0; j < MGG.PFJetCount; j++)
      {
         if((*MGG.PFJetEta)[j] < -5.0 || (*MGG.PFJetEta)[j] > 5.0)
            continue;
         if((*MGG.PFJetEta)[j] > -2.75 && (*MGG.PFJetEta)[j] < 2.75)
            continue;
         if(BestForwardPFJetPTIndex < 0 || (*MGG.PFJetPT)[BestForwardPFJetPTIndex] < (*MGG.PFJetPT)[j])
            BestForwardPFJetPTIndex = j;
      }

      if(BestCaloJetPTIndex >= 0)
      {
         HCaloJet_All.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet16_Eta5p1_v1") == 1)
            HCaloJet_PassL116.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet20_Eta5p1_v1") == 1)
            HCaloJet_PassL120.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet28_Eta5p1_v1") == 1)
            HCaloJet_PassL128.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet40_Eta5p1_v1") == 1)
            HCaloJet_PassL140.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet60_Eta5p1_v1") == 1)
            HCaloJet_PassL160.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4CaloJet30_v10") == 1)
            HCaloJet_Pass30.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4CaloJet40_v9") == 1)
            HCaloJet_Pass40.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4CaloJet50_v9") == 1)
            HCaloJet_Pass50.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4CaloJet80_v9") == 1)
            HCaloJet_Pass80.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4CaloJet100_v9") == 1)
            HCaloJet_Pass100.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4CaloJet120_v8") == 1)
            HCaloJet_Pass120.Fill((*MGG.CaloJetPT)[BestCaloJetPTIndex]);
      }
      if(BestPFJetPTIndex >= 0)
      {
         HPFJet_All.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet16_Eta5p1_v1") == 1)
            HPFJet_PassL116.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet20_Eta5p1_v1") == 1)
            HPFJet_PassL120.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet28_Eta5p1_v1") == 1)
            HPFJet_PassL128.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet40_Eta5p1_v1") == 1)
            HPFJet_PassL140.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet60_Eta5p1_v1") == 1)
            HPFJet_PassL160.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet30_v15") == 1)
            HPFJet_Pass30.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet50_v15") == 1)
            HPFJet_Pass50.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet80_v15") == 1)
            HPFJet_Pass80.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet100_v15") == 1)
            HPFJet_Pass100.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet120_v14") == 1)
            HPFJet_Pass120.Fill((*MGG.PFJetPT)[BestPFJetPTIndex]);
      }
      if(BestForwardPFJetPTIndex >= 0)
      {
         HPFJetFWD_All.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet35FWD") == 1)
            HPFJetFWD_PassL135.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet40FWD") == 1)
            HPFJetFWD_PassL140.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet50FWD") == 1)
            HPFJetFWD_PassL150.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_L1SingleJet60FWD") == 1)
            HPFJetFWD_PassL160.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet30FWD_v14") == 1)
            HPFJetFWD_Pass30.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet50FWD_v14") == 1)
            HPFJetFWD_Pass50.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet60FWD_v14") == 1)
            HPFJetFWD_Pass60.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet70FWD_v14") == 1)
            HPFJetFWD_Pass70.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_AK4PFJet80FWD_v14") == 1)
            HPFJetFWD_Pass80.Fill((*MGG.PFJetPT)[BestForwardPFJetPTIndex]);
      }
   }

   HCaloJet_All.Write();
   HCaloJet_PassL116.Write();
   HCaloJet_PassL120.Write();
   HCaloJet_PassL128.Write();
   HCaloJet_PassL140.Write();
   HCaloJet_PassL160.Write();
   HCaloJet_Pass30.Write();
   HCaloJet_Pass40.Write();
   HCaloJet_Pass50.Write();
   HCaloJet_Pass80.Write();
   HCaloJet_Pass100.Write();
   HCaloJet_Pass120.Write();

   HPFJet_All.Write();
   HPFJet_PassL116.Write();
   HPFJet_PassL120.Write();
   HPFJet_PassL128.Write();
   HPFJet_PassL140.Write();
   HPFJet_PassL160.Write();
   HPFJet_Pass30.Write();
   HPFJet_Pass50.Write();
   HPFJet_Pass80.Write();
   HPFJet_Pass100.Write();
   HPFJet_Pass120.Write();
   
   HPFJetFWD_All.Write();
   HPFJetFWD_PassL135.Write();
   HPFJetFWD_PassL140.Write();
   HPFJetFWD_PassL150.Write();
   HPFJetFWD_PassL160.Write();
   HPFJetFWD_Pass30.Write();
   HPFJetFWD_Pass50.Write();
   HPFJetFWD_Pass60.Write();
   HPFJetFWD_Pass70.Write();
   HPFJetFWD_Pass80.Write();

   OutputFile.Close();

   HLTFile->Close();
   ForestFile->Close();

   delete HLTFile;
   delete ForestFile;

   return 0;
}




