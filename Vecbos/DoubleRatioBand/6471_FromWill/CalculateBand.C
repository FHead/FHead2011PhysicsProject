#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#include "TFile.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooAbsReal.h"
#include "RooArgList.h"
using namespace RooFit;

#include "PlotHelper.h"

void CalculateBand(string Nominator = "Result_PF15_Constrained.root",
   string Denominator = "Result_PF30_Constrained.root");
void CalculateBand(RooFitResult *Nominator, RooFitResult *Denominator, vector<string> Names);
vector<double> CalculateLimits(RooFitResult *Nominator, RooFitResult *Denominator, vector<string> Names, double N);

void CalculateBand(string Nominator, string Denominator)
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

   TFile F1(Nominator.c_str());
   TFile F2(Denominator.c_str());

   RooFitResult *Result1 = (RooFitResult *)F1.Get("ConstrainedResult");
   RooFitResult *Result2 = (RooFitResult *)F2.Get("ConstrainedResult");

   CalculateBand(Result1, Result2, Names);

   F2.Close();
   F1.Close();
}

void CalculateBand(RooFitResult *Nominator, RooFitResult *Denominator, vector<string> Names)
{
   if(Nominator == NULL || Denominator == NULL)   // safety checks
      return;

   if(Names.size() < 4)
      return;

   for(double N = 0; N < 6; N = N + 0.05)
   {
      vector<double> Limits = CalculateLimits(Nominator, Denominator, Names, N);

      cout << N << " " << Limits[0] << " " << Limits[1] << endl;
   }
}

vector<double> CalculateLimits(RooFitResult *Nominator, RooFitResult *Denominator, vector<string> Names, double N)
{
   if(Names.size() < 4)
      return vector<double>(2);

   int TotalTrials = 10000;

   vector<double> Values;
   Values.reserve(TotalTrials);

   // create toys and populate histogram
   for(int i = 0; i < TotalTrials; i++)
   {
      const RooArgList NominatorArgSet = Nominator->randomizePars();
      const RooArgList DenominatorArgSet = Denominator->randomizePars();

      double Alpha1 = ((RooAbsReal *)NominatorArgSet.find(Names[0].c_str()))->getVal();
      double Beta1 = ((RooAbsReal *)NominatorArgSet.find(Names[1].c_str()))->getVal();
      double Alpha2 = ((RooAbsReal *)DenominatorArgSet.find(Names[2].c_str()))->getVal();
      double Beta2 = ((RooAbsReal *)DenominatorArgSet.find(Names[3].c_str()))->getVal();

      double Value = (Alpha1 + N * Beta1) / (Alpha2 + N * Beta2);
      Values.push_back(Value);
   }

   // sort vector
   sort(Values.begin(), Values.end());

   int LowerIndex = (int)(TotalTrials * 0.1575);
   int UpperIndex = (int)(TotalTrials * 0.8425);

   // return answer
   vector<double> Result;

   Result.push_back(Values[LowerIndex]);
   Result.push_back(Values[UpperIndex]);

   return Result;
}



