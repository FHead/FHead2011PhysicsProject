#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

int main(int argc, char *argv[]);
void OverlayHistograms(PsFileHelper &PsFile, TH1D H1, TH1D H2, bool LogY = false, int Mode = 0);
void PlotWithCut(PsFileHelper &PsFile, TH1D &H, double CutPosition, double CutPosition2 = -10000);

int main(int argc, char *argv[])
{
   string InputFile = "MCSamples/GJet_200_HT_inf_All.root";
   string OutputBase = "GJet200";

   if(argc == 2)
   {
      InputFile = argv[1];
      OutputBase = "Random";
   }
   if(argc >= 3)
   {
      InputFile = argv[1];
      OutputBase = argv[2];
   }

   TChain Tree("ReducedTree", "ReducedTree");
   Tree.AddFile(InputFile.c_str());

   int PhotonCount = 0;
   double PT[10] = {0};
   double Eta[10] = {0};
   double Phi[10] = {0};
   double HoE[10] = {0};
   bool Seed[10] = {false};
   double SigmaIEtaIEta[10] = {0};
   double TrackIso[10] = {0};
   double HollowTrackIso[10] = {0};
   double EcalIso[10] = {0};
   double HcalIso[10] = {0};
   double R9[10] = {0};
   double Rho = 0;

   Tree.SetBranchAddress("PhotonCount", &PhotonCount);
   Tree.SetBranchAddress("AllPhotonPT", PT);
   Tree.SetBranchAddress("AllPhotonEta", Eta);
   Tree.SetBranchAddress("AllPhotonPhi", Phi);
   Tree.SetBranchAddress("AllPhotonHOverE", HoE);
   Tree.SetBranchAddress("AllPhotonSeed", Seed);
   Tree.SetBranchAddress("AllPhotonSigmaIEtaIEta", SigmaIEtaIEta);
   Tree.SetBranchAddress("AllPhotonTrackIsolation", TrackIso);
   Tree.SetBranchAddress("AllPhotonHollowTrackIsolation", HollowTrackIso);
   Tree.SetBranchAddress("AllPhotonEcalIsolation", EcalIso);
   Tree.SetBranchAddress("AllPhotonHcalIsolation", HcalIso);
   Tree.SetBranchAddress("AllPhotonR9", R9);
   Tree.SetBranchAddress("Rho", &Rho);

   TH1D HPhotonPTBarrel("HPhotonPTBarrel", "Barrel photon PT;PT (GeV)", 100, 0, 300);
   TH1D HPhotonPTEndcap("HPhotonPTEndcap", "Endcap photon PT;PT (GeV)", 100, 0, 300);
   TH1D HPhotonEtaBarrel("HPhotonEtaBarrel", "Barrel photon eta; eta", 100, -3, 3);
   TH1D HPhotonEtaEndcap("HPhotonEtaEndcap", "Endcap photon eta; eta", 100, -3, 3);
   TH1D HPhotonPhiBarrel("HPhotonPhiBarrel", "Barrel photon phi; phi", 100, -3.2, 3.2);
   TH1D HPhotonPhiEndcap("HPhotonPhiEndcap", "Endcap photon phi; phi", 100, -3.2, 3.2);
   TH1D HPhotonHoEBarrel("HPhotonHoEBarrel", "Barrel photon H/E; H/E", 100, 0, 1);
   TH1D HPhotonHoEEndcap("HPhotonHoEEndcap", "Endcap photon H/E; H/E", 100, 0, 1);
   TH1D HPhotonSigmaIEtaIEtaBarrel("HPhotonSigmaIEtaIEtaBarrel",
      "Barrel photon SigmaIEtaIEta; SigmaIEtaIEta", 100, 0, 0.06);
   TH1D HPhotonSigmaIEtaIEtaEndcap("HPhotonSigmaIEtaIEtaEndcap",
      "Endcap photon SigmaIEtaIEta; SigmaIEtaIEta", 100, 0, 0.06);
   TH1D HPhotonTrackIsoBarrel("HPhotonTrackIsoBarrel", "Barrel photon relative track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonTrackIsoEndcap("HPhotonTrackIsoEndcap", "Endcap photon relative track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHollowTrackIsoBarrel("HPhotonHollowTrackIsoBarrel",
      "Barrel photon relative hollow track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHollowTrackIsoEndcap("HPhotonHollowTrackIsoEndcap",
      "Endcap photon relative hollow track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHcalIsoBarrel("HPhotonHcalIsoBarrel", "Barrel photon relative Hcal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHcalIsoEndcap("HPhotonHcalIsoEndcap", "Endcap photon relative Hcal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonEcalIsoBarrel("HPhotonEcalIsoBarrel", "Barrel photon relative Ecal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonEcalIsoEndcap("HPhotonEcalIsoEndcap", "Endcap photon relative Ecal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonIsoBarrel("HPhotonIsoBarrel", "Barrel photon iso; pt", 100, -20, 100);
   TH1D HPhotonIsoEndcap("HPhotonIsoEndcap", "Endcap photon iso; pt", 100, -20, 100);
   TH1D HPhotonR9Barrel("HPhotonR9Barrel", "Barrel photon R9", 100, 0, 2.5);
   TH1D HPhotonR9Endcap("HPhotonR9Endcap", "Endcap photon R9", 100, 0, 2.5);
   TH1D HPhotonSeedBarrel("HPhotonSeedBarrel", "Photon seed in barrel", 4, -1.5, 2.5);
   TH1D HPhotonSeedEndcap("HPhotonSeedEndcap", "Photon seed in barrel", 4, -1.5, 2.5);

   HPhotonSeedBarrel.GetXaxis()->SetBinLabel(2, "No");
   HPhotonSeedBarrel.GetXaxis()->SetBinLabel(3, "Yes");
   HPhotonSeedEndcap.GetXaxis()->SetBinLabel(2, "No");
   HPhotonSeedEndcap.GetXaxis()->SetBinLabel(3, "Yes");

   TH1D HPhotonPTBarrelWithSeed("HPhotonPTBarrelWithSeed", "Barrel (with seed) photon PT;PT (GeV)", 100, 0, 300);
   TH1D HPhotonPTEndcapWithSeed("HPhotonPTEndcapWithSeed", "Endcap (with seed) photon PT;PT (GeV)", 100, 0, 300);
   TH1D HPhotonEtaBarrelWithSeed("HPhotonEtaBarrelWithSeed", "Barrel (with seed) photon eta; eta", 100, -3, 3);
   TH1D HPhotonEtaEndcapWithSeed("HPhotonEtaEndcapWithSeed", "Endcap (with seed) photon eta; eta", 100, -3, 3);
   TH1D HPhotonPhiBarrelWithSeed("HPhotonPhiBarrelWithSeed", "Barrel (with seed) photon phi; phi", 100, -3.2, 3.2);
   TH1D HPhotonPhiEndcapWithSeed("HPhotonPhiEndcapWithSeed", "Endcap (with seed) photon phi; phi", 100, -3.2, 3.2);
   TH1D HPhotonHoEBarrelWithSeed("HPhotonHoEBarrelWithSeed", "Barrel (with seed) photon H/E; H/E", 100, 0, 1);
   TH1D HPhotonHoEEndcapWithSeed("HPhotonHoEEndcapWithSeed", "Endcap (with seed) photon H/E; H/E", 100, 0, 1);
   TH1D HPhotonSigmaIEtaIEtaBarrelWithSeed("HPhotonSigmaIEtaIEtaBarrelWithSeed",
      "Barrel (with seed) photon SigmaIEtaIEta; SigmaIEtaIEta", 100, 0, 0.06);
   TH1D HPhotonSigmaIEtaIEtaEndcapWithSeed("HPhotonSigmaIEtaIEtaEndcapWithSeed",
      "Endcap (with seed) photon SigmaIEtaIEta; SigmaIEtaIEta", 100, 0, 0.06);
   TH1D HPhotonTrackIsoBarrelWithSeed("HPhotonTrackIsoBarrelWithSeed",
      "Barrel (with seed) photon relative track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonTrackIsoEndcapWithSeed("HPhotonTrackIsoEndcapWithSeed",
      "Endcap (with seed) photon relative track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHollowTrackIsoBarrelWithSeed("HPhotonHollowTrackIsoBarrelWithSeed",
      "Barrel (with seed) photon relative hollow track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHollowTrackIsoEndcapWithSeed("HPhotonHollowTrackIsoEndcapWithSeed",
      "Endcap (with seed) photon relative hollow track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHcalIsoBarrelWithSeed("HPhotonHcalIsoBarrelWithSeed",
      "Barrel (with seed) photon relative Hcal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHcalIsoEndcapWithSeed("HPhotonHcalIsoEndcapWithSeed",
      "Endcap (with seed) photon relative Hcal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonEcalIsoBarrelWithSeed("HPhotonEcalIsoBarrelWithSeed",
      "Barrel (with seed) photon relative Ecal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonEcalIsoEndcapWithSeed("HPhotonEcalIsoEndcapWithSeed",
      "Endcap (with seed) photon relative Ecal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonIsoBarrelWithSeed("HPhotonIsoBarrelWithSeed", "Barrel (with seed) photon iso; pt", 100, -20, 100);
   TH1D HPhotonIsoEndcapWithSeed("HPhotonIsoEndcapWithSeed", "Endcap (with seed) photon iso; pt", 100, -20, 100);
   TH1D HPhotonR9BarrelWithSeed("HPhotonR9BarrelWithSeed", "Barrel (with seed) photon R9", 100, 0, 2.5);
   TH1D HPhotonR9EndcapWithSeed("HPhotonR9EndcapWithSeed", "Endcap (with seed) photon R9", 100, 0, 2.5);

   TH1D HPhotonPTBarrelNoSeed("HPhotonPTBarrelNoSeed", "Barrel (no seed) photon PT;PT (GeV)", 100, 0, 300);
   TH1D HPhotonPTEndcapNoSeed("HPhotonPTEndcapNoSeed", "Endcap (no seed) photon PT;PT (GeV)", 100, 0, 300);
   TH1D HPhotonEtaBarrelNoSeed("HPhotonEtaBarrelNoSeed", "Barrel (no seed) photon eta; eta", 100, -3, 3);
   TH1D HPhotonEtaEndcapNoSeed("HPhotonEtaEndcapNoSeed", "Endcap (no seed) photon eta; eta", 100, -3, 3);
   TH1D HPhotonPhiBarrelNoSeed("HPhotonPhiBarrelNoSeed", "Barrel (no seed) photon phi; phi", 100, -3.2, 3.2);
   TH1D HPhotonPhiEndcapNoSeed("HPhotonPhiEndcapNoSeed", "Endcap (no seed) photon phi; phi", 100, -3.2, 3.2);
   TH1D HPhotonHoEBarrelNoSeed("HPhotonHoEBarrelNoSeed", "Barrel (no seed) photon H/E; H/E", 100, 0, 1);
   TH1D HPhotonHoEEndcapNoSeed("HPhotonHoEEndcapNoSeed", "Endcap (no seed) photon H/E; H/E", 100, 0, 1);
   TH1D HPhotonSigmaIEtaIEtaBarrelNoSeed("HPhotonSigmaIEtaIEtaBarrelNoSeed",
      "Barrel (no seed) photon SigmaIEtaIEta; SigmaIEtaIEta", 100, 0, 0.06);
   TH1D HPhotonSigmaIEtaIEtaEndcapNoSeed("HPhotonSigmaIEtaIEtaEndcapNoSeed",
      "Endcap (no seed) photon SigmaIEtaIEta; SigmaIEtaIEta", 100, 0, 0.06);
   TH1D HPhotonTrackIsoBarrelNoSeed("HPhotonTrackIsoBarrelNoSeed",
      "Barrel (no seed) photon relative track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonTrackIsoEndcapNoSeed("HPhotonTrackIsoEndcapNoSeed",
      "Endcap (no seed) photon relative track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHollowTrackIsoBarrelNoSeed("HPhotonHollowTrackIsoBarrelNoSeed",
      "Barrel (no seed) photon relative hollow track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHollowTrackIsoEndcapNoSeed("HPhotonHollowTrackIsoEndcapNoSeed",
      "Endcap (no seed) photon relative hollow track iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHcalIsoBarrelNoSeed("HPhotonHcalIsoBarrelNoSeed",
      "Barrel (no seed) photon relative Hcal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonHcalIsoEndcapNoSeed("HPhotonHcalIsoEndcapNoSeed",
      "Endcap (no seed) photon relative Hcal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonEcalIsoBarrelNoSeed("HPhotonEcalIsoBarrelNoSeed",
      "Barrel (no seed) photon relative Ecal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonEcalIsoEndcapNoSeed("HPhotonEcalIsoEndcapNoSeed",
      "Endcap (no seed) photon relative Ecal iso; pt/pt", 100, 0, 1);
   TH1D HPhotonIsoBarrelNoSeed("HPhotonIsoBarrelNoSeed", "Barrel (no seed) photon iso; pt", 100, -20, 100);
   TH1D HPhotonIsoEndcapNoSeed("HPhotonIsoEndcapNoSeed", "Endcap (no seed) photon iso; pt", 100, -20, 100);
   TH1D HPhotonR9BarrelNoSeed("HPhotonR9BarrelNoSeed", "Barrel (no seed) photon R9", 100, 0, 2.5);
   TH1D HPhotonR9EndcapNoSeed("HPhotonR9EndcapNoSeed", "Endcap (no seed) photon R9", 100, 0, 2.5);

   TH1D HPhotonPTSelected("HPhotonPTSelected", "Selected photon PT", 100, 0, 300);
   TH1D HPhotonEtaSelected("HPhotonEtaSelected", "Selected photon Eta", 100, -3, 3);
   TH1D HPhotonPhiSelected("HPhotonPhiSelected", "Selected photon Phi", 100, -3.2, 3.2);
   TH1D HPhotonIsolationN1("HPhotonIsolationN1", "Photon isolation (N-1)", 100, -20, 100);
   TH1D HPhotonR9N1("HPhotonR9N1", "Photon R9 (N-1)", 100, 0, 2.5);
   TH1D HPhotonHoEN1("HPhotonHoEN1", "Photon H/E (N-1)", 100, 0, 1);
   TH1D HPhotonSigmaIEtaIEtaN1("HPhotonSigmaIEtaIEtaN1", "Photon #sigma_{i#etai#eta} (N-1)", 100, 0, 0.06);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 1000000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      for(int i = 0; i < PhotonCount; i++)
      {
         double Isolation = TrackIso[i] + HcalIso[i] + EcalIso[i] - Rho * PI * 0.4 * 0.4;
      
         bool Barrel = false;
         bool Endcap = false;
         if(fabs(Eta[i]) < 1.4442)
            Barrel = true;
         if(fabs(Eta[i]) > 1.6)
            Endcap = true;

         if(Barrel == true)   HPhotonPTBarrel.Fill(PT[i]);
         if(Endcap == true)   HPhotonPTEndcap.Fill(PT[i]);

         if(Barrel == true && PT[i] > 30)   HPhotonEtaBarrel.Fill(Eta[i]);
         if(Endcap == true && PT[i] > 30)   HPhotonEtaEndcap.Fill(Eta[i]);
         if(Barrel == true && PT[i] > 30)   HPhotonPhiBarrel.Fill(Phi[i]);
         if(Endcap == true && PT[i] > 30)   HPhotonPhiEndcap.Fill(Phi[i]);
         if(Barrel == true && PT[i] > 30)   HPhotonHoEBarrel.Fill(HoE[i]);
         if(Endcap == true && PT[i] > 30)   HPhotonHoEEndcap.Fill(HoE[i]);
         if(Barrel == true && PT[i] > 30)   HPhotonSigmaIEtaIEtaBarrel.Fill((SigmaIEtaIEta[i]));
         if(Endcap == true && PT[i] > 30)   HPhotonSigmaIEtaIEtaEndcap.Fill((SigmaIEtaIEta[i]));
         if(Barrel == true && PT[i] > 30)   HPhotonTrackIsoBarrel.Fill(TrackIso[i] / PT[i]);
         if(Endcap == true && PT[i] > 30)   HPhotonTrackIsoEndcap.Fill(TrackIso[i] / PT[i]);
         if(Barrel == true && PT[i] > 30)   HPhotonHollowTrackIsoBarrel.Fill(HollowTrackIso[i] / PT[i]);
         if(Endcap == true && PT[i] > 30)   HPhotonHollowTrackIsoEndcap.Fill(HollowTrackIso[i] / PT[i]);
         if(Barrel == true && PT[i] > 30)   HPhotonHcalIsoBarrel.Fill(HcalIso[i] / PT[i]);
         if(Endcap == true && PT[i] > 30)   HPhotonHcalIsoEndcap.Fill(HcalIso[i] / PT[i]);
         if(Barrel == true && PT[i] > 30)   HPhotonEcalIsoBarrel.Fill(EcalIso[i] / PT[i]);
         if(Endcap == true && PT[i] > 30)   HPhotonEcalIsoEndcap.Fill(EcalIso[i] / PT[i]);
         if(Barrel == true && PT[i] > 30)   HPhotonSeedBarrel.Fill(Seed[i]);
         if(Endcap == true && PT[i] > 30)   HPhotonSeedEndcap.Fill(Seed[i]);
         if(Barrel == true && PT[i] > 30)   HPhotonIsoBarrel.Fill(Isolation);
         if(Endcap == true && PT[i] > 30)   HPhotonIsoEndcap.Fill(Isolation);
         if(Barrel == true && PT[i] > 30)   HPhotonR9Barrel.Fill(R9[i]);
         if(Endcap == true && PT[i] > 30)   HPhotonR9Endcap.Fill(R9[i]);

         if(Seed[i] == true)
         {
            if(Barrel == true)   HPhotonPTBarrelWithSeed.Fill(PT[i]);
            if(Endcap == true)   HPhotonPTEndcapWithSeed.Fill(PT[i]);

            if(Barrel == true && PT[i] > 30)   HPhotonEtaBarrelWithSeed.Fill(Eta[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonEtaEndcapWithSeed.Fill(Eta[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonPhiBarrelWithSeed.Fill(Phi[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonPhiEndcapWithSeed.Fill(Phi[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonHoEBarrelWithSeed.Fill(HoE[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonHoEEndcapWithSeed.Fill(HoE[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonSigmaIEtaIEtaBarrelWithSeed.Fill((SigmaIEtaIEta[i]));
            if(Endcap == true && PT[i] > 30)   HPhotonSigmaIEtaIEtaEndcapWithSeed.Fill((SigmaIEtaIEta[i]));
            if(Barrel == true && PT[i] > 30)   HPhotonTrackIsoBarrelWithSeed.Fill(TrackIso[i] / PT[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonTrackIsoEndcapWithSeed.Fill(TrackIso[i] / PT[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonHollowTrackIsoBarrelWithSeed.Fill(HollowTrackIso[i] / PT[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonHollowTrackIsoEndcapWithSeed.Fill(HollowTrackIso[i] / PT[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonHcalIsoBarrelWithSeed.Fill(HcalIso[i] / PT[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonHcalIsoEndcapWithSeed.Fill(HcalIso[i] / PT[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonEcalIsoBarrelWithSeed.Fill(EcalIso[i] / PT[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonEcalIsoEndcapWithSeed.Fill(EcalIso[i] / PT[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonIsoBarrelWithSeed.Fill(Isolation);
            if(Endcap == true && PT[i] > 30)   HPhotonIsoEndcapWithSeed.Fill(Isolation);
            if(Barrel == true && PT[i] > 30)   HPhotonR9BarrelWithSeed.Fill(R9[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonR9EndcapWithSeed.Fill(R9[i]);
         }
         
         if(Seed[i] == false)
         {
            if(Barrel == true)   HPhotonPTBarrelNoSeed.Fill(PT[i]);
            if(Endcap == true)   HPhotonPTEndcapNoSeed.Fill(PT[i]);

            if(Barrel == true && PT[i] > 30)   HPhotonEtaBarrelNoSeed.Fill(Eta[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonEtaEndcapNoSeed.Fill(Eta[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonPhiBarrelNoSeed.Fill(Phi[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonPhiEndcapNoSeed.Fill(Phi[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonHoEBarrelNoSeed.Fill(HoE[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonHoEEndcapNoSeed.Fill(HoE[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonSigmaIEtaIEtaBarrelNoSeed.Fill((SigmaIEtaIEta[i]));
            if(Endcap == true && PT[i] > 30)   HPhotonSigmaIEtaIEtaEndcapNoSeed.Fill((SigmaIEtaIEta[i]));
            if(Barrel == true && PT[i] > 30)   HPhotonTrackIsoBarrelNoSeed.Fill(TrackIso[i] / PT[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonTrackIsoEndcapNoSeed.Fill(TrackIso[i] / PT[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonHollowTrackIsoBarrelNoSeed.Fill(HollowTrackIso[i] / PT[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonHollowTrackIsoEndcapNoSeed.Fill(HollowTrackIso[i] / PT[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonHcalIsoBarrelNoSeed.Fill(HcalIso[i] / PT[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonHcalIsoEndcapNoSeed.Fill(HcalIso[i] / PT[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonEcalIsoBarrelNoSeed.Fill(EcalIso[i] / PT[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonEcalIsoEndcapNoSeed.Fill(EcalIso[i] / PT[i]);
            if(Barrel == true && PT[i] > 30)   HPhotonIsoBarrelNoSeed.Fill(Isolation);
            if(Endcap == true && PT[i] > 30)   HPhotonIsoEndcapNoSeed.Fill(Isolation);
            if(Barrel == true && PT[i] > 30)   HPhotonR9BarrelNoSeed.Fill(R9[i]);
            if(Endcap == true && PT[i] > 30)   HPhotonR9EndcapNoSeed.Fill(R9[i]);
         }

         if(Barrel == true && Seed[i] == false && (SigmaIEtaIEta[i]) < 0.011
            && HoE[i] < 0.05 && Isolation < 6 && R9[i] < 1 && R9[i] > 0.8)
         {
            HPhotonPTSelected.Fill(PT[i]);
            if(PT[i] > 30)
            {
               HPhotonEtaSelected.Fill(Eta[i]);
               HPhotonPhiSelected.Fill(Phi[i]);
            }
         }
         if(Barrel == true && Seed[i] == false && (SigmaIEtaIEta[i]) < 0.011 && HoE[i] < 0.05 && R9[i] < 1 && R9[i] > 0.8)
            HPhotonIsolationN1.Fill(Isolation);
         if(Barrel == true && Seed[i] == false && (SigmaIEtaIEta[i]) < 0.011 && HoE[i] < 0.05 && Isolation < 6)
            HPhotonR9N1.Fill(R9[i]);
         if(Barrel == true && Seed[i] == false && (SigmaIEtaIEta[i]) < 0.011 && Isolation < 6 && R9[i] < 1 && R9[i] > 0.8)
            HPhotonHoEN1.Fill(HoE[i]);
         if(Barrel == true && Seed[i] == false && HoE[i] < 0.05 && Isolation < 6 && R9[i] < 1 && R9[i] > 0.8)
            HPhotonSigmaIEtaIEtaN1.Fill((SigmaIEtaIEta[i]));
      }
   }

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   PsFile.AddTextPage("Basic distributions: PT > 30 for all plots except PT plot");
   OverlayHistograms(PsFile, HPhotonPTBarrel, HPhotonPTEndcap, true, 0);
   OverlayHistograms(PsFile, HPhotonEtaBarrel, HPhotonEtaEndcap, true, 0);
   OverlayHistograms(PsFile, HPhotonPhiBarrel, HPhotonPhiEndcap, false, 0);
   OverlayHistograms(PsFile, HPhotonHoEBarrel, HPhotonHoEEndcap, true, 0);
   OverlayHistograms(PsFile, HPhotonSigmaIEtaIEtaBarrel, HPhotonSigmaIEtaIEtaEndcap, true, 0);
   OverlayHistograms(PsFile, HPhotonTrackIsoBarrel, HPhotonTrackIsoEndcap, true, 0);
   OverlayHistograms(PsFile, HPhotonHollowTrackIsoBarrel, HPhotonHollowTrackIsoEndcap, true, 0);
   OverlayHistograms(PsFile, HPhotonHcalIsoBarrel, HPhotonHcalIsoEndcap, true, 0);
   OverlayHistograms(PsFile, HPhotonEcalIsoBarrel, HPhotonEcalIsoEndcap, true, 0);
   OverlayHistograms(PsFile, HPhotonSeedBarrel, HPhotonSeedEndcap, false, 0);
   OverlayHistograms(PsFile, HPhotonIsoBarrel, HPhotonIsoEndcap, true, 0);
   OverlayHistograms(PsFile, HPhotonR9Barrel, HPhotonR9Endcap, true, 0);

   PsFile.AddTextPage("Pixel seed is important: let's compare with/without seed");
   OverlayHistograms(PsFile, HPhotonPTBarrelWithSeed, HPhotonPTBarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonEtaBarrelWithSeed, HPhotonEtaBarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonPhiBarrelWithSeed, HPhotonPhiBarrelNoSeed, false, 1);
   OverlayHistograms(PsFile, HPhotonHoEBarrelWithSeed, HPhotonHoEBarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonSigmaIEtaIEtaBarrelWithSeed, HPhotonSigmaIEtaIEtaBarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonTrackIsoBarrelWithSeed, HPhotonTrackIsoBarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonHollowTrackIsoBarrelWithSeed, HPhotonHollowTrackIsoBarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonHcalIsoBarrelWithSeed, HPhotonHcalIsoBarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonEcalIsoBarrelWithSeed, HPhotonEcalIsoBarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonIsoBarrelWithSeed, HPhotonIsoBarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonR9BarrelWithSeed, HPhotonR9BarrelNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonPTEndcapWithSeed, HPhotonPTEndcapNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonEtaEndcapWithSeed, HPhotonEtaEndcapNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonPhiEndcapWithSeed, HPhotonPhiEndcapNoSeed, false, 1);
   OverlayHistograms(PsFile, HPhotonHoEEndcapWithSeed, HPhotonHoEEndcapNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonSigmaIEtaIEtaEndcapWithSeed, HPhotonSigmaIEtaIEtaEndcapNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonTrackIsoEndcapWithSeed, HPhotonTrackIsoEndcapNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonHollowTrackIsoEndcapWithSeed, HPhotonHollowTrackIsoEndcapNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonHcalIsoEndcapWithSeed, HPhotonHcalIsoEndcapNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonEcalIsoEndcapWithSeed, HPhotonEcalIsoEndcapNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonIsoEndcapWithSeed, HPhotonIsoEndcapNoSeed, true, 1);
   OverlayHistograms(PsFile, HPhotonR9EndcapWithSeed, HPhotonR9EndcapNoSeed, true, 1);

   vector<string> Selections;
   Selections.push_back("Selections in AN 2011/515 (SUSY diphoton+MET)");
   Selections.push_back("Version 2012 Feb. 8");
   Selections.push_back("");
   Selections.push_back("PT > 40 GeV for leading, 25 GeV for sub-leading");
   Selections.push_back("|eta| < 1.4442 => barrel only");
   Selections.push_back("");
   Selections.push_back("Comined isolation < 6 GeV");
   Selections.push_back("H/E < 0.05");
   Selections.push_back("Sigma ieta ieta < 0.011");
   Selections.push_back("R9 < 1.0 (?)");
   Selections.push_back("");
   Selections.push_back("Let's look at some N-1 plots as well as full selection plots");
   PsFile.AddTextPage(Selections);
   PsFile.AddPlot(HPhotonPTSelected, "", true);
   PsFile.AddPlot(HPhotonEtaSelected, "", false);
   PsFile.AddPlot(HPhotonPhiSelected, "", false);
   PlotWithCut(PsFile, HPhotonIsolationN1, 6);
   PlotWithCut(PsFile, HPhotonR9N1, 0.8, 1);
   PlotWithCut(PsFile, HPhotonHoEN1, 0.05);
   PlotWithCut(PsFile, HPhotonSigmaIEtaIEtaN1, 0.011);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void OverlayHistograms(PsFileHelper &PsFile, TH1D H1, TH1D H2, bool LogY, int Mode)
{
   // Mode = 0: barrel vs. endcap
   // Mode = 1: with seed vs. without seed

   if(Mode == 0)
   {
      H1.SetTitle(TString(H1.GetTitle()).ReplaceAll("Barrel", ""));
      H1.SetTitle(TString(H1.GetTitle()).ReplaceAll("Endcap", ""));
      H2.SetTitle(TString(H2.GetTitle()).ReplaceAll("Barrel", ""));
      H2.SetTitle(TString(H2.GetTitle()).ReplaceAll("Endcap", ""));
   }
   if(Mode == 1)
   {
      H1.SetTitle(TString(H1.GetTitle()).ReplaceAll("(with seed)", ""));
      H1.SetTitle(TString(H1.GetTitle()).ReplaceAll("(no seed)", ""));
      H2.SetTitle(TString(H2.GetTitle()).ReplaceAll("(with seed)", ""));
      H2.SetTitle(TString(H2.GetTitle()).ReplaceAll("(no seed)", ""));
   }

   TCanvas Canvas;

   H1.SetLineWidth(2);
   H2.SetLineWidth(2);

   H1.SetLineColor(kBlack);
   H2.SetLineColor(kRed);

   if(LogY == true)
   {
      H1.SetMinimum(0.5);
      H2.SetMinimum(0.5);
   }
   else
   {
      H1.SetMinimum(0);
      H2.SetMinimum(0);
   }

   if(H1.GetMaximum() > H2.GetMaximum())
   {
      H1.Draw();
      H2.Draw("same");
   }
   else
   {
      H2.Draw();
      H1.Draw("same");
   }

   if(LogY == true)
      Canvas.SetLogy();

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);

   if(Mode == 0)
   {
      Legend.AddEntry(&H1, "Barrel", "l");
      Legend.AddEntry(&H2, "Endcap", "l");
      Legend.Draw();
   }
   else if(Mode == 1)
   {
      Legend.AddEntry(&H1, "With seed", "l");
      Legend.AddEntry(&H2, "No seed", "l");
      Legend.Draw();
   }

   PsFile.AddCanvas(Canvas);
}

void PlotWithCut(PsFileHelper &PsFile, TH1D &H, double CutPosition, double CutPosition2)
{
   TCanvas Canvas;

   H.SetLineColor(kBlack);
   H.SetLineWidth(2);
   H.Draw();

   TGraph G;
   G.SetPoint(0, CutPosition, 0);
   G.SetPoint(1, CutPosition, 9999999);
   G.SetPoint(2, CutPosition2, 9999999);
   G.SetPoint(3, CutPosition2, 0);
   G.SetLineWidth(2);
   G.SetLineStyle(10);
   G.SetLineColor(kRed);
   G.Draw("l");

   Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
}



