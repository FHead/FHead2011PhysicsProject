#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"

int main()
{
   vector<double> PulseShape;

   ifstream in("HcalPulseShape.txt");

   while(in)
   {
      double Temp = -9999;
      in >> Temp;
      if(Temp > -9998)
         PulseShape.push_back(Temp);
   }

   in.close();

   int BinSize = min(180, (int)PulseShape.size());
   TH1D HPulse("HPulse", ";Time (ns);a.u.", BinSize, 0, BinSize);

   for(int i = 0; i < BinSize; i++)
      HPulse.SetBinContent(i + 1, PulseShape[i]);

   TCanvas C("C", "C", 1024, 1024);

   HPulse.SetStats(0);
   HPulse.GetXaxis()->SetTitleOffset(1.1);
   HPulse.GetYaxis()->SetTitleOffset(1.2);
   HPulse.SetLineWidth(2);

   HPulse.Draw("c");

   C.SaveAs("HcalNoise-FitBasedFilter-IdealPulse.png");
   C.SaveAs("HcalNoise-FitBasedFilter-IdealPulse.C");
   C.SaveAs("HcalNoise-FitBasedFilter-IdealPulse.eps");
   C.SaveAs("HcalNoise-FitBasedFilter-IdealPulse.pdf");

   return 0;
}





