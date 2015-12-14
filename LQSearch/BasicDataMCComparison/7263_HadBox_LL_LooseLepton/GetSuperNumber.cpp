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

   double WeightMR300R2014 = 0;
   double Weight2MR300R2014 = 0;
   double WeightMR400R2020 = 0;
   double Weight2MR400R2020 = 0;
   double WeightSideBand = 0;
   double Weight2SideBand = 0;
   double WeightSignal = 0;
   double Weight2Signal = 0;

   int EntryCount = Tree.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree.GetEntry(i);

      if(Rsq > 0.14 && Rsq < 0.5 && MR > 300)
      {
         WeightMR300R2014 = WeightMR300R2014 + Factor;
         Weight2MR300R2014 = Weight2MR300R2014 + Factor * Factor;
      }
      if(Rsq > 0.20 && Rsq < 0.5 && MR > 400)
      {
         WeightMR400R2020 = WeightMR400R2020 + Factor;
         Weight2MR400R2020 = Weight2MR400R2020 + Factor * Factor;
      }
      if(Rsq > 0.20 && Rsq < 0.25 && MR > 400 && MR < 600)
      {
         WeightSideBand = WeightSideBand + Factor;
         Weight2SideBand = Weight2SideBand + Factor * Factor;
      }
      if(Rsq > 0.25 && Rsq < 0.50 && MR > 400)
      {
         WeightSignal = WeightSignal + Factor;
         Weight2Signal = Weight2Signal + Factor * Factor;
      }
   }

   cout << "MR = 400-600, Rsq = 0.20-0.25" << endl;
   cout << "   Total weight = " << WeightSideBand << endl;
   cout << "   Total weight^2 = " << Weight2SideBand << endl;
   cout << "   Error I think = " << sqrt(Weight2SideBand) << endl;
   cout << "MR > 300, Rsq = 0.14-0.50" << endl;
   cout << "   Total weight = " << WeightMR300R2014 << endl;
   cout << "   Total weight^2 = " << Weight2MR300R2014 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR400R2020) << endl;
   cout << "MR > 400, Rsq = 0.20-0.50" << endl;
   cout << "   Total weight = " << WeightMR400R2020 << endl;
   cout << "   Total weight^2 = " << Weight2MR400R2020 << endl;
   cout << "   Error I think = " << sqrt(Weight2MR400R2020) << endl;
   cout << "MR > 400, Rsq = 0.25-0.50" << endl;
   cout << "   Total weight = " << WeightSignal << endl;
   cout << "   Total weight^2 = " << Weight2Signal << endl;
   cout << "   Error I think = " << sqrt(Weight2Signal) << endl;

   return 0;
}



