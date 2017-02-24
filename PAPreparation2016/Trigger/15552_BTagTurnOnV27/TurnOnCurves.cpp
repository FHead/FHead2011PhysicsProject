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
   string ForestFileName = "HiForestAOD_AllJets.root";
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
   TH1D HCaloJetBestCSV_All60("HCaloJetBestCSV_All60", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSV_All80("HCaloJetBestCSV_All80", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSV_All40("HCaloJetBestCSV_All40", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSV_Passed60("HCaloJetBestCSV_Passed60", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSV_Passed80("HCaloJetBestCSV_Passed80", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSV_Passed40("HCaloJetBestCSV_Passed40", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_All60("HPFJetBestCSV_All60", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_All80("HPFJetBestCSV_All80", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_All40("HPFJetBestCSV_All40", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_Passed60("HPFJetBestCSV_Passed60", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_Passed80("HPFJetBestCSV_Passed80", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_Passed40("HPFJetBestCSV_Passed40", ";Discriminant Value;", 100, 0, 1);
   
   TH1D HCaloJetBestPT_All("HCaloJetBestPT_All", ";Jet PT;", 100, 0, 150);
   TH1D HCaloJetBestPT_Passed60("HCaloJetBestPT_Passed60", ";Jet PT;", 100, 0, 150);
   TH1D HCaloJetBestPT_Passed80("HCaloJetBestPT_Passed80", ";Jet PT;", 100, 0, 150);
   TH1D HCaloJetBestPT_Passed40("HCaloJetBestPT_Passed40", ";Jet PT;", 100, 0, 150);
   TH1D HPFJetBestPT_All("HPFJetBestPT_All", ";Jet PT;", 100, 0, 150);
   TH1D HPFJetBestPT_Passed60("HPFJetBestPT_Passed60", ";Jet PT;", 100, 0, 150);
   TH1D HPFJetBestPT_Passed80("HPFJetBestPT_Passed80", ";Jet PT;", 100, 0, 150);
   TH1D HPFJetBestPT_Passed40("HPFJetBestPT_Passed40", ";Jet PT;", 100, 0, 150);

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

      int BestCSVV1Index40 = -1;
      int BestCSVV1Index60 = -1;
      int BestCSVV1Index80 = -1;
      int BestPFCSVIndex40 = -1;
      int BestPFCSVIndex60 = -1;
      int BestPFCSVIndex80 = -1;

      for(int j = 0; j < MCaloJet.JetCount; j++)
      {
         if(MCaloJet.JetEta[j] < -2.1 || MCaloJet.JetEta[j] > 2.1)
            continue;
         if(MCaloJet.JetRawPT[j] < 20)
            continue;
         if(BestCSVV1Index40 < 0 || MCaloJet.JetCSVV2P[BestCSVV1Index40] < MCaloJet.JetCSVV2P[j])
            BestCSVV1Index40 = j;
         if(MCaloJet.JetRawPT[j] < 35)
            continue;
         if(BestCSVV1Index60 < 0 || MCaloJet.JetCSVV2P[BestCSVV1Index60] < MCaloJet.JetCSVV2P[j])
            BestCSVV1Index60 = j;
         if(MCaloJet.JetRawPT[j] < 50)
            continue;
         if(BestCSVV1Index80 < 0 || MCaloJet.JetCSVV2P[BestCSVV1Index80] < MCaloJet.JetCSVV2P[j])
            BestCSVV1Index80 = j;
      }
      for(int j = 0; j < MPFJet.JetCount; j++)
      {
         if(MPFJet.JetEta[j] < -2.1 || MPFJet.JetEta[j] > 2.1)
            continue;
         if(MPFJet.JetRawPT[j] < 20)
            continue;
         if(BestPFCSVIndex40 < 0 || MPFJet.JetCSVV2[BestPFCSVIndex40] < MPFJet.JetCSVV2[j])
            if(MPFJet.JetCSVV2[BestPFCSVIndex40] < 1000)
               BestPFCSVIndex40 = j;
         if(MPFJet.JetRawPT[j] < 50)
            continue;
         if(BestPFCSVIndex60 < 0 || MPFJet.JetCSVV2[BestPFCSVIndex60] < MPFJet.JetCSVV2[j])
            if(MPFJet.JetCSVV2[BestPFCSVIndex60] < 1000)
               BestPFCSVIndex60 = j;
         if(MPFJet.JetRawPT[j] < 75)
            continue;
         if(BestPFCSVIndex80 < 0 || MPFJet.JetCSVV2[BestPFCSVIndex80] < MPFJet.JetCSVV2[j])
            if(MPFJet.JetCSVV2[BestPFCSVIndex80] < 1000)
               BestPFCSVIndex80 = j;
      }

      if(BestCSVV1Index60 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta2p1_v1") == 1)
      {
         HCaloJetBestCSV_All60.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index60]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSV60_Eta2p1_v1") == 1)
            HCaloJetBestCSV_Passed60.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index60]);
      }
      if(BestCSVV1Index80 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta2p1_v1") == 1)
      {
         HCaloJetBestCSV_All80.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index80]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSV80_Eta2p1_v1") == 1)
            HCaloJetBestCSV_Passed80.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index80]);
      }
      if(BestCSVV1Index40 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4CaloJet40_Eta2p1_v1") == 1)
      {
         HCaloJetBestCSV_All40.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index40]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSV40_Eta2p1_v1") == 1)
            HCaloJetBestCSV_Passed40.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index40]);
      }
      if(BestPFCSVIndex60 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta2p1_v1") == 1)
      {
         HPFJetBestCSV_All60.Fill(MPFJet.JetCSVV2[BestPFCSVIndex60]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV60_Eta2p1_v1") == 1)
            HPFJetBestCSV_Passed60.Fill(MPFJet.JetCSVV2[BestPFCSVIndex60]);
      }
      if(BestPFCSVIndex80 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta2p1_v1") == 1)
      {
         HPFJetBestCSV_All80.Fill(MPFJet.JetCSVV2[BestPFCSVIndex80]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV80_Eta2p1_v1") == 1)
            HPFJetBestCSV_Passed80.Fill(MPFJet.JetCSVV2[BestPFCSVIndex80]);
      }
      if(BestPFCSVIndex40 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta2p1_v1") == 1)
      {
         HPFJetBestCSV_All40.Fill(MPFJet.JetCSVV2[BestPFCSVIndex40]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV40_Eta2p1_v1") == 1)
            HPFJetBestCSV_Passed40.Fill(MPFJet.JetCSVV2[BestPFCSVIndex40]);
      }

      int BestCaloJetPTIndex = -1;
      int BestPFJetPTIndex = -1;

      for(int j = 0; j < MCaloJet.JetCount; j++)
      {
         if(MCaloJet.JetEta[j] < -2.1 || MCaloJet.JetEta[j] > 2.1)
            continue;
         if(BestCaloJetPTIndex < 0 || MCaloJet.JetRawPT[BestCaloJetPTIndex] < MCaloJet.JetRawPT[j])
            BestCaloJetPTIndex = j;
      }
      for(int j = 0; j < MPFJet.JetCount; j++)
      {
         if(MPFJet.JetEta[j] < -2.1 || MPFJet.JetEta[j] > 2.1)
            continue;
         if(BestPFJetPTIndex < 0 || MPFJet.JetRawPT[BestPFJetPTIndex] < MPFJet.JetRawPT[j])
            BestPFJetPTIndex = j;
      }

      if(BestCaloJetPTIndex >= 0 && MTrigger.CheckTrigger("HLT_L1ZeroBias_BptxAND_v1") == 1)
      {
         HCaloJetBestPT_All.Fill(MCaloJet.JetRawPT[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta2p1_v1") == 1)
            HCaloJetBestPT_Passed60.Fill(MCaloJet.JetRawPT[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta2p1_v1") == 1)
            HCaloJetBestPT_Passed80.Fill(MCaloJet.JetRawPT[BestCaloJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet40_Eta2p1_v1") == 1)
            HCaloJetBestPT_Passed40.Fill(MCaloJet.JetRawPT[BestCaloJetPTIndex]);
      }
      if(BestPFJetPTIndex >= 0 && MTrigger.CheckTrigger("HLT_L1ZeroBias_BptxAND_v1") == 1)
      {
         HPFJetBestPT_All.Fill(MPFJet.JetRawPT[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta2p1_v1") == 1)
            HPFJetBestPT_Passed60.Fill(MPFJet.JetRawPT[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta2p1_v1") == 1)
            HPFJetBestPT_Passed80.Fill(MPFJet.JetRawPT[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta2p1_v1") == 1)
            HPFJetBestPT_Passed40.Fill(MPFJet.JetRawPT[BestPFJetPTIndex]);
      }
         
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta2p1_v1") == 1 && BestCaloJetPTIndex >= 0
         && MCaloJet.JetRawPT[BestCaloJetPTIndex] < 30)
      {
         cout << "BEGIN EVENT " << MTrigger.Run << " " << MTrigger.Event << " " << MTrigger.Lumi << endl;
         for(int j = 0; j < MCaloJet.JetCount; j++)
            cout << j << " " << MCaloJet.JetEta[j] << " " << MCaloJet.JetRawPT[j] << endl;
      }
      else if(i < 50)
      {
         cout << "BEGIN GOODEVENT " << MTrigger.Run << " " << MTrigger.Event << " " << MTrigger.Lumi << endl;
         for(int j = 0; j < MCaloJet.JetCount; j++)
            cout << j << " " << MCaloJet.JetEta[j] << " " << MCaloJet.JetRawPT[j] << endl;
      }
   }

   HCaloJetBestCSV_All60.Write();
   HCaloJetBestCSV_All80.Write();
   HCaloJetBestCSV_All40.Write();
   HCaloJetBestCSV_Passed60.Write();
   HCaloJetBestCSV_Passed80.Write();
   HCaloJetBestCSV_Passed40.Write();
   HPFJetBestCSV_All60.Write();
   HPFJetBestCSV_All80.Write();
   HPFJetBestCSV_All40.Write();
   HPFJetBestCSV_Passed60.Write();
   HPFJetBestCSV_Passed80.Write();
   HPFJetBestCSV_Passed40.Write();
   
   HCaloJetBestPT_All.Write();
   HCaloJetBestPT_Passed60.Write();
   HCaloJetBestPT_Passed80.Write();
   HCaloJetBestPT_Passed40.Write();
   HPFJetBestPT_All.Write();
   HPFJetBestPT_Passed60.Write();
   HPFJetBestPT_Passed80.Write();
   HPFJetBestPT_Passed40.Write();

   OutputFile.Close();

   HLTFile->Close();
   ForestFile->Close();

   delete HLTFile;
   delete ForestFile;

   return 0;
}









