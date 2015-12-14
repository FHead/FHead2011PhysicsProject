#include <iostream>
using namespace std;

#include "Code/TauHelperFunctions2.h"

int main()
{
   FourVector A1(0, 1, 0.8, 0);
   FourVector A2(0, 1.2, 0.7, 0);
   FourVector A3(0, 1.1, 0.65, 0);

   cout << GetDPhi(A1, A2) << endl;
   cout << GetDPhi(A1, A3) << endl;

   cout << A1.GetP() / sqrt(A1.GetP2() + A2.GetP2() + A3.GetP2()) << endl;
   cout << A2.GetP() / sqrt(A1.GetP2() + A2.GetP2() + A3.GetP2()) << endl;
   cout << A3.GetP() / sqrt(A1.GetP2() + A2.GetP2() + A3.GetP2()) << endl;

   return 0;
}







