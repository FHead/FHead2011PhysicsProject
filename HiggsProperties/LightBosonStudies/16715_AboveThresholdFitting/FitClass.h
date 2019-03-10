#include <iostream>
#include <vector>
using namespace std;

#include "Likelihood.h"
#include "ReducedLikelihood.h"

using namespace RealLikelihood;
// using namespace FullLikelihood;

class FitClass;
class FitConfiguration;
class FitResult;

class FitClass
{
public:
   vector<const Likelihood *> EventsEM;
   vector<const Likelihood *> EventsEE;
public:
   FitClass();
   double Evaluate(const double *Parameters);
   void AddPoint(const Likelihood &NewPoint, bool IsEM);
   FitResult DoFit(const FitConfiguration &Configuration);
};

class FitConfiguration
{
public:
   double FEM;   bool FloatFEM;
   double FEE;   bool FloatFEE;
   double AVV[48];   bool FloatAVV[48];
public:
   FitConfiguration();
   FitConfiguration(FullAVVBasis &A);
   void SetAVV(FullAVVBasis &A);
   int NumberOfFloats() const;
};

class FitResult
{
public:
   double FEM, FEMError;
   double FEE, FEEError;
   FullAVVBasis AVV, AVVError;
   double TruthLL;
   double BestLL;
   double EDM;
   int FitStatus;
};





