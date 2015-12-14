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

#include "Constants.h"
#include "AngleConversion.h"
#include "InterpretCoefficient.h"

// #include "ProjectionHelper.h"
#include "FitClass.h"

#define PI 3.14159265358979323846264338327950288479716939937510

FitConfiguration::FitConfiguration()
{
   SetFloatAs("YYYYYYYYY");
   SetFloatFractions("NNNN");

   SetInitialRatios(ListToVector(9, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
   SetNoSquareMode(false);
}

FitConfiguration::FitConfiguration(string FloatAs, string FloatFractions)
{
   SetFloatAs(FloatAs);
   SetFloatFractions(FloatFractions);

   SetInitialRatios(ListToVector(9, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
   SetNoSquareMode(false);
}
   
FitConfiguration::FitConfiguration(string FloatAs, string FloatFractions,
   vector<double> Ratios, vector<double> Fractions, bool Mode)
{
   SetFloatAs(FloatAs);
   SetFloatFractions(FloatFractions);

   SetInitialRatios(Ratios);
   SetInitialFractions(Fractions);
   SetNoSquareMode(Mode);
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
   FloatDeltaCZ = false;
   FloatDeltaCW = false;
   FloatDeltaM  = false;
   FloatCWW     = false;
   FloatCWWD    = false;
   FloatCWB     = false;
   FloatCWBD    = false;
   FloatCBB     = false;
   FloatCBBD    = false;

   if(FloatAs.size() > 0 && FloatAs[0] == 'Y')   FloatDeltaCZ = true;
   if(FloatAs.size() > 1 && FloatAs[1] == 'Y')   FloatDeltaCW = true;
   if(FloatAs.size() > 2 && FloatAs[2] == 'Y')   FloatDeltaM = true;
   if(FloatAs.size() > 3 && FloatAs[3] == 'Y')   FloatCWW = true;
   if(FloatAs.size() > 4 && FloatAs[4] == 'Y')   FloatCWWD = true;
   if(FloatAs.size() > 5 && FloatAs[5] == 'Y')   FloatCWB = true;
   if(FloatAs.size() > 6 && FloatAs[6] == 'Y')   FloatCWBD = true;
   if(FloatAs.size() > 7 && FloatAs[7] == 'Y')   FloatCBB = true;
   if(FloatAs.size() > 8 && FloatAs[8] == 'Y')   FloatCBBD = true;
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
   if(Ratios.size() > 0)   DeltaCZInitialValue = Ratios[0];
   if(Ratios.size() > 1)   DeltaCWInitialValue = Ratios[1];
   if(Ratios.size() > 2)   DeltaMInitialValue  = Ratios[2];
   if(Ratios.size() > 3)   CWWInitialValue     = Ratios[3];
   if(Ratios.size() > 4)   CWWDInitialValue    = Ratios[4];
   if(Ratios.size() > 5)   CWBInitialValue     = Ratios[5];
   if(Ratios.size() > 6)   CWBDInitialValue    = Ratios[6];
   if(Ratios.size() > 7)   CBBInitialValue     = Ratios[7];
   if(Ratios.size() > 8)   CBBDInitialValue    = Ratios[8];
}

void FitConfiguration::SetInitialFractions(const vector<double> Fractions)
{
   if(Fractions.size() > 0)   FemInitialValue = Fractions[0];
   if(Fractions.size() > 1)   FmeInitialValue = Fractions[1];
   if(Fractions.size() > 2)   FeeInitialValue = Fractions[2];
   if(Fractions.size() > 3)   FmmInitialValue = Fractions[3];
}

void FitConfiguration::SetNoSquareMode(bool Decision)
{
   NoSquareMode = Decision;
}

int FitConfiguration::TotalNumberOfFloats()
{
   int Count = 0;
   
   if(FloatDeltaCZ == true)         Count = Count + 1;
   if(FloatDeltaCW == true)         Count = Count + 1;
   if(FloatDeltaM == true)          Count = Count + 1;
   if(FloatCWW == true)             Count = Count + 1;
   if(FloatCWWD == true)            Count = Count + 1;
   if(FloatCWB == true)             Count = Count + 1;
   if(FloatCWBD == true)            Count = Count + 1;
   if(FloatCBB == true)             Count = Count + 1;
   if(FloatCBBD == true)            Count = Count + 1;
   if(FloatFem == true)             Count = Count + 1;
   if(FloatFme == true)             Count = Count + 1;
   if(FloatFee == true)             Count = Count + 1;
   if(FloatFmm == true)             Count = Count + 1;

   return Count;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double DeltaCZ = Parameters[0];
   double DeltaCW = Parameters[1];
   double DeltaM  = Parameters[2];
   double CWW     = Parameters[3];
   double CWWd    = Parameters[4];
   double CWB     = Parameters[5];
   double CWBd    = Parameters[6];
   double CBB     = Parameters[7];
   double CBBd    = Parameters[8];
   
   double AlphaEM = CONST_ALPHA;
   double CW = CONST_CW;
   double SW = CONST_SW;
   double CW2 = CONST_CW * CONST_CW;
   double SW2 = CONST_SW * CONST_SW;

   // THIS BLOCK COPIED FROM ROBERTO TEXT FILE //
   double A1ZZR = 2 * (1 + DeltaCZ);
   double A2ZZR = -4 * AlphaEM * PI / CW2 / SW2 * (-CWW + SW2 * (CWW + (-4 * CWB + CWW) * CW2 - CBB * SW2));
   double A3ZZR = -4 * AlphaEM * PI / CW2 / SW2 * (-CWWd + SW2 * (CWWd + (-4 * CWBd + CWWd) * CW2 - CBBd * SW2));
   double A4ZZR = -(1 / SW2 * (16 * AlphaEM * CWB * PI + (DeltaCW - DeltaCZ - 4 * DeltaM) * (-1 + 2 * SW2))) / 2;
   double A1ZAR = 0;
   double A2ZAR = 4 * AlphaEM * PI / CW / SW * (-2 * CWB + CWW - (CBB - 4 * CWB + CWW) * SW2);
   double A3ZAR = 4 * AlphaEM * PI / CW / SW * (-2 * CWBd + CWWd - (CBBd - 4 * CWBd + CWWd) * SW2);
   double A4ZAR = -(1 / CW * (8 * AlphaEM * CWB * PI - (DeltaCW - DeltaCZ - 4 * DeltaM) * CW2) / SW);
   double A1AZR = 0;
   double A2AZR = 4 * AlphaEM * PI / CW / SW * (-2 * CWB + CWW - (CBB - 4 * CWB + CWW) * SW2);
   double A3AZR = 4 * AlphaEM * PI / CW / SW * (-2 * CWBd + CWWd - (CBBd - 4 * CWBd + CWWd) * SW2);
   double A4AZR = -(1 / CW * (8 * AlphaEM * CWB * PI - (DeltaCW - DeltaCZ - 4 * DeltaM) * CW2) / SW);
   double A1AAR = 0;
   double A2AAR = 4 * AlphaEM * (CBB - 4 * CWB + CWW) * PI;
   double A3AAR = 4 * AlphaEM * (CBBd - 4 * CWBd + CWWd) * PI;
   double A4AAR = 0;
   // THIS BLOCK COPIED FROM ROBERTO TEXT FILE //

   double Fem = Parameters[9];
   double Fme = Parameters[10];
   double Fee = Parameters[11];
   double Fmm = Parameters[12];

   double As[16] = {0};
   As[0]  = A1ZZR;
   As[1]  = A2ZZR;
   As[2]  = A3ZZR;
   As[3]  = A4ZZR;
   As[4]  = A1ZAR;
   As[5]  = A2ZAR;
   As[6]  = A3ZAR;
   As[7]  = A4ZAR;
   As[8]  = A1AZR;
   As[9]  = A2AZR;
   As[10] = A3AZR;
   As[11] = A4AZR;
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

            if(NoSquareMode == true && (i != 0 && j != 0))
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
   NoSquareMode = configuration.NoSquareMode;

   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(-2);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   // Worker->SetTolerance(1e-10);
   Worker->SetStrategy(1);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 13);
   Worker->SetFunction(Function);

   double StepSize[13] = {0};
   StepSize[0] = (configuration.FloatDeltaCZ == true) ? 0.1 : 0;
   StepSize[1] = (configuration.FloatDeltaCW == true) ? 0.1 : 0;
   StepSize[2] = (configuration.FloatDeltaM == true) ? 0.1 : 0;
   StepSize[3] = (configuration.FloatCWW == true) ? 0.1 : 0;
   StepSize[4] = (configuration.FloatCWWD == true) ? 0.1 : 0;
   StepSize[5] = (configuration.FloatCWB == true) ? 0.1 : 0;
   StepSize[6] = (configuration.FloatCWBD == true) ? 0.1 : 0;
   StepSize[7] = (configuration.FloatCBB == true) ? 0.1 : 0;
   StepSize[8] = (configuration.FloatCBBD == true) ? 0.1 : 0;
   StepSize[9] = (configuration.FloatFem == true) ? 0.1 : 0;
   StepSize[10] = (configuration.FloatFme == true) ? 0.1 : 0;
   StepSize[11] = (configuration.FloatFee == true) ? 0.1 : 0;
   StepSize[12] = (configuration.FloatFmm == true) ? 0.1 : 0;

   Worker->SetLimitedVariable(0,  "DeltaCZ",   configuration.DeltaCZInitialValue,   StepSize[0], -1000, 1000);
   Worker->SetLimitedVariable(1,  "DeltaCW",   configuration.DeltaCWInitialValue,   StepSize[1], -1000, 1000);
   Worker->SetLimitedVariable(2,  "DeltaM",    configuration.DeltaMInitialValue,    StepSize[2], -1000, 1000);
   Worker->SetLimitedVariable(3,  "CWW",       configuration.CWWInitialValue,       StepSize[3], -1000, 1000);
   Worker->SetLimitedVariable(4,  "CWWD",      configuration.CWWDInitialValue,      StepSize[4], -1000, 1000);
   Worker->SetLimitedVariable(5,  "CWB",       configuration.CWBInitialValue,       StepSize[5], -1000, 1000);
   Worker->SetLimitedVariable(6,  "CWBD",      configuration.CWBDInitialValue,      StepSize[6], -1000, 1000);
   Worker->SetLimitedVariable(7,  "CBB",       configuration.CBBInitialValue,       StepSize[7], -1000, 1000);
   Worker->SetLimitedVariable(8,  "CBBD",      configuration.CBBDInitialValue,      StepSize[8], -1000, 1000);
   Worker->SetLimitedVariable(9,  "Fem",       configuration.FemInitialValue,       StepSize[9], 0, 1);
   Worker->SetLimitedVariable(10, "Fme",       configuration.FmeInitialValue,       StepSize[10], 0, 1);
   Worker->SetLimitedVariable(11, "Fee",       configuration.FeeInitialValue,       StepSize[11], 0, 1);
   Worker->SetLimitedVariable(12, "Fmm",       configuration.FmmInitialValue,       StepSize[12], 0, 1);

   for(int i = 0; i < 1; i++)
      Worker->Minimize();

   double EventCount[4] = {0};
   EventCount[0] = SignalStateCount[0] + BackgroundStateCount[0];
   EventCount[1] = SignalStateCount[1] + BackgroundStateCount[1];
   EventCount[2] = SignalStateCount[2] + BackgroundStateCount[2];
   EventCount[3] = SignalStateCount[3] + BackgroundStateCount[3];

   double TrueParameters[13] = {0};
   TrueParameters[0] = configuration.DeltaCZInitialValue;
   TrueParameters[1] = configuration.DeltaCWInitialValue;
   TrueParameters[2] = configuration.DeltaMInitialValue;
   TrueParameters[3] = configuration.CWWInitialValue;
   TrueParameters[4] = configuration.CWWDInitialValue;
   TrueParameters[5] = configuration.CWBInitialValue;
   TrueParameters[6] = configuration.CWBDInitialValue;
   TrueParameters[7] = configuration.CBBInitialValue;
   TrueParameters[8] = configuration.CBBDInitialValue;
   TrueParameters[9] = ((EventCount[0] > 0) ? (BackgroundStateCount[0] / EventCount[0]) : 0);
   TrueParameters[10] = ((EventCount[1] > 0) ? (BackgroundStateCount[1] / EventCount[1]) : 0);
   TrueParameters[11] = ((EventCount[2] > 0) ? (BackgroundStateCount[2] / EventCount[2]) : 0);
   TrueParameters[12] = ((EventCount[3] > 0) ? (BackgroundStateCount[3] / EventCount[3]) : 0);

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.DeltaCZ = Parameters[0];   Result.DeltaCZError = Errors[0];
   Result.DeltaCW = Parameters[1];   Result.DeltaCWError = Errors[1];
   Result.DeltaM = Parameters[2];    Result.DeltaMError = Errors[2];
   Result.CWW = Parameters[3];       Result.CWWError = Errors[3];
   Result.CWWD = Parameters[4];      Result.CWWDError = Errors[4];
   Result.CWB = Parameters[5];       Result.CWBError = Errors[5];
   Result.CWBD = Parameters[6];      Result.CWBDError = Errors[6];
   Result.CBB = Parameters[7];       Result.CBBError = Errors[7];
   Result.CBBD = Parameters[8];      Result.CBBDError = Errors[8];
   Result.Fem = Parameters[9];       Result.FemError = Errors[9];
   Result.Fme = Parameters[10];      Result.FmeError = Errors[10];
   Result.Fee = Parameters[11];      Result.FeeError = Errors[11];
   Result.Fmm = Parameters[12];      Result.FmmError = Errors[12];

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

   Result.NoSquareMode = NoSquareMode;

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




