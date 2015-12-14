#include <iostream>
#include <iomanip>
using namespace std;

#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "MEFunctions.h"

#include "PTYFunctions.h"

int main(int argc, char *argv[]);
double Probability(EventParameters &Angles);
double GiveMeZMass();
double ZMassWeight(double M);
void PrintEvent(EventParameters &Angles);
bool PassTightCut(EventParameters &Angles);

int main(int argc, char *argv[])
{
   bool DoCut = true;

   cout << "START" << endl;

   if(argc == 1)
      srand(time(NULL));
   else
   {
      cerr << "Using seed = " << argv[1] << endl;
      srand(atoi(argv[1]));
   }

   double HMass = 125.6;

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

      EventParameters Angles;
      Angles.HMass = HMass;
      Angles.ZMass = HMass;
      Angles.Z2Mass = HMass;
      Angles.Phi0 = DrawRandom(-PI, PI);
      Angles.Theta0 = DrawRandom(0, PI);
      Angles.Phi = DrawRandom(-PI, PI);
      Angles.Theta1 = DrawRandom(-PI, PI);
      Angles.Theta2 = DrawRandom(-PI, PI);
      Angles.PhiOffset = DrawRandom(-PI, PI);
      Angles.PhiH = DrawRandom(-PI, PI);
      Angles.PTH = 0;
      Angles.YH = 0;

      while(Angles.HMass < Angles.ZMass + Angles.Z2Mass)
      {
         Angles.HMass = 125.6;
         Angles.ZMass = GiveMeZMass();
         Angles.Z2Mass = GiveMeZMass();
      }

      if(DoCut == true && PassTightCut(Angles) == false)
         continue;

      double Value = Probability(Angles) / ZMassWeight(Angles.ZMass) / ZMassWeight(Angles.Z2Mass);

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

double Probability(EventParameters &Angles)
{
   return Get_gg_SMZZ1_ZV1_ZV2_AV2_A1_UnNorm_pdf(Angles);
   // return Get_SMZZ1_FlL_A1_UnNorm_pdf(Angles);
   // return Get_gg_SMZZ1_small_ZV1_ZV3_AV3_A1_UnNorm_pdf(Angles);
   // return Get_VLE110_UnNorm_pdf(Angles);
}

double GiveMeZMass()
{
   double Check = DrawRandom(0, 1);
   if(Check < 0.20)
      return DrawRandom(4, 125.6);
   if(Check < 0.70)
      return DrawGaussian(91, 3);
   if(Check < 0.85)
      return DrawGaussian(30, 0.0001);
   if(Check < 0.95)
      return DrawGaussian(30, 0.0003);
   return DrawGaussian(30, 0.002);
}

double ZMassWeight(double M)
{
   const double Sqrt2PI = sqrt(2 * PI);
   const double Sigma1 = 0.0001;
   const double Sigma2 = 0.0003;
   const double Sigma3 = 0.002;
   double GaussianWeight1 = exp(-(M - 30) * (M - 30) / (2 * Sigma1 * Sigma1)) / Sigma1 / Sqrt2PI;
   double GaussianWeight2 = exp(-(M - 30) * (M - 30) / (2 * Sigma2 * Sigma2)) / Sigma2 / Sqrt2PI;
   double GaussianWeight3 = exp(-(M - 30) * (M - 30) / (2 * Sigma3 * Sigma3)) / Sigma3 / Sqrt2PI;
   double GaussianWeightZ = exp(-(M - 91) * (M - 91) / (2 * 3 * 3)) / 3 / Sqrt2PI;

   return 0.20 / (125.6 - 4) + 0.50 * GaussianWeightZ
      + 0.15 * GaussianWeight1 + 0.10 * GaussianWeight2 + 0.05 * GaussianWeight3;
}

void PrintEvent(EventParameters &Angles)
{
   cout << "EVENT " << setprecision(10) << Angles.HMass << " " << Angles.ZMass << " " << Angles.Z2Mass
      << " " << Angles.Phi0 << " " << Angles.Theta0 << " " << Angles.Phi
      << " " << Angles.Theta1 << " " << Angles.Theta2 << " " << Angles.PhiOffset
      << " " << Angles.PhiH << " " << Angles.PTH << " " << Angles.YH << endl;
}

bool PassTightCut(EventParameters &Angles)
{
   double M1 = max(Angles.ZMass, Angles.Z2Mass);
   double M2 = min(Angles.ZMass, Angles.Z2Mass);
   if(M1 < 50 || M1 > 120)
      return false;
   if(M2 < 12 || M2 > 50)
      return false;

   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Angles);

   if(Leptons.Lepton11.GetPT() < 10)   return false;
   if(Leptons.Lepton12.GetPT() < 10)   return false;
   if(Leptons.Lepton21.GetPT() < 10)   return false;
   if(Leptons.Lepton22.GetPT() < 10)   return false;
   
   if(Leptons.Lepton11.GetAbsEta() > 2.5)   return false;
   if(Leptons.Lepton12.GetAbsEta() > 2.5)   return false;
   if(Leptons.Lepton21.GetAbsEta() > 2.5)   return false;
   if(Leptons.Lepton22.GetAbsEta() > 2.5)   return false;

   return true;
}



