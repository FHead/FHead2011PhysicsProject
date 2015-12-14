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
   bool FloatEQEL;        double EQELInitialValue;
   bool FloatGLEL;        double GLELInitialValue;
   bool FloatGRGL;        double GRGLInitialValue;
   bool FloatGQLGL;       double GQLGLInitialValue;
   bool FloatGQRGQL;      double GQRGQLInitialValue;
public:
   FitConfiguration();
   FitConfiguration(string FloatGs);
   FitConfiguration(string FloatGs, vector<double> Ratios);
   ~FitConfiguration();
   void SetFloats(string FloatGs);
   void SetFloatGs(string FloatGs);
   void SetInitialRatios(const vector<double> Ratios);
   int TotalNumberOfFloats();
};

struct FitResultSummary
{
public:
   double EQEL, EQELError;
   double GLEL, GLELError;
   double GRGL, GRGLError;
   double GQLGL, GQLGLError;
   double GQRGQL, GQRGQLError;
   double EDM;
   double Sem, Sme, See, Smm;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   std::vector<double> V[214];
   std::vector<double> I[214];
   std::vector<EventParameters> E;
   std::vector<std::string> S;
   int SignalStateCount[4];
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(SingleEvent &event);
   void AddPoint(double v[214], double I[214], EventParameters &Event, std::string State);
   void ClearPoints();

   FitResultSummary DoFit(FitConfiguration configuration = FitConfiguration());
};

struct SingleEvent
{
public:
   double v[214];
   double i[214];
   std::string state;
   EventParameters event;
};




