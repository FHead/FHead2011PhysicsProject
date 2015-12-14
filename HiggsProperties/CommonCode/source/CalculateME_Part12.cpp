
#include <cmath>
#include <iostream>
#include <complex>
using namespace std;

#include "CalculateME.h"
#include "AngleConversion.h"
#include "Constants.h"

double GetGeneralScalar4e_Part2(LeptonVectors &leptons, double A2AAI, double A2AAR)
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
    (4*(pow(A2AAI,2) + pow(A2AAR,2))*(el*el*el*el)*(1/(vh*vh))*pow(C36,-2)*
       pow(C45,-2)*(2*(C36*C36)*(C45*C45) + 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(-C46 + C35,2) + pow(-C34 + C56,2))*
          C36*C45) + 
      4*(pow(A2AAI,2) + pow(A2AAR,2))*(el*el*el*el)*(1/(vh*vh))*
       pow(C34,-2)*pow(C56,-2)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) + 
      2*(pow(A2AAI,2) + pow(A2AAR,2))*(el*el*el*el)*(1/(vh*vh))*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 + 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 - C46,2) - 4*C36*C45)*
          C56) + 2*(pow(A2AAI,2) + pow(A2AAR,2))*(el*el*el*el)*(1/(vh*vh))*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + pow(C35,3)*C46 + 
         pow(C46,3)*C35 - (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 + 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(-C46 + C35,2) - 
            4*C34*C56))))/1.048576e6;
}

double GetGeneralScalar4e_Part3(LeptonVectors &leptons, double A3AAI, double A3AAR)
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
    (4*(pow(A3AAI,2) + pow(A3AAR,2))*(el*el*el*el)*(1/(vh*vh))*pow(C36,-2)*
       pow(C45,-2)*(-2*(C36*C36)*(C45*C45) - 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(C46 + C35,2) + pow(C34 + C56,2))*
          C36*C45) + 
      4*(pow(A3AAI,2) + pow(A3AAR,2))*(el*el*el*el)*(1/(vh*vh))*
       pow(C34,-2)*pow(C56,-2)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) + 
      2*(pow(A3AAI,2) + pow(A3AAR,2))*(el*el*el*el)*(1/(vh*vh))*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 - 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 + C46,2) + 4*C36*C45)*
          C56) + 2*(pow(A3AAI,2) + pow(A3AAR,2))*(el*el*el*el)*(1/(vh*vh))*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + pow(C35,3)*C46 + 
         pow(C46,3)*C35 - (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 - 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(C46 + C35,2) + 
            4*C34*C56))))/1.048576e6;
}

double GetGeneralScalar4e_Part5(LeptonVectors &leptons, double A2AAI, double A2AAR, double A3AAI, double A3AAR)
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
    (8*(A2AAI*A3AAI + A2AAR*A3AAR)*E3456*(el*el*el*el)*(1/(vh*vh))*
       pow(C34,-2)*pow(C56,-2)*
       (-(C36*C45) + C35*C46) - 
      2*(A2AAI*A3AAI + A2AAR*A3AAR)*E3456*(el*el*el*el)*(1/(vh*vh))*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*((C35*C35) + (C46*C46) - 
         2*C36*C45 + 2*C34*C56) - 
      2*(A2AAI*A3AAI + A2AAR*A3AAR)*(-E3456)*(el*el*el*el)*(1/(vh*vh))*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*((C46*C46) + (C35*C35) + 
         2*C36*C45 - 2*C34*C56) + 
      8*(A2AAI*A3AAI + A2AAR*A3AAR)*(-E3456)*(el*el*el*el)*(1/(vh*vh))*
       pow(C36,-2)*pow(C45,-2)*
       (C46*C35 - C34*C56)))/524288.;
}

double GetGeneralScalar4e_Part7(LeptonVectors &leptons, double A1ZZI, double A1ZZR)
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
       (C36*C45 + C35*C46) + 
      16*(pow(A1ZZI,2) + pow(A1ZZR,2))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (C46*C35 - C34*C56) + 
      16*(pow(A1ZZI,2) + pow(A1ZZR,2))*(MZ*MZ*MZ*MZ)*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (C46*C35 + C34*C56) + 
      32*(pow(A1ZZI,2) + pow(A1ZZR,2))*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       C46*C35*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
         (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (MZ*MZ)*(wZ*wZ)*(2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
            (MZ*MZ)*(2*C36 + 2*C34) - 
            2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
            2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
               2*C56))) + 
      32*(pow(A1ZZI,2) + pow(A1ZZR,2))*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(MZ*MZ*MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),
        -1)*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       C35*C46*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
         (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (MZ*MZ)*(wZ*wZ)*(2*(MZ*MZ*MZ*MZ) - 
            2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
            2*C34*(-(MZ*MZ) + 2*C36 + 2*C45 - 
               2*C56) + 4*C45*C56 - 
            (MZ*MZ)*(2*C45 + 2*C56)))))/1.048576e6;
}

double GetGeneralScalar4e_Part8(LeptonVectors &leptons, double A2ZZI, double A2ZZR)
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
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (2*(C36*C36)*(C45*C45) + 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(-C46 + C35,2) + pow(-C34 + C56,2))*
          C36*C45) + 
      16*(pow(A2ZZI,2) + pow(A2ZZR,2))*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       C34*(C35 - C36 - C45 + C46)*
       (C35 + C36 + C45 + C46)*C56 + 
      16*(pow(A2ZZI,2) + pow(A2ZZR,2))*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       C36*C45*(-C34 + C46 + C35 - C56)*
       (C34 + C46 + C35 + C56) + 
      16*(pow(A2ZZI,2) + pow(A2ZZR,2))*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56) - 
      16*MZ*wZ*(-E3456)*(pow(A2ZZI,2) + pow(A2ZZR,2))*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-(C46*C46) + (C35*C35))*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
          (-(Sqrt2*SqrtC36) + 
            Sqrt2*SqrtC34)*
          (Sqrt2*SqrtC36 + Sqrt2*SqrtC34) + 
         2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
            2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 - 
         2*C45*((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
            4*C36*C34 + 2*(2*C36 - 2*C34)*C56)
) + 16*(pow(A2ZZI,2) + pow(A2ZZR,2))*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 + 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(-C46 + C35,2) - 
            4*C34*C56))*
       ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (MZ*MZ)*(wZ*wZ)*(2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
            (MZ*MZ)*(2*C36 + 2*C34) - 
            2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
            2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
               2*C56))) - 
      16*MZ*wZ*E3456*(pow(A2ZZI,2) + pow(A2ZZR,2))*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) - (C46*C46))*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
          (Sqrt2*SqrtC45 - Sqrt2*SqrtC56)*
          (Sqrt2*SqrtC45 + Sqrt2*SqrtC56) + 
         2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
            2*C45*(-2*(MZ*MZ) + 2*C56)) - 
         2*C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
            4*C45*C56 + 2*C36*(-2*C45 + 2*C56)
)) + 16*(pow(A2ZZI,2) + pow(A2ZZR,2))*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 + 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 - C46,2) - 4*C36*C45)*
          C56)*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
         (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (MZ*MZ)*(wZ*wZ)*(2*(MZ*MZ*MZ*MZ) - 
            2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
            2*C34*(-(MZ*MZ) + 2*C36 + 2*C45 - 
               2*C56) + 4*C45*C56 - 
            (MZ*MZ)*(2*C45 + 2*C56)))))/1.048576e6;
}

double GetGeneralScalar4e_Part9(LeptonVectors &leptons, double A3ZZI, double A3ZZR)
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
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-2*(C36*C36)*(C45*C45) - 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(C46 + C35,2) + pow(C34 + C56,2))*
          C36*C45) + 
      16*(pow(A3ZZI,2) + pow(A3ZZR,2))*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       C34*(C35 + C36 - C45 - C46)*
       (C35 - C36 + C45 - C46)*C56 + 
      16*(pow(A3ZZI,2) + pow(A3ZZR,2))*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       C36*C45*(C34 - C46 + C35 - C56)*
       (-C34 - C46 + C35 + C56) + 
      16*(pow(A3ZZI,2) + pow(A3ZZR,2))*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56) - 
      16*MZ*wZ*(-E3456)*(pow(A3ZZI,2) + pow(A3ZZR,2))*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-(C46*C46) + (C35*C35))*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
          (-(Sqrt2*SqrtC36) + 
            Sqrt2*SqrtC34)*
          (Sqrt2*SqrtC36 + Sqrt2*SqrtC34) + 
         2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
            2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 - 
         2*C45*((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
            4*C36*C34 + 2*(2*C36 - 2*C34)*C56)
) + 16*(pow(A3ZZI,2) + pow(A3ZZR,2))*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 - 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(C46 + C35,2) + 
            4*C34*C56))*
       ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (MZ*MZ)*(wZ*wZ)*(2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
            (MZ*MZ)*(2*C36 + 2*C34) - 
            2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
            2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
               2*C56))) - 
      16*MZ*wZ*E3456*(pow(A3ZZI,2) + pow(A3ZZR,2))*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) - (C46*C46))*
       ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
          (Sqrt2*SqrtC45 - Sqrt2*SqrtC56)*
          (Sqrt2*SqrtC45 + Sqrt2*SqrtC56) + 
         2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
            2*C45*(-2*(MZ*MZ) + 2*C56)) - 
         2*C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
            4*C45*C56 + 2*C36*(-2*C45 + 2*C56)
)) + 16*(pow(A3ZZI,2) + pow(A3ZZR,2))*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 - 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 + C46,2) + 4*C36*C45)*
          C56)*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
         (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (MZ*MZ)*(wZ*wZ)*(2*(MZ*MZ*MZ*MZ) - 
            2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
            2*C34*(-(MZ*MZ) + 2*C36 + 2*C45 - 
               2*C56) + 4*C45*C56 - 
            (MZ*MZ)*(2*C45 + 2*C56)))))/1.048576e6;
}

double GetGeneralScalar4e_Part10(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A2ZZI, double A2ZZR)
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
       (C35 - C36 + C45 - C46) - 
      8*(A1ZZR*A2ZZI - A1ZZI*A2ZZR)*(-E3456)*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (C34 - C46 + C35 - C56) - 
      8*(A1ZZR*A2ZZI - A1ZZI*A2ZZR)*(-E3456)*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-C34 - C46 + C35 + C56) + 
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
            C46*(C45 + C46) - C34*C56)) + 
      8*(A1ZZI*A2ZZI + A1ZZR*A2ZZR)*(MZ*MZ)*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-((C35*C35)*C46) + 
         C36*C45*(C34 - C46 + C56) + 
         C34*C56*(C34 + C46 + C56) + 
         C35*(-(C46*(C34 + C46)) - 
            C36*C45 + (C34 - C46)*C56)) + 
      8*(A1ZZI*A2ZZI + A1ZZR*A2ZZR)*(MZ*MZ)*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-((C35*C35)*C46) - 
         C34*C56*(C34 - C46 + C56) - 
         C36*C45*(C34 + C46 + C56) + 
         C35*((C34 - C46)*C46 - 
            C36*C45 + (C34 + C46)*C56)) - 
      16*(-E3456)*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C46 - C35)*
       (A1ZZI*(A2ZZI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-(Sqrt2*SqrtC36) + 
                  Sqrt2*SqrtC34)*
                (Sqrt2*SqrtC36 + 
                  Sqrt2*SqrtC34) + 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 - 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A2ZZR*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
               (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                ((MZ*MZ) - 2*C56) + 
               (MZ*MZ)*(wZ*wZ)*
                (-2*(MZ*MZ*MZ*MZ) - 4*C36*C34 + 
                  (MZ*MZ)*(2*C36 + 2*C34) + 
                  2*C45*
                   ((MZ*MZ) + 2*C36 - 2*C34 - 2*C56) + 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56))) + 
         A1ZZR*(A2ZZR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-(Sqrt2*SqrtC36) + 
                  Sqrt2*SqrtC34)*
                (Sqrt2*SqrtC36 + 
                  Sqrt2*SqrtC34) + 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 - 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A2ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
                  (MZ*MZ)*(2*C36 + 2*C34) - 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
                  2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                     2*C56))))) - 
      16*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C46 + C35)*
       (C46*C35 - C36*C45 + C34*C56)*
       (A1ZZI*(A2ZZR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-(Sqrt2*SqrtC36) + 
                  Sqrt2*SqrtC34)*
                (Sqrt2*SqrtC36 + 
                  Sqrt2*SqrtC34) + 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 - 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A2ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
                  (MZ*MZ)*(2*C36 + 2*C34) - 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
                  2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                     2*C56)))) + 
         A1ZZR*(A2ZZI*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (-(Sqrt2*SqrtC36) + 
                    Sqrt2*SqrtC34)*
                  (Sqrt2*SqrtC36 + 
                    Sqrt2*SqrtC34)) - 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 + 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A2ZZR*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
                  (MZ*MZ)*(2*C36 + 2*C34) - 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
                  2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                     2*C56))))) - 
      16*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 + C46)*
       (C36*C45 + C35*C46 - C34*C56)*
       (A1ZZI*(A2ZZR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (Sqrt2*SqrtC45 - 
                  Sqrt2*SqrtC56)*
                (Sqrt2*SqrtC45 + 
                  Sqrt2*SqrtC56) + 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) - 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A2ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) - 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
                  2*C34*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56) 
+ 4*C45*C56 - (MZ*MZ)*(2*C45 + 2*C56)))) + 
         A1ZZR*(A2ZZI*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (Sqrt2*SqrtC45 - 
                    Sqrt2*SqrtC56)*
                  (Sqrt2*SqrtC45 + 
                    Sqrt2*SqrtC56)) - 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A2ZZR*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) - 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
                  2*C34*(-(MZ*MZ) + 2*C36 + 2*C45 - 
                     2*C56) + 4*C45*C56 - 
                  (MZ*MZ)*(2*C45 + 2*C56))))) - 
      16*E3456*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-C35 + C46)*
       (A1ZZR*(A2ZZR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (Sqrt2*SqrtC45 - 
                  Sqrt2*SqrtC56)*
                (Sqrt2*SqrtC45 + 
                  Sqrt2*SqrtC56) + 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) - 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A2ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) - 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
                  2*C34*(-(MZ*MZ) + 2*C36 + 2*C45 - 
                     2*C56) + 4*C45*C56 - 
                  (MZ*MZ)*(2*C45 + 2*C56)))) + 
         A1ZZI*(A2ZZI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (Sqrt2*SqrtC45 - 
                  Sqrt2*SqrtC56)*
                (Sqrt2*SqrtC45 + 
                  Sqrt2*SqrtC56) + 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) - 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A2ZZR*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C45)*
                ((MZ*MZ) - 2*C56) + 
               (MZ*MZ)*(wZ*wZ)*
                (-2*(MZ*MZ*MZ*MZ) + 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) - 
                  4*C45*C56 + 
                  2*C34*((MZ*MZ) - 2*C36 - 2*C45 + 
                     2*C56) + (MZ*MZ)*(2*C45 + 2*C56)))))
))/524288.;
}

double GetGeneralScalar4e_Part11(LeptonVectors &leptons, double A2ZZI, double A2ZZR, double A3ZZI, double A3ZZR)
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
      32*(A2ZZI*A3ZZI + A2ZZR*A3ZZR)*(-E3456)*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       C36*C45 - 16*(A2ZZR*A3ZZI - A2ZZI*A3ZZR)*
       ((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((C34*C34) - (C46*C46) + (C35*C35) - 
         (C56*C56))*C36*C45 - 
      16*(A2ZZR*A3ZZI - A2ZZI*A3ZZR)*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-(C34*C34) - (C46*C46) + (C35*C35) + 
         (C56*C56))*C36*C45 + 
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
         (C46*C46))*C34*C56 + 
      32*(A2ZZI*A3ZZI + A2ZZR*A3ZZR)*(-E3456)*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (C46*C35 - C34*C56) - 
      16*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-(C46*C46) + (C35*C35))*
       (C46*C35 - C36*C45 - C34*C56)*
       (A2ZZI*(A3ZZI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-(Sqrt2*SqrtC36) + 
                  Sqrt2*SqrtC34)*
                (Sqrt2*SqrtC36 + 
                  Sqrt2*SqrtC34) + 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 - 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A3ZZR*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
               (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                ((MZ*MZ) - 2*C56) + 
               (MZ*MZ)*(wZ*wZ)*
                (-2*(MZ*MZ*MZ*MZ) - 4*C36*C34 + 
                  (MZ*MZ)*(2*C36 + 2*C34) + 
                  2*C45*
                   ((MZ*MZ) + 2*C36 - 2*C34 - 2*C56) + 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56))) + 
         A2ZZR*(A3ZZR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-(Sqrt2*SqrtC36) + 
                  Sqrt2*SqrtC34)*
                (Sqrt2*SqrtC36 + 
                  Sqrt2*SqrtC34) + 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 - 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A3ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
                  (MZ*MZ)*(2*C36 + 2*C34) - 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
                  2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                     2*C56))))) - 
      16*(-E3456)*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C46*C46) + (C35*C35) + 2*C36*C45 - 
         2*C34*C56)*
       (A2ZZI*(A3ZZR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-(Sqrt2*SqrtC36) + 
                  Sqrt2*SqrtC34)*
                (Sqrt2*SqrtC36 + 
                  Sqrt2*SqrtC34) + 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 - 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A3ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
                  (MZ*MZ)*(2*C36 + 2*C34) - 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
                  2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                     2*C56)))) + 
         A2ZZR*(A3ZZI*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (-(Sqrt2*SqrtC36) + 
                    Sqrt2*SqrtC34)*
                  (Sqrt2*SqrtC36 + 
                    Sqrt2*SqrtC34)) - 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 + 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A3ZZR*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
                  (MZ*MZ)*(2*C36 + 2*C34) - 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
                  2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                     2*C56))))) - 
      16*E3456*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) + (C46*C46) - 2*C36*C45 + 
         2*C34*C56)*
       (A2ZZI*(A3ZZR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (Sqrt2*SqrtC45 - 
                  Sqrt2*SqrtC56)*
                (Sqrt2*SqrtC45 + 
                  Sqrt2*SqrtC56) + 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) - 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A3ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) - 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
                  2*C34*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56) 
+ 4*C45*C56 - (MZ*MZ)*(2*C45 + 2*C56)))) + 
         A2ZZR*(A3ZZI*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (Sqrt2*SqrtC45 - 
                    Sqrt2*SqrtC56)*
                  (Sqrt2*SqrtC45 + 
                    Sqrt2*SqrtC56)) - 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A3ZZR*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) - 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
                  2*C34*(-(MZ*MZ) + 2*C36 + 2*C45 - 
                     2*C56) + 4*C45*C56 - 
                  (MZ*MZ)*(2*C45 + 2*C56))))) - 
      16*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35) - (C46*C46))*
       (-(C36*C45) + C35*C46 - C34*C56)*
       (A2ZZR*(A3ZZR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (Sqrt2*SqrtC45 - 
                  Sqrt2*SqrtC56)*
                (Sqrt2*SqrtC45 + 
                  Sqrt2*SqrtC56) + 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) - 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A3ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) - 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
                  2*C34*(-(MZ*MZ) + 2*C36 + 2*C45 - 
                     2*C56) + 4*C45*C56 - 
                  (MZ*MZ)*(2*C45 + 2*C56)))) + 
         A2ZZI*(A3ZZI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (Sqrt2*SqrtC45 - 
                  Sqrt2*SqrtC56)*
                (Sqrt2*SqrtC45 + 
                  Sqrt2*SqrtC56) + 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) - 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A3ZZR*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C45)*
                ((MZ*MZ) - 2*C56) + 
               (MZ*MZ)*(wZ*wZ)*
                (-2*(MZ*MZ*MZ*MZ) + 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) - 
                  4*C45*C56 + 
                  2*C34*((MZ*MZ) - 2*C36 - 2*C45 + 
                     2*C56) + (MZ*MZ)*(2*C45 + 2*C56)))))
))/524288.;
}

double GetGeneralScalar4e_Part12(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A3ZZI, double A3ZZR)
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
       (C35 + C36 + C45 + C46) - 
      8*(A1ZZI*A3ZZI + A1ZZR*A3ZZR)*(-E3456)*(MZ*MZ)*(1/(vh*vh))*
       ((gL*gL+gR*gR)*(gL*gL+gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-C34 + C46 + C35 - C56) - 
      8*(A1ZZI*A3ZZI + A1ZZR*A3ZZR)*(-E3456)*(MZ*MZ)*(1/(vh*vh))*
       ((gL*gL-gR*gR)*(gL*gL-gR*gR))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (C34 + C46 + C35 + C56) + 
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
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      8*(A1ZZR*A3ZZI - A1ZZI*A3ZZR)*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((C35*C35)*C46 + 
         C34*(C34 + C46 - C56)*C56 - 
         C36*C45*(-C34 + C46 + C56) - 
         C35*(C46*(C34 + C46) - 
            C36*C45 + (C34 - C46)*C56)) + 
      8*(A1ZZR*A3ZZI - A1ZZI*A3ZZR)*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((C35*C35)*C46 + 
         C36*C45*(-C34 - C46 + C56) + 
         C34*C56*(-C34 + C46 + C56) - 
         C35*((C46*C46) - C34*C46 - 
            C36*C45 + (C34 + C46)*C56)) + 
      16*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (-C46 + C35)*
       (C46*C35 + C36*C45 - C34*C56)*
       (A1ZZI*(A3ZZI*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (-(Sqrt2*SqrtC36) + 
                    Sqrt2*SqrtC34)*
                  (Sqrt2*SqrtC36 + 
                    Sqrt2*SqrtC34)) - 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 + 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A3ZZR*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
               (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                ((MZ*MZ) - 2*C56) + 
               (MZ*MZ)*(wZ*wZ)*
                (-2*(MZ*MZ*MZ*MZ) - 4*C36*C34 + 
                  (MZ*MZ)*(2*C36 + 2*C34) + 
                  2*C45*
                   ((MZ*MZ) + 2*C36 - 2*C34 - 2*C56) + 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56))) + 
         A1ZZR*(A3ZZR*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (-(Sqrt2*SqrtC36) + 
                    Sqrt2*SqrtC34)*
                  (Sqrt2*SqrtC36 + 
                    Sqrt2*SqrtC34)) - 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 + 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A3ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
                  (MZ*MZ)*(2*C36 + 2*C34) - 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
                  2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                     2*C56))))) - 
      16*(-E3456)*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C46 + C35)*
       (A1ZZI*(A3ZZR*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (-(Sqrt2*SqrtC36) + 
                    Sqrt2*SqrtC34)*
                  (Sqrt2*SqrtC36 + 
                    Sqrt2*SqrtC34)) - 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 + 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A3ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
                  (MZ*MZ)*(2*C36 + 2*C34) - 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
                  2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                     2*C56)))) + 
         A1ZZR*(A3ZZI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-(Sqrt2*SqrtC36) + 
                  Sqrt2*SqrtC34)*
                (Sqrt2*SqrtC36 + 
                  Sqrt2*SqrtC34) + 
               2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34)*C56 - 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56)) + 
            A3ZZR*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 4*C36*C34 - 
                  (MZ*MZ)*(2*C36 + 2*C34) - 
                  2*((MZ*MZ) - 2*C36 + 2*C34)*C56 + 
                  2*C45*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                     2*C56))))) - 
      16*E3456*((gL*gL*gL*gL) + (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 + C46)*
       (A1ZZI*(A3ZZR*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (Sqrt2*SqrtC45 - 
                    Sqrt2*SqrtC56)*
                  (Sqrt2*SqrtC45 + 
                    Sqrt2*SqrtC56)) - 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A3ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) - 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
                  2*C34*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56) 
+ 4*C45*C56 - (MZ*MZ)*(2*C45 + 2*C56)))) + 
         A1ZZR*(A3ZZI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (Sqrt2*SqrtC45 - 
                  Sqrt2*SqrtC56)*
                (Sqrt2*SqrtC45 + 
                  Sqrt2*SqrtC56) + 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) - 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A3ZZR*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) - 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
                  2*C34*(-(MZ*MZ) + 2*C36 + 2*C45 - 
                     2*C56) + 4*C45*C56 - 
                  (MZ*MZ)*(2*C45 + 2*C56))))) + 
      16*((gL*gL*gL*gL) - (gR*gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (C35 - C46)*
       (-(C36*C45) + C35*C46 + C34*C56)*
       (A1ZZR*(A3ZZR*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (Sqrt2*SqrtC45 - 
                    Sqrt2*SqrtC56)*
                  (Sqrt2*SqrtC45 + 
                    Sqrt2*SqrtC56)) - 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A3ZZI*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                (-MZ + Sqrt2*SqrtC36)*
                (MZ + Sqrt2*SqrtC36)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                (-MZ + Sqrt2*SqrtC56)*
                (MZ + Sqrt2*SqrtC56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) - 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) + 
                  2*C34*(-(MZ*MZ) + 2*C36 + 2*C45 - 
                     2*C56) + 4*C45*C56 - 
                  (MZ*MZ)*(2*C45 + 2*C56)))) + 
         A1ZZI*(A3ZZI*MZ*wZ*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  (Sqrt2*SqrtC45 - 
                    Sqrt2*SqrtC56)*
                  (Sqrt2*SqrtC45 + 
                    Sqrt2*SqrtC56)) - 
               2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56))) + 
            A3ZZR*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C45)*
                ((MZ*MZ) - 2*C56) + 
               (MZ*MZ)*(wZ*wZ)*
                (-2*(MZ*MZ*MZ*MZ) + 
                  2*C36*((MZ*MZ) + 2*C45 - 2*C56) - 
                  4*C45*C56 + 
                  2*C34*((MZ*MZ) - 2*C36 - 2*C45 + 
                     2*C56) + (MZ*MZ)*(2*C45 + 2*C56)))))
))/524288.;
}

double GetGeneralScalar4e_Part14(LeptonVectors &leptons, double A2ZAI, double A2ZAR)
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
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow(C36,-2)*pow(C45,-2)*
       (2*(C36*C36)*(C45*C45) + 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(-C46 + C35,2) + pow(-C34 + C56,2))*
          C36*C45)*
       (8*gL*gR*((MZ*MZ)*(wZ*wZ) + 
            (-MZ + Sqrt2*SqrtC36)*
             (MZ + Sqrt2*SqrtC36)*
             (-MZ + Sqrt2*SqrtC45)*
             (MZ + Sqrt2*SqrtC45))*C36*C45 + 
         (gL*gL)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
            4*(C45*C45)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C36*C36) - 
               6*(MZ*MZ)*C36) + 
            4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 6*C36)*C36*
             C45) + (gR*gR)*
          (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
            4*(C45*C45)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C36*C36) - 
               6*(MZ*MZ)*C36) + 
            4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 6*C36)*C36*
             C45)) + 8*(pow(A2ZAI,2) + pow(A2ZAR,2))*(el*el)*
       ((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((MZ*MZ)*(wZ*wZ) + (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45))*
       (-C34 + C46 + C35 - C56)*
       (C34 + C46 + C35 + C56) - 
      (gL - gR)*(gL + gR)*MZ*wZ*(-E3456)*
       (pow(A2ZAI,2) + pow(A2ZAR,2))*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(2*C45*
          (4*(C56*C56)*
             ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C36*C36) - 
                  8*(MZ*MZ)*C36) + 
               8*(C34*C34)*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C36*C36) - 
                  8*(MZ*MZ)*C36) - 
               4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 8*C36)*C34
) + 2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
             (8*(MZ*MZ)*(C36*C36) + 
               2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C36*C36) - 
                  8*(MZ*MZ)*C36)*C34) + 
            4*(MZ*MZ*MZ*MZ)*(4*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
               4*(C34*C34)*
                (-(MZ*MZ) - (wZ*wZ) + 8*C36) - 
               32*(C36*C36)*C34)*C56) + 
         2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
          (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
             (-(Sqrt2*SqrtC36) + 
               Sqrt2*SqrtC34)*
             (Sqrt2*SqrtC36 + 
               Sqrt2*SqrtC34)*C34 + 
            4*(C56*C56)*
             ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 8*(C34*C34) - 
               2*(2*(MZ*MZ) + 2*C36)*C34) - 
            2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
               4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
               16*(MZ*MZ)*C36*C34)*C56) + 
         4*(C45*C45)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
             C34*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
               8*(C36*C36) - 4*(MZ*MZ)*C36 - 
               4*C36*C34) + 
            4*(-(Sqrt2*SqrtC36) + 
               Sqrt2*SqrtC34)*
             (Sqrt2*SqrtC36 + 
               Sqrt2*SqrtC34)*(C56*C56)*
             (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 8*C36*C34) 
- 2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 8*(C36*C36))*
                (C34*C34) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 8*(C36*C36) - 
                  4*(MZ*MZ)*C36) - 
               8*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                  8*(MZ*MZ)*(C36*C36) - 4*(MZ*MZ*MZ*MZ)*C36)*
                C34)*C56)) + 
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
               6*(MZ*MZ)*C56))) - 
      (gL - gR)*(gL + gR)*MZ*wZ*E3456*
       (pow(A2ZAI,2) + pow(A2ZAR,2))*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
          (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
             (Sqrt2*SqrtC45 - 
               Sqrt2*SqrtC56)*
             (Sqrt2*SqrtC45 + 
               Sqrt2*SqrtC56)*C45 - 
            2*C36*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
               16*(MZ*MZ)*C45*C56 + 
               4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
            4*(C36*C36)*
             ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 8*(C45*C45) - 
               2*C45*(2*(MZ*MZ) + 2*C56))) + 
         2*C34*(4*(MZ*MZ*MZ*MZ)*C36*
             (4*((MZ*MZ) + (wZ*wZ))*(C56*C56) - 
               32*(C56*C56)*C45 + 
               4*(C45*C45)*(-(MZ*MZ) - (wZ*wZ) + 8*C56)) 
+ 4*(C36*C36)*(-4*(MZ*MZ*MZ*MZ)*C45*
                ((MZ*MZ) + (wZ*wZ) - 8*C56) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
                  8*(MZ*MZ)*C56) + 
               8*(C45*C45)*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
                  8*(MZ*MZ)*C56)) + 
            2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
             (8*(MZ*MZ)*(C56*C56) + 
               2*C45*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                  4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
         4*(C34*C34)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
             C45*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
               8*(C56*C56) - 4*(MZ*MZ)*C56 - 
               4*C45*C56) + 
            4*(C36*C36)*
             (Sqrt2*SqrtC45 - 
               Sqrt2*SqrtC56)*
             (Sqrt2*SqrtC45 + 
               Sqrt2*SqrtC56)*
             (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 8*C45*C56) 
- 2*C36*(4*(C45*C45)*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 8*(C56*C56)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 8*(C56*C56) - 
                  4*(MZ*MZ)*C56) - 
               8*C45*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                  8*(MZ*MZ)*(C56*C56) - 4*(MZ*MZ*MZ*MZ)*C56)))) + 
      (pow(A2ZAI,2) + pow(A2ZAR,2))*(el*el)*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 + 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(-C46 + C35,2) - 
            4*C34*C56))*
       (4*(C45*C45)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
             ((-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 6*(MZ*MZ)*C36) 
+ (MZ*MZ)*(wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) + 
            4*(C56*C56)*
             ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 6*(MZ*MZ)*C36)*
                ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 6*(MZ*MZ)*C34) 
+ (MZ*MZ)*(wZ*wZ)*(2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) + 
                  8*(C34*C34) + 4*C36*C34 - 
                  3*(MZ*MZ)*(2*C36 + 2*C34))) + 
            2*(MZ*MZ)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ) + (wZ*wZ) - 4*C36)*
                  ((MZ*MZ) - 2*C36)) + 
               4*(C34*C34)*
                (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                  24*(C36*C36) + 
                  2*(9*(MZ*MZ) + (wZ*wZ))*C36) + 
               8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36)*
                ((MZ*MZ) - 2*C36)*C34)*C56) + 
         2*(MZ*MZ)*C45*
          (4*(C56*C56)*
             ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34) - 
               ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 8*(MZ*MZ)*C36)*
                ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 6*(MZ*MZ)*C34) 
+ (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 12*(MZ*MZ)*(C36*C36) - 
                  8*(MZ*MZ)*(C34*C34) + 8*(MZ*MZ*MZ*MZ)*C36 + 
                  2*pow(-2*(MZ*MZ) + 2*C36,2)*C34)) + 
            2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
             ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 8*(MZ*MZ)*C36) 
+ (wZ*wZ)*(2*(MZ*MZ*MZ*MZ) + 4*(C36*C36) - 
                  (MZ*MZ)*(8*C36 + 2*C34))) + 
            2*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
               (MZ*MZ)*((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                  8*(MZ*MZ)*C36)*
                ((MZ*MZ*MZ*MZ) + 12*(C34*C34) - 8*(MZ*MZ)*C34) 
+ (MZ*MZ)*(wZ*wZ*wZ*wZ)*(3*(MZ*MZ*MZ*MZ) + 4*(C36*C36) + 
                  4*(C34*C34) - 
                  4*(MZ*MZ)*(2*C36 + 2*C34)) + 
               (wZ*wZ)*(3*pow(MZ,8) + 
                  16*(C36*C36)*(C34*C34) - 
                  8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C34) - 
                  16*(MZ*MZ)*C36*C34*
                   (2*C36 + 2*C34) + 
                  4*(MZ*MZ*MZ*MZ)*
                   (4*(C36*C36) + 4*(C34*C34) + 
                     16*C36*C34)))*C56) + 
         2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
          ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
            (-MZ + Sqrt2*SqrtC34)*
             (MZ + Sqrt2*SqrtC34)*
             ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
             (-8*C34*C56 + 
               (MZ*MZ)*(2*C34 + 2*C56)) + 
            (MZ*MZ)*(wZ*wZ)*
             (8*(C34*C34)*C36 + 8*(C56*C56)*C36 + 
               8*(C56*C56)*C34 + 
               8*(C34*C34)*C56 + 
               2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
               (MZ*MZ)*(4*(C34*C34) + 4*(C56*C56) + 
                  16*C34*C56 + 
                  2*C36*(2*C34 + 2*C56))))) + 
      (pow(A2ZAI,2) + pow(A2ZAR,2))*(el*el)*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),
        -1)*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 + 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 - C46,2) - 4*C36*C45)*
          C56)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
          ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
            (-MZ + Sqrt2*SqrtC45)*
             (MZ + Sqrt2*SqrtC45)*
             ((MZ*MZ) - 2*C36)*
             (-8*C36*C45 + 
               (MZ*MZ)*(2*C36 + 2*C45))*
             ((MZ*MZ) - 2*C56) + 
            (MZ*MZ)*(wZ*wZ)*
             (8*(C45*C45)*C36 + 8*(C36*C36)*C45 + 
               2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
               8*(C36*C36)*C56 + 
               8*(C45*C45)*C56 - 
               (MZ*MZ)*(4*(C36*C36) + 4*(C45*C45) + 
                  16*C36*C45 + 
                  2*(2*C36 + 2*C45)*C56))) + 
         4*(C34*C34)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
             ((MZ*MZ)*(wZ*wZ)*
                (-(MZ*MZ) + 2*C45 + 2*C56) + 
               (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 6*(MZ*MZ)*C56)) + 
            2*(MZ*MZ)*C36*
             (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                  ((MZ*MZ) - 2*C56)) + 
               8*(MZ*MZ)*C45*
                ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                ((MZ*MZ) - 2*C56) + 
               4*(C45*C45)*
                (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                  24*(C56*C56) + 
                  2*(9*(MZ*MZ) + (wZ*wZ))*C56)) + 
            4*(C36*C36)*
             ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 6*(MZ*MZ)*C45)*
                ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 6*(MZ*MZ)*C56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) + 8*(C56*C56) + 
                  4*C45*C56 - 
                  3*(MZ*MZ)*(2*C45 + 2*C56)))) + 
         2*(MZ*MZ)*C34*
          (4*(C36*C36)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45) - 
               ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 6*(MZ*MZ)*C45)*
                ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 8*(MZ*MZ)*C56) + 
               (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 8*(MZ*MZ)*(C45*C45) - 
                  12*(MZ*MZ)*(C56*C56) + 
                  2*pow(-2*(MZ*MZ) + 2*C56,2)*C45 + 
                  8*(MZ*MZ*MZ*MZ)*C56)) + 
            2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
             ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
               (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 8*(MZ*MZ)*C56) + 
               (wZ*wZ)*(2*(MZ*MZ*MZ*MZ) + 4*(C56*C56) - 
                  (MZ*MZ)*(2*C45 + 8*C56))) + 
            2*C36*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
               (MZ*MZ)*((MZ*MZ*MZ*MZ) + 12*(C45*C45) - 
                  8*(MZ*MZ)*C45)*
                ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 8*(MZ*MZ)*C56) + 
               (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                (3*(MZ*MZ*MZ*MZ) + 4*(C45*C45) + 4*(C56*C56) - 
                  4*(MZ*MZ)*(2*C45 + 2*C56)) + 
               (wZ*wZ)*(3*pow(MZ,8) + 
                  16*(C45*C45)*(C56*C56) - 
                  8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C45 + 2*C56) - 
                  16*(MZ*MZ)*C45*C56*
                   (2*C45 + 2*C56) + 
                  4*(MZ*MZ*MZ*MZ)*(4*(C45*C45) + 4*(C56*C56) + 
                     16*C45*C56)))))))/1.048576e6;
}

double GetGeneralScalar4e_Part15(LeptonVectors &leptons, double A3ZAI, double A3ZAR)
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
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow(C36,-2)*pow(C45,-2)*
       (-2*(C36*C36)*(C45*C45) - 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(C46 + C35,2) + pow(C34 + C56,2))*
          C36*C45)*
       (8*gL*gR*((MZ*MZ)*(wZ*wZ) + 
            (-MZ + Sqrt2*SqrtC36)*
             (MZ + Sqrt2*SqrtC36)*
             (-MZ + Sqrt2*SqrtC45)*
             (MZ + Sqrt2*SqrtC45))*C36*C45 + 
         (gL*gL)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
            4*(C45*C45)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C36*C36) - 
               6*(MZ*MZ)*C36) + 
            4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 6*C36)*C36*
             C45) + (gR*gR)*
          (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
            4*(C45*C45)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C36*C36) - 
               6*(MZ*MZ)*C36) + 
            4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 6*C36)*C36*
             C45)) + 8*(pow(A3ZAI,2) + pow(A3ZAR,2))*(el*el)*
       ((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((MZ*MZ)*(wZ*wZ) + (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45))*
       (C34 - C46 + C35 - C56)*
       (-C34 - C46 + C35 + C56) - 
      (gL - gR)*(gL + gR)*MZ*wZ*(-E3456)*
       (pow(A3ZAI,2) + pow(A3ZAR,2))*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(2*C45*
          (4*(C56*C56)*
             ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C36*C36) - 
                  8*(MZ*MZ)*C36) + 
               8*(C34*C34)*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C36*C36) - 
                  8*(MZ*MZ)*C36) - 
               4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 8*C36)*C34
) + 2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
             (8*(MZ*MZ)*(C36*C36) + 
               2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C36*C36) - 
                  8*(MZ*MZ)*C36)*C34) + 
            4*(MZ*MZ*MZ*MZ)*(4*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
               4*(C34*C34)*
                (-(MZ*MZ) - (wZ*wZ) + 8*C36) - 
               32*(C36*C36)*C34)*C56) + 
         2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
          (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
             (-(Sqrt2*SqrtC36) + 
               Sqrt2*SqrtC34)*
             (Sqrt2*SqrtC36 + 
               Sqrt2*SqrtC34)*C34 + 
            4*(C56*C56)*
             ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 8*(C34*C34) - 
               2*(2*(MZ*MZ) + 2*C36)*C34) - 
            2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
               4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
               16*(MZ*MZ)*C36*C34)*C56) + 
         4*(C45*C45)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
             C34*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
               8*(C36*C36) - 4*(MZ*MZ)*C36 - 
               4*C36*C34) + 
            4*(-(Sqrt2*SqrtC36) + 
               Sqrt2*SqrtC34)*
             (Sqrt2*SqrtC36 + 
               Sqrt2*SqrtC34)*(C56*C56)*
             (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 8*C36*C34) 
- 2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 8*(C36*C36))*
                (C34*C34) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 8*(C36*C36) - 
                  4*(MZ*MZ)*C36) - 
               8*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                  8*(MZ*MZ)*(C36*C36) - 4*(MZ*MZ*MZ*MZ)*C36)*
                C34)*C56)) + 
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
               6*(MZ*MZ)*C56))) - 
      (gL - gR)*(gL + gR)*MZ*wZ*E3456*
       (pow(A3ZAI,2) + pow(A3ZAR,2))*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
          (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
             (Sqrt2*SqrtC45 - 
               Sqrt2*SqrtC56)*
             (Sqrt2*SqrtC45 + 
               Sqrt2*SqrtC56)*C45 - 
            2*C36*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
               16*(MZ*MZ)*C45*C56 + 
               4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
            4*(C36*C36)*
             ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 8*(C45*C45) - 
               2*C45*(2*(MZ*MZ) + 2*C56))) + 
         2*C34*(4*(MZ*MZ*MZ*MZ)*C36*
             (4*((MZ*MZ) + (wZ*wZ))*(C56*C56) - 
               32*(C56*C56)*C45 + 
               4*(C45*C45)*(-(MZ*MZ) - (wZ*wZ) + 8*C56)) 
+ 4*(C36*C36)*(-4*(MZ*MZ*MZ*MZ)*C45*
                ((MZ*MZ) + (wZ*wZ) - 8*C56) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
                  8*(MZ*MZ)*C56) + 
               8*(C45*C45)*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 4*(C56*C56) - 
                  8*(MZ*MZ)*C56)) + 
            2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
             (8*(MZ*MZ)*(C56*C56) + 
               2*C45*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                  4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
         4*(C34*C34)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
             C45*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
               8*(C56*C56) - 4*(MZ*MZ)*C56 - 
               4*C45*C56) + 
            4*(C36*C36)*
             (Sqrt2*SqrtC45 - 
               Sqrt2*SqrtC56)*
             (Sqrt2*SqrtC45 + 
               Sqrt2*SqrtC56)*
             (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 8*C45*C56) 
- 2*C36*(4*(C45*C45)*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 8*(C56*C56)) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 8*(C56*C56) - 
                  4*(MZ*MZ)*C56) - 
               8*C45*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                  8*(MZ*MZ)*(C56*C56) - 4*(MZ*MZ*MZ*MZ)*C56)))) + 
      (pow(A3ZAI,2) + pow(A3ZAR,2))*(el*el)*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 - 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(C46 + C35,2) + 
            4*C34*C56))*
       (4*(C45*C45)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
             ((-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 6*(MZ*MZ)*C36) 
+ (MZ*MZ)*(wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) + 
            4*(C56*C56)*
             ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 6*(MZ*MZ)*C36)*
                ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 6*(MZ*MZ)*C34) 
+ (MZ*MZ)*(wZ*wZ)*(2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) + 
                  8*(C34*C34) + 4*C36*C34 - 
                  3*(MZ*MZ)*(2*C36 + 2*C34))) + 
            2*(MZ*MZ)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ) + (wZ*wZ) - 4*C36)*
                  ((MZ*MZ) - 2*C36)) + 
               4*(C34*C34)*
                (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                  24*(C36*C36) + 
                  2*(9*(MZ*MZ) + (wZ*wZ))*C36) + 
               8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36)*
                ((MZ*MZ) - 2*C36)*C34)*C56) + 
         2*(MZ*MZ)*C45*
          (4*(C56*C56)*
             ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34) - 
               ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 8*(MZ*MZ)*C36)*
                ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 6*(MZ*MZ)*C34) 
+ (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 12*(MZ*MZ)*(C36*C36) - 
                  8*(MZ*MZ)*(C34*C34) + 8*(MZ*MZ*MZ*MZ)*C36 + 
                  2*pow(-2*(MZ*MZ) + 2*C36,2)*C34)) + 
            2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
             ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
               (-MZ + Sqrt2*SqrtC34)*
                (MZ + Sqrt2*SqrtC34)*
                ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 8*(MZ*MZ)*C36) 
+ (wZ*wZ)*(2*(MZ*MZ*MZ*MZ) + 4*(C36*C36) - 
                  (MZ*MZ)*(8*C36 + 2*C34))) + 
            2*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
               (MZ*MZ)*((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                  8*(MZ*MZ)*C36)*
                ((MZ*MZ*MZ*MZ) + 12*(C34*C34) - 8*(MZ*MZ)*C34) 
+ (MZ*MZ)*(wZ*wZ*wZ*wZ)*(3*(MZ*MZ*MZ*MZ) + 4*(C36*C36) + 
                  4*(C34*C34) - 
                  4*(MZ*MZ)*(2*C36 + 2*C34)) + 
               (wZ*wZ)*(3*pow(MZ,8) + 
                  16*(C36*C36)*(C34*C34) - 
                  8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C34) - 
                  16*(MZ*MZ)*C36*C34*
                   (2*C36 + 2*C34) + 
                  4*(MZ*MZ*MZ*MZ)*
                   (4*(C36*C36) + 4*(C34*C34) + 
                     16*C36*C34)))*C56) + 
         2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
          ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
            (-MZ + Sqrt2*SqrtC34)*
             (MZ + Sqrt2*SqrtC34)*
             ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
             (-8*C34*C56 + 
               (MZ*MZ)*(2*C34 + 2*C56)) + 
            (MZ*MZ)*(wZ*wZ)*
             (8*(C34*C34)*C36 + 8*(C56*C56)*C36 + 
               8*(C56*C56)*C34 + 
               8*(C34*C34)*C56 + 
               2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
               (MZ*MZ)*(4*(C34*C34) + 4*(C56*C56) + 
                  16*C34*C56 + 
                  2*C36*(2*C34 + 2*C56))))) + 
      (pow(A3ZAI,2) + pow(A3ZAR,2))*(el*el)*((gL*gL) + (gR*gR))*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),
        -1)*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 - 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 + C46,2) + 4*C36*C45)*
          C56)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
          ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
            (-MZ + Sqrt2*SqrtC45)*
             (MZ + Sqrt2*SqrtC45)*
             ((MZ*MZ) - 2*C36)*
             (-8*C36*C45 + 
               (MZ*MZ)*(2*C36 + 2*C45))*
             ((MZ*MZ) - 2*C56) + 
            (MZ*MZ)*(wZ*wZ)*
             (8*(C45*C45)*C36 + 8*(C36*C36)*C45 + 
               2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
               8*(C36*C36)*C56 + 
               8*(C45*C45)*C56 - 
               (MZ*MZ)*(4*(C36*C36) + 4*(C45*C45) + 
                  16*C36*C45 + 
                  2*(2*C36 + 2*C45)*C56))) + 
         4*(C34*C34)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
             ((MZ*MZ)*(wZ*wZ)*
                (-(MZ*MZ) + 2*C45 + 2*C56) + 
               (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 6*(MZ*MZ)*C56)) + 
            2*(MZ*MZ)*C36*
             (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                  ((MZ*MZ) - 2*C56)) + 
               8*(MZ*MZ)*C45*
                ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                ((MZ*MZ) - 2*C56) + 
               4*(C45*C45)*
                (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                  24*(C56*C56) + 
                  2*(9*(MZ*MZ) + (wZ*wZ))*C56)) + 
            4*(C36*C36)*
             ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
               ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 6*(MZ*MZ)*C45)*
                ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 6*(MZ*MZ)*C56) + 
               (MZ*MZ)*(wZ*wZ)*
                (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) + 8*(C56*C56) + 
                  4*C45*C56 - 
                  3*(MZ*MZ)*(2*C45 + 2*C56)))) + 
         2*(MZ*MZ)*C34*
          (4*(C36*C36)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45) - 
               ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 6*(MZ*MZ)*C45)*
                ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 8*(MZ*MZ)*C56) + 
               (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 8*(MZ*MZ)*(C45*C45) - 
                  12*(MZ*MZ)*(C56*C56) + 
                  2*pow(-2*(MZ*MZ) + 2*C56,2)*C45 + 
                  8*(MZ*MZ*MZ*MZ)*C56)) + 
            2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
             ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
               (-MZ + Sqrt2*SqrtC45)*
                (MZ + Sqrt2*SqrtC45)*
                ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 8*(MZ*MZ)*C56) + 
               (wZ*wZ)*(2*(MZ*MZ*MZ*MZ) + 4*(C56*C56) - 
                  (MZ*MZ)*(2*C45 + 8*C56))) + 
            2*C36*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
               (MZ*MZ)*((MZ*MZ*MZ*MZ) + 12*(C45*C45) - 
                  8*(MZ*MZ)*C45)*
                ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 8*(MZ*MZ)*C56) + 
               (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                (3*(MZ*MZ*MZ*MZ) + 4*(C45*C45) + 4*(C56*C56) - 
                  4*(MZ*MZ)*(2*C45 + 2*C56)) + 
               (wZ*wZ)*(3*pow(MZ,8) + 
                  16*(C45*C45)*(C56*C56) - 
                  8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C45 + 2*C56) - 
                  16*(MZ*MZ)*C45*C56*
                   (2*C45 + 2*C56) + 
                  4*(MZ*MZ*MZ*MZ)*(4*(C45*C45) + 4*(C56*C56) + 
                     16*C45*C56)))))))/1.048576e6;
}

double GetGeneralScalar4e_Part17(LeptonVectors &leptons, double A2ZAI, double A2ZAR, double A3ZAI, double A3ZAR)
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
    (16*(A2ZAI*A3ZAI + A2ZAR*A3ZAR)*(-E3456)*(el*el)*
       ((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((MZ*MZ)*(wZ*wZ) + (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)) + 
      16*(A2ZAI*A3ZAI + A2ZAR*A3ZAR)*E3456*(el*el)*
       ((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       ((MZ*MZ)*(wZ*wZ) + (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56)) - 
      4*(A2ZAR*A3ZAI - A2ZAI*A3ZAR)*(gL - gR)*(gL + gR)*(el*el)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(-(C34*C34) - (C46*C46) + 
         (C35*C35) + (C56*C56))*
       ((MZ*MZ)*(wZ*wZ)*(2*C36 + 2*C45) - 
         (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-8*C36*C45 + (MZ*MZ)*(2*C36 + 2*C45))) 
- 4*(A2ZAR*A3ZAI - A2ZAI*A3ZAR)*(gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C45)*((C34*C34) - (C46*C46) + 
         (C35*C35) - (C56*C56))*
       ((MZ*MZ)*(wZ*wZ)*(2*C36 + 2*C45) - 
         (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)*
          (-8*C36*C45 + (MZ*MZ)*(2*C36 + 2*C45))) 
+ 4*(A2ZAI*A3ZAI + A2ZAR*A3ZAR)*(-E3456)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow(C36,-2)*pow(C45,-2)*
       (8*gL*gR*((MZ*MZ)*(wZ*wZ) + 
            (-MZ + Sqrt2*SqrtC36)*
             (MZ + Sqrt2*SqrtC36)*
             (-MZ + Sqrt2*SqrtC45)*
             (MZ + Sqrt2*SqrtC45))*C36*C45 + 
         (gL*gL)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
             (C36*C36) + 
            4*(C45*C45)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C36*C36) - 
               6*(MZ*MZ)*C36) + 
            4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 6*C36)*C36*
             C45) + (gR*gR)*
          (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
            4*(C45*C45)*
             ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 12*(C36*C36) - 
               6*(MZ*MZ)*C36) + 
            4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 6*C36)*C36*
             C45))*(C46*C35 - C34*C56) - 
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
               6*(MZ*MZ)*C56))) - 
      (gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(C46*C35 - C36*C45 - 
         C34*C56)*(A2ZAR*
          (A3ZAR*MZ*wZ*(2*C45*
                (4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     8*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 8*C36)*
                      C34) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   (8*(MZ*MZ)*(C36*C36) + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  4*(MZ*MZ*MZ*MZ)*
                   (4*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
                     4*(C34*C34)*
                      (-(MZ*MZ) - (wZ*wZ) + 8*C36) - 
                     32*(C36*C36)*C34)*C56) - 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 - 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56) + 
               4*(C45*C45)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                     4*C36*C34) + 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     8*C36*C34) - 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36) - 4*(MZ*MZ)*C36) - 
                     8*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        4*(MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A3ZAI*(4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        6*(MZ*MZ)*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) + 
                        8*(C34*C34) + 4*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(MZ*MZ)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ) + (wZ*wZ) - 4*C36)*
                        ((MZ*MZ) - 2*C36)) + 
                     4*(C34*C34)*
                      (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        24*(C36*C36) + 
                        2*(9*(MZ*MZ) + (wZ*wZ))*C36) + 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36)*
                      ((MZ*MZ) - 2*C36)*C34)*C56) + 
               2*(MZ*MZ)*C45*
                (4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        6*(MZ*MZ)*C34) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 12*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ)*(C34*C34) + 
                        8*(MZ*MZ*MZ*MZ)*C36 + 
                        2*pow(-2*(MZ*MZ) + 2*C36,2)*C34)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
                     (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36) + 
                     (wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 4*(C36*C36) - 
                        (MZ*MZ)*(8*C36 + 2*C34))) + 
                  2*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
                     (MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 12*(C34*C34) - 
                        8*(MZ*MZ)*C34) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (3*(MZ*MZ*MZ*MZ) + 4*(C36*C36) + 
                        4*(C34*C34) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (3*pow(MZ,8) + 
                        16*(C36*C36)*(C34*C34) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C34) - 
                        16*(MZ*MZ)*C36*C34*
                         (2*C36 + 2*C34) + 
                        4*(MZ*MZ*MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) + 
                         16*C36*C34)))*C56) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))))) - 
         A2ZAI*(A3ZAI*MZ*wZ*(-2*C45*
                (4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     8*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 8*C36)*
                      C34) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   (8*(MZ*MZ)*(C36*C36) + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  4*(MZ*MZ*MZ*MZ)*
                   (4*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
                     4*(C34*C34)*
                      (-(MZ*MZ) - (wZ*wZ) + 8*C36) - 
                     32*(C36*C36)*C34)*C56) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 - 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56) + 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                     4*C36*C34) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     8*C36*C34) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36) - 4*(MZ*MZ)*C36) - 
                     8*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        4*(MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A3ZAR*(4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        6*(MZ*MZ)*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) + 
                        8*(C34*C34) + 4*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(MZ*MZ)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ) + (wZ*wZ) - 4*C36)*
                        ((MZ*MZ) - 2*C36)) + 
                     4*(C34*C34)*
                      (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        24*(C36*C36) + 
                        2*(9*(MZ*MZ) + (wZ*wZ))*C36) + 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36)*
                      ((MZ*MZ) - 2*C36)*C34)*C56) + 
               2*(MZ*MZ)*C45*
                (4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        6*(MZ*MZ)*C34) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 12*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ)*(C34*C34) + 
                        8*(MZ*MZ*MZ*MZ)*C36 + 
                        2*pow(-2*(MZ*MZ) + 2*C36,2)*C34)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
                     (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36) + 
                     (wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 4*(C36*C36) - 
                        (MZ*MZ)*(8*C36 + 2*C34))) + 
                  2*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
                     (MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 12*(C34*C34) - 
                        8*(MZ*MZ)*C34) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (3*(MZ*MZ*MZ*MZ) + 4*(C36*C36) + 
                        4*(C34*C34) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (3*pow(MZ,8) + 
                        16*(C36*C36)*(C34*C34) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C34) - 
                        16*(MZ*MZ)*C36*C34*
                         (2*C36 + 2*C34) + 
                        4*(MZ*MZ*MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) + 
                         16*C36*C34)))*C56) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56))))))) - 
      (-E3456)*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*((C46*C46) + (C35*C35) + 
         2*C36*C45 - 2*C34*C56)*
       (A2ZAI*(A3ZAR*MZ*wZ*(2*C45*
                (4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     8*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 8*C36)*
                      C34) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   (8*(MZ*MZ)*(C36*C36) + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  4*(MZ*MZ*MZ*MZ)*
                   (4*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
                     4*(C34*C34)*
                      (-(MZ*MZ) - (wZ*wZ) + 8*C36) - 
                     32*(C36*C36)*C34)*C56) - 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 - 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56) + 
               4*(C45*C45)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                     4*C36*C34) + 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     8*C36*C34) - 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36) - 4*(MZ*MZ)*C36) - 
                     8*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        4*(MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A3ZAI*(4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        6*(MZ*MZ)*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) + 
                        8*(C34*C34) + 4*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(MZ*MZ)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ) + (wZ*wZ) - 4*C36)*
                        ((MZ*MZ) - 2*C36)) + 
                     4*(C34*C34)*
                      (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        24*(C36*C36) + 
                        2*(9*(MZ*MZ) + (wZ*wZ))*C36) + 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36)*
                      ((MZ*MZ) - 2*C36)*C34)*C56) + 
               2*(MZ*MZ)*C45*
                (4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        6*(MZ*MZ)*C34) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 12*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ)*(C34*C34) + 
                        8*(MZ*MZ*MZ*MZ)*C36 + 
                        2*pow(-2*(MZ*MZ) + 2*C36,2)*C34)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
                     (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36) + 
                     (wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 4*(C36*C36) - 
                        (MZ*MZ)*(8*C36 + 2*C34))) + 
                  2*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
                     (MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 12*(C34*C34) - 
                        8*(MZ*MZ)*C34) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (3*(MZ*MZ*MZ*MZ) + 4*(C36*C36) + 
                        4*(C34*C34) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (3*pow(MZ,8) + 
                        16*(C36*C36)*(C34*C34) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C34) - 
                        16*(MZ*MZ)*C36*C34*
                         (2*C36 + 2*C34) + 
                        4*(MZ*MZ*MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) + 
                         16*C36*C34)))*C56) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))))) + 
         A2ZAR*(A3ZAI*MZ*wZ*(-2*C45*
                (4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     8*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 8*C36)*
                      C34) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   (8*(MZ*MZ)*(C36*C36) + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  4*(MZ*MZ*MZ*MZ)*
                   (4*((MZ*MZ) + (wZ*wZ))*(C36*C36) + 
                     4*(C34*C34)*
                      (-(MZ*MZ) - (wZ*wZ) + 8*C36) - 
                     32*(C36*C36)*C34)*C56) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 - 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56) + 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                     4*C36*C34) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     8*C36*C34) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36) - 4*(MZ*MZ)*C36) - 
                     8*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        4*(MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A3ZAR*(4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        6*(MZ*MZ)*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) + 
                        8*(C34*C34) + 4*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(MZ*MZ)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ) + (wZ*wZ) - 4*C36)*
                        ((MZ*MZ) - 2*C36)) + 
                     4*(C34*C34)*
                      (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        24*(C36*C36) + 
                        2*(9*(MZ*MZ) + (wZ*wZ))*C36) + 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36)*
                      ((MZ*MZ) - 2*C36)*C34)*C56) + 
               2*(MZ*MZ)*C45*
                (4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        6*(MZ*MZ)*C34) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 12*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ)*(C34*C34) + 
                        8*(MZ*MZ*MZ*MZ)*C36 + 
                        2*pow(-2*(MZ*MZ) + 2*C36,2)*C34)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
                     (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36) + 
                     (wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 4*(C36*C36) - 
                        (MZ*MZ)*(8*C36 + 2*C34))) + 
                  2*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
                     (MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*
                      ((MZ*MZ*MZ*MZ) + 12*(C34*C34) - 
                        8*(MZ*MZ)*C34) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (3*(MZ*MZ*MZ*MZ) + 4*(C36*C36) + 
                        4*(C34*C34) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (3*pow(MZ,8) + 
                        16*(C36*C36)*(C34*C34) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C34) - 
                        16*(MZ*MZ)*C36*C34*
                         (2*C36 + 2*C34) + 
                        4*(MZ*MZ*MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) + 
                         16*C36*C34)))*C56) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56))))))) - 
      (gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (-(C36*C45) + C35*C46 - C34*C56)*
       (A2ZAR*(A3ZAR*MZ*wZ*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                C56*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 + 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56))) + 
               2*C34*(4*(MZ*MZ*MZ*MZ)*C36*
                   (4*((MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                     32*(C56*C56)*C45 + 
                     4*(C45*C45)*
                      (-(MZ*MZ) - (wZ*wZ) + 8*C56)) + 
                  4*(C36*C36)*
                   (-4*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 8*C56) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     8*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   (8*(MZ*MZ)*(C56*C56) + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                     4*C45*C56) + 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     8*C45*C56) - 
                  2*C36*
                   (4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56)) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56) - 4*(MZ*MZ)*C56) - 
                     8*C45*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        4*(MZ*MZ*MZ*MZ)*C56)))) + 
            A3ZAI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*C36*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                        ((MZ*MZ) - 2*C56)) + 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                      ((MZ*MZ) - 2*C56) + 
                     4*(C45*C45)*
                      (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        24*(C56*C56) + 
                        2*(9*(MZ*MZ) + (wZ*wZ))*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        6*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) + 
                        8*(C56*C56) + 4*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)))) + 
               2*(MZ*MZ)*C34*
                (4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45) - 
                     ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        6*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 8*(MZ*MZ)*(C45*C45) - 
                        12*(MZ*MZ)*(C56*C56) + 
                        2*pow(-2*(MZ*MZ) + 2*C56,2)*C45 + 
                        8*(MZ*MZ*MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 8*C56))) + 
                  2*C36*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
                     (MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + 12*(C45*C45) - 
                        8*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (3*(MZ*MZ*MZ*MZ) + 4*(C45*C45) + 
                        4*(C56*C56) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (3*pow(MZ,8) + 
                        16*(C45*C45)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C45 + 2*C56) - 
                        16*(MZ*MZ)*C45*C56*
                         (2*C45 + 2*C56) + 
                        4*(MZ*MZ*MZ*MZ)*
                         (4*(C45*C45) + 4*(C56*C56) + 
                          16*C45*C56)))))) - 
         A2ZAI*(A3ZAI*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                C56*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 + 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56))) - 
               2*C34*(4*(MZ*MZ*MZ*MZ)*C36*
                   (4*((MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                     32*(C56*C56)*C45 + 
                     4*(C45*C45)*
                      (-(MZ*MZ) - (wZ*wZ) + 8*C56)) + 
                  4*(C36*C36)*
                   (-4*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 8*C56) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     8*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   (8*(MZ*MZ)*(C56*C56) + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                     4*C45*C56) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     8*C45*C56) + 
                  2*C36*(4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56)) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56) - 4*(MZ*MZ)*C56) - 
                     8*C45*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        4*(MZ*MZ*MZ*MZ)*C56)))) + 
            A3ZAR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*C36*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                        ((MZ*MZ) - 2*C56)) + 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                      ((MZ*MZ) - 2*C56) + 
                     4*(C45*C45)*
                      (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        24*(C56*C56) + 
                        2*(9*(MZ*MZ) + (wZ*wZ))*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        6*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) + 
                        8*(C56*C56) + 4*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)))) + 
               2*(MZ*MZ)*C34*
                (4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45) - 
                     ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        6*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 8*(MZ*MZ)*(C45*C45) - 
                        12*(MZ*MZ)*(C56*C56) + 
                        2*pow(-2*(MZ*MZ) + 2*C56,2)*C45 + 
                        8*(MZ*MZ*MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 8*C56))) + 
                  2*C36*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
                     (MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + 12*(C45*C45) - 
                        8*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (3*(MZ*MZ*MZ*MZ) + 4*(C45*C45) + 
                        4*(C56*C56) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (3*pow(MZ,8) + 16*(C45*C45)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C45 + 2*C56) - 
                        16*(MZ*MZ)*C45*C56*
                         (2*C45 + 2*C56) + 
                        4*(MZ*MZ*MZ*MZ)*
                         (4*(C45*C45) + 4*(C56*C56) + 
                          16*C45*C56))))))) - 
      E3456*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*((C35*C35) + (C46*C46) - 
         2*C36*C45 + 2*C34*C56)*
       (A2ZAI*(A3ZAR*MZ*wZ*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                C56*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 + 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56))) + 
               2*C34*(4*(MZ*MZ*MZ*MZ)*C36*
                   (4*((MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                     32*(C56*C56)*C45 + 
                     4*(C45*C45)*
                      (-(MZ*MZ) - (wZ*wZ) + 8*C56)) + 
                  4*(C36*C36)*
                   (-4*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 8*C56) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     8*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   (8*(MZ*MZ)*(C56*C56) + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                     4*C45*C56) + 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     8*C45*C56) - 
                  2*C36*(4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56)) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56) - 4*(MZ*MZ)*C56) - 
                     8*C45*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        4*(MZ*MZ*MZ*MZ)*C56)))) + 
            A3ZAI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*C36*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                        ((MZ*MZ) - 2*C56)) + 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                      ((MZ*MZ) - 2*C56) + 
                     4*(C45*C45)*
                      (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        24*(C56*C56) + 
                        2*(9*(MZ*MZ) + (wZ*wZ))*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        6*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) + 
                        8*(C56*C56) + 4*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)))) + 
               2*(MZ*MZ)*C34*
                (4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45) - 
                     ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        6*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 8*(MZ*MZ)*(C45*C45) - 
                        12*(MZ*MZ)*(C56*C56) + 
                        2*pow(-2*(MZ*MZ) + 2*C56,2)*C45 + 
                        8*(MZ*MZ*MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 8*C56))) + 
                  2*C36*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
                     (MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + 12*(C45*C45) - 
                        8*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (3*(MZ*MZ*MZ*MZ) + 4*(C45*C45) + 
                        4*(C56*C56) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (3*pow(MZ,8) + 16*(C45*C45)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C45 + 2*C56) - 
                        16*(MZ*MZ)*C45*C56*
                         (2*C45 + 2*C56) + 
                        4*(MZ*MZ*MZ*MZ)*
                         (4*(C45*C45) + 4*(C56*C56) + 
                          16*C45*C56)))))) + 
         A2ZAR*(A3ZAI*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 + 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56))) - 
               2*C34*(4*(MZ*MZ*MZ*MZ)*C36*
                   (4*((MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                     32*(C56*C56)*C45 + 
                     4*(C45*C45)*
                      (-(MZ*MZ) - (wZ*wZ) + 8*C56)) + 
                  4*(C36*C36)*
                   (-4*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 8*C56) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     8*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   (8*(MZ*MZ)*(C56*C56) + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 8*(C56*C56) - 
                     4*(MZ*MZ)*C56 - 4*C45*C56) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     8*C45*C56) + 
                  2*C36*(4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56)) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56) - 4*(MZ*MZ)*C56) - 
                     8*C45*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 4*(MZ*MZ*MZ*MZ)*C56
)))) + A3ZAR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*C36*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                        ((MZ*MZ) - 2*C56)) + 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 4*C56)*
                      ((MZ*MZ) - 2*C56) + 
                     4*(C45*C45)*
                      (-3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        24*(C56*C56) + 
                        2*(9*(MZ*MZ) + (wZ*wZ))*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        6*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) + 
                        8*(C56*C56) + 4*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)))) + 
               2*(MZ*MZ)*C34*
                (4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45) - 
                     ((MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        6*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) - 8*(MZ*MZ)*(C45*C45) - 
                        12*(MZ*MZ)*(C56*C56) + 
                        2*pow(-2*(MZ*MZ) + 2*C56,2)*C45 + 
                        8*(MZ*MZ*MZ*MZ)*C56)) + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ) - 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 8*C56))) + 
                  2*C36*((MZ*MZ*MZ*MZ)*pow(wZ,6) + 
                     (MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + 12*(C45*C45) - 
                        8*(MZ*MZ)*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (3*(MZ*MZ*MZ*MZ) + 4*(C45*C45) + 
                        4*(C56*C56) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (3*pow(MZ,8) + 16*(C45*C45)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C45 + 2*C56) - 
                        16*(MZ*MZ)*C45*C56*
                         (2*C45 + 2*C56) + 
                        4*(MZ*MZ*MZ*MZ)*
                         (4*(C45*C45) + 4*(C56*C56) + 
                          16*C45*C56)))))))))/524288.;
}

double GetGeneralScalar4e_Part20(LeptonVectors &leptons, double A2AAI, double A2AAR, double A2ZZI, double A2ZZR)
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
    (8*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (2*(C36*C36)*(C45*C45) + 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(-C46 + C35,2) + pow(-C34 + C56,2))*
          C36*C45)*
       (-((A2AAI*A2ZZI + A2AAR*A2ZZR)*(MZ*MZ)*(wZ*wZ)) + 
         (A2AAI*A2ZZI + A2AAR*A2ZZR)*(-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A2AAR*A2ZZI - A2AAI*A2ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45)) + 
      8*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-((A2AAI*A2ZZI + A2AAR*A2ZZR)*(MZ*MZ)*(wZ*wZ)) + 
         (A2AAI*A2ZZI + A2AAR*A2ZZR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A2AAR*A2ZZI - A2AAI*A2ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (-C34 + C46 + C35 - C56)*
       (C34 + C46 + C35 + C56) + 
      8*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
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
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) + 
      (gL - gR)*(gL + gR)*MZ*(-E3456)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(A2AAI*
          (A2ZZI*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                C34*C56*
                (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
               2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-2*(MZ*MZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      (4*(C36*C36) - 4*(MZ*MZ)*C36) + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34) + 
                  4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-2*(MZ*MZ) + 2*C36 + 2*C34)*C56) 
+ 4*(C45*C45)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*C34)*C56)) + 
            A2ZZR*MZ*(4*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56))*C34*
                C56 + 2*C45*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                  4*(C56*C56)*
                   (-4*(C34*C34)*(-2*(MZ*MZ) + 2*C36)*
                      (-(MZ*MZ) - (wZ*wZ) + 2*C36) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ) - 2*C36)*C34) - 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*(wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34))*C56) - 
               4*(C45*C45)*
                (2*((MZ*MZ) + (wZ*wZ))*
                   (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 + 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36))*(C34*C34) - 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36 + 
                     2*(-(MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                        4*(3*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56))) + 
         A2AAR*(A2ZZR*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                C34*C56*
                (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
               2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-2*(MZ*MZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      (4*(C36*C36) - 4*(MZ*MZ)*C36) + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34) + 
                  4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-2*(MZ*MZ) + 2*C36 + 2*C34)*C56) + 
               4*(C45*C45)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*C34)*C56)) + 
            A2ZZI*MZ*(-4*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56))*C34*
                C56 + 2*C45*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                  4*(C56*C56)*
                   (4*(C34*C34)*(-2*(MZ*MZ) + 2*C36)*
                      (-(MZ*MZ) - (wZ*wZ) + 2*C36) - 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C34) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*(wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34))*C56) + 
               4*(C45*C45)*
                (2*((MZ*MZ) + (wZ*wZ))*
                   (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2))*
                   C36 + 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36))*(C34*C34) - 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36 + 
                     2*(-(MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                        4*(3*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56)))) + 
      (el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 + 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(-C46 + C35,2) - 
            4*C34*C56))*
       (A2AAI*(A2ZZR*MZ*wZ*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                C34*C56*
                (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*(-4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34)*C56) - 
               2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-2*(MZ*MZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      (4*(C36*C36) - 4*(MZ*MZ)*C36) - 
                     4*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ)*C36)*C34) - 
                  4*(2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ)*C36) - 
                     4*(pow(MZ,8) + (MZ*MZ*MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ*MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A2ZZI*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56))*C34*
                C56 - 2*(MZ*MZ)*C45*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C36 + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C36*C36) + 
                        4*(C34*C34)*
                        (2*(MZ*MZ) + 2*C36) - 
                        4*(MZ*MZ)*((MZ*MZ) + 2*C36)*C34) 
+ (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-12*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 4*C34))) - 
                  4*(MZ*MZ)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (4*C36*C34*
                        (2*C36 + 2*C34) + 
                        (MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) - 
                         16*C36*C34)))*C56) + 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C36*C36) + 4*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*(2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C34 + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (4*(MZ*MZ)*C36 + 
                        2*((MZ*MZ) - 6*C36)*C34) + 
                     (wZ*wZ)*
                      (-4*(MZ*MZ*MZ*MZ)*C36 + 
                        8*(C36*C36)*C34 + 
                        (MZ*MZ)*
                         (8*(C36*C36) + 4*(C34*C34) - 
                         8*C36*C34)))*C56))) + 
         A2AAR*(A2ZZI*MZ*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                C34*C56*
                (-2*(MZ*MZ) + 2*C34 + 2*C56) + 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*(-4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34)*C56) + 
               2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-2*(MZ*MZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      (4*(C36*C36) - 4*(MZ*MZ)*C36) - 
                     4*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ)*C36)*C34) - 
                  4*(2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ)*C36) - 
                     4*(pow(MZ,8) + (MZ*MZ*MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ*MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A2ZZR*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56))*C34*
                C56 - 2*(MZ*MZ)*C45*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C36 + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C36*C36) + 
                        4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                        4*(MZ*MZ)*((MZ*MZ) + 2*C36)*C34) 
+ (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-12*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 4*C34))) - 
                  4*(MZ*MZ)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (2*C36 + 2*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (4*C36*C34*
                        (2*C36 + 2*C34) + 
                        (MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) - 
                         16*C36*C34)))*C56) + 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2))*
                   C36 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C36*C36) + 4*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*(2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C34 + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (4*(MZ*MZ)*C36 + 
                        2*((MZ*MZ) - 6*C36)*C34) + 
                     (wZ*wZ)*
                      (-4*(MZ*MZ*MZ*MZ)*C36 + 
                        8*(C36*C36)*C34 + 
                        (MZ*MZ)*
                         (8*(C36*C36) + 4*(C34*C34) - 
                          8*C36*C34)))*C56)))) + 
      (gL - gR)*(gL + gR)*MZ*E3456*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (A2AAI*(A2ZZI*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45*
                (-2*(MZ*MZ) + 2*C36 + 2*C45) + 
               4*(C34*C34)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56 + 
                  2*C36*
                   (4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56))*C45 + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56)) - 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-2*(MZ*MZ) + 2*C56) + 
                  4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-2*(MZ*MZ) + 2*C45 + 2*C56) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      (4*(C56*C56) - 4*(MZ*MZ)*C56)))) + 
            A2ZZR*MZ*(4*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45 + 
               2*C34*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*(wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56))*C36 + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                      ((MZ*MZ) - 2*C56) - 
                     4*(C45*C45)*(-2*(MZ*MZ) + 2*C56)*
                      (-(MZ*MZ) - (wZ*wZ) + 2*C56) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C56))) - 
               4*(C34*C34)*
                (2*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*C56 + 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*C36*(4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C56 + 
                     2*C45*
                      (-(MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                        4*(3*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56))))) 
+ A2AAR*(A2ZZR*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45*
                (-2*(MZ*MZ) + 2*C36 + 2*C45) + 
               4*(C34*C34)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56 + 
                  2*C36*
                   (4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56))*C45 + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56)) - 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-2*(MZ*MZ) + 2*C56) + 
                  4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-2*(MZ*MZ) + 2*C45 + 2*C56) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      (4*(C56*C56) - 4*(MZ*MZ)*C56)))) + 
            A2ZZI*MZ*(-4*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45 + 
               2*C34*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*(wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56))*C36 - 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C45 + 
                     4*(C45*C45)*(-2*(MZ*MZ) + 2*C56)*
                      (-(MZ*MZ) - (wZ*wZ) + 2*C56) - 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C56))) + 
               4*(C34*C34)*
                (2*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*C56 + 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*C36*(4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C56 + 
                     2*C45*
                      (-(MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                        4*(3*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56)))))) 
+ (el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 + 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 - C46,2) - 4*C36*C45)*
          C56)*(A2AAI*(A2ZZR*MZ*wZ*
             (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45*
                (-2*(MZ*MZ) + 2*C36 + 2*C45) - 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56 + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*
                   (-4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     4*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) - 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-2*(MZ*MZ) + 2*C56) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      (4*(C56*C56) - 4*(MZ*MZ)*C56) - 
                     4*C45*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ)*C56)) - 
                  4*C36*(2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      C56*(-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ)*C56) - 
                     4*C45*
                      (pow(MZ,8) + (MZ*MZ*MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ*MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*C56)))) + 
            A2ZZI*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45 - 
               2*(MZ*MZ)*C34*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C56 + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C56*C56) - 
                        4*(MZ*MZ)*C45*
                        ((MZ*MZ) + 2*C56) + 
                        4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-12*C45*C56 + 
                        (MZ*MZ)*(4*C45 + 2*C56))) - 
                  4*(MZ*MZ)*C36*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*C45*C56*(2*C45 + 2*C56) + 
                        (MZ*MZ)*
                         (4*(C45*C45) + 4*(C56*C56) - 
                          16*C45*C56)))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*C56 + 
                  4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C45*C45) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56))) - 
                  2*(MZ*MZ)*C36*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C45 + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (2*C45*((MZ*MZ) - 6*C56) + 
                        4*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (8*(C56*C56)*C45 - 
                        4*(MZ*MZ*MZ*MZ)*C56 + 
                        (MZ*MZ)*
                         (4*(C45*C45) + 8*(C56*C56) - 
                          8*C45*C56)))))) + 
         A2AAR*(A2ZZI*MZ*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45*
                (-2*(MZ*MZ) + 2*C36 + 2*C45) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56 + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*(-4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      C56 + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     4*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   C56*(-2*(MZ*MZ) + 2*C56) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      (4*(C56*C56) - 4*(MZ*MZ)*C56) - 
                     4*C45*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ)*C56)) - 
                  4*C36*(2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      C56*(-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ)*C56) - 
                     4*C45*
                      (pow(MZ,8) + (MZ*MZ*MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ*MZ*MZ)*(C56*C56) - 8*(MZ*MZ*MZ*MZ*MZ*MZ)*C56
)))) + A2ZZR*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45 - 
               2*(MZ*MZ)*C34*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   C56*(-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C56 + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C56*C56) - 
                        4*(MZ*MZ)*C45*((MZ*MZ) + 2*C56) + 
                        4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-12*C45*C56 + 
                        (MZ*MZ)*(4*C45 + 2*C56))) - 
                  4*(MZ*MZ)*C36*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*C45*C56*(2*C45 + 2*C56) + 
                        (MZ*MZ)*
                         (4*(C45*C45) + 4*(C56*C56) - 
                          16*C45*C56)))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*C56 + 
                  4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C45*C45) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56))) - 
                  2*(MZ*MZ)*C36*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C45 + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (2*C45*((MZ*MZ) - 6*C56) + 
                        4*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (8*(C56*C56)*C45 - 
                        4*(MZ*MZ*MZ*MZ)*C56 + 
                        (MZ*MZ)*
                         (4*(C45*C45) + 8*(C56*C56) - 
                          8*C45*C56)))))))))/1.048576e6;
}

double GetGeneralScalar4e_Part21(LeptonVectors &leptons, double A3AAI, double A3AAR, double A3ZZI, double A3ZZR)
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
    (8*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-2*(C36*C36)*(C45*C45) - 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(C46 + C35,2) + pow(C34 + C56,2))*
          C36*C45)*
       (-((A3AAI*A3ZZI + A3AAR*A3ZZR)*(MZ*MZ)*(wZ*wZ)) + 
         (A3AAI*A3ZZI + A3AAR*A3ZZR)*(-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A3AAR*A3ZZI - A3AAI*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45)) + 
      8*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-((A3AAI*A3ZZI + A3AAR*A3ZZR)*(MZ*MZ)*(wZ*wZ)) + 
         (A3AAI*A3ZZI + A3AAR*A3ZZR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A3AAR*A3ZZI - A3AAI*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (C34 - C46 + C35 - C56)*
       (-C34 - C46 + C35 + C56) + 
      8*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
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
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) + 
      (gL - gR)*(gL + gR)*MZ*(-E3456)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(A3AAI*
          (A3ZZI*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                C34*C56*
                (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
               2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-2*(MZ*MZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      (4*(C36*C36) - 4*(MZ*MZ)*C36) + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34) + 
                  4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-2*(MZ*MZ) + 2*C36 + 2*C34)*C56) 
+ 4*(C45*C45)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*C34)*C56)) + 
            A3ZZR*MZ*(4*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56))*C34*
                C56 + 2*C45*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                  4*(C56*C56)*
                   (-4*(C34*C34)*(-2*(MZ*MZ) + 2*C36)*
                      (-(MZ*MZ) - (wZ*wZ) + 2*C36) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ) - 2*C36)*C34) - 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*(wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34))*C56) - 
               4*(C45*C45)*
                (2*((MZ*MZ) + (wZ*wZ))*
                   (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 + 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36))*(C34*C34) - 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36 + 
                     2*(-(MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                        4*(3*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56))) + 
         A3AAR*(A3ZZR*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                C34*C56*
                (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
               2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-2*(MZ*MZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      (4*(C36*C36) - 4*(MZ*MZ)*C36) + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34) + 
                  4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-2*(MZ*MZ) + 2*C36 + 2*C34)*C56) + 
               4*(C45*C45)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*C34)*C56)) + 
            A3ZZI*MZ*(-4*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56))*C34*
                C56 + 2*C45*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                  4*(C56*C56)*
                   (4*(C34*C34)*(-2*(MZ*MZ) + 2*C36)*
                      (-(MZ*MZ) - (wZ*wZ) + 2*C36) - 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C34) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*(wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34))*C56) + 
               4*(C45*C45)*
                (2*((MZ*MZ) + (wZ*wZ))*
                   (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2))*
                   C36 + 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36))*(C34*C34) - 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36 + 
                     2*(-(MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                        4*(3*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56)))) + 
      (el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 - 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(C46 + C35,2) + 
            4*C34*C56))*
       (A3AAI*(A3ZZR*MZ*wZ*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                C34*C56*
                (-2*(MZ*MZ) + 2*C34 + 2*C56) - 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*(-4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34)*C56) - 
               2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-2*(MZ*MZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      (4*(C36*C36) - 4*(MZ*MZ)*C36) - 
                     4*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ)*C36)*C34) - 
                  4*(2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ)*C36) - 
                     4*(pow(MZ,8) + (MZ*MZ*MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ*MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A3ZZI*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56))*C34*
                C56 - 2*(MZ*MZ)*C45*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C36 + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C36*C36) + 
                        4*(C34*C34)*
                        (2*(MZ*MZ) + 2*C36) - 
                        4*(MZ*MZ)*((MZ*MZ) + 2*C36)*C34) 
+ (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-12*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 4*C34))) - 
                  4*(MZ*MZ)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (4*C36*C34*
                        (2*C36 + 2*C34) + 
                        (MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) - 
                         16*C36*C34)))*C56) + 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C36*C36) + 4*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*(2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C34 + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (4*(MZ*MZ)*C36 + 
                        2*((MZ*MZ) - 6*C36)*C34) + 
                     (wZ*wZ)*
                      (-4*(MZ*MZ*MZ*MZ)*C36 + 
                        8*(C36*C36)*C34 + 
                        (MZ*MZ)*
                         (8*(C36*C36) + 4*(C34*C34) - 
                         8*C36*C34)))*C56))) + 
         A3AAR*(A3ZZI*MZ*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                C34*C56*
                (-2*(MZ*MZ) + 2*C34 + 2*C56) + 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36 + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*(-4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34)*C56) + 
               2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-2*(MZ*MZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      (4*(C36*C36) - 4*(MZ*MZ)*C36) - 
                     4*((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ)*C36)*C34) - 
                  4*(2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ)*C36) - 
                     4*(pow(MZ,8) + (MZ*MZ*MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ*MZ*MZ)*(C36*C36) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A3ZZR*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56))*C34*
                C56 - 2*(MZ*MZ)*C45*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C34,2))*C36*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C36 + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C36*C36) + 
                        4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                        4*(MZ*MZ)*((MZ*MZ) + 2*C36)*C34) 
+ (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-12*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 4*C34))) - 
                  4*(MZ*MZ)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (2*C36 + 2*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (4*C36*C34*
                        (2*C36 + 2*C34) + 
                        (MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) - 
                         16*C36*C34)))*C56) + 
               4*(C45*C45)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2))*
                   C36 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C36*C36) + 4*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*(2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C34 + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (4*(MZ*MZ)*C36 + 
                        2*((MZ*MZ) - 6*C36)*C34) + 
                     (wZ*wZ)*
                      (-4*(MZ*MZ*MZ*MZ)*C36 + 
                        8*(C36*C36)*C34 + 
                        (MZ*MZ)*
                         (8*(C36*C36) + 4*(C34*C34) - 
                          8*C36*C34)))*C56)))) + 
      (gL - gR)*(gL + gR)*MZ*E3456*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (A3AAI*(A3ZZI*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45*
                (-2*(MZ*MZ) + 2*C36 + 2*C45) + 
               4*(C34*C34)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56 + 
                  2*C36*
                   (4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56))*C45 + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56)) - 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-2*(MZ*MZ) + 2*C56) + 
                  4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-2*(MZ*MZ) + 2*C45 + 2*C56) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      (4*(C56*C56) - 4*(MZ*MZ)*C56)))) + 
            A3ZZR*MZ*(4*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45 + 
               2*C34*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*(wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56))*C36 + 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                      ((MZ*MZ) - 2*C56) - 
                     4*(C45*C45)*(-2*(MZ*MZ) + 2*C56)*
                      (-(MZ*MZ) - (wZ*wZ) + 2*C56) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C56))) - 
               4*(C34*C34)*
                (2*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*C56 + 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*C36*(4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C56 + 
                     2*C45*
                      (-(MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                        4*(3*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56))))) 
+ A3AAR*(A3ZZR*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45*
                (-2*(MZ*MZ) + 2*C36 + 2*C45) + 
               4*(C34*C34)*
                (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56 + 
                  2*C36*
                   (4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     4*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56))*C45 + 
                     4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56)) - 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-2*(MZ*MZ) + 2*C56) + 
                  4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-2*(MZ*MZ) + 2*C45 + 2*C56) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      (4*(C56*C56) - 4*(MZ*MZ)*C56)))) + 
            A3ZZI*MZ*(-4*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45 + 
               2*C34*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*(wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56))*C36 - 
                  2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C45 + 
                     4*(C45*C45)*(-2*(MZ*MZ) + 2*C56)*
                      (-(MZ*MZ) - (wZ*wZ) + 2*C56) - 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C56))) + 
               4*(C34*C34)*
                (2*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*C56 + 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*C36*(4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C56 + 
                     2*C45*
                      (-(MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                        4*(3*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56)))))) 
+ (el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 - 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 + C46,2) + 4*C36*C45)*
          C56)*(A3AAI*(A3ZZR*MZ*wZ*
             (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45*
                (-2*(MZ*MZ) + 2*C36 + 2*C45) - 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56 + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*
                   (-4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     4*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) - 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-2*(MZ*MZ) + 2*C56) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      (4*(C56*C56) - 4*(MZ*MZ)*C56) - 
                     4*C45*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ)*C56)) - 
                  4*C36*(2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      C56*(-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ)*C56) - 
                     4*C45*
                      (pow(MZ,8) + (MZ*MZ*MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ*MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ*MZ*MZ)*C56)))) + 
            A3ZZI*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45 - 
               2*(MZ*MZ)*C34*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56*
                   (-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C56 + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C56*C56) - 
                        4*(MZ*MZ)*C45*
                        ((MZ*MZ) + 2*C56) + 
                        4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-12*C45*C56 + 
                        (MZ*MZ)*(4*C45 + 2*C56))) - 
                  4*(MZ*MZ)*C36*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*C45*C56*(2*C45 + 2*C56) + 
                        (MZ*MZ)*
                         (4*(C45*C45) + 4*(C56*C56) - 
                          16*C45*C56)))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*C56 + 
                  4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C45*C45) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56))) - 
                  2*(MZ*MZ)*C36*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C45 + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (2*C45*((MZ*MZ) - 6*C56) + 
                        4*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (8*(C56*C56)*C45 - 
                        4*(MZ*MZ*MZ*MZ)*C56 + 
                        (MZ*MZ)*
                         (4*(C45*C45) + 8*(C56*C56) - 
                          8*C45*C56)))))) + 
         A3AAR*(A3ZZI*MZ*wZ*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45*
                (-2*(MZ*MZ) + 2*C36 + 2*C45) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     pow(-(MZ*MZ) + 2*C45,2))*C56 + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*(-4*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      C56 + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     4*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   C56*(-2*(MZ*MZ) + 2*C56) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      (4*(C56*C56) - 4*(MZ*MZ)*C56) - 
                     4*C45*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ)*C56)) - 
                  4*C36*(2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      C56*(-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ*MZ*MZ) + (MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ)*(C56*C56) - 
                        8*(MZ*MZ*MZ*MZ)*C56) - 
                     4*C45*
                      (pow(MZ,8) + (MZ*MZ*MZ*MZ*MZ*MZ)*(wZ*wZ) + 
                        8*(MZ*MZ*MZ*MZ)*(C56*C56) - 8*(MZ*MZ*MZ*MZ*MZ*MZ)*C56
)))) + A3ZZR*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*(wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45))*
                ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2))*
                C36*C45 - 
               2*(MZ*MZ)*C34*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   C56*(-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C56 + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C56*C56) - 
                        4*(MZ*MZ)*C45*((MZ*MZ) + 2*C56) + 
                        4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-12*C45*C56 + 
                        (MZ*MZ)*(4*C45 + 2*C56))) - 
                  4*(MZ*MZ)*C36*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*C45*C56*(2*C45 + 2*C56) + 
                        (MZ*MZ)*
                         (4*(C45*C45) + 4*(C56*C56) - 
                          16*C45*C56)))) + 
               4*(C34*C34)*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*C56 + 
                  4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C45*C45) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56))) - 
                  2*(MZ*MZ)*C36*
                   (2*(MZ*MZ)*(wZ*wZ*wZ*wZ)*C45 + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (2*C45*((MZ*MZ) - 6*C56) + 
                        4*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (8*(C56*C56)*C45 - 
                        4*(MZ*MZ*MZ*MZ)*C56 + 
                        (MZ*MZ)*
                         (4*(C45*C45) + 8*(C56*C56) - 
                          8*C45*C56)))))))))/1.048576e6;
}

double GetGeneralScalar4e_Part22(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A2AAI, double A2AAR)
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
    (-4*(gL - gR)*(gL + gR)*(-E3456)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C34)*(1.0/C56)*(C46 - C35)*
       ((-(A1ZZR*A2AAI) + A1ZZI*A2AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*(-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45)) - 
      2*(gL - gR)*(gL + gR)*(-E3456)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       ((-(A1ZZR*A2AAI) + A1ZZI*A2AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (C34 - C46 + C35 - C56) - 
      2*(gL - gR)*(gL + gR)*(-E3456)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       ((-(A1ZZR*A2AAI) + A1ZZI*A2AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (-C34 - C46 + C35 + C56) - 
      4*(el*el)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C34)*(1.0/C56)*(C46 + C35)*
       (-((A1ZZI*A2AAI + A1ZZR*A2AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) - 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (C46*C35 - C36*C45 + C34*C56) - 
      4*(el*el)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C45)*(C35 + C46)*
       (C36*C45 + C35*C46 - C34*C56)*
       (-((A1ZZI*A2AAI + A1ZZR*A2AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) - 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) - 
      2*(gL - gR)*(gL + gR)*E3456*(el*el)*(MZ*MZ)*(1/(vh*vh))*
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
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) - 
      4*(gL - gR)*(gL + gR)*E3456*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C45)*(-C35 + C46)*
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
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) - 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56))*
       (-((C35*C35)*C46) + 
         C36*C45*(C36 + C45 + C46) + 
         C34*(C36 + C45 - C46)*C56 + 
         C35*(C36*(C45 - C46) - 
            C46*(C45 + C46) - C34*C56)) + 
      2*(el*el)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-((A1ZZI*A2AAI + A1ZZR*A2AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) - 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (-((C35*C35)*C46) + 
         C36*C45*(C34 - C46 + C56) + 
         C34*C56*(C34 + C46 + C56) + 
         C35*(-(C46*(C34 + C46)) - 
            C36*C45 + (C34 - C46)*C56)) + 
      2*(el*el)*((gL+gR)*(gL+gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-((A1ZZI*A2AAI + A1ZZR*A2AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A2AAI + A1ZZR*A2AAR)*(-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) - 
         (A1ZZR*A2AAI - A1ZZI*A2AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (-((C35*C35)*C46) - 
         C34*C56*(C34 - C46 + C56) - 
         C36*C45*(C34 + C46 + C56) + 
         C35*((C34 - C46)*C46 - 
            C36*C45 + (C34 + C46)*C56))))/
  524288.;
}

double GetGeneralScalar4e_Part23(LeptonVectors &leptons, double A2AAI, double A2AAR, double A2ZZI, double A2ZZR, double A3AAI, double A3AAR, double A3ZZI, double A3ZZR)
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
    (8*(-E3456)*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-((A2ZZI*A3AAI + A2ZZR*A3AAR + A2AAI*A3ZZI + A2AAR*A3ZZR)*
            (MZ*MZ)*(wZ*wZ)) + 
         (A2ZZI*A3AAI + A2ZZR*A3AAR + A2AAI*A3ZZI + A2AAR*A3ZZR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (-(A2ZZR*A3AAI) + A2ZZI*A3AAR + A2AAR*A3ZZI - A2AAI*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45)) - 
      4*(gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((C34*C34) - (C46*C46) + (C35*C35) - 
         (C56*C56))*((-(A2ZZR*A3AAI) + A2ZZI*A3AAR - A2AAR*A3ZZI + 
            A2AAI*A3ZZR)*(MZ*MZ)*(wZ*wZ) + 
         (A2ZZR*A3AAI - A2ZZI*A3AAR + A2AAR*A3ZZI - A2AAI*A3ZZR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A2ZZI*A3AAI + A2ZZR*A3AAR - A2AAI*A3ZZI - A2AAR*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45)) - 
      4*(gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-(C34*C34) - (C46*C46) + (C35*C35) + 
         (C56*C56))*((-(A2ZZR*A3AAI) + A2ZZI*A3AAR - A2AAR*A3ZZI + 
            A2AAI*A3ZZR)*(MZ*MZ)*(wZ*wZ) + 
         (A2ZZR*A3AAI - A2ZZI*A3AAR + A2AAR*A3ZZI - A2AAI*A3ZZR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A2ZZI*A3AAI + A2ZZR*A3AAR - A2AAI*A3ZZI - A2AAR*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45)) + 
      16*(gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       ((C35*C35) - (C46*C46))*
       ((pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
            pow(Sqrt2*SqrtC34 - 
              Sqrt2*SqrtC56,-1)*
            pow(Sqrt2*SqrtC34 + 
              Sqrt2*SqrtC56,-1)*
            ((A2ZZI*A3AAI + A2ZZR*A3AAR)*MZ*wZ + 
              (A2ZZR*A3AAI - A2ZZI*A3AAR)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*(1.0/C36)*
            (1.0/C45))/4. + 
         (pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
            pow(Sqrt2*SqrtC36 - 
              Sqrt2*SqrtC45,-1)*
            pow(Sqrt2*SqrtC36 + 
              Sqrt2*SqrtC45,-1)*(1.0/C34)*
            (-((A2AAI*A3ZZI + A2AAR*A3ZZR)*MZ*wZ) + 
              (A2AAR*A3ZZI - A2AAI*A3ZZR)*
               (-MZ + Sqrt2*SqrtC36)*
               (MZ + Sqrt2*SqrtC36))*(1.0/C56))/4. 
+ (pow(Sqrt2*SqrtC36 - Sqrt2*SqrtC45,-1)*
            pow(Sqrt2*SqrtC36 + 
              Sqrt2*SqrtC45,-1)*
            pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),
             -1)*(1.0/C34)*
            ((A2AAI*A3ZZI + A2AAR*A3ZZR)*MZ*wZ - 
              (A2AAR*A3ZZI - A2AAI*A3ZZR)*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45))*(1.0/C56))/4. 
- (pow(Sqrt2*SqrtC34 - Sqrt2*SqrtC56,-1)*
            pow(Sqrt2*SqrtC34 + 
              Sqrt2*SqrtC56,-1)*
            pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
            (1.0/C36)*(1.0/C45)*
            ((A2ZZI*A3AAI + A2ZZR*A3AAR)*MZ*wZ + 
              (A2ZZR*A3AAI - A2ZZI*A3AAR)*
               (-MZ + Sqrt2*SqrtC56)*
               (MZ + Sqrt2*SqrtC56)))/4.)*
       (-(C36*C45) + C35*C46 - C34*C56) 
- 16*E3456*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       ((pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
            pow(Sqrt2*SqrtC34 - 
              Sqrt2*SqrtC56,-1)*
            pow(Sqrt2*SqrtC34 + 
              Sqrt2*SqrtC56,-1)*
            ((A2ZZR*A3AAI - A2ZZI*A3AAR)*MZ*wZ - 
              (A2ZZI*A3AAI + A2ZZR*A3AAR)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*(1.0/C36)*
            (1.0/C45))/4. + 
         (pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
            pow(Sqrt2*SqrtC36 - 
              Sqrt2*SqrtC45,-1)*
            pow(Sqrt2*SqrtC36 + 
              Sqrt2*SqrtC45,-1)*(1.0/C34)*
            ((-(A2AAR*A3ZZI) + A2AAI*A3ZZR)*MZ*wZ - 
              (A2AAI*A3ZZI + A2AAR*A3ZZR)*
               (-MZ + Sqrt2*SqrtC36)*
               (MZ + Sqrt2*SqrtC36))*(1.0/C56))/4. 
+ (pow(Sqrt2*SqrtC36 - Sqrt2*SqrtC45,-1)*
            pow(Sqrt2*SqrtC36 + 
              Sqrt2*SqrtC45,-1)*
            pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),
             -1)*(1.0/C34)*
            ((A2AAR*A3ZZI - A2AAI*A3ZZR)*MZ*wZ + 
              (A2AAI*A3ZZI + A2AAR*A3ZZR)*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45))*(1.0/C56))/4. 
+ (pow(Sqrt2*SqrtC34 - Sqrt2*SqrtC56,-1)*
            pow(Sqrt2*SqrtC34 + 
              Sqrt2*SqrtC56,-1)*
            pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
            (1.0/C36)*(1.0/C45)*
            ((-(A2ZZR*A3AAI) + A2ZZI*A3AAR)*MZ*wZ + 
              (A2ZZI*A3AAI + A2ZZR*A3AAR)*
               (-MZ + Sqrt2*SqrtC56)*
               (MZ + Sqrt2*SqrtC56)))/4.)*
       ((C35*C35) + (C46*C46) - 2*C36*C45 + 
         2*C34*C56) - 
      16*(-E3456)*(el*el)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       ((pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
            pow(-(Sqrt2*SqrtC34) + 
              Sqrt2*SqrtC56,-1)*
            pow(Sqrt2*SqrtC34 + 
              Sqrt2*SqrtC56,-1)*(1.0/C36)*
            ((A2AAR*A3ZZI - A2AAI*A3ZZR)*MZ*wZ + 
              (A2AAI*A3ZZI + A2AAR*A3ZZR)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*(1.0/C45))/4. 
+ (pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
            pow(-(Sqrt2*SqrtC36) + 
              Sqrt2*SqrtC45,-1)*
            pow(Sqrt2*SqrtC36 + 
              Sqrt2*SqrtC45,-1)*
            ((-(A2ZZR*A3AAI) + A2ZZI*A3AAR)*MZ*wZ + 
              (A2ZZI*A3AAI + A2ZZR*A3AAR)*
               (-MZ + Sqrt2*SqrtC36)*
               (MZ + Sqrt2*SqrtC36))*(1.0/C34)*
            (1.0/C56))/4. + 
         (pow(-(Sqrt2*SqrtC36) + 
              Sqrt2*SqrtC45,-1)*
            pow(Sqrt2*SqrtC36 + 
              Sqrt2*SqrtC45,-1)*
            pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),
             -1)*(1.0/C34)*
            ((A2ZZR*A3AAI - A2ZZI*A3AAR)*MZ*wZ - 
              (A2ZZI*A3AAI + A2ZZR*A3AAR)*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45))*(1.0/C56))/4. 
+ (pow(-(Sqrt2*SqrtC34) + Sqrt2*SqrtC56,
             -1)*pow(Sqrt2*SqrtC34 + 
              Sqrt2*SqrtC56,-1)*
            pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
            (1.0/C36)*(1.0/C45)*
            ((-(A2AAR*A3ZZI) + A2AAI*A3ZZR)*MZ*wZ - 
              (A2AAI*A3ZZI + A2AAR*A3ZZR)*
               (-MZ + Sqrt2*SqrtC56)*
               (MZ + Sqrt2*SqrtC56)))/4.)*
       ((C46*C46) + (C35*C35) + 2*C36*C45 - 
         2*C34*C56) + 
      8*(-E3456)*(el*el)*((gL+gR)*(gL+gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-((A2ZZI*A3AAI + A2ZZR*A3AAR + A2AAI*A3ZZI + A2AAR*A3ZZR)*
            (MZ*MZ)*(wZ*wZ)) + 
         (A2ZZI*A3AAI + A2ZZR*A3AAR + A2AAI*A3ZZI + A2AAR*A3ZZR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (-(A2ZZR*A3AAI) + A2ZZI*A3AAR + A2AAR*A3ZZI - A2AAI*A3ZZR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (C46*C35 - C34*C56) + 
      16*(gL - gR)*(gL + gR)*(el*el)*(1/(vh*vh))*
       (-(C46*C46) + (C35*C35))*
       ((pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
            pow(-(Sqrt2*SqrtC34) + 
              Sqrt2*SqrtC56,-1)*
            pow(Sqrt2*SqrtC34 + 
              Sqrt2*SqrtC56,-1)*(1.0/C36)*
            ((A2AAI*A3ZZI + A2AAR*A3ZZR)*MZ*wZ - 
              (A2AAR*A3ZZI - A2AAI*A3ZZR)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*(1.0/C45))/4. 
- (pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
            pow(-(Sqrt2*SqrtC36) + 
              Sqrt2*SqrtC45,-1)*
            pow(Sqrt2*SqrtC36 + 
              Sqrt2*SqrtC45,-1)*
            ((A2ZZI*A3AAI + A2ZZR*A3AAR)*MZ*wZ + 
              (A2ZZR*A3AAI - A2ZZI*A3AAR)*
               (-MZ + Sqrt2*SqrtC36)*
               (MZ + Sqrt2*SqrtC36))*(1.0/C34)*
            (1.0/C56))/4. + 
         (pow(-(Sqrt2*SqrtC36) + 
              Sqrt2*SqrtC45,-1)*
            pow(Sqrt2*SqrtC36 + 
              Sqrt2*SqrtC45,-1)*
            pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),
             -1)*(1.0/C34)*
            ((A2ZZI*A3AAI + A2ZZR*A3AAR)*MZ*wZ + 
              (A2ZZR*A3AAI - A2ZZI*A3AAR)*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45))*(1.0/C56))/4. 
+ (pow(-(Sqrt2*SqrtC34) + Sqrt2*SqrtC56,
             -1)*pow(Sqrt2*SqrtC34 + 
              Sqrt2*SqrtC56,-1)*
            pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
            (1.0/C36)*(1.0/C45)*
            (-((A2AAI*A3ZZI + A2AAR*A3ZZR)*MZ*wZ) + 
              (A2AAR*A3ZZI - A2AAI*A3ZZR)*
               (-MZ + Sqrt2*SqrtC56)*
               (MZ + Sqrt2*SqrtC56)))/4.)*
       (C46*C35 - C36*C45 - C34*C56) + 
      8*E3456*(el*el)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
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
          (-2*(MZ*MZ) + 2*C34 + 2*C56))))/524288.;
}

double GetGeneralScalar4e_Part24(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A3AAI, double A3AAR)
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
    (-4*E3456*(el*el)*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C34)*(1.0/C56)*
       (-((A1ZZI*A3AAI + A1ZZR*A3AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) - 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (C35 + C46) - 
      2*(-E3456)*(el*el)*((gL+gR)*(gL+gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-((A1ZZI*A3AAI + A1ZZR*A3AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) - 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (-C34 + C46 + C35 - C56) - 
      2*(-E3456)*(el*el)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-((A1ZZI*A3AAI + A1ZZR*A3AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) - 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (C34 + C46 + C35 + C56) + 
      4*(gL - gR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C34)*(1.0/C56)*
       ((-(A1ZZR*A3AAI) + A1ZZI*A3AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       (C35 - C46)*
       (-(C36*C45) + C35*C46 + C34*C56) 
- 2*E3456*(el*el)*((gL+gR)*(gL+gR))*(MZ*MZ)*(1/(vh*vh))*
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
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) - 
      4*(-E3456)*(el*el)*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C45)*(C46 + C35)*
       (-((A1ZZI*A3AAI + A1ZZR*A3AAR)*(MZ*MZ)*(wZ*wZ)) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) - 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56)) + 
      4*(gL - gR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C45)*(-C46 + C35)*
       (C46*C35 + C36*C45 - C34*C56)*
       ((-(A1ZZR*A3AAI) + A1ZZI*A3AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*MZ*wZ*
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
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*
          (-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*
          (-MZ + Sqrt2*SqrtC56)*
          (MZ + Sqrt2*SqrtC56) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C34 + 2*C56))*
       ((C35*C35)*C46 + 
         C36*C45*(-C36 + C45 + C46) - 
         C34*(C36 - C45 + C46)*C56 - 
         C35*(C36*(C45 - C46) + 
            C46*(C45 + C46) - C34*C56)) + 
      2*(gL - gR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       ((-(A1ZZR*A3AAI) + A1ZZI*A3AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       ((C35*C35)*C46 + 
         C34*(C34 + C46 - C56)*C56 - 
         C36*C45*(-C34 + C46 + C56) - 
         C35*(C46*(C34 + C46) - 
            C36*C45 + (C34 - C46)*C56)) + 
      2*(gL - gR)*(gL + gR)*(el*el)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       ((-(A1ZZR*A3AAI) + A1ZZI*A3AAR)*(MZ*MZ)*(wZ*wZ) + 
         (A1ZZR*A3AAI - A1ZZI*A3AAR)*(-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45) + 
         (A1ZZI*A3AAI + A1ZZR*A3AAR)*MZ*wZ*
          (-2*(MZ*MZ) + 2*C36 + 2*C45))*
       ((C35*C35)*C46 + 
         C36*C45*(-C34 - C46 + C56) + 
         C34*C56*(-C34 + C46 + C56) - 
         C35*((C46*C46) - C34*C46 - 
            C36*C45 + (C34 + C46)*C56))))/
  524288.;
}

double GetGeneralScalar4e_Part26(LeptonVectors &leptons, double A2AAI, double A2AAR, double A2ZAI, double A2ZAR)
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
    (4*(gL + gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow(C36,-2)*pow(C45,-2)*
       (2*(C36*C36)*(C45*C45) + 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(-C46 + C35,2) + pow(-C34 + C56,2))*
          C36*C45)*
       ((A2AAR*A2ZAI - A2AAI*A2ZAR)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
          (2*C36 + 2*C45) + 
         (A2AAR*A2ZAI - A2AAI*A2ZAR)*MZ*wZ*
          (2*(MZ*MZ*MZ*MZ)*C36 + 8*(C45*C45)*C36 + 
            2*((MZ*MZ*MZ*MZ) + 4*(C36*C36) - 8*(MZ*MZ)*C36)*
             C45) + (A2AAI*A2ZAI + A2AAR*A2ZAR)*(MZ*MZ)*(wZ*wZ)*
          (4*(C36*C36) + 4*(C45*C45) - 
            (MZ*MZ)*(2*C36 + 2*C45)) + 
         (A2AAI*A2ZAI + A2AAR*A2ZAR)*(-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)*((MZ*MZ) - 2*C36)*
          (-8*C36*C45 + (MZ*MZ)*(2*C36 + 2*C45))) 
+ 4*(gL + gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       pow(C34,-2)*pow(C56,-2)*
       (2*pow(C36*C45 - C35*C46,2) + 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 - C45,2) + pow(C35 - C46,2))*
          C34*C56)*
       ((A2AAR*A2ZAI - A2AAI*A2ZAR)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
          (2*C34 + 2*C56) + 
         (A2AAI*A2ZAI + A2AAR*A2ZAR)*(MZ*MZ)*(wZ*wZ)*
          (4*(C34*C34) + 4*(C56*C56) - 
            (MZ*MZ)*(2*C34 + 2*C56)) + 
         (A2AAI*A2ZAI + A2AAR*A2ZAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*((MZ*MZ) - 2*C56)*
          (-8*C34*C56 + (MZ*MZ)*(2*C34 + 2*C56)) 
+ (A2AAR*A2ZAI - A2AAI*A2ZAR)*MZ*wZ*
          (2*(MZ*MZ*MZ*MZ)*C56 + 8*(C34*C34)*C56 + 
            2*C34*((MZ*MZ*MZ*MZ) + 4*(C56*C56) - 
               8*(MZ*MZ)*C56))) + 
      (gL - gR)*MZ*(-E3456)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(A2AAI*
          (A2ZAI*wZ*(-2*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ*MZ*MZ)*C36*C34) + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ*MZ*MZ)*C36*C34) + 
                  8*(MZ*MZ*MZ*MZ)*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34)*C56) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C36*C34)) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36)) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 2*(MZ*MZ)*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C36*C34)) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36)) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 2*(MZ*MZ)*C36)*
                      C34)*C56)) + 
            A2ZAR*MZ*(-(((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     ((-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)*
                        (-MZ + Sqrt2*SqrtC34)*
                        (MZ + Sqrt2*SqrtC34) - 
                       (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)
) - 4*(C56*C56)*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                       (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)*
                        (-MZ + Sqrt2*SqrtC34)*
                        (MZ + Sqrt2*SqrtC34)*
                        ((MZ*MZ*MZ*MZ) + 
                         2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                       (MZ*MZ)*(wZ*wZ)*
                        (2*(MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                         (MZ*MZ)*(2*C36 + 6*C34))) + 
                    2*(MZ*MZ)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                         4*(C36*C36)) + 
                       4*(C34*C34)*
                        (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C36)*
                        C34)*C56)) + 
               4*(C45*C45)*
                (-4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) 
- ((MZ*MZ) + (wZ*wZ))*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) - 4*(MZ*MZ)*C36 + 
                        4*C36*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        (MZ*MZ)*(6*C36 + 2*C34))) + 
                  2*(4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ)*((MZ*MZ) - 2*C36)*C36*
                      C34)*C56) + 
               2*C45*(-4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36)) + 
                     4*(C34*C34)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C36)*
                      C34) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ)*((MZ*MZ) - 2*C36)*C36*
                      C34) - 
                  8*(MZ*MZ*MZ*MZ)*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34))*
                   C56))) + 
         A2AAR*(A2ZAR*wZ*(-2*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ*MZ*MZ)*C36*C34) + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ*MZ*MZ)*C36*C34) + 
                  8*(MZ*MZ*MZ*MZ)*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34)*C56) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C36*C34)) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36)) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 2*(MZ*MZ)*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C36*C34)) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36)) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 2*(MZ*MZ)*C36)*
                      C34)*C56)) + 
            A2ZAI*MZ*(((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) - 
                  4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 
                        2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 6*C34))) + 
                  2*(MZ*MZ)*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36)) + 
                     4*(C34*C34)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  ((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) - 4*(MZ*MZ)*C36 + 
                        4*C36*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        (MZ*MZ)*(6*C36 + 2*C34))) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36))*(C34*C34) - 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ)*(-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36*
                      C34)*C56) + 
               2*C45*(4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36)) + 
                     4*(C34*C34)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C36)*
                      C34) - 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ)*((MZ*MZ) - 2*C36)*C36*
                      C34) + 
                  8*(MZ*MZ*MZ*MZ)*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34))*
                   C56)))) + 
      (gL + gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 + 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(-C46 + C35,2) - 
            4*C34*C56))*
       (A2AAI*(-(A2ZAR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    4*(C56*C56)*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                        C34)*C56) + 
                 4*(C45*C45)*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    4*(C56*C56)*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                        C34)*C56) + 
                 2*C45*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 6*(MZ*MZ)*C36)*
                        C34) + 
                    4*(C56*C56)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 6*(MZ*MZ)*C36)*
                        C34) - 
                    8*(MZ*MZ)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 6*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 6*(MZ*MZ)*C36) - 
                       2*(3*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         12*(MZ*MZ)*(C36*C36) - 
                         16*(MZ*MZ*MZ*MZ)*C36)*C34)*C56))) + 
            A2ZAI*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C36*C36) + 4*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 20*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)))*
                   C56) - 
               2*(MZ*MZ)*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 20*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  4*(C56*C56)*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C36*C36) + 4*(C34*C34)) - 
                        8*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C36*C34 + 
                        5*(MZ*MZ)*(2*C36 + 2*C34))) - 
                  8*(MZ*MZ)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34)))*
                   C56) + 
               4*(C45*C45)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        5*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-2*(MZ*MZ*MZ*MZ) - 16*C36*C34 + 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*(3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C36*C36) + 4*(C34*C34)) - 
                        8*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C36*C34 + 
                        5*(MZ*MZ)*(2*C36 + 2*C34)))*C56
))) + A2AAR*(A2ZAI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                      C34)*C56) + 
               2*C45*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                      C34) + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                      C34) - 
                  8*(MZ*MZ)*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36) - 
                     2*(3*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        12*(MZ*MZ)*(C36*C36) - 
                        16*(MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A2ZAR*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C36*C36) + 4*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 20*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)))*C56
) - 2*(MZ*MZ)*C45*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 20*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  4*(C56*C56)*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C36*C36) + 4*(C34*C34)) - 
                        8*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C36*C34 + 
                        5*(MZ*MZ)*(2*C36 + 2*C34))) - 
                  8*(MZ*MZ)*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34)))*C56
) + 4*(C45*C45)*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        5*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-2*(MZ*MZ*MZ*MZ) - 16*C36*C34 + 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*(3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C36*C36) + 4*(C34*C34)) - 
                        8*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C36*C34 + 
                        5*(MZ*MZ)*(2*C36 + 2*C34)))*C56)
))) + (gL + gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + 
         pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 + 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 - C46,2) - 4*C36*C45)*
          C56)*(A2AAI*(-(A2ZAR*MZ*wZ*
               ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    4*(C36*C36)*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    2*C36*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                       8*(MZ*MZ)*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56))) + 
                 4*(C34*C34)*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    4*(C36*C36)*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    2*C36*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                       8*(MZ*MZ)*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56))) + 
                 2*C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                       8*(MZ*MZ)*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56)) + 
                    4*(C36*C36)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                       8*(MZ*MZ)*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56)) - 
                    8*(MZ*MZ)*C36*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56) - 
                       2*C45*
                        (3*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         12*(MZ*MZ)*(C56*C56) - 
                         16*(MZ*MZ*MZ*MZ)*C56))))) + 
            A2ZAI*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-2*(MZ*MZ)*C36*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 20*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C45*C45) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)))) - 
               2*(MZ*MZ)*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 20*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) - 
                  8*(MZ*MZ)*C36*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C45*C45) + 4*(C56*C56)) - 
                        8*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C45*C56 + 
                        5*(MZ*MZ)*(2*C45 + 2*C56)))) + 
               4*(C34*C34)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        5*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-2*(MZ*MZ*MZ*MZ) - 16*C45*C56 + 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) - 
                  2*(MZ*MZ)*C36*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C45*C45) + 4*(C56*C56)) - 
                        8*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C45*C56 + 
                        5*(MZ*MZ)*(2*C45 + 2*C56)))))) + 
         A2AAR*(A2ZAI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56))) + 
               2*C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56)) - 
                  8*(MZ*MZ)*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56) - 
                     2*C45*
                      (3*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        12*(MZ*MZ)*(C56*C56) - 
                        16*(MZ*MZ*MZ*MZ)*C56)))) + 
            A2ZAR*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-2*(MZ*MZ)*C36*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 20*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C45*C45) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)))) - 
               2*(MZ*MZ)*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 20*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) - 
                  8*(MZ*MZ)*C36*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C45*C45) + 4*(C56*C56)) - 
                        8*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C45*C56 + 
                        5*(MZ*MZ)*(2*C45 + 2*C56)))) + 
               4*(C34*C34)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        5*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-2*(MZ*MZ*MZ*MZ) - 16*C45*C56 + 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) - 
                  2*(MZ*MZ)*C36*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C45*C45) + 4*(C56*C56)) - 
                        8*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C45*C56 + 
                        5*(MZ*MZ)*(2*C45 + 2*C56))))))) + 
      (gL - gR)*MZ*E3456*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (A2AAI*(A2ZAI*wZ*(-2*C34*
                (8*(MZ*MZ*MZ*MZ)*(Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (16*(MZ*MZ*MZ*MZ)*C45*C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   (16*(MZ*MZ*MZ*MZ)*C45*C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C45*C56)) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  2*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 2*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C45*C56)) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 2*(MZ*MZ)*C56)))) + 
            A2ZAR*MZ*(2*C34*
                (-8*(MZ*MZ*MZ*MZ)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     8*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 2*C56) + 
                     4*(C45*C45)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (4*(C45*C45)*
                      (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C56*C56)) + 
                     16*(MZ*MZ)*C45*((MZ*MZ) - 2*C56)*
                      C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 8*(MZ*MZ)*C56))) - 
               ((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*(MZ*MZ)*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     8*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 2*C56) + 
                     4*(C45*C45)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 
                        2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        (MZ*MZ)*(6*C45 + 2*C56)))) + 
               4*(C34*C34)*
                (-4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*C36*(4*(C45*C45)*
                      (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C56*C56)) + 
                     16*(MZ*MZ)*C45*((MZ*MZ) - 2*C56)*
                      C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 8*(MZ*MZ)*C56)) - 
                  ((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) - 4*(MZ*MZ)*C56 + 
                        4*C45*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 6*C56)))))) + 
         A2AAR*(A2ZAR*wZ*(-2*C34*
                (8*(MZ*MZ*MZ*MZ)*(Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (16*(MZ*MZ*MZ*MZ)*C45*C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   (16*(MZ*MZ*MZ*MZ)*C45*C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C45*C56)) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 2*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C45*C56)) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 2*(MZ*MZ)*C56)))) + 
            A2ZAI*MZ*(2*C34*
                (8*(MZ*MZ*MZ*MZ)*(Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     8*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 2*C56) + 
                     4*(C45*C45)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) - 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (4*(C45*C45)*
                      (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C56*C56)) + 
                     16*(MZ*MZ)*C45*((MZ*MZ) - 2*C56)*
                      C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               ((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*(MZ*MZ)*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     8*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 2*C56) + 
                     4*(C45*C45)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 
                        2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        (MZ*MZ)*(6*C45 + 2*C56)))) + 
               4*(C34*C34)*
                (4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*C36*(4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) + 
                     16*(MZ*MZ)*(-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C45*
                      C56 - 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  ((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) - 4*(MZ*MZ)*C56 + 
                        4*C45*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 6*C56)))))))))/
  1.048576e6;
}

double GetGeneralScalar4e_Part27(LeptonVectors &leptons, double A3AAI, double A3AAR, double A3ZAI, double A3ZAR)
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
    (4*(gL + gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow(C36,-2)*pow(C45,-2)*
       (-2*(C36*C36)*(C45*C45) - 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(C46 + C35,2) + pow(C34 + C56,2))*
          C36*C45)*
       ((A3AAR*A3ZAI - A3AAI*A3ZAR)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
          (2*C36 + 2*C45) + 
         (A3AAR*A3ZAI - A3AAI*A3ZAR)*MZ*wZ*
          (2*(MZ*MZ*MZ*MZ)*C36 + 8*(C45*C45)*C36 + 
            2*((MZ*MZ*MZ*MZ) + 4*(C36*C36) - 8*(MZ*MZ)*C36)*
             C45) + (A3AAI*A3ZAI + A3AAR*A3ZAR)*(MZ*MZ)*(wZ*wZ)*
          (4*(C36*C36) + 4*(C45*C45) - 
            (MZ*MZ)*(2*C36 + 2*C45)) + 
         (A3AAI*A3ZAI + A3AAR*A3ZAR)*(-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45)*((MZ*MZ) - 2*C36)*
          (-8*C36*C45 + (MZ*MZ)*(2*C36 + 2*C45))) 
+ 4*(gL + gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       pow(C34,-2)*pow(C56,-2)*
       (-2*pow(C36*C45 - C35*C46,2) - 
         2*(C34*C34)*(C56*C56) + 
         (pow(C36 + C45,2) + pow(C35 + C46,2))*
          C34*C56)*
       ((A3AAR*A3ZAI - A3AAI*A3ZAR)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*
          (2*C34 + 2*C56) + 
         (A3AAI*A3ZAI + A3AAR*A3ZAR)*(MZ*MZ)*(wZ*wZ)*
          (4*(C34*C34) + 4*(C56*C56) - 
            (MZ*MZ)*(2*C34 + 2*C56)) + 
         (A3AAI*A3ZAI + A3AAR*A3ZAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34)*((MZ*MZ) - 2*C56)*
          (-8*C34*C56 + (MZ*MZ)*(2*C34 + 2*C56)) 
+ (A3AAR*A3ZAI - A3AAI*A3ZAR)*MZ*wZ*
          (2*(MZ*MZ*MZ*MZ)*C56 + 8*(C34*C34)*C56 + 
            2*C34*((MZ*MZ*MZ*MZ) + 4*(C56*C56) - 
               8*(MZ*MZ)*C56))) + 
      (gL - gR)*MZ*(-E3456)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(A3AAI*
          (A3ZAI*wZ*(-2*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ*MZ*MZ)*C36*C34) + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ*MZ*MZ)*C36*C34) + 
                  8*(MZ*MZ*MZ*MZ)*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34)*C56) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C36*C34)) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36)) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 2*(MZ*MZ)*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C36*C34)) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36)) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 2*(MZ*MZ)*C36)*
                      C34)*C56)) + 
            A3ZAR*MZ*(-(((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     ((-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)*
                        (-MZ + Sqrt2*SqrtC34)*
                        (MZ + Sqrt2*SqrtC34) - 
                       (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)
) - 4*(C56*C56)*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                       (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)*
                        (-MZ + Sqrt2*SqrtC34)*
                        (MZ + Sqrt2*SqrtC34)*
                        ((MZ*MZ*MZ*MZ) + 
                         2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                       (MZ*MZ)*(wZ*wZ)*
                        (2*(MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                         (MZ*MZ)*(2*C36 + 6*C34))) + 
                    2*(MZ*MZ)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                         4*(C36*C36)) + 
                       4*(C34*C34)*
                        (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C36)*
                        C34)*C56)) + 
               4*(C45*C45)*
                (-4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) 
- ((MZ*MZ) + (wZ*wZ))*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) - 4*(MZ*MZ)*C36 + 
                        4*C36*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        (MZ*MZ)*(6*C36 + 2*C34))) + 
                  2*(4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ)*((MZ*MZ) - 2*C36)*C36*
                      C34)*C56) + 
               2*C45*(-4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36)) + 
                     4*(C34*C34)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C36)*
                      C34) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ)*((MZ*MZ) - 2*C36)*C36*
                      C34) - 
                  8*(MZ*MZ*MZ*MZ)*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34))*
                   C56))) + 
         A3AAR*(A3ZAR*wZ*(-2*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ*MZ*MZ)*C36*C34) + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ*MZ*MZ)*C36*C34) + 
                  8*(MZ*MZ*MZ*MZ)*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34)*C56) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C36*C34)) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36)) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 2*(MZ*MZ)*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C36*C34)) - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C36*C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36)) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36))*(C34*C34) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 2*(MZ*MZ)*C36)*
                      C34)*C56)) + 
            A3ZAI*MZ*(((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) - 
                  4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 
                        2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 6*C34))) + 
                  2*(MZ*MZ)*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36)) + 
                     4*(C34*C34)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34)) + 
                  ((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) - 4*(MZ*MZ)*C36 + 
                        4*C36*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        (MZ*MZ)*(6*C36 + 2*C34))) + 
                  2*(4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36))*(C34*C34) - 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ)*(-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36*
                      C34)*C56) + 
               2*C45*(4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C36*C36)) + 
                     4*(C34*C34)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 2*C36)*
                      C34) - 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     16*(MZ*MZ)*((MZ*MZ) - 2*C36)*C36*
                      C34) + 
                  8*(MZ*MZ*MZ*MZ)*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C34))*
                   C56)))) + 
      (gL + gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 - 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(C46 + C35,2) + 
            4*C34*C56))*
       (A3AAI*(-(A3ZAR*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    4*(C56*C56)*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                        C34)*C56) + 
                 4*(C45*C45)*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    4*(C56*C56)*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                        C34)*C56) + 
                 2*C45*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 6*(MZ*MZ)*C36)*
                        C34) + 
                    4*(C56*C56)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                       8*(MZ*MZ)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 6*(MZ*MZ)*C36)*
                        C34) - 
                    8*(MZ*MZ)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 6*(MZ*MZ)*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 6*(MZ*MZ)*C36) - 
                       2*(3*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         12*(MZ*MZ)*(C36*C36) - 
                         16*(MZ*MZ*MZ*MZ)*C36)*C34)*C56))) + 
            A3ZAI*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C36*C36) + 4*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 20*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)))*
                   C56) - 
               2*(MZ*MZ)*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 20*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  4*(C56*C56)*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C36*C36) + 4*(C34*C34)) - 
                        8*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C36*C34 + 
                        5*(MZ*MZ)*(2*C36 + 2*C34))) - 
                  8*(MZ*MZ)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34)))*
                   C56) + 
               4*(C45*C45)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        5*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-2*(MZ*MZ*MZ*MZ) - 16*C36*C34 + 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*(3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C36*C36) + 4*(C34*C34)) - 
                        8*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C36*C34 + 
                        5*(MZ*MZ)*(2*C36 + 2*C34)))*C56
))) + A3AAR*(A3ZAI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                      C34)*C56) + 
               2*C45*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                      C34) + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) - 
                     8*(MZ*MZ)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36)*
                      C34) - 
                  8*(MZ*MZ)*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 6*(MZ*MZ)*C36) - 
                     2*(3*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        12*(MZ*MZ)*(C36*C36) - 
                        16*(MZ*MZ*MZ*MZ)*C36)*C34)*C56)) + 
            A3ZAR*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (4*(C56*C56)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C36*C36) + 4*(C34*C34) - 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-8*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 20*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)))*C56
) - 2*(MZ*MZ)*C45*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        4*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 20*C36*C34 - 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  4*(C56*C56)*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C36*C36) + 4*(C34*C34)) - 
                        8*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C36*C34 + 
                        5*(MZ*MZ)*(2*C36 + 2*C34))) - 
                  8*(MZ*MZ)*((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34)))*C56
) + 4*(C45*C45)*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C36*C36) + 4*(C34*C34)) - 
                        3*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      ((MZ*MZ*MZ*MZ) + 12*C36*C34 - 
                        2*(MZ*MZ)*(2*C36 + 2*C34))) + 
                  4*(C56*C56)*
                   (2*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C36*C36) + 4*(C34*C34)) - 
                        5*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-2*(MZ*MZ*MZ*MZ) - 16*C36*C34 + 
                        3*(MZ*MZ)*(2*C36 + 2*C34))) - 
                  2*(MZ*MZ)*(3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C36*C36) + 4*(C34*C34)) - 
                        8*(MZ*MZ)*(2*C36 + 2*C34)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C36*C34 + 
                        5*(MZ*MZ)*(2*C36 + 2*C34)))*C56)
))) + (gL + gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + 
         pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 - 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 + C46,2) + 4*C36*C45)*
          C56)*(A3AAI*(-(A3ZAR*MZ*wZ*
               ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    4*(C36*C36)*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    2*C36*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                       8*(MZ*MZ)*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56))) + 
                 4*(C34*C34)*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    4*(C36*C36)*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    2*C36*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                       8*(MZ*MZ)*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56))) + 
                 2*C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                       8*(MZ*MZ)*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56)) + 
                    4*(C36*C36)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                       8*(MZ*MZ)*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56)) - 
                    8*(MZ*MZ)*C36*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 6*(MZ*MZ)*C56) - 
                       2*C45*
                        (3*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         12*(MZ*MZ)*(C56*C56) - 
                         16*(MZ*MZ*MZ*MZ)*C56))))) + 
            A3ZAI*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-2*(MZ*MZ)*C36*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 20*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C45*C45) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)))) - 
               2*(MZ*MZ)*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 20*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) - 
                  8*(MZ*MZ)*C36*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C45*C45) + 4*(C56*C56)) - 
                        8*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C45*C56 + 
                        5*(MZ*MZ)*(2*C45 + 2*C56)))) + 
               4*(C34*C34)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        5*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-2*(MZ*MZ*MZ*MZ) - 16*C45*C56 + 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) - 
                  2*(MZ*MZ)*C36*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C45*C45) + 4*(C56*C56)) - 
                        8*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C45*C56 + 
                        5*(MZ*MZ)*(2*C45 + 2*C56)))))) + 
         A3AAR*(A3ZAI*MZ*wZ*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56))) + 
               2*C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56)) - 
                  8*(MZ*MZ)*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 6*(MZ*MZ)*C56) - 
                     2*C45*
                      (3*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        12*(MZ*MZ)*(C56*C56) - 
                        16*(MZ*MZ*MZ*MZ)*C56)))) + 
            A3ZAR*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-2*(MZ*MZ)*C36*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 20*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ)*
                      (4*(C45*C45) + 4*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-8*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)))) - 
               2*(MZ*MZ)*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        4*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 20*C45*C56 - 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) - 
                  8*(MZ*MZ)*C36*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C45*C45) + 4*(C56*C56)) - 
                        8*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C45*C56 + 
                        5*(MZ*MZ)*(2*C45 + 2*C56)))) + 
               4*(C34*C34)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 
                        2*(4*(C45*C45) + 4*(C56*C56)) - 
                        3*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*C45*C56 - 
                        2*(MZ*MZ)*(2*C45 + 2*C56))) + 
                  4*(C36*C36)*
                   (2*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ) + 
                        3*(4*(C45*C45) + 4*(C56*C56)) - 
                        5*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-2*(MZ*MZ*MZ*MZ) - 16*C45*C56 + 
                        3*(MZ*MZ)*(2*C45 + 2*C56))) - 
                  2*(MZ*MZ)*C36*
                   (3*(MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (6*(MZ*MZ*MZ*MZ) + 
                        5*(4*(C45*C45) + 4*(C56*C56)) - 
                        8*(MZ*MZ)*(2*C45 + 2*C56)) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-3*(MZ*MZ*MZ*MZ) - 28*C45*C56 + 
                        5*(MZ*MZ)*(2*C45 + 2*C56))))))) + 
      (gL - gR)*MZ*E3456*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (A3AAI*(A3ZAI*wZ*(-2*C34*
                (8*(MZ*MZ*MZ*MZ)*(Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (16*(MZ*MZ*MZ*MZ)*C45*C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   (16*(MZ*MZ*MZ*MZ)*C45*C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C45*C56)) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  2*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 2*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C45*C56)) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 2*(MZ*MZ)*C56)))) + 
            A3ZAR*MZ*(2*C34*
                (-8*(MZ*MZ*MZ*MZ)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     8*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 2*C56) + 
                     4*(C45*C45)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (4*(C45*C45)*
                      (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C56*C56)) + 
                     16*(MZ*MZ)*C45*((MZ*MZ) - 2*C56)*
                      C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 8*(MZ*MZ)*C56))) - 
               ((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*(MZ*MZ)*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     8*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 2*C56) + 
                     4*(C45*C45)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 
                        2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        (MZ*MZ)*(6*C45 + 2*C56)))) + 
               4*(C34*C34)*
                (-4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*C36*(4*(C45*C45)*
                      (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C56*C56)) + 
                     16*(MZ*MZ)*C45*((MZ*MZ) - 2*C56)*
                      C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 8*(MZ*MZ)*C56)) - 
                  ((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) - 4*(MZ*MZ)*C56 + 
                        4*C45*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 6*C56)))))) + 
         A3AAR*(A3ZAR*wZ*(-2*C34*
                (8*(MZ*MZ*MZ*MZ)*(Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (16*(MZ*MZ*MZ*MZ)*C45*C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  4*(C36*C36)*
                   (16*(MZ*MZ*MZ*MZ)*C45*C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C45*C56)) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 2*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*
                     (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                       4*C45*C56)) - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     4*C45*C56) + 
                  2*C36*((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56)) - 
                     8*(MZ*MZ)*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 2*(MZ*MZ)*C56)))) + 
            A3ZAI*MZ*(2*C34*
                (8*(MZ*MZ*MZ*MZ)*(Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     8*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 2*C56) + 
                     4*(C45*C45)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) - 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (4*(C45*C45)*
                      (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C56*C56)) + 
                     16*(MZ*MZ)*C45*((MZ*MZ) - 2*C56)*
                      C56 + 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 8*(MZ*MZ)*C56))) + 
               ((MZ*MZ) + (wZ*wZ))*
                ((MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*(MZ*MZ)*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) - 
                     8*(MZ*MZ*MZ*MZ)*C45*
                      ((MZ*MZ) + (wZ*wZ) - 2*C56) + 
                     4*(C45*C45)*
                      (3*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) - 
                  4*(C36*C36)*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 
                        2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C45*C45) - 
                        (MZ*MZ)*(6*C45 + 2*C56)))) + 
               4*(C34*C34)*
                (4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   ((-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) - 
                     (wZ*wZ)*(-(MZ*MZ) + 2*C45 + 2*C56)) + 
                  2*C36*(4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) - 
                        4*(C56*C56)) + 
                     16*(MZ*MZ)*(-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C45*
                      C56 - 
                     (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  ((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) - 4*(MZ*MZ)*C56 + 
                        4*C45*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (2*(MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        (MZ*MZ)*(2*C45 + 6*C56)))))))))/
  1.048576e6;
}

double GetGeneralScalar4e_Part29(LeptonVectors &leptons, double A2AAI, double A2AAR, double A2ZAI, double A2ZAR, double A3AAI, double A3AAR, double A3ZAI, double A3ZAR)
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
          (MZ + Sqrt2*SqrtC56)) - 
      4*(gL - gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       ((A2ZAI*A3AAI + A2ZAR*A3AAR - A2AAI*A3ZAI - A2AAR*A3ZAR)*MZ*wZ + 
         (A2ZAR*A3AAI - A2ZAI*A3AAR + A2AAR*A3ZAI - A2AAI*A3ZAR)*
          (-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36))*(1.0/C45)*
       ((C34*C34) - (C46*C46) + (C35*C35) - 
         (C56*C56)) - 4*(gL - gR)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*((A2ZAI*A3AAI + A2ZAR*A3AAR - A2AAI*A3ZAI - 
            A2AAR*A3ZAR)*MZ*wZ + 
         (A2ZAR*A3AAI - A2ZAI*A3AAR + A2AAR*A3ZAI - A2AAI*A3ZAR)*
          (-MZ + Sqrt2*SqrtC45)*
          (MZ + Sqrt2*SqrtC45))*
       (-(C34*C34) - (C46*C46) + (C35*C35) + 
         (C56*C56)) - (gL - gR)*(el*el*el)*(1/(vh*vh))*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
          ((A2ZAI*A3AAI + A2ZAR*A3AAR)*MZ*wZ + 
            (A2ZAR*A3AAI - A2ZAI*A3AAR)*
             (-MZ + Sqrt2*SqrtC34)*
             (MZ + Sqrt2*SqrtC34))*C34 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
          (-((A2AAI*A3ZAI + A2AAR*A3ZAR)*MZ*wZ) + 
            (A2AAR*A3ZAI - A2AAI*A3ZAR)*
             (-MZ + Sqrt2*SqrtC36)*
             (MZ + Sqrt2*SqrtC36))*C36 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
          (-((A2AAI*A3ZAI + A2AAR*A3ZAR)*MZ*wZ) + 
            (A2AAR*A3ZAI - A2AAI*A3ZAR)*
             (-MZ + Sqrt2*SqrtC45)*
             (MZ + Sqrt2*SqrtC45))*C45 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
          ((A2ZAI*A3AAI + A2ZAR*A3AAR)*MZ*wZ + 
            (A2ZAR*A3AAI - A2ZAI*A3AAR)*
             (-MZ + Sqrt2*SqrtC56)*
             (MZ + Sqrt2*SqrtC56))*C56)*
       (-(C36*C45) + C35*C46 - C34*C56) 
- (gL + gR)*E3456*(el*el*el)*(1/(vh*vh))*(1.0/C34)*
       (1.0/C36)*(1.0/C45)*(1.0/C56)*
       (2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
          ((-(A2ZAR*A3AAI) + A2ZAI*A3AAR)*MZ*wZ + 
            (A2ZAI*A3AAI + A2ZAR*A3AAR)*
             (-MZ + Sqrt2*SqrtC34)*
             (MZ + Sqrt2*SqrtC34))*C34 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
          ((A2AAR*A3ZAI - A2AAI*A3ZAR)*MZ*wZ + 
            (A2AAI*A3ZAI + A2AAR*A3ZAR)*
             (-MZ + Sqrt2*SqrtC36)*
             (MZ + Sqrt2*SqrtC36))*C36 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
          ((A2AAR*A3ZAI - A2AAI*A3ZAR)*MZ*wZ + 
            (A2AAI*A3ZAI + A2AAR*A3ZAR)*
             (-MZ + Sqrt2*SqrtC45)*
             (MZ + Sqrt2*SqrtC45))*C45 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
          ((-(A2ZAR*A3AAI) + A2ZAI*A3AAR)*MZ*wZ + 
            (A2ZAI*A3AAI + A2ZAR*A3AAR)*
             (-MZ + Sqrt2*SqrtC56)*
             (MZ + Sqrt2*SqrtC56))*C56)*
       ((C35*C35) + (C46*C46) - 2*C36*C45 + 
         2*C34*C56) - 
      (gL + gR)*(-E3456)*(el*el*el)*(1/(vh*vh))*(1.0/C36)*
       (1.0/C34)*(1.0/C45)*(1.0/C56)*
       (2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
          ((-(A2ZAR*A3AAI) + A2ZAI*A3AAR)*MZ*wZ + 
            (A2ZAI*A3AAI + A2ZAR*A3AAR)*
             (-MZ + Sqrt2*SqrtC36)*
             (MZ + Sqrt2*SqrtC36))*C36 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
          ((A2AAR*A3ZAI - A2AAI*A3ZAR)*MZ*wZ + 
            (A2AAI*A3ZAI + A2AAR*A3ZAR)*
             (-MZ + Sqrt2*SqrtC34)*
             (MZ + Sqrt2*SqrtC34))*C34 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
          ((-(A2ZAR*A3AAI) + A2ZAI*A3AAR)*MZ*wZ + 
            (A2ZAI*A3AAI + A2ZAR*A3AAR)*
             (-MZ + Sqrt2*SqrtC45)*
             (MZ + Sqrt2*SqrtC45))*C45 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
          ((A2AAR*A3ZAI - A2AAI*A3ZAR)*MZ*wZ + 
            (A2AAI*A3ZAI + A2AAR*A3ZAR)*
             (-MZ + Sqrt2*SqrtC56)*
             (MZ + Sqrt2*SqrtC56))*C56)*
       ((C46*C46) + (C35*C35) + 2*C36*C45 - 
         2*C34*C56) + 
      4*(gL + gR)*(-E3456)*(el*el*el)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow(C36,-2)*pow(C45,-2)*
       (4*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ)*(C36*C36) + 
         4*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ)*(C36*C36) + 
         4*A2ZAI*A3AAI*(MZ*MZ*MZ*MZ)*(C45*C45) + 
         4*A2ZAR*A3AAR*(MZ*MZ*MZ*MZ)*(C45*C45) + 
         4*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ)*(C45*C45) + 
         4*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ)*(C45*C45) + 
         32*A2ZAI*A3AAI*(C36*C36)*(C45*C45) + 
         32*A2ZAR*A3AAR*(C36*C36)*(C45*C45) + 
         32*A2AAI*A3ZAI*(C36*C36)*(C45*C45) + 
         32*A2AAR*A3ZAR*(C36*C36)*(C45*C45) - 
         2*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ*MZ*MZ)*C36 - 
         2*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ*MZ*MZ)*C36 + 
         2*A2ZAI*A3AAI*(MZ*MZ*MZ*MZ)*(-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*C36 + 
         2*A2ZAR*A3AAR*(MZ*MZ*MZ*MZ)*(-MZ + Sqrt2*SqrtC36)*
          (MZ + Sqrt2*SqrtC36)*C36 - 
         24*A2ZAI*A3AAI*(MZ*MZ)*(C45*C45)*C36 - 
         24*A2ZAR*A3AAR*(MZ*MZ)*(C45*C45)*C36 - 
         24*A2AAI*A3ZAI*(MZ*MZ)*(C45*C45)*C36 - 
         24*A2AAR*A3ZAR*(MZ*MZ)*(C45*C45)*C36 - 
         2*A2ZAI*A3AAI*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 - 
         2*A2ZAR*A3AAR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 - 
         2*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 - 
         2*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45 - 
         24*A2ZAI*A3AAI*(MZ*MZ)*(C36*C36)*C45 - 
         24*A2ZAR*A3AAR*(MZ*MZ)*(C36*C36)*C45 - 
         24*A2AAI*A3ZAI*(MZ*MZ)*(C36*C36)*C45 - 
         24*A2AAR*A3ZAR*(MZ*MZ)*(C36*C36)*C45 + 
         16*A2ZAI*A3AAI*(MZ*MZ*MZ*MZ)*C36*C45 + 
         16*A2ZAR*A3AAR*(MZ*MZ*MZ*MZ)*C36*C45 + 
         16*A2AAI*A3ZAI*(MZ*MZ*MZ*MZ)*C36*C45 + 
         16*A2AAR*A3ZAR*(MZ*MZ*MZ*MZ)*C36*C45 + 
         (-(A2ZAR*A3AAI) + A2ZAI*A3AAR + A2AAR*A3ZAI - A2AAI*A3ZAR)*
          (MZ*MZ*MZ)*(wZ*wZ*wZ)*(2*C36 + 2*C45) - 
         (A2ZAR*A3AAI - A2ZAI*A3AAR - A2AAR*A3ZAI + A2AAI*A3ZAR)*MZ*wZ*
          (2*(MZ*MZ*MZ*MZ)*C36 + 8*(C45*C45)*C36 + 
            2*((MZ*MZ*MZ*MZ) + 4*(C36*C36) - 8*(MZ*MZ)*C36)*
             C45) + (A2ZAI*A3AAI + A2ZAR*A3AAR + A2AAI*A3ZAI + 
            A2AAR*A3ZAR)*(MZ*MZ)*(wZ*wZ)*
          (4*(C36*C36) + 4*(C45*C45) - 
            (MZ*MZ)*(2*C36 + 2*C45)))*
       (C46*C35 - C34*C56) - 
      (gL - gR)*(el*el*el)*(1/(vh*vh))*(1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(2*pow((MZ*MZ)*(wZ*wZ) + 
            pow(-(MZ*MZ) + 2*C36,2),-1)*
          ((A2ZAI*A3AAI + A2ZAR*A3AAR)*MZ*wZ + 
            (A2ZAR*A3AAI - A2ZAI*A3AAR)*
             (-MZ + Sqrt2*SqrtC36)*
             (MZ + Sqrt2*SqrtC36))*C36 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
          (-((A2AAI*A3ZAI + A2AAR*A3ZAR)*MZ*wZ) + 
            (A2AAR*A3ZAI - A2AAI*A3ZAR)*
             (-MZ + Sqrt2*SqrtC34)*
             (MZ + Sqrt2*SqrtC34))*C34 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
          ((A2ZAI*A3AAI + A2ZAR*A3AAR)*MZ*wZ + 
            (A2ZAR*A3AAI - A2ZAI*A3AAR)*
             (-MZ + Sqrt2*SqrtC45)*
             (MZ + Sqrt2*SqrtC45))*C45 + 
         2*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
          (-((A2AAI*A3ZAI + A2AAR*A3ZAR)*MZ*wZ) + 
            (A2AAR*A3ZAI - A2AAI*A3ZAR)*
             (-MZ + Sqrt2*SqrtC56)*
             (MZ + Sqrt2*SqrtC56))*C56)*
       (C46*C35 - C36*C45 - C34*C56) + 
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
               8*(MZ*MZ)*C56)))))/524288.;
}

double GetGeneralScalar4e_Part32(LeptonVectors &leptons, double A2ZAI, double A2ZAR, double A2ZZI, double A2ZZR)
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
    (8*el*(gL + gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (2*(C36*C36)*(C45*C45) + 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(-C46 + C35,2) + pow(-C34 + C56,2))*
          C36*C45)*
       ((A2ZAR*A2ZZI - A2ZAI*A2ZZR)*MZ*wZ*(2*C36 + 2*C45) + 
         (A2ZAI*A2ZZI + A2ZAR*A2ZZR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45))) + 
      8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((A2ZAR*A2ZZI - A2ZAI*A2ZZR)*MZ*wZ*(2*C36 + 2*C45) + 
         (A2ZAI*A2ZZI + A2ZAR*A2ZZR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45)))*
       (-C34 + C46 + C35 - C56)*
       (C34 + C46 + C35 + C56) + 
      8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
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
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) + 
      el*((gL*gL*gL) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 + 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(-C46 + C35,2) - 
            4*C34*C56))*
       (A2ZAI*(-(A2ZZR*MZ*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  C36*C34*C56*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                    4*C36*C34 + 
                    2*(2*C36 - 2*C34)*C56) + 
                 2*C45*(4*(C56*C56)*
                     (4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                       2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                        (-2*(MZ*MZ) + 2*C36) + 
                       4*(MZ*MZ)*
                        (5*(MZ*MZ) + (wZ*wZ) - 8*C36)*
                        C36*C34) + 
                    4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                     C34*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                       2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                    2*(MZ*MZ)*
                     (2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                        C36 + 
                       8*(C34*C34)*
                        (5*(MZ*MZ) + (wZ*wZ) - 8*C36)*
                        C36 + 
                       2*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        16*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                        C34)*C56) + 
                 4*(C45*C45)*
                  (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*C36*C34 
+ 4*(C56*C56)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    2*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        (C36*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       2*(-2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C36
)*C34)*C56))) + A2ZZI*
             (-2*(MZ*MZ)*C45*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-(MZ*MZ) + (wZ*wZ) + 2*C36)*C34) 
+ 4*(C56*C56)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 - 2*C34) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C36*C36) + 
                        4*(C34*C34)*((MZ*MZ) + 4*C36) + 
                        2*(-2*(MZ*MZ*MZ*MZ) - 8*(C36*C36) + 
                        6*(MZ*MZ)*C36)*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-20*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(-2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36 - 
                     4*(C34*C34)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        8*(3*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        2*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                         C36) + 
                     2*((MZ*MZ*MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                        (C36*C36) - 
                        16*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34))*C36*
                   C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ)*(2*C36 + 2*C34)*
                      (-(MZ*MZ) + 2*C36 + 2*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-16*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(MZ*MZ)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 - 2*C34) + 
                     ((MZ*MZ) - 2*C36)*
                      ((MZ*MZ) - 2*C34)*
                      (-20*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ)*C36 + 
                        8*(-(Sqrt2*SqrtC36) + 
                        Sqrt2*SqrtC34)*
                         (Sqrt2*SqrtC36 + 
                        Sqrt2*SqrtC34)*C36*
                         C34 - 
                        (MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) + 
                         12*C36*C34)))*C56) + 
               8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                C56*((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56)))
) + A2ZAR*(A2ZZI*MZ*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C34*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56) + 
               2*C45*(4*(C56*C56)*
                   (4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 8*C36)*
                      C36*C34) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(MZ*MZ)*
                   (2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*C36 + 
                     8*(C34*C34)*
                      (5*(MZ*MZ) + (wZ*wZ) - 8*C36)*C36 
+ 2*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        16*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C36*C34 + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C36*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     2*(-2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56)) + 
            A2ZZR*(-2*(MZ*MZ)*C45*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-(MZ*MZ) + (wZ*wZ) + 2*C36)*C34) + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 - 2*C34) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C36*C36) + 
                        4*(C34*C34)*((MZ*MZ) + 4*C36) + 
                        2*(-2*(MZ*MZ*MZ*MZ) - 8*(C36*C36) + 
                         6*(MZ*MZ)*C36)*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-20*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(-2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36 - 
                     4*(C34*C34)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        8*(3*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        2*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*C36
) + 2*((MZ*MZ*MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                         (C36*C36) - 
                        16*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34))*C36*
                   C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ)*(2*C36 + 2*C34)*
                      (-(MZ*MZ) + 2*C36 + 2*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-16*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(MZ*MZ)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (2*C36 - 2*C34) + 
                     ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                      (-20*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ)*C36 + 
                        8*(-(Sqrt2*SqrtC36) + 
                         Sqrt2*SqrtC34)*
                         (Sqrt2*SqrtC36 + 
                         Sqrt2*SqrtC34)*C36*
                         C34 - 
                        (MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) + 
                         12*C36*C34)))*C56) + 
               8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                C56*((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56))))
) + el*MZ*E3456*((gL*gL*gL) - (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (A2ZAI*(A2ZZI*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C45*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56)) - 
               2*C34*(2*(MZ*MZ)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*C45*C56) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   C56*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C45*
                      C56 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 16*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45*C56 - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     12*C45*C56) + 
                  2*C36*
                   (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C56*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56)) + 
                     2*(MZ*MZ)*C45*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        32*(C56*C56) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C56)))) + 
            A2ZZR*MZ*(8*((MZ*MZ) + (wZ*wZ))*C36*C45*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56)
)*C56 + 2*C34*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   C56*(-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*(-(MZ*MZ) + (wZ*wZ) + 2*C56)) 
+ 4*(C36*C36)*(-4*(C45*C45)*
                      (pow(-(MZ*MZ) + 2*C56,2) + 
                        (wZ*wZ)*((MZ*MZ) - 4*C56)) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                     2*(MZ*MZ)*C45*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C56)) + 
                  2*(MZ*MZ)*C36*(-2*C45 + 2*C56)*
                   (-(pow((MZ*MZ) + (wZ*wZ),2)*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*
                      (-pow((MZ*MZ) + (wZ*wZ),2) + 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C56))) - 
               4*(C34*C34)*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   (4*C36*C45 - 
                     2*(2*C36 + 2*C45)*C56) + 
                  (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (4*C45*C56 + 
                     2*C36*(2*C45 + 2*C56)) + 
                  (wZ*wZ)*(-16*(C36*C36)*(C45*C45) + 
                     16*(C36*C36)*(C56*C56) + 
                     16*(C45*C45)*(C56*C56) + 
                     32*(C56*C56)*C36*C45 + 
                     4*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45)*C56 + 
                     (MZ*MZ)*
                      (-4*(C56*C56)*(2*C36 + 2*C45) + 
                        4*C36*C45*
                         (2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                         20*C36*C45)*C56))))) + 
         A2ZAR*(A2ZZR*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C45*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56)) - 
               2*C34*(2*(MZ*MZ)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*C45*C56) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   C56*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C45*
                      C56 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 16*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45*C56 - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     12*C45*C56) + 
                  2*C36*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C56*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56)) + 
                     2*(MZ*MZ)*C45*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        32*(C56*C56) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C56)))) + 
            A2ZZI*MZ*(8*((MZ*MZ) + (wZ*wZ))*C36*C45*
                C56*(((MZ*MZ) - 2*C36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   ((MZ*MZ) - 2*C36 - 2*C45 + 2*C56)) + 
               2*C34*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   C45*C56*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*(-(MZ*MZ) + (wZ*wZ) + 2*C56)) + 
                  2*(MZ*MZ)*C36*(-2*C45 + 2*C56)*
                   (pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) + 
                     2*C45*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C56)) + 
                  4*(C36*C36)*
                   (4*(C45*C45)*
                      (pow(-(MZ*MZ) + 2*C56,2) + 
                        (wZ*wZ)*((MZ*MZ) - 4*C56)) - 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C56) - 
                     2*(MZ*MZ)*C45*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C56))) + 
               4*(C34*C34)*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   (4*C36*C45 - 
                     2*(2*C36 + 2*C45)*C56) + 
                  (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (4*C45*C56 + 
                     2*C36*(2*C45 + 2*C56)) + 
                  (wZ*wZ)*(-16*(C36*C36)*(C45*C45) + 
                     16*(C36*C36)*(C56*C56) + 
                     16*(C45*C45)*(C56*C56) + 
                     32*(C56*C56)*C36*C45 + 
                     4*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45)*C56 + 
                     (MZ*MZ)*
                      (-4*(C56*C56)*(2*C36 + 2*C45) + 
                        4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                          20*C36*C45)*C56)))))) + 
      el*MZ*(-E3456)*((gL*gL*gL) - (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(A2ZAI*
          (A2ZZI*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C34*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56) - 
               2*C45*(4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 16*(MZ*MZ)*C36) + 
                     4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C36*
                      C34) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   C34*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(MZ*MZ)*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*C36*C34)*
                   C56) + 
               4*(C45*C45)*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C36*C34 - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     12*C36*C34) + 
                  2*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C36*C36) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36))*(C34*C34) + 
                     2*(MZ*MZ)*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        32*(C36*C36) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C36)*C34)*
                   C56)) + 
            A2ZZR*MZ*(2*C45*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-(MZ*MZ) + (wZ*wZ) + 2*C36)*C34) 
+ 4*(C56*C56)*(-4*(C34*C34)*
                      (pow(-(MZ*MZ) + 2*C36,2) + 
                        (wZ*wZ)*((MZ*MZ) - 4*C36)) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                     2*(MZ*MZ)*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C36)*C34) 
+ 2*(MZ*MZ)*(2*C36 - 2*C34)*
                   (-(pow((MZ*MZ) + (wZ*wZ),2)*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-pow((MZ*MZ) + (wZ*wZ),2) + 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C36)*C34)*
                   C56) + 
               8*((MZ*MZ) + (wZ*wZ))*C36*C34*C56*
                ((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56)) 
- 4*(C45*C45)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (4*C36*C34 + 
                     2*(2*C36 + 2*C34)*C56) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   (4*C34*C56 - 
                     2*C36*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(16*(C36*C36)*(C34*C34) + 
                     16*(C36*C36)*(C56*C56) - 
                     16*(C34*C34)*(C56*C56) + 
                     32*(C36*C36)*C34*C56 + 
                     4*(MZ*MZ*MZ*MZ)*C36*(2*C34 + 2*C56) + 
                     (MZ*MZ)*
                      (-4*(C36*C36)*(2*C34 + 2*C56) + 
                        4*C34*C56*
                         (2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          20*C34*C56)))))) + 
         A2ZAR*(A2ZZR*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C34*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56) - 
               2*C45*(4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 16*(MZ*MZ)*C36) + 
                     4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C36*
                      C34) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(MZ*MZ)*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*C36*C34)*
                   C56) + 
               4*(C45*C45)*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C36*C34 - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     12*C36*C34) + 
                  2*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C36*C36) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36))*(C34*C34) + 
                     2*(MZ*MZ)*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        32*(C36*C36) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C36)*C34)*
                   C56)) + 
            A2ZZI*MZ*(8*((MZ*MZ) + (wZ*wZ))*C36*C34*
                (((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   ((MZ*MZ) + 2*C36 - 2*C34 - 2*C56))*
                C56 + 2*C45*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-(MZ*MZ) + (wZ*wZ) + 2*C36)*C34) + 
                  4*(C56*C56)*
                   (4*(C34*C34)*
                      (pow(-(MZ*MZ) + 2*C36,2) + 
                        (wZ*wZ)*((MZ*MZ) - 4*C36)) - 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C36) - 
                     2*(MZ*MZ)*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C36)*C34) 
+ 2*(MZ*MZ)*(2*C36 - 2*C34)*
                   (pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36) + 
                     2*(pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C36)*C34)*
                   C56) + 
               4*(C45*C45)*
                ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (4*C36*C34 + 
                     2*(2*C36 + 2*C34)*C56) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   (4*C34*C56 - 
                     2*C36*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(16*(C36*C36)*(C34*C34) + 
                     16*(C36*C36)*(C56*C56) - 
                     16*(C34*C34)*(C56*C56) + 
                     32*(C36*C36)*C34*C56 + 
                     4*(MZ*MZ*MZ*MZ)*C36*(2*C34 + 2*C56) + 
                     (MZ*MZ)*
                      (-4*(C36*C36)*(2*C34 + 2*C56) + 
                        4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          20*C34*C56))))))) + 
      el*((gL*gL*gL) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(-2*(C36*C36)*(C45*C45) - 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 + 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 - C46,2) - 4*C36*C45)*
          C56)*(A2ZAI*(-(A2ZZR*MZ*wZ*
               (8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C45*
                  C56*((MZ*MZ)*
                     ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                    4*C45*C56 + 
                    2*C36*(-2*C45 + 2*C56)) + 
                 2*C34*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     C45*C56*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                       2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                    4*(C36*C36)*
                     (4*(C45*C45)*
                        (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                         4*(C56*C56)) + 
                       4*(MZ*MZ)*C45*
                        (5*(MZ*MZ) + (wZ*wZ) - 8*C56)*
                        C56 + 
                       2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                        (-2*(MZ*MZ) + 2*C56)) + 
                    2*(MZ*MZ)*C36*
                     (2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                        C56 + 
                       8*(C45*C45)*
                        (5*(MZ*MZ) + (wZ*wZ) - 8*C56)*C56 
+ 2*C45*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                         4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                         16*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56))) 
+ 4*(C34*C34)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*C45*C56 
+ 4*(C36*C36)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    2*C36*
                     (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        (C56*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       2*C45*
                        (-2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                          2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C56))
))) + A2ZZI*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C45*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56))*
                C56 - 2*(MZ*MZ)*C34*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*C56*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*(-(MZ*MZ) + (wZ*wZ) + 2*C56)) + 
                  2*C36*
                   (-2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                         (C56*C56) - 
                        16*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                     4*(C45*C45)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        8*(3*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        2*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*C56)
) + 4*(C36*C36)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-20*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C56*C56) + 
                        4*(C45*C45)*((MZ*MZ) + 4*C56) + 
                        2*C45*
                         (-2*(MZ*MZ*MZ*MZ) - 8*(C56*C56) + 
                          6*(MZ*MZ)*C56)))) + 
               4*(C34*C34)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56))*C45*
                   C56 + 
                  4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ)*(2*C45 + 2*C56)*
                      (-(MZ*MZ) + 2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-16*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56))) + 
                  2*(MZ*MZ)*C36*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-2*C45 + 2*C56) + 
                     ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56)*
                      (-20*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ)*C56 + 
                        8*(Sqrt2*SqrtC45 - 
                         Sqrt2*SqrtC56)*
                         (Sqrt2*SqrtC45 + 
                         Sqrt2*SqrtC56)*C45*C56 
- (MZ*MZ)*(4*(C45*C45) + 4*(C56*C56) + 
                          12*C45*C56)))))) + 
         A2ZAR*(A2ZZI*MZ*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C45*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56)) + 
               2*C34*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   C56*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   (4*(C45*C45)*
                      (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C56*C56)) + 
                     4*(MZ*MZ)*C45*
                      (5*(MZ*MZ) + (wZ*wZ) - 8*C56)*C56 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56)) + 
                  2*(MZ*MZ)*C36*
                   (2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*C56 + 
                     8*(C45*C45)*
                      (5*(MZ*MZ) + (wZ*wZ) - 8*C56)*C56 + 
                     2*C45*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        16*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56))) + 
               4*(C34*C34)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45*C56 + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C56*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     2*C45*
                      (-2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C56)))) 
+ A2ZZR*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C45*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56))*
                C56 - 2*(MZ*MZ)*C34*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*C56*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*(-(MZ*MZ) + (wZ*wZ) + 2*C56)) + 
                  2*C36*(-2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                         (C56*C56) - 
                        16*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                     4*(C45*C45)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        8*(3*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        2*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*C56)) 
+ 4*(C36*C36)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-20*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C56*C56) + 
                        4*(C45*C45)*((MZ*MZ) + 4*C56) + 
                        2*C45*
                         (-2*(MZ*MZ*MZ*MZ) - 8*(C56*C56) + 
                          6*(MZ*MZ)*C56)))) + 
               4*(C34*C34)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56))*C45*
                   C56 + 
                  4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ)*(2*C45 + 2*C56)*
                      (-(MZ*MZ) + 2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-16*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56))) + 
                  2*(MZ*MZ)*C36*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-2*C45 + 2*C56) + 
                     ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56)*
                      (-20*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ)*C56 + 
                        8*(Sqrt2*SqrtC45 - 
                          Sqrt2*SqrtC56)*
                         (Sqrt2*SqrtC45 + 
                          Sqrt2*SqrtC56)*C45*C56 
- (MZ*MZ)*(4*(C45*C45) + 4*(C56*C56) + 
                          12*C45*C56)))))))))/1.048576e6;
}

double GetGeneralScalar4e_Part33(LeptonVectors &leptons, double A3ZAI, double A3ZAR, double A3ZZI, double A3ZZR)
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
    (8*el*(gL + gR)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-2*(C36*C36)*(C45*C45) - 
         2*pow(-(C46*C35) + C34*C56,2) + 
         (pow(C46 + C35,2) + pow(C34 + C56,2))*
          C36*C45)*
       ((A3ZAR*A3ZZI - A3ZAI*A3ZZR)*MZ*wZ*(2*C36 + 2*C45) + 
         (A3ZAI*A3ZZI + A3ZAR*A3ZZR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45))) + 
      8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((A3ZAR*A3ZZI - A3ZAI*A3ZZR)*MZ*wZ*(2*C36 + 2*C45) + 
         (A3ZAI*A3ZZI + A3ZAR*A3ZZR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45)))*
       (C34 - C46 + C35 - C56)*
       (-C34 - C46 + C35 + C56) + 
      8*el*(gL + gR)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
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
          (8*C34*C56 - (MZ*MZ)*(2*C34 + 2*C56))) + 
      el*((gL*gL*gL) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + 
         pow(C35,3)*C46 + pow(C46,3)*C35 - 
         (C46*C46)*C34*C56 - 
         (C35*C35)*C34*C56 - 
         2*C34*C46*C35*C56 - 
         C36*C45*(pow(C46 + C35,2) + 
            4*C34*C56))*
       (A3ZAI*(-(A3ZZR*MZ*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  C36*C34*C56*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                    4*C36*C34 + 
                    2*(2*C36 - 2*C34)*C56) + 
                 2*C45*(4*(C56*C56)*
                     (4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                       2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                        (-2*(MZ*MZ) + 2*C36) + 
                       4*(MZ*MZ)*
                        (5*(MZ*MZ) + (wZ*wZ) - 8*C36)*
                        C36*C34) + 
                    4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                     C34*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                       2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                    2*(MZ*MZ)*
                     (2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                        C36 + 
                       8*(C34*C34)*
                        (5*(MZ*MZ) + (wZ*wZ) - 8*C36)*
                        C36 + 
                       2*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        16*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                        C34)*C56) + 
                 4*(C45*C45)*
                  (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*C36*C34 
+ 4*(C56*C56)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       8*(C34*C34)*C36 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34) + 
                    2*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        (C36*C36) + 
                       4*(C34*C34)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                       2*(-2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                         2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C36
)*C34)*C56))) + A3ZZI*
             (-2*(MZ*MZ)*C45*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-(MZ*MZ) + (wZ*wZ) + 2*C36)*C34) 
+ 4*(C56*C56)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 - 2*C34) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C36*C36) + 
                        4*(C34*C34)*((MZ*MZ) + 4*C36) + 
                        2*(-2*(MZ*MZ*MZ*MZ) - 8*(C36*C36) + 
                        6*(MZ*MZ)*C36)*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-20*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(-2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36 - 
                     4*(C34*C34)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        8*(3*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        2*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                         C36) + 
                     2*((MZ*MZ*MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                        (C36*C36) - 
                        16*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34))*C36*
                   C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ)*(2*C36 + 2*C34)*
                      (-(MZ*MZ) + 2*C36 + 2*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-16*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(MZ*MZ)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 - 2*C34) + 
                     ((MZ*MZ) - 2*C36)*
                      ((MZ*MZ) - 2*C34)*
                      (-20*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ)*C36 + 
                        8*(-(Sqrt2*SqrtC36) + 
                        Sqrt2*SqrtC34)*
                         (Sqrt2*SqrtC36 + 
                        Sqrt2*SqrtC34)*C36*
                         C34 - 
                        (MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) + 
                         12*C36*C34)))*C56) + 
               8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                C56*((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56)))
) + A3ZAR*(A3ZZI*MZ*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C34*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56) + 
               2*C45*(4*(C56*C56)*
                   (4*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C36*C36))*(C34*C34) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 8*C36)*
                      C36*C34) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(MZ*MZ)*
                   (2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*C36 + 
                     8*(C34*C34)*
                      (5*(MZ*MZ) + (wZ*wZ) - 8*C36)*C36 
+ 2*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        16*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C36*C34 + 
                  4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     8*(C34*C34)*C36 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34) + 
                  2*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C36*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36) + 
                     2*(-2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56)) + 
            A3ZZR*(-2*(MZ*MZ)*C45*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-(MZ*MZ) + (wZ*wZ) + 2*C36)*C34) + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 - 2*C34) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C36*C36) + 
                        4*(C34*C34)*((MZ*MZ) + 4*C36) + 
                        2*(-2*(MZ*MZ*MZ*MZ) - 8*(C36*C36) + 
                         6*(MZ*MZ)*C36)*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-20*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(-2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C36 - 
                     4*(C34*C34)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        8*(3*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        2*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*C36
) + 2*((MZ*MZ*MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                         (C36*C36) - 
                        16*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36)*
                      C34)*C56) + 
               4*(C45*C45)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34))*C36*
                   C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*(wZ*wZ)*(2*C36 + 2*C34)*
                      (-(MZ*MZ) + 2*C36 + 2*C34) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C34)*
                      (-16*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34))) + 
                  2*(MZ*MZ)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (2*C36 - 2*C34) + 
                     ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                      (-20*C36*C34 + 
                        (MZ*MZ)*(2*C36 + 2*C34)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ)*C36 + 
                        8*(-(Sqrt2*SqrtC36) + 
                         Sqrt2*SqrtC34)*
                         (Sqrt2*SqrtC36 + 
                         Sqrt2*SqrtC34)*C36*
                         C34 - 
                        (MZ*MZ)*
                         (4*(C36*C36) + 4*(C34*C34) + 
                         12*C36*C34)))*C56) + 
               8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                C56*((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56))))
) + el*MZ*E3456*((gL*gL*gL) - (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (A3ZAI*(A3ZZI*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C45*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56)) - 
               2*C34*(2*(MZ*MZ)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*C45*C56) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   C56*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C45*
                      C56 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 16*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45*C56 - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     12*C45*C56) + 
                  2*C36*
                   (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C56*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56)) + 
                     2*(MZ*MZ)*C45*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        32*(C56*C56) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C56)))) + 
            A3ZZR*MZ*(8*((MZ*MZ) + (wZ*wZ))*C36*C45*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56)
)*C56 + 2*C34*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   C56*(-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*(-(MZ*MZ) + (wZ*wZ) + 2*C56)) 
+ 4*(C36*C36)*(-4*(C45*C45)*
                      (pow(-(MZ*MZ) + 2*C56,2) + 
                        (wZ*wZ)*((MZ*MZ) - 4*C56)) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C56) + 
                     2*(MZ*MZ)*C45*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C56)) + 
                  2*(MZ*MZ)*C36*(-2*C45 + 2*C56)*
                   (-(pow((MZ*MZ) + (wZ*wZ),2)*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*
                      (-pow((MZ*MZ) + (wZ*wZ),2) + 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C56))) - 
               4*(C34*C34)*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   (4*C36*C45 - 
                     2*(2*C36 + 2*C45)*C56) + 
                  (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (4*C45*C56 + 
                     2*C36*(2*C45 + 2*C56)) + 
                  (wZ*wZ)*(-16*(C36*C36)*(C45*C45) + 
                     16*(C36*C36)*(C56*C56) + 
                     16*(C45*C45)*(C56*C56) + 
                     32*(C56*C56)*C36*C45 + 
                     4*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45)*C56 + 
                     (MZ*MZ)*
                      (-4*(C56*C56)*(2*C36 + 2*C45) + 
                        4*C36*C45*
                         (2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                         20*C36*C45)*C56))))) + 
         A3ZAR*(A3ZZR*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C45*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56)) - 
               2*C34*(2*(MZ*MZ)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C36*
                   (-((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*C45*C56) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   C56*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   (4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C45*
                      C56 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56) - 16*(MZ*MZ)*C56))) + 
               4*(C34*C34)*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45*C56 - 
                  4*(C36*C36)*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     12*C45*C56) + 
                  2*C36*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C56*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C56*C56)) + 
                     2*(MZ*MZ)*C45*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        32*(C56*C56) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C56)))) + 
            A3ZZI*MZ*(8*((MZ*MZ) + (wZ*wZ))*C36*C45*
                C56*(((MZ*MZ) - 2*C36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   ((MZ*MZ) - 2*C36 - 2*C45 + 2*C56)) + 
               2*C34*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   C45*C56*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*(-(MZ*MZ) + (wZ*wZ) + 2*C56)) + 
                  2*(MZ*MZ)*C36*(-2*C45 + 2*C56)*
                   (pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56) + 
                     2*C45*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C56)) + 
                  4*(C36*C36)*
                   (4*(C45*C45)*
                      (pow(-(MZ*MZ) + 2*C56,2) + 
                        (wZ*wZ)*((MZ*MZ) - 4*C56)) - 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C56) - 
                     2*(MZ*MZ)*C45*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C56))) + 
               4*(C34*C34)*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   (4*C36*C45 - 
                     2*(2*C36 + 2*C45)*C56) + 
                  (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (4*C45*C56 + 
                     2*C36*(2*C45 + 2*C56)) + 
                  (wZ*wZ)*(-16*(C36*C36)*(C45*C45) + 
                     16*(C36*C36)*(C56*C56) + 
                     16*(C45*C45)*(C56*C56) + 
                     32*(C56*C56)*C36*C45 + 
                     4*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45)*C56 + 
                     (MZ*MZ)*
                      (-4*(C56*C56)*(2*C36 + 2*C45) + 
                        4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                          20*C36*C45)*C56)))))) + 
      el*MZ*(-E3456)*((gL*gL*gL) - (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(A3ZAI*
          (A3ZZI*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C34*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56) - 
               2*C45*(4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 16*(MZ*MZ)*C36) + 
                     4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C36*
                      C34) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   C34*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(MZ*MZ)*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*C36*C34)*
                   C56) + 
               4*(C45*C45)*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C36*C34 - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     12*C36*C34) + 
                  2*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C36*C36) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36))*(C34*C34) + 
                     2*(MZ*MZ)*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        32*(C36*C36) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C36)*C34)*
                   C56)) + 
            A3ZZR*MZ*(2*C45*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-(MZ*MZ) + (wZ*wZ) + 2*C36)*C34) 
+ 4*(C56*C56)*(-4*(C34*C34)*
                      (pow(-(MZ*MZ) + 2*C36,2) + 
                        (wZ*wZ)*((MZ*MZ) - 4*C36)) + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C36) + 
                     2*(MZ*MZ)*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C36)*C34) 
+ 2*(MZ*MZ)*(2*C36 - 2*C34)*
                   (-(pow((MZ*MZ) + (wZ*wZ),2)*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-pow((MZ*MZ) + (wZ*wZ),2) + 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C36)*C34)*
                   C56) + 
               8*((MZ*MZ) + (wZ*wZ))*C36*C34*C56*
                ((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56)) 
- 4*(C45*C45)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (4*C36*C34 + 
                     2*(2*C36 + 2*C34)*C56) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   (4*C34*C56 - 
                     2*C36*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(16*(C36*C36)*(C34*C34) + 
                     16*(C36*C36)*(C56*C56) - 
                     16*(C34*C34)*(C56*C56) + 
                     32*(C36*C36)*C34*C56 + 
                     4*(MZ*MZ*MZ*MZ)*C36*(2*C34 + 2*C56) + 
                     (MZ*MZ)*
                      (-4*(C36*C36)*(2*C34 + 2*C56) + 
                        4*C34*C56*
                         (2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          20*C34*C56)))))) + 
         A3ZAR*(A3ZZR*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C34*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56) - 
               2*C45*(4*(C56*C56)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-2*(MZ*MZ) + 2*C36) + 
                     4*(C34*C34)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36) - 16*(MZ*MZ)*C36) + 
                     4*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C36*
                      C34) + 
                  4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   C34*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                  2*(MZ*MZ)*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*
                   (-((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*C36*C34)*
                   C56) + 
               4*(C45*C45)*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C36*C34 - 
                  4*(-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*(C56*C56)*
                   (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                     12*C36*C34) + 
                  2*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C36*C36) + 
                     4*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        12*(C36*C36))*(C34*C34) + 
                     2*(MZ*MZ)*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        32*(C36*C36) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C36)*C34)*
                   C56)) + 
            A3ZZI*MZ*(8*((MZ*MZ) + (wZ*wZ))*C36*C34*
                (((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   ((MZ*MZ) + 2*C36 - 2*C34 - 2*C56))*
                C56 + 2*C45*
                (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C34*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC36)*
                        (MZ + Sqrt2*SqrtC36)) + 
                     2*(-(MZ*MZ) + (wZ*wZ) + 2*C36)*C34) + 
                  4*(C56*C56)*
                   (4*(C34*C34)*
                      (pow(-(MZ*MZ) + 2*C36,2) + 
                        (wZ*wZ)*((MZ*MZ) - 4*C36)) - 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                      (-(MZ*MZ) + (wZ*wZ) + 2*C36) - 
                     2*(MZ*MZ)*
                      (pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C36)*C34) 
+ 2*(MZ*MZ)*(2*C36 - 2*C34)*
                   (pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36) + 
                     2*(pow((MZ*MZ) + (wZ*wZ),2) - 
                        2*((MZ*MZ) + 5*(wZ*wZ))*C36)*C34)*
                   C56) + 
               4*(C45*C45)*
                ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (4*C36*C34 + 
                     2*(2*C36 + 2*C34)*C56) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   (4*C34*C56 - 
                     2*C36*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(16*(C36*C36)*(C34*C34) + 
                     16*(C36*C36)*(C56*C56) - 
                     16*(C34*C34)*(C56*C56) + 
                     32*(C36*C36)*C34*C56 + 
                     4*(MZ*MZ*MZ*MZ)*C36*(2*C34 + 2*C56) + 
                     (MZ*MZ)*
                      (-4*(C36*C36)*(2*C34 + 2*C56) + 
                        4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          20*C34*C56))))))) + 
      el*((gL*gL*gL) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*(2*(C36*C36)*(C45*C45) + 
         2*(C34*C34)*(C56*C56) + pow(C46,3)*C35 - 
         (C35*C35)*C36*C45 - 
         (C46*C46)*C36*C45 + 
         pow(C35,3)*C46 - 
         2*C35*C36*C45*C46 - 
         C34*(pow(C35 + C46,2) + 4*C36*C45)*
          C56)*(A3ZAI*(-(A3ZZR*MZ*wZ*
               (8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C45*
                  C56*((MZ*MZ)*
                     ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                    4*C45*C56 + 
                    2*C36*(-2*C45 + 2*C56)) + 
                 2*C34*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     C45*C56*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                       2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                    4*(C36*C36)*
                     (4*(C45*C45)*
                        (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                         4*(C56*C56)) + 
                       4*(MZ*MZ)*C45*
                        (5*(MZ*MZ) + (wZ*wZ) - 8*C56)*
                        C56 + 
                       2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                        (-2*(MZ*MZ) + 2*C56)) + 
                    2*(MZ*MZ)*C36*
                     (2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                        C56 + 
                       8*(C45*C45)*
                        (5*(MZ*MZ) + (wZ*wZ) - 8*C56)*C56 
+ 2*C45*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                         4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                         16*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56))) 
+ 4*(C34*C34)*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*C45*C56 
+ 4*(C36*C36)*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                       8*(C45*C45)*C56 + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                    2*C36*
                     (-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                        (C56*C56) + 
                       4*(C45*C45)*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                       2*C45*
                        (-2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                          2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C56))
))) + A3ZZI*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C45*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56))*
                C56 - 2*(MZ*MZ)*C34*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*C56*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*(-(MZ*MZ) + (wZ*wZ) + 2*C56)) + 
                  2*C36*
                   (-2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                         (C56*C56) - 
                        16*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                     4*(C45*C45)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        8*(3*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        2*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*C56)
) + 4*(C36*C36)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-20*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C56*C56) + 
                        4*(C45*C45)*((MZ*MZ) + 4*C56) + 
                        2*C45*
                         (-2*(MZ*MZ*MZ*MZ) - 8*(C56*C56) + 
                          6*(MZ*MZ)*C56)))) + 
               4*(C34*C34)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56))*C45*
                   C56 + 
                  4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ)*(2*C45 + 2*C56)*
                      (-(MZ*MZ) + 2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-16*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56))) + 
                  2*(MZ*MZ)*C36*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-2*C45 + 2*C56) + 
                     ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56)*
                      (-20*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ)*C56 + 
                        8*(Sqrt2*SqrtC45 - 
                         Sqrt2*SqrtC56)*
                         (Sqrt2*SqrtC45 + 
                         Sqrt2*SqrtC56)*C45*C56 
- (MZ*MZ)*(4*(C45*C45) + 4*(C56*C56) + 
                          12*C45*C56)))))) + 
         A3ZAR*(A3ZZI*MZ*wZ*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                C45*C56*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56)) + 
               2*C34*(4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                   C56*((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   (4*(C45*C45)*
                      (-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
                        4*(C56*C56)) + 
                     4*(MZ*MZ)*C45*
                      (5*(MZ*MZ) + (wZ*wZ) - 8*C56)*C56 + 
                     2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                      (-2*(MZ*MZ) + 2*C56)) + 
                  2*(MZ*MZ)*C36*
                   (2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*C56 + 
                     8*(C45*C45)*
                      (5*(MZ*MZ) + (wZ*wZ) - 8*C56)*C56 + 
                     2*C45*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        16*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56))) + 
               4*(C34*C34)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45*C56 + 
                  4*(C36*C36)*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 + 
                     8*(C45*C45)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)) + 
                  2*C36*(-4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                      (C56*C56) + 
                     4*(C45*C45)*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56) + 
                     2*C45*
                      (-2*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                        2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ))*C56)))) 
+ A3ZZR*(8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*C45*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56))*
                C56 - 2*(MZ*MZ)*C34*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*C56*
                   (-(((MZ*MZ) + (wZ*wZ))*
                        (-MZ + Sqrt2*SqrtC56)*
                        (MZ + Sqrt2*SqrtC56)) + 
                     2*C45*(-(MZ*MZ) + (wZ*wZ) + 2*C56)) + 
                  2*C36*(-2*(MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C56 + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*
                         (C56*C56) - 
                        16*(MZ*MZ*MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                     4*(C45*C45)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        8*(3*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        2*(7*(MZ*MZ*MZ*MZ) + 3*(MZ*MZ)*(wZ*wZ))*C56)) 
+ 4*(C36*C36)*((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-20*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ)*(C56*C56) + 
                        4*(C45*C45)*((MZ*MZ) + 4*C56) + 
                        2*C45*
                         (-2*(MZ*MZ*MZ*MZ) - 8*(C56*C56) + 
                          6*(MZ*MZ)*C56)))) + 
               4*(C34*C34)*
                (4*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((MZ*MZ)*(wZ*wZ) + 
                     (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56))*C45*
                   C56 + 
                  4*(C36*C36)*
                   ((MZ*MZ)*(wZ*wZ)*(2*C45 + 2*C56)*
                      (-(MZ*MZ) + 2*C45 + 2*C56) + 
                     (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C45)*
                      (-16*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56))) + 
                  2*(MZ*MZ)*C36*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*(-2*C45 + 2*C56) + 
                     ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56)*
                      (-20*C45*C56 + 
                        (MZ*MZ)*(2*C45 + 2*C56)) + 
                     (wZ*wZ)*
                      (4*(MZ*MZ*MZ*MZ)*C56 + 
                        8*(Sqrt2*SqrtC45 - 
                          Sqrt2*SqrtC56)*
                         (Sqrt2*SqrtC45 + 
                          Sqrt2*SqrtC56)*C45*C56 
- (MZ*MZ)*(4*(C45*C45) + 4*(C56*C56) + 
                          12*C45*C56)))))))))/1.048576e6;
}

double GetGeneralScalar4e_Part34(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A2ZAI, double A2ZAR)
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
    (-2*el*(gL - gR)*(-E3456)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       ((A1ZZI*A2ZAI + A1ZZR*A2ZAR)*MZ*wZ*
          (2*((gL*gL) + (gR*gR))*C36 + 
            2*((gL+gR)*(gL+gR))*C45) + 
         (A1ZZR*A2ZAI - A1ZZI*A2ZAR)*
          (8*(gL*gR + (gL*gL) + (gR*gR))*C36*C45 - 
            (MZ*MZ)*(2*((gL*gL) + (gR*gR))*C36 + 
               2*((gL+gR)*(gL+gR))*C45)))*
       (C34 - C46 + C35 - C56) - 
      2*el*(gL - gR)*(-E3456)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       ((A1ZZI*A2ZAI + A1ZZR*A2ZAR)*MZ*wZ*
          (2*((gL+gR)*(gL+gR))*C36 + 
            2*((gL*gL) + (gR*gR))*C45) + 
         (A1ZZR*A2ZAI - A1ZZI*A2ZAR)*
          (8*(gL*gR + (gL*gL) + (gR*gR))*C36*C45 - 
            (MZ*MZ)*(2*((gL+gR)*(gL+gR))*C36 + 
               2*((gL*gL) + (gR*gR))*C45)))*
       (-C34 - C46 + C35 + C56) + 
      2*el*(gL + gR)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-((A1ZZR*A2ZAI - A1ZZI*A2ZAR)*MZ*wZ*(2*C36 + 2*C45)) + 
         (A1ZZI*A2ZAI + A1ZZR*A2ZAR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45)))*
       (-((C35*C35)*C46) + 
         C36*C45*(C34 - C46 + C56) + 
         C34*C56*(C34 + C46 + C56) + 
         C35*(-(C46*(C34 + C46)) - 
            C36*C45 + (C34 - C46)*C56)) + 
      2*el*(gL + gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-((A1ZZR*A2ZAI - A1ZZI*A2ZAR)*MZ*wZ*(2*C36 + 2*C45)) + 
         (A1ZZI*A2ZAI + A1ZZR*A2ZAR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45)))*
       (-((C35*C35)*C46) - 
         C34*C56*(C34 - C46 + C56) - 
         C36*C45*(C34 + C46 + C56) + 
         C35*((C34 - C46)*C46 - 
            C36*C45 + (C34 + C46)*C56)) + 
      2*el*(gL + gR)*((gL*gL) + (gR*gR))*(MZ*MZ)*(1/(vh*vh))*
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
          (2*((gL*gL) + (gR*gR))*C34 + 
            2*((gL+gR)*(gL+gR))*C56) + 
         (A1ZZR*A2ZAI - A1ZZI*A2ZAR)*
          (8*(gL*gR + (gL*gL) + (gR*gR))*C34*C56 - 
            (MZ*MZ)*(2*((gL*gL) + (gR*gR))*C34 + 
               2*((gL+gR)*(gL+gR))*C56))) - 
      4*el*E3456*((gL*gL*gL) - (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C45)*(-C35 + C46)*
       (A1ZZR*(A2ZAR*MZ*wZ*(2*(MZ*MZ)*C36*
                ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                  4*(C45*C45)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56)) + 
               4*(C36*C36)*
                (2*(MZ*MZ)*C45*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C56) + 
                  8*(C45*C45)*(-2*(MZ*MZ) + 2*C56)) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 - 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56)))) + 
            A2ZAI*(2*C34*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C36*C36) + 
                       2*C36*((MZ*MZ) - 2*C56) + 
                       2*C45*((MZ*MZ) + 2*C45 - 2*C56)
)) + (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (wZ*wZ)*(-32*(C36*C36)*(C45*C45) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*C36*C45*(2*C36 + 2*C45)*
                      C56 + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56) + 
                     (MZ*MZ)*
                      (4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                         16*C36*C45)*C56))))) + 
         A1ZZI*(A2ZAI*MZ*wZ*(2*(MZ*MZ)*C36*
                ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                  4*(C45*C45)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56)) + 
               4*(C36*C36)*
                (2*(MZ*MZ)*C45*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C56) + 
                  8*(C45*C45)*(-2*(MZ*MZ) + 2*C56)) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 - 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56)))) - 
            A2ZAR*(2*C34*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C36*C36) + 
                       2*C36*((MZ*MZ) - 2*C56) + 
                       2*C45*((MZ*MZ) + 2*C45 - 2*C56))
) + (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (wZ*wZ)*(-32*(C36*C36)*(C45*C45) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*C36*C45*(2*C36 + 2*C45)*
                      C56 + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56) + 
                     (MZ*MZ)*
                      (4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                          16*C36*C45)*C56)))))) - 
      4*el*((gL*gL*gL) + (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C45)*(C35 + C46)*
       (C36*C45 + C35*C46 - C34*C56)*
       (A1ZZI*(A2ZAR*MZ*wZ*(2*(MZ*MZ)*C36*
                ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                  4*(C45*C45)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56)) + 
               4*(C36*C36)*
                (2*(MZ*MZ)*C45*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C56) + 
                  8*(C45*C45)*(-2*(MZ*MZ) + 2*C56)) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 - 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56)))) + 
            A2ZAI*(2*C34*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C36*C36) + 
                       2*C36*((MZ*MZ) - 2*C56) + 
                       2*C45*((MZ*MZ) + 2*C45 - 2*C56)
)) + (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (wZ*wZ)*(-32*(C36*C36)*(C45*C45) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*C36*C45*(2*C36 + 2*C45)*
                      C56 + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56) + 
                     (MZ*MZ)*
                      (4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                         16*C36*C45)*C56))))) + 
         A1ZZR*(-(A2ZAI*MZ*wZ*(2*(MZ*MZ)*C36*
                  ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) - 
                    8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                    4*(C45*C45)*
                     (5*(MZ*MZ) + (wZ*wZ) - 4*C56)) + 
                 4*(C36*C36)*
                  (2*(MZ*MZ)*C45*
                     (5*(MZ*MZ) + (wZ*wZ) - 4*C56) + 
                    (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-2*(MZ*MZ) + 2*C56) + 
                    8*(C45*C45)*(-2*(MZ*MZ) + 2*C56)) + 
                 2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                    2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                 2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*C45 - 
                    2*C36*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                       16*(MZ*MZ)*C45*C56 + 
                       4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                    4*(C36*C36)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                       8*(C45*C45) - 
                       2*C45*(2*(MZ*MZ) + 2*C56))))) + 
            A2ZAR*(2*C34*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C36*C36) + 
                       2*C36*((MZ*MZ) - 2*C56) + 
                       2*C45*((MZ*MZ) + 2*C45 - 2*C56))
) + (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (wZ*wZ)*(-32*(C36*C36)*(C45*C45) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*C36*C45*(2*C36 + 2*C45)*
                      C56 + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56) + 
                     (MZ*MZ)*
                      (4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                          16*C36*C45)*C56)))))) - 
      4*el*(-E3456)*((gL*gL*gL) - (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*(C46 - C35)*
       (A1ZZR*(A2ZAR*MZ*wZ*(4*(C56*C56)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C36) + 
                  8*(C34*C34)*(-2*(MZ*MZ) + 2*C36) + 
                  2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 4*C36)*
                   C34) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34) + 
               2*(MZ*MZ)*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                  4*(C34*C34)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C36) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34)*
                C56 + 2*C45*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) - 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56)) + 
            A2ZAI*(2*C45*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C56*C56) + 
                       2*C34*
                        ((MZ*MZ) - 2*C36 + 2*C34) + 
                       2*((MZ*MZ) - 2*C36)*C56)) + 
                  (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(-32*(C34*C34)*(C56*C56) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) + 
                     8*C36*C34*C56*
                      (2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)) + 
                     (MZ*MZ)*
                      (4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          16*C34*C56)))))) + 
         A1ZZI*(A2ZAI*MZ*wZ*(4*(C56*C56)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C36) + 
                  8*(C34*C34)*(-2*(MZ*MZ) + 2*C36) + 
                  2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 4*C36)*
                   C34) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34) + 
               2*(MZ*MZ)*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                  4*(C34*C34)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C36) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34)*C56 
+ 2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) - 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56)) - 
            A2ZAR*(2*C45*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C56*C56) + 
                       2*C34*
                        ((MZ*MZ) - 2*C36 + 2*C34) + 
                       2*((MZ*MZ) - 2*C36)*C56)) + 
                  (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(-32*(C34*C34)*(C56*C56) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) + 
                     8*C36*C34*C56*
                      (2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)) + 
                     (MZ*MZ)*
                      (4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          16*C34*C56))))))) - 
      4*el*((gL*gL*gL) + (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*(C46 + C35)*
       (C46*C35 - C36*C45 + C34*C56)*
       (A1ZZI*(A2ZAR*MZ*wZ*(4*(C56*C56)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C36) + 
                  8*(C34*C34)*(-2*(MZ*MZ) + 2*C36) + 
                  2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 4*C36)*
                   C34) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34) + 
               2*(MZ*MZ)*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                  4*(C34*C34)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C36) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34)*C56 
+ 2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) - 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56)) + 
            A2ZAI*(2*C45*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C56*C56) + 
                       2*C34*
                        ((MZ*MZ) - 2*C36 + 2*C34) + 
                       2*((MZ*MZ) - 2*C36)*C56)) + 
                  (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(-32*(C34*C34)*(C56*C56) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) + 
                     8*C36*C34*C56*
                      (2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)) + 
                     (MZ*MZ)*
                      (4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          16*C34*C56)))))) + 
         A1ZZR*(-(A2ZAI*MZ*wZ*(4*(C56*C56)*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-2*(MZ*MZ) + 2*C36) + 
                    8*(C34*C34)*(-2*(MZ*MZ) + 2*C36) + 
                    2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 4*C36)*
                     C34) + 
                 2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                    2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                 2*(MZ*MZ)*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                    4*(C34*C34)*
                     (5*(MZ*MZ) + (wZ*wZ) - 4*C36) - 
                    8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34)*
                  C56 + 2*C45*
                  (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*C34 + 
                    4*(C56*C56)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                       8*(C34*C34) - 
                       2*(2*(MZ*MZ) + 2*C36)*C34) - 
                    2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                       16*(MZ*MZ)*C36*C34)*C56))) + 
            A2ZAR*(2*C45*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C56*C56) + 
                       2*C34*
                        ((MZ*MZ) - 2*C36 + 2*C34) + 
                       2*((MZ*MZ) - 2*C36)*C56)) + 
                  (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(-32*(C34*C34)*(C56*C56) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) + 
                     8*C36*C34*C56*
                      (2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)) + 
                     (MZ*MZ)*
                      (4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          16*C34*C56)))))))))/524288.;
}

double GetGeneralScalar4e_Part35(LeptonVectors &leptons, double A2ZAI, double A2ZAR, double A2ZZI, double A2ZZR, double A3ZAI, double A3ZAR, double A3ZZI, double A3ZZR)
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
    (8*el*(gL + gR)*(-E3456)*((gL-gR)*(gL-gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((-(A2ZZR*A3ZAI) + A2ZZI*A3ZAR + A2ZAR*A3ZZI - A2ZAI*A3ZZR)*MZ*wZ*
          (2*C36 + 2*C45) + 
         (A2ZZI*A3ZAI + A2ZZR*A3ZAR + A2ZAI*A3ZZI + A2ZAR*A3ZZR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45))) - 
      4*el*(gL - gR)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       ((C34*C34) - (C46*C46) + (C35*C35) - 
         (C56*C56))*(-4*A2ZAR*A3ZZI*gL*gR*(MZ*MZ)*C36 + 
         4*A2ZAI*A3ZZR*gL*gR*(MZ*MZ)*C36 - 
         2*A2ZAR*A3ZZI*(gL*gL)*(MZ*MZ)*C36 + 
         2*A2ZAI*A3ZZR*(gL*gL)*(MZ*MZ)*C36 - 
         2*A2ZAR*A3ZZI*(gR*gR)*(MZ*MZ)*C36 + 
         2*A2ZAI*A3ZZR*(gR*gR)*(MZ*MZ)*C36 - 
         2*A2ZAR*A3ZZI*(gL*gL)*(MZ*MZ)*C45 + 
         2*A2ZAI*A3ZZR*(gL*gL)*(MZ*MZ)*C45 - 
         2*A2ZAR*A3ZZI*(gR*gR)*(MZ*MZ)*C45 + 
         2*A2ZAI*A3ZZR*(gR*gR)*(MZ*MZ)*C45 + 
         8*A2ZAR*A3ZZI*gL*gR*C36*C45 - 
         8*A2ZAI*A3ZZR*gL*gR*C36*C45 + 
         8*A2ZAR*A3ZZI*(gL*gL)*C36*C45 - 
         8*A2ZAI*A3ZZR*(gL*gL)*C36*C45 + 
         8*A2ZAR*A3ZZI*(gR*gR)*C36*C45 - 
         8*A2ZAI*A3ZZR*(gR*gR)*C36*C45 + 
         A2ZZI*A3ZAI*MZ*wZ*(2*((gL+gR)*(gL+gR))*C36 + 
            2*((gL*gL) + (gR*gR))*C45) + 
         A2ZZR*A3ZAR*MZ*wZ*(2*((gL+gR)*(gL+gR))*C36 + 
            2*((gL*gL) + (gR*gR))*C45) - 
         (A2ZAI*A3ZZI + A2ZAR*A3ZZR)*MZ*wZ*
          (2*((gL+gR)*(gL+gR))*C36 + 
            2*((gL*gL) + (gR*gR))*C45) + 
         A2ZZR*A3ZAI*(8*(gL*gR + (gL*gL) + (gR*gR))*C36*
             C45 - (MZ*MZ)*
             (2*((gL+gR)*(gL+gR))*C36 + 
               2*((gL*gL) + (gR*gR))*C45)) + 
         A2ZZI*A3ZAR*(-8*(gL*gR + (gL*gL) + (gR*gR))*C36*
             C45 + (MZ*MZ)*
             (2*((gL+gR)*(gL+gR))*C36 + 
               2*((gL*gL) + (gR*gR))*C45))) - 
      4*el*(gL - gR)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (-(C34*C34) - (C46*C46) + (C35*C35) + 
         (C56*C56))*(-2*A2ZAR*A3ZZI*(gL*gL)*(MZ*MZ)*C36 + 
         2*A2ZAI*A3ZZR*(gL*gL)*(MZ*MZ)*C36 - 
         2*A2ZAR*A3ZZI*(gR*gR)*(MZ*MZ)*C36 + 
         2*A2ZAI*A3ZZR*(gR*gR)*(MZ*MZ)*C36 - 
         4*A2ZAR*A3ZZI*gL*gR*(MZ*MZ)*C45 + 
         4*A2ZAI*A3ZZR*gL*gR*(MZ*MZ)*C45 - 
         2*A2ZAR*A3ZZI*(gL*gL)*(MZ*MZ)*C45 + 
         2*A2ZAI*A3ZZR*(gL*gL)*(MZ*MZ)*C45 - 
         2*A2ZAR*A3ZZI*(gR*gR)*(MZ*MZ)*C45 + 
         2*A2ZAI*A3ZZR*(gR*gR)*(MZ*MZ)*C45 + 
         8*A2ZAR*A3ZZI*gL*gR*C36*C45 - 
         8*A2ZAI*A3ZZR*gL*gR*C36*C45 + 
         8*A2ZAR*A3ZZI*(gL*gL)*C36*C45 - 
         8*A2ZAI*A3ZZR*(gL*gL)*C36*C45 + 
         8*A2ZAR*A3ZZI*(gR*gR)*C36*C45 - 
         8*A2ZAI*A3ZZR*(gR*gR)*C36*C45 + 
         A2ZZI*A3ZAI*MZ*wZ*(2*((gL*gL) + (gR*gR))*C36 + 
            2*((gL+gR)*(gL+gR))*C45) + 
         A2ZZR*A3ZAR*MZ*wZ*(2*((gL*gL) + (gR*gR))*C36 + 
            2*((gL+gR)*(gL+gR))*C45) - 
         (A2ZAI*A3ZZI + A2ZAR*A3ZZR)*MZ*wZ*
          (2*((gL*gL) + (gR*gR))*C36 + 
            2*((gL+gR)*(gL+gR))*C45) + 
         A2ZZR*A3ZAI*(8*(gL*gR + (gL*gL) + (gR*gR))*C36*
             C45 - (MZ*MZ)*
             (2*((gL*gL) + (gR*gR))*C36 + 
               2*((gL+gR)*(gL+gR))*C45)) + 
         A2ZZI*A3ZAR*(-8*(gL*gR + (gL*gL) + (gR*gR))*C36*
             C45 + (MZ*MZ)*
             (2*((gL*gL) + (gR*gR))*C36 + 
               2*((gL+gR)*(gL+gR))*C45))) + 
      8*el*(gL + gR)*(-E3456)*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       ((-(A2ZZR*A3ZAI) + A2ZZI*A3ZAR + A2ZAR*A3ZZI - A2ZAI*A3ZZR)*MZ*wZ*
          (2*C36 + 2*C45) + 
         (A2ZZI*A3ZAI + A2ZZR*A3ZAR + A2ZAI*A3ZZI + A2ZAR*A3ZZR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45)))*
       (C46*C35 - C34*C56) + 
      8*el*(gL + gR)*E3456*((gL-gR)*(gL-gR))*(1/(vh*vh))*
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
          (2*((gL*gL) + (gR*gR))*C34 + 
            2*((gL+gR)*(gL+gR))*C56) + 
         A2ZZR*A3ZAI*(8*(gL*gR + (gL*gL) + (gR*gR))*C34*
             C56 - (MZ*MZ)*
             (2*((gL*gL) + (gR*gR))*C34 + 
               2*((gL+gR)*(gL+gR))*C56)) + 
         A2ZZI*A3ZAR*(-8*(gL*gR + (gL*gL) + (gR*gR))*C34*
             C56 + (MZ*MZ)*
             (2*((gL*gL) + (gR*gR))*C34 + 
               2*((gL+gR)*(gL+gR))*C56))) - 
      el*((gL*gL*gL) - (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       ((C35*C35) - (C46*C46))*(1.0/C56)*
       (-(C36*C45) + C35*C46 - C34*C56)*
       (4*A2ZZR*C34*C56*
          (A3ZAR*MZ*wZ*(2*(MZ*MZ)*C36*
                ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                  4*(C45*C45)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56)) + 
               4*(C36*C36)*
                (2*(MZ*MZ)*C45*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C56) + 
                  8*(C45*C45)*(-2*(MZ*MZ) + 2*C56)) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 - 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56)))) + 
            A3ZAI*(2*C34*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C36*C36) + 
                       2*C36*((MZ*MZ) - 2*C56) + 
                       2*C45*((MZ*MZ) + 2*C45 - 2*C56)
)) + (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (wZ*wZ)*(-32*(C36*C36)*(C45*C45) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*C36*C45*(2*C36 + 2*C45)*
                      C56 + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56) + 
                     (MZ*MZ)*
                      (4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                         16*C36*C45)*C56))))) + 
         4*A2ZZI*C34*C56*
          (A3ZAI*MZ*wZ*(2*(MZ*MZ)*C36*
                ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                  4*(C45*C45)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56)) + 
               4*(C36*C36)*
                (2*(MZ*MZ)*C45*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C56) + 
                  8*(C45*C45)*(-2*(MZ*MZ) + 2*C56)) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 - 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56)))) - 
            A3ZAR*(2*C34*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C36*C36) + 
                       2*C36*((MZ*MZ) - 2*C56) + 
                       2*C45*((MZ*MZ) + 2*C45 - 2*C56)
)) + (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (wZ*wZ)*(-32*(C36*C36)*(C45*C45) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*C36*C45*(2*C36 + 2*C45)*
                      C56 + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56) + 
                     (MZ*MZ)*
                      (4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                         16*C36*C45)*C56))))) + 
         4*C36*C45*
          (A2ZAR*(-(A3ZZR*MZ*wZ*
                  (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                       4*C45*C56 + 
                       2*C36*(-2*C45 + 2*C56)) + 
                    4*(C34*C34)*
                     (2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         8*(C56*C56) - 4*(MZ*MZ)*C56) + 
                       (MZ*MZ)*
                        (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                         16*(C56*C56) + 
                         2*(5*(MZ*MZ) + (wZ*wZ))*C56) + 
                       2*C36*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                         4*C45*C56)) + 
                    2*C34*
                     ((MZ*MZ)*
                        ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                         4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                         16*(C56*C56)*C45 - 
                         8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                       2*C36*
                        (8*(MZ*MZ)*(C56*C56) + 
                         2*C45*
                         ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56))))) + 
               A3ZZI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C45)*
                      ((MZ*MZ) - 2*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C45 - 
                        2*C56))*C56 + 
                  4*(C34*C34)*
                   (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-8*(C56*C56) + 
                        2*(-MZ + Sqrt2*SqrtC56)*
                         (MZ + Sqrt2*SqrtC56)*C45 + 
                        2*(MZ*MZ)*C56 + 
                        2*C36*
                         (-(MZ*MZ) + 2*C45 + 2*C56))) + 
                  2*(MZ*MZ)*C34*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C45) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                        4*(C56*C56)*(2*C36 + 2*C45) + 
                        2*(MZ*MZ*MZ*MZ)*
                         (2*C36 + 2*C45 + 4*C56) + 
                        (MZ*MZ)*
                         (4*(C56*C56) - 4*C36*C45 - 
                          8*(2*C36 + 2*C45)*C56))))) - 
            A2ZAI*(A3ZZI*MZ*wZ*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                     4*C45*C56 + 
                     2*C36*(-2*C45 + 2*C56)) + 
                  4*(C34*C34)*
                   (2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56) - 4*(MZ*MZ)*C56) + 
                     (MZ*MZ)*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        16*(C56*C56) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C56) + 
                     2*C36*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                        4*C45*C56)) + 
                  2*C34*((MZ*MZ)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        16*(C56*C56)*C45 - 
                        8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                     2*C36*
                      (8*(MZ*MZ)*(C56*C56) + 
                        2*C45*
                         ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                          4*(C56*C56) - 8*(MZ*MZ)*C56)))) + 
               A3ZZR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) 
+ (MZ*MZ)*(wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C45 - 
                        2*C56))*C56 + 
                  4*(C34*C34)*
                   (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-8*(C56*C56) + 
                        2*(-MZ + Sqrt2*SqrtC56)*
                         (MZ + Sqrt2*SqrtC56)*C45 + 
                        2*(MZ*MZ)*C56 + 
                        2*C36*
                         (-(MZ*MZ) + 2*C45 + 2*C56))) + 
                  2*(MZ*MZ)*C34*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C45) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                        4*(C56*C56)*(2*C36 + 2*C45) + 
                        2*(MZ*MZ*MZ*MZ)*
                         (2*C36 + 2*C45 + 4*C56) + 
                        (MZ*MZ)*
                         (4*(C56*C56) - 4*C36*C45 - 
                          8*(2*C36 + 2*C45)*C56))))))) - 
      el*E3456*((gL*gL*gL) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C36)*(1.0/C45)*
       (1.0/C56)*((C35*C35) + (C46*C46) - 
         2*C36*C45 + 2*C34*C56)*
       (4*A2ZZI*C34*C56*
          (A3ZAR*MZ*wZ*(2*(MZ*MZ)*C36*
                ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                  4*(C45*C45)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56)) + 
               4*(C36*C36)*
                (2*(MZ*MZ)*C45*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C56) + 
                  8*(C45*C45)*(-2*(MZ*MZ) + 2*C56)) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*C45*(-2*(MZ*MZ) + 2*C56)) + 
               2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (Sqrt2*SqrtC45 - 
                     Sqrt2*SqrtC56)*
                   (Sqrt2*SqrtC45 + 
                     Sqrt2*SqrtC56)*C45 - 
                  2*C36*
                   (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                     16*(MZ*MZ)*C45*C56 + 
                     4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                  4*(C36*C36)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C45*C45) - 
                     2*C45*(2*(MZ*MZ) + 2*C56)))) + 
            A3ZAI*(2*C34*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C36*C36) + 
                       2*C36*((MZ*MZ) - 2*C56) + 
                       2*C45*((MZ*MZ) + 2*C45 - 2*C56)
)) + (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (wZ*wZ)*(-32*(C36*C36)*(C45*C45) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*C36*C45*(2*C36 + 2*C45)*
                      C56 + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56) + 
                     (MZ*MZ)*
                      (4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                         16*C36*C45)*C56))))) + 
         4*A2ZZR*C34*C56*
          (-(A3ZAI*MZ*wZ*(2*(MZ*MZ)*C36*
                  ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) - 
                    8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45 + 
                    4*(C45*C45)*
                     (5*(MZ*MZ) + (wZ*wZ) - 4*C56)) + 
                 4*(C36*C36)*
                  (2*(MZ*MZ)*C45*
                     (5*(MZ*MZ) + (wZ*wZ) - 4*C56) + 
                    (MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-2*(MZ*MZ) + 2*C56) + 
                    8*(C45*C45)*(-2*(MZ*MZ) + 2*C56)) + 
                 2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C45*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                    2*C45*(-2*(MZ*MZ) + 2*C56)) + 
                 2*C34*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (Sqrt2*SqrtC45 - 
                       Sqrt2*SqrtC56)*
                     (Sqrt2*SqrtC45 + 
                       Sqrt2*SqrtC56)*C45 - 
                    2*C36*
                     (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56 - 
                       16*(MZ*MZ)*C45*C56 + 
                       4*(C45*C45)*(2*(MZ*MZ) + 2*C56)) + 
                    4*(C36*C36)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                       8*(C45*C45) - 
                       2*C45*(2*(MZ*MZ) + 2*C56))))) + 
            A3ZAR*(2*C34*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C36 + 2*C45) - 
                  (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ) - 2*C36)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C45*C45)*C36 + 
                     8*(C36*C36)*C45 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*(C36*C36)*C56 + 
                     8*(C45*C45)*C56 - 
                     (MZ*MZ)*
                      (4*(C36*C36) + 4*(C45*C45) + 
                        16*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C36*C36) + 
                       2*C36*((MZ*MZ) - 2*C56) + 
                       2*C45*((MZ*MZ) + 2*C45 - 2*C56)
)) + (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   (-8*C36*C45 + 
                     (MZ*MZ)*(2*C36 + 2*C45))*
                   ((MZ*MZ) - 2*C56) + 
                  (wZ*wZ)*(-32*(C36*C36)*(C45*C45) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C36 + 2*C45) + 
                     8*C36*C45*(2*C36 + 2*C45)*
                      C56 + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C36*C45 + 
                        2*(2*C36 + 2*C45)*C56) + 
                     (MZ*MZ)*
                      (4*C36*C45*(2*C36 + 2*C45) - 
                        2*(4*(C36*C36) + 4*(C45*C45) + 
                         16*C36*C45)*C56))))) + 
         4*C36*C45*
          (A2ZAI*(-(A3ZZR*MZ*wZ*
                  (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                       4*C45*C56 + 
                       2*C36*(-2*C45 + 2*C56)) + 
                    4*(C34*C34)*
                     (2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         8*(C56*C56) - 4*(MZ*MZ)*C56) + 
                       (MZ*MZ)*
                        (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                         16*(C56*C56) + 
                         2*(5*(MZ*MZ) + (wZ*wZ))*C56) + 
                       2*C36*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                         4*C45*C56)) + 
                    2*C34*
                     ((MZ*MZ)*
                        ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                         4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                         16*(C56*C56)*C45 - 
                         8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                       2*C36*
                        (8*(MZ*MZ)*(C56*C56) + 
                         2*C45*
                         ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C56*C56) - 8*(MZ*MZ)*C56))))) + 
               A3ZZI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C45)*
                      ((MZ*MZ) - 2*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C45 - 
                        2*C56))*C56 + 
                  4*(C34*C34)*
                   (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-8*(C56*C56) + 
                        2*(-MZ + Sqrt2*SqrtC56)*
                         (MZ + Sqrt2*SqrtC56)*C45 + 
                        2*(MZ*MZ)*C56 + 
                        2*C36*
                         (-(MZ*MZ) + 2*C45 + 2*C56))) + 
                  2*(MZ*MZ)*C34*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C45) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                        4*(C56*C56)*(2*C36 + 2*C45) + 
                        2*(MZ*MZ*MZ*MZ)*
                         (2*C36 + 2*C45 + 4*C56) + 
                        (MZ*MZ)*
                         (4*(C56*C56) - 4*C36*C45 - 
                          8*(2*C36 + 2*C45)*C56))))) + 
            A2ZAR*(A3ZZI*MZ*wZ*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                     4*C45*C56 + 
                     2*C36*(-2*C45 + 2*C56)) + 
                  4*(C34*C34)*
                   (2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56) - 4*(MZ*MZ)*C56) + 
                     (MZ*MZ)*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        16*(C56*C56) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C56) + 
                     2*C36*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                        4*C45*C56)) + 
                  2*C34*((MZ*MZ)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                        16*(C56*C56)*C45 - 
                        8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                     2*C36*
                      (8*(MZ*MZ)*(C56*C56) + 
                        2*C45*
                         ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                          4*(C56*C56) - 8*(MZ*MZ)*C56)))) + 
               A3ZZR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   ((-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) 
+ (MZ*MZ)*(wZ*wZ)*(-(MZ*MZ) + 2*C36 + 2*C45 - 
                        2*C56))*C56 + 
                  4*(C34*C34)*
                   (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      (-MZ + Sqrt2*SqrtC45)*
                      (MZ + Sqrt2*SqrtC45)*
                      ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                        6*(MZ*MZ)*C56) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-8*(C56*C56) + 
                        2*(-MZ + Sqrt2*SqrtC56)*
                         (MZ + Sqrt2*SqrtC56)*C45 + 
                        2*(MZ*MZ)*C56 + 
                        2*C36*
                         (-(MZ*MZ) + 2*C45 + 2*C56))) + 
                  2*(MZ*MZ)*C34*
                   ((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-(MZ*MZ) + 2*C36 + 2*C45) + 
                     (-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*
                      ((MZ*MZ) - 2*C45)*
                      ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                        8*(MZ*MZ)*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                        4*(C56*C56)*(2*C36 + 2*C45) + 
                        2*(MZ*MZ*MZ*MZ)*
                         (2*C36 + 2*C45 + 4*C56) + 
                        (MZ*MZ)*
                         (4*(C56*C56) - 4*C36*C45 - 
                          8*(2*C36 + 2*C45)*C56))))))) - 
      el*((gL*gL*gL) - (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*
       (-(C46*C46) + (C35*C35))*(1.0/C45)*
       (1.0/C56)*(C46*C35 - C36*C45 - 
         C34*C56)*(4*A2ZZR*C36*C45*
          (A3ZAR*MZ*wZ*(4*(C56*C56)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C36) + 
                  8*(C34*C34)*(-2*(MZ*MZ) + 2*C36) + 
                  2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 4*C36)*
                   C34) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34) + 
               2*(MZ*MZ)*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                  4*(C34*C34)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C36) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34)*
                C56 + 2*C45*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) - 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56)) + 
            A3ZAI*(2*C45*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C56*C56) + 
                       2*C34*
                        ((MZ*MZ) - 2*C36 + 2*C34) + 
                       2*((MZ*MZ) - 2*C36)*C56)) + 
                  (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(-32*(C34*C34)*(C56*C56) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) + 
                     8*C36*C34*C56*
                      (2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)) + 
                     (MZ*MZ)*
                      (4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          16*C34*C56)))))) + 
         4*A2ZZI*C36*C45*
          (A3ZAI*MZ*wZ*(4*(C56*C56)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C36) + 
                  8*(C34*C34)*(-2*(MZ*MZ) + 2*C36) + 
                  2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 4*C36)*
                   C34) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34) + 
               2*(MZ*MZ)*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                  4*(C34*C34)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C36) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34)*
                C56 + 2*C45*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) - 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56)) - 
            A3ZAR*(2*C45*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C56*C56) + 
                       2*C34*
                        ((MZ*MZ) - 2*C36 + 2*C34) + 
                       2*((MZ*MZ) - 2*C36)*C56)) + 
                  (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(-32*(C34*C34)*(C56*C56) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) + 
                     8*C36*C34*C56*
                      (2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)) + 
                     (MZ*MZ)*
                      (4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          16*C34*C56)))))) + 
         4*C34*C56*
          (A2ZAR*(-(A3ZZR*MZ*wZ*
                  (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                       4*C36*C34 + 
                       2*(2*C36 - 2*C34)*C56) + 
                    4*(C45*C45)*
                     ((MZ*MZ)*
                        (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                         16*(C36*C36) + 
                         2*(5*(MZ*MZ) + (wZ*wZ))*C36) + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36) - 4*(MZ*MZ)*C36)*
                        C34 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                         4*C36*C34)*C56) + 
                    2*C45*
                     ((MZ*MZ)*
                        ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                         4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                         8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                         16*(C36*C36)*C34) - 
                       2*(8*(MZ*MZ)*(C36*C36) + 
                         2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36)*
                         C34)*C56))) + 
               A3ZZI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   ((-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) 
+ (MZ*MZ)*(wZ*wZ)*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                        2*C56)) + 
                  4*(C45*C45)*
                   (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-8*(C36*C36) + 2*(MZ*MZ)*C36 + 
                        2*(-MZ + Sqrt2*SqrtC36)*
                         (MZ + Sqrt2*SqrtC36)*C34 + 
                        2*(-(MZ*MZ) + 2*C36 + 2*C34)*
                         C56)) + 
                  2*(MZ*MZ)*C45*
                   ((-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*((MZ*MZ) - 2*C34) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-(MZ*MZ) + 2*C34 + 2*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                        4*(C36*C36)*(2*C34 + 2*C56) + 
                        2*(MZ*MZ*MZ*MZ)*
                         (4*C36 + 2*C34 + 2*C56) + 
                        (MZ*MZ)*
                         (4*(C36*C36) - 4*C34*C56 - 
                          8*C36*(2*C34 + 2*C56)))))) - 
            A2ZAI*(A3ZZI*MZ*wZ*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                     4*C36*C34 + 
                     2*(2*C36 - 2*C34)*C56) + 
                  4*(C45*C45)*
                   ((MZ*MZ)*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        16*(C36*C36) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C36) + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36) - 4*(MZ*MZ)*C36)*
                      C34 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                        4*C36*C34)*C56) + 
                  2*C45*((MZ*MZ)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                        16*(C36*C36)*C34) - 
                     2*(8*(MZ*MZ)*(C36*C36) + 
                        2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36)*
                         C34)*C56)) + 
               A3ZZR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   ((-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) 
+ (MZ*MZ)*(wZ*wZ)*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                        2*C56)) + 
                  4*(C45*C45)*
                   (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-8*(C36*C36) + 2*(MZ*MZ)*C36 + 
                        2*(-MZ + Sqrt2*SqrtC36)*
                         (MZ + Sqrt2*SqrtC36)*C34 + 
                        2*(-(MZ*MZ) + 2*C36 + 2*C34)*
                         C56)) + 
                  2*(MZ*MZ)*C45*
                   ((-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*((MZ*MZ) - 2*C34) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-(MZ*MZ) + 2*C34 + 2*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                        4*(C36*C36)*(2*C34 + 2*C56) + 
                        2*(MZ*MZ*MZ*MZ)*
                         (4*C36 + 2*C34 + 2*C56) + 
                        (MZ*MZ)*
                         (4*(C36*C36) - 4*C34*C56 - 
                          8*C36*(2*C34 + 2*C56)))))))) - 
      el*(-E3456)*((gL*gL*gL) + (gR*gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C34)*(1.0/C45)*
       (1.0/C56)*((C46*C46) + (C35*C35) + 
         2*C36*C45 - 2*C34*C56)*
       (4*A2ZZI*C36*C45*
          (A3ZAR*MZ*wZ*(4*(C56*C56)*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-2*(MZ*MZ) + 2*C36) + 
                  8*(C34*C34)*(-2*(MZ*MZ) + 2*C36) + 
                  2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 4*C36)*
                   C34) + 
               2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                  2*(-2*(MZ*MZ) + 2*C36)*C34) + 
               2*(MZ*MZ)*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                  4*(C34*C34)*
                   (5*(MZ*MZ) + (wZ*wZ) - 4*C36) - 
                  8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34)*C56 
+ 2*C45*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                   (-(Sqrt2*SqrtC36) + 
                     Sqrt2*SqrtC34)*
                   (Sqrt2*SqrtC36 + 
                     Sqrt2*SqrtC34)*C34 + 
                  4*(C56*C56)*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                     8*(C34*C34) - 
                     2*(2*(MZ*MZ) + 2*C36)*C34) - 
                  2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                     4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                     16*(MZ*MZ)*C36*C34)*C56)) + 
            A3ZAI*(2*C45*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C56*C56) + 
                       2*C34*
                        ((MZ*MZ) - 2*C36 + 2*C34) + 
                       2*((MZ*MZ) - 2*C36)*C56)) + 
                  (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(-32*(C34*C34)*(C56*C56) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) + 
                     8*C36*C34*C56*
                      (2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)) + 
                     (MZ*MZ)*
                      (4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          16*C34*C56)))))) + 
         4*A2ZZR*C36*C45*
          (-(A3ZAI*MZ*wZ*(4*(C56*C56)*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-2*(MZ*MZ) + 2*C36) + 
                    8*(C34*C34)*(-2*(MZ*MZ) + 2*C36) + 
                    2*(MZ*MZ)*(5*(MZ*MZ) + (wZ*wZ) - 4*C36)*
                     C34) + 
                 2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34*
                  ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                    2*(-2*(MZ*MZ) + 2*C36)*C34) + 
                 2*(MZ*MZ)*((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                    4*(C34*C34)*
                     (5*(MZ*MZ) + (wZ*wZ) - 4*C36) - 
                    8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C34)*
                  C56 + 2*C45*
                  (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                     (-(Sqrt2*SqrtC36) + 
                       Sqrt2*SqrtC34)*
                     (Sqrt2*SqrtC36 + 
                       Sqrt2*SqrtC34)*C34 + 
                    4*(C56*C56)*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ)) + 
                       8*(C34*C34) - 
                       2*(2*(MZ*MZ) + 2*C36)*C34) - 
                    2*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 + 
                       4*(C34*C34)*(2*(MZ*MZ) + 2*C36) - 
                       16*(MZ*MZ)*C36*C34)*C56))) + 
            A3ZAR*(2*C45*
                ((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)*(2*C34 + 2*C56) - 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C56)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (8*(C34*C34)*C36 + 
                     8*(C56*C56)*C36 + 
                     8*(C56*C56)*C34 + 
                     8*(C34*C34)*C56 + 
                     2*(MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) - 
                     (MZ*MZ)*
                      (4*(C34*C34) + 4*(C56*C56) + 
                        16*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)))) + 
               (MZ*MZ)*(-((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                     (4*(C56*C56) + 
                       2*C34*
                        ((MZ*MZ) - 2*C36 + 2*C34) + 
                       2*((MZ*MZ) - 2*C36)*C56)) + 
                  (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34)*
                   (-8*C34*C56 + 
                     (MZ*MZ)*(2*C34 + 2*C56)) + 
                  (wZ*wZ)*(-32*(C34*C34)*(C56*C56) - 
                     2*(MZ*MZ*MZ*MZ*MZ*MZ)*(2*C34 + 2*C56) + 
                     8*C36*C34*C56*
                      (2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (8*C34*C56 + 
                        2*C36*(2*C34 + 2*C56)) + 
                     (MZ*MZ)*
                      (4*C34*C56*(2*C34 + 2*C56) - 
                        2*C36*
                         (4*(C34*C34) + 4*(C56*C56) + 
                          16*C34*C56)))))) + 
         4*C34*C56*
          (A2ZAI*(-(A3ZZR*MZ*wZ*
                  (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                     ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                       4*C36*C34 + 
                       2*(2*C36 - 2*C34)*C56) + 
                    4*(C45*C45)*
                     ((MZ*MZ)*
                        (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                         16*(C36*C36) + 
                         2*(5*(MZ*MZ) + (wZ*wZ))*C36) + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         8*(C36*C36) - 4*(MZ*MZ)*C36)*
                        C34 + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                         4*C36*C34)*C56) + 
                    2*C45*
                     ((MZ*MZ)*
                        ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                         4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                         8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                         16*(C36*C36)*C34) - 
                       2*(8*(MZ*MZ)*(C36*C36) + 
                         2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36)*
                         C34)*C56))) + 
               A3ZZI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   ((-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) 
+ (MZ*MZ)*(wZ*wZ)*(-(MZ*MZ) - 2*C36 + 2*C34 + 
                        2*C56)) + 
                  4*(C45*C45)*
                   (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-8*(C36*C36) + 2*(MZ*MZ)*C36 + 
                        2*(-MZ + Sqrt2*SqrtC36)*
                         (MZ + Sqrt2*SqrtC36)*C34 + 
                        2*(-(MZ*MZ) + 2*C36 + 2*C34)*
                         C56)) + 
                  2*(MZ*MZ)*C45*
                   ((-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*((MZ*MZ) - 2*C34) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-(MZ*MZ) + 2*C34 + 2*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                        4*(C36*C36)*(2*C34 + 2*C56) + 
                        2*(MZ*MZ*MZ*MZ)*
                         (4*C36 + 2*C34 + 2*C56) + 
                        (MZ*MZ)*
                         (4*(C36*C36) - 4*C34*C56 - 
                          8*C36*(2*C34 + 2*C56)))))) + 
            A2ZAR*(A3ZZI*MZ*wZ*
                (2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                     4*C36*C34 + 
                     2*(2*C36 - 2*C34)*C56) + 
                  4*(C45*C45)*
                   ((MZ*MZ)*
                      (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                        16*(C36*C36) + 
                        2*(5*(MZ*MZ) + (wZ*wZ))*C36) + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36) - 4*(MZ*MZ)*C36)*
                      C34 + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                        4*C36*C34)*C56) + 
                  2*C45*((MZ*MZ)*
                      ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                        4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                        8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                        16*(C36*C36)*C34) - 
                     2*(8*(MZ*MZ)*(C36*C36) + 
                        2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36)*
                         C34)*C56)) + 
               A3ZZR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                   ((-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56)
) + 4*(C45*C45)*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                     (-MZ + Sqrt2*SqrtC34)*
                      (MZ + Sqrt2*SqrtC34)*
                      (-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                        6*(MZ*MZ)*C36) + 
                     (MZ*MZ)*(wZ*wZ)*
                      (-8*(C36*C36) + 2*(MZ*MZ)*C36 + 
                        2*(-MZ + Sqrt2*SqrtC36)*
                         (MZ + Sqrt2*SqrtC36)*C34 + 
                        2*(-(MZ*MZ) + 2*C36 + 2*C34)*C56
)) + 2*(MZ*MZ)*C45*((-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*
                      ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                        8*(MZ*MZ)*C36)*((MZ*MZ) - 2*C34) + 
                     (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                      (-(MZ*MZ) + 2*C34 + 2*C56) + 
                     (wZ*wZ)*
                      (-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                        4*(C36*C36)*(2*C34 + 2*C56) + 
                        2*(MZ*MZ*MZ*MZ)*
                         (4*C36 + 2*C34 + 2*C56) + 
                        (MZ*MZ)*
                         (4*(C36*C36) - 4*C34*C56 - 
                          8*C36*(2*C34 + 2*C56))))))))))/
  524288.;
}

double GetGeneralScalar4e_Part36(LeptonVectors &leptons, double A1ZZI, double A1ZZR, double A3ZAI, double A3ZAR)
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
    (-2*el*(gL + gR)*(-E3456)*((gL*gL) + (gR*gR))*(MZ*MZ)*
       (1/(vh*vh))*pow((MZ*MZ)*(wZ*wZ) + 
         pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-((A1ZZR*A3ZAI - A1ZZI*A3ZAR)*MZ*wZ*(2*C36 + 2*C45)) + 
         (A1ZZI*A3ZAI + A1ZZR*A3ZAR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45)))*
       (-C34 + C46 + C35 - C56) - 
      2*el*(gL + gR)*(-E3456)*((gL-gR)*(gL-gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       (-((A1ZZR*A3ZAI - A1ZZI*A3ZAR)*MZ*wZ*(2*C36 + 2*C45)) + 
         (A1ZZI*A3ZAI + A1ZZR*A3ZAR)*
          (8*C36*C45 - (MZ*MZ)*(2*C36 + 2*C45)))*
       (C34 + C46 + C35 + C56) + 
      2*el*(gL - gR)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       ((A1ZZI*A3ZAI + A1ZZR*A3ZAR)*MZ*wZ*
          (2*((gL+gR)*(gL+gR))*C36 + 
            2*((gL*gL) + (gR*gR))*C45) + 
         (A1ZZR*A3ZAI - A1ZZI*A3ZAR)*
          (8*(gL*gR + (gL*gL) + (gR*gR))*C36*C45 - 
            (MZ*MZ)*(2*((gL+gR)*(gL+gR))*C36 + 
               2*((gL*gL) + (gR*gR))*C45)))*
       ((C35*C35)*C46 + 
         C34*(C34 + C46 - C56)*C56 - 
         C36*C45*(-C34 + C46 + C56) - 
         C35*(C46*(C34 + C46) - 
            C36*C45 + (C34 - C46)*C56)) + 
      2*el*(gL - gR)*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       (1.0/C36)*(1.0/C45)*
       ((A1ZZI*A3ZAI + A1ZZR*A3ZAR)*MZ*wZ*
          (2*((gL*gL) + (gR*gR))*C36 + 
            2*((gL+gR)*(gL+gR))*C45) + 
         (A1ZZR*A3ZAI - A1ZZI*A3ZAR)*
          (8*(gL*gR + (gL*gL) + (gR*gR))*C36*C45 - 
            (MZ*MZ)*(2*((gL*gL) + (gR*gR))*C36 + 
               2*((gL+gR)*(gL+gR))*C45)))*
       ((C35*C35)*C46 + 
         C36*C45*(-C34 - C46 + C56) + 
         C34*C56*(-C34 + C46 + C56) - 
         C35*((C46*C46) - C34*C46 - 
            C36*C45 + (C34 + C46)*C56)) - 
      2*el*(gL + gR)*E3456*((gL*gL) + (gR*gR))*(MZ*MZ)*
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
          (2*((gL*gL) + (gR*gR))*C34 + 
            2*((gL+gR)*(gL+gR))*C56) + 
         (A1ZZR*A3ZAI - A1ZZI*A3ZAR)*
          (8*(gL*gR + (gL*gL) + (gR*gR))*C34*C56 - 
            (MZ*MZ)*(2*((gL*gL) + (gR*gR))*C34 + 
               2*((gL+gR)*(gL+gR))*C56))) + 
      4*el*((gL*gL*gL) - (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*(C35 - C46)*
       (-(C36*C45) + C35*C46 + C34*C56)*
       (A1ZZR*(A3ZAR*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                C56*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56)) + 
               4*(C34*C34)*
                (2*C45*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C56*C56) - 4*(MZ*MZ)*C56) + 
                  (MZ*MZ)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                     16*(C56*C56) + 
                     2*(5*(MZ*MZ) + (wZ*wZ))*C56) + 
                  2*C36*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                     4*C45*C56)) + 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                     16*(C56*C56)*C45 - 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                  2*C36*
                   (8*(MZ*MZ)*(C56*C56) + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)))) + 
            A3ZAI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56)
)*C56 + 4*(C34*C34)*
                (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                     6*(MZ*MZ)*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-8*(C56*C56) + 
                     2*(-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C45 + 
                     2*(MZ*MZ)*C56 + 
                     2*C36*(-(MZ*MZ) + 2*C45 + 2*C56))
) + 2*(MZ*MZ)*C34*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                     8*(MZ*MZ)*C56) + 
                  (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                     4*(C56*C56)*(2*C36 + 2*C45) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (2*C36 + 2*C45 + 4*C56) + 
                     (MZ*MZ)*
                      (4*(C56*C56) - 4*C36*C45 - 
                        8*(2*C36 + 2*C45)*C56))))) + 
         A1ZZI*(A3ZAI*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                C56*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56)) + 
               4*(C34*C34)*
                (2*C45*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C56*C56) - 4*(MZ*MZ)*C56) + 
                  (MZ*MZ)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                     16*(C56*C56) + 
                     2*(5*(MZ*MZ) + (wZ*wZ))*C56) + 
                  2*C36*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                     4*C45*C56)) + 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                     16*(C56*C56)*C45 - 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                  2*C36*(8*(MZ*MZ)*(C56*C56) + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)))) - 
            A3ZAR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56))*
                C56 + 4*(C34*C34)*
                (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                     6*(MZ*MZ)*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-8*(C56*C56) + 
                     2*(-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C45 + 
                     2*(MZ*MZ)*C56 + 
                     2*C36*(-(MZ*MZ) + 2*C45 + 2*C56))) 
+ 2*(MZ*MZ)*C34*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                     8*(MZ*MZ)*C56) + 
                  (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                     4*(C56*C56)*(2*C36 + 2*C45) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (2*C36 + 2*C45 + 4*C56) + 
                     (MZ*MZ)*
                      (4*(C56*C56) - 4*C36*C45 - 
                        8*(2*C36 + 2*C45)*C56)))))) - 
      4*el*E3456*((gL*gL*gL) + (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C34)*(1.0/C56)*(C35 + C46)*
       (A1ZZI*(A3ZAR*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                C56*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                  4*C45*C56 + 
                  2*C36*(-2*C45 + 2*C56)) + 
               4*(C34*C34)*
                (2*C45*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C56*C56) - 4*(MZ*MZ)*C56) + 
                  (MZ*MZ)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                     16*(C56*C56) + 
                     2*(5*(MZ*MZ) + (wZ*wZ))*C56) + 
                  2*C36*
                   ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                     4*C45*C56)) + 
               2*C34*((MZ*MZ)*
                   ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                     16*(C56*C56)*C45 - 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                  2*C36*
                   (8*(MZ*MZ)*(C56*C56) + 
                     2*C45*
                      ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C56*C56) - 8*(MZ*MZ)*C56)))) + 
            A3ZAI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56)
)*C56 + 4*(C34*C34)*
                (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                     6*(MZ*MZ)*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-8*(C56*C56) + 
                     2*(-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C45 + 
                     2*(MZ*MZ)*C56 + 
                     2*C36*(-(MZ*MZ) + 2*C45 + 2*C56))
) + 2*(MZ*MZ)*C34*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                     8*(MZ*MZ)*C56) + 
                  (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                     4*(C56*C56)*(2*C36 + 2*C45) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (2*C36 + 2*C45 + 4*C56) + 
                     (MZ*MZ)*
                      (4*(C56*C56) - 4*C36*C45 - 
                        8*(2*C36 + 2*C45)*C56))))) + 
         A1ZZR*(-(A3ZAI*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  C56*((MZ*MZ)*
                     ((MZ*MZ) + (wZ*wZ) - 4*C56) + 
                    4*C45*C56 + 
                    2*C36*(-2*C45 + 2*C56)) + 
                 4*(C34*C34)*
                  (2*C45*
                     ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                       8*(C56*C56) - 4*(MZ*MZ)*C56) + 
                    (MZ*MZ)*
                     (-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                       16*(C56*C56) + 
                       2*(5*(MZ*MZ) + (wZ*wZ))*C56) + 
                    2*C36*
                     ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                       8*(C56*C56) - 4*(MZ*MZ)*C56 - 
                       4*C45*C56)) + 
                 2*C34*((MZ*MZ)*
                     ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                       4*(5*(MZ*MZ) + (wZ*wZ))*(C56*C56) - 
                       16*(C56*C56)*C45 - 
                       8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C56) - 
                    2*C36*
                     (8*(MZ*MZ)*(C56*C56) + 
                       2*C45*
                        ((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                          4*(C56*C56) - 8*(MZ*MZ)*C56))))) + 
            A3ZAR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                ((-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*((MZ*MZ) - 2*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45 - 2*C56))*
                C56 + 4*(C34*C34)*
                (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   (-MZ + Sqrt2*SqrtC45)*
                   (MZ + Sqrt2*SqrtC45)*
                   ((MZ*MZ*MZ*MZ) + 8*(C56*C56) - 
                     6*(MZ*MZ)*C56) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-8*(C56*C56) + 
                     2*(-MZ + Sqrt2*SqrtC56)*
                      (MZ + Sqrt2*SqrtC56)*C45 + 
                     2*(MZ*MZ)*C56 + 
                     2*C36*(-(MZ*MZ) + 2*C45 + 2*C56))) 
+ 2*(MZ*MZ)*C34*((MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (-(MZ*MZ) + 2*C36 + 2*C45) + 
                  (-MZ + Sqrt2*SqrtC36)*
                   (MZ + Sqrt2*SqrtC36)*
                   ((MZ*MZ) - 2*C45)*
                   ((MZ*MZ*MZ*MZ) + 12*(C56*C56) - 
                     8*(MZ*MZ)*C56) + 
                  (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                     4*(C56*C56)*(2*C36 + 2*C45) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (2*C36 + 2*C45 + 4*C56) + 
                     (MZ*MZ)*
                      (4*(C56*C56) - 4*C36*C45 - 
                        8*(2*C36 + 2*C45)*C56)))))) + 
      4*el*((gL*gL*gL) - (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C45)*(-C46 + C35)*
       (C46*C35 + C36*C45 - C34*C56)*
       (A1ZZR*(A3ZAR*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                C36*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56) + 
               4*(C45*C45)*
                ((MZ*MZ)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                     16*(C36*C36) + 
                     2*(5*(MZ*MZ) + (wZ*wZ))*C36) + 
                  2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36)*
                   C34 + 
                  2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                     4*C36*C34)*C56) + 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                     16*(C36*C36)*C34) - 
                  2*(8*(MZ*MZ)*(C36*C36) + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34)*C56)) + 
            A3ZAI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                ((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56)) 
+ 4*(C45*C45)*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                     6*(MZ*MZ)*C36) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-8*(C36*C36) + 2*(MZ*MZ)*C36 + 
                     2*(-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C34 + 
                     2*(-(MZ*MZ) + 2*C36 + 2*C34)*C56)
) + 2*(MZ*MZ)*C45*((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                     8*(MZ*MZ)*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (-(MZ*MZ) + 2*C34 + 2*C56) + 
                  (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                     4*(C36*C36)*(2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (4*C36 + 2*C34 + 2*C56) + 
                     (MZ*MZ)*
                      (4*(C36*C36) - 4*C34*C56 - 
                        8*C36*(2*C34 + 2*C56)))))) + 
         A1ZZI*(A3ZAI*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                C36*((MZ*MZ)*
                   ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56) + 
               4*(C45*C45)*
                ((MZ*MZ)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                     16*(C36*C36) + 
                     2*(5*(MZ*MZ) + (wZ*wZ))*C36) + 
                  2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36)*
                   C34 + 
                  2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                     4*C36*C34)*C56) + 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                     16*(C36*C36)*C34) - 
                  2*(8*(MZ*MZ)*(C36*C36) + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34)*C56)) - 
            A3ZAR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                ((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56)) 
+ 4*(C45*C45)*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                     6*(MZ*MZ)*C36) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-8*(C36*C36) + 2*(MZ*MZ)*C36 + 
                     2*(-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C34 + 
                     2*(-(MZ*MZ) + 2*C36 + 2*C34)*C56)) 
+ 2*(MZ*MZ)*C45*((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                     8*(MZ*MZ)*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (-(MZ*MZ) + 2*C34 + 2*C56) + 
                  (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                     4*(C36*C36)*(2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (4*C36 + 2*C34 + 2*C56) + 
                     (MZ*MZ)*
                      (4*(C36*C36) - 4*C34*C56 - 
                        8*C36*(2*C34 + 2*C56))))))) - 
      4*el*(-E3456)*((gL*gL*gL) + (gR*gR*gR))*(MZ*MZ)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C36,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C56,2),-1)*
       (1.0/C36)*(1.0/C45)*(C46 + C35)*
       (A1ZZI*(A3ZAR*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                ((MZ*MZ)*((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                  4*C36*C34 + 
                  2*(2*C36 - 2*C34)*C56) + 
               4*(C45*C45)*
                ((MZ*MZ)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                     16*(C36*C36) + 
                     2*(5*(MZ*MZ) + (wZ*wZ))*C36) + 
                  2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36)*
                   C34 + 
                  2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                     8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                     4*C36*C34)*C56) + 
               2*C45*((MZ*MZ)*
                   ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                     4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                     8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                     16*(C36*C36)*C34) - 
                  2*(8*(MZ*MZ)*(C36*C36) + 
                     2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                        4*(C36*C36) - 8*(MZ*MZ)*C36)*
                      C34)*C56)) + 
            A3ZAI*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                ((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56)) 
+ 4*(C45*C45)*(-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 
                     6*(MZ*MZ)*C36) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-8*(C36*C36) + 2*(MZ*MZ)*C36 + 
                     2*(-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C34 + 
                     2*(-(MZ*MZ) + 2*C36 + 2*C34)*C56)) 
+ 2*(MZ*MZ)*C45*((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                     8*(MZ*MZ)*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (-(MZ*MZ) + 2*C34 + 2*C56) + 
                  (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                     4*(C36*C36)*(2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*
                      (4*C36 + 2*C34 + 2*C56) + 
                     (MZ*MZ)*
                      (4*(C36*C36) - 4*C34*C56 - 
                        8*C36*(2*C34 + 2*C56)))))) + 
         A1ZZR*(-(A3ZAI*MZ*wZ*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*
                  C36*((MZ*MZ)*
                     ((MZ*MZ) + (wZ*wZ) - 4*C36) + 
                    4*C36*C34 + 
                    2*(2*C36 - 2*C34)*C56) + 
                 4*(C45*C45)*
                  ((MZ*MZ)*(-2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ)) - 
                       16*(C36*C36) + 
                       2*(5*(MZ*MZ) + (wZ*wZ))*C36) + 
                    2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                       8*(C36*C36) - 4*(MZ*MZ)*C36)*
                     C34 + 
                    2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                       8*(C36*C36) - 4*(MZ*MZ)*C36 - 
                       4*C36*C34)*C56) + 
                 2*C45*((MZ*MZ)*
                     ((MZ*MZ)*pow((MZ*MZ) + (wZ*wZ),2) + 
                       4*(5*(MZ*MZ) + (wZ*wZ))*(C36*C36) - 
                       8*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36 - 
                       16*(C36*C36)*C34) - 
                    2*(8*(MZ*MZ)*(C36*C36) + 
                       2*((MZ*MZ*MZ*MZ) + (MZ*MZ)*(wZ*wZ) + 
                         4*(C36*C36) - 8*(MZ*MZ)*C36)*
                        C34)*C56))) + 
            A3ZAR*(2*(MZ*MZ)*((MZ*MZ) + (wZ*wZ))*C36*
                ((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ) - 2*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ)*
                   (-(MZ*MZ) - 2*C36 + 2*C34 + 2*C56)) + 
               4*(C45*C45)*
                (-((MZ*MZ*MZ*MZ)*(wZ*wZ*wZ*wZ)) + 
                  (-MZ + Sqrt2*SqrtC34)*
                   (MZ + Sqrt2*SqrtC34)*
                   (-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ*MZ*MZ) + 8*(C36*C36) - 6*(MZ*MZ)*C36) 
+ (MZ*MZ)*(wZ*wZ)*(-8*(C36*C36) + 2*(MZ*MZ)*C36 + 
                     2*(-MZ + Sqrt2*SqrtC36)*
                      (MZ + Sqrt2*SqrtC36)*C34 + 
                     2*(-(MZ*MZ) + 2*C36 + 2*C34)*C56)) 
+ 2*(MZ*MZ)*C45*((-MZ + Sqrt2*SqrtC56)*
                   (MZ + Sqrt2*SqrtC56)*
                   ((MZ*MZ*MZ*MZ) + 12*(C36*C36) - 
                     8*(MZ*MZ)*C36)*((MZ*MZ) - 2*C34) + 
                  (MZ*MZ)*(wZ*wZ*wZ*wZ)*
                   (-(MZ*MZ) + 2*C34 + 2*C56) + 
                  (wZ*wZ)*(-2*(MZ*MZ*MZ*MZ*MZ*MZ) + 
                     4*(C36*C36)*(2*C34 + 2*C56) + 
                     2*(MZ*MZ*MZ*MZ)*(4*C36 + 2*C34 + 2*C56) + 
                     (MZ*MZ)*
                      (4*(C36*C36) - 4*C34*C56 - 
                        8*C36*(2*C34 + 2*C56)))))))))/
  524288.;
}

double GetGeneralScalar4e(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part2(leptons, parameters)
      + GetGeneralScalar4e_Part3(leptons, parameters)
      + GetGeneralScalar4e_Part5(leptons, parameters)
      + GetGeneralScalar4e_Part7(leptons, parameters)
      + GetGeneralScalar4e_Part8(leptons, parameters)
      + GetGeneralScalar4e_Part9(leptons, parameters)
      + GetGeneralScalar4e_Part10(leptons, parameters)
      + GetGeneralScalar4e_Part11(leptons, parameters)
      + GetGeneralScalar4e_Part12(leptons, parameters)
      + GetGeneralScalar4e_Part14(leptons, parameters)
      + GetGeneralScalar4e_Part15(leptons, parameters)
      + GetGeneralScalar4e_Part17(leptons, parameters)
      + GetGeneralScalar4e_Part20(leptons, parameters)
      + GetGeneralScalar4e_Part21(leptons, parameters)
      + GetGeneralScalar4e_Part22(leptons, parameters)
      + GetGeneralScalar4e_Part23(leptons, parameters)
      + GetGeneralScalar4e_Part24(leptons, parameters)
      + GetGeneralScalar4e_Part26(leptons, parameters)
      + GetGeneralScalar4e_Part27(leptons, parameters)
      + GetGeneralScalar4e_Part29(leptons, parameters)
      + GetGeneralScalar4e_Part32(leptons, parameters)
      + GetGeneralScalar4e_Part33(leptons, parameters)
      + GetGeneralScalar4e_Part34(leptons, parameters)
      + GetGeneralScalar4e_Part35(leptons, parameters)
      + GetGeneralScalar4e_Part36(leptons, parameters);
}

double GetGeneralScalar4e_Part2(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part2(leptons, parameters.aAI, parameters.aAR);
}

double GetGeneralScalar4e_Part3(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part3(leptons, parameters.aAdI, parameters.aAdR);
}

double GetGeneralScalar4e_Part5(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part5(leptons, parameters.aAI, parameters.aAR, parameters.aAdI, parameters.aAdR);
}

double GetGeneralScalar4e_Part7(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part7(leptons, parameters.ahI, parameters.ahR);
}

double GetGeneralScalar4e_Part8(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part8(leptons, parameters.aZI, parameters.aZR);
}

double GetGeneralScalar4e_Part9(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part9(leptons, parameters.aZdI, parameters.aZdR);
}

double GetGeneralScalar4e_Part10(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part10(leptons, parameters.ahI, parameters.ahR, parameters.aZI, parameters.aZR);
}

double GetGeneralScalar4e_Part11(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part11(leptons, parameters.aZI, parameters.aZR, parameters.aZdI, parameters.aZdR);
}

double GetGeneralScalar4e_Part12(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part12(leptons, parameters.ahI, parameters.ahR, parameters.aZdI, parameters.aZdR);
}

double GetGeneralScalar4e_Part14(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part14(leptons, parameters.aZAI, parameters.aZAR);
}

double GetGeneralScalar4e_Part15(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part15(leptons, parameters.aZAdI, parameters.aZAdR);
}

double GetGeneralScalar4e_Part17(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part17(leptons, parameters.aZAI, parameters.aZAR, parameters.aZAdI, parameters.aZAdR);
}

double GetGeneralScalar4e_Part20(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part20(leptons, parameters.aAI, parameters.aAR, parameters.aZI, parameters.aZR);
}

double GetGeneralScalar4e_Part21(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part21(leptons, parameters.aAdI, parameters.aAdR, parameters.aZdI, parameters.aZdR);
}

double GetGeneralScalar4e_Part22(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part22(leptons, parameters.ahI, parameters.ahR, parameters.aAI, parameters.aAR);
}

double GetGeneralScalar4e_Part23(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part23(leptons, parameters.aAI, parameters.aAR, parameters.aZI, parameters.aZR, parameters.aAdI, parameters.aAdR, parameters.aZdI, parameters.aZdR);
}

double GetGeneralScalar4e_Part24(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part24(leptons, parameters.ahI, parameters.ahR, parameters.aAdI, parameters.aAdR);
}

double GetGeneralScalar4e_Part26(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part26(leptons, parameters.aAI, parameters.aAR, parameters.aZAI, parameters.aZAR);
}

double GetGeneralScalar4e_Part27(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part27(leptons, parameters.aAdI, parameters.aAdR, parameters.aZAdI, parameters.aZAdR);
}

double GetGeneralScalar4e_Part29(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part29(leptons, parameters.aAI, parameters.aAR, parameters.aZAI, parameters.aZAR, parameters.aAdI, parameters.aAdR, parameters.aZAdI, parameters.aZAdR);
}

double GetGeneralScalar4e_Part32(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part32(leptons, parameters.aZAI, parameters.aZAR, parameters.aZI, parameters.aZR);
}

double GetGeneralScalar4e_Part33(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part33(leptons, parameters.aZAdI, parameters.aZAdR, parameters.aZdI, parameters.aZdR);
}

double GetGeneralScalar4e_Part34(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part34(leptons, parameters.ahI, parameters.ahR, parameters.aZAI, parameters.aZAR);
}

double GetGeneralScalar4e_Part35(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part35(leptons, parameters.aZAI, parameters.aZAR, parameters.aZI, parameters.aZR, parameters.aZAdI, parameters.aZAdR, parameters.aZdI, parameters.aZdR);
}

double GetGeneralScalar4e_Part36(LeptonVectors &leptons, const GeneralScalarParameters &parameters)
{
   return GetGeneralScalar4e_Part36(leptons, parameters.ahI, parameters.ahR, parameters.aZAdI, parameters.aZAdR);
}

double GetGeneralScalar4e_aAR_aAR(LeptonVectors &leptons, double aAR)
{
   return GetGeneralScalar4e_Part2(leptons, 0, aAR);
}

double GetGeneralScalar4e_aAI_aAR(LeptonVectors &leptons, double aAI, double aAR)
{
   return GetGeneralScalar4e_Part2(leptons, aAI, aAR)
      - GetGeneralScalar4e_Part2(leptons, aAI, 0)
      - GetGeneralScalar4e_Part2(leptons, 0, aAR);
}

double GetGeneralScalar4e_aAI_aAI(LeptonVectors &leptons, double aAI)
{
   return GetGeneralScalar4e_Part2(leptons, aAI, 0);
}

double GetGeneralScalar4e_aAdR_aAdR(LeptonVectors &leptons, double aAdR)
{
   return GetGeneralScalar4e_Part3(leptons, 0, aAdR);
}

double GetGeneralScalar4e_aAdI_aAdR(LeptonVectors &leptons, double aAdI, double aAdR)
{
   return GetGeneralScalar4e_Part3(leptons, aAdI, aAdR)
      - GetGeneralScalar4e_Part3(leptons, aAdI, 0)
      - GetGeneralScalar4e_Part3(leptons, 0, aAdR);
}

double GetGeneralScalar4e_aAdI_aAdI(LeptonVectors &leptons, double aAdI)
{
   return GetGeneralScalar4e_Part3(leptons, aAdI, 0);
}

double GetGeneralScalar4e_aAR_aAdR(LeptonVectors &leptons, double aAR, double aAdR)
{
   return GetGeneralScalar4e_Part5(leptons, 0, aAR, 0, aAdR);
}

double GetGeneralScalar4e_aAI_aAdR(LeptonVectors &leptons, double aAI, double aAdR)
{
   return GetGeneralScalar4e_Part5(leptons, aAI, 0, 0, aAdR);
}

double GetGeneralScalar4e_aAR_aAdI(LeptonVectors &leptons, double aAR, double aAdI)
{
   return GetGeneralScalar4e_Part5(leptons, 0, aAR, aAdI, 0);
}

double GetGeneralScalar4e_aAI_aAdI(LeptonVectors &leptons, double aAI, double aAdI)
{
   return GetGeneralScalar4e_Part5(leptons, aAI, 0, aAdI, 0);
}

double GetGeneralScalar4e_ahR_ahR(LeptonVectors &leptons, double ahR)
{
   return GetGeneralScalar4e_Part7(leptons, 0, ahR);
}

double GetGeneralScalar4e_ahI_ahR(LeptonVectors &leptons, double ahI, double ahR)
{
   return GetGeneralScalar4e_Part7(leptons, ahI, ahR)
      - GetGeneralScalar4e_Part7(leptons, 0, ahR)
      - GetGeneralScalar4e_Part7(leptons, ahI, 0);
}

double GetGeneralScalar4e_ahI_ahI(LeptonVectors &leptons, double ahI)
{
   return GetGeneralScalar4e_Part7(leptons, ahI, 0);
}

double GetGeneralScalar4e_aZR_aZR(LeptonVectors &leptons, double aZR)
{
   return GetGeneralScalar4e_Part8(leptons, 0, aZR);
}

double GetGeneralScalar4e_aZI_aZR(LeptonVectors &leptons, double aZI, double aZR)
{
   return GetGeneralScalar4e_Part8(leptons, aZI, aZR)
      - GetGeneralScalar4e_Part8(leptons, 0, aZR)
      - GetGeneralScalar4e_Part8(leptons, aZI, 0);
}

double GetGeneralScalar4e_aZI_aZI(LeptonVectors &leptons, double aZI)
{
   return GetGeneralScalar4e_Part8(leptons, aZI, 0);
}

double GetGeneralScalar4e_aZdR_aZdR(LeptonVectors &leptons, double aZdR)
{
   return GetGeneralScalar4e_Part9(leptons, 0, aZdR);
}

double GetGeneralScalar4e_aZdI_aZdR(LeptonVectors &leptons, double aZdI, double aZdR)
{
   return GetGeneralScalar4e_Part9(leptons, aZdI, aZdR)
      - GetGeneralScalar4e_Part9(leptons, 0, aZdR)
      - GetGeneralScalar4e_Part9(leptons, aZdI, 0);
}

double GetGeneralScalar4e_aZdI_aZdI(LeptonVectors &leptons, double aZdI)
{
   return GetGeneralScalar4e_Part9(leptons, aZdI, 0);
}

double GetGeneralScalar4e_aZR_ahR(LeptonVectors &leptons, double aZR, double ahR)
{
   return GetGeneralScalar4e_Part10(leptons, 0, ahR, 0, aZR);
}

double GetGeneralScalar4e_aZR_ahI(LeptonVectors &leptons, double aZR, double ahI)
{
   return GetGeneralScalar4e_Part10(leptons, ahI, 0, 0, aZR);
}

double GetGeneralScalar4e_aZI_ahR(LeptonVectors &leptons, double aZI, double ahR)
{
   return GetGeneralScalar4e_Part10(leptons, 0, ahR, aZI, 0);
}

double GetGeneralScalar4e_aZI_ahI(LeptonVectors &leptons, double aZI, double ahI)
{
   return GetGeneralScalar4e_Part10(leptons, ahI, 0, aZI, 0);
}

double GetGeneralScalar4e_aZR_aZdR(LeptonVectors &leptons, double aZR, double aZdR)
{
   return GetGeneralScalar4e_Part11(leptons, 0, aZR, 0, aZdR);
}

double GetGeneralScalar4e_aZI_aZdR(LeptonVectors &leptons, double aZI, double aZdR)
{
   return GetGeneralScalar4e_Part11(leptons, aZI, 0, 0, aZdR);
}

double GetGeneralScalar4e_aZR_aZdI(LeptonVectors &leptons, double aZR, double aZdI)
{
   return GetGeneralScalar4e_Part11(leptons, 0, aZR, aZdI, 0);
}

double GetGeneralScalar4e_aZI_aZdI(LeptonVectors &leptons, double aZI, double aZdI)
{
   return GetGeneralScalar4e_Part11(leptons, aZI, 0, aZdI, 0);
}

double GetGeneralScalar4e_aZdR_ahR(LeptonVectors &leptons, double aZdR, double ahR)
{
   return GetGeneralScalar4e_Part12(leptons, 0, ahR, 0, aZdR);
}

double GetGeneralScalar4e_aZdR_ahI(LeptonVectors &leptons, double aZdR, double ahI)
{
   return GetGeneralScalar4e_Part12(leptons, ahI, 0, 0, aZdR);
}

double GetGeneralScalar4e_aZdI_ahR(LeptonVectors &leptons, double aZdI, double ahR)
{
   return GetGeneralScalar4e_Part12(leptons, 0, ahR, aZdI, 0);
}

double GetGeneralScalar4e_aZdI_ahI(LeptonVectors &leptons, double aZdI, double ahI)
{
   return GetGeneralScalar4e_Part12(leptons, ahI, 0, aZdI, 0);
}

double GetGeneralScalar4e_aZAR_aZAR(LeptonVectors &leptons, double aZAR)
{
   return GetGeneralScalar4e_Part14(leptons, 0, aZAR);
}

double GetGeneralScalar4e_aZAI_aZAR(LeptonVectors &leptons, double aZAI, double aZAR)
{
   return GetGeneralScalar4e_Part14(leptons, aZAI, aZAR)
      - GetGeneralScalar4e_Part14(leptons, 0, aZAR)
      - GetGeneralScalar4e_Part14(leptons, aZAI, 0);
}

double GetGeneralScalar4e_aZAI_aZAI(LeptonVectors &leptons, double aZAI)
{
   return GetGeneralScalar4e_Part14(leptons, aZAI, 0);
}

double GetGeneralScalar4e_aZAdR_aZAdR(LeptonVectors &leptons, double aZAdR)
{
   return GetGeneralScalar4e_Part15(leptons, 0, aZAdR);
}

double GetGeneralScalar4e_aZAdI_aZAdR(LeptonVectors &leptons, double aZAdI, double aZAdR)
{
   return GetGeneralScalar4e_Part15(leptons, aZAdI, aZAdR)
      - GetGeneralScalar4e_Part15(leptons, 0, aZAdR)
      - GetGeneralScalar4e_Part15(leptons, aZAdI, 0);
}

double GetGeneralScalar4e_aZAdI_aZAdI(LeptonVectors &leptons, double aZAdI)
{
   return GetGeneralScalar4e_Part15(leptons, aZAdI, 0);
}

double GetGeneralScalar4e_aZAR_aZAdR(LeptonVectors &leptons, double aZAR, double aZAdR)
{
   return GetGeneralScalar4e_Part17(leptons, 0, aZAR, 0, aZAdR);
}

double GetGeneralScalar4e_aZAI_aZAdR(LeptonVectors &leptons, double aZAI, double aZAdR)
{
   return GetGeneralScalar4e_Part17(leptons, aZAI, 0, 0, aZAdR);
}

double GetGeneralScalar4e_aZAR_aZAdI(LeptonVectors &leptons, double aZAR, double aZAdI)
{
   return GetGeneralScalar4e_Part17(leptons, 0, aZAR, aZAdI, 0);
}

double GetGeneralScalar4e_aZAI_aZAdI(LeptonVectors &leptons, double aZAI, double aZAdI)
{
   return GetGeneralScalar4e_Part17(leptons, aZAI, 0, aZAdI, 0);
}

double GetGeneralScalar4e_aAR_aZR(LeptonVectors &leptons, double aAR, double aZR)
{
   return GetGeneralScalar4e_Part20(leptons, 0, aAR, 0, aZR);
}

double GetGeneralScalar4e_aAR_aZI(LeptonVectors &leptons, double aAR, double aZI)
{
   return GetGeneralScalar4e_Part20(leptons, 0, aAR, aZI, 0);
}

double GetGeneralScalar4e_aAI_aZR(LeptonVectors &leptons, double aAI, double aZR)
{
   return GetGeneralScalar4e_Part20(leptons, aAI, 0, 0, aZR);
}

double GetGeneralScalar4e_aAI_aZI(LeptonVectors &leptons, double aAI, double aZI)
{
   return GetGeneralScalar4e_Part20(leptons, aAI, 0, aZI, 0);
}

double GetGeneralScalar4e_aAdR_aZdR(LeptonVectors &leptons, double aAdR, double aZdR)
{
   return GetGeneralScalar4e_Part21(leptons, 0, aAdR, 0, aZdR);
}

double GetGeneralScalar4e_aAdR_aZdI(LeptonVectors &leptons, double aAdR, double aZdI)
{
   return GetGeneralScalar4e_Part21(leptons, 0, aAdR, aZdI, 0);
}

double GetGeneralScalar4e_aAdI_aZdR(LeptonVectors &leptons, double aAdI, double aZdR)
{
   return GetGeneralScalar4e_Part21(leptons, aAdI, 0, 0, aZdR);
}

double GetGeneralScalar4e_aAdI_aZdI(LeptonVectors &leptons, double aAdI, double aZdI)
{
   return GetGeneralScalar4e_Part21(leptons, aAdI, 0, aZdI, 0);
}

double GetGeneralScalar4e_aAR_ahR(LeptonVectors &leptons, double aAR, double ahR)
{
   return GetGeneralScalar4e_Part22(leptons, 0, ahR, 0, aAR);
}

double GetGeneralScalar4e_aAR_ahI(LeptonVectors &leptons, double aAR, double ahI)
{
   return GetGeneralScalar4e_Part22(leptons, ahI, 0, 0, aAR);
}

double GetGeneralScalar4e_aAI_ahR(LeptonVectors &leptons, double aAI, double ahR)
{
   return GetGeneralScalar4e_Part22(leptons, 0, ahR, aAI, 0);
}

double GetGeneralScalar4e_aAI_ahI(LeptonVectors &leptons, double aAI, double ahI)
{
   return GetGeneralScalar4e_Part22(leptons, ahI, 0, aAI, 0);
}

double GetGeneralScalar4e_aAdR_aZR(LeptonVectors &leptons, double aAdR, double aZR)
{
   return GetGeneralScalar4e_Part23(leptons, 0, 0, 0, aZR, 0, aAdR, 0, 0);
}

double GetGeneralScalar4e_aAdR_aZI(LeptonVectors &leptons, double aAdR, double aZI)
{
   return GetGeneralScalar4e_Part23(leptons, 0, 0, aZI, 0, 0, aAdR, 0, 0);
}

double GetGeneralScalar4e_aAdI_aZR(LeptonVectors &leptons, double aAdI, double aZR)
{
   return GetGeneralScalar4e_Part23(leptons, 0, 0, 0, aZR, aAdI, 0, 0, 0);
}

double GetGeneralScalar4e_aAdI_aZI(LeptonVectors &leptons, double aAdI, double aZI)
{
   return GetGeneralScalar4e_Part23(leptons, 0, 0, aZI, 0, aAdI, 0, 0, 0);
}

double GetGeneralScalar4e_aAR_aZdR(LeptonVectors &leptons, double aAR, double aZdR)
{
   return GetGeneralScalar4e_Part23(leptons, 0, aAR, 0, 0, 0, 0, 0, aZdR);
}

double GetGeneralScalar4e_aAR_aZdI(LeptonVectors &leptons, double aAR, double aZdI)
{
   return GetGeneralScalar4e_Part23(leptons, 0, aAR, 0, 0, 0, 0, aZdI, 0);
}

double GetGeneralScalar4e_aAI_aZdR(LeptonVectors &leptons, double aAI, double aZdR)
{
   return GetGeneralScalar4e_Part23(leptons, aAI, 0, 0, 0, 0, 0, 0, aZdR);
}

double GetGeneralScalar4e_aAI_aZdI(LeptonVectors &leptons, double aAI, double aZdI)
{
   return GetGeneralScalar4e_Part23(leptons, aAI, 0, 0, 0, 0, 0, aZdI, 0);
}

double GetGeneralScalar4e_aAdR_ahR(LeptonVectors &leptons, double aAdR, double ahR)
{
   return GetGeneralScalar4e_Part24(leptons, 0, ahR, 0, aAdR);
}

double GetGeneralScalar4e_aAdR_ahI(LeptonVectors &leptons, double aAdR, double ahI)
{
   return GetGeneralScalar4e_Part24(leptons, ahI, 0, 0, aAdR);
}

double GetGeneralScalar4e_aAdI_ahR(LeptonVectors &leptons, double aAdI, double ahR)
{
   return GetGeneralScalar4e_Part24(leptons, 0, ahR, aAdI, 0);
}

double GetGeneralScalar4e_aAdI_ahI(LeptonVectors &leptons, double aAdI, double ahI)
{
   return GetGeneralScalar4e_Part24(leptons, ahI, 0, aAdI, 0);
}

double GetGeneralScalar4e_aAR_aZAR(LeptonVectors &leptons, double aAR, double aZAR)
{
   return GetGeneralScalar4e_Part26(leptons, 0, aAR, 0, aZAR);
}

double GetGeneralScalar4e_aAR_aZAI(LeptonVectors &leptons, double aAR, double aZAI)
{
   return GetGeneralScalar4e_Part26(leptons, 0, aAR, aZAI, 0);
}

double GetGeneralScalar4e_aAI_aZAR(LeptonVectors &leptons, double aAI, double aZAR)
{
   return GetGeneralScalar4e_Part26(leptons, aAI, 0, 0, aZAR);
}

double GetGeneralScalar4e_aAI_aZAI(LeptonVectors &leptons, double aAI, double aZAI)
{
   return GetGeneralScalar4e_Part26(leptons, aAI, 0, aZAI, 0);
}

double GetGeneralScalar4e_aAdR_aZAdR(LeptonVectors &leptons, double aAdR, double aZAdR)
{
   return GetGeneralScalar4e_Part27(leptons, 0, aAdR, 0, aZAdR);
}

double GetGeneralScalar4e_aAdR_aZAdI(LeptonVectors &leptons, double aAdR, double aZAdI)
{
   return GetGeneralScalar4e_Part27(leptons, 0, aAdR, aZAdI, 0);
}

double GetGeneralScalar4e_aAdI_aZAdR(LeptonVectors &leptons, double aAdI, double aZAdR)
{
   return GetGeneralScalar4e_Part27(leptons, aAdI, 0, 0, aZAdR);
}

double GetGeneralScalar4e_aAdI_aZAdI(LeptonVectors &leptons, double aAdI, double aZAdI)
{
   return GetGeneralScalar4e_Part27(leptons, aAdI, 0, aZAdI, 0);
}

double GetGeneralScalar4e_aAdR_aZAR(LeptonVectors &leptons, double aAdR, double aZAR)
{
   return GetGeneralScalar4e_Part29(leptons, 0, 0, 0, aZAR, 0, aAdR, 0, 0);
}

double GetGeneralScalar4e_aAdR_aZAI(LeptonVectors &leptons, double aAdR, double aZAI)
{
   return GetGeneralScalar4e_Part29(leptons, 0, 0, aZAI, 0, 0, aAdR, 0, 0);
}

double GetGeneralScalar4e_aAdI_aZAR(LeptonVectors &leptons, double aAdI, double aZAR)
{
   return GetGeneralScalar4e_Part29(leptons, 0, 0, 0, aZAR, aAdI, 0, 0, 0);
}

double GetGeneralScalar4e_aAdI_aZAI(LeptonVectors &leptons, double aAdI, double aZAI)
{
   return GetGeneralScalar4e_Part29(leptons, 0, 0, aZAI, 0, aAdI, 0, 0, 0);
}

double GetGeneralScalar4e_aAR_aZAdR(LeptonVectors &leptons, double aAR, double aZAdR)
{
   return GetGeneralScalar4e_Part29(leptons, 0, aAR, 0, 0, 0, 0, 0, aZAdR);
}

double GetGeneralScalar4e_aAR_aZAdI(LeptonVectors &leptons, double aAR, double aZAdI)
{
   return GetGeneralScalar4e_Part29(leptons, 0, aAR, 0, 0, 0, 0, aZAdI, 0);
}

double GetGeneralScalar4e_aAI_aZAdR(LeptonVectors &leptons, double aAI, double aZAdR)
{
   return GetGeneralScalar4e_Part29(leptons, aAI, 0, 0, 0, 0, 0, 0, aZAdR);
}

double GetGeneralScalar4e_aAI_aZAdI(LeptonVectors &leptons, double aAI, double aZAdI)
{
   return GetGeneralScalar4e_Part29(leptons, aAI, 0, 0, 0, 0, 0, aZAdI, 0);
}

double GetGeneralScalar4e_aZAR_aZR(LeptonVectors &leptons, double aZAR, double aZR)
{
   return GetGeneralScalar4e_Part32(leptons, 0, aZAR, 0, aZR);
}

double GetGeneralScalar4e_aZAR_aZI(LeptonVectors &leptons, double aZAR, double aZI)
{
   return GetGeneralScalar4e_Part32(leptons, 0, aZAR, aZI, 0);
}

double GetGeneralScalar4e_aZAI_aZR(LeptonVectors &leptons, double aZAI, double aZR)
{
   return GetGeneralScalar4e_Part32(leptons, aZAI, 0, 0, aZR);
}

double GetGeneralScalar4e_aZAI_aZI(LeptonVectors &leptons, double aZAI, double aZI)
{
   return GetGeneralScalar4e_Part32(leptons, aZAI, 0, aZI, 0);
}

double GetGeneralScalar4e_aZAdR_aZdR(LeptonVectors &leptons, double aZAdR, double aZdR)
{
   return GetGeneralScalar4e_Part33(leptons, 0, aZAdR, 0, aZdR);
}

double GetGeneralScalar4e_aZAdR_aZdI(LeptonVectors &leptons, double aZAdR, double aZdI)
{
   return GetGeneralScalar4e_Part33(leptons, 0, aZAdR, aZdI, 0);
}

double GetGeneralScalar4e_aZAdI_aZdR(LeptonVectors &leptons, double aZAdI, double aZdR)
{
   return GetGeneralScalar4e_Part33(leptons, aZAdI, 0, 0, aZdR);
}

double GetGeneralScalar4e_aZAdI_aZdI(LeptonVectors &leptons, double aZAdI, double aZdI)
{
   return GetGeneralScalar4e_Part33(leptons, aZAdI, 0, aZdI, 0);
}

double GetGeneralScalar4e_aZAR_ahR(LeptonVectors &leptons, double aZAR, double ahR)
{
   return GetGeneralScalar4e_Part34(leptons, 0, ahR, 0, aZAR);
}

double GetGeneralScalar4e_aZAR_ahI(LeptonVectors &leptons, double aZAR, double ahI)
{
   return GetGeneralScalar4e_Part34(leptons, ahI, 0, 0, aZAR);
}

double GetGeneralScalar4e_aZAI_ahR(LeptonVectors &leptons, double aZAI, double ahR)
{
   return GetGeneralScalar4e_Part34(leptons, 0, ahR, aZAI, 0);
}

double GetGeneralScalar4e_aZAI_ahI(LeptonVectors &leptons, double aZAI, double ahI)
{
   return GetGeneralScalar4e_Part34(leptons, ahI, 0, aZAI, 0);
}

double GetGeneralScalar4e_aZAdR_aZR(LeptonVectors &leptons, double aZAdR, double aZR)
{
   return GetGeneralScalar4e_Part35(leptons, 0, 0, 0, aZR, 0, aZAdR, 0, 0);
}

double GetGeneralScalar4e_aZAdR_aZI(LeptonVectors &leptons, double aZAdR, double aZI)
{
   return GetGeneralScalar4e_Part35(leptons, 0, 0, aZI, 0, 0, aZAdR, 0, 0);
}

double GetGeneralScalar4e_aZAdI_aZR(LeptonVectors &leptons, double aZAdI, double aZR)
{
   return GetGeneralScalar4e_Part35(leptons, 0, 0, 0, aZR, aZAdI, 0, 0, 0);
}

double GetGeneralScalar4e_aZAdI_aZI(LeptonVectors &leptons, double aZAdI, double aZI)
{
   return GetGeneralScalar4e_Part35(leptons, 0, 0, aZI, 0, aZAdI, 0, 0, 0);
}

double GetGeneralScalar4e_aZAR_aZdR(LeptonVectors &leptons, double aZAR, double aZdR)
{
   return GetGeneralScalar4e_Part35(leptons, 0, aZAR, 0, 0, 0, 0, 0, aZdR);
}

double GetGeneralScalar4e_aZAR_aZdI(LeptonVectors &leptons, double aZAR, double aZdI)
{
   return GetGeneralScalar4e_Part35(leptons, 0, aZAR, 0, 0, 0, 0, aZdI, 0);
}

double GetGeneralScalar4e_aZAI_aZdR(LeptonVectors &leptons, double aZAI, double aZdR)
{
   return GetGeneralScalar4e_Part35(leptons, aZAI, 0, 0, 0, 0, 0, 0, aZdR);
}

double GetGeneralScalar4e_aZAI_aZdI(LeptonVectors &leptons, double aZAI, double aZdI)
{
   return GetGeneralScalar4e_Part35(leptons, aZAI, 0, 0, 0, 0, 0, aZdI, 0);
}

double GetGeneralScalar4e_aZAdR_ahR(LeptonVectors &leptons, double aZAdR, double ahR)
{
   return GetGeneralScalar4e_Part36(leptons, 0, ahR, 0, aZAdR);
}

double GetGeneralScalar4e_aZAdR_ahI(LeptonVectors &leptons, double aZAdR, double ahI)
{
   return GetGeneralScalar4e_Part36(leptons, ahI, 0, 0, aZAdR);
}

double GetGeneralScalar4e_aZAdI_ahR(LeptonVectors &leptons, double aZAdI, double ahR)
{
   return GetGeneralScalar4e_Part36(leptons, 0, ahR, aZAdI, 0);
}

double GetGeneralScalar4e_aZAdI_ahI(LeptonVectors &leptons, double aZAdI, double ahI)
{
   return GetGeneralScalar4e_Part36(leptons, ahI, 0, aZAdI, 0);
}



