#include <iostream>
using namespace std;

#include "TChain.h"

#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"

#include "ReadLQ3Tree.h"

int main()
{
   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile("Samples/AllWJetsToLNu_Added.root");

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("Samples/BookKeeping/7222ReRun_HTRun2011Av4.PU.root");

   Tree.SetBranchStatus("PFJet*", false);
   Tree.SetBranchStatus("CaloJetCSVTag", false);
   Tree.SetBranchStatus("CaloJetCSVMTag", false);
   Tree.SetBranchStatus("CaloJetTCHPTag", false);

   TH1D HMRNewAll("HMRNewAll", "MR (new)", 40, 0, 1500);
   TH1D HMRNewNoTag("HMRNewAllNoTag", "MR (new), b-tag count == 0", 40, 0, 1500);
   TH1D HMRNewTag("HMRNewAllTag", "MR (new) b-tag count > 0", 40, 0, 1500);
   
   TH1D HR2NewAll("HR2NewAll", "R^{2} (new)", 40, 0, 0.5);
   TH1D HR2NewNoTag("HR2NewAllNoTag", "R^{2} (new), b-tag count == 0", 40, 0, 0.5);
   TH1D HR2NewTag("HR2NewAllTag", "R^{2} (new) b-tag count > 0", 40, 0, 0.5);
   
   TH1D HMRNewAll_R2New010("HMRNewAll_R2New010", "MR (new), R^{2} (new) > 0.10", 40, 0, 1500);
   TH1D HMRNewNoTag_R2New010("HMRNewAllNoTag_R2New010", "MR (new), R^{2} (new) > 0.10, b-tag count == 0", 40, 0, 1500);
   TH1D HMRNewTag_R2New010("HMRNewAllTag_R2New010", "MR (new), R^{2} (new) > 0.10, b-tag count > 0", 40, 0, 1500);
   
   TH1D HR2NewAll_MRNew400("HR2NewAll_MRNew400", "R^{2} (new), MR (new) > 400", 40, 0, 0.5);
   TH1D HR2NewNoTag_MRNew400("HR2NewAllNoTag_MRNew400", "R^{2} (new), MR (new) > 400, b-tag count == 0", 40, 0, 0.5);
   TH1D HR2NewTag_MRNew400("HR2NewAllTag_MRNew400", "R^{2} (new), MR (new) > 400, b-tag count > 0", 40, 0, 0.5);
   
   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      double WPU = 1;
      WPU = M.GetCurrentWeight();

      int CaloJetCount60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            CaloJetCount60 = CaloJetCount60 + 1;
      if(CaloJetCount60 < 2)
         continue;

      int JetPassBTagLoose = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 80 && M.CaloJetTCHETag[i] > 1.7 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            JetPassBTagLoose = JetPassBTagLoose + 1;
      
      if(M.GoodMuonCount != 1 || (M.GoodMuonCount >= 1 && M.Muon1PT < 20))
         continue;
      FourVector MuonP;
      MuonP.SetPtEtaPhi(M.Muon1PT, M.Muon1Eta, M.Muon1Phi);

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
      PFMET = PFMET + MuonP;

      double MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
      double RNew = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      double R2New = RNew * RNew;

      HMRNewAll.Fill(MRNew, WPU);
      if(JetPassBTagLoose == 0)
         HMRNewNoTag.Fill(MRNew, WPU);
      else
         HMRNewTag.Fill(MRNew, WPU);
      
      HR2NewAll.Fill(R2New, WPU);
      if(JetPassBTagLoose == 0)
         HR2NewNoTag.Fill(R2New, WPU);
      else
         HR2NewTag.Fill(R2New, WPU);
      
      if(R2New > 0.10)
      {
         HMRNewAll_R2New010.Fill(MRNew, WPU);
         if(JetPassBTagLoose == 0)
            HMRNewNoTag_R2New010.Fill(MRNew, WPU);
         else
            HMRNewTag_R2New010.Fill(MRNew, WPU);
      }
      
      if(MRNew > 400)
      {
         HR2NewAll_MRNew400.Fill(R2New, WPU);
         if(JetPassBTagLoose == 0)
            HR2NewNoTag_MRNew400.Fill(R2New, WPU);
         else
            HR2NewTag_MRNew400.Fill(R2New, WPU);
      }
   }

   PsFileHelper PsFile("WShape.ps");
   PsFile.AddTextPage("W shape check");

   PsFile.AddPlot(HMRNewAll, "", true);
   PsFile.AddPlot(HMRNewNoTag, "", true);
   PsFile.AddPlot(HMRNewTag, "", true);

   TCanvas C1;
   HMRNewAll.DrawNormalized();
   HMRNewNoTag.DrawNormalized("same");
   HMRNewTag.DrawNormalized("same");
   C1.SetLogy();
   PsFile.AddCanvas(C1);

   PsFile.AddPlot(HR2NewAll, "", true);
   PsFile.AddPlot(HR2NewNoTag, "", true);
   PsFile.AddPlot(HR2NewTag, "", true);

   TCanvas C2;
   HR2NewAll.DrawNormalized();
   HR2NewNoTag.DrawNormalized("same");
   HR2NewTag.DrawNormalized("same");
   C2.SetLogy();
   PsFile.AddCanvas(C2);
   
   PsFile.AddPlot(HMRNewAll_R2New010, "", true);
   PsFile.AddPlot(HMRNewNoTag_R2New010, "", true);
   PsFile.AddPlot(HMRNewTag_R2New010, "", true);

   TCanvas C3;
   HMRNewAll_R2New010.DrawNormalized();
   HMRNewNoTag_R2New010.DrawNormalized("same");
   HMRNewTag_R2New010.DrawNormalized("same");
   C3.SetLogy();
   PsFile.AddCanvas(C3);

   PsFile.AddPlot(HR2NewAll_MRNew400, "", true);
   PsFile.AddPlot(HR2NewNoTag_MRNew400, "", true);
   PsFile.AddPlot(HR2NewTag_MRNew400, "", true);

   TCanvas C4;
   HR2NewAll_MRNew400.DrawNormalized();
   HR2NewNoTag_MRNew400.DrawNormalized("same");
   HR2NewTag_MRNew400.DrawNormalized("same");
   C4.SetLogy();
   PsFile.AddCanvas(C4);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();
}






