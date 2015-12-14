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

#include "FitClass.h"

#define PI 3.14159265358979323846264338327950288479716939937510

FitConfiguration::FitConfiguration()
{
   SetFloatPhis("YYY");
   SetFloatPhases("NNNN");

   SetInitialPhis(ListToVector(3, 0, 0, 0));
   SetInitialPhases(ListToVector(4, 0, 0, 0));
}

FitConfiguration::FitConfiguration(string FloatPhis, string FloatPhases)
{
   SetFloatPhis(FloatPhis);
   SetFloatPhases(FloatPhases);

   SetInitialPhis(ListToVector(3, 0, 0, 0));
   SetInitialPhases(ListToVector(4, 0, 0, 0, 0));
}
   
FitConfiguration::FitConfiguration(string FloatPhis, string FloatPhases,
   vector<double> Phis, vector<double> Phases)
{
   SetFloatPhis(FloatPhis);
   SetFloatPhases(FloatPhases);

   SetInitialPhis(Phis);
   SetInitialPhases(Phases);
}

FitConfiguration::~FitConfiguration()
{
}

void FitConfiguration::SetFloats(string FloatPhis, string FloatPhases)
{
   SetFloatPhis(FloatPhis);
   SetFloatPhases(FloatPhases);
}

void FitConfiguration::SetFloatPhis(string FloatPhis)
{
   for(int i = 0; i < 3; i++)
   {
      FloatPhi[i] = false;
      if(FloatPhis.size() > i && FloatPhis[i] == 'Y')
         FloatPhi[i] = true;
   }
}

void FitConfiguration::SetFloatPhases(string FloatPhases)
{
   for(int i = 0; i < 4; i++)
   {
      FloatPhase[i] = false;
      if(FloatPhases.size() > i && FloatPhases[i] == 'Y')
         FloatPhase[i] = true;
   }
}

void FitConfiguration::SetInitialPhis(const vector<double> Phis)
{
   for(int i = 0; i < 3; i++)
   {
      PhiInitialValue[i] = 0;
      if(Phis.size() > i)
         PhiInitialValue[i] = Phis[i];
   }
}

void FitConfiguration::SetInitialPhases(const vector<double> Phases)
{
   for(int i = 0; i < 4; i++)
   {
      PhaseInitialValue[i] = 0;
      if(Phases.size() > i)
         PhaseInitialValue[i] = Phases[i];
   }
}

int FitConfiguration::TotalNumberOfFloats()
{
   cerr << "Total number of floats not implemented yet!  Returning zero." << endl;

   int Count = 0;
   return Count;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double AZA = cos(Parameters[0]);
   double AAA = sin(Parameters[0]);

   double A2ZA = AZA * cos(Parameters[1]);
   double A3ZA = AZA * sin(Parameters[1]);
   double A2AA = AAA * cos(Parameters[2]);
   double A3AA = AAA * sin(Parameters[2]);

   double A2ZAR = A2ZA * cos(Parameters[3]);
   double A2ZAI = A2ZA * sin(Parameters[3]);
   double A3ZAR = A3ZA * cos(Parameters[4]);
   double A3ZAI = A3ZA * sin(Parameters[4]);
   double A2AAR = A2AA * cos(Parameters[5]);
   double A2AAI = A2AA * sin(Parameters[5]);
   double A3AAR = A3AA * cos(Parameters[6]);
   double A3AAI = A3AA * sin(Parameters[6]);

   double LogTotal = 0;
   
   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value = 0, Integral = 0, Likelihood = 0;

      Value
         = A2ZAR * A2ZAR * V[0][iS]
         + A2ZAI * A2ZAI * V[1][iS]
         + A3ZAR * A3ZAR * V[2][iS]
         + A3ZAI * A3ZAI * V[3][iS]
         + A2AAR * A2AAR * V[4][iS]
         + A2AAI * A2AAI * V[5][iS]
         + A3AAR * A3AAR * V[6][iS]
         + A3AAI * A3AAI * V[7][iS]
         + A2ZAR * A2ZAI * V[8][iS]
         + A2ZAR * A3ZAR * V[9][iS]
         + A2ZAR * A3ZAI * V[10][iS]
         + A2ZAR * A2AAR * V[11][iS]
         + A2ZAR * A2AAI * V[12][iS]
         + A2ZAR * A3AAR * V[13][iS]
         + A2ZAR * A3AAI * V[14][iS]
         + A2ZAI * A3ZAR * V[15][iS]
         + A2ZAI * A3ZAI * V[16][iS]
         + A2ZAI * A2AAR * V[17][iS]
         + A2ZAI * A2AAI * V[18][iS]
         + A2ZAI * A3AAR * V[19][iS]
         + A2ZAI * A3AAI * V[20][iS]
         + A3ZAR * A3ZAI * V[21][iS]
         + A3ZAR * A2AAR * V[22][iS]
         + A3ZAR * A2AAI * V[23][iS]
         + A3ZAR * A3AAR * V[24][iS]
         + A3ZAR * A3AAI * V[25][iS]
         + A3ZAI * A2AAR * V[26][iS]
         + A3ZAI * A2AAI * V[27][iS]
         + A3ZAI * A3AAR * V[28][iS]
         + A3ZAI * A3AAI * V[29][iS]
         + A2AAR * A2AAI * V[30][iS]
         + A2AAR * A3AAR * V[31][iS]
         + A2AAR * A3AAI * V[32][iS]
         + A2AAI * A3AAR * V[33][iS]
         + A2AAI * A3AAI * V[34][iS]
         + A3AAR * A3AAI * V[35][iS];
      Integral
         = A2ZAR * A2ZAR * I[0][iS]
         + A2ZAI * A2ZAI * I[1][iS]
         + A3ZAR * A3ZAR * I[2][iS]
         + A3ZAI * A3ZAI * I[3][iS]
         + A2AAR * A2AAR * I[4][iS]
         + A2AAI * A2AAI * I[5][iS]
         + A3AAR * A3AAR * I[6][iS]
         + A3AAI * A3AAI * I[7][iS]
         + A2ZAR * A2ZAI * I[8][iS]
         + A2ZAR * A3ZAR * I[9][iS]
         + A2ZAR * A3ZAI * I[10][iS]
         + A2ZAR * A2AAR * I[11][iS]
         + A2ZAR * A2AAI * I[12][iS]
         + A2ZAR * A3AAR * I[13][iS]
         + A2ZAR * A3AAI * I[14][iS]
         + A2ZAI * A3ZAR * I[15][iS]
         + A2ZAI * A3ZAI * I[16][iS]
         + A2ZAI * A2AAR * I[17][iS]
         + A2ZAI * A2AAI * I[18][iS]
         + A2ZAI * A3AAR * I[19][iS]
         + A2ZAI * A3AAI * I[20][iS]
         + A3ZAR * A3ZAI * I[21][iS]
         + A3ZAR * A2AAR * I[22][iS]
         + A3ZAR * A2AAI * I[23][iS]
         + A3ZAR * A3AAR * I[24][iS]
         + A3ZAR * A3AAI * I[25][iS]
         + A3ZAI * A2AAR * I[26][iS]
         + A3ZAI * A2AAI * I[27][iS]
         + A3ZAI * A3AAR * I[28][iS]
         + A3ZAI * A3AAI * I[29][iS]
         + A2AAR * A2AAI * I[30][iS]
         + A2AAR * A3AAR * I[31][iS]
         + A2AAR * A3AAI * I[32][iS]
         + A2AAI * A3AAR * I[33][iS]
         + A2AAI * A3AAI * I[34][iS]
         + A3AAR * A3AAI * I[35][iS];

      Likelihood = Value / Integral;

      bool Good = true;
      if(Likelihood < 0)
         Good = false;
      if(Good == false)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      double SignalLikelihood = Likelihood;

      if(SignalLikelihood <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      LogTotal = LogTotal + log(SignalLikelihood);
   }

   return -LogTotal * 2;
}

void FitClass::AddPoint(SingleEvent &event)
{
   AddPoint(event.v, event.i, event.event);
}

void FitClass::AddPoint(double v[36], double i[36], ZAEventParameters &Event)
{
   for(int i1 = 0; i1 < 36; i1++)
   {
      V[i1].push_back(v[i1]);
      I[i1].push_back(i[i1]);
   }

   E.push_back(Event);

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   for(int i1 = 0; i1 < 36; i1++)
   {
      V[i1].clear();
      I[i1].clear();
   }

   E.clear();

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit(FitConfiguration configuration)
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(-2);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   Worker->SetTolerance(1e-10);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 7);
   Worker->SetFunction(Function);

   double StepSize[7] = {0};
   StepSize[0] = (configuration.FloatPhi[0] == true) ? 0.1 : 0;
   StepSize[1] = (configuration.FloatPhi[1] == true) ? 0.1 : 0;
   StepSize[2] = (configuration.FloatPhi[2] == true) ? 0.1 : 0;
   StepSize[3] = (configuration.FloatPhase[0] == true) ? 0.1 : 0;
   StepSize[4] = (configuration.FloatPhase[1] == true) ? 0.1 : 0;
   StepSize[5] = (configuration.FloatPhase[2] == true) ? 0.1 : 0;
   StepSize[6] = (configuration.FloatPhase[3] == true) ? 0.1 : 0;

   Worker->SetLimitedVariable(0, "PhiV",      configuration.PhiInitialValue[0],   StepSize[0], -1000, 1000);
   Worker->SetLimitedVariable(1, "PhiZA",     configuration.PhiInitialValue[1],   StepSize[1], -1000, 1000);
   Worker->SetLimitedVariable(2, "PhiAA",     configuration.PhiInitialValue[2],   StepSize[2], -1000, 1000);
   Worker->SetLimitedVariable(3, "PhaseA2ZA", configuration.PhaseInitialValue[0], StepSize[3], -1000, 1000);
   Worker->SetLimitedVariable(4, "PhaseA3ZA", configuration.PhaseInitialValue[1], StepSize[4], -1000, 1000);
   Worker->SetLimitedVariable(5, "PhaseA2AA", configuration.PhaseInitialValue[2], StepSize[5], -1000, 1000);
   Worker->SetLimitedVariable(6, "PhaseA3AA", configuration.PhaseInitialValue[3], StepSize[6], -1000, 1000);
   
   for(int i = 0; i < 10; i++)
      Worker->Minimize();   

   double TrueParameters[7] = {0};
   TrueParameters[0] = configuration.PhiInitialValue[0];
   TrueParameters[1] = configuration.PhiInitialValue[1];
   TrueParameters[2] = configuration.PhiInitialValue[2];
   TrueParameters[3] = configuration.PhaseInitialValue[0];
   TrueParameters[4] = configuration.PhaseInitialValue[1];
   TrueParameters[5] = configuration.PhaseInitialValue[2];
   TrueParameters[6] = configuration.PhaseInitialValue[3];

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;

   Result.Phi[0] = Parameters[0];
   Result.Phi[1] = Parameters[1];
   Result.Phi[2] = Parameters[2];
   Result.Phase[0] = Parameters[3];
   Result.Phase[1] = Parameters[4];
   Result.Phase[2] = Parameters[5];
   Result.Phase[3] = Parameters[6];
   
   Result.PhiError[0] = Errors[0];
   Result.PhiError[1] = Errors[1];
   Result.PhiError[2] = Errors[2];
   Result.PhaseError[0] = Errors[3];
   Result.PhaseError[1] = Errors[4];
   Result.PhaseError[2] = Errors[5];
   Result.PhaseError[3] = Errors[6];

   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   Result.TruthNLL = CalculateLogLikelihoodAll(TrueParameters);
   Result.BestNLL = CalculateLogLikelihoodAll(Parameters);

   delete Worker;

   return Result;
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




