#include <iostream>
using namespace std;

#include "AngleConversion.h"

int main()
{
   while(cin)
   {
      LeptonVectors Leptons;

      cin >> Leptons.Lepton11[1] >> Leptons.Lepton11[2] >> Leptons.Lepton11[3];
      cin >> Leptons.Lepton12[1] >> Leptons.Lepton12[2] >> Leptons.Lepton12[3];
      cin >> Leptons.Lepton21[1] >> Leptons.Lepton21[2] >> Leptons.Lepton21[3];
      cin >> Leptons.Lepton22[1] >> Leptons.Lepton22[2] >> Leptons.Lepton22[3];

      Leptons.Lepton11[0] = Leptons.Lepton11.GetP();
      Leptons.Lepton12[0] = Leptons.Lepton12.GetP();
      Leptons.Lepton21[0] = Leptons.Lepton21.GetP();
      Leptons.Lepton22[0] = Leptons.Lepton22.GetP();

      Leptons = Leptons.ReorderLeptons4e();

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      cout << Event.HMass << " " << Event.ZMass << " " << Event.Z2Mass
         << " " << Event.Phi0 << " " << Event.Theta0
         << " " << Event.Phi << " " << Event.Theta1 << " " << Event.Theta2
         << " " << Event.YH << " " << Event.PTH << " " << Event.PhiH
         << " " << Event.PhiOffset << endl;
   }

   return 0;
}




