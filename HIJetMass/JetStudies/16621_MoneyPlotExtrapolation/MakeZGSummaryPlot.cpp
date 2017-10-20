#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TGraphAsymmErrors.h"
#include "TLatex.h"
#include "TLegend.h"

class TheoryRatio;
int main();
TheoryRatio GetRatio(string FileName, string Name, int Color, string Label, int Style = kSolid);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio, int BinCount);
void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2);

class TheoryRatio
{
public:
   TGraphAsymmErrors G;
   string Label;
public:
   TheoryRatio() {}
   TheoryRatio(TH1D *h1, TH1D *h2, int color, string label, int style = kSolid)
   {
      Initialize(h1, h2, color, label, style);
   }
   TheoryRatio(TGraphAsymmErrors *g, int color, string label, int style = kSolid)
   {
      Initialize(g, color, label, style);
   }
   void Initialize(TH1D *h1, TH1D *h2, int color, string label, int style = kSolid)
   {
      if(h1 == NULL || h2 == NULL)
         return;

      for(int i = 1; i <= h1->GetNbinsX(); i++)
      {
         double x = h1->GetXaxis()->GetBinCenter(i);
         double y1 = h1->GetBinContent(i);
         double y2 = h2->GetBinContent(i);
         double ey1 = h1->GetBinError(i);
         double ey2 = h2->GetBinError(i);
         double l = h1->GetXaxis()->GetBinLowEdge(i);
         double r = h1->GetXaxis()->GetBinUpEdge(i);

         double y = y1 / y2;
         double ey = y * sqrt(ey1 / y1 * ey1 / y1 + ey2 / y2 * ey2 / y2);

         G.SetPoint(i - 1, x, y);
         G.SetPointError(i - 1, x - l, r - x, ey, ey);
      }
      
      Label = label;

      G.SetLineColor(color);
      G.SetLineStyle(style);
      G.SetMarkerColor(color);
      G.SetMarkerStyle(21);
      G.SetMarkerSize(5);
      G.SetLineWidth(3);
   }
   void Initialize(TGraphAsymmErrors *g, int color, string label, int style = kSolid)
   {
      if(g == NULL)
         return;

      for(int i = 0; i < g->GetN(); i++)
      {
         double x, y;
         double ex1, ex2, ey1, ey2;

         g->GetPoint(i, x, y);
         ex1 = g->GetErrorXlow(i);
         ex2 = g->GetErrorXhigh(i);
         ey1 = g->GetErrorYlow(i);
         ey2 = g->GetErrorYhigh(i);

         G.SetPoint(i, x, y);
         G.SetPointError(i, ex1, ex2, ey1, ey2);
      }

      Label = label;

      G.SetLineColor(color);
      G.SetLineStyle(style);
      G.SetMarkerColor(color);
      G.SetMarkerStyle(21);
      G.SetMarkerSize(5);
      G.SetLineWidth(3);
   }
};


int main()
{
   TheoryRatio ZG1HTCEL = GetRatio("ZgGraphsHT.root", "grZgRatioHT_140_160_CEL", kGreen + 2, "HT (Coherent)", kDashed);
   TheoryRatio ZG1HTIEL = GetRatio("ZgGraphsHT.root", "grZgRatioHT_140_160_IEL", kGreen - 3, "HT (Incoherent)", kSolid);
   TheoryRatio ZG1BDMPS1 = GetRatio("ZgGraphsBDMPS.root", "grZgRatioBDMPS_140_160_qhat1", kRed, "BDMPS (#hat{q} = 1)", kSolid);
   TheoryRatio ZG1BDMPS2 = GetRatio("ZgGraphsBDMPS.root", "grZgRatioBDMPS_140_160_qhat2", kRed, "BDMPS (#hat{q} = 2)", kDashed);
   TheoryRatio ZG1SCET18 = GetRatio("ZgGraphsSCET.root", "grZgRatioSCET_140_160_g18", kOrange, "SCET (g = 1.8)", kSolid);
   TheoryRatio ZG1SCET22 = GetRatio("ZgGraphsSCET.root", "grZgRatioSCET_140_160_g22", kOrange + 2, "SCET (g = 2.2)", kDotted);
   TheoryRatio ZG2HTCEL = GetRatio("ZgGraphsHT.root", "grZgRatioHT_250_300_CEL", kGreen + 2, "HT (Coherent)", kDashed);
   TheoryRatio ZG2HTIEL = GetRatio("ZgGraphsHT.root", "grZgRatioHT_250_300_IEL", kGreen - 3, "HT (Incoherent)", kSolid);
   TheoryRatio ZG2BDMPS1 = GetRatio("ZgGraphsBDMPS.root", "grZgRatioBDMPS_250_300_qhat1", kRed, "BDMPS (#hat{q} = 1)", kSolid);
   TheoryRatio ZG2BDMPS2 = GetRatio("ZgGraphsBDMPS.root", "grZgRatioBDMPS_250_300_qhat2", kRed, "BDMPS (#hat{q} = 2)", kDashed);
   TheoryRatio ZG2SCET18 = GetRatio("ZgGraphsSCET.root", "grZgRatioSCET_250_300_g18", kOrange, "SCET (g = 1.8)", kSolid);
   TheoryRatio ZG2SCET22 = GetRatio("ZgGraphsSCET.root", "grZgRatioSCET_250_300_g22", kOrange + 2, "SCET (g = 2.2)", kDotted);

   TFile FGraphs("Graphs_SD0_DataProjected.root");

   TGraphAsymmErrors *G1AA = (TGraphAsymmErrors *)FGraphs.Get("ZGData_0_1");
   TGraphAsymmErrors *G1PP = (TGraphAsymmErrors *)FGraphs.Get("ZGSmear_0_1");
   TGraphAsymmErrors *G2AA = (TGraphAsymmErrors *)FGraphs.Get("ZGData_0_4");
   TGraphAsymmErrors *G2PP = (TGraphAsymmErrors *)FGraphs.Get("ZGSmear_0_4");
   TGraphAsymmErrors *G1AASys = (TGraphAsymmErrors *)FGraphs.Get("ZGDataSys_0_1");
   TGraphAsymmErrors *G1PPSys = (TGraphAsymmErrors *)FGraphs.Get("ZGSmearSys_0_1");
   TGraphAsymmErrors *G2AASys = (TGraphAsymmErrors *)FGraphs.Get("ZGDataSys_0_4");
   TGraphAsymmErrors *G2PPSys = (TGraphAsymmErrors *)FGraphs.Get("ZGSmearSys_0_4");

   TGraphAsymmErrors G1, G2, G1Sys, G2Sys;
   Division(G1AA, G1PP, G1, 15);
   Division(G2AA, G2PP, G2, 15);
   Division(G1AASys, G1PPSys, G1Sys, 15);
   Division(G2AASys, G2PPSys, G2Sys, 15);

   RatioGraphSetting(&G1, &G1Sys);
   RatioGraphSetting(&G2, &G2Sys);

   double BorderWidth = 150;
   double BorderHeight = 150;
   double PanelWidth = 500;
   double PanelHeight = 500;

   double TotalHeight = BorderHeight * 2 + PanelHeight;
   double TotalWidth = BorderWidth * 2 + PanelWidth * 2;

   double PadLowY = BorderHeight / TotalHeight;
   double PadHighY = (BorderHeight + PanelHeight) / TotalHeight;
   
   TCanvas Canvas("Canvas", "", TotalWidth, TotalHeight);

   TPad *Pad1 = new TPad("Pad1", "", (BorderWidth + PanelWidth * 0) / TotalWidth, PadLowY, (BorderWidth + PanelWidth * 1) / TotalWidth, PadHighY);
   TPad *Pad2 = new TPad("Pad2", "", (BorderWidth + PanelWidth * 1) / TotalWidth, PadLowY, (BorderWidth + PanelWidth * 2) / TotalWidth, PadHighY);

   Pad1->SetTopMargin(0);      Pad2->SetTopMargin(0);   
   Pad1->SetLeftMargin(0);     Pad2->SetLeftMargin(0);
   Pad1->SetRightMargin(0);    Pad2->SetRightMargin(0);
   Pad1->SetBottomMargin(0);   Pad2->SetBottomMargin(0);

   Pad1->Draw();               Pad2->Draw();

   double XMin = 0.0, XMax = 0.5;
   double YMin = 0.0, YMax = 2.0;

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetLabelSize(0);
   HWorld.GetYaxis()->SetLabelSize(0);
   HWorld.GetXaxis()->SetTickLength(0.03);
   HWorld.GetYaxis()->SetTickLength(0.03);
   HWorld.GetYaxis()->SetNdivisions(505);

   TGaxis LeftAxis(BorderWidth / TotalWidth, PadLowY, BorderWidth / TotalWidth, PadHighY, YMin, YMax, 50510, "");
   LeftAxis.SetName("LeftAxis");
   LeftAxis.SetLineWidth(0);
   LeftAxis.SetTitle("#frac{PbPb}{Smeared pp}");
   LeftAxis.SetTextFont(42);
   LeftAxis.SetLabelFont(42);
   LeftAxis.CenterTitle(true);
   LeftAxis.SetTitleOffset(1.05);
   LeftAxis.Draw();

   TGaxis BottomAxis1((BorderWidth + PanelWidth * 0) / TotalWidth, PadLowY, (BorderWidth + PanelWidth * 1) / TotalWidth, PadLowY,
      XMin, XMax - 0.00001, 1005, "");
   BottomAxis1.SetName("BottomAxis1");
   BottomAxis1.SetLineWidth(0);
   BottomAxis1.SetTitle("z_{g}");
   BottomAxis1.SetTextFont(42);
   BottomAxis1.SetLabelFont(42);
   BottomAxis1.CenterTitle(true);
   BottomAxis1.SetTitleOffset(1.05);
   BottomAxis1.Draw();

   TGaxis BottomAxis2((BorderWidth + PanelWidth * 1) / TotalWidth, PadLowY, (BorderWidth + PanelWidth * 2) / TotalWidth, PadLowY,
      XMin, XMax, 1005, "");
   BottomAxis2.SetName("BottomAxis2");
   BottomAxis2.SetLineWidth(0);
   BottomAxis2.SetTitle("z_{g}");
   BottomAxis2.SetTextFont(42);
   BottomAxis2.SetLabelFont(42);
   BottomAxis2.CenterTitle(true);
   BottomAxis2.SetTitleOffset(1.05);
   BottomAxis2.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);

   Latex.SetTextSize(0.060);
   Latex.DrawLatex(BorderWidth / TotalWidth, (BorderHeight + PanelHeight) / TotalHeight + 0.015, "#font[62]{CMS} #font[52]{Projection}");

   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(30);
   Latex.DrawLatex((BorderWidth + PanelWidth * 2) / TotalWidth, (BorderHeight + PanelHeight + BorderHeight * 0.5) / TotalHeight, "0-10%, anti-kt R = 0.4, |#eta_{jet}| < 1.3");
   Latex.DrawLatex((BorderWidth + PanelWidth * 2) / TotalWidth, (BorderHeight + PanelHeight + BorderHeight * 0.25) / TotalHeight, "Soft drop z_{cut} = 0.1, #beta = 0.0, #DeltaR_{12} > 0.1");
   Latex.DrawLatex((BorderWidth + PanelWidth * 2) / TotalWidth, (BorderHeight + PanelHeight + 0.000) / TotalHeight, "PbPb 10 nb^{-1} (5.02 TeV)");

   Latex.SetTextAlign(22);
   Latex.DrawLatex((BorderWidth + PanelWidth * 0.5) / TotalWidth, (BorderHeight + PanelHeight * 0.93) / TotalHeight, "140 < p_{T}^{jet} < 160 GeV");
   Latex.DrawLatex((BorderWidth + PanelWidth * 1.5) / TotalWidth, (BorderHeight + PanelHeight * 0.93) / TotalHeight, "250 < p_{T}^{jet} < 300 GeV");

   TGraph GLine;
   GLine.SetPoint(0, XMin, 1);
   GLine.SetPoint(1, XMax, 1);

   Pad1->cd();
   HWorld.Draw("");
   G1Sys.Draw("2");
   G1.Draw("p");
   ZG1HTCEL.G.Draw("l");
   ZG1HTIEL.G.Draw("l");
   ZG1BDMPS1.G.Draw("l");
   ZG1BDMPS2.G.Draw("l");
   ZG1SCET18.G.Draw("l");
   ZG1SCET22.G.Draw("l");
   GLine.Draw("l");
   Pad1->Update();

   Pad2->cd();
   HWorld.Draw("");
   G2Sys.Draw("2");
   G2.Draw("p");
   ZG2HTCEL.G.Draw("l");
   ZG2HTIEL.G.Draw("l");
   ZG2BDMPS1.G.Draw("l");
   ZG2BDMPS2.G.Draw("l");
   ZG2SCET18.G.Draw("l");
   ZG2SCET22.G.Draw("l");
   GLine.Draw("l");
   Pad2->Update();

   Canvas.cd();

   TLegend Legend((BorderWidth + PanelWidth * 0.40) / TotalWidth, (BorderHeight + PanelHeight * 0.75) / TotalHeight, (BorderWidth + PanelWidth * 0.85) / TotalWidth, (BorderHeight + 0.65 * PanelHeight) / TotalHeight);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&G1Sys, "Projection", "plf");
   Legend.Draw();

   TLegend Legend1((BorderWidth + PanelWidth * 0.05) / TotalWidth, (BorderHeight + PanelHeight * 0.25) / TotalHeight, (BorderWidth + PanelWidth * 0.50) / TotalWidth, (BorderHeight + 0.05 * PanelHeight) / TotalHeight);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetFillStyle(0);
   Legend1.SetBorderSize(0);
   Legend1.AddEntry("", "HT", "");
   Legend1.AddEntry(&ZG1HTCEL.G, "Coherent", "l");
   Legend1.AddEntry(&ZG1HTIEL.G, "Incoherent", "l");
   Legend1.Draw();

   TLegend Legend2((BorderWidth + PanelWidth * 0.50) / TotalWidth, (BorderHeight + PanelHeight * 0.25) / TotalHeight, (BorderWidth + PanelWidth * 0.95) / TotalWidth, (BorderHeight + 0.05 * PanelHeight) / TotalHeight);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry("", "BDMPS", "");
   Legend2.AddEntry(&ZG1BDMPS1.G, "#hat{q} = 1 GeV/fm^{2}", "l");
   Legend2.AddEntry(&ZG1BDMPS2.G, "#hat{q} = 2 GeV/fm^{2}", "l");
   Legend2.Draw();

   TLegend Legend3((BorderWidth + PanelWidth * 1.15) / TotalWidth, (BorderHeight + PanelHeight * 0.25) / TotalHeight, (BorderWidth + PanelWidth * 1.60) / TotalWidth, (BorderHeight + 0.05 * PanelHeight) / TotalHeight);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.035);
   Legend3.SetFillStyle(0);
   Legend3.SetBorderSize(0);
   Legend3.AddEntry("", "SCET_{g}", "");
   Legend3.AddEntry(&ZG1SCET18.G, "g = 1.8", "l");
   Legend3.AddEntry(&ZG1SCET22.G, "g = 2.2", "l");
   Legend3.Draw();

   Canvas.SaveAs("ZGMoneyPlot.pdf");

   FGraphs.Close();

   return 0;
}

TheoryRatio GetRatio(string FileName, string Name, int Color, string Label, int Style)
{
   TheoryRatio Result;

   TFile File(FileName.c_str());

   Result.Initialize((TGraphAsymmErrors *)File.Get(Name.c_str()), Color, Label, Style);

   File.Close();

   return Result;
}

void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio, int BinCount)
{
   if(G1 == NULL || G2 == NULL)
      return;

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
         int N = GRatio.GetN();
         GRatio.SetPoint(N, x1, ratio);
         GRatio.SetPointError(N, xl1, xh1, yl, yh);
      }
   }

   GRatio.SetName(Form("Ratio_%s_%s", G1->GetName(), G2->GetName()));
}

void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2)
{
   if(G1 != NULL)
   {
      G1->SetLineColor(kBlack);
      G1->SetLineWidth(2);
      G1->SetMarkerColor(kBlack);
      G1->SetMarkerStyle(20);
      G1->SetMarkerSize(3);
   }

   if(G2 != NULL)
   {
      // was kBlue - 9
      G2->SetLineWidth(0);
      G2->SetFillColor(kGray);
      G2->SetMarkerStyle(20);
      G2->SetMarkerSize(3);
   }
}




