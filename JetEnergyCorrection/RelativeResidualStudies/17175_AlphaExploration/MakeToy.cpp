#include <iostream>
#include <cmath>
using namespace std;

#include "Code/TauHelperFunctions3.h"
#include "Code/DrawRandom.h"

int main()
{
   int NTries = 1000000;

   for(int iT = 0; iT < NTries; iT++)
   {
      FourVector PPhoton;
      PPhoton.SetPtEtaPhi(100, 0, 0);

      FourVector PJet;
      double Phi = DrawRandom(M_PI * 0.875, M_PI * 1.125);
      double Eta = 0;
      double PT = DrawGaussian(100, 20);
      PJet.SetPtEtaPhi(PT, Eta, Phi);

      FourVector PJet2 = -PPhoton - PJet;
      PJet2[0] = PJet2.GetP();

      PJet = PJet * DrawGaussian(0.95, 0.10);
      PJet2 = PJet2 * DrawGaussian(1.10, 0.10);

      FourVector ETMiss = -(PPhoton + PJet + PJet2);
      ETMiss[3] = 0;
      ETMiss[0] = ETMiss.GetP();

      double PTBalance = PJet.GetPT() / PPhoton.GetPT();
      double Alpha = PJet2.GetPT() / PPhoton.GetPT();
      double MPF = 1 + (ETMiss.SpatialDot(PPhoton)) / (PPhoton.GetPT() * PPhoton.GetPT());

      cout << PTBalance << " " << MPF << " " << Alpha << endl;
   }

   return 0;
}





