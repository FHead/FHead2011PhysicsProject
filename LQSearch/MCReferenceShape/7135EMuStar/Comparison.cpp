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

   ReadSample("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar", 165, 1000);   // NNLL
   ReadSample("Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root", "W", 31314, 1000);   // NNLO
   ReadSample("Samples/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola_All.root", "ZZ", 4.2, 1000);   // Production
   ReadSample("Samples/WZtoAnything_TuneZ2_7TeV-pythia6-tauola_All.root", "WZ", 10.4, 1000);   // Production
   ReadSample("Samples/WWtoAnything_TuneZ2_7TeV-pythia6-tauola_All.root", "WW", 27.79, 1000);   // Production
   ReadSample("Samples/PhotonVJets_7TeV-madgraph_All.root", "GammaVJet", 173, 1000);   // Production
   ReadSample("Samples/DYJetsToLL_TuneD6T_M-10To50_7TeV-madgraph-tauola_All.root", "DY10", 3100, 1000);   // Guess
   ReadSample("Samples/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola_All.root", "DY50", 3048, 1000);   // NNLO
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
   TH1D HElectron1PT("HElectron1PT", "Leading electron PT;PT (GeV/c)", 50, 0, 200);
   TH1D HLeadingCaloJetPT("HLeadingCaloJetPT", "Leading calo jet pt;PT (GeV/c)", 50, 0, 500);
   TH1D HSubLeadingCaloJetPT("HSubLeadingCaloJetPT", "Sub-leading calo jet pt;PT (GeV/c)", 50, 0, 500);
   TH1D HCaloJetMR("HCaloJetMR", "MR from calo system;MR (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetR("HCaloJetR", "R from calo system;R", 50, 0, 1);
   TH1D HCaloJetMRStar("HCaloJetMRStar", "MRStar from calo system;MRStar (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetGammaMRStar("HCaloJetGammaMRStar", "MR*** from calo system;MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetRStar("HCaloJetRStar", "RStar from calo system;RStar", 50, 0, 1);
   TH1D HCaloJetGammaMRStar_RStar02("HCaloJetGammaMRStar_RStar02",
      "MR*** from calo system (RStar > 0.2);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetGammaMRStar_RStar03("HCaloJetGammaMRStar_RStar03",
      "MR*** from calo system (RStar > 0.3);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetGammaMRStar_RStar04("HCaloJetGammaMRStar_RStar04",
      "MR*** from calo system (RStar > 0.4);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloJetGammaMRStar_RStar05("HCaloJetGammaMRStar_RStar05",
      "MR*** from calo system (RStar > 0.5);MR*** (GeV/c^2)", 50, 0, 1000);
   TH1D HCaloMET("HCaloMET", "Calo MET distribution;MET (GeV)", 50, 0, 200);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 250000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);
      if(M.CaloJetCount > 100)   // woah....
         cout << "Large number of jets!!!!" << endl;
      if(M.CaloJetCount30 > 20)   // :(
         continue;

      if(M.GoodMuonCountTight < 1)   // at least one muon
         continue;
      if(M.Muon1PT < 20)
         continue;
      if(M.GoodElectronCount80 < 1)   // at least one electron
         continue;
      if(M.Electron1PT < 20)
         continue;

      HMuon1PT.Fill(M.Muon1PT, Factor);
      HElectron1PT.Fill(M.Electron1PT, Factor);

      if(M.CaloJetCount > 0)
         HLeadingCaloJetPT.Fill(M.CaloJetPT[0], Factor);
      if(M.CaloJetCount > 1)
         HSubLeadingCaloJetPT.Fill(M.CaloJetPT[1], Factor);

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount && i < 100; i++)
      {
         if(M.CaloJetPT[i] < 30)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         // electron-jet!  throw it away....
         double DEta = M.CaloJetEta[i] - M.Electron1Eta;
         double DPhi = M.CaloJetPhi[i] - M.Electron1Phi;
         if(DPhi < 0)    DPhi = -DPhi;
         if(DPhi > PI)   DPhi = 2 * PI - DPhi;
         double DR2 = DEta * DEta + DPhi * DPhi;
         if(DR2 < 0.3 * 0.3)
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

      FourVector CaloMET(0, M.CaloMET[0], M.CaloMET[1], 0);
      HCaloMET.Fill(CaloMET.GetPT(), Factor);

      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double R = GetR(Hemispheres[0], Hemispheres[1], CaloMET);
      double MRStar = GetMRStar(Hemispheres[0], Hemispheres[1]);
      double GammaRStar = GetGammaRStar(Hemispheres[0], Hemispheres[1]);
      double RStar = GetRStar(Hemispheres[0], Hemispheres[1], CaloMET);

      HCaloJetMR.Fill(MR, Factor);
      HCaloJetR.Fill(R, Factor);
      HCaloJetMRStar.Fill(MRStar, Factor);
      HCaloJetGammaMRStar.Fill(MRStar * GammaRStar, Factor);
      HCaloJetRStar.Fill(RStar, Factor);

      if(RStar > 0.2)
         HCaloJetGammaMRStar_RStar02.Fill(MRStar * GammaRStar, Factor);
      if(RStar > 0.3)
         HCaloJetGammaMRStar_RStar03.Fill(MRStar * GammaRStar, Factor);
      if(RStar > 0.4)
         HCaloJetGammaMRStar_RStar04.Fill(MRStar * GammaRStar, Factor);
      if(RStar > 0.5)
         HCaloJetGammaMRStar_RStar05.Fill(MRStar * GammaRStar, Factor);
   }

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
   HCaloMET.Write();

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

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
   PsFile.AddPlot(HCaloMET, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.Close();
}




