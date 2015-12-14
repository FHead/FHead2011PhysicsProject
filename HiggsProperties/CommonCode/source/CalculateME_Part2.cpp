#include <cmath>
#include <iostream>
#include <complex>
using namespace std;

#include "CalculateME.h"
#include "AngleConversion.h"
#include "Constants.h"

double GetZABackground_ThetaPhi1(EventParameters &event, bool UpType)
{
   double Pi = PI;
   
   double M1 = event.ZMass;
   double M2 = event.Z2Mass;
   if(M1 < M2)
      swap(M1, M2);

   double MH = event.HMass;
   double s = MH * MH;
   double x = (M1 * M1 - M2 * M2) / s;
   double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   double X = cos(event.Theta1);
   double Y = cos(event.Theta2);
   double Z = cos(event.Theta0);
   double X2 = cos(2 * event.Theta1);
   double Y2 = cos(2 * event.Theta2);
   double Z2 = cos(2 * event.Theta0);
   double theta1 = event.Theta1;
   double theta2 = event.Theta2;
   double Theta = event.Theta0;
   double MW = 80.4;
   double MZ = 91.1876;
   double wZ = 2.4952;
   double phi = event.Phi;
   double Phi1 = event.Phi0;
   
   double cw = MW / MZ;
   double sw2 = (1 - cw * cw);

   double g = 0.652;
   double gqL = (-2.0 / 3 * sw2 + 0.5) / cw * g;
   double gqR = (-2.0 / 3 * sw2) / cw * g;
   double gL = (sw2 - 0.5) / cw * g;
   double gR = (sw2) / cw * g;
   double EE = sqrt(4 * PI / 127);
   double el = -EE;
   double eq = -EE / 3;

   if(UpType == false)
   {
      gqL = (1.0 / 3 * sw2 - 0.5) / cw * g;
      gqR = (1.0 / 3 * sw2) / cw * g;
   }

return -(pow(el,2)*pow(eq,2)*(pow(gqL,2) + pow(gqR,2))*pow(M1,-4)*pow(M2,-2)*
      pow(Pi,-6)*pow(s,-1)*(2*gL*gR*pow(M1,2)*pow(M2,2)*
         ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + pow(MZ,2)*pow(wZ,2)) + 
        pow(gL,2)*(pow(M2,4)*pow(MZ,2)*(pow(MZ,2) + pow(wZ,2)) + 
           pow(M1,2)*pow(M2,2)*pow(MZ,2)*
            (-3*pow(M2,2) + pow(MZ,2) + pow(wZ,2)) + 
           pow(M1,4)*(3*pow(M2,4) - 3*pow(M2,2)*pow(MZ,2) + pow(MZ,4) + 
              pow(MZ,2)*pow(wZ,2))) + 
        pow(gR,2)*(pow(M2,4)*pow(MZ,2)*(pow(MZ,2) + pow(wZ,2)) + 
           pow(M1,2)*pow(M2,2)*pow(MZ,2)*
            (-3*pow(M2,2) + pow(MZ,2) + pow(wZ,2)) + 
           pow(M1,4)*(3*pow(M2,4) - 3*pow(M2,2)*pow(MZ,2) + pow(MZ,4) + 
              pow(MZ,2)*pow(wZ,2))))*
      pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
        pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
      pow(-(pow(cos(Theta),2)*
           (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),
       -2)*pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
      pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
      (8*pow(M1,2)*pow(cos(Theta),4)*
         (6*(pow(M1,4) + pow(M2,4))*pow(s,2) - 
           5*(pow(M1,2) + pow(M2,2))*pow(s,3) + 2*pow(s,4) - 
           5*s*(pow(M1,2) + pow(M2,2))*pow(pow(M1,2) - pow(M2,2),2) + 
           2*pow(pow(M1,2) - pow(M2,2),4)) + 
        4*pow(cos(Theta),2)*(4*pow(M1,2)*
            (pow(M1,2)*(-3*s + pow(M2,2))*(s + pow(M2,2))*
               (-s + 4*pow(M2,2)) + pow(M1,6)*(3*s + 4*pow(M2,2)) - 
              pow(M1,4)*(9*s*pow(M2,2) + 8*pow(M2,4) + 6*pow(s,2)) + 
              3*s*pow(-(M2*s) + pow(M2,3),2)) + 
           s*((-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
               (3*pow(M1,4) + pow(M1,2)*(-4*s + 8*pow(M2,2)) + 
                 pow(-s + pow(M2,2),2)) + 
              4*pow(M1,2)*pow(cos(Phi1),2)*
               (2*pow(M1,6) - pow(M1,4)*(3*s + 4*pow(M2,2)) + 
                 2*pow(M1,2)*(-(s*pow(M2,2)) + pow(M2,4)) + 
                 s*pow(-s + pow(M2,2),2)))*pow(sin(Theta),2)) - 
        pow(-s + pow(M1,2) + pow(M2,2),2)*
         (8*pow(M1,2)*(5*s*(pow(M1,2) + pow(M2,2)) + 2*pow(s,2) + 
              2*pow(pow(M1,2) - pow(M2,2),2) + 
              s*pow(sin(Theta),2)*
               (-3*(M1 - M2)*(M1 + M2) + 
                 2*pow(cos(Phi1),2)*
                  (s + 2*pow(M1,2) - 4*pow(M2,2) - s*pow(sin(Theta),2)))) + 
           s*(pow(M1,4) - 2*pow(M1,2)*(2*s + pow(M2,2)) + 
              pow(-s + pow(M2,2),2))*pow(sin(2*Theta),2))))/442368. + 
  ((gqL - gqR)*(gqL + gqR)*(gL - gR)*(gL + gR)*cos(Phi1)*pow(el,2)*pow(eq,2)*
     pow(M1,-1)*pow(M2,-4)*pow(Pi,-5)*pow(s,-1)*
     (-((M2 - MZ)*(M2 + MZ)*(-2*pow(M1,2)*pow(M2,2) + 
            (pow(M1,2) + pow(M2,2))*pow(MZ,2))) + 
       (pow(M1,2) + pow(M2,2))*pow(MZ,2)*pow(wZ,2))*
     pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
       pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
     (pow(M1,10)*pow(s,0.5) + 3*pow(M1,8)*(-s + pow(M2,2))*pow(s,0.5) + 
       (-s + pow(M2,2))*pow(M2,4)*
        (pow(s,0.5)*pow(-s + pow(M2,2),2) - 
          pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),0.5)*
           pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
               pow(-s + pow(M2,2),2)),0.5)) - 
       pow(M1,6)*((-3*s + 10*pow(M2,2))*pow(s,1.5) + 
          pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),0.5)*
           pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
               pow(-s + pow(M2,2),2)),0.5)) + 
       pow(M1,4)*(pow(s,0.5)*(18*s*pow(M2,4) + 4*pow(M2,6) + 
             7*pow(M2,2)*pow(s,2) - pow(s,3)) + 
          s*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),0.5)*
           pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
               pow(-s + pow(M2,2),2)),0.5) - 
          3*pow(M2,2)*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),0.5)*
           pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
               pow(-s + pow(M2,2),2)),0.5)) + 
       pow(M1,2)*pow(M2,2)*(-9*pow(M2,6)*pow(s,0.5) + 
          14*pow(M2,4)*pow(s,1.5) + 
          2*s*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),0.5)*
           pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
               pow(-s + pow(M2,2),2)),0.5) - 
          pow(M2,2)*(5*pow(s,2.5) + 
             3*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2),0.5)*
              pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                  pow(-s + pow(M2,2),2)),0.5))) + 
       cos(2*Theta)*(pow(M1,10)*pow(s,0.5) - 
          pow(M1,8)*(3*s + pow(M2,2))*pow(s,0.5) + 
          (-s + pow(M2,2))*pow(M2,4)*
           (pow(s,0.5)*pow(-s + pow(M2,2),2) - 
             pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2),0.5)*
              pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                  pow(-s + pow(M2,2),2)),0.5)) - 
          pow(M1,6)*(pow(s,0.5)*
              (6*s*pow(M2,2) + 4*pow(M2,4) - 3*pow(s,2)) + 
             pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2),0.5)*
              pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                  pow(-s + pow(M2,2),2)),0.5)) + 
          pow(M1,4)*(pow(s,0.5)*
              (10*s*pow(M2,4) + 8*pow(M2,6) + 11*pow(M2,2)*pow(s,2) - 
                pow(s,3)) + s*
              pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2),0.5)*
              pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                  pow(-s + pow(M2,2),2)),0.5) - 
             3*pow(M2,2)*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2),0.5)*
              pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                  pow(-s + pow(M2,2),2)),0.5)) + 
          pow(M1,2)*pow(M2,2)*(-5*pow(M2,6)*pow(s,0.5) + 
             2*pow(M2,4)*pow(s,1.5) - 4*pow(s,3.5) + 
             2*s*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2),0.5)*
              pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                  pow(-s + pow(M2,2),2)),0.5) + 
             pow(M2,2)*(7*pow(s,2.5) - 
                3*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                   pow(-s + pow(M2,2),2),0.5)*
                 pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                     pow(-s + pow(M2,2),2)),0.5)))))*
     pow(pow(M1,4) + pow(M1,2)*(-2*s + 6*pow(M2,2)) + 
       pow(-s + pow(M2,2),2) - 
       cos(2*Theta)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
          pow(-s + pow(M2,2),2)),-2)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*sin(Theta))/
   36864.;
}

double GetZABackground_Thetaphi(EventParameters &event, bool UpType)
{
   double Pi = PI;
   
   double M1 = event.ZMass;
   double M2 = event.Z2Mass;
   if(M1 < M2)
      swap(M1, M2);

   double MH = event.HMass;
   double s = MH * MH;
   double x = (M1 * M1 - M2 * M2) / s;
   double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   double X = cos(event.Theta1);
   double Y = cos(event.Theta2);
   double Z = cos(event.Theta0);
   double X2 = cos(2 * event.Theta1);
   double Y2 = cos(2 * event.Theta2);
   double Z2 = cos(2 * event.Theta0);
   double theta1 = event.Theta1;
   double theta2 = event.Theta2;
   double Theta = event.Theta0;
   double MW = 80.4;
   double MZ = 91.1876;
   double wZ = 2.4952;
   double phi = event.Phi;
   double Phi1 = event.Phi0;
   
   double cw = MW / MZ;
   double sw2 = (1 - cw * cw);

   double g = 0.652;
   double gqL = (-2.0 / 3 * sw2 + 0.5) / cw * g;
   double gqR = (-2.0 / 3 * sw2) / cw * g;
   double gL = (sw2 - 0.5) / cw * g;
   double gR = (sw2) / cw * g;
   double EE = sqrt(4 * PI / 127);
   double el = -EE;
   double eq = -EE / 3;

   if(UpType == false)
   {
      gqL = (1.0 / 3 * sw2 - 0.5) / cw * g;
      gqR = (1.0 / 3 * sw2) / cw * g;
   }

return -(M1*M2*cos(phi)*pow(el,2)*pow(eq,2)*(pow(gqL,2) + pow(gqR,2))*
      pow(gL - gR,2)*pow(Pi,-4)*
      ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + pow(MZ,2)*pow(wZ,2))*
      pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
        pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
      pow(-(pow(cos(Theta),2)*
           (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),
       -2)*pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
      pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
      (pow(-s + pow(M1,2) + pow(M2,2),2)*(-2 + pow(sin(Theta),2)) + 
        pow(cos(Theta),2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
           pow(-s + pow(M2,2),2))*(2 + pow(sin(Theta),2))))/98304. + 
  (pow(el,2)*pow(eq,2)*(pow(gqL,2) + pow(gqR,2))*pow(Pi,-6)*pow(s,-1)*
     pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
       pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
     pow(-(pow(cos(Theta),2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
            pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),-2)*
     (pow(gL + gR,2)*pow(M1,-2)*pow(M2,-2)*
        (2*(M1 - MZ)*(M1 + MZ)*(-pow(M2,2) + pow(MZ,2)) - 
          2*pow(MZ,2)*pow(wZ,2))*
        pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
        pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1) + 
       2*(pow(gL,2) + pow(gR,2))*
        (-(pow(M2,-4)*pow(pow(MZ,2)*pow(wZ,2) + 
               pow(pow(M1,2) - pow(MZ,2),2),-1)) - 
          pow(M1,-4)*pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),
            -1)))*(4*pow(M1,2)*pow(M2,2)*pow(cos(Theta),4)*
        (2*(3*pow(M1,4) - 2*pow(M1,2)*pow(M2,2) + 3*pow(M2,4))*pow(s,2) - 
          6*(pow(M1,2) + pow(M2,2))*pow(s,3) + 3*pow(s,4) - 
          6*s*(pow(M1,2) + pow(M2,2))*pow(pow(M1,2) - pow(M2,2),2) + 
          3*pow(pow(M1,2) - pow(M2,2),4) + 
          2*pow(cos(phi),2)*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),2)) - 
       4*pow(cos(Theta),2)*(-2*pow(M1,2)*pow(M2,2)*
           (pow(M1,8) + 2*pow(M1,6)*(s + 3*pow(M2,2)) - 
             2*pow(M1,4)*(9*s*pow(M2,2) + 7*pow(M2,4) + 3*pow(s,2)) + 
             2*pow(M1,2)*(-9*s*pow(M2,4) + 3*pow(M2,6) - 
                7*pow(M2,2)*pow(s,2) + pow(s,3)) + 
             (4*s*pow(M2,2) + pow(M2,4) + pow(s,2))*pow(-s + pow(M2,2),2)) \
+ (-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
           (-(s*(pow(M1,6) + pow(M1,4)*(-2*s + 11*pow(M2,2)) + 
                  pow(M1,2)*(-8*s*pow(M2,2) + 11*pow(M2,4) + pow(s,2)) + 
                  pow(-(M2*s) + pow(M2,3),2))*pow(sin(Theta),2)) + 
             4*pow(M1,2)*pow(M2,2)*pow(cos(phi),2)*
              (pow(M1,4) - 2*s*(pow(M1,2) + pow(M2,2)) + pow(M2,4) + 
                pow(s,2) + s*(-s + pow(M1,2) + pow(M2,2))*pow(sin(Theta),2))\
)) + pow(-s + pow(M1,2) + pow(M2,2),2)*
        (4*pow(M1,2)*pow(M2,2)*
           (-8*s*(pow(M1,2) + pow(M2,2)) - 5*pow(s,2) - 
             5*pow(pow(M1,2) - pow(M2,2),2) + 
             2*pow(cos(phi),2)*
              (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2) + 
                2*s*(-s + pow(M1,2) + pow(M2,2))*pow(sin(Theta),2)) + 
             (2 + cos(2*phi))*pow(s,2)*pow(sin(Theta),4)) - 
          s*(pow(M1,6) - pow(M1,4)*(2*s + pow(M2,2)) + 
             pow(M1,2)*(-8*s*pow(M2,2) - pow(M2,4) + pow(s,2)) + 
             pow(-(M2*s) + pow(M2,3),2))*pow(sin(2*Theta),2))))/884736.;
}

double GetZABackground_ThetaTheta1(EventParameters &event, bool UpType)
{
   double Pi = PI;
   
   double M1 = event.ZMass;
   double M2 = event.Z2Mass;
   if(M1 < M2)
      swap(M1, M2);

   double MH = event.HMass;
   double s = MH * MH;
   double x = (M1 * M1 - M2 * M2) / s;
   double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   double X = cos(event.Theta1);
   double Y = cos(event.Theta2);
   double Z = cos(event.Theta0);
   double X2 = cos(2 * event.Theta1);
   double Y2 = cos(2 * event.Theta2);
   double Z2 = cos(2 * event.Theta0);
   double theta1 = event.Theta1;
   double theta2 = event.Theta2;
   double Theta = event.Theta0;
   double MW = 80.4;
   double MZ = 91.1876;
   double wZ = 2.4952;
   double phi = event.Phi;
   double Phi1 = event.Phi0;
   
   double cw = MW / MZ;
   double sw2 = (1 - cw * cw);

   double g = 0.652;
   double gqL = (-2.0 / 3 * sw2 + 0.5) / cw * g;
   double gqR = (-2.0 / 3 * sw2) / cw * g;
   double gL = (sw2 - 0.5) / cw * g;
   double gR = (sw2) / cw * g;
   double EE = sqrt(4 * PI / 127);
   double el = -EE;
   double eq = -EE / 3;

   if(UpType == false)
   {
      gqL = (1.0 / 3 * sw2 - 0.5) / cw * g;
      gqR = (1.0 / 3 * sw2) / cw * g;
   }

return -((gqL - gqR)*(gqL + gqR)*(gL - gR)*(gL + gR)*cos(Theta)*cos(theta1)*
      pow(el,2)*pow(eq,2)*pow(M2,-2)*pow(Pi,-5)*pow(s,-1)*
      (-((M2 - MZ)*(M2 + MZ)*(-2*pow(M1,2)*pow(M2,2) + 
             (pow(M1,2) + pow(M2,2))*pow(MZ,2))) + 
        (pow(M1,2) + pow(M2,2))*pow(MZ,2)*pow(wZ,2))*
      (-pow(M1,8) + 2*pow(M1,6)*(s + pow(M2,2)) - 
        2*s*pow(M1,4)*(s + 7*pow(M2,2)) + 
        cos(2*Theta)*(-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
         (pow(M1,4) - pow(M2,4) + pow(s,2)) + 
        (s + pow(M2,2))*pow(-s + pow(M2,2),3) - 
        2*pow(M1,2)*(-s + pow(M2,2))*pow(s + pow(M2,2),2))*
      pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
        pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
      pow(-(pow(cos(Theta),2)*
           (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),
       -2)*pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
      pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1))/18432. - 
  (pow(el,2)*pow(eq,2)*(pow(gqL,2) + pow(gqR,2))*pow(M1,-2)*pow(M2,-2)*
     pow(Pi,-5)*pow(s,-1)*(2*gL*gR*pow(M1,2)*pow(M2,2)*
        ((M1 - MZ)*(M2 - MZ)*(M1 + MZ)*(M2 + MZ) + pow(MZ,2)*pow(wZ,2)) + 
       pow(gL,2)*(pow(M2,4)*pow(MZ,2)*(pow(MZ,2) + pow(wZ,2)) + 
          pow(M1,2)*pow(M2,2)*pow(MZ,2)*
           (-3*pow(M2,2) + pow(MZ,2) + pow(wZ,2)) + 
          pow(M1,4)*(3*pow(M2,4) - 3*pow(M2,2)*pow(MZ,2) + pow(MZ,4) + 
             pow(MZ,2)*pow(wZ,2))) + 
       pow(gR,2)*(pow(M2,4)*pow(MZ,2)*(pow(MZ,2) + pow(wZ,2)) + 
          pow(M1,2)*pow(M2,2)*pow(MZ,2)*
           (-3*pow(M2,2) + pow(MZ,2) + pow(wZ,2)) + 
          pow(M1,4)*(3*pow(M2,4) - 3*pow(M2,2)*pow(MZ,2) + pow(MZ,4) + 
             pow(MZ,2)*pow(wZ,2))))*
     (-15*pow(M1,8) + 6*pow(M1,6)*(3*s + 2*pow(M2,2)) + 
       pow(M1,4)*(-280*s*pow(M2,2) + 6*pow(M2,4) - 6*pow(s,2)) + 
       2*pow(M1,2)*(-115*s*pow(M2,4) + 6*pow(M2,6) + 
          36*pow(M2,2)*pow(s,2) + 9*pow(s,3)) - 
       3*(6*s*pow(M2,2) + 5*pow(M2,4) + 5*pow(s,2))*pow(-s + pow(M2,2),2) + 
       cos(2*theta1)*(-5*pow(M1,8) + pow(M1,6)*(22*s + 4*pow(M2,2)) + 
          2*pow(M1,4)*(-20*s*pow(M2,2) + pow(M2,4) - 17*pow(s,2)) + 
          2*pow(M1,2)*(55*s*pow(M2,4) + 2*pow(M2,6) - 
             4*pow(M2,2)*pow(s,2) + 11*pow(s,3)) - 
          (6*s*pow(M2,2) + 5*pow(M2,4) + 5*pow(s,2))*pow(-s + pow(M2,2),2)) \
+ cos(4*Theta)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
          pow(-s + pow(M2,2),2))*
        (3*pow(M1,4) - 2*pow(M1,2)*(2*s + 3*pow(M2,2)) + 
          3*pow(-s + pow(M2,2),2) + 
          cos(2*theta1)*(pow(M1,4) - 2*pow(M1,2)*(-2*s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))) + 
       4*cos(2*Theta)*(-2*s*pow(M1,6) + 3*pow(M1,8) - 
          2*pow(M1,4)*(14*s*pow(M2,2) + 3*pow(M2,4) + pow(s,2)) - 
          2*s*pow(M1,2)*(10*s*pow(M2,2) + 5*pow(M2,4) + pow(s,2)) + 
          cos(2*theta1)*(-6*s*pow(M1,6) + pow(M1,8) + pow(M2,8) - 
             2*pow(M1,4)*(10*s*pow(M2,2) + pow(M2,4) - 5*pow(s,2)) + 
             2*s*pow(M1,2)*(2*s*pow(M2,2) + 17*pow(M2,4) - 3*pow(s,2)) - 
             2*pow(M2,4)*pow(s,2) + pow(s,4)) + 
          3*pow(pow(M2,4) - pow(s,2),2)))*
     pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
       pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
     pow(-(pow(cos(Theta),2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
            pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),-2)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1))/589824.;
}

double GetZABackground_ThetaTheta2(EventParameters &event, bool UpType)
{
   double Pi = PI;
   
   double M1 = event.ZMass;
   double M2 = event.Z2Mass;
   if(M1 < M2)
      swap(M1, M2);

   double MH = event.HMass;
   double s = MH * MH;
   double x = (M1 * M1 - M2 * M2) / s;
   double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   double X = cos(event.Theta1);
   double Y = cos(event.Theta2);
   double Z = cos(event.Theta0);
   double X2 = cos(2 * event.Theta1);
   double Y2 = cos(2 * event.Theta2);
   double Z2 = cos(2 * event.Theta0);
   double theta1 = event.Theta1;
   double theta2 = event.Theta2;
   double Theta = event.Theta0;
   double MW = 80.4;
   double MZ = 91.1876;
   double wZ = 2.4952;
   double phi = event.Phi;
   double Phi1 = event.Phi0;
   
   double cw = MW / MZ;
   double sw2 = (1 - cw * cw);

   double g = 0.652;
   double gqL = (-2.0 / 3 * sw2 + 0.5) / cw * g;
   double gqR = (-2.0 / 3 * sw2) / cw * g;
   double gL = (sw2 - 0.5) / cw * g;
   double gR = (sw2) / cw * g;
   double EE = sqrt(4 * PI / 127);
   double el = -EE;
   double eq = -EE / 3;

   if(UpType == false)
   {
      gqL = (1.0 / 3 * sw2 - 0.5) / cw * g;
      gqR = (1.0 / 3 * sw2) / cw * g;
   }

return -(pow(el,2)*pow(eq,2)*(pow(gqL,2) + pow(gqR,2))*pow(M1,-2)*pow(M2,-2)*
      pow(Pi,-5)*pow(s,-1)*(2*gL*gR*pow(M1,2)*pow(M2,2)*
         (pow(M1,2)*(pow(M2,2) - pow(MZ,2)) + 
           pow(MZ,2)*(-pow(M2,2) + pow(MZ,2) + pow(wZ,2))) + 
        pow(gL,2)*(pow(M2,4)*pow(MZ,2)*(pow(MZ,2) + pow(wZ,2)) + 
           pow(M1,2)*pow(M2,2)*pow(MZ,2)*
            (-3*pow(M2,2) + pow(MZ,2) + pow(wZ,2)) + 
           pow(M1,4)*(3*pow(M2,4) - 3*pow(M2,2)*pow(MZ,2) + pow(MZ,4) + 
              pow(MZ,2)*pow(wZ,2))) + 
        pow(gR,2)*(pow(M2,4)*pow(MZ,2)*(pow(MZ,2) + pow(wZ,2)) + 
           pow(M1,2)*pow(M2,2)*pow(MZ,2)*
            (-3*pow(M2,2) + pow(MZ,2) + pow(wZ,2)) + 
           pow(M1,4)*(3*pow(M2,4) - 3*pow(M2,2)*pow(MZ,2) + pow(MZ,4) + 
              pow(MZ,2)*pow(wZ,2))))*
      (12*s*pow(M1,6) + 4*s*cos(2*theta2)*pow(M1,6) - 15*pow(M1,8) - 
        5*cos(2*theta2)*pow(M1,8) - 230*s*pow(M1,4)*pow(M2,2) + 
        110*s*cos(2*theta2)*pow(M1,4)*pow(M2,2) + 12*pow(M1,6)*pow(M2,2) + 
        4*cos(2*theta2)*pow(M1,6)*pow(M2,2) - 280*s*pow(M1,2)*pow(M2,4) - 
        40*s*cos(2*theta2)*pow(M1,2)*pow(M2,4) + 6*pow(M1,4)*pow(M2,4) + 
        2*cos(2*theta2)*pow(M1,4)*pow(M2,4) + 18*s*pow(M2,6) + 
        22*s*cos(2*theta2)*pow(M2,6) + 12*pow(M1,2)*pow(M2,6) + 
        4*cos(2*theta2)*pow(M1,2)*pow(M2,6) - 15*pow(M2,8) - 
        5*cos(2*theta2)*pow(M2,8) + 6*pow(M1,4)*pow(s,2) + 
        2*cos(2*theta2)*pow(M1,4)*pow(s,2) + 
        72*pow(M1,2)*pow(M2,2)*pow(s,2) - 
        8*cos(2*theta2)*pow(M1,2)*pow(M2,2)*pow(s,2) - 
        6*pow(M2,4)*pow(s,2) - 34*cos(2*theta2)*pow(M2,4)*pow(s,2) + 
        12*pow(M1,2)*pow(s,3) + 4*cos(2*theta2)*pow(M1,2)*pow(s,3) + 
        18*pow(M2,2)*pow(s,3) + 22*cos(2*theta2)*pow(M2,2)*pow(s,3) - 
        15*pow(s,4) - 5*cos(2*theta2)*pow(s,4) + 
        cos(4*Theta)*(3*pow(M1,4) - 4*s*pow(M2,2) - 
           6*pow(M1,2)*(s + pow(M2,2)) + 3*pow(M2,4) + 3*pow(s,2) + 
           cos(2*theta2)*(pow(M1,4) + 4*s*pow(M2,2) - 
              2*pow(M1,2)*(s + pow(M2,2)) + pow(M2,4) + pow(s,2)))*
         (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + pow(-s + pow(M2,2),2)) \
+ 4*cos(2*Theta)*(3*pow(M1,8) - 
           4*s*pow(M1,2)*pow(M2,2)*(5*s + 7*pow(M2,2)) - 
           2*pow(M1,4)*(5*s*pow(M2,2) + 3*pow(M2,4) + 3*pow(s,2)) + 
           (4*s*pow(M2,2) + 3*pow(M2,4) + 3*pow(s,2))*
            pow(-s + pow(M2,2),2) + 
           cos(2*theta2)*(pow(M1,8) + 
              4*s*pow(M1,2)*(s - 5*pow(M2,2))*pow(M2,2) - 
              2*pow(M1,4)*(-17*s*pow(M2,2) + pow(M2,4) + pow(s,2)) + 
              (-4*s*pow(M2,2) + pow(M2,4) + pow(s,2))*pow(-s + pow(M2,2),2)\
)))*pow(pow(M1,4) - 2*pow(M1,2)*pow(MZ,2) + pow(MZ,4) + 
        pow(MZ,2)*pow(wZ,2),-1)*
      pow(pow(M2,4) - 2*pow(M2,2)*pow(MZ,2) + pow(MZ,4) + 
        pow(MZ,2)*pow(wZ,2),-1)*
      pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
        pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
      pow(-(pow(cos(Theta),2)*
           (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),-2)\
)/589824. - ((gqL - gqR)*(gqL + gqR)*(gL - gR)*(gL + gR)*cos(Theta)*
     cos(theta2)*pow(el,2)*pow(eq,2)*pow(M1,-2)*pow(Pi,-5)*pow(s,-1)*
     (-((M1 - MZ)*(M1 + MZ)*(-2*pow(M1,2)*pow(M2,2) + 
            (pow(M1,2) + pow(M2,2))*pow(MZ,2))) + 
       (pow(M1,2) + pow(M2,2))*pow(MZ,2)*pow(wZ,2))*
     (-pow(M1,8) + 2*s*pow(M1,4)*pow(M2,2) + 2*pow(M1,6)*(s + pow(M2,2)) + 
       cos(2*Theta)*(-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
        (pow(M1,4) - pow(M2,4) - pow(s,2)) - 
       2*pow(M1,2)*(-7*s*pow(M2,4) + pow(M2,6) + pow(M2,2)*pow(s,2) + 
          pow(s,3)) + (pow(M2,4) + pow(s,2))*pow(-s + pow(M2,2),2))*
     pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
       pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
     pow(-(pow(cos(Theta),2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
            pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),-2)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1))/18432.;
}

double GetZZBackground_ThetaPhi1(EventParameters &event, bool UpType)
{
   double Pi = PI;
   
   double M1 = event.ZMass;
   double M2 = event.Z2Mass;
   if(M1 < M2)
      swap(M1, M2);

   double MH = event.HMass;
   double s = MH * MH;
   double x = (M1 * M1 - M2 * M2) / s;
   double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   double X = cos(event.Theta1);
   double Y = cos(event.Theta2);
   double Z = cos(event.Theta0);
   double X2 = cos(2 * event.Theta1);
   double Y2 = cos(2 * event.Theta2);
   double Z2 = cos(2 * event.Theta0);
   double theta1 = event.Theta1;
   double theta2 = event.Theta2;
   double Theta = event.Theta0;
   double MW = 80.4;
   double MZ = 91.1876;
   double wZ = 2.4952;
   double phi = event.Phi;
   double Phi1 = event.Phi0;
   
   double cw = MW / MZ;
   double sw2 = (1 - cw * cw);

   double g = 0.652;
   double gqL = (-2.0 / 3 * sw2 + 0.5) / cw * g;
   double gqR = (-2.0 / 3 * sw2) / cw * g;
   double gL = (sw2 - 0.5) / cw * g;
   double gR = (sw2) / cw * g;
   double EE = sqrt(4 * PI / 127);
   double el = -EE;
   double eq = -EE / 3;

   if(UpType == false)
   {
      gqL = (1.0 / 3 * sw2 - 0.5) / cw * g;
      gqR = (1.0 / 3 * sw2) / cw * g;
   }

return -((pow(gqL,4) + pow(gqR,4))*pow(M2,2)*pow(Pi,-6)*pow(s,-1)*
      pow(pow(gL,2) + pow(gR,2),2)*
      pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
        pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
      pow(-(pow(cos(Theta),2)*
           (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),
       -2)*pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
      pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
      (8*pow(M1,2)*pow(cos(Theta),4)*
         (6*(pow(M1,4) + pow(M2,4))*pow(s,2) - 
           5*(pow(M1,2) + pow(M2,2))*pow(s,3) + 2*pow(s,4) - 
           5*s*(pow(M1,2) + pow(M2,2))*pow(pow(M1,2) - pow(M2,2),2) + 
           2*pow(pow(M1,2) - pow(M2,2),4)) + 
        4*pow(cos(Theta),2)*(4*pow(M1,2)*
            (pow(M1,2)*(-3*s + pow(M2,2))*(s + pow(M2,2))*
               (-s + 4*pow(M2,2)) + pow(M1,6)*(3*s + 4*pow(M2,2)) - 
              pow(M1,4)*(9*s*pow(M2,2) + 8*pow(M2,4) + 6*pow(s,2)) + 
              3*s*pow(-(M2*s) + pow(M2,3),2)) + 
           s*((-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
               (3*pow(M1,4) + pow(M1,2)*(-4*s + 8*pow(M2,2)) + 
                 pow(-s + pow(M2,2),2)) + 
              4*pow(M1,2)*pow(cos(Phi1),2)*
               (2*pow(M1,6) - pow(M1,4)*(3*s + 4*pow(M2,2)) + 
                 2*pow(M1,2)*(-(s*pow(M2,2)) + pow(M2,4)) + 
                 s*pow(-s + pow(M2,2),2)))*pow(sin(Theta),2)) - 
        pow(-s + pow(M1,2) + pow(M2,2),2)*
         (8*pow(M1,2)*(5*s*(pow(M1,2) + pow(M2,2)) + 2*pow(s,2) + 
              2*pow(pow(M1,2) - pow(M2,2),2) + 
              s*pow(sin(Theta),2)*
               (-3*(M1 - M2)*(M1 + M2) + 
                 2*pow(cos(Phi1),2)*
                  (s + 2*pow(M1,2) - 4*pow(M2,2) - s*pow(sin(Theta),2)))) + 
           s*(pow(M1,4) - 2*pow(M1,2)*(2*s + pow(M2,2)) + 
              pow(-s + pow(M2,2),2))*pow(sin(2*Theta),2))))/884736. + 
  (M1*cos(Phi1)*(-pow(gqL,4) + pow(gqR,4))*(-pow(gL,2) + pow(gR,2))*
     (pow(gL,2) + pow(gR,2))*pow(Pi,-5)*pow(s,-1)*
     pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
       pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
     (-4*pow(s,0.5)*pow(cos(Theta),2)*
        (pow(M1,6) - pow(M1,4)*(s + 3*pow(M2,2)) + 
          pow(M1,2)*(-6*s*pow(M2,2) + 3*pow(M2,4) - pow(s,2)) - 
          pow(-s + pow(M2,2),3))*
        pow(pow(cos(Theta),2)*
           (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2)) - pow(-s + pow(M1,2) + pow(M2,2),2),-1) \
+ 16*(-s + pow(M1,2) + pow(M2,2))*pow(cos(Theta),2)*
        pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
          pow(-s + pow(M2,2),2),0.5)*
        (pow(s,2.5)*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),0.5) - 
          pow(pow(M1,2) + pow(M2,2),2)*
           pow(s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
               pow(-s + pow(M2,2),2)),0.5))*
        pow(-(pow(cos(Theta),2)*
             (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
               pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),
         -2) + 2*pow(s,0.5)*pow(-(pow(cos(Theta),2)*
             (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
               pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),
         -2)*(pow(-s + pow(M1,2) + pow(M2,2),2)*
           (pow(M1,6) + pow(M1,4)*(-s + 13*pow(M2,2)) + 
             cos(2*Theta)*(-s + pow(M1 - M2,2))*
              (s + pow(M1,2) - pow(M2,2))*(-s + pow(M1 + M2,2)) - 
             pow(M1,2)*(-22*s*pow(M2,2) + 13*pow(M2,4) + pow(s,2)) - 
             pow(-s + pow(M2,2),3) - 
             8*s*pow(M1,2)*pow(M2,2)*pow(sin(Theta),2)) + 
          pow(cos(Theta),2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))*
           (5*pow(M1,6) + pow(M1,4)*(-5*s + pow(M2,2)) + 
             cos(2*Theta)*(-s + pow(M1 - M2,2))*
              (s + pow(M1,2) - pow(M2,2))*(-s + pow(M1 + M2,2)) - 
             pow(M1,2)*(50*s*pow(M2,2) + 17*pow(M2,4) + 5*pow(s,2)) + 
             (5*s + 11*pow(M2,2))*pow(-s + pow(M2,2),2) + 
             8*s*pow(M1,2)*pow(M2,2)*pow(sin(Theta),2))))*sin(Theta))/
   2.359296e6;
}

double GetZZBackground_Thetaphi(EventParameters &event, bool UpType)
{
   double Pi = PI;
   
   double M1 = event.ZMass;
   double M2 = event.Z2Mass;
   if(M1 < M2)
      swap(M1, M2);

   double MH = event.HMass;
   double s = MH * MH;
   double x = (M1 * M1 - M2 * M2) / s;
   double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   double X = cos(event.Theta1);
   double Y = cos(event.Theta2);
   double Z = cos(event.Theta0);
   double X2 = cos(2 * event.Theta1);
   double Y2 = cos(2 * event.Theta2);
   double Z2 = cos(2 * event.Theta0);
   double theta1 = event.Theta1;
   double theta2 = event.Theta2;
   double Theta = event.Theta0;
   double MW = 80.4;
   double MZ = 91.1876;
   double wZ = 2.4952;
   double phi = event.Phi;
   double Phi1 = event.Phi0;
   
   double cw = MW / MZ;
   double sw2 = (1 - cw * cw);

   double g = 0.652;
   double gqL = (-2.0 / 3 * sw2 + 0.5) / cw * g;
   double gqR = (-2.0 / 3 * sw2) / cw * g;
   double gL = (sw2 - 0.5) / cw * g;
   double gR = (sw2) / cw * g;
   double EE = sqrt(4 * PI / 127);
   double el = -EE;
   double eq = -EE / 3;

   if(UpType == false)
   {
      gqL = (1.0 / 3 * sw2 - 0.5) / cw * g;
      gqR = (1.0 / 3 * sw2) / cw * g;
   }

return -(cos(phi)*(pow(gqL,4) + pow(gqR,4))*pow(gL - gR,2)*pow(gL + gR,2)*
      pow(M1,3)*pow(M2,3)*pow(Pi,-4)*
      pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
        pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
      pow(-(pow(cos(Theta),2)*
           (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),
       -2)*pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
      pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
      (pow(-s + pow(M1,2) + pow(M2,2),2)*(-2 + pow(sin(Theta),2)) + 
        pow(cos(Theta),2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
           pow(-s + pow(M2,2),2))*(2 + pow(sin(Theta),2))))/196608. - 
  ((pow(gqL,4) + pow(gqR,4))*pow(Pi,-6)*pow(s,-1)*
     pow(pow(gL,2) + pow(gR,2),2)*
     pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
       pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
     pow(-(pow(cos(Theta),2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
            pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),-2)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
     (4*pow(M1,2)*pow(M2,2)*pow(cos(Theta),4)*
        (2*(3*pow(M1,4) - 2*pow(M1,2)*pow(M2,2) + 3*pow(M2,4))*pow(s,2) - 
          6*(pow(M1,2) + pow(M2,2))*pow(s,3) + 3*pow(s,4) - 
          6*s*(pow(M1,2) + pow(M2,2))*pow(pow(M1,2) - pow(M2,2),2) + 
          3*pow(pow(M1,2) - pow(M2,2),4) + 
          2*pow(cos(phi),2)*pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),2)) - 
       4*pow(cos(Theta),2)*(-2*pow(M1,2)*pow(M2,2)*
           (pow(M1,8) + 2*pow(M1,6)*(s + 3*pow(M2,2)) - 
             2*pow(M1,4)*(9*s*pow(M2,2) + 7*pow(M2,4) + 3*pow(s,2)) + 
             2*pow(M1,2)*(-9*s*pow(M2,4) + 3*pow(M2,6) - 
                7*pow(M2,2)*pow(s,2) + pow(s,3)) + 
             (4*s*pow(M2,2) + pow(M2,4) + pow(s,2))*pow(-s + pow(M2,2),2)) \
+ (-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
           (-(s*(pow(M1,6) + pow(M1,4)*(-2*s + 11*pow(M2,2)) + 
                  pow(M1,2)*(-8*s*pow(M2,2) + 11*pow(M2,4) + pow(s,2)) + 
                  pow(-(M2*s) + pow(M2,3),2))*pow(sin(Theta),2)) + 
             4*pow(M1,2)*pow(M2,2)*pow(cos(phi),2)*
              (pow(M1,4) - 2*s*(pow(M1,2) + pow(M2,2)) + pow(M2,4) + 
                pow(s,2) + s*(-s + pow(M1,2) + pow(M2,2))*pow(sin(Theta),2))\
)) + pow(-s + pow(M1,2) + pow(M2,2),2)*
        (4*pow(M1,2)*pow(M2,2)*
           (-8*s*(pow(M1,2) + pow(M2,2)) - 5*pow(s,2) - 
             5*pow(pow(M1,2) - pow(M2,2),2) + 
             2*pow(cos(phi),2)*
              (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2) + 
                2*s*(-s + pow(M1,2) + pow(M2,2))*pow(sin(Theta),2)) + 
             (2 + cos(2*phi))*pow(s,2)*pow(sin(Theta),4)) - 
          s*(pow(M1,6) - pow(M1,4)*(2*s + pow(M2,2)) + 
             pow(M1,2)*(-8*s*pow(M2,2) - pow(M2,4) + pow(s,2)) + 
             pow(-(M2*s) + pow(M2,3),2))*pow(sin(2*Theta),2))))/884736.;
}

double GetZZBackground_ThetaTheta1(EventParameters &event, bool UpType)
{
   double Pi = PI;
   
   double M1 = event.ZMass;
   double M2 = event.Z2Mass;
   if(M1 < M2)
      swap(M1, M2);

   double MH = event.HMass;
   double s = MH * MH;
   double x = (M1 * M1 - M2 * M2) / s;
   double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   double X = cos(event.Theta1);
   double Y = cos(event.Theta2);
   double Z = cos(event.Theta0);
   double X2 = cos(2 * event.Theta1);
   double Y2 = cos(2 * event.Theta2);
   double Z2 = cos(2 * event.Theta0);
   double theta1 = event.Theta1;
   double theta2 = event.Theta2;
   double Theta = event.Theta0;
   double MW = 80.4;
   double MZ = 91.1876;
   double wZ = 2.4952;
   double phi = event.Phi;
   double Phi1 = event.Phi0;
   
   double cw = MW / MZ;
   double sw2 = (1 - cw * cw);

   double g = 0.652;
   double gqL = (-2.0 / 3 * sw2 + 0.5) / cw * g;
   double gqR = (-2.0 / 3 * sw2) / cw * g;
   double gL = (sw2 - 0.5) / cw * g;
   double gR = (sw2) / cw * g;
   double EE = sqrt(4 * PI / 127);
   double el = -EE;
   double eq = -EE / 3;

   if(UpType == false)
   {
      gqL = (1.0 / 3 * sw2 - 0.5) / cw * g;
      gqR = (1.0 / 3 * sw2) / cw * g;
   }

return -(cos(Theta)*cos(theta1)*(pow(gqL,4) - pow(gqR,4))*(pow(gL,4) - pow(gR,4))*
      pow(M1,2)*pow(M2,2)*pow(Pi,-5)*pow(s,-1)*
      pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
        pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
      pow(-(pow(cos(Theta),2)*
           (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),
       -2)*pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
      pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
      (pow(cos(Theta),2)*(pow(M1,8) - 2*s*pow(M1,4)*pow(M2,2) - 
           pow(M1,6)*(s + 2*pow(M2,2)) + 
           pow(M1,2)*(-s + pow(M2,2))*(s + pow(M2,2))*(s + 2*pow(M2,2)) - 
           (s + pow(M2,2))*pow(-s + pow(M2,2),3)) - 
        (-s + pow(M1,2) + pow(M2,2))*
         (s*pow(M2,2)*(3*pow(M1,2) + pow(M2,2)) + pow(M2,2)*pow(s,2) - 
           pow(s,3) + pow(pow(M1,2) - pow(M2,2),3) + 
           s*pow(M1,2)*(s - pow(M1,2) + pow(M2,2))*pow(sin(Theta),2))))/
   18432. - ((pow(gqL,4) + pow(gqR,4))*pow(Pi,-5)*pow(s,-1)*
     pow(pow(gL,2) + pow(gR,2),2)*
     pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
       pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
     pow(-(pow(cos(Theta),2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
            pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),-2)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
     (4*pow(M1,2)*pow(M2,2)*pow(cos(Theta),4)*
        (pow(cos(theta1),2)*(3*pow(M1,8) - 12*pow(M1,6)*pow(M2,2) + 
             6*pow(M1,4)*(-s + pow(M2,2))*(s + 3*pow(M2,2)) + 
             4*pow(M1,2)*pow(M2,2)*
              (6*s*pow(M2,2) - 3*pow(M2,4) + pow(s,2)) + 
             3*pow(-s + pow(M2,2),4)) + 
          (-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
           pow(s - pow(M1,2) + pow(M2,2),2) + 
          pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),2)*pow(sin(theta1),2)) - 
       pow(-s + pow(M1,2) + pow(M2,2),2)*
        (pow(M2,2)*(4*pow(M1,2)*
              (3*(s + pow(M1 - M2,2))*(s + pow(M1 + M2,2)) + 
                pow(cos(theta1),2)*
                 (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                   pow(-s + pow(M2,2),2)) + 
                4*s*(-pow(M1,2) + pow(M2,2))*pow(sin(Theta),2)) + 
             s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2))*pow(sin(2*Theta),2)) + 
          pow(M1,2)*(-4*pow(M2,2)*
              (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2) + 
                2*s*pow(sin(Theta),2)*
                 (-s - 2*pow(M1,2) + 4*pow(M2,2) + s*pow(sin(Theta),2))) + 
             s*(pow(M1,4) - 4*s*pow(M2,2) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(M2,4) + pow(s,2))*pow(sin(2*Theta),2))*
           pow(sin(theta1),2)) - 
       4*pow(cos(Theta),2)*(-2*pow(M1,2)*pow(M2,2)*
           (pow(M1,8) + 2*pow(M1,6)*(s + pow(M2,2)) + pow(M2,8) - 
             2*pow(M2,4)*pow(s,2) - 
             2*pow(M1,4)*(4*s*pow(M2,2) + 3*pow(M2,4) + 3*pow(s,2)) + 
             2*pow(M1,2)*(-9*s*pow(M2,4) + pow(M2,6) - 
                5*pow(M2,2)*pow(s,2) + pow(s,3)) + pow(s,4)) + 
          2*pow(M1,2)*pow(M2,2)*pow(cos(theta1),2)*
           (pow(M1,8) + 2*pow(M1,6)*(s - 3*pow(M2,2)) + 
             2*pow(M1,4)*(6*s*pow(M2,2) + 5*pow(M2,4) - 3*pow(s,2)) - 
             2*pow(M1,2)*(9*s*pow(M2,4) + 3*pow(M2,6) + 
                pow(M2,2)*pow(s,2) - pow(s,3)) + pow(-s + pow(M2,2),4) - 
             2*s*pow(M1,2)*pow(s - pow(M1,2) + pow(M2,2),2)*
              pow(sin(Theta),2)) + 
          (-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
           (s*pow(M2,2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2))*pow(sin(Theta),2) + 
             pow(M1,2)*(2*pow(M2,2)*
                 (-2*s*pow(M1,2) + pow(M1,4) + pow(-s + pow(M2,2),2)) + 
                s*(pow(M1,4) - 2*s*(pow(M1,2) + 2*pow(M2,2)) + 
                   3*pow(M2,4) + pow(s,2))*pow(sin(Theta),2))*
              pow(sin(theta1),2))) + 
       4*s*cos(Theta)*(-s + pow(M1 - M2,2))*(-s + pow(M1,2) + pow(M2,2))*
        (-s + pow(M1 + M2,2))*(pow(M2,2)*(-s + pow(M1,2) + pow(M2,2)) + 
          pow(M1,2)*(-s + pow(M1,2) + 2*pow(M2,2))*pow(sin(theta1),2))*
        sin(Theta)*sin(2*Theta)))/589824.;
}

double GetZZBackground_ThetaTheta2(EventParameters &event, bool UpType)
{
   double Pi = PI;
   
   double M1 = event.ZMass;
   double M2 = event.Z2Mass;
   if(M1 < M2)
      swap(M1, M2);

   double MH = event.HMass;
   double s = MH * MH;
   double x = (M1 * M1 - M2 * M2) / s;
   double beta1 = sqrt(1 - (4 * M1 * M1) / (s * (1 + x) * (1 + x)));
   double beta2 = sqrt(1 - (4 * M2 * M2) / (s * (1 - x) * (1 - x)));
   double gamma1 = 1 / sqrt(1 - beta1 * beta1);
   double gamma2 = 1 / sqrt(1 - beta2 * beta2);
   double X = cos(event.Theta1);
   double Y = cos(event.Theta2);
   double Z = cos(event.Theta0);
   double X2 = cos(2 * event.Theta1);
   double Y2 = cos(2 * event.Theta2);
   double Z2 = cos(2 * event.Theta0);
   double theta1 = event.Theta1;
   double theta2 = event.Theta2;
   double Theta = event.Theta0;
   double MW = 80.4;
   double MZ = 91.1876;
   double wZ = 2.4952;
   double phi = event.Phi;
   double Phi1 = event.Phi0;
   
   double cw = MW / MZ;
   double sw2 = (1 - cw * cw);

   double g = 0.652;
   double gqL = (-2.0 / 3 * sw2 + 0.5) / cw * g;
   double gqR = (-2.0 / 3 * sw2) / cw * g;
   double gL = (sw2 - 0.5) / cw * g;
   double gR = (sw2) / cw * g;
   double EE = sqrt(4 * PI / 127);
   double el = -EE;
   double eq = -EE / 3;

   if(UpType == false)
   {
      gqL = (1.0 / 3 * sw2 - 0.5) / cw * g;
      gqR = (1.0 / 3 * sw2) / cw * g;
   }

return -(cos(Theta)*cos(theta2)*(pow(gqL,4) - pow(gqR,4))*(pow(gL,4) - pow(gR,4))*
      pow(M1,2)*pow(M2,2)*pow(Pi,-5)*pow(s,-1)*
      pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
        pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
      pow(-(pow(cos(Theta),2)*
           (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),
       -2)*pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
      pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
      (pow(cos(Theta),2)*(pow(M1,8) - s*pow(M1,4)*pow(M2,2) - 
           2*pow(M1,6)*(s + pow(M2,2)) + 
           2*pow(M1,2)*(s + pow(M2,2))*(pow(M2,4) + pow(s,2)) - 
           (s*pow(M2,2) + pow(M2,4) + pow(s,2))*pow(-s + pow(M2,2),2)) - 
        (-s + pow(M1,2) + pow(M2,2))*
         (-(s*pow(M1,2)*(pow(M1,2) + 3*pow(M2,2))) - pow(M1,2)*pow(s,2) + 
           pow(s,3) + pow(pow(M1,2) - pow(M2,2),3) + 
           s*pow(M2,2)*(-s - pow(M1,2) + pow(M2,2))*pow(sin(Theta),2))))/
   18432. - ((pow(gqL,4) + pow(gqR,4))*pow(Pi,-5)*pow(s,-1)*
     pow(pow(gL,2) + pow(gR,2),2)*
     pow(1 - 2*(pow(M1,2) + pow(M2,2))*pow(s,-1) + 
       pow(s,-2)*pow(pow(M1,2) - pow(M2,2),2),0.5)*
     pow(-(pow(cos(Theta),2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
            pow(-s + pow(M2,2),2))) + pow(-s + pow(M1,2) + pow(M2,2),2),-2)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M1,2) - pow(MZ,2),2),-1)*
     pow(pow(MZ,2)*pow(wZ,2) + pow(pow(M2,2) - pow(MZ,2),2),-1)*
     (4*pow(M1,2)*pow(M2,2)*pow(cos(Theta),4)*
        ((-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
           pow(s + pow(M1,2) - pow(M2,2),2) + 
          pow(cos(theta2),2)*(2*
              (9*pow(M1,4) + 2*pow(M1,2)*pow(M2,2) - 3*pow(M2,4))*pow(s,2) \
- 12*pow(M1,2)*pow(s,3) + 3*pow(s,4) + 3*pow(pow(M1,2) - pow(M2,2),4) - 
             12*s*pow(pow(M1,3) - M1*pow(M2,2),2)) + 
          pow(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
             pow(-s + pow(M2,2),2),2)*pow(sin(theta2),2)) - 
       pow(-s + pow(M1,2) + pow(M2,2),2)*
        (pow(M1,2)*(4*pow(M2,2)*
              (3*(s + pow(M1 - M2,2))*(s + pow(M1 + M2,2)) + 
                pow(cos(theta2),2)*
                 (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                   pow(-s + pow(M2,2),2)) + 
                4*(M1 - M2)*(M1 + M2)*s*pow(sin(Theta),2)) + 
             s*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2))*pow(sin(2*Theta),2)) + 
          pow(M2,2)*(-4*pow(M1,2)*
              (pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2) + 
                2*s*pow(sin(Theta),2)*
                 (-s + 4*pow(M1,2) - 2*pow(M2,2) + s*pow(sin(Theta),2))) + 
             s*(pow(M1,4) - 2*pow(M1,2)*(2*s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2))*pow(sin(2*Theta),2))*
           pow(sin(theta2),2)) - 
       4*pow(cos(Theta),2)*(-2*pow(M1,2)*pow(M2,2)*
           (pow(M1,8) + 2*pow(M1,6)*pow(M2,2) + 
             2*pow(M1,2)*pow(M2,2)*(-5*s + pow(M2,2))*(s + pow(M2,2)) - 
             2*pow(M1,4)*(9*s*pow(M2,2) + 3*pow(M2,4) + pow(s,2)) + 
             (4*s*pow(M2,2) + pow(M2,4) + pow(s,2))*pow(-s + pow(M2,2),2)) \
+ 2*pow(M1,2)*pow(M2,2)*pow(cos(theta2),2)*
           (pow(M1,8) - 2*pow(M1,6)*(2*s + 3*pow(M2,2)) + 
             2*pow(M1,4)*(-9*s*pow(M2,2) + 5*pow(M2,4) + 3*pow(s,2)) - 
             2*pow(M1,2)*(-6*s*pow(M2,4) + 3*pow(M2,6) + 
                pow(M2,2)*pow(s,2) + 2*pow(s,3)) + 
             (4*s*pow(M2,2) + pow(M2,4) + pow(s,2))*
              pow(-s + pow(M2,2),2) - 
             2*s*pow(M2,2)*pow(s + pow(M1,2) - pow(M2,2),2)*
              pow(sin(Theta),2)) + 
          (-s + pow(M1 - M2,2))*(-s + pow(M1 + M2,2))*
           (s*pow(M1,2)*(pow(M1,4) - 2*pow(M1,2)*(s + pow(M2,2)) + 
                pow(-s + pow(M2,2),2))*pow(sin(Theta),2) + 
             pow(M2,2)*(2*pow(M1,2)*
                 (-2*s*pow(M1,2) + pow(M1,4) + pow(-s + pow(M2,2),2)) + 
                s*(-4*s*pow(M1,2) + 3*pow(M1,4) + pow(-s + pow(M2,2),2))*
                 pow(sin(Theta),2))*pow(sin(theta2),2))) + 
       4*s*cos(Theta)*(-s + pow(M1 - M2,2))*(-s + pow(M1,2) + pow(M2,2))*
        (-s + pow(M1 + M2,2))*(pow(M1,2)*(-s + pow(M1,2) + pow(M2,2)) + 
          pow(M2,2)*(-s + 2*pow(M1,2) + pow(M2,2))*pow(sin(theta2),2))*
        sin(Theta)*sin(2*Theta)))/589824.;
}

