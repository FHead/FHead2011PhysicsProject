#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sys/stat.h>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TList.h"

#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   if(argc < 2)
   {
      cout << "Usage: " << argv[0] << " SourceFile" << endl;
      return -1;
   }

   map<pair<int, long long>, int> EventList;
   ifstream in("AllFailures.txt");
   while(in)
   {
      int Run = -1;
      long long Event = -1;
      in >> Run >> Event;
      if(Run > 0 && Event > 0)
         EventList.insert(pair<pair<int, long long>, int>(pair<int, long long>(Run, Event), 1));
   }
   in.close();

   string SourceFileName = argv[1];

   TFile Source(SourceFileName.c_str());

   TTree *OldTree = (TTree *)Source.Get("LQ3Tree");

   TreeRecord M;
   M.SetBranchAddress(OldTree);
   OldTree->SetBranchStatus("PFJet*", false);
   OldTree->SetBranchStatus("CaloJetCSVTag", false);
   OldTree->SetBranchStatus("CaloJetCSVMTag", false);
   OldTree->SetBranchStatus("CaloJetTCHPTag", false);
   OldTree->SetBranchStatus("Electron*", false);
   OldTree->SetBranchStatus("Muon*", false);
   OldTree->SetBranchStatus("Electron*", false);

   TH2D HMRNewVsR2NewLL("HMRNewVsR2NewLL", "MR (new) vs. R^{2} (new);MR (new); R^{2} (new)", 100, 200, 1400, 100, 0, 1);
   TH2D HMRNewVsR2NewLLPassFilter("HMRNewVsR2NewPassFilterLL",
      "MR (new) vs. R^{2} (new), passing filter;MR (new); R^{2} (new)", 100, 200, 1400, 100, 0, 1);
   TH2D HMRNewVsR2NewLLFailFilter("HMRNewVsR2NewFailFilterLL",
      "MR (new) vs. R^{2} (new), failing filter;MR (new); R^{2} (new)", 100, 200, 1400, 100, 0, 1);
   
   TH2D HMRNewVsR2NewL("HMRNewVsR2NewL", "MR (new) vs. R^{2} (new);MR (new); R^{2} (new)", 100, 200, 1400, 100, 0, 1);
   TH2D HMRNewVsR2NewLPassFilter("HMRNewVsR2NewPassFilterL",
      "MR (new) vs. R^{2} (new), passing filter;MR (new); R^{2} (new)", 100, 200, 1400, 100, 0, 1);
   TH2D HMRNewVsR2NewLFailFilter("HMRNewVsR2NewFailFilterL",
      "MR (new) vs. R^{2} (new), failing filter;MR (new); R^{2} (new)", 100, 200, 1400, 100, 0, 1);

   int SPassFilter = 0;
   int SFailFilter = 0;
   int SBPassFilter = 0;
   int SBFailFilter = 0;

   int EntryCount = OldTree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 100000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      OldTree->GetEntry(iEntry);

      if(M.PassNoiseFilter == false)
         continue;

      bool InList = true;
      pair<int, long long> Index((int)(M.RunNumber + 0.01), (long long)(M.EventNumber + 0.01));
      if(EventList.find(Index) == EventList.end())
         InList = false;

      int CaloJet60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            CaloJet60 = CaloJet60 + 1;
      if(CaloJet60 < 2)
         continue;

      int LooseCount = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 80 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3 && M.CaloJetTCHETag[i] > 1.7)
            LooseCount = LooseCount + 1;

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

      if(LooseCount >= 2)
      {
         HMRNewVsR2NewLL.Fill(MRNew, R2New);
         if(InList == false)
            HMRNewVsR2NewLLPassFilter.Fill(MRNew, R2New);
         else
            HMRNewVsR2NewLLFailFilter.Fill(MRNew, R2New);
      }
      if(LooseCount == 1)
      {
         HMRNewVsR2NewL.Fill(MRNew, R2New);
         if(InList == false)
            HMRNewVsR2NewLPassFilter.Fill(MRNew, R2New);
         else
            HMRNewVsR2NewLFailFilter.Fill(MRNew, R2New);
      }

      if(LooseCount >= 2 && MRNew > 400 && R2New > 0.25 && R2New < 0.50 && InList == true)
         SFailFilter = SFailFilter + 1;
      if(LooseCount >= 2 && MRNew > 400 && R2New > 0.25 && R2New < 0.50 && InList == false)
         SPassFilter = SPassFilter + 1;
      if(LooseCount == 1 && MRNew > 400 && MRNew < 600 && R2New > 0.20 && R2New < 0.25 && InList == true)
         SBFailFilter = SBFailFilter + 1;
      if(LooseCount == 1 && MRNew > 400 && MRNew < 600 && R2New > 0.20 && R2New < 0.25 && InList == false)
         SBPassFilter = SBPassFilter + 1;
   }

   PsFileHelper PsFile("Distributions.ps");
   PsFile.AddTextPage("Examining events failing hcal noise filter");

   vector<string> Explanations;
   Explanations.push_back("Pick only the events failing after-the-fact noise filtering");
   Explanations.push_back("and check the noise flags in my exported trees");
   Explanations.push_back("Most noise are above R^{2} > 0.5, so I plotted up to R^{2} = 1");
   PsFile.AddTextPage(Explanations);

   PsFile.AddPlot(HMRNewVsR2NewLL, "colz");
   PsFile.AddPlot(HMRNewVsR2NewLLPassFilter, "colz");
   PsFile.AddPlot(HMRNewVsR2NewLLFailFilter, "colz");
   PsFile.AddPlot(HMRNewVsR2NewL, "colz");
   PsFile.AddPlot(HMRNewVsR2NewLPassFilter, "colz");
   PsFile.AddPlot(HMRNewVsR2NewLFailFilter, "colz");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   cout << "S, Pass = " << SPassFilter << endl;
   cout << "S, Fail = " << SFailFilter << endl;
   cout << "SB, Pass = " << SBPassFilter << endl;
   cout << "SB, Fail = " << SBFailFilter << endl;

   Source.Close();

   return 0;
}

