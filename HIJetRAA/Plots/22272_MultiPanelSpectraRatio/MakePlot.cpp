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
#include "TPaveText.h"

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

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A, bool X);
void SetHistogram(TH1D *H, int Color);
void SetTheoryHistogram(TH1D *H, int Color, bool P8);
void GetRatio(TH1D *H, TH1D *H1, TH1D *H2);

int main(int argc, char *argv[])
{
   TFile File("SpectraRatio_Smooth_RedStat.root");

   int Color[6] = {-1, -1, -1, -1, -1, -1};
   int DarkColor[6] = {-1, -1, -1, -1, -1, -1};
   Color[0] = TColor::GetColor("#E74C3C");
   Color[1] = TColor::GetColor("#3498DB");
   Color[2] = TColor::GetColor("#F1C40F");
   Color[3] = TColor::GetColor("#2ECC71");
   Color[4] = TColor::GetColor("#7F7F7F");
   Color[5] = kMagenta;
   DarkColor[0] = TColor::GetColorDark(Color[0]);
   DarkColor[1] = TColor::GetColorDark(Color[1]);
   DarkColor[2] = TColor::GetColorDark(Color[2]);
   DarkColor[3] = TColor::GetColorDark(Color[3]);
   DarkColor[4] = TColor::GetColorDark(Color[4]);
   DarkColor[5] = TColor::GetColorDark(Color[5]);

   SetThesisStyle();
   gStyle->SetErrorX(0.5);

   CommandLine CL(argc, argv);

   string FileName = CL.Get("Input", "Spectra_Smooth.root");

   // Preamble: sizing
   int PanelSizeX = 500;
   int PanelSizeY1 = 300;
   int PanelSizeY2 = 500;
   int PaddingWidthL = 150;
   int PaddingWidthR = 25;
   int PaddingHeightT = 50;
   int PaddingHeightB = 100;
   int CanvasWidth = PanelSizeX * 5 + PaddingWidthL + PaddingWidthR;
   int CanvasHeight = PanelSizeY1 + PanelSizeY2 + PaddingHeightT + PaddingHeightB;

   double PadX0 = (double)PaddingWidthL / CanvasWidth;
   double PadY0 = (double)PaddingHeightB / CanvasHeight;
   double PadDX = (double)PanelSizeX / CanvasWidth;
   double PadDY1 = (double)PanelSizeY1 / CanvasHeight;
   double PadDY2 = (double)PanelSizeY2 / CanvasHeight;

   double XMin = 200 / 1.2;
   double XMax = 1000 * 1.2;
   double YMin1 = 0.86;
   double YMax1 = 1.25;
   double YMin2 = 0.35;
   double YMax2 = 1.00;

   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld1("HWorld1", ";;", 100, XMin, XMax, 100, YMin1, YMax1);
   HWorld1.SetStats(0);
   TH2D HWorld2("HWorld2", ";;", 100, XMin, XMax, 100, YMin2, YMax2);
   HWorld2.SetStats(0);

   TPad P1( "P1",  "", PadX0 + PadDX * 0, PadY0         , PadX0 + PadDX * 1, PadY0 + PadDY1, 0);
   TPad P2 ("P2",  "", PadX0 + PadDX * 1, PadY0         , PadX0 + PadDX * 2, PadY0 + PadDY1, 0);
   TPad P3 ("P3",  "", PadX0 + PadDX * 2, PadY0         , PadX0 + PadDX * 3, PadY0 + PadDY1, 0);
   TPad P4 ("P4",  "", PadX0 + PadDX * 3, PadY0         , PadX0 + PadDX * 4, PadY0 + PadDY1, 0);
   TPad P5 ("P5",  "", PadX0 + PadDX * 4, PadY0         , PadX0 + PadDX * 5, PadY0 + PadDY1, 0);
   TPad P6 ("P6",  "", PadX0 + PadDX * 0, PadY0 + PadDY1, PadX0 + PadDX * 1, PadY0 + PadDY1 + PadDY2, 0);
   TPad P7 ("P7",  "", PadX0 + PadDX * 1, PadY0 + PadDY1, PadX0 + PadDX * 2, PadY0 + PadDY1 + PadDY2, 0);
   TPad P8 ("P8",  "", PadX0 + PadDX * 2, PadY0 + PadDY1, PadX0 + PadDX * 3, PadY0 + PadDY1 + PadDY2, 0);
   TPad P9 ("P9",  "", PadX0 + PadDX * 3, PadY0 + PadDY1, PadX0 + PadDX * 4, PadY0 + PadDY1 + PadDY2, 0);
   TPad P10("P10", "", PadX0 + PadDX * 4, PadY0 + PadDY1, PadX0 + PadDX * 5, PadY0 + PadDY1 + PadDY2, 0);

   SetPad(P1);
   SetPad(P2);
   SetPad(P3);
   SetPad(P4);
   SetPad(P5);
   SetPad(P6);
   SetPad(P7);
   SetPad(P8);
   SetPad(P9);
   SetPad(P10);

   Canvas.cd();

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0, PadX0 + PadDX * 1 , PadY0, XMin,  XMax,  510, "GS");
   TGaxis AxisX2(PadX0 + PadDX * 1, PadY0, PadX0 + PadDX * 2 , PadY0, XMin,  XMax,  510, "GS");
   TGaxis AxisX3(PadX0 + PadDX * 2, PadY0, PadX0 + PadDX * 3 , PadY0, XMin,  XMax,  510, "GS");
   TGaxis AxisX4(PadX0 + PadDX * 3, PadY0, PadX0 + PadDX * 4 , PadY0, XMin,  XMax,  510, "GS");
   TGaxis AxisX5(PadX0 + PadDX * 4, PadY0, PadX0 + PadDX * 5 , PadY0, XMin,  XMax,  510, "GS");
   TGaxis AxisY1(PadX0, PadY0          , PadX0, PadY0 + PadDY1         , YMin1, YMax1, 505, "S");
   TGaxis AxisY2(PadX0, PadY0 + PadDY1 , PadX0, PadY0 + PadDY1 + PadDY2, YMin2, YMax2, 510, "S");

   SetAxis(AxisX1, true);
   SetAxis(AxisX2, true);
   SetAxis(AxisX3, true);
   SetAxis(AxisX4, true);
   SetAxis(AxisX5, true);
   SetAxis(AxisY1, false);
   SetAxis(AxisY2, false);

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 2.5, PadY0 * 0.30, "p_{T}^{jet} (GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.17, PadY0 + PadDY1 + PadDY2 * 0.5, "#frac{dN^{R}}{dp_{T}} #lower[0.45]{#font[82]{#scale[2.5]{/}}} #frac{dN^{R=1.0}}{dp_{T}}");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.30, PadY0 + PadDY1 * 0.5, "Pythia / Data");

   Latex.SetTextFont(62);
   Latex.SetTextSize(0.050);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDY1 + PadDY2 + PadY0 * 0.15, "CMS #scale[0.8]{#font[52]{Preliminary}}");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 5, PadY0 + PadDY1 + PadDY2 + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV, pp 27.4 pb^{-1}");

   TH1D *PPR2    = (TH1D *)File.Get("ak2PFJetAnalyzer_1");
   TH1D *PPR3    = (TH1D *)File.Get("ak3PFJetAnalyzer_1");
   TH1D *PPR4    = (TH1D *)File.Get("ak4PFJetAnalyzer_1");
   TH1D *PPR6    = (TH1D *)File.Get("ak6PFJetAnalyzer_1");
   TH1D *PPR8    = (TH1D *)File.Get("ak8PFJetAnalyzer_1");
   TH1D *PPR2Sys = (TH1D *)File.Get("ak2PFJetAnalyzer_2");
   TH1D *PPR3Sys = (TH1D *)File.Get("ak3PFJetAnalyzer_2");
   TH1D *PPR4Sys = (TH1D *)File.Get("ak4PFJetAnalyzer_2");
   TH1D *PPR6Sys = (TH1D *)File.Get("ak6PFJetAnalyzer_2");
   TH1D *PPR8Sys = (TH1D *)File.Get("ak8PFJetAnalyzer_2");
   TH1D *P6R2    = (TH1D *)File.Get("theoryCompPYT6_1");
   TH1D *P6R3    = (TH1D *)File.Get("theoryCompPYT6_2");
   TH1D *P6R4    = (TH1D *)File.Get("theoryCompPYT6_3");
   TH1D *P6R6    = (TH1D *)File.Get("theoryCompPYT6_4");
   TH1D *P6R8    = (TH1D *)File.Get("theoryCompPYT6_5");
   TH1D *P8R2    = (TH1D *)File.Get("theoryCompPYT8_1");
   TH1D *P8R3    = (TH1D *)File.Get("theoryCompPYT8_2");
   TH1D *P8R4    = (TH1D *)File.Get("theoryCompPYT8_3");
   TH1D *P8R6    = (TH1D *)File.Get("theoryCompPYT8_4");
   TH1D *P8R8    = (TH1D *)File.Get("theoryCompPYT8_5");

   SetHistogram(PPR2, kBlack);   SetHistogram(PPR2Sys, kBlack);
   SetHistogram(PPR3, kBlack);   SetHistogram(PPR3Sys, kBlack);
   SetHistogram(PPR4, kBlack);   SetHistogram(PPR4Sys, kBlack);
   SetHistogram(PPR6, kBlack);   SetHistogram(PPR6Sys, kBlack);
   SetHistogram(PPR8, kBlack);   SetHistogram(PPR8Sys, kBlack);

   SetTheoryHistogram(P6R2, Color[0], false);   SetTheoryHistogram(P8R2, Color[1], false);
   SetTheoryHistogram(P6R3, Color[0], false);   SetTheoryHistogram(P8R3, Color[1], false);
   SetTheoryHistogram(P6R4, Color[0], false);   SetTheoryHistogram(P8R4, Color[1], false);
   SetTheoryHistogram(P6R6, Color[0], false);   SetTheoryHistogram(P8R6, Color[1], false);
   SetTheoryHistogram(P6R8, Color[0], false);   SetTheoryHistogram(P8R8, Color[1], false);

   TH1D *RP6R2 = (TH1D *)P6R2->Clone(); GetRatio(RP6R2, P6R2, PPR2); SetTheoryHistogram(RP6R2, Color[0], false);
   TH1D *RP6R3 = (TH1D *)P6R3->Clone(); GetRatio(RP6R3, P6R3, PPR3); SetTheoryHistogram(RP6R3, Color[0], false);
   TH1D *RP6R4 = (TH1D *)P6R4->Clone(); GetRatio(RP6R4, P6R4, PPR4); SetTheoryHistogram(RP6R4, Color[0], false);
   TH1D *RP6R6 = (TH1D *)P6R6->Clone(); GetRatio(RP6R6, P6R6, PPR6); SetTheoryHistogram(RP6R6, Color[0], false);
   TH1D *RP6R8 = (TH1D *)P6R8->Clone(); GetRatio(RP6R8, P6R8, PPR8); SetTheoryHistogram(RP6R8, Color[0], false);
   TH1D *RP8R2 = (TH1D *)P8R2->Clone(); GetRatio(RP8R2, P8R2, PPR2); SetTheoryHistogram(RP8R2, Color[1], false);
   TH1D *RP8R3 = (TH1D *)P8R3->Clone(); GetRatio(RP8R3, P8R3, PPR3); SetTheoryHistogram(RP8R3, Color[1], false);
   TH1D *RP8R4 = (TH1D *)P8R4->Clone(); GetRatio(RP8R4, P8R4, PPR4); SetTheoryHistogram(RP8R4, Color[1], false);
   TH1D *RP8R6 = (TH1D *)P8R6->Clone(); GetRatio(RP8R6, P8R6, PPR6); SetTheoryHistogram(RP8R6, Color[1], false);
   TH1D *RP8R8 = (TH1D *)P8R8->Clone(); GetRatio(RP8R8, P8R8, PPR8); SetTheoryHistogram(RP8R8, Color[1], false);

   TLegend Legend(0.10, 0.05, 0.35, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.07);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(PPR2Sys, "R = 0.2", "plf");
   Legend.AddEntry(PPR3Sys, "R = 0.3", "plf");
   Legend.AddEntry(PPR4Sys, "R = 0.4", "plf");
   Legend.AddEntry(PPR6Sys, "R = 0.6", "plf");
   Legend.AddEntry(PPR8Sys, "R = 0.8", "plf");

   TH1D HPP, HP6, HP8;
   SetHistogram(&HPP, kBlack);
   SetTheoryHistogram(&HP6, Color[0], false);
   SetTheoryHistogram(&HP8, Color[1], false);

   TLegend Legend2(0.10, 0.05, 0.45, 0.47);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.07);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry(&HPP, "Data", "plf");
   Legend2.AddEntry(&HP6, "#scale[0.8]{PYTHIA}6 (tune Z2)", "l");
   Legend2.AddEntry(&HP8, "#scale[0.8]{PYTHIA}8 (tune CUETP8M1)", "l");
   Legend2.AddEntry("", "", "");
   Legend2.AddEntry("", "", "");

   TGraph G;
   G.SetPoint(0, XMin, 1);
   G.SetPoint(1, XMax, 1);
   G.SetLineStyle(kDotted);
   
   P1.cd();
   HWorld1.Draw("axis");
   RP6R2->Draw("same C hist");
   RP8R2->Draw("same C hist");
   G.Draw("l");
   P2.cd();
   HWorld1.Draw("axis");
   RP6R3->Draw("same C hist");
   RP8R3->Draw("same C hist");
   G.Draw("l");
   P3.cd();
   HWorld1.Draw("axis");
   RP6R4->Draw("same C hist");
   RP8R4->Draw("same C hist");
   G.Draw("l");
   P4.cd();
   HWorld1.Draw("axis");
   RP6R6->Draw("same C hist");
   RP8R6->Draw("same C hist");
   G.Draw("l");
   P5.cd();
   HWorld1.Draw("axis");
   RP6R8->Draw("same C hist");
   RP8R8->Draw("same C hist");
   G.Draw("l");
   P6.cd();
   HWorld2.Draw("axis");
   P6R2->Draw("same C hist");
   P8R2->Draw("same C hist");
   PPR2Sys->Draw("same e2");
   PPR2->Draw("same");
   P7.cd();
   HWorld2.Draw("axis");
   P6R3->Draw("same C hist");
   P8R3->Draw("same C hist");
   PPR3Sys->Draw("same e2");
   PPR3->Draw("same");
   P8.cd();
   HWorld2.Draw("axis");
   P6R4->Draw("same C hist");
   P8R4->Draw("same C hist");
   PPR4Sys->Draw("same e2");
   PPR4->Draw("same");
   P9.cd();
   HWorld2.Draw("axis");
   P6R6->Draw("same C hist");
   P8R6->Draw("same C hist");
   PPR6Sys->Draw("same e2");
   PPR6->Draw("same");
   P10.cd();
   HWorld2.Draw("axis");
   P6R8->Draw("same C hist");
   P8R8->Draw("same C hist");
   PPR8Sys->Draw("same e2");
   PPR8->Draw("same");
   Legend2.Draw();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.07);
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.12, 0.15, "|#eta_{jet}| < 2.0");

   Canvas.cd();

   double PTX = 0.250 / 5;
   double PTY = 0.070;
   TPaveText PT2(PadX0 + PadDX * 0.5 - PTX * 0.5, PadY0 + PadDY1 * 1 - PTY * 0.5, PadX0 + PadDX * 0.5 + PTX * 0.5, PadY0 + PadDY1 * 1 + PTY * 0.5);
   TPaveText PT3(PadX0 + PadDX * 1.5 - PTX * 0.5, PadY0 + PadDY1 * 1 - PTY * 0.5, PadX0 + PadDX * 1.5 + PTX * 0.5, PadY0 + PadDY1 * 1 + PTY * 0.5);
   TPaveText PT4(PadX0 + PadDX * 2.5 - PTX * 0.5, PadY0 + PadDY1 * 1 - PTY * 0.5, PadX0 + PadDX * 2.5 + PTX * 0.5, PadY0 + PadDY1 * 1 + PTY * 0.5);
   TPaveText PT6(PadX0 + PadDX * 3.5 - PTX * 0.5, PadY0 + PadDY1 * 1 - PTY * 0.5, PadX0 + PadDX * 3.5 + PTX * 0.5, PadY0 + PadDY1 * 1 + PTY * 0.5);
   TPaveText PT8(PadX0 + PadDX * 4.5 - PTX * 0.5, PadY0 + PadDY1 * 1 - PTY * 0.5, PadX0 + PadDX * 4.5 + PTX * 0.5, PadY0 + PadDY1 * 1 + PTY * 0.5);

   PT2.AddText("R = 0.2");
   PT3.AddText("R = 0.3");
   PT4.AddText("R = 0.4");
   PT6.AddText("R = 0.6");
   PT8.AddText("R = 0.8");

   PT2.SetFillColor(kWhite);
   PT2.SetBorderSize(1);
   PT2.SetTextFont(42);
   PT2.SetTextSize(0.035);
   PT3.SetFillColor(kWhite);
   PT3.SetBorderSize(1);
   PT3.SetTextFont(42);
   PT3.SetTextSize(0.035);
   PT4.SetFillColor(kWhite);
   PT4.SetBorderSize(1);
   PT4.SetTextFont(42);
   PT4.SetTextSize(0.035);
   PT6.SetFillColor(kWhite);
   PT6.SetBorderSize(1);
   PT6.SetTextFont(42);
   PT6.SetTextSize(0.035);
   PT8.SetFillColor(kWhite);
   PT8.SetBorderSize(1);
   PT8.SetTextFont(42);
   PT8.SetTextSize(0.035);

   PT2.Draw("same");
   PT3.Draw("same");
   PT4.Draw("same");
   PT6.Draw("same");
   PT8.Draw("same");

   string OutputBase = "SpectraRatio";

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

void SetAxis(TGaxis &A, bool X)
{
   A.SetLabelFont(42);
   A.SetLabelSize(0.040);
   A.SetMaxDigits(6);
   if(X == true)
   {
      A.SetMoreLogLabels();
      A.SetNoExponent();
      // A.SetLabelOffset(-0.005);
   }
   // else
   //    A.SetLabelOffset(-0.0001);
   A.SetTickSize(0);
   A.SetTickLength(0);
   A.Draw();
}

void GetGraph(string FileName, TGraphAsymmErrors &G, int R, int C, double Shift, bool Sys)
{
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
}

void SetHistogram(TH1D *H, int Color)
{
   H->SetLineColor(Color);
   H->SetFillColorAlpha(Color, 0.25);
   H->SetMarkerColor(Color);
   H->SetMarkerStyle(20);
   H->SetMarkerSize(2.0);
   H->SetLineWidth(2.0);
}

void SetTheoryHistogram(TH1D *H, int Color, bool P8)
{
   H->SetLineColor(Color);
   H->SetMarkerColor(Color);
   H->SetMarkerSize(1.5);
   H->SetLineWidth(2.0);
   if(P8 == true)
      H->SetLineStyle(kDashed);
   else
      H->SetLineStyle(kSolid);
}

void GetRatio(TH1D *H, TH1D *H1, TH1D *H2)
{
   for(int i = 1; i <= H1->GetNbinsX(); i++)
   {
      double Y1 = H1->GetBinContent(i);
      double Y2 = H2->GetBinContent(i);
      H->SetBinContent(i, Y1 / Y2);
   }
}
