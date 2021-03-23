#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

#include "CommandLine.h"
#include "DataHelper.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string DHFileName        = CL.Get("DHFile", "Results.dh");
   string PosteriorFileName = CL.Get("Posterior");
   string HoldoutFileName   = CL.Get("Holdout");
   int N                    = CL.GetInt("N");

   char StrN[100];
   sprintf(StrN, "%d", N);

   vector<double> Posterior;
   double Holdout = -1;

   ifstream in(PosteriorFileName);
   while(in)
   {
      double Temp = -1;
      in >> Temp;
      if(Temp < 0)
         continue;
      Posterior.push_back(Temp);
   }
   in.close();

   ifstream in2(HoldoutFileName);
   in2 >> Holdout;
   in2.close();

   sort(Posterior.begin(), Posterior.end());
   int Index = upper_bound(Posterior.begin(), Posterior.end(), Holdout) - Posterior.begin();

   DataHelper DHFile(DHFileName);

   DHFile[StrN]["N"] = N;
   DHFile[StrN]["PosteriorSize"] = (int)Posterior.size();
   DHFile[StrN]["Index"] = Index;

   DHFile.SaveToFile(DHFileName);

   return 0;
}



