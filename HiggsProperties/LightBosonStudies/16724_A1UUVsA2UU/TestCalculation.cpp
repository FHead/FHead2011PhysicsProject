#include <iostream>
using namespace std;

#include "AngleConversion.h"
#include "CalculateME.h"

#include "DrawRandom.h"

int main()
{
   EventParameters E;
   
   ZPrimeParameters ZP;
   ZP.VMass = 9.46;
   ZP.VWidth = 0.000054;
   ZP.G1VL = 0.073348;
   ZP.G1VR = 0.073348;
   ZP.G2VL = 0.073348;
   ZP.G2VR = 0.073348;

   for(int i = 0; i < 10000; i++)
   {
      E.HMass = 18.9201;
      E.ZMass = 9.46;
      E.Z2Mass = 9.46;
      E.Phi0 = DrawRandom(0, 2 * M_PI);
      E.Theta0 = acos(DrawRandom(-1, 1));
      E.Phi = DrawRandom(0, 2 * M_PI);
      E.Theta1 = acos(DrawRandom(-1, 1));
      E.Theta2 = acos(DrawRandom(-1, 1));
      E.PhiH = 0;
      E.PTH = 0;
      E.YH = 0;
      E.PhiOffset = 0;

      LeptonVectors L = ConvertAnglesToVectorsRoberto(E);

      cout << GetXVV_EEMM_A1VVR_A1VVR_15721(L, ZP) << " "
         << GetXVV_EEMM_A2VVR_A2VVR_15721(L, ZP) << " "
         << GetXVV_EEMM_A1VVR_A2VVR_15721(L, ZP) << " "
         << GetXVV_EEMM_A2VVR_A1VVR_15721(L, ZP) << " "
         << GetXVV_EEMM_A1VVR_A1VVR_15721(L, ZP) / GetXVV_EEMM_A2VVR_A2VVR_15721(L, ZP) << endl;
   }

   return 0;
}




