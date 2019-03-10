#ifndef ReducedLikelihood_h_16225
#define ReducedLikelihood_h_16225

#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"

#include "AngleConversion.h"
#include "EFTBases.h"
#include "Cuts.h"
#include "Lists.h"
#include "FunctionLists.h"
#include "CalculateME.h"
#include "MEFunctions.h"

#include "HybridCalculatorWithZPrime.h"
#include "PTYFunctions.h"
#include "LeptonResponse.h"

namespace RealLikelihood
{
   class Likelihood;

   class Likelihood
   {
   public:
      double VS[16][16];
      double IS[16][16];
      double VB;
      double IB;
   public:
      ZPrimeParameters ZP;
      HybridCalculator CalculatorEE, CalculatorEM, CalculatorME, CalculatorMM;
   public:
      Likelihood();
      Likelihood(const Likelihood &L);
      Likelihood &operator =(const Likelihood &L);
      void InitializeLikelihoodCalculation();
      double Apply(FullAVVBasis &A, double F) const;
      void SetBranchAddress(TTree *T);
      void SetIS(double is[72][72]);
      void SetIB(double ib);
      void CalculateLikelihood(LeptonVectors &L, int L1ID, int L3ID);
   };
}


#endif




