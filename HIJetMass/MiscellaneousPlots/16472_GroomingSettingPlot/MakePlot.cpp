#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisSmallStyle();

   TGraph G0, G7, GN;

   double XMin = 0;
   double XMax = 0.5;

   for(int i = 0; i < 1000; i++)
   {
      double X = (i + 0.5) / 1000 * (XMax - XMin) + XMin;
      
      G0.SetPoint(i, X, 0.1);
      G7.SetPoint(i, X, 0.5 * pow(X / 0.4, 1.5));
      GN.SetPoint(i, X, 0.25 * pow(X / 0.4, -1.0));
   }

   G0.SetLineWidth(3);
   G0.SetLineColor(kRed);

   G7.SetLineWidth(3);
   G7.SetLineColor(kBlue);

   GN.SetLineWidth(3);
   GN.SetLineColor(kGreen);

   TGraph GLine, GLine2;
   GLine.SetPoint(0, 0.10, 0.00);
   GLine.SetPoint(1, 0.10, 9.99);
   GLine.SetPoint(2, 0.00, 9.99);
   GLine.SetPoint(3, 0.00, 0.00);

   GLine2.SetPoint(0, 0.40, 0.00);
   GLine2.SetPoint(1, 0.40, 9.99);
   GLine2.SetPoint(2, 9.99, 9.99);
   GLine2.SetPoint(3, 9.99, 0.50);
   GLine2.SetPoint(4, 0.00, 0.50);

   GLine.SetFillStyle(3354);
   GLine.SetFillColor(kGray);

   GLine2.SetLineStyle(kDashed);

   TH2D HWorld("HWorld", ";#DeltaR;z_{g} threshold", 100, 0, 0.5, 100, 0, 0.7);
   HWorld.SetStats(0);

   HWorld.GetXaxis()->SetTitleSize(0.05);
   HWorld.GetYaxis()->SetTitleSize(0.05);
   HWorld.GetXaxis()->SetTitleOffset(0.8);
   HWorld.GetYaxis()->SetTitleOffset(0.8);

   TCanvas C;

   HWorld.Draw("axis");
   GLine.Draw("f");

   GLine2.Draw("l");

   G0.Draw("l");
   G7.Draw("l");
   GN.Draw("l");

   TLegend Legend(0.17, 0.45, 0.4, 0.62);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(1);
   Legend.AddEntry(&G0, "(0.10, 0.0)", "l");
   Legend.AddEntry(&G7, "(0.50, 1.5)", "l");
   Legend.AddEntry(&GN, "(0.25, -1.0)", "l");
   Legend.Draw();

   HWorld.Draw("axis same");

   C.SaveAs("Meow.png");
   C.SaveAs("Meow.C");
   C.SaveAs("Meow.eps");
   C.SaveAs("Meow.pdf");

   return 0;
}




