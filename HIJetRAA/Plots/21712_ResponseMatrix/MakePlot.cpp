#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
void GetHistogram(TH2D &H, bool IsPP, int R, string Suffix = "General");
void SetPad(TPad &P);
void SetAxis(TGaxis &A);

int main(int argc, char *argv[])
{
   SetThesisStyle();

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

   double XMin = 200;
   double XMax = 1000;
   double YMin = 100;
   double YMax = 1000;

   int XBin = 6;
   int YBin = 7;
   double XBins[] = {200, 300, 400, 500, 630, 800, 1000};
   double YBins[] = {100, 200, 300, 400, 500, 630, 800, 1000};

   string OutputBase = "Response";

   TH2D HPPR02("HPPR02", "", XBin, XBins, YBin, YBins);
   TH2D HPPR10("HPPR10", "", XBin, XBins, YBin, YBins);
   TH2D HPbPbR02("HPbPbR02", "", XBin, XBins, YBin, YBins);
   TH2D HPbPbR10("HPbPbR10", "", XBin, XBins, YBin, YBins);

   string Suffix = "General";
   GetHistogram(HPbPbR02, false, 2,  Suffix);
   GetHistogram(HPbPbR10, false, 10, Suffix);
   GetHistogram(HPPR02,   true,  2,  Suffix);
   GetHistogram(HPPR10,   true,  10, Suffix);

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

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
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin, YMax, 510, "G");
   TGaxis AxisY2(PadX0 + PadDX * 0, PadY0 + PadDY * 1, PadX0 + PadDX * 0, PadY0 + PadDY * 2, YMin, YMax, 510, "G");

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
   Latex.DrawLatex(PadX0 + PadDX * 1.0, PadY0 * 0.30, "Generated Jet p_{T} (GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.20, PadY0 + PadDY * 1.0, "Reconstructed Jet p_{T} (GeV)");

   Latex.SetTextFont(62);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * 2 + PadY0 * 0.15, "CMS #font[52]{Simulation}");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.030);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 2, PadY0 + PadDY * 2 + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV");
   
   double Max = 0.01;
   Max = max(Max, HPPR02.GetMaximum());
   Max = max(Max, HPPR10.GetMaximum());
   Max = max(Max, HPbPbR02.GetMaximum());
   Max = max(Max, HPbPbR10.GetMaximum());

   HWorld.SetMaximum(Max);
   HWorld.SetMinimum(Max / 1000);
   
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.07);
   Latex.SetTextAngle(0);

   P1.cd();
   HWorld.Draw("axis");
   HPPR02.Draw("col same");
   HWorld.Draw("axis same");
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.05, 0.95, "Pythia");
   Latex.DrawLatex(0.05, 0.86, "R = 0.2");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.95, 0.06, "|#eta_{jet}| < 2.0");
   P2.cd();
   HWorld.Draw("axis");
   HPbPbR02.Draw("col same");
   HWorld.Draw("axis same");
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.05, 0.95, "Pythia+Hydjet");
   Latex.DrawLatex(0.05, 0.86, "R = 0.2");
   P3.cd();
   HWorld.Draw("axis");
   HPPR10.Draw("col same");
   HWorld.Draw("axis same");
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.05, 0.95, "Pythia");
   Latex.DrawLatex(0.05, 0.86, "R = 1.0");
   P4.cd();
   HWorld.Draw("axis");
   HPbPbR10.Draw("col same");
   HWorld.Draw("axis same");
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.05, 0.95, "Pythia+Hydjet");
   Latex.DrawLatex(0.05, 0.86, "R = 1.0");

   Canvas.SaveAs((OutputBase + ".pdf").c_str());
   Canvas.SaveAs((OutputBase + ".png").c_str());
   Canvas.SaveAs((OutputBase + ".C").c_str());

   return 0;
}

void GetHistogram(TH2D &H, bool IsPP, int R, string Suffix)
{
   string FileName = "Matrices/";
   if(IsPP == true)    FileName = FileName + "PPMC";
   if(IsPP == false)   FileName = FileName + "PbPbMC";
   FileName = FileName + "_FracNEntries1p00_JetResponse_20190830_";
   if(IsPP == true && R == 2)     FileName = FileName + "183201";
   if(IsPP == true && R == 3)     FileName = FileName + "183205";
   if(IsPP == true && R == 4)     FileName = FileName + "183209";
   if(IsPP == true && R == 6)     FileName = FileName + "183213";
   if(IsPP == true && R == 8)     FileName = FileName + "183217";
   if(IsPP == true && R == 10)    FileName = FileName + "183221";
   if(IsPP == false && R == 2)    FileName = FileName + "183203";
   if(IsPP == false && R == 3)    FileName = FileName + "183207";
   if(IsPP == false && R == 4)    FileName = FileName + "183211";
   if(IsPP == false && R == 6)    FileName = FileName + "183215";
   if(IsPP == false && R == 8)    FileName = FileName + "183219";
   if(IsPP == false && R == 10)   FileName = FileName + "183223";
   FileName = FileName + ".root";

   string FolderName = "";
   if(IsPP == true)    FolderName = "ak" + to_string(R) + "PFJetAnalyzer";
   if(IsPP == false)   FolderName = "akCs" + to_string(R) + "PU3PFFlowJetAnalyzer";

   string HistogramName = "response_" + FolderName;
   if(IsPP == false)   HistogramName = HistogramName + "_PbPb_Cent0to10";
   if(IsPP == true)    HistogramName = HistogramName + "_PP_Cent50to90";
   HistogramName = HistogramName + "_LightMUAndCHID_ResponseMod0p10_AbsEta0p0to2p0_" + Suffix + "_h";

   TFile File(FileName.c_str());

   TH1D HNorm("HNorm", "", 150, 0, 1500);
   TH2D HAll("HAll", "", 150, 0, 1500, 150, 0, 1500);

   TH2D *Histogram = (TH2D *)File.Get((FolderName + "/" + HistogramName).c_str());

   for(int i = 1; i <= HNorm.GetNbinsX(); i++)
   {
      double Gen = HNorm.GetXaxis()->GetBinCenter(i);
      int by = Histogram->GetYaxis()->FindBin(Gen);

      double Total = 0;
      for(int j = 0; j <= Histogram->GetNbinsX() + 1; j++)
         Total = Total + Histogram->GetBinContent(j, by);
      if(Total == 0)
         Total = 1;

      HNorm.SetBinContent(i, Total);
   }

   for(int i = 1; i <= HAll.GetNbinsX(); i++)
   {
      for(int j = 1; j <= HAll.GetNbinsY(); j++)
      {
         double Gen = HAll.GetXaxis()->GetBinCenter(i);
         double Reco = HAll.GetYaxis()->GetBinCenter(j);

         int bx = Histogram->GetXaxis()->FindBin(Reco);
         int by = Histogram->GetYaxis()->FindBin(Gen);
         int b = Histogram->GetBin(bx, by);

         double BinSize = Histogram->GetXaxis()->GetBinUpEdge(bx) - Histogram->GetXaxis()->GetBinLowEdge(bx);

         double Norm = HNorm.GetBinContent(HNorm.GetXaxis()->FindBin(Gen));
         // Norm = 1;

         HAll.SetBinContent(i, j, Histogram->GetBinContent(b) / BinSize / Norm);
      }
   }

   H.Reset();
   for(int i = 1; i <= HAll.GetNbinsX(); i++)
   {
      for(int j = 1; j <= HAll.GetNbinsY(); j++)
      {
         double x = HAll.GetXaxis()->GetBinCenter(i);
         double y = HAll.GetYaxis()->GetBinCenter(j);
         double xwidth = HAll.GetXaxis()->GetBinUpEdge(i) - HAll.GetXaxis()->GetBinLowEdge(i);
         double ywidth = HAll.GetYaxis()->GetBinUpEdge(j) - HAll.GetYaxis()->GetBinLowEdge(j);
         H.Fill(x, y, HAll.GetBinContent(i, j) * xwidth * ywidth);
      }
   }
   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      for(int j = 1; j <= H.GetNbinsY(); j++)
      {
         double xwidth = H.GetXaxis()->GetBinUpEdge(i) - H.GetXaxis()->GetBinLowEdge(i);
         double ywidth = H.GetYaxis()->GetBinUpEdge(j) - H.GetYaxis()->GetBinLowEdge(j);
         H.SetBinContent(i, j, H.GetBinContent(i, j) / xwidth / ywidth);
      }
   }

   File.Close();

   H.SetStats(0);
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

void SetAxis(TGaxis &A)
{
   A.SetLabelFont(42);
   A.SetLabelSize(0.030);
   A.SetMaxDigits(6);
   A.SetMoreLogLabels();
   A.SetNoExponent();
   A.Draw();
}

