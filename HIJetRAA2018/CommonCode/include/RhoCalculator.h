#ifndef RHOCALCULATOR_H_22753
#define RHOCALCULATOR_H_22753

#include <vector>
#include <map>

#include "fastjet/PseudoJet.hh"

#include "Code/TauHelperFunctions3.h"

class RhoCalculator;
class RhoModulationCalculator;

class RhoCalculator
{
private:
   int EtaBinCount;
   std::vector<double> EtaBins;
   std::vector<double> NTowers;
   double MinTowerFraction;
   double NSigmaPU;
   double PUPTMin;
   double JetR;
   double RadiusPU;
   double SigmaCut;
   std::vector<double> RhoParameters;
private:
   void InitializeCMSEtaBins();
   void InitializeCMSReducedEtaBins();
   std::map<std::pair<int, int>, double> DiscretizePF(const std::vector<FourVector> &PF);
   std::vector<fastjet::PseudoJet> TowerToPseudoJet(const std::map<std::pair<int, int>, double> &PFTowers);
   std::pair<int, int> GetIEtaIPhi(std::pair<double, double> EtaPhi);
   std::pair<int, int> GetIEtaIPhi(double Eta, double Phi);
   std::pair<double, double> GetEtaPhi(std::pair<int, int> IEtaIPhi);
   std::pair<double, double> GetEtaPhi(int IEta, int IPhi);
   double GetDR2(double Eta1, double Phi1, double Eta2, double Phi2);
public:
   RhoCalculator();
   std::vector<double> CalculateRho(const std::vector<FourVector> &PF);
   std::vector<double> GetRhoParameters()          { return RhoParameters; }
   void SetMinTowerFraction(double fraction = 0.7) { MinTowerFraction = fraction; }
   void SetNSigmaPU(double nsigmapu = 1)           { NSigmaPU = nsigmapu; }
   void SetPUPTMin(double PUPTMin = 15)            { PUPTMin = PUPTMin; }
   void SetJetR(double JetR = 0.3)                 { JetR = JetR; }
   void SetRadiusPU(double RadiusPU = 0.5)         { RadiusPU = RadiusPU; }
   void SetSigmaCut(double SigmaCut = 5.0)         { SigmaCut = SigmaCut; }
   void SetReducedEtaBins()                        { InitializeCMSReducedEtaBins(); }
   double GetRho(double Eta);
public:
   void SetCMSPreset();
};

class RhoModulationCalculator
{
private:
   double AbsEtaMax;
   double PTMin;
   double PTMax;
   std::vector<double> Parameters;
   double ExternalPhi2;
   double ExternalPhi3;
   bool UseExternalPhi;
public:
   RhoModulationCalculator();
   double SetCMSPreset();
   std::vector<double> DoRhoModulationFit(const std::vector<FourVector> &PF, bool FloatEventPlane = false, bool RandomizePhi = false);
   std::vector<double> GetParameters() { return Parameters; }
   void SetAbsEtaMax(double Value) { AbsEtaMax = Value; }
   void SetPTMin(double Value)     { PTMin = Value; }
   void SetPTMax(double Value)     { PTMax = Value; }
   void SetExternalPhi(bool Use, double V2 = 0, double V3 = 0)
   {
      UseExternalPhi = Use;
      ExternalPhi2 = V2;
      ExternalPhi3 = V3;
   }
   double GetModulation(double Phi);
};


#endif
