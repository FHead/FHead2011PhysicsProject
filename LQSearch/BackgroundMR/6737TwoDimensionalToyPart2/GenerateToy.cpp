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
   for(int i = 1; i <= 1000; i++)
      GenerateSample(17594 / 5, i);
}

void GenerateSample(int N, int RunNumber)
{
   double InputMROffset = -200;
   double InputR2Offset = -0.22;
   double InputB = 0.0401283 / 3;

   double MRLowerBound = 300;
   double MRUpperBound = 1500;
   double RLowerBound = 0.30;
   double RUpperBound = 1;

   double XLowerBound = MRLowerBound - InputMROffset;
   double YLowerBound = RLowerBound * RLowerBound - InputR2Offset;

   double F0 = (InputB * XLowerBound * YLowerBound - 1) * exp(-InputB * XLowerBound * YLowerBound);

   TFile F(Form("ToyOn2DFit_%d.root", RunNumber), "RECREATE");

   TTree MRTree("MRTree", "MRTree");

   double GroupPFMR = 0;
   double GroupPFR = 0;
   MRTree.Branch("GroupPFMR", &GroupPFMR, "GroupPFMR/D");
   MRTree.Branch("GroupPFR", &GroupPFR, "GroupPFR/D");

   for(int i = 0; i < N; i++)
   {
      // use dummy method for now
      bool OK = false;
      while(OK == false)
      {
         GroupPFMR = DrawRandom(MRLowerBound, MRUpperBound);
         GroupPFR = DrawRandom(RLowerBound, RUpperBound);

         double X = GroupPFMR - InputMROffset;
         double Y = GroupPFR * GroupPFR - InputR2Offset;

         double TestValue = DrawRandom(0, F0);
         if(TestValue < (InputB * X * Y - 1) * exp(-InputB * X * Y))
            OK = true;
      }

      MRTree.Fill();
   }

   MRTree.Write();

   F.Close();
}







