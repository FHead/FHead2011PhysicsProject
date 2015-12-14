//----------------------------------------------------------------------------
#ifndef HybridCalculator_H_KASJDGKASIKGJAHNIWJHNISDHIFASDF
#define HybridCalculator_H_KASJDGKASIKGJAHNIWJHNISDHIFASDF
//----------------------------------------------------------------------------
#include "Code/TauHelperFunctions2.h"
//----------------------------------------------------------------------------
#include "AngleConversion.h"
#include "VolumeElement.h"
//----------------------------------------------------------------------------
// #define HYBRIDCALCULATOR_DEBUG
//----------------------------------------------------------------------------
class MassSquare;
class SignalCoordinates;
class HybridCalculator;
//----------------------------------------------------------------------------
class MassSquare
{
public:
   double M12_2, M34_2, MAA_2, MAB_2, MBA_2, MBB_2;
public:
   MassSquare();
   MassSquare(const EventParameters &Event);
   MassSquare(const LeptonVectors &Vectors);
   MassSquare FlipZ1Z2();
   MassSquare FlipLALB();
};
//----------------------------------------------------------------------------
class SignalCoordinates
{
public:
   double CSReco_Left, CSReco_Right, CSReco;   // CS = the one we scan
   double CSReco_FlatLeft, CSReco_FlatRight;
   double CSReco_LeftLimit, CSReco_RightLimit;
   double CPReco_LeftUp, CPReco_LeftDown, CPReco_LeftCenter, CSReco_LeftCenter;
   double CPReco_RightUp, CPReco_RightDown, CPReco_RightCenter, CSReco_RightCenter;
   double CPReco_1, CPReco_2;                  // CP = the one that's passive
};
//----------------------------------------------------------------------------
class HybridCalculator
{
public:
   HybridCalculator();
   ~HybridCalculator();
   HybridCalculator &operator =(const HybridCalculator &other);
public:
   enum VerboseLevel
   {
      VerboseLevel_Quiet = 0,
      VerboseLevel_Normal = 1
   };
public:
   void SetVerbosity(VerboseLevel Value);
   void SetEfficiency12(double (*F)(double, double, double));
   void SetEfficiency34(double (*F)(double, double, double));
   void SetSmear12(double (*F)(const FourVector &, double));
   void SetSmear34(double (*F)(const FourVector &, double));
   void SetPTYDensity(double (*F)(double, double, double));
   void SetMECalculator(double (*F)(LeptonVectors &));
   void SetToleranceF(double Tolerance);
   void SetMaxDepthF(int Depth);
   void SetIgnorePhi(bool Decision = false);
   void SetApplyEfficiencyAtEnd(bool Decision = true);
   void SetSimpleMassIntegralWindow(double Window);
   void SetSimpleMassIntegralWindow(bool SumZ, double Window);
   void SetSimpleMassIntegralStep(int Step);
   void SetSimpleMassIntegralStep(bool SumZ, int Step);
   void SetExpansionOrder(int Value);
   void SetLeptonReversal(bool Decision = false);
   void SetRotatingLeptonReversal(bool Decision = false);
   void SetDoDeltaMH(bool Decision = false, double Value = -1);
   void SetDoGaussMH(bool Decision = false, double Value = -1, double Width = -1);
   void SetIntegralCRange(double Min, double Max);
   void SetIntegralCStep(int Step);
   void SetAttractorStrength(double Strength);
   void SetAttractorStrength(bool SumZ, double Strength);
   void SetDoDiagonal(bool Decision);
   void SetIncludeSwapping(bool Decision);
   void SetFlatApproximation(bool Decision);
   void SetUsePPPP(bool Decision);
   void SetDebugPrintIntegrand(bool Decision);
   void SetTipRangeFactor(double Value);
   void SetIgnoreTip(bool Decision);
   void SetDoPTZero(bool Decision);
   void SetRecursiveMassIntegralWindow(double Window);
   void SetRecursiveMassIntegralWindow(bool SumZ, double Window);
   void SetRecursiveMassIntegralStep(int Step);
   void SetRecursiveMassIntegralStep(bool SumZ, int Step);
   void SetRecursiveMaxDepthM1(int Depth);
   void SetRecursiveMaxDepthM2(int Depth);
   void SetRecursiveMaxToleranceM1(std::vector<double> Value);
   void SetRecursiveMaxToleranceM2(std::vector<double> Value);
   void SetUseSmartCenter(bool Decision);
   void SetDoReboot(bool Decision);
public:
   void PrintSettings();
   void PrintSettings(std::ostream &out);
   void TestOutput();
private:
   double (*Efficiency12)(double, double, double);
   double (*Efficiency34)(double, double, double);
   double (*Smear12)(const FourVector &, double);
   double (*Smear34)(const FourVector &, double);
   double (*PTYDensity)(double, double, double);
   std::vector<double (*)(LeptonVectors &)> CalculateMEValue;
   int MECount;
public:
   std::vector<double> SimpleMassIntegral(const EventParameters &TargetParameters);
   std::vector<double> RecursiveMassIntegral(const EventParameters &TargetParameters);
   std::vector<double> PassThroughMode(const EventParameters &TargetParameters);
private:
   void AdaptiveMass1Integral(const EventParameters &TargetParameters, std::vector<double> &Iab,
      double MBa, double MBb, std::vector<double> &fa, std::vector<double> &fc, std::vector<double> &fb, double ToleranceFactor, int Depth);
   void CalculateMass1Integrand(const EventParameters &TargetParameters, double MA, std::vector<double> &Result);
   void AdaptiveMass2Integral(const EventParameters &TargetParameters, double MA, std::vector<double> &Iab,
      double MBa, double MBb, std::vector<double> &fa, std::vector<double> &fc, std::vector<double> &fb, double ToleranceFactor, int Depth);
   void CalculateMass2Integrand(const EventParameters &TargetParameters, double MA, double MB, std::vector<double> &Result);
   void CalculateIntegrand(const EventParameters &TargetParameters, const EventParameters &CentralParameters,
      const EventParameters &CentralParametersAlt, const EventParameters &CentralParametersLeft,
      const EventParameters &CentralParametersRight, std::vector<double> &Result);
   void CalculateMEs(const EventParameters &CentralValue, std::vector<double> &ME0,
      std::vector<double> &B1, std::vector<double> &B3, std::vector<double> &B11,
      std::vector<double> &B13, std::vector<double> &B33);
   void CalculateMEsDeltaMH(const EventParameters &CentralValue, std::vector<double> &ME0,
      std::vector<double> &B1, std::vector<double> &B11, bool FirstZ, bool Branch, bool Tip);
   double CalculateF(double M, double M0, int Order, bool FirstZ);
   double CalculateFF(double M, double M0, double AnotherM, double AnotherM0, int Order, int AnotherOrder,
      bool FirstZ, bool Branch, bool Tip);
   double AdaptCalculateF(double sab, double fa, double fc, double fb, double a, double b,
      double Tolerance, double c1c2, int Order, bool FirstZ, int Depth);
   double AdaptCalculateFF(double sab, double fa, double fc, double fb, double a, double b,
      double Tolerance, double c1c2, int Order1, double c3c4, int Order3, bool FirstZ, int Depth, bool Branch,
      bool Tip);
   double f(double x, double c1c2, int Order, bool FirstZ);
   double ff(double x, double c1c2, double c3c4, int Order1, int Order3, bool FirstZ, bool Branch, bool Tip);
   double GetSinAngle(const EventParameters &Center, const EventParameters &A, const EventParameters &B);
   LeptonVectors GoToRest(LeptonVectors Leptons);
   double CalculateCP(double MAA_2, double MBB_2, double MBA_2, double MAB_2, double M12_2, double M34_2,
      double M4l_2, double C1, bool Branch);
   double MHExp(const LeptonVectors &Leptons);
   bool HasSolutionForAnyC1(double RMAA_2, double RMBB_2, double RMBA_2, double RMAB_2, double RM12_2, double RM34_2,
      double GM4l_2, double GM12_2, double GM34_2);
   double FindLeftEndForC1(double RMAA_2, double RMBB_2, double RMBA_2, double RMAB_2, double RM12_2, double RM34_2,
      double GM4l_2, double GM12_2, double GM34_2);
   double FindRightEndForC1(double RMAA_2, double RMBB_2, double RMBA_2, double RMAB_2, double RM12_2, double RM34_2,
      double GM4l_2, double GM12_2, double GM34_2);
   double CalculateCP(MassSquare &MM, double M4l_2, double C1, bool Branch);
   bool HasSolutionForAnyC1(MassSquare &MM, double GM4l_2, double GM12_2, double GM34_2);
   double FindLeftEndForC1(MassSquare &MM, double GM4l_2, double GM12_2, double GM34_2);
   double FindRightEndForC1(MassSquare &MM, double GM4l_2, double GM12_2, double GM34_2);
   void FillMassPosition(int Step, double Center, double Window, double AttractorStrength, double Masses[]);
   void FillMassWeights(int Step, double Masses[], double Weights[]);
   bool PrepareForIntegral(const EventParameters &RecoParameter, double Z1, double Z2);
   bool PrepareForSignalIntegral(const EventParameters &RecoParameter, double Z1, double Z2);
   bool PrepareForBackgroundIntegral(const EventParameters &RecoParameter, double Z1, double Z2);
   double CalculateJS(MassSquare &RMM, Cs &C, bool IsTip);
   std::pair<double, double> GuessCenter(const EventParameters &RecoParameter);
   std::pair<double, double> GuessCenter(const EventParameters &RecoParameter, double Z1, double Z2);
private:
   int Verbosity;
   double RecursiveMassIntegralUniversalFactor;
   std::vector<double> ToleranceM1;   int MaxDepthM1;
   std::vector<double> ToleranceM2;   int MaxDepthM2;
   double RecursiveMassIntegralM1Min, RecursiveMassIntegralM1Max;
   double RecursiveMassIntegralM2Min, RecursiveMassIntegralM2Max;
   int RecursiveMassIntegralM1Step;   double RecursiveMassIntegralM1Window;
   int RecursiveMassIntegralM2Step;   double RecursiveMassIntegralM2Window;
   double ToleranceF;   int MaxDepthF;
   bool IgnorePhi;
   double SimpleMassIntegralWindowPlus, SimpleMassIntegralWindowMinus;
   int SimpleMassIntegralStepPlus, SimpleMassIntegralStepMinus;
   double SimpleMassIntegralAttractorStrengthPlus, SimpleMassIntegralAttractorStrengthMinus;
   int ExpansionOrder;
   bool LeptonReversal, RotatingLeptonReversal;
   bool DoDeltaMH;   double DeltaMH;
   bool DoGaussMH;   double SigmaMH;
   double IntegralCMin, IntegralCMax;   int IntegralCStep;
   bool DoDiagonal;
   bool IncludeSwapping;
   bool FlatApproximation;
   double TipRangeFactor;
   bool IgnoreTip;
   bool DoPTZero;
   bool UseSmartCenter;
   bool DoReboot;
private:
   bool DebugPrintIntegrand;
private:   // temporary variable to avoid passing around too much stuff
   EventParameters TempParameters;
   EventParameters CentralParameters, CentralParametersAlt;
   EventParameters CentralParametersLeft, CentralParametersRight;
   LeptonVectors TempLeptons;
   LeptonVectors CentralLeptons, CentralLeptonsAlt;   // place holder for GEN-level lepton info
   LeptonVectors CentralLeptonsLeft, CentralLeptonsRight;
   MassSquare CentralMM, CentralAltMM, CentralLeftMM, CentralRightMM;
   MassSquare RecoMM;
   SignalCoordinates CCoordinates;
   bool FFFirstZ;
private:
   std::string TextBool(bool Meow);
};
//----------------------------------------------------------------------------
#endif






