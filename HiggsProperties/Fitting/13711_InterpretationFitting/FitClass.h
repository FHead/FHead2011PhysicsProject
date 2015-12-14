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
   bool FloatA4ZZA1ZZ;    double A4ZZA1ZZInitialValue;
   bool FloatA4ZZPhase;   double A4ZZPhaseInitialValue;
   bool FloatA5ZZA1ZZ;    double A5ZZA1ZZInitialValue;
   bool FloatA5ZZPhase;   double A5ZZPhaseInitialValue;
   bool FloatYT;          double YTInitialValue;
   bool FloatYTPhase;     double YTPhaseInitialValue;
   bool FloatMT;          double MTInitialValue;
   bool FloatGWW;         double GWWInitialValue;
   bool FloatMW;          double MWInitialValue;
   bool FloatFem;         double FemInitialValue;
   bool FloatFme;         double FmeInitialValue;
   bool FloatFee;         double FeeInitialValue;
   bool FloatFmm;         double FmmInitialValue;
   bool FloatN1;          double N1InitialValue;
   bool FloatN2;          double N2InitialValue;
   double I1ZZModificationFactor;
public:
   FitConfiguration();
   FitConfiguration(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs,
      double i1zzmodification = 1);
   FitConfiguration(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs,
      vector<double> Ratios, vector<double> Phases, vector<double> Fractions, vector<double> Ns,
      double i1zzmodification = 1);
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
   void SetI1ZZModificationFactor(double Factor);
   int TotalNumberOfFloats();
};

struct FitResultSummary
{
public:
   double A2ZZA1ZZ, A2ZZA1ZZError;
   double A2ZZPhase, A2ZZPhaseError;
   double A3ZZA1ZZ, A3ZZA1ZZError;
   double A3ZZPhase, A3ZZPhaseError;
   double A4ZZA1ZZ, A4ZZA1ZZError;
   double A4ZZPhase, A4ZZPhaseError;
   double A5ZZA1ZZ, A5ZZA1ZZError;
   double A5ZZPhase, A5ZZPhaseError;
   double YT, YTError;
   double YTPhase, YTPhaseError;
   double MT, MTError;
   double GWW, GWWError;
   double MW, MWError;
   double Fem, FemError;
   double Fme, FmeError;
   double Fee, FeeError;
   double Fmm, FmmError;
   double N1, N1Error;
   double N2, N2Error;
   double EDM;
   double Sem, Bem;
   double Sme, Bme;
   double See, Bee;
   double Smm, Bmm;
   double I1ZZModificationFactor;
   double TruthNLL, BestNLL;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   std::vector<double> V[154][5];   // Background = 0, Signal = 1-15; second index = CUDWN
   std::vector<double> I[154][5];   // same as above
   std::vector<EventParameters> E;
   std::vector<std::string> S;
   int SignalStateCount[4];
   int BackgroundStateCount[4];
   double I1ZZModificationFactor;
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(SingleEvent &event);
   void AddPoint(double v[154][5], double I[154][5], EventParameters &Event, std::string State);
   void ClearPoints();

   FitResultSummary DoFit(FitConfiguration configuration = FitConfiguration());

   void PlotResult(PsFileHelper *PsFile, FitResultSummary Result);
};

struct SingleEvent
{
public:
   double v[154][5];
   double i[154][5];
   std::string state;
   EventParameters event;
};




