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

   ReadSample("DataSamples/HTRun2011Av4_All.root", "DataPlots", -1, 963.338747287);
   ReadSample("MCSamples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar", 165, 963.338747287);   // NNLL
   ReadSample("MCSamples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root", "W", 31314, 963.338747287);   // NNLO
   ReadSample("MCSamples/VVJetsTo4L_TuneD6T_7TeV-madgraph-tauola_All.root", "VV", 4.8, 963.338747287);   // Production
   ReadSample("MCSamples/PhotonVJets_7TeV-madgraph_All.root", "GammaVJet", 173, 963.338747287);   // Production
   ReadSample("MCSamples/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root", "DY50", 3048, 963.338747287);   // NNLO
   ReadSample("MCSamples/ZinvisibleJets_7TeV-madgraph_All.root", "Znunu", 3048 * 6, 963.338747287);   // guessed
   ReadSample("MCSamples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root", "QCD1", 30000000, 963.338747287);   // production
   ReadSample("MCSamples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root", "QCD2", 7000000, 963.338747287);   // production
   ReadSample("MCSamples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root", "QCD3", 171000, 963.338747287);   // production
   ReadSample("MCSamples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root", "QCD4", 5200, 963.338747287);   // production
   ReadSample("MCSamples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root", "QCD5", 83, 963.338747287);   // production

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
   TH1D HMRNewUpperFullRegion("HMRNewUpperFullRegion", "MR (new), upper-full region;MR (new)", 60, 0, 1500);
   TH1D HR2NewUpperFullRegion("HR2NewUpperFullRegion", "R^{2} (new), upper-full region;R^{2} (new)", 50, 0, 0.5);
   TH1D HMRNewRightFullRegion("HMRNewRightFullRegion", "MR (new), right-full region;MR (new)", 60, 0, 1500);
   TH1D HR2NewRightFullRegion("HR2NewRightFullRegion", "R^{2} (new), right-full region;R^{2} (new)", 50, 0, 0.5);
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
   TH1D HMRNewRegionFS1("HMRNewRegionFS1", "MR (new), region FS1;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS1("HR2NewRegionFS1", "R^{2} (new), region FS1;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS1("HMRNewVsR2NewRegionFS1",
      "MR (new) vs. R^{2} (new), region FS1;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS2("HMRNewRegionFS2", "MR (new), region FS2;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS2("HR2NewRegionFS2", "R^{2} (new), region FS2;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS2("HMRNewVsR2NewRegionFS2",
      "MR (new) vs. R^{2} (new), region FS2;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS3("HMRNewRegionFS3", "MR (new), region FS3;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS3("HR2NewRegionFS3", "R^{2} (new), region FS3;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS3("HMRNewVsR2NewRegionFS3",
      "MR (new) vs. R^{2} (new), region FS3;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS4("HMRNewRegionFS4", "MR (new), region FS4;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS4("HR2NewRegionFS4", "R^{2} (new), region FS4;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS4("HMRNewVsR2NewRegionFS4",
      "MR (new) vs. R^{2} (new), region FS4;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS5("HMRNewRegionFS5", "MR (new), region FS5;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS5("HR2NewRegionFS5", "R^{2} (new), region FS5;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS5("HMRNewVsR2NewRegionFS5",
      "MR (new) vs. R^{2} (new), region FS5;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS6("HMRNewRegionFS6", "MR (new), region FS6;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS6("HR2NewRegionFS6", "R^{2} (new), region FS6;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS6("HMRNewVsR2NewRegionFS6",
      "MR (new) vs. R^{2} (new), region FS6;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS7("HMRNewRegionFS7", "MR (new), region FS7;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS7("HR2NewRegionFS7", "R^{2} (new), region FS7;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS7("HMRNewVsR2NewRegionFS7",
      "MR (new) vs. R^{2} (new), region FS7;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS8("HMRNewRegionFS8", "MR (new), region FS8;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS8("HR2NewRegionFS8", "R^{2} (new), region FS8;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS8("HMRNewVsR2NewRegionFS8",
      "MR (new) vs. R^{2} (new), region FS8;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS9("HMRNewRegionFS9", "MR (new), region FS9;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS9("HR2NewRegionFS9", "R^{2} (new), region FS9;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS9("HMRNewVsR2NewRegionFS9",
      "MR (new) vs. R^{2} (new), region FS9;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS10("HMRNewRegionFS10", "MR (new), region FS10;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS10("HR2NewRegionFS10", "R^{2} (new), region FS10;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS10("HMRNewVsR2NewRegionFS10",
      "MR (new) vs. R^{2} (new), region FS10;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS11("HMRNewRegionFS11", "MR (new), region FS11;MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS11("HR2NewRegionFS11", "R^{2} (new), region FS11;R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS11("HMRNewVsR2NewRegionFS11",
      "MR (new) vs. R^{2} (new), region FS11;MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH2D HMRNewVsR2NewGrid("HMRNewVsR2NewGrid", "MR (new) vs. R^{2} (new);MR (new);R^{2} (new)", 30, 0, 1500, 10, 0, 0.5);
   TH1D HCountRegions("HCountRegions", "Count in side-band regions B1-B3, FS1-FS11", 14, 0.5, 14.5);

   HCountRegions.GetXaxis()->SetBinLabel(1, "B1");
   HCountRegions.GetXaxis()->SetBinLabel(2, "B2");
   HCountRegions.GetXaxis()->SetBinLabel(3, "B3");
   HCountRegions.GetXaxis()->SetBinLabel(4, "FS1");
   HCountRegions.GetXaxis()->SetBinLabel(5, "FS2");
   HCountRegions.GetXaxis()->SetBinLabel(6, "FS3");
   HCountRegions.GetXaxis()->SetBinLabel(7, "FS4");
   HCountRegions.GetXaxis()->SetBinLabel(8, "FS5");
   HCountRegions.GetXaxis()->SetBinLabel(9, "FS6");
   HCountRegions.GetXaxis()->SetBinLabel(10, "FS7");
   HCountRegions.GetXaxis()->SetBinLabel(11, "FS8");
   HCountRegions.GetXaxis()->SetBinLabel(12, "FS9");
   HCountRegions.GetXaxis()->SetBinLabel(13, "FS10");
   HCountRegions.GetXaxis()->SetBinLabel(14, "FS11");
   
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
   TH1D HMRNewRegionFS1_L("HMRNewRegionFS1_L", "MR (new), region FS1 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS1_L("HR2NewRegionFS1_L", "R^{2} (new), region FS1 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS1_L("HMRNewVsR2NewRegionFS1_L",
      "MR (new) vs. R^{2} (new), region FS1 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS2_L("HMRNewRegionFS2_L", "MR (new), region FS2 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS2_L("HR2NewRegionFS2_L", "R^{2} (new), region FS2 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS2_L("HMRNewVsR2NewRegionFS2_L",
      "MR (new) vs. R^{2} (new), region FS2 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS3_L("HMRNewRegionFS3_L", "MR (new), region FS3 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS3_L("HR2NewRegionFS3_L", "R^{2} (new), region FS3 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS3_L("HMRNewVsR2NewRegionFS3_L",
      "MR (new) vs. R^{2} (new), region FS3 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS4_L("HMRNewRegionFS4_L", "MR (new), region FS4 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS4_L("HR2NewRegionFS4_L", "R^{2} (new), region FS4 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS4_L("HMRNewVsR2NewRegionFS4_L",
      "MR (new) vs. R^{2} (new), region FS4 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS5_L("HMRNewRegionFS5_L", "MR (new), region FS5 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS5_L("HR2NewRegionFS5_L", "R^{2} (new), region FS5 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS5_L("HMRNewVsR2NewRegionFS5_L",
      "MR (new) vs. R^{2} (new), region FS5 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS6_L("HMRNewRegionFS6_L", "MR (new), region FS6 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS6_L("HR2NewRegionFS6_L", "R^{2} (new), region FS6 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS6_L("HMRNewVsR2NewRegionFS6_L",
      "MR (new) vs. R^{2} (new), region FS6 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS7_L("HMRNewRegionFS7_L", "MR (new), region FS7 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS7_L("HR2NewRegionFS7_L", "R^{2} (new), region FS7 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS7_L("HMRNewVsR2NewRegionFS7_L",
      "MR (new) vs. R^{2} (new), region FS7 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS8_L("HMRNewRegionFS8_L", "MR (new), region FS8 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS8_L("HR2NewRegionFS8_L", "R^{2} (new), region FS8 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS8_L("HMRNewVsR2NewRegionFS8_L",
      "MR (new) vs. R^{2} (new), region FS8 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS9_L("HMRNewRegionFS9_L", "MR (new), region FS9 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS9_L("HR2NewRegionFS9_L", "R^{2} (new), region FS9 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS9_L("HMRNewVsR2NewRegionFS9_L",
      "MR (new) vs. R^{2} (new), region FS9 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS10_L("HMRNewRegionFS10_L", "MR (new), region FS10 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS10_L("HR2NewRegionFS10_L", "R^{2} (new), region FS10 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS10_L("HMRNewVsR2NewRegionFS10_L",
      "MR (new) vs. R^{2} (new), region FS10 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HMRNewRegionFS11_L("HMRNewRegionFS11_L", "MR (new), region FS11 (single loose);MR (new)", 60, 0, 1500);
   TH1D HR2NewRegionFS11_L("HR2NewRegionFS11_L", "R^{2} (new), region FS11 (single loose);R^{2} (new)", 50, 0, 0.5);
   TH2D HMRNewVsR2NewRegionFS11_L("HMRNewVsR2NewRegionFS11_L",
      "MR (new) vs. R^{2} (new), region FS11 (single loose);MR (new);R^{2} (new)", 60, 0, 1500, 50, 0, 0.5);
   TH1D HCountRegions_L("HCountRegions_L", "Count in sideband regions B1-B3, FS1-FS11 (single loose)", 14, 0.5, 14.5);

   HCountRegions_L.GetXaxis()->SetBinLabel(1, "B1");
   HCountRegions_L.GetXaxis()->SetBinLabel(2, "B2");
   HCountRegions_L.GetXaxis()->SetBinLabel(3, "B3");
   HCountRegions_L.GetXaxis()->SetBinLabel(4, "FS1");
   HCountRegions_L.GetXaxis()->SetBinLabel(5, "FS2");
   HCountRegions_L.GetXaxis()->SetBinLabel(6, "FS3");
   HCountRegions_L.GetXaxis()->SetBinLabel(7, "FS4");
   HCountRegions_L.GetXaxis()->SetBinLabel(8, "FS5");
   HCountRegions_L.GetXaxis()->SetBinLabel(9, "FS6");
   HCountRegions_L.GetXaxis()->SetBinLabel(10, "FS7");
   HCountRegions_L.GetXaxis()->SetBinLabel(11, "FS8");
   HCountRegions_L.GetXaxis()->SetBinLabel(12, "FS9");
   HCountRegions_L.GetXaxis()->SetBinLabel(13, "FS10");
   HCountRegions_L.GetXaxis()->SetBinLabel(14, "FS11");

   /*
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
   */
   
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
      if(M.GoodMuonCount != 1)   // want single muon
         continue;
      if(M.Muon1PT < 20)
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
      bool InUpperFull = false;
      bool InRightFull = false;
      bool InB1 = false;
      bool InB2 = false;
      bool InB3 = false;
      bool InFS1 = false;
      bool InFS2 = false;
      bool InFS3 = false;
      bool InFS4 = false;
      bool InFS5 = false;
      bool InFS6 = false;
      bool InFS7 = false;
      bool InFS8 = false;
      bool InFS9 = false;
      bool InFS10 = false;
      bool InFS11 = false;

      if(MRNew > 500 && R2New > 0.1 && R2New < 0.5)
         InFull = true;
      if(MRNew > 600 && R2New > 0.07 && R2New < 0.5)
         InFull = true;
      if(MRNew > 500 && R2New > 0.1 && R2New < 0.5)
         InUpperFull = true;
      if(MRNew > 600 && R2New > 0.07 && R2New < 0.5)
         InRightFull = true;
      if(MRNew > 500 && MRNew <= 600 && R2New > 0.10 && R2New <= 0.14)
         InB1 = true;
      if(MRNew > 600 && MRNew <= 700 && R2New > 0.10 && R2New <= 0.14)
         InB2 = true;
      if(MRNew > 600 && MRNew <= 700 && R2New > 0.07 && R2New <= 0.10)
         InB3 = true;

      if(MRNew > 500 && MRNew <= 600 && R2New > 0.30 && R2New <= 0.50)
         InFS1 = true;
      if(MRNew > 500 && MRNew <= 600 && R2New > 0.20 && R2New <= 0.30)
         InFS2 = true;
      if(MRNew > 500 && MRNew <= 600 && R2New > 0.14 && R2New <= 0.20)
         InFS3 = true;
      if(MRNew > 600 && MRNew <= 700 && R2New > 0.30 && R2New <= 0.50)
         InFS4 = true;
      if(MRNew > 600 && MRNew <= 700 && R2New > 0.20 && R2New <= 0.30)
         InFS5 = true;
      if(MRNew > 600 && MRNew <= 700 && R2New > 0.14 && R2New <= 0.20)
         InFS6 = true;
      if(MRNew > 700 && MRNew <= 3500 && R2New > 0.30 && R2New <= 0.50)
         InFS7 = true;
      if(MRNew > 700 && MRNew <= 3500 && R2New > 0.20 && R2New <= 0.30)
         InFS8 = true;
      if(MRNew > 700 && MRNew <= 3500 && R2New > 0.14 && R2New <= 0.20)
         InFS9 = true;
      if(MRNew > 700 && MRNew <= 3500 && R2New > 0.10 && R2New <= 0.14)
         InFS10 = true;
      if(MRNew > 700 && MRNew <= 3500 && R2New > 0.07 && R2New <= 0.10)
         InFS11 = true;

      if(LooseTagCount >= 0)
      {
         HMRNewVsR2NewGrid.Fill(MRNew, R2New, WPU * Factor);
         if(InFull == true)
         {
            HMRNewFullRegion.Fill(MRNew, WPU * Factor);
            HR2NewFullRegion.Fill(R2New, WPU * Factor);
         }
         if(InUpperFull == true)
         {
            HMRNewUpperFullRegion.Fill(MRNew, WPU * Factor);
            HR2NewUpperFullRegion.Fill(R2New, WPU * Factor);
         }
         if(InRightFull == true)
         {
            HMRNewRightFullRegion.Fill(MRNew, WPU * Factor);
            HR2NewRightFullRegion.Fill(R2New, WPU * Factor);
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
         if(InFS1 == true)
         {
            HMRNewRegionFS1.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS1.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS1.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(4, WPU * Factor);
         }
         if(InFS2 == true)
         {
            HMRNewRegionFS2.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS2.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS2.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(5, WPU * Factor);
         }
         if(InFS3 == true)
         {
            HMRNewRegionFS3.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS3.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS3.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(6, WPU * Factor);
         }
         if(InFS4 == true)
         {
            HMRNewRegionFS4.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS4.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS4.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(7, WPU * Factor);
         }
         if(InFS5 == true)
         {
            HMRNewRegionFS5.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS5.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS5.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(8, WPU * Factor);
         }
         if(InFS6 == true)
         {
            HMRNewRegionFS6.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS6.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS6.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(9, WPU * Factor);
         }
         if(InFS7 == true)
         {
            HMRNewRegionFS7.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS7.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS7.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(10, WPU * Factor);
         }
         if(InFS8 == true)
         {
            HMRNewRegionFS8.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS8.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS8.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(11, WPU * Factor);
         }
         if(InFS9 == true)
         {
            HMRNewRegionFS9.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS9.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS9.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(12, WPU * Factor);
         }
         if(InFS10 == true)
         {
            HMRNewRegionFS10.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS10.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS10.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(13, WPU * Factor);
         }
         if(InFS11 == true)
         {
            HMRNewRegionFS11.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS11.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS11.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions.Fill(14, WPU * Factor);
         }
      }
      /*
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
         if(InFS1 == true)
         {
            HMRNewRegionFS1_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS1_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS1_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(4, WPU * Factor);
         }
         if(InFS2 == true)
         {
            HMRNewRegionFS2_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS2_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS2_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(5, WPU * Factor);
         }
         if(InFS3 == true)
         {
            HMRNewRegionFS3_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS3_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS3_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(6, WPU * Factor);
         }
         if(InFS4 == true)
         {
            HMRNewRegionFS4_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS4_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS4_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(7, WPU * Factor);
         }
         if(InFS5 == true)
         {
            HMRNewRegionFS5_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS5_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS5_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(8, WPU * Factor);
         }
         if(InFS6 == true)
         {
            HMRNewRegionFS6_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS6_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS6_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(9, WPU * Factor);
         }
         if(InFS7 == true)
         {
            HMRNewRegionFS7_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS7_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS7_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(10, WPU * Factor);
         }
         if(InFS8 == true)
         {
            HMRNewRegionFS8_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS8_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS8_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(11, WPU * Factor);
         }
         if(InFS9 == true)
         {
            HMRNewRegionFS9_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS9_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS9_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(12, WPU * Factor);
         }
         if(InFS10 == true)
         {
            HMRNewRegionFS10_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS10_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS10_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(13, WPU * Factor);
         }
         if(InFS11 == true)
         {
            HMRNewRegionFS11_L.Fill(MRNew, WPU * Factor);
            HR2NewRegionFS11_L.Fill(R2New, WPU * Factor);
            HMRNewVsR2NewRegionFS11_L.Fill(MRNew, R2New, WPU * Factor);
            HCountRegions_L.Fill(14, WPU * Factor);
         }
      }
      */

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
   HMRNewUpperFullRegion.Write();
   HR2NewUpperFullRegion.Write();
   HMRNewRightFullRegion.Write();
   HR2NewRightFullRegion.Write();
   HMRNewRegionB1.Write();
   HR2NewRegionB1.Write();
   HMRNewVsR2NewRegionB1.Write();
   HMRNewRegionB2.Write();
   HR2NewRegionB2.Write();
   HMRNewVsR2NewRegionB2.Write();
   HMRNewRegionB3.Write();
   HR2NewRegionB3.Write();
   HMRNewVsR2NewRegionB3.Write();
   HMRNewRegionFS1.Write();
   HR2NewRegionFS1.Write();
   HMRNewVsR2NewRegionFS1.Write();
   HMRNewRegionFS2.Write();
   HR2NewRegionFS2.Write();
   HMRNewVsR2NewRegionFS2.Write();
   HMRNewRegionFS3.Write();
   HR2NewRegionFS3.Write();
   HMRNewVsR2NewRegionFS3.Write();
   HMRNewRegionFS4.Write();
   HR2NewRegionFS4.Write();
   HMRNewVsR2NewRegionFS4.Write();
   HMRNewRegionFS5.Write();
   HR2NewRegionFS5.Write();
   HMRNewVsR2NewRegionFS5.Write();
   HMRNewRegionFS6.Write();
   HR2NewRegionFS6.Write();
   HMRNewVsR2NewRegionFS6.Write();
   HMRNewRegionFS7.Write();
   HR2NewRegionFS7.Write();
   HMRNewVsR2NewRegionFS7.Write();
   HMRNewRegionFS8.Write();
   HR2NewRegionFS8.Write();
   HMRNewVsR2NewRegionFS8.Write();
   HMRNewRegionFS9.Write();
   HR2NewRegionFS9.Write();
   HMRNewVsR2NewRegionFS9.Write();
   HMRNewRegionFS10.Write();
   HR2NewRegionFS10.Write();
   HMRNewVsR2NewRegionFS10.Write();
   HMRNewRegionFS11.Write();
   HR2NewRegionFS11.Write();
   HMRNewVsR2NewRegionFS11.Write();
   HMRNewVsR2NewGrid.Write();
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
   HMRNewRegionFS1_L.Write();
   HR2NewRegionFS1_L.Write();
   HMRNewVsR2NewRegionFS1_L.Write();
   HMRNewRegionFS2_L.Write();
   HR2NewRegionFS2_L.Write();
   HMRNewVsR2NewRegionFS2_L.Write();
   HMRNewRegionFS3_L.Write();
   HR2NewRegionFS3_L.Write();
   HMRNewVsR2NewRegionFS3_L.Write();
   HMRNewRegionFS4_L.Write();
   HR2NewRegionFS4_L.Write();
   HMRNewVsR2NewRegionFS4_L.Write();
   HMRNewRegionFS5_L.Write();
   HR2NewRegionFS5_L.Write();
   HMRNewVsR2NewRegionFS5_L.Write();
   HMRNewRegionFS6_L.Write();
   HR2NewRegionFS6_L.Write();
   HMRNewVsR2NewRegionFS6_L.Write();
   HMRNewRegionFS7_L.Write();
   HR2NewRegionFS7_L.Write();
   HMRNewVsR2NewRegionFS7_L.Write();
   HMRNewRegionFS8_L.Write();
   HR2NewRegionFS8_L.Write();
   HMRNewVsR2NewRegionFS8_L.Write();
   HMRNewRegionFS9_L.Write();
   HR2NewRegionFS9_L.Write();
   HMRNewVsR2NewRegionFS9_L.Write();
   HMRNewRegionFS10_L.Write();
   HR2NewRegionFS10_L.Write();
   HMRNewVsR2NewRegionFS10_L.Write();
   HMRNewRegionFS11_L.Write();
   HR2NewRegionFS11_L.Write();
   HMRNewVsR2NewRegionFS11_L.Write();
   HCountRegions_L.Write();

   OutputTree.Write();

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   PsFile.AddPlot(HWeight, "", true);
   PsFile.AddPlot(HNPU);
   PsFile.AddPlot(HNPUWeighted);
   PsFile.AddPlot(HMRNewFullRegion, "", true);
   PsFile.AddPlot(HR2NewFullRegion, "", true);
   PsFile.AddPlot(HMRNewUpperFullRegion, "", true);
   PsFile.AddPlot(HR2NewUpperFullRegion, "", true);
   PsFile.AddPlot(HMRNewRightFullRegion, "", true);
   PsFile.AddPlot(HR2NewRightFullRegion, "", true);
   PsFile.AddPlot(HMRNewRegionB1, "", true);
   PsFile.AddPlot(HR2NewRegionB1, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB1, "colz");
   PsFile.AddPlot(HMRNewRegionB2, "", true);
   PsFile.AddPlot(HR2NewRegionB2, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB2, "colz");
   PsFile.AddPlot(HMRNewRegionB3, "", true);
   PsFile.AddPlot(HR2NewRegionB3, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionB3, "colz");
   PsFile.AddPlot(HMRNewRegionFS1, "", true);
   PsFile.AddPlot(HR2NewRegionFS1, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS1, "colz");
   PsFile.AddPlot(HMRNewRegionFS2, "", true);
   PsFile.AddPlot(HR2NewRegionFS2, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS2, "colz");
   PsFile.AddPlot(HMRNewRegionFS3, "", true);
   PsFile.AddPlot(HR2NewRegionFS3, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS3, "colz");
   PsFile.AddPlot(HMRNewRegionFS4, "", true);
   PsFile.AddPlot(HR2NewRegionFS4, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS4, "colz");
   PsFile.AddPlot(HMRNewRegionFS5, "", true);
   PsFile.AddPlot(HR2NewRegionFS5, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS5, "colz");
   PsFile.AddPlot(HMRNewRegionFS6, "", true);
   PsFile.AddPlot(HR2NewRegionFS6, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS6, "colz");
   PsFile.AddPlot(HMRNewRegionFS7, "", true);
   PsFile.AddPlot(HR2NewRegionFS7, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS7, "colz");
   PsFile.AddPlot(HMRNewRegionFS8, "", true);
   PsFile.AddPlot(HR2NewRegionFS8, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS8, "colz");
   PsFile.AddPlot(HMRNewRegionFS9, "", true);
   PsFile.AddPlot(HR2NewRegionFS9, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS9, "colz");
   PsFile.AddPlot(HMRNewRegionFS10, "", true);
   PsFile.AddPlot(HR2NewRegionFS10, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS10, "colz");
   PsFile.AddPlot(HMRNewRegionFS11, "", true);
   PsFile.AddPlot(HR2NewRegionFS11, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS11, "colz");
   PsFile.AddPlot(HMRNewVsR2NewGrid, "colz");
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
   PsFile.AddPlot(HMRNewRegionFS1_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS1_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS1_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS2_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS2_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS2_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS3_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS3_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS3_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS4_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS4_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS4_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS5_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS5_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS5_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS6_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS6_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS6_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS7_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS7_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS7_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS8_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS8_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS8_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS9_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS9_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS9_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS10_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS10_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS10_L, "colz");
   PsFile.AddPlot(HMRNewRegionFS11_L, "", true);
   PsFile.AddPlot(HR2NewRegionFS11_L, "", true);
   PsFile.AddPlot(HMRNewVsR2NewRegionFS11_L, "colz");
   PsFile.AddPlot(HCountRegions_L, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




