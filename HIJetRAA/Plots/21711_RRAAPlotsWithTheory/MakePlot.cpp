#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "TH1D.h"
#include "TGraphAsymmErrors.h"
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

#include "CommandLine.h"

#define PT0 0
#define PT1 1
#define PT2 2
#define PT3 3
#define PT4 4

#define C0 0
#define C1 1
#define C2 2
#define C3 3

int Color[5] = {-1, -1, -1, -1, -1};

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
void GetRRAA(TGraphAsymmErrors &H, string FileName, int R, int C, bool Sys = false);
vector<TGraphAsymmErrors> GetTheory(string TheoryFileName, int BaseColor);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   bool DoTheory = CL.GetBool("DoTheory", false);

   // Preamble: sizing
   int PanelSize = 500;
   int PaddingWidth = 100;
   int PaddingHeight = 100;
   int CanvasWidth = PanelSize * 3 + PaddingWidth * 2;
   int CanvasHeight = PanelSize * 2 + PaddingHeight * 2;

   double PadX0 = (double)PaddingWidth / CanvasWidth;
   double PadY0 = (double)PaddingHeight / CanvasHeight;
   double PadDX = (double)PanelSize / CanvasWidth;
   double PadDY = (double)PanelSize / CanvasHeight;

   double XMin = 0.15;
   double XMax = 1.10;
   // double YMin = 0.501;
   // double YMax = 1.5;
   double YMin = 0.701;
   double YMax = 1.999;

   string File = "RRAA_Smooth_RedStat.root";

   // double Lumi = 0.023;
   // double TAA[4] = {0.100719, 0.051233, 0.025341, 0.018646};

   // Start declaring canvas, pad, axis, and axis title (as TLatex)
   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetNdivisions(505);
   HWorld.GetYaxis()->SetNdivisions(505);

   TPad P1("P1", "", PadX0 + PadDX * 0, PadY0 + PadDY * 1, PadX0 + PadDX * 1, PadY0 + PadDY * 2, 0);
   TPad P2("P2", "", PadX0 + PadDX * 1, PadY0 + PadDY * 1, PadX0 + PadDX * 2, PadY0 + PadDY * 2, 0);
   TPad P3("P3", "", PadX0 + PadDX * 2, PadY0 + PadDY * 1, PadX0 + PadDX * 3, PadY0 + PadDY * 2, 0);
   TPad P4("P4", "", PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 1, 0);
   TPad P5("P5", "", PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 1, 0);
   TPad P6("P6", "", PadX0 + PadDX * 2, PadY0 + PadDY * 0, PadX0 + PadDX * 3, PadY0 + PadDY * 1, 0);
   
   SetPad(P1);
   SetPad(P2);
   SetPad(P3);
   SetPad(P4);
   SetPad(P5);
   SetPad(P6);
  
   Canvas.cd();

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 505, "");
   TGaxis AxisX2(PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 0, XMin, XMax, 505, "");
   TGaxis AxisX3(PadX0 + PadDX * 2, PadY0 + PadDY * 0, PadX0 + PadDX * 3, PadY0 + PadDY * 0, XMin, XMax, 505, "");
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin, YMax, 505, "");
   TGaxis AxisY2(PadX0 + PadDX * 0, PadY0 + PadDY * 1, PadX0 + PadDX * 0, PadY0 + PadDY * 2, YMin, YMax, 505, "");

   SetAxis(AxisX1);
   SetAxis(AxisX2);
   SetAxis(AxisX3);
   SetAxis(AxisY1);
   SetAxis(AxisY2);

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 1.5, PadY0 * 0.20, "Jet R");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.20, PadY0 + PadDY, "R_{AA}^{R} / R_{AA}^{R = 0.2}");

   Latex.SetTextFont(62);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * 2 + PadY0 * 0.15, "CMS");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 3, PadY0 + PadDY * 2 + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 404 #mub^{-1}, pp 27.4 pb^{-1}");

   TGraph GLine;
   GLine.SetPoint(0, XMin, 1);
   GLine.SetPoint(1, XMax, 1);
   GLine.SetLineStyle(kDashed);

   TGraphAsymmErrors HP0C0RRAA;   GetRRAA(HP0C0RRAA, File, PT0, C0, false);
   TGraphAsymmErrors HP0C1RRAA;   GetRRAA(HP0C1RRAA, File, PT0, C1, false);
   TGraphAsymmErrors HP0C2RRAA;   GetRRAA(HP0C2RRAA, File, PT0, C2, false);
   TGraphAsymmErrors HP0C3RRAA;   GetRRAA(HP0C3RRAA, File, PT0, C3, false);
   TGraphAsymmErrors HP1C0RRAA;   GetRRAA(HP1C0RRAA, File, PT1, C0, false);
   TGraphAsymmErrors HP1C1RRAA;   GetRRAA(HP1C1RRAA, File, PT1, C1, false);
   TGraphAsymmErrors HP1C2RRAA;   GetRRAA(HP1C2RRAA, File, PT1, C2, false);
   TGraphAsymmErrors HP1C3RRAA;   GetRRAA(HP1C3RRAA, File, PT1, C3, false);
   TGraphAsymmErrors HP2C0RRAA;   GetRRAA(HP2C0RRAA, File, PT2, C0, false);
   TGraphAsymmErrors HP2C1RRAA;   GetRRAA(HP2C1RRAA, File, PT2, C1, false);
   TGraphAsymmErrors HP2C2RRAA;   GetRRAA(HP2C2RRAA, File, PT2, C2, false);
   TGraphAsymmErrors HP2C3RRAA;   GetRRAA(HP2C3RRAA, File, PT2, C3, false);
   TGraphAsymmErrors HP3C0RRAA;   GetRRAA(HP3C0RRAA, File, PT3, C0, false);
   TGraphAsymmErrors HP3C1RRAA;   GetRRAA(HP3C1RRAA, File, PT3, C1, false);
   TGraphAsymmErrors HP3C2RRAA;   GetRRAA(HP3C2RRAA, File, PT3, C2, false);
   TGraphAsymmErrors HP3C3RRAA;   GetRRAA(HP3C3RRAA, File, PT3, C3, false);
   TGraphAsymmErrors HP4C0RRAA;   GetRRAA(HP4C0RRAA, File, PT4, C0, false);
   TGraphAsymmErrors HP4C1RRAA;   GetRRAA(HP4C1RRAA, File, PT4, C1, false);
   TGraphAsymmErrors HP4C2RRAA;   GetRRAA(HP4C2RRAA, File, PT4, C2, false);
   TGraphAsymmErrors HP4C3RRAA;   GetRRAA(HP4C3RRAA, File, PT4, C3, false);
   
   TGraphAsymmErrors HP0C0RRAASys;   GetRRAA(HP0C0RRAASys, File, PT0, C0, true);
   TGraphAsymmErrors HP0C1RRAASys;   GetRRAA(HP0C1RRAASys, File, PT0, C1, true);
   TGraphAsymmErrors HP0C2RRAASys;   GetRRAA(HP0C2RRAASys, File, PT0, C2, true);
   TGraphAsymmErrors HP0C3RRAASys;   GetRRAA(HP0C3RRAASys, File, PT0, C3, true);
   TGraphAsymmErrors HP1C0RRAASys;   GetRRAA(HP1C0RRAASys, File, PT1, C0, true);
   TGraphAsymmErrors HP1C1RRAASys;   GetRRAA(HP1C1RRAASys, File, PT1, C1, true);
   TGraphAsymmErrors HP1C2RRAASys;   GetRRAA(HP1C2RRAASys, File, PT1, C2, true);
   TGraphAsymmErrors HP1C3RRAASys;   GetRRAA(HP1C3RRAASys, File, PT1, C3, true);
   TGraphAsymmErrors HP2C0RRAASys;   GetRRAA(HP2C0RRAASys, File, PT2, C0, true);
   TGraphAsymmErrors HP2C1RRAASys;   GetRRAA(HP2C1RRAASys, File, PT2, C1, true);
   TGraphAsymmErrors HP2C2RRAASys;   GetRRAA(HP2C2RRAASys, File, PT2, C2, true);
   TGraphAsymmErrors HP2C3RRAASys;   GetRRAA(HP2C3RRAASys, File, PT2, C3, true);
   TGraphAsymmErrors HP3C0RRAASys;   GetRRAA(HP3C0RRAASys, File, PT3, C0, true);
   TGraphAsymmErrors HP3C1RRAASys;   GetRRAA(HP3C1RRAASys, File, PT3, C1, true);
   TGraphAsymmErrors HP3C2RRAASys;   GetRRAA(HP3C2RRAASys, File, PT3, C2, true);
   TGraphAsymmErrors HP3C3RRAASys;   GetRRAA(HP3C3RRAASys, File, PT3, C3, true);
   TGraphAsymmErrors HP4C0RRAASys;   GetRRAA(HP4C0RRAASys, File, PT4, C0, true);
   TGraphAsymmErrors HP4C1RRAASys;   GetRRAA(HP4C1RRAASys, File, PT4, C1, true);
   TGraphAsymmErrors HP4C2RRAASys;   GetRRAA(HP4C2RRAASys, File, PT4, C2, true);
   TGraphAsymmErrors HP4C3RRAASys;   GetRRAA(HP4C3RRAASys, File, PT4, C3, true);

   vector<TGraphAsymmErrors> Felix = GetTheory("Theory/Felix/FelixRRAA.txt", kBlack);
   vector<TGraphAsymmErrors> Daniel = GetTheory("Theory/Daniel/ForCMS/r_RAA/Daniel_wake.txt", kMagenta);
   vector<TGraphAsymmErrors> Korinna = GetTheory("Theory/Korinna/JewelDataRRAA_0to10.txt", kCyan + 3);
  
   TLegend Legend1(0.1, 0.08, 0.5, 0.48);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.07);
   Legend1.SetFillStyle(0);
   Legend1.SetBorderSize(0);
   Legend1.AddEntry(&HP0C0RRAASys, "0-10%", "plf");
   Legend1.AddEntry(&HP0C1RRAASys, "10-30%", "plf");
   Legend1.AddEntry(&HP0C2RRAASys, "30-50%", "plf");
   Legend1.AddEntry(&HP0C3RRAASys, "50-90%", "plf");

   TLegend Legend2(0.5, 0.08, 0.9, 0.48);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.07);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry(&Felix[0], "Factorization", "lf");
   Legend2.AddEntry(&Daniel[0], "Hybrid", "lf");
   Legend2.AddEntry(&Korinna[0], "Jewel", "lf");
   Legend2.AddEntry("", "", "");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.07);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld.Draw("axis");
   if(DoTheory == true)    Felix[0].Draw("3");
   if(DoTheory == true)    Daniel[0].Draw("3");
   if(DoTheory == true)    Korinna[0].Draw("3");
   if(DoTheory == true)    Felix[0].Draw("lX");
   if(DoTheory == true)    Daniel[0].Draw("lX");
   if(DoTheory == true)    Korinna[0].Draw("lX");
   HP0C0RRAASys.Draw("2");
   HP0C1RRAASys.Draw("2");
   HP0C2RRAASys.Draw("2");
   HP0C3RRAASys.Draw("2");
   HP0C0RRAA.Draw("p");
   HP0C1RRAA.Draw("p");
   HP0C2RRAA.Draw("p");
   HP0C3RRAA.Draw("p");
   GLine.Draw("l");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.9, "200 < p_{T} < 250 GeV");
   P2.cd();
   HWorld.Draw("axis");
   if(DoTheory == true)    Felix[1].Draw("3");
   if(DoTheory == true)    Daniel[1].Draw("3");
   if(DoTheory == true)    Korinna[1].Draw("3");
   if(DoTheory == true)    Felix[1].Draw("lX");
   if(DoTheory == true)    Daniel[1].Draw("lX");
   if(DoTheory == true)    Korinna[1].Draw("lX");
   HP1C0RRAASys.Draw("2");
   HP1C1RRAASys.Draw("2");
   HP1C2RRAASys.Draw("2");
   HP1C3RRAASys.Draw("2");
   HP1C0RRAA.Draw("p");
   HP1C1RRAA.Draw("p");
   HP1C2RRAA.Draw("p");
   HP1C3RRAA.Draw("p");
   GLine.Draw("l");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.9, "250 < p_{T} < 300 GeV");
   P3.cd();
   HWorld.Draw("axis");
   if(DoTheory == true)    Felix[2].Draw("3");
   if(DoTheory == true)    Daniel[2].Draw("3");
   if(DoTheory == true)    Korinna[2].Draw("3");
   if(DoTheory == true)    Felix[2].Draw("lX");
   if(DoTheory == true)    Daniel[2].Draw("lX");
   if(DoTheory == true)    Korinna[2].Draw("lX");
   HP2C0RRAASys.Draw("2");
   HP2C1RRAASys.Draw("2");
   HP2C2RRAASys.Draw("2");
   HP2C3RRAASys.Draw("2");
   HP2C0RRAA.Draw("p");
   HP2C1RRAA.Draw("p");
   HP2C2RRAA.Draw("p");
   HP2C3RRAA.Draw("p");
   GLine.Draw("l");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.9, "300 < p_{T} < 400 GeV");
   P4.cd();
   HWorld.Draw("axis");
   if(DoTheory == true)    Felix[3].Draw("3");
   if(DoTheory == true)    Daniel[3].Draw("3");
   if(DoTheory == true)    Korinna[3].Draw("3");
   if(DoTheory == true)    Felix[3].Draw("lX");
   if(DoTheory == true)    Daniel[3].Draw("lX");
   if(DoTheory == true)    Korinna[3].Draw("lX");
   HP3C0RRAASys.Draw("2");
   HP3C1RRAASys.Draw("2");
   HP3C2RRAASys.Draw("2");
   HP3C3RRAASys.Draw("2");
   HP3C0RRAA.Draw("p");
   HP3C1RRAA.Draw("p");
   HP3C2RRAA.Draw("p");
   HP3C3RRAA.Draw("p");
   GLine.Draw("l");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.9, "400 < p_{T} < 500 GeV");
   P5.cd();
   HWorld.Draw("axis");
   if(DoTheory == true)    Felix[4].Draw("3");
   if(DoTheory == true)    Daniel[4].Draw("3");
   if(DoTheory == true)    Korinna[4].Draw("3");
   if(DoTheory == true)    Felix[4].Draw("lX");
   if(DoTheory == true)    Daniel[4].Draw("lX");
   if(DoTheory == true)    Korinna[4].Draw("lX");
   HP4C0RRAASys.Draw("2");
   HP4C1RRAASys.Draw("2");
   HP4C2RRAASys.Draw("2");
   HP4C3RRAASys.Draw("2");
   HP4C0RRAA.Draw("p");
   HP4C1RRAA.Draw("p");
   HP4C2RRAA.Draw("p");
   HP4C3RRAA.Draw("p");
   GLine.Draw("l");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.9, "500 < p_{T} < 1000 GeV");
   P6.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.9, "anti-k_{T}, |#eta_{jet}| < 2");
   Legend1.Draw();
   if(DoTheory == true)   Legend2.Draw();

   string OutputBase = "PlotRRAA";
   if(DoTheory == true)
      OutputBase = "PlotRRAATheory";

   Canvas.SaveAs((OutputBase + ".pdf").c_str());
   Canvas.SaveAs((OutputBase + ".png").c_str());
   Canvas.SaveAs((OutputBase + ".C").c_str());

   return 0;
}

void SetPad(TPad &P)
{
   // P.SetLogx();
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

void GetRRAA(TGraphAsymmErrors &H, string FileName, int P, int C, bool Sys)
{
   TFile File(FileName.c_str());

   string Ps[] = {"200p0to250p0", "250p0to300p0", "300p0to400p0", "400p0to500p0", "500p0to1000p0"};
   string Cs[] = {"0to10", "10to30", "30to50", "50to90"};

   string HistogramName = "";
   
   HistogramName = HistogramName + "Cent" + Cs[C];
   HistogramName = HistogramName + "_" + Ps[P];
   if(Sys == false)   HistogramName = HistogramName + "_1";
   else               HistogramName = HistogramName + "_2";

   if(Sys == false)
   {
      TGraphAsymmErrors *G = (TGraphAsymmErrors *)File.Get(HistogramName.c_str());
      
      for(int i = 0; i < G->GetN(); i++)
      {
         double X, Y, EX1, EX2, EY1, EY2;
         G->GetPoint(i, X, Y);
         EX1 = G->GetErrorXlow(i);
         EX2 = G->GetErrorXhigh(i);
         EY1 = G->GetErrorYlow(i);
         EY2 = G->GetErrorYhigh(i);
         H.SetPoint(i, X, Y);
         H.SetPointEXlow(i, EX1);
         H.SetPointEXhigh(i, EX2);
         H.SetPointEYlow(i, EY1);
         H.SetPointEYhigh(i, EY2);
      }
   }
   else
   {
      TH1D *Histogram = (TH1D *)File.Get(HistogramName.c_str());

      for(int i = 1; i <= Histogram->GetNbinsX(); i++)
      {
         double X = Histogram->GetBinCenter(i);
         double DX = Histogram->GetXaxis()->GetBinUpEdge(i) - X;
         double Y = Histogram->GetBinContent(i);
         double DY = Histogram->GetBinError(i);
         H.SetPoint(i, X, Y);
         H.SetPointEXlow(i, DX * 0.8);
         H.SetPointEXhigh(i, DX * 0.8);
         H.SetPointEYlow(i, DY);
         H.SetPointEYhigh(i, DY);
      }
   }

   int Style[] = {20, 21, 22, 29};
   double Size[] = {1.8, 1.8, 1.8, 2.4};

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
   H.SetMarkerSize(Size[C]);
   H.SetLineWidth(2.0);

   File.Close();
}

vector<TGraphAsymmErrors> GetTheory(string TheoryFileName, int BaseColor)
{
   vector<TGraphAsymmErrors> Result(5);

   for(int i = 0; i < 5; i++)
   {
      Result[i].SetLineColor(BaseColor);
      Result[i].SetFillColorAlpha(BaseColor, 0.25);
      Result[i].SetMarkerColor(BaseColor);
      Result[i].SetMarkerStyle(20);
   }

   ifstream in(TheoryFileName);

   double JetR[] = {0.2, 0.3, 0.4, 0.6, 0.8, 1.0};
   double DR = 0.04;

   while(in)
   {
      char ch[10240];
      ch[0] = '\0';
      in.getline(ch, 10239, '\n');

      stringstream str(ch);

      double PTMin = 0, PTMax = 0;
      str >> PTMin >> PTMax;

      double PTAve = (PTMin + PTMax) / 2;

      int Index = -1;
      if(PTAve < 250 && PTAve > 200)    Index = 0;
      if(PTAve < 300 && PTAve > 250)    Index = 1;
      if(PTAve < 400 && PTAve > 300)    Index = 2;
      if(PTAve < 500 && PTAve > 400)    Index = 3;
      if(PTAve < 1000 && PTAve > 500)   Index = 4;

      if(Index < 0)
         continue;

      for(int i = 0; i < 6; i++)
      {
         double R, RMax, RMin;
         str >> R >> RMax >> RMin;

         Result[Index].SetPoint(i, JetR[i], R);
         Result[Index].SetPointError(i, DR, DR, R - RMin, RMax - R);
      }
   }

   return Result;
}



