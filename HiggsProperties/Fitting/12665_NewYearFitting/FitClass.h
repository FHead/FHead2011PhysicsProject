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
   bool FloatA2ZZA1ZZ;    double A2ZZA1ZZInitialValue;
   bool FloatA2ZZPhase;   double A2ZZPhaseInitialValue;
   bool FloatA3ZZA1ZZ;    double A3ZZA1ZZInitialValue;
   bool FloatA3ZZPhase;   double A3ZZPhaseInitialValue;
   bool FloatA2ZAA1ZZ;    double A2ZAA1ZZInitialValue;
   bool FloatA2ZAPhase;   double A2ZAPhaseInitialValue;
   bool FloatA3ZAA1ZZ;    double A3ZAA1ZZInitialValue;
   bool FloatA3ZAPhase;   double A3ZAPhaseInitialValue;
   bool FloatA2AAA1ZZ;    double A2AAA1ZZInitialValue;
   bool FloatA2AAPhase;   double A2AAPhaseInitialValue;
   bool FloatA3AAA1ZZ;    double A3AAA1ZZInitialValue;
   bool FloatA3AAPhase;   double A3AAPhaseInitialValue;
   bool FloatFem;         double FemInitialValue;
   bool FloatFme;         double FmeInitialValue;
   bool FloatFee;         double FeeInitialValue;
   bool FloatFmm;         double FmmInitialValue;
   bool FloatFZJem;       double FZJemInitialValue;
   bool FloatFZJme;       double FZJmeInitialValue;
   bool FloatFZJee;       double FZJeeInitialValue;
   bool FloatFZJmm;       double FZJmmInitialValue;
   bool FloatFggZZem;     double FggZZemInitialValue;
   bool FloatFggZZme;     double FggZZmeInitialValue;
   bool FloatFggZZee;     double FggZZeeInitialValue;
   bool FloatFggZZmm;     double FggZZmmInitialValue;
   bool FloatN1;          double N1InitialValue;
   bool FloatN2;          double N2InitialValue;
   bool FloatN3;          double N3InitialValue;
   bool FloatN4;          double N4InitialValue;
   bool FloatN5;          double N5InitialValue;
   bool FloatN6;          double N6InitialValue;
   bool FloatN7;          double N7InitialValue;
public:
   FitConfiguration();
   FitConfiguration(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs);
   FitConfiguration(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs,
      vector<double> Ratios, vector<double> Phases, vector<double> Fractions, vector<double> Ns);
   ~FitConfiguration();
   void SetFloats(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs);
   void SetFloatAs(string FloatAs);
   void SetFloatPhases(string FloatPhases);
   void SetFloatFractions(string FloatFractions);
   void SetFloatNs(string FloatNs);
   void SetInitialRatios(const vector<double> Ratios);
   void SetInitialPhases(const vector<double> Phases);
   void SetInitialFractions(const vector<double> Fractions);
   void SetInitialNs(const vector<double> Ns);
   int TotalNumberOfFloats();
};

struct FitResultSummary
{
public:
   double A2ZZA1ZZ, A2ZZA1ZZError;
   double A2ZZPhase, A2ZZPhaseError;
   double A3ZZA1ZZ, A3ZZA1ZZError;
   double A3ZZPhase, A3ZZPhaseError;
   double A2ZAA1ZZ, A2ZAA1ZZError;
   double A2ZAPhase, A2ZAPhaseError;
   double A3ZAA1ZZ, A3ZAA1ZZError;
   double A3ZAPhase, A3ZAPhaseError;
   double A2AAA1ZZ, A2AAA1ZZError;
   double A2AAPhase, A2AAPhaseError;
   double A3AAA1ZZ, A3AAA1ZZError;
   double A3AAPhase, A3AAPhaseError;
   double Fem, FemError;
   double Fme, FmeError;
   double Fee, FeeError;
   double Fmm, FmmError;
   double FZJem, FZJemError;
   double FZJme, FZJmeError;
   double FZJee, FZJeeError;
   double FZJmm, FZJmmError;
   double FggZZem, FggZZemError;
   double FggZZme, FggZZmeError;
   double FggZZee, FggZZeeError;
   double FggZZmm, FggZZmmError;
   double N1, N1Error;
   double N2, N2Error;
   double N3, N3Error;
   double N4, N4Error;
   double N5, N5Error;
   double N6, N6Error;
   double N7, N7Error;
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
   std::vector<double> V[92][13];   // Background = 0, Signal = 1-91; second index = CUDWNHSFCABCD
   std::vector<double> I[92][13];   // same as above
   std::vector<double> V2[2][13];   // Z+J = 0, ggZZ = 1; second index the same as above
   std::vector<double> I2[2][13];
   std::vector<EventParameters> E;
   std::vector<std::string> S;
   int SignalStateCount[4];
   int BackgroundStateCount[4];
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(SingleEvent &event);
   void AddPoint(double v[92][13], double i[92][13], double v2[2][13], double i2[2][13],
      EventParameters &Event, std::string State);
   void ClearPoints();

   FitResultSummary DoFit(FitConfiguration configuration = FitConfiguration());

   void PlotResult(PsFileHelper *PsFile, FitResultSummary Result);
};

struct SingleEvent
{
public:
   double v[92][13];
   double i[92][13];
   double v2[2][13];
   double i2[2][13];
   std::string state;
   EventParameters event;
};




