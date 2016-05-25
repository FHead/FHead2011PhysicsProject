#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <deque>
using namespace std;

#include "Code/TauHelperFunctions2.h"
#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateME.h"
#include "MEFunctions.h"

#include "LeptonResponse.h"
#include "HybridCalculator.h"
#include "PTYFunctions.h"
#include "Cuts.h"

int main(int argc, char *argv[]);
double GiveMeZMass();
double GiveMeZWeight(double ZMass);
double GiveMeZ2Mass();
double GiveMeZ2Weight(double ZMass);
pair<double, double> GiveMePTY();
bool CheckIfGood(vector<double> Single);
void AddToVector(vector<double> &Total, vector<double> Single, double Weight);
void PrintResult(string Identifier, vector<double> Total, double Count);

int main(int argc, char *argv[])
{
   int RandomSeed = 31426;
   double HMass = 125;
   string Energy = "0";

   if(argc > 1)
      HMass = atof(argv[1]);

   if(argc > 2)
      Energy = argv[2];

   if(argc > 3)
   {
      RandomSeed = atoi(argv[3]);
      cerr << "Using random seed = " << RandomSeed << endl;
      srand(RandomSeed);
   }
   else
      srand(time(NULL));

   // Setup calculator
   HybridCalculator CalculatorSEM, CalculatorSEE, CalculatorBEMuubar, CalculatorBEMddbar,
      CalculatorBEEuubar, CalculatorBEEddbar;

   CalculatorSEM.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorSEM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorSEM.SetSmear12(SmearElectronCentral);
   CalculatorSEM.SetSmear34(SmearMuonCentral);
   CalculatorSEM.SetToleranceF(1e-12);
   CalculatorSEM.SetMaxDepthF(30);
   CalculatorSEM.SetSimpleMassIntegralStep(180);
   CalculatorSEM.SetExpansionOrder(2);
   CalculatorSEM.SetDoDeltaMH(true, 125);
   CalculatorSEM.SetIgnorePhi(true);
   CalculatorSEM.SetApplyEfficiencyAtEnd(true);
   CalculatorSEM.SetIntegralCRange(0.75, 1.25);
   CalculatorSEM.SetAttractorStrength(2);
   CalculatorSEM.SetIntegralCStep(20);
   CalculatorSEM.SetSimpleMassIntegralWindow(true, 30);
   CalculatorSEM.SetSimpleMassIntegralWindow(false, 40);
   CalculatorSEM.SetFlatApproximation(false);
   CalculatorSEM.SetIncludeSwapping(false);
   CalculatorSEM.SetIgnoreTip(false);
   CalculatorSEM.SetTipRangeFactor(0.05);
   CalculatorSEM.SetUseSmartCenter(true);
   if(Energy == "14")
      CalculatorSEM.SetPTYDensity(GetPTYDensityGG_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorSEM.SetPTYDensity(GetPTYDensityGG_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorSEM.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   CalculatorSEE = CalculatorSEM;
   CalculatorBEMuubar = CalculatorSEM;
   CalculatorBEMuubar.SetDoDeltaMH(false);
   CalculatorBEEuubar = CalculatorBEMuubar;
   CalculatorBEMddbar = CalculatorBEMuubar;
   CalculatorBEEddbar = CalculatorBEMuubar;

   if(Energy == "14")
      CalculatorBEMddbar.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorBEMddbar.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorBEMddbar.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   if(Energy == "14")
      CalculatorBEMuubar.SetPTYDensity(GetPTYDensityUUbar_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorBEMuubar.SetPTYDensity(GetPTYDensityUUbar_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorBEMuubar.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   if(Energy == "14")
      CalculatorBEEddbar.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorBEEddbar.SetPTYDensity(GetPTYDensityDDbar_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorBEEddbar.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   if(Energy == "14")
      CalculatorBEEuubar.SetPTYDensity(GetPTYDensityUUbar_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorBEEuubar.SetPTYDensity(GetPTYDensityUUbar_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorBEEuubar.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   CalculatorBEMuubar.SetMECalculator(CalculateUbarUBackground2e2muDirectional);
   CalculatorBEEuubar.SetMECalculator(CalculateUbarUBackground4eDirectional);
   CalculatorBEMddbar.SetMECalculator(CalculateDbarDBackground2e2muDirectional);
   CalculatorBEEddbar.SetMECalculator(CalculateDbarDBackground4eDirectional);

   // vectors to hold totals
   vector<double> TotalSEM[13], TotalSEE[13];
   vector<double> TotalBEM[13], TotalBEE[13];
   double ActualEventCount = 0;

   // Start looping
   double MaxEstimate = 1;
   int EventCount = 1000000;
   EventParameters Angles;

   ProgressBar Bar(cerr, EventCount);
   Bar.SetStyle(1);

   deque<EventParameters> EventQueue;

   for(int iEvent = 0; iEvent < EventCount; iEvent++)
   {
      if(EventCount <= 300 || iEvent % (EventCount / 300) == 0)
      {
         Bar.Update(iEvent);
         Bar.Print();
      }

      if(iEvent % 8 == 0)
      {
         Angles.HMass = HMass;
         Angles.Phi0 = DrawRandom(-PI, PI);
         Angles.Theta0 = acos(DrawRandom(-1, 1));
         Angles.Phi = DrawRandom(-PI, PI);
         Angles.Theta1 = acos(DrawRandom(-1, 1));
         Angles.Theta2 = acos(DrawRandom(-1, 1));
         Angles.PhiOffset = DrawRandom(-PI, PI);
         Angles.PhiH = DrawRandom(-PI, PI);
         Angles.PTH = 0;
         Angles.YH = DrawRandom(-4, 4);

         do
         {
            Angles.HMass = DrawRandom(115, 135);
            Angles.ZMass = GiveMeZMass();
            Angles.Z2Mass = GiveMeZ2Mass();
         } while(Angles.ZMass + Angles.Z2Mass > Angles.HMass);
      }
      else if(iEvent % 2 == 1)
         Angles.Phi = Angles.Phi + PI;
      else if(iEvent % 4 == 2)
         Angles.Theta1 = PI - Angles.Theta1;
      else
         Angles.Theta2 = PI - Angles.Theta2;

      // cout << Angles << endl;

      // double PTYWeight = ToyPTYDensity(Angles.PTH, Angles.YH);
      double PTYWeight = 1;
      double Weight = 1 / MaxEstimate / GiveMeZWeight(Angles.ZMass) / GiveMeZ2Weight(Angles.Z2Mass) / PTYWeight;
      Weight = Weight * Angles.ZMass * Angles.HMass * Angles.Z2Mass;

      vector<double> IntegralSEM, IntegralSEE;
      vector<double> IntegralBEMuubar, IntegralBEEuubar;
      vector<double> IntegralBEMddbar, IntegralBEEddbar;

      LeptonVectors LeptonsEM = ConvertAnglesToVectorsRoberto(Angles).ReorderLeptons2e2mu();
      LeptonVectors LeptonsEE = LeptonsEM.ReorderLeptons4e();

      vector<bool> PassEM = PassPairingCuts(LeptonsEM);
      vector<bool> PassEE = PassPairingCuts(LeptonsEE);

      // IntegralSEM = CalculatorSEM.PassThroughMode(Angles);
      // IntegralSEE = CalculatorSEE.PassThroughMode(Angles);
      IntegralBEMuubar = CalculatorBEMuubar.PassThroughMode(Angles);
      IntegralBEEuubar = CalculatorBEEuubar.PassThroughMode(Angles);
      IntegralBEMddbar = CalculatorBEMddbar.PassThroughMode(Angles);
      IntegralBEEddbar = CalculatorBEEddbar.PassThroughMode(Angles);

      vector<double> IntegralBEM, IntegralBEE;

      IntegralBEM = IntegralBEMuubar;
      IntegralBEM.insert(IntegralBEM.end(), IntegralBEMddbar.begin(), IntegralBEMddbar.end());
      IntegralBEE = IntegralBEEuubar;
      IntegralBEE.insert(IntegralBEE.end(), IntegralBEEddbar.begin(), IntegralBEEddbar.end());

      ActualEventCount = ActualEventCount + Weight;

      cout << "EVENT";
      cout << " " << LeptonsEM.Lepton11[1] << " " << LeptonsEM.Lepton11[2] << " " << LeptonsEM.Lepton11[3];
      cout << " " << LeptonsEM.Lepton12[1] << " " << LeptonsEM.Lepton12[2] << " " << LeptonsEM.Lepton12[3];
      cout << " " << LeptonsEM.Lepton21[1] << " " << LeptonsEM.Lepton21[2] << " " << LeptonsEM.Lepton21[3];
      cout << " " << LeptonsEM.Lepton22[1] << " " << LeptonsEM.Lepton22[2] << " " << LeptonsEM.Lepton22[3];
      for(int i = 0; i < 2; i++)
         cout << " " << IntegralBEM[i] * Weight;
      for(int i = 0; i < 2; i++)
         cout << " " << IntegralBEE[i] * Weight;
      for(int i = 0; i < 13; i++)
         cout << " " << PassEM[i];
      for(int i = 0; i < 13; i++)
         cout << " " << PassEE[i];
      cout << endl;
   }

   Bar.Update(EventCount);
   Bar.Print();
   Bar.PrintLine();

   return 0;
}

double GiveMeZMass()
{
   double Value;
   bool Accepted = false;

   while(Accepted == false)
   {
      Value = DrawRandom(4, 120);
      if(DrawRandom(0, 1) < GiveMeZWeight(Value))
         Accepted = true;
   }

   return Value;
}

double GiveMeZWeight(double ZMass)
{
   return 0.1 + 0.9 * exp(-(ZMass - 90) * (ZMass - 90) / (2 * 3 * 3));
}

double GiveMeZ2Mass()
{
   double Value;
   bool Accepted = false;

   while(Accepted == false)
   {
      Value = DrawRandom(4, 120);
      if(DrawRandom(0, 1) < GiveMeZ2Weight(Value))
         Accepted = true;
   }

   return Value;
}

double GiveMeZ2Weight(double Z2Mass)
{
   return 0.3 + 0.7 * exp(-(Z2Mass - 30) * (Z2Mass - 30) / (2 * 20 * 20));
}

bool CheckIfGood(vector<double> Single)
{
   return true;

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

void PrintResult(string Identifier, vector<double> Total, double Count)
{
   cout << setprecision(20) << Identifier << " " << Count;
   for(int i = 0; i < (int)Total.size(); i++)
      cout << setprecision(20) << " " << Total[i] / Count;
   cout << endl;
}

   








