#include <iostream>
using namespace std;

#include "Code/DrawRandom.h"

double GetME(double y);

int main()
{
   int EntryCount = 1000000;
   for(int i = 0; i < EntryCount; i++)
   {
      // double x = DrawRandom(50, 150);
      double x = 100;
      double y = DrawRandom(-10, 20);

      double oldx = 100;
      double oldy = y / x * oldx;

      double ME = GetME(oldy);

      double Ratio = 100 / x;
      double W = ME * exp(-(x - 100) * (x - 100) / (2 * 10 * 10)) / 10
         * Ratio;

      cout << x << " " << y << " " << W << endl;
   }

   return 0;
}

double GetME(double y)
{
   double Result = 0;

   Result = Result + exp(-(y - 2) * (y - 2) / (2 * 2 * 2)) / 2 * 2;
   Result = Result + exp(-(y - 8) * (y - 8) / (2 * 2 * 2)) / 2 * 2;
   Result = Result + exp(-(y - 6.5) * (y - 6.5) / (2 * 0.2 * 0.2)) / 0.2;

   return Result;
}




