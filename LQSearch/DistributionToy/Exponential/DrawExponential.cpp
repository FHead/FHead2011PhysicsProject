#include <vector>
#include <string>
using namespace std;

#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TH1D.h"

#include "DrawRandom.h"
#include "PlotHelper2.h"

int main(int argc, char *argv[])
{
   srand(time(NULL));

   gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   PsFileHelper PsFile("CheckExponential.ps");
   PsFile.AddTextPage("Enhance exponential distribution intuition");

   vector<string> Explanation;
   Explanation.push_back("Goal is to get used to Poissonian fluctuations near the tail");
   Explanation.push_back("      of exponential distributions, as it is important to gain intuition");
   Explanation.push_back("      on the appearance of the tail.  Otherwise it's easy to get too excited");
   Explanation.push_back("      over flucuations in data....");
   Explanation.push_back("");
   Explanation.push_back("Part 1 (first two plots): validation of the two methods");
   Explanation.push_back("   Method 1 - no brainer, slow, but guaranteed to be correct");
   Explanation.push_back("   Method 2 - better, faster, but need validation");
   Explanation.push_back("Part 2 (1000 plots): smaller statistics, look for fake peak and tails");
   PsFile.AddTextPage(Explanation);

   TH1D HLargeStatisticsExponentialCheck1("HLargeStatisticsExponentialCheck1",
      "Check draw exponential function with large statistics (method 1)", 100, 0, 100);
   TH1D HLargeStatisticsExponentialCheck2("HLargeStatisticsExponentialCheck2",
      "Check draw exponential function with large statistics (method 2)", 100, 0, 100);
   for(int i = 0; i < 10000000; i++)
   {
      HLargeStatisticsExponentialCheck1.Fill(DrawExponential(-0.1, 0, 150));
      HLargeStatisticsExponentialCheck2.Fill(DrawExponential(-0.1, 0));
   }

   PsFile.AddTextPage("Large statistics: validate method");

   PsFile.AddPlot(HLargeStatisticsExponentialCheck1, "", true);
   PsFile.AddPlot(HLargeStatisticsExponentialCheck2, "", true);

   PsFile.AddTextPage("Smaller statistics: look out for the tail and fake peak!");

   for(int i = 0; i < 1000; i++)
   {
      TH1D HSmallerStatistics("HSmallerStatistics",
         Form("Try with smaller statistics (Plot %d)", i + 1), 150, 0, 150);
      for(int j = 0; j < 10000; j++)
         HSmallerStatistics.Fill(DrawExponential(-0.1, 0));
      PsFile.AddPlot(HSmallerStatistics, "", true);
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}



