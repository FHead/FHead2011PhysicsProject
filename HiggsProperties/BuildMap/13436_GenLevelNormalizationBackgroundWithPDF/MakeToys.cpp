#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <deque>
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
#include "Cuts.h"

int main(int argc, char *argv[]);
double GiveMeZMass();
double GiveMeZWeight(double ZMass);
double GiveMeZ2Mass();
double GiveMeZ2Weight(double ZMass);
pair<double, double> GiveMePTY();
bool CheckIfGood(vector<double> Single);
void AddToVector(vector<double> &Total, vector<double> Single, double Weight);
void PrintResult(string Identifier, vector<double> Total, double Count);

int main(int argc, char *argv[])
{
   int RandomSeed = 31426;
   double HMass = 125;

   if(argc > 1)
      HMass = atof(argv[1]);

   if(argc > 2)
   {
      RandomSeed = atoi(argv[2]);
      cerr << "Using random seed = " << RandomSeed << endl;
      srand(RandomSeed);
   }
   else
      srand(time(NULL));

   // Setup calculator
   HybridCalculator CalculatorSEM, CalculatorSEE, CalculatorBEM, CalculatorBEE;

   CalculatorSEM.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorSEM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorSEM.SetSmear12(SmearElectronCentral);
   CalculatorSEM.SetSmear34(SmearMuonCentral);
   CalculatorSEM.SetToleranceF(1e-12);
   CalculatorSEM.SetMaxDepthF(30);
   CalculatorSEM.SetSimpleMassIntegralStep(180);
   CalculatorSEM.SetExpansionOrder(2);
   CalculatorSEM.SetDoDeltaMH(true, 125);
   CalculatorSEM.SetIgnorePhi(true);
   CalculatorSEM.SetApplyEfficiencyAtEnd(true);
   CalculatorSEM.SetIntegralCRange(0.75, 1.25);
   CalculatorSEM.SetPTYDensity(GetPTYDensityGG_MZ_CTEQ6l1_13432);
   CalculatorSEM.SetAttractorStrength(2);
   CalculatorSEM.SetIntegralCStep(20);
   CalculatorSEM.SetSimpleMassIntegralWindow(true, 30);
   CalculatorSEM.SetSimpleMassIntegralWindow(false, 40);
   CalculatorSEM.SetFlatApproximation(false);
   CalculatorSEM.SetIncludeSwapping(false);
   CalculatorSEM.SetIgnoreTip(false);
   CalculatorSEM.SetTipRangeFactor(0.05);
   CalculatorSEM.SetUseSmartCenter(true);

   CalculatorSEE = CalculatorSEM;
   CalculatorBEM = CalculatorSEM;
   CalculatorBEM.SetDoDeltaMH(false);
   CalculatorBEE = CalculatorBEM;

   CalculatorBEM.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_13432);
   CalculatorBEE.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_13432);

   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA1ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA2ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA2ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA3ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZIA3ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZARA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZAIA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZARA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZAIA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2AARA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2AAIA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3AARA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3AAIA3AAISignal2e2mu);

   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA2ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA2ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA3ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA3ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA2ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA3ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA3ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZRA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA3ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA3ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZZIA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA3ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZRA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZIA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZIA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZIA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZIA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZIA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZIA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZIA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZZIA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZARA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZARA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZARA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZARA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZARA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZARA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZARA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZAIA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZAIA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZAIA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZAIA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZAIA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2ZAIA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZARA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZARA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZARA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZARA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZARA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZAIA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZAIA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZAIA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3ZAIA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2AARA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2AARA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2AARA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2AAIA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA2AAIA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA3AARA3AAISignal2e2mu);
   //
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA1L1ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA1L1ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA1LQZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA1LQZZISignal2e2mu);
   //
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA1L1ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA2ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA2ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA3ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA3ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA3AAISignal2e2mu);
   //
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA1L1ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA2ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA2ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA3ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA3ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA1L1ZZISignal2e2mu);
   //
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA1LQZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA2ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA2ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA3ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA3ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA1LQZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA1LQZZRSignal2e2mu);
   //
   // CalculatorSEM.SetMECalculator(CalculateA1ZZRA1LQZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA2ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA2ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA3ZZRSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA3ZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA2ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA2ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA3ZARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA3ZAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA2AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA2AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA3AARSignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZIA3AAISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZRA1LQZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1L1ZZIA1LQZZISignal2e2mu);
   // CalculatorSEM.SetMECalculator(CalculateA1LQZZRA1LQZZISignal2e2mu);

   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA1ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA2ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA2ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA3ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZIA3ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZARA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZAIA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZARA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZAIA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2AARA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2AAIA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3AARA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3AAIA3AAISignal4e);

   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA2ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA2ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA3ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA3ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA2ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA3ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA3ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZRA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA3ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA3ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZZIA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA3ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZRA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZIA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZIA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZIA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZIA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZIA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZIA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZIA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZZIA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZARA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZARA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZARA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZARA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZARA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZARA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZARA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZAIA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZAIA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZAIA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZAIA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZAIA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2ZAIA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZARA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZARA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZARA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZARA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZARA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZAIA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZAIA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZAIA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3ZAIA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2AARA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2AARA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2AARA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2AAIA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA2AAIA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA3AARA3AAISignal4e);

   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA1L1ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA1L1ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA1LQZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA1LQZZISignal4e);
   //
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA1L1ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA2ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA2ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA3ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA3ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA3AAISignal4e);
   //
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA1L1ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA2ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA2ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA3ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA3ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA1L1ZZISignal4e);
   //
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA1LQZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA2ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA2ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA3ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA3ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA1LQZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA1LQZZRSignal4e);
   //
   // CalculatorSEE.SetMECalculator(CalculateA1ZZRA1LQZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA2ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA2ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA3ZZRSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA3ZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA2ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA2ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA3ZARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA3ZAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA2AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA2AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA3AARSignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZIA3AAISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZRA1LQZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1L1ZZIA1LQZZISignal4e);
   // CalculatorSEE.SetMECalculator(CalculateA1LQZZRA1LQZZISignal4e);

   CalculatorBEM.SetMECalculator(CalculateDDbarBackground2e2muDirectional);
   CalculatorBEE.SetMECalculator(CalculateDDbarBackground4eDirectional);

   // vectors to hold totals
   vector<double> TotalSEM[11], TotalSEE[11];
   vector<double> TotalBEM[11], TotalBEE[11];
   double ActualEventCount = 0;

   // Start looping
   double MaxEstimate = 1;
   int EventCount = 5000000;
   EventParameters Angles;

   ProgressBar Bar(cerr, EventCount);
   Bar.SetStyle(1);

   deque<EventParameters> EventQueue;

   for(int iEvent = 0; iEvent < EventCount; iEvent++)
   {
      if(EventCount <= 300 || iEvent % (EventCount / 300) == 0)
      {
         Bar.Update(iEvent);
         Bar.Print();
      }

      if(iEvent % 8 == 0)
      {
         Angles.HMass = HMass;
         Angles.Phi0 = DrawRandom(-PI, PI);
         Angles.Theta0 = acos(DrawRandom(-1, 1));
         Angles.Phi = DrawRandom(-PI, PI);
         Angles.Theta1 = acos(DrawRandom(-1, 1));
         Angles.Theta2 = acos(DrawRandom(-1, 1));
         Angles.PhiOffset = DrawRandom(-PI, PI);
         Angles.PhiH = DrawRandom(-PI, PI);
         Angles.PTH = 0;
         Angles.YH = DrawRandom(-4, 4);

         do
         {
            Angles.HMass = DrawRandom(115, 135);
            Angles.ZMass = GiveMeZMass();
            Angles.Z2Mass = GiveMeZ2Mass();
         } while(Angles.ZMass + Angles.Z2Mass > Angles.HMass);
      }
      else if(iEvent % 2 == 1)
         Angles.Phi = Angles.Phi + PI;
      else if(iEvent % 4 == 2)
         Angles.Theta1 = PI - Angles.Theta1;
      else
         Angles.Theta2 = PI - Angles.Theta2;

      // cout << Angles << endl;

      // double PTYWeight = ToyPTYDensity(Angles.PTH, Angles.YH);
      double PTYWeight = 1;
      double Weight = 1 / MaxEstimate / GiveMeZWeight(Angles.ZMass) / GiveMeZ2Weight(Angles.Z2Mass) / PTYWeight;
      Weight = Weight * Angles.ZMass * Angles.HMass * Angles.Z2Mass;

      vector<double> IntegralSEM, IntegralSEE;
      vector<double> IntegralBEM, IntegralBEE;

      LeptonVectors LeptonsEM = ConvertAnglesToVectorsRoberto(Angles).ReorderLeptons2e2mu();
      LeptonVectors LeptonsEE = LeptonsEM.ReorderLeptons4e();

      vector<bool> PassEM = PassPairingCuts(LeptonsEM);
      vector<bool> PassEE = PassPairingCuts(LeptonsEE);

      // IntegralSEM = CalculatorSEM.PassThroughMode(Angles);
      // IntegralSEE = CalculatorSEE.PassThroughMode(Angles);
      IntegralBEM = CalculatorBEM.PassThroughMode(Angles);
      IntegralBEE = CalculatorBEE.PassThroughMode(Angles);

      ActualEventCount = ActualEventCount + Weight;

      // for(int i = 0; i < 10; i++)
      //    AddToVector(TotalSEM[i], IntegralSEM, Weight * PassEM[i]);
      // for(int i = 0; i < 10; i++)
      //    AddToVector(TotalSEE[i], IntegralSEE, Weight * PassEE[i]);
      for(int i = 0; i < 11; i++)
         AddToVector(TotalBEM[i], IntegralBEM, Weight * PassEM[i]);
      for(int i = 0; i < 11; i++)
         AddToVector(TotalBEE[i], IntegralBEE, Weight * PassEE[i]);
   }

   for(int i = 0; i < 11; i++)
   {
      // string SEMString = "TA1";   SEMString[1] = 'A' + i;
      // string SEEString = "VA1";   SEEString[1] = 'A' + i;
      string BEMString = "TA2";   BEMString[1] = 'A' + i;
      string BEEString = "VA2";   BEEString[1] = 'A' + i;

      // PrintResult(SEMString, TotalSEM[i], ActualEventCount);
      // PrintResult(SEEString, TotalSEE[i], ActualEventCount);
      PrintResult(BEMString, TotalBEM[i], ActualEventCount);
      PrintResult(BEEString, TotalBEE[i], ActualEventCount);
   }

   Bar.Update(EventCount);
   Bar.Print();
   Bar.PrintLine();

   return 0;
}

double GiveMeZMass()
{
   double Value;
   bool Accepted = false;

   while(Accepted == false)
   {
      Value = DrawRandom(4, 120);
      if(DrawRandom(0, 1) < GiveMeZWeight(Value))
         Accepted = true;
   }

   return Value;
}

double GiveMeZWeight(double ZMass)
{
   return 0.1 + 0.9 * exp(-(ZMass - 90) * (ZMass - 90) / (2 * 3 * 3));
}

double GiveMeZ2Mass()
{
   double Value;
   bool Accepted = false;

   while(Accepted == false)
   {
      Value = DrawRandom(4, 120);
      if(DrawRandom(0, 1) < GiveMeZ2Weight(Value))
         Accepted = true;
   }

   return Value;
}

double GiveMeZ2Weight(double Z2Mass)
{
   return 0.3 + 0.7 * exp(-(Z2Mass - 30) * (Z2Mass - 30) / (2 * 20 * 20));
}

bool CheckIfGood(vector<double> Single)
{
   return true;

   for(int i = 0; i < (int)Single.size(); i++)
      if(Single[i] != Single[i])
         return false;
   return true;
}

void AddToVector(vector<double> &Total, vector<double> Single, double Weight)
{
   if(Single.size() > Total.size())
      Total.resize(Single.size());

   for(int i = 0; i < (int)Single.size(); i++)
      Total[i] = Total[i] + Single[i] * Weight;
}

void PrintResult(string Identifier, vector<double> Total, double Count)
{
   cout << setprecision(20) << Identifier << " " << Count;
   for(int i = 0; i < (int)Total.size(); i++)
      cout << setprecision(20) << " " << Total[i] / Count;
   cout << endl;
}

   








