#include <cmath>
#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH3D.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main()
{
   SetStyle();

   int Bin = 100;
   TH3D HMexican("HMexican", "", Bin, -2.2, 2.2, Bin, -2.2, 2.2, Bin, 0, 9);
   HMexican.SetMarkerStyle(1);

   double a = 1;
   double b = -2;
   double c = 1;

   double phimin = -PI / 6 * 2.5;
   double phimax = PI * 10 / 6;

   double ymax = a * 2 * 2 * 2 * 2 + b * 2 * 2 + c;

   double delta = 0.1;

   for(int i = 1; i <= Bin; i++)
   {
      for(int j = 1; j <= Bin; j++)
      {
         double x = HMexican.GetXaxis()->GetBinCenter(i);
         double y = HMexican.GetYaxis()->GetBinCenter(j);

         double r = sqrt(x * x + y * y);

         double phi = acos(x / r);
         if(y < 0)
            phi = -phi;

         if(phi == phi && (phi > phimax || phi < phimin))
            continue;

         double f = a * r * r * r * r + b * r * r + c;

         for(int k = 1; k <= Bin; k++)
         {
            double z = HMexican.GetZaxis()->GetBinCenter(k);
            if(z >= f && z < f + delta + f * delta)
               HMexican.Fill(x, y, z);
         }
      }
   }

   HMexican.SetStats(0);

   TCanvas C("C", "C", 1024, 1024);

   HMexican.Draw("col");

   C.SaveAs("MexicanHatFlat.png");
   C.SaveAs("MexicanHatFlat.C");
   C.SaveAs("MexicanHatFlat.eps");
   C.SaveAs("MexicanHatFlat.pdf");

   HMexican.Draw("iso");

   C.SaveAs("MexicanHat.png");
   C.SaveAs("MexicanHat.C");
   C.SaveAs("MexicanHat.eps");
   C.SaveAs("MexicanHat.pdf");

   return 0;
}





