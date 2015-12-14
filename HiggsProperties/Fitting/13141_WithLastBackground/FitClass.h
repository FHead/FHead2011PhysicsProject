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
   bool FloatAA[6];            double AAInitialValue[6];
   bool FloatPhase[6];         double PhaseInitialValue[6];
   bool FloatCount[4];         double CountInitialValue[4];
   bool FloatF[4];             double FInitialValue[4];
   bool FloatFZJ[4];           double FZJInitialValue[4];
   bool FloatFggZZ[4];         double FggZZInitialValue[4];
   bool FloatN[7];             double NInitialValue[7];
public:
   double NSConstrain[4];      double NSConstrainSigma[4];
   double NBConstrain[4];      double NBConstrainSigma[4];
   double NZJConstrain[4];     double NZJConstrainSigma[4];
   double NggZZConstrain[4];   double NggZZConstrainSigma[4];
public:
   FitConfiguration();
   FitConfiguration(string FloatAs, string FloatPhases, string FloatCounts,
      string FloatFractions, string FloatNs);
   FitConfiguration(string FloatAs, string FloatPhases, string FloatCounts,
      string FloatFractions, string FloatNs,
      vector<double> Ratios, vector<double> Phases, vector<double> Counts,
      vector<double> Fractions, vector<double> Ns,
      vector<double> NS, vector<double> NSSigma, vector<double> NB, vector<double> NBSigma,
      vector<double> NZJ, vector<double> NZJSigma, vector<double> NggZZ, vector<double> NggZZSigma);
   ~FitConfiguration();
   void SetFloats(string FloatAs, string FloatPhases, string FloatCounts,
      string FloatFractions, string FloatNs);
   void SetFloatAs(string FloatAs);
   void SetFloatPhases(string FloatPhases);
   void SetFloatCounts(string FloatCounts);
   void SetFloatFractions(string FloatFractions);
   void SetFloatNs(string FloatNs);
   void SetInitialRatios(const vector<double> Ratios);
   void SetInitialPhases(const vector<double> Phases);
   void SetInitialCounts(const vector<double> Counts);
   void SetInitialFractions(const vector<double> Fractions);
   void SetInitialNs(const vector<double> Ns);
   void SetNSConstrain(const vector<double> NS, const vector<double> NSSigma);
   void SetNBConstrain(const vector<double> NB, const vector<double> NBSigma);
   void SetNZJConstrain(const vector<double> NZJ, const vector<double> NZJSigma);
   void SetNggZZConstrain(const vector<double> NggZZ, const vector<double> NggZZSigma);
   int TotalNumberOfFloats();
};

struct FitResultSummary
{
public:
   double AA[6], AAError[6];
   double Phase[6], PhaseError[6];
   double Count[4], CountError[4];
   double F[4], FError[4];
   double FZJ[4], FZJError[4];
   double FggZZ[4], FggZZError[4];
   double N[7], NError[7];
   double EDM;
   double S[4], B[4], ZJ[4], ggZZ[4];
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
   int ZJStateCount[4];
   int ggZZStateCount[4];
public:
   double NSConstrainMu[4], NSConstrainSigma[4];
   double NBConstrainMu[4], NBConstrainSigma[4];
   double NZJConstrainMu[4], NZJConstrainSigma[4];
   double NggZZConstrainMu[4], NggZZConstrainSigma[4];
   double EventCount[4];
   double GetLogNormalMu(double Mean, double RelativeError);
   double GetLogNormalSigma(double Mean, double RelativeError);
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
   double weight;
};




