//---------------------------------------------------------------------------
#ifndef CALCULATEZAME_H_11251_ASGKAJSGKDJASKDGJASKDJGASGD
#define CALCULATEZAME_H_11251_ASGKAJSGKDJASKDGJASKDJGASGD
//---------------------------------------------------------------------------
// CalculateZAME, copy-paste expression from Roberto Mega-Vorales and compile into code
//---------------------------------------------------------------------------
#include <complex>
#include <string>
//---------------------------------------------------------------------------
#include "AngleConversion.h"
//---------------------------------------------------------------------------
// Part 1
double GetToy1ZAME(ZALeptonVectors &Leptons);
//---------------------------------------------------------------------------
// Part 2
double GetSpin0ZAME(ZALeptonVectors &Leptons, GeneralScalarParameters &parameters);
double GetSpin0ZAME(ZAEventParameters &Event, GeneralScalarParameters &parameters);
double GetSpin0ZAME_M1Only(ZAEventParameters &Event, GeneralScalarParameters &parameters);
double GetqqZAMEWrong(ZALeptonVectors &Leptons, bool Reverse, bool UpType);
double GetqqZAME(ZALeptonVectors &Leptons, bool Reverse, bool UpType);
double GetqqZAME_S(ZALeptonVectors &Leptons, bool Reverse, bool UpType);
double GetqqZAME_TU(ZALeptonVectors &Leptons, bool Reverse, bool UpType);
double GetqqZAME_S_TU_Interference(ZALeptonVectors &Leptons, bool Reverse, bool UpType);
//---------------------------------------------------------------------------
#endif

