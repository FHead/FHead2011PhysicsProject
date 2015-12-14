#include <string>
#include <vector>
using namespace std;

#include "TH1D.h"

TH1D Rebin(TH1D Input, vector<double> Bins, string NewName)
{
   double *bins = new double[Bins.size()];
   for(int i = 0; i < (int)Bins.size(); i++)
      bins[i] = Bins[i];

   TH1D NewHistogram(NewName.c_str(), TString(Input.GetTitle()) + " rebinned", Bins.size() - 1, bins);

   for(int i = 1; i <= NewHistogram.GetNbinsX(); i++)   // loop over each output bins
   {
      // for now, do it the stupid way.  500^2 is just 250000, not a big deal

      double NewLowEdge = NewHistogram.GetBinLowEdge(i);
      double NewHighEdge = NewLowEdge + NewHistogram.GetBinWidth(i);

      double Total = 0;
      for(int j = 1; j <= Input.GetNbinsX(); j++)
      {
         double LowEdge = Input.GetBinLowEdge(j);
         double HighEdge = LowEdge + Input.GetBinWidth(j);

         if(LowEdge > NewHighEdge)
            continue;
         if(HighEdge <= NewLowEdge)
            continue;

         double From = LowEdge;
         double To = HighEdge;

         if(LowEdge < NewLowEdge)
            From = NewLowEdge;
         if(HighEdge > NewHighEdge)
            To = NewHighEdge;

         Total = Total + (To - From) / (HighEdge - LowEdge) * Input.GetBinContent(j);
      }

      NewHistogram.SetBinContent(i, Total / NewHistogram.GetBinWidth(i));
   }

   delete[] bins;

   return NewHistogram;
}



