#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2D.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "CustomAssert.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void DoMatching(PdfFileHelper &PdfFile,
   string DataFileName, string MCFileName,
   string DataCurveName, string MCCurveName,
   string Title, TGraph &GResult, TGraph &GDiff);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DataFileName  = CL.Get("data", "CurvesData.root");
   string MCFileName    = CL.Get("mc", "CurvesMC.root");

   vector<double> Radius{0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};
   
   PdfFileHelper PdfFile("UEMatching.pdf");
   PdfFile.AddTextPage("UE Matching");
   
   vector<TGraph> GMean(Radius.size()), GMeanDiff(Radius.size());
   vector<TGraph> GMedian(Radius.size()), GMedianDiff(Radius.size());
   vector<TGraph> GRMS(Radius.size()), GRMSDiff(Radius.size());
   vector<TGraph> G68Dist(Radius.size()), G68DistDiff(Radius.size());
   vector<TGraph> G95Dist(Radius.size()), G95DistDiff(Radius.size());

   for(int i = 0; i < (int)Radius.size(); i++)
   {
      string CurveName = Form("GMean_%.02f", Radius[i]);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, GMean[i], GMeanDiff[i]);
      CurveName = Form("G50_%.02f", Radius[i]);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, GMedian[i], GMedianDiff[i]);
      CurveName = Form("GRMS_%.02f", Radius[i]);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, GRMS[i], GRMSDiff[i]);
      CurveName = Form("G68Dist_%.02f", Radius[i]);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, G68Dist[i], G68DistDiff[i]);
      CurveName = Form("G95Dist_%.02f", Radius[i]);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, G95Dist[i], G95DistDiff[i]);
   }

   vector<TGraph> GMeanEta(4), GMeanDiffEta(4);
   vector<TGraph> GMedianEta(4), GMedianDiffEta(4);
   vector<TGraph> GRMSEta(4), GRMSDiffEta(4);
   vector<TGraph> G68DistEta(4), G68DistDiffEta(4);
   vector<TGraph> G95DistEta(4), G95DistDiffEta(4);
   for(int i = 0; i < 4; i++)
   {
      string CurveName = Form("GMean_LargeEta%d", i);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, GMeanEta[i], GMeanDiffEta[i]);
      CurveName = Form("G50_LargeEta%d", i);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, GMedianEta[i], GMedianDiffEta[i]);
      CurveName = Form("GRMS_LargeEta%d", i);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, GRMSEta[i], GRMSDiffEta[i]);
      CurveName = Form("G68Dist_LargeEta%d", i);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, G68DistEta[i], G68DistDiffEta[i]);
      CurveName = Form("G95Dist_LargeEta%d", i);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, G95DistEta[i], G95DistDiffEta[i]);
   }

   PdfFile.AddTextPage("Summary plot");

   TCanvas Canvas;

   int Colors[] = {kBlack, kAzure, kGreen + 1, kYellow + 1, kMagenta, kCyan - 7, kRed, kOrange, kTeal - 3};

   TH2D HWorld("HWorld", "Data-MC centrality mapping;Data centrality (%);Equivalent MC centrality (%)", 100, 0, 100, 100, 0, 100);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   TLegend Legend1(0.58, 0.15, 0.73, 0.50);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.03);
   Legend1.SetFillStyle(0);
   Legend1.SetBorderSize(0);

   TLegend Legend2(0.70, 0.15, 0.85, 0.50);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.03);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);

   TLegend Legend3(0.28, 0.15, 0.43, 0.341);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.03);
   Legend3.SetFillStyle(0);
   Legend3.SetBorderSize(0);

   TLegend Legend4(0.43, 0.15, 0.58, 0.341);
   Legend4.SetTextFont(42);
   Legend4.SetTextSize(0.03);
   Legend4.SetFillStyle(0);
   Legend4.SetBorderSize(0);

   Legend1.AddEntry("", "Mean", "");
   Legend2.AddEntry("", "Median", "");
   Legend3.AddEntry("", "Mean", "");
   Legend4.AddEntry("", "Median", "");
   
   Legend1.AddEntry("", "Cone", "");
   Legend2.AddEntry("", "Cone", "");
   Legend3.AddEntry("", "Rho", "");
   Legend4.AddEntry("", "Rho", "");

   for(int i = 0; i < (int)Radius.size(); i++)
   {
      GMean[i].SetLineColor(Colors[i]);
      GMean[i].SetLineStyle(kSolid);
      Legend1.AddEntry(&GMean[i], Form("%.02f", Radius[i]), "l");
      GMean[i].Draw("l");
      
      GMedian[i].SetLineColor(Colors[i]);
      GMedian[i].SetLineStyle(kDashed);
      Legend2.AddEntry(&GMedian[i], Form("%.02f", Radius[i]), "l");
      GMedian[i].Draw("l");
   }
   
   string Cs[] = {"0.0-1.3", "1.3-2.5", "2.5-3.0", "3.0-5.2"};
   for(int i = 0; i < 4; i++)
   {
      GMeanEta[i].SetLineColor(Colors[i]);
      GMeanEta[i].SetLineStyle(kDotted);
      GMeanEta[i].SetLineWidth(2);
      Legend3.AddEntry(&GMeanEta[i], Cs[i].c_str(), "l");
      GMeanEta[i].Draw("l");
      
      GMedianEta[i].SetLineColor(Colors[i]);
      GMedianEta[i].SetLineStyle(6);
      GMedianEta[i].SetLineWidth(2);
      Legend4.AddEntry(&GMedianEta[i], Cs[i].c_str(), "l");
      GMedianEta[i].Draw("l");
   }

   Legend1.Draw();
   Legend2.Draw();
   Legend3.Draw();
   Legend4.Draw();

   TGraph G45;
   G45.SetPoint(0, 0, 0);
   G45.SetPoint(1, 100, 100);
   G45.Draw("l");

   PdfFile.AddCanvas(Canvas);

   TH2D HWorld2("HWorld2", ";Data centrality (%);MC centrality shift (%)", 100, 0, 100, 100, -2, 6);
   HWorld2.SetStats(0);

   HWorld2.Draw("axis");

   for(int i = 0; i < (int)Radius.size(); i++)
   {
      GMeanDiff[i].SetLineColor(Colors[i]);
      GMeanDiff[i].SetLineStyle(kSolid);
      GMeanDiff[i].Draw("l");
      
      GMedianDiff[i].SetLineColor(Colors[i]);
      GMedianDiff[i].SetLineStyle(kDashed);
      GMedianDiff[i].Draw("l");
   }

   for(int i = 0; i < 4; i++)
   {
      GMeanDiffEta[i].SetLineColor(Colors[i]);
      GMeanDiffEta[i].SetLineStyle(kDotted);
      GMeanDiffEta[i].SetLineWidth(2);
      GMeanDiffEta[i].Draw("l");
      
      GMedianDiffEta[i].SetLineColor(Colors[i]);
      GMedianDiffEta[i].SetLineStyle(6);
      GMedianDiffEta[i].SetLineWidth(2);
      GMedianDiffEta[i].Draw("l");
   }

   Legend1.Draw();
   Legend2.Draw();
   Legend3.Draw();
   Legend4.Draw();

   PdfFile.AddCanvas(Canvas);

   TH2D HWorld3("HWorld3", ";Data centrality (%);MC centrality shift (%)", 100, 0, 100, 100, -20, 15);
   HWorld3.SetStats(0);
   HWorld3.Draw("axis");

   TLegend Legend5(0.65, 0.15, 0.80, 0.30);
   Legend5.SetTextFont(42);
   Legend5.SetTextSize(0.03);
   Legend5.SetFillStyle(0);
   Legend5.SetBorderSize(0);
   Legend5.AddEntry("", "RMS", "");

   TLegend Legend6(0.50, 0.15, 0.65, 0.30);
   Legend6.SetTextFont(42);
   Legend6.SetTextSize(0.03);
   Legend6.SetFillStyle(0);
   Legend6.SetBorderSize(0);
   Legend6.AddEntry("", "68%", "");

   TLegend Legend7(0.35, 0.15, 0.50, 0.30);
   Legend7.SetTextFont(42);
   Legend7.SetTextSize(0.03);
   Legend7.SetFillStyle(0);
   Legend7.SetBorderSize(0);
   Legend7.AddEntry("", "95%", "");

   for(int i = 0; i < 4; i++)
   {
      GRMSDiffEta[i].SetLineColor(Colors[i]);
      GRMSDiffEta[i].SetLineStyle(kDotted);
      GRMSDiffEta[i].SetLineWidth(2);
      GRMSDiffEta[i].Draw("l");
      Legend5.AddEntry(&GRMSDiffEta[i], Cs[i].c_str(), "l");
      
      G68DistDiffEta[i].SetLineColor(Colors[i]);
      G68DistDiffEta[i].SetLineStyle(6);
      G68DistDiffEta[i].SetLineWidth(2);
      G68DistDiffEta[i].Draw("l");
      Legend6.AddEntry(&G68DistDiffEta[i], Cs[i].c_str(), "l");
      
      G95DistDiffEta[i].SetLineColor(Colors[i]);
      G95DistDiffEta[i].SetLineStyle(kSolid);
      G95DistDiffEta[i].SetLineWidth(2);
      G95DistDiffEta[i].Draw("l");
      Legend7.AddEntry(&G95DistDiffEta[i], Cs[i].c_str(), "l");
   }

   Legend5.Draw();
   Legend6.Draw();
   Legend7.Draw();

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void DoMatching(PdfFileHelper &PdfFile,
   string DataFileName, string MCFileName,
   string DataCurveName, string MCCurveName,
   string Title, TGraph &GResult, TGraph &GDiff)
{
   TFile FData(DataFileName.c_str());
   TFile FMC(MCFileName.c_str());

   TGraphAsymmErrors *GData = (TGraphAsymmErrors *)FData.Get(DataCurveName.c_str());
   TGraphAsymmErrors *GMC = (TGraphAsymmErrors *)FMC.Get(MCCurveName.c_str());

   Assert(GData != nullptr, "Data curve not found!");
   Assert(GMC != nullptr, "MC curve not found!");

   vector<pair<double, double>> MCPoints;
   for(int i = 0; i < GMC->GetN(); i++)
   {
      double x, y;
      GMC->GetPoint(i, x, y);
      MCPoints.push_back(pair<double, double>{x, y});
   }
   sort(MCPoints.begin(), MCPoints.end());

   for(int i = 0; i < GData->GetN(); i++)
   {
      double x, y;
      GData->GetPoint(i, x, y);

      // deal with out-of-bound cases first
      if(y > MCPoints.begin()->second)
         continue;
      if(y < MCPoints.back().second)
         continue;

      double NewX = -1;

      for(int j = 0; j + 1 < MCPoints.size(); j++)
      {
         if(y > MCPoints[j].second || y <= MCPoints[j+1].second)
            continue;

         double X0 = MCPoints[j].first;
         double X1 = MCPoints[j+1].first;
         double Y0 = MCPoints[j].second;
         double Y1 = MCPoints[j+1].second;
         NewX = (y - Y0) / (Y1 - Y0) * (X1 - X0) + X0;

         break;
      }

      if(NewX > 0)
      {
         GResult.SetPoint(GResult.GetN(), x, NewX);
         GDiff.SetPoint(GResult.GetN(), x, NewX - x);
      }
   }

   FMC.Close();
   FData.Close();

   TGraph G45;
   G45.SetPoint(0, 0, 0);
   G45.SetPoint(1, 100, 100);

   GResult.SetLineWidth(2);
   GResult.SetLineColor(kAzure);
   GDiff.SetLineWidth(2);
   GDiff.SetLineColor(kAzure);

   TCanvas Canvas;

   GMC->Draw("apl");
   GData->Draw("pl");

   PdfFile.AddCanvas(Canvas);

   TH2D HWorld("HWorld", ";Data centrality (%);Equivalent MC centrality (%)", 100, 0, 100, 100, 0, 100);
   HWorld.SetTitle(Title.c_str());
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   GResult.Draw("l");
   G45.Draw("l");

   PdfFile.AddCanvas(Canvas);
   
   TH2D HWorld2("HWorld2", ";Data centrality (%);MC centrality shift (%)", 100, 0, 100, 100, -10, 10);
   HWorld2.SetTitle(Title.c_str());
   HWorld2.SetStats(0);

   HWorld2.Draw("axis");
   GDiff.Draw("l");

   PdfFile.AddCanvas(Canvas);

   return;
}



