#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TChain.h"

#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[])
{
   string InputFileName = "Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root";
   string OutputBase = "WJet";
   double CrossSection = 31314;
   const double Luminosity = 1000;   // 1/fb

   if(argc < 4)
   {
      cout << "Usage: " << argv[0] << " InputFile CrossSection OutputBase" << endl;
      return -1;
   }

   InputFileName = argv[1];
   OutputBase = argv[3];
   stringstream CrossSectionConversion(argv[2]);
   CrossSectionConversion >> CrossSection;

   TChain Tree("LQ3Tree");
   Tree.AddFile(InputFileName.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("Samples/BookKeeping/Example.PU.root");

   Tree.SetBranchStatus("*", false);
   Tree.SetBranchStatus("PileUp", true);
   Tree.SetBranchStatus("AllElectron*", true);
   Tree.SetBranchStatus("CaloJet*", true);
   Tree.SetBranchStatus("PFMET", true);
   Tree.SetBranchStatus("GoodMuonCount", true);

   double AllEvents = 0;
   TFile InputF(InputFileName.c_str());
   TH1D *H = (TH1D *)InputF.Get("HProcessedEventsPU");
   for(int i = 1; i <= H->GetNbinsX(); i++)
      AllEvents = AllEvents + M.GetWeight(i - 1) * H->GetBinContent(i);
   InputF.Close();

   TFile OutputF((OutputBase + ".root").c_str(), "recreate");

   TH1D HRawNPU("HRawNPU", "(raw) pileup distribution", 30, -0.5, 29.5);
   TH1D HNPU("HNPU", "Reweighted pileup distribution", 30, -0.5, 29.5);

   TH1D HAllElectronCount("HAllElectronCount", "Number of electron candidates", 10, -0.5, 9.5);
   TH1D HAllElectronPT("HAllElectronPT", "Electron candidate PT", 100, 0, 100);
   TH1D HAllElectronEta("HAllElectronEta", "Electron candidate Eta", 100, -3, 3);
   TH1D HAllElectronPhi("HAllElectronPhi", "Electron candidate Phi", 100, -3.5, 3.5);
   TH1D HAllElectronSigmaIEtaIEta("HAllElectronSigmaIEtaIEta", "Electron candidate sigma ieta ieta", 100, 0, 0.1);
   TH1D HAllElectronSigmaIEtaIEtaBarrel("HAllElectronSigmaIEtaIEtaBarrel",
      "(Barrel) electron candidate sigma ieta ieta", 100, 0, 0.05);
   TH1D HAllElectronSigmaIEtaIEtaEndcap("HAllElectronSigmaIEtaIEtaEndcap",
      "(Endcap) electron candidate sigma ieta ieta", 100, 0, 0.1);
   TH1D HAllElectronIsolation("HAllElectronIsolation", "Electron candidate isolation", 100, 0, 100);
   TH1D HAllElectronIsolationBarrel("HAllElectronIsolationBarrel",
      "(Barrel) Electron candidate isolation", 100, 0, 100);
   TH1D HAllElectronIsolationEndcap("HAllElectronIsolationEndcap",
      "(Endcap) Electron candidate isolation", 100, 0, 100);
   TH1D HAllElectronRelativeIsolation("HAllElectronRelativeIsolation",
      "Electron candidate relative isolation", 100, 0, 3);
   TH1D HAllElectronRelativeIsolationBarrel("HAllElectronRelativeIsolationBarrel",
      "(Barrel) Electron candidate relative isolation", 100, 0, 3);
   TH1D HAllElectronRelativeIsolationEndcap("HAllElectronRelativeIsolationEndcap",
      "(Endcap) Electron candidate relative isolation", 100, 0, 3);

   TH2D HAllElectronRelativeIsolationVsSigmaIEtaIEtaBarrel("HAllEelctronRelativeIsolationVsSigmaIEtaIEtaBarrel",
      "Electron candidate (barrel), relative isolation vs. sigma ieta ieta;Relative isolation;SigmaIEtaIEta",
      100, 0, 3, 100, 0, 0.05);
   TH2D HAllElectronRelativeIsolationVsSigmaIEtaIEtaEndcap("HAllEelctronRelativeIsolationVsSigmaIEtaIEtaEndcap",
      "Electron candidate (endcap), relative isolation vs. sigma ieta ieta;Relative isolation;SigmaIEtaIEta",
      100, 0, 3, 100, 0, 0.1);

   TH1D HAntiSigmaIEtaIEtaCount("HAntiSigmaIEtaIEtaCount",
      "Number of anti-sigma-ieta-ieta candidate per event", 10, -0.5, 9.5);
   TH1D HAntiSigmaIEtaIEtaBarrelCount("HAntiSigmaIEtaIEtaBarrelCount",
      "Number of anti-sigma-ieta-ieta candidate (barrel) per event", 10, -0.5, 9.5);
   TH1D HAntiSigmaIEtaIEtaEndcapCount("HAntiSigmaIEtaIEtaEndcapCount",
      "Number of anti-sigma-ieta-ieta candidate (endcap) per event", 10, -0.5, 9.5);
   
   TH1D HAntiSigmaIEtaIEtaCountLL("HAntiSigmaIEtaIEtaCountLL",
      "Number of anti-sigma-ieta-ieta candidate per event (double-loose-80)", 10, -0.5, 9.5);
   TH1D HAntiSigmaIEtaIEtaBarrelCountLL("HAntiSigmaIEtaIEtaBarrelCountLL",
      "Number of anti-sigma-ieta-ieta candidate (barrel) per event (double-loose-80)", 10, -0.5, 9.5);
   TH1D HAntiSigmaIEtaIEtaEndcapCountLL("HAntiSigmaIEtaIEtaEndcapCountLL",
      "Number of anti-sigma-ieta-ieta candidate (endcap) per event (double-loose-80)", 10, -0.5, 9.5);

   TH1D HAntiSigmaIEtaIEtaLLMRNew("HAntiSigmaIEtaIEtaLLMRNew",
      "MR (new), anti-sigma-ieta-ieta, double loose tag", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLLMRNew_R2New005("HAntiSigmaIEtaIEtaLLMRNew_R2New005",
      "MR (new), anti-sigma-ieta-ieta, double loose tag, R^{2} (new) > 0.05", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLLMRNew_R2New010("HAntiSigmaIEtaIEtaLLMRNew_R2New010",
      "MR (new), anti-sigma-ieta-ieta, double loose tag, R^{2} (new) > 0.10", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLLMRNew_R2New015("HAntiSigmaIEtaIEtaLLMRNew_R2New015",
      "MR (new), anti-sigma-ieta-ieta, double loose tag, R^{2} (new) > 0.15", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLLMRNew_R2New020("HAntiSigmaIEtaIEtaLLMRNew_R2New020",
      "MR (new), anti-sigma-ieta-ieta, double loose tag, R^{2} (new) > 0.20", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLLMRNew_R2New025("HAntiSigmaIEtaIEtaLLMRNew_R2New025",
      "MR (new), anti-sigma-ieta-ieta, double loose tag, R^{2} (new) > 0.25", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLLR2New("HAntiSigmaIEtaIEtaLLR2New",
      "R^{2} (new), anti-sigma-ieta-ieta, double loose tag", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLLR2New_MRNew300("HAntiSigmaIEtaIEtaLLR2New_MRNew300",
      "R^{2} (new), anti-sigma-ieta-ieta, double loose tag, MR (new) > 300", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLLR2New_MRNew400("HAntiSigmaIEtaIEtaLLR2New_MRNew400",
      "R^{2} (new), anti-sigma-ieta-ieta, double loose tag, MR (new) > 400", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLLR2New_MRNew500("HAntiSigmaIEtaIEtaLLR2New_MRNew500",
      "R^{2} (new), anti-sigma-ieta-ieta, double loose tag, MR (new) > 500", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLLR2New_MRNew600("HAntiSigmaIEtaIEtaLLR2New_MRNew600",
      "R^{2} (new), anti-sigma-ieta-ieta, double loose tag, MR (new) > 600", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLLR2New_MRNew700("HAntiSigmaIEtaIEtaLLR2New_MRNew700",
      "R^{2} (new), anti-sigma-ieta-ieta, double loose tag, MR (new) > 700", 40, 0, 1.2);
   
   TH1D HAntiSigmaIEtaIEtaLMRNew("HAntiSigmaIEtaIEtaLMRNew",
      "MR (new), anti-sigma-ieta-ieta, single loose tag", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLMRNew_R2New005("HAntiSigmaIEtaIEtaLMRNew_R2New005",
      "MR (new), anti-sigma-ieta-ieta, single loose tag, R^{2} (new) > 0.05", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLMRNew_R2New010("HAntiSigmaIEtaIEtaLMRNew_R2New010",
      "MR (new), anti-sigma-ieta-ieta, single loose tag, R^{2} (new) > 0.10", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLMRNew_R2New015("HAntiSigmaIEtaIEtaLMRNew_R2New015",
      "MR (new), anti-sigma-ieta-ieta, single loose tag, R^{2} (new) > 0.15", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLMRNew_R2New020("HAntiSigmaIEtaIEtaLMRNew_R2New020",
      "MR (new), anti-sigma-ieta-ieta, single loose tag, R^{2} (new) > 0.20", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLMRNew_R2New025("HAntiSigmaIEtaIEtaLMRNew_R2New025",
      "MR (new), anti-sigma-ieta-ieta, single loose tag, R^{2} (new) > 0.25", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaLR2New("HAntiSigmaIEtaIEtaLR2New",
      "R^{2} (new), anti-sigma-ieta-ieta, single loose tag", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLR2New_MRNew300("HAntiSigmaIEtaIEtaLR2New_MRNew300",
      "R^{2} (new), anti-sigma-ieta-ieta, single loose tag, MR (new) > 300", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLR2New_MRNew400("HAntiSigmaIEtaIEtaLR2New_MRNew400",
      "R^{2} (new), anti-sigma-ieta-ieta, single loose tag, MR (new) > 400", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLR2New_MRNew500("HAntiSigmaIEtaIEtaLR2New_MRNew500",
      "R^{2} (new), anti-sigma-ieta-ieta, single loose tag, MR (new) > 500", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLR2New_MRNew600("HAntiSigmaIEtaIEtaLR2New_MRNew600",
      "R^{2} (new), anti-sigma-ieta-ieta, single loose tag, MR (new) > 600", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaLR2New_MRNew700("HAntiSigmaIEtaIEtaLR2New_MRNew700",
      "R^{2} (new), anti-sigma-ieta-ieta, single loose tag, MR (new) > 700", 40, 0, 1.2);

   TH1D HAntiSigmaIEtaIEtaMRNew("HAntiSigmaIEtaIEtaMRNew",
      "MR (new), anti-sigma-ieta-ieta", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaMRNew_R2New005("HAntiSigmaIEtaIEtaMRNew_R2New005",
      "MR (new), anti-sigma-ieta-ieta, R^{2} (new) > 0.05", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaMRNew_R2New010("HAntiSigmaIEtaIEtaMRNew_R2New010",
      "MR (new), anti-sigma-ieta-ieta, R^{2} (new) > 0.10", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaMRNew_R2New015("HAntiSigmaIEtaIEtaMRNew_R2New015",
      "MR (new), anti-sigma-ieta-ieta, R^{2} (new) > 0.15", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaMRNew_R2New020("HAntiSigmaIEtaIEtaMRNew_R2New020",
      "MR (new), anti-sigma-ieta-ieta, R^{2} (new) > 0.20", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaMRNew_R2New025("HAntiSigmaIEtaIEtaMRNew_R2New025",
      "MR (new), anti-sigma-ieta-ieta, R^{2} (new) > 0.25", 40, 0, 1000);
   TH1D HAntiSigmaIEtaIEtaR2New("HAntiSigmaIEtaIEtaR2New",
      "R^{2} (new), anti-sigma-ieta-ieta", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaR2New_MRNew300("HAntiSigmaIEtaIEtaR2New_MRNew300",
      "R^{2} (new), anti-sigma-ieta-ieta, MR (new) > 300", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaR2New_MRNew400("HAntiSigmaIEtaIEtaR2New_MRNew400",
      "R^{2} (new), anti-sigma-ieta-ieta, MR (new) > 400", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaR2New_MRNew500("HAntiSigmaIEtaIEtaR2New_MRNew500",
      "R^{2} (new), anti-sigma-ieta-ieta, MR (new) > 500", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaR2New_MRNew600("HAntiSigmaIEtaIEtaR2New_MRNew600",
      "R^{2} (new), anti-sigma-ieta-ieta, MR (new) > 600", 40, 0, 1.2);
   TH1D HAntiSigmaIEtaIEtaR2New_MRNew700("HAntiSigmaIEtaIEtaR2New_MRNew700",
      "R^{2} (new), anti-sigma-ieta-ieta, MR (new) > 700", 40, 0, 1.2);
   
   TH1D HAntiElectronMRNew("HAntiElectronMRNew",
      "MR (new), anti-electron", 40, 0, 1000);
   TH1D HAntiElectronMRNew_R2New005("HAntiElectronMRNew_R2New005",
      "MR (new), anti-electron, R^{2} (new) > 0.05", 40, 0, 1000);
   TH1D HAntiElectronMRNew_R2New010("HAntiElectronMRNew_R2New010",
      "MR (new), anti-electron, R^{2} (new) > 0.10", 40, 0, 1000);
   TH1D HAntiElectronMRNew_R2New015("HAntiElectronMRNew_R2New015",
      "MR (new), anti-electron, R^{2} (new) > 0.15", 40, 0, 1000);
   TH1D HAntiElectronMRNew_R2New020("HAntiElectronMRNew_R2New020",
      "MR (new), anti-electron, R^{2} (new) > 0.20", 40, 0, 1000);
   TH1D HAntiElectronMRNew_R2New025("HAntiElectronMRNew_R2New025",
      "MR (new), anti-electron, R^{2} (new) > 0.25", 40, 0, 1000);
   TH1D HAntiElectronR2New("HAntiElectronR2New",
      "R^{2} (new), anti-electron", 40, 0, 1.2);
   TH1D HAntiElectronR2New_MRNew300("HAntiElectronR2New_MRNew300",
      "R^{2} (new), anti-electron, MR (new) > 300", 40, 0, 1.2);
   TH1D HAntiElectronR2New_MRNew400("HAntiElectronR2New_MRNew400",
      "R^{2} (new), anti-electron, MR (new) > 400", 40, 0, 1.2);
   TH1D HAntiElectronR2New_MRNew500("HAntiElectronR2New_MRNew500",
      "R^{2} (new), anti-electron, MR (new) > 500", 40, 0, 1.2);
   TH1D HAntiElectronR2New_MRNew600("HAntiElectronR2New_MRNew600",
      "R^{2} (new), anti-electron, MR (new) > 600", 40, 0, 1.2);
   TH1D HAntiElectronR2New_MRNew700("HAntiElectronR2New_MRNew700",
      "R^{2} (new), anti-electron, MR (new) > 700", 40, 0, 1.2);

   TH1D HAntiIsolationMRNew("HAntiIsolationMRNew",
      "MR (new), anti-isolation", 40, 0, 1000);
   TH1D HAntiIsolationMRNew_R2New005("HAntiIsolationMRNew_R2New005",
      "MR (new), anti-isolation, R^{2} (new) > 0.05", 40, 0, 1000);
   TH1D HAntiIsolationMRNew_R2New010("HAntiIsolationMRNew_R2New010",
      "MR (new), anti-isolation, R^{2} (new) > 0.10", 40, 0, 1000);
   TH1D HAntiIsolationMRNew_R2New015("HAntiIsolationMRNew_R2New015",
      "MR (new), anti-isolation, R^{2} (new) > 0.15", 40, 0, 1000);
   TH1D HAntiIsolationMRNew_R2New020("HAntiIsolationMRNew_R2New020",
      "MR (new), anti-isolation, R^{2} (new) > 0.20", 40, 0, 1000);
   TH1D HAntiIsolationMRNew_R2New025("HAntiIsolationMRNew_R2New025",
      "MR (new), anti-isolation, R^{2} (new) > 0.25", 40, 0, 1000);
   TH1D HAntiIsolationR2New("HAntiIsolationR2New",
      "R^{2} (new), anti-isolation", 40, 0, 1.2);
   TH1D HAntiIsolationR2New_MRNew300("HAntiIsolationR2New_MRNew300",
      "R^{2} (new), anti-isolation, MR (new) > 300", 40, 0, 1.2);
   TH1D HAntiIsolationR2New_MRNew400("HAntiIsolationR2New_MRNew400",
      "R^{2} (new), anti-isolation, MR (new) > 400", 40, 0, 1.2);
   TH1D HAntiIsolationR2New_MRNew500("HAntiIsolationR2New_MRNew500",
      "R^{2} (new), anti-isolation, MR (new) > 500", 40, 0, 1.2);
   TH1D HAntiIsolationR2New_MRNew600("HAntiIsolationR2New_MRNew600",
      "R^{2} (new), anti-isolation, MR (new) > 600", 40, 0, 1.2);
   TH1D HAntiIsolationR2New_MRNew700("HAntiIsolationR2New_MRNew700",
      "R^{2} (new), anti-isolation, MR (new) > 700", 40, 0, 1.2);
   
   TH1D HAntiNothingMRNew("HAntiNothingMRNew",
      "MR (new), anti-nothing", 40, 0, 1000);
   TH1D HAntiNothingMRNew_R2New005("HAntiNothingMRNew_R2New005",
      "MR (new), anti-nothing, R^{2} (new) > 0.05", 40, 0, 1000);
   TH1D HAntiNothingMRNew_R2New010("HAntiNothingMRNew_R2New010",
      "MR (new), anti-nothing, R^{2} (new) > 0.10", 40, 0, 1000);
   TH1D HAntiNothingMRNew_R2New015("HAntiNothingMRNew_R2New015",
      "MR (new), anti-nothing, R^{2} (new) > 0.15", 40, 0, 1000);
   TH1D HAntiNothingMRNew_R2New020("HAntiNothingMRNew_R2New020",
      "MR (new), anti-nothing, R^{2} (new) > 0.20", 40, 0, 1000);
   TH1D HAntiNothingMRNew_R2New025("HAntiNothingMRNew_R2New025",
      "MR (new), anti-nothing, R^{2} (new) > 0.25", 40, 0, 1000);
   TH1D HAntiNothingR2New("HAntiNothingR2New",
      "R^{2} (new), anti-nothing", 40, 0, 1.2);
   TH1D HAntiNothingR2New_MRNew300("HAntiNothingR2New_MRNew300",
      "R^{2} (new), anti-nothing, MR (new) > 300", 40, 0, 1.2);
   TH1D HAntiNothingR2New_MRNew400("HAntiNothingR2New_MRNew400",
      "R^{2} (new), anti-nothing, MR (new) > 400", 40, 0, 1.2);
   TH1D HAntiNothingR2New_MRNew500("HAntiNothingR2New_MRNew500",
      "R^{2} (new), anti-nothing, MR (new) > 500", 40, 0, 1.2);
   TH1D HAntiNothingR2New_MRNew600("HAntiNothingR2New_MRNew600",
      "R^{2} (new), anti-nothing, MR (new) > 600", 40, 0, 1.2);
   TH1D HAntiNothingR2New_MRNew700("HAntiNothingR2New_MRNew700",
      "R^{2} (new), anti-nothing, MR (new) > 700", 40, 0, 1.2);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      double WPU = M.GetCurrentWeight() * CrossSection * Luminosity / AllEvents;

      HRawNPU.Fill(M.PileUp);
      HNPU.Fill(M.PileUp, WPU);

      if(M.GoodMuonCount != 0)
         continue;

      int CaloJet60Count = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(fabs(M.CaloJetEta[i]) < 3 && M.CaloJetPT[i] > 60)
            CaloJet60Count = CaloJet60Count + 1;
      if(CaloJet60Count < 2)
         continue;

      HAllElectronCount.Fill(M.AllElectronCount, WPU);
      for(int i = 0; i < M.AllElectronCount; i++)
      {
         HAllElectronPT.Fill(M.AllElectronPT[i], WPU);
         HAllElectronEta.Fill(M.AllElectronEta[i], WPU);
         HAllElectronPhi.Fill(M.AllElectronPhi[i], WPU);
         HAllElectronSigmaIEtaIEta.Fill(sqrt(M.AllElectronSigmaIEtaIEta[i]), WPU);
         if(fabs(M.AllElectronEta[i]) < 1.56)   // roughly
            HAllElectronSigmaIEtaIEtaBarrel.Fill(sqrt(M.AllElectronSigmaIEtaIEta[i]), WPU);
         else
            HAllElectronSigmaIEtaIEtaEndcap.Fill(sqrt(M.AllElectronSigmaIEtaIEta[i]), WPU);
         
         HAllElectronIsolation.Fill(M.AllElectronIsolation[i], WPU);
         if(fabs(M.AllElectronEta[i]) < 1.56)   // roughly
            HAllElectronIsolationBarrel.Fill(M.AllElectronIsolation[i], WPU);
         else
            HAllElectronIsolationEndcap.Fill(M.AllElectronIsolation[i], WPU);
         
         HAllElectronRelativeIsolation.Fill(M.AllElectronIsolation[i] / M.AllElectronPT[i], WPU);
         if(fabs(M.AllElectronEta[i]) < 1.56)
            HAllElectronRelativeIsolationBarrel.Fill(M.AllElectronIsolation[i] / M.AllElectronPT[i], WPU);
         else
            HAllElectronRelativeIsolationEndcap.Fill(M.AllElectronIsolation[i] / M.AllElectronPT[i], WPU);

         if(fabs(M.AllElectronEta[i]) < 1.56)
            HAllElectronRelativeIsolationVsSigmaIEtaIEtaBarrel.Fill(M.AllElectronIsolation[i] / M.AllElectronPT[i],
               sqrt(M.AllElectronSigmaIEtaIEta[i]), WPU);
         else
            HAllElectronRelativeIsolationVsSigmaIEtaIEtaEndcap.Fill(M.AllElectronIsolation[i] / M.AllElectronPT[i],
               sqrt(M.AllElectronSigmaIEtaIEta[i]), WPU);
      }

      int Loose80Count = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] > 80 && M.CaloJetTCHETag[i] > 1.7)
            Loose80Count = Loose80Count + 1;
      }

      int AntiSigmaIEtaIEtaBarrelCount = 0;
      int AntiSigmaIEtaIEtaEndcapCount = 0;
      for(int i = 0; i < M.AllElectronCount; i++)
      {
         if(fabs(M.AllElectronEta[i]) < 1.56 && sqrt(M.AllElectronSigmaIEtaIEta[i]) > 0.012)
            AntiSigmaIEtaIEtaBarrelCount = AntiSigmaIEtaIEtaBarrelCount + 1;
         if(fabs(M.AllElectronEta[i]) > 1.56 && sqrt(M.AllElectronSigmaIEtaIEta[i]) > 0.035)
            AntiSigmaIEtaIEtaEndcapCount = AntiSigmaIEtaIEtaEndcapCount + 1;
      }

      HAntiSigmaIEtaIEtaCount.Fill(AntiSigmaIEtaIEtaBarrelCount + AntiSigmaIEtaIEtaEndcapCount, WPU);
      HAntiSigmaIEtaIEtaBarrelCount.Fill(AntiSigmaIEtaIEtaBarrelCount, WPU);
      HAntiSigmaIEtaIEtaEndcapCount.Fill(AntiSigmaIEtaIEtaEndcapCount, WPU);
      
      if(Loose80Count >= 2)
      {
         HAntiSigmaIEtaIEtaCountLL.Fill(AntiSigmaIEtaIEtaBarrelCount + AntiSigmaIEtaIEtaEndcapCount, WPU);
         HAntiSigmaIEtaIEtaBarrelCountLL.Fill(AntiSigmaIEtaIEtaBarrelCount, WPU);
         HAntiSigmaIEtaIEtaEndcapCountLL.Fill(AntiSigmaIEtaIEtaEndcapCount, WPU);
      }

      int AntiElectronCount = 0;
      for(int i = 0; i < M.AllElectronCount; i++)
      {
         if(M.AllElectronIsolation[i] < 20)
            continue;

         if(fabs(M.AllElectronEta[i]) < 1.56 && sqrt(M.AllElectronSigmaIEtaIEta[i]) > 0.012)
            AntiElectronCount = AntiElectronCount + 1;
         if(fabs(M.AllElectronEta[i]) > 1.56 && sqrt(M.AllElectronSigmaIEtaIEta[i]) > 0.035)
            AntiElectronCount = AntiElectronCount + 1;
      }

      int AntiIsolationCount = 0;
      for(int i = 0; i < M.AllElectronCount; i++)
      {
         if(M.AllElectronIsolation[i] < 20)
            continue;
         AntiIsolationCount = AntiIsolationCount + 1;
      }

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 40)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewVector;
         NewVector.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);
         GoodJets.push_back(NewVector);
      }
      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);

      if(GoodJets.size() >= 2)
      {
         double MRNew = Get2011MR(Groups[0], Groups[1]);
         double RNew = Get2011R(Groups[0], Groups[1], PFMET);
         double R2New = RNew * RNew;

         if(Loose80Count >= 2 && AntiSigmaIEtaIEtaBarrelCount + AntiSigmaIEtaIEtaEndcapCount > 0)
         {
            HAntiSigmaIEtaIEtaLLMRNew.Fill(MRNew, WPU);
            if(R2New > 0.05)   HAntiSigmaIEtaIEtaLLMRNew_R2New005.Fill(MRNew, WPU);
            if(R2New > 0.10)   HAntiSigmaIEtaIEtaLLMRNew_R2New010.Fill(MRNew, WPU);
            if(R2New > 0.15)   HAntiSigmaIEtaIEtaLLMRNew_R2New015.Fill(MRNew, WPU);
            if(R2New > 0.20)   HAntiSigmaIEtaIEtaLLMRNew_R2New020.Fill(MRNew, WPU);
            if(R2New > 0.25)   HAntiSigmaIEtaIEtaLLMRNew_R2New025.Fill(MRNew, WPU);

            HAntiSigmaIEtaIEtaLLR2New.Fill(R2New, WPU);
            if(MRNew > 300)   HAntiSigmaIEtaIEtaLLR2New_MRNew300.Fill(R2New, WPU);
            if(MRNew > 400)   HAntiSigmaIEtaIEtaLLR2New_MRNew400.Fill(R2New, WPU);
            if(MRNew > 500)   HAntiSigmaIEtaIEtaLLR2New_MRNew500.Fill(R2New, WPU);
            if(MRNew > 600)   HAntiSigmaIEtaIEtaLLR2New_MRNew600.Fill(R2New, WPU);
            if(MRNew > 700)   HAntiSigmaIEtaIEtaLLR2New_MRNew700.Fill(R2New, WPU);
         }
         if(Loose80Count >= 1 && AntiSigmaIEtaIEtaBarrelCount + AntiSigmaIEtaIEtaEndcapCount > 0)
         {
            HAntiSigmaIEtaIEtaLMRNew.Fill(MRNew, WPU);
            if(R2New > 0.05)   HAntiSigmaIEtaIEtaLMRNew_R2New005.Fill(MRNew, WPU);
            if(R2New > 0.10)   HAntiSigmaIEtaIEtaLMRNew_R2New010.Fill(MRNew, WPU);
            if(R2New > 0.15)   HAntiSigmaIEtaIEtaLMRNew_R2New015.Fill(MRNew, WPU);
            if(R2New > 0.20)   HAntiSigmaIEtaIEtaLMRNew_R2New020.Fill(MRNew, WPU);
            if(R2New > 0.25)   HAntiSigmaIEtaIEtaLMRNew_R2New025.Fill(MRNew, WPU);

            HAntiSigmaIEtaIEtaLR2New.Fill(R2New, WPU);
            if(MRNew > 300)   HAntiSigmaIEtaIEtaLR2New_MRNew300.Fill(R2New, WPU);
            if(MRNew > 400)   HAntiSigmaIEtaIEtaLR2New_MRNew400.Fill(R2New, WPU);
            if(MRNew > 500)   HAntiSigmaIEtaIEtaLR2New_MRNew500.Fill(R2New, WPU);
            if(MRNew > 600)   HAntiSigmaIEtaIEtaLR2New_MRNew600.Fill(R2New, WPU);
            if(MRNew > 700)   HAntiSigmaIEtaIEtaLR2New_MRNew700.Fill(R2New, WPU);
         }
         if(Loose80Count >= 0 && AntiSigmaIEtaIEtaBarrelCount + AntiSigmaIEtaIEtaEndcapCount > 0)
         {
            HAntiSigmaIEtaIEtaMRNew.Fill(MRNew, WPU);
            if(R2New > 0.05)   HAntiSigmaIEtaIEtaMRNew_R2New005.Fill(MRNew, WPU);
            if(R2New > 0.10)   HAntiSigmaIEtaIEtaMRNew_R2New010.Fill(MRNew, WPU);
            if(R2New > 0.15)   HAntiSigmaIEtaIEtaMRNew_R2New015.Fill(MRNew, WPU);
            if(R2New > 0.20)   HAntiSigmaIEtaIEtaMRNew_R2New020.Fill(MRNew, WPU);
            if(R2New > 0.25)   HAntiSigmaIEtaIEtaMRNew_R2New025.Fill(MRNew, WPU);

            HAntiSigmaIEtaIEtaR2New.Fill(R2New, WPU);
            if(MRNew > 300)   HAntiSigmaIEtaIEtaR2New_MRNew300.Fill(R2New, WPU);
            if(MRNew > 400)   HAntiSigmaIEtaIEtaR2New_MRNew400.Fill(R2New, WPU);
            if(MRNew > 500)   HAntiSigmaIEtaIEtaR2New_MRNew500.Fill(R2New, WPU);
            if(MRNew > 600)   HAntiSigmaIEtaIEtaR2New_MRNew600.Fill(R2New, WPU);
            if(MRNew > 700)   HAntiSigmaIEtaIEtaR2New_MRNew700.Fill(R2New, WPU);
         }
         if(Loose80Count >= 0 && AntiElectronCount > 0)
         {
            HAntiElectronMRNew.Fill(MRNew, WPU);
            if(R2New > 0.05)   HAntiElectronMRNew_R2New005.Fill(MRNew, WPU);
            if(R2New > 0.10)   HAntiElectronMRNew_R2New010.Fill(MRNew, WPU);
            if(R2New > 0.15)   HAntiElectronMRNew_R2New015.Fill(MRNew, WPU);
            if(R2New > 0.20)   HAntiElectronMRNew_R2New020.Fill(MRNew, WPU);
            if(R2New > 0.25)   HAntiElectronMRNew_R2New025.Fill(MRNew, WPU);

            HAntiElectronR2New.Fill(R2New, WPU);
            if(MRNew > 300)   HAntiElectronR2New_MRNew300.Fill(R2New, WPU);
            if(MRNew > 400)   HAntiElectronR2New_MRNew400.Fill(R2New, WPU);
            if(MRNew > 500)   HAntiElectronR2New_MRNew500.Fill(R2New, WPU);
            if(MRNew > 600)   HAntiElectronR2New_MRNew600.Fill(R2New, WPU);
            if(MRNew > 700)   HAntiElectronR2New_MRNew700.Fill(R2New, WPU);
         }
         if(Loose80Count >= 0 && AntiIsolationCount > 0)
         {
            HAntiIsolationMRNew.Fill(MRNew, WPU);
            if(R2New > 0.05)   HAntiIsolationMRNew_R2New005.Fill(MRNew, WPU);
            if(R2New > 0.10)   HAntiIsolationMRNew_R2New010.Fill(MRNew, WPU);
            if(R2New > 0.15)   HAntiIsolationMRNew_R2New015.Fill(MRNew, WPU);
            if(R2New > 0.20)   HAntiIsolationMRNew_R2New020.Fill(MRNew, WPU);
            if(R2New > 0.25)   HAntiIsolationMRNew_R2New025.Fill(MRNew, WPU);

            HAntiIsolationR2New.Fill(R2New, WPU);
            if(MRNew > 300)   HAntiIsolationR2New_MRNew300.Fill(R2New, WPU);
            if(MRNew > 400)   HAntiIsolationR2New_MRNew400.Fill(R2New, WPU);
            if(MRNew > 500)   HAntiIsolationR2New_MRNew500.Fill(R2New, WPU);
            if(MRNew > 600)   HAntiIsolationR2New_MRNew600.Fill(R2New, WPU);
            if(MRNew > 700)   HAntiIsolationR2New_MRNew700.Fill(R2New, WPU);
         }
         if(Loose80Count >= 0 && AntiIsolationCount >= 0)   // Anti-nothing!
         {
            HAntiNothingMRNew.Fill(MRNew, WPU);
            if(R2New > 0.05)   HAntiNothingMRNew_R2New005.Fill(MRNew, WPU);
            if(R2New > 0.10)   HAntiNothingMRNew_R2New010.Fill(MRNew, WPU);
            if(R2New > 0.15)   HAntiNothingMRNew_R2New015.Fill(MRNew, WPU);
            if(R2New > 0.20)   HAntiNothingMRNew_R2New020.Fill(MRNew, WPU);
            if(R2New > 0.25)   HAntiNothingMRNew_R2New025.Fill(MRNew, WPU);

            HAntiNothingR2New.Fill(R2New, WPU);
            if(MRNew > 300)   HAntiNothingR2New_MRNew300.Fill(R2New, WPU);
            if(MRNew > 400)   HAntiNothingR2New_MRNew400.Fill(R2New, WPU);
            if(MRNew > 500)   HAntiNothingR2New_MRNew500.Fill(R2New, WPU);
            if(MRNew > 600)   HAntiNothingR2New_MRNew600.Fill(R2New, WPU);
            if(MRNew > 700)   HAntiNothingR2New_MRNew700.Fill(R2New, WPU);
         }
      }
   }

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   PsFile.AddTextPage("Basic pileup sanity checks");
   PsFile.AddPlot(HRawNPU, "", true);
   PsFile.AddPlot(HNPU, "", true);

   PsFile.AddTextPage("Electron candidates");
   PsFile.AddPlot(HAllElectronCount, "hist text00", true);
   PsFile.AddPlot(HAllElectronPT, "hist", true);
   PsFile.AddPlot(HAllElectronEta, "hist", false);
   PsFile.AddPlot(HAllElectronPhi, "hist", false);
   PsFile.AddPlot(HAllElectronSigmaIEtaIEta, "", true);
   PsFile.AddPlot(HAllElectronSigmaIEtaIEtaBarrel, "", true);
   PsFile.AddPlot(HAllElectronSigmaIEtaIEtaEndcap, "", true);
   PsFile.AddPlot(HAllElectronIsolation, "", true);
   PsFile.AddPlot(HAllElectronIsolationBarrel, "", true);
   PsFile.AddPlot(HAllElectronIsolationEndcap, "", true);
   PsFile.AddPlot(HAllElectronRelativeIsolation, "", true);
   PsFile.AddPlot(HAllElectronRelativeIsolationBarrel, "", true);
   PsFile.AddPlot(HAllElectronRelativeIsolationEndcap, "", true);
   PsFile.AddPlot(HAllElectronRelativeIsolationVsSigmaIEtaIEtaBarrel, "colz", false);
   PsFile.AddPlot(HAllElectronRelativeIsolationVsSigmaIEtaIEtaEndcap, "colz", false);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaCount, "hist text00", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaBarrelCount, "hist text00", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaEndcapCount, "hist text00", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaCountLL, "hist text00", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaBarrelCountLL, "hist text00", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaEndcapCountLL, "hist text00", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLMRNew, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLMRNew_R2New005, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLMRNew_R2New010, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLMRNew_R2New015, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLMRNew_R2New020, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLMRNew_R2New025, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLR2New, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLR2New_MRNew300, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLR2New_MRNew400, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLR2New_MRNew500, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLR2New_MRNew600, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLLR2New_MRNew700, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLMRNew, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLMRNew_R2New005, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLMRNew_R2New010, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLMRNew_R2New015, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLMRNew_R2New020, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLMRNew_R2New025, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLR2New, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLR2New_MRNew300, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLR2New_MRNew400, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLR2New_MRNew500, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLR2New_MRNew600, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaLR2New_MRNew700, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaMRNew, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaMRNew_R2New005, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaMRNew_R2New010, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaMRNew_R2New015, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaMRNew_R2New020, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaMRNew_R2New025, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaR2New, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaR2New_MRNew300, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaR2New_MRNew400, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaR2New_MRNew500, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaR2New_MRNew600, "", true);
   PsFile.AddPlot(HAntiSigmaIEtaIEtaR2New_MRNew700, "", true);
   PsFile.AddPlot(HAntiElectronMRNew, "", true);
   PsFile.AddPlot(HAntiElectronMRNew_R2New005, "", true);
   PsFile.AddPlot(HAntiElectronMRNew_R2New010, "", true);
   PsFile.AddPlot(HAntiElectronMRNew_R2New015, "", true);
   PsFile.AddPlot(HAntiElectronMRNew_R2New020, "", true);
   PsFile.AddPlot(HAntiElectronMRNew_R2New025, "", true);
   PsFile.AddPlot(HAntiElectronR2New, "", true);
   PsFile.AddPlot(HAntiElectronR2New_MRNew300, "", true);
   PsFile.AddPlot(HAntiElectronR2New_MRNew400, "", true);
   PsFile.AddPlot(HAntiElectronR2New_MRNew500, "", true);
   PsFile.AddPlot(HAntiElectronR2New_MRNew600, "", true);
   PsFile.AddPlot(HAntiElectronR2New_MRNew700, "", true);
   PsFile.AddPlot(HAntiIsolationMRNew, "", true);
   PsFile.AddPlot(HAntiIsolationMRNew_R2New005, "", true);
   PsFile.AddPlot(HAntiIsolationMRNew_R2New010, "", true);
   PsFile.AddPlot(HAntiIsolationMRNew_R2New015, "", true);
   PsFile.AddPlot(HAntiIsolationMRNew_R2New020, "", true);
   PsFile.AddPlot(HAntiIsolationMRNew_R2New025, "", true);
   PsFile.AddPlot(HAntiIsolationR2New, "", true);
   PsFile.AddPlot(HAntiIsolationR2New_MRNew300, "", true);
   PsFile.AddPlot(HAntiIsolationR2New_MRNew400, "", true);
   PsFile.AddPlot(HAntiIsolationR2New_MRNew500, "", true);
   PsFile.AddPlot(HAntiIsolationR2New_MRNew600, "", true);
   PsFile.AddPlot(HAntiIsolationR2New_MRNew700, "", true);
   PsFile.AddPlot(HAntiNothingMRNew, "", true);
   PsFile.AddPlot(HAntiNothingMRNew_R2New005, "", true);
   PsFile.AddPlot(HAntiNothingMRNew_R2New010, "", true);
   PsFile.AddPlot(HAntiNothingMRNew_R2New015, "", true);
   PsFile.AddPlot(HAntiNothingMRNew_R2New020, "", true);
   PsFile.AddPlot(HAntiNothingMRNew_R2New025, "", true);
   PsFile.AddPlot(HAntiNothingR2New, "", true);
   PsFile.AddPlot(HAntiNothingR2New_MRNew300, "", true);
   PsFile.AddPlot(HAntiNothingR2New_MRNew400, "", true);
   PsFile.AddPlot(HAntiNothingR2New_MRNew500, "", true);
   PsFile.AddPlot(HAntiNothingR2New_MRNew600, "", true);
   PsFile.AddPlot(HAntiNothingR2New_MRNew700, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   HRawNPU.Write();
   HNPU.Write();

   HAllElectronCount.Write();
   HAllElectronPT.Write();
   HAllElectronEta.Write();
   HAllElectronPhi.Write();
   HAllElectronSigmaIEtaIEta.Write();
   HAllElectronSigmaIEtaIEtaBarrel.Write();
   HAllElectronSigmaIEtaIEtaEndcap.Write();
   HAllElectronIsolation.Write();
   HAllElectronIsolationBarrel.Write();
   HAllElectronIsolationEndcap.Write();
   HAllElectronRelativeIsolation.Write();
   HAllElectronRelativeIsolationBarrel.Write();
   HAllElectronRelativeIsolationEndcap.Write();
   HAntiSigmaIEtaIEtaCount.Write();
   HAntiSigmaIEtaIEtaBarrelCount.Write();
   HAntiSigmaIEtaIEtaEndcapCount.Write();
   HAntiSigmaIEtaIEtaCountLL.Write();
   HAntiSigmaIEtaIEtaBarrelCountLL.Write();
   HAntiSigmaIEtaIEtaEndcapCountLL.Write();
   HAntiSigmaIEtaIEtaLLMRNew.Write();
   HAntiSigmaIEtaIEtaLLMRNew_R2New005.Write();
   HAntiSigmaIEtaIEtaLLMRNew_R2New010.Write();
   HAntiSigmaIEtaIEtaLLMRNew_R2New015.Write();
   HAntiSigmaIEtaIEtaLLMRNew_R2New020.Write();
   HAntiSigmaIEtaIEtaLLMRNew_R2New025.Write();
   HAntiSigmaIEtaIEtaLLR2New.Write();
   HAntiSigmaIEtaIEtaLLR2New_MRNew300.Write();
   HAntiSigmaIEtaIEtaLLR2New_MRNew400.Write();
   HAntiSigmaIEtaIEtaLLR2New_MRNew500.Write();
   HAntiSigmaIEtaIEtaLLR2New_MRNew600.Write();
   HAntiSigmaIEtaIEtaLLR2New_MRNew700.Write();
   HAntiSigmaIEtaIEtaLMRNew.Write();
   HAntiSigmaIEtaIEtaLMRNew_R2New005.Write();
   HAntiSigmaIEtaIEtaLMRNew_R2New010.Write();
   HAntiSigmaIEtaIEtaLMRNew_R2New015.Write();
   HAntiSigmaIEtaIEtaLMRNew_R2New020.Write();
   HAntiSigmaIEtaIEtaLMRNew_R2New025.Write();
   HAntiSigmaIEtaIEtaLR2New.Write();
   HAntiSigmaIEtaIEtaLR2New_MRNew300.Write();
   HAntiSigmaIEtaIEtaLR2New_MRNew400.Write();
   HAntiSigmaIEtaIEtaLR2New_MRNew500.Write();
   HAntiSigmaIEtaIEtaLR2New_MRNew600.Write();
   HAntiSigmaIEtaIEtaLR2New_MRNew700.Write();
   HAntiSigmaIEtaIEtaMRNew.Write();
   HAntiSigmaIEtaIEtaMRNew_R2New005.Write();
   HAntiSigmaIEtaIEtaMRNew_R2New010.Write();
   HAntiSigmaIEtaIEtaMRNew_R2New015.Write();
   HAntiSigmaIEtaIEtaMRNew_R2New020.Write();
   HAntiSigmaIEtaIEtaMRNew_R2New025.Write();
   HAntiSigmaIEtaIEtaR2New.Write();
   HAntiSigmaIEtaIEtaR2New_MRNew300.Write();
   HAntiSigmaIEtaIEtaR2New_MRNew400.Write();
   HAntiSigmaIEtaIEtaR2New_MRNew500.Write();
   HAntiSigmaIEtaIEtaR2New_MRNew600.Write();
   HAntiSigmaIEtaIEtaR2New_MRNew700.Write();
   HAntiElectronMRNew.Write();
   HAntiElectronMRNew_R2New005.Write();
   HAntiElectronMRNew_R2New010.Write();
   HAntiElectronMRNew_R2New015.Write();
   HAntiElectronMRNew_R2New020.Write();
   HAntiElectronMRNew_R2New025.Write();
   HAntiElectronR2New.Write();
   HAntiElectronR2New_MRNew300.Write();
   HAntiElectronR2New_MRNew400.Write();
   HAntiElectronR2New_MRNew500.Write();
   HAntiElectronR2New_MRNew600.Write();
   HAntiElectronR2New_MRNew700.Write();
   HAntiIsolationMRNew.Write();
   HAntiIsolationMRNew_R2New005.Write();
   HAntiIsolationMRNew_R2New010.Write();
   HAntiIsolationMRNew_R2New015.Write();
   HAntiIsolationMRNew_R2New020.Write();
   HAntiIsolationMRNew_R2New025.Write();
   HAntiIsolationR2New.Write();
   HAntiIsolationR2New_MRNew300.Write();
   HAntiIsolationR2New_MRNew400.Write();
   HAntiIsolationR2New_MRNew500.Write();
   HAntiIsolationR2New_MRNew600.Write();
   HAntiIsolationR2New_MRNew700.Write();
   HAntiNothingMRNew.Write();
   HAntiNothingMRNew_R2New005.Write();
   HAntiNothingMRNew_R2New010.Write();
   HAntiNothingMRNew_R2New015.Write();
   HAntiNothingMRNew_R2New020.Write();
   HAntiNothingMRNew_R2New025.Write();
   HAntiNothingR2New.Write();
   HAntiNothingR2New_MRNew300.Write();
   HAntiNothingR2New_MRNew400.Write();
   HAntiNothingR2New_MRNew500.Write();
   HAntiNothingR2New_MRNew600.Write();
   HAntiNothingR2New_MRNew700.Write();

   OutputF.Close();

   return 0;
}



