#include <cmath>
#include <iostream>
#include <complex>
using namespace std;

#include "CalculateME.h"
#include "AngleConversion.h"
#include "Constants.h"

double GetGeneralScalar(LeptonVectors &leptons, GeneralScalarParameters &parameters, bool Reverse, bool UpType)
{
   double aAR = parameters.aAR, aAI = parameters.aAI;
   double aAdR = parameters.aAdR, aAdI = parameters.aAdI;
   double aZAR = parameters.aZAR, aZAI = parameters.aZAI;
   double aZAdR = parameters.aZAdR, aZAdI = parameters.aZAdI;
   double aZR = parameters.aZR, aZI = parameters.aZI;
   double aZdR = parameters.aZdR, aZdI = parameters.aZdI;
   double ahR = parameters.ahR, ahI = parameters.ahI;

   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double MH = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass();
   const double Mq = MH;
   const double s = MH * MH;
   const double x = (M1 * M1 - M2 * M2) / s;
   const double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   const double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   const double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   const double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   /*
   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }
   */

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;

   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (2*(-(aAdI*aAdI) - (aAdR*aAdR) + (aAI*aAI) + (aAR*aAR))*
        (C34*C34)*(C56*C56) - 
       2*(C36*C45 - C35*C46)*
        (-2*(aAdI*aAI + aAdR*aAR)*E3456 + 
          ((aAdI*aAdI) + (aAdR*aAdR) - (aAI*aAI) - (aAR*aAR))*
           (C36*C45 - C35*C46)) + 
       C34*(((aAdI*aAdI) + (aAdR*aAdR) + (aAI*aAI) + (aAR*aAR))*
           (C35*C35) + ((aAdI*aAdI) + (aAdR*aAdR) + (aAI*aAI) + 
             (aAR*aAR))*(C36*C36) + 
          ((aAdI*aAdI) + (aAdR*aAdR) + (aAI*aAI) + (aAR*aAR))*
           ((C45*C45) + (C46*C46)) + 
          2*((aAdI*aAdI) + (aAdR*aAdR) - (aAI*aAI) - (aAR*aAR))*
           C36*C45 + 
          2*((aAdI*aAdI) + (aAdR*aAdR) - (aAI*aAI) - (aAR*aAR))*
           C35*C46)*C56))/4096. + 
  ((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (-2*aAdR*aZAdI*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       4*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 4*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       4*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 4*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       4*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 4*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       4*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 4*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       6*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 6*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 6*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 6*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 6*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*aAdI*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 6*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 6*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*aAdI*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 6*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 6*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       8*aAdR*aZAdI*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 8*aAdI*aZAdR*gL*wZ*(M1*M1)*(M2*M2)*
        (MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       8*aAR*aZAI*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 8*aAI*aZAR*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       8*aAdR*aZAdI*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 8*aAdI*aZAdR*gR*wZ*(M1*M1)*(M2*M2)*
        (MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       8*aAR*aZAI*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 8*aAI*aZAR*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       8*aAdI*aZAdI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 8*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       8*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 8*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       8*aAdI*aZAdI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 8*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       8*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 8*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(gL + gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
          aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
          aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*MZ*wZ*
           ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
             (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))) - 
          aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          (aAdI*aZAdI + aAdR*aZAdR - aAI*aZAI - aAR*aZAR)*(MZ*MZ)*
           ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
           (wZ*wZ) + (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*
           ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C34*C34)*
        (C56*C56) + 2*(gL + gR)*E3456*
        (2*aAI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAdI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAdR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          3*aAI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAdI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          aAI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + aAR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          aAdI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + aAdR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          4*aAI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAdI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAdR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + aAR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + aAdR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          (aAR*aZAdI - aAI*aZAdR + aAdR*aZAI - aAdI*aZAR)*MZ*wZ*
           ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
             (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))) - 
          aAI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          (aAI*aZAdI + aAR*aZAdR + aAdI*aZAI + aAdR*aZAR)*(MZ*MZ)*
           ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
           (wZ*wZ) + (aAR*aZAdI - aAI*aZAdR + aAdR*aZAI - aAdI*aZAR)*
           ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*
        (C36*C45 - C35*C46) + 
       C34*((2*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             3*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAdI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAI*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAdR*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAR*aZAdI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             ((aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*
                 gL + (aAR*(aZAdR + aZAI) + 
                   (aAdR + aAI)*(aZAdI - aZAR))*gR)*MZ*wZ*
              ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ))) - aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             ((aAdR - aAI)*(aZAdR - aZAI)*gL + 
                (aAdR + aAI)*(aZAdR + aZAI)*gR + 
                aAR*(aZAdI*(gL - gR) + aZAR*(gL + gR)))*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             aAdI*(aZAR*(gL - gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                aZAdI*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) - 
                (aZAI*(-gL + gR) + aZAdR*(gL + gR))*MZ*wZ*
                 ((M1*M1*M1*M1)*(M2*M2) + 
                   (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1)*
                    ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             ((aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gL + 
                (aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gR)*
              ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*
           (C35*C35) + 
          (2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             MZ*wZ*(aAdR*(aZAR*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    ((M1*M1)*(M2*M2) - (MZ*MZ*MZ*MZ)) + 
                   aZAdI*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))\
)) + aAR*(-(aZAdR*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                      (M1*M2 + (MZ*MZ))) + 
                   aZAI*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))\
)) + aAI*(-(aZAdI*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                      (M1*M2 + (MZ*MZ))) - 
                   aZAR*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ)))\
)) + aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(aAdR*aZAdR*gL*(M1*M1*M1*M1) + 
                aAI*aZAdR*gL*(M1*M1*M1*M1) + aAdR*aZAI*gL*(M1*M1*M1*M1) + 
                aAI*aZAI*gL*(M1*M1*M1*M1) + aAdR*aZAdR*gR*(M1*M1*M1*M1) - 
                aAI*aZAdR*gR*(M1*M1*M1*M1) - aAdR*aZAI*gR*(M1*M1*M1*M1) + 
                aAI*aZAI*gR*(M1*M1*M1*M1) + aAdR*aZAdR*gL*(M2*M2*M2*M2) - 
                aAI*aZAdR*gL*(M2*M2*M2*M2) - aAdR*aZAI*gL*(M2*M2*M2*M2) + 
                aAI*aZAI*gL*(M2*M2*M2*M2) + aAdR*aZAdR*gR*(M2*M2*M2*M2) + 
                aAI*aZAdR*gR*(M2*M2*M2*M2) + aAdR*aZAI*gR*(M2*M2*M2*M2) + 
                aAI*aZAI*gR*(M2*M2*M2*M2) - 
                (((aAdR + aAI)*(aZAdR + aZAI)*gL + 
                      (aAdR - aAI)*(aZAdR - aZAI)*gR)*(M1*M1) + 
                   ((aAdR - aAI)*(aZAdR - aZAI)*gL + 
                      (aAdR + aAI)*(aZAdR + aZAI)*gR)*(M2*M2))*
                 (MZ*MZ) + 
                aAR*(-(aZAdI*(gL - gR)*(M1 - M2)*(M1 + M2)*
                      ((M1*M1) + (M2*M2) - (MZ*MZ))) + 
                   aZAR*(gL + gR)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))))*(wZ*wZ) + 
             aAdI*(aZAdI*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                MZ*(aZAR*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
                    ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                      ((M1*M1) + (M2*M2) - (MZ*MZ))*(wZ*wZ)) + 
                   wZ*(aZAI*(gL - gR)*(M1 - M2)*(M1 + M2)*
                       ((M1*M1)*(M2*M2) - 
                        (MZ*MZ)*((MZ*MZ) + (wZ*wZ))) - 
                      aZAdR*(gL + gR)*
                       ((M1*M1*M1*M1)*(M2*M2) + 
                        (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        (M1*M1)*
                        ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                        (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))) + 
             (((aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*
                    gL + (aAR*(-aZAdR + aZAI) + 
                      (aAdR - aAI)*(aZAdI + aZAR))*gR)*(M1*M1) + 
                ((aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*
                    gL + (aAR*(aZAdR + aZAI) + 
                      (aAdR + aAI)*(aZAdI - aZAR))*gR)*(M2*M2))*
              (MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45) + 
          (-2*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             3*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             4*aAR*aZAdI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAdI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAI*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAdR*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             ((aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gL + 
                (aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gR\
)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ))) + aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             ((-aAdR - aAI)*(aZAdR + aZAI)*gL + 
                aAR*(aZAdI - aZAR)*gL - 
                (aAdR - aAI)*(aZAdR - aZAI)*gR - aAR*(aZAdI + aZAR)*gR\
)*(MZ*MZ)*(-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             aAdI*(aZAdI*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                aZAR*(gL - gR)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ)*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    (-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) - 
                (aZAI*(gL - gR) + aZAdR*(gL + gR))*MZ*wZ*
                 ((M1*M1*M1*M1)*(M2*M2) + 
                   (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1)*
                    ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             ((aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gL + 
                (aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gR)*
              ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*
           (C46*C46) + 
          2*(gL + gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*MZ*wZ*
              ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ))) - aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (aAdI*aZAdI + aAdR*aZAdR - aAI*aZAI - aAR*aZAR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*
              ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C35*
           C46)*C56 + 
       2*(gL + gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
          aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
          aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*MZ*wZ*
           ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
             (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))) - 
          aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          (aAdI*aZAdI + aAdR*aZAdR - aAI*aZAI - aAR*aZAR)*(MZ*MZ)*
           ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
           (wZ*wZ) + (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*
           ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C36*
        C45*(2*C35*C46 + C34*C56) + 
       (C36*C36)*(-2*(gL + gR)*
           (2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*MZ*wZ*
              ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))\
) - aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (aAdI*aZAdI + aAdR*aZAdR - aAI*aZAI - aAR*aZAR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*
              ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45) \
+ (2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             MZ*wZ*(aAdR*(aZAR*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    (-((M1*M1)*(M2*M2)) + (MZ*MZ*MZ*MZ)) + 
                   aZAdI*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ)))) \
+ aAR*(aZAdR*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                    (M1*M2 + (MZ*MZ)) + 
                   aZAI*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ)))) \
+ aAI*(aZAdI*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                    (M1*M2 + (MZ*MZ)) - 
                   aZAR*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))))) \
- aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(aAdR*aZAdR*gL*(M1*M1*M1*M1) - 
                aAI*aZAdR*gL*(M1*M1*M1*M1) - aAdR*aZAI*gL*(M1*M1*M1*M1) + 
                aAI*aZAI*gL*(M1*M1*M1*M1) + aAdR*aZAdR*gR*(M1*M1*M1*M1) + 
                aAI*aZAdR*gR*(M1*M1*M1*M1) + aAdR*aZAI*gR*(M1*M1*M1*M1) + 
                aAI*aZAI*gR*(M1*M1*M1*M1) + aAdR*aZAdR*gL*(M2*M2*M2*M2) + 
                aAI*aZAdR*gL*(M2*M2*M2*M2) + aAdR*aZAI*gL*(M2*M2*M2*M2) + 
                aAI*aZAI*gL*(M2*M2*M2*M2) + aAdR*aZAdR*gR*(M2*M2*M2*M2) - 
                aAI*aZAdR*gR*(M2*M2*M2*M2) - aAdR*aZAI*gR*(M2*M2*M2*M2) + 
                aAI*aZAI*gR*(M2*M2*M2*M2) - 
                (((aAdR - aAI)*(aZAdR - aZAI)*gL + 
                      (aAdR + aAI)*(aZAdR + aZAI)*gR)*(M1*M1) + 
                   ((aAdR + aAI)*(aZAdR + aZAI)*gL + 
                      (aAdR - aAI)*(aZAdR - aZAI)*gR)*(M2*M2))*
                 (MZ*MZ) + aAR*
                 (aZAdI*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    ((M1*M1) + (M2*M2) - (MZ*MZ)) + 
                   aZAR*(gL + gR)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))))*(wZ*wZ) + 
             aAdI*(aZAdI*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                MZ*(-(aZAR*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
                      ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                        ((M1*M1) + (M2*M2) - (MZ*MZ))*(wZ*wZ))) + 
                   wZ*(-(aZAI*(gL - gR)*(M1 - M2)*(M1 + M2)*
                         ((M1*M1)*(M2*M2) - 
                         (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))) - 
                      aZAdR*(gL + gR)*
                       ((M1*M1*M1*M1)*(M2*M2) + 
                         (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         (M1*M1)*
                         ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                         (MZ*MZ)*(wZ*wZ)))))) + 
             (((aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gL + 
                   (aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gR\
)*(M1*M1) + ((aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gL + 
                   (aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gR\
)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C34*C56)))/4096. + 
  ((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) + 
       6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) + 
       6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*
        (MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*
        (MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*((aZAdI*aZAdI) + (aZAdR*aZAdR) - (aZAI*aZAI) - (aZAR*aZAR))*
        (2*gL*gR*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (MZ*MZ)*(wZ*wZ)) + 
          (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
          (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                (MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56) + 
       C34*(((((aZAdR-aZAI)*(aZAdR-aZAI)) + ((aZAdI+aZAR)*(aZAdI+aZAR)))*
              (gL*gL) + (((aZAdR+aZAI)*(aZAdR+aZAI)) + ((aZAdI-aZAR)*(aZAdI-aZAR)))*
              (gR*gR))*((MZ*MZ)*(wZ*wZ)*
              ((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C35*C35) + 
          (-2*aZAdR*aZAI*(gL - gR)*(gL + gR)*(M1 - M2)*(M1 + M2)*
              (MZ*MZ)*((M1*M1)*
                 (2*(M2*M2) - (MZ*MZ) - (wZ*wZ)) - 
                (M2*M2)*((MZ*MZ) + (wZ*wZ))) + 
             2*aZAdI*aZAR*(gL - gR)*(gL + gR)*(M1 - M2)*(M1 + M2)*
              (MZ*MZ)*((M1*M1)*
                 (2*(M2*M2) - (MZ*MZ) - (wZ*wZ)) - 
                (M2*M2)*((MZ*MZ) + (wZ*wZ))) + 
             (aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             (aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             ((aZAI*aZAI) + (aZAR*aZAR))*
              (4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))))*(C45*C45) + 
          ((((aZAdR+aZAI)*(aZAdR+aZAI)) + ((aZAdI-aZAR)*(aZAdI-aZAR)))*(gL*gL) + 
             (((aZAdR-aZAI)*(aZAdR-aZAI)) + ((aZAdI+aZAR)*(aZAdI+aZAR)))*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C46*C46) + 
          2*((aZAdI*aZAdI) + (aZAdR*aZAdR) - (aZAI*aZAI) - (aZAR*aZAR))*
           (4*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46)*
        C56 + 4*(aZAdI*aZAI + aZAdR*aZAR)*E3456*
        ((2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C36*C45 \
- (2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 \
- ((gL-gR)*(gL-gR))*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + (MZ*MZ)*(wZ*wZ))*
           C34*C56) + 
       (C36*C36)*(-2*((aZAdI*aZAdI) + (aZAdR*aZAdR) - (aZAI*aZAI) - 
             (aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*(C45*C45) + 
          (2*aZAdR*aZAI*(gL - gR)*(gL + gR)*(M1 - M2)*(M1 + M2)*
              (MZ*MZ)*((M1*M1)*
                 (2*(M2*M2) - (MZ*MZ) - (wZ*wZ)) - 
                (M2*M2)*((MZ*MZ) + (wZ*wZ))) - 
             2*aZAdI*aZAR*(gL - gR)*(gL + gR)*(M1 - M2)*(M1 + M2)*
              (MZ*MZ)*((M1*M1)*
                 (2*(M2*M2) - (MZ*MZ) - (wZ*wZ)) - 
                (M2*M2)*((MZ*MZ) + (wZ*wZ))) + 
             (aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))) + 
             (aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))) + 
             ((aZAI*aZAI) + (aZAR*aZAR))*
              (4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*C34*
           C56) + 2*((aZAdI*aZAdI) + (aZAdR*aZAdR) - (aZAI*aZAI) - 
          (aZAR*aZAR))*C36*C45*
        (2*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 + 
          ((gL*gL) + (gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*C34*C56)))/
   8192. - (el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (2*aZAdR*aZdI*gR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*gR*MZ*wZ*(gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*gR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*gR*MZ*wZ*(gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*MZ*wZ*(gL*gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*MZ*wZ*(gL*gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*MZ*wZ*(gL*gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*MZ*wZ*(gL*gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*gL*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*gL*MZ*wZ*(gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*gL*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*gL*MZ*wZ*(gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*MZ*wZ*(gR*gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*MZ*wZ*(gR*gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*MZ*wZ*(gR*gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*MZ*wZ*(gR*gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*gR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*gR*MZ*wZ*(gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*gR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*gR*MZ*wZ*(gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*MZ*wZ*(gL*gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*MZ*wZ*(gL*gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*MZ*wZ*(gL*gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*MZ*wZ*(gL*gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*gL*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*gL*MZ*wZ*(gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*gL*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*gL*MZ*wZ*(gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*MZ*wZ*(gR*gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*MZ*wZ*(gR*gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*MZ*wZ*(gR*gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*MZ*wZ*(gR*gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aZAdI*aZdI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aZAdR*aZdR*gR*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aZAI*aZI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aZAR*aZR*gR*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aZAdR*aZdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aZAI*aZI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aZAdI*aZdI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aZAdR*aZdR*gL*(gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aZAI*aZI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aZAR*aZR*gL*(gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aZAdR*aZdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aZAI*aZI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*(gL + gR)*((gL*gL) + (gR*gR))*
        ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*wZ*
           ((M1*M1) + (M2*M2)) + 
          (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
           (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
        (C34*C34)*(C56*C56) - 
       2*ahI*aZAI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       2*ahR*aZAR*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       2*ahI*aZAI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       2*ahR*aZAR*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAdI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAdR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       ahI*aZAdI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahR*aZAdR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       ahI*aZAdI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahR*aZAdR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAdI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAdR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       ahR*aZAdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahI*aZAdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       ahR*aZAdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahI*aZAdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       2*ahI*aZAI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       2*ahR*aZAR*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       2*ahI*aZAI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       2*ahR*aZAR*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       ahI*aZAdI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahR*aZAdR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAdI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAdR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAdI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAdR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 - 
       ahI*aZAdI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahR*aZAdR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 - 
       ahR*aZAdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahI*aZAdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 - 
       ahR*aZAdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahI*aZAdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 - 
       2*ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + 2*ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 + 
       2*ahI*aZAI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + 2*ahR*aZAR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 + 
       2*ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 - 2*ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 + 
       2*ahI*aZAI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + 2*ahR*aZAR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       ahI*aZAdI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAdR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - ahR*aZAI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahI*aZAR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + ahI*aZAdI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 + ahR*aZAdR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahR*aZAI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + ahI*aZAR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - ahI*aZAdI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahR*aZAdR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*
        C45*C46 + ahI*aZAR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahI*aZAdI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 + ahR*aZAdR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*
        C45*C46 - ahR*aZAI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahI*aZAR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 + ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahI*aZAI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahI*aZAI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - ahR*aZAR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahR*aZAdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahI*aZAdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - ahI*aZAI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahR*aZAR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + ahI*aZAdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahI*aZAI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + C34*
        (-2*gL*gR*(2*aZAdI*aZdI*gL*(M1*M1)*(M2*M2) + 
             2*aZAdR*aZdR*gL*(M1*M1)*(M2*M2) + 
             2*aZAR*aZR*gL*(M1*M1)*(M2*M2) + 
             2*aZAdI*aZdI*gR*(M1*M1)*(M2*M2) + 
             2*aZAdR*aZdR*gR*(M1*M1)*(M2*M2) + 
             2*aZAR*aZR*gR*(M1*M1)*(M2*M2) + 
             MZ*wZ*((((aZAdI + aZAR)*(-aZdR + aZI) + 
                      aZAdR*(aZdI + aZR))*gL + 
                   (-(aZAdI*(aZdR + aZI)) + aZAR*(aZdR + aZI) + 
                      aZAdR*(aZdI - aZR))*gR)*(M1*M1) + 
                ((-(aZAdI*(aZdR + aZI)) + aZAR*(aZdR + aZI) + 
                      aZAdR*(aZdI - aZR))*gL + 
                   ((aZAdI + aZAR)*(-aZdR + aZI) + 
                      aZAdR*(aZdI + aZR))*gR)*(M2*M2)) - 
             aZAdI*aZdI*gL*(M1*M1)*(MZ*MZ) - 
             aZAR*aZdI*gL*(M1*M1)*(MZ*MZ) - 
             aZAdR*aZdR*gL*(M1*M1)*(MZ*MZ) + 
             aZAdR*aZI*gL*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZR*gL*(M1*M1)*(MZ*MZ) - 
             aZAR*aZR*gL*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZdI*gR*(M1*M1)*(MZ*MZ) + 
             aZAR*aZdI*gR*(M1*M1)*(MZ*MZ) - 
             aZAdR*aZdR*gR*(M1*M1)*(MZ*MZ) - 
             aZAdR*aZI*gR*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZR*gR*(M1*M1)*(MZ*MZ) - 
             aZAR*aZR*gR*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZdI*gL*(M2*M2)*(MZ*MZ) + 
             aZAR*aZdI*gL*(M2*M2)*(MZ*MZ) - 
             aZAdR*aZdR*gL*(M2*M2)*(MZ*MZ) - 
             aZAdR*aZI*gL*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZR*gL*(M2*M2)*(MZ*MZ) - 
             aZAR*aZR*gL*(M2*M2)*(MZ*MZ) - 
             aZAdI*aZdI*gR*(M2*M2)*(MZ*MZ) - 
             aZAR*aZdI*gR*(M2*M2)*(MZ*MZ) - 
             aZAdR*aZdR*gR*(M2*M2)*(MZ*MZ) + 
             aZAdR*aZI*gR*(M2*M2)*(MZ*MZ) - 
             aZAdI*aZR*gR*(M2*M2)*(MZ*MZ) - 
             aZAR*aZR*gR*(M2*M2)*(MZ*MZ) + 
             aZAI*(MZ*(aZdR*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ - 
                   wZ*(aZdI*(gL - gR)*(M1 - M2)*(M1 + M2) + 
                      aZR*(gL + gR)*((M1*M1) + (M2*M2)))) + 
                aZI*(gL + gR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ))))*(C36*C36) \
+ 2*gL*gR*(-2*aZAdI*aZdI*gL*(M1*M1)*(M2*M2) - 
             2*aZAdR*aZdR*gL*(M1*M1)*(M2*M2) - 
             2*aZAR*aZR*gL*(M1*M1)*(M2*M2) - 
             2*aZAdI*aZdI*gR*(M1*M1)*(M2*M2) - 
             2*aZAdR*aZdR*gR*(M1*M1)*(M2*M2) - 
             2*aZAR*aZR*gR*(M1*M1)*(M2*M2) + 
             MZ*wZ*((((aZAdI - aZAR)*(aZdR + aZI) + 
                      aZAdR*(-aZdI + aZR))*gL - 
                   ((aZAdI + aZAR)*(-aZdR + aZI) + 
                      aZAdR*(aZdI + aZR))*gR)*(M1*M1) - 
                (((aZAdI + aZAR)*(-aZdR + aZI) + aZAdR*(aZdI + aZR))*
                    gL + (-(aZAdI*(aZdR + aZI)) + 
                      aZAR*(aZdR + aZI) + aZAdR*(aZdI - aZR))*gR)*
                 (M2*M2)) + aZAdI*aZdI*gL*(M1*M1)*(MZ*MZ) - 
             aZAR*aZdI*gL*(M1*M1)*(MZ*MZ) + 
             aZAdR*aZdR*gL*(M1*M1)*(MZ*MZ) + 
             aZAdR*aZI*gL*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZR*gL*(M1*M1)*(MZ*MZ) + 
             aZAR*aZR*gL*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZdI*gR*(M1*M1)*(MZ*MZ) + 
             aZAR*aZdI*gR*(M1*M1)*(MZ*MZ) + 
             aZAdR*aZdR*gR*(M1*M1)*(MZ*MZ) - 
             aZAdR*aZI*gR*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZR*gR*(M1*M1)*(MZ*MZ) + 
             aZAR*aZR*gR*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZdI*gL*(M2*M2)*(MZ*MZ) + 
             aZAR*aZdI*gL*(M2*M2)*(MZ*MZ) + 
             aZAdR*aZdR*gL*(M2*M2)*(MZ*MZ) - 
             aZAdR*aZI*gL*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZR*gL*(M2*M2)*(MZ*MZ) + 
             aZAR*aZR*gL*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZdI*gR*(M2*M2)*(MZ*MZ) - 
             aZAR*aZdI*gR*(M2*M2)*(MZ*MZ) + 
             aZAdR*aZdR*gR*(M2*M2)*(MZ*MZ) + 
             aZAdR*aZI*gR*(M2*M2)*(MZ*MZ) - 
             aZAdI*aZR*gR*(M2*M2)*(MZ*MZ) + 
             aZAR*aZR*gR*(M2*M2)*(MZ*MZ) + 
             aZAI*(MZ*(aZdR*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ + 
                   wZ*(aZdI*(gL - gR)*(-(M1*M1) + (M2*M2)) + 
                      aZR*(gL + gR)*((M1*M1) + (M2*M2)))) + 
                aZI*(gL + gR)*
                 (-2*(M1*M1)*(M2*M2) + 
                   ((M1*M1) + (M2*M2))*(MZ*MZ))))*(C45*C45) \
+ gL*gR*(MZ*MZ)*((gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
              (-(ahR*aZAdI*MZ) + ahI*aZAdR*MZ + ahI*aZAdI*wZ + 
                ahR*aZAdR*wZ) + 
             aZAI*(gL + gR)*(-2*ahI*(M1*M1)*(M2*M2) + 
                ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
             aZAR*(gL + gR)*(2*ahR*(M1*M1)*(M2*M2) + 
                ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45 + 
          C36*(gL*gR*(MZ*MZ)*
              ((-gL + gR)*(M1 - M2)*(M1 + M2)*MZ*
                 (-(ahR*aZAdI*MZ) + ahI*aZAdR*MZ + ahI*aZAdI*wZ + 
                   ahR*aZAdR*wZ) + 
                aZAI*(gL + gR)*
                 (-2*ahI*(M1*M1)*(M2*M2) + 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAR*(gL + gR)*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) + 
             4*((gL*gL*gL) + (gR*gR*gR))*
              ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*
                 wZ*((M1*M1) + (M2*M2)) + 
                (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C45) + 
          C46*((MZ*MZ)*
              (-(aZAdR*((gL*gL*gL) - (gR*gR*gR))*
                   (2*ahI*(M1*M1)*(M2*M2) - 
                     ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                     ahI*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
                aZAI*((gL*gL*gL) + (gR*gR*gR))*
                 (2*ahI*(M1*M1)*(M2*M2) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                ((aZAdI - aZAR)*(gL*gL*gL) - (aZAdI + aZAR)*(gR*gR*gR))*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) + 
             2*(-2*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2) + 
                2*aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2) + 
                2*aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
                2*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
                2*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
                2*aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
                2*aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
                2*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
                MZ*wZ*((aZAdI - aZAR)*(aZdR + aZI)*(gL*gL*gL) - 
                   (aZAdI + aZAR)*(-aZdR + aZI)*(gR*gR*gR))*
                 ((M1*M1) + (M2*M2)) + 
                aZAdR*MZ*wZ*((-aZdI + aZR)*(gL*gL*gL) - 
                   (aZdI + aZR)*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
                aZAI*MZ*wZ*((-aZdI + aZR)*(gL*gL*gL) + 
                   (aZdI + aZR)*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
                aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ) - 
                aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ) - 
                aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
                aZAR*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
                aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                aZAR*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                aZAdI*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ) - 
                aZAR*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ) - 
                aZAdI*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
                aZAR*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
                aZAdI*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
                aZAR*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
                aZAdI*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
                aZAR*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ) - 
                aZAdR*((aZdR + aZI)*(gL*gL*gL) + (aZdR - aZI)*(gR*gR*gR))*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAI*((aZdR + aZI)*(gL*gL*gL) + (-aZdR + aZI)*(gR*gR*gR))*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46))*
        C56 + E3456*
        (-2*ahI*aZAdI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C45 - 2*ahR*aZAdR*gR*(gL*gL)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*C45 - 
          2*ahI*aZAdI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C45 - 2*ahR*aZAdR*gL*(gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*C45 + 
          ahR*aZAdI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAdR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          ahR*aZAR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAdI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAdR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          ahI*aZAI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAdI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAdR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          ahI*aZAI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAdI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAdR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          ahR*aZAR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          ahI*aZAdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 - 
          ahI*aZAR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 - 
          ahR*aZAI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 - 
          ahR*aZAI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 - 
          ahI*aZAR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          C36*(gL*gR*(MZ*MZ)*
              ((gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
                 (-(ahR*aZAI*MZ) + ahI*aZAR*MZ + ahI*aZAI*wZ + 
                   ahR*aZAR*wZ) + 
                aZAdI*(gL + gR)*
                 (-2*ahI*(M1*M1)*(M2*M2) + 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAdR*(gL + gR)*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
             2*(gL + gR)*((gL*gL) + (gR*gR))*
              ((aZAR*aZdI - aZAI*aZdR + aZAdR*aZI - aZAdI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2)) + 
                (aZAI*aZdI + aZAR*aZdR + aZAdI*aZI + aZAdR*aZR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C45) + 
          2*ahI*aZAdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahR*aZAdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahR*aZAI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          2*ahI*aZAR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahI*aZAdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahR*aZAdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          2*ahR*aZAI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahI*aZAR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          ahR*aZAdI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAdR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          ahR*aZAR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAdI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAdR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          ahI*aZAI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAdI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAdR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          ahR*aZAR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAdI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAdR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          ahI*aZAI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          ahI*aZAdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 + 
          ahI*aZAR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 + 
          ahR*aZAI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          ahI*aZAR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          ahR*aZAI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          C35*(-((MZ*MZ)*
                (-(aZAR*((gL*gL*gL) - (gR*gR*gR))*
                     (2*ahI*(M1*M1)*(M2*M2) - 
                       ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                       ahI*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
                  aZAdI*((gL*gL*gL) + (gR*gR*gR))*
                   (2*ahI*(M1*M1)*(M2*M2) - 
                     ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                     ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                  (-((aZAdR - aZAI)*(gL*gL*gL)) - 
                     (aZAdR + aZAI)*(gR*gR*gR))*
                   (2*ahR*(M1*M1)*(M2*M2) + 
                     ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                     ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))) + 
             2*(gL + gR)*((gL*gL) + (gR*gR))*
              ((aZAR*aZdI - aZAI*aZdR + aZAdR*aZI - aZAdI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2)) + 
                (aZAI*aZdI + aZAR*aZdR + aZAdI*aZI + aZAdR*aZR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46) + 
          2*(gL + gR)*((gL-gR)*(gL-gR))*
           ((aZAR*aZdI - aZAI*aZdR + aZAdR*aZI - aZAdI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2)) + 
             (aZAI*aZdI + aZAR*aZdR + aZAdI*aZI + aZAdR*aZR)*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
           C34*C56) + 
       (C35*C35)*(-2*(gL + gR)*((gL*gL) + (gR*gR))*
           ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2)) + 
             (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))\
)*(C46*C46) + (MZ*MZ)*
           (aZAdR*((gL*gL*gL) - (gR*gR*gR))*
              (2*ahI*(M1*M1)*(M2*M2) - 
                ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
             aZAI*((gL*gL*gL) + (gR*gR*gR))*
              (2*ahI*(M1*M1)*(M2*M2) - 
                ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
             (-((aZAdI + aZAR)*(gL*gL*gL)) - (-aZAdI + aZAR)*(gR*gR*gR))*
              (2*ahR*(M1*M1)*(M2*M2) + 
                ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46 + 
          2*(-2*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             2*aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             2*aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             2*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             2*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
             2*aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
             2*aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
             2*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
             MZ*wZ*((aZAdI + aZAR)*(-aZdR + aZI)*(gL*gL*gL) - 
                (aZAdI - aZAR)*(aZdR + aZI)*(gR*gR*gR))*
              ((M1*M1) + (M2*M2)) - 
             aZAdR*MZ*wZ*((aZdI + aZR)*(gL*gL*gL) + 
                (aZdI - aZR)*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
             aZAI*MZ*wZ*((aZdI + aZR)*(gL*gL*gL) + 
                (-aZdI + aZR)*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
             aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             aZAR*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ) - 
             aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
             aZAR*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             aZAR*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             aZAR*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ) - 
             aZAR*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ) - 
             aZAdI*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
             aZAR*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
             aZAdR*((-aZdR + aZI)*(gL*gL*gL) - (aZdR + aZI)*(gR*gR*gR))*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)) \
- aZAI*((-aZdR + aZI)*(gL*gL*gL) + (aZdR + aZI)*(gR*gR*gR))*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
           C34*C56) - 
       C35*(-2*ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 2*ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) + 
          2*ahI*aZAI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 2*ahR*aZAR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) + 
          2*ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) - 2*ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) + 
          2*ahI*aZAI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 2*ahR*aZAR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          ahI*aZAdI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAdR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAdI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          ahR*aZAdR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAdI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAdR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAdI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahR*aZAdR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          ahR*aZAdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          gL*gR*(MZ*MZ)*((gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
              (-(ahR*aZAdI*MZ) + ahI*aZAdR*MZ + ahI*aZAdI*wZ + 
                ahR*aZAdR*wZ) + 
             aZAI*(gL + gR)*(-2*ahI*(M1*M1)*(M2*M2) + 
                ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
             aZAR*(gL + gR)*(2*ahR*(M1*M1)*(M2*M2) + 
                ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45*C46 \
+ C36*(gL*gR*(MZ*MZ)*((-gL + gR)*(M1 - M2)*(M1 + M2)*MZ*
                 (-(ahR*aZAdI*MZ) + ahI*aZAdR*MZ + ahI*aZAdI*wZ + 
                   ahR*aZAdR*wZ) + 
                aZAI*(gL + gR)*
                 (-2*ahI*(M1*M1)*(M2*M2) + 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAR*(gL + gR)*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46 + 
             C45*((MZ*MZ)*
                 (aZAdR*((gL*gL*gL) - (gR*gR*gR))*
                    (2*ahI*(M1*M1)*(M2*M2) - 
                      ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                      ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                   aZAI*((gL*gL*gL) + (gR*gR*gR))*
                    (2*ahI*(M1*M1)*(M2*M2) - 
                      ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                      ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (-((aZAdI + aZAR)*(gL*gL*gL)) - 
                      (-aZAdI + aZAR)*(gR*gR*gR))*
                    (2*ahR*(M1*M1)*(M2*M2) + 
                      ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                      ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
                4*(gL + gR)*((gL*gL) + (gR*gR))*
                 ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*
                    wZ*((M1*M1) + (M2*M2)) + 
                   (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
                    (2*(M1*M1)*(M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46)) - 
          C34*((MZ*MZ)*
              (aZAdR*((gL*gL*gL) - (gR*gR*gR))*
                 (2*ahI*(M1*M1)*(M2*M2) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAI*((gL*gL*gL) + (gR*gR*gR))*
                 (2*ahI*(M1*M1)*(M2*M2) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                (-((aZAdI + aZAR)*(gL*gL*gL)) - (-aZAdI + aZAR)*(gR*gR*gR))*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) + 
             4*gL*gR*(gL + gR)*
              ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2)) + 
                (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46)*C56)\
))/8192. - ((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (4*aAdR*aZdI*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*(C45*C45) - 
       4*aAdI*aZdR*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*
        (C45*C45) - 4*aAR*aZI*gL*gR*MZ*wZ*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       4*aAI*aZR*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*(C45*C45) + 
       2*aAdR*aZdI*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aAdI*aZdR*MZ*wZ*(gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aAR*aZI*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aAI*aZR*MZ*wZ*(gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aAdR*aZdI*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aAdI*aZdR*MZ*wZ*(gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aAR*aZI*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aAI*aZR*MZ*wZ*(gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       4*aAdR*aZdI*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aAdI*aZdR*gL*gR*MZ*wZ*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aAR*aZI*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*(C45*C45) + 
       4*aAI*aZR*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*(C45*C45) + 
       2*aAdR*aZdI*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aAdI*aZdR*MZ*wZ*(gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aAR*aZI*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aAI*aZR*MZ*wZ*(gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aAdR*aZdI*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aAdI*aZdR*MZ*wZ*(gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aAR*aZI*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aAI*aZR*MZ*wZ*(gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aAdI*aZdI*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aAdR*aZdR*gL*gR*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aAI*aZI*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aAR*aZR*gL*gR*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aAdI*aZdI*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aAdR*aZdR*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aAI*aZI*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aAR*aZR*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aAdI*aZdI*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aAdR*aZdR*(gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aAI*aZI*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aAR*aZR*(gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aAdI*aZdI*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 4*aAdR*aZdR*gL*gR*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       4*aAI*aZI*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 4*aAR*aZR*gL*gR*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       4*aAdI*aZdI*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 4*aAdR*aZdR*gL*gR*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       4*aAI*aZI*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 4*aAR*aZR*gL*gR*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       8*aAdR*aZdI*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       8*aAdI*aZdR*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       8*aAR*aZI*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       8*aAI*aZR*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAdR*aZdI*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) + 4*aAdI*aZdR*wZ*(gL*gL)*(MZ*MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       4*aAR*aZI*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAI*aZR*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAdR*aZdI*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) + 4*aAdI*aZdR*wZ*(gR*gR)*(MZ*MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       4*aAR*aZI*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAI*aZR*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       4*aAdI*aZdI*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       4*aAdR*aZdR*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAI*aZI*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAR*aZR*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       2*aAdI*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       2*aAdR*aZdR*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       2*aAI*aZI*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       2*aAR*aZR*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       2*aAdI*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       2*aAdR*aZdR*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       2*aAI*aZI*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       2*aAR*aZR*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAdI*aZdI*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) - 4*aAdR*aZdR*gL*gR*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) + 
       4*aAI*aZI*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) + 4*aAR*aZR*gL*gR*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gL*gL)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gL*gL)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gL*gL)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gL*gL)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gR*gR)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gR*gR)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) - 
       2*((gL+gR)*(gL+gR))*((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*
           (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
          (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
           ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
          (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*(wZ*wZ))*
        (C34*C34)*(C56*C56) - 
       2*aAI*ahI*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*
        C36 - 2*aAR*ahR*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       2*aAR*ahI*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahR*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36 - 
       2*aAR*ahI*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahR*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahI*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAR*ahR*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahI*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAR*ahR*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       4*aAR*ahI*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       4*aAI*ahR*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C45*C45)*C36 + 
       2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C45*C45)*C36 - 
       2*aAI*ahI*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        C45 - 2*aAR*ahR*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       2*aAR*ahI*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahR*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45 - 
       2*aAR*ahI*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahR*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahI*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAR*ahR*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahI*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAR*ahR*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       4*aAR*ahI*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 - 
       4*aAI*ahR*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 - 
       2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 - 
       2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C36*C36)*C45 + 
       2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C36*C36)*C45 + 
       aAdR*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + aAI*ahI*(gL*gL)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       aAdI*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + aAR*ahR*(gL*gL)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       aAdR*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + aAI*ahI*(gR*gR)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 + 
       aAdI*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + aAR*ahR*(gR*gR)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       aAdI*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + aAR*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - aAdR*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAI*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + aAdI*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 + aAR*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       aAdR*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 - aAI*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - aAdI*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       aAR*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 - aAdR*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*
        C45*C46 - aAI*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       aAdI*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 + aAR*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*
        C45*C46 + aAdR*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAI*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 - aAdR*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAI*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 + 
       aAdI*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - aAR*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAdR*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAI*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - aAdI*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAR*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAdR*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - aAI*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAdI*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAR*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 + aAdR*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAI*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAdI*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - aAR*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 2*aAdI*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 2*aAR*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 2*aAdR*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 2*aAI*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 2*aAdI*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 2*aAR*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 2*aAdR*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 2*aAI*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        C36*C45*C46 - 
       aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*
        C46 + aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*
        C45*C46 - aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        C36*C45*C46 + 
       aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*
        C46 - aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*
        C45*C46 - aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        C36*C45*C46 - 
       aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*
        C46 + C34*(-4*gL*gR*
           ((aAdI*aZdI + aAdR*aZdR + aAI*aZI + aAR*aZR)*(M1 - MZ)*
              (M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (aAdR*aZdI - aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAdI*aZdI + aAdR*aZdR + aAI*aZI + aAR*aZR)*(MZ*MZ)*
              (wZ*wZ))*(C36*C36) - 
          4*gL*gR*((aAdI*aZdI + aAdR*aZdR + aAI*aZI + aAR*aZR)*
              (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (aAdR*aZdI - aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAdI*aZdI + aAdR*aZdR + aAI*aZI + aAR*aZR)*(MZ*MZ)*
              (wZ*wZ))*(C45*C45) - 
          2*gL*gR*(MZ*MZ)*((aAI*ahI + aAR*ahR)*(M1 - MZ)*(M2 - MZ)*
              (M1 + MZ)*(M2 + MZ) + 
             (aAR*ahI - aAI*ahR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAI*ahI + aAR*ahR)*(MZ*MZ)*(wZ*wZ))*C45 - 
          2*C36*(gL*gR*(MZ*MZ)*
              ((aAI*ahI + aAR*ahR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + 
                (aAR*ahI - aAI*ahR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAI*ahI + aAR*ahR)*(MZ*MZ)*(wZ*wZ)) - 
             2*((gL*gL) + (gR*gR))*
              ((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*
                 (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*
                 (wZ*wZ))*C45) + 
          C46*((MZ*MZ)*
              (-(aAdR*(gL - gR)*(gL + gR)*
                   (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                     ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                     ahI*(MZ*MZ)*(wZ*wZ))) + 
                aAI*((gL*gL) + (gR*gR))*
                 (ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   ahI*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                   ahI*(MZ*MZ)*(wZ*wZ)) + 
                ((aAdI - aAR)*(gL*gL) - (aAdI + aAR)*(gR*gR))*
                 (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahR*(MZ*MZ)*(wZ*wZ))) + 
             2*(-(aAdI*aZdI*(gL*gL)*(M1*M1)*(M2*M2)) + 
                aAR*aZdI*(gL*gL)*(M1*M1)*(M2*M2) + 
                aAdI*aZR*(gL*gL)*(M1*M1)*(M2*M2) - 
                aAR*aZR*(gL*gL)*(M1*M1)*(M2*M2) - 
                aAdI*aZdI*(gR*gR)*(M1*M1)*(M2*M2) - 
                aAR*aZdI*(gR*gR)*(M1*M1)*(M2*M2) - 
                aAdI*aZR*(gR*gR)*(M1*M1)*(M2*M2) - 
                aAR*aZR*(gR*gR)*(M1*M1)*(M2*M2) + 
                MZ*wZ*((aAdI - aAR)*(aZdR + aZI)*(gL*gL) - 
                   (aAdI + aAR)*(-aZdR + aZI)*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                aAdI*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ) - 
                aAR*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ) - 
                aAdI*aZR*(gL*gL)*(M1*M1)*(MZ*MZ) + 
                aAR*aZR*(gL*gL)*(M1*M1)*(MZ*MZ) + 
                aAdI*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                aAR*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                aAdI*aZR*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                aAR*aZR*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                aAdI*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ) - 
                aAR*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ) - 
                aAdI*aZR*(gL*gL)*(M2*M2)*(MZ*MZ) + 
                aAR*aZR*(gL*gL)*(M2*M2)*(MZ*MZ) + 
                aAdI*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ) + 
                aAR*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ) + 
                aAdI*aZR*(gR*gR)*(M2*M2)*(MZ*MZ) + 
                aAR*aZR*(gR*gR)*(M2*M2)*(MZ*MZ) - 
                aAdI*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ) + 
                aAR*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ) + 
                aAdI*aZR*(gL*gL)*(MZ*MZ*MZ*MZ) - 
                aAR*aZR*(gL*gL)*(MZ*MZ*MZ*MZ) - 
                aAdI*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ) - 
                aAR*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ) - 
                aAdI*aZR*(gR*gR)*(MZ*MZ*MZ*MZ) - 
                aAR*aZR*(gR*gR)*(MZ*MZ*MZ*MZ) + 
                ((-aAdI + aAR)*(-aZdI + aZR)*(gL*gL) + 
                   (aAdI + aAR)*(aZdI + aZR)*(gR*gR))*(MZ*MZ)*
                 (wZ*wZ) + aAdR*
                 (MZ*wZ*((-aZdI + aZR)*(gL*gL) - 
                      (aZdI + aZR)*(gR*gR))*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   (M1 - MZ)*(M1 + MZ)*
                    ((aZdR + aZI)*(gL*gL) + (aZdR - aZI)*(gR*gR))*
                    (-(M2*M2) + (MZ*MZ)) + 
                   ((aZdR + aZI)*(gL*gL) + (aZdR - aZI)*(gR*gR))*
                    (MZ*MZ)*(wZ*wZ)) + 
                aAI*(MZ*wZ*((-aZdI + aZR)*(gL*gL) + 
                      (aZdI + aZR)*(gR*gR))*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   (M1 - MZ)*(M1 + MZ)*
                    ((aZdR + aZI)*(gL*gL) + (-aZdR + aZI)*(gR*gR))*
                    (-(M2*M2) + (MZ*MZ)) + 
                   ((aZdR + aZI)*(gL*gL) + (-aZdR + aZI)*(gR*gR))*
                    (MZ*MZ)*(wZ*wZ)))*C46))*C56 + 
       E3456*(-2*aAdI*ahI*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C45 - 2*aAdR*ahR*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C45 - 2*aAdR*ahI*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          2*aAdI*ahR*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          2*aAdR*ahI*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          2*aAdI*ahR*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          2*aAdI*ahI*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          2*aAdR*ahR*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          2*aAdI*ahI*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          2*aAdR*ahR*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          4*aAdR*ahI*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*C45 - 
          4*aAdI*ahR*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*C45 - 
          2*aAdI*ahI*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 - 
          2*aAdR*ahR*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 + 
          2*aAdI*ahI*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C45 + 
          2*aAdR*ahR*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C45 - 
          2*C36*(gL*gR*(MZ*MZ)*
              ((aAdI*ahI + aAdR*ahR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + (aAdR*ahI - aAdI*ahR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAdI*ahI + aAdR*ahR)*(MZ*MZ)*(wZ*wZ)) + 
             ((gL+gR)*(gL+gR))*((aAI*aZdI + aAR*aZdR + aAdI*aZI + 
                   aAdR*aZR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (aAR*aZdI - aAI*aZdR + aAdR*aZI - aAdI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*(MZ*MZ)*
                 (wZ*wZ))*C45) + 
          aAdI*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          aAR*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAdR*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAI*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAdI*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAR*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAdR*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          aAI*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAdR*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          aAI*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          aAR*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          aAdR*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          aAI*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          aAR*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          aAdR*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          aAI*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          aAR*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          aAdR*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAI*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAR*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 + 
          aAR*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdR*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAI*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAR*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdR*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 + 
          aAI*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          aAR*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdR*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAI*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAR*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdR*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          aAI*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          2*aAdR*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 - 
          2*aAI*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          2*aAdI*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 - 
          2*aAR*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 - 
          2*aAdR*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          2*aAI*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          2*aAdI*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          2*aAR*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAdI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 - 
          aAR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAdR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAdI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAdR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 - 
          aAI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 + 
          aAR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAdR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAdI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAdR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 + 
          aAI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 + 
          C35*((MZ*MZ)*
              (aAR*(gL - gR)*(gL + gR)*
                 (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahI*(MZ*MZ)*(wZ*wZ)) + 
                aAdI*((gL*gL) + (gR*gR))*
                 (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahI*(MZ*MZ)*(wZ*wZ)) + 
                ((aAdR - aAI)*(gL*gL) + (aAdR + aAI)*(gR*gR))*
                 (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahR*(MZ*MZ)*(wZ*wZ))) + 
             2*((gL+gR)*(gL+gR))*
              ((aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*(M1 - MZ)*
                 (M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (aAR*aZdI - aAI*aZdR + aAdR*aZI - aAdI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*(MZ*MZ)*
                 (wZ*wZ))*C46) + 
          2*((gL-gR)*(gL-gR))*((aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*
              (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (aAR*aZdI - aAI*aZdR + aAdR*aZI - aAdI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*(MZ*MZ)*
              (wZ*wZ))*C34*C56) + 
       (C35*C35)*(-2*((gL+gR)*(gL+gR))*
           ((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*(M1 - MZ)*
              (M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
             (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*
              (wZ*wZ))*(C46*C46) + 
          (MZ*MZ)*(aAdR*(gL - gR)*(gL + gR)*
              (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                ahI*(MZ*MZ)*(wZ*wZ)) + 
             aAI*((gL*gL) + (gR*gR))*
              (ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                ahI*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                ahI*(MZ*MZ)*(wZ*wZ)) - 
             ((aAdI + aAR)*(gL*gL) + (-aAdI + aAR)*(gR*gR))*
              (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                ahR*(MZ*MZ)*(wZ*wZ)))*C46 + 
          2*(-(aAdI*aZdI*(gL*gL)*(M1*M1)*(M2*M2)) - 
             aAR*aZdI*(gL*gL)*(M1*M1)*(M2*M2) - 
             aAdI*aZR*(gL*gL)*(M1*M1)*(M2*M2) - 
             aAR*aZR*(gL*gL)*(M1*M1)*(M2*M2) - 
             aAdI*aZdI*(gR*gR)*(M1*M1)*(M2*M2) + 
             aAR*aZdI*(gR*gR)*(M1*M1)*(M2*M2) + 
             aAdI*aZR*(gR*gR)*(M1*M1)*(M2*M2) - 
             aAR*aZR*(gR*gR)*(M1*M1)*(M2*M2) - 
             MZ*wZ*((aAdI + aAR)*(-aZdR + aZI)*(gL*gL) - 
                (aAdI - aAR)*(aZdR + aZI)*(gR*gR))*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
             aAdI*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             aAR*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             aAdI*aZR*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             aAR*aZR*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             aAdI*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ) - 
             aAR*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ) - 
             aAdI*aZR*(gR*gR)*(M1*M1)*(MZ*MZ) + 
             aAR*aZR*(gR*gR)*(M1*M1)*(MZ*MZ) + 
             aAdI*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             aAR*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             aAdI*aZR*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             aAR*aZR*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             aAdI*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             aAR*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             aAdI*aZR*(gR*gR)*(M2*M2)*(MZ*MZ) + 
             aAR*aZR*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             aAdI*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ) - 
             aAR*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ) - 
             aAdI*aZR*(gL*gL)*(MZ*MZ*MZ*MZ) - aAR*aZR*(gL*gL)*(MZ*MZ*MZ*MZ) - 
             aAdI*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             aAR*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             aAdI*aZR*(gR*gR)*(MZ*MZ*MZ*MZ) - aAR*aZR*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             ((aAdI + aAR)*(aZdI + aZR)*(gL*gL) - 
                (aAdI - aAR)*(-aZdI + aZR)*(gR*gR))*(MZ*MZ)*(wZ*wZ) \
+ aAdR*((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ)*
                 ((-aZdR + aZI)*(gL*gL) - (aZdR + aZI)*(gR*gR)) - 
                MZ*wZ*((aZdI + aZR)*(gL*gL) + (aZdI - aZR)*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                ((aZdR - aZI)*(gL*gL) + (aZdR + aZI)*(gR*gR))*
                 (MZ*MZ)*(wZ*wZ)) + 
             aAI*(MZ*wZ*((aZdI + aZR)*(gL*gL) + 
                   (-aZdI + aZR)*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (M1 - MZ)*(M1 + MZ)*
                 ((-aZdR + aZI)*(gL*gL) + (aZdR + aZI)*(gR*gR))*
                 (-(M2*M2) + (MZ*MZ)) + 
                ((-aZdR + aZI)*(gL*gL) + (aZdR + aZI)*(gR*gR))*
                 (MZ*MZ)*(wZ*wZ)))*C34*C56) + 
       C35*(-(aAdR*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
             (C46*C46)) - 
          aAI*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + aAdI*ahR*(gL*gL)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          aAR*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          aAI*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) - aAdI*ahR*(gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          aAR*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + aAdI*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) - aAR*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) + aAI*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) - aAR*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) + aAI*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) + aAdI*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) - aAR*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) + aAI*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) - aAR*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) + aAI*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAI*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAR*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAI*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdI*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAR*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAI*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAR*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAI*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdI*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAR*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - 2*aAdI*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + 2*aAR*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - 2*aAdR*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - 2*aAI*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + 2*aAdI*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + 2*aAR*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + 2*aAdR*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - 2*aAI*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) - aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) - aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + 2*gL*gR*(MZ*MZ)*
           ((aAI*ahI + aAR*ahR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (aAR*ahI - aAI*ahR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAI*ahI + aAR*ahR)*(MZ*MZ)*(wZ*wZ))*C45*C46 - 
          C36*(-2*gL*gR*(MZ*MZ)*
              ((aAI*ahI + aAR*ahR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + (aAR*ahI - aAI*ahR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAI*ahI + aAR*ahR)*(MZ*MZ)*(wZ*wZ))*C46 + 
             C45*((MZ*MZ)*
                 (aAdR*(gL - gR)*(gL + gR)*
                    (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                      ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                      ahI*(MZ*MZ)*(wZ*wZ)) + 
                   aAI*((gL*gL) + (gR*gR))*
                    (ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                      ahI*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                      ahI*(MZ*MZ)*(wZ*wZ)) - 
                   ((aAdI + aAR)*(gL*gL) + (-aAdI + aAR)*(gR*gR))*
                    (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                      ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                      ahR*(MZ*MZ)*(wZ*wZ))) - 
                4*((gL+gR)*(gL+gR))*
                 ((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*
                    (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*
                    (wZ*wZ))*C46)) + 
          C34*((MZ*MZ)*
              (aAdR*(gL - gR)*(gL + gR)*
                 (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahI*(MZ*MZ)*(wZ*wZ)) + 
                aAI*((gL*gL) + (gR*gR))*
                 (ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   ahI*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                   ahI*(MZ*MZ)*(wZ*wZ)) - 
                ((aAdI + aAR)*(gL*gL) + (-aAdI + aAR)*(gR*gR))*
                 (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahR*(MZ*MZ)*(wZ*wZ))) + 
             8*gL*gR*((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*
                 (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*
                 (wZ*wZ))*C46)*C56)))/8192. + 
  (pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)) - 
       (aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46) + 
       (aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46) + 
       (aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46) - 
       2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) - 
       2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) + 
       2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) + 
       2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) - 
       (aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46) - 
       (aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46) + 
       (aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46) + 
       (aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46) + 
       (-(aZdI*aZdI) - (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*
        ((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56) - 
       ahR*aZdI*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35 + 
       ahI*aZdR*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35 + 
       ahI*aZI*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35 + 
       ahR*aZR*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35 + 
       ahR*aZdI*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35 - 
       ahI*aZdR*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35 + 
       ahI*aZI*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35 + 
       ahR*aZR*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35 + 
       ahR*aZdI*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 - 
       ahI*aZdR*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 + 
       ahI*aZI*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 + 
       ahR*aZR*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 - 
       ahR*aZdI*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       ahI*aZdR*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       ahI*aZI*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       ahR*aZR*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       (ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       (ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       (ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       (ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46 - 
       2*ahI*aZI*(gL*gL)*(gR*gR)*(MZ*MZ)*C35*C45*
        C46 - 2*ahR*aZR*(gL*gL)*(gR*gR)*(MZ*MZ)*C35*
        C45*C46 + C34*
        (((((aZdR-aZI)*(aZdR-aZI)) + ((aZdI+aZR)*(aZdI+aZR)))*(gL*gL*gL*gL) + 
             (((aZdR+aZI)*(aZdR+aZI)) + ((aZdI-aZR)*(aZdI-aZR)))*(gR*gR*gR*gR))*
           (C35*C35) + ((((aZdR+aZI)*(aZdR+aZI)) + ((aZdI-aZR)*(aZdI-aZR)))*
              (gL*gL*gL*gL) + (((aZdR-aZI)*(aZdR-aZI)) + ((aZdI+aZR)*(aZdI+aZR)))*
              (gR*gR*gR*gR))*(C46*C46) + 
          2*(gL*gL)*(gR*gR)*C45*
           ((ahI*aZI + ahR*aZR)*(MZ*MZ) + 
             ((aZdI*aZdI) + (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*
              C45) + ((ahI*(aZdR + aZI) + ahR*(-aZdI + aZR))*
              (gL*gL*gL*gL) + (ahI*(-aZdR + aZI) + ahR*(aZdI + aZR))*
              (gR*gR*gR*gR))*(MZ*MZ)*C46 + 
          C35*(((ahI*(-aZdR + aZI) + ahR*(aZdI + aZR))*(gL*gL*gL*gL) + 
                (ahI*(aZdR + aZI) + ahR*(-aZdI + aZR))*(gR*gR*gR*gR))*
              (MZ*MZ) + 4*((aZdI*aZdI) + (aZdR*aZdR) - (aZI*aZI) - 
                (aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56 + 
       (C36*C36)*((-(aZdI*aZdI) - (aZdR*aZdR) + (aZI*aZI) + 
             (aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45) + 
          2*(ahI*aZI + ahR*aZR)*(gL*gL)*(gR*gR)*(MZ*MZ)*C45 + 
          2*((aZdI*aZdI) + (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*(gL*gL)*
           (gR*gR)*C34*C56) + 
       E3456*(2*C36*
           ((ahI*aZdI + ahR*aZdR)*(gL*gL)*(gR*gR)*(MZ*MZ) + 
             (aZdI*aZI + aZdR*aZR)*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C45) \
+ (MZ*MZ)*(2*(ahI*aZdI + ahR*aZdR)*(gL*gL)*(gR*gR)*C45 - 
             ((ahR*(aZdR + aZI) + ahI*(aZdI - aZR))*(gL*gL*gL*gL) + 
                (ahR*(aZdR - aZI) + ahI*(aZdI + aZR))*(gR*gR*gR*gR))*C46) \
+ C35*(((ahR*(-aZdR + aZI) - ahI*(aZdI + aZR))*(gL*gL*gL*gL) - 
                (ahR*(aZdR + aZI) + ahI*(aZdI - aZR))*(gR*gR*gR*gR))*(MZ*MZ) \
- 2*(aZdI*aZI + aZdR*aZR)*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46) - 
          2*(aZdI*aZI + aZdR*aZR)*((gL*gL-gR*gR)*(gL*gL-gR*gR))*C34*
           C56) + C36*
        (2*(ahI*aZI + ahR*aZR)*(gL*gL)*(gR*gR)*(MZ*MZ)*
           (C45*C45) + 2*(ahI*aZI + ahR*aZR)*(gL*gL)*(gR*gR)*
           (MZ*MZ)*(-(C35*C46) + C34*C56) + 
          C45*(2*((ahI*ahI) + (ahR*ahR))*(gL*gL)*(gR*gR)*
              (MZ*MZ*MZ*MZ) - ((ahI*(aZdR + aZI) + ahR*(-aZdI + aZR))*
                 (gL*gL*gL*gL) + (ahI*(-aZdR + aZI) + ahR*(aZdI + aZR))*
                 (gR*gR*gR*gR))*(MZ*MZ)*C46 + 
             C35*((-((ahI*(-aZdR + aZI) + ahR*(aZdI + aZR))*
                      (gL*gL*gL*gL)) - 
                   (ahI*(aZdR + aZI) + ahR*(-aZdI + aZR))*(gR*gR*gR*gR))*
                 (MZ*MZ) - 2*
                 (-(aZdI*aZdI) - (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*
                 ((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46) - 
             2*(-(aZdI*aZdI) - (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*
              ((gL*gL*gL*gL) + (gR*gR*gR*gR))*C34*C56))))/8192.;
}



double GetHyp1GeneralScalar(LeptonVectors &leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double MH = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass();
   const double Mq = MH;
   const double s = MH * MH;
   const double x = (M1 * M1 - M2 * M2) / s;
   const double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   const double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   const double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   const double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(Reverse == true)
      swap(P1, P2);
   
   /*
   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }
   */

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C16 = P1 * P6;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C26 = P2 * P6;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1236 = EPS(P1, P2, P3, P6);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1246 = EPS(P1, P2, P4, P6);
   double E1256 = EPS(P1, P2, P5, P6);
   double E1345 = EPS(P1, P3, P4, P5);
   double E1346 = EPS(P1, P3, P4, P6);
   double E1356 = EPS(P1, P3, P5, P6);
   double E1456 = EPS(P1, P4, P5, P6);
   double E2345 = EPS(P2, P3, P4, P5);
   double E2346 = EPS(P2, P3, P4, P6);
   double E2356 = EPS(P2, P3, P5, P6);
   double E2456 = EPS(P2, P4, P5, P6);
   double E3456 = EPS(P3, P4, P5, P6);

   double vh = CONST_VH;

return (pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (8*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)*C36*C45 + 
       4*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       4*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46))/8192. + 
  ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (0.000128*(C34*C34)*(C56*C56) - 
       2*(C36*C45 - C35*C46)*
        (0. - 0.000064*(C36*C45 - C35*C46)) + 
       C34*(0.000064*(C35*C35) + 0.000064*(C36*C36) + 
          0.000064*((C45*C45) + (C46*C46)) - 
          0.000128*C36*C45 - 0.000128*C35*C46)*
        C56))/4096. - (el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*
     pow(vh,-2)*pow((1.0/(s*s))*
       ((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + ((M2*M2-s)*(M2*M2-s))),
      0.5)*(1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.056*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       0.056*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*
        C36 + 0.028*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       0.028*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       0.028*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       0.028*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       0.056*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        C45 - 0.056*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 + 
       0.028*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       0.028*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       0.028*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       0.028*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       0.056*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*
        C46 + 0.056*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        C36*C45*C46 - 
       0.028*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.028*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.028*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.028*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       (C35*C35)*(0. + (-0.014*(gL*gL*gL) - 0.014*(gR*gR*gR))*
           (MZ*MZ)*(4*(M1*M1)*(M2*M2) - 
             2*((M1*M1) + (M2*M2))*(MZ*MZ))*C46) + 
       E3456*(0. + (0. - 
             0.028*wZ*((gL*gL*gL) - (gR*gR*gR))*((M1*M1) + (M2*M2))*
              (MZ*MZ*MZ))*C35 + 
          (0. + gL*(gL - gR)*gR*(M1 - M2)*(M1 + M2)*(0. + 0.028*wZ)*
              (MZ*MZ*MZ))*C36 - 
          0.028*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          0.028*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          0.028*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          0.028*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          0.028*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          0.028*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          0.028*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          0.028*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46) + 
       C34*(0. + (0. - 
             0.014*gL*gR*(gL + gR)*(MZ*MZ)*
              (4*(M1*M1)*(M2*M2) - 
                2*((M1*M1) + (M2*M2))*(MZ*MZ)))*C36 - 
          0.014*gL*gR*(gL + gR)*(MZ*MZ)*
           (4*(M1*M1)*(M2*M2) - 2*((M1*M1) + (M2*M2))*(MZ*MZ))*
           C45 + (0. + (-0.014*(gL*gL*gL) - 0.014*(gR*gR*gR))*
              (MZ*MZ)*(4*(M1*M1)*(M2*M2) - 
                2*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46)*C56 \
- C35*(0. + 0.056*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 0.056*(gR*gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          0.028*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.028*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.028*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.028*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.014*gL*gR*(gL + gR)*(MZ*MZ)*
           (4*(M1*M1)*(M2*M2) - 2*((M1*M1) + (M2*M2))*(MZ*MZ))*
           C45*C46 + 
          C36*((0. + (-0.014*(gL*gL*gL) - 0.014*(gR*gR*gR))*
                 (MZ*MZ)*(4*(M1*M1)*(M2*M2) - 
                   2*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45 - 
             0.014*gL*gR*(gL + gR)*(MZ*MZ)*
              (4*(M1*M1)*(M2*M2) - 
                2*((M1*M1) + (M2*M2))*(MZ*MZ))*C46) - 
          (0. + (-0.014*(gL*gL*gL) - 0.014*(gR*gR*gR))*(MZ*MZ)*
              (4*(M1*M1)*(M2*M2) - 2*((M1*M1) + (M2*M2))*(MZ*MZ))\
)*C34*C56)))/8192. + 
  ((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.000448*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 0.000448*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       0.0006720000000000001*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0006720000000000001*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0006720000000000001*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0006720000000000001*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.000224*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       0.000224*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       0.000896*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.000896*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.000224*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       0.000224*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) + 
       0.000224*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) + 
       0.000224*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) + 
       0.000224*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) + 
       0.000224*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       0.000224*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 0.000224*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.000224*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 0.000224*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.000224*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 0.000224*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.000224*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 0.000224*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(gL + gR)*(0. + 0.000224*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          0.00033600000000000004*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          0.00033600000000000004*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          0.000112*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          0.000448*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          0.000112*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 0.000112*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          0.000112*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.000112*(MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
        (C34*C34)*(C56*C56) + 
       C34*((0. - 0.000224*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.000224*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.00033600000000000004*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.000112*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.000112*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.000448*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000448*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000112*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.000112*(gL + gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C35*C35) + 
          (0. - 0.000224*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.000224*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.00033600000000000004*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.000112*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.000112*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.000448*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000448*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000112*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.000112*(gL + gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C45*C45) + 
          (0. - 0.000224*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.000224*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.00033600000000000004*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.000112*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.000112*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.000448*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000448*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000112*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (0.000112*gL + 0.000112*gR)*(MZ*MZ)*
              (-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C46*C46) + 
          2*(gL + gR)*(0. + 0.000224*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.00033600000000000004*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.00033600000000000004*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.000112*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.000448*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000112*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.000112*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*C35*
           C46)*C56 + 
       2*(gL + gR)*(0. + 0.000224*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          0.00033600000000000004*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          0.00033600000000000004*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          0.000112*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          0.000448*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          0.000112*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 0.000112*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          0.000112*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.000112*(MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*C36*
        C45*(2*C35*C46 + C34*C56) + 
       (C36*C36)*(-2*(gL + gR)*
           (0. + 0.000224*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.00033600000000000004*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.00033600000000000004*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.000112*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.000448*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000112*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.000112*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
              (wZ*wZ))*(C45*C45) + 
          (0. - 0.000224*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.000224*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.00033600000000000004*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.00033600000000000004*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.000112*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.000112*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.000448*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000448*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.000112*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000112*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.000112*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.000112*(gL + gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
              (wZ*wZ))*C34*C56)))/4096. - 
  ((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.032*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*
        C36 - 0.032*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 - 0.032*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.032*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       0.032*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C45*C45)*C36 + 
       0.032*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        C45 - 0.032*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 - 0.032*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.032*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 - 
       0.032*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C36*C36)*C45 - 
       0.016*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*
        C46 - 0.016*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        C36*C45*C46 + 
       0.016*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       0.016*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       0.016*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       0.016*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.016*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.016*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       0.016*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46 + 
       0.016*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46 + 
       E3456*(0. + (0. + 
             0.016*(gL - gR)*(gL + gR)*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ))*(MZ*MZ*MZ))*C35 - 
          0.016*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          0.016*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          0.016*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          0.016*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          0.032*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 - 
          0.032*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46) + 
       (C35*C35)*(0. - (-0.008*(gL*gL) - 0.008*(gR*gR))*
           (MZ*MZ)*(2*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             2*(MZ*MZ)*(wZ*wZ))*C46) + 
       C34*(0. - 2*(0. + 
             gL*gR*(MZ*MZ)*
              (0. - 0.016*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                0.016*(MZ*MZ)*(wZ*wZ)))*C36 - 
          2*gL*gR*(MZ*MZ)*(0. - 
             0.016*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             0.016*(MZ*MZ)*(wZ*wZ))*C45 + 
          (0. + (0.008*(gL*gL) + 0.008*(gR*gR))*(MZ*MZ)*
              (2*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                2*(MZ*MZ)*(wZ*wZ)))*C46)*C56 + 
       C35*(0. + 0.016*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 0.016*(gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          0.016*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.016*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.016*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.016*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.016*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.016*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.016*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46) - 
          0.016*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46) + 
          2*gL*gR*(MZ*MZ)*(0. - 
             0.016*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             0.016*(MZ*MZ)*(wZ*wZ))*C45*C46 - 
          C36*((0. - (-0.008*(gL*gL) - 0.008*(gR*gR))*
                 (MZ*MZ)*(2*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   2*(MZ*MZ)*(wZ*wZ)))*C45 - 
             2*gL*gR*(MZ*MZ)*
              (0. - 0.016*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                0.016*(MZ*MZ)*(wZ*wZ))*C46) + 
          (0. - (-0.008*(gL*gL) - 0.008*(gR*gR))*(MZ*MZ)*
              (2*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                2*(MZ*MZ)*(wZ*wZ)))*C34*C56)))/8192. + 
  ((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.0007840000000000001*gL*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 0.0011760000000000002*(gL*gL)*(M1*M1*M1*M1)*
        (M2*M2*M2*M2)*(C35*C35)*(C46*C46) + 
       0.0011760000000000002*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 0.0007840000000000001*gL*gR*(M1*M1*M1*M1)*(M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) - 
       0.0011760000000000002*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0011760000000000002*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0007840000000000001*gL*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0011760000000000002*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0011760000000000002*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0007840000000000001*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0007840000000000001*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (wZ*wZ)*(C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (wZ*wZ)*(C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.00039200000000000004*(2*gL*gR*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + (MZ*MZ)*(wZ*wZ)) \
+ (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                (MZ*MZ)*(wZ*wZ))) + 
          (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                (MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56) + 
       C34*((0.00019600000000000002*(gL*gL) + 
             0.00019600000000000002*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C35*C35) + 
          (0. + 0.00019600000000000002*
              (4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*(C45*C45) \
+ (0.00019600000000000002*(gL*gL) + 0.00019600000000000002*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C46*C46) - 
          0.00039200000000000004*
           (4*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46)*
        C56 + (C36*C36)*
        (0.00039200000000000004*
           (2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*(C45*C45) + 
          (0. + 0.00019600000000000002*
              (4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*C34*
           C56) - 0.00039200000000000004*C36*C45*
        (2*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 + 
          ((gL*gL) + (gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + ((M1*M1) + (M2*M2))*(MZ*MZ),
              2))*C34*C56)))/8192.;
}


double GetHyp2GeneralScalar(LeptonVectors &leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double MH = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass();
   const double Mq = MH;
   const double s = MH * MH;
   const double x = (M1 * M1 - M2 * M2) / s;
   const double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   const double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   const double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   const double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(Reverse == true)
      swap(P1, P2);
   
   /*
   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }
   */

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C16 = P1 * P6;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C26 = P2 * P6;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1236 = EPS(P1, P2, P3, P6);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1246 = EPS(P1, P2, P4, P6);
   double E1256 = EPS(P1, P2, P5, P6);
   double E1345 = EPS(P1, P3, P4, P5);
   double E1346 = EPS(P1, P3, P4, P6);
   double E1356 = EPS(P1, P3, P5, P6);
   double E1456 = EPS(P1, P4, P5, P6);
   double E2345 = EPS(P2, P3, P4, P5);
   double E2346 = EPS(P2, P3, P4, P6);
   double E2356 = EPS(P2, P3, P5, P6);
   double E2456 = EPS(P2, P4, P5, P6);
   double E3456 = EPS(P3, P4, P5, P6);

   double vh = CONST_VH;
   
   return (pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (8*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)*C36*C45 + 
       4*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       4*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46))/8192. + 
  ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (0.00021632000000000004*(C34*C34)*(C56*C56) - 
       2*(C36*C45 - C35*C46)*
        (0. - 0.00010816000000000002*
           (C36*C45 - C35*C46)) + 
       C34*(0.00010816000000000002*(C35*C35) + 
          0.00010816000000000002*(C36*C36) + 
          0.00010816000000000002*((C45*C45) + (C46*C46)) - 
          0.00021632000000000004*C36*C45 - 
          0.00021632000000000004*C35*C46)*C56))/4096. - 
  (el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.28*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       0.28*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*
        C36 + 0.14*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.14*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.14*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.14*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 - 0.28*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       0.28*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        C45 + 0.14*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.14*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.14*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.14*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.28*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + 0.28*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        C36*C45*C46 - 
       0.14*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.14*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.14*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.14*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       (C35*C35)*(0. + (-0.07*(gL*gL*gL) - 0.07*(gR*gR*gR))*(MZ*MZ)*
           (4*(M1*M1)*(M2*M2) - 2*((M1*M1) + (M2*M2))*(MZ*MZ))*
           C46) + E3456*
        (0. + (0. - 0.14*wZ*((gL*gL*gL) - (gR*gR*gR))*
              ((M1*M1) + (M2*M2))*(MZ*MZ*MZ))*C35 + 
          (0. + gL*(gL - gR)*gR*(M1 - M2)*(M1 + M2)*(0. + 0.14*wZ)*
              (MZ*MZ*MZ))*C36 - 
          0.14*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          0.14*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          0.14*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          0.14*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          0.14*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          0.14*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          0.14*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          0.14*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46) + 
       C34*(0. + (0. - 
             0.07*gL*gR*(gL + gR)*(MZ*MZ)*
              (4*(M1*M1)*(M2*M2) - 
                2*((M1*M1) + (M2*M2))*(MZ*MZ)))*C36 - 
          0.07*gL*gR*(gL + gR)*(MZ*MZ)*
           (4*(M1*M1)*(M2*M2) - 2*((M1*M1) + (M2*M2))*(MZ*MZ))*
           C45 + (0. + (-0.07*(gL*gL*gL) - 0.07*(gR*gR*gR))*
              (MZ*MZ)*(4*(M1*M1)*(M2*M2) - 
                2*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46)*C56 \
- C35*(0. + 0.28*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 0.28*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) - 0.14*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - 0.14*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - 0.14*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - 0.14*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - 0.07*gL*gR*(gL + gR)*(MZ*MZ)*
           (4*(M1*M1)*(M2*M2) - 2*((M1*M1) + (M2*M2))*(MZ*MZ))*
           C45*C46 + 
          C36*((0. + (-0.07*(gL*gL*gL) - 0.07*(gR*gR*gR))*(MZ*MZ)*
                 (4*(M1*M1)*(M2*M2) - 
                   2*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45 - 
             0.07*gL*gR*(gL + gR)*(MZ*MZ)*
              (4*(M1*M1)*(M2*M2) - 
                2*((M1*M1) + (M2*M2))*(MZ*MZ))*C46) - 
          (0. + (-0.07*(gL*gL*gL) - 0.07*(gR*gR*gR))*(MZ*MZ)*
              (4*(M1*M1)*(M2*M2) - 2*((M1*M1) + (M2*M2))*(MZ*MZ))\
)*C34*C56)))/8192. + 
  ((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.0029120000000000005*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 0.0029120000000000005*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       0.004368000000000001*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.004368000000000001*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.004368000000000001*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.004368000000000001*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0014560000000000003*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0014560000000000003*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.005824000000000001*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.005824000000000001*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0014560000000000003*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0014560000000000003*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0014560000000000003*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0014560000000000003*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0014560000000000003*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0014560000000000003*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0014560000000000003*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0014560000000000003*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0014560000000000003*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0014560000000000003*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0014560000000000003*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0014560000000000003*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0014560000000000003*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0014560000000000003*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(gL + gR)*(0. + 0.0014560000000000003*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          0.0021840000000000006*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          0.0021840000000000006*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          0.0007280000000000001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          0.0029120000000000005*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          0.0007280000000000001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
          0.0007280000000000001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          0.0007280000000000001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.0007280000000000001*(MZ*MZ)*
           ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
           (wZ*wZ))*(C34*C34)*(C56*C56) + 
       C34*((0. - 0.0014560000000000003*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0014560000000000003*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0021840000000000006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0007280000000000001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0029120000000000005*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0029120000000000005*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*(gL + gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C35*C35) + 
          (0. - 0.0014560000000000003*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0014560000000000003*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0021840000000000006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0007280000000000001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0029120000000000005*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0029120000000000005*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*(gL + gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C45*C45) + 
          (0. - 0.0014560000000000003*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0014560000000000003*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0021840000000000006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0007280000000000001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0029120000000000005*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0029120000000000005*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (0.0007280000000000001*gL + 0.0007280000000000001*gR)*
              (MZ*MZ)*(-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C46*C46) + 
          2*(gL + gR)*(0. + 0.0014560000000000003*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0021840000000000006*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0021840000000000006*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0007280000000000001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0029120000000000005*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*C35*
           C46)*C56 + 
       2*(gL + gR)*(0. + 0.0014560000000000003*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          0.0021840000000000006*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          0.0021840000000000006*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          0.0007280000000000001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          0.0029120000000000005*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          0.0007280000000000001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
          0.0007280000000000001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          0.0007280000000000001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.0007280000000000001*(MZ*MZ)*
           ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
           (wZ*wZ))*C36*C45*
        (2*C35*C46 + C34*C56) + 
       (C36*C36)*(-2*(gL + gR)*
           (0. + 0.0014560000000000003*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0021840000000000006*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0021840000000000006*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0007280000000000001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0029120000000000005*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
              (wZ*wZ))*(C45*C45) + 
          (0. - 0.0014560000000000003*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0014560000000000003*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0021840000000000006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0021840000000000006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0007280000000000001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0029120000000000005*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0029120000000000005*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0007280000000000001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0007280000000000001*(gL + gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
              (wZ*wZ))*C34*C56)))/4096. - 
  ((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.041600000000000005*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       0.041600000000000005*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 - 0.041600000000000005*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       0.041600000000000005*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       0.041600000000000005*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C45*C45)*
        C36 + 0.041600000000000005*gL*gR*(M1*M1)*(M2*M2)*
        (MZ*MZ)*(C36*C36)*C45 - 
       0.041600000000000005*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 - 0.041600000000000005*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       0.041600000000000005*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 - 
       0.041600000000000005*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C36*C36)*
        C45 - 0.020800000000000003*(gL*gL)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       0.020800000000000003*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        C36*C45*C46 + 
       0.020800000000000003*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 0.020800000000000003*(gR*gR)*(M1*M1)*
        (MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       0.020800000000000003*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 0.020800000000000003*(gR*gR)*(M2*M2)*
        (MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.020800000000000003*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*
        C46 - 0.020800000000000003*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 0.020800000000000003*(gL*gL)*(MZ*MZ*MZ*MZ)*
        (wZ*wZ)*C36*C45*C46 + 
       0.020800000000000003*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*
        C45*C46 + E3456*
        (0. + (0. + 0.020800000000000003*(gL - gR)*(gL + gR)*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ))*(MZ*MZ*MZ))*C35 - 
          0.020800000000000003*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           C46 + 0.020800000000000003*wZ*(gR*gR)*(M1*M1)*
           (MZ*MZ*MZ)*C46 - 
          0.020800000000000003*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
           C46 + 0.020800000000000003*wZ*(gR*gR)*(M2*M2)*
           (MZ*MZ*MZ)*C46 + 
          0.041600000000000005*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 - 
          0.041600000000000005*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46) + 
       (C35*C35)*(0. - (-0.010400000000000001*(gL*gL) - 
             0.010400000000000001*(gR*gR))*(MZ*MZ)*
           (2*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             2*(MZ*MZ)*(wZ*wZ))*C46) + 
       C34*(0. - 2*(0. + 
             gL*gR*(MZ*MZ)*
              (0. - 0.020800000000000003*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + 0.020800000000000003*(MZ*MZ)*(wZ*wZ)))*
           C36 - 2*gL*gR*(MZ*MZ)*
           (0. - 0.020800000000000003*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
              (M2 + MZ) + 0.020800000000000003*(MZ*MZ)*(wZ*wZ))*
           C45 + (0. + (0.010400000000000001*(gL*gL) + 
                0.010400000000000001*(gR*gR))*(MZ*MZ)*
              (2*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                2*(MZ*MZ)*(wZ*wZ)))*C46)*C56 + 
       C35*(0. + 0.020800000000000003*(gL*gL)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) + 
          0.020800000000000003*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) - 0.020800000000000003*(gL*gL)*(M1*M1)*
           (MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.020800000000000003*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - 0.020800000000000003*(gL*gL)*(M2*M2)*
           (MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.020800000000000003*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + 0.020800000000000003*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + 0.020800000000000003*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - 0.020800000000000003*(gL*gL)*(MZ*MZ*MZ*MZ)*
           (wZ*wZ)*(C46*C46) - 
          0.020800000000000003*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + 2*gL*gR*(MZ*MZ)*
           (0. - 0.020800000000000003*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
              (M2 + MZ) + 0.020800000000000003*(MZ*MZ)*(wZ*wZ))*
           C45*C46 - 
          C36*((0. - (-0.010400000000000001*(gL*gL) - 
                   0.010400000000000001*(gR*gR))*(MZ*MZ)*
                 (2*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   2*(MZ*MZ)*(wZ*wZ)))*C45 - 
             2*gL*gR*(MZ*MZ)*
              (0. - 0.020800000000000003*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + 0.020800000000000003*(MZ*MZ)*(wZ*wZ))*
              C46) + (0. - 
             (-0.010400000000000001*(gL*gL) - 
                0.010400000000000001*(gR*gR))*(MZ*MZ)*
              (2*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                2*(MZ*MZ)*(wZ*wZ)))*C34*C56)))/8192. + 
  ((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.019600000000000003*gL*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 0.029400000000000003*(gL*gL)*(M1*M1*M1*M1)*
        (M2*M2*M2*M2)*(C35*C35)*(C46*C46) + 
       0.029400000000000003*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 0.019600000000000003*gL*gR*(M1*M1*M1*M1)*(M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) - 
       0.029400000000000003*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.029400000000000003*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.019600000000000003*gL*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.029400000000000003*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.029400000000000003*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.009800000000000001*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.009800000000000001*(gR*gR)*(M1*M1*M1*M1)*
        (MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) + 
       0.019600000000000003*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.009800000000000001*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.009800000000000001*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.009800000000000001*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.009800000000000001*(gR*gR)*(M2*M2*M2*M2)*
        (MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) + 
       0.009800000000000001*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.009800000000000001*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.019600000000000003*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.009800000000000001*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (wZ*wZ)*(C35*C35)*(C46*C46) + 
       0.009800000000000001*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (wZ*wZ)*(C35*C35)*(C46*C46) + 
       0.009800000000000001*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.009800000000000001*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.009800000000000001*(2*gL*gR*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + (MZ*MZ)*(wZ*wZ)) \
+ (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                (MZ*MZ)*(wZ*wZ))) + 
          (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                (MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56) + 
       C34*((0.004900000000000001*(gL*gL) + 
             0.004900000000000001*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C35*C35) + 
          (0. + 0.004900000000000001*
              (4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*(C45*C45) \
+ (0.004900000000000001*(gL*gL) + 0.004900000000000001*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C46*C46) - 
          0.009800000000000001*
           (4*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46)*
        C56 + (C36*C36)*
        (0.009800000000000001*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*(C45*C45) + 
          (0. + 0.004900000000000001*
              (4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*C34*
           C56) - 0.009800000000000001*C36*C45*
        (2*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 + 
          ((gL*gL) + (gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + ((M1*M1) + (M2*M2))*(MZ*MZ),
              2))*C34*C56)))/8192.;
}


double GetHyp3GeneralScalar(LeptonVectors &leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double MH = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass();
   const double Mq = MH;
   const double s = MH * MH;
   const double x = (M1 * M1 - M2 * M2) / s;
   const double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   const double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   const double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   const double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(Reverse == true)
      swap(P1, P2);
   
   /*
   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }
   */

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C16 = P1 * P6;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C26 = P2 * P6;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1236 = EPS(P1, P2, P3, P6);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1246 = EPS(P1, P2, P4, P6);
   double E1256 = EPS(P1, P2, P5, P6);
   double E1345 = EPS(P1, P3, P4, P5);
   double E1346 = EPS(P1, P3, P4, P6);
   double E1356 = EPS(P1, P3, P5, P6);
   double E1456 = EPS(P1, P4, P5, P6);
   double E2345 = EPS(P2, P3, P4, P5);
   double E2346 = EPS(P2, P3, P4, P6);
   double E2356 = EPS(P2, P3, P5, P6);
   double E2456 = EPS(P2, P4, P5, P6);
   double E3456 = EPS(P3, P4, P5, P6);

   double vh = CONST_VH;
   
   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (-0.0002*(C34*C34)*(C56*C56) - 
       2*(C36*C45 - C35*C46)*
        (0. + 0.0001*(C36*C45 - C35*C46)) + 
       C34*(0.0001*(C35*C35) + 0.0001*(C36*C36) + 
          0.0001*((C45*C45) + (C46*C46)) + 
          0.0002*C36*C45 + 0.0002*C35*C46)*C56\
))/4096. + (pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (-((gL*gL*gL*gL)*(C35*C35)*(C46*C46)) - 
       2*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) - 
       (gR*gR*gR*gR)*(C35*C35)*(C46*C46) - 
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56) + 
       C34*(((gL*gL*gL*gL) + (gR*gR*gR*gR))*(C35*C35) + 
          2*(gL*gL)*(gR*gR)*(C45*C45) + 
          ((gL*gL*gL*gL) + (gR*gR*gR*gR))*(C46*C46) + 
          4*(gL*gL)*(gR*gR)*C35*C46)*C56 + 
       (C36*C36)*(-(((gL*gL+gR*gR)*(gL*gL+gR*gR))*
             (C45*C45)) + 2*(gL*gL)*(gR*gR)*C34*C56) \
+ C36*C45*(2*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C35*C46 + 
          2*((gL*gL*gL*gL) + (gR*gR*gR*gR))*C34*C56)))/8192. + 
  ((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.0004*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 0.0004*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 0.0006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0008*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0008*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 0.0002*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 0.0002*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 0.0002*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*(gL + gR)*
        (0. + 0.0002*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          0.0003*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          0.0003*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          0.0001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          0.0004*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          0.0001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 0.0001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          0.0001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.0001*(MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
        (C34*C34)*(C56*C56) + 
       C34*((0. + 0.0002*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0002*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0004*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (0.0001*gL + 0.0001*gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C35*C35) + 
          (0. + 0.0002*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0002*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0004*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(0. + 0.0001*gL*(M1*M1*M1*M1) + 
                0.0001*gR*(M1*M1*M1*M1) + 0.0001*gL*(M2*M2*M2*M2) + 
                0.0001*gR*(M2*M2*M2*M2) - 
                ((0.0001*gL + 0.0001*gR)*(M1*M1) + 
                   (0.0001*gL + 0.0001*gR)*(M2*M2))*(MZ*MZ))*
              (wZ*wZ))*(C45*C45) + 
          (0. + 0.0002*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0002*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0004*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (-0.0001*gL - 0.0001*gR)*(MZ*MZ)*
              (-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C46*C46) + 
          2*(gL + gR)*(0. + 0.0002*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 0.0001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0001*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*C35*
           C46)*C56 + 
       2*(gL + gR)*(0. + 0.0002*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          0.0003*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          0.0003*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          0.0001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          0.0004*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          0.0001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 0.0001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          0.0001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.0001*(MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*C36*
        C45*(2*C35*C46 + C34*C56) + 
       (C36*C36)*(-2*(gL + gR)*
           (0. + 0.0002*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 0.0001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0001*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
              (wZ*wZ))*(C45*C45) + 
          (0. + 0.0002*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0002*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0004*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(0. + 0.0001*gL*(M1*M1*M1*M1) + 0.0001*gR*(M1*M1*M1*M1) + 
                0.0001*gL*(M2*M2*M2*M2) + 0.0001*gR*(M2*M2*M2*M2) - 
                ((0.0001*gL + 0.0001*gR)*(M1*M1) + 
                   (0.0001*gL + 0.0001*gR)*(M2*M2))*(MZ*MZ))*(wZ*wZ))*
           C34*C56)))/4096. + 
  ((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.0004*gL*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 0.0006000000000000001*(gL*gL)*(M1*M1*M1*M1)*
        (M2*M2*M2*M2)*(C35*C35)*(C46*C46) - 
       0.0006000000000000001*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       0.0004*gL*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0006000000000000001*(gL*gL)*(M1*M1*M1*M1)*
        (M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46) + 
       0.0006000000000000001*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0004*gL*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0006000000000000001*(gL*gL)*(M1*M1)*
        (M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46) + 
       0.0006000000000000001*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0004*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 0.0004*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (wZ*wZ)*(C35*C35)*(C46*C46) - 
       0.0002*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 0.0002*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*(2*gL*gR*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (MZ*MZ)*(wZ*wZ)) + 
          (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
          (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                (MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56) + 
       C34*((0.0001*(gL*gL) + 0.0001*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C35*C35) + 
          (0. + 0.0001*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))))*(C45*C45) + 
          (0.0001*(gL*gL) + 0.0001*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C46*C46) + 
          0.0002*(4*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46)*
        C56 + (C36*C36)*
        (-0.0002*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*(C45*C45) + 
          (0. + 0.0001*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*C34*
           C56) + 0.0002*C36*C45*
        (2*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 + 
          ((gL*gL) + (gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*C34*C56)))/
   8192. - (el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.04*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 0.04*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       0.04*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 0.04*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       0.02*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.02*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       0.02*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.02*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       0.02*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.02*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       0.02*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.02*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*(gL + gR)*((gL*gL) + (gR*gR))*
        (0. - 0.01*(2*(M1*M1)*(M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ)))*(C34*C34)*
        (C56*C56) + C34*
        (0. - 2*gL*gR*(0. + 0.02*gL*(M1*M1)*(M2*M2) + 
             0.02*gR*(M1*M1)*(M2*M2) - 
             0.01*gL*(M1*M1)*(MZ*MZ) - 
             0.01*gR*(M1*M1)*(MZ*MZ) - 
             0.01*gL*(M2*M2)*(MZ*MZ) - 0.01*gR*(M2*M2)*(MZ*MZ))*
           (C36*C36) + 
          2*gL*gR*(0. - 0.02*gL*(M1*M1)*(M2*M2) - 
             0.02*gR*(M1*M1)*(M2*M2) + 
             0.01*gL*(M1*M1)*(MZ*MZ) + 
             0.01*gR*(M1*M1)*(MZ*MZ) + 
             0.01*gL*(M2*M2)*(MZ*MZ) + 0.01*gR*(M2*M2)*(MZ*MZ))*
           (C45*C45) + 
          C36*(0. + 4*((gL*gL*gL) + (gR*gR*gR))*
              (0. - 0.01*(2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C45) + 
          C46*(0. + 2*(0. - 
                0.01*((gL*gL*gL) + (gR*gR*gR))*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46))*
        C56 + (C35*C35)*
        (0. - 2*(gL + gR)*((gL*gL) + (gR*gR))*
           (0. - 0.01*(2*(M1*M1)*(M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ)))*(C46*C46) + 
          2*(0. + 0.01*(-(gL*gL*gL) - (gR*gR*gR))*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
           C34*C56) - 
       C35*(0. + C36*
           (0. + C45*(0. - 
                4*(gL + gR)*((gL*gL) + (gR*gR))*
                 (0. - 0.01*(2*(M1*M1)*(M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46)) - 
          C34*(0. + 4*gL*gR*(gL + gR)*
              (0. - 0.01*(2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46)*C56)\
))/8192. - ((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.04*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 0.02*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       0.02*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 0.04*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.02*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       0.02*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.04*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.02*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       0.02*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.04*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.02*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.02*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.04*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) - 0.02*(gL*gL)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) - 
       0.02*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) - 2*((gL+gR)*(gL+gR))*
        (0. - 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
          0.01*(MZ*MZ)*(wZ*wZ))*(C34*C34)*(C56*C56) + 
       C34*(-4*gL*gR*(0. + 
             0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.01*(MZ*MZ)*(wZ*wZ))*(C36*C36) - 
          4*gL*gR*(0. + 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.01*(MZ*MZ)*(wZ*wZ))*(C45*C45) + 
          4*((gL*gL) + (gR*gR))*
           (0. - 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             0.01*(MZ*MZ)*(wZ*wZ))*C36*C45 + 
          C46*(0. + 0.02*
              ((M1 - MZ)*(M1 + MZ)*((gL*gL) + (gR*gR))*
                 (-(M2*M2) + (MZ*MZ)) + 
                ((gL*gL) + (gR*gR))*(MZ*MZ)*(wZ*wZ))*C46))*
        C56 + (C35*C35)*
        (0. - 2*((gL+gR)*(gL+gR))*
           (0. - 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             0.01*(MZ*MZ)*(wZ*wZ))*(C46*C46) + 
          0.02*((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ)*
              (-(gL*gL) - (gR*gR)) + 
             ((gL*gL) + (gR*gR))*(MZ*MZ)*(wZ*wZ))*C34*
           C56) + C35*
        (0. - C36*C45*
           (0. - 4*((gL+gR)*(gL+gR))*
              (0. - 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                0.01*(MZ*MZ)*(wZ*wZ))*C46) + 
          C34*(0. + 8*gL*gR*
              (0. - 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                0.01*(MZ*MZ)*(wZ*wZ))*C46)*C56)))/8192.;
}


double GetHyp4GeneralScalar(LeptonVectors &leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double MH = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass();
   const double Mq = MH;
   const double s = MH * MH;
   const double x = (M1 * M1 - M2 * M2) / s;
   const double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   const double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   const double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   const double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(Reverse == true)
      swap(P1, P2);
   
   /*
   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }
   */

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C16 = P1 * P6;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C26 = P2 * P6;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1236 = EPS(P1, P2, P3, P6);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1246 = EPS(P1, P2, P4, P6);
   double E1256 = EPS(P1, P2, P5, P6);
   double E1345 = EPS(P1, P3, P4, P5);
   double E1346 = EPS(P1, P3, P4, P6);
   double E1356 = EPS(P1, P3, P5, P6);
   double E1456 = EPS(P1, P4, P5, P6);
   double E2345 = EPS(P2, P3, P4, P5);
   double E2346 = EPS(P2, P3, P4, P6);
   double E2356 = EPS(P2, P3, P5, P6);
   double E2456 = EPS(P2, P4, P5, P6);
   double E3456 = EPS(P3, P4, P5, P6);

   double vh = CONST_VH;
   
   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (0.0002*(C34*C34)*(C56*C56) - 
       2*(C36*C45 - C35*C46)*
        (0. - 0.0001*(C36*C45 - C35*C46)) + 
       C34*(0.0001*(C35*C35) + 0.0001*(C36*C36) + 
          0.0001*((C45*C45) + (C46*C46)) - 
          0.0002*C36*C45 - 0.0002*C35*C46)*C56\
))/4096. + (pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     ((gL*gL*gL*gL)*(C35*C35)*(C46*C46) + 
       2*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) + 
       (gR*gR*gR*gR)*(C35*C35)*(C46*C46) + 
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56) + 
       C34*(((gL*gL*gL*gL) + (gR*gR*gR*gR))*(C35*C35) + 
          2*(gL*gL)*(gR*gR)*(C45*C45) + 
          ((gL*gL*gL*gL) + (gR*gR*gR*gR))*(C46*C46) - 
          4*(gL*gL)*(gR*gR)*C35*C46)*C56 + 
       (C36*C36)*(((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45) + 
          2*(gL*gL)*(gR*gR)*C34*C56) + 
       C36*C45*(-2*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C35*
           C46 - 2*((gL*gL*gL*gL) + (gR*gR*gR*gR))*C34*C56)))/8192. \
+ ((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.0004*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 0.0004*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 0.0006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0008*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0008*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0002*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 0.0002*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 0.0002*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 0.0002*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       0.0002*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*(gL + gR)*
        (0. - 0.0002*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          0.0003*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          0.0003*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          0.0001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
          0.0004*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          0.0001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 0.0001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.0001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          0.0001*(MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
        (C34*C34)*(C56*C56) + 
       C34*((0. + 0.0002*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0002*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0004*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0001*(gL + gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C35*C35) + 
          (0. + 0.0002*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0002*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0004*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0001*(gL + gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C45*C45) + 
          (0. + 0.0002*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0002*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0004*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (-0.0001*gL - 0.0001*gR)*(MZ*MZ)*
              (-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C46*C46) + 
          2*(gL + gR)*(0. - 0.0002*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0003*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0003*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0004*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 0.0001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*C35*
           C46)*C56 + 
       2*(gL + gR)*(0. - 0.0002*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          0.0003*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          0.0003*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          0.0001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
          0.0004*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          0.0001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 0.0001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.0001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          0.0001*(MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*C36*
        C45*(2*C35*C46 + C34*C56) + 
       (C36*C36)*(-2*(gL + gR)*
           (0. - 0.0002*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0003*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             0.0003*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0001*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             0.0004*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 0.0001*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0001*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
              (wZ*wZ))*(C45*C45) + 
          (0. + 0.0002*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0002*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0003*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0003*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0003*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0001*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0004*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0004*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0001*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0001*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             0.0001*(gL + gR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
              (wZ*wZ))*C34*C56)))/4096. + 
  ((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.0004*gL*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 0.0006000000000000001*(gL*gL)*(M1*M1*M1*M1)*
        (M2*M2*M2*M2)*(C35*C35)*(C46*C46) + 
       0.0006000000000000001*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       0.0004*gL*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0006000000000000001*(gL*gL)*(M1*M1*M1*M1)*
        (M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46) - 
       0.0006000000000000001*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       0.0004*gL*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 0.0006000000000000001*(gL*gL)*(M1*M1)*
        (M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46) - 
       0.0006000000000000001*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0004*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 0.0002*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 0.0004*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (wZ*wZ)*(C35*C35)*(C46*C46) + 
       0.0002*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 0.0002*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       0.0002*(2*gL*gR*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (MZ*MZ)*(wZ*wZ)) + 
          (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
          (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                (MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56) + 
       C34*((0.0001*(gL*gL) + 0.0001*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C35*C35) + 
          (0. + 0.0001*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))))*(C45*C45) + 
          (0.0001*(gL*gL) + 0.0001*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C46*C46) - 
          0.0002*(4*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46)*
        C56 + (C36*C36)*
        (0.0002*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*(C45*C45) + 
          (0. + 0.0001*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*C34*
           C56) - 0.0002*C36*C45*
        (2*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 + 
          ((gL*gL) + (gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*C34*C56)))/
   8192. - (el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.04*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 0.04*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       0.04*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 0.04*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       0.02*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.02*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       0.02*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.02*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       0.02*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.02*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       0.02*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.02*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*(gL + gR)*((gL*gL) + (gR*gR))*
        (0. + 0.01*(2*(M1*M1)*(M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ)))*(C34*C34)*
        (C56*C56) + C34*
        (0. - 2*gL*gR*(0. + 0.02*gL*(M1*M1)*(M2*M2) + 
             0.02*gR*(M1*M1)*(M2*M2) - 
             0.01*gL*(M1*M1)*(MZ*MZ) - 
             0.01*gR*(M1*M1)*(MZ*MZ) - 
             0.01*gL*(M2*M2)*(MZ*MZ) - 0.01*gR*(M2*M2)*(MZ*MZ))*
           (C36*C36) + 
          2*gL*gR*(0. - 0.02*gL*(M1*M1)*(M2*M2) - 
             0.02*gR*(M1*M1)*(M2*M2) + 
             0.01*gL*(M1*M1)*(MZ*MZ) + 
             0.01*gR*(M1*M1)*(MZ*MZ) + 
             0.01*gL*(M2*M2)*(MZ*MZ) + 0.01*gR*(M2*M2)*(MZ*MZ))*
           (C45*C45) + 
          2*(0. - 0.02*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             0.02*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
             0.01*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             0.01*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
             0.01*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             0.01*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*(C46*C46) + 
          C36*(0. + 4*((gL*gL*gL) + (gR*gR*gR))*
              (0. + 0.01*(2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C45))*
        C56 + (C35*C35)*
        (-2*(gL + gR)*((gL*gL) + (gR*gR))*
           (0. + 0.01*(2*(M1*M1)*(M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ)))*(C46*C46) + 
          2*(0. - 0.02*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             0.02*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
             0.01*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             0.01*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
             0.01*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             0.01*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*C34*C56) - 
       C35*(0. + C36*
           (0. - 4*(gL + gR)*((gL*gL) + (gR*gR))*
              (0. + 0.01*(2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C45*C46) \
- 4*gL*gR*(gL + gR)*(0. + 0.01*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
           C34*C46*C56)))/8192. - 
  ((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.04*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 0.02*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       0.02*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 0.04*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.02*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       0.02*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.04*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.02*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       0.02*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.04*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.02*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) - 0.02*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) + 0.04*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) + 0.02*(gL*gL)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) + 
       0.02*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) - 2*((gL+gR)*(gL+gR))*
        (0. + 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
          0.01*(MZ*MZ)*(wZ*wZ))*(C34*C34)*(C56*C56) + 
       C34*(0. - 4*gL*gR*
           (0. + 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.01*(MZ*MZ)*(wZ*wZ))*(C36*C36) - 
          4*gL*gR*(0. + 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.01*(MZ*MZ)*(wZ*wZ))*(C45*C45) + 
          2*(0. - 0.01*(gL*gL)*(M1*M1)*(M2*M2) - 
             0.01*(gR*gR)*(M1*M1)*(M2*M2) + 
             0.01*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             0.01*(gR*gR)*(M1*M1)*(MZ*MZ) + 
             0.01*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             0.01*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             0.01*(gL*gL)*(MZ*MZ*MZ*MZ) - 0.01*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             (0.01*(gL*gL) + 0.01*(gR*gR))*(MZ*MZ)*(wZ*wZ))*
           (C46*C46) - 2*C36*
           (0. - 2*((gL*gL) + (gR*gR))*
              (0. + 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                0.01*(MZ*MZ)*(wZ*wZ))*C45))*C56 + 
       (C35*C35)*(-2*((gL+gR)*(gL+gR))*
           (0. + 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.01*(MZ*MZ)*(wZ*wZ))*(C46*C46) + 
          2*(0. - 0.01*(gL*gL)*(M1*M1)*(M2*M2) - 
             0.01*(gR*gR)*(M1*M1)*(M2*M2) + 
             0.01*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             0.01*(gR*gR)*(M1*M1)*(MZ*MZ) + 
             0.01*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             0.01*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             0.01*(gL*gL)*(MZ*MZ*MZ*MZ) - 0.01*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             (0.01*(gL*gL) + 0.01*(gR*gR))*(MZ*MZ)*(wZ*wZ))*
           C34*C56) + 
       C35*(0. - C36*
           (0. - 4*((gL+gR)*(gL+gR))*
              (0. + 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                0.01*(MZ*MZ)*(wZ*wZ))*C45*C46) + 
          8*gL*gR*(0. + 0.01*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.01*(MZ*MZ)*(wZ*wZ))*C34*C46*C56)))/8192.;
}

double GetHyp5GeneralScalar(LeptonVectors &leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double MH = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass();
   const double Mq = MH;
   const double s = MH * MH;
   const double x = (M1 * M1 - M2 * M2) / s;
   const double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   const double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   const double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   const double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(Reverse == true)
      swap(P1, P2);
   
   /*
   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }
   */

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C16 = P1 * P6;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C26 = P2 * P6;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1236 = EPS(P1, P2, P3, P6);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1246 = EPS(P1, P2, P4, P6);
   double E1256 = EPS(P1, P2, P5, P6);
   double E1345 = EPS(P1, P3, P4, P5);
   double E1346 = EPS(P1, P3, P4, P6);
   double E1356 = EPS(P1, P3, P5, P6);
   double E1456 = EPS(P1, P4, P5, P6);
   double E2345 = EPS(P2, P3, P4, P5);
   double E2346 = EPS(P2, P3, P4, P6);
   double E2356 = EPS(P2, P3, P5, P6);
   double E2456 = EPS(P2, P4, P5, P6);
   double E3456 = EPS(P3, P4, P5, P6);

   double vh = CONST_VH;

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (0. - 2*(0. - 0.0002*E3456)*
        (C36*C45 - C35*C46) + 
       (0. + 0.0002*(C35*C35) + 0.0002*(C36*C36) + 
          0.0002*((C45*C45) + (C46*C46)))*C34*C56)\
)/4096. - (el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.002*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       0.002*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*
        C36 + 0.001*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       0.001*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - 0.001*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       0.001*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.001*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       0.001*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       0.001*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       0.001*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       0.002*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        C45 - 0.002*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       0.001*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.001*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       0.001*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - 0.001*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       0.001*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       0.001*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       0.001*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       0.001*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       0.002*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*
        C46 + 0.002*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        C36*C45*C46 - 
       0.001*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + 0.001*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - 0.001*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       0.001*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 - 0.001*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 0.001*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       0.001*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.001*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       C34*(-2*gL*gR*(0. + 0.04*gL*(M1*M1)*(M2*M2) + 
             0.04*gR*(M1*M1)*(M2*M2) - 
             0.02*gL*(M1*M1)*(MZ*MZ) - 
             0.02*gR*(M1*M1)*(MZ*MZ) - 
             0.02*gL*(M2*M2)*(MZ*MZ) - 0.02*gR*(M2*M2)*(MZ*MZ))*
           (C36*C36) + 
          2*gL*gR*(0. - 0.04*gL*(M1*M1)*(M2*M2) - 
             0.04*gR*(M1*M1)*(M2*M2) + 
             0.02*gL*(M1*M1)*(MZ*MZ) + 
             0.02*gR*(M1*M1)*(MZ*MZ) + 
             0.02*gL*(M2*M2)*(MZ*MZ) + 0.02*gR*(M2*M2)*(MZ*MZ))*
           (C45*C45) + 
          (0. + gL*gR*(MZ*MZ)*
              (0. + (-gL + gR)*(M1 - M2)*(M1 + M2)*MZ*(0. + 0.001*wZ) - 
                0.01*(gL + gR)*
                 (0.2*(M1*M1)*(M2*M2) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ))))*C36 + 
          gL*gR*(MZ*MZ)*(0. + 
             (gL - gR)*(M1 - M2)*(M1 + M2)*MZ*(0. + 0.001*wZ) - 
             0.01*(gL + gR)*(0.2*(M1*M1)*(M2*M2) - 
                0.1*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45 + 
          C46*((MZ*MZ)*
              (0. + 0.001*MZ*wZ*((gL*gL*gL) - (gR*gR*gR))*
                 ((M1*M1) + (M2*M2)) + 
                (-0.01*(gL*gL*gL) - 0.01*(gR*gR*gR))*
                 (0.2*(M1*M1)*(M2*M2) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ))) + 
             2*(0. - 0.02*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
                0.02*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
                0.01*MZ*wZ*((gL*gL*gL) - (gR*gR*gR))*
                 ((M1*M1) + (M2*M2)) + 
                MZ*wZ*(-0.01*(gL*gL*gL) + 0.01*(gR*gR*gR))*
                 ((M1*M1) + (M2*M2)) + 
                0.01*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
                0.01*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                0.01*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
                0.01*(gR*gR*gR)*(M2*M2)*(MZ*MZ) - 
                0.01*((gL*gL*gL) + (gR*gR*gR))*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46))*
        C56 + E3456*
        (0. - 0.002*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C45 - 
          0.002*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C45 - 
          0.001*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          0.001*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          0.001*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          0.001*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          0.001*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          0.001*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          0.001*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          0.001*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          C36*(gL*gR*(MZ*MZ)*
              (0. + (gL - gR)*(M1 - M2)*(M1 + M2)*MZ*(0. + 0.001*wZ) - 
                0.01*(gL + gR)*
                 (0.2*(M1*M1)*(M2*M2) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
             2*(gL + gR)*((gL*gL) + (gR*gR))*
              (0. + 0.02*(2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C45) + 
          0.002*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          0.002*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          0.001*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          0.001*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          0.001*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          0.001*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          0.001*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          0.001*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          0.001*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          0.001*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          C35*(-((MZ*MZ)*
                (0. + 0.001*MZ*wZ*((gL*gL*gL) - (gR*gR*gR))*
                   ((M1*M1) + (M2*M2)) + 
                  (-0.01*(gL*gL*gL) - 0.01*(gR*gR*gR))*
                   (0.2*(M1*M1)*(M2*M2) - 
                     0.1*((M1*M1) + (M2*M2))*(MZ*MZ)))) + 
             2*(gL + gR)*((gL*gL) + (gR*gR))*
              (0. + 0.02*(2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46) + 
          2*(gL + gR)*((gL-gR)*(gL-gR))*
           (0. + 0.02*(2*(M1*M1)*(M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ)))*C34*C56) + 
       (C35*C35)*(0. + (MZ*MZ)*
           (0. - 0.001*MZ*wZ*((gL*gL*gL) - (gR*gR*gR))*
              ((M1*M1) + (M2*M2)) + 
             (-0.01*(gL*gL*gL) - 0.01*(gR*gR*gR))*
              (0.2*(M1*M1)*(M2*M2) - 
                0.1*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46 + 
          2*(0. - 0.02*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             0.02*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
             0.01*MZ*wZ*((gL*gL*gL) - (gR*gR*gR))*((M1*M1) + (M2*M2)) - 
             MZ*wZ*(-0.01*(gL*gL*gL) + 0.01*(gR*gR*gR))*
              ((M1*M1) + (M2*M2)) + 
             0.01*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             0.01*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
             0.01*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             0.01*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
             0.01*(-(gL*gL*gL) - (gR*gR*gR))*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
           C34*C56) - 
       C35*(0. + 0.002*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 0.002*(gR*gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          0.001*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          0.001*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          0.001*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          0.001*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) - 
          0.001*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.001*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.001*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.001*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          gL*gR*(MZ*MZ)*(0. + 
             (gL - gR)*(M1 - M2)*(M1 + M2)*MZ*(0. + 0.001*wZ) - 
             0.01*(gL + gR)*(0.2*(M1*M1)*(M2*M2) - 
                0.1*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45*C46 \
+ C36*((0. + (MZ*MZ)*(0. - 
                   0.001*MZ*wZ*((gL*gL*gL) - (gR*gR*gR))*
                    ((M1*M1) + (M2*M2)) + 
                   (-0.01*(gL*gL*gL) - 0.01*(gR*gR*gR))*
                    (0.2*(M1*M1)*(M2*M2) - 
                      0.1*((M1*M1) + (M2*M2))*(MZ*MZ))))*C45 + 
             gL*gR*(MZ*MZ)*(0. + 
                (-gL + gR)*(M1 - M2)*(M1 + M2)*MZ*(0. + 0.001*wZ) - 
                0.01*(gL + gR)*
                 (0.2*(M1*M1)*(M2*M2) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46) - 
          (0. + (MZ*MZ)*(0. - 
                0.001*MZ*wZ*((gL*gL*gL) - (gR*gR*gR))*
                 ((M1*M1) + (M2*M2)) + 
                (-0.01*(gL*gL*gL) - 0.01*(gR*gR*gR))*
                 (0.2*(M1*M1)*(M2*M2) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ))))*C34*
           C56)))/8192. + 
  ((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 2*(gL + gR)*E3456*
        (0. + 0.0004*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          0.0006*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          0.0006*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          0.0002*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          0.0008*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          0.0002*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 0.0002*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          0.0002*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.0002*(MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
        (C36*C45 - C35*C46) + 
       (0. + (0. + 0.0004*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0004*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0002*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0002*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0008*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0008*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0002*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0002*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0002*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (0.0001*gL + 0.0001*gR + 0.0001*(gL + gR))*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C35*C35) + 
          (0. + 0.0004*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0004*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             MZ*wZ*(0. - 0.0001*(gL - gR)*(M1 - M2)*(M1 + M2)*
                 (M1*M2 - (MZ*MZ))*(M1*M2 + (MZ*MZ)) + 
                0.0001*(gL - gR)*(M1 - M2)*(M1 + M2)*
                 ((M1*M1)*(M2*M2) - (MZ*MZ*MZ*MZ))) + 
             0.0002*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0002*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0008*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0008*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0002*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0002*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0002*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(0. + 0.0001*gL*(M1*M1*M1*M1) + 
                0.0001*gR*(M1*M1*M1*M1) + 0.0001*gL*(M2*M2*M2*M2) + 
                0.0001*gR*(M2*M2*M2*M2) - 
                ((0.0001*gL + 0.0001*gR)*(M1*M1) + 
                   (0.0001*gL + 0.0001*gR)*(M2*M2))*(MZ*MZ) + 
                0.0001*(gL + gR)*
                 ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*(wZ*wZ))*
           (C45*C45) + 
          (0. + 0.0004*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0004*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0002*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0002*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0008*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0008*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0002*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0002*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             0.0002*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (-0.0002*gL - 0.0002*gR)*(MZ*MZ)*
              (-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ))*
           (C46*C46))*C34*C56 + 
       (C36*C36)*(0. + (0. + 0.0004*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.0004*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.0006*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0006*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.0006*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.0006*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.0002*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0002*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0008*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0008*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0002*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0002*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             MZ*wZ*(0. + 0.0001*(gL - gR)*(M1 - M2)*(M1 + M2)*
                 (M1*M2 - (MZ*MZ))*(M1*M2 + (MZ*MZ)) + 
                0.0001*(gL - gR)*(M1 - M2)*(M1 + M2)*
                 (-((M1*M1)*(M2*M2)) + (MZ*MZ*MZ*MZ))) - 
             0.0002*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.0002*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(0. + 0.0001*gL*(M1*M1*M1*M1) + 0.0001*gR*(M1*M1*M1*M1) + 
                0.0001*gL*(M2*M2*M2*M2) + 0.0001*gR*(M2*M2*M2*M2) - 
                ((0.0001*gL + 0.0001*gR)*(M1*M1) + 
                   (0.0001*gL + 0.0001*gR)*(M2*M2))*(MZ*MZ) + 
                0.0001*(gL + gR)*
                 ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*(wZ*wZ))*C34*
           C56)))/4096. - 
  ((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.002*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*
        C36 + 0.002*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.002*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 - 0.002*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       0.002*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C45*C45)*C36 - 
       0.002*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        C45 + 0.002*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.002*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 - 0.002*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       0.002*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C36*C36)*C45 + 
       0.001*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*
        C46 + 0.001*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        C36*C45*C46 - 
       0.001*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + 0.001*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - 0.001*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       0.001*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 - 0.001*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 0.001*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       0.001*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.001*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       0.002*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.002*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       0.001*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46 + 
       0.001*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46 - 
       0.001*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46 - 
       0.001*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46 + 
       C34*(-4*gL*gR*(0. + 
             0.02*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.02*(MZ*MZ)*(wZ*wZ))*(C36*C36) - 
          4*gL*gR*(0. + 0.02*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.02*(MZ*MZ)*(wZ*wZ))*(C45*C45) - 
          2*(0. + gL*gR*(MZ*MZ)*
              (0. + 0.001*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                0.001*(MZ*MZ)*(wZ*wZ)))*C36 - 
          2*gL*gR*(MZ*MZ)*(0. + 
             0.001*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.001*(MZ*MZ)*(wZ*wZ))*C45 + 
          C46*((MZ*MZ)*
              (0. + 0.001*(gL - gR)*(gL + gR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (-0.01*(gL*gL) - 0.01*(gR*gR))*
                 (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   0.1*(MZ*MZ)*(wZ*wZ))) + 
             2*(0. - 0.01*(gL*gL)*(M1*M1)*(M2*M2) - 
                0.01*(gR*gR)*(M1*M1)*(M2*M2) + 
                MZ*wZ*(-0.01*(gL*gL) + 0.01*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                0.01*(gL*gL)*(M1*M1)*(MZ*MZ) + 
                0.01*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                0.01*(gL*gL)*(M2*M2)*(MZ*MZ) + 
                0.01*(gR*gR)*(M2*M2)*(MZ*MZ) - 
                0.01*(gL*gL)*(MZ*MZ*MZ*MZ) - 0.01*(gR*gR)*(MZ*MZ*MZ*MZ) + 
                (0.01*(gL*gL) + 0.01*(gR*gR))*(MZ*MZ)*(wZ*wZ) + 
                0.01*(MZ*wZ*((gL*gL) - (gR*gR))*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   (M1 - MZ)*(M1 + MZ)*((gL*gL) + (gR*gR))*
                    (-(M2*M2) + (MZ*MZ)) + 
                   ((gL*gL) + (gR*gR))*(MZ*MZ)*(wZ*wZ)))*C46\
))*C56 + E3456*
        (0. - 0.002*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*C45 + 
          0.002*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          0.002*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 - 
          0.002*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 + 
          0.002*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C45 - 
          2*C36*(gL*gR*(MZ*MZ)*
              (0. + 0.001*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                0.001*(MZ*MZ)*(wZ*wZ)) + 
             ((gL+gR)*(gL+gR))*(0. + 
                0.02*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                0.02*(MZ*MZ)*(wZ*wZ))*C45) + 
          0.001*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          0.001*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          0.001*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          0.001*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          0.001*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          0.001*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          0.001*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          0.001*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          0.001*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          0.001*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          0.002*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          0.002*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          0.001*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          0.001*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 - 
          0.001*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          0.001*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 + 
          C35*((MZ*MZ)*
              (0. - 0.001*(gL - gR)*(gL + gR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (0.01*(gL*gL) + 0.01*(gR*gR))*
                 (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   0.1*(MZ*MZ)*(wZ*wZ))) + 
             2*((gL+gR)*(gL+gR))*
              (0. + 0.02*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                0.02*(MZ*MZ)*(wZ*wZ))*C46) + 
          2*((gL-gR)*(gL-gR))*(0. + 
             0.02*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.02*(MZ*MZ)*(wZ*wZ))*C34*C56) + 
       (C35*C35)*(0. + (MZ*MZ)*
           (0. - 0.001*(gL - gR)*(gL + gR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (0.01*(gL*gL) + 0.01*(gR*gR))*
              (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                0.1*(MZ*MZ)*(wZ*wZ)))*C46 + 
          2*(0. - 0.01*(gL*gL)*(M1*M1)*(M2*M2) - 
             0.01*(gR*gR)*(M1*M1)*(M2*M2) - 
             MZ*wZ*(-0.01*(gL*gL) + 0.01*(gR*gR))*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
             0.01*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             0.01*(gR*gR)*(M1*M1)*(MZ*MZ) + 
             0.01*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             0.01*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             0.01*(gL*gL)*(MZ*MZ*MZ*MZ) - 0.01*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             (0.01*(gL*gL) + 0.01*(gR*gR))*(MZ*MZ)*(wZ*wZ) + 
             0.01*((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ)*
                 (-(gL*gL) - (gR*gR)) - 
                MZ*wZ*((gL*gL) - (gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                ((gL*gL) + (gR*gR))*(MZ*MZ)*(wZ*wZ)))*C34*
           C56) + C35*
        (0. - 0.001*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) - 0.001*(gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) + 
          0.001*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          0.001*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          0.001*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) - 
          0.001*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          0.001*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.001*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.001*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.001*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.002*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.002*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.001*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.001*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.001*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46) + 
          0.001*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46) + 
          2*gL*gR*(MZ*MZ)*(0. + 
             0.001*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
             0.001*(MZ*MZ)*(wZ*wZ))*C45*C46 - 
          C36*((0. + (MZ*MZ)*
                 (0. - 0.001*(gL - gR)*(gL + gR)*MZ*wZ*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   (0.01*(gL*gL) + 0.01*(gR*gR))*
                    (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                      0.1*(MZ*MZ)*(wZ*wZ))))*C45 - 
             2*gL*gR*(MZ*MZ)*
              (0. + 0.001*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                0.001*(MZ*MZ)*(wZ*wZ))*C46) + 
          (0. + (MZ*MZ)*(0. - 
                0.001*(gL - gR)*(gL + gR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (0.01*(gL*gL) + 0.01*(gR*gR))*
                 (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   0.1*(MZ*MZ)*(wZ*wZ))))*C34*C56)))/8192. + 
  ((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + (0. + (0.0002*(gL*gL) + 0.0002*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C35*C35) + 
          (0. + 0.0002*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))))*(C45*C45) + 
          (0.0002*(gL*gL) + 0.0002*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C46*C46))*
        C34*C56 + 0.0004*E3456*
        ((2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C36*C45 \
- (2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 \
- ((gL-gR)*(gL-gR))*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + (MZ*MZ)*(wZ*wZ))*
           C34*C56) + 
       (C36*C36)*(0. + (0. + 
             0.0002*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*C34*
           C56)))/8192. + 
  (pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.1*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35 + 
       0.1*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35 + 
       0.1*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 + 
       0.1*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       0.010000000000000002*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       0.010000000000000002*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46 - 
       0.2*(gL*gL)*(gR*gR)*(MZ*MZ)*C35*C45*C46 + 
       C34*((2*(gL*gL*gL*gL) + 2*(gR*gR*gR*gR))*(C35*C35) + 
          (2*(gL*gL*gL*gL) + 2*(gR*gR*gR*gR))*(C46*C46) + 
          (0.1*(gL*gL*gL*gL) + 0.1*(gR*gR*gR*gR))*(MZ*MZ)*C35 + 
          2*(gL*gL)*(gR*gR)*C45*(0.1*(MZ*MZ) + 2*C45) + 
          (0.1*(gL*gL*gL*gL) + 0.1*(gR*gR*gR*gR))*(MZ*MZ)*C46)*C56 + 
       (C36*C36)*(0.2*(gL*gL)*(gR*gR)*(MZ*MZ)*C45 + 
          4*(gL*gL)*(gR*gR)*C34*C56) + 
       E3456*(2*C36*
           (0.1*(gL*gL)*(gR*gR)*(MZ*MZ) + 
             ((gL*gL+gR*gR)*(gL*gL+gR*gR))*C45) + 
          (MZ*MZ)*(0.2*(gL*gL)*(gR*gR)*C45 - 
             (0.1*(gL*gL*gL*gL) + 0.1*(gR*gR*gR*gR))*C46) + 
          C35*((-0.1*(gL*gL*gL*gL) - 0.1*(gR*gR*gR*gR))*(MZ*MZ) - 
             2*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46) - 
          2*((gL*gL-gR*gR)*(gL*gL-gR*gR))*C34*C56) + 
       C36*(0.2*(gL*gL)*(gR*gR)*(MZ*MZ)*(C45*C45) + 
          C45*(0.020000000000000004*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             (-0.1*(gL*gL*gL*gL) - 0.1*(gR*gR*gR*gR))*(MZ*MZ)*C35 - 
             (0.1*(gL*gL*gL*gL) + 0.1*(gR*gR*gR*gR))*(MZ*MZ)*C46) + 
          0.2*(gL*gL)*(gR*gR)*(MZ*MZ)*
           (-(C35*C46) + C34*C56))))/8192.;
}

double GetHyp6GeneralScalar(LeptonVectors &leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double MH = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass();
   const double Mq = MH;
   const double s = MH * MH;
   const double x = (M1 * M1 - M2 * M2) / s;
   const double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   const double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   const double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   const double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(Reverse == true)
      swap(P1, P2);
   
   /*
   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }
   */

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C16 = P1 * P6;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C26 = P2 * P6;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1236 = EPS(P1, P2, P3, P6);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1246 = EPS(P1, P2, P4, P6);
   double E1256 = EPS(P1, P2, P5, P6);
   double E1345 = EPS(P1, P3, P4, P5);
   double E1346 = EPS(P1, P3, P4, P6);
   double E1356 = EPS(P1, P3, P5, P6);
   double E1456 = EPS(P1, P4, P5, P6);
   double E2345 = EPS(P2, P3, P4, P5);
   double E2346 = EPS(P2, P3, P4, P6);
   double E2356 = EPS(P2, P3, P5, P6);
   double E2456 = EPS(P2, P4, P5, P6);
   double E3456 = EPS(P3, P4, P5, P6);

   double vh = CONST_VH;

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (0. - 2*(0. - 0.00029800000000000003*E3456)*
        (C36*C45 - C35*C46) + 
       (0. + 0.00029800000000000003*(C35*C35) + 
          0.00029800000000000003*(C36*C36) + 
          0.00029800000000000003*((C45*C45) + (C46*C46)))*
        C34*C56))/4096. - 
  (el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 6.938893903907228e-18*gR*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       6.938893903907228e-18*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       6.938893903907228e-18*gL*(gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       6.938893903907228e-18*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       3.469446951953614e-18*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       3.469446951953614e-18*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       3.469446951953614e-18*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       3.469446951953614e-18*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       3.469446951953614e-18*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       3.469446951953614e-18*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       3.469446951953614e-18*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       3.469446951953614e-18*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       0.00328*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*
        C36 - 0.00328*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 + 
       0.00164*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - 0.00164*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       0.00164*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.00164*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       0.00164*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.00164*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       0.00164*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.00164*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       0.00328*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        C45 - 0.00328*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       0.00164*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.00164*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       0.00164*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - 0.00164*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       0.00164*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.00164*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       0.00164*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.00164*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       0.00328*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*
        C46 + 0.00328*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        C36*C45*C46 - 
       0.00164*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + 0.00164*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - 0.00164*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       0.00164*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 - 0.00164*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 0.00164*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       0.00164*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - 0.00164*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + C34*
        (-2*gL*gR*(0.0528*gL*(M1*M1)*(M2*M2) + 
             0.0528*gR*(M1*M1)*(M2*M2) + 
             MZ*wZ*((0.014400000000000003*gL + 
                   0.0016000000000000012*gR)*(M1*M1) + 
                (0.0016000000000000012*gL + 0.014400000000000003*gR)*
                 (M2*M2)) - 
             0.03440000000000001*gL*(M1*M1)*(MZ*MZ) - 
             0.0184*gR*(M1*M1)*(MZ*MZ) - 
             0.0184*gL*(M2*M2)*(MZ*MZ) - 
             0.03440000000000001*gR*(M2*M2)*(MZ*MZ) + 
             0.008*(MZ*((gL - gR)*(M1 - M2)*(M1 + M2)*MZ - 
                   wZ*(0.8*(gL - gR)*(M1 - M2)*(M1 + M2) + 
                      (gL + gR)*((M1*M1) + (M2*M2)))) + 
                0.8*(gL + gR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ))))*(C36*C36) \
+ 2*gL*gR*(-0.0528*gL*(M1*M1)*(M2*M2) - 
             0.0528*gR*(M1*M1)*(M2*M2) + 
             MZ*wZ*((-0.0016000000000000007*gL - 
                   0.014400000000000003*gR)*(M1*M1) - 
                (0.014400000000000003*gL + 0.0016000000000000012*gR)*
                 (M2*M2)) + 0.0184*gL*(M1*M1)*(MZ*MZ) + 
             0.0344*gR*(M1*M1)*(MZ*MZ) + 
             0.0344*gL*(M2*M2)*(MZ*MZ) + 
             0.0184*gR*(M2*M2)*(MZ*MZ) + 
             0.008*(MZ*((gL - gR)*(M1 - M2)*(M1 + M2)*MZ + 
                   wZ*(0.8*(gL - gR)*(-(M1*M1) + (M2*M2)) + 
                      (gL + gR)*((M1*M1) + (M2*M2)))) + 
                0.8*(gL + gR)*
                 (-2*(M1*M1)*(M2*M2) + 
                   ((M1*M1) + (M2*M2))*(MZ*MZ))))*(C45*C45) \
+ (0. + gL*gR*(MZ*MZ)*((-gL + gR)*(M1 - M2)*(M1 + M2)*MZ*
                 (0. + 0.00164*wZ) - 
                0.01*(gL + gR)*
                 (0.2*(M1*M1)*(M2*M2) + 
                   0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                0.008*(gL + gR)*
                 (-0.16*(M1*M1)*(M2*M2) + 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2)) + 
                   0.08*((M1*M1) + (M2*M2))*(MZ*MZ))))*C36 + 
          gL*gR*(MZ*MZ)*((gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
              (0. + 0.00164*wZ) - 
             0.01*(gL + gR)*(0.2*(M1*M1)*(M2*M2) + 
                0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
             0.008*(gL + gR)*
              (-0.16*(M1*M1)*(M2*M2) + 
                0.1*MZ*wZ*((M1*M1) + (M2*M2)) + 
                0.08*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45 + 
          C46*((MZ*MZ)*
              ((-0.002*(gL*gL*gL) - 0.018000000000000002*(gR*gR*gR))*
                 (0.2*(M1*M1)*(M2*M2) + 
                   0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                0.01*((gL*gL*gL) - (gR*gR*gR))*
                 (0.16*(M1*M1)*(M2*M2) - 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   0.08*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                0.008*((gL*gL*gL) + (gR*gR*gR))*
                 (0.16*(M1*M1)*(M2*M2) - 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   0.08*((M1*M1) + (M2*M2))*(MZ*MZ))) + 
             2*(-0.0008000000000000021*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
                0.06480000000000001*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
                0.01*MZ*wZ*(0.19999999999999996*(gL*gL*gL) - 
                   1.8*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
                MZ*wZ*(-0.0036000000000000003*(gL*gL*gL) + 
                   0.0035999999999999995*(gR*gR*gR))*
                 ((M1*M1) + (M2*M2)) + 
                0.008*MZ*wZ*(0.19999999999999996*(gL*gL*gL) + 
                   1.8*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
                0.0003999999999999993*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
                0.0324*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                0.0003999999999999993*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
                0.0324*(gR*gR*gR)*(M2*M2)*(MZ*MZ) - 
                0.008*(1.8*(gL*gL*gL) - 0.19999999999999996*(gR*gR*gR))*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                0.01*(1.8*(gL*gL*gL) + 0.19999999999999996*(gR*gR*gR))*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46))*
        C56 + E3456*
        (-0.00328*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C45 - 
          0.00328*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C45 - 
          0.00164*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          0.00164*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          0.00164*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          0.00164*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          0.00164*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          0.00164*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          0.00164*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          0.00164*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          C36*(gL*gR*(MZ*MZ)*
              ((gL - gR)*(M1 - M2)*(M1 + M2)*MZ*(0. + 0.00164*wZ) - 
                0.01*(gL + gR)*
                 (0.2*(M1*M1)*(M2*M2) + 
                   0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                0.008*(gL + gR)*
                 (-0.16*(M1*M1)*(M2*M2) + 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2)) + 
                   0.08*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
             2*(gL + gR)*((gL*gL) + (gR*gR))*
              (0. + 0.0328*(2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C45) + 
          0.00328*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          0.00328*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          0.00164*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          0.00164*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          0.00164*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          0.00164*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          0.00164*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          0.00164*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          0.00164*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          0.00164*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          C35*(-((MZ*MZ)*
                ((-0.002*(gL*gL*gL) - 0.018000000000000002*(gR*gR*gR))*
                   (0.2*(M1*M1)*(M2*M2) + 
                     0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                     0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                  0.01*((gL*gL*gL) - (gR*gR*gR))*
                   (0.16*(M1*M1)*(M2*M2) - 
                     0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                     0.08*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                  0.008*((gL*gL*gL) + (gR*gR*gR))*
                   (0.16*(M1*M1)*(M2*M2) - 
                     0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                     0.08*((M1*M1) + (M2*M2))*(MZ*MZ)))) + 
             2*(gL + gR)*((gL*gL) + (gR*gR))*
              (0. + 0.0328*(2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46) + 
          2*(gL + gR)*((gL-gR)*(gL-gR))*
           (0. + 0.0328*(2*(M1*M1)*(M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ)))*C34*C56) + 
       (C35*C35)*(0. + (MZ*MZ)*
           ((-0.018000000000000002*(gL*gL*gL) - 0.002*(gR*gR*gR))*
              (0.2*(M1*M1)*(M2*M2) + 
                0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
             0.01*((gL*gL*gL) - (gR*gR*gR))*
              (0.16*(M1*M1)*(M2*M2) - 
                0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                0.08*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
             0.008*((gL*gL*gL) + (gR*gR*gR))*
              (0.16*(M1*M1)*(M2*M2) - 
                0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                0.08*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46 + 
          2*(-0.06480000000000001*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             0.0008000000000000021*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
             0.01*MZ*wZ*(1.8*(gL*gL*gL) - 0.19999999999999996*(gR*gR*gR))*
              ((M1*M1) + (M2*M2)) - 
             MZ*wZ*(-0.0035999999999999995*(gL*gL*gL) + 
                0.0036000000000000003*(gR*gR*gR))*((M1*M1) + (M2*M2)) \
+ 0.008*MZ*wZ*(1.8*(gL*gL*gL) + 0.19999999999999996*(gR*gR*gR))*
              ((M1*M1) + (M2*M2)) + 
             0.0324*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             0.0003999999999999993*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
             0.0324*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             0.0003999999999999993*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
             0.01*(-0.19999999999999996*(gL*gL*gL) - 1.8*(gR*gR*gR))*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)) \
- 0.008*(-0.19999999999999996*(gL*gL*gL) + 1.8*(gR*gR*gR))*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
           C34*C56) - 
       C35*(0.00328*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 0.00328*(gR*gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          0.00164*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          0.00164*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          0.00164*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          0.00164*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) - 
          0.00164*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.00164*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.00164*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.00164*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          gL*gR*(MZ*MZ)*((gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
              (0. + 0.00164*wZ) - 
             0.01*(gL + gR)*(0.2*(M1*M1)*(M2*M2) + 
                0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
             0.008*(gL + gR)*(-0.16*(M1*M1)*(M2*M2) + 
                0.1*MZ*wZ*((M1*M1) + (M2*M2)) + 
                0.08*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45*
           C46 + C36*
           ((0. + (MZ*MZ)*((-0.018000000000000002*(gL*gL*gL) - 
                      0.002*(gR*gR*gR))*
                    (0.2*(M1*M1)*(M2*M2) + 
                      0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                      0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   0.01*((gL*gL*gL) - (gR*gR*gR))*
                    (0.16*(M1*M1)*(M2*M2) - 
                      0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                      0.08*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                   0.008*((gL*gL*gL) + (gR*gR*gR))*
                    (0.16*(M1*M1)*(M2*M2) - 
                      0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                      0.08*((M1*M1) + (M2*M2))*(MZ*MZ))))*C45 \
+ gL*gR*(MZ*MZ)*((-gL + gR)*(M1 - M2)*(M1 + M2)*MZ*(0. + 0.00164*wZ) - 
                0.01*(gL + gR)*
                 (0.2*(M1*M1)*(M2*M2) + 
                   0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                0.008*(gL + gR)*
                 (-0.16*(M1*M1)*(M2*M2) + 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2)) + 
                   0.08*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46) - 
          (0. + (MZ*MZ)*((-0.018000000000000002*(gL*gL*gL) - 
                   0.002*(gR*gR*gR))*
                 (0.2*(M1*M1)*(M2*M2) + 
                   0.08*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   0.1*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                0.01*((gL*gL*gL) - (gR*gR*gR))*
                 (0.16*(M1*M1)*(M2*M2) - 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   0.08*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                0.008*((gL*gL*gL) + (gR*gR*gR))*
                 (0.16*(M1*M1)*(M2*M2) - 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   0.08*((M1*M1) + (M2*M2))*(MZ*MZ))))*C34*
           C56)))/8192. - 
  ((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. - 0.0031200000000000004*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       0.00019999999999999987*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       0.00019999999999999987*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       0.0031200000000000004*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.0031200000000000004*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       0.00039999999999999975*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 - 0.0031200000000000004*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + 0.0031200000000000004*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C45*C45)*C36 - 
       0.0031200000000000004*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       0.00019999999999999987*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 - 
       0.00019999999999999987*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       0.0031200000000000004*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.0031200000000000004*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       0.00039999999999999975*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 - 0.0031200000000000004*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + 0.0031200000000000004*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C36*C36)*C45 + 
       0.00166*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*
        C46 + 0.0014600000000000001*(gR*gR)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       0.0014600000000000004*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 + 0.00166*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       0.0014600000000000004*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*
        C45*C46 + 0.00166*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       0.00166*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - 0.0014600000000000004*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       0.00166*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - 0.0014600000000000004*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 + 
       0.0029200000000000003*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*
        C46 - 0.00332*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*
        C46 + 0.00166*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*
        C46 + 0.0014600000000000001*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 0.00166*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        C36*C45*C46 - 
       0.0014600000000000004*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*
        C45*C46 + C34*
        (-4*gL*gR*(0.031200000000000002*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
              (M2 + MZ) + 0.002*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             0.031200000000000002*(MZ*MZ)*(wZ*wZ))*(C36*C36) - 
          4*gL*gR*(0.031200000000000002*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
              (M2 + MZ) + 0.002*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             0.031200000000000002*(MZ*MZ)*(wZ*wZ))*(C45*C45) - 
          2*(0. + gL*gR*(MZ*MZ)*
              (0.0015600000000000002*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + 
                0.00009999999999999994*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                0.0015600000000000002*(MZ*MZ)*(wZ*wZ)))*C36 - 
          2*gL*gR*(MZ*MZ)*(0.0015600000000000002*(M1 - MZ)*(M2 - MZ)*
              (M1 + MZ)*(M2 + MZ) + 
             0.00009999999999999994*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             0.0015600000000000002*(MZ*MZ)*(wZ*wZ))*C45 + 
          C46*((MZ*MZ)*
              ((-0.003*(gL*gL) - 0.017*(gR*gR))*
                 (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   0.08*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   0.1*(MZ*MZ)*(wZ*wZ)) - 
                0.01*(gL - gR)*(gL + gR)*
                 (0.08*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   0.08*(MZ*MZ)*(wZ*wZ)) + 
                0.007*((gL*gL) + (gR*gR))*
                 (0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   0.08*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                   0.08*(MZ*MZ)*(wZ*wZ))) + 
             2*(-0.0005999999999999998*(gL*gL)*(M1*M1)*(M2*M2) - 
                0.030600000000000002*(gR*gR)*(M1*M1)*(M2*M2) + 
                MZ*wZ*(-0.0054*(gL*gL) + 
                   0.0033999999999999994*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                0.0006000000000000016*(gL*gL)*(M1*M1)*(MZ*MZ) + 
                0.030600000000000002*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                0.0006000000000000016*(gL*gL)*(M2*M2)*(MZ*MZ) + 
                0.030600000000000002*(gR*gR)*(M2*M2)*(MZ*MZ) - 
                0.0005999999999999998*(gL*gL)*(MZ*MZ*MZ*MZ) - 
                0.030600000000000002*(gR*gR)*(MZ*MZ*MZ*MZ) + 
                (0.0005999999999999998*(gL*gL) + 
                   0.030600000000000002*(gR*gR))*(MZ*MZ)*(wZ*wZ) + 
                0.007*(MZ*wZ*
                    (0.19999999999999996*(gL*gL) + 1.8*(gR*gR))*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   (M1 - MZ)*(M1 + MZ)*
                    (1.8*(gL*gL) - 0.19999999999999996*(gR*gR))*
                    (-(M2*M2) + (MZ*MZ)) + 
                   (1.8*(gL*gL) - 0.19999999999999996*(gR*gR))*
                    (MZ*MZ)*(wZ*wZ)) + 
                0.01*(MZ*wZ*(0.19999999999999996*(gL*gL) - 
                      1.8*(gR*gR))*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   (M1 - MZ)*(M1 + MZ)*
                    (1.8*(gL*gL) + 0.19999999999999996*(gR*gR))*
                    (-(M2*M2) + (MZ*MZ)) + 
                   (1.8*(gL*gL) + 0.19999999999999996*(gR*gR))*
                    (MZ*MZ)*(wZ*wZ)))*C46))*C56 + 
       E3456*(-0.0031200000000000004*gL*gR*(M1*M1)*(M2*M2)*
           (MZ*MZ)*C45 - 
          0.00019999999999999987*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          0.00019999999999999987*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          0.0031200000000000004*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          0.0031200000000000004*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          0.00039999999999999975*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*C45 - 
          0.0031200000000000004*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 + 
          0.0031200000000000004*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C45 - 
          2*C36*(gL*gR*(MZ*MZ)*
              (0.0015600000000000002*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + 0.00009999999999999994*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                0.0015600000000000002*(MZ*MZ)*(wZ*wZ)) + 
             ((gL+gR)*(gL+gR))*(0.031200000000000002*(M1 - MZ)*(M2 - MZ)*
                 (M1 + MZ)*(M2 + MZ) + 
                0.002*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                0.031200000000000002*(MZ*MZ)*(wZ*wZ))*C45) + 
          0.0014600000000000001*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C46 + 0.00166*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C46 + 0.00166*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           C46 - 0.0014600000000000004*wZ*(gR*gR)*(M1*M1)*
           (MZ*MZ*MZ)*C46 + 
          0.00166*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          0.0014600000000000004*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
           C46 - 0.0014600000000000004*(gL*gL)*(M1*M1)*
           (MZ*MZ*MZ*MZ)*C46 - 
          0.00166*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          0.0014600000000000004*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          0.00166*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          0.00332*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          0.0029200000000000003*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          0.0014600000000000001*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          0.00166*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 - 
          0.0014600000000000004*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          0.00166*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 + 
          C35*((MZ*MZ)*
              ((0.003*(gL*gL) + 0.017*(gR*gR))*
                 (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   0.08*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   0.1*(MZ*MZ)*(wZ*wZ)) + 
                0.01*(gL - gR)*(gL + gR)*
                 (0.08*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   0.08*(MZ*MZ)*(wZ*wZ)) + 
                0.007*((gL*gL) + (gR*gR))*
                 (0.08*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   0.08*(MZ*MZ)*(wZ*wZ))) + 
             2*((gL+gR)*(gL+gR))*
              (0.031200000000000002*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + 0.002*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                0.031200000000000002*(MZ*MZ)*(wZ*wZ))*C46) + 
          2*((gL-gR)*(gL-gR))*(0.031200000000000002*(M1 - MZ)*(M2 - MZ)*
              (M1 + MZ)*(M2 + MZ) + 
             0.002*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             0.031200000000000002*(MZ*MZ)*(wZ*wZ))*C34*C56) \
+ (C35*C35)*(0. + (MZ*MZ)*
           (-((0.017*(gL*gL) + 0.003*(gR*gR))*
                (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                  0.08*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                  0.1*(MZ*MZ)*(wZ*wZ))) + 
             0.01*(gL - gR)*(gL + gR)*
              (0.08*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                0.08*(MZ*MZ)*(wZ*wZ)) + 
             0.007*((gL*gL) + (gR*gR))*
              (0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                0.08*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                0.08*(MZ*MZ)*(wZ*wZ)))*C46 + 
          2*(-0.030600000000000002*(gL*gL)*(M1*M1)*(M2*M2) - 
             0.0005999999999999998*(gR*gR)*(M1*M1)*(M2*M2) - 
             MZ*wZ*(-0.0033999999999999994*(gL*gL) + 0.0054*(gR*gR))*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
             0.030600000000000002*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             0.0006000000000000016*(gR*gR)*(M1*M1)*(MZ*MZ) + 
             0.030600000000000002*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             0.0006000000000000016*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             0.030600000000000002*(gL*gL)*(MZ*MZ*MZ*MZ) - 
             0.0005999999999999998*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             (0.030600000000000002*(gL*gL) + 
                0.0005999999999999998*(gR*gR))*(MZ*MZ)*(wZ*wZ) + 
             0.007*(MZ*wZ*(1.8*(gL*gL) + 
                   0.19999999999999996*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (M1 - MZ)*(M1 + MZ)*
                 (-0.19999999999999996*(gL*gL) + 1.8*(gR*gR))*
                 (-(M2*M2) + (MZ*MZ)) + 
                (-0.19999999999999996*(gL*gL) + 1.8*(gR*gR))*
                 (MZ*MZ)*(wZ*wZ)) + 
             0.01*((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ)*
                 (-0.19999999999999996*(gL*gL) - 1.8*(gR*gR)) - 
                MZ*wZ*(1.8*(gL*gL) - 0.19999999999999996*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (0.19999999999999996*(gL*gL) + 1.8*(gR*gR))*(MZ*MZ)*
                 (wZ*wZ)))*C34*C56) + 
       C35*(-0.00166*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) - 0.0014600000000000004*(gR*gR)*(M1*M1)*
           (M2*M2)*(MZ*MZ)*(C46*C46) + 
          0.0014600000000000001*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) - 0.00166*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) + 0.0014600000000000001*wZ*(gL*gL)*(M2*M2)*
           (MZ*MZ*MZ)*(C46*C46) - 
          0.00166*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          0.00166*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.0014600000000000001*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + 0.00166*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + 0.0014600000000000001*(gR*gR)*(M2*M2)*
           (MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.0029200000000000007*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.00332*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.00166*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46) - 
          0.0014600000000000004*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46) + 
          0.00166*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46) + 
          0.0014600000000000001*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + 2*gL*gR*(MZ*MZ)*
           (0.0015600000000000002*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
              (M2 + MZ) + 0.00009999999999999994*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             0.0015600000000000002*(MZ*MZ)*(wZ*wZ))*C45*C46 \
- C36*((0. + (MZ*MZ)*(-((0.017*(gL*gL) + 0.003*(gR*gR))*
                      (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                        0.08*MZ*wZ*
                        ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                        0.1*(MZ*MZ)*(wZ*wZ))) + 
                   0.01*(gL - gR)*(gL + gR)*
                    (0.08*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                      0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                      0.08*(MZ*MZ)*(wZ*wZ)) + 
                   0.007*((gL*gL) + (gR*gR))*
                    (0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                      0.08*(M1 - MZ)*(M1 + MZ)*
                       (-(M2*M2) + (MZ*MZ)) + 
                      0.08*(MZ*MZ)*(wZ*wZ))))*C45 - 
             2*gL*gR*(MZ*MZ)*
              (0.0015600000000000002*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + 0.00009999999999999994*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                0.0015600000000000002*(MZ*MZ)*(wZ*wZ))*C46) + 
          (0. + (MZ*MZ)*(-((0.017*(gL*gL) + 0.003*(gR*gR))*
                   (0.1*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                     0.08*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                     0.1*(MZ*MZ)*(wZ*wZ))) + 
                0.01*(gL - gR)*(gL + gR)*
                 (0.08*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   0.08*(MZ*MZ)*(wZ*wZ)) + 
                0.007*((gL*gL) + (gR*gR))*
                 (0.1*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   0.08*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                   0.08*(MZ*MZ)*(wZ*wZ))))*C34*C56)))/8192. + 
  ((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + (0. + (0.00032800000000000006*(gL*gL) + 
             0.00032800000000000006*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C35*C35) + 
          (0. + 0.000328*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))))*(C45*C45) + 
          (0.00032800000000000006*(gL*gL) + 
             0.00032800000000000006*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C46*C46))*
        C34*C56 + 0.000656*E3456*
        ((2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C36*C45 \
- (2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 \
- ((gL-gR)*(gL-gR))*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + (MZ*MZ)*(wZ*wZ))*
           C34*C56) + 
       (C36*C36)*(0. + (0. + 
             0.000328*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*C34*
           C56)))/8192. + 
  ((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 5.421010862427522e-20*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 5.421010862427522e-20*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2.710505431213761e-20*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       1.0842021724855044e-19*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       1.0842021724855044e-19*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2.710505431213761e-20*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2.710505431213761e-20*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2.710505431213761e-20*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2.710505431213761e-20*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(gL + gR)*(0. + 2.710505431213761e-20*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          1.3552527156068805e-20*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          5.421010862427522e-20*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          1.3552527156068805e-20*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          1.3552527156068805e-20*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          1.3552527156068805e-20*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ))*(C34*C34)*
        (C56*C56) + 2*(gL + gR)*E3456*
        (0.000624*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          0.000936*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          0.000936*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          0.000312*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          0.001248*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          0.000312*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          0.000019999999999999998*MZ*wZ*
           ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
             (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))) - 
          0.000312*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 0.000312*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          0.000312*(MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
             ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
          0.000019999999999999998*((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*
           (wZ*wZ*wZ))*(C36*C45 - C35*C46) + 
       C34*((0.00037200000000000004*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.000652*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.000558*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.000978*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.000558*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.000978*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.00018600000000000002*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.000326*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.0007440000000000001*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.001304*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.00018600000000000002*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000326*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             (0.000034*gL + 0.000146*gR)*MZ*wZ*
              ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ))) - 
             0.00018600000000000002*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00032600000000000006*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00018600000000000002*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00032600000000000006*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (6.e-6*gL + 0.00030600000000000007*gR + 
                0.01*(0.008*(gL - gR) + 0.01*(gL + gR)))*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             0.007*(0.01*(gL - gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                0.008*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) - 
                (0.008*(-gL + gR) + 0.01*(gL + gR))*MZ*wZ*
                 ((M1*M1*M1*M1)*(M2*M2) + 
                   (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1)*
                    ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             (0.000034*gL + 0.000146*gR)*((M1*M1) + (M2*M2))*
              (MZ*MZ*MZ)*(wZ*wZ*wZ))*(C35*C35) + 
          (0.000512*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.000512*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.000838*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.000698*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.000698*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.000838*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.000326*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.00018600000000000002*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.001024*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.001024*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.00018600000000000002*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000326*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             MZ*wZ*(0.007*(-0.008*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    (M1*M2 - (MZ*MZ))*(M1*M2 + (MZ*MZ)) - 
                   0.01*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))\
)) + 0.01*(-0.01*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                    (M1*M2 + (MZ*MZ)) + 
                   0.008*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))\
)) + 0.01*(0.01*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    ((M1*M1)*(M2*M2) - (MZ*MZ*MZ*MZ)) + 
                   0.008*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ)))\
)) - 0.00032600000000000006*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00018600000000000002*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00018600000000000002*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00032600000000000006*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(0.000306*gL*(M1*M1*M1*M1) + 
                5.999999999999997e-6*gR*(M1*M1*M1*M1) + 
                5.999999999999997e-6*gL*(M2*M2*M2*M2) + 
                0.000306*gR*(M2*M2*M2*M2) - 
                ((0.00030600000000000007*gL + 6.e-6*gR)*(M1*M1) + 
                   (6.e-6*gL + 0.00030600000000000007*gR)*(M2*M2))*
                 (MZ*MZ) + 
                0.01*(-0.008*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    ((M1*M1) + (M2*M2) - (MZ*MZ)) + 
                   0.01*(gL + gR)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))))*(wZ*wZ) + 
             0.007*(0.008*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                MZ*(0.01*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
                    ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                      ((M1*M1) + (M2*M2) - (MZ*MZ))*(wZ*wZ)) + 
                   wZ*(0.008*(gL - gR)*(M1 - M2)*(M1 + M2)*
                       ((M1*M1)*(M2*M2) - 
                        (MZ*MZ)*((MZ*MZ) + (wZ*wZ))) - 
                      0.01*(gL + gR)*
                       ((M1*M1*M1*M1)*(M2*M2) + 
                        (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        (M1*M1)*
                        ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                        (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))) + 
             ((0.000146*gL + 0.000034*gR)*(M1*M1) + 
                (0.000034*gL + 0.000146*gR)*(M2*M2))*(MZ*MZ*MZ)*
              (wZ*wZ*wZ))*(C45*C45) + 
          (0.000652*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.00037200000000000004*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.000978*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.000558*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.000978*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.000558*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.000326*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.00018600000000000002*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.001304*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.0007440000000000001*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000326*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.00018600000000000002*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             (0.000146*gL + 0.000034*gR)*MZ*wZ*
              ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ))) - 
             0.00032600000000000006*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00018600000000000002*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00032600000000000006*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00018600000000000002*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (-0.00032600000000000006*gL - 0.00018600000000000002*gR)*
              (MZ*MZ)*(-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             0.007*(0.008*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                0.01*(gL - gR)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ)*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    (-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) - 
                (0.008*(gL - gR) + 0.01*(gL + gR))*MZ*wZ*
                 ((M1*M1*M1*M1)*(M2*M2) + 
                   (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1)*
                    ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             (0.000146*gL + 0.000034*gR)*((M1*M1) + (M2*M2))*
              (MZ*MZ*MZ)*(wZ*wZ*wZ))*(C46*C46) + 
          2*(gL + gR)*(0. + 2.710505431213761e-20*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             1.3552527156068805e-20*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             5.421010862427522e-20*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             1.3552527156068805e-20*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             1.3552527156068805e-20*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             1.3552527156068805e-20*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ))*C35*
           C46)*C56 + 
       2*(gL + gR)*(0. + 2.710505431213761e-20*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          1.3552527156068805e-20*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          5.421010862427522e-20*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          1.3552527156068805e-20*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          1.3552527156068805e-20*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          1.3552527156068805e-20*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ))*C36*C45*
        (2*C35*C46 + C34*C56) + 
       (C36*C36)*(-2*(gL + gR)*
           (0. + 2.710505431213761e-20*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             1.3552527156068805e-20*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             5.421010862427522e-20*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             1.3552527156068805e-20*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             1.3552527156068805e-20*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             1.3552527156068805e-20*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ))*(C45*C45) + 
          (0.000512*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             0.000512*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             0.000698*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.000838*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             0.000838*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             0.000698*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             0.00018600000000000002*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.000326*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             0.001024*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.001024*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.000326*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             0.00018600000000000002*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             MZ*wZ*(0.007*(0.008*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    (M1*M2 - (MZ*MZ))*(M1*M2 + (MZ*MZ)) - 
                   0.01*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ)))) \
+ 0.01*(0.01*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                    (M1*M2 + (MZ*MZ)) + 
                   0.008*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ)))) \
+ 0.01*(0.01*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    (-((M1*M1)*(M2*M2)) + (MZ*MZ*MZ*MZ)) + 
                   0.008*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))))) \
- 0.00018600000000000002*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00032600000000000006*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00032600000000000006*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             0.00018600000000000002*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(5.999999999999997e-6*gL*(M1*M1*M1*M1) + 
                0.000306*gR*(M1*M1*M1*M1) + 0.000306*gL*(M2*M2*M2*M2) + 
                5.999999999999997e-6*gR*(M2*M2*M2*M2) - 
                ((6.e-6*gL + 0.00030600000000000007*gR)*(M1*M1) + 
                   (0.00030600000000000007*gL + 6.e-6*gR)*(M2*M2))*
                 (MZ*MZ) + 0.01*
                 (0.008*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    ((M1*M1) + (M2*M2) - (MZ*MZ)) + 
                   0.01*(gL + gR)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))))*(wZ*wZ) + 
             0.007*(0.008*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                MZ*(-0.01*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
                    ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                      ((M1*M1) + (M2*M2) - (MZ*MZ))*(wZ*wZ)) + 
                   wZ*(-0.008*(gL - gR)*(M1 - M2)*(M1 + M2)*
                       ((M1*M1)*(M2*M2) - 
                         (MZ*MZ)*((MZ*MZ) + (wZ*wZ))) - 
                      0.01*(gL + gR)*
                       ((M1*M1*M1*M1)*(M2*M2) + 
                         (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         (M1*M1)*
                         ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                         (MZ*MZ)*(wZ*wZ)))))) + 
             ((0.000034*gL + 0.000146*gR)*(M1*M1) + 
                (0.000146*gL + 0.000034*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*
           C34*C56)))/4096. + 
  (pow(Pi,-7)*(1.0/s)*pow(vh,-2)*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (0. + 0.16399999999999998*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*
        C35 + 0.16400000000000003*(gR*gR*gR*gR)*(MZ*MZ)*
        (C46*C46)*C35 + 
       0.16400000000000003*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 + 
       0.16399999999999998*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       0.0164*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       0.0164*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46 - 
       0.328*(gL*gL)*(gR*gR)*(MZ*MZ)*C35*C45*C46 + 
       C34*((3.2800000000000002*(gL*gL*gL*gL) + 
             3.2800000000000002*(gR*gR*gR*gR))*(C35*C35) + 
          (3.2800000000000002*(gL*gL*gL*gL) + 3.2800000000000002*(gR*gR*gR*gR))*
           (C46*C46) + (0. + 
             (0.16400000000000003*(gL*gL*gL*gL) + 0.164*(gR*gR*gR*gR))*(MZ*MZ))*
           C35 + 2*(gL*gL)*(gR*gR)*C45*
           (0.164*(MZ*MZ) + 3.2800000000000002*C45) + 
          (0.164*(gL*gL*gL*gL) + 0.16400000000000003*(gR*gR*gR*gR))*(MZ*MZ)*
           C46)*C56 + 
       (C36*C36)*(0. + 0.328*(gL*gL)*(gR*gR)*(MZ*MZ)*
           C45 + 6.5600000000000005*(gL*gL)*(gR*gR)*C34*
           C56) + E3456*
        (2*C36*(0.164*(gL*gL)*(gR*gR)*(MZ*MZ) + 
             1.6400000000000001*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C45) + 
          (MZ*MZ)*(0.328*(gL*gL)*(gR*gR)*C45 - 
             (0.16400000000000003*(gL*gL*gL*gL) + 0.164*(gR*gR*gR*gR))*C46) + 
          C35*((-0.164*(gL*gL*gL*gL) - 0.16400000000000003*(gR*gR*gR*gR))*
              (MZ*MZ) - 3.2800000000000002*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
              C46) - 3.2800000000000002*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
           C34*C56) + 
       C36*(0.328*(gL*gL)*(gR*gR)*(MZ*MZ)*(C45*C45) + 
          C45*(0. + 0.0328*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             (0. + (-0.16400000000000003*(gL*gL*gL*gL) - 0.164*(gR*gR*gR*gR))*
                 (MZ*MZ))*C35 - 
             (0.164*(gL*gL*gL*gL) + 0.16400000000000003*(gR*gR*gR*gR))*(MZ*MZ)*
              C46) + 0.328*(gL*gL)*(gR*gR)*(MZ*MZ)*
           (-(C35*C46) + C34*C56))))/8192.;
}

double GetGeneralScalarSecondTry(LeptonVectors &leptons, GeneralScalarParameters &parameters)
{
   double aAR = parameters.aAR, aAI = parameters.aAI;
   double aAdR = parameters.aAdR, aAdI = parameters.aAdI;
   double aZAR = parameters.aZAR, aZAI = parameters.aZAI;
   double aZAdR = parameters.aZAdR, aZAdI = parameters.aZAdI;
   double aZR = parameters.aZR, aZI = parameters.aZI;
   double aZdR = parameters.aZdR, aZdI = parameters.aZdI;
   double ahR = parameters.ahR, ahI = parameters.ahI;

   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double MH = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass();
   const double Mq = MH;
   const double s = MH * MH;
   const double x = (M1 * M1 - M2 * M2) / s;
   const double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   const double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   const double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   const double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;

   double E3456 = EPS(P3, P4, P5, P6);
    
  return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (2*(-(aAdI*aAdI) - (aAdR*aAdR) + (aAI*aAI) + (aAR*aAR))*
        (C34*C34)*(C56*C56) - 
       2*(C36*C45 - C35*C46)*
        (-2*(aAdI*aAI + aAdR*aAR)*E3456 + 
          ((aAdI*aAdI) + (aAdR*aAdR) - (aAI*aAI) - (aAR*aAR))*
           (C36*C45 - C35*C46)) + 
       C34*(((aAdI*aAdI) + (aAdR*aAdR) + (aAI*aAI) + (aAR*aAR))*
           (C35*C35) + ((aAdI*aAdI) + (aAdR*aAdR) + (aAI*aAI) + 
             (aAR*aAR))*(C36*C36) + 
          ((aAdI*aAdI) + (aAdR*aAdR) + (aAI*aAI) + (aAR*aAR))*
           ((C45*C45) + (C46*C46)) + 
          2*((aAdI*aAdI) + (aAdR*aAdR) - (aAI*aAI) - (aAR*aAR))*
           C36*C45 + 
          2*((aAdI*aAdI) + (aAdR*aAdR) - (aAI*aAI) - (aAR*aAR))*
           C35*C46)*C56))/4096. + 
  ((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (-2*aAdR*aZAdI*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       4*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 4*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       4*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 4*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       4*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 4*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       4*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 4*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       6*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 6*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 6*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 6*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 6*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*aAdI*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 6*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 6*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*aAdI*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 6*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 6*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       8*aAdR*aZAdI*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 8*aAdI*aZAdR*gL*wZ*(M1*M1)*(M2*M2)*
        (MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       8*aAR*aZAI*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 8*aAI*aZAR*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       8*aAdR*aZAdI*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 8*aAdI*aZAdR*gR*wZ*(M1*M1)*(M2*M2)*
        (MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       8*aAR*aZAI*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 8*aAI*aZAR*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       8*aAdI*aZAdI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 8*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       8*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 8*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       8*aAdI*aZAdI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 8*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       8*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 8*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdI*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAdI*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*aAdR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) + 2*aAdI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*aAR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*
        (C46*C46) - 2*aAI*aZAR*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(gL + gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
          aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
          aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*MZ*wZ*
           ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
             (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))) - 
          aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          (aAdI*aZAdI + aAdR*aZAdR - aAI*aZAI - aAR*aZAR)*(MZ*MZ)*
           ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
           (wZ*wZ) + (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*
           ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C34*C34)*
        (C56*C56) + 2*(gL + gR)*E3456*
        (2*aAI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAdI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAdR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          3*aAI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAdI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          aAI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + aAR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          aAdI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + aAdR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          4*aAI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAdI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAdR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + aAR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + aAdR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          (aAR*aZAdI - aAI*aZAdR + aAdR*aZAI - aAdI*aZAR)*MZ*wZ*
           ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
             (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))) - 
          aAI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          (aAI*aZAdI + aAR*aZAdR + aAdI*aZAI + aAdR*aZAR)*(MZ*MZ)*
           ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
           (wZ*wZ) + (aAR*aZAdI - aAI*aZAdR + aAdR*aZAI - aAdI*aZAR)*
           ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*
        (C36*C45 - C35*C46) + 
       C34*((2*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             3*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAdI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAI*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAdR*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAR*aZAdI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             ((aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*
                 gL + (aAR*(aZAdR + aZAI) + 
                   (aAdR + aAI)*(aZAdI - aZAR))*gR)*MZ*wZ*
              ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ))) - aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             ((aAdR - aAI)*(aZAdR - aZAI)*gL + 
                (aAdR + aAI)*(aZAdR + aZAI)*gR + 
                aAR*(aZAdI*(gL - gR) + aZAR*(gL + gR)))*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             aAdI*(aZAR*(gL - gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                aZAdI*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) - 
                (aZAI*(-gL + gR) + aZAdR*(gL + gR))*MZ*wZ*
                 ((M1*M1*M1*M1)*(M2*M2) + 
                   (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1)*
                    ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             ((aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gL + 
                (aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gR)*
              ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*
           (C35*C35) + 
          (2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             MZ*wZ*(aAdR*(aZAR*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    ((M1*M1)*(M2*M2) - (MZ*MZ*MZ*MZ)) + 
                   aZAdI*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))
)) + aAR*(-(aZAdR*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                      (M1*M2 + (MZ*MZ))) + 
                   aZAI*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))
)) + aAI*(-(aZAdI*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                      (M1*M2 + (MZ*MZ))) - 
                   aZAR*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ)))
)) + aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(aAdR*aZAdR*gL*(M1*M1*M1*M1) + 
                aAI*aZAdR*gL*(M1*M1*M1*M1) + aAdR*aZAI*gL*(M1*M1*M1*M1) + 
                aAI*aZAI*gL*(M1*M1*M1*M1) + aAdR*aZAdR*gR*(M1*M1*M1*M1) - 
                aAI*aZAdR*gR*(M1*M1*M1*M1) - aAdR*aZAI*gR*(M1*M1*M1*M1) + 
                aAI*aZAI*gR*(M1*M1*M1*M1) + aAdR*aZAdR*gL*(M2*M2*M2*M2) - 
                aAI*aZAdR*gL*(M2*M2*M2*M2) - aAdR*aZAI*gL*(M2*M2*M2*M2) + 
                aAI*aZAI*gL*(M2*M2*M2*M2) + aAdR*aZAdR*gR*(M2*M2*M2*M2) + 
                aAI*aZAdR*gR*(M2*M2*M2*M2) + aAdR*aZAI*gR*(M2*M2*M2*M2) + 
                aAI*aZAI*gR*(M2*M2*M2*M2) - 
                (((aAdR + aAI)*(aZAdR + aZAI)*gL + 
                      (aAdR - aAI)*(aZAdR - aZAI)*gR)*(M1*M1) + 
                   ((aAdR - aAI)*(aZAdR - aZAI)*gL + 
                      (aAdR + aAI)*(aZAdR + aZAI)*gR)*(M2*M2))*
                 (MZ*MZ) + 
                aAR*(-(aZAdI*(gL - gR)*(M1 - M2)*(M1 + M2)*
                      ((M1*M1) + (M2*M2) - (MZ*MZ))) + 
                   aZAR*(gL + gR)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))))*(wZ*wZ) + 
             aAdI*(aZAdI*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                MZ*(aZAR*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
                    ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                      ((M1*M1) + (M2*M2) - (MZ*MZ))*(wZ*wZ)) + 
                   wZ*(aZAI*(gL - gR)*(M1 - M2)*(M1 + M2)*
                       ((M1*M1)*(M2*M2) - 
                        (MZ*MZ)*((MZ*MZ) + (wZ*wZ))) - 
                      aZAdR*(gL + gR)*
                       ((M1*M1*M1*M1)*(M2*M2) + 
                        (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        (M1*M1)*
                        ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                        (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))) + 
             (((aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*
                    gL + (aAR*(-aZAdR + aZAI) + 
                      (aAdR - aAI)*(aZAdI + aZAR))*gR)*(M1*M1) + 
                ((aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*
                    gL + (aAR*(aZAdR + aZAI) + 
                      (aAdR + aAI)*(aZAdI - aZAR))*gR)*(M2*M2))*
              (MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45) + 
          (-2*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             3*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             4*aAR*aZAdI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAdI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAI*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAdR*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             ((aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gL + 
                (aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gR
)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ))) + aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             ((-aAdR - aAI)*(aZAdR + aZAI)*gL + 
                aAR*(aZAdI - aZAR)*gL - 
                (aAdR - aAI)*(aZAdR - aZAI)*gR - aAR*(aZAdI + aZAR)*gR
)*(MZ*MZ)*(-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             aAdI*(aZAdI*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                aZAR*(gL - gR)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ)*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*
                    (-(M1*M1*M1*M1) - (M2*M2*M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) - 
                (aZAI*(gL - gR) + aZAdR*(gL + gR))*MZ*wZ*
                 ((M1*M1*M1*M1)*(M2*M2) + 
                   (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1)*
                    ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             ((aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gL + 
                (aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gR)*
              ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*
           (C46*C46) + 
          2*(gL + gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*MZ*wZ*
              ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ))) - aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (aAdI*aZAdI + aAdR*aZAdR - aAI*aZAI - aAR*aZAR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*
              ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C35*
           C46)*C56 + 
       2*(gL + gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
          2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
          3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
          3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
          3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
          3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
          aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
          aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
          4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
          4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
          aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
          (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*MZ*wZ*
           ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
             (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))) - 
          aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
          aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
          (aAdI*aZAdI + aAdR*aZAdR - aAI*aZAI - aAR*aZAR)*(MZ*MZ)*
           ((M1*M1*M1*M1) + (M2*M2*M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))*
           (wZ*wZ) + (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*
           ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C36*
        C45*(2*C35*C46 + C34*C56) + 
       (C36*C36)*(-2*(gL + gR)*
           (2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*MZ*wZ*
              ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                (M1*M1)*((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))
) - aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (aAdI*aZAdI + aAdR*aZAdR - aAI*aZAI - aAR*aZAR)*(MZ*MZ)*
              ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ) + 
             (aAdR*aZAdI - aAdI*aZAdR - aAR*aZAI + aAI*aZAR)*
              ((M1*M1) + (M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45) 
+ (2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) + 
             2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2) - 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) - 
             3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
             aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) + 
             4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ) + 
             MZ*wZ*(aAdR*(aZAR*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    (-((M1*M1)*(M2*M2)) + (MZ*MZ*MZ*MZ)) + 
                   aZAdI*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ)))) 
+ aAR*(aZAdR*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                    (M1*M2 + (MZ*MZ)) + 
                   aZAI*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ)))) 
+ aAI*(aZAdI*(gL - gR)*(M1 - M2)*(M1 + M2)*(M1*M2 - (MZ*MZ))*
                    (M1*M2 + (MZ*MZ)) - 
                   aZAR*(gL + gR)*
                    ((M1*M1*M1*M1)*(M2*M2) + (M2*M2)*(MZ*MZ*MZ*MZ) + 
                      (M1*M1)*
                       ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ))))) 
- aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) - 
             aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ) + 
             (MZ*MZ)*(aAdR*aZAdR*gL*(M1*M1*M1*M1) - 
                aAI*aZAdR*gL*(M1*M1*M1*M1) - aAdR*aZAI*gL*(M1*M1*M1*M1) + 
                aAI*aZAI*gL*(M1*M1*M1*M1) + aAdR*aZAdR*gR*(M1*M1*M1*M1) + 
                aAI*aZAdR*gR*(M1*M1*M1*M1) + aAdR*aZAI*gR*(M1*M1*M1*M1) + 
                aAI*aZAI*gR*(M1*M1*M1*M1) + aAdR*aZAdR*gL*(M2*M2*M2*M2) + 
                aAI*aZAdR*gL*(M2*M2*M2*M2) + aAdR*aZAI*gL*(M2*M2*M2*M2) + 
                aAI*aZAI*gL*(M2*M2*M2*M2) + aAdR*aZAdR*gR*(M2*M2*M2*M2) - 
                aAI*aZAdR*gR*(M2*M2*M2*M2) - aAdR*aZAI*gR*(M2*M2*M2*M2) + 
                aAI*aZAI*gR*(M2*M2*M2*M2) - 
                (((aAdR - aAI)*(aZAdR - aZAI)*gL + 
                      (aAdR + aAI)*(aZAdR + aZAI)*gR)*(M1*M1) + 
                   ((aAdR + aAI)*(aZAdR + aZAI)*gL + 
                      (aAdR - aAI)*(aZAdR - aZAI)*gR)*(M2*M2))*
                 (MZ*MZ) + aAR*
                 (aZAdI*(gL - gR)*(M1 - M2)*(M1 + M2)*
                    ((M1*M1) + (M2*M2) - (MZ*MZ)) + 
                   aZAR*(gL + gR)*
                    ((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))))*(wZ*wZ) + 
             aAdI*(aZAdI*(gL + gR)*
                 ((M2 - MZ)*(M2 + MZ)*(-(M1*M1) + (MZ*MZ))*
                    (-2*(M1*M1)*(M2*M2) + 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (MZ*MZ)*((M1*M1*M1*M1) + (M2*M2*M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ))*(wZ*wZ)) + 
                MZ*(-(aZAR*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
                      ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                        ((M1*M1) + (M2*M2) - (MZ*MZ))*(wZ*wZ))) + 
                   wZ*(-(aZAI*(gL - gR)*(M1 - M2)*(M1 + M2)*
                         ((M1*M1)*(M2*M2) - 
                         (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))) - 
                      aZAdR*(gL + gR)*
                       ((M1*M1*M1*M1)*(M2*M2) + 
                         (M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         (M1*M1)*
                         ((M2*M2*M2*M2) - 4*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                         (MZ*MZ)*(wZ*wZ)))))) + 
             (((aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gL + 
                   (aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gR
)*(M1*M1) + ((aAR*(aZAdR + aZAI) + (aAdR + aAI)*(aZAdI - aZAR))*gL + 
                   (aAR*(-aZAdR + aZAI) + (aAdR - aAI)*(aZAdI + aZAR))*gR
)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C34*C56)))/4096. + 
  ((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) - 
       6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) - 6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*
        (C46*C46) + 6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) + 
       6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) + 4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*
        (C46*C46) - 4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*
        (MZ*MZ)*(C35*C35)*(C46*C46) + 
       6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*
        (MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*
        (MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) - 2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*
        (C46*C46) + 2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) + 
       2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*
        (C35*C35)*(C46*C46) - 
       2*((aZAdI*aZAdI) + (aZAdR*aZAdR) - (aZAI*aZAI) - (aZAR*aZAR))*
        (2*gL*gR*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (MZ*MZ)*(wZ*wZ)) + 
          (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
          (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
             (M1*M1)*(M2*M2)*(MZ*MZ)*
              (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
             (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                (MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56) + 
       C34*(((((aZAdR-aZAI)*(aZAdR-aZAI)) + ((aZAdI+aZAR)*(aZAdI+aZAR)))*
              (gL*gL) + (((aZAdR+aZAI)*(aZAdR+aZAI)) + ((aZAdI-aZAR)*(aZAdI-aZAR)))*
              (gR*gR))*((MZ*MZ)*(wZ*wZ)*
              ((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C35*C35) + 
          (-2*aZAdR*aZAI*(gL - gR)*(gL + gR)*(M1 - M2)*(M1 + M2)*
              (MZ*MZ)*((M1*M1)*
                 (2*(M2*M2) - (MZ*MZ) - (wZ*wZ)) - 
                (M2*M2)*((MZ*MZ) + (wZ*wZ))) + 
             2*aZAdI*aZAR*(gL - gR)*(gL + gR)*(M1 - M2)*(M1 + M2)*
              (MZ*MZ)*((M1*M1)*
                 (2*(M2*M2) - (MZ*MZ) - (wZ*wZ)) - 
                (M2*M2)*((MZ*MZ) + (wZ*wZ))) + 
             (aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             (aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))) + 
             ((aZAI*aZAI) + (aZAR*aZAR))*
              (4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ)))))*(C45*C45) + 
          ((((aZAdR+aZAI)*(aZAdR+aZAI)) + ((aZAdI-aZAR)*(aZAdI-aZAR)))*(gL*gL) + 
             (((aZAdR-aZAI)*(aZAdR-aZAI)) + ((aZAdI+aZAR)*(aZAdI+aZAR)))*(gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*(C46*C46) + 
          2*((aZAdI*aZAdI) + (aZAdR*aZAdR) - (aZAI*aZAI) - (aZAR*aZAR))*
           (4*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46)*
        C56 + 4*(aZAdI*aZAI + aZAdR*aZAR)*E3456*
        ((2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C36*C45 
- (2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 
- ((gL-gR)*(gL-gR))*(M1*M1)*(M2*M2)*
           ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + (MZ*MZ)*(wZ*wZ))*
           C34*C56) + 
       (C36*C36)*(-2*((aZAdI*aZAdI) + (aZAdR*aZAdR) - (aZAI*aZAI) - 
             (aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*(C45*C45) + 
          (2*aZAdR*aZAI*(gL - gR)*(gL + gR)*(M1 - M2)*(M1 + M2)*
              (MZ*MZ)*((M1*M1)*
                 (2*(M2*M2) - (MZ*MZ) - (wZ*wZ)) - 
                (M2*M2)*((MZ*MZ) + (wZ*wZ))) - 
             2*aZAdI*aZAR*(gL - gR)*(gL + gR)*(M1 - M2)*(M1 + M2)*
              (MZ*MZ)*((M1*M1)*
                 (2*(M2*M2) - (MZ*MZ) - (wZ*wZ)) - 
                (M2*M2)*((MZ*MZ) + (wZ*wZ))) + 
             (aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))) + 
             (aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*
                    (2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + (MZ*MZ*MZ*MZ) + 
                      (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))) + 
             ((aZAI*aZAI) + (aZAR*aZAR))*
              (4*gL*gR*(M1*M1)*(M2*M2)*
                 ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (MZ*MZ)*(wZ*wZ)) + 
                (gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
                (gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ) + 
                   (M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                   (M1*M1*M1*M1)*(2*(M2*M2*M2*M2) - 2*(M2*M2)*(MZ*MZ) + 
                      (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ)))))*C34*
           C56) + 2*((aZAdI*aZAdI) + (aZAdR*aZAdR) - (aZAI*aZAI) - 
          (aZAR*aZAR))*C36*C45*
        (2*(2*gL*gR*(M1*M1)*(M2*M2)*
              ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (MZ*MZ)*(wZ*wZ)) + 
             (gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))) + 
             (gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                (M1*M1)*(M2*M2)*(MZ*MZ)*
                 (-3*(M2*M2) + (MZ*MZ) + (wZ*wZ)) + 
                (M1*M1*M1*M1)*(3*(M2*M2*M2*M2) - 3*(M2*M2)*(MZ*MZ) + 
                   (MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ))))*C35*C46 + 
          ((gL*gL) + (gR*gR))*
           ((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2)) + 
             pow(-2*(M1*M1)*(M2*M2) + 
               ((M1*M1) + (M2*M2))*(MZ*MZ),2))*C34*C56)))/
   8192. - (el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (2*aZAdR*aZdI*gR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*gR*MZ*wZ*(gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*gR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*gR*MZ*wZ*(gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*MZ*wZ*(gL*gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*MZ*wZ*(gL*gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*MZ*wZ*(gL*gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*MZ*wZ*(gL*gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*gL*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*gL*MZ*wZ*(gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*gL*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*gL*MZ*wZ*(gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*MZ*wZ*(gR*gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*MZ*wZ*(gR*gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*MZ*wZ*(gR*gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*MZ*wZ*(gR*gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*gR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*gR*MZ*wZ*(gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*gR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*gR*MZ*wZ*(gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*MZ*wZ*(gL*gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*MZ*wZ*(gL*gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*MZ*wZ*(gL*gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*MZ*wZ*(gL*gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*gL*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*gL*MZ*wZ*(gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*gL*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*gL*MZ*wZ*(gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aZAdR*aZdI*MZ*wZ*(gR*gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aZAdI*aZdR*MZ*wZ*(gR*gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAR*aZI*MZ*wZ*(gR*gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aZAI*aZR*MZ*wZ*(gR*gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aZAdI*aZdI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aZAdR*aZdR*gR*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aZAI*aZI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aZAR*aZR*gR*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aZAdR*aZdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aZAI*aZI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aZAdI*aZdI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aZAdR*aZdR*gL*(gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aZAI*aZI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aZAR*aZR*gL*(gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aZAdR*aZdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aZAI*aZI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aZAdI*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aZAdR*aZdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aZAI*aZI*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aZAR*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*(gL + gR)*((gL*gL) + (gR*gR))*
        ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*wZ*
           ((M1*M1) + (M2*M2)) + 
          (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
           (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
        (C34*C34)*(C56*C56) - 
       2*ahI*aZAI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       2*ahR*aZAR*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       2*ahI*aZAI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       2*ahR*aZAR*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAdI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAdR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       ahI*aZAdI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahR*aZAdR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       ahI*aZAdI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahR*aZAdR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAdI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAdR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       ahR*aZAdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahI*aZAdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahR*aZAdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 - ahI*aZAdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       ahR*aZAdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahI*aZAdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 + 
       ahI*aZAI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*
        C36 + ahR*aZAR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C45*C45)*C36 - 
       2*ahI*aZAI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       2*ahR*aZAR*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       2*ahI*aZAI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       2*ahR*aZAR*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       ahI*aZAdI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahR*aZAdR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAdI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAdR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAdI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAdR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 - 
       ahI*aZAdI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahR*aZAdR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 - 
       ahR*aZAdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahI*aZAdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 - 
       ahR*aZAdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahI*aZAdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahR*aZAdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 - ahI*aZAdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 + 
       ahI*aZAI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*
        C45 + ahR*aZAR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        (C36*C36)*C45 - 
       2*ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + 2*ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 + 
       2*ahI*aZAI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + 2*ahR*aZAR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 + 
       2*ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 - 2*ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 + 
       2*ahI*aZAI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + 2*ahR*aZAR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       ahI*aZAdI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAdR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - ahR*aZAI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahI*aZAR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + ahI*aZAdI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 + ahR*aZAdR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahR*aZAI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + ahI*aZAR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - ahI*aZAdI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahR*aZAdR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*
        C45*C46 + ahI*aZAR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahI*aZAdI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 + ahR*aZAdR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*
        C45*C46 - ahR*aZAI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahI*aZAR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 + ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahI*aZAI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahI*aZAI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - ahR*aZAR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 + 
       ahR*aZAdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahI*aZAdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - ahI*aZAI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahR*aZAR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + ahI*aZAdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       ahI*aZAI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - ahR*aZAR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + C34*
        (-2*gL*gR*(2*aZAdI*aZdI*gL*(M1*M1)*(M2*M2) + 
             2*aZAdR*aZdR*gL*(M1*M1)*(M2*M2) + 
             2*aZAR*aZR*gL*(M1*M1)*(M2*M2) + 
             2*aZAdI*aZdI*gR*(M1*M1)*(M2*M2) + 
             2*aZAdR*aZdR*gR*(M1*M1)*(M2*M2) + 
             2*aZAR*aZR*gR*(M1*M1)*(M2*M2) + 
             MZ*wZ*((((aZAdI + aZAR)*(-aZdR + aZI) + 
                      aZAdR*(aZdI + aZR))*gL + 
                   (-(aZAdI*(aZdR + aZI)) + aZAR*(aZdR + aZI) + 
                      aZAdR*(aZdI - aZR))*gR)*(M1*M1) + 
                ((-(aZAdI*(aZdR + aZI)) + aZAR*(aZdR + aZI) + 
                      aZAdR*(aZdI - aZR))*gL + 
                   ((aZAdI + aZAR)*(-aZdR + aZI) + 
                      aZAdR*(aZdI + aZR))*gR)*(M2*M2)) - 
             aZAdI*aZdI*gL*(M1*M1)*(MZ*MZ) - 
             aZAR*aZdI*gL*(M1*M1)*(MZ*MZ) - 
             aZAdR*aZdR*gL*(M1*M1)*(MZ*MZ) + 
             aZAdR*aZI*gL*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZR*gL*(M1*M1)*(MZ*MZ) - 
             aZAR*aZR*gL*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZdI*gR*(M1*M1)*(MZ*MZ) + 
             aZAR*aZdI*gR*(M1*M1)*(MZ*MZ) - 
             aZAdR*aZdR*gR*(M1*M1)*(MZ*MZ) - 
             aZAdR*aZI*gR*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZR*gR*(M1*M1)*(MZ*MZ) - 
             aZAR*aZR*gR*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZdI*gL*(M2*M2)*(MZ*MZ) + 
             aZAR*aZdI*gL*(M2*M2)*(MZ*MZ) - 
             aZAdR*aZdR*gL*(M2*M2)*(MZ*MZ) - 
             aZAdR*aZI*gL*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZR*gL*(M2*M2)*(MZ*MZ) - 
             aZAR*aZR*gL*(M2*M2)*(MZ*MZ) - 
             aZAdI*aZdI*gR*(M2*M2)*(MZ*MZ) - 
             aZAR*aZdI*gR*(M2*M2)*(MZ*MZ) - 
             aZAdR*aZdR*gR*(M2*M2)*(MZ*MZ) + 
             aZAdR*aZI*gR*(M2*M2)*(MZ*MZ) - 
             aZAdI*aZR*gR*(M2*M2)*(MZ*MZ) - 
             aZAR*aZR*gR*(M2*M2)*(MZ*MZ) + 
             aZAI*(MZ*(aZdR*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ - 
                   wZ*(aZdI*(gL - gR)*(M1 - M2)*(M1 + M2) + 
                      aZR*(gL + gR)*((M1*M1) + (M2*M2)))) + 
                aZI*(gL + gR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ))))*(C36*C36) 
+ 2*gL*gR*(-2*aZAdI*aZdI*gL*(M1*M1)*(M2*M2) - 
             2*aZAdR*aZdR*gL*(M1*M1)*(M2*M2) - 
             2*aZAR*aZR*gL*(M1*M1)*(M2*M2) - 
             2*aZAdI*aZdI*gR*(M1*M1)*(M2*M2) - 
             2*aZAdR*aZdR*gR*(M1*M1)*(M2*M2) - 
             2*aZAR*aZR*gR*(M1*M1)*(M2*M2) + 
             MZ*wZ*((((aZAdI - aZAR)*(aZdR + aZI) + 
                      aZAdR*(-aZdI + aZR))*gL - 
                   ((aZAdI + aZAR)*(-aZdR + aZI) + 
                      aZAdR*(aZdI + aZR))*gR)*(M1*M1) - 
                (((aZAdI + aZAR)*(-aZdR + aZI) + aZAdR*(aZdI + aZR))*
                    gL + (-(aZAdI*(aZdR + aZI)) + 
                      aZAR*(aZdR + aZI) + aZAdR*(aZdI - aZR))*gR)*
                 (M2*M2)) + aZAdI*aZdI*gL*(M1*M1)*(MZ*MZ) - 
             aZAR*aZdI*gL*(M1*M1)*(MZ*MZ) + 
             aZAdR*aZdR*gL*(M1*M1)*(MZ*MZ) + 
             aZAdR*aZI*gL*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZR*gL*(M1*M1)*(MZ*MZ) + 
             aZAR*aZR*gL*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZdI*gR*(M1*M1)*(MZ*MZ) + 
             aZAR*aZdI*gR*(M1*M1)*(MZ*MZ) + 
             aZAdR*aZdR*gR*(M1*M1)*(MZ*MZ) - 
             aZAdR*aZI*gR*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZR*gR*(M1*M1)*(MZ*MZ) + 
             aZAR*aZR*gR*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZdI*gL*(M2*M2)*(MZ*MZ) + 
             aZAR*aZdI*gL*(M2*M2)*(MZ*MZ) + 
             aZAdR*aZdR*gL*(M2*M2)*(MZ*MZ) - 
             aZAdR*aZI*gL*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZR*gL*(M2*M2)*(MZ*MZ) + 
             aZAR*aZR*gL*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZdI*gR*(M2*M2)*(MZ*MZ) - 
             aZAR*aZdI*gR*(M2*M2)*(MZ*MZ) + 
             aZAdR*aZdR*gR*(M2*M2)*(MZ*MZ) + 
             aZAdR*aZI*gR*(M2*M2)*(MZ*MZ) - 
             aZAdI*aZR*gR*(M2*M2)*(MZ*MZ) + 
             aZAR*aZR*gR*(M2*M2)*(MZ*MZ) + 
             aZAI*(MZ*(aZdR*(gL - gR)*(M1 - M2)*(M1 + M2)*MZ + 
                   wZ*(aZdI*(gL - gR)*(-(M1*M1) + (M2*M2)) + 
                      aZR*(gL + gR)*((M1*M1) + (M2*M2)))) + 
                aZI*(gL + gR)*
                 (-2*(M1*M1)*(M2*M2) + 
                   ((M1*M1) + (M2*M2))*(MZ*MZ))))*(C45*C45) 
+ gL*gR*(MZ*MZ)*((gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
              (-(ahR*aZAdI*MZ) + ahI*aZAdR*MZ + ahI*aZAdI*wZ + 
                ahR*aZAdR*wZ) + 
             aZAI*(gL + gR)*(-2*ahI*(M1*M1)*(M2*M2) + 
                ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
             aZAR*(gL + gR)*(2*ahR*(M1*M1)*(M2*M2) + 
                ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45 + 
          C36*(gL*gR*(MZ*MZ)*
              ((-gL + gR)*(M1 - M2)*(M1 + M2)*MZ*
                 (-(ahR*aZAdI*MZ) + ahI*aZAdR*MZ + ahI*aZAdI*wZ + 
                   ahR*aZAdR*wZ) + 
                aZAI*(gL + gR)*
                 (-2*ahI*(M1*M1)*(M2*M2) + 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAR*(gL + gR)*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) + 
             4*((gL*gL*gL) + (gR*gR*gR))*
              ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*
                 wZ*((M1*M1) + (M2*M2)) + 
                (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C45) + 
          C46*((MZ*MZ)*
              (-(aZAdR*((gL*gL*gL) - (gR*gR*gR))*
                   (2*ahI*(M1*M1)*(M2*M2) - 
                     ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                     ahI*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
                aZAI*((gL*gL*gL) + (gR*gR*gR))*
                 (2*ahI*(M1*M1)*(M2*M2) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                ((aZAdI - aZAR)*(gL*gL*gL) - (aZAdI + aZAR)*(gR*gR*gR))*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) + 
             2*(-2*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2) + 
                2*aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2) + 
                2*aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
                2*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
                2*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
                2*aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
                2*aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
                2*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
                MZ*wZ*((aZAdI - aZAR)*(aZdR + aZI)*(gL*gL*gL) - 
                   (aZAdI + aZAR)*(-aZdR + aZI)*(gR*gR*gR))*
                 ((M1*M1) + (M2*M2)) + 
                aZAdR*MZ*wZ*((-aZdI + aZR)*(gL*gL*gL) - 
                   (aZdI + aZR)*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
                aZAI*MZ*wZ*((-aZdI + aZR)*(gL*gL*gL) + 
                   (aZdI + aZR)*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
                aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ) - 
                aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ) - 
                aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
                aZAR*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
                aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                aZAR*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
                aZAdI*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ) - 
                aZAR*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ) - 
                aZAdI*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
                aZAR*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
                aZAdI*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
                aZAR*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
                aZAdI*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
                aZAR*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ) - 
                aZAdR*((aZdR + aZI)*(gL*gL*gL) + (aZdR - aZI)*(gR*gR*gR))*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAI*((aZdR + aZI)*(gL*gL*gL) + (-aZdR + aZI)*(gR*gR*gR))*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46))*
        C56 + E3456*
        (-2*ahI*aZAdI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C45 - 2*ahR*aZAdR*gR*(gL*gL)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*C45 - 
          2*ahI*aZAdI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C45 - 2*ahR*aZAdR*gL*(gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*C45 + 
          ahR*aZAdI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAdR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          ahR*aZAR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAdI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAdR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          ahI*aZAI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAdI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAdR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          ahI*aZAI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          ahR*aZAdI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAdR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          ahI*aZAI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 - 
          ahR*aZAR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          ahI*aZAdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 - 
          ahI*aZAR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 - 
          ahR*aZAI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 - 
          ahR*aZAI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahI*aZAdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          ahR*aZAI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 - 
          ahI*aZAR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          C36*(gL*gR*(MZ*MZ)*
              ((gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
                 (-(ahR*aZAI*MZ) + ahI*aZAR*MZ + ahI*aZAI*wZ + 
                   ahR*aZAR*wZ) + 
                aZAdI*(gL + gR)*
                 (-2*ahI*(M1*M1)*(M2*M2) + 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAdR*(gL + gR)*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
             2*(gL + gR)*((gL*gL) + (gR*gR))*
              ((aZAR*aZdI - aZAI*aZdR + aZAdR*aZI - aZAdI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2)) + 
                (aZAI*aZdI + aZAR*aZdR + aZAdI*aZI + aZAdR*aZR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C45) + 
          2*ahI*aZAdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahR*aZAdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahR*aZAI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          2*ahI*aZAR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahI*aZAdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahR*aZAdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          2*ahR*aZAI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          2*ahI*aZAR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          ahR*aZAdI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAdR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          ahR*aZAR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAdI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAdR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          ahI*aZAI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAdI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAdR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          ahR*aZAR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAdI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          ahI*aZAdR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          ahI*aZAI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          ahR*aZAR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          ahI*aZAdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 + 
          ahI*aZAR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 + 
          ahR*aZAI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          ahI*aZAR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahR*aZAdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          ahR*aZAI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          ahI*aZAR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          C35*(-((MZ*MZ)*
                (-(aZAR*((gL*gL*gL) - (gR*gR*gR))*
                     (2*ahI*(M1*M1)*(M2*M2) - 
                       ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                       ahI*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
                  aZAdI*((gL*gL*gL) + (gR*gR*gR))*
                   (2*ahI*(M1*M1)*(M2*M2) - 
                     ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                     ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                  (-((aZAdR - aZAI)*(gL*gL*gL)) - 
                     (aZAdR + aZAI)*(gR*gR*gR))*
                   (2*ahR*(M1*M1)*(M2*M2) + 
                     ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                     ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))) + 
             2*(gL + gR)*((gL*gL) + (gR*gR))*
              ((aZAR*aZdI - aZAI*aZdR + aZAdR*aZI - aZAdI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2)) + 
                (aZAI*aZdI + aZAR*aZdR + aZAdI*aZI + aZAdR*aZR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46) + 
          2*(gL + gR)*((gL-gR)*(gL-gR))*
           ((aZAR*aZdI - aZAI*aZdR + aZAdR*aZI - aZAdI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2)) + 
             (aZAI*aZdI + aZAR*aZdR + aZAdI*aZI + aZAdR*aZR)*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
           C34*C56) + 
       (C35*C35)*(-2*(gL + gR)*((gL*gL) + (gR*gR))*
           ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2)) + 
             (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ))
)*(C46*C46) + (MZ*MZ)*
           (aZAdR*((gL*gL*gL) - (gR*gR*gR))*
              (2*ahI*(M1*M1)*(M2*M2) - 
                ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
             aZAI*((gL*gL*gL) + (gR*gR*gR))*
              (2*ahI*(M1*M1)*(M2*M2) - 
                ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
             (-((aZAdI + aZAR)*(gL*gL*gL)) - (-aZAdI + aZAR)*(gR*gR*gR))*
              (2*ahR*(M1*M1)*(M2*M2) + 
                ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46 + 
          2*(-2*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             2*aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             2*aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             2*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2) - 
             2*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
             2*aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2) + 
             2*aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
             2*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2) - 
             MZ*wZ*((aZAdI + aZAR)*(-aZdR + aZI)*(gL*gL*gL) - 
                (aZAdI - aZAR)*(aZdR + aZI)*(gR*gR*gR))*
              ((M1*M1) + (M2*M2)) - 
             aZAdR*MZ*wZ*((aZdI + aZR)*(gL*gL*gL) + 
                (aZdI - aZR)*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
             aZAI*MZ*wZ*((aZdI + aZR)*(gL*gL*gL) + 
                (-aZdI + aZR)*(gR*gR*gR))*((M1*M1) + (M2*M2)) + 
             aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             aZAR*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ) - 
             aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ) - 
             aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
             aZAR*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ) + 
             aZAdI*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             aZAR*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             aZAR*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ) + 
             aZAdI*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ) - 
             aZAR*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ) - 
             aZAdI*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
             aZAR*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ) + 
             aZAdR*((-aZdR + aZI)*(gL*gL*gL) - (aZdR + aZI)*(gR*gR*gR))*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)) 
- aZAI*((-aZdR + aZI)*(gL*gL*gL) + (aZdR + aZI)*(gR*gR*gR))*
              (2*(M1*M1)*(M2*M2) - ((M1*M1) + (M2*M2))*(MZ*MZ)))*
           C34*C56) - 
       C35*(-2*ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 2*ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) + 
          2*ahI*aZAI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 2*ahR*aZAR*(gL*gL*gL)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) + 
          2*ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) - 2*ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) + 
          2*ahI*aZAI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + 2*ahR*aZAR*(gR*gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          ahI*aZAdI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAdR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAdI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          ahR*aZAdR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAdI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAdR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAdI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahR*aZAdR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46) + 
          ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          ahR*aZAdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          ahI*aZAdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahI*aZAI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) - 
          ahR*aZAR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46) + 
          gL*gR*(MZ*MZ)*((gL - gR)*(M1 - M2)*(M1 + M2)*MZ*
              (-(ahR*aZAdI*MZ) + ahI*aZAdR*MZ + ahI*aZAdI*wZ + 
                ahR*aZAdR*wZ) + 
             aZAI*(gL + gR)*(-2*ahI*(M1*M1)*(M2*M2) + 
                ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
             aZAR*(gL + gR)*(2*ahR*(M1*M1)*(M2*M2) + 
                ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))*C45*C46 
+ C36*(gL*gR*(MZ*MZ)*((-gL + gR)*(M1 - M2)*(M1 + M2)*MZ*
                 (-(ahR*aZAdI*MZ) + ahI*aZAdR*MZ + ahI*aZAdI*wZ + 
                   ahR*aZAdR*wZ) + 
                aZAI*(gL + gR)*
                 (-2*ahI*(M1*M1)*(M2*M2) + 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) + 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAR*(gL + gR)*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ)))*C46 + 
             C45*((MZ*MZ)*
                 (aZAdR*((gL*gL*gL) - (gR*gR*gR))*
                    (2*ahI*(M1*M1)*(M2*M2) - 
                      ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                      ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                   aZAI*((gL*gL*gL) + (gR*gR*gR))*
                    (2*ahI*(M1*M1)*(M2*M2) - 
                      ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                      ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                   (-((aZAdI + aZAR)*(gL*gL*gL)) - 
                      (-aZAdI + aZAR)*(gR*gR*gR))*
                    (2*ahR*(M1*M1)*(M2*M2) + 
                      ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                      ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) - 
                4*(gL + gR)*((gL*gL) + (gR*gR))*
                 ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*
                    wZ*((M1*M1) + (M2*M2)) + 
                   (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
                    (2*(M1*M1)*(M2*M2) - 
                      ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46)) - 
          C34*((MZ*MZ)*
              (aZAdR*((gL*gL*gL) - (gR*gR*gR))*
                 (2*ahI*(M1*M1)*(M2*M2) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) - 
                aZAI*((gL*gL*gL) + (gR*gR*gR))*
                 (2*ahI*(M1*M1)*(M2*M2) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahI*((M1*M1) + (M2*M2))*(MZ*MZ)) + 
                (-((aZAdI + aZAR)*(gL*gL*gL)) - (-aZAdI + aZAR)*(gR*gR*gR))*
                 (2*ahR*(M1*M1)*(M2*M2) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2)) - 
                   ahR*((M1*M1) + (M2*M2))*(MZ*MZ))) + 
             4*gL*gR*(gL + gR)*
              ((-(aZAdR*aZdI) + aZAdI*aZdR + aZAR*aZI - aZAI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2)) + 
                (-(aZAdI*aZdI) - aZAdR*aZdR + aZAI*aZI + aZAR*aZR)*
                 (2*(M1*M1)*(M2*M2) - 
                   ((M1*M1) + (M2*M2))*(MZ*MZ)))*C46)*C56)
))/8192. - ((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (4*aAdR*aZdI*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*(C45*C45) - 
       4*aAdI*aZdR*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*
        (C45*C45) - 4*aAR*aZI*gL*gR*MZ*wZ*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       4*aAI*aZR*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*(C45*C45) + 
       2*aAdR*aZdI*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aAdI*aZdR*MZ*wZ*(gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aAR*aZI*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aAI*aZR*MZ*wZ*(gL*gL)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       2*aAdR*aZdI*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) - 2*aAdI*aZdR*MZ*wZ*(gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) - 
       2*aAR*aZI*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*
        (C45*C45) + 2*aAI*aZR*MZ*wZ*(gR*gR)*(M1*M1)*
        (C36*C36)*(C45*C45) + 
       4*aAdR*aZdI*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aAdI*aZdR*gL*gR*MZ*wZ*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aAR*aZI*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*(C45*C45) + 
       4*aAI*aZR*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*(C45*C45) + 
       2*aAdR*aZdI*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aAdI*aZdR*MZ*wZ*(gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aAR*aZI*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aAI*aZR*MZ*wZ*(gL*gL)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aAdR*aZdI*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aAdI*aZdR*MZ*wZ*(gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aAR*aZI*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aAI*aZR*MZ*wZ*(gR*gR)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       4*aAdI*aZdI*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 4*aAdR*aZdR*gL*gR*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aAI*aZI*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 4*aAR*aZR*gL*gR*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aAdI*aZdI*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aAdR*aZdR*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aAI*aZI*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aAR*aZR*(gL*gL)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) + 
       2*aAdI*aZdI*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) + 2*aAdR*aZdR*(gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       2*aAI*aZI*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*
        (C45*C45) - 2*aAR*aZR*(gR*gR)*(M1*M1)*(M2*M2)*
        (C36*C36)*(C45*C45) - 
       4*aAdI*aZdI*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 4*aAdR*aZdR*gL*gR*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       4*aAI*aZI*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 4*aAR*aZR*gL*gR*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gL*gL)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gR*gR)*(M1*M1)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       4*aAdI*aZdI*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 4*aAdR*aZdR*gL*gR*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       4*aAI*aZI*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 4*aAR*aZR*gL*gR*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gL*gL)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gR*gR)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*(C45*C45) - 
       8*aAdR*aZdI*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       8*aAdI*aZdR*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       8*aAR*aZI*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       8*aAI*aZR*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAdR*aZdI*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) + 4*aAdI*aZdR*wZ*(gL*gL)*(MZ*MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       4*aAR*aZI*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAI*aZR*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAdR*aZdI*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*
        (C45*C45) + 4*aAdI*aZdR*wZ*(gR*gR)*(MZ*MZ*MZ)*
        (C36*C36)*(C45*C45) + 
       4*aAR*aZI*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAI*aZR*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       4*aAdI*aZdI*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       4*aAdR*aZdR*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAI*aZI*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAR*aZR*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       2*aAdI*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       2*aAdR*aZdR*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       2*aAI*aZI*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       2*aAR*aZR*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       2*aAdI*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) + 
       2*aAdR*aZdR*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       2*aAI*aZI*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       2*aAR*aZR*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45) - 
       4*aAdI*aZdI*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) - 4*aAdR*aZdR*gL*gR*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) + 
       4*aAI*aZI*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) + 4*aAR*aZR*gL*gR*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gL*gL)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gL*gL)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gL*gL)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gL*gL)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) - 
       2*aAdI*aZdI*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) - 2*aAdR*aZdR*(gR*gR)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) + 
       2*aAI*aZI*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*
        (C45*C45) + 2*aAR*aZR*(gR*gR)*(MZ*MZ)*(wZ*wZ)*
        (C36*C36)*(C45*C45) - 
       2*((gL+gR)*(gL+gR))*((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*
           (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
          (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
           ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
          (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*(wZ*wZ))*
        (C34*C34)*(C56*C56) - 
       2*aAI*ahI*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*
        C36 - 2*aAR*ahR*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C45*C45)*C36 - 
       2*aAR*ahI*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahR*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36 - 
       2*aAR*ahI*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahR*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahI*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAR*ahR*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahI*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAR*ahR*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       4*aAR*ahI*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       4*aAI*ahR*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 - 
       2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36 + 
       2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C45*C45)*C36 + 
       2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C45*C45)*C36 - 
       2*aAI*ahI*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*
        C45 - 2*aAR*ahR*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
        (C36*C36)*C45 - 
       2*aAR*ahI*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahR*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45 - 
       2*aAR*ahI*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahR*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahI*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAR*ahR*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahI*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAR*ahR*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       4*aAR*ahI*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 - 
       4*aAI*ahR*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 - 
       2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 - 
       2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45 + 
       2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C36*C36)*C45 + 
       2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C36*C36)*C45 + 
       aAdR*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + aAI*ahI*(gL*gL)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       aAdI*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + aAR*ahR*(gL*gL)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       aAdR*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + aAI*ahI*(gR*gR)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 + 
       aAdI*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*
        C45*C46 + aAR*ahR*(gR*gR)*(M1*M1)*(M2*M2)*
        (MZ*MZ)*C36*C45*C46 - 
       aAdI*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + aAR*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - aAdR*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAI*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 + aAdI*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 + aAR*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       aAdR*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*
        C46 - aAI*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*
        C45*C46 - aAdI*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       aAR*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 - aAdR*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*
        C45*C46 - aAI*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 + 
       aAdI*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 + aAR*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*
        C45*C46 + aAdR*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAI*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*
        C46 - aAdR*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAI*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 + 
       aAdI*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - aAR*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAdR*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAI*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - aAdI*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAR*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAdR*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - aAI*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAdI*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAR*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 + aAdR*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAI*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
        C36*C45*C46 - 
       aAdI*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*
        C46 - aAR*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 2*aAdI*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 2*aAR*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 2*aAdR*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 2*aAI*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 2*aAdI*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 2*aAR*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - 2*aAdR*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + 2*aAI*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 + aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*
        C45*C46 - aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        C36*C45*C46 - 
       aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*
        C46 + aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*
        C45*C46 - aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        C36*C45*C46 + 
       aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*
        C46 - aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*
        C45*C46 - aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
        C36*C45*C46 - 
       aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*
        C46 + C34*(-4*gL*gR*
           ((aAdI*aZdI + aAdR*aZdR + aAI*aZI + aAR*aZR)*(M1 - MZ)*
              (M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (aAdR*aZdI - aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAdI*aZdI + aAdR*aZdR + aAI*aZI + aAR*aZR)*(MZ*MZ)*
              (wZ*wZ))*(C36*C36) - 
          4*gL*gR*((aAdI*aZdI + aAdR*aZdR + aAI*aZI + aAR*aZR)*
              (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (aAdR*aZdI - aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAdI*aZdI + aAdR*aZdR + aAI*aZI + aAR*aZR)*(MZ*MZ)*
              (wZ*wZ))*(C45*C45) - 
          2*gL*gR*(MZ*MZ)*((aAI*ahI + aAR*ahR)*(M1 - MZ)*(M2 - MZ)*
              (M1 + MZ)*(M2 + MZ) + 
             (aAR*ahI - aAI*ahR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAI*ahI + aAR*ahR)*(MZ*MZ)*(wZ*wZ))*C45 - 
          2*C36*(gL*gR*(MZ*MZ)*
              ((aAI*ahI + aAR*ahR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + 
                (aAR*ahI - aAI*ahR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAI*ahI + aAR*ahR)*(MZ*MZ)*(wZ*wZ)) - 
             2*((gL*gL) + (gR*gR))*
              ((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*
                 (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*
                 (wZ*wZ))*C45) + 
          C46*((MZ*MZ)*
              (-(aAdR*(gL - gR)*(gL + gR)*
                   (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                     ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                     ahI*(MZ*MZ)*(wZ*wZ))) + 
                aAI*((gL*gL) + (gR*gR))*
                 (ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   ahI*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                   ahI*(MZ*MZ)*(wZ*wZ)) + 
                ((aAdI - aAR)*(gL*gL) - (aAdI + aAR)*(gR*gR))*
                 (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahR*(MZ*MZ)*(wZ*wZ))) + 
             2*(-(aAdI*aZdI*(gL*gL)*(M1*M1)*(M2*M2)) + 
                aAR*aZdI*(gL*gL)*(M1*M1)*(M2*M2) + 
                aAdI*aZR*(gL*gL)*(M1*M1)*(M2*M2) - 
                aAR*aZR*(gL*gL)*(M1*M1)*(M2*M2) - 
                aAdI*aZdI*(gR*gR)*(M1*M1)*(M2*M2) - 
                aAR*aZdI*(gR*gR)*(M1*M1)*(M2*M2) - 
                aAdI*aZR*(gR*gR)*(M1*M1)*(M2*M2) - 
                aAR*aZR*(gR*gR)*(M1*M1)*(M2*M2) + 
                MZ*wZ*((aAdI - aAR)*(aZdR + aZI)*(gL*gL) - 
                   (aAdI + aAR)*(-aZdR + aZI)*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                aAdI*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ) - 
                aAR*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ) - 
                aAdI*aZR*(gL*gL)*(M1*M1)*(MZ*MZ) + 
                aAR*aZR*(gL*gL)*(M1*M1)*(MZ*MZ) + 
                aAdI*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                aAR*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                aAdI*aZR*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                aAR*aZR*(gR*gR)*(M1*M1)*(MZ*MZ) + 
                aAdI*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ) - 
                aAR*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ) - 
                aAdI*aZR*(gL*gL)*(M2*M2)*(MZ*MZ) + 
                aAR*aZR*(gL*gL)*(M2*M2)*(MZ*MZ) + 
                aAdI*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ) + 
                aAR*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ) + 
                aAdI*aZR*(gR*gR)*(M2*M2)*(MZ*MZ) + 
                aAR*aZR*(gR*gR)*(M2*M2)*(MZ*MZ) - 
                aAdI*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ) + 
                aAR*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ) + 
                aAdI*aZR*(gL*gL)*(MZ*MZ*MZ*MZ) - 
                aAR*aZR*(gL*gL)*(MZ*MZ*MZ*MZ) - 
                aAdI*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ) - 
                aAR*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ) - 
                aAdI*aZR*(gR*gR)*(MZ*MZ*MZ*MZ) - 
                aAR*aZR*(gR*gR)*(MZ*MZ*MZ*MZ) + 
                ((-aAdI + aAR)*(-aZdI + aZR)*(gL*gL) + 
                   (aAdI + aAR)*(aZdI + aZR)*(gR*gR))*(MZ*MZ)*
                 (wZ*wZ) + aAdR*
                 (MZ*wZ*((-aZdI + aZR)*(gL*gL) - 
                      (aZdI + aZR)*(gR*gR))*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   (M1 - MZ)*(M1 + MZ)*
                    ((aZdR + aZI)*(gL*gL) + (aZdR - aZI)*(gR*gR))*
                    (-(M2*M2) + (MZ*MZ)) + 
                   ((aZdR + aZI)*(gL*gL) + (aZdR - aZI)*(gR*gR))*
                    (MZ*MZ)*(wZ*wZ)) + 
                aAI*(MZ*wZ*((-aZdI + aZR)*(gL*gL) + 
                      (aZdI + aZR)*(gR*gR))*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   (M1 - MZ)*(M1 + MZ)*
                    ((aZdR + aZI)*(gL*gL) + (-aZdR + aZI)*(gR*gR))*
                    (-(M2*M2) + (MZ*MZ)) + 
                   ((aZdR + aZI)*(gL*gL) + (-aZdR + aZI)*(gR*gR))*
                    (MZ*MZ)*(wZ*wZ)))*C46))*C56 + 
       E3456*(-2*aAdI*ahI*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C45 - 2*aAdR*ahR*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*
           C45 - 2*aAdR*ahI*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*C45 + 
          2*aAdI*ahR*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*C45 - 
          2*aAdR*ahI*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          2*aAdI*ahR*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*C45 + 
          2*aAdI*ahI*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          2*aAdR*ahR*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*C45 + 
          2*aAdI*ahI*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          2*aAdR*ahR*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*C45 + 
          4*aAdR*ahI*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*C45 - 
          4*aAdI*ahR*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*C45 - 
          2*aAdI*ahI*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 - 
          2*aAdR*ahR*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 + 
          2*aAdI*ahI*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C45 + 
          2*aAdR*ahR*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C45 - 
          2*C36*(gL*gR*(MZ*MZ)*
              ((aAdI*ahI + aAdR*ahR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + (aAdR*ahI - aAdI*ahR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAdI*ahI + aAdR*ahR)*(MZ*MZ)*(wZ*wZ)) + 
             ((gL+gR)*(gL+gR))*((aAI*aZdI + aAR*aZdR + aAdI*aZI + 
                   aAdR*aZR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (aAR*aZdI - aAI*aZdR + aAdR*aZI - aAdI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*(MZ*MZ)*
                 (wZ*wZ))*C45) + 
          aAdI*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          aAR*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAdR*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAI*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAdI*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAR*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAdR*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 - 
          aAI*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46 + 
          aAdR*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          aAI*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          aAR*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          aAdR*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          aAI*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 - 
          aAR*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46 + 
          aAdR*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          aAI*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          aAR*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46 + 
          aAdR*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAI*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAR*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 + 
          aAR*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdR*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAI*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAR*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdR*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 + 
          aAI*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          aAR*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdR*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAI*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAR*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          aAdR*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 + 
          aAI*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46 - 
          2*aAdR*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 - 
          2*aAI*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          2*aAdI*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 - 
          2*aAR*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46 - 
          2*aAdR*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          2*aAI*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          2*aAdI*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          2*aAR*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAdI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 - 
          aAR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAdR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAdI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 + 
          aAdR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 - 
          aAI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46 - 
          aAdI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 + 
          aAR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAdR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAdI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 - 
          aAdR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 + 
          aAI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46 + 
          C35*((MZ*MZ)*
              (aAR*(gL - gR)*(gL + gR)*
                 (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahI*(MZ*MZ)*(wZ*wZ)) + 
                aAdI*((gL*gL) + (gR*gR))*
                 (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahI*(MZ*MZ)*(wZ*wZ)) + 
                ((aAdR - aAI)*(gL*gL) + (aAdR + aAI)*(gR*gR))*
                 (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahR*(MZ*MZ)*(wZ*wZ))) + 
             2*((gL+gR)*(gL+gR))*
              ((aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*(M1 - MZ)*
                 (M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (aAR*aZdI - aAI*aZdR + aAdR*aZI - aAdI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*(MZ*MZ)*
                 (wZ*wZ))*C46) + 
          2*((gL-gR)*(gL-gR))*((aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*
              (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (aAR*aZdI - aAI*aZdR + aAdR*aZI - aAdI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAI*aZdI + aAR*aZdR + aAdI*aZI + aAdR*aZR)*(MZ*MZ)*
              (wZ*wZ))*C34*C56) + 
       (C35*C35)*(-2*((gL+gR)*(gL+gR))*
           ((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*(M1 - MZ)*
              (M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
             (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*
              (wZ*wZ))*(C46*C46) + 
          (MZ*MZ)*(aAdR*(gL - gR)*(gL + gR)*
              (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                ahI*(MZ*MZ)*(wZ*wZ)) + 
             aAI*((gL*gL) + (gR*gR))*
              (ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                ahI*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                ahI*(MZ*MZ)*(wZ*wZ)) - 
             ((aAdI + aAR)*(gL*gL) + (-aAdI + aAR)*(gR*gR))*
              (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                ahR*(MZ*MZ)*(wZ*wZ)))*C46 + 
          2*(-(aAdI*aZdI*(gL*gL)*(M1*M1)*(M2*M2)) - 
             aAR*aZdI*(gL*gL)*(M1*M1)*(M2*M2) - 
             aAdI*aZR*(gL*gL)*(M1*M1)*(M2*M2) - 
             aAR*aZR*(gL*gL)*(M1*M1)*(M2*M2) - 
             aAdI*aZdI*(gR*gR)*(M1*M1)*(M2*M2) + 
             aAR*aZdI*(gR*gR)*(M1*M1)*(M2*M2) + 
             aAdI*aZR*(gR*gR)*(M1*M1)*(M2*M2) - 
             aAR*aZR*(gR*gR)*(M1*M1)*(M2*M2) - 
             MZ*wZ*((aAdI + aAR)*(-aZdR + aZI)*(gL*gL) - 
                (aAdI - aAR)*(aZdR + aZI)*(gR*gR))*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
             aAdI*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             aAR*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             aAdI*aZR*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             aAR*aZR*(gL*gL)*(M1*M1)*(MZ*MZ) + 
             aAdI*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ) - 
             aAR*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ) - 
             aAdI*aZR*(gR*gR)*(M1*M1)*(MZ*MZ) + 
             aAR*aZR*(gR*gR)*(M1*M1)*(MZ*MZ) + 
             aAdI*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             aAR*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             aAdI*aZR*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             aAR*aZR*(gL*gL)*(M2*M2)*(MZ*MZ) + 
             aAdI*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             aAR*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             aAdI*aZR*(gR*gR)*(M2*M2)*(MZ*MZ) + 
             aAR*aZR*(gR*gR)*(M2*M2)*(MZ*MZ) - 
             aAdI*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ) - 
             aAR*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ) - 
             aAdI*aZR*(gL*gL)*(MZ*MZ*MZ*MZ) - aAR*aZR*(gL*gL)*(MZ*MZ*MZ*MZ) - 
             aAdI*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             aAR*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             aAdI*aZR*(gR*gR)*(MZ*MZ*MZ*MZ) - aAR*aZR*(gR*gR)*(MZ*MZ*MZ*MZ) + 
             ((aAdI + aAR)*(aZdI + aZR)*(gL*gL) - 
                (aAdI - aAR)*(-aZdI + aZR)*(gR*gR))*(MZ*MZ)*(wZ*wZ) 
+ aAdR*((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ)*
                 ((-aZdR + aZI)*(gL*gL) - (aZdR + aZI)*(gR*gR)) - 
                MZ*wZ*((aZdI + aZR)*(gL*gL) + (aZdI - aZR)*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                ((aZdR - aZI)*(gL*gL) + (aZdR + aZI)*(gR*gR))*
                 (MZ*MZ)*(wZ*wZ)) + 
             aAI*(MZ*wZ*((aZdI + aZR)*(gL*gL) + 
                   (-aZdI + aZR)*(gR*gR))*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (M1 - MZ)*(M1 + MZ)*
                 ((-aZdR + aZI)*(gL*gL) + (aZdR + aZI)*(gR*gR))*
                 (-(M2*M2) + (MZ*MZ)) + 
                ((-aZdR + aZI)*(gL*gL) + (aZdR + aZI)*(gR*gR))*
                 (MZ*MZ)*(wZ*wZ)))*C34*C56) + 
       C35*(-(aAdR*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
             (C46*C46)) - 
          aAI*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + aAdI*ahR*(gL*gL)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          aAR*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          aAI*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) - aAdI*ahR*(gR*gR)*(M1*M1)*(M2*M2)*
           (MZ*MZ)*(C46*C46) - 
          aAR*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*
           (C46*C46) + aAdI*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) - aAR*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) + aAI*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) - aAR*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) + aAI*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*
           (C46*C46) + aAdI*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) - aAR*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) + aAI*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) - aAR*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) + aAI*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAI*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAR*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAI*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdI*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAR*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAI*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAR*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAI*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdI*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) + aAR*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*
           (C46*C46) - 2*aAdI*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + 2*aAR*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - 2*aAdR*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - 2*aAI*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + 2*aAdI*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + 2*aAR*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + 2*aAdR*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - 2*aAI*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) - aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*
           (C46*C46) + aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) - aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) - aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*
           (C46*C46) + 2*gL*gR*(MZ*MZ)*
           ((aAI*ahI + aAR*ahR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
             (aAR*ahI - aAI*ahR)*MZ*wZ*
              ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
             (aAI*ahI + aAR*ahR)*(MZ*MZ)*(wZ*wZ))*C45*C46 - 
          C36*(-2*gL*gR*(MZ*MZ)*
              ((aAI*ahI + aAR*ahR)*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*
                 (M2 + MZ) + (aAR*ahI - aAI*ahR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                (aAI*ahI + aAR*ahR)*(MZ*MZ)*(wZ*wZ))*C46 + 
             C45*((MZ*MZ)*
                 (aAdR*(gL - gR)*(gL + gR)*
                    (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                      ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                      ahI*(MZ*MZ)*(wZ*wZ)) + 
                   aAI*((gL*gL) + (gR*gR))*
                    (ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                      ahI*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                      ahI*(MZ*MZ)*(wZ*wZ)) - 
                   ((aAdI + aAR)*(gL*gL) + (-aAdI + aAR)*(gR*gR))*
                    (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                      ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                      ahR*(MZ*MZ)*(wZ*wZ))) - 
                4*((gL+gR)*(gL+gR))*
                 ((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*
                    (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
                    ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*
                    (wZ*wZ))*C46)) + 
          C34*((MZ*MZ)*
              (aAdR*(gL - gR)*(gL + gR)*
                 (ahI*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) - 
                   ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahI*(MZ*MZ)*(wZ*wZ)) + 
                aAI*((gL*gL) + (gR*gR))*
                 (ahR*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                   ahI*(M1 - MZ)*(M1 + MZ)*(-(M2*M2) + (MZ*MZ)) + 
                   ahI*(MZ*MZ)*(wZ*wZ)) - 
                ((aAdI + aAR)*(gL*gL) + (-aAdI + aAR)*(gR*gR))*
                 (ahR*(M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                   ahI*MZ*wZ*((M1*M1) + (M2*M2) - 2*(MZ*MZ)) - 
                   ahR*(MZ*MZ)*(wZ*wZ))) + 
             8*gL*gR*((-(aAdI*aZdI) - aAdR*aZdR + aAI*aZI + aAR*aZR)*
                 (M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + 
                (-(aAdR*aZdI) + aAdI*aZdR + aAR*aZI - aAI*aZR)*MZ*wZ*
                 ((M1*M1) + (M2*M2) - 2*(MZ*MZ)) + 
                (aAdI*aZdI + aAdR*aZdR - aAI*aZI - aAR*aZR)*(MZ*MZ)*
                 (wZ*wZ))*C46)*C56)))/8192. + 
  (pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
     pow((1.0/(s*s))*((M1*M1*M1*M1) - 2*(M1*M1)*(s + (M2*M2)) + 
         ((M2*M2-s)*(M2*M2-s))),0.5)*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
     (1.0/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*
     (-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)) - 
       (aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46) + 
       (aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46) + 
       (aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46) - 
       2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) - 
       2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) + 
       2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) + 
       2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46) - 
       (aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46) - 
       (aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46) + 
       (aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46) + 
       (aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46) + 
       (-(aZdI*aZdI) - (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*
        ((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56) - 
       ahR*aZdI*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35 + 
       ahI*aZdR*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35 + 
       ahI*aZI*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35 + 
       ahR*aZR*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35 + 
       ahR*aZdI*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35 - 
       ahI*aZdR*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35 + 
       ahI*aZI*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35 + 
       ahR*aZR*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35 + 
       ahR*aZdI*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 - 
       ahI*aZdR*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 + 
       ahI*aZI*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 + 
       ahR*aZR*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46 - 
       ahR*aZdI*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       ahI*aZdR*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       ahI*aZI*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       ahR*aZR*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46 + 
       (ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       (ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       (ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46 + 
       (ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46 - 
       2*ahI*aZI*(gL*gL)*(gR*gR)*(MZ*MZ)*C35*C45*
        C46 - 2*ahR*aZR*(gL*gL)*(gR*gR)*(MZ*MZ)*C35*
        C45*C46 + C34*
        (((((aZdR-aZI)*(aZdR-aZI)) + ((aZdI+aZR)*(aZdI+aZR)))*(gL*gL*gL*gL) + 
             (((aZdR+aZI)*(aZdR+aZI)) + ((aZdI-aZR)*(aZdI-aZR)))*(gR*gR*gR*gR))*
           (C35*C35) + ((((aZdR+aZI)*(aZdR+aZI)) + ((aZdI-aZR)*(aZdI-aZR)))*
              (gL*gL*gL*gL) + (((aZdR-aZI)*(aZdR-aZI)) + ((aZdI+aZR)*(aZdI+aZR)))*
              (gR*gR*gR*gR))*(C46*C46) + 
          2*(gL*gL)*(gR*gR)*C45*
           ((ahI*aZI + ahR*aZR)*(MZ*MZ) + 
             ((aZdI*aZdI) + (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*
              C45) + ((ahI*(aZdR + aZI) + ahR*(-aZdI + aZR))*
              (gL*gL*gL*gL) + (ahI*(-aZdR + aZI) + ahR*(aZdI + aZR))*
              (gR*gR*gR*gR))*(MZ*MZ)*C46 + 
          C35*(((ahI*(-aZdR + aZI) + ahR*(aZdI + aZR))*(gL*gL*gL*gL) + 
                (ahI*(aZdR + aZI) + ahR*(-aZdI + aZR))*(gR*gR*gR*gR))*
              (MZ*MZ) + 4*((aZdI*aZdI) + (aZdR*aZdR) - (aZI*aZI) - 
                (aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56 + 
       (C36*C36)*((-(aZdI*aZdI) - (aZdR*aZdR) + (aZI*aZI) + 
             (aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45) + 
          2*(ahI*aZI + ahR*aZR)*(gL*gL)*(gR*gR)*(MZ*MZ)*C45 + 
          2*((aZdI*aZdI) + (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*(gL*gL)*
           (gR*gR)*C34*C56) + 
       E3456*(2*C36*
           ((ahI*aZdI + ahR*aZdR)*(gL*gL)*(gR*gR)*(MZ*MZ) + 
             (aZdI*aZI + aZdR*aZR)*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C45) 
+ (MZ*MZ)*(2*(ahI*aZdI + ahR*aZdR)*(gL*gL)*(gR*gR)*C45 - 
             ((ahR*(aZdR + aZI) + ahI*(aZdI - aZR))*(gL*gL*gL*gL) + 
                (ahR*(aZdR - aZI) + ahI*(aZdI + aZR))*(gR*gR*gR*gR))*C46) 
+ C35*(((ahR*(-aZdR + aZI) - ahI*(aZdI + aZR))*(gL*gL*gL*gL) - 
                (ahR*(aZdR + aZI) + ahI*(aZdI - aZR))*(gR*gR*gR*gR))*(MZ*MZ) 
- 2*(aZdI*aZI + aZdR*aZR)*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46) - 
          2*(aZdI*aZI + aZdR*aZR)*((gL*gL-gR*gR)*(gL*gL-gR*gR))*C34*
           C56) + C36*
        (2*(ahI*aZI + ahR*aZR)*(gL*gL)*(gR*gR)*(MZ*MZ)*
           (C45*C45) + 2*(ahI*aZI + ahR*aZR)*(gL*gL)*(gR*gR)*
           (MZ*MZ)*(-(C35*C46) + C34*C56) + 
          C45*(2*((ahI*ahI) + (ahR*ahR))*(gL*gL)*(gR*gR)*
              (MZ*MZ*MZ*MZ) - ((ahI*(aZdR + aZI) + ahR*(-aZdI + aZR))*
                 (gL*gL*gL*gL) + (ahI*(-aZdR + aZI) + ahR*(aZdI + aZR))*
                 (gR*gR*gR*gR))*(MZ*MZ)*C46 + 
             C35*((-((ahI*(-aZdR + aZI) + ahR*(aZdI + aZR))*
                      (gL*gL*gL*gL)) - 
                   (ahI*(aZdR + aZI) + ahR*(-aZdI + aZR))*(gR*gR*gR*gR))*
                 (MZ*MZ) - 2*
                 (-(aZdI*aZdI) - (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*
                 ((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46) - 
             2*(-(aZdI*aZdI) - (aZdR*aZdR) + (aZI*aZI) + (aZR*aZR))*
              ((gL*gL*gL*gL) + (gR*gR*gR*gR))*C34*C56))))/8192.;
}
