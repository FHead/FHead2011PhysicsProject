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

   PsFileHelper PsFile("MCReference.ps");
   PsFile.AddTextPage("MC shape reference!");

   vector<TFile *> Files;
   Files.push_back(new TFile("TTbar.root"));
   Files.push_back(new TFile("W.root"));
   Files.push_back(new TFile("WW.root"));
   Files.push_back(new TFile("WZ.root"));
   Files.push_back(new TFile("ZZ.root"));
   Files.push_back(new TFile("GammaVJet.root"));
   Files.push_back(new TFile("DY10.root"));
   Files.push_back(new TFile("DY50.root"));

   vector<string> Labels;
   Labels.push_back("TTbar");
   Labels.push_back("W");
   Labels.push_back("WW");
   Labels.push_back("WZ");
   Labels.push_back("ZZ");
   Labels.push_back("GammaVJet");
   Labels.push_back("DY 10-50");
   Labels.push_back("DY 50+");

   OverlayHistogram(PsFile, Files, Labels, "HMuon1PT");
   OverlayHistogram(PsFile, Files, Labels, "HLeadingCaloJetPT");
   OverlayHistogram(PsFile, Files, Labels, "HSubLeadingCaloJetPT");
   OverlayHistogram(PsFile, Files, Labels, "HCaloJetMR");
   OverlayHistogram(PsFile, Files, Labels, "HCaloJetR");
   OverlayHistogram(PsFile, Files, Labels, "HCaloJetMRStar");
   OverlayHistogram(PsFile, Files, Labels, "HCaloJetGammaMRStar");
   OverlayHistogram(PsFile, Files, Labels, "HCaloJetRStar");
   OverlayHistogram(PsFile, Files, Labels, "HCaloJetGammaMRStar_RStar02");
   OverlayHistogram(PsFile, Files, Labels, "HCaloJetGammaMRStar_RStar03");
   OverlayHistogram(PsFile, Files, Labels, "HCaloJetGammaMRStar_RStar04");
   OverlayHistogram(PsFile, Files, Labels, "HCaloJetGammaMRStar_RStar05");
   OverlayHistogram(PsFile, Files, Labels, "HCaloMET");

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

   for(int i = 0; i < (int)Files.size(); i++)
      Histograms[i]->SetLineColor(i + 2);

   TLegend legend(0.75, 0.95, 0.95, 0.6);
   for(int i = 0; i < (int)Files.size(); i++)
      legend.AddEntry(Histograms[i], Labels[i].c_str(), "l");
   legend.SetFillColor(0);

   TCanvas C3;
   vector<TH1D *> StackedHistograms;
   StackedHistograms.push_back((TH1D *)Histograms[0]->Clone("StackedHistogram1"));
   for(int i = 1; i < (int)Files.size(); i++)
   {
      StackedHistograms.push_back((TH1D *)StackedHistograms[i-1]->Clone(Form("StackedHistogram%d", i)));
      StackedHistograms[i]->Add(Histograms[i]);
   }
   for(int i = (int)Files.size() - 1; i >= 0; i--)
   {
      StackedHistograms[i]->SetFillColor(i + 2);
      StackedHistograms[i]->SetLineColor(i + 2);
      if(i != (int)Files.size() - 1)
         StackedHistograms[i]->Draw("same");
      else
         StackedHistograms[i]->Draw("");
   }
   C3.SetLogy();
   legend.Draw();
   PsFile.AddCanvas(C3);

   for(int i = 0; i < (int)Files.size(); i++)
      delete StackedHistograms[i];
}




