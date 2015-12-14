#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

#include "TChain.h"
#include "TH1D.h"
#include "TFile.h"

#include "TauHelperFunctions2.h"

#include "ChainAll.h"
#include "ReadLQ3Tree.h"

#define PDFSET_CTEQ66 0
#define PDFSET_MRST2006NNLO 1
#define PDFSET_NNPDF10100 2

int main();
void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min = 0.25, int Type = PDFSET_CTEQ66);
double GetSF(double PT);

int main()
{
   CheckSampleEfficiency("T2bbList", 1, 0.42, PDFSET_CTEQ66);
   CheckSampleEfficiency("T2bbList", 1, 0.42, PDFSET_MRST2006NNLO);
   CheckSampleEfficiency("T2bbList", 1, 0.42, PDFSET_NNPDF10100);

   return 0;
}

void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min, int Type)
{
   // TChain Tree("LQ3Tree", "LQ3Tree");
   // Tree.AddFile(InputFile.c_str());

   TChain *Tree = ChainAll(InputFile.c_str(), "LQ3Tree");

   TreeRecord M;
   M.SetBranchAddress(Tree);
   M.InitializeWeight("PU.root");

   Tree->SetBranchStatus("PFJet*", false);
   Tree->SetBranchStatus("CaloJetCSVTag", false);
   Tree->SetBranchStatus("CaloJetCSVMTag", false);
   Tree->SetBranchStatus("CaloJetTCHPTag", false);

   int *NPDF;
   double *WPDF;

   if(Type == PDFSET_CTEQ66)
   {
      NPDF = &M.NCTEQ66;
      WPDF = M.WCTEQ66;
   }
   if(Type == PDFSET_MRST2006NNLO)
   {
      NPDF = &M.NMRST2006NNLO;
      WPDF = M.WMRST2006NNLO;
   }
   if(Type == PDFSET_NNPDF10100)
   {
      NPDF = &M.NNNPDF10100;
      WPDF = M.WNNPDF10100;
   }

   map<pair<int, int>, double> AllEvents;
   map<pair<int, int>, double> PassedEvents;

   map<pair<int, int>, double> AllEventsCentral;
   map<pair<int, int>, double> AllEvents2Central;
   map<pair<int, int>, double> PassedEventsCentral;
   map<pair<int, int>, double> PassedEvents2Central;

   map<pair<int, int>, vector<double> > AllEventsPairs;
   map<pair<int, int>, vector<double> > AllEvents2Pairs;
   map<pair<int, int>, vector<double> > PassedEventsPairs;
   map<pair<int, int>, vector<double> > PassedEvents2Pairs;

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      double WPU = M.GetCurrentWeight();

      pair<int, int> Model((int)(M.m0 + 0.0001), (int)(M.m12 + 0.0001));
      if(AllEvents.find(Model) == AllEvents.end())
      {
         AllEvents.insert(pair<pair<int, int>, double>(Model, 0));
         PassedEvents.insert(pair<pair<int, int>, double>(Model, 0));

         AllEventsCentral.insert(pair<pair<int, int>, double>(Model, 0));
         AllEvents2Central.insert(pair<pair<int, int>, double>(Model, 0));
         PassedEventsCentral.insert(pair<pair<int, int>, double>(Model, 0));
         PassedEvents2Central.insert(pair<pair<int, int>, double>(Model, 0));

         AllEventsPairs.insert(pair<pair<int, int>, vector<double> >(Model, vector<double>()));
         AllEvents2Pairs.insert(pair<pair<int, int>, vector<double> >(Model, vector<double>()));
         PassedEventsPairs.insert(pair<pair<int, int>, vector<double> >(Model, vector<double>()));
         PassedEvents2Pairs.insert(pair<pair<int, int>, vector<double> >(Model, vector<double>()));

         AllEventsPairs[Model].resize(*NPDF - 1);
         AllEvents2Pairs[Model].resize(*NPDF - 1);
         PassedEventsPairs[Model].resize(*NPDF - 1);
         PassedEvents2Pairs[Model].resize(*NPDF - 1);
      }

      int CaloJetCount60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] <= -3 || M.CaloJetEta[i] >= 3)
            continue;

         if(M.CaloJetPT[i] > 60)
            CaloJetCount60 = CaloJetCount60 + 1;
      }

      int JetPassBTagLoose = 0;
      double AccumulativeSF = 1;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] <= -3 || M.CaloJetEta[i] >= 3)
            continue;
         if(M.CaloJetTCHETag[i] <= 3.3)
            continue;

         if(M.CaloJetPT[i] > 80)
         {
            JetPassBTagLoose = JetPassBTagLoose + 1;
            AccumulativeSF = AccumulativeSF * GetSF(M.CaloJetPT[i]);
         }
      }

      vector<FourVector> CaloJets;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         if(M.CaloJetPT[i] > 40)
            CaloJets.push_back(NewJet);
      }

      vector<FourVector> Hemispheres;
      if(CaloJets.size() >= 2)
         Hemispheres = SplitIntoGroups(CaloJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      PFMET[0] = PFMET.GetPT();

      double MR = 0;
      double R = 0;

      if(Hemispheres.size() == 2)
      {
         MR = Get2011MR(Hemispheres[0], Hemispheres[1]);
         R = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      }

      double R2 = R * R;

      AllEvents[Model] = AllEvents[Model] + WPU;
      AllEventsCentral[Model] = AllEventsCentral[Model] + WPDF[0] * WPU;
      AllEvents2Central[Model] = AllEvents2Central[Model] + WPDF[0] * WPDF[0] * WPU;
      for(int i = 1; i < *NPDF; i++)   // loop over the eigenvalue variations
      {
         AllEventsPairs[Model][i-1] = AllEventsPairs[Model][i-1] + WPDF[i] * WPU;
         AllEvents2Pairs[Model][i-1] = AllEvents2Pairs[Model][i-1] + WPDF[i] * WPDF[i] * WPU;
      }

      if(M.GoodElectronCount == 0 && M.GoodMuonCount == 0 && CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2 >= R2Min && MR >= 400)
      {
         PassedEvents[Model] = PassedEvents[Model] + AccumulativeSF * WPU;
         PassedEventsCentral[Model] = PassedEventsCentral[Model] + WPDF[0] * AccumulativeSF * WPU;
         PassedEvents2Central[Model] = PassedEvents2Central[Model] + WPDF[0] * WPDF[0] * AccumulativeSF * WPU;
         for(int i = 1; i < *NPDF; i++)   // loop over the eigenvalue variations
         {
            PassedEventsPairs[Model][i-1] = PassedEventsPairs[Model][i-1] + WPDF[i] * AccumulativeSF * WPU;
            PassedEvents2Pairs[Model][i-1] = PassedEvents2Pairs[Model][i-1] + WPDF[i] * WPDF[i] * AccumulativeSF * WPU;
         }
      }
   }

   for(map<pair<int, int>, double>::iterator iter = AllEvents.begin(); iter != AllEvents.end(); iter++)
   {
      pair<int, int> Model = iter->first;

      double CentralAcceptance = PassedEventsCentral[Model] / AllEventsCentral[Model];

      cout << "Model (" << Model.first << ", " << Model.second << ")" << endl;
      cout << "   No PDF weighting = " << PassedEvents[Model] / AllEvents[Model] << endl;
      cout << "   Central PDF acceptance = " << CentralAcceptance << endl;
      // cout << endl;

      double W2Plus = 0;
      double W2Minus = 0;
      int NPlus = 0;
      int NMinus = 0;

      for(int i = 1; i + 1 < *NPDF; i = i + 2)
      {
         double Acceptance1 = PassedEventsPairs[Model][i-1] / AllEventsPairs[Model][i-1];
         double Acceptance2 = PassedEventsPairs[Model][i] / AllEventsPairs[Model][i];

         /*
         cout << "      Variation " << (i + 1) / 2 << " - 1 = " << Acceptance1 << ", ";
         if(Acceptance1 > CentralAcceptance)
            cout << "+";
         cout << (Acceptance1 / CentralAcceptance - 1) * 100 << "%" << endl;

         cout << "      Variation " << i / 2 << " - 2 = " << Acceptance2 << ", ";
         if(Acceptance2 > CentralAcceptance)
            cout << "+";
         cout << (Acceptance2 / CentralAcceptance - 1) * 100 << "%" << endl;
         */

         double Variation1 = max(Acceptance1 / CentralAcceptance - 1, Acceptance2 / CentralAcceptance - 1);
         double Variation2 = min(Acceptance1 / CentralAcceptance - 1, Acceptance2 / CentralAcceptance - 1);

         if(Type != PDFSET_NNPDF10100)
         {
            if(Variation1 < 0)   Variation1 = 0;
            if(Variation2 > 0)   Variation2 = 0;

            W2Plus = W2Plus + Variation1 * Variation1;
            W2Minus = W2Minus + Variation2 * Variation2;
         }
         else
         {
            if(Variation1 > 0)
            {
               W2Plus = W2Plus + Variation1 * Variation1;
               NPlus = NPlus + 1;
            }
            else
            {
               W2Minus = W2Minus + Variation1 * Variation1;
               NMinus = NMinus + 1;
            }
            if(Variation2 > 0)
            {
               W2Plus = W2Plus + Variation2 * Variation2;
               NPlus = NPlus + 1;
            }
            else
            {
               W2Minus = W2Minus + Variation2 * Variation2;
               NMinus = NMinus + 1;
            }
         }

         // cout << endl;
      }

      double WPlus = sqrt(W2Plus);
      double WMinus = sqrt(W2Minus);

      if(Type == PDFSET_NNPDF10100)
      {
         WPlus = WPlus / sqrt(NPlus);
         WMinus = WMinus / sqrt(NMinus);
      }

      cout << "   Final relative uncertainty = " << "+" << WPlus * 100 << "% / -" << WMinus * 100 << "%" << endl;

      cout << "[RESULT]";
      if(Type == PDFSET_CTEQ66)         cout << "[CTEQ]";
      if(Type == PDFSET_MRST2006NNLO)   cout << "[MRST]";
      if(Type == PDFSET_NNPDF10100)     cout << "[NNPDF]";
      cout <<" " << Model.first << " " << Model.second << " " << CentralAcceptance
         << " " << WPlus << " " << WMinus << endl;

      cout << endl;
   }
}


double GetSF(double PT)
{
   int BinCount = 14;
   double PTMin[] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500};
   double PTMax[] = {40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 670};
   double SF[] = {0.981363,0.985227,0.989821,0.993138,0.993361,0.998067,0.998301,1.00153,0.999588,0.998280,0.989654,0.980549,0.974686,0.965412};

   if(PT < PTMin[0])
      return SF[0];
   if(PT >= PTMax[BinCount-1])
      return SF[BinCount-1];

   for(int i = 0; i < BinCount; i++)
   {
      if(PT >= PTMin[i] && PT < PTMax[i])
         return SF[i];
   }

   return -1;   // shouldn't happen
}



