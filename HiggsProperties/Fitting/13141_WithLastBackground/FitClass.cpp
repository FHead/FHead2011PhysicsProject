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
   SetFloatCounts("YYYY");
   SetFloatFractions("NNNN");
   SetFloatNs("NN");

   SetInitialRatios(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialCounts(ListToVector(4, 1, 1, 1, 1));
   SetInitialFractions(ListToVector(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialNs(ListToVector(5, 0, 0, 0, 0, 0));

   SetNSConstrain(ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNBConstrain(ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNZJConstrain(ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNggZZConstrain(ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
}

FitConfiguration::FitConfiguration(string FloatAs, string FloatPhases,
   string FloatCounts, string FloatFractions, string FloatNs)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatCounts(FloatCounts);
   SetFloatFractions(FloatFractions);
   SetFloatNs(FloatNs);

   SetInitialRatios(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialCounts(ListToVector(4, 1, 1, 1, 1));
   SetInitialFractions(ListToVector(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialNs(ListToVector(5, 0, 0, 0, 0, 0));

   SetNSConstrain(ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNBConstrain(ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNZJConstrain(ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNggZZConstrain(ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
}
   
FitConfiguration::FitConfiguration(string FloatAs, string FloatPhases,
   string FloatCounts, string FloatFractions, string FloatNs,
   vector<double> Ratios, vector<double> Phases, vector<double> Counts,
   vector<double> Fractions, vector<double> Ns,
   vector<double> NS, vector<double> NSSigma, vector<double> NB, vector<double> NBSigma,
   vector<double> NZJ, vector<double> NZJSigma, vector<double> NggZZ, vector<double> NggZZSigma)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatCounts(FloatCounts);
   SetFloatFractions(FloatFractions);
   SetFloatNs(FloatNs);

   SetInitialRatios(Ratios);
   SetInitialPhases(Phases);
   SetInitialCounts(Counts);
   SetInitialFractions(Fractions);
   SetInitialNs(Ns);

   SetNSConstrain(NS, NSSigma);
   SetNBConstrain(NB, NBSigma);
   SetNZJConstrain(NZJ, NZJSigma);
   SetNggZZConstrain(NggZZ, NggZZSigma);
}

FitConfiguration::~FitConfiguration()
{
}

void FitConfiguration::SetFloats(string FloatAs, string FloatPhases,
   string FloatCounts, string FloatFractions, string FloatNs)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatCounts(FloatCounts);
   SetFloatFractions(FloatFractions);
   SetFloatNs(FloatNs);
}

void FitConfiguration::SetFloatAs(string FloatAs)
{
   for(int i = 0; i < 6; i++)
   {
      FloatAA[i] = false;
      if(FloatAs.size() > i && FloatAs[i] == 'Y')
         FloatAA[i] = true;
   }
}

void FitConfiguration::SetFloatPhases(string FloatPhases)
{
   for(int i = 0; i < 6; i++)
   {
      FloatPhase[i] = false;
      if(FloatPhases.size() > i && FloatPhases[i] == 'Y')
         FloatPhase[i] = true;
   }
}

void FitConfiguration::SetFloatCounts(string FloatCounts)
{
   for(int i = 0; i < 4; i++)
   {
      FloatCount[i] = false;
      if(FloatCounts.size() > i && FloatCounts[i] == 'Y')
         FloatCount[i] = true;
   }
}

void FitConfiguration::SetFloatFractions(string FloatFractions)
{
   for(int i = 0; i < 4; i++)
   {
      FloatF[i] = false;
      if(FloatFractions.size() > i + 0 && FloatFractions[i+0] == 'Y')
         FloatF[i] = true;
   }
   for(int i = 0; i < 4; i++)
   {
      FloatFZJ[i] = false;
      if(FloatFractions.size() > i + 4 && FloatFractions[i+4] == 'Y')
         FloatFZJ[i] = true;
   }
   for(int i = 0; i < 4; i++)
   {
      FloatFggZZ[i] = false;
      if(FloatFractions.size() > i + 8 && FloatFractions[i+8] == 'Y')
         FloatFggZZ[i] = true;
   }
}

void FitConfiguration::SetFloatNs(string FloatNs)
{
   for(int i = 0; i < 7; i++)
   {
      FloatN[i] = false;
      if(FloatNs.size() > i && FloatNs[i] == 'Y')
         FloatN[i] = true;
   }
}
   
void FitConfiguration::SetInitialRatios(const vector<double> Ratios)
{
   for(int i = 0; i < 6; i++)
      if(Ratios.size() > i)
         AAInitialValue[i] = Ratios[i];
}

void FitConfiguration::SetInitialPhases(const vector<double> Phases)
{
   for(int i = 0; i < 6; i++)
      if(Phases.size() > i)
         PhaseInitialValue[i] = Phases[i];
}

void FitConfiguration::SetInitialCounts(const vector<double> Counts)
{
   for(int i = 0; i < 6; i++)
      if(Counts.size() > i)
         CountInitialValue[i] = Counts[i];
}

void FitConfiguration::SetInitialFractions(const vector<double> Fractions)
{
   for(int i = 0; i < 4; i++)
   {
      FInitialValue[i] = 0;
      if(Fractions.size() > i + 0)
         FInitialValue[i] = Fractions[i+0];
   }
   for(int i = 0; i < 4; i++)
   {
      FZJInitialValue[i] = 0;
      if(Fractions.size() > i + 4)
         FZJInitialValue[i] = Fractions[i+4];
   }
   for(int i = 0; i < 4; i++)
   {
      FggZZInitialValue[i] = 0;
      if(Fractions.size() > i + 8)
         FggZZInitialValue[i] = Fractions[i+8];
   }
}

void FitConfiguration::SetInitialNs(const vector<double> Ns)
{
   for(int i = 0; i < 7; i++)
   {
      NInitialValue[i] = 0;
      if(Ns.size() > i)
         NInitialValue[i] = Ns[i];
   }
}
   
void FitConfiguration::SetNSConstrain(const vector<double> NS, const vector<double> NSSigma)
{
   for(int i = 0; i < 4; i++)
   {
      NSConstrain[i] = 0;
      if(NS.size() > i)
         NSConstrain[i] = NS[i];
   }
   for(int i = 0; i < 4; i++)
   {
      NSConstrainSigma[i] = 0;
      if(NSSigma.size() > i)
         NSConstrainSigma[i] = NSSigma[i];
   }
}

void FitConfiguration::SetNBConstrain(const vector<double> NB, const vector<double> NBSigma)
{
   for(int i = 0; i < 4; i++)
   {
      NBConstrain[i] = 0;
      if(NB.size() > i)
         NBConstrain[i] = NB[i];
   }
   for(int i = 0; i < 4; i++)
   {
      NBConstrainSigma[i] = 0;
      if(NBSigma.size() > i)
         NBConstrainSigma[i] = NBSigma[i];
   }
}

void FitConfiguration::SetNZJConstrain(const vector<double> NZJ, const vector<double> NZJSigma)
{
   for(int i = 0; i < 4; i++)
   {
      NZJConstrain[i] = 0;
      if(NZJ.size() > i)
         NZJConstrain[i] = NZJ[i];
   }
   for(int i = 0; i < 4; i++)
   {
      NZJConstrainSigma[i] = 0;
      if(NZJSigma.size() > i)
         NZJConstrainSigma[i] = NZJSigma[i];
   }
}

void FitConfiguration::SetNggZZConstrain(const vector<double> NggZZ, const vector<double> NggZZSigma)
{
   for(int i = 0; i < 4; i++)
   {
      NggZZConstrain[i] = 0;
      if(NggZZ.size() > i)
         NggZZConstrain[i] = NggZZ[i];
   }
   for(int i = 0; i < 4; i++)
   {
      NggZZConstrainSigma[i] = 0;
      if(NggZZSigma.size() > i)
         NggZZConstrainSigma[i] = NggZZSigma[i];
   }
}

int FitConfiguration::TotalNumberOfFloats()
{
   int Count = 0;
   
   for(int i = 0; i < 6; i++)   if(FloatAA[i] == true)      Count = Count + 1;
   for(int i = 0; i < 6; i++)   if(FloatPhase[i] == true)   Count = Count + 1;
   for(int i = 0; i < 4; i++)   if(FloatF[i] == true)       Count = Count + 1;
   for(int i = 0; i < 4; i++)   if(FloatFZJ[i] == true)     Count = Count + 1;
   for(int i = 0; i < 4; i++)   if(FloatFggZZ[i] == true)   Count = Count + 1;
   for(int i = 0; i < 7; i++)   if(FloatN[i] == true)       Count = Count + 1;

   return Count;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1ZZR     = 1;
   double A2ZZR     = Parameters[0] * cos(Parameters[1]);
   double A2ZZI     = Parameters[0] * sin(Parameters[1]);
   double A3ZZR     = Parameters[2] * cos(Parameters[3]);
   double A3ZZI     = Parameters[2] * sin(Parameters[3]);
   double A2ZAR     = Parameters[4] * cos(Parameters[5]);
   double A2ZAI     = Parameters[4] * sin(Parameters[5]);
   double A3ZAR     = Parameters[6] * cos(Parameters[7]);
   double A3ZAI     = Parameters[6] * sin(Parameters[7]);
   double A2AAR     = Parameters[8] * cos(Parameters[9]);
   double A2AAI     = Parameters[8] * sin(Parameters[9]);
   double A3AAR     = Parameters[10] * cos(Parameters[11]);
   double A3AAI     = Parameters[10] * sin(Parameters[11]);
   double Counts[4] = {Parameters[12], Parameters[13], Parameters[14], Parameters[15]};
   double F[4]      = {Parameters[16], Parameters[17], Parameters[18], Parameters[19]};
   double FZJ[4]    = {Parameters[20], Parameters[21], Parameters[22], Parameters[23]};
   double FggZZ[4]  = {Parameters[24], Parameters[25], Parameters[26], Parameters[27]};
   double N[7]      = {Parameters[28], Parameters[29], Parameters[30], Parameters[31],
                       Parameters[32], Parameters[33], Parameters[34]};

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
         continue;
         LogTotal = LogTotal - 99999;
         continue;
      }

      double LSa = Likelihood[0];
      double LSb1 = (N[0] > 0) ? (Likelihood[1] - Likelihood[0]) : (Likelihood[0] - Likelihood[2]);
      double LSb2 = (N[1] > 0) ? (Likelihood[3] - Likelihood[0]) : (Likelihood[0] - Likelihood[4]);
      double LSb3 = (N[2] > 0) ? (Likelihood[5] - Likelihood[0]) : (Likelihood[0] - Likelihood[6]);
      double LSb4 = (N[3] > 0) ? (Likelihood[7] - Likelihood[0]) : (Likelihood[0] - Likelihood[8]);
      double LSb5 = 0;
      double LBa = LikelihoodB[0];
      double LBb1 = (N[0] > 0) ? (LikelihoodB[1] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[2]);
      double LBb2 = (N[1] > 0) ? (LikelihoodB[3] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[4]);
      double LBb3 = (N[2] > 0) ? (LikelihoodB[5] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[5]);
      double LBb4 = (N[3] > 0) ? (LikelihoodB[7] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[7]);
      double LBb5 = 0;
      double LZJa = LikelihoodZJ[0];
      double LZJb1 = (N[0] > 0) ? (LikelihoodZJ[1] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[2]);
      double LZJb2 = (N[1] > 0) ? (LikelihoodZJ[3] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[4]);
      double LZJb3 = (N[2] > 0) ? (LikelihoodZJ[5] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[5]);
      double LZJb4 = (N[3] > 0) ? (LikelihoodZJ[7] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[7]);
      double LZJb5 = 0;
      double LBgga = LikelihoodBgg[0];
      double LBggb1 = (N[0] > 0) ? (LikelihoodBgg[1] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[2]);
      double LBggb2 = (N[1] > 0) ? (LikelihoodBgg[3] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[4]);
      double LBggb3 = (N[2] > 0) ? (LikelihoodBgg[5] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[5]);
      double LBggb4 = (N[3] > 0) ? (LikelihoodBgg[7] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[7]);
      double LBggb5 = 0;

      LSb5 = Likelihood[11] - Likelihood[0];

      double LZJb6 = LikelihoodB[0] - LikelihoodZJ[0];

      // double SignalLikelihood = LSa + LSb1 * N1 + LSb2 * N2 + LSb3 * N3 + LSb4 * N4 + LSb5 * N5;
      // double BackgroundLikelihood = LBa + LBb1 * N1 + LBb2 * N2 + LBb3 * N3 + LBb4 * N4 + LBb5 * N5;
      // double BackgroundZJLikelihood = LZJa + LZJb1 * N1 + LZJb2 * N2 + LZJb3 * N3 + LZJb4 * N4 + LZJb5 * N5;
      // double BackgroundggLikelihood = LBgga + LBggb1 * N1 + LBggb2 * N2 + LBggb3 * N3 + LBggb4 * N4 + LBggb5 * N5;

      double SignalLikelihood = LSa;
      double BackgroundLikelihood = LBa;
      double BackgroundZJLikelihood = LZJa + LZJb6 * N[5];
      double BackgroundggLikelihood = LBgga;

      if(SignalLikelihood <= 0 || BackgroundLikelihood <= 0
         || BackgroundZJLikelihood <= 0 || BackgroundggLikelihood <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      int StateIndex = -1;
      if(S[iS] == "em")   StateIndex = 0;
      if(S[iS] == "me")   StateIndex = 1;
      if(S[iS] == "ee")   StateIndex = 2;
      if(S[iS] == "mm")   StateIndex = 3;
      if(StateIndex < 0)
      {
         LogTotal = LogTotal - 99999;
         cerr << "WTF State Index Not Valid.  S[iS] = \"" << S[iS] << "\"" << endl;
         continue;
      }

      double LTotal = SignalLikelihood * (1 - F[StateIndex] - FZJ[StateIndex] - FggZZ[StateIndex])
         + BackgroundLikelihood * F[StateIndex]
         + BackgroundZJLikelihood * FZJ[StateIndex]
         + BackgroundggLikelihood * FggZZ[StateIndex];
      // double LTotal = SignalLikelihood * (1 - F[StateIndex]) + BackgroundLikelihood * F[StateIndex];
      // double LTotal = SignalLikelihood;

      if(LTotal <= 0 || F[StateIndex] + FZJ[StateIndex] + FggZZ[StateIndex] >= 1)
         LogTotal = LogTotal - 99999;
      else
         LogTotal = LogTotal + log(LTotal);
   }

   // Apply log normals
   for(int i = 0; i < 4; i++)
   {
      double NS = Counts[i] * (1 - F[i] - FZJ[i] - FggZZ[i]);
      double Mu = NSConstrainMu[i];
      double Sigma = NSConstrainSigma[i];
      if(Mu == Mu && Sigma > 0 && NS > 0)
         LogTotal = LogTotal - (log(NS) - Mu) * (log(NS) - Mu) / (2 * Sigma * Sigma) - log(NS) - log(Sigma);

      double NB = Counts[i] * F[i];
      Mu = NBConstrainMu[i];
      Sigma = NBConstrainSigma[i];
      if(Mu == Mu && Sigma > 0 && NB > 0)
         LogTotal = LogTotal - (log(NB) - Mu) * (log(NB) - Mu) / (2 * Sigma * Sigma) - log(NB) - log(Sigma);

      double NZJ = Counts[i] * FZJ[i];
      Mu = NZJConstrainMu[i];
      Sigma = NZJConstrainSigma[i];
      if(Mu == Mu && Sigma > 0 && NZJ > 0)
         LogTotal = LogTotal - (log(NZJ) - Mu) * (log(NZJ) - Mu) / (2 * Sigma * Sigma) - log(NZJ) - log(Sigma);

      double NggZZ = Counts[i] * FggZZ[i];
      Mu = NggZZConstrainMu[i];
      Sigma = NggZZConstrainSigma[i];
      if(Mu == Mu && Sigma > 0 && NggZZ > 0)
         LogTotal = LogTotal - (log(NggZZ) - Mu) * (log(NggZZ) - Mu) / (2 * Sigma * Sigma) - log(NggZZ) - log(Sigma);

      if(EventCount[i] > 0)
         LogTotal = LogTotal + EventCount[i] * log(Counts[i]) - Counts[i];
   }

   // Penalty terms for systematic errors
   double Factor[7] = {0.01, 1, 1, 1, 1, 1, 1};
   for(int i = 0; i < 7; i++)
      LogTotal = LogTotal - N[i] * N[i] / 2 / Factor[i];

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

   for(int i = 0; i < 4; i++)
   {
      SignalStateCount[i] = 0;
      BackgroundStateCount[i] = 0;
      ZJStateCount[i] = 0;
      ggZZStateCount[i] = 0;

      NSConstrainMu[i] = 0;
      NSConstrainSigma[i] = 0;
      NBConstrainMu[i] = 0;
      NBConstrainSigma[i] = 0;
      NZJConstrainMu[i] = 0;
      NZJConstrainSigma[i] = 0;
      NggZZConstrainMu[i] = 0;
      NggZZConstrainSigma[i] = 0;
   }

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

   for(int i = 0; i < 4; i++)
      NSConstrainMu[i] = GetLogNormalMu(configuration.NSConstrain[i], configuration.NSConstrainSigma[i]);
   for(int i = 0; i < 4; i++)
      NBConstrainMu[i] = GetLogNormalMu(configuration.NBConstrain[i], configuration.NBConstrainSigma[i]);
   for(int i = 0; i < 4; i++)
      NZJConstrainMu[i] = GetLogNormalMu(configuration.NZJConstrain[i], configuration.NZJConstrainSigma[i]);
   for(int i = 0; i < 4; i++)
      NggZZConstrainMu[i] = GetLogNormalMu(configuration.NggZZConstrain[i], configuration.NggZZConstrainSigma[i]);
   for(int i = 0; i < 4; i++)
      NSConstrainSigma[i] = GetLogNormalSigma(configuration.NSConstrain[i], configuration.NSConstrainSigma[i]);
   for(int i = 0; i < 4; i++)
      NBConstrainSigma[i] = GetLogNormalSigma(configuration.NBConstrain[i], configuration.NBConstrainSigma[i]);
   for(int i = 0; i < 4; i++)
      NZJConstrainSigma[i] = GetLogNormalSigma(configuration.NZJConstrain[i], configuration.NZJConstrainSigma[i]);
   for(int i = 0; i < 4; i++)
      NggZZConstrainSigma[i] = GetLogNormalSigma(configuration.NggZZConstrain[i], configuration.NggZZConstrainSigma[i]);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 35);
   Worker->SetFunction(Function);

   EventCount[0] = SignalStateCount[0] + BackgroundStateCount[0] + ZJStateCount[0] + ggZZStateCount[0];
   EventCount[1] = SignalStateCount[1] + BackgroundStateCount[1] + ZJStateCount[1] + ggZZStateCount[1];
   EventCount[2] = SignalStateCount[2] + BackgroundStateCount[2] + ZJStateCount[2] + ggZZStateCount[2];
   EventCount[3] = SignalStateCount[3] + BackgroundStateCount[3] + ZJStateCount[3] + ggZZStateCount[3];

   configuration.FInitialValue[0] = BackgroundStateCount[0] / EventCount[0];
   configuration.FInitialValue[1] = BackgroundStateCount[1] / EventCount[1];
   configuration.FInitialValue[2] = BackgroundStateCount[2] / EventCount[2];
   configuration.FInitialValue[3] = BackgroundStateCount[3] / EventCount[3];
   configuration.FZJInitialValue[0] = ZJStateCount[0] / EventCount[0];
   configuration.FZJInitialValue[1] = ZJStateCount[1] / EventCount[1];
   configuration.FZJInitialValue[2] = ZJStateCount[2] / EventCount[2];
   configuration.FZJInitialValue[3] = ZJStateCount[3] / EventCount[3];
   configuration.FggZZInitialValue[0] = ggZZStateCount[0] / EventCount[0];
   configuration.FggZZInitialValue[1] = ggZZStateCount[1] / EventCount[1];
   configuration.FggZZInitialValue[2] = ggZZStateCount[2] / EventCount[2];
   configuration.FggZZInitialValue[3] = ggZZStateCount[3] / EventCount[3];
  
   double StepSize[35] = {0};
   StepSize[0] = (configuration.FloatAA[0] == true) ? 0.1 : 0;
   StepSize[1] = (configuration.FloatPhase[0] == true) ? 0.1 : 0;
   StepSize[2] = (configuration.FloatAA[1] == true) ? 0.1 : 0;
   StepSize[3] = (configuration.FloatPhase[1] == true) ? 0.1 : 0;
   StepSize[4] = (configuration.FloatAA[2] == true) ? 0.1 : 0;
   StepSize[5] = (configuration.FloatPhase[2] == true) ? 0.1 : 0;
   StepSize[6] = (configuration.FloatAA[3] == true) ? 0.1 : 0;
   StepSize[7] = (configuration.FloatPhase[3] == true) ? 0.1 : 0;
   StepSize[8] = (configuration.FloatAA[4] == true) ? 0.1 : 0;
   StepSize[9] = (configuration.FloatPhase[4] == true) ? 0.1 : 0;
   StepSize[10] = (configuration.FloatAA[5] == true) ? 0.1 : 0;
   StepSize[11] = (configuration.FloatPhase[5] == true) ? 0.1 : 0;
   StepSize[12] = (configuration.FloatCount[0] == true) ? 1 : 0;
   StepSize[13] = (configuration.FloatCount[1] == true) ? 1 : 0;
   StepSize[14] = (configuration.FloatCount[2] == true) ? 1 : 0;
   StepSize[15] = (configuration.FloatCount[3] == true) ? 1 : 0;
   StepSize[16] = (configuration.FloatF[0] == true) ? 0.1 : 0;
   StepSize[17] = (configuration.FloatF[1] == true) ? 0.1 : 0;
   StepSize[18] = (configuration.FloatF[2] == true) ? 0.1 : 0;
   StepSize[19] = (configuration.FloatF[3] == true) ? 0.1 : 0;
   StepSize[20] = (configuration.FloatFZJ[0] == true) ? 0.05 : 0;
   StepSize[21] = (configuration.FloatFZJ[1] == true) ? 0.10 : 0;
   StepSize[22] = (configuration.FloatFZJ[2] == true) ? 0.10 : 0;
   StepSize[23] = (configuration.FloatFZJ[3] == true) ? 0.05 : 0;
   StepSize[24] = (configuration.FloatFggZZ[0] == true) ? 0.1 : 0;
   StepSize[25] = (configuration.FloatFggZZ[1] == true) ? 0.1 : 0;
   StepSize[26] = (configuration.FloatFggZZ[2] == true) ? 0.1 : 0;
   StepSize[27] = (configuration.FloatFggZZ[3] == true) ? 0.1 : 0;
   StepSize[28] = (configuration.FloatN[0] == true) ? 0.1 : 0;   // up-down
   StepSize[29] = (configuration.FloatN[1] == true) ? 0.1 : 0;   // wide-narrow
   StepSize[30] = (configuration.FloatN[2] == true) ? 0.1 : 0;   // spectrum
   StepSize[31] = (configuration.FloatN[3] == true) ? 0.1 : 0;   // spectrum
   StepSize[32] = (configuration.FloatN[4] == true) ? 0.1 : 0;   // mass
   StepSize[33] = (configuration.FloatN[5] == true) ? 0.1 : 0;   // ZX
   StepSize[34] = (configuration.FloatN[6] == true) ? 0.1 : 0;

   Worker->SetLimitedVariable(0, "A2ZZA1ZZ",   configuration.AAInitialValue[0], StepSize[0], -1000, 1000);
   Worker->SetLimitedVariable(1, "A2ZZPhase",  configuration.PhaseInitialValue[0], StepSize[1], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(2, "A3ZZA1ZZ",   configuration.AAInitialValue[1], StepSize[2], -1000, 1000);
   Worker->SetLimitedVariable(3, "A3ZZPhase",  configuration.PhaseInitialValue[1], StepSize[3], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(4, "A2ZAA1ZZ",   configuration.AAInitialValue[2], StepSize[4], -1000, 1000);
   Worker->SetLimitedVariable(5, "A2ZAPhase",  configuration.PhaseInitialValue[2], StepSize[5], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(6, "A3ZAA1ZZ",   configuration.AAInitialValue[3], StepSize[6], -1000, 1000);
   Worker->SetLimitedVariable(7, "A3ZAPhase",  configuration.PhaseInitialValue[3], StepSize[7], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(8, "A2AAA1ZZ",   configuration.AAInitialValue[4], StepSize[8], -1000, 1000);
   Worker->SetLimitedVariable(9, "A2AAPhase",  configuration.PhaseInitialValue[4], StepSize[9], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(10, "A3AAA1ZZ",  configuration.AAInitialValue[5], StepSize[10], -1000, 1000);
   Worker->SetLimitedVariable(11, "A3AAPhase", configuration.PhaseInitialValue[5], StepSize[11], -PI * 10, PI * 10);
   Worker->SetLimitedVariable(12, "Nem",       configuration.CountInitialValue[0], StepSize[12], 0, 10000);
   Worker->SetLimitedVariable(13, "Nme",       configuration.CountInitialValue[1], StepSize[13], 0, 10000);
   Worker->SetLimitedVariable(14, "Nee",       configuration.CountInitialValue[2], StepSize[14], 0, 10000);
   Worker->SetLimitedVariable(15, "Nmm",       configuration.CountInitialValue[3], StepSize[15], 0, 10000);
   Worker->SetLimitedVariable(16, "Fem",       configuration.FInitialValue[0], StepSize[16], 0, 1);
   Worker->SetLimitedVariable(17, "Fme",       configuration.FInitialValue[1], StepSize[17], 0, 1);
   Worker->SetLimitedVariable(18, "Fee",       configuration.FInitialValue[2], StepSize[18], 0, 1);
   Worker->SetLimitedVariable(19, "Fmm",       configuration.FInitialValue[3], StepSize[19], 0, 1);
   Worker->SetLimitedVariable(20, "FZJem",     configuration.FZJInitialValue[0], StepSize[20], 0, 1);
   Worker->SetLimitedVariable(21, "FZJme",     configuration.FZJInitialValue[1], StepSize[21], 0, 1);
   Worker->SetLimitedVariable(22, "FZJee",     configuration.FZJInitialValue[2], StepSize[22], 0, 1);
   Worker->SetLimitedVariable(23, "FZJmm",     configuration.FZJInitialValue[3], StepSize[23], 0, 1);
   Worker->SetLimitedVariable(24, "FggZZem",   configuration.FggZZInitialValue[0], StepSize[24], 0, 1);
   Worker->SetLimitedVariable(25, "FggZZme",   configuration.FggZZInitialValue[1], StepSize[25], 0, 1);
   Worker->SetLimitedVariable(26, "FggZZee",   configuration.FggZZInitialValue[2], StepSize[26], 0, 1);
   Worker->SetLimitedVariable(27, "FggZZmm",   configuration.FggZZInitialValue[3], StepSize[27], 0, 1);
   Worker->SetLimitedVariable(28, "N1",        configuration.NInitialValue[0], StepSize[28], -5, 5);
   Worker->SetLimitedVariable(29, "N2",        configuration.NInitialValue[1], StepSize[29], -5, 5);
   Worker->SetLimitedVariable(30, "N3",        configuration.NInitialValue[2], StepSize[30], -5, 5);
   Worker->SetLimitedVariable(31, "N4",        configuration.NInitialValue[3], StepSize[31], -5, 5);
   Worker->SetLimitedVariable(32, "N5",        configuration.NInitialValue[4], StepSize[32], -5, 5);
   Worker->SetLimitedVariable(33, "N6",        configuration.NInitialValue[5], StepSize[33], -5, 5);
   Worker->SetLimitedVariable(34, "N7",        configuration.NInitialValue[6], StepSize[34], -5, 5);
   
   for(int i = 0; i < 5; i++)
      Worker->Minimize();

   double TrueParameters[31] = {0};
   TrueParameters[0] = configuration.AAInitialValue[0];
   TrueParameters[1] = configuration.PhaseInitialValue[0];
   TrueParameters[2] = configuration.AAInitialValue[1];
   TrueParameters[3] = configuration.PhaseInitialValue[1];
   TrueParameters[4] = configuration.AAInitialValue[2];
   TrueParameters[5] = configuration.PhaseInitialValue[2];
   TrueParameters[6] = configuration.AAInitialValue[3];
   TrueParameters[7] = configuration.PhaseInitialValue[3];
   TrueParameters[8] = configuration.AAInitialValue[4];
   TrueParameters[9] = configuration.PhaseInitialValue[4];
   TrueParameters[10] = configuration.AAInitialValue[5];
   TrueParameters[11] = configuration.PhaseInitialValue[5];
   TrueParameters[12] = EventCount[0];
   TrueParameters[13] = EventCount[1];
   TrueParameters[14] = EventCount[2];
   TrueParameters[15] = EventCount[3];
   TrueParameters[16] = ((EventCount[0] > 0) ? (BackgroundStateCount[0] / EventCount[0]) : 0);
   TrueParameters[17] = ((EventCount[1] > 0) ? (BackgroundStateCount[1] / EventCount[1]) : 0);
   TrueParameters[18] = ((EventCount[2] > 0) ? (BackgroundStateCount[2] / EventCount[2]) : 0);
   TrueParameters[19] = ((EventCount[3] > 0) ? (BackgroundStateCount[3] / EventCount[3]) : 0);
   TrueParameters[20] = ((EventCount[0] > 0) ? (ZJStateCount[0] / EventCount[0]) : 0);
   TrueParameters[21] = ((EventCount[1] > 0) ? (ZJStateCount[1] / EventCount[1]) : 0);
   TrueParameters[22] = ((EventCount[2] > 0) ? (ZJStateCount[2] / EventCount[2]) : 0);
   TrueParameters[23] = ((EventCount[3] > 0) ? (ZJStateCount[3] / EventCount[3]) : 0);
   TrueParameters[24] = ((EventCount[0] > 0) ? (ggZZStateCount[0] / EventCount[0]) : 0);
   TrueParameters[25] = ((EventCount[1] > 0) ? (ggZZStateCount[1] / EventCount[1]) : 0);
   TrueParameters[26] = ((EventCount[2] > 0) ? (ggZZStateCount[2] / EventCount[2]) : 0);
   TrueParameters[27] = ((EventCount[3] > 0) ? (ggZZStateCount[3] / EventCount[3]) : 0);
   for(int i = 28; i < 35; i++)
      TrueParameters[i] = 0;

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.AA[0] = Parameters[0];       Result.AAError[0] = Errors[0];
   Result.Phase[0] = Parameters[1];    Result.PhaseError[0] = Errors[1];
   Result.AA[1] = Parameters[2];       Result.AAError[1] = Errors[2];
   Result.Phase[1] = Parameters[3];    Result.PhaseError[1] = Errors[3];
   Result.AA[2] = Parameters[4];       Result.AAError[2] = Errors[4];
   Result.Phase[2] = Parameters[5];    Result.PhaseError[2] = Errors[5];
   Result.AA[3] = Parameters[6];       Result.AAError[3] = Errors[6];
   Result.Phase[3] = Parameters[7];    Result.PhaseError[3] = Errors[7];
   Result.AA[4] = Parameters[8];       Result.AAError[4] = Errors[8];
   Result.Phase[4] = Parameters[9];    Result.PhaseError[4] = Errors[9];
   Result.AA[5] = Parameters[10];      Result.AAError[5] = Errors[10];
   Result.Phase[5] = Parameters[11];   Result.PhaseError[5] = Errors[11];
   Result.Count[0] = Parameters[12];   Result.CountError[0] = Errors[12];
   Result.Count[1] = Parameters[13];   Result.CountError[1] = Errors[13];
   Result.Count[2] = Parameters[14];   Result.CountError[2] = Errors[14];
   Result.Count[3] = Parameters[15];   Result.CountError[3] = Errors[15];
   Result.F[0] = Parameters[16];       Result.FError[0] = Errors[16];
   Result.F[1] = Parameters[17];       Result.FError[1] = Errors[17];
   Result.F[2] = Parameters[18];       Result.FError[2] = Errors[18];
   Result.F[3] = Parameters[19];       Result.FError[3] = Errors[19];
   Result.FZJ[0] = Parameters[20];     Result.FZJError[0] = Errors[20];
   Result.FZJ[1] = Parameters[21];     Result.FZJError[1] = Errors[21];
   Result.FZJ[2] = Parameters[22];     Result.FZJError[2] = Errors[22];
   Result.FZJ[3] = Parameters[23];     Result.FZJError[3] = Errors[23];
   Result.FggZZ[0] = Parameters[24];   Result.FggZZError[0] = Errors[24];
   Result.FggZZ[1] = Parameters[25];   Result.FggZZError[1] = Errors[25];
   Result.FggZZ[2] = Parameters[26];   Result.FggZZError[2] = Errors[26];
   Result.FggZZ[3] = Parameters[27];   Result.FggZZError[3] = Errors[27];
   Result.N[0] = Parameters[28];       Result.NError[0] = Errors[28];
   Result.N[1] = Parameters[29];       Result.NError[1] = Errors[29];
   Result.N[2] = Parameters[30];       Result.NError[2] = Errors[30];
   Result.N[3] = Parameters[31];       Result.NError[3] = Errors[31];
   Result.N[4] = Parameters[32];       Result.NError[4] = Errors[32];
   Result.N[5] = Parameters[33];       Result.NError[5] = Errors[33];
   Result.N[6] = Parameters[34];       Result.NError[6] = Errors[34];
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   Result.S[0] = SignalStateCount[0];
   Result.S[1] = SignalStateCount[1];
   Result.S[2] = SignalStateCount[2];
   Result.S[3] = SignalStateCount[3];

   Result.B[0] = BackgroundStateCount[0];
   Result.B[1] = BackgroundStateCount[1];
   Result.B[2] = BackgroundStateCount[2];
   Result.B[3] = BackgroundStateCount[3];

   Result.ZJ[0] = ZJStateCount[0];
   Result.ZJ[1] = ZJStateCount[1];
   Result.ZJ[2] = ZJStateCount[2];
   Result.ZJ[3] = ZJStateCount[3];

   Result.ggZZ[0] = ggZZStateCount[0];
   Result.ggZZ[1] = ggZZStateCount[1];
   Result.ggZZ[2] = ggZZStateCount[2];
   Result.ggZZ[3] = ggZZStateCount[3];

   Result.TruthNLL = CalculateLogLikelihoodAll(TrueParameters);
   Result.BestNLL = CalculateLogLikelihoodAll(Parameters);

   delete Worker;

   return Result;
}

void FitClass::PlotResult(PsFileHelper *PsFile, FitResultSummary Result)
{
   cout << "FitClass::PlotResult: Not implemented!" << endl;
}
   
double FitClass::GetLogNormalMu(double Mean, double RelativeError)
{
   double Sigma2 = log(1 + RelativeError * RelativeError);
   return log(Mean) - Sigma2 / 2;
}
   
double FitClass::GetLogNormalSigma(double Mean, double RelativeError)
{
   double Sigma2 = log(1 + RelativeError * RelativeError);
   return sqrt(Sigma2);
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




