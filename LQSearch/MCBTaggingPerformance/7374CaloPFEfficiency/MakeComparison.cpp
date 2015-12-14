#include <string>
#include <iostream>
using namespace std;

#include "TChain.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"

#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"
#include "SetStyle.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[])
{
   string Input = "BugFixed.root";
   string Output = "Meow";

   if(argc > 1)
      Input = argv[1];
   if(argc > 2)
      Output = argv[2];

   SetStyle();

   TChain Tree("LQ3Tree", "LQ3Tree");
   // Tree.AddFile("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root");
   Tree.AddFile(Input.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);

   TH2D HPFPassVsCaloPass("HPFPassVsCaloPass", "PF pass vs. Calo pass (out-of-the-box counting)", 2, 0, 2, 2, 0, 2);
   HPFPassVsCaloPass.GetXaxis()->SetBinLabel(1, "PF says \"no\"");
   HPFPassVsCaloPass.GetXaxis()->SetBinLabel(2, "PF says \"yes\"");
   HPFPassVsCaloPass.GetYaxis()->SetBinLabel(1, "Calo bad");
   HPFPassVsCaloPass.GetYaxis()->SetBinLabel(2, "Calo good");
   HPFPassVsCaloPass.SetStats(0);

   TH1D HClosestDR("HClosestDR", "Smallest dR while matching;delta R", 100, 0, 3);
   TH1D HClosestDR_80GeV("HClosestDR_80GeV", "Smallest dR while matching (jet PT > 80);delta R", 100, 0, 3);
   TH2D HCaloPTVsPFPT("HCaloPTVsPFPT", "Calo PT vs. PF PT;Calo;PF", 100, 0, 500, 100, 0, 500);

   TH2D HCaloPassVsMatchPass("HCaloPassVsMatchPass", "Calo pass vs. Matched pass", 2, 0, 2, 2, 0, 2);
   HCaloPassVsMatchPass.GetXaxis()->SetBinLabel(1, "Calo bad");
   HCaloPassVsMatchPass.GetXaxis()->SetBinLabel(2, "Calo good");
   HCaloPassVsMatchPass.GetYaxis()->SetBinLabel(1, "Matched bad");
   HCaloPassVsMatchPass.GetYaxis()->SetBinLabel(2, "Matched good");
   HCaloPassVsMatchPass.SetStats(0);

   TFile F(Form("%s.root", Output.c_str()), "recreate");

   TTree OutputTree("QuickTree", "QuickTree");

   double MR, R, DeltaPhi;
   bool PassCalo, PassMatch, PassPF;

   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");
   OutputTree.Branch("DeltaPhi", &DeltaPhi, "DeltaPhi/D");
   OutputTree.Branch("PassCalo", &PassCalo, "PassCalo/O");
   OutputTree.Branch("PassMatch", &PassMatch, "PassMatch/O");
   OutputTree.Branch("PassPF", &PassPF, "PassPF/O");

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 250000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      int CountJet60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && fabs(M.CaloJetEta[i]) < 3)
            CountJet60 = CountJet60 + 1;
      if(CountJet60 < 2)
         continue;

      vector<FourVector> PFJetP(M.PFJetCount);
      for(int i = 0; i < M.PFJetCount; i++)
         PFJetP[i].SetPtEtaPhiMass(M.PFJetPT[i], M.PFJetEta[i], M.PFJetPhi[i], 0);

      vector<FourVector> CaloJetP(M.CaloJetCount);
      vector<int> ClosestJetIndex(M.CaloJetCount);
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         CaloJetP[i].SetPtEtaPhiMass(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i], 0);

         int ClosestIndex = 0;
         for(int j = 1; j < M.PFJetCount; j++)
            if(GetDR(CaloJetP[i], PFJetP[ClosestIndex]) > GetDR(CaloJetP[i], PFJetP[j]))
               ClosestIndex = j;

         ClosestJetIndex[i] = ClosestIndex;

         HClosestDR.Fill(GetDR(CaloJetP[i], PFJetP[ClosestIndex]));
         if(CaloJetP[i].GetPT() > 80)
            HClosestDR_80GeV.Fill(GetDR(CaloJetP[i], PFJetP[ClosestIndex]));

         if(CaloJetP[i].GetEta() > -3 && CaloJetP[i].GetEta() < 3 && GetDR(CaloJetP[i], PFJetP[ClosestIndex]) < 0.5)
            HCaloPTVsPFPT.Fill(CaloJetP[i].GetPT(), PFJetP[ClosestIndex].GetPT());
      }
      
      int CaloBCount = 0;
      int MatchBCount = 0;
      int PFBCount = 0;

      PassCalo = false;
      PassMatch = false;
      PassPF = false;

      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 80)
            continue;

         if(M.CaloJetTCHETag[i] > 1.7)
            CaloBCount = CaloBCount + 1;
         if(M.PFJetTCHETag[ClosestJetIndex[i]] > 1.7 && ClosestJetIndex[i] >= 0
            && GetDR(CaloJetP[i], PFJetP[ClosestJetIndex[i]]) < 0.5)
            MatchBCount = MatchBCount + 1;
      }

      for(int i = 0; i < M.PFJetCount; i++)
      {
         if(M.PFJetEta[i] < -3 || M.PFJetEta[i] > 3)
            continue;
         if(M.PFJetPT[i] < 80)
            continue;
         if(M.PFJetTCHETag[i] < 1.7)
            continue;

         PFBCount = PFBCount + 1;
      }

      if(CaloBCount >= 2)
         PassCalo = true;
      if(MatchBCount >= 2)
         PassMatch = true;
      if(PFBCount >= 2)
         PassPF = true;

      HPFPassVsCaloPass.Fill(PassPF, PassCalo);
      HCaloPassVsMatchPass.Fill(PassCalo, PassMatch);

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount; i++)
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
      double MegaJetDeltaPhi = fabs(GetDPhi(Hemispheres[0], Hemispheres[1]));

      MR = MRNew;
      R = RNew;
      DeltaPhi = MegaJetDeltaPhi;

      OutputTree.Fill();
   }

   OutputTree.Write();
   F.Close();

   PsFileHelper PsFile(Output + ".ps");
   PsFile.AddTextPage("Meow!");

   PsFile.AddPlot(HPFPassVsCaloPass, "colz text00", false, true);
   HPFPassVsCaloPass.SetTitle(Form("%s (Percentage)", HPFPassVsCaloPass.GetTitle()));
   HPFPassVsCaloPass.Scale(100.0 / HPFPassVsCaloPass.Integral());
   PsFile.AddPlot(HPFPassVsCaloPass, "text00", false, true);

   PsFile.AddPlot(HClosestDR, "", true);
   PsFile.AddPlot(HClosestDR_80GeV, "", true);
   PsFile.AddPlot(HCaloPTVsPFPT, "colz", false, true);
   PsFile.AddPlot(HCaloPassVsMatchPass, "colz text00", false, true);
   HCaloPassVsMatchPass.SetTitle(Form("%s (Percentage)", HCaloPassVsMatchPass.GetTitle()));
   HCaloPassVsMatchPass.Scale(100.0 / HCaloPassVsMatchPass.Integral());
   PsFile.AddPlot(HCaloPassVsMatchPass, "text00", false, true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}






