// this one do an average

#include "TH1D.h"
#include "TFile.h"

#include <iostream>
#include <fstream>

void GetPedestalMean2(char *inputrootfile, char *output)
{
   TFile adcfile(inputrootfile);
   // std::ofstream outputfile(output);

   for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < 16; iChannel++)
      {
         TH1D *histogram = (TH1D *)adcfile.Get(Form("Adc_%d_%d", iMotherBoard, iChannel));
         double histogram_mean = histogram->GetMean();

         histogram->Rebin(4);

         int maxbin = histogram->GetMaximumBin();
         double average = 0;
         double weight = 0;
         for(int i = -4; i <= 4; i++)
         {
            average = average + histogram->GetBinContent(maxbin + i) * histogram->GetBinCenter(maxbin + i);
            weight = weight + histogram->GetBinContent(maxbin + i);
         }

         cout << iMotherBoard << " " << iChannel << " " << average / weight << " " << histogram_mean
            << " " << average / weight - histogram_mean << std::endl;
      }
   }

   // outputfile.close();
   adcfile.Close();
}
