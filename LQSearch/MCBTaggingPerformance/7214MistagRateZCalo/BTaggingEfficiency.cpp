//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <sstream>
using namespace std;
//---------------------------------------------------------------------------
#include "fastjet/ClusterSequence.hh"
using namespace fastjet;
//---------------------------------------------------------------------------
#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TGraphAsymmErrors.h"
//---------------------------------------------------------------------------
#include "ChainAll.h"
#include "PlotHelper2.h"
#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "ReadNTPTree.h"
#include "Rebin.h"
#include "SetStyle.h"
#include "SlidePreparationHelper.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[]);
void BTaggingEfficiency(string InputList, double CutValue, string OutputBase, int PUMin = 0,
   int PUMax = 10000);
int FindChildIndex(NTPTreeMessenger &M, int ChildPDGID, int ParentPDGID);
int TraceBHadron(NTPTreeMessenger &M, int StartIndex);
bool HasB(int PDGID);
int FindClosestJet(float *JetCollectionEta, float *JetCollectionPhi, int JetCount, double Eta, double Phi);
bool IsGoodMuon(NTPTreeMessenger &M, int MuonIndex);
void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, bool LogY = false);
void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, TH1D *H3, bool LogY = false);
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   SetStyle();

   BTaggingEfficiency("ZJetsV4.list", 1.7, "ReproduceBTaggingEfficiencyPU_TCHEL");
   /*
   BTaggingEfficiency("ZJetsV4.list", 1.7, "ReproduceBTaggingEfficiencyPUSmall_TCHEL", 0, 4);
   BTaggingEfficiency("ZJetsV4.list", 1.7, "ReproduceBTaggingEfficiencyPUMedium_TCHEL", 5, 7);
   BTaggingEfficiency("ZJetsV4.list", 1.7, "ReproduceBTaggingEfficiencyPULarge_TCHEL", 8, 1000);
   */
   // BTaggingEfficiency("ZJetsV4.list", 3.3, "ReproduceBTaggingEfficiencyPU_TCHEM");
   // BTaggingEfficiency("ZJetsV4.list", 10.2, "ReproduceBTaggingEfficiencyPU_TCHET");
   /*
   BTaggingEfficiency("ZJetsV4.list", 10.2, "ReproduceBTaggingEfficiencyPUSmall_TCHET", 0, 4);
   BTaggingEfficiency("ZJetsV4.list", 10.2, "ReproduceBTaggingEfficiencyPUMedium_TCHET", 5, 7);
   BTaggingEfficiency("ZJetsV4.list", 10.2, "ReproduceBTaggingEfficiencyPULarge_TCHET", 8, 1000);
   */

   return 0;
}
//---------------------------------------------------------------------------
void BTaggingEfficiency(string InputList, double CutValue, string OutputBase, int PUMin, int PUMax)
{
   // Read inputs
   TChain *NTPTree = ChainAll(InputList, "ntp1");
   if(NTPTree == NULL)   // error!
      return;

   NTPTreeMessenger M;
   M.SetBranchAddress(NTPTree);

   NTPTree->SetBranchStatus("*", false);   // to speed things up
   NTPTree->SetBranchStatus("nAK5Jet", true);
   NTPTree->SetBranchStatus("etaAK5Jet", true);
   NTPTree->SetBranchStatus("phiAK5Jet", true);
   NTPTree->SetBranchStatus("energyAK5Jet", true);
   NTPTree->SetBranchStatus("pxAK5Jet", true);
   NTPTree->SetBranchStatus("pyAK5Jet", true);
   NTPTree->SetBranchStatus("pzAK5Jet", true);
   NTPTree->SetBranchStatus("nMc", true);
   NTPTree->SetBranchStatus("idMc", true);
   NTPTree->SetBranchStatus("pMc", true);
   NTPTree->SetBranchStatus("etaMc", true);
   NTPTree->SetBranchStatus("phiMc", true);
   NTPTree->SetBranchStatus("energyMc", true);
   NTPTree->SetBranchStatus("mothMc", true);
   NTPTree->SetBranchStatus("nPV", true);
   NTPTree->SetBranchStatus("ndofPV", true);
   NTPTree->SetBranchStatus("PVxPV", true);
   NTPTree->SetBranchStatus("PVyPV", true);
   NTPTree->SetBranchStatus("PVzPV", true);
   NTPTree->SetBranchStatus("SumPtPV", true);
   NTPTree->SetBranchStatus("trackCountingHighEffBJetTagsAK5Jet", true);

   float *Tag = M.trackCountingHighEffBJetTagsAK5Jet;
   
   // Output file header
   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage("Try to explore b-tagging efficiency (mistag) with MC");

   vector<string> ExplanationText;
   ExplanationText.push_back("Estimate mis-tag rate from W events!");
   ExplanationText.push_back("Doing several different selections of jets:");
   ExplanationText.push_back("      1. not close to b-hadron (above 20 GeV) from t/tbar (\"Good\")");
   ExplanationText.push_back("      2. not close to any b-hadron (above 20 GeV) in the event (\"Pure\")");
   ExplanationText.push_back("      3. not close to any offsprings (above 20 GeV) of ttbar (\"Exclusive\")");
   ExplanationText.push_back("      4. dR > 0.4 to b-hadron (above 20 GeV) from ttbar (\"SmallRadius\")");
   ExplanationText.push_back("      5. not close to b-hadron (above 10 GeV) from ttbar (\"Low\")");
   ExplanationText.push_back("      6. not close to b-hadron (above 20 GeV) and b-quark from ttbar (\"Paranoid\")");
   ExplanationText.push_back("");
   ExplanationText.push_back("The criteria to \"closeness\" is delta R smaller than 0.6");
   ExplanationText.push_back("(Calo jets)");
   ExplanationText.push_back("");
   ExplanationText.push_back("");
   ExplanationText.push_back("");
   PsFile.AddTextPage(ExplanationText);

   vector<string> TableOfContentItems;
   TableOfContentItems.push_back("Basic Information");
   TableOfContentItems.push_back("Sanity checks of tracing b-hadron and match to jets");
   TableOfContentItems.push_back("Jets not close to b-hadron (20 GeV) from ttbar (\"Good\")");
   TableOfContentItems.push_back("Jets not close to any b-hadron (20 GeV) (\"Pure\")");
   TableOfContentItems.push_back("Jets not close to ttbar offsprings (20 GeV) (\"Exclusive\")");
   TableOfContentItems.push_back("Jets not close (dR > 0.4) to b-hadron from ttbar (\"SmallRadius\")");
   TableOfContentItems.push_back("Jets not close to b-hadron (10 GeV) from ttbar (\"Low\")");
   TableOfContentItems.push_back("Jets not close to b-hadron and b-quark (20 GeV) from ttbar (\"Paranoid\")");
   TableOfContentItems.push_back("Summary plots");
   
   vector<string> Destinations;
   Destinations.push_back("BasicInformation");
   Destinations.push_back("FinalBMeson");
   Destinations.push_back("GoodJets");
   Destinations.push_back("PureJets");
   Destinations.push_back("ExclusiveJets");
   Destinations.push_back("SmallRadiusJets");
   Destinations.push_back("LowJets");
   Destinations.push_back("ParanoidJets");
   Destinations.push_back("SummaryPlots");

   PsFile.AddTableOfContentPage(TableOfContentItems, Destinations);
   PsFile.InsertNamedDestination("HomePage");
   PsFile.SetAutomaticHomeButton(true, "HomePage", 50, 50, 75);

   TFile OutputFile((OutputBase + ".root").c_str(), "recreate");

   // Basic information
   TH1D HBunchCrossing("HBunchCrossing", "Bunch crossing of triggers!", 3502, -1.5, 3500.5);
   TH1D HNPV("HNPV", "Number of (good) primary vertices", 10, -0.5, 9.5);
   TH2D HPVXVsPVY("HPVXVsPVY", "PV, x vs. y, best PV;X;Y", 100, 0.1, 0.4, 100, 0.2, 0.5);
   TH2D HPVTVsPVZ("HPVTVsPVZ", "PV, transverse vs. z, best PV;Transverse;Z", 100, 0.4, 0.5, 100, -40, 40);

   // Final b-meson distribution
   TH1D HFinalBMesonCount("HFinalBMesonCount", "Number of final b-mesons in the event", 10, -0.5, 9.5);

   // Selected jets
   TH1D HAllJetCount("HAllJetCount", "All jets", 30, -0.5, 29.5);

   // Good jets
   TH1D HGoodJetCount("HGoodJetCount", "Good jets", 30, -0.5, 29.5);
   TH1D HGoodJetTCHE("HGoodJetTCHE", "Good jets TCHE value", 100, 0, 20);
   TH2D HGoodJetTCHEVsPT("HGoodJetTCHEVsPT", "Good jets TCHE value vs. PT;TCHE;PT", 100, 0, 20, 100, 0, 500);
   TH1D HGoodJetPT("HGoodJetPT", "PT of good jets", 100, 0, 500);
   TH1D HGoodJetPTPassTCHE("HGoodJetPTPassTCHE", "PT of good jets (pass TCHE)", 100, 0, 500);
   TH1D HGoodJetPTFailTCHE("HGoodJetPTFailTCHE", "PT of good jets (fail TCHE)", 100, 0, 500);
   TH1D HGoodJetEta("HGoodJetEta", "Eta of good jets", 100, -3, 3);
   TH1D HGoodJetEtaPassTCHE("HGoodJetEtaPassTCHE", "Eta of good jets (pass TCHE)", 100, -3, 3);
   TH1D HGoodJetEtaFailTCHE("HGoodJetEtaFailTCHE", "Eta of good jets (fail TCHE)", 100, -3, 3);
   TH2D HGoodJetPTVsEta("HGoodJetPTVsEta", "PT vs. eta of good jets;PT;Eta", 100, 0, 500, 100, -3, 3);
   
   // pure jets
   TH1D HPureJetCount("HPureJetCount", "Pure jets", 30, -0.5, 29.5);
   TH1D HPureJetTCHE("HPureJetTCHE", "Pure jets TCHE value", 100, 0, 20);
   TH2D HPureJetTCHEVsPT("HPureJetTCHEVsPT", "Pure jets TCHE value vs. PT;TCHE;PT", 100, 0, 20, 100, 0, 500);
   TH1D HPureJetPT("HPureJetPT", "PT of Pure jets", 100, 0, 500);
   TH1D HPureJetPTPassTCHE("HPureJetPTPassTCHE", "PT of Pure jets (pass TCHE)", 100, 0, 500);
   TH1D HPureJetPTFailTCHE("HPureJetPTFailTCHE", "PT of Pure jets (fail TCHE)", 100, 0, 500);
   TH1D HPureJetEta("HPureJetEta", "Eta of Pure jets", 100, -3, 3);
   TH1D HPureJetEtaPassTCHE("HPureJetEtaPassTCHE", "Eta of Pure jets (pass TCHE)", 100, -3, 3);
   TH1D HPureJetEtaFailTCHE("HPureJetEtaFailTCHE", "Eta of Pure jets (fail TCHE)", 100, -3, 3);

   // exclusive jets
   TH1D HExclusiveJetCount("HExclusiveJetCount", "Exclusive jets", 30, -0.5, 29.5);
   TH1D HExclusiveJetTCHE("HExclusiveJetTCHE", "Exclusive jets TCHE value", 100, 0, 20);
   TH2D HExclusiveJetTCHEVsPT("HExclusiveJetTCHEVsPT", "Exclusive jets TCHE value vs. PT;TCHE;PT",
      100, 0, 20, 100, 0, 500);
   TH1D HExclusiveJetPT("HExclusiveJetPT", "PT of Exclusive jets", 100, 0, 500);
   TH1D HExclusiveJetPTPassTCHE("HExclusiveJetPTPassTCHE", "PT of Exclusive jets (pass TCHE)", 100, 0, 500);
   TH1D HExclusiveJetPTFailTCHE("HExclusiveJetPTFailTCHE", "PT of Exclusive jets (fail TCHE)", 100, 0, 500);
   TH1D HExclusiveJetEta("HExclusiveJetEta", "Eta of Exclusive jets", 100, -3, 3);
   TH1D HExclusiveJetEtaPassTCHE("HExclusiveJetEtaPassTCHE", "Eta of Exclusive jets (pass TCHE)", 100, -3, 3);
   TH1D HExclusiveJetEtaFailTCHE("HExclusiveJetEtaFailTCHE", "Eta of Exclusive jets (fail TCHE)", 100, -3, 3);
   TH2D HExclusiveJetPTVsEta("HExclusiveJetPTVsEta", "PT vs. eta of good jets;PT;Eta", 100, 0, 500, 100, -3, 3);

   // SmallRadius jets
   TH1D HSmallRadiusJetCount("HSmallRadiusJetCount", "SmallRadius jets", 30, -0.5, 29.5);
   TH1D HSmallRadiusJetTCHE("HSmallRadiusJetTCHE", "SmallRadius jets TCHE value", 100, 0, 20);
   TH2D HSmallRadiusJetTCHEVsPT("HSmallRadiusJetTCHEVsPT", "SmallRadius jets TCHE value vs. PT;TCHE;PT",
      100, 0, 20, 100, 0, 500);
   TH1D HSmallRadiusJetPT("HSmallRadiusJetPT", "PT of SmallRadius jets", 100, 0, 500);
   TH1D HSmallRadiusJetPTPassTCHE("HSmallRadiusJetPTPassTCHE", "PT of SmallRadius jets (pass TCHE)", 100, 0, 500);
   TH1D HSmallRadiusJetPTFailTCHE("HSmallRadiusJetPTFailTCHE", "PT of SmallRadius jets (fail TCHE)", 100, 0, 500);
   TH1D HSmallRadiusJetEta("HSmallRadiusJetEta", "Eta of SmallRadius jets", 100, -3, 3);
   TH1D HSmallRadiusJetEtaPassTCHE("HSmallRadiusJetEtaPassTCHE", "Eta of SmallRadius jets (pass TCHE)", 100, -3, 3);
   TH1D HSmallRadiusJetEtaFailTCHE("HSmallRadiusJetEtaFailTCHE", "Eta of SmallRadius jets (fail TCHE)", 100, -3, 3);

   // Low jets
   TH1D HLowJetCount("HLowJetCount", "Low jets", 30, -0.5, 29.5);
   TH1D HLowJetTCHE("HLowJetTCHE", "Low jets TCHE value", 100, 0, 20);
   TH2D HLowJetTCHEVsPT("HLowJetTCHEVsPT", "Low jets TCHE value vs. PT;TCHE;PT",
      100, 0, 20, 100, 0, 500);
   TH1D HLowJetPT("HLowJetPT", "PT of Low jets", 100, 0, 500);
   TH1D HLowJetPTPassTCHE("HLowJetPTPassTCHE", "PT of Low jets (pass TCHE)", 100, 0, 500);
   TH1D HLowJetPTFailTCHE("HLowJetPTFailTCHE", "PT of Low jets (fail TCHE)", 100, 0, 500);
   TH1D HLowJetEta("HLowJetEta", "Eta of Low jets", 100, -3, 3);
   TH1D HLowJetEtaPassTCHE("HLowJetEtaPassTCHE", "Eta of Low jets (pass TCHE)", 100, -3, 3);
   TH1D HLowJetEtaFailTCHE("HLowJetEtaFailTCHE", "Eta of Low jets (fail TCHE)", 100, -3, 3);

   // Paranoid jets
   TH1D HParanoidJetCount("HParanoidJetCount", "Paranoid jets", 30, -0.5, 29.5);
   TH1D HParanoidJetTCHE("HParanoidJetTCHE", "Paranoid jets TCHE value", 100, 0, 20);
   TH2D HParanoidJetTCHEVsPT("HParanoidJetTCHEVsPT", "Paranoid jets TCHE value vs. PT;TCHE;PT",
      100, 0, 20, 100, 0, 500);
   TH1D HParanoidJetPT("HParanoidJetPT", "PT of Paranoid jets", 100, 0, 500);
   TH1D HParanoidJetPTPassTCHE("HParanoidJetPTPassTCHE", "PT of Paranoid jets (pass TCHE)", 100, 0, 500);
   TH1D HParanoidJetPTFailTCHE("HParanoidJetPTFailTCHE", "PT of Paranoid jets (fail TCHE)", 100, 0, 500);
   TH1D HParanoidJetEta("HParanoidJetEta", "Eta of Paranoid jets", 100, -3, 3);
   TH1D HParanoidJetEtaPassTCHE("HParanoidJetEtaPassTCHE", "Eta of Paranoid jets (pass TCHE)", 100, -3, 3);
   TH1D HParanoidJetEtaFailTCHE("HParanoidJetEtaFailTCHE", "Eta of Paranoid jets (fail TCHE)", 100, -3, 3);

   // Loop through events
   int NumberOfEvents = NTPTree->GetEntries();
   for(int iEvent = 0; iEvent < NumberOfEvents; iEvent++)
   {
      if((iEvent + 1) % 20000 == 0)
         cout << "Processing entry " << iEvent + 1 << "/" << NumberOfEvents << endl;

      NTPTree->GetEntry(iEvent);

      // Basic information
      HBunchCrossing.Fill(M.bunchCrossing);

      int GoodPVCount = 0;
      int BestPVIndex = -1;
      for(int i = 0; i < M.nPV; i++)
      {
         if(M.ndofPV[i] <= 4)   continue;
         if(sqrt(M.PVzPV[i]) > 15)   continue;
         if(M.PVxPV[i] * M.PVxPV[i] + M.PVyPV[i] * M.PVyPV[i] > 2 * 2)   continue;
         
         GoodPVCount = GoodPVCount + 1;
         if(BestPVIndex < 0 || M.SumPtPV[i] > M.SumPtPV[BestPVIndex])
            BestPVIndex = i;
      }

      HNPV.Fill(GoodPVCount);
      if(BestPVIndex >= 0 && BestPVIndex < M.nPV)
      {
         FourVector BestPVP(0, M.PVxPV[BestPVIndex], M.PVyPV[BestPVIndex], M.PVzPV[BestPVIndex]);
         HPVXVsPVY.Fill(BestPVP[1], BestPVP[2]);
         HPVTVsPVZ.Fill(BestPVP.GetPT(), BestPVP[3]);
      }
      
      if(GoodPVCount < PUMin || GoodPVCount > PUMax)
         continue;

      // Trace b-mesons from MC information
      vector<FourVector> AllBMeson;
      int BMesonCountInAcceptance = 0;
      for(int i = 0; i < M.nMc; i++)
      {
         if(M.idMc[i] != 5 && M.idMc[i] != -5)
            continue;

         int index = TraceBHadron(M, i);
         FourVector BMesonP;
         BMesonP.SetSizeEtaPhi(M.energyMc[i], M.etaMc[i], M.phiMc[i]);

         if(BMesonP.GetPT() > 20)
            AllBMeson.push_back(BMesonP);

         if(BMesonP.GetPT() > 20 && fabs(BMesonP.GetEta()) < 3)
            BMesonCountInAcceptance = BMesonCountInAcceptance + 1;
      }
      HFinalBMesonCount.Fill(BMesonCountInAcceptance);
     
      vector<FourVector> BMeson, LowBMeson, ParanoidB;
      int BFromT = max(FindChildIndex(M, 5, 6), FindChildIndex(M, -5, 6));
      int BFromTBar = max(FindChildIndex(M, 5, -6), FindChildIndex(M, -5, -6));
      int FinalBHadronFromT = TraceBHadron(M, BFromT);
      int FinalBHadronFromTBar = TraceBHadron(M, BFromTBar);
      FourVector FinalBFromTP, FinalBFromTBarP;
      if(BFromT >= 0)
      {
         FourVector BP;
         BP.SetSizeEtaPhiEnergy(M.pMc[BFromT], M.etaMc[BFromT], M.phiMc[BFromT], M.energyMc[BFromT]);
         ParanoidB.push_back(BP);
      }
      if(BFromTBar >= 0)
      {
         FourVector BP;
         BP.SetSizeEtaPhiEnergy(M.pMc[BFromTBar], M.etaMc[BFromTBar], M.phiMc[BFromTBar], M.energyMc[BFromTBar]);
         ParanoidB.push_back(BP);
      }
      if(FinalBHadronFromT >= 0)
      {
         FinalBFromTP.SetSizeEtaPhiEnergy(M.pMc[FinalBHadronFromT], M.etaMc[FinalBHadronFromT],
            M.phiMc[FinalBHadronFromT], M.energyMc[FinalBHadronFromT]);
         if(FinalBFromTP.GetPT() > 20)
            BMeson.push_back(FinalBFromTP);
         if(FinalBFromTP.GetPT() > 20)
            ParanoidB.push_back(FinalBFromTP);
         if(FinalBFromTP.GetPT() > 10)
            LowBMeson.push_back(FinalBFromTP);
      }
      if(FinalBHadronFromTBar >= 0)
      {
         FinalBFromTBarP.SetSizeEtaPhiEnergy(M.pMc[FinalBHadronFromTBar], M.etaMc[FinalBHadronFromTBar],
            M.phiMc[FinalBHadronFromTBar], M.energyMc[FinalBHadronFromTBar]);
         if(FinalBFromTBarP.GetPT() > 20)
            BMeson.push_back(FinalBFromTBarP);
         if(FinalBFromTBarP.GetPT() > 20)
            ParanoidB.push_back(FinalBFromTBarP);
         if(FinalBFromTBarP.GetPT() > 10)
            LowBMeson.push_back(FinalBFromTBarP);
      }

      vector<FourVector> TTbarFragment = BMeson;
      int WFromT = max(FindChildIndex(M, 24, 6), FindChildIndex(M, -24, 6));
      int WFromTBar = max(FindChildIndex(M, 24, -6), FindChildIndex(M, -24, -6));
      for(int i = 0; i < M.nMc; i++)
      {
         if(M.idMc[i] == 12 || M.idMc[i] == 14 || M.idMc[i] == 16
            || M.idMc[i] == -12 || M.idMc[i] == -14 || M.idMc[i] == -16)
            continue;

         FourVector ParticleP;
         ParticleP.SetSizeEtaPhi(M.pMc[i], M.etaMc[i], M.phiMc[i]);

         if(WFromT >= 0 && M.mothMc[i] == WFromT)
            TTbarFragment.push_back(ParticleP);
         if(WFromTBar >= 0 && M.mothMc[i] == WFromTBar)
            TTbarFragment.push_back(ParticleP);
      }
      for(int i = 0; i < M.nMc; i++)
      {
         if(M.idMc[i] == 12 || M.idMc[i] == 14 || M.idMc[i] == 16
            || M.idMc[i] == -12 || M.idMc[i] == -14 || M.idMc[i] == -16)
            continue;

         FourVector ParticleP;
         ParticleP.SetSizeEtaPhi(M.pMc[i], M.etaMc[i], M.phiMc[i]);

         if(M.mothMc[i] >= 0 && fabs(M.idMc[M.mothMc[i]]) == 24)
            TTbarFragment.push_back(ParticleP);
         if(M.mothMc[i] >= 0 && fabs(M.idMc[M.mothMc[i]]) == 23)
            TTbarFragment.push_back(ParticleP);
      }

      // exclude jets too close to a final b-meson
      vector<int> GoodJets, PureJets, ExclusiveJets, SmallRadiusJets, LowJets, ParanoidJets;
      vector<FourVector> GoodJetsP, PureJetsP, ExclusiveJetsP, SmallRadiusJetsP, LowJetsP, ParanoidJetsP;
      int AllJetCount = 0;
      for(int i = 0; i < M.nAK5Jet; i++)
      {
         FourVector JetP(M.energyAK5Jet[i], M.pxAK5Jet[i], M.pyAK5Jet[i], M.pzAK5Jet[i]);
         if(JetP.GetPT() < 30 || fabs(JetP.GetEta()) > 2.4)
            continue;

         AllJetCount = AllJetCount + 1;

         bool Good = true;
         for(int j = 0; j < (int)BMeson.size() && Good == true; j++)
         {
            if(GetDR(JetP, BMeson[j]) < 0.6)
               Good = false;
         }
         if(Good == true)
         {
            GoodJets.push_back(i);
            GoodJetsP.push_back(JetP);
         }

         bool Pure = true;
         for(int j = 0; j < (int)AllBMeson.size() && Pure == true; j++)
         {
            if(GetDR(JetP, AllBMeson[j]) < 0.6)
               Pure = false;
         }
         if(Pure == true)
         {
            PureJets.push_back(i);
            PureJetsP.push_back(JetP);
         }
         
         bool Exclusive = true;
         for(int j = 0; j < (int)TTbarFragment.size() && Exclusive == true; j++)
         {
            if(GetDR(JetP, TTbarFragment[j]) < 0.6)
               Exclusive = false;
         }
         if(Exclusive == true)
         {
            ExclusiveJets.push_back(i);
            ExclusiveJetsP.push_back(JetP);
         }

         bool SmallRadius = true;
         for(int j = 0; j < (int)BMeson.size() && SmallRadius == true; j++)
         {
            if(GetDR(JetP, BMeson[j]) < 0.4)
               SmallRadius = false;
         }
         if(SmallRadius == true)
         {
            SmallRadiusJets.push_back(i);
            SmallRadiusJetsP.push_back(JetP);
         }

         bool Low = true;
         for(int j = 0; j < (int)LowBMeson.size() && Low == true; j++)
         {
            if(GetDR(JetP, LowBMeson[j]) < 0.6)
               Low = false;
         }
         if(Low == true)
         {
            LowJets.push_back(i);
            LowJetsP.push_back(JetP);
         }

         bool Paranoid = true;
         for(int j = 0; j < (int)ParanoidB.size() && Paranoid == true; j++)
         {
            if(GetDR(JetP, ParanoidB[j]) < 0.6)
               Paranoid = false;
         }
         if(Paranoid == true)
         {
            ParanoidJets.push_back(i);
            ParanoidJetsP.push_back(JetP);
         }
      }

      HAllJetCount.Fill(AllJetCount);
      HGoodJetCount.Fill(GoodJets.size());
      HPureJetCount.Fill(PureJets.size());
      HExclusiveJetCount.Fill(ExclusiveJets.size());
      HSmallRadiusJetCount.Fill(SmallRadiusJets.size());
      HLowJetCount.Fill(LowJets.size());
      HParanoidJetCount.Fill(ParanoidJets.size());

      for(int i = 0; i < (int)GoodJets.size(); i++)
      {
         HGoodJetTCHE.Fill(Tag[GoodJets[i]]);
         HGoodJetTCHEVsPT.Fill(Tag[GoodJets[i]], GoodJetsP[i].GetPT());

         HGoodJetPT.Fill(GoodJetsP[i].GetPT());
         HGoodJetPTVsEta.Fill(GoodJetsP[i].GetPT(), GoodJetsP[i].GetEta());
         if(Tag[GoodJets[i]] > CutValue)
            HGoodJetPTPassTCHE.Fill(GoodJetsP[i].GetPT());
         else
            HGoodJetPTFailTCHE.Fill(GoodJetsP[i].GetPT());

         HGoodJetEta.Fill(GoodJetsP[i].GetEta());
         if(Tag[GoodJets[i]] > CutValue)
            HGoodJetEtaPassTCHE.Fill(GoodJetsP[i].GetEta());
         else
            HGoodJetEtaFailTCHE.Fill(GoodJetsP[i].GetEta());
      }
      
      for(int i = 0; i < (int)PureJets.size(); i++)
      {
         HPureJetTCHE.Fill(Tag[PureJets[i]]);
         HPureJetTCHEVsPT.Fill(Tag[PureJets[i]], PureJetsP[i].GetPT());

         HPureJetPT.Fill(PureJetsP[i].GetPT());
         if(Tag[PureJets[i]] > CutValue)
            HPureJetPTPassTCHE.Fill(PureJetsP[i].GetPT());
         else
            HPureJetPTFailTCHE.Fill(PureJetsP[i].GetPT());

         HPureJetEta.Fill(PureJetsP[i].GetEta());
         if(Tag[PureJets[i]] > CutValue)
            HPureJetEtaPassTCHE.Fill(PureJetsP[i].GetEta());
         else
            HPureJetEtaFailTCHE.Fill(PureJetsP[i].GetEta());
      }
      
      for(int i = 0; i < (int)ExclusiveJets.size(); i++)
      {
         HExclusiveJetTCHE.Fill(Tag[ExclusiveJets[i]]);
         HExclusiveJetTCHEVsPT.Fill(Tag[ExclusiveJets[i]], ExclusiveJetsP[i].GetPT());

         HExclusiveJetPT.Fill(ExclusiveJetsP[i].GetPT());
         HExclusiveJetPTVsEta.Fill(ExclusiveJetsP[i].GetPT(), ExclusiveJetsP[i].GetEta());
         if(Tag[ExclusiveJets[i]] > CutValue)
            HExclusiveJetPTPassTCHE.Fill(ExclusiveJetsP[i].GetPT());
         else
            HExclusiveJetPTFailTCHE.Fill(ExclusiveJetsP[i].GetPT());

         HExclusiveJetEta.Fill(ExclusiveJetsP[i].GetEta());
         if(Tag[ExclusiveJets[i]] > CutValue)
            HExclusiveJetEtaPassTCHE.Fill(ExclusiveJetsP[i].GetEta());
         else
            HExclusiveJetEtaFailTCHE.Fill(ExclusiveJetsP[i].GetEta());
      }
      
      for(int i = 0; i < (int)SmallRadiusJets.size(); i++)
      {
         HSmallRadiusJetTCHE.Fill(Tag[SmallRadiusJets[i]]);
         HSmallRadiusJetTCHEVsPT.Fill(Tag[SmallRadiusJets[i]], SmallRadiusJetsP[i].GetPT());

         HSmallRadiusJetPT.Fill(SmallRadiusJetsP[i].GetPT());
         if(Tag[SmallRadiusJets[i]] > CutValue)
            HSmallRadiusJetPTPassTCHE.Fill(SmallRadiusJetsP[i].GetPT());
         else
            HSmallRadiusJetPTFailTCHE.Fill(SmallRadiusJetsP[i].GetPT());

         HSmallRadiusJetEta.Fill(SmallRadiusJetsP[i].GetEta());
         if(Tag[SmallRadiusJets[i]] > CutValue)
            HSmallRadiusJetEtaPassTCHE.Fill(SmallRadiusJetsP[i].GetEta());
         else
            HSmallRadiusJetEtaFailTCHE.Fill(SmallRadiusJetsP[i].GetEta());
      }
      
      for(int i = 0; i < (int)LowJets.size(); i++)
      {
         HLowJetTCHE.Fill(Tag[LowJets[i]]);
         HLowJetTCHEVsPT.Fill(Tag[LowJets[i]], LowJetsP[i].GetPT());

         HLowJetPT.Fill(LowJetsP[i].GetPT());
         if(Tag[LowJets[i]] > CutValue)
            HLowJetPTPassTCHE.Fill(LowJetsP[i].GetPT());
         else
            HLowJetPTFailTCHE.Fill(LowJetsP[i].GetPT());

         HLowJetEta.Fill(LowJetsP[i].GetEta());
         if(Tag[LowJets[i]] > CutValue)
            HLowJetEtaPassTCHE.Fill(LowJetsP[i].GetEta());
         else
            HLowJetEtaFailTCHE.Fill(LowJetsP[i].GetEta());
      }
      
      for(int i = 0; i < (int)ParanoidJets.size(); i++)
      {
         HParanoidJetTCHE.Fill(Tag[ParanoidJets[i]]);
         HParanoidJetTCHEVsPT.Fill(Tag[ParanoidJets[i]], ParanoidJetsP[i].GetPT());

         HParanoidJetPT.Fill(ParanoidJetsP[i].GetPT());
         if(Tag[ParanoidJets[i]] > CutValue)
            HParanoidJetPTPassTCHE.Fill(ParanoidJetsP[i].GetPT());
         else
            HParanoidJetPTFailTCHE.Fill(ParanoidJetsP[i].GetPT());

         HParanoidJetEta.Fill(ParanoidJetsP[i].GetEta());
         if(Tag[ParanoidJets[i]] > CutValue)
            HParanoidJetEtaPassTCHE.Fill(ParanoidJetsP[i].GetEta());
         else
            HParanoidJetEtaFailTCHE.Fill(ParanoidJetsP[i].GetEta());
      }
   }

   // Write to output
   PsFile.AddTextPage("Basic information");
   PsFile.InsertNamedDestination("BasicInformation");
   PsFile.AddPlot(HBunchCrossing, "", true);
   PsFile.AddPlot(HNPV, "hist text00", true);
   PsFile.AddPlot(HPVXVsPVY, "colz", false, true);
   PsFile.AddPlot(HPVTVsPVZ, "colz", false, true);

   PsFile.AddTextPage("Final B-Meson");
   PsFile.InsertNamedDestination("FinalBMeson");
   PsFile.AddPlot(HFinalBMesonCount, "text00 hist", true);
   
   PsFile.AddTextPage("Good jets");
   PsFile.InsertNamedDestination("GoodJets");
   PsFile.AddPlot(HAllJetCount, "text00 hist", true);
   PsFile.AddPlot(HGoodJetCount, "text00 hist", true);
   PsFile.AddPlot(HGoodJetTCHE, "", true);
   PsFile.AddPlot(HGoodJetTCHEVsPT, "colz", false, true);
   PsFile.AddPlot(HGoodJetPTVsEta, "colz", false);   HGoodJetPTVsEta.Write();
   PsFile.AddPlot(HGoodJetPT, "", true);             HGoodJetPT.Write();
   PsFile.AddPlot(HGoodJetPTPassTCHE, "", true);     HGoodJetPTPassTCHE.Write();
   PsFile.AddPlot(HGoodJetPTFailTCHE, "", true);     HGoodJetPTFailTCHE.Write();

   TGraphAsymmErrors GMistagPT;
   GMistagPT.SetNameTitle("GMistagPT", "Mis-tag rate as a function of transverse momentum");
   GMistagPT.BayesDivide(&HGoodJetPTPassTCHE, &HGoodJetPT);
   TCanvas CMistagPT;
   GMistagPT.Draw("ape");
   GMistagPT.GetXaxis()->SetTitle("Jet PT");
   GMistagPT.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CMistagPT);
   
   PsFile.AddPlot(HGoodJetEta, "", true);           HGoodJetEta.Write();
   PsFile.AddPlot(HGoodJetEtaPassTCHE, "", true);   HGoodJetEtaPassTCHE.Write();
   PsFile.AddPlot(HGoodJetEtaFailTCHE, "", true);   HGoodJetEtaFailTCHE.Write();

   TGraphAsymmErrors GMistagEta;
   GMistagEta.SetNameTitle("GMistagEta", "Mis-tag rate as a function of eta");
   GMistagEta.BayesDivide(&HGoodJetEtaPassTCHE, &HGoodJetEta);
   TCanvas CMistagEta;
   GMistagEta.Draw("ape");
   GMistagEta.GetXaxis()->SetTitle("Jet Eta");
   GMistagEta.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CMistagEta);
   GMistagEta.Write();
   
   PsFile.AddTextPage("Pure jets");
   PsFile.InsertNamedDestination("PureJets");
   PsFile.AddPlot(HAllJetCount, "text00 hist", true);
   PsFile.AddPlot(HPureJetCount, "text00 hist", true);
   PsFile.AddPlot(HPureJetTCHE, "", true);
   PsFile.AddPlot(HPureJetTCHEVsPT, "colz", false, true);
   PsFile.AddPlot(HPureJetPT, "", true);
   PsFile.AddPlot(HPureJetPTPassTCHE, "", true);
   PsFile.AddPlot(HPureJetPTFailTCHE, "", true);

   TGraphAsymmErrors GPureMistagPT;
   GPureMistagPT.SetNameTitle("GPureMistagPT", "Mis-tag rate as a function of transverse momentum (pure)");
   GPureMistagPT.BayesDivide(&HPureJetPTPassTCHE, &HPureJetPT);
   TCanvas CPureMistagPT;
   GPureMistagPT.Draw("ape");
   GPureMistagPT.GetXaxis()->SetTitle("Jet PT");
   GPureMistagPT.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CPureMistagPT);

   PsFile.AddPlot(HPureJetEta, "", true);
   PsFile.AddPlot(HPureJetEtaPassTCHE, "", true);
   PsFile.AddPlot(HPureJetEtaFailTCHE, "", true);
   
   TGraphAsymmErrors GPureMistagEta;
   GPureMistagEta.SetNameTitle("GPureMistagEta", "Mis-tag rate as a function of eta (pure)");
   GPureMistagEta.BayesDivide(&HPureJetEtaPassTCHE, &HPureJetEta);
   TCanvas CPureMistagEta;
   GPureMistagEta.Draw("ape");
   GPureMistagEta.GetXaxis()->SetTitle("Jet Eta");
   GPureMistagEta.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CPureMistagEta);
   
   PsFile.AddTextPage("Exclusive jets");
   PsFile.InsertNamedDestination("ExclusiveJets");
   PsFile.AddPlot(HAllJetCount, "text00 hist", true);
   PsFile.AddPlot(HExclusiveJetCount, "text00 hist", true);
   PsFile.AddPlot(HExclusiveJetTCHE, "", true);
   PsFile.AddPlot(HExclusiveJetTCHEVsPT, "colz", false, true);
   PsFile.AddPlot(HExclusiveJetPTVsEta, "colz", false);   HExclusiveJetPTVsEta.Write();
   PsFile.AddPlot(HExclusiveJetPT, "", true);             HExclusiveJetPT.Write();
   PsFile.AddPlot(HExclusiveJetPTPassTCHE, "", true);     HExclusiveJetPTPassTCHE.Write();
   PsFile.AddPlot(HExclusiveJetPTFailTCHE, "", true);     HExclusiveJetPTFailTCHE.Write();

   TGraphAsymmErrors GExclusiveMistagPT;
   GExclusiveMistagPT.SetNameTitle("GExclusiveMistagPT",
      "Mis-tag rate as a function of transverse momentum (Exclusive)");
   GExclusiveMistagPT.BayesDivide(&HExclusiveJetPTPassTCHE, &HExclusiveJetPT);
   TCanvas CExclusiveMistagPT;
   GExclusiveMistagPT.Draw("ape");
   GExclusiveMistagPT.GetXaxis()->SetTitle("Jet PT");
   GExclusiveMistagPT.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CExclusiveMistagPT);

   PsFile.AddPlot(HExclusiveJetEta, "", true);           HExclusiveJetEta.Write();
   PsFile.AddPlot(HExclusiveJetEtaPassTCHE, "", true);   HExclusiveJetEtaPassTCHE.Write();
   PsFile.AddPlot(HExclusiveJetEtaFailTCHE, "", true);   HExclusiveJetEtaFailTCHE.Write();
   
   TGraphAsymmErrors GExclusiveMistagEta;
   GExclusiveMistagEta.SetNameTitle("GExclusiveMistagEta", "Mis-tag rate as a function of eta (Exclusive)");
   GExclusiveMistagEta.BayesDivide(&HExclusiveJetEtaPassTCHE, &HExclusiveJetEta);
   TCanvas CExclusiveMistagEta;
   GExclusiveMistagEta.Draw("ape");
   GExclusiveMistagEta.GetXaxis()->SetTitle("Jet Eta");
   GExclusiveMistagEta.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CExclusiveMistagEta);
   
   PsFile.AddTextPage("SmallRadius jets");
   PsFile.InsertNamedDestination("SmallRadiusJets");
   PsFile.AddPlot(HAllJetCount, "text00 hist", true);
   PsFile.AddPlot(HSmallRadiusJetCount, "text00 hist", true);
   PsFile.AddPlot(HSmallRadiusJetTCHE, "", true);
   PsFile.AddPlot(HSmallRadiusJetTCHEVsPT, "colz", false, true);
   PsFile.AddPlot(HSmallRadiusJetPT, "", true);
   PsFile.AddPlot(HSmallRadiusJetPTPassTCHE, "", true);
   PsFile.AddPlot(HSmallRadiusJetPTFailTCHE, "", true);

   TGraphAsymmErrors GSmallRadiusMistagPT;
   GSmallRadiusMistagPT.SetNameTitle("GSmallRadiusMistagPT",
      "Mis-tag rate as a function of transverse momentum (SmallRadius)");
   GSmallRadiusMistagPT.BayesDivide(&HSmallRadiusJetPTPassTCHE, &HSmallRadiusJetPT);
   TCanvas CSmallRadiusMistagPT;
   GSmallRadiusMistagPT.Draw("ape");
   GSmallRadiusMistagPT.GetXaxis()->SetTitle("Jet PT");
   GSmallRadiusMistagPT.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CSmallRadiusMistagPT);

   PsFile.AddPlot(HSmallRadiusJetEta, "", true);
   PsFile.AddPlot(HSmallRadiusJetEtaPassTCHE, "", true);
   PsFile.AddPlot(HSmallRadiusJetEtaFailTCHE, "", true);
   
   TGraphAsymmErrors GSmallRadiusMistagEta;
   GSmallRadiusMistagEta.SetNameTitle("GSmallRadiusMistagEta", "Mis-tag rate as a function of eta (SmallRadius)");
   GSmallRadiusMistagEta.BayesDivide(&HSmallRadiusJetEtaPassTCHE, &HSmallRadiusJetEta);
   TCanvas CSmallRadiusMistagEta;
   GSmallRadiusMistagEta.Draw("ape");
   GSmallRadiusMistagEta.GetXaxis()->SetTitle("Jet Eta");
   GSmallRadiusMistagEta.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CSmallRadiusMistagEta);

   PsFile.AddTextPage("Low jets");
   PsFile.InsertNamedDestination("LowJets");
   PsFile.AddPlot(HAllJetCount, "text00 hist", true);
   PsFile.AddPlot(HLowJetCount, "text00 hist", true);
   PsFile.AddPlot(HLowJetTCHE, "", true);
   PsFile.AddPlot(HLowJetTCHEVsPT, "colz", false, true);
   PsFile.AddPlot(HLowJetPT, "", true);
   PsFile.AddPlot(HLowJetPTPassTCHE, "", true);
   PsFile.AddPlot(HLowJetPTFailTCHE, "", true);

   TGraphAsymmErrors GLowMistagPT;
   GLowMistagPT.SetNameTitle("GLowMistagPT",
      "Mis-tag rate as a function of transverse momentum (Low)");
   GLowMistagPT.BayesDivide(&HLowJetPTPassTCHE, &HLowJetPT);
   TCanvas CLowMistagPT;
   GLowMistagPT.Draw("ape");
   GLowMistagPT.GetXaxis()->SetTitle("Jet PT");
   GLowMistagPT.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CLowMistagPT);

   PsFile.AddPlot(HLowJetEta, "", true);
   PsFile.AddPlot(HLowJetEtaPassTCHE, "", true);
   PsFile.AddPlot(HLowJetEtaFailTCHE, "", true);
   
   TGraphAsymmErrors GLowMistagEta;
   GLowMistagEta.SetNameTitle("GLowMistagEta", "Mis-tag rate as a function of eta (Low)");
   GLowMistagEta.BayesDivide(&HLowJetEtaPassTCHE, &HLowJetEta);
   TCanvas CLowMistagEta;
   GLowMistagEta.Draw("ape");
   GLowMistagEta.GetXaxis()->SetTitle("Jet Eta");
   GLowMistagEta.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CLowMistagEta);
   
   PsFile.AddTextPage("Paranoid jets");
   PsFile.InsertNamedDestination("ParanoidJets");
   PsFile.AddPlot(HAllJetCount, "text00 hist", true);
   PsFile.AddPlot(HParanoidJetCount, "text00 hist", true);
   PsFile.AddPlot(HParanoidJetTCHE, "", true);
   PsFile.AddPlot(HParanoidJetTCHEVsPT, "colz", false, true);
   PsFile.AddPlot(HParanoidJetPT, "", true);
   PsFile.AddPlot(HParanoidJetPTPassTCHE, "", true);
   PsFile.AddPlot(HParanoidJetPTFailTCHE, "", true);

   TGraphAsymmErrors GParanoidMistagPT;
   GParanoidMistagPT.SetNameTitle("GParanoidMistagPT",
      "Mis-tag rate as a function of transverse momentum (Paranoid)");
   GParanoidMistagPT.BayesDivide(&HParanoidJetPTPassTCHE, &HParanoidJetPT);
   TCanvas CParanoidMistagPT;
   GParanoidMistagPT.Draw("ape");
   GParanoidMistagPT.GetXaxis()->SetTitle("Jet PT");
   GParanoidMistagPT.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CParanoidMistagPT);

   PsFile.AddPlot(HParanoidJetEta, "", true);
   PsFile.AddPlot(HParanoidJetEtaPassTCHE, "", true);
   PsFile.AddPlot(HParanoidJetEtaFailTCHE, "", true);
   
   TGraphAsymmErrors GParanoidMistagEta;
   GParanoidMistagEta.SetNameTitle("GParanoidMistagEta", "Mis-tag rate as a function of eta (Paranoid)");
   GParanoidMistagEta.BayesDivide(&HParanoidJetEtaPassTCHE, &HParanoidJetEta);
   TCanvas CParanoidMistagEta;
   GParanoidMistagEta.Draw("ape");
   GParanoidMistagEta.GetXaxis()->SetTitle("Jet Eta");
   GParanoidMistagEta.GetYaxis()->SetTitle("Mistag rate");
   PsFile.AddCanvas(CParanoidMistagEta);

   PsFile.AddTextPage("Summary plots");
   PsFile.InsertNamedDestination("SummaryPlots");

   TLegend legendPT(0.15, 0.65, 0.55, 0.85);
   legendPT.SetBorderSize(0);
   legendPT.SetFillStyle(0);
   legendPT.AddEntry(&GMistagPT, "Good", "l");
   legendPT.AddEntry(&GPureMistagPT, "Pure", "l");
   legendPT.AddEntry(&GExclusiveMistagPT, "Exclusive", "l");
   legendPT.AddEntry(&GSmallRadiusMistagPT, "SmallRadius", "l");
   legendPT.AddEntry(&GLowMistagPT, "Low", "l");
   legendPT.AddEntry(&GParanoidMistagPT, "Paranoid", "l");

   TLegend legendEta(0.4, 0.15, 0.8, 0.35);
   legendEta.SetBorderSize(0);
   legendEta.SetFillStyle(0);
   legendEta.AddEntry(&GMistagEta, "Good", "l");
   legendEta.AddEntry(&GPureMistagEta, "Pure", "l");
   legendEta.AddEntry(&GExclusiveMistagEta, "Exclusive", "l");
   legendEta.AddEntry(&GSmallRadiusMistagEta, "SmallRadius", "l");
   legendEta.AddEntry(&GLowMistagEta, "Low", "l");
   legendEta.AddEntry(&GParanoidMistagEta, "Paranoid", "l");

   TCanvas CPTSummary;
   GMistagPT.SetLineColor(1);
   GPureMistagPT.SetLineColor(2);
   GExclusiveMistagPT.SetLineColor(3);
   GSmallRadiusMistagPT.SetLineColor(4);
   GLowMistagPT.SetLineColor(5);
   GParanoidMistagPT.SetLineColor(6);
   GMistagPT.Draw("ape");
   GPureMistagPT.Draw("pe");
   GExclusiveMistagPT.Draw("pe");
   GSmallRadiusMistagPT.Draw("pe");
   GLowMistagPT.Draw("pe");
   GParanoidMistagPT.Draw("pe");
   legendPT.Draw();
   PsFile.AddCanvas(CPTSummary);

   TCanvas CEtaSummary;
   GMistagEta.SetLineColor(1);
   GPureMistagEta.SetLineColor(2);
   GExclusiveMistagEta.SetLineColor(3);
   GSmallRadiusMistagEta.SetLineColor(4);
   GLowMistagEta.SetLineColor(5);
   GParanoidMistagEta.SetLineColor(6);
   GMistagEta.Draw("ape");
   GPureMistagEta.Draw("pe");
   GExclusiveMistagEta.Draw("pe");
   GSmallRadiusMistagEta.Draw("pe");
   GLowMistagEta.Draw("pe");
   GParanoidMistagEta.Draw("pe");
   legendEta.Draw();
   PsFile.AddCanvas(CEtaSummary);

   // Close things 
   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}
//---------------------------------------------------------------------------
int FindChildIndex(NTPTreeMessenger &M, int ChildPDGID, int ParentPDGID)
{
   int MotherIndex = -1;

   for(int i = 0; i < M.nMc; i++)
   {
      if(M.idMc[i] == ParentPDGID)
      {
         MotherIndex = i;
         break;
      }
   }

   if(MotherIndex == -1)
      return -1;

   for(int i = 0; i < M.nMc; i++)
      if(M.idMc[i] == ChildPDGID && M.mothMc[i] == MotherIndex)
         return i;

   return -1;
}
//---------------------------------------------------------------------------
int TraceBHadron(NTPTreeMessenger &M, int StartIndex)
{
   if(StartIndex < 0 || StartIndex >= M.nMc)
      return -1;
   if(HasB(M.idMc[StartIndex]) == false && M.idMc[StartIndex] != 92)
      return -1;

   int CurrentIndex = StartIndex;

   bool OK = false;
   while(OK == false)
   {
      // step 1: collect list of children that contain b (or is a string)
      vector<int> ChildrenIndex;
      for(int i = 0; i < M.nMc; i++)
      {
         if(M.mothMc[i] == CurrentIndex)
         {
            if(M.idMc[i] != 92 && HasB(M.idMc[i]) == false)
               continue;
            ChildrenIndex.push_back(i);
         }
      }

      // step 2: if there is more than one candidate, choose the one with highest pt
      if(ChildrenIndex.size() == 0)
         return CurrentIndex;
      else if(ChildrenIndex.size() == 1)
         CurrentIndex = ChildrenIndex[0];
      else
      {
         double BestCandidatePT = M.pMc[ChildrenIndex[0]] / cosh(M.etaMc[ChildrenIndex[0]]);
         int BestCandidate = 0;
         for(int i = 1; i < (int)ChildrenIndex.size(); i++)
         {
            double PT = M.pMc[ChildrenIndex[i]] / cosh(M.etaMc[ChildrenIndex[i]]);
            if(PT > BestCandidatePT)
            {
               BestCandidate = i;
               BestCandidatePT = PT;
            }
         }

         CurrentIndex = ChildrenIndex[BestCandidate];
      }
   }

   return -1;
}
//---------------------------------------------------------------------------
bool HasB(int PDGID)
{
   // note:
   //    b quark: +-5
   //    meson code = 100i + 10j + 2s + 1, quark(i), anti-quark(-j)
   //    baryon code = 1000i + 100j + 10k + 2s + 1, quarks(ijk)

   if(PDGID < 0)
      PDGID = -PDGID;

   if(PDGID == 5)
      return true;
   if((PDGID % 100) / 10 == 5)
      return true;
   if((PDGID % 1000) / 100 == 5)
      return true;
   if((PDGID % 10000) / 1000 == 5)
      return true;

   return false;
}
//---------------------------------------------------------------------------
int FindClosestJet(float *JetCollectionEta, float *JetCollectionPhi, int JetCount, double Eta, double Phi)
{
   double ClosestJetDR = 999999;
   int ClosestJetIndex = 0;
   for(int i = 0; i < JetCount; i++)
   {
      double EtaJet = JetCollectionEta[i];
      double PhiJet = JetCollectionPhi[i];

      double DEta = Eta - EtaJet;
      double DPhi = Phi - PhiJet;
      if(DPhi > PI)   DPhi = DPhi - 2 * PI;
      if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
      double DR = sqrt(DPhi * DPhi + DEta * DEta);

      if(ClosestJetDR > DR)
      {
         ClosestJetDR = DR;
         ClosestJetIndex = i;
      }
   }

   return ClosestJetIndex;
}
//---------------------------------------------------------------------------
bool IsGoodMuon(NTPTreeMessenger &M, int MuonIndex)
{
   if(MuonIndex >= M.nMuon)   // what!?
      return false;

   int TrackIndex = M.trackIndexMuon[MuonIndex];
   int GlobalTrackIndex = M.combinedTrackIndexMuon[MuonIndex];
   int MuonTrackIndex = M.standAloneTrackIndexMuon[MuonIndex];

   if(TrackIndex < 0 || TrackIndex >= M.nTrack)
      return false;
   if(GlobalTrackIndex < 0 || TrackIndex >= M.nGlobalMuonTrack)
      return false;
   if(MuonTrackIndex < 0 || MuonTrackIndex >= M.nSTAMuonTrack)
      return false;

   FourVector MuonP(M.energyMuon[MuonIndex], M.pxMuon[MuonIndex], M.pyMuon[MuonIndex], M.pzMuon[MuonIndex]);
   FourVector PV(1, M.PVxPV[0], M.PVyPV[0], M.PVzPV[0]);
   FourVector MuonV(1, M.vertexXMuon[MuonIndex], M.vertexYMuon[MuonIndex], M.vertexZMuon[MuonIndex]);
   FourVector DeltaV = MuonV - PV;

   double Dxy = (-DeltaV[1] * MuonP[2] + DeltaV[2] * MuonP[1]) / MuonP.GetPT();

   if((M.muonIdMuon[MuonIndex] >> 13) % 2 == 0)   // not global muon
      return false;
   if((M.muonIdMuon[MuonIndex] >> 11) % 2 == 0)   // not tracker muon
      return false;
   if(M.trackNormalizedChi2GlobalMuonTrack[GlobalTrackIndex] > 10)
      return false;
   if(M.numberOfValidPixelBarrelHitsTrack[TrackIndex] + M.numberOfValidPixelEndcapHitsTrack[TrackIndex]
      + M.numberOfValidStripTIBHitsTrack[TrackIndex] + M.numberOfValidStripTOBHitsTrack[TrackIndex]
      + M.numberOfValidStripTIDHitsTrack[TrackIndex] + M.numberOfValidStripTECHitsTrack[TrackIndex] < 10)
      return false;
   if(M.numberOfValidPixelBarrelHitsTrack[TrackIndex] + M.numberOfValidPixelEndcapHitsTrack[TrackIndex] < 1)
      return false;
   if(M.trackValidHitsSTAMuonTrack[MuonTrackIndex] < 1)
      return false;
   if(Dxy > 0.2)
      return false;
   if(M.sumPt03Muon[MuonIndex] + M.emEt03Muon[MuonIndex] + M.hadEt03Muon[MuonIndex] > 0.1 * MuonP.GetPT())
      return false;

   return true;
}
//---------------------------------------------------------------------------
void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, bool LogY)
{
   TCanvas Canvas;

   H1->SetLineColor(1);
   H1->DrawNormalized();

   H2->SetLineColor(2);
   H2->DrawNormalized("same");

   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.AddEntry(H1, "Low", "l");
   legend.AddEntry(H2, "High", "l");
   legend.SetFillColor(0);
   legend.Draw();

   if(LogY == true)
      Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
}
//---------------------------------------------------------------------------
void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, TH1D *H3, bool LogY)
{
   TCanvas Canvas;

   H1->SetLineColor(1);
   H1->DrawNormalized();

   H2->SetLineColor(2);
   H2->DrawNormalized("same");
   
   H3->SetLineColor(3);
   H3->DrawNormalized("same");

   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.AddEntry(H1, "Low", "l");
   legend.AddEntry(H2, "Mixed", "l");
   legend.AddEntry(H3, "High", "l");
   legend.SetFillColor(0);
   legend.Draw();

   if(LogY == true)
      Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
}
//---------------------------------------------------------------------------








