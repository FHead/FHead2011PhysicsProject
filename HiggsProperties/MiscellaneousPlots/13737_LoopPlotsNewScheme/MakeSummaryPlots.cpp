#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper2.h"

#define NONSENSE 999999

int main();
void AddPlot(PsFileHelper &PsFile, TFile &File, vector<string> Histograms, vector<string> Labels, string Title, string XAxis, string YAxis, double Level = NONSENSE);
vector<string> ToVector(string S1, string S2 = "", string S3 = "", string S4 = "", string S5 = "", string S6 = "", string S7 = "", string S8 = "");

int main()
{
   PsFileHelper PsFileA("SummaryPlotsPointA.ps");
   PsFileHelper PsFileB("SummaryPlotsPointB.ps");
   PsFileA.AddTextPage("Various plots for us to stare at!  Point A - SM");
   PsFileB.AddTextPage("Various plots for us to stare at!  Point B - exotic");

   vector<string> Items(13);
   vector<string> Labels(13);

   Items[0]  = "Different combinations of floating y_{t}, #tilde{y}_{t}, g_{WW}, A cut";
   Items[1]  = "Different combinations of floating y_{t}, #tilde{y}_{t}, g_{WW}, J cut";
   Items[2]  = "Compare A, H, I, J cuts, float only one of y_{t}, #tilde{y}_{t}, g_{WW}";
   Items[3]  = "Compare A, H, I, J cuts, float both y_{t}, #tilde{y}_{t}";
   Items[4]  = "Compare A, H, I, J cuts, float all of y_{t}, #tilde{y}_{t}, g_{WW}";
   Items[5]  = "Check effect of floating ZZ sector on y_{t}, #tilde{y}_{t} and g_{WW}, A cut";
   Items[6]  = "Check effect of floating ZZ sector on y_{t}, #tilde{y}_{t} and g_{WW}, J cut";
   Items[7]  = "Different channels, floating one of y_{t}, #tilde{y}_{t}, g_{WW}, A cut";
   Items[8]  = "Different channels, floating all of y_{t}, #tilde{y}_{t}, g_{WW}, A cut";
   Items[9]  = "Different channels, floating one of y_{t}, #tilde{y}_{t}, g_{WW}, J cut";
   Items[10] = "Different channels, floating all of y_{t}, #tilde{y}_{t}, g_{WW}, J cut";
   Items[11] = "Effect of background, A cut";
   Items[12] = "Effect of background, J cut";

   Labels[0]  = "CompareA";
   Labels[1]  = "CompareJ";
   Labels[2]  = "CompareCutsSingle";
   Labels[3]  = "CompareCutsBoth";
   Labels[4]  = "CompareCutsAll";
   Labels[5]  = "CompareFloatZZA";
   Labels[6]  = "CompareFloatZZJ";
   Labels[7]  = "CompareChannelSingleA";
   Labels[8]  = "CompareChannelAllA";
   Labels[9]  = "CompareChannelSingleJ";
   Labels[10] = "CompareChannelAllJ";
   Labels[11] = "CompareBackgroundA";
   Labels[12] = "CompareBackgroundJ";

   PsFileA.AddTableOfContentPage(Items, Labels);
   PsFileB.AddTableOfContentPage(Items, Labels);

   PsFileA.InsertNamedDestination("TableOfContent");
   PsFileB.InsertNamedDestination("TableOfContent");

   PsFileA.SetAutomaticHomeButton(true, "TableOfContent");
   PsFileB.SetAutomaticHomeButton(true, "TableOfContent");

   TFile File("AllGraphs.root");

   PsFileA.AddTextPage("Different combinations of floating y_{t}, #tilde{y}_{y}, g_{WW}, A cut");
   PsFileA.InsertNamedDestination("CompareA");

   AddPlot(PsFileA, File,
      ToVector("YT_BothS_A_Count_NNNYNN_PointA", "YT_BothS_A_Count_NNNYYN_PointA", "YT_BothS_A_Count_NNNYNY_PointA", "YT_BothS_A_Count_NNNYYY_PointA"),
      ToVector("Float y_{t}", "Float y_{t}, #tilde{y}_{t}", "Float y_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "y_{t}, A cut, both channels, Point A",
      "N_{S}", "#sigma(y_{t})", 1);
   AddPlot(PsFileA, File,
      ToVector("YTA_BothS_A_Count_NNNNYN_PointA", "YTA_BothS_A_Count_NNNYYN_PointA", "YTA_BothS_A_Count_NNNNYY_PointA", "YTA_BothS_A_Count_NNNYYY_PointA"),
      ToVector("Float #tilde{y}_{t}", "Float y_{t}, #tilde{y}_{t}", "Float #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "#tilde{y}_{t}, A cut, both channels, Point A",
      "N_{S}", "#sigma(#tilde{y}_{t})", 0);
   AddPlot(PsFileA, File,
      ToVector("GWW_BothS_A_Count_NNNNNY_PointA", "GWW_BothS_A_Count_NNNYNY_PointA", "GWW_BothS_A_Count_NNNNYY_PointA", "GWW_BothS_A_Count_NNNYYY_PointA"),
      ToVector("Float g_{WW}", "Float y_{t}, g_{WW}", "Float #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "g_{WW}, A cut, both channels, Point A",
      "N_{S}", "#sigma(g_{WW})", 2);
   
   PsFileA.AddTextPage("Different combinations of floating y_{t}, #tilde{y}_{y}, g_{WW}, J cut");
   PsFileA.InsertNamedDestination("CompareJ");
   
   AddPlot(PsFileA, File,
      ToVector("YT_BothS_J_Count_NNNYNN_PointA", "YT_BothS_J_Count_NNNYYN_PointA", "YT_BothS_J_Count_NNNYNY_PointA", "YT_BothS_J_Count_NNNYYY_PointA"),
      ToVector("Float y_{t}", "Float y_{t}, #tilde{y}_{t}", "Float y_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "y_{t}, J cut, both channels, Point A",
      "N_{S}", "#sigma(y_{t})", 1);
   AddPlot(PsFileA, File,
      ToVector("YTA_BothS_J_Count_NNNNYN_PointA", "YTA_BothS_J_Count_NNNYYN_PointA", "YTA_BothS_J_Count_NNNNYY_PointA", "YTA_BothS_J_Count_NNNYYY_PointA"),
      ToVector("Float #tilde{y}_{t}", "Float y_{t}, #tilde{y}_{t}", "Float #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "#tilde{y}_{t}, J cut, both channels, Point A",
      "N_{S}", "#sigma(#tilde{y}_{t})", 0);
   AddPlot(PsFileA, File,
      ToVector("GWW_BothS_J_Count_NNNNNY_PointA", "GWW_BothS_J_Count_NNNYNY_PointA", "GWW_BothS_J_Count_NNNNYY_PointA", "GWW_BothS_J_Count_NNNYYY_PointA"),
      ToVector("Float g_{WW}", "Float y_{t}, g_{WW}", "Float #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "g_{WW}, J cut, both channels, Point A",
      "N_{S}", "#sigma(g_{WW})", 2);

   PsFileB.AddTextPage("Different combinations of floating y_{t}, #tilde{y}_{y}, g_{WW}, A cut");
   PsFileB.InsertNamedDestination("CompareA");
   
   AddPlot(PsFileB, File,
      ToVector("YT_BothS_A_Count_NNNYNN_PointB", "YT_BothS_A_Count_NNNYYN_PointB", "YT_BothS_A_Count_NNNYNY_PointB", "YT_BothS_A_Count_NNNYYY_PointB"),
      ToVector("Float y_{t}", "Float y_{t}, #tilde{y}_{t}", "Float y_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "y_{t}, A cut, both channels, Point B",
      "N_{S}", "#sigma(y_{t})", 1.5);
   AddPlot(PsFileB, File,
      ToVector("YTA_BothS_A_Count_NNNNYN_PointB", "YTA_BothS_A_Count_NNNYYN_PointB", "YTA_BothS_A_Count_NNNNYY_PointB", "YTA_BothS_A_Count_NNNYYY_PointB"),
      ToVector("Float #tilde{y}_{t}", "Float y_{t}, #tilde{y}_{t}", "Float #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "#tilde{y}_{t}, A cut, both channels, Point B",
      "N_{S}", "#sigma(#tilde{y}_{t})", 1);
   AddPlot(PsFileB, File,
      ToVector("GWW_BothS_A_Count_NNNNNY_PointB", "GWW_BothS_A_Count_NNNYNY_PointB", "GWW_BothS_A_Count_NNNNYY_PointB", "GWW_BothS_A_Count_NNNYYY_PointB"),
      ToVector("Float g_{WW}", "Float y_{t}, g_{WW}", "Float #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "g_{WW}, A cut, both channels, Point B",
      "N_{S}", "#sigma(g_{WW})", 2);
   
   PsFileB.AddTextPage("Different combinations of floating y_{t}, #tilde{y}_{y}, g_{WW}, J cut");
   PsFileB.InsertNamedDestination("CompareJ");
   
   AddPlot(PsFileB, File,
      ToVector("YT_BothS_J_Count_NNNYNN_PointB", "YT_BothS_J_Count_NNNYYN_PointB", "YT_BothS_J_Count_NNNYNY_PointB", "YT_BothS_J_Count_NNNYYY_PointB"),
      ToVector("Float y_{t}", "Float y_{t}, #tilde{y}_{t}", "Float y_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "y_{t}, J cut, both channels, Point B",
      "N_{S}", "#sigma(y_{t})", 1.5);
   AddPlot(PsFileB, File,
      ToVector("YTA_BothS_J_Count_NNNNYN_PointB", "YTA_BothS_J_Count_NNNYYN_PointB", "YTA_BothS_J_Count_NNNNYY_PointB", "YTA_BothS_J_Count_NNNYYY_PointB"),
      ToVector("Float #tilde{y}_{t}", "Float y_{t}, #tilde{y}_{t}", "Float #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "#tilde{y}_{t}, J cut, both channels, Point B",
      "N_{S}", "#sigma(#tilde{y}_{t})", 1);
   AddPlot(PsFileB, File,
      ToVector("GWW_BothS_J_Count_NNNNNY_PointB", "GWW_BothS_J_Count_NNNYNY_PointB", "GWW_BothS_J_Count_NNNNYY_PointB", "GWW_BothS_J_Count_NNNYYY_PointB"),
      ToVector("Float g_{WW}", "Float y_{t}, g_{WW}", "Float #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}"),
      "g_{WW}, J cut, both channels, Point B",
      "N_{S}", "#sigma(g_{WW})", 2);

   PsFileA.AddTextPage("Compare A, H, I, J cuts, float only one of y_{t}, #tilde{y}_{t}, g_{WW}");
   PsFileA.InsertNamedDestination("CompareCutsSingle");
   
   AddPlot(PsFileA, File,
      ToVector("YT_BothS_A_Lumi_NNNYNN_PointA", "YT_BothS_H_Lumi_NNNYNN_PointA", "YT_BothS_I_Lumi_NNNYNN_PointA", "YT_BothS_J_Lumi_NNNYNN_PointA"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "y_{t}, different cuts, float only y_{t}, both channels, Point A",
      "N_{S} / #epsilon", "#sigma(y_{t})", 1);
   AddPlot(PsFileA, File,
      ToVector("YTA_BothS_A_Lumi_NNNNYN_PointA", "YTA_BothS_H_Lumi_NNNNYN_PointA", "YTA_BothS_I_Lumi_NNNNYN_PointA", "YTA_BothS_J_Lumi_NNNNYN_PointA"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "#tilde{y}_{t}, different cuts, float only #tilde{y}_{t}, both channels, Point A",
      "N_{S} / #epsilon", "#sigma(#tilde{y}_{t})", 0);
   AddPlot(PsFileA, File,
      ToVector("GWW_BothS_A_Lumi_NNNNNY_PointA", "GWW_BothS_H_Lumi_NNNNNY_PointA", "GWW_BothS_I_Lumi_NNNNNY_PointA", "GWW_BothS_J_Lumi_NNNNNY_PointA"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "g_{WW}, different cuts, float only g_{WW}, both channels, Point A",
      "N_{S} / #epsilon", "#sigma(g_{WW})", 2);
   
   PsFileA.AddTextPage("Compare A, H, I, J cuts, float both y_{t}, #tilde{y}_{t}");
   PsFileA.InsertNamedDestination("CompareCutsBoth");
   
   AddPlot(PsFileA, File,
      ToVector("YT_BothS_A_Lumi_NNNYYN_PointA", "YT_BothS_H_Lumi_NNNYYN_PointA", "YT_BothS_I_Lumi_NNNYYN_PointA", "YT_BothS_J_Lumi_NNNYYN_PointA"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "y_{t}, different cuts, float y_{t} and #tilde{y}_{t}, both channels, Point A",
      "N_{S} / #epsilon", "#sigma(y_{t})", 1);
   AddPlot(PsFileA, File,
      ToVector("YTA_BothS_A_Lumi_NNNYYN_PointA", "YTA_BothS_H_Lumi_NNNYYN_PointA", "YTA_BothS_I_Lumi_NNNYYN_PointA", "YTA_BothS_J_Lumi_NNNYYN_PointA"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "#tilde{y}_{t}, different cuts, float y_{t} and #tilde{y}_{t}, both channels, Point A",
      "N_{S} / #epsilon", "#sigma(#tilde{y}_{t})", 0);
   
   PsFileA.AddTextPage("Compare A, H, I, J cuts, float all of y_{t}, #tilde{y}_{t}, g_{WW}");
   PsFileA.InsertNamedDestination("CompareCutsAll");
   
   AddPlot(PsFileA, File,
      ToVector("YT_BothS_A_Lumi_NNNYYY_PointA", "YT_BothS_H_Lumi_NNNYYY_PointA", "YT_BothS_I_Lumi_NNNYYY_PointA", "YT_BothS_J_Lumi_NNNYYY_PointA"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "y_{t}, different cuts, float y_{t}, #tilde{y}_{t}, g_{WW}, both channels, Point A",
      "N_{S} / #epsilon", "#sigma(y_{t})", 1);
   AddPlot(PsFileA, File,
      ToVector("YTA_BothS_A_Lumi_NNNYYY_PointA", "YTA_BothS_H_Lumi_NNNYYY_PointA", "YTA_BothS_I_Lumi_NNNYYY_PointA", "YTA_BothS_J_Lumi_NNNYYY_PointA"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "#tilde{y}_{t}, different cuts, float y_{t}, #tilde{y}_{t}, g_{WW}, both channels, Point A",
      "N_{S} / #epsilon", "#sigma(#tilde{y}_{t})", 0);
   AddPlot(PsFileA, File,
      ToVector("GWW_BothS_A_Lumi_NNNYYY_PointA", "GWW_BothS_H_Lumi_NNNYYY_PointA", "GWW_BothS_I_Lumi_NNNYYY_PointA", "GWW_BothS_J_Lumi_NNNYYY_PointA"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "g_{WW}, different cuts, float y_{t}, #tilde{y}_{t}, g_{WW}, both channels, Point A",
      "N_{S} / #epsilon", "#sigma(g_{WW})", 2);
   
   PsFileB.AddTextPage("Compare A, H, I, J cuts, float only one of y_{t}, #tilde{y}_{t}, g_{WW}");
   PsFileB.InsertNamedDestination("CompareCutsSingle");
   
   AddPlot(PsFileB, File,
      ToVector("YT_BothS_A_Lumi_NNNYNN_PointB", "YT_BothS_H_Lumi_NNNYNN_PointB", "YT_BothS_I_Lumi_NNNYNN_PointB", "YT_BothS_J_Lumi_NNNYNN_PointB"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "y_{t}, different cuts, float only y_{t}, both channels, Point B",
      "N_{S} / #epsilon", "#sigma(y_{t})", 1.5);
   AddPlot(PsFileB, File,
      ToVector("YTA_BothS_A_Lumi_NNNNYN_PointB", "YTA_BothS_H_Lumi_NNNNYN_PointB", "YTA_BothS_I_Lumi_NNNNYN_PointB", "YTA_BothS_J_Lumi_NNNNYN_PointB"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "#tilde{y}_{t}, different cuts, float only #tilde{y}_{t}, both channels, Point B",
      "N_{S} / #epsilon", "#sigma(#tilde{y}_{t})", 1);
   AddPlot(PsFileB, File,
      ToVector("GWW_BothS_A_Lumi_NNNNNY_PointB", "GWW_BothS_H_Lumi_NNNNNY_PointB", "GWW_BothS_I_Lumi_NNNNNY_PointB", "GWW_BothS_J_Lumi_NNNNNY_PointB"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "g_{WW}, different cuts, float only g_{WW}, both channels, Point B",
      "N_{S} / #epsilon", "#sigma(g_{WW})", 2);
   
   PsFileB.AddTextPage("Compare A, H, I, J cuts, float both y_{t}, #tilde{y}_{t}");
   PsFileB.InsertNamedDestination("CompareCutsBoth");
   
   AddPlot(PsFileB, File,
      ToVector("YT_BothS_A_Lumi_NNNYYN_PointB", "YT_BothS_H_Lumi_NNNYYN_PointB", "YT_BothS_I_Lumi_NNNYYN_PointB", "YT_BothS_J_Lumi_NNNYYN_PointB"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "y_{t}, different cuts, float y_{t} and #tilde{y}_{t}, both channels, Point B",
      "N_{S} / #epsilon", "#sigma(y_{t})", 1.5);
   AddPlot(PsFileB, File,
      ToVector("YTA_BothS_A_Lumi_NNNYYN_PointB", "YTA_BothS_H_Lumi_NNNYYN_PointB", "YTA_BothS_I_Lumi_NNNYYN_PointB", "YTA_BothS_J_Lumi_NNNYYN_PointB"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "#tilde{y}_{t}, different cuts, float y_{t} and #tilde{y}_{t}, both channels, Point B",
      "N_{S} / #epsilon", "#sigma(#tilde{y}_{t})", 1);
   
   PsFileB.AddTextPage("Compare A, H, I, J cuts, float all of y_{t}, #tilde{y}_{t}, g_{WW}");
   PsFileB.InsertNamedDestination("CompareCutsAll");
   
   AddPlot(PsFileB, File,
      ToVector("YT_BothS_A_Lumi_NNNYYY_PointB", "YT_BothS_H_Lumi_NNNYYY_PointB", "YT_BothS_I_Lumi_NNNYYY_PointB", "YT_BothS_J_Lumi_NNNYYY_PointB"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "y_{t}, different cuts, float y_{t}, #tilde{y}_{t}, g_{WW}, both channels, Point B",
      "N_{S} / #epsilon", "#sigma(y_{t})", 1.5);
   AddPlot(PsFileB, File,
      ToVector("YTA_BothS_A_Lumi_NNNYYY_PointB", "YTA_BothS_H_Lumi_NNNYYY_PointB", "YTA_BothS_I_Lumi_NNNYYY_PointB", "YTA_BothS_J_Lumi_NNNYYY_PointB"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "#tilde{y}_{t}, different cuts, float y_{t}, #tilde{y}_{t}, g_{WW}, both channels, Point B",
      "N_{S} / #epsilon", "#sigma(#tilde{y}_{t})", 1);
   AddPlot(PsFileB, File,
      ToVector("GWW_BothS_A_Lumi_NNNYYY_PointB", "GWW_BothS_H_Lumi_NNNYYY_PointB", "GWW_BothS_I_Lumi_NNNYYY_PointB", "GWW_BothS_J_Lumi_NNNYYY_PointB"),
      ToVector("A cut", "H cut", "I cut", "J cut"),
      "g_{WW}, different cuts, float y_{t}, #tilde{y}_{t}, g_{WW}, both channels, Point B",
      "N_{S} / #epsilon", "#sigma(g_{WW})", 2);

   PsFileA.AddTextPage("Check effect of floating ZZ sector on y_{t}, #tilde{y}_{t} and g_{WW}, A cut");
   PsFileA.InsertNamedDestination("CompareFloatZZA");

   AddPlot(PsFileA, File,
      ToVector("YT_BothS_A_Count_NNNYNN_PointA", "YT_BothS_A_Count_YYYYNN_PointA", "YT_BothS_A_Count_NNNYYY_PointA", "YT_BothS_A_Count_YYYYYY_PointA"),
      ToVector("Float y_{t}", "Float y_{t}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "y_{t}, A cut, both channels, Point A",
      "N_{S}", "#sigma(y_{t})", 1);
   AddPlot(PsFileA, File,
      ToVector("YTA_BothS_A_Count_NNNNYN_PointA", "YTA_BothS_A_Count_YYYNYN_PointA", "YTA_BothS_A_Count_NNNYYY_PointA", "YTA_BothS_A_Count_YYYYYY_PointA"),
      ToVector("Float #tilde{y}_{t}", "Float #tilde{y}_{t}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "#tilde{y}_{t}, A cut, both channels, Point A",
      "N_{S}", "#sigma(#tilde{y}_{t})", 0);
   AddPlot(PsFileA, File,
      ToVector("GWW_BothS_A_Count_NNNNNY_PointA", "GWW_BothS_A_Count_YYYNNY_PointA", "GWW_BothS_A_Count_NNNYYY_PointA", "GWW_BothS_A_Count_YYYYYY_PointA"),
      ToVector("Float g_{WW}", "Float g_{WW}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "g_{WW}, A cut, both channels, Point A",
      "N_{S}", "#sigma(g_{WW})", 2);
   
   PsFileB.AddTextPage("Check effect of floating ZZ sector on y_{t}, #tilde{y}_{t} and g_{WW}, A cut");
   PsFileB.InsertNamedDestination("CompareFloatZZA");
   
   AddPlot(PsFileB, File,
      ToVector("YT_BothS_A_Count_NNNYNN_PointB", "YT_BothS_A_Count_YYYYNN_PointB", "YT_BothS_A_Count_NNNYYY_PointB", "YT_BothS_A_Count_YYYYYY_PointB"),
      ToVector("Float y_{t}", "Float y_{t}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "y_{t}, A cut, both channels, Point B",
      "N_{S}", "#sigma(y_{t})", 1.5);
   AddPlot(PsFileB, File,
      ToVector("YTA_BothS_A_Count_NNNNYN_PointB", "YTA_BothS_A_Count_YYYNYN_PointB", "YTA_BothS_A_Count_NNNYYY_PointB", "YTA_BothS_A_Count_YYYYYY_PointB"),
      ToVector("Float #tilde{y}_{t}", "Float #tilde{y}_{t}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "#tilde{y}_{t}, A cut, both channels, Point B",
      "N_{S}", "#sigma(#tilde{y}_{t})", 1);
   AddPlot(PsFileB, File,
      ToVector("GWW_BothS_A_Count_NNNNNY_PointB", "GWW_BothS_A_Count_YYYNNY_PointB", "GWW_BothS_A_Count_NNNYYY_PointB", "GWW_BothS_A_Count_YYYYYY_PointB"),
      ToVector("Float g_{WW}", "Float g_{WW}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "g_{WW}, A cut, both channels, Point B",
      "N_{S}", "#sigma(g_{WW})", 2);
   
   PsFileA.AddTextPage("Check effect of floating ZZ sector on y_{t}, #tilde{y}_{t} and g_{WW}, J cut");
   PsFileA.InsertNamedDestination("CompareFloatZZJ");

   AddPlot(PsFileA, File,
      ToVector("YT_BothS_J_Count_NNNYNN_PointA", "YT_BothS_J_Count_YYYYNN_PointA", "YT_BothS_J_Count_NNNYYY_PointA", "YT_BothS_J_Count_YYYYYY_PointA"),
      ToVector("Float y_{t}", "Float y_{t}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "y_{t}, J cut, both channels, Point A",
      "N_{S}", "#sigma(y_{t})", 1);
   AddPlot(PsFileA, File,
      ToVector("YTA_BothS_J_Count_NNNNYN_PointA", "YTA_BothS_J_Count_YYYNYN_PointA", "YTA_BothS_J_Count_NNNYYY_PointA", "YTA_BothS_J_Count_YYYYYY_PointA"),
      ToVector("Float #tilde{y}_{t}", "Float #tilde{y}_{t}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "#tilde{y}_{t}, J cut, both channels, Point A",
      "N_{S}", "#sigma(#tilde{y}_{t})", 0);
   AddPlot(PsFileA, File,
      ToVector("GWW_BothS_J_Count_NNNNNY_PointA", "GWW_BothS_J_Count_YYYNNY_PointA", "GWW_BothS_J_Count_NNNYYY_PointA", "GWW_BothS_J_Count_YYYYYY_PointA"),
      ToVector("Float g_{WW}", "Float g_{WW}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "g_{WW}, J cut, both channels, Point A",
      "N_{S}", "#sigma(g_{WW})", 2);
   
   PsFileB.AddTextPage("Check effect of floating ZZ sector on y_{t}, #tilde{y}_{t} and g_{WW}, J cut");
   PsFileB.InsertNamedDestination("CompareFloatZZJ");
   
   AddPlot(PsFileB, File,
      ToVector("YT_BothS_J_Count_NNNYNN_PointB", "YT_BothS_J_Count_YYYYNN_PointB", "YT_BothS_J_Count_NNNYYY_PointB", "YT_BothS_J_Count_YYYYYY_PointB"),
      ToVector("Float y_{t}", "Float y_{t}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "y_{t}, J cut, both channels, Point B",
      "N_{S}", "#sigma(y_{t})", 1.5);
   AddPlot(PsFileB, File,
      ToVector("YTA_BothS_J_Count_NNNNYN_PointB", "YTA_BothS_J_Count_YYYNYN_PointB", "YTA_BothS_J_Count_NNNYYY_PointB", "YTA_BothS_J_Count_YYYYYY_PointB"),
      ToVector("Float #tilde{y}_{t}", "Float #tilde{y}_{t}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "#tilde{y}_{t}, J cut, both channels, Point B",
      "N_{S}", "#sigma(#tilde{y}_{t})", 1);
   AddPlot(PsFileB, File,
      ToVector("GWW_BothS_J_Count_NNNNNY_PointB", "GWW_BothS_J_Count_YYYNNY_PointB", "GWW_BothS_J_Count_NNNYYY_PointB", "GWW_BothS_J_Count_YYYYYY_PointB"),
      ToVector("Float g_{WW}", "Float g_{WW}, ZZ's", "Float y_{t}, #tilde{y}_{t}, g_{WW}", "Float y_{t}, #tilde{y}_{t}, g_{WW}, ZZ's"),
      "g_{WW}, J cut, both channels, Point B",
      "N_{S}", "#sigma(g_{WW})", 2);

   PsFileA.AddTextPage("Different channels, floating one of y_{t}, #tilde{y}_{t}, g_{WW}, A cut");
   PsFileA.InsertNamedDestination("CompareChannelSingleA");
   
   // AddPlot(PsFileA, File,
   //    ToVector("YT_BothS_A_Count_NNNYNN_PointA", "YT_EMS_A_Count_NNNYNN_PointA", "YT_EES_A_Count_NNNYNN_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "y_{t}, A cut, float only y_{t}, Point A",
   //    "N_{S}", "#sigma(y_{t})", 1);
   // AddPlot(PsFileA, File,
   //    ToVector("YTA_BothS_A_Count_NNNNYN_PointA", "YTA_EMS_A_Count_NNNNYN_PointA", "YTA_EES_A_Count_NNNNYN_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "#tilde{y}_{t}, A cut, float only #tilde{y}_{t}, Point A",
   //    "N_{S}", "#sigma(#tilde{y}_{t})", 0);
   // AddPlot(PsFileA, File,
   //    ToVector("GWW_BothS_A_Count_NNNNNY_PointA", "GWW_EMS_A_Count_NNNNNY_PointA", "GWW_EES_A_Count_NNNNNY_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "g_{WW}, A cut, float only g_{WW}, Point A",
   //    "N_{S}", "#sigma(g_{WW})", 2);

   PsFileB.AddTextPage("Different channels, floating one of y_{t}, #tilde{y}_{t}, g_{WW}, A cut");
   PsFileB.InsertNamedDestination("CompareChannelSingleA");
   
   // AddPlot(PsFileB, File,
   //    ToVector("YT_BothS_A_Count_NNNYNN_PointB", "YT_EMS_A_Count_NNNYNN_PointB", "YT_EES_A_Count_NNNYNN_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "y_{t}, A cut, float only y_{t}, Point B",
   //    "N_{S}", "#sigma(y_{t})", 1.5);
   // AddPlot(PsFileB, File,
   //    ToVector("YTA_BothS_A_Count_NNNNYN_PointB", "YTA_EMS_A_Count_NNNNYN_PointB", "YTA_EES_A_Count_NNNNYN_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "#tilde{y}_{t}, A cut, float only #tilde{y}_{t}, Point B",
   //    "N_{S}", "#sigma(#tilde{y}_{t})", 1);
   // AddPlot(PsFileB, File,
   //    ToVector("GWW_BothS_A_Count_NNNNNY_PointB", "GWW_EMS_A_Count_NNNNNY_PointB", "GWW_EES_A_Count_NNNNNY_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "g_{WW}, A cut, float only g_{WW}, Point B",
   //    "N_{S}", "#sigma(g_{WW})", 2);

   PsFileA.AddTextPage("Different channels, floating all of y_{t}, #tilde{y}_{t}, g_{WW}, A cut");
   PsFileA.InsertNamedDestination("CompareChannelAllA");
   
   // AddPlot(PsFileA, File,
   //    ToVector("YT_BothS_A_Count_NNNYYY_PointA", "YT_EMS_A_Count_NNNYYY_PointA", "YT_EES_A_Count_NNNYYY_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "y_{t}, A cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point A",
   //    "N_{S}", "#sigma(y_{t})", 1);
   // AddPlot(PsFileA, File,
   //    ToVector("YTA_BothS_A_Count_NNNYYY_PointA", "YTA_EMS_A_Count_NNNYYY_PointA", "YTA_EES_A_Count_NNNYYY_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "#tilde{y}_{t}, A cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point A",
   //    "N_{S}", "#sigma(#tilde{y}_{t})", 0);
   // AddPlot(PsFileA, File,
   //    ToVector("GWW_BothS_A_Count_NNNYYY_PointA", "GWW_EMS_A_Count_NNNYYY_PointA", "GWW_EES_A_Count_NNNYYY_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "g_{WW}, A cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point A",
   //    "N_{S}", "#sigma(g_{WW})", 2);
   
   PsFileB.AddTextPage("Different channels, floating all of y_{t}, #tilde{y}_{t}, g_{WW}, A cut");
   PsFileB.InsertNamedDestination("CompareChannelAllA");
   
   // AddPlot(PsFileB, File,
   //    ToVector("YT_BothS_A_Count_NNNYYY_PointB", "YT_EMS_A_Count_NNNYYY_PointB", "YT_EES_A_Count_NNNYYY_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "y_{t}, A cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point B",
   //    "N_{S}", "#sigma(y_{t})", 1.5);
   // AddPlot(PsFileB, File,
   //    ToVector("YTA_BothS_A_Count_NNNYYY_PointB", "YTA_EMS_A_Count_NNNYYY_PointB", "YTA_EES_A_Count_NNNYYY_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "#tilde{y}_{t}, A cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point B",
   //    "N_{S}", "#sigma(#tilde{y}_{t})", 1);
   // AddPlot(PsFileB, File,
   //    ToVector("GWW_BothS_A_Count_NNNYYY_PointB", "GWW_EMS_A_Count_NNNYYY_PointB", "GWW_EES_A_Count_NNNYYY_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "g_{WW}, A cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point B",
   //    "N_{S}", "#sigma(g_{WW})", 2);

   PsFileA.AddTextPage("Different channels, floating one of y_{t}, #tilde{y}_{t}, g_{WW}, J cut");
   PsFileA.InsertNamedDestination("CompareChannelSingleJ");
   
   // AddPlot(PsFileA, File,
   //    ToVector("YT_BothS_J_Count_NNNYNN_PointA", "YT_EMS_J_Count_NNNYNN_PointA", "YT_EES_J_Count_NNNYNN_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "y_{t}, J cut, float only y_{t}, Point A",
   //    "N_{S}", "#sigma(y_{t})", 1);
   // AddPlot(PsFileA, File,
   //    ToVector("YTA_BothS_J_Count_NNNNYN_PointA", "YTA_EMS_J_Count_NNNNYN_PointA", "YTA_EES_J_Count_NNNNYN_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "#tilde{y}_{t}, J cut, float only #tilde{y}_{t}, Point A",
   //    "N_{S}", "#sigma(#tilde{y}_{t})", 0);
   // AddPlot(PsFileA, File,
   //    ToVector("GWW_BothS_J_Count_NNNNNY_PointA", "GWW_EMS_J_Count_NNNNNY_PointA", "GWW_EES_J_Count_NNNNNY_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "g_{WW}, J cut, float only g_{WW}, Point A",
   //    "N_{S}", "#sigma(g_{WW})", 2);

   PsFileB.AddTextPage("Different channels, floating one of y_{t}, #tilde{y}_{t}, g_{WW}, J cut");
   PsFileB.InsertNamedDestination("CompareChannelSingleJ");
   
   // AddPlot(PsFileB, File,
   //    ToVector("YT_BothS_J_Count_NNNYNN_PointB", "YT_EMS_J_Count_NNNYNN_PointB", "YT_EES_J_Count_NNNYNN_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "y_{t}, J cut, float only y_{t}, Point B",
   //    "N_{S}", "#sigma(y_{t})", 1.5);
   // AddPlot(PsFileB, File,
   //    ToVector("YTA_BothS_J_Count_NNNNYN_PointB", "YTA_EMS_J_Count_NNNNYN_PointB", "YTA_EES_J_Count_NNNNYN_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "#tilde{y}_{t}, J cut, float only #tilde{y}_{t}, Point B",
   //    "N_{S}", "#sigma(#tilde{y}_{t})", 1);
   // AddPlot(PsFileB, File,
   //    ToVector("GWW_BothS_J_Count_NNNNNY_PointB", "GWW_EMS_J_Count_NNNNNY_PointB", "GWW_EES_J_Count_NNNNNY_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "g_{WW}, J cut, float only g_{WW}, Point B",
   //    "N_{S}", "#sigma(g_{WW})", 2);

   PsFileA.AddTextPage("Different channels, floating all of y_{t}, #tilde{y}_{t}, g_{WW}, J cut");
   PsFileA.InsertNamedDestination("CompareChannelAllJ");
   
   // AddPlot(PsFileA, File,
   //    ToVector("YT_BothS_J_Count_NNNYYY_PointA", "YT_EMS_J_Count_NNNYYY_PointA", "YT_EES_J_Count_NNNYYY_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "y_{t}, J cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point A",
   //    "N_{S}", "#sigma(y_{t})", 1);
   // AddPlot(PsFileA, File,
   //    ToVector("YTA_BothS_J_Count_NNNYYY_PointA", "YTA_EMS_J_Count_NNNYYY_PointA", "YTA_EES_J_Count_NNNYYY_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "#tilde{y}_{t}, J cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point A",
   //    "N_{S}", "#sigma(#tilde{y}_{t})", 0);
   // AddPlot(PsFileA, File,
   //    ToVector("GWW_BothS_J_Count_NNNYYY_PointA", "GWW_EMS_J_Count_NNNYYY_PointA", "GWW_EES_J_Count_NNNYYY_PointA"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "g_{WW}, J cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point A",
   //    "N_{S}", "#sigma(g_{WW})", 2);
   
   PsFileB.AddTextPage("Different channels, floating all of y_{t}, #tilde{y}_{t}, g_{WW}, J cut");
   PsFileB.InsertNamedDestination("CompareChannelAllJ");
   
   // AddPlot(PsFileB, File,
   //    ToVector("YT_BothS_J_Count_NNNYYY_PointB", "YT_EMS_J_Count_NNNYYY_PointB", "YT_EES_J_Count_NNNYYY_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "y_{t}, J cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point B",
   //    "N_{S}", "#sigma(y_{t})", 1.5);
   // AddPlot(PsFileB, File,
   //    ToVector("YTA_BothS_J_Count_NNNYYY_PointB", "YTA_EMS_J_Count_NNNYYY_PointB", "YTA_EES_J_Count_NNNYYY_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "#tilde{y}_{t}, J cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point B",
   //    "N_{S}", "#sigma(#tilde{y}_{t})", 1);
   // AddPlot(PsFileB, File,
   //    ToVector("GWW_BothS_J_Count_NNNYYY_PointB", "GWW_EMS_J_Count_NNNYYY_PointB", "GWW_EES_J_Count_NNNYYY_PointB"),
   //    ToVector("Both channels", "2e2#mu only", "4e only"),
   //    "g_{WW}, J cut, float all of y_{t}, #tilde{y}_{t}, g_{WW}, Point B",
   //    "N_{S}", "#sigma(g_{WW})", 2);

   PsFileA.AddTextPage("Effect of background! (A)");
   PsFileA.InsertNamedDestination("CompareBackgroundA");

   AddPlot(PsFileA, File,
      ToVector("YT_Both_A_Count_NNNYNN_PointA", "YT_BothS_A_Count_NNNYNN_PointA", "YT_Both_A_Count_NNNYYY_PointA", "YT_BothS_A_Count_NNNYYY_PointA"),
      ToVector("Float y_{t}, S+B", "Float y_{t}, S", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S+B", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S"),
      "y_{t}, A cut, compare S vs. S+B, point A",
      "N_{S}", "y_{t}", 1);
   AddPlot(PsFileA, File,
      ToVector("YTA_Both_A_Count_NNNNYN_PointA", "YTA_BothS_A_Count_NNNNYN_PointA", "YTA_Both_A_Count_NNNYYY_PointA", "YTA_BothS_A_Count_NNNYYY_PointA"),
      ToVector("Float #tilde{y}_{t}, S+B", "Float #tilde{y}_{t}, S", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S+B", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S"),
      "#tilde{y}_{t}, A cut, compare S vs. S+B, point A",
      "N_{S}", "#tilde{y}_{t}", 0);
   AddPlot(PsFileA, File,
      ToVector("GWW_Both_A_Count_NNNNNY_PointA", "GWW_BothS_A_Count_NNNNNY_PointA", "GWW_Both_A_Count_NNNYYY_PointA", "GWW_BothS_A_Count_NNNYYY_PointA"),
      ToVector("Float g_{WW}, S+B", "Float g_{WW}, S", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S+B", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S"),
      "g_{WW}, A cut, compare S vs. S+B, point A",
      "N_{S}", "g_{WW}", 2);

   PsFileA.AddTextPage("Effect of background! (J)");
   PsFileA.InsertNamedDestination("CompareBackgroundJ");

   AddPlot(PsFileA, File,
      ToVector("YT_Both_J_Count_NNNYNN_PointA", "YT_BothS_J_Count_NNNYNN_PointA", "YT_Both_J_Count_NNNYYY_PointA", "YT_BothS_J_Count_NNNYYY_PointA"),
      ToVector("Float y_{t}, S+B", "Float y_{t}, S", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S+B", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S"),
      "y_{t}, J cut, compare S vs. S+B, point A",
      "N_{S}", "y_{t}", 1);
   AddPlot(PsFileA, File,
      ToVector("YTA_Both_J_Count_NNNNYN_PointA", "YTA_BothS_J_Count_NNNNYN_PointA", "YTA_Both_J_Count_NNNYYY_PointA", "YTA_BothS_J_Count_NNNYYY_PointA"),
      ToVector("Float #tilde{y}_{t}, S+B", "Float #tilde{y}_{t}, S", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S+B", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S"),
      "#tilde{y}_{t}, J cut, compare S vs. S+B, point A",
      "N_{S}", "#tilde{y}_{t}", 0);
   AddPlot(PsFileA, File,
      ToVector("GWW_Both_J_Count_NNNNNY_PointA", "GWW_BothS_J_Count_NNNNNY_PointA", "GWW_Both_J_Count_NNNYYY_PointA", "GWW_BothS_J_Count_NNNYYY_PointA"),
      ToVector("Float g_{WW}, S+B", "Float g_{WW}, S", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S+B", "Float y_{t}, #tilde{y}_{t}, g_{WW}, S"),
      "g_{WW}, J cut, compare S vs. S+B, point A",
      "N_{S}", "g_{WW}", 2);

   PsFileA.AddTextPage("Background on ZZ sector (float only ZZ's)");

   AddPlot(PsFileA, File,
      ToVector("A2_BothS_J_Count_YYYNNN_PointA", "A2_BothF_J_Count_YYYNNN_PointA", "A2_Both_J_Count_YYYNNN_PointA"),
      ToVector("S only", "S+B, fix fraction to expectation", "S+B, float fraction"),
      "A_{2}^{ZZ}, J cut, float only ZZ sector",
      "N_{S}", "A_{2}^{ZZ}", 0);
   AddPlot(PsFileA, File,
      ToVector("A3_BothS_J_Count_YYYNNN_PointA", "A3_BothF_J_Count_YYYNNN_PointA", "A3_Both_J_Count_YYYNNN_PointA"),
      ToVector("S only", "S+B, fix fraction to expectation", "S+B, float fraction"),
      "A_{3}^{ZZ}, J cut, float only ZZ sector",
      "N_{S}", "A_{3}^{ZZ}", 0);
   AddPlot(PsFileA, File,
      ToVector("A4_BothS_J_Count_YYYNNN_PointA", "A4_BothF_J_Count_YYYNNN_PointA", "A4_Both_J_Count_YYYNNN_PointA"),
      ToVector("S only", "S+B, fix fraction to expectation", "S+B, float fraction"),
      "A_{4}^{ZZ}, J cut, float only ZZ sector",
      "N_{S}", "A_{4}^{ZZ}", 0);
   
   AddPlot(PsFileA, File,
      ToVector("A4_BothS_J_Count_NNYNNN_PointA", "A4_BothF_J_Count_NNYNNN_PointA", "A4_Both_J_Count_NNYNNN_PointA"),
      ToVector("S only", "S+B, fix fraction to expectation", "S+B, float fraction"),
      "A_{4}^{ZZ}, J cut, float only A4ZZ",
      "N_{S}", "A_{4}^{ZZ}", 0);
   
   AddPlot(PsFileA, File,
      ToVector("A4_BothS_J_Count_NYYNNN_PointA", "A4_BothF_J_Count_NYYNNN_PointA", "A4_Both_J_Count_NYYNNN_PointA"),
      ToVector("S only", "S+B, fix fraction to expectation", "S+B, float fraction"),
      "A_{4}^{ZZ}, J cut, float only A4ZZ and A3ZZ",
      "N_{S}", "A_{4}^{ZZ}", 0);

   AddPlot(PsFileA, File,
      ToVector("A4_BothS_J_Count_YNYNNN_PointA", "A4_BothF_J_Count_YNYNNN_PointA", "A4_Both_J_Count_YNYNNN_PointA"),
      ToVector("S only", "S+B, fix fraction to expectation", "S+B, float fraction"),
      "A_{4}^{ZZ}, J cut, float only A4ZZ and A2ZZ",
      "N_{S}", "A_{4}^{ZZ}", 0);

   File.Close();

   PsFileB.AddTimeStampPage();
   PsFileB.Close();
   PsFileA.AddTimeStampPage();
   PsFileA.Close();

   return 0;
}

void AddPlot(PsFileHelper &PsFile, TFile &File, vector<string> Histograms, vector<string> Labels, string Title, string XAxis, string YAxis, double Level)
{
   int GraphCount = 0;
   vector<TGraphErrors *> Graphs;

   for(int i = 0; i < (int)Histograms.size(); i++)
   {
      TGraphErrors *G = (TGraphErrors *)File.Get(Histograms[i].c_str());
      Graphs.push_back(G);
      if(G != NULL)
         GraphCount = GraphCount + 1;
   }

   cout << "Graph count = " << GraphCount << endl;

   if(GraphCount == 0)
   {
      vector<string> Explanations(8);

      Explanations[0] = "Requested plot with title " + Title + " is empty.";
      Explanations[1] = "";
      Explanations[2] = "";
      Explanations[3] = "";
      Explanations[4] = "";
      Explanations[5] = "";
      Explanations[6] = "";
      Explanations[7] = "";

      PsFile.AddTextPage(Explanations);

      return;
   }

   cout << "Meow" << endl;

   int Colors[7] = {kBlack, kRed, kBlue, kCyan - 3, kYellow - 3, kMagenta - 3, kGreen - 3};

   TLegend Legend(0.6, 0.85, 0.85, 0.6);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);

   for(int i = 0; i < (int)Graphs.size(); i++)
   {
      if(Graphs[i] == NULL)
         continue;

      Graphs[i]->SetLineWidth(2);
      Graphs[i]->SetLineColor(Colors[i]);

      Legend.AddEntry(Graphs[i], Labels[i].c_str(), "l");
   }

   double XMax = -1, XMin = -1, YMax = -1, YMin = -1;

   for(int i = 0; i < (int)Graphs.size(); i++)
   {
      if(Graphs[i] == NULL)
         continue;

      for(int j = 0; j < Graphs[i]->GetN(); j++)
      {
         double x, y;
         Graphs[i]->GetPoint(j, x, y);

         if(XMin < 0 || XMin > x)   XMin = x;
         if(XMax < 0 || XMax < x)   XMax = x;
         if(YMin < 0 || YMin > y)   YMin = y;
         if(YMax < 0 || YMax < y)   YMax = y;
      }
   }

   double DeltaX = XMax / XMin;
   double DeltaY = YMax / YMin;

   TH2D HWorld("HWorld", Form("%s;%s;%s", Title.c_str(), XAxis.c_str(), YAxis.c_str()),
      100, XMin / pow(DeltaX, 0.1), XMax * pow(DeltaX, 0.1),
      100, YMin / pow(DeltaY, 0.1), YMax * pow(DeltaY, 0.4));
   HWorld.SetStats(0);

   TCanvas C;
   C.SetLogx();
   C.SetLogy();

   HWorld.Draw();
   Legend.Draw();

   for(int i = 0; i < (int)Graphs.size(); i++)
   {
      if(Graphs[i] == NULL)
         continue;

      Graphs[i]->Draw("pl");
   }

   TGraph GLine;
   if(Level != NONSENSE)
   {
      GLine.SetPoint(0, -99999, Level);
      GLine.SetPoint(1, +99999, Level);
      GLine.SetLineWidth(2);
      GLine.SetLineStyle(kDashed);
      GLine.Draw("l");
   }

   PsFile.AddCanvas(C);
}

vector<string> ToVector(string S1, string S2, string S3, string S4, string S5, string S6, string S7, string S8)
{
   vector<string> Result;

   Result.push_back(S1);

   if(S2 != "")   Result.push_back(S2);
   if(S3 != "")   Result.push_back(S3);
   if(S4 != "")   Result.push_back(S4);
   if(S5 != "")   Result.push_back(S5);
   if(S6 != "")   Result.push_back(S6);
   if(S7 != "")   Result.push_back(S7);
   if(S8 != "")   Result.push_back(S8);

   return Result;
}



