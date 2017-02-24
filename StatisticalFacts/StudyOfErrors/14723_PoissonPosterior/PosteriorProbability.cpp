#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#define SIZE 250000

struct Range;
int main();
Range CalculateRange(int k);
pair<double, double> SearchRange(int k, double TargetIntegral);
double LogPoisson(int k, double lambda);
double CDF(int k, double lambda);
double CDFExpansion(int k, double lambda);

struct Range
{
   double MostProbable;
   double Median;
   double Min68, Max68;
   double Min95, Max95;
};

int main()
{
   ofstream out("Everything.txt");

   for(int k = 0; k <= 1000; k++)
   {
      Range Result = CalculateRange(k);
      cout << k << " " << Result.Min68 << " " << Result.Max68
         << " " << Result.Min95 << " " << Result.Max95 << endl;
      out << k << " " << Result.Min68 << " " << Result.Max68
         << " " << Result.Min95 << " " << Result.Max95 << endl;
   }

   out.close();

   return 0;
}

Range CalculateRange(int k)
{
   if(k > 1000)
   {
      Range Result;
      Result.MostProbable = k;
      Result.Min68 = -1;
      Result.Max68 = -1;
      Result.Min95 = -1;
      Result.Max95 = -1;

      return Result;
   }

   double MostLikely = (double)k;

   pair<double, double> Range68 = SearchRange(k, 0.6827);
   pair<double, double> Range95 = SearchRange(k, 0.9545);

   Range Result;
   Result.MostProbable = MostLikely;
   Result.Min68 = Range68.first;
   Result.Max68 = Range68.second;
   Result.Min95 = Range95.first;
   Result.Max95 = Range95.second;

   return Result;
}

pair<double, double> SearchRange(int k, double TargetIntegral)
{
   double MostLikely = (double)k;

   double RawIntegral = 1;   // by definition!
   double LogHeight = LogPoisson(k, MostLikely);

   double MaxHeight = LogHeight;
   double MinHeight = LogHeight - log(100000);

   double MaxIntegral = 0;
   double MinIntegral = 1;

   double TargetEpsilon = 0.0001;

   double Left = 0, Right = 100000;

   while(fabs(MaxIntegral - MinIntegral) > TargetEpsilon)
   {
      double TestHeight = (MaxHeight + MinHeight) / 2;

      Left = 0, Right = 100000;

      double Min = 0, Max = MostLikely;
      if(Min == Max)
         Left = Min;
      else
      {
         while(Max - Min > 0.000000001)
         {
            if(LogPoisson(k, (Min + Max) / 2) > TestHeight)
               Max = (Min + Max) / 2;
            else
               Min = (Min + Max) / 2;
         }
         Left = (Min + Max) / 2;
      }

      Min = MostLikely, Max = 100000;
      if(Min == Max)
         Right = Max;
      else
      {
         while(Max - Min > 0.000000001)
         {
            if(LogPoisson(k, (Min + Max) / 2) > TestHeight)
               Min = (Min + Max) / 2;
            else
               Max = (Min + Max) / 2;
         }
         Right = (Min + Max) / 2;
      }

      double TestIntegral = (CDFExpansion(k, Right) - CDFExpansion(k, Left)) / RawIntegral;

      if(TestIntegral < TargetIntegral)
      {
         MaxHeight = TestHeight;
         MaxIntegral = TestIntegral;
      }
      else
      {
         MinHeight = TestHeight;
         MinIntegral = TestIntegral;
      }

      // cout << "After Iteration" << endl;
      // cout << "LR " << Left << " " << Right << endl;
      // cout << "Heights " << MaxHeight << " " << MinHeight << endl;
      // cout << "Integrals " << MaxIntegral << " " << MinIntegral << endl;
      // cout << endl;
   }

   pair<double, double> Result;
   Result.first = Left;
   Result.second = Right;
   return Result;
}

double LogPoisson(int k, double lambda)
{
   double Answer = 0;

   for(int i = 1; i <= k; i++)
      Answer = Answer - log(i) + log(lambda);
   Answer = Answer - lambda;

   return Answer;
}

double CDF(int k, double lambda)
{
   double LogIntIk = log(1 - exp(-lambda));

   if(k > 0 && lambda > 0)
   {
      double LogTerm = 0;
      for(int i = 1; i <= k; i++)
         LogTerm = LogTerm + log(lambda) - log(i);
      LogTerm = LogTerm - lambda;

      for(int i = k; i >= 1; i--)
      {  
         // cout << i << " " << LogIntIk << " " << LogTerm << endl;

         LogIntIk = LogIntIk + log(1 - exp(LogTerm - LogIntIk));
         LogTerm = LogTerm - log(lambda) + log(i);
      }
   }

   // cout << "CDF " << k << " " << lambda << " " << IntIk << endl;

   return exp(LogIntIk);
}

double CDFExpansion(int k, double lambda)
{
   if(lambda == 0)
      return 0;

   double LogSum = 0;

   double LogTerm = 0;
   for(int i = 1; i <= k; i++)
      LogTerm = LogTerm + log(lambda) - log(i);

   for(int i = k + 1; i < k + 1000; i++)
   {
      LogTerm = LogTerm + log(lambda) - log(i);
      if(i == k + 1)
         LogSum = LogTerm;
      else
         LogSum = LogSum + log(1 + exp(LogTerm - LogSum));
   }

   LogSum = LogSum - lambda;

   return exp(LogSum);
}

double DrawRandom()
{
   // Get a random number from 0 to 1
   double x = rand() % 100;
   for(int i = 0; i < 20; i++)
      x = x / 100 + rand() % 100;
   return x / 100;
}






