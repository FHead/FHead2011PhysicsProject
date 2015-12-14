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
   SetTDRStyle();

   ReadSample("Samples/LM1_SUSY_sftsht_7TeV-pythia6_All.root", "LM1", 4.888, 1000);   // pythia LO
   ReadSample("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar", 165, 1000);   // NNLL
   ReadSample("Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root", "W", 31314, 1000);   // NNLO
   ReadSample("Samples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root", "QCD_50", 30000000, 1000);
   ReadSample("Samples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root", "QCD_100", 7000000, 1000);
   ReadSample("Samples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root", "QCD_250", 171000, 1000);
   ReadSample("Samples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root", "QCD_500", 5200, 1000);
   ReadSample("Samples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root", "QCD_1000", 83, 1000);
}

void ReadSample(string Input, string OutputBase, double CrossSection, double Luminosity)
{
   cout << "t processing sample " << Input << endl;
   
   double NumberOfProcessedEvents = 0;
   TFile F(Input.c_str());
   NumberOfProcessedEvents = ((TH2D *)F.Get("HProcessedEvents"))->GetBinContent(1, 1);
   F.Close();

   double Factor = CrossSection * Luminosity / NumberOfProcessedEvents;
   if(CrossSection < 0)   // data!
      Factor = 1;

   cout << "ProcessedEvents = " << NumberOfProcessedEvents << endl;
   cout << "Event weight = " << Factor << endl;

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(Input.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);

   TFile OutputFile(Form("%s.root", OutputBase.c_str()), "RECREATE");

   TH1D HMuon1PT("HMuon1PT", "Leading muon PT;PT (GeV/c)", 50, 0, 200);
   TH1D HMuon2PT("HMuon2PT", "Sub-leading muon PT;PT (GeV/c)", 50, 0, 200);
   TH1D HDiMuonMass("HDiMuonMass", "Di-muon mass;Mass (GeV/c^2)", 50, 0, 200);
   TH1D HLeadingPFJetPT("HLeadingPFJetPT", "Leading PF jet pt;PT (GeV/c)", 50, 0, 500);
   TH1D HSubLeadingPFJetPT("HSubLeadingPFJetPT", "Sub-leading PF jet pt;PT (GeV/c)", 50, 0, 500);
   TH1D HPFJetMR("HPFJetMR", "MR*** from PF system;MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HPFJetR("HPFJetR", "R from PF system;R", 50, 0, 1);
   TH1D HPFJetMR_R05("HPFJetMR_R05",
      "MR*** from PF system (R > 0.5);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HPFMET("HPFMET", "PF MET distribution;MET (GeV)", 50, 0, 200);
   TH2D HPFJetMRVsR2("HPFJetMRVsR2",
      "MR vs. R^{2} from PF system;MR;R^{2}", 100, 0, 2000, 100, 0, 1.5);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 250000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);
      if(M.PFJetCount > 100)   // woah....
         cout << "Large number of jets!!!!" << endl;
      if(M.PFJetCount30 > 20)   // :(
         continue;

      HMuon1PT.Fill(M.Muon1PT, Factor);
      HMuon2PT.Fill(M.Muon2PT, Factor);

      FourVector Mu1P, Mu2P;
      Mu1P.SetPtEtaPhi(M.Muon1PT, M.Muon1Eta, M.Muon1Phi);
      Mu2P.SetPtEtaPhi(M.Muon2PT, M.Muon2Eta, M.Muon2Phi);
      HDiMuonMass.Fill((Mu1P + Mu2P).GetMass(), Factor);

      if(M.PFJetCount > 0)
         HLeadingPFJetPT.Fill(M.PFJetPT[0], Factor);
      if(M.PFJetCount > 1)
         HSubLeadingPFJetPT.Fill(M.PFJetPT[1], Factor);

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount && i < 100; i++)
      {
         if(M.CaloJetPT[i] < 30)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);
         GoodJets.push_back(NewJet);
      }
      if(GoodJets.size() > 20 || GoodJets.size() < 2)
         continue;
      vector<FourVector> Hemispheres = SplitIntoGroups(GoodJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      HPFMET.Fill(PFMET.GetPT(), Factor);

      double MR = Get2011MR(Hemispheres[0], Hemispheres[1]);
      double R = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);

      HPFJetMR.Fill(MR, Factor);
      HPFJetR.Fill(R, Factor);
      HPFJetMRVsR2.Fill(MR, R * R, Factor);
   
      if(R > 0.5)
         HPFJetMR_R05.Fill(MR, Factor);
   }

   HMuon1PT.Write();
   HMuon2PT.Write();
   HDiMuonMass.Write();
   HLeadingPFJetPT.Write();
   HSubLeadingPFJetPT.Write();
   HPFJetMR.Write();
   HPFJetR.Write();
   HPFJetMRVsR2.Write();
   HPFJetMR_R05.Write();
   HPFMET.Write();

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   PsFile.AddPlot(HMuon1PT, "", true);
   PsFile.AddPlot(HMuon2PT, "", true);
   PsFile.AddPlot(HDiMuonMass, "", true);
   PsFile.AddPlot(HLeadingPFJetPT, "", true);
   PsFile.AddPlot(HSubLeadingPFJetPT, "", true);
   PsFile.AddPlot(HPFJetMR, "", true);
   PsFile.AddPlot(HPFJetR, "", true);
   PsFile.AddPlot(HPFJetMRVsR2, "colz", false);
   PsFile.AddPlot(HPFJetMR_R05, "", true);
   PsFile.AddPlot(HPFMET, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




