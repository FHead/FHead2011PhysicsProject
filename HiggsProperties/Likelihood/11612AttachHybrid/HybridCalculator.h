#include "Code/TauHelperFunctions2.h"

#include "AngleConversion.h"

// #define HYBRIDCALCULATOR_DEBUG

class HybridCalculator
{
public:
   HybridCalculator();
   ~HybridCalculator();
public:
   void SetEfficiency12(double (*F)(double, double, double));
   void SetEfficiency34(double (*F)(double, double, double));
   void SetSmear12(double (*F)(FourVector &, double));
   void SetSmear34(double (*F)(FourVector &, double));
   void SetMECalculator(double (*F)(LeptonVectors &));
   void SetToleranceF(double Tolerance);
private:
   double (*Efficiency12)(double, double, double);
   double (*Efficiency34)(double, double, double);
   double (*Smear12)(FourVector &, double);
   double (*Smear34)(FourVector &, double);
   std::vector<double (*)(LeptonVectors &)> CalculateMEValue;
   int MECount;
public:
   std::vector<double> SimpleMassIntegral(const EventParameters &TargetParameters);
private:
   void CalculateIntegrand(const EventParameters &TargetParameters, const EventParameters &CentralParameters,
      std::vector<double> &Result);
   void CalculateMEs(const EventParameters &CentralValue, std::vector<double> &ME0,
      std::vector<double> &B1, std::vector<double> &B3);
   double CalculateF(double M, double M0, int Order, bool FirstZ);
   double AdaptCalculateF(double sab, double fa, double fc, double fb, double a, double b,
      double Tolerance, double c1c2, int Order, bool FirstZ, int Depth);
   double f(double x, double c1c2, int Order, bool FirstZ);
private:
   double ToleranceF;
private:   // temporary variable to avoid passing around too much stuff
   EventParameters TempParameters;
   LeptonVectors TempLeptons;
   double TargetM12_2, TargetM13_2, TargetM14_2, TargetM23_2, TargetM24_2, TargetM34_2;
};








