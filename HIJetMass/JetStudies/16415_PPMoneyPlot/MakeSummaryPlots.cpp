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
#define ZGBINCOUNT 10
#define DRBINCOUNT 15
#define PTPTBINCOUNT 50

#define TYPE_MASS 1
#define TYPE_MASS0 3
#define TYPE_ZG 0
#define TYPE_DR -1
#define TYPE_DR0 -2
#define TYPE_PTPT 2

int main();
void DoGraph(vector<TGraphAsymmErrors *> Gs, string OutputBase, double BinMin, double BinMax, bool IsMC, bool IsPT, int Type, string SD);
void PadSetting(TPad *Pad);
void GraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *G3, TGraphAsymmErrors *G4,
      TGraphAsymmErrors *G5, TGraphAsymmErrors *G6);
void GraphTidying(TGraphAsymmErrors *G);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio, int BinCount);
void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, int MC);

int main()
{
   string FileName;
   string OutputBase;
   bool IsMC;

   for(int iSD = 0; iSD < 2; iSD++)
   {
      string SD = "0";
      if(iSD == 1)
         SD = "7";

      for(int iMC = 0; iMC < 1; iMC++)   // no different types here
      {
         FileName = "Graphs_SD" + SD + "_Picked.root";
         OutputBase = "Plots/Data" + SD;
         IsMC = false;

         TFile FGraphs(FileName.c_str());

         double PTBinEdge[] = {120, 140, 160, 180, 200, 300, 500};
         double CBinEdge[] = {0, 10, 30, 50, 80, 100};

         for(int i = 4; i < 5; i++)   // This is pp.  Only last centrality bin is around.
         {
            vector<TGraphAsymmErrors *> Gs(24);
            Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassData_%d_1"    , i));
            Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassDataSys_%d_1" , i));
            Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassData_%d_2"    , i));
            Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassDataSys_%d_2" , i));
            Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassData_%d_3"    , i));
            Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassDataSys_%d_3" , i));
            Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassData_%d_4"    , i));
            Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassDataSys_%d_4" , i));
            Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassData_%d_1"   , i));
            Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassDataSys_%d_1", i));
            Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassData_%d_2"   , i));
            Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassDataSys_%d_2", i));
            Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassData_%d_3"   , i));
            Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassDataSys_%d_3", i));
            Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassData_%d_4"   , i));
            Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassDataSys_%d_4", i));
            Gs[16] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassData_%d_1"   , i));
            Gs[17] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassDataSys_%d_1", i));
            Gs[18] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassData_%d_2"   , i));
            Gs[19] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassDataSys_%d_2", i));
            Gs[20] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassData_%d_3"   , i));
            Gs[21] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassDataSys_%d_3", i));
            Gs[22] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassData_%d_4"   , i));
            Gs[23] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassDataSys_%d_4", i));

            DoGraph(Gs, OutputBase + Form("_PrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_MASS, SD);

            Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGData_%d_1"    , i));
            Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGDataSys_%d_1" , i));
            Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGData_%d_2"    , i));
            Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGDataSys_%d_2" , i));
            Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGData_%d_3"    , i));
            Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGDataSys_%d_3" , i));
            Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGData_%d_4"    , i));
            Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGDataSys_%d_4" , i));
            Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGData_%d_1"   , i));
            Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGDataSys_%d_1", i));
            Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGData_%d_2"   , i));
            Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGDataSys_%d_2", i));
            Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGData_%d_3"   , i));
            Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGDataSys_%d_3", i));
            Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGData_%d_4"   , i));
            Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGDataSys_%d_4", i));
            Gs[16] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGData_%d_1"   , i));
            Gs[17] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGDataSys_%d_1", i));
            Gs[18] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGData_%d_2"   , i));
            Gs[19] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGDataSys_%d_2", i));
            Gs[20] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGData_%d_3"   , i));
            Gs[21] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGDataSys_%d_3", i));
            Gs[22] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGData_%d_4"   , i));
            Gs[23] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGDataSys_%d_4", i));

            DoGraph(Gs, OutputBase + Form("_ZGPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_ZG, SD);

            Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRData_%d_1"    , i));
            Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRDataSys_%d_1" , i));
            Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRData_%d_2"    , i));
            Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRDataSys_%d_2" , i));
            Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRData_%d_3"    , i));
            Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRDataSys_%d_3" , i));
            Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRData_%d_4"    , i));
            Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRDataSys_%d_4" , i));
            Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRData_%d_1"   , i));
            Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRDataSys_%d_1", i));
            Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRData_%d_2"   , i));
            Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRDataSys_%d_2", i));
            Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRData_%d_3"   , i));
            Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRDataSys_%d_3", i));
            Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRData_%d_4"   , i));
            Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRDataSys_%d_4", i));
            Gs[16] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRData_%d_1"   , i));
            Gs[17] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRDataSys_%d_1", i));
            Gs[18] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRData_%d_2"   , i));
            Gs[19] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRDataSys_%d_2", i));
            Gs[20] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRData_%d_3"   , i));
            Gs[21] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRDataSys_%d_3", i));
            Gs[22] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRData_%d_4"   , i));
            Gs[23] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRDataSys_%d_4", i));

            DoGraph(Gs, OutputBase + Form("_DRPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_DR, SD);

            Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTData_%d_1"    , i));
            Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTDataSys_%d_1" , i));
            Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTData_%d_2"    , i));
            Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTDataSys_%d_2" , i));
            Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTData_%d_3"    , i));
            Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTDataSys_%d_3" , i));
            Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTData_%d_4"    , i));
            Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTDataSys_%d_4" , i));
            Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTData_%d_1"   , i));
            Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTDataSys_%d_1", i));
            Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTData_%d_2"   , i));
            Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTDataSys_%d_2", i));
            Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTData_%d_3"   , i));
            Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTDataSys_%d_3", i));
            Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTData_%d_4"   , i));
            Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTDataSys_%d_4", i));
            Gs[16] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTData_%d_1"   , i));
            Gs[17] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTDataSys_%d_1", i));
            Gs[18] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTData_%d_2"   , i));
            Gs[19] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTDataSys_%d_2", i));
            Gs[20] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTData_%d_3"   , i));
            Gs[21] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTDataSys_%d_3", i));
            Gs[22] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTData_%d_4"   , i));
            Gs[23] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTDataSys_%d_4", i));

            DoGraph(Gs, OutputBase + Form("_PTPTPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_PTPT, SD);
            
            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassData0_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassDataSys0_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassData0_%d_2"    , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassDataSys0_%d_2" , i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassData0_%d_3"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassDataSys0_%d_3" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassData0_%d_4"    , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_MassDataSys0_%d_4" , i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassData0_%d_1"   , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassDataSys0_%d_1", i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassData0_%d_2"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassDataSys0_%d_2", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassData0_%d_3"   , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassDataSys0_%d_3", i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassData0_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_MassDataSys0_%d_4", i));
            // Gs[16] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassData0_%d_1"   , i));
            // Gs[17] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassDataSys0_%d_1", i));
            // Gs[18] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassData0_%d_2"   , i));
            // Gs[19] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassDataSys0_%d_2", i));
            // Gs[20] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassData0_%d_3"   , i));
            // Gs[21] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassDataSys0_%d_3", i));
            // Gs[22] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassData0_%d_4"   , i));
            // Gs[23] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_MassDataSys0_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_0_PrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_MASS0, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGData0_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGDataSys0_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGData0_%d_2"    , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGDataSys0_%d_2" , i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGData0_%d_3"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGDataSys0_%d_3" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGData0_%d_4"    , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_ZGDataSys0_%d_4" , i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGData0_%d_1"   , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGDataSys0_%d_1", i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGData0_%d_2"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGDataSys0_%d_2", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGData0_%d_3"   , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGDataSys0_%d_3", i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGData0_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_ZGDataSys0_%d_4", i));
            // Gs[16] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGData0_%d_1"   , i));
            // Gs[17] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGDataSys0_%d_1", i));
            // Gs[18] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGData0_%d_2"   , i));
            // Gs[19] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGDataSys0_%d_2", i));
            // Gs[20] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGData0_%d_3"   , i));
            // Gs[21] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGDataSys0_%d_3", i));
            // Gs[22] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGData0_%d_4"   , i));
            // Gs[23] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_ZGDataSys0_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_0_ZGPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_ZG, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRData0_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRDataSys0_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRData0_%d_2"    , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRDataSys0_%d_2" , i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRData0_%d_3"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRDataSys0_%d_3" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRData0_%d_4"    , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_DRDataSys0_%d_4" , i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRData0_%d_1"   , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRDataSys0_%d_1", i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRData0_%d_2"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRDataSys0_%d_2", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRData0_%d_3"   , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRDataSys0_%d_3", i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRData0_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_DRDataSys0_%d_4", i));
            // Gs[16] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRData0_%d_1"   , i));
            // Gs[17] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRDataSys0_%d_1", i));
            // Gs[18] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRData0_%d_2"   , i));
            // Gs[19] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRDataSys0_%d_2", i));
            // Gs[20] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRData0_%d_3"   , i));
            // Gs[21] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRDataSys0_%d_3", i));
            // Gs[22] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRData0_%d_4"   , i));
            // Gs[23] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_DRDataSys0_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_0_DRPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_DR0, SD);

            // Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTData0_%d_1"    , i));
            // Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTDataSys0_%d_1" , i));
            // Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTData0_%d_2"    , i));
            // Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTDataSys0_%d_2" , i));
            // Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTData0_%d_3"    , i));
            // Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTDataSys0_%d_3" , i));
            // Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTData0_%d_4"    , i));
            // Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_PTPTDataSys0_%d_4" , i));
            // Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTData0_%d_1"   , i));
            // Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTDataSys0_%d_1", i));
            // Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTData0_%d_2"   , i));
            // Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTDataSys0_%d_2", i));
            // Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTData0_%d_3"   , i));
            // Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTDataSys0_%d_3", i));
            // Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTData0_%d_4"   , i));
            // Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("PP6_PTPTDataSys0_%d_4", i));
            // Gs[16] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTData0_%d_1"   , i));
            // Gs[17] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTDataSys0_%d_1", i));
            // Gs[18] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTData0_%d_2"   , i));
            // Gs[19] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTDataSys0_%d_2", i));
            // Gs[20] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTData0_%d_3"   , i));
            // Gs[21] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTDataSys0_%d_3", i));
            // Gs[22] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTData0_%d_4"   , i));
            // Gs[23] = (TGraphAsymmErrors *)FGraphs.Get(Form("PPHerwig_PTPTDataSys0_%d_4", i));

            // DoGraph(Gs, OutputBase + Form("_0_PTPTPrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false, TYPE_PTPT, SD);
         }

         FGraphs.Close();
      }
   }

   return 0;
}

void DoGraph(vector<TGraphAsymmErrors *> Gs, string OutputBase, double BinMin, double BinMax, bool IsMC, bool IsPT, int Type, string SD)
{
   bool LogMass = false;

   if(Gs.size() != 24)
      return;

   TGraphAsymmErrors *G1Data     = Gs[0];
   TGraphAsymmErrors *G1DataSys  = Gs[1];
   TGraphAsymmErrors *G2Data     = Gs[2];
   TGraphAsymmErrors *G2DataSys  = Gs[3];
   TGraphAsymmErrors *G3Data     = Gs[4];
   TGraphAsymmErrors *G3DataSys  = Gs[5];
   TGraphAsymmErrors *G4Data     = Gs[6];
   TGraphAsymmErrors *G4DataSys  = Gs[7];
   TGraphAsymmErrors *G1MC1      = Gs[8];
   TGraphAsymmErrors *G1MC1Sys   = Gs[9];
   TGraphAsymmErrors *G2MC1      = Gs[10];
   TGraphAsymmErrors *G2MC1Sys   = Gs[11];
   TGraphAsymmErrors *G3MC1      = Gs[12];
   TGraphAsymmErrors *G3MC1Sys   = Gs[13];
   TGraphAsymmErrors *G4MC1      = Gs[14];
   TGraphAsymmErrors *G4MC1Sys   = Gs[15];
   TGraphAsymmErrors *G1MC2      = Gs[16];
   TGraphAsymmErrors *G1MC2Sys   = Gs[17];
   TGraphAsymmErrors *G2MC2      = Gs[18];
   TGraphAsymmErrors *G2MC2Sys   = Gs[19];
   TGraphAsymmErrors *G3MC2      = Gs[20];
   TGraphAsymmErrors *G3MC2Sys   = Gs[21];
   TGraphAsymmErrors *G4MC2      = Gs[22];
   TGraphAsymmErrors *G4MC2Sys   = Gs[23];

   GraphSetting(G1Data, G1DataSys, G1MC1, G1MC1Sys, G1MC2, G1MC2Sys);
   GraphSetting(G2Data, G2DataSys, G2MC1, G2MC1Sys, G2MC2, G2MC2Sys);
   GraphSetting(G3Data, G3DataSys, G3MC1, G3MC1Sys, G3MC2, G3MC2Sys);
   GraphSetting(G4Data, G4DataSys, G4MC1, G4MC1Sys, G4MC2, G4MC2Sys);

   GraphTidying(G1DataSys);   GraphTidying(G1MC1Sys);   GraphTidying(G1MC2Sys);
   GraphTidying(G2DataSys);   GraphTidying(G2MC1Sys);   GraphTidying(G2MC2Sys);
   GraphTidying(G3DataSys);   GraphTidying(G3MC1Sys);   GraphTidying(G3MC2Sys);
   GraphTidying(G4DataSys);   GraphTidying(G4MC1Sys);   GraphTidying(G4MC2Sys);

   TGraphAsymmErrors G1Ratio1, G1Ratio1Sys, G1Ratio2, G1Ratio2Sys;
   TGraphAsymmErrors G2Ratio1, G2Ratio1Sys, G2Ratio2, G2Ratio2Sys;
   TGraphAsymmErrors G3Ratio1, G3Ratio1Sys, G3Ratio2, G3Ratio2Sys;
   TGraphAsymmErrors G4Ratio1, G4Ratio1Sys, G4Ratio2, G4Ratio2Sys;

   int BinCount = 0;
   if(Type == TYPE_MASS)
      BinCount = MASSBINCOUNT;
   if(Type == TYPE_MASS0)
      BinCount = MASSBINCOUNT;
   if(Type == TYPE_ZG)
      BinCount = ZGBINCOUNT;
   if(Type == TYPE_DR)
      BinCount = DRBINCOUNT;
   if(Type == TYPE_DR0)
      BinCount = DRBINCOUNT;
   if(Type == TYPE_PTPT)
      BinCount = PTPTBINCOUNT;

   Division(G1MC1,    G1Data,    G1Ratio1,    BinCount);
   Division(G1MC1Sys, G1DataSys, G1Ratio1Sys, BinCount);
   Division(G2MC1,    G2Data,    G2Ratio1,    BinCount);
   Division(G2MC1Sys, G2DataSys, G2Ratio1Sys, BinCount);
   Division(G3MC1,    G3Data,    G3Ratio1,    BinCount);
   Division(G3MC1Sys, G3DataSys, G3Ratio1Sys, BinCount);
   Division(G4MC1,    G4Data,    G4Ratio1,    BinCount);
   Division(G4MC1Sys, G4DataSys, G4Ratio1Sys, BinCount);
   Division(G1MC2,    G1Data,    G1Ratio2,    BinCount);
   Division(G1MC2Sys, G1DataSys, G1Ratio2Sys, BinCount);
   Division(G2MC2,    G2Data,    G2Ratio2,    BinCount);
   Division(G2MC2Sys, G2DataSys, G2Ratio2Sys, BinCount);
   Division(G3MC2,    G3Data,    G3Ratio2,    BinCount);
   Division(G3MC2Sys, G3DataSys, G3Ratio2Sys, BinCount);
   Division(G4MC2,    G4Data,    G4Ratio2,    BinCount);
   Division(G4MC2Sys, G4DataSys, G4Ratio2Sys, BinCount);

   RatioGraphSetting(&G1Ratio1, &G1Ratio1Sys, 1);
   RatioGraphSetting(&G2Ratio1, &G2Ratio1Sys, 1);
   RatioGraphSetting(&G3Ratio1, &G3Ratio1Sys, 1);
   RatioGraphSetting(&G4Ratio1, &G4Ratio1Sys, 1);
   RatioGraphSetting(&G1Ratio2, &G1Ratio2Sys, 2);
   RatioGraphSetting(&G2Ratio2, &G2Ratio2Sys, 2);
   RatioGraphSetting(&G3Ratio2, &G3Ratio2Sys, 2);
   RatioGraphSetting(&G4Ratio2, &G4Ratio2Sys, 2);

   double Border = 350;
   double PadWidth = 1000;
   double PadHeight = 1000;
   double RatioHeight = 500;

   double TotalHeight = RatioHeight + PadHeight + Border * 2;
   double TotalWidth = PadWidth * 4 + Border * 2;

   double PadLowY  = (Border + RatioHeight) / TotalHeight;
   double PadHighY = (Border + RatioHeight + PadHeight) / TotalHeight;
   double PadRatioLowY  = Border / TotalHeight;

   double WorldMin = 0.011;
   double WorldMax = 500;
   double MassMin = 0;
   double MassMax = 0.26;
   double RatioMin = 0.5000;
   double RatioMax = 1.4999;

   if(Type == TYPE_MASS && SD == "0" && LogMass == false)
   {
      WorldMin = 0;
      WorldMax = 18;
   }
   if(Type == TYPE_MASS && SD == "7" && LogMass == false)
   {
      WorldMin = 0;
      WorldMax = 25;
   }
   if(Type == TYPE_MASS0 && SD == "0" && LogMass == false)
   {
      WorldMin = 0;
      WorldMax = 22;
   }
   if(Type == TYPE_MASS0 && SD == "7" && LogMass == false)
   {
      WorldMin = 0;
      WorldMax = 32;
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

   TPad *Pad1 = new TPad("Pad1", "", (Border + PadWidth * 0) / TotalWidth, PadLowY, (Border + PadWidth * 1) / TotalWidth, PadHighY);
   TPad *Pad2 = new TPad("Pad2", "", (Border + PadWidth * 1) / TotalWidth, PadLowY, (Border + PadWidth * 2) / TotalWidth, PadHighY);
   TPad *Pad3 = new TPad("Pad3", "", (Border + PadWidth * 2) / TotalWidth, PadLowY, (Border + PadWidth * 3) / TotalWidth, PadHighY);
   TPad *Pad4 = new TPad("Pad4", "", (Border + PadWidth * 3) / TotalWidth, PadLowY, (Border + PadWidth * 4) / TotalWidth, PadHighY);

   TPad *Pad5 = new TPad("Pad5", "", (Border + PadWidth * 0) / TotalWidth, PadRatioLowY, (Border + PadWidth * 1) / TotalWidth, PadLowY);
   TPad *Pad6 = new TPad("Pad6", "", (Border + PadWidth * 1) / TotalWidth, PadRatioLowY, (Border + PadWidth * 2) / TotalWidth, PadLowY);
   TPad *Pad7 = new TPad("Pad7", "", (Border + PadWidth * 2) / TotalWidth, PadRatioLowY, (Border + PadWidth * 3) / TotalWidth, PadLowY);
   TPad *Pad8 = new TPad("Pad8", "", (Border + PadWidth * 3) / TotalWidth, PadRatioLowY, (Border + PadWidth * 4) / TotalWidth, PadLowY);

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

   TGraph GData, GMC1, GMC2;
   GData.SetLineColor(G1Data->GetLineColor());
   if(G1DataSys)   GData.SetFillColor(G1DataSys->GetFillColor());
   else            GData.SetFillColor(kWhite);
   if(G1DataSys)   GData.SetFillStyle(3154);
   else            GData.SetFillStyle(0);
   GMC1.SetLineColor(G1MC1->GetLineColor());
   if(G1MC1Sys)    GMC1.SetFillColor(G1MC1Sys->GetFillColor());
   else            GMC1.SetFillColor(kWhite);
   if(G1MC1Sys)    GMC1.SetFillStyle(G1MC1Sys->GetFillStyle());
   else            GMC1.SetFillStyle(0);
   GMC2.SetLineColor(G1MC2->GetLineColor());
   if(G1MC2Sys)    GMC2.SetFillColor(G1MC2Sys->GetFillColor());
   else            GMC2.SetFillColor(kWhite);
   if(G1MC2Sys)    GMC2.SetFillStyle(3145);
   else            GMC2.SetFillStyle(0);

   Pad1->cd();
   HWorld.Draw("");
   if(G1MC1Sys)     G1MC1Sys->Draw("2");
   if(G1MC2Sys)     G1MC2Sys->Draw("2");
   if(G1DataSys)    G1DataSys->Draw("2");
   G1MC1->Draw("p");
   G1MC2->Draw("p");
   G1Data->Draw("p");
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
   if(G2MC1Sys)     G2MC1Sys->Draw("2");
   if(G2MC2Sys)     G2MC2Sys->Draw("2");
   if(G2DataSys)    G2DataSys->Draw("2");
   G2MC1->Draw("p");
   G2MC2->Draw("p");
   G2Data->Draw("p");
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
   if(G3MC1Sys)   G3MC1Sys->Draw("2");
   if(G3MC2Sys)   G3MC2Sys->Draw("2");
   if(G3DataSys)    G3DataSys->Draw("2");
   G3MC1->Draw("p");
   G3MC2->Draw("p");
   G3Data->Draw("p");
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
   if(G4MC1Sys)   G4MC1Sys->Draw("2");
   if(G4MC2Sys)   G4MC2Sys->Draw("2");
   if(G4DataSys)    G4DataSys->Draw("2");
   G4MC1->Draw("p");
   G4MC2->Draw("p");
   G4Data->Draw("p");
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
   if(G1MC1Sys)   G1Ratio1Sys.Draw("2");
   if(G1MC2Sys)   G1Ratio2Sys.Draw("2");
   G1Ratio1.Draw("p");
   G1Ratio2.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad5->SetLogy();
   Pad5->Update();

   Pad6->cd();
   HWorldRatio.Draw("");
   if(G2MC1Sys)   G2Ratio1Sys.Draw("2");
   if(G2MC2Sys)   G2Ratio2Sys.Draw("2");
   G2Ratio1.Draw("p");
   G2Ratio2.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad6->SetLogy();
   Pad6->Update();

   Pad7->cd();
   HWorldRatio.Draw("");
   if(G3MC1Sys)   G3Ratio1Sys.Draw("2");
   if(G3MC2Sys)   G3Ratio2Sys.Draw("2");
   G3Ratio1.Draw("p");
   G3Ratio2.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad7->SetLogy();
   Pad7->Update();

   Pad8->cd();
   HWorldRatio.Draw("");
   if(G4MC1Sys)   G4Ratio1Sys.Draw("2");
   if(G4MC2Sys)   G4Ratio2Sys.Draw("2");
   G4Ratio1.Draw("p");
   G4Ratio2.Draw("p");
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
   TGaxis LeftAxis1(Border / TotalWidth, (Border + RatioHeight) / TotalHeight, Border / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight,
         WorldMin, WorldMax, 50510, Scale.c_str());
   LeftAxis1.SetName("LeftAxis1");
   LeftAxis1.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(SD Mass/PT)}");
   if(Type == TYPE_MASS)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(M_{g} / p_{T})}");
   if(Type == TYPE_MASS0)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(M_{g} / p_{T})}");
   if(Type == TYPE_ZG)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d z_{g}}");
   if(Type == TYPE_DR)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d #DeltaR}");
   if(Type == TYPE_DR0)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d #DeltaR}");
   if(Type == TYPE_PTPT)
      LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(p_{T,g} / p_{T})}");
   LeftAxis1.SetTextFont(42);
   LeftAxis1.SetLabelFont(42);
   LeftAxis1.CenterTitle(true);
   LeftAxis1.SetTitleOffset(0.85);
   LeftAxis1.Draw();

   TGaxis LeftAxis2(Border / TotalWidth, Border / TotalHeight, Border / TotalWidth, (Border + RatioHeight) / TotalHeight,
         RatioMin, RatioMax, 1005, "");
   // TGaxis LeftAxis2(Border / TotalWidth, Border / TotalHeight, Border / TotalWidth, (Border + RatioHeight) / TotalHeight,
   //       RatioMin, RatioMax, 1005, "G");
   LeftAxis2.SetName("LeftAxis2");
   LeftAxis2.SetLineWidth(0);
      LeftAxis2.SetTitle("#frac{MC}{Data}");
   LeftAxis2.SetTextFont(42);
   LeftAxis2.SetLabelFont(42);
   LeftAxis2.CenterTitle(true);
   LeftAxis2.SetTitleOffset(0.85);
   LeftAxis2.Draw();

   int BottomTick = 1005;
   if(Type == TYPE_MASS0)
      BottomTick = 505;

   TGaxis BottomAxis1((Border + PadWidth * 0) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 1) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax - 0.00001, BottomTick, "");
   BottomAxis1.SetName("BottomAxis1");
   BottomAxis1.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    BottomAxis1.SetTitle("SD Mass / Jet PT");
   if(Type == TYPE_MASS)
      BottomAxis1.SetTitle("M_{g} / p_{T}");
   if(Type == TYPE_MASS0)
      BottomAxis1.SetTitle("M_{g} / p_{T}");
   if(Type == TYPE_ZG)
      BottomAxis1.SetTitle("z_{g}");
   if(Type == TYPE_DR)
      BottomAxis1.SetTitle("#DeltaR");
   if(Type == TYPE_DR0)
      BottomAxis1.SetTitle("#DeltaR");
   if(Type == TYPE_PTPT)
      BottomAxis1.SetTitle("p_{T,g} / p_{T}");
   BottomAxis1.SetTextFont(42);
   BottomAxis1.SetLabelFont(42);
   BottomAxis1.CenterTitle(true);
   BottomAxis1.Draw();

   TGaxis BottomAxis2((Border + PadWidth * 1) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 2) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax - 0.00001, BottomTick, "");
   BottomAxis2.SetName("BottomAxis2");
   BottomAxis2.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    BottomAxis2.SetTitle("SD Mass / Jet PT");
   if(Type == TYPE_MASS)
      BottomAxis2.SetTitle("M_{g} / p_{T}");
   if(Type == TYPE_MASS0)
      BottomAxis2.SetTitle("M_{g} / p_{T}");
   if(Type == TYPE_ZG)
      BottomAxis2.SetTitle("z_{g}");
   if(Type == TYPE_DR)
      BottomAxis2.SetTitle("#DeltaR");
   if(Type == TYPE_DR0)
      BottomAxis2.SetTitle("#DeltaR");
   if(Type == TYPE_PTPT)
      BottomAxis2.SetTitle("p_{T,g} / p_{T}");
   BottomAxis2.SetTextFont(42);
   BottomAxis2.SetLabelFont(42);
   BottomAxis2.CenterTitle(true);
   BottomAxis2.Draw();

   TGaxis BottomAxis3((Border + PadWidth * 2) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 3) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax - 0.00001, BottomTick, "");
   BottomAxis3.SetName("BottomAxis3");
   BottomAxis3.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    BottomAxis3.SetTitle("SD Mass / Jet PT");
   if(Type == TYPE_MASS)
      BottomAxis3.SetTitle("M_{g} / p_{T}");
   if(Type == TYPE_MASS0)
      BottomAxis3.SetTitle("M_{g} / p_{T}");
   if(Type == TYPE_ZG)
      BottomAxis3.SetTitle("z_{g}");
   if(Type == TYPE_DR)
      BottomAxis3.SetTitle("#DeltaR");
   if(Type == TYPE_DR0)
      BottomAxis3.SetTitle("#DeltaR");
   if(Type == TYPE_PTPT)
      BottomAxis3.SetTitle("p_{T,g} / p_{T}");
   BottomAxis3.SetTextFont(42);
   BottomAxis3.SetLabelFont(42);
   BottomAxis3.CenterTitle(true);
   BottomAxis3.Draw();

   TGaxis BottomAxis4((Border + PadWidth * 3) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 4) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax, BottomTick, "");
   BottomAxis4.SetName("BottomAxis4");
   BottomAxis4.SetLineWidth(0);
   // if(Type == TYPE_MASS)
   //    BottomAxis4.SetTitle("SD Mass / Jet PT");
   if(Type == TYPE_MASS)
      BottomAxis4.SetTitle("M_{g} / p_{T}");
   if(Type == TYPE_MASS0)
      BottomAxis4.SetTitle("M_{g} / p_{T}");
   if(Type == TYPE_ZG)
      BottomAxis4.SetTitle("z_{g}");
   if(Type == TYPE_DR)
      BottomAxis4.SetTitle("#DeltaR");
   if(Type == TYPE_DR0)
      BottomAxis4.SetTitle("#DeltaR");
   if(Type == TYPE_PTPT)
      BottomAxis4.SetTitle("p_{T,g} / p_{T}");
   BottomAxis4.SetTextFont(42);
   BottomAxis4.SetLabelFont(42);
   BottomAxis4.CenterTitle(true);
   BottomAxis4.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);

   Latex.SetTextAlign(10);
   if(Type == TYPE_MASS || Type == TYPE_MASS0)
      Latex.DrawLatex(Border / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight, "CMS Preliminary");
   else
      Latex.DrawLatex(Border / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight, "CMS Internal");

   Latex.SetTextAlign(30);
   if(IsMC == false)
      Latex.DrawLatex((Border + PadWidth * 4) / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight, "#sqrt{s_{NN}} = 5.02 TeV, pp 28 pb^{-1}");
   else
      Latex.DrawLatex((Border + PadWidth * 4) / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight, "#sqrt{s_{NN}} = 5.02 TeV, Simulation");

   TLegend Legend((Border + PadWidth * 0.40) / TotalWidth, (Border + RatioHeight + 0.45 * PadHeight) / TotalHeight,
                  (Border + PadWidth * 0.85) / TotalWidth, (Border + RatioHeight + 0.85 * PadHeight) / TotalHeight);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&GData, "Data", "lf");
   Legend.AddEntry(&GMC1, "PYTHIA6 (Z2)", "lf");
   Legend.AddEntry(&GMC2, "HERWIG++", "lf");
   Legend.AddEntry("", " (EE5C)", "");
   Legend.Draw();

   Latex.SetTextAlign(33);
   if(IsPT == true)
   {
      Latex.DrawLatex((Border + PadWidth * 0.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "Centrality: 0-10%");
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "Centrality: 10-30%");
      Latex.DrawLatex((Border + PadWidth * 2.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "Centrality: 30-50%");
      Latex.DrawLatex((Border + PadWidth * 3.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "Centrality: 50-80%");
   }
   else
   {
      Latex.DrawLatex((Border + PadWidth * 0.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "140 < p_{T,jet} < 160 GeV");
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "160 < p_{T,jet} < 180 GeV");
      Latex.DrawLatex((Border + PadWidth * 2.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "180 < p_{T,jet} < 200 GeV");
      Latex.DrawLatex((Border + PadWidth * 3.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "200 < p_{T,jet} < 300 GeV");
   }

   if(IsPT == true)
   {
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.85) / TotalHeight, Form("%.0f < p_{T,jet} < %.0f GeV", BinMin, BinMax));
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.75) / TotalHeight, "|#eta| < 1.3");
   }
   else
   {
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.85) / TotalHeight, "|#eta| < 1.3");
      // Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.75) / TotalHeight, Form("Centrality: %.0f-%.0f%%", BinMin, BinMax));
   }

   Latex.DrawLatex((Border + PadWidth * 3.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.85) / TotalHeight, "anti-kt R = 0.4");
   Latex.DrawLatex((Border + PadWidth * 3.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.75) / TotalHeight, "#DeltaR_{1,2} > 0.1");

   Latex.DrawLatex((Border + PadWidth * 2.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.85) / TotalHeight, "Soft drop");
   if(SD == "7")
      Latex.DrawLatex((Border + PadWidth * 2.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.75) / TotalHeight, "z_{cut} = 0.5, #beta = 1.5");
   else
      Latex.DrawLatex((Border + PadWidth * 2.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.75) / TotalHeight, "z_{cut} = 0.1, #beta = 0.0");

   Canvas.SaveAs(Form("%s.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.C"  , OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}

void PadSetting(TPad *Pad)
{
   Pad->SetTopMargin(0);
   Pad->SetRightMargin(0);
   Pad->SetBottomMargin(0);
   Pad->SetLeftMargin(0);

   Pad->Draw();
}

void GraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *G3, TGraphAsymmErrors *G4,
   TGraphAsymmErrors *G5, TGraphAsymmErrors *G6)
{
   if(G1 != NULL)
   {
      G1->SetLineColor(kRed + 2);
      G1->SetMarkerColor(kRed + 2);
   }

   if(G2 != NULL)
   {
      G2->SetLineWidth(0);
      G2->SetFillStyle(3454);
      G2->SetFillColor(kRed - 7);
   }

   if(G3 != NULL)
   {
      G3->SetLineColor(kBlue + 2);
      G3->SetMarkerColor(kBlue + 2);
      G3->SetLineWidth(1);
   }

   if(G4 != NULL)
   {
      G4->SetLineWidth(0);
      G4->SetFillColor(TColor::GetColor("#50BFE6"));
   }

   if(G5 != NULL)
   {
      G5->SetLineColor(kGreen + 3);
      G5->SetMarkerColor(kGreen + 3);
      G5->SetLineWidth(1);
   }

   if(G6 != NULL)
   {
      G6->SetLineWidth(0);
      G6->SetFillStyle(3445);
      G6->SetFillColor(kGreen - 3);
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
         GRatio.SetPoint(i, x1, ratio);
         GRatio.SetPointError(i, xl1, xh1, yl, yh);
      }
      else
      {
         GRatio.SetPoint(i, -100, -100);
         GRatio.SetPointError(i, 0, 0, 0, 0);
      }
   }

   // GRatio.Print();
}

void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, int MC)
{
   int LineColor = kBlack;
   int FillColor = kBlue - 9;
   int FillStyle = 1001;

   if(MC == 1)
   {
      LineColor = kBlue + 2;
      FillColor = TColor::GetColor("#50BFE6");
      FillStyle = 1001;
   }
   if(MC == 2)
   {
      LineColor = kGreen + 3;
      FillColor = kGreen - 3;
      FillStyle = 3445;
   }

   if(G1 != NULL)
   {
      G1->SetLineColor(LineColor);
      G1->SetMarkerColor(LineColor);
   }

   if(G2 != NULL)
   {
      G2->SetLineWidth(0);
      G2->SetFillColor(FillColor);
      G2->SetFillStyle(FillStyle);
   }
}


