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

   if(argc <= 4)
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
   HybridCalculator CalculatorEE[4], CalculatorME[4], CalculatorEM[4], CalculatorMM[4];

   CalculatorEM[0].SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEM[0].SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorEM[0].SetSmear12(SmearElectronCentral);
   CalculatorEM[0].SetSmear34(SmearMuonCentral);
   CalculatorEM[0].SetToleranceF(1e-6);
   CalculatorEM[0].SetMaxDepthF(30);
   CalculatorEM[0].SetExpansionOrder(2);
   CalculatorEM[0].SetDoDeltaMH(false);
   CalculatorEM[0].SetIgnorePhi(true);
   CalculatorEM[0].SetApplyEfficiencyAtEnd(true);
   CalculatorEM[0].SetIntegralCRange(0.25, 1.75);
   CalculatorEM[0].SetAttractorStrength(2);
   CalculatorEM[0].SetIntegralCStep(20);
   CalculatorEM[0].SetSimpleMassIntegralStep(40);
   CalculatorEM[0].SetSimpleMassIntegralWindow(30);
   CalculatorEM[0].SetDoDiagonal(false);
   CalculatorEM[0].SetFlatApproximation(false);
   CalculatorEM[0].SetIncludeSwapping(true);
   CalculatorEM[0].SetUseSmartCenter(true);
   CalculatorEM[0].SetDoReboot(true);
   CalculatorEM[0].SetUseSignalAverageExpansionPoint(true);
   CalculatorEM[0].SetUseBigRangeDerivatives(false);

   CalculatorEM[1] = CalculatorEM[0];
   CalculatorEM[2] = CalculatorEM[0];
   CalculatorEM[3] = CalculatorEM[0];

   CalculatorEM[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbar2e2mu);
   CalculatorEM[0].SetMECalculator(CalculateUUbarBackground2e2muDirectionalFlatS);
   CalculatorEM[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarU2e2mu);
   CalculatorEM[1].SetMECalculator(CalculateUbarUBackground2e2muDirectionalFlatS);
   CalculatorEM[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbar2e2mu);
   CalculatorEM[2].SetMECalculator(CalculateDDbarBackground2e2muDirectionalFlatS);
   CalculatorEM[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarD2e2mu);
   CalculatorEM[3].SetMECalculator(CalculateDbarDBackground2e2muDirectionalFlatS);

   for(int i = 0; i < 4; i++)
   {
      CalculatorME[i] = CalculatorEM[i];
      CalculatorME[i].SetEfficiency12(GetMuonEfficiencyPtEta);
      CalculatorME[i].SetEfficiency34(GetElectronEfficiencyPtEta);
      CalculatorME[i].SetSmear12(SmearMuonCentral);
      CalculatorME[i].SetSmear34(SmearElectronCentral);
   }

   CalculatorEE[0].SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEE[0].SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorEE[0].SetSmear12(SmearElectronCentral);
   CalculatorEE[0].SetSmear34(SmearElectronCentral);
   CalculatorEE[0].SetToleranceF(1e-6);
   CalculatorEE[0].SetMaxDepthF(30);
   CalculatorEE[0].SetExpansionOrder(2);
   CalculatorEE[0].SetDoDeltaMH(false);
   CalculatorEE[0].SetIgnorePhi(true);
   CalculatorEE[0].SetApplyEfficiencyAtEnd(true);
   CalculatorEE[0].SetIntegralCRange(0.25, 1.75);
   CalculatorEE[0].SetAttractorStrength(2);
   CalculatorEE[0].SetIntegralCStep(20);
   CalculatorEE[0].SetSimpleMassIntegralStep(40);
   CalculatorEE[0].SetSimpleMassIntegralWindow(30);
   CalculatorEE[0].SetDoDiagonal(false);
   CalculatorEE[0].SetFlatApproximation(false);
   CalculatorEE[0].SetIncludeSwapping(true);
   CalculatorEE[0].SetUseSmartCenter(true);
   CalculatorEE[0].SetDoReboot(true);
   CalculatorEE[0].SetUseSignalAverageExpansionPoint(true);
   CalculatorEE[0].SetUseBigRangeDerivatives(false);

   CalculatorEE[1] = CalculatorEE[0];
   CalculatorEE[2] = CalculatorEE[0];
   CalculatorEE[3] = CalculatorEE[0];

   CalculatorEE[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbar4e);
   CalculatorEE[0].SetMECalculator(CalculateUUbarBackground4eDirectionalFlatS);
   CalculatorEE[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarU4e);
   CalculatorEE[1].SetMECalculator(CalculateUbarUBackground4eDirectionalFlatS);
   CalculatorEE[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbar4e);
   CalculatorEE[2].SetMECalculator(CalculateDDbarBackground4eDirectionalFlatS);
   CalculatorEE[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarD4e);
   CalculatorEE[3].SetMECalculator(CalculateDbarDBackground4eDirectionalFlatS);

   for(int i = 0; i < 4; i++)
   {
      CalculatorMM[i] = CalculatorEE[i];
      CalculatorMM[i].SetEfficiency12(GetMuonEfficiencyPtEta);
      CalculatorMM[i].SetEfficiency34(GetMuonEfficiencyPtEta);
      CalculatorMM[i].SetSmear12(SmearMuonCentral);
      CalculatorMM[i].SetSmear34(SmearMuonCentral);
   }

   HybridCalculator CalculatorUpEM[4], CalculatorUpME[4], CalculatorUpEE[4], CalculatorUpMM[4];
   HybridCalculator CalculatorDownEM[4], CalculatorDownME[4], CalculatorDownEE[4], CalculatorDownMM[4];
   HybridCalculator CalculatorWideEM[4], CalculatorWideME[4], CalculatorWideEE[4], CalculatorWideMM[4];
   HybridCalculator CalculatorNarrowEM[4], CalculatorNarrowME[4], CalculatorNarrowEE[4], CalculatorNarrowMM[4];
   HybridCalculator CalculatorHardEM[4], CalculatorHardME[4], CalculatorHardEE[4], CalculatorHardMM[4];
   HybridCalculator CalculatorSoftEM[4], CalculatorSoftME[4], CalculatorSoftEE[4], CalculatorSoftMM[4];
   HybridCalculator CalculatorCentralEM[4], CalculatorCentralME[4], CalculatorCentralEE[4], CalculatorCentralMM[4];
   HybridCalculator CalculatorForwardEM[4], CalculatorForwardME[4], CalculatorForwardEE[4], CalculatorForwardMM[4];

   for(int i = 0; i < 4; i++)
   {
      CalculatorUpEM[i] = CalculatorEM[i];                  CalculatorDownEM[i] = CalculatorEM[i];
      CalculatorUpEM[i].SetSmear12(SmearElectronUp);        CalculatorDownEM[i].SetSmear12(SmearElectronDown);
      CalculatorUpEM[i].SetSmear34(SmearMuonUp);            CalculatorDownEM[i].SetSmear34(SmearMuonDown);
      CalculatorUpME[i] = CalculatorME[i];                  CalculatorDownME[i] = CalculatorME[i];
      CalculatorUpME[i].SetSmear12(SmearMuonUp);            CalculatorDownME[i].SetSmear12(SmearMuonDown);
      CalculatorUpME[i].SetSmear34(SmearElectronUp);        CalculatorDownME[i].SetSmear34(SmearElectronDown);
      CalculatorUpEE[i] = CalculatorEE[i];                  CalculatorDownEE[i] = CalculatorEE[i];
      CalculatorUpEE[i].SetSmear12(SmearElectronUp);        CalculatorDownEE[i].SetSmear12(SmearElectronDown);
      CalculatorUpEE[i].SetSmear34(SmearElectronUp);        CalculatorDownEE[i].SetSmear34(SmearElectronDown);
      CalculatorUpMM[i] = CalculatorMM[i];                  CalculatorDownMM[i] = CalculatorMM[i];
      CalculatorUpMM[i].SetSmear12(SmearMuonUp);            CalculatorDownMM[i].SetSmear12(SmearMuonDown);
      CalculatorUpMM[i].SetSmear34(SmearMuonUp);            CalculatorDownMM[i].SetSmear34(SmearMuonDown);

      CalculatorWideEM[i] = CalculatorEM[i];                CalculatorNarrowEM[i] = CalculatorEM[i];
      CalculatorWideEM[i].SetSmear12(SmearElectronWide);    CalculatorNarrowEM[i].SetSmear12(SmearElectronNarrow);
      CalculatorWideEM[i].SetSmear34(SmearMuonWide);        CalculatorNarrowEM[i].SetSmear34(SmearMuonNarrow);
      CalculatorWideME[i] = CalculatorME[i];                CalculatorNarrowME[i] = CalculatorME[i];
      CalculatorWideME[i].SetSmear12(SmearMuonWide);        CalculatorNarrowME[i].SetSmear12(SmearMuonNarrow);
      CalculatorWideME[i].SetSmear34(SmearElectronWide);    CalculatorNarrowME[i].SetSmear34(SmearElectronNarrow);
      CalculatorWideEE[i] = CalculatorEE[i];                CalculatorNarrowEE[i] = CalculatorEE[i];
      CalculatorWideEE[i].SetSmear12(SmearElectronWide);    CalculatorNarrowEE[i].SetSmear12(SmearElectronNarrow);
      CalculatorWideEE[i].SetSmear34(SmearElectronWide);    CalculatorNarrowEE[i].SetSmear34(SmearElectronNarrow);
      CalculatorWideMM[i] = CalculatorMM[i];                CalculatorNarrowMM[i] = CalculatorMM[i];
      CalculatorWideMM[i].SetSmear12(SmearMuonWide);        CalculatorNarrowMM[i].SetSmear12(SmearMuonNarrow);
      CalculatorWideMM[i].SetSmear34(SmearMuonWide);        CalculatorNarrowMM[i].SetSmear34(SmearMuonNarrow);

      CalculatorHardEM[i] = CalculatorEM[i];
      CalculatorHardME[i] = CalculatorME[i];
      CalculatorHardEE[i] = CalculatorEE[i];
      CalculatorHardMM[i] = CalculatorMM[i];

      CalculatorSoftEM[i] = CalculatorEM[i];
      CalculatorSoftME[i] = CalculatorME[i];
      CalculatorSoftEE[i] = CalculatorEE[i];
      CalculatorSoftMM[i] = CalculatorMM[i];

      CalculatorCentralEM[i] = CalculatorEM[i];
      CalculatorCentralME[i] = CalculatorME[i];
      CalculatorCentralEE[i] = CalculatorEE[i];
      CalculatorCentralMM[i] = CalculatorMM[i];

      CalculatorForwardEM[i] = CalculatorEM[i];
      CalculatorForwardME[i] = CalculatorME[i];
      CalculatorForwardEE[i] = CalculatorEE[i];
      CalculatorForwardMM[i] = CalculatorMM[i];
   }

   CalculatorHardEM[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarHard2e2mu);
   CalculatorHardME[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarHard2e2mu);
   CalculatorHardEE[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarHard4e);
   CalculatorHardMM[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarHard4e);
   CalculatorHardEM[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUHard2e2mu);
   CalculatorHardME[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUHard2e2mu);
   CalculatorHardEE[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUHard4e);
   CalculatorHardMM[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUHard4e);
   CalculatorHardEM[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarHard2e2mu);
   CalculatorHardME[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarHard2e2mu);
   CalculatorHardEE[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarHard4e);
   CalculatorHardMM[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarHard4e);
   CalculatorHardEM[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDHard2e2mu);
   CalculatorHardME[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDHard2e2mu);
   CalculatorHardEE[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDHard4e);
   CalculatorHardMM[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDHard4e);

   CalculatorSoftEM[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarSoft2e2mu);
   CalculatorSoftME[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarSoft2e2mu);
   CalculatorSoftEE[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarSoft4e);
   CalculatorSoftMM[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarSoft4e);
   CalculatorSoftEM[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUSoft2e2mu);
   CalculatorSoftME[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUSoft2e2mu);
   CalculatorSoftEE[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUSoft4e);
   CalculatorSoftMM[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUSoft4e);
   CalculatorSoftEM[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarSoft2e2mu);
   CalculatorSoftME[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarSoft2e2mu);
   CalculatorSoftEE[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarSoft4e);
   CalculatorSoftMM[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarSoft4e);
   CalculatorSoftEM[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDSoft2e2mu);
   CalculatorSoftME[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDSoft2e2mu);
   CalculatorSoftEE[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDSoft4e);
   CalculatorSoftMM[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDSoft4e);

   CalculatorForwardEM[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarForward2e2mu);
   CalculatorForwardME[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarForward2e2mu);
   CalculatorForwardEE[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarForward4e);
   CalculatorForwardMM[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarForward4e);
   CalculatorForwardEM[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUForward2e2mu);
   CalculatorForwardME[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUForward2e2mu);
   CalculatorForwardEE[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUForward4e);
   CalculatorForwardMM[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUForward4e);
   CalculatorForwardEM[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarForward2e2mu);
   CalculatorForwardME[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarForward2e2mu);
   CalculatorForwardEE[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarForward4e);
   CalculatorForwardMM[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarForward4e);
   CalculatorForwardEM[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDForward2e2mu);
   CalculatorForwardME[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDForward2e2mu);
   CalculatorForwardEE[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDForward4e);
   CalculatorForwardMM[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDForward4e);

   CalculatorCentralEM[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarCentral2e2mu);
   CalculatorCentralME[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarCentral2e2mu);
   CalculatorCentralEE[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarCentral4e);
   CalculatorCentralMM[0].SetPTYDensity(GetPTYDensity8TeVBackgroundUUbarCentral4e);
   CalculatorCentralEM[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUCentral2e2mu);
   CalculatorCentralME[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUCentral2e2mu);
   CalculatorCentralEE[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUCentral4e);
   CalculatorCentralMM[1].SetPTYDensity(GetPTYDensity8TeVBackgroundUbarUCentral4e);
   CalculatorCentralEM[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarCentral2e2mu);
   CalculatorCentralME[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarCentral2e2mu);
   CalculatorCentralEE[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarCentral4e);
   CalculatorCentralMM[2].SetPTYDensity(GetPTYDensity8TeVBackgroundDDbarCentral4e);
   CalculatorCentralEM[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDCentral2e2mu);
   CalculatorCentralME[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDCentral2e2mu);
   CalculatorCentralEE[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDCentral4e);
   CalculatorCentralMM[3].SetPTYDensity(GetPTYDensity8TeVBackgroundDbarDCentral4e);

   CalculatorEM[0].PrintSettings();
   CalculatorME[0].PrintSettings();

   string BranchName = "";
   HybridCalculator *ChosenEM, *ChosenME, *ChosenEE, *ChosenMM;
   switch(Branch)
   {
      case 0:
         BranchName = "BCentral";
         ChosenEM = CalculatorEM, ChosenME = CalculatorME;
         ChosenEE = CalculatorEE, ChosenMM = CalculatorMM;
         break;
      case 1:
         BranchName = "BLeptonUp";
         ChosenEM = CalculatorUpEM, ChosenME = CalculatorUpME;
         ChosenEE = CalculatorUpEE, ChosenMM = CalculatorUpMM;
         break;
      case 2:
         BranchName = "BLeptonDown";
         ChosenEM = CalculatorDownEM, ChosenME = CalculatorDownME;
         ChosenEE = CalculatorDownEE, ChosenMM = CalculatorDownMM;
         break;
      case 3:
         BranchName = "BLeptonWide";
         ChosenEM = CalculatorWideEM, ChosenME = CalculatorWideME;
         ChosenEE = CalculatorWideEE, ChosenMM = CalculatorWideMM;
         break;
      case 4:
         BranchName = "BLeptonNarrow";
         ChosenEM = CalculatorNarrowEM, ChosenME = CalculatorNarrowME;
         ChosenEE = CalculatorNarrowEE, ChosenMM = CalculatorNarrowMM;
         break;
      case 5:
         BranchName = "BSpectrumHard";
         ChosenEM = CalculatorHardEM, ChosenME = CalculatorHardME;
         ChosenEE = CalculatorHardEE, ChosenMM = CalculatorHardMM;
         break;
      case 6:
         BranchName = "BSpectrumSoft";
         ChosenEM = CalculatorSoftEM, ChosenME = CalculatorSoftME;
         ChosenEE = CalculatorSoftEE, ChosenMM = CalculatorSoftMM;
         break;
      case 7:
         BranchName = "BSpectrumForward";
         ChosenEM = CalculatorForwardEM, ChosenME = CalculatorForwardME;
         ChosenEE = CalculatorForwardEE, ChosenMM = CalculatorForwardMM;
         break;
      case 8:
         BranchName = "BSpectrumCentral";
         ChosenEM = CalculatorCentralEM, ChosenME = CalculatorCentralME;
         ChosenEE = CalculatorCentralEE, ChosenMM = CalculatorCentralMM;
         break;
      default:
         BranchName = "BCentral";
         ChosenEM = CalculatorEM, ChosenME = CalculatorME;
         ChosenEE = CalculatorEE, ChosenMM = CalculatorMM;
         break;
   }

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

      vector<double> Integral[4], AlternativeIntegral[4];

      if(PassBaselineCut(Angles) == true)
      {
         for(int iInitial = 0; iInitial < 4; iInitial++)
         {
            if(abs(l1id) == 11 && abs(l3id) == 11)
            {
               Integral[iInitial] = ChosenEE[iInitial].SimpleMassIntegral(Angles);
               AlternativeIntegral[iInitial] = ChosenEE[iInitial].SimpleMassIntegral(AlternativeAngles);

               for(int i = 0; i < (int)Integral[iInitial].size(); i++)
                  Integral[iInitial][i] = (Integral[iInitial][i] + AlternativeIntegral[iInitial][i]);
            }
            else if(abs(l1id) == 11 && abs(l3id) == 13)
               Integral[iInitial] = ChosenEM[iInitial].SimpleMassIntegral(Angles);
            else if(abs(l1id) == 13 && abs(l3id) == 11)
               Integral[iInitial] = ChosenME[iInitial].SimpleMassIntegral(Angles);
            else if(abs(l1id) == 13 && abs(l3id) == 13)
            {
               Integral[iInitial] = ChosenMM[iInitial].SimpleMassIntegral(Angles);
               AlternativeIntegral[iInitial] = ChosenMM[iInitial].SimpleMassIntegral(AlternativeAngles);

               for(int i = 0; i < (int)Integral[iInitial].size(); i++)
                  Integral[iInitial][i] = (Integral[iInitial][i] + AlternativeIntegral[iInitial][i]);
            }
            else
               cout << "MEOW!" << endl;
         }
      }
      else
         cout << "Didn't pass baseline cut!" << endl;

      cout << setprecision(20);
      cout << FileName << " " << BranchName << " " << iEvent;
      for(int i = 0; i < (int)Integral[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + Integral[iInitial][i];
         cout << " " << Total;
      }
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

   if(fabs(Leptons.Lepton11.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.5)   return false;

   if(max(Event.ZMass, Event.Z2Mass) < 40)   return false;
   if(min(Event.ZMass, Event.Z2Mass) < 12)   return false;

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













