#include <iostream>
using namespace std;

#include "TChain.h"
#include "TFile.h"

#include "PlotHelper2.h"

#include "ReadLQ3Tree.h"

int main();
void ReadSample(string InputFile, string OutputBase);

int main()
{
   // ReadSample("NotReducedSample/ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola_Summer11-PU_S4_START42_V11-v1_All.root", "ZbbFull");
   // ReadSample("HalfReducedSample/ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola_Summer11-PU_S4_START42_V11-v1_All.root", "ZbbHalf");
   ReadSample("Samples/ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola_Summer11-PU_S4_START42_V11-v1_All.root", "Zbb");
   ReadSample("Samples/ZinvisibleJets_7TeV-madgraph_All.root", "Znunu");
   ReadSample("Samples/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root", "DY");

   return 0;
}

void ReadSample(string InputFile, string OutputBase)
{
   double CrossSection = 1;
   double Luminosity = 1;

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(InputFile.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("Samples/BookKeeping/7222ReRun_HTRun2011Av4.PU.root");

   Tree.SetBranchStatus("PFJet*", false);
   Tree.SetBranchStatus("CaloJetCSVTag", false);
   Tree.SetBranchStatus("CaloJetCSVMTag", false);
   Tree.SetBranchStatus("CaloJetTCHPTag", false);

   double AllEvents = 0;
   TFile F(InputFile.c_str());
   TH1D *H = (TH1D *)F.Get("HProcessedEventsPU");
   for(int i = 1; i <= H->GetNbinsX(); i++)
      AllEvents = AllEvents + M.GetWeight(i - 1) * H->GetBinContent(i);
   F.Close();

   TH1D HRawNPU("HRawNPU", "Number of pileups, before weighting;Count", 20, -0.5, 19.5);
   TH1D HNPU("HNPU", "Number of pileups, after weighting;Count", 20, -0.5, 19.5);

   TH1D HTCHETag("HTCHETag", "TCHE tag of all jets above 40 GeV;TCHE", 100, 0, 20);
   TH1D HTCHELCount("HTCHELCount", "Number of jets (30GeV) passing TCHEL;Count", 20, -0.5, 19.5);
   TH1D HTCHEMCount("HTCHEMCount", "Number of jets (30GeV) passing TCHEM;Count", 20, -0.5, 19.5);
   TH1D HTCHETCount("HTCHETCount", "Number of jets (30GeV) passing TCHET;Count", 20, -0.5, 19.5);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 100000 == 0)
         cout << "Processing " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      double WPU = M.GetCurrentWeight();
      WPU = WPU * CrossSection * Luminosity / AllEvents;

      HRawNPU.Fill(M.PileUp);
      HNPU.Fill(M.PileUp, WPU);

      int TCHELCount = 0;
      int TCHEMCount = 0;
      int TCHETCount = 0;

      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 30)
            continue;

         HTCHETag.Fill(M.CaloJetTCHETag[i], WPU);

         if(M.CaloJetTCHETag[i] > 1.7)
            TCHELCount = TCHELCount + 1;
         if(M.CaloJetTCHETag[i] > 3.3)
            TCHEMCount = TCHEMCount + 1;
         if(M.CaloJetTCHETag[i] > 10.2)
            TCHETCount = TCHETCount + 1;
      }

      HTCHELCount.Fill(TCHELCount, WPU);
      HTCHEMCount.Fill(TCHEMCount, WPU);
      HTCHETCount.Fill(TCHETCount, WPU);
   }

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   PsFile.AddTextPage("Sanity check plots");
   PsFile.AddPlot(HRawNPU, "text00 hist", true);
   PsFile.AddPlot(HNPU, "text00 hist", true);

   PsFile.AddTextPage("B-tagging plots");
   PsFile.AddPlot(HTCHETag, "", true);
   PsFile.AddPlot(HTCHELCount, "", true);
   PsFile.AddPlot(HTCHEMCount, "", true);
   PsFile.AddPlot(HTCHETCount, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}




