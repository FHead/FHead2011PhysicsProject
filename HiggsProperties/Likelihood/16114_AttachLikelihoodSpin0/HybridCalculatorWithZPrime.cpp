//----------------------------------------------------------------------------
// Calculation of the hybrid method.  Result is proportional to pdf value.
// Author: Yi Chen (12173)
//----------------------------------------------------------------------------
#include "HybridCalculatorWithZPrime.h"
//----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
//----------------------------------------------------------------------------
HybridCalculator::HybridCalculator()
{
   Verbosity = VerboseLevel_Quiet;

   Efficiency12 = NULL;
   Efficiency34 = NULL;
   Smear12 = NULL;
   Smear34 = NULL;
   PTYDensity = NULL;

   ToleranceF = 1e-6;
   MaxDepthF = 20;
   IgnorePhi = true;

   SimpleMassIntegralWindowPlus = 0.5;
   SimpleMassIntegralWindowMinus = 0.5;
   SimpleMassIntegralStepPlus = 40;
   SimpleMassIntegralStepMinus = 40;
   SimpleMassIntegralAttractorStrengthPlus = 0;
   SimpleMassIntegralAttractorStrengthMinus = 0;

   ExpansionOrder = 2;

   LeptonReversal = false;
   RotatingLeptonReversal = false;

   DoDeltaMH = false;
   DeltaMH = 125;
   DoGaussMH = false;
   SigmaMH = 1;
   DoDiagonal = true;

   IntegralCMin = 0.75;
   IntegralCMax = 1.25;
   IntegralCStep = 20;

   IncludeSwapping = false;

   FlatApproximation = true;

   DebugPrintIntegrand = false;

   IgnoreTip = false;
   TipRangeFactor = 1;

   DoPTZero = false;
   
   ToleranceM1.clear();
   ToleranceM2.clear();   
   MaxDepthM1 = 30;
   MaxDepthM2 = 30;

   RecursiveMassIntegralM1Step = 20;
   RecursiveMassIntegralM1Window = 40;
   RecursiveMassIntegralM2Step = 20;
   RecursiveMassIntegralM2Window = 40;

   UseSmartCenter = false;

   ZP.VMass = 9.46;
   ZP.VWidth = 1;
   ZP.G1VL = -0.073348;
   ZP.G1VR = 0.073348;
   ZP.G2VL = -0.073348;
   ZP.G2VR = 0.073348;
}
//----------------------------------------------------------------------------
HybridCalculator::~HybridCalculator()
{
}
//----------------------------------------------------------------------------
HybridCalculator &HybridCalculator::operator =(const HybridCalculator &other)
{
   Verbosity = other.Verbosity;

   ToleranceF = other.ToleranceF;
   MaxDepthF = other.MaxDepthF;
   IgnorePhi = other.IgnorePhi;
   SimpleMassIntegralWindowPlus = other.SimpleMassIntegralWindowPlus;
   SimpleMassIntegralWindowMinus = other.SimpleMassIntegralWindowMinus;
   SimpleMassIntegralStepPlus = other.SimpleMassIntegralStepPlus;
   SimpleMassIntegralStepMinus = other.SimpleMassIntegralStepMinus;
   SimpleMassIntegralAttractorStrengthPlus = other.SimpleMassIntegralAttractorStrengthPlus;
   SimpleMassIntegralAttractorStrengthMinus = other.SimpleMassIntegralAttractorStrengthMinus;
   ExpansionOrder = other.ExpansionOrder;
   LeptonReversal = other.LeptonReversal;
   RotatingLeptonReversal = other.RotatingLeptonReversal;
   DoDeltaMH = other.DoDeltaMH;
   DeltaMH = other.DeltaMH;
   DoGaussMH = other.DoGaussMH;
   SigmaMH = other.SigmaMH;
   IntegralCMin = other.IntegralCMin;
   IntegralCMax = other.IntegralCMax;
   IntegralCStep = other.IntegralCStep;
   DoDiagonal = other.DoDiagonal;

   Efficiency12 = other.Efficiency12;
   Efficiency34 = other.Efficiency34;
   Smear12 = other.Smear12;
   Smear34 = other.Smear34;
   PTYDensity = other.PTYDensity;
   CalculateMEValue = other.CalculateMEValue;
   MECount = other.MECount;

   IncludeSwapping = other.IncludeSwapping;
   FlatApproximation = other.FlatApproximation;

   DebugPrintIntegrand = other.DebugPrintIntegrand;

   IgnoreTip = other.IgnoreTip;
   TipRangeFactor = other.TipRangeFactor;

   DoPTZero = other.DoPTZero;
 
   ToleranceM1 = other.ToleranceM1;
   ToleranceM2 = other.ToleranceM2; 
   MaxDepthM1 = other.MaxDepthM1;
   MaxDepthM2 = other.MaxDepthM2;

   RecursiveMassIntegralM1Step = other.RecursiveMassIntegralM1Step;
   RecursiveMassIntegralM1Window = other.RecursiveMassIntegralM1Window;
   RecursiveMassIntegralM2Step = other.RecursiveMassIntegralM2Step;
   RecursiveMassIntegralM2Window = other.RecursiveMassIntegralM2Window;

   UseSmartCenter = other.UseSmartCenter;

   ZP = other.ZP;

   return *this;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetVerbosity(VerboseLevel Value)
{
   Verbosity = Value;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetEfficiency12(double (*F)(double, double, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[HybridCalculator] Efficiency function on first lepton pair set to NULL." << std::endl;
      else
         std::cerr << "[HybridCalculator] Efficiency function on first lepton pair set." << std::endl;
   }

   Efficiency12 = F;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetEfficiency34(double (*F)(double, double, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[HybridCalculator] Efficiency function on second lepton pair set to NULL." << std::endl;
      else
         std::cerr << "[HybridCalculator] Efficiency function on second lepton pair set." << std::endl;
   }

   Efficiency34 = F;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetSmear12(double (*F)(FourVector &, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[HybridCalculator] Smearing function on first lepton pair set to NULL." << std::endl;
      else
         std::cerr << "[HybridCalculator] Smearing function on first lepton pair set." << std::endl;
   }

   Smear12 = F;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetSmear34(double (*F)(FourVector &, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[HybridCalculator] Smearing function on second lepton pair set to NULL." << std::endl;
      else
         std::cerr << "[HybridCalculator] Smearing function on second lepton pair set." << std::endl;
   }

   Smear34 = F;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetPTYDensity(double (*F)(double, double, double))
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(F == NULL)
         std::cerr << "[HybridCalculator] (PT,Y) density set to NULL." << std::endl;
      else
         std::cerr << "[HybridCalculator] (PT,Y) density set." << std::endl;
   }

   PTYDensity = F;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetMECalculator(double (*F)(LeptonVectors &, ZPrimeParameters &))
{
   if(F == NULL)
   {
      if(Verbosity >= VerboseLevel_Normal)
         std::cerr << "[HybridCalculator] Attempted to add a NULL ME function.  Do nothing." << std::endl;
      return;
   }

   CalculateMEValue.push_back(F);
   MECount = CalculateMEValue.size();

   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Added a new ME function.  Current count: " << MECount << std::endl;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetToleranceF(double Tolerance)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Tolerance on F functions set to " << Tolerance << "." << std::endl;

   ToleranceF = Tolerance;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetMaxDepthF(int Depth)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Max depth on F functions set to " << Depth << "." << std::endl;

   MaxDepthF = Depth;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetIgnorePhi(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(Decision == true)
         std::cerr << "[HybridCalculator] Don't use phi in the lepton efficiency." << std::endl;
      else
         std::cerr << "[HybridCalculator] Use phi in the lepton efficiency." << std::endl;
   }

   IgnorePhi = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetApplyEfficiencyAtEnd(bool Decision)
{
   std::cerr << "[HybridCalculator] Efficiency is always applied at the end!" << std::endl;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetSimpleMassIntegralWindow(double Window)
{
   SetSimpleMassIntegralWindow(true, Window);
   SetSimpleMassIntegralWindow(false, Window);
}
//----------------------------------------------------------------------------
void HybridCalculator::SetSimpleMassIntegralWindow(bool SumZ, double Window)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(DoDiagonal == true)
         std::cerr << "[HybridCalculator] Mass integration window for mass "
            << ((SumZ == true) ? "sum" : "difference") << " set to " << Window << "." << std::endl;
      else
         std::cerr << "[HybridCalculator] Mass integration window for mass "
            << ((SumZ == true) ? "M1" : "M2") << " set to " << Window << "." << std::endl;
   }

   if(SumZ == true)
      SimpleMassIntegralWindowPlus = Window;
   else
      SimpleMassIntegralWindowMinus = Window;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetSimpleMassIntegralStep(int Step)
{
   SetSimpleMassIntegralStep(true, Step);
   SetSimpleMassIntegralStep(false, Step);
}
//----------------------------------------------------------------------------
void HybridCalculator::SetSimpleMassIntegralStep(bool SumZ, int Step)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(DoDiagonal == true)
         std::cerr << "[HybridCalculator] Mass integration step count for mass "
            << ((SumZ == true) ? "sum" : "difference") << " set to " << Step << "." << std::endl;
      else
         std::cerr << "[HybridCalculator] Mass integration step count for mass "
            << ((SumZ == true) ? "M1" : "M2") << " set to " << Step << "." << std::endl;
   }

   if(SumZ == true)
      SimpleMassIntegralStepPlus = Step;
   else
      SimpleMassIntegralStepMinus = Step;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetExpansionOrder(int Value)
{
   ExpansionOrder = Value;

   if(Value < 0)
   {
      if(Verbosity >= VerboseLevel_Normal)
         std::cerr << "[HybridCalculator] Weird order requested." << std::endl;
      ExpansionOrder = 0;
   }
   else if(Value > 2)
   {
      if(Verbosity >= VerboseLevel_Normal)
         std::cerr << "[HybridCalculator] Currently we don't support orders greater than 2." << std::endl;
      ExpansionOrder = 2;
   }

   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Order set to " << ExpansionOrder << std::endl;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetLeptonReversal(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(Decision == true)
         std::cerr << "[HybridCalculator] Set lepton reversal to be true." << std::endl;
      else
         std::cerr << "[HybridCalculator] Don't use lepton reversal." << std::endl;
   }

   LeptonReversal = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetRotatingLeptonReversal(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(Decision == true)
         std::cerr << "[HybridCalculator] Set rotating lepton reversal to be true." << std::endl;
      else
         std::cerr << "[HybridCalculator] Use fixed lepton reversal." << std::endl;
   }

   RotatingLeptonReversal = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetDoDeltaMH(bool Decision, double Value)
{
   DoDeltaMH = Decision;
   DeltaMH = Value;

   if(Verbosity >= VerboseLevel_Normal)
   {
      if(DoDeltaMH == false)
         std::cerr << "[HybridCalculator] Don't use narrow-width approximation." << std::endl;
      else
         std::cerr << "[HybridCalculator] Use narrow-width approximation with MH = " << DeltaMH << std::endl;
   }

   if(DoGaussMH == true && DoDeltaMH == true)
   {
      if(Verbosity >= VerboseLevel_Normal)
         std::cerr << "[HybridCalculator] Set gauss-width approximation to false." << std::endl;
      DoGaussMH = false;
   }
}
//----------------------------------------------------------------------------
void HybridCalculator::SetDoGaussMH(bool Decision, double Value, double Width)
{
   DoGaussMH = Decision;
   DeltaMH = Value;
   SigmaMH = Width;

   if(Verbosity >= VerboseLevel_Normal)
   {
      if(DoGaussMH == false)
         std::cerr << "[HybridCalculator] Don't use gauss-width approximation." << std::endl;
      else
         std::cerr << "[HybridCalculator] Use gauss-width approximation with MH = " << DeltaMH
            << " and width = " << SigmaMH << std::endl;
   }

   if(DoGaussMH == true && DoDeltaMH == true)
   {
      if(Verbosity >= VerboseLevel_Normal)
         std::cerr << "[HybridCalculator] Set narrow-width approximation to false." << std::endl;
      DoDeltaMH = false;
   }
}
//----------------------------------------------------------------------------
void HybridCalculator::SetIntegralCRange(double Min, double Max)
{
   if(Min > Max)
   {
      std::cerr << "[HybridCalculator] Warning: min > max.  Swap the two for now" << std::endl;
      std::swap(Min, Max);
   }
   if(Min <= 0)
   {
      std::cerr << "[HybridCalculator] Warning: integral min < 0.  Do nothing." << std::endl;
      return;
   }
   if(Max <= 0)
   {
      std::cerr << "[HybridCalculator] Warning: integral max < 0.  Do nothing." << std::endl;
      return;
   }

   IntegralCMin = Min;
   IntegralCMax = Max;

   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Integration range for C's set to "
         << Min << " - " << Max << std::endl;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetIntegralCStep(int Step)
{
   if(Step <= 1)
   {
      std::cerr << "[HybridCalculator] Unreasonable value of initial step count in C's requested." << std::endl;
      Step = 20;
   }

   IntegralCStep = Step;

   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Step size set to " << IntegralCStep << "." << std::endl;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetAttractorStrength(double Strength)
{
   SetAttractorStrength(true, Strength);
   SetAttractorStrength(false, Strength);
}
//----------------------------------------------------------------------------
void HybridCalculator::SetAttractorStrength(bool SumZ, double Strength)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(DoDiagonal == true)
         std::cerr << "[HybridCalculator] Mass integration attractor strength for mass "
            << ((SumZ == true) ? "sum" : "difference") << " set to " << Strength << "." << std::endl;
      else
         std::cerr << "[HybridCalculator] Mass integration attractor strength for mass "
            << ((SumZ == true) ? "M1" : "M2") << " set to " << Strength << "." << std::endl;
   }

   if(SumZ == true)
      SimpleMassIntegralAttractorStrengthPlus = Strength;
   else
      SimpleMassIntegralAttractorStrengthMinus = Strength;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetDoDiagonal(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(Decision == true)
         std::cerr << "[HybridCalculator] Integrate along M1+M2 vs. M1-M2 directions." << std::endl;
      else
         std::cerr << "[HybridCalculator] Integrate along M1 vs. M2 directions." << std::endl;
   }

   DoDiagonal = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetIncludeSwapping(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(Decision == true)
         std::cerr << "[HybridCalculator] Calculate also swapped ME." << std::endl;
      else
         std::cerr << "[HybridCalculator] Don't calculate swapped ME." << std::endl;
   }

   IncludeSwapping = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetFlatApproximation(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(Decision == true)
         std::cerr << "[HybridCalculator] Use c1-c2-c3-c4 flat approxmation." << std::endl;
      else
         std::cerr << "[HybridCalculator] Include c1-c2-c3-c4 volume element in the calculation." << std::endl;
   }

   FlatApproximation = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetUsePPPP(bool Decision)
{
   std::cerr << "[HybridCalculator] p1-p2-p3-p4 option is not supported anymore!" << std::endl;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetDebugPrintIntegrand(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(Decision == true)
         std::cerr << "[HybridCalculator] DEBUG: print integrand." << std::endl;
      else
         std::cerr << "[HybridCalculator] DEBUG: don't print integrand." << std::endl;
   }

   DebugPrintIntegrand = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetIgnoreTip(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(Decision == true)
         std::cerr << "[HybridCalculator] Ignore tip integral" << std::endl;
      else
         std::cerr << "[HybridCalculator] Include tip integral" << std::endl;
   }

   IgnoreTip = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetTipRangeFactor(double Value)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Tip range factor set to " << Value << std::endl;

   TipRangeFactor = Value;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetDoPTZero(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(Decision == true)
         std::cerr << "[HybridCalculator] Require Generator level PT to be zero." << std::endl;
      else
         std::cerr << "[HybridCalculator] Generator level PT is free to float." << std::endl;
   }

   DoPTZero = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetRecursiveMassIntegralWindow(double Window)
{
   SetRecursiveMassIntegralWindow(true, Window);
   SetRecursiveMassIntegralWindow(false, Window);
}
//----------------------------------------------------------------------------
void HybridCalculator::SetRecursiveMassIntegralWindow(bool SumZ, double Window)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(DoDiagonal == true)
         std::cerr << "[HybridCalculator] Mass integration window for mass "
            << ((SumZ == true) ? "sum" : "difference") << " set to " << Window << "." << std::endl;
      else
         std::cerr << "[HybridCalculator] Mass integration window for mass "
            << ((SumZ == true) ? "M1" : "M2") << " set to " << Window << "." << std::endl;
   }

   if(SumZ == true)
      RecursiveMassIntegralM1Window = Window;
   else
      RecursiveMassIntegralM2Window = Window;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetRecursiveMassIntegralStep(int Step)
{
   SetRecursiveMassIntegralStep(true, Step);
   SetRecursiveMassIntegralStep(false, Step);
}
//----------------------------------------------------------------------------
void HybridCalculator::SetRecursiveMassIntegralStep(bool SumZ, int Step)
{
   if(Verbosity >= VerboseLevel_Normal)
   {
      if(DoDiagonal == true)
         std::cerr << "[HybridCalculator] Initial mass integration step count for mass "
            << ((SumZ == true) ? "sum" : "difference") << " set to " << Step << "." << std::endl;
      else
         std::cerr << "[HybridCalculator] Initial mass integration step count for mass "
            << ((SumZ == true) ? "M1" : "M2") << " set to " << Step << "." << std::endl;
   }

   if(SumZ == true)
      RecursiveMassIntegralM1Step = Step;
   else
      RecursiveMassIntegralM2Step = Step;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetRecursiveMaxDepthM1(int Depth)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Max depth on recursive M1 scan set to " << Depth << "." << std::endl;

   MaxDepthM1 = Depth;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetRecursiveMaxDepthM2(int Depth)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Max depth on recursive M2 scan set to " << Depth << "." << std::endl;

   MaxDepthM2 = Depth;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetRecursiveMaxToleranceM1(std::vector<double> Value)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Tolerance on recursive M1 scan has been set." << std::endl;

   ToleranceM1 = Value;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetRecursiveMaxToleranceM2(std::vector<double> Value)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Tolerance on recursive M2 scan has been set." << std::endl;

   ToleranceM2 = Value;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetUseSmartCenter(bool Decision)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] Smart center set to " << TextBool(Decision) << std::endl;

   UseSmartCenter = Decision;
}
//----------------------------------------------------------------------------
void HybridCalculator::SetZPrimeParameter(ZPrimeParameters &P)
{
   if(Verbosity >= VerboseLevel_Normal)
      std::cerr << "[HybridCalculator] ZPrime parameter set." << std::endl;

   ZP = P;
}
//----------------------------------------------------------------------------
void HybridCalculator::PrintSettings()
{
   PrintSettings(std::cout);
}
//----------------------------------------------------------------------------
void HybridCalculator::PrintSettings(std::ostream &out)
{
   out << "Summary of settings:" << std::endl;
   out << std::endl;

   if(Efficiency12 == NULL)   out << "Efficiency12: not set." << std::endl;
   else                       out << "Efficiency12: set." << std::endl;
   if(Efficiency34 == NULL)   out << "Efficiency34: not set." << std::endl;
   else                       out << "Efficiency34: set." << std::endl;
   if(Smear12 == NULL)        out << "Smear12: not set." << std::endl;
   else                       out << "Smear12: set." << std::endl;
   if(Smear34 == NULL)        out << "Smear34: not set." << std::endl;
   else                       out << "Smear34: set." << std::endl;
   if(PTYDensity == NULL)     out << "PTYDensity: not set." << std::endl;
   else                       out << "PTYDensity: set." << std::endl;

   out << "Number of ME: " << CalculateMEValue.size() << std::endl;

   out << "Tolerance on F: " << ToleranceF << std::endl;
   out << "Max depth on F: " << MaxDepthF << std::endl;

   out << "Ignore phi in efficiency: " << TextBool(IgnorePhi) << std::endl;

   out << "Scan mass in diagonal direction: " << TextBool(DoDiagonal) << std::endl;
   out << "Mass window: " << SimpleMassIntegralWindowPlus
      << ", " << SimpleMassIntegralWindowMinus << std::endl;
   out << "Mass steps: " << SimpleMassIntegralStepPlus
      << ", " << SimpleMassIntegralStepMinus << std::endl;
   out << "Mass attractor strength: " << SimpleMassIntegralAttractorStrengthPlus
      << ", " << SimpleMassIntegralAttractorStrengthMinus << std::endl;

   out << "Expansion order: " << ExpansionOrder << std::endl;

   out << "Do lepton reversal: " << TextBool(LeptonReversal) << std::endl;
   out << "Rotating lepton reversal: " << TextBool(RotatingLeptonReversal) << std::endl;

   out << "DoDeltaMH: " << TextBool(DoDeltaMH) << std::endl;
   out << "DoGaussMH: " << TextBool(DoGaussMH) << std::endl;

   if(DoDeltaMH == true)        out << "MH: set at " << DeltaMH << std::endl;
   else if(DoGaussMH == true)   out << "MH: set at " << DeltaMH << " with width " << SigmaMH << std::endl;
   else                         out << "MH: no prior distribution." << std::endl;

   out << "Integral range on c's limited to: " << IntegralCMin << " - " << IntegralCMax << std::endl;
   out << "Number of initial steps on c's: " << IntegralCStep << std::endl;

   out << "Include evaluation of swapping M1 and M2: " << TextBool(IncludeSwapping) << std::endl;

   if(FlatApproximation == true)
      out << "Jacobian treatment: c1-c2-c3-c4 flat" << std::endl;
   else
      out << "Jacobian treatment: include volume element" << std::endl;

   if(IgnoreTip == true)
      out << "Tip: ignore" << std::endl;
   else
      out << "Tip: include" << std::endl;
   out << "Tip range factor " << TipRangeFactor << std::endl;

   out << "Require GEN-level PT to be zero: " << TextBool(DoPTZero) << std::endl;
   
   out << "Recursive mass 1 tolerance set to [";
   for(int i = 0; i < (int)ToleranceM1.size(); i++)
   {
      if(i != 0)
         out << ", ";
      out << ToleranceM1[i];
   }
   out << "]" << std::endl;
   
   out << "Recursive mass 2 tolerance set to [";
   for(int i = 0; i < (int)ToleranceM2.size(); i++)
   {
      if(i != 0)
         out << ", ";
      out << ToleranceM2[i];
   }
   out << "]" << std::endl;
   
   out << "Recursive mass max depth set to (" << MaxDepthM1 << ", " << MaxDepthM2 << ")" << std::endl;
   out << "Recursive mass step set to (" << RecursiveMassIntegralM1Step
      << ", " << RecursiveMassIntegralM2Step << ")" << std::endl;
   out << "Recursive mass window set to (" << RecursiveMassIntegralM1Window
      << ", " << RecursiveMassIntegralM2Window << ")" << std::endl;

   out << "Smart center: " << TextBool(UseSmartCenter) << std::endl;

   out << std::endl;
}
//----------------------------------------------------------------------------
void HybridCalculator::TestOutput()
{
   EventParameters Point;
   Point.HMass = 125.0717827;
   Point.ZMass = 105.77198368;
   Point.Z2Mass = 15.5285557;
   Point.Phi0 = 3.014345815;
   Point.Theta0 = acos(0.1267741978);
   Point.Phi = 3.028885554;
   Point.Theta1 = acos(0.8313573548);
   Point.Theta2 = acos(-0.0468909004);
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

   LeptonVectors Leptons;
   Leptons.Lepton11.SetPtEtaPhi(14.624126, 0.7552305, 0.5874394);
   Leptons.Lepton12.SetPtEtaPhi(82.687938, 0.5519971, 3.1338023);
   Leptons.Lepton21.SetPtEtaPhi(19.936076, -0.020645, -1.480457);
   Leptons.Lepton22.SetPtEtaPhi(49.456566, 0.4155587, 2.7247681);

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
std::vector<double> HybridCalculator::SimpleMassIntegral(const EventParameters &TargetParameters)
{
   if(TargetParameters.HMass < TargetParameters.ZMass + TargetParameters.Z2Mass)
      return std::vector<double>(MECount);

   LeptonVectors TargetLeptons = ConvertAnglesToVectorsRoberto(TargetParameters);

   FourVector &L11 = TargetLeptons.Lepton11;
   FourVector &L12 = TargetLeptons.Lepton12;
   FourVector &L21 = TargetLeptons.Lepton21;
   FourVector &L22 = TargetLeptons.Lepton22;

   double RecoEfficiency =
      Efficiency12(L11.GetPT(), L11[3] / L11.GetP(), (IgnorePhi == false) ? L11.GetPhi() : 0)
      * Efficiency12(L12.GetPT(), L12[3] / L12.GetP(), (IgnorePhi == false) ? L12.GetPhi() : 0)
      * Efficiency34(L21.GetPT(), L21[3] / L21.GetP(), (IgnorePhi == false) ? L21.GetPhi() : 0)
      * Efficiency34(L22.GetPT(), L22[3] / L22.GetP(), (IgnorePhi == false) ? L22.GetPhi() : 0);
   
   if(RecoEfficiency < 1e-7)
      return std::vector<double>(MECount);

   if(RotatingLeptonReversal == true)
      LeptonReversal = !LeptonReversal;

   double MassWindowPlus = SimpleMassIntegralWindowPlus;
   double MassWindowMinus = SimpleMassIntegralWindowMinus;
   int MassStepPlus = SimpleMassIntegralStepPlus;
   int MassStepMinus = SimpleMassIntegralStepMinus;

   double MassPlus[1001] = {0}, MassMinus[1001] = {0};
   double MassCenterPlus, MassCenterMinus;
   if(UseSmartCenter == false)
   {
      if(DoDiagonal == true)
      {
         MassCenterPlus = TargetParameters.ZMass + TargetParameters.Z2Mass;
         MassCenterMinus = TargetParameters.ZMass - TargetParameters.Z2Mass;
      }
      else
      {
         MassCenterPlus = TargetParameters.ZMass;
         MassCenterMinus = TargetParameters.Z2Mass;
      }
      if(DoDeltaMH == true)
      {
         MassCenterPlus = MassCenterPlus / TargetParameters.HMass * DeltaMH;
         MassCenterMinus = MassCenterMinus / TargetParameters.HMass * DeltaMH;
      }
   }
   else
   {
      std::pair<double, double> CenterResult = GuessCenter(TargetParameters);
      if(DoDiagonal == false)
      {
         MassCenterPlus = CenterResult.first;
         MassCenterMinus = CenterResult.second;
      }
      else
      {
         MassCenterPlus = CenterResult.first + CenterResult.second;
         MassCenterMinus = CenterResult.first - CenterResult.second;
      }
   }

   FillMassPosition(MassStepPlus, MassCenterPlus, MassWindowPlus,
      SimpleMassIntegralAttractorStrengthPlus, MassPlus);
   FillMassPosition(MassStepMinus, MassCenterMinus, MassWindowMinus,
      SimpleMassIntegralAttractorStrengthMinus, MassMinus);

   double FactorsPlus[1001] = {0}, FactorsMinus[1001] = {0};
   FillMassWeights(MassStepPlus, MassPlus, FactorsPlus);
   FillMassWeights(MassStepMinus, MassMinus, FactorsMinus);

   CentralParameters = TargetParameters,
   CentralParametersAlt = TargetParameters,
   CentralParametersLeft = TargetParameters,
   CentralParametersRight = TargetParameters;

   std::vector<double> Integral(MECount);
   RecoMM = MassSquare(TargetLeptons);
   // MassSquare FlippedRecoMM = RecoMM.FlipZ1Z2();

   if(DoDeltaMH == true)
   {
      if(fabs(cos(TargetParameters.Theta1)) < fabs(cos(TargetParameters.Theta2)))
         FFFirstZ = true;
      else
         FFFirstZ = false;

      FFFirstZ = true;   // DEBUG
   }

   for(int iMPlus = 0; iMPlus <= MassStepPlus; iMPlus++)
   {
      double ZMassPlus = MassPlus[iMPlus];

      for(int iMMinus = 0; iMMinus <= MassStepMinus; iMMinus++)
      {
         double ZMassMinus = MassMinus[iMMinus];

         double ZMass, Z2Mass;

         if(DoDiagonal == true)
            ZMass = (ZMassPlus + ZMassMinus) / 2, Z2Mass = (ZMassPlus - ZMassMinus) / 2;
         else
            ZMass = ZMassPlus, Z2Mass = ZMassMinus;

         if(ZMass <= 0 || Z2Mass <= 0)
            continue;
         if(DoDeltaMH == true && ZMass + Z2Mass >= DeltaMH)   // gen-level config doesn't exist
            continue;

         // Prepare!
         if(PrepareForIntegral(TargetParameters, ZMass, Z2Mass) == false)
            continue;

         // Do calculation for this mass point
         std::vector<double> Contribution(MECount);
         CalculateIntegrand(TargetParameters, CentralParameters, CentralParametersAlt,
            CentralParametersLeft, CentralParametersRight, Contribution);

         if(DebugPrintIntegrand == true)
            std::cout << iMPlus << " " << iMMinus << " "
               << ZMass << " " << Z2Mass << " " << Contribution[0] << std::endl;

         // Add stuff to integral
         for(int i = 0; i < MECount; i++)
         {
            if(DoDiagonal == true)
               Integral[i] = Integral[i] + FactorsPlus[iMPlus] * FactorsMinus[iMMinus] * Contribution[i] / 2;
            else
               Integral[i] = Integral[i] + FactorsPlus[iMPlus] * FactorsMinus[iMMinus] * Contribution[i];
         }
      }
   }

   double RecoJ12 = VolumeElement::EstimateVolumeFull5(TargetParameters);
   for(int i = 0; i < MECount; i++)
      Integral[i] = Integral[i] / RecoJ12;

   if(DebugPrintIntegrand == true)
      std::cout << "RecoJ12 = " << RecoJ12 << std::endl;

   if(DebugPrintIntegrand == true)
      std::cout << "RecoEfficiency = " << RecoEfficiency << std::endl;

   for(int i = 0; i < MECount; i++)
      Integral[i] = Integral[i] * RecoEfficiency;

   return Integral;
}
//----------------------------------------------------------------------------
std::vector<double> HybridCalculator::RecursiveMassIntegral(const EventParameters &TargetParameters)
{
   std::vector<double> Integral(MECount);
   for(int i = 0; i < MECount; i++)
      Integral[i] = 0;

   if((int)ToleranceM1.size() < MECount)
      ToleranceM1.insert(ToleranceM1.end(), MECount - ToleranceM1.size(), 1);
   if((int)ToleranceM2.size() < MECount)
      ToleranceM2.insert(ToleranceM2.end(), MECount - ToleranceM2.size(), 1);

   LeptonVectors TargetLeptons = ConvertAnglesToVectorsRoberto(TargetParameters);
   RecoMM = MassSquare(TargetLeptons);
   
   double RecoJ12 = VolumeElement::EstimateVolumeFull5(TargetParameters);
   
   FourVector &L11 = TargetLeptons.Lepton11;   FourVector &L12 = TargetLeptons.Lepton12;
   FourVector &L21 = TargetLeptons.Lepton21;   FourVector &L22 = TargetLeptons.Lepton22;
   double RecoEfficiency =
      Efficiency12(L11.GetPT(), L11[3] / L11.GetP(), (IgnorePhi == false) ? L11.GetPhi() : 0)
      * Efficiency12(L12.GetPT(), L12[3] / L12.GetP(), (IgnorePhi == false) ? L12.GetPhi() : 0)
      * Efficiency34(L21.GetPT(), L21[3] / L21.GetP(), (IgnorePhi == false) ? L21.GetPhi() : 0)
      * Efficiency34(L22.GetPT(), L22[3] / L22.GetP(), (IgnorePhi == false) ? L22.GetPhi() : 0);

   if(RecoEfficiency < 1e-7)
      return Integral;

   RecursiveMassIntegralUniversalFactor = RecoEfficiency / RecoJ12;

   double M1Center = (DoDiagonal == true) ? (TargetParameters.ZMass + TargetParameters.Z2Mass) : TargetParameters.ZMass;
   double M2Center = (DoDiagonal == true) ? (TargetParameters.ZMass - TargetParameters.Z2Mass) : TargetParameters.Z2Mass;

   if(DoDeltaMH == true)
   {
      M1Center = M1Center * DeltaMH / TargetParameters.HMass;
      M2Center = M2Center * DeltaMH / TargetParameters.HMass;
   }

   RecursiveMassIntegralM1Min = M1Center - RecursiveMassIntegralM1Window / 2;
   RecursiveMassIntegralM1Max = M1Center + RecursiveMassIntegralM1Window / 2;
   RecursiveMassIntegralM2Min = M2Center - RecursiveMassIntegralM2Window / 2;
   RecursiveMassIntegralM2Max = M2Center + RecursiveMassIntegralM2Window / 2;

   double MMin = RecursiveMassIntegralM1Min;
   double MMax = RecursiveMassIntegralM1Max;

   std::vector<double> fa(MECount), fc(MECount), fb(MECount), Iab(MECount);
   for(int iS = 0; iS < RecursiveMassIntegralM1Step; iS++)
   {
      double a = (MMax - MMin) / RecursiveMassIntegralM1Step * iS + MMin;
      double b = (MMax - MMin) / RecursiveMassIntegralM1Step * (iS + 1) + MMin;
      double c = (a + b) / 2;

      if(iS == 0)
         CalculateMass1Integrand(TargetParameters, a, fa);
      CalculateMass1Integrand(TargetParameters, c, fc);
      CalculateMass1Integrand(TargetParameters, b, fb);

      for(int i = 0; i < MECount; i++)
         Iab[i] = (fa[i] + fc[i] * 4 + fb[i]) / 6 * (b - a);

      AdaptiveMass1Integral(TargetParameters, Iab, a, b, fa, fc, fb, 1.0 / RecursiveMassIntegralM1Step, 0);

      for(int i = 0; i < MECount; i++)
         Integral[i] = Integral[i] + Iab[i];

      fb = fa;
   }
   
   for(int i = 0; i < MECount; i++)
      Integral[i] = Integral[i] * RecoEfficiency / RecoJ12;

   return Integral;
}
//----------------------------------------------------------------------------
std::vector<double> HybridCalculator::PassThroughMode(const EventParameters &TargetParameters)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(TargetParameters);

   double PTYWeight = 1;
   FourVector Total = Leptons.GetTotal();
   if(PTYDensity != NULL)
      PTYWeight = PTYDensity(Total.GetPT(), Total.GetY(), Total.GetMass2());

   std::cout << "PTY " << PTYWeight << std::endl;

   LeptonVectors SwappedLeptons = Leptons.FlipZ1Z2();

   Leptons = GoToRest(Leptons);
   SwappedLeptons = GoToRest(SwappedLeptons);

   std::vector<double> Result(CalculateMEValue.size());

   for(int i = 0; i < (int)CalculateMEValue.size(); i++)
   {
      Result[i] = (*CalculateMEValue[i])(Leptons, ZP);
      if(IncludeSwapping == true)
         Result[i] = Result[i] + (*CalculateMEValue[i])(SwappedLeptons, ZP);

      Result[i] = Result[i] * PTYWeight;
   }

   return Result;
}
//----------------------------------------------------------------------------
void HybridCalculator::AdaptiveMass1Integral(const EventParameters &TargetParameters, std::vector<double> &Iab,
   double MBa, double MBb, std::vector<double> &fa, std::vector<double> &fc, std::vector<double> &fb, double ToleranceFactor, int Depth)
{
   if(Depth >= MaxDepthM1)
      return;

   double MBc = (MBa + MBb) / 2;
   std::vector<double> fd(MECount);   CalculateMass1Integrand(TargetParameters, (MBa + MBc) / 2, fd);
   std::vector<double> fe(MECount);   CalculateMass1Integrand(TargetParameters, (MBc + MBb) / 2, fe);

   std::vector<double> Iac(MECount);   for(int i = 0; i < MECount; i++)   Iac[i] = (fa[i] + fd[i] * 4 + fc[i]) / 6 * (MBc - MBa);
   std::vector<double> Icb(MECount);   for(int i = 0; i < MECount; i++)   Icb[i] = (fb[i] + fe[i] * 4 + fb[i]) / 6 * (MBb - MBc);

   bool Good = true;
   for(int i = 0; i < MECount && Good == true; i++)
      if(fabs(Iab[i] - Iac[i] - Icb[i]) * RecursiveMassIntegralUniversalFactor > ToleranceM1[i] * ToleranceFactor * 10)
         Good = false;

   if(Good == false)
   {
      AdaptiveMass1Integral(TargetParameters, Iac, MBa, MBc, fa, fd, fc, ToleranceFactor / 2, Depth + 1);
      AdaptiveMass1Integral(TargetParameters, Icb, MBc, MBb, fc, fe, fb, ToleranceFactor / 2, Depth + 1);
   }

   for(int i = 0; i < MECount; i++)
      Iab[i] = Iac[i] + Icb[i];
}
//----------------------------------------------------------------------------
void HybridCalculator::CalculateMass1Integrand(const EventParameters &TargetParameters, double MA, std::vector<double> &Result)
{
   int ResultSize = Result.size();
   for(int i = 0; i < ResultSize; i++)
      Result[i] = 0;

   double MMin = RecursiveMassIntegralM2Min;
   double MMax = RecursiveMassIntegralM2Max;

   std::vector<double> fa(MECount), fc(MECount), fb(MECount), Iab(MECount);
   for(int iS = 0; iS < RecursiveMassIntegralM2Step; iS++)
   {
      double a = (MMax - MMin) / RecursiveMassIntegralM2Step * iS + MMin;
      double b = (MMax - MMin) / RecursiveMassIntegralM2Step * (iS + 1) + MMin;
      double c = (a + b) / 2;

      if(iS == 0)
         CalculateMass2Integrand(TargetParameters, MA, a, fa);
      CalculateMass2Integrand(TargetParameters, MA, c, fc);
      CalculateMass2Integrand(TargetParameters, MA, b, fb);

      for(int i = 0; i < MECount; i++)
         Iab[i] = (fa[i] + fc[i] * 4 + fb[i]) / 6 * (b - a);

      AdaptiveMass2Integral(TargetParameters, MA, Iab, a, b, fa, fc, fb, 1.0 / RecursiveMassIntegralM2Step, 0);

      for(int i = 0; i < MECount; i++)
         Result[i] = Result[i] + Iab[i];

      fb = fa;
   }
   
   std::cout << "M1 " << MA << " " << Result[0] << std::endl;
}
//----------------------------------------------------------------------------
void HybridCalculator::AdaptiveMass2Integral(const EventParameters &TargetParameters, double MA, std::vector<double> &Iab,
   double MBa, double MBb, std::vector<double> &fa, std::vector<double> &fc, std::vector<double> &fb, double ToleranceFactor, int Depth)
{
   if(Depth >= MaxDepthM2)
      return;

   double MBc = (MBa + MBb) / 2;
   std::vector<double> fd(MECount);   CalculateMass2Integrand(TargetParameters, MA, (MBa + MBc) / 2, fd);
   std::vector<double> fe(MECount);   CalculateMass2Integrand(TargetParameters, MA, (MBc + MBb) / 2, fe);

   std::vector<double> Iac(MECount);   for(int i = 0; i < MECount; i++)   Iac[i] = (fa[i] + fd[i] * 4 + fc[i]) / 6 * (MBc - MBa);
   std::vector<double> Icb(MECount);   for(int i = 0; i < MECount; i++)   Icb[i] = (fb[i] + fe[i] * 4 + fb[i]) / 6 * (MBb - MBc);

   bool Good = true;
   for(int i = 0; i < MECount && Good == true; i++)
      if(fabs(Iab[i] - Iac[i] - Icb[i]) * RecursiveMassIntegralUniversalFactor > ToleranceM2[i] * ToleranceFactor * 10)
         Good = false;

   if(Good == false)
   {
      AdaptiveMass2Integral(TargetParameters, MA, Iac, MBa, MBc, fa, fd, fc, ToleranceFactor / 2, Depth + 1);
      AdaptiveMass2Integral(TargetParameters, MA, Icb, MBc, MBb, fc, fe, fb, ToleranceFactor / 2, Depth + 1);
   }

   for(int i = 0; i < MECount; i++)
      Iab[i] = Iac[i] + Icb[i];
}
//----------------------------------------------------------------------------
void HybridCalculator::CalculateMass2Integrand(const EventParameters &TargetParameters, double MA, double MB, std::vector<double> &Result)
{
   int ResultSize = Result.size();
   for(int i = 0; i < ResultSize; i++)
      Result[i] = 0;

   double ZMass = (DoDiagonal == true) ? ((MA + MB) / 2) : MA;
   double Z2Mass = (DoDiagonal == true) ? ((MA - MB) / 2) : MB;

   if(ZMass <= 0 || Z2Mass <= 0)
      return;
   if(DoDeltaMH == true && ZMass + Z2Mass >= DeltaMH)   // gen-level config doesn't exist
      return;

   // Prepare!
   if(PrepareForIntegral(TargetParameters, ZMass, Z2Mass) == false)
      return;
   
   // Do calculation for this mass point
   CalculateIntegrand(TargetParameters, CentralParameters, CentralParametersAlt,
      CentralParametersLeft, CentralParametersRight, Result);

   if(DebugPrintIntegrand == true)
      std::cout << ZMass << " " << Z2Mass << " " << Result[0] << std::endl;

   if(DoDiagonal == true)
      for(int i = 0; i < MECount; i++)
         Result[i] = Result[i] / 2;
}
//----------------------------------------------------------------------------
void HybridCalculator::CalculateIntegrand(const EventParameters &TargetParameters,
   const EventParameters &CentralParameters, const EventParameters &CentralParametersAlt,
   const EventParameters &CentralParametersLeft, const EventParameters &CentralParametersRight,
   std::vector<double> &Result)
{
   if(DoDeltaMH == false && DoPTZero == false)
   {
      static std::vector<double> ME0(MECount), B1(MECount), B3(MECount), B11(MECount), B13(MECount), B33(MECount);

      CalculateMEs(CentralParameters, ME0, B1, B3, B11, B13, B33);

      TempLeptons = CentralLeptons;

      double CM1 = CentralParameters.ZMass, TM1 = TargetParameters.ZMass;
      double CM2 = CentralParameters.Z2Mass, TM2 = TargetParameters.Z2Mass;

      double F0Z1 = (ExpansionOrder >= 0) ? CalculateF(CM1, TM1, 0, true) : 0;
      double F1Z1 = (ExpansionOrder >= 1) ? CalculateF(CM1, TM1, 1, true) : 0;
      double F2Z1 = (ExpansionOrder >= 2) ? CalculateF(CM1, TM1, 2, true) : 0;
      double F0Z2 = (ExpansionOrder >= 0) ? CalculateF(CM2, TM2, 0, false) : 0;
      double F1Z2 = (ExpansionOrder >= 1) ? CalculateF(CM2, TM2, 1, false) : 0;
      double F2Z2 = (ExpansionOrder >= 2) ? CalculateF(CM2, TM2, 2, false) : 0;
      
      for(int i = 0; i < MECount; i++)
      {
         switch(ExpansionOrder)
         {
            case 0:
               Result[i] = ME0[i] * F0Z1 * F0Z2;
               break;
            case 1:
               Result[i] = (ME0[i] * F0Z1 * F0Z2 + B1[i] * F1Z1 * F0Z2 + B3[i] * F0Z1 * F1Z2);
               break;
            case 2:
               Result[i] = (ME0[i] * F0Z1 * F0Z2 + B1[i] * F1Z1 * F0Z2 + B3[i] * F0Z1 * F1Z2
                  + 0.5 * B11[i] * F2Z1 * F0Z2 + 1 * B13[i] * F1Z1 * F1Z2 + 0.5 * B33[i] * F0Z1 * F2Z2);
               break;
            default:
               Result[i] = 0;
               break;
         }

         Result[i] = Result[i] * CM1 * CM2;
      }
   }
   else if(DoDeltaMH == false && DoPTZero == true)
   {
      double CM1 = CentralParameters.ZMass, TM1 = TargetParameters.ZMass;
      double CM2 = CentralParameters.Z2Mass, TM2 = TargetParameters.Z2Mass;

      LeptonVectors TargetLeptons = ConvertAnglesToVectorsRoberto(TargetParameters);

      double A1 = TargetLeptons.Lepton11[1];
      double A2 = TargetLeptons.Lepton12[1] * CM1 * CM1 / TM1 / TM1;
      double A3 = TargetLeptons.Lepton21[1];
      double A4 = TargetLeptons.Lepton22[1] * CM2 * CM2 / TM2 / TM2;

      double B1 = TargetLeptons.Lepton11[2];
      double B2 = TargetLeptons.Lepton12[2] * CM1 * CM1 / TM1 / TM1;
      double B3 = TargetLeptons.Lepton21[2];
      double B4 = TargetLeptons.Lepton22[2] * CM2 * CM2 / TM2 / TM2;

      double c1_1 = (-2*A3*A4*B1*B2 + A2*A4*B1*B3 + A1*A4*B2*B3 - std::pow(A4,2)*std::pow(B3,2) +
            A2*A3*B1*B4 + A1*A3*B2*B4 - 2*A1*A2*B3*B4 + 2*A3*A4*B3*B4 -
            std::pow(A3,2)*std::pow(B4,2) + (-(A4*B3) + A3*B4)*
            std::sqrt(std::pow(A2,2)*std::pow(B1,2) + 4*A3*A4*B1*B2 + std::pow(A1*B2 - A4*B3,2) -
               2*A3*(A1*B2 + A4*B3)*B4 + std::pow(A3,2)*std::pow(B4,2) -
               2*A2*(A1*B1*B2 + A4*B1*B3 + A3*B1*B4 - 2*A1*B3*B4))) /
         (2.*(A3*B2 - A2*B3)*(A4*B2 - A2*B4));
      double c1_2 = (-2*A3*A4*B1*B2 + A2*A4*B1*B3 + A1*A4*B2*B3 - std::pow(A4,2)*std::pow(B3,2) +
            A2*A3*B1*B4 + A1*A3*B2*B4 - 2*A1*A2*B3*B4 + 2*A3*A4*B3*B4 -
            std::pow(A3,2)*std::pow(B4,2) + (A4*B3 - A3*B4)*
            std::sqrt(std::pow(A2,2)*std::pow(B1,2) + 4*A3*A4*B1*B2 + std::pow(A1*B2 - A4*B3,2) -
               2*A3*(A1*B2 + A4*B3)*B4 + std::pow(A3,2)*std::pow(B4,2) -
               2*A2*(A1*B1*B2 + A4*B1*B3 + A3*B1*B4 - 2*A1*B3*B4)))/
         (2.*(A3*B2 - A2*B3)*(A4*B2 - A2*B4));

      if(c1_1 < 0)   c1_1 = 0.0001;
      if(c1_2 < 0)   c1_2 = 0.0001;

      c1_1 = sqrt(c1_1);
      c1_2 = sqrt(c1_2);

      double c3_1 = (A3*B1 - A1*B3 + A3*B2*std::pow(c1_1,2) - A2*B3*std::pow(c1_1,2))/((A4*B3 - A3*B4)*c1_1);
      double c3_2 = (A3*B1 - A1*B3 + A3*B2*std::pow(c1_2,2) - A2*B3*std::pow(c1_2,2))/((A4*B3 - A3*B4)*c1_2);

      double c2_1 = TM1 * TM1 / CM1 / CM1 / c1_1;
      double c2_2 = TM1 * TM1 / CM1 / CM1 / c1_2;

      double c4_1 = TM2 * TM2 / CM2 / CM2 / c3_1;
      double c4_2 = TM2 * TM2 / CM2 / CM2 / c3_2;

      LeptonVectors GenLeptons1, GenLeptons2;
      GenLeptons1.Lepton11 = TargetLeptons.Lepton11 / c1_1;   GenLeptons2.Lepton11 = TargetLeptons.Lepton11 / c1_2;
      GenLeptons1.Lepton12 = TargetLeptons.Lepton12 / c2_1;   GenLeptons2.Lepton12 = TargetLeptons.Lepton12 / c2_2;
      GenLeptons1.Lepton21 = TargetLeptons.Lepton21 / c3_1;   GenLeptons2.Lepton21 = TargetLeptons.Lepton21 / c3_2;
      GenLeptons1.Lepton22 = TargetLeptons.Lepton22 / c4_1;   GenLeptons2.Lepton22 = TargetLeptons.Lepton22 / c4_2;

      LeptonVectors SwappedGenLeptons1 = GenLeptons1.FlipZ1Z2();
      LeptonVectors SwappedGenLeptons2 = GenLeptons2.FlipZ1Z2();

      LeptonVectors RestGenLeptons1, RestGenLeptons2, SwappedRestGenLeptons1, SwappedRestGenLeptons2;
      RestGenLeptons1 = GoToRest(GenLeptons1);
      RestGenLeptons2 = GoToRest(GenLeptons2);
      SwappedRestGenLeptons1 = GoToRest(SwappedGenLeptons1);
      SwappedRestGenLeptons2 = GoToRest(SwappedGenLeptons2);

      EventParameters GenEvent1, GenEvent2, SwappedGenEvent1, SwappedGenEvent2;
      GenEvent1 = ConvertVectorsToAnglesRoberto(GenLeptons1);
      GenEvent2 = ConvertVectorsToAnglesRoberto(GenLeptons2);
      SwappedGenEvent1 = ConvertVectorsToAnglesRoberto(SwappedGenLeptons1);
      SwappedGenEvent2 = ConvertVectorsToAnglesRoberto(SwappedGenLeptons2);

      FourVector Total1 = GenLeptons1.GetTotal(), Total2 = GenLeptons2.GetTotal();

      double PTLepton1 = Total1.GetPT();   double YLepton1 = Total1.GetY();   double SLepton1 = Total1.GetMass2();
      double PTLepton2 = Total2.GetPT();   double YLepton2 = Total2.GetY();   double SLepton2 = Total2.GetMass2();

      double Factor1 = 1, Factor2 = 1;

      Factor1 = Factor1 * Smear12(GenLeptons1.Lepton11, c1_1 - 1) * Smear12(GenLeptons1.Lepton12, c2_1 - 1);
      Factor1 = Factor1 * Smear34(GenLeptons1.Lepton21, c3_1 - 1) * Smear34(GenLeptons1.Lepton22, c4_1 - 1);
      Factor2 = Factor2 * Smear12(GenLeptons2.Lepton11, c1_2 - 1) * Smear12(GenLeptons2.Lepton12, c2_2 - 1);
      Factor2 = Factor2 * Smear34(GenLeptons2.Lepton21, c3_2 - 1) * Smear34(GenLeptons2.Lepton22, c4_2 - 1);

      double P1x = TargetLeptons.Lepton11[1];                        double P1y = TargetLeptons.Lepton11[2];
      double P2x = TargetLeptons.Lepton12[1];                        double P2y = TargetLeptons.Lepton12[2];
      double P3x = TargetLeptons.Lepton21[1];                        double P3y = TargetLeptons.Lepton21[2];
      double P4x = TargetLeptons.Lepton22[1];                        double P4y = TargetLeptons.Lepton22[2];

      double Jacobian1 = (c2_1*(c4_1*P1y*P3x - c4_1*P1x*P3y - c3_1*P1y*P4x + \
                   c3_1*P1x*P4y) + c1_1*\
             (-(c4_1*P2y*P3x) + c4_1*P2x*P3y + c3_1*P2y*P4x - \
                      c3_1*P2x*P4y))*std::pow(c1_1,-3)*std::pow(c2_1,-3)*std::pow(c3_1,-3)*\
            std::pow(c4_1,-3)*std::pow(TM1,2)*std::pow(TM2,2);
      double Jacobian2 = (c2_2*(c4_2*P1y*P3x - c4_2*P1x*P3y - c3_2*P1y*P4x + \
                   c3_2*P1x*P4y) + c1_2*\
             (-(c4_2*P2y*P3x) + c4_2*P2x*P3y + c3_2*P2y*P4x - \
                      c3_2*P2x*P4y))*std::pow(c1_2,-3)*std::pow(c2_2,-3)*std::pow(c3_2,-3)*\
            std::pow(c4_2,-3)*std::pow(TM1,2)*std::pow(TM2,2);

      if(Jacobian1 < 0)   Jacobian1 = -Jacobian1;
      if(Jacobian2 < 0)   Jacobian2 = -Jacobian2;

      Factor1 = Factor1 / c1_1 / c1_1 / c2_1 / c2_1 / c3_1 / c3_1 / c4_1 / c4_1;
      Factor2 = Factor2 / c1_2 / c1_2 / c2_2 / c2_2 / c3_2 / c3_2 / c4_2 / c4_2;
      Factor1 = Factor1 / Jacobian1;
      Factor2 = Factor2 / Jacobian2;

      Factor1 = Factor1 * TargetLeptons.Lepton11.GetP() / GenLeptons1.Lepton11.GetP();
      Factor1 = Factor1 * TargetLeptons.Lepton12.GetP() / GenLeptons1.Lepton12.GetP();
      Factor1 = Factor1 * TargetLeptons.Lepton21.GetP() / GenLeptons1.Lepton21.GetP();
      Factor1 = Factor1 * TargetLeptons.Lepton22.GetP() / GenLeptons1.Lepton22.GetP();
      Factor2 = Factor2 * TargetLeptons.Lepton11.GetP() / GenLeptons2.Lepton11.GetP();
      Factor2 = Factor2 * TargetLeptons.Lepton12.GetP() / GenLeptons2.Lepton12.GetP();
      Factor2 = Factor2 * TargetLeptons.Lepton21.GetP() / GenLeptons2.Lepton21.GetP();
      Factor2 = Factor2 * TargetLeptons.Lepton22.GetP() / GenLeptons2.Lepton22.GetP();

      double VolumeElement1 = VolumeElement::EstimateVolumeFull5(GenEvent1);
      double VolumeElement2 = VolumeElement::EstimateVolumeFull5(GenEvent2);
      double SwappedVolumeElement1 = VolumeElement::EstimateVolumeFull5(SwappedGenEvent1);
      double SwappedVolumeElement2 = VolumeElement::EstimateVolumeFull5(SwappedGenEvent2);

      bool FirstOneGood = true, SecondOneGood = true;
      if(c1_1 < IntegralCMin || c1_1 > IntegralCMax || c1_1 != c1_1)   FirstOneGood = false;
      if(c2_1 < IntegralCMin || c2_1 > IntegralCMax || c2_1 != c2_1)   FirstOneGood = false;
      if(c3_1 < IntegralCMin || c3_1 > IntegralCMax || c3_1 != c3_1)   FirstOneGood = false;
      if(c4_1 < IntegralCMin || c4_1 > IntegralCMax || c4_1 != c4_1)   FirstOneGood = false;
      if(c1_2 < IntegralCMin || c1_2 > IntegralCMax || c1_2 != c1_2)   SecondOneGood = false;
      if(c2_2 < IntegralCMin || c2_2 > IntegralCMax || c2_2 != c2_2)   SecondOneGood = false;
      if(c3_2 < IntegralCMin || c3_2 > IntegralCMax || c3_2 != c3_2)   SecondOneGood = false;
      if(c4_2 < IntegralCMin || c4_2 > IntegralCMax || c4_2 != c4_2)   SecondOneGood = false;

      for(int i = 0; i < MECount; i++)
      {
         Result[i] = 0;

         if(FirstOneGood == true)
            Result[i] = Result[i] + VolumeElement1 * CalculateMEValue[i](RestGenLeptons1, ZP) * PTYDensity(PTLepton1, YLepton1, SLepton1) * Factor1;
         if(SecondOneGood == true)
            Result[i] = Result[i] + VolumeElement2 * CalculateMEValue[i](RestGenLeptons2, ZP) * PTYDensity(PTLepton2, YLepton2, SLepton2) * Factor2;

         if(IncludeSwapping == true)
         {
            if(FirstOneGood == true)
               Result[i] = Result[i] + SwappedVolumeElement1 * CalculateMEValue[i](SwappedRestGenLeptons1, ZP) * PTYDensity(PTLepton1, YLepton1, SLepton1) * Factor1;
            if(SecondOneGood == true)
               Result[i] = Result[i] + SwappedVolumeElement2 * CalculateMEValue[i](SwappedRestGenLeptons2, ZP) * PTYDensity(PTLepton2, YLepton2, SLepton2) * Factor2;
         }

         Result[i] = Result[i] * CM1 * CM2;
      }
   }
   else if(DoDeltaMH == true && DoPTZero == false)   // With delta(MH = XXX) approximation
   {
      static std::vector<double> ME0_1(MECount), B1_1(MECount), B11_1(MECount);
      static std::vector<double> ME0_2(MECount), B1_2(MECount), B11_2(MECount);
      static std::vector<double> ME0_L(MECount), B1_L(MECount), B11_L(MECount);
      static std::vector<double> ME0_R(MECount), B1_R(MECount), B11_R(MECount);

      CalculateMEsDeltaMH(CentralParameters, ME0_1, B1_1, B11_1, FFFirstZ, true, false);
      CalculateMEsDeltaMH(CentralParametersAlt, ME0_2, B1_2, B11_2, FFFirstZ, false, false);
      CalculateMEsDeltaMH(CentralParametersRight, ME0_R, B1_R, B11_R, FFFirstZ, true, true);
      CalculateMEsDeltaMH(CentralParametersLeft, ME0_L, B1_L, B11_L, FFFirstZ, false, true);

      double CM1 = CentralParameters.ZMass, TM1 = TargetParameters.ZMass;
      double CM2 = CentralParameters.Z2Mass, TM2 = TargetParameters.Z2Mass;

      TempLeptons = CentralLeptons;
      double F0Z1F0Z2_1 = (ExpansionOrder >= 0) ? CalculateFF(CM1, TM1, CM2, TM2, 0, 0, FFFirstZ, true, false) : 0;
      double F1Z1F0Z2_1 = (ExpansionOrder >= 1) ? CalculateFF(CM1, TM1, CM2, TM2, 1, 0, FFFirstZ, true, false) : 0;
      double F2Z1F0Z2_1 = (ExpansionOrder >= 2) ? CalculateFF(CM1, TM1, CM2, TM2, 2, 0, FFFirstZ, true, false) : 0;

      TempLeptons = CentralLeptonsAlt;
      double F0Z1F0Z2_2 = (ExpansionOrder >= 0) ? CalculateFF(CM1, TM1, CM2, TM2, 0, 0, FFFirstZ, false, false) : 0;
      double F1Z1F0Z2_2 = (ExpansionOrder >= 1) ? CalculateFF(CM1, TM1, CM2, TM2, 1, 0, FFFirstZ, false, false) : 0;
      double F2Z1F0Z2_2 = (ExpansionOrder >= 2) ? CalculateFF(CM1, TM1, CM2, TM2, 2, 0, FFFirstZ, false, false) : 0;

      TempLeptons = CentralLeptonsLeft;
      double F0Z1F0Z2_L = (ExpansionOrder >= 0) ? CalculateFF(CM1, TM1, CM2, TM2, 0, 0, FFFirstZ, false, true) : 0;
      double F1Z1F0Z2_L = (ExpansionOrder >= 1) ? CalculateFF(CM1, TM1, CM2, TM2, 1, 0, FFFirstZ, false, true) : 0;
      double F2Z1F0Z2_L = (ExpansionOrder >= 2) ? CalculateFF(CM1, TM1, CM2, TM2, 2, 0, FFFirstZ, false, true) : 0;

      TempLeptons = CentralLeptonsRight;
      double F0Z1F0Z2_R = (ExpansionOrder >= 0) ? CalculateFF(CM1, TM1, CM2, TM2, 0, 0, FFFirstZ, true, true) : 0;
      double F1Z1F0Z2_R = (ExpansionOrder >= 1) ? CalculateFF(CM1, TM1, CM2, TM2, 1, 0, FFFirstZ, true, true) : 0;
      double F2Z1F0Z2_R = (ExpansionOrder >= 2) ? CalculateFF(CM1, TM1, CM2, TM2, 2, 0, FFFirstZ, true, true) : 0;

      for(int i = 0; i < MECount; i++)
      {
         switch(ExpansionOrder)
         {
            case 0:
               Result[i] = ME0_1[i] * F0Z1F0Z2_1 + ME0_2[i] * F0Z1F0Z2_2
                  + ME0_L[i] * F0Z1F0Z2_L + ME0_R[i] * F0Z1F0Z2_R;
               break;
            case 1:
               Result[i] = (ME0_1[i] * F0Z1F0Z2_1 + B1_1[i] * F1Z1F0Z2_1)
                  + (ME0_2[i] * F0Z1F0Z2_2 + B1_2[i] * F1Z1F0Z2_2)
                  + (ME0_L[i] * F0Z1F0Z2_L + B1_L[i] * F1Z1F0Z2_L)
                  + (ME0_R[i] * F0Z1F0Z2_R + B1_R[i] * F1Z1F0Z2_R);
               break;
            case 2:
               Result[i] = (ME0_1[i] * F0Z1F0Z2_1 + B1_1[i] * F1Z1F0Z2_1 + 0.5 * B11_1[i] * F2Z1F0Z2_1)
                  + (ME0_2[i] * F0Z1F0Z2_2 + B1_2[i] * F1Z1F0Z2_2 + 0.5 * B11_2[i] * F2Z1F0Z2_2)
                  + (ME0_L[i] * F0Z1F0Z2_L + B1_L[i] * F1Z1F0Z2_L + 0.5 * B11_L[i] * F2Z1F0Z2_L)
                  + (ME0_R[i] * F0Z1F0Z2_R + B1_R[i] * F1Z1F0Z2_R + 0.5 * B11_R[i] * F2Z1F0Z2_R);
               break;
            default:
               Result[i] = 0;
               break;
         }

         Result[i] = Result[i] * CM1 * CM2;
      }
   }
   else
   {
      std::cerr << "[HybridCalculator] delta(PT = 0) for signal not supported yet!" << std::endl;
      std::cerr << "[HybridCalculator] Returning nonsense..." << std::endl;
   }
}
//----------------------------------------------------------------------------
void HybridCalculator::CalculateMEs(const EventParameters &CentralParameters,
   std::vector<double> &ME0, std::vector<double> &B1, std::vector<double> &B3,
   std::vector<double> &B11, std::vector<double> &B13, std::vector<double> &B33)
{
   TempParameters = CentralParameters;
   TempLeptons = ConvertAnglesToVectorsRoberto(CentralParameters);

   LeptonVectors PlusLeptons1 = TempLeptons.ApplySmearing(Cs(1 / 1.01, 1.01, 1, 1));
   LeptonVectors PlusLeptons3 = TempLeptons.ApplySmearing(Cs(1, 1, 1 / 1.01, 1.01));
   LeptonVectors PlusLeptons13 = TempLeptons.ApplySmearing(Cs(1 / 1.01, 1.01, 1 / 1.01, 1.01));
   LeptonVectors MinusLeptons1 = TempLeptons.ApplySmearing(Cs(1.01, 1 / 1.01, 1, 1));
   LeptonVectors MinusLeptons3 = TempLeptons.ApplySmearing(Cs(1, 1, 1.01, 1 / 1.01));

   FourVector TotalCenter = TempLeptons.GetTotal();
   FourVector TotalPlus1 = PlusLeptons1.GetTotal();
   FourVector TotalPlus3 = PlusLeptons3.GetTotal();
   FourVector TotalPlus13 = PlusLeptons13.GetTotal();
   FourVector TotalMinus1 = MinusLeptons1.GetTotal();
   FourVector TotalMinus3 = MinusLeptons3.GetTotal();

   double PTCenter = TotalCenter.GetPT();     double PTPlus1 = TotalPlus1.GetPT();
   double YCenter = TotalCenter.GetY();       double YPlus1 = TotalPlus1.GetY();
   double SCenter = TotalCenter.GetMass2();   double SPlus1 = TotalPlus1.GetMass2();
   double PTPlus3 = TotalPlus3.GetPT();       double PTPlus13 = TotalPlus13.GetPT();
   double YPlus3 = TotalPlus3.GetY();         double YPlus13 = TotalPlus13.GetY();
   double SPlus3 = TotalPlus3.GetMass2();     double SPlus13 = TotalPlus13.GetMass2();
   double PTMinus1 = TotalMinus1.GetPT();     double PTMinus3 = TotalMinus3.GetPT();
   double YMinus1 = TotalMinus1.GetY();       double YMinus3 = TotalMinus3.GetY();
   double SMinus1 = TotalMinus1.GetMass2();   double SMinus3 = TotalMinus3.GetMass2();

   TempLeptons = GoToRest(TempLeptons);
   PlusLeptons1 = GoToRest(PlusLeptons1);
   PlusLeptons3 = GoToRest(PlusLeptons3);
   PlusLeptons13 = GoToRest(PlusLeptons13);
   MinusLeptons1 = GoToRest(MinusLeptons1);
   MinusLeptons3 = GoToRest(MinusLeptons3);

   LeptonVectors SwappedTempLeptons = TempLeptons.FlipZ1Z2();
   LeptonVectors SwappedPlusLeptons1 = PlusLeptons1.FlipZ1Z2();
   LeptonVectors SwappedPlusLeptons3 = PlusLeptons3.FlipZ1Z2();
   LeptonVectors SwappedPlusLeptons13 = PlusLeptons13.FlipZ1Z2();
   LeptonVectors SwappedMinusLeptons1 = MinusLeptons1.FlipZ1Z2();
   LeptonVectors SwappedMinusLeptons3 = MinusLeptons3.FlipZ1Z2();

   double VolumeElement = 1, SwappedVolumeElement = 1;
   if(FlatApproximation == false)
   {
      LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(CentralParameters);
      EventParameters SwappedParameters = ConvertVectorsToAnglesRoberto(Leptons.FlipZ1Z2());

      VolumeElement = VolumeElement::EstimateVolumeFull5(CentralParameters);
      SwappedVolumeElement = VolumeElement::EstimateVolumeFull5(SwappedParameters);
   }

   for(int i = 0; i < MECount; i++)
   {
      double ValueCentral = CalculateMEValue[i](TempLeptons, ZP);
      double ValuePlus1 = (ExpansionOrder >= 1) ? CalculateMEValue[i](PlusLeptons1, ZP) : 0;
      double ValuePlus3 = (ExpansionOrder >= 1) ? CalculateMEValue[i](PlusLeptons3, ZP) : 0;
      double ValuePlus13 = (ExpansionOrder >= 2) ? CalculateMEValue[i](PlusLeptons13, ZP) : 0;
      double ValueMinus1 = (ExpansionOrder >= 1) ? CalculateMEValue[i](MinusLeptons1, ZP) : 0;
      double ValueMinus3 = (ExpansionOrder >= 1) ? CalculateMEValue[i](MinusLeptons3, ZP) : 0;

      ValueCentral = ValueCentral * VolumeElement;
      ValuePlus1 = ValuePlus1 * VolumeElement;
      ValuePlus3 = ValuePlus3 * VolumeElement;
      ValuePlus13 = ValuePlus13 * VolumeElement;
      ValueMinus1 = ValueMinus1 * VolumeElement;
      ValueMinus3 = ValueMinus3 * VolumeElement;

      if(IncludeSwapping == true)
      {
         double SwappedValueCentral = CalculateMEValue[i](SwappedTempLeptons, ZP);
         double SwappedValuePlus1 = (ExpansionOrder >= 1) ? CalculateMEValue[i](SwappedPlusLeptons1, ZP) : 0;
         double SwappedValuePlus3 = (ExpansionOrder >= 1) ? CalculateMEValue[i](SwappedPlusLeptons3, ZP) : 0;
         double SwappedValuePlus13 = (ExpansionOrder >= 2) ? CalculateMEValue[i](SwappedPlusLeptons13, ZP) : 0;
         double SwappedValueMinus1 = (ExpansionOrder >= 1) ? CalculateMEValue[i](SwappedMinusLeptons1, ZP) : 0;
         double SwappedValueMinus3 = (ExpansionOrder >= 1) ? CalculateMEValue[i](SwappedMinusLeptons3, ZP) : 0;

         SwappedValueCentral = SwappedValueCentral * SwappedVolumeElement;
         SwappedValuePlus1 = SwappedValuePlus1 * SwappedVolumeElement;
         SwappedValuePlus3 = SwappedValuePlus3 * SwappedVolumeElement;
         SwappedValuePlus13 = SwappedValuePlus13 * SwappedVolumeElement;
         SwappedValueMinus1 = SwappedValueMinus1 * SwappedVolumeElement;
         SwappedValueMinus3 = SwappedValueMinus3 * SwappedVolumeElement;

         ValueCentral = ValueCentral + SwappedValueCentral;
         ValuePlus1 = ValuePlus1 + SwappedValuePlus1;
         ValuePlus3 = ValuePlus3 + SwappedValuePlus3;
         ValuePlus13 = ValuePlus13 + SwappedValuePlus13;
         ValueMinus1 = ValueMinus1 + SwappedValueMinus1;
         ValueMinus3 = ValueMinus3 + SwappedValueMinus3;
      }

      ValueCentral = ValueCentral * MHExp(TempLeptons);
      ValuePlus1 = ValuePlus1 * MHExp(PlusLeptons1);
      ValuePlus3 = ValuePlus3 * MHExp(PlusLeptons3);
      ValuePlus13 = ValuePlus13 * MHExp(PlusLeptons13);
      ValueMinus1 = ValueMinus1 * MHExp(MinusLeptons1);
      ValueMinus3 = ValueMinus3 * MHExp(MinusLeptons3);

      if(PTYDensity != NULL)
      {
         ValueCentral = ValueCentral * PTYDensity(PTCenter, YCenter, SCenter);
         ValuePlus1 = ValuePlus1 * PTYDensity(PTPlus1, YPlus1, SPlus1);
         ValuePlus3 = ValuePlus3 * PTYDensity(PTPlus3, YPlus3, SPlus3);
         ValuePlus13 = ValuePlus13 * PTYDensity(PTPlus13, YPlus13, SPlus13);
         ValueMinus1 = ValueMinus1 * PTYDensity(PTMinus1, YMinus1, SMinus1);
         ValueMinus3 = ValueMinus3 * PTYDensity(PTMinus3, YMinus3, SMinus3);
      }

      ME0[i] = ValueCentral;
      B1[i] = (ValuePlus1 - ValueMinus1) / (1.01 - 0.99);
      B3[i] = (ValuePlus3 - ValueMinus3) / (1.01 - 0.99);
      B11[i] = (ValuePlus1 + ValueMinus1 - ME0[i] * 2) / (1.01 - 1.00) / (1.01 - 1.00);
      B13[i] = (ValuePlus13 - ValuePlus1 - ValuePlus3 + ME0[i]) / (1.01 - 1.00) / (1.01 - 1.00);
      B33[i] = (ValuePlus3 + ValueMinus3 - ME0[i] * 2) / (1.01 - 1.00) / (1.01 - 1.00);
   }

   return;
}
//----------------------------------------------------------------------------
void HybridCalculator::CalculateMEsDeltaMH(const EventParameters &CentralValue, std::vector<double> &ME0,
   std::vector<double> &B1, std::vector<double> &B11, bool FirstZ, bool Branch, bool Tip)
{
   for(int i = 0; i < (int)ME0.size(); i++)
      ME0[i] = 0;
   for(int i = 0; i < (int)B1.size(); i++)
      B1[i] = 0;
   for(int i = 0; i < (int)B11.size(); i++)
      B11[i] = 0;

   if(IgnoreTip == true && Tip == true)
      return;

   if(CentralValue.HMass != CentralValue.HMass)
      return;
   if(CentralValue.HMass < 10)
      return;

   TempParameters = CentralValue;
   TempLeptons = ConvertAnglesToVectorsRoberto(CentralValue);

   double Min, Max;

   if(Tip == false)
   {
      Min = std::max(IntegralCMin, CCoordinates.CSReco_LeftLimit);
      Max = std::min(IntegralCMax, CCoordinates.CSReco_RightLimit);
   }
   else
   {
      Min = std::max(IntegralCMin, (Branch == false) ? CCoordinates.CPReco_LeftDown : CCoordinates.CPReco_RightDown);
      Max = std::min(IntegralCMax, (Branch == false) ? CCoordinates.CPReco_LeftUp : CCoordinates.CPReco_RightUp);
   }

   double CSCenter = CCoordinates.CSReco;
   if(Tip == true)
      CSCenter = (Branch == true) ? CCoordinates.CPReco_RightCenter : CCoordinates.CPReco_LeftCenter;

   if(CSCenter < 0)   // nothing to do here!
      return;

   double CSPlus = (Max + CSCenter) / 2;
   double CSMinus = (CSCenter + Min) / 2;

   if(CSPlus / CSCenter > 1.01)   // We want small steps :3
      CSPlus = CSCenter * 1.01;
   if(CSMinus / CSCenter < 0.99)
      CSMinus = CSCenter * 0.99;

   MassSquare MM;
   if(Tip == false)   MM = (Branch == true) ? CentralMM : CentralAltMM;
   else               MM = (Branch == true) ? CentralRightMM : CentralLeftMM;
   MassSquare FlippedMM = MM.FlipZ1Z2();

   double CPPlus, CPMinus;
   if(FirstZ == true)
   {
      if(Tip == false)
      {
         CPPlus = CalculateCP(MM, DeltaMH * DeltaMH, CSPlus / CSCenter, Branch);
         CPMinus = CalculateCP(MM, DeltaMH * DeltaMH, CSMinus / CSCenter, Branch);
      }
      else
      {
         CPPlus = CalculateCP(FlippedMM, DeltaMH * DeltaMH, CSPlus / CSCenter, !Branch);
         CPMinus = CalculateCP(FlippedMM, DeltaMH * DeltaMH, CSMinus / CSCenter, !Branch);
      }
   }
   else
   {
      // TODO
   }

   LeptonVectors PlusLepton1, MinusLepton1;

   if(FirstZ == true)
   {
      if(Tip == false)
      {
         PlusLepton1 = TempLeptons.ApplySmearing(Cs(CSCenter / CSPlus, CSPlus / CSCenter, 1 / CPPlus, CPPlus));
         MinusLepton1 = TempLeptons.ApplySmearing(Cs(CSCenter / CSMinus, CSMinus / CSCenter, 1 / CPMinus, CPMinus));
      }
      else
      {
         PlusLepton1 = TempLeptons.ApplySmearing(Cs(1 / CPPlus, CPPlus, CSCenter / CSPlus, CSPlus / CSCenter));
         MinusLepton1 = TempLeptons.ApplySmearing(Cs(1 / CPMinus, CPMinus, CSCenter / CSMinus, CSMinus / CSCenter));
      }
   }
   else
   {
      // TODO
   }

   TempLeptons = GoToRest(TempLeptons);
   PlusLepton1 = GoToRest(PlusLepton1);
   MinusLepton1 = GoToRest(MinusLepton1);

   LeptonVectors SwappedTempLeptons = TempLeptons.FlipZ1Z2();
   LeptonVectors SwappedPlusLeptons1 = PlusLepton1.FlipZ1Z2();
   LeptonVectors SwappedMinusLeptons1 = MinusLepton1.FlipZ1Z2();

   double VolumeElement = 1, SwappedVolumeElement = 1;
   if(FlatApproximation == false)
   {
      LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(CentralValue);
      EventParameters SwappedParameters = ConvertVectorsToAnglesRoberto(Leptons.FlipZ1Z2());

      VolumeElement = VolumeElement::EstimateVolumeFull5(CentralValue);
      SwappedVolumeElement = VolumeElement::EstimateVolumeFull5(SwappedParameters);
   }

   for(int i = 0; i < MECount; i++)
   {
      double ValuePlus1 = 0;
      double ValueMinus1 = 0;

      ME0[i] = CalculateMEValue[i](TempLeptons, ZP) * VolumeElement;
      ValuePlus1 = (ExpansionOrder >= 1) ? (CalculateMEValue[i](PlusLepton1, ZP) * VolumeElement) : 0;
      ValueMinus1 = (ExpansionOrder >= 1) ? (CalculateMEValue[i](MinusLepton1, ZP) * VolumeElement) : 0;

      if(IncludeSwapping == true)
      {
         ME0[i] = ME0[i] + CalculateMEValue[i](SwappedTempLeptons, ZP) * SwappedVolumeElement;
         ValuePlus1 = ValuePlus1 +
            ((ExpansionOrder >= 1) ? (CalculateMEValue[i](SwappedPlusLeptons1, ZP) * SwappedVolumeElement) : 0);
         ValueMinus1 = ValueMinus1 +
            ((ExpansionOrder >= 1) ? (CalculateMEValue[i](SwappedMinusLeptons1, ZP) * SwappedVolumeElement) : 0);
      }

      B1[i] = (ExpansionOrder >= 1) ? ((ValuePlus1 - ValueMinus1) / (CSPlus - CSMinus)) : 0;
      B11[i] = (ExpansionOrder >= 2) ?
         ((((ValuePlus1 - ME0[i]) / (CSPlus - CSCenter) - (ValueMinus1 - ME0[i]) / (CSMinus - CSCenter))
         / (CSPlus - CSMinus)) * 2) : 0;
   }
}
//----------------------------------------------------------------------------
double HybridCalculator::CalculateF(double M, double M0, int Order, bool FirstZ)
{
   const double TargetC1C2 = (M0 / M) * (M0 / M);

   const int InitialStepSize = IntegralCStep;

   const double CMin = IntegralCMin;
   const double CMax = IntegralCMax;

   double Integral = 0;
   double fa = 0, fc = 0, fb = 0;
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

      double CurrentToleranceF = ToleranceF / InitialStepSize;
      if(Order >= 2)
         CurrentToleranceF = CurrentToleranceF / 100;

      double Contribution = AdaptCalculateF(sab, fa, fc, fb, a, b, CurrentToleranceF, TargetC1C2, Order, FirstZ, 0);

      Integral = Integral + Contribution;

      fa = fb;
   }

   return Integral;
}
//----------------------------------------------------------------------------
double HybridCalculator::CalculateFF(double M, double M0, double AnotherM, double AnotherM0,
   int Order, int AnotherOrder, bool FirstZ, bool Branch, bool Tip)
{
   if(Tip == true && IgnoreTip == true)
      return 0;

   const double TargetC1C2 = (M0 / M) * (M0 / M);
   const double TargetC3C4 = (AnotherM0 / AnotherM) * (AnotherM0 / AnotherM);

   const int InitialStepSize = IntegralCStep;

   double CMin, CMax;
   if(Tip == false)
   {
      CMin = std::max(IntegralCMin, CCoordinates.CSReco_LeftLimit);
      CMax = std::min(IntegralCMax, CCoordinates.CSReco_RightLimit);
   }
   else
   {
      if(Branch == true)
      {
         CMin = std::max(IntegralCMin, CCoordinates.CPReco_RightDown);
         CMax = std::min(IntegralCMax, CCoordinates.CPReco_RightUp);
      }
      else
      {
         CMin = std::max(IntegralCMin, CCoordinates.CPReco_LeftDown);
         CMax = std::min(IntegralCMax, CCoordinates.CPReco_LeftUp);
      }
   }

   if(CMax <= CMin)
      return 0;

   double Integral = 0;
   double fa = 0, fc = 0, fb = 0;
   for(int i = 0; i < InitialStepSize; i++)
   {
      double a = (CMax - CMin) / InitialStepSize * i + CMin;
      double b = (CMax - CMin) / InitialStepSize * (i + 1) + CMin;
      double c = (a + b) / 2;

      if(i == 0)
         fa = ff(a, TargetC1C2, TargetC3C4, Order, AnotherOrder, FirstZ, Branch, Tip);
      fc = ff(c, TargetC1C2, TargetC3C4, Order, AnotherOrder, FirstZ, Branch, Tip);
      fb = ff(b, TargetC1C2, TargetC3C4, Order, AnotherOrder, FirstZ, Branch, Tip);

      // if(M > 76.2937 && M < 76.2939 && AnotherM > 34.3658 && AnotherM < 34.3660)
      // {
      //    std::cout << a << " " << b << " " << c << std::endl;
      //    std::cout << fa << " " << fb << " " << fc << std::endl;
      //    std::cout << TargetC1C2 << " " << TargetC3C4 << std::endl;
      //    std::cout << std::endl;
      // }

      double sab = (b - a) * (fa + 4 * fc + fb) / 6;

      double CurrentToleranceF = ToleranceF / InitialStepSize;
      if(Order >= 2)
         CurrentToleranceF = CurrentToleranceF / 100;

      double Contribution = AdaptCalculateFF(sab, fa, fc, fb, a, b, CurrentToleranceF,
         TargetC1C2, Order, TargetC3C4, AnotherOrder, FirstZ, 0, Branch, Tip);

      Integral = Integral + Contribution;

      fa = fb;
   }

   return Integral;
}
//----------------------------------------------------------------------------
double HybridCalculator::AdaptCalculateF(double sab, double fa, double fc, double fb, double a, double b,
   double Tolerance, double c1c2, int Order, bool FirstZ, int Depth)
{
   if(Depth > MaxDepthF)
      return sab;

   double c = (a + b) / 2;
   double fd = f((a + c) / 2, c1c2, Order, FirstZ);
   double fe = f((c + b) / 2, c1c2, Order, FirstZ);
   double sac = (c - a) * (fa + 4 * fd + fc) / 6;
   double scb = (b - c) * (fc + 4 * fe + fb) / 6;

   if(fabs(sac + scb - sab) < Tolerance * 10)
      return sac + scb;

   return AdaptCalculateF(sac, fa, fd, fc, a, c, Tolerance / 2, c1c2, Order, FirstZ, Depth + 1)
      + AdaptCalculateF(scb, fc, fe, fb, c, b, Tolerance / 2, c1c2, Order, FirstZ, Depth + 1);
}
//----------------------------------------------------------------------------
double HybridCalculator::AdaptCalculateFF(double sab, double fa, double fc, double fb, double a, double b,
   double Tolerance, double c1c2, int Order1, double c3c4, int Order3, bool FirstZ, int Depth, bool Branch,
   bool Tip)
{
   if(Depth > MaxDepthF)
      return sab;

   double c = (a + b) / 2;
   double fd = ff((a + c) / 2, c1c2, c3c4, Order1, Order3, FirstZ, Branch, Tip);
   double fe = ff((c + b) / 2, c1c2, c3c4, Order1, Order3, FirstZ, Branch, Tip);
   double sac = (c - a) * (fa + 4 * fd + fc) / 6;
   double scb = (b - c) * (fc + 4 * fe + fb) / 6;

   if(fabs(sac + scb - sab) < Tolerance * 10)
      return sac + scb;

   return AdaptCalculateFF(sac, fa, fd, fc, a, c, Tolerance / 2, c1c2, Order1, c3c4, Order3, FirstZ, Depth + 1, Branch, Tip)
      + AdaptCalculateFF(scb, fc, fe, fb, c, b, Tolerance / 2, c1c2, Order1, c3c4, Order3, FirstZ, Depth + 1, Branch, Tip);
}
//----------------------------------------------------------------------------
double HybridCalculator::f(double x, double c1c2, int Order, bool FirstZ)
{
   double Result = 0;

   FourVector L11, L12, L21, L22;
   double C1, C2;

   if(LeptonReversal == false)
   {
      L11 = TempLeptons.Lepton11 / x;
      L12 = TempLeptons.Lepton12 * x;
      L21 = TempLeptons.Lepton21 / x;
      L22 = TempLeptons.Lepton22 * x;
      C1 = x;
      C2 = c1c2 / x;
   }
   else
   {
      L11 = TempLeptons.Lepton11 * x;
      L12 = TempLeptons.Lepton12 / x;
      L21 = TempLeptons.Lepton21 * x;
      L22 = TempLeptons.Lepton22 / x;
      C1 = c1c2 / x;
      C2 = x;
   }

   double RecoPPFactor = C1 * C2;   // p^R_i / p^G_i = c_i

   double Jacobian = 1;
   if(FirstZ == true)
      Jacobian = RecoMM.M12_2 / C1 / C2 / C2;
   else
      Jacobian = RecoMM.M34_2 / C1 / C2 / C2;

   if(FirstZ == true)
      Result = Smear12(L11, C1 - 1) * Smear12(L12, C2 - 1) / C1 / C1 / C2 / C2 / Jacobian * RecoPPFactor;
   else
      Result = Smear34(L21, C1 - 1) * Smear34(L22, C2 - 1) / C1 / C1 / C2 / C2 / Jacobian * RecoPPFactor;

   if(Order == 0)
      return Result;
   if(Order == 1)
      return Result * (x - 1);

   for(int i = 0; i < Order; i++)
      Result = Result * (x - 1);
   return Result;
}
//----------------------------------------------------------------------------
double HybridCalculator::ff(double x, double c1c2, double c3c4, int Order1, int Order3, bool FirstZ, bool Branch,
   bool Tip)
{
   if(LeptonReversal == true)
   {
      std::cerr << "[HybridCalculator][ff] LeptonReversal == true!!  Not implemented yet!!!  Return 0!!!!!" << std::endl;
      return 0;
   }
   if(FirstZ == false)
   {
      std::cerr << "[HybridCalculator][ff] Warning!!  FirstZ == false not yet supported!!" << std::endl;
      return 0;
   }

   double CPReco;
   MassSquare MM, RMM = RecoMM;
   if(Tip == false)
   {
      CPReco = (Branch == true) ? CCoordinates.CPReco_1 : CCoordinates.CPReco_2;
      MM = (Branch == true) ? CentralMM : CentralAltMM;
   }
   else
   {
      CPReco = (Branch == true) ? CCoordinates.CSReco_RightCenter : CCoordinates.CSReco_LeftCenter;
      MM = (Branch == true) ? CentralRightMM : CentralLeftMM;
   }

   if(LeptonReversal == true)
   {
      MM = MM.FlipLALB();
      RMM = RMM.FlipLALB();
   }

   MassSquare FlippedMM = MM.FlipZ1Z2();

   double Result = 12345;

   Cs c;
   double Jacobian = 1;

   double CS = CCoordinates.CSReco;
   if(Tip == true)
      CS = (Branch == true) ? CCoordinates.CPReco_RightCenter : CCoordinates.CPReco_LeftCenter;

   if(FirstZ == true)
   {
      if(Tip == false)
      {
         double TempCP = CalculateCP(MM, DeltaMH * DeltaMH, x / CS, Branch);
         c = Cs(x / CS, c1c2 / x * CS, TempCP, c3c4 / TempCP);
      }
      else
      {
         double TempCP = CalculateCP(FlippedMM, DeltaMH * DeltaMH, x / CS, !Branch);
         c = Cs(TempCP, c1c2 / TempCP, x / CS, c3c4 / x * CS);
      }

      Cs C;

      if(Tip == false)
         C = c * Cs(CS, 1 / CS, CPReco, 1 / CPReco);
      else
         C = c * Cs(CPReco, 1 / CPReco, CS, 1 / CS);

      Jacobian = CalculateJS(RecoMM, C, Tip);

      /*
      double CA12 = C.c[0];
      double CB12 = C.c[1];
      double CA34 = C.c[2];
      double CB34 = C.c[3];

      double dMH2dcA34 = -(RecoMM.MAA_2 / CA12 + RecoMM.MBA_2 / CB12 + RecoMM.M34_2 / CB34) / CA34 / CA34;
      double dMH2dcB34 = -(RecoMM.MAB_2 / CA12 + RecoMM.MBB_2 / CB12 + RecoMM.M34_2 / CA34) / CB34 / CB34;

      double dM12dcB12 = -RecoMM.M12_2 / CA12 / CB12 / CB12;
      double dM22dcA34 = -RecoMM.M34_2 / CA34 / CA34 / CB34;
      double dM22dcB34 = -RecoMM.M34_2 / CA34 / CB34 / CB34;

      if(Tip == true)
      {
         dMH2dcA34 = -(RecoMM.MAA_2 / CA34 + RecoMM.MAB_2 / CB34 + RecoMM.M12_2 / CB12) / CA12 / CA12;
         dMH2dcB34 = -(RecoMM.MBA_2 / CA34 + RecoMM.MBB_2 / CB34 + RecoMM.M12_2 / CA12) / CB12 / CB12;
         dM12dcB12 = -RecoMM.M34_2 / CA34 / CB34 / CB34;
         dM22dcA34 = -RecoMM.M12_2 / CA12 / CA12 / CB12;
         dM22dcB34 = -RecoMM.M12_2 / CA12 / CB12 / CB12;
      }

      Jacobian = dM12dcB12 * (dM22dcA34 * dMH2dcB34 - dM22dcB34 * dMH2dcA34);

      if(fabs(Jacobian) < 1 && CA12 > IntegralCMin && CA12 < IntegralCMax
         && CB12 > IntegralCMin && CB12 < IntegralCMax
         && CA34 > IntegralCMin && CA34 < IntegralCMax
         && CB34 > IntegralCMin && CB34 < IntegralCMax)
      {
         if(Tip == true)   std::cout << "Tip" << std::endl;
         else              std::cout << "Bulk" << std::endl;
         std::cout << "J " << dM12dcB12 << " " << dM22dcA34 << " " << dM22dcB34
            << " " << dMH2dcA34 << " " << dMH2dcB34 << " " << Jacobian << std::endl;
      }
      */
   }
   else
   {
      // TODO!
   }

   if(Jacobian < 0)
      Jacobian = -Jacobian;

   LeptonVectors L;
   Cs C;

   if(FirstZ == true)
   {
      if(LeptonReversal == false)
      {
         L = TempLeptons.ApplySmearing(Cs(1 / c.c[0], c.c[0], 1 / c.c[2], c.c[2]));
         if(Tip == false)
            C = c * Cs(CS, 1 / CS, CPReco, 1 / CPReco);
         else
            C = c * Cs(CPReco, 1 / CPReco, CS, 1 / CS);
      }
      else
      {
         // TODO!!!!!
      }
   }
   else
   {
      // TODO!!!!!!
   }

   // std::cout << "GEN " << L.GetTotal().GetMass()
   //    << " " << (L[0] + L[1]).GetMass() << " " << (L[2] + L[3]).GetMass() << std::endl;
   // std::cout << "CEN " << (TempLeptons.Lepton11 + TempLeptons.Lepton12 + TempLeptons.Lepton21 + TempLeptons.Lepton22).GetMass()
   //    << " " << (TempLeptons.Lepton11 + TempLeptons.Lepton12).GetMass()
   //    << " " << (TempLeptons.Lepton21 + TempLeptons.Lepton22).GetMass() << std::endl;
   // std::cout << "RECO " << (L.ApplySmearing(C).GetTotal()).GetMass()
   //    << " " << (L[0] * C.c[0] + L[1] * C.c[1]).GetMass() << " " << (L[2] * C.c[2] + L[3] * C.c[3]).GetMass() << std::endl;
   // std::cout << std::endl;

   // double GenM1 = (L11 + L12).GetMass();
   // double GenM2 = (L21 + L22).GetMass();
   // if(GenM1 > 99.2 && GenM1 < 99.3 && GenM2 > 20.5 && GenM2 < 20.6 && Branch == true)
   // {
   //    std::cout << C1 << " " << C2 << " " << C3 << " " << C4 << std::endl;
   //    std::cout << Smear12(L11, C1 - 1) << " " << Smear12(L12, C2 - 1)
   //       << " " << Smear34(L21, C3 - 1) << " " << Smear34(L22, C4 - 1) << std::endl;
   //    // std::cout << L11 << " " << L12 << " " << L21 << " " << L22 << std::endl;
   //    // std::cout << L11 * C1 << " " << L12 * C2 << " " << L21 * C3 << " " << L22 * C4 << std::endl;
   //    // std::cout << GenM1 << " " << GenM2 << std::endl;
   //    // std::cout << " " << (L11 * C1 + L12 * C2).GetMass() << " " << (L21 * C3 + L22 * C4).GetMass() << std::endl;
   //    // std::cout << std::endl;
   // }

   double PTYWeight = 1;
   if(PTYDensity != NULL)
   {
      FourVector Gen4l = L.GetTotal();
      PTYWeight = PTYDensity(Gen4l.GetPT(), Gen4l.GetY(), Gen4l.GetMass2());
   }

   if((FirstZ == true && C.c[2] > 1e-5 && Jacobian < 1e10 && Jacobian == Jacobian)
      || (FirstZ == false && C.c[0] > 1e-5 && Jacobian < 1e10 && Jacobian == Jacobian))
      Result = Smear12(L[0], C.c[0] - 1) * Smear12(L[1], C.c[1] - 1)
         * Smear34(L[2], C.c[2] - 1) * Smear34(L[3], C.c[3] - 1) * Jacobian * PTYWeight
         / C.c[0] / C.c[1] / C.c[2] / C.c[3];
      // Result = Smear12(L11, C1 - 1) * Smear12(L12, C2 - 1)
      //    * Smear34(L21, C3 - 1) * Smear34(L22, C4 - 1) / Jacobian * PTYWeight
      //    / C1 / C2 / C3 / C4 / C1 / C2 / C3 / C4
      //    * (L11.GetP() * C1) * (L12.GetP() * C2) * (L21.GetP() * C3) * (L22.GetP() * C4)
      //    / L11.GetP() / L12.GetP() / L21.GetP() / L22.GetP();
   else
      Result = 0;

   if(FirstZ == true)
   {
      if(Tip == false)
      {
         for(int i = 0; i < Order1; i++)
            Result = Result * (C.c[0] - CS);
         for(int i = 0; i < Order3; i++)
            Result = Result * (C.c[2] - CPReco);
      }
      else
      {
         for(int i = 0; i < Order3; i++)
            Result = Result * (C.c[0] - CPReco);
         for(int i = 0; i < Order1; i++)
            Result = Result * (C.c[2] - CS);
      }
   }
   else
   {
      // TODO!!!
   }

   return Result;
}
//----------------------------------------------------------------------------
double HybridCalculator::GetSinAngle(const EventParameters &Center, const EventParameters &A, const EventParameters &B)
{
   double DA[12] = {0}, DB[12] = {0};

   DA[0] = A.HMass * A.HMass - Center.HMass * Center.HMass;
   DA[1] = A.ZMass * A.ZMass - Center.ZMass * Center.ZMass;
   DA[2] = A.Z2Mass * A.Z2Mass - Center.Z2Mass * Center.Z2Mass;
   DA[3] = A.Phi0 - Center.Phi0;
   DA[4] = cos(A.Theta0) - cos(Center.Theta0);
   DA[5] = A.Phi - Center.Phi;
   DA[6] = cos(A.Theta1) - cos(Center.Theta1);
   DA[7] = cos(A.Theta2) - cos(Center.Theta2);
   DA[8] = A.PhiH - Center.PhiH;
   DA[9] = A.PhiOffset - Center.PhiOffset;
   DA[10] = A.PTH - Center.PTH;
   DA[11] = A.YH - Center.YH;

   DB[0] = B.HMass * B.HMass - Center.HMass * Center.HMass;
   DB[1] = B.ZMass * B.ZMass - Center.ZMass * Center.ZMass;
   DB[2] = B.Z2Mass * B.Z2Mass - Center.Z2Mass * Center.Z2Mass;
   DB[3] = B.Phi0 - Center.Phi0;
   DB[4] = cos(B.Theta0) - cos(Center.Theta0);
   DB[5] = B.Phi - Center.Phi;
   DB[6] = cos(B.Theta1) - cos(Center.Theta1);
   DB[7] = cos(B.Theta2) - cos(Center.Theta2);
   DB[8] = B.PhiH - Center.PhiH;
   DB[9] = B.PhiOffset - Center.PhiOffset;
   DB[10] = B.PTH - Center.PTH;
   DB[11] = B.YH - Center.YH;

   if(DA[3] < -PI)   DA[3] = DA[3] + 2 * PI;
   if(DA[3] > PI)    DA[3] = DA[3] - 2 * PI;
   if(DA[5] < -PI)   DA[5] = DA[5] + 2 * PI;
   if(DA[5] > PI)    DA[5] = DA[5] - 2 * PI;
   if(DA[8] < -PI)   DA[8] = DA[8] + 2 * PI;
   if(DA[8] > PI)    DA[8] = DA[8] - 2 * PI;
   if(DA[9] < -PI)   DA[9] = DA[9] + 2 * PI;
   if(DA[9] > PI)    DA[9] = DA[9] - 2 * PI;
   if(DB[3] < -PI)   DB[3] = DB[3] + 2 * PI;
   if(DB[3] > PI)    DB[3] = DB[3] - 2 * PI;
   if(DB[5] < -PI)   DB[5] = DB[5] + 2 * PI;
   if(DB[5] > PI)    DB[5] = DB[5] - 2 * PI;
   if(DB[8] < -PI)   DB[8] = DB[8] + 2 * PI;
   if(DB[8] > PI)    DB[8] = DB[8] - 2 * PI;
   if(DB[9] < -PI)   DB[9] = DB[9] + 2 * PI;
   if(DB[9] > PI)    DB[9] = DB[9] - 2 * PI;

   double DotProduct = 0;
   double SumDA2 = 0, SumDB2 = 0;

   for(int i = 0; i < 12; i++)
   {
      DotProduct = DotProduct + DA[i] * DB[i];
      SumDA2 = SumDA2 + DA[i] * DA[i];
      SumDB2 = SumDB2 + DB[i] * DB[i];
   }

   return sqrt((SumDA2 * SumDB2 - DotProduct * DotProduct) / (SumDA2 * SumDB2));
}
//----------------------------------------------------------------------------
LeptonVectors HybridCalculator::GoToRest(LeptonVectors Leptons)
{
   FourVector Total = Leptons.GetTotal();
   Leptons.Lepton11 = Leptons.Lepton11.Boost(-Total, Total.GetP() / Total[0]);
   Leptons.Lepton12 = Leptons.Lepton12.Boost(-Total, Total.GetP() / Total[0]);
   Leptons.Lepton21 = Leptons.Lepton21.Boost(-Total, Total.GetP() / Total[0]);
   Leptons.Lepton22 = Leptons.Lepton22.Boost(-Total, Total.GetP() / Total[0]);
   return Leptons;
}
//----------------------------------------------------------------------------
double HybridCalculator::CalculateCP(double MAA_2, double MBB_2, double MBA_2, double MAB_2,
   double M12_2, double M34_2, double M4l_2, double C1, bool Branch)
{
   double Term1 = 1 / C1 * MAB_2 + C1 * MBB_2;
   double TermC = -(M4l_2 - M12_2 - M34_2);
   double TermCC = 1 / C1 * MAA_2 + C1 * MBA_2;

   if(TermC * TermC - 4 * Term1 * TermCC < 0)   // no solution
      return -1;

   double Result = 0;
   if(Branch == true)
      Result = (-TermC - sqrt(TermC * TermC - 4 * Term1 * TermCC)) / (2 * Term1);
   else
      Result = (-TermC + sqrt(TermC * TermC - 4 * Term1 * TermCC)) / (2 * Term1);

   if(Result != Result)
      Result = -1;

   return Result;
}
//----------------------------------------------------------------------------
double HybridCalculator::MHExp(const LeptonVectors &Leptons)
{
   if(DoGaussMH == false)
      return 1;

   double HMass = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   return exp(-(HMass - DeltaMH) * (HMass - DeltaMH) / (2 * SigmaMH * SigmaMH)) / SigmaMH;
}
//----------------------------------------------------------------------------
double HybridCalculator::CalculateCP(MassSquare &MM, double M4l_2, double C1, bool Branch)
{
   double Term1 = 1 / C1 * MM.MAB_2 + C1 * MM.MBB_2;
   double TermC = -(M4l_2 - MM.M12_2 - MM.M34_2);
   double TermCC = 1 / C1 * MM.MAA_2 + C1 * MM.MBA_2;

   if(TermC * TermC - 4 * Term1 * TermCC < 0)   // no solution
      return -1;

   double Result = 0;
   if(Branch == true)
      Result = (-TermC - sqrt(TermC * TermC - 4 * Term1 * TermCC)) / (2 * Term1);
   else
      Result = (-TermC + sqrt(TermC * TermC - 4 * Term1 * TermCC)) / (2 * Term1);

   if(Result != Result)
      Result = -1;

   return Result;
}
//----------------------------------------------------------------------------
bool HybridCalculator::HasSolutionForAnyC1(MassSquare &MM, double GM4l_2, double GM12_2, double GM34_2)
{
   double R12 = GM12_2 / MM.M12_2;
   double R34 = GM34_2 / MM.M34_2;

   double A = -4 * R34 * R12 * R12 * MM.MBB_2 * MM.MBA_2;
   double B = -4 * R12 * R34 * MM.MAB_2 * MM.MBA_2 - 4 * R12 * R34 * MM.MAA_2 * MM.MBB_2
      + (GM4l_2 - GM12_2 - GM34_2) * (GM4l_2 - GM12_2 - GM34_2);
   double C = -4 * R34 * MM.MAB_2 * MM.MAA_2;

   if(B * B < 4 * A * C)
      return false;
   if(B < 0)
      return false;

   return true;
}
//----------------------------------------------------------------------------
double HybridCalculator::FindLeftEndForC1(MassSquare &MM, double GM4l_2, double GM12_2, double GM34_2)
{
   double R12 = GM12_2 / MM.M12_2;
   double R34 = GM34_2 / MM.M34_2;

   double A = -4 * R34 * R12 * R12 * MM.MBB_2 * MM.MBA_2;
   double B = -4 * R12 * R34 * MM.MAB_2 * MM.MBA_2 - 4 * R12 * R34 * MM.MAA_2 * MM.MBB_2 + (GM4l_2 - GM12_2 - GM34_2) * (GM4l_2 - GM12_2 - GM34_2);
   double C = -4 * R34 * MM.MAB_2 * MM.MAA_2;

   if(B * B < 4 * A * C)
      return -999999;
   if(B < 0)
      return -999999;

   double Value = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
   if(Value < 0)
      Value = 0;

   return sqrt(Value);
}
//----------------------------------------------------------------------------
double HybridCalculator::FindRightEndForC1(MassSquare &MM, double GM4l_2, double GM12_2, double GM34_2)
{
   double R12 = GM12_2 / MM.M12_2;
   double R34 = GM34_2 / MM.M34_2;

   double A = -4 * R34 * R12 * R12 * MM.MBB_2 * MM.MBA_2;
   double B = -4 * R12 * R34 * MM.MAB_2 * MM.MBA_2 - 4 * R12 * R34 * MM.MAA_2 * MM.MBB_2 + (GM4l_2 - GM12_2 - GM34_2) * (GM4l_2 - GM12_2 - GM34_2);
   double C = -4 * R34 * MM.MAB_2 * MM.MAA_2;

   if(B * B < 4 * A * C)
      return -999999;
   if(B < 0)
      return -999999;

   double Value = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
   return sqrt(Value);
}
//----------------------------------------------------------------------------
bool HybridCalculator::HasSolutionForAnyC1(double RMAA_2, double RMBB_2, double RMBA_2, double RMAB_2, double RM12_2, double RM34_2,
   double GM4l_2, double GM12_2, double GM34_2)
{
   double R12 = GM12_2 / RM12_2;
   double R34 = GM34_2 / RM34_2;

   double A = -4 * R34 * R12 * R12 * RMBB_2 * RMBA_2;
   double B = -4 * R12 * R34 * RMAB_2 * RMBA_2 - 4 * R12 * R34 * RMAA_2 * RMBB_2 + (GM4l_2 - GM12_2 - GM34_2) * (GM4l_2 - GM12_2 - GM34_2);
   double C = -4 * R34 * RMAB_2 * RMAA_2;

   if(B * B < 4 * A * C)
      return false;
   if(B < 0)
      return false;

   return true;
}
//----------------------------------------------------------------------------
double HybridCalculator::FindLeftEndForC1(double RMAA_2, double RMBB_2, double RMBA_2, double RMAB_2, double RM12_2, double RM34_2,
   double GM4l_2, double GM12_2, double GM34_2)
{
   double R12 = GM12_2 / RM12_2;
   double R34 = GM34_2 / RM34_2;

   double A = -4 * R34 * R12 * R12 * RMBB_2 * RMBA_2;
   double B = -4 * R12 * R34 * RMAB_2 * RMBA_2 - 4 * R12 * R34 * RMAA_2 * RMBB_2 + (GM4l_2 - GM12_2 - GM34_2) * (GM4l_2 - GM12_2 - GM34_2);
   double C = -4 * R34 * RMAB_2 * RMAA_2;

   if(B * B < 4 * A * C)
      return -999999;
   if(B < 0)
      return -999999;

   double Value = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
   if(Value < 0)
      Value = 0;

   return sqrt(Value);
}
//----------------------------------------------------------------------------
double HybridCalculator::FindRightEndForC1(double RMAA_2, double RMBB_2, double RMBA_2, double RMAB_2, double RM12_2, double RM34_2,
   double GM4l_2, double GM12_2, double GM34_2)
{
   double R12 = GM12_2 / RM12_2;
   double R34 = GM34_2 / RM34_2;

   double A = -4 * R34 * R12 * R12 * RMBB_2 * RMBA_2;
   double B = -4 * R12 * R34 * RMAB_2 * RMBA_2 - 4 * R12 * R34 * RMAA_2 * RMBB_2 + (GM4l_2 - GM12_2 - GM34_2) * (GM4l_2 - GM12_2 - GM34_2);
   double C = -4 * R34 * RMAB_2 * RMAA_2;

   if(B * B < 4 * A * C)
      return -999999;
   if(B < 0)
      return -999999;

   double Value = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
   return sqrt(Value);
}
//----------------------------------------------------------------------------
std::string HybridCalculator::TextBool(bool Meow)
{
   return (Meow == true) ? "true" : "false";
}
//----------------------------------------------------------------------------
void HybridCalculator::FillMassPosition(int Step, double Center, double Window,
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
void HybridCalculator::FillMassWeights(int Step, double Masses[], double Weights[])
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
bool HybridCalculator::PrepareForIntegral(const EventParameters &RecoParameter, double Z1, double Z2)
{
   // Get central gen-level leptons
   if(DoDeltaMH == false)
   {
      bool Good = PrepareForBackgroundIntegral(RecoParameter, Z1, Z2);
      if(Good == false)
         return false;
   }
   else
   {
      bool Good = PrepareForSignalIntegral(RecoParameter, Z1, Z2);
      if(Good == false)
         return false;
   }
   CentralParameters = ConvertVectorsToAnglesRoberto(CentralLeptons);
   CentralParametersAlt = ConvertVectorsToAnglesRoberto(CentralLeptonsAlt);
   CentralParametersLeft = ConvertVectorsToAnglesRoberto(CentralLeptonsLeft);
   CentralParametersRight = ConvertVectorsToAnglesRoberto(CentralLeptonsRight);

   // Store mass squares for later use
   CentralMM = MassSquare(CentralLeptons);
   CentralAltMM = MassSquare(CentralLeptonsAlt);
   CentralLeftMM = MassSquare(CentralLeptonsLeft);
   CentralRightMM = MassSquare(CentralLeptonsRight);

   return true;
}
//----------------------------------------------------------------------------
bool HybridCalculator::PrepareForSignalIntegral(const EventParameters &RecoParameter, double Z1, double Z2)
{
   LeptonVectors TargetLeptons = ConvertAnglesToVectorsRoberto(RecoParameter);

   double Z1Ratio = Z1 / RecoParameter.ZMass;
   double Z2Ratio = Z2 / RecoParameter.Z2Mass;
   CentralLeptons = TargetLeptons;
   CentralLeptonsAlt = TargetLeptons;
   CentralLeptonsLeft = TargetLeptons;
   CentralLeptonsRight = TargetLeptons;
   CCoordinates.CPReco_1 = 0, CCoordinates.CPReco_2 = 0, CCoordinates.CSReco = 1;

   CentralLeptons.Lepton12 = CentralLeptons.Lepton12 * Z1Ratio * Z1Ratio;
   CentralLeptons.Lepton22 = CentralLeptons.Lepton22 * Z2Ratio * Z2Ratio;
   CentralLeptonsAlt.Lepton12 = CentralLeptonsAlt.Lepton12 * Z1Ratio * Z1Ratio;
   CentralLeptonsAlt.Lepton22 = CentralLeptonsAlt.Lepton22 * Z2Ratio * Z2Ratio;
   CentralLeptonsLeft.Lepton12 = CentralLeptonsLeft.Lepton12 * Z1Ratio * Z1Ratio;
   CentralLeptonsLeft.Lepton22 = CentralLeptonsLeft.Lepton22 * Z2Ratio * Z2Ratio;
   CentralLeptonsRight.Lepton12 = CentralLeptonsRight.Lepton12 * Z1Ratio * Z1Ratio;
   CentralLeptonsRight.Lepton22 = CentralLeptonsRight.Lepton22 * Z2Ratio * Z2Ratio;

   MassSquare MM = MassSquare(CentralLeptons);
   MassSquare FlippedMM = MM.FlipZ1Z2();

   MassSquare FlippedRecoMM = RecoMM.FlipZ1Z2();

   bool HasSolution = true;
   if(FFFirstZ == true)
      HasSolution = HasSolutionForAnyC1(RecoMM, DeltaMH * DeltaMH, MM.M12_2, MM.M34_2);
   else
      HasSolution = HasSolutionForAnyC1(FlippedRecoMM, DeltaMH * DeltaMH, MM.M34_2, MM.M12_2);

   if(HasSolution == false)
      return false;
   if(DeltaMH * DeltaMH < MM.M12_2 + MM.M34_2)   // No positive c_p solution no matter what
      return false;

   if(FFFirstZ == true)
   {
      CCoordinates.CSReco_Left = FindLeftEndForC1(RecoMM, DeltaMH * DeltaMH, MM.M12_2, MM.M34_2);
      CCoordinates.CSReco_Right = FindRightEndForC1(RecoMM, DeltaMH * DeltaMH, MM.M12_2, MM.M34_2);

      if(CCoordinates.CSReco_Left > CCoordinates.CSReco_Right)
         std::swap(CCoordinates.CSReco_Left, CCoordinates.CSReco_Right);

      double CPReco_FlatLeft = FindLeftEndForC1(FlippedRecoMM, DeltaMH * DeltaMH, MM.M34_2, MM.M12_2);
      double CPReco_FlatRight = FindRightEndForC1(FlippedRecoMM, DeltaMH * DeltaMH, MM.M34_2, MM.M12_2);

      if(CPReco_FlatLeft > CPReco_FlatRight)
         std::swap(CPReco_FlatLeft, CPReco_FlatRight);

      CCoordinates.CSReco_FlatLeft =
         (CalculateCP(FlippedMM, DeltaMH * DeltaMH, CPReco_FlatLeft + 0.00001, true)
          + CalculateCP(FlippedMM, DeltaMH * DeltaMH, CPReco_FlatLeft + 0.00001, false)) / 2;
      CCoordinates.CSReco_FlatRight =
         (CalculateCP(FlippedMM, DeltaMH * DeltaMH, CPReco_FlatRight - 0.00001, true)
          + CalculateCP(FlippedMM, DeltaMH * DeltaMH, CPReco_FlatRight - 0.00001, false)) / 2;

      if(CCoordinates.CSReco_FlatLeft > CCoordinates.CSReco_FlatRight)
         std::swap(CCoordinates.CSReco_FlatLeft, CCoordinates.CSReco_FlatRight);

      CCoordinates.CSReco_LeftLimit = (CCoordinates.CSReco_Left + CCoordinates.CSReco_FlatLeft * TipRangeFactor) / (1 + TipRangeFactor);
      CCoordinates.CSReco_RightLimit = (CCoordinates.CSReco_Right + CCoordinates.CSReco_FlatRight * TipRangeFactor) / (1 + TipRangeFactor);

      CCoordinates.CPReco_LeftUp = CalculateCP(MM, DeltaMH * DeltaMH, CCoordinates.CSReco_LeftLimit, true);
      CCoordinates.CPReco_LeftDown = CalculateCP(MM, DeltaMH * DeltaMH, CCoordinates.CSReco_LeftLimit, false);
      CCoordinates.CPReco_RightUp = CalculateCP(MM, DeltaMH * DeltaMH, CCoordinates.CSReco_RightLimit, true);
      CCoordinates.CPReco_RightDown = CalculateCP(MM, DeltaMH * DeltaMH, CCoordinates.CSReco_RightLimit, false);

      if(CCoordinates.CPReco_LeftUp < CCoordinates.CPReco_LeftDown)
         std::swap(CCoordinates.CPReco_LeftUp, CCoordinates.CPReco_LeftDown);
      if(CCoordinates.CPReco_RightUp < CCoordinates.CPReco_RightDown)
         std::swap(CCoordinates.CPReco_RightUp, CCoordinates.CPReco_RightDown);

      CCoordinates.CPReco_LeftUp = std::min(CCoordinates.CPReco_LeftUp, IntegralCMax);
      CCoordinates.CPReco_LeftDown = std::max(CCoordinates.CPReco_LeftDown, IntegralCMin);
      CCoordinates.CPReco_RightUp = std::min(CCoordinates.CPReco_RightUp, IntegralCMax);
      CCoordinates.CPReco_RightDown = std::max(CCoordinates.CPReco_RightDown, IntegralCMin);

      if(CCoordinates.CPReco_LeftUp > CCoordinates.CPReco_LeftDown)
         CCoordinates.CPReco_LeftCenter = (CCoordinates.CPReco_LeftUp + CCoordinates.CPReco_LeftDown) / 2;
      else
         CCoordinates.CPReco_LeftCenter = -1;
      if(CCoordinates.CPReco_RightUp > CCoordinates.CPReco_RightDown)
         CCoordinates.CPReco_RightCenter = (CCoordinates.CPReco_RightUp + CCoordinates.CPReco_RightDown) / 2;
      else
         CCoordinates.CPReco_RightCenter = -1;

      if(CCoordinates.CPReco_LeftCenter > 0)
      {
         CCoordinates.CSReco_LeftCenter =
            std::min(CalculateCP(FlippedMM, DeltaMH * DeltaMH, CCoordinates.CPReco_LeftCenter, true),
                  CalculateCP(FlippedMM, DeltaMH * DeltaMH, CCoordinates.CPReco_LeftCenter, false));
      }
      if(CCoordinates.CPReco_RightCenter > 0)
      {
         CCoordinates.CSReco_RightCenter =
            std::max(CalculateCP(FlippedMM, DeltaMH * DeltaMH, CCoordinates.CPReco_RightCenter, true),
                  CalculateCP(FlippedMM, DeltaMH * DeltaMH, CCoordinates.CPReco_RightCenter, false));
      }
   }
   else
   {
      // TODO
   }

   if(CCoordinates.CSReco_Right < 0)   // WTF
      return false;

   double Min = std::max(IntegralCMin, CCoordinates.CSReco_Left);
   double Max = std::min(IntegralCMax, CCoordinates.CSReco_Right);
   if(Min > Max)   // Allowed C1 range has no overlap with integration range
      return false;

   Min = std::max(IntegralCMin, CCoordinates.CSReco_LeftLimit);
   Max = std::min(IntegralCMax, CCoordinates.CSReco_RightLimit);
   if(Min > Max)   // Bulk region has no overlap with integration range
      CCoordinates.CSReco = -1;
   else
      CCoordinates.CSReco = (Min + Max) / 2;

   if(CCoordinates.CSReco > 0)
   {
      if(FFFirstZ == true)
      {
         CCoordinates.CPReco_1 = CalculateCP(MM, DeltaMH * DeltaMH, CCoordinates.CSReco, true);
         CCoordinates.CPReco_2 = CalculateCP(MM, DeltaMH * DeltaMH, CCoordinates.CSReco, false);
      }
      else
      {
         CCoordinates.CPReco_1 = CalculateCP(FlippedMM, DeltaMH * DeltaMH, CCoordinates.CSReco, true);
         CCoordinates.CPReco_2 = CalculateCP(FlippedMM, DeltaMH * DeltaMH, CCoordinates.CSReco, false);
      }
   }

   if(CCoordinates.CSReco > 0)
   {
      if(CCoordinates.CPReco_1 < 1e-5 || CCoordinates.CPReco_1 != CCoordinates.CPReco_1)
      {
         std::cerr << CCoordinates.CSReco << " " << CCoordinates.CPReco_1 << " " << CCoordinates.CPReco_2 << std::endl;
         std::cerr << "[HybridCalculator][SimpleMassIntegral] ERROR!  C3(1) is weird!"
            << "  This should never happen!!  Contact Yi to debug!!!" << std::endl;
         std::cerr << "LeftCenter " << CCoordinates.CSReco_LeftCenter << std::endl;
         std::cerr << "FlatLeft " << CCoordinates.CSReco_FlatLeft << std::endl;
         std::cerr << "LeftLimit " << CCoordinates.CSReco_LeftLimit << std::endl;
         std::cerr << "RightCenter " << CCoordinates.CSReco_RightCenter << std::endl;
         std::cerr << "FlatRight " << CCoordinates.CSReco_FlatRight << std::endl;
         std::cerr << "RightLimit " << CCoordinates.CSReco_RightLimit << std::endl;
         std::cerr << "Middle " << CCoordinates.CSReco << std::endl;
         std::cerr << "Left " << CCoordinates.CSReco_Left << std::endl;
         std::cerr << "Right " << CCoordinates.CSReco_Right << std::endl;
      }
      if(CCoordinates.CPReco_2 < 1e-5 || CCoordinates.CPReco_2 != CCoordinates.CPReco_2)
         std::cerr << "[HybridCalculator][SimpleMassIntegral] ERROR!  C3(2) is weird!"
            << "  This should never happen!!  Contact Yi to debug!!!" << std::endl;
   }

   if(FFFirstZ == true)
   {
      CentralLeptons.Lepton11 = CentralLeptons.Lepton11 / CCoordinates.CSReco;
      CentralLeptons.Lepton12 = CentralLeptons.Lepton12 * CCoordinates.CSReco;
      CentralLeptonsAlt.Lepton11 = CentralLeptonsAlt.Lepton11 / CCoordinates.CSReco;
      CentralLeptonsAlt.Lepton12 = CentralLeptonsAlt.Lepton12 * CCoordinates.CSReco;
      CentralLeptonsLeft.Lepton11 = CentralLeptonsLeft.Lepton11 / CCoordinates.CSReco_LeftCenter;
      CentralLeptonsLeft.Lepton12 = CentralLeptonsLeft.Lepton12 * CCoordinates.CSReco_LeftCenter;
      CentralLeptonsRight.Lepton11 = CentralLeptonsRight.Lepton11 / CCoordinates.CSReco_RightCenter;
      CentralLeptonsRight.Lepton12 = CentralLeptonsRight.Lepton12 * CCoordinates.CSReco_RightCenter;

      CentralLeptons.Lepton21 = CentralLeptons.Lepton21 / CCoordinates.CPReco_1;
      CentralLeptons.Lepton22 = CentralLeptons.Lepton22 * CCoordinates.CPReco_1;
      CentralLeptonsAlt.Lepton21 = CentralLeptonsAlt.Lepton21 / CCoordinates.CPReco_2;
      CentralLeptonsAlt.Lepton22 = CentralLeptonsAlt.Lepton22 * CCoordinates.CPReco_2;
      CentralLeptonsLeft.Lepton21 = CentralLeptonsLeft.Lepton21 / CCoordinates.CPReco_LeftCenter;
      CentralLeptonsLeft.Lepton22 = CentralLeptonsLeft.Lepton22 * CCoordinates.CPReco_LeftCenter;
      CentralLeptonsRight.Lepton21 = CentralLeptonsRight.Lepton21 / CCoordinates.CPReco_RightCenter;
      CentralLeptonsRight.Lepton22 = CentralLeptonsRight.Lepton22 * CCoordinates.CPReco_RightCenter;
   }
   else
   {
      // TODO
   }

   // std::cout << CentralLeptons << " " << CentralLeptonsAlt << std::endl;
   // std::cout << CentralLeptonsLeft << " " << CentralLeptonsRight << std::endl;
   // std::cout << "---" << std::endl;

   return true;
}
//----------------------------------------------------------------------------
bool HybridCalculator::PrepareForBackgroundIntegral(const EventParameters &RecoParameter, double Z1, double Z2)
{
   LeptonVectors TargetLeptons = ConvertAnglesToVectorsRoberto(RecoParameter);

   double Z1Ratio = Z1 / RecoParameter.ZMass;
   double Z2Ratio = Z2 / RecoParameter.Z2Mass;
   CentralLeptons = TargetLeptons;
   CentralLeptonsAlt = TargetLeptons;
   CentralLeptonsLeft = TargetLeptons;
   CentralLeptonsRight = TargetLeptons;

   if(LeptonReversal == false)
   {
      CentralLeptons.Lepton12 = CentralLeptons.Lepton12 * Z1Ratio * Z1Ratio;
      CentralLeptons.Lepton22 = CentralLeptons.Lepton22 * Z2Ratio * Z2Ratio;
   }
   else
   {
      CentralLeptons.Lepton11 = CentralLeptons.Lepton11 * Z1Ratio * Z1Ratio;
      CentralLeptons.Lepton21 = CentralLeptons.Lepton21 * Z2Ratio * Z2Ratio;
   }

   return true;
}
//----------------------------------------------------------------------------
double HybridCalculator::CalculateJS(MassSquare &RMM, Cs &C, bool IsTip)
{
   double &CA12 = C.c[0];
   double &CB12 = C.c[1];
   double &CA34 = C.c[2];
   double &CB34 = C.c[3];

   double dMH2dcA34 = -(RMM.MAA_2 / CA12 + RMM.MBA_2 / CB12 + RMM.M34_2 / CB34) / CA34 / CA34;
   double dMH2dcB34 = -(RMM.MAB_2 / CA12 + RMM.MBB_2 / CB12 + RMM.M34_2 / CA34) / CB34 / CB34;

   double dM12dcB12 = -RMM.M12_2 / CA12 / CB12 / CB12;
   double dM22dcA34 = -RMM.M34_2 / CA34 / CA34 / CB34;
   double dM22dcB34 = -RMM.M34_2 / CA34 / CB34 / CB34;

   if(IsTip == true)
   {
      dMH2dcA34 = -(RMM.MAA_2 / CA34 + RMM.MAB_2 / CB34 + RMM.M12_2 / CB12) / CA12 / CA12;
      dMH2dcB34 = -(RMM.MBA_2 / CA34 + RMM.MBB_2 / CB34 + RMM.M12_2 / CA12) / CB12 / CB12;
      dM12dcB12 = -RMM.M34_2 / CA34 / CB34 / CB34;
      dM22dcA34 = -RMM.M12_2 / CA12 / CA12 / CB12;
      dM22dcB34 = -RMM.M12_2 / CA12 / CB12 / CB12;
   }

   double Jacobian = dM12dcB12 * (dM22dcA34 * dMH2dcB34 - dM22dcB34 * dMH2dcA34);

   if(fabs(Jacobian) < 1 && CA12 > IntegralCMin && CA12 < IntegralCMax
         && CB12 > IntegralCMin && CB12 < IntegralCMax
         && CA34 > IntegralCMin && CA34 < IntegralCMax
         && CB34 > IntegralCMin && CB34 < IntegralCMax)
   {
      if(IsTip == true)   std::cout << "Tip" << std::endl;
      else              std::cout << "Bulk" << std::endl;
      std::cout << "J " << dM12dcB12 << " " << dM22dcA34 << " " << dM22dcB34
         << " " << dMH2dcA34 << " " << dMH2dcB34 << " " << Jacobian << std::endl;
   }

   return 1 / Jacobian;
}
//----------------------------------------------------------------------------
std::pair<double, double> HybridCalculator::GuessCenter(const EventParameters &RecoParameter)
{
   return GuessCenter(RecoParameter, RecoParameter.ZMass, RecoParameter.Z2Mass);
}
//----------------------------------------------------------------------------
std::pair<double, double> HybridCalculator::GuessCenter(const EventParameters &RecoParameter, double Z1, double Z2)
{
   RecoMM = MassSquare(ConvertAnglesToVectorsRoberto(RecoParameter));
   
   double CurrentCenterZ1 = Z1;
   double CurrentCenterZ2 = Z2;
   double CurrentWindowSize = (SimpleMassIntegralWindowPlus + SimpleMassIntegralWindowMinus) / 2;
   double ScanStep = 8;

   double BestZ1 = Z1;
   double BestZ2 = Z2;
   double BestValue = 0;

   std::vector<double> Result(MECount);

   int PassCount = 8;
   for(int iPass = 0; iPass < PassCount; iPass++)
   {
      for(int i1 = 0; i1 < ScanStep; i1++)
      {
         double M1 = CurrentCenterZ1 + CurrentWindowSize / (ScanStep - 1) * (i1 - ScanStep / 2);

         for(int i2 = 0; i2 < ScanStep; i2++)
         {
            Result[0] = 0;

            double M2 = CurrentCenterZ2 + CurrentWindowSize / (ScanStep - 1) * (i2 - ScanStep / 2);

            bool Good = PrepareForIntegral(RecoParameter, M1, M2);
            if(Good == true)
               CalculateIntegrand(RecoParameter, CentralParameters, CentralParametersAlt,
                  CentralParametersLeft, CentralParametersRight, Result);

            if(BestValue < 0 || fabs(Result[0]) > BestValue)
            {
               BestZ1 = M1;
               BestZ2 = M2;
               BestValue = fabs(Result[0]);
            }
         }
      }

      CurrentCenterZ1 = BestZ1;
      CurrentCenterZ2 = BestZ2;
      CurrentWindowSize = CurrentWindowSize * 0.66;
   }

   return std::pair<double, double>(BestZ1, BestZ2);
}
//----------------------------------------------------------------------------
MassSquare::MassSquare()
{
   M12_2 = 0, M34_2 = 0, MAA_2 = 0, MBB_2 = 0, MAB_2 = 0, MBA_2 = 0;
}
//----------------------------------------------------------------------------
MassSquare::MassSquare(const EventParameters &Event)
{
   LeptonVectors Vectors = ConvertAnglesToVectorsRoberto(Event);

   M12_2 = (Vectors.Lepton11 + Vectors.Lepton12).GetMass2();
   M34_2 = (Vectors.Lepton21 + Vectors.Lepton22).GetMass2();
   MAA_2 = (Vectors.Lepton11 + Vectors.Lepton21).GetMass2();
   MAB_2 = (Vectors.Lepton11 + Vectors.Lepton22).GetMass2();
   MBA_2 = (Vectors.Lepton12 + Vectors.Lepton21).GetMass2();
   MBB_2 = (Vectors.Lepton12 + Vectors.Lepton22).GetMass2();
}
//----------------------------------------------------------------------------
MassSquare::MassSquare(const LeptonVectors &Vectors)
{
   M12_2 = (Vectors.Lepton11 + Vectors.Lepton12).GetMass2();
   M34_2 = (Vectors.Lepton21 + Vectors.Lepton22).GetMass2();
   MAA_2 = (Vectors.Lepton11 + Vectors.Lepton21).GetMass2();
   MAB_2 = (Vectors.Lepton11 + Vectors.Lepton22).GetMass2();
   MBA_2 = (Vectors.Lepton12 + Vectors.Lepton21).GetMass2();
   MBB_2 = (Vectors.Lepton12 + Vectors.Lepton22).GetMass2();
}
//----------------------------------------------------------------------------
MassSquare MassSquare::FlipZ1Z2()
{
   MassSquare NewOne;
   NewOne.M12_2 = M34_2;   NewOne.M34_2 = M12_2;
   NewOne.MAA_2 = MAA_2;   NewOne.MBB_2 = MBB_2;
   NewOne.MAB_2 = MBA_2;   NewOne.MBA_2 = MAB_2;
   return NewOne;
}
//----------------------------------------------------------------------------
MassSquare MassSquare::FlipLALB()
{
   MassSquare NewOne;
   NewOne.M12_2 = M12_2;   NewOne.M34_2 = M34_2;
   NewOne.MAA_2 = MBB_2;   NewOne.MBB_2 = MAA_2;
   NewOne.MAB_2 = MBA_2;   NewOne.MBA_2 = MAB_2;
   return NewOne;
}
//----------------------------------------------------------------------------





