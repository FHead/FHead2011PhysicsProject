//----------------------------------------------------------------------------
// Conversion of the HZZ angles <==> lepton vectors
// Author: Yi Chen (11223)
//----------------------------------------------------------------------------
#include <ostream>
#include <iostream>
//----------------------------------------------------------------------------
#include "Code/TauHelperFunctions2.h"
#include "AngleConversion_11332.h"
//----------------------------------------------------------------------------
LeptonVectors ConvertAnglesToVectors(const EventParameters &Angles, double HiggsPT, double HiggsEta)
{
   // Collect information
   double HMass = Angles.HMass;
   double ZMass = Angles.ZMass;
   double Z2Mass = Angles.Z2Mass;
   double PhiOffset = Angles.PhiH;
   double Phi0 = Angles.Phi0;
   double Theta0 = Angles.Theta0;
   double Phi = Angles.Phi;
   double Theta1 = Angles.Theta1;
   double Theta2 = Angles.Theta2;

   double Gamma1 = HMass / (2 * ZMass) * (1 + (ZMass * ZMass - Z2Mass * Z2Mass) / (HMass * HMass));
   double Gamma2 = HMass / (2 * Z2Mass) * (1 - (ZMass * ZMass - Z2Mass * Z2Mass) / (HMass * HMass));
   double Beta1 = GammaToBeta(Gamma1);
   double Beta2 = GammaToBeta(Gamma2);

   if(HMass < ZMass + Z2Mass)
      std::cerr << "[ConvertAnglesToVectors] WTF!  HMass < ZMass + Z2Mass.  Expect errors" << std::endl;

   // Calculate Higgs direction and boost in the ZZ frame (in that famous illustration used everywhere)
   double HiggsBoostGamma =
      sqrt(HiggsPT * HiggsPT / HMass / HMass * cosh(HiggsEta) * cosh(HiggsEta) + 1);
   double HiggsBoostBeta = GammaToBeta(HiggsBoostGamma);

   double HiggsPZ = HiggsPT * sinh(HiggsEta);
   double HiggsP = HiggsPT * cosh(HiggsEta);
   double HiggsE = sqrt(HiggsP * HiggsP + HMass * HMass);

   // Write down the four-vectors in the ZZ frame
   FourVector Lepton11, Lepton12, Lepton21, Lepton22;

   Lepton11[0] = Gamma1 * (1 + Beta1 * cos(Theta1));
   Lepton11[1] = -sin(Phi) * sin(Theta1);
   Lepton11[2] = -cos(Phi) * sin(Theta1);
   Lepton11[3] = -Gamma1 * (Beta1 + cos(Theta1));
   Lepton11 = Lepton11 * ZMass / 2;

   Lepton12[0] = Gamma1 * (1 - Beta1 * cos(Theta1));
   Lepton12[1] = sin(Phi) * sin(Theta1);
   Lepton12[2] = cos(Phi) * sin(Theta1);
   Lepton12[3] = -Gamma1 * (Beta1 - cos(Theta1));
   Lepton12 = Lepton12 * ZMass / 2;

   Lepton21[0] = Gamma2 * (1 + Beta2 * cos(Theta2));
   Lepton21[1] = 0;
   Lepton21[2] = sin(Theta2);
   Lepton21[3] = Gamma2 * (Beta2 + cos(Theta2));
   Lepton21 = Lepton21 * Z2Mass / 2;

   Lepton22[0] = Gamma2 * (1 - Beta2 * cos(Theta2));
   Lepton22[1] = 0;
   Lepton22[2] = -sin(Theta2);
   Lepton22[3] = Gamma2 * (Beta2 - cos(Theta2));
   Lepton22 = Lepton22 * Z2Mass / 2;

   FourVector IncomingA;
   IncomingA[0] = 1;
   IncomingA[1] = sin(Theta0) * cos(Phi0);
   IncomingA[2] = sin(Theta0) * sin(Phi0);
   IncomingA[3] = cos(Theta0);

   FourVector IncomingD;
   IncomingD[0] = (HiggsE - HiggsPZ) / HMass;
   IncomingD[1] = HiggsE * HiggsPZ / HMass / HiggsP - HiggsP / HMass;
   IncomingD[2] = 0;
   IncomingD[3] = HiggsPT / HiggsP;

   FourVector RotationAD = IncomingA.SpatialCross(IncomingD).SpatialNormalize();
   double RotationADAngle = IncomingA.SpatialDot(IncomingD)
      / IncomingA.GetP() / IncomingD.GetP();
   RotationADAngle = acos(RotationADAngle);

   Lepton11 = Lepton11.Rotate(IncomingA, PhiOffset);
   Lepton12 = Lepton12.Rotate(IncomingA, PhiOffset);
   Lepton21 = Lepton21.Rotate(IncomingA, PhiOffset);
   Lepton22 = Lepton22.Rotate(IncomingA, PhiOffset);

   Lepton11 = Lepton11.Rotate(RotationAD, RotationADAngle);
   Lepton12 = Lepton12.Rotate(RotationAD, RotationADAngle);
   Lepton21 = Lepton21.Rotate(RotationAD, RotationADAngle);
   Lepton22 = Lepton22.Rotate(RotationAD, RotationADAngle);

   Lepton11 = Lepton11.BoostX(HiggsBoostBeta);
   Lepton12 = Lepton12.BoostX(HiggsBoostBeta);
   Lepton21 = Lepton21.BoostX(HiggsBoostBeta);
   Lepton22 = Lepton22.BoostX(HiggsBoostBeta);

   FourVector HiggsMomentumC;
   HiggsMomentumC[0] = 1;
   HiggsMomentumC[1] = 1;
   HiggsMomentumC[2] = 0;
   HiggsMomentumC[3] = 0;

   FourVector FinalDirection;
   FinalDirection[0] = 1;
   FinalDirection[1] = HiggsPT;
   FinalDirection[2] = 0;
   FinalDirection[3] = HiggsPZ;

   FourVector RotationAxis = HiggsMomentumC.SpatialCross(FinalDirection).SpatialNormalize();
   double RotationAngle = HiggsMomentumC.SpatialDot(FinalDirection) / FinalDirection.GetP();
   RotationAngle = acos(RotationAngle);

   // Rotate to correct frame
   Lepton11 = Lepton11.Rotate(RotationAxis, RotationAngle);
   Lepton12 = Lepton12.Rotate(RotationAxis, RotationAngle);
   Lepton21 = Lepton21.Rotate(RotationAxis, RotationAngle);
   Lepton22 = Lepton22.Rotate(RotationAxis, RotationAngle);

   // Collect output
   LeptonVectors Result;
   Result.Lepton11 = Lepton11;
   Result.Lepton12 = Lepton12;
   Result.Lepton21 = Lepton21;
   Result.Lepton22 = Lepton22;

   return Result;
}
//----------------------------------------------------------------------------
EventParameters ConvertVectorsToAngles(const LeptonVectors &Leptons)
{
   // Some short-hand notation
   FourVector L11 = Leptons.Lepton11;
   FourVector L12 = Leptons.Lepton12;
   FourVector L21 = Leptons.Lepton21;
   FourVector L22 = Leptons.Lepton22;

   // Calculate basic information
   double HMass = (L11 + L12 + L21 + L22).GetMass();
   double ZMass = (L11 + L12).GetMass();
   double Z2Mass = (L21 + L22).GetMass();

   double Gamma2 = HMass / (2 * Z2Mass) * (1 - (ZMass * ZMass - Z2Mass * Z2Mass) / (HMass * HMass));
   double Beta2 = GammaToBeta(Gamma2);

   // Calculate higgs direction in lab frame, and boost to go to CM frame
   FourVector HiggsLab = L11 + L12 + L21 + L22;
   double HiggsBoostGamma = HiggsLab[0] / HMass;
   double HiggsBoostBeta = GammaToBeta(HiggsBoostGamma);

   // Boost everything back to the higgs rest frame
   L11 = L11.Boost(HiggsLab, -HiggsBoostBeta);
   L12 = L12.Boost(HiggsLab, -HiggsBoostBeta);
   L21 = L21.Boost(HiggsLab, -HiggsBoostBeta);
   L22 = L22.Boost(HiggsLab, -HiggsBoostBeta);

   // Z directions
   FourVector Z1 = L11 + L12;
   FourVector Z2 = L21 + L22;

   // now, the small theta's
   double Z1BoostBeta = GammaToBeta(Z1[0] / ZMass);
   double Z2BoostBeta = GammaToBeta(Z2[0] / Z2Mass);

   double Theta1 = GetAngle(Z1, L11.Boost(Z1, -Z1BoostBeta));
   double Theta2 = GetAngle(Z2, L21.Boost(Z2, -Z2BoostBeta));

   // Subtract out Z1-projection from L11, and same thing for L21
   // From these we can cook up the small phi
   FourVector L11Perpendicular = L11 - Z1 * (L11.SpatialDot(Z1)) / Z1.GetP2();
   FourVector L21Perpendicular = L21 - Z1 * (L21.SpatialDot(Z1)) / Z1.GetP2();
   FourVector HPerpendicular = HiggsLab - Z1 * (HiggsLab.SpatialDot(Z1)) / Z1.GetP2();

   double Phi = GetAngle(-L21Perpendicular, L11Perpendicular);
   if(Z2.SpatialDot(L21Perpendicular.SpatialCross(L11Perpendicular)) < 0)
      Phi = 2 * PI - Phi;
   while(Phi < 0)         Phi = Phi + 2 * PI;
   while(Phi >= 2 * PI)   Phi = Phi - 2 * PI;

   // Now the complicated stuff: theta0 and phi0
   FourVector Z2_B = (Leptons.Lepton21 + Leptons.Lepton22).RotateZ(HiggsLab.GetPhi());
   FourVector L21_B = Leptons.Lepton21.RotateZ(HiggsLab.GetPhi());
   FourVector Q_B(1, 0, 0, 1);

   FourVector H_B = HiggsLab.RotateZ(HiggsLab.GetPhi());
   FourVector H_C(HiggsLab[0], HiggsLab.GetP(), 0, 0);
   FourVector Axis_BC = H_B.SpatialCross(H_C).SpatialNormalize();
   double Angle_BC = H_B.SpatialDot(H_C) / H_B.GetP() / H_C.GetP();
   Angle_BC = acos(Angle_BC);

   FourVector Z2_C = Z2_B.Rotate(Axis_BC, Angle_BC);
   FourVector L21_C = L21_B.Rotate(Axis_BC, Angle_BC);
   FourVector Q_C = Q_B.Rotate(Axis_BC, Angle_BC);

   FourVector Z2_D = Z2_C.BoostX(-HiggsBoostBeta);
   FourVector L21_D = L21_C.BoostX(-HiggsBoostBeta);
   FourVector Q_D = Q_C.BoostX(-HiggsBoostBeta);

   double Theta0 = GetAngle(Z2_D, Q_D);

   double SinPhi0 = L21_D.SpatialDot(Q_D) / Q_D.GetP() * 2 / Z2Mass - cos(Theta0) * Gamma2 * (Beta2 + cos(Theta2));
   SinPhi0 = SinPhi0 / sin(Theta0) / sin(Theta2);
   double Phi0 = asin(SinPhi0);

   FourVector L21P_D = L21_D - Z2_D * L21_D.SpatialDot(Z2_D) / Z2_D.GetP2();
   FourVector QP_D = Q_D - Z2_D * Q_D.SpatialDot(Z2_D) / Z2_D.GetP2();
   if(L21P_D.SpatialDot(QP_D) < 0)
      Phi0 = PI - Phi0;
   if(Phi0 < 0)
      Phi0 = Phi0 + 2 * PI;
   if(Phi0 > 2 * PI)   // this should not happen, but still...
      Phi0 = Phi0 - 2 * PI;

   // collect output
   EventParameters Result;
   Result.Phi0 = Phi0;
   Result.Theta0 = Theta0;
   Result.Phi = Phi;
   Result.Theta1 = Theta1;
   Result.Theta2 = Theta2;
   Result.HMass = HMass;
   Result.ZMass = ZMass;
   Result.Z2Mass = Z2Mass;
   Result.PhiH = 0;
   return Result;
}
//----------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &out, const EventParameters &Value)
{
   out << "Event parameters: " << std::endl;
   out << "   Phi0   = " << Value.Phi0 << std::endl;
   out << "   Theta0 = " << Value.Theta0 << std::endl;
   out << "   Phi    = " << Value.Phi << std::endl;
   out << "   Theta1 = " << Value.Theta1 << std::endl;
   out << "   Theta2 = " << Value.Theta2 << std::endl;
   out << "   PhiH   = " << Value.PhiH << std::endl;
   out << "   HMass  = " << Value.HMass << std::endl;
   out << "   ZMass  = " << Value.ZMass << std::endl;
   out << "   Z2Mass = " << Value.Z2Mass << std::endl;

   return out;
}
//----------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &out, const LeptonVectors &Leptons)
{
   out << "Vectors of the 4 leptons = " << std::endl;
   out << "   L11 = " << Leptons.Lepton11 << std::endl;
   out << "   L12 = " << Leptons.Lepton12 << std::endl;
   out << "   L21 = " << Leptons.Lepton21 << std::endl;
   out << "   L22 = " << Leptons.Lepton22 << std::endl;

   return out;
}
//----------------------------------------------------------------------------
bool EventParameters::operator ==(const EventParameters &other)
{
   if(std::min(fabs(Phi0 - other.Phi0), 2 * PI - std::fabs(Phi0 - other.Phi0)) > 1e-5)   return false;
   if(std::fabs(Theta0 - other.Theta0) > 1e-5)                                           return false;
   if(std::min(fabs(Phi - other.Phi), 2 * PI - std::fabs(Phi - other.Phi)) > 1e-5)       return false;
   if(std::fabs(Theta1 - other.Theta1) > 1e-5)                                           return false;
   if(std::fabs(Theta2 - other.Theta2) > 1e-5)                                           return false;

   return true;
}
//----------------------------------------------------------------------------




