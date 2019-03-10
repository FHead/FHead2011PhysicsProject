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

#define SD0_PT 0
#define SD0_CENTRALITY 1
#define SD7_PT 2
#define SD7_CENTRALITY 3

int main();
void MakePlot(vector<TGraphAsymmErrors *> G, vector<TGraphAsymmErrors *> T, string OutputBase, int Preset = SD0_PT);
bool DivideAndShift(vector<TGraphAsymmErrors *> &G, vector<TGraphAsymmErrors *> &R, double YShift, double RShift);
bool DivideAndShiftTheory(vector<TGraphAsymmErrors *> &T, vector<TGraphAsymmErrors *> &R, double YShift, double RShift);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *GRatio);
void ShiftUp(TGraphAsymmErrors *G, double Amount);
TGraphAsymmErrors *HistogramToGraph(TH1D *H);

int main()
{
   TFile F("HEPDataGraphs.root", "RECREATE");
   F.Close();

   TFile F0("Graphs_SD0_DataCentered.root");
   TFile F7("Graphs_SD7_DataCentered.root");
   TFile FT0("PickedPlots_SD0.root");
   TFile FT7("PickedPlots_SD7.root");

   vector<TGraphAsymmErrors *> G(16);
   vector<TGraphAsymmErrors *> T(24);

   G[0]  = (TGraphAsymmErrors *)F0.Get("MassData0_0_1")->Clone();
   G[1]  = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_1")->Clone();
   G[2]  = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_1")->Clone();
   G[3]  = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_1")->Clone();
   G[4]  = (TGraphAsymmErrors *)F0.Get("MassData0_0_2")->Clone();
   G[5]  = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_2")->Clone();
   G[6]  = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_2")->Clone();
   G[7]  = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_2")->Clone();
   G[8]  = (TGraphAsymmErrors *)F0.Get("MassData0_0_3")->Clone();
   G[9]  = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_3")->Clone();
   G[10] = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_3")->Clone();
   G[11] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_3")->Clone();
   G[12] = (TGraphAsymmErrors *)F0.Get("MassData0_0_4")->Clone();
   G[13] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_4")->Clone();
   G[14] = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_4")->Clone();
   G[15] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_4")->Clone();

   T[0]  = HistogramToGraph((TH1D *)FT0.Get("JewelOffSB_C0PT1"));
   T[1]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacSB_C0PT1"));
   T[2]  = HistogramToGraph((TH1D *)FT0.Get("JewelOnS_C0PT1"));
   T[3]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacS_C0PT1"));
   T[4]  = HistogramToGraph((TH1D *)FT0.Get("QPythiaMedSB_C0PT1"));
   T[5]  = HistogramToGraph((TH1D *)FT0.Get("QPythiaVacSB_C0PT1"));
   T[6]  = HistogramToGraph((TH1D *)FT0.Get("JewelOffSB_C0PT2"));
   T[7]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacSB_C0PT2"));
   T[8]  = HistogramToGraph((TH1D *)FT0.Get("JewelOnS_C0PT2"));
   T[9]  = HistogramToGraph((TH1D *)FT0.Get("JewelVacS_C0PT2"));
   T[10] = HistogramToGraph((TH1D *)FT0.Get("QPythiaMedSB_C0PT2"));
   T[11] = HistogramToGraph((TH1D *)FT0.Get("QPythiaVacSB_C0PT2"));
   T[12] = HistogramToGraph((TH1D *)FT0.Get("JewelOffSB_C0PT3"));
   T[13] = HistogramToGraph((TH1D *)FT0.Get("JewelVacSB_C0PT3"));
   T[14] = HistogramToGraph((TH1D *)FT0.Get("JewelOnS_C0PT3"));
   T[15] = HistogramToGraph((TH1D *)FT0.Get("JewelVacS_C0PT3"));
   T[16] = HistogramToGraph((TH1D *)FT0.Get("QPythiaMedSB_C0PT3"));
   T[17] = HistogramToGraph((TH1D *)FT0.Get("QPythiaVacSB_C0PT3"));
   T[18] = HistogramToGraph((TH1D *)FT0.Get("JewelOffSB_C0PT4"));
   T[19] = HistogramToGraph((TH1D *)FT0.Get("JewelVacSB_C0PT4"));
   T[20] = HistogramToGraph((TH1D *)FT0.Get("JewelOnS_C0PT4"));
   T[21] = HistogramToGraph((TH1D *)FT0.Get("JewelVacS_C0PT4"));
   T[22] = HistogramToGraph((TH1D *)FT0.Get("QPythiaMedSB_C0PT4"));
   T[23] = HistogramToGraph((TH1D *)FT0.Get("QPythiaVacSB_C0PT4"));
   
   MakePlot(G, T, "Plots/SD0_CBin0", SD0_PT);

   G[0] = (TGraphAsymmErrors *)F7.Get("MassData_0_1")->Clone();
   G[1] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_1")->Clone();
   G[2] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_1")->Clone();
   G[3] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_1")->Clone();
   G[4] = (TGraphAsymmErrors *)F7.Get("MassData_0_2")->Clone();
   G[5] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_2")->Clone();
   G[6] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_2")->Clone();
   G[7] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_2")->Clone();
   G[8] = (TGraphAsymmErrors *)F7.Get("MassData_0_3")->Clone();
   G[9] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_3")->Clone();
   G[10] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_3")->Clone();
   G[11] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_3")->Clone();
   G[12] = (TGraphAsymmErrors *)F7.Get("MassData_0_4")->Clone();
   G[13] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_4")->Clone();
   G[14] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_4")->Clone();
   G[15] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_4")->Clone();

   T[0]  = HistogramToGraph((TH1D *)FT7.Get("JewelOffS_C0PT1"));
   T[1]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT1"));
   T[2]  = HistogramToGraph((TH1D *)FT7.Get("JewelOnS_C0PT1"));
   T[3]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT1"));
   T[4]  = HistogramToGraph((TH1D *)FT7.Get("QPythiaMedS_C0PT1"));
   T[5]  = HistogramToGraph((TH1D *)FT7.Get("QPythiaVacS_C0PT1"));
   T[6]  = HistogramToGraph((TH1D *)FT7.Get("JewelOffS_C0PT2"));
   T[7]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT2"));
   T[8]  = HistogramToGraph((TH1D *)FT7.Get("JewelOnS_C0PT2"));
   T[9]  = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT2"));
   T[10] = HistogramToGraph((TH1D *)FT7.Get("QPythiaMedS_C0PT2"));
   T[11] = HistogramToGraph((TH1D *)FT7.Get("QPythiaVacS_C0PT2"));
   T[12] = HistogramToGraph((TH1D *)FT7.Get("JewelOffS_C0PT3"));
   T[13] = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT3"));
   T[14] = HistogramToGraph((TH1D *)FT7.Get("JewelOnS_C0PT3"));
   T[15] = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT3"));
   T[16] = HistogramToGraph((TH1D *)FT7.Get("QPythiaMedS_C0PT3"));
   T[17] = HistogramToGraph((TH1D *)FT7.Get("QPythiaVacS_C0PT3"));
   T[18] = HistogramToGraph((TH1D *)FT7.Get("JewelOffS_C0PT4"));
   T[19] = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT4"));
   T[20] = HistogramToGraph((TH1D *)FT7.Get("JewelOnS_C0PT4"));
   T[21] = HistogramToGraph((TH1D *)FT7.Get("JewelVacS_C0PT4"));
   T[22] = HistogramToGraph((TH1D *)FT7.Get("QPythiaMedS_C0PT4"));
   T[23] = HistogramToGraph((TH1D *)FT7.Get("QPythiaVacS_C0PT4"));
   
   MakePlot(G, T, "Plots/SD7_CBin0", SD7_PT);

   G[0] = (TGraphAsymmErrors *)F0.Get("MassData0_0_2")->Clone();
   G[1] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_0_2")->Clone();
   G[2] = (TGraphAsymmErrors *)F0.Get("MassSmear0_0_2")->Clone();
   G[3] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_0_2")->Clone();
   G[4] = (TGraphAsymmErrors *)F0.Get("MassData0_1_2")->Clone();
   G[5] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_1_2")->Clone();
   G[6] = (TGraphAsymmErrors *)F0.Get("MassSmear0_1_2")->Clone();
   G[7] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_1_2")->Clone();
   G[8] = (TGraphAsymmErrors *)F0.Get("MassData0_2_2")->Clone();
   G[9] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_2_2")->Clone();
   G[10] = (TGraphAsymmErrors *)F0.Get("MassSmear0_2_2")->Clone();
   G[11] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_2_2")->Clone();
   G[12] = (TGraphAsymmErrors *)F0.Get("MassData0_3_2")->Clone();
   G[13] = (TGraphAsymmErrors *)F0.Get("MassDataSys0_3_2")->Clone();
   G[14] = (TGraphAsymmErrors *)F0.Get("MassSmear0_3_2")->Clone();
   G[15] = (TGraphAsymmErrors *)F0.Get("MassSmearSys0_3_2")->Clone();

   for(int i = 0; i < 24; i++)
      T[i] = NULL;

   MakePlot(G, T, "Plots/SD0_PTBin2", SD0_CENTRALITY);

   G[0] = (TGraphAsymmErrors *)F7.Get("MassData_0_2")->Clone();
   G[1] = (TGraphAsymmErrors *)F7.Get("MassDataSys_0_2")->Clone();
   G[2] = (TGraphAsymmErrors *)F7.Get("MassSmear_0_2")->Clone();
   G[3] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_0_2")->Clone();
   G[4] = (TGraphAsymmErrors *)F7.Get("MassData_1_2")->Clone();
   G[5] = (TGraphAsymmErrors *)F7.Get("MassDataSys_1_2")->Clone();
   G[6] = (TGraphAsymmErrors *)F7.Get("MassSmear_1_2")->Clone();
   G[7] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_1_2")->Clone();
   G[8] = (TGraphAsymmErrors *)F7.Get("MassData_2_2")->Clone();
   G[9] = (TGraphAsymmErrors *)F7.Get("MassDataSys_2_2")->Clone();
   G[10] = (TGraphAsymmErrors *)F7.Get("MassSmear_2_2")->Clone();
   G[11] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_2_2")->Clone();
   G[12] = (TGraphAsymmErrors *)F7.Get("MassData_3_2")->Clone();
   G[13] = (TGraphAsymmErrors *)F7.Get("MassDataSys_3_2")->Clone();
   G[14] = (TGraphAsymmErrors *)F7.Get("MassSmear_3_2")->Clone();
   G[15] = (TGraphAsymmErrors *)F7.Get("MassSmearSys_3_2")->Clone();

   for(int i = 0; i < 24; i++)
      T[i] = NULL;

   MakePlot(G, T, "Plots/SD7_PTBin2", SD7_CENTRALITY);

   FT7.Close();
   FT0.Close();
   F7.Close();
   F0.Close();

   return 0;
}

void MakePlot(vector<TGraphAsymmErrors *> G, vector<TGraphAsymmErrors *> T, string OutputBase, int Preset)
{
   string GraphBase = OutputBase;
   int Position = GraphBase.find("Plots/");
   if(Position != string::npos)
      GraphBase.replace(Position, 6, "");

   // Inputs: edit to your liking

   double LeftMargin, RightMargin, TopMargin, BottomMargin, Height, Width;
   double XMin, XMax, YMin, YMax, RMin, RMax;
   double HeaderSize, BreakPointOffset, BreakPointSizeX, BreakPointSizeY, BreakPointSpacing;
   double TextSpacing;
   double TextYX, TextYY, TextRX, TextRY;
   int TextRAlign, TextYAlign;
   int AxisStyle, TopAxisStyle;

   LeftMargin = 100;
   RightMargin = 50;
   TopMargin = 50;
   BottomMargin = 75;
   Height = 700;
   Width = 500;

   TextSpacing = 0.035;

   if(Preset == SD0_PT)
   {
      XMin = 0.00;   XMax = 0.27;
      YMin = 0.00;   YMax = 7.99;
      RMin = 0.00;   RMax = 11.99;

      HeaderSize = 1.5;
      BreakPointOffset = -0.07;
      BreakPointSizeX = 0.020;
      BreakPointSizeY = 0.004;
      BreakPointSpacing = 0.003;

      TextYAlign = 22;
      TextYX = 0.50;
      TextYY = 9.00;
      TextRAlign = 22;
      TextRX = 0.50;
      TextRY = 4.00;
   
      AxisStyle = 502;
      TopAxisStyle = 505;
   }
   if(Preset == SD7_PT)
   {
      XMin = 0.00;   XMax = 0.26;
      YMin = 0.00;   YMax = 19.99;
      RMin = 0.00;   RMax = 6.99;

      HeaderSize = 1.5;
      BreakPointOffset = -0.07;
      BreakPointSizeX = 0.020;
      BreakPointSizeY = 0.004;
      BreakPointSpacing = 0.003;

      TextYAlign = 22;
      TextYX = 0.70;
      TextYY = 5.50;
      TextRAlign = 22;
      TextRX = 0.50;
      TextRY = 2.50;
   
      AxisStyle = 502;
      TopAxisStyle = 505;
   }
   if(Preset == SD0_CENTRALITY)
   {
      XMin = 0.00;   XMax = 0.27;
      YMin = 0.00;   YMax = 11.99;
      RMin = 0.00;   RMax = 2.99;

      HeaderSize = 1.5;
      BreakPointOffset = -0.07;
      BreakPointSizeX = 0.020;
      BreakPointSizeY = 0.004;
      BreakPointSpacing = 0.003;

      TextYAlign = 22;
      TextYX = 0.50;
      TextYY = 9.50;
      TextRAlign = 22;
      TextRX = 0.50;
      TextRY = 1.70;
   
      AxisStyle = 502;
      TopAxisStyle = 505;
   }
   if(Preset == SD7_CENTRALITY)
   {
      XMin = 0.00;   XMax = 0.26;
      YMin = 0.00;   YMax = 19.99;
      RMin = 0.00;   RMax = 2.99;

      HeaderSize = 1.5;
      BreakPointOffset = -0.07;
      BreakPointSizeX = 0.020;
      BreakPointSizeY = 0.004;
      BreakPointSpacing = 0.003;

      TextYAlign = 22;
      TextYX = 0.70;
      TextYY = 5.50;
      TextRAlign = 22;
      TextRX = 0.50;
      TextRY = 1.70;
   
      AxisStyle = 502;
      TopAxisStyle = 505;
   }

   // Derived inputs.  Don't edit.

   double TotalHeight = Height + TopMargin + BottomMargin;
   double TotalWidth = Width + LeftMargin + RightMargin;

   double WorldYMin = YMin;
   double WorldYMax = YMin + (YMax - YMin) * (4 + HeaderSize);
   double YShift = YMax - YMin;
   
   double WorldRMin = RMin;
   double WorldRMax = RMin + (RMax - RMin) * (4 + HeaderSize);
   double RShift = RMax - RMin;

   double PanelHeight = Height / (4 + HeaderSize);

   // Canvas and pad settings

   TCanvas Canvas("Canvas", "", TotalWidth, TotalHeight);
   TPad *Pad = new TPad("Pad", "", LeftMargin / TotalWidth, BottomMargin / TotalHeight,
      (LeftMargin + Width) / TotalWidth, (BottomMargin + Height) / TotalHeight);
   Pad->SetTopMargin(0);
   Pad->SetRightMargin(0);
   Pad->SetBottomMargin(0);
   Pad->SetLeftMargin(0);
   Pad->Draw();

   // Make sure the inputs are done correctly

   vector<TGraphAsymmErrors *> R(8, NULL);
   bool Success = DivideAndShift(G, R, 0, 0);
   if(Success == false)
   {
      for(int i = 0; i < 16; i++)
      {
         if(G[i] != NULL)
            delete G[i];
         G[i] = NULL;
      }   
      for(int i = 0; i < 24; i++)
      {
         if(T[i] != NULL)
            delete T[i];
         T[i] = NULL;
      }
      return;
   }

   // Save graphs before shifting anything
   TFile File("HEPDataGraphs.root", "UPDATE");

   string SpectrumLabelCPlot[16] =
   {
      "AACBin0", "AACBin0Sys", "PPCBin0", "PPCBin0Sys",
      "AACBin1", "AACBin1Sys", "PPCBin1", "PPCBin1Sys",
      "AACBin2", "AACBin2Sys", "PPCBin2", "PPCBin2Sys",
      "AACBin3", "AACBin3Sys", "PPCBin3", "PPCBin3Sys",
   };
   string SpectrumLabelPTPlot[16] =
   {
      "AAPTBin1", "AAPTBin1Sys", "PPPTBin1", "PPPTBin1Sys",
      "AAPTBin2", "AAPTBin2Sys", "PPPTBin2", "PPPTBin2Sys",
      "AAPTBin3", "AAPTBin3Sys", "PPPTBin3", "PPPTBin3Sys",
      "AAPTBin4", "AAPTBin4Sys", "PPPTBin4", "PPPTBin4Sys",
   };
   string RatioLabelCPlot[16] = {"CBin0", "CBin0Sys", "CBin1", "CBin1Sys", "CBin2", "CBin2Sys", "CBin3", "CBin3Sys"};
   string RatioLabelPTPlot[16] = {"PTBin1", "PTBin1Sys", "PTBin2", "PTBin2Sys", "PTBin3", "PTBin3Sys", "PTBin4", "PTBin4Sys"};

   string *SpectrumLabel = SpectrumLabelPTPlot;
   if(Preset == SD0_CENTRALITY || Preset == SD7_CENTRALITY)
      SpectrumLabel = SpectrumLabelCPlot;
   string *RatioLabel = RatioLabelPTPlot;
   if(Preset == SD0_CENTRALITY || Preset == SD7_CENTRALITY)
      RatioLabel = RatioLabelCPlot;

   for(int i = 0; i < 16; i++)
      G[i]->Clone(Form("Spectrum_%s_%s", GraphBase.c_str(), SpectrumLabel[i].c_str()))->Write();
   for(int i = 0; i < 8; i++)
      R[i]->Clone(Form("Ratio_%s_%s", GraphBase.c_str(), RatioLabel[i].c_str()))->Write();

   File.Close();

   // Make sure the inputs are done correctly
   Success = DivideAndShift(G, R, YShift, RShift);

   bool HasTheory = true;
   for(int i = 0; i < 24; i++)
      if(T[i] == NULL)
         HasTheory = false;

   vector<TGraphAsymmErrors *> RT(12, NULL);
   if(HasTheory == true)
   {
      Success = DivideAndShiftTheory(T, RT, YShift, RShift);
      if(Success == false)
      {
         for(int i = 0; i < 16; i++)
         {
            if(G[i] != NULL)
               delete G[i];
            G[i] = NULL;
         }
         for(int i = 0; i < 24; i++)
         {
            if(T[i] != NULL)
               delete T[i];
            T[i] = NULL;
         }
         return;
      }
   }

   // Set the stage

   TH2D HWorld("HWorld", ";;", 100, XMin, XMax, 100, WorldYMin, WorldYMax);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetLabelSize(0);
   HWorld.GetYaxis()->SetLabelSize(0);
   HWorld.GetXaxis()->SetTickLength(0);
   HWorld.GetYaxis()->SetTickLength(0);
   
   TH2D HWorldRatio("HWorldRatio", ";;", 100, XMin, XMax, 100, WorldRMin, WorldRMax);
   HWorldRatio.SetStats(0);
   HWorldRatio.GetXaxis()->SetLabelSize(0);
   HWorldRatio.GetYaxis()->SetLabelSize(0);
   HWorldRatio.GetXaxis()->SetTickLength(0);
   HWorldRatio.GetYaxis()->SetTickLength(0);

   // Prepare axis

   TGaxis BottomAxis(LeftMargin / TotalWidth, BottomMargin / TotalHeight,
      (LeftMargin + Width) / TotalWidth, BottomMargin / TotalHeight,
      XMin, XMax, 1005, "S");
   BottomAxis.SetName("BottomAxis");
   BottomAxis.SetTitle("M_{g} / p_{T,jet}");
   BottomAxis.SetTickLength(0.025);
   BottomAxis.SetTextFont(42);
   BottomAxis.SetLabelFont(42);
   BottomAxis.CenterTitle(true);
   BottomAxis.SetLabelOffset(-0.005);
   BottomAxis.SetTitleSize(0.050);
   BottomAxis.SetTitleOffset(0.80);
   BottomAxis.Draw();

   TGaxis LeftAxis1(LeftMargin / TotalWidth, (BottomMargin + PanelHeight * 0) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + PanelHeight * 1) / TotalHeight,
      YMin, YMax, AxisStyle, "S");
   LeftAxis1.SetName("LeftAxis1");
   LeftAxis1.SetTitle("");
   LeftAxis1.SetTickLength(0.2);
   LeftAxis1.SetLabelFont(42);
   LeftAxis1.Draw();

   TGaxis LeftAxis2(LeftMargin / TotalWidth, (BottomMargin + PanelHeight * 1) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + PanelHeight * 2) / TotalHeight,
      YMin, YMax, AxisStyle, "S");
   LeftAxis2.SetName("LeftAxis2");
   LeftAxis2.SetTitle("");
   LeftAxis2.SetTickLength(0.2);
   LeftAxis2.SetLabelFont(42);
   LeftAxis2.Draw();

   TGaxis LeftAxis3(LeftMargin / TotalWidth, (BottomMargin + PanelHeight * 2) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + PanelHeight * 3) / TotalHeight,
      YMin, YMax, AxisStyle, "S");
   LeftAxis3.SetName("LeftAxis3");
   LeftAxis3.SetTitle("");
   LeftAxis3.SetTickLength(0.2);
   LeftAxis3.SetLabelFont(42);
   LeftAxis3.Draw();

   TGaxis LeftAxis4(LeftMargin / TotalWidth, (BottomMargin + PanelHeight * 3) / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + Height) / TotalHeight,
      YMin, YMax + (YMax - YMin) * HeaderSize, TopAxisStyle, "S");
   LeftAxis4.SetName("LeftAxis4");
   LeftAxis4.SetTitle("");
   LeftAxis4.SetTickLength(0.2 / (1 + HeaderSize));
   LeftAxis4.SetLabelFont(42);
   LeftAxis4.Draw();

   TGaxis LeftAxis(LeftMargin / TotalWidth, BottomMargin / TotalHeight,
      LeftMargin / TotalWidth, (BottomMargin + Height) / TotalHeight,
      YMin, YMax, 510, "S");
   LeftAxis.SetName("LeftAxis");
   LeftAxis.SetTitle("#frac{1}{N} #frac{d N}{d M_{g} / p_{T,jet}}");
   LeftAxis.SetTickLength(0);
   LeftAxis.SetTextFont(42);
   LeftAxis.SetLabelSize(0);
   LeftAxis.CenterTitle(true);
   LeftAxis.SetTitleSize(0.050);
   LeftAxis.SetTitleOffset(1.20);
   LeftAxis.Draw();

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

   TLine Line;
   Line.SetLineWidth(2);
   Line.SetNDC();
   
   for(int i = 0; i < 3; i++)
   {
      double X = LeftMargin / TotalWidth;
      double Y = (BottomMargin + PanelHeight * (i + 1) + PanelHeight * BreakPointOffset) / TotalHeight;

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

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetNDC();

   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(31);
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth, (BottomMargin + Height) / TotalHeight + 0.005, "PbPb 404 #mub^{-1} (5.02 TeV), pp 27.4 #mub^{-1} (5.02 TeV)");

   Latex.SetTextSize(0.065);
   Latex.SetTextAlign(13);
   Latex.DrawLatex((LeftMargin) / TotalWidth + 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight, "#font[62]{CMS}");

   Latex.SetTextSize(0.040);
   Latex.SetTextAlign(31);
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 0.4, "anti-k_{T} R = 0.4, |#eta_{jet}| < 1.3");
   if(Preset == SD0_PT || Preset ==  SD0_CENTRALITY)
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 1.5, "Soft Drop z_{cut} = 0.1, #beta = 0.0");
   else
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 1.5, "Soft Drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 2.5, "#DeltaR_{12} > 0.1");
   if(Preset == SD0_PT || Preset == SD7_PT)
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 3.5, "Centrality: 0-10%");
   else
      Latex.DrawLatex((LeftMargin + Width) / TotalWidth - 0.04, (BottomMargin + Height - 0.04 * TotalWidth) / TotalHeight - TextSpacing * 3.5, "160 < p_{T,jet} < 180 GeV");

   // Set graph styles

   for(int i = 0; i < 4; i++)
   {
      G[i*4+0]->SetMarkerSize(2.0);
      G[i*4+2]->SetMarkerSize(2.0);
  
      if(i % 2 == 0)
      {
         G[i*4+0]->SetMarkerStyle(25);
         G[i*4+2]->SetMarkerStyle(26);
      }
      else
      {
         G[i*4+0]->SetMarkerStyle(25);
         G[i*4+2]->SetMarkerStyle(22);
      }
   
      G[i*4+2]->SetFillStyle(3145);
      G[i*4+3]->SetFillStyle(3145);
   
      G[i*4+0]->SetFillColor(kRed - 9);
      G[i*4+1]->SetFillColor(kRed - 9);
      G[i*4+2]->SetFillColor(kGray + 2);
      G[i*4+3]->SetFillColor(kGray + 2);
   
      R[i*2+0]->SetMarkerSize(2.0);
      R[i*2+0]->SetMarkerStyle(25);
      R[i*2+0]->SetMarkerColor(kBlack);
      R[i*2+0]->SetLineColor(kBlack);
      R[i*2+0]->SetFillColor(kRed - 9);
      R[i*2+1]->SetFillColor(kRed - 9);
   }

   // Prepare Legend
   
   TLegend Legend1(0.08, 0.70, 0.60, 0.85);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.055);
   Legend1.SetBorderSize(0);
   Legend1.SetFillStyle(0);
   Legend1.AddEntry(G[0], "PbPb", "lpf");
   Legend1.AddEntry(G[2], "Smeared pp", "lpf");
   Legend1.AddEntry("", " ", "");
   Legend1.AddEntry("", " ", "");
   
   TLegend Legend2(0.08, 0.70, 0.60, 0.85);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.055);
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

   // Draw it!

   Pad->cd();
   HWorld.Draw("axis");

   for(int i = 1; i < 16; i = i + 2)
      G[i]->Draw("2");
   for(int i = 0; i < 16; i = i + 2)
      G[i]->Draw("p");
   
   Latex.SetTextSize(0.055);
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
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 0) / (WorldYMax - YMin), "50-80%");
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 1) / (WorldYMax - YMin), "30-50%");
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 2) / (WorldYMax - YMin), "10-30%");
      Latex.DrawLatex(TextYX, (TextYY - YMin + (YMax - YMin) * 3) / (WorldYMax - YMin), "0-10%");
   }

   HWorld.Draw("axis same");

   Legend1.Draw();

   Canvas.cd();

   Canvas.SaveAs((OutputBase + "_Spectrum.pdf").c_str());

   // Draw ratio!

   LeftAxis1.SetWmin(RMin);   LeftAxis1.SetWmax(RMax);
   LeftAxis2.SetWmin(RMin);   LeftAxis2.SetWmax(RMax);
   LeftAxis3.SetWmin(RMin);   LeftAxis3.SetWmax(RMax);
   LeftAxis4.SetWmin(RMin);   LeftAxis4.SetWmax(RMax + (RMax - RMin) * HeaderSize);

   RightAxis1.SetWmin(RMin);   RightAxis1.SetWmax(RMax);
   RightAxis2.SetWmin(RMin);   RightAxis2.SetWmax(RMax);
   RightAxis3.SetWmin(RMin);   RightAxis3.SetWmax(RMax);
   RightAxis4.SetWmin(RMin);   RightAxis4.SetWmax(RMax + (RMax - RMin) * HeaderSize);
   
   LeftAxis.SetTitle("#frac{PbPb}{Smeared pp}");

   Pad->cd();

   HWorldRatio.Draw("axis");

   for(int i = 1; i < 8; i = i + 2)
      R[i]->Draw("2");

   UnityLine.DrawLine(XMin, 1 + RShift * 0, XMax, 1 + RShift * 0);
   UnityLine.DrawLine(XMin, 1 + RShift * 1, XMax, 1 + RShift * 1);
   UnityLine.DrawLine(XMin, 1 + RShift * 2, XMax, 1 + RShift * 2);
   UnityLine.DrawLine(XMin, 1 + RShift * 3, XMax, 1 + RShift * 3);

   for(int i = 0; i < 8; i = i + 2)
      R[i]->Draw("p");

   if(HasTheory == true)
   {
      for(int i = 0; i < 4; i++)
      {
         RT[i*3+0]->SetLineWidth(2);
         RT[i*3+1]->SetLineWidth(2);
         RT[i*3+2]->SetLineWidth(2);

         RT[i*3+0]->SetLineColor(kGreen - 2);
         RT[i*3+1]->SetLineColor(kBlue);
         RT[i*3+2]->SetLineColor(kRed);
         
         RT[i*3+0]->SetLineStyle(kSolid);
         RT[i*3+1]->SetLineStyle(kDashed);
         RT[i*3+2]->SetLineStyle(kDotted);

         RT[i*3+0]->SetMarkerStyle(20);
         RT[i*3+1]->SetMarkerStyle(20);
         RT[i*3+2]->SetMarkerStyle(20);

         RT[i*3+0]->SetMarkerSize(0);
         RT[i*3+1]->SetMarkerSize(0);
         RT[i*3+2]->SetMarkerSize(0);

         RT[i*3+0]->SetMarkerColor(kGreen - 2);
         RT[i*3+1]->SetMarkerColor(kBlue);
         RT[i*3+2]->SetMarkerColor(kRed);
      }

      for(int i = 0; i < 12; i++)
         RT[i]->Draw("l");
   }
   
   Latex.SetTextSize(0.055);
   Latex.SetTextAlign(TextRAlign);

   if(Preset == SD0_PT || Preset == SD7_PT)
   {
      Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 0) / (WorldRMax - RMin), "200 < p_{T,jet} < 300 GeV");
      Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 1) / (WorldRMax - RMin), "180 < p_{T,jet} < 200 GeV");
      Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 2) / (WorldRMax - RMin), "160 < p_{T,jet} < 180 GeV");
      Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 3) / (WorldRMax - RMin), "140 < p_{T,jet} < 160 GeV");
   }
   else
   {
      Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 0) / (WorldRMax - RMin), "50-80%");
      Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 1) / (WorldRMax - RMin), "30-50%");
      Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 2) / (WorldRMax - RMin), "10-30%");
      Latex.DrawLatex(TextRX, (TextRY - RMin + (RMax - RMin) * 3) / (WorldRMax - RMin), "0-10%");
   }

   HWorldRatio.Draw("axis same");

   Legend2.Draw();

   Canvas.cd();

   Canvas.SaveAs((OutputBase + "_Ratio.pdf").c_str());

   // Clean up

   for(int i = 0; i < 16; i++)
   {
      if(G[i] != NULL)
         delete G[i];
      G[i] = NULL;
   }
   for(int i = 0; i < 8; i++)
      if(R[i] != NULL)
         delete R[i];
   
   for(int i = 0; i < 24; i++)
   {
      if(T[i] != NULL)
         delete T[i];
      T[i] = NULL;
   }
   for(int i = 0; i < 12; i++)
      if(RT[i] != NULL)
         delete RT[i];
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










