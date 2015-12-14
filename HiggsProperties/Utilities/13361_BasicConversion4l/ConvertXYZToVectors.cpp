#include <iostream>
using namespace std;

#include "AngleConversion.h"

int main()
{
   while(cin)
   {
      int ID;
      FourVector X;

      cin >> ID >> X[1] >> X[2] >> X[3];

      X[0] = X.GetP();

      cout << ID << " " << X.GetPT() << " " << X.GetEta() << " " << X.GetPhi() << endl;
   }

   return 0;
}




