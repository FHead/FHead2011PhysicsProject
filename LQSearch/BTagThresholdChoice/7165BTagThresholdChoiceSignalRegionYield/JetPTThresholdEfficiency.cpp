#include <cmath>
#include <string>
#include <map>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TColor.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"

#include "PlotHelper2.h"
#include "SetStyle.h"
#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);
void JetPTThresholdEfficiency(string InputFileName, string OutputBase, double CrossSection);
void Get1DCumulativeHistogram(TH1D &Source, TH1D &Destination);
double DeterminePT(multimap<double, int, greater<double> > &List);
double DeterminePT(multimap<double, int, greater<double> > &List1, multimap<double, int, greater<double> > &List2);

int main(int argc, char *argv[])
{
   SetStyle();

   string Tag = "LQ450";
   if(argc > 1)
      Tag = argv[1];

   double CrossSection = 1;
   if(argc > 2)
   {
      stringstream str(argv[2]);
      str >> CrossSection;
   }

   string InputFileName = "Samples/" + Tag + ".root";
   string OutputBase = Tag;

   JetPTThresholdEfficiency(InputFileName, OutputBase, CrossSection);
}

void JetPTThresholdEfficiency(string InputFileName, string OutputBase, double CrossSection)
{
   double Luminosity = 1000;   // 1/fb

   TH2D HMRVsR("HMRVsR", "MR vs. R for sanity check....", 100, 0, 1000, 100, 0, 1);

   TH1D HCountPassTCHEL("HCountPassTCHEL", "Count passing TCHEL", 400, 0, 200);
   TH1D HCountPassTCHEM("HCountPassTCHEM", "Count passing TCHEM", 400, 0, 200);
   TH1D HCountPassTCHET("HCountPassTCHET", "Count passing TCHET", 400, 0, 200);
   TH1D HCountPassTCHPL("HCountPassTCHPL", "Count passing TCHPL", 400, 0, 200);
   TH1D HCountPassTCHPM("HCountPassTCHPM", "Count passing TCHPM", 400, 0, 200);
   TH1D HCountPassTCHPT("HCountPassTCHPT", "Count passing TCHPT", 400, 0, 200);

   TH1D HCountPassTCHELTCHEL("HCountPassTCHELTCHEL", "Count passing TCHEL x TCHEL", 400, 0, 200);
   TH1D HCountPassTCHELTCHEM("HCountPassTCHELTCHEM", "Count passing TCHEL x TCHEM", 400, 0, 200);
   TH1D HCountPassTCHELTCHET("HCountPassTCHELTCHET", "Count passing TCHEL x TCHET", 400, 0, 200);
   TH1D HCountPassTCHELTCHPL("HCountPassTCHELTCHPL", "Count passing TCHEL x TCHPL", 400, 0, 200);
   TH1D HCountPassTCHELTCHPM("HCountPassTCHELTCHPM", "Count passing TCHEL x TCHPM", 400, 0, 200);
   TH1D HCountPassTCHELTCHPT("HCountPassTCHELTCHPT", "Count passing TCHEL x TCHPT", 400, 0, 200);
   TH1D HCountPassTCHEMTCHEM("HCountPassTCHEMTCHEM", "Count passing TCHEM x TCHEM", 400, 0, 200);
   TH1D HCountPassTCHEMTCHET("HCountPassTCHEMTCHET", "Count passing TCHEM x TCHET", 400, 0, 200);
   TH1D HCountPassTCHEMTCHPL("HCountPassTCHEMTCHPL", "Count passing TCHEM x TCHPL", 400, 0, 200);
   TH1D HCountPassTCHEMTCHPM("HCountPassTCHEMTCHPM", "Count passing TCHEM x TCHPM", 400, 0, 200);
   TH1D HCountPassTCHEMTCHPT("HCountPassTCHEMTCHPT", "Count passing TCHEM x TCHPT", 400, 0, 200);
   TH1D HCountPassTCHETTCHET("HCountPassTCHETTCHET", "Count passing TCHET x TCHET", 400, 0, 200);
   TH1D HCountPassTCHETTCHPL("HCountPassTCHETTCHPL", "Count passing TCHET x TCHPL", 400, 0, 200);
   TH1D HCountPassTCHETTCHPM("HCountPassTCHETTCHPM", "Count passing TCHET x TCHPM", 400, 0, 200);
   TH1D HCountPassTCHETTCHPT("HCountPassTCHETTCHPT", "Count passing TCHET x TCHPT", 400, 0, 200);
   TH1D HCountPassTCHPLTCHPL("HCountPassTCHPLTCHPL", "Count passing TCHPL x TCHPL", 400, 0, 200);
   TH1D HCountPassTCHPLTCHPM("HCountPassTCHPLTCHPM", "Count passing TCHPL x TCHPM", 400, 0, 200);
   TH1D HCountPassTCHPLTCHPT("HCountPassTCHPLTCHPT", "Count passing TCHPL x TCHPT", 400, 0, 200);
   TH1D HCountPassTCHPMTCHPM("HCountPassTCHPMTCHPM", "Count passing TCHPM x TCHPM", 400, 0, 200);
   TH1D HCountPassTCHPMTCHPT("HCountPassTCHPMTCHPT", "Count passing TCHPM x TCHPT", 400, 0, 200);
   TH1D HCountPassTCHPTTCHPT("HCountPassTCHPTTCHPT", "Count passing TCHPT x TCHPT", 400, 0, 200);

   TFile F(InputFileName.c_str());
   TTree *Tree = (TTree *)F.Get("LQ3Tree");
   if(Tree == NULL)
      return;

   TreeRecord M;
   M.SetBranchAddress(Tree);

   int EntryCount = Tree->GetEntries();   cout << "Total entry = " << EntryCount << endl;
   for(int iEntry = 1; iEntry <= EntryCount; iEntry++)
   {
      if(iEntry % 500000 == 0)
         cout << "Processing entry " << iEntry << "/" << EntryCount << endl;

      M.Clear();
      Tree->GetEntry(iEntry - 1);

      int JetAbove60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 60)
            continue;
         
         JetAbove60 = JetAbove60 + 1;
      }
      if(JetAbove60 < 2)
         continue;

      if(M.GoodElectronCount80 > 0 && M.Electron1PT > 20)
         continue;
      if(M.GoodMuonCountTight > 0 && M.Muon1PT > 10)
         continue;

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 40)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);
         GoodJets.push_back(NewJet);
      }
      if(GoodJets.size() < 2)
         continue;
      if(GoodJets.size() > 20)   // :(
         continue;

      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);

      double GammaMRStar = GetMRStar(Groups[0], Groups[1]) * GetGammaRStar(Groups[0], Groups[1]);
      double RStar = GetRStar(Groups[0], Groups[1], PFMET);
      HMRVsR.Fill(GammaMRStar, RStar);

      if(GammaMRStar > 400 && RStar > 0.4)
      {
         multimap<double, int, greater<double> > JetPassTCHEL;
         multimap<double, int, greater<double> > JetPassTCHEM;
         multimap<double, int, greater<double> > JetPassTCHET;
         multimap<double, int, greater<double> > JetPassTCHPL;
         multimap<double, int, greater<double> > JetPassTCHPM;
         multimap<double, int, greater<double> > JetPassTCHPT;

         for(int i = 0; i < M.CaloJetCount; i++)
         {
            if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
               continue;

            if(M.CaloJetTCHETag[i] > 1.7)
               JetPassTCHEL.insert(pair<double, int>(M.CaloJetPT[i], i));
            if(M.CaloJetTCHETag[i] > 3.3)
               JetPassTCHEM.insert(pair<double, int>(M.CaloJetPT[i], i));
            if(M.CaloJetTCHETag[i] > 10.2)
               JetPassTCHET.insert(pair<double, int>(M.CaloJetPT[i], i));
            if(M.CaloJetTCHPTag[i] > 1.19)
               JetPassTCHPL.insert(pair<double, int>(M.CaloJetPT[i], i));
            if(M.CaloJetTCHPTag[i] > 1.93)
               JetPassTCHPM.insert(pair<double, int>(M.CaloJetPT[i], i));
            if(M.CaloJetTCHPTag[i] > 3.41)
               JetPassTCHPT.insert(pair<double, int>(M.CaloJetPT[i], i));
         }

         HCountPassTCHEL.Fill(DeterminePT(JetPassTCHEL));
         HCountPassTCHEM.Fill(DeterminePT(JetPassTCHEM));
         HCountPassTCHET.Fill(DeterminePT(JetPassTCHET));
         HCountPassTCHPL.Fill(DeterminePT(JetPassTCHPL));
         HCountPassTCHPM.Fill(DeterminePT(JetPassTCHPM));
         HCountPassTCHPT.Fill(DeterminePT(JetPassTCHPT));

         HCountPassTCHELTCHEL.Fill(DeterminePT(JetPassTCHEL, JetPassTCHEL));
         HCountPassTCHELTCHEM.Fill(DeterminePT(JetPassTCHEL, JetPassTCHEM));
         HCountPassTCHELTCHET.Fill(DeterminePT(JetPassTCHEL, JetPassTCHET));
         HCountPassTCHELTCHPL.Fill(DeterminePT(JetPassTCHEL, JetPassTCHPL));
         HCountPassTCHELTCHPM.Fill(DeterminePT(JetPassTCHEL, JetPassTCHPM));
         HCountPassTCHELTCHPT.Fill(DeterminePT(JetPassTCHEL, JetPassTCHPT));
         HCountPassTCHEMTCHEM.Fill(DeterminePT(JetPassTCHEM, JetPassTCHEM));
         HCountPassTCHEMTCHET.Fill(DeterminePT(JetPassTCHEM, JetPassTCHET));
         HCountPassTCHEMTCHPL.Fill(DeterminePT(JetPassTCHEM, JetPassTCHPL));
         HCountPassTCHEMTCHPM.Fill(DeterminePT(JetPassTCHEM, JetPassTCHPM));
         HCountPassTCHEMTCHPT.Fill(DeterminePT(JetPassTCHEM, JetPassTCHPT));
         HCountPassTCHETTCHET.Fill(DeterminePT(JetPassTCHET, JetPassTCHET));
         HCountPassTCHETTCHPL.Fill(DeterminePT(JetPassTCHET, JetPassTCHPL));
         HCountPassTCHETTCHPM.Fill(DeterminePT(JetPassTCHET, JetPassTCHPM));
         HCountPassTCHETTCHPT.Fill(DeterminePT(JetPassTCHET, JetPassTCHPT));
         HCountPassTCHPLTCHPL.Fill(DeterminePT(JetPassTCHPL, JetPassTCHPL));
         HCountPassTCHPLTCHPM.Fill(DeterminePT(JetPassTCHPL, JetPassTCHPM));
         HCountPassTCHPLTCHPT.Fill(DeterminePT(JetPassTCHPL, JetPassTCHPT));
         HCountPassTCHPMTCHPM.Fill(DeterminePT(JetPassTCHPM, JetPassTCHPM));
         HCountPassTCHPMTCHPT.Fill(DeterminePT(JetPassTCHPM, JetPassTCHPT));
         HCountPassTCHPTTCHPT.Fill(DeterminePT(JetPassTCHPT, JetPassTCHPT));
      }
   }

   TH1D HYieldPassTCHEL("HYieldPassTCHEL",
      "Yield remaining passing TCHEL as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHEM("HYieldPassTCHEM",
      "Yield remaining passing TCHEM as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHET("HYieldPassTCHET",
      "Yield remaining passing TCHET as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHPL("HYieldPassTCHPL",
      "Yield remaining passing TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHPM("HYieldPassTCHPM",
      "Yield remaining passing TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHPT("HYieldPassTCHPT",
      "Yield remaining passing TCHPT as a function of threshold;PT", 400, 0, 200);
   
   TH1D HYieldPassTCHELTCHEL("HYieldPassTCHELTCHEL",
      "Yield remaining passing TCHEL x TCHEL as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHELTCHEM("HYieldPassTCHELTCHEM",
      "Yield remaining passing TCHEL x TCHEM as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHELTCHET("HYieldPassTCHELTCHET",
      "Yield remaining passing TCHEL x TCHET as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHELTCHPL("HYieldPassTCHELTCHPL",
      "Yield remaining passing TCHEL x TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHELTCHPM("HYieldPassTCHELTCHPM",
      "Yield remaining passing TCHEL x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHELTCHPT("HYieldPassTCHELTCHPT",
      "Yield remaining passing TCHEL x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHEMTCHEM("HYieldPassTCHEMTCHEM",
      "Yield remaining passing TCHEM x TCHEM as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHEMTCHET("HYieldPassTCHEMTCHET",
      "Yield remaining passing TCHEM x TCHET as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHEMTCHPL("HYieldPassTCHEMTCHPL",
      "Yield remaining passing TCHEM x TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHEMTCHPM("HYieldPassTCHEMTCHPM",
      "Yield remaining passing TCHEM x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHEMTCHPT("HYieldPassTCHEMTCHPT",
      "Yield remaining passing TCHEM x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHETTCHET("HYieldPassTCHETTCHET",
      "Yield remaining passing TCHET x TCHET as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHETTCHPL("HYieldPassTCHETTCHPL",
      "Yield remaining passing TCHET x TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHETTCHPM("HYieldPassTCHETTCHPM",
      "Yield remaining passing TCHET x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHETTCHPT("HYieldPassTCHETTCHPT",
      "Yield remaining passing TCHET x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHPLTCHPL("HYieldPassTCHPLTCHPL",
      "Yield remaining passing TCHPL x TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHPLTCHPM("HYieldPassTCHPLTCHPM",
      "Yield remaining passing TCHPL x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHPLTCHPT("HYieldPassTCHPLTCHPT",
      "Yield remaining passing TCHPL x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHPMTCHPM("HYieldPassTCHPMTCHPM",
      "Yield remaining passing TCHPM x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHPMTCHPT("HYieldPassTCHPMTCHPT",
      "Yield remaining passing TCHPM x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HYieldPassTCHPTTCHPT("HYieldPassTCHPTTCHPT",
      "Yield remaining passing TCHPT x TCHPT as a function of threshold;PT", 400, 0, 200);

   Get1DCumulativeHistogram(HCountPassTCHEL, HYieldPassTCHEL);
   Get1DCumulativeHistogram(HCountPassTCHEM, HYieldPassTCHEM);
   Get1DCumulativeHistogram(HCountPassTCHET, HYieldPassTCHET);
   Get1DCumulativeHistogram(HCountPassTCHPL, HYieldPassTCHPL);
   Get1DCumulativeHistogram(HCountPassTCHPM, HYieldPassTCHPM);
   Get1DCumulativeHistogram(HCountPassTCHPT, HYieldPassTCHPT);
   
   Get1DCumulativeHistogram(HCountPassTCHELTCHEL, HYieldPassTCHELTCHEL);
   Get1DCumulativeHistogram(HCountPassTCHELTCHEM, HYieldPassTCHELTCHEM);
   Get1DCumulativeHistogram(HCountPassTCHELTCHET, HYieldPassTCHELTCHET);
   Get1DCumulativeHistogram(HCountPassTCHELTCHPL, HYieldPassTCHELTCHPL);
   Get1DCumulativeHistogram(HCountPassTCHELTCHPM, HYieldPassTCHELTCHPM);
   Get1DCumulativeHistogram(HCountPassTCHELTCHPT, HYieldPassTCHELTCHPT);
   Get1DCumulativeHistogram(HCountPassTCHEMTCHEM, HYieldPassTCHEMTCHEM);
   Get1DCumulativeHistogram(HCountPassTCHEMTCHET, HYieldPassTCHEMTCHET);
   Get1DCumulativeHistogram(HCountPassTCHEMTCHPL, HYieldPassTCHEMTCHPL);
   Get1DCumulativeHistogram(HCountPassTCHEMTCHPM, HYieldPassTCHEMTCHPM);
   Get1DCumulativeHistogram(HCountPassTCHEMTCHPT, HYieldPassTCHEMTCHPT);
   Get1DCumulativeHistogram(HCountPassTCHETTCHET, HYieldPassTCHETTCHET);
   Get1DCumulativeHistogram(HCountPassTCHETTCHPL, HYieldPassTCHETTCHPL);
   Get1DCumulativeHistogram(HCountPassTCHETTCHPM, HYieldPassTCHETTCHPM);
   Get1DCumulativeHistogram(HCountPassTCHETTCHPT, HYieldPassTCHETTCHPT);
   Get1DCumulativeHistogram(HCountPassTCHPLTCHPL, HYieldPassTCHPLTCHPL);
   Get1DCumulativeHistogram(HCountPassTCHPLTCHPM, HYieldPassTCHPLTCHPM);
   Get1DCumulativeHistogram(HCountPassTCHPLTCHPT, HYieldPassTCHPLTCHPT);
   Get1DCumulativeHistogram(HCountPassTCHPMTCHPM, HYieldPassTCHPMTCHPM);
   Get1DCumulativeHistogram(HCountPassTCHPMTCHPT, HYieldPassTCHPMTCHPT);
   Get1DCumulativeHistogram(HCountPassTCHPTTCHPT, HYieldPassTCHPTTCHPT);

   HYieldPassTCHEL.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHEM.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHET.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHPL.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHPM.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHPT.Scale(CrossSection * Luminosity / EntryCount);
   
   HYieldPassTCHELTCHEL.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHELTCHEM.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHELTCHET.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHELTCHPL.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHELTCHPM.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHELTCHPT.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHEMTCHEM.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHEMTCHET.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHEMTCHPL.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHEMTCHPM.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHEMTCHPT.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHETTCHET.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHETTCHPL.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHETTCHPM.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHETTCHPT.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHPLTCHPL.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHPLTCHPM.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHPLTCHPT.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHPMTCHPM.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHPMTCHPT.Scale(CrossSection * Luminosity / EntryCount);
   HYieldPassTCHPTTCHPT.Scale(CrossSection * Luminosity / EntryCount);

   HYieldPassTCHEL.SetMinimum(0.5);
   HYieldPassTCHEM.SetMinimum(0.5);
   HYieldPassTCHET.SetMinimum(0.5);
   HYieldPassTCHPL.SetMinimum(0.5);
   HYieldPassTCHPM.SetMinimum(0.5);
   HYieldPassTCHPT.SetMinimum(0.5);
   
   HYieldPassTCHELTCHEL.SetMinimum(0.5);
   HYieldPassTCHELTCHEM.SetMinimum(0.5);
   HYieldPassTCHELTCHET.SetMinimum(0.5);
   HYieldPassTCHELTCHPL.SetMinimum(0.5);
   HYieldPassTCHELTCHPM.SetMinimum(0.5);
   HYieldPassTCHELTCHPT.SetMinimum(0.5);
   HYieldPassTCHEMTCHEM.SetMinimum(0.5);
   HYieldPassTCHEMTCHET.SetMinimum(0.5);
   HYieldPassTCHEMTCHPL.SetMinimum(0.5);
   HYieldPassTCHEMTCHPM.SetMinimum(0.5);
   HYieldPassTCHEMTCHPT.SetMinimum(0.5);
   HYieldPassTCHETTCHET.SetMinimum(0.5);
   HYieldPassTCHETTCHPL.SetMinimum(0.5);
   HYieldPassTCHETTCHPM.SetMinimum(0.5);
   HYieldPassTCHETTCHPT.SetMinimum(0.5);
   HYieldPassTCHPLTCHPL.SetMinimum(0.5);
   HYieldPassTCHPLTCHPM.SetMinimum(0.5);
   HYieldPassTCHPLTCHPT.SetMinimum(0.5);
   HYieldPassTCHPMTCHPM.SetMinimum(0.5);
   HYieldPassTCHPMTCHPT.SetMinimum(0.5);
   HYieldPassTCHPTTCHPT.SetMinimum(0.5);

   HYieldPassTCHEL.SetStats(0);
   HYieldPassTCHEM.SetStats(0);
   HYieldPassTCHET.SetStats(0);
   HYieldPassTCHPL.SetStats(0);
   HYieldPassTCHPM.SetStats(0);
   HYieldPassTCHPT.SetStats(0);
   
   HYieldPassTCHELTCHEL.SetStats(0);
   HYieldPassTCHELTCHEM.SetStats(0);
   HYieldPassTCHELTCHET.SetStats(0);
   HYieldPassTCHELTCHPL.SetStats(0);
   HYieldPassTCHELTCHPM.SetStats(0);
   HYieldPassTCHELTCHPT.SetStats(0);
   HYieldPassTCHEMTCHEM.SetStats(0);
   HYieldPassTCHEMTCHET.SetStats(0);
   HYieldPassTCHEMTCHPL.SetStats(0);
   HYieldPassTCHEMTCHPM.SetStats(0);
   HYieldPassTCHEMTCHPT.SetStats(0);
   HYieldPassTCHETTCHET.SetStats(0);
   HYieldPassTCHETTCHPL.SetStats(0);
   HYieldPassTCHETTCHPM.SetStats(0);
   HYieldPassTCHETTCHPT.SetStats(0);
   HYieldPassTCHPLTCHPL.SetStats(0);
   HYieldPassTCHPLTCHPM.SetStats(0);
   HYieldPassTCHPLTCHPT.SetStats(0);
   HYieldPassTCHPMTCHPM.SetStats(0);
   HYieldPassTCHPMTCHPT.SetStats(0);
   HYieldPassTCHPTTCHPT.SetStats(0);

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage("Jet PT threshold yield plots for " + OutputBase);

   vector<string> Explanations;
   Explanations.push_back("Where can we best set the jet pt threshold for counting b-jets?");
   Explanations.push_back("Set a threshold, evaluate expected yield in MR>400, R>0.4, for");
   Explanations.push_back("      both 1-tag and 2-tag cases, using all TCH working points");
   PsFile.AddTextPage(Explanations);

   vector<string> TableOfContentItems;
   TableOfContentItems.push_back("Count distribution - single tag");
   TableOfContentItems.push_back("Yield - single tag");
   TableOfContentItems.push_back("Count distribution - double tag");
   TableOfContentItems.push_back("Yield - double tag");

   vector<string> Destinations;
   Destinations.push_back("CountSingleTag");
   Destinations.push_back("YieldSingleTag");
   Destinations.push_back("CountDoubleTag");
   Destinations.push_back("YieldDoubleTag");

   PsFile.AddTableOfContentPage(TableOfContentItems, Destinations);
   PsFile.InsertNamedDestination("TableOfContentPage");
   PsFile.SetAutomaticHomeButton(true, "TableOfContentPage");

   HMRVsR.Scale(CrossSection * Luminosity / EntryCount);
   PsFile.AddPlot(HMRVsR, "colz", false, true);

   PsFile.AddTextPage("Count distributions - single tag");
   PsFile.InsertNamedDestination("CountSingleTag");
   PsFile.AddPlot(HCountPassTCHEL, "", true);
   PsFile.AddPlot(HCountPassTCHEM, "", true);
   PsFile.AddPlot(HCountPassTCHET, "", true);
   PsFile.AddPlot(HCountPassTCHPL, "", true);
   PsFile.AddPlot(HCountPassTCHPM, "", true);
   PsFile.AddPlot(HCountPassTCHPT, "", true);
   
   PsFile.AddTextPage("Yield cutting on b-tagging - single tag");
   PsFile.InsertNamedDestination("YieldSingleTag");
   PsFile.AddPlot(HYieldPassTCHEL, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHEM, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHET, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHPL, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHPM, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHPT, "", true, false, true);
   
   PsFile.AddTextPage("Count distributions - double tag");
   PsFile.InsertNamedDestination("CountDoubleTag");
   PsFile.AddPlot(HCountPassTCHELTCHEL, "", true);
   PsFile.AddPlot(HCountPassTCHELTCHEM, "", true);
   PsFile.AddPlot(HCountPassTCHELTCHET, "", true);
   PsFile.AddPlot(HCountPassTCHELTCHPL, "", true);
   PsFile.AddPlot(HCountPassTCHELTCHPM, "", true);
   PsFile.AddPlot(HCountPassTCHELTCHPT, "", true);
   PsFile.AddPlot(HCountPassTCHEMTCHEM, "", true);
   PsFile.AddPlot(HCountPassTCHEMTCHET, "", true);
   PsFile.AddPlot(HCountPassTCHEMTCHPL, "", true);
   PsFile.AddPlot(HCountPassTCHEMTCHPM, "", true);
   PsFile.AddPlot(HCountPassTCHEMTCHPT, "", true);
   PsFile.AddPlot(HCountPassTCHETTCHET, "", true);
   PsFile.AddPlot(HCountPassTCHETTCHPL, "", true);
   PsFile.AddPlot(HCountPassTCHETTCHPM, "", true);
   PsFile.AddPlot(HCountPassTCHETTCHPT, "", true);
   PsFile.AddPlot(HCountPassTCHPLTCHPL, "", true);
   PsFile.AddPlot(HCountPassTCHPLTCHPM, "", true);
   PsFile.AddPlot(HCountPassTCHPLTCHPT, "", true);
   PsFile.AddPlot(HCountPassTCHPMTCHPM, "", true);
   PsFile.AddPlot(HCountPassTCHPMTCHPT, "", true);
   PsFile.AddPlot(HCountPassTCHPTTCHPT, "", true);

   PsFile.AddTextPage("Yield cutting on b-tag - double tags");
   PsFile.InsertNamedDestination("YieldDoubleTag");
   PsFile.AddPlot(HYieldPassTCHELTCHEL, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHELTCHEM, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHELTCHET, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHELTCHPL, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHELTCHPM, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHELTCHPT, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHEMTCHEM, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHEMTCHET, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHEMTCHPL, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHEMTCHPM, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHEMTCHPT, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHETTCHET, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHETTCHPL, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHETTCHPM, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHETTCHPT, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHPLTCHPL, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHPLTCHPM, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHPLTCHPT, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHPMTCHPM, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHPMTCHPT, "", true, false, true);
   PsFile.AddPlot(HYieldPassTCHPTTCHPT, "", true, false, true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

void Get1DCumulativeHistogram(TH1D &Source, TH1D &Destination)
{
   Destination.SetBinContent(Source.GetNbinsX(), Source.GetBinContent(Source.GetNbinsX()));
   for(int i = Destination.GetNbinsX() - 1; i >= 1; i--)
      Destination.SetBinContent(i, Destination.GetBinContent(i + 1) + Source.GetBinContent(i));
}

double DeterminePT(multimap<double, int, greater<double> > &List)
{
   if(List.size() > 0)
      return min(List.begin()->first, 199.9);
   return 0;
}

double DeterminePT(multimap<double, int, greater<double> > &List1, multimap<double, int, greater<double> > &List2)
{
   if(List1.size() == 0 || List2.size() == 0)
      return 0;

   if(List1.size() >= 1 && List2.size() >= 1 && List1.begin()->second != List2.begin()->second)
      return min(min(List1.begin()->first, List2.begin()->first), 199.9);
   
   if(List1.size() == 1 && List2.size() == 1 && List1.begin()->second == List2.begin()->second)
      return 0;

   if(List1.size() == 1 && List2.size() > 1)
      return min(min(List1.begin()->first, (++(List2.begin()))->first), 199.9);
   if(List1.size() > 1 && List2.size() == 1)
      return min(min((++(List1.begin()))->first, List2.begin()->first), 199.9);

   // otherwise: both lists have more than 1 entry, and the first entry is the same
   double Min1 = min(List1.begin()->first, (++(List2.begin()))->first);
   double Min2 = min((++(List1.begin()))->first, List2.begin()->first);
   return min(max(Min1, Min2), 199.9);
}




