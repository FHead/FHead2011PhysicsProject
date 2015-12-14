#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLatex.h"

int main()
{
   TH2D HWorld("HWorld", ";M_{R} [GeV];R^{2} [GeV]", 10, 300, 3500, 10, 0.11, 0.5);
   HWorld.SetStats(0);

   TGraph FitRegion;
   FitRegion.SetPoint(0, 300, 0.11);
   FitRegion.SetPoint(1, 300, 0.50);
   FitRegion.SetPoint(2, 450, 0.50);
   FitRegion.SetPoint(3, 450, 0.30);
   FitRegion.SetPoint(4, 650, 0.30);
   FitRegion.SetPoint(5, 650, 0.20);
   FitRegion.SetPoint(6, 1000, 0.20);
   FitRegion.SetPoint(7, 1000, 0.11);
   FitRegion.SetPoint(8, 300, 0.11);
   FitRegion.SetFillColor(kGreen - 3);
   FitRegion.SetLineColor(kBlack);

   TGraph S1;
   S1.SetPoint(0, 2000, 0.11);
   S1.SetPoint(1, 2000, 0.30);
   S1.SetPoint(2, 3500, 0.30);
   S1.SetPoint(3, 3500, 0.11);
   S1.SetPoint(4, 2000, 0.11);
   S1.SetFillColor(kBlue - 10);
   
   TGraph S2;
   S2.SetPoint(0, 2000, 0.30);
   S2.SetPoint(1, 2000, 0.50);
   S2.SetPoint(2, 3500, 0.50);
   S2.SetPoint(3, 3500, 0.30);
   S2.SetPoint(4, 2000, 0.30);
   S2.SetFillColor(kBlue - 10);

   TGraph S3;
   S3.SetPoint(0, 1000, 0.11);
   S3.SetPoint(1, 1000, 0.30);
   S3.SetPoint(2, 2000, 0.30);
   S3.SetPoint(3, 2000, 0.11);
   S3.SetPoint(4, 1000, 0.11);
   S3.SetFillColor(kBlue - 10);

   TGraph S4;
   S4.SetPoint(0, 1000, 0.30);
   S4.SetPoint(1, 1000, 0.50);
   S4.SetPoint(2, 2000, 0.50);
   S4.SetPoint(3, 2000, 0.30);
   S4.SetPoint(4, 1000, 0.30);
   S4.SetFillColor(kBlue - 10);

   TGraph S5;
   S5.SetPoint(0, 650, 0.20);
   S5.SetPoint(1, 650, 0.30);
   S5.SetPoint(2, 1000, 0.30);
   S5.SetPoint(3, 1000, 0.20);
   S5.SetPoint(4, 650, 0.20);
   S5.SetFillColor(kBlue - 10);

   TGraph S6;
   S6.SetPoint(0, 450, 0.30);
   S6.SetPoint(1, 450, 0.50);
   S6.SetPoint(2, 1000, 0.50);
   S6.SetPoint(3, 1000, 0.30);
   S6.SetPoint(4, 450, 0.30);
   S6.SetFillColor(kBlue - 10);

   TLatex Latex;
   Latex.SetTextAlign(22);
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.04);

   TCanvas C;

   HWorld.Draw();
   FitRegion.Draw("F");
   FitRegion.Draw("L");
   S1.Draw("F");
   S1.Draw("L");
   S2.Draw("F");
   S2.Draw("L");
   S3.Draw("F");
   S3.Draw("L");
   S4.Draw("F");
   S4.Draw("L");
   S5.Draw("F");
   S5.Draw("L");
   S6.Draw("F");
   S6.Draw("L");
   Latex.DrawLatex(650, 0.15, "Fit region");
   Latex.DrawLatex(2750, 0.205, "Signal region 1");
   Latex.DrawLatex(2750, 0.4, "Signal region 2");
   Latex.DrawLatex(1500, 0.205, "Signal region 3");
   Latex.DrawLatex(1500, 0.4, "Signal region 4");
   // Latex.DrawLatex(825, 0.25, "#splitline{Signal}{#splitline{region}{5}}");
   Latex.DrawLatex(825, 0.275, "Signal");
   Latex.DrawLatex(825, 0.25, "region");
   Latex.DrawLatex(825, 0.225, "5");
   // Latex.DrawLatex(725, 0.4, "#splitline{Signal}{#splitline{region}{6}}");
   Latex.DrawLatex(725, 0.425, "Signal");
   Latex.DrawLatex(725, 0.40, "region");
   Latex.DrawLatex(725, 0.375, "6");
   HWorld.Draw("axis same");

   C.SaveAs("Regions.png");
   C.SaveAs("Regions.C");
   C.SaveAs("Regions.eps");
   C.SaveAs("Regions.pdf");
}




