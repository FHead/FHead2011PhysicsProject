//----------------------------------------------------------------------------
#include <iostream>
using namespace std;
//----------------------------------------------------------------------------
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
//----------------------------------------------------------------------------
#include "TauHelperFunctions2.h"
#include "ChainAll.h"
//----------------------------------------------------------------------------
#include "ReadNTPTreeV3.h"
//----------------------------------------------------------------------------
int main();
bool IsGoodWP80Electron(NTPTreeMessenger &M, int index);
bool IsGoodTightMuon(NTPTreeMessenger &M, int index);
int CountWDecayProduct(NTPTreeMessenger &M, int ChildrenID);
//----------------------------------------------------------------------------
int main()
{
   // Get input
   TChain *InputTree = ChainAll("TTbar.list", "ntp1");

   NTPTreeMessenger M;
   M.SetBranchAddress(InputTree);

   // Prepare output
   TFile OutputFile("TTbarReducedTree.root", "RECREATE");

   // common variables
   double MR = 0;
   double MRStar = 0;
   double R = 0;
   double RStar = 0;
   double GammaMRStar = 0;
   double BetaR = 0;
   int MCCategory = 0;
   int BoxCategory = 0;

   // output trees
   TTree OutputTree("OutputTree", "OutputTree");
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("MRStar", &MRStar, "MRStar/D");
   OutputTree.Branch("R", &R, "R/D");
   OutputTree.Branch("RStar", &RStar, "RStar/D");
   OutputTree.Branch("GammaMRStar", &GammaMRStar, "GammaMRStar/D");
   OutputTree.Branch("BetaR", &BetaR, "BetaR/D");
   OutputTree.Branch("MCCategory", &MCCategory, "MCCategory/I");
   OutputTree.Branch("BoxCategory", &BoxCategory, "BoxCategory/I");

   // counting histogram
   TH2D HCategoryCount("HCategoryCount", "Count of events in each category;MC Category;Box", 10, 0, 10, 6, 0, 6);
   HCategoryCount.GetXaxis()->SetBinLabel(1, "e e");
   HCategoryCount.GetXaxis()->SetBinLabel(2, "e mu");
   HCategoryCount.GetXaxis()->SetBinLabel(3, "e tau");
   HCategoryCount.GetXaxis()->SetBinLabel(4, "e had");
   HCategoryCount.GetXaxis()->SetBinLabel(5, "mu mu");
   HCategoryCount.GetXaxis()->SetBinLabel(6, "mu tau");
   HCategoryCount.GetXaxis()->SetBinLabel(7, "mu had");
   HCategoryCount.GetXaxis()->SetBinLabel(8, "tau tau");
   HCategoryCount.GetXaxis()->SetBinLabel(9, "tau had");
   HCategoryCount.GetXaxis()->SetBinLabel(10, "had had");
   HCategoryCount.GetYaxis()->SetBinLabel(1, "had");
   HCategoryCount.GetYaxis()->SetBinLabel(2, "e");
   HCategoryCount.GetYaxis()->SetBinLabel(3, "mu");
   HCategoryCount.GetYaxis()->SetBinLabel(4, "e e");
   HCategoryCount.GetYaxis()->SetBinLabel(5, "e mu");
   HCategoryCount.GetYaxis()->SetBinLabel(6, "mu mu");

   // Start looping over events
   int EntryCount = InputTree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      // some output for the impatient
      if((iEntry + 1) % 50000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      // Get event
      InputTree->GetEntry(iEntry);

      // Calculate MR/R/MRStar/RStar/GammaMRStar/BetaR
      vector<FourVector> InputJets;
      for(int i = 0; i < M.nAK5PFPUcorrJet; i++)
      {
         if(M.etaAK5PFPUcorrJet[i] > 3 || M.etaAK5PFPUcorrJet[i] < -3)
            continue;
         if(M.pxAK5PFPUcorrJet[i] * M.pxAK5PFPUcorrJet[i] + M.pyAK5PFPUcorrJet[i] * M.pyAK5PFPUcorrJet[i]
            < 40 * 40)
            continue;

         InputJets.push_back(FourVector(M.energyAK5PFPUcorrJet[i], M.pxAK5PFPUcorrJet[i],
            M.pyAK5PFPUcorrJet[i], M.pzAK5PFPUcorrJet[i]));
      }
      if(InputJets.size() < 2)
         continue;
      if(InputJets.size() > 20)
         continue;
      vector<FourVector> Hemispheres = SplitIntoGroups(InputJets, true);

      if(GetDPhi(Hemispheres[0], Hemispheres[1]) > 2.8)
         continue;

      FourVector MET(0, M.pxPFMet[0], M.pyPFMet[0], 0);

      MR = GetMR(Hemispheres[0], Hemispheres[1]);
      R = GetR(Hemispheres[0], Hemispheres[1], MET);
      MRStar = GetMRStar(Hemispheres[0], Hemispheres[1]);
      RStar = GetRStar(Hemispheres[0], Hemispheres[1], MET);
      GammaMRStar = MRStar * GetGammaRStar(Hemispheres[0], Hemispheres[1]);
      BetaR = (Hemispheres[0][0] - Hemispheres[1][0]) / (Hemispheres[0][3] - Hemispheres[1][3]);

      // Final state categorization
      int GoodElectronCount = 0;
      for(int index = 0; index < M.nEle; index++)
         if(IsGoodWP80Electron(M, index) == true)
            GoodElectronCount = GoodElectronCount + 1;

      int GoodMuonCount = 0;
      for(int index = 0; index < M.nMuon; index++)
         if(IsGoodTightMuon(M, index) == true)
            GoodMuonCount = GoodMuonCount + 1;

      if(GoodElectronCount >= 2)
         BoxCategory = 3;
      else if(GoodMuonCount >= 2)
         BoxCategory = 5;
      else if(GoodElectronCount >= 1 && GoodMuonCount >= 1)
         BoxCategory = 4;
      else if(GoodElectronCount >= 1)
         BoxCategory = 1;
      else if(GoodMuonCount >= 1)
         BoxCategory = 2;
      else
         BoxCategory = 0;

      // MC-level categorization (W decays)
      int WENuCount = CountWDecayProduct(M, 11);
      int WMuNuCount = CountWDecayProduct(M, 13);
      int WTauNuCount = CountWDecayProduct(M, 15);

      if(WENuCount == 2)
         MCCategory = 0;
      else if(WENuCount == 1 && WMuNuCount == 1)
         MCCategory = 1;
      else if(WENuCount == 1 && WTauNuCount == 1)
         MCCategory = 2;
      else if(WENuCount == 1)
         MCCategory = 3;
      else if(WMuNuCount == 2)
         MCCategory = 4;
      else if(WMuNuCount == 1 && WTauNuCount == 1)
         MCCategory = 5;
      else if(WMuNuCount == 1)
         MCCategory = 6;
      else if(WTauNuCount == 2)
         MCCategory = 7;
      else if(WTauNuCount == 1)
         MCCategory = 8;
      else
         MCCategory = 9;

      HCategoryCount.Fill(MCCategory, BoxCategory);

      OutputTree.Fill();
   }

   // Write stuff
   OutputTree.Write();
   HCategoryCount.Write();

   // Close stuff
   OutputFile.Close();

   // Delete stuff
   delete InputTree;

   // Happy ending
   return 0;
}
//----------------------------------------------------------------------------
bool IsGoodWP80Electron(NTPTreeMessenger &M, int index)
{
   bool IsGoodElectron = true;

   bool IsBarrel = false;
   bool IsEndcap = false;

   int iSC = M.superClusterIndexEle[index];
   if(iSC < 0 || iSC >= M.nSC)   // something wrong!  electron don't have SC associated?
      IsGoodElectron = false;

   double eta = M.etaSC[iSC];
   if(fabs(eta) < 1.4442)
      IsBarrel = true;
   if(fabs(eta) > 1.566 && fabs(eta) < 2.5)
      IsEndcap = true;

   double TrackIsolation = M.dr03TkSumPtEle[index];
   double EcalIsolation = M.dr03EcalRecHitSumEtEle[index];
   double HcalIsolation = M.dr03HcalTowerSumEtEle[index];

   double PT = sqrt(M.pxEle[index] * M.pxEle[index] + M.pyEle[index] * M.pyEle[index]);
   if(PT < 15)
      IsGoodElectron = false;

   double SigmaIEtaIEta = M.covIEtaIEtaSC[iSC];
   double DEta = fabs(M.deltaEtaAtVtxEle[index]);
   double DPhi = fabs(M.deltaPhiAtVtxEle[index]);

   double CombinedIsolation = 0;
   if(IsBarrel == true)
      CombinedIsolation = TrackIsolation + max(0.0, EcalIsolation - 1) + HcalIsolation;
   else
      CombinedIsolation = TrackIsolation + EcalIsolation + HcalIsolation;
   CombinedIsolation = CombinedIsolation - M.rhoFastjet * PI * 0.3 * 0.3;
   CombinedIsolation = CombinedIsolation / PT;

   double CovariantDistance = M.convDistEle[index];
   double CovariantDCotTheta = M.convDcotEle[index];

   if(CovariantDistance > 0.02)      IsGoodElectron = false;
   if(CovariantDCotTheta > 0.02)     IsGoodElectron = false;
   if(IsBarrel == true)
   {
      if(CombinedIsolation > 0.040)  IsGoodElectron = false;
      if(SigmaIEtaIEta > 0.01)       IsGoodElectron = false;
      if(DPhi > 0.027)               IsGoodElectron = false;
      if(DEta > 0.005)               IsGoodElectron = false;
   }
   if(IsEndcap == true)
   {
      if(CombinedIsolation > 0.033)  IsGoodElectron = false;
      if(SigmaIEtaIEta > 0.031)      IsGoodElectron = false;
      if(DPhi > 0.021)               IsGoodElectron = false;
      if(DEta > 0.006)               IsGoodElectron = false;
   }

   return IsGoodElectron;
}
//----------------------------------------------------------------------------
bool IsGoodTightMuon(NTPTreeMessenger &M, int index)
{
   bool IsGoodMuon = true;

   double PT = sqrt(M.pxMuon[index] * M.pxMuon[index] + M.pyMuon[index] * M.pyMuon[index]);
   if(PT < 15)
      IsGoodMuon = false;

   double CombinedIsolation = M.emEt03Muon[index] + M.hadEt03Muon[index] + M.sumPt03Muon[index];
   CombinedIsolation = CombinedIsolation - M.rhoFastjet * PI * 0.3 * 0.3;
   CombinedIsolation = CombinedIsolation / PT;

   if(CombinedIsolation >= 0.15)
      IsGoodMuon = false;

   int iTrack = M.trackIndexMuon[index];
   if(iTrack < 0 || iTrack >= M.nTrack)   // something's wrong.  VERY wrong.
      IsGoodMuon = false;

   if(M.numberOfValidStripTIBHitsTrack[iTrack]
      + M.numberOfValidStripTIDHitsTrack[iTrack]
      + M.numberOfValidStripTOBHitsTrack[iTrack]
      + M.numberOfValidStripTECHitsTrack[iTrack] <= 10)
      IsGoodMuon = false;

   if(M.numberOfValidPixelBarrelHitsTrack[iTrack] + M.numberOfValidPixelEndcapHitsTrack[iTrack] == 0)
      IsGoodMuon = false;

   if(fabs(M.transvImpactParTrack[iTrack]) >= 0.2)
      IsGoodMuon = false;

   return IsGoodMuon;
}
//----------------------------------------------------------------------------
int CountWDecayProduct(NTPTreeMessenger &M, int ChildrenID)
{
   int Count = 0;

   for(int i = 0; i < M.nMc; i++)
   {
      if(fabs(M.idMc[i]) != ChildrenID)
         continue;
      if(M.mothMc[i] < 0)
         continue;
      if(fabs(M.idMc[M.mothMc[i]]) == 24)
         Count = Count + 1;
   }

   return Count;
}
//----------------------------------------------------------------------------


