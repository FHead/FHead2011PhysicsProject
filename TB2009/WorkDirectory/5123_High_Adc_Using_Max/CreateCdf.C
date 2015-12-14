#include "TFile.h"
#include "TH1D.h"

#include <fstream>
#include <iomanip>
using namespace std;

void CreateCdf(char *rootfilename, int motherboard = 0, int channel = 0, char *outputfilename = "Cdf.txt", int startadc = 50)
{
   TFile inputFile(rootfilename);

   TString name = Form("MaxAdc_%d_%d", motherboard, channel);

   TH1D *histogram = (TH1D *)inputFile.Get(name);
   if(histogram == 0)
      return;

   ofstream out(outputfilename);

   int totalcount = (int)histogram->Integral();

   for(int adc = startadc + 10000; adc < 16000 + 10000; adc++)
   {
      int count = (int)histogram->Integral(1, adc);

      out << adc - 10000 << " " << setprecision(20) << ((double)count) / totalcount << endl;

      if(count == totalcount)
         break;
   }

   out.close();

   inputFile.Close();
}


