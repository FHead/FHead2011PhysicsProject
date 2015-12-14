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

   if(argc <= 3)
   {
      cerr << "Usage: " << argv[0] << " FileWithTree StartEvent EndEvent" << endl;
      return -1;
   }

   FileName = argv[1];
   StartEvent = atoi(argv[2]);
   EndEvent = atoi(argv[3]);

   // Read spectrum of Higgs
   ifstream in("HiggsFile_125");
   vector<double> HPT, HEta, HWeight;
   while(in)
   {
      char ch[10240] = "";
      in.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      double TempPT = -100, TempEta = -100, TempWeight = -100;
      str >> TempPT >> TempEta >> TempWeight;

      if(TempPT < 0 || TempEta < -99 || TempWeight < -99)
         continue;

      HPT.push_back(TempPT);
      HEta.push_back(TempEta);
      HWeight.push_back(TempWeight);
   }

   // Setup calculators
   HybridCalculator CalculatorEE, CalculatorME, CalculatorEM, CalculatorMM;

   CalculatorEM.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorEM.SetSmear12(SmearElectronCentral);
   CalculatorEM.SetSmear34(SmearMuonCentral);
   CalculatorEM.SetToleranceF(1e-12);
   CalculatorEM.SetMaxDepthF(30);
   CalculatorEM.SetSimpleMassIntegralStep(80);
   CalculatorEM.SetExpansionOrder(2);
   CalculatorEM.SetDoDeltaMH(true, 125);
   CalculatorEM.SetIgnorePhi(true);
   CalculatorEM.SetApplyEfficiencyAtEnd(true);
   CalculatorEM.SetIntegralCRange(0.75, 1.25);
   CalculatorEM.SetPTYDensity(GetPTYDensity8TeVSignal);
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
   CalculatorEE.SetSimpleMassIntegralStep(50);
   CalculatorEE.SetExpansionOrder(2);
   CalculatorEE.SetDoDeltaMH(true, 125);
   CalculatorEE.SetIgnorePhi(true);
   CalculatorEE.SetApplyEfficiencyAtEnd(true);
   CalculatorEE.SetIntegralCRange(0.75, 1.25);
   CalculatorEE.SetPTYDensity(GetPTYDensity8TeVSignal);
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

   CalculatorMM = CalculatorEE;
   CalculatorMM.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorMM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorMM.SetSmear12(SmearMuonCentral);
   CalculatorMM.SetSmear34(SmearMuonCentral);

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

   CalculatorHardEM = CalculatorEM;      CalculatorHardEM.SetPTYDensity(GetPTYDensity8TeVSignalHard);
   CalculatorHardME = CalculatorME;      CalculatorHardME.SetPTYDensity(GetPTYDensity8TeVSignalHard);
   CalculatorHardEE = CalculatorEE;      CalculatorHardEE.SetPTYDensity(GetPTYDensity8TeVSignalHard);
   CalculatorHardMM = CalculatorMM;      CalculatorHardMM.SetPTYDensity(GetPTYDensity8TeVSignalHard);

   CalculatorSoftEM = CalculatorEM;      CalculatorSoftEM.SetPTYDensity(GetPTYDensity8TeVSignalSoft);
   CalculatorSoftME = CalculatorME;      CalculatorSoftME.SetPTYDensity(GetPTYDensity8TeVSignalSoft);
   CalculatorSoftEE = CalculatorEE;      CalculatorSoftEE.SetPTYDensity(GetPTYDensity8TeVSignalSoft);
   CalculatorSoftMM = CalculatorMM;      CalculatorSoftMM.SetPTYDensity(GetPTYDensity8TeVSignalSoft);
   
   CalculatorCentralEM = CalculatorEM;   CalculatorCentralEM.SetPTYDensity(GetPTYDensity8TeVSignalCentral);
   CalculatorCentralME = CalculatorME;   CalculatorCentralME.SetPTYDensity(GetPTYDensity8TeVSignalCentral);
   CalculatorCentralEE = CalculatorEE;   CalculatorCentralEE.SetPTYDensity(GetPTYDensity8TeVSignalCentral);
   CalculatorCentralMM = CalculatorMM;   CalculatorCentralMM.SetPTYDensity(GetPTYDensity8TeVSignalCentral);

   CalculatorForwardEM = CalculatorEM;   CalculatorForwardEM.SetPTYDensity(GetPTYDensity8TeVSignalForward);
   CalculatorForwardME = CalculatorME;   CalculatorForwardME.SetPTYDensity(GetPTYDensity8TeVSignalForward);
   CalculatorForwardEE = CalculatorEE;   CalculatorForwardEE.SetPTYDensity(GetPTYDensity8TeVSignalForward);
   CalculatorForwardMM = CalculatorMM;   CalculatorForwardMM.SetPTYDensity(GetPTYDensity8TeVSignalForward);

   CalculatorHMassAEM = CalculatorEM;    CalculatorHMassAEM.SetDoDeltaMH(true, 122);
   CalculatorHMassAME = CalculatorME;    CalculatorHMassAME.SetDoDeltaMH(true, 122);
   CalculatorHMassAEE = CalculatorEE;    CalculatorHMassAEE.SetDoDeltaMH(true, 122);
   CalculatorHMassAMM = CalculatorMM;    CalculatorHMassAMM.SetDoDeltaMH(true, 122);

   CalculatorHMassBEM = CalculatorEM;    CalculatorHMassBEM.SetDoDeltaMH(true, 124);
   CalculatorHMassBME = CalculatorME;    CalculatorHMassBME.SetDoDeltaMH(true, 124);
   CalculatorHMassBEE = CalculatorEE;    CalculatorHMassBEE.SetDoDeltaMH(true, 124);
   CalculatorHMassBMM = CalculatorMM;    CalculatorHMassBMM.SetDoDeltaMH(true, 124);

   CalculatorHMassCEM = CalculatorEM;    CalculatorHMassCEM.SetDoDeltaMH(true, 126);
   CalculatorHMassCME = CalculatorME;    CalculatorHMassCME.SetDoDeltaMH(true, 126);
   CalculatorHMassCEE = CalculatorEE;    CalculatorHMassCEE.SetDoDeltaMH(true, 126);
   CalculatorHMassCMM = CalculatorMM;    CalculatorHMassCMM.SetDoDeltaMH(true, 126);

   CalculatorHMassDEM = CalculatorEM;    CalculatorHMassDEM.SetDoDeltaMH(true, 128);
   CalculatorHMassDME = CalculatorME;    CalculatorHMassDME.SetDoDeltaMH(true, 128);
   CalculatorHMassDEE = CalculatorEE;    CalculatorHMassDEE.SetDoDeltaMH(true, 128);
   CalculatorHMassDMM = CalculatorMM;    CalculatorHMassDMM.SetDoDeltaMH(true, 128);

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

      vector<double> Integral, IntegralUp, IntegralDown, IntegralWide, IntegralNarrow,
         IntegralHard, IntegralSoft, IntegralCentral, IntegralForward,
         IntegralHMassA, IntegralHMassB, IntegralHMassC, IntegralHMassD;
      vector<double> AlternativeIntegral, AlternativeIntegralUp, AlternativeIntegralDown,
         AlternativeIntegralWide, AlternativeIntegralNarrow, AlternativeIntegralHard,
         AlternativeIntegralSoft, AlternativeIntegralCentral, AlternativeIntegralForward,
         AlternativeIntegralHMassA, AlternativeIntegralHMassB, AlternativeIntegralHMassC,
         AlternativeIntegralHMassD;

      if(PassBaselineCut(Angles) == true)
      {
         if(l1id == 11 && l3id == 11)
         {
            Integral = CalculatorEE.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpEE.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownEE.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideEE.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowEE.SimpleMassIntegral(Angles);
            IntegralHard = CalculatorHardEE.SimpleMassIntegral(Angles);
            IntegralSoft = CalculatorSoftEE.SimpleMassIntegral(Angles);
            IntegralForward = CalculatorForwardEE.SimpleMassIntegral(Angles);
            IntegralCentral = CalculatorCentralEE.SimpleMassIntegral(Angles);
            IntegralHMassA = CalculatorHMassAEE.SimpleMassIntegral(Angles);
            IntegralHMassB = CalculatorHMassBEE.SimpleMassIntegral(Angles);
            IntegralHMassC = CalculatorHMassCEE.SimpleMassIntegral(Angles);
            IntegralHMassD = CalculatorHMassDEE.SimpleMassIntegral(Angles);

            AlternativeIntegral = CalculatorEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralUp = CalculatorUpEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralDown = CalculatorDownEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralWide = CalculatorWideEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralNarrow = CalculatorNarrowEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHard = CalculatorHardEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralSoft = CalculatorSoftEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralForward = CalculatorForwardEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralCentral = CalculatorCentralEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHMassA = CalculatorHMassAEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHMassB = CalculatorHMassBEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHMassC = CalculatorHMassCEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHMassD = CalculatorHMassDEE.SimpleMassIntegral(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
            {
               Integral[i] = (Integral[i] + AlternativeIntegral[i]);
               IntegralUp[i] = (IntegralUp[i] + AlternativeIntegralUp[i]);
               IntegralDown[i] = (IntegralDown[i] + AlternativeIntegralDown[i]);
               IntegralWide[i] = (IntegralWide[i] + AlternativeIntegralWide[i]);
               IntegralNarrow[i] = (IntegralNarrow[i] + AlternativeIntegralNarrow[i]);
               IntegralHard[i] = (IntegralHard[i] + AlternativeIntegralHard[i]);
               IntegralSoft[i] = (IntegralSoft[i] + AlternativeIntegralSoft[i]);
               IntegralForward[i] = (IntegralForward[i] + AlternativeIntegralForward[i]);
               IntegralCentral[i] = (IntegralCentral[i] + AlternativeIntegralCentral[i]);
               IntegralHMassA[i] = (IntegralHMassA[i] + AlternativeIntegralHMassA[i]);
               IntegralHMassB[i] = (IntegralHMassB[i] + AlternativeIntegralHMassB[i]);
               IntegralHMassC[i] = (IntegralHMassC[i] + AlternativeIntegralHMassC[i]);
               IntegralHMassD[i] = (IntegralHMassD[i] + AlternativeIntegralHMassD[i]);
            }
         }
         if(l1id == 11 && l3id == 13)
         {
            Integral = CalculatorEM.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpEM.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownEM.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideEM.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowEM.SimpleMassIntegral(Angles);
            IntegralHard = CalculatorHardEM.SimpleMassIntegral(Angles);
            IntegralSoft = CalculatorSoftEM.SimpleMassIntegral(Angles);
            IntegralForward = CalculatorForwardEM.SimpleMassIntegral(Angles);
            IntegralCentral = CalculatorCentralEM.SimpleMassIntegral(Angles);
            IntegralHMassA = CalculatorHMassAEM.SimpleMassIntegral(Angles);
            IntegralHMassB = CalculatorHMassBEM.SimpleMassIntegral(Angles);
            IntegralHMassC = CalculatorHMassCEM.SimpleMassIntegral(Angles);
            IntegralHMassD = CalculatorHMassDEM.SimpleMassIntegral(Angles);
         }
         if(l1id == 13 && l3id == 11)
         {
            Integral = CalculatorME.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpME.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownME.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideME.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowME.SimpleMassIntegral(Angles);
            IntegralHard = CalculatorHardME.SimpleMassIntegral(Angles);
            IntegralSoft = CalculatorSoftME.SimpleMassIntegral(Angles);
            IntegralForward = CalculatorForwardME.SimpleMassIntegral(Angles);
            IntegralCentral = CalculatorCentralME.SimpleMassIntegral(Angles);
            IntegralHMassA = CalculatorHMassAME.SimpleMassIntegral(Angles);
            IntegralHMassB = CalculatorHMassBME.SimpleMassIntegral(Angles);
            IntegralHMassC = CalculatorHMassCME.SimpleMassIntegral(Angles);
            IntegralHMassD = CalculatorHMassDME.SimpleMassIntegral(Angles);
         }
         if(l1id == 13 && l3id == 13)
         {
            Integral = CalculatorMM.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpMM.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownMM.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideMM.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowMM.SimpleMassIntegral(Angles);
            IntegralHard = CalculatorHardMM.SimpleMassIntegral(Angles);
            IntegralSoft = CalculatorSoftMM.SimpleMassIntegral(Angles);
            IntegralForward = CalculatorForwardMM.SimpleMassIntegral(Angles);
            IntegralCentral = CalculatorCentralMM.SimpleMassIntegral(Angles);
            IntegralHMassA = CalculatorHMassAMM.SimpleMassIntegral(Angles);
            IntegralHMassB = CalculatorHMassBMM.SimpleMassIntegral(Angles);
            IntegralHMassC = CalculatorHMassCMM.SimpleMassIntegral(Angles);
            IntegralHMassD = CalculatorHMassDMM.SimpleMassIntegral(Angles);

            AlternativeIntegral = CalculatorMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralUp = CalculatorUpMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralDown = CalculatorDownMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralWide = CalculatorWideMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralNarrow = CalculatorNarrowMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHard = CalculatorHardMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralSoft = CalculatorSoftMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralForward = CalculatorForwardMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralCentral = CalculatorCentralMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHMassA = CalculatorHMassAMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHMassB = CalculatorHMassBMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHMassC = CalculatorHMassCMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralHMassD = CalculatorHMassDMM.SimpleMassIntegral(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
            {
               Integral[i] = (Integral[i] + AlternativeIntegral[i]);
               IntegralUp[i] = (IntegralUp[i] + AlternativeIntegralUp[i]);
               IntegralDown[i] = (IntegralDown[i] + AlternativeIntegralDown[i]);
               IntegralWide[i] = (IntegralWide[i] + AlternativeIntegralWide[i]);
               IntegralNarrow[i] = (IntegralNarrow[i] + AlternativeIntegralNarrow[i]);
               IntegralHard[i] = (IntegralHard[i] + AlternativeIntegralHard[i]);
               IntegralSoft[i] = (IntegralSoft[i] + AlternativeIntegralSoft[i]);
               IntegralForward[i] = (IntegralForward[i] + AlternativeIntegralForward[i]);
               IntegralCentral[i] = (IntegralCentral[i] + AlternativeIntegralCentral[i]);
               IntegralHMassA[i] = (IntegralHMassA[i] + AlternativeIntegralHMassA[i]);
               IntegralHMassB[i] = (IntegralHMassB[i] + AlternativeIntegralHMassB[i]);
               IntegralHMassC[i] = (IntegralHMassC[i] + AlternativeIntegralHMassC[i]);
               IntegralHMassD[i] = (IntegralHMassD[i] + AlternativeIntegralHMassD[i]);
            }
         }
      }
      else
         cout << "Didn't pass baseline cut!" << endl;

      cout << setprecision(20);
      cout << FileName << " Central " << iEvent;
      for(int i = 0; i < (int)Integral.size(); i++)
         cout << " " << Integral[i];
      cout << endl;
      cout << FileName << " LeptonUp " << iEvent;
      for(int i = 0; i < (int)IntegralUp.size(); i++)
         cout << " " << IntegralUp[i];
      cout << endl;
      cout << FileName << " LeptonDown " << iEvent;
      for(int i = 0; i < (int)IntegralDown.size(); i++)
         cout << " " << IntegralDown[i];
      cout << endl;
      cout << FileName << " LeptonWide " << iEvent;
      for(int i = 0; i < (int)IntegralWide.size(); i++)
         cout << " " << IntegralWide[i];
      cout << endl;
      cout << FileName << " LeptonNarrow " << iEvent;
      for(int i = 0; i < (int)IntegralNarrow.size(); i++)
         cout << " " << IntegralNarrow[i];
      cout << endl;
      cout << FileName << " SpectrumHard " << iEvent;
      for(int i = 0; i < (int)IntegralHard.size(); i++)
         cout << " " << IntegralHard[i];
      cout << endl;
      cout << FileName << " SpectrumSoft " << iEvent;
      for(int i = 0; i < (int)IntegralSoft.size(); i++)
         cout << " " << IntegralSoft[i];
      cout << endl;
      cout << FileName << " SpectrumCentral " << iEvent;
      for(int i = 0; i < (int)IntegralCentral.size(); i++)
         cout << " " << IntegralCentral[i];
      cout << endl;
      cout << FileName << " SpectrumForward " << iEvent;
      for(int i = 0; i < (int)IntegralForward.size(); i++)
         cout << " " << IntegralForward[i];
      cout << endl;
      cout << FileName << " HMassA " << iEvent;
      for(int i = 0; i < (int)IntegralHMassA.size(); i++)
         cout << " " << IntegralHMassA[i];
      cout << endl;
      cout << FileName << " HMassB " << iEvent;
      for(int i = 0; i < (int)IntegralHMassB.size(); i++)
         cout << " " << IntegralHMassB[i];
      cout << endl;
      cout << FileName << " HMassC " << iEvent;
      for(int i = 0; i < (int)IntegralHMassC.size(); i++)
         cout << " " << IntegralHMassC[i];
      cout << endl;
      cout << FileName << " HMassD " << iEvent;
      for(int i = 0; i < (int)IntegralHMassD.size(); i++)
         cout << " " << IntegralHMassD[i];
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

   // if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   // if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   // if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   // if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   // if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   // if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}













