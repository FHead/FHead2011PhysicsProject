#include <string>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper.h"

void CompareMCDistributions(string ZMuMuFile = "Samples/ZJetsAll.root",
   string ZNuNuFile = "Samples/ZnunuAll.root");
void CompareSingleMCDistribution(TFile &MuonFile, TFile &NeutrinoFile,
   string HistogramName, string Option, PsFileHelper &PsFile, bool LogY);
void PlotSingleSampleZPt(TFile &File, PsFileHelper &PsFile, string Title);
void JetCountPlot(TFile &MuonFile, TFile &NeutrinoFile, PsFileHelper &PsFile);

void CompareMCDistributions(string ZMuMuFile, string ZNuNuFile)
{
   TFile MuonFile(ZMuMuFile.c_str());
   TFile NeutrinoFile(ZNuNuFile.c_str());

   PsFileHelper PsFile("MCComparison.ps");

   PsFile.AddTextPage("MC-level comparison between ZMuMu sample and ZNuNu sample");

   JetCountPlot(MuonFile, NeutrinoFile, PsFile);

   CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZMass", "", PsFile, true);
   // CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZMass1CaloJet", "", PsFile, true);
   // CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZMass2CaloJet", "", PsFile, true);
   // CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZMass3CaloJet", "", PsFile, true);
   // CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZMass4CaloJet", "", PsFile, true);
   // CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZMass5CaloJet", "", PsFile, true);
   CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZPt", "", PsFile, true);
   CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZPt1CaloJet", "", PsFile, true);
   CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZPt2CaloJet", "", PsFile, true);
   CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZPt3CaloJet", "", PsFile, true);
   CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZPt4CaloJet", "", PsFile, true);
   CompareSingleMCDistribution(MuonFile, NeutrinoFile, "HMCZPt5CaloJet", "", PsFile, true);

   PlotSingleSampleZPt(MuonFile, PsFile, "ZMuMu PT distributions");
   PlotSingleSampleZPt(NeutrinoFile, PsFile, "ZNuNu PT distributions");

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

void CompareSingleMCDistribution(TFile &MuonFile, TFile &NeutrinoFile,
   string HistogramName, string Option, PsFileHelper &PsFile, bool LogY)
{
   TCanvas Canvas("c", "c", 1024, 768);

   TH1D *HistogramMu = (TH1D *)MuonFile.Get(HistogramName.c_str());
   TH1D *HistogramNu = (TH1D *)NeutrinoFile.Get(HistogramName.c_str());

   if(HistogramMu == NULL)
      return;
   if(HistogramNu == NULL)
      return;

   HistogramMu->SetLineWidth(2);
   HistogramNu->SetLineWidth(2);
   
   HistogramMu->SetLineColor(1);
   HistogramNu->SetLineColor(2);

   HistogramMu->SetStats(0);
   HistogramNu->SetStats(0);

   // HistogramMu->DrawNormalized(Form("%s", Option.c_str()));
   // HistogramNu->DrawNormalized(Form("%s same", Option.c_str()));
   HistogramMu->DrawNormalized("");
   HistogramNu->DrawNormalized("same");

   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.SetFillColor(0);
   legend.AddEntry(HistogramMu, "ZMuMu", "l");
   legend.AddEntry(HistogramNu, "ZNuNu", "l");
   legend.Draw();

   if(LogY == true)
      Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
}

void PlotSingleSampleZPt(TFile &File, PsFileHelper &PsFile, string Title)
{
   TH1D *H0Jet = (TH1D *)File.Get("HMCZPt")->Clone("H0Jet");
   TH1D *H1Jet = (TH1D *)File.Get("HMCZPt1CaloJet")->Clone("H1Jet");
   TH1D *H2Jet = (TH1D *)File.Get("HMCZPt2CaloJet")->Clone("H2Jet");
   TH1D *H3Jet = (TH1D *)File.Get("HMCZPt3CaloJet")->Clone("H3Jet");

   TCanvas Canvas("Canvas", "Canvas", 0, 0, 1024, 768);

   H0Jet->SetTitle(Title.c_str());
   H1Jet->SetTitle(Title.c_str());
   H2Jet->SetTitle(Title.c_str());
   H3Jet->SetTitle(Title.c_str());
   
   H0Jet->SetLineWidth(2);
   H1Jet->SetLineWidth(2);
   H2Jet->SetLineWidth(2);
   H3Jet->SetLineWidth(2);
   
   H0Jet->SetLineColor(1);
   H1Jet->SetLineColor(2);
   H2Jet->SetLineColor(3);
   H3Jet->SetLineColor(4);

   H0Jet->SetStats(0);
   H1Jet->SetStats(0);
   H2Jet->SetStats(0);
   H3Jet->SetStats(0);
   
   H0Jet->Draw();
   H1Jet->Draw("same");
   H2Jet->Draw("same");
   H3Jet->Draw("same");

   TLegend legend(0.5, 0.8, 0.8, 0.6);
   legend.SetFillColor(0);
   legend.AddEntry(H0Jet, "All inclusive", "l");
   legend.AddEntry(H1Jet, "At least one calojet", "l");
   legend.AddEntry(H2Jet, "At least two calojet", "l");
   legend.AddEntry(H3Jet, "At least three calojet", "l");
   legend.Draw();

   Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
}

void JetCountPlot(TFile &MuonFile, TFile &NeutrinoFile, PsFileHelper &PsFile)
{
   TCanvas Canvas("Canvas", "Canvas", 0, 0, 1024, 768);

   TGraph MuonGraph;
   MuonGraph.SetNameTitle("MuonGraph", "Number of events in the sample");
   MuonGraph.SetMarkerStyle(20);
   MuonGraph.SetMarkerColor(1);
   MuonGraph.SetLineWidth(2);
   MuonGraph.SetLineColor(1);

   TGraph NeutrinoGraph;
   NeutrinoGraph.SetNameTitle("NeutrinoGraph", "Number of events in the sample");
   NeutrinoGraph.SetMarkerStyle(20);
   NeutrinoGraph.SetMarkerColor(2);
   NeutrinoGraph.SetLineWidth(2);
   NeutrinoGraph.SetLineColor(2);

   for(int i = 0; i <= 5; i++)
   {
      char label[1024] = "";

      if(i == 0)
         sprintf(label, "HMCZPt");
      else
         sprintf(label, "HMCZPt%dCaloJet", i);

      TH1D *HMu = (TH1D *)MuonFile.Get(label);
      TH1D *HNu = (TH1D *)NeutrinoFile.Get(label);

      if(HMu != NULL)
         MuonGraph.SetPoint(i, i, HMu->GetEntries());
      if(HNu != NULL)
         NeutrinoGraph.SetPoint(i, i, HNu->GetEntries());
   }

   NeutrinoGraph.Draw("apl");
   MuonGraph.Draw("pl");

   NeutrinoGraph.GetHistogram()->GetXaxis()->SetTitle("Inclusive jet count");
   NeutrinoGraph.GetHistogram()->GetYaxis()->SetTitle("Event count");
   NeutrinoGraph.GetHistogram()->GetYaxis()->SetRangeUser(0.1, 30000000);

   TLegend legend(0.5, 0.8, 0.8, 0.6);
   legend.SetFillColor(0);
   legend.AddEntry(&MuonGraph, "ZMuMu", "l");
   legend.AddEntry(&NeutrinoGraph, "ZNuNu", "l");
   legend.Draw();

   Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
}






