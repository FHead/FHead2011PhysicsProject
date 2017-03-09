#include <iostream>
#include <cmath>
using namespace std;

#include "Code/DrawRandom.h"
#include "ProgressBar.h"

int main();
double GiveMeZ();

int main()
{
   int EntryCount = 10000000;

   double S = 0, B = 0, N = 0;
   double Total = 0;

   double InvSqrt2 = 1 / sqrt(2 * 3.1415926535);

   ProgressBar Bar(cout, EntryCount);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(iE % (EntryCount / 200) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      double Z1 = 100, Z2 = 100;

      do
      {
         Z1 = GiveMeZ();
         Z2 = GiveMeZ();
      } while(Z1 + Z2 > 18.4);

      double SZ1 = 0.2 + 0.8 * exp(-(Z1 - 9.4) * (Z1 - 9.4) / (2 * 0.5 * 0.5));
      double SZ2 = 0.2 + 0.8 * exp(-(Z2 - 9.4) * (Z2 - 9.4) / (2 * 0.5 * 0.5));
      double BZ1 = 0.1 + 0.9 * exp(-(Z1 - 90) * (Z1 - 90) / (2 * 3 * 3));
      double BZ2 = 0.3 + 0.7 * exp(-(Z2 - 30) * (Z2 - 30) / (2 * 20 * 20));
      double NZ1 = 0.1 / 19.9 + 0.1 * InvSqrt2 / 0.001 * exp(-(Z1 - 9.4) * (Z1 - 9.4) / (2 * 0.001 * 0.001))
         + 0.8 * InvSqrt2 / 0.5 * exp(-(Z1 - 9.4) * (Z1 - 9.4) / (2 * 0.5 * 0.5));
      double NZ2 = 0.1 / 19.9 + 0.1 * InvSqrt2 / 0.001 * exp(-(Z2 - 9.4) * (Z2 - 9.4) / (2 * 0.001 * 0.001))
         + 0.8 * InvSqrt2 / 0.5 * exp(-(Z2 - 9.4) * (Z2 - 9.4) / (2 * 0.5 * 0.5));

      S = S + SZ1 * SZ2 / NZ1 / NZ2 * Z1 * Z2;
      B = B + BZ1 * BZ2 / NZ1 / NZ2 * Z1 * Z2;
      N = N + NZ1 * NZ2 / NZ1 / NZ2 * Z1 * Z2;
      Total = Total + 1 / NZ1 / NZ2 * Z1 * Z2;
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   cout << S / Total << " " << B / Total << " " << N / Total << endl;

   return 0;
}

double GiveMeZ()
{
   double Type = DrawRandom(0, 1);

   if(Type < 0.1)
      return DrawRandom(0.1, 20);
   else if(Type < 0.2)
      return DrawGaussian(9.4, 0.001);
   else
      return DrawGaussian(9.4, 0.5);

   return -1;
}







