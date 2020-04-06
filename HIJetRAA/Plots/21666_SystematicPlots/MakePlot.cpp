#include <iostream>
#include <vector>
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

int Color[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
vector<TH1D *> GetSystematics(TFile &File, bool PP, int R, int C, int Grouping);
vector<TH1D *> DoGrouping(vector<TH1D *> &H, int Grouping);
void FormatHistograms(vector<TH1D *> &H);
void DrawAll(vector<TH1D *> &H);
void ScaleAll(vector<TH1D *> &H);
void QuadratureAdd(TH1D *H1, TH1D *H2);
void AppendTotal(vector<TH1D *> &H);

int main(int argc, char *argv[])
{
   // Preamble: sizing
   int PanelSize = 500;
   int PaddingWidth = 100;
   int PaddingHeight = 100;
   int CanvasWidth = PanelSize * 5 + PaddingWidth * 2;
   int CanvasHeight = PanelSize * 2 + PaddingHeight * 2;

   double PadX0 = (double)PaddingWidth / CanvasWidth;
   double PadY0 = (double)PaddingHeight / CanvasHeight;
   double PadDX = (double)PanelSize / CanvasWidth;
   double PadDY = (double)PanelSize / CanvasHeight;

   double XMin = 150;
   double XMax = 1500;
   double YMin = 0;
   double YMax = 33;

   string FileName = "SysSpectra_Smooth.root";
   TFile File(FileName.c_str());

   double Lumi = 0.023;
   double TAA[4] = {0.100719, 0.051233, 0.025341, 0.018646};
   
   int Grouping = 2;

   vector<string> Sys = {"JECMC", "JECData", "JECUE", "JERMC", "JERData", "Misrec.", "Prior1PowerPthat", "MatrixStat", "SVD", "PriorAdj", "Lumi", "TAA"};
   if(Grouping == 1)
      Sys = {"JEC", "Misrec.", "Unfolding", "Lumi/T_{AA}"};
   if(Grouping == 2)
      Sys = {"JEC", "JER", "Misrec.", "Unfolding", "Lumi/T_{AA}"};

   // Start declaring canvas, pad, axis, and axis title (as TLatex)
   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   TPad P1("P1", "", PadX0 + PadDX * 0, PadY0 + PadDY * 1, PadX0 + PadDX * 1, PadY0 + PadDY * 2, 0);
   TPad P2("P2", "", PadX0 + PadDX * 1, PadY0 + PadDY * 1, PadX0 + PadDX * 2, PadY0 + PadDY * 2, 0);
   TPad P3("P3", "", PadX0 + PadDX * 2, PadY0 + PadDY * 1, PadX0 + PadDX * 3, PadY0 + PadDY * 2, 0);
   TPad P4("P4", "", PadX0 + PadDX * 3, PadY0 + PadDY * 1, PadX0 + PadDX * 4, PadY0 + PadDY * 2, 0);
   TPad P5("P5", "", PadX0 + PadDX * 4, PadY0 + PadDY * 1, PadX0 + PadDX * 5, PadY0 + PadDY * 2, 0);
   TPad P6("P6", "", PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 1, 0);
   TPad P7("P7", "", PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 1, 0);
   TPad P8("P8", "", PadX0 + PadDX * 2, PadY0 + PadDY * 0, PadX0 + PadDX * 3, PadY0 + PadDY * 1, 0);
   TPad P9("P9", "", PadX0 + PadDX * 3, PadY0 + PadDY * 0, PadX0 + PadDX * 4, PadY0 + PadDY * 1, 0);
   TPad P10("P10", "", PadX0 + PadDX * 4, PadY0 + PadDY * 0, PadX0 + PadDX * 5, PadY0 + PadDY * 1, 0);
   
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

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 510, "GS");
   TGaxis AxisX2(PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 0, XMin, XMax, 510, "GS");
   TGaxis AxisX3(PadX0 + PadDX * 2, PadY0 + PadDY * 0, PadX0 + PadDX * 3, PadY0 + PadDY * 0, XMin, XMax, 510, "GS");
   TGaxis AxisX4(PadX0 + PadDX * 3, PadY0 + PadDY * 0, PadX0 + PadDX * 4, PadY0 + PadDY * 0, XMin, XMax, 510, "GS");
   TGaxis AxisX5(PadX0 + PadDX * 4, PadY0 + PadDY * 0, PadX0 + PadDX * 5, PadY0 + PadDY * 0, XMin, XMax, 510, "GS");
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin, YMax, 510, "S");
   TGaxis AxisY2(PadX0 + PadDX * 0, PadY0 + PadDY * 1, PadX0 + PadDX * 0, PadY0 + PadDY * 2, YMin, YMax, 510, "S");

   SetAxis(AxisX1);
   SetAxis(AxisX2);
   SetAxis(AxisX3);
   SetAxis(AxisX4);
   SetAxis(AxisX5);
   SetAxis(AxisY1);
   SetAxis(AxisY2);

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 2.5, PadY0 * 0.25, "p_{T}^{jet} (GeV)");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.20, PadY0 + PadDY, "Uncertainty (%)");

   Latex.SetTextFont(62);
   Latex.SetTextSize(0.050);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * 2 + PadY0 * 0.15, "CMS #scale[0.8]{#font[52]{Preliminary}}");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 5, PadY0 + PadDY * 2 + PadY0 * 0.20, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 404 #mub^{-1}, pp 27.4 pb^{-1}");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(270);
   Latex.DrawLatex(PadX0 + PadDX * 5 + PadX0 * 0.5, PadY0 + PadDY * 1.5, "R = 0.2");
   Latex.DrawLatex(PadX0 + PadDX * 5 + PadX0 * 0.5, PadY0 + PadDY * 0.5, "R = 1.0");

   vector<TH1D *> HPPR02 = GetSystematics(File, true , R02, C0, Grouping);
   vector<TH1D *> HC0R02 = GetSystematics(File, false, R02, C0, Grouping);
   vector<TH1D *> HC1R02 = GetSystematics(File, false, R02, C1, Grouping);
   vector<TH1D *> HC2R02 = GetSystematics(File, false, R02, C2, Grouping);
   vector<TH1D *> HC3R02 = GetSystematics(File, false, R02, C3, Grouping);
   vector<TH1D *> HPPR10 = GetSystematics(File, true,  R10, C0, Grouping);
   vector<TH1D *> HC0R10 = GetSystematics(File, false, R10, C0, Grouping);
   vector<TH1D *> HC1R10 = GetSystematics(File, false, R10, C1, Grouping);
   vector<TH1D *> HC2R10 = GetSystematics(File, false, R10, C2, Grouping);
   vector<TH1D *> HC3R10 = GetSystematics(File, false, R10, C3, Grouping);

   Sys.push_back("Total");
   AppendTotal(HPPR02);
   AppendTotal(HC0R02);
   AppendTotal(HC1R02);
   AppendTotal(HC2R02);
   AppendTotal(HC3R02);
   AppendTotal(HPPR10);
   AppendTotal(HC0R10);
   AppendTotal(HC1R10);
   AppendTotal(HC2R10);
   AppendTotal(HC3R10);

   ScaleAll(HPPR02);
   ScaleAll(HC0R02);
   ScaleAll(HC1R02);
   ScaleAll(HC2R02);
   ScaleAll(HC3R02);
   ScaleAll(HPPR10);
   ScaleAll(HC0R10);
   ScaleAll(HC1R10);
   ScaleAll(HC2R10);
   ScaleAll(HC3R10);

   FormatHistograms(HPPR02);
   FormatHistograms(HC0R02);
   FormatHistograms(HC1R02);
   FormatHistograms(HC2R02);
   FormatHistograms(HC3R02);
   FormatHistograms(HPPR10);
   FormatHistograms(HC0R10);
   FormatHistograms(HC1R10);
   FormatHistograms(HC2R10);
   FormatHistograms(HC3R10);

   TLegend Legend(0.08, 0.08, 0.48, 0.58);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.08);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   for(int i = 0; i < (int)HPPR02.size(); i++)
      Legend.AddEntry(HPPR02[i], Sys[i].c_str(), "l");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.08);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "pp");
   DrawAll(HPPR02);
   P2.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "PbPb 50-90%");
   DrawAll(HC3R02);
   P3.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "PbPb 30-50%");
   DrawAll(HC2R02);
   P4.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "PbPb 10-30%");
   DrawAll(HC1R02);
   P5.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "PbPb 0-10%");
   DrawAll(HC0R02);
   P6.cd();
   HWorld.Draw("axis");
   DrawAll(HPPR10);
   P7.cd();
   HWorld.Draw("axis");
   DrawAll(HC3R10);
   P8.cd();
   HWorld.Draw("axis");
   DrawAll(HC2R10);
   P9.cd();
   HWorld.Draw("axis");
   DrawAll(HC1R10);
   P10.cd();
   HWorld.Draw("axis");
   Legend.Draw();
   DrawAll(HC0R10);

   Canvas.SaveAs("PlotSystematics.pdf");
   Canvas.SaveAs("PlotSystematics.png");

   File.Close();

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
   A.SetTitleSize(0.040);
   A.SetMaxDigits(6);
   A.SetMoreLogLabels();
   A.SetNoExponent();
   A.SetTickLength(0);
   A.Draw();
}

vector<TH1D *> GetSystematics(TFile &File, bool PP, int R, int C, int Grouping)
{
   string Rs[] = {"2", "3", "4", "6", "8", "10"};
   string Cs[] = {"0to10", "10to30", "30to50", "50to90"};
   vector<string> Sys = {"JECMC", "JECData", "JECUE", "JERMC", "JERData", "Fake", "Prior1PowerPthat", "MatrixStat", "SVD", "PriorAdj", "Lumi", "TAA"};
   
   vector<TH1D *> RawResult;

   string Algorithm = "";
   if(PP == true)
      Algorithm = "ak" + Rs[R] + "PFJetAnalyzer";
   else
      Algorithm = "akCs" + Rs[R] + "PU3PFFlowJetAnalyzer";

   string Centrality = "Cent" + Cs[C];

   for(int i = 0; i < (int)Sys.size(); i++)
   {
      TH1D *H = (TH1D *)File.Get((Algorithm + "_" + Centrality + "_" + Sys[i]).c_str());
      RawResult.push_back(H);
   }

   return DoGrouping(RawResult, Grouping);
}

void DrawAll(vector<TH1D *> &H)
{
   for(TH1D *Item : H)
   {
      if(Item == nullptr)
         continue;
      Item->Draw("same hist ][");
   }
}

void FormatHistograms(vector<TH1D *> &H)
{
   if(Color[0] == -1)
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
      new TColor(Color[4], 0.5547, 0.2656, 0.6758);   //8E44AD
      Color[5] = kBlack;
      Color[6] = kBlack;
      Color[7] = kBlack;
      Color[8] = kBlack;
      Color[9] = kBlack;
      Color[10] = kBlack;
      Color[11] = kBlack;
   }

   for(int i = 0; i < (int)H.size(); i++)
   {
      H[i]->SetLineColor(Color[i]);
      H[i]->SetLineWidth(2);
   }
}

vector<TH1D *> DoGrouping(vector<TH1D *> &H, int Grouping)
{
   vector<TH1D *> Result;

   if(Grouping == 0)
   {
      for(auto item : H)
         Result.push_back((TH1D *)item->Clone());
   }
   if(Grouping == 1)
   {
      int N = 4;

      for(int i = 0; i < 4; i++)
      {
         Result.push_back((TH1D *)H[0]->Clone());
         Result[i]->Reset();
      }

      QuadratureAdd(Result[0], H[0]);
      QuadratureAdd(Result[0], H[1]);
      QuadratureAdd(Result[0], H[2]);
      QuadratureAdd(Result[0], H[3]);
      QuadratureAdd(Result[0], H[4]);
      QuadratureAdd(Result[1], H[5]);
      QuadratureAdd(Result[2], H[6]);
      QuadratureAdd(Result[2], H[7]);
      QuadratureAdd(Result[2], H[8]);
      QuadratureAdd(Result[2], H[9]);
      QuadratureAdd(Result[3], H[10]);
      QuadratureAdd(Result[3], H[11]);
   }
   if(Grouping == 2)
   {
      int N = 5;

      for(int i = 0; i < 5; i++)
      {
         Result.push_back((TH1D *)H[0]->Clone());
         Result[i]->Reset();
      }

      QuadratureAdd(Result[0], H[0]);
      QuadratureAdd(Result[0], H[1]);
      QuadratureAdd(Result[0], H[2]);
      QuadratureAdd(Result[1], H[3]);
      QuadratureAdd(Result[1], H[4]);
      QuadratureAdd(Result[2], H[5]);
      QuadratureAdd(Result[3], H[6]);
      QuadratureAdd(Result[3], H[7]);
      QuadratureAdd(Result[3], H[8]);
      QuadratureAdd(Result[3], H[9]);
      QuadratureAdd(Result[4], H[10]);
      QuadratureAdd(Result[4], H[11]);
   }

   return Result;
}

void ScaleAll(vector<TH1D *> &H)
{
   for(TH1D *I : H)
      I->Scale(100);
}

void QuadratureAdd(TH1D *H1, TH1D *H2)
{
   for(int i = 1; i <= H1->GetNbinsX(); i++)
   {
      double V1 = H1->GetBinContent(i);
      double V2 = H2->GetBinContent(i);
      H1->SetBinContent(i, sqrt(V1 * V1 + V2 * V2));
   }
}

void AppendTotal(vector<TH1D *> &H)
{
   TH1D *Total = (TH1D *)H[0]->Clone();

   for(int i = 1; i < (int)H.size(); i++)
      QuadratureAdd(Total, H[i]);

   H.push_back(Total);
}

