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
#include "ReadLQ3Tree.h"
#include "TauHelperFunctions2.h"

int main();
void ReadSample(string Input, string OutputBase, double CrossSection, double Luminosity);

int main()
{
   SetStyle();

   ReadSample("DataSamples/MuEGMay10ReRecov1_All.root", "DataPlotsReReco", -1, 191);
   ReadSample("DataSamples/MuEGRun2011Av4_All.root", "DataPlotsPrompt", -1, 510);
   ReadSample("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar", 165, 701);   // NNLL
   ReadSample("Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root", "W", 31314, 701);   // NNLO
   ReadSample("Samples/VVJetsTo4L_TuneD6T_7TeV-madgraph-tauola_All.root", "VV", 4.8, 701);   // Production
   ReadSample("Samples/PhotonVJets_7TeV-madgraph_All.root", "GammaVJet", 173, 701);   // Production
   ReadSample("Samples/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root", "DY50", 3048, 701);   // NNLO
   ReadSample("Samples/ZinvisibleJets_7TeV-madgraph_All.root", "Znunu", 3048 * 6, 701);   // guessed
   ReadSample("Samples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root", "QCD1", 30000000, 701);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root", "QCD2", 7000000, 701);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root", "QCD3", 171000, 701);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root", "QCD4", 5200, 701);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root", "QCD5", 83, 701);   // production
}

void ReadSample(string Input, string OutputBase, double CrossSection, double Luminosity)
{
   cout << "Start processing sample " << Input << endl;

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(Input.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("DataSamples/BookKeeping/7174PUTriggersAdded_ElectronHadRun2011Av4.PU.root");

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
      cout << "ProcessedEvents with weight = " << WeightedEvents << endl;
   cout << "Sigma * L / Count = " << CrossSection * Luminosity / NumberOfProcessedEvents << endl;

   Tree.SetBranchStatus("PFJet*", false);
   Tree.SetBranchStatus("CaloJetCSVTag", false);
   Tree.SetBranchStatus("CaloJetCSVMTag", false);
   Tree.SetBranchStatus("CaloJetTCHPTag", false);

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

   TH1D HWeight("HWeight", "Weight of events from pileups only", 100, 0, 3);
   TH1D HNPU("HNPU", "Closure check of number of added PU, not weighted", 25, 0, 25);
   TH1D HNPUWeighted("HNPUWeighted", "Closure check of number of added PU, weighted", 25, 0, 25);
   TH1D HMuon1PT("HMuon1PT", "Leading muon PT;PT (GeV/c)", 50, 0, 200);
   TH1D HElectron1PT("HElectron1PT", "Leading electron PT;PT (GeV/c)", 50, 0, 200);
   TH1D HLeadingCaloJetPT("HLeadingCaloJetPT", "Leading Calo jet pt;PT (GeV/c)", 50, 0, 500);
   TH1D HSubLeadingCaloJetPT("HSubLeadingCaloJetPT", "Sub-leading Calo jet pt;PT (GeV/c)", 50, 0, 500);
   TH1D HCaloJetMR("HCaloJetMR", "MR from Calo system;MR (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetR("HCaloJetR", "R from Calo system;R", 50, 0, 1);
   TH1D HCaloJetMRStar("HCaloJetMRStar", "MRStar from Calo system;MRStar (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetGammaMRStar("HCaloJetGammaMRStar", "MR*** from Calo system;MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetRStar("HCaloJetRStar", "RStar from Calo system;RStar", 50, 0, 1);
   TH1D HCaloJetGammaMRStar_RStar02("HCaloJetGammaMRStar_RStar02",
      "MR*** from Calo system (RStar > 0.2);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetGammaMRStar_RStar03("HCaloJetGammaMRStar_RStar03",
      "MR*** from Calo system (RStar > 0.3);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetGammaMRStar_RStar04("HCaloJetGammaMRStar_RStar04",
      "MR*** from Calo system (RStar > 0.4);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetGammaMRStar_RStar05("HCaloJetGammaMRStar_RStar05",
      "MR*** from Calo system (RStar > 0.5);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetGammaMRStar_RStar06("HCaloJetGammaMRStar_RStar06",
      "MR*** from Calo system (RStar > 0.6);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HPFMET("HPFMET", "PF MET distribution;MET (GeV)", 50, 0, 200);

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

      if(M.GoodMuonCountTight < 1)   // tight muon, 10 GeV
         continue;
      if(M.Muon1PT < 10)
         continue;

      if(M.GoodElectronCount80 < 1)   // tight electron, 20 GeV
         continue;
      if(M.Electron1PT < 20)
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

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      HPFMET.Fill(PFMET.GetPT(), Factor * WPU);

      HMuon1PT.Fill(M.Muon1PT, Factor * WPU);

      if(M.CaloJetCount > 0)
         HLeadingCaloJetPT.Fill(M.CaloJetPT[0], Factor * WPU);
      if(M.CaloJetCount > 1)
         HSubLeadingCaloJetPT.Fill(M.CaloJetPT[1], Factor * WPU);

      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double R = GetR(Hemispheres[0], Hemispheres[1], PFMET);
      double MRStar = GetMRStar(Hemispheres[0], Hemispheres[1]);
      double GammaRStar = GetGammaRStar(Hemispheres[0], Hemispheres[1]);
      double RStar = GetRStar(Hemispheres[0], Hemispheres[1], PFMET);

      HCaloJetMR.Fill(MR, Factor * WPU);
      HCaloJetR.Fill(R, Factor * WPU);
      HCaloJetMRStar.Fill(MRStar, Factor * WPU);
      HCaloJetGammaMRStar.Fill(MRStar * GammaRStar, Factor * WPU);
      HCaloJetRStar.Fill(RStar, Factor * WPU);

      if(RStar > 0.2)
         HCaloJetGammaMRStar_RStar02.Fill(MRStar * GammaRStar, Factor * WPU);
      if(RStar > 0.3)
         HCaloJetGammaMRStar_RStar03.Fill(MRStar * GammaRStar, Factor * WPU);
      if(RStar > 0.4)
         HCaloJetGammaMRStar_RStar04.Fill(MRStar * GammaRStar, Factor * WPU);
      if(RStar > 0.5)
         HCaloJetGammaMRStar_RStar05.Fill(MRStar * GammaRStar, Factor * WPU);
      if(RStar > 0.6)
         HCaloJetGammaMRStar_RStar06.Fill(MRStar * GammaRStar, Factor * WPU);

      TreeMR = MRStar * GammaRStar;
      TreeR = RStar;
      TreeRsq = RStar * RStar;
      TreeFactor = Factor * WPU;
      OutputTree.Fill();
   }

   HWeight.Write();
   HNPU.Write();
   HNPUWeighted.Write();
   HMuon1PT.Write();
   HElectron1PT.Write();
   HLeadingCaloJetPT.Write();
   HSubLeadingCaloJetPT.Write();
   HCaloJetMR.Write();
   HCaloJetR.Write();
   HCaloJetMRStar.Write();
   HCaloJetGammaMRStar.Write();
   HCaloJetRStar.Write();
   HCaloJetGammaMRStar_RStar02.Write();
   HCaloJetGammaMRStar_RStar03.Write();
   HCaloJetGammaMRStar_RStar04.Write();
   HCaloJetGammaMRStar_RStar05.Write();
   HCaloJetGammaMRStar_RStar06.Write();
   HPFMET.Write();

   OutputTree.Write();

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   PsFile.AddPlot(HWeight);
   PsFile.AddPlot(HNPU);
   PsFile.AddPlot(HNPUWeighted);

   PsFile.AddPlot(HMuon1PT, "", true);
   PsFile.AddPlot(HElectron1PT, "", true);
   PsFile.AddPlot(HLeadingCaloJetPT, "", true);
   PsFile.AddPlot(HSubLeadingCaloJetPT, "", true);
   PsFile.AddPlot(HCaloJetMR, "", true);
   PsFile.AddPlot(HCaloJetR, "", true);
   PsFile.AddPlot(HCaloJetMRStar, "", true);
   PsFile.AddPlot(HCaloJetGammaMRStar, "", true);
   PsFile.AddPlot(HCaloJetRStar, "", true);
   PsFile.AddPlot(HCaloJetGammaMRStar_RStar02, "", true);
   PsFile.AddPlot(HCaloJetGammaMRStar_RStar03, "", true);
   PsFile.AddPlot(HCaloJetGammaMRStar_RStar04, "", true);
   PsFile.AddPlot(HCaloJetGammaMRStar_RStar05, "", true);
   PsFile.AddPlot(HCaloJetGammaMRStar_RStar06, "", true);
   PsFile.AddPlot(HPFMET, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




