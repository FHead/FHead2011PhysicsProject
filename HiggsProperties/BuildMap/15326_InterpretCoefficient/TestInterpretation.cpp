#include <cmath>
#include <iostream>
using namespace std;

#include "Constants.h"
#include "InterpretCoefficient.h"

int main()
{
   InterpretationCoefficients C;
   C.gww = -1;
   C.yt = 0;
   C.yta = 0;
   C.mt = 172.5;
   C.mw = CONST_MW;

   cout << InterpretedA2ZA_Roberto14167(C) << endl;

   return 0;
}





