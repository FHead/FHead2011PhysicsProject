#include <iostream>
using namespace std;

#include "AngleConversion.h"
#include "MEFunctions.h"
#include "Constants.h"

int main(int argc, char *argv[])
{
   PrintConstants();

   ExtendedAVVBasis A1;
   ExtendedAVVBasis A2;
   ExtendedAVVBasis A3;

   A2.A1ZZ = 1;
   
   A3.A1VV = 1;
   
   A1.A1ZZ = 1;
   A1.A2ZZ = 1.1;
   A1.A3ZZ = 0.8;
   A1.A4ZZ = 0;
   
   A1.A1ZV = 1.96;
   A1.A2ZV = 1.4;
   A1.A3ZV = 0.9;
   A1.A4ZV = 0;
   
   A1.A1ZA = 0;
   A1.A2ZA = 0.4;
   A1.A3ZA = 0.65;
   A1.A4ZA = 0;
   
   A1.A1VV = 1.56;
   A1.A2VV = 1.19;
   A1.A3VV = 0.85;
   A1.A4VV = 0;
   
   A1.A1VA = 0;
   A1.A2VA = 1.14;
   A1.A3VA = 1.8;
   A1.A4VA = 0;
   
   A1.A1AA = 0;
   A1.A2AA = 0.1;
   A1.A3AA = 0.18;
   A1.A4AA = 0;

   ZPrimeParameters P;

   P.VMass = 9.46;
   P.VWidth = 1;
   P.G1VL = 0.073348;
   P.G1VR = 0.073348;
   P.G2VL = 0.073348;
   P.G2VR = 0.073348;

   ZPrimeParameters P2;
   
   P2.VMass = 9.46;
   P2.VWidth = 0.054;
   P2.G1VL = -0.073348;
   P2.G1VR = 0.073348;
   P2.G2VL = -0.073348;
   P2.G2VR = 0.073348;

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

   cout << CalculateSpin2XVV_EEMM_RR_15764(Leptons, A1, P) << endl;
   cout << CalculateSpin2XVV_EEEE_RR_15764(Leptons, A1, P) << endl;
   cout << CalculateSpin1XVV_EEMM_RR_15762(Leptons, A1, P) << endl;
   cout << CalculateSpin1XVV_EEEE_RR_15762(Leptons, A1, P) << endl;
   cout << CalculateXVV_EEMM_RR_15721(Leptons, A1, P) << endl;
   cout << CalculateXVV_EEEE_RR_15721(Leptons, A1, P) << endl;

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

      cout << ConvertVectorsToAnglesRoberto(Leptons) << endl;

      cout << "Test Point 1" << endl;
      cout << "2e2mu " << CalculateSpin2XVV_EEMM_RR_15764(Leptons, A1, P) << endl;
      cout << "4e " << CalculateSpin2XVV_EEEE_RR_15764(Leptons, A1, P) << endl;
      cout << "2e2mu " << CalculateSpin1XVV_EEMM_RR_15762(Leptons, A1, P) << endl;
      cout << "4e " << CalculateSpin1XVV_EEEE_RR_15762(Leptons, A1, P) << endl;
      cout << "2e2mu " << CalculateXVV_EEMM_RR_15721(Leptons, A1, P) << endl;
      cout << "4e " << CalculateXVV_EEEE_RR_15721(Leptons, A1, P) << endl;
      cout << "Test Point 2" << endl;
      cout << "2e2mu " << CalculateSpin2XVV_EEMM_RR_15764(Leptons, A2, P) << endl;
      cout << "4e " << CalculateSpin2XVV_EEEE_RR_15764(Leptons, A2, P) << endl;
      cout << "2e2mu " << CalculateSpin1XVV_EEMM_RR_15762(Leptons, A2, P) << endl;
      cout << "4e " << CalculateSpin1XVV_EEEE_RR_15762(Leptons, A2, P) << endl;
      cout << "2e2mu " << CalculateXVV_EEMM_RR_15721(Leptons, A2, P) << endl;
      cout << "4e " << CalculateXVV_EEEE_RR_15721(Leptons, A2, P) << endl;
      cout << "Test Point 3" << endl;
      cout << "2e2mu " << CalculateSpin2XVV_EEMM_RR_15764(Leptons, A3, P) << endl;
      cout << "4e " << CalculateSpin2XVV_EEEE_RR_15764(Leptons, A3, P) << endl;
      cout << "2e2mu " << CalculateSpin1XVV_EEMM_RR_15762(Leptons, A3, P) << endl;
      cout << "4e " << CalculateSpin1XVV_EEEE_RR_15762(Leptons, A3, P) << endl;
      cout << "2e2mu " << CalculateXVV_EEMM_RR_15721(Leptons, A3, P) << endl;
      cout << "4e " << CalculateXVV_EEEE_RR_15721(Leptons, A3, P) << endl;
      cout << "Test Point 4" << endl;
      cout << "2e2mu " << CalculateSpin2XVV_EEMM_RR_15764(Leptons, A3, P2) << endl;
      cout << "4e " << CalculateSpin2XVV_EEEE_RR_15764(Leptons, A3, P2) << endl;
      cout << "2e2mu " << CalculateSpin1XVV_EEMM_RR_15762(Leptons, A3, P2) << endl;
      cout << "4e " << CalculateSpin1XVV_EEEE_RR_15762(Leptons, A3, P2) << endl;
      cout << "2e2mu " << CalculateXVV_EEMM_RR_15721(Leptons, A3, P2) << endl;
      cout << "4e " << CalculateXVV_EEEE_RR_15721(Leptons, A3, P2) << endl;

      cout << endl;
      cout << endl;
   }

   return 0;
}





