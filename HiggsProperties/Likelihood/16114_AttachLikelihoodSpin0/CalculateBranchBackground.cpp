#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Code/TauHelperFunctions3.h"
#include "Code/DrawRandom2.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateME.h"
#include "MEFunctions.h"
#include "Constants.h"

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
   PrintConstants();

   string FileName = "EventB.root";
   int StartEvent = 0;
   int EndEvent = 19;
   int StockM4lSeed = -1;
   string Energy = "13";

   if(argc <= 5)
   {
      cerr << "Usage: " << argv[0] << " FileWithTree StartEvent EndEvent StockM4lSeed Energy" << endl;
      return -1;
   }

   FileName = argv[1];
   StartEvent = atoi(argv[2]);
   EndEvent = atoi(argv[3]);
   StockM4lSeed = atoi(argv[4]);
   Energy = argv[5];

   StockM4l M4l(StockM4lSeed, 100000);

   // Setup calculators
   HybridCalculator CalculatorEEuubar, CalculatorMEuubar, CalculatorEMuubar, CalculatorMMuubar;
   HybridCalculator CalculatorEEddbar, CalculatorMEddbar, CalculatorEMddbar, CalculatorMMddbar;

   CalculatorEMuubar.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEMuubar.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorEMuubar.SetSmear12(SmearElectronCentral);
   CalculatorEMuubar.SetSmear34(SmearMuonCentral);
   CalculatorEMuubar.SetToleranceF(1e-6);
   CalculatorEMuubar.SetMaxDepthF(30);
   CalculatorEMuubar.SetExpansionOrder(2);
   CalculatorEMuubar.SetDoDeltaMH(false);
   CalculatorEMuubar.SetIgnorePhi(true);
   CalculatorEMuubar.SetApplyEfficiencyAtEnd(true);
   CalculatorEMuubar.SetIntegralCRange(0.75, 1.25);
   CalculatorEMuubar.SetAttractorStrength(2);
   CalculatorEMuubar.SetIntegralCStep(20);
   CalculatorEMuubar.SetSimpleMassIntegralStep(40);
   CalculatorEMuubar.SetSimpleMassIntegralWindow(30);
   CalculatorEMuubar.SetDoDiagonal(false);
   CalculatorEMuubar.SetFlatApproximation(false);
   CalculatorEMuubar.SetIncludeSwapping(true);
   CalculatorEMuubar.SetUseSmartCenter(true);

   CalculatorEMddbar = CalculatorEMuubar;

   if(Energy == "14")
      CalculatorEMuubar.SetPTYDensity(GetPTYDensityUUbar_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorEMuubar.SetPTYDensity(GetPTYDensityUUbar_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorEMuubar.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   if(Energy == "14")
      CalculatorEMddbar.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorEMddbar.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorEMddbar.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   CalculatorEMuubar.SetMECalculator(CalculateUbarUBackground2e2muDirectional);
   CalculatorEMddbar.SetMECalculator(CalculateDbarDBackground2e2muDirectional);
   // CalculatorEMuubar.SetMECalculator(CalculateUUbarBackground2e2muDirectional);
   // CalculatorEMddbar.SetMECalculator(CalculateDDbarBackground2e2muDirectional);

   CalculatorMEuubar = CalculatorEMuubar;
   CalculatorMEuubar.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorMEuubar.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorMEuubar.SetSmear12(SmearMuonCentral);
   CalculatorMEuubar.SetSmear34(SmearElectronCentral);
   CalculatorMEddbar = CalculatorEMddbar;
   CalculatorMEddbar.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorMEddbar.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorMEddbar.SetSmear12(SmearMuonCentral);
   CalculatorMEddbar.SetSmear34(SmearElectronCentral);

   CalculatorEEuubar.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEEuubar.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorEEuubar.SetSmear12(SmearElectronCentral);
   CalculatorEEuubar.SetSmear34(SmearElectronCentral);
   CalculatorEEuubar.SetToleranceF(1e-6);
   CalculatorEEuubar.SetMaxDepthF(30);
   CalculatorEEuubar.SetExpansionOrder(2);
   CalculatorEEuubar.SetDoDeltaMH(false);
   CalculatorEEuubar.SetIgnorePhi(true);
   CalculatorEEuubar.SetApplyEfficiencyAtEnd(true);
   CalculatorEEuubar.SetIntegralCRange(0.75, 1.25);
   CalculatorEEuubar.SetAttractorStrength(2);
   CalculatorEEuubar.SetIntegralCStep(20);
   CalculatorEEuubar.SetSimpleMassIntegralStep(40);
   CalculatorEEuubar.SetSimpleMassIntegralWindow(30);
   CalculatorEEuubar.SetDoDiagonal(false);
   CalculatorEEuubar.SetFlatApproximation(false);
   CalculatorEEuubar.SetIncludeSwapping(true);
   CalculatorEEuubar.SetUseSmartCenter(true);

   CalculatorEEddbar = CalculatorEEuubar;
   
   if(Energy == "14")
      CalculatorEEuubar.SetPTYDensity(GetPTYDensityUUbar_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorEEuubar.SetPTYDensity(GetPTYDensityUUbar_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorEEuubar.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   if(Energy == "14")
      CalculatorEEddbar.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorEEddbar.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorEEddbar.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   CalculatorEEuubar.SetMECalculator(CalculateUbarUBackground4eDirectional);
   CalculatorEEddbar.SetMECalculator(CalculateDbarDBackground4eDirectional);
   // CalculatorEEuubar.SetMECalculator(CalculateUUbarBackground4eDirectional);
   // CalculatorEEddbar.SetMECalculator(CalculateDDbarBackground4eDirectional);

   CalculatorMMuubar = CalculatorEEuubar;
   CalculatorMMuubar.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorMMuubar.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorMMuubar.SetSmear12(SmearMuonCentral);
   CalculatorMMuubar.SetSmear34(SmearMuonCentral);
   CalculatorMMddbar = CalculatorEEddbar;
   CalculatorMMddbar.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorMMddbar.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorMMddbar.SetSmear12(SmearMuonCentral);
   CalculatorMMddbar.SetSmear34(SmearMuonCentral);

   HybridCalculator CalculatorUpEMuubar, CalculatorUpMEuubar, CalculatorUpEEuubar, CalculatorUpMMuubar;
   HybridCalculator CalculatorDownEMuubar, CalculatorDownMEuubar, CalculatorDownEEuubar, CalculatorDownMMuubar;
   HybridCalculator CalculatorWideEMuubar, CalculatorWideMEuubar, CalculatorWideEEuubar, CalculatorWideMMuubar;
   HybridCalculator CalculatorNarrowEMuubar, CalculatorNarrowMEuubar, CalculatorNarrowEEuubar, CalculatorNarrowMMuubar;
   HybridCalculator CalculatorUpEMddbar, CalculatorUpMEddbar, CalculatorUpEEddbar, CalculatorUpMMddbar;
   HybridCalculator CalculatorDownEMddbar, CalculatorDownMEddbar, CalculatorDownEEddbar, CalculatorDownMMddbar;
   HybridCalculator CalculatorWideEMddbar, CalculatorWideMEddbar, CalculatorWideEEddbar, CalculatorWideMMddbar;
   HybridCalculator CalculatorNarrowEMddbar, CalculatorNarrowMEddbar, CalculatorNarrowEEddbar, CalculatorNarrowMMddbar;

   CalculatorUpEMuubar = CalculatorEMuubar;               CalculatorDownEMuubar = CalculatorEMuubar;
   CalculatorUpEMuubar.SetSmear12(SmearElectronUp);       CalculatorDownEMuubar.SetSmear12(SmearElectronDown);
   CalculatorUpEMuubar.SetSmear34(SmearMuonUp);           CalculatorDownEMuubar.SetSmear34(SmearMuonDown);
   CalculatorUpMEuubar = CalculatorMEuubar;               CalculatorDownMEuubar = CalculatorMEuubar;
   CalculatorUpMEuubar.SetSmear12(SmearMuonUp);           CalculatorDownMEuubar.SetSmear12(SmearMuonDown);
   CalculatorUpMEuubar.SetSmear34(SmearElectronUp);       CalculatorDownMEuubar.SetSmear34(SmearElectronDown);
   CalculatorUpEEuubar = CalculatorEEuubar;               CalculatorDownEEuubar = CalculatorEEuubar;
   CalculatorUpEEuubar.SetSmear12(SmearElectronUp);       CalculatorDownEEuubar.SetSmear12(SmearElectronDown);
   CalculatorUpEEuubar.SetSmear34(SmearElectronUp);       CalculatorDownEEuubar.SetSmear34(SmearElectronDown);
   CalculatorUpMMuubar = CalculatorMMuubar;               CalculatorDownMMuubar = CalculatorMMuubar;
   CalculatorUpMMuubar.SetSmear12(SmearMuonUp);           CalculatorDownMMuubar.SetSmear12(SmearMuonDown);
   CalculatorUpMMuubar.SetSmear34(SmearMuonUp);           CalculatorDownMMuubar.SetSmear34(SmearMuonDown);

   CalculatorWideEMuubar = CalculatorEMuubar;             CalculatorNarrowEMuubar = CalculatorEMuubar;
   CalculatorWideEMuubar.SetSmear12(SmearElectronWide);   CalculatorNarrowEMuubar.SetSmear12(SmearElectronNarrow);
   CalculatorWideEMuubar.SetSmear34(SmearMuonWide);       CalculatorNarrowEMuubar.SetSmear34(SmearMuonNarrow);
   CalculatorWideMEuubar = CalculatorMEuubar;             CalculatorNarrowMEuubar = CalculatorMEuubar;
   CalculatorWideMEuubar.SetSmear12(SmearMuonWide);       CalculatorNarrowMEuubar.SetSmear12(SmearMuonNarrow);
   CalculatorWideMEuubar.SetSmear34(SmearElectronWide);   CalculatorNarrowMEuubar.SetSmear34(SmearElectronNarrow);
   CalculatorWideEEuubar = CalculatorEEuubar;             CalculatorNarrowEEuubar = CalculatorEEuubar;
   CalculatorWideEEuubar.SetSmear12(SmearElectronWide);   CalculatorNarrowEEuubar.SetSmear12(SmearElectronNarrow);
   CalculatorWideEEuubar.SetSmear34(SmearElectronWide);   CalculatorNarrowEEuubar.SetSmear34(SmearElectronNarrow);
   CalculatorWideMMuubar = CalculatorMMuubar;             CalculatorNarrowMMuubar = CalculatorMMuubar;
   CalculatorWideMMuubar.SetSmear12(SmearMuonWide);       CalculatorNarrowMMuubar.SetSmear12(SmearMuonNarrow);
   CalculatorWideMMuubar.SetSmear34(SmearMuonWide);       CalculatorNarrowMMuubar.SetSmear34(SmearMuonNarrow);

   CalculatorUpEMddbar = CalculatorEMddbar;               CalculatorDownEMddbar = CalculatorEMddbar;
   CalculatorUpEMddbar.SetSmear12(SmearElectronUp);       CalculatorDownEMddbar.SetSmear12(SmearElectronDown);
   CalculatorUpEMddbar.SetSmear34(SmearMuonUp);           CalculatorDownEMddbar.SetSmear34(SmearMuonDown);
   CalculatorUpMEddbar = CalculatorMEddbar;               CalculatorDownMEddbar = CalculatorMEddbar;
   CalculatorUpMEddbar.SetSmear12(SmearMuonUp);           CalculatorDownMEddbar.SetSmear12(SmearMuonDown);
   CalculatorUpMEddbar.SetSmear34(SmearElectronUp);       CalculatorDownMEddbar.SetSmear34(SmearElectronDown);
   CalculatorUpEEddbar = CalculatorEEddbar;               CalculatorDownEEddbar = CalculatorEEddbar;
   CalculatorUpEEddbar.SetSmear12(SmearElectronUp);       CalculatorDownEEddbar.SetSmear12(SmearElectronDown);
   CalculatorUpEEddbar.SetSmear34(SmearElectronUp);       CalculatorDownEEddbar.SetSmear34(SmearElectronDown);
   CalculatorUpMMddbar = CalculatorMMddbar;               CalculatorDownMMddbar = CalculatorMMddbar;
   CalculatorUpMMddbar.SetSmear12(SmearMuonUp);           CalculatorDownMMddbar.SetSmear12(SmearMuonDown);
   CalculatorUpMMddbar.SetSmear34(SmearMuonUp);           CalculatorDownMMddbar.SetSmear34(SmearMuonDown);

   CalculatorWideEMddbar = CalculatorEMddbar;             CalculatorNarrowEMddbar = CalculatorEMddbar;
   CalculatorWideEMddbar.SetSmear12(SmearElectronWide);   CalculatorNarrowEMddbar.SetSmear12(SmearElectronNarrow);
   CalculatorWideEMddbar.SetSmear34(SmearMuonWide);       CalculatorNarrowEMddbar.SetSmear34(SmearMuonNarrow);
   CalculatorWideMEddbar = CalculatorMEddbar;             CalculatorNarrowMEddbar = CalculatorMEddbar;
   CalculatorWideMEddbar.SetSmear12(SmearMuonWide);       CalculatorNarrowMEddbar.SetSmear12(SmearMuonNarrow);
   CalculatorWideMEddbar.SetSmear34(SmearElectronWide);   CalculatorNarrowMEddbar.SetSmear34(SmearElectronNarrow);
   CalculatorWideEEddbar = CalculatorEEddbar;             CalculatorNarrowEEddbar = CalculatorEEddbar;
   CalculatorWideEEddbar.SetSmear12(SmearElectronWide);   CalculatorNarrowEEddbar.SetSmear12(SmearElectronNarrow);
   CalculatorWideEEddbar.SetSmear34(SmearElectronWide);   CalculatorNarrowEEddbar.SetSmear34(SmearElectronNarrow);
   CalculatorWideMMddbar = CalculatorMMddbar;             CalculatorNarrowMMddbar = CalculatorMMddbar;
   CalculatorWideMMddbar.SetSmear12(SmearMuonWide);       CalculatorNarrowMMddbar.SetSmear12(SmearMuonNarrow);
   CalculatorWideMMddbar.SetSmear34(SmearMuonWide);       CalculatorNarrowMMddbar.SetSmear34(SmearMuonNarrow);

   // CalculatorEMuubar.TestOutput();
   // CalculatorMEuubar.TestOutput();
   // CalculatorEEuubar.TestOutput();
   // CalculatorMMuubar.TestOutput();

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

      if(StockM4lSeed <= 0)   // background!
      {
         if(iEvent % 2 == 1)
         {
            Leptons.Lepton11[3] = -Leptons.Lepton11[3];
            Leptons.Lepton12[3] = -Leptons.Lepton12[3];
            Leptons.Lepton21[3] = -Leptons.Lepton21[3];
            Leptons.Lepton22[3] = -Leptons.Lepton22[3];
         }
      }

      if(l1id == l3id)
         Leptons = Leptons.ReorderLeptons4e();
      else
         Leptons = Leptons.ReorderLeptons2e2mu();
      
      double Ratio = 1;
      EventParameters Angles = ConvertVectorsToAnglesRoberto(Leptons);
      if(StockM4lSeed > 0)
      {
         Ratio = M4l[iEvent] / Angles.HMass;
         Angles.HMass = Angles.HMass * Ratio;
         Angles.ZMass = Angles.ZMass * Ratio;
         Angles.Z2Mass = Angles.Z2Mass * Ratio;
         Leptons = ConvertAnglesToVectorsRoberto(Angles);
      }

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

      LeptonVectors LeptonsFlip = Leptons;
      LeptonVectors AlternativeLeptonsFlip = AlternativeLeptons;

      LeptonsFlip.Lepton11[3] = -LeptonsFlip.Lepton11[3];
      LeptonsFlip.Lepton12[3] = -LeptonsFlip.Lepton12[3];
      LeptonsFlip.Lepton21[3] = -LeptonsFlip.Lepton21[3];
      LeptonsFlip.Lepton22[3] = -LeptonsFlip.Lepton22[3];
      AlternativeLeptonsFlip.Lepton11[3] = -AlternativeLeptonsFlip.Lepton11[3];
      AlternativeLeptonsFlip.Lepton12[3] = -AlternativeLeptonsFlip.Lepton12[3];
      AlternativeLeptonsFlip.Lepton21[3] = -AlternativeLeptonsFlip.Lepton21[3];
      AlternativeLeptonsFlip.Lepton22[3] = -AlternativeLeptonsFlip.Lepton22[3];

      EventParameters AnglesFlip = ConvertVectorsToAnglesRoberto(LeptonsFlip);
      EventParameters AlternativeAnglesFlip = ConvertVectorsToAnglesRoberto(AlternativeLeptonsFlip);

      vector<double> Integraluubar, IntegralFlipuubar;
      vector<double> AlternativeIntegraluubar, AlternativeIntegralFlipuubar;
      vector<double> Integralddbar, IntegralFlipddbar;
      vector<double> AlternativeIntegralddbar, AlternativeIntegralFlipddbar;

      double RecoJ12 = VolumeElement::EstimateVolumeFull5(Angles);
      double SortedRecoJ12 = VolumeElement::EstimateVolumeFull5(AlternativeAngles);

      if(PassBaselineCut(Angles) == true)
      {
         if(abs(l1id) == 11 && abs(l3id) == 11)
         {
            Integraluubar = CalculatorEEuubar.PassThroughMode(Angles);
            IntegralFlipuubar = CalculatorEEuubar.PassThroughMode(AnglesFlip);
            AlternativeIntegraluubar = CalculatorEEuubar.PassThroughMode(AlternativeAngles);
            AlternativeIntegralFlipuubar = CalculatorEEuubar.PassThroughMode(AlternativeAnglesFlip);
            Integralddbar = CalculatorEEddbar.PassThroughMode(Angles);
            IntegralFlipddbar = CalculatorEEddbar.PassThroughMode(AnglesFlip);
            AlternativeIntegralddbar = CalculatorEEddbar.PassThroughMode(AlternativeAngles);
            AlternativeIntegralFlipddbar = CalculatorEEddbar.PassThroughMode(AlternativeAnglesFlip);

            for(int i = 0; i < (int)Integraluubar.size(); i++)
            {
               Integraluubar[i] = (Integraluubar[i] + AlternativeIntegraluubar[i] * SortedRecoJ12 / RecoJ12);
               IntegralFlipuubar[i] = (IntegralFlipuubar[i] + AlternativeIntegralFlipuubar[i] * SortedRecoJ12 / RecoJ12);
            }
            for(int i = 0; i < (int)Integralddbar.size(); i++)
            {
               Integralddbar[i] = (Integralddbar[i] + AlternativeIntegralddbar[i] * SortedRecoJ12 / RecoJ12);
               IntegralFlipddbar[i] = (IntegralFlipddbar[i] + AlternativeIntegralFlipddbar[i] * SortedRecoJ12 / RecoJ12);
            }
         }
         else if(abs(l1id) == 11 && abs(l3id) == 13)
         {
            Integraluubar = CalculatorEMuubar.PassThroughMode(Angles);
            IntegralFlipuubar = CalculatorEMuubar.PassThroughMode(AnglesFlip);
            Integralddbar = CalculatorEMddbar.PassThroughMode(Angles);
            IntegralFlipddbar = CalculatorEMddbar.PassThroughMode(AnglesFlip);
         }
         else if(abs(l1id) == 13 && abs(l3id) == 11)
         {
            Integraluubar = CalculatorMEuubar.PassThroughMode(Angles);
            IntegralFlipuubar = CalculatorMEuubar.PassThroughMode(AnglesFlip);
            Integralddbar = CalculatorMEddbar.PassThroughMode(Angles);
            IntegralFlipddbar = CalculatorMEddbar.PassThroughMode(AnglesFlip);
         }
         else if(abs(l1id) == 13 && abs(l3id) == 13)
         {
            Integraluubar = CalculatorMMuubar.PassThroughMode(Angles);
            IntegralFlipuubar = CalculatorMMuubar.PassThroughMode(AnglesFlip);
            AlternativeIntegraluubar = CalculatorMMuubar.PassThroughMode(AlternativeAngles);
            AlternativeIntegralFlipuubar = CalculatorMMuubar.PassThroughMode(AlternativeAnglesFlip);
            Integralddbar = CalculatorMMddbar.PassThroughMode(Angles);
            IntegralFlipddbar = CalculatorMMddbar.PassThroughMode(AnglesFlip);
            AlternativeIntegralddbar = CalculatorMMddbar.PassThroughMode(AlternativeAngles);
            AlternativeIntegralFlipddbar = CalculatorMMddbar.PassThroughMode(AlternativeAnglesFlip);

            for(int i = 0; i < (int)Integraluubar.size(); i++)
            {
               Integraluubar[i] = (Integraluubar[i] + AlternativeIntegraluubar[i] * SortedRecoJ12 / RecoJ12);
               IntegralFlipuubar[i] = (IntegralFlipuubar[i] + AlternativeIntegralFlipuubar[i] * SortedRecoJ12 / RecoJ12);
            }
            for(int i = 0; i < (int)Integralddbar.size(); i++)
            {
               Integralddbar[i] = (Integralddbar[i] + AlternativeIntegralddbar[i] * SortedRecoJ12 / RecoJ12);
               IntegralFlipddbar[i] = (IntegralFlipddbar[i] + AlternativeIntegralFlipddbar[i] * SortedRecoJ12 / RecoJ12);
            }
         }
         else
            cout << "MEOW!" << endl;
      }
      else
         cout << "Didn't pass baseline cut!" << endl;

      cout << setprecision(20);
      cout << FileName << " BCentral " << iEvent;
      for(int i = 0; i < (int)Integraluubar.size(); i++)
         cout << " " << Integraluubar[i] + IntegralFlipuubar[i];
      for(int i = 0; i < (int)Integralddbar.size(); i++)
         cout << " " << Integralddbar[i] + IntegralFlipddbar[i];
      cout << endl;

      // if(iEvent < 10)
      // {
      //    cerr << Leptons << " " << LeptonsFlip << endl;
      //    cerr << Angles << " " << AnglesFlip << endl;
      //    cerr << iEvent << " " << Integraluubar[0] << " " << IntegralFlipuubar[0] << endl;
      // }
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













