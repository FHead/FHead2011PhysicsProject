#include <string>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"

#include "PlotHelper2.h"
#include "SetStyle.h"
#include "DrawRandom.h"

int main();
void OverlayHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string HistogramName,
   bool MakeRatio = false);
TH2Poly GetPolyHistogram();

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
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS1");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS1");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS2");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS2");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS3");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS3");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS4");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS4");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS5");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS5");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS6");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS6");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS7");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS7");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS8");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS8");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS9");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS9");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS10");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS10");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS11");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS11");
   OverlayHistogram(PsFile, Files, Labels, "HCountRegions", true);

   /*
   OverlayHistogram(PsFile, Files, Labels, "HMRNewFullRegion_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewFullRegion_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB1_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB1_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB2_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB2_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB3_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB3_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS1_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS1_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS2_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS2_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS3_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS3_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS4_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS4_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS5_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS5_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS6_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS6_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS7_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS7_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS8_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS8_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS9_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS9_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS10_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS10_L");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionFS11_L");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionFS11_L");
   OverlayHistogram(PsFile, Files, Labels, "HCountRegions_L", true);
   */

   /*
   OverlayHistogram(PsFile, Files, Labels, "HMRNewFullRegion_LL");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewFullRegion_LL");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB1_LL");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB1_LL");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB2_LL");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB2_LL");
   OverlayHistogram(PsFile, Files, Labels, "HMRNewRegionB3_LL");
   OverlayHistogram(PsFile, Files, Labels, "HR2NewRegionB3_LL");
   OverlayHistogram(PsFile, Files, Labels, "HCountRegions_LL", true);
   */

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

   TLegend legend(0.15, 0.45, 0.35, 0.15);
   for(int i = 0; i < (int)Files.size(); i++)
      legend.AddEntry(Histograms[i], Labels[i].c_str(), "l");
   // legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);

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
      TGraphAsymmErrors RatioGraph;
      TGraphAsymmErrors RatioGraph2;
      TGraphAsymmErrors RatioGraph3;
      
      TGraph Line;

      double DataAll = 0;
      double MCAll = 0;
      for(int i = 1; i <= 3; i++)
      {
         DataAll = DataAll + Histograms[0]->GetBinContent(i);
         MCAll = MCAll + StackedHistograms[Files.size()-1]->GetBinContent(i);
      }
      Line.SetPoint(0, -9999, DataAll / MCAll);
      Line.SetPoint(1, 9999, DataAll / MCAll);

      TH1D *H = (TH1D *)Histograms[0]->Clone("H");
      H->SetTitle(Form("%s (data/MC ratio)", H->GetTitle()));

      TH2Poly Temperature = GetPolyHistogram();

      for(int i = 1; i <= (int)H->GetNbinsX(); i++)
      {
         double x = Histograms[0]->GetBinContent(i);
         double ex = Histograms[0]->GetBinError(i);
         double y = StackedHistograms[Files.size()-1]->GetBinContent(i);
         double ey = StackedHistograms[Files.size()-1]->GetBinError(i);

         int NumberOfTries = 1000000;
         vector<double> Toys;
         Toys.reserve(NumberOfTries);
         vector<double> DataPoints;
         vector<double> MCPoints;
         for(int j = 0; j < NumberOfTries; j++)
         {
            double Data = DrawPoisson(x);
            double MC = DrawPoisson(y / ey) * ey + 0.00000001;   // to prevent NaN
            Toys.push_back(Data / MC);
            DataPoints.push_back(Data);
            MCPoints.push_back(MC);
         }
         sort(Toys.begin(), Toys.end());

         int Middle = (int)(NumberOfTries * 0.5);
         int OneSigmaLow = (int)(NumberOfTries * 0.317);
         int OneSigmaHigh = (int)(NumberOfTries * 0.683);
         int TwoSigmaLow = (int)(NumberOfTries * 0.05);
         int TwoSigmaHigh = (int)(NumberOfTries * 0.95);
         int ThreeSigmaLow = (int)(NumberOfTries * 0.01);
         int ThreeSigmaHigh = (int)(NumberOfTries * 0.99);

         // cout << Toys[OneSigmaLow] << " " << Toys[Middle] << " " << Toys[OneSigmaHigh] << endl;
         // cout << DataPoints[Middle] << " " << DataPoints[OneSigmaHigh] << endl;

         H->SetBinContent(i, Toys[Middle]);

         RatioGraph.SetPoint(i - 1, i, Toys[Middle]);
         RatioGraph.SetPointError(i - 1, 0, 0, Toys[Middle] - Toys[OneSigmaLow], Toys[OneSigmaHigh] - Toys[Middle]);
         RatioGraph2.SetPoint(i - 1, i, Toys[Middle]);
         RatioGraph2.SetPointError(i - 1, 0, 0, Toys[Middle] - Toys[TwoSigmaLow], Toys[TwoSigmaHigh] - Toys[Middle]);
         RatioGraph3.SetPoint(i - 1, i, Toys[Middle]);
         RatioGraph3.SetPointError(i - 1, 0, 0, Toys[Middle] - Toys[ThreeSigmaLow], Toys[ThreeSigmaHigh] - Toys[Middle]);

         Temperature.SetBinContent(i, Toys[Middle]);
      }

      H->SetMaximum(2.5);
      H->SetMinimum(0);
      H->SetLineColor(0);
      H->SetMarkerColor(0);

      RatioGraph3.SetLineColor(kRed);
      RatioGraph2.SetLineColor(kGreen);
      RatioGraph.SetLineColor(kBlack);

      Line.SetLineColor(kBlue);

      TCanvas C5;
      H->Draw();
      // RatioGraph3.Draw("pe");
      RatioGraph2.Draw("pe");
      RatioGraph.Draw("pe");
      Line.Draw("l");
      C5.SaveAs((HistogramName + "_Ratio.png").c_str());
      C5.SaveAs((HistogramName + "_Ratio.C").c_str());
      C5.SaveAs((HistogramName + "_Ratio.eps").c_str());
      C5.SaveAs((HistogramName + "_Ratio.pdf").c_str());

      PsFile.AddCanvas(C5);

      PsFile.AddPlot(Temperature, "colz");

      delete H;
   }

   for(int i = 1; i < (int)Files.size(); i++)
      delete StackedHistograms[i];
}

TH2Poly GetPolyHistogram()
{
   TH2Poly Histogram;

   double B1X[] = {500, 600, 600, 500};
   double B2X[] = {600, 700, 700, 600};
   double B3X[] = {600, 700, 700, 600};
   double FS1X[] = {500, 600, 600, 500};
   double FS2X[] = {500, 600, 600, 500};
   double FS3X[] = {500, 600, 600, 500};
   double FS4X[] = {600, 700, 700, 600};
   double FS5X[] = {600, 700, 700, 600};
   double FS6X[] = {600, 700, 700, 600};
   double FS7X[] = {700, 1500, 1500, 700};
   double FS8X[] = {700, 1500, 1500, 700};
   double FS9X[] = {700, 1500, 1500, 700};
   double FS10X[] = {700, 1500, 1500, 700};
   double FS11X[] = {700, 1500, 1500, 700};

   double B1Y[] = {0.10, 0.10, 0.14, 0.14};
   double B2Y[] = {0.10, 0.10, 0.14, 0.14};
   double B3Y[] = {0.07, 0.07, 0.10, 0.10};
   double FS1Y[] = {0.30, 0.30, 0.50, 0.50};
   double FS2Y[] = {0.20, 0.20, 0.30, 0.30};
   double FS3Y[] = {0.14, 0.14, 0.20, 0.20};
   double FS4Y[] = {0.30, 0.30, 0.50, 0.50};
   double FS5Y[] = {0.20, 0.20, 0.30, 0.30};
   double FS6Y[] = {0.14, 0.14, 0.20, 0.20};
   double FS7Y[] = {0.30, 0.30, 0.50, 0.50};
   double FS8Y[] = {0.20, 0.20, 0.30, 0.30};
   double FS9Y[] = {0.14, 0.14, 0.20, 0.20};
   double FS10Y[] = {0.10, 0.10, 0.14, 0.14};
   double FS11Y[] = {0.07, 0.07, 0.10, 0.10};

   Histogram.AddBin(4, B1X, B1Y);
   Histogram.AddBin(4, B2X, B2Y);
   Histogram.AddBin(4, B3X, B3Y);
   Histogram.AddBin(4, FS1X, FS1Y);
   Histogram.AddBin(4, FS2X, FS2Y);
   Histogram.AddBin(4, FS3X, FS3Y);
   Histogram.AddBin(4, FS4X, FS4Y);
   Histogram.AddBin(4, FS5X, FS5Y);
   Histogram.AddBin(4, FS6X, FS6Y);
   Histogram.AddBin(4, FS7X, FS7Y);
   Histogram.AddBin(4, FS8X, FS8Y);
   Histogram.AddBin(4, FS9X, FS9Y);
   Histogram.AddBin(4, FS10X, FS10Y);
   Histogram.AddBin(4, FS11X, FS11Y);

   return Histogram;
}



