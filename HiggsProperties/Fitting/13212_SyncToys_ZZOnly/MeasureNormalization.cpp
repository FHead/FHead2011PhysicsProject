#include <iostream>
#include <cmath>
using namespace std;

#include "Code/DrawRandom.h"

#include "M4lSpectrum.h"

int main()
{
   double ZX8TeV2e2mu = 0;
   double ZX8TeV2mu2e = 0;
   double ZX8TeV4e = 0;
   double ZX8TeV4mu = 0;
   double ggZZ8TeV2e2mu = 0;
   double ggZZ8TeV2mu2e = 0;
   double ggZZ8TeV4e = 0;
   double ggZZ8TeV4mu = 0;
   double ZX7TeV2e2mu = 0;
   double ZX7TeV2mu2e = 0;
   double ZX7TeV4e = 0;
   double ZX7TeV4mu = 0;
   double ggZZ7TeV2e2mu = 0;
   double ggZZ7TeV2mu2e = 0;
   double ggZZ7TeV4e = 0;
   double ggZZ7TeV4mu = 0;

   int EntryCount = 1000000;
   for(int i = 0; i < EntryCount; i++)
   {
      double s = DrawRandom(115 * 115, 135 * 135);

      ZX8TeV2e2mu   += GetZX8TeV2e2muSpectrum(s);
      ZX8TeV2mu2e   += GetZX8TeV2mu2eSpectrum(s);
      ZX8TeV4e      += GetZX8TeV4eSpectrum(s);
      ZX8TeV4mu     += GetZX8TeV4muSpectrum(s);
      ggZZ8TeV2e2mu += GetggZZ8TeV2e2muSpectrum(s);
      ggZZ8TeV2mu2e += GetggZZ8TeV2mu2eSpectrum(s);
      ggZZ8TeV4e    += GetggZZ8TeV4eSpectrum(s);
      ggZZ8TeV4mu   += GetggZZ8TeV4muSpectrum(s);
      ZX7TeV2e2mu   += GetZX7TeV2e2muSpectrum(s);
      ZX7TeV2mu2e   += GetZX7TeV2mu2eSpectrum(s);
      ZX7TeV4e      += GetZX7TeV4eSpectrum(s);
      ZX7TeV4mu     += GetZX7TeV4muSpectrum(s);
      ggZZ7TeV2e2mu += GetggZZ7TeV2e2muSpectrum(s);
      ggZZ7TeV2mu2e += GetggZZ7TeV2mu2eSpectrum(s);
      ggZZ7TeV4e    += GetggZZ7TeV4eSpectrum(s);
      ggZZ7TeV4mu   += GetggZZ7TeV4muSpectrum(s);

      if(i == 0)
      {
         cout << ZX8TeV2e2mu << endl;
      }
   }

   cout << "ZX8TeV2e2mu   " << ZX8TeV2e2mu / EntryCount << endl;
   cout << "ZX8TeV2mu2e   " << ZX8TeV2mu2e / EntryCount << endl;
   cout << "ZX8TeV4e      " << ZX8TeV4e / EntryCount << endl;
   cout << "ZX8TeV4mu     " << ZX8TeV4mu / EntryCount << endl;
   cout << "ggZZ8TeV2e2mu " << ggZZ8TeV2e2mu / EntryCount << endl;
   cout << "ggZZ8TeV2mu2e " << ggZZ8TeV2mu2e / EntryCount << endl;
   cout << "ggZZ8TeV4e    " << ggZZ8TeV4e / EntryCount << endl;
   cout << "ggZZ8TeV4mu   " << ggZZ8TeV4mu / EntryCount << endl;
   cout << "ZX7TeV2e2mu   " << ZX7TeV2e2mu / EntryCount << endl;
   cout << "ZX7TeV2mu2e   " << ZX7TeV2mu2e / EntryCount << endl;
   cout << "ZX7TeV4e      " << ZX7TeV4e / EntryCount << endl;
   cout << "ZX7TeV4mu     " << ZX7TeV4mu / EntryCount << endl;
   cout << "ggZZ7TeV2e2mu " << ggZZ7TeV2e2mu / EntryCount << endl;
   cout << "ggZZ7TeV2mu2e " << ggZZ7TeV2mu2e / EntryCount << endl;
   cout << "ggZZ7TeV4e    " << ggZZ7TeV4e / EntryCount << endl;
   cout << "ggZZ7TeV4mu   " << ggZZ7TeV4mu / EntryCount << endl;

   return 0;
}





