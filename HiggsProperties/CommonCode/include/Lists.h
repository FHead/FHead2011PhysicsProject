//---------------------------------------------------------------------------
#ifndef LISTS_H_12665_ASKDGJAKSDJGKASJGKSADJ
#define LISTS_H_12665_ASKDGJAKSDJGKASJGKSADJ
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
vector<string> GetHLLSignalSuffixList();
vector<string> GetVffSignalSuffixList();
vector<string> GetHLLZASignalSuffixList();
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
vector<string> GetXVVSignalSuffixList();
//---------------------------------------------------------------------------
#endif
