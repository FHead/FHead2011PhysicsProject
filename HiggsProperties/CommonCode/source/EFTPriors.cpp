#include <iostream>
#include <cmath>
using namespace std;

#include "Constants.h"

#include "EFTPriors.h"

double GetRAA_AVV(const AVVBasis &A)
{
   return A.A2AA * A.A2AA + A.A3AA * A.A3AA;
}

double GetRZA_AVV(const AVVBasis &A)
{
   return A.A2ZA * A.A2ZA + A.A3ZA * A.A3ZA;
}

double GetRHto4l_NoSquare_AVV(const AVVBasis &A)
{
   double A1ZZR = A.A1ZZ;
   double A2ZZR = A.A2ZZ;
   double A4ZZR = A.A4ZZ;
   double A2ZAR = A.A2ZA;
   double A4ZAR = A.A4ZA;
   double A2AZR = A.A2ZA;
   double A4AZR = A.A4ZA;
   double A2AAR = A.A2AA;

   return pow(A1ZZR,-2)*(0.0018*A1ZZR*A2AAR + 0.092*A1ZZR*A2AZR + 0.092*A1ZZR*A2ZAR - 0.14*A1ZZR*A2ZZR - 0.031*A1ZZR*A4AZR - 0.031*A1ZZR*A4ZAR + 0.49*A1ZZR*A4ZZR + pow(A1ZZR,2));
}

double GetRHto4l_NoSquare_Higgs(const HiggsBasis &H)
{
   double DeltaCZ = H.DeltaCZ;
   double CZB = H.CZB;
   double CZZ = H.CZZ;
   double CZA = H.CZA;
   double CAA = H.CAA;
   double SW = CONST_SW;
   double CW = CONST_CW;
   double AlphaEM = CONST_ALPHA;

   return (pow(1 + DeltaCZ,-2)*(0.04523893421169302*AlphaEM*CAA*(1 + DeltaCZ) + 4*pow(1 + DeltaCZ,2) + 12.315043202071989*AlphaEM*CZB*(1 + DeltaCZ)*pow(SW,-2) + 4.624424386084176*AlphaEM*CZA*(1 + DeltaCZ)*pow(CW,-1)*pow(SW,-1) - 1.5582299561805373*AlphaEM*(1 + DeltaCZ)*pow(CW,-1)*(-CZA + 2*CZB + CZZ - (CAA - 2*CZA + 2*CZB)*pow(SW,2) + CAA*pow(SW,4))*pow(SW - 2*pow(SW,3),-1) - 3.518583772020569*AlphaEM*CZZ*(1 + DeltaCZ)*pow(pow(SW,2) - pow(SW,4),-1)))/4.;
}

double GetRHto4l_NoSquare_Warsaw(const WarsawBasis &W)
{
   double CT = W.CT;
   double CH = W.CH;
   double CWW = W.CWW;
   double CWB = W.CWB;
   double CBB = W.CBB;
   double DeltaM = 0;
   double SW = CONST_SW;
   double CW = CONST_CW;
   double AlphaEM = CONST_ALPHA;
   double PI = CONST_PI;

   return (pow(SW,4)*pow(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2),-2)*(0.04523893421169302*AlphaEM*(CBB - 4*CWB + CWW)*pow(SW,-2)*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2)) + 4.624424386084176*AlphaEM*pow(CW,-1)*pow(SW,-3)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2)) + 1.96*pow(SW,-4)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2))*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2)) - 3.518583772020569*AlphaEM*pow(CW,-2)*pow(SW,-4)*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 0.496*pow(CW,-1)*pow(SW,-3)*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2))*(DeltaM - CT*pow(CW,2) + (-3 + 2*pow(SW,2))*(-2*AlphaEM*CWB*PI + DeltaM*pow(SW,2)))*pow(-1 + 2*pow(SW,2),-1) + 4*pow(SW,-4)*pow(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2),2)))/4.;
}

double GetRHto4l_WithSquare_AVV(const AVVBasis &A)
{
   double A1ZZR = A.A1ZZ;
   double A2ZZR = A.A2ZZ;
   double A3ZZR = A.A3ZZ;
   double A4ZZR = A.A4ZZ;
   double A1ZAR = A.A1ZA;
   double A2ZAR = A.A2ZA;
   double A3ZAR = A.A3ZA;
   double A4ZAR = A.A4ZA;
   double A1AZR = A.A1ZA;
   double A2AZR = A.A2ZA;
   double A3AZR = A.A3ZA;
   double A4AZR = A.A4ZA;
   double A1AAR = A.A1AA;
   double A2AAR = A.A2AA;
   double A3AAR = A.A3AA;
   double A4AAR = A.A4AA;

   return pow(A1ZZR,-2)*(0.0036*A1ZZR*A2AAR + 0.184*A1ZZR*A2AZR - 0.126*A2AAR*A2AZR + 0.184*A1ZZR*A2ZAR - 0.126*A2AAR*A2ZAR + (A2AZR*A2ZAR)/50000. - 0.28*A1ZZR*A2ZZR + (A2AAR*A2ZZR)/50000. - 0.032*A2AZR*A2ZZR - 0.032*A2ZAR*A2ZZR + (A2ZZR*A3AAR)/1.e6 - 0.1*A3AAR*A3AZR - 0.1*A3AAR*A3ZAR + 0.00082*A3AZR*A3ZAR + 0.00082*A3AAR*A3ZZR - 0.015*A3AZR*A3ZZR - 0.015*A3ZAR*A3ZZR - 0.062*A1ZZR*A4AZR + 0.038*A2AAR*A4AZR - 1.94*A2AZR*A4AZR + 0.00074*A2ZAR*A4AZR + 0.0084*A2ZZR*A4AZR - 0.062*A1ZZR*A4ZAR + 0.038*A2AAR*A4ZAR + 0.00074*A2AZR*A4ZAR - 1.94*A2ZAR*A4ZAR + 0.0084*A2ZZR*A4ZAR + 0.00028*A4AZR*A4ZAR + 0.98*A1ZZR*A4ZZR + 0.00142*A2AAR*A4ZZR + 0.094*A2AZR*A4ZZR + 0.094*A2ZAR*A4ZZR - 0.138*A2ZZR*A4ZZR - 0.03*A4AZR*A4ZZR - 0.03*A4ZAR*A4ZZR + pow(A1ZZR,2) + 3*pow(A2AAR,2) + 5.4*pow(A2AZR,2) + 5.4*pow(A2ZAR,2) + 0.025*pow(A2ZZR,2) + 2.6*pow(A3AAR,2) + 3.1*pow(A3AZR,2) + 3.1*pow(A3ZAR,2) + 0.0096*pow(A3ZZR,2) + 0.31*pow(A4AZR,2) + 0.31*pow(A4ZAR,2) + 0.25*pow(A4ZZR,2));
}

double GetRHto4l_WithSquare_Higgs(const HiggsBasis &H)
{
   double DeltaCZ = H.DeltaCZ;
   double CZB = H.CZB;
   double CZZ = H.CZZ;
   double CZZD = H.CZZD;
   double CZA = H.CZA;
   double CZAD = H.CZAD;
   double CAA = H.CAA;
   double CAAD = H.CAAD;
   double AlphaEM = CONST_ALPHA;
   double SW = CONST_SW;
   double CW = CONST_CW;
   double PI = CONST_PI;

   return (pow(1 + DeltaCZ,-2)*(0.09047786842338604*AlphaEM*CAA*(1 + DeltaCZ) + 410.5755430853173*pow(AlphaEM,2)*pow(CAAD,2) + 4*pow(1 + DeltaCZ,2) + 48*pow(AlphaEM,2)*pow(CAA,2)*pow(PI,2) + 39.47841760435743*pow(AlphaEM,2)*pow(CZB,2)*pow(SW,-4) + 29.68777003847679*CZA*CZB*pow(AlphaEM,2)*pow(CW,-1)*pow(SW,-3) + 24.630086404143977*AlphaEM*CZB*(1 + DeltaCZ)*pow(SW,-2) + 0.2242374119927502*CAA*CZB*pow(AlphaEM,2)*pow(SW,-2) + 1705.4676405082412*pow(AlphaEM,2)*pow(CW,-2)*pow(CZA,2)*pow(SW,-2) + 979.1942457978066*pow(AlphaEM,2)*pow(CW,-2)*pow(CZAD,2)*pow(SW,-2) + (pow(AlphaEM,2)*pow(CW,-2)*pow(CZA,2)*pow(PI,2)*pow(SW,-2))/3125. + 9.248848772168351*AlphaEM*CZA*(1 + DeltaCZ)*pow(CW,-1)*pow(SW,-1) - 39.79424494519229*CAA*CZA*pow(AlphaEM,2)*pow(CW,-1)*pow(SW,-1) - 31.582734083485946*CAAD*CZAD*pow(AlphaEM,2)*pow(CW,-1)*pow(SW,-1) - 3.1164599123610746*AlphaEM*(1 + DeltaCZ)*pow(CW,-1)*(-CZA + 2*CZB + CZZ - (CAA - 2*CZA + 2*CZB)*pow(SW,2) + CAA*pow(SW,4))*pow(SW - 2*pow(SW,3),-1) + 12.001438951724658*CAA*pow(AlphaEM,2)*pow(CW,-1)*(-CZA + 2*CZB + CZZ - (CAA - 2*CZA + 2*CZB)*pow(SW,2) + CAA*pow(SW,4))*pow(SW - 2*pow(SW,3),-1) - 9.474820225045784*CZB*pow(AlphaEM,2)*pow(CW,-1)*pow(SW,-2)*(-CZA + 2*CZB + CZZ - (CAA - 2*CZA + 2*CZB)*pow(SW,2) + CAA*pow(SW,4))*pow(SW - 2*pow(SW,3),-1) - 612.4713289874095*CZA*pow(AlphaEM,2)*pow(CW,-2)*pow(SW,-1)*(-CZA + 2*CZB + CZZ - (CAA - 2*CZA + 2*CZB)*pow(SW,2) + CAA*pow(SW,4))*pow(SW - 2*pow(SW,3),-1) + 3.947841760435743*pow(AlphaEM,2)*pow(CZZ,2)*pow(pow(SW,2) - pow(SW,4),-2) + 1.5159712360073252*pow(AlphaEM,2)*pow(CZZD,2)*pow(pow(SW,2) - pow(SW,4),-2) - 7.037167544041138*AlphaEM*CZZ*(1 + DeltaCZ)*pow(pow(SW,2) - pow(SW,4),-1) + 0.12948920974229236*CAAD*CZZD*pow(AlphaEM,2)*pow(pow(SW,2) - pow(SW,4),-1) + (CAA*CZZ*pow(AlphaEM,2)*pow(PI,2)*pow(pow(SW,2) - pow(SW,4),-1))/3125. + (CAAD*CZZ*pow(AlphaEM,2)*pow(PI,2)*pow(pow(SW,2) - pow(SW,4),-1))/62500. - 21.792086517605306*CZB*CZZ*pow(AlphaEM,2)*pow(SW,-2)*pow(pow(SW,2) - pow(SW,4),-1) - 10.106474906715503*CZA*CZZ*pow(AlphaEM,2)*pow(CW,-1)*pow(SW,-1)*pow(pow(SW,2) - pow(SW,4),-1) - 4.737410112522892*CZAD*CZZD*pow(AlphaEM,2)*pow(CW,-1)*pow(SW,-1)*pow(pow(SW,2) - pow(SW,4),-1) + 2.6529496630128193*CZZ*pow(AlphaEM,2)*pow(CW,-1)*(-CZA + 2*CZB + CZZ - (CAA - 2*CZA + 2*CZB)*pow(SW,2) + CAA*pow(SW,4))*pow(SW - 2*pow(SW,3),-1)*pow(pow(SW,2) - pow(SW,4),-1) + 97.95069148652331*pow(AlphaEM,2)*pow(CW,-2)*pow(SW - 2*pow(SW,3),-2)*pow(-CZA + 2*CZB + CZZ - (CAA - 2*CZA + 2*CZB)*pow(SW,2) + CAA*pow(SW,4),2)))/4.;
}

double GetRHto4l_WithSquare_Warsaw(const WarsawBasis &W)
{
   double CT = W.CT;
   double CH = W.CH;
   double CWW = W.CWW;
   double CWWD = W.CWWD;
   double CWB = W.CWB;
   double CWBD = W.CWBD;
   double CBB = W.CBB;
   double CBBD = W.CBBD;
   double DeltaM = 0;
   double CW = CONST_CW;
   double SW = CONST_SW;
   double AlphaEM = CONST_ALPHA;
   double PI = CONST_PI;

   return (pow(SW,4)*pow(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2),-2)*(410.5755430853173*pow(AlphaEM,2)*pow(CBBD - 4*CWBD + CWWD,2) + 48*pow(AlphaEM,2)*pow(CBB - 4*CWB + CWW,2)*pow(PI,2) - 39.79424494519229*(CBB - 4*CWB + CWW)*pow(AlphaEM,2)*pow(CW,-1)*pow(SW,-1)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) - 31.582734083485946*(CBBD - 4*CWBD + CWWD)*pow(AlphaEM,2)*pow(CW,-1)*pow(SW,-1)*(-2*CWBD + CWWD - (CBBD - 4*CWBD + CWWD)*pow(SW,2)) + 0.03568849254478005*AlphaEM*(CBB - 4*CWB + CWW)*pow(SW,-2)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) + 4.724955350999049*AlphaEM*pow(CW,-1)*pow(SW,-3)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) + 0.09047786842338604*AlphaEM*(CBB - 4*CWB + CWW)*pow(SW,-2)*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2)) + 9.248848772168351*AlphaEM*pow(CW,-1)*pow(SW,-3)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2)) + 3.92*pow(SW,-4)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2))*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2)) + ((CBB - 4*CWB + CWW)*pow(AlphaEM,2)*pow(CW,-2)*pow(PI,2)*pow(SW,-2)*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)))/3125. + ((CBBD - 4*CWBD + CWWD)*pow(AlphaEM,2)*pow(CW,-2)*pow(PI,2)*pow(SW,-2)*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)))/62500. - 10.106474906715503*pow(AlphaEM,2)*pow(CW,-3)*pow(SW,-3)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 3.4683182895631317*AlphaEM*pow(CW,-2)*pow(SW,-4)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 7.037167544041138*AlphaEM*pow(CW,-2)*pow(SW,-4)*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 0.12948920974229236*(CBBD - 4*CWBD + CWWD)*pow(AlphaEM,2)*pow(CW,-2)*pow(SW,-2)*(CWWD - 2*(-2*CWBD + CWWD)*pow(SW,2) + (CBBD - 4*CWBD + CWWD)*pow(SW,4)) - 4.737410112522892*pow(AlphaEM,2)*pow(CW,-3)*pow(SW,-3)*(-2*CWBD + CWWD - (CBBD - 4*CWBD + CWWD)*pow(SW,2))*(CWWD - 2*(-2*CWBD + CWWD)*pow(SW,2) + (CBBD - 4*CWBD + CWWD)*pow(SW,4)) - 3.8201766667651884*AlphaEM*(CBB - 4*CWB + CWW)*pow(CW,-1)*pow(SW,-1)*(DeltaM - CT*pow(CW,2) + (-3 + 2*pow(SW,2))*(-2*AlphaEM*CWB*PI + DeltaM*pow(SW,2)))*pow(-1 + 2*pow(SW,2),-1) + 194.95567902081734*AlphaEM*pow(CW,-2)*pow(SW,-2)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(DeltaM - CT*pow(CW,2) + (-3 + 2*pow(SW,2))*(-2*AlphaEM*CWB*PI + DeltaM*pow(SW,2)))*pow(-1 + 2*pow(SW,2),-1) + 0.48*pow(CW,-1)*pow(SW,-3)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2))*(DeltaM - CT*pow(CW,2) + (-3 + 2*pow(SW,2))*(-2*AlphaEM*CWB*PI + DeltaM*pow(SW,2)))*pow(-1 + 2*pow(SW,2),-1) + 0.992*pow(CW,-1)*pow(SW,-3)*(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2))*(DeltaM - CT*pow(CW,2) + (-3 + 2*pow(SW,2))*(-2*AlphaEM*CWB*PI + DeltaM*pow(SW,2)))*pow(-1 + 2*pow(SW,2),-1) - 0.8444601052849363*AlphaEM*pow(CW,-3)*pow(SW,-3)*(DeltaM - CT*pow(CW,2) + (-3 + 2*pow(SW,2))*(-2*AlphaEM*CWB*PI + DeltaM*pow(SW,2)))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4))*pow(-1 + 2*pow(SW,2),-1) + 1705.4676405082412*pow(AlphaEM,2)*pow(CW,-2)*pow(SW,-2)*pow(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2),2) + (pow(AlphaEM,2)*pow(CW,-2)*pow(PI,2)*pow(SW,-2)*pow(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2),2))/3125. + 979.1942457978066*pow(AlphaEM,2)*pow(CW,-2)*pow(SW,-2)*pow(-2*CWBD + CWWD - (CBBD - 4*CWBD + CWWD)*pow(SW,2),2) + 1.*pow(SW,-4)*pow(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2),2) + 4*pow(SW,-4)*pow(3*(DeltaM + 4*AlphaEM*CWB*PI) - 3*CT*pow(CW,2) - (-1 + CH + 6*DeltaM)*pow(SW,2),2) + 9.924479999999999*pow(CW,-2)*pow(SW,-2)*pow(-1 + 2*pow(SW,2),-2)*pow(DeltaM - CT*pow(CW,2) + (-3 + 2*pow(SW,2))*(-2*AlphaEM*CWB*PI + DeltaM*pow(SW,2)),2) + 3.947841760435743*pow(AlphaEM,2)*pow(CW,-4)*pow(SW,-4)*pow(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4),2) + 1.5159712360073252*pow(AlphaEM,2)*pow(CW,-4)*pow(SW,-4)*pow(CWWD - 2*(-2*CWBD + CWWD)*pow(SW,2) + (CBBD - 4*CWBD + CWWD)*pow(SW,4),2)))/4.;
}

double GetRZZWW_NoSquare_AVV(const AVVBasis &A)
{
   double A2ZZR = A.A2ZZ;
   double A4ZZR = A.A4ZZ;
   double A2ZAR = A.A2ZA;
   double A2AZR = A.A2ZA;
   double A2AAR = A.A2AA;
   double CW = CONST_CW;
   double SW = CONST_SW;
   double AlphaEM = CONST_ALPHA;

   return 1 + 0.0039788735772973835*A2AAR*pow(AlphaEM,-1) + 0.021485917317405873*A2AZR*CW*SW*pow(AlphaEM,-1) - 0.026260565610162732*A4ZZR*pow(AlphaEM,-1)*pow(SW,2) - 0.01909859317102744*A2ZZR*pow(AlphaEM,-1)*pow(CW,2)*pow(SW,2);
}

double GetRZZWW_NoSquare_Higgs(const HiggsBasis &H)
{
   double CZB = H.CZB;
   double CZZ = H.CZZ;
   double CZA = H.CZA;
   double CAA = H.CAA;

   return 1 + 0.05 * CAA + 0.27 * CZA - 0.33 * CZB - 0.24 * CZZ;
}

double GetRZZWW_NoSquare_Warsaw(const WarsawBasis &W)
{
   double CT = W.CT;
   double CH = W.CH;
   double CWW = W.CWW;
   double CWB = W.CWB;
   double CBB = W.CBB;
   double DeltaM = 0;
   double SW = CONST_SW;
   double CW = CONST_CW;
   double AlphaEM = CONST_ALPHA;
   double PI = CONST_PI;

   return 1 + 0.05*(CBB - 4*CWB + CWW) + 0.27*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) - 0.052521131220325465*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 0.24*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4));
}

double GetChi2_AllHiggs_WithSquare_AVV(const AVVBasis &A)
{
   double A1ZZR = A.A1ZZ;
   double A2ZZR = A.A2ZZ;
   double A4ZZR = A.A4ZZ;
   double A2ZAR = A.A2ZA;
   double A2AZR = A.A2ZA;
   double A2AAR = A.A2AA;
   double CW = CONST_CW;
   double SW = CONST_SW;
   double AlphaEM = CONST_ALPHA;

   double Chi2 = 2.14602 + 4.441195*(-2 + A1ZZR) + 31.9515*pow(-2 + A1ZZR,2) - 0.7440267817815969*A2AAR*A2AZR*CW*SW*pow(AlphaEM,-2) + 53.290193165386434*pow(A2AAR,2)*pow(AlphaEM,-2) + 17.365952883057524*A2AAR*pow(AlphaEM,-1) - 25.23234510031754*(-2 + A1ZZR)*A2AAR*pow(AlphaEM,-1) - 0.28243954510973934*A2AZR*CW*SW*pow(AlphaEM,-1) - 1.921724318110245*(-2 + A1ZZR)*A2AZR*CW*SW*pow(AlphaEM,-1) + 0.9557563927241945*A2AAR*A4ZZR*pow(AlphaEM,-2)*pow(SW,2) + 3.8897865979016952*A4ZZR*pow(AlphaEM,-1)*pow(SW,2) + 27.56909776352852*(-2 + A1ZZR)*A4ZZR*pow(AlphaEM,-1)*pow(SW,2) - 0.7311083308671988*A2AAR*A2ZZR*pow(AlphaEM,-2)*pow(CW,2)*pow(SW,2) + 0.7282460074293028*pow(A2AZR,2)*pow(AlphaEM,-2)*pow(CW,2)*pow(SW,2) + 1.5494847794597655*A2ZZR*pow(AlphaEM,-1)*pow(CW,2)*pow(SW,2) + 12.754517984441401*(-2 + A1ZZR)*A2ZZR*pow(AlphaEM,-1)*pow(CW,2)*pow(SW,2) - 1.2797372099945472*A2AZR*A4ZZR*CW*pow(AlphaEM,-2)*pow(SW,3) - 0.5832990883975632*A2AZR*A2ZZR*pow(AlphaEM,-2)*pow(CW,3)*pow(SW,3) + 8.139763939386759*pow(A4ZZR,2)*pow(AlphaEM,-2)*pow(SW,4) + 7.33324731759375*A2ZZR*A4ZZR*pow(AlphaEM,-2)*pow(CW,2)*pow(SW,4) + 1.660084268239928*pow(A2ZZR,2)*pow(AlphaEM,-2)*pow(CW,4)*pow(SW,4);

   return Chi2;
}

double GetChi2_AllHiggs_WithSquare_Higgs(const HiggsBasis &H)
{
   double DeltaCZ = H.DeltaCZ;
   double CZB = H.CZB;
   double CZZ = H.CZZ;
   double CZA = H.CZA;
   double CAA = H.CAA;

   double Chi2 = 2.14602 + 218.227*CAA - 3.54924*CZA - 117.492*CAA*CZA + 48.8805*CZB + 150.927*CAA*CZB - 202.088*CZA*CZB + 19.4714*CZZ - 115.452*CAA*CZZ - 92.1109*CZA*CZZ + 1158.02*CZB*CZZ + 8.88239*DeltaCZ - 634.158*CAA*DeltaCZ - 48.2982*CZA*DeltaCZ + 692.887*CZB*DeltaCZ + 320.556*CZZ*DeltaCZ + 8415.25*pow(CAA,2) + 115.*pow(CZA,2) + 1285.38*pow(CZB,2) + 262.15*pow(CZZ,2) + 127.806*pow(DeltaCZ,2);

   return Chi2;
}

double GetChi2_AllHiggs_WithSquare_Warsaw(const WarsawBasis &W)
{
   double CT = W.CT;
   double CH = W.CH;
   double CWW = W.CWW;
   double CWB = W.CWB;
   double CBB = W.CBB;
   double DeltaM = 0;
   double SW = CONST_SW;
   double CW = CONST_CW;
   double AlphaEM = CONST_ALPHA;
   double PI = CONST_PI;

   double Chi2 = 2.14602 + 218.227*(CBB - 4*CWB + CWW) + 8415.25*pow(CBB - 4*CWB + CWW,2) - 3.54924*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) - 117.492*(CBB - 4*CWB + CWW)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) + 7.7795731958033905*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) + 24.020778096030487*(CBB - 4*CWB + CWW)*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 32.163304139554945*pow(AlphaEM,-1)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) + 8.88239*(-CH + 3*pow(SW,-2)*(DeltaM + 4*AlphaEM*CWB*PI - CT*pow(CW,2) - 2*DeltaM*pow(SW,2))) - 634.158*(CBB - 4*CWB + CWW)*(-CH + 3*pow(SW,-2)*(DeltaM + 4*AlphaEM*CWB*PI - CT*pow(CW,2) - 2*DeltaM*pow(SW,2))) - 48.2982*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(-CH + 3*pow(SW,-2)*(DeltaM + 4*AlphaEM*CWB*PI - CT*pow(CW,2) - 2*DeltaM*pow(SW,2))) + 110.27639105411409*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2))*(-CH + 3*pow(SW,-2)*(DeltaM + 4*AlphaEM*CWB*PI - CT*pow(CW,2) - 2*DeltaM*pow(SW,2))) + 19.4714*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 115.452*(CBB - 4*CWB + CWW)*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 92.1109*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 184.30460719927663*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 320.556*(-CH + 3*pow(SW,-2)*(DeltaM + 4*AlphaEM*CWB*PI - CT*pow(CW,2) - 2*DeltaM*pow(SW,2)))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 115.*pow(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2),2) + 32.559055757547036*pow(AlphaEM,-2)*pow(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2),2) + 127.806*pow(-CH + 3*pow(SW,-2)*(DeltaM + 4*AlphaEM*CWB*PI - CT*pow(CW,2) - 2*DeltaM*pow(SW,2)),2) + 262.15*pow(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4),2);

   return Chi2;
}

double GetChi2_AllHiggs_Higgs_14252(const HiggsBasis &H)
{
   double DeltaCZ = H.DeltaCZ;
   double CZB = H.CZB;
   double CZZ = H.CZZ;
   double CZA = H.CZA;
   double CAA = H.CAA;

   double Chi2 = 0.33199134268557384 - 86.77013402376377 * CAA + 0.27882228440221635 * CZA + 101.42390636218539 * CAA * CZA + 9.520834740681632 * CZB - 3612.5527577790854 * CAA * CZB - 106.30878664574996 * CZA * CZB + 5.038333356250416 * CZZ - 1861.3764213625473 * CAA * CZZ - 51.15475534288645 * CZA * CZZ + 598.8098529520332 * CZB * CZZ + 9715.487372153202 * CAA * CAA + 111.60207061059137 * CZA * CZA + 619.8405888684907 * CZB * CZB + 145.6818354210663 * CZZ * CZZ;

   return Chi2;
}

double GetChi2_AllHiggs_Warsaw_14252(const WarsawBasis &W)
{
   double CT = W.CT;
   double CH = W.CH;
   double CWW = W.CWW;
   double CWB = W.CWB;
   double CBB = W.CBB;
   double DeltaM = 0;
   double SW = CONST_SW;
   double CW = CONST_CW;
   double AlphaEM = CONST_ALPHA;
   double PI = CONST_PI;

   double Chi2 = 0.33199134268557384 - 86.77013402376377*(CBB - 4*CWB + CWW) + 9715.487372153202*pow(CBB - 4*CWB + CWW,2) + 0.27882228440221635*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) + 101.42390636218539*(CBB - 4*CWB + CWW)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) + 1.5152879113405253*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 574.9556285808*(CBB - 4*CWB + CWW)*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 16.91956888877278*pow(AlphaEM,-1)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) + 5.038333356250416*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 1861.3764213625473*(CBB - 4*CWB + CWW)*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 51.15475534288645*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 95.30354806944707*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 111.60207061059137*pow(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2),2) + 15.700745533429783*pow(AlphaEM,-2)*pow(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2),2) + 145.6818354210663*pow(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4),2);

   return Chi2;
}

double GetChi2_LEP2WW_Higgs_14252(const HiggsBasis &H)
{
   double DeltaCZ = H.DeltaCZ;
   double CZB = H.CZB;
   double CZZ = H.CZZ;
   double CZA = H.CZA;
   double CAA = H.CAA;

   double Chi2 = 7.146227259555785 + 2.149906918620676*CAA + 6.274575123519259*CZA + 1.7462014288110317*CAA*CZA - 9.44548140226887*CZB - 1.6732549551991465*CAA*CZB - 4.883450453721856*CZA*CZB - 11.906303961840143*CZZ - 3.3135000507193926*CAA*CZZ - 9.670560529831004*CZA*CZZ + 9.266578906140673*CZB*CZZ + 0.2991573500358796*pow(CAA,2) + 2.5481735862548414*pow(CZA,2) + 3.2370272782520018*pow(CZB,2) + 9.175173687693626*pow(CZZ,2);

   return Chi2;
}

double GetChi2_LEP2WW_Warsaw_14252(const WarsawBasis &W)
{
   double CT = W.CT;
   double CH = W.CH;
   double CWW = W.CWW;
   double CWB = W.CWB;
   double CBB = W.CBB;
   double DeltaM = 0;
   double SW = CONST_SW;
   double CW = CONST_CW;
   double AlphaEM = CONST_ALPHA;
   double PI = CONST_PI;

   double Chi2 = 7.146227259555785 + 2.149906918620676*(CBB - 4*CWB + CWW) + 0.2991573500358796*pow(CBB - 4*CWB + CWW,2) + 6.274575123519259*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) + 1.7462014288110317*(CBB - 4*CWB + CWW)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) - 1.503295055053658*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 0.266306797172952*(CBB - 4*CWB + CWW)*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 0.7772252790541926*pow(AlphaEM,-1)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 11.906303961840143*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 3.3135000507193926*(CBB - 4*CWB + CWW)*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 9.670560529831004*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 1.4748218384633767*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 2.5481735862548414*pow(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2),2) + 0.08199485882875697*pow(AlphaEM,-2)*pow(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2),2) + 9.175173687693626*pow(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4),2);

   return Chi2;
}

double GetChi2_HiggsPlusLEP2WW_Higgs_14252(const HiggsBasis &H)
{
   double DeltaCZ = H.DeltaCZ;
   double CZB = H.CZB;
   double CZZ = H.CZZ;
   double CZA = H.CZA;
   double CAA = H.CAA;

   double Chi2 = 3.053301962922411 - 89.2895174486161*CAA + 6.542715541026529*CZA + 99.15200009363252*CAA*CZA + 0.08852387274139772*CZB - 3531.8512989892943*CAA*CZB - 110.00980068459677*CZA*CZB - 6.87825531589022*CZZ - 1824.8775510936466*CAA*CZZ - 60.216265438982795*CZA*CZZ + 596.3015833972656*CZB*CZZ + 9746.343949366783*pow(CAA,2) + 114.11710642482562*pow(CZA,2) + 611.4484390723362*pow(CZB,2) + 151.91039302722132*pow(CZZ,2);

   return Chi2;
}

double GetChi2_HiggsPlusLEP2WW_Warsaw_14252(const WarsawBasis &W)
{
   double CT = W.CT;
   double CH = W.CH;
   double CWW = W.CWW;
   double CWB = W.CWB;
   double CBB = W.CBB;
   double DeltaM = 0;
   double SW = CONST_SW;
   double CW = CONST_CW;
   double AlphaEM = CONST_ALPHA;
   double PI = CONST_PI;

   double Chi2 = 3.053301962922411 - 89.2895174486161*(CBB - 4*CWB + CWW) + 9746.343949366783*pow(CBB - 4*CWB + CWW,2) + 6.542715541026529*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) + 99.15200009363252*(CBB - 4*CWB + CWW)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2)) + 0.01408901192843134*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 562.1115924996777*(CBB - 4*CWB + CWW)*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 17.50860356750775*pow(AlphaEM,-1)*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2)) - 6.87825531589022*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 1824.8775510936466*(CBB - 4*CWB + CWW)*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) - 60.216265438982795*(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 94.90434457119889*pow(AlphaEM,-1)*(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2))*(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4)) + 114.11710642482562*pow(-2*CWB + CWW - (CBB - 4*CWB + CWW)*pow(SW,2),2) + 15.48816989576724*pow(AlphaEM,-2)*pow(-CT + DeltaM + 4*AlphaEM*CWB*PI - 2*DeltaM*pow(SW,2),2) + 151.91039302722132*pow(CWW - 2*(-2*CWB + CWW)*pow(SW,2) + (CBB - 4*CWB + CWW)*pow(SW,4),2);

   return Chi2;
}

double GetChi2_TopYukawaMagnitude_15243(const LoopBasis &L)
{
   // TODO!  Here comes constraints from Htt search
   return 1;
}


