#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "Code/DrawRandom.h"

int main()
{
   TFile File("Gaussian.root", "RECREATE");

   TTree Tree("Tree", "Tree");

   double P1, P2, P3, P4;

   Tree.Branch("P1", &P1, "P1/D");
   Tree.Branch("P2", &P2, "P2/D");
   Tree.Branch("P3", &P3, "P3/D");
   Tree.Branch("P4", &P4, "P4/D");

   for(int i = 0; i < 100000; i++)
   {
      P1 = DrawGaussian(201, 43.44);
      P2 = DrawGaussian(201, 43.44);
      P3 = DrawGaussian(201, 43.44);
      P4 = DrawGaussian(201, 43.44);

      Tree.Fill();
   }

   Tree.Write();

   File.Close();

   return 0;
}



