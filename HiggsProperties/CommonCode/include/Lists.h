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
#include "Code/TauHelperFunctions2.h"
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
#endif
