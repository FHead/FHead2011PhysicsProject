#include <iostream>
using namespace std;

#include "CalculateME.h"
#include "AngleConversion.h"

int main()
{
   EventParameters event;
   event.HMass = 125;
   event.ZMass = 90;
   event.Z2Mass = 12;
   event.Phi0 = 2;
   event.Theta0 = acos(0.3);
   event.Phi = -2.43;
   event.Theta1 = acos(-0.2);
   event.Theta2 = acos(-0.6);

   LeptonVectors leptons = ConvertAnglesToVectorsRoberto(event);

   cout << GetGeneralScalar2e2mu_Part10(leptons, 1, 1, 0, 0) << endl;
   cout << GetGeneralScalar2e2mu_Part10(leptons, 1, 0, 1, 0) << endl;
   cout << GetGeneralScalar2e2mu_Part10(leptons, 1, 0, 0, 1) << endl;
   cout << GetGeneralScalar2e2mu_Part10(leptons, 0, 1, 1, 0) << endl;
   cout << GetGeneralScalar2e2mu_Part10(leptons, 0, 1, 0, 1) << endl;
   cout << GetGeneralScalar2e2mu_Part10(leptons, 0, 0, 1, 1) << endl;
   
   cout << GetGeneralScalar2e2mu_Part11(leptons, 1, 1, 0, 0) << endl;
   cout << GetGeneralScalar2e2mu_Part11(leptons, 1, 0, 1, 0) << endl;
   cout << GetGeneralScalar2e2mu_Part11(leptons, 1, 0, 0, 1) << endl;
   cout << GetGeneralScalar2e2mu_Part11(leptons, 0, 1, 1, 0) << endl;
   cout << GetGeneralScalar2e2mu_Part11(leptons, 0, 1, 0, 1) << endl;
   cout << GetGeneralScalar2e2mu_Part11(leptons, 0, 0, 1, 1) << endl;

   cout << GetGeneralScalar2e2mu_Part12(leptons, 1, 1, 0, 0) << endl;
   cout << GetGeneralScalar2e2mu_Part12(leptons, 1, 0, 1, 0) << endl;
   cout << GetGeneralScalar2e2mu_Part12(leptons, 1, 0, 0, 1) << endl;
   cout << GetGeneralScalar2e2mu_Part12(leptons, 0, 1, 1, 0) << endl;
   cout << GetGeneralScalar2e2mu_Part12(leptons, 0, 1, 0, 1) << endl;
   cout << GetGeneralScalar2e2mu_Part12(leptons, 0, 0, 1, 1) << endl;

   return 0;
}








