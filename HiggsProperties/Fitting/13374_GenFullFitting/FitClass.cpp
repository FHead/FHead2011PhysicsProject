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
   SetFloatAs("YYNNNNNN");
   SetFloatPhases("NNNNNNNN");
   SetFloatFractions("NNNN");
   SetFloatNs("NN");

   SetInitialRatios(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
   SetInitialNs(ListToVector(2, 0, 0));
   
   I1ZZModificationFactor = 1;
}

FitConfiguration::FitConfiguration(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs,
   double i1zzmodification)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatFractions(FloatFractions);
   SetFloatNs(FloatNs);

   SetInitialRatios(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
   SetInitialNs(ListToVector(2, 0, 0));

   I1ZZModificationFactor = i1zzmodification;
}
   
FitConfiguration::FitConfiguration(string FloatAs, string FloatPhases, string FloatFractions, string FloatNs,
   vector<double> Ratios, vector<double> Phases, vector<double> Fractions, vector<double> Ns,
   double i1zzmodification)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatFractions(FloatFractions);
   SetFloatNs(FloatNs);

   SetInitialRatios(Ratios);
   SetInitialPhases(Phases);
   SetInitialFractions(Fractions);
   SetInitialNs(Ns);
   
   I1ZZModificationFactor = i1zzmodification;
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
   FloatA4ZZA1ZZ = false;
   FloatA5ZZA1ZZ = false;

   if(FloatAs.size() > 0 && FloatAs[0] == 'Y')   FloatA2ZZA1ZZ = true;
   if(FloatAs.size() > 1 && FloatAs[1] == 'Y')   FloatA3ZZA1ZZ = true;
   if(FloatAs.size() > 2 && FloatAs[2] == 'Y')   FloatA2ZAA1ZZ = true;
   if(FloatAs.size() > 3 && FloatAs[3] == 'Y')   FloatA3ZAA1ZZ = true;
   if(FloatAs.size() > 4 && FloatAs[4] == 'Y')   FloatA2AAA1ZZ = true;
   if(FloatAs.size() > 5 && FloatAs[5] == 'Y')   FloatA3AAA1ZZ = true;
   if(FloatAs.size() > 6 && FloatAs[6] == 'Y')   FloatA4ZZA1ZZ = true;
   if(FloatAs.size() > 7 && FloatAs[7] == 'Y')   FloatA5ZZA1ZZ = true;
}

void FitConfiguration::SetFloatPhases(string FloatPhases)
{
   FloatA2ZZPhase = false;
   FloatA3ZZPhase = false;
   FloatA2ZAPhase = false;
   FloatA3ZAPhase = false;
   FloatA2AAPhase = false;
   FloatA3AAPhase = false;
   FloatA4ZZPhase = false;
   FloatA5ZZPhase = false;

   if(FloatPhases.size() > 0 && FloatPhases[0] == 'Y')   FloatA2ZZPhase = true;
   if(FloatPhases.size() > 1 && FloatPhases[1] == 'Y')   FloatA3ZZPhase = true;
   if(FloatPhases.size() > 2 && FloatPhases[2] == 'Y')   FloatA2ZAPhase = true;
   if(FloatPhases.size() > 3 && FloatPhases[3] == 'Y')   FloatA3ZAPhase = true;
   if(FloatPhases.size() > 4 && FloatPhases[4] == 'Y')   FloatA2AAPhase = true;
   if(FloatPhases.size() > 5 && FloatPhases[5] == 'Y')   FloatA3AAPhase = true;
   if(FloatPhases.size() > 6 && FloatPhases[6] == 'Y')   FloatA4ZZPhase = true;
   if(FloatPhases.size() > 7 && FloatPhases[7] == 'Y')   FloatA5ZZPhase = true;
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
   if(Ratios.size() > 6)   A4ZZA1ZZInitialValue = Ratios[6];
   if(Ratios.size() > 7)   A5ZZA1ZZInitialValue = Ratios[7];
}

void FitConfiguration::SetInitialPhases(const vector<double> Phases)
{
   if(Phases.size() > 0)   A2ZZPhaseInitialValue = Phases[0];
   if(Phases.size() > 1)   A3ZZPhaseInitialValue = Phases[1];
   if(Phases.size() > 2)   A2ZAPhaseInitialValue = Phases[2];
   if(Phases.size() > 3)   A3ZAPhaseInitialValue = Phases[3];
   if(Phases.size() > 4)   A2AAPhaseInitialValue = Phases[4];
   if(Phases.size() > 5)   A3AAPhaseInitialValue = Phases[5];
   if(Phases.size() > 6)   A4ZZPhaseInitialValue = Phases[6];
   if(Phases.size() > 7)   A5ZZPhaseInitialValue = Phases[7];
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
   
void FitConfiguration::SetI1ZZModificationFactor(double Factor)
{
   I1ZZModificationFactor = Factor;
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
   if(FloatA4ZZA1ZZ == true)     Count = Count + 1;
   if(FloatA4ZZPhase == true)    Count = Count + 1;
   if(FloatA5ZZA1ZZ == true)     Count = Count + 1;
   if(FloatA5ZZPhase == true)    Count = Count + 1;
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
   double A4ZZR = Parameters[12] * cos(Parameters[13]) / 91.1876 / 91.1876;
   double A4ZZI = Parameters[12] * sin(Parameters[13]) / 91.1876 / 91.1876;
   double A5ZZR = Parameters[14] * cos(Parameters[15]);
   double A5ZZI = Parameters[14] * sin(Parameters[15]);
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
   double Fem = Parameters[16];
   double Fme = Parameters[17];
   double Fee = Parameters[18];
   double Fmm = Parameters[19];
   double N1 = Parameters[20];
   double N2 = Parameters[21];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value[5] = {0}, Integral[5] = {0}, Likelihood[5] = {0};
      double LikelihoodB[5] = {0};

      for(int i = 0; i < 1; i++)
      {
         Value[i] = A1ZZR * A1ZZR * V[1][i][iS]
            + A2ZZR * A2ZZR * V[2][i][iS]
            // + A2ZZI * A2ZZI * V[3][i][iS]
            + A3ZZR * A3ZZR * V[4][i][iS]
            // + A3ZZI * A3ZZI * V[5][i][iS]
            + A2ZAR * A2ZAR * V[6][i][iS]
            // + A2ZAI * A2ZAI * V[7][i][iS]
            + A3ZAR * A3ZAR * V[8][i][iS]
            // + A3ZAI * A3ZAI * V[9][i][iS]
            + A2AAR * A2AAR * V[10][i][iS]
            // + A2AAI * A2AAI * V[11][i][iS]
            + A3AAR * A3AAR * V[12][i][iS]
            // + A3AAI * A3AAI * V[13][i][iS]
            + A1ZZR * A2ZZR * V[14][i][iS]
            // + A1ZZR * A2ZZI * V[15][i][iS]
            + A1ZZR * A3ZZR * V[16][i][iS]
            // + A1ZZR * A3ZZI * V[17][i][iS]
            + A1ZZR * A2ZAR * V[18][i][iS]
            // + A1ZZR * A2ZAI * V[19][i][iS]
            + A1ZZR * A3ZAR * V[20][i][iS]
            // + A1ZZR * A3ZAI * V[21][i][iS]
            + A1ZZR * A2AAR * V[22][i][iS]
            // + A1ZZR * A2AAI * V[23][i][iS]
            + A1ZZR * A3AAR * V[24][i][iS]
            // + A1ZZR * A3AAI * V[25][i][iS]
            // + A2ZZR * A2ZZI * V[26][i][iS]
            + A2ZZR * A3ZZR * V[27][i][iS]
            // + A2ZZR * A3ZZI * V[28][i][iS]
            + A2ZZR * A2ZAR * V[29][i][iS]
            // + A2ZZR * A2ZAI * V[30][i][iS]
            + A2ZZR * A3ZAR * V[31][i][iS]
            // + A2ZZR * A3ZAI * V[32][i][iS]
            + A2ZZR * A2AAR * V[33][i][iS]
            // + A2ZZR * A2AAI * V[34][i][iS]
            + A2ZZR * A3AAR * V[35][i][iS]
            // + A2ZZR * A3AAI * V[36][i][iS]
            // + A2ZZI * A3ZZR * V[37][i][iS]
            // + A2ZZI * A3ZZI * V[38][i][iS]
            // + A2ZZI * A2ZAR * V[39][i][iS]
            // + A2ZZI * A2ZAI * V[40][i][iS]
            // + A2ZZI * A3ZAR * V[41][i][iS]
            // + A2ZZI * A3ZAI * V[42][i][iS]
            // + A2ZZI * A2AAR * V[43][i][iS]
            // + A2ZZI * A2AAI * V[44][i][iS]
            // + A2ZZI * A3AAR * V[45][i][iS]
            // + A2ZZI * A3AAI * V[46][i][iS]
            // + A3ZZR * A3ZZI * V[47][i][iS]
            + A3ZZR * A2ZAR * V[48][i][iS]
            // + A3ZZR * A2ZAI * V[49][i][iS]
            + A3ZZR * A3ZAR * V[50][i][iS]
            // + A3ZZR * A3ZAI * V[51][i][iS]
            + A3ZZR * A2AAR * V[52][i][iS]
            // + A3ZZR * A2AAI * V[53][i][iS]
            + A3ZZR * A3AAR * V[54][i][iS]
            // + A3ZZR * A3AAI * V[55][i][iS]
            // + A3ZZI * A2ZAR * V[56][i][iS]
            // + A3ZZI * A2ZAI * V[57][i][iS]
            // + A3ZZI * A3ZAR * V[58][i][iS]
            // + A3ZZI * A3ZAI * V[59][i][iS]
            // + A3ZZI * A2AAR * V[60][i][iS]
            // + A3ZZI * A2AAI * V[61][i][iS]
            // + A3ZZI * A3AAR * V[62][i][iS]
            // + A3ZZI * A3AAI * V[63][i][iS]
            // + A2ZAR * A2ZAI * V[64][i][iS]
            + A2ZAR * A3ZAR * V[65][i][iS]
            // + A2ZAR * A3ZAI * V[66][i][iS]
            + A2ZAR * A2AAR * V[67][i][iS]
            // + A2ZAR * A2AAI * V[68][i][iS]
            + A2ZAR * A3AAR * V[69][i][iS]
            // + A2ZAR * A3AAI * V[70][i][iS]
            // + A2ZAI * A3ZAR * V[71][i][iS]
            // + A2ZAI * A3ZAI * V[72][i][iS]
            // + A2ZAI * A2AAR * V[73][i][iS]
            // + A2ZAI * A2AAI * V[74][i][iS]
            // + A2ZAI * A3AAR * V[75][i][iS]
            // + A2ZAI * A3AAI * V[76][i][iS]
            // + A3ZAR * A3ZAI * V[77][i][iS]
            + A3ZAR * A2AAR * V[78][i][iS]
            // + A3ZAR * A2AAI * V[79][i][iS]
            + A3ZAR * A3AAR * V[80][i][iS]
            // + A3ZAR * A3AAI * V[81][i][iS]
            // + A3ZAI * A2AAR * V[82][i][iS]
            // + A3ZAI * A2AAI * V[83][i][iS]
            // + A3ZAI * A3AAR * V[84][i][iS]
            // + A3ZAI * A3AAI * V[85][i][iS]
            // + A2AAR * A2AAI * V[86][i][iS]
            + A2AAR * A3AAR * V[87][i][iS]
            // + A2AAR * A3AAI * V[88][i][iS]
            // + A2AAI * A3AAR * V[89][i][iS]
            // + A2AAI * A3AAI * V[90][i][iS]
            // + A3AAR * A3AAI * V[91][i][iS]
            + A4ZZR * A4ZZR * V[92][i][iS]
            // + A4ZZI * A4ZZI * V[93][i][iS]
            + A5ZZR * A5ZZR * V[94][i][iS]
            // + A5ZZI * A5ZZI * V[95][i][iS]
            + A1ZZR * A4ZZR * V[96][i][iS]
            + A2ZZR * A4ZZR * V[97][i][iS]
            // + A2ZZI * A4ZZR * V[98][i][iS]
            + A3ZZR * A4ZZR * V[99][i][iS]
            // + A3ZZI * A4ZZR * V[100][i][iS]
            + A2ZZR * A4ZZR * V[101][i][iS]
            // + A2ZZI * A4ZZR * V[102][i][iS]
            + A3ZZR * A4ZZR * V[103][i][iS]
            // + A3ZZI * A4ZZR * V[104][i][iS]
            + A2ZZR * A4ZZR * V[105][i][iS]
            // + A2ZZI * A4ZZR * V[106][i][iS]
            + A3ZZR * A4ZZR * V[107][i][iS]
            // + A3ZZI * A4ZZR * V[108][i][iS]
            // + A1ZZR * A4ZZI * V[109][i][iS]
            // + A2ZZR * A4ZZI * V[110][i][iS]
            // + A2ZZI * A4ZZI * V[111][i][iS]
            // + A3ZZR * A4ZZI * V[112][i][iS]
            // + A3ZZI * A4ZZI * V[113][i][iS]
            // + A2ZZR * A4ZZI * V[114][i][iS]
            // + A2ZZI * A4ZZI * V[115][i][iS]
            // + A3ZZR * A4ZZI * V[116][i][iS]
            // + A3ZZI * A4ZZI * V[117][i][iS]
            // + A2ZZR * A4ZZI * V[118][i][iS]
            // + A2ZZI * A4ZZI * V[119][i][iS]
            // + A3ZZR * A4ZZI * V[120][i][iS]
            // + A3ZZI * A4ZZI * V[121][i][iS]
            // + A4ZZR * A4ZZI * V[122][i][iS]
            + A1ZZR * A5ZZR * V[123][i][iS]
            + A2ZZR * A5ZZR * V[124][i][iS]
            // + A2ZZI * A5ZZR * V[125][i][iS]
            + A3ZZR * A5ZZR * V[126][i][iS]
            // + A3ZZI * A5ZZR * V[127][i][iS]
            + A2ZZR * A5ZZR * V[128][i][iS]
            // + A2ZZI * A5ZZR * V[129][i][iS]
            + A3ZZR * A5ZZR * V[130][i][iS]
            // + A3ZZI * A5ZZR * V[131][i][iS]
            + A2ZZR * A5ZZR * V[132][i][iS]
            // + A2ZZI * A5ZZR * V[133][i][iS]
            + A3ZZR * A5ZZR * V[134][i][iS]
            // + A3ZZI * A5ZZR * V[135][i][iS]
            + A4ZZR * A5ZZR * V[136][i][iS]
            // + A4ZZI * A5ZZR * V[137][i][iS]
            // + A1ZZR * A5ZZI * V[138][i][iS]
            // + A2ZZR * A5ZZI * V[139][i][iS]
            // + A2ZZI * A5ZZI * V[140][i][iS]
            // + A3ZZR * A5ZZI * V[141][i][iS]
            // + A3ZZI * A5ZZI * V[142][i][iS]
            // + A2ZZR * A5ZZI * V[143][i][iS]
            // + A2ZZI * A5ZZI * V[144][i][iS]
            // + A3ZZR * A5ZZI * V[145][i][iS]
            // + A3ZZI * A5ZZI * V[146][i][iS]
            // + A2ZZR * A5ZZI * V[147][i][iS]
            // + A2ZZI * A5ZZI * V[148][i][iS]
            // + A3ZZR * A5ZZI * V[149][i][iS]
            // + A3ZZI * A5ZZI * V[150][i][iS]
            // + A4ZZR * A5ZZI * V[151][i][iS]
            // + A4ZZI * A5ZZI * V[152][i][iS]
            // + A5ZZR * A5ZZI * V[153][i][iS]
            ;
         Integral[i] = A1ZZR * A1ZZR * I[1][i][iS]
            + A2ZZR * A2ZZR * I[2][i][iS]
            // + A2ZZI * A2ZZI * I[3][i][iS]
            + A3ZZR * A3ZZR * I[4][i][iS]
            // + A3ZZI * A3ZZI * I[5][i][iS]
            + A2ZAR * A2ZAR * I[6][i][iS]
            // + A2ZAI * A2ZAI * I[7][i][iS]
            + A3ZAR * A3ZAR * I[8][i][iS]
            // + A3ZAI * A3ZAI * I[9][i][iS]
            + A2AAR * A2AAR * I[10][i][iS]
            // + A2AAI * A2AAI * I[11][i][iS]
            + A3AAR * A3AAR * I[12][i][iS]
            // + A3AAI * A3AAI * I[13][i][iS]
            + A1ZZR * A2ZZR * I[14][i][iS]
            // + A1ZZR * A2ZZI * I[15][i][iS]
            + A1ZZR * A3ZZR * I[16][i][iS]
            // + A1ZZR * A3ZZI * I[17][i][iS]
            + A1ZZR * A2ZAR * I[18][i][iS]
            // + A1ZZR * A2ZAI * I[19][i][iS]
            + A1ZZR * A3ZAR * I[20][i][iS]
            // + A1ZZR * A3ZAI * I[21][i][iS]
            + A1ZZR * A2AAR * I[22][i][iS]
            // + A1ZZR * A2AAI * I[23][i][iS]
            + A1ZZR * A3AAR * I[24][i][iS]
            // + A1ZZR * A3AAI * I[25][i][iS]
            // + A2ZZR * A2ZZI * I[26][i][iS]
            + A2ZZR * A3ZZR * I[27][i][iS]
            // + A2ZZR * A3ZZI * I[28][i][iS]
            + A2ZZR * A2ZAR * I[29][i][iS]
            // + A2ZZR * A2ZAI * I[30][i][iS]
            + A2ZZR * A3ZAR * I[31][i][iS]
            // + A2ZZR * A3ZAI * I[32][i][iS]
            + A2ZZR * A2AAR * I[33][i][iS]
            // + A2ZZR * A2AAI * I[34][i][iS]
            + A2ZZR * A3AAR * I[35][i][iS]
            // + A2ZZR * A3AAI * I[36][i][iS]
            // + A2ZZI * A3ZZR * I[37][i][iS]
            // + A2ZZI * A3ZZI * I[38][i][iS]
            // + A2ZZI * A2ZAR * I[39][i][iS]
            // + A2ZZI * A2ZAI * I[40][i][iS]
            // + A2ZZI * A3ZAR * I[41][i][iS]
            // + A2ZZI * A3ZAI * I[42][i][iS]
            // + A2ZZI * A2AAR * I[43][i][iS]
            // + A2ZZI * A2AAI * I[44][i][iS]
            // + A2ZZI * A3AAR * I[45][i][iS]
            // + A2ZZI * A3AAI * I[46][i][iS]
            // + A3ZZR * A3ZZI * I[47][i][iS]
            + A3ZZR * A2ZAR * I[48][i][iS]
            // + A3ZZR * A2ZAI * I[49][i][iS]
            + A3ZZR * A3ZAR * I[50][i][iS]
            // + A3ZZR * A3ZAI * I[51][i][iS]
            + A3ZZR * A2AAR * I[52][i][iS]
            // + A3ZZR * A2AAI * I[53][i][iS]
            + A3ZZR * A3AAR * I[54][i][iS]
            // + A3ZZR * A3AAI * I[55][i][iS]
            // + A3ZZI * A2ZAR * I[56][i][iS]
            // + A3ZZI * A2ZAI * I[57][i][iS]
            // + A3ZZI * A3ZAR * I[58][i][iS]
            // + A3ZZI * A3ZAI * I[59][i][iS]
            // + A3ZZI * A2AAR * I[60][i][iS]
            // + A3ZZI * A2AAI * I[61][i][iS]
            // + A3ZZI * A3AAR * I[62][i][iS]
            // + A3ZZI * A3AAI * I[63][i][iS]
            // + A2ZAR * A2ZAI * I[64][i][iS]
            + A2ZAR * A3ZAR * I[65][i][iS]
            // + A2ZAR * A3ZAI * I[66][i][iS]
            + A2ZAR * A2AAR * I[67][i][iS]
            // + A2ZAR * A2AAI * I[68][i][iS]
            + A2ZAR * A3AAR * I[69][i][iS]
            // + A2ZAR * A3AAI * I[70][i][iS]
            // + A2ZAI * A3ZAR * I[71][i][iS]
            // + A2ZAI * A3ZAI * I[72][i][iS]
            // + A2ZAI * A2AAR * I[73][i][iS]
            // + A2ZAI * A2AAI * I[74][i][iS]
            // + A2ZAI * A3AAR * I[75][i][iS]
            // + A2ZAI * A3AAI * I[76][i][iS]
            // + A3ZAR * A3ZAI * I[77][i][iS]
            + A3ZAR * A2AAR * I[78][i][iS]
            // + A3ZAR * A2AAI * I[79][i][iS]
            + A3ZAR * A3AAR * I[80][i][iS]
            // + A3ZAR * A3AAI * I[81][i][iS]
            // + A3ZAI * A2AAR * I[82][i][iS]
            // + A3ZAI * A2AAI * I[83][i][iS]
            // + A3ZAI * A3AAR * I[84][i][iS]
            // + A3ZAI * A3AAI * I[85][i][iS]
            // + A2AAR * A2AAI * I[86][i][iS]
            + A2AAR * A3AAR * I[87][i][iS]
            // + A2AAR * A3AAI * I[88][i][iS]
            // + A2AAI * A3AAR * I[89][i][iS]
            // + A2AAI * A3AAI * I[90][i][iS]
            // + A3AAR * A3AAI * I[91][i][iS]
            + A4ZZR * A4ZZR * I[92][i][iS]
            // + A4ZZI * A4ZZI * I[93][i][iS]
            + A5ZZR * A5ZZR * I[94][i][iS]
            // + A5ZZI * A5ZZI * I[95][i][iS]
            + A1ZZR * A4ZZR * I[96][i][iS]
            + A2ZZR * A4ZZR * I[97][i][iS]
            // + A2ZZI * A4ZZR * I[98][i][iS]
            + A3ZZR * A4ZZR * I[99][i][iS]
            // + A3ZZI * A4ZZR * I[100][i][iS]
            + A2ZZR * A4ZZR * I[101][i][iS]
            // + A2ZZI * A4ZZR * I[102][i][iS]
            + A3ZZR * A4ZZR * I[103][i][iS]
            // + A3ZZI * A4ZZR * I[104][i][iS]
            + A2ZZR * A4ZZR * I[105][i][iS]
            // + A2ZZI * A4ZZR * I[106][i][iS]
            + A3ZZR * A4ZZR * I[107][i][iS]
            // + A3ZZI * A4ZZR * I[108][i][iS]
            // + A1ZZR * A4ZZI * I[109][i][iS]
            // + A2ZZR * A4ZZI * I[110][i][iS]
            // + A2ZZI * A4ZZI * I[111][i][iS]
            // + A3ZZR * A4ZZI * I[112][i][iS]
            // + A3ZZI * A4ZZI * I[113][i][iS]
            // + A2ZZR * A4ZZI * I[114][i][iS]
            // + A2ZZI * A4ZZI * I[115][i][iS]
            // + A3ZZR * A4ZZI * I[116][i][iS]
            // + A3ZZI * A4ZZI * I[117][i][iS]
            // + A2ZZR * A4ZZI * I[118][i][iS]
            // + A2ZZI * A4ZZI * I[119][i][iS]
            // + A3ZZR * A4ZZI * I[120][i][iS]
            // + A3ZZI * A4ZZI * I[121][i][iS]
            // + A4ZZR * A4ZZI * I[122][i][iS]
            + A1ZZR * A5ZZR * I[123][i][iS]
            + A2ZZR * A5ZZR * I[124][i][iS]
            // + A2ZZI * A5ZZR * I[125][i][iS]
            + A3ZZR * A5ZZR * I[126][i][iS]
            // + A3ZZI * A5ZZR * I[127][i][iS]
            + A2ZZR * A5ZZR * I[128][i][iS]
            // + A2ZZI * A5ZZR * I[129][i][iS]
            + A3ZZR * A5ZZR * I[130][i][iS]
            // + A3ZZI * A5ZZR * I[131][i][iS]
            + A2ZZR * A5ZZR * I[132][i][iS]
            // + A2ZZI * A5ZZR * I[133][i][iS]
            + A3ZZR * A5ZZR * I[134][i][iS]
            // + A3ZZI * A5ZZR * I[135][i][iS]
            + A4ZZR * A5ZZR * I[136][i][iS]
            // + A4ZZI * A5ZZR * I[137][i][iS]
            // + A1ZZR * A5ZZI * I[138][i][iS]
            // + A2ZZR * A5ZZI * I[139][i][iS]
            // + A2ZZI * A5ZZI * I[140][i][iS]
            // + A3ZZR * A5ZZI * I[141][i][iS]
            // + A3ZZI * A5ZZI * I[142][i][iS]
            // + A2ZZR * A5ZZI * I[143][i][iS]
            // + A2ZZI * A5ZZI * I[144][i][iS]
            // + A3ZZR * A5ZZI * I[145][i][iS]
            // + A3ZZI * A5ZZI * I[146][i][iS]
            // + A2ZZR * A5ZZI * I[147][i][iS]
            // + A2ZZI * A5ZZI * I[148][i][iS]
            // + A3ZZR * A5ZZI * I[149][i][iS]
            // + A3ZZI * A5ZZI * I[150][i][iS]
            // + A4ZZR * A5ZZI * I[151][i][iS]
            // + A4ZZI * A5ZZI * I[152][i][iS]
            // + A5ZZR * A5ZZI * I[153][i][iS]
            ;

         Likelihood[i] = Value[i] / Integral[i];

         LikelihoodB[i] = V[0][i][iS] / I[0][i][iS];
      }

      bool Good = true;
      for(int i = 0; i < 1; i++)
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

      // double SignalLikelihood = LSa + LSb1 * N1 + LSb2 * N2;
      // double BackgroundLikelihood = LBa + LBb1 * N1 + LBb2 * N2;

      double SignalLikelihood = LSa;
      double BackgroundLikelihood = LBa;

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

void FitClass::AddPoint(double v[154][5], double i[154][5], EventParameters &Event, string State)
{
   for(int i1 = 0; i1 < 154; i1++)
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
   for(int i1 = 0; i1 < 154; i1++)
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

   Worker->SetPrintLevel(-2);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   Worker->SetTolerance(1e-10);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 22);
   Worker->SetFunction(Function);

   double StepSize[22] = {0};
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
   StepSize[12] = (configuration.FloatA4ZZA1ZZ == true) ? 0.1 : 0;
   StepSize[13] = (configuration.FloatA4ZZPhase == true) ? 0.1 : 0;
   StepSize[14] = (configuration.FloatA5ZZA1ZZ == true) ? 0.1 : 0;
   StepSize[15] = (configuration.FloatA5ZZPhase == true) ? 0.1 : 0;
   StepSize[16] = (configuration.FloatFem == true) ? 0.1 : 0;
   StepSize[17] = (configuration.FloatFme == true) ? 0.1 : 0;
   StepSize[18] = (configuration.FloatFee == true) ? 0.1 : 0;
   StepSize[19] = (configuration.FloatFmm == true) ? 0.1 : 0;
   StepSize[20] = (configuration.FloatN1 == true) ? 0.1 : 0;
   StepSize[21] = (configuration.FloatN2 == true) ? 0.1 : 0;

   I1ZZModificationFactor = configuration.I1ZZModificationFactor;

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
   Worker->SetLimitedVariable(12, "A4ZZA1ZZ",  configuration.A4ZZA1ZZInitialValue, StepSize[12], -1000, 1000);
   Worker->SetLimitedVariable(13, "A4ZZPhase", configuration.A4ZZPhaseInitialValue, StepSize[13], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(14, "A5ZZA1ZZ",  configuration.A5ZZA1ZZInitialValue, StepSize[14], -1000, 1000);
   Worker->SetLimitedVariable(15, "A5ZZPhase", configuration.A5ZZPhaseInitialValue, StepSize[15], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(16, "Fem",       configuration.FemInitialValue, StepSize[16], 0, 1);
   Worker->SetLimitedVariable(17, "Fme",       configuration.FmeInitialValue, StepSize[17], 0, 1);
   Worker->SetLimitedVariable(18, "Fee",       configuration.FeeInitialValue, StepSize[18], 0, 1);
   Worker->SetLimitedVariable(19, "Fmm",       configuration.FmmInitialValue, StepSize[19], 0, 1);
   Worker->SetLimitedVariable(20, "N1",        configuration.N1InitialValue, StepSize[20], -5, 5);
   Worker->SetLimitedVariable(21, "N2",        configuration.N2InitialValue, StepSize[21], -5, 5);
   
   Worker->Minimize();
   Worker->Minimize();
   Worker->Minimize();
   // Worker->Minimize();
   // Worker->Minimize();

   double EventCount[4] = {0};
   EventCount[0] = SignalStateCount[0] + BackgroundStateCount[0];
   EventCount[1] = SignalStateCount[1] + BackgroundStateCount[1];
   EventCount[2] = SignalStateCount[2] + BackgroundStateCount[2];
   EventCount[3] = SignalStateCount[3] + BackgroundStateCount[3];

   double TrueParameters[22] = {0};
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
   TrueParameters[12] = configuration.A4ZZA1ZZInitialValue;
   TrueParameters[13] = configuration.A4ZZPhaseInitialValue;
   TrueParameters[14] = configuration.A5ZZA1ZZInitialValue;
   TrueParameters[15] = configuration.A5ZZPhaseInitialValue;
   TrueParameters[16] = ((EventCount[0] > 0) ? (BackgroundStateCount[0] / EventCount[0]) : 0);
   TrueParameters[17] = ((EventCount[1] > 0) ? (BackgroundStateCount[1] / EventCount[1]) : 0);
   TrueParameters[18] = ((EventCount[2] > 0) ? (BackgroundStateCount[2] / EventCount[2]) : 0);
   TrueParameters[19] = ((EventCount[3] > 0) ? (BackgroundStateCount[3] / EventCount[3]) : 0);
   TrueParameters[20] = 0;
   TrueParameters[21] = 0;

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
   Result.A4ZZA1ZZ = Parameters[12];
   Result.A4ZZA1ZZError = Errors[12];
   Result.A4ZZPhase = Parameters[13];
   Result.A4ZZPhaseError = Errors[13];
   Result.A5ZZA1ZZ = Parameters[14];
   Result.A5ZZA1ZZError = Errors[14];
   Result.A5ZZPhase = Parameters[15];
   Result.A5ZZPhaseError = Errors[15];
   Result.Fem = Parameters[16];
   Result.FemError = Errors[16];
   Result.Fme = Parameters[17];
   Result.FmeError = Errors[17];
   Result.Fee = Parameters[18];
   Result.FeeError = Errors[18];
   Result.Fmm = Parameters[19];
   Result.FmmError = Errors[19];
   Result.N1 = Parameters[20];
   Result.N1Error = Errors[20];
   Result.N2 = Parameters[21];
   Result.N2Error = Errors[21];
   Result.EDM = Worker->Edm();
   Result.I1ZZModificationFactor = I1ZZModificationFactor;
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




