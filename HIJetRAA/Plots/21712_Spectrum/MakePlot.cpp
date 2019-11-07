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

int Color[5] = {-1, -1, -1, -1, -1};

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A, bool X);
void GetGraph(string FileName, TGraphAsymmErrors &G, int R, int Cent, double Shift, bool Sys);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName = CL.Get("Input", "Spectra_Smooth.root");

   // Preamble: sizing
   int PanelSizeX = 400;
   int PanelSizeY = 600;
   int PaddingWidthL = 150;
   int PaddingWidthR = 50;
   int PaddingHeight = 75;
   int CanvasWidth = PanelSizeX * 2 + PaddingWidthL + PaddingWidthR;
   int CanvasHeight = PanelSizeY * 1 + PaddingHeight * 2;

   double PadX0 = (double)PaddingWidthL / CanvasWidth;
   double PadY0 = (double)PaddingHeight / CanvasHeight;
   double PadDX = (double)PanelSizeX / CanvasWidth;
   double PadDY = (double)PanelSizeY / CanvasHeight;

   double XMin = 200 / 1.2;
   double XMax = 1000 * 1.2;
   double YMin = 1e-6;
   double YMax = 1e4;


   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   TPad P1("P1", "", PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 1, 0);
   TPad P2("P2", "", PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 1, 0);

   SetPad(P1);
   SetPad(P2);

   Canvas.cd();

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 510, "GS");
   TGaxis AxisX2(PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 0, XMin, XMax, 510, "GS");
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin, YMax, 510, "GS");

   SetAxis(AxisX1, true);
   SetAxis(AxisX2, true);
   SetAxis(AxisY1, false);

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 1.0, PadY0 * 0.30, "Jet p_{T} (GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.30, PadY0 + PadDY * 0.5, "#frac{1}{<T_{AA}>} #frac{1}{N_{evt}} #frac{d^{2}N_{jet}}{dp_{T}d#eta} or #frac{d^{2}#sigma_{jet}}{dp_{T}d#eta} (nb/GeV)");

   Latex.SetTextFont(62);
   Latex.SetTextSize(0.050);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * 1 + PadY0 * 0.15, "CMS");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 2, PadY0 + PadDY * 1 + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 404 #mub^{-1}, pp 27.4 pb^{-1}");

   TGraphAsymmErrors GPPR02, GPPR02Sys;
   TGraphAsymmErrors GPbPbC0R02, GPbPbC0R02Sys;
   TGraphAsymmErrors GPbPbC1R02, GPbPbC1R02Sys;
   TGraphAsymmErrors GPbPbC2R02, GPbPbC2R02Sys;
   TGraphAsymmErrors GPbPbC3R02, GPbPbC3R02Sys;
   TGraphAsymmErrors GPPR10, GPPR10Sys;
   TGraphAsymmErrors GPbPbC0R10, GPbPbC0R10Sys;
   TGraphAsymmErrors GPbPbC1R10, GPbPbC1R10Sys;
   TGraphAsymmErrors GPbPbC2R10, GPbPbC2R10Sys;
   TGraphAsymmErrors GPbPbC3R10, GPbPbC3R10Sys;

   TLegend Legend(0.40, 0.60, 0.80, 0.95);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.05);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&GPbPbC0R02Sys, "PbPb 0-10% #times10^{4}", "plf");
   Legend.AddEntry(&GPbPbC1R02Sys, "PbPb 10-30% #times10^{3}", "plf");
   Legend.AddEntry(&GPbPbC2R02Sys, "PbPb 30-50% #times10^{2}", "plf");
   Legend.AddEntry(&GPbPbC3R02Sys, "PbPb 50-90% #times10^{1}", "plf");
   Legend.AddEntry(&GPPR02Sys, "pp #times10^{0}", "plf");

   GetGraph(FileName, GPPR02, R02, PP, 1, false);          GetGraph(FileName, GPPR02Sys, R02, PP, 1, true);
   GetGraph(FileName, GPbPbC0R02, R02, C0, 1e+3, false);   GetGraph(FileName, GPbPbC0R02Sys, R02, C0, 1e+3, true);
   GetGraph(FileName, GPbPbC1R02, R02, C1, 1e+1, false);   GetGraph(FileName, GPbPbC1R02Sys, R02, C1, 1e+1, true);
   GetGraph(FileName, GPbPbC2R02, R02, C2, 1e-1, false);   GetGraph(FileName, GPbPbC2R02Sys, R02, C2, 1e-1, true);
   GetGraph(FileName, GPbPbC3R02, R02, C3, 1e-3, false);   GetGraph(FileName, GPbPbC3R02Sys, R02, C3, 1e-3, true);
   GetGraph(FileName, GPPR10, R10, PP, 1, false);          GetGraph(FileName, GPPR10Sys, R10, PP, 1, true);
   GetGraph(FileName, GPbPbC0R10, R10, C0, 1e+3, false);   GetGraph(FileName, GPbPbC0R10Sys, R10, C0, 1e+3, true);
   GetGraph(FileName, GPbPbC1R10, R10, C1, 1e+1, false);   GetGraph(FileName, GPbPbC1R10Sys, R10, C1, 1e+1, true);
   GetGraph(FileName, GPbPbC2R10, R10, C2, 1e-1, false);   GetGraph(FileName, GPbPbC2R10Sys, R10, C2, 1e-1, true);
   GetGraph(FileName, GPbPbC3R10, R10, C3, 1e-3, false);   GetGraph(FileName, GPbPbC3R10Sys, R10, C3, 1e-3, true);

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.065);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld.Draw("axis");
   GPPR02Sys.Draw("2");
   GPbPbC0R02Sys.Draw("2");
   GPbPbC1R02Sys.Draw("2");
   GPbPbC2R02Sys.Draw("2");
   GPbPbC3R02Sys.Draw("2");
   GPPR02.Draw("p");
   GPbPbC0R02.Draw("p");
   GPbPbC1R02.Draw("p");
   GPbPbC2R02.Draw("p");
   GPbPbC3R02.Draw("p");
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.08, 0.95, "#font[62]{R = 0.2}");
   Latex.SetTextAlign(33);
   Latex.DrawLatex(0.92, 0.95, "|#eta_{jet}| < 2.0");
   P2.cd();
   HWorld.Draw("axis");
   GPPR10Sys.Draw("2");
   GPbPbC0R10Sys.Draw("2");
   GPbPbC1R10Sys.Draw("2");
   GPbPbC2R10Sys.Draw("2");
   GPbPbC3R10Sys.Draw("2");
   GPPR10.Draw("p");
   GPbPbC0R10.Draw("p");
   GPbPbC1R10.Draw("p");
   GPbPbC2R10.Draw("p");
   GPbPbC3R10.Draw("p");
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.08, 0.95, "#font[62]{R = 1.0}");
   Legend.Draw();

   string OutputBase = "Spectra";

   Canvas.SaveAs((OutputBase + ".pdf").c_str());
   Canvas.SaveAs((OutputBase + ".png").c_str());
   Canvas.SaveAs((OutputBase + ".C").c_str());

   return 0;
}

void SetPad(TPad &P)
{
   P.SetLogx();
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
   A.Draw();
}

void GetGraph(string FileName, TGraphAsymmErrors &G, int R, int C, double Shift, bool Sys)
{
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



