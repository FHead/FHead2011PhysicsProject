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
   int AfterJetCut;
   int AfterBTagCut;
   int AfterJetAndElectronVeto;
   int AfterJetAndLeptonVeto;
   int AfterBetaRCut;
   int AfterMR200Cut;
   int AfterR020Cut;
   int AfterMR400Cut;
   int AfterR050Cut;
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
   Samples.push_back(ReadSample(PsFile, "Samples/TTJets_TuneD6T.root", "TTbar", 165));
   Samples.push_back(ReadSample(PsFile, "Samples/TToBLNu_TuneZ2_s-channel_7TeV-madgraph.root", "Top_s", 4.6));
   Samples.push_back(ReadSample(PsFile, "Samples/TToBLNu_TuneZ2_t-channel_7TeV-madgraph.root", "Top_t", 64.6));
   Samples.push_back(ReadSample(PsFile, "Samples/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph.root", "Top_tW", 10.6));
   Samples.push_back(ReadSample(PsFile, "Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root",
      "W", 31314));
   Samples.push_back(ReadSample(PsFile, "Samples/ZZtoAnything_TuneZ2.root", "ZZ", 5.9));
   Samples.push_back(ReadSample(PsFile, "Samples/WZtoAnything_TuneZ2.root", "WZ", 18.2));
   Samples.push_back(ReadSample(PsFile, "Samples/WWtoAnything.root", "WW", 43));
   Samples.push_back(ReadSample(PsFile, "Samples/ZnunuMADGRAPH.root", "Znunu", 3048 * 6));   // >__<
   Samples.push_back(ReadSample(PsFile, "Samples/DYJetsToLL_TuneD6T_M-10To50_7TeV-madgraph-tauola.root",
      "DY_10_50", 3000));   // >__<
   Samples.push_back(ReadSample(PsFile, "Samples/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola.root",
      "DY_50", 3048));
   Samples.push_back(ReadSample(PsFile, "Samples/QCD_Pt-20to30_BCtoE_TuneZ2.root", "BC2E_20_30", 236000000 * 0.00056));
   Samples.push_back(ReadSample(PsFile, "Samples/QCD_Pt-30to80_BCtoE_TuneZ2.root", "BC2E_30_80", 59480000 * 0.00230));
   Samples.push_back(ReadSample(PsFile, "Samples/QCD_Pt-80to170_BCtoE_TuneZ2.root", "BC2E_80_170", 900000 * 0.0104));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_2jet_40to120.root",
      "QCD_2Jet_40_120", 8804000 * 0.527));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_2jet_120to280.root",
      "QCD_2Jet_120_280", 36260 * 0.296));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_2jet_280to500.root",
      "QCD_2Jet_280_500", 377.1 * 0.240));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_2jet_500to5000.root",
      "QCD_2Jet_500_5000", 13.14 * 0.251));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_3jet_40to120.root",
      "QCD_3Jet_40_120", 3425000 * 0.303));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_3jet_120to280.root",
      "QCD_3Jet_120_280", 50100 * 0.226));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_3jet_280to500.root",
      "QCD_3Jet_280_500", 651.7 * 0.185));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_3jet_500to5000.root",
      "QCD_3Jet_500_5000", 22.73 * 0.185));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_4jet_40to120.root",
      "QCD_4Jet_40_120", 467000 * 0.200));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_4jet_120to280.root",
      "QCD_4Jet_120_280", 25680 * 0.174));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_4jet_280to500.root",
      "QCD_4Jet_280_500", 470.8 * 0.143));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_4jet_500to5000.root",
      "QCD_4Jet_500_5000", 17.97 * 0.142));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_5jet_40to120.root",
      "QCD_5Jet_40_120", 64230 * 0.136));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_5jet_120to280.root",
      "QCD_5Jet_120_280", 8187 * 0.130));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_5jet_280to500.root",
      "QCD_5Jet_280_500", 232.9 * 0.116));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_5jet_500to5000.root",
      "QCD_5Jet_500_5000", 9.325 * 0.110));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_6jet_40to120.root",
      "QCD_6Jet_40_120", 9800 * 0.118));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_6jet_120to280.root",
      "QCD_6Jet_120_280", 2656 * 0.131));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_6jet_280to500.root",
      "QCD_6Jet_280_500", 123.8 * 0.137));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_6jet_500to5000.root",
      "QCD_6Jet_500_5000", 6.194 * 0.148));

   PsFile.AddTextPage("Summary tables");

   TFile F("XD.root", "RECREATE");

   TH2D HExpectedYieldSummary("HExpectedYieldSummary", "Expected yield in 1/fb",
      Samples.size(), 0, Samples.size(), 10, 0, 10);
   HExpectedYieldSummary.SetStats(0);

   HExpectedYieldSummary.GetYaxis()->SetBinLabel(1, "All");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(2, "Two Jet PT 60");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(3, "B Tag");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(4, "Electron");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(5, "Muon");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(6, "BetaR");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(7, "MR 200");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(8, "R 0.20");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(9, "MR 400");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(10, "R 0.4");

   const double IntegratedLuminosity = 1000;   // 1/fb

   for(int i = 0; i < (int)Samples.size(); i++)
   {
      HExpectedYieldSummary.GetXaxis()->SetBinLabel(i + 1, Samples[i].Tag.c_str());

      double Factor = Samples[i].CrossSection / Samples[i].AllEvents * IntegratedLuminosity;

      HExpectedYieldSummary.SetBinContent(i + 1, 1, Samples[i].AllEvents * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 2, Samples[i].AfterJetCut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 3, Samples[i].AfterBTagCut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 4, Samples[i].AfterJetAndElectronVeto * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 5, Samples[i].AfterJetAndLeptonVeto * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 6, Samples[i].AfterBetaRCut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 7, Samples[i].AfterMR200Cut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 8, Samples[i].AfterR020Cut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 9, Samples[i].AfterMR400Cut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 10, Samples[i].AfterR050Cut * Factor);
   }

   PsFile.AddPlot(HExpectedYieldSummary, "text90 colz", false, true);
   // PsFile.AddPlot(HExpectedYieldSummary, "text90");

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

   HSMOnly->SetTitle("SM only vs. SM + LQ");

   TCanvas LQ350Case;
   HSMOnly->SetLineColor(kBlack);
   HSMOnly->Draw();
   HSMWithLQ450->SetLineColor(kGreen);
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
   Result.AfterJetCut = 0;
   Result.AfterBTagCut = 0;
   Result.AfterJetAndElectronVeto = 0;
   Result.AfterJetAndLeptonVeto = 0;
   Result.AfterBetaRCut = 0;
   Result.AfterMR200Cut = 0;
   Result.AfterR020Cut = 0;
   Result.AfterMR400Cut = 0;
   Result.AfterR050Cut = 0;

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

      double CaloJetCount60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            CaloJetCount60 = CaloJetCount60 + 1;
      if(CaloJetCount60 < 2)
         continue;
      Result.AfterJetCut = Result.AfterJetCut + 1;

      int JetPassBTag = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetTCHETag[i] > 1.7 && M.CaloJetPT[i] > 30 && M.CaloJetEta[i] < 2.4 && M.CaloJetEta[i] > -2.4)
            JetPassBTag = JetPassBTag + 1;
      if(JetPassBTag < 2)
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

      double BetaR = (Hemispheres[0][0] - Hemispheres[1][0]) / (Hemispheres[0][3] - Hemispheres[1][3]);
      if(BetaR < -0.99 || BetaR > 0.99)
         continue;
      Result.AfterBetaRCut = Result.AfterBetaRCut + 1;

      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double R = GetR(Hemispheres[0], Hemispheres[1], CaloMET);
      double MRStar = GetMRStar(Hemispheres[0], Hemispheres[1]);
      double RStar = GetRStar(Hemispheres[0], Hemispheres[1], CaloMET) / GetGammaRStar(Hemispheres[0], Hemispheres[1]);

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

      if(MR < 200)
         continue;
      Result.AfterMR200Cut = Result.AfterMR200Cut + 1;

      if(R < 0.20)
         continue;
      Result.AfterR020Cut = Result.AfterR020Cut + 1;

      if(MR < 400)
         continue;
      Result.AfterMR400Cut = Result.AfterMR400Cut + 1;

      if(R < 0.4)
         continue;
      Result.AfterR050Cut = Result.AfterR050Cut + 1;

      M.Clear();
   }

   PsFile.AddTextPage(Tag);

   TH1D HCountHistogram("HCountHistogram", Form("Count histogram for file %s", FileName.c_str()), 11, 0, 11);

   HCountHistogram.GetXaxis()->SetBinLabel(1, "All");
   HCountHistogram.GetXaxis()->SetBinLabel(2, "Jet PT 60");
   HCountHistogram.GetXaxis()->SetBinLabel(3, "Jet b-tag");
   HCountHistogram.GetXaxis()->SetBinLabel(4, "Electron");
   HCountHistogram.GetXaxis()->SetBinLabel(5, "Muon");
   HCountHistogram.GetXaxis()->SetBinLabel(6, "BetaR");
   HCountHistogram.GetXaxis()->SetBinLabel(7, "MR 200");
   HCountHistogram.GetXaxis()->SetBinLabel(8, "R 0.20");
   HCountHistogram.GetXaxis()->SetBinLabel(9, "MR 400");
   HCountHistogram.GetXaxis()->SetBinLabel(10, "R 0.5");

   HCountHistogram.SetStats(0);

   HCountHistogram.SetBinContent(1, Result.AllEvents);
   HCountHistogram.SetBinContent(2, Result.AfterJetCut);
   HCountHistogram.SetBinContent(3, Result.AfterBTagCut);
   HCountHistogram.SetBinContent(4, Result.AfterJetAndElectronVeto);
   HCountHistogram.SetBinContent(5, Result.AfterJetAndLeptonVeto);
   HCountHistogram.SetBinContent(6, Result.AfterBetaRCut);
   HCountHistogram.SetBinContent(7, Result.AfterMR200Cut);
   HCountHistogram.SetBinContent(8, Result.AfterR020Cut);
   HCountHistogram.SetBinContent(9, Result.AfterMR400Cut);
   HCountHistogram.SetBinContent(10, Result.AfterR050Cut);

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



