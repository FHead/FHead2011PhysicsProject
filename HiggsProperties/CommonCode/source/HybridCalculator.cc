//----------------------------------------------------------------------------
// Calculation of the hybrid method.  Result is proportional to pdf value.
// Author: Yi Chen (11662)
//----------------------------------------------------------------------------
#include "HybridCalculator.h"
//----------------------------------------------------------------------------
HybridCalculator::HybridCalculator()
{
   Efficiency12 = NULL;
   Efficiency34 = NULL;
   Smear12 = NULL;
   Smear34 = NULL;
}
//----------------------------------------------------------------------------
HybridCalculator::~HybridCalculator()
{
}
//----------------------------------------------------------------------------
void HybridCalculator::SetEfficiency12(double (*F)(double, double, double))
{
   Efficiency12 = F;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetEfficiency34(double (*F)(double, double, double))
{
   Efficiency34 = F;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetSmear12(double (*F)(const FourVector &, double))
{
   Smear12 = F;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetSmear34(double (*F)(const FourVector &, double))
{
   Smear34 = F;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetMECalculator(double (*F)(LeptonVectors &))
{
   CalculateMEValue.push_back(F);
   MECount = CalculateMEValue.size();
}
//----------------------------------------------------------------------------
void HybridCalculator::SetToleranceF(double Tolerance)
{
   ToleranceF = Tolerance;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetIgnorePhi(bool Decision)
{
   IgnorePhi = Decision;
}
//----------------------------------------------------------------------------
std::vector<double> HybridCalculator::SimpleMassIntegral(const EventParameters &TargetParameters,
   double PT, double Eta)
{
   if(TargetParameters.HMass < TargetParameters.ZMass + TargetParameters.Z2Mass)
      return std::vector<double>(MECount);

   double MassWindow = 20;
   int MassStep = 40;

   double Factors[1001] = {0};
   for(int iM = 0; iM <= MassStep; iM++)
   {
      if(iM % 2 == 0)                 Factors[iM] = 4 * (MassWindow / MassStep * 2) / 6;
      if(iM % 2 == 1)                 Factors[iM] = 2 * (MassWindow / MassStep * 2) / 6;
      if(iM == 0 || iM == MassStep)   Factors[iM] = 1 * (MassWindow / MassStep * 2) / 6;
   }

   EventParameters CentralParameters = TargetParameters;
   LeptonVectors TargetLeptons = ConvertAnglesToVectorsRoberto(TargetParameters, 0, 0);

   double HMass = TargetParameters.HMass;

   double M12_2 = (TargetLeptons.Lepton11 + TargetLeptons.Lepton12).GetMass2();
   double M13_2 = (TargetLeptons.Lepton11 + TargetLeptons.Lepton21).GetMass2();
   double M14_2 = (TargetLeptons.Lepton11 + TargetLeptons.Lepton22).GetMass2();
   double M23_2 = (TargetLeptons.Lepton12 + TargetLeptons.Lepton21).GetMass2();
   double M24_2 = (TargetLeptons.Lepton12 + TargetLeptons.Lepton22).GetMass2();
   double M34_2 = (TargetLeptons.Lepton21 + TargetLeptons.Lepton22).GetMass2();

   TargetM12_2 = M12_2;
   TargetM13_2 = M13_2;
   TargetM14_2 = M14_2;
   TargetM23_2 = M23_2;
   TargetM24_2 = M24_2;
   TargetM34_2 = M34_2;

   std::vector<double> Integral(MECount);

   for(int iM1 = 0; iM1 <= MassStep; iM1++)
   {
      double ZMass = MassWindow * (iM1 - MassStep / 2) / MassStep + TargetParameters.ZMass;
      if(ZMass <= 0)
         continue;

      for(int iM2 = 0; iM2 <= MassStep; iM2++)
      {
         double Z2Mass = MassWindow * (iM2 - MassStep / 2) / MassStep + TargetParameters.Z2Mass;
         if(Z2Mass <= 0)
            continue;

         /*
         // This is for approximation that all deltas are small
         double DeltaZMass = 1 - ZMass / TargetParameters.ZMass;
         double DeltaZ2Mass = 1 - Z2Mass / TargetParameters.Z2Mass;
         
         double HMass2 = HMass * HMass + 2 * DeltaZMass * (M12_2 + M23_2 + M24_2)
            + 2 * DeltaZ2Mass * (M34_2 + M14_2 + M24_2);
         */

         // This is for approximation that delta_1, delta_3 are small, but not mass deltas
         double DeltaZMass = 1 - TargetParameters.ZMass / ZMass;
         double DeltaZ2Mass = 1 - TargetParameters.Z2Mass / Z2Mass;
         
         double HMass2 = HMass * HMass
            + M12_2 * (DeltaZMass * DeltaZMass - 2 * DeltaZMass)
            + M34_2 * (DeltaZ2Mass * DeltaZ2Mass - 2 * DeltaZ2Mass)
            + M13_2 * 0
            + M23_2 * (DeltaZMass * DeltaZMass - 2 * DeltaZMass)
            + M14_2 * (DeltaZ2Mass * DeltaZ2Mass - 2 * DeltaZ2Mass)
            + M24_2 * ((DeltaZMass * DeltaZMass - 2 * DeltaZMass + 1) * (DeltaZ2Mass * DeltaZ2Mass - 2 * DeltaZ2Mass + 1) - 1);

#ifdef HYBRIDCALCULATOR_DEBUG
         std::cout << "Target " << HMass << " " << TargetParameters.ZMass << " " << TargetParameters.Z2Mass << std::endl;
         std::cout << "Central " << sqrt(HMass2) << " " << ZMass << " " << Z2Mass << std::endl;
#endif

         if(HMass2 < (ZMass + Z2Mass) * (ZMass + Z2Mass))
            continue;

         CentralParameters.HMass = sqrt(HMass2);
         CentralParameters.ZMass = ZMass;
         CentralParameters.Z2Mass = Z2Mass;

         std::vector<double> Contribution(MECount);
         
         CalculateIntegrand(TargetParameters, CentralParameters, Contribution, PT, Eta);

         for(int i = 0; i < MECount; i++)
            Integral[i] = Integral[i] + Factors[iM1] * Factors[iM2] * Contribution[i];

#ifdef HYBRIDCALCULATOR_DEBUG
         std::cout << "Contribution " << Contribution << std::endl;
#endif
      }
   }

   return Integral;
}
//----------------------------------------------------------------------------
void HybridCalculator::CalculateIntegrand(const EventParameters &TargetParameters,
   const EventParameters &CentralParameters, std::vector<double> &Result,
   double PT, double Eta)
{
   static std::vector<double> ME0(MECount), B1(MECount), B3(MECount);

   CalculateMEs(CentralParameters, ME0, B1, B3);

   TempLeptons = ConvertAnglesToVectorsRoberto(CentralParameters, PT, Eta);

   // double F0Z1 = CalculateF(CentralParameters.ZMass, TargetParameters.ZMass, 0, true);
   // double F1Z1 = CalculateF(CentralParameters.ZMass, TargetParameters.ZMass, 1, true);
   // double F0Z2 = CalculateF(CentralParameters.Z2Mass, TargetParameters.Z2Mass, 0, false);
   // double F1Z2 = CalculateF(CentralParameters.Z2Mass, TargetParameters.Z2Mass, 1, false);

   double F0Z1 = 0, F1Z1 = 0;
   CalculateF_Order01(CentralParameters.ZMass, TargetParameters.ZMass, true, F0Z1, F1Z1);
   double F0Z2 = 0, F1Z2 = 0;
   CalculateF_Order01(CentralParameters.Z2Mass, TargetParameters.Z2Mass, false, F0Z2, F1Z2);

   // std::cout << TargetParameters.ZMass << " " << CentralParameters.ZMass << " " << std::endl;

   for(int i = 0; i < MECount; i++)
   {
      Result[i] = (ME0[i] * F0Z1 * F0Z2 + B1[i] * F1Z1 * F0Z2 + B3[i] * F0Z1 * F1Z2)
         * (4 * CentralParameters.ZMass * CentralParameters.Z2Mass);   // don't forget the Jacobian!
   }
}
//----------------------------------------------------------------------------
void HybridCalculator::CalculateMEs(const EventParameters &CentralParameters,
   std::vector<double> &ME0, std::vector<double> &B1, std::vector<double> &B3)
{
   const double HMass = CentralParameters.HMass;

   TempParameters = CentralParameters;
   TempLeptons = ConvertAnglesToVectorsRoberto(CentralParameters, 0, 0);

   LeptonVectors PlusLeptons1 = TempLeptons;
   PlusLeptons1.Lepton11 = TempLeptons.Lepton11 * 1.01;
   
   LeptonVectors PlusLeptons3 = TempLeptons;
   PlusLeptons3.Lepton11 = TempLeptons.Lepton21 * 1.01;

   for(int i = 0; i < MECount; i++)
   {
      ME0[i] = CalculateMEValue[i](TempLeptons);
      B1[i] = (CalculateMEValue[i](PlusLeptons1) - ME0[i]) / (1.01 - 1.00);
      B3[i] = (CalculateMEValue[i](PlusLeptons3) - ME0[i]) / (1.01 - 1.00);
   }

   /*
   EventParameters PlusParameters = CentralParameters;
   PlusParameters.HMass = HMass * 1.01;
   LeptonVectors PlusLeptons = ConvertAnglesToVectorsRoberto(PlusParameters, 0, 0);

   double RatioM12_2 = TargetM12_2 / CentralParameters.ZMass / CentralParameters.ZMass;
   double RatioM34_2 = TargetM34_2 / CentralParameters.Z2Mass / CentralParameters.Z2Mass;
   // RatioM12_2 = RatioM12_2 * RatioM12_2;
   // RatioM34_2 = RatioM34_2 * RatioM34_2;

   for(int i = 0; i < MECount; i++)
   {
      ME0[i] = CalculateMEValue[i](TempLeptons);
      double dMEdMH = (CalculateMEValue[i](PlusLeptons) - ME0[i]) / (HMass * 0.01);

      // This is with approximation that delta M's are small
      // B1 = dMEdMH * (TempLeptons.Lepton11[0] - TempLeptons.Lepton12[0]);
      // B3 = dMEdMH * (TempLeptons.Lepton21[0] - TempLeptons.Lepton22[0]);

      // This is without that mass delta approximation
      B1[i] = dMEdMH / (2 * HMass) * (TargetM13_2 - RatioM12_2 * TargetM23_2 + RatioM34_2 * TargetM14_2 - RatioM12_2 * RatioM34_2 * TargetM24_2);
      B3[i] = dMEdMH / (2 * HMass) * (TargetM13_2 - RatioM34_2 * TargetM14_2 + RatioM12_2 * TargetM23_2 - RatioM34_2 * RatioM12_2 * TargetM24_2);

      // This is without any corrections
      // B1[i] = 0;
      // B3[i] = 0;
   }
   */

   return;
}
//----------------------------------------------------------------------------
double HybridCalculator::CalculateF(double M, double M0, int Order, bool FirstZ)
{
   const double TargetC1C2 = (M0 / M) * (M0 / M);

   const int InitialStepSize = 10;

   const double CMin = 0.2;
   const double CMax = 5;

   double Integral = 0;
   double fa = 0;
   double fc = 0;
   double fb = 0;
   for(int i = 0; i < InitialStepSize; i++)
   {
      double a = (CMax - CMin) / InitialStepSize * i + CMin;
      double b = (CMax - CMin) / InitialStepSize * (i + 1) + CMin;
      double c = (a + b) / 2;

      if(i == 0)
         fa = f(a, TargetC1C2, Order, FirstZ);
      fc = f(c, TargetC1C2, Order, FirstZ);
      fb = f(b, TargetC1C2, Order, FirstZ);

      double sab = (b - a) * (fa + 4 * fc + fb) / 6;

      Integral = Integral
         + AdaptCalculateF(sab, fa, fc, fb, a, b, ToleranceF / InitialStepSize, TargetC1C2, Order, FirstZ, 0);
   }

   return Integral;
}
//----------------------------------------------------------------------------
void HybridCalculator::CalculateF_Order01(double M, double M0, bool FirstZ, double &Result0, double &Result1)
{
   const double TargetC1C2 = (M0 / M) * (M0 / M);

   const int InitialStepSize = 10;

   const double CMin = 0.2;
   const double CMax = 5;

   double Integral0 = 0, Integral1 = 0;
   double fa0 = 0, fa1 = 0;
   double fc0 = 0, fc1 = 0;
   double fb0 = 0, fb1 = 0;
   for(int i = 0; i < InitialStepSize; i++)
   {
      double a = (CMax - CMin) / InitialStepSize * i + CMin;
      double b = (CMax - CMin) / InitialStepSize * (i + 1) + CMin;
      double c = (a + b) / 2;

      if(i == 0)
         f_Order01(a, TargetC1C2, FirstZ, fa0, fa1);
      f_Order01(c, TargetC1C2, FirstZ, fc0, fc1);
      f_Order01(b, TargetC1C2, FirstZ, fb0, fb1);

      double sab0 = (b - a) * (fa0 + 4 * fc0 + fb0) / 6;
      double sab1 = (b - a) * (fa1 + 4 * fc1 + fb1) / 6;

      double Answer0 = 0, Answer1 = 0;
      AdaptCalculateF_Order01(sab0, fa0, fc0, fb0, sab1, fa1, fc1, fb1, a, b,
         ToleranceF / InitialStepSize, TargetC1C2, FirstZ, 0, Answer0, Answer1);
      
      Integral0 = Integral0 + Answer0;
      Integral1 = Integral1 + Answer1;
   }

   Result0 = Integral0;
   Result1 = Integral1;
}
//----------------------------------------------------------------------------
double HybridCalculator::AdaptCalculateF(double sab, double fa, double fc, double fb, double a, double b,
   double Tolerance, double c1c2, int Order, bool FirstZ, int Depth)
{
   double c = (a + b) / 2;
   double fd = f((a + c) / 2, c1c2, Order, FirstZ);
   double fe = f((c + b) / 2, c1c2, Order, FirstZ);
   double sac = (c - a) * (fa + 4 * fd + fc) / 6;
   double scb = (b - c) * (fc + 4 * fe + fb) / 6;

#ifdef HYBRIDCALCULATOR_DEBUG
   std::cout << "Current depth = " << Depth << std::endl;
   std::cout << a << " " << c << " " << b << " " << sac << " " << scb << " " << sab << std::endl;
   std::cout << c1c2 << " " << Order << " " << FirstZ << " " << Tolerance << std::endl;
#endif

   if(fabs(sac + scb - sab) < Tolerance * 10)
      return sac + scb;

   return AdaptCalculateF(sac, fa, fd, fc, a, c, Tolerance / 2, c1c2, Order, FirstZ, Depth + 1)
      + AdaptCalculateF(scb, fc, fe, fb, c, b, Tolerance / 2, c1c2, Order, FirstZ, Depth + 1);
}
//----------------------------------------------------------------------------
void HybridCalculator::AdaptCalculateF_Order01(double sab0, double fa0, double fc0, double fb0,
   double sab1, double fa1, double fc1, double fb1, double a, double b,
   double Tolerance, double c1c2, bool FirstZ, int Depth, double &Result0, double &Result1)
{
   // std::cout << "Depth = " << Depth << std::endl;
   // std::cout << "input " << sab0 << " " << fa0 << " " << fc0 << " " << fb0 << std::endl;
   // std::cout << "input " << sab1 << " " << fa1 << " " << fc1 << " " << fb1 << std::endl;

   double c = (a + b) / 2;

   double fd0, fd1;   f_Order01((a + c) / 2, c1c2, FirstZ, fd0, fd1);
   double fe0, fe1;   f_Order01((c + b) / 2, c1c2, FirstZ, fe0, fe1);

   double sac0 = (c - a) * (fa0 + 4 * fd0 + fc0) / 6;
   double sac1 = (c - a) * (fa1 + 4 * fd1 + fc1) / 6;
   double scb0 = (b - c) * (fc0 + 4 * fe0 + fb0) / 6;
   double scb1 = (b - c) * (fc1 + 4 * fe1 + fb1) / 6;

   if(fabs(sac0 + scb0 - sab0) < Tolerance * 10 && fabs(sac1 + scb1 - sab1) < Tolerance * 10)
   {
      Result0 = sac0 + scb0;
      Result1 = sac1 + scb1;
      return;
   }
   else if(fabs(sac0 + scb0 - sab0) < Tolerance * 10 && fabs(sac1 + scb1 - sab1) >= Tolerance * 10)
   {
      Result0 = sac0 + scb0;
      Result1 = AdaptCalculateF(sac1, fa1, fd1, fc1, a, c, Tolerance / 2, c1c2, 1, FirstZ, Depth + 1)
         + AdaptCalculateF(scb1, fc1, fe1, fb1, c, b, Tolerance / 2, c1c2, 1, FirstZ, Depth + 1);
      return;
   }
   else if(fabs(sac0 + scb0 - sab0) >= Tolerance * 10 && fabs(sac1 + scb1 - sab1) < Tolerance * 10)
   {
      Result0 = AdaptCalculateF(sac0, fa0, fd0, fc0, a, c, Tolerance / 2, c1c2, 0, FirstZ, Depth + 1)
         + AdaptCalculateF(scb0, fc0, fe0, fb0, c, b, Tolerance / 2, c1c2, 0, FirstZ, Depth + 1);
      Result1 = sac1 + scb1;
      return;
   }
   
   // Otherwise everything is ongoing

   double Left0, Left1;
   AdaptCalculateF_Order01(sac0, fa0, fd0, fc0, sac1, fa1, fd1, fc1, a, c,
      Tolerance / 2, c1c2, FirstZ, Depth + 1, Left0, Left1);
   
   double Right0, Right1;   
   AdaptCalculateF_Order01(scb0, fc0, fe0, fb0, scb1, fc1, fe1, fb1, c, b,
      Tolerance / 2, c1c2, FirstZ, Depth + 1, Right0, Right1);

   Result0 = Left0 + Right0;
   Result1 = Left1 + Right1;
}
//----------------------------------------------------------------------------
double HybridCalculator::f(double x, double c1c2, int Order, bool FirstZ)
{
   double Result = 0;

   const FourVector &L11 = TempLeptons.Lepton11;
   const FourVector &L12 = TempLeptons.Lepton12;
   const FourVector &L21 = TempLeptons.Lepton21;
   const FourVector &L22 = TempLeptons.Lepton22;

   if(IgnorePhi == true)
   {
      if(FirstZ == true)
         Result = Smear12(L11, x - 1) * Smear12(L12, c1c2 / x - 1)
            * Efficiency12(L11.GetPT() * x, L11[3] / L11.GetP(), 0)
            * Efficiency12(L12.GetPT() * c1c2 / x, L12[3] / L12.GetP(), 0);
      else
         Result = Smear34(L21, x - 1) * Smear34(L22, c1c2 / x - 1)
            * Efficiency34(L21.GetPT() * x, L21[3] / L21.GetP(), 0)
            * Efficiency34(L22.GetPT() * c1c2 / x, L22[3] / L22.GetP(), 0);
   }
   else
   {
      if(FirstZ == true)
         Result = Smear12(L11, x - 1) * Smear12(L12, c1c2 / x - 1)
            * Efficiency12(L11.GetPT() * x, L11[3] / L11.GetP(), L11.GetPhi())
            * Efficiency12(L12.GetPT() * c1c2 / x, L12[3] / L12.GetP(), L12.GetPhi());
      else
         Result = Smear34(L21, x - 1) * Smear34(L22, c1c2 / x - 1)
            * Efficiency34(L21.GetPT() * x, L21[3] / L21.GetP(), L21.GetPhi())
            * Efficiency34(L22.GetPT() * c1c2 / x, L22[3] / L22.GetP(), L22.GetPhi());
   }

#ifdef HYBRIDCALCULATOR_DEBUG
   std::cout << "Eff1 = " << Efficiency12(L11.GetPT() * x, L11.GetAbsEta(), L11.GetPhi()) << std::endl;
   std::cout << "Eff2 = " << Efficiency12(L12.GetPT() * c1c2 / x, L12.GetAbsEta(), L12.GetPhi()) << std::endl;
   std::cout << "Eff3 = " << Efficiency34(L21.GetPT() * x, L21.GetAbsEta(), L21.GetPhi()) << std::endl;
   std::cout << "Eff4 = " << Efficiency34(L22.GetPT() * c1c2 / x, L22.GetAbsEta(), L22.GetPhi()) << std::endl;

   std::cout << TempLeptons << std::endl;
   std::cout << L21.GetPT() << " " << L21.GetAbsEta() << " " << L21.GetPhi() << std::endl;
#endif

   if(Order == 0)
      return Result;
   if(Order == 1)
      return Result * (x - 1);

   for(int i = 0; i < Order; i++)
      Result = Result * (x - 1);
   return Result;
}
//----------------------------------------------------------------------------
void HybridCalculator::f_Order01(double x, double c1c2, bool FirstZ, double &Result0, double &Result1)
{
   Result0 = f(x, c1c2, 0, FirstZ);
   Result1 = Result0 * (x - 1);
}
//----------------------------------------------------------------------------




