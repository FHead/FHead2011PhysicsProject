#include <iostream>
using namespace std;

#include "Code/TauHelperFunctions2.h"

#include "LeptonResponse.h"

int main()
{
   for(double PT = 5; PT <= 200; PT = PT + 1)
   {
      for(double Eta = -3; Eta <= 3; Eta = Eta + 0.1)
      {
         FourVector Lepton;
         Lepton.SetPtEtaPhi(PT, Eta, 0);

         double Sum = 0;

         for(double x = 0.25; x < 1.75; x = x + 0.0001)
            Sum = Sum + SmearElectron8TeVWide_Si12575(Lepton, x - 1);

         cout << PT << " " << Eta << " " << Sum << endl;
      }
   }
}








