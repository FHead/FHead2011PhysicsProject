#include <vector>
#include <string>

#include "PlotHelper2Forward.h"
#include "AngleConversion.h"
#include "EFTBases.h"

#define BASIS_AVV 0
#define BASIS_HIGGS 1
#define BASIS_WARSAW 2
#define BASIS_LOOP 3

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
   int Basis;
   bool FloatParameter1;  double Parameter1InitialValue;
   bool FloatParameter2;  double Parameter2InitialValue;
   bool FloatParameter3;  double Parameter3InitialValue;
   bool FloatParameter4;  double Parameter4InitialValue;
   bool FloatParameter5;  double Parameter5InitialValue;
   bool FloatParameter6;  double Parameter6InitialValue;
   bool FloatParameter7;  double Parameter7InitialValue;
   bool FloatParameter8;  double Parameter8InitialValue;
   bool FloatFem;         double FemInitialValue;
   bool FloatFme;         double FmeInitialValue;
   bool FloatFee;         double FeeInitialValue;
   bool FloatFmm;         double FmmInitialValue;
   bool UsePriors[20];
   bool NoSquareMode;
public:
   FitConfiguration();
   FitConfiguration(string FloatAs, string FloatFractions, string Priors);
   FitConfiguration(string FloatAs, string FloatFractions,
      vector<double> Ratios, vector<double> Fractions, bool Mode, int BasisChoice, string Priors);
   ~FitConfiguration();
   FitConfiguration &operator =(const FitConfiguration &other);
   void SetFloats(string FloatAs, string FloatFractions);
   void SetFloatAs(string FloatAs);
   void SetFloatFractions(string FloatFractions);
   void SetUsePriors(string Priors);
   void SetInitialRatios(const vector<double> Ratios);
   void SetInitialFractions(const vector<double> Fractions);
   void SetNoSquareMode(bool Decision);
   void SetBasis(int Decision);
   int TotalNumberOfFloats();
};

struct FitResultSummary
{
public:
   int Basis;
   double Parameter1, Parameter1Error;
   double Parameter2, Parameter2Error;
   double Parameter3, Parameter3Error;
   double Parameter4, Parameter4Error;
   double Parameter5, Parameter5Error;
   double Parameter6, Parameter6Error;
   double Parameter7, Parameter7Error;
   double Parameter8, Parameter8Error;
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
   bool NoSquareMode;
   bool UsedPriors[20];
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
   double *VSCopy[16][16];
   double *ISCopy[16][16];
   std::vector<EventParameters> E;
   std::vector<std::string> S;
   int SignalStateCount[4];
   int BackgroundStateCount[4];
   bool NoSquareMode;
   bool UsePriors[20];
   int Basis;
   bool AVVEFTMode;
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




