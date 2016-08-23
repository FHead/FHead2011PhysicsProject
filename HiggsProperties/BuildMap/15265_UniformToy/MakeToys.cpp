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
         if(Energy != "0")
            Angles.YH = DrawRandom(-4, 4);
         else
            Angles.YH = 0;

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
      double Weight = 1 / MaxEstimate / GiveMeZWeight(Angles.ZMass) / GiveMeZ2Weight(Angles.Z2Mass);
      Weight = Weight * Angles.ZMass * Angles.HMass * Angles.Z2Mass;

      LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Angles);

      cout << "EVENT ";
      cout << " " << Leptons.Lepton11.GetPT();
      cout << " " << Leptons.Lepton11.GetEta();
      cout << " " << Leptons.Lepton11.GetPhi();
      cout << " " << 11;
      cout << " " << Leptons.Lepton12.GetPT();
      cout << " " << Leptons.Lepton12.GetEta();
      cout << " " << Leptons.Lepton12.GetPhi();
      cout << " " << -11;
      cout << " " << Leptons.Lepton21.GetPT();
      cout << " " << Leptons.Lepton21.GetEta();
      cout << " " << Leptons.Lepton21.GetPhi();
      cout << " " << 13;
      cout << " " << Leptons.Lepton22.GetPT();
      cout << " " << Leptons.Lepton22.GetEta();
      cout << " " << Leptons.Lepton22.GetPhi();
      cout << " " << -13;
      cout << " " << Weight;
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
      Value = DrawRandom(0.1, 120);
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
      Value = DrawRandom(0.1, 120);
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








