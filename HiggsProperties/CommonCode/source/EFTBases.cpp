#include <cmath>
using namespace std;

#include "EFTBases.h"
#include "Constants.h"

AVVBasis::AVVBasis()
{
   A1ZZ = 0;   A2ZZ = 0;   A3ZZ = 0;   A4ZZ = 0;
   A1ZA = 0;   A2ZA = 0;   A3ZA = 0;   A4ZA = 0;
   A1AA = 0;   A2AA = 0;   A3AA = 0;   A4AA = 0;
}

AVVBasis::AVVBasis(double A[12])
{
   A1ZZ = A[0];   A2ZZ = A[1];   A3ZZ = A[2];   A4ZZ = A[3];
   A1ZA = A[4];   A2ZA = A[5];   A3ZA = A[6];   A4ZA = A[7];
   A1AA = A[8];   A2AA = A[9];   A3AA = A[10];  A4AA = A[11];
}

AVVBasis::AVVBasis(const HiggsBasis &H)
{
   double DeltaCZ = H.DeltaCZ;
   double CZB = H.CZB;
   double DeltaM = 0;
   double CZZ = H.CZZ;
   double CZZD = H.CZZD;
   double CZA = H.CZA;
   double CZAD = H.CZAD;
   double CAA = H.CAA;
   double CAAD = H.CAAD;

   double AlphaEM = CONST_ALPHA;
   double SW2 = CONST_SW2;
   double SW4 = SW2 * SW2;
   double CW2 = 1 - SW2;
   double CW4 = CW2 * CW2;
   double SW = sqrt(SW2);
   double CW = sqrt(CW2);
   double SW3 = SW * SW2;
   double PI = CONST_PI;

   // Older version with delta cw
   // A1ZZ = 2 * (1 + DeltaCZ);
   // A2ZZ = 4 * AlphaEM * CZZ * PI * pow(SW2 - SW4, -1);
   // A3ZZ = 4 * AlphaEM * CZZD * PI * pow(SW2 - SW4, -1);
   // A4ZZ = (1 / SW2 * (DeltaCW - DeltaCZ - 4 * DeltaM - 8 * AlphaEM * CZZ * PI + 8 * AlphaEM * CZA * PI * (1 - 2 * SW2) + 2 * (-DeltaCW + DeltaCZ + 4 * DeltaM + 4 * AlphaEM * CAA * PI * CW2) * SW2)) / 2;
   // A1ZA = 0;
   // A2ZA = 4 * AlphaEM * CZA * PI * pow(SW2 - SW4, -0.5);
   // A3ZA = 4 * AlphaEM * CZAD * PI * pow(SW2 - SW4, -0.5);
   // A4ZA = 1 / CW / SW * (-4 * AlphaEM * CZZ * PI + 4 * AlphaEM * CZA * PI * (1 - 2 * SW2) + CW2 * (DeltaCW - DeltaCZ - 4 * DeltaM + 4 * AlphaEM * CAA * PI * SW2));
   // A1AA = 0;
   // A2AA = 4 * AlphaEM * CAA * PI;
   // A3AA = 4 * AlphaEM * CAAD * PI;
   // A4AA = 0;

   // 1,4111
   A1ZZ = 2 * (1 + DeltaCZ);
   A2ZZ = 4 * AlphaEM * CZZ * PI / (SW2 - SW4);
   A3ZZ = 4 * AlphaEM * CZZD * PI / (SW2 - SW4);
   A4ZZ = 4 * AlphaEM * CZB * PI / SW2;
   A1ZA = 0;
   A2ZA = 4 * AlphaEM * CZA * PI / CW / SW;
   A3ZA = 4 * AlphaEM * CZAD * PI / CW / SW;
   A4ZA = 4 * AlphaEM * PI / CW * (-CZA + 2 * CZB + CZZ - (CAA - 2 * CZA + 2 * CZB) * SW2 + CAA * SW4) / (SW - 2 * SW3);
   A1AA = 0;
   A2AA = 4 * AlphaEM * CAA * PI;
   A3AA = 4 * AlphaEM * CAAD * PI;
   A4AA = 0;
}

AVVBasis::AVVBasis(const WarsawBasis &W)
{
   double CT = W.CT;
   double CH = W.CH;
   double DeltaM = 0;
   double CWW = W.CWW;
   double CWWD = W.CWWD;
   double CWB = W.CWB;
   double CWBD = W.CWBD;
   double CBB = W.CBB;
   double CBBD = W.CBBD;

   double AlphaEM = CONST_ALPHA;
   double SW2 = CONST_SW2;
   double SW4 = SW2 * SW2;
   double CW2 = 1 - SW2;
   double CW4 = CW2 * CW2;
   double SW = sqrt(SW2);
   double CW = sqrt(CW2);
   double PI = CONST_PI;
   
   // Older version with delta cw
   // A1ZZ = -2 / SW2 * (-DeltaM - 4 * AlphaEM * CWB * PI + (-1 + CH + 2 * DeltaM) * SW2 + CT * (1 + SW2));
   // A2ZZ = 4 * AlphaEM * PI / CW2 / SW2 * (CWW - 2 * (-2 * CWB + CWW) * SW2 + (CBB - 4 * CWB + CWW) * SW4);
   // A3ZZ = 4 * AlphaEM * PI / CW2 / SW2 * (CWWD - 2 * (-2 * CWBD + CWWD) * SW2 + (CBBD - 4 * CWBD + CWWD) * SW4);
   // A4ZZ = 1 / SW2 * (CT - DeltaM - 8 * AlphaEM * CWB * PI - 2 * CT * SW2 + 2 * DeltaM * SW2);
   // A1ZA = 0;
   // A2ZA = 4 * AlphaEM * PI / CW / SW * (-2 * CWB + CWW - (CBB - 4 * CWB + CWW) * SW2);
   // A3ZA = 4 * AlphaEM * PI / CW / SW * (-2 * CWBD + CWWD - (CBBD - 4 * CWBD + CWWD) * SW2);
   // A4ZA = 2 / CW / SW * (-4 * AlphaEM * CWB * PI + CT * CW2 + DeltaM * (-1 + SW2));
   // A1AA = 0;
   // A2AA = 4 * AlphaEM * (CBB - 4 * CWB + CWW) * PI;
   // A3AA = 4 * AlphaEM * (CBBD - 4 * CWBD + CWWD) * PI;
   // A4AA = 0;
   
   // 1,4112
   A1ZZ = 2 / SW2 * (3 * (DeltaM + 4 * AlphaEM * CWB * PI) - 3 * CT * CW2 - (-1 + CH + 6 * DeltaM) * SW2);
   A2ZZ = 4 * AlphaEM * PI / CW2 / SW2 * (CWW - 2 * (-2 * CWB + CWW) * SW2 + (CBB - 4 * CWB + CWW) * SW4);
   A3ZZ = 4 * AlphaEM * PI / CW2 / SW2 * (CWWD - 2 * (-2 * CWBD + CWWD) * SW2 + (CBBD - 4 * CWBD + CWWD) * SW4);
   A4ZZ = 2 / SW2 * (-CT + DeltaM + 4 * AlphaEM * CWB * PI - 2 * DeltaM * SW2);
   A1ZA = 0;
   A2ZA = 4 * AlphaEM * PI / CW / SW * (-2 * CWB + CWW - (CBB - 4 * CWB + CWW) * SW2);
   A3ZA = 4 * AlphaEM * PI / CW / SW * (-2 * CWBD + CWWD - (CBBD - 4 * CWBD + CWWD) * SW2);
   A4ZA = -4 / CW / SW * (DeltaM - CT * CW2 + (-3 + 2 * SW2) * (-2 * AlphaEM * CWB * PI + DeltaM * SW2)) / (-1 + 2 * SW2);
   A1AA = 0;
   A2AA = 4 * AlphaEM * (CBB - 4 * CWB + CWW) * PI;
   A3AA = 4 * AlphaEM * (CBBD - 4 * CWBD + CWWD) * PI;
   A4AA = 0;
}

void AVVBasis::Print(ostream &out)
{
   out << "(" << A1ZZ << ", " << A2ZZ << ", " << A3ZZ << ", " << A4ZZ << "; "
      << A1ZA << ", " << A2ZA << ", " << A3ZA << ", " << A4ZA << "; "
      << A1AA << ", " << A2AA << ", " << A3AA << ", " << A4AA << ")";
}

HiggsBasis::HiggsBasis()
{
   DeltaCZ = 0;   CZB = 0;
   CZZ = 0;       CZZD = 0;
   CZA = 0;       CZAD = 0;
   CAA = 0;       CAAD = 0;
}

HiggsBasis::HiggsBasis(double H[8])
{
   DeltaCZ = H[0];   CZB = H[1];
   CZZ = H[2];       CZZD = H[3];
   CZA = H[4];       CZAD = H[5];
   CAA = H[6];       CAAD = H[7];
}

HiggsBasis::HiggsBasis(const AVVBasis &A)
{
   double A1ZZR = A.A1ZZ;
   double A2ZZR = A.A2ZZ;
   double A3ZZR = A.A3ZZ;
   double A4ZZR = A.A4ZZ;
   double A1ZAR = A.A1ZA;
   double A2ZAR = A.A2ZA;
   double A3ZAR = A.A3ZA;
   double A4ZAR = A.A4ZA;
   double A1AAR = A.A1AA;
   double A2AAR = A.A2AA;
   double A3AAR = A.A3AA;
   double A4AAR = A.A4AA;
   double DeltaM = 0;

   double AlphaEM = CONST_ALPHA;
   double SW2 = CONST_SW2;
   double SW4 = SW2 * SW2;
   double CW2 = 1 - SW2;
   double CW4 = CW2 * CW2;
   double SW = sqrt(SW2);
   double CW = sqrt(CW2);
   double PI = CONST_PI;

   // Older version with DeltaCW
   // CZZ = (A2ZZR / AlphaEM * CW2 / PI * SW2) / 4;
   // CZZD = (A3ZZR / AlphaEM * CW2 / PI * SW2) / 4;
   // CZA = (A2ZAR * CW * SW / AlphaEM / PI) / 4;
   // CZAD = (A3ZAR * CW * SW / AlphaEM / PI) / 4;
   // CAA = (A2AAR / AlphaEM / PI) / 4;
   // CAAD = (A3AAR / AlphaEM / PI) / 4;
   // DeltaCW = (-2 + A1ZZR + A2AAR - A2ZZR - 2 * A4ZZR + 8 * DeltaM - 4 * A2ZAR * CW * SW + 2 * (-A2AAR + A2ZZR) * SW2 + (A2AAR - A2ZZR - 2 * A4ZZR) / (-1 + 2 * SW2)) / 2;
   // DeltaCZ = (-2 + A1ZZR) / 2;
   
   // 1,4111
   CZZ = (A2ZZR / AlphaEM * CW2 / PI * SW2) / 4;
   CZZD = (A3ZZR / AlphaEM * CW2 / PI * SW2) / 4;
   CZA = (A2ZAR * CW * SW / AlphaEM / PI) / 4;
   CZAD = (A3ZAR * CW * SW / AlphaEM / PI) / 4;
   CAA = (A2AAR / AlphaEM / PI) / 4;
   CAAD = (A3AAR / AlphaEM / PI) / 4;
   CZB = (A4ZZR / AlphaEM / PI * SW2) / 4;
   DeltaCZ = (-2 + A1ZZR) / 2;
}

HiggsBasis::HiggsBasis(const WarsawBasis &W)
{
   AVVBasis A(W);
   HiggsBasis H(A);

   DeltaCZ = H.DeltaCZ;
   CZB = H.CZB;
   CZZ = H.CZZ;
   CZZD = H.CZZD;
   CZA = H.CZA;
   CZAD = H.CZAD;
   CAA = H.CAA;
   CAAD = H.CAAD;
}

void HiggsBasis::Print(ostream &out)
{
   out << "(" << DeltaCZ << ", " << CZB << ", " << CZZ << ", " << CZZD << ", " << CZA << ", " << CZAD << ", " << CAA << ", " << CAAD << ")";
}

WarsawBasis::WarsawBasis()
{
   CT = 0;    CH = 0;
   CWW = 0;   CWWD = 0;
   CWB = 0;   CWBD = 0;
   CBB = 0;   CBBD = 0;
}

WarsawBasis::WarsawBasis(double W[8])
{
   CT = W[0];    CH = W[1];
   CWW = W[2];   CWWD = W[3];
   CWB = W[4];   CWBD = W[5];
   CBB = W[6];   CBBD = W[7];
}

WarsawBasis::WarsawBasis(const AVVBasis &A)
{
   double A1ZZR = A.A1ZZ;
   double A2ZZR = A.A2ZZ;
   double A3ZZR = A.A3ZZ;
   double A4ZZR = A.A4ZZ;
   double A1ZAR = A.A1ZA;
   double A2ZAR = A.A2ZA;
   double A3ZAR = A.A3ZA;
   double A4ZAR = A.A4ZA;
   double A1AAR = A.A1AA;
   double A2AAR = A.A2AA;
   double A3AAR = A.A3AA;
   double A4AAR = A.A4AA;
   double DeltaM = 0;

   double AlphaEM = CONST_ALPHA;
   double SW2 = CONST_SW2;
   double SW4 = SW2 * SW2;
   double SW6 = SW2 * SW2 * SW2;
   double CW2 = 1 - SW2;
   double CW4 = CW2 * CW2;
   double SW = sqrt(SW2);
   double CW = sqrt(CW2);
   double PI = CONST_PI;

   // Older version with delta cw
   // CWW = (1 / AlphaEM / PI * SW2 * (A2ZZR + SW * (2 * A2ZAR * CW + A2AAR * SW) - A2ZZR * SW2)) / 4;
   // CBB = (1 / AlphaEM * CW2 * (SW * (-2 * A2ZAR * CW + A2ZZR * SW) + A2AAR * CW2) / PI) / 4;
   // CWB = -(CW * SW / AlphaEM / PI * (A2ZAR + (A2AAR - A2ZZR) * CW * SW - 2 * A2ZAR * SW2)) / 8;
   // CWWD = (1 / AlphaEM / PI * SW2 * (A3ZZR + SW * (2 * A3ZAR * CW + A3AAR * SW) - A3ZZR * SW2)) / 4;
   // CBBD = (1 / AlphaEM * CW2 * (SW * (-2 * A3ZAR * CW + A3ZZR * SW) + A3AAR * CW2) / PI) / 4;
   // CWBD = -(CW * SW / AlphaEM / PI * (A3ZAR + (A3AAR - A3ZZR) * CW * SW - 2 * A3ZAR * SW2)) / 8;
   // CT = DeltaM - A2ZAR * CW * SW + (SW / CW * (-((A2ZAR + A4ZAR) * CW2) + (A2AAR - A2ZZR) * CW * SW * (-1 + 2 * CW2) + (A2ZAR + A4ZAR) * SW2) / (-1 + 2 * SW2)) / 2;
   // CH = (1 / CW / SW * (A4ZAR * (CW - SW) * (CW + SW) * (1 + SW2) + SW * (-(A2ZAR * SW * (1 + SW2)) + A2ZAR * SW * CW2 * (-1 + 8 * SW2) - CW * (-1 + 2 * SW2) * (-2 + A1ZZR + 6 * DeltaM + 2 * (-A2AAR + A2ZZR) * SW2))) / (-1 + 2 * SW2)) / 2;
   
   // 1,4112
   CWW = (1 / AlphaEM / PI * SW2 * (A2ZZR + SW * (2 * A2ZAR * CW + A2AAR * SW) - A2ZZR * SW2))/4;
   CWWD = (1 / AlphaEM / PI * SW2 * (A3ZZR + SW * (2 * A3ZAR * CW + A3AAR * SW) - A3ZZR * SW2))/4;
   CBB = (1 / AlphaEM * CW2 * (SW * (-2 * A2ZAR * CW + A2ZZR * SW) + A2AAR * CW2) / PI) / 4;
   CBBD = (1 / AlphaEM * CW2 * (SW * (-2 * A3ZAR * CW + A3ZZR * SW) + A3AAR * CW2) / PI) / 4;
   CWB = -(CW * SW / AlphaEM / PI * (A2ZAR + (A2AAR - A2ZZR) * CW * SW - 2 * A2ZAR * SW2)) / 8;
   CWBD = -(CW * SW / AlphaEM / PI * (A3ZAR + (A3AAR - A3ZZR) * CW * SW - 2 * A3ZAR * SW2)) / 8;
   CT = (2 * DeltaM - (A4ZZR + 4 * DeltaM + (A2AAR - A2ZZR) * CW2) * SW2 + A2ZAR * CW * SW * (-1 + 2 * SW2)) / 2;
   CH = (2 - A1ZZR + 6 * DeltaM + 3 * A4ZZR * CW2 - 3 * SW * (4 * DeltaM * SW + CW * (A2ZAR + (A2AAR - A2ZZR) * CW * SW - 2 * A2ZAR * SW2))) / 2;
}

WarsawBasis::WarsawBasis(const HiggsBasis &H)
{
   AVVBasis A(H);
   WarsawBasis W(A);

   CT = W.CT;
   CH = W.CH;
   CWW = W.CWW;
   CWWD = W.CWWD;
   CWB = W.CWB;
   CWBD = W.CWBD;
   CBB = W.CBB;
   CBBD = W.CBBD;
}

void WarsawBasis::Print(ostream &out)
{
   out << "(" << CT << ", " << CH << ", " << CWW << ", " << CWWD << ", " << CWB << ", " << CWBD << ", " << CBB << ", " << CBBD << ")";
}

std::ostream &operator <<(std::ostream &out, AVVBasis &A)
{
   A.Print(out);
   return out;
}

std::ostream &operator <<(std::ostream &out, HiggsBasis &H)
{
   H.Print(out);
   return out;
}

std::ostream &operator <<(std::ostream &out, WarsawBasis &W)
{
   W.Print(out);
   return out;
}

