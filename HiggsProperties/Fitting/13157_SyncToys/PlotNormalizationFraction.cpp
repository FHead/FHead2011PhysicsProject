#include <iostream>
using namespace std;

#include "TH2D.h"

#include "PlotHelper2.h"
#include "DataHelper.h"

int main()
{
   DataHelper DHFile("Normalization.dh");

   TH2D HA2("HA2", "A2 yield fraction", 100, -10, 10, 100, -10, 10);
   TH2D HA3("HA3", "A3 yield fraction", 100, -10, 10, 100, -10, 10);

   for(int iX = 1; iX <= HA2.GetNbinsX(); iX++)
   {
      for(int iY = 1; iY <= HA2.GetNbinsY(); iY++)
      {
         double A1RA1R = DHFile["em"]["T1_001"].GetDouble();
         double A2RA2R = DHFile["em"]["T1_002"].GetDouble();
         double A2IA2I = DHFile["em"]["T1_003"].GetDouble();
         double A3RA3R = DHFile["em"]["T1_004"].GetDouble();
         double A3IA3I = DHFile["em"]["T1_005"].GetDouble();
         double A1RA2R = DHFile["em"]["T1_014"].GetDouble();
         double A1RA2I = DHFile["em"]["T1_015"].GetDouble();
         double A1RA3R = DHFile["em"]["T1_016"].GetDouble();
         double A1RA3I = DHFile["em"]["T1_017"].GetDouble();

         double X = HA2.GetXaxis()->GetBinCenter(iX);
         double Y = HA2.GetYaxis()->GetBinCenter(iY);

         double S2 = (1 + X * X / 3.276 / 3.276 + Y * Y / 3.276 / 3.276);
         double S3 = (1 + X * X / 5.042 / 5.042 + Y * Y / 5.042 / 5.042);

         HA2.SetBinContent(iX, iY, (A1RA1R + X * X * A2RA2R + Y * Y * A2IA2I + X * A1RA2R + Y * A1RA2I) / A1RA1R / S2);
         HA3.SetBinContent(iX, iY, (A1RA1R + X * X * A3RA3R + Y * Y * A3IA3I + X * A1RA3R + Y * A1RA3I) / A1RA1R / S3);
      }
   }

   HA2.SetStats(0);
   HA3.SetStats(0);

   PsFileHelper PsFile("NormalizationResult.ps");
   PsFile.AddTextPage("EDCBA");

   PsFile.AddPlot(HA2, "colz");
   PsFile.AddPlot(HA3, "colz");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}




