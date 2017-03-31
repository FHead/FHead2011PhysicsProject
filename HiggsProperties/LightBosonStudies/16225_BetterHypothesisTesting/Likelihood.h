#ifndef Likelihood_h_16225
#define Likelihood_h_16225

#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"

#include "AngleConversion.h"
#include "EFTBases.h"
#include "Cuts.h"
#include "Lists.h"

class Likelihood;

class Likelihood
{
public:
   double VS[72][72];
   double IS[72][72];
   double VB;
   double IB;
public:
   Likelihood();
   Likelihood(const Likelihood &L);
   Likelihood &operator =(const Likelihood &L);
   double Apply(FullAVVBasis &A, double F);
   void SetBranchAddress(TTree *T);
};


#endif




