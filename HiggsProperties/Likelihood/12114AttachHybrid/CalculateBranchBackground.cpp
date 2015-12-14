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

#include "LeptonResponse.h"
#include "HybridCalculator.h"

int main(int argc, char *argv[]);
double CalculateA1RA1RSignal(LeptonVectors &Leptons);
double CalculateA2RA2RSignal(LeptonVectors &Leptons);
double CalculateA2IA2ISignal(LeptonVectors &Leptons);
double CalculateA3RA3RSignal(LeptonVectors &Leptons);
double CalculateA3IA3ISignal(LeptonVectors &Leptons);
double CalculateA1RA2RSignal(LeptonVectors &Leptons);
double CalculateA1RA2ISignal(LeptonVectors &Leptons);
double CalculateA1RA3RSignal(LeptonVectors &Leptons);
double CalculateA1RA3ISignal(LeptonVectors &Leptons);
double CalculateA2RA2ISignal(LeptonVectors &Leptons);
double CalculateA2RA3RSignal(LeptonVectors &Leptons);
double CalculateA2RA3ISignal(LeptonVectors &Leptons);
double CalculateA2IA3RSignal(LeptonVectors &Leptons);
double CalculateA2IA3ISignal(LeptonVectors &Leptons);
double CalculateA3RA3ISignal(LeptonVectors &Leptons);
double CalculateBackground(LeptonVectors &Leptons);
double CalculateA1RA1RSignal4e(LeptonVectors &Leptons);
double CalculateA2RA2RSignal4e(LeptonVectors &Leptons);
double CalculateA2IA2ISignal4e(LeptonVectors &Leptons);
double CalculateA3RA3RSignal4e(LeptonVectors &Leptons);
double CalculateA3IA3ISignal4e(LeptonVectors &Leptons);
double CalculateA1RA2RSignal4e(LeptonVectors &Leptons);
double CalculateA1RA2ISignal4e(LeptonVectors &Leptons);
double CalculateA1RA3RSignal4e(LeptonVectors &Leptons);
double CalculateA1RA3ISignal4e(LeptonVectors &Leptons);
double CalculateA2RA2ISignal4e(LeptonVectors &Leptons);
double CalculateA2RA3RSignal4e(LeptonVectors &Leptons);
double CalculateA2RA3ISignal4e(LeptonVectors &Leptons);
double CalculateA2IA3RSignal4e(LeptonVectors &Leptons);
double CalculateA2IA3ISignal4e(LeptonVectors &Leptons);
double CalculateA3RA3ISignal4e(LeptonVectors &Leptons);
double CalculateBackground4e(LeptonVectors &Leptons);
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
   CalculatorEM.SetSimpleMassIntegralStep(40);
   CalculatorEM.SetSimpleMassIntegralWindow(20);
   CalculatorEM.SetExpansionOrder(1);
   CalculatorEM.SetDoDeltaMH(false);
   CalculatorEM.SetIgnorePhi(true);

   CalculatorEM.SetMECalculator(CalculateBackground);

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
   CalculatorEE.SetSimpleMassIntegralStep(40);
   CalculatorEE.SetSimpleMassIntegralWindow(20);
   CalculatorEE.SetExpansionOrder(1);
   CalculatorEE.SetDoDeltaMH(false);
   CalculatorEE.SetIgnorePhi(true);

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
   
   // Setup tree
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");

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

      vector<double> Integral, IntegralUp, IntegralDown, IntegralWide, IntegralNarrow;
      vector<double> AlternativeIntegral, AlternativeIntegralUp, AlternativeIntegralDown, AlternativeIntegralWide, AlternativeIntegralNarrow;

      if(PassBaselineCut(Angles) == true)
      {
         if(abs(l1id) == 11 && abs(l3id) == 11)
         {
            Integral = CalculatorEE.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpEE.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownEE.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideEE.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowEE.SimpleMassIntegral(Angles);
            AlternativeIntegral = CalculatorEE.SimpleMassIntegral(AlternativeAngles);             
            AlternativeIntegralUp = CalculatorUpEE.SimpleMassIntegral(AlternativeAngles);         
            AlternativeIntegralDown = CalculatorDownEE.SimpleMassIntegral(AlternativeAngles);     
            AlternativeIntegralWide = CalculatorWideEE.SimpleMassIntegral(AlternativeAngles);     
            AlternativeIntegralNarrow = CalculatorNarrowEE.SimpleMassIntegral(AlternativeAngles); 

            for(int i = 0; i < (int)Integral.size(); i++)
            {
               Integral[i] = (Integral[i] + AlternativeIntegral[i]) / 2;
               IntegralUp[i] = (IntegralUp[i] + AlternativeIntegralUp[i]) / 2;
               IntegralDown[i] = (IntegralDown[i] + AlternativeIntegralDown[i]) / 2;
               IntegralWide[i] = (IntegralWide[i] + AlternativeIntegralWide[i]) / 2;
               IntegralNarrow[i] = (IntegralNarrow[i] + AlternativeIntegralNarrow[i]) / 2;
            }
         }
         if(abs(l1id) == 11 && abs(l3id) == 13)
         {
            Integral = CalculatorEM.SimpleMassIntegral(Angles);              
            IntegralUp = CalculatorUpEM.SimpleMassIntegral(Angles);          
            IntegralDown = CalculatorDownEM.SimpleMassIntegral(Angles);      
            IntegralWide = CalculatorWideEM.SimpleMassIntegral(Angles);      
            IntegralNarrow = CalculatorNarrowEM.SimpleMassIntegral(Angles);  
         }
         if(abs(l1id) == 13 && abs(l3id) == 11)
         {
            Integral = CalculatorME.SimpleMassIntegral(Angles);             
            IntegralUp = CalculatorUpME.SimpleMassIntegral(Angles);         
            IntegralDown = CalculatorDownME.SimpleMassIntegral(Angles);     
            IntegralWide = CalculatorWideME.SimpleMassIntegral(Angles);     
            IntegralNarrow = CalculatorNarrowME.SimpleMassIntegral(Angles); 
         }
         if(abs(l1id) == 13 && abs(l3id) == 13)
         {
            Integral = CalculatorMM.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpMM.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownMM.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideMM.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowMM.SimpleMassIntegral(Angles);
            AlternativeIntegral = CalculatorMM.SimpleMassIntegral(AlternativeAngles);             
            AlternativeIntegralUp = CalculatorUpMM.SimpleMassIntegral(AlternativeAngles);         
            AlternativeIntegralDown = CalculatorDownMM.SimpleMassIntegral(AlternativeAngles);     
            AlternativeIntegralWide = CalculatorWideMM.SimpleMassIntegral(AlternativeAngles);     
            AlternativeIntegralNarrow = CalculatorNarrowMM.SimpleMassIntegral(AlternativeAngles); 

            for(int i = 0; i < (int)Integral.size(); i++)
            {
               Integral[i] = (Integral[i] + AlternativeIntegral[i]) / 2;
               IntegralUp[i] = (IntegralUp[i] + AlternativeIntegralUp[i]) / 2;
               IntegralDown[i] = (IntegralDown[i] + AlternativeIntegralDown[i]) / 2;
               IntegralWide[i] = (IntegralWide[i] + AlternativeIntegralWide[i]) / 2;
               IntegralNarrow[i] = (IntegralNarrow[i] + AlternativeIntegralNarrow[i]) / 2;
            }
         }
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
   }

   // Cleanup
   File.Close();

   return 0;
}

double CalculateA1RA1RSignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_ahR_ahR(Leptons, 1, true);
}

double CalculateA2RA2RSignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZR_aZR(Leptons, 1, true);
}

double CalculateA2IA2ISignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZI_aZI(Leptons, 1, true);
}

double CalculateA3RA3RSignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZdR_aZdR(Leptons, 1, true);
}

double CalculateA3IA3ISignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZdI_aZdI(Leptons, 1, true);
}

double CalculateA1RA2RSignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZR_ahR(Leptons, 1, 1, true);
}

double CalculateA1RA2ISignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZI_ahR(Leptons, 1, 1, true);
}

double CalculateA1RA3RSignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZdR_ahR(Leptons, 1, 1, true);
}

double CalculateA1RA3ISignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZdI_ahR(Leptons, 1, 1, true);
}

double CalculateA2RA2ISignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZI_aZR(Leptons, 1, 1, true);
}

double CalculateA2RA3RSignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZR_aZdR(Leptons, 1, 1, true);
}

double CalculateA2RA3ISignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZR_aZdI(Leptons, 1, 1, true);
}

double CalculateA2IA3RSignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZI_aZdR(Leptons, 1, 1, true);
}

double CalculateA2IA3ISignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZI_aZdI(Leptons, 1, 1, true);
}

double CalculateA3RA3ISignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZdI_aZdR(Leptons, 1, 1, true);
}

double CalculateBackground(LeptonVectors &Leptons)
{
   double M4l = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   return (GetZZZAAABackground(Leptons, false, true) + GetZZZAAABackground(Leptons, true, true)
      + GetZZZAAABackground(Leptons, false, false) + GetZZZAAABackground(Leptons, true, false)) * M4l;
}

double CalculateA1RA1RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_ahR_ahR(Leptons, 1);
}

double CalculateA2RA2RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_aZR(Leptons, 1);
}

double CalculateA2IA2ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZI(Leptons, 1);
}

double CalculateA3RA3RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdR_aZdR(Leptons, 1);
}

double CalculateA3IA3ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdI_aZdI(Leptons, 1);
}

double CalculateA1RA2RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_ahR(Leptons, 1, 1);
}

double CalculateA1RA2ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_ahR(Leptons, 1, 1);
}

double CalculateA1RA3RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdR_ahR(Leptons, 1, 1);
}

double CalculateA1RA3ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdI_ahR(Leptons, 1, 1);
}

double CalculateA2RA2ISignal4e(LeptonVectors &Leptons)
{
   return 0;
   return GetGeneralScalar4e_aZI_aZR(Leptons, 1, 1);
}

double CalculateA2RA3RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_aZdR(Leptons, 1, 1);
}

double CalculateA2RA3ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_aZdI(Leptons, 1, 1);
}

double CalculateA2IA3RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZdR(Leptons, 1, 1);
}

double CalculateA2IA3ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZdI(Leptons, 1, 1);
}

double CalculateA3RA3ISignal4e(LeptonVectors &Leptons)
{
   return 0;
   return GetGeneralScalar4e_aZdI_aZdR(Leptons, 1, 1);
}

double CalculateBackground4e(LeptonVectors &Leptons)
{
   double M4l = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   return (GetZZZAAA4eBackground(Leptons, false, true) + GetZZZAAA4eBackground(Leptons, true, true)
      + GetZZZAAA4eBackground(Leptons, false, false) + GetZZZAAA4eBackground(Leptons, true, false)) * M4l;
}

double FlatEfficiency(double PT, double Eta, double Phi)
{
   Phi = 0;

   if(PT < 5)
      return 0;
   if(Eta < -0.983 || Eta > 0.983)   // this is actually pzp
      return 0;

   return 1;
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

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}













