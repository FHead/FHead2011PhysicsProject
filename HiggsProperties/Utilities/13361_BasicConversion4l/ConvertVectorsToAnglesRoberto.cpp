#include <iostream>
using namespace std;

#include "AngleConversion.h"

int main()
{
   while(cin)
   {
      LeptonVectors Leptons;

      int ID[4];
      double PT, Eta, Phi;

      cin >> ID[0] >> PT >> Eta >> Phi;
      Leptons.Lepton11.SetPtEtaPhi(PT, Eta, Phi);
      cin >> ID[1] >> PT >> Eta >> Phi;
      Leptons.Lepton12.SetPtEtaPhi(PT, Eta, Phi);
      cin >> ID[2] >> PT >> Eta >> Phi;
      Leptons.Lepton21.SetPtEtaPhi(PT, Eta, Phi);
      cin >> ID[3] >> PT >> Eta >> Phi;
      Leptons.Lepton22.SetPtEtaPhi(PT, Eta, Phi);

      Leptons.Lepton11[0] = Leptons.Lepton11.GetP();
      Leptons.Lepton12[0] = Leptons.Lepton12.GetP();
      Leptons.Lepton21[0] = Leptons.Lepton21.GetP();
      Leptons.Lepton22[0] = Leptons.Lepton22.GetP();

      if(ID[0] != -ID[1] && ID[0] == -ID[2])
      {
         swap(ID[1], ID[2]);
         swap(Leptons.Lepton12, Leptons.Lepton21);
      }
      else if(ID[0] != -ID[1] && ID[0] == -ID[3])
      {
         swap(ID[1], ID[3]);
         swap(Leptons.Lepton12, Leptons.Lepton22);
      }

      if(ID[0] < 0 && ID[1] > 0)
      {
         swap(ID[0], ID[1]);
         swap(Leptons.Lepton11, Leptons.Lepton12);
      }
      if(ID[2] < 0 && ID[3] > 0)
      {
         swap(ID[2], ID[3]);
         swap(Leptons.Lepton21, Leptons.Lepton22);
      }

      if(ID[0] != ID[2])
         Leptons = Leptons.ReorderLeptons2e2mu();
      else
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




