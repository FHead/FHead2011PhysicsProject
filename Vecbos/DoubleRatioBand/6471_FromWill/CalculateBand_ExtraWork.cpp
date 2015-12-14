#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooAbsReal.h"
#include "RooArgSet.h"
using namespace RooFit;

void CalculateBand(RooFitResult *Nominator, RooFitResult *Denominator)
vector<double> CalculateLimits(RooFitResult *Nominator, RooFitResult *Denominator, vector<string> Names, double N);

void CalculateBand(RooFitResult *Nominator, RooFitResult *Denominator)
{
   string Alpha1Name = "Alpha";   // the alpha in nominator
   string Beta1Name = "Beta";     // the beta in nominator
   string Alpha2Name = "Alpha";   // the alpha in denominator
   string Beta2Name = "Beta";     // the beta in denominator

   vector<string> Names;
   Names.push_back(Alpha1Name);
   Names.push_back(Beta1Name);
   Names.push_back(Alpha2Name);
   Names.push_back(Beta2Name);

   if(Nominator == NULL || Denominator == NULL)   // safety checks
      return;
}

vector<double> CalculateLimits(RooFitResult *Nominator, RooFitResult *Denominator, vector<string> Names, double N)
{
   if(Names.size() < 4)
      return vector<double>();

   vector<double> Histogram(10000);   // 0 - 10, bin width 0.001
   const double Min = 0;
   const double Max = 10;
   const double Interval = 0.01;

   int TotalTrials = 1000000;

   // create toys and populate histogram
   for(int i = 0; i < TotalTrials; i++)
   {
      RooArgSet &NominatorArgSet = Nominator->randomizePars();
      RooArgSet &DenominatorArgSet = Denominator->randomizePars();

      double Alpha1 = ((RooAbsReal *)NominatorArgSet.find(Names[0].c_str()))->getVal();
      double Beta1 = ((RooAbsReal *)NominatorArgSet.find(Names[1].c_str()))->getVal();
      double Alpha2 = ((RooAbsReal *)DenominatorArgSet.find(Names[2].c_str()))->getVal();
      double Beta2 = ((RooAbsReal *)DenominatorArgSet.find(Names[3].c_str()))->getVal();

      double Value = (Alpha1 + N * Beta1) / (Alpha2 + N * Beta2);
      
      int Index = (int)((Value - Min) / Interval);

      Histogram[Index] = Histogram[Index] + 1;
   }

   // Find the count level that correspond to 68.3%
   vector<double> SortedHistogram = Histogram;
   sort(SortedHistogram.begin(), SortedHistogram.end(), greater<double>());
   double CumulativeCount = SortedHistogram[0] / 2;
   double Level = 0;

   for(int i = 1; i < (int)SortedHistogram.size(); i++)
   {
      CumulativeCount = CumulativeCount + (SortedHistogram[i] + SortedHistogram[i-1]) / 2;

      if(CumulativeCount > TotalTrials * 0.683)   // 1 sigma is 0.683....is this correct?
      {
         double OldCumulativeCount = CumulativeCount - (SortedHistogram[i] + SortedHistogram[i-1]) / 2;
         double Area = TotalTrials * 0.683 - OldCumulativeCount;

         double Level2 = SortedHistogram[i-1] * SortedHistogram[i-1]
            + Area * (SortedHistogram[i-1] - SortedHistogram[i]);
         Level = sqrt(Level2);

         break;
      }
   }

   // find maximum bin
   int MaxIndex = 0;
   for(int i = 0; i < (int)Histogram.size(); i++)
      if(Histogram[MaxIndex] < Histogram[i])
         MaxIndex = i;

   // Now find the limits
   double LowerLimit = 0;
   for(int i = MaxIndex; i >= 0; i--)
   {
      if(Histogram[i] < Level)
      {
         double LowerLimitIndex = Histogram[i] + (Level - Histogram[i]) / (Histogram[i+1] - Histogram[i]) * 1;
         LowerLimit = Min + LowerLimitIndex * Interval;
         break;
      }
   }
   
   double UpperLimit = 0;
   for(int i = MaxIndex; i < (int)Histogram.size(); i++)
   {
      if(Histogram[i] < Level)
      {
         double UpperLimitIndex = Histogram[i-1] + (Histogram[i-1] - Level) / (Histogram[i-1] - Histogram[i]) * 1;
         UpperLimit = Min + UpperLimitIndex * Interval;
         break;
      }
   }

   // return answer
   vector<double> Result;

   Result.push_back(LowerLimit);
   Result.push_back(UpperLimit);

   return Result;
}



