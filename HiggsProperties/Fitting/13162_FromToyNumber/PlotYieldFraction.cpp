#include <iostream>
using namespace std;

#include "PlotHelper2.h"
#include "DataHelper.h"

#include "TH1D.h"
#include "TH2D.h"

#include "YieldFraction.h"

int main()
{
   PsFileHelper PsFile("Result.ps");
   PsFile.AddTextPage("ABCDE");

   for(int energy = 0; energy < 2; energy++)
   {
      for(int finalstate = 0; finalstate < 4; finalstate++)
      {
         TH2D HA2("HA2", "A2 yield fraction", 100, -10, 10, 100, -10, 10);
         TH2D HA3("HA3", "A3 yield fraction", 100, -10, 10, 100, -10, 10);
         TH2D HA2Norm("HA2Norm", "A2 yield fraction from normalization", 100, -10, 10, 100, -10, 10);
         TH2D HA3Norm("HA3Norm", "A3 yield fraction from normalization", 100, -10, 10, 100, -10, 10);
         TH1D H1DA3("H1DA3", "1D A3 yield fraction", 100, -10, 10);
         TH1D H1DA3Norm("H1DA3Norm", "1D A3 yield fraction from normalization", 100, -10, 10);

         for(int iX = 1; iX <= HA2.GetNbinsX(); iX++)
         {
            for(int iY = 1; iY <= HA2.GetNbinsY(); iY++)
            {
               double X = HA2.GetXaxis()->GetBinCenter(iX);
               double Y = HA2.GetYaxis()->GetBinCenter(iY);
   
               HA2.SetBinContent(iX, iY, GetYieldFractionA1ZZA2ZZ(1, X, Y, energy, finalstate));
               HA3.SetBinContent(iX, iY, GetYieldFractionA1ZZA3ZZ(1, X, Y, energy, finalstate));
               HA2Norm.SetBinContent(iX, iY, GetNormalizationYieldFraction(1, X, Y, 0, 0, energy, finalstate));
               HA3Norm.SetBinContent(iX, iY, GetNormalizationYieldFraction(1, 0, 0, X, Y, energy, finalstate));
            }

            break;
         }
         
         for(int iX = 1; iX <= H1DA3.GetNbinsX(); iX++)
         {
            double X = H1DA3.GetBinCenter(iX);
            H1DA3.SetBinContent(iX, GetYieldFractionA1ZZA3ZZ(1, X, 0, energy, finalstate));
            H1DA3Norm.SetBinContent(iX, GetNormalizationYieldFraction(1, 0, 0, X, 0, energy, finalstate));

            cout << iX << " " << X << GetNormalizationYieldFraction(1, 0, 0, X, 0, energy, finalstate) << endl;
         }

         HA2.SetStats(0);
         HA3.SetStats(0);
         HA2Norm.SetStats(0);
         HA3Norm.SetStats(0);
         H1DA3.SetStats(0);
         H1DA3Norm.SetStats(0);

         PsFile.AddTextPage(Form("%d %d", energy, finalstate));
         PsFile.AddPlot(HA2, "colz");
         PsFile.AddPlot(HA2Norm, "colz");
         PsFile.AddPlot(HA3, "colz");
         PsFile.AddPlot(HA3Norm, "colz");
         PsFile.AddPlot(H1DA3, "");
         PsFile.AddPlot(H1DA3Norm, "");
      }
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}




