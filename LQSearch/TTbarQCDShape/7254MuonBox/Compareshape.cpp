#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "TFile.h"
#include "TChain.h"
#include "TTree.h"

#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   string InputFileName = "Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root";
   string OutputBase = "TTbar";
   double CrossSection = 165;
   const double Luminosity = 1000;

   if(argc < 4)
   {
      cout << "Usage: " << argv[0] << " InputFile CrossSection OutputBase" << endl;
      return -1;
   }

   InputFileName = argv[1];
   OutputBase = argv[3];
   stringstream CrossSectionConversion(argv[2]);
   CrossSectionConversion >> CrossSection;

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(InputFileName.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("Samples/BookKeeping/Example.PU.root");

   Tree.SetBranchStatus("*", false);
   Tree.SetBranchStatus("CaloJet*", true);
   Tree.SetBranchStatus("PFMET", true);
   Tree.SetBranchStatus("GoodElectronCount", true);
   Tree.SetBranchStatus("GoodMuonCount", true);
   Tree.SetBranchStatus("Muon1PT", true);
   Tree.SetBranchStatus("Muon2PT", true);

   double AllEvents = 0;
   TFile InputF(InputFileName.c_str());
   TH1D *H = (TH1D *)InputF.Get("HProcessedEventsPU");
   for(int i = 1; i <= H->GetNbinsX(); i++)
      AllEvents = AllEvents + M.GetWeight(i - 1) * H->GetBinContent(i);
   InputF.Close();

   TFile OutputF(Form("%s.root", OutputBase.c_str()), "recreate");

   TH1D HMRNew("HMRNew", "MR (new);MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New005("HMRNew_R2New005", "MR (new), R^{2} (new) > 0.05;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New010("HMRNew_R2New010", "MR (new), R^{2} (new) > 0.10;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New015("HMRNew_R2New015", "MR (new), R^{2} (new) > 0.15;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New020("HMRNew_R2New020", "MR (new), R^{2} (new) > 0.20;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New025("HMRNew_R2New025", "MR (new), R^{2} (new) > 0.25;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New030("HMRNew_R2New030", "MR (new), R^{2} (new) > 0.30;MR (new)", 40, 0, 1000);
   TH1D HR2New("HR2New", "R^{2} (new);R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew200("HR2New_MRNew200", "R^{2} (new), MR (new) > 200;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew300("HR2New_MRNew300", "R^{2} (new), MR (new) > 300;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew400("HR2New_MRNew400", "R^{2} (new), MR (new) > 400;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew500("HR2New_MRNew500", "R^{2} (new), MR (new) > 500;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew600("HR2New_MRNew600", "R^{2} (new), MR (new) > 600;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew700("HR2New_MRNew700", "R^{2} (new), MR (new) > 700;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew800("HR2New_MRNew800", "R^{2} (new), MR (new) > 800;R^{2} (new)", 40, 0, 1.2);

   TH1D HMRNew_L("HMRNew_L", "MR (new), single loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New005_L("HMRNew_R2New005_L", "MR (new), R^{2} (new) > 0.05, single loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New010_L("HMRNew_R2New010_L", "MR (new), R^{2} (new) > 0.10, single loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New015_L("HMRNew_R2New015_L", "MR (new), R^{2} (new) > 0.15, single loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New020_L("HMRNew_R2New020_L", "MR (new), R^{2} (new) > 0.20, single loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New025_L("HMRNew_R2New025_L", "MR (new), R^{2} (new) > 0.25, single loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New030_L("HMRNew_R2New030_L", "MR (new), R^{2} (new) > 0.30, single loose tag;MR (new)", 40, 0, 1000);
   TH1D HR2New_L("HR2New_L", "R^{2} (new), single loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew200_L("HR2New_MRNew200_L", "R^{2} (new), MR (new) > 200, single loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew300_L("HR2New_MRNew300_L", "R^{2} (new), MR (new) > 300, single loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew400_L("HR2New_MRNew400_L", "R^{2} (new), MR (new) > 400, single loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew500_L("HR2New_MRNew500_L", "R^{2} (new), MR (new) > 500, single loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew600_L("HR2New_MRNew600_L", "R^{2} (new), MR (new) > 600, single loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew700_L("HR2New_MRNew700_L", "R^{2} (new), MR (new) > 700, single loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew800_L("HR2New_MRNew800_L", "R^{2} (new), MR (new) > 800, single loose tag;R^{2} (new)", 40, 0, 1.2);

   TH1D HMRNew_LL("HMRNew_LL", "MR (new), double loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New005_LL("HMRNew_R2New005_LL", "MR (new), R^{2} (new) > 0.05, double loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New010_LL("HMRNew_R2New010_LL", "MR (new), R^{2} (new) > 0.10, double loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New015_LL("HMRNew_R2New015_LL", "MR (new), R^{2} (new) > 0.15, double loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New020_LL("HMRNew_R2New020_LL", "MR (new), R^{2} (new) > 0.20, double loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New025_LL("HMRNew_R2New025_LL", "MR (new), R^{2} (new) > 0.25, double loose tag;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New030_LL("HMRNew_R2New030_LL", "MR (new), R^{2} (new) > 0.30, double loose tag;MR (new)", 40, 0, 1000);
   TH1D HR2New_LL("HR2New_LL", "R^{2} (new), double loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew200_LL("HR2New_MRNew200_LL", "R^{2} (new), MR (new) > 200, double loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew300_LL("HR2New_MRNew300_LL", "R^{2} (new), MR (new) > 300, double loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew400_LL("HR2New_MRNew400_LL", "R^{2} (new), MR (new) > 400, double loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew500_LL("HR2New_MRNew500_LL", "R^{2} (new), MR (new) > 500, double loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew600_LL("HR2New_MRNew600_LL", "R^{2} (new), MR (new) > 600, double loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew700_LL("HR2New_MRNew700_LL", "R^{2} (new), MR (new) > 700, double loose tag;R^{2} (new)", 40, 0, 1.2);
   TH1D HR2New_MRNew800_LL("HR2New_MRNew800_LL", "R^{2} (new), MR (new) > 800, double loose tag;R^{2} (new)", 40, 0, 1.2);

   HMRNew.Sumw2();
   HMRNew_R2New005.Sumw2();
   HMRNew_R2New010.Sumw2();
   HMRNew_R2New015.Sumw2();
   HMRNew_R2New020.Sumw2();
   HMRNew_R2New025.Sumw2();
   HMRNew_R2New030.Sumw2();
   HR2New.Sumw2();
   HR2New_MRNew200.Sumw2();
   HR2New_MRNew300.Sumw2();
   HR2New_MRNew400.Sumw2();
   HR2New_MRNew500.Sumw2();
   HR2New_MRNew600.Sumw2();
   HR2New_MRNew700.Sumw2();
   HR2New_MRNew800.Sumw2();

   HMRNew_L.Sumw2();
   HMRNew_R2New005_L.Sumw2();
   HMRNew_R2New010_L.Sumw2();
   HMRNew_R2New015_L.Sumw2();
   HMRNew_R2New020_L.Sumw2();
   HMRNew_R2New025_L.Sumw2();
   HMRNew_R2New030_L.Sumw2();
   HR2New_L.Sumw2();
   HR2New_MRNew200_L.Sumw2();
   HR2New_MRNew300_L.Sumw2();
   HR2New_MRNew400_L.Sumw2();
   HR2New_MRNew500_L.Sumw2();
   HR2New_MRNew600_L.Sumw2();
   HR2New_MRNew700_L.Sumw2();
   HR2New_MRNew800_L.Sumw2();

   HMRNew_LL.Sumw2();
   HMRNew_R2New005_LL.Sumw2();
   HMRNew_R2New010_LL.Sumw2();
   HMRNew_R2New015_LL.Sumw2();
   HMRNew_R2New020_LL.Sumw2();
   HMRNew_R2New025_LL.Sumw2();
   HMRNew_R2New030_LL.Sumw2();
   HR2New_LL.Sumw2();
   HR2New_MRNew200_LL.Sumw2();
   HR2New_MRNew300_LL.Sumw2();
   HR2New_MRNew400_LL.Sumw2();
   HR2New_MRNew500_LL.Sumw2();
   HR2New_MRNew600_LL.Sumw2();
   HR2New_MRNew700_LL.Sumw2();
   HR2New_MRNew800_LL.Sumw2();

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing entry "<< iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      double WPU = M.GetCurrentWeight() * CrossSection * Luminosity / AllEvents;

      if(M.GoodElectronCount > 0)
         continue;
      if(M.GoodMuonCount == 0 || (M.GoodMuonCount == 1 && M.Muon1PT < 20) || M.GoodMuonCount >= 2)
         continue;

      int LooseTagCount = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 80)
            continue;
         if(M.CaloJetTCHETag[i] < 1.7)
            continue;
         LooseTagCount = LooseTagCount + 1;
      }

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 40)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);
         GoodJets.push_back(NewJet);
      }
      if(GoodJets.size() < 2 || GoodJets.size() > 20)
         continue;

      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);

      double MRNew = Get2011MR(Groups[0], Groups[1]);
      double RNew = Get2011R(Groups[0], Groups[1], PFMET);
      double R2New = RNew * RNew;

      HMRNew.Fill(MRNew, WPU);
      if(R2New > 0.05)   HMRNew_R2New005.Fill(MRNew, WPU);
      if(R2New > 0.10)   HMRNew_R2New010.Fill(MRNew, WPU);
      if(R2New > 0.15)   HMRNew_R2New015.Fill(MRNew, WPU);
      if(R2New > 0.20)   HMRNew_R2New020.Fill(MRNew, WPU);
      if(R2New > 0.25)   HMRNew_R2New025.Fill(MRNew, WPU);
      if(R2New > 0.30)   HMRNew_R2New030.Fill(MRNew, WPU);

      HR2New.Fill(R2New, WPU);
      if(MRNew > 200)   HR2New_MRNew200.Fill(R2New, WPU);
      if(MRNew > 300)   HR2New_MRNew300.Fill(R2New, WPU);
      if(MRNew > 400)   HR2New_MRNew400.Fill(R2New, WPU);
      if(MRNew > 500)   HR2New_MRNew500.Fill(R2New, WPU);
      if(MRNew > 600)   HR2New_MRNew600.Fill(R2New, WPU);
      if(MRNew > 700)   HR2New_MRNew700.Fill(R2New, WPU);
      if(MRNew > 800)   HR2New_MRNew800.Fill(R2New, WPU);

      if(LooseTagCount >= 1)
      {
         HMRNew_L.Fill(MRNew, WPU);
         if(R2New > 0.05)   HMRNew_R2New005_L.Fill(MRNew, WPU);
         if(R2New > 0.10)   HMRNew_R2New010_L.Fill(MRNew, WPU);
         if(R2New > 0.15)   HMRNew_R2New015_L.Fill(MRNew, WPU);
         if(R2New > 0.20)   HMRNew_R2New020_L.Fill(MRNew, WPU);
         if(R2New > 0.25)   HMRNew_R2New025_L.Fill(MRNew, WPU);
         if(R2New > 0.30)   HMRNew_R2New030_L.Fill(MRNew, WPU);

         HR2New_L.Fill(R2New, WPU);
         if(MRNew > 200)   HR2New_MRNew200_L.Fill(R2New, WPU);
         if(MRNew > 300)   HR2New_MRNew300_L.Fill(R2New, WPU);
         if(MRNew > 400)   HR2New_MRNew400_L.Fill(R2New, WPU);
         if(MRNew > 500)   HR2New_MRNew500_L.Fill(R2New, WPU);
         if(MRNew > 600)   HR2New_MRNew600_L.Fill(R2New, WPU);
         if(MRNew > 700)   HR2New_MRNew700_L.Fill(R2New, WPU);
         if(MRNew > 800)   HR2New_MRNew800_L.Fill(R2New, WPU);
      }

      if(LooseTagCount >= 2)
      {
         HMRNew_LL.Fill(MRNew, WPU);
         if(R2New > 0.05)   HMRNew_R2New005_LL.Fill(MRNew, WPU);
         if(R2New > 0.10)   HMRNew_R2New010_LL.Fill(MRNew, WPU);
         if(R2New > 0.15)   HMRNew_R2New015_LL.Fill(MRNew, WPU);
         if(R2New > 0.20)   HMRNew_R2New020_LL.Fill(MRNew, WPU);
         if(R2New > 0.25)   HMRNew_R2New025_LL.Fill(MRNew, WPU);
         if(R2New > 0.30)   HMRNew_R2New030_LL.Fill(MRNew, WPU);

         HR2New_LL.Fill(R2New, WPU);
         if(MRNew > 200)   HR2New_MRNew200_LL.Fill(R2New, WPU);
         if(MRNew > 300)   HR2New_MRNew300_LL.Fill(R2New, WPU);
         if(MRNew > 400)   HR2New_MRNew400_LL.Fill(R2New, WPU);
         if(MRNew > 500)   HR2New_MRNew500_LL.Fill(R2New, WPU);
         if(MRNew > 600)   HR2New_MRNew600_LL.Fill(R2New, WPU);
         if(MRNew > 700)   HR2New_MRNew700_LL.Fill(R2New, WPU);
         if(MRNew > 800)   HR2New_MRNew800_LL.Fill(R2New, WPU);
      }
   }

   HMRNew.Write();
   HMRNew_R2New005.Write();
   HMRNew_R2New010.Write();
   HMRNew_R2New015.Write();
   HMRNew_R2New020.Write();
   HMRNew_R2New025.Write();
   HMRNew_R2New030.Write();

   HR2New.Write();
   HR2New_MRNew200.Write();
   HR2New_MRNew300.Write();
   HR2New_MRNew400.Write();
   HR2New_MRNew500.Write();
   HR2New_MRNew600.Write();
   HR2New_MRNew700.Write();
   HR2New_MRNew800.Write();
   
   HMRNew_L.Write();
   HMRNew_R2New005_L.Write();
   HMRNew_R2New010_L.Write();
   HMRNew_R2New015_L.Write();
   HMRNew_R2New020_L.Write();
   HMRNew_R2New025_L.Write();
   HMRNew_R2New030_L.Write();

   HR2New_L.Write();
   HR2New_MRNew200_L.Write();
   HR2New_MRNew300_L.Write();
   HR2New_MRNew400_L.Write();
   HR2New_MRNew500_L.Write();
   HR2New_MRNew600_L.Write();
   HR2New_MRNew700_L.Write();
   HR2New_MRNew800_L.Write();
   
   HMRNew_LL.Write();
   HMRNew_R2New005_LL.Write();
   HMRNew_R2New010_LL.Write();
   HMRNew_R2New015_LL.Write();
   HMRNew_R2New020_LL.Write();
   HMRNew_R2New025_LL.Write();
   HMRNew_R2New030_LL.Write();

   HR2New_LL.Write();
   HR2New_MRNew200_LL.Write();
   HR2New_MRNew300_LL.Write();
   HR2New_MRNew400_LL.Write();
   HR2New_MRNew500_LL.Write();
   HR2New_MRNew600_LL.Write();
   HR2New_MRNew700_LL.Write();
   HR2New_MRNew800_LL.Write();

   OutputF.Close();

   return 0;
}





