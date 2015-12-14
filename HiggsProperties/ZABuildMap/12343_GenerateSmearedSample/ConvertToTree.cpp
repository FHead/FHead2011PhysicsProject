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
LeptonVectors ReorderLeptons(LeptonVectors Leptons);
bool PassBaselineCut(EventParameters Event);

int main()
{
   TFile File("ResultTree.root", "RECREATE");

   double MH, M1, Phi0, Theta0, ThetaLL, CosTheta0, CosThetaLL;
   double L1PT, L1Eta, L1Phi, L2PT, L2Eta, L2Phi, PPT, PEta, PPhi;
   int L1ID, L2ID;
   double HPT = 0, HY = 0, HPhi = 0, PhiOffset = 0;

   TTree Tree("Tree", "Tree");

   Tree.Branch("MH", &MH, "MH/D");
   Tree.Branch("M1", &M1, "M1/D");
   Tree.Branch("Phi0", &Phi0, "Phi0/D");
   Tree.Branch("Theta0", &Theta0, "Theta0/D");
   Tree.Branch("ThetaLL", &ThetaLL, "ThetaLL/D");
   Tree.Branch("zzmass", &MH, "zzmass/D");
   Tree.Branch("z1mass", &M1, "z1mass/D");
   Tree.Branch("phistar", &Phi0, "phistar/D");
   Tree.Branch("costhetastar", &CosTheta0, "costhetastar/D");
   Tree.Branch("costhetall", &CosThetaLL, "costhetall/D");
   Tree.Branch("L1PT", &L1PT, "L1PT/D");
   Tree.Branch("L1Eta", &L1Eta, "L1Eta/D");
   Tree.Branch("L1Phi", &L1Phi, "L1Phi/D");
   Tree.Branch("L1ID", &L1ID, "L1ID/I");
   Tree.Branch("L2PT", &L2PT, "L2PT/D");
   Tree.Branch("L2Eta", &L2Eta, "L2Eta/D");
   Tree.Branch("L2Phi", &L2Phi, "L2Phi/D");
   Tree.Branch("L2ID", &L2ID, "L2ID/I");
   Tree.Branch("PPT", &PPT, "PPT/D");
   Tree.Branch("PEta", &PEta, "PEta/D");
   Tree.Branch("PPhi", &PPhi, "PPhi/D");
   Tree.Branch("l1pt", &L1PT, "l1pt/D");
   Tree.Branch("l1eta", &L1Eta, "l1eta/D");
   Tree.Branch("l1phi", &L1Phi, "l1phi/D");
   Tree.Branch("l1id", &L1ID, "l1id/I");
   Tree.Branch("l2pt", &L2PT, "l2pt/D");
   Tree.Branch("l2eta", &L2Eta, "l2eta/D");
   Tree.Branch("l2phi", &L2Phi, "l2phi/D");
   Tree.Branch("l2id", &L2ID, "l2id/I");
   Tree.Branch("ppt", &PPT, "ppt/D");
   Tree.Branch("peta", &PEta, "peta/D");
   Tree.Branch("pphi", &PPhi, "pphi/D");
   Tree.Branch("HPT", &HPT, "HPT/D");
   Tree.Branch("HY", &HY, "HY/D");
   Tree.Branch("HPhi", &HPhi, "HPhi/D");
   Tree.Branch("PhiOffset", &PhiOffset, "PhiOffset/D");

   L1ID = 13;
   L2ID = -13;

   while(cin)
   {
      char ch[10240] = "";
      cin.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream line(ch);

      MH = -10, M1 = -10, Phi0 = -10, Theta0 = -10, ThetaLL = -10;
      line >> MH >> M1 >> Phi0 >> Theta0 >> ThetaLL;
      if(MH < 0 || M1 < 0 || Phi0 < -5 || Theta0 < -5 || ThetaLL < -5)
         continue;

      PhiOffset = -99999;
      line >> PhiOffset;
      if(PhiOffset < -99998)
         continue;

      HPT = -10, HY = -99999, HPhi = -99999;
      line >> HPhi >> HPT >> HY;
      if(HPT < 0 || HY < -99998 || HPhi < -99998)
         continue;

      ZAEventParameters Angles;
      Angles.HMass = MH;
      Angles.ZMass = M1;
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

      CosTheta0 = cos(Theta0);
      CosThetaLL = cos(ThetaLL);

      Tree.Fill();
   }

   Tree.Write();

   File.Close();

   return 0;
}



