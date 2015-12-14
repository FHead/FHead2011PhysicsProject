// //---------------------------------------------------------------------------
#include <iostream>
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
//---------------------------------------------------------------------------
struct SampleCounts;
int main(int argc, char *argv[]);
SampleCounts ReadSample(PsFileHelper &PsFile, string FileName);
//---------------------------------------------------------------------------
struct SampleCounts
{
   int AllEvents;
   int AfterJetCut;
   int AfterJetAndMETCut;
   int AfterJetMETAndElectronVeto;
   int AfterJetMETAndLeptonVeto;
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

   ReadSample(PsFile, "Samples/TTJets_TuneD6T.root");
   // ReadSample(PsFile, "Samples/TTJets_TuneD6T_1.root");
   // ReadSample(PsFile, "Samples/TTJets_TuneD6T_2.root");
   // ReadSample(PsFile, "Samples/TTJets_TuneD6T_3.root");
   // ReadSample(PsFile, "Samples/TTJets_TuneD6T_4.root");
   // ReadSample(PsFile, "Samples/TTJets_TuneD6T_5.root");
   // ReadSample(PsFile, "Samples/TTJets_TuneD6T_6.root");
   // ReadSample(PsFile, "Samples/TTJets_TuneD6T_8.root");
   // ReadSample(PsFile, "Samples/LQ350_LQ3Tree.root");
   // ReadSample(PsFile, "Samples/LQ450_LQ3Tree.root");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}
//---------------------------------------------------------------------------
SampleCounts ReadSample(PsFileHelper &PsFile, string FileName)
{
   SampleCounts Result;
   Result.AllEvents = 0;
   Result.AfterJetCut = 0;
   Result.AfterJetAndMETCut = 0;
   Result.AfterJetMETAndElectronVeto = 0;
   Result.AfterJetMETAndLeptonVeto = 0;

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

      if(M.PFMET[0] * M.PFMET[0] + M.PFMET[1] * M.PFMET[1] < 50 * 50)
         continue;
      Result.AfterJetAndMETCut = Result.AfterJetAndMETCut + 1;

      if(M.GoodElectronCount >= 1)
         continue;
      Result.AfterJetMETAndElectronVeto = Result.AfterJetMETAndElectronVeto + 1;

      if(M.GoodMuonCount >= 1)
         continue;
      Result.AfterJetMETAndLeptonVeto = Result.AfterJetMETAndLeptonVeto + 1;

      M.Clear();
   }

   TH1D HCountHistogram("HCountHistogram", Form("Count histogram for file %s", FileName.c_str()), 5, -0.5, 4.5);

   HCountHistogram.GetXaxis()->SetBinLabel(1, "All");
   HCountHistogram.GetXaxis()->SetBinLabel(2, "Jet PT 50");
   HCountHistogram.GetXaxis()->SetBinLabel(3, "MET 50");
   HCountHistogram.GetXaxis()->SetBinLabel(4, "Electron");
   HCountHistogram.GetXaxis()->SetBinLabel(5, "Muon");

   HCountHistogram.SetStats(0);

   HCountHistogram.SetBinContent(1, Result.AllEvents);
   HCountHistogram.SetBinContent(2, Result.AfterJetCut);
   HCountHistogram.SetBinContent(3, Result.AfterJetAndMETCut);
   HCountHistogram.SetBinContent(4, Result.AfterJetMETAndElectronVeto);
   HCountHistogram.SetBinContent(5, Result.AfterJetMETAndLeptonVeto);

   PsFile.AddPlot(HCountHistogram, "hist text00", true);

   return Result;
}
//---------------------------------------------------------------------------



