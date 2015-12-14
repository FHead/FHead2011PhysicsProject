#include <iostream>
#include <string>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "ChainAll.h"
#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

#include "ReadNTPTreeV4.h"

int main(int argc, char *argv[])
{
   if(argc == 1)
   {
      cout << "Usage: " << argv[0] << " Tag" << endl;
      return -1;
   }
   
   string Tag = argv[1];

   string InputList = Tag + "List";
   string OutputBase = Tag;

   TChain *Tree = ChainAll(InputList, "ntp1");
   if(Tree == NULL)
      return -1;

   NTPTreeMessenger M;
   M.SetBranchAddress(Tree);

   Tree->SetBranchStatus("*", false);
   Tree->SetBranchStatus("*PU", true);
   Tree->SetBranchStatus("*PV", true);
   Tree->SetBranchStatus("*Mc", true);
   Tree->SetBranchStatus("*AK5Jet", true);
   Tree->SetBranchStatus("*PFMet", true);

   TFile F((OutputBase + ".root").c_str(), "RECREATE");

   TH1D HNPU("NPU", "Added pileup;Count", 30, -0.5, 29.5);
   TH1D HNPV("NPV", "Reconstructed vertex;Count", 30, -0.5, 29.5);

   TH1D HVBCount("HVBCount", "Count of vector boson", 3, -1.5, 1.5);
   HVBCount.GetXaxis()->SetBinLabel(1, "W-");
   HVBCount.GetXaxis()->SetBinLabel(2, "Z");
   HVBCount.GetXaxis()->SetBinLabel(3, "W+");
   TH1D HVBCountPerEvent("HVBCountPerEvent", "VB count per event;Count", 5, -0.5, 4.5);
   TH1D HVBChildren("HVBChildren", "Children PDG ID of vector bosons;PDG ID", 101, -50.5, 50.5);

   TH1D HDRJetVBChild("HDRJetVBChild", "DR of jets to VB children;dR", 100, 0, 5);
   TH1D HQCDJetCount30("HQCDJetCount30", "QCD jets above 30 GeV;Count", 30, -0.5, 29.5);
   TH1D HQCDJetCount50("HQCDJetCount50", "QCD jets above 50 GeV;Count", 30, -0.5, 29.5);
   TH1D HQCDJetCount80("HQCDJetCount80", "QCD jets above 80 GeV;Count", 30, -0.5, 29.5);
   TH1D HQCDJetPT("HQCDJetPT", "QCD jet PT;PT (GeV)", 100, 0, 200);
   TH1D HQCDJetEta("HQCDJetEta", "QCD jet eta;eta", 100, -4, 4);
   TH1D HQCDJetPhi("HQCDJetPhi", "QCD jet phi;phi", 100, -3.2, 3.2);

   TH1D HQCDJetTCHE30("HQCDJetTCHE30", "TCHE tag of QCD jets (30 GeV);TCHE", 100, 0, 20);
   TH1D HQCDJetTCHE50("HQCDJetTCHE50", "TCHE tag of QCD jets (50 GeV);TCHE", 100, 0, 20);
   TH1D HQCDJetTCHE80("HQCDJetTCHE80", "TCHE tag of QCD jets (80 GeV);TCHE", 100, 0, 20);
   TH1D HQCDJetTCHELCount30("HQCDJetTCHELCount30", "Number of QCD jets (30 GeV) passing TCHEL;Count", 20, -0.5, 19.5);
   TH1D HQCDJetTCHEMCount30("HQCDJetTCHEMCount30", "Number of QCD jets (30 GeV) passing TCHEM;Count", 20, -0.5, 19.5);
   TH1D HQCDJetTCHETCount30("HQCDJetTCHETCount30", "Number of QCD jets (30 GeV) passing TCHET;Count", 20, -0.5, 19.5);
   TH1D HQCDJetTCHELCount50("HQCDJetTCHELCount50", "Number of QCD jets (50 GeV) passing TCHEL;Count", 20, -0.5, 19.5);
   TH1D HQCDJetTCHEMCount50("HQCDJetTCHEMCount50", "Number of QCD jets (50 GeV) passing TCHEM;Count", 20, -0.5, 19.5);
   TH1D HQCDJetTCHETCount50("HQCDJetTCHETCount50", "Number of QCD jets (50 GeV) passing TCHET;Count", 20, -0.5, 19.5);
   TH1D HQCDJetTCHELCount80("HQCDJetTCHELCount80", "Number of QCD jets (80 GeV) passing TCHEL;Count", 20, -0.5, 19.5);
   TH1D HQCDJetTCHEMCount80("HQCDJetTCHEMCount80", "Number of QCD jets (80 GeV) passing TCHEM;Count", 20, -0.5, 19.5);
   TH1D HQCDJetTCHETCount80("HQCDJetTCHETCount80", "Number of QCD jets (80 GeV) passing TCHET;Count", 20, -0.5, 19.5);
   TH1D HQCDBJetPT("HQCDBJetPT", "QCD b-tagged jet PT;PT (GeV)", 100, 0, 200);
   TH1D HQCDBJetEta("HQCDBJetEta", "QCD b-tagged jet eta;eta", 100, -4, 4);
   TH1D HQCDBJetPhi("HQCDBJetPhi", "QCD b-tagged jet phi;phi", 100, -3.2, 3.2);

   TH1D HTaggedEventQCDJetCount30("HTaggedEventQCDJetCount30",
      "QCD jet count (30) in tagged event;Count", 20, -0.5, 19.5);
   TH1D HTaggedEventQCDJetCount50("HTaggedEventQCDJetCount50",
      "QCD jet count (50) in tagged event;Count", 20, -0.5, 19.5);
   TH1D HTaggedEventQCDJetCount80("HTaggedEventQCDJetCount80",
      "QCD jet count (80) in tagged event;Count", 20, -0.5, 19.5);
   TH1D HTaggedEventQCDJetPT("HTaggedEventQCDJetPT", "QCD jet PT in tagged event;PT (GeV)", 100, 0, 200);
   TH1D HTaggedEventQCDJetEta("HTaggedEventQCDJetEta", "QCD jet eta in tagged event;eta", 100, -4, 4);
   TH1D HTaggedEventQCDJetPhi("HTaggedEventQCDJetPhi", "QCD jet phi in tagged event;phi", 100, -3.2, 3.2);
   
   TH1D HSingleTaggedEventQCDJetCount30("HSingleTaggedEventQCDJetCount30",
      "QCD jet count (30) in single-tagged event;Count", 20, -0.5, 19.5);
   TH1D HSingleTaggedEventQCDJetCount50("HSingleTaggedEventQCDJetCount50",
      "QCD jet count (50) in single-tagged event;Count", 20, -0.5, 19.5);
   TH1D HSingleTaggedEventQCDJetCount80("HSingleTaggedEventQCDJetCount80",
      "QCD jet count (80) in single-tagged event;Count", 20, -0.5, 19.5);
   TH1D HSingleTaggedEventQCDJetPT("HSingleTaggedEventQCDJetPT",
      "QCD jet PT in single-tagged event;PT (GeV)", 100, 0, 200);
   TH1D HSingleTaggedEventQCDJetEta("HSingleTaggedEventQCDJetEta",
      "QCD jet eta in single-tagged event;eta", 100, -4, 4);
   TH1D HSingleTaggedEventQCDJetPhi("HSingleTaggedEventQCDJetPhi",
      "QCD jet phi in single-tagged event;phi", 100, -3.2, 3.2);
   
   TH1D HLowTaggedEventQCDJetCount30("HLowTaggedEventQCDJetCount30",
      "QCD jet count (30) in low-tagged event;Count", 20, -0.5, 19.5);
   TH1D HLowTaggedEventQCDJetCount50("HLowTaggedEventQCDJetCount50",
      "QCD jet count (50) in low-tagged event;Count", 20, -0.5, 19.5);
   TH1D HLowTaggedEventQCDJetCount80("HLowTaggedEventQCDJetCount80",
      "QCD jet count (80) in low-tagged event;Count", 20, -0.5, 19.5);
   TH1D HLowTaggedEventQCDJetPT("HLowTaggedEventQCDJetPT", "QCD jet PT in low-tagged event;PT (GeV)", 100, 0, 200);
   TH1D HLowTaggedEventQCDJetEta("HLowTaggedEventQCDJetEta", "QCD jet eta in low-tagged event;eta", 100, -4, 4);
   TH1D HLowTaggedEventQCDJetPhi("HLowTaggedEventQCDJetPhi", "QCD jet phi in low-tagged event;phi", 100, -3.2, 3.2);

   TH1D HTaggedEventMRNew("HTaggedEventMRNew", "MR (new) in tagged event;MR (new) (GeV)", 40, 0, 1500);
   TH1D HTaggedEventMRNew_R2New005("HTaggedEventMRNew_R2New005",
      "MR (new) in tagged event, R^{2} (new) > 0.05;MR (new) (GeV)", 40, 0, 1500);
   TH1D HTaggedEventMRNew_R2New010("HTaggedEventMRNew_R2New010",
      "MR (new) in tagged event, R^{2} (new) > 0.10;MR (new) (GeV)", 40, 0, 1500);
   TH1D HTaggedEventMRNew_R2New015("HTaggedEventMRNew_R2New015",
      "MR (new) in tagged event, R^{2} (new) > 0.15;MR (new) (GeV)", 40, 0, 1500);
   TH1D HTaggedEventMRNew_R2New020("HTaggedEventMRNew_R2New020",
      "MR (new) in tagged event, R^{2} (new) > 0.20;MR (new) (GeV)", 40, 0, 1500);
   TH1D HTaggedEventMRNew_R2New025("HTaggedEventMRNew_R2New025",
      "MR (new) in tagged event, R^{2} (new) > 0.25;MR (new) (GeV)", 40, 0, 1500);
   
   TH1D HTaggedEventR2New("HTaggedEventR2New", "R^{2} (new) in tagged event;R^{2} (new)", 40, 0, 1.2);
   TH1D HTaggedEventR2New_MRNew300("HTaggedEventR2New_MRNew300",
      "R^{2} (new) in tagged event, MR (new) > 300;R^{2} (new)", 40, 0, 1.2);
   TH1D HTaggedEventR2New_MRNew400("HTaggedEventR2New_MRNew400",
      "R^{2} (new) in tagged event, MR (new) > 400;R^{2} (new)", 40, 0, 1.2);
   TH1D HTaggedEventR2New_MRNew500("HTaggedEventR2New_MRNew500",
      "R^{2} (new) in tagged event, MR (new) > 500;R^{2} (new)", 40, 0, 1.2);
   TH1D HTaggedEventR2New_MRNew600("HTaggedEventR2New_MRNew600",
      "R^{2} (new) in tagged event, MR (new) > 600;R^{2} (new)", 40, 0, 1.2);
   TH1D HTaggedEventR2New_MRNew700("HTaggedEventR2New_MRNew700",
      "R^{2} (new) in tagged event, MR (new) > 700;R^{2} (new)", 40, 0, 1.2);

   TH2D HTaggedEventMRNewVsR2New("HTaggedEventMRNewVsR2New",
      "MR (new) vs. R^{2} (new) in tagged event;MR (new);R^{2} (new)", 100, 0, 1500, 100, 0, 1.2);

   TH1D HSingleTaggedEventMRNew("HSingleTaggedEventMRNew",
      "MR (new) in single-tagged event;MR (new) (GeV)", 40, 0, 1500);
   TH1D HSingleTaggedEventMRNew_R2New005("HSingleTaggedEventMRNew_R2New005",
      "MR (new) in single-tagged event, R^{2} (new) > 0.05;MR (new) (GeV)", 40, 0, 1500);
   TH1D HSingleTaggedEventMRNew_R2New010("HSingleTaggedEventMRNew_R2New010",
      "MR (new) in single-tagged event, R^{2} (new) > 0.10;MR (new) (GeV)", 40, 0, 1500);
   TH1D HSingleTaggedEventMRNew_R2New015("HSingleTaggedEventMRNew_R2New015",
      "MR (new) in single-tagged event, R^{2} (new) > 0.15;MR (new) (GeV)", 40, 0, 1500);
   TH1D HSingleTaggedEventMRNew_R2New020("HSingleTaggedEventMRNew_R2New020",
      "MR (new) in single-tagged event, R^{2} (new) > 0.20;MR (new) (GeV)", 40, 0, 1500);
   TH1D HSingleTaggedEventMRNew_R2New025("HSingleTaggedEventMRNew_R2New025",
      "MR (new) in single-tagged event, R^{2} (new) > 0.25;MR (new) (GeV)", 40, 0, 1500);
   
   TH1D HSingleTaggedEventR2New("HSingleTaggedEventR2New",
      "R^{2} (new) in single-tagged event;R^{2} (new)", 40, 0, 1.2);
   TH1D HSingleTaggedEventR2New_MRNew300("HSingleTaggedEventR2New_MRNew300",
      "R^{2} (new) in single-tagged event, MR (new) > 300;R^{2} (new)", 40, 0, 1.2);
   TH1D HSingleTaggedEventR2New_MRNew400("HSingleTaggedEventR2New_MRNew400",
      "R^{2} (new) in single-tagged event, MR (new) > 400;R^{2} (new)", 40, 0, 1.2);
   TH1D HSingleTaggedEventR2New_MRNew500("HSingleTaggedEventR2New_MRNew500",
      "R^{2} (new) in single-tagged event, MR (new) > 500;R^{2} (new)", 40, 0, 1.2);
   TH1D HSingleTaggedEventR2New_MRNew600("HSingleTaggedEventR2New_MRNew600",
      "R^{2} (new) in single-tagged event, MR (new) > 600;R^{2} (new)", 40, 0, 1.2);
   TH1D HSingleTaggedEventR2New_MRNew700("HSingleTaggedEventR2New_MRNew700",
      "R^{2} (new) in single-tagged event, MR (new) > 700;R^{2} (new)", 40, 0, 1.2);

   TH2D HSingleTaggedEventMRNewVsR2New("HSingleTaggedEventMRNewVsR2New",
      "MR (new) vs. R^{2} (new) in single-tagged event;MR (new);R^{2} (new)", 100, 0, 1500, 100, 0, 1.2);
   
   TH1D HLowTaggedEventMRNew("HLowTaggedEventMRNew",
      "MR (new) in low-tagged event;MR (new) (GeV)", 40, 0, 1500);
   TH1D HLowTaggedEventMRNew_R2New005("HLowTaggedEventMRNew_R2New005",
      "MR (new) in low-tagged event, R^{2} (new) > 0.05;MR (new) (GeV)", 40, 0, 1500);
   TH1D HLowTaggedEventMRNew_R2New010("HLowTaggedEventMRNew_R2New010",
      "MR (new) in low-tagged event, R^{2} (new) > 0.10;MR (new) (GeV)", 40, 0, 1500);
   TH1D HLowTaggedEventMRNew_R2New015("HLowTaggedEventMRNew_R2New015",
      "MR (new) in low-tagged event, R^{2} (new) > 0.15;MR (new) (GeV)", 40, 0, 1500);
   TH1D HLowTaggedEventMRNew_R2New020("HLowTaggedEventMRNew_R2New020",
      "MR (new) in low-tagged event, R^{2} (new) > 0.20;MR (new) (GeV)", 40, 0, 1500);
   TH1D HLowTaggedEventMRNew_R2New025("HLowTaggedEventMRNew_R2New025",
      "MR (new) in low-tagged event, R^{2} (new) > 0.25;MR (new) (GeV)", 40, 0, 1500);
   
   TH1D HLowTaggedEventR2New("HLowTaggedEventR2New",
      "R^{2} (new) in low-tagged event;R^{2} (new)", 40, 0, 1.2);
   TH1D HLowTaggedEventR2New_MRNew300("HLowTaggedEventR2New_MRNew300",
      "R^{2} (new) in low-tagged event, MR (new) > 300;R^{2} (new)", 40, 0, 1.2);
   TH1D HLowTaggedEventR2New_MRNew400("HLowTaggedEventR2New_MRNew400",
      "R^{2} (new) in low-tagged event, MR (new) > 400;R^{2} (new)", 40, 0, 1.2);
   TH1D HLowTaggedEventR2New_MRNew500("HLowTaggedEventR2New_MRNew500",
      "R^{2} (new) in low-tagged event, MR (new) > 500;R^{2} (new)", 40, 0, 1.2);
   TH1D HLowTaggedEventR2New_MRNew600("HLowTaggedEventR2New_MRNew600",
      "R^{2} (new) in low-tagged event, MR (new) > 600;R^{2} (new)", 40, 0, 1.2);
   TH1D HLowTaggedEventR2New_MRNew700("HLowTaggedEventR2New_MRNew700",
      "R^{2} (new) in low-tagged event, MR (new) > 700;R^{2} (new)", 40, 0, 1.2);

   TH2D HLowTaggedEventMRNewVsR2New("HLowTaggedEventMRNewVsR2New",
      "MR (new) vs. R^{2} (new) in low-tagged event;MR (new);R^{2} (new)", 100, 0, 1500, 100, 0, 1.2);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 100000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      // basic plots
      int GoodPVCount = 0;
      for(int i = 0; i < M.nPV; i++)
      {
         if(M.ndofPV[i] <= 4)
            continue;
         if(M.PVzPV[i] > 15 || M.PVzPV[i] < -15)
            continue;
         if(M.PVxPV[i] * M.PVxPV[i] + M.PVyPV[i] * M.PVyPV[i] > 2 * 2)
            continue;
         GoodPVCount = GoodPVCount + 1;
      }
      HNPU.Fill(M.nPU[0]);
      HNPV.Fill(GoodPVCount);

      // tracing vector boson
      int VBCountInEvent = 0;
      int VBIndex = -1;
      for(int i = 0; i < M.nMc; i++)
      {
         if(M.statusMc[i] == 2)
            continue;
         if(M.idMc[i] != 23 && M.idMc[i] != 24 && M.idMc[i] != -24)
            continue;
         VBCountInEvent = VBCountInEvent + 1;
         VBIndex = i;
      }

      HVBCountPerEvent.Fill(VBCountInEvent);
      if(VBIndex == -1)   // oops....
         continue;
      if(M.idMc[VBIndex] == 23)
         HVBCount.Fill(0);
      if(M.idMc[VBIndex] == 24)
         HVBCount.Fill(1);
      if(M.idMc[VBIndex] == -24)
         HVBCount.Fill(-1);

      vector<int> VBChildren;
      vector<FourVector> VBChildrenP;
      bool HaveTauInChildren = false;
      for(int i = 0; i < M.nMc; i++)
      {
         if(M.mothMc[i] != VBIndex)
            continue;
         if(M.statusMc[i] == 2)
            continue;

         FourVector P;
         P.SetSizeEtaPhi(M.pMc[i], M.etaMc[i], M.phiMc[i]);

         HVBChildren.Fill(M.idMc[i]);
         VBChildren.push_back(i);
         VBChildrenP.push_back(P);

         if(M.idMc[i] == 15 || M.idMc[i] == -15)
            HaveTauInChildren = true;
      }
      if(HaveTauInChildren == true)
         continue;

      // jets
      int QCDJetCount30 = 0;
      int QCDJetCount50 = 0;
      int QCDJetCount80 = 0;
      for(int i = 0; i < M.nAK5Jet; i++)
      {
         FourVector JetP(M.energyAK5Jet[i], M.pxAK5Jet[i], M.pyAK5Jet[i], M.pzAK5Jet[i]);

         if(fabs(JetP.GetEta()) > 3)   // don't look at HF jets
            continue;

         for(int j = 0; j < (int)VBChildrenP.size(); j++)
            HDRJetVBChild.Fill(GetDR(VBChildrenP[j], JetP));

         bool CloseToVBChild = false;
         for(int j = 0; j < (int)VBChildrenP.size() && CloseToVBChild == false; j++)
            if(GetDR(VBChildrenP[j], JetP) < 0.5)
               CloseToVBChild = true;
         if(CloseToVBChild == true)
            continue;

         if(JetP.GetPT() > 30)
            QCDJetCount30 = QCDJetCount30 + 1;
         if(JetP.GetPT() > 50)
            QCDJetCount50 = QCDJetCount50 + 1;
         if(JetP.GetPT() > 100)
            QCDJetCount80 = QCDJetCount80 + 1;

         HQCDJetPT.Fill(JetP.GetPT());
         if(JetP.GetPT() > 30)
         {
            HQCDJetEta.Fill(JetP.GetEta());
            HQCDJetPhi.Fill(JetP.GetPhi());
         }
      }
      HQCDJetCount30.Fill(QCDJetCount30);
      HQCDJetCount50.Fill(QCDJetCount50);
      HQCDJetCount80.Fill(QCDJetCount80);

      // b-tagging
      int TCHELCount30 = 0;
      int TCHEMCount30 = 0;
      int TCHETCount30 = 0;
      int TCHELCount50 = 0;
      int TCHEMCount50 = 0;
      int TCHETCount50 = 0;
      int TCHELCount80 = 0;
      int TCHEMCount80 = 0;
      int TCHETCount80 = 0;
      for(int i = 0; i < M.nAK5Jet; i++)
      {
         FourVector JetP(M.energyAK5Jet[i], M.pxAK5Jet[i], M.pyAK5Jet[i], M.pzAK5Jet[i]);
         if(JetP.GetPT() < 30)
            continue;
         if(fabs(JetP.GetEta()) > 3)
            continue;

         bool CloseToVBChild = false;
         for(int j = 0; j < (int)VBChildrenP.size() && CloseToVBChild == false; j++)
            if(GetDR(VBChildrenP[j], JetP) < 0.5)
               CloseToVBChild = true;
         if(CloseToVBChild == true)
            continue;
         
         if(JetP.GetPT() > 30)
            HQCDJetTCHE30.Fill(M.trackCountingHighEffBJetTagsAK5Jet[i]);
         if(JetP.GetPT() > 50)
            HQCDJetTCHE50.Fill(M.trackCountingHighEffBJetTagsAK5Jet[i]);
         if(JetP.GetPT() > 80)
            HQCDJetTCHE80.Fill(M.trackCountingHighEffBJetTagsAK5Jet[i]);
         
         if(JetP.GetPT() > 30 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 1.7)
            TCHELCount30 = TCHELCount30 + 1;
         if(JetP.GetPT() > 30 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 3.3)
            TCHEMCount30 = TCHEMCount30 + 1;
         if(JetP.GetPT() > 30 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 10.2)
            TCHETCount30 = TCHETCount30 + 1;
         if(JetP.GetPT() > 50 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 1.7)
            TCHELCount50 = TCHELCount50 + 1;
         if(JetP.GetPT() > 50 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 3.3)
            TCHEMCount50 = TCHEMCount50 + 1;
         if(JetP.GetPT() > 50 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 10.2)
            TCHETCount50 = TCHETCount50 + 1;
         if(JetP.GetPT() > 80 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 1.7)
            TCHELCount80 = TCHELCount80 + 1;
         if(JetP.GetPT() > 80 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 3.3)
            TCHEMCount80 = TCHEMCount80 + 1;
         if(JetP.GetPT() > 80 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 10.2)
            TCHETCount80 = TCHETCount80 + 1;

         if(JetP.GetPT() > 30 && M.trackCountingHighEffBJetTagsAK5Jet[i] > 1.7)
         {
            HQCDBJetPT.Fill(JetP.GetPT());
            HQCDBJetEta.Fill(JetP.GetEta());
            HQCDBJetPhi.Fill(JetP.GetPhi());
         }
      }
      HQCDJetTCHELCount30.Fill(TCHELCount30);
      HQCDJetTCHEMCount30.Fill(TCHEMCount30);
      HQCDJetTCHETCount30.Fill(TCHETCount30);
      HQCDJetTCHELCount50.Fill(TCHELCount50);
      HQCDJetTCHEMCount50.Fill(TCHEMCount50);
      HQCDJetTCHETCount50.Fill(TCHETCount50);
      HQCDJetTCHELCount80.Fill(TCHELCount80);
      HQCDJetTCHEMCount80.Fill(TCHEMCount80);
      HQCDJetTCHETCount80.Fill(TCHETCount80);

      // Looking at jets with b-event-tagging
      for(int i = 0; i < M.nAK5Jet; i++)
      {
         FourVector JetP(M.energyAK5Jet[i], M.pxAK5Jet[i], M.pyAK5Jet[i], M.pzAK5Jet[i]);

         if(fabs(JetP.GetEta()) > 3)   // don't look at HF jets
            continue;

         bool CloseToVBChild = false;
         for(int j = 0; j < (int)VBChildrenP.size() && CloseToVBChild == false; j++)
            if(GetDR(VBChildrenP[j], JetP) < 0.5)
               CloseToVBChild = true;
         if(CloseToVBChild == true)
            continue;

         if(TCHELCount80 >= 2)
         {
            HTaggedEventQCDJetPT.Fill(JetP.GetPT());
            if(JetP.GetPT() > 30)
            {
               HTaggedEventQCDJetEta.Fill(JetP.GetEta());
               HTaggedEventQCDJetPhi.Fill(JetP.GetPhi());
            }
         }
         if(TCHELCount80 >= 1)
         {
            HSingleTaggedEventQCDJetPT.Fill(JetP.GetPT());
            if(JetP.GetPT() > 30)
            {
               HSingleTaggedEventQCDJetEta.Fill(JetP.GetEta());
               HSingleTaggedEventQCDJetPhi.Fill(JetP.GetPhi());
            }
         }
         if(TCHELCount30 >= 2)
         {
            HLowTaggedEventQCDJetPT.Fill(JetP.GetPT());
            if(JetP.GetPT() > 30)
            {
               HLowTaggedEventQCDJetEta.Fill(JetP.GetEta());
               HLowTaggedEventQCDJetPhi.Fill(JetP.GetPhi());
            }
         }
      }

      if(TCHELCount80 >= 2)
      {
         HTaggedEventQCDJetCount30.Fill(QCDJetCount30);
         HTaggedEventQCDJetCount50.Fill(QCDJetCount50);
         HTaggedEventQCDJetCount80.Fill(QCDJetCount80);
      }
      if(TCHELCount80 >= 1)
      {
         HSingleTaggedEventQCDJetCount30.Fill(QCDJetCount30);
         HSingleTaggedEventQCDJetCount50.Fill(QCDJetCount50);
         HSingleTaggedEventQCDJetCount80.Fill(QCDJetCount80);
      }
      if(TCHELCount30 >= 1)
      {
         HLowTaggedEventQCDJetCount30.Fill(QCDJetCount30);
         HLowTaggedEventQCDJetCount50.Fill(QCDJetCount50);
         HLowTaggedEventQCDJetCount80.Fill(QCDJetCount80);
      }

      // razor with b-event-tagging
      vector<FourVector> GoodJets;
      for(int i = 0; i < M.nAK5Jet; i++)
      {
         FourVector JetP(M.energyAK5Jet[i], M.pxAK5Jet[i], M.pyAK5Jet[i], M.pzAK5Jet[i]);
         
         if(fabs(JetP.GetEta()) > 3)   // don't look at HF jets
            continue;

         bool CloseToVBChild = false;
         for(int j = 0; j < (int)VBChildrenP.size() && CloseToVBChild == false; j++)
            if(GetDR(VBChildrenP[j], JetP) < 0.5)
               CloseToVBChild = true;
         if(CloseToVBChild == true)
            continue;

         if(JetP.GetPT() > 40)
            GoodJets.push_back(JetP);
      }
      if(GoodJets.size() < 2 || GoodJets.size() > 20)
         continue;
      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      FourVector PFMET(0, M.pxPFMet[0], M.pyPFMet[0], 0);
      for(int i = 0; i < M.nMc; i++)   // correct back the leptons in missing energy
      {
         if(M.mothMc[i] != VBIndex)
            continue;
         if(M.statusMc[i] == 2)
            continue;

         if(M.idMc[i] == 11 || M.idMc[i] == -11 || M.idMc[i] == 13 || M.idMc[i] == -13)   // e/mu
         {
            FourVector ParticleP;
            ParticleP.SetSizeEtaPhi(M.pMc[i], M.etaMc[i], M.phiMc[i]);
            PFMET = PFMET + ParticleP;   // or minus?
         }
      }

      double MRNew = Get2011MR(Groups[0], Groups[1]);
      double RNew = Get2011R(Groups[0], Groups[1], PFMET);
      double R2New = RNew * RNew;

      if(TCHELCount80 >= 2)
      {
         HTaggedEventMRNew.Fill(MRNew);
         if(R2New > 0.05)   HTaggedEventMRNew_R2New005.Fill(MRNew);
         if(R2New > 0.10)   HTaggedEventMRNew_R2New010.Fill(MRNew);
         if(R2New > 0.15)   HTaggedEventMRNew_R2New015.Fill(MRNew);
         if(R2New > 0.20)   HTaggedEventMRNew_R2New020.Fill(MRNew);
         if(R2New > 0.25)   HTaggedEventMRNew_R2New025.Fill(MRNew);

         HTaggedEventR2New.Fill(R2New);
         if(MRNew > 300)   HTaggedEventR2New_MRNew300.Fill(R2New);
         if(MRNew > 400)   HTaggedEventR2New_MRNew400.Fill(R2New);
         if(MRNew > 500)   HTaggedEventR2New_MRNew500.Fill(R2New);
         if(MRNew > 600)   HTaggedEventR2New_MRNew600.Fill(R2New);
         if(MRNew > 700)   HTaggedEventR2New_MRNew700.Fill(R2New);

         HTaggedEventMRNewVsR2New.Fill(MRNew, R2New);
      }
      
      if(TCHELCount80 >= 1)
      {
         HSingleTaggedEventMRNew.Fill(MRNew);
         if(R2New > 0.05)   HSingleTaggedEventMRNew_R2New005.Fill(MRNew);
         if(R2New > 0.10)   HSingleTaggedEventMRNew_R2New010.Fill(MRNew);
         if(R2New > 0.15)   HSingleTaggedEventMRNew_R2New015.Fill(MRNew);
         if(R2New > 0.20)   HSingleTaggedEventMRNew_R2New020.Fill(MRNew);
         if(R2New > 0.25)   HSingleTaggedEventMRNew_R2New025.Fill(MRNew);

         HSingleTaggedEventR2New.Fill(R2New);
         if(MRNew > 300)   HSingleTaggedEventR2New_MRNew300.Fill(R2New);
         if(MRNew > 400)   HSingleTaggedEventR2New_MRNew400.Fill(R2New);
         if(MRNew > 500)   HSingleTaggedEventR2New_MRNew500.Fill(R2New);
         if(MRNew > 600)   HSingleTaggedEventR2New_MRNew600.Fill(R2New);
         if(MRNew > 700)   HSingleTaggedEventR2New_MRNew700.Fill(R2New);

         HSingleTaggedEventMRNewVsR2New.Fill(MRNew, R2New);
      }
      
      if(TCHELCount30 >= 2)
      {
         HLowTaggedEventMRNew.Fill(MRNew);
         if(R2New > 0.05)   HLowTaggedEventMRNew_R2New005.Fill(MRNew);
         if(R2New > 0.10)   HLowTaggedEventMRNew_R2New010.Fill(MRNew);
         if(R2New > 0.15)   HLowTaggedEventMRNew_R2New015.Fill(MRNew);
         if(R2New > 0.20)   HLowTaggedEventMRNew_R2New020.Fill(MRNew);
         if(R2New > 0.25)   HLowTaggedEventMRNew_R2New025.Fill(MRNew);

         HLowTaggedEventR2New.Fill(R2New);
         if(MRNew > 300)   HLowTaggedEventR2New_MRNew300.Fill(R2New);
         if(MRNew > 400)   HLowTaggedEventR2New_MRNew400.Fill(R2New);
         if(MRNew > 500)   HLowTaggedEventR2New_MRNew500.Fill(R2New);
         if(MRNew > 600)   HLowTaggedEventR2New_MRNew600.Fill(R2New);
         if(MRNew > 700)   HLowTaggedEventR2New_MRNew700.Fill(R2New);

         HLowTaggedEventMRNewVsR2New.Fill(MRNew, R2New);
      }
   }

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase + " --- check kinematics");

   PsFile.AddTextPage("Basic sanity check to get started");
   PsFile.AddPlot(HNPU, "", true);
   PsFile.AddPlot(HNPV, "", true);

   PsFile.AddTextPage("Tracing vector-boson, and remove events with taus");
   PsFile.AddPlot(HVBCount, "text00 hist", false);
   PsFile.AddPlot(HVBCountPerEvent, "text00 hist", true);
   PsFile.AddPlot(HVBChildren, "", true);

   PsFile.AddTextPage("Jets (not from VB decays)");
   PsFile.AddPlot(HDRJetVBChild, "hist", true);
   PsFile.AddPlot(HQCDJetCount30, "hist text00", true);
   PsFile.AddPlot(HQCDJetCount50, "hist text00", true);
   PsFile.AddPlot(HQCDJetCount80, "text00 hist", true);
   PsFile.AddPlot(HQCDJetPT, "", true);
   PsFile.AddPlot(HQCDJetEta, "", true);
   PsFile.AddPlot(HQCDJetPhi, "", true);

   PsFile.AddTextPage("Jets (not from VB decays) b-tagging");
   PsFile.AddPlot(HQCDJetTCHE30, "", true);
   PsFile.AddPlot(HQCDJetTCHELCount30, "", true);
   PsFile.AddPlot(HQCDJetTCHEMCount30, "", true);
   PsFile.AddPlot(HQCDJetTCHETCount30, "", true);
   PsFile.AddPlot(HQCDJetTCHE50, "", true);
   PsFile.AddPlot(HQCDJetTCHELCount50, "", true);
   PsFile.AddPlot(HQCDJetTCHEMCount50, "", true);
   PsFile.AddPlot(HQCDJetTCHETCount50, "", true);
   PsFile.AddPlot(HQCDJetTCHE80, "", true);
   PsFile.AddPlot(HQCDJetTCHELCount80, "", true);
   PsFile.AddPlot(HQCDJetTCHEMCount80, "", true);
   PsFile.AddPlot(HQCDJetTCHETCount80, "", true);
   PsFile.AddPlot(HQCDBJetPT, "", true);
   PsFile.AddPlot(HQCDBJetEta, "", true);
   PsFile.AddPlot(HQCDBJetPhi, "", true);

   PsFile.AddTextPage("Jets in tagged (LL, 80) events");
   PsFile.AddPlot(HTaggedEventQCDJetCount30, "", true);
   PsFile.AddPlot(HTaggedEventQCDJetCount50, "", true);
   PsFile.AddPlot(HTaggedEventQCDJetCount80, "", true);
   PsFile.AddPlot(HTaggedEventQCDJetPT, "", true);
   PsFile.AddPlot(HTaggedEventQCDJetEta, "", true);
   PsFile.AddPlot(HTaggedEventQCDJetPhi, "", true);

   PsFile.AddTextPage("Razor in tagged (LL, 80) events");
   PsFile.AddPlot(HTaggedEventMRNewVsR2New, "colz", false);
   PsFile.AddPlot(HTaggedEventMRNew, "", true);
   PsFile.AddPlot(HTaggedEventMRNew_R2New005, "", true);
   PsFile.AddPlot(HTaggedEventMRNew_R2New010, "", true);
   PsFile.AddPlot(HTaggedEventMRNew_R2New015, "", true);
   PsFile.AddPlot(HTaggedEventMRNew_R2New020, "", true);
   PsFile.AddPlot(HTaggedEventMRNew_R2New025, "", true);
   PsFile.AddPlot(HTaggedEventR2New, "", true);
   PsFile.AddPlot(HTaggedEventR2New_MRNew300, "", true);
   PsFile.AddPlot(HTaggedEventR2New_MRNew400, "", true);
   PsFile.AddPlot(HTaggedEventR2New_MRNew500, "", true);
   PsFile.AddPlot(HTaggedEventR2New_MRNew600, "", true);
   PsFile.AddPlot(HTaggedEventR2New_MRNew700, "", true);
   
   PsFile.AddTextPage("Jets in tagged (L, 80) events");
   PsFile.AddPlot(HSingleTaggedEventQCDJetCount30, "", true);
   PsFile.AddPlot(HSingleTaggedEventQCDJetCount50, "", true);
   PsFile.AddPlot(HSingleTaggedEventQCDJetCount80, "", true);
   PsFile.AddPlot(HSingleTaggedEventQCDJetPT, "", true);
   PsFile.AddPlot(HSingleTaggedEventQCDJetEta, "", true);
   PsFile.AddPlot(HSingleTaggedEventQCDJetPhi, "", true);
   
   PsFile.AddTextPage("Razor in singly tagged (L, 80) events");
   PsFile.AddPlot(HSingleTaggedEventMRNewVsR2New, "colz", false);
   PsFile.AddPlot(HSingleTaggedEventMRNew, "", true);
   PsFile.AddPlot(HSingleTaggedEventMRNew_R2New005, "", true);
   PsFile.AddPlot(HSingleTaggedEventMRNew_R2New010, "", true);
   PsFile.AddPlot(HSingleTaggedEventMRNew_R2New015, "", true);
   PsFile.AddPlot(HSingleTaggedEventMRNew_R2New020, "", true);
   PsFile.AddPlot(HSingleTaggedEventMRNew_R2New025, "", true);
   PsFile.AddPlot(HSingleTaggedEventR2New, "", true);
   PsFile.AddPlot(HSingleTaggedEventR2New_MRNew300, "", true);
   PsFile.AddPlot(HSingleTaggedEventR2New_MRNew400, "", true);
   PsFile.AddPlot(HSingleTaggedEventR2New_MRNew500, "", true);
   PsFile.AddPlot(HSingleTaggedEventR2New_MRNew600, "", true);
   PsFile.AddPlot(HSingleTaggedEventR2New_MRNew700, "", true);
   
   PsFile.AddTextPage("Jets in tagged (LL, 30) events");
   PsFile.AddPlot(HLowTaggedEventQCDJetCount30, "", true);
   PsFile.AddPlot(HLowTaggedEventQCDJetCount50, "", true);
   PsFile.AddPlot(HLowTaggedEventQCDJetCount80, "", true);
   PsFile.AddPlot(HLowTaggedEventQCDJetPT, "", true);
   PsFile.AddPlot(HLowTaggedEventQCDJetEta, "", true);
   PsFile.AddPlot(HLowTaggedEventQCDJetPhi, "", true);

   PsFile.AddTextPage("Razor in tagged (LL, 30) events");
   PsFile.AddPlot(HLowTaggedEventMRNewVsR2New, "colz", false);
   PsFile.AddPlot(HLowTaggedEventMRNew, "", true);
   PsFile.AddPlot(HLowTaggedEventMRNew_R2New005, "", true);
   PsFile.AddPlot(HLowTaggedEventMRNew_R2New010, "", true);
   PsFile.AddPlot(HLowTaggedEventMRNew_R2New015, "", true);
   PsFile.AddPlot(HLowTaggedEventMRNew_R2New020, "", true);
   PsFile.AddPlot(HLowTaggedEventMRNew_R2New025, "", true);
   PsFile.AddPlot(HLowTaggedEventR2New, "", true);
   PsFile.AddPlot(HLowTaggedEventR2New_MRNew300, "", true);
   PsFile.AddPlot(HLowTaggedEventR2New_MRNew400, "", true);
   PsFile.AddPlot(HLowTaggedEventR2New_MRNew500, "", true);
   PsFile.AddPlot(HLowTaggedEventR2New_MRNew600, "", true);
   PsFile.AddPlot(HLowTaggedEventR2New_MRNew700, "", true);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   HNPU.Write();
   HNPV.Write();

   HVBCount.Write();
   HVBCountPerEvent.Write();
   HVBChildren.Write();

   HDRJetVBChild.Write();
   HQCDJetCount30.Write();
   HQCDJetCount50.Write();
   HQCDJetCount80.Write();
   HQCDJetPT.Write();
   HQCDJetEta.Write();
   HQCDJetPhi.Write();

   HQCDJetTCHE30.Write();
   HQCDJetTCHE50.Write();
   HQCDJetTCHE80.Write();
   HQCDJetTCHELCount30.Write();
   HQCDJetTCHEMCount30.Write();
   HQCDJetTCHETCount30.Write();
   HQCDJetTCHELCount50.Write();
   HQCDJetTCHEMCount50.Write();
   HQCDJetTCHETCount50.Write();
   HQCDJetTCHELCount80.Write();
   HQCDJetTCHEMCount80.Write();
   HQCDJetTCHETCount80.Write();
   HQCDBJetPT.Write();
   HQCDBJetEta.Write();
   HQCDBJetPhi.Write();

   HTaggedEventQCDJetCount30.Write();
   HTaggedEventQCDJetCount50.Write();
   HTaggedEventQCDJetCount80.Write();
   HTaggedEventQCDJetPT.Write();
   HTaggedEventQCDJetEta.Write();
   HTaggedEventQCDJetPhi.Write();

   HSingleTaggedEventQCDJetCount30.Write();
   HSingleTaggedEventQCDJetCount50.Write();
   HSingleTaggedEventQCDJetCount80.Write();
   HSingleTaggedEventQCDJetPT.Write();
   HSingleTaggedEventQCDJetEta.Write();
   HSingleTaggedEventQCDJetPhi.Write();

   HLowTaggedEventQCDJetCount30.Write();
   HLowTaggedEventQCDJetCount50.Write();
   HLowTaggedEventQCDJetCount80.Write();
   HLowTaggedEventQCDJetPT.Write();
   HLowTaggedEventQCDJetEta.Write();
   HLowTaggedEventQCDJetPhi.Write();

   HTaggedEventMRNew.Write();
   HTaggedEventMRNew_R2New005.Write();
   HTaggedEventMRNew_R2New010.Write();
   HTaggedEventMRNew_R2New015.Write();
   HTaggedEventMRNew_R2New020.Write();
   HTaggedEventMRNew_R2New025.Write();

   HTaggedEventR2New.Write();
   HTaggedEventR2New_MRNew300.Write();
   HTaggedEventR2New_MRNew400.Write();
   HTaggedEventR2New_MRNew500.Write();
   HTaggedEventR2New_MRNew600.Write();
   HTaggedEventR2New_MRNew700.Write();

   HTaggedEventMRNewVsR2New.Write();

   HSingleTaggedEventMRNew.Write();
   HSingleTaggedEventMRNew_R2New005.Write();
   HSingleTaggedEventMRNew_R2New010.Write();
   HSingleTaggedEventMRNew_R2New015.Write();
   HSingleTaggedEventMRNew_R2New020.Write();
   HSingleTaggedEventMRNew_R2New025.Write();

   HSingleTaggedEventR2New.Write();
   HSingleTaggedEventR2New_MRNew300.Write();
   HSingleTaggedEventR2New_MRNew400.Write();
   HSingleTaggedEventR2New_MRNew500.Write();
   HSingleTaggedEventR2New_MRNew600.Write();
   HSingleTaggedEventR2New_MRNew700.Write();

   HSingleTaggedEventMRNewVsR2New.Write();

   HLowTaggedEventMRNew.Write();
   HLowTaggedEventMRNew_R2New005.Write();
   HLowTaggedEventMRNew_R2New010.Write();
   HLowTaggedEventMRNew_R2New015.Write();
   HLowTaggedEventMRNew_R2New020.Write();
   HLowTaggedEventMRNew_R2New025.Write();

   HLowTaggedEventR2New.Write();
   HLowTaggedEventR2New_MRNew300.Write();
   HLowTaggedEventR2New_MRNew400.Write();
   HLowTaggedEventR2New_MRNew500.Write();
   HLowTaggedEventR2New_MRNew600.Write();
   HLowTaggedEventR2New_MRNew700.Write();

   HLowTaggedEventMRNewVsR2New.Write();

   F.Close();

   return 0;
}





