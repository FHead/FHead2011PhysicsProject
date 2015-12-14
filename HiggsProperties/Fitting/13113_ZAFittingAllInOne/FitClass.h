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
public:
   FitConfiguration();
   FitConfiguration(string FloatPhis, string FloatPhases);
   FitConfiguration(string FloatPhis, string FloatPhases,
      vector<double> Phis, vector<double> Phases);
   ~FitConfiguration();
   void SetFloats(string FloatPhis, string FloatPhases);
   void SetFloatPhis(string FloatPhis);
   void SetFloatPhases(string FloatPhases);
   void SetInitialPhis(const vector<double> Phis);
   void SetInitialPhases(const vector<double> Phases);
   int TotalNumberOfFloats();
};

struct FitResultSummary
{
public:
   double Phi[3], PhiError[3];
   double Phase[4], PhaseError[4];
   double EDM;
   double TruthNLL, BestNLL;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   std::vector<double> V[36];
   std::vector<double> I[36];
   std::vector<ZAEventParameters> E;
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(SingleEvent &event);
   void AddPoint(double v[36], double I[36], ZAEventParameters &Event);
   void ClearPoints();

   FitResultSummary DoFit(FitConfiguration configuration = FitConfiguration());
};

struct SingleEvent
{
public:
   double v[36];
   double i[36];
   ZAEventParameters event;
};




