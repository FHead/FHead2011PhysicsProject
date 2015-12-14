#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TGraph.h"

#include "SetStyle.h"

int main()
{
   TFile F1("PointA_BothS_J.root");
   TFile F2("PointSM14572_BothS_J.root");

   TTree *Tree1 = (TTree *)F1.Get("Tree");
   TTree *Tree2 = (TTree *)F2.Get("Tree");

   Tree2->SetMarkerColor(kRed);
   Tree2->SetLineColor(kRed);
   Tree2->SetFillColor(kRed);

   SetThesisStyle();

   double x[101] = {0};
   for(int i = 0; i <= 100; i++)
      x[i] = 50 * pow(40000 / 50, 0.01 * i);

   TH2D HA("HA", ";Event Count;Likelihood away from being negative (sigmas)", 100, x, 100, -20, 20);
   HA.SetStats(0);

   TH2D H5("H5", ";Event Count;Likelihood away from being negative (sigmas)", 100, x, 100, -20, 20);
   
   TGraph G;
   G.SetPoint(0, 0, 0);
   G.SetPoint(1, 100000, 0);

   TCanvas C;

   Tree1->Draw("S:2*N>>HA", "N", "colz");
   Tree2->Draw("S:2*N*1.06913094473*1.06913094473>>H5", "N", "colz");
   
   HA.Draw("colz");
   H5.Draw("col same");
   G.Draw("l");

   C.SetLogx();
   C.SetLogz();
   C.SaveAs("Meow.png");

   F2.Close();
   F1.Close();

   return 0;
}
