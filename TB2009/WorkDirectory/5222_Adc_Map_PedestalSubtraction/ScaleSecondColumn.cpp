#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char **argv)
{
   if(argc != 3)
   {
      cout << "usage: exe txtfile scaling" << endl;
      return -1;
   }

   stringstream str(argv[2]);
   double scaling = 1;
   str >> scaling;

   ifstream in(argv[1]);

   while(in)
   {
      double number1 = 0;
      double number2 = 0;

      in >> number1 >> number2;

      if(number2 < 1e-5 || number1 < 1e-5)
         continue;

      cout << number1 << " " << number2 * scaling << endl;
   }

   in.close();

   return 0;
}

