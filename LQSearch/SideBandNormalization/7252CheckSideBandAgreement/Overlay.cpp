#include <string>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main();
void OverlayHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string HistogramName,
   bool MakeRatio = false);

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
   Files.push_back(new TFile("VV.root"));
   Files.push_back(new TFile("GammaVJet.root"));
   Files.push_back(new TFile("DY50.root"));
   Files.push_back(new TFile("QCDAll.root"));

   vector<string> Labels;
   Labels.push_back("Data (863/pb)");
   Labels.push_back("TTbar");
   Labels.push_back("W");
   Labels.push_back("Znunu");
   Labels.push_back("VV");
   Labels.push_back("GammaVJet");
   Labels.push_back("DY 50+");
   Labels.push_back("QCD");

   OverlayHistogram(PsFile, Files, Labels, "HMRNewFullRegion");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewFullRegion");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB1");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB1");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB2");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB2");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB3");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB3");
   OverlayHistogram(PsFile, Files, Labels, "HCountRegions", true);

   OverlayHistogram(PsFile, Files, Labels, "HMRNewFullRegion_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewFullRegion_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB1_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB1_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB2_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB2_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB3_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB3_L");
   OverlayHistogram(PsFile, Files, Labels, "HCountRegions_L", true);

   OverlayHistogram(PsFile, Files, Labels, "HMRNewFullRegion_LL");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewFullRegion_LL");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB1_LL");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB1_LL");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB2_LL");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB2_LL");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB3_LL");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB3_LL");
   OverlayHistogram(PsFile, Files, Labels, "HCountRegions_LL", true);

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
   bool MakeRatio)
{
   vector<TH1D *> Histograms;
   for(int i = 0; i < (int)Files.size(); i++)
      Histograms.push_back((TH1D *)Files[i]->Get(HistogramName.c_str()));

   Histograms[0]->SetMarkerStyle(8);
   Histograms[0]->SetLineColor(1);
   Histograms[0]->SetStats(0);
   Histograms[0]->SetMinimum(0.3);
   Histograms[0]->Sumw2();
   Histograms[0]->GetXaxis()->SetTitle(TString(Histograms[0]->GetXaxis()->GetTitle()).ReplaceAll("MR***", "MR").ReplaceAll("RStar", "R"));
   Histograms[0]->SetTitle(TString(Histograms[0]->GetTitle()).ReplaceAll("MR***", "MR").ReplaceAll("RStar", "R"));

   for(int i = 1; i < (int)Files.size(); i++)
      Histograms[i]->SetLineColor(i + 1);

   TLegend legend(0.75, 0.95, 0.95, 0.6);
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
   // double TotalMCYield = HTogether->Integral();   // hack!!!
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
      // StackedHistograms[i]->Scale(Histograms[0]->Integral() / TotalMCYield);   // hack!
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

   if(MakeRatio == true)
   {
      TH1D *H = (TH1D *)Histograms[0]->Clone("H");
      H->SetTitle(Form("%s (data/MC ratio)", H->GetTitle()));
      for(int i = 1; i <= (int)H->GetNbinsX(); i++)
      {
         double x = Histograms[0]->GetBinContent(i);
         double ex = Histograms[0]->GetBinError(i);
         double y = StackedHistograms[Files.size()-1]->GetBinContent(i);
         double ey = StackedHistograms[Files.size()-1]->GetBinError(i);

         H->SetBinContent(i, x / y);
         H->SetBinError(i, x / y * sqrt(ex * ex / x / x + ey * ey / y / y));
      }

      H->SetMaximum(2);
      H->SetMinimum(0);

      TCanvas C5;
      H->Draw();
      C5.SaveAs((HistogramName + "_Ratio.png").c_str());
      C5.SaveAs((HistogramName + "_Ratio.C").c_str());
      C5.SaveAs((HistogramName + "_Ratio.eps").c_str());

      PsFile.AddCanvas(C5);

      delete H;
   }

   for(int i = 1; i < (int)Files.size(); i++)
      delete StackedHistograms[i];
}




