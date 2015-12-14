#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"

#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

#include "ReadLQ3Tree.h"

int main();
void CheckSamples(string InputFile, string OutputBase);
void OverlayPlots(PsFileHelper &PsFile, TH1D &H10, TH1D &H12, TH1D &H14, TH1D &H16, TH1D &H18, TH1D &H20);
void RatioPlots(PsFileHelper &PsFile, TH1D &H10, TH1D &H12, TH1D &H14, TH1D &H16, TH1D &H18, TH1D &H20);

int main()
{
   SetStyle();

   // CheckSamples("Samples/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola_All.root", "DY50");
   CheckSamples("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar");
   CheckSamples("Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root", "WJets");

   return 0;
}

void CheckSamples(string InputFile, string OutputBase)
{
   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(InputFile.c_str());
   if(Tree.GetEntries() == 0)
      return;

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   
   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage("Changing lepton PT cut for sample " + OutputBase);
   
   vector<string> Explanations;
   Explanations.push_back("Start from MC sample");
   Explanations.push_back("As a baseline selection require at least 2 PF jets above 60 GeV/c");
   Explanations.push_back("Require exactly one tight muon and no electrons");
   Explanations.push_back("Mu star box treatment --- remove jets too close to muon");
   Explanations.push_back("      add it back to the MET");
   Explanations.push_back("");
   Explanations.push_back("Change muon PT threshold from 10, 11, .... to 20");
   Explanations.push_back("For each threshold, recalculate hemispheres and subsequently MR/R");
   Explanations.push_back("The MR/R are the old GammaMRStar (MR***) and RStar (R*)");
   Explanations.push_back("");
   Explanations.push_back("Compare R and MR distributions");
   PsFile.AddTextPage(Explanations);

   vector<string> Items, Destinations;

   Items.push_back("Individual plots - MR");
   Items.push_back("Individual plots - R");
   Items.push_back("Individual plots - MR (R > 0.2)");
   Items.push_back("Individual plots - MR (R > 0.3)");
   Items.push_back("Individual plots - MR (R > 0.4)");
   Items.push_back("Individual plots - MR (R > 0.5)");
   Items.push_back("Individual plots - R (MR > 200)");
   Items.push_back("Individual plots - R (MR > 300)");
   Items.push_back("Overlaid plots (only 10, 12, 14, 16, 18, 20 to avoid running out of color)");
   Items.push_back("Ratio to PT > 10 distribution");

   Destinations.push_back("IndividualMR");
   Destinations.push_back("IndividualR");
   Destinations.push_back("IndividualMR02");
   Destinations.push_back("IndividualMR03");
   Destinations.push_back("IndividualMR04");
   Destinations.push_back("IndividualMR05");
   Destinations.push_back("IndividualR200");
   Destinations.push_back("IndividualR300");
   Destinations.push_back("Overlay");
   Destinations.push_back("Ratio");

   PsFile.AddTableOfContentPage(Items, Destinations);
   PsFile.InsertNamedDestination("HomePage");
   PsFile.SetAutomaticHomeButton(true, "HomePage");

   TFile OutputFile(Form("%s.root", OutputBase.c_str()), "recreate");
   TTree OutputTree("MRTree", "MRTree");

   double TreeMR10, TreeR10;
   double TreeMR11, TreeR11;
   double TreeMR12, TreeR12;
   double TreeMR13, TreeR13;
   double TreeMR14, TreeR14;
   double TreeMR15, TreeR15;
   double TreeMR16, TreeR16;
   double TreeMR17, TreeR17;
   double TreeMR18, TreeR18;
   double TreeMR19, TreeR19;
   double TreeMR20, TreeR20;

   OutputTree.Branch("MR10", &TreeMR10, "MR10/D");
   OutputTree.Branch("MR11", &TreeMR11, "MR11/D");
   OutputTree.Branch("MR12", &TreeMR12, "MR12/D");
   OutputTree.Branch("MR13", &TreeMR13, "MR13/D");
   OutputTree.Branch("MR14", &TreeMR14, "MR14/D");
   OutputTree.Branch("MR15", &TreeMR15, "MR15/D");
   OutputTree.Branch("MR16", &TreeMR16, "MR16/D");
   OutputTree.Branch("MR17", &TreeMR17, "MR17/D");
   OutputTree.Branch("MR18", &TreeMR18, "MR18/D");
   OutputTree.Branch("MR19", &TreeMR19, "MR19/D");
   OutputTree.Branch("MR20", &TreeMR20, "MR20/D");

   OutputTree.Branch("R10", &TreeR10, "R10/D");
   OutputTree.Branch("R11", &TreeR11, "R11/D");
   OutputTree.Branch("R12", &TreeR12, "R12/D");
   OutputTree.Branch("R13", &TreeR13, "R13/D");
   OutputTree.Branch("R14", &TreeR14, "R14/D");
   OutputTree.Branch("R15", &TreeR15, "R15/D");
   OutputTree.Branch("R16", &TreeR16, "R16/D");
   OutputTree.Branch("R17", &TreeR17, "R17/D");
   OutputTree.Branch("R18", &TreeR18, "R18/D");
   OutputTree.Branch("R19", &TreeR19, "R19/D");
   OutputTree.Branch("R20", &TreeR20, "R20/D");

   TH1D HMR_10("HMR_10", "MR distribution, lepton threshold 10 GeV;MR", 40, 0, 1000);
   TH1D HMR_11("HMR_11", "MR distribution, lepton threshold 11 GeV;MR", 40, 0, 1000);
   TH1D HMR_12("HMR_12", "MR distribution, lepton threshold 12 GeV;MR", 40, 0, 1000);
   TH1D HMR_13("HMR_13", "MR distribution, lepton threshold 13 GeV;MR", 40, 0, 1000);
   TH1D HMR_14("HMR_14", "MR distribution, lepton threshold 14 GeV;MR", 40, 0, 1000);
   TH1D HMR_15("HMR_15", "MR distribution, lepton threshold 15 GeV;MR", 40, 0, 1000);
   TH1D HMR_16("HMR_16", "MR distribution, lepton threshold 16 GeV;MR", 40, 0, 1000);
   TH1D HMR_17("HMR_17", "MR distribution, lepton threshold 17 GeV;MR", 40, 0, 1000);
   TH1D HMR_18("HMR_18", "MR distribution, lepton threshold 18 GeV;MR", 40, 0, 1000);
   TH1D HMR_19("HMR_19", "MR distribution, lepton threshold 19 GeV;MR", 40, 0, 1000);
   TH1D HMR_20("HMR_20", "MR distribution, lepton threshold 20 GeV;MR", 40, 0, 1000);

   TH1D HR_10("HR_10", "R distribution, lepton threshold 10 GeV;R", 40, 0, 1);
   TH1D HR_11("HR_11", "R distribution, lepton threshold 11 GeV;R", 40, 0, 1);
   TH1D HR_12("HR_12", "R distribution, lepton threshold 12 GeV;R", 40, 0, 1);
   TH1D HR_13("HR_13", "R distribution, lepton threshold 13 GeV;R", 40, 0, 1);
   TH1D HR_14("HR_14", "R distribution, lepton threshold 14 GeV;R", 40, 0, 1);
   TH1D HR_15("HR_15", "R distribution, lepton threshold 15 GeV;R", 40, 0, 1);
   TH1D HR_16("HR_16", "R distribution, lepton threshold 16 GeV;R", 40, 0, 1);
   TH1D HR_17("HR_17", "R distribution, lepton threshold 17 GeV;R", 40, 0, 1);
   TH1D HR_18("HR_18", "R distribution, lepton threshold 18 GeV;R", 40, 0, 1);
   TH1D HR_19("HR_19", "R distribution, lepton threshold 19 GeV;R", 40, 0, 1);
   TH1D HR_20("HR_20", "R distribution, lepton threshold 20 GeV;R", 40, 0, 1);

   TH1D HMR_R02_10("HMR_R02_10", "MR distribution (R > 0.2), lepton threshold 10 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_11("HMR_R02_11", "MR distribution (R > 0.2), lepton threshold 11 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_12("HMR_R02_12", "MR distribution (R > 0.2), lepton threshold 12 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_13("HMR_R02_13", "MR distribution (R > 0.2), lepton threshold 13 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_14("HMR_R02_14", "MR distribution (R > 0.2), lepton threshold 14 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_15("HMR_R02_15", "MR distribution (R > 0.2), lepton threshold 15 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_16("HMR_R02_16", "MR distribution (R > 0.2), lepton threshold 16 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_17("HMR_R02_17", "MR distribution (R > 0.2), lepton threshold 17 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_18("HMR_R02_18", "MR distribution (R > 0.2), lepton threshold 18 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_19("HMR_R02_19", "MR distribution (R > 0.2), lepton threshold 19 GeV;MR", 40, 0, 1000);
   TH1D HMR_R02_20("HMR_R02_20", "MR distribution (R > 0.2), lepton threshold 20 GeV;MR", 40, 0, 1000);

   TH1D HMR_R03_10("HMR_R03_10", "MR distribution (R > 0.3), lepton threshold 10 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_11("HMR_R03_11", "MR distribution (R > 0.3), lepton threshold 11 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_12("HMR_R03_12", "MR distribution (R > 0.3), lepton threshold 12 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_13("HMR_R03_13", "MR distribution (R > 0.3), lepton threshold 13 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_14("HMR_R03_14", "MR distribution (R > 0.3), lepton threshold 14 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_15("HMR_R03_15", "MR distribution (R > 0.3), lepton threshold 15 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_16("HMR_R03_16", "MR distribution (R > 0.3), lepton threshold 16 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_17("HMR_R03_17", "MR distribution (R > 0.3), lepton threshold 17 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_18("HMR_R03_18", "MR distribution (R > 0.3), lepton threshold 18 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_19("HMR_R03_19", "MR distribution (R > 0.3), lepton threshold 19 GeV;MR", 40, 0, 1000);
   TH1D HMR_R03_20("HMR_R03_20", "MR distribution (R > 0.3), lepton threshold 20 GeV;MR", 40, 0, 1000);

   TH1D HMR_R04_10("HMR_R04_10", "MR distribution (R > 0.4), lepton threshold 10 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_11("HMR_R04_11", "MR distribution (R > 0.4), lepton threshold 11 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_12("HMR_R04_12", "MR distribution (R > 0.4), lepton threshold 12 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_13("HMR_R04_13", "MR distribution (R > 0.4), lepton threshold 13 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_14("HMR_R04_14", "MR distribution (R > 0.4), lepton threshold 14 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_15("HMR_R04_15", "MR distribution (R > 0.4), lepton threshold 15 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_16("HMR_R04_16", "MR distribution (R > 0.4), lepton threshold 16 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_17("HMR_R04_17", "MR distribution (R > 0.4), lepton threshold 17 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_18("HMR_R04_18", "MR distribution (R > 0.4), lepton threshold 18 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_19("HMR_R04_19", "MR distribution (R > 0.4), lepton threshold 19 GeV;MR", 40, 0, 1000);
   TH1D HMR_R04_20("HMR_R04_20", "MR distribution (R > 0.4), lepton threshold 20 GeV;MR", 40, 0, 1000);

   TH1D HMR_R05_10("HMR_R05_10", "MR distribution (R > 0.5), lepton threshold 10 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_11("HMR_R05_11", "MR distribution (R > 0.5), lepton threshold 11 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_12("HMR_R05_12", "MR distribution (R > 0.5), lepton threshold 12 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_13("HMR_R05_13", "MR distribution (R > 0.5), lepton threshold 13 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_14("HMR_R05_14", "MR distribution (R > 0.5), lepton threshold 14 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_15("HMR_R05_15", "MR distribution (R > 0.5), lepton threshold 15 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_16("HMR_R05_16", "MR distribution (R > 0.5), lepton threshold 16 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_17("HMR_R05_17", "MR distribution (R > 0.5), lepton threshold 17 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_18("HMR_R05_18", "MR distribution (R > 0.5), lepton threshold 18 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_19("HMR_R05_19", "MR distribution (R > 0.5), lepton threshold 19 GeV;MR", 40, 0, 1000);
   TH1D HMR_R05_20("HMR_R05_20", "MR distribution (R > 0.5), lepton threshold 20 GeV;MR", 40, 0, 1000);

   TH1D HR_MR200_10("HR_MR200_10", "R distribution (MR > 200), lepton threshold 10 GeV;R", 40, 0, 1);
   TH1D HR_MR200_11("HR_MR200_11", "R distribution (MR > 200), lepton threshold 11 GeV;R", 40, 0, 1);
   TH1D HR_MR200_12("HR_MR200_12", "R distribution (MR > 200), lepton threshold 12 GeV;R", 40, 0, 1);
   TH1D HR_MR200_13("HR_MR200_13", "R distribution (MR > 200), lepton threshold 13 GeV;R", 40, 0, 1);
   TH1D HR_MR200_14("HR_MR200_14", "R distribution (MR > 200), lepton threshold 14 GeV;R", 40, 0, 1);
   TH1D HR_MR200_15("HR_MR200_15", "R distribution (MR > 200), lepton threshold 15 GeV;R", 40, 0, 1);
   TH1D HR_MR200_16("HR_MR200_16", "R distribution (MR > 200), lepton threshold 16 GeV;R", 40, 0, 1);
   TH1D HR_MR200_17("HR_MR200_17", "R distribution (MR > 200), lepton threshold 17 GeV;R", 40, 0, 1);
   TH1D HR_MR200_18("HR_MR200_18", "R distribution (MR > 200), lepton threshold 18 GeV;R", 40, 0, 1);
   TH1D HR_MR200_19("HR_MR200_19", "R distribution (MR > 200), lepton threshold 19 GeV;R", 40, 0, 1);
   TH1D HR_MR200_20("HR_MR200_20", "R distribution (MR > 200), lepton threshold 20 GeV;R", 40, 0, 1);

   TH1D HR_MR300_10("HR_MR300_10", "R distribution (MR > 300), lepton threshold 10 GeV;R", 40, 0, 1);
   TH1D HR_MR300_11("HR_MR300_11", "R distribution (MR > 300), lepton threshold 11 GeV;R", 40, 0, 1);
   TH1D HR_MR300_12("HR_MR300_12", "R distribution (MR > 300), lepton threshold 12 GeV;R", 40, 0, 1);
   TH1D HR_MR300_13("HR_MR300_13", "R distribution (MR > 300), lepton threshold 13 GeV;R", 40, 0, 1);
   TH1D HR_MR300_14("HR_MR300_14", "R distribution (MR > 300), lepton threshold 14 GeV;R", 40, 0, 1);
   TH1D HR_MR300_15("HR_MR300_15", "R distribution (MR > 300), lepton threshold 15 GeV;R", 40, 0, 1);
   TH1D HR_MR300_16("HR_MR300_16", "R distribution (MR > 300), lepton threshold 16 GeV;R", 40, 0, 1);
   TH1D HR_MR300_17("HR_MR300_17", "R distribution (MR > 300), lepton threshold 17 GeV;R", 40, 0, 1);
   TH1D HR_MR300_18("HR_MR300_18", "R distribution (MR > 300), lepton threshold 18 GeV;R", 40, 0, 1);
   TH1D HR_MR300_19("HR_MR300_19", "R distribution (MR > 300), lepton threshold 19 GeV;R", 40, 0, 1);
   TH1D HR_MR300_20("HR_MR300_20", "R distribution (MR > 300), lepton threshold 20 GeV;R", 40, 0, 1);

   int NumberOfEntries = Tree.GetEntries();
   for(int iEntry = 0; iEntry < NumberOfEntries; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing " << iEntry + 1 << "-th entry out of total " << NumberOfEntries << " entries" << endl;

      Tree.GetEntry(iEntry);

      int JetCount60 = 0;
      for(int i = 0; i < M.PFJetCount; i++)
      {
         if(M.PFJetPT[i] < 60)
            continue;
         if(M.PFJetEta[i] < -3 || M.PFJetEta[i] > 3)
            continue;

         JetCount60 = JetCount60 + 1;
      }
      if(JetCount60 < 2)   // guu
         continue;

      // single-muon only for simplicity
      if(M.GoodMuonCountTight != 1 && (M.GoodElectronCount80 != 0 && M.Electron1PT > 20))
         continue;
      if(M.Muon1PT < 10)   // too small for any threshold we're considering!
         continue;
      FourVector MuonP;
      MuonP.SetPtEtaPhiMass(M.Muon1PT, M.Muon1Eta, M.Muon1Phi, 0.1);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      PFMET = PFMET + MuonP;

      vector<FourVector> GoodJets10;
      vector<FourVector> GoodJets11;
      vector<FourVector> GoodJets12;
      vector<FourVector> GoodJets13;
      vector<FourVector> GoodJets14;
      vector<FourVector> GoodJets15;
      vector<FourVector> GoodJets16;
      vector<FourVector> GoodJets17;
      vector<FourVector> GoodJets18;
      vector<FourVector> GoodJets19;
      vector<FourVector> GoodJets20;
      for(int i = 0; i < M.PFJetCount; i++)
      {
         if(M.PFJetPT[i] < 30)
            continue;
         if(M.PFJetEta[i] < -3 || M.PFJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.PFJetPT[i], M.PFJetEta[i], M.PFJetPhi[i]);

         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 10)
            GoodJets10.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 11)
            GoodJets11.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 12)
            GoodJets12.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 13)
            GoodJets13.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 14)
            GoodJets14.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 15)
            GoodJets15.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 16)
            GoodJets16.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 17)
            GoodJets17.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 18)
            GoodJets18.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 19)
            GoodJets19.push_back(NewJet);
         if(GetDR(NewJet, MuonP) >= 0.3 && MuonP.GetPT() > 20)
            GoodJets20.push_back(NewJet);
      }

      vector<FourVector> Hemispheres10;
      vector<FourVector> Hemispheres11;
      vector<FourVector> Hemispheres12;
      vector<FourVector> Hemispheres13;
      vector<FourVector> Hemispheres14;
      vector<FourVector> Hemispheres15;
      vector<FourVector> Hemispheres16;
      vector<FourVector> Hemispheres17;
      vector<FourVector> Hemispheres18;
      vector<FourVector> Hemispheres19;
      vector<FourVector> Hemispheres20;

      if(GoodJets10.size() >= 2 && GoodJets10.size() < 20 && MuonP.GetPT() > 10)
         Hemispheres10 = SplitIntoGroups(GoodJets10, true);
      if(GoodJets11.size() >= 2 && GoodJets11.size() < 20 && MuonP.GetPT() > 11)
         Hemispheres11 = SplitIntoGroups(GoodJets11, true);
      if(GoodJets12.size() >= 2 && GoodJets12.size() < 20 && MuonP.GetPT() > 12)
         Hemispheres12 = SplitIntoGroups(GoodJets12, true);
      if(GoodJets13.size() >= 2 && GoodJets13.size() < 20 && MuonP.GetPT() > 13)
         Hemispheres13 = SplitIntoGroups(GoodJets13, true);
      if(GoodJets14.size() >= 2 && GoodJets14.size() < 20 && MuonP.GetPT() > 14)
         Hemispheres14 = SplitIntoGroups(GoodJets14, true);
      if(GoodJets15.size() >= 2 && GoodJets15.size() < 20 && MuonP.GetPT() > 15)
         Hemispheres15 = SplitIntoGroups(GoodJets15, true);
      if(GoodJets16.size() >= 2 && GoodJets16.size() < 20 && MuonP.GetPT() > 16)
         Hemispheres16 = SplitIntoGroups(GoodJets16, true);
      if(GoodJets17.size() >= 2 && GoodJets17.size() < 20 && MuonP.GetPT() > 17)
         Hemispheres17 = SplitIntoGroups(GoodJets17, true);
      if(GoodJets18.size() >= 2 && GoodJets18.size() < 20 && MuonP.GetPT() > 18)
         Hemispheres18 = SplitIntoGroups(GoodJets18, true);
      if(GoodJets19.size() >= 2 && GoodJets19.size() < 20 && MuonP.GetPT() > 19)
         Hemispheres19 = SplitIntoGroups(GoodJets19, true);
      if(GoodJets20.size() >= 2 && GoodJets20.size() < 20 && MuonP.GetPT() > 20)
         Hemispheres20 = SplitIntoGroups(GoodJets20, true);

      double MR10 = -1000;   // these are gamma mr stars and r stars
      double MR11 = -1000;
      double MR12 = -1000;
      double MR13 = -1000;
      double MR14 = -1000;
      double MR15 = -1000;
      double MR16 = -1000;
      double MR17 = -1000;
      double MR18 = -1000;
      double MR19 = -1000;
      double MR20 = -1000;

      double R10 = -1000;
      double R11 = -1000;
      double R12 = -1000;
      double R13 = -1000;
      double R14 = -1000;
      double R15 = -1000;
      double R16 = -1000;
      double R17 = -1000;
      double R18 = -1000;
      double R19 = -1000;
      double R20 = -1000;

      if(Hemispheres10.size() == 2)
      {
         MR10 = GetMRStar(Hemispheres10[0], Hemispheres10[1]) * GetGammaRStar(Hemispheres10[0], Hemispheres10[1]);
         R10 = GetRStar(Hemispheres10[0], Hemispheres10[1], PFMET);
      }
      if(Hemispheres11.size() == 2)
      {
         MR11 = GetMRStar(Hemispheres11[0], Hemispheres11[1]) * GetGammaRStar(Hemispheres11[0], Hemispheres11[1]);
         R11 = GetRStar(Hemispheres11[0], Hemispheres11[1], PFMET);
      }
      if(Hemispheres12.size() == 2)
      {
         MR12 = GetMRStar(Hemispheres12[0], Hemispheres12[1]) * GetGammaRStar(Hemispheres12[0], Hemispheres12[1]);
         R12 = GetRStar(Hemispheres12[0], Hemispheres12[1], PFMET);
      }
      if(Hemispheres13.size() == 2)
      {
         MR13 = GetMRStar(Hemispheres13[0], Hemispheres13[1]) * GetGammaRStar(Hemispheres13[0], Hemispheres13[1]);
         R13 = GetRStar(Hemispheres13[0], Hemispheres13[1], PFMET);
      }
      if(Hemispheres14.size() == 2)
      {
         MR14 = GetMRStar(Hemispheres14[0], Hemispheres14[1]) * GetGammaRStar(Hemispheres14[0], Hemispheres14[1]);
         R14 = GetRStar(Hemispheres14[0], Hemispheres14[1], PFMET);
      }
      if(Hemispheres15.size() == 2)
      {
         MR15 = GetMRStar(Hemispheres15[0], Hemispheres15[1]) * GetGammaRStar(Hemispheres15[0], Hemispheres15[1]);
         R15 = GetRStar(Hemispheres15[0], Hemispheres15[1], PFMET);
      }
      if(Hemispheres16.size() == 2)
      {
         MR16 = GetMRStar(Hemispheres16[0], Hemispheres16[1]) * GetGammaRStar(Hemispheres16[0], Hemispheres16[1]);
         R16 = GetRStar(Hemispheres16[0], Hemispheres16[1], PFMET);
      }
      if(Hemispheres17.size() == 2)
      {
         MR17 = GetMRStar(Hemispheres17[0], Hemispheres17[1]) * GetGammaRStar(Hemispheres17[0], Hemispheres17[1]);
         R17 = GetRStar(Hemispheres17[0], Hemispheres17[1], PFMET);
      }
      if(Hemispheres18.size() == 2)
      {
         MR18 = GetMRStar(Hemispheres18[0], Hemispheres18[1]) * GetGammaRStar(Hemispheres18[0], Hemispheres18[1]);
         R18 = GetRStar(Hemispheres18[0], Hemispheres18[1], PFMET);
      }
      if(Hemispheres19.size() == 2)
      {
         MR19 = GetMRStar(Hemispheres19[0], Hemispheres19[1]) * GetGammaRStar(Hemispheres19[0], Hemispheres19[1]);
         R19 = GetRStar(Hemispheres19[0], Hemispheres19[1], PFMET);
      }
      if(Hemispheres20.size() == 2)
      {
         MR20 = GetMRStar(Hemispheres20[0], Hemispheres20[1]) * GetGammaRStar(Hemispheres20[0], Hemispheres20[1]);
         R20 = GetRStar(Hemispheres20[0], Hemispheres20[1], PFMET);
      }

      HMR_10.Fill(MR10);
      HMR_11.Fill(MR11);
      HMR_12.Fill(MR12);
      HMR_13.Fill(MR13);
      HMR_14.Fill(MR14);
      HMR_15.Fill(MR15);
      HMR_16.Fill(MR16);
      HMR_17.Fill(MR17);
      HMR_18.Fill(MR18);
      HMR_19.Fill(MR19);
      HMR_20.Fill(MR20);

      HR_10.Fill(R10);
      HR_11.Fill(R11);
      HR_12.Fill(R12);
      HR_13.Fill(R13);
      HR_14.Fill(R14);
      HR_15.Fill(R15);
      HR_16.Fill(R16);
      HR_17.Fill(R17);
      HR_18.Fill(R18);
      HR_19.Fill(R19);
      HR_20.Fill(R20);

      if(R10 > 0.2)   HMR_R02_10.Fill(MR10);
      if(R11 > 0.2)   HMR_R02_11.Fill(MR11);
      if(R12 > 0.2)   HMR_R02_12.Fill(MR12);
      if(R13 > 0.2)   HMR_R02_13.Fill(MR13);
      if(R14 > 0.2)   HMR_R02_14.Fill(MR14);
      if(R15 > 0.2)   HMR_R02_15.Fill(MR15);
      if(R16 > 0.2)   HMR_R02_16.Fill(MR16);
      if(R17 > 0.2)   HMR_R02_17.Fill(MR17);
      if(R18 > 0.2)   HMR_R02_18.Fill(MR18);
      if(R19 > 0.2)   HMR_R02_19.Fill(MR19);
      if(R20 > 0.2)   HMR_R02_20.Fill(MR20);

      if(R10 > 0.3)   HMR_R03_10.Fill(MR10);
      if(R11 > 0.3)   HMR_R03_11.Fill(MR11);
      if(R12 > 0.3)   HMR_R03_12.Fill(MR12);
      if(R13 > 0.3)   HMR_R03_13.Fill(MR13);
      if(R14 > 0.3)   HMR_R03_14.Fill(MR14);
      if(R15 > 0.3)   HMR_R03_15.Fill(MR15);
      if(R16 > 0.3)   HMR_R03_16.Fill(MR16);
      if(R17 > 0.3)   HMR_R03_17.Fill(MR17);
      if(R18 > 0.3)   HMR_R03_18.Fill(MR18);
      if(R19 > 0.3)   HMR_R03_19.Fill(MR19);
      if(R20 > 0.3)   HMR_R03_20.Fill(MR20);

      if(R10 > 0.4)   HMR_R04_10.Fill(MR10);
      if(R11 > 0.4)   HMR_R04_11.Fill(MR11);
      if(R12 > 0.4)   HMR_R04_12.Fill(MR12);
      if(R13 > 0.4)   HMR_R04_13.Fill(MR13);
      if(R14 > 0.4)   HMR_R04_14.Fill(MR14);
      if(R15 > 0.4)   HMR_R04_15.Fill(MR15);
      if(R16 > 0.4)   HMR_R04_16.Fill(MR16);
      if(R17 > 0.4)   HMR_R04_17.Fill(MR17);
      if(R18 > 0.4)   HMR_R04_18.Fill(MR18);
      if(R19 > 0.4)   HMR_R04_19.Fill(MR19);
      if(R20 > 0.4)   HMR_R04_20.Fill(MR20);

      if(R10 > 0.5)   HMR_R05_10.Fill(MR10);
      if(R11 > 0.5)   HMR_R05_11.Fill(MR11);
      if(R12 > 0.5)   HMR_R05_12.Fill(MR12);
      if(R13 > 0.5)   HMR_R05_13.Fill(MR13);
      if(R14 > 0.5)   HMR_R05_14.Fill(MR14);
      if(R15 > 0.5)   HMR_R05_15.Fill(MR15);
      if(R16 > 0.5)   HMR_R05_16.Fill(MR16);
      if(R17 > 0.5)   HMR_R05_17.Fill(MR17);
      if(R18 > 0.5)   HMR_R05_18.Fill(MR18);
      if(R19 > 0.5)   HMR_R05_19.Fill(MR19);
      if(R20 > 0.5)   HMR_R05_20.Fill(MR20);

      if(MR10 > 200)   HR_MR200_10.Fill(R10);
      if(MR11 > 200)   HR_MR200_11.Fill(R11);
      if(MR12 > 200)   HR_MR200_12.Fill(R12);
      if(MR13 > 200)   HR_MR200_13.Fill(R13);
      if(MR14 > 200)   HR_MR200_14.Fill(R14);
      if(MR15 > 200)   HR_MR200_15.Fill(R15);
      if(MR16 > 200)   HR_MR200_16.Fill(R16);
      if(MR17 > 200)   HR_MR200_17.Fill(R17);
      if(MR18 > 200)   HR_MR200_18.Fill(R18);
      if(MR19 > 200)   HR_MR200_19.Fill(R19);
      if(MR20 > 200)   HR_MR200_20.Fill(R20);

      if(MR10 > 300)   HR_MR300_10.Fill(R10);
      if(MR11 > 300)   HR_MR300_11.Fill(R11);
      if(MR12 > 300)   HR_MR300_12.Fill(R12);
      if(MR13 > 300)   HR_MR300_13.Fill(R13);
      if(MR14 > 300)   HR_MR300_14.Fill(R14);
      if(MR15 > 300)   HR_MR300_15.Fill(R15);
      if(MR16 > 300)   HR_MR300_16.Fill(R16);
      if(MR17 > 300)   HR_MR300_17.Fill(R17);
      if(MR18 > 300)   HR_MR300_18.Fill(R18);
      if(MR19 > 300)   HR_MR300_19.Fill(R19);
      if(MR20 > 300)   HR_MR300_20.Fill(R20);

      TreeMR10 = MR10;
      TreeMR11 = MR11;
      TreeMR12 = MR12;
      TreeMR13 = MR13;
      TreeMR14 = MR14;
      TreeMR15 = MR15;
      TreeMR16 = MR16;
      TreeMR17 = MR17;
      TreeMR18 = MR18;
      TreeMR19 = MR19;
      TreeMR20 = MR20;

      TreeR10 = R10;
      TreeR11 = R11;
      TreeR12 = R12;
      TreeR13 = R13;
      TreeR14 = R14;
      TreeR15 = R15;
      TreeR16 = R16;
      TreeR17 = R17;
      TreeR18 = R18;
      TreeR19 = R19;
      TreeR20 = R20;

      OutputTree.Fill();
   }

   OutputTree.Write();

   HMR_10.Write();
   HMR_11.Write();
   HMR_12.Write();
   HMR_13.Write();
   HMR_14.Write();
   HMR_15.Write();
   HMR_16.Write();
   HMR_17.Write();
   HMR_18.Write();
   HMR_19.Write();
   HMR_20.Write();

   HR_10.Write();
   HR_11.Write();
   HR_12.Write();
   HR_13.Write();
   HR_14.Write();
   HR_15.Write();
   HR_16.Write();
   HR_17.Write();
   HR_18.Write();
   HR_19.Write();
   HR_20.Write();

   HMR_R02_10.Write();
   HMR_R02_11.Write();
   HMR_R02_12.Write();
   HMR_R02_13.Write();
   HMR_R02_14.Write();
   HMR_R02_15.Write();
   HMR_R02_16.Write();
   HMR_R02_17.Write();
   HMR_R02_18.Write();
   HMR_R02_19.Write();
   HMR_R02_20.Write();

   HMR_R03_10.Write();
   HMR_R03_11.Write();
   HMR_R03_12.Write();
   HMR_R03_13.Write();
   HMR_R03_14.Write();
   HMR_R03_15.Write();
   HMR_R03_16.Write();
   HMR_R03_17.Write();
   HMR_R03_18.Write();
   HMR_R03_19.Write();
   HMR_R03_20.Write();

   HMR_R04_10.Write();
   HMR_R04_11.Write();
   HMR_R04_12.Write();
   HMR_R04_13.Write();
   HMR_R04_14.Write();
   HMR_R04_15.Write();
   HMR_R04_16.Write();
   HMR_R04_17.Write();
   HMR_R04_18.Write();
   HMR_R04_19.Write();
   HMR_R04_20.Write();

   HMR_R05_10.Write();
   HMR_R05_11.Write();
   HMR_R05_12.Write();
   HMR_R05_13.Write();
   HMR_R05_14.Write();
   HMR_R05_15.Write();
   HMR_R05_16.Write();
   HMR_R05_17.Write();
   HMR_R05_18.Write();
   HMR_R05_19.Write();
   HMR_R05_20.Write();

   HR_MR200_10.Write();
   HR_MR200_11.Write();
   HR_MR200_12.Write();
   HR_MR200_13.Write();
   HR_MR200_14.Write();
   HR_MR200_15.Write();
   HR_MR200_16.Write();
   HR_MR200_17.Write();
   HR_MR200_18.Write();
   HR_MR200_19.Write();
   HR_MR200_20.Write();

   HR_MR300_10.Write();
   HR_MR300_11.Write();
   HR_MR300_12.Write();
   HR_MR300_13.Write();
   HR_MR300_14.Write();
   HR_MR300_15.Write();
   HR_MR300_16.Write();
   HR_MR300_17.Write();
   HR_MR300_18.Write();
   HR_MR300_19.Write();
   HR_MR300_20.Write();

   PsFile.AddTextPage("IndividualPlots");

   PsFile.AddTextPage("MR");
   PsFile.InsertNamedDestination("IndividualMR");
   PsFile.AddPlot(HMR_10, "", true);
   PsFile.AddPlot(HMR_11, "", true);
   PsFile.AddPlot(HMR_12, "", true);
   PsFile.AddPlot(HMR_13, "", true);
   PsFile.AddPlot(HMR_14, "", true);
   PsFile.AddPlot(HMR_15, "", true);
   PsFile.AddPlot(HMR_16, "", true);
   PsFile.AddPlot(HMR_17, "", true);
   PsFile.AddPlot(HMR_18, "", true);
   PsFile.AddPlot(HMR_19, "", true);
   PsFile.AddPlot(HMR_20, "", true);

   PsFile.AddTextPage("R");
   PsFile.InsertNamedDestination("IndividualR");
   PsFile.AddPlot(HR_10, "", true);
   PsFile.AddPlot(HR_11, "", true);
   PsFile.AddPlot(HR_12, "", true);
   PsFile.AddPlot(HR_13, "", true);
   PsFile.AddPlot(HR_14, "", true);
   PsFile.AddPlot(HR_15, "", true);
   PsFile.AddPlot(HR_16, "", true);
   PsFile.AddPlot(HR_17, "", true);
   PsFile.AddPlot(HR_18, "", true);
   PsFile.AddPlot(HR_19, "", true);
   PsFile.AddPlot(HR_20, "", true);

   PsFile.AddTextPage("MR, R > 0.2");
   PsFile.InsertNamedDestination("IndividualMR02");
   PsFile.AddPlot(HMR_R02_10, "", true);
   PsFile.AddPlot(HMR_R02_11, "", true);
   PsFile.AddPlot(HMR_R02_12, "", true);
   PsFile.AddPlot(HMR_R02_13, "", true);
   PsFile.AddPlot(HMR_R02_14, "", true);
   PsFile.AddPlot(HMR_R02_15, "", true);
   PsFile.AddPlot(HMR_R02_16, "", true);
   PsFile.AddPlot(HMR_R02_17, "", true);
   PsFile.AddPlot(HMR_R02_18, "", true);
   PsFile.AddPlot(HMR_R02_19, "", true);
   PsFile.AddPlot(HMR_R02_20, "", true);

   PsFile.AddTextPage("MR, R > 0.3");
   PsFile.InsertNamedDestination("IndividualMR03");
   PsFile.AddPlot(HMR_R03_10, "", true);
   PsFile.AddPlot(HMR_R03_11, "", true);
   PsFile.AddPlot(HMR_R03_12, "", true);
   PsFile.AddPlot(HMR_R03_13, "", true);
   PsFile.AddPlot(HMR_R03_14, "", true);
   PsFile.AddPlot(HMR_R03_15, "", true);
   PsFile.AddPlot(HMR_R03_16, "", true);
   PsFile.AddPlot(HMR_R03_17, "", true);
   PsFile.AddPlot(HMR_R03_18, "", true);
   PsFile.AddPlot(HMR_R03_19, "", true);
   PsFile.AddPlot(HMR_R03_20, "", true);

   PsFile.AddTextPage("MR, R > 0.4");
   PsFile.InsertNamedDestination("IndividualMR04");
   PsFile.AddPlot(HMR_R04_10, "", true);
   PsFile.AddPlot(HMR_R04_11, "", true);
   PsFile.AddPlot(HMR_R04_12, "", true);
   PsFile.AddPlot(HMR_R04_13, "", true);
   PsFile.AddPlot(HMR_R04_14, "", true);
   PsFile.AddPlot(HMR_R04_15, "", true);
   PsFile.AddPlot(HMR_R04_16, "", true);
   PsFile.AddPlot(HMR_R04_17, "", true);
   PsFile.AddPlot(HMR_R04_18, "", true);
   PsFile.AddPlot(HMR_R04_19, "", true);
   PsFile.AddPlot(HMR_R04_20, "", true);

   PsFile.AddTextPage("MR, R > 0.5");
   PsFile.InsertNamedDestination("IndividualMR05");
   PsFile.AddPlot(HMR_R05_10, "", true);
   PsFile.AddPlot(HMR_R05_11, "", true);
   PsFile.AddPlot(HMR_R05_12, "", true);
   PsFile.AddPlot(HMR_R05_13, "", true);
   PsFile.AddPlot(HMR_R05_14, "", true);
   PsFile.AddPlot(HMR_R05_15, "", true);
   PsFile.AddPlot(HMR_R05_16, "", true);
   PsFile.AddPlot(HMR_R05_17, "", true);
   PsFile.AddPlot(HMR_R05_18, "", true);
   PsFile.AddPlot(HMR_R05_19, "", true);
   PsFile.AddPlot(HMR_R05_20, "", true);

   PsFile.AddTextPage("R, MR > 200");
   PsFile.InsertNamedDestination("IndividualR200");
   PsFile.AddPlot(HR_MR200_10, "", true);
   PsFile.AddPlot(HR_MR200_11, "", true);
   PsFile.AddPlot(HR_MR200_12, "", true);
   PsFile.AddPlot(HR_MR200_13, "", true);
   PsFile.AddPlot(HR_MR200_14, "", true);
   PsFile.AddPlot(HR_MR200_15, "", true);
   PsFile.AddPlot(HR_MR200_16, "", true);
   PsFile.AddPlot(HR_MR200_17, "", true);
   PsFile.AddPlot(HR_MR200_18, "", true);
   PsFile.AddPlot(HR_MR200_19, "", true);
   PsFile.AddPlot(HR_MR200_20, "", true);

   PsFile.AddTextPage("R, MR > 300");
   PsFile.InsertNamedDestination("IndividualR300");
   PsFile.AddPlot(HR_MR300_10, "", true);
   PsFile.AddPlot(HR_MR300_11, "", true);
   PsFile.AddPlot(HR_MR300_12, "", true);
   PsFile.AddPlot(HR_MR300_13, "", true);
   PsFile.AddPlot(HR_MR300_14, "", true);
   PsFile.AddPlot(HR_MR300_15, "", true);
   PsFile.AddPlot(HR_MR300_16, "", true);
   PsFile.AddPlot(HR_MR300_17, "", true);
   PsFile.AddPlot(HR_MR300_18, "", true);
   PsFile.AddPlot(HR_MR300_19, "", true);
   PsFile.AddPlot(HR_MR300_20, "", true);

   PsFile.AddTextPage("Overlaid plots");
   PsFile.InsertNamedDestination("Overlay");
   OverlayPlots(PsFile, HMR_10, HMR_12, HMR_14, HMR_16, HMR_18, HMR_20);
   OverlayPlots(PsFile, HR_10, HR_12, HR_14, HR_16, HR_18, HR_20);
   OverlayPlots(PsFile, HMR_R02_10, HMR_R02_12, HMR_R02_14, HMR_R02_16, HMR_R02_18, HMR_R02_20);
   OverlayPlots(PsFile, HMR_R03_10, HMR_R03_12, HMR_R03_14, HMR_R03_16, HMR_R03_18, HMR_R03_20);
   OverlayPlots(PsFile, HMR_R04_10, HMR_R04_12, HMR_R04_14, HMR_R04_16, HMR_R04_18, HMR_R04_20);
   OverlayPlots(PsFile, HMR_R05_10, HMR_R05_12, HMR_R05_14, HMR_R05_16, HMR_R05_18, HMR_R05_20);
   OverlayPlots(PsFile, HR_MR200_10, HR_MR200_12, HR_MR200_14, HR_MR200_16, HR_MR200_18, HR_MR200_20);
   OverlayPlots(PsFile, HR_MR300_10, HR_MR300_12, HR_MR300_14, HR_MR300_16, HR_MR300_18, HR_MR300_20);

   PsFile.AddTextPage("Ratio plots");
   PsFile.InsertNamedDestination("Ratio");
   // RatioPlots(PsFile, HMR_10, HMR_12, HMR_14, HMR_16, HMR_18, HMR_20);
   // RatioPlots(PsFile, HR_10, HR_12, HR_14, HR_16, HR_18, HR_20);
   RatioPlots(PsFile, HMR_R02_10, HMR_R02_12, HMR_R02_14, HMR_R02_16, HMR_R02_18, HMR_R02_20);
   RatioPlots(PsFile, HMR_R03_10, HMR_R03_12, HMR_R03_14, HMR_R03_16, HMR_R03_18, HMR_R03_20);
   RatioPlots(PsFile, HMR_R04_10, HMR_R04_12, HMR_R04_14, HMR_R04_16, HMR_R04_18, HMR_R04_20);
   RatioPlots(PsFile, HMR_R05_10, HMR_R05_12, HMR_R05_14, HMR_R05_16, HMR_R05_18, HMR_R05_20);
   RatioPlots(PsFile, HR_MR200_10, HR_MR200_12, HR_MR200_14, HR_MR200_16, HR_MR200_18, HR_MR200_20);
   RatioPlots(PsFile, HR_MR300_10, HR_MR300_12, HR_MR300_14, HR_MR300_16, HR_MR300_18, HR_MR300_20);

   OutputTree.Write();
   OutputFile.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

void OverlayPlots(PsFileHelper &PsFile, TH1D &H10, TH1D &H12, TH1D &H14, TH1D &H16, TH1D &H18, TH1D &H20)
{
   H10.SetLineColor(1);
   H12.SetLineColor(2);
   H14.SetLineColor(3);
   H16.SetLineColor(4);
   H18.SetLineColor(5);
   H20.SetLineColor(6);

   H10.SetStats(0);
   H12.SetStats(0);
   H14.SetStats(0);
   H16.SetStats(0);
   H18.SetStats(0);
   H20.SetStats(0);

   TLegend legend(0.8, 0.95, 0.95, 0.65);
   legend.SetFillColor(0);
   legend.AddEntry(&H10, "PT > 10", "l");
   legend.AddEntry(&H12, "PT > 12", "l");
   legend.AddEntry(&H14, "PT > 14", "l");
   legend.AddEntry(&H16, "PT > 16", "l");
   legend.AddEntry(&H18, "PT > 18", "l");
   legend.AddEntry(&H20, "PT > 20", "l");

   TCanvas Canvas;
   H10.Draw();
   H12.Draw("same");
   H14.Draw("same");
   H16.Draw("same");
   H18.Draw("same");
   H20.Draw("same");
   legend.Draw();
   Canvas.SetLogy();
   PsFile.AddCanvas(Canvas);
}

void RatioPlots(PsFileHelper &PsFile, TH1D &H10, TH1D &H12, TH1D &H14, TH1D &H16, TH1D &H18, TH1D &H20)
{
   H10.Sumw2();
   H12.Sumw2();
   H14.Sumw2();
   H16.Sumw2();
   H18.Sumw2();
   H20.Sumw2();

   TH1D *Yay = (TH1D *)H10.Clone("Yay");
   Yay->SetMaximum(1.2);
   Yay->SetMinimum(0.5);
   Yay->SetLineColor(0);

   TGraphAsymmErrors G12, G14, G16, G18, G20;
   G12.Divide(&H12, &H10);
   G14.Divide(&H14, &H10);
   G16.Divide(&H16, &H10);
   G18.Divide(&H18, &H10);
   G20.Divide(&H20, &H10);

   G12.SetLineColor(2);
   G14.SetLineColor(3);
   G16.SetLineColor(4);
   G18.SetLineColor(5);
   G20.SetLineColor(6);

   TLegend legend(0.8, 0.95, 0.95, 0.75);
   legend.SetFillColor(0);
   legend.AddEntry(&G12, "(PT > 12) / (PT > 10)", "l");
   legend.AddEntry(&G14, "(PT > 14) / (PT > 10)", "l");
   legend.AddEntry(&G16, "(PT > 16) / (PT > 10)", "l");
   legend.AddEntry(&G18, "(PT > 18) / (PT > 10)", "l");
   legend.AddEntry(&G20, "(PT > 20) / (PT > 10)", "l");

   TCanvas Canvas;
   Yay->Draw();
   G12.Draw("pe");
   G14.Draw("pe");
   G16.Draw("pe");
   G18.Draw("pe");
   G20.Draw("pe");
   legend.Draw();
   PsFile.AddCanvas(Canvas);
}



