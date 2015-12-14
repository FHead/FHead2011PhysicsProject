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

FitConfiguration::FitConfiguration()
{
   SetFloatAs("YYNNNN");
   SetFloatPhases("NNNNNN");
   SetFloatFractions("NNNN");
   SetFloatNs("NN");

   SetInitialRatios(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
   SetInitialNs(ListToVector(2, 0, 0));
}

FitConfiguration::FitConfiguration(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatFractions(FloatFractions);
   SetFloatNs(FloatNs);

   SetInitialRatios(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
   SetInitialNs(ListToVector(2, 0, 0));
}
   
FitConfiguration::FitConfiguration(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs,
   vector<double> Ratios, vector<double> Phases, vector<double> Fractions, vector<double> Ns)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatFractions(FloatFractions);
   SetFloatNs(FloatNs);

   SetInitialRatios(Ratios);
   SetInitialPhases(Phases);
   SetInitialFractions(Fractions);
   SetInitialNs(Ns);
}

FitConfiguration::~FitConfiguration()
{
}

void FitConfiguration::SetFloats(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatFractions(FloatFractions);
   SetFloatNs(FloatNs);
}

void FitConfiguration::SetFloatAs(string FloatAs)
{
   FloatA2ZZA1ZZ = false;
   FloatA3ZZA1ZZ = false;
   FloatA2ZAA1ZZ = false;
   FloatA3ZAA1ZZ = false;
   FloatA2AAA1ZZ = false;
   FloatA3AAA1ZZ = false;

   if(FloatAs.size() > 0 && FloatAs[0] == 'Y')   FloatA2ZZA1ZZ = true;
   if(FloatAs.size() > 1 && FloatAs[1] == 'Y')   FloatA3ZZA1ZZ = true;
   if(FloatAs.size() > 2 && FloatAs[2] == 'Y')   FloatA2ZAA1ZZ = true;
   if(FloatAs.size() > 3 && FloatAs[3] == 'Y')   FloatA3ZAA1ZZ = true;
   if(FloatAs.size() > 4 && FloatAs[4] == 'Y')   FloatA2AAA1ZZ = true;
   if(FloatAs.size() > 5 && FloatAs[5] == 'Y')   FloatA3AAA1ZZ = true;
}

void FitConfiguration::SetFloatPhases(string FloatPhases)
{
   FloatA2ZZPhase = false;
   FloatA3ZZPhase = false;
   FloatA2ZAPhase = false;
   FloatA3ZAPhase = false;
   FloatA2AAPhase = false;
   FloatA3AAPhase = false;

   if(FloatPhases.size() > 0 && FloatPhases[0] == 'Y')   FloatA2ZZPhase = true;
   if(FloatPhases.size() > 1 && FloatPhases[1] == 'Y')   FloatA3ZZPhase = true;
   if(FloatPhases.size() > 2 && FloatPhases[2] == 'Y')   FloatA2ZAPhase = true;
   if(FloatPhases.size() > 3 && FloatPhases[3] == 'Y')   FloatA3ZAPhase = true;
   if(FloatPhases.size() > 4 && FloatPhases[4] == 'Y')   FloatA2AAPhase = true;
   if(FloatPhases.size() > 5 && FloatPhases[5] == 'Y')   FloatA3AAPhase = true;
}

void FitConfiguration::SetFloatFractions(string FloatFractions)
{
   FloatFem = false;   FloatFme = false;   FloatFee = false;   FloatFmm = false;

   if(FloatFractions.size() > 0 && FloatFractions[0] == 'Y')   FloatFem = true;
   if(FloatFractions.size() > 1 && FloatFractions[1] == 'Y')   FloatFme = true;
   if(FloatFractions.size() > 2 && FloatFractions[2] == 'Y')   FloatFee = true;
   if(FloatFractions.size() > 3 && FloatFractions[3] == 'Y')   FloatFmm = true;
}

void FitConfiguration::SetFloatNs(string FloatNs)
{
   FloatN1 = false;   FloatN2 = false;

   if(FloatNs.size() > 0 && FloatNs[0] == 'Y')   FloatN1 = true;
   if(FloatNs.size() > 1 && FloatNs[1] == 'Y')   FloatN2 = true;
}
   
void FitConfiguration::SetInitialRatios(const vector<double> Ratios)
{
   if(Ratios.size() > 0)   A2ZZA1ZZInitialValue = Ratios[0];
   if(Ratios.size() > 1)   A3ZZA1ZZInitialValue = Ratios[1];
   if(Ratios.size() > 2)   A2ZAA1ZZInitialValue = Ratios[2];
   if(Ratios.size() > 3)   A3ZAA1ZZInitialValue = Ratios[3];
   if(Ratios.size() > 4)   A2AAA1ZZInitialValue = Ratios[4];
   if(Ratios.size() > 5)   A3AAA1ZZInitialValue = Ratios[5];
}

void FitConfiguration::SetInitialPhases(const vector<double> Phases)
{
   if(Phases.size() > 0)   A2ZZPhaseInitialValue = Phases[0];
   if(Phases.size() > 1)   A3ZZPhaseInitialValue = Phases[1];
   if(Phases.size() > 2)   A2ZAPhaseInitialValue = Phases[2];
   if(Phases.size() > 3)   A3ZAPhaseInitialValue = Phases[3];
   if(Phases.size() > 4)   A2AAPhaseInitialValue = Phases[4];
   if(Phases.size() > 5)   A3AAPhaseInitialValue = Phases[5];
}

void FitConfiguration::SetInitialFractions(const vector<double> Fractions)
{
   if(Fractions.size() > 0)   FemInitialValue = Fractions[0];
   if(Fractions.size() > 1)   FmeInitialValue = Fractions[1];
   if(Fractions.size() > 2)   FeeInitialValue = Fractions[2];
   if(Fractions.size() > 3)   FmmInitialValue = Fractions[3];
}

void FitConfiguration::SetInitialNs(const vector<double> Ns)
{
   if(Ns.size() > 0)   N1InitialValue = Ns[0];
   if(Ns.size() > 1)   N2InitialValue = Ns[1];
}
   
int FitConfiguration::TotalNumberOfFloats()
{
   int Count = 0;
   
   if(FloatA2ZZA1ZZ == true)     Count = Count + 1;
   if(FloatA2ZZPhase == true)    Count = Count + 1;
   if(FloatA3ZZA1ZZ == true)     Count = Count + 1;
   if(FloatA3ZZPhase == true)    Count = Count + 1;
   if(FloatA2ZAA1ZZ == true)     Count = Count + 1;
   if(FloatA2ZAPhase == true)    Count = Count + 1;
   if(FloatA3ZAA1ZZ == true)     Count = Count + 1;
   if(FloatA3ZAPhase == true)    Count = Count + 1;
   if(FloatA2AAA1ZZ == true)     Count = Count + 1;
   if(FloatA2AAPhase == true)    Count = Count + 1;
   if(FloatA3AAA1ZZ == true)     Count = Count + 1;
   if(FloatA3AAPhase == true)    Count = Count + 1;
   if(FloatFem == true)          Count = Count + 1;
   if(FloatFme == true)          Count = Count + 1;
   if(FloatFee == true)          Count = Count + 1;
   if(FloatFmm == true)          Count = Count + 1;
   if(FloatN1 == true)           Count = Count + 1;
   if(FloatN2 == true)           Count = Count + 1;

   return Count;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1ZZR = 1;
   double A2ZZR = Parameters[0] * cos(Parameters[1]);
   double A2ZZI = Parameters[0] * sin(Parameters[1]);
   double A3ZZR = Parameters[2] * cos(Parameters[3]);
   double A3ZZI = Parameters[2] * sin(Parameters[3]);
   double A2ZAR = Parameters[4] * cos(Parameters[5]);
   double A2ZAI = Parameters[4] * sin(Parameters[5]);
   double A3ZAR = Parameters[6] * cos(Parameters[7]);
   double A3ZAI = Parameters[6] * sin(Parameters[7]);
   double A2AAR = Parameters[8] * cos(Parameters[9]);
   double A2AAI = Parameters[8] * sin(Parameters[9]);
   double A3AAR = Parameters[10] * cos(Parameters[11]);
   double A3AAI = Parameters[10] * sin(Parameters[11]);
   // double A2ZZR = Parameters[0];
   // double A2ZZI = 0;
   // double A3ZZR = Parameters[2];
   // double A3ZZI = 0;
   // double A2ZAR = Parameters[4];
   // double A2ZAI = 0;
   // double A3ZAR = Parameters[6];
   // double A3ZAI = 0;
   // double A2AAR = Parameters[8];
   // double A2AAI = 0;
   // double A3AAR = Parameters[10];
   // double A3AAI = 0;
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

FitResultSummary FitClass::DoFit(FitConfiguration configuration)
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(-1);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   Worker->SetTolerance(1e-10);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 18);
   Worker->SetFunction(Function);

   double StepSize[18] = {0};
   StepSize[0] = (configuration.FloatA2ZZA1ZZ == true) ? 0.1 : 0;
   StepSize[1] = (configuration.FloatA2ZZPhase == true) ? 0.1 : 0;
   StepSize[2] = (configuration.FloatA3ZZA1ZZ == true) ? 0.1 : 0;
   StepSize[3] = (configuration.FloatA3ZZPhase == true) ? 0.1 : 0;
   StepSize[4] = (configuration.FloatA2ZAA1ZZ == true) ? 0.1 : 0;
   StepSize[5] = (configuration.FloatA2ZAPhase == true) ? 0.1 : 0;
   StepSize[6] = (configuration.FloatA3ZAA1ZZ == true) ? 0.1 : 0;
   StepSize[7] = (configuration.FloatA3ZAPhase == true) ? 0.1 : 0;
   StepSize[8] = (configuration.FloatA2AAA1ZZ == true) ? 0.1 : 0;
   StepSize[9] = (configuration.FloatA2AAPhase == true) ? 0.1 : 0;
   StepSize[10] = (configuration.FloatA3AAA1ZZ == true) ? 0.1 : 0;
   StepSize[11] = (configuration.FloatA3AAPhase == true) ? 0.1 : 0;
   StepSize[12] = (configuration.FloatFem == true) ? 0.1 : 0;
   StepSize[13] = (configuration.FloatFme == true) ? 0.1 : 0;
   StepSize[14] = (configuration.FloatFee == true) ? 0.1 : 0;
   StepSize[15] = (configuration.FloatFmm == true) ? 0.1 : 0;
   StepSize[16] = (configuration.FloatN1 == true) ? 0.1 : 0;
   StepSize[17] = (configuration.FloatN2 == true) ? 0.1 : 0;

   // double InitialValues[18] = {0, 0, 5.05, 0.0, 0., 0.0, -0, 0.0, 0, 0.0, 0, 0.0, 0, 0, 0, 0, 0, 0};
   // double StepSize[18] = {0.1, 0, 0.1, 0, 0.1, 0, 0.1, 0, 0.1, 0, 0.1, 0, 0, 0, 0, 0, 0, 0};

   Worker->SetLimitedVariable(0, "A2ZZA1ZZ",   configuration.A2ZZA1ZZInitialValue, StepSize[0], -1000, 1000);
   Worker->SetLimitedVariable(1, "A2ZZPhase",  configuration.A2ZZPhaseInitialValue, StepSize[1], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(2, "A3ZZA1ZZ",   configuration.A3ZZA1ZZInitialValue, StepSize[2], -1000, 1000);
   Worker->SetLimitedVariable(3, "A3ZZPhase",  configuration.A3ZZPhaseInitialValue, StepSize[3], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(4, "A2ZAA1ZZ",   configuration.A2ZAA1ZZInitialValue, StepSize[4], -1000, 1000);
   Worker->SetLimitedVariable(5, "A2ZAPhase",  configuration.A2ZAPhaseInitialValue, StepSize[5], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(6, "A3ZAA1ZZ",   configuration.A3ZAA1ZZInitialValue, StepSize[6], -1000, 1000);
   Worker->SetLimitedVariable(7, "A3ZAPhase",  configuration.A3ZAPhaseInitialValue, StepSize[7], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(8, "A2AAA1ZZ",   configuration.A2AAA1ZZInitialValue, StepSize[8], -1000, 1000);
   Worker->SetLimitedVariable(9, "A2AAPhase",  configuration.A2AAPhaseInitialValue, StepSize[9], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(10, "A3AAA1ZZ",  configuration.A3AAA1ZZInitialValue, StepSize[10], -1000, 1000);
   Worker->SetLimitedVariable(11, "A3AAPhase", configuration.A3AAPhaseInitialValue, StepSize[11], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(12, "Fem",       configuration.FemInitialValue, StepSize[12], 0, 1);
   Worker->SetLimitedVariable(13, "Fme",       configuration.FmeInitialValue, StepSize[13], 0, 1);
   Worker->SetLimitedVariable(14, "Fee",       configuration.FeeInitialValue, StepSize[14], 0, 1);
   Worker->SetLimitedVariable(15, "Fmm",       configuration.FmmInitialValue, StepSize[15], 0, 1);
   Worker->SetLimitedVariable(16, "N1",        configuration.N1InitialValue, StepSize[16], -5, 5);
   Worker->SetLimitedVariable(17, "N2",        configuration.N2InitialValue, StepSize[17], -5, 5);
   
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
   
   Result.InitialA2ZZ = configuration.A2ZZA1ZZInitialValue;
   Result.InitialA2ZZPhase = configuration.A2ZZPhaseInitialValue;
   Result.InitialA3ZZ = configuration.A3ZZA1ZZInitialValue;
   Result.InitialA3ZZPhase = configuration.A3ZZPhaseInitialValue;
   Result.InitialA2ZA = configuration.A2ZAA1ZZInitialValue;
   Result.InitialA2ZAPhase = configuration.A2ZAPhaseInitialValue;
   Result.InitialA3ZA = configuration.A3ZAA1ZZInitialValue;
   Result.InitialA3ZAPhase = configuration.A3ZAPhaseInitialValue;
   Result.InitialA2AA = configuration.A2AAA1ZZInitialValue;
   Result.InitialA2AAPhase = configuration.A2AAPhaseInitialValue;
   Result.InitialA3AA = configuration.A3AAA1ZZInitialValue;
   Result.InitialA3AAPhase = configuration.A3AAPhaseInitialValue;

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




