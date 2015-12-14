#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"

#include "PlotHelper2.h"
#include "SetStyle.h"
#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"

int main();
void ReadSample(string Input, string OutputBase, double CrossSection, double Luminosity);

int main()
{
   SetStyle();

   ReadSample("DataSamples/HTRun2011Av4_All.root", "DataPlots", -1, 863.338747287);
   ReadSample("MCSamples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar", 165, 863.338747287);   // NNLL
   ReadSample("MCSamples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root", "W", 31314, 863.338747287);   // NNLO
   ReadSample("MCSamples/VVJetsTo4L_TuneD6T_7TeV-madgraph-tauola_All.root", "VV", 4.8, 863.338747287);   // Production
   ReadSample("MCSamples/PhotonVJets_7TeV-madgraph_All.root", "GammaVJet", 173, 863.338747287);   // Production
   ReadSample("MCSamples/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root", "DY50", 3048, 863.338747287);   // NNLO
   ReadSample("MCSamples/ZinvisibleJets_7TeV-madgraph_All.root", "Znunu", 3048 * 6, 863.338747287);   // guessed
   ReadSample("MCSamples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root", "QCD1", 30000000, 863.338747287);   // production
   ReadSample("MCSamples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root", "QCD2", 7000000, 863.338747287);   // production
   ReadSample("MCSamples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root", "QCD3", 171000, 863.338747287);   // production
   ReadSample("MCSamples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root", "QCD4", 5200, 863.338747287);   // production
   ReadSample("MCSamples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root", "QCD5", 83, 863.338747287);   // production

   return 0;
}

void ReadSample(string Input, string OutputBase, double CrossSection, double Luminosity)
{
   cout << "Start processing sample " << Input << endl;

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(Input.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("DataSamples/BookKeeping/7222ReRun_HTRun2011Av4.PU.root");

   double NumberOfProcessedEvents = 0;
   double WeightedEvents = 0;
   TFile F(Input.c_str());
   NumberOfProcessedEvents = ((TH2D *)F.Get("HProcessedEvents"))->GetBinContent(1, 1);
   TH1D *HPUDistribution = (TH1D *)F.Get("HProcessedEventsPU");
   for(int i = 0; i < HPUDistribution->GetNbinsX(); i++)
      WeightedEvents = WeightedEvents + HPUDistribution->GetBinContent(i + 1) * M.GetWeight(i);
   F.Close();

   double Factor = CrossSection * Luminosity / WeightedEvents;
   if(CrossSection < 0)   // data!
      Factor = 1;

   cout << "ProcessedEvents = " << NumberOfProcessedEvents << endl;
   if(CrossSection > 0)
   {
      cout << "ProcessedEvents with weight = " << WeightedEvents << endl;
      cout << "Sigma * L / Count = " << CrossSection * Luminosity / NumberOfProcessedEvents << endl;
   }

   TFile OutputFile(Form("%s.root", OutputBase.c_str()), "RECREATE");
   TTree OutputTree("MRTree", "MRTree");

   double TreeMR;
   double TreeR;
   double TreeRsq;
   double TreeFactor;

   OutputTree.Branch("MR", &TreeMR, "MR/D");
   OutputTree.Branch("R", &TreeR, "R/D");
   OutputTree.Branch("Rsq", &TreeRsq, "Rsq/D");
   OutputTree.Branch("Factor", &TreeFactor, "Factor/D");

   TH1D HWeight("HWeight", "Weight of events from pileups only", 100, 0, 1);
   TH1D HNPU("HNPU", "Closure check of number of added PU, not weighted", 25, 0, 25);
   TH1D HNPUWeighted("HNPUWeighted", "Closure check of number of added PU, weighted", 25, 0, 25);

   TH1D HMRNewFullRegion("HMRNewFullRegion", "MR (new), full region;MR (new)", 60, 0, 1500);
   TH1D HR2NewFullRegion("HR2NewFullRegion", "R^{2} (new), full region;R^{2} (new)", 50, 0, 0.5);
   TH1D HMRNewRegionB1("HMRNewRegionB1", "MR (new), region B1;MR (n32)", 60, 0, 1500);
   TH1D HR2NewRegionB1("HR2NewRegionB1", "R^{2} (new), region B1;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionB1("HMRNewVsR2NewRegionB1",
      "MR (new) vs. R^{2} (new), region B1;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionB2("HMRNewRegionB2", "MR (new), region B2;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionB2("HR2NewRegionB2", "R^{2} (new), region B2;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionB2("HMRNewVsR2NewRegionB2",
      "MR (new) vs. R^{2} (new), region B2;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionB3("HMRNewRegionB3", "MR (new), region B3;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionB3("HR2NewRegionB3", "R^{2} (new), region B3;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionB3("HMRNewVsR2NewRegionB3",
      "MR (new) vs. R^{2} (new), region B3;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HCountRegions("HCountRegions", "Count in side-band regions B1-B3", 3, 0.5, 3.5);

   HCountRegions.GetXaxis()->SetBinLabel(1, "B1");
   HCountRegions.GetXaxis()->SetBinLabel(2, "B2");
   HCountRegions.GetXaxis()->SetBinLabel(3, "B3");
   
   TH1D HMRNewFullRegion_L("HMRNewFullRegion_L", "MR (new), full region, single-loose;MR (new)", 60, 0, 1500);
   TH1D HR2NewFullRegion_L("HR2NewFullRegion_L", "R^{2} (new), full region, single-loose;R^{2} (new)", 50, 0, 0.5);
   TH1D HMRNewRegionB1_L("HMRNewRegionB1_L", "MR (new), region B1 (single loose);MR (n32)", 60, 0, 1500);
   TH1D HR2NewRegionB1_L("HR2NewRegionB1_L", "R^{2} (new), region B1 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionB1_L("HMRNewVsR2NewRegionB1_L",
      "MR (new) vs. R^{2} (new), region B1 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionB2_L("HMRNewRegionB2_L", "MR (new), region B2 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionB2_L("HR2NewRegionB2_L", "R^{2} (new), region B2 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionB2_L("HMRNewVsR2NewRegionB2_L",
      "MR (new) vs. R^{2} (new), region B2 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionB3_L("HMRNewRegionB3_L", "MR (new), region B3 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionB3_L("HR2NewRegionB3_L", "R^{2} (new), region B3 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionB3_L("HMRNewVsR2NewRegionB3_L",
      "MR (new) vs. R^{2} (new), region B3 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HCountRegions_L("HCountRegions_L", "Count in sideband regions B1-B3 (single loose)", 3, 0.5, 3.5);

   HCountRegions_L.GetXaxis()->SetBinLabel(1, "B1");
   HCountRegions_L.GetXaxis()->SetBinLabel(2, "B2");
   HCountRegions_L.GetXaxis()->SetBinLabel(3, "B3");
   
   TH1D HMRNewFullRegion_LL("HMRNewFullRegion_LL", "MR (new), full region, double-loose;MR (new)", 60, 0, 1500);
   TH1D HR2NewFullRegion_LL("HR2NewFullRegion_LL", "R^{2} (new), full region, double-loose;R^{2} (new)", 50, 0, 0.5);
   TH1D HMRNewRegionB1_LL("HMRNewRegionB1_LL", "MR (new), region B1 (double loose);MR (n32)", 60, 0, 1500);
   TH1D HR2NewRegionB1_LL("HR2NewRegionB1_LL", "R^{2} (new), region B1 (double loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionB1_LL("HMRNewVsR2NewRegionB1_LL",
      "MR (new) vs. R^{2} (new), region B1 (double loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionB2_LL("HMRNewRegionB2_LL", "MR (new), region B2 (double loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionB2_LL("HR2NewRegionB2_LL", "R^{2} (new), region B2 (double loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionB2_LL("HMRNewVsR2NewRegionB2_LL",
      "MR (new) vs. R^{2} (new), region B2 (double loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionB3_LL("HMRNewRegionB3_LL", "MR (new), region B3 (double loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionB3_LL("HR2NewRegionB3_LL", "R^{2} (new), region B3 (double loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionB3_LL("HMRNewVsR2NewRegionB3_LL",
      "MR (new) vs. R^{2} (new), region B3 (double loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HCountRegions_LL("HCountRegions_LL", "Count in sideband regions B1-B3 (double loose)", 3, 0.5, 3.5);

   HCountRegions_LL.GetXaxis()->SetBinLabel(1, "B1");
   HCountRegions_LL.GetXaxis()->SetBinLabel(2, "B2");
   HCountRegions_LL.GetXaxis()->SetBinLabel(3, "B3");
   
   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 250000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      double WPU = 1;
      if(CrossSection > 0)
         WPU = M.GetCurrentWeight();
      HWeight.Fill(WPU);

      HNPU.Fill(M.PileUp);
      HNPUWeighted.Fill(M.PileUp, WPU * Factor);

      if(M.CaloJetCount > 100)   // woah....
         cout << "Large number of jets!!!!" << endl;
      if(M.CaloJetCount30 > 20)   // :(
         continue;
      if(M.PassNoiseFilter == false)
         continue;

      if(M.GoodElectronCount != 0)   // no electron
         continue;
      if(M.GoodMuonCount != 0)   // want no muon either
         continue;

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount && i < 100; i++)
      {
         if(M.CaloJetPT[i] < 40)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         GoodJets.push_back(NewJet);
      }
      if(GoodJets.size() > 20)
         continue;
      if(GoodJets.size() < 2)
         continue;

      vector<FourVector> Hemispheres = SplitIntoGroups(GoodJets, true);

      int LooseTagCount = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 80 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3 && M.CaloJetTCHETag[i] > 1.7)
            LooseTagCount = LooseTagCount + 1;

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);

      double MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
      double RNew = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      double R2New = RNew * RNew;

      bool InFull = false;
      bool InB1 = false;
      bool InB2 = false;
      bool InB3 = false;

      if(MRNew > 500 && R2New > 0.1)
         InFull = true;
      if(MRNew > 600 && R2New > 0.07)
         InFull = true;
      if(MRNew > 500 && MRNew <= 600 && R2New > 0.10 && R2New <= 0.14)
         InB1 = true;
      if(MRNew > 600 && MRNew <= 700 && R2New > 0.10 && R2New <= 0.14)
         InB2 = true;
      if(MRNew > 600 && MRNew <= 700 && R2New > 0.07 && R2New <= 0.10)
         InB3 = true;

      if(LooseTagCount >= 0)
      {
         if(InFull == true)
         {
            HMRNewFullRegion.Fill(MRNew, WPU * Factor);
            HR2NewFullRegion.Fill(R2New, WPU * Factor);
         }
         if(InB1 == true)
         {
            HMRNewRegionB1.Fill(MRNew, WPU * Factor);
            HR2NewRegionB1.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionB1.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(1, WPU * Factor);
         }
         if(InB2 == true)
         {
            HMRNewRegionB2.Fill(MRNew, WPU * Factor);
            HR2NewRegionB2.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionB2.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(2, WPU * Factor);
         }
         if(InB3 == true)
         {
            HMRNewRegionB3.Fill(MRNew, WPU * Factor);
            HR2NewRegionB3.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionB3.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(3, WPU * Factor);
         }
      }
      if(LooseTagCount >= 1)
      {
         if(InFull == true)
         {
            HMRNewFullRegion_L.Fill(MRNew, WPU * Factor);
            HR2NewFullRegion_L.Fill(R2New, WPU * Factor);
         }
         if(InB1 == true)
         {
            HMRNewRegionB1_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionB1_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionB1_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(1, WPU * Factor);
         }
         if(InB2 == true)
         {
            HMRNewRegionB2_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionB2_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionB2_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(2, WPU * Factor);
         }
         if(InB3 == true)
         {
            HMRNewRegionB3_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionB3_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionB3_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(3, WPU * Factor);
         }
      }
      if(LooseTagCount >= 2)
      {
         if(InFull == true)
         {
            HMRNewFullRegion_LL.Fill(MRNew, WPU * Factor);
            HR2NewFullRegion_LL.Fill(R2New, WPU * Factor);
         }
         if(InB1 == true)
         {
            HMRNewRegionB1_LL.Fill(MRNew, WPU * Factor);
            HR2NewRegionB1_LL.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionB1_LL.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_LL.Fill(1, WPU * Factor);
         }
         if(InB2 == true)
         {
            HMRNewRegionB2_LL.Fill(MRNew, WPU * Factor);
            HR2NewRegionB2_LL.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionB2_LL.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_LL.Fill(2, WPU * Factor);
         }
         if(InB3 == true)
         {
            HMRNewRegionB3_LL.Fill(MRNew, WPU * Factor);
            HR2NewRegionB3_LL.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionB3_LL.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_LL.Fill(3, WPU * Factor);
         }
      }

      if(InFull == true)
      {
         TreeMR = MRNew;
         TreeR = RNew;
         TreeRsq = R2New;
         TreeFactor = Factor * WPU;
         OutputTree.Fill();
      }
   }

   HWeight.Write();
   HNPU.Write();
   HNPUWeighted.Write();
   HMRNewFullRegion.Write();
   HR2NewFullRegion.Write();
   HMRNewRegionB1.Write();
   HR2NewRegionB1.Write();
   HMRNewVsR2NewRegionB1.Write();
   HMRNewRegionB2.Write();
   HR2NewRegionB2.Write();
   HMRNewVsR2NewRegionB2.Write();
   HMRNewRegionB3.Write();
   HR2NewRegionB3.Write();
   HMRNewVsR2NewRegionB3.Write();
   HCountRegions.Write();
   HMRNewFullRegion_L.Write();
   HR2NewFullRegion_L.Write();
   HMRNewRegionB1_L.Write();
   HR2NewRegionB1_L.Write();
   HMRNewVsR2NewRegionB1_L.Write();
   HMRNewRegionB2_L.Write();
   HR2NewRegionB2_L.Write();
   HMRNewVsR2NewRegionB2_L.Write();
   HMRNewRegionB3_L.Write();
   HR2NewRegionB3_L.Write();
   HMRNewVsR2NewRegionB3_L.Write();
   HCountRegions_L.Write();
   HMRNewFullRegion_LL.Write();
   HR2NewFullRegion_LL.Write();
   HMRNewRegionB1_LL.Write();
   HR2NewRegionB1_LL.Write();
   HMRNewVsR2NewRegionB1_LL.Write();
   HMRNewRegionB2_LL.Write();
   HR2NewRegionB2_LL.Write();
   HMRNewVsR2NewRegionB2_LL.Write();
   HMRNewRegionB3_LL.Write();
   HR2NewRegionB3_LL.Write();
   HMRNewVsR2NewRegionB3_LL.Write();
   HCountRegions_LL.Write();

   OutputTree.Write();

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   PsFile.AddPlot(HWeight, "", true);
   PsFile.AddPlot(HNPU);
   PsFile.AddPlot(HNPUWeighted);
   PsFile.AddPlot(HMRNewFullRegion, "", true);
   PsFile.AddPlot(HR2NewFullRegion, "", true);
   PsFile.AddPlot(HMRNewRegionB1, "", true);
   PsFile.AddPlot(HR2NewRegionB1, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB1, "colz");
   PsFile.AddPlot(HMRNewRegionB2, "", true);
   PsFile.AddPlot(HR2NewRegionB2, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB2, "colz");
   PsFile.AddPlot(HMRNewRegionB3, "", true);
   PsFile.AddPlot(HR2NewRegionB3, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB3, "colz");
   PsFile.AddPlot(HCountRegions, "", true);
   PsFile.AddPlot(HMRNewFullRegion_L, "", true);
   PsFile.AddPlot(HR2NewFullRegion_L, "", true);
   PsFile.AddPlot(HMRNewRegionB1_L, "", true);
   PsFile.AddPlot(HR2NewRegionB1_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB1_L, "colz");
   PsFile.AddPlot(HMRNewRegionB2_L, "", true);
   PsFile.AddPlot(HR2NewRegionB2_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB2_L, "colz");
   PsFile.AddPlot(HMRNewRegionB3_L, "", true);
   PsFile.AddPlot(HR2NewRegionB3_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB3_L, "colz");
   PsFile.AddPlot(HCountRegions_L, "", true);
   PsFile.AddPlot(HMRNewFullRegion_LL, "", true);
   PsFile.AddPlot(HR2NewFullRegion_LL, "", true);
   PsFile.AddPlot(HMRNewRegionB1_LL, "", true);
   PsFile.AddPlot(HR2NewRegionB1_LL, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB1_LL, "colz");
   PsFile.AddPlot(HMRNewRegionB2_LL, "", true);
   PsFile.AddPlot(HR2NewRegionB2_LL, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB2_LL, "colz");
   PsFile.AddPlot(HMRNewRegionB3_LL, "", true);
   PsFile.AddPlot(HR2NewRegionB3_LL, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB3_LL, "colz");
   PsFile.AddPlot(HCountRegions_LL, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




