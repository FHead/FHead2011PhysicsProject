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

   ReadSample("Samples/LM1_SUSY_sftsht_7TeV-pythia6_All.root", "LM1", 4.888, 1000);   // pythia LO
   ReadSample("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar", 165, 1000);   // NNLL
   ReadSample("Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root", "W", 31314, 1000);   // NNLO
   /*
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_2jet_40to120.root", "QCD_2jet_40-120", 8804000 * 0.527, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_2jet_120to280.root", "QCD_2jet_120-280", 36260 * 0.296, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_2jet_280to500.root", "QCD_2jet_280-500", 377.1 * 0.240, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_2jet_500to5000.root", "QCD_2jet_500-5000", 13.14 * 0.251, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_3jet_40to120.root", "QCD_3jet_40-120", 3425000 * 0.303, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_3jet_120to280.root", "QCD_3jet_120-280", 50100 * 0.226, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_3jet_280to500.root", "QCD_3jet_280-500", 651.7 * 0.185, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_3jet_500to5000.root", "QCD_3jet_500-5000", 22.73 * 0.185, 1000);
   // ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_4jet_40to120.root", "QCD_4jet_40-120", 467000 * 0.200, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_4jet_120to280.root", "QCD_4jet_120-280", 25680 * 0.174, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_4jet_280to500.root", "QCD_4jet_280-500", 470.8 * 0.143, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_4jet_500to5000.root", "QCD_4jet_500-5000", 17.97 * 0.142, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_5jet_40to120.root", "QCD_5jet_40-120", 64230 * 0.136, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_5jet_120to280.root", "QCD_5jet_120-280", 8187 * 0.130, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_5jet_280to500.root", "QCD_5jet_280-500", 232.9 * 0.116, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_5jet_500to5000.root", "QCD_5jet_500-5000", 9.325 * 0.110, 1000);
   // ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_6jet_40to120.root", "QCD_6jet_40-120", 9800 * 0.118, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_6jet_120to280.root", "QCD_6jet_120-280", 2656 * 0.131, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_6jet_280to500.root", "QCD_6jet_280-500", 123.8 * 0.137, 1000);
   ReadSample("QCDSamples/CopiedFromT3SUSY_QCD_6jet_500to5000.root", "QCD_6jet_500-5000", 6.194 * 0.148, 1000);
   */
}

void ReadSample(string Input, string OutputBase, double CrossSection, double Luminosity)
{
   cout << "Start processing sample " << Input << endl;
   
   double NumberOfProcessedEvents = 0;
   TFile F(Input.c_str());
   NumberOfProcessedEvents = ((TTree *)F.Get("LQ3Tree"))->GetEntries();
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
   TH1D HPFJetMR("HPFJetMR", "MR from PF system;MR (GeV/c^2)", 50, 0, 1000);
   TH1D HPFJetR("HPFJetR", "R from PF system;R", 50, 0, 1);
   TH1D HPFJetMRStar("HPFJetMRStar", "MRStar from PF system;MRStar (GeV/c^2)", 50, 0, 1000);
   TH1D HPFJetGammaMRStar("HPFJetGammaMRStar", "MR*** from PF system;MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HPFJetRStar("HPFJetRStar", "RStar from PF system;RStar", 50, 0, 1);
   TH1D HPFJetGammaMRStar_RStar05("HPFJetGammaMRStar_RStar05",
      "MR*** from PF system (RStar > 0.5);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HPFMET("HPFMET", "PF MET distribution;MET (GeV)", 50, 0, 200);
   TH2D HPFJetGammaMRStarVsRStar("HPFJetGammaMRStarVsRStar",
      "GammaMRStar vs. RStar from PF system;GammaMRStar;RStar", 100, 0, 2000, 100, 0, 1.5);

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
         if(M.PFJetEta[i] < -3 || M.PFJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.PFJetPT[i], M.PFJetEta[i], M.PFJetPhi[i]);
         GoodJets.push_back(NewJet);
      }
      if(GoodJets.size() > 20 || GoodJets.size() < 2)
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
      HPFJetGammaMRStarVsRStar.Fill(MRStar * GammaRStar, RStar * RStar, Factor);
   
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
   HPFJetGammaMRStarVsRStar.Write();
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
   PsFile.AddPlot(HPFJetGammaMRStarVsRStar, "colz", false);
   PsFile.AddPlot(HPFJetGammaMRStar_RStar05, "", true);
   PsFile.AddPlot(HPFMET, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




