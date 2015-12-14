#include "TH1D.h"
#include "TFile.h"

#include <fstream>

void GetPedestalMean(char *inputrootfile, char *output)
{
   TFile adcfile(inputrootfile);
   std::ofstream outputfile(output);

   for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < 16; iChannel++)
      {
         TH1D *histogram = (TH1D *)adcfile.Get(Form("Adc_%d_%d", iMotherBoard, iChannel));

         outputfile << iMotherBoard << " " << iChannel << " " << histogram->GetMean() << std::endl;
      }
   }

   outputfile.close();
   adcfile.Close();
}
