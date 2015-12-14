#include <vector>
#include <string>
using namespace std;

#include "TH1D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"

#include "PlotHelper.h"

void PFThresholdScan(string JetFlavor = "PF");
void MakeYieldPlots(PsFileHelper &PsFile, vector<string> FileNames, vector<string> Labels, vector<double> Thresholds);
void MakeRatioPlots(PsFileHelper &PsFile, vector<string> FileNames, vector<string> Labels, vector<double> Thresholds);

void PFThresholdScan(string JetFlavor)
{
   PsFileHelper PsFile(JetFlavor + "ThresholdScan.ps");
   PsFile.AddTextPage(JetFlavor + " Jet Multiplicity Threshold Scan");

   vector<string> FileNames;
   FileNames.push_back("../FitResult_" + JetFlavor + "_15.root");
   FileNames.push_back("../FitResult_" + JetFlavor + "_17.root");
   FileNames.push_back("../FitResult_" + JetFlavor + "_20.root");
   FileNames.push_back("../FitResult_" + JetFlavor + "_25.root");
   FileNames.push_back("../FitResult_" + JetFlavor + "_30.root");
   // FileNames.push_back("../FitResult_PF_40.root");
   // FileNames.push_back("../FitResult_PF_50.root");

   vector<string> Labels;
   Labels.push_back("15 GeV");
   Labels.push_back("17 GeV");
   Labels.push_back("20 GeV");
   Labels.push_back("25 GeV");
   Labels.push_back("30 GeV");
   // Labels.push_back("40 GeV");
   //Labels.push_back("50 GeV");
   
   vector<double> Thresholds;
   Thresholds.push_back(15);
   Thresholds.push_back(17);
   Thresholds.push_back(20);
   Thresholds.push_back(25);
   Thresholds.push_back(30);
   // Thresholds.push_back(40);
   // Thresholds.push_back(50);

   MakeYieldPlots(PsFile, FileNames, Labels, Thresholds);
   MakeRatioPlots(PsFile, FileNames, Labels, Thresholds);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

void MakeYieldPlots(PsFileHelper &PsFile, vector<string> FileNames, vector<string> Labels, vector<double> Thresholds)
{
   vector<TFile *> Files;
   vector<TH1D *> Histograms;
   vector<TGraphErrors *> Graphs;

   for(int i = 0; i < (int)FileNames.size(); i++)
      Files.push_back(new TFile(FileNames[i].c_str()));

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      Histograms.push_back((TH1D *)Files[i]->Get("InclusiveYieldsHistogram"));
      Graphs.push_back((TGraphErrors *)Files[i]->Get("InclusiveYieldsGraph"));
   }

   int IndexOfHistogramWithLargestRange = -1;
   double MaxRange = 0;
   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      if(Histograms[i] == NULL)
         continue;

      if(Histograms[i]->GetMaximum() > MaxRange)
      {
         IndexOfHistogramWithLargestRange = i;
         MaxRange = Histograms[i]->GetMaximum();
      }
   }

   if(IndexOfHistogramWithLargestRange == -1)
   {
      for(int i = 0; i < (int)FileNames.size(); i++)
      {
         Files[i]->Close();
         delete Files[i];
      }
      return;
   }

   TCanvas Canvas("C", "c", 0, 0, 1024, 768);

   Histograms[IndexOfHistogramWithLargestRange]->SetLineColor(kWhite);
   Histograms[IndexOfHistogramWithLargestRange]->Draw();

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      if(Graphs[i] == NULL)
         continue;

      Graphs[i]->SetLineColor(i + 1);
      Graphs[i]->Draw("pl");
   }

   TLegend Legend(0.70, 0.85, 0.85, 0.65);
   Legend.SetFillColor(0);
   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      if(Graphs[i] == NULL)
         continue;

      Legend.AddEntry(Graphs[i], Labels[i].c_str(), "l");
   }
   Legend.Draw();

   Canvas.SetLogy();
   PsFile.AddCanvas(Canvas);

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      Files[i]->Close();
      delete Files[i];
   }
}

void MakeRatioPlots(PsFileHelper &PsFile, vector<string> FileNames, vector<string> Labels, vector<double> Thresholds)
{
   vector<TFile *> Files;
   vector<TGraphErrors *> Graphs;
   vector<TGraphErrors *> BandGraphs;
   vector<TGraph *> LineGraphs;
   vector<TF1 *> LinearFits;

   TGraphErrors SummaryGraph;
   SummaryGraph.SetName("SummaryGraph");
   SummaryGraph.SetTitle("Summary graph of alpha parameter");

   TH1D RangeSetter("RangeSetter", "Ratio summary for different jet threhsold", 7, 0.5, 7.5);
   RangeSetter.Fill(0.0, 6.0);
   RangeSetter.Fill(7.0, 6.0);
   RangeSetter.SetLineColor(kWhite);
   RangeSetter.GetXaxis()->SetTitle("N (Inclusive Jet Count)");
   RangeSetter.GetYaxis()->SetTitle("#frac{Z + N Jets}{Z + (N+1) Jets}");
   RangeSetter.SetStats(0);

   for(int i = 0; i < (int)FileNames.size(); i++)
      Files.push_back(new TFile(FileNames[i].c_str()));

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      Graphs.push_back((TGraphErrors *)Files[i]->Get("RatioGraph"));
      BandGraphs.push_back((TGraphErrors *)Files[i]->Get("BandFromComplicatedFitGraph"));
      LineGraphs.push_back((TGraphErrors *)Files[i]->Get("LineFromComplicatedFitGraph"));
      LinearFits.push_back((TF1 *)Files[i]->Get("LinearFit"));
   }

   TCanvas Canvas("C", "c", 0, 0, 1024, 768);

   RangeSetter.Draw();

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      if(Graphs[i] == NULL || BandGraphs[i] == NULL || LineGraphs[i] == NULL)
         continue;

      for(int j = 0; j < Graphs[i]->GetN(); j++)   // shift points a little for clearer view
      {
         double X, Y;
         Graphs[i]->GetPoint(j, X, Y);
         Graphs[i]->SetPoint(j, X + 0.01 * i, Y);
      }

      Graphs[i]->SetLineColor(i + 1);
      Graphs[i]->SetLineWidth(1);
      Graphs[i]->Draw("p");

      BandGraphs[i]->SetFillColor(i + 1);
      BandGraphs[i]->SetFillStyle(3001);
      BandGraphs[i]->Draw("3");

      LineGraphs[i]->SetLineWidth(1);
      LineGraphs[i]->SetLineColor(i + 1);
      LineGraphs[i]->Draw("l");

      LinearFits[i]->Draw("same");

      double X, Y, EY;
      BandGraphs[i]->GetPoint(1, X, Y);
      EY = BandGraphs[i]->GetErrorY(1);
      SummaryGraph.SetPoint(i, Thresholds[i], Y);
      SummaryGraph.SetPointError(i, 0, EY);
   }

   TLegend Legend(0.70, 0.85, 0.85, 0.65);
   Legend.SetFillColor(0);
   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      if(Graphs[i] == NULL)
         continue;

      Legend.AddEntry(Graphs[i], Labels[i].c_str(), "l");
   }
   Legend.Draw();

   PsFile.AddCanvas(Canvas);

   SummaryGraph.GetXaxis()->SetTitle("Jet threshold (GeV/c)");
   SummaryGraph.GetYaxis()->SetTitle("Alpha parameter");
   PsFile.AddPlot(SummaryGraph, "ap");

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      Files[i]->Close();
      delete Files[i];
   }
}







