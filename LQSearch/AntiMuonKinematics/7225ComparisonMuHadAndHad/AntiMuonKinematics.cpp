#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"

#include "ReadLQ3Tree.h"
#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

int main(int argc, char *argv[]);
void CompareHistograms(PsFileHelper &PsFile, TH1D HNormal, TH1D HAntiMuon);

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cout << "Usage: " << argv[0] << " SourceFileName OutputBase [CrossSection]" << endl;
      return -1;
   }

   string FileName = argv[1];
   string OutputBase = argv[2];

   double CrossSection = -1;
   if(argc >= 4)
   {
      stringstream str(argv[3]);
      str >> CrossSection;
      cout << "Cross section = " << CrossSection << endl;
   }

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(FileName.c_str());

   TreeRecord M;
   M.SetBranchAddress(&Tree);
   M.InitializeWeight("Samples/BookKeeping/7174PUTriggersAdded_DoubleMuRun2011Av4.PU.root");   // tentatively

   Tree.SetBranchStatus("PFJet*", false);
   Tree.SetBranchStatus("CaloJetCSVTag", false);
   Tree.SetBranchStatus("CaloJetCSVMTag", false);
   Tree.SetBranchStatus("CaloJetTCHPTag", false);

   TFile F(Form("%s.root", OutputBase.c_str()), "recreate");

   double TreeMR = 0;
   double TreeR2 = 0;
   double TreeWeight = 0;
   int TreeCategory = 0;

   TTree OutputTree("RMRTree", "RMRTree for QCD control fits");
   OutputTree.Branch("MR", &TreeMR, "MR/D");
   OutputTree.Branch("Rsq", &TreeR2, "Rsq/D");
   OutputTree.Branch("W", &TreeWeight, "W/D");
   OutputTree.Branch("Category", &TreeCategory, "Category/I");

   TH1D HRelativeEnergy("HRelativeEnergy", "RelativeEnergy, dR(muon, jet) < 0.3;Jet PT / Muon PT", 100, 0, 5);
   TH1D HCountSample("HCountSample", "Count in each sub-sample", 2, 0, 2);

   TH1D HNormalJetEta("HNormalJetEta", "Jet eta distribution in normal sample;#eta", 50, -3, 3);
   TH1D HNormalJetPT("HNormalJetPT", "Jet PT distribution in normal sample;PT (GeV)", 50, 0, 500);
   TH1D HNormalLeadingJetPT("HNormalLeadingJetPT", "Leading jet PT distribution in normal sample;PT (GeV)", 50, 0, 500);
   TH1D HAntiMuonJetEta("HAntiMuonJetEta", "Jet eta distribution in anti-muon sample;#eta", 50, -3, 3);
   TH1D HAntiMuonJetPT("HAntiMuonJetPT", "Jet PT distribution in anti-muon sample;PT (GeV)", 50, 0, 500);
   TH1D HAntiMuonLeadingJetPT("HAntiMuonLeadingJetPT",
      "Leading jet PT distribution in anti-muon sample;PT (GeV)", 50, 0, 500);

   TH1D HMRNewNormal("HMRNewNormal", "MR (new) in normal sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New005Normal("HMRNew_R2New005Normal", "MR (new), R^{2} (new) > 0.05 in normal sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New010Normal("HMRNew_R2New010Normal", "MR (new), R^{2} (new) > 0.10 in normal sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New015Normal("HMRNew_R2New015Normal", "MR (new), R^{2} (new) > 0.15 in normal sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New020Normal("HMRNew_R2New020Normal", "MR (new), R^{2} (new) > 0.20 in normal sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New025Normal("HMRNew_R2New025Normal", "MR (new), R^{2} (new) > 0.25 in normal sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New030Normal("HMRNew_R2New030Normal", "MR (new), R^{2} (new) > 0.30 in normal sample;MR (new)", 40, 0, 1000);
   TH1D HR2NewNormal("HR2NewNormal", "R^{2} (new) in normal sample;R^{2} (new)", 40, 0, 0.5);
   TH1D HR2New_MRNew200Normal("HR2New_MRNew200Normal", "R^{2} (new), MR (new) > 200 in normal sample;R^{2} (new)", 40, 0, 0.5);
   TH1D HR2New_MRNew400Normal("HR2New_MRNew400Normal", "R^{2} (new), MR (new) > 400 in normal sample;R^{2} (new)", 40, 0, 0.5);
   
   TH1D HMRNewAntiMuon("HMRNewAntiMuon", "MR (new) in anti-muon sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New005AntiMuon("HMRNew_R2New005AntiMuon", "MR (new), R^{2} (new) > 0.05 in anti-muon sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New010AntiMuon("HMRNew_R2New010AntiMuon", "MR (new), R^{2} (new) > 0.10 in anti-muon sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New015AntiMuon("HMRNew_R2New015AntiMuon", "MR (new), R^{2} (new) > 0.15 in anti-muon sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New020AntiMuon("HMRNew_R2New020AntiMuon", "MR (new), R^{2} (new) > 0.20 in anti-muon sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New025AntiMuon("HMRNew_R2New025AntiMuon", "MR (new), R^{2} (new) > 0.25 in anti-muon sample;MR (new)", 40, 0, 1000);
   TH1D HMRNew_R2New030AntiMuon("HMRNew_R2New030AntiMuon", "MR (new), R^{2} (new) > 0.30 in anti-muon sample;MR (new)", 40, 0, 1000);
   TH1D HR2NewAntiMuon("HR2NewAntiMuon", "R^{2} (new) in anti-muon sample;R^{2} (new)", 40, 0, 0.5);
   TH1D HR2New_MRNew200AntiMuon("HR2New_MRNew200AntiMuon", "R^{2} (new), MR (new) > 200 in anti-muon sample;R^{2} (new)", 40, 0, 0.5);
   TH1D HR2New_MRNew400AntiMuon("HR2New_MRNew400AntiMuon", "R^{2} (new), MR (new) > 400 in anti-muon sample;R^{2} (new)", 40, 0, 0.5);

   HNormalJetEta.Sumw2();
   HNormalJetPT.Sumw2();
   HNormalLeadingJetPT.Sumw2();
   HAntiMuonJetEta.Sumw2();
   HAntiMuonJetPT.Sumw2();
   HAntiMuonLeadingJetPT.Sumw2();
   
   HMRNewNormal.Sumw2();
   HMRNew_R2New005Normal.Sumw2();
   HMRNew_R2New010Normal.Sumw2();
   HMRNew_R2New015Normal.Sumw2();
   HMRNew_R2New020Normal.Sumw2();
   HMRNew_R2New025Normal.Sumw2();
   HMRNew_R2New030Normal.Sumw2();
   HR2NewNormal.Sumw2();
   HR2New_MRNew200Normal.Sumw2();
   HR2New_MRNew400Normal.Sumw2();

   HMRNewAntiMuon.Sumw2();
   HMRNew_R2New005AntiMuon.Sumw2();
   HMRNew_R2New010AntiMuon.Sumw2();
   HMRNew_R2New015AntiMuon.Sumw2();
   HMRNew_R2New020AntiMuon.Sumw2();
   HMRNew_R2New025AntiMuon.Sumw2();
   HMRNew_R2New030AntiMuon.Sumw2();
   HR2NewAntiMuon.Sumw2();
   HR2New_MRNew200AntiMuon.Sumw2();
   HR2New_MRNew400AntiMuon.Sumw2();
   
   HCountSample.GetXaxis()->SetBinLabel(1, "Normal");
   HCountSample.GetXaxis()->SetBinLabel(2, "Anti-Muon");

   double AllEvents = 0;
   if(CrossSection > 0)
   {
      TFile FSource(FileName.c_str());
      TH1D *H = (TH1D *)FSource.Get("HProcessedEventsPU");
      for(int i = 1; i <= H->GetNbinsX(); i++)
         AllEvents = AllEvents + M.GetWeight(i - 1) * H->GetBinContent(i);
      FSource.Close();
   }

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Alive and looking at entry " << iEntry + 1 << " out of " << EntryCount << " entries." << endl;

      Tree.GetEntry(iEntry);

      double WPU = 1;
      if(CrossSection != -1)
      {
         WPU = M.GetCurrentWeight();
         WPU = WPU * CrossSection / AllEvents * 1000;   // 1 fb^-1
      }

      bool InAntiMuonSample = false;
      
      if(M.GoodMuonCount >= 1 && M.Muon1PT > 30)
      {
         FourVector MuonP;
         MuonP.SetPtEtaPhi(M.Muon1PT, M.Muon1Eta, M.Muon1Phi);

         for(int i = 0; i < M.CaloJetCount; i++)
         {
            if(M.CaloJetPT[i] < 20)
               continue;

            FourVector JetP;
            JetP.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

            if(GetDR(JetP, MuonP) < 0.3)
            {
               double RelativeEnergy = JetP.GetPT() / MuonP.GetPT();
               if(RelativeEnergy > 0.5)
                  InAntiMuonSample = true;
               HRelativeEnergy.Fill(RelativeEnergy, WPU);
            }
         }
      }

      if(InAntiMuonSample == false)
         HCountSample.Fill(0.0, WPU);
      else
         HCountSample.Fill(1.0, WPU);
      
      int MaxJetIndex = -1;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 20)
            continue;

         if(MaxJetIndex == -1)
            MaxJetIndex = i;
         else if(M.CaloJetPT[MaxJetIndex] < M.CaloJetPT[i])
            MaxJetIndex = i;

         if(InAntiMuonSample == false)
         {
            HNormalJetEta.Fill(M.CaloJetEta[i], WPU);
            HNormalJetPT.Fill(M.CaloJetPT[i], WPU);
         }
         else
         {
            HAntiMuonJetEta.Fill(M.CaloJetEta[i], WPU);
            HAntiMuonJetPT.Fill(M.CaloJetPT[i], WPU);
         }
      }

      if(MaxJetIndex >= 0)
      {
         if(InAntiMuonSample == false)
            HNormalLeadingJetPT.Fill(M.CaloJetPT[MaxJetIndex], WPU);
         else
            HAntiMuonLeadingJetPT.Fill(M.CaloJetPT[MaxJetIndex], WPU);
      }

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

      double MRStar = GetMRStar(Hemispheres[0], Hemispheres[1]) * GetGammaRStar(Hemispheres[0], Hemispheres[1]);
      double RStar = GetRStar(Hemispheres[0], Hemispheres[1], PFMET);

      if(InAntiMuonSample == false)
      {
         HMRNewNormal.Fill(MRStar, WPU);
         if(RStar * RStar > 0.05)
            HMRNew_R2New005Normal.Fill(MRStar, WPU);
         if(RStar * RStar > 0.10)
            HMRNew_R2New010Normal.Fill(MRStar, WPU);
         if(RStar * RStar > 0.15)
            HMRNew_R2New015Normal.Fill(MRStar, WPU);
         if(RStar * RStar > 0.20)
            HMRNew_R2New020Normal.Fill(MRStar, WPU);
         if(RStar * RStar > 0.25)
            HMRNew_R2New025Normal.Fill(MRStar, WPU);
         if(RStar * RStar > 0.30)
            HMRNew_R2New030Normal.Fill(MRStar, WPU);

         HR2NewNormal.Fill(RStar * RStar, WPU);
         if(MRStar > 200)
            HR2New_MRNew200Normal.Fill(RStar * RStar, WPU);
         if(MRStar > 400)
            HR2New_MRNew400Normal.Fill(RStar * RStar, WPU);
      }
      else
      {
         HMRNewAntiMuon.Fill(MRStar, WPU);
         if(RStar * RStar > 0.05)
            HMRNew_R2New005AntiMuon.Fill(MRStar, WPU);
         if(RStar * RStar > 0.10)
            HMRNew_R2New010AntiMuon.Fill(MRStar, WPU);
         if(RStar * RStar > 0.15)
            HMRNew_R2New015AntiMuon.Fill(MRStar, WPU);
         if(RStar * RStar > 0.20)
            HMRNew_R2New020AntiMuon.Fill(MRStar, WPU);
         if(RStar * RStar > 0.25)
            HMRNew_R2New025AntiMuon.Fill(MRStar, WPU);
         if(RStar * RStar > 0.30)
            HMRNew_R2New030AntiMuon.Fill(MRStar, WPU);

         HR2NewAntiMuon.Fill(RStar * RStar, WPU);
         if(MRStar > 200)
            HR2New_MRNew200AntiMuon.Fill(RStar * RStar, WPU);
         if(MRStar > 400)
            HR2New_MRNew400AntiMuon.Fill(RStar * RStar, WPU);
      }

      TreeMR = MRStar;
      TreeR2 = RStar * RStar;
      TreeWeight = WPU;
      TreeCategory = (int)InAntiMuonSample;
      OutputTree.Fill();
   }

   F.cd();

   OutputTree.Write();

   HRelativeEnergy.Write();
   HCountSample.Write();
   HNormalJetEta.Write();
   HNormalJetPT.Write();
   HNormalLeadingJetPT.Write();
   HAntiMuonJetEta.Write();
   HAntiMuonJetPT.Write();
   HAntiMuonLeadingJetPT.Write();

   HMRNewNormal.Write();
   HMRNew_R2New005Normal.Write();
   HMRNew_R2New010Normal.Write();
   HMRNew_R2New015Normal.Write();
   HMRNew_R2New020Normal.Write();
   HMRNew_R2New025Normal.Write();
   HMRNew_R2New030Normal.Write();
   HR2NewNormal.Write();
   HR2New_MRNew200Normal.Write();
   HR2New_MRNew400Normal.Write();

   HMRNewAntiMuon.Write();
   HMRNew_R2New005AntiMuon.Write();
   HMRNew_R2New010AntiMuon.Write();
   HMRNew_R2New015AntiMuon.Write();
   HMRNew_R2New020AntiMuon.Write();
   HMRNew_R2New025AntiMuon.Write();
   HMRNew_R2New030AntiMuon.Write();
   HR2NewAntiMuon.Write();
   HR2New_MRNew200AntiMuon.Write();
   HR2New_MRNew400AntiMuon.Write();

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   vector<string> Explanations;
   Explanations.push_back("Starting from file " + FileName);
   Explanations.push_back("Split into two exclusive samples, depending on whether there is an anti-muon");
   Explanations.push_back("Anti-muon is defined by the following");
   Explanations.push_back("      - muon pass loose selection");
   Explanations.push_back("      - muon PT > 30");
   Explanations.push_back("      - dR(jet, muon) < 0.3");
   Explanations.push_back("      - jet PT > 20");
   Explanations.push_back("      - jet PT / muon PT > 0.5");
   Explanations.push_back("Using calo jets to avoid muons counted as jets");
   PsFile.AddTextPage(Explanations);

   PsFile.AddPlot(HRelativeEnergy, "", true);
   PsFile.AddPlot(HCountSample, "hist text00", false);

   PsFile.AddPlot(HNormalJetEta);
   PsFile.AddPlot(HAntiMuonJetEta);
   CompareHistograms(PsFile, HNormalJetEta, HAntiMuonJetEta);
   
   PsFile.AddPlot(HNormalJetPT, "", true);
   PsFile.AddPlot(HAntiMuonJetPT, "", true);
   CompareHistograms(PsFile, HNormalJetPT, HAntiMuonJetPT);
   
   PsFile.AddPlot(HNormalLeadingJetPT, "", true);
   PsFile.AddPlot(HAntiMuonLeadingJetPT, "", true);
   CompareHistograms(PsFile, HNormalLeadingJetPT, HAntiMuonLeadingJetPT);

   PsFile.AddPlot(HMRNewNormal, "", true);
   PsFile.AddPlot(HMRNewAntiMuon, "", true);
   CompareHistograms(PsFile, HMRNewNormal, HMRNewAntiMuon);
   
   PsFile.AddPlot(HMRNew_R2New005Normal, "", true);
   PsFile.AddPlot(HMRNew_R2New005AntiMuon, "", true);
   CompareHistograms(PsFile, HMRNew_R2New005Normal, HMRNew_R2New005AntiMuon);
   
   PsFile.AddPlot(HMRNew_R2New010Normal, "", true);
   PsFile.AddPlot(HMRNew_R2New010AntiMuon, "", true);
   CompareHistograms(PsFile, HMRNew_R2New010Normal, HMRNew_R2New010AntiMuon);
   
   PsFile.AddPlot(HMRNew_R2New015Normal, "", true);
   PsFile.AddPlot(HMRNew_R2New015AntiMuon, "", true);
   CompareHistograms(PsFile, HMRNew_R2New015Normal, HMRNew_R2New015AntiMuon);
   
   PsFile.AddPlot(HMRNew_R2New020Normal, "", true);
   PsFile.AddPlot(HMRNew_R2New020AntiMuon, "", true);
   CompareHistograms(PsFile, HMRNew_R2New020Normal, HMRNew_R2New020AntiMuon);
   
   PsFile.AddPlot(HMRNew_R2New025Normal, "", true);
   PsFile.AddPlot(HMRNew_R2New025AntiMuon, "", true);
   CompareHistograms(PsFile, HMRNew_R2New025Normal, HMRNew_R2New025AntiMuon);
   
   PsFile.AddPlot(HMRNew_R2New030Normal, "", true);
   PsFile.AddPlot(HMRNew_R2New030AntiMuon, "", true);
   CompareHistograms(PsFile, HMRNew_R2New030Normal, HMRNew_R2New030AntiMuon);
   
   PsFile.AddPlot(HR2NewNormal, "", true);
   PsFile.AddPlot(HR2NewAntiMuon, "", true);
   CompareHistograms(PsFile, HR2NewNormal, HR2NewAntiMuon);
   
   PsFile.AddPlot(HR2New_MRNew200Normal, "", true);
   PsFile.AddPlot(HR2New_MRNew200AntiMuon, "", true);
   CompareHistograms(PsFile, HR2New_MRNew200Normal, HR2New_MRNew200AntiMuon);
   
   PsFile.AddPlot(HR2New_MRNew400Normal, "", true);
   PsFile.AddPlot(HR2New_MRNew400AntiMuon, "", true);
   CompareHistograms(PsFile, HR2New_MRNew400Normal, HR2New_MRNew400AntiMuon);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();

   return 0;
}

void CompareHistograms(PsFileHelper &PsFile, TH1D HNormal, TH1D HAntiMuon)
{
   TCanvas C;

   HNormal.SetStats(0);
   HAntiMuon.SetStats(0);

   TString Title = HNormal.GetTitle();
   HNormal.SetTitle(Title.ReplaceAll(" in normal sample", ""));

   HNormal.SetLineColor(1);
   HAntiMuon.SetLineColor(2);

   HNormal.DrawNormalized("");
   HAntiMuon.DrawNormalized("same");

   TLegend legend(0.6, 0.8, 0.9, 0.6);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(&HNormal, "Normal", "l");
   legend.AddEntry(&HAntiMuon, "Anti-muon", "l");
   legend.Draw();

   C.SetLogy();
   PsFile.AddCanvas(C);

   TCanvas C2;

   HNormal.Add(&HAntiMuon);

   TH1D HWorld("HWorld", Form("Ratio of anti-muon sample to the inclusive for %s", HNormal.GetTitle()),
      HNormal.GetNbinsX(), HNormal.GetXaxis()->GetBinLowEdge(1),
      HNormal.GetXaxis()->GetBinUpEdge(HNormal.GetNbinsX()));
   HWorld.GetXaxis()->SetTitle(HNormal.GetXaxis()->GetTitle());
   HWorld.SetMaximum(0.5);
   HWorld.SetMinimum(0);
   HWorld.SetStats(0);
   HWorld.Draw();

   TGraphAsymmErrors G;
   G.BayesDivide(&HAntiMuon, &HNormal);
   G.Draw("pe");

   PsFile.AddCanvas(C2);
}





