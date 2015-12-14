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
#include "JetCorrectionUncertainty.h"

#define PDFSET_CTEQ66 0
#define PDFSET_MRST2006NNLO 1
#define PDFSET_NNPDF10100 2

int main();
void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min = 0.25, int Type = PDFSET_CTEQ66);

int main()
{
   CheckSampleEfficiency("T2bbList", 1, 0.25, PDFSET_CTEQ66);
   CheckSampleEfficiency("T2bbList", 1, 0.25, PDFSET_MRST2006NNLO);
   CheckSampleEfficiency("T2bbList", 1, 0.25, PDFSET_NNPDF10100);

   return 0;
}

void CheckSampleEfficiency(string InputFile, double ExpectedYield, double R2Min, int Type)
{
   JetCorrectionUncertainty CaloJetUncertainty("TextFiles/GR_R_41_V0::All_AK5Calo_Uncertainty.txt");

   // TChain Tree("LQ3Tree", "LQ3Tree");
   // Tree.AddFile(InputFile.c_str());

   TChain *Tree = ChainAll(InputFile.c_str(), "LQ3Tree");

   TreeRecord M;
   M.SetBranchAddress(Tree);

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
   map<pair<int, int>, double> AllEventsCentralUp;
   map<pair<int, int>, double> AllEventsCentralDown;
   map<pair<int, int>, double> PassedEventsCentral;
   map<pair<int, int>, double> PassedEventsCentralUp;
   map<pair<int, int>, double> PassedEventsCentralDown;

   map<pair<int, int>, vector<double> > AllEventsPairs;
   map<pair<int, int>, vector<double> > PassedEventsPairs;

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      pair<int, int> Model((int)(M.m0 + 0.0001), (int)(M.m12 + 0.0001));
      if(AllEvents.find(Model) == AllEvents.end())
      {
         AllEvents.insert(pair<pair<int, int>, double>(Model, 0));
         PassedEvents.insert(pair<pair<int, int>, double>(Model, 0));

         AllEventsCentral.insert(pair<pair<int, int>, double>(Model, 0));
         AllEventsCentralUp.insert(pair<pair<int, int>, double>(Model, 0));
         AllEventsCentralDown.insert(pair<pair<int, int>, double>(Model, 0));
         PassedEventsCentral.insert(pair<pair<int, int>, double>(Model, 0));
         PassedEventsCentralUp.insert(pair<pair<int, int>, double>(Model, 0));
         PassedEventsCentralDown.insert(pair<pair<int, int>, double>(Model, 0));

         AllEventsPairs.insert(pair<pair<int, int>, vector<double> >(Model, vector<double>()));
         PassedEventsPairs.insert(pair<pair<int, int>, vector<double> >(Model, vector<double>()));

         AllEventsPairs[Model].resize(*NPDF - 1);
         PassedEventsPairs[Model].resize(*NPDF - 1);
      }

      double JetUncertainty[500] = {0};
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

         if(M.CaloJetPT[i] > 60)
            CaloJetCount60 = CaloJetCount60 + 1;
         if(M.CaloJetPT[i] + JetUncertainty[i] > 60)
            CaloJetCount60Up = CaloJetCount60Up + 1;
         if(M.CaloJetPT[i] - JetUncertainty[i] > 60)
            CaloJetCount60Down = CaloJetCount60Down + 1;
      }

      int JetPassBTagLoose = 0;
      int JetPassBTagLooseUp = 0;
      int JetPassBTagLooseDown = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] <= -3 || M.CaloJetEta[i] >= 3)
            continue;
         if(M.CaloJetTCHETag[i] <= 3.3)
            continue;

         if(M.CaloJetPT[i] > 80)
            JetPassBTagLoose = JetPassBTagLoose + 1;
         if(M.CaloJetPT[i] + JetUncertainty[i] > 80)
            JetPassBTagLooseUp = JetPassBTagLooseUp + 1;
         if(M.CaloJetPT[i] - JetUncertainty[i] > 80)
            JetPassBTagLooseDown = JetPassBTagLooseDown + 1;
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

         if(M.CaloJetPT[i] > 40)
            CaloJets.push_back(NewJet);
         if(M.CaloJetPT[i] + JetUncertainty[i] > 40)
            CaloJetsUp.push_back(NewJet);
         if(M.CaloJetPT[i] - JetUncertainty[i] > 40)
            CaloJetsDown.push_back(NewJet);
      }

      vector<FourVector> Hemispheres;
      vector<FourVector> HemispheresUp;
      vector<FourVector> HemispheresDown;
      if(CaloJets.size() >= 2)
         Hemispheres = SplitIntoGroups(CaloJets, true);
      if(CaloJetsUp.size() >= 2)
         HemispheresUp = SplitIntoGroups(CaloJetsUp, true);
      if(CaloJetsDown.size() >= 2)
         HemispheresDown = SplitIntoGroups(CaloJetsDown, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      PFMET[0] = PFMET.GetPT();

      double MR = 0;
      double R = 0;
      double MRUp = 0;
      double RUp = 0;
      double MRDown = 0;
      double RDown = 0;

      if(Hemispheres.size() == 2)
      {
         MR = Get2011MR(Hemispheres[0], Hemispheres[1]);
         R = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      }
      if(HemispheresUp.size() == 2)
      {
         MRUp = Get2011MR(HemispheresUp[0], HemispheresUp[1]);
         RUp = Get2011R(HemispheresUp[0], HemispheresUp[1], PFMET);
      }
      if(HemispheresDown.size() == 2)
      {
         MRDown = Get2011MR(HemispheresDown[0], HemispheresDown[1]);
         RDown = Get2011R(HemispheresDown[0], HemispheresDown[1], PFMET);
      }

      double R2 = R * R;
      double R2Up = RUp * RUp;
      double R2Down = RDown * RDown;

      AllEvents[Model] = AllEvents[Model] + 1;
      AllEventsCentral[Model] = AllEventsCentral[Model] + WPDF[0];
      AllEventsCentralUp[Model] = AllEventsCentralUp[Model] + WPDF[0];
      AllEventsCentralDown[Model] = AllEventsCentralDown[Model] + WPDF[0];
      for(int i = 1; i < *NPDF; i++)   // loop over the eigenvalue variations
         AllEventsPairs[Model][i-1] = AllEventsPairs[Model][i-1] + WPDF[i];

      if(M.GoodElectronCount == 0 && M.GoodMuonCount == 0 && CaloJetCount60 >= 2 && JetPassBTagLoose >= 2 && R2 >= R2Min && MR >= 400)
      {
         PassedEvents[Model] = PassedEvents[Model] + 1;
         PassedEventsCentral[Model] = PassedEventsCentral[Model] + WPDF[0];
         for(int i = 1; i < *NPDF; i++)   // loop over the eigenvalue variations
            PassedEventsPairs[Model][i-1] = PassedEventsPairs[Model][i-1] + WPDF[i];
      }
      if(M.GoodElectronCount == 0 && M.GoodMuonCount == 0 && CaloJetCount60Up >= 2 && JetPassBTagLooseUp >= 2 && R2Up >= R2Min && MRUp >= 400)
         PassedEventsCentralUp[Model] = PassedEventsCentralUp[Model] + WPDF[0];
      if(M.GoodElectronCount == 0 && M.GoodMuonCount == 0 && CaloJetCount60Down >= 2 && JetPassBTagLooseDown >= 2 && R2Down >= R2Min && MRDown >= 400)
         PassedEventsCentralDown[Model] = PassedEventsCentralDown[Model] + WPDF[0];
   }

   for(map<pair<int, int>, double>::iterator iter = AllEvents.begin(); iter != AllEvents.end(); iter++)
   {
      pair<int, int> Model = iter->first;

      double CentralAcceptance = PassedEventsCentral[Model] / AllEventsCentral[Model];
      double JESUpAcceptance = PassedEventsCentralUp[Model] / AllEventsCentralUp[Model];
      double JESDownAcceptance = PassedEventsCentralDown[Model] / AllEventsCentralDown[Model];

      cout << "Model (" << Model.first << ", " << Model.second << ")" << endl;
      cout << "   No PDF weighting = " << PassedEvents[Model] / AllEvents[Model] << endl;
      cout << "   Central PDF acceptance = " << CentralAcceptance << endl;
      cout << "   JES up = " << JESUpAcceptance << endl;
      cout << "   JES down = " << JESDownAcceptance << endl;
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
         << " " << WPlus << " " << WMinus << " " << fabs(JESUpAcceptance - JESDownAcceptance) / 2 / CentralAcceptance << endl;

      cout << endl;
   }
}





