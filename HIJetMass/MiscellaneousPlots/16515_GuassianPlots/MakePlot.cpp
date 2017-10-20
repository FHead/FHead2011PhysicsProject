#include <iostream>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   double CoreWidth = 0.075;
   double BigWidth = 0.2;
   double Percentage = 0.8;

   TH1D HPP("HPP", ";#eta/#phi;", 1000, -0.5, 0.5);
   TH1D HAA("HAA", ";#eta/#phi;", 1000, -0.5, 0.5);
   TH1D HAACore("HAACore", ";#eta/#phi;", 1000, -0.5, 0.5);
   TH1D HAAPeriphery("HAAPeriphery", ";#eta/#phi;", 1000, -0.5, 0.5);

   HPP.SetStats(0);

   for(int i = 1; i <= 1000; i++)
   {
      double x = HPP.GetBinCenter(i);

      HPP.SetBinContent(i, x, exp(-x * x / (2 * CoreWidth * CoreWidth)) / sqrt(2 * M_PI * CoreWidth * CoreWidth));
      HAACore.SetBinContent(i, x, exp(-x * x / (2 * CoreWidth * CoreWidth)) / sqrt(2 * M_PI * CoreWidth * CoreWidth) * Percentage);
      HAAPeriphery.SetBinContent(i, x, exp(-x * x / (2 * BigWidth * BigWidth)) / sqrt(2 * M_PI * BigWidth * BigWidth) * (1 - Percentage));

      HAA.SetBinContent(i, HAACore.GetBinContent(i) + HAAPeriphery.GetBinContent(i));
   }

   HPP.SetLineWidth(3);
   HAA.SetLineWidth(3);
   HAAPeriphery.SetLineWidth(3);
   
   HPP.SetLineColor(kGreen - 3);
   HAA.SetLineColor(kYellow + 3);
   HAAPeriphery.SetLineColor(kYellow + 3);

   HAAPeriphery.SetLineStyle(kDashed);

   TCanvas C;

   HPP.Draw();
   HAA.Draw("same");
   HAAPeriphery.Draw("same");

   TLegend Legend(0.15, 0.60, 0.45, 0.85);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HPP, "pp jet", "l");
   Legend.AddEntry(&HAA, "Subtracted", "l");
   Legend.AddEntry("", "PbPb jet", "");
   Legend.AddEntry(&HAAPeriphery, "Redistributed", "l");
   Legend.AddEntry("", "energy", "");
   Legend.Draw();

   C.SaveAs("Result.png");
   C.SaveAs("Result.C");
   C.SaveAs("Result.eps");
   C.SaveAs("Result.pdf");

   return 0;
}



