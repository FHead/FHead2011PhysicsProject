#ifndef YIELDFRACTION_H_13234_AJSDKGJASKDGJKASDGJ
#define YIELDFRACTION_H_13234_AJSDKGJASKDGJKASDGJ

#include <cmath>
using namespace std;

#include "DataHelperFwd.h"

double GetYieldFractionA1ZZA2ZZ(double A1ZZ, double A2ZZR, double A2ZZI, bool Is7TeV, int FinalState);
double GetYieldFractionA1ZZA2ZZReal(double A1ZZ, double A2ZZR, bool Is7TeV, int FinalState);
double GetYieldFractionA1ZZA3ZZ(double A1ZZ, double A3ZZR, double A3ZZI, bool Is7TeV, int FinalState);
double GetNormalizationYieldFraction(double A1ZZR, double A2ZZR, double A2ZZI,
   double A3ZZR, double A3ZZI, bool Is7TeV, int FinalState);

#endif




