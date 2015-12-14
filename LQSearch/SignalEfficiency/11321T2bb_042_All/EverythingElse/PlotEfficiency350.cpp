#include <iostream>
using namespace std;

#include "TGraphErrors.h"

#include "PlotHelper2.h"

int main()
{
   TGraphErrors GEfficiency;

   GEfficiency.SetPoint(0, 0, 0.0441279);
   GEfficiency.SetPointError(0, 0, 0.00365232);
   GEfficiency.SetPoint(1, 50, 0.0502351);
   GEfficiency.SetPointError(1, 0, 0.00421607);
   GEfficiency.SetPoint(2, 75, 0.0484023);
   GEfficiency.SetPointError(2, 0, 0.00398219);
   GEfficiency.SetPoint(3, 100, 0.0419515);
   GEfficiency.SetPointError(3, 0, 0.00339808);
   GEfficiency.SetPoint(4, 125, 0.0340112);
   GEfficiency.SetPointError(4, 0, 0.0027447);
   GEfficiency.SetPoint(5, 150, 0.030321);
   GEfficiency.SetPointError(5, 0, 0.00249348);
   GEfficiency.SetPoint(6, 175, 0.0203025);
   GEfficiency.SetPointError(6, 0, 0.00163953);
   GEfficiency.SetPoint(7, 200, 0.0116859);
   GEfficiency.SetPointError(7, 0, 0.000979174);
   GEfficiency.SetPoint(8, 225, 0.00699202);
   GEfficiency.SetPointError(8, 0, 0.000698276);
   GEfficiency.SetPoint(9, 250, 0.00542761);
   GEfficiency.SetPointError(9, 0, 0.000446696);

   for(int i = 1; i < GEfficiency.GetN(); i++)
   {
      double X;
      double Y;
      GEfficiency.GetPoint(i, X, Y);
      Y = Y * 0.96 * 0.96;

      double EX = GEfficiency.GetErrorX(i);
      double EY = GEfficiency.GetErrorY(i) * 0.96 * 0.96;

      GEfficiency.SetPoint(i, X, Y);
      GEfficiency.SetPointError(i, EX, EY);
   }

   PsFileHelper PsFile("ASDG.ps");
   PsFile.AddPlot(GEfficiency, "apl");
   PsFile.Close();

   TCanvas C("C", "C", 1024, 1024);

   TH1D HWorld("HWorld", ";Neutralino mass (GeV);Efficiency", 1, -25, 275);
   HWorld.SetStats(0);
   HWorld.SetMaximum(0.07);
   HWorld.Draw();

   GEfficiency.SetLineWidth(2);
   GEfficiency.Draw("p");

   C.SaveAs("Efficiency350.png");
   C.SaveAs("Efficiency350.C");
   C.SaveAs("Efficiency350.eps");
   C.SaveAs("Efficiency350.pdf");

   return 0;
}





