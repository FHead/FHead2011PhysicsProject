//----------------------------------------------------------------------------
// Calculation of the hybrid method.  Result is proportional to pdf value.
// Author: Yi Chen (12173)
//----------------------------------------------------------------------------
#include "ZAHybridCalculator.h"
//----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
//----------------------------------------------------------------------------
ZAHybridCalculator::ZAHybridCalculator()
{
   Verbosity = VerboseLevel_Quiet;

   Efficiency12 = NULL;
   EfficiencyP = NULL;
   Smear12 = NULL;
   SmearP = NULL;
   PTYDensity = NULL;

   ExpansionOrder = 2;

   ToleranceFZ = 1e-6;
   ToleranceFP = 1e-6;
   ToleranceFF = 1e-15;
   IntegralCZMin = 0.75;
   IntegralCZMax = 1.25;
   IntegralCPMin = 0.75;
   IntegralCPMax = 1.25;
   IntegralCZStep = 20;
   IntegralCPStep = 20;

   DoDeltaMH = false;
   DeltaMH = 125;

   SimpleMassIntegralWindow = 100;
   SimpleMassIntegralStep = 1000;
}
//----------------------------------------------------------------------------
ZAHybridCalculator::~ZAHybridCalculator()
{
}
//----------------------------------------------------------------------------
ZAHybridCalculator &ZAHybridCalculator::operator =(const ZAHybridCalculator &other)
{
   CalculateMEValue = other.CalculateMEValue;
   MECount = other.MECount;
   
   Verbosity = other.Verbosity;

   Efficiency12 = other.Efficiency12;
   EfficiencyP = other.EfficiencyP;
   Smear12 = other.Smear12;
   SmearP = other.SmearP;
   PTYDensity = other.PTYDensity;
   
   ExpansionOrder = other.ExpansionOrder;

   ToleranceFZ = other.ToleranceFZ;
   ToleranceFP = other.ToleranceFP;
   ToleranceFF = other.ToleranceFF;
   IntegralCZMin = other.IntegralCZMin;
   IntegralCZMax = other.IntegralCZMax;
   IntegralCPMin = other.IntegralCPMin;
   IntegralCPMax = other.IntegralCPMax;
   IntegralCZStep = other.IntegralCZStep;
   IntegralCPStep = other.IntegralCPStep;

   DoDeltaMH = other.DoDeltaMH;
   DeltaMH = other.DeltaMH;

   SimpleMassIntegralWindow = other.SimpleMassIntegralWindow;
   SimpleMassIntegralStep = other.SimpleMassIntegralStep;

   return *this;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetVerbosity(VerboseLevel Value)
{
   Verbosity = Value;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetEfficiency12(double (*F)(double, double, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[ZAHybridCalculator] Efficiency function on first lepton pair set to NULL." << std::endl;
      else
         std::cerr << "[ZAHybridCalculator] Efficiency function on first lepton pair set." << std::endl;
   }

   Efficiency12 = F;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetEfficiencyP(double (*F)(double, double, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[ZAHybridCalculator] Efficiency function on second lepton pair set to NULL." << std::endl;
      else
         std::cerr << "[ZAHybridCalculator] Efficiency function on second lepton pair set." << std::endl;
   }

   EfficiencyP = F;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetSmear12(double (*F)(const FourVector &, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[ZAHybridCalculator] Smearing function on first lepton pair set to NULL." << std::endl;
      else
         std::cerr << "[ZAHybridCalculator] Smearing function on first lepton pair set." << std::endl;
   }

   Smear12 = F;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetSmearP(double (*F)(const FourVector &, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[ZAHybridCalculator] Smearing function on second lepton pair set to NULL." << std::endl;
      else
         std::cerr << "[ZAHybridCalculator] Smearing function on second lepton pair set." << std::endl;
   }

   SmearP = F;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetPTYDensity(double (*F)(double, double, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[ZAHybridCalculator] (PT,Y) density set to NULL." << std::endl;
      else
         std::cerr << "[ZAHybridCalculator] (PT,Y) density set." << std::endl;
   }

   PTYDensity = F;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetMECalculator(double (*F)(ZALeptonVectors &))
{
   if(F == NULL)
   {
      if(Verbosity >= VerboseLevel_Normal)
         std::cerr << "[ZAHybridCalculator] Attempted to add a NULL ME function.  Do nothing." << std::endl;
      return;
   }

   CalculateMEValue.push_back(F);
   MECount = CalculateMEValue.size();

   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[ZAHybridCalculator] Added a new ME function.  Current count: " << MECount << std::endl;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetDoDeltaMH(bool Decision, double Value)
{
   DoDeltaMH = Decision;
   DeltaMH = Value;

   if(Verbosity >= VerboseLevel_Normal)
   {
      if(DoDeltaMH == false)
         std::cerr << "[ZAHybridCalculator] Don't use narrow-width approximation." << std::endl;
      else
         std::cerr << "[ZAHybridCalculator] Use narrow-width approximation with MH = " << DeltaMH << std::endl;
   }
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetSimpleMassIntegralWindow(double Window)
{
   if(Verbosity >= VerboseLevel_Normal)
         std::cerr << "[ZAHybridCalculator] Mass integration window set to " << Window << "." << std::endl;
   
   SimpleMassIntegralWindow = Window;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetSimpleMassIntegralStep(int Step)
{
   if(Verbosity >= VerboseLevel_Normal)
         std::cerr << "[ZAHybridCalculator] Mass integration Step set to " << Step << "." << std::endl;
   
   SimpleMassIntegralStep = Step;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetToleranceFZ(double Tolerance)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[ZAHybridCalculator] Tolerance on FZ functions set to " << Tolerance << "." << std::endl;

   ToleranceFZ = Tolerance;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetToleranceFP(double Tolerance)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[ZAHybridCalculator] Tolerance on FP functions set to " << Tolerance << "." << std::endl;

   ToleranceFP = Tolerance;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetToleranceFF(double Tolerance)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[ZAHybridCalculator] Tolerance on FF functions set to " << Tolerance << "." << std::endl;

   ToleranceFF = Tolerance;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetIntegralCZRange(double Min, double Max)
{
   if(Min > Max)
   {
      std::cerr << "[ZAHybridCalculator] Warning: min > max.  Swap the two for now" << std::endl;
      std::swap(Min, Max);
   }
   if(Min <= 0)
   {
      std::cerr << "[ZAHybridCalculator] Warning: integral min < 0.  Do nothing." << std::endl;
      return;
   }
   if(Max <= 0)
   {
      std::cerr << "[ZAHybridCalculator] Warning: integral max < 0.  Do nothing." << std::endl;
      return;
   }

   IntegralCZMin = Min;
   IntegralCZMax = Max;

   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[ZAHybridCalculator] Integration range for CZ's set to "
         << Min << " - " << Max << std::endl;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetIntegralCPRange(double Min, double Max)
{
   if(Min > Max)
   {
      std::cerr << "[ZAHybridCalculator] Warning: min > max.  Swap the two for now" << std::endl;
      std::swap(Min, Max);
   }
   if(Min <= 0)
   {
      std::cerr << "[ZAHybridCalculator] Warning: integral min < 0.  Do nothing." << std::endl;
      return;
   }
   if(Max <= 0)
   {
      std::cerr << "[ZAHybridCalculator] Warning: integral max < 0.  Do nothing." << std::endl;
      return;
   }

   IntegralCPMin = Min;
   IntegralCPMax = Max;

   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[ZAHybridCalculator] Integration range for CP's set to "
         << Min << " - " << Max << std::endl;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetIntegralCZStep(int Step)
{
   if(Step <= 5)
   {
      std::cerr << "[ZAHybridCalculator] Unreasonable value of initial step count in CZ's requested." << std::endl;
      Step = 20;
   }

   IntegralCZStep = Step;

   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[ZAHybridCalculator] Step size set to " << IntegralCZStep << "." << std::endl;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::SetIntegralCPStep(int Step)
{
   if(Step <= 5)
   {
      std::cerr << "[ZAHybridCalculator] Unreasonable value of initial step count in CP's requested." << std::endl;
      Step = 20;
   }

   IntegralCPStep = Step;

   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[ZAHybridCalculator] Step size set to " << IntegralCPStep << "." << std::endl;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::PrintSettings()
{
   PrintSettings(std::cout);
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::PrintSettings(std::ostream &out)
{
   out << "Summary of settings:" << std::endl;
   out << std::endl;

   if(Efficiency12 == NULL)   out << "Efficiency12: not set." << std::endl;
   else                       out << "Efficiency12: set." << std::endl;
   if(EfficiencyP == NULL)    out << "EfficiencyP: not set." << std::endl;
   else                       out << "EfficiencyP: set." << std::endl;
   if(Smear12 == NULL)        out << "Smear12: not set." << std::endl;
   else                       out << "Smear12: set." << std::endl;
   if(SmearP == NULL)         out << "SmearP: not set." << std::endl;
   else                       out << "SmearP: set." << std::endl;
   if(PTYDensity == NULL)     out << "PTYDensity: not set." << std::endl;
   else                       out << "PTYDensity: set." << std::endl;

   out << "Number of ME: " << CalculateMEValue.size() << std::endl;
   out << "Expansion order: " << ExpansionOrder << std::endl;

   out << "Tolerance on FZ: " << ToleranceFZ << std::endl;
   out << "Tolerance on FP: " << ToleranceFP << std::endl;
   out << "Tolerance on FF: " << ToleranceFF << std::endl;

   out << "Integral range on CZ: " << IntegralCZMin << " - " << IntegralCZMax << std::endl;
   out << "Integral range on CP: " << IntegralCPMin << " - " << IntegralCPMax << std::endl;
   out << "Number of initial steps on CZ: " << IntegralCZStep << std::endl;
   out << "Number of initial steps on CP: " << IntegralCPStep << std::endl;

   out << "DoDeltaMH: " << TextBool(DoDeltaMH) << std::endl;

   if(DoDeltaMH == true)        out << "MH: set at " << DeltaMH << std::endl;
   else                         out << "MH: no prior distribution." << std::endl;

   out << "Mass window: " << SimpleMassIntegralWindow << std::endl;
   out << "Mass Step: " << SimpleMassIntegralStep << std::endl;

   out << std::endl;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::TestOutput()
{
   ZAEventParameters Point;
   Point.HMass = 125.0717827;
   Point.ZMass = 105.77198368;
   Point.Phi0 = 3.014345815;
   Point.Theta0 = acos(0.1267741978);
   Point.ThetaLL = acos(0.8313573548);
   Point.PTH = 30;
   Point.YH = 0.5;
   Point.PhiH = 1;
   Point.PhiOffset = -1.020748664;

   std::vector<double> Integrals = SimpleMassIntegral(Point);

   std::cout << "Integral[1] = [";
   for(int i = 0; i < (int)Integrals.size(); i++)
   {
      if(i != 0)
         std::cout << ", ";
      std::cout << Integrals[i];
   }
   std::cout << "]" << std::endl;

   ZALeptonVectors Leptons;
   Leptons.Lepton1.SetPtEtaPhi(14.624126, 0.7552305, 0.5874394);
   Leptons.Lepton2.SetPtEtaPhi(82.687938, 0.5519971, 3.1338023);
   Leptons.Photon.SetPtEtaPhi(19.936076, -0.020645, -1.480457);

   Point = ConvertVectorsToAnglesRoberto(Leptons);

   Integrals = SimpleMassIntegral(Point);

   std::cout << "Integral[2] = [";
   for(int i = 0; i < (int)Integrals.size(); i++)
   {
      if(i != 0)
         std::cout << ", ";
      std::cout << Integrals[i];
   }
   std::cout << "]" << std::endl;
}
//----------------------------------------------------------------------------
std::vector<double> ZAHybridCalculator::SimpleMassIntegral(const ZAEventParameters &RecoParameters)
{
   std::vector<double> Result(MECount);
   for(int i = 0; i < MECount; i++)
      Result[i] = 0;

   if(RecoParameters.HMass < RecoParameters.ZMass)
      return Result;

   ZALeptonVectors RecoVectors = ConvertAnglesToVectorsRoberto(RecoParameters);

   FourVector &L1 = RecoVectors.Lepton1;
   FourVector &L2 = RecoVectors.Lepton2;
   FourVector &P = RecoVectors.Photon;

   double RecoEfficiency = Efficiency12(L1.GetPT(), L1[3] / L1.GetP(), L1.GetPhi())
      * Efficiency12(L2.GetPT(), L2[3] / L2.GetP(), L2.GetPhi())
      * EfficiencyP(P.GetPT(), P[3] / P.GetP(), P.GetPhi());

   if(RecoEfficiency < 1e-7)
      return Result;

   double Masses[1001] = {0}, Factors[1001] = {0};
   FillMassPosition(SimpleMassIntegralStep, RecoParameters.ZMass, SimpleMassIntegralWindow, 0, Masses);
   FillMassWeights(SimpleMassIntegralStep, Masses, Factors);

   for(int iM = 0; iM <= SimpleMassIntegralStep; iM++)
   {
      double MZ = Masses[iM];
      double RecoMZ = RecoParameters.ZMass;

      if(MZ <= 0)
         continue;

      ZALeptonVectors CentralVectors = RecoVectors;
      CentralVectors.Lepton2 = RecoVectors.Lepton2 / RecoMZ / RecoMZ * MZ * MZ;

      std::vector<double> Contribution = CalculateIntegrand(RecoVectors, CentralVectors);

      // std::cout << MZ << " " << Contribution[0] << std::endl;

      for(int i = 0; i < MECount; i++)
         Result[i] = Result[i] + Factors[iM] * Contribution[i];
   }

   double RecoJ9 = VolumeElement::EstimateVolumeFull5(RecoParameters);
   for(int i = 0; i < MECount; i++)
      Result[i] = Result[i] / RecoJ9 * RecoEfficiency;

   return Result;
}
//----------------------------------------------------------------------------
std::vector<double> ZAHybridCalculator::PassThroughMode(const ZAEventParameters &RecoParameters)
{
   ZALeptonVectors Vectors = ConvertAnglesToVectorsRoberto(RecoParameters);

   double PTYWeight = 1;
   FourVector Total = Vectors.GetTotal();
   if(PTYDensity != NULL)
      PTYWeight = PTYDensity(Total.GetPT(), Total.GetY(), Total.GetMass2());

   Vectors = GoToRest(Vectors);

   std::vector<double> Result(CalculateMEValue.size());

   for(int i = 0; i < (int)CalculateMEValue.size(); i++)
      Result[i] = (*CalculateMEValue[i])(Vectors) * PTYWeight;

   return Result;
}
//----------------------------------------------------------------------------
std::vector<double> ZAHybridCalculator::CalculateIntegrand(const ZALeptonVectors &Reco,
   const ZALeptonVectors &Central)
{
   std::vector<double> Result(MECount);

   if(DoDeltaMH == false)
   {
      static std::vector<double> ME0(MECount), B1(MECount), BP(MECount), B11(MECount), B1P(MECount), BPP(MECount);

      CalculateMEs(Central, ME0, B1, BP, B11, B1P, BPP);

      ZAMassSquare RecoMM(Reco);

      double F0Z = (ExpansionOrder >= 0) ? CalculateFZ(Central.Lepton1, Central.Lepton2, RecoMM, 0) : 0;
      double F1Z = (ExpansionOrder >= 1) ? CalculateFZ(Central.Lepton1, Central.Lepton2, RecoMM, 1) : 0;
      double F2Z = (ExpansionOrder >= 2) ? CalculateFZ(Central.Lepton1, Central.Lepton2, RecoMM, 2) : 0;
      double F0P = (ExpansionOrder >= 0) ? CalculateFP(Central.Photon, 0) : 0;
      double F1P = (ExpansionOrder >= 1) ? CalculateFP(Central.Photon, 1) : 0;
      double F2P = (ExpansionOrder >= 2) ? CalculateFP(Central.Photon, 2) : 0;

      for(int i = 0; i < MECount; i++)
      {
         switch(ExpansionOrder)
         {
            case 0:
               Result[i] = ME0[i] * F0Z * F0P;
               break;
            case 1:
               Result[i] = (ME0[i] * F0Z * F0P + B1[i] * F1Z * F0P + BP[i] * F0Z * F1P);
               break;
            case 2:
               Result[i] = (ME0[i] * F0Z * F0P + B1[i] * F1Z * F0P + BP[i] * F0Z * F1P
                     + 0.5 * B11[i] * F2Z * F0P + 1 * B1P[i] * F1Z * F1P + 0.5 * BPP[i] * F0Z * F2P);
               break;
            default:
               Result[i] = 0;
               break;
         }

         Result[i] = Result[i] * (Central.Lepton1 + Central.Lepton2).GetMass();
      }
   }
   else
   {
      static std::vector<double> ME0(MECount), B1(MECount), B11(MECount);

      ZAMassSquare RecoMM(Reco);

      CalculateMEsDeltaMH(Central, RecoMM, ME0, B1, B11);

      double F0Z = (ExpansionOrder >= 0) ? CalculateFF(Central, RecoMM, 0) : 0;
      double F1Z = (ExpansionOrder >= 1) ? CalculateFF(Central, RecoMM, 1) : 0;
      double F2Z = (ExpansionOrder >= 2) ? CalculateFF(Central, RecoMM, 2) : 0;

      for(int i = 0; i < MECount; i++)
      {
         switch(ExpansionOrder)
         {
            case 0:
               Result[i] = ME0[i] * F0Z;
               break;
            case 1:
               Result[i] = (ME0[i] * F0Z + B1[i] * F1Z);
               break;
            case 2:
               Result[i] = (ME0[i] * F0Z + B1[i] * F1Z + 0.5 * B11[i] * F2Z);
               break;
            default:
               Result[i] = 0;
               break;
         }

         Result[i] = Result[i] * (Central.Lepton1 + Central.Lepton2).GetMass();
      }
   }

   return Result;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::CalculateMEs(const ZALeptonVectors &Central, std::vector<double> &ME0,
   std::vector<double> &B1, std::vector<double> &BP, std::vector<double> &B11,
   std::vector<double> &B1P, std::vector<double> &BPP)
{
   ZALeptonVectors Plus1 = Central.ApplySmearing(ZACs(1, 1 / 1.01, 1.01));
   ZALeptonVectors PlusP = Central.ApplySmearing(ZACs(1 / 1.01, 1, 1));
   ZALeptonVectors Plus1P = Central.ApplySmearing(ZACs(1 / 1.01, 1 / 1.01, 1.01));
   ZALeptonVectors Minus1 = Central.ApplySmearing(ZACs(1, 1.01, 1 / 1.01));
   ZALeptonVectors MinusP = Central.ApplySmearing(ZACs(1.01, 1, 1));

   double PTYCentral = 1;
   double PTYPlus1 = 1;
   double PTYPlusP = 1;
   double PTYPlus1P = 1;
   double PTYMinus1 = 1;
   double PTYMinusP = 1;

   if(PTYDensity != NULL)
   {
      FourVector TotalCentral = Central.GetTotal();
      FourVector TotalPlus1 = Plus1.GetTotal();
      FourVector TotalPlusP = PlusP.GetTotal();
      FourVector TotalPlus1P = Plus1P.GetTotal();
      FourVector TotalMinus1 = Minus1.GetTotal();
      FourVector TotalMinusP = MinusP.GetTotal();

      PTYCentral = PTYDensity(TotalCentral.GetPT(), TotalCentral.GetY(), TotalCentral.GetMass2());
      PTYPlus1 = PTYDensity(TotalPlus1.GetPT(), TotalPlus1.GetY(), TotalPlus1.GetMass2());
      PTYPlusP = PTYDensity(TotalPlusP.GetPT(), TotalPlusP.GetY(), TotalPlusP.GetMass2());
      PTYPlus1P = PTYDensity(TotalPlus1P.GetPT(), TotalPlus1P.GetY(), TotalPlus1P.GetMass2());
      PTYMinus1 = PTYDensity(TotalMinus1.GetPT(), TotalMinus1.GetY(), TotalMinus1.GetMass2());
      PTYMinusP = PTYDensity(TotalMinusP.GetPT(), TotalMinusP.GetY(), TotalMinusP.GetMass2());
   }

   ZALeptonVectors RestCentral = Central.GoToRest();
   ZALeptonVectors RestPlus1 = Plus1.GoToRest();
   ZALeptonVectors RestPlusP = PlusP.GoToRest();
   ZALeptonVectors RestPlus1P = Plus1P.GoToRest();
   ZALeptonVectors RestMinus1 = Minus1.GoToRest();
   ZALeptonVectors RestMinusP = MinusP.GoToRest();

   double VolumeElementCentral
      = VolumeElement::EstimateVolumeFull5(ConvertVectorsToAnglesRoberto(Central));
   double VolumeElementPlus1
      = (ExpansionOrder >= 1) ? VolumeElement::EstimateVolumeFull5(ConvertVectorsToAnglesRoberto(Plus1)) : 0;
   double VolumeElementPlusP
      = (ExpansionOrder >= 1) ? VolumeElement::EstimateVolumeFull5(ConvertVectorsToAnglesRoberto(PlusP)) : 0;
   double VolumeElementPlus1P
      = (ExpansionOrder >= 2) ? VolumeElement::EstimateVolumeFull5(ConvertVectorsToAnglesRoberto(Plus1P)) : 0;
   double VolumeElementMinus1
      = (ExpansionOrder >= 1) ? VolumeElement::EstimateVolumeFull5(ConvertVectorsToAnglesRoberto(Minus1)) : 0;
   double VolumeElementMinusP
      = (ExpansionOrder >= 1) ? VolumeElement::EstimateVolumeFull5(ConvertVectorsToAnglesRoberto(MinusP)) : 0;

   for(int i = 0; i < MECount; i++)
   {
      double ValueCentral = CalculateMEValue[i](RestCentral);
      double ValuePlus1 = (ExpansionOrder >= 1) ? CalculateMEValue[i](RestPlus1) : 0;
      double ValuePlusP = (ExpansionOrder >= 1) ? CalculateMEValue[i](RestPlusP) : 0;
      double ValuePlus1P = (ExpansionOrder >= 2) ? CalculateMEValue[i](RestPlus1P) : 0;
      double ValueMinus1 = (ExpansionOrder >= 1) ? CalculateMEValue[i](RestMinus1) : 0;
      double ValueMinusP = (ExpansionOrder >= 1) ? CalculateMEValue[i](RestMinusP) : 0;

      ValueCentral = ValueCentral * VolumeElementCentral;
      ValuePlus1 = ValuePlus1 * VolumeElementPlus1;
      ValuePlusP = ValuePlusP * VolumeElementPlusP;
      ValuePlus1P = ValuePlus1P * VolumeElementPlus1P;
      ValueMinus1 = ValueMinus1 * VolumeElementMinus1;
      ValueMinusP = ValueMinusP * VolumeElementMinusP;

      ME0[i] = ValueCentral;
      B1[i] = (ValuePlus1 - ValueMinus1) / (1.01 - 0.99);
      BP[i] = (ValuePlusP - ValueMinusP) / (1.01 - 0.99);
      B11[i] = (ValuePlus1 + ValueMinus1 - ME0[i] * 2) / (1.01 - 1.00) / (1.01 - 1.00);
      B1P[i] = (ValuePlus1P - ValuePlus1 - ValuePlusP + ME0[i]) / (1.01 - 1.00) / (1.01 - 1.00);
      BPP[i] = (ValuePlusP + ValueMinusP - ME0[i] * 2) / (1.01 - 1.00) / (1.01 - 1.00);

      if(ExpansionOrder < 1)
         B1[i] = 0, BP[i] = 0;
      if(ExpansionOrder < 2)
         B11[i] = 0, B1P[i] = 0, BPP[i] = 0;
   }
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::CalculateMEsDeltaMH(const ZALeptonVectors &Central, const ZAMassSquare &RecoMM,
   std::vector<double> &ME0, std::vector<double> &B1, std::vector<double> &B11)
{
   double GenM12_2 = (Central.Lepton1 + Central.Lepton2).GetMass2();

   ZALeptonVectors Middle = Central.ApplySmearing(ZACs(1 / CalculateCP(RecoMM, 1, GenM12_2), 1, 1));
   ZALeptonVectors Plus1 = Central.ApplySmearing(ZACs(1 / CalculateCP(RecoMM, 1.01, GenM12_2), 1 / 1.01, 1.01));
   ZALeptonVectors Minus1 = Central.ApplySmearing(ZACs(1 / CalculateCP(RecoMM, 1 / 1.01, GenM12_2), 1.01, 1 / 1.01));

   double PTYMiddle = 1;
   double PTYPlus1 = 1;
   double PTYMinus1 = 1;

   if(PTYDensity != NULL)
   {
      FourVector TotalMiddle = Middle.GetTotal();
      FourVector TotalPlus1 = Plus1.GetTotal();
      FourVector TotalMinus1 = Minus1.GetTotal();

      PTYMiddle = PTYDensity(TotalMiddle.GetPT(), TotalMiddle.GetY(), TotalMiddle.GetMass2());
      PTYPlus1 = PTYDensity(TotalPlus1.GetPT(), TotalPlus1.GetY(), TotalPlus1.GetMass2());
      PTYMinus1 = PTYDensity(TotalMinus1.GetPT(), TotalMinus1.GetY(), TotalMinus1.GetMass2());
   }

   ZALeptonVectors RestMiddle = Middle.GoToRest();
   ZALeptonVectors RestPlus1 = Plus1.GoToRest();
   ZALeptonVectors RestMinus1 = Minus1.GoToRest();

   double VolumeElementMiddle
      = VolumeElement::EstimateVolumeFull5(ConvertVectorsToAnglesRoberto(Middle));
   double VolumeElementPlus1
      = (ExpansionOrder >= 1) ? VolumeElement::EstimateVolumeFull5(ConvertVectorsToAnglesRoberto(Plus1)) : 0;
   double VolumeElementMinus1
      = (ExpansionOrder >= 1) ? VolumeElement::EstimateVolumeFull5(ConvertVectorsToAnglesRoberto(Minus1)) : 0;

   for(int i = 0; i < MECount; i++)
   {
      double ValueMiddle = CalculateMEValue[i](RestMiddle);
      double ValuePlus1 = (ExpansionOrder >= 1) ? CalculateMEValue[i](RestPlus1) : 0;
      double ValueMinus1 = (ExpansionOrder >= 1) ? CalculateMEValue[i](RestMinus1) : 0;

      ValueMiddle = ValueMiddle * VolumeElementMiddle;
      ValuePlus1 = ValuePlus1 * VolumeElementPlus1;
      ValueMinus1 = ValueMinus1 * VolumeElementMinus1;

      ME0[i] = ValueMiddle;
      B1[i] = (ValuePlus1 - ValueMinus1) / (1.01 - 0.99);
      B11[i] = (ValuePlus1 + ValueMinus1 - ME0[i] * 2) / (1.01 - 1.00) / (1.01 - 1.00);

      if(ExpansionOrder < 1)
         B1[i] = 0;
      if(ExpansionOrder < 2)
         B11[i] = 0;
   }
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::CalculateFZ(const FourVector &L1, const FourVector &L2,
   const ZAMassSquare &RecoMM, int Order)
{
   const double Tolerance = ToleranceFZ;
   const double Min = IntegralCZMin;
   const double Max = IntegralCZMax;
   const int Step = IntegralCZStep;

   double Integral = 0;
   double fa = 0, fc = 0, fb = 0;
   for(int i = 0; i < Step; i++)
   {
      double a = (Max - Min) / Step * i + Min;
      double b = (Max - Min) / Step * (i + 1) + Min;
      double c = (a + b) / 2;

      if(i == 0)
         fa = FZ(a, L1, L2, RecoMM, Order);
      fc = FZ(c, L1, L2, RecoMM, Order);
      fb = FZ(b, L1, L2, RecoMM, Order);

      double sab = (b - a) * (fa + 4 * fc + fb) / 6;

      double CurrentTolerance = Tolerance / Step;

      double Contribution = AdaptCalculateFZ(sab, fa, fc, fb, a, b, L1, L2, RecoMM, CurrentTolerance, Order, 0);

      Integral = Integral + Contribution;

      fa = fb;
   }

   return Integral;
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::CalculateFP(const FourVector &Photon, int Order)
{
   const double Tolerance = ToleranceFP;
   const double Min = IntegralCPMin;
   const double Max = IntegralCPMax;
   const int Step = IntegralCPStep;

   double Integral = 0;
   double fa = 0, fc = 0, fb = 0;
   for(int i = 0; i < Step; i++)
   {
      double a = (Max - Min) / Step * i + Min;
      double b = (Max - Min) / Step * (i + 1) + Min;
      double c = (a + b) / 2;

      if(i == 0)
         fa = FP(a, Photon, Order);
      fc = FP(c, Photon, Order);
      fb = FP(b, Photon, Order);

      double sab = (b - a) * (fa + 4 * fc + fb) / 6;

      double CurrentTolerance = Tolerance / Step;

      double Contribution = AdaptCalculateFP(sab, fa, fc, fb, a, b, Photon, CurrentTolerance, Order, 0);

      Integral = Integral + Contribution;

      fa = fb;
   }

   return Integral;
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::CalculateFF(const ZALeptonVectors &Vectors,
   const ZAMassSquare &RecoMM, int Order)
{
   const double Tolerance = ToleranceFZ;
   const double Min = IntegralCZMin;
   const double Max = IntegralCZMax;
   const int Step = IntegralCZStep;

   double Integral = 0;
   double fa = 0, fc = 0, fb = 0;
   for(int i = 0; i < Step; i++)
   {
      double a = (Max - Min) / Step * i + Min;
      double b = (Max - Min) / Step * (i + 1) + Min;
      double c = (a + b) / 2;

      if(i == 0)
         fa = FF(a, Vectors, RecoMM, Order);
      fc = FF(c, Vectors, RecoMM, Order);
      fb = FF(b, Vectors, RecoMM, Order);

      double sab = (b - a) * (fa + 4 * fc + fb) / 6;

      double CurrentTolerance = Tolerance / Step;

      double Contribution = AdaptCalculateFF(sab, fa, fc, fb, a, b, Vectors, RecoMM, CurrentTolerance, Order, 0);

      Integral = Integral + Contribution;

      fa = fb;
   }

   return Integral;
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::AdaptCalculateFZ(double sab,
   double fa, double fc, double fb, double a, double b,
   const FourVector &L1, const FourVector &L2, const ZAMassSquare &RecoMM,
   double Tolerance, int Order, int Depth)
{
   double c = (a + b) / 2;
   double fd = FZ((a + c) / 2, L1, L2, RecoMM, Order);
   double fe = FZ((c + b) / 2, L1, L2, RecoMM, Order);
   double sac = (c - a) * (fa + 4 * fd + fc) / 6;
   double scb = (b - c) * (fc + 4 * fe + fb) / 6;

   if(fabs(sac + scb - sab) < Tolerance * 10)
      return sac + scb;

   return AdaptCalculateFZ(sac, fa, fd, fc, a, c, L1, L2, RecoMM, Tolerance / 2, Order, Depth + 1)
      + AdaptCalculateFZ(scb, fc, fe, fb, c, b, L1, L2, RecoMM, Tolerance / 2, Order, Depth + 1);
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::AdaptCalculateFP(double sab,
   double fa, double fc, double fb, double a, double b,
   const FourVector &Photon, double Tolerance, int Order, int Depth)
{
   double c = (a + b) / 2;
   double fd = FP((a + c) / 2, Photon, Order);
   double fe = FP((c + b) / 2, Photon, Order);
   double sac = (c - a) * (fa + 4 * fd + fc) / 6;
   double scb = (b - c) * (fc + 4 * fe + fb) / 6;

   if(fabs(sac + scb - sab) < Tolerance * 10)
      return sac + scb;

   return AdaptCalculateFP(sac, fa, fd, fc, a, c, Photon, Tolerance / 2, Order, Depth + 1)
      + AdaptCalculateFP(scb, fc, fe, fb, c, b, Photon, Tolerance / 2, Order, Depth + 1);
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::AdaptCalculateFF(double sab,
   double fa, double fc, double fb, double a, double b,
   const ZALeptonVectors &Vectors, const ZAMassSquare &RecoMM, double Tolerance, int Order, int Depth)
{
   double c = (a + b) / 2;
   double fd = FF((a + c) / 2, Vectors, RecoMM, Order);
   double fe = FF((c + b) / 2, Vectors, RecoMM, Order);
   double sac = (c - a) * (fa + 4 * fd + fc) / 6;
   double scb = (b - c) * (fc + 4 * fe + fb) / 6;

   if(fabs(sac + scb - sab) < Tolerance * 10)
      return sac + scb;

   return AdaptCalculateFF(sac, fa, fd, fc, a, c, Vectors, RecoMM, Tolerance / 2, Order, Depth + 1)
      + AdaptCalculateFF(scb, fc, fe, fb, c, b, Vectors, RecoMM, Tolerance / 2, Order, Depth + 1);
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::FZ(double c, const FourVector &L1, const FourVector &L2,
   const ZAMassSquare &RecoMM, int Order)
{
   double cc = (L1 + L2).GetMass2() / RecoMM.M12_2;

   double Result = Smear12(L1 / c, c - 1) * Smear12(L2 * c, 1 / c / cc - 1) * cc;
   Result = Result / CalculateJB(RecoMM, ZACs(1, c, 1 / c / cc));

   for(int i = 0; i < Order; i++)
      Result = Result * (c - 1);
   
   return Result;
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::FP(double c, const FourVector &Photon, int Order)
{
   double Result = SmearP(Photon / c, c - 1) / c;

   for(int i = 0; i < Order; i++)
      Result = Result * (c - 1);

   return Result;
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::FF(double c, const ZALeptonVectors &Vectors, const ZAMassSquare &RecoMM, int Order)
{
   const FourVector &L1 = Vectors.Lepton1;
   const FourVector &L2 = Vectors.Lepton2;
   const FourVector &Photon = Vectors.Photon;

   double GenM12_2 = (L1 + L2).GetMass2();

   double cc = GenM12_2 / RecoMM.M12_2;
   double cp = CalculateCP(RecoMM, c, GenM12_2);

   double Result = Smear12(L1 / c, c - 1) * Smear12(L2 * c, 1 / c / cc - 1) * cc;
   Result = Result * SmearP(Photon / cp, cp - 1) / cp;
   Result = Result / CalculateJS(RecoMM, ZACs(cp, c, 1 / c / cc));

   for(int i = 0; i < Order; i++)
      Result = Result * (c - 1);
   
   return Result;
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::FillMassPosition(int Step, double Center, double Window,
   double AttractorStrength, double Masses[])
{
   for(int iM = 0; iM <= Step; iM++)
   {
      double K = 1 / (Window / 2 * AttractorStrength + 1);
      double Delta = Window * (iM - Step / 2) / Step;
      double FDelta = K * Delta * (fabs(Delta * AttractorStrength) + 1);
      Masses[iM] = Center + FDelta;
   }
}
//----------------------------------------------------------------------------
void ZAHybridCalculator::FillMassWeights(int Step, double Masses[], double Weights[])
{
   for(int iM = 0; iM < Step; iM = iM + 2)
   {
      double X1 = Masses[iM+0];
      double X2 = Masses[iM+1];   double Delta12 = X2 - X1;
      double X3 = Masses[iM+2];   double Delta23 = X3 - X2;

      double A1 = Delta23 / (Delta12 * Delta23 * (Delta12 + Delta23));
      double A2 = (-Delta23 - Delta12) / (Delta12 * Delta23 * (Delta12 + Delta23));
      double A3 = Delta12 / (Delta12 * Delta23 * (Delta12 + Delta23));

      double B1 = -Delta23 * Delta23 / (Delta12 * Delta23 * (Delta12 + Delta23));
      double B2 = (Delta23 * Delta23 - Delta12 * Delta12) / (Delta12 * Delta23 * (Delta12 + Delta23));
      double B3 = Delta12 * Delta12 / (Delta12 * Delta23 * (Delta12 + Delta23));

      double C1 = 0;
      double C2 = 1;
      double C3 = 0;

      double W1 = (Delta12 + Delta23) * (A1 / 3 * (Delta23 * Delta23 - Delta23 * Delta12 + Delta12 * Delta12)
         + B1 / 2 * (Delta23 - Delta12) + C1);
      double W2 = (Delta12 + Delta23) * (A2 / 3 * (Delta23 * Delta23 - Delta23 * Delta12 + Delta12 * Delta12)
         + B2 / 2 * (Delta23 - Delta12) + C2);
      double W3 = (Delta12 + Delta23) * (A3 / 3 * (Delta23 * Delta23 - Delta23 * Delta12 + Delta12 * Delta12)
         + B3 / 2 * (Delta23 - Delta12) + C3);

      Weights[iM+0] = Weights[iM+0] + W1;
      Weights[iM+1] = Weights[iM+1] + W2;
      Weights[iM+2] = Weights[iM+2] + W3;
   }
}
//----------------------------------------------------------------------------
ZALeptonVectors ZAHybridCalculator::GoToRest(ZALeptonVectors Vectors)
{
   FourVector Total = Vectors.GetTotal();

   Vectors.Lepton1 = Vectors.Lepton1.Boost(-Total, Total.GetP() / Total[0]);
   Vectors.Lepton2 = Vectors.Lepton2.Boost(-Total, Total.GetP() / Total[0]);
   Vectors.Photon = Vectors.Photon.Boost(-Total, Total.GetP() / Total[0]);

   return Vectors;
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::CalculateJS(const ZAMassSquare &RMM, const ZACs &C)
{
   const double &C1 = C.c[1];
   const double &C2 = C.c[2];
   const double &CP = C.c[0];

   return (RMM.M1P_2 / C1 / CP / CP + RMM.M2P_2 / C2 / CP / CP) * (RMM.M12_2 / C1 / C2 / C2);
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::CalculateJB(const ZAMassSquare &RMM, const ZACs &C)
{
   const double &C1 = C.c[1];
   const double &C2 = C.c[2];

   return RMM.M12_2 / C1 / C2 / C2;
}
//----------------------------------------------------------------------------
double ZAHybridCalculator::CalculateCP(const ZAMassSquare &RMM, const double c1, const double GenM12_2)
{
   return (RMM.M1P_2 / c1 + c1 * GenM12_2 / RMM.M12_2 * RMM.M2P_2) / (DeltaMH * DeltaMH - GenM12_2);
}
//----------------------------------------------------------------------------
std::string ZAHybridCalculator::TextBool(bool Meow)
{
   return (Meow == true) ? "true" : "false";
}
//----------------------------------------------------------------------------
ZAMassSquare::ZAMassSquare()
{
   M12_2 = 0, M1P_2 = 0, M2P_2 = 0;
}
//----------------------------------------------------------------------------
ZAMassSquare::ZAMassSquare(const ZAEventParameters &Event)
{
   ZALeptonVectors Vectors = ConvertAnglesToVectorsRoberto(Event);

   M12_2 = (Vectors.Lepton1 + Vectors.Lepton2).GetMass2();
   M1P_2 = (Vectors.Lepton1 + Vectors.Photon).GetMass2();
   M2P_2 = (Vectors.Lepton2 + Vectors.Photon).GetMass2();
}
//----------------------------------------------------------------------------
ZAMassSquare::ZAMassSquare(const ZALeptonVectors &Vectors)
{
   M12_2 = (Vectors.Lepton1 + Vectors.Lepton2).GetMass2();
   M1P_2 = (Vectors.Lepton1 + Vectors.Photon).GetMass2();
   M2P_2 = (Vectors.Lepton2 + Vectors.Photon).GetMass2();
}
//----------------------------------------------------------------------------
ZAMassSquare ZAMassSquare::FlipL1L2()
{
   ZAMassSquare NewOne;
   NewOne.M12_2 = M12_2;
   NewOne.M1P_2 = M2P_2;
   NewOne.M2P_2 = M1P_2;
   return NewOne;
}
//----------------------------------------------------------------------------





