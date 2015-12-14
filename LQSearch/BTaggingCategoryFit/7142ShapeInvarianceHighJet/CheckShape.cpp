#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TChain.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"

#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"
#include "ReadLQ3Tree.h"
#include "SetStyle.h"

#define CaloJetThreshold 30
#define CaloJetBTagThreshold 80

int main();
void CheckShape(string InputFileName, string OutputBase);
void PlotStuff(PsFileHelper &PsFile, TH1D &All, TH1D &NoTag, TH1D &OneTag, TH1D &TwoTag, string OutputBase = "");

int main()
{
   SetStyle();

   CheckShape("Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root", "TTbar");
   // CheckShape("Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root", "W");

   return 0;
}

void CheckShape(string InputFileName, string OutputBase)
{
   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(InputFileName.c_str());

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   TreeRecord M;
   M.SetBranchAddress(&Tree);

   TH1D HGammaMRStar_All("HGammaMRStar_All", "MR***, all;MR***", 50, 0, 1500);
   TH1D HGammaMRStar_NoTag("HGammaMRStar_NoTag", "GammaMRStar, 0 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_OneTag("HGammaMRStar_OneTag", "GammaMRStar, 1 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_TwoTag("HGammaMRStar_TwoTag", "GammaMRStar, at least 2 tags;GammaMRStar", 50, 0, 1500);
   
   TH1D HGammaMRStar_RStar03_All("HGammaMRStar_RStar03_All",
      "GammaMRStar, RStar > 0.3, all;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar03_NoTag("HGammaMRStar_RStar03_NoTag",
      "GammaMRStar, RStar > 0.3, 0 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar03_OneTag("HGammaMRStar_RStar03_OneTag",
      "GammaMRStar, RStar > 0.3, 1 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar03_TwoTag("HGammaMRStar_RStar03_TwoTag",
      "GammaMRStar, RStar > 0.3, at least 2 tags;GammaMRStar", 50, 0, 1500);
   
   TH1D HGammaMRStar_RStar04_All("HGammaMRStar_RStar04_All",
      "GammaMRStar, RStar > 0.4, all;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar04_NoTag("HGammaMRStar_RStar04_NoTag",
      "GammaMRStar, RStar > 0.4, 0 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar04_OneTag("HGammaMRStar_RStar04_OneTag",
      "GammaMRStar, RStar > 0.4, 1 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar04_TwoTag("HGammaMRStar_RStar04_TwoTag",
      "GammaMRStar, RStar > 0.4, at least 2 tags;GammaMRStar", 50, 0, 1500);
   
   TH1D HGammaMRStar_RStar05_All("HGammaMRStar_RStar05_All",
      "GammaMRStar, RStar > 0.5, all;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar05_NoTag("HGammaMRStar_RStar05_NoTag",
      "GammaMRStar, RStar > 0.5, 0 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar05_OneTag("HGammaMRStar_RStar05_OneTag",
      "GammaMRStar, RStar > 0.5, 1 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar05_TwoTag("HGammaMRStar_RStar05_TwoTag",
      "GammaMRStar, RStar > 0.5, at least 2 tags;GammaMRStar", 50, 0, 1500);
   
   TH1D HGammaMRStar_RStar06_All("HGammaMRStar_RStar06_All",
      "GammaMRStar, RStar > 0.6, all;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar06_NoTag("HGammaMRStar_RStar06_NoTag",
      "GammaMRStar, RStar > 0.6, 0 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar06_OneTag("HGammaMRStar_RStar06_OneTag",
      "GammaMRStar, RStar > 0.6, 1 tag;GammaMRStar", 50, 0, 1500);
   TH1D HGammaMRStar_RStar06_TwoTag("HGammaMRStar_RStar06_TwoTag",
      "GammaMRStar, RStar > 0.6, at least 2 tags;GammaMRStar", 50, 0, 1500);
   
   TH1D HRStar_All("HRStar_All", "RStar, all;RStar", 100, 0, 1.5);
   TH1D HRStar_NoTag("HRStar_NoTag", "RStar, 0 tag;RStar", 100, 0, 1.5);
   TH1D HRStar_OneTag("HRStar_OneTag", "RStar, 1 tag;RStar", 100, 0, 1.5);
   TH1D HRStar_TwoTag("HRStar_TwoTag", "RStar, at least 2 tags;RStar", 100, 0, 1.5);

   TH1D HRStar_GammaMRStar400_All("HRStar_GammaMRStar400_All",
      "R*, MR*** > 400, all;R*", 100, 0, 1.5);
   TH1D HRStar_GammaMRStar400_NoTag("HRStar_GammaMRStar400_NoTag",
      "RStar, GammaMRStar > 400, no tag;RStar", 100, 0, 1.5);
   TH1D HRStar_GammaMRStar400_OneTag("HRStar_GammaMRStar400_OneTag",
      "RStar, GammaMRStar > 400, 1 tag;RStar", 100, 0, 1.5);
   TH1D HRStar_GammaMRStar400_TwoTag("HRStar_GammaMRStar400_TwoTag",
      "RStar, GammaMRStar > 400, at least 2 tags;RStar", 100, 0, 1.5);
   
   int NumberOfEntries = Tree.GetEntries();
   for(int iEntry = 0; iEntry < NumberOfEntries; iEntry++)
   {
      if((iEntry + 1) % 250000 == 0)
         cout << "Processing entry " << iEntry + 1 << " out of total of " << NumberOfEntries << " entries." << endl;

      M.Clear();
      Tree.GetEntry(iEntry);

      if(M.GoodMuonCount == 0)
         continue;
      if(M.Muon1PT < 15)
         continue;

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < CaloJetThreshold)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);
         GoodJets.push_back(NewJet);
      }
      if(GoodJets.size() > 20)
         continue;

      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);
      FourVector CaloMET(0, M.CaloMET[0], M.CaloMET[1], 0);

      double MRStar = GetMRStar(Groups[0], Groups[1]);
      double GammaMRStar = MRStar * GetGammaRStar(Groups[0], Groups[1]);
      double RStar = GetRStar(Groups[0], Groups[1], CaloMET);

      int BTagCount = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < CaloJetBTagThreshold)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         if(M.CaloJetTCHETag[i] > 10.2)
            BTagCount = BTagCount + 1;
      }

      HGammaMRStar_All.Fill(GammaMRStar);
      HRStar_All.Fill(RStar);
      if(RStar > 0.3)
         HGammaMRStar_RStar03_All.Fill(GammaMRStar);
      if(RStar > 0.4)
         HGammaMRStar_RStar04_All.Fill(GammaMRStar);
      if(RStar > 0.5)
         HGammaMRStar_RStar05_All.Fill(GammaMRStar);
      if(RStar > 0.6)
         HGammaMRStar_RStar06_All.Fill(GammaMRStar);
      if(GammaMRStar > 400)
         HRStar_GammaMRStar400_All.Fill(RStar);

      if(BTagCount == 0)
      {
         HGammaMRStar_NoTag.Fill(GammaMRStar);
         HRStar_NoTag.Fill(RStar);
         if(RStar > 0.3)
            HGammaMRStar_RStar03_NoTag.Fill(GammaMRStar);
         if(RStar > 0.4)
            HGammaMRStar_RStar04_NoTag.Fill(GammaMRStar);
         if(RStar > 0.5)
            HGammaMRStar_RStar05_NoTag.Fill(GammaMRStar);
         if(RStar > 0.6)
            HGammaMRStar_RStar06_NoTag.Fill(GammaMRStar);
         if(GammaMRStar > 400)
            HRStar_GammaMRStar400_NoTag.Fill(RStar);
      }
      else if(BTagCount == 1)
      {
         HGammaMRStar_OneTag.Fill(GammaMRStar);
         HRStar_OneTag.Fill(RStar);
         if(RStar > 0.3)
            HGammaMRStar_RStar03_OneTag.Fill(GammaMRStar);
         if(RStar > 0.4)
            HGammaMRStar_RStar04_OneTag.Fill(GammaMRStar);
         if(RStar > 0.5)
            HGammaMRStar_RStar05_OneTag.Fill(GammaMRStar);
         if(RStar > 0.6)
            HGammaMRStar_RStar06_OneTag.Fill(GammaMRStar);
         if(GammaMRStar > 400)
            HRStar_GammaMRStar400_OneTag.Fill(RStar);
      }
      else
      {
         HGammaMRStar_TwoTag.Fill(GammaMRStar);
         HRStar_TwoTag.Fill(RStar);
         if(RStar > 0.3)
            HGammaMRStar_RStar03_TwoTag.Fill(GammaMRStar);
         if(RStar > 0.4)
            HGammaMRStar_RStar04_TwoTag.Fill(GammaMRStar);
         if(RStar > 0.5)
            HGammaMRStar_RStar05_TwoTag.Fill(GammaMRStar);
         if(RStar > 0.6)
            HGammaMRStar_RStar06_TwoTag.Fill(GammaMRStar);
         if(GammaMRStar > 400)
            HRStar_GammaMRStar400_TwoTag.Fill(RStar);
      }
   }

   PlotStuff(PsFile, HGammaMRStar_All, HGammaMRStar_NoTag, HGammaMRStar_OneTag, HGammaMRStar_TwoTag,
      "HGammaMRStar");
   PlotStuff(PsFile, HGammaMRStar_RStar03_All, HGammaMRStar_RStar03_NoTag, HGammaMRStar_RStar03_OneTag,
      HGammaMRStar_RStar03_TwoTag, "HGammaMRStar_RStar03");
   PlotStuff(PsFile, HGammaMRStar_RStar04_All, HGammaMRStar_RStar04_NoTag, HGammaMRStar_RStar04_OneTag,
      HGammaMRStar_RStar04_TwoTag, "HGammaMRStar_RStar04");
   PlotStuff(PsFile, HGammaMRStar_RStar05_All, HGammaMRStar_RStar05_NoTag, HGammaMRStar_RStar05_OneTag,
      HGammaMRStar_RStar05_TwoTag, "HGammaMRStar_RStar05");
   PlotStuff(PsFile, HGammaMRStar_RStar06_All, HGammaMRStar_RStar06_NoTag, HGammaMRStar_RStar06_OneTag,
      HGammaMRStar_RStar06_TwoTag, "HGammaMRStar_RStar06");
   PlotStuff(PsFile, HRStar_All, HRStar_NoTag, HRStar_OneTag, HRStar_TwoTag, "HRStar");
   PlotStuff(PsFile, HRStar_GammaMRStar400_All, HRStar_GammaMRStar400_NoTag,
      HRStar_GammaMRStar400_OneTag, HRStar_GammaMRStar400_TwoTag, "HRStar_GammaMRStar400");

   HGammaMRStar_RStar03_All.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar03_NoTag.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar03_OneTag.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar03_TwoTag.Fit("expo", "", "", 500, 1000);
   
   HGammaMRStar_RStar04_All.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar04_NoTag.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar04_OneTag.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar04_TwoTag.Fit("expo", "", "", 500, 1000);

   HGammaMRStar_RStar05_All.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar05_NoTag.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar05_OneTag.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar05_TwoTag.Fit("expo", "", "", 500, 1000);

   HGammaMRStar_RStar06_All.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar06_NoTag.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar06_OneTag.Fit("expo", "", "", 500, 1000);
   HGammaMRStar_RStar06_TwoTag.Fit("expo", "", "", 500, 1000);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

void PlotStuff(PsFileHelper &PsFile, TH1D &All, TH1D &NoTag, TH1D &OneTag, TH1D &TwoTag, string OutputBase)
{
   PsFile.AddPlot(All, "", true);
   PsFile.AddPlot(NoTag, "", true);
   PsFile.AddPlot(OneTag, "", true);
   PsFile.AddPlot(TwoTag, "", true);

   TLegend Legend(0.65, 0.95, 0.95, 0.75);
   Legend.AddEntry(&All, "All", "l");
   Legend.AddEntry(&NoTag, "No tag", "l");
   Legend.AddEntry(&OneTag, "One tag", "l");
   Legend.AddEntry(&TwoTag, "At least 2 tag", "l");
   Legend.SetFillColor(0);

   TCanvas CGammaMRStar;
   All.SetMinimum(0.1);
   All.SetLineWidth(2);
   All.SetLineColor(1);
   All.SetStats(0);
   All.Draw();
   NoTag.SetLineColor(2);
   NoTag.SetStats(0);
   NoTag.Draw("same");
   OneTag.SetLineColor(3);
   OneTag.SetStats(0);
   OneTag.Draw("same");
   TwoTag.SetLineColor(4);
   TwoTag.SetStats(0);
   TwoTag.Draw("same");
   CGammaMRStar.SetLogy();
   Legend.Draw();
   PsFile.AddCanvas(CGammaMRStar);

   TCanvas CRatio;
   TGraphAsymmErrors GRatio_NoTag, GRatio_OneTag, GRatio_TwoTag;
   GRatio_NoTag.BayesDivide(&NoTag, &All);
   GRatio_OneTag.BayesDivide(&OneTag, &All);
   GRatio_TwoTag.BayesDivide(&TwoTag, &All);
   GRatio_NoTag.SetLineColor(2);
   GRatio_OneTag.SetLineColor(3);
   GRatio_TwoTag.SetLineColor(4);
   GRatio_NoTag.Draw("ap");
   GRatio_OneTag.Draw("p");
   GRatio_TwoTag.Draw("p");
   GRatio_NoTag.GetXaxis()->SetTitle(All.GetXaxis()->GetTitle());
   GRatio_NoTag.SetTitle("Ratio for different tag categories");
   GRatio_NoTag.GetYaxis()->SetRangeUser(0, 1);
   // CRatio.SetLogy();
   PsFile.AddCanvas(CRatio);

   if(OutputBase != "")
   {
      TCanvas CTogether("CTogether", "CTogether", 512, 1024);
      CTogether.Divide(1, 2);
      CTogether.cd(1)->SetLogy();
      All.Draw();
      NoTag.Draw("same");
      OneTag.Draw("same");
      TwoTag.Draw("same");
      Legend.Draw();
      CTogether.cd(2);
      GRatio_NoTag.Draw("ap");
      GRatio_OneTag.Draw("p");
      GRatio_TwoTag.Draw("p");
      GRatio_NoTag.GetXaxis()->SetTitle(All.GetXaxis()->GetTitle());
      GRatio_NoTag.SetTitle("Ratio for different tag categories");
      GRatio_NoTag.GetYaxis()->SetRangeUser(0, 1);
      CTogether.SaveAs((OutputBase + ".png").c_str());
      CTogether.SaveAs((OutputBase + ".C").c_str());
      CTogether.SaveAs((OutputBase + ".eps").c_str());
   }
}







