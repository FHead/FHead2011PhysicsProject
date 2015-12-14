#include <vector>
#include <string>

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
   double A2A1, A2A1Error;
   double A2Phase, A2PhaseError;
   double A3A1, A3A1Error;
   double A3Phase, A3PhaseError;
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
   std::vector<double> V[16][5];   // Background = 0, Signal = 1-15; second index = CUDWN
   std::vector<double> I[16][5];   // same as above
   std::vector<EventParameters> E;
   std::vector<std::string> S;
   int SignalStateCount[4];
   int BackgroundStateCount[4];
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(SingleEvent &event);
   void AddPoint(double v[16][5], double I[16][5], EventParameters &Event, std::string State);
   void ClearPoints();

   FitResultSummary DoFit(int Mode = FITMODE_SIGNALONLY, double v1 = 0, double v2 = 0);
};

struct SingleEvent
{
public:
   double v[16][5];
   double i[16][5];
   std::string state;
   EventParameters event;
};




