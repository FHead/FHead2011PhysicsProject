#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "TH1D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"

#include "PlotHelper.h"
#include "DataHelper.h"

void PFThresholdScan(string JetFlavor = "PF", string Suffix = "");
void MakeYieldPlots(PsFileHelper &PsFile, vector<string> FileNames, vector<string> Labels, vector<double> Thresholds);
void MakeRatioPlots(PsFileHelper &PsFile, vector<string> FileNames, vector<string> Labels, vector<double> Thresholds,
   DataHelper &DHFile, vector<string> States, string Tag);

void PFThresholdScan(string JetFlavor, string Suffix)
{
   string DataHelperFile = "../Samples/DataAll.dh";
   DataHelper DHFile(DataHelperFile);

   PsFileHelper PsFile(JetFlavor + Suffix + "_ThresholdScan.ps");
   PsFile.AddTextPage(JetFlavor + " Jet Multiplicity Threshold Scan");

   string SuffixCleaned = "all";
   if(Suffix == "")
      SuffixCleaned = "all";
   else if(Suffix == "_Eta10")
      SuffixCleaned = "1.0";
   else if(Suffix == "_Eta24")
      SuffixCleaned = "2.4";
   else if(Suffix == "_Eta25")
      SuffixCleaned = "2.5";
   else
      SuffixCleaned = "none";

   vector<double> Thresholds;
   Thresholds.push_back(15);
   Thresholds.push_back(16);
   Thresholds.push_back(17);
   Thresholds.push_back(18);
   Thresholds.push_back(19);
   Thresholds.push_back(20);
   Thresholds.push_back(22);
   Thresholds.push_back(24);
   Thresholds.push_back(26);
   Thresholds.push_back(28);
   Thresholds.push_back(30);
   // Thresholds.push_back(35);
   // Thresholds.push_back(40);
   // Thresholds.push_back(50);

   vector<string> FileNames;
   vector<string> Labels;
   vector<string> States;

   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      stringstream ThresholdStream;
      ThresholdStream << Thresholds[i];
      string ThresholdString = ThresholdStream.str();

      FileNames.push_back("../FitResult_" + JetFlavor + "_" + ThresholdString + Suffix + ".root");
      Labels.push_back(ThresholdString + " GeV");
      States.push_back(JetFlavor + " Jet, " + ThresholdString + ", Eta range " + SuffixCleaned + ", Isolation 0.30");
   }

   string Tag = JetFlavor + Suffix;
   
   MakeYieldPlots(PsFile, FileNames, Labels, Thresholds);
   MakeRatioPlots(PsFile, FileNames, Labels, Thresholds, DHFile, States, Tag);

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

void MakeRatioPlots(PsFileHelper &PsFile, vector<string> FileNames, vector<string> Labels, vector<double> Thresholds,
   DataHelper &DHFile, vector<string> States, string Tag)
{
   vector<TFile *> Files;
   vector<TGraphErrors *> Graphs;
   vector<TGraphErrors *> BandGraphs;
   vector<TGraph *> LineGraphs;
   vector<TF1 *> LinearFits;

   TGraphErrors AlphaSummaryGraph;
   AlphaSummaryGraph.SetName("AlphaSummaryGraph");
   AlphaSummaryGraph.SetTitle("Summary graph of alpha parameter");
   AlphaSummaryGraph.SetMarkerStyle(20);
   
   TGraphErrors BetaSummaryGraph;
   BetaSummaryGraph.SetName("BetaSummaryGraph");
   BetaSummaryGraph.SetTitle("Summary graph of beta parameter");
   BetaSummaryGraph.SetMarkerStyle(20);

   TGraph ZeroGraph;
   ZeroGraph.SetPoint(0, 0, 0);
   ZeroGraph.SetPoint(1, 100, 0);

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

   int PointCount = 0;
   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      double Alpha = DHFile[States[i]]["ConstrainedFitAlpha"].GetDouble();
      double AlphaError = DHFile[States[i]]["ConstrainedFitAlphaError"].GetDouble();
      double Beta = DHFile[States[i]]["ConstrainedFitBeta"].GetDouble();
      double BetaError = DHFile[States[i]]["ConstrainedFitBetaError"].GetDouble();

      cout << Beta << " " << BetaError << endl;
      if(fabs(Beta) / BetaError < 4)
      {
         AlphaSummaryGraph.SetPoint(PointCount, Thresholds[i], Alpha);
         AlphaSummaryGraph.SetPointError(PointCount, 0, AlphaError);
         BetaSummaryGraph.SetPoint(PointCount, Thresholds[i], Beta);
         BetaSummaryGraph.SetPointError(PointCount, 0, BetaError);
         PointCount = PointCount + 1;
      }

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

   AlphaSummaryGraph.GetXaxis()->SetTitle("Jet threshold (GeV/c)");
   AlphaSummaryGraph.GetYaxis()->SetTitle("Alpha parameter");
   PsFile.AddPlot(AlphaSummaryGraph, "ap");
   
   BetaSummaryGraph.GetXaxis()->SetTitle("Jet threshold (GeV/c)");
   BetaSummaryGraph.GetYaxis()->SetTitle("Beta parameter");
   PsFile.AddPlot(BetaSummaryGraph, "ap");

   // Two graphs on the same canvas
   TCanvas CanvasOverlay("CanvasOverlay", "Overlayed canvas", 1024, 768);

   CanvasOverlay.Divide(1, 2);

   CanvasOverlay.cd(1);
   AlphaSummaryGraph.Draw("ap");
   
   CanvasOverlay.cd(2);
   BetaSummaryGraph.Draw("ap");
   ZeroGraph.Draw("l");

   CanvasOverlay.SaveAs((Tag + ".png").c_str());
   CanvasOverlay.SaveAs((Tag + ".C").c_str());
   CanvasOverlay.SaveAs((Tag + ".eps").c_str());

   PsFile.AddCanvas(CanvasOverlay);

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      Files[i]->Close();
      delete Files[i];
   }
}







