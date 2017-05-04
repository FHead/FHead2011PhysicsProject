#ifndef EFTBASES_H_13764_AJSDFJASKDGJAKSDHGKAJSDHG
#define EFTBASES_H_13764_AJSDFJASKDGJAKSDHGKAJSDHG

#include <iostream>

#include "InterpretCoefficient.h"

class AVVBasis;
class HiggsBasis;
class WarsawBasis;
class LoopBasis;
class LoopBasis2;
class ExtendedAVVBasis;
struct FullAVVBasisVerbose;
union FullAVVBasis;
struct PolarSymmetricFullAVVBasisVerbose;
union PolarSymmetricFullAVVBasis;

std::ostream &operator <<(std::ostream &out, AVVBasis &A);
std::ostream &operator <<(std::ostream &out, HiggsBasis &H);
std::ostream &operator <<(std::ostream &out, WarsawBasis &W);
std::ostream &operator <<(std::ostream &out, LoopBasis &L);
std::ostream &operator <<(std::ostream &out, LoopBasis2 &L);

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
   AVVBasis(const LoopBasis2 &L);
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

class LoopBasis2
{
public:
   double A2ZZ;
   double A3ZZ;
   double A4ZZ;
   double YT;
   double YTA;
   double MT;
   double GWW;
   double CZ;
public:
   LoopBasis2();
   LoopBasis2(double L[8]);
   LoopBasis2(const InterpretationCoefficients &C);
   void Print(std::ostream &out);
};

class ExtendedAVVBasis
{
public:
   double A1ZZ;
   double A2ZZ;
   double A3ZZ;
   double A4ZZ;
   double A1ZV;
   double A2ZV;
   double A3ZV;
   double A4ZV;
   double A1ZA;
   double A2ZA;
   double A3ZA;
   double A4ZA;
   double A1VV;
   double A2VV;
   double A3VV;
   double A4VV;
   double A1VA;
   double A2VA;
   double A3VA;
   double A4VA;
   double A1AA;
   double A2AA;
   double A3AA;
   double A4AA;
public:
   ExtendedAVVBasis();
   ExtendedAVVBasis(double A[24]);
   void Print(std::ostream &out);
};

struct FullAVVBasisVerbose
{
   double A1ZZR;
   double A1ZZI;
   double A2ZZR;
   double A2ZZI;
   double A3ZZR;
   double A3ZZI;
   double A4ZZR;
   double A4ZZI;
   double A1ZVR;
   double A1ZVI;
   double A2ZVR;
   double A2ZVI;
   double A3ZVR;
   double A3ZVI;
   double A4ZVR;
   double A4ZVI;
   double A1ZAR;
   double A1ZAI;
   double A2ZAR;
   double A2ZAI;
   double A3ZAR;
   double A3ZAI;
   double A4ZAR;
   double A4ZAI;
   double A1VZR;
   double A1VZI;
   double A2VZR;
   double A2VZI;
   double A3VZR;
   double A3VZI;
   double A4VZR;
   double A4VZI;
   double A1VVR;
   double A1VVI;
   double A2VVR;
   double A2VVI;
   double A3VVR;
   double A3VVI;
   double A4VVR;
   double A4VVI;
   double A1VAR;
   double A1VAI;
   double A2VAR;
   double A2VAI;
   double A3VAR;
   double A3VAI;
   double A4VAR;
   double A4VAI;
   double A1AZR;
   double A1AZI;
   double A2AZR;
   double A2AZI;
   double A3AZR;
   double A3AZI;
   double A4AZR;
   double A4AZI;
   double A1AVR;
   double A1AVI;
   double A2AVR;
   double A2AVI;
   double A3AVR;
   double A3AVI;
   double A4AVR;
   double A4AVI;
   double A1AAR;
   double A1AAI;
   double A2AAR;
   double A2AAI;
   double A3AAR;
   double A3AAI;
   double A4AAR;
   double A4AAI;
};

union FullAVVBasis
{
public:
   double A[72];
   FullAVVBasisVerbose AVV;
public:
   FullAVVBasis();
   FullAVVBasis(PolarSymmetricFullAVVBasis &P);
};

struct PolarSymmetricFullAVVBasisVerbose
{
   double A;
   double Theta;
   double PhiD, ThetaD;   // VV, V = V, (ZZ, VV, AA)
   double PhiO, ThetaO;   // VV', V != V', (ZV, ZA, VA)
   double ThetaZZ, ThetaVV, ThetaAA, ThetaZV, ThetaZA, ThetaVA;
   double Psi12ZZ, Psi12VV, Psi12AA, Psi12ZV, Psi12ZA, Psi12VA;
   double Psi34ZZ, Psi34VV, Psi34AA, Psi34ZV, Psi34ZA, Psi34VA;
   double ThetaA1ZZ, ThetaA2ZZ, ThetaA3ZZ, ThetaA4ZZ;
   double ThetaA1VV, ThetaA2VV, ThetaA3VV, ThetaA4VV;
   double ThetaA1AA, ThetaA2AA, ThetaA3AA, ThetaA4AA;
   double ThetaA1ZV, ThetaA2ZV, ThetaA3ZV, ThetaA4ZV;
   double ThetaA1ZA, ThetaA2ZA, ThetaA3ZA, ThetaA4ZA;
   double ThetaA1VA, ThetaA2VA, ThetaA3VA, ThetaA4VA;
};

union PolarSymmetricFullAVVBasis
{
public:
   double P[48];
   PolarSymmetricFullAVVBasisVerbose V;
public:
   PolarSymmetricFullAVVBasis();
   PolarSymmetricFullAVVBasis(FullAVVBasis &AVV);
   double GetAngle(double X, double Y);
};

#endif
