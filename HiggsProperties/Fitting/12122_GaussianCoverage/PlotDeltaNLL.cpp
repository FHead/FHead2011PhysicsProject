#include <iostream>
#include <vector>
using namespace std;

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

#include "Code/DrawRandom.h"

class FitClass;
struct FitResultSummary;
int main();
vector<double> GetData(int DatasetSize);

class FitClass
{
public:
   vector<double> Data;
public:
   FitClass();
   FitClass(vector<double> &data);
   double GetLogLikelihood(const double *Parameters);
   FitResultSummary DoFit();
};

struct FitResultSummary
{
public:
   double Mean1;
   double Mean1Error;
   double Sigma1;
   double Sigma1Error;
   double Mean2;
   double Mean2Error;
   double Sigma2;
   double Sigma2Error;
};

FitClass::FitClass()
{
   Data.clear();
}

FitClass::FitClass(vector<double> &data)
{
   Data = data;
}

double FitClass::GetLogLikelihood(const double *Parameters)
{
   double Mean1 = Parameters[0];
   double Sigma1 = Parameters[1];
   double Mean2 = Parameters[2];
   double Sigma2 = Parameters[3];

   double LL = 0;

   for(int i = 0; i < (int)Data.size(); i++)
   {
      double G1 = -(Data[i] - Mean1) * (Data[i] - Mean1) / (2 * Sigma1 * Sigma1) - log(2 * PI) - log(Sigma1);
      double G2 = -(Data[i] - Mean2) * (Data[i] - Mean2) / (2 * Sigma2 * Sigma2) - log(2 * PI) - log(Sigma2);
      LL = LL + log(exp(G1) + exp(G2));
   }

   return -LL;
}

FitResultSummary FitClass::DoFit()
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");

   Worker->SetPrintLevel(1);
   Worker->SetMaxFunctionCalls(1000000);
   Worker->SetMaxIterations(100000);
   Worker->SetTolerance(1e-3);

   ROOT::Math::Functor Function(this, &FitClass::GetLogLikelihood, 4);
   Worker->SetFunction(Function);

   Worker->SetLimitedVariable(0, "Mean1", -1.02, 0.5, -1000, 1000);
   Worker->SetLimitedVariable(1, "Sigma1", 0.5, 0, 0.001, 1000);
   Worker->SetLimitedVariable(2, "Mean2", 1.02, 0.5, -1000, 1000);
   Worker->SetLimitedVariable(3, "Sigma2", 1.5, 0, 0.001, 1000);
   
   Worker->Minimize();

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.Mean1 = Parameters[0];
   Result.Mean1Error = Errors[0];
   Result.Sigma1 = Parameters[1];
   Result.Sigma1Error = Errors[1];
   Result.Mean2 = Parameters[2];
   Result.Mean2Error = Errors[2];
   Result.Sigma2 = Parameters[3];
   Result.Sigma2Error = Errors[3];
   return Result;
}

int main()
{
   int ExperimentCount = 100000;
   int DatasetSize = 100;

   for(int iE = 0; iE < ExperimentCount; iE++)
   {
      vector<double> Data = GetData(DatasetSize);

      FitClass Fit(Data);

      FitResultSummary Result = Fit.DoFit();

      double Correct[4] = {0, 1, 1, 1.5};
      double Best[4] = {Result.Mean1, Result.Sigma1, Result.Mean2, Result.Sigma2};

      double LL1 = Fit.GetLogLikelihood(Correct);
      double LL2 = Fit.GetLogLikelihood(Best);

      cout << "RESULT " << Result.Mean1 << " " << Result.Sigma1
         << " " << Result.Mean2 << " " << Result.Sigma2
         << " " << LL1 << " " << LL2 << endl;
   }

   return 0;
}

vector<double> GetData(int DatasetSize)
{
   vector<double> Data;

   for(int i = 0; i < DatasetSize; i++)
   {
      if(DrawRandom(0, 1) < 0.5)
         Data.push_back(DrawGaussian(0, 1));
      else
         Data.push_back(DrawGaussian(1, 1.5));
   }

   return Data;
}


