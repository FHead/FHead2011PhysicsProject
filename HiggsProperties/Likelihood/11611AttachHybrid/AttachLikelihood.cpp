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
double CalculateA1A1Signal(LeptonVectors &Leptons);
double CalculateA1A3Signal(LeptonVectors &Leptons);
double CalculateA3A3Signal(LeptonVectors &Leptons);
double CalculateBackground(LeptonVectors &Leptons);

int main(int argc, char *argv[])
{
   // Usage string
   if(argc <= 4)
   {
      cerr << "Usage: " << argv[0] << " FileWithTree StartEvent EndEvent OutputName" << endl;
      return -1;
   }

   string FileName = argv[1];
   int StartEvent = atoi(argv[2]);
   int EndEvent = atoi(argv[3]);
   string OutputFileName = argv[4];

   // Setup calculator
   HybridCalculator CalculatorA1A1, CalculatorA1A3, CalculatorA3A3, CalculatorBackground;

   CalculatorA1A1.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   CalculatorA1A1.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   CalculatorA1A1.SetSmear12(SmearMuon);
   CalculatorA1A1.SetSmear34(SmearMuon);
   CalculatorA1A1.SetToleranceF(1e-8);

   CalculatorA1A3.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   CalculatorA1A3.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   CalculatorA1A3.SetSmear12(SmearMuon);
   CalculatorA1A3.SetSmear34(SmearMuon);
   CalculatorA1A3.SetToleranceF(1e-8);

   CalculatorA3A3.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   CalculatorA3A3.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   CalculatorA3A3.SetSmear12(SmearMuon);
   CalculatorA3A3.SetSmear34(SmearMuon);
   CalculatorA3A3.SetToleranceF(1e-8);

   CalculatorBackground.SetEfficiency12(GetMuonEfficiencyPtEtaPhi);
   CalculatorBackground.SetEfficiency34(GetMuonEfficiencyPtEtaPhi);
   CalculatorBackground.SetSmear12(SmearMuon);
   CalculatorBackground.SetSmear34(SmearMuon);
   CalculatorBackground.SetToleranceF(1e-8);

   CalculatorA1A1.SetMECalculator(CalculateA1A1Signal);
   CalculatorA1A3.SetMECalculator(CalculateA1A3Signal);
   CalculatorA3A3.SetMECalculator(CalculateA3A3Signal);
   CalculatorBackground.SetMECalculator(CalculateBackground);

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
      
      double IntegralA1A1 = CalculatorA1A1.SimpleMassIntegral(Angles);
      double IntegralA1A3 = CalculatorA1A3.SimpleMassIntegral(Angles);
      double IntegralA3A3 = CalculatorA3A3.SimpleMassIntegral(Angles);
      double IntegralBackground = CalculatorBackground.SimpleMassIntegral(Angles);

      IntegralA1A3 = IntegralA1A3 - IntegralA1A1 - IntegralA3A3;

      cout << FileName << " " << iEvent
         << " " << IntegralA1A1 << " " << IntegralA1A3 << " " << IntegralA3A3
         << " " << IntegralBackground << endl;
   }

   File.Close();

   return 0;
}

double CalculateA1A1Signal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_ahR_ahR(Leptons, 1, false);
}

double CalculateA1A3Signal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZdR_ahR(Leptons, 1, 1, false);
}

double CalculateA3A3Signal(LeptonVectors &Leptons)
{
   return GetGeneralScalar_aZdR_aZdR(Leptons, 1, false);
}

double CalculateBackground(LeptonVectors &Leptons)
{
   return GetZZZAAABackground(Leptons, false, false) + GetZZZAAABackground(Leptons, true, false);
}

















