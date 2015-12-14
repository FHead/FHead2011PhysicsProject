#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

#define MIN 3000
#define MAX 4000

int main(int argc, char **argv)
{
   if(argc != 2)
   {
      cerr << "usage: exe AdcMappingFile (from preamp off to preamp on)" << endl;
      return -1;
   }

   ifstream in(argv[1]);

   double ratio_sum = 0;
   double count = 0;

   while(in)
   {
      double number1 = 0;
      double number2 = 0;

      in >> number1 >> number2;

      if(number1 < 1e-5 || number2 < 1e-5)
         continue;

      if(number1 < MAX && number1 > MIN)
      {
         ratio_sum = ratio_sum + number1 / number2;
         count = count + 1.0;
      }
   }

   cout << "FitScale: The scaling factor is " << setprecision(10) << ratio_sum / count << endl;

   in.close();

   return 0;
}

