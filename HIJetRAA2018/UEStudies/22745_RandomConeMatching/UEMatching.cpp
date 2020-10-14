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

   for(int i = 0; i < (int)Radius.size(); i++)
   {
      string CurveName = Form("GMean_%.02f", Radius[i]);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, GMean[i], GMeanDiff[i]);
      CurveName = Form("G50_%.02f", Radius[i]);
      DoMatching(PdfFile, DataFileName, MCFileName, CurveName, CurveName, CurveName, GMedian[i], GMedianDiff[i]);
   }

   PdfFile.AddTextPage("Summary plot");

   TCanvas Canvas;

   int Colors[] = {kBlack, kAzure, kGreen + 1, kYellow + 1, kMagenta, kCyan - 7, kRed, kOrange, kTeal - 3};

   TH2D HWorld("HWorld", "Data-MC centrality mapping;Data centrality (%);Equivalent MC centrality (%)", 100, 0, 100, 100, 0, 100);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   TLegend Legend1(0.5, 0.15, 0.7, 0.50);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetFillStyle(0);
   Legend1.SetBorderSize(0);

   TLegend Legend2(0.65, 0.15, 0.85, 0.50);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);

   Legend1.AddEntry("", "Mean", "");
   Legend2.AddEntry("", "Median", "");

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

   Legend1.Draw();
   Legend2.Draw();

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

   Legend1.Draw();
   Legend2.Draw();

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



