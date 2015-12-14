#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
   ifstream in("AllData.txt");

   int Count = 10;
   int HiggsMass[] = {100, 110, 120, 125, 130, 140, 160, 200, 300, 400};
   string HiggsMassString[] = {"100", "110", "120", "125", "130",
      "140", "160", "200", "300", "400"};

   vector<ofstream *> out;
   for(int i = 0; i < Count; i++)
      out.push_back(new ofstream(("HiggsFile_" + HiggsMassString[i]).c_str()));

   while(in)
   {
      double Mass = 0, Eta = 0, PT = 0;
      in >> Mass >> Eta >> PT;

      for(int i = 0; i < Count; i++)
      {
         if(out[i] == NULL)
            continue;

         if(Mass < HiggsMass[i] + 5 && Mass > HiggsMass[i] - 5)
            *(out[i]) << PT << " " << Eta << " " << 1 << endl;
      }
   }

   for(int i = 0; i < Count; i++)
   {
      if(out[i] == NULL)
         continue;

      out[i]->close();
      delete out[i];
      out[i] = NULL;
   }

   in.close();

   return 0;
}



