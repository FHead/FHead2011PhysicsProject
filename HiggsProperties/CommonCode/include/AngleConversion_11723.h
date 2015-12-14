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
#include "Code/TauHelperFunctions2.h"
//----------------------------------------------------------------------------
struct EventParameters;
struct LeptonVectors;
LeptonVectors ConvertAnglesToVectors(const EventParameters &Angles, double HiggsPT, double HiggsEta,
   bool FrameChoice = 0);
EventParameters ConvertVectorsToAngles(const LeptonVectors &Leptons,
   bool FrameChoice = 0);
LeptonVectors ConvertAnglesToVectorsRoberto(const EventParameters &Angles, double HiggsPT, double HiggsEta);
EventParameters ConvertVectorsToAnglesRoberto(const LeptonVectors &Leptons);
std::ostream &operator <<(std::ostream &out, const EventParameters &Parameters);
std::ostream &operator <<(std::ostream &out, const LeptonVectors &Leptons);
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
public:
   EventParameters()
      : Phi0(0), Theta0(0), Phi(0), Theta1(0), Theta2(0), HMass(125),
      ZMass(91), Z2Mass(25), PhiH(0), PhiOffset(0) {}
   ~EventParameters() {}
   bool operator ==(const EventParameters &other);
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
   LeptonVectors() {}
   ~LeptonVectors() {}
};
//----------------------------------------------------------------------------
#endif




