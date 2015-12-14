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
   bool FloatA2ZZA1ZZ;    double A2ZZA1ZZInitialValue;
   bool FloatA3ZZA1ZZ;    double A3ZZA1ZZInitialValue;
   bool FloatA4ZZA1ZZ;    double A4ZZA1ZZInitialValue;
   bool FloatYT;          double YTInitialValue;
   bool FloatYTA;         double YTAInitialValue;
   bool FloatMT;          double MTInitialValue;
   bool FloatGWW;         double GWWInitialValue;
   bool FloatMW;          double MWInitialValue;
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
   double A2ZZA1ZZ, A2ZZA1ZZError;
   double A3ZZA1ZZ, A3ZZA1ZZError;
   double A4ZZA1ZZ, A4ZZA1ZZError;
   double YT, YTError;
   double YTA, YTAError;
   double MT, MTError;
   double GWW, GWWError;
   double MW, MWError;
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
   std::vector<double> VS[12][12];
   std::vector<double> IS[12][12];
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
   void AddPoint(double vs[12][12], double is[12][12], double vb, double ib, EventParameters &Event, std::string State);
   void ClearPoints();

   FitResultSummary DoFit(FitConfiguration configuration = FitConfiguration());

   void PlotResult(PsFileHelper *PsFile, FitResultSummary Result);
};

struct SingleEvent
{
public:
   double VS[12][12];
   double IS[12][12];
   double VB;
   double IB;
   std::string state;
   EventParameters event;
};




