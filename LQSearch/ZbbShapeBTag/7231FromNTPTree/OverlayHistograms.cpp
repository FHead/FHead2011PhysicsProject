#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper2.h"

int main();
void OverlayHistograms(PsFileHelper &PsFile, TFile &FW, TFile &FZ, TFile &FZnunu, TFile &FZbb, string HistogramName,
   int LegendLocation = 0);
void SideBySideHistograms2D(PsFileHelper &PsFile, TFile &FW, TFile &FZ, TFile &FZnunu, TFile &FZbb, string HistogramName);

int main()
{
   TFile FW("W.root");
   TFile FZ("DY.root");
   TFile FZnunu("Znunu.root");
   TFile FZbb("Zbb.root");

   PsFileHelper PsFile("HistogramOverlay.ps");
   PsFile.AddTextPage("Comparison between different samples");

   PsFile.AddTextPage("Basic sanity check to get started");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "NPU", 2);
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "NPV", 2);

   PsFile.AddTextPage("Tracing vector-boson, and remove events with taus");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HVBCount", 1);
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HVBCountPerEvent");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HVBChildren");

   PsFile.AddTextPage("Jets (not from VB decays)");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HDRJetVBChild", 1);
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetCount30");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetCount50");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetCount100");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetPT");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetEta", 3);
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetPhi", 1);

   PsFile.AddTextPage("Jets (not from VB decays) b-tagging");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHE30");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHELCount30");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHEMCount30");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHETCount30");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHE50");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHELCount50");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHEMCount50");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHETCount50");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHE80");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHELCount80");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHEMCount80");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDJetTCHETCount80");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDBJetPT");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDBJetEta", 3);
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HQCDBJetPhi", 3);

   PsFile.AddTextPage("Jets in tagged (LL, 80) events");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventQCDJetCount30");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventQCDJetCount50");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventQCDJetCount80");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventQCDJetPT");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventQCDJetEta", 3);
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventQCDJetPhi", 3);
  
   PsFile.AddTextPage("Razor in tagged (LL, 80) events");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventMRNew");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventMRNew_R2New005");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventMRNew_R2New010");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventMRNew_R2New015");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventMRNew_R2New020");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventMRNew_R2New025");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventR2New");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventR2New_MRNew300");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventR2New_MRNew400");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventR2New_MRNew500");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventR2New_MRNew600");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventR2New_MRNew700");
   SideBySideHistograms2D(PsFile, FW, FZ, FZnunu, FZbb, "HTaggedEventMRNewVsR2New");
   
   PsFile.AddTextPage("Jets in tagged (L, 80) events");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventQCDJetCount30");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventQCDJetCount50");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventQCDJetCount80");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventQCDJetPT");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventQCDJetEta", 3);
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventQCDJetPhi", 3);

   PsFile.AddTextPage("Razor in tagged (L, 80) events");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventMRNew");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventMRNew_R2New005");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventMRNew_R2New010");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventMRNew_R2New015");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventMRNew_R2New020");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventMRNew_R2New025");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventR2New");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventR2New_MRNew300");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventR2New_MRNew400");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventR2New_MRNew500");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventR2New_MRNew600");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventR2New_MRNew700");
   SideBySideHistograms2D(PsFile, FW, FZ, FZnunu, FZbb, "HSingleTaggedEventMRNewVsR2New");
   
   PsFile.AddTextPage("Jets in tagged (LL, 30) events");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventQCDJetCount30");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventQCDJetCount50");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventQCDJetCount80");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventQCDJetPT");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventQCDJetEta", 3);
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventQCDJetPhi", 3);

   PsFile.AddTextPage("Razor in tagged (LL, 30) events");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventMRNew");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventMRNew_R2New005");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventMRNew_R2New010");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventMRNew_R2New015");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventMRNew_R2New020");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventMRNew_R2New025");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventR2New");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventR2New_MRNew300");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventR2New_MRNew400");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventR2New_MRNew500");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventR2New_MRNew600");
   OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventR2New_MRNew700");
   SideBySideHistograms2D(PsFile, FW, FZ, FZnunu, FZbb, "HLowTaggedEventMRNewVsR2New");
   
   // OverlayHistograms(PsFile, FW, FZ, FZnunu, FZbb, "");
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   FZbb.Close();
   FZnunu.Close();
   FZ.Close();
   FW.Close();

   return 0;
}

void OverlayHistograms(PsFileHelper &PsFile, TFile &FW, TFile &FZ, TFile &FZnunu, TFile &FZbb, string HistogramName,
   int LegendLocation)
{
   TH1D *HW = (TH1D *)FW.Get(HistogramName.c_str());
   TH1D *HZ = (TH1D *)FZ.Get(HistogramName.c_str());
   TH1D *HZnunu = (TH1D *)FZnunu.Get(HistogramName.c_str());
   TH1D *HZbb = (TH1D *)FZbb.Get(HistogramName.c_str());

   if(HW == NULL || HZ == NULL || HZnunu == NULL || HZbb == NULL)
   {
      cout << "Histogram extraction with name \"" << HistogramName << "\" failed!!!" << endl;
      return;
   }

   TCanvas C;

   HW->SetLineColor(kBlack);
   HZ->SetLineColor(kGreen);
   HZnunu->SetLineColor(kCyan);
   HZbb->SetLineColor(kRed);

   HW->SetStats(0);
   HZ->SetStats(0);
   HZnunu->SetStats(0);
   HZbb->SetStats(0);

   HW->Scale(1.0 / HW->Integral());
   HZ->Scale(1.0 / HZ->Integral());
   HZnunu->Scale(1.0 / HZnunu->Integral());
   HZbb->Scale(1.0 / HZbb->Integral());

   double Minimum = 10000;
   double Maximum = -1;
   for(int i = 1; i <= HW->GetNbinsX(); i++)
   {
      double BinContent = HW->GetBinContent(i);
      if(BinContent > 0)
      {
         if(Minimum > BinContent)
            Minimum = BinContent;
         if(Maximum < BinContent)
            Maximum = BinContent;
      }
      BinContent = HZ->GetBinContent(i);
      if(BinContent > 0)
      {
         if(Minimum > BinContent)
            Minimum = BinContent;
         if(Maximum < BinContent)
            Maximum = BinContent;
      }
      BinContent = HZnunu->GetBinContent(i);
      if(BinContent > 0)
      {
         if(Minimum > BinContent)
            Minimum = BinContent;
         if(Maximum < BinContent)
            Maximum = BinContent;
      }
      BinContent = HZbb->GetBinContent(i);
      if(BinContent > 0)
      {
         if(Minimum > BinContent)
            Minimum = BinContent;
         if(Maximum < BinContent)
            Maximum = BinContent;
      }
   }

   if(Maximum / Minimum < 1000)
      Minimum = Maximum / 1000;
   Maximum = Maximum * 3;
   Minimum = Minimum / 3;

   HW->SetMaximum(Maximum);
   HW->SetMinimum(Minimum);

   HW->Draw();
   HZ->Draw("same");
   HZnunu->Draw("same");
   HZbb->Draw("same");

   double LegendX1 = 0.65;
   double LegendX2 = 0.85;
   double LegendY1 = 0.8;
   double LegendY2 = 0.6;

   if(LegendLocation == 1)
   {
      LegendX1 = 0.65;
      LegendX2 = 0.85;
      LegendY1 = 0.35;
      LegendY2 = 0.15;
   }
   if(LegendLocation == 2)
   {
      LegendX1 = 0.15;
      LegendX2 = 0.35;
      LegendY1 = 0.35;
      LegendY2 = 0.15;
   }
   if(LegendLocation == 3)
   {
      LegendX1 = 0.4;
      LegendX2 = 0.6;
      LegendY1 = 0.35;
      LegendY2 = 0.15;
   }

   TLegend Legend(LegendX1, LegendY1, LegendX2, LegendY2);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(HW, "W to lnu", "l");
   Legend.AddEntry(HZ, "Z to ll", "l");
   Legend.AddEntry(HZnunu, "Z to nunu", "l");
   Legend.AddEntry(HZbb, "(Z to ll) + bb", "l");
   Legend.SetTextFont(42);
   Legend.Draw();

   C.SetLogy();

   PsFile.AddCanvas(C);
}

void SideBySideHistograms2D(PsFileHelper &PsFile, TFile &FW, TFile &FZ, TFile &FZnunu, TFile &FZbb, string HistogramName)
{
   TH2D *HW = (TH2D *)FW.Get(HistogramName.c_str());
   TH2D *HZ = (TH2D *)FZ.Get(HistogramName.c_str());
   TH2D *HZnunu = (TH2D *)FZnunu.Get(HistogramName.c_str());
   TH2D *HZbb = (TH2D *)FZbb.Get(HistogramName.c_str());

   if(HW == NULL || HZ == NULL || HZnunu == NULL || HZbb == NULL)
   {
      cout << "Histogram extraction with name \"" << HistogramName << "\" failed!!!" << endl;
      return;
   }

   HW->SetStats(0);
   HZ->SetStats(0);
   HZnunu->SetStats(0);
   HZbb->SetStats(0);

   TLatex WText(1000, 1, "W to lnu");
   TLatex ZText(1000, 1, "Z to ll");
   TLatex ZnunuText(1000, 1, "Z to nunu");
   TLatex ZbbText(1000, 1, "(Z to ll) + bb");

   WText.SetTextFont(42);
   ZText.SetTextFont(42);
   ZnunuText.SetTextFont(42);
   ZbbText.SetTextFont(42);

   TCanvas C;

   C.Divide(2, 2);

   C.cd(1);
   HW->Draw("colz");
   WText.Draw();

   C.cd(2);
   HZ->Draw("colz");
   ZText.Draw();

   C.cd(3);
   HZnunu->Draw("colz");
   ZnunuText.Draw();

   C.cd(4);
   HZbb->Draw("colz");
   ZbbText.Draw();

   PsFile.AddCanvas(C);
}





