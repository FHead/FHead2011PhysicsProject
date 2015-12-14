#include <cmath>
#include <iostream>
#include <complex>
using namespace std;

#include "CalculateZAME.h"
#include "AngleConversion.h"
#include "Constants.h"

double GetSpin0ZAME(ZALeptonVectors &Leptons, GeneralScalarParameters &parameters)
{
   const double Pi = CONST_PI;
   
   const double M1 = (Leptons.Lepton1 + Leptons.Lepton2).GetMass();
   const double s = (Leptons.Lepton1 + Leptons.Lepton2 + Leptons.Photon).GetMass2();
   const double MH = sqrt(s);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;
   
   double A2ZAR = parameters.aZAR;
   double A2ZAI = parameters.aZAI;
   double A3ZAR = parameters.aZAdR;
   double A3ZAI = parameters.aZAdI;
   double A2AAR = parameters.aAR;
   double A2AAI = parameters.aAI;
   double A3AAR = parameters.aAdR;
   double A3AAI = parameters.aAdI;

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = Leptons.Lepton1;
   FourVector P4 = Leptons.Lepton2;
   FourVector P5 = Leptons.Photon;
   
   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C45 = P4 * P5;

   double Sqrt2 = sqrt(2);

   double SqrtC12 = sqrt(C12);
   double SqrtC13 = sqrt(C13);
   double SqrtC14 = sqrt(C14);
   double SqrtC15 = sqrt(C15);
   double SqrtC23 = sqrt(C23);
   double SqrtC24 = sqrt(C24);
   double SqrtC25 = sqrt(C25);
   double SqrtC34 = sqrt(C34);
   double SqrtC35 = sqrt(C35);
   double SqrtC45 = sqrt(C45);

   return 
      (pow(Pi,-5)*(1.0/s)*(1 - (M1*M1)*(1.0/s))*
    (-4*el*(gL - gR)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       ((A2ZAI*A3AAI + A2ZAR*A3AAR)*MZ*wZ +
         (A2ZAR*A3AAI - A2ZAI*A3AAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34))*
       ((C35*C35) - (C45*C45)) +
      4*el*(gL - gR)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       ((A2AAI*A3ZAI + A2AAR*A3ZAR)*MZ*wZ -
         (A2AAR*A3ZAI - A2AAI*A3ZAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34))*
       ((C35*C35) - (C45*C45)) +
      2*(pow(A2AAI,2) + pow(A2AAR,2))*(el*el)*(1/(vh*vh))*
       (1.0/C34)*((C35*C35) + (C45*C45)) +
      2*(pow(A3AAI,2) + pow(A3AAR,2))*(el*el)*(1/(vh*vh))*
       (1.0/C34)*((C35*C35) + (C45*C45)) +
      4*el*(gL + gR)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       ((A2AAR*A2ZAI - A2AAI*A2ZAR)*MZ*wZ +
         (A2AAI*A2ZAI + A2AAR*A2ZAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34))*
       ((C35*C35) + (C45*C45)) +
      4*el*(gL + gR)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       ((A3AAR*A3ZAI - A3AAI*A3ZAR)*MZ*wZ +
         (A3AAI*A3ZAI + A3AAR*A3ZAR)*(-MZ + Sqrt2*SqrtC34)*
          (MZ + Sqrt2*SqrtC34))*
       ((C35*C35) + (C45*C45)) -
      8*(A2ZAR*A3ZAI - A2ZAI*A3ZAR)*(gL - gR)*(gL + gR)*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       ((C35*C35) - (C45*C45))*C34 +
      4*(pow(A2ZAI,2) + pow(A2ZAR,2))*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       ((C35*C35) + (C45*C45))*C34 +
      4*(pow(A3ZAI,2) + pow(A3ZAR,2))*((gL*gL) + (gR*gR))*(1/(vh*vh))*
       pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C34,2),-1)*
       ((C35*C35) + (C45*C45))*C34))/4096.;
}

double GetSpin0ZAME(ZAEventParameters &Event, GeneralScalarParameters &parameters)
{
   const double Pi = CONST_PI;
   
   const double M1 = Event.ZMass;
   const double MH = Event.HMass;
   const double s = MH * MH;
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   const double Theta1 = Event.ThetaLL;
   const double Gamma = MH / (2 * M1) * (1 + (M1 * M1) / (MH * MH));
   const double Beta = GammaToBeta(Gamma);
   const double beta1 = Beta;

   double A2ZAR = parameters.aZAR;
   double A2ZAI = parameters.aZAI;
   double A3ZAR = parameters.aZAdR;
   double A3ZAI = parameters.aZAdI;
   double A2AAR = parameters.aAR;
   double A2AAI = parameters.aAI;
   double A3AAR = parameters.aAdR;
   double A3AAI = parameters.aAdI;

   return (pow(-1 + beta1,-2)*(beta1*beta1)*(M1*M1)*pow(Pi,-5)*(1.0/s)*
    (1 - (M1*M1)*(1.0/s))*(1/(vh*vh))*
    (-8*(gL - gR)*cos(Theta1)*(M1*M1)*
       ((A2AAR*A3ZAI - A2AAI*A3ZAR)*el*(M1 - MZ)*(M1 + MZ) -
         (A2AAI*A3ZAI + A2AAR*A3ZAR)*el*MZ*wZ +
         A2ZAR*(A3AAI*el*(M1 - MZ)*(M1 + MZ) + A3AAR*el*MZ*wZ +
            A3ZAI*(gL + gR)*(M1*M1)) -
         A2ZAI*(A3AAR*el*(M1 - MZ)*(M1 + MZ) - A3AAI*el*MZ*wZ +
            A3ZAR*(gL + gR)*(M1*M1))) +
      (3 + cos(2*Theta1))*(2*A2AAI*A2ZAI*el*(gL + gR)*(M1 - MZ)*(M1 + MZ)*
          (M1*M1) + 2*(A2AAR*A2ZAI - A2AAI*A2ZAR + A3AAR*A3ZAI -
            A3AAI*A3ZAR)*el*(gL + gR)*MZ*wZ*(M1*M1) +
         2*A3AAI*A3ZAI*el*gL*(M1*M1*M1*M1) + 2*A3AAR*A3ZAR*el*gL*(M1*M1*M1*M1) +
         2*A3AAI*A3ZAI*el*gR*(M1*M1*M1*M1) + 2*A3AAR*A3ZAR*el*gR*(M1*M1*M1*M1) +
         2*A2AAR*A2ZAR*el*(gL + gR)*(M1*M1*M1*M1) +
         2*pow(A3AAI,2)*(el*el)*(M1*M1*M1*M1) +
         2*pow(A3AAR,2)*(el*el)*(M1*M1*M1*M1) +
         pow(A2ZAI,2)*(gL*gL)*(M1*M1*M1*M1) +
         pow(A2ZAR,2)*(gL*gL)*(M1*M1*M1*M1) +
         pow(A3ZAI,2)*(gL*gL)*(M1*M1*M1*M1) +
         pow(A3ZAR,2)*(gL*gL)*(M1*M1*M1*M1) +
         pow(A2ZAI,2)*(gR*gR)*(M1*M1*M1*M1) +
         pow(A2ZAR,2)*(gR*gR)*(M1*M1*M1*M1) +
         pow(A3ZAI,2)*(gR*gR)*(M1*M1*M1*M1) +
         pow(A3ZAR,2)*(gR*gR)*(M1*M1*M1*M1) -
         2*A3AAI*A3ZAI*el*gL*(M1*M1)*(MZ*MZ) -
         2*A3AAR*A3ZAR*el*gL*(M1*M1)*(MZ*MZ) -
         2*A3AAI*A3ZAI*el*gR*(M1*M1)*(MZ*MZ) -
         2*A3AAR*A3ZAR*el*gR*(M1*M1)*(MZ*MZ) -
         2*A2AAR*A2ZAR*el*(gL + gR)*(M1*M1)*(MZ*MZ) -
         4*pow(A3AAI,2)*(el*el)*(M1*M1)*(MZ*MZ) -
         4*pow(A3AAR,2)*(el*el)*(M1*M1)*(MZ*MZ) +
         2*pow(A3AAI,2)*(el*el)*(MZ*MZ*MZ*MZ) +
         2*pow(A3AAR,2)*(el*el)*(MZ*MZ*MZ*MZ) +
         2*(pow(A2AAI,2) + pow(A2AAR,2) + pow(A3AAI,2) + pow(A3AAR,2))*
          (el*el)*(MZ*MZ)*(wZ*wZ) +
         2*pow(A2AAI,2)*(el*el)*((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ)) +
         2*pow(A2AAR,2)*(el*el)*((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*
    (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ)))))/8192.;
}

double GetSpin0ZAME_M1Only(ZAEventParameters &Event, GeneralScalarParameters &parameters)
{
   const double Pi = CONST_PI;
   
   const double M1 = Event.ZMass;
   const double MH = Event.HMass;
   const double s = MH * MH;
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;
   
   const double Gamma = MH / (2 * M1) * (1 + (M1 * M1) / (MH * MH));
   const double Beta = GammaToBeta(Gamma);
   const double beta1 = Beta;
   
   double A2ZAR = parameters.aZAR;
   double A2ZAI = parameters.aZAI;
   double A3ZAR = parameters.aZAdR;
   double A3ZAI = parameters.aZAdI;
   double A2AAR = parameters.aAR;
   double A2AAI = parameters.aAI;
   double A3AAR = parameters.aAdR;
   double A3AAI = parameters.aAdI;

   return (pow(-1 + beta1,-2)*(beta1*beta1)*(M1*M1)*pow(Pi,-5)*(1.0/s)*
    (1 - (M1*M1)*(1.0/s))*(1/(vh*vh))*
    (2*A2AAI*A2ZAI*el*(gL + gR)*(M1 - MZ)*(M1 + MZ)*(M1*M1) +
      2*(A2AAR*A2ZAI - A2AAI*A2ZAR + A3AAR*A3ZAI - A3AAI*A3ZAR)*el*
       (gL + gR)*MZ*wZ*(M1*M1) + 2*A3AAI*A3ZAI*el*gL*(M1*M1*M1*M1) +
      2*A3AAR*A3ZAR*el*gL*(M1*M1*M1*M1) + 2*A3AAI*A3ZAI*el*gR*(M1*M1*M1*M1) +
      2*A3AAR*A3ZAR*el*gR*(M1*M1*M1*M1) +
      2*A2AAR*A2ZAR*el*(gL + gR)*(M1*M1*M1*M1) +
      2*pow(A3AAI,2)*(el*el)*(M1*M1*M1*M1) +
      2*pow(A3AAR,2)*(el*el)*(M1*M1*M1*M1) +
      pow(A2ZAI,2)*(gL*gL)*(M1*M1*M1*M1) + pow(A2ZAR,2)*(gL*gL)*(M1*M1*M1*M1) +
      pow(A3ZAI,2)*(gL*gL)*(M1*M1*M1*M1) + pow(A3ZAR,2)*(gL*gL)*(M1*M1*M1*M1) +
      pow(A2ZAI,2)*(gR*gR)*(M1*M1*M1*M1) + pow(A2ZAR,2)*(gR*gR)*(M1*M1*M1*M1) +
      pow(A3ZAI,2)*(gR*gR)*(M1*M1*M1*M1) + pow(A3ZAR,2)*(gR*gR)*(M1*M1*M1*M1) -
      2*A3AAI*A3ZAI*el*gL*(M1*M1)*(MZ*MZ) -
      2*A3AAR*A3ZAR*el*gL*(M1*M1)*(MZ*MZ) -
      2*A3AAI*A3ZAI*el*gR*(M1*M1)*(MZ*MZ) -
      2*A3AAR*A3ZAR*el*gR*(M1*M1)*(MZ*MZ) -
      2*A2AAR*A2ZAR*el*(gL + gR)*(M1*M1)*(MZ*MZ) -
      4*pow(A3AAI,2)*(el*el)*(M1*M1)*(MZ*MZ) -
      4*pow(A3AAR,2)*(el*el)*(M1*M1)*(MZ*MZ) +
      2*pow(A3AAI,2)*(el*el)*(MZ*MZ*MZ*MZ) +
      2*pow(A3AAR,2)*(el*el)*(MZ*MZ*MZ*MZ) +
      2*(pow(A2AAI,2) + pow(A2AAR,2) + pow(A3AAI,2) + pow(A3AAR,2))*
       (el*el)*(MZ*MZ)*(wZ*wZ) +
      2*pow(A2AAI,2)*(el*el)*((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ)) +
      2*pow(A2AAR,2)*(el*el)*((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ)))*
    (1.0/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ)))))/1536.;
}

double GetqqZAMEWrong(ZALeptonVectors &Leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   const double M1 = (Leptons.Lepton1 + Leptons.Lepton2).GetMass();
   const double s = (Leptons.Lepton1 + Leptons.Lepton2 + Leptons.Photon).GetMass2();
   const double MH = sqrt(s);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = Leptons.Lepton1;
   FourVector P4 = Leptons.Lepton2;
   FourVector P5 = Leptons.Photon;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   if(Reverse == true)
      swap(P1, P2);

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C45 = P4 * P5;
   
   double Sqrt2 = sqrt(2);

   double SqrtC12 = sqrt(C12);
   double SqrtC13 = sqrt(C13);
   double SqrtC14 = sqrt(C14);
   double SqrtC15 = sqrt(C15);
   double SqrtC23 = sqrt(C23);
   double SqrtC24 = sqrt(C24);
   double SqrtC25 = sqrt(C25);
   double SqrtC34 = sqrt(C34);
   double SqrtC35 = sqrt(C35);
   double SqrtC45 = sqrt(C45);

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1345 = EPS(P1, P3, P4, P5);
   double E2345 = EPS(P2, P3, P4, P5);

   return 
(pow(Pi,-5)*(1.0/s)*(1 - (M1*M1)*(1.0/s))*
    (((gqL - gqR)*(gL - gR)*(el*el)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         (1.0/C12)*(1.0/C35)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12) + 
           2*(gqL + gqR)*(gL + gR)*C12)*
         (-(C14*C23) + C13*C24))/3. + 
      ((el*el)*pow((MZ*MZ)*(wZ*wZ) + 
           pow(-(MZ*MZ) + 2*C12,2),-1)*pow(C12,-2)*
         (1.0/C35)*(4*((gqL*gqL) + (gqR*gqR))*
            ((gL*gL) + (gR*gR))*(C12*C12) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*C12)*
         (C14*C23 + C13*C24))/6. + 
      (el*(gqL - gqR)*MZ*wZ*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C13)*
         pow(2*C12 - 2*(C15 + C25),-1)*
         (el*(gL + gR)*((MZ*MZ)*(wZ*wZ) + 
              pow(-(MZ*MZ) + 2*C12,2)) + 
           2*((gL*gL) + (gR*gR))*
            (Sqrt2*SqrtC12 - 
              Sqrt2*SqrtC45)*
            (Sqrt2*SqrtC12 + 
              Sqrt2*SqrtC45)*C12)*
         (E1345*C12 + E2345*C12 - 
           (E1345 + E2345)*C12 + 
           E1245*C13 + E1235*C14 + 
           E1234*C15 + (-E1245)*C23 + 
           E1235*C24 + 
           (-E1235)*(C14 + C24) + 
           (-E1234)*C25 + 
           E1234*(C15 + C25) + 
           E1245*(C13 + 2*C15 + C23 - 
              2*C35)))/3. + 
      ((gqL - gqR)*(gL - gR)*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C13)*(1.0/C45)*
         (-(C25*C34) + C24*C35)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45) + 
           2*(gqL + gqR)*(gL + gR)*C45))/3. - 
      (el*(gqL - gqR)*MZ*wZ*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C35)*
         pow(-2*(C14 + C15) + 2*C45,-1)*
         (el*(gL + gR)*((MZ*MZ)*(wZ*wZ) + 
              pow(-(MZ*MZ) + 2*C12,2)) + 
           2*((gL*gL) + (gR*gR))*
            (Sqrt2*SqrtC12 - 
              Sqrt2*SqrtC45)*
            (Sqrt2*SqrtC12 + 
              Sqrt2*SqrtC45)*C12)*
         ((-E2345)*C14 + E2345*C15 + 
           E2345*(C14 + C15) + 
           (-E1345)*C24 + (-E1345)*C25 + 
           E1345*(C24 + C25) + 
           (-E1245)*C34 + E1245*C35 + 
           E1245*(-2*(C13 + C15) + C34 + 
              C35) + E1234*C45 + 
           E1235*C45 + 
           ((-E1234) + (-E1235))*C45))/3. + 
      ((eq*eq)*pow((MZ*MZ)*(wZ*wZ) + 
           pow(-(MZ*MZ) + 2*C45,2),-1)*(1.0/C13)*
         pow(C45,-2)*(C25*C34 + C24*C35)*
         (4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            (C45*C45) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45)*C45))/6. + 
      (2*(gqL - gqR)*(gL - gR)*(el*el)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         (1.0/C12)*pow(2*C12 - 2*(C15 + C25),-2)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12) + 
           2*(gqL + gqR)*(gL + gR)*C12)*
         (-2*C12*(C14 + C24)*C25 - 
           (C15*C24 - C14*C25)*
            (2*C12 - 2*(C15 + C25)) + 
           2*C12*C15*(C14 + C24 - C45) + 
           2*C12*C25*C45))/3. + 
      (el*(gqL - gqR)*(gL - gR)*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C13)*(1.0/C35)*
         ((MZ*MZ)*(wZ*wZ)*
            (el*(-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45) + 
              2*(gL + gR)*C12) + 
           (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*
            (-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45)*
            (-(el*(MZ*MZ)) + 2*(el + gL + gR)*C12))*
         (C14*C15*C23 - 2*(C15*C15)*C24 - 
           2*C13*C15*C24 + 
           C13*C14*C25 + 
           2*C14*C15*C25 - 
           C15*C25*C34 - 
           (-2*(C13 + C15)*C24 + 
              C14*(C12 + C25))*C35 + 
           C13*C25*C45))/3. + 
      ((gqL - gqR)*(gL - gR)*(el*el)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         (1.0/C12)*pow(2*C12 - 2*(C15 + C25),-1)*
         (1.0/C35)*(2*el*eq*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12) + 
           2*(gqL + gqR)*(gL + gR)*C12)*
         (8*(C15*C24 - C14*C25)*
            (C13 + C15 + C23 + C25 - C35) + 
           8*(C12*(C13 + C15) + 
              (-C12 + C15)*C23 - 
              (C12 + C13)*C25)*C45))/12. + 
      ((el*el)*pow((MZ*MZ)*(wZ*wZ) + 
           pow(-(MZ*MZ) + 2*C12,2),-1)*pow(C12,-2)*
         pow(2*C12 - 2*(C15 + C25),-1)*(1.0/C35)*
         (4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            (C12*C12) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*C12)*
         (C12*C15*C34 + C12*C25*C34 - 
           2*C15*C25*C34 + 
           (C15 + C25)*
            ((C13 + C15)*C24 + 
              C14*(C23 + C25) - C12*C34) - 
           C12*C14*C35 - C12*C24*C35 + 
           C15*C24*C35 + C14*C25*C35 + 
           (C14 + C24)*
            (-(C15*C23) - 
              (C13 + 2*C15)*C25 + C12*C35) + 
           (C15*(C12 + C23) + 
              (C12 + C13)*C25 + 
              C12*(C13 + C23 - 2*C35))*C45))/
       3. + (el*(gqL - gqR)*(gL - gR)*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C13)*
         pow(2*C12 - 2*(C15 + C25),-1)*
         ((MZ*MZ)*(wZ*wZ)*
            (el*(-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45) + 
              2*(gL + gR)*C12) + 
           (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*
            (-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45)*
            (-(el*(MZ*MZ)) + 2*(el + gL + gR)*C12))*
         (2*C12*C14*C15 - 2*(C15*C15)*C24 + 
           2*C12*C15*C24 - 
           C15*(C13 + C23)*C24 - 
           2*C12*C15*(C14 + C24) + 
           C15*C23*(C14 + C24) - 
           C12*C15*C34 + 
           (C15 + C25)*
            (C14*C23 + C13*C24 - 
              C12*C34) - C12*C14*C35 - 
           C12*C24*C35 + 
           2*C15*C24*C35 + 
           C12*(C14 + C24)*C35 - 
           C25*(C13*(C14 + C24) + 
              C12*(4*C14 - 5*C34) + 
              4*C15*C34 + 
              C14*(C13 + C23 - 
                 2*(C15 + C35))) + 
           (C12*C13 - C12*C23 + 
              C12*(C13 + 2*C15 + C23 - 
                 2*C35))*C45))/3. + 
      (el*(gqL - gqR)*MZ*wZ*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C13)*(1.0/C35)*
         (el*(gL + gR)*((MZ*MZ)*(wZ*wZ) + 
              pow(-(MZ*MZ) + 2*C12,2)) + 
           2*((gL*gL) + (gR*gR))*
            (Sqrt2*SqrtC12 - 
              Sqrt2*SqrtC45)*
            (Sqrt2*SqrtC12 + 
              Sqrt2*SqrtC45)*C12)*
         (E2345*C15 + E1245*C35 + 
           (-E1235)*(C14 + C45)))/3. - 
      ((el*el)*pow((MZ*MZ)*(wZ*wZ) + 
           pow(-(MZ*MZ) + 2*C12,2),-1)*pow(C12,-2)*
         pow(2*C12 - 2*(C15 + C25),-2)*
         (4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            (C12*C12) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*C12)*
         (2*C12*(C15*C24 + C14*C25) - 
           2*((C15 + C25)*
               (C15*C24 + C14*C25) + 
              (C12 - 2*C15)*C25*
               (C14 + C24 - C45)) + 
           2*C12*C15*(-C14 - C24 + C45)))/3. + 
      (el*(gL - gR)*MZ*wZ*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C13)*(1.0/C35)*
         (1.0/C45)*(E1245*C13 + 
           E1234*C15 + 
           (-E1345)*(C12 + C25))*
         (4*(gqL + gqR)*(gL + gR)*
            (Sqrt2*SqrtC12 - 
              Sqrt2*SqrtC45)*
            (Sqrt2*SqrtC12 + 
              Sqrt2*SqrtC45)*C12*C45 + 
           el*(-4*eq*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C45,2))*C12 + 
              2*gqL*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C12,2))*C45 + 
              2*gqR*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C12,2))*C45)))/6. + 
      (el*(gL - gR)*MZ*wZ*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C13)*
         pow(2*C12 - 2*(C15 + C25),-1)*(1.0/C45)*
         (E1345*C12 + E2345*C12 - 
           (E1345 + E2345)*C12 + 
           E1245*C13 + E1235*C14 + 
           E1234*C15 + (-E1245)*C23 + 
           E1235*C24 + 
           (-E1235)*(C14 + C24) + 
           (-E1234)*C25 + 
           E1234*(C15 + C25) + 
           E1245*(C13 + 2*C15 + C23 - 
              2*C35))*(4*(gqL + gqR)*(gL + gR)*
            (Sqrt2*SqrtC12 - 
              Sqrt2*SqrtC45)*
            (Sqrt2*SqrtC12 + 
              Sqrt2*SqrtC45)*C12*C45 + 
           el*(-4*eq*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C45,2))*C12 + 
              2*gqL*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C12,2))*C45 + 
              2*gqR*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C12,2))*C45)))/6. - 
      (el*(gL - gR)*MZ*wZ*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C35)*(1.0/C45)*
         pow(-2*(C14 + C15) + 2*C45,-1)*
         (E2345*C14 + E2345*C15 + 
           E2345*(C14 + C15) + 
           (-E1345)*C24 + E1345*C25 + 
           (-E1345)*(C24 + C25) + 
           E1245*C34 + E1245*C35 + 
           E1245*(-2*(C13 + C15) + C34 + 
              C35) + E1234*C45 + 
           (-E1235)*C45 - 
           ((-E1234) + (-E1235))*C45)*
         (4*(gqL + gqR)*(gL + gR)*
            (Sqrt2*SqrtC12 - 
              Sqrt2*SqrtC45)*
            (Sqrt2*SqrtC12 + 
              Sqrt2*SqrtC45)*C12*C45 + 
           el*(-4*eq*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C45,2))*C12 + 
              2*gqL*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C12,2))*C45 + 
              2*gqR*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C12,2))*C45)))/6. + 
      (el*(eq*eq)*pow((MZ*MZ)*(wZ*wZ) + 
           pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C13)*(1.0/C35)*
         (1.0/C45)*(-(C14*C15*C23) - 
           2*(C15*C15)*C24 - 
           2*C13*C15*C24 - 
           C13*C14*C25 - 
           2*C14*C15*C25 + 
           C15*C25*C34 + 
           (2*(C13 + C15)*C24 + 
              C14*(C12 + C25))*C35 - 
           C13*C25*C45)*
         (4*eq*(el*el)*((MZ*MZ)*(wZ*wZ) + 
              pow(-(MZ*MZ) + 2*C12,2))*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2)) + 
           4*(gqL + gqR)*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45))*C12*C45 + 
           el*(gL + gR)*(4*eq*(-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
               C12 + 2*(gqL + gqR)*
               ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2))*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45)*C45)))/6. + 
      (el*(eq*eq)*pow((MZ*MZ)*(wZ*wZ) + 
           pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C13)*
         pow(2*C12 - 2*(C15 + C25),-1)*(1.0/C45)*
         (2*C12*C14*C15 - 
           2*(C15*C15)*C24 + 
           2*C12*C15*C24 - 
           C15*(C13 + C23)*C24 - 
           2*C12*C15*(C14 + C24) + 
           C15*C23*(C14 + C24) - 
           C12*C15*C34 + 
           (C15 + C25)*
            (C14*C23 + C13*C24 - 
              C12*C34) - 
           C25*(C13*(C14 + C24) - 
              4*C15*C34 + 
              C12*(-4*C14 + 3*C34) + 
              C14*(C13 + 6*C15 + C23 - 
                 2*C35)) - C12*C14*C35 - 
           C12*C24*C35 + 
           2*C15*C24*C35 + 
           C12*(C14 + C24)*C35 + 
           (C12*C13 - C12*C23 + 
              C12*(C13 + 2*C15 + C23 - 
                 2*C35))*C45)*
         (4*eq*(el*el)*((MZ*MZ)*(wZ*wZ) + 
              pow(-(MZ*MZ) + 2*C12,2))*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2)) + 
           4*(gqL + gqR)*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45))*C12*C45 + 
           el*(gL + gR)*(4*eq*(-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
               C12 + 2*(gqL + gqR)*
               ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2))*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45)*C45)))/6. + 
      (el*(eq*eq)*pow((MZ*MZ)*(wZ*wZ) + 
           pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*pow(2*C12 - 2*(C15 + C25),-1)*
         (1.0/C45)*pow(-2*(C14 + C15) + 2*C45,
          -1)*(4*eq*(el*el)*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2))*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2)) + 
           4*(gqL + gqR)*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45))*C12*C45 
+ el*(gL + gR)*(4*eq*(-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
               C12 + 2*(gqL + gqR)*
               ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2))*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45)*C45))*
         (-4*C12*C14*C15 + 
           2*(C15*C15)*C24 - 
           2*C12*C15*C24 - 
           2*C12*C14*C25 + 
           6*C14*C15*C25 - 
           (C14 + C15)*(C14 + C24)*C25 + 
           C15*(C14 + C24)*(C24 + C25) + 
           C15*C24*
            (C14 + C15 + C24 + C25) + 
           C14*C25*
            (C14 + C15 + C24 + C25) + 
           C12*C14*C45 + 
           3*C12*C15*C45 + 
           C12*C24*C45 - 
           2*C15*C24*C45 - 
           C12*(C14 + C24)*C45 + 
           C12*C25*C45 - 
           2*C14*C25*C45 - 
           4*C15*C25*C45 + 
           (C12*(C14 + C15) - 
              C12*(-2*C12 + C24 + C25) - 
              C12*(C14 + 3*C15 + C24 + 
                 C25 - 2*C45))*C45 + 
           (C15 + C25)*
            (-((C14 + C15)*C24) - 
              C14*(C24 + C25) + C12*C45)))/3. 
+ ((eq*eq)*pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C13)*pow(C45,-2)*
         pow(-2*(C14 + C15) + 2*C45,-1)*
         (4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            (C45*C45) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45)*C45)*
         (-2*C14*C15*C23 + 
           C13*C15*C24 - 
           C15*(C14 + C15)*C24 + 
           C13*C14*C25 - 
           C14*(C14 + C15)*C25 + 
           C12*C15*C34 + 
           (C14 + C15)*C25*C34 + 
           C12*C14*C35 + 
           (C14 + C15)*C24*C35 - 
           C12*C15*C45 + C15*C23*C45 + 
           (C14*(-C12 + C23) - C13*C24)*
            C45 - C13*C25*C45 + 
           (-((C14 + C15)*C23) + 
              C12*(-2*C13 + C34 + C35))*C45 
+ (C24 + C25)*(-(C15*C34) - 
              C14*(-2*C15 + C35) + C13*C45)))/
       3. + (2*(gqL - gqR)*(gL - gR)*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C13)*(1.0/C45)*
         pow(-2*(C14 + C15) + 2*C45,-1)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45) + 
           2*(gqL + gqR)*(gL + gR)*C45)*
         (C14*C25*
            (C13 + C14 + C15 - C34 - C35) + 
           C15*C24*
            (-C13 - C14 - C15 + C34 + C35) + 
           C12*(C15*(C34 - C45) + 
              (C14 - C34)*C45 + 
              C35*(-C14 + C45))))/3. + 
      (el*(gqL - gqR)*(gL - gR)*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C35)*
         pow(-2*(C14 + C15) + 2*C45,-1)*
         ((MZ*MZ)*(wZ*wZ)*
            (el*(-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45) + 
              2*(gL + gR)*C12) + 
           (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*
            (-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45)*
            (-(el*(MZ*MZ)) + 2*(el + gL + gR)*C12))*
         ((5*C14*C23 - C12*C34)*C45 + 
           (-((C14 + C15)*C23) + 
              (C13 + 2*C15)*(C24 + C25) + 
              C12*(-2*(C13 + C15) + C34 + 
                 C35))*C45 + 
           C35*(-(C14*(C24 + C25)) + 
              C12*C45) - 
           C24*(-((C14 + C15)*C35) + 
              C15*(-2*(C13 + C15) + C34 + 
                 C35) + (C13 + 2*C15)*C45) - 
           C25*(-((C14 + C15)*C34) + 
              C14*(-2*C13 + 2*C15 + C34 + 
                 C35 - 4*C45) + 
              (C13 + 2*C15)*C45) + 
           C15*((C24 + C25)*C34 - 
              C23*(4*C14 + C45))))/3. - 
      (2*el*(gqL - gqR)*MZ*wZ*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*pow(2*C12 - 2*(C15 + C25),-1)*
         pow(-2*(C14 + C15) + 2*C45,-1)*
         (el*(gL + gR)*((MZ*MZ)*(wZ*wZ) + 
              pow(-(MZ*MZ) + 2*C12,2)) + 
           2*((gL*gL) + (gR*gR))*
            (Sqrt2*SqrtC12 - 
              Sqrt2*SqrtC45)*
            (Sqrt2*SqrtC12 + 
              Sqrt2*SqrtC45)*C12)*
         ((-E1245)*C14 + E1245*C15 + 
           (-E1245)*(C14 + C15) + 
           (-E1245)*C24 + 
           E1245*(C14 + C24) + 
           (-E1245)*C25 + 
           (-E1245)*(C15 + C25) + 
           E1245*(C24 + C25) + 
           E1245*(C14 + C15 + C24 + 
              C25 - 2*(C12 - C15 + C45))))/3. + 
      (el*(gL - gR)*MZ*wZ*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*pow(2*C12 - 2*(C15 + C25),-1)*
         (1.0/C45)*pow(-2*(C14 + C15) + 2*C45,
          -1)*(4*(gqL + gqR)*(gL + gR)*
            (Sqrt2*SqrtC12 - 
              Sqrt2*SqrtC45)*
            (Sqrt2*SqrtC12 + 
              Sqrt2*SqrtC45)*C12*C45 + 
           el*(-4*eq*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C45,2))*C12 + 
              2*gqL*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C12,2))*C45 + 
              2*gqR*((MZ*MZ)*(wZ*wZ) + 
                 pow(-(MZ*MZ) + 2*C12,2))*C45))*
         (E1245*C14 + E1245*C15 + 
           (-E1245)*(C14 + C15) + 
           E1245*C24 + 
           (-E1245)*(C14 + C24) + 
           (-E1245)*C25 + 
           (-E1245)*(C15 + C25) + 
           E1245*(C24 + C25) + 
           E1245*(C14 + C15 + C24 + 
              C25 - 2*(C12 - C15 + C45))))/3. + 
      ((eq*eq)*pow((MZ*MZ)*(wZ*wZ) + 
           pow(-(MZ*MZ) + 2*C45,2),-1)*pow(C45,-2)*
         pow(-2*(C14 + C15) + 2*C45,-2)*
         (4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            (C45*C45) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45)*C45)*
         (-2*C12*C14*C45 - 
           C14*C25*
            (-2*(C14 + C15) + 2*C45) + 
           2*(C24 + C25)*
            (C14*C45 + C15*(-2*C14 + C45)) + 
           C15*(-2*C12*(-2*C14 + C45) - 
              C24*(-2*(C14 + C15) + 2*C45))))/3. + 
      (2*(gqL - gqR)*(gL - gR)*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C45)*pow(-2*(C14 + C15) + 2*C45,
          -2)*(2*el*eq*(-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45) + 
           2*(gqL + gqR)*(gL + gR)*C45)*
         (2*C12*C14*C45 + 
           C14*C25*
            (-2*(C14 + C15) + 2*C45) + 
           (C24 + C25)*
            (-2*C14*C45 + 2*C15*C45) - 
           C15*(2*C12*C45 + 
              C24*(-2*(C14 + C15) + 2*C45))))/3. + 
      (el*(eq*eq)*pow((MZ*MZ)*(wZ*wZ) + 
           pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*(1.0/C35)*(1.0/C45)*
         pow(-2*(C14 + C15) + 2*C45,-1)*
         (4*eq*(el*el)*((MZ*MZ)*(wZ*wZ) + 
              pow(-(MZ*MZ) + 2*C12,2))*
            ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2)) + 
           4*(gqL + gqR)*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45))*C12*C45 
+ el*(gL + gR)*(4*eq*(-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2))*
               C12 + 2*(gqL + gqR)*
               ((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2))*
               (-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45)*C45))*
         (-((3*C14*C23 + C12*C34)*C45) + 
           (-((C14 + C15)*C23) + 
              (C13 + 2*C15)*(C24 + C25) + 
              C12*(-2*(C13 + C15) + C34 + 
                 C35))*C45 + 
           C35*(-(C14*(C24 + C25)) + 
              C12*C45) - 
           C24*(-((C14 + C15)*C35) + 
              C15*(-2*(C13 + C15) + C34 + 
                 C35) + (C13 + 2*C15)*C45) + 
           C15*((C24 + C25)*C34 - 
              C23*(-4*C14 + C45)) - 
           C25*(-((C14 + C15)*C34) + 
              (C13 + 2*C15)*C45 + 
              C14*(-2*C13 - 6*C15 + C34 + 
                 C35 + 4*C45))))/6. + 
      (2*el*(gqL - gqR)*(gL - gR)*(eq*eq)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C12,2),-1)*
         pow((MZ*MZ)*(wZ*wZ) + pow(-(MZ*MZ) + 2*C45,2),-1)*
         (1.0/C12)*pow(2*C12 - 2*(C15 + C25),-1)*
         pow(-2*(C14 + C15) + 2*C45,-1)*
         ((MZ*MZ)*(wZ*wZ)*
            (el*(-MZ + Sqrt2*SqrtC45)*
               (MZ + Sqrt2*SqrtC45) + 
              2*(gL + gR)*C12) + 
           (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*
            (-MZ + Sqrt2*SqrtC45)*
            (MZ + Sqrt2*SqrtC45)*
            (-(el*(MZ*MZ)) + 2*(el + gL + gR)*C12))*
         (-((C12*(C14 + C15) - 
                C12*(-2*C12 + C24 + C25) - 
                C12*(C14 + 3*C15 + C24 + 
                   C25 - 2*C45))*C45) + 
           (C15 + C25)*
            ((C14 + C15)*C24 + 
              C14*(C24 + C25) - C12*C45) + 
           (C14 + C24)*
            (-(C15*(C24 + C25)) + C12*C45) - 
           C12*(-5*C15*C45 + 
              C14*(4*C15 + C45)) - 
           C24*(2*(C15*C15) + C12*C45 + 
              C15*(C14 + C15 + C24 + C25 - 
                 2*(C12 + C45))) + 
           C25*((C14 + C15)*(C14 + C24) - 
              4*C15*C45 - 
              C12*(-2*C14 + C45) + 
              C14*(-C14 - C15 - C24 - C25 + 
                 2*(C15 + C45)))))/3.))/4096.;
}

double GetqqZAME(ZALeptonVectors &Leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   const double M1 = (Leptons.Lepton1 + Leptons.Lepton2).GetMass();
   const double s = (Leptons.Lepton1 + Leptons.Lepton2 + Leptons.Photon).GetMass2();
   const double MH = sqrt(s);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = Leptons.Lepton1;
   FourVector P4 = Leptons.Lepton2;
   FourVector P5 = Leptons.Photon;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   if(Reverse == true)
      swap(P1, P2);

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C45 = P4 * P5;
   
   double Sqrt2 = sqrt(2);

   double SqrtC12 = sqrt(C12);
   double SqrtC13 = sqrt(C13);
   double SqrtC14 = sqrt(C14);
   double SqrtC15 = sqrt(C15);
   double SqrtC23 = sqrt(C23);
   double SqrtC24 = sqrt(C24);
   double SqrtC25 = sqrt(C25);
   double SqrtC34 = sqrt(C34);
   double SqrtC35 = sqrt(C35);
   double SqrtC45 = sqrt(C45);

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1345 = EPS(P1, P3, P4, P5);
   double E2345 = EPS(P2, P3, P4, P5);

   double MZMZC12 = MZ * MZ - 2 * C12;
   double MZMZC34 = MZ * MZ - 2 * C34;
   double MZMZC45 = MZ * MZ - 2 * C45;
   double iMZMZwZwZMZMZC12 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC12 * MZMZC12), -1);
   double iMZMZwZwZMZMZC34 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC34 * MZMZC34), -1);
   double iMZMZwZwZMZMZC45 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC45 * MZMZC45), -1);
   
   return 
(pow(Pi,-5)*(1.0/s)*(1 - (M1*M1)*(1.0/s))*
    (((gqL - gqR)*(gL - gR)*(el*el)*
         iMZMZwZwZMZMZC12*
         (1.0/C12)*(1.0/C45)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12) + 
           2*(gqL + gqR)*(gL + gR)*C12)*
         (C15*C23 - C13*C25))/3. + 
((el*el)*iMZMZwZwZMZMZC12*(1.0/C12/C12)*
         (1.0/C45)*(4*((gqL*gqL) + (gqR*gqR))*
            ((gL*gL) + (gR*gR))*(C12*C12) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*C12)*
         (C15*C23 + C13*C25))/6. + 
      ((gqL - gqR)*(gL - gR)*(el*el)*
         iMZMZwZwZMZMZC12*
         (1.0/C12)*(1.0/C35)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12) + 
           2*(gqL + gqR)*(gL + gR)*C12)*
         (-(C15*C24) + C14*C25))/3. + 
((el*el)*iMZMZwZwZMZMZC12*(1.0/C12/C12)*
         (1.0/C35)*(4*((gqL*gqL) + (gqR*gqR))*
            ((gL*gL) + (gR*gR))*(C12*C12) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*C12)*
         (C15*C24 + C14*C25))/6. + 
(el*eq*(gL-gR)*MZ*wZ*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C45)*((-E1235)*C14 + 
           E1234*C15 + 
           (-E1345)*(C12 + C24))*
         (4*(gL + gR)*((gqL*gqL) + (gqR*gqR))*C12*C34 + 
           el*eq*(gqL + gqR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34)))/6. + 
(el*eq*(gL-gR)*MZ*wZ*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C45)*(E2345*(C12 + C14) + 
           (-E1235)*C24 + E1234*C25)*
         (4*(gL + gR)*((gqL*gqL) + (gqR*gqR))*C12*C34 + 
           el*eq*(gqL + gqR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34)))/6. - 
      (el*eq*(gqL - gqR)*MZ*wZ*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C45)*((-E2345)*C14 + 
           E1245*C23)*
         (4*(gqL + gqR)*((gL*gL) + (gR*gR))*C12*C34 + 
           el*eq*(gL + gR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34)))/6. - 
      (el*eq*(gqL - gqR)*MZ*wZ*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C35)*((-E2345)*C13 + 
           (-E1235)*C24)*
         (4*(gqL + gqR)*((gL*gL) + (gR*gR))*C12*C34 + 
           el*eq*(gL + gR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34)))/6. + 
(el*eq*(gL-gR)*MZ*wZ*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C35)*(4*(gL + gR)*((gqL*gqL) + (gqR*gqR))*
            C12*C34 + 
           el*eq*(gqL + gqR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34))*
         (E2345*C13 + 
           (-E1235)*(C14 + C34) + 
           E1234*C35))/6. + 
      (el*eq*(gqL - gqR)*MZ*wZ*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C35)*(4*(gqL + gqR)*((gL*gL) + (gR*gR))*
            C12*C34 + 
           el*eq*(gL + gR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34))*
         (E2345*C13 + 
           (-E1235)*(C14 + C34) + 
           E1234*C35))/6. + 
(el*eq*(gL-gR)*MZ*wZ*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C35)*(4*(gL + gR)*((gqL*gqL) + (gqR*gqR))*
            C12*C34 + 
           el*eq*(gqL + gqR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34))*
         ((-E1345)*C23 + 
           (-E1235)*(C24 + C34) + 
           E1234*C35))/6. + 
      (el*eq*(gqL - gqR)*MZ*wZ*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C45)*(4*(gqL + gqR)*((gL*gL) + (gR*gR))*
            C12*C34 + 
           el*eq*(gL + gR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34))*
         (E2345*C14 + 
           E1245*(C13 + C34) + 
           E1234*C45))/6. + 
      ((gqL - gqR)*(gL - gR)*(eq*eq)*
         iMZMZwZwZMZMZC34*
         (1.0/C25)*(1.0/C34)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34) + 
           2*(gqL + gqR)*(gL + gR)*C34)*
         (C14*C35 - C13*C45))/3. + 
((eq*eq)*iMZMZwZwZMZMZC34*(1.0/C25)*(1.0/C34/C34)*(4*((gqL*gqL)+(gqR*gqR))*
            ((gL*gL) + (gR*gR))*(C34*C34) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34)*C34)*
         (C14*C35 + C13*C45))/6. + 
      ((gqL - gqR)*(gL - gR)*(eq*eq)*
         iMZMZwZwZMZMZC34*
         (1.0/C15)*(1.0/C25)*(1.0/C34)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34) + 
           2*(gqL + gqR)*(gL + gR)*C34)*
         (-((C14*C23 - C13*C24)*
              (-2*C12 + C15 + C25)) + 
           C12*(-C14 + C24)*C35 + 
           C12*(C13 - C23)*C45))/3. + 
      ((gqL - gqR)*(gL - gR)*(eq*eq)*
         iMZMZwZwZMZMZC34*
         (1.0/C15)*(1.0/C34)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34) + 
           2*(gqL + gqR)*(gL + gR)*C34)*
         (-(C24*C35) + C23*C45))/3. + 
((eq*eq)*iMZMZwZwZMZMZC34*(1.0/C15)*(1.0/C34/C34)*(4*((gqL*gqL)+(gqR*gqR))*
            ((gL*gL) + (gR*gR))*(C34*C34) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34)*C34)*
         (C24*C35 + C23*C45))/6. + 
      (el*eq*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (1.0/C35)*(4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12))*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (2*C13*C14*C23 + 
           C14*C15*C23 + 2*(C13*C13)*C24 + 
           2*C13*C15*C24 + 
           C13*C14*C25 + C15*C23*C34 + 
           (-(C14*(C12 + C23)) - 
              2*(C13 + C15)*C24)*C35 - 
           C13*C23*C45))/6. + 
      (el*eq*(gqL - gqR)*(gL - gR)*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (1.0/C35)*(4*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*((MZ*MZ)*(wZ*wZ)*(4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (2*C13*C14*C23 + 
           C14*C15*C23 - 2*(C13*C13)*C24 - 
           2*C13*C15*C24 + 
           C13*C14*C25 + C15*C23*C34 + 
           (-(C14*(C12 + C23)) + 
              2*(C13 + C15)*C24)*C35 - 
           C13*C23*C45))/6. - 
((eq*eq)*iMZMZwZwZMZMZC34*(1.0/C15)*(1.0/C25)*(1.0/C34/C34)*
         (4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            (C34*C34) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34)*C34)*
         (C24*(-2*C15*C23 + 
              C13*(-2*C12 + C15 + C25)) + 
           C14*(-2*C13*C25 + 
              C23*(-2*C12 + C15 + C25)) + 
           C12*(C14 + C24)*C35 + 
           C12*(C13 + C23)*C45))/6. + 
      (el*eq*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (1.0/C45)*(4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12))*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (C24*((2*C14 + C15)*C23 + 
              2*C13*C24 - C14*C35) + 
           C25*(C14*(C23 + C34) + 
              2*C13*(C24 - C45)) - 
           ((C12 + C14)*C23 + 2*C13*C24)*
            C45))/6. + (el*eq*(gqL - gqR)*(gL - gR)*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (1.0/C45)*(4*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*((MZ*MZ)*(wZ*wZ)*(4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (-2*(C14*C14)*C23 - 
           2*C14*C15*C23 + 
           2*C13*C14*C24 + 
           C13*C15*C24 + C13*C14*C25 + 
           C15*C24*C34 - C14*C24*C35 - 
           (-2*(C14 + C15)*C23 + 
              C13*(C12 + C24))*C45))/6. + 
      (el*eq*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (1.0/C45)*(4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12))*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (-2*(C14*C14)*C23 - 
           2*C14*C15*C23 - 
           2*C13*C14*C24 - 
           C13*C15*C24 - C13*C14*C25 - 
           C15*C24*C34 + C14*C24*C35 + 
           (2*(C14 + C15)*C23 + 
              C13*(C12 + C24))*C45))/6. + 
((el*el)*iMZMZwZwZMZMZC12*(1.0/C12/C12)*
         (1.0/C35)*(1.0/C45)*
         (4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            (C12*C12) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*C12)*
         (((2*C14 + C15)*C23 + 
              (2*C13 + C15)*C24 + 
              (C13 + C14)*C25)*C34 + 
           (C14*(C23 - 2*C24) + C13*C24)*
            C35 + (C14*C23 + 
              C13*(-2*C23 + C24))*C45))/6. + 
      ((gqL - gqR)*(gL - gR)*(el*el)*
         iMZMZwZwZMZMZC12*
         (1.0/C12)*(1.0/C35)*(1.0/C45)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12) + 
           2*(gqL + gqR)*(gL + gR)*C12)*
         (4*((2*C14 + C15)*C23 - 
              (2*C13 + C15)*C24 + 
              (-C13 + C14)*C25)*C34 + 
           4*(C14*C23 - C13*C24)*
            (C35 + C45)))/12. + 
      (el*eq*(gqL - gqR)*(gL - gR)*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (1.0/C35)*(4*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*((MZ*MZ)*(wZ*wZ)*(4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (C24*((2*C13 + C15)*C23 - 
              (C12 + C13)*C35) + 
           C25*(C13*(C24 + C34) + 
              2*C14*(-C23 + C35)) - 
           C23*(2*C14*(C23 - C35) + 
              C13*C45)))/6. + 
      (el*eq*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (1.0/C35)*(4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12))*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (C24*(-((2*C13 + C15)*C23) + 
              (C12 + C13)*C35) + 
           C25*(-(C13*(C24 + C34)) + 
              2*C14*(-C23 + C35)) + 
           C23*(2*C14*(-C23 + C35) + 
              C13*C45)))/6. + 
      (el*eq*(gqL - gqR)*(gL - gR)*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (1.0/C45)*(4*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 + 
           el*eq*((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (-2*(C24*C24)*C13 - 
           (C12 + C14)*C23*C45 + 
           C24*((2*C14 + C15)*C23 - 
              C14*C35 + 2*C13*C45) + 
           C25*(C14*(C23 + C34) + 
              2*C13*(-C24 + C45))))/6.))/4096.;

}

double GetqqZAME_S(ZALeptonVectors &Leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   const double M1 = (Leptons.Lepton1 + Leptons.Lepton2).GetMass();
   const double s = (Leptons.Lepton1 + Leptons.Lepton2 + Leptons.Photon).GetMass2();
   const double MH = sqrt(s);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = Leptons.Lepton1;
   FourVector P4 = Leptons.Lepton2;
   FourVector P5 = Leptons.Photon;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   if(Reverse == true)
      swap(P1, P2);

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C45 = P4 * P5;
   
   double Sqrt2 = sqrt(2);

   double SqrtC12 = sqrt(C12);
   double SqrtC13 = sqrt(C13);
   double SqrtC14 = sqrt(C14);
   double SqrtC15 = sqrt(C15);
   double SqrtC23 = sqrt(C23);
   double SqrtC24 = sqrt(C24);
   double SqrtC25 = sqrt(C25);
   double SqrtC34 = sqrt(C34);
   double SqrtC35 = sqrt(C35);
   double SqrtC45 = sqrt(C45);

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1345 = EPS(P1, P3, P4, P5);
   double E2345 = EPS(P2, P3, P4, P5);

   double MZMZC12 = MZ * MZ - 2 * C12;
   double MZMZC34 = MZ * MZ - 2 * C34;
   double MZMZC45 = MZ * MZ - 2 * C45;
   double iMZMZwZwZMZMZC12 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC12 * MZMZC12), -1);
   double iMZMZwZwZMZMZC34 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC34 * MZMZC34), -1);
   double iMZMZwZwZMZMZC45 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC45 * MZMZC45), -1);

   return (pow(Pi,-5)*(1.0/s)*(1 - (M1*M1)*(1.0/s))*
    (((gqL - gqR)*(gL - gR)*(el*el)*
         iMZMZwZwZMZMZC12*
         (1.0/C12)*(1.0/C45)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12) + 
           2*(gqL + gqR)*(gL + gR)*C12)*
         (C15*C23 - C13*C25))/3. + 
((el*el)*iMZMZwZwZMZMZC12*(1.0/C12/C12)*
         (1.0/C45)*(4*((gqL*gqL) + (gqR*gqR))*
            ((gL*gL) + (gR*gR))*(C12*C12) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*C12)*
         (C15*C23 + C13*C25))/6. + 
      ((gqL - gqR)*(gL - gR)*(el*el)*
         iMZMZwZwZMZMZC12*
         (1.0/C12)*(1.0/C35)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12) + 
           2*(gqL + gqR)*(gL + gR)*C12)*
         (-(C15*C24) + C14*C25))/3. + 
((el*el)*iMZMZwZwZMZMZC12*(1.0/C12/C12)*
         (1.0/C35)*(4*((gqL*gqL) + (gqR*gqR))*
            ((gL*gL) + (gR*gR))*(C12*C12) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*C12)*
         (C15*C24 + C14*C25))/6. + 
((el*el)*iMZMZwZwZMZMZC12*(1.0/C12/C12)*
         (1.0/C35)*(1.0/C45)*
         (4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            (C12*C12) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12)*C12)*
         (((2*C14 + C15)*C23 + 
              (2*C13 + C15)*C24 + 
              (C13 + C14)*C25)*C34 + 
           (C14*(C23 - 2*C24) + C13*C24)*
            C35 + (C14*C23 + 
              C13*(-2*C23 + C24))*C45))/6. + 
      ((gqL - gqR)*(gL - gR)*(el*el)*
         iMZMZwZwZMZMZC12*
         (1.0/C12)*(1.0/C35)*(1.0/C45)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC12)*
            (MZ + Sqrt2*SqrtC12) + 
           2*(gqL + gqR)*(gL + gR)*C12)*
         (4*((2*C14 + C15)*C23 - 
              (2*C13 + C15)*C24 + 
              (-C13 + C14)*C25)*C34 + 
           4*(C14*C23 - C13*C24)*
            (C35 + C45)))/12.))/4096.;
}

double GetqqZAME_TU(ZALeptonVectors &Leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   const double M1 = (Leptons.Lepton1 + Leptons.Lepton2).GetMass();
   const double s = (Leptons.Lepton1 + Leptons.Lepton2 + Leptons.Photon).GetMass2();
   const double MH = sqrt(s);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = Leptons.Lepton1;
   FourVector P4 = Leptons.Lepton2;
   FourVector P5 = Leptons.Photon;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   if(Reverse == true)
      swap(P1, P2);

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C45 = P4 * P5;
   
   double Sqrt2 = sqrt(2);

   double SqrtC12 = sqrt(C12);
   double SqrtC13 = sqrt(C13);
   double SqrtC14 = sqrt(C14);
   double SqrtC15 = sqrt(C15);
   double SqrtC23 = sqrt(C23);
   double SqrtC24 = sqrt(C24);
   double SqrtC25 = sqrt(C25);
   double SqrtC34 = sqrt(C34);
   double SqrtC35 = sqrt(C35);
   double SqrtC45 = sqrt(C45);

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1345 = EPS(P1, P3, P4, P5);
   double E2345 = EPS(P2, P3, P4, P5);

   double MZMZC12 = MZ * MZ - 2 * C12;
   double MZMZC34 = MZ * MZ - 2 * C34;
   double MZMZC45 = MZ * MZ - 2 * C45;
   double iMZMZwZwZMZMZC12 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC12 * MZMZC12), -1);
   double iMZMZwZwZMZMZC34 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC34 * MZMZC34), -1);
   double iMZMZwZwZMZMZC45 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC45 * MZMZC45), -1);

   return (pow(Pi,-5)*(1.0/s)*(1 - (M1*M1)*(1.0/s))*
    (((gqL - gqR)*(gL - gR)*(eq*eq)*
         iMZMZwZwZMZMZC34*
         (1.0/C25)*(1.0/C34)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34) + 
           2*(gqL + gqR)*(gL + gR)*C34)*
         (C14*C35 - C13*C45))/3. + 
((eq*eq)*iMZMZwZwZMZMZC34*(1.0/C25)*(1.0/C34/C34)*(4*((gqL*gqL)+(gqR*gqR))*
            ((gL*gL) + (gR*gR))*(C34*C34) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34)*C34)*
         (C14*C35 + C13*C45))/6. + 
      ((gqL - gqR)*(gL - gR)*(eq*eq)*
         iMZMZwZwZMZMZC34*
         (1.0/C15)*(1.0/C25)*(1.0/C34)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34) + 
           2*(gqL + gqR)*(gL + gR)*C34)*
         (-((C14*C23 - C13*C24)*
              (-2*C12 + C15 + C25)) + 
           C12*(-C14 + C24)*C35 + 
           C12*(C13 - C23)*C45))/3. + 
      ((gqL - gqR)*(gL - gR)*(eq*eq)*
         iMZMZwZwZMZMZC34*
         (1.0/C15)*(1.0/C34)*
         (2*el*eq*(-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34) + 
           2*(gqL + gqR)*(gL + gR)*C34)*
         (-(C24*C35) + C23*C45))/3. + 
((eq*eq)*iMZMZwZwZMZMZC34*(1.0/C15)*(1.0/C34/C34)*(4*((gqL*gqL)+(gqR*gqR))*
            ((gL*gL) + (gR*gR))*(C34*C34) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34)*C34)*
         (C24*C35 + C23*C45))/6. - 
((eq*eq)*iMZMZwZwZMZMZC34*(1.0/C15)*(1.0/C25)*(1.0/C34/C34)*(4*((gqL*gqL)+(gqR*gqR))*((gL*gL)+(gR*gR))*
            (C34*C34) + 
           4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*el*eq*(gqL + gqR)*(gL + gR)*
            (-MZ + Sqrt2*SqrtC34)*
            (MZ + Sqrt2*SqrtC34)*C34)*
         (C24*(-2*C15*C23 + 
              C13*(-2*C12 + C15 + C25)) + 
           C14*(-2*C13*C25 + 
              C23*(-2*C12 + C15 + C25)) + 
           C12*(C14 + C24)*C35 + 
           C12*(C13 + C23)*C45))/6.))/4096.;
}

double GetqqZAME_S_TU_Interference(ZALeptonVectors &Leptons, bool Reverse, bool UpType)
{
   const double Pi = CONST_PI;
   
   const double M1 = (Leptons.Lepton1 + Leptons.Lepton2).GetMass();
   const double s = (Leptons.Lepton1 + Leptons.Lepton2 + Leptons.Photon).GetMass2();
   const double MH = sqrt(s);
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P1(MH / 2, 0, 0, MH / 2);
   FourVector P2(MH / 2, 0, 0, -MH / 2);
   FourVector P3 = Leptons.Lepton1;
   FourVector P4 = Leptons.Lepton2;
   FourVector P5 = Leptons.Photon;
   
   double eq = EE * 2 / 3;
   double gqL = CONST_GQL_UP;
   double gqR = CONST_GQR_UP;
   if(UpType == false)
   {
      eq = -EE / 3;
      gqL = CONST_GQL_DOWN;
      gqR = CONST_GQR_DOWN;
   }

   if(Reverse == true)
      swap(P1, P2);

   double C12 = P1 * P2;
   double C13 = P1 * P3;
   double C14 = P1 * P4;
   double C15 = P1 * P5;
   double C23 = P2 * P3;
   double C24 = P2 * P4;
   double C25 = P2 * P5;
   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C45 = P4 * P5;
   
   double Sqrt2 = sqrt(2);

   double SqrtC12 = sqrt(C12);
   double SqrtC13 = sqrt(C13);
   double SqrtC14 = sqrt(C14);
   double SqrtC15 = sqrt(C15);
   double SqrtC23 = sqrt(C23);
   double SqrtC24 = sqrt(C24);
   double SqrtC25 = sqrt(C25);
   double SqrtC34 = sqrt(C34);
   double SqrtC35 = sqrt(C35);
   double SqrtC45 = sqrt(C45);

   double E1234 = EPS(P1, P2, P3, P4);
   double E1235 = EPS(P1, P2, P3, P5);
   double E1245 = EPS(P1, P2, P4, P5);
   double E1345 = EPS(P1, P3, P4, P5);
   double E2345 = EPS(P2, P3, P4, P5);

   double MZMZC12 = MZ * MZ - 2 * C12;
   double MZMZC34 = MZ * MZ - 2 * C34;
   double MZMZC45 = MZ * MZ - 2 * C45;
   double iMZMZwZwZMZMZC12 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC12 * MZMZC12), -1);
   double iMZMZwZwZMZMZC34 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC34 * MZMZC34), -1);
   double iMZMZwZwZMZMZC45 = pow((MZ * MZ) * (wZ * wZ) + (MZMZC45 * MZMZC45), -1);

   return (pow(Pi,-5)*(1.0/s)*(1 - (M1*M1)*(1.0/s))*
((el*eq*(gL-gR)*MZ*wZ*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C45)*((-E1235)*C14 + 
           E1234*C15 + 
           (-E1345)*(C12 + C24))*
         (4*(gL + gR)*((gqL*gqL) + (gqR*gqR))*C12*C34 + 
           el*eq*(gqL + gqR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34)))/6. + 
(el*eq*(gL-gR)*MZ*wZ*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C45)*(E2345*(C12 + C14) + 
           (-E1235)*C24 + E1234*C25)*
         (4*(gL + gR)*((gqL*gqL) + (gqR*gqR))*C12*C34 + 
           el*eq*(gqL + gqR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34)))/6. - 
      (el*eq*(gqL - gqR)*MZ*wZ*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C45)*((-E2345)*C14 + 
           E1245*C23)*
         (4*(gqL + gqR)*((gL*gL) + (gR*gR))*C12*C34 + 
           el*eq*(gL + gR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34)))/6. - 
      (el*eq*(gqL - gqR)*MZ*wZ*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C35)*((-E2345)*C13 + 
           (-E1235)*C24)*
         (4*(gqL + gqR)*((gL*gL) + (gR*gR))*C12*C34 + 
           el*eq*(gL + gR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34)))/6. + 
(el*eq*(gL-gR)*MZ*wZ*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C35)*(4*(gL + gR)*((gqL*gqL) + (gqR*gqR))*
            C12*C34 + 
           el*eq*(gqL + gqR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34))*
         (E2345*C13 + 
           (-E1235)*(C14 + C34) + 
           E1234*C35))/6. + 
      (el*eq*(gqL - gqR)*MZ*wZ*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C35)*(4*(gqL + gqR)*((gL*gL) + (gR*gR))*
            C12*C34 + 
           el*eq*(gL + gR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34))*
         (E2345*C13 + 
           (-E1235)*(C14 + C34) + 
           E1234*C35))/6. + 
(el*eq*(gL-gR)*MZ*wZ*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C35)*(4*(gL + gR)*((gqL*gqL) + (gqR*gqR))*
            C12*C34 + 
           el*eq*(gqL + gqR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34))*
         ((-E1345)*C23 + 
           (-E1235)*(C24 + C34) + 
           E1234*C35))/6. + 
      (el*eq*(gqL - gqR)*MZ*wZ*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (Sqrt2*SqrtC12 - Sqrt2*SqrtC34)*
         (Sqrt2*SqrtC12 + Sqrt2*SqrtC34)*
         (1.0/C45)*(4*(gqL + gqR)*((gL*gL) + (gR*gR))*
            C12*C34 + 
           el*eq*(gL + gR)*(-((MZ*MZ)*((MZ*MZ) + (wZ*wZ))) + 
              4*C12*C34))*
         (E2345*C14 + 
           E1245*(C13 + C34) + 
           E1234*C45))/6. + 
      (el*eq*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (1.0/C35)*(4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12))*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (2*C13*C14*C23 + 
           C14*C15*C23 + 2*(C13*C13)*C24 + 
           2*C13*C15*C24 + 
           C13*C14*C25 + C15*C23*C34 + 
           (-(C14*(C12 + C23)) - 
              2*(C13 + C15)*C24)*C35 - 
           C13*C23*C45))/6. + 
      (el*eq*(gqL - gqR)*(gL - gR)*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (1.0/C35)*(4*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*((MZ*MZ)*(wZ*wZ)*(4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (2*C13*C14*C23 + 
           C14*C15*C23 - 2*(C13*C13)*C24 - 
           2*C13*C15*C24 + 
           C13*C14*C25 + C15*C23*C34 + 
           (-(C14*(C12 + C23)) + 
              2*(C13 + C15)*C24)*C35 - 
           C13*C23*C45))/6. + 
      (el*eq*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (1.0/C45)*(4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12))*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (C24*((2*C14 + C15)*C23 + 
              2*C13*C24 - C14*C35) + 
           C25*(C14*(C23 + C34) + 
              2*C13*(C24 - C45)) - 
           ((C12 + C14)*C23 + 2*C13*C24)*
            C45))/6. + (el*eq*(gqL - gqR)*(gL - gR)*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (1.0/C45)*(4*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*((MZ*MZ)*(wZ*wZ)*(4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (-2*(C14*C14)*C23 - 
           2*C14*C15*C23 + 
           2*C13*C14*C24 + 
           C13*C15*C24 + C13*C14*C25 + 
           C15*C24*C34 - C14*C24*C35 - 
           (-2*(C14 + C15)*C23 + 
              C13*(C12 + C24))*C45))/6. + 
      (el*eq*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C15)*(1.0/C34)*
         (1.0/C45)*(4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12))*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (-2*(C14*C14)*C23 - 
           2*C14*C15*C23 - 
           2*C13*C14*C24 - 
           C13*C15*C24 - C13*C14*C25 - 
           C15*C24*C34 + C14*C24*C35 + 
           (2*(C14 + C15)*C23 + 
              C13*(C12 + C24))*C45))/6. + 
      (el*eq*(gqL - gqR)*(gL - gR)*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (1.0/C35)*(4*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*((MZ*MZ)*(wZ*wZ)*(4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (C24*((2*C13 + C15)*C23 - 
              (C12 + C13)*C35) + 
           C25*(C13*(C24 + C34) + 
              2*C14*(-C23 + C35)) - 
           C23*(2*C14*(C23 - C35) + 
              C13*C45)))/6. + 
      (el*eq*iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (1.0/C35)*(4*(el*el)*(eq*eq)*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC12*MZMZC12))*
            ((MZ*MZ)*(wZ*wZ) + (MZMZC34*MZMZC34)) + 
           4*((gqL*gqL) + (gqR*gqR))*((gL*gL) + (gR*gR))*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 
+ el*eq*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (C24*(-((2*C13 + C15)*C23) + 
              (C12 + C13)*C35) + 
           C25*(-(C13*(C24 + C34)) + 
              2*C14*(-C23 + C35)) + 
           C23*(2*C14*(-C23 + C35) + 
              C13*C45)))/6. + 
      (el*eq*(gqL - gqR)*(gL - gR)*
         iMZMZwZwZMZMZC12*
         iMZMZwZwZMZMZC34*
         (1.0/C12)*(1.0/C25)*(1.0/C34)*
         (1.0/C45)*(4*(gqL + gqR)*(gL + gR)*
            ((MZ*MZ)*(wZ*wZ) + 
              (-MZ + Sqrt2*SqrtC12)*
               (MZ + Sqrt2*SqrtC12)*
               (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34))*C12*C34 + 
           el*eq*((MZ*MZ)*(wZ*wZ)*
               (4*(C12*C12) + 4*(C34*C34) - 
                 (MZ*MZ)*(2*C12 + 2*C34)) + 
              (-MZ + Sqrt2*SqrtC34)*
               (MZ + Sqrt2*SqrtC34)*
               ((MZ*MZ) - 2*C12)*
               (-8*C12*C34 + 
                 (MZ*MZ)*(2*C12 + 2*C34))))*
         (-2*(C24*C24)*C13 - 
           (C12 + C14)*C23*C45 + 
           C24*((2*C14 + C15)*C23 - 
              C14*C35 + 2*C13*C45) + 
           C25*(C14*(C23 + C34) + 
              2*C13*(-C24 + C45))))/6.))/4096.;
}




