#include <iostream>
using namespace std;

#include "TFile.h"
#include "TDirectoryFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions2.h"

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

int main(int argc, char *argv[])
{
   // Usage string
   if(argc <= 3)
   {
      cerr << "Usage: " << argv[0] << " FileWithTree StartEvent EndEvent" << endl;
      return -1;
   }

   string FileName = argv[1];
   int StartEvent = atoi(argv[2]);
   int EndEvent = atoi(argv[3]);

   // Setup calculator
   HybridCalculator Calculator, CalculatorUp, CalculatorDown, CalculatorWide, CalculatorNarrow;

   Calculator.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   Calculator.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   Calculator.SetSmear12(SmearMuonCentral);
   Calculator.SetSmear34(SmearMuonCentral);
   Calculator.SetToleranceF(1e-6);
   CalculatorUp.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   CalculatorUp.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   CalculatorUp.SetSmear12(SmearMuonUp);
   CalculatorUp.SetSmear34(SmearMuonUp);
   CalculatorUp.SetToleranceF(1e-6);
   CalculatorDown.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   CalculatorDown.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   CalculatorDown.SetSmear12(SmearMuonDown);
   CalculatorDown.SetSmear34(SmearMuonDown);
   CalculatorDown.SetToleranceF(1e-6);
   CalculatorWide.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   CalculatorWide.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   CalculatorWide.SetSmear12(SmearMuonWide);
   CalculatorWide.SetSmear34(SmearMuonWide);
   CalculatorWide.SetToleranceF(1e-6);
   CalculatorNarrow.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   CalculatorNarrow.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   CalculatorNarrow.SetSmear12(SmearMuonNarrow);
   CalculatorNarrow.SetSmear34(SmearMuonNarrow);
   CalculatorNarrow.SetToleranceF(1e-6);

   Calculator.SetMECalculator(CalculateBackground);
   Calculator.SetMECalculator(CalculateA1RA1RSignal);
   Calculator.SetMECalculator(CalculateA2RA2RSignal);
   Calculator.SetMECalculator(CalculateA2IA2ISignal);
   Calculator.SetMECalculator(CalculateA3RA3RSignal);
   Calculator.SetMECalculator(CalculateA3IA3ISignal);
   Calculator.SetMECalculator(CalculateA1RA2RSignal);
   Calculator.SetMECalculator(CalculateA1RA2ISignal);
   Calculator.SetMECalculator(CalculateA1RA3RSignal);
   Calculator.SetMECalculator(CalculateA1RA3ISignal);
   Calculator.SetMECalculator(CalculateA2RA2ISignal);
   Calculator.SetMECalculator(CalculateA2RA3RSignal);
   Calculator.SetMECalculator(CalculateA2RA3ISignal);
   Calculator.SetMECalculator(CalculateA2IA3RSignal);
   Calculator.SetMECalculator(CalculateA2IA3ISignal);
   Calculator.SetMECalculator(CalculateA3RA3ISignal);
   CalculatorUp.SetMECalculator(CalculateBackground);
   CalculatorUp.SetMECalculator(CalculateA1RA1RSignal);
   CalculatorUp.SetMECalculator(CalculateA2RA2RSignal);
   CalculatorUp.SetMECalculator(CalculateA2IA2ISignal);
   CalculatorUp.SetMECalculator(CalculateA3RA3RSignal);
   CalculatorUp.SetMECalculator(CalculateA3IA3ISignal);
   CalculatorUp.SetMECalculator(CalculateA1RA2RSignal);
   CalculatorUp.SetMECalculator(CalculateA1RA2ISignal);
   CalculatorUp.SetMECalculator(CalculateA1RA3RSignal);
   CalculatorUp.SetMECalculator(CalculateA1RA3ISignal);
   CalculatorUp.SetMECalculator(CalculateA2RA2ISignal);
   CalculatorUp.SetMECalculator(CalculateA2RA3RSignal);
   CalculatorUp.SetMECalculator(CalculateA2RA3ISignal);
   CalculatorUp.SetMECalculator(CalculateA2IA3RSignal);
   CalculatorUp.SetMECalculator(CalculateA2IA3ISignal);
   CalculatorUp.SetMECalculator(CalculateA3RA3ISignal);
   CalculatorDown.SetMECalculator(CalculateBackground);
   CalculatorDown.SetMECalculator(CalculateA1RA1RSignal);
   CalculatorDown.SetMECalculator(CalculateA2RA2RSignal);
   CalculatorDown.SetMECalculator(CalculateA2IA2ISignal);
   CalculatorDown.SetMECalculator(CalculateA3RA3RSignal);
   CalculatorDown.SetMECalculator(CalculateA3IA3ISignal);
   CalculatorDown.SetMECalculator(CalculateA1RA2RSignal);
   CalculatorDown.SetMECalculator(CalculateA1RA2ISignal);
   CalculatorDown.SetMECalculator(CalculateA1RA3RSignal);
   CalculatorDown.SetMECalculator(CalculateA1RA3ISignal);
   CalculatorDown.SetMECalculator(CalculateA2RA2ISignal);
   CalculatorDown.SetMECalculator(CalculateA2RA3RSignal);
   CalculatorDown.SetMECalculator(CalculateA2RA3ISignal);
   CalculatorDown.SetMECalculator(CalculateA2IA3RSignal);
   CalculatorDown.SetMECalculator(CalculateA2IA3ISignal);
   CalculatorDown.SetMECalculator(CalculateA3RA3ISignal);
   CalculatorWide.SetMECalculator(CalculateBackground);
   CalculatorWide.SetMECalculator(CalculateA1RA1RSignal);
   CalculatorWide.SetMECalculator(CalculateA2RA2RSignal);
   CalculatorWide.SetMECalculator(CalculateA2IA2ISignal);
   CalculatorWide.SetMECalculator(CalculateA3RA3RSignal);
   CalculatorWide.SetMECalculator(CalculateA3IA3ISignal);
   CalculatorWide.SetMECalculator(CalculateA1RA2RSignal);
   CalculatorWide.SetMECalculator(CalculateA1RA2ISignal);
   CalculatorWide.SetMECalculator(CalculateA1RA3RSignal);
   CalculatorWide.SetMECalculator(CalculateA1RA3ISignal);
   CalculatorWide.SetMECalculator(CalculateA2RA2ISignal);
   CalculatorWide.SetMECalculator(CalculateA2RA3RSignal);
   CalculatorWide.SetMECalculator(CalculateA2RA3ISignal);
   CalculatorWide.SetMECalculator(CalculateA2IA3RSignal);
   CalculatorWide.SetMECalculator(CalculateA2IA3ISignal);
   CalculatorWide.SetMECalculator(CalculateA3RA3ISignal);
   CalculatorNarrow.SetMECalculator(CalculateBackground);
   CalculatorNarrow.SetMECalculator(CalculateA1RA1RSignal);
   CalculatorNarrow.SetMECalculator(CalculateA2RA2RSignal);
   CalculatorNarrow.SetMECalculator(CalculateA2IA2ISignal);
   CalculatorNarrow.SetMECalculator(CalculateA3RA3RSignal);
   CalculatorNarrow.SetMECalculator(CalculateA3IA3ISignal);
   CalculatorNarrow.SetMECalculator(CalculateA1RA2RSignal);
   CalculatorNarrow.SetMECalculator(CalculateA1RA2ISignal);
   CalculatorNarrow.SetMECalculator(CalculateA1RA3RSignal);
   CalculatorNarrow.SetMECalculator(CalculateA1RA3ISignal);
   CalculatorNarrow.SetMECalculator(CalculateA2RA2ISignal);
   CalculatorNarrow.SetMECalculator(CalculateA2RA3RSignal);
   CalculatorNarrow.SetMECalculator(CalculateA2RA3ISignal);
   CalculatorNarrow.SetMECalculator(CalculateA2IA3RSignal);
   CalculatorNarrow.SetMECalculator(CalculateA2IA3ISignal);
   CalculatorNarrow.SetMECalculator(CalculateA3RA3ISignal);

   // Setup tree
   TFile File(FileName.c_str());
   TDirectoryFile *Directory = (TDirectoryFile *)File.Get("zz4lTree");
   TTree *Tree = (TTree *)Directory->Get("probe_tree");

   float l1pt, l1eta, l1phi;
   float l2pt, l2eta, l2phi;
   float l3pt, l3eta, l3phi;
   float l4pt, l4eta, l4phi;
   float pho1pt, pho1eta, pho1phi;
   float pho2pt, pho2eta, pho2phi;
   Tree->SetBranchAddress("l1pt", &l1pt);
   Tree->SetBranchAddress("l1eta", &l1eta);
   Tree->SetBranchAddress("l1phi", &l1phi);
   Tree->SetBranchAddress("l2pt", &l2pt);
   Tree->SetBranchAddress("l2eta", &l2eta);
   Tree->SetBranchAddress("l2phi", &l2phi);
   Tree->SetBranchAddress("l3pt", &l3pt);
   Tree->SetBranchAddress("l3eta", &l3eta);
   Tree->SetBranchAddress("l3phi", &l3phi);
   Tree->SetBranchAddress("l4pt", &l4pt);
   Tree->SetBranchAddress("l4eta", &l4eta);
   Tree->SetBranchAddress("l4phi", &l4phi);
   Tree->SetBranchAddress("pho1pt", &pho1pt);
   Tree->SetBranchAddress("pho1eta", &pho1eta);
   Tree->SetBranchAddress("pho1phi", &pho1phi);
   Tree->SetBranchAddress("pho2pt", &pho2pt);
   Tree->SetBranchAddress("pho2eta", &pho2eta);
   Tree->SetBranchAddress("pho2phi", &pho2phi);

   int EventCount = Tree->GetEntries();
   for(int iEvent = StartEvent; iEvent < EventCount && iEvent <= EndEvent; iEvent++)
   {
      Tree->GetEntry(iEvent);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      if(pho1pt > 1)   // photon for Z1 found
      {
         FourVector Photon;
         Photon.SetPtEtaPhi(pho1pt, pho1eta, pho1phi);

         if(GetDR(Photon, Leptons.Lepton11) < GetDR(Photon, Leptons.Lepton12))
            Leptons.Lepton11 = Leptons.Lepton11 + Photon;
         else
            Leptons.Lepton12 = Leptons.Lepton12 + Photon;
      }
      if(pho2pt > 1)   // photon for Z2 found
      {
         FourVector Photon;
         Photon.SetPtEtaPhi(pho2pt, pho2eta, pho2phi);

         if(GetDR(Photon, Leptons.Lepton21) < GetDR(Photon, Leptons.Lepton22))
            Leptons.Lepton21 = Leptons.Lepton21 + Photon;
         else
            Leptons.Lepton22 = Leptons.Lepton22 + Photon;
      }

      EventParameters Angles = ConvertVectorsToAnglesRoberto(Leptons);
      
      vector<double> Integral = Calculator.SimpleMassIntegral(Angles);
      vector<double> IntegralUp = CalculatorUp.SimpleMassIntegral(Angles);
      vector<double> IntegralDown = CalculatorDown.SimpleMassIntegral(Angles);
      vector<double> IntegralWide = CalculatorWide.SimpleMassIntegral(Angles);
      vector<double> IntegralNarrow = CalculatorNarrow.SimpleMassIntegral(Angles);

      Integral[6] = Integral[6] - Integral[1] - Integral[2];
      Integral[7] = Integral[7] - Integral[1] - Integral[3];
      Integral[8] = Integral[8] - Integral[1] - Integral[4];
      Integral[9] = Integral[9] - Integral[1] - Integral[5];
      Integral[10] = Integral[10] - Integral[2] - Integral[3];
      Integral[11] = Integral[11] - Integral[2] - Integral[4];
      Integral[12] = Integral[12] - Integral[2] - Integral[5];
      Integral[13] = Integral[13] - Integral[3] - Integral[4];
      Integral[14] = Integral[14] - Integral[3] - Integral[5];
      Integral[15] = Integral[15] - Integral[4] - Integral[5];
      IntegralUp[6] = IntegralUp[6] - IntegralUp[1] - IntegralUp[2];
      IntegralUp[7] = IntegralUp[7] - IntegralUp[1] - IntegralUp[3];
      IntegralUp[8] = IntegralUp[8] - IntegralUp[1] - IntegralUp[4];
      IntegralUp[9] = IntegralUp[9] - IntegralUp[1] - IntegralUp[5];
      IntegralUp[10] = IntegralUp[10] - IntegralUp[2] - IntegralUp[3];
      IntegralUp[11] = IntegralUp[11] - IntegralUp[2] - IntegralUp[4];
      IntegralUp[12] = IntegralUp[12] - IntegralUp[2] - IntegralUp[5];
      IntegralUp[13] = IntegralUp[13] - IntegralUp[3] - IntegralUp[4];
      IntegralUp[14] = IntegralUp[14] - IntegralUp[3] - IntegralUp[5];
      IntegralUp[15] = IntegralUp[15] - IntegralUp[4] - IntegralUp[5];
      IntegralDown[6] = IntegralDown[6] - IntegralDown[1] - IntegralDown[2];
      IntegralDown[7] = IntegralDown[7] - IntegralDown[1] - IntegralDown[3];
      IntegralDown[8] = IntegralDown[8] - IntegralDown[1] - IntegralDown[4];
      IntegralDown[9] = IntegralDown[9] - IntegralDown[1] - IntegralDown[5];
      IntegralDown[10] = IntegralDown[10] - IntegralDown[2] - IntegralDown[3];
      IntegralDown[11] = IntegralDown[11] - IntegralDown[2] - IntegralDown[4];
      IntegralDown[12] = IntegralDown[12] - IntegralDown[2] - IntegralDown[5];
      IntegralDown[13] = IntegralDown[13] - IntegralDown[3] - IntegralDown[4];
      IntegralDown[14] = IntegralDown[14] - IntegralDown[3] - IntegralDown[5];
      IntegralDown[15] = IntegralDown[15] - IntegralDown[4] - IntegralDown[5];
      IntegralWide[6] = IntegralWide[6] - IntegralWide[1] - IntegralWide[2];
      IntegralWide[7] = IntegralWide[7] - IntegralWide[1] - IntegralWide[3];
      IntegralWide[8] = IntegralWide[8] - IntegralWide[1] - IntegralWide[4];
      IntegralWide[9] = IntegralWide[9] - IntegralWide[1] - IntegralWide[5];
      IntegralWide[10] = IntegralWide[10] - IntegralWide[2] - IntegralWide[3];
      IntegralWide[11] = IntegralWide[11] - IntegralWide[2] - IntegralWide[4];
      IntegralWide[12] = IntegralWide[12] - IntegralWide[2] - IntegralWide[5];
      IntegralWide[13] = IntegralWide[13] - IntegralWide[3] - IntegralWide[4];
      IntegralWide[14] = IntegralWide[14] - IntegralWide[3] - IntegralWide[5];
      IntegralWide[15] = IntegralWide[15] - IntegralWide[4] - IntegralWide[5];
      IntegralNarrow[6] = IntegralNarrow[6] - IntegralNarrow[1] - IntegralNarrow[2];
      IntegralNarrow[7] = IntegralNarrow[7] - IntegralNarrow[1] - IntegralNarrow[3];
      IntegralNarrow[8] = IntegralNarrow[8] - IntegralNarrow[1] - IntegralNarrow[4];
      IntegralNarrow[9] = IntegralNarrow[9] - IntegralNarrow[1] - IntegralNarrow[5];
      IntegralNarrow[10] = IntegralNarrow[10] - IntegralNarrow[2] - IntegralNarrow[3];
      IntegralNarrow[11] = IntegralNarrow[11] - IntegralNarrow[2] - IntegralNarrow[4];
      IntegralNarrow[12] = IntegralNarrow[12] - IntegralNarrow[2] - IntegralNarrow[5];
      IntegralNarrow[13] = IntegralNarrow[13] - IntegralNarrow[3] - IntegralNarrow[4];
      IntegralNarrow[14] = IntegralNarrow[14] - IntegralNarrow[3] - IntegralNarrow[5];
      IntegralNarrow[15] = IntegralNarrow[15] - IntegralNarrow[4] - IntegralNarrow[5];

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
   }

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
   return GetZZZAAABackground(Leptons, false, true) + GetZZZAAABackground(Leptons, true, true);
}

















