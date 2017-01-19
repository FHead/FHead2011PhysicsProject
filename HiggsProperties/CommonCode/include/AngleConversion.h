//----------------------------------------------------------------------------
#ifndef ANGLECONVERSION_H_11223_JASKDJGHASHDIKFAHNWEIKHFIEHWFI
#define ANGLECONVERSION_H_11223_JASKDJGHASHDIKFAHNWEIKHFIEHWFI
//----------------------------------------------------------------------------
// Conversion of the HZZ angles <==> lepton vectors
// Author: Yi Chen (11223)
//----------------------------------------------------------------------------
#include <ostream>
#include <iostream>
//----------------------------------------------------------------------------
#include "Code/TauHelperFunctions3.h"
//----------------------------------------------------------------------------
struct EventParameters;
struct ZAEventParameters;
struct LeptonVectors;
struct ZALeptonVectors;
struct Cs;
struct ZACs;
struct GeneralScalarParameters;
struct ZPrimeParameters;
LeptonVectors ConvertAnglesToVectors(const EventParameters &Angles, double HiggsPT, double HiggsEta,
   bool FrameChoice = 0);
EventParameters ConvertVectorsToAngles(const LeptonVectors &Leptons,
   bool FrameChoice = 0);
LeptonVectors ConvertAnglesToVectorsRoberto(const EventParameters &Angles);
LeptonVectors ConvertAnglesToVectorsRoberto(const EventParameters &Angles, double HiggsPT, double HiggsEta);
ZALeptonVectors ConvertAnglesToVectorsRoberto(const ZAEventParameters &Angles);
EventParameters ConvertVectorsToAnglesRoberto(LeptonVectors &Leptons);
ZAEventParameters ConvertVectorsToAnglesRoberto(ZALeptonVectors &Leptons);
std::ostream &operator <<(std::ostream &out, const EventParameters &Parameters);
std::ostream &operator <<(std::ostream &out, LeptonVectors &Leptons);
std::ostream &operator <<(std::ostream &out, const ZAEventParameters &Parameters);
std::ostream &operator <<(std::ostream &out, ZALeptonVectors &Leptons);
void MultiplyFront(double A[3][3], double B[3][3]);
void MultiplyFrontX(double A[3][3], double B[3][3]);
void MultiplyFrontZ(double A[3][3], double B[3][3]);
void TransformVector(double A[3][3], FourVector &V);
void MultiplyFront(double A[4][4], double B[4][4]);
void MultiplyFrontTX(double A[4][4], double B[4][4]);
void MultiplyFrontTY(double A[4][4], double B[4][4]);
void MultiplyFrontTZ(double A[4][4], double B[4][4]);
void MultiplyFrontXY(double A[4][4], double B[4][4]);
void TransformVector(double A[4][4], FourVector &V);
double EventParametersDistance2(const EventParameters &P1, const EventParameters &P2);
double EventParametersDistance(const EventParameters &P1, const EventParameters &P2);
//----------------------------------------------------------------------------
struct EventParameters
{
public:
   double Phi0;
   double Theta0;
   double Phi;
   double Theta1;
   double Theta2;
   double HMass;
   double ZMass;
   double Z2Mass;
   double PhiH;
   double PhiOffset;
   double PTH;
   double YH;
public:
   EventParameters()
      : Phi0(0), Theta0(0), Phi(0), Theta1(0), Theta2(0), HMass(125),
      ZMass(91), Z2Mass(25), PhiH(0), PhiOffset(0), PTH(10), YH(0) {}
   ~EventParameters() {}
   bool operator ==(const EventParameters &other);
   bool ContainNaN() const;
};
//----------------------------------------------------------------------------
struct ZAEventParameters
{
public:
   double Phi0;
   double Theta0;
   double ThetaLL;
   double HMass;
   double ZMass;
   double PhiH;
   double PhiOffset;
   double PTH;
   double YH;
public:
   ZAEventParameters()
      : Phi0(0), Theta0(0), ThetaLL(0), HMass(125),
      ZMass(91), PhiH(0), PhiOffset(0), PTH(10), YH(0) {}
   ~ZAEventParameters() {}
   bool operator ==(const ZAEventParameters &other);
};
//----------------------------------------------------------------------------
struct LeptonVectors
{
public:
   FourVector Lepton11;
   FourVector Lepton12;   // these two add up to on-shell Z
   FourVector Lepton21;
   FourVector Lepton22;   // these two add up to off-shell Z
public:
   LeptonVectors() : Lepton11(FourVector()), Lepton12(FourVector()),
      Lepton21(FourVector()), Lepton22(FourVector()) {}
   ~LeptonVectors() {}
   FourVector GetTotal() const;
   LeptonVectors FlipZ1Z2() const;
   FourVector &operator [](int index);
   LeptonVectors ApplySmearing(Cs Smearing) const;
   LeptonVectors ApplyInverseSmearing(Cs Smearing) const;
   LeptonVectors GoToRest() const;
   LeptonVectors ReorderLeptons2e2mu() const;
   LeptonVectors ReorderLeptons4e() const;
   LeptonVectors ReorderLeptons4eAA() const;
};
//----------------------------------------------------------------------------
struct ZALeptonVectors
{
public:
   FourVector Photon;
   FourVector Lepton1;
   FourVector Lepton2;
public:
   ZALeptonVectors() : Photon(FourVector()), Lepton1(FourVector()), Lepton2(FourVector()) {}
   ~ZALeptonVectors() {}
   FourVector GetTotal() const;
   FourVector &operator [](int index);
   ZALeptonVectors ApplySmearing(ZACs Smearing) const;
   ZALeptonVectors ApplyInverseSmearing(ZACs Smearing) const;
   ZALeptonVectors GoToRest() const;
};
//----------------------------------------------------------------------------
struct Cs
{
public:
   double c[4];
public:
   Cs();
   Cs(double c0, double c1, double c2, double c3);
   Cs Inverse();
   Cs operator *(Cs other);
   Cs operator /(Cs other);
};
//----------------------------------------------------------------------------
struct ZACs
{
public:
   double c[3];
public:
   ZACs();
   ZACs(double c0, double c1, double c2);
   ZACs Inverse();
   ZACs operator *(ZACs other);
   ZACs operator /(ZACs other);
};
//----------------------------------------------------------------------------
struct GeneralScalarParameters
{
public:
   double aAR, aAI;
   double aAdR, aAdI;
   double aZAR, aZAI;
   double aZAdR, aZAdI;
   double aZR, aZI;
   double aZdR, aZdI;
   double ahR, ahI;
public:
   GeneralScalarParameters()
      : aAR(0), aAI(0), aAdR(0), aAdI(0), aZAR(0), aZAI(0), aZAdR(0), aZAdI(0),
      aZR(0), aZI(0), aZdR(0), aZdI(0), ahR(0), ahI(0)
   {
   }
};
//---------------------------------------------------------------------------
struct ZPrimeParameters
{
public:
   double VMass;
   double VWidth;
   double G1VL;
   double G1VR;
   double G2VL;
   double G2VR;
public:
   ZPrimeParameters()
      : VMass(50), VWidth(1), G1VL(1), G1VR(1), G2VL(1), G2VR(1)
   {
   }
};
//---------------------------------------------------------------------------
#endif




