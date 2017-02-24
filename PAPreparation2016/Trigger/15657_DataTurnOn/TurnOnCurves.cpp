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
   TH1D HPassL112CaloJets("HPassL112CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL116CaloJets("HPassL116CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL124CaloJets("HPassL124CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL136CaloJets("HPassL136CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL152CaloJets("HPassL152CaloJets", ";pt;", 100, 0, 200);
   
   TH1D HAllCaloJetsF1("HAllCaloJetsF1", ";pt;", 100, 0, 200);
   TH1D HAllCaloJetsF2("HAllCaloJetsF2", ";pt;", 100, 0, 200);
   TH1D HPassL112F1CaloJets("HPassL112F1CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL112F2CaloJets("HPassL112F2CaloJets", ";pt;", 100, 0, 200);
   TH1D HPassL124F1CaloJets("HPassL124F1CaloJets", ";pt;", 100, 0, 200);
   
   TH1D HFireL112CaloJets("HFireL112CaloJets", ";pt;", 100, 0, 200);
   TH1D HFireL116CaloJets("HFireL116CaloJets", ";pt;", 100, 0, 200);
   TH1D HFireL124CaloJets("HFireL124CaloJets", ";pt;", 100, 0, 200);
   TH1D HFireL136CaloJets("HFireL136CaloJets", ";pt;", 100, 0, 200);
   TH1D HFireL152CaloJets("HFireL152CaloJets", ";pt;", 100, 0, 200);
   TH1D HFireL112F1CaloJets("HFireL112F1CaloJets", ";pt;", 100, 0, 200);
   TH1D HFireL112F2CaloJets("HFireL112F2CaloJets", ";pt;", 100, 0, 200);
   TH1D HFireL124F1CaloJets("HFireL124F1CaloJets", ";pt;", 100, 0, 200);

   TH1D HPass40CaloJets("HPass40CaloJets", ";pt;", 100, 0, 200);
   TH1D HPass60CaloJets("HPass60CaloJets", ";pt;", 100, 0, 200);
   TH1D HPass80CaloJets("HPass80CaloJets", ";pt;", 100, 0, 200);
   TH1D HPass100CaloJets("HPass100CaloJets", ";pt;", 100, 0, 200);
   
   TH1D HFireL112PFJets("HFireL112PFJets", ";pt;", 100, 0, 200);
   TH1D HFireL116PFJets("HFireL116PFJets", ";pt;", 100, 0, 200);
   TH1D HFireL124PFJets("HFireL124PFJets", ";pt;", 100, 0, 200);
   TH1D HFireL136PFJets("HFireL136PFJets", ";pt;", 100, 0, 200);
   TH1D HFireL152PFJets("HFireL152PFJets", ";pt;", 100, 0, 200);
   TH1D HFireL112F1PFJets("HFireL112F1PFJets", ";pt;", 100, 0, 200);
   TH1D HFireL112F2PFJets("HFireL112F2PFJets", ";pt;", 100, 0, 200);
   TH1D HFireL124F1PFJets("HFireL124F1PFJets", ";pt;", 100, 0, 200);
   
   TH1D HPass40PFJets("HPass40PFJets", ";pt;", 100, 0, 200);
   TH1D HPass60PFJets("HPass60PFJets", ";pt;", 100, 0, 200);
   TH1D HPass80PFJets("HPass80PFJets", ";pt;", 100, 0, 200);
   TH1D HPass100PFJets("HPass100PFJets", ";pt;", 100, 0, 200);
   TH1D HPass120PFJets("HPass120PFJets", ";pt;", 100, 0, 200);
   
   int EntryCount = MTrigger.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      MHiEvent.GetEntry(i);
      MCaloJet.GetEntry(i);
      MPFJet.GetEntry(i);
      MTrigger.GetEntry(i);
      MSkim.GetEntry(i);

      bool Good = false;
      switch(MHiEvent.Run)
      {
         case 285090:
            if(MHiEvent.Lumi >= 60 && MHiEvent.Lumi <= 190)    Good = true;
            if(MHiEvent.Lumi >= 270 && MHiEvent.Lumi <= 370)   Good = true;
            break;
         case 285216:
            if(MHiEvent.Lumi >= 35 && MHiEvent.Lumi <= 2065)   Good = true;
            break;
         case 285368:
            if(MHiEvent.Lumi >= 30 && MHiEvent.Lumi <= 500)    Good = true;
            break;
         case 285480:
            if(MHiEvent.Lumi >= 1 && MHiEvent.Lumi <= 1000)    Good = true;
            break;
         case 285505:
            if(MHiEvent.Lumi >= 12 && MHiEvent.Lumi <= 527)    Good = true;
            break;
         case 285517:
            if(MHiEvent.Lumi >= 98 && MHiEvent.Lumi <= 1569)   Good = true;
            break;
         case 285750:
            if(MHiEvent.Lumi >= 0 && MHiEvent.Lumi <= 1240)    Good = true;
            break;
         case 285759:
            if(MHiEvent.Lumi >= 74 && MHiEvent.Lumi <= 455)    Good = true;
            break;
         default:
            Good = true;
            break;
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
      if(MTrigger.CheckTriggerStartWith("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v") == 1)   PassMB = true;

      bool PassCalo40 = false, PassCalo60 = false, PassCalo80 = false, PassCalo100 = false;
      double Calo40Scale = 0, Calo60Scale = 0, Calo80Scale = 0, Calo100Scale = 0;
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4CaloJet40_Eta5p1_v") == 1)   PassCalo40 = true;
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4CaloJet60_Eta5p1_v") == 1)   PassCalo60 = true;
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4CaloJet80_Eta5p1_v") == 1)   PassCalo80 = true;
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4CaloJet100_Eta5p1_v") == 1)   PassCalo100 = true;

      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4CaloJet40_Eta5p1_v") >= 0)
         Calo40Scale = MTrigger.GetPrescaleStartWith("HLT_PAAK4CaloJet40_Eta5p1_v");
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4CaloJet60_Eta5p1_v") >= 0)
         Calo60Scale = MTrigger.GetPrescaleStartWith("HLT_PAAK4CaloJet60_Eta5p1_v");
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4CaloJet80_Eta5p1_v") >= 0)
         Calo80Scale = MTrigger.GetPrescaleStartWith("HLT_PAAK4CaloJet80_Eta5p1_v");
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4CaloJet100_Eta5p1_v") >= 0)
         Calo100Scale = MTrigger.GetPrescaleStartWith("HLT_PAAK4CaloJet100_Eta5p1_v");

      bool PassPF40 = false, PassPF60 = false, PassPF80 = false, PassPF100 = false, PassPF120 = false;
      double PF40Scale = 0, PF60Scale = 0, PF80Scale = 0, PF100Scale = 0, PF120Scale = 0;
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet40_Eta5p1_v") == 1)   PassPF40 = true;
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet60_Eta5p1_v") == 1)   PassPF60 = true;
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet80_Eta5p1_v") == 1)   PassPF80 = true;
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet100_Eta5p1_v") == 1)   PassPF100 = true;
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet120_Eta5p1_v") == 1)   PassPF120 = true;

      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet40_Eta5p1_v") >= 0)
         PF40Scale = MTrigger.GetPrescaleStartWith("HLT_PAAK4PFJet40_Eta5p1_v");
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet60_Eta5p1_v") >= 0)
         PF60Scale = MTrigger.GetPrescaleStartWith("HLT_PAAK4PFJet60_Eta5p1_v");
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet80_Eta5p1_v") >= 0)
         PF80Scale = MTrigger.GetPrescaleStartWith("HLT_PAAK4PFJet80_Eta5p1_v");
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet100_Eta5p1_v") >= 0)
         PF100Scale = MTrigger.GetPrescaleStartWith("HLT_PAAK4PFJet100_Eta5p1_v");
      if(MTrigger.CheckTriggerStartWith("HLT_PAAK4PFJet120_Eta5p1_v") >= 0)
         PF120Scale = MTrigger.GetPrescaleStartWith("HLT_PAAK4PFJet120_Eta5p1_v");

      bool PassL112 = false, PassL116 = false, PassL124 = false, PassL136 = false, PassL152 = false;
      bool PassL112F1 = false, PassL112F2 = false, PassL124F1 = false;
      if(MTrigger.CheckTrigger("L1_SingleJet12_BptxAND_Initial") == 1)   PassL112 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet16_BptxAND_Initial") == 1)   PassL116 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet24_BptxAND_Initial") == 1)   PassL124 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet36_BptxAND_Initial") == 1)   PassL136 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet52_BptxAND_Initial") == 1)   PassL152 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet12_ForEta1p5_BptxAND_Initial") == 1)   PassL112F1 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet12_ForEta2p5_BptxAND_Initial") == 1)   PassL112F2 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet24_ForEta1p5_BptxAND_Initial") == 1)   PassL124F1 = true;
      
      bool FireL112 = false, FireL116 = false, FireL124 = false, FireL136 = false, FireL152 = false;
      bool FireL112F1 = false, FireL112F2 = false, FireL124F1 = false;
      if(MTrigger.CheckTrigger("L1_SingleJet12_BptxAND_Final") == 1)   FireL112 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet16_BptxAND_Final") == 1)   FireL116 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet24_BptxAND_Final") == 1)   FireL124 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet36_BptxAND_Final") == 1)   FireL136 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet52_BptxAND_Final") == 1)   FireL152 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet12_ForEta1p5_BptxAND_Final") == 1)   FireL112F1 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet12_ForEta2p5_BptxAND_Final") == 1)   FireL112F2 = true;
      if(MTrigger.CheckTrigger("L1_SingleJet24_ForEta1p5_BptxAND_Final") == 1)   FireL124F1 = true;

      if(PassMB == true)
      {
         if(BestCaloJetPTIndex >= 0 && fabs(MCaloJet.JetEta[BestCaloJetPTIndex]) < 5.1)
         {
            HAllCaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
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
            
            if(FireL112 == true)
               HFireL112CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(FireL116 == true)
               HFireL116CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(FireL124 == true)
               HFireL124CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(FireL136 == true)
               HFireL136CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(FireL152 == true)
               HFireL152CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);

            if(FireL112 == true && PassCalo40 == true)
               HPass40CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo40Scale);
            if(FireL124 == true && PassCalo60 == true)
               HPass60CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo60Scale);
            if(FireL136 == true && PassCalo80 == true)
               HPass80CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo80Scale);
            if(FireL152 == true && PassCalo100 == true)
               HPass100CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex], Calo100Scale);
         }
         if(BestCaloJetPTIndex >= 0
            && fabs(MCaloJet.JetEta[BestCaloJetPTIndex]) < 5.1 && fabs(MCaloJet.JetEta[BestCaloJetPTIndex]) > 1.5)
         {
            HAllCaloJetsF1.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(PassL112F1 == true)
               HPassL112F1CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(PassL124F1 == true)
               HPassL124F1CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            
            if(FireL112F1 == true)
               HFireL112F1CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(FireL124F1 == true)
               HFireL124F1CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
         }
         if(BestCaloJetPTIndex >= 0
            && fabs(MCaloJet.JetEta[BestCaloJetPTIndex]) < 5.1 && fabs(MCaloJet.JetEta[BestCaloJetPTIndex]) > 2.5)
         {
            HAllCaloJetsF2.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            if(PassL112F2 == true)
               HPassL112F2CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
            
            if(FireL112F2 == true)
               HFireL112F2CaloJets.Fill(MCaloJet.JetPT[BestCaloJetPTIndex]);
         }
         if(BestPFJetPTIndex >= 0 && fabs(MPFJet.JetEta[BestPFJetPTIndex]) < 5.1)
         {
            if(FireL112 == true)
               HFireL112PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
            if(FireL116 == true)
               HFireL116PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
            if(FireL124 == true)
               HFireL124PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
            if(FireL136 == true)
               HFireL136PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
            if(FireL152 == true)
               HFireL152PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);

            if(FireL112 == true && PassPF40 == true)
               HPass40PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF40Scale);
            if(FireL116 == true && PassPF60 == true)
               HPass60PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF60Scale);
            if(FireL124 == true && PassPF80 == true)
               HPass80PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF80Scale);
            if(FireL136 == true && PassPF100 == true)
               HPass100PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF100Scale);
            if(FireL152 == true && PassPF120 == true)
               HPass120PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex], PF120Scale);
         }
         if(BestPFJetPTIndex >= 0
            && fabs(MPFJet.JetEta[BestPFJetPTIndex]) < 5.1 && fabs(MPFJet.JetEta[BestPFJetPTIndex]) > 1.5)
         {
            if(FireL112F1 == true)
               HFireL112F1PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
            if(FireL124F1 == true)
               HFireL124F1PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
         }
         if(BestPFJetPTIndex >= 0
            && fabs(MPFJet.JetEta[BestPFJetPTIndex]) < 5.1 && fabs(MPFJet.JetEta[BestPFJetPTIndex]) > 2.5)
         {
            if(FireL112F2 == true)
               HFireL112F2PFJets.Fill(MPFJet.JetPT[BestPFJetPTIndex]);
         }
      }
   }

   HAllCaloJets.Write();
   HPassL112CaloJets.Write();
   HPassL116CaloJets.Write();
   HPassL124CaloJets.Write();
   HPassL136CaloJets.Write();
   HPassL152CaloJets.Write();
   
   HAllCaloJetsF1.Write();
   HAllCaloJetsF2.Write();
   HPassL112F1CaloJets.Write();
   HPassL112F2CaloJets.Write();
   HPassL124F1CaloJets.Write();
   
   HFireL112CaloJets.Write();
   HFireL116CaloJets.Write();
   HFireL124CaloJets.Write();
   HFireL136CaloJets.Write();
   HFireL152CaloJets.Write();
   HFireL112F1CaloJets.Write();
   HFireL112F2CaloJets.Write();
   HFireL124F1CaloJets.Write();

   HPass40CaloJets.Write();
   HPass60CaloJets.Write();
   HPass80CaloJets.Write();
   HPass100CaloJets.Write();
   
   HFireL112PFJets.Write();
   HFireL116PFJets.Write();
   HFireL124PFJets.Write();
   HFireL136PFJets.Write();
   HFireL152PFJets.Write();
   HFireL112F1PFJets.Write();
   HFireL112F2PFJets.Write();
   HFireL124F1PFJets.Write();

   HPass40PFJets.Write();
   HPass60PFJets.Write();
   HPass80PFJets.Write();
   HPass100PFJets.Write();
   HPass120PFJets.Write();

   OutputFile.Close();

   ForestFile->Close();

   delete ForestFile;

   return 0;
}









