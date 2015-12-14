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
   SetFloatAs("YYNNNNNNN");
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
   FloatA2ZZA1ZZ = false;
   FloatA3ZZA1ZZ = false;
   FloatA4ZZA1ZZ = false;
   FloatYT = false;
   FloatYTA = false;
   FloatMT = false;
   FloatGWW = false;
   FloatMW = false;

   if(FloatAs.size() > 0 && FloatAs[0] == 'Y')   FloatA2ZZA1ZZ = true;
   if(FloatAs.size() > 1 && FloatAs[1] == 'Y')   FloatA3ZZA1ZZ = true;
   if(FloatAs.size() > 2 && FloatAs[2] == 'Y')   FloatA4ZZA1ZZ = true;
   if(FloatAs.size() > 3 && FloatAs[3] == 'Y')   FloatYT = true;
   if(FloatAs.size() > 4 && FloatAs[4] == 'Y')   FloatYTA = true;
   if(FloatAs.size() > 5 && FloatAs[5] == 'Y')   FloatMT = true;
   if(FloatAs.size() > 6 && FloatAs[6] == 'Y')   FloatGWW = true;
   if(FloatAs.size() > 7 && FloatAs[7] == 'Y')   FloatMW = true;
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
   if(Ratios.size() > 0)   A2ZZA1ZZInitialValue = Ratios[0];
   if(Ratios.size() > 1)   A3ZZA1ZZInitialValue = Ratios[1];
   if(Ratios.size() > 2)   A4ZZA1ZZInitialValue = Ratios[2];
   if(Ratios.size() > 3)   YTInitialValue = Ratios[3];
   if(Ratios.size() > 4)   YTAInitialValue = Ratios[4];
   if(Ratios.size() > 5)   MTInitialValue = Ratios[5];
   if(Ratios.size() > 6)   GWWInitialValue = Ratios[6];
   if(Ratios.size() > 7)   MWInitialValue = Ratios[7];
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
   
   if(FloatA2ZZA1ZZ == true)     Count = Count + 1;
   if(FloatA3ZZA1ZZ == true)     Count = Count + 1;
   if(FloatA4ZZA1ZZ == true)     Count = Count + 1;
   if(FloatYT == true)           Count = Count + 1;
   if(FloatYTA == true)          Count = Count + 1;
   if(FloatMT == true)           Count = Count + 1;
   if(FloatGWW == true)          Count = Count + 1;
   if(FloatMW == true)           Count = Count + 1;
   if(FloatFem == true)          Count = Count + 1;
   if(FloatFme == true)          Count = Count + 1;
   if(FloatFee == true)          Count = Count + 1;
   if(FloatFmm == true)          Count = Count + 1;

   return Count;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   InterpretationCoefficients C;
   C.yt = Parameters[3];
   C.yta = Parameters[4];
   C.mt = Parameters[5];
   C.gww = Parameters[6];
   C.mw = Parameters[7];

   double A1ZZR = 1;
   double A2ZZR = Parameters[0];
   double A3ZZR = Parameters[1];
   double A2ZAR = InterpretedA2ZA_Roberto13711(C) / 2;
   double A3ZAR = InterpretedA3ZA_Roberto13711(C) / 2;
   double A2AAR = InterpretedA2AA_Roberto13711(C) / 2;
   double A3AAR = InterpretedA3AA_Roberto13711(C) / 2;
   double A4ZZR = Parameters[2];
   double Fem = Parameters[8];
   double Fme = Parameters[9];
   double Fee = Parameters[10];
   double Fmm = Parameters[11];

   double As[12] = {0};
   As[0]  = A1ZZR;
   As[1]  = A2ZZR;
   As[2]  = A3ZZR;
   As[3]  = A4ZZR;
   As[4]  = 0;
   As[5]  = A2ZAR;
   As[6]  = A3ZAR;
   As[7]  = 0;
   As[8]  = 0;
   As[9]  = A2AAR;
   As[10] = A3AAR;
   As[11] = 0;

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value = 0, Integral = 0, LikelihoodS = 0;
      double LikelihoodB = 0;

      for(int i = 0; i < 12; i++)
      {
         if(i == 4 || i == 7 || i == 8 || i == 11)
            continue;

         for(int j = 0; j < 12; j++)
         {
            if(j == 4 || j == 7 || j == 8 || j == 11)
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

void FitClass::AddPoint(double vs[12][12], double is[12][12], double vb, double ib,
   EventParameters &Event, string State)
{
   for(int i1 = 0; i1 < 12; i1++)
   {
      for(int i2 = 0; i2 < 12; i2++)
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
   for(int i1 = 0; i1 < 12; i1++)
   {
      for(int i2 = 0; i2 < 12; i2++)
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
   StepSize[0] = (configuration.FloatA2ZZA1ZZ == true) ? 0.1 : 0;
   StepSize[1] = (configuration.FloatA3ZZA1ZZ == true) ? 0.1 : 0;
   StepSize[2] = (configuration.FloatA4ZZA1ZZ == true) ? 0.1 : 0;
   StepSize[3] = (configuration.FloatYT == true) ? 0.1 : 0;
   StepSize[4] = (configuration.FloatYTA == true) ? 0.1 : 0;
   StepSize[5] = (configuration.FloatMT == true) ? 0.1 : 0;
   StepSize[6] = (configuration.FloatGWW == true) ? 0.1 : 0;
   StepSize[7] = (configuration.FloatMW == true) ? 0.1 : 0;
   StepSize[8] = (configuration.FloatFem == true) ? 0.1 : 0;
   StepSize[9] = (configuration.FloatFme == true) ? 0.1 : 0;
   StepSize[10] = (configuration.FloatFee == true) ? 0.1 : 0;
   StepSize[11] = (configuration.FloatFmm == true) ? 0.1 : 0;

   Worker->SetLimitedVariable(0,  "A2ZZA1ZZ",  configuration.A2ZZA1ZZInitialValue,  StepSize[0], -1000, 1000);
   Worker->SetLimitedVariable(1,  "A3ZZA1ZZ",  configuration.A3ZZA1ZZInitialValue,  StepSize[1], -1000, 1000);
   Worker->SetLimitedVariable(2,  "A4ZZA1ZZ",  configuration.A4ZZA1ZZInitialValue,  StepSize[2], -1000, 1000);
   Worker->SetLimitedVariable(3,  "YT",        configuration.YTInitialValue,        StepSize[3], -100, 100);
   Worker->SetLimitedVariable(4,  "YTA",       configuration.YTAInitialValue,       StepSize[4], -100, 100);
   Worker->SetLimitedVariable(5,  "MT",        configuration.MTInitialValue,        StepSize[5], 10, 1000);
   Worker->SetLimitedVariable(6,  "GWW",       configuration.GWWInitialValue,       StepSize[6], -100, 100);
   Worker->SetLimitedVariable(7,  "MW",        configuration.MWInitialValue,        StepSize[7], 10, 1000);
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
   TrueParameters[0] = configuration.A2ZZA1ZZInitialValue;
   TrueParameters[1] = configuration.A3ZZA1ZZInitialValue;
   TrueParameters[2] = configuration.A4ZZA1ZZInitialValue;
   TrueParameters[3] = configuration.YTInitialValue;
   TrueParameters[4] = configuration.YTAInitialValue;
   TrueParameters[5] = configuration.MTInitialValue;
   TrueParameters[6] = configuration.GWWInitialValue;
   TrueParameters[7] = configuration.MWInitialValue;
   TrueParameters[8] = ((EventCount[0] > 0) ? (BackgroundStateCount[0] / EventCount[0]) : 0);
   TrueParameters[9] = ((EventCount[1] > 0) ? (BackgroundStateCount[1] / EventCount[1]) : 0);
   TrueParameters[10] = ((EventCount[2] > 0) ? (BackgroundStateCount[2] / EventCount[2]) : 0);
   TrueParameters[11] = ((EventCount[3] > 0) ? (BackgroundStateCount[3] / EventCount[3]) : 0);

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.A2ZZA1ZZ = Parameters[0];
   Result.A2ZZA1ZZError = Errors[0];
   Result.A3ZZA1ZZ = Parameters[1];
   Result.A3ZZA1ZZError = Errors[1];
   Result.A4ZZA1ZZ = Parameters[2];
   Result.A4ZZA1ZZError = Errors[2];
   Result.YT = Parameters[3];
   Result.YTError = Errors[3];
   Result.YTA = Parameters[4];
   Result.YTAError = Errors[4];
   Result.MT = Parameters[5];
   Result.MTError = Errors[5];
   Result.GWW = Parameters[6];
   Result.GWWError = Errors[6];
   Result.MW = Parameters[7];
   Result.MWError = Errors[7];
   Result.Fem = Parameters[8];
   Result.FemError = Errors[8];
   Result.Fme = Parameters[9];
   Result.FmeError = Errors[9];
   Result.Fee = Parameters[10];
   Result.FeeError = Errors[10];
   Result.Fmm = Parameters[11];
   Result.FmmError = Errors[11];
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




