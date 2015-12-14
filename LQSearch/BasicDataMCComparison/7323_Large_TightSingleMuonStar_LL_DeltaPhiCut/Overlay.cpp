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
void OverlayHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string HistogramName,
   vector<bool> Bundle);

int main()
{
   SetStyle();

   PsFileHelper PsFile("DataMCComparison.ps");
   PsFile.AddTextPage("Data-MC comparison!");

   vector<TFile *> Files;
   Files.push_back(new TFile("DataPlots.root"));
   Files.push_back(new TFile("TTbar.root"));
   Files.push_back(new TFile("W.root"));
   Files.push_back(new TFile("Znunu.root"));
   Files.push_back(new TFile("QCDAll.root"));
   Files.push_back(new TFile("VV.root"));
   Files.push_back(new TFile("GammaVJet.root"));
   Files.push_back(new TFile("DY50.root"));

   vector<string> Labels;
   Labels.push_back("Data (1769 pb^{-1})");
   Labels.push_back("t#bar{t} + jets");
   Labels.push_back("W + jets");
   Labels.push_back("Z #rightarrow #nu#bar#nu");
   Labels.push_back("Multijets");
   Labels.push_back("VV");
   Labels.push_back("GammaVJet");
   Labels.push_back("DY 50+");

   vector<bool> Bundle;
   Bundle.push_back(false);
   Bundle.push_back(false);
   Bundle.push_back(false);
   Bundle.push_back(false);
   Bundle.push_back(false);
   Bundle.push_back(true);
   Bundle.push_back(true);
   Bundle.push_back(true);

   OverlayHistogram(PsFile, Files, Labels, "HMuon1PT", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HElectron1PT", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HLeadingCaloJetPT", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HSubLeadingCaloJetPT", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMRNew", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HR2New", Bundle);
   // OverlayHistogram(PsFile, Files, Labels, "HR2New_MRNew400", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_RNew02", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_RNew03", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_RNew04", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_RNew05", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_RNew06", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMRNew_R2New020", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HPFMET", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMegaJetDeltaPhi", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMegaJetDeltaPhi_MRNew400_R2New016", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMegaJetDeltaPhi_MRNew400_R2New025", Bundle);
   OverlayHistogram(PsFile, Files, Labels, "HMegaJetDeltaPhi_MRNew400_R2New050Up", Bundle);

   for(int i = 0; i < (int)Files.size(); i++)
   {
      Files[i]->Close();
      delete Files[i];
   }
   Files.clear();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

void OverlayHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string HistogramName,
   vector<bool> Bundle)
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

   vector<TH1D *> StackedHistograms2;
   StackedHistograms2.push_back(NULL);
   StackedHistograms2.push_back((TH1D *)Histograms[1]->Clone("StackedHistogram21"));
   
   TLegend legend2(0.6, 0.85, 0.9, 0.55);
   legend2.SetFillStyle(0);
   legend2.SetBorderSize(0);
   legend2.SetTextFont(42);
   legend2.AddEntry(Histograms[0], "Data", "lp");
   legend2.AddEntry(StackedHistograms2[1], Labels[1].c_str(), "f");

   for(int i = 2; i < (int)Files.size(); i++)
   {
      if(Bundle[i] == true)
         continue;
      TH1D *H = (TH1D *)StackedHistograms2[StackedHistograms2.size()-1]->Clone(Form("StackedHistogram2%d", i));
      StackedHistograms2.push_back(H);
      H->Add(Histograms[i]);

      legend2.AddEntry(H, Labels[i].c_str(), "f");
   }
   TH1D *H = (TH1D *)StackedHistograms2[StackedHistograms2.size()-1]->Clone(Form("StackedHistogram2%d", 999));
   StackedHistograms2.push_back(H);
   for(int i = 2; i < (int)Files.size(); i++)
   {
      if(Bundle[i] == false)
         continue;
      H->Add(Histograms[i]);
   }
   legend2.AddEntry(H, "Others", "f");

   TCanvas C4("C4", "C4", 1024, 1024);
   // Histograms[0]->SetTitle(TString(Histograms[0]->GetTitle()).ReplaceAll(" (new)", ""));
   Histograms[0]->SetTitle("");
   Histograms[0]->GetXaxis()->SetTitle(TString(Histograms[0]->GetXaxis()->GetTitle()).ReplaceAll(" (new)", ""));
   Histograms[0]->Draw("error point");
   for(int i = (int)StackedHistograms2.size() - 1; i >= 1; i--)
   {
      StackedHistograms2[i]->SetFillColor(i + 1);
      StackedHistograms2[i]->SetLineColor(i + 1);
      StackedHistograms2[i]->Draw("same");
   }
   Histograms[0]->Draw("error point same");
   C4.SetLogy();
   legend2.Draw();
   AddCMSPreliminary(0.10, 0.925, 1769, 0.025);
   C4.SaveAs((HistogramName + ".png").c_str());
   C4.SaveAs((HistogramName + ".C").c_str());
   C4.SaveAs((HistogramName + ".eps").c_str());

   for(int i = 1; i < (int)Files.size(); i++)
      delete StackedHistograms[i];
   for(int i = 1; i < (int)StackedHistograms2.size(); i++)
      delete StackedHistograms2[i];
}




