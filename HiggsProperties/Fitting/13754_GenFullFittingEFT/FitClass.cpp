#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TCanvas.h"

#include "Code/DrawRandom.h"

#include "AngleConversion.h"
#include "InterpretCoefficient.h"

// #include "ProjectionHelper.h"
#include "FitClass.h"

#define PI 3.14159265358979323846264338327950288479716939937510

FitConfiguration::FitConfiguration()
{
   SetFloatAs("YYYYYYYY");
   SetFloatFractions("NNNN");

   SetInitialRatios(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
}

FitConfiguration::FitConfiguration(string FloatAs, string FloatFractions)
{
   SetFloatAs(FloatAs);
   SetFloatFractions(FloatFractions);

   SetInitialRatios(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
}
   
FitConfiguration::FitConfiguration(string FloatAs, string FloatFractions,
   vector<double> Ratios, vector<double> Fractions)
{
   SetFloatAs(FloatAs);
   SetFloatFractions(FloatFractions);

   SetInitialRatios(Ratios);
   SetInitialFractions(Fractions);
}

FitConfiguration::~FitConfiguration()
{
}

void FitConfiguration::SetFloats(string FloatAs, string FloatFractions)
{
   SetFloatAs(FloatAs);
   SetFloatFractions(FloatFractions);
}

void FitConfiguration::SetFloatAs(string FloatAs)
{
   FloatA2ZZ = false;
   FloatA3ZZ = false;
   FloatA4ZZ = false;
   FloatA2ZA = false;
   FloatA3ZA = false;
   FloatA4ZA = false;
   FloatA2AA = false;
   FloatA3AA = false;

   if(FloatAs.size() > 0 && FloatAs[0] == 'Y')   FloatA2ZZ = true;
   if(FloatAs.size() > 1 && FloatAs[1] == 'Y')   FloatA3ZZ = true;
   if(FloatAs.size() > 2 && FloatAs[2] == 'Y')   FloatA4ZZ = true;
   if(FloatAs.size() > 3 && FloatAs[3] == 'Y')   FloatA2ZA = true;
   if(FloatAs.size() > 4 && FloatAs[4] == 'Y')   FloatA3ZA = true;
   if(FloatAs.size() > 5 && FloatAs[5] == 'Y')   FloatA4ZA = true;
   if(FloatAs.size() > 6 && FloatAs[6] == 'Y')   FloatA2AA = true;
   if(FloatAs.size() > 7 && FloatAs[7] == 'Y')   FloatA3AA = true;
}

void FitConfiguration::SetFloatFractions(string FloatFractions)
{
   FloatFem = false;   FloatFme = false;   FloatFee = false;   FloatFmm = false;

   if(FloatFractions.size() > 0 && FloatFractions[0] == 'Y')   FloatFem = true;
   if(FloatFractions.size() > 1 && FloatFractions[1] == 'Y')   FloatFme = true;
   if(FloatFractions.size() > 2 && FloatFractions[2] == 'Y')   FloatFee = true;
   if(FloatFractions.size() > 3 && FloatFractions[3] == 'Y')   FloatFmm = true;
}

void FitConfiguration::SetInitialRatios(const vector<double> Ratios)
{
   if(Ratios.size() > 0)   A2ZZInitialValue = Ratios[0];
   if(Ratios.size() > 1)   A3ZZInitialValue = Ratios[1];
   if(Ratios.size() > 2)   A4ZZInitialValue = Ratios[2];
   if(Ratios.size() > 3)   A2ZAInitialValue = Ratios[3];
   if(Ratios.size() > 4)   A3ZAInitialValue = Ratios[4];
   if(Ratios.size() > 5)   A4ZAInitialValue = Ratios[5];
   if(Ratios.size() > 6)   A2AAInitialValue = Ratios[6];
   if(Ratios.size() > 7)   A3AAInitialValue = Ratios[7];
}

void FitConfiguration::SetInitialFractions(const vector<double> Fractions)
{
   if(Fractions.size() > 0)   FemInitialValue = Fractions[0];
   if(Fractions.size() > 1)   FmeInitialValue = Fractions[1];
   if(Fractions.size() > 2)   FeeInitialValue = Fractions[2];
   if(Fractions.size() > 3)   FmmInitialValue = Fractions[3];
}

int FitConfiguration::TotalNumberOfFloats()
{
   int Count = 0;
   
   if(FloatA2ZZ == true)         Count = Count + 1;
   if(FloatA3ZZ == true)         Count = Count + 1;
   if(FloatA4ZZ == true)         Count = Count + 1;
   if(FloatA2ZA == true)         Count = Count + 1;
   if(FloatA3ZA == true)         Count = Count + 1;
   if(FloatA4ZA == true)         Count = Count + 1;
   if(FloatA2AA == true)         Count = Count + 1;
   if(FloatA3AA == true)         Count = Count + 1;
   if(FloatFem == true)          Count = Count + 1;
   if(FloatFme == true)          Count = Count + 1;
   if(FloatFee == true)          Count = Count + 1;
   if(FloatFmm == true)          Count = Count + 1;

   return Count;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1ZZR = 2;
   double A2ZZR = Parameters[0];
   double A3ZZR = Parameters[1];
   double A4ZZR = Parameters[2];

   double A1ZAR = 0;
   double A2ZAR = Parameters[3];
   double A3ZAR = Parameters[4];
   double A4ZAR = Parameters[5];
   
   double A1AAR = 0;
   double A2AAR = Parameters[6];
   double A3AAR = Parameters[7];
   double A4AAR = 0;

   double Fem = Parameters[8];
   double Fme = Parameters[9];
   double Fee = Parameters[10];
   double Fmm = Parameters[11];

   double As[16] = {0};
   As[0]  = A1ZZR;
   As[1]  = A2ZZR;
   As[2]  = A3ZZR;
   As[3]  = A4ZZR;
   As[4]  = A1ZAR;
   As[5]  = A2ZAR;
   As[6]  = A3ZAR;
   As[7]  = A4ZAR;
   As[8]  = A1ZAR;   // Let's set ZA = AZ
   As[9]  = A2ZAR;
   As[10] = A3ZAR;
   As[11] = A4ZAR;
   As[12] = A1AAR;
   As[13] = A2AAR;
   As[14] = A3AAR;
   As[15] = A4AAR;

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value = 0, Integral = 0, LikelihoodS = 0;
      double LikelihoodB = 0;

      for(int i = 0; i < 16; i++)
      {
         if(i == 4 || i == 8 || i == 12 || i == 15)   // Skip A1ZA, A1AA, A4AA
            continue;

         for(int j = 0; j < 16; j++)
         {
            if(j == 4 || j == 8 || j == 12 || j == 15)
               continue;

            Value = Value + As[i] * As[j] * VS[i][j][iS];
            Integral = Integral + As[i] * As[j] * IS[i][j][iS];
         }
      }
      LikelihoodS = Value / Integral;

      LikelihoodB = VB[iS] / IB[iS];

      if(LikelihoodS <= 0 || LikelihoodB <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      double F = 0;
      if(S[iS] == "em")   F = Fem;
      if(S[iS] == "me")   F = Fme;
      if(S[iS] == "ee")   F = Fee;
      if(S[iS] == "mm")   F = Fmm;

      LogTotal = LogTotal + log(LikelihoodS * (1 - F) + LikelihoodB * F);
   }

   return -LogTotal * 2;
}

void FitClass::AddPoint(SingleEvent &event)
{
   AddPoint(event.VS, event.IS, event.VB, event.IB, event.event, event.state);
}

void FitClass::AddPoint(double vs[16][16], double is[16][16], double vb, double ib,
   EventParameters &Event, string State)
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 16; i2++)
      {
         VS[i1][i2].push_back(vs[i1][i2]);
         IS[i1][i2].push_back(is[i1][i2]);
      }
   }

   VB.push_back(vb);
   IB.push_back(ib);

   E.push_back(Event);
   S.push_back(State);

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 16; i2++)
      {
         VS[i1][i2].clear();
         IS[i1][i2].clear();
      }
   }
   VB.clear();
   IB.clear();

   E.clear();
   S.clear();

   SignalStateCount[0] = 0;
   SignalStateCount[1] = 0;
   SignalStateCount[2] = 0;
   SignalStateCount[3] = 0;

   BackgroundStateCount[0] = 0;
   BackgroundStateCount[1] = 0;
   BackgroundStateCount[2] = 0;
   BackgroundStateCount[3] = 0;

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit(FitConfiguration configuration)
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(-2);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   // Worker->SetTolerance(1e-10);
   Worker->SetStrategy(1);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 12);
   Worker->SetFunction(Function);

   double StepSize[12] = {0};
   StepSize[0] = (configuration.FloatA2ZZ == true) ? 0.1 : 0;
   StepSize[1] = (configuration.FloatA3ZZ == true) ? 0.1 : 0;
   StepSize[2] = (configuration.FloatA4ZZ == true) ? 0.1 : 0;
   StepSize[3] = (configuration.FloatA2ZA == true) ? 0.1 : 0;
   StepSize[4] = (configuration.FloatA3ZA == true) ? 0.1 : 0;
   StepSize[5] = (configuration.FloatA4ZA == true) ? 0.1 : 0;
   StepSize[6] = (configuration.FloatA2AA == true) ? 0.1 : 0;
   StepSize[7] = (configuration.FloatA3AA == true) ? 0.1 : 0;
   StepSize[8] = (configuration.FloatFem == true) ? 0.1 : 0;
   StepSize[9] = (configuration.FloatFme == true) ? 0.1 : 0;
   StepSize[10] = (configuration.FloatFee == true) ? 0.1 : 0;
   StepSize[11] = (configuration.FloatFmm == true) ? 0.1 : 0;

   Worker->SetLimitedVariable(0,  "A2ZZ",      configuration.A2ZZInitialValue,      StepSize[0], -1000, 1000);
   Worker->SetLimitedVariable(1,  "A3ZZ",      configuration.A3ZZInitialValue,      StepSize[1], -1000, 1000);
   Worker->SetLimitedVariable(2,  "A4ZZ",      configuration.A4ZZInitialValue,      StepSize[2], -1000, 1000);
   Worker->SetLimitedVariable(3,  "A2ZA",      configuration.A2ZAInitialValue,      StepSize[3], -1000, 1000);
   Worker->SetLimitedVariable(4,  "A3ZA",      configuration.A3ZAInitialValue,      StepSize[4], -1000, 1000);
   Worker->SetLimitedVariable(5,  "A4ZA",      configuration.A4ZAInitialValue,      StepSize[5], -1000, 1000);
   Worker->SetLimitedVariable(6,  "A2AA",      configuration.A2AAInitialValue,      StepSize[6], -1000, 1000);
   Worker->SetLimitedVariable(7,  "A3AA",      configuration.A3AAInitialValue,      StepSize[7], -1000, 1000);
   Worker->SetLimitedVariable(8,  "Fem",       configuration.FemInitialValue,       StepSize[8], 0, 1);
   Worker->SetLimitedVariable(9,  "Fme",       configuration.FmeInitialValue,       StepSize[9], 0, 1);
   Worker->SetLimitedVariable(10, "Fee",       configuration.FeeInitialValue,       StepSize[10], 0, 1);
   Worker->SetLimitedVariable(11, "Fmm",       configuration.FmmInitialValue,       StepSize[11], 0, 1);

   for(int i = 0; i < 1; i++)
      Worker->Minimize();

   double EventCount[4] = {0};
   EventCount[0] = SignalStateCount[0] + BackgroundStateCount[0];
   EventCount[1] = SignalStateCount[1] + BackgroundStateCount[1];
   EventCount[2] = SignalStateCount[2] + BackgroundStateCount[2];
   EventCount[3] = SignalStateCount[3] + BackgroundStateCount[3];

   double TrueParameters[12] = {0};
   TrueParameters[0] = configuration.A2ZZInitialValue;
   TrueParameters[1] = configuration.A3ZZInitialValue;
   TrueParameters[2] = configuration.A4ZZInitialValue;
   TrueParameters[3] = configuration.A2ZAInitialValue;
   TrueParameters[4] = configuration.A3ZAInitialValue;
   TrueParameters[5] = configuration.A4ZAInitialValue;
   TrueParameters[6] = configuration.A2AAInitialValue;
   TrueParameters[7] = configuration.A3AAInitialValue;
   TrueParameters[8] = ((EventCount[0] > 0) ? (BackgroundStateCount[0] / EventCount[0]) : 0);
   TrueParameters[9] = ((EventCount[1] > 0) ? (BackgroundStateCount[1] / EventCount[1]) : 0);
   TrueParameters[10] = ((EventCount[2] > 0) ? (BackgroundStateCount[2] / EventCount[2]) : 0);
   TrueParameters[11] = ((EventCount[3] > 0) ? (BackgroundStateCount[3] / EventCount[3]) : 0);

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.A2ZZ = Parameters[0];   Result.A2ZZError = Errors[0];
   Result.A3ZZ = Parameters[1];   Result.A3ZZError = Errors[1];
   Result.A4ZZ = Parameters[2];   Result.A4ZZError = Errors[2];
   Result.A2ZA = Parameters[3];   Result.A2ZAError = Errors[3];
   Result.A3ZA = Parameters[4];   Result.A3ZAError = Errors[4];
   Result.A4ZA = Parameters[5];   Result.A4ZAError = Errors[5];
   Result.A2AA = Parameters[6];   Result.A2AAError = Errors[6];
   Result.A3AA = Parameters[7];   Result.A3AAError = Errors[7];
   Result.Fem = Parameters[8];    Result.FemError = Errors[8];
   Result.Fme = Parameters[9];    Result.FmeError = Errors[9];
   Result.Fee = Parameters[10];   Result.FeeError = Errors[10];
   Result.Fmm = Parameters[11];   Result.FmmError = Errors[11];

   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   Result.Sem = SignalStateCount[0];
   Result.Sme = SignalStateCount[1];
   Result.See = SignalStateCount[2];
   Result.Smm = SignalStateCount[3];

   Result.Bem = BackgroundStateCount[0];
   Result.Bme = BackgroundStateCount[1];
   Result.Bee = BackgroundStateCount[2];
   Result.Bmm = BackgroundStateCount[3];

   Result.TruthNLL = CalculateLogLikelihoodAll(TrueParameters);
   Result.BestNLL = CalculateLogLikelihoodAll(Parameters);

   delete Worker;

   return Result;
}

void FitClass::PlotResult(PsFileHelper *PsFile, FitResultSummary Result)
{
}

vector<double> ListToVector(int N, double x1, double x2, double x3, double x4,
   double x5, double x6, double x7, double x8, double x9, double x10,
   double x11, double x12, double x13, double x14, double x15, double x16)
{
   vector<double> Result(N);

   if(N > 0)   Result[0] = x1;
   if(N > 1)   Result[1] = x2;
   if(N > 2)   Result[2] = x3;
   if(N > 3)   Result[3] = x4;
   if(N > 4)   Result[4] = x5;
   if(N > 5)   Result[5] = x6;
   if(N > 6)   Result[6] = x7;
   if(N > 7)   Result[7] = x8;
   if(N > 8)   Result[8] = x9;
   if(N > 9)   Result[9] = x10;
   if(N > 10)   Result[10] = x11;
   if(N > 11)   Result[11] = x12;
   if(N > 12)   Result[12] = x13;
   if(N > 13)   Result[13] = x14;
   if(N > 14)   Result[14] = x15;
   if(N > 15)   Result[15] = x16;

   return Result;
}




