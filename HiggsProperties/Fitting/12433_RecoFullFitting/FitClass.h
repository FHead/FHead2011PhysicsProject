#include <vector>
#include <string>

#include "PlotHelper2Forward.h"
#include "AngleConversion.h"

#define FITMODE_ALL 0
#define FITMODE_SIGNALONLY 1
#define FITMODE_PHASEONLY 2

struct FitResultSummary;
class FitClass;
struct SingleEvent;

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
   double N1, N1Error;
   double N2, N2Error;
   double EDM;
   double Sem, Bem;
   double Sme, Bme;
   double See, Bee;
   double Smm, Bmm;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   std::vector<double> V[92][5];   // Background = 0, Signal = 1-15; second index = CUDWN
   std::vector<double> I[92][5];   // same as above
   std::vector<EventParameters> E;
   std::vector<std::string> S;
   int SignalStateCount[4];
   int BackgroundStateCount[4];
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(SingleEvent &event);
   void AddPoint(double v[92][5], double I[92][5], EventParameters &Event, std::string State);
   void ClearPoints();

   FitResultSummary DoFit(int Mode = FITMODE_SIGNALONLY, double v1 = 0, double v2 = 0);

   void PlotResult(PsFileHelper *PsFile, FitResultSummary Result);
};

struct SingleEvent
{
public:
   double v[92][5];
   double i[92][5];
   std::string state;
   EventParameters event;
};




