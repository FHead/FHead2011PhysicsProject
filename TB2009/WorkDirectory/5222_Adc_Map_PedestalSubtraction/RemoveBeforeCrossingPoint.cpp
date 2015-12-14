#include <iostream>
#include <fstream>
using namespace std;

#define MIN 3000
#define MAX 4000

int main(int argc, char **argv)
{
   if(argc != 2)
   {
      cerr << "Grrr!!!" << endl;
      return -1;
   }

   ifstream in(argv[1]);

   while(in)   // remove points before MIN
   {
      // hardcoded MIN - MAX

      double number1 = 0;
      double number2 = 0;

      in >> number1 >> number2;

      if(number1 < MIN)
         continue;
      else
         break;
   }

   while(in)   // remove points before crossing point
   {
      double number1 = 0;
      double number2 = 0;

      in >> number1 >> number2;

      if(number2 < number1)
         break;
   }

   while(in)   // output everything thereafter
   {
      double number1 = 0;
      double number2 = 0;

      in >> number1 >> number2;

      if(number1 > 1e-5 && number2 > 1e-5)
         cout << number1 << " " << number2 << endl;
   }

   in.close();

   return 0;
}
