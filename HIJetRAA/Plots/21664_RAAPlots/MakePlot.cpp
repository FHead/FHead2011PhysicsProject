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

int Color[4] = {-1, -1, -1, -1};

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
void GetRAA(TH1D &H, string FilePP, string FilePbPb, int R, int C, bool Sys = false);
void Rebin(TH1D &H1, TH1D &H2);

TH1D *GetPPSpectrum(TFile &F, int R, int C);
TH1D *GetPbPbSpectrum(TFile &F, int R, int C);

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

   string FilePP = "Sep11plots/dataPP_UnfoldRawData_CombinedAlgos_NoClean_NToy1000_20190606.root";
   string FilePbPb = "Sep11plots/dataPbPb_UnfoldRawData_CombinedAlgos_NoClean_NToy1000_20190606.root";

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
   TH1D HR02C00RAA("HR02C00RAA", "", 5, Bins);   GetRAA(HR02C00RAA, FilePP, FilePbPb, R02, C0, false);
   TH1D HR02C01RAA("HR02C01RAA", "", 5, Bins);   GetRAA(HR02C01RAA, FilePP, FilePbPb, R02, C1, false);
   TH1D HR02C02RAA("HR02C02RAA", "", 5, Bins);   GetRAA(HR02C02RAA, FilePP, FilePbPb, R02, C2, false);
   TH1D HR02C03RAA("HR02C03RAA", "", 5, Bins);   GetRAA(HR02C03RAA, FilePP, FilePbPb, R02, C3, false);
   TH1D HR03C00RAA("HR03C00RAA", "", 5, Bins);   GetRAA(HR03C00RAA, FilePP, FilePbPb, R03, C0, false);
   TH1D HR03C01RAA("HR03C01RAA", "", 5, Bins);   GetRAA(HR03C01RAA, FilePP, FilePbPb, R03, C1, false);
   TH1D HR03C02RAA("HR03C02RAA", "", 5, Bins);   GetRAA(HR03C02RAA, FilePP, FilePbPb, R03, C2, false);
   TH1D HR03C03RAA("HR03C03RAA", "", 5, Bins);   GetRAA(HR03C03RAA, FilePP, FilePbPb, R03, C3, false);
   TH1D HR04C00RAA("HR04C00RAA", "", 5, Bins);   GetRAA(HR04C00RAA, FilePP, FilePbPb, R04, C0, false);
   TH1D HR04C01RAA("HR04C01RAA", "", 5, Bins);   GetRAA(HR04C01RAA, FilePP, FilePbPb, R04, C1, false);
   TH1D HR04C02RAA("HR04C02RAA", "", 5, Bins);   GetRAA(HR04C02RAA, FilePP, FilePbPb, R04, C2, false);
   TH1D HR04C03RAA("HR04C03RAA", "", 5, Bins);   GetRAA(HR04C03RAA, FilePP, FilePbPb, R04, C3, false);
   TH1D HR06C00RAA("HR06C00RAA", "", 5, Bins);   GetRAA(HR06C00RAA, FilePP, FilePbPb, R06, C0, false);
   TH1D HR06C01RAA("HR06C01RAA", "", 5, Bins);   GetRAA(HR06C01RAA, FilePP, FilePbPb, R06, C1, false);
   TH1D HR06C02RAA("HR06C02RAA", "", 5, Bins);   GetRAA(HR06C02RAA, FilePP, FilePbPb, R06, C2, false);
   TH1D HR06C03RAA("HR06C03RAA", "", 5, Bins);   GetRAA(HR06C03RAA, FilePP, FilePbPb, R06, C3, false);
   TH1D HR08C00RAA("HR08C00RAA", "", 5, Bins);   GetRAA(HR08C00RAA, FilePP, FilePbPb, R08, C0, false);
   TH1D HR08C01RAA("HR08C01RAA", "", 5, Bins);   GetRAA(HR08C01RAA, FilePP, FilePbPb, R08, C1, false);
   TH1D HR08C02RAA("HR08C02RAA", "", 5, Bins);   GetRAA(HR08C02RAA, FilePP, FilePbPb, R08, C2, false);
   TH1D HR08C03RAA("HR08C03RAA", "", 5, Bins);   GetRAA(HR08C03RAA, FilePP, FilePbPb, R08, C3, false);
   TH1D HR10C00RAA("HR10C00RAA", "", 5, Bins);   GetRAA(HR10C00RAA, FilePP, FilePbPb, R10, C0, false);
   TH1D HR10C01RAA("HR10C01RAA", "", 5, Bins);   GetRAA(HR10C01RAA, FilePP, FilePbPb, R10, C1, false);
   TH1D HR10C02RAA("HR10C02RAA", "", 5, Bins);   GetRAA(HR10C02RAA, FilePP, FilePbPb, R10, C2, false);
   TH1D HR10C03RAA("HR10C03RAA", "", 5, Bins);   GetRAA(HR10C03RAA, FilePP, FilePbPb, R10, C3, false);
   
   TH1D HR02C00RAASys("HR02C00RAASys", "", 5, Bins);   GetRAA(HR02C00RAASys, FilePP, FilePbPb, R02, C0, true);
   TH1D HR02C01RAASys("HR02C01RAASys", "", 5, Bins);   GetRAA(HR02C01RAASys, FilePP, FilePbPb, R02, C1, true);
   TH1D HR02C02RAASys("HR02C02RAASys", "", 5, Bins);   GetRAA(HR02C02RAASys, FilePP, FilePbPb, R02, C2, true);
   TH1D HR02C03RAASys("HR02C03RAASys", "", 5, Bins);   GetRAA(HR02C03RAASys, FilePP, FilePbPb, R02, C3, true);
   TH1D HR03C00RAASys("HR03C00RAASys", "", 5, Bins);   GetRAA(HR03C00RAASys, FilePP, FilePbPb, R03, C0, true);
   TH1D HR03C01RAASys("HR03C01RAASys", "", 5, Bins);   GetRAA(HR03C01RAASys, FilePP, FilePbPb, R03, C1, true);
   TH1D HR03C02RAASys("HR03C02RAASys", "", 5, Bins);   GetRAA(HR03C02RAASys, FilePP, FilePbPb, R03, C2, true);
   TH1D HR03C03RAASys("HR03C03RAASys", "", 5, Bins);   GetRAA(HR03C03RAASys, FilePP, FilePbPb, R03, C3, true);
   TH1D HR04C00RAASys("HR04C00RAASys", "", 5, Bins);   GetRAA(HR04C00RAASys, FilePP, FilePbPb, R04, C0, true);
   TH1D HR04C01RAASys("HR04C01RAASys", "", 5, Bins);   GetRAA(HR04C01RAASys, FilePP, FilePbPb, R04, C1, true);
   TH1D HR04C02RAASys("HR04C02RAASys", "", 5, Bins);   GetRAA(HR04C02RAASys, FilePP, FilePbPb, R04, C2, true);
   TH1D HR04C03RAASys("HR04C03RAASys", "", 5, Bins);   GetRAA(HR04C03RAASys, FilePP, FilePbPb, R04, C3, true);
   TH1D HR06C00RAASys("HR06C00RAASys", "", 5, Bins);   GetRAA(HR06C00RAASys, FilePP, FilePbPb, R06, C0, true);
   TH1D HR06C01RAASys("HR06C01RAASys", "", 5, Bins);   GetRAA(HR06C01RAASys, FilePP, FilePbPb, R06, C1, true);
   TH1D HR06C02RAASys("HR06C02RAASys", "", 5, Bins);   GetRAA(HR06C02RAASys, FilePP, FilePbPb, R06, C2, true);
   TH1D HR06C03RAASys("HR06C03RAASys", "", 5, Bins);   GetRAA(HR06C03RAASys, FilePP, FilePbPb, R06, C3, true);
   TH1D HR08C00RAASys("HR08C00RAASys", "", 5, Bins);   GetRAA(HR08C00RAASys, FilePP, FilePbPb, R08, C0, true);
   TH1D HR08C01RAASys("HR08C01RAASys", "", 5, Bins);   GetRAA(HR08C01RAASys, FilePP, FilePbPb, R08, C1, true);
   TH1D HR08C02RAASys("HR08C02RAASys", "", 5, Bins);   GetRAA(HR08C02RAASys, FilePP, FilePbPb, R08, C2, true);
   TH1D HR08C03RAASys("HR08C03RAASys", "", 5, Bins);   GetRAA(HR08C03RAASys, FilePP, FilePbPb, R08, C3, true);
   TH1D HR10C00RAASys("HR10C00RAASys", "", 5, Bins);   GetRAA(HR10C00RAASys, FilePP, FilePbPb, R10, C0, true);
   TH1D HR10C01RAASys("HR10C01RAASys", "", 5, Bins);   GetRAA(HR10C01RAASys, FilePP, FilePbPb, R10, C1, true);
   TH1D HR10C02RAASys("HR10C02RAASys", "", 5, Bins);   GetRAA(HR10C02RAASys, FilePP, FilePbPb, R10, C2, true);
   TH1D HR10C03RAASys("HR10C03RAASys", "", 5, Bins);   GetRAA(HR10C03RAASys, FilePP, FilePbPb, R10, C3, true);

   TLegend Legend(0.1, 0.1, 0.5, 0.5);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.07);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&HR02C00RAA, "0-10%", "pl");
   Legend.AddEntry(&HR02C01RAA, "10-30%", "pl");
   Legend.AddEntry(&HR02C02RAA, "30-50%", "pl");
   Legend.AddEntry(&HR02C03RAA, "50-90%", "pl");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.07);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld.Draw("axis");
   HR02C00RAA.Draw("same");
   HR02C01RAA.Draw("same");
   HR02C02RAA.Draw("same");
   HR02C03RAA.Draw("same");
   GLine.Draw("l");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.1, "anti-k_{T}, |#eta_{jet}| < 2");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.2");
   P2.cd();
   HWorld.Draw("axis");
   HR03C00RAA.Draw("same");
   HR03C01RAA.Draw("same");
   HR03C02RAA.Draw("same");
   HR03C03RAA.Draw("same");
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.3");
   P3.cd();
   HWorld.Draw("axis");
   HR04C00RAA.Draw("same");
   HR04C01RAA.Draw("same");
   HR04C02RAA.Draw("same");
   HR04C03RAA.Draw("same");
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.4");
   P4.cd();
   HWorld.Draw("axis");
   HR06C00RAA.Draw("same");
   HR06C01RAA.Draw("same");
   HR06C02RAA.Draw("same");
   HR06C03RAA.Draw("same");
   Legend.Draw();
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.6");
   P5.cd();
   HWorld.Draw("axis");
   HR08C00RAA.Draw("same");
   HR08C01RAA.Draw("same");
   HR08C02RAA.Draw("same");
   HR08C03RAA.Draw("same");
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 0.8");
   P6.cd();
   HWorld.Draw("axis");
   HR10C00RAA.Draw("same");
   HR10C01RAA.Draw("same");
   HR10C02RAA.Draw("same");
   HR10C03RAA.Draw("same");
   GLine.Draw("l");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.9, "R = 1.0");

   Canvas.SaveAs("Plot.pdf");

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

void GetRAA(TH1D &H, string FilePP, string FilePbPb, int R, int C, bool Sys)
{
   TFile FPP(FilePP.c_str());
   TFile FPbPb(FilePbPb.c_str());

   TH1D *HRawPP   = GetPPSpectrum(FPP, R, C);
   TH1D *HRawPbPb = GetPbPbSpectrum(FPbPb, R, C);

   double Bins[] = {200, 250, 300, 400, 500, 1000};
   TH1D HPP("HPP", "", 5, Bins);
   TH1D HPbPb("HPbPb", "", 5, Bins);
   
   Rebin(*HRawPP, HPP);
   Rebin(*HRawPbPb, HPbPb);

   int Min[6][4] = {{3, 1, 1, 1}, {3, 1, 1, 1}, {4, 3, 2, 1}, {4, 3, 2, 1}, {4, 4, 2, 2}, {5, 4, 2, 2}};
   int Max[6][4] = {{5, 5, 3, 3}, {5, 5, 3, 3}, {5, 5, 3, 3}, {5, 5, 3, 3}, {5, 5, 3, 3}, {5, 5, 3, 3}};

   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      double VPbPb = HPbPb.GetBinContent(i);
      double VPP   = HPP.GetBinContent(i);
      double EPbPb = HPbPb.GetBinError(i) / VPbPb;
      double EPP   = HPP.GetBinError(i) / VPP;

      double V = VPbPb / VPP;
      double E = V * sqrt(EPbPb * EPbPb + EPP * EPP);

      if(i < Min[R][C] || i > Max[R][C])
         V = E = 0;

      H.SetBinContent(i, V);
      H.SetBinError(i, E);
   }

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
   }

   H.SetMarkerStyle(Style[C]);
   H.SetMarkerColor(Color[C]);
   H.SetLineColor(Color[C]);
   H.SetMarkerSize(1.8);
   H.SetLineWidth(2.0);

   FPbPb.Close();
   FPP.Close();
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

   for(int i = 1; i <= H2.GetNbinsX(); i++)
   {
      double BinSize = H2.GetXaxis()->GetBinUpEdge(i) - H2.GetXaxis()->GetBinLowEdge(i);

      H2.SetBinContent(i, H2.GetBinContent(i) / BinSize);
      H2.SetBinError(i, H2.GetBinError(i) / BinSize);
   }
}

TH1D *GetPPSpectrum(TFile &F, int R, int C)
{
   string CentString[] = {"0to10", "10to30", "30to50", "50to90"};
   string RString[] = {"2", "3", "4", "6", "8", "10"};
   
   string Name = "ak" + RString[R] + "PFJetAnalyzer_PP_Cent" + CentString[C] + "_LightMUAndCHID_ResponseMod0p10_AbsEta0p0to2p0_";
   TNamed *N = (TNamed *)F.Get(("cutDir/unfoldDirBayes/" + Name).c_str());
   string B = N->GetTitle();
   Name = string("ak") + RString[R] + "PFJetAnalyzer/jtPtUnfoldedBayes_RecoGenAsymm_" + Name + "Bayes" + B + "_h";
   TH1D *H = (TH1D *)F.Get(Name.c_str());
   
   double LumiFactor = 27400;
   H->Scale(1 / (2 * 2 * LumiFactor));

   return H;
}

TH1D *GetPbPbSpectrum(TFile &F, int R, int C)
{
   string CentString[] = {"0to10", "10to30", "30to50", "50to90"};
   string RString[] = {"2", "3", "4", "6", "8", "10"};
   
   string Name = "akCs" + RString[R] + "PU3PFFlowJetAnalyzer_PbPb_Cent" + CentString[C] + "_LightMUAndCHID_ResponseMod0p10_AbsEta0p0to2p0_";
   TNamed *N = (TNamed *)F.Get(("cutDir/unfoldDirBayes/" + Name).c_str());
   string B = N->GetTitle();
   Name = string("akCs") + RString[R] + "PU3PFFlowJetAnalyzer/jtPtUnfoldedBayes_RecoGenAsymm_" + Name + "Bayes" + B + "_h";
   TH1D *H = (TH1D *)F.Get(Name.c_str());

   double CentBinWidth[] = {0.1, 0.2, 0.2, 0.4};
   double MBEventCountPS = (45092445 + 450028) / 0.9;
   double MBPS = double(2506791) / 45784;
   double MBEventCount = MBEventCountPS * MBPS;
   double TAA[] = {0.019, 0.026, 0.054, 0.112};
   double Factor = MBEventCount * 2 * 2 * CentBinWidth[C] * TAA[C] / 1000000;
   H->Scale(1 / Factor);
   
   double RAAFudge[] = {1200, 440, 70, 5};
   H->Scale(1 / RAAFudge[C]);

   return H;
}



