#include <iostream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"

#include "Messenger.h"
#include "EventMatching.h"

int main()
{
   string ForestName = "HiForestAOD.root";
   string HLTName = "openHLT.root";
   string OutputName = "Output.root";

   TFile ForestFile(ForestName.c_str());
   TFile HLTFile(HLTName.c_str());

   TriggerTreeMessenger MTrigger(HLTFile, "hltbitanalysis/HltTree");

   HiEventTreeMessenger MHiEvent(ForestFile);
   JetTreeMessenger MCaloJet(ForestFile, "ak4CaloJetAnalyzer/t");
   JetTreeMessenger MPFJet(ForestFile, "ak4PFJetAnalyzer/t");
   GenParticleTreeMessenger MGen(ForestFile);

   map<EventCoordinate, int> Location = BuildMap(MTrigger, true);
   Location = BuildMap(MHiEvent, Location);

   vector<string> Labels(16);
   Labels[0] = "All";
   Labels[1] = "Pass Calo Jet 40";
   Labels[2] = "Pass Calo Jet 60";
   Labels[3] = "Pass Calo Jet 80";
   Labels[4] = "Pass PF Jet 40";
   Labels[5] = "Pass PF Jet 60";
   Labels[6] = "Pass PF Jet 80";
   Labels[7] = "Pass Calo Jet CSV 40";
   Labels[8] = "Pass Calo Jet CSV 60";
   Labels[9] = "Pass Calo Jet CSV 80";
   Labels[10] = "Pass PF Jet CSV 40";
   Labels[11] = "Pass PF Jet CSV 60";
   Labels[12] = "Pass PF Jet CSV 80";
   Labels[13] = "Pass PF Jet CSV 40 (CT)";
   Labels[14] = "Pass PF Jet CSV 60 (CT)";
   Labels[15] = "Pass PF Jet CSV 80 (CT)";

   vector<string> JetLabels(7);
   JetLabels[0] = "All";
   JetLabels[1] = "Central Calo B 40";
   JetLabels[2] = "Central Calo B 60";
   JetLabels[3] = "Central Calo B 80";
   JetLabels[4] = "Central PF B 40";
   JetLabels[5] = "Central PF B 60";
   JetLabels[6] = "Central PF B 80";

   TFile OutputFile(OutputName.c_str(), "RECREATE");

   TH2D HYield("HYield", ";;", 16, 0, 16, 7, 0, 7);
   for(int i = 1; i <= 16; i++)
      HYield.GetXaxis()->SetBinLabel(i, Labels[i-1].c_str());
   for(int j = 1; j <= 7; j++)
      HYield.GetYaxis()->SetBinLabel(j, JetLabels[j-1].c_str());

   int EntryCount = MTrigger.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MTrigger.GetEntry(iE);

      EventCoordinate E(MTrigger);
      if(Location.find(E) == Location.end())
         continue;
      if(Location[E] == -1)
         continue;

      int IE = Location[E];

      MHiEvent.GetEntry(IE);
      MCaloJet.GetEntry(IE);
      MPFJet.GetEntry(IE);

      bool CentralCaloB40 = false;
      bool CentralCaloB60 = false;
      bool CentralCaloB80 = false;
      bool CentralPFB40 = false;
      bool CentralPFB60 = false;
      bool CentralPFB80 = false;

      for(int i = 0; i < MCaloJet.JetCount; i++)
      {
         if(MCaloJet.JetEta[i] < -2.1 || MCaloJet.JetEta[i] > 2.1)   continue;
         if(abs(MCaloJet.RefPartonFlavorForB[i]) != 5)               continue;
         if(MCaloJet.JetPT[i] < 40)                                  continue;

         CentralCaloB40 = true;
         
         if(MCaloJet.JetPT[i] < 60)                                  continue;

         CentralCaloB60 = true;
         
         if(MCaloJet.JetPT[i] < 80)                                 continue;

         CentralCaloB80 = true;
      }
      for(int i = 0; i < MPFJet.JetCount; i++)
      {
         if(MPFJet.JetEta[i] < -2.1 || MPFJet.JetEta[i] > 2.1)     continue;
         if(abs(MPFJet.RefPartonFlavorForB[i]) != 5)               continue;
         if(MPFJet.JetPT[i] < 40)                                  continue;

         CentralPFB40 = true;
         
         if(MPFJet.JetPT[i] < 60)                                  continue;

         CentralPFB60 = true;
         
         if(MPFJet.JetPT[i] < 80)                                 continue;

         CentralPFB80 = true;
      }

      for(int i = 0; i < 7; i++)
      {
         if(i == 1 && CentralCaloB40 == false)    continue;
         if(i == 2 && CentralCaloB60 == false)    continue;
         if(i == 3 && CentralCaloB80 == false)   continue;
         if(i == 4 && CentralPFB40 == false)      continue;
         if(i == 5 && CentralPFB60 == false)      continue;
         if(i == 6 && CentralPFB80 == false)     continue;

         HYield.Fill(0.0, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet40_Eta2p1_v1") == 1)
            HYield.Fill(1, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet60_Eta2p1_v1") == 1)
            HYield.Fill(2, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloJet80_Eta2p1_v1") == 1)
            HYield.Fill(3, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet40_Eta2p1_v1") == 1)
            HYield.Fill(4, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet60_Eta2p1_v1") == 1)
            HYield.Fill(5, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta2p1_v1") == 1)
            HYield.Fill(6, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSV40_Eta2p1_v1") == 1)
            HYield.Fill(7, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSV60_Eta2p1_v1") == 1)
            HYield.Fill(8, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4CaloBJetCSV80_Eta2p1_v1") == 1)
            HYield.Fill(9, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV40_Eta2p1_v1") == 1)
            HYield.Fill(10, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV60_Eta2p1_v1") == 1)
            HYield.Fill(11, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV80_Eta2p1_v1") == 1)
            HYield.Fill(12, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV40_CommonTracking_Eta2p1_v1") == 1)
            HYield.Fill(13, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV60_CommonTracking_Eta2p1_v1") == 1)
            HYield.Fill(14, i);
         if(MTrigger.CheckTrigger("HLT_PAAK4PFBJetCSV80_CommonTracking_Eta2p1_v1") == 1)
            HYield.Fill(15, i);
      }
   }

   HYield.Write();

   OutputFile.Close();

   HLTFile.Close();
   ForestFile.Close();

   return 0;
}








