#ifndef RHOCALCULATOR_H_22753
#define RHOCALCULATOR_H_22753

#include <vector>
#include <map>

#include "fastjet/PseudoJet.hh"

#include "Code/TauHelperFunctions3.h"

class RhoCalculator;

class RhoCalculator
{
private:
   const int EtaBinCount = 82;
   std::vector<double> EtaBins;
   std::vector<double> NTowers;
   double MinTowerFraction;
   double NSigmaPU;
   double PUPTMin;
   double JetR;
   double RadiusPU;
   double SigmaCut;
private:
   std::map<std::pair<int, int>, double> DiscretizePF(std::vector<FourVector> &PF);
   std::vector<fastjet::PseudoJet> TowerToPseudoJet(const std::map<std::pair<int, int>, double> &PFTowers);
   std::pair<int, int> GetIEtaIPhi(std::pair<double, double> EtaPhi);
   std::pair<int, int> GetIEtaIPhi(double Eta, double Phi);
   std::pair<double, double> GetEtaPhi(std::pair<int, int> IEtaIPhi);
   std::pair<double, double> GetEtaPhi(int IEta, int IPhi);
   double GetDR2(double Eta1, double Phi1, double Eta2, double Phi2);
public:
   RhoCalculator();
   std::vector<double> CalculateRho(std::vector<FourVector> &PF);
   void SetMinTowerFraction(double fraction = 0.7) { MinTowerFraction = fraction; }
   void SetNSigmaPU(double nsigmapu = 1)           { NSigmaPU = nsigmapu; }
   void SetPUPTMin(double PUPTMin = 15)            { PUPTMin = PUPTMin; }
   void SetJetR(double JetR = 0.3)                 { JetR = JetR; }
   void SetRadiusPU(double RadiusPU = 0.5)         { RadiusPU = RadiusPU; }
   void SetSigmaCut(double SigmaCut = 5.0)         { SigmaCut = SigmaCut; }
public:
   void SetCMSPreset();
};



#endif
