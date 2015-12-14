#include <vector>
#include <string>

#include "PlotHelper2Forward.h"
#include "AngleConversion.h"

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
   bool FloatA2ZZ;        double A2ZZInitialValue;
   bool FloatA3ZZ;        double A3ZZInitialValue;
   bool FloatA4ZZ;        double A4ZZInitialValue;
   bool FloatA2ZA;        double A2ZAInitialValue;
   bool FloatA3ZA;        double A3ZAInitialValue;
   bool FloatA4ZA;        double A4ZAInitialValue;
   bool FloatA2AA;        double A2AAInitialValue;
   bool FloatA3AA;        double A3AAInitialValue;
   bool FloatFem;         double FemInitialValue;
   bool FloatFme;         double FmeInitialValue;
   bool FloatFee;         double FeeInitialValue;
   bool FloatFmm;         double FmmInitialValue;
public:
   FitConfiguration();
   FitConfiguration(string FloatAs, string FloatFractions);
   FitConfiguration(string FloatAs, string FloatFractions,
      vector<double> Ratios, vector<double> Fractions);
   ~FitConfiguration();
   void SetFloats(string FloatAs, string FloatFractions);
   void SetFloatAs(string FloatAs);
   void SetFloatFractions(string FloatFractions);
   void SetInitialRatios(const vector<double> Ratios);
   void SetInitialFractions(const vector<double> Fractions);
   int TotalNumberOfFloats();
};

struct FitResultSummary
{
public:
   double A2ZZ, A2ZZError;
   double A3ZZ, A3ZZError;
   double A4ZZ, A4ZZError;
   double A2ZA, A2ZAError;
   double A3ZA, A3ZAError;
   double A4ZA, A4ZAError;
   double A2AA, A2AAError;
   double A3AA, A3AAError;
   double Fem, FemError;
   double Fme, FmeError;
   double Fee, FeeError;
   double Fmm, FmmError;
   double EDM;
   double Sem, Bem;
   double Sme, Bme;
   double See, Bee;
   double Smm, Bmm;
   double TruthNLL, BestNLL;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   std::vector<double> VS[16][16];
   std::vector<double> IS[16][16];
   std::vector<double> VB;
   std::vector<double> IB;
   std::vector<EventParameters> E;
   std::vector<std::string> S;
   int SignalStateCount[4];
   int BackgroundStateCount[4];
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(SingleEvent &event);
   void AddPoint(double vs[16][16], double is[16][16], double vb, double ib, EventParameters &Event, std::string State);
   void ClearPoints();

   FitResultSummary DoFit(FitConfiguration configuration = FitConfiguration());

   void PlotResult(PsFileHelper *PsFile, FitResultSummary Result);
};

struct SingleEvent
{
public:
   double VS[16][16];
   double IS[16][16];
   double VB;
   double IB;
   std::string state;
   EventParameters event;
};




