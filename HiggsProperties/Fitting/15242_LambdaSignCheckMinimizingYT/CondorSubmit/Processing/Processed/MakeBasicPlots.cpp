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
   TFile F1("SMVV_Both_ggPDF_J.root");
   TFile F2("SMVV_Both_noPDF_J.root");
   TFile F3("5plet_Both_noPDF_J.root");

   TTree *Tree1 = (TTree *)F1.Get("Tree");
   TTree *Tree2 = (TTree *)F2.Get("Tree");
   TTree *Tree3 = (TTree *)F3.Get("Tree");

   Tree2->SetMarkerColor(kRed);
   Tree2->SetLineColor(kRed);
   Tree2->SetFillColor(kRed);

   SetThesisStyle();

   double x[101] = {0};
   for(int i = 0; i <= 100; i++)
      x[i] = 50 * pow(40000 / 50, 0.01 * i);

   TH2D HA("HA", ";Event Count;p-value for being negative", 100, x, 100, 0, 1);
   HA.SetStats(0);

   TH2D H5("H5", ";Event Count;p-value for being negative", 100, x, 100, 0, 1);
   
   TH2D H3("H3", ";Event Count;p-value for being negative", 100, x, 100, 0, 1);
   
   TGraph G;
   G.SetPoint(0, 0, 0);
   G.SetPoint(1, 100000, 0);

   TCanvas C;

   Tree1->Draw("P:2*N>>HA", "N", "colz");
   Tree2->Draw("P:2*N*1.06913094473>>H5", "N", "colz");
   Tree3->Draw("P:2*N*1.06913094473*1.06913094473>>H3", "N", "colz");
   
   HA.Draw("colz");
   H5.Draw("col same");
   H3.Draw("col same");
   G.Draw("l");

   C.SetLogx();
   C.SetLogz();
   C.SaveAs("Meow.png");

   F2.Close();
   F1.Close();

   return 0;
}
