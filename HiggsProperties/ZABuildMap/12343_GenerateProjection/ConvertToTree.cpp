#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"

#include "AngleConversion.h"
#include "CalculateME.h"

int main();

int main()
{
   TFile File("ResultTree.root", "RECREATE");

   double MH, MZ, Phi0, Theta0, ThetaLL;
   double L1PT, L1Eta, L1Phi, L2PT, L2Eta, L2Phi, PPT, PEta, PPhi;
   double HPT, HY, HPhi, PhiOffset;
   double Weight;

   TTree Tree("Tree", "Tree");

   Tree.Branch("MH", &MH, "MH/D");
   Tree.Branch("MZ", &MZ, "MZ/D");
   Tree.Branch("Phi0", &Phi0, "Phi0/D");
   Tree.Branch("Theta0", &Theta0, "Theta0/D");
   Tree.Branch("ThetaLL", &ThetaLL, "ThetaLL/D");
   Tree.Branch("L1PT", &L1PT, "L1PT/D");
   Tree.Branch("L1Eta", &L1Eta, "L1Eta/D");
   Tree.Branch("L1Phi", &L1Phi, "L1Phi/D");
   Tree.Branch("L2PT", &L2PT, "L2PT/D");
   Tree.Branch("L2Eta", &L2Eta, "L2Eta/D");
   Tree.Branch("L2Phi", &L2Phi, "L2Phi/D");
   Tree.Branch("PPT", &PPT, "PPT/D");
   Tree.Branch("PEta", &PEta, "PEta/D");
   Tree.Branch("PPhi", &PPhi, "PPhi/D");
   Tree.Branch("HPT", &HPT, "HPT/D");
   Tree.Branch("HY", &HY, "HY/D");
   Tree.Branch("HPhi", &HPhi, "HPhi/D");
   Tree.Branch("PhiOffset", &PhiOffset, "PhiOffset/D");
   Tree.Branch("Weight", &Weight, "Weight/D");

   while(cin)
   {
      char ch[10240] = "";
      cin.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream line(ch);

      MH = -10, MZ = -10, Phi0 = -10, Theta0 = -10, ThetaLL = -10;
      line >> MH >> MZ >> Phi0 >> Theta0 >> ThetaLL;
      if(MH < 0 || MZ < 0 || Phi0 < -5 || Theta0 < -5 || ThetaLL < -5)
         continue;

      PhiOffset = -99999;
      line >> PhiOffset;
      if(PhiOffset < -99998)
         continue;

      HPT = -10, HY = -99999, HPhi = -99999;
      line >> HY >> HPT >> HPhi;
      if(HPT < 0 || HY < -99998 || HPhi < -99998)
         continue;

      Weight = -99999;
      line >> Weight;
      if(Weight < -99998 || Weight != Weight)
         continue;

      ZAEventParameters Angles;
      Angles.HMass = MH;
      Angles.ZMass = MZ;
      Angles.Phi0 = Phi0;
      Angles.Theta0 = Theta0;
      Angles.ThetaLL = ThetaLL;
      Angles.PhiOffset = PhiOffset;
      Angles.PTH = HPT;
      Angles.YH = HY;
      Angles.PhiH = HPhi;

      ZALeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Angles);

      L1PT = Leptons.Lepton1.GetPT();
      L1Eta = Leptons.Lepton1.GetEta();
      L1Phi = Leptons.Lepton1.GetPhi();
      L2PT = Leptons.Lepton2.GetPT();
      L2Eta = Leptons.Lepton2.GetEta();
      L2Phi = Leptons.Lepton2.GetPhi();
      PPT = Leptons.Photon.GetPT();
      PEta = Leptons.Photon.GetEta();
      PPhi = Leptons.Photon.GetPhi();

      Tree.Fill();
   }

   Tree.Write();

   File.Close();

   return 0;
}



