#include <iostream>
#include <vector>
using namespace std;

#include "Code/DrawRandom.h"

int main()
{
   int D = 10;
   cerr << "D = ";
   cin >> D;

   vector<double> Theta(D);
   for(int i = 0; i < D; i++)
   {
      cerr << "Theta[" << i << "] = ";
      cin >> Theta[i];
   }

   int N = 1000;
   cerr << "N = ";
   cin >> N;

   for(int i = 0; i < N; i++)
   {
      vector<double> Sample(D);
      for(int j = 0; j < D; j++)
         Sample[j] = DrawRandom(-100, 100);

      double Test = 0;
      for(int j = 0; j < D; j++)
         Test = Test + Sample[j] * Theta[j];

      if(Test > 0)   Test = 1;
      if(Test < 0)   Test = -1;

      cout << Test;
      for(int j = 0; j < D; j++)
         cout << " " << Sample[j];
      cout << endl;
   }

   return 0;
}





