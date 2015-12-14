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

   double MH, M1, M2, M123, M124, M134, M234, Phi0, Theta0, Phi, Theta1, Theta2, CosTheta0, CosTheta1, CosTheta2;
   double L1PT, L1Eta, L1Phi, L2PT, L2Eta, L2Phi, L3PT, L3Eta, L3Phi, L4PT, L4Eta, L4Phi;
   int L1ID, L2ID, L3ID, L4ID;
   double HPT = 0, HY = 0, HPhi = 0, PhiOffset = 0;
   double Weight[92][4] = {{0}}, Weight2[92][4] = {{0}};
   bool PassBaseline2e2mu;

   TTree Tree("Tree", "Tree");

   Tree.Branch("MH", &MH, "MH/D");
   Tree.Branch("M1", &M1, "M1/D");
   Tree.Branch("M2", &M2, "M2/D");
   Tree.Branch("M123", &M123, "M123/D");
   Tree.Branch("M124", &M124, "M124/D");
   Tree.Branch("M134", &M134, "M134/D");
   Tree.Branch("M234", &M234, "M234/D");
   Tree.Branch("Phi0", &Phi0, "Phi0/D");
   Tree.Branch("Theta0", &Theta0, "Theta0/D");
   Tree.Branch("Phi", &Phi, "Phi/D");
   Tree.Branch("Theta1", &Theta1, "Theta1/D");
   Tree.Branch("Theta2", &Theta2, "Theta2/D");
   Tree.Branch("zzmass", &MH, "zzmass/D");
   Tree.Branch("z1mass", &M1, "z1mass/D");
   Tree.Branch("z2mass", &M2, "z2mass/D");
   Tree.Branch("phistar", &Phi0, "phistar/D");
   Tree.Branch("costhetastar", &CosTheta0, "costhetastar/D");
   Tree.Branch("phi", &Phi, "phi/D");
   Tree.Branch("costheta1", &CosTheta1, "costheta1/D");
   Tree.Branch("costheta2", &CosTheta2, "costheta2/D");
   Tree.Branch("L1PT", &L1PT, "L1PT/D");
   Tree.Branch("L1Eta", &L1Eta, "L1Eta/D");
   Tree.Branch("L1Phi", &L1Phi, "L1Phi/D");
   Tree.Branch("L1ID", &L1ID, "L1ID/I");
   Tree.Branch("L2PT", &L2PT, "L2PT/D");
   Tree.Branch("L2Eta", &L2Eta, "L2Eta/D");
   Tree.Branch("L2Phi", &L2Phi, "L2Phi/D");
   Tree.Branch("L2ID", &L2ID, "L2ID/I");
   Tree.Branch("L3PT", &L3PT, "L3PT/D");
   Tree.Branch("L3Eta", &L3Eta, "L3Eta/D");
   Tree.Branch("L3Phi", &L3Phi, "L3Phi/D");
   Tree.Branch("L3ID", &L3ID, "L3ID/I");
   Tree.Branch("L4PT", &L4PT, "L4PT/D");
   Tree.Branch("L4Eta", &L4Eta, "L4Eta/D");
   Tree.Branch("L4Phi", &L4Phi, "L4Phi/D");
   Tree.Branch("L4ID", &L4ID, "L4ID/I");
   Tree.Branch("l1pt", &L1PT, "l1pt/D");
   Tree.Branch("l1eta", &L1Eta, "l1eta/D");
   Tree.Branch("l1phi", &L1Phi, "l1phi/D");
   Tree.Branch("l1id", &L1ID, "l1id/I");
   Tree.Branch("l2pt", &L2PT, "l2pt/D");
   Tree.Branch("l2eta", &L2Eta, "l2eta/D");
   Tree.Branch("l2phi", &L2Phi, "l2phi/D");
   Tree.Branch("l2id", &L2ID, "l2id/I");
   Tree.Branch("l3pt", &L3PT, "l3pt/D");
   Tree.Branch("l3eta", &L3Eta, "l3eta/D");
   Tree.Branch("l3phi", &L3Phi, "l3phi/D");
   Tree.Branch("l3id", &L3ID, "l3id/I");
   Tree.Branch("l4pt", &L4PT, "l4pt/D");
   Tree.Branch("l4eta", &L4Eta, "l4eta/D");
   Tree.Branch("l4phi", &L4Phi, "l4phi/D");
   Tree.Branch("l4id", &L4ID, "l4id/I");
   Tree.Branch("HPT", &HPT, "HPT/D");
   Tree.Branch("HY", &HY, "HY/D");
   Tree.Branch("HPhi", &HPhi, "HPhi/D");
   Tree.Branch("PhiOffset", &PhiOffset, "PhiOffset/D");
   // Tree.Branch("Weight", Weight, "Weight[92][4]/D");
   Tree.Branch("PassBaseline2e2mu", &PassBaseline2e2mu, "PassBaseline2e2mu/O");

   L1ID = 11;
   L2ID = -11;
   L3ID = 13;
   L4ID = -13;

   while(cin)
   {
      char ch[10240] = "";
      cin.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream line(ch);

      MH = -10, M1 = -10, M2 = -10, Phi0 = -10, Theta0 = -10, Phi = -10, Theta1 = -10, Theta2 = -10;
      line >> MH >> M1 >> M2 >> Phi0 >> Theta0 >> Phi >> Theta1 >> Theta2;
      if(MH < 0 || M1 < 0 || M2 < 0 || Phi0 < -5 || Theta0 < -5 || Phi < -5 || Theta1 < -5 || Theta2 < -5)
         continue;

      PhiOffset = -99999;
      line >> PhiOffset;
      if(PhiOffset < -99998)
         continue;

      HPT = -10, HY = -99999, HPhi = -99999;
      line >> HPhi >> HPT >> HY;
      if(HPT < 0 || HY < -99998 || HPhi < -99998)
         continue;

      EventParameters Angles;
      Angles.HMass = MH;
      Angles.ZMass = M1;
      Angles.Z2Mass = M2;
      Angles.Phi0 = Phi0;
      Angles.Theta0 = Theta0;
      Angles.Phi = Phi;
      Angles.Theta1 = Theta1;
      Angles.Theta2 = Theta2;
      Angles.PhiOffset = PhiOffset;
      Angles.PTH = HPT;
      Angles.YH = HY;
      Angles.PhiH = HPhi;

      LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Angles);

      if(M1 < M2)
      {
         swap(Leptons.Lepton11, Leptons.Lepton21);
         swap(Leptons.Lepton12, Leptons.Lepton22);

         Angles = ConvertVectorsToAnglesRoberto(Leptons);
         MH = Angles.HMass;
         M1 = Angles.ZMass;
         M2 = Angles.Z2Mass;
         Phi0 = Angles.Phi0;
         Theta0 = Angles.Theta0;
         Phi = Angles.Phi;
         Theta1 = Angles.Theta1;
         Theta2 = Angles.Theta2;
         PhiOffset = Angles.PhiOffset;
         HPT = Angles.PTH;
         HY = Angles.YH;
         HPhi = Angles.PhiH;

         if(M1 < 1)
         {
            cout << "!" << endl;
            cout << Leptons << endl;
         }
      }

      M123 = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21).GetMass();
      M124 = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton22).GetMass();
      M134 = (Leptons.Lepton11 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();
      M234 = (Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();

      L1PT = Leptons.Lepton11.GetPT();
      L1Eta = Leptons.Lepton11.GetEta();
      L1Phi = Leptons.Lepton11.GetPhi();
      L2PT = Leptons.Lepton12.GetPT();
      L2Eta = Leptons.Lepton12.GetEta();
      L2Phi = Leptons.Lepton12.GetPhi();
      L3PT = Leptons.Lepton21.GetPT();
      L3Eta = Leptons.Lepton21.GetEta();
      L3Phi = Leptons.Lepton21.GetPhi();
      L4PT = Leptons.Lepton22.GetPT();
      L4Eta = Leptons.Lepton22.GetEta();
      L4Phi = Leptons.Lepton22.GetPhi();

      PassBaseline2e2mu = PassBaselineCut(Angles);
      
      CosTheta0 = cos(Theta0);
      CosTheta1 = cos(Theta1);
      CosTheta2 = cos(Theta2);

      Tree.Fill();
   }

   Tree.Write();

   File.Close();

   return 0;
}

LeptonVectors ReorderLeptons(LeptonVectors Leptons)
{
   double M12 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M14 = (Leptons.Lepton11 + Leptons.Lepton22).GetMass();
   double M32 = (Leptons.Lepton21 + Leptons.Lepton12).GetMass();
   double M34 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   double D12 = fabs(M12 - 91.186);
   double D14 = fabs(M14 - 91.186);
   double D32 = fabs(M32 - 91.186);
   double D34 = fabs(M34 - 91.186);

   if(D12 <= D14 && D12 <= D32 && D12 <= D34)
   {
      // Do nothing...already ordered
   }
   else if(D14 <= D32 && D14 <= D34)
      swap(Leptons.Lepton12, Leptons.Lepton22);
   else if(D32 <= D34)
      swap(Leptons.Lepton11, Leptons.Lepton21);
   else
   {
      swap(Leptons.Lepton11, Leptons.Lepton21);
      swap(Leptons.Lepton12, Leptons.Lepton22);
   }

   return Leptons;
}

bool PassBaselineCut(EventParameters Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(Event.ZMass < 4)    return false;
   if(Event.Z2Mass < 4)   return false;

   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 2)   return false;
   if(LPTs[2] < 2)   return false;
   if(LPTs[1] < 2)   return false;
   if(LPTs[0] < 2)   return false;

   // if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   // if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   // if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   // if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}



