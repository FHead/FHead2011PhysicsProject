#include <iostream>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLine.h"
#include "TLatex.h"
#include "TLegend.h"

#include "PlotHelper3.h"

int main();
void MakePlot(vector<TGraphAsymmErrors *> G[4], vector<TGraphAsymmErrors *> T[4], string OutputBase);
bool DivideAndShift(vector<TGraphAsymmErrors *> &G, vector<TGraphAsymmErrors *> &R, double YShift, double RShift);
bool DivideAndShiftTheory(vector<TGraphAsymmErrors *> &T, vector<TGraphAsymmErrors *> &R, double YShift, double RShift);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *GRatio);
void ShiftUp(TGraphAsymmErrors *G, double Amount);
TGraphAsymmErrors *HistogramToGraph(TH1D *H);

int main()
{
   TFile F0("Graphs_SD0_DataCentered.root");
   TFile F7("Graphs_SD7_DataCentered.root");
   TFile FT0("PickedPlots_SD0.root");
   TFile FT7("PickedPlots_SD7.root");

   vector<TGraphAsymmErrors *> G[4];
   vector<TGraphAsymmErrors *> T[4];

   G[0].resize(16, NULL);
   G[1].resize(16, NULL);
   G[2].resize(16, NULL);
   G[3].resize(16, NULL);
   T[0].resize(24, NULL);
   T[1].resize(24, NULL);
   T[2].resize(24, NULL);
   T[3].resize(24, NULL);

   G[0][0]  = (TGraphAsymmErrors *)F0.Get("MassData0_0_1")->Clone();
   G[0][1]  = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_1")->Clone();
   G[0][2]  = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_1")->Clone();
   G[0][3]  = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_1")->Clone();
   G[0][4]  = (TGraphAsymmErrors *)F0.Get("MassData0_0_2")->Clone();
   G[0][5]  = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_2")->Clone();
   G[0][6]  = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_2")->Clone();
   G[0][7]  = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_2")->Clone();
   G[0][8]  = (TGraphAsymmErrors *)F0.Get("MassData0_0_3")->Clone();
   G[0][9]  = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_3")->Clone();
   G[0][10] = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_3")->Clone();
   G[0][11] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_3")->Clone();
   G[0][12] = (TGraphAsymmErrors *)F0.Get("MassData0_0_4")->Clone();
   G[0][13] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_4")->Clone();
   G[0][14] = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_4")->Clone();
   G[0][15] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_4")->Clone();

   T[0][0]  = HistogramToGraph((TH1D *)FT0.Get("JewelOffSB_C0PT1"));
   T[0][1]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacSB_C0PT1"));
   T[0][2]  = HistogramToGraph((TH1D *)FT0.Get("JewelOnS_C0PT1"));
   T[0][3]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacS_C0PT1"));
   T[0][4]  = HistogramToGraph((TH1D *)FT0.Get("QPythiaMedSB_C0PT1"));
   T[0][5]  = HistogramToGraph((TH1D *)FT0.Get("QPythiaVacSB_C0PT1"));
   T[0][6]  = HistogramToGraph((TH1D *)FT0.Get("JewelOffSB_C0PT2"));
   T[0][7]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacSB_C0PT2"));
   T[0][8]  = HistogramToGraph((TH1D *)FT0.Get("JewelOnS_C0PT2"));
   T[0][9]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacS_C0PT2"));
   T[0][10] = HistogramToGraph((TH1D *)FT0.Get("QPythiaMedSB_C0PT2"));
   T[0][11] = HistogramToGraph((TH1D *)FT0.Get("QPythiaVacSB_C0PT2"));
   T[0][12] = HistogramToGraph((TH1D *)FT0.Get("JewelOffSB_C0PT3"));
   T[0][13] = HistogramToGraph((TH1D *)FT0.Get("JewelVacSB_C0PT3"));
   T[0][14] = HistogramToGraph((TH1D *)FT0.Get("JewelOnS_C0PT3"));
   T[0][15] = HistogramToGraph((TH1D *)FT0.Get("JewelVacS_C0PT3"));
   T[0][16] = HistogramToGraph((TH1D *)FT0.Get("QPythiaMedSB_C0PT3"));
   T[0][17] = HistogramToGraph((TH1D *)FT0.Get("QPythiaVacSB_C0PT3"));
   T[0][18] = HistogramToGraph((TH1D *)FT0.Get("JewelOffSB_C0PT4"));
   T[0][19] = HistogramToGraph((TH1D *)FT0.Get("JewelVacSB_C0PT4"));
   T[0][20] = HistogramToGraph((TH1D *)FT0.Get("JewelOnS_C0PT4"));
   T[0][21] = HistogramToGraph((TH1D *)FT0.Get("JewelVacS_C0PT4"));
   T[0][22] = HistogramToGraph((TH1D *)FT0.Get("QPythiaMedSB_C0PT4"));
   T[0][23] = HistogramToGraph((TH1D *)FT0.Get("QPythiaVacSB_C0PT4"));
  
   G[2][0] = (TGraphAsymmErrors *)F7.Get("MassData_0_1")->Clone();
   G[2][1] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_1")->Clone();
   G[2][2] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_1")->Clone();
   G[2][3] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_1")->Clone();
   G[2][4] = (TGraphAsymmErrors *)F7.Get("MassData_0_2")->Clone();
   G[2][5] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_2")->Clone();
   G[2][6] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_2")->Clone();
   G[2][7] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_2")->Clone();
   G[2][8] = (TGraphAsymmErrors *)F7.Get("MassData_0_3")->Clone();
   G[2][9] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_3")->Clone();
   G[2][10] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_3")->Clone();
   G[2][11] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_3")->Clone();
   G[2][12] = (TGraphAsymmErrors *)F7.Get("MassData_0_4")->Clone();
   G[2][13] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_4")->Clone();
   G[2][14] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_4")->Clone();
   G[2][15] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_4")->Clone();

   T[2][0]  = HistogramToGraph((TH1D *)FT7.Get("JewelOffS_C0PT1"));
   T[2][1]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT1"));
   T[2][2]  = HistogramToGraph((TH1D *)FT7.Get("JewelOnS_C0PT1"));
   T[2][3]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT1"));
   T[2][4]  = HistogramToGraph((TH1D *)FT7.Get("QPythiaMedS_C0PT1"));
   T[2][5]  = HistogramToGraph((TH1D *)FT7.Get("QPythiaVacS_C0PT1"));
   T[2][6]  = HistogramToGraph((TH1D *)FT7.Get("JewelOffS_C0PT2"));
   T[2][7]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT2"));
   T[2][8]  = HistogramToGraph((TH1D *)FT7.Get("JewelOnS_C0PT2"));
   T[2][9]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT2"));
   T[2][10] = HistogramToGraph((TH1D *)FT7.Get("QPythiaMedS_C0PT2"));
   T[2][11] = HistogramToGraph((TH1D *)FT7.Get("QPythiaVacS_C0PT2"));
   T[2][12] = HistogramToGraph((TH1D *)FT7.Get("JewelOffS_C0PT3"));
   T[2][13] = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT3"));
   T[2][14] = HistogramToGraph((TH1D *)FT7.Get("JewelOnS_C0PT3"));
   T[2][15] = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT3"));
   T[2][16] = HistogramToGraph((TH1D *)FT7.Get("QPythiaMedS_C0PT3"));
   T[2][17] = HistogramToGraph((TH1D *)FT7.Get("QPythiaVacS_C0PT3"));
   T[2][18] = HistogramToGraph((TH1D *)FT7.Get("JewelOffS_C0PT4"));
   T[2][19] = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT4"));
   T[2][20] = HistogramToGraph((TH1D *)FT7.Get("JewelOnS_C0PT4"));
   T[2][21] = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT4"));
   T[2][22] = HistogramToGraph((TH1D *)FT7.Get("QPythiaMedS_C0PT4"));
   T[2][23] = HistogramToGraph((TH1D *)FT7.Get("QPythiaVacS_C0PT4"));
   
   G[1][0] = (TGraphAsymmErrors *)F0.Get("MassData0_0_2")->Clone();
   G[1][1] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_2")->Clone();
   G[1][2] = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_2")->Clone();
   G[1][3] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_2")->Clone();
   G[1][4] = (TGraphAsymmErrors *)F0.Get("MassData0_1_2")->Clone();
   G[1][5] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_1_2")->Clone();
   G[1][6] = (TGraphAsymmErrors *)F0.Get("MassSmear0_1_2")->Clone();
   G[1][7] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_1_2")->Clone();
   G[1][8] = (TGraphAsymmErrors *)F0.Get("MassData0_2_2")->Clone();
   G[1][9] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_2_2")->Clone();
   G[1][10] = (TGraphAsymmErrors *)F0.Get("MassSmear0_2_2")->Clone();
   G[1][11] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_2_2")->Clone();
   G[1][12] = (TGraphAsymmErrors *)F0.Get("MassData0_3_2")->Clone();
   G[1][13] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_3_2")->Clone();
   G[1][14] = (TGraphAsymmErrors *)F0.Get("MassSmear0_3_2")->Clone();
   G[1][15] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_3_2")->Clone();

   for(int i = 0; i < 24; i++)
      T[1][i] = NULL;

   G[3][0] = (TGraphAsymmErrors *)F7.Get("MassData_0_2")->Clone();
   G[3][1] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_2")->Clone();
   G[3][2] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_2")->Clone();
   G[3][3] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_2")->Clone();
   G[3][4] = (TGraphAsymmErrors *)F7.Get("MassData_1_2")->Clone();
   G[3][5] = (TGraphAsymmErrors *)F7.Get("MassDataSys_1_2")->Clone();
   G[3][6] = (TGraphAsymmErrors *)F7.Get("MassSmear_1_2")->Clone();
   G[3][7] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_1_2")->Clone();
   G[3][8] = (TGraphAsymmErrors *)F7.Get("MassData_2_2")->Clone();
   G[3][9] = (TGraphAsymmErrors *)F7.Get("MassDataSys_2_2")->Clone();
   G[3][10] = (TGraphAsymmErrors *)F7.Get("MassSmear_2_2")->Clone();
   G[3][11] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_2_2")->Clone();
   G[3][12] = (TGraphAsymmErrors *)F7.Get("MassData_3_2")->Clone();
   G[3][13] = (TGraphAsymmErrors *)F7.Get("MassDataSys_3_2")->Clone();
   G[3][14] = (TGraphAsymmErrors *)F7.Get("MassSmear_3_2")->Clone();
   G[3][15] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_3_2")->Clone();

   for(int i = 0; i < 24; i++)
      T[3][i] = NULL;

   MakePlot(G, T, "Plots/MoneyPlot16714");

   FT7.Close();
   FT0.Close();
   F7.Close();
   F0.Close();

   return 0;
}

void MakePlot(vector<TGraphAsymmErrors *> G[4], vector<TGraphAsymmErrors *> T[4], string OutputBase)
{
   // Inputs: edit to your liking

   double LeftMargin, RightMargin, TopMargin, BottomMargin, Height, Width;
   double XMinL, XMaxL, XMinR, XMaxR, YMinB, YMaxB, YMinT, YMaxT, RMinB, RMaxB, RMinT, RMaxT;
   double HeaderSizeB, HeaderSizeT, BreakPointOffset, BreakPointSizeX, BreakPointSizeY, BreakPointSpacing;
   double TextSpacing;
   double TextYX, TextYY, TextRX, TextRY;
   int TextRAlign, TextYAlign;
   int AxisStyleB, TopAxisStyleB;
   int AxisStyleT, TopAxisStyleT;

   LeftMargin = 150;
   RightMargin = 100;
   TopMargin = 100;
   BottomMargin = 100;
   Height = 700;
   Width = 300;

   TextSpacing = 0.035;

   XMinL = 0.00;   XMaxL = 0.27;
   XMinR = 0.00;   XMaxR = 0.27;
   YMinB = 0.00;   YMaxB = 19.99;
   YMinT = 0.00;   YMaxT = 9.99;
   RMinB = 0.00;   RMaxB = 5.99;
   RMinT = 0.00;   RMaxT = 11.99;

   HeaderSizeB = 0.5;
   HeaderSizeT = 2.0;
   BreakPointOffset = -0.07;
   BreakPointSizeX = 0.020;
   BreakPointSizeY = 0.004;
   BreakPointSpacing = 0.003;

   TextYAlign = 22;
   TextYX = 0.50;
   TextYY = 8.50;
   TextRAlign = 22;
   TextRX = 0.50;
   TextRY = 4.00;

   AxisStyleB = 502;
   TopAxisStyleB = 505;
   AxisStyleT = 502;
   TopAxisStyleT = 510;

   // Derived inputs.  Don't edit.

   double TotalHeight = 2 * Height + TopMargin + BottomMargin;
   double TotalWidth = 2 * Width + LeftMargin + RightMargin;

   double WorldYMinB = YMinB;
   double WorldYMaxB = YMinB + (YMaxB - YMinB) * (4 + HeaderSizeB);
   double YShiftB = YMaxB - YMinB;
   double WorldYMinT = YMinT;
   double WorldYMaxT = YMinT + (YMaxT - YMinT) * (4 + HeaderSizeT);
   double YShiftT = YMaxT - YMinT;
   
   double WorldRMinB = RMinB;
   double WorldRMaxB = RMinB + (RMaxB - RMinB) * (4 + HeaderSizeB);
   double RShiftB = RMaxB - RMinB;
   double WorldRMinT = RMinT;
   double WorldRMaxT = RMinT + (RMaxT - RMinT) * (4 + HeaderSizeT);
   double RShiftT = RMaxT - RMinT;

   double PanelHeightB = Height / (4 + HeaderSizeB);
   double PanelHeightT = Height / (4 + HeaderSizeT);

   // Canvas and pad settings

   TCanvas Canvas("Canvas", "", TotalWidth, TotalHeight);

   TPad *Pad1 = new TPad("Pad1", "", LeftMargin / TotalWidth, (BottomMargin + Height) / TotalHeight,
      (LeftMargin + Width) / TotalWidth, (BottomMargin + 2 * Height) / TotalHeight);
   Pad1->SetTopMargin(0);
   Pad1->SetRightMargin(0);
   Pad1->SetBottomMargin(0);
   Pad1->SetLeftMargin(0);
   Pad1->Draw();

   TPad *Pad2 = new TPad("Pad2", "", (LeftMargin + Width) / TotalWidth, (BottomMargin + Height) / TotalHeight,
      (LeftMargin + 2 * Width) / TotalWidth, (BottomMargin + 2 * Height) / TotalHeight);
   Pad2->SetTopMargin(0);
   Pad2->SetRightMargin(0);
   Pad2->SetBottomMargin(0);
   Pad2->SetLeftMargin(0);
   Pad2->Draw();

   TPad *Pad3 = new TPad("Pad3", "", LeftMargin / TotalWidth, BottomMargin / TotalHeight,
      (LeftMargin + Width) / TotalWidth, (BottomMargin + Height) / TotalHeight);
   Pad3->SetTopMargin(0);
   Pad3->SetRightMargin(0);
   Pad3->SetBottomMargin(0);
   Pad3->SetLeftMargin(0);
   Pad3->Draw();
   
   TPad *Pad4 = new TPad("Pad4", "", (LeftMargin + Width) / TotalWidth, BottomMargin / TotalHeight,
      (LeftMargin + 2 * Width) / TotalWidth, (BottomMargin + Height) / TotalHeight);
   Pad4->SetTopMargin(0);
   Pad4->SetRightMargin(0);
   Pad4->SetBottomMargin(0);
   Pad4->SetLeftMargin(0);
   Pad4->Draw();

   // Make sure the inputs are done correctly

   vector<TGraphAsymmErrors *> R[4];
   R[0].resize(8, NULL);
   R[1].resize(8, NULL);
   R[2].resize(8, NULL);
   R[3].resize(8, NULL);
   bool Success = DivideAndShift(G[0], R[0], YShiftT, RShiftT)
      && DivideAndShift(G[1], R[1], YShiftT, RShiftT)
      && DivideAndShift(G[2], R[2], YShiftB, RShiftB)
      && DivideAndShift(G[3], R[3], YShiftB, RShiftB);
   if(Success == false)
   {
      for(int j = 0; j < 4; j++)
      {
         for(int i = 0; i < 16; i++)
         {
            if(G[j][i] != NULL)
               delete G[j][i];
            G[j][i] = NULL;
         }   
         for(int i = 0; i < 24; i++)
         {
            if(T[j][i] != NULL)
               delete T[j][i];
            T[j][i] = NULL;
         }
      }
      return;
   }

   bool HasTheory[4] = {true, true, true, true};
   for(int j = 0; j < 4; j++)
      for(int i = 0; i < 24; i++)
         if(T[j][i] == NULL)
            HasTheory[j] = false;

   vector<TGraphAsymmErrors *> RT[4];
   RT[0].resize(12, NULL);
   RT[1].resize(12, NULL);
   RT[2].resize(12, NULL);
   RT[3].resize(12, NULL);
   for(int j = 0; j < 4; j++)
   {
      if(HasTheory[j] == true)
      {
         if(j == 0 || j == 1)
            Success = DivideAndShiftTheory(T[j], RT[j], YShiftT, RShiftT);
         else
            Success = DivideAndShiftTheory(T[j], RT[j], YShiftB, RShiftB);

         if(Success == false)
         {
            for(int i = 0; i < 16; i++)
            {
               if(G[j][i] != NULL)
                  delete G[j][i];
               G[j][i] = NULL;
            }
            for(int i = 0; i < 24; i++)
            {
               if(T[j][i] != NULL)
                  delete T[j][i];
               T[j][i] = NULL;
            }
            return;
         }
      }
   }

   // Set the stage

   TH2D HWorld1("HWorld1", ";;", 100, XMinL, XMaxL, 100, WorldYMinT, WorldYMaxT);
   HWorld1.SetStats(0);
   HWorld1.GetXaxis()->SetLabelSize(0);
   HWorld1.GetYaxis()->SetLabelSize(0);
   HWorld1.GetXaxis()->SetTickLength(0);
   HWorld1.GetYaxis()->SetTickLength(0);
   
   TH2D HWorld2("HWorld2", ";;", 100, XMinR, XMaxR, 100, WorldYMinT, WorldYMaxT);
   HWorld2.SetStats(0);
   HWorld2.GetXaxis()->SetLabelSize(0);
   HWorld2.GetYaxis()->SetLabelSize(0);
   HWorld2.GetXaxis()->SetTickLength(0);
   HWorld2.GetYaxis()->SetTickLength(0);
   
   TH2D HWorld3("HWorld3", ";;", 100, XMinL, XMaxL, 100, WorldYMinB, WorldYMaxB);
   HWorld3.SetStats(0);
   HWorld3.GetXaxis()->SetLabelSize(0);
   HWorld3.GetYaxis()->SetLabelSize(0);
   HWorld3.GetXaxis()->SetTickLength(0);
   HWorld3.GetYaxis()->SetTickLength(0);
   
   TH2D HWorld4("HWorld4", ";;", 100, XMinR, XMaxR, 100, WorldYMinB, WorldYMaxB);
   HWorld4.SetStats(0);
   HWorld4.GetXaxis()->SetLabelSize(0);
   HWorld4.GetYaxis()->SetLabelSize(0);
   HWorld4.GetXaxis()->SetTickLength(0);
   HWorld4.GetYaxis()->SetTickLength(0);
   
   TH2D HWorldRatio1("HWorldRatio1", ";;", 100, XMinL, XMaxL, 100, WorldRMinT, WorldRMaxT);
   HWorldRatio1.SetStats(0);
   HWorldRatio1.GetXaxis()->SetLabelSize(0);
   HWorldRatio1.GetYaxis()->SetLabelSize(0);
   HWorldRatio1.GetXaxis()->SetTickLength(0);
   HWorldRatio1.GetYaxis()->SetTickLength(0);

   TH2D HWorldRatio2("HWorldRatio2", ";;", 100, XMinR, XMaxR, 100, WorldRMinT, WorldRMaxT);
   HWorldRatio2.SetStats(0);
   HWorldRatio2.GetXaxis()->SetLabelSize(0);
   HWorldRatio2.GetYaxis()->SetLabelSize(0);
   HWorldRatio2.GetXaxis()->SetTickLength(0);
   HWorldRatio2.GetYaxis()->SetTickLength(0);

   TH2D HWorldRatio3("HWorldRatio3", ";;", 100, XMinL, XMaxL, 100, WorldRMinB, WorldRMaxB);
   HWorldRatio3.SetStats(0);
   HWorldRatio3.GetXaxis()->SetLabelSize(0);
   HWorldRatio3.GetYaxis()->SetLabelSize(0);
   HWorldRatio3.GetXaxis()->SetTickLength(0);
   HWorldRatio3.GetYaxis()->SetTickLength(0);

   TH2D HWorldRatio4("HWorldRatio4", ";;", 100, XMinR, XMaxR, 100, WorldRMinB, WorldRMaxB);
   HWorldRatio4.SetStats(0);
   HWorldRatio4.GetXaxis()->SetLabelSize(0);
   HWorldRatio4.GetYaxis()->SetLabelSize(0);
   HWorldRatio4.GetXaxis()->SetTickLength(0);
   HWorldRatio4.GetYaxis()->SetTickLength(0);

   // Prepare axis

   TGaxis BottomAxisL(LeftMargin / TotalWidth, BottomMargin / TotalHeight,
      (LeftMargin + Width) / TotalWidth, BottomMargin / TotalHeight,
      XMinL, XMaxL, 1005, "S");
   BottomAxisL.SetName("BottomAxisL");
   BottomAxisL.SetTitle("M_{g} / p_{T,jet}");
   BottomAxisL.SetTickLength(0.025);
   BottomAxisL.SetTextFont(42);
   BottomAxisL.SetLabelFont(42);
   BottomAxisL.CenterTitle(true);
   BottomAxisL.SetLabelOffset(-0.005);
   BottomAxisL.SetTitleOffset(0.75);
   BottomAxisL.Draw();
   
   TGaxis BottomAxisR((LeftMargin + Width) / TotalWidth, BottomMargin / TotalHeight,
      (LeftMargin + Width * 2) / TotalWidth, BottomMargin / TotalHeight,
      XMinR, XMaxR, 1005, "S");
   BottomAxisR.SetName("BottomAxisR");
   BottomAxisR.SetTitle("M_{g} / p_{T,jet}");
   BottomAxisR.SetTickLength(0.025);
   BottomAxisR.SetTextFont(42);
   BottomAxisR.SetLabelFont(42);
   BottomAxisR.CenterTitle(true);
   BottomAxisR.SetLabelOffset(-0.005);
   BottomAxisR.SetTitleOffset(0.75);
   BottomAxisR.Draw();

   TGaxis LeftAxis1(LeftMargin / TotalWidth, (BottomMargin + PanelHeightB * 0) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + PanelHeightB * 1) / TotalHeight,
      YMinB, YMaxB, AxisStyleB, "S");
   LeftAxis1.SetName("LeftAxis1");
   LeftAxis1.SetTitle("");
   LeftAxis1.SetTickLength(0.2);
   LeftAxis1.SetLabelFont(42);
   LeftAxis1.Draw();

   TGaxis LeftAxis2(LeftMargin / TotalWidth, (BottomMargin + PanelHeightB * 1) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + PanelHeightB * 2) / TotalHeight,
      YMinB, YMaxB, AxisStyleB, "S");
   LeftAxis2.SetName("LeftAxis2");
   LeftAxis2.SetTitle("");
   LeftAxis2.SetTickLength(0.2);
   LeftAxis2.SetLabelFont(42);
   LeftAxis2.Draw();

   TGaxis LeftAxis3(LeftMargin / TotalWidth, (BottomMargin + PanelHeightB * 2) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + PanelHeightB * 3) / TotalHeight,
      YMinB, YMaxB, AxisStyleB, "S");
   LeftAxis3.SetName("LeftAxis3");
   LeftAxis3.SetTitle("");
   LeftAxis3.SetTickLength(0.2);
   LeftAxis3.SetLabelFont(42);
   LeftAxis3.Draw();

   TGaxis LeftAxis4(LeftMargin / TotalWidth, (BottomMargin + PanelHeightB * 3) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + Height) / TotalHeight,
      YMinB, YMaxB + (YMaxB - YMinB) * HeaderSizeB, TopAxisStyleB, "S");
   LeftAxis4.SetName("LeftAxis4");
   LeftAxis4.SetTitle("");
   LeftAxis4.SetTickLength(0.2 / (1 + HeaderSizeB));
   LeftAxis4.SetLabelFont(42);
   LeftAxis4.Draw();

   TGaxis LeftAxis5(LeftMargin / TotalWidth, (BottomMargin + PanelHeightT * 0 + Height) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + PanelHeightT * 1 + Height) / TotalHeight,
      YMinT, YMaxT, AxisStyleT, "S");
   LeftAxis5.SetName("LeftAxis5");
   LeftAxis5.SetTitle("");
   LeftAxis5.SetTickLength(0.2);
   LeftAxis5.SetLabelFont(42);
   LeftAxis5.Draw();

   TGaxis LeftAxis6(LeftMargin / TotalWidth, (BottomMargin + PanelHeightT * 1 + Height) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + PanelHeightT * 2 + Height) / TotalHeight,
      YMinT, YMaxT, AxisStyleT, "S");
   LeftAxis6.SetName("LeftAxis6");
   LeftAxis6.SetTitle("");
   LeftAxis6.SetTickLength(0.2);
   LeftAxis6.SetLabelFont(42);
   LeftAxis6.Draw();

   TGaxis LeftAxis7(LeftMargin / TotalWidth, (BottomMargin + PanelHeightT * 2 + Height) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + PanelHeightT * 3 + Height) / TotalHeight,
      YMinT, YMaxT, AxisStyleT, "S");
   LeftAxis7.SetName("LeftAxis7");
   LeftAxis7.SetTitle("");
   LeftAxis7.SetTickLength(0.2);
   LeftAxis7.SetLabelFont(42);
   LeftAxis7.Draw();

   TGaxis LeftAxis8(LeftMargin / TotalWidth, (BottomMargin + PanelHeightT * 3 + Height) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + Height * 2) / TotalHeight,
      YMinT, YMaxT + (YMaxT - YMinT) * HeaderSizeT, TopAxisStyleT, "S");
   LeftAxis8.SetName("LeftAxis8");
   LeftAxis8.SetTitle("");
   LeftAxis8.SetTickLength(0.2 / (1 + HeaderSizeT));
   LeftAxis8.SetLabelFont(42);
   LeftAxis8.Draw();

   TGaxis LeftAxisB(LeftMargin / TotalWidth, BottomMargin / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + Height) / TotalHeight,
      YMinB, YMaxB, 510, "S");
   LeftAxisB.SetName("LeftAxisB");
   LeftAxisB.SetTitle("#frac{1}{N} #frac{d N}{d M_{g}/p_{T,jet}}");
   LeftAxisB.SetTickLength(0);
   LeftAxisB.SetTextFont(42);
   LeftAxisB.SetLabelSize(0);
   LeftAxisB.CenterTitle(true);
   LeftAxisB.SetTitleOffset(1.40);
   LeftAxisB.Draw();

   TGaxis LeftAxisT(LeftMargin / TotalWidth, (BottomMargin + Height) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + Height * 2) / TotalHeight,
      YMinT, YMaxT, 510, "S");
   LeftAxisT.SetName("LeftAxisT");
   LeftAxisT.SetTitle("#frac{1}{N} #frac{d N}{d M_{g}/p_{T,jet}}");
   LeftAxisT.SetTickLength(0);
   LeftAxisT.SetTextFont(42);
   LeftAxisT.SetLabelSize(0);
   LeftAxisT.CenterTitle(true);
   LeftAxisT.SetTitleOffset(1.40);
   LeftAxisT.Draw();

   /*
   TGaxis RightAxis1((LeftMargin + Width) / TotalWidth, (BottomMargin + PanelHeight * 0) / TotalHeight,
      (LeftMargin + Width) / TotalWidth, (BottomMargin + PanelHeight * 1) / TotalHeight,
      YMin, YMax, AxisStyle, "S+L");
   RightAxis1.SetName("RightAxis1");
   RightAxis1.SetTitle("");
   RightAxis1.SetTickLength(0.2);
   RightAxis1.SetLabelFont(42);
   RightAxis1.SetLabelSize(0);
   RightAxis1.Draw();

   TGaxis RightAxis2((LeftMargin + Width) / TotalWidth, (BottomMargin + PanelHeight * 1) / TotalHeight,
      (LeftMargin + Width) / TotalWidth, (BottomMargin + PanelHeight * 2) / TotalHeight,
      YMin, YMax, AxisStyle, "S+L");
   RightAxis2.SetName("RightAxis2");
   RightAxis2.SetTitle("");
   RightAxis2.SetTickLength(0.2);
   RightAxis2.SetLabelFont(42);
   RightAxis2.SetLabelSize(0);
   RightAxis2.Draw();

   TGaxis RightAxis3((LeftMargin + Width) / TotalWidth, (BottomMargin + PanelHeight * 2) / TotalHeight,
      (LeftMargin + Width) / TotalWidth, (BottomMargin + PanelHeight * 3) / TotalHeight,
      YMin, YMax, AxisStyle, "S+L");
   RightAxis3.SetName("RightAxis3");
   RightAxis3.SetTitle("");
   RightAxis3.SetTickLength(0.2);
   RightAxis3.SetLabelFont(42);
   RightAxis3.SetLabelSize(0);
   RightAxis3.Draw();

   TGaxis RightAxis4((LeftMargin + Width) / TotalWidth, (BottomMargin + PanelHeight * 3) / TotalHeight,
      (LeftMargin + Width) / TotalWidth, (BottomMargin + Height) / TotalHeight,
      YMin, YMax + (YMax - YMin) * HeaderSize, TopAxisStyle, "S+L");
   RightAxis4.SetName("RightAxis4");
   RightAxis4.SetTitle("");
   RightAxis4.SetTickLength(0.2 / (1 + HeaderSize));
   RightAxis4.SetLabelFont(42);
   RightAxis4.SetLabelSize(0);
   RightAxis4.Draw();
   */

   TLine Line;
   Line.SetLineWidth(2);
   Line.SetNDC();
   
   for(int i = 0; i < 3; i++)
   {
      double X = LeftMargin / TotalWidth;
      double Y = (BottomMargin + PanelHeightB * (i + 1) + PanelHeightB * BreakPointOffset) / TotalHeight;

      Line.SetLineColor(kBlack);
      Line.DrawLine(X - BreakPointSizeX / 2, Y + BreakPointSpacing / 2 - BreakPointSizeY / 2,
         X + BreakPointSizeX / 2, Y + BreakPointSpacing / 2 + BreakPointSizeY / 2);
      Line.DrawLine(X - BreakPointSizeX / 2, Y - BreakPointSpacing / 2 - BreakPointSizeY / 2,
         X + BreakPointSizeX / 2, Y - BreakPointSpacing / 2 + BreakPointSizeY / 2);

      Line.SetLineColor(kWhite);
      Line.DrawLine(X - BreakPointSizeX, Y - BreakPointSizeY,
         X + BreakPointSizeX, Y + BreakPointSizeY);
   
      X = (LeftMargin + Width) / TotalWidth;

      Line.SetLineColor(kBlack);
      Line.DrawLine(X - BreakPointSizeX / 2, Y + BreakPointSpacing / 2 - BreakPointSizeY / 2,
         X + BreakPointSizeX / 2, Y + BreakPointSpacing / 2 + BreakPointSizeY / 2);
      Line.DrawLine(X - BreakPointSizeX / 2, Y - BreakPointSpacing / 2 - BreakPointSizeY / 2,
         X + BreakPointSizeX / 2, Y - BreakPointSpacing / 2 + BreakPointSizeY / 2);

      Line.SetLineColor(kWhite);
      Line.DrawLine(X - BreakPointSizeX, Y - BreakPointSizeY,
         X + BreakPointSizeX, Y + BreakPointSizeY);
   }

   // Prepare TGraphs and TLines

   TLine UnityLine;
   UnityLine.SetLineStyle(kDotted);

   // Prepare TLatex

   /*
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetNDC();

   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(31);
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth, (BottomMargin + Height) / TotalHeight + 0.005, "PbPb 404 #mub^{-1} (5.02 TeV), pp 27.4 #mub^{-1} (5.02 TeV)");

   Latex.SetTextSize(0.065);
   Latex.SetTextAlign(13);
   Latex.DrawLatex((LeftMargin) / TotalWidth + 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight, "#font[62]{CMS}");

   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(31);
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 0.5, "anti-k_{T} R = 0.4, |#eta_{jet}| < 1.3");
   if(Preset == SD0_PT || Preset ==  SD0_CENTRALITY)
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 1.5, "Soft drop z_{cut} = 0.1, #beta = 0.0");
   else
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 1.5, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 2.5, "#DeltaR_{12} > 0.1");
   if(Preset == SD0_PT || Preset == SD7_PT)
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 3.5, "Centrality: 0-10%");
   else
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 3.5, "160 < p_{T,jet} < 180 GeV");
   */

   // Set graph styles

   for(int j = 0; j < 4; j++)
   {
      for(int i = 0; i < 4; i++)
      {
         G[j][i*4+0]->SetMarkerSize(2.0);
         G[j][i*4+2]->SetMarkerSize(2.0);

         G[j][i*4+0]->SetMarkerStyle(25);
         G[j][i*4+2]->SetMarkerStyle(26);

         G[j][i*4+2]->SetFillStyle(3145);
         G[j][i*4+3]->SetFillStyle(3145);

         G[j][i*4+0]->SetFillColor(kRed - 9);
         G[j][i*4+1]->SetFillColor(kRed - 9);
         G[j][i*4+2]->SetFillColor(kGray + 2);
         G[j][i*4+3]->SetFillColor(kGray + 2);

         R[j][i*2+0]->SetMarkerSize(2.0);
         R[j][i*2+0]->SetMarkerStyle(25);
         R[j][i*2+0]->SetMarkerColor(kBlack);
         R[j][i*2+0]->SetLineColor(kBlack);
         R[j][i*2+0]->SetFillColor(kRed - 9);
         R[j][i*2+1]->SetFillColor(kRed - 9);
      }
   }

   // Prepare Legend
  
   /*
   TLegend Legend1(0.10, 0.70, 0.60, 0.85);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.045);
   Legend1.SetBorderSize(0);
   Legend1.SetFillStyle(0);
   Legend1.AddEntry(G[0], "PbPb", "lpf");
   Legend1.AddEntry(G[2], "Smeared pp", "lpf");
   Legend1.AddEntry("", " ", "");
   Legend1.AddEntry("", " ", "");
   
   TLegend Legend2(0.10, 0.70, 0.60, 0.85);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.045);
   Legend2.SetBorderSize(0);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(R[0], "Data", "lpf");
   if(HasTheory == true)
   {
      Legend2.AddEntry(RT[0], "Jewel (Recoil off)", "lp");
      Legend2.AddEntry(RT[1], "Jewel (Recoil on)",  "lp");
      Legend2.AddEntry(RT[2], "QPythia",            "lp");
   }
   else
   {
      Legend2.AddEntry("", " ", "");
      Legend2.AddEntry("", " ", "");
      Legend2.AddEntry("", " ", "");
   }
   */

   // Draw it!

   Pad1->cd();
   HWorld1.Draw("axis");
   for(int i = 1; i < 16; i = i + 2)   G[0][i]->Draw("2");
   for(int i = 0; i < 16; i = i + 2)   G[0][i]->Draw("p");
   HWorld1.Draw("axis same");
   
   Pad2->cd();
   HWorld2.Draw("axis");
   for(int i = 1; i < 16; i = i + 2)   G[1][i]->Draw("2");
   for(int i = 0; i < 16; i = i + 2)   G[1][i]->Draw("p");
   HWorld2.Draw("axis same");
   
   Pad3->cd();
   HWorld3.Draw("axis");
   for(int i = 1; i < 16; i = i + 2)   G[2][i]->Draw("2");
   for(int i = 0; i < 16; i = i + 2)   G[2][i]->Draw("p");
   HWorld3.Draw("axis same");
   
   Pad4->cd();
   HWorld4.Draw("axis");
   for(int i = 1; i < 16; i = i + 2)   G[3][i]->Draw("2");
   for(int i = 0; i < 16; i = i + 2)   G[3][i]->Draw("p");
   HWorld4.Draw("axis same");
  
   /*
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(TextYAlign);

   if(Preset == SD0_PT || Preset == SD7_PT)
   {
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 0) / (WorldYMax - YMin), "200 < p_{T,jet} < 300 GeV");
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 1) / (WorldYMax - YMin), "180 < p_{T,jet} < 200 GeV");
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 2) / (WorldYMax - YMin), "160 < p_{T,jet} < 180 GeV");
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 3) / (WorldYMax - YMin), "140 < p_{T,jet} < 160 GeV");
   }
   else
   {
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 0) / (WorldYMax - YMin), "Centrality: 50-80%");
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 1) / (WorldYMax - YMin), "Centrality: 30-50%");
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 2) / (WorldYMax - YMin), "Centrality: 10-30%");
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 3) / (WorldYMax - YMin), "Centrality: 0-10%");
   }
   */

   // Legend1.Draw();

   Canvas.cd();

   Canvas.SaveAs((OutputBase + "_Spectrum.pdf").c_str());

   // Draw ratio!

   LeftAxis1.SetWmin(RMinB);   LeftAxis1.SetWmax(RMaxB);
   LeftAxis2.SetWmin(RMinB);   LeftAxis2.SetWmax(RMaxB);
   LeftAxis3.SetWmin(RMinB);   LeftAxis3.SetWmax(RMaxB);
   LeftAxis4.SetWmin(RMinB);   LeftAxis4.SetWmax(RMaxB + (RMaxB - RMinB) * HeaderSizeB);
   LeftAxis5.SetWmin(RMinT);   LeftAxis5.SetWmax(RMaxT);
   LeftAxis6.SetWmin(RMinT);   LeftAxis6.SetWmax(RMaxT);
   LeftAxis7.SetWmin(RMinT);   LeftAxis7.SetWmax(RMaxT);
   LeftAxis8.SetWmin(RMinT);   LeftAxis8.SetWmax(RMaxT + (RMaxT - RMinT) * HeaderSizeT);

   // RightAxis1.SetWmin(RMin);   RightAxis1.SetWmax(RMax);
   // RightAxis2.SetWmin(RMin);   RightAxis2.SetWmax(RMax);
   // RightAxis3.SetWmin(RMin);   RightAxis3.SetWmax(RMax);
   // RightAxis4.SetWmin(RMin);   RightAxis4.SetWmax(RMax + (RMax - RMin) * HeaderSize);
   
   LeftAxisT.SetTitle("#frac{PbPb}{Smeared pp}");
   LeftAxisB.SetTitle("#frac{PbPb}{Smeared pp}");

   for(int j = 0; j < 4; j++)
   {
      if(j == 0)   Pad1->cd();
      if(j == 1)   Pad2->cd();
      if(j == 2)   Pad3->cd();
      if(j == 3)   Pad4->cd();

      if(j == 0)   HWorldRatio1.Draw("axis");
      if(j == 1)   HWorldRatio2.Draw("axis");
      if(j == 2)   HWorldRatio3.Draw("axis");
      if(j == 3)   HWorldRatio4.Draw("axis");

      for(int i = 1; i < 8; i = i + 2)
         R[j][i]->Draw("2");

      double XMin, XMax, RShift;
      if(j == 0)   XMin = XMinL, XMax = XMaxL, RShift = RShiftT;
      if(j == 1)   XMin = XMinR, XMax = XMaxR, RShift = RShiftT;
      if(j == 2)   XMin = XMinL, XMax = XMaxL, RShift = RShiftB;
      if(j == 3)   XMin = XMinR, XMax = XMaxR, RShift = RShiftB;

      UnityLine.DrawLine(XMinL, 1 + RShift * 0, XMax, 1 + RShift * 0);
      UnityLine.DrawLine(XMinL, 1 + RShift * 1, XMax, 1 + RShift * 1);
      UnityLine.DrawLine(XMinL, 1 + RShift * 2, XMax, 1 + RShift * 2);
      UnityLine.DrawLine(XMinL, 1 + RShift * 3, XMax, 1 + RShift * 3);

      for(int i = 0; i < 8; i = i + 2)
         R[j][i]->Draw("p");

      if(HasTheory[j] == true)
      {
         for(int i = 0; i < 4; i++)
         {
            RT[j][i*3+0]->SetLineWidth(2);
            RT[j][i*3+1]->SetLineWidth(2);
            RT[j][i*3+2]->SetLineWidth(2);

            RT[j][i*3+0]->SetLineColor(kGreen - 2);
            RT[j][i*3+1]->SetLineColor(kBlue);
            RT[j][i*3+2]->SetLineColor(kRed);

            RT[j][i*3+0]->SetMarkerStyle(20);
            RT[j][i*3+1]->SetMarkerStyle(20);
            RT[j][i*3+2]->SetMarkerStyle(20);

            RT[j][i*3+0]->SetMarkerSize(0);
            RT[j][i*3+1]->SetMarkerSize(0);
            RT[j][i*3+2]->SetMarkerSize(0);

            RT[j][i*3+0]->SetMarkerColor(kGreen - 2);
            RT[j][i*3+1]->SetMarkerColor(kBlue);
            RT[j][i*3+2]->SetMarkerColor(kRed);
         }

         for(int i = 0; i < 12; i++)
            RT[j][i]->Draw("l");
      }

      if(j == 0)   HWorldRatio1.Draw("axis same");
      if(j == 1)   HWorldRatio2.Draw("axis same");
      if(j == 2)   HWorldRatio3.Draw("axis same");
      if(j == 3)   HWorldRatio4.Draw("axis same");
   }
   
   // Latex.SetTextSize(0.035);
   // Latex.SetTextAlign(TextRAlign);

   // if(Preset == SD0_PT || Preset == SD7_PT)
   // {
   //    Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 0) / (WorldRMax - RMin), "200 < p_{T,jet} < 300 GeV");
   //    Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 1) / (WorldRMax - RMin), "180 < p_{T,jet} < 200 GeV");
   //    Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 2) / (WorldRMax - RMin), "160 < p_{T,jet} < 180 GeV");
   //    Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 3) / (WorldRMax - RMin), "140 < p_{T,jet} < 160 GeV");
   // }
   // else
   // {
   //    Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 0) / (WorldRMax - RMin), "Centrality: 50-80%");
   //    Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 1) / (WorldRMax - RMin), "Centrality: 30-50%");
   //    Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 2) / (WorldRMax - RMin), "Centrality: 10-30%");
   //    Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 3) / (WorldRMax - RMin), "Centrality: 0-10%");
   // }

   // Legend2.Draw();

   Canvas.cd();

   Canvas.SaveAs((OutputBase + "_Ratio.pdf").c_str());

   // Clean up

   for(int j = 0; j < 4; j++)
   {
      for(int i = 0; i < 16; i++)
      {
         if(G[j][i] != NULL)
            delete G[j][i];
         G[j][i] = NULL;
      }
      for(int i = 0; i < 8; i++)
         if(R[j][i] != NULL)
            delete R[j][i];

      for(int i = 0; i < 24; i++)
      {
         if(T[j][i] != NULL)
            delete T[j][i];
         T[j][i] = NULL;
      }
      for(int i = 0; i < 12; i++)
         if(RT[j][i] != NULL)
            delete RT[j][i];
   }
}

bool DivideAndShift(vector<TGraphAsymmErrors *> &G, vector<TGraphAsymmErrors *> &R, double YShift, double RShift)
{
   if(G.size() != 16)
      return false;
   for(int i = 0; i < 16; i++)
      if(G[i] == NULL)
         return false;

   for(int i = 0; i < 8; i++)
   {
      if(R[i] != NULL)
         delete R[i];
      R[i] = new TGraphAsymmErrors;
   }

   // First do the division
   Division(G[0], G[2], R[0]);
   Division(G[1], G[3], R[1]);
   Division(G[4], G[6], R[2]);
   Division(G[5], G[7], R[3]);
   Division(G[8], G[10], R[4]);
   Division(G[9], G[11], R[5]);
   Division(G[12], G[14], R[6]);
   Division(G[13], G[15], R[7]);

   // Then do the shifting
   ShiftUp(G[0], YShift * 3);
   ShiftUp(G[1], YShift * 3);
   ShiftUp(G[2], YShift * 3);
   ShiftUp(G[3], YShift * 3);
   ShiftUp(G[4], YShift * 2);
   ShiftUp(G[5], YShift * 2);
   ShiftUp(G[6], YShift * 2);
   ShiftUp(G[7], YShift * 2);
   ShiftUp(G[8], YShift * 1);
   ShiftUp(G[9], YShift * 1);
   ShiftUp(G[10], YShift * 1);
   ShiftUp(G[11], YShift * 1);
   ShiftUp(G[12], YShift * 0);
   ShiftUp(G[13], YShift * 0);
   ShiftUp(G[14], YShift * 0);
   ShiftUp(G[15], YShift * 0);
   ShiftUp(R[0], RShift * 3);
   ShiftUp(R[1], RShift * 3);
   ShiftUp(R[2], RShift * 2);
   ShiftUp(R[3], RShift * 2);
   ShiftUp(R[4], RShift * 1);
   ShiftUp(R[5], RShift * 1);
   ShiftUp(R[6], RShift * 0);
   ShiftUp(R[7], RShift * 0);

   return true;
}

bool DivideAndShiftTheory(vector<TGraphAsymmErrors *> &T, vector<TGraphAsymmErrors *> &R, double YShift, double RShift)
{
   if(T.size() != 24)
      return false;
   for(int i = 0; i < 24; i++)
      if(T[i] == NULL)
         return false;

   for(int i = 0; i < 12; i++)
   {
      if(R[i] != NULL)
         delete R[i];
      R[i] = new TGraphAsymmErrors;
   }

   // First do the division
   Division(T[0], T[1], R[0]);
   Division(T[2], T[3], R[1]);
   Division(T[4], T[5], R[2]);
   Division(T[6], T[7], R[3]);
   Division(T[8], T[9], R[4]);
   Division(T[10], T[11], R[5]);
   Division(T[12], T[13], R[6]);
   Division(T[14], T[15], R[7]);
   Division(T[16], T[17], R[8]);
   Division(T[18], T[19], R[9]);
   Division(T[20], T[21], R[10]);
   Division(T[22], T[23], R[11]);

   // Then do the shifting
   ShiftUp(R[0], RShift * 3);
   ShiftUp(R[1], RShift * 3);
   ShiftUp(R[2], RShift * 3);
   ShiftUp(R[3], RShift * 2);
   ShiftUp(R[4], RShift * 2);
   ShiftUp(R[5], RShift * 2);
   ShiftUp(R[6], RShift * 1);
   ShiftUp(R[7], RShift * 1);
   ShiftUp(R[8], RShift * 1);
   ShiftUp(R[9], RShift * 0);
   ShiftUp(R[10], RShift * 0);
   ShiftUp(R[11], RShift * 0);

   return true;
}

void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *GRatio)
{
   if(G1 == NULL || G2 == NULL || GRatio == NULL)
      return;

   int BinCount = min(G1->GetN(), G2->GetN());

   for(int i = 0; i < BinCount; i++)
   {
      double x1, x2, y1, y2;
      G1->GetPoint(i, x1, y1);
      G2->GetPoint(i, x2, y2);

      double xl1, xh1, xl2, xh2;
      xl1 = G1->GetErrorXlow(i);
      xh1 = G1->GetErrorXhigh(i);
      xl2 = G2->GetErrorXlow(i);
      xh2 = G2->GetErrorXhigh(i);

      double yl1, yh1, yl2, yh2;
      yl1 = G1->GetErrorYlow(i);
      yh1 = G1->GetErrorYhigh(i);
      yl2 = G2->GetErrorYlow(i);
      yh2 = G2->GetErrorYhigh(i);

      double ratio = (y1 / y2);

      double yl = ratio * sqrt((yl1 / y1) * (yl1 / y1) + (yl2 / y2) * (yl2 / y2));
      double yh = ratio * sqrt((yh1 / y1) * (yh1 / y1) + (yh2 / y2) * (yh2 / y2));

      if(x1 == x1 && x2 == x2 && ratio == ratio)
      {
         int N = GRatio->GetN();
         GRatio->SetPoint(N, x1, ratio);
         GRatio->SetPointError(N, xl1, xh1, yl, yh);
      }
   }
}

void ShiftUp(TGraphAsymmErrors *G, double Amount)
{
   if(G == NULL)
      return;

   int BinCount = G->GetN();
   for(int i = 0; i < BinCount; i++)
   {
      double x, y;
      G->GetPoint(i, x, y);
      G->SetPoint(i, x, y + Amount);
   }
}

TGraphAsymmErrors *HistogramToGraph(TH1D *H)
{
   if(H == NULL)
      return NULL;

   TGraphAsymmErrors *G = new TGraphAsymmErrors;

   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      double x = H->GetBinCenter(i);
      double y = H->GetBinContent(i);

      double l = H->GetXaxis()->GetBinLowEdge(i);
      double r = H->GetXaxis()->GetBinUpEdge(i);

      double e = H->GetBinError(i);

      if(y != y)
         continue;
      if(x > 0.27)
         continue;

      int I = G->GetN();
      G->SetPoint(I, x, y);
      // G->SetPointError(I, x - l, r - x, e, e);
   }

   return G;
}










