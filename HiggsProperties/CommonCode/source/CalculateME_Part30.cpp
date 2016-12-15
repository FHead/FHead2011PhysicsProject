#include <cmath>
#include <iostream>
#include <complex>
using namespace std;

#include "CalculateME.h"
#include "AngleConversion.h"
#include "Constants.h"

double GetFullWithZPrime_A1VVR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(pow(g1VL,2) - pow(g1VR,2))*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      16*(pow(g1VL,2) + pow(g1VR,2))*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C36*C45 + C35*C46)))/262144.
   ;
}
double GetFullWithZPrime_A1VVR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) + 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C36*C45 + C35*C46) + 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C36*C45 + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A1VVR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (MZ*MZ*MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C36*C45 + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))
) + 4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A1VVR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*(g1VL + g1VR)*(g2VL - g2VR)*Mv*wV*E3456*(el*el)*
       (MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56) - 
      2*(g1VL - g1VR)*(g2VL + g2VR)*Mv*wV*E3456*(el*el)*
       (MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56) + 
      2*(g1VL + g1VR)*(g2VL + g2VR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g1VL - g1VR)*(g2VL - g2VR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1VVR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(pow(g1VL,2) + pow(g1VR,2))*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(pow(g1VL,2) - pow(g1VR,2))*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1VVR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(g2VL - g2VR)*(g1VL*gL + g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(g2VL + g2VR)*(g1VL*gL - g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(g1VL + g1VR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) - 
      4*el*(g1VL - g1VR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) + 
      4*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*
             C56))*(-(C36*C45*
            (C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
))*(-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1VVR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       (C35 + C36 - C45 - C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       (C35 - C36 + C45 - C46) - 
      8*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) - 
      8*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) + 
      8*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1VVR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56)) - 
      8*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))*(-(C36*C45*
            (C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))*(-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1VVR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*(g1VL + g1VR)*(g2VL + g2VR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) - 
      2*(g1VL - g1VR)*(g2VL - g2VR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      2*(g1VL - g1VR)*(g2VL + g2VR)*Mv*wV*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g1VL + g1VR)*(g2VL - g2VR)*Mv*wV*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1VVR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46) - 
      8*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)))/262144.
   ;
}
double GetFullWithZPrime_A1VVR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      4*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      4*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) - 4*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 4*el*(g2VL + g2VR)*(g1VL*gL - g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL - g1VR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL - g2VR)*(g1VL*gL + g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL + g1VR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1VVR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 + C45 + C46) - 
      8*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) - 
      8*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      8*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1VVR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) - 8*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*
       E3456*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 8*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) + 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C36*C45 + C35*C46) + 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C36*C45 + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(pow(g2VL,2) - pow(g2VR,2))*((gL*gL) - (gR*gR))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      16*(pow(g1VL,2) - pow(g1VR,2))*((gL*gL) - (gR*gR))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      16*(pow(g2VL,2) + pow(g2VR,2))*((gL*gL) + (gR*gR))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C36*C45 + C35*C46) + 
      16*(pow(g1VL,2) + pow(g1VR,2))*((gL*gL) + (gR*gR))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C36*C45 + C35*C46) + 
      32*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56)) + 
      32*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C36*C45 + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))))/262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) + 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C36*C45 + C35*C46) + 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C36*C45 + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*(g1VL + g1VR)*(gL - gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56) - 2*(g1VL - g1VR)*(gL + gR)*E3456*
       (el*el)*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56) - 2*(g2VL - g2VR)*(gL + gR)*E3456*
       (el*el)*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56)) - 
      2*(g2VL + g2VR)*(gL - gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56)) + 
      2*(g1VL + g1VR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g2VL + g2VR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g1VL - g1VR)*(gL - gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      2*(g2VL - g2VR)*(gL - gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       (C35 + C36 - C45 - C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       (C35 - C36 + C45 - C46) - 
      8*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) - 
      8*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) + 
      8*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(g2VL - g2VR)*Mv*wV*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46) - 
      4*el*(g1VL + g1VR)*Mv*wV*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46) - 
      4*el*(g2VL + g2VR)*Mv*wV*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 + C45 - C46) - 
      4*el*(g1VL - g1VR)*Mv*wV*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46) - 
      4*el*(gL + gR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(gL - gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(gL - gR)*(g1VL*gL + g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(gL + gR)*(g1VL*gL - g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      4*el*(g1VL + g1VR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL + g2VR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*(-pow(Mv,2) + 2*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*(g1VL*gL + g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))*(-(C36*C45*
            (C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL - g1VR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL - g2VR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*(-pow(Mv,2) + 2*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*(g1VL*gL - g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))*(-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(pow(g2VL,2) + pow(g2VR,2))*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(pow(g1VL,2) + pow(g1VR,2))*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(pow(g2VL,2) - pow(g2VR,2))*((gL*gL) - (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(pow(g1VL,2) - pow(g1VR,2))*((gL*gL) - (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       (C35 + C36 - C45 - C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       (C35 - C36 + C45 - C46) - 
      8*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) - 
      8*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) + 
      8*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*(g1VL + g1VR)*(gL + gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) - 
      2*(g1VL - g1VR)*(gL - gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) - 
      2*(g2VL + g2VR)*(gL + gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) - 
      2*(g2VL - g2VR)*(gL - gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      2*(g1VL - g1VR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56)*((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g2VL + g2VR)*(gL - gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g1VL + g1VR)*(gL - gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56)*((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      2*(g2VL - g2VR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 + C45 + C46) - 
      8*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) - 
      8*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      8*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(g1VL + g1VR)*E3456*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (C35 - C36 - C45 + C46) - 
      4*el*(g1VL - g1VR)*E3456*((gL*gL) - (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (C35 + C36 + C45 + C46) - 
      4*el*(g2VL + g2VR)*E3456*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (-pow(Mv,2) + 2*C56) - 
      4*el*(g2VL - g2VR)*E3456*((gL*gL) - (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (-pow(Mv,2) + 2*C56) - 
      4*el*(gL + gR)*(g1VL*gL + g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      4*el*(gL - gR)*(g1VL*gL - g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      4*el*(gL + gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) - 4*el*(gL - gR)*(g2VL*gL - g2VR*gR)*
       E3456*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 4*el*(g2VL + g2VR)*Mv*wV*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL - g1VR)*Mv*wV*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*(g1VL*gL - g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL - g2VR)*Mv*wV*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL + g1VR)*Mv*wV*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*(g1VL*gL + g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       ((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46) - 
      8*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       ((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46) - 
      8*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       ((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46) - 
      8*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       ((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46) - 
      16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56)) - 
      16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))))/262144.
   ;
}
double GetFullWithZPrime_A1ZVR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 + C45 + C46) - 
      8*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) - 
      8*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      8*(g1VL*gL - g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (MZ*MZ*MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C36*C45 + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))
) + 4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) + 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C36*C45 + C35*C46) + 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C36*C45 + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      16*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C36*C45 + C35*C46)))/262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*wZ*E3456*(el*el)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
      2*wZ*E3456*(el*el)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56) + 
      2*(el*el)*((gL+gR)*(gL+gR))*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(el*el)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56)) - 
      8*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))*(-(C36*C45*
            (C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))*(-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(gL - gR)*wZ*E3456*((gL+gR)*(gL+gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46) - 
      4*el*wZ*E3456*
       (-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46) - 
      4*el*wZ*E3456*
       (-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46) - 
      4*el*(gL - gR)*wZ*E3456*((gL+gR)*(gL+gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46) + 
      4*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       (C35 + C36 - C45 - C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       (C35 - C36 + C45 - C46) - 
      8*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) - 
      8*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) + 
      8*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(MZ*MZ)*(1/(vh*vh))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(MZ*MZ)*(1/(vh*vh))*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*E3456*(el*el)*((gL+gR)*(gL+gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) - 
      2*E3456*(el*el)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      2*wZ*(el*el)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*wZ*(el*el)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) - 8*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*
       E3456*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 8*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (C35 - C36 - C45 + C46) - 
      4*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (C35 + C36 + C45 + C46) - 
      4*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (-(MZ*MZ) + 2*C56) - 
      4*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (-(MZ*MZ) + 2*C56) + 
      4*el*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (MZ*MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*wZ*((gL+gR)*(gL+gR))*(MZ*MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*wZ*((gL+gR)*(gL+gR))*(MZ*MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (MZ*MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 + C45 + C46) - 
      8*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) - 
      8*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      8*(g1VL*gL - g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A1ZZR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*E3456*(MZ*MZ)*(1/(vh*vh))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46) - 
      8*E3456*(MZ*MZ)*(1/(vh*vh))*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)))/262144.
   ;
}
double GetFullWithZPrime_A2AAR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*(g1VL + g1VR)*(g2VL - g2VR)*Mv*wV*E3456*(el*el)*
       (MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56) - 
      2*(g1VL - g1VR)*(g2VL + g2VR)*Mv*wV*E3456*(el*el)*
       (MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56) + 
      2*(g1VL + g1VR)*(g2VL + g2VR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g1VL - g1VR)*(g2VL - g2VR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2AAR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*(g1VL + g1VR)*(gL - gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56) - 2*(g1VL - g1VR)*(gL + gR)*E3456*
       (el*el)*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56) - 2*(g2VL - g2VR)*(gL + gR)*E3456*
       (el*el)*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56)) - 
      2*(g2VL + g2VR)*(gL - gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56)) + 
      2*(g1VL + g1VR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g2VL + g2VR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g1VL - g1VR)*(gL - gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      2*(g2VL - g2VR)*(gL - gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2AAR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*wZ*E3456*(el*el)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
      2*wZ*E3456*(el*el)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56) + 
      2*(el*el)*((gL+gR)*(gL+gR))*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(el*el)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2AAR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*(el*el*el*el)*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*(1.0/C34/C34)*
    (1.0/C56/C56)*(2*pow(C36*C45 - C35*C46,2) + 
      2*(C34*C34)*(C56*C56) + 
      (pow(C36 - C45,2) + pow(C35 - C46,2))*
       C34*C56))/65536.
   ;
}
double GetFullWithZPrime_A2AAR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(g1VL - g1VR)*(g2VL - g2VR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      4*(g1VL + g1VR)*(g2VL + g2VR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2AAR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(gL + gR)*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(MZ*MZ) + 2*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      4*(gL + gR)*(el*el*el)*(1/(vh*vh))*(1.0/C34/C34)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2AAR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(g1VL - g1VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      4*(g1VL + g1VR)*(gL + gR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      4*(g2VL - g2VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      4*(g2VL + g2VR)*(gL + gR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2AAR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      4*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2AAR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*E3456*(el*el*el*el)*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*(1.0/C34/C34)*
    (1.0/C56/C56)*(-(C36*C45) + C35*C46))/32768.
   ;
}
double GetFullWithZPrime_A2AAR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(g1VL - g1VR)*(g2VL + g2VR)*Mv*wV*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (2*pow(Mv,2) - 2*C34 - 2*C56) - 
      4*(g1VL + g1VR)*(g2VL - g2VR)*Mv*wV*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (2*pow(Mv,2) - 2*C34 - 2*C56) + 
      8*(g1VL - g1VR)*(g2VL - g2VR)*E3456*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      8*(g1VL + g1VR)*(g2VL + g2VR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2AAR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(gL - gR)*MZ*wZ*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*(1.0/C56) + 
      4*(gL - gR)*MZ*wZ*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1) + 
      8*(gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(MZ*MZ) + 2*C34)*
       (-(C36*C45) + C35*C46) + 
      8*(gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*(1.0/C34/C34)*
       (1.0/C56)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-(MZ*MZ) + 2*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2AAR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(g1VL - g1VR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34) - 2*Mv*wV*C56) - 
      4*(g1VL + g1VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34) - 2*Mv*wV*C56) + 
      8*(g1VL - g1VR)*(gL - gR)*E3456*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      8*(g1VL + g1VR)*(gL + gR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      8*(g2VL - g2VR)*(gL - gR)*E3456*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      8*(g2VL + g2VR)*(gL + gR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) - 
      4*(g2VL + g2VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (-2*Mv*wV*C34 + MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56)) 
- 4*(g2VL - g2VR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (-2*Mv*wV*C34 + MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2AAR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (2*(MZ*MZ) - 2*C34 - 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (2*(MZ*MZ) - 2*C34 - 2*C56) + 
      8*E3456*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      8*E3456*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(pow(g1VL,2) + pow(g1VR,2))*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(pow(g1VL,2) - pow(g1VR,2))*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2VVR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       (C35 + C36 - C45 - C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       (C35 - C36 + C45 - C46) - 
      8*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) - 
      8*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) + 
      8*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2VVR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56)) - 
      8*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))*(-(C36*C45*
            (C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))*(-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2VVR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(g1VL - g1VR)*(g2VL - g2VR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      4*(g1VL + g1VR)*(g2VL + g2VR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(pow(g1VL,2) - pow(g1VR,2))*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(pow(g1VL,2) + pow(g1VR,2))*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 8*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56)
)))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))
) + 4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(g1VL - g1VR)*(g2VL + g2VR)*Mv*wV*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56) - 
      4*(g1VL + g1VR)*(g2VL - g2VR)*Mv*wV*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56) + 
      8*(g1VL - g1VR)*(g2VL - g2VR)*E3456*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      8*(g1VL + g1VR)*(g2VL + g2VR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      32*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*C56))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*el*(g2VL + g2VR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(g2VL - g2VR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      16*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      8*el*(g1VL - g1VR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) - 
      8*el*(g1VL + g1VR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) + 
      16*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 16*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56)
)))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) - 
      16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*C56 - 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*C56 + 
      32*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*C56 - 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) - 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) + 
      32*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      32*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2VVR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-16*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56)) - 
      16*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56)) + 
      32*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 32*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*
       E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))
) + 4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(g2VL - g2VR)*(g1VL*gL + g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(g2VL + g2VR)*(g1VL*gL - g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(g1VL + g1VR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) - 
      4*el*(g1VL - g1VR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) + 
      4*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*
             C56))*(-(C36*C45*
            (C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
))*(-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(g2VL - g2VR)*Mv*wV*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46) - 
      4*el*(g1VL + g1VR)*Mv*wV*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46) - 
      4*el*(g2VL + g2VR)*Mv*wV*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 + C45 - C46) - 
      4*el*(g1VL - g1VR)*Mv*wV*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46) - 
      4*el*(gL + gR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(gL - gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(gL - gR)*(g1VL*gL + g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      4*el*(gL + gR)*(g1VL*gL - g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      4*el*(g1VL + g1VR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL + g2VR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*(-pow(Mv,2) + 2*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*(g1VL*gL + g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))*(-(C36*C45*
            (C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL - g1VR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL - g2VR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*(-pow(Mv,2) + 2*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*(g1VL*gL - g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))*(-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(gL - gR)*wZ*E3456*((gL+gR)*(gL+gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46) - 
      4*el*wZ*E3456*
       (-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46) - 
      4*el*wZ*E3456*
       (-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46) - 
      4*el*(gL - gR)*wZ*E3456*((gL+gR)*(gL+gR))*(MZ*MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46) + 
      4*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(gL + gR)*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(MZ*MZ) + 2*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      4*(gL + gR)*(el*el*el)*(1/(vh*vh))*(1.0/C34/C34)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 8*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56)
)))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      8*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*(1.0/C34/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      8*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      8*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g1VL - g1VR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      8*el*(g2VL - g2VR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (-pow(Mv,2) + 2*C56) + 
      8*el*(g1VL + g1VR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      8*el*(g2VL + g2VR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*(-pow(Mv,2) + 2*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      8*el*(gL - gR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(gL + gR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(gL - gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 8*el*(gL + gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (-(MZ*MZ) + 2*C56) + 
      8*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      8*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(gL - gR)*MZ*wZ*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*(1.0/C56) - 
      4*(gL - gR)*MZ*wZ*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1) + 
      8*(gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(MZ*MZ) + 2*C34)*
       (-(C36*C45) + C35*C46) + 
      8*(gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*(1.0/C34/C34)*
       (1.0/C56)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-(MZ*MZ) + 2*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*el*(g2VL + g2VR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (-4*Mv*wV*(C34*C34) - 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) - 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(g2VL - g2VR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (-4*Mv*wV*(C34*C34) - 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) - 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      16*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      8*el*(g1VL - g1VR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (-2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) - 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) - 
      8*el*(g1VL + g1VR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (-2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) - 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) + 
      16*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 16*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56)
)))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*E3456*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(C36*C45) + C35*C46) + 
      16*E3456*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       (1.0/C34/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (2*C34 - 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (2*C34 - 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-2*C34 + 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-2*C34 + 2*C56) + 
      16*E3456*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      16*E3456*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g2VL + g2VR)*Mv*wV*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34 + 
      8*el*(g2VL - g2VR)*Mv*wV*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34 + 
      16*el*(g1VL + g1VR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-(C36*C45) + C35*C46) + 
      8*el*(g1VL - g1VR)*Mv*wV*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      8*el*(g1VL + g1VR)*Mv*wV*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      16*el*(g1VL - g1VR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*C56 + 
      16*el*(g2VL - g2VR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*(-pow(Mv,2) + 2*C56) + 
      16*el*(g2VL + g2VR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-pow(Mv,2) + 2*C56) - 
      8*el*(gL - gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (-(MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
              2*Mv*(MZ*wV + Mv*wZ)*C56)) - 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL + gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (-(MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
              2*Mv*(MZ*wV + Mv*wZ)*C56)) - 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL + gR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (-4*MZ*wZ*(C34*C34) - 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) - 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL - gR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (-4*MZ*wZ*(C34*C34) - 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) - 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      16*el*(gL - gR)*(g1VL*gL - g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(gL + gR)*(g1VL*gL + g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(gL + gR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 16*el*(gL - gR)*(g2VL*gL - g2VR*gR)*
       E3456*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZAR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(gL - gR)*MZ*wZ*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34 + 
      8*el*MZ*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34 + 
      16*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-(C36*C45) + C35*C46) + 
      8*el*MZ*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      8*el*(gL - gR)*MZ*wZ*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      16*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*C56 + 
      16*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*(-(MZ*MZ) + 2*C56) + 
      16*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-(MZ*MZ) + 2*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       (C35 + C36 - C45 - C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       (C35 - C36 + C45 - C46) - 
      8*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) - 
      8*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) + 
      8*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(pow(g2VL,2) + pow(g2VR,2))*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(pow(g1VL,2) + pow(g1VR,2))*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(pow(g2VL,2) - pow(g2VR,2))*((gL*gL) - (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(pow(g1VL,2) - pow(g1VR,2))*((gL*gL) - (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       (C35 + C36 - C45 - C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       (C35 - C36 + C45 - C46) - 
      8*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) - 
      8*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) + 
      8*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(g1VL - g1VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      4*(g1VL + g1VR)*(gL + gR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      4*(g2VL - g2VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      4*(g2VL + g2VR)*(gL + gR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g1VL - g1VR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      8*el*(g2VL - g2VR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (-pow(Mv,2) + 2*C56) + 
      8*el*(g1VL + g1VR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      8*el*(g2VL + g2VR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*(-pow(Mv,2) + 2*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      8*el*(gL - gR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(gL + gR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(gL - gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 8*el*(gL + gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(pow(g2VL,2) - pow(g2VR,2))*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(pow(g1VL,2) - pow(g1VR,2))*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(pow(g2VL,2) + pow(g2VR,2))*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      16*(pow(g1VL,2) + pow(g1VR,2))*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      32*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56)) + 
      32*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(g1VL - g1VR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56) - 4*(g1VL + g1VR)*(gL - gR)*(el*el)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56) + 8*(g1VL - g1VR)*(gL - gR)*E3456*
       (el*el)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      8*(g1VL + g1VR)*(gL + gR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      8*(g2VL - g2VR)*(gL - gR)*E3456*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      8*(g2VL + g2VR)*(gL + gR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) - 
      4*(g2VL + g2VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56)) - 
      4*(g2VL - g2VR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) - 
      16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*C56 - 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*C56 + 
      32*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*C56 - 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) - 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) + 
      32*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      32*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*el*(g2VL + g2VR)*Mv*wV*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34 - 
      8*el*(g2VL - g2VR)*Mv*wV*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34 + 
      16*el*(g1VL + g1VR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-(C36*C45) + C35*C46) - 
      8*el*(g1VL - g1VR)*Mv*wV*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 - 
      8*el*(g1VL + g1VR)*Mv*wV*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      16*el*(g1VL - g1VR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*C56 + 
      16*el*(g2VL - g2VR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*(-pow(Mv,2) + 2*C56) + 
      16*el*(g2VL + g2VR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-pow(Mv,2) + 2*C56) - 
      8*el*(gL - gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL + gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL + gR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL - gR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      16*el*(gL - gR)*(g1VL*gL - g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(gL + gR)*(g1VL*gL + g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(gL + gR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 16*el*(gL - gR)*(g2VL*gL - g2VR*gR)*
       E3456*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       ((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      32*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       ((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      32*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       ((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*C56 + 
      32*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       ((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56 + 
      64*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56)) + 
      64*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZVR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) - 
      16*(g1VL*gL - g1VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*C56 - 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*C56 + 
      32*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*C56 - 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) - 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) + 
      32*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      32*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56)) - 
      8*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))*(-(C36*C45*
            (C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))*(-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       (C35 + C36 - C45 - C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       (C35 - C36 + C45 - C46) - 
      8*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) - 
      8*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 + C45 - C46)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) + 
      8*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(MZ*MZ)*(1/(vh*vh))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(MZ*MZ)*(1/(vh*vh))*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      4*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))
) + 4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (-(MZ*MZ) + 2*C56) + 
      8*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      8*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(1/(vh*vh))*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(1/(vh*vh))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56) + 
      8*E3456*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      8*E3456*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 32*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*
       E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) - 16*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56)) - 
      16*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56))))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*el*(gL - gR)*MZ*wZ*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34 - 
      8*el*MZ*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34 + 
      16*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-(C36*C45) + C35*C46) - 
      8*el*MZ*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 - 
      8*el*(gL - gR)*MZ*wZ*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      16*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*C56 + 
      16*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*(-(MZ*MZ) + 2*C56) + 
      16*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-(MZ*MZ) + 2*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) - 
      16*(g1VL*gL - g1VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*C56 - 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*C56 + 
      32*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*C56 - 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) - 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) + 
      32*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      32*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A2ZZR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*E3456*(1/(vh*vh))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      32*E3456*(1/(vh*vh))*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56))/262144.
   ;
}
double GetFullWithZPrime_A3AAR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*(g1VL + g1VR)*(g2VL + g2VR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) - 
      2*(g1VL - g1VR)*(g2VL - g2VR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      2*(g1VL - g1VR)*(g2VL + g2VR)*Mv*wV*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g1VL + g1VR)*(g2VL - g2VR)*Mv*wV*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3AAR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*(g1VL + g1VR)*(gL + gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) - 
      2*(g1VL - g1VR)*(gL - gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) - 
      2*(g2VL + g2VR)*(gL + gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) - 
      2*(g2VL - g2VR)*(gL - gR)*E3456*(el*el)*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      2*(g1VL - g1VR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56)*((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g2VL + g2VR)*(gL - gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(g1VL + g1VR)*(gL - gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56)*((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      2*(g2VL - g2VR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3AAR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*E3456*(el*el)*((gL+gR)*(gL+gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) - 
      2*E3456*(el*el)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      2*wZ*(el*el)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*wZ*(el*el)*((gL*gL) - (gR*gR))*(MZ*MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3AAR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*E3456*(el*el*el*el)*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*(1.0/C34/C34)*
    (1.0/C56/C56)*(-(C36*C45) + C35*C46))/32768.
   ;
}
double GetFullWithZPrime_A3AAR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(g1VL - g1VR)*(g2VL + g2VR)*Mv*wV*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56) - 
      4*(g1VL + g1VR)*(g2VL - g2VR)*Mv*wV*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (-2*pow(Mv,2) + 2*C34 + 2*C56) + 
      8*(g1VL - g1VR)*(g2VL - g2VR)*E3456*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      8*(g1VL + g1VR)*(g2VL + g2VR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3AAR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(gL - gR)*MZ*wZ*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*(1.0/C56) - 
      4*(gL - gR)*MZ*wZ*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1) + 
      8*(gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(MZ*MZ) + 2*C34)*
       (-(C36*C45) + C35*C46) + 
      8*(gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*(1.0/C34/C34)*
       (1.0/C56)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-(MZ*MZ) + 2*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3AAR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(g1VL - g1VR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56) - 4*(g1VL + g1VR)*(gL - gR)*(el*el)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34)) + 
         2*Mv*wV*C56) + 8*(g1VL - g1VR)*(gL - gR)*E3456*
       (el*el)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      8*(g1VL + g1VR)*(gL + gR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      8*(g2VL - g2VR)*(gL - gR)*E3456*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      8*(g2VL + g2VR)*(gL + gR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) - 
      4*(g2VL + g2VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56)) - 
      4*(g2VL - g2VR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (2*Mv*wV*C34 - MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3AAR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-2*(MZ*MZ) + 2*C34 + 2*C56) + 
      8*E3456*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      8*E3456*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3AAR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*(el*el*el*el)*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*(1.0/C34/C34)*
    (1.0/C56/C56)*(-2*pow(C36*C45 - C35*C46,2) - 
      2*(C34*C34)*(C56*C56) + 
      (pow(C36 + C45,2) + pow(C35 + C46,2))*
       C34*C56))/65536.
   ;
}
double GetFullWithZPrime_A3AAR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(g1VL - g1VR)*(g2VL - g2VR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      4*(g1VL + g1VR)*(g2VL + g2VR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3AAR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(gL + gR)*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(MZ*MZ) + 2*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      4*(gL + gR)*(el*el*el)*(1/(vh*vh))*(1.0/C34/C34)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3AAR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(g1VL - g1VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      4*(g1VL + g1VR)*(gL + gR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      4*(g2VL - g2VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      4*(g2VL + g2VR)*(gL + gR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3AAR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      4*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46) - 
      8*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 + C45 + C46) - 
      8*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) - 
      8*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      8*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3VVR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) - 8*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*
       E3456*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 8*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3VVR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(g1VL - g1VR)*(g2VL + g2VR)*Mv*wV*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (2*pow(Mv,2) - 2*C34 - 2*C56) - 
      4*(g1VL + g1VR)*(g2VL - g2VR)*Mv*wV*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (2*pow(Mv,2) - 2*C34 - 2*C56) + 
      8*(g1VL - g1VR)*(g2VL - g2VR)*E3456*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      8*(g1VL + g1VR)*(g2VL + g2VR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      32*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*C56))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*el*(g2VL + g2VR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (-4*Mv*wV*(C34*C34) - 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) - 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(g2VL - g2VR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (-4*Mv*wV*(C34*C34) - 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) - 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      16*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      8*el*(g1VL - g1VR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (-2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) - 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) - 
      8*el*(g1VL + g1VR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (-2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) - 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) + 
      16*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 16*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56)
)))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) - 
      16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*C56 - 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*C56 + 
      32*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*C56 - 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) - 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) + 
      32*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      32*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 32*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*
       E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) - 16*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56)) - 
      16*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(MZ*wV - Mv*wZ) + 
            2*(-(Mv*wV) + MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               2*Mv*wZ*(MZ*MZ) - wV*(MZ*MZ*MZ) - Mv*wZ*pow(wV,2) + 
               MZ*wV*(wZ*wZ)) + 4*(-(Mv*wV) + MZ*wZ)*(C56*C56) + 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(-(MZ*wZ*pow(Mv,2)) + MZ*wZ*pow(wV,2) + 
               Mv*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(MZ*wV - Mv*wZ)*(C56*C56) + 
            2*(-2*MZ*wV*pow(Mv,2) + wZ*pow(Mv,3) + 
               Mv*wZ*(2*(MZ*MZ) - pow(wV,2)) + 
               MZ*wV*(-(MZ*MZ) + (wZ*wZ)))*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(g1VL - g1VR)*(g2VL - g2VR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56)) + 
      4*(g1VL + g1VR)*(g2VL + g2VR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (pow(Mv,2)*(pow(Mv,2) - pow(wV,2) - 2*C56) + 
         2*C34*(-pow(Mv,2) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(pow(g1VL,2) - pow(g1VR,2))*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(pow(g1VL,2) + pow(g1VR,2))*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 8*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56)
)))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3VVR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))
) + 4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      4*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      4*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) - 4*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 4*el*(g2VL + g2VR)*(g1VL*gL - g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL - g1VR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL - g2VR)*(g1VL*gL + g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL + g1VR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*(g1VL + g1VR)*E3456*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (C35 - C36 - C45 + C46) - 
      4*el*(g1VL - g1VR)*E3456*((gL*gL) - (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (C35 + C36 + C45 + C46) - 
      4*el*(g2VL + g2VR)*E3456*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (-pow(Mv,2) + 2*C56) - 
      4*el*(g2VL - g2VR)*E3456*((gL*gL) - (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (-pow(Mv,2) + 2*C56) - 
      4*el*(gL + gR)*(g1VL*gL + g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      4*el*(gL - gR)*(g1VL*gL - g1VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      4*el*(gL + gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) - 4*el*(gL - gR)*(g2VL*gL - g2VR*gR)*
       E3456*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 4*el*(g2VL + g2VR)*Mv*wV*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL - g1VR)*Mv*wV*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*(g2VL*gL + g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*(g1VL*gL - g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(g2VL - g2VR)*Mv*wV*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(g1VL + g1VR)*Mv*wV*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL + gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*(g1VL*gL + g1VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (C35 - C36 - C45 + C46) - 
      4*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (C35 + C36 + C45 + C46) - 
      4*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (-(MZ*MZ) + 2*C56) - 
      4*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (-(MZ*MZ) + 2*C56) + 
      4*el*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (MZ*MZ*MZ)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*wZ*((gL+gR)*(gL+gR))*(MZ*MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      4*el*(gL - gR)*wZ*((gL+gR)*(gL+gR))*(MZ*MZ*MZ)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      4*el*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (MZ*MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(gL - gR)*MZ*wZ*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*(1.0/C56) + 
      4*(gL - gR)*MZ*wZ*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1) + 
      8*(gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(MZ*MZ) + 2*C34)*
       (-(C36*C45) + C35*C46) + 
      8*(gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*(1.0/C34/C34)*
       (1.0/C56)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-(MZ*MZ) + 2*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*el*(g2VL + g2VR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(g2VL - g2VR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (4*Mv*wV*(C34*C34) + 
         Mv*MZ*(Mv*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(Mv*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      16*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) - 
      8*el*(g1VL - g1VR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) - 
      8*el*(g1VL + g1VR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         Mv*(Mv*MZ*(2*Mv*MZ*wV - wZ*pow(Mv,2) + wZ*pow(wV,2)) + 
            4*wV*(C56*C56) + 
            2*(Mv*MZ*wZ - 2*wV*pow(Mv,2) - wV*(MZ*MZ))*C56)) + 
      16*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 16*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56)
)))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*E3456*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(C36*C45) + C35*C46) + 
      16*E3456*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       (1.0/C34/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (2*C34 - 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (2*C34 - 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-2*C34 + 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (-2*C34 + 2*C56) + 
      16*E3456*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      16*E3456*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*el*(g2VL + g2VR)*Mv*wV*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34 - 
      8*el*(g2VL - g2VR)*Mv*wV*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34 + 
      16*el*(g1VL + g1VR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-(C36*C45) + C35*C46) - 
      8*el*(g1VL - g1VR)*Mv*wV*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 - 
      8*el*(g1VL + g1VR)*Mv*wV*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      16*el*(g1VL - g1VR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*C56 + 
      16*el*(g2VL - g2VR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*(-pow(Mv,2) + 2*C56) + 
      16*el*(g2VL + g2VR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-pow(Mv,2) + 2*C56) - 
      8*el*(gL - gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL + gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
            2*Mv*(MZ*wV + Mv*wZ)*C56) + 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL + gR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL - gR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (4*MZ*wZ*(C34*C34) + 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) + 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      16*el*(gL - gR)*(g1VL*gL - g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(gL + gR)*(g1VL*gL + g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(gL + gR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 16*el*(gL - gR)*(g2VL*gL - g2VR*gR)*
       E3456*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*el*(gL - gR)*MZ*wZ*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34 - 
      8*el*MZ*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34 + 
      16*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-(C36*C45) + C35*C46) - 
      8*el*MZ*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 - 
      8*el*(gL - gR)*MZ*wZ*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      16*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*C56 + 
      16*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*(-(MZ*MZ) + 2*C56) + 
      16*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-(MZ*MZ) + 2*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(gL + gR)*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-(MZ*MZ) + 2*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      4*(gL + gR)*(el*el*el)*(1/(vh*vh))*(1.0/C34/C34)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g2VL - g2VR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(g2VL + g2VR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (4*(C34*C34)*(-pow(Mv,2) + 2*C56) + 
         Mv*MZ*(Mv*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(Mv*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - 
               Mv*pow(wV,2)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(g1VL - g1VR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56
)) + 8*el*(g1VL + g1VR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*(Mv*MZ*(-2*Mv*wV*wZ - MZ*pow(Mv,2) + MZ*pow(wV,2)) - 
            4*Mv*(C56*C56) + 
            2*(MZ*wV*wZ + pow(Mv,3) + Mv*(MZ*MZ) - Mv*pow(wV,2))*C56)
)))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56/C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      8*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*(1.0/C34/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      8*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      8*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g1VL - g1VR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      8*el*(g2VL - g2VR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (-pow(Mv,2) + 2*C56) + 
      8*el*(g1VL + g1VR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      8*el*(g2VL + g2VR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*(-pow(Mv,2) + 2*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      8*el*(gL - gR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(gL + gR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(gL - gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 8*el*(gL + gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZAR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (-(MZ*MZ) + 2*C56) + 
      8*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      8*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 + C45 + C46) - 
      8*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) - 
      8*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      8*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       ((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 - C36 - C45 + C46) - 
      8*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       ((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46) - 
      8*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       ((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 + C45 + C46) - 
      8*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       ((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46) - 
      16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56)) - 
      16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 + C45 + C46) - 
      8*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) - 
      8*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      8*(g1VL*gL - g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(g1VL - g1VR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34) - 2*Mv*wV*C56) - 
      4*(g1VL + g1VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C34) - 2*Mv*wV*C56) + 
      8*(g1VL - g1VR)*(gL - gR)*E3456*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      8*(g1VL + g1VR)*(gL + gR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      8*(g2VL - g2VR)*(gL - gR)*E3456*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      8*(g2VL + g2VR)*(gL + gR)*E3456*(el*el)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) - 
      4*(g2VL + g2VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (-2*Mv*wV*C34 + MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56)) 
- 4*(g2VL - g2VR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       (-2*Mv*wV*C34 + MZ*(Mv*MZ*wV + wZ*pow(Mv,2) - 2*wZ*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) - 
      16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*C56 - 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*C56 + 
      32*(g1VL*gL - g1VR*gR)*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*C56 - 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) - 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) + 
      32*(g2VL*gL + g2VR*gR)*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      32*(g2VL*gL - g2VR*gR)*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g2VL + g2VR)*Mv*wV*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34 + 
      8*el*(g2VL - g2VR)*Mv*wV*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*C34 + 
      16*el*(g1VL + g1VR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-(C36*C45) + C35*C46) + 
      8*el*(g1VL - g1VR)*Mv*wV*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      8*el*(g1VL + g1VR)*Mv*wV*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      16*el*(g1VL - g1VR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*C56 + 
      16*el*(g2VL - g2VR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*(-pow(Mv,2) + 2*C56) + 
      16*el*(g2VL + g2VR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-pow(Mv,2) + 2*C56) - 
      8*el*(gL - gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (-(MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
              2*Mv*(MZ*wV + Mv*wZ)*C56)) - 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL + gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (-(MZ*(Mv*MZ*wV*((MZ*MZ) + (wZ*wZ)) + 4*wZ*(C56*C56) - 
              2*Mv*(MZ*wV + Mv*wZ)*C56)) - 
         2*C34*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL + gR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (-4*MZ*wZ*(C34*C34) - 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) - 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) - 
      8*el*(gL - gR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (-4*MZ*wZ*(C34*C34) - 
         Mv*MZ*(MZ*wV*((MZ*MZ) + (wZ*wZ)) + 
            2*(-(MZ*wV) + Mv*wZ)*C56) - 
         2*C34*(-(Mv*MZ*(MZ*wV + Mv*wZ)) + 
            2*(Mv*wV - MZ*wZ)*C56)) + 
      16*el*(gL - gR)*(g1VL*gL - g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(gL + gR)*(g1VL*gL + g1VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      16*el*(gL + gR)*(g2VL*gL + g2VR*gR)*E3456*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 16*el*(gL - gR)*(g2VL*gL - g2VR*gR)*
       E3456*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*E3456*(pow(g2VL,2) + pow(g2VR,2))*
       ((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      32*E3456*(pow(g1VL,2) + pow(g1VR,2))*
       ((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      32*E3456*(pow(g2VL,2) - pow(g2VR,2))*
       ((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*C56 + 
      32*E3456*(pow(g1VL,2) - pow(g1VR,2))*
       ((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56 + 
      64*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56)) + 
      64*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) - 
      16*(g1VL*gL - g1VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*C56 - 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C34)*C56 + 
      32*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*C56 - 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) - 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(MZ*wV - Mv*wZ) + 2*(-(Mv*wV) + MZ*wZ)*C56) + 
      32*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      32*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(g1VL - g1VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      4*(g1VL + g1VR)*(gL + gR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (2*C34*(-(MZ*MZ) + 2*C56) - 
         Mv*(MZ*wV*wZ - Mv*(MZ*MZ) + 2*Mv*C56)) + 
      4*(g2VL - g2VR)*(gL - gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56)) + 
      4*(g2VL + g2VR)*(gL + gR)*(el*el)*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (2*C34*(-pow(Mv,2) + 2*C56) - 
         MZ*(Mv*wV*wZ - MZ*pow(Mv,2) + 2*MZ*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(pow(g2VL,2) - pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(g2VL*gL - g2VR*gR)*(pow(g1VL,2) - pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g1VL*gL + g1VR*gR)*(pow(g2VL,2) + pow(g2VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      16*(g2VL*gL + g2VR*gR)*(pow(g1VL,2) + pow(g1VR,2))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(g1VL - g1VR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      8*el*(g2VL - g2VR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (-pow(Mv,2) + 2*C56) + 
      8*el*(g1VL + g1VR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       (1.0/C34)*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-pow(Mv,2) + 2*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      8*el*(g2VL + g2VR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*(-pow(Mv,2) + 2*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      8*el*(gL - gR)*(g1VL*gL - g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(gL + gR)*(g1VL*gL + g1VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (4*(C34*C34)*(-(MZ*MZ) + 2*C56) + 
         Mv*MZ*(-(Mv*MZ*((MZ*MZ) + (wZ*wZ))) + 
            2*(Mv*MZ + wV*wZ)*C56) + 
         2*C34*(MZ*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + 
               MZ*(wZ*wZ)) - 2*(pow(Mv,2) + (MZ*MZ))*C56)) + 
      8*el*(gL - gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56)) + 8*el*(gL + gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (2*C34*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         MZ*(-(MZ*pow(Mv,2)*((MZ*MZ) + (wZ*wZ))) - 
            4*MZ*(C56*C56) + 
            2*(-(Mv*wV*wZ) + MZ*pow(Mv,2) + (MZ*MZ*MZ) + MZ*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(pow(g2VL,2) - pow(g2VR,2))*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(pow(g1VL,2) - pow(g1VR,2))*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(pow(g2VL,2) + pow(g2VR,2))*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      16*(pow(g1VL,2) + pow(g1VR,2))*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      32*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56)) + 
      32*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(pow(Mv,2) + pow(wV,2))*((MZ*MZ) + (wZ*wZ)) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*Mv*MZ*(pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ))*
             C56) - 2*C34*
          (pow(Mv,2)*(MZ*MZ)*
             (pow(Mv,2) + (MZ*MZ) + pow(wV,2) + (wZ*wZ)) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(-2*Mv*MZ*wV*wZ + pow(Mv,4) + 
               pow(Mv,2)*(2*(MZ*MZ) + pow(wV,2)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ)))*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZVR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A1VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*(MZ*MZ)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) - 8*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*
       E3456*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 8*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A1ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 - C36 - C45 + C46) - 
      8*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 + C45 + C46) - 
      8*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) - 
      8*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (MZ*MZ)*(1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      8*(g1VL*gL - g1VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL + g2VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(g1VL*gL + g1VR*gR)*((gL*gL) - (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      8*(g2VL*gL - g2VR*gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A1ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*E3456*(MZ*MZ)*(1/(vh*vh))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 - C36 - C45 + C46) - 
      8*E3456*(MZ*MZ)*(1/(vh*vh))*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 + C45 + C46)))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A2AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (2*(MZ*MZ) - 2*C34 - 2*C56) - 
      4*MZ*wZ*(el*el)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*
       (2*(MZ*MZ) - 2*C34 - 2*C56) + 
      8*E3456*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      8*E3456*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A2VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-16*(g1VL*gL - g1VR*gR)*(g2VL*gL + g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56)) - 
      16*(g1VL*gL + g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(-(MZ*wV) + Mv*wZ) + 
            2*(Mv*wV - MZ*wZ)*C56) + 
         2*C34*(Mv*MZ*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ))) + 
            4*(Mv*wV - MZ*wZ)*(C56*C56) - 
            4*(Mv*wV - MZ*wZ)*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(2*Mv*MZ*(MZ*wZ*pow(Mv,2) - MZ*wZ*pow(wV,2) + 
               Mv*wV*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(-(MZ*wV) + Mv*wZ)*(C56*C56) + 
            2*(2*MZ*wV*pow(Mv,2) - wZ*pow(Mv,3) + 
               Mv*wZ*(-2*(MZ*MZ) + pow(wV,2)) + 
               MZ*wV*((MZ*MZ) - (wZ*wZ)))*C56)) + 
      32*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*E3456*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 32*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*
       E3456*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))
) + 4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A2ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(gL - gR)*MZ*wZ*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34 + 
      8*el*MZ*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34 + 
      16*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-(C36*C45) + C35*C46) + 
      8*el*MZ*wZ*(-(gR*(gL*gL)) + (gL*gL*gL) + gL*(gR*gR) - (gR*gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      8*el*(gL - gR)*MZ*wZ*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C56 + 
      16*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*C56 + 
      16*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*(-(MZ*MZ) + 2*C56) + 
      16*el*E3456*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + 
         (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (-(MZ*MZ) + 2*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A2ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(g1VL*gL + g1VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-(C36*C45) + C35*C46) - 
      16*(g1VL*gL - g1VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*C56 - 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C56*C56) - 4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C34)*C56 + 
      32*(g1VL*gL - g1VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*C56 - 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) - 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C56*C56) - 4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(-(MZ*wV) + Mv*wZ) + 2*(Mv*wV - MZ*wZ)*C56) + 
      32*(g2VL*gL + g2VR*gR)*E3456*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      32*(g2VL*gL - g2VR*gR)*E3456*((gL*gL) - (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A2ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*E3456*(1/(vh*vh))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-(C36*C45) + C35*C46) + 
      32*E3456*(1/(vh*vh))*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*C56))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A3AAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (4*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56)) + 
      4*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*(1.0/C34)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       ((MZ*MZ)*((MZ*MZ) - (wZ*wZ) - 2*C56) + 
         2*C34*(-(MZ*MZ) + 2*C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A3VVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*(g2VL*gL - g2VR*gR)*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + 
               pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))) + 
            4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56)) + 16*(g1VL*gL + g1VR*gR)*(g2VL*gL + g2VR*gR)*
       (1/(vh*vh))*pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 
         4*(C34*C34) - 4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (4*(C34*C34)*(Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
            2*(pow(Mv,2) + (MZ*MZ))*C56) + 
         Mv*MZ*(Mv*MZ*(4*Mv*MZ*wV*wZ + pow(Mv,2)*((MZ*MZ) - (wZ*wZ)) + 
               pow(wV,2)*(-(MZ*MZ) + (wZ*wZ))) + 
            4*(Mv*MZ + wV*wZ)*(C56*C56) - 
            2*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 2*wV*wZ*(MZ*MZ) + 
               Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ)))*C56) - 
         2*C34*(Mv*MZ*(2*wV*wZ*pow(Mv,2) + MZ*pow(Mv,3) + 
               2*wV*wZ*(MZ*MZ) + Mv*MZ*((MZ*MZ) - pow(wV,2) - (wZ*wZ))
) + 4*(pow(Mv,2) + (MZ*MZ))*(C56*C56) - 
            2*(2*Mv*MZ*wV*wZ + pow(Mv,4) + (MZ*MZ*MZ*MZ) + 
               pow(Mv,2)*(2*(MZ*MZ) - pow(wV,2)) - (MZ*MZ)*(wZ*wZ))*
             C56))))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A3ZAR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (-(MZ*MZ) + 2*C56) + 
      8*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(1/(vh*vh))*
       (1.0/C34)*pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
         4*(C34*C34) - 4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      8*el*(gR*(gL*gL) + (gL*gL*gL) + gL*(gR*gR) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*(1.0/C56)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*(-(MZ*MZ) + 2*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A3ZVR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(1*1*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(g1VL*gL - g1VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(g2VL*gL - g2VR*gR)*((gL*gL) - (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56) + 
      16*(g1VL*gL + g1VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C34*C34) - 
         4*pow(Mv,2)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C34*C34) - 
         2*(pow(Mv,2) + (MZ*MZ))*C34)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      16*(g2VL*gL + g2VR*gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow(pow(Mv,4) + pow(Mv,2)*pow(wV,2) + 4*(C56*C56) - 
         4*pow(Mv,2)*C56,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (Mv*MZ*(Mv*MZ + wV*wZ) + 4*(C56*C56) - 
         2*(pow(Mv,2) + (MZ*MZ))*C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
double GetFullWithZPrime_A3ZZR_A3ZZR_15714(LeptonVectors &leptons, ZPrimeParameters &P)
{
   const double Pi = CONST_PI;

   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
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

   double Sqrt2 = sqrt(2);
   double SqrtC45 = sqrt(C45);
   double SqrtC56 = sqrt(C56);
   double SqrtC36 = sqrt(C36);
   double SqrtC34 = sqrt(C34);

   double Mv = P.VMass;
   double wV = P.VWidth;
   double g1VL = P.G1VL;
   double g1VR = P.G1VR;
   double g2VL = P.G2VL;
   double g2VR = P.G2VR;

   return
(pow(1,2)*pow(Pi,-7)*(1.0/s)*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(1/(vh*vh))*((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*C34*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(1/(vh*vh))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C34*C34) - 
         4*(MZ*MZ)*C34,-1)*
       pow((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
         4*(MZ*MZ)*C56,-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.
   ;
}
