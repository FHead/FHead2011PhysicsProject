// //---------------------------------------------------------------------------
#include <iostream>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TColor.h"
#include "TLegend.h"
//---------------------------------------------------------------------------
#include "PlotHelper2.h"
#include "ReadLQ3Tree.h"
#include "TauHelperFunctions2.h"
//---------------------------------------------------------------------------
class SampleCounts;
int main(int argc, char *argv[]);
SampleCounts ReadSample(PsFileHelper &PsFile, string FileName, string Tag = "", double CrossSection = 1);
//---------------------------------------------------------------------------
class SampleCounts
{
public:
   string FileName;
   string Tag;
   double CrossSection;
   int AllEvents;
   int AfterBasicSelections;
   int AfterJetCut;
   int AfterBTagCut;
   int AfterJetAndElectronVeto;
   int AfterJetAndLeptonVeto;
   int AfterMRStar200Cut;
   int AfterRStar020Cut;
   int AfterMRStar400Cut;
   int AfterRStar050Cut;
   TH1D *HMR;
   TH1D *HMRStar;
   TH1D *HR;
   TH1D *HRStar;
   TH1D *HMR_R020Cut;
   TH1D *HMRStar_RStar020Cut;
   TH1D *HMR_R050Cut;
   TH1D *HMRStar_RStar050Cut;
   TH2D *HMRR;
   TH2D *HMRStarRStar;

public:
   SampleCounts() : HMR(0), HR(0), HMR_R020Cut(0) {}
   ~SampleCounts() {}
   void CleanHistograms()
   {
      if(HMR != NULL)               delete HMR;
      if(HR != NULL)                delete HR;
      if(HMRR != NULL)          delete HMRR;
      if(HMR_R020Cut != NULL)   delete HMR_R020Cut;
      if(HMR_R050Cut != NULL)   delete HMR_R050Cut;
   }
};
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   PsFileHelper PsFile("SimpleCutTable.ps");
   PsFile.AddTextPage("Simple Cut Efficiency Table");

   vector<SampleCounts> Samples;

   Samples.push_back(ReadSample(PsFile, "Samples/LQ350_LQ3Tree.root", "LQ350", 0.477));
   Samples.push_back(ReadSample(PsFile, "Samples/LQ450_LQ3Tree.root", "LQ450", 0.0949));
   Samples.push_back(ReadSample(PsFile, "Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_all.root", "TTbar", 165));
   Samples.push_back(ReadSample(PsFile, "Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_all.root", "W", 31314));
   Samples.push_back(ReadSample(PsFile, "Samples/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola_all.root", "ZZ", 5.9));
   Samples.push_back(ReadSample(PsFile, "Samples/WZtoAnything_TuneZ2_7TeV-pythia6-tauola_all.root", "WZ", 18.2));
   Samples.push_back(ReadSample(PsFile, "Samples/WWtoAnything_TuneZ2_7TeV-pythia6-tauola_all.root", "WW", 43));
   // Samples.push_back(ReadSample(PsFile, "Samples/PhotonVJets_7TeV-madgraph_all.root", "GammaVJet", 173));
   Samples.push_back(ReadSample(PsFile, "Samples/DYJetsToLL_TuneD6T_M-10To50_7TeV-madgraph-tauola_all.root",
      "DY_10_50", 3100));   // Guessed
   Samples.push_back(ReadSample(PsFile, "Samples/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola_all.root",
      "DY_50", 3048));

   PsFile.AddTextPage("Summary tables");

   TFile F("XD.root", "RECREATE");

   TH2D HExpectedYieldSummary("HExpectedYieldSummary", "Expected yield in 1/fb",
      Samples.size(), 0, Samples.size(), 10, 0, 10);
   TH2D HExpectedYieldSummaryTranspose("HExpectedYieldSummaryTranspose", "Expected yield in 1/fb",
      10, 0, 10, Samples.size(), 0, Samples.size());
   HExpectedYieldSummary.SetStats(0);
   HExpectedYieldSummaryTranspose.SetStats(0);

   HExpectedYieldSummary.GetYaxis()->SetBinLabel(1, "All");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(2, "Jet ID");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(3, "Two Jet PT 60");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(4, "B Tag");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(5, "Electron");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(6, "Muon");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(7, "MR* 200");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(8, "R* 0.20");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(9, "MR* 400");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(10, "R* 0.4");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(1, "All");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(2, "Jet ID");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(3, "Two Jet PT 60");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(4, "B Tag");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(5, "Electron");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(6, "Muon");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(7, "MR* 200");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(8, "R* 0.20");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(9, "MR* 400");
   HExpectedYieldSummaryTranspose.GetXaxis()->SetBinLabel(10, "R* 0.4");

   const double IntegratedLuminosity = 1000;   // 1/fb

   for(int i = 0; i < (int)Samples.size(); i++)
   {
      HExpectedYieldSummary.GetXaxis()->SetBinLabel(i + 1, Samples[i].Tag.c_str());
      HExpectedYieldSummaryTranspose.GetYaxis()->SetBinLabel(i + 1, Samples[i].Tag.c_str());

      double Factor = Samples[i].CrossSection / Samples[i].AllEvents * IntegratedLuminosity;

      HExpectedYieldSummary.SetBinContent(i + 1, 1, Samples[i].AllEvents * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 2, Samples[i].AfterBasicSelections * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 3, Samples[i].AfterJetCut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 4, Samples[i].AfterBTagCut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 5, Samples[i].AfterJetAndElectronVeto * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 6, Samples[i].AfterJetAndLeptonVeto * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 7, Samples[i].AfterMRStar200Cut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 8, Samples[i].AfterRStar020Cut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 9, Samples[i].AfterMRStar400Cut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 10, Samples[i].AfterRStar050Cut * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(1, i + 1, Samples[i].AllEvents * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(2, i + 1, Samples[i].AfterBasicSelections * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(3, i + 1, Samples[i].AfterJetCut * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(4, i + 1, Samples[i].AfterBTagCut * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(5, i + 1, Samples[i].AfterJetAndElectronVeto * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(6, i + 1, Samples[i].AfterJetAndLeptonVeto * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(7, i + 1, Samples[i].AfterMRStar200Cut * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(8, i + 1, Samples[i].AfterRStar020Cut * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(9, i + 1, Samples[i].AfterMRStar400Cut * Factor);
      HExpectedYieldSummaryTranspose.SetBinContent(10, i + 1, Samples[i].AfterRStar050Cut * Factor);
   }

   PsFile.AddPlot(HExpectedYieldSummary, "text90 colz", false, true);
   // PsFile.AddPlot(HExpectedYieldSummary, "text90");

   TCanvas ExpectedYieldCanvas("ExpectedYieldCanvas", "ExpectedYieldCanvas", 1024, 1024);
   HExpectedYieldSummaryTranspose.Draw("text30 colz");
   ExpectedYieldCanvas.SetLogz();
   ExpectedYieldCanvas.SaveAs("ExpectedYield.png");
   ExpectedYieldCanvas.SaveAs("ExpectedYield.C");
   ExpectedYieldCanvas.SaveAs("ExpectedYield.eps");

   TCanvas MRStarCurveCanvas;
   TLegend MRStarCurveLegend(0.65, 0.85, 0.85, 0.35);
   double Maximum = 0;
   for(int i = 0; i < (int)Samples.size(); i++)
      if(Maximum < Samples[i].HMRStar_RStar050Cut->GetMaximum())
         Maximum = Samples[i].HMRStar_RStar050Cut->GetMaximum();
   for(int i = 0; i < (int)Samples.size(); i++)
   {
      Samples[i].HMRStar_RStar050Cut->SetMaximum(Maximum * 2);
      Samples[i].HMRStar_RStar050Cut->SetLineColor(i + 1);
      MRStarCurveLegend.AddEntry(Samples[i].HMRStar_RStar050Cut, Samples[i].Tag.c_str(), "l");

      if(i == 0)
      {
         Samples[i].HMRStar_RStar050Cut->SetTitle("Comparison of MRStar distribution under RStar 0.5 cut");
         Samples[i].HMRStar_RStar050Cut->Draw("");
      }
      else
         Samples[i].HMRStar_RStar050Cut->Draw("same");
   }
   MRStarCurveLegend.SetFillColor(0);
   MRStarCurveLegend.Draw();
   MRStarCurveCanvas.SetLogy();
   PsFile.AddCanvas(MRStarCurveCanvas);

   TCanvas MRCurveCanvas;
   TLegend MRCurveLegend(0.65, 0.85, 0.85, 0.35);
   Maximum = 0;
   for(int i = 0; i < (int)Samples.size(); i++)
      if(Maximum < Samples[i].HMR_R050Cut->GetMaximum())
         Maximum = Samples[i].HMR_R050Cut->GetMaximum();
   for(int i = 0; i < (int)Samples.size(); i++)
   {
      Samples[i].HMR_R050Cut->SetMaximum(Maximum * 2);
      Samples[i].HMR_R050Cut->SetLineColor(i + 1);
      MRCurveLegend.AddEntry(Samples[i].HMR_R050Cut, Samples[i].Tag.c_str(), "l");

      if(i == 0)
      {
         Samples[i].HMR_R050Cut->SetTitle("Comparison of MR distribution under R 0.5 cut");
         Samples[i].HMR_R050Cut->Draw("");
      }
      else
         Samples[i].HMR_R050Cut->Draw("same");
   }
   MRCurveLegend.SetFillColor(0);
   MRCurveLegend.Draw();
   MRCurveCanvas.SetLogy();
   PsFile.AddCanvas(MRCurveCanvas);

   TH1D *HSMOnly = (TH1D *)(Samples[2].HMR_R050Cut->Clone("HSMOnly"));
   TH1D *HSMWithLQ350 = (TH1D *)(Samples[2].HMR_R050Cut->Clone("HSMOnly"));
   TH1D *HSMWithLQ450 = (TH1D *)(Samples[2].HMR_R050Cut->Clone("HSMOnly"));
   for(int i = 3; i < (int)Samples.size(); i++)
   {
      HSMOnly->Add(Samples[i].HMR_R050Cut);
      HSMWithLQ350->Add(Samples[i].HMR_R050Cut);
      HSMWithLQ450->Add(Samples[i].HMR_R050Cut);
   }
   HSMWithLQ350->Add(Samples[0].HMR_R050Cut);
   HSMWithLQ450->Add(Samples[1].HMR_R050Cut);

   HSMOnly->SetTitle("SM only vs. Signal LQ, under R 0.50 cut");

   TCanvas LQ350Case;
   HSMOnly->SetLineColor(kBlack);
   HSMOnly->Draw();
   HSMWithLQ350->SetLineColor(kGreen);
   HSMWithLQ350->Draw("same");
   Samples[0].HMR_R050Cut->SetLineColor(kBlue);
   Samples[0].HMR_R050Cut->Draw("same");
   LQ350Case.SetLogy();
   PsFile.AddCanvas(LQ350Case);

   TCanvas LQ450Case;
   HSMOnly->SetLineColor(kBlack);
   HSMOnly->Draw();
   HSMWithLQ450->SetLineColor(kGreen);
   HSMWithLQ450->Draw("same");
   Samples[1].HMR_R050Cut->SetLineColor(kBlue);
   Samples[1].HMR_R050Cut->Draw("same");
   LQ450Case.SetLogy();
   PsFile.AddCanvas(LQ450Case);

   TCanvas LQ350CaseSquare("LQ350CaseSquare", "LQ350CaseSquare", 1024, 1024);
   HSMOnly->SetLineColor(kBlack);
   HSMOnly->SetStats(0);
   HSMOnly->SetLineWidth(2);
   HSMOnly->Draw();
   Samples[0].HMR_R050Cut->SetLineColor(kRed);
   Samples[0].HMR_R050Cut->SetStats(0);
   Samples[0].HMR_R050Cut->SetLineWidth(2);
   Samples[0].HMR_R050Cut->Draw("same");
   LQ350CaseSquare.SetLogy();
   TLegend LQ350CaseLegend(0.4, 0.8, 0.8, 0.6);
   LQ350CaseLegend.AddEntry(Samples[0].HMR_R050Cut, "LQ 350", "l");
   LQ350CaseLegend.AddEntry(HSMOnly, "Total SM background", "l");
   LQ350CaseLegend.SetFillColor(0);
   LQ350CaseLegend.Draw();
   LQ350CaseSquare.SaveAs("LQ350CaseSquare.png");
   LQ350CaseSquare.SaveAs("LQ350CaseSquare.C");
   LQ350CaseSquare.SaveAs("LQ350CaseSquare.eps");

   TCanvas Canvas2D("Canvas2D", "Canvas2D", 1024, 512);
   Canvas2D.Divide(2);
   Canvas2D.cd(1);
   TH2D *HSMOnly2D = (TH2D *)(Samples[2].HMRStarRStar->Clone("HSMOnly2D"));
   for(int i = 3; i < (int)Samples.size(); i++)
      HSMOnly2D->Add(Samples[i].HMRStarRStar);
   HSMOnly2D->Draw("colz");
   Canvas2D.cd(2);
   Samples[0].HMRStarRStar->Draw();
   Canvas2D.SaveAs("MRStarRStar.png");
   Canvas2D.SaveAs("MRStarRStar.C");
   Canvas2D.SaveAs("MRStarRStar.eps");

   HExpectedYieldSummary.Write();

   F.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   for(int i = 0; i < (int)Samples.size(); i++)
      Samples[i].CleanHistograms();

   return 0;
}
//---------------------------------------------------------------------------
SampleCounts ReadSample(PsFileHelper &PsFile, string FileName, string Tag, double CrossSection)
{
   cout << "Start processing file \"" << FileName << "\" with tag \"" << Tag << "\"" << endl;

   SampleCounts Result;
   Result.FileName = FileName;
   Result.Tag = Tag;
   Result.CrossSection = CrossSection;
   Result.AllEvents = 0;
   Result.AfterBasicSelections = 0;
   Result.AfterJetCut = 0;
   Result.AfterBTagCut = 0;
   Result.AfterJetAndElectronVeto = 0;
   Result.AfterJetAndLeptonVeto = 0;
   Result.AfterMRStar200Cut = 0;
   Result.AfterRStar020Cut = 0;
   Result.AfterMRStar400Cut = 0;
   Result.AfterRStar050Cut = 0;

   Result.HMR = new TH1D(Form("HMR_%s", Tag.c_str()), Form("MR, (%s);MR", Tag.c_str()), 40, 0, 1500);
   Result.HMRStar = new TH1D(Form("HMRStar_%s", Tag.c_str()), Form("MRStar, (%s);MRStar", Tag.c_str()), 40, 0, 1500);
   Result.HR = new TH1D(Form("HR_%s", Tag.c_str()), Form("R, (%s);R", Tag.c_str()), 40, 0, 1.5);
   Result.HRStar = new TH1D(Form("HRStar_%s", Tag.c_str()), Form("RStar, (%s);RStar", Tag.c_str()), 40, 0, 1.5);
   Result.HMRR = new TH2D(Form("HMRR_%s", Tag.c_str()),
      Form("MR vs. R, (%s);MR;R", Tag.c_str()), 40, 0, 1500, 50, 0, 1.5);
   Result.HMRStarRStar = new TH2D(Form("HMRStarRStar_%s", Tag.c_str()),
      Form("MRStar vs. RStar, (%s);MRStar;RStar", Tag.c_str()), 40, 0, 1500, 50, 0, 1.5);
   Result.HMR_R020Cut = new TH1D(Form("HMR_R020Cut_%s", Tag.c_str()),
      Form("MR, cut on R 0.20 (%s);MR", Tag.c_str()), 40, 0, 1500);
   Result.HMRStar_RStar020Cut = new TH1D(Form("HMRStar_RStar020Cut_%s", Tag.c_str()),
      Form("MRStar, cut on RStar 0.20 (%s);MRStar", Tag.c_str()), 40, 0, 1500);
   Result.HMR_R050Cut = new TH1D(Form("HMR_R050Cut_%s", Tag.c_str()),
      Form("MR, cut on R 0.50 (%s);MR", Tag.c_str()), 40, 0, 1500);
   Result.HMRStar_RStar050Cut = new TH1D(Form("HMRStar_RStar050Cut_%s", Tag.c_str()),
      Form("MRStar, cut on RStar 0.50 (%s);MRStar", Tag.c_str()), 40, 0, 1500);

   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("LQ3Tree");

   if(Tree == NULL)
      return Result;

   TreeRecord M;
   M.SetBranchAddress(Tree);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree->GetEntry(iEntry);

      Result.AllEvents = Result.AllEvents + 1;

      if(M.PassCaloJetID == false || M.PassNoiseFilter == false || M.PassHLT == false)
         continue;
      Result.AfterBasicSelections = Result.AfterBasicSelections + 1;

      double CaloJetCount60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            CaloJetCount60 = CaloJetCount60 + 1;
      if(CaloJetCount60 < 2)
         continue;
      Result.AfterJetCut = Result.AfterJetCut + 1;

      int JetPassBTag = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetTCHETag[i] > 10.2 && M.CaloJetPT[i] > 100 && M.CaloJetEta[i] < 2.4 && M.CaloJetEta[i] > -2.4)
            JetPassBTag = JetPassBTag + 1;
      if(JetPassBTag < 1)
         continue;
      Result.AfterBTagCut = Result.AfterBTagCut + 1;

      if(M.GoodElectronCount >= 1)
         continue;
      Result.AfterJetAndElectronVeto = Result.AfterJetAndElectronVeto + 1;

      if(M.GoodMuonCount >= 1)
         continue;
      Result.AfterJetAndLeptonVeto = Result.AfterJetAndLeptonVeto + 1;

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

      FourVector CaloMET(0, M.CaloMET[0], M.CaloMET[1], 0);
      CaloMET[0] = CaloMET.GetPT();

      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double R = GetR(Hemispheres[0], Hemispheres[1], CaloMET);
      double MRStar = GetMRStar(Hemispheres[0], Hemispheres[1]) * GetGammaRStar(Hemispheres[0], Hemispheres[1]);
      double RStar = GetRStar(Hemispheres[0], Hemispheres[1], CaloMET);

      Result.HMR->Fill(MR);
      Result.HMRStar->Fill(MRStar);
      Result.HR->Fill(R);
      Result.HRStar->Fill(RStar);
      Result.HMRR->Fill(MR, R);
      Result.HMRStarRStar->Fill(MRStar, RStar);
      if(R > 0.20)
         Result.HMR_R020Cut->Fill(MR);
      if(RStar > 0.20)
         Result.HMRStar_RStar020Cut->Fill(MRStar);
      if(R > 0.50)
         Result.HMR_R050Cut->Fill(MR);
      if(RStar > 0.50)
         Result.HMRStar_RStar050Cut->Fill(MRStar);

      if(MRStar < 200)
         continue;
      Result.AfterMRStar200Cut = Result.AfterMRStar200Cut + 1;

      if(RStar < 0.20)
         continue;
      Result.AfterRStar020Cut = Result.AfterRStar020Cut + 1;

      if(MRStar < 400)
         continue;
      Result.AfterMRStar400Cut = Result.AfterMRStar400Cut + 1;

      if(RStar < 0.4)
         continue;
      Result.AfterRStar050Cut = Result.AfterRStar050Cut + 1;

      M.Clear();
   }

   PsFile.AddTextPage(Tag);

   TH1D HCountHistogram("HCountHistogram", Form("Count histogram for file %s", FileName.c_str()), 10, 0, 10);

   HCountHistogram.GetXaxis()->SetBinLabel(1, "All");
   HCountHistogram.GetXaxis()->SetBinLabel(2, "Jet ID");
   HCountHistogram.GetXaxis()->SetBinLabel(3, "Jet PT 60");
   HCountHistogram.GetXaxis()->SetBinLabel(4, "Jet b-tag");
   HCountHistogram.GetXaxis()->SetBinLabel(5, "Electron");
   HCountHistogram.GetXaxis()->SetBinLabel(6, "Muon");
   HCountHistogram.GetXaxis()->SetBinLabel(7, "MR* 200");
   HCountHistogram.GetXaxis()->SetBinLabel(8, "R* 0.20");
   HCountHistogram.GetXaxis()->SetBinLabel(9, "MR* 400");
   HCountHistogram.GetXaxis()->SetBinLabel(10, "R* 0.5");

   HCountHistogram.SetStats(0);

   HCountHistogram.SetBinContent(1, Result.AllEvents);
   HCountHistogram.SetBinContent(2, Result.AfterBasicSelections);
   HCountHistogram.SetBinContent(3, Result.AfterJetCut);
   HCountHistogram.SetBinContent(4, Result.AfterBTagCut);
   HCountHistogram.SetBinContent(5, Result.AfterJetAndElectronVeto);
   HCountHistogram.SetBinContent(6, Result.AfterJetAndLeptonVeto);
   HCountHistogram.SetBinContent(7, Result.AfterMRStar200Cut);
   HCountHistogram.SetBinContent(8, Result.AfterRStar020Cut);
   HCountHistogram.SetBinContent(9, Result.AfterMRStar400Cut);
   HCountHistogram.SetBinContent(10, Result.AfterRStar050Cut);

   PsFile.AddPlot(HCountHistogram, "hist text00", true);

   TH1D *HExpectedYieldHistogram = (TH1D *)HCountHistogram.Clone("HExpectedYieldHistogram");
   HExpectedYieldHistogram->SetTitle(Form("Expected yield for 1/fb (%s)", FileName.c_str()));
   HExpectedYieldHistogram->SetStats(0);
   HExpectedYieldHistogram->Scale(CrossSection * 1000 / Result.AllEvents);
   PsFile.AddPlot(HExpectedYieldHistogram, "hist text00", true);

   Result.HMR->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStar->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HR->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HRStar->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRR->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStarRStar->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMR_R020Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStar_RStar020Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMR_R050Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStar_RStar050Cut->Scale(CrossSection * 1000 / Result.AllEvents);

   PsFile.AddPlot(Result.HMR, "", true);
   PsFile.AddPlot(Result.HMRStar, "", true);
   PsFile.AddPlot(Result.HR, "", true);
   PsFile.AddPlot(Result.HRStar, "", true);
   PsFile.AddPlot(Result.HMRR, "colz", false);
   PsFile.AddPlot(Result.HMRStarRStar, "colz", false);
   PsFile.AddPlot(Result.HMR_R020Cut, "", true);
   PsFile.AddPlot(Result.HMRStar_RStar020Cut, "", true);
   PsFile.AddPlot(Result.HMR_R050Cut, "", true);
   PsFile.AddPlot(Result.HMRStar_RStar050Cut, "", true);

   return Result;
}
//---------------------------------------------------------------------------



