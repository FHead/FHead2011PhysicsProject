
#include <cmath>
#include <iostream>
#include <complex>
using namespace std;

#include "CalculateME.h"
#include "AngleConversion.h"
#include "Constants.h"

double GetGeneralScalar2e2mu_Part2(LeptonVectors &leptons, double A2AAI, double A2AAR)
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

return ((pow(A2AAI,2) + pow(A2AAR,2))*(el*el*el*el)*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*pow(C34,-2)*
    pow(C56,-2)*(2*pow(C36*C45 - C35*C46,2) + 
      2*(C34*C34)*(C56*C56) + 
      (pow(C36 - C45,2) + pow(C35 - C46,2))*
       C34*C56))/65536.;
}

double GetGeneralScalar2e2mu_Part3(LeptonVectors &leptons, double A3AAI, double A3AAR)
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

return ((pow(A3AAI,2) + pow(A3AAR,2))*(el*el*el*el)*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*pow(C34,-2)*
    pow(C56,-2)*(-2*pow(C36*C45 - C35*C46,2) - 
      2*(C34*C34)*(C56*C56) + 
      (pow(C36 + C45,2) + pow(C35 + C46,2))*
       C34*C56))/65536.;
}

double GetGeneralScalar2e2mu_Part5(LeptonVectors &leptons, double A2AAI, double A2AAR, double A3AAI, double A3AAR)
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

return ((A2AAI*A3AAI + A2AAR*A3AAR)*E3456*(el*el*el*el)*pow(Pi,-7)*(1.0/s)*
    (1/(vh*vh))*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*pow(C34,-2)*
    pow(C56,-2)*(-(C36*C45) + C35*C46))/16384.
;
}

double GetGeneralScalar2e2mu_Part7(LeptonVectors &leptons, double A1ZZI, double A1ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(pow(A1ZZI,2) + pow(A1ZZR,2))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-(C36*C45) + C35*C46) + 
      16*(pow(A1ZZI,2) + pow(A1ZZR,2))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C36*C45 + C35*C46)))/262144.;
}

double GetGeneralScalar2e2mu_Part8(LeptonVectors &leptons, double A2ZZI, double A2ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(pow(A2ZZI,2) + pow(A2ZZR,2))*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       C34*(C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(pow(A2ZZI,2) + pow(A2ZZR,2))*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)))/262144.;
}

double GetGeneralScalar2e2mu_Part9(LeptonVectors &leptons, double A3ZZI, double A3ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(pow(A3ZZI,2) + pow(A3ZZR,2))*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       C34*(C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(pow(A3ZZI,2) + pow(A3ZZR,2))*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)))/262144.;
}

double GetGeneralScalar2e2mu_Part10(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A2ZZI, double A2ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(A1ZZR*A2ZZI - A1ZZI*A2ZZR)*E3456*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 + C36 - C45 - C46) - 
      8*(A1ZZR*A2ZZI - A1ZZI*A2ZZR)*E3456*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 - C36 + C45 - C46) + 
      8*(A1ZZI*A2ZZI + A1ZZR*A2ZZR)*(MZ*MZ)*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(A1ZZI*A2ZZI + A1ZZR*A2ZZR)*(MZ*MZ)*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  131072.;
}

double GetGeneralScalar2e2mu_Part11(LeptonVectors &leptons, double A2ZZI, double A2ZZR, double A3ZZI, double A3ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (32*(A2ZZI*A3ZZI + A2ZZR*A3ZZR)*E3456*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-(C36*C45) + C35*C46) + 
      32*(A2ZZI*A3ZZI + A2ZZR*A3ZZR)*E3456*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       C34*C56 - 16*(A2ZZR*A3ZZI - A2ZZI*A3ZZR)*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*C34*C56 - 
      16*(A2ZZR*A3ZZI - A2ZZI*A3ZZR)*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*C34*C56))/131072.;
}

double GetGeneralScalar2e2mu_Part12(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A3ZZI, double A3ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-8*(A1ZZI*A3ZZI + A1ZZR*A3ZZR)*E3456*(MZ*MZ)*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 - C36 - C45 + C46) - 
      8*(A1ZZI*A3ZZI + A1ZZR*A3ZZR)*E3456*(MZ*MZ)*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 + C36 + C45 + C46) + 
      8*(A1ZZR*A3ZZI - A1ZZI*A3ZZR)*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      8*(A1ZZR*A3ZZI - A1ZZI*A3ZZR)*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),
        -1)*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  131072.;
}

double GetGeneralScalar2e2mu_Part14(LeptonVectors &leptons, double A2ZAI, double A2ZAR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(pow(A2ZAI,2) + pow(A2ZAR,2))*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((MZ*MZ)*(wZ*wZ) + (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56))*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46) + 
      2*(pow(A2ZAI,2) + pow(A2ZAR,2))*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       pow(C34,-2)*pow(C56,-2)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (8*gL*gR*((MZ*MZ)*(wZ*wZ) + 
            (-MZ + Sqrt2*SqrtC34)*
             (MZ + Sqrt2*SqrtC34)*
             (-MZ + Sqrt2*SqrtC56)*
             (MZ + Sqrt2*SqrtC56))*C34*C56 + 
         (gL*gL)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C56*C56) + 
            4*(MZ*MZ)*C34*((MZ*MZ) + (wZ*wZ) - 6*C56)*
             C56 + 4*(C34*C34)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C56*C56) - 
               6*(MZ*MZ)*C56)) + 
         (gR*gR)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C56*C56) + 
            4*(MZ*MZ)*C34*((MZ*MZ) + (wZ*wZ) - 6*C56)*
             C56 + 4*(C34*C34)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C56*C56) - 
               6*(MZ*MZ)*C56)))))/262144.;
}

double GetGeneralScalar2e2mu_Part15(LeptonVectors &leptons, double A3ZAI, double A3ZAR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(pow(A3ZAI,2) + pow(A3ZAR,2))*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((MZ*MZ)*(wZ*wZ) + (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56))*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46) + 
      2*(pow(A3ZAI,2) + pow(A3ZAR,2))*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       pow(C34,-2)*pow(C56,-2)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (8*gL*gR*((MZ*MZ)*(wZ*wZ) + 
            (-MZ + Sqrt2*SqrtC34)*
             (MZ + Sqrt2*SqrtC34)*
             (-MZ + Sqrt2*SqrtC56)*
             (MZ + Sqrt2*SqrtC56))*C34*C56 + 
         (gL*gL)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C56*C56) + 
            4*(MZ*MZ)*C34*((MZ*MZ) + (wZ*wZ) - 6*C56)*
             C56 + 4*(C34*C34)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C56*C56) - 
               6*(MZ*MZ)*C56)) + 
         (gR*gR)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C56*C56) + 
            4*(MZ*MZ)*C34*((MZ*MZ) + (wZ*wZ) - 6*C56)*
             C56 + 4*(C34*C34)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C56*C56) - 
               6*(MZ*MZ)*C56)))))/262144.;
}

double GetGeneralScalar2e2mu_Part17(LeptonVectors &leptons, double A2ZAI, double A2ZAR, double A3ZAI, double A3ZAR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (16*(A2ZAI*A3ZAI + A2ZAR*A3ZAR)*E3456*(el*el)*
       ((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((MZ*MZ)*(wZ*wZ) + (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56)) - 
      4*(A2ZAR*A3ZAI - A2ZAI*A3ZAR)*(gL - gR)*(gL + gR)*(el*el)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*((C35*C35) - (C36*C36) + 
         (C45*C45) - (C46*C46))*
       ((MZ*MZ)*(wZ*wZ)*(2*C34 + 2*C56) - 
         (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-8*C34*C56 + (MZ*MZ)*(2*C34 + 2*C56))) 
- 4*(A2ZAR*A3ZAI - A2ZAI*A3ZAR)*(gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*(1.0/C56)*
       ((MZ*MZ)*(wZ*wZ)*(2*C34 + 2*C56) - 
         (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56)*
          (-8*C34*C56 + (MZ*MZ)*(2*C34 + 2*C56))) 
+ 4*(A2ZAI*A3ZAI + A2ZAR*A3ZAR)*E3456*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       pow(C34,-2)*pow(C56,-2)*
       (-(C36*C45) + C35*C46)*
       (8*gL*gR*((MZ*MZ)*(wZ*wZ) + 
            (-MZ + Sqrt2*SqrtC34)*
             (MZ + Sqrt2*SqrtC34)*
             (-MZ + Sqrt2*SqrtC56)*
             (MZ + Sqrt2*SqrtC56))*C34*C56 + 
         (gL*gL)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C56*C56) + 
            4*(MZ*MZ)*C34*((MZ*MZ) + (wZ*wZ) - 6*C56)*
             C56 + 4*(C34*C34)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C56*C56) - 
               6*(MZ*MZ)*C56)) + 
         (gR*gR)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C56*C56) + 
            4*(MZ*MZ)*C34*((MZ*MZ) + (wZ*wZ) - 6*C56)*
             C56 + 4*(C34*C34)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C56*C56) - 
               6*(MZ*MZ)*C56)))))/131072.;
}

double GetGeneralScalar2e2mu_Part20(LeptonVectors &leptons, double A2AAI, double A2AAR, double A2ZZI, double A2ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       (-((A2AAI*A2ZZI + A2AAR*A2ZZR)*(MZ*MZ)*(wZ*wZ)) + 
         (A2AAI*A2ZZI + A2AAR*A2ZZR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A2AAR*A2ZZI - A2AAI*A2ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) + 
      8*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       (-((A2AAI*A2ZZI + A2AAR*A2ZZR)*(MZ*MZ)*(wZ*wZ)) + 
         (A2AAI*A2ZZI + A2AAR*A2ZZR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A2AAR*A2ZZI - A2AAI*A2ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56))))/262144.;
}

double GetGeneralScalar2e2mu_Part21(LeptonVectors &leptons, double A3AAI, double A3AAR, double A3ZZI, double A3ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       (-((A3AAI*A3ZZI + A3AAR*A3ZZR)*(MZ*MZ)*(wZ*wZ)) + 
         (A3AAI*A3ZZI + A3AAR*A3ZZR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A3AAR*A3ZZI - A3AAI*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) + 
      8*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       (-((A3AAI*A3ZZI + A3AAR*A3ZZR)*(MZ*MZ)*(wZ*wZ)) + 
         (A3AAI*A3ZZI + A3AAR*A3ZZR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A3AAR*A3ZZI - A3AAI*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56))))/262144.;
}

double GetGeneralScalar2e2mu_Part22(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A2AAI, double A2AAR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*(gL - gR)*(gL + gR)*E3456*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (C35 + C36 - C45 - C46)*
       ((-(A1ZZR*A2AAI) + A1ZZI*A2AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) - 
      2*(gL - gR)*(gL + gR)*E3456*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (C35 - C36 + C45 - C46)*
       ((-(A1ZZR*A2AAI) + A1ZZI*A2AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) + 
      2*(el*el)*((gL+gR)*(gL+gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (-((A1ZZI*A2AAI + A1ZZR*A2AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) - 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56))*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(el*el)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (-((A1ZZI*A2AAI + A1ZZR*A2AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) - 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))))/
  131072.;
}

double GetGeneralScalar2e2mu_Part23(LeptonVectors &leptons, double A2AAI, double A2AAR, double A2ZZI, double A2ZZR, double A3AAI, double A3AAR, double A3ZZI, double A3ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*E3456*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-((A2ZZI*A3AAI + A2ZZR*A3AAR + A2AAI*A3ZZI + A2AAR*A3ZZR)*
            (MZ*MZ)*(wZ*wZ)) + 
         (A2ZZI*A3AAI + A2ZZR*A3AAR + A2AAI*A3ZZI + A2AAR*A3ZZR)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (-(A2ZZR*A3AAI) + A2ZZI*A3AAR + A2AAR*A3ZZI - A2AAI*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) + 
      8*E3456*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (-(C36*C45) + C35*C46)*
       (-((A2ZZI*A3AAI + A2ZZR*A3AAR + A2AAI*A3ZZI + A2AAR*A3ZZR)*
            (MZ*MZ)*(wZ*wZ)) + 
         (A2ZZI*A3AAI + A2ZZR*A3AAR + A2AAI*A3ZZI + A2AAR*A3ZZR)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (-(A2ZZR*A3AAI) + A2ZZI*A3AAR + A2AAR*A3ZZI - A2AAI*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) - 
      4*(gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*((-(A2ZZR*A3AAI) + A2ZZI*A3AAR - A2AAR*A3ZZI + 
            A2AAI*A3ZZR)*(MZ*MZ)*(wZ*wZ) + 
         (A2ZZR*A3AAI - A2ZZI*A3AAR + A2AAR*A3ZZI - A2AAI*A3ZZR)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A2ZZI*A3AAI + A2ZZR*A3AAR - A2AAI*A3ZZI - A2AAR*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) - 
      4*(gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*((-(A2ZZR*A3AAI) + A2ZZI*A3AAR - A2AAR*A3ZZI + 
            A2AAI*A3ZZR)*(MZ*MZ)*(wZ*wZ) + 
         (A2ZZR*A3AAI - A2ZZI*A3AAR + A2AAR*A3ZZI - A2AAI*A3ZZR)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A2ZZI*A3AAI + A2ZZR*A3AAR - A2AAI*A3ZZI - A2AAR*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56))))/131072.;
}

double GetGeneralScalar2e2mu_Part24(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A3AAI, double A3AAR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*E3456*(el*el)*((gL+gR)*(gL+gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (C35 - C36 - C45 + C46)*
       (-((A1ZZI*A3AAI + A1ZZR*A3AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) - 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) - 
      2*E3456*(el*el)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (C35 + C36 + C45 + C46)*
       (-((A1ZZI*A3AAI + A1ZZR*A3AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) - 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) + 
      2*(gL - gR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       ((-(A1ZZR*A3AAI) + A1ZZI*A3AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56)) + 
      2*(gL - gR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       ((-(A1ZZR*A3AAI) + A1ZZI*A3AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))))/
  131072.;
}

double GetGeneralScalar2e2mu_Part26(LeptonVectors &leptons, double A2AAI, double A2AAR, double A2ZAI, double A2ZAR)
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

return ((gL + gR)*(el*el*el)*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
    pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
    pow(C34,-2)*pow(C56,-2)*
    (2*pow(C36*C45 - C35*C46,2) + 
      2*(C34*C34)*(C56*C56) + 
      (pow(C36 - C45,2) + pow(C35 - C46,2))*
       C34*C56)*((A2AAR*A2ZAI - A2AAI*A2ZAR)*(MZ*MZ*MZ)*
       (wZ*wZ*wZ)*(2*C34 + 2*C56) + 
      (A2AAI*A2ZAI + A2AAR*A2ZAR)*(MZ*MZ)*(wZ*wZ)*
       (4*(C34*C34) + 4*(C56*C56) - 
         (MZ*MZ)*(2*C34 + 2*C56)) + 
      (A2AAI*A2ZAI + A2AAR*A2ZAR)*(-MZ + Sqrt2*SqrtC34)*
       (MZ + Sqrt2*SqrtC34)*((MZ*MZ) - 2*C56)*
       (-8*C34*C56 + (MZ*MZ)*(2*C34 + 2*C56)) + 
      (A2AAR*A2ZAI - A2AAI*A2ZAR)*MZ*wZ*
       (2*(MZ*MZ*MZ*MZ)*C56 + 8*(C34*C34)*C56 + 
         2*C34*((MZ*MZ*MZ*MZ) + 4*(C56*C56) - 8*(MZ*MZ)*C56)
)))/65536.;
}

double GetGeneralScalar2e2mu_Part27(LeptonVectors &leptons, double A3AAI, double A3AAR, double A3ZAI, double A3ZAR)
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

return ((gL + gR)*(el*el*el)*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*
    pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
    pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
    pow(C34,-2)*pow(C56,-2)*
    (-2*pow(C36*C45 - C35*C46,2) - 
      2*(C34*C34)*(C56*C56) + 
      (pow(C36 + C45,2) + pow(C35 + C46,2))*
       C34*C56)*((A3AAR*A3ZAI - A3AAI*A3ZAR)*(MZ*MZ*MZ)*
       (wZ*wZ*wZ)*(2*C34 + 2*C56) + 
      (A3AAI*A3ZAI + A3AAR*A3ZAR)*(MZ*MZ)*(wZ*wZ)*
       (4*(C34*C34) + 4*(C56*C56) - 
         (MZ*MZ)*(2*C34 + 2*C56)) + 
      (A3AAI*A3ZAI + A3AAR*A3ZAR)*(-MZ + Sqrt2*SqrtC34)*
       (MZ + Sqrt2*SqrtC34)*((MZ*MZ) - 2*C56)*
       (-8*C34*C56 + (MZ*MZ)*(2*C34 + 2*C56)) + 
      (A3AAR*A3ZAI - A3AAI*A3ZAR)*MZ*wZ*
       (2*(MZ*MZ*MZ*MZ)*C56 + 8*(C34*C34)*C56 + 
         2*C34*((MZ*MZ*MZ*MZ) + 4*(C56*C56) - 8*(MZ*MZ)*C56)
)))/65536.;
}

double GetGeneralScalar2e2mu_Part29(LeptonVectors &leptons, double A2AAI, double A2AAR, double A2ZAI, double A2ZAR, double A3AAI, double A3AAR, double A3ZAI, double A3ZAR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-4*(gL - gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       ((A2ZAI*A3AAI + A2ZAR*A3AAR - A2AAI*A3ZAI - A2AAR*A3ZAR)*MZ*wZ + 
         (A2ZAR*A3AAI - A2ZAI*A3AAR + A2AAR*A3ZAI - A2AAI*A3ZAR)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34))*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*(1.0/C56) - 
      4*(gL - gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*((C35*C35) - (C36*C36) + 
         (C45*C45) - (C46*C46))*
       ((A2ZAI*A3AAI + A2ZAR*A3AAR - A2AAI*A3ZAI - A2AAR*A3ZAR)*MZ*wZ + 
         (A2ZAR*A3AAI - A2ZAI*A3AAR + A2AAR*A3ZAI - A2AAI*A3ZAR)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56)) + 
      4*(gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       pow(C34,-2)*pow(C56,-2)*
       (-(C36*C45) + C35*C46)*
       (4*A2ZAI*A3AAI*(MZ*MZ*MZ*MZ)*(C34*C34) + 
         4*A2ZAR*A3AAR*(MZ*MZ*MZ*MZ)*(C34*C34) + 
         4*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ)*(C34*C34) + 
         4*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ)*(C34*C34) + 
         4*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ)*(C56*C56) + 
         4*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ)*(C56*C56) + 
         32*A2ZAI*A3AAI*(C34*C34)*(C56*C56) + 
         32*A2ZAR*A3AAR*(C34*C34)*(C56*C56) + 
         32*A2AAI*A3ZAI*(C34*C34)*(C56*C56) + 
         32*A2AAR*A3ZAR*(C34*C34)*(C56*C56) - 
         2*A2ZAI*A3AAI*(MZ*MZ*MZ*MZ*MZ*MZ)*C34 - 
         2*A2ZAR*A3AAR*(MZ*MZ*MZ*MZ*MZ*MZ)*C34 - 
         2*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ*MZ*MZ)*C34 - 
         2*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ*MZ*MZ)*C34 - 
         24*A2ZAI*A3AAI*(MZ*MZ)*(C56*C56)*C34 - 
         24*A2ZAR*A3AAR*(MZ*MZ)*(C56*C56)*C34 - 
         24*A2AAI*A3ZAI*(MZ*MZ)*(C56*C56)*C34 - 
         24*A2AAR*A3ZAR*(MZ*MZ)*(C56*C56)*C34 - 
         2*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ*MZ*MZ)*C56 - 
         2*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ*MZ*MZ)*C56 - 
         24*A2ZAI*A3AAI*(MZ*MZ)*(C34*C34)*C56 - 
         24*A2ZAR*A3AAR*(MZ*MZ)*(C34*C34)*C56 - 
         24*A2AAI*A3ZAI*(MZ*MZ)*(C34*C34)*C56 - 
         24*A2AAR*A3ZAR*(MZ*MZ)*(C34*C34)*C56 + 
         2*A2ZAI*A3AAI*(MZ*MZ*MZ*MZ)*(-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56)*C56 + 
         2*A2ZAR*A3AAR*(MZ*MZ*MZ*MZ)*(-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56)*C56 + 
         16*A2ZAI*A3AAI*(MZ*MZ*MZ*MZ)*C34*C56 + 
         16*A2ZAR*A3AAR*(MZ*MZ*MZ*MZ)*C34*C56 + 
         16*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ)*C34*C56 + 
         16*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ)*C34*C56 + 
         (-(A2ZAR*A3AAI) + A2ZAI*A3AAR + A2AAR*A3ZAI - A2AAI*A3ZAR)*
          (MZ*MZ*MZ)*(wZ*wZ*wZ)*(2*C34 + 2*C56) + 
         (A2ZAI*A3AAI + A2ZAR*A3AAR + A2AAI*A3ZAI + A2AAR*A3ZAR)*(MZ*MZ)*
          (wZ*wZ)*(4*(C34*C34) + 4*(C56*C56) - 
            (MZ*MZ)*(2*C34 + 2*C56)) - 
         (A2ZAR*A3AAI - A2ZAI*A3AAR - A2AAR*A3ZAI + A2AAI*A3ZAR)*MZ*wZ*
          (2*(MZ*MZ*MZ*MZ)*C56 + 8*(C34*C34)*C56 + 
            2*C34*((MZ*MZ*MZ*MZ) + 4*(C56*C56) - 
               8*(MZ*MZ)*C56)))))/131072.;
}

double GetGeneralScalar2e2mu_Part32(LeptonVectors &leptons, double A2ZAI, double A2ZAR, double A2ZZI, double A2ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*
       ((A2ZAR*A2ZZI - A2ZAI*A2ZZR)*MZ*wZ*(2*C34 + 2*C56) + 
         (A2ZAI*A2ZZI + A2ZAR*A2ZZR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) + 
      8*el*(gL + gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       ((A2ZAR*A2ZZI - A2ZAI*A2ZZR)*MZ*wZ*(2*C34 + 2*C56) + 
         (A2ZAI*A2ZZI + A2ZAR*A2ZZR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56)))))/
  262144.;
}

double GetGeneralScalar2e2mu_Part33(LeptonVectors &leptons, double A3ZAI, double A3ZAR, double A3ZZI, double A3ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*
       ((A3ZAR*A3ZZI - A3ZAI*A3ZZR)*MZ*wZ*(2*C34 + 2*C56) + 
         (A3ZAI*A3ZZI + A3ZAR*A3ZZR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) + 
      8*el*(gL + gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       ((A3ZAR*A3ZZI - A3ZAI*A3ZZR)*MZ*wZ*(2*C34 + 2*C56) + 
         (A3ZAI*A3ZZI + A3ZAR*A3ZZR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56)))))/
  262144.;
}

double GetGeneralScalar2e2mu_Part34(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A2ZAI, double A2ZAR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (2*el*(gL + gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (-(C36*C45*(C36 + C45 - C46)) - 
         (C35*C35)*C46 - 
         C34*(C36 + C45 + C46)*C56 + 
         C35*((C45 - C46)*C46 + 
            C36*(C45 + C46) - C34*C56))*
       (-((A1ZZR*A2ZAI - A1ZZI*A2ZAR)*MZ*wZ*(2*C34 + 2*C56)) + 
         (A1ZZI*A2ZAI + A1ZZR*A2ZAR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) + 
      2*el*(gL + gR)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56))*
       (-((A1ZZR*A2ZAI - A1ZZI*A2ZAR)*MZ*wZ*(2*C34 + 2*C56)) + 
         (A1ZZI*A2ZAI + A1ZZR*A2ZAR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) - 
      2*el*(gL - gR)*E3456*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (C35 - C36 + C45 - C46)*
       ((A1ZZI*A2ZAI + A1ZZR*A2ZAR)*MZ*wZ*
          (2*((gL+gR)*(gL+gR))*C34 + 
            2*((gL*gL) + (gR*gR))*C56) + 
         (A1ZZR*A2ZAI - A1ZZI*A2ZAR)*
          (8*(gL*gR + (gL*gL) + (gR*gR))*C34*C56 - 
            (MZ*MZ)*(2*((gL+gR)*(gL+gR))*C34 + 
               2*((gL*gL) + (gR*gR))*C56))) - 
      2*el*(gL - gR)*E3456*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (C35 + C36 - C45 - C46)*
       ((A1ZZI*A2ZAI + A1ZZR*A2ZAR)*MZ*wZ*
          (2*((gL*gL) + (gR*gR))*C34 + 2*((gL+gR)*(gL+gR))*C56) 
+ (A1ZZR*A2ZAI - A1ZZI*A2ZAR)*(8*(gL*gR + (gL*gL) + (gR*gR))*C34*
             C56 - (MZ*MZ)*
             (2*((gL*gL) + (gR*gR))*C34 + 
               2*((gL+gR)*(gL+gR))*C56)))))/131072.;
}

double GetGeneralScalar2e2mu_Part35(LeptonVectors &leptons, double A2ZAI, double A2ZAR, double A2ZZI, double A2ZZR, double A3ZAI, double A3ZAR, double A3ZZI, double A3ZZR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (8*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((-(A2ZZR*A3ZAI) + A2ZZI*A3ZAR + A2ZAR*A3ZZI - A2ZAI*A3ZZR)*MZ*wZ*
          (2*C34 + 2*C56) + 
         (A2ZZI*A3ZAI + A2ZZR*A3ZAR + A2ZAI*A3ZZI + A2ZAR*A3ZZR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) + 
      8*el*(gL + gR)*E3456*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (-(C36*C45) + C35*C46)*
       ((-(A2ZZR*A3ZAI) + A2ZZI*A3ZAR + A2ZAR*A3ZZI - A2ZAI*A3ZZR)*MZ*wZ*
          (2*C34 + 2*C56) + 
         (A2ZZI*A3ZAI + A2ZZR*A3ZAR + A2ZAI*A3ZZI + A2ZAR*A3ZZR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) - 
      4*el*(gL - gR)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) + (C36*C36) - (C45*C45) - 
         (C46*C46))*(-4*A2ZAR*A3ZZI*gL*gR*(MZ*MZ)*C34 + 
         4*A2ZAI*A3ZZR*gL*gR*(MZ*MZ)*C34 - 
         2*A2ZAR*A3ZZI*(gL*gL)*(MZ*MZ)*C34 + 
         2*A2ZAI*A3ZZR*(gL*gL)*(MZ*MZ)*C34 - 
         2*A2ZAR*A3ZZI*(gR*gR)*(MZ*MZ)*C34 + 
         2*A2ZAI*A3ZZR*(gR*gR)*(MZ*MZ)*C34 - 
         2*A2ZAR*A3ZZI*(gL*gL)*(MZ*MZ)*C56 + 
         2*A2ZAI*A3ZZR*(gL*gL)*(MZ*MZ)*C56 - 
         2*A2ZAR*A3ZZI*(gR*gR)*(MZ*MZ)*C56 + 
         2*A2ZAI*A3ZZR*(gR*gR)*(MZ*MZ)*C56 + 
         8*A2ZAR*A3ZZI*gL*gR*C34*C56 - 
         8*A2ZAI*A3ZZR*gL*gR*C34*C56 + 
         8*A2ZAR*A3ZZI*(gL*gL)*C34*C56 - 
         8*A2ZAI*A3ZZR*(gL*gL)*C34*C56 + 
         8*A2ZAR*A3ZZI*(gR*gR)*C34*C56 - 
         8*A2ZAI*A3ZZR*(gR*gR)*C34*C56 + 
         A2ZZI*A3ZAI*MZ*wZ*(2*((gL+gR)*(gL+gR))*C34 + 
            2*((gL*gL) + (gR*gR))*C56) + 
         A2ZZR*A3ZAR*MZ*wZ*(2*((gL+gR)*(gL+gR))*C34 + 
            2*((gL*gL) + (gR*gR))*C56) - 
         (A2ZAI*A3ZZI + A2ZAR*A3ZZR)*MZ*wZ*
          (2*((gL+gR)*(gL+gR))*C34 + 
            2*((gL*gL) + (gR*gR))*C56) + 
         A2ZZR*A3ZAI*(8*(gL*gR + (gL*gL) + (gR*gR))*C34*
             C56 - (MZ*MZ)*
             (2*((gL+gR)*(gL+gR))*C34 + 
               2*((gL*gL) + (gR*gR))*C56)) + 
         A2ZZI*A3ZAR*(-8*(gL*gR + (gL*gL) + (gR*gR))*C34*
             C56 + (MZ*MZ)*
             (2*((gL+gR)*(gL+gR))*C34 + 
               2*((gL*gL) + (gR*gR))*C56))) - 
      4*el*(gL - gR)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) - (C36*C36) + (C45*C45) - 
         (C46*C46))*(-2*A2ZAR*A3ZZI*(gL*gL)*(MZ*MZ)*C34 + 
         2*A2ZAI*A3ZZR*(gL*gL)*(MZ*MZ)*C34 - 
         2*A2ZAR*A3ZZI*(gR*gR)*(MZ*MZ)*C34 + 
         2*A2ZAI*A3ZZR*(gR*gR)*(MZ*MZ)*C34 - 
         4*A2ZAR*A3ZZI*gL*gR*(MZ*MZ)*C56 + 
         4*A2ZAI*A3ZZR*gL*gR*(MZ*MZ)*C56 - 
         2*A2ZAR*A3ZZI*(gL*gL)*(MZ*MZ)*C56 + 
         2*A2ZAI*A3ZZR*(gL*gL)*(MZ*MZ)*C56 - 
         2*A2ZAR*A3ZZI*(gR*gR)*(MZ*MZ)*C56 + 
         2*A2ZAI*A3ZZR*(gR*gR)*(MZ*MZ)*C56 + 
         8*A2ZAR*A3ZZI*gL*gR*C34*C56 - 
         8*A2ZAI*A3ZZR*gL*gR*C34*C56 + 
         8*A2ZAR*A3ZZI*(gL*gL)*C34*C56 - 
         8*A2ZAI*A3ZZR*(gL*gL)*C34*C56 + 
         8*A2ZAR*A3ZZI*(gR*gR)*C34*C56 - 
         8*A2ZAI*A3ZZR*(gR*gR)*C34*C56 + 
         A2ZZI*A3ZAI*MZ*wZ*(2*((gL*gL) + (gR*gR))*C34 + 
            2*((gL+gR)*(gL+gR))*C56) + 
         A2ZZR*A3ZAR*MZ*wZ*(2*((gL*gL) + (gR*gR))*C34 + 
            2*((gL+gR)*(gL+gR))*C56) - 
         (A2ZAI*A3ZZI + A2ZAR*A3ZZR)*MZ*wZ*
          (2*((gL*gL) + (gR*gR))*C34 + 2*((gL+gR)*(gL+gR))*C56) 
+ A2ZZR*A3ZAI*(8*(gL*gR + (gL*gL) + (gR*gR))*C34*C56 - 
            (MZ*MZ)*(2*((gL*gL) + (gR*gR))*C34 + 
               2*((gL+gR)*(gL+gR))*C56)) + 
         A2ZZI*A3ZAR*(-8*(gL*gR + (gL*gL) + (gR*gR))*C34*
             C56 + (MZ*MZ)*
             (2*((gL*gL) + (gR*gR))*C34 + 
               2*((gL+gR)*(gL+gR))*C56)))))/131072.;
}

double GetGeneralScalar2e2mu_Part36(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A3ZAI, double A3ZAR)
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

return (pow(Pi,-7)*(1.0/s)*pow(1 - 2*((M1*M1) + (M2*M2))*(1.0/s) + 
      (1.0/(s*s))*((M1*M1-M2*M2)*(M1*M1-M2*M2)),0.5)*
    (-2*el*(gL + gR)*E3456*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (C35 - C36 - C45 + C46)*
       (-((A1ZZR*A3ZAI - A1ZZI*A3ZAR)*MZ*wZ*(2*C34 + 2*C56)) + 
         (A1ZZI*A3ZAI + A1ZZR*A3ZAR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) - 
      2*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (C35 + C36 + C45 + C46)*
       (-((A1ZZR*A3ZAI - A1ZZI*A3ZAR)*MZ*wZ*(2*C34 + 2*C56)) + 
         (A1ZZI*A3ZAI + A1ZZR*A3ZAR)*
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) + 
      2*el*(gL - gR)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       ((C35*C35)*C46 + 
         C36*C45*(C36 - C45 + C46) + 
         C34*(C36 - C45 - C46)*C56 - 
         C35*((C46*C46) - C45*C46 + 
            C36*(C45 + C46) - C34*C56))*
       ((A1ZZI*A3ZAI + A1ZZR*A3ZAR)*MZ*wZ*
          (2*((gL+gR)*(gL+gR))*C34 + 
            2*((gL*gL) + (gR*gR))*C56) + 
         (A1ZZR*A3ZAI - A1ZZI*A3ZAR)*
          (8*(gL*gR + (gL*gL) + (gR*gR))*C34*C56 - 
            (MZ*MZ)*(2*((gL+gR)*(gL+gR))*C34 + 
               2*((gL*gL) + (gR*gR))*C56))) + 
      2*el*(gL - gR)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56))*
       ((A1ZZI*A3ZAI + A1ZZR*A3ZAR)*MZ*wZ*
          (2*((gL*gL) + (gR*gR))*C34 + 2*((gL+gR)*(gL+gR))*C56) 
+ (A1ZZR*A3ZAI - A1ZZI*A3ZAR)*(8*(gL*gR + (gL*gL) + (gR*gR))*C34*
             C56 - (MZ*MZ)*
             (2*((gL*gL) + (gR*gR))*C34 + 
               2*((gL+gR)*(gL+gR))*C56)))))/131072.;
}

