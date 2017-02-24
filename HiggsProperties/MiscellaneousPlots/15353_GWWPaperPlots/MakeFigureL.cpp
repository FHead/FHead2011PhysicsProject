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

int main(int argc, char *argv[])
{
   string GraphName = "Meow";
   string OutputBase = "Meow";

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " GraphName OutputBase" << endl;
      return -1;
   }

   GraphName = argv[1];
   OutputBase = argv[2];

   SetThesisStyle();

   TFile File("FigureLGraphs.root");

   TGraphAsymmErrors *G = (TGraphAsymmErrors *)File.Get(GraphName.c_str());
   
   TCanvas C;

   TH2D HWorld("HWorld", ";Luminosity (fb^{-1});p-Value", 100, 10, 10000, 100, 0.001, 1);
   HWorld.SetStats(0);
   HWorld.Draw();

   G->Draw("p");

   TGraph G1, G2;
   G1.SetPoint(0, 0, 0.05);
   G1.SetPoint(1, 10000000, 0.05);
   G1.SetLineStyle(kDashed);
   G2.SetPoint(0, 0, 0.01);
   G2.SetPoint(1, 10000000, 0.01);
   G2.SetLineStyle(kDashed);

   G1.Draw("l");
   G2.Draw("l");

   C.SetLogx();
   C.SetLogy();

   C.SaveAs(Form("Plots/FigureL_%s.png", OutputBase.c_str()));
   C.SaveAs(Form("Plots/FigureL_%s.C", OutputBase.c_str()));
   C.SaveAs(Form("Plots/FigureL_%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("Plots/FigureL_%s.pdf", OutputBase.c_str()));

   File.Close();

   return 0;
}

