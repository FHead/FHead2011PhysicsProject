#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main();
void OverlayHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string HistogramName);

int main()
{
   SetStyle();

   PsFileHelper PsFile("DataMCComparison.ps");
   PsFile.AddTextPage("Data-MC comparison!");

   vector<TFile *> Files;
   Files.push_back(new TFile("DataPlots.root"));
   Files.push_back(new TFile("TTbar.root"));
   Files.push_back(new TFile("W.root"));
   Files.push_back(new TFile("VV.root"));
   Files.push_back(new TFile("GammaVJet.root"));
   Files.push_back(new TFile("DY50.root"));
   Files.push_back(new TFile("QCDAll.root"));
   Files.push_back(new TFile("Znunu.root"));

   vector<string> Labels;
   Labels.push_back("Data (863 pb^{-1})");
   Labels.push_back("TTbar");
   Labels.push_back("W");
   Labels.push_back("VV");
   Labels.push_back("GammaVJet");
   Labels.push_back("DY 50+");
   Labels.push_back("QCD");
   Labels.push_back("Znunu");

   OverlayHistogram(PsFile, Files, Labels, "HMuon1PT");
   OverlayHistogram(PsFile, Files, Labels, "HElectron1PT");
   OverlayHistogram(PsFile, Files, Labels, "HLeadingCaloJetPT");
   OverlayHistogram(PsFile, Files, Labels, "HSubLeadingCaloJetPT");
   OverlayHistogram(PsFile, Files, Labels, "HMRNew");
   OverlayHistogram(PsFile, Files, Labels, "HR2New");
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_RNew02");
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_RNew03");
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_RNew04");
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_RNew05");
   OverlayHistogram(PsFile, Files, Labels, "HPFMET");
   OverlayHistogram(PsFile, Files, Labels, "HMegaJetDeltaPhi");
   OverlayHistogram(PsFile, Files, Labels, "HMegaJetDeltaPhi_MRNew400_R2New016");
   OverlayHistogram(PsFile, Files, Labels, "HMegaJetDeltaPhi_MRNew400_R2New025");

   for(int i = 0; i < (int)Files.size(); i++)
   {
      Files[i]->Close();
      delete Files[i];
   }
   Files.clear();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

void OverlayHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string HistogramName)
{
   vector<TH1D *> Histograms;
   for(int i = 0; i < (int)Files.size(); i++)
      Histograms.push_back((TH1D *)Files[i]->Get(HistogramName.c_str()));

   Histograms[0]->SetMarkerStyle(8);
   Histograms[0]->SetLineColor(1);
   Histograms[0]->SetStats(0);
   Histograms[0]->SetMinimum(0.3);
   Histograms[0]->Sumw2();

   for(int i = 1; i < (int)Files.size(); i++)
      Histograms[i]->SetLineColor(i + 1);

   TLegend legend(0.65, 0.85, 0.85, 0.5);
   legend.SetTextFont(42);
   legend.SetBorderSize(0);
   legend.SetFillStyle(0);
   for(int i = 0; i < (int)Files.size(); i++)
      legend.AddEntry(Histograms[i], Labels[i].c_str(), "l");
   legend.SetFillColor(0);

   TCanvas C;
   Histograms[0]->Draw("error point");
   for(int i = 1; i < (int)Files.size(); i++)
      Histograms[i]->Draw("same");
   C.SetLogy();
   legend.Draw();
   PsFile.AddCanvas(C);

   TCanvas C2;
   TH1D *HTogether =(TH1D *)Histograms[1]->Clone("HTogether");
   for(int i = 2; i < (int)Files.size(); i++)
      HTogether->Add(Histograms[i]);
   Histograms[0]->Draw("error point");
   HTogether->Draw("same");
   C2.SetLogy();
   PsFile.AddCanvas(C2);
   delete HTogether;

   TCanvas C3;
   Histograms[0]->Draw("error point");
   vector<TH1D *> StackedHistograms;
   StackedHistograms.push_back(NULL);
   StackedHistograms.push_back((TH1D *)Histograms[1]->Clone("StackedHistogram1"));
   for(int i = 2; i < (int)Files.size(); i++)
   {
      StackedHistograms.push_back((TH1D *)StackedHistograms[i-1]->Clone(Form("StackedHistogram%d", i)));
      StackedHistograms[i]->Add(Histograms[i]);
   }
   for(int i = (int)Files.size() - 1; i >= 1; i--)
   {
      StackedHistograms[i]->SetFillColor(i + 1);
      StackedHistograms[i]->SetLineColor(i + 1);
      StackedHistograms[i]->Draw("same");
   }
   Histograms[0]->Draw("error point same");
   C3.SetLogy();
   legend.Draw();
   PsFile.AddCanvas(C3);

   TCanvas C4("C4", "C4", 1024, 1024);
   Histograms[0]->Draw("error point");
   for(int i = (int)Files.size() - 1; i >= 1; i--)
   {
      StackedHistograms[i]->SetFillColor(i + 1);
      StackedHistograms[i]->SetLineColor(i + 1);
      StackedHistograms[i]->Draw("same");
   }
   Histograms[0]->Draw("error point same");
   C4.SetLogy();
   legend.Draw();
   C4.SaveAs((HistogramName + ".png").c_str());
   C4.SaveAs((HistogramName + ".C").c_str());
   C4.SaveAs((HistogramName + ".eps").c_str());

   for(int i = 1; i < (int)Files.size(); i++)
      delete StackedHistograms[i];
}




