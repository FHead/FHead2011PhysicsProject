#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <map>
using namespace std;

#include "Code/TauHelperFunctions2.h"
#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateZAME.h"
#include "MEFunctions.h"

#include "LeptonResponse.h"
#include "ZAHybridCalculator.h"
#include "PTYFunctions.h"

int main(int argc, char *argv[]);
double GiveMeZMass(double HMass);
double GiveMeZWeight(double ZMass);
pair<double, double> GiveMePTY();

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
   ZAHybridCalculator Calculator;

   Calculator.SetEfficiency12(GetMuonEfficiencyPtEta);
   Calculator.SetEfficiencyP(GetElectronEfficiencyPtEta);
   Calculator.SetSmear12(SmearMuonCentral);
   Calculator.SetSmearP(SmearElectronCentral);
   Calculator.SetPTYDensity(ToyPTYDensity);
   Calculator.SetSimpleMassIntegralWindow(40);
   Calculator.SetSimpleMassIntegralStep(200);
   Calculator.SetDoDeltaMH(true, 125);

   Calculator.SetMECalculator(GetToy1ZAME);

   Calculator.PrintSettings(cerr);

   // Start looping
   double MaxEstimate = 1e-15;
   int EventCount = 1000;
   int ActualEventCount = 0;
   ZAEventParameters Angles;

   ProgressBar Bar(cerr, EventCount);
   Bar.SetStyle(1);

   for(int iEvent = 0; iEvent < EventCount; iEvent++)
   {
      Bar.Update(iEvent);
      Bar.Print();

      pair<double, double> PTY = GiveMePTY();

      Angles.HMass = DrawRandom(HMass - 10, HMass + 10);
      Angles.ZMass = GiveMeZMass(Angles.HMass);
      Angles.Phi0 = DrawRandom(-PI, PI);
      Angles.Theta0 = acos(DrawRandom(-1, 1));
      Angles.ThetaLL = acos(DrawRandom(-1, 1));
      Angles.PhiOffset = DrawRandom(-PI, PI);
      Angles.PhiH = DrawRandom(-PI, PI);
      Angles.YH = PTY.second;
      Angles.PTH = PTY.first;

      double MassWeight = 1 / GiveMeZWeight(Angles.ZMass);

      vector<double> Integral = Calculator.SimpleMassIntegral(Angles);

      cout << setprecision(10) << Angles.HMass << " " << Angles.ZMass << " "
         << Angles.Phi0 << " " << Angles.Theta0 << " "
         << Angles.ThetaLL << " " << Angles.PhiOffset << " "
         << Angles.YH << " " << Angles.PTH << " " << Angles.PhiH;

      for(int i = 0; i < (int)Integral.size(); i++)
         cout << " " << Integral[i] * MassWeight;

      cout << endl;
   }

   Bar.Update(EventCount);
   Bar.Print();
   Bar.PrintLine();

   return 0;
}

double GiveMeZMass(double HMass)
{
   double Value;
   bool Accepted = false;

   while(Accepted == false)
   {
      Value = DrawRandom(40, HMass);
      if(DrawRandom(0, 1) < GiveMeZWeight(Value))
         Accepted = true;
   }

   return Value;
}

double GiveMeZWeight(double ZMass)
{
   return 0.1 + 0.9 * exp(-(ZMass - 90) * (ZMass - 90) / (2 * 3 * 3));
}

pair<double, double> GiveMePTY()
{
   pair<double, double> Result;

   bool Good = false;
   while(Good == false)
   {
      Result.first = DrawRandom(0, 500);
      Result.second = DrawRandom(-10, 10);

      double Density = ToyPTYDensity(Result.first, Result.second);

      if(DrawRandom(0, 1) < Density)
         Good = true;
   };

   return Result;
}




