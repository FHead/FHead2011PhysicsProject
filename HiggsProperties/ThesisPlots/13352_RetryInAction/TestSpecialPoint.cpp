#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

#include "Code/TauHelperFunctions2.h"
#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateME.h"
#include "MEFunctions.h"

#include "LeptonResponse.h"
#include "HybridCalculator.h"
#include "PTYFunctions.h"

int main(int argc, char *argv[])
{
   // Setup calculator
   HybridCalculator Calculator;

   Calculator.SetEfficiency12(GetElectronEfficiencyPtEta);
   Calculator.SetEfficiency34(GetMuonEfficiencyPtEta);
   Calculator.SetSmear12(SmearElectronCentral);
   Calculator.SetSmear34(SmearMuonCentral);
   Calculator.SetToleranceF(1e-10);
   Calculator.SetMaxDepthF(30);
   Calculator.SetExpansionOrder(2);
   Calculator.SetDoDeltaMH(true, 125);
   Calculator.SetIgnorePhi(true);
   Calculator.SetIntegralCRange(0.75, 1.25);
   Calculator.SetPTYDensity(ToyPTYDensity);
   Calculator.SetAttractorStrength(true, 2);
   Calculator.SetIntegralCStep(20);
   Calculator.SetSimpleMassIntegralStep(200);
   Calculator.SetSimpleMassIntegralWindow(30);
   Calculator.SetDoDiagonal(true);
   Calculator.SetFlatApproximation(false);
   Calculator.SetIncludeSwapping(true);
   Calculator.SetUseSmartCenter(true);
   Calculator.SetDoReboot(true);

   Calculator.SetMECalculator(CalculateA1RA1RSignal2e2mu);

   // CalculatePoint
   double MaxEstimate = 1;

   LeptonVectors Leptons;
   Leptons.Lepton11.SetPtEtaPhi(44.209379, 2.3134395, 3.1007234);
   Leptons.Lepton12.SetPtEtaPhi(22.083182, 0.4241077, -0.063093);
   Leptons.Lepton21.SetPtEtaPhi(12.686774, 1.3928545, 0.6985075);
   Leptons.Lepton22.SetPtEtaPhi(17.727226, 2.2251508, 1.8439758);

   EventParameters Point = ConvertVectorsToAnglesRoberto(Leptons);

   cerr << Point << endl;

   Calculator.PrintSettings(cerr);

   Calculator.SetDebugPrintIntegrand(true);
   
   cout << Calculator.SimpleMassIntegral(Point)[0] << endl;
   
   Calculator.SetDoDiagonal(false);
   cout << Calculator.SimpleMassIntegral(Point)[0] << endl;

   return 0;
}


