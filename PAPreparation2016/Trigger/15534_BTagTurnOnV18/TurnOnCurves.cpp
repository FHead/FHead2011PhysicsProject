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
   string HLTFileName = "openHLT_Tranche.root";
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
   TH1D HCaloJetBestCSVV1V1_All60("HCaloJetBestCSVV1V1_All60", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V1_All80("HCaloJetBestCSVV1V1_All80", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V1_All100("HCaloJetBestCSVV1V1_All100", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V1_Passed60("HCaloJetBestCSVV1V1_Passed60", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V1_Passed80("HCaloJetBestCSVV1V1_Passed80", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V1_Passed100("HCaloJetBestCSVV1V1_Passed100", "Trigger V1, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V2_All60("HCaloJetBestCSVV1V2_All60", "Trigger V1, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V2_All80("HCaloJetBestCSVV1V2_All80", "Trigger V1, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V2_All100("HCaloJetBestCSVV1V2_All100", "Trigger V1, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V2_Passed60("HCaloJetBestCSVV1V2_Passed60", "Trigger V1, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V2_Passed80("HCaloJetBestCSVV1V2_Passed80", "Trigger V1, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV1V2_Passed100("HCaloJetBestCSVV1V2_Passed100", "Trigger V1, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V1_All60("HCaloJetBestCSVV2V1_All60", "Trigger V2, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V1_All80("HCaloJetBestCSVV2V1_All80", "Trigger V2, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V1_All100("HCaloJetBestCSVV2V1_All100", "Trigger V2, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V1_Passed60("HCaloJetBestCSVV2V1_Passed60", "Trigger V2, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V1_Passed80("HCaloJetBestCSVV2V1_Passed80", "Trigger V2, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V1_Passed100("HCaloJetBestCSVV2V1_Passed100", "Trigger V2, offline V1;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V2_All60("HCaloJetBestCSVV2V2_All60", "Trigger V2, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V2_All80("HCaloJetBestCSVV2V2_All80", "Trigger V2, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V2_All100("HCaloJetBestCSVV2V2_All100", "Trigger V2, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V2_Passed60("HCaloJetBestCSVV2V2_Passed60", "Trigger V2, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V2_Passed80("HCaloJetBestCSVV2V2_Passed80", "Trigger V2, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HCaloJetBestCSVV2V2_Passed100("HCaloJetBestCSVV2V2_Passed100", "Trigger V2, offline V2;Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_All60("HPFJetBestCSV_All60", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_All80("HPFJetBestCSV_All80", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_All100("HPFJetBestCSV_All100", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_Passed60("HPFJetBestCSV_Passed60", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_Passed80("HPFJetBestCSV_Passed80", ";Discriminant Value;", 100, 0, 1);
   TH1D HPFJetBestCSV_Passed100("HPFJetBestCSV_Passed100", ";Discriminant Value;", 100, 0, 1);
   
   TH1D HCaloJetBestPT_All("HCaloJetBestPT_All", ";Jet PT;", 100, 0, 150);
   TH1D HCaloJetBestPT_Passed60("HCaloJetBestPT_Passed60", ";Jet PT;", 100, 0, 150);
   TH1D HCaloJetBestPT_Passed80("HCaloJetBestPT_Passed80", ";Jet PT;", 100, 0, 150);
   TH1D HCaloJetBestPT_Passed100("HCaloJetBestPT_Passed100", ";Jet PT;", 100, 0, 150);
   TH1D HPFJetBestPT_All("HPFJetBestPT_All", ";Jet PT;", 100, 0, 150);
   TH1D HPFJetBestPT_Passed60("HPFJetBestPT_Passed60", ";Jet PT;", 100, 0, 150);
   TH1D HPFJetBestPT_Passed80("HPFJetBestPT_Passed80", ";Jet PT;", 100, 0, 150);
   TH1D HPFJetBestPT_Passed100("HPFJetBestPT_Passed100", ";Jet PT;", 100, 0, 150);

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

      int BestCSVV1Index60 = -1;
      int BestCSVV1Index80 = -1;
      int BestCSVV1Index100 = -1;
      int BestCSVV2Index60 = -1;
      int BestCSVV2Index80 = -1;
      int BestCSVV2Index100 = -1;
      int BestPFCSVIndex60 = -1;
      int BestPFCSVIndex80 = -1;
      int BestPFCSVIndex100 = -1;

      for(int j = 0; j < MCaloJet.JetCount; j++)
      {
         if(MCaloJet.JetEta[j] < -2.1 || MCaloJet.JetEta[j] > 2.1)
            continue;
         if(MCaloJet.JetRawPT[j] < 35)
            continue;
         if(BestCSVV1Index60 < 0 || MCaloJet.JetCSVV1P[BestCSVV1Index60] < MCaloJet.JetCSVV1P[j])
            BestCSVV1Index60 = j;
         if(BestCSVV2Index60 < 0 || MCaloJet.JetCSVV2P[BestCSVV2Index60] < MCaloJet.JetCSVV2P[j])
            BestCSVV2Index60 = j;
         if(MCaloJet.JetRawPT[j] < 50)
            continue;
         if(BestCSVV1Index80 < 0 || MCaloJet.JetCSVV1P[BestCSVV1Index80] < MCaloJet.JetCSVV1P[j])
            BestCSVV1Index80 = j;
         if(BestCSVV2Index80 < 0 || MCaloJet.JetCSVV2P[BestCSVV2Index80] < MCaloJet.JetCSVV2P[j])
            BestCSVV2Index80 = j;
         if(MCaloJet.JetRawPT[j] < 50)
            continue;
         if(BestCSVV1Index100 < 0 || MCaloJet.JetCSVV1P[BestCSVV1Index100] < MCaloJet.JetCSVV1P[j])
            BestCSVV1Index100 = j;
         if(BestCSVV2Index100 < 0 || MCaloJet.JetCSVV2P[BestCSVV2Index100] < MCaloJet.JetCSVV2P[j])
            BestCSVV2Index100 = j;
      }
      for(int j = 0; j < MPFJet.JetCount; j++)
      {
         if(MPFJet.JetEta[j] < -2.1 || MPFJet.JetEta[j] > 2.1)
            continue;
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
         if(MPFJet.JetRawPT[j] < 95)
            continue;
         if(BestPFCSVIndex100 < 0 || MPFJet.JetCSVV2[BestPFCSVIndex100] < MPFJet.JetCSVV2[j])
            if(MPFJet.JetCSVV2[BestPFCSVIndex100] < 1000)
               BestPFCSVIndex100 = j;
      }

      if(BestCSVV1Index60 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta2p1_v1") == 1)
      {
         HCaloJetBestCSVV1V1_All60.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index60]);
         HCaloJetBestCSVV2V1_All60.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index60]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1") == 1)
            HCaloJetBestCSVV1V1_Passed60.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index60]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1") == 1)
            HCaloJetBestCSVV2V1_Passed60.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index60]);
      }
      if(BestCSVV1Index80 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta2p1_v1") == 1)
      {
         HCaloJetBestCSVV1V1_All80.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index80]);
         HCaloJetBestCSVV2V1_All80.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index80]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv180_Eta2p1_v1") == 1)
            HCaloJetBestCSVV1V1_Passed80.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index80]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv280_Eta2p1_v1") == 1)
            HCaloJetBestCSVV2V1_Passed80.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index80]);
      }
      if(BestCSVV1Index100 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4CaloJet100_Eta2p1_v1") == 1)
      {
         HCaloJetBestCSVV1V1_All100.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index100]);
         HCaloJetBestCSVV2V1_All100.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index100]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv1100_Eta2p1_v1") == 1)
            HCaloJetBestCSVV1V1_Passed100.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index100]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv2100_Eta2p1_v1") == 1)
            HCaloJetBestCSVV2V1_Passed100.Fill(MCaloJet.JetCSVV1P[BestCSVV1Index100]);
      }
      if(BestCSVV2Index60 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta2p1_v1") == 1)
      {
         HCaloJetBestCSVV1V2_All60.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index60]);
         HCaloJetBestCSVV2V2_All60.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index60]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1") == 1)
            HCaloJetBestCSVV1V2_Passed60.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index60]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1") == 1)
            HCaloJetBestCSVV2V2_Passed60.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index60]);
      }
      if(BestCSVV2Index80 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta2p1_v1") == 1)
      {
         HCaloJetBestCSVV1V2_All80.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index80]);
         HCaloJetBestCSVV2V2_All80.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index80]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv180_Eta2p1_v1") == 1)
            HCaloJetBestCSVV1V2_Passed80.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index80]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv280_Eta2p1_v1") == 1)
            HCaloJetBestCSVV2V2_Passed80.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index80]);
      }
      if(BestCSVV2Index100 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4CaloJet100_Eta2p1_v1") == 1)
      {
         HCaloJetBestCSVV1V2_All100.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index100]);
         HCaloJetBestCSVV2V2_All100.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index100]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv1100_Eta2p1_v1") == 1)
            HCaloJetBestCSVV1V2_Passed100.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index100]);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSVv2100_Eta2p1_v1") == 1)
            HCaloJetBestCSVV2V2_Passed100.Fill(MCaloJet.JetCSVV2P[BestCSVV2Index100]);
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
      if(BestPFCSVIndex100 >= 0 && MTrigger.CheckTrigger("HLT_PAAK4PFJet100_Eta2p1_v1") == 1)
      {
         HPFJetBestCSV_All100.Fill(MPFJet.JetCSVV2[BestPFCSVIndex100]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV100_Eta2p1_v1") == 1)
            HPFJetBestCSV_Passed100.Fill(MPFJet.JetCSVV2[BestPFCSVIndex100]);
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
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet100_Eta2p1_v1") == 1)
            HCaloJetBestPT_Passed100.Fill(MCaloJet.JetRawPT[BestCaloJetPTIndex]);
      }
      if(BestPFJetPTIndex >= 0 && MTrigger.CheckTrigger("HLT_L1ZeroBias_BptxAND_v1") == 1)
      {
         HPFJetBestPT_All.Fill(MPFJet.JetRawPT[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta2p1_v1") == 1)
            HPFJetBestPT_Passed60.Fill(MPFJet.JetRawPT[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta2p1_v1") == 1)
            HPFJetBestPT_Passed80.Fill(MPFJet.JetRawPT[BestPFJetPTIndex]);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet100_Eta2p1_v1") == 1)
            HPFJetBestPT_Passed100.Fill(MPFJet.JetRawPT[BestPFJetPTIndex]);
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

   HCaloJetBestCSVV1V1_All60.Write();
   HCaloJetBestCSVV1V1_All80.Write();
   HCaloJetBestCSVV1V1_All100.Write();
   HCaloJetBestCSVV1V1_Passed60.Write();
   HCaloJetBestCSVV1V1_Passed80.Write();
   HCaloJetBestCSVV1V1_Passed100.Write();
   HCaloJetBestCSVV1V2_All60.Write();
   HCaloJetBestCSVV1V2_All80.Write();
   HCaloJetBestCSVV1V2_All100.Write();
   HCaloJetBestCSVV1V2_Passed60.Write();
   HCaloJetBestCSVV1V2_Passed80.Write();
   HCaloJetBestCSVV1V2_Passed100.Write();
   HCaloJetBestCSVV2V1_All60.Write();
   HCaloJetBestCSVV2V1_All80.Write();
   HCaloJetBestCSVV2V1_All100.Write();
   HCaloJetBestCSVV2V1_Passed60.Write();
   HCaloJetBestCSVV2V1_Passed80.Write();
   HCaloJetBestCSVV2V1_Passed100.Write();
   HCaloJetBestCSVV2V2_All60.Write();
   HCaloJetBestCSVV2V2_All80.Write();
   HCaloJetBestCSVV2V2_All100.Write();
   HCaloJetBestCSVV2V2_Passed60.Write();
   HCaloJetBestCSVV2V2_Passed80.Write();
   HCaloJetBestCSVV2V2_Passed100.Write();
   HPFJetBestCSV_All60.Write();
   HPFJetBestCSV_All80.Write();
   HPFJetBestCSV_All100.Write();
   HPFJetBestCSV_Passed60.Write();
   HPFJetBestCSV_Passed80.Write();
   HPFJetBestCSV_Passed100.Write();
   
   HCaloJetBestPT_All.Write();
   HCaloJetBestPT_Passed60.Write();
   HCaloJetBestPT_Passed80.Write();
   HCaloJetBestPT_Passed100.Write();
   HPFJetBestPT_All.Write();
   HPFJetBestPT_Passed60.Write();
   HPFJetBestPT_Passed80.Write();
   HPFJetBestPT_Passed100.Write();

   OutputFile.Close();

   HLTFile->Close();
   ForestFile->Close();

   delete HLTFile;
   delete ForestFile;

   return 0;
}









