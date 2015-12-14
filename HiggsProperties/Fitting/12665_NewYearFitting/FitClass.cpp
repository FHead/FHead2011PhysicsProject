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
   SetInitialFractions(ListToVector(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialNs(ListToVector(5, 0, 0, 0, 0, 0));
}

FitConfiguration::FitConfiguration(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatFractions(FloatFractions);
   SetFloatNs(FloatNs);

   SetInitialRatios(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialNs(ListToVector(5, 0, 0, 0, 0, 0));
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
   FloatFem = false;       FloatFme = false;       FloatFee = false;       FloatFmm = false;
   FloatFZJem = false;     FloatFZJme = false;     FloatFZJee = false;     FloatFZJmm = false;
   FloatFggZZem = false;   FloatFggZZme = false;   FloatFggZZee = false;   FloatFggZZmm = false;

   if(FloatFractions.size() > 0 && FloatFractions[0] == 'Y')     FloatFem = true;
   if(FloatFractions.size() > 1 && FloatFractions[1] == 'Y')     FloatFme = true;
   if(FloatFractions.size() > 2 && FloatFractions[2] == 'Y')     FloatFee = true;
   if(FloatFractions.size() > 3 && FloatFractions[3] == 'Y')     FloatFmm = true;
   
   if(FloatFractions.size() > 4 && FloatFractions[4] == 'Y')     FloatFZJem = true;
   if(FloatFractions.size() > 5 && FloatFractions[5] == 'Y')     FloatFZJme = true;
   if(FloatFractions.size() > 6 && FloatFractions[6] == 'Y')     FloatFZJee = true;
   if(FloatFractions.size() > 7 && FloatFractions[7] == 'Y')     FloatFZJmm = true;
   
   if(FloatFractions.size() > 8 && FloatFractions[8] == 'Y')     FloatFggZZem = true;
   if(FloatFractions.size() > 9 && FloatFractions[9] == 'Y')     FloatFggZZme = true;
   if(FloatFractions.size() > 10 && FloatFractions[10] == 'Y')   FloatFggZZee = true;
   if(FloatFractions.size() > 11 && FloatFractions[11] == 'Y')   FloatFggZZmm = true;
}

void FitConfiguration::SetFloatNs(string FloatNs)
{
   FloatN1 = false;   FloatN2 = false;   FloatN3 = false;   FloatN4 = false;
   FloatN5 = false;   FloatN6 = false;   FloatN7 = false;

   if(FloatNs.size() > 0 && FloatNs[0] == 'Y')   FloatN1 = true;
   if(FloatNs.size() > 1 && FloatNs[1] == 'Y')   FloatN2 = true;
   if(FloatNs.size() > 2 && FloatNs[2] == 'Y')   FloatN3 = true;
   if(FloatNs.size() > 3 && FloatNs[3] == 'Y')   FloatN4 = true;
   if(FloatNs.size() > 4 && FloatNs[4] == 'Y')   FloatN5 = true;
   if(FloatNs.size() > 5 && FloatNs[5] == 'Y')   FloatN6 = true;
   if(FloatNs.size() > 6 && FloatNs[6] == 'Y')   FloatN7 = true;
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
   if(Fractions.size() > 0)    FemInitialValue = Fractions[0];
   if(Fractions.size() > 1)    FmeInitialValue = Fractions[1];
   if(Fractions.size() > 2)    FeeInitialValue = Fractions[2];
   if(Fractions.size() > 3)    FmmInitialValue = Fractions[3];
   
   if(Fractions.size() > 4)    FZJemInitialValue = Fractions[4];
   if(Fractions.size() > 5)    FZJmeInitialValue = Fractions[5];
   if(Fractions.size() > 6)    FZJeeInitialValue = Fractions[6];
   if(Fractions.size() > 7)    FZJmmInitialValue = Fractions[7];
   
   if(Fractions.size() > 8)    FggZZemInitialValue = Fractions[8];
   if(Fractions.size() > 9)    FggZZmeInitialValue = Fractions[9];
   if(Fractions.size() > 10)   FggZZeeInitialValue = Fractions[10];
   if(Fractions.size() > 10)   FggZZmmInitialValue = Fractions[11];
}

void FitConfiguration::SetInitialNs(const vector<double> Ns)
{
   if(Ns.size() > 0)   N1InitialValue = Ns[0];
   if(Ns.size() > 1)   N2InitialValue = Ns[1];
   if(Ns.size() > 2)   N3InitialValue = Ns[2];
   if(Ns.size() > 3)   N4InitialValue = Ns[3];
   if(Ns.size() > 4)   N5InitialValue = Ns[4];
   if(Ns.size() > 5)   N6InitialValue = Ns[5];
   if(Ns.size() > 6)   N7InitialValue = Ns[6];
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
   if(FloatFZJem == true)        Count = Count + 1;
   if(FloatFZJme == true)        Count = Count + 1;
   if(FloatFZJee == true)        Count = Count + 1;
   if(FloatFZJmm == true)        Count = Count + 1;
   if(FloatFggZZem == true)      Count = Count + 1;
   if(FloatFggZZme == true)      Count = Count + 1;
   if(FloatFggZZee == true)      Count = Count + 1;
   if(FloatFggZZmm == true)      Count = Count + 1;
   if(FloatN1 == true)           Count = Count + 1;
   if(FloatN2 == true)           Count = Count + 1;
   if(FloatN3 == true)           Count = Count + 1;
   if(FloatN4 == true)           Count = Count + 1;
   if(FloatN5 == true)           Count = Count + 1;
   if(FloatN6 == true)           Count = Count + 1;
   if(FloatN7 == true)           Count = Count + 1;

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
   double Fem = Parameters[12];
   double Fme = Parameters[13];
   double Fee = Parameters[14];
   double Fmm = Parameters[15];
   double FZJem = Parameters[16];
   double FZJme = Parameters[17];
   double FZJee = Parameters[18];
   double FZJmm = Parameters[19];
   double FggZZem = Parameters[20];
   double FggZZme = Parameters[21];
   double FggZZee = Parameters[22];
   double FggZZmm = Parameters[23];
   double N1 = Parameters[24];
   double N2 = Parameters[25];
   double N3 = Parameters[26];
   double N4 = Parameters[27];
   double N5 = Parameters[28];
   double N6 = Parameters[29];
   double N7 = Parameters[30];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value[13] = {0}, Integral[13] = {0}, Likelihood[13] = {0};
      double LikelihoodB[13] = {0}, LikelihoodZJ[13] = {0}, LikelihoodBgg[13] = {0};

      for(int i = 0; i < 13; i++)
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

         LikelihoodZJ[i] = V2[0][i][iS] / I2[0][i][iS];
         
         LikelihoodBgg[i] = V2[1][i][iS] / I2[1][i][iS];
      }

      bool Good = true;
      for(int i = 0; i < 13; i++)
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
      double LSb3 = (N3 > 0) ? (Likelihood[5] - Likelihood[0]) : (Likelihood[0] - Likelihood[6]);
      double LSb4 = (N4 > 0) ? (Likelihood[7] - Likelihood[0]) : (Likelihood[0] - Likelihood[8]);
      double LSb5 = 0;
      double LBa = LikelihoodB[0];
      double LBb1 = (N1 > 0) ? (LikelihoodB[1] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[2]);
      double LBb2 = (N2 > 0) ? (LikelihoodB[3] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[4]);
      double LBb3 = (N3 > 0) ? (LikelihoodB[5] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[5]);
      double LBb4 = (N4 > 0) ? (LikelihoodB[7] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[7]);
      double LBb5 = 0;
      double LZJa = LikelihoodZJ[0];
      double LZJb1 = (N1 > 0) ? (LikelihoodZJ[1] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[2]);
      double LZJb2 = (N2 > 0) ? (LikelihoodZJ[3] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[4]);
      double LZJb3 = (N3 > 0) ? (LikelihoodZJ[5] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[5]);
      double LZJb4 = (N4 > 0) ? (LikelihoodZJ[7] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[7]);
      double LZJb5 = 0;
      double LBgga = LikelihoodBgg[0];
      double LBggb1 = (N1 > 0) ? (LikelihoodBgg[1] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[2]);
      double LBggb2 = (N2 > 0) ? (LikelihoodBgg[3] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[4]);
      double LBggb3 = (N3 > 0) ? (LikelihoodBgg[5] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[5]);
      double LBggb4 = (N4 > 0) ? (LikelihoodBgg[7] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[7]);
      double LBggb5 = 0;

      if(N5 > 1)        LSb5 = (Likelihood[12] - Likelihood[11]) / 2;
      else if(N5 > 0)   LSb5 = (Likelihood[11] - Likelihood[0]) / 1;
      else if(N5 > 1)   LSb5 = (Likelihood[0] - Likelihood[10]) / 1;
      else              LSb5 = (Likelihood[10] - Likelihood[9]) / 2;

      if(N5 > 1)        LBb5 = (LikelihoodB[12] - LikelihoodB[11]) / 2;
      else if(N5 > 0)   LBb5 = (LikelihoodB[11] - LikelihoodB[0]) / 1;
      else if(N5 > 1)   LBb5 = (LikelihoodB[0] - LikelihoodB[10]) / 1;
      else              LBb5 = (LikelihoodB[10] - LikelihoodB[9]) / 2;

      if(N5 > 1)        LZJb5 = (LikelihoodZJ[12] - LikelihoodZJ[11]) / 2;
      else if(N5 > 0)   LZJb5 = (LikelihoodZJ[11] - LikelihoodZJ[0]) / 1;
      else if(N5 > 1)   LZJb5 = (LikelihoodZJ[0] - LikelihoodZJ[10]) / 1;
      else              LZJb5 = (LikelihoodZJ[10] - LikelihoodZJ[9]) / 2;

      if(N5 > 1)        LBggb5 = (LikelihoodBgg[12] - LikelihoodBgg[11]) / 2;
      else if(N5 > 0)   LBggb5 = (LikelihoodBgg[11] - LikelihoodBgg[0]) / 1;
      else if(N5 > 1)   LBggb5 = (LikelihoodBgg[0] - LikelihoodBgg[10]) / 1;
      else              LBggb5 = (LikelihoodBgg[10] - LikelihoodBgg[9]) / 2;

      // double SignalLikelihood = LSa + LSb1 * N1 + LSb2 * N2 + LSb3 * N3 + LSb4 * N4 + LSb5 * N5;
      // double BackgroundLikelihood = LBa + LBb1 * N1 + LBb2 * N2 + LBb3 * N3 + LBb4 * N4 + LBb5 * N5;
      // double BackgroundZJLikelihood = LZJa + LZJb1 * N1 + LZJb2 * N2 + LZJb3 * N3 + LZJb4 * N4 + LZJb5 * N5;
      // double BackgroundggLikelihood = LBgga + LBggb1 * N1 + LBggb2 * N2 + LBggb3 * N3 + LBggb4 * N4 + LBggb5 * N5;

      double SignalLikelihood = LSa + LSb1 * N1;
      double BackgroundLikelihood = LBa + LBb1 * N1;
      double BackgroundZJLikelihood = LZJa + LZJb1 * N1;
      double BackgroundggLikelihood = LBgga + LBggb1 * N1;

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

      double FZJ = 0;
      if(S[iS] == "em")   FZJ = FZJem;
      if(S[iS] == "me")   FZJ = FZJme;
      if(S[iS] == "ee")   FZJ = FZJee;
      if(S[iS] == "mm")   FZJ = FZJmm;
      
      double Fgg = 0;
      if(S[iS] == "em")   Fgg = FggZZem;
      if(S[iS] == "me")   Fgg = FggZZme;
      if(S[iS] == "ee")   Fgg = FggZZee;
      if(S[iS] == "mm")   Fgg = FggZZmm;
      
      // double LTotal = SignalLikelihood * (1 - F - FZJ - Fgg) + BackgroundLikelihood * F
      //    + BackgroundZJLikelihood * FZJ + BackgroundggLikelihood * Fgg;
      double LTotal = SignalLikelihood * (1 - F) + BackgroundLikelihood * F;
      // double LTotal = SignalLikelihood;
      LogTotal = LogTotal + log(LTotal)
         - N1 * N1 / 2 / (0.1 * 0.1)
         - N2 * N2 / 2 - N3 * N3 / 2 - N4 * N4 / 2 - N5 * N5 / 2 - N6 * N6 / 2 - N7 * N7 / 2;
   }

   return -LogTotal * 2;
}

void FitClass::AddPoint(SingleEvent &event)
{
   AddPoint(event.v, event.i, event.v2, event.i2, event.event, event.state);
}

void FitClass::AddPoint(double v[92][13], double i[92][13], double v2[2][13], double i2[2][13],
   EventParameters &Event, string State)
{
   for(int j1 = 0; j1 < 92; j1++)
   {
      for(int j2 = 0; j2 < 13; j2++)
      {
         V[j1][j2].push_back(v[j1][j2]);
         I[j1][j2].push_back(i[j1][j2]);
      }
   }
   
   for(int j1 = 0; j1 < 2; j1++)
   {
      for(int j2 = 0; j2 < 13; j2++)
      {
         V2[j1][j2].push_back(v2[j1][j2]);
         I2[j1][j2].push_back(i2[j1][j2]);
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
      for(int i2 = 0; i2 < 13; i2++)
      {
         V[i1][i2].clear();
         I[i1][i2].clear();
      }
   }

   for(int i1 = 0; i1 < 2; i1++)
   {
      for(int i2 = 0; i2 < 13; i2++)
      {
         V2[i1][i2].clear();
         I2[i1][i2].clear();
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

   Worker->SetPrintLevel(-2);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   Worker->SetTolerance(1e-10);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 31);
   Worker->SetFunction(Function);

   double StepSize[31] = {0};
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
   StepSize[16] = (configuration.FloatFZJem == true) ? 0.1 : 0;
   StepSize[17] = (configuration.FloatFZJme == true) ? 0.1 : 0;
   StepSize[18] = (configuration.FloatFZJee == true) ? 0.1 : 0;
   StepSize[19] = (configuration.FloatFZJmm == true) ? 0.1 : 0;
   StepSize[20] = (configuration.FloatFggZZem == true) ? 0.1 : 0;
   StepSize[21] = (configuration.FloatFggZZme == true) ? 0.1 : 0;
   StepSize[22] = (configuration.FloatFggZZee == true) ? 0.1 : 0;
   StepSize[23] = (configuration.FloatFggZZmm == true) ? 0.1 : 0;
   StepSize[24] = (configuration.FloatN1 == true) ? 0.1 : 0;
   StepSize[25] = (configuration.FloatN2 == true) ? 0.1 : 0;
   StepSize[26] = (configuration.FloatN3 == true) ? 0.1 : 0;
   StepSize[27] = (configuration.FloatN4 == true) ? 0.1 : 0;
   StepSize[28] = (configuration.FloatN5 == true) ? 0.1 : 0;
   StepSize[29] = (configuration.FloatN6 == true) ? 0.1 : 0;
   StepSize[30] = (configuration.FloatN7 == true) ? 0.1 : 0;

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
   Worker->SetLimitedVariable(16, "FZJem",     configuration.FZJemInitialValue, StepSize[16], 0, 1);
   Worker->SetLimitedVariable(17, "FZJme",     configuration.FZJmeInitialValue, StepSize[17], 0, 1);
   Worker->SetLimitedVariable(18, "FZJee",     configuration.FZJeeInitialValue, StepSize[18], 0, 1);
   Worker->SetLimitedVariable(19, "FZJmm",     configuration.FZJmmInitialValue, StepSize[19], 0, 1);
   Worker->SetLimitedVariable(20, "FggZZem",   configuration.FggZZemInitialValue, StepSize[20], 0, 1);
   Worker->SetLimitedVariable(21, "FggZZme",   configuration.FggZZmeInitialValue, StepSize[21], 0, 1);
   Worker->SetLimitedVariable(22, "FggZZee",   configuration.FggZZeeInitialValue, StepSize[22], 0, 1);
   Worker->SetLimitedVariable(23, "FggZZmm",   configuration.FggZZmmInitialValue, StepSize[23], 0, 1);
   Worker->SetLimitedVariable(24, "N1",        configuration.N1InitialValue, StepSize[24], -5, 5);
   Worker->SetLimitedVariable(25, "N2",        configuration.N2InitialValue, StepSize[25], -5, 5);
   Worker->SetLimitedVariable(26, "N3",        configuration.N3InitialValue, StepSize[26], -5, 5);
   Worker->SetLimitedVariable(27, "N4",        configuration.N4InitialValue, StepSize[27], -5, 5);
   Worker->SetLimitedVariable(28, "N5",        configuration.N5InitialValue, StepSize[28], -5, 5);
   Worker->SetLimitedVariable(29, "N6",        configuration.N6InitialValue, StepSize[29], -5, 5);
   Worker->SetLimitedVariable(30, "N7",        configuration.N7InitialValue, StepSize[30], -5, 5);
   
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();

   double EventCount[4] = {0};
   EventCount[0] = SignalStateCount[0] + BackgroundStateCount[0];
   EventCount[1] = SignalStateCount[1] + BackgroundStateCount[1];
   EventCount[2] = SignalStateCount[2] + BackgroundStateCount[2];
   EventCount[3] = SignalStateCount[3] + BackgroundStateCount[3];

   double TrueParameters[18] = {0};
   TrueParameters[0] = configuration.A2ZZA1ZZInitialValue;
   TrueParameters[1] = configuration.A2ZZPhaseInitialValue;
   TrueParameters[2] = configuration.A3ZZA1ZZInitialValue;
   TrueParameters[3] = configuration.A3ZZPhaseInitialValue;
   TrueParameters[4] = configuration.A2ZAA1ZZInitialValue;
   TrueParameters[5] = configuration.A2ZAPhaseInitialValue;
   TrueParameters[6] = configuration.A3ZAA1ZZInitialValue;
   TrueParameters[7] = configuration.A3ZAPhaseInitialValue;
   TrueParameters[8] = configuration.A2AAA1ZZInitialValue;
   TrueParameters[9] = configuration.A2AAPhaseInitialValue;
   TrueParameters[10] = configuration.A3AAA1ZZInitialValue;
   TrueParameters[11] = configuration.A3AAPhaseInitialValue;
   TrueParameters[12] = ((EventCount[0] > 0) ? (BackgroundStateCount[0] / EventCount[0]) : 0);
   TrueParameters[13] = ((EventCount[1] > 0) ? (BackgroundStateCount[1] / EventCount[1]) : 0);
   TrueParameters[14] = ((EventCount[2] > 0) ? (BackgroundStateCount[2] / EventCount[2]) : 0);
   TrueParameters[15] = ((EventCount[3] > 0) ? (BackgroundStateCount[3] / EventCount[3]) : 0);
   TrueParameters[16] = 0;
   TrueParameters[17] = 0;

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
   Result.FZJem = Parameters[16];
   Result.FZJemError = Errors[16];
   Result.FZJme = Parameters[17];
   Result.FZJmeError = Errors[17];
   Result.FZJee = Parameters[18];
   Result.FZJeeError = Errors[18];
   Result.FZJmm = Parameters[19];
   Result.FZJmmError = Errors[19];
   Result.FggZZem = Parameters[20];
   Result.FggZZemError = Errors[20];
   Result.FggZZme = Parameters[21];
   Result.FggZZmeError = Errors[21];
   Result.FggZZee = Parameters[22];
   Result.FggZZeeError = Errors[22];
   Result.FggZZmm = Parameters[23];
   Result.FggZZmmError = Errors[23];
   Result.N1 = Parameters[24];
   Result.N1Error = Errors[24];
   Result.N2 = Parameters[25];
   Result.N2Error = Errors[25];
   Result.N3 = Parameters[26];
   Result.N3Error = Errors[26];
   Result.N4 = Parameters[27];
   Result.N4Error = Errors[27];
   Result.N5 = Parameters[28];
   Result.N5Error = Errors[28];
   Result.N6 = Parameters[29];
   Result.N6Error = Errors[29];
   Result.N7 = Parameters[30];
   Result.N7Error = Errors[30];
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
   cout << "FitClass::PlotResult: Not implemented!" << endl;
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




