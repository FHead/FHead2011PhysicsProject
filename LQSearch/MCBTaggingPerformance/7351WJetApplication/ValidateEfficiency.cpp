#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper2.h"
#include "ChainAll.h"
#include "TauHelperFunctions2.h"

#include "ReadNTPTreeV4.h"
#include "TaggingEfficiencyHelper.h"

int main();
int FindChildIndex(NTPTreeMessenger &M, int ChildPDGID, int ParentPDGID);
int TraceBHadron(NTPTreeMessenger &M, int StartIndex);
void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, bool LogY = false);
bool HasB(int PDGID);

int main()
{
   SetStyle();

   string InputList = "WJetV4.list";

   TChain *NTPTree = ChainAll(InputList, "ntp1");
   if(NTPTree == NULL)
      return -1;

   NTPTreeMessenger M;
   M.SetBranchAddress(NTPTree);

   NTPTree->SetBranchStatus("*", false);   // to speed things up
   NTPTree->SetBranchStatus("nAK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("etaAK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("phiAK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("energyAK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("pxAK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("pyAK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("pzAK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("neutral*AK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("charged*AK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("*MultiplicityAK5PFPUcorrJet", true);
   NTPTree->SetBranchStatus("*BJetTagsAK5PFPUcorrJet", true);
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

   TFile FB("EfficiencyTCHEL.root");
   TFile FNonB("MistagTCHEL.root");

   TaggingEfficiencyHelper BHelper, NonBHelper;
   // BHelper.Initialize(FB, "HAllBJetPT", "HTaggedBJetPT", "HAllBJetEta", "HTaggedBJetEta", "HAllBJetPTVsEta");
   // NonBHelper.Initialize(FNonB, "HGoodJetPT", "HGoodJetPTPassTCHE", "HGoodJetEta",
   //    "HGoodJetEtaPassTCHE", "HGoodJetPTVsEta");
   NonBHelper.Initialize(FNonB, "HExclusiveJetPT", "HExclusiveJetPTPassTCHE", "HExclusiveJetEta",
      "HExclusiveJetEtaPassTCHE", "HExclusiveJetPTVsEta");

   TH1D HJetPTPassed("HJetPTPassed", "Jet PT, passed", 100, 0, 500);
   TH1D HJetPTWeighted("HJetPTWeighted", "Jet PT, weighted", 100, 0, 500);

   TH1D HBJetPTPassed("HBJetPTPassed", "Tagged jet PT, passed", 100, 0, 500);
   TH1D HBJetPTWeighted("HBJetPTWeighted", "Tagged jet PT, weighted", 100, 0, 500);

   TH1D HBJetEtaPassed("HBJetEtaPassed", "Tagged jet Eta, passed", 100, -3, 3);
   TH1D HBJetEtaWeighted("HBJetEtaWeighted", "Tagged jet Eta, weighted", 100, -3, 3);

   TH1D HR2NewPassed("HR2NewPassed", "R^{2} (new), pass TCHELx2", 30, 0, 1.2);
   TH1D HR2NewWeighted("HR2NewWeighted", "R^{2} (new), weight with TCHELx2", 30, 0, 1.2);
   
   TH1D HR2NewMRNew300Passed("HR2NewMRNew300Passed", "R^{2} (new), MR (new) > 300, pass TCHELx2", 30, 0, 1.2);
   TH1D HR2NewMRNew300Weighted("HR2NewMRNew300Weighted", "R^{2} (new), MR (new) > 300, weight with TCHELx2", 30, 0, 1.2);
   
   TH1D HR2NewMRNew400Passed("HR2NewMRNew400Passed", "R^{2} (new), MR (new) > 400, pass TCHELx2", 30, 0, 1.2);
   TH1D HR2NewMRNew400Weighted("HR2NewMRNew400Weighted", "R^{2} (new), MR (new) > 400, weight with TCHELx2", 30, 0, 1.2);
   
   TH1D HMRNewPassed("HMRNewPassed", "MR (new), pass TCHELx2", 40, 0, 1000);
   TH1D HMRNewWeighted("HMRNewWeighted", "MR (new), weight with TCHELx2",40, 0, 1000);
   
   TH1D HMRNewR2New01Passed("HMRNewR2New01Passed", "MR (new), R^{2} (new) > 0.1, pass TCHELx2", 40, 0, 1000);
   TH1D HMRNewR2New01Weighted("HMRNewR2New01Weighted", "MR (new), R^{2} (new) > 0.1, weight with TCHELx2", 40, 0, 1000);
   
   TH1D HMRNewR2New014Passed("HMRNewR2New014Passed", "MR (new), R^{2} (new) > 0.14, pass TCHELx2", 40, 0, 1000);
   TH1D HMRNewR2New014Weighted("HMRNewR2New014Weighted", "MR (new), R^{2} (new) > 0.14, weight with TCHELx2", 40, 0, 1000);
   
   TH1D HMRNewR2New02Passed("HMRNewR2New02Passed", "MR (new), R^{2} (new) > 0.2, pass TCHELx2", 40, 0, 1000);
   TH1D HMRNewR2New02Weighted("HMRNewR2New02Weighted", "MR (new), R^{2} (new) > 0.2, weight with TCHELx2", 40, 0, 1000);
   
   TH1D HMRNewR2New03Passed("HMRNewR2New03Passed", "MR (new), R^{2} (new) > 0.3, pass TCHELx2", 40, 0, 1000);
   TH1D HMRNewR2New03Weighted("HMRNewR2New03Weighted", "MR (new), R^{2} (new) > 0.3, weight with TCHELx2", 40, 0, 1000);
   
   TH1D HMRNewR2New04Passed("HMRNewR2New04Passed", "MR (new), R^{2} (new) > 0.4, pass TCHELx2", 40, 0, 1000);
   TH1D HMRNewR2New04Weighted("HMRNewR2New04Weighted", "MR (new), R^{2} (new) > 0.4, weight with TCHELx2", 40, 0, 1000);
   
   TH1D HMRNewR2New05Passed("HMRNewR2New05Passed", "MR (new), R^{2} (new) > 0.5, pass TCHELx2", 40, 0, 1000);
   TH1D HMRNewR2New05Weighted("HMRNewR2New05Weighted", "MR (new), R^{2} (new) > 0.5, weight with TCHELx2", 40, 0, 1000);

   int EntryCount = NTPTree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 20000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      NTPTree->GetEntry(iEntry);

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.nAK5PFPUcorrJet; i++)
      {
         FourVector JetP(M.energyAK5PFPUcorrJet[i], M.pxAK5PFPUcorrJet[i],
            M.pyAK5PFPUcorrJet[i], M.pzAK5PFPUcorrJet[i]);

         if(JetP.GetPT() < 40)
            continue;
         if(JetP.GetEta() < -3 || JetP.GetEta() > 3)
            continue;

         GoodJets.push_back(JetP);
      }
      if(GoodJets.size() > 20 || GoodJets.size() < 2)
         continue;
      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      vector<FourVector> WOffspring;
      int WFromT = max(FindChildIndex(M, 24, 6), FindChildIndex(M, -24, 6));
      int WFromTBar = max(FindChildIndex(M, 24, -6), FindChildIndex(M, -24, -6));
      for(int i = 0; i < M.nMc; i++)
      {
         if(M.idMc[i] == 12 || M.idMc[i] == 14 || M.idMc[i] == 16
            || M.idMc[i] == -12 || M.idMc[i] == -14 || M.idMc[i] == -16)
            continue;
   
         FourVector ParticleP;
         ParticleP.SetSizeEtaPhiEnergy(M.pMc[i], M.etaMc[i], M.phiMc[i], M.energyMc[i]);

         if(WFromT >= 0 && M.mothMc[i] == WFromT && ParticleP.GetPT() > 20)
            WOffspring.push_back(ParticleP);
         if(WFromTBar >= 0 && M.mothMc[i] == WFromTBar && ParticleP.GetPT() > 20)
            WOffspring.push_back(ParticleP);
      }

      FourVector PFMet;
      PFMet[1] = M.pxPFMet[0];
      PFMet[2] = M.pyPFMet[0];

      double RNew = Get2011R(Groups[0], Groups[1], PFMet);
      double MRNew = Get2011MR(Groups[0], Groups[1]);
      double R2New = RNew * RNew;

      int BTagJetCount = 0;
      vector<double> Efficiencies;
      vector<int> BJetIndices;
      for(int i = 0; i < M.nAK5PFPUcorrJet; i++)
      {
         FourVector JetP(M.energyAK5PFPUcorrJet[i], M.pxAK5PFPUcorrJet[i],
            M.pyAK5PFPUcorrJet[i], M.pzAK5PFPUcorrJet[i]);

         if(JetP.GetPT() < 40 || fabs(JetP.GetEta()) > 2.4)
            continue;

         if(M.trackCountingHighEffBJetTagsAK5PFPUcorrJet[i] > 1.7)
         {
            HBJetPTPassed.Fill(JetP.GetPT());
            HBJetEtaPassed.Fill(JetP.GetEta());
            BTagJetCount = BTagJetCount + 1;
            BJetIndices.push_back(i);
         }

         bool CloseToWOffspring = false;
         for(int j = 0; j < (int)WOffspring.size(); j++)
            if(GetDR(JetP, WOffspring[j]) < 0.6)
               CloseToWOffspring = true;
         if(CloseToWOffspring == false)
         {
            // double Efficiency = NonBHelper.GetEfficiency(JetP.GetPT(), JetP.GetEta()) / 2
            //    * exp((JetP.GetPT() - 100) / (500 - 100) * log(2));
            double Efficiency = NonBHelper.GetEfficiency(JetP.GetPT(), JetP.GetEta());
            Efficiencies.push_back(Efficiency);
            HBJetPTWeighted.Fill(JetP.GetPT(), Efficiency);
            HBJetEtaWeighted.Fill(JetP.GetEta(), Efficiency);
            // cout << JetP.GetPT() << " " << JetP.GetEta() << " "
            //    << (NonBHelper.GetEfficiency(JetP.GetPT(), JetP.GetEta()))
            //    << endl;
         }
      }
      double EventChance = 0;
      for(int i = 0; i < (int)BJetIndices.size(); i++)
         EventChance = EventChance + EventTaggedChance(Efficiencies, 2 - 1, BJetIndices[i]) / BJetIndices.size();
      // cout << "Weight = " << EventChance << endl;
      // cout << endl;

      if(BTagJetCount >= 2)
      {
         for(int i = 0; i < M.nAK5PFPUcorrJet; i++)
         {
            FourVector JetP(M.energyAK5PFPUcorrJet[i], M.pxAK5PFPUcorrJet[i],
               M.pyAK5PFPUcorrJet[i], M.pzAK5PFPUcorrJet[i]);
            HJetPTPassed.Fill(JetP.GetPT());
         }

         HR2NewPassed.Fill(R2New);
         HMRNewPassed.Fill(MRNew);

         if(MRNew > 300)
            HR2NewMRNew300Passed.Fill(R2New);
         if(MRNew > 400)
            HR2NewMRNew400Passed.Fill(R2New);

         if(R2New > 0.1)
            HMRNewR2New01Passed.Fill(MRNew);
         if(R2New > 0.14)
            HMRNewR2New014Passed.Fill(MRNew);
         if(R2New > 0.2)
            HMRNewR2New02Passed.Fill(MRNew);
         if(R2New > 0.3)
            HMRNewR2New03Passed.Fill(MRNew);
         if(R2New > 0.5)
            HMRNewR2New04Passed.Fill(MRNew);
         if(R2New > 0.6)
            HMRNewR2New05Passed.Fill(MRNew);
      }

      for(int i = 0; i < M.nAK5PFPUcorrJet; i++)
      {
         FourVector JetP(M.energyAK5PFPUcorrJet[i], M.pxAK5PFPUcorrJet[i],
            M.pyAK5PFPUcorrJet[i], M.pzAK5PFPUcorrJet[i]);
         HJetPTWeighted.Fill(JetP.GetPT(), EventChance);
      }
      
      HR2NewWeighted.Fill(R2New, EventChance);
      HMRNewWeighted.Fill(MRNew, EventChance);

      if(MRNew > 300)
         HR2NewMRNew300Weighted.Fill(R2New, EventChance);
      if(MRNew > 400)
         HR2NewMRNew400Weighted.Fill(R2New, EventChance);

      if(R2New > 0.1)
         HMRNewR2New01Weighted.Fill(MRNew, EventChance);
      if(R2New > 0.14)
         HMRNewR2New014Weighted.Fill(MRNew, EventChance);
      if(R2New > 0.2)
         HMRNewR2New02Weighted.Fill(MRNew, EventChance);
      if(R2New > 0.3)
         HMRNewR2New03Weighted.Fill(MRNew, EventChance);
      if(R2New > 0.5)
         HMRNewR2New04Weighted.Fill(MRNew, EventChance);
      if(R2New > 0.6)
         HMRNewR2New05Weighted.Fill(MRNew, EventChance);
   }

   PsFileHelper PsFile("Application.ps");
   PsFile.AddTextPage("Application of b-tagging event chance!!!!");

   PsFile.AddPlot(HBJetPTPassed, "", true);
   PsFile.AddPlot(HBJetPTWeighted, "", true);
   OverlayHistograms(PsFile, &HBJetPTPassed, &HBJetPTWeighted, true);
   
   PsFile.AddPlot(HBJetEtaPassed, "", true);
   PsFile.AddPlot(HBJetEtaWeighted, "", true);
   OverlayHistograms(PsFile, &HBJetEtaPassed, &HBJetEtaWeighted, true);

   PsFile.AddPlot(HJetPTPassed, "", true);
   PsFile.AddPlot(HJetPTWeighted, "", true);
   OverlayHistograms(PsFile, &HJetPTPassed, &HJetPTWeighted, true);

   PsFile.AddPlot(HR2NewPassed, "", true);
   PsFile.AddPlot(HR2NewWeighted, "", true);
   OverlayHistograms(PsFile, &HR2NewPassed, &HR2NewWeighted, true);

   PsFile.AddPlot(HR2NewMRNew300Passed, "", true);
   PsFile.AddPlot(HR2NewMRNew300Weighted, "", true);
   OverlayHistograms(PsFile, &HR2NewMRNew300Passed, &HR2NewMRNew300Weighted, true);

   PsFile.AddPlot(HR2NewMRNew400Passed, "", true);
   PsFile.AddPlot(HR2NewMRNew400Weighted, "", true);
   OverlayHistograms(PsFile, &HR2NewMRNew400Passed, &HR2NewMRNew400Weighted, true);

   PsFile.AddPlot(HMRNewPassed, "", true);
   PsFile.AddPlot(HMRNewWeighted, "", true);
   OverlayHistograms(PsFile, &HMRNewPassed, &HMRNewWeighted, true);

   PsFile.AddPlot(HMRNewR2New01Passed, "", true);
   PsFile.AddPlot(HMRNewR2New01Weighted, "", true);
   OverlayHistograms(PsFile, &HMRNewR2New01Passed, &HMRNewR2New01Weighted, true);

   PsFile.AddPlot(HMRNewR2New014Passed, "", true);
   PsFile.AddPlot(HMRNewR2New014Weighted, "", true);
   OverlayHistograms(PsFile, &HMRNewR2New014Passed, &HMRNewR2New014Weighted, true);

   PsFile.AddPlot(HMRNewR2New02Passed, "", true);
   PsFile.AddPlot(HMRNewR2New02Weighted, "", true);
   OverlayHistograms(PsFile, &HMRNewR2New02Passed, &HMRNewR2New02Weighted, true);

   PsFile.AddPlot(HMRNewR2New03Passed, "", true);
   PsFile.AddPlot(HMRNewR2New03Weighted, "", true);
   OverlayHistograms(PsFile, &HMRNewR2New03Passed, &HMRNewR2New03Weighted, true);

   PsFile.AddPlot(HMRNewR2New04Passed, "", true);
   PsFile.AddPlot(HMRNewR2New04Weighted, "", true);
   OverlayHistograms(PsFile, &HMRNewR2New04Passed, &HMRNewR2New04Weighted, true);

   PsFile.AddPlot(HMRNewR2New05Passed, "", true);
   PsFile.AddPlot(HMRNewR2New05Weighted, "", true);
   OverlayHistograms(PsFile, &HMRNewR2New05Passed, &HMRNewR2New05Weighted, true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   FNonB.Close();
   FB.Close();

   return 0;
}

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

void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, bool LogY)
{
   TCanvas Canvas;

   H1->SetLineColor(1);
   H1->Draw();

   H2->SetLineColor(2);
   H2->Draw("same");

   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.AddEntry(H1, "Passed", "l");
   legend.AddEntry(H2, "Weighted", "l");
   legend.SetFillColor(0);
   legend.Draw();

   if(LogY == true)
      Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
}










