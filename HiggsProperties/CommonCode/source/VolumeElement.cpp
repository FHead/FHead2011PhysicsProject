#include <vector>
using namespace std;

#include "VolumeElement.h"

namespace VolumeElement
{
   double EstimateVolume(EventParameters C)
   {
      double Delta = 0.0001;
      double Factor = 0.01 / Delta;

      LeptonVectors VC = ConvertAnglesToVectorsRoberto(C);

      LeptonVectors V1 = VC;   V1.Lepton11 = V1.Lepton11 * (1 + Delta);
      LeptonVectors V2 = VC;   V2.Lepton12 = V2.Lepton12 * (1 + Delta);
      LeptonVectors V3 = VC;   V3.Lepton21 = V3.Lepton21 * (1 + Delta);
      LeptonVectors V4 = VC;   V4.Lepton22 = V4.Lepton22 * (1 + Delta);

      EventParameters X1 = ConvertVectorsToAnglesRoberto(V1);
      EventParameters X2 = ConvertVectorsToAnglesRoberto(V2);
      EventParameters X3 = ConvertVectorsToAnglesRoberto(V3);
      EventParameters X4 = ConvertVectorsToAnglesRoberto(V4);

      return GetVolume(C, X1, X2, X3, X4) * Factor * Factor * Factor * Factor;
   }

   double EstimateVolumeFull(EventParameters C)
   {
      double Delta = 0.000001;
      double Factor = 0.01 / Delta;

      LeptonVectors VC = ConvertAnglesToVectorsRoberto(C);

      LeptonVectors V1 = VC;   V1.Lepton11 = V1.Lepton11 * (1 + Delta);
      LeptonVectors V2 = VC;   V2.Lepton12 = V2.Lepton12 * (1 + Delta);
      LeptonVectors V3 = VC;   V3.Lepton21 = V3.Lepton21 * (1 + Delta);
      LeptonVectors V4 = VC;   V4.Lepton22 = V4.Lepton22 * (1 + Delta);

      FourVector P11_1, P11_2;   GetPerpendicular(VC.Lepton11, P11_1, P11_2);
      FourVector P12_1, P12_2;   GetPerpendicular(VC.Lepton12, P12_1, P12_2);
      FourVector P21_1, P21_2;   GetPerpendicular(VC.Lepton21, P21_1, P21_2);
      FourVector P22_1, P22_2;   GetPerpendicular(VC.Lepton22, P22_1, P22_2);

      LeptonVectors V5 = VC;    V5.Lepton11 = V5.Lepton11 + P11_1 * Delta * VC.Lepton11.GetP();
      LeptonVectors V6 = VC;    V6.Lepton11 = V6.Lepton11 + P11_2 * Delta * VC.Lepton11.GetP();
      LeptonVectors V7 = VC;    V7.Lepton12 = V7.Lepton12 + P12_1 * Delta * VC.Lepton12.GetP();
      LeptonVectors V8 = VC;    V8.Lepton12 = V8.Lepton12 + P12_2 * Delta * VC.Lepton12.GetP();
      LeptonVectors V9 = VC;    V9.Lepton21 = V9.Lepton21 + P21_1 * Delta * VC.Lepton21.GetP();
      LeptonVectors V10 = VC;   V10.Lepton21 = V10.Lepton21 + P21_2 * Delta * VC.Lepton21.GetP();
      LeptonVectors V11 = VC;   V11.Lepton22 = V11.Lepton22 + P22_1 * Delta * VC.Lepton22.GetP();
      LeptonVectors V12 = VC;   V12.Lepton22 = V12.Lepton22 + P22_2 * Delta * VC.Lepton22.GetP();

      V5.Lepton11[0] = V5.Lepton11.GetP();
      V6.Lepton11[0] = V6.Lepton11.GetP();
      V7.Lepton12[0] = V7.Lepton12.GetP();
      V8.Lepton12[0] = V8.Lepton12.GetP();
      V9.Lepton21[0] = V9.Lepton21.GetP();
      V10.Lepton21[0] = V10.Lepton21.GetP();
      V11.Lepton22[0] = V11.Lepton22.GetP();
      V12.Lepton22[0] = V12.Lepton22.GetP();

      EventParameters X1 = ConvertVectorsToAnglesRoberto(V1);
      EventParameters X2 = ConvertVectorsToAnglesRoberto(V2);
      EventParameters X3 = ConvertVectorsToAnglesRoberto(V3);
      EventParameters X4 = ConvertVectorsToAnglesRoberto(V4);
      EventParameters X5 = ConvertVectorsToAnglesRoberto(V5);
      EventParameters X6 = ConvertVectorsToAnglesRoberto(V6);
      EventParameters X7 = ConvertVectorsToAnglesRoberto(V7);
      EventParameters X8 = ConvertVectorsToAnglesRoberto(V8);
      EventParameters X9 = ConvertVectorsToAnglesRoberto(V9);
      EventParameters X10 = ConvertVectorsToAnglesRoberto(V10);
      EventParameters X11 = ConvertVectorsToAnglesRoberto(V11);
      EventParameters X12 = ConvertVectorsToAnglesRoberto(V12);

      return GetVolume(C, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12) * pow(Factor, 12)
         / VC.Lepton11.GetP() / VC.Lepton12.GetP() / VC.Lepton21.GetP() / VC.Lepton22.GetP()
         / VC.Lepton11.GetP() / VC.Lepton12.GetP() / VC.Lepton21.GetP() / VC.Lepton22.GetP()
         * 1e10;
   }

   double EstimateVolumeFull2(EventParameters C)
   {
      LeptonVectors VC = ConvertAnglesToVectorsRoberto(C);

      return EstimateVolumeFull5(C) * VC.Lepton11.GetP() * VC.Lepton12.GetP() * VC.Lepton21.GetP() * VC.Lepton22.GetP();
   }
   
   double EstimateVolumeFull3(EventParameters C)
   {
      double VolumeRatio = EstimateVolumeFull2(C);

      FourVector P4l;
      P4l.SetPtYPhiMass(C.PTH, C.YH, C.PhiH, C.HMass);
      double pz = P4l[3];
      double pt = P4l.GetPT();
      double p = P4l.GetP();
      double E = P4l[0];
      // double ExtraJacobian = pz * pz * p / (E * (E * E - pz * pz)) - E * p / (E * E - pz * pz);
      // ExtraJacobian = ExtraJacobian * p * p;
      // if(ExtraJacobian < 0)
      //    ExtraJacobian = -ExtraJacobian;
      // double ExtraJacobian = p * p * pt / E;
      double ExtraJacobian = E * pt / E;
      // double ExtraJacobian = p * pt * pz / (E * E - pz * pz) * p * pt;

      return VolumeRatio * ExtraJacobian;
   }

   double EstimateVolumeFull4(EventParameters C)
   {
      double VolumeRatio = EstimateVolumeFull2(C);

      FourVector P4l;
      P4l.SetPtYPhiMass(C.PTH, C.YH, C.PhiH, C.HMass);
      double pz = P4l[3];
      double pt = P4l.GetPT();
      double p = P4l.GetP();
      double E = P4l[0];
      // double ExtraJacobian = pz * pz * p / (E * (E * E - pz * pz)) - E * p / (E * E - pz * pz);
      // ExtraJacobian = ExtraJacobian * p * p;
      // if(ExtraJacobian < 0)
      //    ExtraJacobian = -ExtraJacobian;
      // double ExtraJacobian = p * p * pt / E;
      double ExtraJacobian = 1 / E;
      // double ExtraJacobian = p * pt * pz / (E * E - pz * pz) * p * pt;

      return VolumeRatio * ExtraJacobian;
   }

   double EstimateVolumeFull5(EventParameters C)
   {
      if(C.PTH < 1e-4)
         C.PTH = 1e-4;

      double Delta = 0.001;

      EventParameters X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12;

      X1 = C;    X1.HMass = C.HMass * sqrt(1 + Delta);
      X2 = C;    X2.ZMass = C.ZMass * sqrt(1 - Delta);
      X3 = C;    X3.Z2Mass = C.Z2Mass * sqrt(1 - Delta);
      X4 = C;    X4.Phi0 = C.Phi0 + Delta;
      X5 = C;    if(cos(C.Theta0) > 0)   X5.Theta0 = acos(cos(C.Theta0) - Delta);
                 else                    X5.Theta0 = acos(cos(C.Theta0) + Delta);
      X6 = C;    X6.Phi = C.Phi + Delta;
      X7 = C;    if(cos(C.Theta1) > 0)   X7.Theta1 = acos(cos(C.Theta1) - Delta);
                 else                    X7.Theta1 = acos(cos(C.Theta1) + Delta);
      X8 = C;    if(cos(C.Theta2) > 0)   X8.Theta2 = acos(cos(C.Theta2) - Delta);
                 else                    X8.Theta2 = acos(cos(C.Theta2) + Delta);
      X9 = C;    X9.YH = C.YH + Delta;
      X10 = C;   X10.PhiH = C.PhiH + Delta;
      X11 = C;   X11.PTH = C.PTH + Delta * C.HMass;
      X12 = C;   X12.PhiOffset = C.PhiOffset + Delta;

      LeptonVectors VC = ConvertAnglesToVectorsRoberto(C);
      LeptonVectors V1 = ConvertAnglesToVectorsRoberto(X1);
      LeptonVectors V2 = ConvertAnglesToVectorsRoberto(X2);
      LeptonVectors V3 = ConvertAnglesToVectorsRoberto(X3);
      LeptonVectors V4 = ConvertAnglesToVectorsRoberto(X4);
      LeptonVectors V5 = ConvertAnglesToVectorsRoberto(X5);
      LeptonVectors V6 = ConvertAnglesToVectorsRoberto(X6);
      LeptonVectors V7 = ConvertAnglesToVectorsRoberto(X7);
      LeptonVectors V8 = ConvertAnglesToVectorsRoberto(X8);
      LeptonVectors V9 = ConvertAnglesToVectorsRoberto(X9);
      LeptonVectors V10 = ConvertAnglesToVectorsRoberto(X10);
      LeptonVectors V11 = ConvertAnglesToVectorsRoberto(X11);
      LeptonVectors V12 = ConvertAnglesToVectorsRoberto(X12);

      FourVector D1 = VC.Lepton11.SpatialNormalize();
      FourVector D2 = VC.Lepton12.SpatialNormalize();
      FourVector D3 = VC.Lepton21.SpatialNormalize();
      FourVector D4 = VC.Lepton22.SpatialNormalize();
      FourVector P11_1, P11_2;   GetPerpendicular(VC.Lepton11, P11_1, P11_2);
      FourVector P12_1, P12_2;   GetPerpendicular(VC.Lepton12, P12_1, P12_2);
      FourVector P21_1, P21_2;   GetPerpendicular(VC.Lepton21, P21_1, P21_2);
      FourVector P22_1, P22_2;   GetPerpendicular(VC.Lepton22, P22_1, P22_2);

      vector<double> VVC = Vectorize(VC, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX1 = Vectorize(V1, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX2 = Vectorize(V2, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX3 = Vectorize(V3, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX4 = Vectorize(V4, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX5 = Vectorize(V5, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX6 = Vectorize(V6, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX7 = Vectorize(V7, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX8 = Vectorize(V8, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX9 = Vectorize(V9, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX10 = Vectorize(V10, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX11 = Vectorize(V11, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);
      vector<double> VX12 = Vectorize(V12, D1, P11_1, P11_2, D2, P12_1, P12_2, D3, P21_1, P21_2, D4, P22_1, P22_2);

      vector<double> VD1 = Difference(VX1, VVC);
      vector<double> VD2 = Difference(VX2, VVC);
      vector<double> VD3 = Difference(VX3, VVC);
      vector<double> VD4 = Difference(VX4, VVC);
      vector<double> VD5 = Difference(VX5, VVC);
      vector<double> VD6 = Difference(VX6, VVC);
      vector<double> VD7 = Difference(VX7, VVC);
      vector<double> VD8 = Difference(VX8, VVC);
      vector<double> VD9 = Difference(VX9, VVC);
      vector<double> VD10 = Difference(VX10, VVC);
      vector<double> VD11 = Difference(VX11, VVC);
      vector<double> VD12 = Difference(VX12, VVC);

      double L1 = Length(VD1);

      VD2 = SubtractOutParallel(VD2, VD1, L1 * L1);
      double L2 = Length(VD2);

      VD3 = SubtractOutParallel(VD3, VD1, L1 * L1);
      VD3 = SubtractOutParallel(VD3, VD2, L2 * L2);
      double L3 = Length(VD3);

      VD4 = SubtractOutParallel(VD4, VD1, L1 * L1);
      VD4 = SubtractOutParallel(VD4, VD2, L2 * L2);
      VD4 = SubtractOutParallel(VD4, VD3, L3 * L3);
      double L4 = Length(VD4);

      VD5 = SubtractOutParallel(VD5, VD1, L1 * L1);
      VD5 = SubtractOutParallel(VD5, VD2, L2 * L2);
      VD5 = SubtractOutParallel(VD5, VD3, L3 * L3);
      VD5 = SubtractOutParallel(VD5, VD4, L4 * L4);
      double L5 = Length(VD5);

      VD6 = SubtractOutParallel(VD6, VD1, L1 * L1);
      VD6 = SubtractOutParallel(VD6, VD2, L2 * L2);
      VD6 = SubtractOutParallel(VD6, VD3, L3 * L3);
      VD6 = SubtractOutParallel(VD6, VD4, L4 * L4);
      VD6 = SubtractOutParallel(VD6, VD5, L5 * L5);
      double L6 = Length(VD6);

      VD7 = SubtractOutParallel(VD7, VD1, L1 * L1);
      VD7 = SubtractOutParallel(VD7, VD2, L2 * L2);
      VD7 = SubtractOutParallel(VD7, VD3, L3 * L3);
      VD7 = SubtractOutParallel(VD7, VD4, L4 * L4);
      VD7 = SubtractOutParallel(VD7, VD5, L5 * L5);
      VD7 = SubtractOutParallel(VD7, VD6, L6 * L6);
      double L7 = Length(VD7);

      VD8 = SubtractOutParallel(VD8, VD1, L1 * L1);
      VD8 = SubtractOutParallel(VD8, VD2, L2 * L2);
      VD8 = SubtractOutParallel(VD8, VD3, L3 * L3);
      VD8 = SubtractOutParallel(VD8, VD4, L4 * L4);
      VD8 = SubtractOutParallel(VD8, VD5, L5 * L5);
      VD8 = SubtractOutParallel(VD8, VD6, L6 * L6);
      VD8 = SubtractOutParallel(VD8, VD7, L7 * L7);
      double L8 = Length(VD8);

      VD9 = SubtractOutParallel(VD9, VD1, L1 * L1);
      VD9 = SubtractOutParallel(VD9, VD2, L2 * L2);
      VD9 = SubtractOutParallel(VD9, VD3, L3 * L3);
      VD9 = SubtractOutParallel(VD9, VD4, L4 * L4);
      VD9 = SubtractOutParallel(VD9, VD5, L5 * L5);
      VD9 = SubtractOutParallel(VD9, VD6, L6 * L6);
      VD9 = SubtractOutParallel(VD9, VD7, L7 * L7);
      VD9 = SubtractOutParallel(VD9, VD8, L8 * L8);
      double L9 = Length(VD9);

      VD10 = SubtractOutParallel(VD10, VD1, L1 * L1);
      VD10 = SubtractOutParallel(VD10, VD2, L2 * L2);
      VD10 = SubtractOutParallel(VD10, VD3, L3 * L3);
      VD10 = SubtractOutParallel(VD10, VD4, L4 * L4);
      VD10 = SubtractOutParallel(VD10, VD5, L5 * L5);
      VD10 = SubtractOutParallel(VD10, VD6, L6 * L6);
      VD10 = SubtractOutParallel(VD10, VD7, L7 * L7);
      VD10 = SubtractOutParallel(VD10, VD8, L8 * L8);
      VD10 = SubtractOutParallel(VD10, VD9, L9 * L9);
      double L10 = Length(VD10);

      VD11 = SubtractOutParallel(VD11, VD1, L1 * L1);
      VD11 = SubtractOutParallel(VD11, VD2, L2 * L2);
      VD11 = SubtractOutParallel(VD11, VD3, L3 * L3);
      VD11 = SubtractOutParallel(VD11, VD4, L4 * L4);
      VD11 = SubtractOutParallel(VD11, VD5, L5 * L5);
      VD11 = SubtractOutParallel(VD11, VD6, L6 * L6);
      VD11 = SubtractOutParallel(VD11, VD7, L7 * L7);
      VD11 = SubtractOutParallel(VD11, VD8, L8 * L8);
      VD11 = SubtractOutParallel(VD11, VD9, L9 * L9);
      VD11 = SubtractOutParallel(VD11, VD10, L10 * L10);
      double L11 = Length(VD11);

      VD12 = SubtractOutParallel(VD12, VD1, L1 * L1);
      VD12 = SubtractOutParallel(VD12, VD2, L2 * L2);
      VD12 = SubtractOutParallel(VD12, VD3, L3 * L3);
      VD12 = SubtractOutParallel(VD12, VD4, L4 * L4);
      VD12 = SubtractOutParallel(VD12, VD5, L5 * L5);
      VD12 = SubtractOutParallel(VD12, VD6, L6 * L6);
      VD12 = SubtractOutParallel(VD12, VD7, L7 * L7);
      VD12 = SubtractOutParallel(VD12, VD8, L8 * L8);
      VD12 = SubtractOutParallel(VD12, VD9, L9 * L9);
      VD12 = SubtractOutParallel(VD12, VD10, L10 * L10);
      VD12 = SubtractOutParallel(VD12, VD11, L11 * L11);
      double L12 = Length(VD12);

      double Volume = L1 * L2 * L3 * L4 * L5 * L6 * L7 * L8 * L9 * L10 * L11 * L12;
      double EVolume = pow(Delta, 12) * C.HMass * C.HMass * C.HMass * C.ZMass * C.ZMass * C.Z2Mass * C.Z2Mass;

      return EVolume / Volume;
   }
 
   double EstimateVolumeFull5(ZAEventParameters C)
   {
      if(C.PTH < 1e-4)
         C.PTH = 1e-4;

      double Delta = 0.001;

      ZAEventParameters X1, X2, X3, X4, X5, X6, X7, X8, X9;

      X1 = C;    X1.HMass = C.HMass * sqrt(1 + Delta);
      X2 = C;    X2.ZMass = C.ZMass * sqrt(1 - Delta);
      X3 = C;    X3.Phi0 = C.Phi0 + Delta;
      X4 = C;    if(cos(C.Theta0) > 0)    X4.Theta0 = acos(cos(C.Theta0) - Delta);
                 else                     X4.Theta0 = acos(cos(C.Theta0) + Delta);
      X5 = C;    if(cos(C.ThetaLL) > 0)   X5.ThetaLL = acos(cos(C.ThetaLL) - Delta);
                 else                     X5.ThetaLL = acos(cos(C.ThetaLL) + Delta);
      X6 = C;    X6.YH = C.YH + Delta;
      X7 = C;    X7.PhiH = C.PhiH + Delta;
      X8 = C;    X8.PTH = C.PTH + Delta * C.HMass;
      X9 = C;    X9.PhiOffset = C.PhiOffset + Delta;

      ZALeptonVectors VC = ConvertAnglesToVectorsRoberto(C);
      ZALeptonVectors V1 = ConvertAnglesToVectorsRoberto(X1);
      ZALeptonVectors V2 = ConvertAnglesToVectorsRoberto(X2);
      ZALeptonVectors V3 = ConvertAnglesToVectorsRoberto(X3);
      ZALeptonVectors V4 = ConvertAnglesToVectorsRoberto(X4);
      ZALeptonVectors V5 = ConvertAnglesToVectorsRoberto(X5);
      ZALeptonVectors V6 = ConvertAnglesToVectorsRoberto(X6);
      ZALeptonVectors V7 = ConvertAnglesToVectorsRoberto(X7);
      ZALeptonVectors V8 = ConvertAnglesToVectorsRoberto(X8);
      ZALeptonVectors V9 = ConvertAnglesToVectorsRoberto(X9);

      FourVector D1 = VC.Lepton1.SpatialNormalize();
      FourVector D2 = VC.Lepton2.SpatialNormalize();
      FourVector DP = VC.Photon.SpatialNormalize();
      FourVector P1_1, P1_2;   GetPerpendicular(VC.Lepton1, P1_1, P1_2);
      FourVector P2_1, P2_2;   GetPerpendicular(VC.Lepton2, P2_1, P2_2);
      FourVector PP_1, PP_2;   GetPerpendicular(VC.Photon, PP_1, PP_2);

      vector<double> VVC = Vectorize9(VC, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);
      vector<double> VX1 = Vectorize9(V1, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);
      vector<double> VX2 = Vectorize9(V2, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);
      vector<double> VX3 = Vectorize9(V3, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);
      vector<double> VX4 = Vectorize9(V4, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);
      vector<double> VX5 = Vectorize9(V5, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);
      vector<double> VX6 = Vectorize9(V6, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);
      vector<double> VX7 = Vectorize9(V7, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);
      vector<double> VX8 = Vectorize9(V8, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);
      vector<double> VX9 = Vectorize9(V9, D1, P1_1, P1_2, D2, P2_1, P2_2, DP, PP_1, PP_2);

      vector<double> VD1 = Difference9(VX1, VVC);
      vector<double> VD2 = Difference9(VX2, VVC);
      vector<double> VD3 = Difference9(VX3, VVC);
      vector<double> VD4 = Difference9(VX4, VVC);
      vector<double> VD5 = Difference9(VX5, VVC);
      vector<double> VD6 = Difference9(VX6, VVC);
      vector<double> VD7 = Difference9(VX7, VVC);
      vector<double> VD8 = Difference9(VX8, VVC);
      vector<double> VD9 = Difference9(VX9, VVC);

      double L1 = Length(VD1);

      VD2 = SubtractOutParallel9(VD2, VD1, L1 * L1);
      double L2 = Length(VD2);

      VD3 = SubtractOutParallel9(VD3, VD1, L1 * L1);
      VD3 = SubtractOutParallel9(VD3, VD2, L2 * L2);
      double L3 = Length(VD3);

      VD4 = SubtractOutParallel9(VD4, VD1, L1 * L1);
      VD4 = SubtractOutParallel9(VD4, VD2, L2 * L2);
      VD4 = SubtractOutParallel9(VD4, VD3, L3 * L3);
      double L4 = Length(VD4);

      VD5 = SubtractOutParallel9(VD5, VD1, L1 * L1);
      VD5 = SubtractOutParallel9(VD5, VD2, L2 * L2);
      VD5 = SubtractOutParallel9(VD5, VD3, L3 * L3);
      VD5 = SubtractOutParallel9(VD5, VD4, L4 * L4);
      double L5 = Length(VD5);

      VD6 = SubtractOutParallel9(VD6, VD1, L1 * L1);
      VD6 = SubtractOutParallel9(VD6, VD2, L2 * L2);
      VD6 = SubtractOutParallel9(VD6, VD3, L3 * L3);
      VD6 = SubtractOutParallel9(VD6, VD4, L4 * L4);
      VD6 = SubtractOutParallel9(VD6, VD5, L5 * L5);
      double L6 = Length(VD6);

      VD7 = SubtractOutParallel9(VD7, VD1, L1 * L1);
      VD7 = SubtractOutParallel9(VD7, VD2, L2 * L2);
      VD7 = SubtractOutParallel9(VD7, VD3, L3 * L3);
      VD7 = SubtractOutParallel9(VD7, VD4, L4 * L4);
      VD7 = SubtractOutParallel9(VD7, VD5, L5 * L5);
      VD7 = SubtractOutParallel9(VD7, VD6, L6 * L6);
      double L7 = Length(VD7);

      VD8 = SubtractOutParallel9(VD8, VD1, L1 * L1);
      VD8 = SubtractOutParallel9(VD8, VD2, L2 * L2);
      VD8 = SubtractOutParallel9(VD8, VD3, L3 * L3);
      VD8 = SubtractOutParallel9(VD8, VD4, L4 * L4);
      VD8 = SubtractOutParallel9(VD8, VD5, L5 * L5);
      VD8 = SubtractOutParallel9(VD8, VD6, L6 * L6);
      VD8 = SubtractOutParallel9(VD8, VD7, L7 * L7);
      double L8 = Length(VD8);

      VD9 = SubtractOutParallel9(VD9, VD1, L1 * L1);
      VD9 = SubtractOutParallel9(VD9, VD2, L2 * L2);
      VD9 = SubtractOutParallel9(VD9, VD3, L3 * L3);
      VD9 = SubtractOutParallel9(VD9, VD4, L4 * L4);
      VD9 = SubtractOutParallel9(VD9, VD5, L5 * L5);
      VD9 = SubtractOutParallel9(VD9, VD6, L6 * L6);
      VD9 = SubtractOutParallel9(VD9, VD7, L7 * L7);
      VD9 = SubtractOutParallel9(VD9, VD8, L8 * L8);
      double L9 = Length(VD9);

      double Volume = L1 * L2 * L3 * L4 * L5 * L6 * L7 * L8 * L9;
      double EVolume = pow(Delta, 9) * C.HMass * C.HMass * C.HMass * C.ZMass * C.ZMass;

      return EVolume / Volume;
   }

   double EstimateVolumeFull6(EventParameters C)
   {
      double VolumeRatio = EstimateVolumeFull5(C);

      FourVector P4l;
      P4l.SetPtYPhiMass(C.PTH, C.YH, C.PhiH, C.HMass);
      double pz = P4l[3];
      double pt = P4l.GetPT();
      double p = P4l.GetP();
      double E = P4l[0];
      double ExtraJacobian = 1 / E;

      return VolumeRatio * ExtraJacobian;
   }

   double EstimateVolumeFull7(EventParameters C)
   {
      double VolumeRatio = EstimateVolumeFull5(C);

      FourVector P4l;
      P4l.SetPtYPhiMass(C.PTH, C.YH, C.PhiH, C.HMass);
      double pz = P4l[3];
      double pt = P4l.GetPT();
      double p = P4l.GetP();
      double E = P4l[0];
      double ExtraJacobian = 1 / pt;

      return VolumeRatio * ExtraJacobian;
   }

   double EstimateVolumeFull7(ZAEventParameters C)
   {
      double VolumeRatio = EstimateVolumeFull5(C);

      FourVector P4l;
      P4l.SetPtYPhiMass(C.PTH, C.YH, C.PhiH, C.HMass);
      double pz = P4l[3];
      double pt = P4l.GetPT();
      double p = P4l.GetP();
      double E = P4l[0];
      double ExtraJacobian = 1 / pt;

      return VolumeRatio * ExtraJacobian;
   }

   double GetVolume(EventParameters C, EventParameters X1, EventParameters X2, EventParameters X3, EventParameters X4)
   {
      vector<double> VC = Vectorize(C);
      vector<double> VX1 = Vectorize(X1);
      vector<double> VX2 = Vectorize(X2);
      vector<double> VX3 = Vectorize(X3);
      vector<double> VX4 = Vectorize(X4);

      PhiShifter(VC, VX1, VX2, VX3, VX4);

      vector<double> V1 = Difference(VX1, VC);
      vector<double> V2 = Difference(VX2, VC);
      vector<double> V3 = Difference(VX3, VC);
      vector<double> V4 = Difference(VX4, VC);

      V2 = SubtractOutParallel(V2, V1);
      V3 = SubtractOutParallel(V3, V1);
      V3 = SubtractOutParallel(V3, V2);
      V4 = SubtractOutParallel(V4, V1);
      V4 = SubtractOutParallel(V4, V2);
      V4 = SubtractOutParallel(V4, V3);

      double L1 = Length(V1);
      double L2 = Length(V2);
      double L3 = Length(V3);
      double L4 = Length(V4);

      return L1 * L2 * L3 * L4;
   }

   double GetVolume(EventParameters C,
      EventParameters X1, EventParameters X2, EventParameters X3, EventParameters X4,
      EventParameters X5, EventParameters X6, EventParameters X7, EventParameters X8,
      EventParameters X9, EventParameters X10, EventParameters X11, EventParameters X12)
   {
      vector<double> VC = Vectorize(C);
      vector<double> VX1 = Vectorize(X1);
      vector<double> VX2 = Vectorize(X2);
      vector<double> VX3 = Vectorize(X3);
      vector<double> VX4 = Vectorize(X4);
      vector<double> VX5 = Vectorize(X5);
      vector<double> VX6 = Vectorize(X6);
      vector<double> VX7 = Vectorize(X7);
      vector<double> VX8 = Vectorize(X8);
      vector<double> VX9 = Vectorize(X9);
      vector<double> VX10 = Vectorize(X10);
      vector<double> VX11 = Vectorize(X11);
      vector<double> VX12 = Vectorize(X12);

      vector<double> VCTemp = VC;
      PhiShifter(VC, VX1, VX2, VX3, VX4);
      VC = VCTemp;
      PhiShifter(VC, VX5, VX6, VX7, VX8);
      VC = VCTemp;
      PhiShifter(VC, VX9, VX10, VX11, VX12);

      vector<double> V1 = Difference(VX1, VC);
      vector<double> V2 = Difference(VX2, VC);
      vector<double> V3 = Difference(VX3, VC);
      vector<double> V4 = Difference(VX4, VC);
      vector<double> V5 = Difference(VX5, VC);
      vector<double> V6 = Difference(VX6, VC);
      vector<double> V7 = Difference(VX7, VC);
      vector<double> V8 = Difference(VX8, VC);
      vector<double> V9 = Difference(VX9, VC);
      vector<double> V10 = Difference(VX10, VC);
      vector<double> V11 = Difference(VX11, VC);
      vector<double> V12 = Difference(VX12, VC);

      V2 = SubtractOutParallel(V2, V1);

      V3 = SubtractOutParallel(V3, V1);
      V3 = SubtractOutParallel(V3, V2);

      V4 = SubtractOutParallel(V4, V1);
      V4 = SubtractOutParallel(V4, V2);
      V4 = SubtractOutParallel(V4, V3);

      V5 = SubtractOutParallel(V5, V1);
      V5 = SubtractOutParallel(V5, V2);
      V5 = SubtractOutParallel(V5, V3);
      V5 = SubtractOutParallel(V5, V4);

      V6 = SubtractOutParallel(V6, V1);
      V6 = SubtractOutParallel(V6, V2);
      V6 = SubtractOutParallel(V6, V3);
      V6 = SubtractOutParallel(V6, V4);
      V6 = SubtractOutParallel(V6, V5);

      V7 = SubtractOutParallel(V7, V1);
      V7 = SubtractOutParallel(V7, V2);
      V7 = SubtractOutParallel(V7, V3);
      V7 = SubtractOutParallel(V7, V4);
      V7 = SubtractOutParallel(V7, V5);
      V7 = SubtractOutParallel(V7, V6);

      V8 = SubtractOutParallel(V8, V1);
      V8 = SubtractOutParallel(V8, V2);
      V8 = SubtractOutParallel(V8, V3);
      V8 = SubtractOutParallel(V8, V4);
      V8 = SubtractOutParallel(V8, V5);
      V8 = SubtractOutParallel(V8, V6);
      V8 = SubtractOutParallel(V8, V7);

      V9 = SubtractOutParallel(V9, V1);
      V9 = SubtractOutParallel(V9, V2);
      V9 = SubtractOutParallel(V9, V3);
      V9 = SubtractOutParallel(V9, V4);
      V9 = SubtractOutParallel(V9, V5);
      V9 = SubtractOutParallel(V9, V6);
      V9 = SubtractOutParallel(V9, V7);
      V9 = SubtractOutParallel(V9, V8);

      V10 = SubtractOutParallel(V10, V1);
      V10 = SubtractOutParallel(V10, V2);
      V10 = SubtractOutParallel(V10, V3);
      V10 = SubtractOutParallel(V10, V4);
      V10 = SubtractOutParallel(V10, V5);
      V10 = SubtractOutParallel(V10, V6);
      V10 = SubtractOutParallel(V10, V7);
      V10 = SubtractOutParallel(V10, V8);
      V10 = SubtractOutParallel(V10, V9);

      V11 = SubtractOutParallel(V11, V1);
      V11 = SubtractOutParallel(V11, V2);
      V11 = SubtractOutParallel(V11, V3);
      V11 = SubtractOutParallel(V11, V4);
      V11 = SubtractOutParallel(V11, V5);
      V11 = SubtractOutParallel(V11, V6);
      V11 = SubtractOutParallel(V11, V7);
      V11 = SubtractOutParallel(V11, V8);
      V11 = SubtractOutParallel(V11, V9);
      V11 = SubtractOutParallel(V11, V10);

      V12 = SubtractOutParallel(V12, V1);
      V12 = SubtractOutParallel(V12, V2);
      V12 = SubtractOutParallel(V12, V3);
      V12 = SubtractOutParallel(V12, V4);
      V12 = SubtractOutParallel(V12, V5);
      V12 = SubtractOutParallel(V12, V6);
      V12 = SubtractOutParallel(V12, V7);
      V12 = SubtractOutParallel(V12, V8);
      V12 = SubtractOutParallel(V12, V9);
      V12 = SubtractOutParallel(V12, V10);
      V12 = SubtractOutParallel(V12, V11);

      double L1 = Length(V1);
      double L2 = Length(V2);
      double L3 = Length(V3);
      double L4 = Length(V4);
      double L5 = Length(V5);
      double L6 = Length(V6);
      double L7 = Length(V7);
      double L8 = Length(V8);
      double L9 = Length(V9);
      double L10 = Length(V10);
      double L11 = Length(V11);
      double L12 = Length(V12);

      double Volume = L1 * L2 * L3 * L4 * L5 * L6 * L7 * L8 * L9 * L10 * L11 * L12;

      return Volume;
   }

   vector<double> Vectorize(EventParameters E)
   {
      vector<double> Result(12);

      Result[0] = E.HMass * E.HMass;
      Result[1] = E.ZMass * E.ZMass;
      Result[2] = E.Z2Mass * E.Z2Mass;
      Result[3] = E.Phi0;
      Result[4] = cos(E.Theta0);
      Result[5] = E.Phi;
      Result[6] = cos(E.Theta1);
      Result[7] = cos(E.Theta2);
      Result[8] = E.PTH;
      Result[9] = E.YH;
      Result[10] = E.PhiH;
      Result[11] = E.PhiOffset;

      return Result;
   }

   void PhiShifter(vector<double> &C, vector<double> &X1, vector<double> &X2, vector<double> &X3, vector<double> &X4)
   {
      double Phi0Shift = C[3];
      double PhiShift = C[5];
      double PhiHShift = C[10];
      double PhiOffsetShift = C[11];

      C[3] = C[3] - Phi0Shift;
      C[5] = C[5] - PhiShift;
      C[10] = C[10] - PhiHShift;
      C[11] = C[11] - PhiOffsetShift;

      X1[3] = X1[3] - Phi0Shift;
      X1[5] = X1[5] - PhiShift;
      X1[10] = X1[10] - PhiHShift;
      X1[11] = X1[11] - PhiOffsetShift;

      X2[3] = X2[3] - Phi0Shift;
      X2[5] = X2[5] - PhiShift;
      X2[10] = X2[10] - PhiHShift;
      X2[11] = X2[11] - PhiOffsetShift;

      X3[3] = X3[3] - Phi0Shift;
      X3[5] = X3[5] - PhiShift;
      X3[10] = X3[10] - PhiHShift;
      X3[11] = X3[11] - PhiOffsetShift;

      X4[3] = X4[3] - Phi0Shift;
      X4[5] = X4[5] - PhiShift;
      X4[10] = X4[10] - PhiHShift;
      X4[11] = X4[11] - PhiOffsetShift;
   }

   vector<double> Difference(const vector<double> &V1, const vector<double> &V2, double C)
   {
      vector<double> V(V1.size());
      for(int i = 0; i < 12; i++)
         V[i] = V1[i] - V2[i] * C;
      return V;
   }

   vector<double> Difference9(const vector<double> &V1, const vector<double> &V2, double C)
   {
      vector<double> V(V1.size());
      for(int i = 0; i < 9; i++)
         V[i] = V1[i] - V2[i] * C;
      return V;
   }

   double Dot(const vector<double> &V1, const vector<double> &V2)
   {
      double Answer = 0;
      for(int i = 0; i < 12; i++)
         Answer = Answer + V1[i] * V2[i];
      return Answer;
   }

   double Dot9(const vector<double> &V1, const vector<double> &V2)
   {
      double Answer = 0;
      for(int i = 0; i < 9; i++)
         Answer = Answer + V1[i] * V2[i];
      return Answer;
   }

   double Length(const vector<double> &V)
   {
      return sqrt(Dot(V, V));
   }

   double CosAngle(const vector<double> &V1, const vector<double> &V2)
   {
      return Dot(V1, V2) / Length(V1) / Length(V2);
   }

   double ProjectionSize(const vector<double> &Vector, const vector<double> &ProjectionVector)
   {
      return Dot(Vector, ProjectionVector) / Length(ProjectionVector);
   }

   vector<double> SubtractOutParallel(const vector<double> &Vector, const vector<double> &ProjectionVector, double ProjectionSize2)
   {
      if(ProjectionSize2 <= 0)
         ProjectionSize2 = Dot(ProjectionVector, ProjectionVector);
      return Difference(Vector, ProjectionVector, Dot(Vector, ProjectionVector) / ProjectionSize2);
   }

   vector<double> SubtractOutParallel9(const vector<double> &Vector, const vector<double> &ProjectionVector, double ProjectionSize2)
   {
      if(ProjectionSize2 <= 0)
         ProjectionSize2 = Dot9(ProjectionVector, ProjectionVector);
      return Difference9(Vector, ProjectionVector, Dot9(Vector, ProjectionVector) / ProjectionSize2);
   }

   void GetPerpendicular(const FourVector &Main, FourVector &P1, FourVector &P2, double MixingOffset)
   {
      FourVector V1(1, 1, 0, 0);   V1 = V1.SpatialNormalize();
      FourVector V2(1, 0, 1, 0);   V2 = V2.SpatialNormalize();
      FourVector V3(1, 0, 0, 1);   V3 = V3.SpatialNormalize();

      V1 = V1 - Main * V1.SpatialDot(Main) / Main.SpatialDot(Main);
      V2 = V2 - Main * V2.SpatialDot(Main) / Main.SpatialDot(Main);
      V3 = V3 - Main * V3.SpatialDot(Main) / Main.SpatialDot(Main);

      double S1 = V1.SpatialDot(V1);
      double S2 = V2.SpatialDot(V2);
      double S3 = V3.SpatialDot(V3);

      FourVector O1, O2;

      if(S1 > S2 && S1 > S3)
         O1 = V1;
      else if(S2 > S3)
         O1 = V2;
      else
         O1 = V3;

      O2 = O1.SpatialCross(Main);

      O1 = O1 / O1.GetP();
      O2 = O2 / O2.GetP();

      // std::cout << O1.SpatialDot(O2) << std::endl;
      // std::cout << Main << std::endl;
      // std::cout << O1 << " " << O2 << std::endl;

      P1 = O1 * cos(MixingOffset) + O2 * sin(MixingOffset);
      P2 = -O1 * sin(MixingOffset) + O2 * cos(MixingOffset);
   }

   void VectorDecompose(FourVector P, FourVector D1, FourVector D2, FourVector D3,
      double &A1, double &A2, double &A3)
   {
      A1 = P.SpatialDot(D1) / D1.GetP();
      A2 = P.SpatialDot(D2) / D2.GetP();
      A3 = P.SpatialDot(D3) / D3.GetP();
   }

   std::vector<double> Vectorize(LeptonVectors E,
      FourVector D11, FourVector P11_1, FourVector P11_2,
      FourVector D12, FourVector P12_1, FourVector P12_2,
      FourVector D21, FourVector P21_1, FourVector P21_2,
      FourVector D22, FourVector P22_1, FourVector P22_2)
   {
      std::vector<double> Result(12);

      Result[0] = E.Lepton11.SpatialDot(D11) / D11.GetP();
      Result[1] = E.Lepton11.SpatialDot(P11_1) / P11_1.GetP();
      Result[2] = E.Lepton11.SpatialDot(P11_2) / P11_2.GetP();
      Result[3] = E.Lepton12.SpatialDot(D12) / D12.GetP();
      Result[4] = E.Lepton12.SpatialDot(P12_1) / P12_1.GetP();
      Result[5] = E.Lepton12.SpatialDot(P12_2) / P12_2.GetP();
      Result[6] = E.Lepton21.SpatialDot(D21) / D21.GetP();
      Result[7] = E.Lepton21.SpatialDot(P21_1) / P21_1.GetP();
      Result[8] = E.Lepton21.SpatialDot(P21_2) / P21_2.GetP();
      Result[9] = E.Lepton22.SpatialDot(D22) / D22.GetP();
      Result[10] = E.Lepton22.SpatialDot(P22_1) / P22_1.GetP();
      Result[11] = E.Lepton22.SpatialDot(P22_2) / P22_2.GetP();

      return Result;
   }
   
   std::vector<double> Vectorize9(ZALeptonVectors E,
      FourVector D1, FourVector P1_1, FourVector P1_2,
      FourVector D2, FourVector P2_1, FourVector P2_2,
      FourVector DP, FourVector PP_1, FourVector PP_2)
   {
      std::vector<double> Result(9);

      Result[0] = E.Lepton1.SpatialDot(D1) / D1.GetP();
      Result[1] = E.Lepton1.SpatialDot(P1_1) / P1_1.GetP();
      Result[2] = E.Lepton1.SpatialDot(P1_2) / P1_2.GetP();
      Result[3] = E.Lepton2.SpatialDot(D2) / D2.GetP();
      Result[4] = E.Lepton2.SpatialDot(P2_1) / P2_1.GetP();
      Result[5] = E.Lepton2.SpatialDot(P2_2) / P2_2.GetP();
      Result[6] = E.Photon.SpatialDot(DP) / DP.GetP();
      Result[7] = E.Photon.SpatialDot(PP_1) / PP_1.GetP();
      Result[8] = E.Photon.SpatialDot(PP_2) / PP_2.GetP();

      return Result;
   }
}




