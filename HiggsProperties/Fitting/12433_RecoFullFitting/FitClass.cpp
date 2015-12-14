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

// #include "ProjectionHelper.h"
#include "FitClass.h"

#define PI 3.14159265358979323846264338327950288479716939937510

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1ZZR = 1;
   // double A2ZZR = Parameters[0] * cos(Parameters[1]);
   // double A2ZZI = Parameters[0] * sin(Parameters[1]);
   // double A3ZZR = Parameters[2] * cos(Parameters[3]);
   // double A3ZZI = Parameters[2] * sin(Parameters[3]);
   // double A2ZAR = Parameters[4] * cos(Parameters[5]);
   // double A2ZAI = Parameters[4] * sin(Parameters[5]);
   // double A3ZAR = Parameters[6] * cos(Parameters[7]);
   // double A3ZAI = Parameters[6] * sin(Parameters[7]);
   // double A2AAR = Parameters[8] * cos(Parameters[9]);
   // double A2AAI = Parameters[8] * sin(Parameters[9]);
   // double A3AAR = Parameters[10] * cos(Parameters[11]);
   // double A3AAI = Parameters[10] * sin(Parameters[11]);
   double A2ZZR = Parameters[0];
   double A2ZZI = 0;
   double A3ZZR = Parameters[2];
   double A3ZZI = 0;
   double A2ZAR = Parameters[4];
   double A2ZAI = 0;
   double A3ZAR = Parameters[6];
   double A3ZAI = 0;
   double A2AAR = Parameters[8];
   double A2AAI = 0;
   double A3AAR = Parameters[10];
   double A3AAI = 0;
   double Fem = Parameters[12];
   double Fme = Parameters[13];
   double Fee = Parameters[14];
   double Fmm = Parameters[15];
   double N1 = Parameters[16];
   double N2 = Parameters[17];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value[5] = {0}, Integral[5] = {0}, Likelihood[5] = {0};
      double LikelihoodB[5] = {0};

      for(int i = 0; i < 5; i++)
      {
         Value[i] = A1ZZR * A1ZZR * V[1][i][iS]
            + A2ZZR * A2ZZR * V[2][i][iS]
            + A2ZZI * A2ZZI * V[3][i][iS]
            + A3ZZR * A3ZZR * V[4][i][iS]
            + A3ZZI * A3ZZI * V[5][i][iS]
            + A2ZAR * A2ZAR * V[6][i][iS]
            + A2ZAI * A2ZAI * V[7][i][iS]
            + A3ZAR * A3ZAR * V[8][i][iS]
            + A3ZAI * A3ZAI * V[9][i][iS]
            + A2AAR * A2AAR * V[10][i][iS]
            + A2AAI * A2AAI * V[11][i][iS]
            + A3AAR * A3AAR * V[12][i][iS]
            + A3AAI * A3AAI * V[13][i][iS]
            + A1ZZR * A2ZZR * V[14][i][iS]
            + A1ZZR * A2ZZI * V[15][i][iS]
            + A1ZZR * A3ZZR * V[16][i][iS]
            + A1ZZR * A3ZZI * V[17][i][iS]
            + A1ZZR * A2ZAR * V[18][i][iS]
            + A1ZZR * A2ZAI * V[19][i][iS]
            + A1ZZR * A3ZAR * V[20][i][iS]
            + A1ZZR * A3ZAI * V[21][i][iS]
            + A1ZZR * A2AAR * V[22][i][iS]
            + A1ZZR * A2AAI * V[23][i][iS]
            + A1ZZR * A3AAR * V[24][i][iS]
            + A1ZZR * A3AAI * V[25][i][iS]
            + A2ZZR * A2ZZI * V[26][i][iS]
            + A2ZZR * A3ZZR * V[27][i][iS]
            + A2ZZR * A3ZZI * V[28][i][iS]
            + A2ZZR * A2ZAR * V[29][i][iS]
            + A2ZZR * A2ZAI * V[30][i][iS]
            + A2ZZR * A3ZAR * V[31][i][iS]
            + A2ZZR * A3ZAI * V[32][i][iS]
            + A2ZZR * A2AAR * V[33][i][iS]
            + A2ZZR * A2AAI * V[34][i][iS]
            + A2ZZR * A3AAR * V[35][i][iS]
            + A2ZZR * A3AAI * V[36][i][iS]
            + A2ZZI * A3ZZR * V[37][i][iS]
            + A2ZZI * A3ZZI * V[38][i][iS]
            + A2ZZI * A2ZAR * V[39][i][iS]
            + A2ZZI * A2ZAI * V[40][i][iS]
            + A2ZZI * A3ZAR * V[41][i][iS]
            + A2ZZI * A3ZAI * V[42][i][iS]
            + A2ZZI * A2AAR * V[43][i][iS]
            + A2ZZI * A2AAI * V[44][i][iS]
            + A2ZZI * A3AAR * V[45][i][iS]
            + A2ZZI * A3AAI * V[46][i][iS]
            + A3ZZR * A3ZZI * V[47][i][iS]
            + A3ZZR * A2ZAR * V[48][i][iS]
            + A3ZZR * A2ZAI * V[49][i][iS]
            + A3ZZR * A3ZAR * V[50][i][iS]
            + A3ZZR * A3ZAI * V[51][i][iS]
            + A3ZZR * A2AAR * V[52][i][iS]
            + A3ZZR * A2AAI * V[53][i][iS]
            + A3ZZR * A3AAR * V[54][i][iS]
            + A3ZZR * A3AAI * V[55][i][iS]
            + A3ZZI * A2ZAR * V[56][i][iS]
            + A3ZZI * A2ZAI * V[57][i][iS]
            + A3ZZI * A3ZAR * V[58][i][iS]
            + A3ZZI * A3ZAI * V[59][i][iS]
            + A3ZZI * A2AAR * V[60][i][iS]
            + A3ZZI * A2AAI * V[61][i][iS]
            + A3ZZI * A3AAR * V[62][i][iS]
            + A3ZZI * A3AAI * V[63][i][iS]
            + A2ZAR * A2ZAI * V[64][i][iS]
            + A2ZAR * A3ZAR * V[65][i][iS]
            + A2ZAR * A3ZAI * V[66][i][iS]
            + A2ZAR * A2AAR * V[67][i][iS]
            + A2ZAR * A2AAI * V[68][i][iS]
            + A2ZAR * A3AAR * V[69][i][iS]
            + A2ZAR * A3AAI * V[70][i][iS]
            + A2ZAI * A3ZAR * V[71][i][iS]
            + A2ZAI * A3ZAI * V[72][i][iS]
            + A2ZAI * A2AAR * V[73][i][iS]
            + A2ZAI * A2AAI * V[74][i][iS]
            + A2ZAI * A3AAR * V[75][i][iS]
            + A2ZAI * A3AAI * V[76][i][iS]
            + A3ZAR * A3ZAI * V[77][i][iS]
            + A3ZAR * A2AAR * V[78][i][iS]
            + A3ZAR * A2AAI * V[79][i][iS]
            + A3ZAR * A3AAR * V[80][i][iS]
            + A3ZAR * A3AAI * V[81][i][iS]
            + A3ZAI * A2AAR * V[82][i][iS]
            + A3ZAI * A2AAI * V[83][i][iS]
            + A3ZAI * A3AAR * V[84][i][iS]
            + A3ZAI * A3AAI * V[85][i][iS]
            + A2AAR * A2AAI * V[86][i][iS]
            + A2AAR * A3AAR * V[87][i][iS]
            + A2AAR * A3AAI * V[88][i][iS]
            + A2AAI * A3AAR * V[89][i][iS]
            + A2AAI * A3AAI * V[90][i][iS]
            + A3AAR * A3AAI * V[91][i][iS];
         Integral[i] = A1ZZR * A1ZZR * I[1][i][iS]
            + A2ZZR * A2ZZR * I[2][i][iS]
            + A2ZZI * A2ZZI * I[3][i][iS]
            + A3ZZR * A3ZZR * I[4][i][iS]
            + A3ZZI * A3ZZI * I[5][i][iS]
            + A2ZAR * A2ZAR * I[6][i][iS]
            + A2ZAI * A2ZAI * I[7][i][iS]
            + A3ZAR * A3ZAR * I[8][i][iS]
            + A3ZAI * A3ZAI * I[9][i][iS]
            + A2AAR * A2AAR * I[10][i][iS]
            + A2AAI * A2AAI * I[11][i][iS]
            + A3AAR * A3AAR * I[12][i][iS]
            + A3AAI * A3AAI * I[13][i][iS]
            + A1ZZR * A2ZZR * I[14][i][iS]
            + A1ZZR * A2ZZI * I[15][i][iS]
            + A1ZZR * A3ZZR * I[16][i][iS]
            + A1ZZR * A3ZZI * I[17][i][iS]
            + A1ZZR * A2ZAR * I[18][i][iS]
            + A1ZZR * A2ZAI * I[19][i][iS]
            + A1ZZR * A3ZAR * I[20][i][iS]
            + A1ZZR * A3ZAI * I[21][i][iS]
            + A1ZZR * A2AAR * I[22][i][iS]
            + A1ZZR * A2AAI * I[23][i][iS]
            + A1ZZR * A3AAR * I[24][i][iS]
            + A1ZZR * A3AAI * I[25][i][iS]
            + A2ZZR * A2ZZI * I[26][i][iS]
            + A2ZZR * A3ZZR * I[27][i][iS]
            + A2ZZR * A3ZZI * I[28][i][iS]
            + A2ZZR * A2ZAR * I[29][i][iS]
            + A2ZZR * A2ZAI * I[30][i][iS]
            + A2ZZR * A3ZAR * I[31][i][iS]
            + A2ZZR * A3ZAI * I[32][i][iS]
            + A2ZZR * A2AAR * I[33][i][iS]
            + A2ZZR * A2AAI * I[34][i][iS]
            + A2ZZR * A3AAR * I[35][i][iS]
            + A2ZZR * A3AAI * I[36][i][iS]
            + A2ZZI * A3ZZR * I[37][i][iS]
            + A2ZZI * A3ZZI * I[38][i][iS]
            + A2ZZI * A2ZAR * I[39][i][iS]
            + A2ZZI * A2ZAI * I[40][i][iS]
            + A2ZZI * A3ZAR * I[41][i][iS]
            + A2ZZI * A3ZAI * I[42][i][iS]
            + A2ZZI * A2AAR * I[43][i][iS]
            + A2ZZI * A2AAI * I[44][i][iS]
            + A2ZZI * A3AAR * I[45][i][iS]
            + A2ZZI * A3AAI * I[46][i][iS]
            + A3ZZR * A3ZZI * I[47][i][iS]
            + A3ZZR * A2ZAR * I[48][i][iS]
            + A3ZZR * A2ZAI * I[49][i][iS]
            + A3ZZR * A3ZAR * I[50][i][iS]
            + A3ZZR * A3ZAI * I[51][i][iS]
            + A3ZZR * A2AAR * I[52][i][iS]
            + A3ZZR * A2AAI * I[53][i][iS]
            + A3ZZR * A3AAR * I[54][i][iS]
            + A3ZZR * A3AAI * I[55][i][iS]
            + A3ZZI * A2ZAR * I[56][i][iS]
            + A3ZZI * A2ZAI * I[57][i][iS]
            + A3ZZI * A3ZAR * I[58][i][iS]
            + A3ZZI * A3ZAI * I[59][i][iS]
            + A3ZZI * A2AAR * I[60][i][iS]
            + A3ZZI * A2AAI * I[61][i][iS]
            + A3ZZI * A3AAR * I[62][i][iS]
            + A3ZZI * A3AAI * I[63][i][iS]
            + A2ZAR * A2ZAI * I[64][i][iS]
            + A2ZAR * A3ZAR * I[65][i][iS]
            + A2ZAR * A3ZAI * I[66][i][iS]
            + A2ZAR * A2AAR * I[67][i][iS]
            + A2ZAR * A2AAI * I[68][i][iS]
            + A2ZAR * A3AAR * I[69][i][iS]
            + A2ZAR * A3AAI * I[70][i][iS]
            + A2ZAI * A3ZAR * I[71][i][iS]
            + A2ZAI * A3ZAI * I[72][i][iS]
            + A2ZAI * A2AAR * I[73][i][iS]
            + A2ZAI * A2AAI * I[74][i][iS]
            + A2ZAI * A3AAR * I[75][i][iS]
            + A2ZAI * A3AAI * I[76][i][iS]
            + A3ZAR * A3ZAI * I[77][i][iS]
            + A3ZAR * A2AAR * I[78][i][iS]
            + A3ZAR * A2AAI * I[79][i][iS]
            + A3ZAR * A3AAR * I[80][i][iS]
            + A3ZAR * A3AAI * I[81][i][iS]
            + A3ZAI * A2AAR * I[82][i][iS]
            + A3ZAI * A2AAI * I[83][i][iS]
            + A3ZAI * A3AAR * I[84][i][iS]
            + A3ZAI * A3AAI * I[85][i][iS]
            + A2AAR * A2AAI * I[86][i][iS]
            + A2AAR * A3AAR * I[87][i][iS]
            + A2AAR * A3AAI * I[88][i][iS]
            + A2AAI * A3AAR * I[89][i][iS]
            + A2AAI * A3AAI * I[90][i][iS]
            + A3AAR * A3AAI * I[91][i][iS];
         Likelihood[i] = Value[i] / Integral[i];

         LikelihoodB[i] = V[0][i][iS] / I[0][i][iS];
      }

      bool Good = true;
      for(int i = 0; i < 5; i++)
         if(Likelihood[i] < 0)
            Good = false;
      if(Good == false)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      double LSa = Likelihood[0];
      double LSb1 = (N1 > 0) ? (Likelihood[1] - Likelihood[0]) : (Likelihood[0] - Likelihood[2]);
      double LSb2 = (N2 > 0) ? (Likelihood[3] - Likelihood[0]) : (Likelihood[0] - Likelihood[4]);
      double LBa = LikelihoodB[0];
      double LBb1 = (N1 > 0) ? (LikelihoodB[1] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[2]);
      double LBb2 = (N2 > 0) ? (LikelihoodB[3] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[4]);

      double SignalLikelihood = LSa + LSb1 * N1 + LSb2 * N2;
      double BackgroundLikelihood = LBa + LBb1 * N1 + LBb2 * N2;

      if(SignalLikelihood <= 0 || BackgroundLikelihood <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      double F = 0;
      if(S[iS] == "em")   F = Fem;
      if(S[iS] == "me")   F = Fme;
      if(S[iS] == "ee")   F = Fee;
      if(S[iS] == "mm")   F = Fmm;
      
      LogTotal = LogTotal + log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F) - N1 * N1 / 2 - N2 * N2 / 2;
   }

   return -LogTotal * 2;
}

void FitClass::AddPoint(SingleEvent &event)
{
   AddPoint(event.v, event.i, event.event, event.state);
}

void FitClass::AddPoint(double v[92][5], double i[92][5], EventParameters &Event, string State)
{
   for(int i1 = 0; i1 < 92; i1++)
   {
      for(int i2 = 0; i2 < 5; i2++)
      {
         V[i1][i2].push_back(v[i1][i2]);
         I[i1][i2].push_back(i[i1][i2]);
      }
   }

   E.push_back(Event);
   S.push_back(State);

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   for(int i1 = 0; i1 < 92; i1++)
   {
      for(int i2 = 0; i2 < 5; i2++)
      {
         V[i1][i2].clear();
         I[i1][i2].clear();
      }
   }

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

FitResultSummary FitClass::DoFit(int Mode, double v1, double v2)
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(2);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   Worker->SetTolerance(1e-10);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 18);
   Worker->SetFunction(Function);

   double InitialValues[18] = {0, 0, 5.05, 0.0, 0., 0.0, -0, 0.0, 0, 0.0, 0, 0.0, 0, 0, 0, 0, 0, 0};
   double StepSizes[18] = {0.1, 0, 0.1, 0, 0.1, 0, 0.1, 0, 0.1, 0, 0.1, 0, 0, 0, 0, 0, 0, 0};
   // double StepSizes[18] = {0.1, 0, 0.1, 0, 0, 0, 0, 0, 0.1, 0, 0.1, 0, 0, 0, 0, 0, 0, 0};

   // switch(Mode)
   // {
   // case FITMODE_ALL:
   //    break;
   // case FITMODE_ZZSIGNALONLY:
   //    StepSizes[4] = 0;   InitialValues[4] = 0;
   //    break;
   // case FITMODE_ZZPHASEONLY:
   //    StepSizes[0] = 0;   InitialValues[0] = v1;
   //    StepSizes[2] = 0;   InitialValues[2] = v2;
   //    StepSizes[4] = 0.1; InitialValues[4] = 0.1;
   //    break;
   // }

   Worker->SetLimitedVariable(0, "A2ZZA1ZZ", InitialValues[0], StepSizes[0], -1000, 1000);
   Worker->SetLimitedVariable(1, "A2ZZPhase", InitialValues[1], StepSizes[1], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(2, "A3ZZA1ZZ", InitialValues[2], StepSizes[2], -1000, 1000);
   Worker->SetLimitedVariable(3, "A3ZZPhase", InitialValues[3], StepSizes[3], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(4, "A2ZAA1ZZ", InitialValues[4], StepSizes[4], -1000, 1000);
   Worker->SetLimitedVariable(5, "A2ZAPhase", InitialValues[5], StepSizes[5], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(6, "A3ZAA1ZZ", InitialValues[6], StepSizes[6], -1000, 1000);
   Worker->SetLimitedVariable(7, "A3ZAPhase", InitialValues[7], StepSizes[7], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(8, "A2AAA1ZZ", InitialValues[8], StepSizes[8], -1000, 1000);
   Worker->SetLimitedVariable(9, "A2AAPhase", InitialValues[9], StepSizes[9], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(10, "A3AAA1ZZ", InitialValues[10], StepSizes[10], -1000, 1000);
   Worker->SetLimitedVariable(11, "A3AAPhase", InitialValues[11], StepSizes[11], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(12, "Fem", InitialValues[12], StepSizes[12], 0, 1);
   Worker->SetLimitedVariable(13, "Fme", InitialValues[13], StepSizes[13], 0, 1);
   Worker->SetLimitedVariable(14, "Fee", InitialValues[14], StepSizes[14], 0, 1);
   Worker->SetLimitedVariable(15, "Fmm", InitialValues[15], StepSizes[15], 0, 1);
   Worker->SetLimitedVariable(16, "N1", InitialValues[16], StepSizes[16], -5, 5);
   Worker->SetLimitedVariable(17, "N2", InitialValues[17], StepSizes[17], -5, 5);
   
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.A2ZZA1ZZ = Parameters[0];
   Result.A2ZZA1ZZError = Errors[0];
   Result.A2ZZPhase = Parameters[1];
   Result.A2ZZPhaseError = Errors[1];
   Result.A3ZZA1ZZ = Parameters[2];
   Result.A3ZZA1ZZError = Errors[2];
   Result.A3ZZPhase = Parameters[3];
   Result.A3ZZPhaseError = Errors[3];
   Result.A2ZAA1ZZ = Parameters[4];
   Result.A2ZAA1ZZError = Errors[4];
   Result.A2ZAPhase = Parameters[5];
   Result.A2ZAPhaseError = Errors[5];
   Result.A3ZAA1ZZ = Parameters[6];
   Result.A3ZAA1ZZError = Errors[6];
   Result.A3ZAPhase = Parameters[7];
   Result.A3ZAPhaseError = Errors[7];
   Result.A2AAA1ZZ = Parameters[8];
   Result.A2AAA1ZZError = Errors[8];
   Result.A2AAPhase = Parameters[9];
   Result.A2AAPhaseError = Errors[9];
   Result.A3AAA1ZZ = Parameters[10];
   Result.A3AAA1ZZError = Errors[10];
   Result.A3AAPhase = Parameters[11];
   Result.A3AAPhaseError = Errors[11];
   Result.Fem = Parameters[12];
   Result.FemError = Errors[12];
   Result.Fme = Parameters[13];
   Result.FmeError = Errors[13];
   Result.Fee = Parameters[14];
   Result.FeeError = Errors[14];
   Result.Fmm = Parameters[15];
   Result.FmmError = Errors[15];
   Result.N1 = Parameters[16];
   Result.N1Error = Errors[16];
   Result.N2 = Parameters[17];
   Result.N2Error = Errors[17];
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

   delete Worker;

   return Result;
}

void FitClass::PlotResult(PsFileHelper *PsFile, FitResultSummary Result)
{
   /*
   TFile SignalFile("ProjectionTree.root");
   TTree *SignalTree = (TTree *)SignalFile.Get("Tree");
   
   TFile BackgroundFile("BackgroundProjectionTree.root");
   TTree *BackgroundTree = (TTree *)BackgroundFile.Get("Tree");

   GeneralScalarParameters Parameters;
   Parameters.ahR = 1;
   Parameters.ahI = 0;
   Parameters.aZR = Result.A2ZZA1ZZ * cos(Result.A2ZZPhase);
   Parameters.aZI = Result.A2ZZA1ZZ * sin(Result.A2ZZPhase);
   Parameters.aZdR = Result.A3ZZA1ZZ * cos(Result.A3ZZPhase);
   Parameters.aZdI = Result.A3ZZA1ZZ * sin(Result.A3ZZPhase);
   Parameters.aZAR = Result.A2ZAA1ZZ * cos(Result.A2ZAPhase);
   Parameters.aZAI = Result.A2ZAA1ZZ * sin(Result.A2ZAPhase);
   Parameters.aZAdR = Result.A3ZAA1ZZ * cos(Result.A3ZAPhase);
   Parameters.aZAdI = Result.A3ZAA1ZZ * sin(Result.A3ZAPhase);
   Parameters.aAR = Result.A2AAA1ZZ * cos(Result.A2AAPhase);
   Parameters.aAI = Result.A2AAA1ZZ * sin(Result.A2AAPhase);
   Parameters.aAdR = Result.A3AAA1ZZ * cos(Result.A3AAPhase);
   Parameters.aAdI = Result.A3AAA1ZZ * sin(Result.A3AAPhase);

   ProjectionHelper Projection(SignalTree, BackgroundTree);

   TH1D HHMass("HHMass", "Projection of HMass", 40, 115, 135);
   TH1D HZMass("HZMass", "Projection of ZMass", 40, 40, 120);
   TH1D HZ2Mass("HZ2Mass", "Projection of Z2Mass", 40, 12, 80);
   TH1D HPhi0("HPhi0", "Projection of Phi0", 25, -PI, PI);
   TH1D HCosTheta0("HCosTheta0", "Projection of CosTheta0", 25, -1, 1);
   TH1D HPhi("HPhi", "Projection of Phi", 20, -PI, PI);
   TH1D HCosTheta1("HCosTheta1", "Projection of CosTheta1", 25, -1, 1);
   TH1D HCosTheta2("HCosTheta2", "Projection of CosTheta2", 25, -1, 1);

   int EMCount = Result.Sem + Result.Bem;
   int MECount = Result.Sme + Result.Bme;
   int EECount = Result.See + Result.Bee;
   int MMCount = Result.Smm + Result.Bmm;

   for(int i = 0; i < (int)E.size(); i++)
   {
      if(E[i].Phi0 > PI)   E[i].Phi0 = E[i].Phi0 - 2 * PI;
      if(E[i].Phi > PI)    E[i].Phi = E[i].Phi - 2 * PI;

      HHMass.Fill(E[i].HMass);
      HZMass.Fill(E[i].ZMass);
      HZ2Mass.Fill(E[i].Z2Mass);
      HPhi0.Fill(E[i].Phi0);
      HCosTheta0.Fill(cos(E[i].Theta0));
      HPhi.Fill(E[i].Phi);
      HCosTheta1.Fill(cos(E[i].Theta1));
      HCosTheta2.Fill(cos(E[i].Theta2));
   }
   
   TH1D HPDFHMass("HPDFHMass", "Projection of HMass", 60, 115, 135);
   TH1D HPDFZMass("HPDFZMass", "Projection of ZMass", 60, 40, 120);
   TH1D HPDFZ2Mass("HPDFZ2Mass", "Projection of Z2Mass", 60, 12, 80);
   TH1D HPDFPhi0("HPDFPhi0", "Projection of Phi0", 40, -PI, PI);
   TH1D HPDFCosTheta0("HPDFCosTheta0", "Projection of CosTheta0", 40, -1, 1);
   TH1D HPDFPhi("HPDFPhi", "Projection of Phi", 30, -PI, PI);
   TH1D HPDFCosTheta1("HPDFCosTheta1", "Projection of CosTheta1", 40, -1, 1);
   TH1D HPDFCosTheta2("HPDFCosTheta2", "Projection of CosTheta2", 40, -1, 1);

   Projection.FillProjection(HPDFHMass, ProjectionHelper::DimensionMH, HHMass.Integral() * (135 - 115) / 40,
      Parameters, EECount, MMCount, EMCount, MECount,
      Result.Fee, Result.Fmm, Result.Fem, Result.Fme);
   Projection.FillProjection(HPDFZMass, ProjectionHelper::DimensionM1, HZMass.Integral() * (120 - 40) / 40,
      Parameters, EECount, MMCount, EMCount, MECount,
      Result.Fee, Result.Fmm, Result.Fem, Result.Fme);
   Projection.FillProjection(HPDFZ2Mass, ProjectionHelper::DimensionM2, HZ2Mass.Integral() * (80 - 12) / 40,
      Parameters, EECount, MMCount, EMCount, MECount,
      Result.Fee, Result.Fmm, Result.Fem, Result.Fme);
   Projection.FillProjection(HPDFPhi0, ProjectionHelper::DimensionPhi0, HPhi0.Integral() * (2 * PI) / 25,
      Parameters, EECount, MMCount, EMCount, MECount,
      Result.Fee, Result.Fmm, Result.Fem, Result.Fme);
   Projection.FillProjection(HPDFCosTheta0, ProjectionHelper::DimensionCosTheta0, HCosTheta0.Integral() * 2 / 25,
      Parameters, EECount, MMCount, EMCount, MECount,
      Result.Fee, Result.Fmm, Result.Fem, Result.Fme);
   Projection.FillProjection(HPDFPhi, ProjectionHelper::DimensionPhi, HPhi.Integral() * (2 * PI) / 20,
      Parameters, EECount, MMCount, EMCount, MECount,
      Result.Fee, Result.Fmm, Result.Fem, Result.Fme);
   Projection.FillProjection(HPDFCosTheta1, ProjectionHelper::DimensionCosTheta1, HCosTheta1.Integral() * 2 / 25,
      Parameters, EECount, MMCount, EMCount, MECount,
      Result.Fee, Result.Fmm, Result.Fem, Result.Fme);
   Projection.FillProjection(HPDFCosTheta2, ProjectionHelper::DimensionCosTheta2, HCosTheta2.Integral() * 2 / 25,
      Parameters, EECount, MMCount, EMCount, MECount,
      Result.Fee, Result.Fmm, Result.Fem, Result.Fme);

   HHMass.SetStats(0);
   HZMass.SetStats(0);
   HZ2Mass.SetStats(0);
   HPhi0.SetStats(0);
   HCosTheta0.SetStats(0);
   HPhi.SetStats(0);
   HCosTheta1.SetStats(0);
   HCosTheta2.SetStats(0);
   
   HHMass.SetMinimum(0);
   HZMass.SetMinimum(0);
   HZ2Mass.SetMinimum(0);
   HPhi0.SetMinimum(0);
   HCosTheta0.SetMinimum(0);
   HPhi.SetMinimum(0);
   HCosTheta1.SetMinimum(0);
   HCosTheta2.SetMinimum(0);
   
   HHMass.SetMarkerStyle(20);
   HZMass.SetMarkerStyle(20);
   HZ2Mass.SetMarkerStyle(20);
   HPhi0.SetMarkerStyle(20);
   HCosTheta0.SetMarkerStyle(20);
   HPhi.SetMarkerStyle(20);
   HCosTheta1.SetMarkerStyle(20);
   HCosTheta2.SetMarkerStyle(20);
   
   HHMass.SetLineWidth(2);
   HZMass.SetLineWidth(2);
   HZ2Mass.SetLineWidth(2);
   HPhi0.SetLineWidth(2);
   HCosTheta0.SetLineWidth(2);
   HPhi.SetLineWidth(2);
   HCosTheta1.SetLineWidth(2);
   HCosTheta2.SetLineWidth(2);

   HPDFHMass.SetLineWidth(2);
   HPDFZMass.SetLineWidth(2);
   HPDFZ2Mass.SetLineWidth(2);
   HPDFPhi0.SetLineWidth(2);
   HPDFCosTheta0.SetLineWidth(2);
   HPDFPhi.SetLineWidth(2);
   HPDFCosTheta1.SetLineWidth(2);
   HPDFCosTheta2.SetLineWidth(2);

   TCanvas C;

   HHMass.Draw("error");
   HPDFHMass.Draw("same");
   PsFile->AddCanvas(C);

   HZMass.Draw("error");
   HPDFZMass.Draw("same");
   PsFile->AddCanvas(C);

   HZ2Mass.Draw("error");
   HPDFZ2Mass.Draw("same");
   PsFile->AddCanvas(C);

   HPhi0.Draw("error");
   HPDFPhi0.Draw("same");
   PsFile->AddCanvas(C);

   HCosTheta0.Draw("error");
   HPDFCosTheta0.Draw("same");
   PsFile->AddCanvas(C);

   HPhi.Draw("error");
   HPDFPhi.Draw("same");
   PsFile->AddCanvas(C);

   HCosTheta1.Draw("error");
   HPDFCosTheta1.Draw("same");
   PsFile->AddCanvas(C);

   HCosTheta2.Draw("error");
   HPDFCosTheta2.Draw("same");
   PsFile->AddCanvas(C);

   BackgroundFile.Close();
   SignalFile.Close();
   */
}


