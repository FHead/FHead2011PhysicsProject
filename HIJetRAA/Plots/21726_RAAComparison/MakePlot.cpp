#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "TH1D.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TColor.h"
#include "TBox.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"

#define R02 0
#define R03 1
#define R04 2
#define R06 3
#define R08 4
#define R10 5

#define C0 0
#define C1 1
#define C2 2
#define C3 3

#define C01 0
#define C12 1
#define C23 2
#define C34 3
#define C45 4
#define C56 5
#define C67 6
#define C78 7

int Color[5] = {-1, -1, -1, -1, -1};

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
void GetRAA(TH1D &H, string FileName, int R, int C, bool Sys = false);
void GetATLAS(TGraphAsymmErrors &G, string FileName, int C, bool Sys = false);
void Rebin(TH1D &H1, TH1D &H2);
void DrawLumiTAA(double Lumi, double TAA[4], double XMin, double XMax);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   int C = CL.GetInt("C", 0);

   // Preamble: sizing
   int PanelSizeX = 750;
   int PanelSizeY = 500;
   int PaddingWidthL = 50;
   int PaddingWidthR = 26;
   int PaddingHeight = 50;
   int CanvasWidth = PanelSizeX * 1 + PaddingWidthL + PaddingWidthR;
   int CanvasHeight = PanelSizeY * 1 + PaddingHeight * 2;

   double PadX0 = (double)PaddingWidthL / CanvasWidth;
   double PadY0 = (double)PaddingHeight / CanvasHeight;
   double PadDX = (double)PanelSizeX / CanvasWidth;
   double PadDY = (double)PanelSizeY / CanvasHeight;

   double XMin = 150;
   double XMax = 1100;
   double YMin = 0.0;
   double YMax = 1.199;

   string File = "RAA_Smooth.root";
   string ATLASFile = "ATLAS.root";

   double Lumi = 0.023;
   double TAAFull[4] = {0.018646, 0.025341, 0.051233, 0.100719};
   double TAA[4] = {0};
   TAA[C] = TAAFull[C];
   
   string Cs[] = {"0to10", "10to30", "30to50", "50to90"};
   string CsCMS[] = {"CMS 0 - 10%", "CMS 10 - 30%", "CMS 30 - 50%", "CMS 50 - 90%"};
   string CsATLAS[] = {"ATLAS 0 - 10%", "ATLAS 10 - 20%", "ATLAS 20 - 30%", "ATLAS 30 - 40%", "ATLAS 40 - 50%", "ATLAS 50 - 60%", "ATLAS 60 - 70%", "ATLAS 70 - 80%"};

   // Start declaring canvas, pad, axis, and axis title (as TLatex)
   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   TPad P1("P1", "", PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 1, 0);
   SetPad(P1);
  
   Canvas.cd();

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 510, "G");
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin, YMax, 510, "");

   SetAxis(AxisX1);
   SetAxis(AxisY1);

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 0.5, PadY0 * 0.20, "p_{T}^{jet} (GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.20, PadY0 + PadDY * 0.5, "R_{AA}");

   Latex.SetTextFont(62);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDY + PadY0 * 0.15, "CMS #font[52]{Preliminary}");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 1, PadY0 + PadDY + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 404 #mub^{-1}, pp 27.4 pb^{-1}");

   TGraph GLine;
   GLine.SetPoint(0, XMin, 1);
   GLine.SetPoint(1, XMax, 1);
   GLine.SetLineStyle(kDashed);

   double Bins[] = {200, 250, 300, 400, 500, 1000};
   TH1D HR04C00RAA("HR04C00RAA", "", 5, Bins);   GetRAA(HR04C00RAA, File, R04, C0, false);
   TH1D HR04C01RAA("HR04C01RAA", "", 5, Bins);   GetRAA(HR04C01RAA, File, R04, C1, false);
   TH1D HR04C02RAA("HR04C02RAA", "", 5, Bins);   GetRAA(HR04C02RAA, File, R04, C2, false);
   TH1D HR04C03RAA("HR04C03RAA", "", 5, Bins);   GetRAA(HR04C03RAA, File, R04, C3, false);
   
   TH1D HR04C00RAASys("HR04C00RAASys", "", 5, Bins);   GetRAA(HR04C00RAASys, File, R04, C0, true);
   TH1D HR04C01RAASys("HR04C01RAASys", "", 5, Bins);   GetRAA(HR04C01RAASys, File, R04, C1, true);
   TH1D HR04C02RAASys("HR04C02RAASys", "", 5, Bins);   GetRAA(HR04C02RAASys, File, R04, C2, true);
   TH1D HR04C03RAASys("HR04C03RAASys", "", 5, Bins);   GetRAA(HR04C03RAASys, File, R04, C3, true);

   // Lazy!
   TH1D &HCMSRAA = (C == 0 ? HR04C00RAA : (C == 1 ? HR04C01RAA : (C == 2 ? HR04C02RAA : HR04C03RAA)));
   TH1D &HCMSRAASys = (C == 0 ? HR04C00RAASys : (C == 1 ? HR04C01RAASys : (C == 2 ? HR04C02RAASys : HR04C03RAASys)));

   TGraphAsymmErrors ATLASC01;   GetATLAS(ATLASC01, ATLASFile, C01, false);
   TGraphAsymmErrors ATLASC12;   GetATLAS(ATLASC12, ATLASFile, C12, false);
   TGraphAsymmErrors ATLASC23;   GetATLAS(ATLASC23, ATLASFile, C23, false);
   TGraphAsymmErrors ATLASC34;   GetATLAS(ATLASC34, ATLASFile, C34, false);
   TGraphAsymmErrors ATLASC45;   GetATLAS(ATLASC45, ATLASFile, C45, false);
   TGraphAsymmErrors ATLASC56;   GetATLAS(ATLASC56, ATLASFile, C56, false);
   TGraphAsymmErrors ATLASC67;   GetATLAS(ATLASC67, ATLASFile, C67, false);
   TGraphAsymmErrors ATLASC78;   GetATLAS(ATLASC78, ATLASFile, C78, false);

   TGraphAsymmErrors ATLASC01Sys;   GetATLAS(ATLASC01Sys, ATLASFile, C01, true);
   TGraphAsymmErrors ATLASC12Sys;   GetATLAS(ATLASC12Sys, ATLASFile, C12, true);
   TGraphAsymmErrors ATLASC23Sys;   GetATLAS(ATLASC23Sys, ATLASFile, C23, true);
   TGraphAsymmErrors ATLASC34Sys;   GetATLAS(ATLASC34Sys, ATLASFile, C34, true);
   TGraphAsymmErrors ATLASC45Sys;   GetATLAS(ATLASC45Sys, ATLASFile, C45, true);
   TGraphAsymmErrors ATLASC56Sys;   GetATLAS(ATLASC56Sys, ATLASFile, C56, true);
   TGraphAsymmErrors ATLASC67Sys;   GetATLAS(ATLASC67Sys, ATLASFile, C67, true);
   TGraphAsymmErrors ATLASC78Sys;   GetATLAS(ATLASC78Sys, ATLASFile, C78, true);

   TH1D HLumi("HLumi", "", 1, 0, 1);
   HLumi.SetFillColor(Color[4]);
   TLegend Legend1(0.07, 0.08, 0.27, 0.29);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.04);
   Legend1.SetFillStyle(0);
   Legend1.SetBorderSize(0);
   Legend1.AddEntry(&HCMSRAASys, CsCMS[C].c_str(), "eplf");
   Legend1.AddEntry(&HCMSRAA, "T_{AA}", "f");
   Legend1.AddEntry(&HLumi, "Lumi", "f");

   TLegend Legend2(0.30, 0.08, 0.50, 0.29);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.04);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   if(C == C0)
   {
      Legend2.AddEntry("", "", "");
      Legend2.AddEntry("", "", "");
      Legend2.AddEntry(&ATLASC01Sys, CsATLAS[0].c_str(), "epfl");
   }
   if(C == C1)
   {
      Legend2.AddEntry("", "", "");
      Legend2.AddEntry(&ATLASC12Sys, CsATLAS[1].c_str(), "epfl");
      Legend2.AddEntry(&ATLASC23Sys, CsATLAS[2].c_str(), "epfl");
   }
   if(C == C2)
   {
      Legend2.AddEntry("", "", "");
      Legend2.AddEntry(&ATLASC34Sys, CsATLAS[3].c_str(), "epfl");
      Legend2.AddEntry(&ATLASC45Sys, CsATLAS[4].c_str(), "epfl");
   }
   if(C == C3)
   {
      Legend2.AddEntry(&ATLASC56Sys, CsATLAS[5].c_str(), "epfl");
      Legend2.AddEntry(&ATLASC67Sys, CsATLAS[6].c_str(), "epfl");
      Legend2.AddEntry(&ATLASC78Sys, CsATLAS[7].c_str(), "epfl");
   }
   
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.04);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld.Draw("axis");
   DrawLumiTAA(Lumi, TAA, XMin, XMax);
   if(C == C0)
   {
      ATLASC01Sys.Draw("5");
      ATLASC01.Draw("p");
   }
   if(C == C1)
   {
      ATLASC12Sys.Draw("5");
      ATLASC23Sys.Draw("5");
      ATLASC12.Draw("p");
      ATLASC23.Draw("p");
   }
   if(C == C2)
   {
      ATLASC34Sys.Draw("5");
      ATLASC45Sys.Draw("5");
      ATLASC34.Draw("p");
      ATLASC45.Draw("p");
   }
   if(C == C3)
   {
      ATLASC56Sys.Draw("5");
      ATLASC67Sys.Draw("5");
      ATLASC78Sys.Draw("5");
      ATLASC56.Draw("p");
      ATLASC67.Draw("p");
      ATLASC78.Draw("p");
   }
   HCMSRAASys.Draw("same e2");
   HCMSRAA.Draw("same");
   GLine.Draw("l");
   Legend1.Draw();
   Legend2.Draw();
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.24, "anti-k_{T} R = 0.4");
   Latex.DrawLatex(0.92, 0.17, "|#eta_{jet}| < 2.0");
   Latex.DrawLatex(0.92, 0.10, "|#eta_{jet}^{ATLAS}| < 2.8");
   
   string OutputBase = "PlotRAAOverlay" + Cs[C];

   Canvas.SaveAs((OutputBase + ".pdf").c_str());
   Canvas.SaveAs((OutputBase + ".png").c_str());
   Canvas.SaveAs((OutputBase + ".C").c_str());

   return 0;
}

void SetPad(TPad &P)
{
   P.SetLogx();
   P.SetLeftMargin(0);
   P.SetTopMargin(0);
   P.SetRightMargin(0);
   P.SetBottomMargin(0);
   P.SetTickx();
   P.SetTicky();
   P.Draw();
}

void SetAxis(TGaxis &A)
{
   A.SetLabelFont(42);
   A.SetLabelSize(0.030);
   A.SetMaxDigits(6);
   A.SetMoreLogLabels();
   A.SetNoExponent();
   A.Draw();
}

void GetRAA(TH1D &H, string FileName, int R, int C, bool Sys)
{
   TFile File(FileName.c_str());

   string Rs[] = {"2", "3", "4", "6", "8", "10"};
   string Cs[] = {"0to10", "10to30", "30to50", "50to90"};

   string HistogramName = "";
   
   HistogramName = HistogramName + "akCs" + Rs[R] + "PU3PFFlowJetAnalyzer";
   HistogramName = HistogramName + "_Cent" + Cs[C];
   if(Sys == false)   HistogramName = HistogramName + "_1";
   else               HistogramName = HistogramName + "_2";

   TH1D *Histogram = (TH1D *)File.Get(HistogramName.c_str());
   Rebin(*Histogram, H);

   int Style[] = {20, 20, 20, 20};

   if(Color[C] == -1)
   {
      Color[0] = TColor::GetFreeColorIndex();
      new TColor(Color[0], 0.9648, 0.2969, 0.2344);   // E74C3C
      Color[1] = TColor::GetFreeColorIndex();
      new TColor(Color[1], 0.2031, 0.5938, 0.8555);   // 3498DB
      Color[2] = TColor::GetFreeColorIndex();
      new TColor(Color[2], 0.9414, 0.7656, 0.0586);   // F1C40F
      Color[3] = TColor::GetFreeColorIndex();
      new TColor(Color[3], 0.1797, 0.7969, 0.4414);   // 2ECC71
      Color[4] = TColor::GetFreeColorIndex();
      new TColor(Color[4], 0.5, 0.5, 0.5);
   }

   H.SetMarkerStyle(Style[C]);
   H.SetMarkerColor(Color[C]);
   H.SetLineColor(Color[C]);
   H.SetFillColor(Color[C]);
   if(Sys == true)
      H.SetFillColorAlpha(Color[C], 0.25);
   H.SetMarkerSize(1.8);
   H.SetLineWidth(2.0);

   File.Close();
}

void GetATLAS(TGraphAsymmErrors &G, string FileName, int C, bool Sys)
{
   string Cs[] = {"0-10", "10-20", "20-30", "30-40", "40-50", "50-60", "60-70", "70-80"};

   int ATLASColors[] = {kBlack, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kRed};

   G.SetLineColor(ATLASColors[C]);
   G.SetMarkerColor(ATLASColors[C]);
   G.SetFillStyle(0);

   TFile File(FileName.c_str());

   if(Sys == false)
   {
      TGraphAsymmErrors *Graph = (TGraphAsymmErrors *)File.Get(Form("ATLAS_Cent%s_Stat", Cs[C].c_str()));
      for(int i = 0; i < Graph->GetN(); i++)
      {
         double X, Y, EXL, EXH, EYL, EYH;
         Graph->GetPoint(i, X, Y);
         EXL = Graph->GetErrorXlow(i);
         EYL = Graph->GetErrorYlow(i);
         EXH = Graph->GetErrorXhigh(i);
         EYH = Graph->GetErrorYhigh(i);
         G.SetPoint(i, X, Y);
         G.SetPointError(i, EXL, EXH, EYL, EYH);
      }
   }
   else
   {
      TGraphAsymmErrors *Graph1 = (TGraphAsymmErrors *)File.Get(Form("ATLAS_Cent%s_Sys", Cs[C].c_str()));
      TGraphAsymmErrors *Graph2 = (TGraphAsymmErrors *)File.Get(Form("ATLAS_Cent%s_Lumi", Cs[C].c_str()));
      TGraphAsymmErrors *Graph3 = (TGraphAsymmErrors *)File.Get(Form("ATLAS_Cent%s_TAA", Cs[C].c_str()));
      for(int i = 0; i < Graph1->GetN(); i++)
      {
         double X, Y, EXL, EXH, EYL1, EYH1, EYL2, EYH2, EYL3, EYH3;
         Graph1->GetPoint(i, X, Y);
         EXL = Graph1->GetErrorXlow(i);
         EXH = Graph1->GetErrorXhigh(i);
         EYL1 = Graph1->GetErrorYlow(i);
         EYH1 = Graph1->GetErrorYhigh(i);
         EYL2 = Graph2->GetErrorYlow(i);
         EYH2 = Graph2->GetErrorYhigh(i);
         EYL3 = Graph3->GetErrorYlow(i);
         EYH3 = Graph3->GetErrorYhigh(i);
         double EYL = sqrt(EYL1 * EYL1 + EYL2 * EYL2 + EYL3 * EYL3);
         double EYH = sqrt(EYH1 * EYH1 + EYH2 * EYH2 + EYH3 * EYH3);
         G.SetPoint(i, X, Y);
         G.SetPointError(i, EXL, EXH, EYL, EYH);
      }
   }

   File.Close();
}

void Rebin(TH1D &H1, TH1D &H2)
{
   H2.Reset();

   for(int i = 1; i <= H1.GetNbinsX(); i++)
   {
      double V = H1.GetBinContent(i);
      double E = H1.GetBinError(i);

      int B = H2.FindBin(H1.GetBinCenter(i));

      V = V + H2.GetBinContent(B);
      E = sqrt(E * E + H2.GetBinError(B) * H2.GetBinError(B));

      H2.SetBinContent(B, V);
      H2.SetBinError(B, E);
   }
}

void DrawLumiTAA(double Lumi, double TAA[4], double XMin, double XMax)
{
   double Offset = 0.06;
   double Size = 0.08;
   double Grid = 0.10;

   TBox Box;

   double X1, X2;
   double x1, x2;

   Box.SetFillColor(Color[4]);
   x1 = Offset - Size * 0.5 + Grid * 0;
   x2 = Offset + Size * 0.5 + Grid * 0;
   X1 = exp(x1 * (log(XMax) - log(XMin)) + log(XMin));
   X2 = exp(x2 * (log(XMax) - log(XMin)) + log(XMin));
   Box.DrawBox(X1, 1 - Lumi, X2, 1 + Lumi);

   for(int i = 0; i < 4; i++)
   {
      if(TAA[i] < 0)
         continue;

      Box.SetFillColor(Color[i]);
      x1 = Offset - Size * 0.5 + Grid * (i + 1);
      x2 = Offset + Size * 0.5 + Grid * (i + 1);
      X1 = exp(x1 * (log(XMax) - log(XMin)) + log(XMin));
      X2 = exp(x2 * (log(XMax) - log(XMin)) + log(XMin));
      Box.DrawBox(X1, 1 - TAA[i], X2, 1 + TAA[i]);
   }
}


