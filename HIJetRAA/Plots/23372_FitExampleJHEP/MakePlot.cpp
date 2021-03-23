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
#include "TF1.h"
#include "TBox.h"
#include "TKey.h"
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
void SetFunction(TF1 &F, int Color, int Style);

int main(int argc, char *argv[])
{
   int Color[6] = {-1, -1, -1, -1, -1, -1};
   Color[0] = TColor::GetColor("#E74C3C");
   Color[1] = TColor::GetColor("#3498DB");
   // Color[2] = TColor::GetColor("#F1C40F");
   // Color[3] = TColor::GetColor("#2ECC71");
   Color[2] = TColor::GetColor("#D1A40A");
   Color[3] = TColor::GetColor("#1EAC61");
   Color[4] = TColor::GetColor("#7F7F7F");
   Color[5] = kMagenta;

   int Style[6] = {kSolid, kSolid, kSolid, kSolid, kSolid, kSolid};

   CommandLine CL(argc, argv);

   string Run   = CL.Get("Run", "None");
   string Lumi  = CL.Get("Lumi", "None");
   string Event = CL.Get("Event", "None");

   // Preamble: sizing
   int PanelSize = 250;
   int PaddingWidthL = 50;
   int PaddingWidthR = 25;
   int PaddingHeight = 50;
   int PaddingSpacing = 20;
   int CanvasWidth = PanelSize * 2 + PaddingWidthL + PaddingWidthR + PaddingSpacing;
   int CanvasHeight = PanelSize * 1 + PaddingHeight * 2;

   double PadX0 = (double)PaddingWidthL / CanvasWidth;
   double PadY0 = (double)PaddingHeight / CanvasHeight;
   double PadDX = (double)PanelSize / CanvasWidth;
   double PadDY = (double)PanelSize / CanvasHeight;
   double PadSX = (double)PaddingSpacing / CanvasWidth;

   double XMin = -M_PI;
   double XMax = M_PI;
   double YMin = 0;
   double YMax = 100;

   int Count = 0;

   string FileName = "AllPlots.root";

   TFile File(FileName.c_str());
   TList *List = File.GetListOfKeys();
   TIter next(List);
   
   TKey *object = nullptr;
   while((object = (TKey *)next()))
   {
      string Name = object->GetName();
      vector<string> Names = CommandLine::Parse(Name, '_');

      if(Names[0] != "phiFit")
         continue;

      if(Run != "None" && Names[1] != "Run" + Run)
         continue;
      if(Lumi != "None" && Names[2] != "Lumi" + Lumi)
         continue;
      if(Event != "None" && Names[3] != "Evt" + Event)
         continue;

      string Tag = Names[1] + "_" + Names[2] + "_" + Names[3] + "_" + Names[4];

      TH1F *H1 = (TH1F *)File.Get(("phiFit_" + Tag).c_str());
      TH1F *H2 = (TH1F *)File.Get(("phiFitSide_" + Tag).c_str());
      if(H1 == nullptr || H2 == nullptr)
         continue;

      int hiBin = atoi(Names[4].substr(5).c_str());
      cout << hiBin << endl;

      SetHistogram(H1, kBlack);
      SetHistogram(H2, kBlack);

      double Max1 = H1->GetMaximum();
      double Max2 = H2->GetMaximum();
      double Mean1 = H1->Integral() / H1->GetNbinsX();
      double Mean2 = H2->Integral() / H2->GetNbinsX();

      TF1 F1  ("F1",   "[0]*(1+[1]*cos(2*x+[2])+[3]*cos(3*x+[4]))", -M_PI, M_PI);
      TF1 F1V2("F1V2", "[0]*(1+[1]*cos(2*x+[2])+[3]*cos(3*x+[4]))", -M_PI, M_PI);
      TF1 F1V3("F1V3", "[0]*(1+[1]*cos(2*x+[2])+[3]*cos(3*x+[4]))", -M_PI, M_PI);
      TF1 F2  ("F2",   "[0]*(1+[1]*cos(2*x+[2])+[3]*cos(3*x+[4]))", -M_PI, M_PI);
      TF1 F2V2("F2V2", "[0]*(1+[1]*cos(2*x+[2])+[3]*cos(3*x+[4]))", -M_PI, M_PI);
      TF1 F2V3("F2V3", "[0]*(1+[1]*cos(2*x+[2])+[3]*cos(3*x+[4]))", -M_PI, M_PI);

      H1->Fit(&F1, "N");
      F1V2.SetParameters(F1.GetParameter(0), F1.GetParameter(1), F1.GetParameter(2), 0, 0);
      F1V3.SetParameters(F1.GetParameter(0), 0, 0, F1.GetParameter(3), F1.GetParameter(4));
      F2.SetParameters(Mean2, F1.GetParameter(1), F1.GetParameter(2), F1.GetParameter(3), F1.GetParameter(4));
      F2V2.SetParameters(Mean2, F1.GetParameter(1), F1.GetParameter(2), 0, 0);
      F2V3.SetParameters(Mean2, 0, 0, F1.GetParameter(3), F1.GetParameter(4));

      SetFunction(F1,   Color[0], Style[0]);
      SetFunction(F1V2, Color[1], Style[1]);
      SetFunction(F1V3, Color[2], Style[2]);
      SetFunction(F2,   Color[0], Style[0]);
      SetFunction(F2V2, Color[1], Style[1]);
      SetFunction(F2V3, Color[2], Style[2]);

      cout << Max1 << " " << Max2 << " " << Mean1 << " " << Mean2 << endl;

      YMax = max(Mean1, Mean2) * 3.5;

      // Start declaring canvas, pad, axis, and axis title (as TLatex)
      TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

      TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
      HWorld.SetStats(0);

      TPad P1("P1", "", PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 1, 0);
      TPad P2("P2", "", PadX0 + PadDX * 1 + PadSX, PadY0 + PadDY * 0, PadX0 + PadDX * 2 + PadSX, PadY0 + PadDY * 1, 0);

      SetPad(P1);
      SetPad(P2);

      Canvas.cd();

      TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 510, "");
      TGaxis AxisX2(PadX0 + PadDX * 1 + PadSX, PadY0 + PadDY * 0, PadX0 + PadDX * 2 + PadSX, PadY0 + PadDY * 0, XMin, XMax, 510, "");
      TGaxis AxisY(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin, YMax, 510, "S");

      SetAxis(AxisX1);
      SetAxis(AxisX2);
      SetAxis(AxisY);

      TLatex Latex;
      Latex.SetNDC();

      Latex.SetTextFont(42);
      Latex.SetTextSize(0.070);
      Latex.SetTextAlign(22);
      Latex.SetTextAngle(0);
      Latex.DrawLatex(PadX0 + PadDX * 1.0 + PadSX * 0.5, PadY0 * 0.20, "PF Candidate #phi (radian)");

      Latex.SetTextFont(42);
      Latex.SetTextSize(0.070);
      Latex.SetTextAlign(22);
      Latex.SetTextAngle(90);
      Latex.DrawLatex(PadX0 * 0.20, PadY0 + PadDY * 0.5, "Counts");

      Latex.SetTextFont(62);
      Latex.SetTextSize(0.080);
      Latex.SetTextAlign(11);
      Latex.SetTextAngle(0);
      Latex.DrawLatex(PadX0, PadY0 + PadDY * 1 + PadY0 * 0.15, "CMS #scale[0.8]{#font[52]{ }}");

      Latex.SetTextFont(42);
      Latex.SetTextSize(0.060);
      Latex.SetTextAlign(31);
      Latex.SetTextAngle(0);
      Latex.DrawLatex(PadX0 + PadDX * 2 + PadSX, PadY0 + PadDY * 1 + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 2015");

      TLegend Legend(0.25, 0.48, 0.65, 0.82);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.07);
      Legend.SetFillStyle(0);
      Legend.SetBorderSize(0);
      Legend.AddEntry(H1, "PF Charged Hadron", "pl");
      Legend.AddEntry(&F1, "Total fit", "l");
      Legend.AddEntry(&F1V2, "v_{2} component + 1", "l");
      Legend.AddEntry(&F1V3, "v_{3} component + 1", "l");

      Latex.SetTextFont(42);
      Latex.SetTextSize(0.07);
      Latex.SetTextAlign(31);
      Latex.SetTextAngle(0);

      P1.cd();
      HWorld.Draw("axis");
      F1V2.Draw("same");
      F1V3.Draw("same");
      F1.Draw("same");
      H1->Draw("hist e1 p same");
      Latex.SetTextAlign(11);
      Latex.DrawLatex(0.08, 0.88, "#font[62]{|#eta| < 1}");
      Latex.DrawLatex(0.08, 0.78, "0.3 < p_{T} < 3.0 GeV");
      Latex.DrawLatex(0.08, 0.70, Form("Event centrality: %.1f%%-%.1f%%", hiBin * 0.5, (hiBin + 1) * 0.5));
      Latex.SetTextAlign(31);
      P2.cd();
      HWorld.Draw("axis");
      F2V2.Draw("same");
      F2V3.Draw("same");
      F2.Draw("same");
      H2->Draw("hist e1 p same");
      Legend.Draw();
      Latex.SetTextAlign(11);
      Latex.DrawLatex(0.08, 0.88, "#font[62]{1 < |#eta| < 2}");

      string OutputBase = "plots/PlotJet_" + Tag;

      Canvas.SaveAs((OutputBase + ".pdf").c_str());
      Canvas.SaveAs((OutputBase + ".png").c_str());
      Canvas.SaveAs((OutputBase + ".C").c_str());

      // if(Count > 5)
      //    break;
      Count = Count + 1;
   }

   return 0;
}

void SetPad(TPad &P)
{
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
   A.SetLabelSize(0.060);
   A.SetMaxDigits(6);
   A.SetMoreLogLabels();
   A.SetNoExponent();
   A.SetTickLength(0);
   A.Draw();
}

void SetHistogram(TH1F *H, int Color)
{
   if(H == nullptr)
      return;

   H->SetLineColor(Color);
   H->SetMarkerColor(Color);
   H->SetMarkerStyle(20);
   H->SetLineWidth(1);
}

void SetFunction(TF1 &F, int Color, int Style)
{
   F.SetLineWidth(2);
   F.SetLineColor(Color);
   F.SetLineStyle(Style);
}



