#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "SetStyle.h"

#define GRAPH_NONE 0
#define GRAPH_NE_SW 1
#define GRAPH_NW_SE 2

int main(int argc, char *argv[]);
void ExportHistogram2D(TFile &File, string Name, string OutputBase, int GraphOption = GRAPH_NONE, int Rebin = 1);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string InputFile = "ScaledResult/AA8Dijet.root";
   string OutputBase = "Plots/AA8Dijet";

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   TFile File(InputFile.c_str());

   string C[5] = {"_C0", "_C1", "_C2", "_C3", "_C4"};
   string P[7] = {"_P0", "_P1", "_P2", "_P3", "_P4", "_P5", "_P6"};

   string Names[16] = {"SubJet1Location", "SubJet2Location",
      "SubJet1XVsGenWeightedXIn", "SubJet1PTVsGenSumPTIn", "SubJet1PTVsGenSubJet1PTIn",
      "SubJet2PTVsGenSubJet2PTIn", "SubJet1DPTVsSubJet2DPTIn", "SumPTVsGenSubJet1PTIn",
      "SubJetAverageXVsSubJetAverageYIn",
      "SubJet1XVsGenWeightedXOut", "SubJet1PTVsGenSumPTOut", "SubJet1PTVsGenSubJet1PTOut",
      "SubJet2PTVsGenSubJet2PTOut", "SubJet1DPTVsSubJet2DPTOut", "SumPTVsGenSubJet1PTOut",
      "SubJetAverageXVsSubJetAverageYOut"};

   int GraphOption[16] = {GRAPH_NONE, GRAPH_NONE,
      GRAPH_NE_SW, GRAPH_NE_SW, GRAPH_NE_SW,
      GRAPH_NE_SW, GRAPH_NW_SE, GRAPH_NE_SW,
      GRAPH_NONE,
      GRAPH_NE_SW, GRAPH_NE_SW, GRAPH_NE_SW,
      GRAPH_NE_SW, GRAPH_NW_SE, GRAPH_NE_SW,
      GRAPH_NONE};

   int Rebin[16] = {1, 1,
      1, 5, 5,
      5, 4, 5,
      1,
      1, 5, 5,
      5, 4, 5,
      1};

   for(int i = 0; i < 5; i++)
      for(int j = 0; j < 7; j++)
         for(int k = 0; k < 16; k++)
            ExportHistogram2D(File, Form("H%s%d%d", Names[k].c_str(), i, j),
               OutputBase + "_" + Names[k] + C[i] + P[j], GraphOption[k], Rebin[k]);

   File.Close();

   return 0;
}

void ExportHistogram2D(TFile &File, string Name, string OutputBase, int GraphOption, int Rebin)
{
   TH2D *H = (TH2D *)File.Get(Name.c_str());
   if(H == NULL)
      return;

   H->Rebin2D(Rebin, Rebin);

   TGraph G;

   TCanvas C;

   H->SetStats(0);
   H->Draw("colz");
   
   if(GraphOption == GRAPH_NE_SW)
   {
      G.SetPoint(0, 10000, 10000);
      G.SetPoint(1, -10000, -10000);
      G.Draw("l");
   }
   if(GraphOption == GRAPH_NW_SE)
   {
      G.SetPoint(0, -10000, 10000);
      G.SetPoint(1, 10000, -10000);
      G.Draw("l");
   }

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C", OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}


