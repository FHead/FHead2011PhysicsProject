#include <vector>

#include "AngleConversion.h"

namespace VolumeElement
{
   double EstimateVolume(EventParameters C);
   double EstimateVolumeFull(EventParameters C);
   double EstimateVolumeFull2(EventParameters C);
   double EstimateVolumeFull3(EventParameters C);
   double EstimateVolumeFull4(EventParameters C);
   double EstimateVolumeFull5(EventParameters C);
   double EstimateVolumeFull5(ZAEventParameters C);
   double EstimateVolumeFull6(EventParameters C);
   double EstimateVolumeFull7(EventParameters C);
   double EstimateVolumeFull7(ZAEventParameters C);
   double GetVolume(EventParameters C, EventParameters X1, EventParameters X2,
      EventParameters X3, EventParameters X4);
   double GetVolume(EventParameters C,
      EventParameters X1, EventParameters X2, EventParameters X3, EventParameters X4,
      EventParameters X5, EventParameters X6, EventParameters X7, EventParameters X8,
      EventParameters X9, EventParameters X10, EventParameters X11, EventParameters X12);
   std::vector<double> Vectorize(EventParameters E);
   void PhiShifter(std::vector<double> &C, std::vector<double> &X1, std::vector<double> &X2,
      std::vector<double> &X3, std::vector<double> &X4);
   std::vector<double> Difference(const std::vector<double> &V1, const std::vector<double> &V2, double C = 1);
   std::vector<double> Difference9(const std::vector<double> &V1, const std::vector<double> &V2, double C = 1);
   double Dot(const std::vector<double> &V1, const std::vector<double> &V2);
   double Dot9(const std::vector<double> &V1, const std::vector<double> &V2);
   double Length(const std::vector<double> &V);
   double CosAngle(const std::vector<double> &V1, const std::vector<double> &V2);
   double ProjectionSize(const std::vector<double> &Vector, const std::vector<double> &ProjectionVector);
   std::vector<double> SubtractOutParallel(const std::vector<double> &Vector, const std::vector<double> &ProjectionVector, double ProjectionSize2 = -1);
   std::vector<double> SubtractOutParallel9(const std::vector<double> &Vector, const std::vector<double> &ProjectionVector, double ProjectionSize2 = -1);
   void GetPerpendicular(const FourVector &Main, FourVector &P1, FourVector &P2, double MixingOffset = 0.8);
   void VectorDecompose(FourVector P, FourVector D1, FourVector D2, FourVector D3,
      double &A1, double &A2, double &A3);
   std::vector<double> Vectorize(LeptonVectors E,
      FourVector D11, FourVector P11_1, FourVector P11_2,
      FourVector D12, FourVector P12_1, FourVector P12_2,
      FourVector D21, FourVector P21_1, FourVector P21_2,
      FourVector D22, FourVector P22_1, FourVector P22_2);
   std::vector<double> Vectorize9(ZALeptonVectors E,
      FourVector D1, FourVector P1_1, FourVector P1_2,
      FourVector D2, FourVector P2_1, FourVector P2_2,
      FourVector DP, FourVector PP_1, FourVector PP_2);
}

