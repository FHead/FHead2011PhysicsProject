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

   // ReadSample("Samples/DoubleMuMay10ReRecov1_All.root", "DataPlots", -1, 240.1);
   ReadSample("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar", 165, 173.6);   // NNLL
   ReadSample("Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root", "W", 31314, 173.6);   // NNLO
   ReadSample("Samples/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola_All.root", "ZZ", 4.2, 173.6);   // Production
   ReadSample("Samples/WZtoAnything_TuneZ2_7TeV-pythia6-tauola_All.root", "WZ", 10.4, 173.6);   // Production
   ReadSample("Samples/WWtoAnything_TuneZ2_7TeV-pythia6-tauola_All.root", "WW", 27.79, 173.6);   // Production
   ReadSample("Samples/PhotonVJets_7TeV-madgraph_All.root", "GammaVJet", 173, 173.6);   // Production
   // ReadSample("Samples/DYJetsToLL_TuneD6T_M-10To50_7TeV-madgraph-tauola_All.root", "DY10", 310, 240.1);   // Production
   ReadSample("Samples/DYJetsToLL_TuneD6T_M-10To50_7TeV-madgraph-tauola_All.root", "DY10", 3100, 173.6);   // Guess
   ReadSample("Samples/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola_All.root", "DY50", 3048, 173.6);   // NNLO
}

void ReadSample(string Input, string OutputBase, double CrossSection, double Luminosity)
{
   cout << "Start processing sample " << Input << endl;
   
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
   TH1D HLeadingPFJetPT("HLeadingPFJetPT", "Leading calo jet pt;PT (GeV/c)", 50, 0, 500);
   TH1D HSubLeadingPFJetPT("HSubLeadingPFJetPT", "Sub-leading calo jet pt;PT (GeV/c)", 50, 0, 500);
   TH1D HPFJetMR("HPFJetMR", "MR from calo system;MR (GeV/c^2)", 50, 0, 1000);
   TH1D HPFJetR("HPFJetR", "R from calo system;R", 50, 0, 1);
   TH1D HPFJetMRStar("HPFJetMRStar", "MRStar from calo system;MRStar (GeV/c^2)", 50, 0, 1000);
   TH1D HPFJetGammaMRStar("HPFJetGammaMRStar", "MR*** from calo system;MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HPFJetRStar("HPFJetRStar", "RStar from calo system;RStar", 50, 0, 1);
   TH1D HPFJetGammaMRStar_RStar02("HPFJetGammaMRStar_RStar02",
      "MR*** from calo system (RStar > 0.2);MR*** (GeV/c^2)", 40, 0, 2000);
   TH1D HPFJetGammaMRStar_RStar03("HPFJetGammaMRStar_RStar03",
      "MR*** from calo system (RStar > 0.3);MR*** (GeV/c^2)", 40, 0, 2000);
   TH1D HPFJetGammaMRStar_RStar04("HPFJetGammaMRStar_RStar04",
      "MR*** from calo system (RStar > 0.4);MR*** (GeV/c^2)", 40, 0, 2000);
   TH1D HPFJetGammaMRStar_RStar05("HPFJetGammaMRStar_RStar05",
      "MR*** from calo system (RStar > 0.5);MR*** (GeV/c^2)", 40, 0, 2000);
   TH1D HPFMET("HPFMET", "PF MET distribution;MET (GeV)", 50, 0, 200);

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
      for(int i = 0; i < M.PFJetCount && i < 100; i++)
      {
         if(M.PFJetPT[i] < 30)
            continue;
         if(M.PFJetEta[i] < -2.4 || M.PFJetEta[i] > 2.4)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.PFJetPT[i], M.PFJetEta[i], M.PFJetPhi[i]);
         GoodJets.push_back(NewJet);
      }
      if(GoodJets.size() > 20)
         continue;
      if(GoodJets.size() < 2)   // single-jet event
         continue;
      vector<FourVector> Hemispheres = SplitIntoGroups(GoodJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      HPFMET.Fill(PFMET.GetPT(), Factor);

      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double R = GetR(Hemispheres[0], Hemispheres[1], PFMET);
      double MRStar = GetMRStar(Hemispheres[0], Hemispheres[1]);
      double GammaRStar = GetGammaRStar(Hemispheres[0], Hemispheres[1]);
      double RStar = GetRStar(Hemispheres[0], Hemispheres[1], PFMET);

      HPFJetMR.Fill(MR, Factor);
      HPFJetR.Fill(R, Factor);
      HPFJetMRStar.Fill(MRStar, Factor);
      HPFJetGammaMRStar.Fill(MRStar * GammaRStar, Factor);
      HPFJetRStar.Fill(RStar, Factor);
   
      if(RStar > 0.2)
         HPFJetGammaMRStar_RStar02.Fill(MRStar * GammaRStar, Factor);
      if(RStar > 0.3)
         HPFJetGammaMRStar_RStar03.Fill(MRStar * GammaRStar, Factor);
      if(RStar > 0.4)
         HPFJetGammaMRStar_RStar04.Fill(MRStar * GammaRStar, Factor);
      if(RStar > 0.5)
         HPFJetGammaMRStar_RStar05.Fill(MRStar * GammaRStar, Factor);
   }

   HMuon1PT.Write();
   HMuon2PT.Write();
   HDiMuonMass.Write();
   HLeadingPFJetPT.Write();
   HSubLeadingPFJetPT.Write();
   HPFJetMR.Write();
   HPFJetR.Write();
   HPFJetMRStar.Write();
   HPFJetGammaMRStar.Write();
   HPFJetRStar.Write();
   HPFJetGammaMRStar_RStar02.Write();
   HPFJetGammaMRStar_RStar03.Write();
   HPFJetGammaMRStar_RStar04.Write();
   HPFJetGammaMRStar_RStar05.Write();
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
   PsFile.AddPlot(HPFJetMRStar, "", true);
   PsFile.AddPlot(HPFJetGammaMRStar, "", true);
   PsFile.AddPlot(HPFJetRStar, "", true);
   PsFile.AddPlot(HPFJetGammaMRStar_RStar02, "", true);
   PsFile.AddPlot(HPFJetGammaMRStar_RStar03, "", true);
   PsFile.AddPlot(HPFJetGammaMRStar_RStar04, "", true);
   PsFile.AddPlot(HPFJetGammaMRStar_RStar05, "", true);
   PsFile.AddPlot(HPFMET, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




