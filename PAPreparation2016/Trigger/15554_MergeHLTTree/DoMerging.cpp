#include <iostream>
using namespace std;

#include "TTree.h"
#include "TDirectory.h"
#include "TFile.h"

#include "Messenger.h"
#include "EventMatching.h"

#define NoTree -1
#define ChrisTree 0
#define YiTree 1

class Trigger;
int main(int argc, char *argv[]);

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
   string ChrisFile = "openHLT_ChrisV14.root";
   string YiFile = "openHLT_V28.root";
   string NewFile = "openHLT_Merged.root";

   vector<Trigger> Triggers;

   Triggers.push_back(Trigger("L1_SingleJet20_BptxAND", NoTree, 1));
   Triggers.push_back(Trigger("L1_SingleJet40_BptxAND", NoTree, 1));
   Triggers.push_back(Trigger("L1_SingleJet60_BptxAND", NoTree, 1));
   Triggers.push_back(Trigger("L1_SingleEG2_BptxAND", NoTree, 1));
   Triggers.push_back(Trigger("L1_SingleEG5_BptxAND", NoTree, 1));
   Triggers.push_back(Trigger("L1_SingleEG18_BptxAND", NoTree, 1));
   Triggers.push_back(Trigger("L1_SingleMu3_BptxAND", NoTree, 1));
   Triggers.push_back(Trigger("L1_SingleMu5_BptxAND", NoTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet40_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet60_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet80_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet40_Eta1p9toEta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet60_Eta1p9toEta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet40_Eta2p9toEta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4PFJet40_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4PFJet60_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4PFJet80_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4PFJet40_Eta1p9toEta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4PFJet60_Eta1p9toEta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4PFJet40_Eta2p9toEta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PADiAK4CaloJetAve40_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PADiAK4CaloJetAve60_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PADiAK4CaloJetAve80_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PADiAK4PFJetAve40_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PADiAK4PFJetAve60_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PADiAK4PFJetAve80_Eta5p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloBJetCSV40_Eta2p1_v1", YiTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloBJetCSV60_Eta2p1_v1", YiTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloBJetCSV80_Eta2p1_v1", YiTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4PFBJetCSV40_Eta2p1_v1", YiTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4PFBJetCSV60_Eta2p1_v1", YiTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4PFBJetCSV80_Eta2p1_v1", YiTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton10_Eta3p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton15_Eta3p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton20_Eta3p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton30_Eta3p1_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PADoublePhoton15_Eta3p1_Mass50_1000_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu3_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu5_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu3_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu5_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton10_Eta3p1_PAL3Mu3_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton10_Eta3p1_PAL3Mu5_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton15_Eta3p1_PAL3Mu3_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton15_Eta3p1_PAL3Mu5_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton20_Eta3p1_PAL3Mu3_v2", ChrisTree, 1));
   Triggers.push_back(Trigger("HLT_PASinglePhoton20_Eta3p1_PAL3Mu5_v2", ChrisTree, 1));
   
   int N = (int)Triggers.size();

   TFile FChris(ChrisFile.c_str());
   TFile FYi(YiFile.c_str());

   TriggerTreeMessenger MChris(FChris, "hltbitanalysis/HltTree");
   TriggerTreeMessenger MYi(FYi, "hltbitanalysis/HltTree");

   TFile FNew(NewFile.c_str(), "RECREATE");
   TDirectory *Directory = FNew.mkdir("hltbitanalysis");
   Directory->cd();

   TTree *Tree = new TTree("HltTree", "HltTree");

   vector<int> TriggerBits(N);
   for(int i = 0; i < N; i++)
      Tree->Branch(Triggers[i].TriggerString.c_str(), &TriggerBits[i], (Triggers[i].TriggerString + "/I").c_str());

   map<EventCoordinate, int> Location = BuildMap(MYi, true);
   Location = BuildMap(MChris, Location);

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
      
      MChris.GetEntry(IE);

      for(int i = 0; i < N; i++)
      {
         if(Triggers[i].WhichTree == NoTree)
            TriggerBits[i] = 1;
         else if(Triggers[i].WhichTree == YiTree)
            TriggerBits[i] = MYi.CheckTrigger(Triggers[i].TriggerString);
         else
            TriggerBits[i] = MChris.CheckTrigger(Triggers[i].TriggerString);
      }

      Tree->Fill();
   }

   Tree->Write();

   FNew.Close();

   FYi.Close();
   FChris.Close();

   return 0;
}





