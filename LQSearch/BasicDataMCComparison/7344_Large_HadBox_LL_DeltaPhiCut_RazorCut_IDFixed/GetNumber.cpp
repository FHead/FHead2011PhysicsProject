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

   double Weight025 = 0;
   double Weight030 = 0;
   double Weight031 = 0;
   double Weight032 = 0;
   double Weight033 = 0;
   double Weight034 = 0;
   double Weight035 = 0;
   double Weight036 = 0;
   double Weight037 = 0;
   double Weight038 = 0;
   double Weight039 = 0;
   double Weight040 = 0;
   double Weight041 = 0;
   double Weight042 = 0;
   double Weight043 = 0;
   double Weight044 = 0;
   double Weight045 = 0;
   double Weight2025 = 0;
   double Weight2030 = 0;
   double Weight2031 = 0;
   double Weight2032 = 0;
   double Weight2033 = 0;
   double Weight2034 = 0;
   double Weight2035 = 0;
   double Weight2036 = 0;
   double Weight2037 = 0;
   double Weight2038 = 0;
   double Weight2039 = 0;
   double Weight2040 = 0;
   double Weight2041 = 0;
   double Weight2042 = 0;
   double Weight2043 = 0;
   double Weight2044 = 0;
   double Weight2045 = 0;

   int EntryCount = Tree.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree.GetEntry(i);

      if(MR < 400 || Rsq > 0.5)
         continue;

      if(Rsq > 0.25)
      {
         Weight025 = Weight025 + Factor;
         Weight2025 = Weight2025 + Factor * Factor;
      }
      if(Rsq > 0.30)
      {
         Weight030 = Weight030 + Factor;
         Weight2030 = Weight2030 + Factor * Factor;
      }
      if(Rsq > 0.31)
      {
         Weight031 = Weight031 + Factor;
         Weight2031 = Weight2031 + Factor * Factor;
      }
      if(Rsq > 0.32)
      {
         Weight032 = Weight032 + Factor;
         Weight2032 = Weight2032 + Factor * Factor;
      }
      if(Rsq > 0.33)
      {
         Weight033 = Weight033 + Factor;
         Weight2033 = Weight2033 + Factor * Factor;
      }
      if(Rsq > 0.34)
      {
         Weight034 = Weight034 + Factor;
         Weight2034 = Weight2034 + Factor * Factor;
      }
      if(Rsq > 0.35)
      {
         Weight035 = Weight035 + Factor;
         Weight2035 = Weight2035 + Factor * Factor;
      }
      if(Rsq > 0.36)
      {
         Weight036 = Weight036 + Factor;
         Weight2036 = Weight2036 + Factor * Factor;
      }
      if(Rsq > 0.37)
      {
         Weight037 = Weight037 + Factor;
         Weight2037 = Weight2037 + Factor * Factor;
      }
      if(Rsq > 0.38)
      {
         Weight038 = Weight038 + Factor;
         Weight2038 = Weight2038 + Factor * Factor;
      }
      if(Rsq > 0.39)
      {
         Weight039 = Weight039 + Factor;
         Weight2039 = Weight2039 + Factor * Factor;
      }
      if(Rsq > 0.40)
      {
         Weight040 = Weight040 + Factor;
         Weight2040 = Weight2040 + Factor * Factor;
      }
      if(Rsq > 0.41)
      {
         Weight041 = Weight041 + Factor;
         Weight2041 = Weight2041 + Factor * Factor;
      }
      if(Rsq > 0.42)
      {
         Weight042 = Weight042 + Factor;
         Weight2042 = Weight2042 + Factor * Factor;
      }
      if(Rsq > 0.43)
      {
         Weight043 = Weight043 + Factor;
         Weight2043 = Weight2043 + Factor * Factor;
      }
      if(Rsq > 0.44)
      {
         Weight044 = Weight044 + Factor;
         Weight2044 = Weight2044 + Factor * Factor;
      }
      if(Rsq > 0.45)
      {
         Weight045 = Weight045 + Factor;
         Weight2045 = Weight2045 + Factor * Factor;
      }
   }

   cout << "MR > 400, Rsq = 0.25-0.50" << endl;
   cout << "   Total weight = " << Weight025 << endl;
   cout << "   Total weight^2 = " << Weight2025 << endl;
   cout << "   Error I think = " << sqrt(Weight2025) << endl;
   cout << "MR > 400, Rsq = 0.30-0.50" << endl;
   cout << "   Total weight = " << Weight030 << endl;
   cout << "   Total weight^2 = " << Weight2030 << endl;
   cout << "   Error I think = " << sqrt(Weight2030) << endl;
   cout << "MR > 400, Rsq = 0.31-0.50" << endl;
   cout << "   Total weight = " << Weight031 << endl;
   cout << "   Total weight^2 = " << Weight2031 << endl;
   cout << "   Error I think = " << sqrt(Weight2031) << endl;
   cout << "MR > 400, Rsq = 0.32-0.50" << endl;
   cout << "   Total weight = " << Weight032 << endl;
   cout << "   Total weight^2 = " << Weight2032 << endl;
   cout << "   Error I think = " << sqrt(Weight2032) << endl;
   cout << "MR > 400, Rsq = 0.33-0.50" << endl;
   cout << "   Total weight = " << Weight033 << endl;
   cout << "   Total weight^2 = " << Weight2033 << endl;
   cout << "   Error I think = " << sqrt(Weight2033) << endl;
   cout << "MR > 400, Rsq = 0.34-0.50" << endl;
   cout << "   Total weight = " << Weight034 << endl;
   cout << "   Total weight^2 = " << Weight2034 << endl;
   cout << "   Error I think = " << sqrt(Weight2034) << endl;
   cout << "MR > 400, Rsq = 0.35-0.50" << endl;
   cout << "   Total weight = " << Weight035 << endl;
   cout << "   Total weight^2 = " << Weight2035 << endl;
   cout << "   Error I think = " << sqrt(Weight2035) << endl;
   cout << "MR > 400, Rsq = 0.36-0.50" << endl;
   cout << "   Total weight = " << Weight036 << endl;
   cout << "   Total weight^2 = " << Weight2036 << endl;
   cout << "   Error I think = " << sqrt(Weight2036) << endl;
   cout << "MR > 400, Rsq = 0.37-0.50" << endl;
   cout << "   Total weight = " << Weight037 << endl;
   cout << "   Total weight^2 = " << Weight2037 << endl;
   cout << "   Error I think = " << sqrt(Weight2037) << endl;
   cout << "MR > 400, Rsq = 0.38-0.50" << endl;
   cout << "   Total weight = " << Weight038 << endl;
   cout << "   Total weight^2 = " << Weight2038 << endl;
   cout << "   Error I think = " << sqrt(Weight2038) << endl;
   cout << "MR > 400, Rsq = 0.39-0.50" << endl;
   cout << "   Total weight = " << Weight039 << endl;
   cout << "   Total weight^2 = " << Weight2039 << endl;
   cout << "   Error I think = " << sqrt(Weight2039) << endl;
   cout << "MR > 400, Rsq = 0.40-0.50" << endl;
   cout << "   Total weight = " << Weight040 << endl;
   cout << "   Total weight^2 = " << Weight2040 << endl;
   cout << "   Error I think = " << sqrt(Weight2040) << endl;
   cout << "MR > 400, Rsq = 0.41-0.50" << endl;
   cout << "   Total weight = " << Weight041 << endl;
   cout << "   Total weight^2 = " << Weight2041 << endl;
   cout << "   Error I think = " << sqrt(Weight2041) << endl;
   cout << "MR > 400, Rsq = 0.42-0.50" << endl;
   cout << "   Total weight = " << Weight042 << endl;
   cout << "   Total weight^2 = " << Weight2042 << endl;
   cout << "   Error I think = " << sqrt(Weight2042) << endl;
   cout << "MR > 400, Rsq = 0.43-0.50" << endl;
   cout << "   Total weight = " << Weight043 << endl;
   cout << "   Total weight^2 = " << Weight2043 << endl;
   cout << "   Error I think = " << sqrt(Weight2043) << endl;
   cout << "MR > 400, Rsq = 0.44-0.50" << endl;
   cout << "   Total weight = " << Weight044 << endl;
   cout << "   Total weight^2 = " << Weight2044 << endl;
   cout << "   Error I think = " << sqrt(Weight2044) << endl;
   cout << "MR > 400, Rsq = 0.45-0.50" << endl;
   cout << "   Total weight = " << Weight045 << endl;
   cout << "   Total weight^2 = " << Weight2045 << endl;
   cout << "   Error I think = " << sqrt(Weight2045) << endl;
   cout << "" << endl;

   return 0;
}



