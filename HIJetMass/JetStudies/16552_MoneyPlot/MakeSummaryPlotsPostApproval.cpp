#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"

#define MASSBINCOUNT 9
#define MASS0BINCOUNT 11
#define ZGBINCOUNT 10
#define DRBINCOUNT 15
#define PTPTBINCOUNT 50

#define TYPE_MASS 1
#define TYPE_MASS0 3
#define TYPE_ZG 0
#define TYPE_DR -1
#define TYPE_DR0 -2
#define TYPE_PTPT 2

#define OriginalPP false

class TheoryRatio;
int main();
void DoGraph(vector<TGraphAsymmErrors *> Gs, string OutputBase, double BinMin, double BinMax,
   bool IsMC, bool IsPT, int Type, string SD,
   vector<TheoryRatio> Extra1 = vector<TheoryRatio>(),
   vector<TheoryRatio> Extra2 = vector<TheoryRatio>(),
   vector<TheoryRatio> Extra3 = vector<TheoryRatio>(),
   vector<TheoryRatio> Extra4 = vector<TheoryRatio>());
void PadSetting(TPad *Pad);
void GraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *G3, TGraphAsymmErrors *G4);
void GraphTidying(TGraphAsymmErrors *G);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio, int BinCount);
void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2);
TheoryRatio GetRatio(string FileName, string Name1, string Name2, int Color, string Label);

class TheoryRatio
{
public:
   TGraphAsymmErrors G;
   string Label;
public:
   TheoryRatio() {}
   TheoryRatio(TH1D *h1, TH1D *h2, int color, string label)
   {
      Initialize(h1, h2, color, label);
   }
   void Initialize(TH1D *h1, TH1D *h2, int color, string label)
   {
      if(h1 == NULL || h2 == NULL)
         return;

      for(int i = 1; i <= h1->GetNbinsX(); i++)
      {
         double x = h1->GetXaxis()->GetBinCenter(i);
         double y1 = h1->GetBinContent(i);
         double y2 = h2->GetBinContent(i);
         double ey1 = h1->GetBinError(i);
         double ey2 = h2->GetBinError(i);
         double l = h1->GetXaxis()->GetBinLowEdge(i);
         double r = h1->GetXaxis()->GetBinUpEdge(i);

         double y = y1 / y2;
         double ey = y * sqrt(ey1 / y1 * ey1 / y1 + ey2 / y2 * ey2 / y2);

         G.SetPoint(i - 1, x, y);
         G.SetPointError(i - 1, x - l, r - x, ey, ey);
      }

      Label = label;

      G.SetLineColor(color);
      G.SetMarkerColor(color);
      G.SetMarkerStyle(21);
      G.SetMarkerSize(5);
      G.SetLineWidth(2);
   }
};

int main()
{
   TFile RatioOutputFile("RatioFile.root", "RECREATE");
   RatioOutputFile.Close();

   string FileName;
   string OutputBase;
   bool IsMC;

   for(int iSD = 0; iSD < 2; iSD++)
   {
      string SD = "0";
      if(iSD == 1)
         SD = "7";

      TheoryRatio JewelOnPT0 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOnSB_C0PT0", "JewelVacSB_C0PT0",
         kGreen, "Jewel (recoil on)");
      TheoryRatio JewelOnPT1 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOnSB_C0PT1", "JewelVacSB_C0PT1",
         kGreen, "Jewel (recoil on)");
      TheoryRatio JewelOnPT2 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOnSB_C0PT2", "JewelVacSB_C0PT2",
         kGreen, "Jewel (recoil on)");
      TheoryRatio JewelOnPT3 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOnSB_C0PT3", "JewelVacSB_C0PT3",
         kGreen, "Jewel (recoil on)");
      TheoryRatio JewelOnPT4 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOnSB_C0PT4", "JewelVacSB_C0PT4",
         kGreen, "Jewel (recoil on)");
      TheoryRatio JewelOnPT5 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOnSB_C0PT5", "JewelVacSB_C0PT5",
         kGreen, "Jewel (recoil on)");
      TheoryRatio JewelOffPT0 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOffSB_C0PT0", "JewelVacSB_C0PT0",
         kGreen + 3, "Jewel (recoil off)");
      TheoryRatio JewelOffPT1 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOffSB_C0PT1", "JewelVacSB_C0PT1",
         kGreen + 3, "Jewel (recoil off)");
      TheoryRatio JewelOffPT2 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOffSB_C0PT2", "JewelVacSB_C0PT2",
         kGreen + 3, "Jewel (recoil off)");
      TheoryRatio JewelOffPT3 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOffSB_C0PT3", "JewelVacSB_C0PT3",
         kGreen + 3, "Jewel (recoil off)");
      TheoryRatio JewelOffPT4 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOffSB_C0PT4", "JewelVacSB_C0PT4",
         kGreen + 3, "Jewel (recoil off)");
      TheoryRatio JewelOffPT5 = GetRatio("PickedPlots_SD" + SD + ".root", "JewelOffSB_C0PT5", "JewelVacSB_C0PT5",
         kGreen + 3, "Jewel (recoil off)");
      TheoryRatio QPythiaPT0 = GetRatio("PickedPlots_SD" + SD + ".root", "QPythiaMedS_C0PT0", "QPythiaVacS_C0PT0",
         kBlue, "QPythia");
      TheoryRatio QPythiaPT1 = GetRatio("PickedPlots_SD" + SD + ".root", "QPythiaMedS_C0PT1", "QPythiaVacS_C0PT1",
         kBlue, "QPythia");
      TheoryRatio QPythiaPT2 = GetRatio("PickedPlots_SD" + SD + ".root", "QPythiaMedS_C0PT2", "QPythiaVacS_C0PT2",
         kBlue, "QPythia");
      TheoryRatio QPythiaPT3 = GetRatio("PickedPlots_SD" + SD + ".root", "QPythiaMedS_C0PT3", "QPythiaVacS_C0PT3",
         kBlue, "QPythia");
      TheoryRatio QPythiaPT4 = GetRatio("PickedPlots_SD" + SD + ".root", "QPythiaMedS_C0PT4", "QPythiaVacS_C0PT4",
         kBlue, "QPythia");
      TheoryRatio QPythiaPT5 = GetRatio("PickedPlots_SD" + SD + ".root", "QPythiaMedS_C0PT5", "QPythiaVacS_C0PT5",
         kBlue, "QPythia");

      for(int iMC = 0; iMC < 2; iMC++)
      {
         if(iMC == 0)
         {
            FileName = "Graphs_SD" + SD + "_DataCentered.root";
            OutputBase = "Plots/DataClosure" + SD;
            IsMC = false;
         }
         else
         {
            FileName = "Graphs_SD" + SD + "_MC.root";
            OutputBase = "Plots/MCClosure" + SD;
            IsMC = true;

            continue;
         }

         TFile FGraphs(FileName.c_str());

         double PTBinEdge[] = {120, 140, 160, 180, 200, 300, 500};
         double CBinEdge[] = {0, 10, 30, 50, 80, 100};

         for(int i = 1; i < 5; i++)
         {
            vector<TGraphAsymmErrors *> Gs(16);
            Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData_3_%d"    , i));
            Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys_3_%d" , i));
            Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear_3_%d"   , i));
            Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys_3_%d", i));
            Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData_2_%d"    , i));
            Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys_2_%d" , i));
            Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear_2_%d"   , i));
            Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys_2_%d", i));
            Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData_1_%d"    , i));
            Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys_1_%d" , i));
            Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear_1_%d"   , i));
            Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys_1_%d", i));
            Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData_0_%d"    , i));
            Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys_0_%d" , i));
            Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear_0_%d"   , i));
            Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys_0_%d", i));

            DoGraph(Gs, OutputBase + Form("_PrettyPlotPTBin%d", i), PTBinEdge[i], PTBinEdge[i+1], IsMC, true, TYPE_MASS, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData_0_%d"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys_0_%d" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear_0_%d"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys_0_%d", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData_1_%d"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys_1_%d" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear_1_%d"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys_1_%d", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData_2_%d"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys_2_%d" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear_2_%d"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys_2_%d", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData_3_%d"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys_3_%d" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear_3_%d"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys_3_%d", i));

            // DoGraph(Gs, OutputBase + Form("_ZGPrettyPlotPTBin%d", i), PTBinEdge[i], PTBinEdge[i+1], IsMC, true, TYPE_ZG, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData_0_%d"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys_0_%d" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear_0_%d"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys_0_%d", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData_1_%d"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys_1_%d" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear_1_%d"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys_1_%d", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData_2_%d"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys_2_%d" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear_2_%d"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys_2_%d", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData_3_%d"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys_3_%d" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear_3_%d"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys_3_%d", i));

            // DoGraph(Gs, OutputBase + Form("_DRPrettyPlotPTBin%d", i), PTBinEdge[i], PTBinEdge[i+1], IsMC, true, TYPE_DR, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData_0_%d"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys_0_%d" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear_0_%d"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys_0_%d", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData_1_%d"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys_1_%d" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear_1_%d"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys_1_%d", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData_2_%d"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys_2_%d" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear_2_%d"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys_2_%d", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData_3_%d"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys_3_%d" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear_3_%d"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys_3_%d", i));

            // DoGraph(Gs, OutputBase + Form("_PTPTPrettyPlotPTBin%d", i), PTBinEdge[i], PTBinEdge[i+1], IsMC, true, TYPE_PTPT, SD);

            Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData0_0_%d"    , i));
            Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys0_0_%d" , i));
            Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear0_0_%d"   , i));
            Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys0_0_%d", i));
            Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData0_1_%d"    , i));
            Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys0_1_%d" , i));
            Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear0_1_%d"   , i));
            Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys0_1_%d", i));
            Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData0_2_%d"    , i));
            Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys0_2_%d" , i));
            Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear0_2_%d"   , i));
            Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys0_2_%d", i));
            Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData0_3_%d"    , i));
            Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys0_3_%d" , i));
            Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear0_3_%d"   , i));
            Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys0_3_%d", i));

            DoGraph(Gs, OutputBase + Form("_0_PrettyPlotPTBin%d", i), PTBinEdge[i], PTBinEdge[i+1], IsMC, true, TYPE_MASS0, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData0_0_%d"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys0_0_%d" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear0_0_%d"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys0_0_%d", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData0_1_%d"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys0_1_%d" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear0_1_%d"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys0_1_%d", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData0_2_%d"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys0_2_%d" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear0_2_%d"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys0_2_%d", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData0_3_%d"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys0_3_%d" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear0_3_%d"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys0_3_%d", i));

            // DoGraph(Gs, OutputBase + Form("_0_ZGPrettyPlotPTBin%d", i), PTBinEdge[i], PTBinEdge[i+1], IsMC, true, TYPE_ZG, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData0_0_%d"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys0_0_%d" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear0_0_%d"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys0_0_%d", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData0_1_%d"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys0_1_%d" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear0_1_%d"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys0_1_%d", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData0_2_%d"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys0_2_%d" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear0_2_%d"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys0_2_%d", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData0_3_%d"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys0_3_%d" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear0_3_%d"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys0_3_%d", i));

            // DoGraph(Gs, OutputBase + Form("_0_DRPrettyPlotPTBin%d", i), PTBinEdge[i], PTBinEdge[i+1], IsMC, true, TYPE_DR0, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData0_0_%d"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys0_0_%d" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear0_0_%d"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys0_0_%d", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData0_1_%d"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys0_1_%d" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear0_1_%d"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys0_1_%d", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData0_2_%d"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys0_2_%d" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear0_2_%d"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys0_2_%d", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData0_3_%d"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys0_3_%d" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear0_3_%d"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys0_3_%d", i));

            // DoGraph(Gs, OutputBase + Form("_0_PTPTPrettyPlotPTBin%d", i), PTBinEdge[i], PTBinEdge[i+1], IsMC, true, TYPE_PTPT, SD);
         }

         for(int i = 0; i < 5; i++)
         {
            vector<TGraphAsymmErrors *> Gs(16);
            Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData_%d_1"    , i));
            Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys_%d_1" , i));
            Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear_%d_1"   , i));
            Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys_%d_1", i));
            Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData_%d_2"    , i));
            Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys_%d_2" , i));
            Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear_%d_2"   , i));
            Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys_%d_2", i));
            Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData_%d_3"    , i));
            Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys_%d_3" , i));
            Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear_%d_3"   , i));
            Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys_%d_3", i));
            Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData_%d_4"    , i));
            Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys_%d_4" , i));
            Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear_%d_4"   , i));
            Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys_%d_4", i));

            if(i == 0)
            {
               vector<TheoryRatio> Extra1;
               vector<TheoryRatio> Extra2;
               vector<TheoryRatio> Extra3;
               vector<TheoryRatio> Extra4;

               Extra1.push_back(JewelOnPT1);
               Extra1.push_back(JewelOffPT1);
               Extra1.push_back(QPythiaPT1);
               Extra2.push_back(JewelOnPT2);
               Extra2.push_back(JewelOffPT2);
               Extra2.push_back(QPythiaPT2);
               Extra3.push_back(JewelOnPT3);
               Extra3.push_back(JewelOffPT3);
               Extra3.push_back(QPythiaPT3);
               Extra4.push_back(JewelOnPT4);
               Extra4.push_back(JewelOffPT4);
               Extra4.push_back(QPythiaPT4);

               DoGraph(Gs, OutputBase + Form("_PrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_MASS, SD, Extra1, Extra2, Extra3, Extra4);
            }
            else
               DoGraph(Gs, OutputBase + Form("_PrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_MASS, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear_%d_1"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys_%d_1", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData_%d_2"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys_%d_2" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear_%d_2"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys_%d_2", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData_%d_3"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys_%d_3" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear_%d_3"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys_%d_3", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData_%d_4"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys_%d_4" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_ZGPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_ZG, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear_%d_1"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys_%d_1", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData_%d_2"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys_%d_2" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear_%d_2"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys_%d_2", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData_%d_3"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys_%d_3" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear_%d_3"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys_%d_3", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData_%d_4"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys_%d_4" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_DRPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_DR, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear_%d_1"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys_%d_1", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData_%d_2"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys_%d_2" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear_%d_2"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys_%d_2", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData_%d_3"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys_%d_3" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear_%d_3"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys_%d_3", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData_%d_4"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys_%d_4" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_PTPTPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_PTPT, SD);

            Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData0_%d_1"    , i));
            Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys0_%d_1" , i));
            Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear0_%d_1"   , i));
            Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys0_%d_1", i));
            Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData0_%d_2"    , i));
            Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys0_%d_2" , i));
            Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear0_%d_2"   , i));
            Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys0_%d_2", i));
            Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData0_%d_3"    , i));
            Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys0_%d_3" , i));
            Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear0_%d_3"   , i));
            Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys0_%d_3", i));
            Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassData0_%d_4"    , i));
            Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassDataSys0_%d_4" , i));
            Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmear0_%d_4"   , i));
            Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("MassSmearSys0_%d_4", i));

            if(i == 0)
            {
               vector<TheoryRatio> Extra1;
               vector<TheoryRatio> Extra2;
               vector<TheoryRatio> Extra3;
               vector<TheoryRatio> Extra4;

               Extra1.push_back(JewelOnPT1);
               Extra1.push_back(JewelOffPT1);
               Extra1.push_back(QPythiaPT1);
               Extra2.push_back(JewelOnPT2);
               Extra2.push_back(JewelOffPT2);
               Extra2.push_back(QPythiaPT2);
               Extra3.push_back(JewelOnPT3);
               Extra3.push_back(JewelOffPT3);
               Extra3.push_back(QPythiaPT3);
               Extra4.push_back(JewelOnPT4);
               Extra4.push_back(JewelOffPT4);
               Extra4.push_back(QPythiaPT4);

               DoGraph(Gs, OutputBase + Form("_0_PrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_MASS0, SD, Extra1, Extra2, Extra3, Extra4);
            }
            else
               DoGraph(Gs, OutputBase + Form("_0_PrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_MASS0, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData0_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys0_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear0_%d_1"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys0_%d_1", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData0_%d_2"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys0_%d_2" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear0_%d_2"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys0_%d_2", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData0_%d_3"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys0_%d_3" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear0_%d_3"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys0_%d_3", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGData0_%d_4"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGDataSys0_%d_4" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmear0_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("ZGSmearSys0_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_0_ZGPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_ZG, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData0_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys0_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear0_%d_1"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys0_%d_1", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData0_%d_2"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys0_%d_2" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear0_%d_2"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys0_%d_2", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData0_%d_3"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys0_%d_3" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear0_%d_3"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys0_%d_3", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRData0_%d_4"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRDataSys0_%d_4" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmear0_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("DRSmearSys0_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_0_DRPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_DR0, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData0_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys0_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear0_%d_1"   , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys0_%d_1", i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData0_%d_2"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys0_%d_2" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear0_%d_2"   , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys0_%d_2", i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData0_%d_3"    , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys0_%d_3" , i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear0_%d_3"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys0_%d_3", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTData0_%d_4"    , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTDataSys0_%d_4" , i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmear0_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PTPTSmearSys0_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_0_PTPTPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_PTPT, SD);
         }

         FGraphs.Close();
      }
   }

   return 0;
}

void DoGraph(vector<TGraphAsymmErrors *> Gs, string OutputBase, double BinMin, double BinMax,
   bool IsMC, bool IsPT, int Type, string SD,
   vector<TheoryRatio> Extra1, vector<TheoryRatio> Extra2, vector<TheoryRatio> Extra3, vector<TheoryRatio> Extra4)
{
   bool LogMass = false;

   if(Gs.size() != 16)
      return;

   TFile RatioOutputFile("RatioFile.root", "UPDATE");

   TGraphAsymmErrors *G1Data     = Gs[0];
   TGraphAsymmErrors *G1DataSys  = Gs[1];
   TGraphAsymmErrors *G1Smear    = Gs[2];
   TGraphAsymmErrors *G1SmearSys = Gs[3];
   TGraphAsymmErrors *G2Data     = Gs[4];
   TGraphAsymmErrors *G2DataSys  = Gs[5];
   TGraphAsymmErrors *G2Smear    = Gs[6];
   TGraphAsymmErrors *G2SmearSys = Gs[7];
   TGraphAsymmErrors *G3Data     = Gs[8];
   TGraphAsymmErrors *G3DataSys  = Gs[9];
   TGraphAsymmErrors *G3Smear    = Gs[10];
   TGraphAsymmErrors *G3SmearSys = Gs[11];
   TGraphAsymmErrors *G4Data     = Gs[12];
   TGraphAsymmErrors *G4DataSys  = Gs[13];
   TGraphAsymmErrors *G4Smear    = Gs[14];
   TGraphAsymmErrors *G4SmearSys = Gs[15];

   GraphSetting(G1Data, G1DataSys, G1Smear, G1SmearSys);
   GraphSetting(G2Data, G2DataSys, G2Smear, G2SmearSys);
   GraphSetting(G3Data, G3DataSys, G3Smear, G3SmearSys);
   GraphSetting(G4Data, G4DataSys, G4Smear, G4SmearSys);

   GraphTidying(G1DataSys);   GraphTidying(G1SmearSys);
   GraphTidying(G2DataSys);   GraphTidying(G2SmearSys);
   GraphTidying(G3DataSys);   GraphTidying(G3SmearSys);
   GraphTidying(G4DataSys);   GraphTidying(G4SmearSys);

   TGraphAsymmErrors G1Ratio, G1RatioSys;
   TGraphAsymmErrors G2Ratio, G2RatioSys;
   TGraphAsymmErrors G3Ratio, G3RatioSys;
   TGraphAsymmErrors G4Ratio, G4RatioSys;

   int BinCount = 0;
   if(Type == TYPE_MASS)
      BinCount = MASSBINCOUNT;
   if(Type == TYPE_MASS0)
      BinCount = MASS0BINCOUNT;
   if(Type == TYPE_ZG)
      BinCount = ZGBINCOUNT;
   if(Type == TYPE_DR)
      BinCount = DRBINCOUNT;
   if(Type == TYPE_DR0)
      BinCount = DRBINCOUNT;
   if(Type == TYPE_PTPT)
      BinCount = PTPTBINCOUNT;

   Division(G1Data, G1Smear, G1Ratio, BinCount);
   Division(G1DataSys, G1SmearSys, G1RatioSys, BinCount);
   Division(G2Data, G2Smear, G2Ratio, BinCount);
   Division(G2DataSys, G2SmearSys, G2RatioSys, BinCount);
   Division(G3Data, G3Smear, G3Ratio, BinCount);
   Division(G3DataSys, G3SmearSys, G3RatioSys, BinCount);
   Division(G4Data, G4Smear, G4Ratio, BinCount);
   Division(G4DataSys, G4SmearSys, G4RatioSys, BinCount);

   RatioGraphSetting(&G1Ratio, &G1RatioSys);
   RatioGraphSetting(&G2Ratio, &G2RatioSys);
   RatioGraphSetting(&G3Ratio, &G3RatioSys);
   RatioGraphSetting(&G4Ratio, &G4RatioSys);

   if(IsPT == false)
   {
      cout << G1Ratio.GetName() << " " << G1RatioSys.GetName() << endl;
      cout << G2Ratio.GetName() << " " << G2RatioSys.GetName() << endl;
      cout << G3Ratio.GetName() << " " << G3RatioSys.GetName() << endl;
      cout << G4Ratio.GetName() << " " << G4RatioSys.GetName() << endl;

      G1Ratio.SetName(Form("%s_SD%s", G1Ratio.GetName(), SD.c_str()));
      G2Ratio.SetName(Form("%s_SD%s", G2Ratio.GetName(), SD.c_str()));
      G3Ratio.SetName(Form("%s_SD%s", G3Ratio.GetName(), SD.c_str()));
      G4Ratio.SetName(Form("%s_SD%s", G4Ratio.GetName(), SD.c_str()));

      G1Ratio.Write();
      G2Ratio.Write();
      G3Ratio.Write();
      G4Ratio.Write();
   
      if(string(G1Ratio.GetName()) == "Ratio_ZGData_0_1_ZGSmear_0_1_SD0")
      {
         TGraphAsymmErrors *G = (TGraphAsymmErrors *)G1Ratio.Clone("Ratio_ZGData_0_1_ZGSmear_0_1_SD0_Corrected");
         
         for(int i = 0; i < G->GetN(); i++)
         {
            double x, y;
            G->GetPoint(i, x, y);

            double Correction = 1 + 0.2 / 0.3 * (x - 0.2);
            G->SetPoint(i, x, y / Correction);
         }

         G->Write();
      }

      if(Type == TYPE_MASS || Type == TYPE_MASS0)
      {
         G1RatioSys.SetName(Form("%s_SD%s", G1RatioSys.GetName(), SD.c_str()));
         G2RatioSys.SetName(Form("%s_SD%s", G2RatioSys.GetName(), SD.c_str()));
         G3RatioSys.SetName(Form("%s_SD%s", G3RatioSys.GetName(), SD.c_str()));
         G4RatioSys.SetName(Form("%s_SD%s", G4RatioSys.GetName(), SD.c_str()));

         G1RatioSys.Write();
         G2RatioSys.Write();
         G3RatioSys.Write();
         G4RatioSys.Write();
      }
   }

   double BorderWidth = 400;
   double BorderHeight = 350;
   double PadWidth = 1000;
   double PadHeight = 1000;
   double RatioHeight = 1000;

   double TotalHeight = RatioHeight + PadHeight + BorderHeight * 2;
   double TotalWidth = PadWidth * 4 + BorderWidth * 2;

   double TextSizeFactor = (500 + 1000 + 350 * 2) / TotalHeight;

   double PadLowY  = (BorderHeight + RatioHeight) / TotalHeight;
   double PadHighY = (BorderHeight + RatioHeight + PadHeight) / TotalHeight;
   double PadRatioLowY  = BorderHeight / TotalHeight;

   double WorldMin = 0.011;
   double WorldMax = 500;
   double MassMin = 0;
   double MassMax = 0.26;
   double RatioMin = 0;
   double RatioMax = 4.999;

   if(Type == TYPE_MASS && SD == "0" && LogMass == false)
   {
      WorldMin = 0;
      WorldMax = 14.5;
   }
   if(Type == TYPE_MASS && SD == "7" && LogMass == false)
   {
      WorldMin = 0;
      WorldMax = 30;

      RatioMax = 4.999;
   }
   if(Type == TYPE_MASS0 && SD == "0" && LogMass == false)
   {
      WorldMin = 0;
      WorldMax = 14.5;

      MassMax = 0.27;
      RatioMax = 4.999;
   }
   if(Type == TYPE_MASS0 && SD == "7" && LogMass == false)
   {
      WorldMin = 0;
      WorldMax = 30;

      MassMax = 0.27;
   }

   // if(Type == TYPE_MASS0 && SD == "0" && LogMass == false)
   //    MassMax = 0.19;
   // if(Type == TYPE_MASS0 && SD == "7" && LogMass == false)
   //    MassMax = 0.19;

   if(Type == TYPE_ZG && SD == "0")
   {
      WorldMin = 1e-3;
      WorldMax = 12;
      MassMin = 0;
      MassMax = 0.5;
      RatioMin = 0;
      RatioMax = 2.5;
   }
   if(Type == TYPE_ZG && SD == "7")
   {
      WorldMin = 1e-3;
      WorldMax = 8;
      MassMin = 0;
      MassMax = 0.5;
      RatioMin = 0;
      RatioMax = 2.5;
   }
   if(Type == TYPE_DR && SD == "0")
   {
      WorldMin = 1e-3;
      WorldMax = 15;
      MassMin = 0.1;
      MassMax = 0.5;
      RatioMin = 0;
      RatioMax = 2.5;
   }
   if(Type == TYPE_DR && SD == "7")
   {
      WorldMin = 1e-3;
      WorldMax = 8;
      MassMin = 0.1;
      MassMax = 0.5;
      RatioMin = 0;
      RatioMax = 2.5;
   }
   if(Type == TYPE_DR0)
   {
      WorldMin = 1e-3;
      WorldMax = 15;
      MassMin = 0.0;
      MassMax = 0.5;
      RatioMin = 0;
      RatioMax = 2.5;
   }

   if(Type == TYPE_PTPT && SD == "0")
   {
      WorldMin = 1e-4;
      WorldMax = 10000;
      MassMin = 0.5;
      MassMax = 0.999;
      RatioMin = 0.0;
      RatioMax = 2.5;
   }
   if(Type == TYPE_PTPT && SD == "7")
   {
      WorldMin = 1e-4;
      WorldMax = 10000;
      MassMin = 0.0;
      MassMax = 0.999;
      RatioMin = 0.0;
      RatioMax = 2.5;
   }

   TGraph GLine;
   GLine.SetPoint(0, MassMin, 1);
   GLine.SetPoint(1, MassMax, 1);

   gStyle->SetPaperSize(TotalWidth / 170, TotalHeight / 170);

   TCanvas Canvas("Canvas", "", TotalWidth, TotalHeight);

   TPad *Pad1 = new TPad("Pad1", "", (BorderWidth + PadWidth * 0) / TotalWidth, PadLowY, (BorderWidth + PadWidth * 1) / TotalWidth, PadHighY);
   TPad *Pad2 = new TPad("Pad2", "", (BorderWidth + PadWidth * 1) / TotalWidth, PadLowY, (BorderWidth + PadWidth * 2) / TotalWidth, PadHighY);
   TPad *Pad3 = new TPad("Pad3", "", (BorderWidth + PadWidth * 2) / TotalWidth, PadLowY, (BorderWidth + PadWidth * 3) / TotalWidth, PadHighY);
   TPad *Pad4 = new TPad("Pad4", "", (BorderWidth + PadWidth * 3) / TotalWidth, PadLowY, (BorderWidth + PadWidth * 4) / TotalWidth, PadHighY);

   TPad *Pad5 = new TPad("Pad5", "", (BorderWidth + PadWidth * 0) / TotalWidth, PadRatioLowY, (BorderWidth + PadWidth * 1) / TotalWidth, PadLowY);
   TPad *Pad6 = new TPad("Pad6", "", (BorderWidth + PadWidth * 1) / TotalWidth, PadRatioLowY, (BorderWidth + PadWidth * 2) / TotalWidth, PadLowY);
   TPad *Pad7 = new TPad("Pad7", "", (BorderWidth + PadWidth * 2) / TotalWidth, PadRatioLowY, (BorderWidth + PadWidth * 3) / TotalWidth, PadLowY);
   TPad *Pad8 = new TPad("Pad8", "", (BorderWidth + PadWidth * 3) / TotalWidth, PadRatioLowY, (BorderWidth + PadWidth * 4) / TotalWidth, PadLowY);

   PadSetting(Pad1);
   PadSetting(Pad2);
   PadSetting(Pad3);
   PadSetting(Pad4);

   PadSetting(Pad5);
   PadSetting(Pad6);
   PadSetting(Pad7);
   PadSetting(Pad8);

   TH2D HWorld("HWorld", ";;", 100, MassMin, MassMax, 100, WorldMin, WorldMax);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetLabelSize(0);
   HWorld.GetYaxis()->SetLabelSize(0);

   TH2D HWorldRatio("HWorldRatio", ";;", 100, MassMin, MassMax, 100, RatioMin, RatioMax);
   HWorldRatio.SetStats(0);
   HWorldRatio.GetXaxis()->SetLabelSize(0);
   HWorldRatio.GetYaxis()->SetLabelSize(0);
   HWorldRatio.GetXaxis()->SetTickLength(0.06);
   HWorldRatio.GetYaxis()->SetTickLength(0.03);
   HWorldRatio.GetYaxis()->SetNdivisions(505);

   TGraph GData, GSmear;
   GData.SetLineColor(G1Data->GetLineColor());
   GData.SetLineWidth(G1Data->GetLineWidth());
   GData.SetMarkerColor(G1Data->GetMarkerColor());
   GData.SetMarkerStyle(G1Data->GetMarkerStyle());
   GData.SetMarkerSize(G1Data->GetMarkerSize());
   if(G1DataSys)   GData.SetFillStyle(G1DataSys->GetFillStyle());
   if(G1DataSys)   GData.SetFillColor(G1DataSys->GetFillColor());
   else            GData.SetFillColor(kWhite);
   GSmear.SetLineColor(G1Smear->GetLineColor());
   GSmear.SetLineWidth(G1Smear->GetLineWidth());
   GSmear.SetMarkerColor(G1Smear->GetMarkerColor());
   GSmear.SetMarkerStyle(G1Smear->GetMarkerStyle());
   GSmear.SetMarkerSize(G1Smear->GetMarkerSize());
   if(G1SmearSys)  GSmear.SetFillStyle(G1SmearSys->GetFillStyle());
   if(G1SmearSys)  GSmear.SetFillColor(G1SmearSys->GetFillColor());
   else            GSmear.SetFillColor(kWhite);

   if(GData.GetFillStyle() == 3454)
      GData.SetFillStyle(3154);
   if(GSmear.GetFillStyle() == 3545)
      GSmear.SetFillStyle(3145);

   Pad1->cd();
   HWorld.Draw("");
   if(G1DataSys)    G1DataSys->Draw("2");
   if(G1SmearSys)   G1SmearSys->Draw("2");
   G1Data->Draw("p");
   G1Smear->Draw("p");
   HWorld.Draw("axis same");
   if(Type == TYPE_MASS && LogMass == true)
      Pad1->SetLogy();
   if(Type == TYPE_MASS0 && LogMass == true)
      Pad1->SetLogy();
   if(Type == TYPE_PTPT)
      Pad1->SetLogy();
   Pad1->Update();

   Pad2->cd();
   HWorld.Draw("");
   if(G2DataSys)    G2DataSys->Draw("2");
   if(G2SmearSys)   G2SmearSys->Draw("2");
   G2Data->Draw("p");
   G2Smear->Draw("p");
   HWorld.Draw("axis same");
   if(Type == TYPE_MASS && LogMass == true)
      Pad2->SetLogy();
   if(Type == TYPE_MASS0 && LogMass == true)
      Pad2->SetLogy();
   if(Type == TYPE_PTPT)
      Pad2->SetLogy();
   Pad2->Update();

   Pad3->cd();
   HWorld.Draw("");
   if(G3DataSys)    G3DataSys->Draw("2");
   if(G3SmearSys)   G3SmearSys->Draw("2");
   G3Data->Draw("p");
   G3Smear->Draw("p");
   HWorld.Draw("axis same");
   if(Type == TYPE_MASS && LogMass == true)
      Pad3->SetLogy();
   if(Type == TYPE_MASS0 && LogMass == true)
      Pad3->SetLogy();
   if(Type == TYPE_PTPT)
      Pad3->SetLogy();
   Pad3->Update();

   Pad4->cd();
   HWorld.Draw("");
   if(G4DataSys)    G4DataSys->Draw("2");
   if(G4SmearSys)   G4SmearSys->Draw("2");
   G4Data->Draw("p");
   G4Smear->Draw("p");
   HWorld.Draw("axis same");
   if(Type == TYPE_MASS && LogMass == true)
      Pad4->SetLogy();
   if(Type == TYPE_MASS0 && LogMass == true)
      Pad4->SetLogy();
   if(Type == TYPE_PTPT)
      Pad4->SetLogy();
   Pad4->Update();

   Pad5->cd();
   HWorldRatio.Draw("");
   if(G1SmearSys)   G1RatioSys.Draw("2");
   if(Extra1.size() > 0)
      for(int i = 0; i < (int)Extra1.size(); i++)
         Extra1[i].G.Draw("p");
   G1Ratio.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad5->SetLogy();
   Pad5->Update();

   Pad6->cd();
   HWorldRatio.Draw("");
   if(G2SmearSys)   G2RatioSys.Draw("2");
   if(Extra2.size() > 0)
      for(int i = 0; i < (int)Extra2.size(); i++)
         Extra2[i].G.Draw("p");
   G2Ratio.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad6->SetLogy();
   Pad6->Update();

   Pad7->cd();
   HWorldRatio.Draw("");
   if(G3SmearSys)   G3RatioSys.Draw("2");
   if(Extra3.size() > 0)
      for(int i = 0; i < (int)Extra3.size(); i++)
         Extra3[i].G.Draw("p");
   G3Ratio.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad7->SetLogy();
   Pad7->Update();

   Pad8->cd();
   HWorldRatio.Draw("");
   if(G4SmearSys)   G4RatioSys.Draw("2");
   if(Extra4.size() > 0)
      for(int i = 0; i < (int)Extra4.size(); i++)
         Extra4[i].G.Draw("p");
   G4Ratio.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad8->SetLogy();
   Pad8->Update();

   Pad1->cd();
   HWorld.Draw("axis same");
   Pad1->Update();

   Pad2->cd();
   HWorld.Draw("axis same");
   Pad2->Update();

   Pad3->cd();
   HWorld.Draw("axis same");
   Pad3->Update();

   Pad4->cd();
   HWorld.Draw("axis same");
   Pad4->Update();

   Pad5->cd();
   HWorldRatio.Draw("axis same");
   Pad5->Update();

   Pad6->cd();
   HWorldRatio.Draw("axis same");
   Pad6->Update();

   Pad7->cd();
   HWorldRatio.Draw("axis same");
   Pad7->Update();

   Pad8->cd();
   HWorldRatio.Draw("axis same");
   Pad8->Update();

   Canvas.cd();

   string Scale = "G";
   if(Type == TYPE_ZG || Type == TYPE_DR || Type == TYPE_DR0)
      Scale = "";
   if(Type == TYPE_MASS && LogMass == false)
      Scale = "";
   if(Type == TYPE_MASS0 && LogMass == false)
      Scale = "";
   TGaxis LeftAxis1(BorderWidth / TotalWidth, (BorderHeight + RatioHeight) / TotalHeight, BorderWidth / TotalWidth, (BorderHeight + RatioHeight + PadHeight) / TotalHeight,
         WorldMin, WorldMax, 50510, Scale.c_str());
   LeftAxis1.SetName("LeftAxis1");
   LeftAxis1.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(SD Mass/PT)}");
   if(Type == TYPE_MASS)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(M_{g} / p_{T,jet})}");
   if(Type == TYPE_MASS0)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(M_{g} / p_{T,jet})}");
   if(Type == TYPE_ZG)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d z_{g}}");
   if(Type == TYPE_DR)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d #DeltaR}");
   if(Type == TYPE_DR0)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d #DeltaR}");
   if(Type == TYPE_PTPT)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(p_{T,g} / p_{T,jet})}");
   LeftAxis1.SetTextFont(42);
   LeftAxis1.SetLabelFont(42);
   LeftAxis1.CenterTitle(true);
   LeftAxis1.SetTitleOffset(0.85);
   LeftAxis1.Draw();

   TGaxis LeftAxis2(BorderWidth / TotalWidth, BorderHeight / TotalHeight, BorderWidth / TotalWidth, (BorderHeight + RatioHeight) / TotalHeight,
         RatioMin, RatioMax, 1005, "");
   // TGaxis LeftAxis2(Border / TotalWidth, Border / TotalHeight, Border / TotalWidth, (Border + RatioHeight) / TotalHeight,
   //       RatioMin, RatioMax, 1005, "G");
   LeftAxis2.SetName("LeftAxis2");
   LeftAxis2.SetLineWidth(0);
   if(OriginalPP == true)
      LeftAxis2.SetTitle("#frac{PbPb}{Original pp}");
   else
      LeftAxis2.SetTitle("#frac{PbPb}{Smeared pp}");
   LeftAxis2.SetTextFont(42);
   LeftAxis2.SetLabelFont(42);
   LeftAxis2.CenterTitle(true);
   LeftAxis2.SetTitleOffset(0.85);
   LeftAxis2.Draw();

   int BottomTick = 1005;
   if(Type == TYPE_MASS0)
      BottomTick = 505;

   TGaxis BottomAxis1((BorderWidth + PadWidth * 0) / TotalWidth, BorderHeight / TotalHeight, (BorderWidth + PadWidth * 1) / TotalWidth, BorderHeight / TotalHeight,
         MassMin, MassMax - 0.00001, BottomTick, "");
   BottomAxis1.SetName("BottomAxis1");
   BottomAxis1.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    BottomAxis1.SetTitle("SD Mass / Jet PT");
   if(Type == TYPE_MASS)
      BottomAxis1.SetTitle("M_{g} / p_{T,jet}");
   if(Type == TYPE_MASS0)
      BottomAxis1.SetTitle("M_{g} / p_{T,jet}");
   if(Type == TYPE_ZG)
      BottomAxis1.SetTitle("z_{g}");
   if(Type == TYPE_DR)
      BottomAxis1.SetTitle("#DeltaR");
   if(Type == TYPE_DR0)
      BottomAxis1.SetTitle("#DeltaR");
   if(Type == TYPE_PTPT)
      BottomAxis1.SetTitle("p_{T,g} / p_{T,jet}");
   BottomAxis1.SetTextFont(42);
   BottomAxis1.SetLabelFont(42);
   BottomAxis1.CenterTitle(true);
   BottomAxis1.Draw();

   TGaxis BottomAxis2((BorderWidth + PadWidth * 1) / TotalWidth, BorderHeight / TotalHeight, (BorderWidth + PadWidth * 2) / TotalWidth, BorderHeight / TotalHeight,
         MassMin, MassMax - 0.00001, BottomTick, "");
   BottomAxis2.SetName("BottomAxis2");
   BottomAxis2.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    BottomAxis2.SetTitle("SD Mass / Jet PT");
   if(Type == TYPE_MASS)
      BottomAxis2.SetTitle("M_{g} / p_{T,jet}");
   if(Type == TYPE_MASS0)
      BottomAxis2.SetTitle("M_{g} / p_{T,jet}");
   if(Type == TYPE_ZG)
      BottomAxis2.SetTitle("z_{g}");
   if(Type == TYPE_DR)
      BottomAxis2.SetTitle("#DeltaR");
   if(Type == TYPE_DR0)
      BottomAxis2.SetTitle("#DeltaR");
   if(Type == TYPE_PTPT)
      BottomAxis2.SetTitle("p_{T,g} / p_{T,jet}");
   BottomAxis2.SetTextFont(42);
   BottomAxis2.SetLabelFont(42);
   BottomAxis2.CenterTitle(true);
   BottomAxis2.Draw();

   TGaxis BottomAxis3((BorderWidth + PadWidth * 2) / TotalWidth, BorderHeight / TotalHeight, (BorderWidth + PadWidth * 3) / TotalWidth, BorderHeight / TotalHeight,
         MassMin, MassMax - 0.00001, BottomTick, "");
   BottomAxis3.SetName("BottomAxis3");
   BottomAxis3.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    BottomAxis3.SetTitle("SD Mass / Jet PT");
   if(Type == TYPE_MASS)
      BottomAxis3.SetTitle("M_{g} / p_{T,jet}");
   if(Type == TYPE_MASS0)
      BottomAxis3.SetTitle("M_{g} / p_{T,jet}");
   if(Type == TYPE_ZG)
      BottomAxis3.SetTitle("z_{g}");
   if(Type == TYPE_DR)
      BottomAxis3.SetTitle("#DeltaR");
   if(Type == TYPE_DR0)
      BottomAxis3.SetTitle("#DeltaR");
   if(Type == TYPE_PTPT)
      BottomAxis3.SetTitle("p_{T,g} / p_{T,jet}");
   BottomAxis3.SetTextFont(42);
   BottomAxis3.SetLabelFont(42);
   BottomAxis3.CenterTitle(true);
   BottomAxis3.Draw();

   TGaxis BottomAxis4((BorderWidth + PadWidth * 3) / TotalWidth, BorderHeight / TotalHeight, (BorderWidth + PadWidth * 4) / TotalWidth, BorderHeight / TotalHeight,
         MassMin, MassMax, BottomTick, "");
   BottomAxis4.SetName("BottomAxis4");
   BottomAxis4.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    BottomAxis4.SetTitle("SD Mass / Jet PT");
   if(Type == TYPE_MASS)
      BottomAxis4.SetTitle("M_{g} / p_{T,jet}");
   if(Type == TYPE_MASS0)
      BottomAxis4.SetTitle("M_{g} / p_{T,jet}");
   if(Type == TYPE_ZG)
      BottomAxis4.SetTitle("z_{g}");
   if(Type == TYPE_DR)
      BottomAxis4.SetTitle("#DeltaR");
   if(Type == TYPE_DR0)
      BottomAxis4.SetTitle("#DeltaR");
   if(Type == TYPE_PTPT)
      BottomAxis4.SetTitle("p_{T,g} / p_{T,jet}");
   BottomAxis4.SetTextFont(42);
   BottomAxis4.SetLabelFont(42);
   BottomAxis4.CenterTitle(true);
   BottomAxis4.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035 * TextSizeFactor);

   Latex.SetTextSize(0.06 * TextSizeFactor);
   Latex.SetTextAlign(10);
   if(Type == TYPE_MASS || Type == TYPE_MASS0)
      Latex.DrawLatex(BorderWidth / TotalWidth, (BorderHeight + RatioHeight + PadHeight) / TotalHeight + 0.005, "#font[62]{CMS}");
   else                                                                                           
      Latex.DrawLatex(BorderWidth / TotalWidth, (BorderHeight + RatioHeight + PadHeight) / TotalHeight + 0.005, "#font[62]{CMS} #font[52]{Internal}");

   Latex.SetTextSize(0.035 * TextSizeFactor);
   Latex.SetTextAlign(30);
   if(IsMC == false)
      Latex.DrawLatex((BorderWidth + PadWidth * 4) / TotalWidth, (BorderHeight + RatioHeight + PadHeight + 0.000) / TotalHeight, "PbPb 404 #mub^{-1} (5.02 TeV), pp 27.4 pb^{-1} (5.02 TeV)");
   else
      Latex.DrawLatex((BorderWidth + PadWidth * 4) / TotalWidth, (BorderHeight + RatioHeight + PadHeight + 0.000) / TotalHeight, "Simulation (5.02 TeV)");

   Latex.SetTextSize(0.035 * TextSizeFactor);
   Latex.SetTextAlign(30);
   if(SD == "0")
      Latex.DrawLatex((BorderWidth + PadWidth * 4) / TotalWidth, (BorderHeight + RatioHeight + PadHeight + BorderHeight * 0.2) / TotalHeight, "anti-kt R = 0.4, |#eta_{jet}| < 1.3, Soft drop z_{cut} = 0.1, #beta = 0.0, #DeltaR_{12} > 0.1");
   else
      Latex.DrawLatex((BorderWidth + PadWidth * 4) / TotalWidth, (BorderHeight + RatioHeight + PadHeight + BorderHeight * 0.2) / TotalHeight, "anti-kt R = 0.4, |#eta_{jet}| < 1.3, Soft drop z_{cut} = 0.5, #beta = 1.5, #DeltaR_{12} > 0.1");

   TLegend Legend((BorderWidth + PadWidth * 0.40) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.85) / TotalHeight, (BorderWidth + PadWidth * 0.85) / TotalWidth, (BorderHeight + RatioHeight + 0.65 * PadHeight) / TotalHeight);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035 * TextSizeFactor);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&GData, "PbPb", "plf");
   if(OriginalPP == true)
      Legend.AddEntry(&GSmear, "Original pp", "plf");
   else
      Legend.AddEntry(&GSmear, "Smeared pp", "plf");
   Legend.Draw();

   TLegend Legend2((BorderWidth + PadWidth * 1.30) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.85) / TotalHeight, (BorderWidth + PadWidth * 1.75) / TotalWidth, (BorderHeight + RatioHeight + 0.55 * PadHeight) / TotalHeight);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035 * TextSizeFactor);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   if(Extra1.size() > 0)
   {
      for(int i = 0; i < (int)Extra1.size(); i++)
         Legend2.AddEntry(&Extra1[i].G, Extra1[i].Label.c_str(), "pl");
      Legend2.Draw();
   }

   Latex.SetTextAlign(13);
   if(IsPT == true)
   {
      Latex.DrawLatex((BorderWidth + PadWidth * 3.07) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.97) / TotalHeight, "Centrality: 0-10%");
      Latex.DrawLatex((BorderWidth + PadWidth * 2.07) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.97) / TotalHeight, "Centrality: 10-30%");
      Latex.DrawLatex((BorderWidth + PadWidth * 1.07) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.97) / TotalHeight, "Centrality: 30-50%");
      Latex.DrawLatex((BorderWidth + PadWidth * 0.07) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.97) / TotalHeight, "Centrality: 50-80%");
   }
   else
   {
      Latex.DrawLatex((BorderWidth + PadWidth * 0.07) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.97) / TotalHeight, "140 < p_{T,jet} < 160 GeV");
      Latex.DrawLatex((BorderWidth + PadWidth * 1.07) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.97) / TotalHeight, "160 < p_{T,jet} < 180 GeV");
      Latex.DrawLatex((BorderWidth + PadWidth * 2.07) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.97) / TotalHeight, "180 < p_{T,jet} < 200 GeV");
      Latex.DrawLatex((BorderWidth + PadWidth * 3.07) / TotalWidth, (BorderHeight + RatioHeight + PadHeight * 0.97) / TotalHeight, "200 < p_{T,jet} < 300 GeV");
   }

   Latex.SetTextAlign(20);
   if(IsPT == true)
      Latex.DrawLatex((BorderWidth + PadWidth * 1.50) / TotalWidth, (BorderHeight + RatioHeight + PadHeight + BorderHeight * 0.0) / TotalHeight, Form("%.0f < p_{T,jet} < %.0f GeV", BinMin, BinMax));
   else
      Latex.DrawLatex((BorderWidth + PadWidth * 1.50) / TotalWidth, (BorderHeight + RatioHeight + PadHeight + BorderHeight * 0.0) / TotalHeight, Form("Centrality: %.0f-%.0f%%", BinMin, BinMax));

   Canvas.SaveAs(Form("%s.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.C"  , OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.pdf", OutputBase.c_str()));

   RatioOutputFile.Close();
}

void PadSetting(TPad *Pad)
{
   Pad->SetTopMargin(0);
   Pad->SetRightMargin(0);
   Pad->SetBottomMargin(0);
   Pad->SetLeftMargin(0);

   Pad->Draw();
}

void GraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *G3, TGraphAsymmErrors *G4)
{
   if(G1 != NULL)
   {
      // was kRed
      G1->SetLineColor(kRed + 1);
      G1->SetLineWidth(2);
      G1->SetMarkerColor(kRed + 1);
      G1->SetMarkerStyle(21);
      G1->SetMarkerSize(5);
   }

   if(G2 != NULL)
   {
      // was kMagenta - 9, 3454
      G2->SetLineWidth(0);
      G2->SetFillColor(kRed - 9);
      G2->SetMarkerColor(kRed + 1);
      G2->SetMarkerStyle(21);
      G2->SetMarkerSize(5);
   }

   if(G3 != NULL)
   {
      // was kBlue
      G3->SetLineColor(kBlack);
      G3->SetLineWidth(2);
      G3->SetMarkerColor(kBlack);
      G3->SetMarkerStyle(20);
      G3->SetMarkerSize(5);
   }

   if(G4 != NULL)
   {
      // was kCyan - 9
      G4->SetLineWidth(0);
      G4->SetFillStyle(3545);
      G4->SetFillColor(kBlack);
      G4->SetMarkerColor(kBlack);
      G4->SetMarkerStyle(20);
      G4->SetMarkerSize(5);
   }
}

void GraphTidying(TGraphAsymmErrors *G)
{
   if(G == NULL)
      return;

   double F = 1.2;

   for(int i = 0; i < G->GetN(); i++)
   {
      G->SetPointEYlow(i, G->GetErrorYlow(i) * F);
      G->SetPointEYhigh(i, G->GetErrorYhigh(i) * F);
   }
}

void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio, int BinCount)
{
   if(G1 == NULL || G2 == NULL)
      return;

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
         int N = GRatio.GetN();
         GRatio.SetPoint(N, x1, ratio);
         GRatio.SetPointError(N, xl1, xh1, yl, yh);
      }
      // else
      // {
      //    GRatio.SetPoint(i, 0, 0);
      //    GRatio.SetPointError(i, 0, 0, 0, 0);
      // }
   }

   GRatio.SetName(Form("Ratio_%s_%s", G1->GetName(), G2->GetName()));

   // GRatio.Print();
}

void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2)
{
   if(G1 != NULL)
   {
      G1->SetLineColor(kBlack);
      G1->SetLineWidth(2);
      G1->SetMarkerColor(kBlack);
      G1->SetMarkerStyle(20);
      G1->SetMarkerSize(5);
   }

   if(G2 != NULL)
   {
      // was kBlue - 9
      G2->SetLineWidth(0);
      G2->SetFillColor(kGray);
      G2->SetMarkerStyle(20);
      G2->SetMarkerSize(5);
   }
}

TheoryRatio GetRatio(string FileName, string Name1, string Name2, int Color, string Label)
{
   TheoryRatio Result;

   TFile File(FileName.c_str());

   Result.Initialize((TH1D *)File.Get(Name1.c_str()), (TH1D *)File.Get(Name2.c_str()), Color, Label);

   File.Close();

   return Result;
}




