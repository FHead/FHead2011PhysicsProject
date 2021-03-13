#include <iostream>
#include <vector>
using namespace std;

#include "CommandLine.h"
#include "Code/DrawRandom.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<double> Ranges = CL.GetDoubleVector("range", vector<double>({0, 1, 0, 1}));
   int Tries = CL.GetInt("n", 1000000);

   int N = Ranges.size() / 2;

   for(int i = 0; i < Tries; i++)
   {
      for(int j = 0; j < N; j++)
         cout << " " << DrawRandom(Ranges[j*2], Ranges[j*2+1]);
      cout << endl;
   }

   return 0;
}




