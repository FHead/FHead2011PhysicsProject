#include <iostream>
using namespace std;

#include "AngleConversion.h"
#include "MEFunctions.h"

int main(int argc, char *argv[])
{
   ExtendedAVVBasis A;
   ExtendedAVVBasis A2;

   A2.A1ZZ = 1;
   
   A.A1ZZ = 1;
   A.A2ZZ = 1.1;
   A.A3ZZ = 0.8;
   A.A4ZZ = 0;
   
   A.A1ZV = 1.96;
   A.A2ZV = 1.4;
   A.A3ZV = 0.9;
   A.A4ZV = 0;
   
   A.A1ZA = 0;
   A.A2ZA = 0.4;
   A.A3ZA = 0.65;
   A.A4ZA = 0;
   
   A.A1VV = 1.56;
   A.A2VV = 1.19;
   A.A3VV = 0.85;
   A.A4VV = 0;
   
   A.A1VA = 0;
   A.A2VA = 1.14;
   A.A3VA = 1.8;
   A.A4VA = 0;
   
   A.A1AA = 0;
   A.A2AA = 0.1;
   A.A3AA = 0.18;
   A.A4AA = 0;

   ZPrimeParameters P;

   P.VMass = 9.46;
   P.VWidth = 1;
   P.G1VL = 0.073348;
   P.G1VR = 0.073348;
   P.G2VL = 0.073348;
   P.G2VR = 0.073348;

   EventParameters Event;
   Event.HMass = 18.7;
   Event.ZMass = 9.40;
   Event.Z2Mass = 3.00;
   Event.Phi0 = 2;
   Event.Phi = 3;
   Event.Theta0 = 0.5;
   Event.Theta1 = 0.5;
   Event.Theta2 = 0.5;
   Event.PhiH = 2;
   Event.YH = 1;
   Event.PTH = 0.3;
   Event.PhiOffset = 3;

   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   cout << Leptons << endl;

   cout << CalculateARARWithZPrime15714(Leptons, A, P) << endl;

   cout << endl;

   cout << "Starting evaluating points from std in..." << endl;

   while(cin)
   {
      cin >> Leptons.Lepton11[0] >> Leptons.Lepton11[1] >> Leptons.Lepton11[2] >> Leptons.Lepton11[3];
      cin >> Leptons.Lepton12[0] >> Leptons.Lepton12[1] >> Leptons.Lepton12[2] >> Leptons.Lepton12[3];
      cin >> Leptons.Lepton21[0] >> Leptons.Lepton21[1] >> Leptons.Lepton21[2] >> Leptons.Lepton21[3];
      cin >> Leptons.Lepton22[0] >> Leptons.Lepton22[1] >> Leptons.Lepton22[2] >> Leptons.Lepton22[3];

      Leptons.Lepton11[0] = Leptons.Lepton11.GetP();
      Leptons.Lepton12[0] = Leptons.Lepton12.GetP();
      Leptons.Lepton21[0] = Leptons.Lepton21.GetP();
      Leptons.Lepton22[0] = Leptons.Lepton22.GetP();

      cout << Leptons << endl;

      cout << CalculateARARWithZPrime15714(Leptons, A2, P) << endl;
   }

   return 0;
}





