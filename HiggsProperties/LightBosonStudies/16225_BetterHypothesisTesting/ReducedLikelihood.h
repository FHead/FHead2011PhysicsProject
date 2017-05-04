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

namespace RealLikelihood
{
   class Likelihood;

   class Likelihood
   {
   public:
      double VS[36][36];
      double IS[36][36];
      double VB;
      double IB;
   public:
      Likelihood();
      Likelihood(const Likelihood &L);
      Likelihood &operator =(const Likelihood &L);
      double Apply(FullAVVBasis &A, double F) const;
      void SetBranchAddress(TTree *T);
   };
}


#endif




