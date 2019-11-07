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

#define PT0 0
#define PT1 1
#define PT2 2
#define PT3 3
#define PT4 4

#define C0 0
#define C1 1
#define C2 2
#define C3 3

int Color[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
vector<TH1D *> GetSystematics(TFile &File, int PT, int C, int Grouping);
vector<TH1D *> DoGrouping(vector<TH1D *> &H, int Grouping);
void FormatHistograms(vector<TH1D *> &H);
void DrawAll(vector<TH1D *> &H);
void ScaleAll(vector<TH1D *> &H);
void QuadratureAdd(TH1D *H1, TH1D *H2);
void AppendTotal(vector<TH1D *> &H);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   int C = CL.GetInt("C", 0);

   string Cs[] = {"0 - 10%", "10 - 30%", "30 - 50%", "50 - 90%"};

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

   double XMin = 0.1;
   double XMax = 1.1;
   double YMin = 0;
   double YMax = 16.5;

   string FileName = "SysRRAA_Smooth.root";
   TFile File(FileName.c_str());

   double Lumi = 0.023;
   double TAA[4] = {0.100719, 0.051233, 0.025341, 0.018646};
   
   int Grouping = 2;

   vector<string> Sys = {"JECMC", "JECData", "JECUE", "JERMC", "JERData", "Fake", "Prior1PowerPthat", "MatrixStat", "SVD", "PriorAdj", "Lumi", "TAA"};
   if(Grouping == 1)
      Sys = {"JERC", "Fake", "Unfolding", "Lumi/T_{AA}"};
   if(Grouping == 2)
      Sys = {"JEC", "JER", "Fake", "Unfolding", "Lumi/T_{AA}"};
   if(Grouping == 3)
      Sys = {"JEC", "JER", "Fake", "Power", "Unfolding", "Lumi/T_{AA}"};

   // Start declaring canvas, pad, axis, and axis title (as TLatex)
   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetNdivisions(505);
   HWorld.GetYaxis()->SetNdivisions(505);

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

   TGaxis AxisX1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 1, PadY0 + PadDY * 0, XMin, XMax, 505, "S");
   TGaxis AxisX2(PadX0 + PadDX * 1, PadY0 + PadDY * 0, PadX0 + PadDX * 2, PadY0 + PadDY * 0, XMin, XMax, 505, "S");
   TGaxis AxisX3(PadX0 + PadDX * 2, PadY0 + PadDY * 0, PadX0 + PadDX * 3, PadY0 + PadDY * 0, XMin, XMax, 505, "S");
   TGaxis AxisY1(PadX0 + PadDX * 0, PadY0 + PadDY * 0, PadX0 + PadDX * 0, PadY0 + PadDY * 1, YMin, YMax, 505, "S");
   TGaxis AxisY2(PadX0 + PadDX * 0, PadY0 + PadDY * 1, PadX0 + PadDX * 0, PadY0 + PadDY * 2, YMin, YMax, 505, "S");

   SetAxis(AxisX1);
   SetAxis(AxisX2);
   SetAxis(AxisX3);
   SetAxis(AxisY1);
   SetAxis(AxisY2);

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 1.5, PadY0 * 0.25, "Jet R");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(22);
   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.20, PadY0 + PadDY, "Uncertainty (%)");

   Latex.SetTextFont(62);
   Latex.SetTextSize(0.050);
   Latex.SetTextAlign(11);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * 2 + PadY0 * 0.15, "CMS");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadDX * 3, PadY0 + PadDY * 2 + PadY0 * 0.15, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 404 #mub^{-1}, pp 27.4 pb^{-1}");

   vector<TH1D *> HPT0 = GetSystematics(File, PT0, C, Grouping);
   vector<TH1D *> HPT1 = GetSystematics(File, PT1, C, Grouping);
   vector<TH1D *> HPT2 = GetSystematics(File, PT2, C, Grouping);
   vector<TH1D *> HPT3 = GetSystematics(File, PT3, C, Grouping);
   vector<TH1D *> HPT4 = GetSystematics(File, PT4, C, Grouping);

   Sys.push_back("Total");
   AppendTotal(HPT0);
   AppendTotal(HPT1);
   AppendTotal(HPT2);
   AppendTotal(HPT3);
   AppendTotal(HPT4);

   ScaleAll(HPT0);
   ScaleAll(HPT1);
   ScaleAll(HPT2);
   ScaleAll(HPT3);
   ScaleAll(HPT4);

   FormatHistograms(HPT0);
   FormatHistograms(HPT1);
   FormatHistograms(HPT2);
   FormatHistograms(HPT3);
   FormatHistograms(HPT4);

   TLegend Legend(0.08, 0.08, 0.48, 0.68);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.08);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   for(int i = 0; i < (int)HPT0.size(); i++)
      Legend.AddEntry(HPT0[i], Sys[i].c_str(), "l");

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.08);
   Latex.SetTextAlign(31);
   Latex.SetTextAngle(0);
   
   P1.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "200 - 250 GeV");
   DrawAll(HPT0);
   P2.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "250 - 300 GeV");
   DrawAll(HPT1);
   P3.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "300 - 400 GeV");
   DrawAll(HPT2);
   P4.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "400 - 500 GeV");
   DrawAll(HPT3);
   P5.cd();
   HWorld.Draw("axis");
   Latex.SetTextAlign(11);
   Latex.DrawLatex(0.08, 0.88, "500 - 1000 GeV");
   DrawAll(HPT4);
   P6.cd();
   HWorld.Draw("axis");
   Legend.Draw();
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.92, 0.88, ("Centrality: " + Cs[C]).c_str());
   Latex.DrawLatex(0.92, 0.78, "|#eta_{jet}| < 2");

   string OutputBase = "PlotSystematicsRRAA";
   OutputBase = OutputBase + "C" + to_string(C);

   Canvas.SaveAs((OutputBase + ".pdf").c_str());
   Canvas.SaveAs((OutputBase + ".png").c_str());
   Canvas.SaveAs((OutputBase + ".C").c_str());

   File.Close();

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
   A.SetTitleSize(0.040);
   A.SetMaxDigits(6);
   A.SetMoreLogLabels();
   A.SetNoExponent();
   A.SetTickLength(0);
   A.Draw();
}

vector<TH1D *> GetSystematics(TFile &File, int PT, int C, int Grouping)
{
   string Rs[] = {"2", "3", "4", "6", "8", "10"};
   string Cs[] = {"0to10", "10to30", "30to50", "50to90"};
   string PTs[] = {"200p0to250p0", "250p0to300p0", "300p0to400p0", "400p0to500p0", "500p0to1000p0"};
   vector<string> Sys = {"JECMC", "JECData", "JECUE", "JERMC", "JERData", "Fake", "Prior1PowerPthat", "MatrixStat", "SVD", "PriorAdj", "Lumi", "TAA"};
   
   vector<TH1D *> RawResult;

   string Centrality = "Cent" + Cs[C];

   for(int i = 0; i < (int)Sys.size(); i++)
   {
      TH1D *H = (TH1D *)File.Get((Centrality + "_" + PTs[PT] + "_" + Sys[i]).c_str());
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
      Item->Draw("same hist");
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
      H[i]->SetMarkerColor(Color[i]);
      H[i]->SetMarkerStyle(20);
      H[i]->SetMarkerSize(1);
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
   if(Grouping == 3)
   {
      int N = 6;

      for(int i = 0; i < 6; i++)
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
      QuadratureAdd(Result[4], H[7]);
      QuadratureAdd(Result[4], H[8]);
      QuadratureAdd(Result[4], H[9]);
      QuadratureAdd(Result[5], H[10]);
      QuadratureAdd(Result[5], H[11]);
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

