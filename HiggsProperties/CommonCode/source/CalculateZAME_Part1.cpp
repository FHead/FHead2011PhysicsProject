#include <cmath>
#include <iostream>
#include <complex>
using namespace std;

#include "CalculateZAME.h"
#include "AngleConversion.h"
#include "Constants.h"

double GetToy1ZAME(ZALeptonVectors &Leptons)
{
   ZAEventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

   double HWeight = 1;
   double ZWeight = exp(-(Event.ZMass - CONST_MZ) * (Event.ZMass - CONST_MZ) / (2 * 5 * 5)) * 0.9 + 0.1;
   double Phi0Weight = 1 + 0.2 * cos(Event.Phi0);
   double CosTheta0Weight = 1;
   double CosThetaLLWeight = 1 - cos(Event.ThetaLL) * cos(Event.ThetaLL) / 2;

   return HWeight * ZWeight * Phi0Weight * CosTheta0Weight * CosThetaLLWeight;
}





