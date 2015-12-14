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
   HybridCalculator Calculator;

   Calculator.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   Calculator.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   Calculator.SetSmear12(SmearMuon);
   Calculator.SetSmear34(SmearMuon);
   Calculator.SetToleranceF(1e-6);

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

      cout << FileName << " " << iEvent;
      for(int i = 0; i < (int)Integral.size(); i++)
         cout << " " << Integral[i];
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
   return GetGeneralScalar_aZI_aZdR(Leptons, 1, 1, true);
}

double CalculateA2IA3RSignal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZR_aZdI(Leptons, 1, 1, true);
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

















