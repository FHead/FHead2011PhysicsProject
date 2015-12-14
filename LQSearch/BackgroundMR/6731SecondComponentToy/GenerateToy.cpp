#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "DrawRandom.h"

int main();
void GenerateSample(int N, int RunNumber);

int main()
{
   srand(time(NULL));

   for(int i = 1; i <= 1000; i++)
      GenerateSample(17594 / 10, i);
}

void GenerateSample(int N, int RunNumber)
{
   double InputA = 0.00452278 / 2.5;
   double InputB = 0.0526323 / 3;

   TFile F(Form("ToyOnMRScalingFit_%d.root", RunNumber), "RECREATE");

   TTree MRTree("MRTree", "MRTree");

   double GroupPFMR = 0;
   double GroupPFR = 0;
   MRTree.Branch("GroupPFMR", &GroupPFMR, "GroupPFMR/D");
   MRTree.Branch("GroupPFR", &GroupPFR, "GroupPFR/D");

   double RelativeWeightTemp[] = {8486, 4493, 2333, 1128, 1154};   // taken from "hadronic" ttbar sample
   vector<double> RelativeWeight(RelativeWeightTemp, RelativeWeightTemp + 5);
   double TotalWeight = 0;
   for(int i = 0; i < (int)RelativeWeight.size(); i++)
      TotalWeight = TotalWeight + RelativeWeight[i];
   for(int i = 0; i < (int)RelativeWeight.size(); i++)
      RelativeWeight[i] = RelativeWeight[i] / TotalWeight;
   for(int i = 1; i < (int)RelativeWeight.size(); i++)
      RelativeWeight[i] = RelativeWeight[i] + RelativeWeight[i-1];

   vector<double> AboveWeight(RelativeWeight.size());
   AboveWeight[AboveWeight.size()-1] = RelativeWeightTemp[RelativeWeight.size()-1];
   for(int i = (int)RelativeWeight.size() - 1 - 1; i >= 0; i--)
      AboveWeight[i] = AboveWeight[i+1] + RelativeWeightTemp[i];

   double RValue[] = {0.35, 0.40, 0.45, 0.50, 0.55, 1.00};

   for(int i = 0; i < N; i++)
   {
      double CheckRBin = DrawRandom(0, 1);
      int RBinDecision = -1;
      for(int i = 0; i < (int)RelativeWeight.size(); i++)
      {
         if(CheckRBin <= RelativeWeight[i])
         {
            RBinDecision = i;
            break;
         }
      }
      if(RBinDecision == -1)   // some weird error - restart
         continue;

      if(RBinDecision == (int)RelativeWeight.size() - 1)   // last bin: exponential
      {
         double Exponent = InputA + InputB * RValue[RBinDecision] * RValue[RBinDecision];

         // cout << Exponent << endl;

         GroupPFR = (RValue[RBinDecision] + RValue[RBinDecision+1]) / 2;
         GroupPFMR = DrawExponential(-Exponent, 250);

         MRTree.Fill();

         continue;
      }

      double Exponent1 = InputA + InputB * RValue[RBinDecision] * RValue[RBinDecision];
      double Exponent2 = InputA + InputB * RValue[RBinDecision+1] * RValue[RBinDecision+1];
      double Height1 = AboveWeight[RBinDecision] * Exponent1;
      double Height2 = AboveWeight[RBinDecision+1] * Exponent2;
      double HeightDifference = Height1 - Height2;
      // cout << HeightDifference << endl;

      bool OK = false;
      double TestValue = 0;

      while(OK == false)
      {
         TestValue = DrawRandom(250, 1500);

         double Check = DrawRandom(0, 1) * HeightDifference;

         if(Check < Height1 * exp(-Exponent1 * (TestValue - 250)) - Height2 * exp(-Exponent2 * (TestValue - 250)))
            OK = true;
      }

      GroupPFR = (RValue[RBinDecision] + RValue[RBinDecision+1]) / 2;
      GroupPFMR = TestValue;

      MRTree.Fill();
   }

   MRTree.Write();

   F.Close();
}







