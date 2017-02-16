//----------------------------------------------------------------------------
// Conversion of the HZZ angles <==> lepton vectors
// Author: Yi Chen (11223)
//----------------------------------------------------------------------------
#include <ostream>
#include <iostream>
//----------------------------------------------------------------------------
#include "Code/TauHelperFunctions3.h"
//----------------------------------------------------------------------------
#include "AngleConversion.h"
#include "Constants.h"
//----------------------------------------------------------------------------
LeptonVectors ConvertAnglesToVectors(const EventParameters &Angles, double HiggsPT, double HiggsEta,
   bool CenterFrame)
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

   if(CenterFrame == false)
   {
      double HiggsPZ = HiggsPT * sinh(HiggsEta);
      double HiggsP = HiggsPT * cosh(HiggsEta);
      double HiggsE = sqrt(HiggsP * HiggsP + HMass * HMass);

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
      double CosRotationADAngle = IncomingA.SpatialDot(IncomingD) / IncomingD.GetP();
      double SinRotationADAngle = sqrt(1 - CosRotationADAngle * CosRotationADAngle);

      /*
      double RotationADAngle = acos(CosRotationADAngle);

      FourVector ALepton11 = Lepton11.Rotate(IncomingA, PhiOffset);
      FourVector ALepton12 = Lepton12.Rotate(IncomingA, PhiOffset);
      FourVector ALepton21 = Lepton21.Rotate(IncomingA, PhiOffset);
      FourVector ALepton22 = Lepton22.Rotate(IncomingA, PhiOffset);

      ALepton11 = ALepton11.Rotate(RotationAD, RotationADAngle);
      ALepton12 = ALepton12.Rotate(RotationAD, RotationADAngle);
      ALepton21 = ALepton21.Rotate(RotationAD, RotationADAngle);
      ALepton22 = ALepton22.Rotate(RotationAD, RotationADAngle);
      */

      double Psi_1 = PI / 2 - IncomingA.GetPhi();
      double CosPsi_1 = cos(Psi_1);
      double SinPsi_1 = sin(Psi_1);
      double CosTheta_1 = IncomingA[3];
      double SinTheta_1 = sqrt(1 - IncomingA[3] * IncomingA[3]);

      double Psi_2 = PI / 2 - RotationAD.GetPhi();
      double CosPsi_2 = cos(Psi_2);
      double SinPsi_2 = sin(Psi_2);
      double CosTheta_2 = RotationAD[3];
      double SinTheta_2 = sqrt(1 - RotationAD[3] * RotationAD[3]);

      double CosPsi_21 = cos(Psi_2 - Psi_1);
      double SinPsi_21 = sin(Psi_2 - Psi_1);

      double TotalRotation[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
      // double R1[3][3] = {{CosPsi_1, SinPsi_1, 0}, {-SinPsi_1, CosPsi_1, 0}, {0, 0, 1}};
      double R2[3][3] = {{1, 0, 0}, {0, CosTheta_1, SinTheta_1}, {0, -SinTheta_1, CosTheta_1}};
      double R3[3][3] = {{cos(PhiOffset), -sin(PhiOffset), 0}, {sin(PhiOffset), cos(PhiOffset), 0}, {0, 0, 1}};
      double R4[3][3] = {{1, 0, 0}, {0, CosTheta_1, -SinTheta_1}, {0, SinTheta_1, CosTheta_1}};
      double R5[3][3] = {{CosPsi_1, -SinPsi_1, 0}, {SinPsi_1, CosPsi_1, 0}, {0, 0, 1}};
      double R6[3][3] = {{CosPsi_2, SinPsi_2, 0}, {-SinPsi_2, CosPsi_2, 0}, {0, 0, 1}};
      double R7[3][3] = {{1, 0, 0}, {0, CosTheta_2, SinTheta_2}, {0, -SinTheta_2, CosTheta_2}};
      double R8[3][3] = {{CosRotationADAngle, -SinRotationADAngle, 0}, {SinRotationADAngle, CosRotationADAngle, 0}, {0, 0, 1}};
      double R9[3][3] = {{1, 0, 0}, {0, CosTheta_2, -SinTheta_2}, {0, SinTheta_2, CosTheta_2}};
      //double R10[3][3] = {{CosPsi_2, -SinPsi_2, 0}, {SinPsi_2, CosPsi_2, 0}, {0, 0, 1}};

      double R110[3][3] = {{CosPsi_21, -SinPsi_21, 0}, {SinPsi_21, CosPsi_21, 0}, {0, 0, 1}};

      MultiplyFrontZ(TotalRotation, R5);
      MultiplyFrontX(TotalRotation, R4);
      MultiplyFrontZ(TotalRotation, R3);
      MultiplyFrontX(TotalRotation, R2);

      // MultiplyFrontZ(TotalRotation, R1);
      // MultiplyFrontZ(TotalRotation, R10);
      MultiplyFrontZ(TotalRotation, R110);   // This combines previous two

      MultiplyFrontX(TotalRotation, R9);
      MultiplyFrontZ(TotalRotation, R8);
      MultiplyFrontX(TotalRotation, R7);
      MultiplyFrontZ(TotalRotation, R6);

      TransformVector(TotalRotation, Lepton11);
      TransformVector(TotalRotation, Lepton12);
      TransformVector(TotalRotation, Lepton21);
      TransformVector(TotalRotation, Lepton22);

      // std::cout << Lepton11 << " " << ALepton11 << std::endl;

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
   else
   {
      /*
      FourVector HiggsDirection;
      HiggsDirection.SetPtEtaPhiMass(HiggsPT, HiggsEta, PhiOffset, HMass);

      FourVector ALepton11 = Lepton11.RotateZ(-Phi0);
      FourVector ALepton12 = Lepton12.RotateZ(-Phi0);
      FourVector ALepton21 = Lepton21.RotateZ(-Phi0);
      FourVector ALepton22 = Lepton22.RotateZ(-Phi0);

      ALepton11 = ALepton11.RotateY(-Theta0);
      ALepton12 = ALepton12.RotateY(-Theta0);
      ALepton21 = ALepton21.RotateY(-Theta0);
      ALepton22 = ALepton22.RotateY(-Theta0);

      ALepton11 = ALepton11.Boost(HiggsDirection, HiggsBoostBeta);
      ALepton12 = ALepton12.Boost(HiggsDirection, HiggsBoostBeta);
      ALepton21 = ALepton21.Boost(HiggsDirection, HiggsBoostBeta);
      ALepton22 = ALepton22.Boost(HiggsDirection, HiggsBoostBeta);
      */

      double CosPhi0 = cos(Phi0);
      double SinPhi0 = sin(Phi0);
      double CosTheta0 = cos(Theta0);
      double SinTheta0 = sin(Theta0);

      // double TotalMatrix[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
      // double R1[4][4] = {{1, 0, 0, 0}, {0, CosPhi0, SinPhi0, 0},
      //    {0, -SinPhi0, CosPhi0, 0}, {0, 0, 0, 1}};
      
      double TotalMatrix[4][4] = {{1, 0, 0, 0}, {0, CosPhi0, SinPhi0, 0},
         {0, -SinPhi0, CosPhi0, 0}, {0, 0, 0, 1}};
      
      double R2[4][4] = {{1, 0, 0, 0}, {0, CosTheta0, 0, -SinTheta0},
         {0, 0, 1, 0}, {0, SinTheta0, 0, CosTheta0}};

      // MultiplyFrontTZ(TotalMatrix, R1);
      MultiplyFrontTY(TotalMatrix, R2);

      if(HiggsPT > 1e-8)
      {
         // double Psi = PI / 2 - PhiOffset;
         // double Theta = acos(HiggsDirection[3] / HiggsDirection.GetP());
         
         // double CosPsi = cos(Psi);
         // double SinPsi = sin(Psi);
         double CosPsi = sin(PhiOffset);
         double SinPsi = cos(PhiOffset);

         // double HiggsP = HiggsDirection.GetP();
         // double CosTheta = HiggsDirection[3] / HiggsP;
         // double SinTheta = HiggsPT / HiggsP;
         double CosTheta = tanh(HiggsEta);
         double SinTheta = sqrt(1 - CosTheta * CosTheta);
         // double SinTheta = 1.0 / cosh(HiggsEta);
         // double CosTheta = sqrt(1 - SinTheta * SinTheta);
         
         /*
         double R3[4][4] = {{1, 0, 0, 0}, {0, cos(Psi), -sin(Psi), 0},
            {0, sin(Psi), cos(Psi), 0}, {0, 0, 0, 1}};
         double R4[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, cos(Theta), -sin(Theta)},
            {0, 0, sin(Theta), cos(Theta)}};
         double R5[4][4] = {{HiggsBoostGamma, 0, 0, HiggsBoostGamma * HiggsBoostBeta}, {0, 1, 0, 0},
            {0, 0, 1, 0}, {HiggsBoostGamma * HiggsBoostBeta, 0, 0, HiggsBoostGamma}};
         double R6[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, cos(-Theta), -sin(-Theta)},
            {0, 0, sin(-Theta), cos(-Theta)}};
         double R7[4][4] = {{1, 0, 0, 0}, {0, cos(-Psi), -sin(-Psi), 0},
            {0, sin(-Psi), cos(-Psi), 0}, {0, 0, 0, 1}};
         */
         
         double R3[4][4] = {{1, 0, 0, 0}, {0, CosPsi, -SinPsi, 0},
            {0, SinPsi, CosPsi, 0}, {0, 0, 0, 1}};
         double R4[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, CosTheta, -SinTheta},
            {0, 0, SinTheta, CosTheta}};
         double R5[4][4] = {{HiggsBoostGamma, 0, 0, HiggsBoostGamma * HiggsBoostBeta}, {0, 1, 0, 0},
            {0, 0, 1, 0}, {HiggsBoostGamma * HiggsBoostBeta, 0, 0, HiggsBoostGamma}};
         double R6[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, CosTheta, SinTheta},
            {0, 0, -SinTheta, CosTheta}};
         double R7[4][4] = {{1, 0, 0, 0}, {0, CosPsi, SinPsi, 0},
            {0, -SinPsi, CosPsi, 0}, {0, 0, 0, 1}};

         MultiplyFrontTZ(TotalMatrix, R3);
         MultiplyFrontTX(TotalMatrix, R4);
         MultiplyFrontXY(TotalMatrix, R5);
         MultiplyFrontTX(TotalMatrix, R6);
         MultiplyFrontTZ(TotalMatrix, R7);

         // std::cout << "!";
      }
      else if(HiggsEta > 0)
      {
         double R5[4][4] = {{HiggsBoostGamma, 0, 0, HiggsBoostGamma * HiggsBoostBeta}, {0, 1, 0, 0},
            {0, 0, 1, 0}, {HiggsBoostGamma * HiggsBoostBeta, 0, 0, HiggsBoostGamma}};

         MultiplyFrontXY(TotalMatrix, R5);
      }
      else
      {
         double R5[4][4] = {{HiggsBoostGamma, 0, 0, HiggsBoostGamma * -HiggsBoostBeta}, {0, 1, 0, 0},
            {0, 0, 1, 0}, {HiggsBoostGamma * -HiggsBoostBeta, 0, 0, HiggsBoostGamma}};

         MultiplyFrontXY(TotalMatrix, R5);
      }

      LeptonVectors Result;
      Result.Lepton11 = Lepton11;
      Result.Lepton12 = Lepton12;
      Result.Lepton21 = Lepton21;
      Result.Lepton22 = Lepton22;
      
      TransformVector(TotalMatrix, Result.Lepton11);
      TransformVector(TotalMatrix, Result.Lepton12);
      TransformVector(TotalMatrix, Result.Lepton21);
      TransformVector(TotalMatrix, Result.Lepton22);

      // std::cout << Result.Lepton11 << " " << ALepton11 << std::endl;

      return Result;
   }
   
   LeptonVectors Result;
   Result.Lepton11 = Lepton11;
   Result.Lepton12 = Lepton12;
   Result.Lepton21 = Lepton21;
   Result.Lepton22 = Lepton22;

   return Result;
}
//----------------------------------------------------------------------------
EventParameters ConvertVectorsToAngles(LeptonVectors &Leptons, bool CenterFrame)
{
   // Some short-hand notation
   FourVector L11 = Leptons.Lepton11;
   FourVector L12 = Leptons.Lepton12;
   FourVector L21 = Leptons.Lepton21;
   FourVector L22 = Leptons.Lepton22;

   L11[0] = L11.GetP();
   L12[0] = L12.GetP();
   L21[0] = L21.GetP();
   L22[0] = L22.GetP();

   // Calculate basic information
   double HMass = (L11 + L12 + L21 + L22).GetMass();
   double ZMass = (L11 + L12).GetMass();
   double Z2Mass = (L21 + L22).GetMass();

   double Gamma1 = HMass / (2 * ZMass) * (1 + (ZMass * ZMass - Z2Mass * Z2Mass) / (HMass * HMass));
   double Beta1 = GammaToBeta(Gamma1);
   double Gamma2 = HMass / (2 * Z2Mass) * (1 - (ZMass * ZMass - Z2Mass * Z2Mass) / (HMass * HMass));
   double Beta2 = GammaToBeta(Gamma2);

   // Calculate higgs direction in lab frame, and boost to go to CM frame
   FourVector HiggsLab = L11 + L12 + L21 + L22;
   double HiggsBoostGamma = HiggsLab[0] / HMass;
   double HiggsBoostBeta = GammaToBeta(HiggsBoostGamma);

   // Boost everything back to the higgs rest frame
   L11 = L11.GammaBoost(HiggsLab, -HiggsBoostGamma);
   L12 = L12.GammaBoost(HiggsLab, -HiggsBoostGamma);
   L21 = L21.GammaBoost(HiggsLab, -HiggsBoostGamma);
   L22 = L22.GammaBoost(HiggsLab, -HiggsBoostGamma);

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
   double Theta0 = 0;
   double Phi0 = 0;
   double PhiH = 0;
   if(CenterFrame == false)
   {
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

      Theta0 = GetAngle(Z2_D, Q_D);

      double SinPhi0 = L21_D.SpatialDot(Q_D) / Q_D.GetP() * 2 / Z2Mass;
      SinPhi0 = SinPhi0 - cos(Theta0) * Gamma2 * (Beta2 + cos(Theta2));
      SinPhi0 = SinPhi0 / sin(Theta0) / sin(Theta2);
      Phi0 = asin(SinPhi0);

      // Look out for rounding errors
      if(SinPhi0 > 1)    Phi0 = PI / 2;
      if(SinPhi0 < -1)   Phi0 = -PI / 2;

      // FourVector L21P_D = L21_D - Z2_D * L21_D.SpatialDot(Z2_D) / Z2_D.GetP2();
      // FourVector QP_D = Q_D - Z2_D * Q_D.SpatialDot(Z2_D) / Z2_D.GetP2();
      // if(L21P_D.SpatialDot(QP_D) * Phi0 < 0)
      //    std::cout << "!" << std::endl;
      // if(L21P_D.SpatialDot(QP_D) < 0)
      //    Phi0 = PI - Phi0;

      FourVector L21P_D = L21_D - Z2_D * L21_D.SpatialDot(Z2_D) / Z2_D.GetP2();
      L21P_D = L21P_D / sin(Theta2);   // this is "y" direction, Z2_D is "z" direction
      FourVector XDirection = L21P_D.SpatialCross(Z2_D);
      if(XDirection.SpatialDot(Q_D) < 0)
         Phi0 = PI - Phi0;

      if(Phi0 < 0)
         Phi0 = Phi0 + 2 * PI;
      if(Phi0 > 2 * PI)
         Phi0 = Phi0 - 2 * PI;
   }
   else   // Guessed version of MELA angle implementation
   {
      Theta0 = Z2.SpatialDot(FourVector(1, 0, 0, 1)) / (Z2Mass * Beta2 * Gamma2);
      Theta0 = acos(Theta0);

      double SinPhi0 = L21.SpatialDot(FourVector(1, 0, 0, 1)) * 2 / Z2Mass
         - cos(Theta0) * Gamma2 * (cos(Theta2) + Beta2);
      SinPhi0 = SinPhi0 / sin(Theta0) / sin(Theta2);
      if(fabs(SinPhi0) > 1.0001)
      {
         std::cout << "Warning!  sin(Phi0) = " << SinPhi0 << std::endl;
         std::cout << Leptons << std::endl << std::endl;
         std::cout << L21 << " " << Z2Mass << " " << cos(Theta0) << " " << Gamma2 << " "
            << cos(Theta2) << " " << Beta2 << std::endl;
      }
      if(SinPhi0 > 1)   SinPhi0 = 1;   // these two lines are to prevent rounding errors
      if(SinPhi0 < -1)   SinPhi0 = -1;
      Phi0 = asin(SinPhi0);

      double CosPhi0 = L11.SpatialDot(FourVector(1, 0, 0, 1)) * 2 / ZMass
         + sin(Theta0) * SinPhi0 * cos(Phi) * sin(Theta1)
         + cos(Theta0) * Gamma1 * (Beta1 + cos(Theta1));
      CosPhi0 = -CosPhi0 / (sin(Theta0) * sin(Phi) * sin(Theta1));

      if(CosPhi0 < 0)      Phi0 = PI - Phi0;
      if(Phi0 < 0)         Phi0 = Phi0 + 2 * PI;
      if(Phi0 >= 2 * PI)   Phi0 = Phi0 - 2 * PI;

      PhiH = HiggsLab.GetPhi();
   }

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
   Result.PhiH = PhiH;
   return Result;
}
//----------------------------------------------------------------------------
LeptonVectors ConvertAnglesToVectorsRoberto(const EventParameters Angles)
{
   // Collect information
   double HMass = Angles.HMass;
   double ZMass = Angles.ZMass;
   double Z2Mass = Angles.Z2Mass;
   double PhiH = Angles.PhiH;
   double PhiOffset = Angles.PhiOffset;
   double Phi0 = Angles.Phi0;
   double Theta0 = Angles.Theta0;
   double Phi = Angles.Phi;
   double Theta1 = Angles.Theta1;
   double Theta2 = Angles.Theta2;
   double HiggsPT = Angles.PTH;
   double HiggsY = Angles.YH;

   while(Theta0 < 0)         Theta0 = Theta0 + 2 * PI;
   while(Theta0 >= 2 * PI)   Theta0 = Theta0 - 2 * PI;
   while(Theta1 < 0)         Theta1 = Theta1 + 2 * PI;
   while(Theta1 >= 2 * PI)   Theta1 = Theta1 - 2 * PI;
   while(Theta2 < 0)         Theta2 = Theta2 + 2 * PI;
   while(Theta2 >= 2 * PI)   Theta2 = Theta2 - 2 * PI;

   if(Theta0 > PI)           Theta0 = 2 * PI - Theta0;
   if(Theta1 > PI)           Theta1 = 2 * PI - Theta1;
   if(Theta2 > PI)           Theta2 = 2 * PI - Theta2;

   double Phi1 = PI - Phi0;
   double Phi2 = Phi + Phi0;

   double Gamma1 = HMass / (2 * ZMass) * (1 + (ZMass * ZMass - Z2Mass * Z2Mass) / (HMass * HMass));
   double Gamma2 = HMass / (2 * Z2Mass) * (1 - (ZMass * ZMass - Z2Mass * Z2Mass) / (HMass * HMass));
   double Beta1 = GammaToBeta(Gamma1);
   double Beta2 = GammaToBeta(Gamma2);

   if(HMass < ZMass + Z2Mass)
      std::cerr << "[ConvertAnglesToVectors] WTF!  HMass < ZMass + Z2Mass.  Expect errors" << std::endl;

   double SinTheta0 = sin(Theta0);   double CosTheta0 = cos(Theta0);
   double SinTheta1 = sin(Theta1);   double CosTheta1 = cos(Theta1);
   double SinTheta2 = sin(Theta2);   double CosTheta2 = cos(Theta2);
   double SinPhi1 = sin(Phi1);       double CosPhi1 = cos(Phi1);
   double SinPhi2 = sin(Phi2);       double CosPhi2 = cos(Phi2);
   
   // Write down the four-vectors in the ZZ frame
   FourVector Lepton11, Lepton12, Lepton21, Lepton22;

   Lepton11[0] = Gamma1 * (1 + Beta1 * CosTheta1);
   Lepton11[1] = Gamma1 * (Beta1 + CosTheta1) * SinTheta0 + CosTheta0 * CosPhi1 * SinTheta1;
   Lepton11[2] = SinTheta1 * SinPhi1;
   Lepton11[3] = Gamma1 * CosTheta0 * (Beta1 + CosTheta1) - CosPhi1 * SinTheta0 * SinTheta1;
   Lepton11 = Lepton11 * ZMass / 2;

   Lepton12[0] = Gamma1 * (1 - Beta1 * CosTheta1);
   Lepton12[1] = Gamma1 * (Beta1 - CosTheta1) * SinTheta0 - CosTheta0 * CosPhi1 * SinTheta1;
   Lepton12[2] = -SinTheta1 * SinPhi1;
   Lepton12[3] = Gamma1 * CosTheta0 * (Beta1 - CosTheta1) + CosPhi1 * SinTheta0 * SinTheta1;
   Lepton12 = Lepton12 * ZMass / 2;

   Lepton21[0] = Gamma2 * (1 + Beta2 * CosTheta2);
   Lepton21[1] = -Gamma2 * (Beta2 + CosTheta2) * SinTheta0 - CosTheta0 * CosPhi2 * SinTheta2;
   Lepton21[2] = SinTheta2 * SinPhi2;
   Lepton21[3] = -Gamma2 * CosTheta0 * (Beta2 + CosTheta2) + CosPhi2 * SinTheta0 * SinTheta2;
   Lepton21 = Lepton21 * Z2Mass / 2;

   Lepton22[0] = Gamma2 * (1 - Beta2 * CosTheta2);
   Lepton22[1] = Gamma2 * (-Beta2 + CosTheta2) * SinTheta0 + CosTheta0 * CosPhi2 * SinTheta2;
   Lepton22[2] = -SinTheta2 * SinPhi2;
   Lepton22[3] = -Gamma2 * CosTheta0 * (Beta2 - CosTheta2) - CosPhi2 * SinTheta0 * SinTheta2;
   Lepton22 = Lepton22 * Z2Mass / 2;

   LeptonVectors Result;

   FourVector HiggsDirection;
   HiggsDirection.SetPtYPhiMass(HiggsPT, HiggsY, PhiH, HMass);
   double HiggsBoostGamma = HiggsDirection[0] / HMass;

   if(HiggsBoostGamma < 1)
      std::cerr << "[AnglesToVectorsRoberto] Conversion error.  Gamma = " << HiggsBoostGamma << std::endl;

   Result.Lepton11 = Lepton11.RotateZ(PhiOffset).GammaBoost(HiggsDirection, HiggsBoostGamma);
   Result.Lepton12 = Lepton12.RotateZ(PhiOffset).GammaBoost(HiggsDirection, HiggsBoostGamma);
   Result.Lepton21 = Lepton21.RotateZ(PhiOffset).GammaBoost(HiggsDirection, HiggsBoostGamma);
   Result.Lepton22 = Lepton22.RotateZ(PhiOffset).GammaBoost(HiggsDirection, HiggsBoostGamma);

   // Result.Lepton11 = Lepton11.GammaBoost(HiggsDirection, HiggsBoostGamma);
   // Result.Lepton12 = Lepton12.GammaBoost(HiggsDirection, HiggsBoostGamma);
   // Result.Lepton21 = Lepton21.GammaBoost(HiggsDirection, HiggsBoostGamma);
   // Result.Lepton22 = Lepton22.GammaBoost(HiggsDirection, HiggsBoostGamma);

   return Result;
}
//----------------------------------------------------------------------------
LeptonVectors ConvertAnglesToVectorsRoberto(const EventParameters &Angles, double HiggsPT, double HiggsEta)
{
   EventParameters TempAngles = Angles;
   FourVector H;
   H.SetPtEtaPhiMass(HiggsPT, HiggsEta, Angles.PhiH, Angles.HMass);
   TempAngles.PTH = HiggsPT;
   TempAngles.YH = H.GetY();
   return ConvertAnglesToVectorsRoberto(TempAngles);
}
//----------------------------------------------------------------------------
ZALeptonVectors ConvertAnglesToVectorsRoberto(const ZAEventParameters &Angles)
{
   // Collect information
   double HMass = Angles.HMass;
   double ZMass = Angles.ZMass;
   double PhiH = Angles.PhiH;
   double PhiOffset = Angles.PhiOffset;
   double Phi0 = Angles.Phi0;
   double Theta0 = Angles.Theta0;
   double ThetaLL = Angles.ThetaLL;
   double HiggsPT = Angles.PTH;
   double HiggsY = Angles.YH;

   while(Theta0 < 0)         Theta0 = Theta0 + 2 * PI;
   while(Theta0 >= 2 * PI)   Theta0 = Theta0 - 2 * PI;
   while(ThetaLL < 0)         ThetaLL = ThetaLL + 2 * PI;
   while(ThetaLL >= 2 * PI)   ThetaLL = ThetaLL - 2 * PI;

   if(Theta0 > PI)           Theta0 = 2 * PI - Theta0;
   if(ThetaLL > PI)           ThetaLL = 2 * PI - ThetaLL;

   double Phi1 = PI - Phi0;

   double Gamma = HMass / (2 * ZMass) * (1 + (ZMass * ZMass) / (HMass * HMass));
   double Beta = GammaToBeta(Gamma);

   if(HMass < ZMass)
      std::cerr << "[ConvertAnglesToVectors] WTF!  HMass < ZMass.  Expect errors" << std::endl;
   
   // Write down the four-vectors in the H frame
   FourVector Lepton1, Lepton2, Photon;

   Lepton1[0] = Gamma * (1 + Beta * cos(ThetaLL));
   Lepton1[1] = Gamma * (Beta + cos(ThetaLL)) * sin(Theta0) + cos(Theta0) * cos(Phi1) * sin(ThetaLL);
   Lepton1[2] = sin(ThetaLL) * sin(Phi1);
   Lepton1[3] = Gamma * cos(Theta0) * (Beta + cos(ThetaLL)) - cos(Phi1) * sin(Theta0) * sin(ThetaLL);
   Lepton1 = Lepton1 * ZMass / 2;

   Lepton2[0] = Gamma * (1 - Beta * cos(ThetaLL));
   Lepton2[1] = Gamma * (Beta - cos(ThetaLL)) * sin(Theta0) - cos(Theta0) * cos(Phi1) * sin(ThetaLL);
   Lepton2[2] = -sin(ThetaLL) * sin(Phi1);
   Lepton2[3] = Gamma * cos(Theta0) * (Beta - cos(ThetaLL)) + cos(Phi1) * sin(Theta0) * sin(ThetaLL);
   Lepton2 = Lepton2 * ZMass / 2;

   Photon = -(Lepton1 + Lepton2);
   Photon[0] = Photon.GetP();

   ZALeptonVectors Result;

   FourVector HiggsDirection;
   HiggsDirection.SetPtYPhiMass(HiggsPT, HiggsY, PhiH, HMass);
   double HiggsBoostGamma = HiggsDirection[0] / HMass;

   if(HiggsBoostGamma < 1)
      std::cerr << "[AnglesToVectorsRoberto] Conversion error.  Gamma = " << HiggsBoostGamma << std::endl;

   Result.Lepton1 = Lepton1.RotateZ(PhiOffset).GammaBoost(HiggsDirection, HiggsBoostGamma);
   Result.Lepton2 = Lepton2.RotateZ(PhiOffset).GammaBoost(HiggsDirection, HiggsBoostGamma);
   Result.Photon = Photon.RotateZ(PhiOffset).GammaBoost(HiggsDirection, HiggsBoostGamma);

   return Result;
}
//----------------------------------------------------------------------------
EventParameters ConvertVectorsToAnglesRoberto(LeptonVectors Leptons)
{
   FourVector L11 = Leptons.Lepton11;
   FourVector L12 = Leptons.Lepton12;
   FourVector L21 = Leptons.Lepton21;
   FourVector L22 = Leptons.Lepton22;

   L11[0] = L11.GetP();
   L12[0] = L12.GetP();
   L21[0] = L21.GetP();
   L22[0] = L22.GetP();

   double HMass = (L11 + L12 + L21 + L22).GetMass();
   double ZMass = (L11 + L12).GetMass();
   double Z2Mass = (L21 + L22).GetMass();

   double Gamma1 = HMass / (2 * ZMass) * (1 + (ZMass * ZMass - Z2Mass * Z2Mass) / (HMass * HMass));
   double Beta1 = GammaToBeta(Gamma1);
   double Gamma2 = HMass / (2 * Z2Mass) * (1 - (ZMass * ZMass - Z2Mass * Z2Mass) / (HMass * HMass));
   double Beta2 = GammaToBeta(Gamma2);

   FourVector HiggsLab = L11 + L12 + L21 + L22;
   double HiggsBoostGamma = HiggsLab[0] / HMass;
   double HiggsBoostBeta = GammaToBeta(HiggsBoostGamma);
   double PhiH = HiggsLab.GetPhi();

   L11 = L11.GammaBoost(HiggsLab, -HiggsBoostGamma);
   L12 = L12.GammaBoost(HiggsLab, -HiggsBoostGamma);
   L21 = L21.GammaBoost(HiggsLab, -HiggsBoostGamma);
   L22 = L22.GammaBoost(HiggsLab, -HiggsBoostGamma);

   FourVector Z1 = L11 + L12;
   FourVector Z2 = L21 + L22;

   double Z1BoostBeta = GammaToBeta(Z1[0] / ZMass);
   double Z2BoostBeta = GammaToBeta(Z2[0] / Z2Mass);

   double Theta1 = GetAngle(Z1, L11.GammaBoost(Z1, -Z1[0] / ZMass));
   double Theta2 = GetAngle(Z2, L21.GammaBoost(Z2, -Z2[0] / Z2Mass));

   FourVector L11Perpendicular = L11 - Z1 * (L11.SpatialDot(Z1)) / Z1.GetP2();
   FourVector L21Perpendicular = L21 - Z1 * (L21.SpatialDot(Z1)) / Z1.GetP2();
   FourVector HPerpendicular = HiggsLab - Z1 * (HiggsLab.SpatialDot(Z1)) / Z1.GetP2();

   double Phi = GetAngle(-L21Perpendicular, L11Perpendicular) - PI;
   if(Z2.SpatialDot(L21Perpendicular.SpatialCross(L11Perpendicular)) < 0)
      Phi = 2 * PI - Phi;
   while(Phi < 0)         Phi = Phi + 2 * PI;
   while(Phi >= 2 * PI)   Phi = Phi - 2 * PI;

   FourVector P1CM(HMass / 2, 0, 0, HMass / 2);
   double CosTheta0 = -(P1CM * (L11 + L12) / (0.5 * ZMass * HMass * Gamma1) - 1) / Beta1;
   double Theta0 = acos(CosTheta0);

   double CosPhi1 = (P1CM * (L11 - L12)) / (0.5 * ZMass * HMass)
      - Gamma1 * (Beta1 - cos(Theta0)) * cos(Theta1);
   CosPhi1 = CosPhi1 / (fabs(sin(Theta0) * sin(Theta1)));

   double SinPhi1 = (P1CM.SpatialCross(L11 + L12).SpatialDot(L11))
      / (0.25 * ZMass * ZMass * HMass * Beta1 * Gamma1 * fabs(sin(Theta0)) * sin(Theta1));

   double Phi1 = PI - acos(CosPhi1);
   if(SinPhi1 < 0)
      Phi1 = -Phi1;

   if(Phi1 < 0)         Phi1 = Phi1 + 2 * PI;
   if(Phi1 >= 2 * PI)   Phi1 = Phi1 - 2 * PI;
   
   FourVector Lepton11;
   Lepton11[0] = Gamma1 * (1 + Beta1 * cos(Theta1));
   Lepton11[1] = Gamma1 * (Beta1 + cos(Theta1)) * sin(Theta0) + cos(Theta0) * cos(PI-Phi1) * sin(Theta1);
   Lepton11[2] = sin(Theta1) * sin(Phi1);
   Lepton11[3] = Gamma1 * cos(Theta0) * (Beta1 + cos(Theta1)) - cos(PI-Phi1) * sin(Theta0) * sin(Theta1);
   Lepton11 = Lepton11 * ZMass / 2;
   
   EventParameters Result;

   Result.Phi0 = Phi1;
   Result.Theta0 = Theta0;
   Result.Phi = Phi;
   Result.Theta1 = Theta1;
   Result.Theta2 = Theta2;
   Result.HMass = HMass;
   Result.ZMass = ZMass;
   Result.Z2Mass = Z2Mass;
   Result.PhiH = PhiH;
   Result.PhiOffset = -(Lepton11.GetPhi() - L11.GetPhi());
   Result.PTH = HiggsLab.GetPT();
   Result.YH = HiggsLab.GetY();

   if(Result.PTH < 1e-8)
      Result.PhiH = 0;

   return Result;
}
//----------------------------------------------------------------------------
ZAEventParameters ConvertVectorsToAnglesRoberto(ZALeptonVectors &Leptons)
{
   FourVector L1 = Leptons.Lepton1;
   FourVector L2 = Leptons.Lepton2;
   FourVector Photon = Leptons.Photon;

   L1[0] = L1.GetP();
   L2[0] = L2.GetP();
   Photon[0] = Photon.GetP();

   double HMass = (L1 + L2 + Photon).GetMass();
   double ZMass = (L1 + L2).GetMass();

   double Gamma = HMass / (2 * ZMass) * (1 + (ZMass * ZMass) / (HMass * HMass));
   double Beta = GammaToBeta(Gamma);

   FourVector HiggsLab = L1 + L2 + Photon;
   double HiggsBoostGamma = HiggsLab[0] / HMass;
   double HiggsBoostBeta = GammaToBeta(HiggsBoostGamma);
   double PhiH = HiggsLab.GetPhi();

   L1 = L1.GammaBoost(HiggsLab, -HiggsBoostGamma);
   L2 = L2.GammaBoost(HiggsLab, -HiggsBoostGamma);
   Photon = Photon.GammaBoost(HiggsLab, -HiggsBoostGamma);

   FourVector Z = L1 + L2;

   double ZBoostBeta = GammaToBeta(Z[0] / ZMass);

   double ThetaLL = GetAngle(Z, L1.GammaBoost(Z, -Z[0] / ZMass));

   FourVector P1CM(HMass / 2, 0, 0, HMass / 2);
   double CosTheta0 = -(P1CM * (L1 + L2) / (0.5 * ZMass * HMass * Gamma) - 1) / Beta;
   double Theta0 = acos(CosTheta0);

   double CosPhi1 = (P1CM * (L1 - L2)) / (0.5 * ZMass * HMass)
      - Gamma * (Beta - cos(Theta0)) * cos(ThetaLL);
   CosPhi1 = CosPhi1 / (fabs(sin(Theta0) * sin(ThetaLL)));

   double SinPhi1 = (P1CM.SpatialCross(L1 + L2).SpatialDot(L1))
      / (0.25 * ZMass * ZMass * HMass * Beta * Gamma * fabs(sin(Theta0)) * sin(ThetaLL));

   double Phi1 = PI - acos(CosPhi1);
   if(SinPhi1 < 0)
      Phi1 = -Phi1;
   if(Phi1 != Phi1)     Phi1 = 0;

   if(Phi1 < 0)         Phi1 = Phi1 + 2 * PI;
   if(Phi1 >= 2 * PI)   Phi1 = Phi1 - 2 * PI;
   
   FourVector Lepton1;
   Lepton1[0] = Gamma * (1 + Beta * cos(ThetaLL));
   Lepton1[1] = Gamma * (Beta + cos(ThetaLL)) * sin(Theta0) + cos(Theta0) * cos(PI-Phi1) * sin(ThetaLL);
   Lepton1[2] = sin(ThetaLL) * sin(Phi1);
   Lepton1[3] = Gamma * cos(Theta0) * (Beta + cos(ThetaLL)) - cos(PI-Phi1) * sin(Theta0) * sin(ThetaLL);
   Lepton1 = Lepton1 * ZMass / 2;
   
   ZAEventParameters Result;

   Result.Phi0 = Phi1;
   Result.Theta0 = Theta0;
   Result.ThetaLL = ThetaLL;
   Result.HMass = HMass;
   Result.ZMass = ZMass;
   Result.PhiH = PhiH;
   Result.PhiOffset = -(Lepton1.GetPhi() - L1.GetPhi());
   Result.PTH = HiggsLab.GetPT();
   Result.YH = HiggsLab.GetY();

   if(Result.PTH < 1e-8)
      Result.PhiH = 0;

   return Result;
}
//----------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &out, const EventParameters &Value)
{
   out << "Event parameters: " << std::endl;
   out << "   Phi0/Phi1 = " << Value.Phi0 << std::endl;
   out << "   Theta0    = " << Value.Theta0 << ", cos(Theta0) = " << cos(Value.Theta0) << std::endl;
   out << "   Phi       = " << Value.Phi << std::endl;
   out << "   Theta1    = " << Value.Theta1 << ", cos(Theta1) = " << cos(Value.Theta1) << std::endl;
   out << "   Theta2    = " << Value.Theta2 << ", cos(Theta2) = " << cos(Value.Theta2) << std::endl;
   out << "   PhiH      = " << Value.PhiH << std::endl;
   out << "   PhiOffset = " << Value.PhiOffset << std::endl;
   out << "   HMass     = " << Value.HMass << std::endl;
   out << "   ZMass     = " << Value.ZMass << std::endl;
   out << "   Z2Mass    = " << Value.Z2Mass << std::endl;
   out << "   PTH       = " << Value.PTH << std::endl;
   out << "   YH        = " << Value.YH << std::endl;

   return out;
}
//----------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &out, LeptonVectors &Leptons)
{
   out << "Vectors of the 4 leptons = " << std::endl;
   out << "   L11 = " << Leptons.Lepton11 << " " << Leptons.Lepton11.GetPT() << " " << Leptons.Lepton11.GetEta() << std::endl;
   out << "   L12 = " << Leptons.Lepton12 << " " << Leptons.Lepton12.GetPT() << " " << Leptons.Lepton12.GetEta() << std::endl;
   out << "   L21 = " << Leptons.Lepton21 << " " << Leptons.Lepton21.GetPT() << " " << Leptons.Lepton21.GetEta() << std::endl;
   out << "   L22 = " << Leptons.Lepton22 << " " << Leptons.Lepton22.GetPT() << " " << Leptons.Lepton22.GetEta() << std::endl;

   return out;
}
//----------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &out, const ZAEventParameters &Value)
{
   out << "Event parameters: " << std::endl;
   out << "   Phi0/Phi1 = " << Value.Phi0 << std::endl;
   out << "   Theta0    = " << Value.Theta0 << ", cos(Theta0) = " << cos(Value.Theta0) << std::endl;
   out << "   ThetaLL   = " << Value.ThetaLL << ", cos(ThetaLL) = " << cos(Value.ThetaLL) << std::endl;
   out << "   PhiH      = " << Value.PhiH << std::endl;
   out << "   PhiOffset = " << Value.PhiOffset << std::endl;
   out << "   HMass     = " << Value.HMass << std::endl;
   out << "   ZMass     = " << Value.ZMass << std::endl;
   out << "   PTH       = " << Value.PTH << std::endl;
   out << "   YH        = " << Value.YH << std::endl;

   return out;
}
//----------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &out, ZALeptonVectors &Leptons)
{
   out << "Vectors of the leptons and photon = " << std::endl;
   out << "   L1 =     " << Leptons.Lepton1 << std::endl;
   out << "   L2 =     " << Leptons.Lepton2 << std::endl;
   out << "   Photon = " << Leptons.Photon << std::endl;

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
bool EventParameters::ContainNaN() const
{
   if(HMass != HMass)           return true;
   if(ZMass != ZMass)           return true;
   if(Z2Mass != Z2Mass)         return true;
   if(Phi0 != Phi0)             return true;
   if(Theta0 != Theta0)         return true;
   if(Phi != Phi)               return true;
   if(Theta1 != Theta1)         return true;
   if(Theta2 != Theta2)         return true;
   if(PhiOffset != PhiOffset)   return true;
   if(PhiH != PhiH)             return true;
   if(PTH != PTH)               return true;
   if(YH != YH)                 return true;

   return false;
}
//----------------------------------------------------------------------------
bool ZAEventParameters::operator ==(const ZAEventParameters &other)
{
   if(std::min(fabs(Phi0 - other.Phi0), 2 * PI - std::fabs(Phi0 - other.Phi0)) > 1e-5)   return false;
   if(std::fabs(Theta0 - other.Theta0) > 1e-5)                                           return false;
   if(std::fabs(ThetaLL - other.ThetaLL) > 1e-5)                                         return false;

   return true;
}
//----------------------------------------------------------------------------
FourVector LeptonVectors::GetTotal() const
{
   return Lepton11 + Lepton12 + Lepton21 + Lepton22;
}
//----------------------------------------------------------------------------
LeptonVectors LeptonVectors::FlipZ1Z2() const
{
   LeptonVectors Result;
   Result.Lepton11 = Lepton21;
   Result.Lepton12 = Lepton22;
   Result.Lepton21 = Lepton11;
   Result.Lepton22 = Lepton12;
   return Result;
}
//----------------------------------------------------------------------------
FourVector &LeptonVectors::operator [](int index)
{
   switch(index)
   {
   case 0:
      return Lepton11;
   case 1:
      return Lepton12;
   case 2:
      return Lepton21;
   case 3:
      return Lepton22;
   }

   return Lepton11;
}
//----------------------------------------------------------------------------
LeptonVectors LeptonVectors::ApplySmearing(Cs Smearing) const
{
   LeptonVectors NewOne;
   NewOne.Lepton11 = Lepton11 * Smearing.c[0];
   NewOne.Lepton12 = Lepton12 * Smearing.c[1];
   NewOne.Lepton21 = Lepton21 * Smearing.c[2];
   NewOne.Lepton22 = Lepton22 * Smearing.c[3];
   return NewOne;
}
//----------------------------------------------------------------------------
LeptonVectors LeptonVectors::ApplyInverseSmearing(Cs Smearing) const
{
   LeptonVectors NewOne;
   NewOne.Lepton11 = Lepton11 / Smearing.c[0];
   NewOne.Lepton12 = Lepton12 / Smearing.c[1];
   NewOne.Lepton21 = Lepton21 / Smearing.c[2];
   NewOne.Lepton22 = Lepton22 / Smearing.c[3];
   return NewOne;
}
//----------------------------------------------------------------------------
LeptonVectors LeptonVectors::GoToRest() const
{
   FourVector Total = GetTotal();
   double P = Total.GetP();
   double E = Total[0];

   LeptonVectors Result;
   Result.Lepton11 = Lepton11.Boost(-Total, P / E);
   Result.Lepton12 = Lepton12.Boost(-Total, P / E);
   Result.Lepton21 = Lepton21.Boost(-Total, P / E);
   Result.Lepton22 = Lepton22.Boost(-Total, P / E);

   return Result;
}
//----------------------------------------------------------------------------
LeptonVectors LeptonVectors::ReorderLeptons2e2mu() const
{
   LeptonVectors Leptons = *this;

   double M12 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M34 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   
   double D12 = fabs(M12 - 91.186);
   double D34 = fabs(M34 - 91.186);

   if(D34 <= D12)
   {
      std::swap(Leptons.Lepton11, Leptons.Lepton21);
      std::swap(Leptons.Lepton12, Leptons.Lepton22);
   }

   return Leptons;
}
//----------------------------------------------------------------------------
LeptonVectors LeptonVectors::ReorderLeptons4e() const
{
   LeptonVectors Leptons = *this;

   double M12 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M14 = (Leptons.Lepton11 + Leptons.Lepton22).GetMass();
   double M32 = (Leptons.Lepton21 + Leptons.Lepton12).GetMass();
   double M34 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   double D12 = fabs(M12 - 91.186);
   double D14 = fabs(M14 - 91.186);
   double D32 = fabs(M32 - 91.186);
   double D34 = fabs(M34 - 91.186);

   if(D12 <= D14 && D12 <= D32 && D12 <= D34)
   {
      // Do nothing...already ordered
   }
   else if(D14 <= D32 && D14 <= D34)
      std::swap(Leptons.Lepton12, Leptons.Lepton22);
   else if(D32 <= D34)
      std::swap(Leptons.Lepton11, Leptons.Lepton21);
   else
   {
      std::swap(Leptons.Lepton11, Leptons.Lepton21);
      std::swap(Leptons.Lepton12, Leptons.Lepton22);
   }

   return Leptons;
}
//----------------------------------------------------------------------------
LeptonVectors LeptonVectors::ReorderLeptons4eAA() const
{
   LeptonVectors Leptons = *this;

   double M12 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M14 = (Leptons.Lepton11 + Leptons.Lepton22).GetMass();
   double M32 = (Leptons.Lepton21 + Leptons.Lepton12).GetMass();
   double M34 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(std::max(M12, M34) < std::max(M14, M32))
   {
      if(M12 < M34)   // first pair should be 34 (21 + 22)
      {
         std::swap(Leptons.Lepton11, Leptons.Lepton21);
         std::swap(Leptons.Lepton12, Leptons.Lepton22);
      }
   }
   else
   {
      if(M14 > M32)   // first pair should be 14 (11 + 22)
         std::swap(Leptons.Lepton12, Leptons.Lepton22);
      else            // first pair should be 32 (21 + 12)
         std::swap(Leptons.Lepton11, Leptons.Lepton21);
   }

   return Leptons;
}
//----------------------------------------------------------------------------
FourVector ZALeptonVectors::GetTotal() const
{
   return Lepton1 + Lepton2 + Photon;
}
//----------------------------------------------------------------------------
FourVector &ZALeptonVectors::operator [](int index)
{
   switch(index)
   {
   case 0:
      return Photon;
   case 1:
      return Lepton1;
   case 2:
      return Lepton2;
   }

   return Photon;
}
//----------------------------------------------------------------------------
ZALeptonVectors ZALeptonVectors::ApplySmearing(ZACs Smearing) const
{
   ZALeptonVectors NewOne;
   NewOne.Photon = Photon * Smearing.c[0];
   NewOne.Lepton1 = Lepton1 * Smearing.c[1];
   NewOne.Lepton2 = Lepton2 * Smearing.c[2];
   return NewOne;
}
//----------------------------------------------------------------------------
ZALeptonVectors ZALeptonVectors::ApplyInverseSmearing(ZACs Smearing) const
{
   ZALeptonVectors NewOne;
   NewOne.Photon = Photon / Smearing.c[0];
   NewOne.Lepton1 = Lepton1 / Smearing.c[2];
   NewOne.Lepton2 = Lepton2 / Smearing.c[3];
   return NewOne;
}
//----------------------------------------------------------------------------
ZALeptonVectors ZALeptonVectors::GoToRest() const
{
   FourVector Total = GetTotal();
   double P = Total.GetP();
   double E = Total[0];

   ZALeptonVectors Result;
   Result.Lepton1 = Lepton1.Boost(-Total, P / E);
   Result.Lepton2 = Lepton2.Boost(-Total, P / E);
   Result.Photon = Photon.Boost(-Total, P / E);

   return Result;
}
//----------------------------------------------------------------------------
Cs::Cs()
{
   c[0] = 1, c[1] = 1, c[2] = 1, c[3] = 1;
}
//----------------------------------------------------------------------------
Cs::Cs(double c0, double c1, double c2, double c3)
{
   c[0] = c0, c[1] = c1, c[2] = c2, c[3] = c3;
}
//----------------------------------------------------------------------------
Cs Cs::Inverse()
{
   Cs NewOne;
   NewOne.c[0] = 1 / c[0];
   NewOne.c[1] = 1 / c[1];
   NewOne.c[2] = 1 / c[2];
   NewOne.c[3] = 1 / c[3];
   return NewOne;
}
//----------------------------------------------------------------------------
Cs Cs::operator *(Cs other)
{
   Cs NewOne;
   NewOne.c[0] = c[0] * other.c[0];
   NewOne.c[1] = c[1] * other.c[1];
   NewOne.c[2] = c[2] * other.c[2];
   NewOne.c[3] = c[3] * other.c[3];
   return NewOne;
}
//----------------------------------------------------------------------------
Cs Cs::operator /(Cs other)
{
   Cs NewOne;
   NewOne.c[0] = c[0] / other.c[0];
   NewOne.c[1] = c[1] / other.c[1];
   NewOne.c[2] = c[2] / other.c[2];
   NewOne.c[3] = c[3] / other.c[3];
   return NewOne;
}
//----------------------------------------------------------------------------
ZACs::ZACs()
{
   c[0] = 1, c[1] = 1, c[2] = 1;
}
//----------------------------------------------------------------------------
ZACs::ZACs(double c0, double c1, double c2)
{
   c[0] = c0, c[1] = c1, c[2] = c2;
}
//----------------------------------------------------------------------------
ZACs ZACs::Inverse()
{
   ZACs NewOne;
   NewOne.c[0] = 1 / c[0];
   NewOne.c[1] = 1 / c[1];
   NewOne.c[2] = 1 / c[2];
   return NewOne;
}
//----------------------------------------------------------------------------
ZACs ZACs::operator *(ZACs other)
{
   ZACs NewOne;
   NewOne.c[0] = c[0] * other.c[0];
   NewOne.c[1] = c[1] * other.c[1];
   NewOne.c[2] = c[2] * other.c[2];
   return NewOne;
}
//----------------------------------------------------------------------------
ZACs ZACs::operator /(ZACs other)
{
   ZACs NewOne;
   NewOne.c[0] = c[0] / other.c[0];
   NewOne.c[1] = c[1] / other.c[1];
   NewOne.c[2] = c[2] / other.c[2];
   return NewOne;
}
//----------------------------------------------------------------------------
void MultiplyFront(double A[3][3], double B[3][3])
{
   double C[3][3] = {{0}};

   for(int x = 0; x < 3; x++)
   {
      for(int y = 0; y < 3; y++)
      {
         C[x][y] = 0;
         for(int i = 0; i < 3; i++)
            C[x][y] = C[x][y] + B[x][i] * A[i][y];
      }
   }
   
   for(int x = 0; x < 3; x++)
      for(int y = 0; y < 3; y++)
         A[x][y] = C[x][y];
}
//----------------------------------------------------------------------------
void MultiplyFrontX(double A[3][3], double B[3][3])
{
   double C[3][3] = {{0}};

   for(int x = 1; x < 3; x++)
   {
      for(int y = 0; y < 3; y++)
      {
         C[x][y] = 0;
         for(int i = 1; i < 3; i++)
            C[x][y] = C[x][y] + B[x][i] * A[i][y];
      }
   }
   
   for(int x = 1; x < 3; x++)
      for(int y = 0; y < 3; y++)
         A[x][y] = C[x][y];
}
//----------------------------------------------------------------------------
void MultiplyFrontZ(double A[3][3], double B[3][3])
{
   double C[3][3] = {{0}};

   for(int x = 0; x < 2; x++)
   {
      for(int y = 0; y < 3; y++)
      {
         C[x][y] = 0;
         for(int i = 0; i < 2; i++)
            C[x][y] = C[x][y] + B[x][i] * A[i][y];
      }
   }
   
   for(int x = 0; x < 2; x++)
      for(int y = 0; y < 3; y++)
         A[x][y] = C[x][y];
}
//----------------------------------------------------------------------------
void TransformVector(double A[3][3], FourVector &V)
{
   double C[3] = {0};

   for(int x = 0; x < 3; x++)
   {
      C[x] = 0;
      for(int i = 0; i < 3; i++)
         C[x] = C[x] + A[x][i] * V.P[i+1];
   }

   for(int x = 0; x < 3; x++)
      V.P[x+1] = C[x];
}
//----------------------------------------------------------------------------
void MultiplyFront(double A[4][4], double B[4][4])
{
   double C[4][4] = {{0}};

   for(int x = 0; x < 4; x++)
   {
      for(int y = 0; y < 4; y++)
      {
         C[x][y] = 0;
         for(int i = 0; i < 4; i++)
            C[x][y] = C[x][y] + B[x][i] * A[i][y];
      }
   }
   
   for(int x = 0; x < 4; x++)
      for(int y = 0; y < 4; y++)
         A[x][y] = C[x][y];
}
//----------------------------------------------------------------------------
void MultiplyFrontTX(double A[4][4], double B[4][4])
{
   static const int I[2] = {2, 3};
   double C[4][4] = {{0}};

   for(int x = 0; x < 2; x++)
   {
      for(int y = 0; y < 4; y++)
      {
         C[I[x]][y] = 0;
         for(int i = 0; i < 2; i++)
            C[I[x]][y] = C[I[x]][y] + B[I[x]][I[i]] * A[I[i]][y];
      }
   }
   
   for(int x = 0; x < 2; x++)
      for(int y = 0; y < 4; y++)
         A[I[x]][y] = C[I[x]][y];
}
//----------------------------------------------------------------------------
void MultiplyFrontTY(double A[4][4], double B[4][4])
{
   static const int I[2] = {1, 3};
   double C[4][4] = {{0}};

   for(int x = 0; x < 2; x++)
   {
      for(int y = 0; y < 4; y++)
      {
         C[I[x]][y] = 0;
         for(int i = 0; i < 2; i++)
            C[I[x]][y] = C[I[x]][y] + B[I[x]][I[i]] * A[I[i]][y];
      }
   }
   
   for(int x = 0; x < 2; x++)
      for(int y = 0; y < 4; y++)
         A[I[x]][y] = C[I[x]][y];
}
//----------------------------------------------------------------------------
void MultiplyFrontTZ(double A[4][4], double B[4][4])
{
   static const int I[2] = {1, 2};
   double C[4][4] = {{0}};

   for(int x = 0; x < 2; x++)
   {
      for(int y = 0; y < 4; y++)
      {
         C[I[x]][y] = 0;
         for(int i = 0; i < 2; i++)
            C[I[x]][y] = C[I[x]][y] + B[I[x]][I[i]] * A[I[i]][y];
      }
   }
   
   for(int x = 0; x < 2; x++)
      for(int y = 0; y < 4; y++)
         A[I[x]][y] = C[I[x]][y];
}
//----------------------------------------------------------------------------
void MultiplyFrontXY(double A[4][4], double B[4][4])
{
   static const int I[2] = {0, 3};
   double C[4][4] = {{0}};

   for(int x = 0; x < 2; x++)
   {
      for(int y = 0; y < 4; y++)
      {
         C[I[x]][y] = 0;
         for(int i = 0; i < 2; i++)
            C[I[x]][y] = C[I[x]][y] + B[I[x]][I[i]] * A[I[i]][y];
      }
   }
   
   for(int x = 0; x < 2; x++)
      for(int y = 0; y < 4; y++)
         A[I[x]][y] = C[I[x]][y];
}
//----------------------------------------------------------------------------
void TransformVector(double A[4][4], FourVector &V)
{
   double C[4] = {0};

   for(int x = 0; x < 4; x++)
   {
      C[x] = 0;
      for(int i = 0; i < 4; i++)
         C[x] = C[x] + A[x][i] * V.P[i];
   }

   for(int x = 0; x < 4; x++)
      V.P[x] = C[x];
}
//----------------------------------------------------------------------------
double EventParametersDistance2(const EventParameters &P1, const EventParameters &P2)
{
   double DMH2 = (P1.HMass * P1.HMass - P2.HMass * P2.HMass) / 125 / 125;
   double DM12 = (P1.ZMass * P1.ZMass - P2.ZMass * P2.ZMass) / CONST_MZ / CONST_MZ;
   double DM22 = (P1.Z2Mass * P1.Z2Mass - P2.Z2Mass * P2.Z2Mass) / CONST_MZ / CONST_MZ;
   double DPhi0 = P1.Phi0 - P2.Phi0;
   double DTheta0 = cos(P1.Theta0) - cos(P2.Theta0);
   double DPhi = P1.Phi - P2.Phi;
   double DTheta1 = cos(P1.Theta1) - cos(P2.Theta1);
   double DTheta2 = cos(P1.Theta2) - cos(P2.Theta2);
   double DPhiOffset = P1.PhiOffset - P2.PhiOffset;
   double DPhiH = P1.PhiH - P2.PhiH;
   double DPTH = P1.PTH - P2.PTH;
   double DYH = P1.YH - P2.YH;

   if(DPhi0 < -PI)         DPhi0 = DPhi0 + 2 * PI;
   if(DPhi0 > PI)          DPhi0 = DPhi0 - 2 * PI;
   if(DPhi < -PI)          DPhi = DPhi + 2 * PI;
   if(DPhi > PI)           DPhi = DPhi - 2 * PI;
   if(DPhiOffset < -PI)    DPhiOffset = DPhiOffset + 2 * PI;
   if(DPhiOffset > PI)     DPhiOffset = DPhiOffset - 2 * PI;
   if(DPhiH < -PI)         DPhiH = DPhiH + 2 * PI;
   if(DPhiH > PI)          DPhiH = DPhiH - 2 * PI;

   /*
   std::cout << P1.HMass << " " << P2.HMass << std::endl;
   std::cout << DMH2 << " " << DM12 << " " << DM22 << " " << DPhi0 << " " << DTheta0
      << " " << DPhi << " " << DTheta1 << " " << DTheta2 << std::endl;
   */

   return DMH2 * DMH2 + DM12 * DM12 + DM22 * DM22 + DPhi0 * DPhi0
      + DTheta0 * DTheta0 + DPhi * DPhi + DTheta1 * DTheta1 + DTheta2 * DTheta2
      + DPhiOffset * DPhiOffset + DPhiH * DPhiH + DPTH * DPTH + DYH * DYH;
}
//----------------------------------------------------------------------------
double EventParametersDistance(const EventParameters &P1, const EventParameters &P2)
{
   return sqrt(EventParametersDistance2(P1, P2));
}
//----------------------------------------------------------------------------





