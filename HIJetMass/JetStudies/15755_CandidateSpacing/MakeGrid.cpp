#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

int main()
{
   TFile OutputFile("Grid.root", "RECREATE");

   TH1D HGrid("HGrid", "", 10000, 0, 0.01);

   double Spacing = 0.001;

   vector<double> DRs;

   for(int i = 0; i <= 1000; i++)
   {
      for(int j = 0; j <= 1000; j++)
      {
         double DR = sqrt(i * i + j * j) * Spacing;

         DRs.push_back(DR);
      }
   }

   sort(DRs.begin(), DRs.end());
   vector<double>::iterator iter = unique(DRs.begin(), DRs.end());
   DRs.erase(iter, DRs.end());

   for(int i = 0; i < (int)DRs.size(); i++)
      HGrid.Fill(DRs[i]);

   HGrid.Write();

   OutputFile.Close();

   return 0;
}





