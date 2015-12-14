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
LeptonVectors ConvertAnglesToVectors(const EventParameters &Angles, double HiggsPT, double HiggsEta);
EventParameters ConvertVectorsToAngles(const LeptonVectors &Leptons);
std::ostream &operator <<(std::ostream &out, const EventParameters &Parameters);
std::ostream &operator <<(std::ostream &out, const LeptonVectors &Leptons);
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
public:
   EventParameters()
      : Phi0(0), Theta0(0), Phi(0), Theta1(0), Theta2(0), HMass(125),
      ZMass(91), Z2Mass(25), PhiH(0) {}
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




