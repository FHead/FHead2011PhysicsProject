#ifndef FITCLASS_H_JQIAKSJFGIAKSNJDGIADNGKADSJGASDJGSJDGASDJGASDJGDS
#define FITCLASS_H_JQIAKSJFGIAKSNJDGIADNGKADSJGASDJGSJDGASDJGASDJGDS

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
   bool FloatAA[8];               double AAInitialValue[8];
   bool FloatPhase[8];            double PhaseInitialValue[8];
   bool FloatCount[2][4];         double CountInitialValue[2][4];
   bool FloatF[2][4];             double FInitialValue[2][4];
   bool FloatFZJ[2][4];           double FZJInitialValue[2][4];
   bool FloatFggZZ[2][4];         double FggZZInitialValue[2][4];
   bool FloatN[7];                double NInitialValue[7];
   bool FloatMu;                  double MuInitialValue;
public:
   double NSConstrain[2][4];      double NSConstrainSigma[2][4];
   double NBConstrain[2][4];      double NBConstrainSigma[2][4];
   double NZJConstrain[2][4];     double NZJConstrainSigma[2][4];
   double NggZZConstrain[2][4];   double NggZZConstrainSigma[2][4];
public:
   FitConfiguration();
   FitConfiguration(string FloatAs, string FloatPhases, string FloatCounts7TeV, string FloatCounts8TeV,
      string FloatFractions7TeV, string FloatFractions8TeV, string FloatNs, string FloatRate);
   FitConfiguration(string FloatAs, string FloatPhases, string FloatCounts7TeV, string FloatCounts8TeV,
      string FloatFractions7TeV, string FloatFractions8TeV, string FloatNs, string FloatRate,
      vector<double> Ratios, vector<double> Phases,
      vector<double> Counts7TeV,     vector<double> Counts8TeV,
      vector<double> Fractions7TeV,  vector<double> Fractions8TeV,
      vector<double> Ns,
      vector<double> NS7TeV,         vector<double> NS8TeV,
      vector<double> NSSigma7TeV,    vector<double> NSSigma8TeV,
      vector<double> NB7TeV,         vector<double> NB8TeV,
      vector<double> NBSigma7TeV,    vector<double> NBSigma8TeV,
      vector<double> NZJ7TeV,        vector<double> NZJ8TeV,
      vector<double> NZJSigma7TeV,   vector<double> NZJSigma8TeV,
      vector<double> NggZZ7TeV,      vector<double> NggZZ8TeV,
      vector<double> NggZZSigma7TeV, vector<double> NggZZSigma8TeV,
      double Mu);
   ~FitConfiguration();
   void SetFloats(string FloatAs, string FloatPhases,
      string FloatCounts7TeV, string FloatCounts8TeV,
      string FloatFractions7TeV, string FloatFractions8TeV, string FloatNs, string FloatRate);
   void SetFloatAs(string FloatAs);
   void SetFloatPhases(string FloatPhases);
   void SetFloatCounts(bool Is7TeV, string FloatCounts);
   void SetFloatFractions(bool Is7TeV, string FloatFractions);
   void SetFloatNs(string FloatNs);
   void SetFloatMu(string FloatRate);
   void SetInitialRatios(const vector<double> Ratios);
   void SetInitialPhases(const vector<double> Phases);
   void SetInitialCounts(bool Is7TeV, const vector<double> Counts);
   void SetInitialFractions(bool Is7TeV, const vector<double> Fractions);
   void SetInitialNs(const vector<double> Ns);
   void SetInitialMu(const double Mu);
   void SetNSConstrain(bool Is7TeV, const vector<double> NS, const vector<double> NSSigma);
   void SetNBConstrain(bool Is7TeV, const vector<double> NB, const vector<double> NBSigma);
   void SetNZJConstrain(bool Is7TeV, const vector<double> NZJ, const vector<double> NZJSigma);
   void SetNggZZConstrain(bool Is7TeV, const vector<double> NggZZ, const vector<double> NggZZSigma);
   int TotalNumberOfFloats();
};

struct FitResultSummary
{
public:
   double AA[8], AAError[8];
   double Phase[8], PhaseError[8];
   double Count[2][4], CountError[2][4];
   double F[2][4], FError[2][4];
   double FZJ[2][4], FZJError[2][4];
   double FggZZ[2][4], FggZZError[2][4];
   double N[7], NError[7];
   double EDM;
   double S[2][4], B[2][4], ZJ[2][4], ggZZ[2][4];
   double TruthNLL, BestNLL;
   double Mu, MuError;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   std::vector<double> V[154][13];   // Background = 0, Signal = 1-153; second index = CUDWNHSFCABCD
   std::vector<double> I[154][13];   // same as above
   std::vector<double> V2[2][13];   // Z+J = 0, ggZZ = 1; second index the same as above
   std::vector<double> I2[2][13];
   std::vector<EventParameters> E;
   std::vector<std::string> S;
   std::vector<std::string> Energy;
   int SignalStateCount[2][4];
   int BackgroundStateCount[2][4];
   int ZJStateCount[2][4];
   int ggZZStateCount[2][4];
public:
   double NSConstrainMu[2][4], NSConstrainSigma[2][4];
   double NBConstrainMu[2][4], NBConstrainSigma[2][4];
   double NZJConstrainMu[2][4], NZJConstrainSigma[2][4];
   double NggZZConstrainMu[2][4], NggZZConstrainSigma[2][4];
   double EventCount[2][4];
   double GetLogNormalMu(double Mean, double RelativeError);
   double GetLogNormalSigma(double Mean, double RelativeError);
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(SingleEvent &event);
   void AddPoint(double v[154][13], double i[154][13], double v2[2][13], double i2[2][13],
      EventParameters &Event, std::string State, std::string SqrtS);
   void ClearPoints();

   FitResultSummary DoFit(FitConfiguration configuration = FitConfiguration());

   void PlotResult(PsFileHelper *PsFile, FitResultSummary Result);
};

struct SingleEvent
{
public:
   double v[154][13];
   double i[154][13];
   double v2[2][13];
   double i2[2][13];
   std::string state;
   EventParameters event;
   std::string energy;
   double weight;
   int ToyNumber;
};

#endif


