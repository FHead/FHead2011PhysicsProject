#include <iostream>
#include <string>
using namespace std;

#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[])
{
   string FileName = "LQSamples/LQToBNutau_310.list.root";
   if(argc > 1)
      FileName = argv[1];

   string Tag = "LQ310";
   if(argc == 2)
      Tag = "Unknown";
   else if(argc > 2)
      Tag = argv[2];

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(FileName.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);

   TH1D HBTagCountL60("HBTagCountL60", "b-tag count (60 GeV), TCHEL", 10, -0.5, 9.5);
   TH1D HBTagCountL80("HBTagCountL80", "b-tag count (80 GeV), TCHEL", 10, -0.5, 9.5);
   TH1D HBTagCountL100("HBTagCountL100", "b-tag count (100 GeV), TCHEL", 10, -0.5, 9.5);
   TH1D HBTagCountM60("HBTagCountM60", "b-tag count (60 GeV), TCHEM", 10, -0.5, 9.5);
   TH1D HBTagCountM80("HBTagCountM80", "b-tag count (80 GeV), TCHEM", 10, -0.5, 9.5);
   TH1D HBTagCountM100("HBTagCountM100", "b-tag count (100 GeV), TCHEM", 10, -0.5, 9.5);

   TH1D HMR_2M80("HMR_2M80", "MR, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HR2_2M80("HR2_2M80", "R2, 80 GeV b (TCHEM) x2", 100, 0, 1.5);
   TH2D HMRVsR2_2M80("HMRVsR2_2M80", "MR vs. R2, 80 GeV b (TCHEM) x2", 100, 0, 1500, 100, 0, 1.5);
   TH1D HISRRemovedMR_2M80("HISRRemovedMR_2M80", "ISRRemovedMR, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HISRRemovedR2_2M80("HISRRemovedR2_2M80", "ISRRemovedR2, 80 GeV b (TCHEM) x2", 100, 0, 1.5);
   TH2D HISRRemovedMRVsR2_2M80("HISRRemovedMRVsR2_2M80", "ISRRemovedMR vs. ISRRemovedR2, 80 GeV b (TCHEM) x2",
      100, 0, 1500, 100, 0, 1.5);
   
   TH1D HMRNew_2M80("HMRNew_2M80", "MRNew, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HMRNew_Razor020_2M80("HMRNew_Razor020_2M80", "MRNew, razor cut 0.2, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HMRNew_Razor025_2M80("HMRNew_Razor025_2M80", "MRNew, razor cut 0.25, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HMRNew_Razor030_2M80("HMRNew_Razor030_2M80", "MRNew, razor cut 0.3, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HR2New_2M80("HR2New_2M80", "R2New, 80 GeV b (TCHEM) x2", 100, 0, 1.5);
   TH2D HMRNewVsR2New_2M80("HMRNewVsR2New_2M80", "MRNew vs. R2New, 80 GeV b (TCHEM) x2", 100, 0, 1500, 100, 0, 1.5);
   TH1D HISRRemovedMRNew_2M80("HISRRemovedMRNew_2M80", "ISRRemovedMRNew, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HISRRemovedMRNew_Razor020_2M80("HISRRemovedMRNew_Razor020_2M80",
      "ISRRemovedMRNew, Razor cut 0.2, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HISRRemovedMRNew_Razor025_2M80("HISRRemovedMRNew_Razor025_2M80",
      "ISRRemovedMRNew, Razor cut 0.25, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HISRRemovedMRNew_Razor030_2M80("HISRRemovedMRNew_Razor030_2M80",
      "ISRRemovedMRNew, Razor cut 0.3, 80 GeV b (TCHEM) x2", 100, 0, 1500);
   TH1D HISRRemovedR2New_2M80("HISRRemovedR2New_2M80", "ISRRemovedR2New, 80 GeV b (TCHEM) x2", 100, 0, 1.5);
   TH2D HISRRemovedMRNewVsR2New_2M80("HISRRemovedMRNewVsR2New_2M80",
      "ISRRemovedMRNew vs. ISRRemovedR2New, 80 GeV b (TCHEM) x2", 100, 0, 1500, 100, 0, 1.5);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << "..." << endl;

      Tree.GetEntry(iEntry);

      int JetCount60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetPT[i] < 60)
            continue;

         JetCount60 = JetCount60 + 1;
      }
      if(JetCount60 < 2)
         continue;

      int BTagCountL60 = 0;
      int BTagCountL80 = 0;
      int BTagCountL100 = 0;
      int BTagCountM60 = 0;
      int BTagCountM80 = 0;
      int BTagCountM100 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         if(M.CaloJetTCHETag[i] > 1.7)
         {
            if(M.CaloJetPT[i] > 60)
               BTagCountL60 = BTagCountL60 + 1;
            if(M.CaloJetPT[i] > 80)
               BTagCountL80 = BTagCountL80 + 1;
            if(M.CaloJetPT[i] > 100)
               BTagCountL100 = BTagCountL100 + 1;
         }
         if(M.CaloJetTCHETag[i] > 3.3)
         {
            if(M.CaloJetPT[i] > 60)
               BTagCountM60 = BTagCountM60 + 1;
            if(M.CaloJetPT[i] > 80)
               BTagCountM80 = BTagCountM80 + 1;
            if(M.CaloJetPT[i] > 100)
               BTagCountM100 = BTagCountM100 + 1;
         }
      }

      HBTagCountL60.Fill(BTagCountL60);
      HBTagCountL80.Fill(BTagCountL80);
      HBTagCountL100.Fill(BTagCountL100);
      HBTagCountM60.Fill(BTagCountM60);
      HBTagCountM80.Fill(BTagCountM80);
      HBTagCountM100.Fill(BTagCountM100);

      // let's focus on M80, 2 jet case for now
      if(BTagCountM80 == 2)
      {
         vector<FourVector> GoodJets;
         vector<FourVector> BJets;
         for(int i = 0; i < M.CaloJetCount; i++)
         {
            if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
               continue;

            FourVector JetP;
            JetP.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

            if(M.CaloJetPT[i] > 40)
               GoodJets.push_back(JetP);
            if(M.CaloJetPT[i] > 80 && M.CaloJetTCHETag[i] > 3.3)
               BJets.push_back(JetP);
         }
         vector<FourVector> Hemispheres = SplitIntoGroups(GoodJets, true);

         FourVector MET(0, M.PFMET[0], M.PFMET[1], 0);
         MET[0] = MET.GetPT();

         FourVector Others = -(BJets[0] + BJets[1] + MET);
         Others[0] = Others.GetP();

         double MR = GetMR(Hemispheres[0], Hemispheres[1]);
         double R = GetR(Hemispheres[0], Hemispheres[1], MET);
         double ISRRemovedMR = GetISRRemovedMR(BJets[0], BJets[1], -(BJets[0] + BJets[1] + MET));
         double ISRRemovedR = GetISRRemovedR(BJets[0], BJets[1], -(BJets[0] + BJets[1] + MET));
         
         double MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
         double RNew = Get2011R(Hemispheres[0], Hemispheres[1], MET);
         double ISRRemovedMRNew = GetISRRemoved2011MR(BJets[0], BJets[1], -(BJets[0] + BJets[1] + MET));
         double ISRRemovedRNew = GetISRRemoved2011R(BJets[0], BJets[1], -(BJets[0] + BJets[1] + MET));

         HMR_2M80.Fill(MR);
         HR2_2M80.Fill(R * R);
         HMRVsR2_2M80.Fill(MR, R * R);
         HISRRemovedMR_2M80.Fill(ISRRemovedMR);
         HISRRemovedR2_2M80.Fill(ISRRemovedR * ISRRemovedR);
         HISRRemovedMRVsR2_2M80.Fill(ISRRemovedMR, ISRRemovedR * ISRRemovedR);
         
         HMRNew_2M80.Fill(MRNew);
         HR2New_2M80.Fill(RNew * RNew);
         HMRNewVsR2New_2M80.Fill(MRNew, RNew * RNew);
         HISRRemovedMRNew_2M80.Fill(ISRRemovedMRNew);
         HISRRemovedR2New_2M80.Fill(ISRRemovedRNew * ISRRemovedRNew);
         HISRRemovedMRNewVsR2New_2M80.Fill(ISRRemovedMRNew, ISRRemovedRNew * ISRRemovedRNew);
         
         if(RNew * RNew > 0.2)
            HMRNew_Razor020_2M80.Fill(MRNew);
         if(ISRRemovedRNew * ISRRemovedRNew > 0.2)
            HISRRemovedMRNew_Razor020_2M80.Fill(ISRRemovedMRNew);
         
         if(RNew * RNew > 0.25)
            HMRNew_Razor025_2M80.Fill(MRNew);
         if(ISRRemovedRNew * ISRRemovedRNew > 0.25)
            HISRRemovedMRNew_Razor025_2M80.Fill(ISRRemovedMRNew);
         
         if(RNew * RNew > 0.3)
            HMRNew_Razor030_2M80.Fill(MRNew);
         if(ISRRemovedRNew * ISRRemovedRNew > 0.3)
            HISRRemovedMRNew_Razor030_2M80.Fill(ISRRemovedMRNew);
      }
   }

   PsFileHelper PsFile(Tag + ".ps");
   PsFile.AddTextPage(FileName);

   PsFile.AddPlot(HBTagCountL60, "text00 hist", true);
   PsFile.AddPlot(HBTagCountM60, "text00 hist", true);
   PsFile.AddPlot(HBTagCountL80, "text00 hist", true);
   PsFile.AddPlot(HBTagCountM80, "text00 hist", true);
   PsFile.AddPlot(HBTagCountL100, "text00 hist", true);
   PsFile.AddPlot(HBTagCountM100, "text00 hist", true);

   PsFile.AddTextPage("Focus on 2-tagged events for now (80 GeV, TCHEM)");
   PsFile.AddPlot(HMR_2M80, "", true);
   PsFile.AddPlot(HISRRemovedMR_2M80, "", true);
   PsFile.AddPlot(HR2_2M80, "", true);
   PsFile.AddPlot(HISRRemovedR2_2M80, "", true);
   PsFile.AddPlot(HMRVsR2_2M80, "colz", false);
   PsFile.AddPlot(HISRRemovedMRVsR2_2M80, "colz", false);
   
   PsFile.AddPlot(HMRNew_2M80, "", true);
   PsFile.AddPlot(HISRRemovedMRNew_2M80, "", true);
   PsFile.AddPlot(HR2New_2M80, "", true);
   PsFile.AddPlot(HISRRemovedR2New_2M80, "", true);
   PsFile.AddPlot(HMRNewVsR2New_2M80, "colz", false);
   PsFile.AddPlot(HISRRemovedMRNewVsR2New_2M80, "colz", false);
   
   PsFile.AddPlot(HMRNew_Razor020_2M80, "", true);
   PsFile.AddPlot(HISRRemovedMRNew_Razor020_2M80, "", true);

   HISRRemovedMRNew_Razor020_2M80.SetLineColor(kRed);

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetFillColor(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&HMRNew_Razor020_2M80, "Old", "l");
   Legend.AddEntry(&HISRRemovedMRNew_Razor020_2M80, "New", "l");

   TCanvas CRazor020;
   HISRRemovedMRNew_Razor020_2M80.Draw();
   HMRNew_Razor020_2M80.Draw("same");
   Legend.Draw();
   CRazor020.SetLogy();
   PsFile.AddCanvas(CRazor020);
   
   PsFile.AddPlot(HMRNew_Razor025_2M80, "", true);
   PsFile.AddPlot(HISRRemovedMRNew_Razor025_2M80, "", true);
   
   HISRRemovedMRNew_Razor025_2M80.SetLineColor(kRed);

   TCanvas CRazor025;
   HISRRemovedMRNew_Razor025_2M80.Draw();
   HMRNew_Razor025_2M80.Draw("same");
   Legend.Draw();
   CRazor025.SetLogy();
   PsFile.AddCanvas(CRazor025);

   PsFile.AddPlot(HMRNew_Razor030_2M80, "", true);
   PsFile.AddPlot(HISRRemovedMRNew_Razor030_2M80, "", true);
   
   HISRRemovedMRNew_Razor030_2M80.SetLineColor(kRed);

   TCanvas CRazor030;
   HISRRemovedMRNew_Razor030_2M80.Draw();
   HMRNew_Razor030_2M80.Draw("same");
   Legend.Draw();
   CRazor030.SetLogy();
   PsFile.AddCanvas(CRazor030);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}


