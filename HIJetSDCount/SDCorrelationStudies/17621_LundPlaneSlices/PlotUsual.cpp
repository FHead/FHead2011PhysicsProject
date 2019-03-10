#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   double R0 = 0.4;

   SetThesisStyle();

   vector<double> Z    = {0.1,   0.5,  5.0,        100,         0.15,     0.1,   0.25};
   vector<double> Beta = {0.0,   1.5,  5.0,        10,          -1,       -2,    0.0};
   vector<int> Color   = {kBlue, kRed, kGreen + 3, kYellow + 3, kMagenta, kCyan, kOrange};
   
   TH2D HWorld("HWorld", ";#DeltaR;z_{g}", 100, 0.0, 0.5, 100, 0.0, 0.85);
   HWorld.SetStats(0);

   vector<TGraph *> Gs;
   for(int i = 0; i < (int)Z.size(); i++)
   {
      TGraph *G = new TGraph;
      G->SetLineColor(Color[i]);
      G->SetLineWidth(3);
      for(double x = 0; x <= 0.5; x = x + 0.01)
      {
         int N = G->GetN();
         G->SetPoint(N, x, Z[i] * pow(x / R0, Beta[i]));
      }
      Gs.push_back(G);
   }

   TCanvas Canvas;

   HWorld.Draw();

   TGraph G1, G2, G3;
   G1.SetPoint(0, 0.1, 0.0);
   G1.SetPoint(1, 0.1, 1.0);
   G2.SetPoint(0, R0, 0.0);
   G2.SetPoint(1, R0, 1.0);
   G3.SetPoint(0, 0.0, 0.5);
   G3.SetPoint(1, 1.0, 0.5);

   G1.SetLineStyle(kDashed);
   G2.SetLineStyle(kDashed);
   G3.SetLineStyle(kDashed);

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   for(TGraph *G : Gs)
      if(G != NULL)
         G->Draw("l");

   TLegend Legend(0.50, 0.87, 0.80, 0.60);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(1);
   for(int i = 0; i < (int)Z.size(); i++)
      Legend.AddEntry(Gs[i], Form("(%.02f, %.02f)", Z[i], Beta[i]), "l");
   Legend.Draw();

   HWorld.Draw("axis same");

   Canvas.SaveAs("GroomingPlot.pdf");

   for(TGraph *G : Gs)
      if(G != NULL)
         delete G;
   
   return 0;
}







