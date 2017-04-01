#include <vector>
#include <iostream>
using namespace std;

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

#include "FitClass.h"

FitClass::FitClass()
{
   EventsEM.clear();
   EventsEE.clear();
}
   
double FitClass::Evaluate(const double *Parameters)
{
   FullAVVBasis A;

   for(int i = 0; i < 8; i++)   A.A[i+0*8] = Parameters[i+0*8];   // ZZ
   for(int i = 0; i < 8; i++)   A.A[i+1*8] = Parameters[i+1*8];   // ZV
   for(int i = 0; i < 8; i++)   A.A[i+2*8] = Parameters[i+2*8];   // ZA
   for(int i = 0; i < 8; i++)   A.A[i+3*8] = Parameters[i+1*8];   // VZ
   for(int i = 0; i < 8; i++)   A.A[i+4*8] = Parameters[i+3*8];   // VV
   for(int i = 0; i < 8; i++)   A.A[i+5*8] = Parameters[i+4*8];   // VA
   for(int i = 0; i < 8; i++)   A.A[i+6*8] = Parameters[i+2*8];   // AZ
   for(int i = 0; i < 8; i++)   A.A[i+7*8] = Parameters[i+4*8];   // AV
   for(int i = 0; i < 8; i++)   A.A[i+8*8] = Parameters[i+5*8];   // AA

   double FEM = Parameters[48];
   double FEE = Parameters[49];

   double LL = 0;

   for(int i = 0; i < (int)EventsEM.size(); i++)
      LL = LL + log(EventsEM[i]->Apply(A, FEM));
   for(int i = 0; i < (int)EventsEE.size(); i++)
      LL = LL + log(EventsEE[i]->Apply(A, FEE));
   
   return -2 * LL;
}

void FitClass::AddPoint(const Likelihood &NewPoint, bool IsEM)
{
   if(IsEM == true)
      EventsEM.push_back(&NewPoint);
   else
      EventsEE.push_back(&NewPoint);
}

FitResult FitClass::DoFit(const FitConfiguration &Configuration)
{
   string ParameterNames[48] =
   {
      "A1ZZR", "A1ZZI", "A2ZZR", "A2ZZI", "A3ZZR", "A3ZZI", "A4ZZR", "A4ZZI",
      "A1ZVR", "A1ZVI", "A2ZVR", "A2ZVI", "A3ZVR", "A3ZVI", "A4ZVR", "A4ZVI",
      "A1ZAR", "A1ZAI", "A2ZAR", "A2ZAI", "A3ZAR", "A3ZAI", "A4ZAR", "A4ZAI",
      "A1VVR", "A1VVI", "A2VVR", "A2VVI", "A3VVR", "A3VVI", "A4VVR", "A4VVI",
      "A1VAR", "A1VAI", "A2VAR", "A2VAI", "A3VAR", "A3VAI", "A4VAR", "A4VAI",
      "A1AAR", "A1AAI", "A2AAR", "A2AAI", "A3AAR", "A3AAI", "A4AAR", "A4AAI",
   };

   int FloatCount = Configuration.NumberOfFloats();

   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   if(FloatCount > 0)
   {
      Worker->SetPrintLevel(-2);
      Worker->SetMaxFunctionCalls(1e9);
      Worker->SetMaxIterations(1e9);
      // Worker->SetTolerance(1e-10);
      Worker->SetStrategy(1);   // 0 = speed, 2 = robustness, 1 is in the middle

      ROOT::Math::Functor Function(this, &FitClass::Evaluate, 50);
      Worker->SetFunction(Function);

      double StepSize[50] = {0};
      for(int i = 0; i < 48; i++)
      {
         if(Configuration.FloatAVV[i] == true)
            StepSize[i] = 0.1;
         else
            StepSize[i] = 0.0;
      }
      StepSize[48] = (Configuration.FloatFEM == true) ? 0.1 : 0.0;
      StepSize[49] = (Configuration.FloatFEE == true) ? 0.1 : 0.0;

      for(int i = 0; i < 48; i++)
         Worker->SetLimitedVariable(i, ParameterNames[i], Configuration.AVV[i], StepSize[i], -1000, 1000);
      Worker->SetLimitedVariable(48, "FEM", Configuration.FEM, StepSize[48], 0, 1);
      Worker->SetLimitedVariable(49, "FEE", Configuration.FEE, StepSize[49], 0, 1);

      Worker->Minimize();
   }

   double TruthParameters[50] = {0};
   for(int i = 0; i < 48; i++)
      TruthParameters[i] = Configuration.AVV[i];
   TruthParameters[48] = Configuration.FEM;
   TruthParameters[49] = Configuration.FEE;

   double ZeroVector[50] = {0};

   const double *Parameters = (FloatCount > 0) ? Worker->X() : TruthParameters;
   const double *Errors = (FloatCount > 0) ? Worker->Errors() : ZeroVector;

   FitResult Result;

   for(int i = 0; i < 8; i++)   Result.AVV.A[i+0*8] = Parameters[i+0*8];   // ZZ
   for(int i = 0; i < 8; i++)   Result.AVV.A[i+1*8] = Parameters[i+1*8];   // ZV
   for(int i = 0; i < 8; i++)   Result.AVV.A[i+2*8] = Parameters[i+2*8];   // ZA
   for(int i = 0; i < 8; i++)   Result.AVV.A[i+3*8] = Parameters[i+1*8];   // VZ
   for(int i = 0; i < 8; i++)   Result.AVV.A[i+4*8] = Parameters[i+3*8];   // VV
   for(int i = 0; i < 8; i++)   Result.AVV.A[i+5*8] = Parameters[i+4*8];   // VA
   for(int i = 0; i < 8; i++)   Result.AVV.A[i+6*8] = Parameters[i+2*8];   // AZ
   for(int i = 0; i < 8; i++)   Result.AVV.A[i+7*8] = Parameters[i+4*8];   // AV
   for(int i = 0; i < 8; i++)   Result.AVV.A[i+8*8] = Parameters[i+5*8];   // AA
   
   for(int i = 0; i < 8; i++)   Result.AVVError.A[i+0*8] = Errors[i+0*8];   // ZZ
   for(int i = 0; i < 8; i++)   Result.AVVError.A[i+1*8] = Errors[i+1*8];   // ZV
   for(int i = 0; i < 8; i++)   Result.AVVError.A[i+2*8] = Errors[i+2*8];   // ZA
   for(int i = 0; i < 8; i++)   Result.AVVError.A[i+3*8] = Errors[i+1*8];   // VZ
   for(int i = 0; i < 8; i++)   Result.AVVError.A[i+4*8] = Errors[i+3*8];   // VV
   for(int i = 0; i < 8; i++)   Result.AVVError.A[i+5*8] = Errors[i+4*8];   // VA
   for(int i = 0; i < 8; i++)   Result.AVVError.A[i+6*8] = Errors[i+2*8];   // AZ
   for(int i = 0; i < 8; i++)   Result.AVVError.A[i+7*8] = Errors[i+4*8];   // AV
   for(int i = 0; i < 8; i++)   Result.AVVError.A[i+8*8] = Errors[i+5*8];   // AA
   
   Result.FEM = Parameters[48];   Result.FEMError = Errors[48];
   Result.FEE = Parameters[49];   Result.FEEError = Errors[49];

   Result.TruthLL = Evaluate(TruthParameters);
   Result.BestLL = Evaluate(Parameters);
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   return Result;
}

FitConfiguration::FitConfiguration()
{
   FEM = 0;
   FloatFEM = false;
   
   FEE = 0;
   FloatFEE = false;
   
   for(int i = 0; i < 48; i++)
   {
      AVV[i] = 0;
      FloatAVV[i] = false;
   }
}

FitConfiguration::FitConfiguration(FullAVVBasis &A)
{
   FEM = 0;
   FloatFEM = false;
   
   FEE = 0;
   FloatFEE = false;
   
   for(int i = 0; i < 48; i++)
   {
      AVV[i] = 0;
      FloatAVV[i] = false;
   }

   SetAVV(A);
}

void FitConfiguration::SetAVV(FullAVVBasis &A)
{
   for(int i = 0; i < 8; i++)   AVV[i+0*8] = A.A[i+0*8];   // ZZ
   for(int i = 0; i < 8; i++)   AVV[i+1*8] = A.A[i+1*8];   // ZV
   for(int i = 0; i < 8; i++)   AVV[i+2*8] = A.A[i+2*8];   // ZA
   for(int i = 0; i < 8; i++)   AVV[i+3*8] = A.A[i+4*8];   // VV
   for(int i = 0; i < 8; i++)   AVV[i+4*8] = A.A[i+5*8];   // VA
   for(int i = 0; i < 8; i++)   AVV[i+5*8] = A.A[i+8*8];   // AA
}

int FitConfiguration::NumberOfFloats() const
{
   int Result = 0;

   for(int i = 0; i < 48; i++)
      if(FloatAVV[i] == true)
         Result = Result + 1;

   if(FloatFEM == true)
      Result = Result + 1;
   if(FloatFEE == true)
      Result = Result + 1;

   return Result;
}




