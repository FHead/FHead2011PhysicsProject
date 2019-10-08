#include <iostream>
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

int Color[5] = {-1, -1, -1, -1, -1};

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
void GetRAA(TH1D &H, string FileName, int R, int C, bool Sys = false);
void Rebin(TH1D &H1, TH1D &H2);
void DrawLumiTAA(double Lumi, double TAA[4], double XMin, double XMax);

int main(int argc, char *argv[])
{
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

   double XMin = 150;
   double XMax = 1500;
   double YMin = 0.0;
   double YMax = 1.199;

   string File = "RAA_Smooth.root";

   double Lumi = 0.023;
   double TAA[4] = {0.100719, 0.051233, 0.025341, 0.018646};

   // Start declaring canvas, pad, axis, and axis title (as TLatex)
   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

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

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 510, "G");
   TGaxis AxisX2(PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 0, XMin, XMax, 510, "G");
   TGaxis AxisX3(PadX0 + PadDX * 2, PadY0 + PadDY * 0, PadX0 + PadDX * 3, PadY0 + PadDY * 0, XMin, XMax, 510, "G");
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin, YMax, 510, "");
   TGaxis AxisY2(PadX0 + PadDX * 0, PadY0 + PadDY * 1, PadX0 + PadDX * 0, PadY0 + PadDY * 2, YMin, YMax, 510, "");

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
   Latex.DrawLatex(PadX0 + PadDX * 1.5, PadY0 * 0.20, "Jet p_{T} (GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.20, PadY0 + PadDY, "R_{AA}");

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

   double Bins[] = {200, 250, 300, 400, 500, 1000};
   TH1D HR02C00RAA("HR02C00RAA", "", 5, Bins);   GetRAA(HR02C00RAA, File, R02, C0, false);
   TH1D HR02C01RAA("HR02C01RAA", "", 5, Bins);   GetRAA(HR02C01RAA, File, R02, C1, false);
   TH1D HR02C02RAA("HR02C02RAA", "", 5, Bins);   GetRAA(HR02C02RAA, File, R02, C2, false);
   TH1D HR02C03RAA("HR02C03RAA", "", 5, Bins);   GetRAA(HR02C03RAA, File, R02, C3, false);
   TH1D HR03C00RAA("HR03C00RAA", "", 5, Bins);   GetRAA(HR03C00RAA, File, R03, C0, false);
   TH1D HR03C01RAA("HR03C01RAA", "", 5, Bins);   GetRAA(HR03C01RAA, File, R03, C1, false);
   TH1D HR03C02RAA("HR03C02RAA", "", 5, Bins);   GetRAA(HR03C02RAA, File, R03, C2, false);
   TH1D HR03C03RAA("HR03C03RAA", "", 5, Bins);   GetRAA(HR03C03RAA, File, R03, C3, false);
   TH1D HR04C00RAA("HR04C00RAA", "", 5, Bins);   GetRAA(HR04C00RAA, File, R04, C0, false);
   TH1D HR04C01RAA("HR04C01RAA", "", 5, Bins);   GetRAA(HR04C01RAA, File, R04, C1, false);
   TH1D HR04C02RAA("HR04C02RAA", "", 5, Bins);   GetRAA(HR04C02RAA, File, R04, C2, false);
   TH1D HR04C03RAA("HR04C03RAA", "", 5, Bins);   GetRAA(HR04C03RAA, File, R04, C3, false);
   TH1D HR06C00RAA("HR06C00RAA", "", 5, Bins);   GetRAA(HR06C00RAA, File, R06, C0, false);
   TH1D HR06C01RAA("HR06C01RAA", "", 5, Bins);   GetRAA(HR06C01RAA, File, R06, C1, false);
   TH1D HR06C02RAA("HR06C02RAA", "", 5, Bins);   GetRAA(HR06C02RAA, File, R06, C2, false);
   TH1D HR06C03RAA("HR06C03RAA", "", 5, Bins);   GetRAA(HR06C03RAA, File, R06, C3, false);
   TH1D HR08C00RAA("HR08C00RAA", "", 5, Bins);   GetRAA(HR08C00RAA, File, R08, C0, false);
   TH1D HR08C01RAA("HR08C01RAA", "", 5, Bins);   GetRAA(HR08C01RAA, File, R08, C1, false);
   TH1D HR08C02RAA("HR08C02RAA", "", 5, Bins);   GetRAA(HR08C02RAA, File, R08, C2, false);
   TH1D HR08C03RAA("HR08C03RAA", "", 5, Bins);   GetRAA(HR08C03RAA, File, R08, C3, false);
   TH1D HR10C00RAA("HR10C00RAA", "", 5, Bins);   GetRAA(HR10C00RAA, File, R10, C0, false);
   TH1D HR10C01RAA("HR10C01RAA", "", 5, Bins);   GetRAA(HR10C01RAA, File, R10, C1, false);
   TH1D HR10C02RAA("HR10C02RAA", "", 5, Bins);   GetRAA(HR10C02RAA, File, R10, C2, false);
   TH1D HR10C03RAA("HR10C03RAA", "", 5, Bins);   GetRAA(HR10C03RAA, File, R10, C3, false);
   
   TH1D HR02C00RAASys("HR02C00RAASys", "", 5, Bins);   GetRAA(HR02C00RAASys, File, R02, C0, true);
   TH1D HR02C01RAASys("HR02C01RAASys", "", 5, Bins);   GetRAA(HR02C01RAASys, File, R02, C1, true);
   TH1D HR02C02RAASys("HR02C02RAASys", "", 5, Bins);   GetRAA(HR02C02RAASys, File, R02, C2, true);
   TH1D HR02C03RAASys("HR02C03RAASys", "", 5, Bins);   GetRAA(HR02C03RAASys, File, R02, C3, true);
   TH1D HR03C00RAASys("HR03C00RAASys", "", 5, Bins);   GetRAA(HR03C00RAASys, File, R03, C0, true);
   TH1D HR03C01RAASys("HR03C01RAASys", "", 5, Bins);   GetRAA(HR03C01RAASys, File, R03, C1, true);
   TH1D HR03C02RAASys("HR03C02RAASys", "", 5, Bins);   GetRAA(HR03C02RAASys, File, R03, C2, true);
   TH1D HR03C03RAASys("HR03C03RAASys", "", 5, Bins);   GetRAA(HR03C03RAASys, File, R03, C3, true);
   TH1D HR04C00RAASys("HR04C00RAASys", "", 5, Bins);   GetRAA(HR04C00RAASys, File, R04, C0, true);
   TH1D HR04C01RAASys("HR04C01RAASys", "", 5, Bins);   GetRAA(HR04C01RAASys, File, R04, C1, true);
   TH1D HR04C02RAASys("HR04C02RAASys", "", 5, Bins);   GetRAA(HR04C02RAASys, File, R04, C2, true);
   TH1D HR04C03RAASys("HR04C03RAASys", "", 5, Bins);   GetRAA(HR04C03RAASys, File, R04, C3, true);
   TH1D HR06C00RAASys("HR06C00RAASys", "", 5, Bins);   GetRAA(HR06C00RAASys, File, R06, C0, true);
   TH1D HR06C01RAASys("HR06C01RAASys", "", 5, Bins);   GetRAA(HR06C01RAASys, File, R06, C1, true);
   TH1D HR06C02RAASys("HR06C02RAASys", "", 5, Bins);   GetRAA(HR06C02RAASys, File, R06, C2, true);
   TH1D HR06C03RAASys("HR06C03RAASys", "", 5, Bins);   GetRAA(HR06C03RAASys, File, R06, C3, true);
   TH1D HR08C00RAASys("HR08C00RAASys", "", 5, Bins);   GetRAA(HR08C00RAASys, File, R08, C0, true);
   TH1D HR08C01RAASys("HR08C01RAASys", "", 5, Bins);   GetRAA(HR08C01RAASys, File, R08, C1, true);
   TH1D HR08C02RAASys("HR08C02RAASys", "", 5, Bins);   GetRAA(HR08C02RAASys, File, R08, C2, true);
   TH1D HR08C03RAASys("HR08C03RAASys", "", 5, Bins);   GetRAA(HR08C03RAASys, File, R08, C3, true);
   TH1D HR10C00RAASys("HR10C00RAASys", "", 5, Bins);   GetRAA(HR10C00RAASys, File, R10, C0, true);
   TH1D HR10C01RAASys("HR10C01RAASys", "", 5, Bins);   GetRAA(HR10C01RAASys, File, R10, C1, true);
   TH1D HR10C02RAASys("HR10C02RAASys", "", 5, Bins);   GetRAA(HR10C02RAASys, File, R10, C2, true);
   TH1D HR10C03RAASys("HR10C03RAASys", "", 5, Bins);   GetRAA(HR10C03RAASys, File, R10, C3, true);

   TLegend Legend(0.1, 0.08, 0.5, 0.48);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.07);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&HR02C00RAASys, "0-10%", "plf");
   Legend.AddEntry(&HR02C01RAASys, "10-30%", "plf");
   Legend.AddEntry(&HR02C02RAASys, "30-50%", "plf");
   Legend.AddEntry(&HR02C03RAASys, "50-90%", "plf");

   TLegend Legend2(0.45, 0.08, 0.85, 0.48);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.07);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry(&HR02C00RAA, "T_{AA}", "f");
   Legend2.AddEntry(&HR02C01RAA, "", "f");
   Legend2.AddEntry(&HR02C02RAA, "", "f");
   Legend2.AddEntry(&HR02C03RAA, "", "f");
   
   TH1D HLumi("HLumi", "", 1, 0, 1);
   HLumi.SetFillColor(Color[4]);
   TLegend Legend3(0.7, 0.08, 1.1, 0.48);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.07);
   Legend3.SetFillStyle(0);
   Legend3.SetBorderSize(0);
   Legend3.AddEntry(&HLumi, "Lumi", "f");
   Legend3.AddEntry("", "", "");
   Legend3.AddEntry("", "", "");
   Legend3.AddEntry("", "", "");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.07);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld.Draw("axis");
   HR02C00RAASys.Draw("same e2");
   HR02C01RAASys.Draw("same e2");
   HR02C02RAASys.Draw("same e2");
   HR02C03RAASys.Draw("same e2");
   HR02C00RAA.Draw("same");
   HR02C01RAA.Draw("same");
   HR02C02RAA.Draw("same");
   HR02C03RAA.Draw("same");
   DrawLumiTAA(Lumi, TAA, XMin, XMax);
   GLine.Draw("l");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.1, "anti-k_{T}, |#eta_{jet}| < 2");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.2");
   P2.cd();
   HWorld.Draw("axis");
   HR03C00RAASys.Draw("same e2");
   HR03C01RAASys.Draw("same e2");
   HR03C02RAASys.Draw("same e2");
   HR03C03RAASys.Draw("same e2");
   HR03C00RAA.Draw("same");
   HR03C01RAA.Draw("same");
   HR03C02RAA.Draw("same");
   HR03C03RAA.Draw("same");
   DrawLumiTAA(Lumi, TAA, XMin, XMax);
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.3");
   P3.cd();
   HWorld.Draw("axis");
   HR04C00RAASys.Draw("same e2");
   HR04C01RAASys.Draw("same e2");
   HR04C02RAASys.Draw("same e2");
   HR04C03RAASys.Draw("same e2");
   HR04C00RAA.Draw("same");
   HR04C01RAA.Draw("same");
   HR04C02RAA.Draw("same");
   HR04C03RAA.Draw("same");
   DrawLumiTAA(Lumi, TAA, XMin, XMax);
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.4");
   P4.cd();
   HWorld.Draw("axis");
   HR06C00RAASys.Draw("same e2");
   HR06C01RAASys.Draw("same e2");
   HR06C02RAASys.Draw("same e2");
   HR06C03RAASys.Draw("same e2");
   HR06C00RAA.Draw("same");
   HR06C01RAA.Draw("same");
   HR06C02RAA.Draw("same");
   HR06C03RAA.Draw("same");
   DrawLumiTAA(Lumi, TAA, XMin, XMax);
   Legend.Draw();
   Legend2.Draw();
   Legend3.Draw();
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.6");
   P5.cd();
   HWorld.Draw("axis");
   HR08C00RAASys.Draw("same e2");
   HR08C01RAASys.Draw("same e2");
   HR08C02RAASys.Draw("same e2");
   HR08C03RAASys.Draw("same e2");
   HR08C00RAA.Draw("same");
   HR08C01RAA.Draw("same");
   HR08C02RAA.Draw("same");
   HR08C03RAA.Draw("same");
   DrawLumiTAA(Lumi, TAA, XMin, XMax);
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.8");
   P6.cd();
   HWorld.Draw("axis");
   HR10C00RAASys.Draw("same e2");
   HR10C01RAASys.Draw("same e2");
   HR10C02RAASys.Draw("same e2");
   HR10C03RAASys.Draw("same e2");
   HR10C00RAA.Draw("same");
   HR10C01RAA.Draw("same");
   HR10C02RAA.Draw("same");
   HR10C03RAA.Draw("same");
   DrawLumiTAA(Lumi, TAA, XMin, XMax);
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 1.0");

   Canvas.SaveAs("PlotRAA.pdf");
   Canvas.SaveAs("PlotRAA.png");

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
      Box.SetFillColor(Color[i]);
      x1 = Offset - Size * 0.5 + Grid * (i + 1);
      x2 = Offset + Size * 0.5 + Grid * (i + 1);
      X1 = exp(x1 * (log(XMax) - log(XMin)) + log(XMin));
      X2 = exp(x2 * (log(XMax) - log(XMin)) + log(XMin));
      Box.DrawBox(X1, 1 - TAA[i], X2, 1 + TAA[i]);
   }
}


