#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"

#include "CustomAssert.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> Labels       = CL.GetStringVector("label");
   vector<string> FileNames    = CL.GetStringVector("file");
   vector<string> Numerators   = CL.GetStringVector("numerator");
   vector<string> Denominators = CL.GetStringVector("denominator");
   string OutputFileName       = CL.Get("output");
   string Title                = CL.Get("title", ";;Efficiency");
   double XMin                  = CL.GetDouble("xmin");
   double XMax                  = CL.GetDouble("xmax");
   double YMin                  = CL.GetDouble("ymin", 0.0);
   double YMax                  = CL.GetDouble("ymax", 1.1);
   vector<int> Colors          = CL.GetIntVector("color", vector<int>({kBlack, kRed, kGreen + 3, kYellow, kMagenta}));

   int N = FileNames.size();

   Assert(N == Labels.size(),       "Number of files != number of labels");
   Assert(N == Numerators.size(),   "Number of files != number of numberators");
   Assert(N == Denominators.size(), "Number of files != number of denominators");

   vector<TGraphAsymmErrors> Graphs(N);
   for(int i = 0; i < N; i++)
   {
      TFile File(FileNames[i].c_str());

      TH1D *H1 = (TH1D *)File.Get(Numerators[i].c_str());
      TH1D *H2 = (TH1D *)File.Get(Denominators[i].c_str());

      if(H1 != nullptr && H2 != nullptr)
         Graphs[i].Divide(H1, H2);

      File.Close();
   }

   TCanvas Canvas;

   TH2D HWorld("HWorld", Title.c_str(), 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.Draw();

   TGraph GLine;
   GLine.SetLineStyle(kDashed);
   GLine.SetPoint(0, XMin, 1);
   GLine.SetPoint(1, XMax, 1);
   GLine.Draw("l");

   for(int i = 0; i < N; i++)
   {
      Graphs[i].SetMarkerColor(Colors[i]);
      Graphs[i].SetLineColor(Colors[i]);
      Graphs[i].Draw("pl");
   }

   TLegend Legend(0.35, 0.2, 0.65, 0.4);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int i = 0; i < N; i++)
      Legend.AddEntry(&Graphs[i], Labels[i].c_str(), "pl");
   Legend.Draw();

   Canvas.SaveAs(OutputFileName.c_str());

   return 0;
}



