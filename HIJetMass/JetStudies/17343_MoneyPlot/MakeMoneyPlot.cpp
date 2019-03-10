#include <iostream>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLine.h"
#include "TLatex.h"
#include "TLegend.h"

#include "PlotHelper3.h"

#define SD0 0
#define SD7 1

int main();
void MakePlot(vector<TGraphAsymmErrors *> G, vector<TGraphAsymmErrors *> T, string OutputBase, int Preset = SD0);
bool Divide(vector<TGraphAsymmErrors *> &G, vector<TGraphAsymmErrors *> &R, double YShift, double RShift);
bool DivideTheory(vector<TGraphAsymmErrors *> &T, vector<TGraphAsymmErrors *> &R, double YShift, double RShift);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *GRatio);
void ShiftUp(TGraphAsymmErrors *G, double Amount);
TGraphAsymmErrors *HistogramToGraph(TH1D *H);

int main()
{
   TFile F0("Graphs_SD0_DataCentered.root");
   TFile F7("Graphs_SD7_DataCentered.root");
   TFile FT0("PickedPlots_SD0.root");
   TFile FT7("PickedPlots_SD7.root");

   vector<TGraphAsymmErrors *> G(4);
   vector<TGraphAsymmErrors *> T(6);

   G[0]  = (TGraphAsymmErrors *)F0.Get("MassData0_0_1")->Clone();
   G[1]  = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_1")->Clone();
   G[2]  = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_1")->Clone();
   G[3]  = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_1")->Clone();

   T[0]  = HistogramToGraph((TH1D *)FT0.Get("JewelOffSB_C0PT1"));
   T[1]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacSB_C0PT1"));
   T[2]  = HistogramToGraph((TH1D *)FT0.Get("JewelOnS_C0PT1"));
   T[3]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacS_C0PT1"));
   T[4]  = HistogramToGraph((TH1D *)FT0.Get("QPythiaMedSB_C0PT1"));
   T[5]  = HistogramToGraph((TH1D *)FT0.Get("QPythiaVacSB_C0PT1"));
   
   MakePlot(G, T, "Plots/SD0", SD0);

   G[0] = (TGraphAsymmErrors *)F7.Get("MassData_0_1")->Clone();
   G[1] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_1")->Clone();
   G[2] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_1")->Clone();
   G[3] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_1")->Clone();

   T[0]  = HistogramToGraph((TH1D *)FT7.Get("JewelOffS_C0PT1"));
   T[1]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT1"));
   T[2]  = HistogramToGraph((TH1D *)FT7.Get("JewelOnS_C0PT1"));
   T[3]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT1"));
   T[4]  = HistogramToGraph((TH1D *)FT7.Get("QPythiaMedS_C0PT1"));
   T[5]  = HistogramToGraph((TH1D *)FT7.Get("QPythiaVacS_C0PT1"));
   
   MakePlot(G, T, "Plots/SD7", SD7);

   FT7.Close();
   FT0.Close();
   F7.Close();
   F0.Close();

   return 0;
}

void MakePlot(vector<TGraphAsymmErrors *> G, vector<TGraphAsymmErrors *> T, string OutputBase, int Preset)
{
   // Inputs: edit to your liking

   double LeftMargin, RightMargin, TopMargin, BottomMargin, Height, Width;
   double XMin, XMax, YMin, YMax, RMin, RMax;
   double HeaderSize;
   double TextSpacing;
   double TextYX, TextYY, TextRX, TextRY;
   int TextRAlign, TextYAlign;
   int AxisStyle, TopAxisStyle;
   double LegendL, LegendT, LegendRL, LegendRT, LegendW, LegendH;

   LeftMargin = 100;
   RightMargin = 50;
   TopMargin = 50;
   BottomMargin = 75;
   Height = 500;
   Width = 500;

   TextSpacing = 0.055;
      
   LegendW = 0.52;
   LegendH = 0.25;

   if(Preset == SD0)
   {
      XMin = 0.00;   XMax = 0.27;
      YMin = 0.00;   YMax = 13.99;
      RMin = 0.00;   RMax = 19.99;

      HeaderSize = 1.5;

      TextYAlign = 22;
      TextYX = 0.50;
      TextYY = 9.00;
      TextRAlign = 22;
      TextRX = 0.50;
      TextRY = 4.00;
   
      AxisStyle = 502;
      TopAxisStyle = 505;

      LegendL = 0.08;
      LegendT = 0.75;
      LegendRL = 0.08;
      LegendRT = 0.60;
   }
   if(Preset == SD7)
   {
      XMin = 0.00;   XMax = 0.26;
      YMin = 0.00;   YMax = 24.99;
      RMin = 0.00;   RMax = 9.99;

      HeaderSize = 1.5;

      TextYAlign = 22;
      TextYX = 0.70;
      TextYY = 5.50;
      TextRAlign = 22;
      TextRX = 0.50;
      TextRY = 2.50;
   
      AxisStyle = 502;
      TopAxisStyle = 505;

      LegendL = 0.50;
      LegendT = 0.50;
      LegendRL = 0.08;
      LegendRT = 0.60;
   }

   // Derived inputs.  Don't edit.

   double TotalHeight = Height + TopMargin + BottomMargin;
   double TotalWidth = Width + LeftMargin + RightMargin;

   double WorldYMin = YMin;
   double WorldYMax = YMax;
   double YShift = YMax - YMin;
   
   double WorldRMin = RMin;
   double WorldRMax = RMax;
   double RShift = RMax - RMin;

   double PanelHeight = Height / (1 + HeaderSize);

   // Canvas and pad settings

   TCanvas Canvas("Canvas", "", TotalWidth, TotalHeight);
   TPad *Pad = new TPad("Pad", "", LeftMargin / TotalWidth, BottomMargin / TotalHeight,
      (LeftMargin + Width) / TotalWidth, (BottomMargin + Height) / TotalHeight);
   Pad->SetTopMargin(0);
   Pad->SetRightMargin(0);
   Pad->SetBottomMargin(0);
   Pad->SetLeftMargin(0);
   Pad->Draw();

   // Make sure the inputs are done correctly

   vector<TGraphAsymmErrors *> R(2, NULL);
   bool Success = Divide(G, R, YShift, RShift);
   if(Success == false)
   {
      for(int i = 0; i < 4; i++)
      {
         if(G[i] != NULL)
            delete G[i];
         G[i] = NULL;
      }   
      for(int i = 0; i < 6; i++)
      {
         if(T[i] != NULL)
            delete T[i];
         T[i] = NULL;
      }
      return;
   }

   bool HasTheory = true;
   for(int i = 0; i < 6; i++)
      if(T[i] == NULL)
         HasTheory = false;

   vector<TGraphAsymmErrors *> RT(3, NULL);
   if(HasTheory == true)
   {
      Success = DivideTheory(T, RT, YShift, RShift);
      if(Success == false)
      {
         for(int i = 0; i < 4; i++)
         {
            if(G[i] != NULL)
               delete G[i];
            G[i] = NULL;
         }
         for(int i = 0; i < 6; i++)
         {
            if(T[i] != NULL)
               delete T[i];
            T[i] = NULL;
         }
         return;
      }
   }

   // Set the stage

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, WorldYMin, WorldYMax);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetLabelSize(0);
   HWorld.GetYaxis()->SetLabelSize(0);
   HWorld.GetXaxis()->SetTickLength(0);
   HWorld.GetYaxis()->SetTickLength(0);
   
   TH2D HWorldRatio("HWorldRatio", ";;", 100, XMin, XMax, 100, WorldRMin, WorldRMax);
   HWorldRatio.SetStats(0);
   HWorldRatio.GetXaxis()->SetLabelSize(0);
   HWorldRatio.GetYaxis()->SetLabelSize(0);
   HWorldRatio.GetXaxis()->SetTickLength(0);
   HWorldRatio.GetYaxis()->SetTickLength(0);

   // Prepare axis

   TGaxis BottomAxis(LeftMargin / TotalWidth, BottomMargin / TotalHeight,
      (LeftMargin + Width) / TotalWidth, BottomMargin / TotalHeight,
      XMin, XMax, 1005, "S");
   BottomAxis.SetName("BottomAxis");
   BottomAxis.SetTitle("M_{g} / p_{T,jet}");
   BottomAxis.SetTickLength(0.025);
   BottomAxis.SetTextFont(42);
   BottomAxis.SetLabelFont(42);
   BottomAxis.CenterTitle(true);
   BottomAxis.SetLabelOffset(0.015);
   BottomAxis.SetTitleSize(0.050);
   BottomAxis.SetTitleOffset(1.10);
   BottomAxis.Draw();

   TGaxis LeftAxis(LeftMargin / TotalWidth, BottomMargin / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + Height) / TotalHeight,
      YMin, YMax, 510, "S");
   LeftAxis.SetName("LeftAxis");
   LeftAxis.SetTitle("#frac{1}{N} #frac{d N}{d M_{g} / p_{T,jet}}");
   LeftAxis.SetTextFont(42);
   LeftAxis.SetLabelFont(42);
   LeftAxis.CenterTitle(true);
   LeftAxis.SetTitleSize(0.050);
   LeftAxis.SetTitleOffset(1.20);
   LeftAxis.SetTickLength(0.025);
   LeftAxis.Draw();

   TGaxis RightAxis((LeftMargin + Width) / TotalWidth, BottomMargin / TotalHeight,
      (LeftMargin + Width) / TotalWidth, (BottomMargin + Height) / TotalHeight,
      YMin, YMax, 510, "S+L");
   RightAxis.SetName("RightAxis");
   RightAxis.SetTitle("");
   RightAxis.SetTickLength(0.025);
   RightAxis.SetLabelFont(42);
   RightAxis.SetLabelSize(0);
   RightAxis.Draw();

   // Prepare TGraphs and TLines

   TLine UnityLine;
   UnityLine.SetLineStyle(kDotted);

   // Prepare TLatex

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetNDC();

   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(31);
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth, (BottomMargin + Height) / TotalHeight + 0.005, "PbPb 404 #mub^{-1} (5.02 TeV), pp 27.4 #mub^{-1} (5.02 TeV)");

   Latex.SetTextSize(0.065);
   Latex.SetTextAlign(13);
   Latex.DrawLatex((LeftMargin) / TotalWidth + 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight, "#font[62]{CMS}");
   Latex.SetTextSize(0.045);
   Latex.DrawLatex((LeftMargin) / TotalWidth + 0.04, (BottomMargin + Height - 0.10 * TotalWidth) / TotalHeight, "#font[52]{Supplementary}");

   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(31);
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 0.4, "anti-k_{T} R = 0.4, |#eta_{jet}| < 1.3");
   if(Preset == SD0)
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 1.5, "Soft Drop z_{cut} = 0.1, #beta = 0.0");
   else
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 1.5, "Soft Drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 2.5, "#DeltaR_{12} > 0.1");
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 3.5, "Centrality: 0-10%");
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 4.5, "140 < p_{T,jet} < 160 GeV");

   // Set graph styles

   G[0]->SetMarkerSize(2.0);
   G[2]->SetMarkerSize(2.0);
  
   G[0]->SetMarkerStyle(25);
   G[2]->SetMarkerStyle(26);
   
   G[2]->SetFillStyle(3145);
   G[3]->SetFillStyle(3145);
   
   G[0]->SetFillColor(kRed - 9);
   G[1]->SetFillColor(kRed - 9);
   G[2]->SetFillColor(kGray + 2);
   G[3]->SetFillColor(kGray + 2);
   
   R[0]->SetMarkerSize(2.0);
   R[0]->SetMarkerStyle(25);
   R[0]->SetMarkerColor(kBlack);
   R[0]->SetLineColor(kBlack);
   R[0]->SetFillColor(kRed - 9);
   R[1]->SetFillColor(kRed - 9);
   

   // Prepare Legend
   
   TLegend Legend1(LegendL, LegendT - LegendH, LegendL + LegendW, LegendT);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.055);
   Legend1.SetBorderSize(0);
   Legend1.SetFillStyle(0);
   Legend1.AddEntry(G[0], "PbPb", "lpf");
   Legend1.AddEntry(G[2], "Smeared pp", "lpf");
   Legend1.AddEntry("", " ", "");
   Legend1.AddEntry("", " ", "");
   
   TLegend Legend2(LegendL, LegendT - LegendH, LegendL + LegendW, LegendT);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.055);
   Legend2.SetBorderSize(0);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(R[0], "Data", "lpf");
   if(HasTheory == true)
   {
      Legend2.AddEntry(RT[0], "Jewel (Recoil off)", "lp");
      Legend2.AddEntry(RT[1], "Jewel (Recoil on)",  "lp");
      Legend2.AddEntry(RT[2], "QPythia",            "lp");
   }
   else
   {
      Legend2.AddEntry("", " ", "");
      Legend2.AddEntry("", " ", "");
      Legend2.AddEntry("", " ", "");
   }

   TLegend Legend3(LegendRL, LegendRT - LegendH, LegendRL + LegendW, LegendRT);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.055);
   Legend3.SetBorderSize(0);
   Legend3.SetFillStyle(0);
   Legend3.AddEntry(R[0], "Data", "lpf");
   if(HasTheory == true)
   {
      Legend3.AddEntry(RT[0], "Jewel (Recoil off)", "lp");
      Legend3.AddEntry(RT[1], "Jewel (Recoil on)",  "lp");
      Legend3.AddEntry(RT[2], "QPythia",            "lp");
   }
   else
   {
      Legend3.AddEntry("", " ", "");
      Legend3.AddEntry("", " ", "");
      Legend3.AddEntry("", " ", "");
   }

   // Draw it!

   Pad->cd();
   HWorld.Draw("axis");

   for(int i = 1; i < 4; i = i + 2)
      G[i]->Draw("2");
   for(int i = 0; i < 4; i = i + 2)
      G[i]->Draw("p");
   
   Latex.SetTextSize(0.055);
   Latex.SetTextAlign(TextYAlign);

   HWorld.Draw("axis same");

   Legend1.Draw();

   Canvas.cd();

   Canvas.SaveAs((OutputBase + "_Spectrum.pdf").c_str());

   // Draw ratio!

   LeftAxis.SetWmin(RMin);    LeftAxis.SetWmax(RMax);
   RightAxis.SetWmin(RMin);   RightAxis.SetWmax(RMax);
   
   LeftAxis.SetTitle("#frac{PbPb}{Smeared pp}");

   Pad->cd();

   HWorldRatio.Draw("axis");

   R[1]->Draw("2");

   UnityLine.DrawLine(XMin, 1, XMax, 1);

   R[0]->Draw("p");

   if(HasTheory == true)
   {
      RT[0]->SetLineWidth(4);
      RT[1]->SetLineWidth(4);
      RT[2]->SetLineWidth(4);

      RT[0]->SetLineColor(kGreen - 2);
      RT[1]->SetLineColor(kBlue);
      RT[2]->SetLineColor(kRed);

      RT[0]->SetLineStyle(kSolid);
      RT[1]->SetLineStyle(kDashed);
      RT[2]->SetLineStyle(kDotted);

      RT[0]->SetMarkerStyle(20);
      RT[1]->SetMarkerStyle(20);
      RT[2]->SetMarkerStyle(20);

      RT[0]->SetMarkerSize(0);
      RT[1]->SetMarkerSize(0);
      RT[2]->SetMarkerSize(0);

      RT[0]->SetMarkerColor(kGreen - 2);
      RT[1]->SetMarkerColor(kBlue);
      RT[2]->SetMarkerColor(kRed);

      for(int i = 0; i < 3; i++)
         RT[i]->Draw("l");
   }
   
   Latex.SetTextSize(0.055);
   Latex.SetTextAlign(TextRAlign);

   HWorldRatio.Draw("axis same");

   Legend3.Draw();

   Canvas.cd();

   Canvas.SaveAs((OutputBase + "_Ratio.pdf").c_str());

   // Clean up

   for(int i = 0; i < 4; i++)
   {
      if(G[i] != NULL)
         delete G[i];
      G[i] = NULL;
   }
   for(int i = 0; i < 2; i++)
      if(R[i] != NULL)
         delete R[i];
   
   for(int i = 0; i < 6; i++)
   {
      if(T[i] != NULL)
         delete T[i];
      T[i] = NULL;
   }
   for(int i = 0; i < 3; i++)
      if(RT[i] != NULL)
         delete RT[i];
}

bool Divide(vector<TGraphAsymmErrors *> &G, vector<TGraphAsymmErrors *> &R, double YShift, double RShift)
{
   if(G.size() != 4)
      return false;
   for(int i = 0; i < 4; i++)
      if(G[i] == NULL)
         return false;

   for(int i = 0; i < 2; i++)
   {
      if(R[i] != NULL)
         delete R[i];
      R[i] = new TGraphAsymmErrors;
   }

   Division(G[0], G[2], R[0]);
   Division(G[1], G[3], R[1]);

   return true;
}

bool DivideTheory(vector<TGraphAsymmErrors *> &T, vector<TGraphAsymmErrors *> &R, double YShift, double RShift)
{
   if(T.size() != 6)
      return false;
   for(int i = 0; i < 6; i++)
      if(T[i] == NULL)
         return false;

   for(int i = 0; i < 3; i++)
   {
      if(R[i] != NULL)
         delete R[i];
      R[i] = new TGraphAsymmErrors;
   }

   Division(T[0], T[1], R[0]);
   Division(T[2], T[3], R[1]);
   Division(T[4], T[5], R[2]);

   return true;
}

void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *GRatio)
{
   if(G1 == NULL || G2 == NULL || GRatio == NULL)
      return;

   int BinCount = min(G1->GetN(), G2->GetN());

   for(int i = 0; i < BinCount; i++)
   {
      double x1, x2, y1, y2;
      G1->GetPoint(i, x1, y1);
      G2->GetPoint(i, x2, y2);

      double xl1, xh1, xl2, xh2;
      xl1 = G1->GetErrorXlow(i);
      xh1 = G1->GetErrorXhigh(i);
      xl2 = G2->GetErrorXlow(i);
      xh2 = G2->GetErrorXhigh(i);

      double yl1, yh1, yl2, yh2;
      yl1 = G1->GetErrorYlow(i);
      yh1 = G1->GetErrorYhigh(i);
      yl2 = G2->GetErrorYlow(i);
      yh2 = G2->GetErrorYhigh(i);

      double ratio = (y1 / y2);

      double yl = ratio * sqrt((yl1 / y1) * (yl1 / y1) + (yl2 / y2) * (yl2 / y2));
      double yh = ratio * sqrt((yh1 / y1) * (yh1 / y1) + (yh2 / y2) * (yh2 / y2));

      if(x1 == x1 && x2 == x2 && ratio == ratio)
      {
         int N = GRatio->GetN();
         GRatio->SetPoint(N, x1, ratio);
         GRatio->SetPointError(N, xl1, xh1, yl, yh);
      }
   }
}

void ShiftUp(TGraphAsymmErrors *G, double Amount)
{
   if(G == NULL)
      return;

   int BinCount = G->GetN();
   for(int i = 0; i < BinCount; i++)
   {
      double x, y;
      G->GetPoint(i, x, y);
      G->SetPoint(i, x, y + Amount);
   }
}

TGraphAsymmErrors *HistogramToGraph(TH1D *H)
{
   if(H == NULL)
      return NULL;

   TGraphAsymmErrors *G = new TGraphAsymmErrors;

   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      double x = H->GetBinCenter(i);
      double y = H->GetBinContent(i);

      double l = H->GetXaxis()->GetBinLowEdge(i);
      double r = H->GetXaxis()->GetBinUpEdge(i);

      double e = H->GetBinError(i);

      if(y != y)
         continue;
      if(x > 0.27)
         continue;

      int I = G->GetN();
      G->SetPoint(I, x, y);
      // G->SetPointError(I, x - l, r - x, e, e);
   }

   return G;
}










