#include <iostream>
using namespace std;

#include "Code/DrawRandom.h"

int main();
double GiveMeSample();

int main()
{
   for(int i = 0; i < 10000000; i++)
   {
      double x = 100;
      double y = GiveMeSample();

      // double newx = DrawGaussian(100, 10);
      double newx = 100;
      double newy = y / x * newx;

      cout << newx << " " << newy << endl;
   }

   return 0;
}

double GiveMeSample()
{
   double Sample = 0;

   if(DrawRandom(0, 5) < 2)
      Sample = DrawGaussian(2, 2);
   else if(DrawRandom(0, 3) < 2)
      Sample = DrawGaussian(8, 2);
   else
      Sample = DrawGaussian(6.5, 0.2);

   return Sample;
}



