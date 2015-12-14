#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

#include "Code/TauHelperFunctions2.h"
#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateZAME.h"

#include "ZAHybridCalculator.h"
#include "LeptonResponse.h"
#include "PTYFunctions.h"

int main(int argc, char *argv[]);
double GiveMeZMass(double HMass);
double GiveMeZWeight(double ZMass);

int main(int argc, char *argv[])
{
   // Setup calculator
   ZAHybridCalculator Calculator;

   Calculator.SetEfficiency12(GetMuonEfficiencyPtEta);
   Calculator.SetEfficiencyP(GetElectronEfficiencyPtEta);
   Calculator.SetSmear12(SmearMuonCentral);
   Calculator.SetSmearP(SmearElectronCentral);
   Calculator.SetDoDeltaMH(true, 125);
   Calculator.SetPTYDensity(ToyPTYDensity);

   Calculator.SetMECalculator(GetToy1ZAME);

   // CalculatePoint

   ZALeptonVectors Leptons;
   Leptons.Lepton1.SetPtEtaPhi(51.436344, 2.1366567, 3.0702371);
   Leptons.Lepton2.SetPtEtaPhi(9.6852369, 2.2697250, -0.482584);
   Leptons.Photon.SetPtEtaPhi(33.415840, 1.9145932, -0.015806);

   ZAEventParameters Point = ConvertVectorsToAnglesRoberto(Leptons);

   cerr << Point << endl;

   Calculator.PrintSettings(cerr);

   cout << Calculator.SimpleMassIntegral(Point)[0] << endl;
   cout << Calculator.PassThroughMode(Point)[0] << endl;
   
   return 0;
}

double GiveMeZMass(double HMass)
{
   double Value;
   bool Accepted = false;

   while(Accepted == false)
   {
      Value = DrawRandom(4, HMass);
      if(DrawRandom(0, 1) < GiveMeZWeight(Value))
         Accepted = true;
   }

   return Value;
}

double GiveMeZWeight(double ZMass)
{
   return 0.1 + 0.9 * exp(-(ZMass - 90) * (ZMass - 90) / (2 * 3 * 3));
}


