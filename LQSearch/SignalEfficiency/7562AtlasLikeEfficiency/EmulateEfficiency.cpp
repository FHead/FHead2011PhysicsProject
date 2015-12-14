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

int main();
void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min = 0.25);

int main()
{
   CheckSampleEfficiency("Samples/T2bb_All.root", 1, 0.25);

   return 0;
}

void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min)
{
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
      }

      double WPU = M.GetCurrentWeight();

      AllWeight[Model] = AllWeight[Model] + WPU;

      vector<FourVector> SoftJets;
      vector<FourVector> Jets;
      int CaloJetCount30 = 0;
      int CaloJetCount50 = 0;
      int CaloJetCount130 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] <= -3 || M.CaloJetEta[i] >= 3)
            continue;

         if(M.CaloJetPT[i] > 30)
            CaloJetCount30 = CaloJetCount30 + 1;
         if(M.CaloJetPT[i] > 50)
            CaloJetCount50 = CaloJetCount50 + 1;
         if(M.CaloJetPT[i] > 130)
            CaloJetCount130 = CaloJetCount130 + 1;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         if(M.CaloJetPT[i] > 50)
            Jets.push_back(NewJet);
         else if(M.CaloJetPT[i] > 30)
            SoftJets.push_back(NewJet);
      }

      int JetPassBTagLoose30 = 0;
      int JetPassBTagLoose50 = 0;
      int JetPassBTagLoose130 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] <= -2.5 || M.CaloJetEta[i] >= 2.5)
            continue;
         if(M.CaloJetTCHETag[i] <= 3.3)
            continue;

         if(M.CaloJetPT[i] > 30)
            JetPassBTagLoose30 = JetPassBTagLoose30 + 1;
         if(M.CaloJetPT[i] > 50)
            JetPassBTagLoose50 = JetPassBTagLoose50 + 1;
         if(M.CaloJetPT[i] > 130)
            JetPassBTagLoose130 = JetPassBTagLoose130 + 1;
      }

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);   // what do you do here?
      PFMET[0] = PFMET.GetPT();

      double MCT = 0;
      if(Jets.size() >= 2)
         MCT = sqrt((Jets[0].GetPT() + Jets[1].GetPT()) * (Jets[0].GetPT() + Jets[1].GetPT())
            - (Jets[0] - Jets[1]).GetPT2());

      bool Pass = true;
      if(CaloJetCount130 == 0)
         Pass = false;
      else if(PFMET.GetPT() < 130)
         Pass = false;
      else if(CaloJetCount50 != 2)
         Pass = false;
      else if(fabs(GetDPhi(Jets[0], PFMET)) < 0.4)
         Pass = false;
      else if(fabs(GetDPhi(Jets[1], PFMET)) < 0.4)
         Pass = false;
      else if(CaloJetCount30 - CaloJetCount50 > 1)
         Pass = false;
      else if(SoftJets.size() > 0 && fabs(GetDPhi(SoftJets[0], PFMET)) < 0.2)
         Pass = false;
      else if(PFMET.GetPT() / (PFMET.GetPT() + Jets[0].GetPT() + Jets[1].GetPT()) < 0.25)
         Pass = false;
      else if(JetPassBTagLoose50 < 2)
         Pass = false;
      else if(MCT < 150)
         Pass = false;

      if(Pass == true)
         PassedWeight[Model] = PassedWeight[Model] + WPU;
   }

   cout << "Summary for input file \"" << InputFile << endl;
   cout << endl;

   for(map<pair<int, int>, double>::iterator iter = AllWeight.begin(); iter != AllWeight.end(); iter++)
   {
      pair<int, int> Model = iter->first;

      cout << "Model: " << Model.first << " " << Model.second << endl;

      cout << "Efficiencies (MR > 400):" << endl;
      cout << "   Nominal " << PassedWeight[Model] / AllWeight[Model] << endl;
      cout << "   11.54%  " << PassedWeight[Model] / AllWeight[Model] * 0.1154 << endl;
      cout << endl;
   }
}




