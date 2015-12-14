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
#include "ReadNTPTreeV4.h"
#include "Rebin.h"
#include "SetStyle.h"
#include "SlidePreparationHelper.h"
//---------------------------------------------------------------------------
#define Tagger_TCHE 1
#define Tagger_TCHP 2
#define Tagger_JetProbability 3
#define Tagger_JetBProbability 4
#define Tagger_SSVHE 5
#define Tagger_SSVHP 6
#define Tagger_CSV 7
#define Tagger_CSVMVA 8
//---------------------------------------------------------------------------
int main(int argc, char *argv[]);
void BTaggingEfficiency(string InputList, int Tagger, double CutValue, string OutputBase, int PUMin = 0,
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

   // BTaggingEfficiency("TTbar.list", Tagger_SSVHE, 1.74, "ReproduceBTaggingEfficiencyPU_SSVHEM");
   // BTaggingEfficiency("TTbar.list", Tagger_SSVHE, 1.74, "ReproduceBTaggingEfficiencyPUSmall_SSVHEM",
   //    0, 4);
   // BTaggingEfficiency("TTbar.list", Tagger_SSVHE, 1.74, "ReproduceBTaggingEfficiencyPUMedium_SSVHEM",
   //    5, 7);
   // BTaggingEfficiency("TTbar.list", Tagger_SSVHE, 1.74, "ReproduceBTaggingEfficiencyPULarge_SSVHEM",
   //    8, 1000);
   // BTaggingEfficiency("TTbar.list", Tagger_SSVHE, 3.05, "ReproduceBTaggingEfficiencyPU_SSVHET");
   // BTaggingEfficiency("TTbar.list", Tagger_SSVHP, 2.0, "ReproduceBTaggingEfficiencyPU_SSVHEP");
   BTaggingEfficiency("TTbar.list", Tagger_TCHE, 1.7, "ReproduceBTaggingEfficiencyPUCalo_TCHEL");
   // BTaggingEfficiency("TTbar.list", Tagger_TCHE, 1.7, "ReproduceBTaggingEfficiencyPUSmallCalo_TCHEL", 0, 4);
   // BTaggingEfficiency("TTbar.list", Tagger_TCHE, 1.7, "ReproduceBTaggingEfficiencyPUMediumCalo_TCHEL", 5, 7);
   // BTaggingEfficiency("TTbar.list", Tagger_TCHE, 1.7, "ReproduceBTaggingEfficiencyPULargeCalo_TCHEL", 8, 1000);
   // BTaggingEfficiency("TTbar.list", Tagger_TCHE, 3.3, "ReproduceBTaggingEfficiencyPU_TCHEM");
   // BTaggingEfficiency("TTbar.list", Tagger_TCHE, 10.2, "ReproduceBTaggingEfficiencyPU_TCHET");
   // BTaggingEfficiency("TTbar.list", Tagger_TCHP, 1.19, "ReproduceBTaggingEfficiencyPU_TCHPL");
   // BTaggingEfficiency("TTbar.list", Tagger_TCHP, 1.93, "ReproduceBTaggingEfficiencyPU_TCHPM");
   // BTaggingEfficiency("TTbar.list", Tagger_TCHP, 3.41, "ReproduceBTaggingEfficiencyPU_TCHPT");

   return 0;
}
//---------------------------------------------------------------------------
void BTaggingEfficiency(string InputList, int Tagger, double CutValue, string OutputBase, int PUMin, int PUMax)
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
   NTPTree->SetBranchStatus("*BJetTagsAK5Jet", true);
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
   NTPTree->SetBranchStatus("energyPFMet", true);
   NTPTree->SetBranchStatus("pxPFMet", true);
   NTPTree->SetBranchStatus("pyPFMet", true);
   NTPTree->SetBranchStatus("pzPFMet", true);

   float *Tag = NULL;

   // Tagger string and links
   string TaggerString = "NoTagger";
   switch(Tagger)
   {
   case Tagger_TCHE:
      TaggerString = "TCHE";
      Tag = M.trackCountingHighEffBJetTagsAK5Jet;
      break;
   case Tagger_TCHP:
      TaggerString = "TCHP";
      Tag = M.trackCountingHighPurBJetTagsAK5Jet;
      break;
   case Tagger_JetProbability:
      TaggerString = "JetProbability";
      Tag = M.jetProbabilityBJetTagsAK5Jet;
      break;
   case Tagger_JetBProbability:
      TaggerString = "JetBProbability";
      Tag = M.jetBProbabilityBJetTagsAK5Jet;
      break;
   case Tagger_SSVHE:
      TaggerString = "SSVHE";
      Tag = M.simpleSecondaryVertexHighEffBJetTagsAK5Jet;
      break;
   case Tagger_SSVHP:
      TaggerString = "SSVHP";
      Tag = M.simpleSecondaryVertexHighPurBJetTagsAK5Jet;
      break;
   case Tagger_CSV:
      TaggerString = "CSV";
      Tag = M.combinedSecondaryVertexBJetTagsAK5Jet;
      break;
   case Tagger_CSVMVA:
      TaggerString = "CSVMVA";
      Tag = M.combinedSecondaryVertexMVABJetTagsAK5Jet;
      break;
   default:
      TaggerString = "UnknownTagger";
      Tag = NULL;
      break;
   }
   
   if(Tag == NULL)
      return;

   // Output file header
   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage("Try to reproduce b-tagging efficiency with MC");

   vector<string> ExplanationText;
   PsFile.AddTextPage(ExplanationText);

   vector<string> TableOfContentItems;
   TableOfContentItems.push_back("Basic Information");
   TableOfContentItems.push_back("Sanity checks of tracing b-hadron and match to jets");
   
   vector<string> Destinations;
   Destinations.push_back("BasicInformation");
   Destinations.push_back("Tracing");

   PsFile.AddTableOfContentPage(TableOfContentItems, Destinations);
   PsFile.InsertNamedDestination("HomePage");
   PsFile.SetAutomaticHomeButton(true, "HomePage", 50, 50, 75);

   TFile OutputFile((OutputBase + ".root").c_str(), "recreate");

   // Basic information
   TH1D HBunchCrossing("HBunchCrossing", "Bunch crossing of triggers!", 3502, -1.5, 3500.5);
   TH1D HNPV("HNPV", "Number of (good) primary vertices", 10, -0.5, 9.5);
   TH2D HPVXVsPVY("HPVXVsPVY", "PV, x vs. y, best PV;X;Y", 100, 0.1, 0.4, 100, 0.2, 0.5);
   TH2D HPVTVsPVZ("HPVTVsPVZ", "PV, transverse vs. z, best PV;Transverse;Z", 100, 0.4, 0.5, 100, -40, 40);

   // Plots about tracing B-Meson
   TH1D HBHadronPT("HBHadronPT", "PT of \"final\" b hadron", 100, 0, 500);
   TH1D HClosestJetPT("HClosestJetPT", "PT of jet closest to \"final\" b hadron", 100, 0, 500);
   TH2D HBHadronPTVsClosestJetPT("HBHadronPTVsClosestJetPT", "PT of \"final\" b hadron vs. closest jet pt;B;Jet",
      100, 0, 500, 100, 0, 500);
   TH2D HBHadronVsClosestJetDEtaDPhi("HBHadronVsClosestJetDEtaDPhi",
      "deta-dphi between \"final\" b hadron vs. closest jet;deta;dphi", 100, -2, 2, 100, -2, 2);
   TH2D HBHadronPTVsClosestJetPTSelected("HBHadronPTVsClosestJetPTSelected",
      "PT of \"final\" b hadron vs. closest jet pt, selected;B;Jet", 100, 0, 500, 100, 0, 500);
   TH2D HBHadronVsClosestJetDEtaDPhiSelected("HBHadronVsClosestJetDEtaDPhiSelected",
      "deta-dphi between \"final\" b hadron vs. closest jet, selected;deta;dphi", 100, -2, 2, 100, -2, 2);
   TH1D HJetTagDistribution("HJetTagDistribution", "Tag distribution for selected jets", 100, 0, 15);

   // Plots on PT-dependent efficiency
   TH1D HAllBJetPT("HAllBJetPT", "PT of all b-matched jets", 500, 0, 500);
   TH1D HTaggedBJetPT("HTaggedBJetPT", "PT of all b-tagged b-matched jets", 500, 0, 500);
   TH2D HAllBJetPTVsEta("HAllBJetPTVsEta", "PT vs. eta of all b-matched jets;PT;Eta", 500, 0, 500, 100, -3, 3);
   
   TH1D HAllBJetPTTightDR("HAllBJetPTTightDR", "PT of all b-matched jets, (dR < 0.1)", 500, 0, 500);
   TH1D HTaggedBJetPTTightDR("HTaggedBJetPTTightDR", "PT of all b-tagged b-matched jets (dR < 0.1)", 500, 0, 500);

   TH1D HAllBJetPTLooseDR("HAllBJetPTLooseDR", "PT of all b-matched jets, (dR < 0.4)", 500, 0, 500);
   TH1D HTaggedBJetPTLooseDR("HTaggedBJetPTLooseDR", "PT of all b-tagged b-matched jets (dR < 0.4)", 500, 0, 500);

   TH1D HAllBJetPTJECPlus("HAllBJetPTJECPlus", "PT of all b-matched jets, JEC plus", 500, 0, 500);
   TH1D HTaggedBJetPTJECPlus("HTaggedBJetPTJECPlus", "PT of all b-tagged b-matched jets, JEC plus", 500, 0, 500);
   
   TH1D HAllBJetPTJECMinus("HAllBJetPTJECMinus", "PT of all b-matched jets, JEC minus", 500, 0, 500);
   TH1D HTaggedBJetPTJECMinus("HTaggedBJetPTJECMinus", "PT of all b-tagged b-matched jets, JEC minus", 500, 0, 500);

   // Plots on Eta-dependent efficiency
   TH1D HAllBJetEta("HAllBJetEta", "Eta of all b-matched jets", 100, -3, 3);
   TH1D HTaggedBJetEta("HTaggedBJetEta", "Eta of all b-tagged b-matched jets", 100, -3, 3);
   
   // Plots on Phi-dependent efficiency
   TH1D HAllBJetPhi("HAllBJetPhi", "Phi of all b-matched jets", 100, -3.1415926535, 3.1415926535);
   TH1D HTaggedBJetPhi("HTaggedBJetPhi", "Phi of all b-tagged b-matched jets", 100, -3.1415926535, 3.1415926535);

   // Loop through events
   int NumberOfEvents = NTPTree->GetEntries();
   for(int iEvent = 0; iEvent < NumberOfEvents; iEvent++)
   {
      if((iEvent + 1) % 100000 == 0)
      {
         time_t currenttime;
         time(&currenttime);
         string stringtime = ctime(&currenttime);
         for(int i = 0; i < (int)stringtime.size(); i++)
         {
            if(stringtime[i] == '\n')
            {
               stringtime.erase(stringtime.begin() + i);
               i = i - 1;
            }
         }
         cout << "Processing entry " << iEvent + 1 << "/" << NumberOfEvents << " (" << stringtime << ")" << endl;
      }

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

         if(BestPVP[1] > 0.35)
         {
            cout << "x!" << M.PVxPV[BestPVIndex] << " " << BestPVP[1] << endl;
            cout << "y!" << M.PVyPV[BestPVIndex] << " " << BestPVP[2] << endl;
            cout << "z!" << M.PVzPV[BestPVIndex] << " " << BestPVP[4] << endl;
         }
      }
      
      if(GoodPVCount < PUMin || GoodPVCount > PUMax)
         continue;

      // Trace b-mesons from MC information
      int BFromT = max(FindChildIndex(M, 5, 6), FindChildIndex(M, -5, 6));
      int BFromTBar = max(FindChildIndex(M, 5, -6), FindChildIndex(M, -5, -6));
      int FinalBHadronFromT = TraceBHadron(M, BFromT);
      int FinalBHadronFromTBar = TraceBHadron(M, BFromTBar);
      int ClosestJetToBHadronFromT = -1;
      int ClosestJetToBHadronFromTBar = -1;
      FourVector FinalBFromTP, FinalBFromTBarP;
      FourVector ClosestJetToBHadronFromTP, ClosestJetToBHadronFromTBarP;

      if(M.etaMc[FinalBHadronFromT] > 2.4 || M.etaMc[FinalBHadronFromT] < -2.4)
         FinalBHadronFromT = -1;
      if(M.etaMc[FinalBHadronFromTBar] > 2.4 || M.etaMc[FinalBHadronFromTBar] < -2.4)
         FinalBHadronFromTBar = -1;

      if(FinalBHadronFromT >= 0)
         FinalBFromTP.SetSizeEtaPhiEnergy(M.pMc[FinalBHadronFromT], M.etaMc[FinalBHadronFromT],
            M.phiMc[FinalBHadronFromT], M.energyMc[FinalBHadronFromT]);
      if(FinalBHadronFromTBar >= 0)
         FinalBFromTBarP.SetSizeEtaPhiEnergy(M.pMc[FinalBHadronFromTBar], M.etaMc[FinalBHadronFromTBar],
            M.phiMc[FinalBHadronFromTBar], M.energyMc[FinalBHadronFromTBar]);
      if(FinalBHadronFromT >= 0)
      {
         ClosestJetToBHadronFromT = FindClosestJet(M.etaAK5Jet, M.phiAK5Jet, M.nAK5Jet,
            M.etaMc[FinalBHadronFromT], M.phiMc[FinalBHadronFromT]);
         if(ClosestJetToBHadronFromT >= 0)
            ClosestJetToBHadronFromTP = FourVector(M.energyAK5Jet[ClosestJetToBHadronFromT],
               M.pxAK5Jet[ClosestJetToBHadronFromT],
               M.pyAK5Jet[ClosestJetToBHadronFromT],
               M.pzAK5Jet[ClosestJetToBHadronFromT]);
      }
      if(FinalBHadronFromTBar >= 0)
      {
         ClosestJetToBHadronFromTBar = FindClosestJet(M.etaAK5Jet, M.phiAK5Jet, M.nAK5Jet,
            M.etaMc[FinalBHadronFromTBar], M.phiMc[FinalBHadronFromTBar]);
         if(ClosestJetToBHadronFromTBar >= 0)
            ClosestJetToBHadronFromTBarP = FourVector(M.energyAK5Jet[ClosestJetToBHadronFromTBar],
               M.pxAK5Jet[ClosestJetToBHadronFromTBar],
               M.pyAK5Jet[ClosestJetToBHadronFromTBar],
               M.pzAK5Jet[ClosestJetToBHadronFromTBar]);
      }

      HBHadronPT.Fill(FinalBFromTP.GetPT());
      HBHadronPT.Fill(FinalBFromTBarP.GetPT());
      HClosestJetPT.Fill(ClosestJetToBHadronFromTP.GetPT());
      HClosestJetPT.Fill(ClosestJetToBHadronFromTBarP.GetPT());
      HBHadronPTVsClosestJetPT.Fill(FinalBFromTP.GetPT(), ClosestJetToBHadronFromTP.GetPT());
      HBHadronPTVsClosestJetPT.Fill(FinalBFromTBarP.GetPT(), ClosestJetToBHadronFromTBarP.GetPT());
      HBHadronVsClosestJetDEtaDPhi.Fill(FinalBFromTP.GetEta() - ClosestJetToBHadronFromTP.GetEta(),
         GetDPhi(FinalBFromTP, ClosestJetToBHadronFromTP));
      HBHadronVsClosestJetDEtaDPhi.Fill(FinalBFromTBarP.GetEta() - ClosestJetToBHadronFromTBarP.GetEta(),
         GetDPhi(FinalBFromTBarP, ClosestJetToBHadronFromTBarP));

      // Calculate MR, R
      vector<FourVector> GoodJets;
      for(int i = 0; i < M.nAK5Jet; i++)
      {
         /*
         if(M.neutralHadronEnergyAK5Jet[i] / M.energyAK5Jet[i] >= 0.99)
            continue;
         if(M.neutralEmEnergyAK5Jet[i] / M.energyAK5Jet[i] >= 0.99)
            continue;
         if(M.chargedHadronMultiplicityAK5Jet[i]
            + M.neutralHadronMultiplicityAK5Jet[i]
            + M.photonMultiplicityAK5Jet[i]
            + M.electronMultiplicityAK5Jet[i]
            + M.muonMultiplicityAK5Jet[i]
            + M.HFHadronMultiplicityAK5Jet[i]
            + M.HFEMMultiplicityAK5Jet[i] <= 1)
            continue;
         if(M.etaAK5Jet[i] < 2.4 && M.etaAK5Jet[i] > -2.4)
         {
            if(M.chargedHadronEnergyAK5Jet[i] / M.energyAK5Jet[i] <= 0)
               continue;
            if(M.chargedHadronMultiplicityAK5Jet[i] + M.electronMultiplicityAK5Jet[i]
               + M.muonMultiplicityAK5Jet[i] <= 0)
               continue;
            if(M.chargedEmEnergyAK5Jet[i] / M.energyAK5Jet[i] >= 0.99)
               continue;
         }
         */

         if(M.pxAK5Jet[i] * M.pxAK5Jet[i] + M.pyAK5Jet[i] * M.pyAK5Jet[i] < 40 * 40)
            continue;
         if(M.etaAK5Jet[i] > 2.4 || M.etaAK5Jet[i] < -2.4)
            continue;

         GoodJets.push_back(FourVector(M.energyAK5Jet[i], M.pxAK5Jet[i], M.pyAK5Jet[i], M.pzAK5Jet[i]));
      }

      vector<FourVector> Hemispheres = SplitIntoGroups(GoodJets);

      double EventMR = GetMR(Hemispheres[0], Hemispheres[1]);
      double EventR = GetR(Hemispheres[0], Hemispheres[1],
         FourVector(M.energyPFMet[0], M.pxPFMet[0], M.pyPFMet[0], M.pzPFMet[0]));

      // For now on, select only events with 2 good b's and 2 good matches - and some minimum energy
      if(FinalBHadronFromT < 0 || FinalBHadronFromTBar < 0)   continue;
      if(FinalBFromTP.GetPT() < 30 || FinalBFromTBarP.GetPT() < 30)   continue;
      if(ClosestJetToBHadronFromTP.GetPT() < 30 || ClosestJetToBHadronFromTBarP.GetPT() < 30)   continue;
      
      if(GetDR(FinalBFromTP, ClosestJetToBHadronFromTP) < 0.25 &&
         GetDR(FinalBFromTBarP, ClosestJetToBHadronFromTBarP) < 0.25)
      {
         HBHadronPTVsClosestJetPTSelected.Fill(FinalBFromTP.GetPT(), ClosestJetToBHadronFromTP.GetPT());
         HBHadronPTVsClosestJetPTSelected.Fill(FinalBFromTBarP.GetPT(), ClosestJetToBHadronFromTBarP.GetPT());
         HBHadronVsClosestJetDEtaDPhiSelected.Fill(FinalBFromTP.GetEta() - ClosestJetToBHadronFromTP.GetEta(),
            GetDPhi(FinalBFromTP, ClosestJetToBHadronFromTP));
         HBHadronVsClosestJetDEtaDPhiSelected.Fill(FinalBFromTBarP.GetEta() - ClosestJetToBHadronFromTBarP.GetEta(),
            GetDPhi(FinalBFromTBarP, ClosestJetToBHadronFromTBarP));
         HJetTagDistribution.Fill(Tag[ClosestJetToBHadronFromT]);
         HJetTagDistribution.Fill(Tag[ClosestJetToBHadronFromTBar]);
      }

      if(GetDR(FinalBFromTP, ClosestJetToBHadronFromTP) < 0.25 &&
         GetDR(FinalBFromTBarP, ClosestJetToBHadronFromTBarP) < 0.25)
      {
         HAllBJetPT.Fill(ClosestJetToBHadronFromTP.GetPT());
         if(Tag[ClosestJetToBHadronFromT] > CutValue)
            HTaggedBJetPT.Fill(ClosestJetToBHadronFromTP.GetPT());
         HAllBJetPTVsEta.Fill(ClosestJetToBHadronFromTP.GetPT(), ClosestJetToBHadronFromTP.GetEta());
         HAllBJetPT.Fill(ClosestJetToBHadronFromTBarP.GetPT());
         if(Tag[ClosestJetToBHadronFromTBar] > CutValue)
            HTaggedBJetPT.Fill(ClosestJetToBHadronFromTBarP.GetPT());
         HAllBJetPTVsEta.Fill(ClosestJetToBHadronFromTBarP.GetPT(), ClosestJetToBHadronFromTBarP.GetEta());
      
         double JECPercentage = 0.05;

         HAllBJetPTJECPlus.Fill(ClosestJetToBHadronFromTP.GetPT() * (1 + JECPercentage));
         if(Tag[ClosestJetToBHadronFromT] > CutValue)
            HTaggedBJetPTJECPlus.Fill(ClosestJetToBHadronFromTP.GetPT() * (1 + JECPercentage));
         HAllBJetPTJECPlus.Fill(ClosestJetToBHadronFromTBarP.GetPT() * (1 + JECPercentage));
         if(Tag[ClosestJetToBHadronFromTBar] > CutValue)
            HTaggedBJetPTJECPlus.Fill(ClosestJetToBHadronFromTBarP.GetPT() * (1 + JECPercentage));
         
         HAllBJetPTJECMinus.Fill(ClosestJetToBHadronFromTP.GetPT() * (1 - JECPercentage));
         if(Tag[ClosestJetToBHadronFromT] > CutValue)
            HTaggedBJetPTJECMinus.Fill(ClosestJetToBHadronFromTP.GetPT() * (1 - JECPercentage));
         HAllBJetPTJECMinus.Fill(ClosestJetToBHadronFromTBarP.GetPT() * (1 - JECPercentage));
         if(Tag[ClosestJetToBHadronFromTBar] > CutValue)
            HTaggedBJetPTJECMinus.Fill(ClosestJetToBHadronFromTBarP.GetPT() * (1 - JECPercentage));
         
         HAllBJetEta.Fill(ClosestJetToBHadronFromTP.GetEta());
         if(Tag[ClosestJetToBHadronFromT] > CutValue)
            HTaggedBJetEta.Fill(ClosestJetToBHadronFromTP.GetEta());
         HAllBJetEta.Fill(ClosestJetToBHadronFromTBarP.GetEta());
         if(Tag[ClosestJetToBHadronFromTBar] > CutValue)
            HTaggedBJetEta.Fill(ClosestJetToBHadronFromTBarP.GetEta());
      
         HAllBJetPhi.Fill(ClosestJetToBHadronFromTP.GetPhi());
         if(Tag[ClosestJetToBHadronFromT] > CutValue)
            HTaggedBJetPhi.Fill(ClosestJetToBHadronFromTP.GetPhi());
         HAllBJetPhi.Fill(ClosestJetToBHadronFromTBarP.GetPhi());
         if(Tag[ClosestJetToBHadronFromTBar] > CutValue)
            HTaggedBJetPhi.Fill(ClosestJetToBHadronFromTBarP.GetPhi());
      }
      
      if(GetDR(FinalBFromTP, ClosestJetToBHadronFromTP) < 0.1 &&
         GetDR(FinalBFromTBarP, ClosestJetToBHadronFromTBarP) < 0.1)
      {
         HAllBJetPTTightDR.Fill(ClosestJetToBHadronFromTP.GetPT());
         if(Tag[ClosestJetToBHadronFromT] > CutValue)
            HTaggedBJetPTTightDR.Fill(ClosestJetToBHadronFromTP.GetPT());
         HAllBJetPTTightDR.Fill(ClosestJetToBHadronFromTBarP.GetPT());
         if(Tag[ClosestJetToBHadronFromTBar] > CutValue)
            HTaggedBJetPTTightDR.Fill(ClosestJetToBHadronFromTBarP.GetPT());
      }   
      
      if(GetDR(FinalBFromTP, ClosestJetToBHadronFromTP) < 0.4 &&
         GetDR(FinalBFromTBarP, ClosestJetToBHadronFromTBarP) < 0.4)
      {
         HAllBJetPTLooseDR.Fill(ClosestJetToBHadronFromTP.GetPT());
         if(Tag[ClosestJetToBHadronFromT] > CutValue)
            HTaggedBJetPTLooseDR.Fill(ClosestJetToBHadronFromTP.GetPT());
         HAllBJetPTLooseDR.Fill(ClosestJetToBHadronFromTBarP.GetPT());
         if(Tag[ClosestJetToBHadronFromTBar] > CutValue)
            HTaggedBJetPTLooseDR.Fill(ClosestJetToBHadronFromTBarP.GetPT());
      }   
   }

   // Write to output
   PsFile.AddTextPage("Basic information");
   PsFile.InsertNamedDestination("BasicInformation");
   PsFile.AddPlot(HBunchCrossing, "", true);
   PsFile.AddPlot(HNPV, "hist text00", true);
   PsFile.AddPlot(HPVXVsPVY, "colz", false, true);
   PsFile.AddPlot(HPVTVsPVZ, "colz", false, true);

   PsFile.AddTextPage("Tracing b-hadron");
   PsFile.InsertNamedDestination("Tracing");
   PsFile.AddPlot(HBHadronPT, "", true);
   PsFile.AddPlot(HClosestJetPT, "", true);
   PsFile.AddPlot(HBHadronPTVsClosestJetPT, "colz", false, true);
   PsFile.AddPlot(HBHadronVsClosestJetDEtaDPhi, "colz", false, true);
   PsFile.AddPlot(HBHadronPTVsClosestJetPTSelected, "colz", false, true);
   PsFile.AddPlot(HBHadronVsClosestJetDEtaDPhiSelected, "colz", false, true);
   PsFile.AddPlot(HJetTagDistribution, "", true);

   PsFile.AddTextPage("Attempt at calcuating b-jet efficiency");
   PsFile.InsertNamedDestination("BJetEfficiency");
   PsFile.AddPlot(HAllBJetPTVsEta, "colz", false);   HAllBJetPTVsEta.Write();
   PsFile.AddPlot(HAllBJetPT, "", true);   HAllBJetPT.Write();
   PsFile.AddPlot(HTaggedBJetPT, "", true);   HTaggedBJetPT.Write();

   double JetPTBinsTemp[] = {40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100,
      105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 160, 170, 180, 190, 200,
      225, 250, 275, 300, 350, 400, 500};
   vector<double> JetPTBins(JetPTBinsTemp, JetPTBinsTemp + 38);

   TH1D HAllBJetPT_Rebin = Rebin(HAllBJetPT, JetPTBins, "HAllBJetPT_Rebin");
   TH1D HTaggedBJetPT_Rebin = Rebin(HTaggedBJetPT, JetPTBins, "HTaggedBJetPT_Rebin");
   
   TH1D HAllBJetPTTightDR_Rebin = Rebin(HAllBJetPTTightDR, JetPTBins, "HAllBJetPTTightDR_Rebin");
   TH1D HTaggedBJetPTTightDR_Rebin = Rebin(HTaggedBJetPTTightDR, JetPTBins, "HTaggedBJetPTTightDR_Rebin");
   
   TH1D HAllBJetPTLooseDR_Rebin = Rebin(HAllBJetPTLooseDR, JetPTBins, "HAllBJetPTLooseDR_Rebin");
   TH1D HTaggedBJetPTLooseDR_Rebin = Rebin(HTaggedBJetPTLooseDR, JetPTBins, "HTaggedBJetPTLooseDR_Rebin");
   
   TH1D HAllBJetPTJECPlus_Rebin = Rebin(HAllBJetPTJECPlus, JetPTBins, "HAllBJetPTJECPlus_Rebin");
   TH1D HTaggedBJetPTJECPlus_Rebin = Rebin(HTaggedBJetPTJECPlus, JetPTBins, "HTaggedBJetPTJECPlus_Rebin");
   
   TH1D HAllBJetPTJECMinus_Rebin = Rebin(HAllBJetPTJECMinus, JetPTBins, "HAllBJetPTJECMinus_Rebin");
   TH1D HTaggedBJetPTJECMinus_Rebin = Rebin(HTaggedBJetPTJECMinus, JetPTBins, "HTaggedBJetPTJECMinus_Rebin");
   
   TGraphAsymmErrors GTaggedBJetPTEfficiency;
   GTaggedBJetPTEfficiency.BayesDivide(&HTaggedBJetPT_Rebin, &HAllBJetPT_Rebin, "");
   GTaggedBJetPTEfficiency.SetNameTitle("GTaggedBJetPTEfficiency", "Efficiency as a function of PT");
   PsFile.AddPlot(GTaggedBJetPTEfficiency, "ape", false, false, true);
   
   TGraphAsymmErrors GTaggedBJetPTEfficiencyTightDR;
   GTaggedBJetPTEfficiencyTightDR.BayesDivide(&HTaggedBJetPTTightDR_Rebin, &HAllBJetPTTightDR_Rebin, "");
   GTaggedBJetPTEfficiencyTightDR.SetNameTitle("GTaggedBJetPTEfficiencyTightDR",
      "Efficiency as a function of PT (dR < 0.1)");
   PsFile.AddPlot(GTaggedBJetPTEfficiencyTightDR, "ape", false, false, true);

   TGraphAsymmErrors GTaggedBJetPTEfficiencyLooseDR;
   GTaggedBJetPTEfficiencyLooseDR.BayesDivide(&HTaggedBJetPTLooseDR_Rebin, &HAllBJetPTLooseDR_Rebin, "");
   GTaggedBJetPTEfficiencyLooseDR.SetNameTitle("GTaggedBJetPTEfficiencyLooseDR",
      "Efficiency as a function of PT (dR < 0.4)");
   PsFile.AddPlot(GTaggedBJetPTEfficiencyLooseDR, "ape", false, false, true);

   TCanvas CTaggedBJetPTEfficiencyDR;
   GTaggedBJetPTEfficiency.SetLineColor(kBlack);
   GTaggedBJetPTEfficiencyTightDR.SetLineColor(kRed);
   GTaggedBJetPTEfficiencyLooseDR.SetLineColor(kBlue);
   GTaggedBJetPTEfficiency.Draw("ape");
   GTaggedBJetPTEfficiencyTightDR.Draw("pe");
   GTaggedBJetPTEfficiencyLooseDR.Draw("pe");
   CTaggedBJetPTEfficiencyDR.SetGridx();
   CTaggedBJetPTEfficiencyDR.SetGridy();
   TLegend LegendTaggedBJetPTEfficiencyDR(0.65, 0.95, 0.95, 0.75);
   LegendTaggedBJetPTEfficiencyDR.SetFillColor(0);
   LegendTaggedBJetPTEfficiencyDR.AddEntry(&GTaggedBJetPTEfficiency, "Central value (DR < 0.25)", "l");
   LegendTaggedBJetPTEfficiencyDR.AddEntry(&GTaggedBJetPTEfficiencyTightDR, "DR < 0.1", "l");
   LegendTaggedBJetPTEfficiencyDR.AddEntry(&GTaggedBJetPTEfficiencyLooseDR, "DR < 0.4", "l");
   LegendTaggedBJetPTEfficiencyDR.Draw();
   PsFile.AddCanvas(CTaggedBJetPTEfficiencyDR);

   TGraphAsymmErrors GTaggedBJetPTEfficiencyDRBand;
   for(int i = 0; i < GTaggedBJetPTEfficiency.GetN(); i++)
   {
      double X, Y;
      GTaggedBJetPTEfficiency.GetPoint(i, X, Y);
      double EXL = GTaggedBJetPTEfficiency.GetErrorXlow(i);
      double EXH = GTaggedBJetPTEfficiency.GetErrorXhigh(i);

      double YH, YL;
      GTaggedBJetPTEfficiencyTightDR.GetPoint(i, X, YH);
      GTaggedBJetPTEfficiencyLooseDR.GetPoint(i, X, YL);

      GTaggedBJetPTEfficiencyDRBand.SetPoint(i, X, Y);
      GTaggedBJetPTEfficiencyDRBand.SetPointError(i, EXL, EXH, fabs(Y - YL), fabs(YH - Y));
   }
   GTaggedBJetPTEfficiencyDRBand.SetNameTitle("GTaggedBJetPTEfficiencyDRBand",
      "Uncertainty band estimated by changing dR during matching");
   GTaggedBJetPTEfficiencyDRBand.SetFillStyle(3001);
   GTaggedBJetPTEfficiencyDRBand.SetFillColor(kYellow);

   TCanvas CTaggedBJetPTEfficiencyDRBand;
   GTaggedBJetPTEfficiency.Draw("ape");
   GTaggedBJetPTEfficiencyDRBand.Draw("3");
   GTaggedBJetPTEfficiency.Draw("pe");
   PsFile.AddCanvas(CTaggedBJetPTEfficiencyDRBand);
   
   TCanvas CTaggedBJetPTEfficiencyDRBandSquare("CTaggedBJetPTEfficiencyDRBandSquare",
      "CTaggedBJetPTEfficiencyDRBandSquare", 1024, 1024);
   GTaggedBJetPTEfficiency.Draw("ape");
   GTaggedBJetPTEfficiencyDRBand.Draw("3");
   GTaggedBJetPTEfficiency.Draw("pe");
   GTaggedBJetPTEfficiency.GetXaxis()->SetTitle("Jet PT (GeV/c)");
   GTaggedBJetPTEfficiency.GetYaxis()->SetTitle("b-tagging efficiency");
   CTaggedBJetPTEfficiencyDRBandSquare.SaveAs((OutputBase + "_Efficiency.png").c_str());
   CTaggedBJetPTEfficiencyDRBandSquare.SaveAs((OutputBase + "_Efficiency.C").c_str());
   CTaggedBJetPTEfficiencyDRBandSquare.SaveAs((OutputBase + "_Efficiency.eps").c_str());
   
   TGraphAsymmErrors GTaggedBJetPTEfficiencyJECPlus;
   GTaggedBJetPTEfficiencyJECPlus.BayesDivide(&HTaggedBJetPTJECPlus_Rebin, &HAllBJetPTJECPlus_Rebin, "");
   GTaggedBJetPTEfficiencyJECPlus.SetNameTitle("GTaggedBJetPTEfficiencyJECPlus", "Efficiency as a function of PT (JEC++)");
   PsFile.AddPlot(GTaggedBJetPTEfficiencyJECPlus, "ape", false, false, true);

   TGraphAsymmErrors GTaggedBJetPTEfficiencyJECMinus;
   GTaggedBJetPTEfficiencyJECMinus.BayesDivide(&HTaggedBJetPTJECMinus_Rebin, &HAllBJetPTJECMinus_Rebin, "");
   GTaggedBJetPTEfficiencyJECMinus.SetNameTitle("GTaggedBJetPTEfficiencyJECMinus",
      "Efficiency as a function of PT (JEC--)");
   PsFile.AddPlot(GTaggedBJetPTEfficiencyJECMinus, "ape", false, false, true);

   TCanvas CTaggedBJetPTEfficiencyJEC;
   GTaggedBJetPTEfficiency.SetLineColor(kBlack);
   GTaggedBJetPTEfficiencyJECPlus.SetLineColor(kRed);
   GTaggedBJetPTEfficiencyJECMinus.SetLineColor(kBlue);
   GTaggedBJetPTEfficiency.Draw("ape");
   GTaggedBJetPTEfficiencyJECPlus.Draw("pe");
   GTaggedBJetPTEfficiencyJECMinus.Draw("pe");
   CTaggedBJetPTEfficiencyJEC.SetGridx();
   CTaggedBJetPTEfficiencyJEC.SetGridy();
   TLegend LegendTaggedBJetPTEfficiencyJEC(0.65, 0.95, 0.95, 0.75);
   LegendTaggedBJetPTEfficiencyJEC.SetFillColor(0);
   LegendTaggedBJetPTEfficiencyJEC.AddEntry(&GTaggedBJetPTEfficiency, "Central value", "l");
   LegendTaggedBJetPTEfficiencyJEC.AddEntry(&GTaggedBJetPTEfficiencyJECPlus, "JEC++", "l");
   LegendTaggedBJetPTEfficiencyJEC.AddEntry(&GTaggedBJetPTEfficiencyJECMinus, "JEC--", "l");
   LegendTaggedBJetPTEfficiencyJEC.Draw();
   PsFile.AddCanvas(CTaggedBJetPTEfficiencyJEC);
   
   TGraphAsymmErrors GTaggedBJetPTEfficiencyJECBand;
   GTaggedBJetPTEfficiencyJECBand.SetNameTitle("GTaggedBJetPTEfficiencyJECBand",
      "Uncertainty band estimated by changing JEC");
   for(int i = 0; i < GTaggedBJetPTEfficiency.GetN(); i++)
   {
      double X, Y;
      GTaggedBJetPTEfficiency.GetPoint(i, X, Y);
      double EXL = GTaggedBJetPTEfficiency.GetErrorXlow(i);
      double EXH = GTaggedBJetPTEfficiency.GetErrorXhigh(i);

      double YH, YL;
      GTaggedBJetPTEfficiencyJECPlus.GetPoint(i, X, YH);
      GTaggedBJetPTEfficiencyJECMinus.GetPoint(i, X, YL);

      GTaggedBJetPTEfficiencyJECBand.SetPoint(i, X, Y);
      GTaggedBJetPTEfficiencyJECBand.SetPointError(i, EXL, EXH, fabs(Y - YL), fabs(YH - Y));
   }
   GTaggedBJetPTEfficiencyJECBand.SetFillStyle(3002);
   GTaggedBJetPTEfficiencyJECBand.SetFillColor(kGreen);

   TCanvas CTaggedBJetPTEfficiencyJECBand;
   GTaggedBJetPTEfficiency.Draw("ape");
   GTaggedBJetPTEfficiencyJECBand.Draw("3");
   GTaggedBJetPTEfficiency.Draw("pe");
   PsFile.AddCanvas(CTaggedBJetPTEfficiencyJECBand); 

   HAllBJetEta.Sumw2();
   HTaggedBJetEta.Sumw2();
   PsFile.AddPlot(HAllBJetEta, "", false);   HAllBJetEta.Write();
   PsFile.AddPlot(HTaggedBJetEta, "", false);   HTaggedBJetEta.Write();

   TGraphAsymmErrors GTaggedBJetEtaEfficiency;
   GTaggedBJetEtaEfficiency.BayesDivide(&HTaggedBJetEta, &HAllBJetEta, "");
   GTaggedBJetEtaEfficiency.SetTitle("Efficiency as a function of eta");
   PsFile.AddPlot(GTaggedBJetEtaEfficiency, "ape", false, false, true);
   
   HAllBJetPhi.Sumw2();
   HTaggedBJetPhi.Sumw2();
   PsFile.AddPlot(HAllBJetPhi, "", false);
   PsFile.AddPlot(HTaggedBJetPhi, "", false);

   TGraphAsymmErrors GTaggedBJetPhiEfficiency;
   GTaggedBJetPhiEfficiency.BayesDivide(&HTaggedBJetPhi, &HAllBJetPhi, "");
   GTaggedBJetPhiEfficiency.SetTitle("Efficiency as a function of phi");
   PsFile.AddPlot(GTaggedBJetPhiEfficiency, "ape", false, false, true);
   
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








