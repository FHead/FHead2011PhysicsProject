#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string Graph = "Both_J_Y";
   string OutputBase = "Meow";

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " GraphName OutputBase" << endl;
      return -1;
   }

   Graph = argv[1];
   OutputBase = argv[2];

   TFile File("FigureMGraphs.root");

   TGraph *G = (TGraph *)File.Get(Graph.c_str());

   TCanvas C;

   TH2D HWorld("HWorld", ";Luminosity (fb^{-1});Model separation p-value", 100, 10, 10000, 100, 0.001, 1);
   HWorld.SetStats(0);
   HWorld.Draw();

   G->Draw("pl");

   TGraph G1, G2;
   G1.SetLineStyle(kDashed);
   G1.SetPoint(0, 0, 0.05);
   G1.SetPoint(1, 100000000, 0.05);
   G1.Draw("l");
   G2.SetLineStyle(kDashed);
   G2.SetPoint(0, 0, 0.01);
   G2.SetPoint(1, 100000000, 0.01);
   G2.Draw("l");

   C.SetLogx();
   C.SetLogy();

   C.SaveAs(Form("Plots/FigureM_%s.png", OutputBase.c_str()));
   C.SaveAs(Form("Plots/FigureM_%s.C", OutputBase.c_str()));
   C.SaveAs(Form("Plots/FigureM_%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("Plots/FigureM_%s.pdf", OutputBase.c_str()));

   return 0;
}

