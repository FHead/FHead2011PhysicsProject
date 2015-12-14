#include <iostream>
#include <sstream>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);
void ReadSample(string Tag, double CrossSection);

int main(int argc, char *argv[])
{
   string Tag = "";
   if(argc <= 2)
   {
      cerr << "Usage: " << argv[0] << " Tag CrossSection" << endl;
      return -1;
   }

   Tag = argv[1];
   stringstream str(argv[2]);
   double CrossSection = -1;
   str >> CrossSection;

   if(CrossSection <= 0)
   {
      cerr << "CrossSection smaller than zero!!" << endl;
      return -1;
   }

   ReadSample(Tag, CrossSection);

   return 0;
}

void ReadSample(string Tag, double CrossSection)
{
   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(("Samples/" + Tag + ".root").c_str());
   if(Tree.GetEntries() == 0)
      return;

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("Samples/BookKeeping/7222ReRun_HTRun2011Av4.PU.root");

   Tree.SetBranchStatus("PFJet*", false);
   Tree.SetBranchStatus("CaloJetCSVTag", false);
   Tree.SetBranchStatus("CaloJetCSVMTag", false);
   Tree.SetBranchStatus("CaloJetTCHPTag", false);

   double AllEvents = 0;
   TFile InputF(("Samples/" + Tag + ".root").c_str());
   TH1D *H = (TH1D *)InputF.Get("HProcessedEventsPU");
   for(int i = 1; i <= H->GetNbinsX(); i++)
      AllEvents = AllEvents + M.GetWeight(i - 1) * H->GetBinContent(i);
   InputF.Close();

   TFile F((Tag + ".root").c_str(), "RECREATE");

   TH2D HMRNewVsR2New("HMRNewVsR2New", "MR (new) vs. R^{2} (new);MR (new);R^2 (new)", 100, 0, 1000, 100, 0, 1.2);

   TH1D HMRNew("HMRNew", "MR (new);MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New005("HMRNew_R2New005", "MR (new), R^{2} (new) > 0.05;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New010("HMRNew_R2New010", "MR (new), R^{2} (new) > 0.10;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New015("HMRNew_R2New015", "MR (new), R^{2} (new) > 0.15;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New020("HMRNew_R2New020", "MR (new), R^{2} (new) > 0.20;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New025("HMRNew_R2New025", "MR (new), R^{2} (new) > 0.25;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New030("HMRNew_R2New030", "MR (new), R^{2} (new) > 0.30;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New035("HMRNew_R2New035", "MR (new), R^{2} (new) > 0.35;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New040("HMRNew_R2New040", "MR (new), R^{2} (new) > 0.40;MR (new)", 40, 0, 1500);
   TH1D HMRNew_R2New045("HMRNew_R2New045", "MR (new), R^{2} (new) > 0.45;MR (new)", 40, 0, 1500);
   
   TH1D HR2New("HR2New", "R^{2} (new);R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew300("HR2New_MRNew300", "R^{2} (new), MR (new) > 300;R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew400("HR2New_MRNew400", "R^{2} (new), MR (new) > 400;R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew500("HR2New_MRNew500", "R^{2} (new), MR (new) > 500;R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew600("HR2New_MRNew600", "R^{2} (new), MR (new) > 600;R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew700("HR2New_MRNew700", "R^{2} (new), MR (new) > 700;R^{2} (new)", 40, 0.0, 1.2);
   
   TH1D HMRNew_MRNew300("HMRNew_MRNew300", "MR (new), MR (new) > 300;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New005("HMRNew_MRNew300_R2New005",
      "MR (new), MR (new) > 300, R^{2} (new) > 0.05;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New010("HMRNew_MRNew300_R2New010",
      "MR (new), MR (new) > 300, R^{2} (new) > 0.10;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New015("HMRNew_MRNew300_R2New015",
      "MR (new), MR (new) > 300, R^{2} (new) > 0.15;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New020("HMRNew_MRNew300_R2New020",
      "MR (new), MR (new) > 300, R^{2} (new) > 0.20;MR (new)", 40, 0, 1500);
   TH1D HMRNew_MRNew300_R2New025("HMRNew_MRNew300_R2New025",
      "MR (new), MR (new) > 300, R^{2} (new) > 0.25;MR (new)", 40, 0, 1500);

   TH1D HR2New_R2New015("HR2New_R2New015", "R^{2} (new), R^{2} > 0.15;R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew300_R2New015("HR2New_MRNew300_R2New015",
      "R^{2} (new), MR (new) > 300, R^{2} (new) > 0.15;R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew400_R2New015("HR2New_MRNew400_R2New015",
      "R^{2} (new), MR (new) > 400, R^{2} (new) > 0.15;R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew500_R2New015("HR2New_MRNew500_R2New015",
      "R^{2} (new), MR (new) > 500, R^{2} (new) > 0.15;R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew600_R2New015("HR2New_MRNew600_R2New015",
      "R^{2} (new), MR (new) > 600, R^{2} (new) > 0.15;R^{2} (new)", 40, 0.0, 1.2);
   TH1D HR2New_MRNew700_R2New015("HR2New_MRNew700_R2New015",
      "R^{2} (new), MR (new) > 700, R^{2} (new) > 0.15;R^{2} (new)", 40, 0.0, 1.2);
   
   HMRNewVsR2New.Sumw2();

   HMRNew.Sumw2();
   HMRNew_R2New005.Sumw2();
   HMRNew_R2New010.Sumw2();
   HMRNew_R2New015.Sumw2();
   HMRNew_R2New020.Sumw2();
   HMRNew_R2New025.Sumw2();
   HMRNew_R2New030.Sumw2();
   HMRNew_R2New035.Sumw2();
   HMRNew_R2New040.Sumw2();
   HMRNew_R2New045.Sumw2();

   HR2New.Sumw2();
   HR2New_MRNew300.Sumw2();
   HR2New_MRNew400.Sumw2();
   HR2New_MRNew500.Sumw2();
   HR2New_MRNew600.Sumw2();
   HR2New_MRNew700.Sumw2();
   
   HR2New_R2New015.Sumw2();
   HR2New_MRNew300_R2New015.Sumw2();
   HR2New_MRNew400_R2New015.Sumw2();
   HR2New_MRNew500_R2New015.Sumw2();
   HR2New_MRNew600_R2New015.Sumw2();
   HR2New_MRNew700_R2New015.Sumw2();

   double Luminosity = 1000;

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 100000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      double WPU = M.GetCurrentWeight();
      WPU = WPU * CrossSection * Luminosity / AllEvents;

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

      if(M.GoodElectronCount >= 1 && M.Electron1PT > 20)
         continue;
      if(M.GoodMuonCount >= 1 && M.Muon1PT > 20)
         continue;

      vector<FourVector> CaloJets;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 40)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);
         CaloJets.push_back(NewJet);
      }
      if(CaloJets.size() < 2 || CaloJets.size() > 20)
         continue;
      vector<FourVector> Hemispheres = SplitIntoGroups(CaloJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      PFMET[0] = PFMET.GetPT();

      double MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
      double RNew = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      double R2New = RNew * RNew;

      HMRNewVsR2New.Fill(MRNew, R2New, WPU);

      if(R2New > 0.00 && MRNew > 0)
      {
         HMRNew.Fill(MRNew, WPU);
         if(R2New > 0.05)   HMRNew_R2New005.Fill(MRNew, WPU);
         if(R2New > 0.10)   HMRNew_R2New010.Fill(MRNew, WPU);
         if(R2New > 0.15)   HMRNew_R2New015.Fill(MRNew, WPU);
         if(R2New > 0.20)   HMRNew_R2New020.Fill(MRNew, WPU);
         if(R2New > 0.25)   HMRNew_R2New025.Fill(MRNew, WPU);
         if(R2New > 0.30)   HMRNew_R2New030.Fill(MRNew, WPU);
         if(R2New > 0.35)   HMRNew_R2New035.Fill(MRNew, WPU);
         if(R2New > 0.40)   HMRNew_R2New040.Fill(MRNew, WPU);
         if(R2New > 0.45)   HMRNew_R2New045.Fill(MRNew, WPU);
         
         HR2New.Fill(R2New, WPU);
         if(MRNew > 300)   HR2New_MRNew300.Fill(R2New, WPU);
         if(MRNew > 400)   HR2New_MRNew400.Fill(R2New, WPU);
         if(MRNew > 500)   HR2New_MRNew500.Fill(R2New, WPU);
         if(MRNew > 600)   HR2New_MRNew600.Fill(R2New, WPU);
         if(MRNew > 700)   HR2New_MRNew700.Fill(R2New, WPU);
      }
      
      if(R2New > 0.00 && MRNew > 300)
      {
         HMRNew_MRNew300.Fill(MRNew, WPU);
         if(R2New > 0.05)   HMRNew_MRNew300_R2New005.Fill(MRNew, WPU);
         if(R2New > 0.10)   HMRNew_MRNew300_R2New010.Fill(MRNew, WPU);
         if(R2New > 0.15)   HMRNew_MRNew300_R2New015.Fill(MRNew, WPU);
         if(R2New > 0.20)   HMRNew_MRNew300_R2New020.Fill(MRNew, WPU);
         if(R2New > 0.25)   HMRNew_MRNew300_R2New025.Fill(MRNew, WPU);
      }
      
      if(R2New > 0.15 && MRNew > 0)
      {
         HR2New_R2New015.Fill(R2New, WPU);
         if(MRNew > 300)   HR2New_MRNew300_R2New015.Fill(R2New, WPU);
         if(MRNew > 400)   HR2New_MRNew400_R2New015.Fill(R2New, WPU);
         if(MRNew > 500)   HR2New_MRNew500_R2New015.Fill(R2New, WPU);
         if(MRNew > 600)   HR2New_MRNew600_R2New015.Fill(R2New, WPU);
         if(MRNew > 700)   HR2New_MRNew700_R2New015.Fill(R2New, WPU);
      }
   }

   PsFileHelper PsFile(Tag + ".ps");
   PsFile.AddTextPage(Tag);

   PsFile.AddPlot(HMRNewVsR2New, "colz");

   PsFile.AddPlot(HMRNew, "", true);
   PsFile.AddPlot(HMRNew_R2New005, "", true);
   PsFile.AddPlot(HMRNew_R2New010, "", true);
   PsFile.AddPlot(HMRNew_R2New015, "", true);
   PsFile.AddPlot(HMRNew_R2New020, "", true);
   PsFile.AddPlot(HMRNew_R2New025, "", true);
   PsFile.AddPlot(HMRNew_R2New030, "", true);
   PsFile.AddPlot(HMRNew_R2New035, "", true);
   PsFile.AddPlot(HMRNew_R2New040, "", true);
   PsFile.AddPlot(HMRNew_R2New045, "", true);

   PsFile.AddPlot(HR2New, "", true);
   PsFile.AddPlot(HR2New_MRNew300, "", true);
   PsFile.AddPlot(HR2New_MRNew400, "", true);
   PsFile.AddPlot(HR2New_MRNew500, "", true);
   PsFile.AddPlot(HR2New_MRNew600, "", true);
   PsFile.AddPlot(HR2New_MRNew700, "", true);
   
   PsFile.AddPlot(HMRNew_MRNew300, "", true);
   PsFile.AddPlot(HMRNew_MRNew300_R2New005, "", true);
   PsFile.AddPlot(HMRNew_MRNew300_R2New010, "", true);
   PsFile.AddPlot(HMRNew_MRNew300_R2New015, "", true);
   PsFile.AddPlot(HMRNew_MRNew300_R2New020, "", true);
   PsFile.AddPlot(HMRNew_MRNew300_R2New025, "", true);

   PsFile.AddPlot(HR2New_R2New015, "", true);
   PsFile.AddPlot(HR2New_MRNew300_R2New015, "", true);
   PsFile.AddPlot(HR2New_MRNew400_R2New015, "", true);
   PsFile.AddPlot(HR2New_MRNew500_R2New015, "", true);
   PsFile.AddPlot(HR2New_MRNew600_R2New015, "", true);
   PsFile.AddPlot(HR2New_MRNew700_R2New015, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   HMRNewVsR2New.Write();

   HMRNew.Write();
   HMRNew_R2New005.Write();
   HMRNew_R2New010.Write();
   HMRNew_R2New015.Write();
   HMRNew_R2New020.Write();
   HMRNew_R2New025.Write();
   HMRNew_R2New030.Write();
   HMRNew_R2New035.Write();
   HMRNew_R2New040.Write();
   HMRNew_R2New045.Write();

   HR2New.Write();
   HR2New_MRNew300.Write();
   HR2New_MRNew400.Write();
   HR2New_MRNew500.Write();
   HR2New_MRNew600.Write();
   HR2New_MRNew700.Write();

   HMRNew_MRNew300.Write();
   HMRNew_MRNew300_R2New005.Write();
   HMRNew_MRNew300_R2New010.Write();
   HMRNew_MRNew300_R2New015.Write();
   HMRNew_MRNew300_R2New020.Write();
   HMRNew_MRNew300_R2New025.Write();

   HR2New_R2New015.Write();
   HR2New_MRNew300_R2New015.Write();
   HR2New_MRNew400_R2New015.Write();
   HR2New_MRNew500_R2New015.Write();
   HR2New_MRNew600_R2New015.Write();
   HR2New_MRNew700_R2New015.Write();

   F.Close();
}





