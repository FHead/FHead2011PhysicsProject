#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Code/DrawRandom.h"

#include "PTYFunctions.h"

int main()
{
   double s = 126 * 126;

   TFile File("Toys.root", "Recreate");

   TTree Tree("ProductionSpectrumTree", "ProductionSpectrumTree");

   float pt, y, w;
   Tree.Branch("pt", &pt, "pt/F"); 
   Tree.Branch("y", &y, "y/F"); 
   Tree.Branch("w", &w, "w/F");

   int EntryCount = 2000000;
   for(int i = 0; i < EntryCount; i++)
   {
      pt = DrawRandom(0, 1200);
      y = DrawRandom(-4.5, 4.5);

      w = GetPTYDensity8TeVSignal(pt, y, s);

      Tree.Fill();
   }

   Tree.Write();
   
   File.Close();

   return 0;
}





