#include "TH2Poly.h"
#include "TLatex.h"
#include "TCanvas.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main()
{
   SetStyle();

   TH2Poly Histogram;

   double B1X[] = {500, 600, 600, 500};
   double B2X[] = {600, 700, 700, 600};
   double B3X[] = {600, 700, 700, 600};
   double FS1X[] = {500, 600, 600, 500};
   double FS2X[] = {500, 600, 600, 500};
   double FS3X[] = {500, 600, 600, 500};
   double FS4X[] = {600, 700, 700, 600};
   double FS5X[] = {600, 700, 700, 600};
   double FS6X[] = {600, 700, 700, 600};
   double FS7X[] = {700, 1500, 1500, 700};
   double FS8X[] = {700, 1500, 1500, 700};
   double FS9X[] = {700, 1500, 1500, 700};
   double FS10X[] = {700, 1500, 1500, 700};
   double FS11X[] = {700, 1500, 1500, 700};

   double B1Y[] = {0.10, 0.10, 0.14, 0.14};
   double B2Y[] = {0.10, 0.10, 0.14, 0.14};
   double B3Y[] = {0.07, 0.07, 0.10, 0.10};
   double FS1Y[] = {0.30, 0.30, 0.50, 0.50};
   double FS2Y[] = {0.20, 0.20, 0.30, 0.30};
   double FS3Y[] = {0.14, 0.14, 0.20, 0.20};
   double FS4Y[] = {0.30, 0.30, 0.50, 0.50};
   double FS5Y[] = {0.20, 0.20, 0.30, 0.30};
   double FS6Y[] = {0.14, 0.14, 0.20, 0.20};
   double FS7Y[] = {0.30, 0.30, 0.50, 0.50};
   double FS8Y[] = {0.20, 0.20, 0.30, 0.30};
   double FS9Y[] = {0.14, 0.14, 0.20, 0.20};
   double FS10Y[] = {0.10, 0.10, 0.14, 0.14};
   double FS11Y[] = {0.07, 0.07, 0.10, 0.10};

   Histogram.AddBin(4, B1X, B1Y);
   Histogram.AddBin(4, B2X, B2Y);
   Histogram.AddBin(4, B3X, B3Y);
   Histogram.AddBin(4, FS1X, FS1Y);
   Histogram.AddBin(4, FS2X, FS2Y);
   Histogram.AddBin(4, FS3X, FS3Y);
   Histogram.AddBin(4, FS4X, FS4Y);
   Histogram.AddBin(4, FS5X, FS5Y);
   Histogram.AddBin(4, FS6X, FS6Y);
   Histogram.AddBin(4, FS7X, FS7Y);
   Histogram.AddBin(4, FS8X, FS8Y);
   Histogram.AddBin(4, FS9X, FS9Y);
   Histogram.AddBin(4, FS10X, FS10Y);
   Histogram.AddBin(4, FS11X, FS11Y);

   Histogram.SetBinContent(1, 1);
   Histogram.SetBinContent(2, 2);
   Histogram.SetBinContent(3, 3);
   Histogram.SetBinContent(4, 4);
   Histogram.SetBinContent(5, 5);
   Histogram.SetBinContent(6, 6);
   Histogram.SetBinContent(7, 7);
   Histogram.SetBinContent(8, 8);
   Histogram.SetBinContent(9, 9);
   Histogram.SetBinContent(10, 10);
   Histogram.SetBinContent(11, 11);
   Histogram.SetBinContent(12, 12);
   Histogram.SetBinContent(13, 13);
   Histogram.SetBinContent(14, 14);

   TCanvas Canvas("C", "C", 1024, 1024);

   Histogram.SetStats(0);
   Histogram.GetXaxis()->SetTitle("MR (new)");
   Histogram.GetYaxis()->SetTitle("R^{2} (new)");
   Histogram.SetTitle("Regions used to test data-MC agreement");
   Histogram.Draw("colz");

   TLatex text;
   text.SetTextFont(42);
   text.SetTextSize(0.03);
   text.SetTextAlign(22);   // center?

   text.DrawLatex(550, 0.12, "B1");
   text.DrawLatex(650, 0.12, "B2");
   text.DrawLatex(650, 0.085, "B3");
   text.DrawLatex(550, 0.40, "FS1");
   text.DrawLatex(550, 0.25, "FS2");
   text.DrawLatex(550, 0.17, "FS3");
   text.DrawLatex(650, 0.40, "FS4");
   text.DrawLatex(650, 0.25, "FS5");
   text.DrawLatex(650, 0.17, "FS6");
   text.DrawLatex(1100, 0.40, "FS7");
   text.DrawLatex(1100, 0.25, "FS8");
   text.DrawLatex(1100, 0.17, "FS9");
   text.DrawLatex(1100, 0.12, "FS10");
   text.DrawLatex(1100, 0.085, "FS11");

   Canvas.SaveAs("Regions.png");
   Canvas.SaveAs("Regions.C");
   Canvas.SaveAs("Regions.eps");
   Canvas.SaveAs("Regions.pdf");
   
   return 0;
}




