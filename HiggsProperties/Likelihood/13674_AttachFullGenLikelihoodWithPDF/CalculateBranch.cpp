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
#include "StockM4l.h"

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
   int StockM4lSeed = -1;

   if(argc <= 4)
   {
      cerr << "Usage: " << argv[0] << " FileWithTree StartEvent EndEvent StockM4lSeed" << endl;
      return -1;
   }

   FileName = argv[1];
   StartEvent = atoi(argv[2]);
   EndEvent = atoi(argv[3]);
   StockM4lSeed = atoi(argv[4]);
   cerr << "StockM4lSeed = " << StockM4lSeed << endl;

   StockM4l M4l(StockM4lSeed, 100000);

   // Setup calculators
   HybridCalculator CalculatorEE, CalculatorME, CalculatorEM, CalculatorMM;

   CalculatorEM.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorEM.SetSmear12(SmearElectronCentral);
   CalculatorEM.SetSmear34(SmearMuonCentral);
   CalculatorEM.SetToleranceF(1e-12);
   CalculatorEM.SetMaxDepthF(30);
   CalculatorEM.SetSimpleMassIntegralStep(180);
   CalculatorEM.SetExpansionOrder(2);
   CalculatorEM.SetDoDeltaMH(true, 125);
   CalculatorEM.SetIgnorePhi(true);
   CalculatorEM.SetApplyEfficiencyAtEnd(true);
   CalculatorEM.SetIntegralCRange(0.75, 1.25);
   CalculatorEM.SetPTYDensity(GetPTYDensityGG_MZ_CTEQ6l1_13432);
   CalculatorEM.SetAttractorStrength(2);
   CalculatorEM.SetIntegralCStep(20);
   CalculatorEM.SetSimpleMassIntegralWindow(true, 30);
   CalculatorEM.SetSimpleMassIntegralWindow(false, 40);
   CalculatorEM.SetFlatApproximation(false);
   CalculatorEM.SetIncludeSwapping(true);
   CalculatorEM.SetIgnoreTip(false);
   CalculatorEM.SetTipRangeFactor(0.05);
   CalculatorEM.SetUseSmartCenter(true);

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
   CalculatorME.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorME.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorME.SetSmear12(SmearMuonCentral);
   CalculatorME.SetSmear34(SmearElectronCentral);

   CalculatorEE.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEE.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorEE.SetSmear12(SmearElectronCentral);
   CalculatorEE.SetSmear34(SmearElectronCentral);
   CalculatorEE.SetToleranceF(1e-12);
   CalculatorEE.SetMaxDepthF(30);
   CalculatorEE.SetSimpleMassIntegralStep(180);
   CalculatorEE.SetExpansionOrder(2);
   CalculatorEE.SetDoDeltaMH(true, 125);
   CalculatorEE.SetIgnorePhi(true);
   CalculatorEE.SetApplyEfficiencyAtEnd(true);
   CalculatorEE.SetIntegralCRange(0.75, 1.25);
   CalculatorEE.SetPTYDensity(GetPTYDensityGG_MZ_CTEQ6l1_13432);
   CalculatorEE.SetAttractorStrength(2);
   CalculatorEE.SetIntegralCStep(20);
   CalculatorEE.SetSimpleMassIntegralWindow(true, 30);
   CalculatorEE.SetSimpleMassIntegralWindow(false, 40);
   CalculatorEE.SetFlatApproximation(false);
   CalculatorEE.SetIncludeSwapping(true);
   CalculatorEE.SetIgnoreTip(false);
   CalculatorEE.SetTipRangeFactor(0.05);
   CalculatorEE.SetUseSmartCenter(true);

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
   CalculatorMM.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorMM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorMM.SetSmear12(SmearMuonCentral);
   CalculatorMM.SetSmear34(SmearMuonCentral);

   HybridCalculator CalculatorUpEM, CalculatorUpME, CalculatorUpEE, CalculatorUpMM;
   HybridCalculator CalculatorDownEM, CalculatorDownME, CalculatorDownEE, CalculatorDownMM;
   HybridCalculator CalculatorWideEM, CalculatorWideME, CalculatorWideEE, CalculatorWideMM;
   HybridCalculator CalculatorNarrowEM, CalculatorNarrowME, CalculatorNarrowEE, CalculatorNarrowMM;

   CalculatorUpEM = CalculatorEM;                     CalculatorDownEM = CalculatorEM;
   CalculatorUpEM.SetSmear12(SmearElectronUp);        CalculatorDownEM.SetSmear12(SmearElectronDown);
   CalculatorUpEM.SetSmear34(SmearMuonUp);            CalculatorDownEM.SetSmear34(SmearMuonDown);
   CalculatorUpME = CalculatorME;                     CalculatorDownME = CalculatorME;
   CalculatorUpME.SetSmear12(SmearMuonUp);            CalculatorDownME.SetSmear12(SmearMuonDown);
   CalculatorUpME.SetSmear34(SmearElectronUp);        CalculatorDownME.SetSmear34(SmearElectronDown);
   CalculatorUpEE = CalculatorEE;                     CalculatorDownEE = CalculatorEE;
   CalculatorUpEE.SetSmear12(SmearElectronUp);        CalculatorDownEE.SetSmear12(SmearElectronDown);
   CalculatorUpEE.SetSmear34(SmearElectronUp);        CalculatorDownEE.SetSmear34(SmearElectronDown);
   CalculatorUpMM = CalculatorMM;                     CalculatorDownMM = CalculatorMM;
   CalculatorUpMM.SetSmear12(SmearMuonUp);            CalculatorDownMM.SetSmear12(SmearMuonDown);
   CalculatorUpMM.SetSmear34(SmearMuonUp);            CalculatorDownMM.SetSmear34(SmearMuonDown);

   CalculatorWideEM = CalculatorEM;                   CalculatorNarrowEM = CalculatorEM;
   CalculatorWideEM.SetSmear12(SmearElectronWide);    CalculatorNarrowEM.SetSmear12(SmearElectronNarrow);
   CalculatorWideEM.SetSmear34(SmearMuonWide);        CalculatorNarrowEM.SetSmear34(SmearMuonNarrow);
   CalculatorWideME = CalculatorME;                   CalculatorNarrowME = CalculatorME;
   CalculatorWideME.SetSmear12(SmearMuonWide);        CalculatorNarrowME.SetSmear12(SmearMuonNarrow);
   CalculatorWideME.SetSmear34(SmearElectronWide);    CalculatorNarrowME.SetSmear34(SmearElectronNarrow);
   CalculatorWideEE = CalculatorEE;                   CalculatorNarrowEE = CalculatorEE;
   CalculatorWideEE.SetSmear12(SmearElectronWide);    CalculatorNarrowEE.SetSmear12(SmearElectronNarrow);
   CalculatorWideEE.SetSmear34(SmearElectronWide);    CalculatorNarrowEE.SetSmear34(SmearElectronNarrow);
   CalculatorWideMM = CalculatorMM;                   CalculatorNarrowMM = CalculatorMM;
   CalculatorWideMM.SetSmear12(SmearMuonWide);        CalculatorNarrowMM.SetSmear12(SmearMuonNarrow);
   CalculatorWideMM.SetSmear34(SmearMuonWide);        CalculatorNarrowMM.SetSmear34(SmearMuonNarrow);

   CalculatorEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorUpEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorDownEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorWideEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorNarrowEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorUpEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorDownEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorWideEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorNarrowEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorUpME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorDownME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorWideME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorNarrowME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorUpMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorDownMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorWideMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorNarrowMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);

   // CalculatorEM.TestOutput();
   // CalculatorME.TestOutput();
   // CalculatorEE.TestOutput();
   // CalculatorMM.TestOutput();

   // Setup tree
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      return -1;

   double l1pt, l1eta, l1phi;   double l1id;
   double l2pt, l2eta, l2phi;   double l2id;
   double l3pt, l3eta, l3phi;   double l3id;
   double l4pt, l4eta, l4phi;   double l4id;
   Tree->SetBranchAddress("L1PT", &l1pt);
   Tree->SetBranchAddress("L1Eta", &l1eta);
   Tree->SetBranchAddress("L1Phi", &l1phi);
   Tree->SetBranchAddress("L1ID", &l1id);
   Tree->SetBranchAddress("L2PT", &l2pt);
   Tree->SetBranchAddress("L2Eta", &l2eta);
   Tree->SetBranchAddress("L2Phi", &l2phi);
   Tree->SetBranchAddress("L2ID", &l2id);
   Tree->SetBranchAddress("L3PT", &l3pt);
   Tree->SetBranchAddress("L3Eta", &l3eta);
   Tree->SetBranchAddress("L3Phi", &l3phi);
   Tree->SetBranchAddress("L3ID", &l3id);
   Tree->SetBranchAddress("L4PT", &l4pt);
   Tree->SetBranchAddress("L4Eta", &l4eta);
   Tree->SetBranchAddress("L4Phi", &l4phi);
   Tree->SetBranchAddress("L4ID", &l4id);

   // Start looping
   int EventCount = Tree->GetEntries();
   for(int iEvent = StartEvent; iEvent < EventCount && iEvent <= EndEvent; iEvent++)
   {
      Tree->GetEntry(iEvent);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      EventParameters Angles = ConvertVectorsToAnglesRoberto(Leptons);

      double m4l = Angles.HMass;
      if(StockM4lSeed > 0)
         m4l = M4l[iEvent];

      double TempRatio = 125 / Angles.HMass;
      Angles.HMass = Angles.HMass * TempRatio;
      Angles.ZMass = Angles.ZMass * TempRatio;
      Angles.Z2Mass = Angles.Z2Mass * TempRatio;
      Leptons = ConvertAnglesToVectorsRoberto(Angles);

      if(l1id == l3id)
         Leptons = Leptons.ReorderLeptons4e();
      else
         Leptons = Leptons.ReorderLeptons2e2mu();
      Angles = ConvertVectorsToAnglesRoberto(Leptons);

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

      double RecoJ12 = VolumeElement::EstimateVolumeFull5(Angles);
      double SortedRecoJ12 = VolumeElement::EstimateVolumeFull5(AlternativeAngles);

      if(PassBaselineCut(Angles) == true)
      {
         if(abs(l1id) == 11 && abs(l3id) == 11)
         {
            Integral = CalculatorEE.PassThroughMode(Angles);
            AlternativeIntegral = CalculatorEE.PassThroughMode(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
               Integral[i] = (Integral[i] + AlternativeIntegral[i] * SortedRecoJ12 / RecoJ12);
         }
         else if(abs(l1id) == 11 && abs(l3id) == 13)
            Integral = CalculatorEM.PassThroughMode(Angles);
         else if(abs(l1id) == 13 && abs(l3id) == 11)
            Integral = CalculatorME.PassThroughMode(Angles);
         else if(abs(l1id) == 13 && abs(l3id) == 13)
         {
            Integral = CalculatorMM.PassThroughMode(Angles);
            AlternativeIntegral = CalculatorMM.PassThroughMode(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
               Integral[i] = (Integral[i] + AlternativeIntegral[i] * SortedRecoJ12 / RecoJ12);
         }
         else
            cerr << "MEOW!" << endl;
      }
      else
         cout << "Didn't pass baseline cut!" << endl;

      double Ratio = 125 / m4l;

      cout << setprecision(20);
      cout << FileName << " Central " << iEvent;
      for(int i = 0; i < (int)Integral.size(); i++)
         cout << " " << Integral[i] * exp(-(m4l - 125) * (m4l - 125) / (2 * 1 * 1)) / m4l
            * Ratio * Ratio * Ratio * Ratio;
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

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

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
   if(LPTs[1] < 7)    return false;
   if(LPTs[0] < 7)    return false;

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}












