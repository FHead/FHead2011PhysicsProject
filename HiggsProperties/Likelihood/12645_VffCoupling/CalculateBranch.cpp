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
   // CalculatorEM.SetPTYDensity(ToyPTYDensity);
   CalculatorEM.SetAttractorStrength(2);
   CalculatorEM.SetIntegralCStep(20);
   CalculatorEM.SetSimpleMassIntegralWindow(true, 30);
   CalculatorEM.SetSimpleMassIntegralWindow(false, 40);
   CalculatorEM.SetFlatApproximation(false);
   CalculatorEM.SetIncludeSwapping(true);
   CalculatorEM.SetIgnoreTip(false);
   CalculatorEM.SetTipRangeFactor(0.05);
   CalculatorEM.SetUseSmartCenter(true);

   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000404);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000413);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000422);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000431);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000440);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000503);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000512);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000521);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000530);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000602);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000611);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_000620);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001304);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001313);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001322);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001331);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001340);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001403);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001412);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001421);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001430);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001502);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001511);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_001520);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002204);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002213);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002222);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002231);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002240);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002303);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002312);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002321);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002330);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002402);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002411);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_002420);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003104);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003113);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003122);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003131);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003140);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003203);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003212);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003221);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003230);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003302);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003311);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_003320);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004004);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004013);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004022);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004031);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004040);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004103);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004112);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004121);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004130);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004202);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004211);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_004220);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_005003);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_005012);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_005021);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_005030);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_005102);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_005111);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_005120);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_006002);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_006011);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_006020);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_110303);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_110312);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_110321);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_110330);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_110402);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_110411);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_110420);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_110501);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_110510);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_111203);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_111212);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_111221);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_111230);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_111302);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_111311);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_111320);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_111401);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_111410);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_112103);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_112112);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_112121);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_112130);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_112202);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_112211);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_112220);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_112301);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_112310);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_113003);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_113012);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_113021);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_113030);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_113102);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_113111);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_113120);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_113201);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_113210);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_114002);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_114011);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_114020);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_114101);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_114110);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_115001);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_115010);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_200303);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_200312);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_200321);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_200330);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_200402);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_200411);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_200420);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_201203);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_201212);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_201221);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_201230);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_201302);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_201311);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_201320);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_202103);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_202112);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_202121);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_202130);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_202202);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_202211);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_202220);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_203003);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_203012);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_203021);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_203030);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_203102);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_203111);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_203120);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_204002);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_204011);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_204020);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_220202);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_220211);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_220220);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_220301);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_220310);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_220400);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_221102);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_221111);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_221120);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_221201);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_221210);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_221300);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_222002);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_222011);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_222020);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_222101);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_222110);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_222200);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_223001);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_223010);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_223100);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_224000);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_310202);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_310211);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_310220);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_310301);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_310310);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_311102);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_311111);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_311120);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_311201);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_311210);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_312002);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_312011);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_312020);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_312101);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_312110);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_313001);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_313010);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_330101);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_330110);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_330200);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_331001);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_331010);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_331100);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_332000);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_400202);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_400211);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_400220);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_401102);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_401111);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_401120);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_402002);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_402011);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_402020);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_420101);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_420110);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_420200);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_421001);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_421010);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_421100);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_422000);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_440000);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_510101);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_510110);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_511001);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_511010);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_530000);
   CalculatorEM.SetMECalculator(GetDecomposed2e2muBackground_620000);
   CalculatorEM.SetMECalculator(CalculateUUbarBackground2e2muDirectional);
   
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
   // CalculatorEE.SetPTYDensity(ToyPTYDensity);
   CalculatorEE.SetAttractorStrength(2);
   CalculatorEE.SetIntegralCStep(20);
   CalculatorEE.SetSimpleMassIntegralWindow(true, 30);
   CalculatorEE.SetSimpleMassIntegralWindow(false, 40);
   CalculatorEE.SetFlatApproximation(false);
   CalculatorEE.SetIncludeSwapping(true);
   CalculatorEE.SetIgnoreTip(false);
   CalculatorEE.SetTipRangeFactor(0.05);
   CalculatorEE.SetUseSmartCenter(true);

   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000404);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000413);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000422);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000431);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000440);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000503);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000512);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000521);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000530);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000602);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000611);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_000620);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001304);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001313);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001322);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001331);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001340);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001403);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001412);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001421);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001430);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001502);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001511);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_001520);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002204);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002213);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002222);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002231);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002240);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002303);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002312);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002321);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002330);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002402);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002411);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_002420);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003104);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003113);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003122);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003131);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003140);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003203);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003212);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003221);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003230);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003302);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003311);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_003320);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004004);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004013);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004022);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004031);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004040);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004103);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004112);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004121);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004130);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004202);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004211);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_004220);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_005003);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_005012);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_005021);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_005030);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_005102);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_005111);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_005120);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_006002);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_006011);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_006020);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_110303);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_110312);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_110321);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_110330);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_110402);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_110411);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_110420);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_110501);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_110510);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_111203);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_111212);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_111221);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_111230);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_111302);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_111311);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_111320);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_111401);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_111410);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_112103);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_112112);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_112121);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_112130);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_112202);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_112211);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_112220);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_112301);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_112310);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_113003);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_113012);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_113021);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_113030);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_113102);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_113111);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_113120);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_113201);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_113210);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_114002);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_114011);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_114020);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_114101);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_114110);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_115001);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_115010);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_200303);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_200312);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_200321);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_200330);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_200402);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_200411);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_200420);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_201203);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_201212);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_201221);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_201230);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_201302);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_201311);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_201320);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_202103);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_202112);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_202121);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_202130);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_202202);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_202211);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_202220);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_203003);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_203012);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_203021);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_203030);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_203102);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_203111);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_203120);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_204002);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_204011);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_204020);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_220202);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_220211);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_220220);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_220301);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_220310);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_220400);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_221102);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_221111);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_221120);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_221201);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_221210);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_221300);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_222002);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_222011);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_222020);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_222101);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_222110);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_222200);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_223001);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_223010);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_223100);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_224000);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_310202);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_310211);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_310220);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_310301);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_310310);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_311102);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_311111);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_311120);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_311201);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_311210);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_312002);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_312011);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_312020);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_312101);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_312110);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_313001);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_313010);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_330101);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_330110);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_330200);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_331001);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_331010);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_331100);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_332000);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_400202);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_400211);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_400220);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_401102);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_401111);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_401120);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_402002);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_402011);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_402020);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_420101);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_420110);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_420200);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_421001);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_421010);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_421100);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_422000);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_440000);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_510101);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_510110);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_511001);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_511010);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_530000);
   CalculatorEE.SetMECalculator(GetDecomposed2e2muBackground_620000);
   CalculatorEE.SetMECalculator(CalculateUUbarBackground2e2muDirectional);

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

   double l1pt, l1eta, l1phi;   int l1id;
   double l2pt, l2eta, l2phi;   int l2id;
   double l3pt, l3eta, l3phi;   int l3id;
   double l4pt, l4eta, l4phi;   int l4id;
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
   ProgressBar Bar(cerr, StartEvent, min(EndEvent, EventCount));
   Bar.SetStyle(6);
   for(int iEvent = StartEvent; iEvent < EventCount && iEvent <= EndEvent; iEvent++)
   {
      Tree->GetEntry(iEvent);

      if(EventCount < 1000 || iEvent % (EventCount / 1000) == 0)
      {
         Bar.Update(iEvent);
         Bar.Print();
      }

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

      vector<double> Integral, IntegralUp, IntegralDown, IntegralWide, IntegralNarrow;
      vector<double> AlternativeIntegral, AlternativeIntegralUp, AlternativeIntegralDown,
         AlternativeIntegralWide, AlternativeIntegralNarrow;

      if(PassBaselineCut(Angles) == true)
      {
         if(l1id == 11 && l3id == 11)
         {
            Integral = CalculatorEE.PassThroughMode(Angles);
            // IntegralUp = CalculatorUpEE.PassThroughMode(Angles);
            // IntegralDown = CalculatorDownEE.PassThroughMode(Angles);
            // IntegralWide = CalculatorWideEE.PassThroughMode(Angles);
            // IntegralNarrow = CalculatorNarrowEE.PassThroughMode(Angles);

            AlternativeIntegral = CalculatorEE.PassThroughMode(AlternativeAngles);
            // AlternativeIntegralUp = CalculatorUpEE.PassThroughMode(AlternativeAngles);
            // AlternativeIntegralDown = CalculatorDownEE.PassThroughMode(AlternativeAngles);
            // AlternativeIntegralWide = CalculatorWideEE.PassThroughMode(AlternativeAngles);
            // AlternativeIntegralNarrow = CalculatorNarrowEE.PassThroughMode(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
            {
               Integral[i] = (Integral[i] + AlternativeIntegral[i]);
               // IntegralUp[i] = (IntegralUp[i] + AlternativeIntegralUp[i]);
               // IntegralDown[i] = (IntegralDown[i] + AlternativeIntegralDown[i]);
               // IntegralWide[i] = (IntegralWide[i] + AlternativeIntegralWide[i]);
               // IntegralNarrow[i] = (IntegralNarrow[i] + AlternativeIntegralNarrow[i]);
            }
         }
         if(l1id == 11 && l3id == 13)
         {
            Integral = CalculatorEM.PassThroughMode(Angles);
            // IntegralUp = CalculatorUpEM.PassThroughMode(Angles);
            // IntegralDown = CalculatorDownEM.PassThroughMode(Angles);
            // IntegralWide = CalculatorWideEM.PassThroughMode(Angles);
            // IntegralNarrow = CalculatorNarrowEM.PassThroughMode(Angles);
         }
         if(l1id == 13 && l3id == 11)
         {
            Integral = CalculatorME.PassThroughMode(Angles);
            // IntegralUp = CalculatorUpME.PassThroughMode(Angles);
            // IntegralDown = CalculatorDownME.PassThroughMode(Angles);
            // IntegralWide = CalculatorWideME.PassThroughMode(Angles);
            // IntegralNarrow = CalculatorNarrowME.PassThroughMode(Angles);
         }
         if(l1id == 13 && l3id == 13)
         {
            Integral = CalculatorMM.PassThroughMode(Angles);
            // IntegralUp = CalculatorUpMM.PassThroughMode(Angles);
            // IntegralDown = CalculatorDownMM.PassThroughMode(Angles);
            // IntegralWide = CalculatorWideMM.PassThroughMode(Angles);
            // IntegralNarrow = CalculatorNarrowMM.PassThroughMode(Angles);
            
            AlternativeIntegral = CalculatorMM.PassThroughMode(AlternativeAngles);
            // AlternativeIntegralUp = CalculatorUpMM.PassThroughMode(AlternativeAngles);
            // AlternativeIntegralDown = CalculatorDownMM.PassThroughMode(AlternativeAngles);
            // AlternativeIntegralWide = CalculatorWideMM.PassThroughMode(AlternativeAngles);
            // AlternativeIntegralNarrow = CalculatorNarrowMM.PassThroughMode(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
            {
               Integral[i] = (Integral[i] + AlternativeIntegral[i]);
               // IntegralUp[i] = (IntegralUp[i] + AlternativeIntegralUp[i]);
               // IntegralDown[i] = (IntegralDown[i] + AlternativeIntegralDown[i]);
               // IntegralWide[i] = (IntegralWide[i] + AlternativeIntegralWide[i]);
               // IntegralNarrow[i] = (IntegralNarrow[i] + AlternativeIntegralNarrow[i]);
            }
         }
      }
      else
         cout << "Didn't pass baseline cut!" << endl;

      // cout << setprecision(20);
      cout << FileName << " Central " << iEvent;
      for(int i = 0; i < (int)Integral.size(); i++)
         cout << " " << Integral[i];
      cout << endl;
      // cout << FileName << " LeptonUp " << iEvent;
      // for(int i = 0; i < (int)IntegralUp.size(); i++)
      //    cout << " " << IntegralUp[i];
      // cout << endl;
      // cout << FileName << " LeptonDown " << iEvent;
      // for(int i = 0; i < (int)IntegralDown.size(); i++)
      //    cout << " " << IntegralDown[i];
      // cout << endl;
      // cout << FileName << " LeptonWide " << iEvent;
      // for(int i = 0; i < (int)IntegralWide.size(); i++)
      //    cout << " " << IntegralWide[i];
      // cout << endl;
      // cout << FileName << " LeptonNarrow " << iEvent;
      // for(int i = 0; i < (int)IntegralNarrow.size(); i++)
      //    cout << " " << IntegralNarrow[i];
      // cout << endl;
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












