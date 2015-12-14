#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "DrawRandom.h"

void GenerateSignalBatch();
void GenerateSignal(double target, string output, double BackgroundTarget);

void GenerateSignalBatch()
{
   vector<double> Targets;
   Targets.push_back(3000);

   for(unsigned int i = 0; i < Targets.size(); i++)
   {
      for(int j = 0; j < 1000; j++)
      {
         stringstream str;
         str << "Signal_" << i + 1 << "_" << j << ".root";

         GenerateSignal(Targets[i], str.str().c_str(), 200);
      }
   }
}

void GenerateSignal(double target, string output, double BackgroundTarget)
{
   int realtarget = DrawGaussian(target, sqrt(target)) + 0.5;
   if(target <= 15)
      realtarget = DrawPoisson(target);
   
   int realbackgroundtarget = DrawGaussian(BackgroundTarget, sqrt(BackgroundTarget)) + 0.5;
   if(BackgroundTarget <= 15)
      realbackgroundtarget = DrawPoisson(BackgroundTarget);

   TFile F(output.c_str(), "RECREATE");

   TTree *NewTree = new TTree("MllTree", "MllTree");

   double mll;
   NewTree->Branch("ZMass", &mll, "ZMass/D");

   for(int i = 0; i < realtarget; i++)
   {
      mll = DrawCruijff(90.97, 2.50, 2.05, 0.49, 0.45, 60, 120);

      NewTree->Fill();
   }

   for(int j = 0; j < realbackgroundtarget; j++)
   {
      mll = DrawExponential(-0.009, 60, 120);

      NewTree->Fill();
   }

   F.Write();
   F.Close();
}


