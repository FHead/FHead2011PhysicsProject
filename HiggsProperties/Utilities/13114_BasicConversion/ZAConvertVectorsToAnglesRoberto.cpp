#include <iostream>
using namespace std;

#include "AngleConversion.h"

int main()
{
   while(cin)
   {
      ZALeptonVectors Leptons;

      cin >> Leptons.Lepton1[1] >> Leptons.Lepton1[2] >> Leptons.Lepton1[3];
      cin >> Leptons.Lepton2[1] >> Leptons.Lepton2[2] >> Leptons.Lepton2[3];
      cin >> Leptons.Photon[1] >> Leptons.Photon[2] >> Leptons.Photon[3];

      Leptons.Lepton1[0] = Leptons.Lepton1.GetP();
      Leptons.Lepton2[0] = Leptons.Lepton2.GetP();
      Leptons.Photon[0] = Leptons.Photon.GetP();

      ZAEventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      cout << Event.HMass << " " << Event.ZMass << " " << Event.Phi0 << " " << Event.Theta0
         << " " << Event.ThetaLL << " " << Event.YH << " " << Event.PTH << " " << Event.PhiH
         << " " << Event.PhiOffset << endl;
   }

   return 0;
}




