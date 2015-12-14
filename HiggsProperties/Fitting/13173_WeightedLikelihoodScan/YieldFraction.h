#include <cmath>
using namespace std;

#include "DataHelperFwd.h"

double GetYieldFractionA1ZZA2ZZ(double A1ZZ, double A2ZZR, double A2ZZI, bool Is7TeV, int FinalState)
{
   double r1, r2, r3;
   if(Is7TeV == true && FinalState == 0)    r1 = 1.100, r2 = 3.923, r3 = 2.101;
   if(Is7TeV == true && FinalState == 1)    r1 = 1.099, r2 = 3.923, r3 = 2.100;
   if(Is7TeV == true && FinalState == 2)    r1 = 0.942, r2 = 3.667, r3 = 1.920;
   if(Is7TeV == true && FinalState == 3)    r1 = 0.948, r2 = 3.674, r3 = 1.926;
   if(Is7TeV == false && FinalState == 0)   r1 = 1.100, r2 = 3.923, r3 = 2.101;
   if(Is7TeV == false && FinalState == 1)   r1 = 1.100, r2 = 3.923, r3 = 2.101;
   if(Is7TeV == false && FinalState == 2)   r1 = 0.942, r2 = 3.667, r3 = 1.920;
   if(Is7TeV == false && FinalState == 3)   r1 = 0.947, r2 = 3.671, r3 = 1.925;

   double A1 = A1ZZ;
   double A2 = sqrt(A2ZZR * A2ZZR + A2ZZI * A2ZZI);
   double S1 = A1 * A1 / 1.000 / 1.000;
   double S2 = A2 * A2 / 3.276 / 3.276;
   double F = S2 / (S1 + S2);
   double CosPhi = -A2ZZR / A2;
   double SinPhi = A2ZZI / A2;

   return (1 - F) + F * r1 + sqrt(F * (1 - F)) * (CosPhi * (r2 - 1 - r1) + SinPhi * (r3 - 1 - r1));
}

double GetYieldFractionA1ZZA3ZZ(double A1ZZ, double A3ZZR, double A3ZZI, bool Is7TeV, int FinalState)
{
   double r1, r2, r3;
   if(Is7TeV == true && FinalState == 0)    r1 = 0.968, r2 = 1.970, r3 = 1.970;
   if(Is7TeV == true && FinalState == 1)    r1 = 0.968, r2 = 1.970, r3 = 1.970;
   if(Is7TeV == true && FinalState == 2)    r1 = 0.729, r2 = 1.729, r3 = 1.729;
   if(Is7TeV == true && FinalState == 3)    r1 = 0.787, r2 = 1.787, r3 = 1.787;
   if(Is7TeV == false && FinalState == 0)   r1 = 0.966, r2 = 1.968, r3 = 1.968;
   if(Is7TeV == false && FinalState == 1)   r1 = 0.966, r2 = 1.968, r3 = 1.968;
   if(Is7TeV == false && FinalState == 2)   r1 = 0.723, r2 = 1.723, r3 = 1.723;
   if(Is7TeV == false && FinalState == 3)   r1 = 0.787, r2 = 1.787, r3 = 1.787;

   double A1 = A1ZZ;
   double A3 = sqrt(A3ZZR * A3ZZR + A3ZZI * A3ZZI);
   double S1 = A1 * A1 / 1.000 / 1.000;
   double S3 = A3 * A3 / 5.042 / 5.042;
   double F = S3 / (S1 + S3);
   double CosPhi = A3ZZR / A3;
   double SinPhi = A3ZZI / A3;

   return (1 - F) + F * r1 + sqrt(F * (1 - F)) * (CosPhi * (r2 - 1 - r1) + SinPhi * (r3 - 1 - r1));
}

double GetNormalizationYieldFraction(double A1ZZR, double A2ZZR, double A2ZZI,
   double A3ZZR, double A3ZZI, bool Is7TeV, int FinalState)
{
   static DataHelper DHFile("Normalization.dh");

   string DHState = "";
   if(FinalState == 0)   DHState = "em";
   if(FinalState == 1)   DHState = "me";
   if(FinalState == 2)   DHState = "ee";
   if(FinalState == 3)   DHState = "mm";

   char Prefix = '\0';
   if(FinalState == 0)   Prefix = 'T';
   if(FinalState == 1)   Prefix = 'U';
   if(FinalState == 2)   Prefix = 'V';
   if(FinalState == 3)   Prefix = 'W';

   double I[91] = {0};
   for(int i = 0; i < 91; i++)
   {
      char State[20] = "X1_001";
      sprintf(State, "%c1_%03d", Prefix, i + 1);
      I[i] = DHFile[DHState][State].GetDouble();
   }

   double Sigma2 = 1 / 3.276 / 3.276;
   double Sigma3 = 1 / 5.042 / 5.042;
   double S2 = A1ZZR * A1ZZR + A2ZZR * A2ZZR * Sigma2 + A2ZZI * A2ZZI * Sigma2
      + A3ZZR * A3ZZR * Sigma3 + A3ZZI * A3ZZI * Sigma3;

   double IExotic = I[1-1] * A1ZZR * A1ZZR
      + I[2-1] * A2ZZR * A2ZZR
      + I[3-1] * A2ZZI * A2ZZI
      + I[4-1] * A3ZZR * A3ZZR
      + I[5-1] * A3ZZI * A3ZZI
      + I[14-1] * A1ZZR * A2ZZR
      + I[15-1] * A1ZZR * A2ZZI
      + I[16-1] * A1ZZR * A3ZZR
      + I[17-1] * A1ZZR * A3ZZI
      + I[26-1] * A2ZZR * A2ZZI
      + I[27-1] * A2ZZR * A3ZZR
      + I[28-1] * A2ZZR * A3ZZI
      + I[37-1] * A2ZZI * A3ZZR
      + I[38-1] * A2ZZI * A3ZZI
      + I[47-1] * A3ZZR * A3ZZI;
   IExotic = IExotic / S2;
   double ISM = I[1-1];

   return IExotic / ISM;
}






