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
   CalculatorEM.SetToleranceF(1e-6);
   CalculatorEM.SetMaxDepthF(30);
   CalculatorEM.SetExpansionOrder(2);
   CalculatorEM.SetDoDeltaMH(false);
   CalculatorEM.SetIgnorePhi(true);
   CalculatorEM.SetApplyEfficiencyAtEnd(true);
   CalculatorEM.SetIntegralCRange(0.75, 1.25);
   CalculatorEM.SetPTYDensity(GetPTYDensity8TeVBackground);
   CalculatorEM.SetAttractorStrength(2);
   CalculatorEM.SetIntegralCStep(20);
   CalculatorEM.SetSimpleMassIntegralStep(40);
   CalculatorEM.SetSimpleMassIntegralWindow(30);
   CalculatorEM.SetDoDiagonal(false);
   CalculatorEM.SetFlatApproximation(false);
   CalculatorEM.SetIncludeSwapping(true);
   CalculatorEM.SetUseSmartCenter(true);

   CalculatorEM.SetMECalculator(CalculateBackground2e2mu_Roberto12253);

   CalculatorME = CalculatorEM;
   CalculatorME.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorME.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorME.SetSmear12(SmearMuonCentral);
   CalculatorME.SetSmear34(SmearElectronCentral);
 
   CalculatorEE.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEE.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorEE.SetSmear12(SmearElectronCentral);
   CalculatorEE.SetSmear34(SmearElectronCentral);
   CalculatorEE.SetToleranceF(1e-6);
   CalculatorEE.SetMaxDepthF(30);
   CalculatorEE.SetExpansionOrder(2);
   CalculatorEE.SetDoDeltaMH(false);
   CalculatorEE.SetIgnorePhi(true);
   CalculatorEE.SetApplyEfficiencyAtEnd(true);
   CalculatorEE.SetIntegralCRange(0.75, 1.25);
   CalculatorEM.SetPTYDensity(GetPTYDensity8TeVBackground);
   CalculatorEE.SetAttractorStrength(2);
   CalculatorEE.SetIntegralCStep(20);
   CalculatorEE.SetSimpleMassIntegralStep(40);
   CalculatorEE.SetSimpleMassIntegralWindow(30);
   CalculatorEE.SetDoDiagonal(false);
   CalculatorEE.SetFlatApproximation(false);
   CalculatorEE.SetIncludeSwapping(true);
   CalculatorEE.SetUseSmartCenter(true);

   CalculatorEE.SetMECalculator(CalculateBackground4e);

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

   CalculatorHardEM = CalculatorEM;      CalculatorHardEM.SetPTYDensity(GetPTYDensity8TeVBackgroundHard);
   CalculatorHardME = CalculatorME;      CalculatorHardME.SetPTYDensity(GetPTYDensity8TeVBackgroundHard);
   CalculatorHardEE = CalculatorEE;      CalculatorHardEE.SetPTYDensity(GetPTYDensity8TeVBackgroundHard);
   CalculatorHardMM = CalculatorMM;      CalculatorHardMM.SetPTYDensity(GetPTYDensity8TeVBackgroundHard);

   CalculatorSoftEM = CalculatorEM;      CalculatorSoftEM.SetPTYDensity(GetPTYDensity8TeVBackgroundSoft);
   CalculatorSoftME = CalculatorME;      CalculatorSoftME.SetPTYDensity(GetPTYDensity8TeVBackgroundSoft);
   CalculatorSoftEE = CalculatorEE;      CalculatorSoftEE.SetPTYDensity(GetPTYDensity8TeVBackgroundSoft);
   CalculatorSoftMM = CalculatorMM;      CalculatorSoftMM.SetPTYDensity(GetPTYDensity8TeVBackgroundSoft);
   
   CalculatorCentralEM = CalculatorEM;   CalculatorCentralEM.SetPTYDensity(GetPTYDensity8TeVBackgroundCentral);
   CalculatorCentralME = CalculatorME;   CalculatorCentralME.SetPTYDensity(GetPTYDensity8TeVBackgroundCentral);
   CalculatorCentralEE = CalculatorEE;   CalculatorCentralEE.SetPTYDensity(GetPTYDensity8TeVBackgroundCentral);
   CalculatorCentralMM = CalculatorMM;   CalculatorCentralMM.SetPTYDensity(GetPTYDensity8TeVBackgroundCentral);

   CalculatorForwardEM = CalculatorEM;   CalculatorForwardEM.SetPTYDensity(GetPTYDensity8TeVBackgroundForward);
   CalculatorForwardME = CalculatorME;   CalculatorForwardME.SetPTYDensity(GetPTYDensity8TeVBackgroundForward);
   CalculatorForwardEE = CalculatorEE;   CalculatorForwardEE.SetPTYDensity(GetPTYDensity8TeVBackgroundForward);
   CalculatorForwardMM = CalculatorMM;   CalculatorForwardMM.SetPTYDensity(GetPTYDensity8TeVBackgroundForward);
   
   CalculatorEM.TestOutput();
   CalculatorME.TestOutput();
   CalculatorEE.TestOutput();
   CalculatorMM.TestOutput();

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

      vector<double> Integral, IntegralUp, IntegralDown, IntegralWide, IntegralNarrow,
         IntegralHard, IntegralSoft, IntegralCentral, IntegralForward;
      vector<double> AlternativeIntegral, AlternativeIntegralUp, AlternativeIntegralDown,
         AlternativeIntegralWide, AlternativeIntegralNarrow, AlternativeIntegralHard,
         AlternativeIntegralSoft, AlternativeIntegralCentral, AlternativeIntegralForward;

      if(PassBaselineCut(Angles) == true)
      {
         if(abs(l1id) == 11 && abs(l3id) == 11)
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
            
            AlternativeIntegral = CalculatorEE.SimpleMassIntegral(AlternativeAngles);             
            AlternativeIntegralUp = CalculatorUpEE.SimpleMassIntegral(AlternativeAngles);         
            AlternativeIntegralDown = CalculatorDownEE.SimpleMassIntegral(AlternativeAngles);     
            AlternativeIntegralWide = CalculatorWideEE.SimpleMassIntegral(AlternativeAngles);     
            AlternativeIntegralNarrow = CalculatorNarrowEE.SimpleMassIntegral(AlternativeAngles); 
            AlternativeIntegralHard = CalculatorHardEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralSoft = CalculatorSoftEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralForward = CalculatorForwardEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralCentral = CalculatorCentralEE.SimpleMassIntegral(AlternativeAngles);

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
            }
         }
         else if(abs(l1id) == 11 && abs(l3id) == 13)
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
         }
         else if(abs(l1id) == 13 && abs(l3id) == 11)
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
         }
         else if(abs(l1id) == 13 && abs(l3id) == 13)
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

            AlternativeIntegral = CalculatorMM.SimpleMassIntegral(AlternativeAngles);             
            AlternativeIntegralUp = CalculatorUpMM.SimpleMassIntegral(AlternativeAngles);         
            AlternativeIntegralDown = CalculatorDownMM.SimpleMassIntegral(AlternativeAngles);     
            AlternativeIntegralWide = CalculatorWideMM.SimpleMassIntegral(AlternativeAngles);     
            AlternativeIntegralNarrow = CalculatorNarrowMM.SimpleMassIntegral(AlternativeAngles); 
            AlternativeIntegralHard = CalculatorHardMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralSoft = CalculatorSoftMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralForward = CalculatorForwardMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralCentral = CalculatorCentralMM.SimpleMassIntegral(AlternativeAngles);

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
            }
         }
         else
            cout << "MEOW!" << endl;
      }
      else
         cout << "Didn't pass baseline cut!" << endl;

      cout << setprecision(20);
      cout << FileName << " BCentral " << iEvent;
      for(int i = 0; i < (int)Integral.size(); i++)
         cout << " " << Integral[i];
      cout << endl;
      cout << FileName << " BLeptonUp " << iEvent;
      for(int i = 0; i < (int)IntegralUp.size(); i++)
         cout << " " << IntegralUp[i];
      cout << endl;
      cout << FileName << " BLeptonDown " << iEvent;
      for(int i = 0; i < (int)IntegralDown.size(); i++)
         cout << " " << IntegralDown[i];
      cout << endl;
      cout << FileName << " BLeptonWide " << iEvent;
      for(int i = 0; i < (int)IntegralWide.size(); i++)
         cout << " " << IntegralWide[i];
      cout << endl;
      cout << FileName << " BLeptonNarrow " << iEvent;
      for(int i = 0; i < (int)IntegralNarrow.size(); i++)
         cout << " " << IntegralNarrow[i];
      cout << endl;
      cout << FileName << " BSpectrumHard " << iEvent;
      for(int i = 0; i < (int)IntegralHard.size(); i++)
         cout << " " << IntegralHard[i];
      cout << endl;
      cout << FileName << " BSpectrumSoft " << iEvent;
      for(int i = 0; i < (int)IntegralSoft.size(); i++)
         cout << " " << IntegralSoft[i];
      cout << endl;
      cout << FileName << " BSpectrumCentral " << iEvent;
      for(int i = 0; i < (int)IntegralCentral.size(); i++)
         cout << " " << IntegralCentral[i];
      cout << endl;
      cout << FileName << " BSpectrumForward " << iEvent;
      for(int i = 0; i < (int)IntegralForward.size(); i++)
         cout << " " << IntegralForward[i];
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













