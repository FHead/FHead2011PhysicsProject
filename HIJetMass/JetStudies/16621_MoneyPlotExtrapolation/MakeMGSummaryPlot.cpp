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

int main(int argc, char *argv[]);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio, int BinCount);
void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2);

int main(int argc, char *argv[])
{
   int SD = 0;

   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " SD" << endl;
      return -1;
   }

   SD = atoi(argv[1]);

   TFile FGraphs(Form("Graphs_SD%d_DataProjected.root", SD));

   TGraphAsymmErrors *G1AA = (TGraphAsymmErrors *)FGraphs.Get("MassData0_0_1");
   TGraphAsymmErrors *G1PP = (TGraphAsymmErrors *)FGraphs.Get("MassSmear0_0_1");
   TGraphAsymmErrors *G2AA = (TGraphAsymmErrors *)FGraphs.Get("MassData0_0_4");
   TGraphAsymmErrors *G2PP = (TGraphAsymmErrors *)FGraphs.Get("MassSmear0_0_4");
   TGraphAsymmErrors *G1AASys = (TGraphAsymmErrors *)FGraphs.Get("MassDataSys0_0_1");
   TGraphAsymmErrors *G1PPSys = (TGraphAsymmErrors *)FGraphs.Get("MassSmearSys0_0_1");
   TGraphAsymmErrors *G2AASys = (TGraphAsymmErrors *)FGraphs.Get("MassDataSys0_0_4");
   TGraphAsymmErrors *G2PPSys = (TGraphAsymmErrors *)FGraphs.Get("MassSmearSys0_0_4");

   TGraphAsymmErrors G1, G2, G1Sys, G2Sys;
   Division(G1AA, G1PP, G1, 18);
   Division(G2AA, G2PP, G2, 18);
   Division(G1AASys, G1PPSys, G1Sys, 18);
   Division(G2AASys, G2PPSys, G2Sys, 18);

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

   double XMin = 0.0, XMax = 0.27;
   double YMin = 0.0, YMax = 5.0;

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
   BottomAxis1.SetTitle("M_{g} / p_{T}^{jet}");
   BottomAxis1.SetTextFont(42);
   BottomAxis1.SetLabelFont(42);
   BottomAxis1.CenterTitle(true);
   BottomAxis1.SetTitleOffset(1.05);
   BottomAxis1.Draw();

   TGaxis BottomAxis2((BorderWidth + PanelWidth * 1) / TotalWidth, PadLowY, (BorderWidth + PanelWidth * 2) / TotalWidth, PadLowY,
      XMin, XMax, 1005, "");
   BottomAxis2.SetName("BottomAxis2");
   BottomAxis2.SetLineWidth(0);
   BottomAxis2.SetTitle("M_{g} / p_{T}^{jet}");
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
   Latex.DrawLatex((BorderWidth + PanelWidth * 2) / TotalWidth, (BorderHeight + PanelHeight + BorderHeight * 0.5) / TotalHeight, "anti-kt R = 0.4, |#eta_{jet}| < 1.3");
   if(SD == 0)
      Latex.DrawLatex((BorderWidth + PanelWidth * 2) / TotalWidth, (BorderHeight + PanelHeight + BorderHeight * 0.25) / TotalHeight, "Soft drop z_{cut} = 0.1, #beta = 0.0, #DeltaR_{12} > 0.1");
   else
      Latex.DrawLatex((BorderWidth + PanelWidth * 2) / TotalWidth, (BorderHeight + PanelHeight + BorderHeight * 0.25) / TotalHeight, "Soft drop z_{cut} = 0.5, #beta = 1.5, #DeltaR_{12} > 0.1");
   Latex.DrawLatex((BorderWidth + PanelWidth * 2) / TotalWidth, (BorderHeight + PanelHeight + 0.000) / TotalHeight, "PbPb 10 nb^{-1} (#sqrt{s_{NN}} = 5.02 TeV)");

   Latex.SetTextAlign(22);
   Latex.DrawLatex((BorderWidth + PanelWidth * 0.5) / TotalWidth, (BorderHeight + PanelHeight * 0.93) / TotalHeight, "140 < p_{T}^{jet} < 160 GeV");
   Latex.DrawLatex((BorderWidth + PanelWidth * 1.5) / TotalWidth, (BorderHeight + PanelHeight * 0.93) / TotalHeight, "200 < p_{T}^{jet} < 300 GeV");

   TGraph GLine;
   GLine.SetPoint(0, XMin, 1);
   GLine.SetPoint(1, XMax, 1);

   G1.Print();
   G1Sys.Print();

   Pad1->cd();
   HWorld.Draw("");
   G1Sys.Draw("2");
   G1.Draw("p");
   GLine.Draw("l");
   Pad1->Update();

   Pad2->cd();
   HWorld.Draw("");
   G2Sys.Draw("2");
   G2.Draw("p");
   GLine.Draw("l");
   Pad2->Update();

   Canvas.cd();

   TLegend Legend((BorderWidth + PanelWidth * 0.40) / TotalWidth, (BorderHeight + PanelHeight * 0.75) / TotalHeight, (BorderWidth + PanelWidth * 0.85) / TotalWidth, (BorderHeight + 0.55 * PanelHeight) / TotalHeight);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry("", "Centrality: 0-10%", "");
   Legend.AddEntry(&G1Sys, "Projection", "plf");
   Legend.Draw();

   Canvas.SaveAs(Form("MGMoneyPlot_%d.pdf", SD));

   FGraphs.Close();

   return 0;
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




