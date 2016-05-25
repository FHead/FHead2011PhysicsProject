#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TGraph.h"
#include "TF1.h"

int main()
{
   vector<double> AveragePerJob;

   double AverageTotal = 0;

   while(cin)
   {
      double Temp = -999;
      cin >> Temp;
      if(Temp > -998.9)
      {
         AveragePerJob.push_back(Temp);
         AverageTotal = AverageTotal + Temp;
      }
   }

   TGraph Graph;

   double Mean = AverageTotal / AveragePerJob.size();

   int MaxCount = AveragePerJob.size() / 10;
   for(int i = 5; i < MaxCount; i++)
   {
      vector<double> Average;

      random_shuffle(AveragePerJob.begin(), AveragePerJob.end());

      for(int j = 0; (j + 1) * i < (int)AveragePerJob.size(); j++)
      {
         double Sum = 0;
         int Count = 0;

         for(int k = 0; k < i; k++)
         {
            Sum = Sum + AveragePerJob[j*i+k];
            Count = Count + 1;
         }

         Average.push_back(Sum / Count);
      }

      double Total0 = 0, Total1 = 0, Total2 = 0;
      for(int j = 0; j < (int)Average.size(); j++)
      {
         Total0 = Total0 + 1;
         Total1 = Total1 + Average[j];
         Total2 = Total2 + Average[j] * Average[j];
      }

      double RMS = sqrt((Total2 - Total1 * Total1 / Total0) / (Total0 - 1));

      cout << i << " " << Mean << " " << RMS << endl;

      Graph.SetPoint(Graph.GetN(), i, RMS / Mean);
   }

   TF1 Fit("Fit", "[0]/sqrt(x)");
   Graph.Fit(&Fit);

   cout << "Estimated value at current point = " << Mean << endl;
   cout << "Estimated error at current point = " << Fit.Eval(AveragePerJob.size()) << endl;

   return 0;
}







