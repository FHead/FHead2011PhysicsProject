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
   double HMass = 125;

   if(argc > 1)
      HMass = atof(argv[1]);

   if(argc > 2)
   {
      RandomSeed = atoi(argv[2]);
      cerr << "Using random seed = " << RandomSeed << endl;
      srand(RandomSeed);
   }
   else
      srand(time(NULL));

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
   CalculatorSEM.SetPTYDensity(GetPTYDensityGG_MZ_CTEQ6l1_13432);
   CalculatorSEM.SetAttractorStrength(2);
   CalculatorSEM.SetIntegralCStep(20);
   CalculatorSEM.SetSimpleMassIntegralWindow(true, 30);
   CalculatorSEM.SetSimpleMassIntegralWindow(false, 40);
   CalculatorSEM.SetFlatApproximation(false);
   CalculatorSEM.SetIncludeSwapping(false);
   CalculatorSEM.SetIgnoreTip(false);
   CalculatorSEM.SetTipRangeFactor(0.05);
   CalculatorSEM.SetUseSmartCenter(true);

   CalculatorSEE = CalculatorSEM;
   // CalculatorBEM = CalculatorSEM;
   // CalculatorBEM.SetDoDeltaMH(false);
   // CalculatorBEE = CalculatorBEM;

   MEArray MEEM = GetHEFTFunctionListEM_ZAAZSeparate();   // ME, 2e2mu = ME,EM = MEEM
   MEArray MEEE = GetHEFTFunctionListEE_ZAAZSeparate();   // ME, 4e = ME,EE = MEEE

   for(int i = 0; i < 32; i++)
      for(int j = 0; j < 32; j++)
         CalculatorSEM.SetMECalculator(MEEM[i][j]);
   for(int i = 0; i < 32; i++)
      for(int j = 0; j < 32; j++)
         CalculatorSEE.SetMECalculator(MEEE[i][j]);
 
   // CalculatorBEM.SetMECalculator(CalculateBackground2e2mu);
   // CalculatorBEE.SetMECalculator(CalculateBackground4e);

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
      double m4l = DrawRandom(115, 135);
      Weight = Weight * exp(-(m4l - 125) * (m4l - 125) / (2 * 2 * 2)) / m4l;

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
      Value = DrawRandom(0.05, 120);
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
      Value = DrawRandom(0.05, 120);
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








