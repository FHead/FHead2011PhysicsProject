#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TCanvas.h"

#include "Code/DrawRandom.h"

#include "Constants.h"
#include "AngleConversion.h"
#include "InterpretCoefficient.h"
#include "EFTBases.h"
#include "EFTPriors.h"

// #include "ProjectionHelper.h"
#include "FitClass.h"

#define PI 3.14159265358979323846264338327950288479716939937510

FitConfiguration::FitConfiguration()
{
   SetFloatAs("YYYYYYYY");
   SetFloatFractions("NNNN");
   SetUsePriors("NNNNNNNNNN");

   SetInitialRatios(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
   SetNoSquareMode(false);
   SetBasis(BASIS_AVV);
   SetUUbarDDbarRatio(ListToVector(4, 2, 2, 2, 2));
   SetVerbose(false);
}

FitConfiguration::FitConfiguration(string FloatAs, string FloatFractions, string Priors, vector<double> UUbarDDbarRateRatio)
{
   SetFloatAs(FloatAs);
   SetFloatFractions(FloatFractions);
   SetUsePriors(Priors);

   SetInitialRatios(ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0));
   SetInitialFractions(ListToVector(4, 0, 0, 0, 0));
   SetNoSquareMode(false);
   SetBasis(BASIS_AVV);
   SetUUbarDDbarRatio(UUbarDDbarRateRatio);
   SetVerbose(false);
}
   
FitConfiguration::FitConfiguration(string FloatAs, string FloatFractions,
   vector<double> Ratios, vector<double> Fractions, bool Mode, int BasisDecision, string Priors,
   vector<double> UUbarDDbarRateRatio)
{
   SetFloatAs(FloatAs);
   SetFloatFractions(FloatFractions);
   SetUsePriors(Priors);

   SetInitialRatios(Ratios);
   SetInitialFractions(Fractions);
   SetNoSquareMode(Mode);
   SetBasis(BasisDecision);
   SetUUbarDDbarRatio(UUbarDDbarRateRatio);
   SetVerbose(false);
}

FitConfiguration::~FitConfiguration()
{
}

FitConfiguration &FitConfiguration::operator =(const FitConfiguration &other)
{
   Basis = other.Basis;
   FloatParameter1 = other.FloatParameter1;  Parameter1InitialValue = other.Parameter1InitialValue;
   FloatParameter2 = other.FloatParameter2;  Parameter2InitialValue = other.Parameter2InitialValue;
   FloatParameter3 = other.FloatParameter3;  Parameter3InitialValue = other.Parameter3InitialValue;
   FloatParameter4 = other.FloatParameter4;  Parameter4InitialValue = other.Parameter4InitialValue;
   FloatParameter5 = other.FloatParameter5;  Parameter5InitialValue = other.Parameter5InitialValue;
   FloatParameter6 = other.FloatParameter6;  Parameter6InitialValue = other.Parameter6InitialValue;
   FloatParameter7 = other.FloatParameter7;  Parameter7InitialValue = other.Parameter7InitialValue;
   FloatParameter8 = other.FloatParameter8;  Parameter8InitialValue = other.Parameter8InitialValue;
   FloatFem = other.FloatFem;                FemInitialValue = other.FemInitialValue;
   FloatFme = other.FloatFme;                FmeInitialValue = other.FmeInitialValue;
   FloatFee = other.FloatFee;                FeeInitialValue = other.FeeInitialValue;
   FloatFmm = other.FloatFmm;                FmmInitialValue = other.FmmInitialValue;
   
   for(int i = 0; i < 20; i++)
      UsePriors[i] = other.UsePriors[i];
   
   NoSquareMode = other.NoSquareMode;

   UUbarDDbarRatio = other.UUbarDDbarRatio;
   Verbose = other.Verbose;
}

void FitConfiguration::SetFloats(string FloatAs, string FloatFractions)
{
   SetFloatAs(FloatAs);
   SetFloatFractions(FloatFractions);
}

void FitConfiguration::SetFloatAs(string FloatAs)
{
   FloatParameter1 = false;
   FloatParameter2 = false;
   FloatParameter3 = false;
   FloatParameter4 = false;
   FloatParameter5 = false;
   FloatParameter6 = false;
   FloatParameter7 = false;
   FloatParameter8 = false;

   if(FloatAs.size() > 0 && FloatAs[0] == 'Y')   FloatParameter1 = true;
   if(FloatAs.size() > 1 && FloatAs[1] == 'Y')   FloatParameter2 = true;
   if(FloatAs.size() > 2 && FloatAs[2] == 'Y')   FloatParameter3 = true;
   if(FloatAs.size() > 3 && FloatAs[3] == 'Y')   FloatParameter4 = true;
   if(FloatAs.size() > 4 && FloatAs[4] == 'Y')   FloatParameter5 = true;
   if(FloatAs.size() > 5 && FloatAs[5] == 'Y')   FloatParameter6 = true;
   if(FloatAs.size() > 6 && FloatAs[6] == 'Y')   FloatParameter7 = true;
   if(FloatAs.size() > 7 && FloatAs[7] == 'Y')   FloatParameter8 = true;
}

void FitConfiguration::SetFloatFractions(string FloatFractions)
{
   FloatFem = false;   FloatFme = false;   FloatFee = false;   FloatFmm = false;

   if(FloatFractions.size() > 0 && FloatFractions[0] == 'Y')   FloatFem = true;
   if(FloatFractions.size() > 1 && FloatFractions[1] == 'Y')   FloatFme = true;
   if(FloatFractions.size() > 2 && FloatFractions[2] == 'Y')   FloatFee = true;
   if(FloatFractions.size() > 3 && FloatFractions[3] == 'Y')   FloatFmm = true;
}

void FitConfiguration::SetUsePriors(string Priors)
{
   for(int i = 0; i < 20; i++)
   {
      if(Priors.size() > i && Priors[i] == 'Y')
         UsePriors[i] = true;
      else
         UsePriors[i] = false;
   }
}

void FitConfiguration::SetInitialRatios(const vector<double> Ratios)
{
   if(Ratios.size() > 0)   Parameter1InitialValue = Ratios[0];
   if(Ratios.size() > 1)   Parameter2InitialValue = Ratios[1];
   if(Ratios.size() > 2)   Parameter3InitialValue = Ratios[2];
   if(Ratios.size() > 3)   Parameter4InitialValue = Ratios[3];
   if(Ratios.size() > 4)   Parameter5InitialValue = Ratios[4];
   if(Ratios.size() > 5)   Parameter6InitialValue = Ratios[5];
   if(Ratios.size() > 6)   Parameter7InitialValue = Ratios[6];
   if(Ratios.size() > 7)   Parameter8InitialValue = Ratios[7];
}

void FitConfiguration::SetInitialFractions(const vector<double> Fractions)
{
   if(Fractions.size() > 0)   FemInitialValue = Fractions[0];
   if(Fractions.size() > 1)   FmeInitialValue = Fractions[1];
   if(Fractions.size() > 2)   FeeInitialValue = Fractions[2];
   if(Fractions.size() > 3)   FmmInitialValue = Fractions[3];
}
   
void FitConfiguration::SetNoSquareMode(bool Decision)
{
   NoSquareMode = Decision;
}

void FitConfiguration::SetBasis(int Decision)
{
   Basis = Decision;
}

void FitConfiguration::SetUUbarDDbarRatio(vector<double> Ratio)
{
   while(Ratio.size() < 4)
      Ratio.push_back(2);
   UUbarDDbarRatio = Ratio;
}

void FitConfiguration::SetVerbose(bool Decision)
{
   Verbose = Decision;
}

int FitConfiguration::TotalNumberOfFloats()
{
   int Count = 0;
   
   if(FloatParameter1 == true)      Count = Count + 1;
   if(FloatParameter2 == true)      Count = Count + 1;
   if(FloatParameter3 == true)      Count = Count + 1;
   if(FloatParameter4 == true)      Count = Count + 1;
   if(FloatParameter5 == true)      Count = Count + 1;
   if(FloatParameter6 == true)      Count = Count + 1;
   if(FloatParameter7 == true)      Count = Count + 1;
   if(FloatParameter8 == true)      Count = Count + 1;
   if(FloatFem == true)             Count = Count + 1;
   if(FloatFme == true)             Count = Count + 1;
   if(FloatFee == true)             Count = Count + 1;
   if(FloatFmm == true)             Count = Count + 1;

   return Count;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double Fem = Parameters[8];
   double Fme = Parameters[9];
   double Fee = Parameters[10];
   double Fmm = Parameters[11];

   double As[16] = {0};

   if(Basis == BASIS_AVV)
   {
      As[0]  = 2;   As[1]  = Parameters[0];   As[2]  = Parameters[1];   As[3]  = Parameters[2];
      As[4]  = 0;   As[5]  = Parameters[3];   As[6]  = Parameters[4];   As[7]  = Parameters[5];
      As[8]  = 0;   As[9]  = Parameters[3];   As[10] = Parameters[4];   As[11] = Parameters[5];
      As[12] = 0;   As[13] = Parameters[6];   As[14] = Parameters[7];   As[15] = 0;

      if(AVVEFTMode == true)
      {
         // A4AZR = ((-A2AAR + A2ZZR + 2*A4ZZR)*cW*sW + A2AZR*(-Power(cW,2) + Power(sW,2)))/(Power(cW,2) - Power(sW,2))
         double CW = CONST_CW;
         double SW = CONST_SW;

         As[7] = ((-As[13] + As[1] + 2 * As[3]) * CW * SW + As[5] * (-CW * CW + SW * SW)) / (CW * CW - SW * SW);
         As[11] = As[7];
      }
   }
   else if(Basis == BASIS_HIGGS)
   {
      HiggsBasis H;
      H.DeltaCZ = Parameters[0];
      H.CZB = Parameters[1];
      H.CZZ = Parameters[2];
      H.CZZD = Parameters[3];
      H.CZA = Parameters[4];
      H.CZAD = Parameters[5];
      H.CAA = Parameters[6];
      H.CAAD = Parameters[7];

      AVVBasis A(H);

      As[0]  = A.A1ZZ;   As[1]  = A.A2ZZ;   As[2]  = A.A3ZZ;   As[3]  = A.A4ZZ;
      As[4]  = A.A1ZA;   As[5]  = A.A2ZA;   As[6]  = A.A3ZA;   As[7]  = A.A4ZA;
      As[8]  = A.A1ZA;   As[9]  = A.A2ZA;   As[10] = A.A3ZA;   As[11] = A.A4ZA;
      As[12] = A.A1AA;   As[13] = A.A2AA;   As[14] = A.A3AA;   As[15] = A.A4AA;
   }
   else if(Basis == BASIS_WARSAW)
   {
      WarsawBasis W;
      W.CT = Parameters[0];
      W.CH = Parameters[1];
      W.CWW = Parameters[2];
      W.CWWD = Parameters[3];
      W.CWB = Parameters[4];
      W.CWBD = Parameters[5];
      W.CBB = Parameters[6];
      W.CBBD = Parameters[7];

      AVVBasis A(W);

      As[0]  = A.A1ZZ;   As[1]  = A.A2ZZ;   As[2]  = A.A3ZZ;   As[3]  = A.A4ZZ;
      As[4]  = A.A1ZA;   As[5]  = A.A2ZA;   As[6]  = A.A3ZA;   As[7]  = A.A4ZA;
      As[8]  = A.A1ZA;   As[9]  = A.A2ZA;   As[10] = A.A3ZA;   As[11] = A.A4ZA;
      As[12] = A.A1AA;   As[13] = A.A2AA;   As[14] = A.A3AA;   As[15] = A.A4AA;
   }
   else if(Basis == BASIS_LOOP)
   {
      InterpretationCoefficients C;
      C.yt = Parameters[3];
      C.yta = Parameters[4];
      C.mt = Parameters[5];
      C.gww = Parameters[6];
      C.mw = Parameters[7];

      double A2ZA = InterpretedA2ZA_Roberto14167(C);
      double A3ZA = InterpretedA3ZA_Roberto14167(C);
      double A2AA = InterpretedA2AA_Roberto14167(C);
      double A3AA = InterpretedA3AA_Roberto14167(C);

      // cout << endl;
      // cout << A2ZA << " " << A3ZA << " " << A2AA << " " << A3AA << endl;
      // cout << C.yt << " " << C.yta << " " << C.mt << " " << C.gww << " " << C.mw << endl;

      As[0]  = 2;   As[1]  = Parameters[0];   As[2]  = Parameters[1];   As[3]  = Parameters[2];
      As[4]  = 0;   As[5]  = A2ZA;   As[6]  = A3ZA;   As[7]  = 0;
      As[8]  = 0;   As[9]  = A2ZA;   As[10] = A3ZA;   As[11] = 0;
      As[12] = 0;   As[13] = A2AA;   As[14] = A3AA;   As[15] = 0;
   }
   else
   {
      cerr << "ERROR! BASIS SELECTED = " << Basis << " WHICH DOES NOT EXIST!  RETURNING NONSENSE!!!" << endl;
      return -1912871;
   }

   double LogTotal = 0;

   double OriginalA1ZZ = As[0];
   if(NoSquareMode == true)
      As[0] = 2;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value = 0, Integral = 0, LikelihoodS = 0;
      double LikelihoodB = 0;

      for(int i = 0; i < 16; i++)
      {
         if(i == 4 || i == 8 || i == 12 || i == 15)   // Skip A1ZA, A1AA, A4AA
            continue;

         for(int j = 0; j < 16; j++)
         {
            if(j == 4 || j == 8 || j == 12 || j == 15)
               continue;

            if(NoSquareMode == true && (i != 0 && j != 0))
               continue;

            Value = Value + As[i] * As[j] * VS[i][j][iS];
            Integral = Integral + As[i] * As[j] * IS[i][j][iS];
         }
      }

      if(NoSquareMode == true)
      {
         Value = Value + 2 * As[0] * OriginalA1ZZ * VS[0][0][iS];
         Integral = Integral + 2 * As[0] * OriginalA1ZZ * IS[0][0][iS];
      }

      double Rud = 0;
      if(S[iS] == "em")   Rud = UUbarDDbarRatio[0];
      if(S[iS] == "me")   Rud = UUbarDDbarRatio[1];
      if(S[iS] == "ee")   Rud = UUbarDDbarRatio[2];
      if(S[iS] == "mm")   Rud = UUbarDDbarRatio[3];

      LikelihoodS = Value / Integral;
      LikelihoodB = VB[0][iS] / IB[0][iS] * Rud / (Rud + 1) + VB[1][iS] / IB[1][iS] / (Rud + 1);

      if(LikelihoodS <= 0 || LikelihoodB <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      double F = 0;
      if(S[iS] == "em")   F = Fem;
      if(S[iS] == "me")   F = Fme;
      if(S[iS] == "ee")   F = Fee;
      if(S[iS] == "mm")   F = Fmm;

      LogTotal = LogTotal + log(LikelihoodS * (1 - F) + LikelihoodB * F);
   }

   AVVBasis A;
   A.A1ZZ = OriginalA1ZZ;   A.A1ZA = As[4];   A.A1AA = As[12];
   A.A2ZZ = As[1];          A.A2ZA = As[5];   A.A2AA = As[13];
   A.A3ZZ = As[2];          A.A3ZA = As[6];   A.A3AA = As[14];
   A.A4ZZ = As[3];          A.A4ZA = As[7];   A.A4AA = As[15];

   HiggsBasis H(A);
   WarsawBasis W(A);

   LoopBasis L;
   if(Basis == BASIS_LOOP)
   {
      InterpretationCoefficients C;
      C.yt = Parameters[3];
      C.yta = Parameters[4];
      C.mt = Parameters[5];
      C.gww = Parameters[6];
      C.mw = Parameters[7];

      L = LoopBasis(C);
      L.A2ZZ = As[1];
      L.A3ZZ = As[2];
      L.A4ZZ = As[3];
   }

   if(UsePriors[0] == true)   // RWWZZ
   {
      double RWWZZ = 1;

      if(Basis == BASIS_AVV)      RWWZZ = GetRZZWW_NoSquare_AVV(A);
      if(Basis == BASIS_HIGGS)    RWWZZ = GetRZZWW_NoSquare_Higgs(H);
      if(Basis == BASIS_WARSAW)   RWWZZ = GetRZZWW_NoSquare_Warsaw(W);

      double TrueRWWZZ = 1.18;
      double TrueSigmaRWWZZ = 0.44;

      double Function = exp(-(RWWZZ - TrueRWWZZ) * (RWWZZ - TrueRWWZZ) / (2 * TrueSigmaRWWZZ * TrueSigmaRWWZZ));
      LogTotal = LogTotal + log(Function);
   }
   if(UsePriors[1] == true)   // RZA
   {
      double RZA = GetRZA_AVV(A);

      double TrueRZA = 0.0141977 * 0.0141977;
      double TrueSigmaRZA = TrueRZA * 0.5;

      double Function = exp(-(RZA - TrueRZA) * (RZA - TrueRZA) / (2 * TrueSigmaRZA * TrueSigmaRZA));
      LogTotal = LogTotal + log(Function);
   }
   if(UsePriors[2] == true)   // RAA
   {
      double RAA = GetRAA_AVV(A);

      double TrueRAA = 0.008102360 * 0.008102360;
      double TrueSigmaRAA = TrueRAA * 0.10;

      double Function = exp(-(RAA - TrueRAA) * (RAA - TrueRAA) / (2 * TrueSigmaRAA * TrueSigmaRAA));
      LogTotal = LogTotal + log(Function);
   }
   if(UsePriors[3] == true)   // RHto4l
   {
      double RHto4l = 1;

      if(Basis == BASIS_AVV && NoSquareMode == true)       RHto4l = GetRHto4l_NoSquare_AVV(A);
      if(Basis == BASIS_HIGGS && NoSquareMode == true)     RHto4l = GetRHto4l_NoSquare_Higgs(H);
      if(Basis == BASIS_WARSAW && NoSquareMode == true)    RHto4l = GetRHto4l_NoSquare_Warsaw(W);
      if(Basis == BASIS_AVV && NoSquareMode == false)      RHto4l = GetRHto4l_WithSquare_AVV(A);
      if(Basis == BASIS_HIGGS && NoSquareMode == false)    RHto4l = GetRHto4l_WithSquare_Higgs(H);
      if(Basis == BASIS_WARSAW && NoSquareMode == false)   RHto4l = GetRHto4l_WithSquare_Warsaw(W);

      double TrueRHto4l = 1;
      double TrueSigmaRHto4l = 0.4;

      double Function = exp(-(RHto4l - TrueRHto4l) * (RHto4l - TrueRHto4l) / (2 * TrueSigmaRHto4l * TrueSigmaRHto4l));
      LogTotal = LogTotal + log(Function);
   }
   if(UsePriors[4] == true)   // Higgs All
   {
      double Chi2 = 0;

      if(Basis == BASIS_AVV)      Chi2 = GetChi2_AllHiggs_WithSquare_AVV(A);
      if(Basis == BASIS_HIGGS)    Chi2 = GetChi2_AllHiggs_WithSquare_Higgs(H);
      if(Basis == BASIS_WARSAW)   Chi2 = GetChi2_AllHiggs_WithSquare_Warsaw(W);

      LogTotal = LogTotal + Chi2;
   }
   if(UsePriors[5] == true)   // New Higgs All
   {
      double Chi2 = 0;

      if(Basis == BASIS_AVV)      Chi2 = GetChi2_AllHiggs_Higgs_14252(H);
      if(Basis == BASIS_HIGGS)    Chi2 = GetChi2_AllHiggs_Higgs_14252(H);
      if(Basis == BASIS_WARSAW)   Chi2 = GetChi2_AllHiggs_Warsaw_14252(W);

      LogTotal = LogTotal + Chi2;
   }
   if(UsePriors[6] == true)   // LEP2WW
   {
      double Chi2 = 0;

      if(Basis == BASIS_AVV)      Chi2 = GetChi2_LEP2WW_Higgs_14252(H);
      if(Basis == BASIS_HIGGS)    Chi2 = GetChi2_LEP2WW_Higgs_14252(H);
      if(Basis == BASIS_WARSAW)   Chi2 = GetChi2_LEP2WW_Warsaw_14252(W);

      LogTotal = LogTotal + Chi2;
   }
   if(UsePriors[7] == true)   // Higgs All + LEP
   {
      double Chi2 = 0;

      if(Basis == BASIS_AVV)      Chi2 = GetChi2_HiggsPlusLEP2WW_Higgs_14252(H);
      if(Basis == BASIS_HIGGS)    Chi2 = GetChi2_HiggsPlusLEP2WW_Higgs_14252(H);
      if(Basis == BASIS_WARSAW)   Chi2 = GetChi2_HiggsPlusLEP2WW_Warsaw_14252(W);

      LogTotal = LogTotal + Chi2;
   }
   if(UsePriors[8] == true)   // Loop basis, flat |yt| up to 2 and falls off afterwards
   {
      if(Basis == BASIS_LOOP)
      {
         double LL = GetLLFlatYTSoftEdge(L);
         LogTotal = LogTotal + LL;
      }
   }
   if(UsePriors[9] == true)   // Loop basis, flat |yt| up to 2.5 and falls off afterwards
   {
      if(Basis == BASIS_LOOP)
      {
         double LL = GetLLFlatYTSoftEdgeLoose(L);
         LogTotal = LogTotal + LL;
      }
   }

   if(Verbose == true)
   {
      cout << "[LikelihoodLog] " << FitID << " " << Basis;
      for(int i = 0; i < 12; i++)
         cout << " " << Parameters[i];
      cout << " " << -LogTotal * 2;
      cout << endl;
   }

   return -LogTotal * 2;
}

void FitClass::AddPoint(SingleEvent &event)
{
   AddPoint(event.VS, event.IS, event.VB, event.IB, event.event, event.state);
}

void FitClass::AddPoint(double vs[16][16], double is[16][16], double vb[2], double ib[2],
   EventParameters &Event, string State)
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 16; i2++)
      {
         VS[i1][i2].push_back(vs[i1][i2]);
         IS[i1][i2].push_back(is[i1][i2]);
      }
   }

   for(int i = 0; i < 2; i++)
   {
      VB[i].push_back(vb[i]);
      IB[i].push_back(ib[i]);
   }

   E.push_back(Event);
   S.push_back(State);

   SampleSize = SampleSize + 1;
}

int FitClass::PointCount()
{
   return SampleSize;
}

void FitClass::ClearPoints()
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 16; i2++)
      {
         VS[i1][i2].clear();
         IS[i1][i2].clear();
      }
   }

   for(int i = 0; i < 2; i++)
   {
      VB[i].clear();
      IB[i].clear();
   }

   E.clear();
   S.clear();

   SignalStateCount[0] = 0;
   SignalStateCount[1] = 0;
   SignalStateCount[2] = 0;
   SignalStateCount[3] = 0;

   BackgroundStateCount[0] = 0;
   BackgroundStateCount[1] = 0;
   BackgroundStateCount[2] = 0;
   BackgroundStateCount[3] = 0;

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit(FitConfiguration configuration)
{
   FitID = FitID + 1;

   NoSquareMode = configuration.NoSquareMode;
   Basis = configuration.Basis;
   UUbarDDbarRatio = configuration.UUbarDDbarRatio;
   while(UUbarDDbarRatio.size() < 4)
      UUbarDDbarRatio.push_back(2);
   Verbose = configuration.Verbose;

   if(Basis == BASIS_AVV && configuration.FloatParameter6 == false)   // don't float A4ZA
      AVVEFTMode = true;
   else
      AVVEFTMode = false;

   for(int i = 0; i < 20; i++)
      UsePriors[i] = configuration.UsePriors[i];
 
   // cout << UsePriors[0] << " " << UsePriors[1] << " " << UsePriors[2] << " " << UsePriors[3] << endl;

   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(-2);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   // Worker->SetTolerance(1e-10);
   Worker->SetStrategy(1);   // 0 = speed, 2 = robustness, 1 is in the middle

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 12);
   Worker->SetFunction(Function);

   double StepSize[12] = {0};
   StepSize[0] = (configuration.FloatParameter1 == true) ? 0.1 : 0;
   StepSize[1] = (configuration.FloatParameter2 == true) ? 0.1 : 0;
   StepSize[2] = (configuration.FloatParameter3 == true) ? 0.1 : 0;
   StepSize[3] = (configuration.FloatParameter4 == true) ? 0.1 : 0;
   StepSize[4] = (configuration.FloatParameter5 == true) ? 0.1 : 0;
   StepSize[5] = (configuration.FloatParameter6 == true) ? 0.1 : 0;
   StepSize[6] = (configuration.FloatParameter7 == true) ? 0.1 : 0;
   StepSize[7] = (configuration.FloatParameter8 == true) ? 0.1 : 0;
   StepSize[8] = (configuration.FloatFem == true) ? 0.1 : 0;
   StepSize[9] = (configuration.FloatFme == true) ? 0.1 : 0;
   StepSize[10] = (configuration.FloatFee == true) ? 0.1 : 0;
   StepSize[11] = (configuration.FloatFmm == true) ? 0.1 : 0;

   string AVVNames[8] = {"A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"};
   string HiggsNames[8] = {"DeltaCZ", "CZB", "CZZ", "CZZD", "CZA", "CZAD", "CAA", "CAAD"};
   string WarsawNames[8] = {"CT", "CH", "CWW", "CWWD", "CWB", "CWBD", "CBB", "CBBD"};
   string LoopNames[8] = {"A2ZZ", "A3ZZ", "A4ZZ", "YT", "YTA", "MT", "GWW", "MWW"};

   string *Names = NULL;
   if(Basis == BASIS_AVV)      Names = AVVNames;
   if(Basis == BASIS_HIGGS)    Names = HiggsNames;
   if(Basis == BASIS_WARSAW)   Names = WarsawNames;
   if(Basis == BASIS_LOOP)     Names = LoopNames;
   if(Names == NULL)
   {
      cerr << "ERROR!  BASIS = " << Basis << " WHICH DOES NOT EXIST!  RETURNING NONSENSE!!" << endl;
      return FitResultSummary();
   }

   Worker->SetLimitedVariable(0,  Names[0], configuration.Parameter1InitialValue, StepSize[0],  -1000, 1000);
   Worker->SetLimitedVariable(1,  Names[1], configuration.Parameter2InitialValue, StepSize[1],  -1000, 1000);
   Worker->SetLimitedVariable(2,  Names[2], configuration.Parameter3InitialValue, StepSize[2],  -1000, 1000);
   Worker->SetLimitedVariable(3,  Names[3], configuration.Parameter4InitialValue, StepSize[3],  -1000, 1000);
   Worker->SetLimitedVariable(4,  Names[4], configuration.Parameter5InitialValue, StepSize[4],  -1000, 1000);
   Worker->SetLimitedVariable(5,  Names[5], configuration.Parameter6InitialValue, StepSize[5],  -1000, 1000);
   Worker->SetLimitedVariable(6,  Names[6], configuration.Parameter7InitialValue, StepSize[6],  -1000, 1000);
   Worker->SetLimitedVariable(7,  Names[7], configuration.Parameter8InitialValue, StepSize[7],  -1000, 1000);
   Worker->SetLimitedVariable(8,  "Fem",    configuration.FemInitialValue,        StepSize[8],  0,     1);
   Worker->SetLimitedVariable(9,  "Fme",    configuration.FmeInitialValue,        StepSize[9],  0,     1);
   Worker->SetLimitedVariable(10, "Fee",    configuration.FeeInitialValue,        StepSize[10], 0,     1);
   Worker->SetLimitedVariable(11, "Fmm",    configuration.FmmInitialValue,        StepSize[11], 0,     1);

   for(int i = 0; i < 1; i++)
      Worker->Minimize();

   double EventCount[4] = {0};
   EventCount[0] = SignalStateCount[0] + BackgroundStateCount[0];
   EventCount[1] = SignalStateCount[1] + BackgroundStateCount[1];
   EventCount[2] = SignalStateCount[2] + BackgroundStateCount[2];
   EventCount[3] = SignalStateCount[3] + BackgroundStateCount[3];

   double TrueParameters[12] = {0};
   TrueParameters[0] = configuration.Parameter1InitialValue;
   TrueParameters[1] = configuration.Parameter2InitialValue;
   TrueParameters[2] = configuration.Parameter3InitialValue;
   TrueParameters[3] = configuration.Parameter4InitialValue;
   TrueParameters[4] = configuration.Parameter5InitialValue;
   TrueParameters[5] = configuration.Parameter6InitialValue;
   TrueParameters[6] = configuration.Parameter7InitialValue;
   TrueParameters[7] = configuration.Parameter8InitialValue;
   TrueParameters[8] = ((EventCount[0] > 0) ? (BackgroundStateCount[0] / EventCount[0]) : 0);
   TrueParameters[9] = ((EventCount[1] > 0) ? (BackgroundStateCount[1] / EventCount[1]) : 0);
   TrueParameters[10] = ((EventCount[2] > 0) ? (BackgroundStateCount[2] / EventCount[2]) : 0);
   TrueParameters[11] = ((EventCount[3] > 0) ? (BackgroundStateCount[3] / EventCount[3]) : 0);

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.Parameter1 = Parameters[0];   Result.Parameter1Error = Errors[0];
   Result.Parameter2 = Parameters[1];   Result.Parameter2Error = Errors[1];
   Result.Parameter3 = Parameters[2];   Result.Parameter3Error = Errors[2];
   Result.Parameter4 = Parameters[3];   Result.Parameter4Error = Errors[3];
   Result.Parameter5 = Parameters[4];   Result.Parameter5Error = Errors[4];
   Result.Parameter6 = Parameters[5];   Result.Parameter6Error = Errors[5];
   Result.Parameter7 = Parameters[6];   Result.Parameter7Error = Errors[6];
   Result.Parameter8 = Parameters[7];   Result.Parameter8Error = Errors[7];
   Result.Fem = Parameters[8];          Result.FemError = Errors[8];
   Result.Fme = Parameters[9];          Result.FmeError = Errors[9];
   Result.Fee = Parameters[10];         Result.FeeError = Errors[10];
   Result.Fmm = Parameters[11];         Result.FmmError = Errors[11];

   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   Result.Sem = SignalStateCount[0];
   Result.Sme = SignalStateCount[1];
   Result.See = SignalStateCount[2];
   Result.Smm = SignalStateCount[3];

   Result.Bem = BackgroundStateCount[0];
   Result.Bme = BackgroundStateCount[1];
   Result.Bee = BackgroundStateCount[2];
   Result.Bmm = BackgroundStateCount[3];

   Verbose = false;
   Result.TruthNLL = CalculateLogLikelihoodAll(TrueParameters);
   Result.BestNLL = CalculateLogLikelihoodAll(Parameters);
   Result.NoSquareMode = NoSquareMode;
   Result.Basis = Basis;
   Result.UUbarDDbarRatio = UUbarDDbarRatio;

   for(int i = 0; i < 20; i++)
      Result.UsedPriors[i] = UsePriors[i];

   delete Worker;

   return Result;
}

void FitClass::PlotResult(PsFileHelper *PsFile, FitResultSummary Result)
{
}

vector<double> ListToVector(int N, double x1, double x2, double x3, double x4,
   double x5, double x6, double x7, double x8, double x9, double x10,
   double x11, double x12, double x13, double x14, double x15, double x16)
{
   vector<double> Result(N);

   if(N > 0)    Result[0] = x1;
   if(N > 1)    Result[1] = x2;
   if(N > 2)    Result[2] = x3;
   if(N > 3)    Result[3] = x4;
   if(N > 4)    Result[4] = x5;
   if(N > 5)    Result[5] = x6;
   if(N > 6)    Result[6] = x7;
   if(N > 7)    Result[7] = x8;
   if(N > 8)    Result[8] = x9;
   if(N > 9)    Result[9] = x10;
   if(N > 10)   Result[10] = x11;
   if(N > 11)   Result[11] = x12;
   if(N > 12)   Result[12] = x13;
   if(N > 13)   Result[13] = x14;
   if(N > 14)   Result[14] = x15;
   if(N > 15)   Result[15] = x16;

   return Result;
}




