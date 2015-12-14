#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Code/TauHelperFunctions2.h"
#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateME.h"
#include "MEFunctions.h"

#include "LeptonResponse.h"
#include "HybridCalculator.h"
#include "PTYFunctions.h"

int main(int argc, char *argv[]);
bool CheckIfGood(vector<double> Single);
void AddToVector(vector<double> &Total, vector<double> Single, double Weight);
void PrintResult(string Identifier, vector<double> Total, int Count);
bool PassBaselineCut(EventParameters &Event);

int main(int argc, char *argv[])
{
   string FileName = "EventB.root";
   int StartEvent = 0;
   int EndEvent = 19;
   int Branch = 0;
   int FlavorTreatment = 0;

   if(argc <= 5)
   {
      cerr << "Usage: " << argv[0] << " FileWithTree StartEvent EndEvent Branch FlavorTreatment" << endl;
      cerr << "Flavor treatment: 1 = em, 2 = me, 3 = ee, 4 = mm, others = from tree" << endl;
      return -1;
   }

   FileName = argv[1];
   StartEvent = atoi(argv[2]);
   EndEvent = atoi(argv[3]);
   Branch = atoi(argv[4]);
   FlavorTreatment = atoi(argv[5]);

   // Setup calculators
   HybridCalculator CalculatorEE, CalculatorME, CalculatorEM, CalculatorMM;

   CalculatorEM.SetEfficiency12(GetElectronEfficiencyPtEta7TeV);
   CalculatorEM.SetEfficiency34(GetMuonEfficiencyPtEta7TeV);
   CalculatorEM.SetSmear12(SmearElectronCentral7TeV);
   CalculatorEM.SetSmear34(SmearMuonCentral7TeV);
   CalculatorEM.SetToleranceF(1e-12);
   CalculatorEM.SetMaxDepthF(30);
   CalculatorEM.SetSimpleMassIntegralStep(80);
   CalculatorEM.SetExpansionOrder(0);
   CalculatorEM.SetDoDeltaMH(true, 125.6);
   CalculatorEM.SetIgnorePhi(true);
   CalculatorEM.SetApplyEfficiencyAtEnd(true);
   CalculatorEM.SetIntegralCRange(0.25, 1.75);
   CalculatorEM.SetPTYDensity(GetPTYDensity7TeVSignal);
   CalculatorEM.SetAttractorStrength(true, 2);
   CalculatorEM.SetAttractorStrength(false, 0.5);
   CalculatorEM.SetIntegralCStep(20);
   CalculatorEM.SetSimpleMassIntegralWindow(true, 30);
   CalculatorEM.SetSimpleMassIntegralWindow(false, 40);
   CalculatorEM.SetFlatApproximation(false);
   CalculatorEM.SetIncludeSwapping(true);
   CalculatorEM.SetIgnoreTip(false);
   CalculatorEM.SetTipRangeFactor(0.05);
   CalculatorEM.SetUseSmartCenter(true);
   CalculatorEM.SetDoReboot(true);
   CalculatorEM.SetDoDiagonal(true);
   CalculatorEM.SetUseSignalAverageExpansionPoint(true);
   CalculatorEM.SetUseBigRangeDerivatives(true);
   CalculatorEM.SetUseSignalMESpline(false);

   CalculatorEM.SetMECalculator(CalculateA1ZZRA1ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA2ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA2ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA3ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZIA3ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZARA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZAIA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZARA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZAIA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2AARA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2AAIA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3AARA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3AAIA3AAISignal2e2mu);

   CalculatorEM.SetMECalculator(CalculateA1ZZRA2ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA2ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA3ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA3ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1ZZRA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA2ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA3ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA3ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZRA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA3ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA3ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZZIA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA3ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZRA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZIA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZIA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZIA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZIA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZIA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZIA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZIA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZZIA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZARA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZARA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZARA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZARA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZARA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZARA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZARA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZAIA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZAIA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZAIA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZAIA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZAIA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2ZAIA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZARA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZARA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZARA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZARA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZARA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZAIA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZAIA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZAIA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3ZAIA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2AARA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2AARA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2AARA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2AAIA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2AAIA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3AARA3AAISignal2e2mu);

   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA1L1ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA1L1ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA1LQZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA1LQZZISignal2e2mu);
   
   CalculatorEM.SetMECalculator(CalculateA1ZZRA1L1ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA2ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA2ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA3ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA3ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA3AAISignal2e2mu);
   
   CalculatorEM.SetMECalculator(CalculateA1ZZRA1L1ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA2ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA2ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA3ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA3ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA1L1ZZISignal2e2mu);
   
   CalculatorEM.SetMECalculator(CalculateA1ZZRA1LQZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA2ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA2ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA3ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA3ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA1LQZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA1LQZZRSignal2e2mu);
   
   CalculatorEM.SetMECalculator(CalculateA1ZZRA1LQZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA2ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA2ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA3ZZRSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA3ZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA2ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA2ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA3ZARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA3ZAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA2AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA2AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA3AARSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZIA3AAISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZRA1LQZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1L1ZZIA1LQZZISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1LQZZRA1LQZZISignal2e2mu);

   CalculatorME = CalculatorEM;
   CalculatorME.SetEfficiency12(GetMuonEfficiencyPtEta7TeV);
   CalculatorME.SetEfficiency34(GetElectronEfficiencyPtEta7TeV);
   CalculatorME.SetSmear12(SmearMuonCentral7TeV);
   CalculatorME.SetSmear34(SmearElectronCentral7TeV);

   CalculatorEE.SetEfficiency12(GetElectronEfficiencyPtEta7TeV);
   CalculatorEE.SetEfficiency34(GetElectronEfficiencyPtEta7TeV);
   CalculatorEE.SetSmear12(SmearElectronCentral7TeV);
   CalculatorEE.SetSmear34(SmearElectronCentral7TeV);
   CalculatorEE.SetToleranceF(1e-12);
   CalculatorEE.SetMaxDepthF(30);
   CalculatorEE.SetSimpleMassIntegralStep(80);
   CalculatorEE.SetExpansionOrder(0);
   CalculatorEE.SetDoDeltaMH(true, 125.6);
   CalculatorEE.SetIgnorePhi(true);
   CalculatorEE.SetApplyEfficiencyAtEnd(true);
   CalculatorEE.SetIntegralCRange(0.25, 1.75);
   CalculatorEE.SetPTYDensity(GetPTYDensity7TeVSignal);
   CalculatorEE.SetAttractorStrength(true, 2);
   CalculatorEE.SetAttractorStrength(false, 0.5);
   CalculatorEE.SetIntegralCStep(20);
   CalculatorEE.SetSimpleMassIntegralWindow(true, 30);
   CalculatorEE.SetSimpleMassIntegralWindow(false, 40);
   CalculatorEE.SetFlatApproximation(false);
   CalculatorEE.SetIncludeSwapping(true);
   CalculatorEE.SetIgnoreTip(false);
   CalculatorEE.SetTipRangeFactor(0.05);
   CalculatorEE.SetUseSmartCenter(true);
   CalculatorEE.SetDoReboot(true);
   CalculatorEE.SetDoDiagonal(true);
   CalculatorEE.SetUseSignalAverageExpansionPoint(true);
   CalculatorEE.SetUseBigRangeDerivatives(true);
   CalculatorEE.SetUseSignalMESpline(false);

   CalculatorEE.SetMECalculator(CalculateA1ZZRA1ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA2ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA2ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA3ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZIA3ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZARA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZAIA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZARA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZAIA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2AARA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2AAIA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3AARA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3AAIA3AAISignal4e);

   CalculatorEE.SetMECalculator(CalculateA1ZZRA2ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA2ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA3ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA3ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1ZZRA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA2ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA3ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA3ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZRA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA3ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA3ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZZIA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA3ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZRA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZIA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZIA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZIA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZIA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZIA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZIA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZIA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZZIA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZARA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZARA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZARA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZARA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZARA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZARA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZARA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZAIA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZAIA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZAIA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZAIA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZAIA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2ZAIA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZARA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZARA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZARA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZARA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZARA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZAIA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZAIA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZAIA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3ZAIA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2AARA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2AARA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2AARA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2AAIA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2AAIA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3AARA3AAISignal4e);

   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA1L1ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA1L1ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA1LQZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA1LQZZISignal4e);
   
   CalculatorEE.SetMECalculator(CalculateA1ZZRA1L1ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA2ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA2ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA3ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA3ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA3AAISignal4e);
   
   CalculatorEE.SetMECalculator(CalculateA1ZZRA1L1ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA2ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA2ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA3ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA3ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA1L1ZZISignal4e);
   
   CalculatorEE.SetMECalculator(CalculateA1ZZRA1LQZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA2ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA2ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA3ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA3ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA1LQZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA1LQZZRSignal4e);
   
   CalculatorEE.SetMECalculator(CalculateA1ZZRA1LQZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA2ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA2ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA3ZZRSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA3ZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA2ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA2ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA3ZARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA3ZAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA2AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA2AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA3AARSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZIA3AAISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZRA1LQZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1L1ZZIA1LQZZISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1LQZZRA1LQZZISignal4e);


   CalculatorMM = CalculatorEE;
   CalculatorMM.SetEfficiency12(GetMuonEfficiencyPtEta7TeV);
   CalculatorMM.SetEfficiency34(GetMuonEfficiencyPtEta7TeV);
   CalculatorMM.SetSmear12(SmearMuonCentral7TeV);
   CalculatorMM.SetSmear34(SmearMuonCentral7TeV);

   HybridCalculator CalculatorUpEM, CalculatorUpME, CalculatorUpEE, CalculatorUpMM;
   HybridCalculator CalculatorDownEM, CalculatorDownME, CalculatorDownEE, CalculatorDownMM;
   HybridCalculator CalculatorWideEM, CalculatorWideME, CalculatorWideEE, CalculatorWideMM;
   HybridCalculator CalculatorNarrowEM, CalculatorNarrowME, CalculatorNarrowEE, CalculatorNarrowMM;
   HybridCalculator CalculatorHardEM, CalculatorHardME, CalculatorHardEE, CalculatorHardMM;
   HybridCalculator CalculatorSoftEM, CalculatorSoftME, CalculatorSoftEE, CalculatorSoftMM;
   HybridCalculator CalculatorCentralEM, CalculatorCentralME, CalculatorCentralEE, CalculatorCentralMM;
   HybridCalculator CalculatorForwardEM, CalculatorForwardME, CalculatorForwardEE, CalculatorForwardMM;
   HybridCalculator CalculatorHMassAEM, CalculatorHMassAME, CalculatorHMassAEE, CalculatorHMassAMM;
   HybridCalculator CalculatorHMassBEM, CalculatorHMassBME, CalculatorHMassBEE, CalculatorHMassBMM;
   HybridCalculator CalculatorHMassCEM, CalculatorHMassCME, CalculatorHMassCEE, CalculatorHMassCMM;
   HybridCalculator CalculatorHMassDEM, CalculatorHMassDME, CalculatorHMassDEE, CalculatorHMassDMM;

   CalculatorUpEM = CalculatorEM;                     CalculatorDownEM = CalculatorEM;
   CalculatorUpEM.SetSmear12(SmearElectronUp7TeV);    CalculatorDownEM.SetSmear12(SmearElectronDown7TeV);
   CalculatorUpEM.SetSmear34(SmearMuonUp7TeV);        CalculatorDownEM.SetSmear34(SmearMuonDown7TeV);
   CalculatorUpME = CalculatorME;                     CalculatorDownME = CalculatorME;
   CalculatorUpME.SetSmear12(SmearMuonUp7TeV);        CalculatorDownME.SetSmear12(SmearMuonDown7TeV);
   CalculatorUpME.SetSmear34(SmearElectronUp7TeV);    CalculatorDownME.SetSmear34(SmearElectronDown7TeV);
   CalculatorUpEE = CalculatorEE;                     CalculatorDownEE = CalculatorEE;
   CalculatorUpEE.SetSmear12(SmearElectronUp7TeV);    CalculatorDownEE.SetSmear12(SmearElectronDown7TeV);
   CalculatorUpEE.SetSmear34(SmearElectronUp7TeV);    CalculatorDownEE.SetSmear34(SmearElectronDown7TeV);
   CalculatorUpMM = CalculatorMM;                     CalculatorDownMM = CalculatorMM;
   CalculatorUpMM.SetSmear12(SmearMuonUp7TeV);        CalculatorDownMM.SetSmear12(SmearMuonDown7TeV);
   CalculatorUpMM.SetSmear34(SmearMuonUp7TeV);        CalculatorDownMM.SetSmear34(SmearMuonDown7TeV);

   CalculatorWideEM = CalculatorEM;                   CalculatorNarrowEM = CalculatorEM;
   CalculatorWideEM.SetSmear12(SmearElectronWide7TeV);CalculatorNarrowEM.SetSmear12(SmearElectronNarrow7TeV);
   CalculatorWideEM.SetSmear34(SmearMuonWide7TeV);    CalculatorNarrowEM.SetSmear34(SmearMuonNarrow7TeV);
   CalculatorWideME = CalculatorME;                   CalculatorNarrowME = CalculatorME;
   CalculatorWideME.SetSmear12(SmearMuonWide7TeV);    CalculatorNarrowME.SetSmear12(SmearMuonNarrow7TeV);
   CalculatorWideME.SetSmear34(SmearElectronWide7TeV);CalculatorNarrowME.SetSmear34(SmearElectronNarrow7TeV);
   CalculatorWideEE = CalculatorEE;                   CalculatorNarrowEE = CalculatorEE;
   CalculatorWideEE.SetSmear12(SmearElectronWide7TeV);CalculatorNarrowEE.SetSmear12(SmearElectronNarrow7TeV);
   CalculatorWideEE.SetSmear34(SmearElectronWide7TeV);CalculatorNarrowEE.SetSmear34(SmearElectronNarrow7TeV);
   CalculatorWideMM = CalculatorMM;                   CalculatorNarrowMM = CalculatorMM;
   CalculatorWideMM.SetSmear12(SmearMuonWide7TeV);    CalculatorNarrowMM.SetSmear12(SmearMuonNarrow7TeV);
   CalculatorWideMM.SetSmear34(SmearMuonWide7TeV);    CalculatorNarrowMM.SetSmear34(SmearMuonNarrow7TeV);

   CalculatorHardEM = CalculatorEM;      CalculatorHardEM.SetPTYDensity(GetPTYDensity7TeVSignalHard);
   CalculatorHardME = CalculatorME;      CalculatorHardME.SetPTYDensity(GetPTYDensity7TeVSignalHard);
   CalculatorHardEE = CalculatorEE;      CalculatorHardEE.SetPTYDensity(GetPTYDensity7TeVSignalHard);
   CalculatorHardMM = CalculatorMM;      CalculatorHardMM.SetPTYDensity(GetPTYDensity7TeVSignalHard);

   CalculatorSoftEM = CalculatorEM;      CalculatorSoftEM.SetPTYDensity(GetPTYDensity7TeVSignalSoft);
   CalculatorSoftME = CalculatorME;      CalculatorSoftME.SetPTYDensity(GetPTYDensity7TeVSignalSoft);
   CalculatorSoftEE = CalculatorEE;      CalculatorSoftEE.SetPTYDensity(GetPTYDensity7TeVSignalSoft);
   CalculatorSoftMM = CalculatorMM;      CalculatorSoftMM.SetPTYDensity(GetPTYDensity7TeVSignalSoft);
   
   CalculatorCentralEM = CalculatorEM;   CalculatorCentralEM.SetPTYDensity(GetPTYDensity7TeVSignalCentral);
   CalculatorCentralME = CalculatorME;   CalculatorCentralME.SetPTYDensity(GetPTYDensity7TeVSignalCentral);
   CalculatorCentralEE = CalculatorEE;   CalculatorCentralEE.SetPTYDensity(GetPTYDensity7TeVSignalCentral);
   CalculatorCentralMM = CalculatorMM;   CalculatorCentralMM.SetPTYDensity(GetPTYDensity7TeVSignalCentral);

   CalculatorForwardEM = CalculatorEM;   CalculatorForwardEM.SetPTYDensity(GetPTYDensity7TeVSignalForward);
   CalculatorForwardME = CalculatorME;   CalculatorForwardME.SetPTYDensity(GetPTYDensity7TeVSignalForward);
   CalculatorForwardEE = CalculatorEE;   CalculatorForwardEE.SetPTYDensity(GetPTYDensity7TeVSignalForward);
   CalculatorForwardMM = CalculatorMM;   CalculatorForwardMM.SetPTYDensity(GetPTYDensity7TeVSignalForward);

   CalculatorHMassAEM = CalculatorEM;    CalculatorHMassAEM.SetDoDeltaMH(true, 124.5);
   CalculatorHMassAME = CalculatorME;    CalculatorHMassAME.SetDoDeltaMH(true, 124.5);
   CalculatorHMassAEE = CalculatorEE;    CalculatorHMassAEE.SetDoDeltaMH(true, 124.5);
   CalculatorHMassAMM = CalculatorMM;    CalculatorHMassAMM.SetDoDeltaMH(true, 124.5);

   CalculatorHMassBEM = CalculatorEM;    CalculatorHMassBEM.SetDoDeltaMH(true, 125.0);
   CalculatorHMassBME = CalculatorME;    CalculatorHMassBME.SetDoDeltaMH(true, 125.0);
   CalculatorHMassBEE = CalculatorEE;    CalculatorHMassBEE.SetDoDeltaMH(true, 125.0);
   CalculatorHMassBMM = CalculatorMM;    CalculatorHMassBMM.SetDoDeltaMH(true, 125.0);

   CalculatorHMassCEM = CalculatorEM;    CalculatorHMassCEM.SetDoDeltaMH(true, 126.0);
   CalculatorHMassCME = CalculatorME;    CalculatorHMassCME.SetDoDeltaMH(true, 126.0);
   CalculatorHMassCEE = CalculatorEE;    CalculatorHMassCEE.SetDoDeltaMH(true, 126.0);
   CalculatorHMassCMM = CalculatorMM;    CalculatorHMassCMM.SetDoDeltaMH(true, 126.0);

   CalculatorHMassDEM = CalculatorEM;    CalculatorHMassDEM.SetDoDeltaMH(true, 126.5);
   CalculatorHMassDME = CalculatorME;    CalculatorHMassDME.SetDoDeltaMH(true, 126.5);
   CalculatorHMassDEE = CalculatorEE;    CalculatorHMassDEE.SetDoDeltaMH(true, 126.5);
   CalculatorHMassDMM = CalculatorMM;    CalculatorHMassDMM.SetDoDeltaMH(true, 126.5);

   CalculatorEM.PrintSettings();

   // CalculatorEM.TestOutput();
   // CalculatorME.TestOutput();
   // CalculatorEE.TestOutput();
   // CalculatorMM.TestOutput();

   // Setup tree
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("zz4lTree/probe_tree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("zz4lTree");
   if(Tree == NULL)
      return -1;

   float l1pt, l1eta, l1phi;   int l1id;
   float l2pt, l2eta, l2phi;   int l2id;
   float l3pt, l3eta, l3phi;   int l3id;
   float l4pt, l4eta, l4phi;   int l4id;
   Tree->SetBranchAddress("l1pt", &l1pt);
   Tree->SetBranchAddress("l1eta", &l1eta);
   Tree->SetBranchAddress("l1phi", &l1phi);
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l2pt", &l2pt);
   Tree->SetBranchAddress("l2eta", &l2eta);
   Tree->SetBranchAddress("l2phi", &l2phi);
   Tree->SetBranchAddress("l2id", &l2id);
   Tree->SetBranchAddress("l3pt", &l3pt);
   Tree->SetBranchAddress("l3eta", &l3eta);
   Tree->SetBranchAddress("l3phi", &l3phi);
   Tree->SetBranchAddress("l3id", &l3id);
   Tree->SetBranchAddress("l4pt", &l4pt);
   Tree->SetBranchAddress("l4eta", &l4eta);
   Tree->SetBranchAddress("l4phi", &l4phi);
   Tree->SetBranchAddress("l4id", &l4id);

   string BranchName = "";
   HybridCalculator *ChosenEM, *ChosenME, *ChosenEE, *ChosenMM;
   switch(Branch)
   {
      case 0:
         BranchName = "Central";
         ChosenEM = &CalculatorEM, ChosenME = &CalculatorME;
         ChosenEE = &CalculatorEE, ChosenMM = &CalculatorMM;
         break;
      case 1:
         BranchName = "LeptonUp";
         ChosenEM = &CalculatorUpEM, ChosenME = &CalculatorUpME;
         ChosenEE = &CalculatorUpEE, ChosenMM = &CalculatorUpMM;
         break;
      case 2:
         BranchName = "LeptonDown";
         ChosenEM = &CalculatorDownEM, ChosenME = &CalculatorDownME;
         ChosenEE = &CalculatorDownEE, ChosenMM = &CalculatorDownMM;
         break;
      case 3:
         BranchName = "LeptonWide";
         ChosenEM = &CalculatorWideEM, ChosenME = &CalculatorWideME;
         ChosenEE = &CalculatorWideEE, ChosenMM = &CalculatorWideMM;
         break;
      case 4:
         BranchName = "LeptonNarrow";
         ChosenEM = &CalculatorNarrowEM, ChosenME = &CalculatorNarrowME;
         ChosenEE = &CalculatorNarrowEE, ChosenMM = &CalculatorNarrowMM;
         break;
      case 5:
         BranchName = "SpectrumHard";
         ChosenEM = &CalculatorHardEM, ChosenME = &CalculatorHardME;
         ChosenEE = &CalculatorHardEE, ChosenMM = &CalculatorHardMM;
         break;
      case 6:
         BranchName = "SpectrumSoft";
         ChosenEM = &CalculatorSoftEM, ChosenME = &CalculatorSoftME;
         ChosenEE = &CalculatorSoftEE, ChosenMM = &CalculatorSoftMM;
         break;
      case 7:
         BranchName = "SpectrumCentral";
         ChosenEM = &CalculatorCentralEM, ChosenME = &CalculatorCentralME;
         ChosenEE = &CalculatorCentralEE, ChosenMM = &CalculatorCentralMM;
         break;
      case 8:
         BranchName = "SpectrumForward";
         ChosenEM = &CalculatorForwardEM, ChosenME = &CalculatorForwardME;
         ChosenEE = &CalculatorForwardEE, ChosenMM = &CalculatorForwardMM;
         break;
      case 9:
         BranchName = "HMassA";
         ChosenEM = &CalculatorHMassAEM, ChosenME = &CalculatorHMassAME;
         ChosenEE = &CalculatorHMassAEE, ChosenMM = &CalculatorHMassAMM;
         break;
      case 10:
         BranchName = "HMassB";
         ChosenEM = &CalculatorHMassBEM, ChosenME = &CalculatorHMassBME;
         ChosenEE = &CalculatorHMassBEE, ChosenMM = &CalculatorHMassBMM;
         break;
      case 11:
         BranchName = "HMassC";
         ChosenEM = &CalculatorHMassCEM, ChosenME = &CalculatorHMassCME;
         ChosenEE = &CalculatorHMassCEE, ChosenMM = &CalculatorHMassCMM;
         break;
      case 12:
         BranchName = "HMassD";
         ChosenEM = &CalculatorHMassDEM, ChosenME = &CalculatorHMassDME;
         ChosenEE = &CalculatorHMassDEE, ChosenMM = &CalculatorHMassDMM;
         break;
      default:
         BranchName = "Central";
         ChosenEM = &CalculatorEM, ChosenME = &CalculatorME;
         ChosenEE = &CalculatorEE, ChosenMM = &CalculatorMM;
         break;
   }

   // Start looping
   int EventCount = Tree->GetEntries();
   for(int iEvent = StartEvent; iEvent < EventCount && iEvent <= EndEvent; iEvent++)
   {
      Tree->GetEntry(iEvent);

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      if(FlavorTreatment == 1)   l1id = 11, l3id = 13;
      if(FlavorTreatment == 2)   l1id = 13, l3id = 11;
      if(FlavorTreatment == 3)   l1id = 11, l3id = 11;
      if(FlavorTreatment == 4)   l1id = 13, l3id = 13;

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      EventParameters Angles = ConvertVectorsToAnglesRoberto(Leptons);

      LeptonVectors AlternativeLeptons;
      if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() > (Leptons.Lepton21 + Leptons.Lepton12).GetMass())
      {
         AlternativeLeptons.Lepton11 = Leptons.Lepton11;
         AlternativeLeptons.Lepton12 = Leptons.Lepton22;
         AlternativeLeptons.Lepton21 = Leptons.Lepton21;
         AlternativeLeptons.Lepton22 = Leptons.Lepton12;
      }
      else
      {
         AlternativeLeptons.Lepton11 = Leptons.Lepton21;
         AlternativeLeptons.Lepton12 = Leptons.Lepton12;
         AlternativeLeptons.Lepton21 = Leptons.Lepton11;
         AlternativeLeptons.Lepton22 = Leptons.Lepton22;
      }

      EventParameters AlternativeAngles = ConvertVectorsToAnglesRoberto(AlternativeLeptons);

      vector<double> Integral;
      vector<double> AlternativeIntegral;

      // cout << Leptons << " " << Angles << endl;

      if(PassBaselineCut(Angles) == true)
      {
         if(l1id == 11 && l3id == 11)
         {
            Integral = ChosenEE->SimpleMassIntegral(Angles);
            AlternativeIntegral = ChosenEE->SimpleMassIntegral(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
               Integral[i] = Integral[i] + AlternativeIntegral[i];
         }
         if(l1id == 11 && l3id == 13)
            Integral = ChosenEM->SimpleMassIntegral(Angles);
         if(l1id == 13 && l3id == 11)
            Integral = ChosenME->SimpleMassIntegral(Angles);
         if(l1id == 13 && l3id == 13)
         {
            Integral = ChosenMM->SimpleMassIntegral(Angles);
            AlternativeIntegral = ChosenMM->SimpleMassIntegral(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
               Integral[i] = Integral[i] + AlternativeIntegral[i];
         }
      }
      else
         cout << "Didn't pass baseline cut!" << endl;

      cout << setprecision(20);
      cout << FileName << " " << BranchName << " " << iEvent;
      for(int i = 0; i < (int)Integral.size(); i++)
         cout << " " << Integral[i];
      cout << endl;
   }

   // Cleanup
   File.Close();

   return 0;
}

bool CheckIfGood(vector<double> Single)
{
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

void PrintResult(string Identifier, vector<double> Total, int Count)
{
   cout << Identifier << " " << Count;
   for(int i = 0; i < (int)Total.size(); i++)
      cout << setprecision(20) << " " << Total[i] / Count;
   cout << endl;
}

bool PassBaselineCut(EventParameters &Event)
{
   return true;

   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(fabs(Leptons.Lepton11.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.5)   return false;

   if(Event.ZMass < 40)    return false;
   if(Event.Z2Mass < 12)   return false;

   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;
   if(LPTs[1] < 5)    return false;
   if(LPTs[0] < 5)    return false;

   // if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   // if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   // if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   // if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   // if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   // if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}













