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
#include "TPaveText.h"
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

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
void SetHistogram(TH1F *H, int Color);
void DrawLumiTAA(double Lumi, double TAA[4], double XMin, double XMax);

int main(int argc, char *argv[])
{
   int Color[6] = {-1, -1, -1, -1, -1, -1};
   Color[0] = TColor::GetColor("#E74C3C");
   Color[1] = TColor::GetColor("#3498DB");
   Color[2] = TColor::GetColor("#F1C40F");
   Color[3] = TColor::GetColor("#2ECC71");
   Color[4] = TColor::GetColor("#7F7F7F");
   Color[5] = kMagenta;

   CommandLine CL(argc, argv);

   // Preamble: sizing
   int PanelSize = 500;
   int PaddingWidthL = 100;
   int PaddingWidthR = 50;
   int PaddingHeight = 100;
   int CanvasWidth = PanelSize * 2 + PaddingWidthL + PaddingWidthR;
   int CanvasHeight = PanelSize * 2 + PaddingHeight * 2;

   double PadX0 = (double)PaddingWidthL / CanvasWidth;
   double PadY0 = (double)PaddingHeight / CanvasHeight;
   double PadDX = (double)PanelSize / CanvasWidth;
   double PadDY = (double)PanelSize / CanvasHeight;

   double XMin = 97;
   double XMax = 700;
   double YMin1 = 0.851;
   double YMax1 = 1.149;
   double YMin2 = 0.00;
   double YMax2 = 0.49;

   string File = "RAA_Smooth.root";

   // Start declaring canvas, pad, axis, and axis title (as TLatex)
   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld1("HWorld1", ";;", 100, XMin, XMax, 100, YMin1, YMax1);
   TH2D HWorld2("HWorld2", ";;", 100, XMin, XMax, 100, YMin2, YMax2);
   HWorld1.SetStats(0);
   HWorld2.SetStats(0);

   HWorld1.GetYaxis()->SetNdivisions(505);
   HWorld2.GetYaxis()->SetNdivisions(505);

   TPad P1("P1", "", PadX0 + PadDX * 0, PadY0 + PadDY * 1, PadX0 + PadDX * 1, PadY0 + PadDY * 2, 0);
   TPad P2("P2", "", PadX0 + PadDX * 1, PadY0 + PadDY * 1, PadX0 + PadDX * 2, PadY0 + PadDY * 2, 0);
   TPad P3("P3", "", PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 1, 0);
   TPad P4("P4", "", PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 1, 0);
   
   SetPad(P1);
   SetPad(P2);
   SetPad(P3);
   SetPad(P4);
  
   Canvas.cd();

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 510, "G");
   TGaxis AxisX2(PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 0, XMin, XMax, 510, "G");
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin2, YMax2, 505, "");
   TGaxis AxisY2(PadX0 + PadDX * 0, PadY0 + PadDY * 1, PadX0 + PadDX * 0, PadY0 + PadDY * 2, YMin1, YMax1, 505, "");

   SetAxis(AxisX1);
   SetAxis(AxisX2);
   SetAxis(AxisY1);
   SetAxis(AxisY2);

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 1.0, PadY0 * 0.25, "Generated p_{T}^{jet} (GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.20, PadY0 + PadDY * 0.5, "#sigma/#mu");
   Latex.DrawLatex(PadX0 * 0.20, PadY0 + PadDY * 1.5, "#mu");

   Latex.SetTextFont(62);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * 2 + PadY0 * 0.15, "CMS #scale[0.8]{#font[52]{Simulation}}");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 2, PadY0 + PadDY * 2 + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV");

   double PTX = 0.120;
   double PTY = 0.045;
   TPaveText PT4(PadX0 + PadDX * 0.5 - PTX * 0.5, PadY0 + PadDY * 1 - PTY * 0.5, PadX0 + PadDX * 0.5 + PTX * 0.5, PadY0 + PadDY * 1 + PTY * 0.5);
   TPaveText PT8(PadX0 + PadDX * 1.5 - PTX * 0.5, PadY0 + PadDY * 1 - PTY * 0.5, PadX0 + PadDX * 1.5 + PTX * 0.5, PadY0 + PadDY * 1 + PTY * 0.5);

   PT4.AddText("R = 0.4");
   PT8.AddText("R = 0.8");

   PT4.SetFillColor(kWhite);
   PT4.SetBorderSize(1);
   PT4.SetTextFont(42);
   PT4.SetTextSize(0.035);
   PT8.SetFillColor(kWhite);
   PT8.SetBorderSize(1);
   PT8.SetTextFont(42);
   PT8.SetTextSize(0.035);

   TFile F4("AK4.root");
   TFile F8("AK8.root");

   TH1F *HMuR4C0 = (TH1F *)F4.Get("Mu_Cent0to10");
   TH1F *HMuR4C1 = (TH1F *)F4.Get("Mu_Cent10to30");
   TH1F *HMuR4C2 = (TH1F *)F4.Get("Mu_Cent30to50");
   TH1F *HMuR4C3 = (TH1F *)F4.Get("Mu_Cent50to70");
   TH1F *HMuR4C4 = (TH1F *)F4.Get("Mu_Cent70to100");
   TH1F *HMuR8C0 = (TH1F *)F8.Get("Mu_Cent0to10");
   TH1F *HMuR8C1 = (TH1F *)F8.Get("Mu_Cent10to30");
   TH1F *HMuR8C2 = (TH1F *)F8.Get("Mu_Cent30to50");
   TH1F *HMuR8C3 = (TH1F *)F8.Get("Mu_Cent50to70");
   TH1F *HMuR8C4 = (TH1F *)F8.Get("Mu_Cent70to100");
   TH1F *HSigmaMuR4C0 = (TH1F *)F4.Get("SigmaMu_Cent0to10");
   TH1F *HSigmaMuR4C1 = (TH1F *)F4.Get("SigmaMu_Cent10to30");
   TH1F *HSigmaMuR4C2 = (TH1F *)F4.Get("SigmaMu_Cent30to50");
   TH1F *HSigmaMuR4C3 = (TH1F *)F4.Get("SigmaMu_Cent50to70");
   TH1F *HSigmaMuR4C4 = (TH1F *)F4.Get("SigmaMu_Cent70to100");
   TH1F *HSigmaMuR8C0 = (TH1F *)F8.Get("SigmaMu_Cent0to10");
   TH1F *HSigmaMuR8C1 = (TH1F *)F8.Get("SigmaMu_Cent10to30");
   TH1F *HSigmaMuR8C2 = (TH1F *)F8.Get("SigmaMu_Cent30to50");
   TH1F *HSigmaMuR8C3 = (TH1F *)F8.Get("SigmaMu_Cent50to70");
   TH1F *HSigmaMuR8C4 = (TH1F *)F8.Get("SigmaMu_Cent70to100");

   SetHistogram(HMuR4C0, Color[0]);
   SetHistogram(HMuR4C1, Color[1]);
   SetHistogram(HMuR4C2, Color[2]);
   SetHistogram(HMuR4C3, Color[3]);
   SetHistogram(HMuR4C4, Color[4]);
   SetHistogram(HMuR8C0, Color[0]);
   SetHistogram(HMuR8C1, Color[1]);
   SetHistogram(HMuR8C2, Color[2]);
   SetHistogram(HMuR8C3, Color[3]);
   SetHistogram(HMuR8C4, Color[4]);
   SetHistogram(HSigmaMuR4C0, Color[0]);
   SetHistogram(HSigmaMuR4C1, Color[1]);
   SetHistogram(HSigmaMuR4C2, Color[2]);
   SetHistogram(HSigmaMuR4C3, Color[3]);
   SetHistogram(HSigmaMuR4C4, Color[4]);
   SetHistogram(HSigmaMuR8C0, Color[0]);
   SetHistogram(HSigmaMuR8C1, Color[1]);
   SetHistogram(HSigmaMuR8C2, Color[2]);
   SetHistogram(HSigmaMuR8C3, Color[3]);
   SetHistogram(HSigmaMuR8C4, Color[4]);

   TGraph GLine;
   GLine.SetPoint(0, XMin, 1 + 0.02);
   GLine.SetPoint(1, XMax, 1 + 0.02);
   GLine.SetPoint(2, XMax, 1 - 0.02);
   GLine.SetPoint(3, XMin, 1 - 0.02);
   GLine.SetLineStyle(kDashed);

   TLegend Legend(0.5, 0.35, 0.9, 0.8);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.07);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(HMuR4C0, "0-10%", "pl");
   Legend.AddEntry(HMuR4C1, "10-30%", "pl");
   Legend.AddEntry(HMuR4C2, "30-50%", "pl");
   Legend.AddEntry(HMuR4C3, "50-70%", "pl");
   Legend.AddEntry(HMuR4C4, "70-100%", "pl");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.07);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld1.Draw("axis");
   GLine.Draw("l");
   HMuR4C0->Draw("same");
   HMuR4C1->Draw("same");
   HMuR4C2->Draw("same");
   HMuR4C3->Draw("same");
   HMuR4C4->Draw("same");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.8, "anti-k_{T}, |#eta_{jet}| < 2");
   Latex.DrawLatex(0.08, 0.9, "Pythia8+Hydjet");
   P2.cd();
   HWorld1.Draw("axis");
   GLine.Draw("l");
   HMuR8C0->Draw("same");
   HMuR8C1->Draw("same");
   HMuR8C2->Draw("same");
   HMuR8C3->Draw("same");
   HMuR8C4->Draw("same");
   P3.cd();
   HWorld2.Draw("axis");
   HSigmaMuR4C0->Draw("same");
   HSigmaMuR4C1->Draw("same");
   HSigmaMuR4C2->Draw("same");
   HSigmaMuR4C3->Draw("same");
   HSigmaMuR4C4->Draw("same");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.55, 0.83, "Centrality");
   Legend.Draw();
   P4.cd();
   HWorld2.Draw("axis");
   HSigmaMuR8C0->Draw("same");
   HSigmaMuR8C1->Draw("same");
   HSigmaMuR8C2->Draw("same");
   HSigmaMuR8C3->Draw("same");
   HSigmaMuR8C4->Draw("same");

   Canvas.cd();

   PT4.Draw();
   PT8.Draw();

   string OutputBase = "PlotJet";

   Canvas.SaveAs((OutputBase + ".pdf").c_str());
   Canvas.SaveAs((OutputBase + ".png").c_str());
   Canvas.SaveAs((OutputBase + ".C").c_str());

   F4.Close();
   F8.Close();

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

void SetHistogram(TH1F *H, int Color)
{
   if(H == nullptr)
      return;

   H->SetLineColor(Color);
   H->SetMarkerColor(Color);
   H->SetLineWidth(2);
   H->SetMarkerStyle(20);
}

