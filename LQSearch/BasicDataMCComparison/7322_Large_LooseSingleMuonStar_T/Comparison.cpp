#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
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

   ReadSample("DataSamples/MuHadRun2011Av4_Aug05v1_Run2011AV6_All.root", "DataPlots", -1, 1769.617);
   ReadSample("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar", 165, 1769.517);   // NNLL
   ReadSample("Samples/AllWJetsToLNu_Added.root", "W", 31314, 1769.517);   // NNLO
   ReadSample("Samples/VVJetsTo4L_TuneD6T_7TeV-madgraph-tauola_All.root", "VV", 4.8, 1769.517);   // Production
   ReadSample("Samples/PhotonVJets_7TeV-madgraph_All.root", "GammaVJet", 173, 1769.517);   // Production
   ReadSample("Samples/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root", "DY50", 3048, 1769.517);   // NNLO
   ReadSample("Samples/ZinvisibleJets_7TeV-madgraph_All.root", "Znunu", 3048 * 6, 1769.517);   // guessed
   ReadSample("Samples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root", "QCD1", 30000000, 1769.517);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root", "QCD2", 7000000, 1769.517);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root", "QCD3", 171000, 1769.517);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root", "QCD4", 5200, 1769.517);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root", "QCD5", 83, 1769.517);   // production
}

void ReadSample(string Input, string OutputBase, double CrossSection, double Luminosity)
{
   cout << "Start processing sample " << Input << endl;

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(Input.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("DataSamples/BookKeeping/Pileup_2011_to_173692_LPLumiScale_68mb.root");

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

   map<pair<int, long long>, int> NoiseEvents;
   if(CrossSection < 0)
   {
      ifstream in("DataSamples/ExcludedEvents/AllEvents");
      while(in)
      {
         int Run = 0;
         long long Event = 0;
         in >> Run >> Event;
         if(Run <= 0 || Event <= 0)
            continue;
         NoiseEvents.insert(pair<pair<int, long long>, int>(pair<int, long long>(Run, Event), 1));
      }
      in.close();
   }

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
   TH1D HLeadingCaloJetPT("HLeadingCaloJetPT", "Leading Calo jet pt;PT (GeV/c)", 50, 0, 1000);
   TH1D HSubLeadingCaloJetPT("HSubLeadingCaloJetPT", "Sub-leading Calo jet pt;PT (GeV/c)", 50, 0, 1000);
   TH1D HMRNew("HMRNew", "MR (new);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HR2New("HR2New", "R^{2} (new);R^{2} (new)", 50, 0, 1.0);
   TH1D HMRNew_RNew02("HMRNew_RNew02",
      "MR (new) (R (new) > 0.2);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HMRNew_RNew03("HMRNew_RNew03",
      "MR (new) (R (new) > 0.3);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HMRNew_RNew04("HMRNew_RNew04",
      "MR (new) (R (new) > 0.4);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HMRNew_RNew05("HMRNew_RNew05",
      "MR (new) (R (new) > 0.5);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HMRNew_RNew06("HMRNew_RNew06",
      "MR (new) (R (new) > 0.6);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HMRNew_R2New020("HMRNew_R2New020",
      "MR (new) (R^{2} (new) > 0.2);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HPFMET("HPFMET", "PF MET distribution;MET (GeV)", 50, 0, 500);
   TH1D HMegaJetDeltaPhi("HMegaJetDeltaPhi", "Delta phi of the two mega jets", 40, 0, 3.2);
   TH1D HMegaJetDeltaPhi_MRNew400_R2New016("HMegaJetDeltaPhi_MRNew400_R2New016",
      "Delta phi of the two mega jets, MR (new) > 400, R^{2} (new) > 0.16", 40, 0, 3.2);
   TH1D HMegaJetDeltaPhi_MRNew400_R2New025("HMegaJetDeltaPhi_MRNew400_R2New025",
      "Delta phi of the two mega jets, MR (new) > 400, R^{2} (new) > 0.25", 40, 0, 3.2);
   TH1D HMegaJetDeltaPhi_MRNew400_R2New050Up("HMegaJetDeltaPhi_MRNew400_R2New050Up",
      "Delta phi of the two mega jets, MR (new) > 400, R^{2} (new) > 0.50", 40, 0, 3.2);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 250000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      if(CrossSection < 0)
      {
         pair<int, long long> Index((int)(M.RunNumber + 0.0001), (long long)(M.EventNumber + 0.0001));
         if(NoiseEvents.find(Index) != NoiseEvents.end())
         {
            // cout << "Event " << M.RunNumber << " " << M.EventNumber << " rejected" << endl;
            continue;
         }
      }

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

      if(M.GoodMuonCount != 1 || (M.GoodMuonCount == 1 && M.Muon1PT < 20))
         continue;
      FourVector MuonP;
      MuonP.SetPtEtaPhi(M.Muon1PT, M.Muon1Eta, M.Muon1Phi);

      if(M.GoodElectronCount80 >= 1)
         continue;

      int BTagCount = 0;
      for(int i = 0; i < M.CaloJetCount && i < 100; i++)
         if(M.CaloJetPT[i] > 80 && fabs(M.CaloJetEta[i]) < 3 && M.CaloJetTCHETag[i] > 10.2)
            BTagCount = BTagCount + 1;
      if(BTagCount < 1)
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

      PFMET = PFMET + MuonP;

      double MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
      double RNew = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      double R2New = RNew * RNew;

      if(R2New > 0.09 && MRNew > 300)
      {
         if(M.CaloJetCount > 0)
            HLeadingCaloJetPT.Fill(M.CaloJetPT[0], Factor * WPU);
         if(M.CaloJetCount > 1)
            HSubLeadingCaloJetPT.Fill(M.CaloJetPT[1], Factor * WPU);

         HMuon1PT.Fill(M.Muon1PT, Factor * WPU);

         HPFMET.Fill(PFMET.GetPT(), Factor * WPU);

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
         if(R2New > 0.2)
            HMRNew_R2New020.Fill(MRNew, Factor * WPU);

         double MegaJetDeltaPhi = fabs(GetDPhi(Hemispheres[0], Hemispheres[1]));
         HMegaJetDeltaPhi.Fill(MegaJetDeltaPhi, Factor * WPU);
         if(MRNew > 400 && R2New > 0.16 && R2New < 0.5)
            HMegaJetDeltaPhi_MRNew400_R2New016.Fill(MegaJetDeltaPhi, Factor * WPU);
         if(MRNew > 400 && R2New > 0.25 && R2New < 0.5)
            HMegaJetDeltaPhi_MRNew400_R2New025.Fill(MegaJetDeltaPhi, Factor * WPU);
         if(MRNew > 400 && R2New > 0.5)
            HMegaJetDeltaPhi_MRNew400_R2New050Up.Fill(MegaJetDeltaPhi, Factor * WPU);
      }

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
   HMRNew_R2New020.Write();
   HPFMET.Write();
   HMegaJetDeltaPhi.Write();
   HMegaJetDeltaPhi_MRNew400_R2New016.Write();
   HMegaJetDeltaPhi_MRNew400_R2New025.Write();
   HMegaJetDeltaPhi_MRNew400_R2New050Up.Write();

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
   PsFile.AddPlot(HMRNew_R2New020, "", true);
   PsFile.AddPlot(HPFMET, "", true);
   PsFile.AddPlot(HMegaJetDeltaPhi, "", true);
   PsFile.AddPlot(HMegaJetDeltaPhi_MRNew400_R2New016, "", true);
   PsFile.AddPlot(HMegaJetDeltaPhi_MRNew400_R2New025, "", true);
   PsFile.AddPlot(HMegaJetDeltaPhi_MRNew400_R2New050Up, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




