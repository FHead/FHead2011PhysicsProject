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

#include "ProjectionHelper.h"
#include "FitClass.h"

#define PI 3.14159265358979323846264338327950288479716939937510

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1R = 1;
   double A3R = Parameters[0] * cos(Parameters[1]);
   double A3I = Parameters[0] * sin(Parameters[1]);
   double A2R = Parameters[2] * cos(Parameters[3]);
   double A2I = Parameters[2] * sin(Parameters[3]);
   double Fem = Parameters[4];
   double Fme = Parameters[5];
   double Fee = Parameters[6];
   double Fmm = Parameters[7];
   double N1 = Parameters[8];
   double N2 = Parameters[9];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value[5] = {0}, Integral[5] = {0}, Likelihood[5] = {0};
      double LikelihoodB[5] = {0};

      for(int i = 0; i < 5; i++)
      {
         Value[i] = A1R * A1R * V[1][i][iS] + A2R * A2R * V[2][i][iS] + A2I * A2I * V[3][i][iS]
            + A3R * A3R * V[4][i][iS] + A3I * A3I * V[5][i][iS]
            + A1R * A2R * V[6][i][iS] + A1R * A2I * V[7][i][iS] + A1R * A3R * V[8][i][iS]
            + A1R * A3I * V[9][i][iS] + A2R * A2I * V[10][i][iS]
            + A2R * A3R * V[11][i][iS] + A2R * A3I * V[12][i][iS] + A2I * A3R * V[13][i][iS]
            + A2I * A3I * V[14][i][iS] + A3R * A3I * V[15][i][iS];
         Integral[i] = A1R * A1R * I[1][i][iS] + A2R * A2R * I[2][i][iS] + A2I * A2I * I[3][i][iS]
            + A3R * A3R * I[4][i][iS] + A3I * A3I * I[5][i][iS]
            + A1R * A2R * I[6][i][iS] + A1R * A2I * I[7][i][iS] + A1R * A3R * I[8][i][iS]
            + A1R * A3I * I[9][i][iS] + A2R * A2I * I[10][i][iS]
            + A2R * A3R * I[11][i][iS] + A2R * A3I * I[12][i][iS] + A2I * A3R * I[13][i][iS]
            + A2I * A3I * I[14][i][iS] + A3R * A3I * I[15][i][iS];
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

   return -LogTotal;
}

void FitClass::AddPoint(SingleEvent &event)
{
   AddPoint(event.v, event.i, event.event, event.state);
}

void FitClass::AddPoint(double v[16][5], double i[16][5], EventParameters &Event, string State)
{
   for(int i1 = 0; i1 < 16; i1++)
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
   for(int i1 = 0; i1 < 16; i1++)
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

   // Worker->SetPrintLevel(1);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   Worker->SetTolerance(1e-10);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 10);
   Worker->SetFunction(Function);

   double InitialValues[10] = {0, PI / 4, 0, PI / 2, 0, 0, 0, 0, 0, 0};
   double StepSizes[10] = {0.4, 0.05, 0.3, 0.05, 0.2, 0, 0, 0, 0, 0};

   switch(Mode)
   {
   case FITMODE_ALL:
      break;
   case FITMODE_SIGNALONLY:
      StepSizes[4] = 0;   InitialValues[4] = 0;
      break;
   case FITMODE_PHASEONLY:
      StepSizes[0] = 0;   InitialValues[0] = v1;
      StepSizes[2] = 0;   InitialValues[2] = v2;
      StepSizes[4] = 0.1; InitialValues[4] = 0.1;
      break;
   }

   Worker->SetLimitedVariable(0, "A3A1", InitialValues[0], StepSizes[0], -1000, 1000);
   Worker->SetLimitedVariable(1, "A3Phase", InitialValues[1], StepSizes[1], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(2, "A2A1", InitialValues[2], StepSizes[2], -1000, 1000);
   Worker->SetLimitedVariable(3, "A2Phase", InitialValues[3], StepSizes[3], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(4, "Fem", InitialValues[4], StepSizes[4], 0, 1);
   Worker->SetLimitedVariable(5, "Fme", InitialValues[5], StepSizes[5], 0, 1);
   Worker->SetLimitedVariable(6, "Fee", InitialValues[6], StepSizes[6], 0, 1);
   Worker->SetLimitedVariable(7, "Fmm", InitialValues[7], StepSizes[7], 0, 1);
   Worker->SetLimitedVariable(8, "N1", InitialValues[8], StepSizes[8], -5, 5);
   Worker->SetLimitedVariable(9, "N2", InitialValues[9], StepSizes[9], -5, 5);
   
   Worker->Minimize();

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.A3A1 = Parameters[0];
   Result.A3A1Error = Errors[0];
   Result.A3Phase = Parameters[1];
   Result.A3PhaseError = Errors[1];
   Result.A2A1 = Parameters[2];
   
   Result.A2Phase = Parameters[3];
   Result.A2PhaseError = Errors[3];
   Result.Fem = Parameters[4];
   Result.FemError = Errors[4];
   Result.Fme = Parameters[5];
   Result.FmeError = Errors[5];
   Result.Fee = Parameters[6];
   Result.FeeError = Errors[6];
   Result.Fmm = Parameters[7];
   Result.FmmError = Errors[7];
   Result.N1 = Parameters[8];
   Result.N1Error = Errors[8];
   Result.N2 = Parameters[9];
   Result.N2Error = Errors[9];
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


