// this "acceptance" includes detector geometry (rough) and muon pt requirement
#include <map>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

#include "Vector4.h"
#include "DrawRandom.h"

int main();
void CheckAcceptance();
int CheckAcceptance(double ZPt, int Count = 100000);

int main()
{
   CheckAcceptance();

   return 0;
}

void CheckAcceptance()
{
   map<double, int> Reconstructed;

   TFile F("Output.root", "RECREATE");
   TH1D Histogram("ResultHistogramCount",
      "Counts reconstructed out of 200000;Z PT (GeV/c);Reconstruected count", 1001, -0.5, 1000.5);
   TH1D Histogram2("ResultHistogramPercentage",
      "Percentage falling in kinematic cut acceptance;Z PT (GeV/c);Percentage", 1001, -0.5, 1000.5);

   const int NumberOfTrials = 200000;
   for(double pt = 0; pt <= 1000; pt = pt + 1)
   {
      int ReconstructedCount = CheckAcceptance(pt, NumberOfTrials);
      Reconstructed.insert(pair<double, int>(pt, ReconstructedCount));

      cout << pt << " " << ReconstructedCount << "/" << NumberOfTrials << endl;

      Histogram.Fill(pt, ReconstructedCount);
      Histogram2.Fill(pt, (double)ReconstructedCount / NumberOfTrials);
   }

   Histogram.Write();
   Histogram2.Write();
   F.Close();
}

int CheckAcceptance(double ZPt, int Count)
{
   int Reconstructed = 0;

   for(int i = 0; i < Count; i++)
   {
      // get lepton direction at Z rest frame
      double MuonPhi = DrawRandom(PI * 2);
      double MuonTheta = DrawSine(0, PI);
      const double ZMass = 91.1876;
      double MuonEnergy = ZMass / 2;

      Vector4 Muon1Momentum(MuonEnergy, MuonEnergy * sin(MuonTheta) * cos(MuonPhi),
         MuonEnergy * sin(MuonTheta) * sin(MuonPhi), MuonEnergy * cos(MuonTheta));
      Vector4 Muon2Momentum(MuonEnergy, MuonEnergy * sin(PI - MuonTheta) * cos(-MuonPhi),
         MuonEnergy * sin(PI - MuonTheta) * sin(-MuonPhi), MuonEnergy * cos(PI - MuonTheta));

      double ZEnergy = sqrt(ZMass * ZMass + ZPt * ZPt);
      Vector4 ZDirection(ZEnergy, ZPt, 0, 0);   // without loss of generality, Z goes in x direction
      double Beta = ZPt / ZEnergy;

      Muon1Momentum = Muon1Momentum.Boost(ZDirection, Beta);
      Muon2Momentum = Muon2Momentum.Boost(ZDirection, Beta);

      // detector acceptance emulation
      if(Muon1Momentum.Eta() > 2.4 || Muon1Momentum.Eta() < -2.4)
         continue;
      if(Muon2Momentum.Eta() > 2.4 || Muon2Momentum.Eta() < -2.4)
         continue;

      // muon PT/eta cut emulation
      int PassFirstLeg = 0;
      int PassSecondLeg = 0;

      if(fabs(Muon1Momentum.Eta()) < 2.1 && Muon1Momentum.PT() > 15)
         PassFirstLeg = PassFirstLeg + 1;
      if(fabs(Muon2Momentum.Eta()) < 2.1 && Muon2Momentum.PT() > 15)
         PassFirstLeg = PassFirstLeg + 1;
      
      if(fabs(Muon1Momentum.Eta()) < 2.4 && Muon1Momentum.PT() > 10)
         PassSecondLeg = PassSecondLeg + 1;
      if(fabs(Muon2Momentum.Eta()) < 2.4 && Muon2Momentum.PT() > 10)
         PassSecondLeg = PassSecondLeg + 1;

      if(PassFirstLeg == 0)
         continue;
      if(PassSecondLeg < 2)
         continue;

      Reconstructed = Reconstructed + 1;
   }

   return Reconstructed;
}


