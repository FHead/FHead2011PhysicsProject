//----------------------------------------------------------------------------
#ifndef HybridCalculator_H_KASJDGKASIKGJAHNIWJHNISDHIFASDF
#define HybridCalculator_H_KASJDGKASIKGJAHNIWJHNISDHIFASDF
//----------------------------------------------------------------------------
#include "TauHelperFunctions3.h"
//----------------------------------------------------------------------------
#include "AngleConversion.h"
//----------------------------------------------------------------------------
// #define HYBRIDCALCULATOR_DEBUG
//----------------------------------------------------------------------------
class HybridCalculator
{
public:
   HybridCalculator();
   ~HybridCalculator();
public:
   void SetEfficiency12(double (*F)(double, double, double));
   void SetEfficiency34(double (*F)(double, double, double));
   void SetSmear12(double (*F)(const FourVector &, double));
   void SetSmear34(double (*F)(const FourVector &, double));
   void SetMECalculator(double (*F)(LeptonVectors &));
   void SetToleranceF(double Tolerance);
   void SetIgnorePhi(bool Decision = false);
private:
   double (*Efficiency12)(double, double, double);
   double (*Efficiency34)(double, double, double);
   double (*Smear12)(const FourVector &, double);
   double (*Smear34)(const FourVector &, double);
   std::vector<double (*)(LeptonVectors &)> CalculateMEValue;
   int MECount;
public:
   std::vector<double> SimpleMassIntegral(const EventParameters &TargetParameters, double PT, double Eta);
private:
   void CalculateIntegrand(const EventParameters &TargetParameters, const EventParameters &CentralParameters,
      std::vector<double> &Result, double PT, double Eta);
   void CalculateMEs(const EventParameters &CentralValue, std::vector<double> &ME0,
      std::vector<double> &B1, std::vector<double> &B3);
   double CalculateF(double M, double M0, int Order, bool FirstZ);
   void CalculateF_Order01(double M, double M0, bool FirstZ, double &Result0, double &Result1);
   double AdaptCalculateF(double sab, double fa, double fc, double fb, double a, double b,
      double Tolerance, double c1c2, int Order, bool FirstZ, int Depth);
   void AdaptCalculateF_Order01(double sab0, double fa0, double fc0, double fb0,
      double sab1, double fa1, double fc1, double fb1, double a, double b,
      double Tolerance, double c1c2, bool FirstZ, int Depth, double &Result0, double &Result1);
   double f(double x, double c1c2, int Order, bool FirstZ);
   void f_Order01(double x, double c1c2, bool FirstZ, double &Result0, double &Result1);
private:
   double ToleranceF;
   bool IgnorePhi;
private:   // temporary variable to avoid passing around too much stuff
   EventParameters TempParameters;
   LeptonVectors TempLeptons;
   double TargetM12_2, TargetM13_2, TargetM14_2, TargetM23_2, TargetM24_2, TargetM34_2;
};
//----------------------------------------------------------------------------
#endif






