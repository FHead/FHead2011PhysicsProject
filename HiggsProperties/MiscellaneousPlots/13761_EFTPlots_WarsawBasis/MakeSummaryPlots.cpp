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
   PsFileHelper PsFile("WarsawBasisFirstGlance.ps");

   PsFile.AddTextPage("All-zero point: true value is zero for everything");

   TFile File("AllGraphs.root");

   AddPlot(PsFile, File,
      ToVector("CWW_BothS_I_Count_NNNYYYYYY_WithSquare_Point0",
         "CWWD_BothS_I_Count_NNNYYYYYY_WithSquare_Point0",
         "CWB_BothS_I_Count_NNNYYYYYY_WithSquare_Point0",
         "CWBD_BothS_I_Count_NNNYYYYYY_WithSquare_Point0",
         "CBB_BothS_I_Count_NNNYYYYYY_WithSquare_Point0",
         "CBBD_BothS_I_Count_NNNYYYYYY_WithSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float all cVV together, I Cut",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CWW_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CWWD_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CWB_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CWBD_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CBB_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CBBD_BothS_J_Count_NNNYYYYYY_WithSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float all cVV together, J Cut",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CWW_BothS_I_Count_NNNYNNNNN_WithSquare_Point0",
         "CWWD_BothS_I_Count_NNNNYNNNN_WithSquare_Point0",
         "CWB_BothS_I_Count_NNNNNYNNN_WithSquare_Point0",
         "CWBD_BothS_I_Count_NNNNNNYNN_WithSquare_Point0",
         "CBB_BothS_I_Count_NNNNNNNYN_WithSquare_Point0",
         "CBBD_BothS_I_Count_NNNNNNNNY_WithSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float each cVV individually, I Cut",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CWW_BothS_J_Count_NNNYNNNNN_WithSquare_Point0",
         "CWWD_BothS_J_Count_NNNNYNNNN_WithSquare_Point0",
         "CWB_BothS_J_Count_NNNNNYNNN_WithSquare_Point0",
         "CWBD_BothS_J_Count_NNNNNNYNN_WithSquare_Point0",
         "CBB_BothS_J_Count_NNNNNNNYN_WithSquare_Point0",
         "CBBD_BothS_J_Count_NNNNNNNNY_WithSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float each cVV individually, J Cut",
      "N_{S}", "#sigma", 0);

   AddPlot(PsFile, File,
      ToVector("CWW_BothS_I_Count_NYNYYYYYY_WithSquare_Point0",
         "CWWD_BothS_I_Count_NYNYYYYYY_WithSquare_Point0",
         "CWB_BothS_I_Count_NYNYYYYYY_WithSquare_Point0",
         "CWBD_BothS_I_Count_NYNYYYYYY_WithSquare_Point0",
         "CBB_BothS_I_Count_NYNYYYYYY_WithSquare_Point0",
         "CBBD_BothS_I_Count_NYNYYYYYY_WithSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float all cVV together and DeltaCW, I Cut",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CWW_BothS_J_Count_NYNYYYYYY_WithSquare_Point0",
         "CWWD_BothS_J_Count_NYNYYYYYY_WithSquare_Point0",
         "CWB_BothS_J_Count_NYNYYYYYY_WithSquare_Point0",
         "CWBD_BothS_J_Count_NYNYYYYYY_WithSquare_Point0",
         "CBB_BothS_J_Count_NYNYYYYYY_WithSquare_Point0",
         "CBBD_BothS_J_Count_NYNYYYYYY_WithSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float all cVV together and DeltaCW, J Cut",
      "N_{S}", "#sigma", 0);

   AddPlot(PsFile, File,
      ToVector("CWW_BothS_I_Count_NNYYYYYYY_WithSquare_Point0",
         "CWWD_BothS_I_Count_NNYYYYYYY_WithSquare_Point0",
         "CWB_BothS_I_Count_NNYYYYYYY_WithSquare_Point0",
         "CWBD_BothS_I_Count_NNYYYYYYY_WithSquare_Point0",
         "CBB_BothS_I_Count_NNYYYYYYY_WithSquare_Point0",
         "CBBD_BothS_I_Count_NNYYYYYYY_WithSquare_Point0",
         "DeltaM_BothS_I_Count_NNYYYYYYY_WithSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd", "DeltaM"),
      "Signal only, float all cVV together and DeltaM, I Cut",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CWW_BothS_J_Count_NNYYYYYYY_WithSquare_Point0",
         "CWWD_BothS_J_Count_NNYYYYYYY_WithSquare_Point0",
         "CWB_BothS_J_Count_NNYYYYYYY_WithSquare_Point0",
         "CWBD_BothS_J_Count_NNYYYYYYY_WithSquare_Point0",
         "CBB_BothS_J_Count_NNYYYYYYY_WithSquare_Point0",
         "CBBD_BothS_J_Count_NNYYYYYYY_WithSquare_Point0",
         "DeltaM_BothS_J_Count_NNYYYYYYY_WithSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd", "DeltaM"),
      "Signal only, float all cVV together and DeltaM, J Cut",
      "N_{S}", "#sigma", 0);

   AddPlot(PsFile, File,
      ToVector("CWW_BothS_I_Count_NNNYYYYYY_NoSquare_Point0",
         "CWWD_BothS_I_Count_NNNYYYYYY_NoSquare_Point0",
         "CWB_BothS_I_Count_NNNYYYYYY_NoSquare_Point0",
         "CWBD_BothS_I_Count_NNNYYYYYY_NoSquare_Point0",
         "CBB_BothS_I_Count_NNNYYYYYY_NoSquare_Point0",
         "CBBD_BothS_I_Count_NNNYYYYYY_NoSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float all cVV together, I Cut (no square)",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CWW_BothS_J_Count_NNNYYYYYY_NoSquare_Point0",
         "CWWD_BothS_J_Count_NNNYYYYYY_NoSquare_Point0",
         "CWB_BothS_J_Count_NNNYYYYYY_NoSquare_Point0",
         "CWBD_BothS_J_Count_NNNYYYYYY_NoSquare_Point0",
         "CBB_BothS_J_Count_NNNYYYYYY_NoSquare_Point0",
         "CBBD_BothS_J_Count_NNNYYYYYY_NoSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float all cVV together, J Cut (no square)",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CWW_BothS_I_Count_NNNYNNNNN_NoSquare_Point0",
         "CWWD_BothS_I_Count_NNNNYNNNN_NoSquare_Point0",
         "CWB_BothS_I_Count_NNNNNYNNN_NoSquare_Point0",
         "CWBD_BothS_I_Count_NNNNNNYNN_NoSquare_Point0",
         "CBB_BothS_I_Count_NNNNNNNYN_NoSquare_Point0",
         "CBBD_BothS_I_Count_NNNNNNNNY_NoSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float each cVV individually, I Cut (no square)",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CWW_BothS_J_Count_NNNYNNNNN_NoSquare_Point0",
         "CWWD_BothS_J_Count_NNNNYNNNN_NoSquare_Point0",
         "CWB_BothS_J_Count_NNNNNYNNN_NoSquare_Point0",
         "CWBD_BothS_J_Count_NNNNNNYNN_NoSquare_Point0",
         "CBB_BothS_J_Count_NNNNNNNYN_NoSquare_Point0",
         "CBBD_BothS_J_Count_NNNNNNNNY_NoSquare_Point0"),
      ToVector("CWW", "CWWd", "CWB", "CWBd", "CBB", "CBBd"),
      "Signal only, float each cVV individually, J Cut (no square)",
      "N_{S}", "#sigma", 0);

   AddPlot(PsFile, File,
      ToVector("CWW_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CWW_BothS_J_Count_NNNYYYYYY_NoSquare_Point0",
         "CWWD_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CWWD_BothS_J_Count_NNNYYYYYY_NoSquare_Point0"),
      ToVector("CWW (with square)", "CWW (no square)", "CWWd (with square)", "CWWd (no square)"),
      "Signal only, float all cVV together, J Cut",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CWB_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CWB_BothS_J_Count_NNNYYYYYY_NoSquare_Point0",
         "CWBD_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CWBD_BothS_J_Count_NNNYYYYYY_NoSquare_Point0"),
      ToVector("CWB (with square)", "CWB (no square)", "CWBd (with square)", "CWBd (no square)"),
      "Signal only, float all cVV together, J Cut",
      "N_{S}", "#sigma", 0);
   AddPlot(PsFile, File,
      ToVector("CBB_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CBB_BothS_J_Count_NNNYYYYYY_NoSquare_Point0",
         "CBBD_BothS_J_Count_NNNYYYYYY_WithSquare_Point0",
         "CBBD_BothS_J_Count_NNNYYYYYY_NoSquare_Point0"),
      ToVector("CBB (with square)", "CBB (no square)", "CBBd (with square)", "CBBd (no square)"),
      "Signal only, float all cVV together, J Cut",
      "N_{S}", "#sigma", 0);
   
   File.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

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

   int Colors[8] = {kBlack, kRed, kBlue, kCyan - 3, kYellow - 3, kMagenta - 3, kGreen - 3, kRed - 3};

   TLegend Legend(0.6, 0.85, 0.85, 0.55);
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
      100, YMin / pow(DeltaY, 0.1), YMax * pow(DeltaY, 0.6));
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



