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
void GetIan(TGraphAsymmErrors &G, string IanFileName, bool Rebin = false);
void GetRatio(TGraphAsymmErrors &GRatio, TGraphAsymmErrors &G, TGraphAsymmErrors &GIan);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName = CL.Get("Input", "Spectra_Smooth.root");

   // Preamble: sizing
   int PanelSizeX = 400;
   int PanelSizeY = 500;
   int PanelSizeR = 100;
   int PaddingWidthL = 100;
   int PaddingWidthR = 25;
   int PaddingHeight = 50;
   int CanvasWidth = PanelSizeX * 1 + PaddingWidthL + PaddingWidthR;
   int CanvasHeight = PanelSizeY * 1 + PanelSizeR + PaddingHeight * 2;
   double TickLength = 10;

   double PadX0 = (double)PaddingWidthL / CanvasWidth;
   double PadY0 = (double)PaddingHeight / CanvasHeight;
   double PadDX = (double)PanelSizeX / CanvasWidth;
   double PadDY = (double)PanelSizeY / CanvasHeight;
   double PadDYR = (double)PanelSizeR / CanvasHeight;

   double XMin = 200 / 1.2;
   double XMax = 1000 * 1.2;
   double YMin = 3e-6;
   double YMax = 1e4;
   double RMin = 0.60;
   double RMax = 1.39;

   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   TH2D HWorldR("HWorldR", ";;", 100, XMin, XMax, 100, RMin, RMax);
   HWorld.SetStats(0);
   HWorldR.SetStats(0);

   HWorldR.GetYaxis()->SetNdivisions(505);

   HWorldR.GetXaxis()->SetTickLength(TickLength / PanelSizeR);
   HWorld.GetXaxis()->SetTickLength(TickLength / PanelSizeY);
   HWorldR.GetYaxis()->SetTickLength(TickLength / PanelSizeX);
   HWorld.GetYaxis()->SetTickLength(TickLength / PanelSizeX);

   TPad P1("P1", "", PadX0 + PadDX * 0, PadY0 + PadDYR, PadX0 + PadDX * 1, PadY0 + PadDY + PadDYR, 0);
   TPad P2("P2", "", PadX0 + PadDX * 0, PadY0, PadX0 + PadDX * 1, PadY0 + PadDYR, 0);

   SetPad(P1, false);
   SetPad(P2, true);

   Canvas.cd();

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 510, "GS");
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDYR   , PadX0 + PadDX * 0, PadY0 + PadDYR + PadDY, YMin, YMax, 510, "GS");
   TGaxis AxisY2(PadX0 + PadDX * 0, PadY0            , PadX0 + PadDX * 0, PadY0 + PadDYR, RMin, RMax, 505, "S");

   SetAxis(AxisX1, true);
   SetAxis(AxisY1, false);
   SetAxis(AxisY2, false);

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 0.5, PadY0 * 0.30, "Jet p_{T} (GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.30, PadY0 + PadDYR + PadDY * 0.5, "#frac{1}{<T_{AA}>} #frac{1}{N_{evt}} #frac{d^{2}N_{jet}}{dp_{T}d#eta} or #frac{d^{2}#sigma_{jet}}{dp_{T}d#eta} (nb/GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.30, PadY0 + PadDYR * 0.5, "Chris / Ian");

   Latex.SetTextFont(62);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDYR + PadDY * 1 + PadY0 * 0.15, "CMS");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 1, PadY0 + PadDYR + PadDY * 1 + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 404 #mub^{-1}, pp 27.4 pb^{-1}");

   TGraphAsymmErrors GPPR04, GPPR04Sys;
   TGraphAsymmErrors GPbPbC0R04, GPbPbC0R04Sys;
   TGraphAsymmErrors GPbPbC1R04, GPbPbC1R04Sys;
   TGraphAsymmErrors GPbPbC2R04, GPbPbC2R04Sys;
   TGraphAsymmErrors GPbPbC3R04, GPbPbC3R04Sys;

   string IanFileName = "Ian/ak4PFJets_wjtID_anabins_Bayes_PY8_FullRECO_10.22.19_CHRISbins2_withJECsysv2_SMPbins_withLumiCorr_LOMC_00eta05.root";
   TGraphAsymmErrors GIan;
   GetIan(GIan, IanFileName, true);

   TLegend Legend(0.45, 0.65, 0.75, 0.95);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.05);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&GPbPbC0R04Sys, "PbPb 0-10% #times10^{4}",  "plf");
   Legend.AddEntry(&GPbPbC1R04Sys, "PbPb 10-30% #times10^{3}", "plf");
   Legend.AddEntry(&GPbPbC2R04Sys, "PbPb 30-50% #times10^{2}", "plf");
   Legend.AddEntry(&GPbPbC3R04Sys, "PbPb 50-90% #times10^{1}", "plf");
   Legend.AddEntry(&GPPR04Sys,     "pp #times10^{0}",          "plf");
   Legend.AddEntry(&GIan,          "pp (Ian)",                 "plf");

   GetGraph(FileName, GPPR04, R04, PP, 1, false);          GetGraph(FileName, GPPR04Sys, R04, PP, 1, true);
   GetGraph(FileName, GPbPbC0R04, R04, C0, 1e+3, false);   GetGraph(FileName, GPbPbC0R04Sys, R04, C0, 1e+3, true);
   GetGraph(FileName, GPbPbC1R04, R04, C1, 1e+1, false);   GetGraph(FileName, GPbPbC1R04Sys, R04, C1, 1e+1, true);
   GetGraph(FileName, GPbPbC2R04, R04, C2, 1e-1, false);   GetGraph(FileName, GPbPbC2R04Sys, R04, C2, 1e-1, true);
   GetGraph(FileName, GPbPbC3R04, R04, C3, 1e-3, false);   GetGraph(FileName, GPbPbC3R04Sys, R04, C3, 1e-3, true);

   TGraphAsymmErrors GRatio, GRatioSys, GRatioIan;
   GetRatio(GRatio, GPPR04, GIan);
   GetRatio(GRatioSys, GPPR04Sys, GIan);
   GetRatio(GRatioIan, GIan, GIan);

   TGraph Line;
   Line.SetPoint(0, 0, 1);
   Line.SetPoint(1, 10000, 1);

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.05);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld.Draw("axis");
   GPPR04Sys.Draw("2");
   GPbPbC0R04Sys.Draw("2");
   GPbPbC1R04Sys.Draw("2");
   GPbPbC2R04Sys.Draw("2");
   GPbPbC3R04Sys.Draw("2");
   GPPR04.Draw("p");
   GPbPbC0R04.Draw("p");
   GPbPbC1R04.Draw("p");
   GPbPbC2R04.Draw("p");
   GPbPbC3R04.Draw("p");
   GIan.Draw("2");
   GIan.Draw("p");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.12, "anti-k_{T} R = 0.4");
   Latex.DrawLatex(0.08, 0.06, "|#eta_{jet}| < 2.0");
   Legend.Draw();
   P2.cd();
   HWorldR.Draw("axis");
   Line.Draw("l");
   GRatioIan.Draw("2");
   GRatio.Draw("p"); 
   GRatioSys.Draw("2");

   string OutputBase = "SpectraSinglePanelR04";

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

void GetIan(TGraphAsymmErrors &G, string IanFileName, bool Rebin)
{
   if(Color[5] == -1)
   {
      Color[0] = TColor::GetColor("#E74C3C");
      Color[1] = TColor::GetColor("#3498DB");
      Color[2] = TColor::GetColor("#F1C40F");
      Color[3] = TColor::GetColor("#2ECC71");
      Color[4] = TColor::GetColor("#7F7F7F");
      Color[5] = TColor::GetColor("#8E44AD");
   }

   TFile F(IanFileName.c_str());

   TH1D *H = (TH1D *)F.Get("Data_unf");
      
   vector<double> XMax;
   vector<double> XMin;
   vector<double> Y;
   vector<double> X;
   vector<double> EY;
   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      XMax.push_back(H->GetXaxis()->GetBinUpEdge(i));
      XMin.push_back(H->GetXaxis()->GetBinLowEdge(i));
      Y.push_back(H->GetBinContent(i));
      EY.push_back(H->GetBinError(i));
      X.push_back((XMax[i-1] + XMin[i-1]) / 2);
   }

   if(Rebin == false)
   {
      for(int i = 0; i < (int)X.size(); i++)
      {
         G.SetPoint(i, X[i], Y[i]);
         G.SetPointError(i, X[i] - XMin[i], XMax[i] - X[i], EY[i], EY[i]);
      }
   }
   else
   {
      G.SetPoint(0, (XMin[0] + XMax[0]) / 2, Y[0]);
      G.SetPoint(1, (XMin[1] + XMax[1]) / 2, Y[1]);
      G.SetPoint(2, (XMin[2] + XMax[3]) / 2, (Y[2] * 50 + Y[3] * 50) / 100);
      G.SetPoint(3, (XMin[4] + XMax[4]) / 2, Y[4]);
      G.SetPoint(4, (XMin[5] + XMax[6]) / 2, (Y[5] * 120 + Y[6] * 380) / 500);
      
      double EY23 = sqrt(EY[2] * EY[2] * 50 * 50 + EY[3] * EY[3] * 50 * 50) / 100;
      double EY56 = sqrt(EY[5] * EY[5] * 120 * 120 + EY[6] * EY[6] * 380 * 380) / 500;

      G.SetPointError(0, (XMax[0] - XMin[0]) / 2, (XMax[0] - XMin[0]) / 2, EY[0], EY[0]);
      G.SetPointError(1, (XMax[1] - XMin[1]) / 2, (XMax[1] - XMin[1]) / 2, EY[1], EY[1]);
      G.SetPointError(2, (XMax[3] - XMin[2]) / 2, (XMax[3] - XMin[2]) / 2, EY23, EY23);
      G.SetPointError(3, (XMax[4] - XMin[4]) / 2, (XMax[4] - XMin[4]) / 2, EY[4], EY[4]);
      G.SetPointError(4, (XMax[6] - XMin[5]) / 2, (XMax[6] - XMin[5]) / 2, EY56, EY56);
   }

   G.SetMarkerStyle(20);
   G.SetMarkerColor(Color[5]);
   G.SetLineColor(Color[5]);
   G.SetFillColorAlpha(Color[5], 0.25);
   G.SetMarkerSize(1.25);

   F.Close();
}

void GetRatio(TGraphAsymmErrors &GRatio, TGraphAsymmErrors &G, TGraphAsymmErrors &GIan)
{
   int N = G.GetN();

   for(int i = 0; i < N; i++)
   {
      double IanX, IanY;
      double X, Y;
      double EXL, EXH, EYL, EYH;

      GIan.GetPoint(i, IanX, IanY);
      G.GetPoint(i, X, Y);
      EXL = G.GetErrorXlow(i);
      EXH = G.GetErrorXhigh(i);
      EYL = G.GetErrorYlow(i);
      EYH = G.GetErrorYhigh(i);

      GRatio.SetPoint(i, X, Y / IanY);
      GRatio.SetPointError(i, EXL, EXH, EYL / IanY, EYH / IanY);
   }

   GRatio.SetLineColor(G.GetLineColor());
   GRatio.SetLineStyle(G.GetLineStyle());
   GRatio.SetLineWidth(G.GetLineWidth());
   GRatio.SetMarkerColor(G.GetMarkerColor());
   GRatio.SetMarkerStyle(G.GetMarkerStyle());
   GRatio.SetMarkerSize(G.GetMarkerSize());
   GRatio.SetFillColor(G.GetFillColor());
}

