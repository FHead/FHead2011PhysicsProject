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
   string OutputFileName = "Output.root";

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " Forest.root Output.root" << endl;
      return -1;
   }

   ForestFileName = argv[1];
   OutputFileName = argv[2];

   TFile *ForestFile = TFile::Open(ForestFileName.c_str());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   HiEventTreeMessenger MHiEvent(*ForestFile);
   JetTreeMessenger MCaloJet(*ForestFile, "ak4CaloJetAnalyzer/t");
   JetTreeMessenger MPFJet(*ForestFile, "ak4PFJetAnalyzer/t");
   TriggerTreeMessenger MTrigger(*ForestFile);
   SkimTreeMessenger MSkim(*ForestFile);

   TH1D HAllCaloJets("HAllCaloJets", ";pt;", 100, 0, 200);
   TH1D HAllCaloJets40("HAllCaloJets40", ";pt;", 100, 0, 200);
   TH1D HAllCaloJets60("HAllCaloJets60", ";pt;", 100, 0, 200);
   TH1D HAllCaloJets80("HAllCaloJets80", ";pt;", 100, 0, 200);
   TH1D HPass40CaloJets("HPass40CaloJets", ";pt;", 100, 0, 200);
   TH1D HPass60CaloJets("HPass60CaloJets", ";pt;", 100, 0, 200);
   TH1D HPass80CaloJets("HPass80CaloJets", ";pt;", 100, 0, 200);
   
   TH1D HForwardCaloJets("HForwardCaloJets", ";pt;", 100, 0, 200);
   TH1D HForwardCaloJets40("HForwardCaloJets40", ";pt;", 100, 0, 200);
   TH1D HForwardCaloJets60("HForwardCaloJets60", ";pt;", 100, 0, 200);
   TH1D HForwardCaloJets80("HForwardCaloJets80", ";pt;", 100, 0, 200);
   TH1D HForwardPass40CaloJets("HForwardPass40CaloJets", ";pt;", 100, 0, 200);
   TH1D HForwardPass60CaloJets("HForwardPass60CaloJets", ";pt;", 100, 0, 200);
   TH1D HForwardPass80CaloJets("HForwardPass80CaloJets", ";pt;", 100, 0, 200);

   TH1D HPassL112CaloJets("HPassL112CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL116CaloJets("HPassL116CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL124CaloJets("HPassL124CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL136CaloJets("HPassL136CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL152CaloJets("HPassL152CaloJets", ";pt;", 100, 0, 200);

   TH1D HAllPFJets("HAllPFJets", ";pt;", 100, 0, 200);
   TH1D HAllPFJets40("HAllPFJets40", ";pt;", 100, 0, 200);
   TH1D HAllPFJets60("HAllPFJets60", ";pt;", 100, 0, 200);
   TH1D HAllPFJets80("HAllPFJets80", ";pt;", 100, 0, 200);
   TH1D HPass40PFJets("HPass40PFJets", ";pt;", 100, 0, 200);
   TH1D HPass60PFJets("HPass60PFJets", ";pt;", 100, 0, 200);
   TH1D HPass80PFJets("HPass80PFJets", ";pt;", 100, 0, 200);
   
   TH1D HForwardPFJets("HForwardPFJets", ";pt;", 100, 0, 200);
   TH1D HForwardPFJets40("HForwardPFJets40", ";pt;", 100, 0, 200);
   TH1D HForwardPFJets60("HForwardPFJets60", ";pt;", 100, 0, 200);
   TH1D HForwardPFJets80("HForwardPFJets80", ";pt;", 100, 0, 200);
   TH1D HForwardPass40PFJets("HForwardPass40PFJets", ";pt;", 100, 0, 200);
   TH1D HForwardPass60PFJets("HForwardPass60PFJets", ";pt;", 100, 0, 200);
   TH1D HForwardPass80PFJets("HForwardPass80PFJets", ";pt;", 100, 0, 200);

   TH1D HPassCalo40PFJets("HPassCalo40PFJets", ";pt;", 100, 0, 200);
   TH1D HPassCalo60PFJets("HPassCalo60PFJets", ";pt;", 100, 0, 200);
   TH1D HPassCalo80PFJets("HPassCalo80PFJets", ";pt;", 100, 0, 200);

   TH2D HAllPFJetsPTEta("HAllPFJetsPTEta", ";pt;eta", 100, 0, 200, 100, -5.1, 5.1);
   TH2D HPass40PFJetsPTEta("HPass40PFJetsPTEta", ";pt;eta", 100, 0, 200, 100, -5.1, 5.1);
   TH2D HPass60PFJetsPTEta("HPass60PFJetsPTEta", ";pt;eta", 100, 0, 200, 100, -5.1, 5.1);
   TH2D HPass80PFJetsPTEta("HPass80PFJetsPTEta", ";pt;eta", 100, 0, 200, 100, -5.1, 5.1);

   int EntryCount = MTrigger.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      MHiEvent.GetEntry(i);
      MCaloJet.GetEntry(i);
      MPFJet.GetEntry(i);
      MTrigger.GetEntry(i);
      MSkim.GetEntry(i);

      bool Good = false;
      if(MHiEvent.Run == 285090)
      {
         if(MHiEvent.Lumi >= 60 && MHiEvent.Lumi <= 190)
            Good = true;
         if(MHiEvent.Lumi >= 270 && MHiEvent.Lumi <= 370)
            Good = true;
      }
      if(MHiEvent.Run == 285216)
      {
         if(MHiEvent.Lumi >= 35 && MHiEvent.Lumi <= 2065)
            Good = true;
      }
      if(MHiEvent.Run == 285368)
      {
         if(MHiEvent.Lumi >= 30 && MHiEvent.Lumi <= 500)
            Good = true;
      }
      if(MHiEvent.Run == 285480)
      {
         if(MHiEvent.Lumi >= 1 && MHiEvent.Lumi <= 1000)
            Good = true;
      }
      if(MHiEvent.Run == 285505)
      {
         if(MHiEvent.Lumi >= 12 && MHiEvent.Lumi <= 527)
            Good = true;
      }
      if(MHiEvent.Run == 285517)
      {
         if(MHiEvent.Lumi >= 98 && MHiEvent.Lumi <= 1569)
            Good = true;
      }
      if(MHiEvent.Run == 285750)
      {
         if(MHiEvent.Lumi >= 0 && MHiEvent.Lumi <= 1240)
            Good = true;
      }
      if(MHiEvent.Run == 285759)
      {
         if(MHiEvent.Lumi >= 74 && MHiEvent.Lumi <= 455)
            Good = true;
      }
      if(MSkim.HBHENoise == 0)
         Good = false;
      if(MSkim.PVFilter == 0)
         Good = false;
      if(MSkim.HFCoincidenceFilter == 0)
         Good = false;
      if(Good == false)
         continue;

      int BestCaloJetPTIndex = -1;
      int BestPFJetPTIndex = -1;

      for(int j = 0; j < MCaloJet.JetCount; j++)
      {
         if(MCaloJet.JetEta[j] < -EtaRange || MCaloJet.JetEta[j] > EtaRange)
            continue;
         if(BestCaloJetPTIndex < 0 || MCaloJet.JetPT[BestCaloJetPTIndex] < MCaloJet.JetPT[j])
            BestCaloJetPTIndex = j;
      }
      for(int j = 0; j < MPFJet.JetCount; j++)
      {
         if(MPFJet.JetEta[j] < -EtaRange || MPFJet.JetEta[j] > EtaRange)
            continue;
         if(BestPFJetPTIndex < 0 || MPFJet.JetPT[BestPFJetPTIndex] < MPFJet.JetPT[j])
            BestPFJetPTIndex = j;
      }

      bool PassMB = false;
      if(MTrigger.CheckTrigger("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v1") == 1)   PassMB = true;
      if(MTrigger.CheckTrigger("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v2") == 1)   PassMB = true;
      if(MTrigger.CheckTrigger("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v3") == 1)   PassMB = true;
      if(MTrigger.CheckTrigger("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v4") == 1)   PassMB = true;
      if(MTrigger.CheckTrigger("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v5") == 1)   PassMB = true;

      bool PassCalo40 = false, PassCalo60 = false, PassCalo80 = false;
      double Calo40Scale = 0, Calo60Scale = 0, Calo80Scale = 0;
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet40_Eta5p1_v2") == 1)   PassCalo40 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet40_Eta5p1_v3") == 1)   PassCalo40 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta5p1_v2") == 1)   PassCalo60 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta5p1_v3") == 1)   PassCalo60 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta5p1_v2") == 1)   PassCalo80 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta5p1_v3") == 1)   PassCalo80 = true;

      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet40_Eta5p1_v2") >= 0)   Calo40Scale = MTrigger.GetPrescale("HLT_PAAK4CaloJet40_Eta5p1_v2");
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet40_Eta5p1_v3") >= 0)   Calo40Scale = MTrigger.GetPrescale("HLT_PAAK4CaloJet40_Eta5p1_v3");
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta5p1_v2") >= 0)   Calo60Scale = MTrigger.GetPrescale("HLT_PAAK4CaloJet60_Eta5p1_v2");
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta5p1_v3") >= 0)   Calo60Scale = MTrigger.GetPrescale("HLT_PAAK4CaloJet60_Eta5p1_v3");
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta5p1_v2") >= 0)   Calo80Scale = MTrigger.GetPrescale("HLT_PAAK4CaloJet80_Eta5p1_v2");
      if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta5p1_v3") >= 0)   Calo80Scale = MTrigger.GetPrescale("HLT_PAAK4CaloJet80_Eta5p1_v3");

      bool PassPF40 = false, PassPF60 = false, PassPF80 = false;
      double PF40Scale = 0, PF60Scale = 0, PF80Scale = 0;
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1_v2") == 1)   PassPF40 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1_v3") == 1)   PassPF40 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1_v4") == 1)   PassPF40 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v2") == 1)   PassPF60 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v3") == 1)   PassPF60 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v4") == 1)   PassPF60 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v2") == 1)   PassPF80 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v3") == 1)   PassPF80 = true;
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v4") == 1)   PassPF80 = true;

      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1_v2") >= 0)   PF40Scale = MTrigger.GetPrescale("HLT_PAAK4PFJet40_Eta5p1_v2");
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1_v3") >= 0)   PF40Scale = MTrigger.GetPrescale("HLT_PAAK4PFJet40_Eta5p1_v3");
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta5p1_v4") >= 0)   PF40Scale = MTrigger.GetPrescale("HLT_PAAK4PFJet40_Eta5p1_v4");
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v2") >= 0)   PF60Scale = MTrigger.GetPrescale("HLT_PAAK4PFJet60_Eta5p1_v2");
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v3") >= 0)   PF60Scale = MTrigger.GetPrescale("HLT_PAAK4PFJet60_Eta5p1_v3");
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta5p1_v4") >= 0)   PF60Scale = MTrigger.GetPrescale("HLT_PAAK4PFJet60_Eta5p1_v4");
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v2") >= 0)   PF80Scale = MTrigger.GetPrescale("HLT_PAAK4PFJet80_Eta5p1_v2");
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v3") >= 0)   PF80Scale = MTrigger.GetPrescale("HLT_PAAK4PFJet80_Eta5p1_v3");
      if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v4") >= 0)   PF80Scale = MTrigger.GetPrescale("HLT_PAAK4PFJet80_Eta5p1_v4");

      bool PassL112 = false, PassL116 = false, PassL124 = false, PassL136 = false, PassL152 = false;
      if(MTrigger.CheckTrigger("L1_SingleJet12_BptxAND_Initial") == 1)   PassL112 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet16_BptxAND_Initial") == 1)   PassL116 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet24_BptxAND_Initial") == 1)   PassL124 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet36_BptxAND_Initial") == 1)   PassL136 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet52_BptxAND_Initial") == 1)   PassL152 = true;

      if(PassMB == true)
      {
         if(BestCaloJetPTIndex >= 0 && fabs(MCaloJet.JetEta[BestCaloJetPTIndex]) < 5.1)
         {
            if(PassCalo40 == true)
               cout << Calo40Scale << endl;

            HAllCaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            HAllCaloJets40.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], PF40Scale);
            HAllCaloJets60.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], PF60Scale);
            HAllCaloJets80.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], PF80Scale);
            if(PassCalo40 == true)
               HPass40CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo40Scale);
            if(PassCalo60 == true)
               HPass60CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo60Scale);
            if(PassCalo80 == true)
               HPass80CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo80Scale);
            if(PassL112 == true)
               HPassL112CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(PassL116 == true)
               HPassL116CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(PassL124 == true)
               HPassL124CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(PassL136 == true)
               HPassL136CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(PassL152 == true)
               HPassL152CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);

            if(fabs(MCaloJet.JetEta[BestCaloJetPTIndex]) > 3)
            {
               HForwardCaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
               HForwardCaloJets40.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], PF40Scale);
               HForwardCaloJets60.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], PF60Scale);
               HForwardCaloJets80.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], PF80Scale);
               if(PassCalo40 == true)
                  HForwardPass40CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo40Scale);
               if(PassCalo60 == true)
                  HForwardPass60CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo60Scale);
               if(PassCalo80 == true)
                  HForwardPass80CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo80Scale);
            }

            if(PassCalo60 == false && MCaloJet.JetPT[BestCaloJetPTIndex] > 70)
            {
               cout << "CaloJet60 " << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event << " " << MCaloJet.JetPT[BestCaloJetPTIndex] << endl;
            }
            if(PassCalo80 == false && MCaloJet.JetPT[BestCaloJetPTIndex] > 90)
            {
               cout << "CaloJet80 " << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event << " " << MCaloJet.JetPT[BestCaloJetPTIndex] << endl;
            }

            if(PassL152 == false && MCaloJet.JetPT[BestCaloJetPTIndex] > 90)
            {
               cout << "L1Jet52 " << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event << " " << MCaloJet.JetPT[BestCaloJetPTIndex] << endl;
            }
         }
         if(BestPFJetPTIndex >= 0 && fabs(MPFJet.JetEta[BestPFJetPTIndex]) < 5.1)
         {
            HAllPFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
            HAllPFJets40.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF40Scale);
            HAllPFJets60.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF60Scale);
            HAllPFJets80.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF80Scale);
            if(PassPF40 == true)
               HPass40PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF40Scale);
            if(PassPF60 == true)
               HPass60PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF60Scale);
            if(PassPF80 == true)
               HPass80PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF80Scale);
            if(PassCalo40 == true)
               HPassCalo40PFJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo40Scale);
            if(PassCalo60 == true)
               HPassCalo60PFJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo60Scale);
            if(PassCalo80 == true)
               HPassCalo80PFJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo80Scale);
            
            if(fabs(MPFJet.JetEta[BestPFJetPTIndex]) > 3)
            {
               HForwardPFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
               HForwardPFJets40.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF40Scale);
               HForwardPFJets60.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF60Scale);
               HForwardPFJets80.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF80Scale);
               if(PassPF40 == true)
                  HForwardPass40PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF40Scale);
               if(PassPF60 == true)
                  HForwardPass60PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF60Scale);
               if(PassPF80 == true)
                  HForwardPass80PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF80Scale);
            }

            if(PassPF60 == false && MPFJet.JetPT[BestPFJetPTIndex] > 80)
            {
               cout << "PFJet60 " << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event << " " << MPFJet.JetPT[BestPFJetPTIndex] << endl;
            }
            if(PassPF80 == false && MPFJet.JetPT[BestPFJetPTIndex] > 100)
            {
               cout << "PFJet80 " << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event << " " << MPFJet.JetPT[BestPFJetPTIndex] << endl;
            }
         }
         if(BestPFJetPTIndex >= 0 && fabs(MPFJet.JetEta[BestPFJetPTIndex]) < 5.1)
         {
            HAllPFJetsPTEta.Fill(MPFJet.JetPT[BestPFJetPTIndex], MPFJet.JetEta[BestPFJetPTIndex]);
            if(PassPF40 == true)
               HPass40PFJetsPTEta.Fill(MPFJet.JetPT[BestPFJetPTIndex], MPFJet.JetEta[BestPFJetPTIndex], PF40Scale);
            if(PassPF60 == true)
               HPass60PFJetsPTEta.Fill(MPFJet.JetPT[BestPFJetPTIndex], MPFJet.JetEta[BestPFJetPTIndex], PF60Scale);
            if(PassPF80 == true)
               HPass80PFJetsPTEta.Fill(MPFJet.JetPT[BestPFJetPTIndex], MPFJet.JetEta[BestPFJetPTIndex], PF80Scale);
         }
      }
   }

   HAllCaloJets.Write();
   HAllCaloJets40.Write();
   HAllCaloJets60.Write();
   HAllCaloJets80.Write();
   HPass40CaloJets.Write();
   HPass60CaloJets.Write();
   HPass80CaloJets.Write();

   HForwardCaloJets.Write();
   HForwardCaloJets40.Write();
   HForwardCaloJets60.Write();
   HForwardCaloJets80.Write();
   HForwardPass40CaloJets.Write();
   HForwardPass60CaloJets.Write();
   HForwardPass80CaloJets.Write();

   HPassL112CaloJets.Write();
   HPassL116CaloJets.Write();
   HPassL124CaloJets.Write();
   HPassL136CaloJets.Write();
   HPassL152CaloJets.Write();

   HAllPFJets.Write();
   HAllPFJets40.Write();
   HAllPFJets60.Write();
   HAllPFJets80.Write();
   HPass40PFJets.Write();
   HPass60PFJets.Write();
   HPass80PFJets.Write();
   HPassCalo40PFJets.Write();
   HPassCalo60PFJets.Write();
   HPassCalo80PFJets.Write();

   HForwardPFJets.Write();
   HForwardPFJets40.Write();
   HForwardPFJets60.Write();
   HForwardPFJets80.Write();
   HForwardPass40PFJets.Write();
   HForwardPass60PFJets.Write();
   HForwardPass80PFJets.Write();

   HAllPFJetsPTEta.Write();
   HPass40PFJetsPTEta.Write();
   HPass60PFJetsPTEta.Write();
   HPass80PFJetsPTEta.Write();

   OutputFile.Close();

   ForestFile->Close();

   delete ForestFile;

   return 0;
}









