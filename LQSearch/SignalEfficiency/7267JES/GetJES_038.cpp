#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include "TChain.h"
#include "TH1D.h"
#include "TFile.h"

#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"
#include "JetCorrectionUncertainty.h"

int main();
void CheckSampleEfficiency(string InputFile, double ExpectedYield);

int main()
{
   CheckSampleEfficiency("Samples/LQ200.root", 11.9 * 1000);
   CheckSampleEfficiency("Samples/LQ250.root", 3.47 * 1000);
   CheckSampleEfficiency("Samples/LQ350.root", 0.477 * 1000);
   CheckSampleEfficiency("Samples/LQ450.root", 0.0949 * 1000);
   CheckSampleEfficiency("Samples/LQ550.root", 0.0236 * 1000);

   return 0;
}

void CheckSampleEfficiency(string InputFile, double ExpectedYield)
{
   JetCorrectionUncertainty CaloJetUncertainty("TextFiles/GR_R_41_V0::All_AK5Calo_Uncertainty.txt");

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(InputFile.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   // M.InitializeWeight("OldSamples/BookKeeping/7174PUTriggersAdded_ElectronHadRun2011Av4.PU.root");
   M.InitializeWeight("Samples/BookKeeping/7222ReRun_HTRun2011Av4.PU.root");

   Tree.SetBranchStatus("PFJet*", false);
   Tree.SetBranchStatus("CaloJetCSVTag", false);
   Tree.SetBranchStatus("CaloJetCSVMTag", false);
   Tree.SetBranchStatus("CaloJetTCHPTag", false);

   double TotalWeight = 0;
   TFile InputF(InputFile.c_str());
   TH1D *H = (TH1D *)InputF.Get("HProcessedEventsPU");
   for(int i = 1; i <= H->GetNbinsX(); i++)
      TotalWeight = TotalWeight + M.GetWeight(i - 1) * H->GetBinContent(i);
   InputF.Close();

   double PassedJet60Weight = 0;
   double PassedBTagWeight = 0;
   double PassedElectronVetoWeight = 0;
   double PassedLeptonVetoWeight = 0;
   double PassedWeight1 = 0;
   double PassedWeight2 = 0;
   double PassedWeight3 = 0;
   double PassedWeight4 = 0;
   
   double PassedWeight = 0;
   double PassedWeightUp = 0;
   double PassedWeightDown = 0;
   
   double PassedWeightMR450 = 0;
   double PassedWeightMR500 = 0;
   double PassedWeightMR550 = 0;
   double PassedWeightMR600 = 0;
   double PassedWeightMR650 = 0;
   double PassedWeightMR700 = 0;
   double PassedWeightMR750 = 0;
   double PassedWeightMR800 = 0;
   
   double PassedWeightMR450Up = 0;
   double PassedWeightMR500Up = 0;
   double PassedWeightMR550Up = 0;
   double PassedWeightMR600Up = 0;
   double PassedWeightMR650Up = 0;
   double PassedWeightMR700Up = 0;
   double PassedWeightMR750Up = 0;
   double PassedWeightMR800Up = 0;

   double PassedWeightMR450Down = 0;
   double PassedWeightMR500Down = 0;
   double PassedWeightMR550Down = 0;
   double PassedWeightMR600Down = 0;
   double PassedWeightMR650Down = 0;
   double PassedWeightMR700Down = 0;
   double PassedWeightMR750Down = 0;
   double PassedWeightMR800Down = 0;

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      double WPU = M.GetCurrentWeight();

      double JetUncertainty[100] = {0};
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         CaloJetUncertainty.setJetEta(M.CaloJetEta[i]);
         CaloJetUncertainty.setJetPt(M.CaloJetPT[i]);
         JetUncertainty[i] = M.CaloJetPT[i] * CaloJetUncertainty.getUncertainty(true);
      }

      int CaloJetCount60 = 0;
      int CaloJetCount60Up = 0;
      int CaloJetCount60Down = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] <= -3 || M.CaloJetEta[i] >= 3)
            continue;

         if(M.CaloJetPT[i] > 60)                       CaloJetCount60 = CaloJetCount60 + 1;
         if(M.CaloJetPT[i] + JetUncertainty[i] > 60)   CaloJetCount60Up = CaloJetCount60Up + 1;
         if(M.CaloJetPT[i] - JetUncertainty[i] > 60)   CaloJetCount60Down = CaloJetCount60Down + 1;
      }

      int JetPassBTagLoose = 0;
      int JetPassBTagLooseUp = 0;
      int JetPassBTagLooseDown = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] <= -3 || M.CaloJetEta[i] >= 3)
            continue;
         if(M.CaloJetTCHETag[i] <= 1.7)
            continue;

         if(M.CaloJetPT[i] > 80)                       JetPassBTagLoose = JetPassBTagLoose + 1;
         if(M.CaloJetPT[i] + JetUncertainty[i] > 80)   JetPassBTagLooseUp = JetPassBTagLooseUp + 1;
         if(M.CaloJetPT[i] - JetUncertainty[i] > 80)   JetPassBTagLooseDown = JetPassBTagLooseDown + 1;
      }

      vector<FourVector> CaloJets;
      vector<FourVector> CaloJetsUp;
      vector<FourVector> CaloJetsDown;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         if(M.CaloJetPT[i] > 40)                       CaloJets.push_back(NewJet);
         if(M.CaloJetPT[i] + JetUncertainty[i] > 40)   CaloJetsUp.push_back(NewJet);
         if(M.CaloJetPT[i] - JetUncertainty[i] > 40)   CaloJetsDown.push_back(NewJet);
      }

      vector<FourVector> Hemispheres;
      vector<FourVector> HemispheresUp;
      vector<FourVector> HemispheresDown;

      if(CaloJets.size() >= 2)       Hemispheres = SplitIntoGroups(CaloJets, true);
      if(CaloJetsUp.size() >= 2)     HemispheresUp = SplitIntoGroups(CaloJetsUp, true);
      if(CaloJetsDown.size() >= 2)   HemispheresDown = SplitIntoGroups(CaloJetsDown, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);   // what do you do here?
      PFMET[0] = PFMET.GetPT();

      double MRNew = 0;
      double RNew = 0;
      double MRNewUp = 0;
      double RNewUp = 0;
      double MRNewDown = 0;
      double RNewDown = 0;

      if(Hemispheres.size() == 2)
      {
         MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
         RNew = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      }
      if(HemispheresUp.size() == 2)
      {
         MRNewUp = Get2011MR(HemispheresUp[0], HemispheresUp[1]);
         RNewUp = Get2011R(HemispheresUp[0], HemispheresUp[1], PFMET);
      }
      if(HemispheresDown.size() == 2)
      {
         MRNewDown = Get2011MR(HemispheresDown[0], HemispheresDown[1]);
         RNewDown = Get2011R(HemispheresDown[0], HemispheresDown[1], PFMET);
      }

      double R2New = RNew * RNew;
      double R2NewUp = RNewUp * RNewUp;
      double R2NewDown = RNewDown * RNewDown;

      if(CaloJetCount60 >= 2)
         PassedJet60Weight = PassedJet60Weight + WPU;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2)
         PassedBTagWeight = PassedBTagWeight + WPU;

      if(M.GoodElectronCount >= 1)
         continue;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2)
         PassedElectronVetoWeight = PassedElectronVetoWeight + WPU;
      if(M.GoodMuonCount >= 1)
         continue;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2)
         PassedLeptonVetoWeight = PassedLeptonVetoWeight + WPU;

      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.00 && MRNew >= 200)
         PassedWeight1 = PassedWeight1 + WPU;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.04 && MRNew >= 200)
         PassedWeight2 = PassedWeight2 + WPU;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.04 && MRNew >= 400)
         PassedWeight3 = PassedWeight3 + WPU;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.25 && MRNew >= 400)
         PassedWeight4 = PassedWeight4 + WPU;

      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.38 && MRNew >= 400)
         PassedWeight = PassedWeight + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= 0.38 && MRNewUp >= 400)
         PassedWeightUp = PassedWeightUp + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= 0.38 && MRNewDown >= 400)
         PassedWeightDown = PassedWeightDown + WPU;
      
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.38 && MRNew >= 450)
         PassedWeightMR450 = PassedWeightMR450 + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= 0.38 && MRNewUp >= 450)
         PassedWeightMR450Up = PassedWeightMR450Up + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= 0.38 && MRNewDown >= 450)
         PassedWeightMR450Down = PassedWeightMR450Down + WPU;
      
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.38 && MRNew >= 500)
         PassedWeightMR500 = PassedWeightMR500 + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= 0.38 && MRNewUp >= 500)
         PassedWeightMR500Up = PassedWeightMR500Up + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= 0.38 && MRNewDown >= 500)
         PassedWeightMR500Down = PassedWeightMR500Down + WPU;
      
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.38 && MRNew >= 550)
         PassedWeightMR550 = PassedWeightMR550 + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= 0.38 && MRNewUp >= 550)
         PassedWeightMR550Up = PassedWeightMR550Up + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= 0.38 && MRNewDown >= 550)
         PassedWeightMR550Down = PassedWeightMR550Down + WPU;
      
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.38 && MRNew >= 600)
         PassedWeightMR600 = PassedWeightMR600 + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= 0.38 && MRNewUp >= 600)
         PassedWeightMR600Up = PassedWeightMR600Up + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= 0.38 && MRNewDown >= 600)
         PassedWeightMR600Down = PassedWeightMR600Down + WPU;
      
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.38 && MRNew >= 650)
         PassedWeightMR650 = PassedWeightMR650 + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= 0.38 && MRNewUp >= 650)
         PassedWeightMR650Up = PassedWeightMR650Up + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= 0.38 && MRNewDown >= 650)
         PassedWeightMR650Down = PassedWeightMR650Down + WPU;
      
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.38 && MRNew >= 700)
         PassedWeightMR700 = PassedWeightMR700 + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= 0.38 && MRNewUp >= 700)
         PassedWeightMR700Up = PassedWeightMR700Up + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= 0.38 && MRNewDown >= 700)
         PassedWeightMR700Down = PassedWeightMR700Down + WPU;
      
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.38 && MRNew >= 750)
         PassedWeightMR750 = PassedWeightMR750 + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= 0.38 && MRNewUp >= 750)
         PassedWeightMR750Up = PassedWeightMR750Up + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= 0.38 && MRNewDown >= 750)
         PassedWeightMR750Down = PassedWeightMR750Down + WPU;
      
      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= 0.38 && MRNew >= 800)
         PassedWeightMR800 = PassedWeightMR800 + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= 0.38 && MRNewUp >= 800)
         PassedWeightMR800Up = PassedWeightMR800Up + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= 0.38 && MRNewDown >= 800)
         PassedWeightMR800Down = PassedWeightMR800Down + WPU;
   }

   cout << "Summary for input file \"" << InputFile << "\"" << endl;
   cout << endl;

   cout << "Total weight: " << TotalWeight << endl;
   cout << "Weights: " << PassedWeight << " " << PassedWeightUp << " " << PassedWeightDown << endl;
   cout << endl;

   cout << "Total event: " << TotalWeight / TotalWeight * ExpectedYield << endl;
   cout << "Counts: " << PassedWeight / TotalWeight * ExpectedYield
      << " " << PassedWeightUp / TotalWeight * ExpectedYield
      << " " << PassedWeightDown / TotalWeight * ExpectedYield << endl;
   cout << endl;

   cout << "Peek at the cut flow:" << endl;
   cout << "   Pass Jet PT 60x2 " << PassedJet60Weight / TotalWeight * ExpectedYield << endl;
   cout << "   B tagging        " << PassedBTagWeight / TotalWeight * ExpectedYield << endl;
   cout << "   Electron veto    " << PassedElectronVetoWeight / TotalWeight * ExpectedYield << endl;
   cout << "   Muon veto        " << PassedLeptonVetoWeight / TotalWeight * ExpectedYield << endl;
   cout << "   MR > 200         " << PassedWeight1 / TotalWeight * ExpectedYield << endl;
   cout << "   R > 0.2          " << PassedWeight2 / TotalWeight * ExpectedYield << endl;
   cout << "   MR > 400         " << PassedWeight3 / TotalWeight * ExpectedYield << endl;
   cout << "   R > 0.5          " << PassedWeight4 / TotalWeight * ExpectedYield << endl;
   cout << endl;

   cout << "Efficiencies (MR > 400):" << endl;
   cout << "   Nominal " << PassedWeight / TotalWeight << endl;
   cout << "   Up      " << PassedWeightUp / TotalWeight << endl;
   cout << "   Down    " << PassedWeightDown / TotalWeight << endl;
   cout << "Efficiencies (MR > 450):" << endl;
   cout << "   Nominal " << PassedWeightMR450 / TotalWeight << endl;
   cout << "   Up      " << PassedWeightMR450Up / TotalWeight << endl;
   cout << "   Down    " << PassedWeightMR450Down / TotalWeight << endl;
   cout << "Efficiencies (MR > 500):" << endl;
   cout << "   Nominal " << PassedWeightMR500 / TotalWeight << endl;
   cout << "   Up      " << PassedWeightMR500Up / TotalWeight << endl;
   cout << "   Down    " << PassedWeightMR500Down / TotalWeight << endl;
   cout << "Efficiencies (MR > 550):" << endl;
   cout << "   Nominal " << PassedWeightMR550 / TotalWeight << endl;
   cout << "   Up      " << PassedWeightMR550Up / TotalWeight << endl;
   cout << "   Down    " << PassedWeightMR550Down / TotalWeight << endl;
   cout << "Efficiencies (MR > 600):" << endl;
   cout << "   Nominal " << PassedWeightMR600 / TotalWeight << endl;
   cout << "   Up      " << PassedWeightMR600Up / TotalWeight << endl;
   cout << "   Down    " << PassedWeightMR600Down / TotalWeight << endl;
   cout << "Efficiencies (MR > 650):" << endl;
   cout << "   Nominal " << PassedWeightMR650 / TotalWeight << endl;
   cout << "   Up      " << PassedWeightMR650Up / TotalWeight << endl;
   cout << "   Down    " << PassedWeightMR650Down / TotalWeight << endl;
   cout << "Efficiencies (MR > 700):" << endl;
   cout << "   Nominal " << PassedWeightMR700 / TotalWeight << endl;
   cout << "   Up      " << PassedWeightMR700Up / TotalWeight << endl;
   cout << "   Down    " << PassedWeightMR700Down / TotalWeight << endl;
   cout << "Efficiencies (MR > 750):" << endl;
   cout << "   Nominal " << PassedWeightMR750 / TotalWeight << endl;
   cout << "   Up      " << PassedWeightMR750Up / TotalWeight << endl;
   cout << "   Down    " << PassedWeightMR750Down / TotalWeight << endl;
   cout << "Efficiencies (MR > 800):" << endl;
   cout << "   Nominal " << PassedWeightMR800 / TotalWeight << endl;
   cout << "   Up      " << PassedWeightMR800Up / TotalWeight << endl;
   cout << "   Down    " << PassedWeightMR800Down / TotalWeight << endl;
   cout << endl;
}




