#include <iostream>
#include <cmath>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"

int main()
{
   TGraph G0, G1, G2, G3;

   double Window = 100;
   double Center = 0;
   double Step = 75;

   for(int i = 0; i <= Step; i++)
   {
      double K0 = 1 / (Window / 2 * 0 + 1);
      double K1 = 1 / (Window / 2 * 0.02 + 1);
      double K2 = 1 / (Window / 2 * 0.1 + 1);
      double K3 = 1 / (Window / 2 * 2 + 1);

      double Delta = Window * (i - Step / 2) / Step;

      double FDelta0 = K0 * Delta * (fabs(Delta * 0) + 1);
      double FDelta1 = K1 * Delta * (fabs(Delta * 0.02) + 1);
      double FDelta2 = K2 * Delta * (fabs(Delta * 0.1) + 1);
      double FDelta3 = K3 * Delta * (fabs(Delta * 2) + 1);

      G0.SetPoint(i, Center + FDelta0, 0.5);
      G1.SetPoint(i, Center + FDelta1, 1.5);
      G2.SetPoint(i, Center + FDelta2, 2.5);
      G3.SetPoint(i, Center + FDelta3, 3.5);
   }

   TH2D HWorld("HWorld", ";Grid Point Coordinate;A_{S}", 100, -60, 60, 4, 0, 4);
   HWorld.SetStats(false);

   HWorld.GetXaxis()->SetTitleOffset(0.8);
   HWorld.GetYaxis()->SetTitleOffset(0.6);
   HWorld.GetXaxis()->SetTitleSize(0.05);
   HWorld.GetYaxis()->SetTitleSize(0.075);
   HWorld.GetXaxis()->SetLabelSize(0.05);
   HWorld.GetYaxis()->SetLabelSize(0.075);
   HWorld.GetYaxis()->SetBinLabel(1, "0");
   HWorld.GetYaxis()->SetBinLabel(2, "0.02");
   HWorld.GetYaxis()->SetBinLabel(3, "0.1");
   HWorld.GetYaxis()->SetBinLabel(4, "2");

   G0.SetMarkerStyle(6);
   G1.SetMarkerStyle(6);
   G2.SetMarkerStyle(6);
   G3.SetMarkerStyle(6);

   TCanvas C("C", "C", 1024, 512);
   HWorld.Draw();
   G0.Draw("p");
   G1.Draw("p");
   G2.Draw("p");
   G3.Draw("p");
   C.SaveAs("MultiDimensionalDetails-Integral-Attractor.png");
   C.SaveAs("MultiDimensionalDetails-Integral-Attractor.C");
   C.SaveAs("MultiDimensionalDetails-Integral-Attractor.eps");
   C.SaveAs("MultiDimensionalDetails-Integral-Attractor.pdf");

   return 0;
}


