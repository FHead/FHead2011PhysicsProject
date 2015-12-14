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

   PsFileHelper PsFile("CheckGaussian.ps");
   PsFile.AddTextPage("Enhance Gaussian distribution intuition");

   TH1D HLargeStatisticsCheck("HLargeStatisticsExponentialCheck",
      "Check draw gaussian function with large statistics", 90, -45, 45);
   for(int i = 0; i < 10000000; i++)
      HLargeStatisticsCheck.Fill(DrawGaussian(0, 10));

   PsFile.AddTextPage("Large statistics: validate method");

   PsFile.AddPlot(HLargeStatisticsCheck, "", true);

   PsFile.AddTextPage("Smaller statistics: look out for the tail and fake peak!");

   for(int i = 0; i < 1000; i++)
   {
      TH1D HSmallerStatisticsTry("HSmallerStatisticsTry",
         Form("Try with smaller statistics (Try %d)", i + 1), 180, -90, 90);
      for(int j = 0; j < 100000; j++)
         HSmallerStatisticsTry.Fill(DrawGaussian(0, 10));
      PsFile.AddPlot(HSmallerStatisticsTry, "", true);
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}



