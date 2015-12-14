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

   ReadSample("DataSamples/HTRun2011Av4_All.root", "Data1Plots", -1, 863.339);
   ReadSample("DataSamples/HTRun2011A_05Aug2011v1_All.root", "Data2Plots", -1, 0);
   ReadSample("DataSamples/HTPromptRecoUpTo174084_Aug05Excluded.root", "Data3Plots", -1, 889.414);
   ReadSample("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar", 165, 1752.753);   // NNLL
   ReadSample("Samples/AllWJetsToLNu_Added.root", "W", 31314, 1752.753);   // NNLO
   ReadSample("Samples/VVJetsTo4L_TuneD6T_7TeV-madgraph-tauola_All.root", "VV", 4.8, 1752.753);   // Production
   ReadSample("Samples/PhotonVJets_7TeV-madgraph_All.root", "GammaVJet", 173, 1752.753);   // Production
   ReadSample("Samples/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root", "DY50", 3048, 1752.753);   // NNLO
   ReadSample("Samples/ZinvisibleJets_7TeV-madgraph_All.root", "Znunu", 3048 * 6, 1752.753);   // guessed
   ReadSample("Samples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root", "QCD1", 30000000, 1752.753);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root", "QCD2", 7000000, 1752.753);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root", "QCD3", 171000, 1752.753);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root", "QCD4", 5200, 1752.753);   // production
   ReadSample("Samples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root", "QCD5", 83, 1752.753);   // production
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
   TH1D HMRNew("HMRNew", "MR (new);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HR2New("HR2New", "R^{2} (new);R^{2} (new)", 50, 0, 0.5);
   TH1D HMRNew_RNew02("HMRNew_RNew02",
      "MR (new) (R (new) > 0.2, R^{2} (new) < 0.5);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HMRNew_RNew03("HMRNew_RNew03",
      "MR (new) (R (new) > 0.3, R^{2} (new) < 0.5);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HMRNew_RNew04("HMRNew_RNew04",
      "MR (new) (R (new) > 0.4, R^{2} (new) < 0.5);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HMRNew_RNew05("HMRNew_RNew05",
      "MR (new) (R (new) > 0.5, R^{2} (new) < 0.5);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HMRNew_RNew06("HMRNew_RNew06",
      "MR (new) (R (new) > 0.6, R^{2} (new) < 0.5);MR (new) (GeV/c^2)", 50, 0, 1500);
   TH1D HPFMET("HPFMET", "PF MET distribution;MET (GeV)", 50, 0, 200);
   TH1D HMegaJetDeltaPhi("HMegaJetDeltaPhi", "Delta phi of the two mega jets", 40, 0, 3.2);
   TH1D HMegaJetDeltaPhi_MRNew400_R2New016("HMegaJetDeltaPhi_MRNew400_R2New016",
      "Delta phi of the two mega jets, MR (new) > 400, R^{2} (new) > 0.16", 40, 0, 3.2);
   TH1D HMegaJetDeltaPhi_MRNew400_R2New025("HMegaJetDeltaPhi_MRNew400_R2New025",
      "Delta phi of the two mega jets, MR (new) > 400, R^{2} (new) > 0.25", 40, 0, 3.2);

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

      int CaloJetCount60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            CaloJetCount60 = CaloJetCount60 + 1;
      if(CaloJetCount60 < 2)
         continue;

      int JetPassBTagLoose = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetTCHETag[i] > 1.7 && M.CaloJetPT[i] > 80 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            JetPassBTagLoose = JetPassBTagLoose + 1;
      if(JetPassBTagLoose < 2)
         continue;

      if(M.GoodMuonCount >= 1)
         continue;
      if(M.GoodElectronCount >= 1)
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
      
      double MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
      double RNew = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      double R2New = RNew * RNew;

      if(MRNew > 300 && R2New > 0.09)
      {
         HPFMET.Fill(PFMET.GetPT(), Factor * WPU);

         // HMuon1PT.Fill(M.Muon1PT, Factor * WPU);

         if(M.CaloJetCount > 0)
            HLeadingCaloJetPT.Fill(M.CaloJetPT[0], Factor * WPU);
         if(M.CaloJetCount > 1)
            HSubLeadingCaloJetPT.Fill(M.CaloJetPT[1], Factor * WPU);

         HMRNew.Fill(MRNew, Factor * WPU);
         HR2New.Fill(R2New, Factor * WPU);

         if(RNew > 0.2 && R2New < 0.5)
            HMRNew_RNew02.Fill(MRNew, Factor * WPU);
         if(RNew > 0.3 && R2New < 0.5)
            HMRNew_RNew03.Fill(MRNew, Factor * WPU);
         if(RNew > 0.4 && R2New < 0.5)
            HMRNew_RNew04.Fill(MRNew, Factor * WPU);
         if(RNew > 0.5 && R2New < 0.5)
            HMRNew_RNew05.Fill(MRNew, Factor * WPU);
         if(RNew > 0.6 && R2New < 0.5)
            HMRNew_RNew06.Fill(MRNew, Factor * WPU);

         double MegaJetDeltaPhi = fabs(GetDPhi(Hemispheres[0], Hemispheres[1]));
         HMegaJetDeltaPhi.Fill(MegaJetDeltaPhi);
         if(MRNew > 400 && R2New > 0.16 && R2New < 0.5)
            HMegaJetDeltaPhi_MRNew400_R2New016.Fill(MegaJetDeltaPhi);
         if(MRNew > 400 && R2New > 0.25 && R2New < 0.5)
            HMegaJetDeltaPhi_MRNew400_R2New025.Fill(MegaJetDeltaPhi);
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
   HPFMET.Write();
   HMegaJetDeltaPhi.Write();
   HMegaJetDeltaPhi_MRNew400_R2New016.Write();
   HMegaJetDeltaPhi_MRNew400_R2New025.Write();

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
   PsFile.AddPlot(HMegaJetDeltaPhi, "", true);
   PsFile.AddPlot(HMegaJetDeltaPhi_MRNew400_R2New016, "", true);
   PsFile.AddPlot(HMegaJetDeltaPhi_MRNew400_R2New025, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




