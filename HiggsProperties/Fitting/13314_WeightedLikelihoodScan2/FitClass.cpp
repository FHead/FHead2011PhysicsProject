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

#include "YieldFractionFwd.h"
#include "FitClass.h"

#define PI 3.14159265358979323846264338327950288479716939937510

FitConfiguration::FitConfiguration()
{
   SetWeighted("N");

   SetFloatAs("YYNNNNNN");
   SetFloatPhases("NNNNNNNN");
   SetFloatCounts(0, "YYYY");
   SetFloatCounts(1, "YYYY");
   SetFloatFractions(0, "NNNN");
   SetFloatFractions(1, "NNNN");
   SetFloatNs("NNNNNNN");
   SetFloatMu("N");

   SetInitialRatios(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
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

   SetGuessF(true);
}

FitConfiguration::FitConfiguration(string IsWeighted, string FloatAs, string FloatPhases,
   string FloatCounts7TeV, string FloatCounts8TeV,
   string FloatFractions7TeV, string FloatFractions8TeV, string FloatNs, string FloatRate,
   bool GuessF)
{
   SetWeighted(IsWeighted);

   SetFloatAs(FloatAs);
   SetFloatPhases(FloatPhases);
   SetFloatCounts(1, FloatCounts7TeV);
   SetFloatCounts(0, FloatCounts8TeV);
   SetFloatFractions(1, FloatFractions7TeV);
   SetFloatFractions(0, FloatFractions8TeV);
   SetFloatNs(FloatNs);
   SetFloatMu(FloatRate);

   SetInitialRatios(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialPhases(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
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

   SetGuessF(GuessF);
}

FitConfiguration::FitConfiguration(string IsWeighted, string FloatAs, string FloatPhases,
   string FloatCounts7TeV, string FloatCounts8TeV,
   string FloatFractions7TeV, string FloatFractions8TeV, string FloatNs, string FloatRate, bool GuessF,
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
   SetWeighted(IsWeighted);

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

   SetGuessF(GuessF);
}

FitConfiguration::~FitConfiguration()
{
}

void FitConfiguration::SetWeighted(string DoWeight)
{
   WeightedDataset = false;
   if(DoWeight.size() > 0 && DoWeight[0] == 'Y')
      WeightedDataset = true;
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
   for(int i = 0; i < 8; i++)
   {
      FloatAA[i] = false;
      if(FloatAs.size() > i && FloatAs[i] == 'Y')
         FloatAA[i] = true;
   }
}

void FitConfiguration::SetFloatPhases(string FloatPhases)
{
   for(int i = 0; i < 8; i++)
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
   FloatMu = false;
   if(FloatRate.size() > 0 && FloatRate[0] == 'Y')
      FloatMu = true;
}

void FitConfiguration::SetInitialRatios(const vector<double> Ratios)
{
   for(int i = 0; i < 8; i++)
      if(Ratios.size() > i)
         AAInitialValue[i] = Ratios[i];
}

void FitConfiguration::SetInitialPhases(const vector<double> Phases)
{
   for(int i = 0; i < 8; i++)
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

void FitConfiguration::SetGuessF(bool GuessF)
{
   GuessInitialFValue = GuessF;
}

int FitConfiguration::TotalNumberOfFloats()
{
   int Count = 0;

   for(int i = 0; i < 8; i++)   if(FloatAA[i] == true)         Count = Count + 1;
   for(int i = 0; i < 8; i++)   if(FloatPhase[i] == true)      Count = Count + 1;
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

void FitClass::SetUsePenalty(bool Penalty)
{
   UsePenalty = Penalty;
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
   double A1L1ZZR      = Parameters[12] * cos(Parameters[13]);
   double A1L1ZZI      = Parameters[12] * sin(Parameters[13]);
   double A1LQZZR      = Parameters[14] * cos(Parameters[15]);
   double A1LQZZI      = Parameters[14] * sin(Parameters[15]);
   double Counts[2][4] = {{Parameters[16], Parameters[17], Parameters[18], Parameters[19]},
                          {Parameters[20], Parameters[21], Parameters[22], Parameters[23]}};
   double F[2][4]      = {{Parameters[24], Parameters[25], Parameters[26], Parameters[27]},
                          {Parameters[28], Parameters[29], Parameters[30], Parameters[31]}};
   double FZJ[2][4]    = {{Parameters[32], Parameters[33], Parameters[34], Parameters[35]},
                          {Parameters[36], Parameters[37], Parameters[38], Parameters[39]}};
   double FggZZ[2][4]  = {{Parameters[40], Parameters[41], Parameters[42], Parameters[43]},
                          {Parameters[44], Parameters[45], Parameters[46], Parameters[47]}};
   double N[7]         = {Parameters[48], Parameters[49], Parameters[50], Parameters[51],
                          Parameters[52], Parameters[53], Parameters[54]};
   double SigmaMu      = Parameters[55];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value[13] = {0}, Integral[13] = {0}, Likelihood[13] = {0};
      double LikelihoodB[13] = {0}, LikelihoodZJ[13] = {0}, LikelihoodBgg[13] = {0};

      for(int i = 0; i < 5; i++)
      {
         Value[i] = A1ZZR   * A1ZZR   * V[1][i][iS]
            + A2ZZR   * A2ZZR   * V[2][i][iS]
            + A2ZZI   * A2ZZI   * V[3][i][iS]
            + A3ZZR   * A3ZZR   * V[4][i][iS]
            + A3ZZI   * A3ZZI   * V[5][i][iS]
            // + A1L1ZZR * A1L1ZZR * V[6][i][iS]
            // + A1L1ZZI * A1L1ZZI * V[7][i][iS]
            + A1ZZR   * A2ZZR   * V[8][i][iS]
            + A1ZZR   * A2ZZI   * V[9][i][iS]
            + A1ZZR   * A3ZZR   * V[10][i][iS]
            + A1ZZR   * A3ZZI   * V[11][i][iS]
            // + A1ZZR   * A1L1ZZR * V[12][i][iS]
            // + A1ZZR   * A1L1ZZI * V[13][i][iS]
            + A2ZZR   * A2ZZI   * V[14][i][iS]
            + A2ZZR   * A3ZZR   * V[15][i][iS]
            + A2ZZR   * A3ZZI   * V[16][i][iS]
            // + A2ZZR   * A1L1ZZR * V[17][i][iS]
            // + A2ZZR   * A1L1ZZI * V[18][i][iS]
            + A2ZZI   * A3ZZR   * V[19][i][iS]
            + A2ZZI   * A3ZZI   * V[20][i][iS]
            // + A2ZZI   * A1L1ZZR * V[21][i][iS]
            // + A2ZZI   * A1L1ZZI * V[22][i][iS]
            + A3ZZR   * A3ZZI   * V[23][i][iS]
            // + A3ZZR   * A1L1ZZR * V[24][i][iS]
            // + A3ZZR   * A1L1ZZI * V[25][i][iS]
            // + A3ZZI   * A1L1ZZR * V[26][i][iS]
            // + A3ZZI   * A1L1ZZI * V[27][i][iS]
            // + A1L1ZZR * A1L1ZZI * V[28][i][iS];
            ;
         Integral[i] = A1ZZR   * A1ZZR   * I[1][i][iS]
            + A2ZZR   * A2ZZR   * I[2][i][iS]
            + A2ZZI   * A2ZZI   * I[3][i][iS]
            + A3ZZR   * A3ZZR   * I[4][i][iS]
            + A3ZZI   * A3ZZI   * I[5][i][iS]
            // + A1L1ZZR * A1L1ZZR * I[6][i][iS]
            // + A1L1ZZI * A1L1ZZI * I[7][i][iS]
            + A1ZZR   * A2ZZR   * I[8][i][iS]
            + A1ZZR   * A2ZZI   * I[9][i][iS]
            + A1ZZR   * A3ZZR   * I[10][i][iS]
            + A1ZZR   * A3ZZI   * I[11][i][iS]
            // + A1ZZR   * A1L1ZZR * I[12][i][iS]
            // + A1ZZR   * A1L1ZZI * I[13][i][iS]
            + A2ZZR   * A2ZZI   * I[14][i][iS]
            + A2ZZR   * A3ZZR   * I[15][i][iS]
            + A2ZZR   * A3ZZI   * I[16][i][iS]
            // + A2ZZR   * A1L1ZZR * I[17][i][iS]
            // + A2ZZR   * A1L1ZZI * I[18][i][iS]
            + A2ZZI   * A3ZZR   * I[19][i][iS]
            + A2ZZI   * A3ZZI   * I[20][i][iS]
            // + A2ZZI   * A1L1ZZR * I[21][i][iS]
            // + A2ZZI   * A1L1ZZI * I[22][i][iS]
            + A3ZZR   * A3ZZI   * I[23][i][iS]
            // + A3ZZR   * A1L1ZZR * I[24][i][iS]
            // + A3ZZR   * A1L1ZZI * I[25][i][iS]
            // + A3ZZI   * A1L1ZZR * I[26][i][iS]
            // + A3ZZI   * A1L1ZZI * I[27][i][iS]
            // + A1L1ZZR * A1L1ZZI * I[28][i][iS];
            ;
         Likelihood[i] = Value[i] / Integral[i];

         LikelihoodB[i] = V[0][i][iS] / I[0][i][iS];

         LikelihoodZJ[i] = V2[0][i][iS] / I2[0][i][iS];

         LikelihoodBgg[i] = V2[1][i][iS] / I2[1][i][iS];
      }

      for(int i = 0; i < 5; i++)
      {
         if(Likelihood[i] < 0 || Likelihood[i] != Likelihood[i])
            Likelihood[i] = 0;
         if(LikelihoodB[i] < 0 || LikelihoodB[i] != LikelihoodB[i])
            LikelihoodB[i] = 0;
         if(LikelihoodZJ[i] < 0 || LikelihoodZJ[i] != LikelihoodZJ[i])
            LikelihoodZJ[i] = 0;
         if(LikelihoodBgg[i] < 0 || LikelihoodBgg[i] != LikelihoodBgg[i])
            LikelihoodBgg[i] = 0;
      }

      bool Good = true;
      double TotalNegative = 0;
      for(int i = 0; i < 5; i++)
      {
         if(Likelihood[i] < 0)
         {
            // cout << "Likelihood value smaller than zero.  Try to force minuit out of this area." << endl;
            // cout << iS << " " << i << " " << Likelihood[i] << endl;
            // cout << A1ZZR << " " << A2ZZR << " " << A2ZZI << " " << A3ZZR << " " << A3ZZI << endl;
            // cout << Value[i] << " " << Integral[i] << endl;
            // for(int j = 0; j < 28; j++)
            //    cout << j << " " << V[j][i][iS] << endl;

            Good = false;
            TotalNegative = TotalNegative + Likelihood[i];
         }
      }
      if(Good == false)
      {
         if(UsePenalty == true)
         {
            LogTotal = LogTotal - 99999;
            // LogTotal = LogTotal + TotalNegative * 10000;
         }
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

      double SignalLikelihood = LSa + LSb1 * N[0] + LSb2 * N[1];
      double BackgroundLikelihood = LBa + LBb1 * N[0] + LBb2 * N[1];
      double BackgroundZJLikelihood = LZJa + LZJb6 * N[5];
      double BackgroundggLikelihood = LBgga;

      if(BackgroundZJLikelihood < 0)
         BackgroundZJLikelihood = 0;

      // if(SignalLikelihood <= 0 || BackgroundLikelihood <= 0
      //    || BackgroundZJLikelihood <= 0 || BackgroundggLikelihood <= 0)
      if(SignalLikelihood < 0 || BackgroundLikelihood < 0
         || BackgroundZJLikelihood < 0)
      {
         // cout << "Combined single-type likelihood is negative.  Try to force minuit out of this area." << endl;
         cout << SignalLikelihood << " " << BackgroundLikelihood << " " << BackgroundZJLikelihood << endl;
         if(UsePenalty == true)
            LogTotal = LogTotal - 99999;
         continue;
      }

      int StateIndex = -1;
      if(S[iS] == "em")   StateIndex = 0;
      if(S[iS] == "me")   StateIndex = 0;   // EMME Fix TODO
      if(S[iS] == "ee")   StateIndex = 2;
      if(S[iS] == "mm")   StateIndex = 3;
      if(StateIndex < 0)
      {
         if(UsePenalty == true)
            LogTotal = LogTotal - 99999;
         cerr << "WTF State Index Not Valid.  S[iS] = \"" << S[iS] << "\"" << endl;
         continue;
      }

      int Is7TeV = -1;
      if(Energy[iS] == "7TeV")   Is7TeV = 1;
      if(Energy[iS] == "8TeV")   Is7TeV = 0;
      if(Is7TeV < 0)
      {
         if(UsePenalty == true)
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

      // cout << SignalLikelihood << " " << BackgroundLikelihood << " " << BackgroundZJLikelihood << " " << BackgroundggLikelihood << endl;
      // cout << "?" << LTotal << endl;

      if(LTotal != LTotal || LTotal <= 0 || F[Is7TeV][StateIndex] + FZJ[Is7TeV][StateIndex] + FggZZ[Is7TeV][StateIndex] > 1)
      {
         // cout << "Final combined likelihood is negative or sum of fraction above one.  Try to force minuit out of this area." << endl;
         // cout << "LTotal = " << LTotal << ", F = " << F[Is7TeV][StateIndex] << ", FZJ = " << FZJ[Is7TeV][StateIndex]
         //    << ", FggZZ = " << FggZZ[Is7TeV][StateIndex] << endl;
         // cout << "Likelihoods = " << SignalLikelihood << " " << BackgroundLikelihood << " "
         //    << BackgroundZJLikelihood << " " << BackgroundggLikelihood << endl;
         if(UsePenalty == true)
         {
            LogTotal = LogTotal - 99999;
            LogTotal = LogTotal - (F[Is7TeV][StateIndex] + FZJ[Is7TeV][StateIndex] + FggZZ[Is7TeV][StateIndex] - 1) * 10000;
         }
      }
      else
      {
         if(WeightedDataset == false)
            LogTotal = LogTotal + log(LTotal);
         else
            LogTotal = LogTotal + log(LTotal) * W[iS];
      }
   }

   // cout << "LOG_TOTAL " << LogTotal << endl;

   // Apply log normals and poissons
   for(int i = 0; i < 4; i++)
   {
      if(i == 1)       // EMME Fix TODO
         continue;

      for(int j = 0; j < 2; j++)
      {
         // double R = GetYieldFractionA1ZZA3ZZ(A1ZZR, A3ZZR, A3ZZI, j, i) * GetYieldFractionA1ZZA2ZZ(A1ZZR, A2ZZR, A2ZZI, j, i);
         double R = 1;
         double NS = Counts[j][i] * (1 - F[j][i] - FZJ[j][i] - FggZZ[j][i]) / SigmaMu / R;
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
            double PoissonMean = Counts[j][i];
            LogTotal = LogTotal + EventCount[j][i] * log(PoissonMean) - PoissonMean;
         }
      }
   }

   // Penalty terms for systematic errors
   double Factor[7] = {0.01, 0.1, 1, 1, 1, 0.1, 1};
   for(int i = 0; i < 7; i++)
      LogTotal = LogTotal - N[i] * N[i] / 2 / Factor[i];

   if(LogTotal != LogTotal)
   {
      cout << SampleSize << " " << A3ZZR << " " << SigmaMu << " " << LogTotal << " " << Counts[0][0] << " " << NSConstrainMu[0][0] << " " << NSConstrainSigma[0][0] << endl;
      for(int i = 0; i < 4; i++)
         cout << Counts[0][i] << " " << Counts[1][i] << endl;

      for(int i = 0; i < 56; i++)
         cout << i << " " << Parameters[i] << endl;
   }

   return -LogTotal * 2;
}

void FitClass::AddPoint(SingleEvent &event)
{
   AddPoint(event.v, event.i, event.v2, event.i2, event.event, event.state, event.energy, event.weight);
}

void FitClass::AddPoint(ReducedSingleEvent &event)
{
   AddPointReduced(event.v, event.i, event.v2, event.i2, event.event, event.state, event.energy, event.weight);
}

void FitClass::AddPoint(double v[154][13], double i[154][13], double v2[2][13], double i2[2][13],
   EventParameters &Event, string State, string SqrtS, double Weight)
{
   for(int j1 = 0; j1 < 154; j1++)
   {
      int j0 = -1;
      if(j1 == 0)     j0 = 0;
      if(j1 == 1)     j0 = 1;
      if(j1 == 2)     j0 = 2;
      if(j1 == 3)     j0 = 3;
      if(j1 == 4)     j0 = 4;
      if(j1 == 5)     j0 = 5;
      if(j1 == 92)    j0 = 6;
      if(j1 == 93)    j0 = 7;
      if(j1 == 14)    j0 = 8;
      if(j1 == 15)    j0 = 9;
      if(j1 == 16)    j0 = 10;
      if(j1 == 17)    j0 = 11;
      if(j1 == 96)    j0 = 12;
      if(j1 == 109)   j0 = 13;
      if(j1 == 26)    j0 = 14;
      if(j1 == 27)    j0 = 15;
      if(j1 == 28)    j0 = 16;
      if(j1 == 97)    j0 = 17;
      if(j1 == 110)   j0 = 18;
      if(j1 == 37)    j0 = 19;
      if(j1 == 38)    j0 = 20;
      if(j1 == 98)    j0 = 21;
      if(j1 == 111)   j0 = 22;
      if(j1 == 47)    j0 = 23;
      if(j1 == 99)    j0 = 24;
      if(j1 == 112)   j0 = 25;
      if(j1 == 100)   j0 = 26;
      if(j1 == 113)   j0 = 27;
      if(j1 == 122)   j0 = 28;

      if(j0 < 0)
         continue;

      for(int j2 = 0; j2 < 13; j2++)
      {
         V[j0][j2].push_back(v[j1][j2]);
         I[j0][j2].push_back(i[j1][j2]);
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

   // E.push_back(Event);
   S.push_back(State);
   Energy.push_back(SqrtS);
   W.push_back(Weight);

   SampleSize = SampleSize + 1;
}

void FitClass::AddPointReduced(double v[29][13], double i[29][13], double v2[2][13], double i2[2][13],
   EventParameters &Event, string State, string SqrtS, double Weight)
{
   for(int j1 = 0; j1 < 29; j1++)
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

   // E.push_back(Event);
   S.push_back(State);
   Energy.push_back(SqrtS);
   W.push_back(Weight);

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   for(int i1 = 0; i1 < 29; i1++)
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
   WeightedDataset = configuration.WeightedDataset;

   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(1);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   // Worker->SetTolerance(1e-3);
   Worker->SetStrategy(2);

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

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 56);
   Worker->SetFunction(Function);

   EventCount[0][0] = SignalStateCount[0][0] + BackgroundStateCount[0][0] + ZJStateCount[0][0] + ggZZStateCount[0][0];
   EventCount[0][1] = SignalStateCount[0][1] + BackgroundStateCount[0][1] + ZJStateCount[0][1] + ggZZStateCount[0][1];
   EventCount[0][2] = SignalStateCount[0][2] + BackgroundStateCount[0][2] + ZJStateCount[0][2] + ggZZStateCount[0][2];
   EventCount[0][3] = SignalStateCount[0][3] + BackgroundStateCount[0][3] + ZJStateCount[0][3] + ggZZStateCount[0][3];
   EventCount[1][0] = SignalStateCount[1][0] + BackgroundStateCount[1][0] + ZJStateCount[1][0] + ggZZStateCount[1][0];
   EventCount[1][1] = SignalStateCount[1][1] + BackgroundStateCount[1][1] + ZJStateCount[1][1] + ggZZStateCount[1][1];
   EventCount[1][2] = SignalStateCount[1][2] + BackgroundStateCount[1][2] + ZJStateCount[1][2] + ggZZStateCount[1][2];
   EventCount[1][3] = SignalStateCount[1][3] + BackgroundStateCount[1][3] + ZJStateCount[1][3] + ggZZStateCount[1][3];

   if(configuration.GuessInitialFValue == true)
   {
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
   }

   double StepSize[56] = {0};
   for(int i = 0; i < 16; i++)
      StepSize[i] = 0.05;
   for(int i = 16; i < 24; i++)
      StepSize[i] = 1;
   for(int i = 24; i < 48; i++)
      StepSize[i] = 0.01;
   for(int i = 48; i < 55; i++)
      StepSize[i] = 0.01;
   StepSize[55] = 0.01;

   for(int i = 0; i < 2; i++)
   {
      for(int j = 0; j < 4; j++)
         cout << configuration.CountInitialValue[i][j] << " ";
      cout << endl;
   }

   if(configuration.FloatAA[0] == true)          Worker->SetLimitedVariable(0,  "A2ZZA1ZZ",    configuration.AAInitialValue[0], StepSize[0], -1000, 1000);
   if(configuration.FloatAA[0] == false)         Worker->SetFixedVariable  (0,  "A2ZZA1ZZ",    configuration.AAInitialValue[0]);
   if(configuration.FloatPhase[0] == true)       Worker->SetLimitedVariable(1,  "A2ZZPhase",   configuration.PhaseInitialValue[0], StepSize[1], -PI * 10, PI * 10);
   if(configuration.FloatPhase[0] == false)      Worker->SetFixedVariable  (1,  "A2ZZPhase",   configuration.PhaseInitialValue[0]);
   if(configuration.FloatAA[1] == true)          Worker->SetLimitedVariable(2,  "A3ZZA1ZZ",    configuration.AAInitialValue[1], StepSize[2], -1000, 1000);
   if(configuration.FloatAA[1] == false)         Worker->SetFixedVariable  (2,  "A3ZZA1ZZ",    configuration.AAInitialValue[1]);
   if(configuration.FloatPhase[1] == true)       Worker->SetLimitedVariable(3,  "A3ZZPhase",   configuration.PhaseInitialValue[1], StepSize[3], -PI * 10, PI * 10);
   if(configuration.FloatPhase[1] == false)      Worker->SetFixedVariable  (3,  "A3ZZPhase",   configuration.PhaseInitialValue[1]);
   if(configuration.FloatAA[2] == true)          Worker->SetLimitedVariable(4,  "A2ZAA1ZZ",    configuration.AAInitialValue[2], StepSize[4], -1000, 1000);
   if(configuration.FloatAA[2] == false)         Worker->SetFixedVariable  (4,  "A2ZAA1ZZ",    configuration.AAInitialValue[2]);
   if(configuration.FloatPhase[2] == true)       Worker->SetLimitedVariable(5,  "A2ZAPhase",   configuration.PhaseInitialValue[2], StepSize[5], -PI * 10, PI * 10);
   if(configuration.FloatPhase[2] == false)      Worker->SetFixedVariable  (5,  "A2ZAPhase",   configuration.PhaseInitialValue[2]);
   if(configuration.FloatAA[3] == true)          Worker->SetLimitedVariable(6,  "A3ZAA1ZZ",    configuration.AAInitialValue[3], StepSize[6], -1000, 1000);
   if(configuration.FloatAA[3] == false)         Worker->SetFixedVariable  (6,  "A3ZAA1ZZ",    configuration.AAInitialValue[3]);
   if(configuration.FloatPhase[3] == true)       Worker->SetLimitedVariable(7,  "A3ZAPhase",   configuration.PhaseInitialValue[3], StepSize[7], -PI * 10, PI * 10);
   if(configuration.FloatPhase[3] == false)      Worker->SetFixedVariable  (7,  "A3ZAPhase",   configuration.PhaseInitialValue[3]);
   if(configuration.FloatAA[4] == true)          Worker->SetLimitedVariable(8,  "A2AAA1ZZ",    configuration.AAInitialValue[4], StepSize[8], -1000, 1000);
   if(configuration.FloatAA[4] == false)         Worker->SetFixedVariable  (8,  "A2AAA1ZZ",    configuration.AAInitialValue[4]);
   if(configuration.FloatPhase[4] == true)       Worker->SetLimitedVariable(9,  "A2AAPhase",   configuration.PhaseInitialValue[4], StepSize[9], -PI * 10, PI * 10);
   if(configuration.FloatPhase[4] == false)      Worker->SetFixedVariable  (9,  "A2AAPhase",   configuration.PhaseInitialValue[4]);
   if(configuration.FloatAA[5] == true)          Worker->SetLimitedVariable(10, "A3AAA1ZZ",    configuration.AAInitialValue[5], StepSize[10], -1000, 1000);
   if(configuration.FloatAA[5] == false)         Worker->SetFixedVariable  (10, "A3AAA1ZZ",    configuration.AAInitialValue[5]);
   if(configuration.FloatPhase[5] == true)       Worker->SetLimitedVariable(11, "A3AAPhase",   configuration.PhaseInitialValue[5], StepSize[11], -PI * 10, PI * 10);
   if(configuration.FloatPhase[5] == false)      Worker->SetFixedVariable  (11, "A3AAPhase",   configuration.PhaseInitialValue[5]);
   if(configuration.FloatAA[6] == true)          Worker->SetLimitedVariable(12, "A1L1ZZ",      configuration.AAInitialValue[6], StepSize[12], -0.01, 0.01);
   if(configuration.FloatAA[6] == false)         Worker->SetFixedVariable  (12, "A1L1ZZ",      configuration.AAInitialValue[6]);
   if(configuration.FloatPhase[6] == true)       Worker->SetLimitedVariable(13, "A1L1ZZPhase", configuration.PhaseInitialValue[6], StepSize[13], -PI * 10, PI * 10);
   if(configuration.FloatPhase[6] == false)      Worker->SetFixedVariable  (13, "A1L1ZZPhase", configuration.PhaseInitialValue[6]);
   if(configuration.FloatAA[7] == true)          Worker->SetLimitedVariable(14, "A1LQZZ",      configuration.AAInitialValue[7], StepSize[14], -1000, 1000);
   if(configuration.FloatAA[7] == false)         Worker->SetFixedVariable  (14, "A1LQZZ",      configuration.AAInitialValue[7]);
   if(configuration.FloatPhase[7] == true)       Worker->SetLimitedVariable(15, "A1LQZZPhase", configuration.PhaseInitialValue[7], StepSize[15], -PI * 10, PI * 10);
   if(configuration.FloatPhase[7] == false)      Worker->SetFixedVariable  (15, "A1LQZZPhase", configuration.PhaseInitialValue[7]);
   if(configuration.FloatCount[0][0] == true)    Worker->SetLimitedVariable(16, "Nem8TeV",     configuration.CountInitialValue[0][0], StepSize[16], 0, 100000);
   if(configuration.FloatCount[0][0] == false)   Worker->SetFixedVariable  (16, "Nem8TeV",     configuration.CountInitialValue[0][0]);
   if(configuration.FloatCount[0][1] == true)    Worker->SetLimitedVariable(17, "Nme8TeV",     configuration.CountInitialValue[0][1], StepSize[17], 0, 100000);
   if(configuration.FloatCount[0][1] == false)   Worker->SetFixedVariable  (17, "Nme8TeV",     configuration.CountInitialValue[0][1]);
   if(configuration.FloatCount[0][2] == true)    Worker->SetLimitedVariable(18, "Nee8TeV",     configuration.CountInitialValue[0][2], StepSize[18], 0, 100000);
   if(configuration.FloatCount[0][2] == false)   Worker->SetFixedVariable  (18, "Nee8TeV",     configuration.CountInitialValue[0][2]);
   if(configuration.FloatCount[0][3] == true)    Worker->SetLimitedVariable(19, "Nmm8TeV",     configuration.CountInitialValue[0][3], StepSize[19], 0, 100000);
   if(configuration.FloatCount[0][3] == false)   Worker->SetFixedVariable  (19, "Nmm8TeV",     configuration.CountInitialValue[0][3]);
   if(configuration.FloatCount[1][0] == true)    Worker->SetLimitedVariable(20, "Nem7TeV",     configuration.CountInitialValue[1][0], StepSize[20], 0, 100000);
   if(configuration.FloatCount[1][0] == false)   Worker->SetFixedVariable  (20, "Nem7TeV",     configuration.CountInitialValue[1][0]);
   if(configuration.FloatCount[1][1] == true)    Worker->SetLimitedVariable(21, "Nme7TeV",     configuration.CountInitialValue[1][1], StepSize[21], 0, 100000);
   if(configuration.FloatCount[1][1] == false)   Worker->SetFixedVariable  (21, "Nme7TeV",     configuration.CountInitialValue[1][1]);
   if(configuration.FloatCount[1][2] == true)    Worker->SetLimitedVariable(22, "Nee7TeV",     configuration.CountInitialValue[1][2], StepSize[22], 0, 100000);
   if(configuration.FloatCount[1][2] == false)   Worker->SetFixedVariable  (22, "Nee7TeV",     configuration.CountInitialValue[1][2]);
   if(configuration.FloatCount[1][3] == true)    Worker->SetLimitedVariable(23, "Nmm7TeV",     configuration.CountInitialValue[1][3], StepSize[23], 0, 100000);
   if(configuration.FloatCount[1][3] == false)   Worker->SetFixedVariable  (23, "Nmm7TeV",     configuration.CountInitialValue[1][3]);
   if(configuration.FloatF[0][0] == true)        Worker->SetLimitedVariable(24, "Fem8TeV",     configuration.FInitialValue[0][0], StepSize[24], 0, 1);
   if(configuration.FloatF[0][0] == false)       Worker->SetFixedVariable  (24, "Fem8TeV",     configuration.FInitialValue[0][0]);
   if(configuration.FloatF[0][1] == true)        Worker->SetLimitedVariable(25, "Fme8TeV",     configuration.FInitialValue[0][1], StepSize[25], 0, 1);
   if(configuration.FloatF[0][1] == false)       Worker->SetFixedVariable  (25, "Fme8TeV",     configuration.FInitialValue[0][1]);
   if(configuration.FloatF[0][2] == true)        Worker->SetLimitedVariable(26, "Fee8TeV",     configuration.FInitialValue[0][2], StepSize[26], 0, 1);
   if(configuration.FloatF[0][2] == false)       Worker->SetFixedVariable  (26, "Fee8TeV",     configuration.FInitialValue[0][2]);
   if(configuration.FloatF[0][3] == true)        Worker->SetLimitedVariable(27, "Fmm8TeV",     configuration.FInitialValue[0][3], StepSize[27], 0, 1);
   if(configuration.FloatF[0][3] == false)       Worker->SetFixedVariable  (27, "Fmm8TeV",     configuration.FInitialValue[0][3]);
   if(configuration.FloatF[1][0] == true)        Worker->SetLimitedVariable(28, "Fem7TeV",     configuration.FInitialValue[1][0], StepSize[28], 0, 1);
   if(configuration.FloatF[1][0] == false)       Worker->SetFixedVariable  (28, "Fem7TeV",     configuration.FInitialValue[1][0]);
   if(configuration.FloatF[1][1] == true)        Worker->SetLimitedVariable(29, "Fme7TeV",     configuration.FInitialValue[1][1], StepSize[29], 0, 1);
   if(configuration.FloatF[1][1] == false)       Worker->SetFixedVariable  (29, "Fme7TeV",     configuration.FInitialValue[1][1]);
   if(configuration.FloatF[1][2] == true)        Worker->SetLimitedVariable(30, "Fee7TeV",     configuration.FInitialValue[1][2], StepSize[30], 0, 1);
   if(configuration.FloatF[1][2] == false)       Worker->SetFixedVariable  (30, "Fee7TeV",     configuration.FInitialValue[1][2]);
   if(configuration.FloatF[1][3] == true)        Worker->SetLimitedVariable(31, "Fmm7TeV",     configuration.FInitialValue[1][3], StepSize[31], 0, 1);
   if(configuration.FloatF[1][3] == false)       Worker->SetFixedVariable  (31, "Fmm7TeV",     configuration.FInitialValue[1][3]);
   if(configuration.FloatFZJ[0][0] == true)      Worker->SetLimitedVariable(32, "FZJem8TeV",   configuration.FZJInitialValue[0][0], StepSize[32], 0, 1);
   if(configuration.FloatFZJ[0][0] == false)     Worker->SetFixedVariable  (32, "FZJem8TeV",   configuration.FZJInitialValue[0][0]);
   if(configuration.FloatFZJ[0][1] == true)      Worker->SetLimitedVariable(33, "FZJme8TeV",   configuration.FZJInitialValue[0][1], StepSize[33], 0, 1);
   if(configuration.FloatFZJ[0][1] == false)     Worker->SetFixedVariable  (33, "FZJme8TeV",   configuration.FZJInitialValue[0][1]);
   if(configuration.FloatFZJ[0][2] == true)      Worker->SetLimitedVariable(34, "FZJee8TeV",   configuration.FZJInitialValue[0][2], StepSize[34], 0, 1);
   if(configuration.FloatFZJ[0][2] == false)     Worker->SetFixedVariable  (34, "FZJee8TeV",   configuration.FZJInitialValue[0][2]);
   if(configuration.FloatFZJ[0][3] == true)      Worker->SetLimitedVariable(35, "FZJmm8TeV",   configuration.FZJInitialValue[0][3], StepSize[35], 0, 1);
   if(configuration.FloatFZJ[0][3] == false)     Worker->SetFixedVariable  (35, "FZJmm8TeV",   configuration.FZJInitialValue[0][3]);
   if(configuration.FloatFZJ[1][0] == true)      Worker->SetLimitedVariable(36, "FZJem7TeV",   configuration.FZJInitialValue[1][0], StepSize[36], 0, 1);
   if(configuration.FloatFZJ[1][0] == false)     Worker->SetFixedVariable  (36, "FZJem7TeV",   configuration.FZJInitialValue[1][0]);
   if(configuration.FloatFZJ[1][1] == true)      Worker->SetLimitedVariable(37, "FZJme7TeV",   configuration.FZJInitialValue[1][1], StepSize[37], 0, 1);
   if(configuration.FloatFZJ[1][1] == false)     Worker->SetFixedVariable  (37, "FZJme7TeV",   configuration.FZJInitialValue[1][1]);
   if(configuration.FloatFZJ[1][2] == true)      Worker->SetLimitedVariable(38, "FZJee7TeV",   configuration.FZJInitialValue[1][2], StepSize[38], 0, 1);
   if(configuration.FloatFZJ[1][2] == false)     Worker->SetFixedVariable  (38, "FZJee7TeV",   configuration.FZJInitialValue[1][2]);
   if(configuration.FloatFZJ[1][3] == true)      Worker->SetLimitedVariable(39, "FZJmm7TeV",   configuration.FZJInitialValue[1][3], StepSize[39], 0, 1);
   if(configuration.FloatFZJ[1][3] == false)     Worker->SetFixedVariable  (39, "FZJmm7TeV",   configuration.FZJInitialValue[1][3]);
   if(configuration.FloatFggZZ[0][0] == true)    Worker->SetLimitedVariable(40, "FggZZem8TeV", configuration.FggZZInitialValue[0][0], StepSize[40], 0, 1);
   if(configuration.FloatFggZZ[0][0] == false)   Worker->SetFixedVariable  (40, "FggZZem8TeV", configuration.FggZZInitialValue[0][0]);
   if(configuration.FloatFggZZ[0][1] == true)    Worker->SetLimitedVariable(41, "FggZZme8TeV", configuration.FggZZInitialValue[0][1], StepSize[41], 0, 1);
   if(configuration.FloatFggZZ[0][1] == false)   Worker->SetFixedVariable  (41, "FggZZme8TeV", configuration.FggZZInitialValue[0][1]);
   if(configuration.FloatFggZZ[0][2] == true)    Worker->SetLimitedVariable(42, "FggZZee8TeV", configuration.FggZZInitialValue[0][2], StepSize[42], 0, 1);
   if(configuration.FloatFggZZ[0][2] == false)   Worker->SetFixedVariable  (42, "FggZZee8TeV", configuration.FggZZInitialValue[0][2]);
   if(configuration.FloatFggZZ[0][3] == true)    Worker->SetLimitedVariable(43, "FggZZmm8TeV", configuration.FggZZInitialValue[0][3], StepSize[43], 0, 1);
   if(configuration.FloatFggZZ[0][3] == false)   Worker->SetFixedVariable  (43, "FggZZmm8TeV", configuration.FggZZInitialValue[0][3]);
   if(configuration.FloatFggZZ[1][0] == true)    Worker->SetLimitedVariable(44, "FggZZem7TeV", configuration.FggZZInitialValue[1][0], StepSize[44], 0, 1);
   if(configuration.FloatFggZZ[1][0] == false)   Worker->SetFixedVariable  (44, "FggZZem7TeV", configuration.FggZZInitialValue[1][0]);
   if(configuration.FloatFggZZ[1][1] == true)    Worker->SetLimitedVariable(45, "FggZZme7TeV", configuration.FggZZInitialValue[1][1], StepSize[45], 0, 1);
   if(configuration.FloatFggZZ[1][1] == false)   Worker->SetFixedVariable  (45, "FggZZme7TeV", configuration.FggZZInitialValue[1][1]);
   if(configuration.FloatFggZZ[1][2] == true)    Worker->SetLimitedVariable(46, "FggZZee7TeV", configuration.FggZZInitialValue[1][2], StepSize[46], 0, 1);
   if(configuration.FloatFggZZ[1][2] == false)   Worker->SetFixedVariable  (46, "FggZZee7TeV", configuration.FggZZInitialValue[1][2]);
   if(configuration.FloatFggZZ[1][3] == true)    Worker->SetLimitedVariable(47, "FggZZmm7TeV", configuration.FggZZInitialValue[1][3], StepSize[47], 0, 1);
   if(configuration.FloatFggZZ[1][3] == false)   Worker->SetFixedVariable  (47, "FggZZmm7TeV", configuration.FggZZInitialValue[1][3]);
   if(configuration.FloatN[0] == true)           Worker->SetLimitedVariable(48, "N1",          configuration.NInitialValue[0], StepSize[48], -5, 5);
   if(configuration.FloatN[0] == false)          Worker->SetFixedVariable  (48, "N1",          configuration.NInitialValue[0]);
   if(configuration.FloatN[1] == true)           Worker->SetLimitedVariable(49, "N2",          configuration.NInitialValue[1], StepSize[49], -5, 5);
   if(configuration.FloatN[1] == false)          Worker->SetFixedVariable  (49, "N2",          configuration.NInitialValue[1]);
   if(configuration.FloatN[2] == true)           Worker->SetLimitedVariable(50, "N3",          configuration.NInitialValue[2], StepSize[50], -5, 5);
   if(configuration.FloatN[2] == false)          Worker->SetFixedVariable  (50, "N3",          configuration.NInitialValue[2]);
   if(configuration.FloatN[3] == true)           Worker->SetLimitedVariable(51, "N4",          configuration.NInitialValue[3], StepSize[51], -5, 5);
   if(configuration.FloatN[3] == false)          Worker->SetFixedVariable  (51, "N4",          configuration.NInitialValue[3]);
   if(configuration.FloatN[4] == true)           Worker->SetLimitedVariable(52, "N5",          configuration.NInitialValue[4], StepSize[52], -5, 5);
   if(configuration.FloatN[4] == false)          Worker->SetFixedVariable  (52, "N5",          configuration.NInitialValue[4]);
   if(configuration.FloatN[5] == true)           Worker->SetLimitedVariable(53, "N6",          configuration.NInitialValue[5], StepSize[53], -5, 5);
   if(configuration.FloatN[5] == false)          Worker->SetFixedVariable  (53, "N6",          configuration.NInitialValue[5]);
   if(configuration.FloatN[6] == true)           Worker->SetLimitedVariable(54, "N7",          configuration.NInitialValue[6], StepSize[54], -5, 5);
   if(configuration.FloatN[6] == false)          Worker->SetFixedVariable  (54, "N7",          configuration.NInitialValue[6]);
   if(configuration.FloatMu == true)             Worker->SetLimitedVariable(55, "Mu",          configuration.MuInitialValue, StepSize[55], 0, 1000);
   if(configuration.FloatMu == false)            Worker->SetFixedVariable  (55, "Mu",          configuration.MuInitialValue);


   const int Tries = 1;
   FitResultSummary Result[Tries];

   for(int i = 0; i < Tries; i++)
   {
      Worker->Minimize();

      const double *Parameters = Worker->X();
      const double *Errors = Worker->Errors();

      Result[i].AA[0] = Parameters[0];          Result[i].AAError[0] = Errors[0];
      Result[i].Phase[0] = Parameters[1];       Result[i].PhaseError[0] = Errors[1];
      Result[i].AA[1] = Parameters[2];          Result[i].AAError[1] = Errors[2];
      Result[i].Phase[1] = Parameters[3];       Result[i].PhaseError[1] = Errors[3];
      Result[i].AA[2] = Parameters[4];          Result[i].AAError[2] = Errors[4];
      Result[i].Phase[2] = Parameters[5];       Result[i].PhaseError[2] = Errors[5];
      Result[i].AA[3] = Parameters[6];          Result[i].AAError[3] = Errors[6];
      Result[i].Phase[3] = Parameters[7];       Result[i].PhaseError[3] = Errors[7];
      Result[i].AA[4] = Parameters[8];          Result[i].AAError[4] = Errors[8];
      Result[i].Phase[4] = Parameters[9];       Result[i].PhaseError[4] = Errors[9];
      Result[i].AA[5] = Parameters[10];         Result[i].AAError[5] = Errors[10];
      Result[i].Phase[5] = Parameters[11];      Result[i].PhaseError[5] = Errors[11];
      Result[i].AA[6] = Parameters[12];         Result[i].AAError[6] = Errors[12];
      Result[i].Phase[6] = Parameters[13];      Result[i].PhaseError[6] = Errors[13];
      Result[i].AA[7] = Parameters[14];         Result[i].AAError[7] = Errors[14];
      Result[i].Phase[7] = Parameters[15];      Result[i].PhaseError[7] = Errors[15];
      Result[i].Count[0][0] = Parameters[16];   Result[i].CountError[0][0] = Errors[16];
      Result[i].Count[0][1] = Parameters[17];   Result[i].CountError[0][1] = Errors[17];
      Result[i].Count[0][2] = Parameters[18];   Result[i].CountError[0][2] = Errors[18];
      Result[i].Count[0][3] = Parameters[19];   Result[i].CountError[0][3] = Errors[19];
      Result[i].Count[1][0] = Parameters[20];   Result[i].CountError[1][0] = Errors[20];
      Result[i].Count[1][1] = Parameters[21];   Result[i].CountError[1][1] = Errors[21];
      Result[i].Count[1][2] = Parameters[22];   Result[i].CountError[1][2] = Errors[22];
      Result[i].Count[1][3] = Parameters[23];   Result[i].CountError[1][3] = Errors[23];
      Result[i].F[0][0] = Parameters[24];       Result[i].FError[0][0] = Errors[24];
      Result[i].F[0][1] = Parameters[25];       Result[i].FError[0][1] = Errors[25];
      Result[i].F[0][2] = Parameters[26];       Result[i].FError[0][2] = Errors[26];
      Result[i].F[0][3] = Parameters[27];       Result[i].FError[0][3] = Errors[27];
      Result[i].F[1][0] = Parameters[28];       Result[i].FError[1][0] = Errors[28];
      Result[i].F[1][1] = Parameters[29];       Result[i].FError[1][1] = Errors[29];
      Result[i].F[1][2] = Parameters[30];       Result[i].FError[1][2] = Errors[30];
      Result[i].F[1][3] = Parameters[31];       Result[i].FError[1][3] = Errors[31];
      Result[i].FZJ[0][0] = Parameters[32];     Result[i].FZJError[0][0] = Errors[32];
      Result[i].FZJ[0][1] = Parameters[33];     Result[i].FZJError[0][1] = Errors[33];
      Result[i].FZJ[0][2] = Parameters[34];     Result[i].FZJError[0][2] = Errors[34];
      Result[i].FZJ[0][3] = Parameters[35];     Result[i].FZJError[0][3] = Errors[35];
      Result[i].FZJ[1][0] = Parameters[36];     Result[i].FZJError[1][0] = Errors[36];
      Result[i].FZJ[1][1] = Parameters[37];     Result[i].FZJError[1][1] = Errors[37];
      Result[i].FZJ[1][2] = Parameters[38];     Result[i].FZJError[1][2] = Errors[38];
      Result[i].FZJ[1][3] = Parameters[39];     Result[i].FZJError[1][3] = Errors[39];
      Result[i].FggZZ[0][0] = Parameters[40];   Result[i].FggZZError[0][0] = Errors[40];
      Result[i].FggZZ[0][1] = Parameters[41];   Result[i].FggZZError[0][1] = Errors[41];
      Result[i].FggZZ[0][2] = Parameters[42];   Result[i].FggZZError[0][2] = Errors[42];
      Result[i].FggZZ[0][3] = Parameters[43];   Result[i].FggZZError[0][3] = Errors[43];
      Result[i].FggZZ[1][0] = Parameters[44];   Result[i].FggZZError[1][0] = Errors[44];
      Result[i].FggZZ[1][1] = Parameters[45];   Result[i].FggZZError[1][1] = Errors[45];
      Result[i].FggZZ[1][2] = Parameters[46];   Result[i].FggZZError[1][2] = Errors[46];
      Result[i].FggZZ[1][3] = Parameters[47];   Result[i].FggZZError[1][3] = Errors[47];
      Result[i].N[0] = Parameters[48];          Result[i].NError[0] = Errors[48];
      Result[i].N[1] = Parameters[49];          Result[i].NError[1] = Errors[49];
      Result[i].N[2] = Parameters[50];          Result[i].NError[2] = Errors[50];
      Result[i].N[3] = Parameters[51];          Result[i].NError[3] = Errors[51];
      Result[i].N[4] = Parameters[52];          Result[i].NError[4] = Errors[52];
      Result[i].N[5] = Parameters[53];          Result[i].NError[5] = Errors[53];
      Result[i].N[6] = Parameters[54];          Result[i].NError[6] = Errors[54];
      Result[i].EDM = Worker->Edm();
      Result[i].FitStatus = Worker->CovMatrixStatus();

      Result[i].S[0][0] = SignalStateCount[0][0];
      Result[i].S[0][1] = SignalStateCount[0][1];
      Result[i].S[0][2] = SignalStateCount[0][2];
      Result[i].S[0][3] = SignalStateCount[0][3];
      Result[i].S[1][0] = SignalStateCount[1][0];
      Result[i].S[1][1] = SignalStateCount[1][1];
      Result[i].S[1][2] = SignalStateCount[1][2];
      Result[i].S[1][3] = SignalStateCount[1][3];

      Result[i].B[0][0] = BackgroundStateCount[0][0];
      Result[i].B[0][1] = BackgroundStateCount[0][1];
      Result[i].B[0][2] = BackgroundStateCount[0][2];
      Result[i].B[0][3] = BackgroundStateCount[0][3];
      Result[i].B[1][0] = BackgroundStateCount[1][0];
      Result[i].B[1][1] = BackgroundStateCount[1][1];
      Result[i].B[1][2] = BackgroundStateCount[1][2];
      Result[i].B[1][3] = BackgroundStateCount[1][3];

      Result[i].ZJ[0][0] = ZJStateCount[0][0];
      Result[i].ZJ[0][1] = ZJStateCount[0][1];
      Result[i].ZJ[0][2] = ZJStateCount[0][2];
      Result[i].ZJ[0][3] = ZJStateCount[0][3];
      Result[i].ZJ[1][0] = ZJStateCount[1][0];
      Result[i].ZJ[1][1] = ZJStateCount[1][1];
      Result[i].ZJ[1][2] = ZJStateCount[1][2];
      Result[i].ZJ[1][3] = ZJStateCount[1][3];

      Result[i].ggZZ[0][0] = ggZZStateCount[0][0];
      Result[i].ggZZ[0][1] = ggZZStateCount[0][1];
      Result[i].ggZZ[0][2] = ggZZStateCount[0][2];
      Result[i].ggZZ[0][3] = ggZZStateCount[0][3];
      Result[i].ggZZ[1][0] = ggZZStateCount[1][0];
      Result[i].ggZZ[1][1] = ggZZStateCount[1][1];
      Result[i].ggZZ[1][2] = ggZZStateCount[1][2];
      Result[i].ggZZ[1][3] = ggZZStateCount[1][3];

      Result[i].BestNLL = CalculateLogLikelihoodAll(Parameters);

      bool CurrentSetting = UsePenalty;
      UsePenalty = false;
      Result[i].BestNLLNoPenalty = CalculateLogLikelihoodAll(Parameters);
      UsePenalty = CurrentSetting;

      Result[i].Mu = Parameters[55];
      Result[i].MuError = Errors[55];
   }

   delete Worker;

   int Best = 0;
   for(int i = 1; i < Tries; i++)
      if(Result[Best].BestNLLNoPenalty > Result[i].BestNLLNoPenalty)
         Best = i;

   return Result[Best];
}

void FitClass::PlotResult(PsFileHelper *PsFile, FitResultSummary Result)
{
   cout << "FitClass::PlotResult: Not implemented!" << endl;
}

double FitClass::GetLogNormalMu(double Mean, double RelativeError)
{
   // Median = input
   // return log(Mean);

   // Mean = input
   double Sigma2 = log(1 + RelativeError * RelativeError);
   return log(Mean) - Sigma2 / 2;
}

double FitClass::GetLogNormalSigma(double Mean, double RelativeError)
{
   // Median = input
   // return sqrt(log((1 + sqrt(1 + 4 * RelativeError * RelativeError)) / 2));

   // Mean = input
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




