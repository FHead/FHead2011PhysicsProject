#ifndef EFTBASES_H_13764_AJSDFJASKDGJAKSDHGKAJSDHG
#define EFTBASES_H_13764_AJSDFJASKDGJAKSDHGKAJSDHG

#include <iostream>

#include "InterpretCoefficient.h"

class AVVBasis;
class HiggsBasis;
class WarsawBasis;
class LoopBasis;

std::ostream &operator <<(std::ostream &out, AVVBasis &A);
std::ostream &operator <<(std::ostream &out, HiggsBasis &H);
std::ostream &operator <<(std::ostream &out, WarsawBasis &W);
std::ostream &operator <<(std::ostream &out, LoopBasis &L);

class AVVBasis
{
public:
   double A1ZZ;
   double A2ZZ;
   double A3ZZ;
   double A4ZZ;
   double A1ZA;
   double A2ZA;
   double A3ZA;
   double A4ZA;
   double A1AA;
   double A2AA;
   double A3AA;
   double A4AA;
public:
   AVVBasis();
   AVVBasis(double A[12]);
   AVVBasis(const HiggsBasis &H);
   AVVBasis(const WarsawBasis &W);
   AVVBasis(const LoopBasis &L);
   void Print(std::ostream &out);
};

class HiggsBasis
{
public:
   double DeltaCZ;
   double CZB;
   double CZZ;
   double CZZD;
   double CZA;
   double CZAD;
   double CAA;
   double CAAD;
public:
   HiggsBasis();
   HiggsBasis(double H[8]);
   HiggsBasis(const AVVBasis &A);
   HiggsBasis(const WarsawBasis &W);
   void Print(std::ostream &out);
};

class WarsawBasis
{
public:
   double CT;
   double CH;
   double CWW;
   double CWWD;
   double CWB;
   double CWBD;
   double CBB;
   double CBBD;
public:
   WarsawBasis();
   WarsawBasis(double W[8]);
   WarsawBasis(const AVVBasis &A);
   WarsawBasis(const HiggsBasis &H);
   void Print(std::ostream &out);
};

class LoopBasis
{
public:
   double A2ZZ;
   double A3ZZ;
   double A4ZZ;
   double YT;
   double YTA;
   double MT;
   double GWW;
   double MW;
public:
   LoopBasis();
   LoopBasis(double L[8]);
   LoopBasis(const InterpretationCoefficients &C);
   void Print(std::ostream &out);
};

#endif
