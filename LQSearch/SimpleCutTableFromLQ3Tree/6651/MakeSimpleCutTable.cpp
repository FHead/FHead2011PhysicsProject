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
//---------------------------------------------------------------------------
#include "PlotHelper2.h"
#include "ReadLQ3Tree.h"
#include "TauHelperFunctions2.h"
//---------------------------------------------------------------------------
struct SampleCounts;
int main(int argc, char *argv[]);
SampleCounts ReadSample(PsFileHelper &PsFile, string FileName, string Tag = "", double CrossSection = 1);
//---------------------------------------------------------------------------
struct SampleCounts
{
   string FileName;
   string Tag;
   double CrossSection;
   int AllEvents;
   int AfterJetCut;
   int AfterBTagCut;
   int AfterJetAndMETCut;
   int AfterJetMETAndElectronVeto;
   int AfterJetMETAndLeptonVeto;
   int AfterBetaRCut;
   int AfterMR200Cut;
   int AfterR015Cut;
   int AfterMR400Cut;
   int AfterR04Cut;
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
   Samples.push_back(ReadSample(PsFile, "Samples/TToBLNu_TuneZ2_s-channel_7TeV-madgraph.root", "Top(s)", 4.6));
   Samples.push_back(ReadSample(PsFile, "Samples/TToBLNu_TuneZ2_t-channel_7TeV-madgraph.root", "Top(t)", 64.6));
   Samples.push_back(ReadSample(PsFile, "Samples/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph.root", "Top(tW)", 10.6));
   Samples.push_back(ReadSample(PsFile, "Samples/ZZtoAnything_TuneZ2.root", "ZZ", 5.9));
   Samples.push_back(ReadSample(PsFile, "Samples/WZtoAnything_TuneZ2.root", "WZ", 18.2));
   Samples.push_back(ReadSample(PsFile, "Samples/WWtoAnything.root", "WW", 43));
   Samples.push_back(ReadSample(PsFile, "Samples/ZnunuMADGRAPH.root", "Znunu", 3048 * 6));   // >__<
   Samples.push_back(ReadSample(PsFile, "Samples/DYJetsToLL_TuneD6T_M-10To50_7TeV-madgraph-tauola.root",
      "DY 10-50", 3000));   // >__<
   Samples.push_back(ReadSample(PsFile, "Samples/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola.root",
      "DY 50", 3048));
   Samples.push_back(ReadSample(PsFile, "Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root",
      "W", 31314));
   Samples.push_back(ReadSample(PsFile, "Samples/QCD_Pt-20to30_BCtoE_TuneZ2.root", "BC2E 20-30", 236000000 * 0.00056));
   Samples.push_back(ReadSample(PsFile, "Samples/QCD_Pt-30to80_BCtoE_TuneZ2.root", "BC2E 30-80", 59480000 * 0.00230));
   Samples.push_back(ReadSample(PsFile, "Samples/QCD_Pt-80to170_BCtoE_TuneZ2.root", "BC2E 80-170", 900000 * 0.0104));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_2jet_40to120.root",
      "QCD_2Jet_40-120", 8804000 * 0.527));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_2jet_120to280.root",
      "QCD_2Jet_120-280", 36260 * 0.296));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_2jet_280to500.root",
      "QCD_2Jet_280-500", 377.1 * 0.240));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_2jet_500to5000.root",
      "QCD_2Jet_500-5000", 13.14 * 0.251));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_3jet_40to120.root",
      "QCD_3Jet_40-120", 3425000 * 0.303));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_3jet_120to280.root",
      "QCD_3Jet_120-280", 50100 * 0.226));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_3jet_280to500.root",
      "QCD_3Jet_280-500", 651.7 * 0.185));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_3jet_500to5000.root",
      "QCD_3Jet_500-5000", 22.73 * 0.185));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_4jet_40to120.root",
      "QCD_4Jet_40-120", 467000 * 0.200));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_4jet_120to280.root",
      "QCD_4Jet_120-280", 25680 * 0.174));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_4jet_280to500.root",
      "QCD_4Jet_280-500", 470.8 * 0.143));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_4jet_500to5000.root",
      "QCD_4Jet_500-5000", 17.97 * 0.142));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_5jet_40to120.root",
      "QCD_5Jet_40-120", 64230 * 0.136));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_5jet_120to280.root",
      "QCD_5Jet_120-280", 8187 * 0.130));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_5jet_280to500.root",
      "QCD_5Jet_280-500", 232.9 * 0.116));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_5jet_500to5000.root",
      "QCD_5Jet_500-5000", 9.325 * 0.110));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_6jet_40to120.root",
      "QCD_6Jet_40-120", 9800 * 0.118));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_6jet_120to280.root",
      "QCD_6Jet_120-280", 2656 * 0.131));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_6jet_280to500.root",
      "QCD_6Jet_280-500", 123.8 * 0.137));
   Samples.push_back(ReadSample(PsFile, "Samples/CopiedFromT3SUSY_QCD_6jet_500to5000.root",
      "QCD_6Jet_500-5000", 6.194 * 0.148));

   PsFile.AddTextPage("Summary tables");

   TFile F("XD.root", "RECREATE");

   TH2D HExpectedYieldSummary("HExpectedYieldSummary", "Expected yield in 1/fb",
      Samples.size(), 0, Samples.size(), 11, 0, 11);
   HExpectedYieldSummary.SetStats(0);

   HExpectedYieldSummary.GetYaxis()->SetBinLabel(1, "All");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(2, "Jet PT 50");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(3, "B Tag");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(4, "MET 50");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(5, "Electron");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(6, "Muon");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(7, "BetaR");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(8, "MR 200");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(9, "R 0.15");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(10, "MR 400");
   HExpectedYieldSummary.GetYaxis()->SetBinLabel(11, "R 0.4");

   const double IntegratedLuminosity = 1000;   // 1/fb

   for(int i = 0; i < (int)Samples.size(); i++)
   {
      HExpectedYieldSummary.GetXaxis()->SetBinLabel(i + 1, Samples[i].Tag.c_str());

      double Factor = Samples[i].CrossSection / Samples[i].AllEvents * IntegratedLuminosity;

      HExpectedYieldSummary.SetBinContent(i + 1, 1, Samples[i].AllEvents * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 2, Samples[i].AfterJetCut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 3, Samples[i].AfterBTagCut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 4, Samples[i].AfterJetAndMETCut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 5, Samples[i].AfterJetMETAndElectronVeto * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 6, Samples[i].AfterJetMETAndLeptonVeto * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 7, Samples[i].AfterBetaRCut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 8, Samples[i].AfterMR200Cut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 9, Samples[i].AfterR015Cut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 10, Samples[i].AfterMR400Cut * Factor);
      HExpectedYieldSummary.SetBinContent(i + 1, 11, Samples[i].AfterR04Cut * Factor);
   }
   
   PsFile.AddPlot(HExpectedYieldSummary, "text90 colz", false, true);
   // PsFile.AddPlot(HExpectedYieldSummary, "text90");

   HExpectedYieldSummary.Write();

   F.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

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
   Result.AfterJetAndMETCut = 0;
   Result.AfterJetMETAndElectronVeto = 0;
   Result.AfterJetMETAndLeptonVeto = 0;
   Result.AfterBetaRCut = 0;
   Result.AfterMR200Cut = 0;
   Result.AfterR015Cut = 0;
   Result.AfterMR400Cut = 0;
   Result.AfterR04Cut = 0;

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

      if(M.PFJetCount50 < 2)
         continue;
      Result.AfterJetCut = Result.AfterJetCut + 1;

      bool AnyLargeJetPassBTag = false;
      for(int i = 0; i < M.PFJetCount; i++)
         if(M.PFJetCSVMTag[i] > 0.1 && M.PFJetPT[i] > 50)
            AnyLargeJetPassBTag = true;
      if(AnyLargeJetPassBTag == false)
         continue;
      Result.AfterBTagCut = Result.AfterBTagCut + 1;

      if(M.PFMET[0] * M.PFMET[0] + M.PFMET[1] * M.PFMET[1] < 50 * 50)
         continue;
      Result.AfterJetAndMETCut = Result.AfterJetAndMETCut + 1;

      if(M.GoodElectronCount >= 1)
         continue;
      Result.AfterJetMETAndElectronVeto = Result.AfterJetMETAndElectronVeto + 1;

      if(M.GoodMuonCount >= 1)
         continue;
      Result.AfterJetMETAndLeptonVeto = Result.AfterJetMETAndLeptonVeto + 1;
      
      vector<FourVector> PFJets;
      for(int i = 0; i < M.PFJetCount30; i++)
      {
         if(M.PFJetPT[i] < 30)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.PFJetPT[i], M.PFJetEta[i], M.PFJetPhi[i]);
         PFJets.push_back(NewJet);
      }
      vector<FourVector> Hemispheres = SplitIntoGroups(PFJets);

      double BetaR = (Hemispheres[0][0] - Hemispheres[1][0]) / (Hemispheres[0][3] - Hemispheres[1][3]);
      if(BetaR < -0.99 || BetaR > 0.99)
         continue;
      Result.AfterBetaRCut = Result.AfterBetaRCut + 1;

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);
      PFMET[0] = PFMET.GetPT();
      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double R = GetR(Hemispheres[0], Hemispheres[1], PFMET);

      if(MR < 200)
         continue;
      Result.AfterMR200Cut = Result.AfterMR200Cut + 1;
      
      if(R < 0.15)
         continue;
      Result.AfterR015Cut = Result.AfterR015Cut + 1;

      if(MR < 400)
         continue;
      Result.AfterMR400Cut = Result.AfterMR400Cut + 1;
      
      if(R < 0.4)
         continue;
      Result.AfterR04Cut = Result.AfterR04Cut + 1;

      M.Clear();
   }

   PsFile.AddTextPage(Tag);

   TH1D HCountHistogram("HCountHistogram", Form("Count histogram for file %s", FileName.c_str()), 11, 0, 11);

   HCountHistogram.GetXaxis()->SetBinLabel(1, "All");
   HCountHistogram.GetXaxis()->SetBinLabel(2, "Jet PT 50");
   HCountHistogram.GetXaxis()->SetBinLabel(3, "Jet b-tag");
   HCountHistogram.GetXaxis()->SetBinLabel(4, "MET 50");
   HCountHistogram.GetXaxis()->SetBinLabel(5, "Electron");
   HCountHistogram.GetXaxis()->SetBinLabel(6, "Muon");
   HCountHistogram.GetXaxis()->SetBinLabel(7, "BetaR");
   HCountHistogram.GetXaxis()->SetBinLabel(8, "MR 200");
   HCountHistogram.GetXaxis()->SetBinLabel(9, "R 0.15");
   HCountHistogram.GetXaxis()->SetBinLabel(10, "MR 400");
   HCountHistogram.GetXaxis()->SetBinLabel(11, "R 0.4");

   HCountHistogram.SetStats(0);

   HCountHistogram.SetBinContent(1, Result.AllEvents);
   HCountHistogram.SetBinContent(2, Result.AfterJetCut);
   HCountHistogram.SetBinContent(3, Result.AfterBTagCut);
   HCountHistogram.SetBinContent(4, Result.AfterJetAndMETCut);
   HCountHistogram.SetBinContent(5, Result.AfterJetMETAndElectronVeto);
   HCountHistogram.SetBinContent(6, Result.AfterJetMETAndLeptonVeto);
   HCountHistogram.SetBinContent(7, Result.AfterBetaRCut);
   HCountHistogram.SetBinContent(8, Result.AfterMR200Cut);
   HCountHistogram.SetBinContent(9, Result.AfterR015Cut);
   HCountHistogram.SetBinContent(10, Result.AfterMR400Cut);
   HCountHistogram.SetBinContent(11, Result.AfterR04Cut);

   PsFile.AddPlot(HCountHistogram, "hist text00", true);

   TH1D *HExpectedYieldHistogram = (TH1D *)HCountHistogram.Clone("HExpectedYieldHistogram");
   HExpectedYieldHistogram->SetTitle(Form("Expected yield for 1/fb (%s)", FileName.c_str()));
   HExpectedYieldHistogram->SetStats(0);
   HExpectedYieldHistogram->Scale(CrossSection * 1000 / Result.AllEvents);
   PsFile.AddPlot(HExpectedYieldHistogram, "hist text00", true);

   return Result;
}
//---------------------------------------------------------------------------



