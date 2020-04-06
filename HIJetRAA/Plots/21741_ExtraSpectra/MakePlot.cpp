#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"

#include "SetStyle.h"
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
#define PP 4

int Color[6] = {-1, -1, -1, -1, -1, -1};

int main(int argc, char *argv[]);
void SetPad(TPad &P, bool Ratio = false);
void SetAxis(TGaxis &A, bool X);
void GetGraph(string FileName, TGraphAsymmErrors &G, int R, int Cent, double Shift, bool Sys);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName = CL.Get("Input", "Spectra_Smooth.root");
   int R = CL.GetInt("R", 2);

   // Preamble: sizing
   int PanelSizeX = 400;
   int PanelSizeY = 500;
   int PaddingWidthL = 100;
   int PaddingWidthR = 25;
   int PaddingHeight = 50;
   int CanvasWidth = PanelSizeX * 1 + PaddingWidthL + PaddingWidthR;
   int CanvasHeight = PanelSizeY * 1 + PaddingHeight * 2;
   double TickLength = 10;

   double PadX0 = (double)PaddingWidthL / CanvasWidth;
   double PadY0 = (double)PaddingHeight / CanvasHeight;
   double PadDX = (double)PanelSizeX / CanvasWidth;
   double PadDY = (double)PanelSizeY / CanvasHeight;

   double XMin = 200 / 1.2;
   double XMax = 1000 * 1.2;
   double YMin = 3e-6;
   double YMax = 1e4;
   double RMin = 0.60;
   double RMax = 1.39;

   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.GetXaxis()->SetTickLength(TickLength / PanelSizeY);
   HWorld.GetYaxis()->SetTickLength(TickLength / PanelSizeX);

   TPad P1("P1", "", PadX0 + PadDX * 0, PadY0, PadX0 + PadDX * 1, PadY0 + PadDY, 0);

   SetPad(P1, false);

   Canvas.cd();

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 510, "GS");
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin, YMax, 510, "GS");

   SetAxis(AxisX1, true);
   SetAxis(AxisY1, false);

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 0.5, PadY0 * 0.30, "p_{T}^{jet} (GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.30, PadY0 + PadDY * 0.5, "#frac{1}{<T_{AA}>} #frac{1}{N_{evt}} #frac{d^{2}N_{jet}}{dp_{T}d#eta} or #frac{d^{2}#sigma_{jet}}{dp_{T}d#eta} (nb/GeV)");

   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * 1 + PadY0 * 0.15, "CMS #scale[0.8]{#font[52]{Preliminary}}");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.025);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 1, PadY0 + PadDY * 1 + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 404 #mub^{-1}, pp 27.4 pb^{-1}");

   TGraphAsymmErrors GPPRXX, GPPRXXSys;
   TGraphAsymmErrors GPbPbC0RXX, GPbPbC0RXXSys;
   TGraphAsymmErrors GPbPbC1RXX, GPbPbC1RXXSys;
   TGraphAsymmErrors GPbPbC2RXX, GPbPbC2RXXSys;
   TGraphAsymmErrors GPbPbC3RXX, GPbPbC3RXXSys;

   TLegend Legend(0.45, 0.65, 0.75, 0.95);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.05);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&GPbPbC0RXXSys, "PbPb 0-10% #times10^{4}",  "plf");
   Legend.AddEntry(&GPbPbC1RXXSys, "PbPb 10-30% #times10^{3}", "plf");
   Legend.AddEntry(&GPbPbC2RXXSys, "PbPb 30-50% #times10^{2}", "plf");
   Legend.AddEntry(&GPbPbC3RXXSys, "PbPb 50-90% #times10^{1}", "plf");
   Legend.AddEntry(&GPPRXXSys,     "pp #times10^{0}",          "plf");

   int RXX;
   if(R == 2)    RXX = R02;
   if(R == 3)    RXX = R03;
   if(R == 4)    RXX = R04;
   if(R == 6)    RXX = R06;
   if(R == 8)    RXX = R08;
   if(R == 10)   RXX = R10;

   GetGraph(FileName, GPPRXX, RXX, PP, 1, false);          GetGraph(FileName, GPPRXXSys, RXX, PP, 1, true);
   GetGraph(FileName, GPbPbC0RXX, RXX, C0, 1e+3, false);   GetGraph(FileName, GPbPbC0RXXSys, RXX, C0, 1e+3, true);
   GetGraph(FileName, GPbPbC1RXX, RXX, C1, 1e+1, false);   GetGraph(FileName, GPbPbC1RXXSys, RXX, C1, 1e+1, true);
   GetGraph(FileName, GPbPbC2RXX, RXX, C2, 1e-1, false);   GetGraph(FileName, GPbPbC2RXXSys, RXX, C2, 1e-1, true);
   GetGraph(FileName, GPbPbC3RXX, RXX, C3, 1e-3, false);   GetGraph(FileName, GPbPbC3RXXSys, RXX, C3, 1e-3, true);

   TGraph Line;
   Line.SetPoint(0, 0, 1);
   Line.SetPoint(1, 10000, 1);

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.05);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld.Draw("axis");
   GPPRXXSys.Draw("2");
   GPbPbC0RXXSys.Draw("2");
   GPbPbC1RXXSys.Draw("2");
   GPbPbC2RXXSys.Draw("2");
   GPbPbC3RXXSys.Draw("2");
   GPPRXX.Draw("p");
   GPbPbC0RXX.Draw("p");
   GPbPbC1RXX.Draw("p");
   GPbPbC2RXX.Draw("p");
   GPbPbC3RXX.Draw("p");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.12, Form("anti-k_{T} R = %.1f", R * 0.1));
   Latex.DrawLatex(0.08, 0.06, "|#eta_{jet}| < 2.0");
   Legend.Draw();

   string OutputBase = Form("SpectraSinglePanelR%02d", R);

   Canvas.SaveAs((OutputBase + ".pdf").c_str());
   Canvas.SaveAs((OutputBase + ".png").c_str());
   Canvas.SaveAs((OutputBase + ".C").c_str());

   return 0;
}

void SetPad(TPad &P, bool Ratio)
{
   P.SetLogx();
   if(Ratio == false)
      P.SetLogy();
   P.SetLogz();
   P.SetLeftMargin(0);
   P.SetTopMargin(0);
   P.SetRightMargin(0);
   P.SetBottomMargin(0);
   P.SetTickx();
   P.SetTicky();
   P.Draw();
}

void SetAxis(TGaxis &A, bool X)
{
   A.SetLabelFont(42);
   A.SetLabelSize(0.040);
   A.SetMaxDigits(6);
   if(X == true)
      A.SetMoreLogLabels();
   if(X == true)
      A.SetNoExponent();
   A.SetTickSize(0);
   A.SetTickLength(0);
   if(X == true)
      A.SetLabelOffset(-0.005);
   A.Draw();
}

void GetGraph(string FileName, TGraphAsymmErrors &G, int R, int C, double Shift, bool Sys)
{
   if(Color[C] == -1)
   {
      Color[0] = TColor::GetColor("#E74C3C");
      Color[1] = TColor::GetColor("#3498DB");
      Color[2] = TColor::GetColor("#F1C40F");
      Color[3] = TColor::GetColor("#2ECC71");
      Color[4] = TColor::GetColor("#7F7F7F");
      Color[5] = TColor::GetColor("#8E44AD");
   }

   TFile File(FileName.c_str());

   string Rs[] = {"2", "3", "4", "6", "8", "10"};
   string Cs[] = {"Cent0to10", "Cent10to30", "Cent30to50", "Cent50to90"};

   string HistName = "";
   if(C != PP)
      HistName = "akCs" + Rs[R] + "PU3PFFlowJetAnalyzer_" + Cs[C];
   else
      HistName = "ak" + Rs[R] + "PFJetAnalyzer_" + Cs[0];
   
   if(Sys == false)
      HistName = HistName + "_1";
   else
      HistName = HistName + "_2";

   TH1D *H = (TH1D *)File.Get(HistName.c_str());
   if(H == nullptr)
      cout << HistName << endl;

   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      double X = H->GetXaxis()->GetBinCenter(i);
      double Y = H->GetBinContent(i);
      double EX = (H->GetXaxis()->GetBinUpEdge(i) - H->GetXaxis()->GetBinLowEdge(i)) / 2;
      double EY = H->GetBinError(i);

      G.SetPoint(i - 1, X, Y * Shift);
      G.SetPointError(i - 1, EX, EX, EY * Shift, EY * Shift);
   }

   File.Close();

   G.SetLineColor(Color[C]);
   G.SetMarkerColor(Color[C]);
   G.SetFillColorAlpha(Color[C], 0.25);
   G.SetMarkerSize(1.5);
}


