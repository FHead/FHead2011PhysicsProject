#include <iostream>
using namespace std;

#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateZAME.h"

#include "PTYFunctions.h"

int main(int argc, char *argv[]);
double Probability(ZAEventParameters &Angles);
void PrintEvent(ZAEventParameters &Angles);
pair<double, double> GiveMePTY();

int main(int argc, char *argv[])
{
   cout << "START" << endl;

   if(argc == 1)
      srand(time(NULL));
   else
   {
      cerr << "Using seed = " << argv[1] << endl;
      srand(atoi(argv[1]));
   }

   double HMass = 125;

   double MaxSoFar = 0;
   double EstimatedCount = 0;
   int WeightedCount = 0;

   int TargetCount = 100000;

   ProgressBar Bar(cerr, TargetCount);
   Bar.SetStyle(3);

   while(TargetCount > EstimatedCount)
   {
      if(WeightedCount < 100 || WeightedCount % 1000 == 0)
      {
         Bar.Update(EstimatedCount);
         Bar.Print();
      }

      pair<double, double> PTY = GiveMePTY();

      ZAEventParameters Angles;
      Angles.HMass = HMass;
      Angles.ZMass = HMass;
      Angles.Phi0 = DrawRandom(-PI, PI);
      Angles.Theta0 = acos(DrawRandom(-1, 1));
      Angles.ThetaLL = acos(DrawRandom(-1, 1));
      Angles.PhiOffset = DrawRandom(-PI, PI);
      Angles.PhiH = DrawRandom(-PI, PI);
      Angles.PTH = PTY.first;
      Angles.YH = PTY.second;

      while(Angles.HMass <= Angles.ZMass)
      {
         Angles.HMass = DrawRandom(HMass - 30, HMass + 30);
         Angles.ZMass = DrawRandom(4, HMass + 30);
      }

      double Value = Probability(Angles);

      if(WeightedCount == 0)
      {
         WeightedCount = 1;
         EstimatedCount = 1;
         MaxSoFar = Value;
         PrintEvent(Angles);
         continue;
      }

      if(Value > MaxSoFar)
      {
         cout << "SCALE " << MaxSoFar / Value << endl;
         WeightedCount = WeightedCount + 1;
         EstimatedCount = EstimatedCount * MaxSoFar / Value + 1;
         MaxSoFar = Value;
         PrintEvent(Angles);
         continue;
      }

      double Check = DrawRandom(0, 1);
      if(Check < Value / MaxSoFar)
      {
         WeightedCount = WeightedCount + 1;
         EstimatedCount = EstimatedCount + 1;
         PrintEvent(Angles);
      }
   }

   Bar.Update(TargetCount);
   Bar.Print();
   Bar.PrintLine();

   cout << "END" << endl;

   return 0;
}

double Probability(ZAEventParameters &Angles)
{
   ZALeptonVectors Vectors = ConvertAnglesToVectorsRoberto(Angles);
   return GetToy1ZAME(Vectors) * Angles.ZMass * Angles.HMass;
}

void PrintEvent(ZAEventParameters &Angles)
{
   cout << "EVENT " << Angles.HMass << " " << Angles.ZMass
      << " " << Angles.Phi0 << " " << Angles.Theta0
      << " " << Angles.ThetaLL << " " << Angles.PhiOffset
      << " " << Angles.PhiH << " " << Angles.PTH << " " << Angles.YH << endl;
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




