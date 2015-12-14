#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main();
void MakeOverlay(PsFileHelper &PsFile, vector<TFile *> Files, TFile *DataFile, TFile *SignalFile, string HistogramName, vector<string> Labels, double Luminosity, int LQMass);
void Make2DPlots(PsFileHelper &PsFile, vector<TFile *> Files, TFile *DataFile, TFile *SignalFile, string Tag, vector<string> Labels, double Luminosity, int LQMass);

int main()
{
   SetStyle();

   int LQMasses[] = {250, 350, 450, 550};

   double Luminosity = 4.625;   // in inverse femtobarn

   vector<string> MCSamples;
   // MCSamples.push_back("Histograms/QCD_TuneD6T_HT-All.root");
   MCSamples.push_back("Histograms/QCD_Pt-All.root");
   MCSamples.push_back("Histograms/TTJets_TuneZ2_7TeV-madgraph-tauola_HIGHSTAT_All.root");
   MCSamples.push_back("Histograms/SingleTop_All.root");
   MCSamples.push_back("Histograms/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root");
   MCSamples.push_back("Histograms/ZinvisibleJets_7TeV-madgraph_All.root");
   MCSamples.push_back("Histograms/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root");
   MCSamples.push_back("Histograms/GJet_All.root");

   vector<string> Labels;
   Labels.push_back("QCD");
   Labels.push_back("TTJet");
   Labels.push_back("TJet");
   Labels.push_back("WJet");
   Labels.push_back("ZnunuJet");
   Labels.push_back("DYJet");
   Labels.push_back("GJet");

   vector<TFile *> MCFiles;
   for(int i = 0; i < (int)MCSamples.size(); i++)
      MCFiles.push_back(new TFile(MCSamples[i].c_str()));

   TFile HTDataFile("Histograms/HTRun2011All.root");
   TFile MuDataFile("Histograms/MuHadRun2011All.root");
   TFile EleDataFile("Histograms/ElectronHadRun2011All.root");
   TFile MuEGDataFile("Histograms/MuEG_All.root");
   TFile PhotonDataFile("Histograms/PhotonHadRun2011All.root");
   TFile DoubleMuonDataFile("Histograms/DoubleMuRun2011All.root");

   vector<TFile *> SignalFiles;
   for(int i = 0; i < 4; i++)
      SignalFiles.push_back(new TFile((Form("Histograms/LQToBNutau_%d.root", LQMasses[i]))));

   string Category[9] = {"Had", "TightMuon", "LooseMuon", "TightElectron", "LooseElectron",
      "LooseMuEle", "TightMuEle", "Photon", "DoubleMuon"};
   string BTag[8] = {"All", "NoTag", "OneLoose", "TwoLoose", "OneMedium", "TwoMedium", "OneTight", "TwoTight"};

   PsFileHelper PsFile("Meow.ps");

   for(int k = 0; k < 4; k++)   // LQ 550 is weird
   {
      for(int i = 0; i < 1; i++)
      {
         TFile *DataFile = NULL;
         // if(i == 0)   DataFile = &HTDataFile;
         if(i == 0)   DataFile = NULL;
         if(i == 1)   DataFile = &MuDataFile;
         if(i == 2)   DataFile = &MuDataFile;
         if(i == 3)   DataFile = &EleDataFile;
         if(i == 4)   DataFile = &EleDataFile;
         if(i == 5)   DataFile = &MuEGDataFile;
         if(i == 6)   DataFile = &MuEGDataFile;
         if(i == 7)   DataFile = &PhotonDataFile;
         if(i == 8)   DataFile = &DoubleMuonDataFile;
   
         // cout << "! " << ((TH1D *)DataFile->Get("HMR11_R112020_Photon_All"))->GetBinContent(1) << endl;

         if(i == 0)   Luminosity = 4.700;
         if(i == 1)   Luminosity = 4.776;
         if(i == 2)   Luminosity = 4.776;
         if(i == 3)   Luminosity = 4.782;
         if(i == 4)   Luminosity = 4.782;
         if(i == 5)   Luminosity = 4.698;   // old lumi
         if(i == 6)   Luminosity = 4.698;   // old lumi
         if(i == 7)   Luminosity = 4.716;   // old lumi
         if(i == 8)   Luminosity = 4.320;   // old lumi

         for(int j = 0; j < 8; j++)
         {
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2000_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2014Restricted_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2020_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2020Restricted_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2025Restricted_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2030_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2035_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2040_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2045_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR_R2050_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);

            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2_MR000_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2_MR100_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2_MR200_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2_MR300_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2_MR400_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2_MR400Restricted_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2_MR400Restricted2_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2_MR500_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);

            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2000_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2014Restricted_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2020_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2020Restricted_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2025Restricted_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2030_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2035_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2040_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2045_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMRL_R2050_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);

            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2L_MR000_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2L_MR100_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2L_MR200_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2L_MR300_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2L_MR400_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2L_MR400Restricted_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2L_MR400Restricted2_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR2L_MR500_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);

            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonMR_R2000_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonMR_R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonMR_R2020_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonMR_R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonMR_R2030_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonMR_R2035_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonMR_R2040_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonMR_R2045_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonMR_R2050_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);

            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonR2_MR000_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonR2_MR100_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonR2_MR200_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonR2_MR300_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonR2_MR400_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonR2_MR500_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);

            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR11_R112000_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR11_R112014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR11_R112020_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR11_R112040_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR11_R112050_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR11_R112060_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR11_R112070_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR11_R112080_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMR11_R112090_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);

            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR112_MR11000_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR112_MR11100_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR112_MR11200_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR112_MR11300_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR112_MR11400_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HR112_MR11500_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);

            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HJetPT_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMuonPT_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMuon2PT_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonPT_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonMass_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonMass2_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonPT_ZPole_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonRapidity_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HElectronPT_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonPT_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMET_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HJetPT_MR400R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMuonPT_MR400R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMuon2PT_MR400R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonPT_MR400R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonMass_MR400R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonRapidity_MR400R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HElectronPT_MR400R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonPT_MR400R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMET_MR400R2025_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HJetPT_MR400R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMuonPT_MR400R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMuon2PT_MR400R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonPT_MR400R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonMass_MR400R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HDiMuonRapidity_MR400R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HElectronPT_MR400R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HPhotonPT_MR400R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            MakeOverlay(PsFile, MCFiles, DataFile, SignalFiles[k], "HMET_MR400R2014_" + Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
            
            Make2DPlots(PsFile, MCFiles, DataFile, SignalFiles[k], Category[i] + "_" + BTag[j], Labels, Luminosity, LQMasses[k]);
         }
      }
   }

   for(int i = 0; i < 4; i++)
   {
      if(SignalFiles[i] != NULL)
      {
         SignalFiles[i]->Close();
         delete SignalFiles[i];
      }
   }
   
   PhotonDataFile.Close();
   EleDataFile.Close();
   MuDataFile.Close();
   HTDataFile.Close();

   for(int i = 0; i < (int)MCSamples.size(); i++)
   {
      MCFiles[i]->Close();
      delete MCFiles[i];
   }

   cout << "DONE!!!" << endl;

   return 0;
}

void MakeOverlay(PsFileHelper &PsFile, vector<TFile *> Files, TFile *DataFile, TFile *SignalFile, string HistogramName, vector<string> Labels, double Luminosity, int LQMass)
{
   // cout << "! " << ((TH1D *)DataFile->Get(HistogramName.c_str()))->GetBinContent(1) << endl;
   
   if(DataFile != NULL)
      ((TH1D *)DataFile->Get(HistogramName.c_str()))->GetBinContent(1);
   
   vector<TH1D *> Histograms(0);
   for(int i = 0; i < (int)Files.size(); i++)
      Histograms.push_back((TH1D *)((TH1D *)Files[i]->Get(HistogramName.c_str())->Clone("")));

   TH1D *DataHist = NULL;
   if(DataFile != NULL)
      DataHist = (TH1D *)DataFile->Get(HistogramName.c_str())->Clone("DataClone");

   TH1D *SignalHist = NULL;
   if(SignalFile != NULL)
      SignalHist = (TH1D *)((TH1D *)SignalFile->Get(HistogramName.c_str())->Clone(""));

   for(int i = (int)Files.size() - 1; i > 0; i--)
      Histograms[i-1]->Add(Histograms[i]);
   if(SignalHist != NULL)
      SignalHist->Add(Histograms[0]);

   for(int i = 0; i < (int)Files.size(); i++)
   {
      Histograms[i]->SetFillColor(i + 2);
      Histograms[i]->SetLineColor(i + 2);
      Histograms[i]->SetStats(0);
      Histograms[i]->Scale(Luminosity);
   }
   if(SignalHist != NULL)
   {
      SignalHist->SetLineColor(kBlack);
      SignalHist->SetLineWidth(2);
      SignalHist->Scale(Luminosity);
   }
   if(DataHist != NULL)
      DataHist->SetMarkerStyle(8);

   TCanvas C("C", "", 800, 800);
   for(int i = 0; i < (int)Files.size(); i++)
   {
      if(i == 0)
      {
         Histograms[i]->SetMinimum(0.5);
         Histograms[i]->Draw("hist");
      }
      else
         Histograms[i]->Draw("hist same");
   }

   if(DataHist != NULL)
      DataHist->Draw("error same point");
   if(SignalHist != NULL)
      SignalHist->Draw("hist same");

   TLegend Legend(0.7, 0.85, 0.9, 0.55);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   for(int i = 0; i < (int)Files.size(); i++)
      Legend.AddEntry(Histograms[i], Labels[i].c_str(), "f");
   if(DataHist != NULL)
      Legend.AddEntry(DataHist, "Data", "pl");
   if(SignalHist != NULL)
      Legend.AddEntry(SignalHist, Form("LQ%d + SM", LQMass), "l");
   Legend.Draw();

   Histograms[0]->Draw("axis same");

   AddCMSPreliminary(0.05, 0.02, Luminosity * 1000);

   C.SetLogy();
   // PsFile.AddCanvas(C);

   C.SaveAs(("IndividualPlots/" + HistogramName + Form("_WithLQ%d", LQMass) + ".png").c_str());
   // C.SaveAs(("IndividualPlots/" + HistogramName + Form("_WithLQ%d", LQMass) + ".C").c_str());
   // C.SaveAs(("IndividualPlots/" + HistogramName + Form("_WithLQ%d", LQMass) + ".eps").c_str());
   C.SaveAs(("IndividualPlots/" + HistogramName + Form("_WithLQ%d", LQMass) + ".pdf").c_str());

   if(SignalHist != NULL)
      delete SignalHist;

   if(DataHist != NULL)
      delete DataHist;

   for(int i = 0; i < (int)Files.size(); i++)
      delete Histograms[i];
}

void Make2DPlots(PsFileHelper &PsFile, vector<TFile *> Files, TFile *DataFile, TFile *SignalFile, string Tag, vector<string> Labels, double Luminosity, int LQMass)
{
   TH2D *HAllBackground = (TH2D *)Files[0]->Get(("HMRRMap_" + Tag).c_str())->Clone("");
   for(int i = 1; i < (int)Files.size(); i++)
      HAllBackground->Add((TH2D *)Files[i]->Get(("HMRRMap_" + Tag).c_str()));
   HAllBackground->Scale(Luminosity);

   TH2D *HSignal = NULL;
   if(SignalFile != NULL)
   {
      HSignal = (TH2D *)((TH2D *)SignalFile->Get(("HMRRMap_" + Tag).c_str())->Clone(""));
      HSignal->Scale(Luminosity);
   }

   TCanvas C("C", "", 800, 800);

   HAllBackground->SetStats(0);
   HAllBackground->SetTitle(Form("All background yields, %s", Tag.c_str()));
   HAllBackground->Draw("colz text30");
   C.SetLogz(true);
   // PsFile.AddCanvas(C);
   C.SaveAs(("IndividualPlots/MRRMapBackground_" + Tag + "_" + Form("WithLQ%d", LQMass) + ".png").c_str());

   if(HSignal != NULL)
   {
      HSignal->SetStats(0);
      HSignal->Draw("colz text30");
      C.SetLogz(true);
      // PsFile.AddCanvas(C);
      C.SaveAs(("IndividualPlots/MRRMapSignal_" + Tag + "_" + Form("WithLQ%d", LQMass) + ".png").c_str());
   }

   for(int i = 0; i < (int)Files.size(); i++)
   {
      TH2D *HIndividual = (TH2D *)((TH2D *)Files[i]->Get(("HMRRMap_" + Tag).c_str()))->Clone("");
      HIndividual->SetStats(0);
      HIndividual->Draw("colz text30");
      HIndividual->Scale(Luminosity);
      C.SetLogz(true);
      // PsFile.AddCanvas(C);
      C.SaveAs(("IndividualPlots/MRRMapBackground" + Labels[i] + "_" + Tag + "_" + Form("WithLQ%d", LQMass) + ".png").c_str());
      delete HIndividual;
   }

   if(HSignal != NULL)
   {
      TH2D *HSOverB = (TH2D *)HSignal->Clone("");
      TH2D *HSOverSqrtSB = (TH2D *)HSignal->Clone("");

      HSOverB->SetTitle(Form("S/B, %s, LQ Mass %d", Tag.c_str(), LQMass));
      HSOverSqrtSB->SetTitle(Form("S/sqrt(S+B), %s, LQ Mass %d", Tag.c_str(), LQMass));

      for(int i = 1; i <= HSignal->GetNbinsX(); i++)
      {
         for(int j = 1; j <= HSignal->GetNbinsY(); j++)
         {
            double S = HSignal->GetBinContent(i, j);
            double B = HAllBackground->GetBinContent(i, j);

            HSOverB->SetBinContent(i, j, S / B);
            HSOverSqrtSB->SetBinContent(i, j, S / sqrt(S + B));
         }
      }

      HSOverB->Draw("colz text30");
      C.SetLogz(false);
      // PsFile.AddCanvas(C);
      C.SaveAs(("IndividualPlots/MRRMapSOverB_" + Tag + "_" + Form("WithLQ%d", LQMass) + ".png").c_str());
      
      HSOverSqrtSB->Draw("colz text30");
      C.SetLogz(false);
      // PsFile.AddCanvas(C);
      C.SaveAs(("IndividualPlots/MRRMapSOverSqrtSB_" + Tag + "_" + Form("WithLQ%d", LQMass) + ".png").c_str());

      delete HSOverSqrtSB;
      delete HSOverB;
   }

   if(HSignal != NULL)
      delete HSignal;

   delete HAllBackground;
}




