#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

int main()
{
   TFile File("openHLT.root");

   TTree *Tree = (TTree *)File.Get("hltbitanalysis/HltTree");

   vector<string> Triggers(55);
   Triggers[0]  = "HLT_PAAK4CaloJet40_Eta5p1_v2";
   Triggers[1]  = "HLT_PAAK4CaloJet60_Eta5p1_v2";
   Triggers[2]  = "HLT_PAAK4CaloJet80_Eta5p1_v2";
   Triggers[3]  = "HLT_PAAK4CaloJet100_Eta5p1_v2";
   Triggers[4]  = "HLT_PAAK4CaloJet40_Eta1p9toEta5p1_v2";
   Triggers[5]  = "HLT_PAAK4CaloJet60_Eta1p9toEta5p1_v2";
   Triggers[6]  = "HLT_PAAK4CaloJet40_Eta2p9toEta5p1_v2";
   Triggers[7]  = "HLT_PAAK4CaloJet30_Eta5p1_PAL3Mu3_v2";
   Triggers[8]  = "HLT_PAAK4CaloJet30_Eta5p1_PAL3Mu5_v2";
   Triggers[9]  = "HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu3_v2";
   Triggers[10] = "HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu5_v2";
   Triggers[11] = "HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu3_v2";
   Triggers[12] = "HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu5_v2";
   Triggers[13] = "HLT_PAAK4PFJet40_Eta5p1_v2";
   Triggers[14] = "HLT_PAAK4PFJet60_Eta5p1_v2";
   Triggers[15] = "HLT_PAAK4PFJet80_Eta5p1_v2";
   Triggers[16] = "HLT_PAAK4PFJet100_Eta5p1_v2";
   Triggers[17] = "HLT_PAAK4PFJet40_Eta1p9toEta5p1_v2";
   Triggers[18] = "HLT_PAAK4PFJet60_Eta1p9toEta5p1_v2";
   Triggers[19] = "HLT_PAAK4PFJet40_Eta2p9toEta5p1_v2";
   Triggers[20] = "HLT_PADiAK4CaloJetAve40_Eta5p1_v2";
   Triggers[21] = "HLT_PADiAK4CaloJetAve60_Eta5p1_v2";
   Triggers[22] = "HLT_PADiAK4CaloJetAve80_Eta5p1_v2";
   Triggers[23] = "HLT_PADiAK4PFJetAve40_Eta5p1_v2";
   Triggers[24] = "HLT_PADiAK4PFJetAve60_Eta5p1_v2";
   Triggers[25] = "HLT_PADiAK4PFJetAve80_Eta5p1_v2";
   Triggers[26] = "HLT_PASinglePhoton10_Eta3p1_v2";
   Triggers[27] = "HLT_PASinglePhoton15_Eta3p1_v2";
   Triggers[28] = "HLT_PASinglePhoton20_Eta3p1_v2";
   Triggers[29] = "HLT_PASinglePhoton30_Eta3p1_v2";
   Triggers[30] = "HLT_PASinglePhoton40_Eta3p1_v2";
   Triggers[31] = "HLT_PASingleIsoPhoton20_Eta3p1_v2";
   Triggers[32] = "HLT_PADoublePhoton15_Eta3p1_Mass50_1000_v2";
   Triggers[33] = "HLT_PASinglePhoton10_Eta3p1_PAL3Mu3_v2";
   Triggers[34] = "HLT_PASinglePhoton10_Eta3p1_PAL3Mu5_v2";
   Triggers[35] = "HLT_PASinglePhoton15_Eta3p1_PAL3Mu3_v2";
   Triggers[36] = "HLT_PASinglePhoton15_Eta3p1_PAL3Mu5_v2";
   Triggers[37] = "HLT_PASinglePhoton20_Eta3p1_PAL3Mu3_v2";
   Triggers[38] = "HLT_PASinglePhoton20_Eta3p1_PAL3Mu5_v2";
   Triggers[39] = "HLT_PAPhoton10_Eta3p1_PPStyle_v6";
   Triggers[40] = "HLT_PAPhoton15_Eta3p1_PPStyle_v6";
   Triggers[41] = "HLT_PAPhoton20_Eta3p1_PPStyle_v6";
   Triggers[42] = "HLT_PAPhoton30_Eta3p1_PPStyle_v6";
   Triggers[43] = "HLT_PAPhoton40_Eta3p1_PPStyle_v6";
   Triggers[44] = "HLT_PAIsoPhoton20_Eta3p1_PPStyle_v6";
   Triggers[45] = "HLT_PAAK4CaloBJetCSV40_Eta2p1_v1";
   Triggers[46] = "HLT_PAAK4CaloBJetCSV60_Eta2p1_v1";
   Triggers[47] = "HLT_PAAK4CaloBJetCSV80_Eta2p1_v1";
   Triggers[48] = "HLT_PAAK4PFBJetCSV40_Eta2p1_v1";
   Triggers[49] = "HLT_PAAK4PFBJetCSV60_Eta2p1_v1";
   Triggers[50] = "HLT_PAAK4PFBJetCSV80_Eta2p1_v1";
   Triggers[51] = "HLT_PAAK4PFBJetCSV40_CommonTracking_Eta2p1_v1";
   Triggers[52] = "HLT_PAAK4PFBJetCSV60_CommonTracking_Eta2p1_v1";
   Triggers[53] = "HLT_PAAK4PFBJetCSV80_CommonTracking_Eta2p1_v1";
   Triggers[54] = "HLT_Ele20_WPLoose_Gsf_v6";

   vector<int> Bits(55);
   for(int i = 0; i < 55; i++)
      Tree->SetBranchAddress(Triggers[i].c_str(), &Bits[i]);

   int Run;
   unsigned long long Event;
   int Lumi;

   Tree->SetBranchAddress("Run", &Run);
   Tree->SetBranchAddress("Event", &Event);
   Tree->SetBranchAddress("LumiBlock", &Lumi);

   vector<ofstream *> Out;
   vector<int> Count(55);
   for(int i = 0; i < 55; i++)
   {
      Out.push_back(new ofstream(Triggers[i] + ".txt"));
      Count[i] = 0;
   }

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if((iE + 1) % 10000 == 0)
         cout << "Processing entry " << iE + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iE);

      for(int i = 0; i < 55; i++)
      {
         if(Out[i] == NULL)
            continue;

         if(Bits[i] > 0 && Count[i] < 1000)
         {
            *Out[i] << Run << ":" << Lumi << ":" << Event << ",";
            Count[i] = Count[i] + 1;
         }
      }
   }

   for(int i = 0; i < 55; i++)
   {
      if(Out[i] != NULL)
      {
         Out[i]->close();
         delete Out[i];
      }
   }

   File.Close();

   return 0;
}



