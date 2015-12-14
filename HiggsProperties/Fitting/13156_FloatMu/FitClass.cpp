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

#include "YieldFraction.h"
#include "FitClass.h"

#define PI 3.14159265358979323846264338327950288479716939937510

FitConfiguration::FitConfiguration()
{
   SetFloatAs("YYNNNN");
   SetFloatPhases("NNNNNN");
   SetFloatCounts(0, "YYYY");
   SetFloatCounts(1, "YYYY");
   SetFloatFractions(0, "NNNN");
   SetFloatFractions(1, "NNNN");
   SetFloatNs("NNNNNNN");
   SetFloatMu("N");

   SetInitialRatios(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialCounts(0, ListToVector(4, 1, 1, 1, 1));
   SetInitialCounts(1, ListToVector(4, 1, 1, 1, 1));
   SetInitialFractions(0, ListToVector(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(1, ListToVector(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialNs(ListToVector(5, 0, 0, 0, 0, 0));
   SetInitialMu(1);

   SetNSConstrain(0, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNSConstrain(1, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNBConstrain(0, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNBConstrain(1, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNZJConstrain(0, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNZJConstrain(1, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNggZZConstrain(0, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNggZZConstrain(1, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
}

FitConfiguration::FitConfiguration(string FloatAs, string FloatPhases,
   string FloatCounts7TeV, string FloatCounts8TeV,
   string FloatFractions7TeV, string FloatFractions8TeV, string FloatNs, string FloatRate)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatCounts(1, FloatCounts7TeV);
   SetFloatCounts(0, FloatCounts8TeV);
   SetFloatFractions(1, FloatFractions7TeV);
   SetFloatFractions(0, FloatFractions8TeV);
   SetFloatNs(FloatNs);
   SetFloatMu(FloatRate);

   SetInitialRatios(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(6, 0, 0, 0, 0, 0, 0));
   SetInitialCounts(1, ListToVector(4, 1, 1, 1, 1));
   SetInitialCounts(0, ListToVector(4, 1, 1, 1, 1));
   SetInitialFractions(1, ListToVector(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(0, ListToVector(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialNs(ListToVector(5, 0, 0, 0, 0, 0));
   SetInitialMu(1);

   SetNSConstrain(1, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNSConstrain(0, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNBConstrain(1, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNBConstrain(0, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNZJConstrain(1, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNZJConstrain(0, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNggZZConstrain(1, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
   SetNggZZConstrain(0, ListToVector(4, 0, 0, 0, 0), ListToVector(4, 0, 0, 0, 0));
}
   
FitConfiguration::FitConfiguration(string FloatAs, string FloatPhases,
   string FloatCounts7TeV, string FloatCounts8TeV,
   string FloatFractions7TeV, string FloatFractions8TeV, string FloatNs, string FloatRate,
   vector<double> Ratios,         vector<double> Phases,
   vector<double> Counts7TeV,     vector<double> Counts8TeV,
   vector<double> Fractions7TeV,  vector<double> Fractions8TeV,
   vector<double> Ns,
   vector<double> NS7TeV,         vector<double> NS8TeV,
   vector<double> NSSigma7TeV,    vector<double> NSSigma8TeV,
   vector<double> NB7TeV,         vector<double> NB8TeV,
   vector<double> NBSigma7TeV,    vector<double> NBSigma8TeV,
   vector<double> NZJ7TeV,        vector<double> NZJ8TeV,
   vector<double> NZJSigma7TeV,   vector<double> NZJSigma8TeV,
   vector<double> NggZZ7TeV,      vector<double> NggZZ8TeV,
   vector<double> NggZZSigma7TeV, vector<double> NggZZSigma8TeV,
   double Mu)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatCounts(1, FloatCounts7TeV);
   SetFloatCounts(0, FloatCounts8TeV);
   SetFloatFractions(1, FloatFractions7TeV);
   SetFloatFractions(0, FloatFractions8TeV);
   SetFloatNs(FloatNs);
   SetFloatMu(FloatRate);

   SetInitialRatios(Ratios);
   SetInitialPhases(Phases);
   SetInitialCounts(1, Counts7TeV);
   SetInitialCounts(0, Counts8TeV);
   SetInitialFractions(1, Fractions7TeV);
   SetInitialFractions(0, Fractions8TeV);
   SetInitialNs(Ns);
   SetInitialMu(Mu);

   SetNSConstrain(1, NS7TeV, NSSigma7TeV);
   SetNSConstrain(0, NS8TeV, NSSigma8TeV);
   SetNBConstrain(1, NB7TeV, NBSigma7TeV);
   SetNBConstrain(0, NB8TeV, NBSigma8TeV);
   SetNZJConstrain(1, NZJ7TeV, NZJSigma7TeV);
   SetNZJConstrain(0, NZJ8TeV, NZJSigma8TeV);
   SetNggZZConstrain(1, NggZZ7TeV, NggZZSigma7TeV);
   SetNggZZConstrain(0, NggZZ8TeV, NggZZSigma8TeV);
}

FitConfiguration::~FitConfiguration()
{
}

void FitConfiguration::SetFloats(string FloatAs, string FloatPhases,
   string FloatCounts7TeV, string FloatCounts8TeV,
   string FloatFractions7TeV, string FloatFractions8TeV, string FloatNs, string FloatRate)
{
   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatCounts(1, FloatCounts7TeV);
   SetFloatCounts(0, FloatCounts8TeV);
   SetFloatFractions(1, FloatFractions7TeV);
   SetFloatFractions(0, FloatFractions8TeV);
   SetFloatNs(FloatNs);
   SetFloatMu(FloatRate);
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

void FitConfiguration::SetFloatCounts(bool Is7TeV, string FloatCounts)
{
   for(int i = 0; i < 4; i++)
   {
      FloatCount[Is7TeV][i] = false;
      if(FloatCounts.size() > i && FloatCounts[i] == 'Y')
         FloatCount[Is7TeV][i] = true;
   }
}

void FitConfiguration::SetFloatFractions(bool Is7TeV, string FloatFractions)
{
   for(int i = 0; i < 4; i++)
   {
      FloatF[Is7TeV][i] = false;
      if(FloatFractions.size() > i + 0 && FloatFractions[i+0] == 'Y')
         FloatF[Is7TeV][i] = true;
   }
   for(int i = 0; i < 4; i++)
   {
      FloatFZJ[Is7TeV][i] = false;
      if(FloatFractions.size() > i + 4 && FloatFractions[i+4] == 'Y')
         FloatFZJ[Is7TeV][i] = true;
   }
   for(int i = 0; i < 4; i++)
   {
      FloatFggZZ[Is7TeV][i] = false;
      if(FloatFractions.size() > i + 8 && FloatFractions[i+8] == 'Y')
         FloatFggZZ[Is7TeV][i] = true;
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

void FitConfiguration::SetFloatMu(string FloatRate)
{
   if(FloatRate.size() > 0 && FloatRate[0] == 'Y')
      FloatMu = true;
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

void FitConfiguration::SetInitialCounts(bool Is7TeV, const vector<double> Counts)
{
   for(int i = 0; i < 6; i++)
      if(Counts.size() > i)
         CountInitialValue[Is7TeV][i] = Counts[i];
}

void FitConfiguration::SetInitialFractions(bool Is7TeV, const vector<double> Fractions)
{
   for(int i = 0; i < 4; i++)
   {
      FInitialValue[Is7TeV][i] = 0;
      if(Fractions.size() > i + 0)
         FInitialValue[Is7TeV][i] = Fractions[i+0];
   }
   for(int i = 0; i < 4; i++)
   {
      FZJInitialValue[Is7TeV][i] = 0;
      if(Fractions.size() > i + 4)
         FZJInitialValue[Is7TeV][i] = Fractions[i+4];
   }
   for(int i = 0; i < 4; i++)
   {
      FggZZInitialValue[Is7TeV][i] = 0;
      if(Fractions.size() > i + 8)
         FggZZInitialValue[Is7TeV][i] = Fractions[i+8];
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
   
void FitConfiguration::SetInitialMu(const double Mu)
{
   MuInitialValue = Mu;
}
   
void FitConfiguration::SetNSConstrain(bool Is7TeV, const vector<double> NS, const vector<double> NSSigma)
{
   for(int i = 0; i < 4; i++)
   {
      NSConstrain[Is7TeV][i] = 0;
      if(NS.size() > i)
         NSConstrain[Is7TeV][i] = NS[i];
   }
   for(int i = 0; i < 4; i++)
   {
      NSConstrainSigma[Is7TeV][i] = 0;
      if(NSSigma.size() > i)
         NSConstrainSigma[Is7TeV][i] = NSSigma[i];
   }
}

void FitConfiguration::SetNBConstrain(bool Is7TeV, const vector<double> NB, const vector<double> NBSigma)
{
   for(int i = 0; i < 4; i++)
   {
      NBConstrain[Is7TeV][i] = 0;
      if(NB.size() > i)
         NBConstrain[Is7TeV][i] = NB[i];
   }
   for(int i = 0; i < 4; i++)
   {
      NBConstrainSigma[Is7TeV][i] = 0;
      if(NBSigma.size() > i)
         NBConstrainSigma[Is7TeV][i] = NBSigma[i];
   }
}

void FitConfiguration::SetNZJConstrain(bool Is7TeV, const vector<double> NZJ, const vector<double> NZJSigma)
{
   for(int i = 0; i < 4; i++)
   {
      NZJConstrain[Is7TeV][i] = 0;
      if(NZJ.size() > i)
         NZJConstrain[Is7TeV][i] = NZJ[i];
   }
   for(int i = 0; i < 4; i++)
   {
      NZJConstrainSigma[Is7TeV][i] = 0;
      if(NZJSigma.size() > i)
         NZJConstrainSigma[Is7TeV][i] = NZJSigma[i];
   }
}

void FitConfiguration::SetNggZZConstrain(bool Is7TeV, const vector<double> NggZZ, const vector<double> NggZZSigma)
{
   for(int i = 0; i < 4; i++)
   {
      NggZZConstrain[Is7TeV][i] = 0;
      if(NggZZ.size() > i)
         NggZZConstrain[Is7TeV][i] = NggZZ[i];
   }
   for(int i = 0; i < 4; i++)
   {
      NggZZConstrainSigma[Is7TeV][i] = 0;
      if(NggZZSigma.size() > i)
         NggZZConstrainSigma[Is7TeV][i] = NggZZSigma[i];
   }
}

int FitConfiguration::TotalNumberOfFloats()
{
   int Count = 0;
   
   for(int i = 0; i < 6; i++)   if(FloatAA[i] == true)         Count = Count + 1;
   for(int i = 0; i < 6; i++)   if(FloatPhase[i] == true)      Count = Count + 1;
   for(int i = 0; i < 4; i++)   if(FloatF[0][i] == true)       Count = Count + 1;
   for(int i = 0; i < 4; i++)   if(FloatF[1][i] == true)       Count = Count + 1;
   for(int i = 0; i < 4; i++)   if(FloatFZJ[0][i] == true)     Count = Count + 1;
   for(int i = 0; i < 4; i++)   if(FloatFZJ[1][i] == true)     Count = Count + 1;
   for(int i = 0; i < 4; i++)   if(FloatFggZZ[0][i] == true)   Count = Count + 1;
   for(int i = 0; i < 4; i++)   if(FloatFggZZ[1][i] == true)   Count = Count + 1;
   for(int i = 0; i < 7; i++)   if(FloatN[i] == true)          Count = Count + 1;

   if(FloatMu == true)
      Count = Count + 1;

   return Count;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1ZZR        = 1;
   double A2ZZR        = Parameters[0] * cos(Parameters[1]);
   double A2ZZI        = Parameters[0] * sin(Parameters[1]);
   double A3ZZR        = Parameters[2] * cos(Parameters[3]);
   double A3ZZI        = Parameters[2] * sin(Parameters[3]);
   double A2ZAR        = Parameters[4] * cos(Parameters[5]);
   double A2ZAI        = Parameters[4] * sin(Parameters[5]);
   double A3ZAR        = Parameters[6] * cos(Parameters[7]);
   double A3ZAI        = Parameters[6] * sin(Parameters[7]);
   double A2AAR        = Parameters[8] * cos(Parameters[9]);
   double A2AAI        = Parameters[8] * sin(Parameters[9]);
   double A3AAR        = Parameters[10] * cos(Parameters[11]);
   double A3AAI        = Parameters[10] * sin(Parameters[11]);
   double Counts[2][4] = {{Parameters[12], Parameters[13], Parameters[14], Parameters[15]},
                          {Parameters[16], Parameters[17], Parameters[18], Parameters[19]}};
   double F[2][4]      = {{Parameters[20], Parameters[21], Parameters[22], Parameters[23]},
                          {Parameters[24], Parameters[25], Parameters[26], Parameters[27]}};
   double FZJ[2][4]    = {{Parameters[28], Parameters[29], Parameters[30], Parameters[31]},
                          {Parameters[32], Parameters[33], Parameters[34], Parameters[35]}};
   double FggZZ[2][4]  = {{Parameters[36], Parameters[37], Parameters[38], Parameters[39]},
                          {Parameters[40], Parameters[41], Parameters[42], Parameters[43]}};
   double N[7]         = {Parameters[44], Parameters[45], Parameters[46], Parameters[47],
                          Parameters[48], Parameters[49], Parameters[50]};
   double SigmaMu      = Parameters[51];

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
      
      double LBa = LikelihoodB[0];
      double LBb1 = (N[0] > 0) ? (LikelihoodB[1] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[2]);
      double LBb2 = (N[1] > 0) ? (LikelihoodB[3] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[4]);
      double LBb3 = (N[2] > 0) ? (LikelihoodB[5] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[5]);
      double LBb4 = (N[3] > 0) ? (LikelihoodB[7] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[7]);
      
      double LZJa = LikelihoodZJ[0];
      double LZJb1 = (N[0] > 0) ? (LikelihoodZJ[1] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[2]);
      double LZJb2 = (N[1] > 0) ? (LikelihoodZJ[3] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[4]);
      double LZJb3 = (N[2] > 0) ? (LikelihoodZJ[5] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[5]);
      double LZJb4 = (N[3] > 0) ? (LikelihoodZJ[7] - LikelihoodZJ[0]) : (LikelihoodZJ[0] - LikelihoodZJ[7]);
      
      double LBgga = LikelihoodBgg[0];
      double LBggb1 = (N[0] > 0) ? (LikelihoodBgg[1] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[2]);
      double LBggb2 = (N[1] > 0) ? (LikelihoodBgg[3] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[4]);
      double LBggb3 = (N[2] > 0) ? (LikelihoodBgg[5] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[5]);
      double LBggb4 = (N[3] > 0) ? (LikelihoodBgg[7] - LikelihoodBgg[0]) : (LikelihoodBgg[0] - LikelihoodBgg[7]);

      double LZJb6 = LikelihoodB[0] - LikelihoodZJ[0];

      // double SignalLikelihood       = LSa   + LSb1   * N1 + LSb2   * N2 + LSb3   * N3 + LSb4   * N4 + LSb5   * N5;
      // double BackgroundLikelihood   = LBa   + LBb1   * N1 + LBb2   * N2 + LBb3   * N3 + LBb4   * N4 + LBb5   * N5;
      // double BackgroundZJLikelihood = LZJa  + LZJb1  * N1 + LZJb2  * N2 + LZJb3  * N3 + LZJb4  * N4 + LZJb5  * N5;
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

      int Is7TeV = -1;
      if(Energy[iS] == "7TeV")   Is7TeV = 1;
      if(Energy[iS] == "8TeV")   Is7TeV = 0;
      if(Is7TeV < 0)
      {
         LogTotal = LogTotal - 99999;
         cerr << "WTF Energy Index Not Valid.  Energy[iS] = \"" << Energy[iS] << "\"" << endl;
         continue;
      }

      double LTotal = SignalLikelihood * (1 - F[Is7TeV][StateIndex] - FZJ[Is7TeV][StateIndex] - FggZZ[Is7TeV][StateIndex])
         + BackgroundLikelihood * F[Is7TeV][StateIndex]
         + BackgroundZJLikelihood * FZJ[Is7TeV][StateIndex]
         + BackgroundggLikelihood * FggZZ[Is7TeV][StateIndex];
      // double LTotal = SignalLikelihood * (1 - F[Is7TeV][StateIndex]) + BackgroundLikelihood * F[Is7TeV][StateIndex];
      // double LTotal = SignalLikelihood;

      if(LTotal <= 0 || F[Is7TeV][StateIndex] + FZJ[Is7TeV][StateIndex] + FggZZ[Is7TeV][StateIndex] >= 1)
         LogTotal = LogTotal - 99999;
      else
         LogTotal = LogTotal + log(LTotal);
   }

   // Apply log normals and poissons
   for(int i = 0; i < 4; i++)
   {
      for(int j = 0; j < 2; j++)
      {
         double NS = Counts[j][i] * (1 - F[j][i] - FZJ[j][i] - FggZZ[j][i]);
         double Mu = NSConstrainMu[j][i];
         double Sigma = NSConstrainSigma[j][i];
         if(Mu == Mu && Sigma > 0 && NS > 0)
            LogTotal = LogTotal - (log(NS) - Mu) * (log(NS) - Mu) / (2 * Sigma * Sigma) - log(NS) - log(Sigma);

         double NB = Counts[j][i] * F[j][i];
         Mu = NBConstrainMu[j][i];
         Sigma = NBConstrainSigma[j][i];
         if(Mu == Mu && Sigma > 0 && NB > 0)
            LogTotal = LogTotal - (log(NB) - Mu) * (log(NB) - Mu) / (2 * Sigma * Sigma) - log(NB) - log(Sigma);

         double NZJ = Counts[j][i] * FZJ[j][i];
         Mu = NZJConstrainMu[j][i];
         Sigma = NZJConstrainSigma[j][i];
         if(Mu == Mu && Sigma > 0 && NZJ > 0)
            LogTotal = LogTotal - (log(NZJ) - Mu) * (log(NZJ) - Mu) / (2 * Sigma * Sigma) - log(NZJ) - log(Sigma);

         double NggZZ = Counts[j][i] * FggZZ[j][i];
         Mu = NggZZConstrainMu[j][i];
         Sigma = NggZZConstrainSigma[j][i];
         if(Mu == Mu && Sigma > 0 && NggZZ > 0)
            LogTotal = LogTotal - (log(NggZZ) - Mu) * (log(NggZZ) - Mu) / (2 * Sigma * Sigma) - log(NggZZ) - log(Sigma);

         if(EventCount[j][i] > 0)
         {
            double R = GetNormalizationYieldFraction(A1ZZR, A2ZZR, A2ZZI, A3ZZR, A3ZZI, j, i);
            double PoissonMean = Counts[j][i] * SigmaMu * R;
            LogTotal = LogTotal + EventCount[j][i] * log(PoissonMean) - PoissonMean;
         }
      }
   }

   // Penalty terms for systematic errors
   double Factor[7] = {0.01, 1, 1, 1, 1, 1, 1};
   for(int i = 0; i < 7; i++)
      LogTotal = LogTotal - N[i] * N[i] / 2 / Factor[i];

   return -LogTotal * 2;
}

void FitClass::AddPoint(SingleEvent &event)
{
   AddPoint(event.v, event.i, event.v2, event.i2, event.event, event.state, event.energy);
}

void FitClass::AddPoint(double v[92][13], double i[92][13], double v2[2][13], double i2[2][13],
   EventParameters &Event, string State, string SqrtS)
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
   Energy.push_back(SqrtS);

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
   Energy.clear();

   for(int j = 0; j < 2; j++)
   {
      for(int i = 0; i < 4; i++)
      {
         SignalStateCount[j][i] = 0;
         BackgroundStateCount[j][i] = 0;
         ZJStateCount[j][i] = 0;
         ggZZStateCount[j][i] = 0;

         NSConstrainMu[j][i] = 0;
         NSConstrainSigma[j][i] = 0;
         NBConstrainMu[j][i] = 0;
         NBConstrainSigma[j][i] = 0;
         NZJConstrainMu[j][i] = 0;
         NZJConstrainSigma[j][i] = 0;
         NggZZConstrainMu[j][i] = 0;
         NggZZConstrainSigma[j][i] = 0;
      }
   }

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit(FitConfiguration configuration)
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(1);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   Worker->SetTolerance(1e-10);

   for(int j = 0; j < 2; j++)
   {
      for(int i = 0; i < 4; i++)
         NSConstrainMu[j][i]
            = GetLogNormalMu(configuration.NSConstrain[j][i], configuration.NSConstrainSigma[j][i]);
      for(int i = 0; i < 4; i++)
         NBConstrainMu[j][i]
            = GetLogNormalMu(configuration.NBConstrain[j][i], configuration.NBConstrainSigma[j][i]);
      for(int i = 0; i < 4; i++)
         NZJConstrainMu[j][i]
            = GetLogNormalMu(configuration.NZJConstrain[j][i], configuration.NZJConstrainSigma[j][i]);
      for(int i = 0; i < 4; i++)
         NggZZConstrainMu[j][i]
            = GetLogNormalMu(configuration.NggZZConstrain[j][i], configuration.NggZZConstrainSigma[j][i]);
      for(int i = 0; i < 4; i++)
         NSConstrainSigma[j][i]
            = GetLogNormalSigma(configuration.NSConstrain[j][i], configuration.NSConstrainSigma[j][i]);
      for(int i = 0; i < 4; i++)
         NBConstrainSigma[j][i]
            = GetLogNormalSigma(configuration.NBConstrain[j][i], configuration.NBConstrainSigma[j][i]);
      for(int i = 0; i < 4; i++)
         NZJConstrainSigma[j][i]
            = GetLogNormalSigma(configuration.NZJConstrain[j][i], configuration.NZJConstrainSigma[j][i]);
      for(int i = 0; i < 4; i++)
         NggZZConstrainSigma[j][i]
            = GetLogNormalSigma(configuration.NggZZConstrain[j][i], configuration.NggZZConstrainSigma[j][i]);
   }

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 52);
   Worker->SetFunction(Function);

   EventCount[0][0] = SignalStateCount[0][0] + BackgroundStateCount[0][0] + ZJStateCount[0][0] + ggZZStateCount[0][0];
   EventCount[0][1] = SignalStateCount[0][1] + BackgroundStateCount[0][1] + ZJStateCount[0][1] + ggZZStateCount[0][1];
   EventCount[0][2] = SignalStateCount[0][2] + BackgroundStateCount[0][2] + ZJStateCount[0][2] + ggZZStateCount[0][2];
   EventCount[0][3] = SignalStateCount[0][3] + BackgroundStateCount[0][3] + ZJStateCount[0][3] + ggZZStateCount[0][3];
   EventCount[1][0] = SignalStateCount[1][0] + BackgroundStateCount[1][0] + ZJStateCount[1][0] + ggZZStateCount[1][0];
   EventCount[1][1] = SignalStateCount[1][1] + BackgroundStateCount[1][1] + ZJStateCount[1][1] + ggZZStateCount[1][1];
   EventCount[1][2] = SignalStateCount[1][2] + BackgroundStateCount[1][2] + ZJStateCount[1][2] + ggZZStateCount[1][2];
   EventCount[1][3] = SignalStateCount[1][3] + BackgroundStateCount[1][3] + ZJStateCount[1][3] + ggZZStateCount[1][3];

   configuration.FInitialValue[0][0]     = ((EventCount[0][0] > 0) ? (BackgroundStateCount[0][0] / EventCount[0][0]) : 0);
   configuration.FInitialValue[0][1]     = ((EventCount[0][1] > 0) ? (BackgroundStateCount[0][1] / EventCount[0][1]) : 0);
   configuration.FInitialValue[0][2]     = ((EventCount[0][2] > 0) ? (BackgroundStateCount[0][2] / EventCount[0][2]) : 0);
   configuration.FInitialValue[0][3]     = ((EventCount[0][3] > 0) ? (BackgroundStateCount[0][3] / EventCount[0][3]) : 0);
   configuration.FInitialValue[1][0]     = ((EventCount[1][0] > 0) ? (BackgroundStateCount[1][0] / EventCount[1][0]) : 0);
   configuration.FInitialValue[1][1]     = ((EventCount[1][1] > 0) ? (BackgroundStateCount[1][1] / EventCount[1][1]) : 0);
   configuration.FInitialValue[1][2]     = ((EventCount[1][2] > 0) ? (BackgroundStateCount[1][2] / EventCount[1][2]) : 0);
   configuration.FInitialValue[1][3]     = ((EventCount[1][3] > 0) ? (BackgroundStateCount[1][3] / EventCount[1][3]) : 0);
   configuration.FZJInitialValue[0][0]   = ((EventCount[0][0] > 0) ? (ZJStateCount[0][0] / EventCount[0][0])         : 0);
   configuration.FZJInitialValue[0][1]   = ((EventCount[0][1] > 0) ? (ZJStateCount[0][1] / EventCount[0][1])         : 0);
   configuration.FZJInitialValue[0][2]   = ((EventCount[0][2] > 0) ? (ZJStateCount[0][2] / EventCount[0][2])         : 0);
   configuration.FZJInitialValue[0][3]   = ((EventCount[0][3] > 0) ? (ZJStateCount[0][3] / EventCount[0][3])         : 0);
   configuration.FZJInitialValue[1][0]   = ((EventCount[1][0] > 0) ? (ZJStateCount[1][0] / EventCount[1][0])         : 0);
   configuration.FZJInitialValue[1][1]   = ((EventCount[1][1] > 0) ? (ZJStateCount[1][1] / EventCount[1][1])         : 0);
   configuration.FZJInitialValue[1][2]   = ((EventCount[1][2] > 0) ? (ZJStateCount[1][2] / EventCount[1][2])         : 0);
   configuration.FZJInitialValue[1][3]   = ((EventCount[1][3] > 0) ? (ZJStateCount[1][3] / EventCount[1][3])         : 0);
   configuration.FggZZInitialValue[0][0] = ((EventCount[0][0] > 0) ? (ggZZStateCount[0][0] / EventCount[0][0])       : 0);
   configuration.FggZZInitialValue[0][1] = ((EventCount[0][1] > 0) ? (ggZZStateCount[0][1] / EventCount[0][1])       : 0);
   configuration.FggZZInitialValue[0][2] = ((EventCount[0][2] > 0) ? (ggZZStateCount[0][2] / EventCount[0][2])       : 0);
   configuration.FggZZInitialValue[0][3] = ((EventCount[0][3] > 0) ? (ggZZStateCount[0][3] / EventCount[0][3])       : 0);
   configuration.FggZZInitialValue[1][0] = ((EventCount[1][0] > 0) ? (ggZZStateCount[1][0] / EventCount[1][0])       : 0);
   configuration.FggZZInitialValue[1][1] = ((EventCount[1][1] > 0) ? (ggZZStateCount[1][1] / EventCount[1][1])       : 0);
   configuration.FggZZInitialValue[1][2] = ((EventCount[1][2] > 0) ? (ggZZStateCount[1][2] / EventCount[1][2])       : 0);
   configuration.FggZZInitialValue[1][3] = ((EventCount[1][3] > 0) ? (ggZZStateCount[1][3] / EventCount[1][3])       : 0);
  
   double StepSize[52] = {0};
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
   StepSize[12] = (configuration.FloatCount[0][0] == true) ? 1 : 0;
   StepSize[13] = (configuration.FloatCount[0][1] == true) ? 1 : 0;
   StepSize[14] = (configuration.FloatCount[0][2] == true) ? 1 : 0;
   StepSize[15] = (configuration.FloatCount[0][3] == true) ? 1 : 0;
   StepSize[16] = (configuration.FloatCount[1][0] == true) ? 1 : 0;
   StepSize[17] = (configuration.FloatCount[1][1] == true) ? 1 : 0;
   StepSize[18] = (configuration.FloatCount[1][2] == true) ? 1 : 0;
   StepSize[19] = (configuration.FloatCount[1][3] == true) ? 1 : 0;
   StepSize[20] = (configuration.FloatF[0][0] == true) ? 0.1 : 0;
   StepSize[21] = (configuration.FloatF[0][1] == true) ? 0.1 : 0;
   StepSize[22] = (configuration.FloatF[0][2] == true) ? 0.1 : 0;
   StepSize[23] = (configuration.FloatF[0][3] == true) ? 0.1 : 0;
   StepSize[24] = (configuration.FloatF[1][0] == true) ? 0.1 : 0;
   StepSize[25] = (configuration.FloatF[1][1] == true) ? 0.1 : 0;
   StepSize[26] = (configuration.FloatF[1][2] == true) ? 0.1 : 0;
   StepSize[27] = (configuration.FloatF[1][3] == true) ? 0.1 : 0;
   StepSize[28] = (configuration.FloatFZJ[0][0] == true) ? 0.05 : 0;
   StepSize[29] = (configuration.FloatFZJ[0][1] == true) ? 0.10 : 0;
   StepSize[30] = (configuration.FloatFZJ[0][2] == true) ? 0.10 : 0;
   StepSize[31] = (configuration.FloatFZJ[0][3] == true) ? 0.05 : 0;
   StepSize[32] = (configuration.FloatFZJ[1][0] == true) ? 0.05 : 0;
   StepSize[33] = (configuration.FloatFZJ[1][1] == true) ? 0.10 : 0;
   StepSize[34] = (configuration.FloatFZJ[1][2] == true) ? 0.10 : 0;
   StepSize[35] = (configuration.FloatFZJ[1][3] == true) ? 0.05 : 0;
   StepSize[36] = (configuration.FloatFggZZ[0][0] == true) ? 0.1 : 0;
   StepSize[37] = (configuration.FloatFggZZ[0][1] == true) ? 0.1 : 0;
   StepSize[38] = (configuration.FloatFggZZ[0][2] == true) ? 0.1 : 0;
   StepSize[39] = (configuration.FloatFggZZ[0][3] == true) ? 0.1 : 0;
   StepSize[40] = (configuration.FloatFggZZ[1][0] == true) ? 0.1 : 0;
   StepSize[41] = (configuration.FloatFggZZ[1][1] == true) ? 0.1 : 0;
   StepSize[42] = (configuration.FloatFggZZ[1][2] == true) ? 0.1 : 0;
   StepSize[43] = (configuration.FloatFggZZ[1][3] == true) ? 0.1 : 0;
   StepSize[44] = (configuration.FloatN[0] == true) ? 0.1 : 0;   // up-down
   StepSize[45] = (configuration.FloatN[1] == true) ? 0.1 : 0;   // wide-narrow
   StepSize[46] = (configuration.FloatN[2] == true) ? 0.1 : 0;   // spectrum
   StepSize[47] = (configuration.FloatN[3] == true) ? 0.1 : 0;   // spectrum
   StepSize[48] = (configuration.FloatN[4] == true) ? 0.1 : 0;   // mass
   StepSize[49] = (configuration.FloatN[5] == true) ? 0.1 : 0;   // ZX
   StepSize[50] = (configuration.FloatN[6] == true) ? 0.1 : 0;
   StepSize[51] = (configuration.FloatMu == true) ? 0.1 : 0;   // Sigma / Sigma_SM

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
   Worker->SetLimitedVariable(12, "Nem8TeV",   configuration.CountInitialValue[0][0], StepSize[12], 0, 10000);
   Worker->SetLimitedVariable(13, "Nme8TeV",   configuration.CountInitialValue[0][1], StepSize[13], 0, 10000);
   Worker->SetLimitedVariable(14, "Nee8TeV",   configuration.CountInitialValue[0][2], StepSize[14], 0, 10000);
   Worker->SetLimitedVariable(15, "Nmm8TeV",   configuration.CountInitialValue[0][3], StepSize[15], 0, 10000);
   Worker->SetLimitedVariable(16, "Nem7TeV",   configuration.CountInitialValue[1][0], StepSize[16], 0, 10000);
   Worker->SetLimitedVariable(17, "Nme7TeV",   configuration.CountInitialValue[1][1], StepSize[17], 0, 10000);
   Worker->SetLimitedVariable(18, "Nee7TeV",   configuration.CountInitialValue[1][2], StepSize[18], 0, 10000);
   Worker->SetLimitedVariable(19, "Nmm7TeV",   configuration.CountInitialValue[1][3], StepSize[19], 0, 10000);
   Worker->SetLimitedVariable(20, "Fem8TeV",   configuration.FInitialValue[0][0], StepSize[20], 0, 1);
   Worker->SetLimitedVariable(21, "Fme8TeV",   configuration.FInitialValue[0][1], StepSize[21], 0, 1);
   Worker->SetLimitedVariable(22, "Fee8TeV",   configuration.FInitialValue[0][2], StepSize[22], 0, 1);
   Worker->SetLimitedVariable(23, "Fmm8TeV",   configuration.FInitialValue[0][3], StepSize[23], 0, 1);
   Worker->SetLimitedVariable(24, "Fem7TeV",   configuration.FInitialValue[1][0], StepSize[24], 0, 1);
   Worker->SetLimitedVariable(25, "Fme7TeV",   configuration.FInitialValue[1][1], StepSize[25], 0, 1);
   Worker->SetLimitedVariable(26, "Fee7TeV",   configuration.FInitialValue[1][2], StepSize[26], 0, 1);
   Worker->SetLimitedVariable(27, "Fmm7TeV",   configuration.FInitialValue[1][3], StepSize[27], 0, 1);
   Worker->SetLimitedVariable(28, "FZJem8TeV", configuration.FZJInitialValue[0][0], StepSize[28], 0, 1);
   Worker->SetLimitedVariable(29, "FZJme8TeV", configuration.FZJInitialValue[0][1], StepSize[29], 0, 1);
   Worker->SetLimitedVariable(30, "FZJee8TeV", configuration.FZJInitialValue[0][2], StepSize[30], 0, 1);
   Worker->SetLimitedVariable(31, "FZJmm8TeV", configuration.FZJInitialValue[0][3], StepSize[31], 0, 1);
   Worker->SetLimitedVariable(32, "FZJem7TeV", configuration.FZJInitialValue[1][0], StepSize[32], 0, 1);
   Worker->SetLimitedVariable(33, "FZJme7TeV", configuration.FZJInitialValue[1][1], StepSize[33], 0, 1);
   Worker->SetLimitedVariable(34, "FZJee7TeV", configuration.FZJInitialValue[1][2], StepSize[34], 0, 1);
   Worker->SetLimitedVariable(35, "FZJmm7TeV", configuration.FZJInitialValue[1][3], StepSize[35], 0, 1);
   Worker->SetLimitedVariable(36, "FggZZem8TeV", configuration.FggZZInitialValue[0][0], StepSize[36], 0, 1);
   Worker->SetLimitedVariable(37, "FggZZme8TeV", configuration.FggZZInitialValue[0][1], StepSize[37], 0, 1);
   Worker->SetLimitedVariable(38, "FggZZee8TeV", configuration.FggZZInitialValue[0][2], StepSize[38], 0, 1);
   Worker->SetLimitedVariable(39, "FggZZmm8TeV", configuration.FggZZInitialValue[0][3], StepSize[39], 0, 1);
   Worker->SetLimitedVariable(40, "FggZZem7TeV", configuration.FggZZInitialValue[1][0], StepSize[40], 0, 1);
   Worker->SetLimitedVariable(41, "FggZZme7TeV", configuration.FggZZInitialValue[1][1], StepSize[41], 0, 1);
   Worker->SetLimitedVariable(42, "FggZZee7TeV", configuration.FggZZInitialValue[1][2], StepSize[42], 0, 1);
   Worker->SetLimitedVariable(43, "FggZZmm7TeV", configuration.FggZZInitialValue[1][3], StepSize[43], 0, 1);
   Worker->SetLimitedVariable(44, "N1",        configuration.NInitialValue[0], StepSize[44], -5, 5);
   Worker->SetLimitedVariable(45, "N2",        configuration.NInitialValue[1], StepSize[45], -5, 5);
   Worker->SetLimitedVariable(46, "N3",        configuration.NInitialValue[2], StepSize[46], -5, 5);
   Worker->SetLimitedVariable(47, "N4",        configuration.NInitialValue[3], StepSize[47], -5, 5);
   Worker->SetLimitedVariable(48, "N5",        configuration.NInitialValue[4], StepSize[48], -5, 5);
   Worker->SetLimitedVariable(49, "N6",        configuration.NInitialValue[5], StepSize[49], -5, 5);
   Worker->SetLimitedVariable(50, "N7",        configuration.NInitialValue[6], StepSize[50], -5, 5);
   Worker->SetLimitedVariable(51, "Mu",        configuration.MuInitialValue, StepSize[51], 0, 100);
   
   for(int i = 0; i < 5; i++)
      Worker->Minimize();

   double TrueParameters[51] = {0};
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
   TrueParameters[12] = EventCount[0][0];
   TrueParameters[13] = EventCount[0][1];
   TrueParameters[14] = EventCount[0][2];
   TrueParameters[15] = EventCount[0][3];
   TrueParameters[16] = EventCount[1][0];
   TrueParameters[17] = EventCount[1][1];
   TrueParameters[18] = EventCount[1][2];
   TrueParameters[19] = EventCount[1][3];
   TrueParameters[20] = ((EventCount[0][0] > 0) ? (BackgroundStateCount[0][0] / EventCount[0][0]) : 0);
   TrueParameters[21] = ((EventCount[0][1] > 0) ? (BackgroundStateCount[0][1] / EventCount[0][1]) : 0);
   TrueParameters[22] = ((EventCount[0][2] > 0) ? (BackgroundStateCount[0][2] / EventCount[0][2]) : 0);
   TrueParameters[23] = ((EventCount[0][3] > 0) ? (BackgroundStateCount[0][3] / EventCount[0][3]) : 0);
   TrueParameters[24] = ((EventCount[1][0] > 0) ? (BackgroundStateCount[1][0] / EventCount[1][0]) : 0);
   TrueParameters[25] = ((EventCount[1][1] > 0) ? (BackgroundStateCount[1][1] / EventCount[1][1]) : 0);
   TrueParameters[26] = ((EventCount[1][2] > 0) ? (BackgroundStateCount[1][2] / EventCount[1][2]) : 0);
   TrueParameters[27] = ((EventCount[1][3] > 0) ? (BackgroundStateCount[1][3] / EventCount[1][3]) : 0);
   TrueParameters[28] = ((EventCount[0][0] > 0) ? (ZJStateCount[0][0] / EventCount[0][0]) : 0);
   TrueParameters[29] = ((EventCount[0][1] > 0) ? (ZJStateCount[0][1] / EventCount[0][1]) : 0);
   TrueParameters[30] = ((EventCount[0][2] > 0) ? (ZJStateCount[0][2] / EventCount[0][2]) : 0);
   TrueParameters[31] = ((EventCount[0][3] > 0) ? (ZJStateCount[0][3] / EventCount[0][3]) : 0);
   TrueParameters[32] = ((EventCount[1][0] > 0) ? (ZJStateCount[1][0] / EventCount[1][0]) : 0);
   TrueParameters[33] = ((EventCount[1][1] > 0) ? (ZJStateCount[1][1] / EventCount[1][1]) : 0);
   TrueParameters[34] = ((EventCount[1][2] > 0) ? (ZJStateCount[1][2] / EventCount[1][2]) : 0);
   TrueParameters[35] = ((EventCount[1][3] > 0) ? (ZJStateCount[1][3] / EventCount[1][3]) : 0);
   TrueParameters[36] = ((EventCount[0][0] > 0) ? (ggZZStateCount[0][0] / EventCount[0][0]) : 0);
   TrueParameters[37] = ((EventCount[0][1] > 0) ? (ggZZStateCount[0][1] / EventCount[0][1]) : 0);
   TrueParameters[38] = ((EventCount[0][2] > 0) ? (ggZZStateCount[0][2] / EventCount[0][2]) : 0);
   TrueParameters[39] = ((EventCount[0][3] > 0) ? (ggZZStateCount[0][3] / EventCount[0][3]) : 0);
   TrueParameters[40] = ((EventCount[1][0] > 0) ? (ggZZStateCount[1][0] / EventCount[1][0]) : 0);
   TrueParameters[41] = ((EventCount[1][1] > 0) ? (ggZZStateCount[1][1] / EventCount[1][1]) : 0);
   TrueParameters[42] = ((EventCount[1][2] > 0) ? (ggZZStateCount[1][2] / EventCount[1][2]) : 0);
   TrueParameters[43] = ((EventCount[1][3] > 0) ? (ggZZStateCount[1][3] / EventCount[1][3]) : 0);
   for(int i = 44; i < 51; i++)
      TrueParameters[i] = 0;

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.AA[0] = Parameters[0];          Result.AAError[0] = Errors[0];
   Result.Phase[0] = Parameters[1];       Result.PhaseError[0] = Errors[1];
   Result.AA[1] = Parameters[2];          Result.AAError[1] = Errors[2];
   Result.Phase[1] = Parameters[3];       Result.PhaseError[1] = Errors[3];
   Result.AA[2] = Parameters[4];          Result.AAError[2] = Errors[4];
   Result.Phase[2] = Parameters[5];       Result.PhaseError[2] = Errors[5];
   Result.AA[3] = Parameters[6];          Result.AAError[3] = Errors[6];
   Result.Phase[3] = Parameters[7];       Result.PhaseError[3] = Errors[7];
   Result.AA[4] = Parameters[8];          Result.AAError[4] = Errors[8];
   Result.Phase[4] = Parameters[9];       Result.PhaseError[4] = Errors[9];
   Result.AA[5] = Parameters[10];         Result.AAError[5] = Errors[10];
   Result.Phase[5] = Parameters[11];      Result.PhaseError[5] = Errors[11];
   Result.Count[0][0] = Parameters[12];   Result.CountError[0][0] = Errors[12];
   Result.Count[0][1] = Parameters[13];   Result.CountError[0][1] = Errors[13];
   Result.Count[0][2] = Parameters[14];   Result.CountError[0][2] = Errors[14];
   Result.Count[0][3] = Parameters[15];   Result.CountError[0][3] = Errors[15];
   Result.Count[1][0] = Parameters[16];   Result.CountError[1][0] = Errors[16];
   Result.Count[1][1] = Parameters[17];   Result.CountError[1][1] = Errors[17];
   Result.Count[1][2] = Parameters[18];   Result.CountError[1][2] = Errors[18];
   Result.Count[1][3] = Parameters[19];   Result.CountError[1][3] = Errors[19];
   Result.F[0][0] = Parameters[20];       Result.FError[0][0] = Errors[20];
   Result.F[0][1] = Parameters[21];       Result.FError[0][1] = Errors[21];
   Result.F[0][2] = Parameters[22];       Result.FError[0][2] = Errors[22];
   Result.F[0][3] = Parameters[23];       Result.FError[0][3] = Errors[23];
   Result.F[1][0] = Parameters[24];       Result.FError[1][0] = Errors[24];
   Result.F[1][1] = Parameters[25];       Result.FError[1][1] = Errors[25];
   Result.F[1][2] = Parameters[26];       Result.FError[1][2] = Errors[26];
   Result.F[1][3] = Parameters[27];       Result.FError[1][3] = Errors[27];
   Result.FZJ[0][0] = Parameters[28];     Result.FZJError[0][0] = Errors[28];
   Result.FZJ[0][1] = Parameters[29];     Result.FZJError[0][1] = Errors[29];
   Result.FZJ[0][2] = Parameters[30];     Result.FZJError[0][2] = Errors[30];
   Result.FZJ[0][3] = Parameters[31];     Result.FZJError[0][3] = Errors[31];
   Result.FZJ[1][0] = Parameters[32];     Result.FZJError[1][0] = Errors[32];
   Result.FZJ[1][1] = Parameters[33];     Result.FZJError[1][1] = Errors[33];
   Result.FZJ[1][2] = Parameters[34];     Result.FZJError[1][2] = Errors[34];
   Result.FZJ[1][3] = Parameters[35];     Result.FZJError[1][3] = Errors[35];
   Result.FggZZ[0][0] = Parameters[36];   Result.FggZZError[0][0] = Errors[36];
   Result.FggZZ[0][1] = Parameters[37];   Result.FggZZError[0][1] = Errors[37];
   Result.FggZZ[0][2] = Parameters[38];   Result.FggZZError[0][2] = Errors[38];
   Result.FggZZ[0][3] = Parameters[39];   Result.FggZZError[0][3] = Errors[39];
   Result.FggZZ[1][0] = Parameters[40];   Result.FggZZError[1][0] = Errors[40];
   Result.FggZZ[1][1] = Parameters[41];   Result.FggZZError[1][1] = Errors[41];
   Result.FggZZ[1][2] = Parameters[42];   Result.FggZZError[1][2] = Errors[42];
   Result.FggZZ[1][3] = Parameters[43];   Result.FggZZError[1][3] = Errors[43];
   Result.N[0] = Parameters[44];          Result.NError[0] = Errors[44];
   Result.N[1] = Parameters[45];          Result.NError[1] = Errors[45];
   Result.N[2] = Parameters[46];          Result.NError[2] = Errors[46];
   Result.N[3] = Parameters[47];          Result.NError[3] = Errors[47];
   Result.N[4] = Parameters[48];          Result.NError[4] = Errors[48];
   Result.N[5] = Parameters[49];          Result.NError[5] = Errors[49];
   Result.N[6] = Parameters[50];          Result.NError[6] = Errors[50];
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   Result.S[0][0] = SignalStateCount[0][0];
   Result.S[0][1] = SignalStateCount[0][1];
   Result.S[0][2] = SignalStateCount[0][2];
   Result.S[0][3] = SignalStateCount[0][3];
   Result.S[1][0] = SignalStateCount[1][0];
   Result.S[1][1] = SignalStateCount[1][1];
   Result.S[1][2] = SignalStateCount[1][2];
   Result.S[1][3] = SignalStateCount[1][3];

   Result.B[0][0] = BackgroundStateCount[0][0];
   Result.B[0][1] = BackgroundStateCount[0][1];
   Result.B[0][2] = BackgroundStateCount[0][2];
   Result.B[0][3] = BackgroundStateCount[0][3];
   Result.B[1][0] = BackgroundStateCount[1][0];
   Result.B[1][1] = BackgroundStateCount[1][1];
   Result.B[1][2] = BackgroundStateCount[1][2];
   Result.B[1][3] = BackgroundStateCount[1][3];

   Result.ZJ[0][0] = ZJStateCount[0][0];
   Result.ZJ[0][1] = ZJStateCount[0][1];
   Result.ZJ[0][2] = ZJStateCount[0][2];
   Result.ZJ[0][3] = ZJStateCount[0][3];
   Result.ZJ[1][0] = ZJStateCount[1][0];
   Result.ZJ[1][1] = ZJStateCount[1][1];
   Result.ZJ[1][2] = ZJStateCount[1][2];
   Result.ZJ[1][3] = ZJStateCount[1][3];

   Result.ggZZ[0][0] = ggZZStateCount[0][0];
   Result.ggZZ[0][1] = ggZZStateCount[0][1];
   Result.ggZZ[0][2] = ggZZStateCount[0][2];
   Result.ggZZ[0][3] = ggZZStateCount[0][3];
   Result.ggZZ[1][0] = ggZZStateCount[1][0];
   Result.ggZZ[1][1] = ggZZStateCount[1][1];
   Result.ggZZ[1][2] = ggZZStateCount[1][2];
   Result.ggZZ[1][3] = ggZZStateCount[1][3];

   Result.TruthNLL = CalculateLogLikelihoodAll(TrueParameters);
   Result.BestNLL = CalculateLogLikelihoodAll(Parameters);

   Result.Mu = Parameters[51];
   Result.MuError = Errors[51];
 
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




