#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <deque>
using namespace std;

#include "Code/TauHelperFunctions3.h"
#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateME.h"
#include "MEFunctions.h"

#include "LeptonResponse.h"
#include "HybridCalculatorWithZPrime.h"
#include "PTYFunctions.h"
#include "Cuts.h"
#include "Lists.h"

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
   double HMass = 18.4;
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

   cerr << "Energy is \"" << Energy << "\"" << endl;

   ZPrimeParameters ZP;
   ZP.VMass = 9.46;
   ZP.VWidth = 0.054;
   ZP.G1VL = -0.073348;
   ZP.G1VR = 0.073348;
   ZP.G2VL = -0.073348;
   ZP.G2VR = 0.073348;

   // Setup calculator
   HybridCalculator CalculatorSEM, CalculatorSEE, CalculatorBEM, CalculatorBEE;

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
   CalculatorSEM.SetZPrimeParameter(ZP);
   if(Energy == "14")
      CalculatorSEM.SetPTYDensity(GetPTYDensityGG_MZ_CTEQ6l1_14TeV_13432);
   else if(Energy == "13")
      CalculatorSEM.SetPTYDensity(GetPTYDensityGG_MZ_CTEQ6l1_13TeV_13432);
   else if(Energy == "0")
      CalculatorSEM.SetPTYDensity(JustFlatPTYDensity);
   else   // wut
      cerr << "ERROR" << endl;

   CalculatorSEE = CalculatorSEM;
   // CalculatorBEM = CalculatorSEM;
   // CalculatorBEM.SetDoDeltaMH(false);
   // CalculatorBEE = CalculatorBEM;
   
   MEArrayZPrime MEEM = GetSpin0XVVFunctionListEM();   // ME, 2e2mu = ME,EM = MEEM
   MEArrayZPrime MEEE = GetSpin0XVVFunctionListEE();   // ME, 4ee = ME,EE = MEEE
   
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 72; j++)
         CalculatorSEM.SetMECalculator(MEEM[i][j]);
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 72; j++)
         CalculatorSEE.SetMECalculator(MEEE[i][j]);
 
   // CalculatorBEM.SetMECalculator(CalculateBackground2e2mu);
   // CalculatorBEE.SetMECalculator(CalculateBackground4e);

   // vectors to hold totals
   vector<double> TotalSEM[13], TotalSEE[13];
   vector<double> TotalBEM[13], TotalBEE[13];
   double ActualEventCount = 0;

   // Start looping
   double MaxEstimate = 1;
   int EventCount = 100000;
   EventParameters Angles;

   ProgressBar Bar(cerr, EventCount);
   Bar.SetStyle(1);

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
         if(Energy != "0")
            Angles.YH = DrawRandom(-4, 4);
         else
            Angles.YH = 0;

         do
         {
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

      // double m4l = DrawGaussian(125, 2);
      // double m4l = DrawRandom(115, 135);
      // Weight = Weight * exp(-(m4l - 125) * (m4l - 125) / (2 * 2 * 2)) / m4l;
      double m4l = HMass;

      vector<double> IntegralSEM, IntegralSEE;
      vector<double> IntegralBEM, IntegralBEE;
      
      EventParameters RealAngles = Angles;
      RealAngles.HMass = m4l;
      RealAngles.ZMass = Angles.ZMass / Angles.HMass * m4l;
      RealAngles.Z2Mass = Angles.Z2Mass / Angles.HMass * m4l;
      LeptonVectors LeptonsEM = ConvertAnglesToVectorsRoberto(RealAngles).ReorderLeptons2e2mu();
      LeptonVectors LeptonsEE = LeptonsEM.ReorderLeptons4e();

      vector<bool> PassEM = PassPairingCuts(LeptonsEM);
      vector<bool> PassEE = PassPairingCuts(LeptonsEE);

      IntegralSEM = CalculatorSEM.PassThroughMode(Angles);
      IntegralSEE = CalculatorSEE.PassThroughMode(Angles);
      // IntegralBEM = CalculatorBEM.PassThroughMode(Angles);
      // IntegralBEE = CalculatorBEE.PassThroughMode(Angles);

      ActualEventCount = ActualEventCount + Weight;

      cout << "EVENT";
      cout << " " << LeptonsEM.Lepton11.GetPT() << " " << LeptonsEM.Lepton11.GetEta() << " " << LeptonsEM.Lepton11.GetPhi();
      cout << " " << LeptonsEM.Lepton12.GetPT() << " " << LeptonsEM.Lepton12.GetEta() << " " << LeptonsEM.Lepton12.GetPhi();
      cout << " " << LeptonsEM.Lepton21.GetPT() << " " << LeptonsEM.Lepton21.GetEta() << " " << LeptonsEM.Lepton21.GetPhi();
      cout << " " << LeptonsEM.Lepton22.GetPT() << " " << LeptonsEM.Lepton22.GetEta() << " " << LeptonsEM.Lepton22.GetPhi();
      cout << " " << Angles.HMass << " " << Angles.ZMass << " " << Angles.Z2Mass;
      cout << " " << Angles.Phi0 << " " << Angles.Theta0;
      cout << " " << Angles.Phi << " " << Angles.Theta1 << " " << Angles.Theta2;
      cout << " " << Weight;
      for(int i = 0; i < 13; i++)
         cout << " " << PassEM[i];
      for(int i = 0; i < (int)IntegralSEM.size(); i++)
         cout << " " << IntegralSEM[i];
      cout << endl;

      for(int i = 0; i < 13; i++)
         AddToVector(TotalSEM[i], IntegralSEM, Weight * PassEM[i]);
      for(int i = 0; i < 13; i++)
         AddToVector(TotalSEE[i], IntegralSEE, Weight * PassEE[i]);
      // for(int i = 0; i < 10; i++)
      //    AddToVector(TotalBEM[i], IntegralBEM, Weight * PassEM[i]);
      // for(int i = 0; i < 10; i++)
      //    AddToVector(TotalBEE[i], IntegralBEE, Weight * PassEE[i]);
   }

   for(int i = 0; i < 13; i++)
   {
      string SEMString = "TA1";   SEMString[1] = 'A' + i;
      string SEEString = "VA1";   SEEString[1] = 'A' + i;
      // string BEMString = "TA2";   BEMString[1] = 'A' + i;
      // string BEEString = "VA2";   BEEString[1] = 'A' + i;

      PrintResult(SEMString, TotalSEM[i], ActualEventCount);
      PrintResult(SEEString, TotalSEE[i], ActualEventCount);
      // PrintResult(BEMString, TotalBEM[i], ActualEventCount);
      // PrintResult(BEEString, TotalBEE[i], ActualEventCount);
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
      Value = DrawRandom(0.1, 20);
      if(DrawRandom(0, 1) < GiveMeZWeight(Value))
         Accepted = true;
   }

   return Value;
}

double GiveMeZWeight(double ZMass)
{
   return 0.2 + 0.8 * exp(-(ZMass - 9.4) * (ZMass - 9.4) / (2 * 0.5 * 0.5));
   // return 0.1 + 0.9 * exp(-(ZMass - 90) * (ZMass - 90) / (2 * 3 * 3));
}

double GiveMeZ2Mass()
{
   double Value;
   bool Accepted = false;

   while(Accepted == false)
   {
      Value = DrawRandom(0.1, 20);
      if(DrawRandom(0, 1) < GiveMeZ2Weight(Value))
         Accepted = true;
   }

   return Value;
}

double GiveMeZ2Weight(double Z2Mass)
{
   return 0.2 + 0.8 * exp(-(Z2Mass - 9.4) * (Z2Mass - 9.4) / (2 * 0.5 * 0.5));
   // return 0.3 + 0.7 * exp(-(Z2Mass - 30) * (Z2Mass - 30) / (2 * 20 * 20));
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








