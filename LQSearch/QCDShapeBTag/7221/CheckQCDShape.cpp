#include <string>
#include <sstream>
using namespace std;

#include "TChain.h"
#include "TFile.h"

#include "ReadLQ3Tree.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"

int main();
void ReadSample(string Input, string OutputBase, double Luminosity, double CrossSection, int LooseTag);

int main()
{
   ReadSample("Samples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root", "QCD50All", 1000, 30000000, -1);
   ReadSample("Samples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root", "QCD100All", 1000, 7000000, -1);
   ReadSample("Samples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root", "QCD200All", 1000, 171000, -1);
   ReadSample("Samples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root", "QCD500All", 1000, 5200, -1);
   ReadSample("Samples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root", "QCD1000All", 1000, 83, -1);
   
   ReadSample("Samples/ArturBQCD_30To50_All.root", "BQCD30All", 1000, 53100000 * 0.075, -1);
   ReadSample("Samples/ArturBQCD_50To150_All.root", "BQCD50All", 1000, 7236000 * 0.09, -1);
   ReadSample("Samples/ArturBQCD_150_All.root", "BQCD150All", 1000, 47620 * 0.114, -1);
   
   ReadSample("Samples/ArturBQCD_30To50_All.root", "BQCD30_B0", 1000, 53100000 * 0.075, 0);
   ReadSample("Samples/ArturBQCD_50To150_All.root", "BQCD50_B0", 1000, 7236000 * 0.09, 0);
   ReadSample("Samples/ArturBQCD_150_All.root", "BQCD150_B0", 1000, 47620 * 0.114, 0);
   
   ReadSample("Samples/ArturBQCD_30To50_All.root", "BQCD30_B1", 1000, 53100000 * 0.075, 1);
   ReadSample("Samples/ArturBQCD_50To150_All.root", "BQCD50_B1", 1000, 7236000 * 0.09, 1);
   ReadSample("Samples/ArturBQCD_150_All.root", "BQCD150_B1", 1000, 47620 * 0.114, 1);
   
   ReadSample("Samples/ArturBQCD_30To50_All.root", "BQCD30_B2", 1000, 53100000 * 0.075, 2);
   ReadSample("Samples/ArturBQCD_50To150_All.root", "BQCD50_B2", 1000, 7236000 * 0.09, 2);
   ReadSample("Samples/ArturBQCD_150_All.root", "BQCD150_B2", 1000, 47620 * 0.114, 2);

   return 0;
}

void ReadSample(string Input, string OutputBase, double Luminosity, double CrossSection, int LooseTag)
{
   if(LooseTag != -1)
      cout << "Start processing file " << Input << " requiring " << LooseTag << " b-tags...." << endl;
   else
      cout << "Start processing file " << Input << endl;

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(Input.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("Samples/BookKeeping/7174PUTriggersAdded_ElectronHadRun2011Av4.PU.root");      

   Tree.SetBranchStatus("PFJet*", false);
   Tree.SetBranchStatus("CaloJetCSVTag", false);
   Tree.SetBranchStatus("CaloJetCSVMTag", false);
   Tree.SetBranchStatus("CaloJetTCHPTag", false);

   double AllEvents = 0;
   TFile FSource(Input.c_str());
   TH1D *H = (TH1D *)FSource.Get("HProcessedEventsPU");
   for(int i = 1; i <= H->GetNbinsX(); i++)
      AllEvents = AllEvents + M.GetWeight(i - 1) * H->GetBinContent(i);
   FSource.Close();

   TFile F(Form("%s.root", OutputBase.c_str()), "recreate");

   TH1D HMRNew("HMRNew", "MR (new);MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New005("HMRNew_R2New005", "MR (new), R^{2} (new) > 0.05;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New010("HMRNew_R2New010", "MR (new), R^{2} (new) > 0.10;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New015("HMRNew_R2New015", "MR (new), R^{2} (new) > 0.15;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New020("HMRNew_R2New020", "MR (new), R^{2} (new) > 0.20;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New025("HMRNew_R2New025", "MR (new), R^{2} (new) > 0.25;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New030("HMRNew_R2New030", "MR (new), R^{2} (new) > 0.30;MR (new)", 40, 0, 1000);
   
   TH1D HR2New("HR2New", "R^{2} (new);R^{2} (new)", 40, 0, 0.5);
   TH1D HR2New_MRNew200("HR2New_MRNew200", "R^{2} (new), MR (new) > 200;R^{2} (new)", 40, 0, 0.5);
   TH1D HR2New_MRNew400("HR2New_MRNew400", "R^{2} (new), MR (new) > 400;R^{2} (new)", 40, 0, 0.5);

   HMRNew.Sumw2();
   HMRNew_R2New005.Sumw2();
   HMRNew_R2New010.Sumw2();
   HMRNew_R2New015.Sumw2();
   HMRNew_R2New020.Sumw2();
   HMRNew_R2New025.Sumw2();
   HMRNew_R2New030.Sumw2();

   HR2New.Sumw2();
   HR2New_MRNew200.Sumw2();
   HR2New_MRNew400.Sumw2();

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree.GetEntry(iEntry);

      double WPU = M.GetCurrentWeight();
      WPU = WPU * CrossSection * Luminosity / AllEvents;   // weight...

      int JetCount60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            JetCount60 = JetCount60 + 1;
      if(JetCount60 < 2)
         continue;

      int JetPassBTagLoose = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetTCHETag[i] > 1.7 && M.CaloJetPT[i] > 80 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            JetPassBTagLoose = JetPassBTagLoose + 1;
      if(LooseTag >= 0 && LooseTag < 2 && JetPassBTagLoose != LooseTag)
         continue;
      if(LooseTag == 2 && JetPassBTagLoose < 2)
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
      vector<FourVector> Hemispheres = SplitIntoGroups(CaloJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      PFMET[0] = PFMET.GetPT();

      double MRStar = GetMRStar(Hemispheres[0], Hemispheres[1]) * GetGammaRStar(Hemispheres[0], Hemispheres[1]);
      double RStar = GetRStar(Hemispheres[0], Hemispheres[1], PFMET);

      HMRNew.Fill(MRStar, WPU);
      if(RStar * RStar > 0.05)
         HMRNew_R2New005.Fill(MRStar, WPU);
      if(RStar * RStar > 0.10)
         HMRNew_R2New010.Fill(MRStar, WPU);
      if(RStar * RStar > 0.15)
         HMRNew_R2New015.Fill(MRStar, WPU);
      if(RStar * RStar > 0.20)
         HMRNew_R2New020.Fill(MRStar, WPU);
      if(RStar * RStar > 0.25)
         HMRNew_R2New025.Fill(MRStar, WPU);
      if(RStar * RStar > 0.30)
         HMRNew_R2New030.Fill(MRStar, WPU);
      
      HR2New.Fill(RStar * RStar, WPU);
      if(MRStar > 200)
         HR2New_MRNew200.Fill(RStar * RStar, WPU);
      if(MRStar > 400)
         HR2New_MRNew400.Fill(RStar * RStar, WPU);
   }

   HMRNew.Write();
   HMRNew_R2New005.Write();
   HMRNew_R2New010.Write();
   HMRNew_R2New015.Write();
   HMRNew_R2New020.Write();
   HMRNew_R2New025.Write();
   HMRNew_R2New030.Write();

   HR2New.Write();
   HR2New_MRNew200.Write();
   HR2New_MRNew400.Write();

   PsFileHelper PsFile(OutputBase + ".ps");
   if(LooseTag < 0)
      PsFile.AddTextPage(OutputBase);
   else
   {
      stringstream str;
      str << OutputBase << ", " << LooseTag << " tags";
      PsFile.AddTextPage(str.str());
   }

   PsFile.AddPlot(HMRNew, "", true);
   PsFile.AddPlot(HMRNew_R2New005, "", true);
   PsFile.AddPlot(HMRNew_R2New010, "", true);
   PsFile.AddPlot(HMRNew_R2New015, "", true);
   PsFile.AddPlot(HMRNew_R2New020, "", true);
   PsFile.AddPlot(HMRNew_R2New025, "", true);
   PsFile.AddPlot(HMRNew_R2New030, "", true);

   PsFile.AddPlot(HR2New, "", true);
   PsFile.AddPlot(HR2New_MRNew200, "", true);
   PsFile.AddPlot(HR2New_MRNew400, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}





