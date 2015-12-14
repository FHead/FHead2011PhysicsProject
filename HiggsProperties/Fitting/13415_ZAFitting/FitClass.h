#include <vector>
#include <string>

#include "PlotHelper2Forward.h"
#include "AngleConversion.h"

#define FITMODE_ALL 0
#define FITMODE_SIGNALONLY 1
#define FITMODE_PHASEONLY 2

struct FitConfiguration;
struct FitResultSummary;
class FitClass;
struct SingleEvent;
vector<double> ListToVector(int N = 0, double x1 = 0, double x2 = 0, double x3 = 0, double x4 = 0,
   double x5 = 0, double x6 = 0, double x7 = 0, double x8 = 0, double x9 = 0, double x10 = 0,
   double x11 = 0, double x12 = 0, double x13 = 0, double x14 = 0, double x15 = 0, double x16 = 0);

struct FitConfiguration
{
public:
   bool FloatPhi[3];        double PhiInitialValue[3];
   bool FloatPhase[4];      double PhaseInitialValue[4];
   bool FloatFraction[1];   double FractionInitialValue[1];
public:
   FitConfiguration();
   FitConfiguration(string FloatPhis, string FloatPhases, string FloatFractions);
   FitConfiguration(string FloatPhis, string FloatPhases, string FloatFractions,
      vector<double> Phis, vector<double> Phases, vector<double> Fractions);
   ~FitConfiguration();
   void SetFloats(string FloatPhis, string FloatPhases, string Fractions);
   void SetFloatPhis(string FloatPhis);
   void SetFloatPhases(string FloatPhases);
   void SetFloatFractions(string FloatFractions);
   void SetInitialPhis(const vector<double> Phis);
   void SetInitialPhases(const vector<double> Phases);
   void SetInitialFractions(const vector<double> Fractions);
   int TotalNumberOfFloats();
};

struct FitResultSummary
{
public:
   double Phi[3], PhiError[3];
   double Phase[4], PhaseError[4];
   double Fraction, FractionError;
   double EDM;
   double TruthNLL, BestNLL;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   std::vector<double> VS[36];
   std::vector<double> IS[36];
   std::vector<double> VB[1];
   std::vector<double> IB[1];
   std::vector<ZAEventParameters> E;
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(SingleEvent &event);
   void AddPoint(double vs[36], double is[36], double vb[36], double ib[36], ZAEventParameters &Event);
   void ClearPoints();
   double PrimaryAngle(double x);

   FitResultSummary DoFit(FitConfiguration configuration = FitConfiguration());
};

struct SingleEvent
{
public:
   double vs[36];
   double is[36];
   double vb[1];
   double ib[1];
   ZAEventParameters event;
};




