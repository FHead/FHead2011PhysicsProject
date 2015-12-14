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
double CalculateAverageEfficiency(EventParameters &Event,
   double (*E12)(double, double, double), double(*E34)(double, double, double),
   double (*PTY)(double, double, double));

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
   HybridCalculator CalculatorEE[4], CalculatorME[4], CalculatorEM[4], CalculatorMM[4];

   CalculatorEM[0].SetEfficiency12(GetFlatEfficiency);
   CalculatorEM[0].SetEfficiency34(GetFlatEfficiency);
   CalculatorEM[0].SetSmear12(SmearElectronCentral);
   CalculatorEM[0].SetSmear34(SmearMuonCentral);
   CalculatorEM[0].SetToleranceF(1e-6);
   CalculatorEM[0].SetMaxDepthF(30);
   CalculatorEM[0].SetExpansionOrder(2);
   CalculatorEM[0].SetDoDeltaMH(false);
   CalculatorEM[0].SetIgnorePhi(true);
   CalculatorEM[0].SetApplyEfficiencyAtEnd(true);
   CalculatorEM[0].SetIntegralCRange(0.75, 1.25);
   CalculatorEM[0].SetAttractorStrength(2);
   CalculatorEM[0].SetIntegralCStep(20);
   CalculatorEM[0].SetSimpleMassIntegralStep(40);
   CalculatorEM[0].SetSimpleMassIntegralWindow(30);
   CalculatorEM[0].SetDoDiagonal(false);
   CalculatorEM[0].SetFlatApproximation(false);
   CalculatorEM[0].SetIncludeSwapping(true);
   CalculatorEM[0].SetUseSmartCenter(true);

   CalculatorEM[1] = CalculatorEM[0];
   CalculatorEM[2] = CalculatorEM[0];
   CalculatorEM[3] = CalculatorEM[0];

   CalculatorEM[0].SetMECalculator(CalculateUUbarBackground2e2muDirectionalFlatS);
   CalculatorEM[1].SetMECalculator(CalculateUbarUBackground2e2muDirectionalFlatS);
   CalculatorEM[2].SetMECalculator(CalculateDDbarBackground2e2muDirectionalFlatS);
   CalculatorEM[3].SetMECalculator(CalculateDbarDBackground2e2muDirectionalFlatS);

   for(int i = 0; i < 4; i++)
   {
      CalculatorME[i] = CalculatorEM[i];
      CalculatorME[i].SetSmear12(SmearMuonCentral);
      CalculatorME[i].SetSmear34(SmearElectronCentral);
   }

   CalculatorEE[0].SetEfficiency12(GetFlatEfficiency);
   CalculatorEE[0].SetEfficiency34(GetFlatEfficiency);
   CalculatorEE[0].SetSmear12(SmearElectronCentral);
   CalculatorEE[0].SetSmear34(SmearElectronCentral);
   CalculatorEE[0].SetToleranceF(1e-6);
   CalculatorEE[0].SetMaxDepthF(30);
   CalculatorEE[0].SetExpansionOrder(2);
   CalculatorEE[0].SetDoDeltaMH(false);
   CalculatorEE[0].SetIgnorePhi(true);
   CalculatorEE[0].SetApplyEfficiencyAtEnd(true);
   CalculatorEE[0].SetIntegralCRange(0.75, 1.25);
   CalculatorEE[0].SetAttractorStrength(2);
   CalculatorEE[0].SetIntegralCStep(20);
   CalculatorEE[0].SetSimpleMassIntegralStep(40);
   CalculatorEE[0].SetSimpleMassIntegralWindow(30);
   CalculatorEE[0].SetDoDiagonal(false);
   CalculatorEE[0].SetFlatApproximation(false);
   CalculatorEE[0].SetIncludeSwapping(true);
   CalculatorEE[0].SetUseSmartCenter(true);

   CalculatorEE[1] = CalculatorEE[0];
   CalculatorEE[2] = CalculatorEE[0];
   CalculatorEE[3] = CalculatorEE[0];

   CalculatorEE[0].SetMECalculator(CalculateUUbarBackground4eDirectionalFlatS);
   CalculatorEE[1].SetMECalculator(CalculateUbarUBackground4eDirectionalFlatS);
   CalculatorEE[2].SetMECalculator(CalculateDDbarBackground4eDirectionalFlatS);
   CalculatorEE[3].SetMECalculator(CalculateDbarDBackground4eDirectionalFlatS);

   for(int i = 0; i < 4; i++)
   {
      CalculatorMM[i] = CalculatorEE[i];
      CalculatorMM[i].SetSmear12(SmearMuonCentral);
      CalculatorMM[i].SetSmear34(SmearMuonCentral);
   }

   HybridCalculator CalculatorUpEM[4], CalculatorUpME[4], CalculatorUpEE[4], CalculatorUpMM[4];
   HybridCalculator CalculatorDownEM[4], CalculatorDownME[4], CalculatorDownEE[4], CalculatorDownMM[4];
   HybridCalculator CalculatorWideEM[4], CalculatorWideME[4], CalculatorWideEE[4], CalculatorWideMM[4];
   HybridCalculator CalculatorNarrowEM[4], CalculatorNarrowME[4], CalculatorNarrowEE[4], CalculatorNarrowMM[4];

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
   }

   // CalculatorEM[0].TestOutput();
   // CalculatorME[0].TestOutput();
   // CalculatorEE[0].TestOutput();
   // CalculatorMM[0].TestOutput();

   vector<double (*)(double, double, double)> PTYDensity2e2mu, PTYDensityHard2e2mu, PTYDensitySoft2e2mu,
      PTYDensityForward2e2mu, PTYDensityCentral2e2mu;
   vector<double (*)(double, double, double)> PTYDensity4e, PTYDensityHard4e, PTYDensitySoft4e,
      PTYDensityForward4e, PTYDensityCentral4e;

   PTYDensity2e2mu.push_back(GetPTYDensity8TeVBackgroundUUbar2e2mu);
   PTYDensity2e2mu.push_back(GetPTYDensity8TeVBackgroundUbarU2e2mu);
   PTYDensity2e2mu.push_back(GetPTYDensity8TeVBackgroundDDbar2e2mu);
   PTYDensity2e2mu.push_back(GetPTYDensity8TeVBackgroundDbarD2e2mu);
   PTYDensityHard2e2mu.push_back(GetPTYDensity8TeVBackgroundUUbarHard2e2mu);
   PTYDensityHard2e2mu.push_back(GetPTYDensity8TeVBackgroundUbarUHard2e2mu);
   PTYDensityHard2e2mu.push_back(GetPTYDensity8TeVBackgroundDDbarHard2e2mu);
   PTYDensityHard2e2mu.push_back(GetPTYDensity8TeVBackgroundDbarDHard2e2mu);
   PTYDensitySoft2e2mu.push_back(GetPTYDensity8TeVBackgroundUUbarSoft2e2mu);
   PTYDensitySoft2e2mu.push_back(GetPTYDensity8TeVBackgroundUbarUSoft2e2mu);
   PTYDensitySoft2e2mu.push_back(GetPTYDensity8TeVBackgroundDDbarSoft2e2mu);
   PTYDensitySoft2e2mu.push_back(GetPTYDensity8TeVBackgroundDbarDSoft2e2mu);
   PTYDensityForward2e2mu.push_back(GetPTYDensity8TeVBackgroundUUbarForward2e2mu);
   PTYDensityForward2e2mu.push_back(GetPTYDensity8TeVBackgroundUbarUForward2e2mu);
   PTYDensityForward2e2mu.push_back(GetPTYDensity8TeVBackgroundDDbarForward2e2mu);
   PTYDensityForward2e2mu.push_back(GetPTYDensity8TeVBackgroundDbarDForward2e2mu);
   PTYDensityCentral2e2mu.push_back(GetPTYDensity8TeVBackgroundUUbarCentral2e2mu);
   PTYDensityCentral2e2mu.push_back(GetPTYDensity8TeVBackgroundUbarUCentral2e2mu);
   PTYDensityCentral2e2mu.push_back(GetPTYDensity8TeVBackgroundDDbarCentral2e2mu);
   PTYDensityCentral2e2mu.push_back(GetPTYDensity8TeVBackgroundDbarDCentral2e2mu);

   PTYDensity4e.push_back(GetPTYDensity8TeVBackgroundUUbar4e);
   PTYDensity4e.push_back(GetPTYDensity8TeVBackgroundUbarU4e);
   PTYDensity4e.push_back(GetPTYDensity8TeVBackgroundDDbar4e);
   PTYDensity4e.push_back(GetPTYDensity8TeVBackgroundDbarD4e);
   PTYDensityHard4e.push_back(GetPTYDensity8TeVBackgroundUUbarHard4e);
   PTYDensityHard4e.push_back(GetPTYDensity8TeVBackgroundUbarUHard4e);
   PTYDensityHard4e.push_back(GetPTYDensity8TeVBackgroundDDbarHard4e);
   PTYDensityHard4e.push_back(GetPTYDensity8TeVBackgroundDbarDHard4e);
   PTYDensitySoft4e.push_back(GetPTYDensity8TeVBackgroundUUbarSoft4e);
   PTYDensitySoft4e.push_back(GetPTYDensity8TeVBackgroundUbarUSoft4e);
   PTYDensitySoft4e.push_back(GetPTYDensity8TeVBackgroundDDbarSoft4e);
   PTYDensitySoft4e.push_back(GetPTYDensity8TeVBackgroundDbarDSoft4e);
   PTYDensityForward4e.push_back(GetPTYDensity8TeVBackgroundUUbarForward4e);
   PTYDensityForward4e.push_back(GetPTYDensity8TeVBackgroundUbarUForward4e);
   PTYDensityForward4e.push_back(GetPTYDensity8TeVBackgroundDDbarForward4e);
   PTYDensityForward4e.push_back(GetPTYDensity8TeVBackgroundDbarDForward4e);
   PTYDensityCentral4e.push_back(GetPTYDensity8TeVBackgroundUUbarCentral4e);
   PTYDensityCentral4e.push_back(GetPTYDensity8TeVBackgroundUbarUCentral4e);
   PTYDensityCentral4e.push_back(GetPTYDensity8TeVBackgroundDDbarCentral4e);
   PTYDensityCentral4e.push_back(GetPTYDensity8TeVBackgroundDbarDCentral4e);

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

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      if(l1id < 0)
      {
         swap(Leptons.Lepton11, Leptons.Lepton12);
         l1id = -l1id;
      }
      if(l3id < 0)
      {
         swap(Leptons.Lepton21, Leptons.Lepton22);
         l3id = -l3id;
      }

      // swap(Leptons.Lepton11, Leptons.Lepton21);
      // swap(Leptons.Lepton12, Leptons.Lepton22);

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

      vector<double> Integral[4], IntegralUp[4], IntegralDown[4], IntegralWide[4], IntegralNarrow[4];
      vector<double> AlternativeIntegral[4], AlternativeIntegralUp[4], AlternativeIntegralDown[4],
         AlternativeIntegralWide[4], AlternativeIntegralNarrow[4];
      vector<double> TotalIntegral[4], TotalIntegralUp[4], TotalIntegralDown[4], TotalIntegralWide[4], TotalIntegralNarrow[4];
      vector<double> Efficiency(4), EfficiencyUp(4), EfficiencyDown(4), EfficiencyWide(4), EfficiencyNarrow(4),
         EfficiencyHard(4), EfficiencySoft(4), EfficiencyCentral(4), EfficiencyForward(4);

      if(PassBaselineCut(Angles) == true)
      {
         for(int iInitial = 0; iInitial < 4; iInitial++)
         {
            if(l1id == 11 && l3id == 11)
            {
               Efficiency[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensity4e[iInitial]);
               EfficiencyUp[iInitial] = Efficiency[iInitial];
               EfficiencyDown[iInitial] = Efficiency[iInitial];
               EfficiencyWide[iInitial] = Efficiency[iInitial];
               EfficiencyNarrow[iInitial] = Efficiency[iInitial];
               EfficiencyHard[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensityHard4e[iInitial]);
               EfficiencySoft[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensitySoft4e[iInitial]);
               EfficiencyCentral[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensityCentral4e[iInitial]);
               EfficiencyForward[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensityForward4e[iInitial]);
            }
            if(l1id == 11 && l3id == 13)
            {
               Efficiency[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensity2e2mu[iInitial]);
               EfficiencyUp[iInitial] = Efficiency[iInitial];
               EfficiencyDown[iInitial] = Efficiency[iInitial];
               EfficiencyWide[iInitial] = Efficiency[iInitial];
               EfficiencyNarrow[iInitial] = Efficiency[iInitial];
               EfficiencyHard[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensityHard2e2mu[iInitial]);
               EfficiencySoft[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensitySoft2e2mu[iInitial]);
               EfficiencyCentral[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensityCentral2e2mu[iInitial]);
               EfficiencyForward[iInitial] = CalculateAverageEfficiency(Angles,
                  GetElectronEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensityForward2e2mu[iInitial]);
            }
            if(l1id == 13 && l3id == 11)
            {
               Efficiency[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensity2e2mu[iInitial]);
               EfficiencyUp[iInitial] = Efficiency[iInitial];
               EfficiencyDown[iInitial] = Efficiency[iInitial];
               EfficiencyWide[iInitial] = Efficiency[iInitial];
               EfficiencyNarrow[iInitial] = Efficiency[iInitial];
               EfficiencyHard[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensityHard2e2mu[iInitial]);
               EfficiencySoft[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensitySoft2e2mu[iInitial]);
               EfficiencyCentral[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensityCentral2e2mu[iInitial]);
               EfficiencyForward[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetElectronEfficiencyPtEta8TeV,
                  PTYDensityForward2e2mu[iInitial]);
            }
            if(l1id == 13 && l3id == 13)
            {
               Efficiency[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensity4e[iInitial]);
               EfficiencyUp[iInitial] = Efficiency[iInitial];
               EfficiencyDown[iInitial] = Efficiency[iInitial];
               EfficiencyWide[iInitial] = Efficiency[iInitial];
               EfficiencyNarrow[iInitial] = Efficiency[iInitial];
               EfficiencyHard[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensityHard4e[iInitial]);
               EfficiencySoft[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensitySoft4e[iInitial]);
               EfficiencyCentral[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensityCentral4e[iInitial]);
               EfficiencyForward[iInitial] = CalculateAverageEfficiency(Angles,
                  GetMuonEfficiencyPtEta8TeV, GetMuonEfficiencyPtEta8TeV,
                  PTYDensityForward4e[iInitial]);
            }
         }

         for(int iHat = 0; iHat < 4; iHat++)
         {
            if(iHat == 0)
               Angles.PTH = 50, Angles.YH = 0, Angles.PhiOffset = 0,
               AlternativeAngles.PTH = 50, AlternativeAngles.YH = 0, AlternativeAngles.PhiOffset = 0;
            if(iHat == 1)
               Angles.PTH = 50, Angles.YH = 0, Angles.PhiOffset = PI,
               AlternativeAngles.PTH = 50, AlternativeAngles.YH = 0, AlternativeAngles.PhiOffset = PI;
            if(iHat == 2)
               Angles.PTH = 100, Angles.YH = 0, Angles.PhiOffset = 0,
               AlternativeAngles.PTH = 100, AlternativeAngles.YH = 0, AlternativeAngles.PhiOffset = 0;
            if(iHat == 3)
               Angles.PTH = 100, Angles.YH = 0, Angles.PhiOffset = PI,
               AlternativeAngles.PTH = 100, AlternativeAngles.YH = 0, AlternativeAngles.PhiOffset = PI;
            
            for(int iInitial = 0; iInitial < 4; iInitial++)
            {
               if(abs(l1id) == 11 && abs(l3id) == 11)
               {
                  Integral[iInitial] = CalculatorEE[iInitial].SimpleMassIntegral(Angles);
                  IntegralUp[iInitial] = CalculatorUpEE[iInitial].PassThroughMode(Angles);
                  IntegralDown[iInitial] = CalculatorDownEE[iInitial].PassThroughMode(Angles);
                  IntegralWide[iInitial] = CalculatorWideEE[iInitial].PassThroughMode(Angles);
                  IntegralNarrow[iInitial] = CalculatorNarrowEE[iInitial].PassThroughMode(Angles);

                  AlternativeIntegral[iInitial] = CalculatorEE[iInitial].SimpleMassIntegral(AlternativeAngles);
                  AlternativeIntegralUp[iInitial] = CalculatorUpEE[iInitial].PassThroughMode(AlternativeAngles);
                  AlternativeIntegralDown[iInitial] = CalculatorDownEE[iInitial].PassThroughMode(AlternativeAngles);
                  AlternativeIntegralWide[iInitial] = CalculatorWideEE[iInitial].PassThroughMode(AlternativeAngles);
                  AlternativeIntegralNarrow[iInitial] = CalculatorNarrowEE[iInitial].PassThroughMode(AlternativeAngles);

                  for(int i = 0; i < (int)Integral[iInitial].size(); i++)
                  {
                     Integral[iInitial][i] = (Integral[iInitial][i] + AlternativeIntegral[iInitial][i]);
                     IntegralUp[iInitial][i] = (IntegralUp[iInitial][i] + AlternativeIntegralUp[iInitial][i]);
                     IntegralDown[iInitial][i] = (IntegralDown[iInitial][i] + AlternativeIntegralDown[iInitial][i]);
                     IntegralWide[iInitial][i] = (IntegralWide[iInitial][i] + AlternativeIntegralWide[iInitial][i]);
                     IntegralNarrow[iInitial][i] = (IntegralNarrow[iInitial][i] + AlternativeIntegralNarrow[iInitial][i]);
                  }
               }
               else if(abs(l1id) == 11 && abs(l3id) == 13)
               {
                  Integral[iInitial] = CalculatorEM[iInitial].SimpleMassIntegral(Angles);
                  IntegralUp[iInitial] = CalculatorUpEM[iInitial].PassThroughMode(Angles);
                  IntegralDown[iInitial] = CalculatorDownEM[iInitial].PassThroughMode(Angles);
                  IntegralWide[iInitial] = CalculatorWideEM[iInitial].PassThroughMode(Angles);
                  IntegralNarrow[iInitial] = CalculatorNarrowEM[iInitial].PassThroughMode(Angles);
               }
               else if(abs(l1id) == 13 && abs(l3id) == 11)
               {
                  Integral[iInitial] = CalculatorME[iInitial].SimpleMassIntegral(Angles);
                  IntegralUp[iInitial] = CalculatorUpME[iInitial].PassThroughMode(Angles);
                  IntegralDown[iInitial] = CalculatorDownME[iInitial].PassThroughMode(Angles);
                  IntegralWide[iInitial] = CalculatorWideME[iInitial].PassThroughMode(Angles);
                  IntegralNarrow[iInitial] = CalculatorNarrowME[iInitial].PassThroughMode(Angles);
               }
               else if(abs(l1id) == 13 && abs(l3id) == 13)
               {
                  Integral[iInitial] = CalculatorMM[iInitial].SimpleMassIntegral(Angles);
                  IntegralUp[iInitial] = CalculatorUpMM[iInitial].PassThroughMode(Angles);
                  IntegralDown[iInitial] = CalculatorDownMM[iInitial].PassThroughMode(Angles);
                  IntegralWide[iInitial] = CalculatorWideMM[iInitial].PassThroughMode(Angles);
                  IntegralNarrow[iInitial] = CalculatorNarrowMM[iInitial].PassThroughMode(Angles);

                  AlternativeIntegral[iInitial] = CalculatorMM[iInitial].SimpleMassIntegral(AlternativeAngles);
                  AlternativeIntegralUp[iInitial] = CalculatorUpMM[iInitial].PassThroughMode(AlternativeAngles);
                  AlternativeIntegralDown[iInitial] = CalculatorDownMM[iInitial].PassThroughMode(AlternativeAngles);
                  AlternativeIntegralWide[iInitial] = CalculatorWideMM[iInitial].PassThroughMode(AlternativeAngles);
                  AlternativeIntegralNarrow[iInitial] = CalculatorNarrowMM[iInitial].PassThroughMode(AlternativeAngles);

                  for(int i = 0; i < (int)Integral[iInitial].size(); i++)
                  {
                     Integral[iInitial][i] = (Integral[iInitial][i] + AlternativeIntegral[iInitial][i]);
                     IntegralUp[iInitial][i] = (IntegralUp[iInitial][i] + AlternativeIntegralUp[iInitial][i]);
                     IntegralDown[iInitial][i] = (IntegralDown[iInitial][i] + AlternativeIntegralDown[iInitial][i]);
                     IntegralWide[iInitial][i] = (IntegralWide[iInitial][i] + AlternativeIntegralWide[iInitial][i]);
                     IntegralNarrow[iInitial][i] = (IntegralNarrow[iInitial][i] + AlternativeIntegralNarrow[iInitial][i]);
                  }
               }
               else
                  cout << "MEOW!" << endl;
            }

            if(iHat == 0)
            {
               for(int iInitial = 0; iInitial < 4; iInitial++)
               {
                  TotalIntegral[iInitial] = Integral[iInitial];
                  TotalIntegralUp[iInitial] = IntegralUp[iInitial];
                  TotalIntegralDown[iInitial] = IntegralDown[iInitial];
                  TotalIntegralWide[iInitial] = IntegralWide[iInitial];
                  TotalIntegralNarrow[iInitial] = IntegralNarrow[iInitial];
               }
            }
            else
            {
               for(int iInitial = 0; iInitial < 4; iInitial++)
               {
                  for(int i = 0; i < (int)Integral[iInitial].size(); i++)
                  {
                     TotalIntegral[iInitial][i] = TotalIntegral[iInitial][i] + Integral[iInitial][i];
                     TotalIntegralUp[iInitial][i] = TotalIntegralUp[iInitial][i] + IntegralUp[iInitial][i];
                     TotalIntegralDown[iInitial][i] = TotalIntegralDown[iInitial][i] + IntegralDown[iInitial][i];
                     TotalIntegralWide[iInitial][i] = TotalIntegralWide[iInitial][i] + IntegralWide[iInitial][i];
                     TotalIntegralNarrow[iInitial][i] = TotalIntegralNarrow[iInitial][i] + IntegralNarrow[iInitial][i];
                  }
               }
            }
         }
      }
      else
         cout << "Didn't pass baseline cut!" << endl;

      cout << setprecision(20);
      cout << FileName << " BCentral " << iEvent;
      for(int i = 0; i < (int)Integral[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + Integral[iInitial][i] * Efficiency[iInitial];
         cout << " " << Total;
      }
      cout << endl;
      cout << FileName << " BLeptonUp " << iEvent;
      for(int i = 0; i < (int)IntegralUp[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + IntegralUp[iInitial][i] * EfficiencyUp[iInitial];
         cout << " " << Total;
      }
      cout << endl;
      cout << FileName << " BLeptonDown " << iEvent;
      for(int i = 0; i < (int)IntegralDown[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + IntegralDown[iInitial][i] * EfficiencyDown[iInitial];
         cout << " " << Total;
      }
      cout << endl;
      cout << FileName << " BLeptonWide " << iEvent;
      for(int i = 0; i < (int)IntegralWide[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + IntegralWide[iInitial][i] * EfficiencyWide[iInitial];
         cout << " " << Total;
      }
      cout << endl;
      cout << FileName << " BLeptonNarrow " << iEvent;
      for(int i = 0; i < (int)IntegralNarrow[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + IntegralNarrow[iInitial][i] * EfficiencyNarrow[iInitial];
         cout << " " << Total;
      }
      cout << endl;
      cout << FileName << " BSpectrumHard " << iEvent;
      for(int i = 0; i < (int)Integral[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + Integral[iInitial][i] * EfficiencyHard[iInitial];
         cout << " " << Total;
      }
      cout << endl;
      cout << FileName << " BSpectrumSoft " << iEvent;
      for(int i = 0; i < (int)Integral[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + Integral[iInitial][i] * EfficiencySoft[iInitial];
         cout << " " << Total;
      }
      cout << endl;
      cout << FileName << " BSpectrumCentral " << iEvent;
      for(int i = 0; i < (int)Integral[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + Integral[iInitial][i] * EfficiencyCentral[iInitial];
         cout << " " << Total;
      }
      cout << endl;
      cout << FileName << " BSpectrumForward " << iEvent;
      for(int i = 0; i < (int)Integral[0].size(); i++)
      {
         double Total = 0;
         for(int iInitial = 0; iInitial < 4; iInitial++)
            Total = Total + Integral[iInitial][i] * EfficiencyForward[iInitial];
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

   // if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   // if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   // if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   // if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   // if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   // if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}

double CalculateAverageEfficiency(EventParameters &Event,
   double (*E12)(double, double, double), double (*E34)(double, double, double),
   double (*PTY)(double, double, double))
{
   int NumberOfTries = 10000;
   double Total = 0;

   for(int i = 0; i < NumberOfTries; i++)
   {
      double PT = DrawRandom(0, 500);
      double Y = DrawGaussian(0, 2);

      Event.PTH = PT;
      Event.YH = Y;

      LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

      FourVector &L11 = Leptons.Lepton11;
      FourVector &L12 = Leptons.Lepton12;
      FourVector &L21 = Leptons.Lepton21;
      FourVector &L22 = Leptons.Lepton22;

      double Efficiency = 1;
      Efficiency = Efficiency * E12(L11.GetPT(), L11[3] / L11.GetP(), L11.GetPhi());
      Efficiency = Efficiency * E12(L12.GetPT(), L12[3] / L12.GetP(), L12.GetPhi());
      Efficiency = Efficiency * E34(L21.GetPT(), L21[3] / L21.GetP(), L21.GetPhi());
      Efficiency = Efficiency * E34(L22.GetPT(), L22[3] / L22.GetP(), L22.GetPhi());

      Total = Total + Efficiency * PTY(PT, Y, Event.HMass * Event.HMass) / exp(-Y * Y / (2 * 2 * 2));
   }

   return Total / NumberOfTries;
}













