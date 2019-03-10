#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"

#define MASSBINCOUNT 9
#define ZGBINCOUNT 10
#define DRBINCOUNT 15
#define PTPTBINCOUNT 50

int main();
void DoGraph(vector<TGraphAsymmErrors *> Gs, string OutputBase);
void PadSetting(TPad *Pad);
void GraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *G3, TGraphAsymmErrors *G4,
      TGraphAsymmErrors *G5, TGraphAsymmErrors *G6);
void GraphTidying(TGraphAsymmErrors *G);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio, int BinCount, bool IgnoreFirstError);
void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, int MC);

int main()
{
   TFile FGraphs0("Graphs_SD0_Centered.root");
   TFile FGraphs7("Graphs_SD7_Centered.root");

   vector<TGraphAsymmErrors *> Gs(12);
   Gs[0]  = (TGraphAsymmErrors *)FGraphs0.Get("Data_MassData_4_2");
   Gs[1]  = (TGraphAsymmErrors *)FGraphs0.Get("Data_MassDataSys_4_2");
   Gs[2]  = (TGraphAsymmErrors *)FGraphs7.Get("Data_MassData_4_2");
   Gs[3]  = (TGraphAsymmErrors *)FGraphs7.Get("Data_MassDataSys_4_2");
   Gs[4]  = (TGraphAsymmErrors *)FGraphs0.Get("PP6_MassData_4_2");
   Gs[5]  = (TGraphAsymmErrors *)FGraphs0.Get("PP6_MassDataSys_4_2");
   Gs[6]  = (TGraphAsymmErrors *)FGraphs7.Get("PP6_MassData_4_2");
   Gs[7]  = (TGraphAsymmErrors *)FGraphs7.Get("PP6_MassDataSys_4_2");
   Gs[8]  = (TGraphAsymmErrors *)FGraphs0.Get("PPHerwig_MassData_4_2");
   Gs[9]  = (TGraphAsymmErrors *)FGraphs0.Get("PPHerwig_MassDataSys_4_2");
   Gs[10] = (TGraphAsymmErrors *)FGraphs7.Get("PPHerwig_MassData_4_2");
   Gs[11] = (TGraphAsymmErrors *)FGraphs7.Get("PPHerwig_MassDataSys_4_2");

   DoGraph(Gs, "Plots/PrettyPlotCentralityBin0");

   FGraphs7.Close();
   FGraphs0.Close();

   return 0;
}

void DoGraph(vector<TGraphAsymmErrors *> Gs, string OutputBase)
{
   bool LogMass = false;

   if(Gs.size() != 12)
      return;

   TGraphAsymmErrors *G1Data     = Gs[0];
   TGraphAsymmErrors *G1DataSys  = Gs[1];
   TGraphAsymmErrors *G2Data     = Gs[2];
   TGraphAsymmErrors *G2DataSys  = Gs[3];
   TGraphAsymmErrors *G1MC1      = Gs[4];
   TGraphAsymmErrors *G1MC1Sys   = Gs[5];
   TGraphAsymmErrors *G2MC1      = Gs[6];
   TGraphAsymmErrors *G2MC1Sys   = Gs[7];
   TGraphAsymmErrors *G1MC2      = Gs[8];
   TGraphAsymmErrors *G1MC2Sys   = Gs[9];
   TGraphAsymmErrors *G2MC2      = Gs[10];
   TGraphAsymmErrors *G2MC2Sys   = Gs[11];

   GraphSetting(G1Data, G1DataSys, G1MC1, G1MC1Sys, G1MC2, G1MC2Sys);
   GraphSetting(G2Data, G2DataSys, G2MC1, G2MC1Sys, G2MC2, G2MC2Sys);

   GraphTidying(G1DataSys);   GraphTidying(G1MC1Sys);   GraphTidying(G1MC2Sys);
   GraphTidying(G2DataSys);   GraphTidying(G2MC1Sys);   GraphTidying(G2MC2Sys);

   TGraphAsymmErrors G1Ratio1, G1Ratio1Sys, G1Ratio2, G1Ratio2Sys;
   TGraphAsymmErrors G2Ratio1, G2Ratio1Sys, G2Ratio2, G2Ratio2Sys;

   int BinCount = MASSBINCOUNT;

   Division(G1MC1,     G1Data,    G1Ratio1,    BinCount, false);
   Division(G1DataSys, G1DataSys, G1Ratio1Sys, BinCount, true);
   Division(G2MC1,     G2Data,    G2Ratio1,    BinCount, false);
   Division(G2DataSys, G2DataSys, G2Ratio1Sys, BinCount, true);
   Division(G1MC2,     G1Data,    G1Ratio2,    BinCount, false);
   Division(G1DataSys, G1DataSys, G1Ratio2Sys, BinCount, true);
   Division(G2MC2,     G2Data,    G2Ratio2,    BinCount, false);
   Division(G2DataSys, G2DataSys, G2Ratio2Sys, BinCount, true);

   RatioGraphSetting(&G1Ratio1, &G1Ratio1Sys, 1);
   RatioGraphSetting(&G2Ratio1, &G2Ratio1Sys, 1);
   RatioGraphSetting(&G1Ratio2, &G1Ratio2Sys, 2);
   RatioGraphSetting(&G2Ratio2, &G2Ratio2Sys, 2);

   double Border = 350;
   double PadWidth = 1000;
   double PadHeight = 1000;
   double RatioHeight = 500;

   double TotalHeight = RatioHeight + PadHeight + Border * 2;
   double TotalWidth = PadWidth * 2 + Border * 2;

   double PadLowY  = (Border + RatioHeight) / TotalHeight;
   double PadHighY = (Border + RatioHeight + PadHeight) / TotalHeight;
   double PadRatioLowY  = Border / TotalHeight;

   double WorldMin = 0;
   double WorldMax = 25;
   double MassMin = 0;
   double MassMax = 0.26;
   double RatioMin = 0.0000;
   double RatioMax = 1.9999;

   TGraph GLine;
   GLine.SetPoint(0, MassMin, 1);
   GLine.SetPoint(1, MassMax, 1);

   gStyle->SetPaperSize(TotalWidth / 170, TotalHeight / 170);

   TCanvas Canvas("Canvas", "", TotalWidth, TotalHeight);

   TPad *Pad1 = new TPad("Pad1", "", (Border + PadWidth * 0) / TotalWidth, PadLowY, (Border + PadWidth * 1) / TotalWidth, PadHighY);
   TPad *Pad2 = new TPad("Pad2", "", (Border + PadWidth * 1) / TotalWidth, PadLowY, (Border + PadWidth * 2) / TotalWidth, PadHighY);

   TPad *Pad3 = new TPad("Pad3", "", (Border + PadWidth * 0) / TotalWidth, PadRatioLowY, (Border + PadWidth * 1) / TotalWidth, PadLowY);
   TPad *Pad4 = new TPad("Pad4", "", (Border + PadWidth * 1) / TotalWidth, PadRatioLowY, (Border + PadWidth * 2) / TotalWidth, PadLowY);

   PadSetting(Pad1);
   PadSetting(Pad2);
   PadSetting(Pad3);
   PadSetting(Pad4);

   TH2D HWorld("HWorld", ";;", 100, MassMin, MassMax, 100, WorldMin, WorldMax);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetLabelSize(0);
   HWorld.GetYaxis()->SetLabelSize(0);

   TH2D HWorldRatio("HWorldRatio", ";;", 100, MassMin, MassMax, 100, RatioMin, RatioMax);
   HWorldRatio.SetStats(0);
   HWorldRatio.GetXaxis()->SetLabelSize(0);
   HWorldRatio.GetYaxis()->SetLabelSize(0);
   HWorldRatio.GetXaxis()->SetTickLength(0.06);
   HWorldRatio.GetYaxis()->SetTickLength(0.03);
   HWorldRatio.GetYaxis()->SetNdivisions(505);

   TGraph GData, GMC1, GMC2;
   GData.SetLineColor(G1Data->GetLineColor());
   GData.SetLineWidth(G1Data->GetLineWidth());
   GData.SetMarkerStyle(G1Data->GetMarkerStyle());
   GData.SetMarkerColor(G1Data->GetMarkerColor());
   GData.SetMarkerSize(G1Data->GetMarkerSize());
   if(G1DataSys)   GData.SetFillColor(G1DataSys->GetFillColor());
   else            GData.SetFillColor(kWhite);
   if(G1DataSys)   GData.SetFillStyle(1001);
   else            GData.SetFillStyle(0);
   GMC1.SetLineColor(G1MC1->GetLineColor());
   GMC1.SetLineWidth(G1MC1->GetLineWidth());
   GMC1.SetMarkerStyle(G1MC1->GetMarkerStyle());
   GMC1.SetMarkerColor(G1MC1->GetMarkerColor());
   GMC1.SetMarkerSize(G1MC1->GetMarkerSize());
   if(G1MC1Sys)    GMC1.SetFillColor(G1MC1Sys->GetFillColor());
   else            GMC1.SetFillColor(kWhite);
   if(G1MC1Sys)    GMC1.SetFillStyle(G1MC1Sys->GetFillStyle());
   else            GMC1.SetFillStyle(0);
   GMC2.SetLineColor(G1MC2->GetLineColor());
   GMC2.SetLineWidth(G1MC2->GetLineWidth());
   GMC2.SetMarkerStyle(G1MC2->GetMarkerStyle());
   GMC2.SetMarkerColor(G1MC2->GetMarkerColor());
   GMC2.SetMarkerSize(G1MC2->GetMarkerSize());
   if(G1MC2Sys)    GMC2.SetFillColor(G1MC2Sys->GetFillColor());
   else            GMC2.SetFillColor(kWhite);
   if(G1MC2Sys)    GMC2.SetFillStyle(3145);
   else            GMC2.SetFillStyle(0);

   Pad1->cd();
   HWorld.Draw("");
   // if(G1MC1Sys)     G1MC1Sys->Draw("2");
   // if(G1MC2Sys)     G1MC2Sys->Draw("2");
   if(G1DataSys)    G1DataSys->Draw("2");
   G1MC1->Draw("p");
   G1MC2->Draw("p");
   G1Data->Draw("p");
   HWorld.Draw("axis same");
   Pad1->Update();

   Pad2->cd();
   HWorld.Draw("");
   // if(G2MC1Sys)     G2MC1Sys->Draw("2");
   // if(G2MC2Sys)     G2MC2Sys->Draw("2");
   if(G2DataSys)    G2DataSys->Draw("2");
   G2MC1->Draw("p");
   G2MC2->Draw("p");
   G2Data->Draw("p");
   HWorld.Draw("axis same");
   Pad2->Update();

   Pad3->cd();
   HWorldRatio.Draw("");
   if(G1MC1Sys)   G1Ratio1Sys.Draw("2");
   if(G1MC2Sys)   G1Ratio2Sys.Draw("2");
   G1Ratio1.Draw("p");
   G1Ratio2.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad3->SetLogy();
   Pad3->Update();

   Pad4->cd();
   HWorldRatio.Draw("");
   if(G2MC1Sys)   G2Ratio1Sys.Draw("2");
   if(G2MC2Sys)   G2Ratio2Sys.Draw("2");
   G2Ratio1.Draw("p");
   G2Ratio2.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad4->SetLogy();
   Pad4->Update();

   Pad1->cd();
   HWorld.Draw("axis same");
   Pad1->Update();

   Pad2->cd();
   HWorld.Draw("axis same");
   Pad2->Update();

   Pad3->cd();
   HWorldRatio.Draw("axis same");
   Pad3->Update();

   Pad4->cd();
   HWorldRatio.Draw("axis same");
   Pad4->Update();

   Canvas.cd();

   string Scale = "";
   TGaxis LeftAxis1(Border / TotalWidth, (Border + RatioHeight) / TotalHeight, Border / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight,
         WorldMin, WorldMax, 50510, Scale.c_str());
   LeftAxis1.SetName("LeftAxis1");
   LeftAxis1.SetLineWidth(0);
   LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(M_{g} / p_{T}^{jet})}");
   LeftAxis1.SetTextFont(42);
   LeftAxis1.SetLabelFont(42);
   LeftAxis1.CenterTitle(true);
   LeftAxis1.SetTitleOffset(1.25);
   LeftAxis1.Draw();

   TGaxis LeftAxis2(Border / TotalWidth, Border / TotalHeight, Border / TotalWidth, (Border + RatioHeight) / TotalHeight,
         RatioMin, RatioMax, 1005, "");
   LeftAxis2.SetName("LeftAxis2");
   LeftAxis2.SetLineWidth(0);
   LeftAxis2.SetTitle("#frac{MC}{Data}");
   LeftAxis2.SetTextFont(42);
   LeftAxis2.SetLabelFont(42);
   LeftAxis2.CenterTitle(true);
   LeftAxis2.SetTitleOffset(1.25);
   LeftAxis2.Draw();

   int BottomTick = 1005;

   TGaxis BottomAxis1((Border + PadWidth * 0) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 1) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax - 0.00001, BottomTick, "");
   BottomAxis1.SetName("BottomAxis1");
   BottomAxis1.SetLineWidth(0);
      BottomAxis1.SetTitle("M_{g} / p_{T}^{jet}");
   BottomAxis1.SetTextFont(42);
   BottomAxis1.SetLabelFont(42);
   BottomAxis1.CenterTitle(true);
   BottomAxis1.Draw();

   TGaxis BottomAxis2((Border + PadWidth * 1) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 2) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax - 0.00001, BottomTick, "");
   BottomAxis2.SetName("BottomAxis2");
   BottomAxis2.SetLineWidth(0);
      BottomAxis2.SetTitle("M_{g} / p_{T}^{jet}");
   BottomAxis2.SetTextFont(42);
   BottomAxis2.SetLabelFont(42);
   BottomAxis2.CenterTitle(true);
   BottomAxis2.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);

   Latex.SetTextSize(0.06);
   Latex.SetTextAlign(10);
   Latex.DrawLatex(Border / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight + 0.005, "#font[62]{CMS}");

   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(30);
   Latex.DrawLatex((Border + PadWidth * 2) / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight, "pp 27.4 pb^{-1} (5.02 TeV)");

   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(30);
   // Latex.DrawLatex((Border + PadWidth * 2) / TotalWidth, (Border + RatioHeight + PadHeight + Border * 0.2) / TotalHeight, "anti-kt R = 0.4, |#eta_{jet}| < 1.3, 160 < p_{T}^{jet} < 180 GeV");
   Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.90) / TotalHeight, "anti-kt R = 0.4");
   Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.76) / TotalHeight, "160 < p_{T}^{jet} < 180 GeV");
   Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.65) / TotalHeight, "|#eta_{jet}| < 1.3");

   TLegend Legend((Border + PadWidth * 0.15) / TotalWidth, (Border + RatioHeight + 0.50 * PadHeight) / TotalHeight,
      (Border + PadWidth * 0.60) / TotalWidth, (Border + RatioHeight + 0.90 * PadHeight) / TotalHeight);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&GData, "Data", "lfp");
   Legend.AddEntry(&GMC1, "PYTHIA6 (Z2*)", "lp");
   Legend.AddEntry(&GMC2, "HERWIG++ (EE5C)", "lp");
   Legend.AddEntry("", " ", "");
   Legend.Draw();

   Latex.SetTextAlign(13);
   Latex.DrawLatex((Border + PadWidth * 0.4) / TotalWidth, (Border + RatioHeight + PadHeight * 0.5) / TotalHeight,
      "z_{cut} = 0.1, #beta = 0.0");
   Latex.DrawLatex((Border + PadWidth * 0.4) / TotalWidth, (Border + RatioHeight + PadHeight * 0.4) / TotalHeight,
      "#DeltaR_{12} > 0.1");
   
   Latex.DrawLatex((Border + PadWidth * 1.4) / TotalWidth, (Border + RatioHeight + PadHeight * 0.5) / TotalHeight,
      "z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex((Border + PadWidth * 1.4) / TotalWidth, (Border + RatioHeight + PadHeight * 0.4) / TotalHeight,
      "#DeltaR_{12} > 0.1");

   Canvas.SaveAs(Form("%s.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.C"  , OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}

void PadSetting(TPad *Pad)
{
   Pad->SetTopMargin(0);
   Pad->SetRightMargin(0);
   Pad->SetBottomMargin(0);
   Pad->SetLeftMargin(0);

   Pad->Draw();
}

void GraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *G3, TGraphAsymmErrors *G4,
   TGraphAsymmErrors *G5, TGraphAsymmErrors *G6)
{
   if(G1 != NULL)
   {
      // was kRed + 2
      G1->SetLineColor(kBlack);
      G1->SetMarkerColor(kBlack);
      G1->SetLineWidth(2);
      G1->SetMarkerStyle(20);
      G1->SetMarkerSize(5);
   }

   if(G2 != NULL)
   {
      // was kRed - 7
      G2->SetLineWidth(0);
      // G2->SetFillStyle(3454);
      G2->SetFillStyle(1001);
      G2->SetFillColor(kGray);
      G2->SetMarkerStyle(20);
      G2->SetMarkerSize(5);
   }

   if(G3 != NULL)
   {
      G3->SetLineColor(kBlue + 2);
      G3->SetMarkerColor(kBlue + 2);
      G3->SetLineWidth(2);
      G3->SetMarkerStyle(25);
      G3->SetMarkerSize(5);
   }

   if(G4 != NULL)
   {
      G4->SetLineWidth(0);
      G4->SetFillColor(TColor::GetColor("#50BFE6"));
      G4->SetMarkerStyle(25);
      G4->SetMarkerSize(5);
   }

   if(G5 != NULL)
   {
      G5->SetLineColor(kGreen + 3);
      G5->SetMarkerColor(kGreen + 3);
      G5->SetLineWidth(2);
      G5->SetMarkerStyle(28);
      G5->SetMarkerSize(5);
   }

   if(G6 != NULL)
   {
      G6->SetLineWidth(0);
      G6->SetFillStyle(3445);
      G6->SetFillColor(kGreen - 3);
      G6->SetMarkerStyle(28);
      G6->SetMarkerSize(5);
   }
}

void GraphTidying(TGraphAsymmErrors *G)
{
   if(G == NULL)
      return;

   double F = 1.2;

   for(int i = 0; i < G->GetN(); i++)
   {
      G->SetPointEYlow(i, G->GetErrorYlow(i) * F);
      G->SetPointEYhigh(i, G->GetErrorYhigh(i) * F);
   }
}

void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio, int BinCount, bool IgnoreFirstError)
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

      if(IgnoreFirstError == true)
      {
         yl1 = 0;
         yh1 = 0;
      }

      double ratio = (y1 / y2);

      double yl = ratio * sqrt((yl1 / y1) * (yl1 / y1) + (yl2 / y2) * (yl2 / y2));
      double yh = ratio * sqrt((yh1 / y1) * (yh1 / y1) + (yh2 / y2) * (yh2 / y2));

      if(x1 == x1 && x2 == x2 && ratio == ratio)
      {
         GRatio.SetPoint(i, x1, ratio);
         GRatio.SetPointError(i, xl1, xh1, yl, yh);
      }
      else
      {
         GRatio.SetPoint(i, -100, -100);
         GRatio.SetPointError(i, 0, 0, 0, 0);
      }
   }

   // GRatio.Print();
}

void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, int MC)
{
   int LineColor = kBlack;
   int FillColor = kBlue - 9;
   int FillStyle = 1001;
   int MarkerStyle = 20;

   if(MC == 1)
   {
      LineColor = kBlue + 2;
      FillColor = TColor::GetColor("#50BFE6");
      FillStyle = 1001;
      MarkerStyle = 25;
   }
   if(MC == 2)
   {
      LineColor = kGreen + 3;
      FillColor = kGreen - 3;
      FillStyle = 3445;
      MarkerStyle = 28;
   }

   if(G1 != NULL)
   {
      G1->SetLineWidth(2);
      G1->SetLineColor(LineColor);
      G1->SetMarkerStyle(MarkerStyle);
      G1->SetMarkerSize(5);
      G1->SetMarkerColor(LineColor);
   }

   LineColor = kBlack;
   FillColor = kGray;
   // FillStyle = 3454;
   FillStyle = 1001;
   MarkerStyle = 1;

   if(G2 != NULL)
   {
      G2->SetLineWidth(0);
      G2->SetFillColor(FillColor);
      G2->SetMarkerStyle(MarkerStyle);
      G2->SetMarkerSize(5);
      G2->SetFillStyle(FillStyle);
   }
}


