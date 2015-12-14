#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

#include "TChain.h"
#include "TH1D.h"
#include "TFile.h"

#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"
#include "JetCorrectionUncertainty.h"

int main();
void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min = 0.25);

int main()
{
   CheckSampleEfficiency("Samples/T2bb_All.root", 1, 0.25);

   return 0;
}

void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min)
{
   JetCorrectionUncertainty CaloJetUncertainty("TextFiles/GR_R_41_V0::All_AK5Calo_Uncertainty.txt");

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(InputFile.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("PU.root");

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

   map<pair<int, int>, double> AllWeight;
   map<pair<int, int>, double> PassedWeight;
   map<pair<int, int>, double> PassedWeightUp;
   map<pair<int, int>, double> PassedWeightDown;
   
   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      pair<int, int> Model((int)(M.m0 + 0.0001), (int)(M.m12 + 0.0001));
      if(AllWeight.find(Model) == AllWeight.end())
      {
         AllWeight.insert(pair<pair<int, int>, double>(Model, 0));
         PassedWeight.insert(pair<pair<int, int>, double>(Model, 0));
         PassedWeightUp.insert(pair<pair<int, int>, double>(Model, 0));
         PassedWeightDown.insert(pair<pair<int, int>, double>(Model, 0));
      }

      double WPU = M.GetCurrentWeight();

      AllWeight[Model] = AllWeight[Model] + WPU;

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

      if(M.GoodElectronCount >= 1)
         continue;
      if(M.GoodMuonCount >= 1)
         continue;

      if(CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2New >= R2Min && MRNew >= 400)
         PassedWeight[Model] = PassedWeight[Model] + WPU;
      if(CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2NewUp >= R2Min && MRNewUp >= 400)
         PassedWeightUp[Model] = PassedWeightUp[Model] + WPU;
      if(CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2NewDown >= R2Min && MRNewDown >= 400)
         PassedWeightDown[Model] = PassedWeightDown[Model] + WPU;
   }

   cout << "Summary for input file \"" << InputFile << "\" with R2 cut " << R2Min << endl;
   cout << endl;

   for(map<pair<int, int>, double>::iterator iter = AllWeight.begin(); iter != AllWeight.end(); iter++)
   {
      pair<int, int> Model = iter->first;

      cout << "Model: " << Model.first << " " << Model.second << endl;

      cout << "Efficiencies (MR > 400):" << endl;
      cout << "   Nominal " << PassedWeight[Model] / AllWeight[Model] << endl;
      cout << "   Up      " << PassedWeightUp[Model] / AllWeight[Model] << endl;
      cout << "   Down    " << PassedWeightDown[Model] / AllWeight[Model] << endl;
      cout << "   JES Relative " << (PassedWeightUp[Model] - PassedWeightDown[Model]) / 2 / PassedWeight[Model] << endl;
      cout << "   11.54%  " << PassedWeight[Model] / AllWeight[Model] * 0.1154 << endl;
      cout << "   Total   "
         << sqrt((PassedWeightUp[Model] - PassedWeightDown[Model]) * (PassedWeightUp[Model] - PassedWeightDown[Model]) / 4
         + 0.1154 * 0.1154 * PassedWeight[Model] * PassedWeight[Model]) / AllWeight[Model] << endl;
      cout << endl;
   }
}




