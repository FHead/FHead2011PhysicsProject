#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Messenger.h"
#include "EventMatching.h"

#define ChrisTree 0
#define YiTree 1

class Trigger;
int main(int argc, char *argv[]);
void EvaluateRate(string ChrisFile, string YiFile, vector<Trigger> TriggerList);

class Trigger
{
public:
   string TriggerString;
   int WhichTree;
   int Prescale;
public:
   Trigger() : TriggerString(""), WhichTree(0) {}
   Trigger(string trigger, int whichtree, int prescale = 1)
      : TriggerString(trigger), WhichTree(whichtree), Prescale(prescale) {}
};

int main(int argc, char *argv[])
{
   vector<Trigger> LowerJetPD, HigherJetPD, LowerEGPD, HigherEGPD;

   LowerJetPD.push_back(Trigger("HLT_PAAK4CaloJet40_Eta5p1_v2", ChrisTree, 10));
   LowerJetPD.push_back(Trigger("HLT_PAAK4CaloJet60_Eta5p1_v2", ChrisTree, 2));
   HigherJetPD.push_back(Trigger("HLT_PAAK4CaloJet80_Eta5p1_v2", ChrisTree, 1));
   LowerJetPD.push_back(Trigger("HLT_PAAK4CaloJet40_Eta1p9toEta5p1_v2", ChrisTree, 6));
   HigherJetPD.push_back(Trigger("HLT_PAAK4CaloJet60_Eta1p9toEta5p1_v2", ChrisTree, 1));
   LowerJetPD.push_back(Trigger("HLT_PAAK4CaloJet40_Eta2p9toEta5p1_v2", ChrisTree, 3));
   LowerJetPD.push_back(Trigger("HLT_PAAK4PFJet40_Eta5p1_v2", ChrisTree, 10));
   LowerJetPD.push_back(Trigger("HLT_PAAK4PFJet60_Eta5p1_v2", ChrisTree, 2));
   HigherJetPD.push_back(Trigger("HLT_PAAK4PFJet80_Eta5p1_v2", ChrisTree, 1));
   LowerJetPD.push_back(Trigger("HLT_PAAK4PFJet40_Eta1p9toEta5p1_v2", ChrisTree, 6));
   HigherJetPD.push_back(Trigger("HLT_PAAK4PFJet60_Eta1p9toEta5p1_v2", ChrisTree, 1));
   LowerJetPD.push_back(Trigger("HLT_PAAK4PFJet40_Eta2p9toEta5p1_v2", ChrisTree, 3));
   LowerJetPD.push_back(Trigger("HLT_PADiAK4CaloJetAve40_Eta5p1_v2", ChrisTree, 10));
   HigherJetPD.push_back(Trigger("HLT_PADiAK4CaloJetAve60_Eta5p1_v2", ChrisTree, 1));
   HigherJetPD.push_back(Trigger("HLT_PADiAK4CaloJetAve80_Eta5p1_v2", ChrisTree, 1));
   LowerJetPD.push_back(Trigger("HLT_PADiAK4PFJetAve40_Eta5p1_v2", ChrisTree, 10));
   HigherJetPD.push_back(Trigger("HLT_PADiAK4PFJetAve60_Eta5p1_v2", ChrisTree, 1));
   HigherJetPD.push_back(Trigger("HLT_PADiAK4PFJetAve80_Eta5p1_v2", ChrisTree, 1));
   LowerJetPD.push_back(Trigger("HLT_PAAK4CaloBJetCSV40_Eta2p1_v1", YiTree, 10));
   HigherJetPD.push_back(Trigger("HLT_PAAK4CaloBJetCSV60_Eta2p1_v1", YiTree, 1));
   HigherJetPD.push_back(Trigger("HLT_PAAK4CaloBJetCSV80_Eta2p1_v1", YiTree, 1));
   LowerJetPD.push_back(Trigger("HLT_PAAK4PFBJetCSV40_Eta2p1_v1", YiTree, 10));
   HigherJetPD.push_back(Trigger("HLT_PAAK4PFBJetCSV60_Eta2p1_v1", YiTree, 1));
   HigherJetPD.push_back(Trigger("HLT_PAAK4PFBJetCSV80_Eta2p1_v1", YiTree, 1));
   LowerEGPD.push_back(Trigger("HLT_PASinglePhoton10_Eta3p1_v2", ChrisTree, 30));
   LowerEGPD.push_back(Trigger("HLT_PASinglePhoton15_Eta3p1_v2", ChrisTree, 30));
   HigherEGPD.push_back(Trigger("HLT_PASinglePhoton20_Eta3p1_v2", ChrisTree, 1));
   HigherEGPD.push_back(Trigger("HLT_PASinglePhoton30_Eta3p1_v2", ChrisTree, 1));
   HigherEGPD.push_back(Trigger("HLT_PADoublePhoton15_Eta3p1_Mass50_1000_v2", ChrisTree, 1));
   // LowerJetPD.push_back(Trigger("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu3_v2", ChrisTree, 10));
   // LowerJetPD.push_back(Trigger("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu5_v2", ChrisTree, 1));
   // LowerJetPD.push_back(Trigger("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu3_v2", ChrisTree, 10));
   // LowerJetPD.push_back(Trigger("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu5_v2", ChrisTree, 1));
   // LowerJetPD.push_back(Trigger("HLT_PASinglePhoton10_Eta3p1_PAL3Mu3_v2", ChrisTree, 1));
   // LowerJetPD.push_back(Trigger("HLT_PASinglePhoton10_Eta3p1_PAL3Mu5_v2", ChrisTree, 1));
   // LowerJetPD.push_back(Trigger("HLT_PASinglePhoton15_Eta3p1_PAL3Mu3_v2", ChrisTree, 1));
   // LowerJetPD.push_back(Trigger("HLT_PASinglePhoton15_Eta3p1_PAL3Mu5_v2", ChrisTree, 1));
   // LowerJetPD.push_back(Trigger("HLT_PASinglePhoton20_Eta3p1_PAL3Mu3_v2", ChrisTree, 1));
   // LowerJetPD.push_back(Trigger("HLT_PASinglePhoton20_Eta3p1_PAL3Mu5_v2", ChrisTree, 1));

   string ChrisFile = "openHLT_ChrisV14.root";
   string YiFile = "openHLT_V28.root";

   EvaluateRate(ChrisFile, YiFile, LowerJetPD);
   EvaluateRate(ChrisFile, YiFile, HigherJetPD);
   EvaluateRate(ChrisFile, YiFile, LowerEGPD);
   EvaluateRate(ChrisFile, YiFile, HigherEGPD);

   return 0;
}

void EvaluateRate(string ChrisFile, string YiFile, vector<Trigger> TriggerList)
{
   TFile FChris(ChrisFile.c_str());
   TFile FYi(YiFile.c_str());

   TriggerTreeMessenger MChris(FChris, "hltbitanalysis/HltTree");
   TriggerTreeMessenger MYi(FYi, "hltbitanalysis/HltTree");

   map<EventCoordinate, int> Location = BuildMap(MYi, true);
   Location = BuildMap(MChris, Location);

   int TotalCount = 0;
   vector<int> Count(TriggerList.size());
   for(int i = 0; i < (int)TriggerList.size(); i++)
      Count[i] = 0;
   int PDCount = 0;

   int EntryCount = MYi.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if((iE + 1) % 1000000 == 0)
         cout << "Processing " << iE + 1 << " / " << EntryCount << endl;

      MYi.GetEntry(iE);

      if(Location.find(MYi) == Location.end())
         continue;
      if(Location[MYi] < 0)
         continue;
      int IE = Location[MYi];
      
      TotalCount = TotalCount + 1;

      MChris.GetEntry(IE);

      bool AnyPass = false;

      for(int i = 0; i < (int)TriggerList.size(); i++)
      {
         bool Pass = false;

         if(TriggerList[i].WhichTree == ChrisTree)
         {
            if(MChris.CheckTrigger(TriggerList[i].TriggerString) == 1)
               Pass = true;
         }
         else
         {
            if(MYi.CheckTrigger(TriggerList[i].TriggerString) == 1)
               Pass = true;
         }

         if(Pass == true)
         {
            Count[i] = Count[i] + 1;

            // if(TriggerList[i].Prescale <= 1 || Count[i] % TriggerList[i].Prescale == 0)
            //    AnyPass = true;
            if(TriggerList[i].Prescale <= 1 || iE % TriggerList[i].Prescale == 0)
               AnyPass = true;
         }
      }

      if(AnyPass == true)
         PDCount = PDCount + 1;
   }

   cout << "PD Summary" << endl;
   cout << "   Total Event = " << TotalCount << endl;
   cout << "   Trigger List" << endl;
   for(int i = 0; i < (int)TriggerList.size(); i++)
      cout << "      \"" << TriggerList[i].TriggerString << "\": " << Count[i] << endl;
   cout << "   PD Event = " << PDCount << endl;
   cout << "   PD Rate (1MHz) = " << (double)PDCount / TotalCount * 1000000 << endl;
   cout << endl;

   FYi.Close();
   FChris.Close();
}





