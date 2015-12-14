#include <iostream>
#include <string>
#include <vector>
#include <deque>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"

#include "PlotHelper2.h"
#include "ChainAll.h"
#include "GenparticleTree.h"
#include "TauHelperFunctions2.h"
#include "SetStyle.h"

#include "ReadNTPTreeV4.h"

int main(int argc, char *argv[]);
bool muonPassLoose(NTPTreeMessenger &M, int index);
bool electronPassWP95(NTPTreeMessenger &M, int index);

int main(int argc, char *argv[])
{
   SetStyle();

   TChain *Tree = ChainAll("ZbbList", "ntp1");
   if(Tree == NULL)
      return -1;

   NTPTreeMessenger M;
   M.SetBranchAddress(Tree);
   M.InitializeWeight("Samples/BookKeeping/7222ReRun_HTRun2011Av4.PU.root");

   Tree->SetBranchStatus("*", false);
   Tree->SetBranchStatus("*PU", true);
   Tree->SetBranchStatus("*Mc", true);
   Tree->SetBranchStatus("*AK5Jet", true);
   Tree->SetBranchStatus("*PFMet", true);
   Tree->SetBranchStatus("*Ele", true);
   Tree->SetBranchStatus("*SC", true);
   Tree->SetBranchStatus("rhoFastjet", true);
   Tree->SetBranchStatus("expInnerLayersGsfTrack", true);
   Tree->SetBranchStatus("*Muon", true);
   Tree->SetBranchStatus("*Track", true);

   TFile F("ZbbPlots.root", "RECREATE");

   TTree OutputTree("MRTree", "MRTree");
   double TreeMR = 0;
   double TreeR = 0;
   double TreeFactor = 0;
   OutputTree.Branch("MR", &TreeMR, "MR/D");
   OutputTree.Branch("R", &TreeR, "R/D");
   OutputTree.Branch("Factor", &TreeFactor, "Factor/D");

   TH1D HMCTauCount("HMCTauCount", "Number of MC taus (from Z) in the event", 5, -0.5, 4.5);
   TH1D HMCTauChildrenCount("HMCTauChildrenCount", "Number of children (final) from taus", 20, -0.5, 19.5);
   TH1D HMCTauChildrenSpread("HMCTauChildrenSpread", "Spread of children (final) from taus (PT > 1 GeV)", 100, 0, 3);

   TH1D HMCTauClosestJetDR("HMCTauClosestJetDR",
      "DeltaR from tau to closest jet (jet PT > 20, tau PT > 20);DeltaR", 100, 0, 3);
   TH1D HMCTauClosestJetPTRatio("HMCTauClosestJetPTRatio",
      "PT ratio from tau to closest jet (jet PT > 20, tau PT > 20);PT Jet / PT Tau", 100, 0, 5);
   TH2D HMCTauClosestJetDRVsPTRatio("HMCTauClosestJetDRVsPTRatio",
      "DeltaR vs. PT ratio from tau to closest jet (jet PT > 20, tau PT > 20);DeltaR;PT Jet / PT Tau",
      100, 0, 3, 100, 0, 5);

   TH1D HMRNew("HMRNew", "MR (new) after single-lepton-neutrino treatment;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New005("HMRNew_R2New005",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.05;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New010("HMRNew_R2New010",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.10;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New015("HMRNew_R2New015",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.15;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New020("HMRNew_R2New020",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.20;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New025("HMRNew_R2New025",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.25;MR (new)", 40, 0, 1500);
   
   TH1D HR2New("HR2New", "R^{2} (new) after single-lepton-neutrino treatment;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew300("HR2New_MRNew300",
      "R^{2} (new) after single-lepton-neutrino treatment, MR (new) > 300;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew400("HR2New_MRNew400",
      "R^{2} (new) after single-lepton-neutrino treatment, MR (new) > 400;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew500("HR2New_MRNew500",
      "R^{2} (new) after single-lepton-neutrino treatment, MR (new) > 500;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew600("HR2New_MRNew600",
      "R^{2} (new) after single-lepton-neutrino treatment, MR (new) > 600;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew700("HR2New_MRNew700",
      "R^{2} (new) after single-lepton-neutrino treatment, MR (new) > 700;R^{2} (new)", 40, 0, 1.2);

   TH1D HMRNew_MRNew300("HMRNew_MRNew300",
      "MR (new) after single-lepton-neutrino treatment, MR(new) > 300;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New005("HMRNew_MRNew300_R2New005",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.05, MR (new) > 300;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New010("HMRNew_MRNew300_R2New010",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.10, MR (new) > 300;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New015("HMRNew_MRNew300_R2New015",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.15, MR (new) > 300;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New020("HMRNew_MRNew300_R2New020",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.20, MR (new) > 300;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New025("HMRNew_MRNew300_R2New025",
      "MR (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.25, MR (new) > 300;MR (new)", 40, 0, 1500);
   
   TH1D HR2New_R2New015("HR2New_R2New015",
      "R^{2} (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.15;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew300_R2New015("HR2New_MRNew300_R2New015",
      "R^{2} (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.15, MR (new) > 300;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew400_R2New015("HR2New_MRNew400_R2New015",
      "R^{2} (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.15, MR (new) > 400;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew500_R2New015("HR2New_MRNew500_R2New015",
      "R^{2} (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.15, MR (new) > 500;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew600_R2New015("HR2New_MRNew600_R2New015",
      "R^{2} (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.15, MR (new) > 600;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew700_R2New015("HR2New_MRNew700_R2New015",
      "R^{2} (new) after single-lepton-neutrino treatment, R^{2} (new) > 0.15, MR (new) > 700;R^{2} (new)", 40, 0, 1.2);

   double TotalWeight = 0;

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 100000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;
      // if(iEntry >= 1000000)
      //    break;

      Tree->GetEntry(iEntry);

      double WPU = M.GetCurrentWeight();
      TotalWeight = TotalWeight + WPU;

      // Convert to GenParticleTree
      vector<GenParticle> GenParticles;
      for(int i = 0; i < M.nMc; i++)
      {
         GenParticle Particle;
         Particle.P[0] = M.energyMc[i];
         Particle.P[1] = M.pMc[i] / cosh(M.etaMc[i]) * cos(M.phiMc[i]);
         Particle.P[2] = M.pMc[i] / cosh(M.etaMc[i]) * sin(M.phiMc[i]);
         Particle.P[3] = M.pMc[i] * tanh(M.etaMc[i]);
         Particle.PDGID = M.idMc[i];
         Particle.StatusCode = M.statusMc[i];
         GenParticles.push_back(Particle);
      }
      for(int i = 0; i < M.nMc; i++)
      {
         if(M.mothMc[i] >= 0)
         {
            GenParticles[i].Mothers.push_back(M.mothMc[i]);
            GenParticles[M.mothMc[i]].Daughters.push_back(i);
         }
      }
      GenParticleTree MCTree(GenParticles, 1, iEntry);

      // find the Z boson
      int VBIndex = -1;
      for(int i = 0; i < MCTree.ParticleCount(); i++)
      {
         if(MCTree[i].StatusCode == 2)
            continue;
         if(MCTree[i].PDGID != 23)
            continue;
         VBIndex = i;
      }

      // recycle each event twice - once with each lepton
      vector<int> VBChildren = MCTree[VBIndex].Daughters;
      for(int i = 0; i < (int)VBChildren.size(); i++)
      {
         FourVector LeptonP(MCTree[VBChildren[i]].P);

         // 60 GeV jet x2
         int CaloJetCount60 = 0;
         for(int j = 0; j < M.nAK5Jet; j++)
         {
            if(M.pxAK5Jet[j] * M.pxAK5Jet[j] + M.pyAK5Jet[j] * M.pyAK5Jet[j] < 60 * 60)
               continue;
            if(M.etaAK5Jet[j] < 3 && M.etaAK5Jet[j] > -3)
               CaloJetCount60 = CaloJetCount60 + 1;
         }
         if(CaloJetCount60 < 2)
            continue;

         // double-medium tag
         int JetPassBTagLoose = 0;
         for(int j = 0; j < M.nAK5Jet; j++)
         {
            if(M.pxAK5Jet[j] * M.pxAK5Jet[j] + M.pyAK5Jet[j] * M.pyAK5Jet[j] < 80 * 80)
               continue;
            if(M.etaAK5Jet[j] < -3 || M.etaAK5Jet[j] > 3)
               continue;
            if(M.trackCountingHighEffBJetTagsAK5Jet[j] > 1.7)
               JetPassBTagLoose = JetPassBTagLoose + 1;
         }
         if(JetPassBTagLoose < 2)
            continue;

         // Reject events with good electron or muon
         int GoodElectronCount = 0;
         for(int j = 0; j < M.nEle; j++)
         {
            FourVector Momentum(0, M.pxEle[j], M.pyEle[j], M.pzEle[j]);
            if(GetDR(Momentum, LeptonP) < 0.25)
               continue;

            if(M.pxEle[j] * M.pxEle[j] + M.pyEle[j] * M.pyEle[j] < 20 * 20)
               continue;
            if(electronPassWP95(M, j) == true)
               GoodElectronCount = GoodElectronCount + 1;
         }

         FourVector MuonP;
         bool DecayToMuon = false;
         int GoodMuonCount = 0;
         for(int j = 0; j < M.nMuon; j++)
         {
            FourVector Momentum(0, M.pxMuon[j], M.pyMuon[j], M.pzMuon[j]);
            if(GetDR(Momentum, LeptonP) < 0.25)
            {
               DecayToMuon = true;
               continue;
            }

            if(M.pxMuon[j] * M.pxMuon[j] + M.pyMuon[j] * M.pyMuon[j] < 20 * 20)
               continue;
            if(muonPassLoose(M, j) == true)
            {
               GoodMuonCount = GoodMuonCount + 1;
               MuonP[0] = M.energyMuon[j];
               MuonP[1] = M.pxMuon[j];
               MuonP[2] = M.pyMuon[j];
               MuonP[3] = M.pzMuon[j];
            }
         }

         if(GoodElectronCount >= 1)
            continue;
         if(GoodMuonCount != 1)
            continue;

         // Calculate MR and R
         bool JetMatched = false;
         vector<FourVector> GoodJets;
         for(int j = 0; j < M.nAK5Jet; j++)
         {
            FourVector JetP(M.energyAK5Jet[j], M.pxAK5Jet[j], M.pyAK5Jet[j], M.pzAK5Jet[j]);
            if(fabs(JetP.GetEta()) > 3)
               continue;
            if(fabs(MCTree[VBChildren[i]].PDGID) == 11
               || (fabs(MCTree[VBChildren[i]].PDGID) == 15 && DecayToMuon == false))
            {
               if(GetDR(JetP, LeptonP) < 0.5)   // exclude possible lepton (and decay products)
               {
                  JetMatched = true;
                  continue;
               }
            }
            if(JetP.GetPT() < 40)
               continue;
            
            GoodJets.push_back(JetP);
         }
         if(GoodJets.size() < 2 || GoodJets.size() > 20)
            continue;
         vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

         FourVector PFMET(0, M.pxPFMet[0], M.pyPFMet[0], 0);
         if(JetMatched == true)
            PFMET = PFMET + LeptonP;   // add lepton back if lepton is in acceptance
         if(JetMatched == false && fabs(MCTree[VBChildren[i]].PDGID) == 13 && fabs(LeptonP.GetEta()) < 2.4)
            PFMET = PFMET + LeptonP;
         if(JetMatched == false && fabs(MCTree[VBChildren[i]].PDGID) == 15 && fabs(LeptonP.GetEta()) < 2.4
            && DecayToMuon == true)
            PFMET = PFMET + LeptonP;
         // if(fabs(FourVector(MCTree[VBChildren[i]].P).GetEta()) < 2.4)
         //    PFMET = PFMET + LeptonP;

         // Also add back the identified good muon
         PFMET = PFMET + MuonP;

         double MRNew = Get2011MR(Groups[0], Groups[1]);
         double RNew = Get2011R(Groups[0], Groups[1], PFMET);
         double R2New = RNew * RNew;

         TreeFactor = WPU / 2;
         TreeMR = MRNew;
         TreeR = RNew;
         OutputTree.Fill();

         HMRNew.Fill(MRNew, WPU / 2);
         if(R2New > 0.05)   HMRNew_R2New005.Fill(MRNew, WPU / 2);
         if(R2New > 0.10)   HMRNew_R2New010.Fill(MRNew, WPU / 2);
         if(R2New > 0.15)   HMRNew_R2New015.Fill(MRNew, WPU / 2);
         if(R2New > 0.20)   HMRNew_R2New020.Fill(MRNew, WPU / 2);
         if(R2New > 0.25)   HMRNew_R2New025.Fill(MRNew, WPU / 2);
         
         HR2New.Fill(R2New, WPU / 2);
         if(MRNew > 300)   HR2New_MRNew300.Fill(R2New, WPU / 2);
         if(MRNew > 400)   HR2New_MRNew400.Fill(R2New, WPU / 2);
         if(MRNew > 500)   HR2New_MRNew500.Fill(R2New, WPU / 2);
         if(MRNew > 600)   HR2New_MRNew600.Fill(R2New, WPU / 2);
         if(MRNew > 700)   HR2New_MRNew700.Fill(R2New, WPU / 2);

         if(MRNew > 300)
         {
            HMRNew_MRNew300.Fill(MRNew, WPU / 2);
            if(R2New > 0.05)   HMRNew_MRNew300_R2New005.Fill(MRNew, WPU / 2);
            if(R2New > 0.10)   HMRNew_MRNew300_R2New010.Fill(MRNew, WPU / 2);
            if(R2New > 0.15)   HMRNew_MRNew300_R2New015.Fill(MRNew, WPU / 2);
            if(R2New > 0.20)   HMRNew_MRNew300_R2New020.Fill(MRNew, WPU / 2);
            if(R2New > 0.25)   HMRNew_MRNew300_R2New025.Fill(MRNew, WPU / 2);
         }

         if(R2New > 0.15)
         {
            HR2New_R2New015.Fill(R2New, WPU / 2);
            if(MRNew > 300)   HR2New_MRNew300_R2New015.Fill(R2New, WPU / 2);
            if(MRNew > 400)   HR2New_MRNew400_R2New015.Fill(R2New, WPU / 2);
            if(MRNew > 500)   HR2New_MRNew500_R2New015.Fill(R2New, WPU / 2);
            if(MRNew > 600)   HR2New_MRNew600_R2New015.Fill(R2New, WPU / 2);
            if(MRNew > 700)   HR2New_MRNew700_R2New015.Fill(R2New, WPU / 2);
         }
      }
   }

   // scale histograms if desired
   bool ScaleHistograms = true;
   if(ScaleHistograms == true)
   {
      double Factor = 1;
      double Luminosity = 1000;
      double CrossSection = 1;
      Factor = Factor * CrossSection * Luminosity / TotalWeight;

      HMRNew.Scale(Factor);
      HMRNew_R2New005.Scale(Factor);
      HMRNew_R2New010.Scale(Factor);
      HMRNew_R2New015.Scale(Factor);
      HMRNew_R2New020.Scale(Factor);
      HMRNew_R2New025.Scale(Factor);
      
      HR2New.Scale(Factor);
      HR2New_MRNew300.Scale(Factor);
      HR2New_MRNew400.Scale(Factor);
      HR2New_MRNew500.Scale(Factor);
      HR2New_MRNew600.Scale(Factor);
      HR2New_MRNew700.Scale(Factor);

      HMRNew_MRNew300.Scale(Factor);
      HMRNew_MRNew300_R2New005.Scale(Factor);
      HMRNew_MRNew300_R2New010.Scale(Factor);
      HMRNew_MRNew300_R2New015.Scale(Factor);
      HMRNew_MRNew300_R2New020.Scale(Factor);
      HMRNew_MRNew300_R2New025.Scale(Factor);

      HR2New_R2New015.Scale(Factor);
      HR2New_MRNew300_R2New015.Scale(Factor);
      HR2New_MRNew400_R2New015.Scale(Factor);
      HR2New_MRNew500_R2New015.Scale(Factor);
      HR2New_MRNew600_R2New015.Scale(Factor);
      HR2New_MRNew700_R2New015.Scale(Factor);
   }

   // make a nice pdf file of all the plots
   bool PsFileOutput = true;
   if(PsFileOutput == true)
   {
      PsFileHelper PsFile("ZbbEmulateWbbShape.ps");
      PsFile.AddTextPage("Using Zbb MC to emulate Wbb shape!");

      PsFile.AddTextPage("First let's look at a few things for taus");
      PsFile.AddPlot(HMCTauCount, "text00 hist", true);
      PsFile.AddPlot(HMCTauChildrenCount, "", true);
      PsFile.AddPlot(HMCTauChildrenSpread, "", true);

      vector<string> TauExplanation;
      TauExplanation.push_back("The tau does not decay, not within the first 100 particles");
      TauExplanation.push_back("So we won't be seeing anything for taus");
      TauExplanation.push_back("That's why the number of children is always zero");
      TauExplanation.push_back("");
      TauExplanation.push_back("Short conclusion: I'm wasting my time here");
      TauExplanation.push_back("I'll go back to generator-level study I did a while ago");
      PsFile.AddTextPage(TauExplanation);

      PsFile.AddTextPage("Look at tau jets now");
      PsFile.AddPlot(HMCTauClosestJetDR, "", true);
      PsFile.AddPlot(HMCTauClosestJetPTRatio, "", true);
      PsFile.AddPlot(HMCTauClosestJetDRVsPTRatio, "colz", false, true);

      PsFile.AddTextPage("Razor variables with single-lepton-neutrino treatment");

      PsFile.AddPlot(HMRNew, "", true);
      PsFile.AddPlot(HMRNew_R2New005, "", true);
      PsFile.AddPlot(HMRNew_R2New010, "", true);
      PsFile.AddPlot(HMRNew_R2New015, "", true);
      PsFile.AddPlot(HMRNew_R2New020, "", true);
      PsFile.AddPlot(HMRNew_R2New025, "", true);

      PsFile.AddPlot(HR2New, "", true);
      PsFile.AddPlot(HR2New_MRNew300, "", true);
      PsFile.AddPlot(HR2New_MRNew400, "", true);
      PsFile.AddPlot(HR2New_MRNew500, "", true);
      PsFile.AddPlot(HR2New_MRNew600, "", true);
      PsFile.AddPlot(HR2New_MRNew700, "", true);

      PsFile.AddPlot(HMRNew_MRNew300, "", true);
      PsFile.AddPlot(HMRNew_MRNew300_R2New005, "", true);
      PsFile.AddPlot(HMRNew_MRNew300_R2New010, "", true);
      PsFile.AddPlot(HMRNew_MRNew300_R2New015, "", true);
      PsFile.AddPlot(HMRNew_MRNew300_R2New020, "", true);
      PsFile.AddPlot(HMRNew_MRNew300_R2New025, "", true);

      PsFile.AddPlot(HR2New_R2New015, "", true);
      PsFile.AddPlot(HR2New_MRNew300_R2New015, "", true);
      PsFile.AddPlot(HR2New_MRNew400_R2New015, "", true);
      PsFile.AddPlot(HR2New_MRNew500_R2New015, "", true);
      PsFile.AddPlot(HR2New_MRNew600_R2New015, "", true);
      PsFile.AddPlot(HR2New_MRNew700_R2New015, "", true);

      PsFile.AddTimeStampPage();
      PsFile.Close();
   }

   // write histograms to file
   bool WriteHistograms = true;
   if(WriteHistograms == true)
   {
      HMCTauCount.Write();
      HMCTauChildrenCount.Write();
      HMCTauChildrenSpread.Write();

      HMCTauClosestJetDR.Write();
      HMCTauClosestJetPTRatio.Write();
      HMCTauClosestJetDRVsPTRatio.Write();

      HMRNew.Write();
      HMRNew_R2New005.Write();
      HMRNew_R2New010.Write();
      HMRNew_R2New015.Write();
      HMRNew_R2New020.Write();
      HMRNew_R2New025.Write();
      
      HR2New.Write();
      HR2New_MRNew300.Write();
      HR2New_MRNew400.Write();
      HR2New_MRNew500.Write();
      HR2New_MRNew600.Write();
      HR2New_MRNew700.Write();

      HMRNew_MRNew300.Write();
      HMRNew_MRNew300_R2New005.Write();
      HMRNew_MRNew300_R2New010.Write();
      HMRNew_MRNew300_R2New015.Write();
      HMRNew_MRNew300_R2New020.Write();
      HMRNew_MRNew300_R2New025.Write();

      HR2New_R2New015.Write();
      HR2New_MRNew300_R2New015.Write();
      HR2New_MRNew400_R2New015.Write();
      HR2New_MRNew500_R2New015.Write();
      HR2New_MRNew600_R2New015.Write();
      HR2New_MRNew700_R2New015.Write();
   }

   OutputTree.Write();

   F.Close();

   return 0;
}

bool muonPassLoose(NTPTreeMessenger &M, int index)
{
   if(index >= M.nMuon)   // imaginary muon always fail ID
      return false;

   if((M.muonIdMuon[index] >> 8) % 2 == false)
      return false;

   int iTrack = M.trackIndexMuon[index];
   if(iTrack < 0 || iTrack >= M.nTrack)   // something's wrong
      return false;

   if(M.numberOfValidStripTIBHitsTrack[iTrack]
      + M.numberOfValidStripTIDHitsTrack[iTrack]
      + M.numberOfValidStripTOBHitsTrack[iTrack]
      + M.numberOfValidStripTECHitsTrack[iTrack] <= 10)
      return false;

   return true;
}

bool electronPassWP95(NTPTreeMessenger &M, int index)
{
   if(index >= M.nEle)   // asking for an electron that doesn't exist!?  Meow!!
     return false;

   bool IsBarrel = false;
   bool IsEndcap = false;

   int iSC = M.superClusterIndexEle[index];
   if(iSC < 0 || iSC >= M.nSC)   // something wrong!  electron don't have SC associated?
      return false;

   int iGsfTrack = M.gsfTrackIndexEle[index];
   if(iGsfTrack < 0 || iGsfTrack >= M.nGsfTrack)
      return false;
   if(M.expInnerLayersGsfTrack[iGsfTrack] > 0)
      return false;

   double eta = M.etaSC[iSC];
   if(fabs(eta) < 1.4442)
      IsBarrel = true;
   if(fabs(eta) > 1.566 && fabs(eta) < 2.5)
      IsEndcap = true;

   double TrackIsolation = M.dr03TkSumPtEle[index];
   double EcalIsolation = M.dr03EcalRecHitSumEtEle[index];
   double HcalIsolation = M.dr03HcalTowerSumEtEle[index];

   double PT = sqrt(M.pxEle[index] * M.pxEle[index] + M.pyEle[index] * M.pyEle[index]);

   double SigmaIEtaIEta = sqrt(M.covIEtaIEtaSC[iSC]);
   double DEta = fabs(M.deltaEtaAtVtxEle[index]);
   double DPhi = fabs(M.deltaPhiAtVtxEle[index]);
   double HOverE = M.hOverEEle[index];   // not used at the moment....
   double CombinedIsolation = 0;
   if(IsBarrel == true)
      CombinedIsolation = TrackIsolation + max(0.0, EcalIsolation - 1) + HcalIsolation;
   else
      CombinedIsolation = TrackIsolation + EcalIsolation + HcalIsolation;
   CombinedIsolation = CombinedIsolation - M.rhoFastjet * TMath::Pi() * 0.3 * 0.3;
   CombinedIsolation = CombinedIsolation / PT;

   double ConversionDistance = fabs(M.convDistEle[index]);
   double ConversionDCotTheta = fabs(M.convDcotEle[index]);

   if(IsBarrel == true)
   {
      if(CombinedIsolation > 0.150)  return false;
      if(SigmaIEtaIEta > 0.012)      return false;
      if(DPhi > 0.800)               return false;
      if(DEta > 0.007)               return false;
   }
   if(IsEndcap == true)
   {
      if(CombinedIsolation > 0.100)  return false;
      if(SigmaIEtaIEta > 0.031)      return false;
      if(DPhi > 0.700)               return false;
      if(DEta > 0.011)               return false;
   }

   return true;
}



