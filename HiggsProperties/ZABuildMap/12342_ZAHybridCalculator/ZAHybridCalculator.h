//----------------------------------------------------------------------------
#ifndef ZAHybridCalculator_H_KASJDGKASIKGJAHNIWJHNISDHIFASDF
#define ZAHybridCalculator_H_KASJDGKASIKGJAHNIWJHNISDHIFASDF
//----------------------------------------------------------------------------
#include "Code/TauHelperFunctions2.h"
//----------------------------------------------------------------------------
#include "AngleConversion.h"
#include "VolumeElement.h"
//----------------------------------------------------------------------------
// #define ZAHYBRIDCALCULATOR_DEBUG
//----------------------------------------------------------------------------
class ZAMassSquare;
class ZAHybridCalculator;
//----------------------------------------------------------------------------
class ZAMassSquare
{
public:
   double M12_2, M1P_2, M2P_2;
public:
   ZAMassSquare();
   ZAMassSquare(const ZAEventParameters &Event);
   ZAMassSquare(const ZALeptonVectors &Vectors);
   ZAMassSquare FlipL1L2();
};
//----------------------------------------------------------------------------
class ZAHybridCalculator
{
public:
   ZAHybridCalculator();
   ~ZAHybridCalculator();
   ZAHybridCalculator &operator =(const ZAHybridCalculator &other);
public:
   enum VerboseLevel
   {
      VerboseLevel_Quiet = 0,
      VerboseLevel_Normal = 1
   };
public:
   void SetVerbosity(VerboseLevel Value);
   void SetEfficiency12(double (*F)(double, double, double));
   void SetEfficiencyP(double (*F)(double, double, double));
   void SetSmear12(double (*F)(const FourVector &, double));
   void SetSmearP(double (*F)(const FourVector &, double));
   void SetPTYDensity(double (*F)(double, double, double));
   void SetMECalculator(double (*F)(ZALeptonVectors &));
   void SetDoDeltaMH(bool Decision = false, double Value = -1);
   void SetSimpleMassIntegralWindow(double Window);
   void SetSimpleMassIntegralStep(int Step);
   void SetToleranceFZ(double Tolerance);
   void SetToleranceFP(double Tolerance);
   void SetToleranceFF(double Tolerance);
   void SetIntegralCZRange(double Min, double Max);
   void SetIntegralCPRange(double Min, double Max);
   void SetIntegralCZStep(int Step);
   void SetIntegralCPStep(int Step);
public:
   void PrintSettings();
   void PrintSettings(std::ostream &out);
   void TestOutput();
private:
   double (*Efficiency12)(double, double, double);
   double (*EfficiencyP)(double, double, double);
   double (*Smear12)(const FourVector &, double);
   double (*SmearP)(const FourVector &, double);
   double (*PTYDensity)(double, double, double);
   std::vector<double (*)(ZALeptonVectors &)> CalculateMEValue;
   int MECount;
public:
   std::vector<double> SimpleMassIntegral(const ZAEventParameters &RecoParameters);
   std::vector<double> PassThroughMode(const ZAEventParameters &RecoParameters);
private:
   int Verbosity;
   bool DoDeltaMH;   double DeltaMH;
   double SimpleMassIntegralWindow;
   int SimpleMassIntegralStep;
   int ExpansionOrder;
   double ToleranceFZ, ToleranceFP, ToleranceFF;
   double IntegralCZMin, IntegralCPMin;
   double IntegralCZMax, IntegralCPMax;
   int IntegralCZStep, IntegralCPStep;
private:
   std::vector<double> CalculateIntegrand(const ZALeptonVectors &Reco, const ZALeptonVectors &Central);
   void CalculateMEs(const ZALeptonVectors &Central, std::vector<double> &ME0,
      std::vector<double> &B1, std::vector<double> &B3, std::vector<double> &B11,
      std::vector<double> &B13, std::vector<double> &B33);
   void CalculateMEsDeltaMH(const ZALeptonVectors &Central, const ZAMassSquare &RecoMM,
      std::vector<double> &ME0, std::vector<double> &B1, std::vector<double> &B11);
   double CalculateFZ(const FourVector &L1, const FourVector &L2, const ZAMassSquare &RecoMM, int Order);
   double CalculateFP(const FourVector &P, int Order);
   double CalculateFF(const ZALeptonVectors &Vectors, const ZAMassSquare &RecoMM, int Order);
   double AdaptCalculateFZ(double sab, double fa, double fc, double fb, double a, double b,
      const FourVector &L1, const FourVector &L2, const ZAMassSquare &RecoMM,
      double Tolerance, int Order, int Depth);
   double AdaptCalculateFP(double sab, double fa, double fc, double fb, double a, double b,
      const FourVector &Photon, double Tolerance, int Order, int Depth);
   double AdaptCalculateFF(double sab, double fa, double fc, double fb, double a, double b,
      const ZALeptonVectors &Vectors, const ZAMassSquare &RecoMM, double Tolerance, int Order, int Depth);
   double FZ(double c, const FourVector &L1, const FourVector &L2, const ZAMassSquare &RecoMM, int Order);
   double FP(double c, const FourVector &Photon, int Order);
   double FF(double c, const ZALeptonVectors &Vectors, const ZAMassSquare &RecoMM, int Order);
   void FillMassPosition(int Step, double Center, double Window, double AttractorStrength, double Masses[]);
   void FillMassWeights(int Step, double Masses[], double Weights[]);
   ZALeptonVectors GoToRest(ZALeptonVectors Vectors);
   double CalculateJS(const ZAMassSquare &RMM, const ZACs &C);
   double CalculateJB(const ZAMassSquare &RMM, const ZACs &C);
   double CalculateCP(const ZAMassSquare &RMM, const double c1, const double GenM12_2);
private:
   std::string TextBool(bool Meow);
};
//----------------------------------------------------------------------------
#endif






