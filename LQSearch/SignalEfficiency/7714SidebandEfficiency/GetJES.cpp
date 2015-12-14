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
void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min = 0.20, double R2Max = 0.25);

int main()
{
   CheckSampleEfficiency("Samples/LQ250.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_200.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_210.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_220.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_230.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_240.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_260.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_270.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_280.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_290.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_310.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_320.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_330.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_340.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_350.list.root", 1, 0.20, 0.25);
   // CheckSampleEfficiency("LQSamples/LQToBNutau_400.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_450.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_500.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_550.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_600.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_750.list.root", 1, 0.20, 0.25);
   CheckSampleEfficiency("LQSamples/LQToBNutau_850.list.root", 1, 0.20, 0.25);

   return 0;
}

void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min, double R2Max)
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
      if(CaloJetCount60 >= 2 && JetPassBTagLoose == 1)
         PassedBTagWeight = PassedBTagWeight + WPU;

      if(M.GoodElectronCount >= 1)
         continue;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose == 1)
         PassedElectronVetoWeight = PassedElectronVetoWeight + WPU;
      if(M.GoodMuonCount >= 1)
         continue;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose == 1)
         PassedLeptonVetoWeight = PassedLeptonVetoWeight + WPU;

      if(CaloJetCount60 >= 2 && JetPassBTagLoose == 1 && R2New >= 0.00 && MRNew >= 200)
         PassedWeight1 = PassedWeight1 + WPU;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose == 1 && R2New >= 0.04 && MRNew >= 200)
         PassedWeight2 = PassedWeight2 + WPU;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose == 1 && R2New >= 0.04 && MRNew >= 400)
         PassedWeight3 = PassedWeight3 + WPU;
      if(CaloJetCount60 >= 2 && JetPassBTagLoose == 1 && R2New >= 0.25 && MRNew >= 400)
         PassedWeight4 = PassedWeight4 + WPU;

      if(CaloJetCount60 >= 2 && JetPassBTagLoose == 1 && R2New >= R2Min && MRNew >= 400 && MRNew <= 600 && R2New < R2Max)
         PassedWeight = PassedWeight + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp == 1 && R2NewUp >= R2Min && MRNewUp >= 400 && MRNewUp < 600 && R2NewUp < R2Max)
         PassedWeightUp = PassedWeightUp + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown == 1 && R2NewDown >= R2Min && MRNewDown >= 400 && MRNewDown < 600 && R2NewDown < R2Max)
         PassedWeightDown = PassedWeightDown + WPU;
   }

   cout << "Summary for input file \"" << InputFile << "\" with R2 cut " << R2Min << endl;
   cout << endl;

   cout << "Efficiencies (MR > 400, MR < 600):" << endl;
   cout << "   Nominal " << PassedWeight / TotalWeight << endl;
   cout << "   Up      " << PassedWeightUp / TotalWeight << endl;
   cout << "   Down    " << PassedWeightDown / TotalWeight << endl;
   cout << "   JES Relative " << (PassedWeightUp - PassedWeightDown) / 2 / PassedWeight << endl;
   cout << "   11.54%  " << PassedWeight / TotalWeight * 0.1154 << endl;
   cout << "   Total   "
      << sqrt((PassedWeightUp - PassedWeightDown)  * (PassedWeightUp - PassedWeightDown) / 4
      + 0.1154 * 0.1154 * PassedWeight * PassedWeight) / TotalWeight << endl;
   cout << endl;
}




