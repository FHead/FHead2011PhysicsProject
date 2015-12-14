#include <cmath>
using namespace std;

#include "InterpretCoefficient.h"
#include "Constants.h"
   
InterpretationCoefficients::InterpretationCoefficients()
   : mh(125), mw(CONST_MW), mt(172), yt(1), yta(0), c3(0), c4(0), gww(2), rho(1), gv(1)
{
}

void InterpretationCoefficients::Print()
{
   cout << "mh = " << mh << endl;
   cout << "mw = " << mw << endl;
   cout << "mt = " << mt << endl;
   cout << "yt = " << yt << endl;
   cout << "yta = " << yta << endl;
   cout << "c3 = " << c3 << endl;
   cout << "c4 = " << c4 << endl;
   cout << "gww = " << gww << endl;
   cout << "rho = " << rho << endl;
   cout << "gv = " << gv << endl;
}

double InterpretedA2ZZ_Toy(const InterpretationCoefficients &c)
{
   return c.mw;
}

double InterpretedA3ZZ_Toy(const InterpretationCoefficients &c)
{
   return c.mt;
}

double InterpretedA4ZZ_Toy(const InterpretationCoefficients &c)
{
   return 0;
}

double InterpretedA2ZA_Toy(const InterpretationCoefficients &c)
{
   return c.yt;
}

double InterpretedA3ZA_Toy(const InterpretationCoefficients &c)
{
   return c.yta;
}

double InterpretedA2AA_Toy(const InterpretationCoefficients &c)
{
   return c.c3 + c.c4;
}

double InterpretedA3AA_Toy(const InterpretationCoefficients &c)
{
   return c.rho * c.gv;
}

double InterpretedA2ZA_Roberto13364(const InterpretationCoefficients &c)
{
   double tW = sqrt(CONST_SW2 / (1 - CONST_SW2));
   double alpha = CONST_ALPHA;
   double mt = c.mt;
   double v = CONST_VH * c.gv;
   double yt = c.yt;
   double mh = c.mh;
   double PI = CONST_PI;

   double WContribution = -0.0056799;

   return (8*alpha*mt*tW*v*yt*pow(2,0.5)*pow(mh,-4)*pow(PI,-1)*
    (pow(mh,2) + (pow(mh,2) - 4*pow(mt,2))*pow(acsc(2*mt*pow(mh,-1)),2)))/3. + WContribution;
}

double InterpretedA3ZA_Roberto13364(const InterpretationCoefficients &c)
{
   double tW = sqrt(CONST_SW2 / (1 - CONST_SW2));
   double alpha = CONST_ALPHA;
   double mt = c.mt;
   double v = CONST_VH * c.gv;
   double ytA = c.yta;
   double mh = c.mh;
   double PI = CONST_PI;

   return (-16*alpha*mt*tW*v*ytA*pow(2,0.5)*pow(mh,-2)*pow(PI,-1)*
    pow(acsc(2*mt*pow(mh,-1)),2))/3.;
}

double InterpretedA2AA_Roberto13364(const InterpretationCoefficients &c)
{
   double tW = sqrt(CONST_SW2 / (1 - CONST_SW2));
   double alpha = CONST_ALPHA;
   double mt = c.mt;
   double v = CONST_VH * c.gv;
   double yt = c.yt;
   double mh = c.mh;
   double PI = CONST_PI;

   double WContribution = -0.0103925;

   return (8*alpha*mt*v*yt*pow(2,0.5)*pow(mh,-4)*pow(PI,-1)*
    (pow(mh,2) + (pow(mh,2) - 4*pow(mt,2))*pow(acsc(2*mt*pow(mh,-1)),2)))/3. + WContribution;
}

double InterpretedA3AA_Roberto13364(const InterpretationCoefficients &c)
{
   double tW = sqrt(CONST_SW2 / (1 - CONST_SW2));
   double alpha = CONST_ALPHA;
   double mt = c.mt;
   double v = CONST_VH * c.gv;
   double ytA = c.yta;
   double mh = c.mh;
   double PI = CONST_PI;

   return (-16*alpha*mt*v*ytA*pow(2,0.5)*pow(mh,-2)*pow(PI,-1)*
    pow(acsc(2*mt*pow(mh,-1)),2))/3.;
}

double acsc(double x)
{
   return asin(1 / x);
}

double InterpretedA2AA_Roberto13366(const InterpretationCoefficients &c)
{
   return InterpretedA2AA_Top_Roberto13366(c)
      + InterpretedA2AA_W_Roberto13366(c);
}

double InterpretedA3AA_Roberto13366(const InterpretationCoefficients &c)
{
   return InterpretedA3AA_Top_Roberto13366(c)
      + InterpretedA3AA_W_Roberto13366(c);
}

double InterpretedA2AA_Top_Roberto13366(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double Nc = CONST_NC;
   double yt = c.yt;
   double Pi = CONST_PI;
   double Qt = 2.0 / 3;   // top charge, set to constant for now
   double Rt = (c.mh / 2 / c.mt) * (c.mh / 2 / c.mt);

   return aem*Nc*yt*pow(2,-0.5)*pow(Pi,-1)*pow(Qt,2)*pow(Rt,-2)*
     (Rt + (-1 + Rt)*pow(asin(pow(Rt,0.5)),2));
}

double InterpretedA3AA_Top_Roberto13366(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double Nc = CONST_NC;
   double ytA = c.yta;
   double Pi = CONST_PI;
   double Qt = 2.0 / 3;   // top charge, set to constant for now
   double Rt = (c.mh / 2 / c.mt) * (c.mh / 2 / c.mt);
   
   return -(aem*Nc*ytA*pow(2,0.5)*pow(Pi,-1)*pow(Qt,2)*pow(Rt,-1)*
    pow(asin(pow(Rt,0.5)),2));
}

double InterpretedA2AA_W_Roberto13366(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double gWW = c.gww;
   double Pi = CONST_PI;
   double QW = 1;   // charge of W set to const for now
   double RW = (c.mh / 2 / c.mw) * (c.mh / 2 / c.mw);   // make sure default for mw is the SM one

   return -(aem*gWW*pow(Pi,-1)*pow(QW,2)*pow(RW,-2)*
     (RW*(3 + 2*RW) + (-3 + 6*RW)*pow(asin(pow(RW,0.5)),2)))/4.;
}

double InterpretedA3AA_W_Roberto13366(const InterpretationCoefficients &c)
{
   return 0;
}

double InterpretedA2ZA_Roberto13711(const InterpretationCoefficients &c)
{
   return InterpretedA2ZA_Top_Roberto13711(c)
      + InterpretedA2ZA_W_Roberto13711(c);
}

double InterpretedA3ZA_Roberto13711(const InterpretationCoefficients &c)
{
   return InterpretedA3ZA_Top_Roberto13711(c)
      + InterpretedA3ZA_W_Roberto13711(c);
}

double InterpretedA2AA_Roberto13711(const InterpretationCoefficients &c)
{
   return InterpretedA2AA_Top_Roberto13711(c)
      + InterpretedA2AA_W_Roberto13711(c);
}

double InterpretedA3AA_Roberto13711(const InterpretationCoefficients &c)
{
   return InterpretedA3AA_Top_Roberto13711(c)
      + InterpretedA3AA_W_Roberto13711(c);
}

double InterpretedA2ZA_Top_Roberto13711(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double Nc = CONST_NC;
   double yt = c.yt;
   double Pi = CONST_PI;
   double Qt = 2.0 / 3;   // top charge, set to constant for now
   double Rt = (c.mh / 2 / c.mt) * (c.mh / 2 / c.mt);
   double mt = c.mt;
   double mh = c.mh;
   double M1 = CONST_MZ;
   double cW = CONST_CW;
   double sW = CONST_SW;
   double T3 = 0.5;   // TODO WHAT IS THIS
  
   return 2*aem*mt*Nc*Qt*yt*pow(cW,-1)*pow(mh,-1)*pow(Pi,-1)*pow(sW,-1)*
  (-T3 + 2*Qt*pow(sW,2))*pow(pow(M1,2) - pow(mh,2),-2)*
  pow(4 - pow(M1,2)*pow(mt,-2),-0.5)*
  (-2*M1*mh*acsc(2*mt*pow(M1,-1))*(pow(M1,2) - 4*pow(mt,2)) + 
    mh*(-pow(M1,2) + pow(mh,2))*pow(-pow(M1,2) + 4*pow(mt,2),0.5) + 
    mh*(pow(M1,2) - pow(mh,2) + 4*pow(mt,2))*pow(acsc(2*mt*pow(M1,-1)),2)*
     pow(-pow(M1,2) + 4*pow(mt,2),0.5) + 
    mh*(-pow(M1,2) + pow(mh,2) - 4*pow(mt,2))*pow(acsc(2*mt*pow(mh,-1)),2)*
     pow(-pow(M1,2) + 4*pow(mt,2),0.5) - 
    2*acsc(2*mt*pow(mh,-1))*pow(M1,2)*
     pow(-((pow(M1,2) - 4*pow(mt,2))*(-pow(mh,2) + 4*pow(mt,2))),0.5));

//    return 2*aem*mt*Nc*Qt*yt*pow(cW,-1)*pow(mh,-1)*pow(Pi,-1)*pow(sW,-1)*
//   (-T3 + 2*Qt*pow(sW,2))*pow(pow(M1,2) - pow(mh,2),-2)*
//   pow(4 - pow(M1,2)*pow(mt,-2),-0.5)*
//   (-2*M1*mh*asin(M1/2/mt)*(pow(M1,2) - 4*pow(mt,2)) + 
//     mh*(-pow(M1,2) + pow(mh,2))*pow(-pow(M1,2) + 4*pow(mt,2),0.5) + 
//     mh*(pow(M1,2) - pow(mh,2) + 4*pow(mt,2))*pow(asin(M1/2/mt),2)*
//      pow(-pow(M1,2) + 4*pow(mt,2),0.5) + 
//     mh*(-pow(M1,2) + pow(mh,2) - 4*pow(mt,2))*pow(acsc(2*mt*pow(mh,-1)),2)*
//      pow(-pow(M1,2) + 4*pow(mt,2),0.5) - 
//     2*acsc(2*mt*pow(mh,-1))*pow(M1,2)*
//      pow(-((pow(M1,2) - 4*pow(mt,2))*(-pow(mh,2) + 4*pow(mt,2))),0.5));
}

double InterpretedA3ZA_Top_Roberto13711(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double Nc = CONST_NC;
   double ytA = c.yta;
   double Pi = CONST_PI;
   double Qt = 2.0 / 3;   // top charge, set to constant for now
   double Rt = (c.mh / 2 / c.mt) * (c.mh / 2 / c.mt);
   double mt = c.mt;
   double mh = c.mh;
   double M1 = CONST_MZ;
   double cW = CONST_CW;
   double sW = CONST_SW;
   double T3 = 0.5;   // TODO WHAT IS THIS
  
   return 2*aem*Nc*Qt*ytA*pow(cW,-1)*pow(M1 - mh,-1)*pow(M1 + mh,-1)*pow(mt,2)*
  pow(Pi,-1)*pow(sW,-1)*(-T3 + 2*Qt*pow(sW,2))*
  (pow(acsc(2*mt*pow(M1,-1)),2) - pow(acsc(2*mt*pow(mh,-1)),2));
}

double InterpretedA2ZA_W_Roberto13711(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double gWW = c.gww;
   double Pi = CONST_PI;
   double QW = 1;   // charge of W set to const for now
   double RW = (c.mh / 2 / c.mw) * (c.mh / 2 / c.mw);   // make sure default for mw is the SM one
   double M1 = CONST_MZ;   // leading term
   double sW = CONST_SW;
   double cW = CONST_CW;
   double tW = CONST_TW;
   double mW = c.mw;
   double mh = c.mh;

   return (aem*cW*gWW*pow(mh,-4)*pow(Pi,-1)*pow(sW,-1)*
    pow(-1 + pow(M1,2)*pow(mh,-2),-2)*
    ((pow(M1,2) - pow(mh,2))*(2*pow(mW,2)*(-5 + pow(tW,2)) + 
         pow(mh,2)*(-1 + pow(tW,2))) + 
      4*pow(mW,2)*((pow(mh,2) - 2*pow(mW,2))*(-5 + pow(tW,2)) - 
         2*pow(M1,2)*(-3 + pow(tW,2)))*pow(asin((M1*pow(mW,-1))/2.),2) + 
      4*pow(mW,2)*(-((pow(mh,2) - 2*pow(mW,2))*(-5 + pow(tW,2))) + 
         2*pow(M1,2)*(-3 + pow(tW,2)))*pow(asin((mh*pow(mW,-1))/2.),2) - 
      2*asin((M1*pow(mW,-1))/2.)*pow(M1,2)*
       (2*pow(mW,2)*(-5 + pow(tW,2)) + pow(mh,2)*(-1 + pow(tW,2)))*
       pow(-1 + 4*pow(M1,-2)*pow(mW,2),0.5) + 
      2*asin((mh*pow(mW,-1))/2.)*pow(M1,2)*
       (2*pow(mW,2)*(-5 + pow(tW,2)) + pow(mh,2)*(-1 + pow(tW,2)))*
       pow(-1 + 4*pow(mh,-2)*pow(mW,2),0.5)))/4.;
      
   // return (aem*cW*gWW*pow(mh,-4)*pow(Pi,-1)*pow(sW,-1)*
   //  pow(-1 + pow(M1,2)*pow(mh,-2),-2)*
   //  ((pow(M1,2) - pow(mh,2))*(2*pow(mW,2)*(-5 + pow(tW,2)) + 
   //       pow(mh,2)*(-1 + pow(tW,2))) + 
   //    4*pow(mW,2)*((pow(mh,2) - 2*pow(mW,2))*(-5 + pow(tW,2)) - 
   //       2*pow(M1,2)*(-3 + pow(tW,2)))*pow(asin((M1*pow(mW,-1))/2.),2) + 
   //    4*pow(mW,2)*(-((pow(mh,2) - 2*pow(mW,2))*(-5 + pow(tW,2))) + 
   //       2*pow(M1,2)*(-3 + pow(tW,2)))*pow(asin((mh*pow(mW,-1))/2.),2) +
   //    2*asin((mh*pow(mW,-1))/2.)*pow(M1,2)*
   //     (2*pow(mW,2)*(-5 + pow(tW,2)) + pow(mh,2)*(-1 + pow(tW,2)))*
   //     pow(-1 + 4*pow(mh,-2)*pow(mW,2),0.5)))/4.;
}

double InterpretedA3ZA_W_Roberto13711(const InterpretationCoefficients &c)
{
   return 0;
}

double InterpretedA2AA_Top_Roberto13711(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double Nc = CONST_NC;
   double yt = c.yt;
   double Pi = CONST_PI;
   double Qt = 2.0 / 3;   // top charge, set to constant for now
   double Rt = (c.mh / 2 / c.mt) * (c.mh / 2 / c.mt);
   double mh = c.mh;
   double mt = c.mt;

   return 4*aem*Nc*yt*pow(mh,-4)*pow(mt,2)*pow(Pi,-1)*pow(Qt,2)*
  (pow(mh,2) + (pow(mh,2) - 4*pow(mt,2))*pow(acsc(2*mt*pow(mh,-1)),2));
}

double InterpretedA3AA_Top_Roberto13711(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double Nc = CONST_NC;
   double ytA = c.yta;
   double Pi = CONST_PI;
   double Qt = 2.0 / 3;   // top charge, set to constant for now
   double Rt = (c.mh / 2 / c.mt) * (c.mh / 2 / c.mt);
   double mh = c.mh;
   double mt = c.mt;

   return -8*aem*Nc*ytA*pow(mh,-2)*pow(mt,2)*pow(Pi,-1)*pow(Qt,2)*
  pow(acsc(2*mt*pow(mh,-1)),2);
}

double InterpretedA2AA_W_Roberto13711(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double gWW = c.gww;
   double Pi = CONST_PI;
   double QW = 1;   // charge of W set to const for now
   double RW = (c.mh / 2 / c.mw) * (c.mh / 2 / c.mw);   // make sure default for mw is the SM one
   double sW = CONST_SW;
   double cW = CONST_CW;
   double tW = CONST_TW;
   double mW = c.mw;
   double mh = c.mh;

   return (aem*gWW*pow(mh,-4)*pow(Pi,-1)*pow(QW,2)*
    (-(pow(mh,2)*(pow(mh,2) + 6*pow(mW,2))) - 
      12*(pow(mh,2) - 2*pow(mW,2))*pow(mW,2)*pow(acsc(2*mW*pow(mh,-1)),2)))/2.;
}

double InterpretedA3AA_W_Roberto13711(const InterpretationCoefficients &c)
{
   return 0;
}

double InterpretedA2ZA_Roberto14167(const InterpretationCoefficients &c)
{
   return InterpretedA2ZA_Top_Roberto13711(c)
      + InterpretedA2ZA_W_Roberto13711(c);
}

double InterpretedA3ZA_Roberto14167(const InterpretationCoefficients &c)
{
   return InterpretedA3ZA_Top_Roberto14167(c)
      + InterpretedA3ZA_W_Roberto13711(c);
}

double InterpretedA2AA_Roberto14167(const InterpretationCoefficients &c)
{
   return InterpretedA2AA_Top_Roberto13711(c)
      + InterpretedA2AA_W_Roberto13711(c);
}

double InterpretedA3AA_Roberto14167(const InterpretationCoefficients &c)
{
   return InterpretedA3AA_Top_Roberto14167(c)
      + InterpretedA3AA_W_Roberto13711(c);
}

double InterpretedA3ZA_Top_Roberto14167(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double Nc = CONST_NC;
   double ytA = c.yta;
   double Pi = CONST_PI;
   double Qt = 2.0 / 3;   // top charge, set to constant for now
   double Rt = (c.mh / 2 / c.mt) * (c.mh / 2 / c.mt);
   double mt = c.mt;
   double mh = c.mh;
   double M1 = CONST_MZ;
   double cW = CONST_CW;
   double sW = CONST_SW;
   double T3 = 0.5;   // TODO WHAT IS THIS

   return -2*aem*Nc*Qt*ytA*pow(cW,-1)*pow(M1 - mh,-1)*pow(M1 + mh,-1)*pow(mt,2)*
  pow(Pi,-1)*pow(sW,-1)*(-T3 + 2*Qt*pow(sW,2))*
  (pow(acsc(2*mt*pow(M1,-1)),2) - pow(acsc(2*mt*pow(mh,-1)),2));

   /*
   return 2*aem*Nc*Qt*ytA*pow(cW,-1)*pow(M1 - mh,-1)*pow(M1 + mh,-1)*pow(mt,2)*
  pow(Pi,-1)*pow(sW,-1)*(-T3 + 2*Qt*pow(sW,2))*
  (pow(acsc(2*mt*pow(M1,-1)),2) - pow(acsc(2*mt*pow(mh,-1)),2));
   */
}

double InterpretedA3AA_Top_Roberto14167(const InterpretationCoefficients &c)
{
   double aem = CONST_ALPHA;
   double Nc = CONST_NC;
   double ytA = c.yta;
   double Pi = CONST_PI;
   double Qt = 2.0 / 3;   // top charge, set to constant for now
   double Rt = (c.mh / 2 / c.mt) * (c.mh / 2 / c.mt);
   double mh = c.mh;
   double mt = c.mt;

   return 4*aem*Nc*ytA*pow(mh,-2)*pow(mt,2)*pow(Pi,-1)*pow(Qt,2)*
  pow(acsc(2*mt*pow(mh,-1)),2);

   /*
   return -8*aem*Nc*ytA*pow(mh,-2)*pow(mt,2)*pow(Pi,-1)*pow(Qt,2)*
  pow(acsc(2*mt*pow(mh,-1)),2);
   */
}






