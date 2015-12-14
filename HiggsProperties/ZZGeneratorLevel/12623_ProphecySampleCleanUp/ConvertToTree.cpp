#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"

#include "AngleConversion.h"

#include "PTYFunctions.h"
#include "LeptonResponse.h"

int main(int argc, char *argv[]);
double GetASmear(const FourVector &Lepton, int PDGID);
pair<double, double> GetPTY();
int FlipLepton(int PDGID);
bool PassBaselineCut(EventParameters &Event);

int main(int argc, char *argv[])
{
   string InputFile = "UpD_4eBG_pTgt2_110to140GeV_ZZpZApAA_All.leptons";
   string OutputFile = "MC.root";

   if(argc <= 2)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputFile" << endl;
      return -1;
   }

   InputFile = argv[1];
   OutputFile = argv[2];

   TFile File(OutputFile.c_str(), "RECREATE");

   TTree Tree("MCTree", "MCTree");

   double zzmass, z1mass, z2mass, costheta1, costheta2, phi, costhetastar, phistar;
   Tree.Branch("zzmass", &zzmass, "zzmass/D");
   Tree.Branch("z1mass", &z1mass, "z1mass/D");
   Tree.Branch("z2mass", &z2mass, "z2mass/D");
   Tree.Branch("costheta1", &costheta1, "costheta1/D");
   Tree.Branch("costheta2", &costheta2, "costheta2/D");
   Tree.Branch("phi", &phi, "phi/D");
   Tree.Branch("costhetastar", &costhetastar, "costhetastar/D");
   Tree.Branch("phistar", &phistar, "phistar/D");

   float l1pt, l1eta, l1phi;   int l1id;
   float l2pt, l2eta, l2phi;   int l2id;
   float l3pt, l3eta, l3phi;   int l3id;
   float l4pt, l4eta, l4phi;   int l4id;
   Tree.Branch("l1pt", &l1pt, "l1pt/F");
   Tree.Branch("l1eta", &l1eta, "l1eta/F");
   Tree.Branch("l1phi", &l1phi, "l1phi/F");
   Tree.Branch("l1id", &l1id, "l1id/I");
   Tree.Branch("l2pt", &l2pt, "l2pt/F");
   Tree.Branch("l2eta", &l2eta, "l2eta/F");
   Tree.Branch("l2phi", &l2phi, "l2phi/F");
   Tree.Branch("l2id", &l2id, "l2id/I");
   Tree.Branch("l3pt", &l3pt, "l3pt/F");
   Tree.Branch("l3eta", &l3eta, "l3eta/F");
   Tree.Branch("l3phi", &l3phi, "l3phi/F");
   Tree.Branch("l3id", &l3id, "l3id/I");
   Tree.Branch("l4pt", &l4pt, "l4pt/F");
   Tree.Branch("l4eta", &l4eta, "l4eta/F");
   Tree.Branch("l4phi", &l4phi, "l4phi/F");
   Tree.Branch("l4id", &l4id, "l4id/I");

   float weight;
   Tree.Branch("weight", &weight, "weight/F");

   bool PassBaseline;
   Tree.Branch("PassBaseline", &PassBaseline, "PassBaseline/O");

   ifstream in(InputFile.c_str());

   vector<FourVector> Leptons;
   vector<int> PDGIDs;

   while(in)
   {
      int PDGID = 0, Status = 0, Mother1 = -1, Mother2 = -1, Color1 = -1, Color2 = -1;
      double Px = 0, Py = 0, Pz = 0, E = -1, M = 0;
      double Something1 = 0, Something2 = 0;

      char ch[10240] = "";
      in.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream line(ch);

      line >> PDGID >> Status >> Mother1 >> Mother2 >> Color1 >> Color2;
      line >> Px >> Py >> Pz >> E >> M;
      line >> Something1 >> Something2;

      if(PDGID == 0)    continue;
      if(Status != 1)   continue;
      if(Mother1 < 0)   continue;
      if(Mother2 < 0)   continue;
      if(Color1 != 0)   continue;
      if(Color2 != 0)   continue;

      PDGIDs.push_back(PDGID);
      Leptons.push_back(FourVector(E, Px, Py, Pz));
   }

   cout << "Number of leptons = " << Leptons.size() << endl;

   for(int i = 0; i + 4 <= (int)Leptons.size(); i = i + 4)
   {
      if(DrawRandom(0, 1) > 0.5)
      {
         PDGIDs[i+0] = FlipLepton(PDGIDs[i+0]);
         PDGIDs[i+1] = FlipLepton(PDGIDs[i+1]);
         PDGIDs[i+2] = FlipLepton(PDGIDs[i+2]);
         PDGIDs[i+3] = FlipLepton(PDGIDs[i+3]);
      }

      FourVector Total = Leptons[i+0] + Leptons[i+1] + Leptons[i+2] + Leptons[i+3];
      Leptons[i+0] = Leptons[i+0].Boost(Total, -Total.GetP() / Total[0]);
      Leptons[i+1] = Leptons[i+1].Boost(Total, -Total.GetP() / Total[0]);
      Leptons[i+2] = Leptons[i+2].Boost(Total, -Total.GetP() / Total[0]);
      Leptons[i+3] = Leptons[i+3].Boost(Total, -Total.GetP() / Total[0]);

      Leptons[i+0] = Leptons[i+0] * GetASmear(Leptons[i+0], PDGIDs[i+0]);
      Leptons[i+1] = Leptons[i+1] * GetASmear(Leptons[i+1], PDGIDs[i+1]);
      Leptons[i+2] = Leptons[i+2] * GetASmear(Leptons[i+2], PDGIDs[i+2]);
      Leptons[i+3] = Leptons[i+3] * GetASmear(Leptons[i+3], PDGIDs[i+3]);
      
      double M12 = (Leptons[i+0] + Leptons[i+1]).GetMass();
      double M14 = (Leptons[i+0] + Leptons[i+3]).GetMass();
      double M32 = (Leptons[i+2] + Leptons[i+1]).GetMass();
      double M34 = (Leptons[i+2] + Leptons[i+3]).GetMass();
      
      double M13 = (Leptons[i+0] + Leptons[i+2]).GetMass();
      double M24 = (Leptons[i+1] + Leptons[i+3]).GetMass();

      if(M12 < 4 || M14 < 4 || M32 < 4 || M34 < 4)   // phase space cut!
         continue;
      if(M13 < 4 || M24 < 4)   // hmm?
         continue;
      if(Leptons[i+0].GetPT() < 2 || Leptons[i+1].GetPT() < 2
         || Leptons[i+2].GetPT() < 2 || Leptons[i+3].GetPT() < 2)
         continue;

      LeptonVectors Vectors;

      int I1 = 0, I2 = 1, I3 = 2, I4 = 3;
      int ID1 = PDGIDs[i], ID2 = PDGIDs[i+1], ID3 = PDGIDs[i+2], ID4 = PDGIDs[i+3];
      if(ID1 < 0)   ID1 = -ID1;
      if(ID2 < 0)   ID2 = -ID2;
      if(ID3 < 0)   ID3 = -ID3;
      if(ID4 < 0)   ID4 = -ID4;

      double D12 = fabs(M12 - 91.186);
      double D14 = fabs(M14 - 91.186);
      double D32 = fabs(M32 - 91.186);
      double D34 = fabs(M34 - 91.186);

      if(ID1 == ID2 && ID1 == ID3 && ID1 == ID4)
      {
         if(D12 <= D14 && D12 <= D32 && D12 <= D34)
            I1 = 0, I2 = 1, I3 = 2, I4 = 3;
         else if(D14 <= D32 && D14 <= D34)
            I1 = 0, I2 = 3, I3 = 2, I4 = 1;
         else if(D32 <= D34)
            I1 = 2, I2 = 1, I3 = 0, I4 = 3;
         else
            I1 = 2, I2 = 3, I3 = 0, I4 = 1;
      }
      else
      {
         if(D12 < D34)
            I1 = 0, I2 = 1, I3 = 2, I4 = 3;
         else
            I1 = 2, I2 = 3, I3 = 0, I4 = 1;
      }
      
      if(PDGIDs[i+I1] < PDGIDs[i+I2])   // particle first, then anti-particle
         swap(I1, I2);
      if(PDGIDs[i+I3] < PDGIDs[i+I4])
         swap(I3, I4);

      if(PDGIDs[i+I1] == 13 && PDGIDs[i+I3] == 11)
      {
         PDGIDs[i+I1] = 11;
         PDGIDs[i+I2] = -11;
         PDGIDs[i+I3] = 13;
         PDGIDs[i+I4] = -13;
      }

      Vectors.Lepton11 = Leptons[i+I1];
      Vectors.Lepton12 = Leptons[i+I2];
      Vectors.Lepton21 = Leptons[i+I3];
      Vectors.Lepton22 = Leptons[i+I4];

      EventParameters Event = ConvertVectorsToAnglesRoberto(Vectors);

      zzmass = Event.HMass;
      z1mass = Event.ZMass;
      z2mass = Event.Z2Mass;
      costheta1 = cos(Event.Theta1);
      costheta2 = cos(Event.Theta2);
      phi = Event.Phi;
      costhetastar = cos(Event.Theta0);
      phistar = Event.Phi0;

      l1pt = Vectors.Lepton11.GetPT();
      l1eta = Vectors.Lepton11.GetEta();
      l1phi = Vectors.Lepton11.GetPhi();
      l1id = PDGIDs[i+I1];
      l2pt = Vectors.Lepton12.GetPT();
      l2eta = Vectors.Lepton12.GetEta();
      l2phi = Vectors.Lepton12.GetPhi();
      l2id = PDGIDs[i+I2];
      l3pt = Vectors.Lepton21.GetPT();
      l3eta = Vectors.Lepton21.GetEta();
      l3phi = Vectors.Lepton21.GetPhi();
      l3id = PDGIDs[i+I3];
      l4pt = Vectors.Lepton22.GetPT();
      l4eta = Vectors.Lepton22.GetEta();
      l4phi = Vectors.Lepton22.GetPhi();
      l4id = PDGIDs[i+I4];
      
      weight = 1;
      if(PDGIDs[i+I1] == 11 || PDGIDs[i+I1] == -11)
         weight = weight * GetElectronEfficiencyPtEta(l1pt, Vectors.Lepton11[3] / Vectors.Lepton11.GetP(), l1phi);
      else
         weight = weight * GetMuonEfficiencyPtEta(l1pt, Vectors.Lepton11[3] / Vectors.Lepton11.GetP(), l1phi);
      if(PDGIDs[i+I2] == 11 || PDGIDs[i+I2] == -11)
         weight = weight * GetElectronEfficiencyPtEta(l2pt, Vectors.Lepton12[3] / Vectors.Lepton12.GetP(), l2phi);
      else
         weight = weight * GetMuonEfficiencyPtEta(l2pt, Vectors.Lepton12[3] / Vectors.Lepton12.GetP(), l2phi);
      if(PDGIDs[i+I3] == 11 || PDGIDs[i+I3] == -11)
         weight = weight * GetElectronEfficiencyPtEta(l3pt, Vectors.Lepton21[3] / Vectors.Lepton21.GetP(), l3phi);
      else
         weight = weight * GetMuonEfficiencyPtEta(l3pt, Vectors.Lepton21[3] / Vectors.Lepton21.GetP(), l3phi);
      if(PDGIDs[i+I4] == 11 || PDGIDs[i+I4] == -11)
         weight = weight * GetElectronEfficiencyPtEta(l4pt, Vectors.Lepton22[3] / Vectors.Lepton22.GetP(), l4phi);
      else
         weight = weight * GetMuonEfficiencyPtEta(l4pt, Vectors.Lepton22[3] / Vectors.Lepton22.GetP(), l4phi);

      PassBaseline = PassBaselineCut(Event);

      /*
      if(Event.Phi > 2 * PI - 1e-5 || Event.Phi < 1e-5)
      {
         cout << "Weird event!" << endl;
         cout << Vectors << endl;
         cout << Event << endl;
      }
      */

      Tree.Fill();
   }

   Tree.Write();

   File.Close();

   return 0;
}

double GetASmear(const FourVector &Lepton, int PDGID)
{
   return 1;

   double CentralValue = 0;

   if(PDGID == 11 || PDGID == -11)
      CentralValue = SmearElectronCentral(Lepton, 0) * 2;
   else
      CentralValue = SmearMuonCentral(Lepton, 0) * 2;
   if(CentralValue < 1e-10)
      return 0;

   double Delta = 0;

   bool OK = false;
   while(OK == false)
   {
      Delta = DrawRandom(-0.5, 0.5);
      double Value = 0;
      if(PDGID == 11 || PDGID == -11)
         Value = SmearElectronCentral(Lepton, Delta);
      else
         Value = SmearMuonCentral(Lepton, Delta);

      if(DrawRandom(0, 1) < Value / CentralValue)
         OK = true;
   }

   return (Delta + 1);
}

pair<double, double> GetPTY()
{
   pair<double, double> Result;

   bool Good = false;
   while(Good == false)
   {
      Result.first = DrawRandom(0, 500);
      Result.second = DrawRandom(-10, 10);

      double Density = GetPTYDensity(Result.first, Result.second);

      if(DrawRandom(0, 1) < Density)
         Good = true;
   };

   return Result;
}

int FlipLepton(int PDGID)
{
   if(PDGID == 11)   return 13;
   if(PDGID == 13)   return 11;
   if(PDGID == -11)   return -13;
   if(PDGID == -13)   return -11;

   return 0;
}

bool PassBaselineCut(EventParameters &Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(Event.ZMass < 40)    return false;
   if(Event.Z2Mass < 12)   return false;

   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;
   if(LPTs[1] < 7)    return false;
   if(LPTs[0] < 7)    return false;

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}


