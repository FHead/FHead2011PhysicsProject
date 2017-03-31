//---------------------------------------------------------------------------
#ifndef FUNCTIONLISTS_H_16225_ASKDGJAKSDJGKASJGKSADJ
#define FUNCTIONLISTS_H_16225_ASKDGJAKSDJGKASJGKSADJ
//---------------------------------------------------------------------------
#include <vector>
#include <string>
using namespace std;
//---------------------------------------------------------------------------
#include "AngleConversion.h"
#include "CalculateME.h"
//---------------------------------------------------------------------------
#include "Code/TauHelperFunctions3.h"
//---------------------------------------------------------------------------
typedef vector<vector<double (*)(LeptonVectors &)> > MEArray;
MEArray GetHEFTFunctionListEM();
MEArray GetHEFTFunctionListEE();
MEArray GetHEFTFunctionListEM_ZAAZSeparate();
MEArray GetHEFTFunctionListEE_ZAAZSeparate();
//---------------------------------------------------------------------------
typedef vector<vector<double (*)(LeptonVectors &, ZPrimeParameters &)> > MEArrayZPrime;
MEArrayZPrime GetSpin0XVVFunctionListEM();
MEArrayZPrime GetSpin0XVVFunctionListEE();
//---------------------------------------------------------------------------
#endif
