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

   ReadSample("Samples/MuEGMay10ReRecov1_All.root", "DataPlotsReReco", -1, 191);
   ReadSample("Samples/MuEGRun2011Av4_All.root", "DataPlotsPrompt", -1, 510);
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
   M.InitializeWeight("Samples/BookKeeping/7222ReRun_MuEGRun2011Av4.PU.root");

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
   TH1D HMRNew("HMRNew", "MR (new) from Calo system;MR (new) (GeV/c^2)", 50, 0, 1000);
   TH1D HR2New("HR2New", "R^{2} (new) from Calo system;R^{2} (new)", 50, 0, 1);
   TH1D HMRNew_RNew02("HMRNew_RNew02",
      "MR (new) from Calo system (R (new) > 0.2);MR (new) (GeV/c^2)", 50, 0, 1000);
   TH1D HMRNew_RNew03("HMRNew_RNew03",
      "MR (new) from Calo system (R (new) > 0.3);MR (new) (GeV/c^2)", 50, 0, 1000);
   TH1D HMRNew_RNew04("HMRNew_RNew04",
      "MR (new) from Calo system (R (new) > 0.4);MR (new) (GeV/c^2)", 50, 0, 1000);
   TH1D HMRNew_RNew05("HMRNew_RNew05",
      "MR (new) from Calo system (R (new) > 0.5);MR (new) (GeV/c^2)", 50, 0, 1000);
   TH1D HMRNew_RNew06("HMRNew_RNew06",
      "MR (new) from Calo system (R (new) > 0.6);MR (new) (GeV/c^2)", 50, 0, 1000);
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

      int BTagCount = 0;
      for(int i = 0; i < M.CaloJetCount && i < 100; i++)
      {
         if(M.CaloJetPT[i] < 30)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetTCHETag[i] < 1.7)
            continue;

         BTagCount = BTagCount + 1;
      }
      if(BTagCount < 2)
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
      HElectron1PT.Fill(M.Electron1PT, Factor * WPU);

      if(M.CaloJetCount > 0)
         HLeadingCaloJetPT.Fill(M.CaloJetPT[0], Factor * WPU);
      if(M.CaloJetCount > 1)
         HSubLeadingCaloJetPT.Fill(M.CaloJetPT[1], Factor * WPU);

      double MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
      double RNew = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      double R2New = RNew * RNew;

      HMRNew.Fill(MRNew, Factor * WPU);
      HR2New.Fill(R2New, Factor * WPU);

      if(RNew > 0.2)
         HMRNew_RNew02.Fill(MRNew, Factor * WPU);
      if(RNew > 0.3)
         HMRNew_RNew03.Fill(MRNew, Factor * WPU);
      if(RNew > 0.4)
         HMRNew_RNew04.Fill(MRNew, Factor * WPU);
      if(RNew > 0.5)
         HMRNew_RNew05.Fill(MRNew, Factor * WPU);
      if(RNew > 0.6)
         HMRNew_RNew06.Fill(MRNew, Factor * WPU);

      TreeMR = MRNew;
      TreeR = RNew;
      TreeRsq = R2New;
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
   HMRNew.Write();
   HR2New.Write();
   HMRNew_RNew02.Write();
   HMRNew_RNew03.Write();
   HMRNew_RNew04.Write();
   HMRNew_RNew05.Write();
   HMRNew_RNew06.Write();
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
   PsFile.AddPlot(HMRNew, "", true);
   PsFile.AddPlot(HR2New, "", true);
   PsFile.AddPlot(HMRNew_RNew02, "", true);
   PsFile.AddPlot(HMRNew_RNew03, "", true);
   PsFile.AddPlot(HMRNew_RNew04, "", true);
   PsFile.AddPlot(HMRNew_RNew05, "", true);
   PsFile.AddPlot(HMRNew_RNew06, "", true);
   PsFile.AddPlot(HPFMET, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




