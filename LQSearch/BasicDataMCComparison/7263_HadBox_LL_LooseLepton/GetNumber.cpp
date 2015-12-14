#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

#include "TChain.h"

int main(int argc, char *argv[])
{
   string InputFile = "";
   if(argc == 1)
   {
      cout << "Usage: " << argv[0] << " InputFile" << endl;
      return 0;
   }
   InputFile = argv[1];

   TChain Tree("MRTree", "MRTree");
   Tree.AddFile(InputFile.c_str());

   double MR = 0;
   double Rsq = 0;
   double Factor = 0;
   Tree.SetBranchAddress("MR", &MR);
   Tree.SetBranchAddress("Rsq", &Rsq);
   Tree.SetBranchAddress("Factor", &Factor);

   double WeightFull = 0;
   double Weight2Full = 0;
   double WeightMR400 = 0;
   double Weight2MR400 = 0;
   double WeightMR450 = 0;
   double Weight2MR450 = 0;
   double WeightMR500 = 0;
   double Weight2MR500 = 0;
   double WeightMR550 = 0;
   double Weight2MR550 = 0;
   double WeightMR600 = 0;
   double Weight2MR600 = 0;
   double WeightMR650 = 0;
   double Weight2MR650 = 0;
   double WeightMR700 = 0;
   double Weight2MR700 = 0;
   double WeightMR750 = 0;
   double Weight2MR750 = 0;
   double WeightMR800 = 0;
   double Weight2MR800 = 0;

   int EntryCount = Tree.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree.GetEntry(i);

      if(Rsq > 0.09 && Rsq < 0.5 && MR > 200)
      {
         WeightFull = WeightFull + Factor;
         Weight2Full = Weight2Full + Factor * Factor;
      }

      if(Rsq > 0.48 && Rsq < 0.5)
      {
         if(MR > 400)
         {
            WeightMR400 = WeightMR400 + Factor;
            Weight2MR400 = Weight2MR400 + Factor * Factor;
         }
         if(MR > 450)
         {
            WeightMR450 = WeightMR450 + Factor;
            Weight2MR450 = Weight2MR450 + Factor * Factor;
         }
         if(MR > 500)
         {
            WeightMR500 = WeightMR500 + Factor;
            Weight2MR500 = Weight2MR500 + Factor * Factor;
         }
         if(MR > 550)
         {
            WeightMR550 = WeightMR550 + Factor;
            Weight2MR550 = Weight2MR550 + Factor * Factor;
         }
         if(MR > 600)
         {
            WeightMR600 = WeightMR600 + Factor;
            Weight2MR600 = Weight2MR600 + Factor * Factor;
         }
         if(MR > 650)
         {
            WeightMR650 = WeightMR650 + Factor;
            Weight2MR650 = Weight2MR650 + Factor * Factor;
         }
         if(MR > 700)
         {
            WeightMR700 = WeightMR700 + Factor;
            Weight2MR700 = Weight2MR700 + Factor * Factor;
         }
         if(MR > 750)
         {
            WeightMR750 = WeightMR750 + Factor;
            Weight2MR750 = Weight2MR750 + Factor * Factor;
         }
         if(MR > 800)
         {
            WeightMR800 = WeightMR800 + Factor;
            Weight2MR800 = Weight2MR800 + Factor * Factor;
         }
      }
   }

   cout << "MR > 400, Rsq = 0.48-0.50" << endl;
   cout << "   Total weight = " << WeightMR400 << endl;
   cout << "   Total weight^2 = " << Weight2MR400 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR400) << endl;
   cout << "MR > 450, Rsq = 0.48-0.50" << endl;
   cout << "   Total weight = " << WeightMR450 << endl;
   cout << "   Total weight^2 = " << Weight2MR450 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR450) << endl;
   cout << "MR > 500, Rsq = 0.48-0.50" << endl;
   cout << "   Total weight = " << WeightMR500 << endl;
   cout << "   Total weight^2 = " << Weight2MR500 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR500) << endl;
   cout << "MR > 550, Rsq = 0.48-0.50" << endl;
   cout << "   Total weight = " << WeightMR550 << endl;
   cout << "   Total weight^2 = " << Weight2MR550 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR550) << endl;
   cout << "MR > 600, Rsq = 0.48-0.50" << endl;
   cout << "   Total weight = " << WeightMR600 << endl;
   cout << "   Total weight^2 = " << Weight2MR600 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR600) << endl;
   cout << "MR > 650, Rsq = 0.48-0.50" << endl;
   cout << "   Total weight = " << WeightMR650 << endl;
   cout << "   Total weight^2 = " << Weight2MR650 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR650) << endl;
   cout << "MR > 700, Rsq = 0.48-0.50" << endl;
   cout << "   Total weight = " << WeightMR700 << endl;
   cout << "   Total weight^2 = " << Weight2MR700 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR700) << endl;
   cout << "MR > 750, Rsq = 0.48-0.50" << endl;
   cout << "   Total weight = " << WeightMR750 << endl;
   cout << "   Total weight^2 = " << Weight2MR750 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR750) << endl;
   cout << "MR > 800, Rsq = 0.48-0.50" << endl;
   cout << "   Total weight = " << WeightMR800 << endl;
   cout << "   Total weight^2 = " << Weight2MR800 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR800) << endl;
   cout << "" << endl;

   cout << "MR > 200, Rsq = 0.09-0.50" << endl;
   cout << "   Total weight = " << setprecision(10) << WeightFull << endl;
   cout << "   Total weight^2 = " << Weight2Full << endl;
   cout << "   Error I think = " << sqrt(Weight2Full) << endl;
   cout << "" << endl;

   return 0;
}



