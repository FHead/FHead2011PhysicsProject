#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TEllipse.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   double R0 = CL.GetDouble("R0", 0.4);
   bool Zoom = CL.GetBool("Zoom", false);

   TH2D HWorld("HWorld", ";ln(1/#theta);ln(z#theta)", 100, 0, (Zoom?3:5), 100, (Zoom?-7:-10), (Zoom?1.5:2.0));
   HWorld.SetStats(0);

   vector<double> Z    = {0.1,   0.5,  5.0,        100,         0.15,     0.1,   0.25};
   vector<double> Beta = {0.0,   1.5,  5.0,        10,          -1,       -2,    0.0};
   vector<int> Color   = {kBlue, kRed, kGreen + 3, kYellow + 3, kMagenta, kCyan, kOrange};

   vector<TGraph *> Gs;
   for(int i = 0; i < (int)Z.size(); i++)
   {
      TGraph *G = new TGraph;
      G->SetLineColor(Color[i]);
      G->SetLineWidth(3);
      G->SetPoint(0, -10, log(Z[i]) - Beta[i] * log(R0) - (Beta[i] + 1) * (-10));
      G->SetPoint(1, +10, log(Z[i]) - Beta[i] * log(R0) - (Beta[i] + 1) * (+10));
      Gs.push_back(G);
   }

   TGraph G1, G2, G3;
   G1.SetLineStyle(kDashed);
   G1.SetPoint(0, -log(R0), -1000);
   G1.SetPoint(1, -log(R0), +1000);
   G2.SetLineStyle(kDashed);
   G2.SetPoint(0, 0, log(0.5));
   G2.SetPoint(1, 1000, log(0.5) - 1000);
   G3.SetLineStyle(kDashed);
   G3.SetPoint(0, -log(0.1), -1000);
   G3.SetPoint(1, -log(0.1), +1000);

   TEllipse E(1.2, -4.5, 0.3, 1.4, 0, 360, -5);
   E.SetLineStyle(kDashed);
   E.SetFillStyle(0);

   TCanvas Canvas;

   HWorld.Draw("axis");

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");
   E.Draw("l");

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

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.SetNDC();
   Latex.SetTextAlign(22);
   if(Zoom == false)
   {
      Latex.DrawLatex(0.25, 0.915, Form("#theta = %.2f", R0));
      Latex.DrawLatex(0.45, 0.915, Form("#theta = %.2f", 0.1));
   }
   else
   {
      Latex.DrawLatex(0.33, 0.915, Form("#theta = %.2f", R0));
      Latex.DrawLatex(0.68, 0.915, Form("#theta = %.2f", 0.1));
   }
   Latex.SetTextAlign(12);
   if(Zoom == false)
      Latex.DrawLatex(0.87, 0.38, "z = 0.5");
   else
      Latex.DrawLatex(0.87, 0.40, "z = 0.5");
   Latex.SetTextAlign(22);
   if(Zoom == false)
      Latex.DrawLatex(0.30, 0.35, "hurricane");
   else
      Latex.DrawLatex(0.45, 0.20, "recoil");

   Canvas.SaveAs("LundPlane.pdf");
   
   for(TGraph *G : Gs)
      if(G != NULL)
         delete G;

   return 0;
}







