//----------------------------------------------------------------------------
#include "AngleConversion.h"
#include "CalculateME.h"
#include "Constants.h"
//----------------------------------------------------------------------------
#include "MEFunctions.h"
//----------------------------------------------------------------------------
double CalculateA1RA1RSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_ahR_ahR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2RA2RSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZR_aZR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2IA2ISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_aZI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3RA3RSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdR_aZdR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3IA3ISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdI_aZdI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA1RA2RSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1RA2ISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1RA3RSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1RA3ISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2RA2ISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2RA3RSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2RA3ISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2IA3RSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2IA3ISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3RA3ISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateBackground2e2muNoM4lCorrection(LeptonVectors &Leptons)
{
   return (GetZZZAAABackground(Leptons, false, true) + GetZZZAAABackground(Leptons, true, true)
      + GetZZZAAABackground(Leptons, false, false) + GetZZZAAABackground(Leptons, true, false));
}
//----------------------------------------------------------------------------
double CalculateBackground2e2mu_Roberto12253(LeptonVectors &Leptons)
{
   double M4l = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   // this is for pdfs:
   // a -> 0.117222, b -> -5.84853, c -> 0.798958
   //
   // this is for the integral of my expressions:
   // a -> 0.00187086, b -> -8.31003, c -> 1.46776

   double MA = 0.117222;
   double MB = -5.84853;
   double MC = 0.798958;
   double EA = 0.00187086;
   double EB = -8.31003;
   double EC = 1.46776;

   double MadgraphFactor = MA * M4l * exp(MB / CONST_MZ * M4l)
      * exp((MC / CONST_MZ * M4l) * (MC / CONST_MZ * M4l));
   double ExpressionFactor = EA * M4l * exp(EB / CONST_MZ * M4l)
      * exp((EC / CONST_MZ * M4l) * (EC / CONST_MZ * M4l));

   return (GetZZZAAABackground(Leptons, false, true) + GetZZZAAABackground(Leptons, true, true)
      + GetZZZAAABackground(Leptons, false, false) + GetZZZAAABackground(Leptons, true, false))
      * MadgraphFactor / ExpressionFactor * M4l * M4l;
}
//----------------------------------------------------------------------------
double CalculateBackground2e2mu(LeptonVectors &Leptons)
{
   double M4l = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   return (GetZZZAAABackground(Leptons, false, true) + GetZZZAAABackground(Leptons, true, true)
      + GetZZZAAABackground(Leptons, false, false) + GetZZZAAABackground(Leptons, true, false)) * M4l;
}
//----------------------------------------------------------------------------
double CalculateDDbarBackground2e2mu(LeptonVectors &Leptons)
{
   return GetZZZAAABackground(Leptons, false, false) + GetZZZAAABackground(Leptons, true, false);
}
//----------------------------------------------------------------------------
double CalculateUUbarBackground2e2muDirectional(LeptonVectors &Leptons)
{
   return GetZZZAAABackground(Leptons, false, true);
}
//----------------------------------------------------------------------------
double CalculateUbarUBackground2e2muDirectional(LeptonVectors &Leptons)
{
   return GetZZZAAABackground(Leptons, true, true);
}
//----------------------------------------------------------------------------
double CalculateDDbarBackground2e2muDirectional(LeptonVectors &Leptons)
{
   return GetZZZAAABackground(Leptons, false, false);
}
//----------------------------------------------------------------------------
double CalculateDbarDBackground2e2muDirectional(LeptonVectors &Leptons)
{
   return GetZZZAAABackground(Leptons, true, false);
}
//----------------------------------------------------------------------------
double CalculateUUbarBackground2e2muDirectionalFlatS(LeptonVectors &Leptons)
{
   double M = Leptons.GetTotal().GetMass();
   // double BW = 9.21705 / (2.26509 * 2.26509 + (M - 91.1876) * (M - 91.1876));
   // double Weird = 2.19627 * (1 + tanh((M - 106.975) / 4.58807)) * exp(-(M - 106.975) / 67.0303)
   //    / (M - 69.5910);
   double BW = 9.63641 / (2.54 * 2.54 + (M - 91.1876) * (M - 91.1876));
   double Weird = 0.0734595 * (1 + tanh((M - 106.805) / 4.74764)) * exp(-(M - 106.805) / 45.0662);

   return GetZZZAAABackground(Leptons, false, true) / (BW + Weird) * (2 * M);
}
//----------------------------------------------------------------------------
double CalculateUbarUBackground2e2muDirectionalFlatS(LeptonVectors &Leptons)
{
   double M = Leptons.GetTotal().GetMass();
   // double BW = 9.21705 / (2.26509 * 2.26509 + (M - 91.1876) * (M - 91.1876));
   // double Weird = 2.19627 * (1 + tanh((M - 106.975) / 4.58807)) * exp(-(M - 106.975) / 67.0303)
   //    / (M - 69.5910);
   double BW = 9.63641 / (2.54 * 2.54 + (M - 91.1876) * (M - 91.1876));
   double Weird = 0.0734595 * (1 + tanh((M - 106.805) / 4.74764)) * exp(-(M - 106.805) / 45.0662);

   return GetZZZAAABackground(Leptons, true, true) / (BW + Weird) * (2 * M);
}
//----------------------------------------------------------------------------
double CalculateDDbarBackground2e2muDirectionalFlatS(LeptonVectors &Leptons)
{
   double M = Leptons.GetTotal().GetMass();
   // double BW = 7.68515 / (-0.415023 * 0.415023 + (M - 91.1876) * (M - 91.1876));
   // double Weird = 0.581785 * (1 + tanh((M - 106.975) / 4.58807)) * exp(-(M - 106.975) / 67.0303)
   //    / (M - 69.5910);
   double BW = 9.22681 / (2.54 * 2.54 + (M - 91.1876) * (M - 91.1876));
   double Weird = 0.0184946 * (1 + tanh((M - 107.179) / 3.41822)) * exp(-(M - 107.179) / 55.0957);

   return GetZZZAAABackground(Leptons, false, false) / (BW + Weird) * (2 * M);
}
//----------------------------------------------------------------------------
double CalculateDbarDBackground2e2muDirectionalFlatS(LeptonVectors &Leptons)
{
   double M = Leptons.GetTotal().GetMass();
   // double BW = 7.68515 / (-0.415023 * 0.415023 + (M - 91.1876) * (M - 91.1876));
   // double Weird = 0.581785 * (1 + tanh((M - 106.975) / 4.58807)) * exp(-(M - 106.975) / 67.0303)
   //    / (M - 69.5910);
   double BW = 9.22681 / (2.54 * 2.54 + (M - 91.1876) * (M - 91.1876));
   double Weird = 0.0184946 * (1 + tanh((M - 107.179) / 3.41822)) * exp(-(M - 107.179) / 55.0957);

   return GetZZZAAABackground(Leptons, true, false) / (BW + Weird) * (2 * M);
}
//----------------------------------------------------------------------------
double CalculateA1RA1RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_ahR_ahR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2RA2RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_aZR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2IA2ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3RA3RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdR_aZdR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3IA3ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdI_aZdI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA1RA2RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1RA2ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1RA3RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1RA3ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2RA2ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2RA3RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2RA3ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2IA3RSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2IA3ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3RA3ISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateBackground4eNoM4lCorrection(LeptonVectors &Leptons)
{
   return (GetZZZAAA4eBackground(Leptons, false, true) + GetZZZAAA4eBackground(Leptons, true, true)
      + GetZZZAAA4eBackground(Leptons, false, false) + GetZZZAAA4eBackground(Leptons, true, false));
}
//----------------------------------------------------------------------------
double CalculateBackground4e_Roberto12253(LeptonVectors &Leptons)
{
   double M4l = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   // this is for pdfs:
   // a -> 0.117222, b -> -5.84853, c -> 0.798958
   //
   // this is for the integral of my expressions:
   // a -> 0.00187086, b -> -8.31003, c -> 1.46776

   double MA = 0.117222;
   double MB = -5.84853;
   double MC = 0.798958;
   double EA = 0.00187086;
   double EB = -8.31003;
   double EC = 1.46776;

   double MadgraphFactor = MA * M4l * exp(MB / CONST_MZ * M4l)
      * exp((MC / CONST_MZ * M4l) * (MC / CONST_MZ * M4l));
   double ExpressionFactor = EA * M4l * exp(EB / CONST_MZ * M4l)
      * exp((EC / CONST_MZ * M4l) * (EC / CONST_MZ * M4l));

   return (GetZZZAAA4eBackground(Leptons, false, true) + GetZZZAAA4eBackground(Leptons, true, true)
      + GetZZZAAA4eBackground(Leptons, false, false) + GetZZZAAA4eBackground(Leptons, true, false))
      * MadgraphFactor / ExpressionFactor * M4l * M4l;
}
//----------------------------------------------------------------------------
double CalculateBackground4e(LeptonVectors &Leptons)
{
   double M4l = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   return (GetZZZAAA4eBackground(Leptons, false, true) + GetZZZAAA4eBackground(Leptons, true, true)
         + GetZZZAAA4eBackground(Leptons, false, false) + GetZZZAAA4eBackground(Leptons, true, false)) * M4l;
}
//----------------------------------------------------------------------------
double CalculateDDbarBackground4e(LeptonVectors &Leptons)
{
   return GetZZZAAA4eBackground(Leptons, false, false) + GetZZZAAA4eBackground(Leptons, true, false);
}
//----------------------------------------------------------------------------
double CalculateUUbarBackground4eDirectional(LeptonVectors &Leptons)
{
   return GetZZZAAA4eBackground(Leptons, false, true);
}
//----------------------------------------------------------------------------
double CalculateUbarUBackground4eDirectional(LeptonVectors &Leptons)
{
   return GetZZZAAA4eBackground(Leptons, true, true);
}
//----------------------------------------------------------------------------
double CalculateDDbarBackground4eDirectional(LeptonVectors &Leptons)
{
   return GetZZZAAA4eBackground(Leptons, false, false);
}
//----------------------------------------------------------------------------
double CalculateDbarDBackground4eDirectional(LeptonVectors &Leptons)
{
   return GetZZZAAA4eBackground(Leptons, true, false);
}
//----------------------------------------------------------------------------
double CalculateUUbarBackground4eDirectionalFlatS(LeptonVectors &Leptons)
{
   double M = Leptons.GetTotal().GetMass();
   // double BW = 14.9088 / (2.26509 * 2.26509 + (M - 91.1876) * (M - 91.1876));
   // double Weird = 3.62481 * (1 + tanh((M - 106.975) / 4.58807)) * exp(-(M - 106.975) / 38.0154)
   //    / (M - 69.5910);
   double BW = 15.1656 / (2.54 * 2.54 + (M - 91.1876) * (M - 91.1876));
   double Weird = 0.0966261 * (1 + tanh((M - 106.541) / 7.42674)) * exp(-(M - 106.541) / 37.2631);

   return GetZZZAAA4eBackground(Leptons, false, true) / (BW + Weird) * (2 * M);
}
//----------------------------------------------------------------------------
double CalculateUbarUBackground4eDirectionalFlatS(LeptonVectors &Leptons)
{
   double M = Leptons.GetTotal().GetMass();
   // double BW = 14.9088 / (2.26509 * 2.26509 + (M - 91.1876) * (M - 91.1876));
   // double Weird = 3.62481 * (1 + tanh((M - 106.975) / 4.58807)) * exp(-(M - 106.975) / 38.0154)
   //    / (M - 69.5910);
   double BW = 15.1656 / (2.54 * 2.54 + (M - 91.1876) * (M - 91.1876));
   double Weird = 0.0966261 * (1 + tanh((M - 106.541) / 7.42674)) * exp(-(M - 106.541) / 37.2631);

   return GetZZZAAA4eBackground(Leptons, true, true) / (BW + Weird) * (2 * M);
}
//----------------------------------------------------------------------------
double CalculateDDbarBackground4eDirectionalFlatS(LeptonVectors &Leptons)
{
   double M = Leptons.GetTotal().GetMass();
   // double BW = 11.2287 / (-0.415023 * 0.415023 + (M - 91.1876) * (M - 91.1876));
   // double Weird = 0.943527 * (1 + tanh((M - 106.975) / 4.58807)) * exp(-(M - 106.975) / 34.8334)
   //    / (M - 69.5910);
   double BW = 13.1729 / (2.54 * 2.54 + (M - 91.1876) * (M - 91.1876));
   double Weird = 0.0216815 * (1 + tanh((M - 108.703) / 4.74419)) * exp(-(M - 108.703) / 40.2929);

   return GetZZZAAA4eBackground(Leptons, false, false) / (BW + Weird) * (2 * M);
}
//----------------------------------------------------------------------------
double CalculateDbarDBackground4eDirectionalFlatS(LeptonVectors &Leptons)
{
   double M = Leptons.GetTotal().GetMass();
   // double BW = 11.2287 / (-0.415023 * 0.415023 + (M - 91.1876) * (M - 91.1876));
   // double Weird = 0.943527 * (1 + tanh((M - 106.975) / 4.58807)) * exp(-(M - 106.975) / 34.8334)
   //    / (M - 69.5910);
   double BW = 13.1729 / (2.54 * 2.54 + (M - 91.1876) * (M - 91.1876));
   double Weird = 0.0216815 * (1 + tanh((M - 108.703) / 4.74419)) * exp(-(M - 108.703) / 40.2929);

   return GetZZZAAA4eBackground(Leptons, true, false) / (BW + Weird) * (2 * M);
}
//----------------------------------------------------------------------------
double CalculateFlatBackground(LeptonVectors &Leptons)
{
   return 1;
}
//----------------------------------------------------------------------------
double CalculateTofuME(LeptonVectors &Leptons)
{
   EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

   if(Event.Phi0 > PI)   Event.Phi0 = Event.Phi0 - 2 * PI;
   if(Event.Phi > PI)    Event.Phi = Event.Phi - 2 * PI;

   if(Event.Phi0 < -1 || Event.Phi0 > 1)
      return 0;
   if(cos(Event.Theta0) < -0.5 || cos(Event.Theta0) > 0.5)
      return 0;
   if(Event.Phi < -1 || Event.Phi > 1)
      return 0;
   if(cos(Event.Theta1) < -0.5 || cos(Event.Theta1) > 0.5)
      return 0;
   if(cos(Event.Theta2) < -0.5 || cos(Event.Theta2) > 0.5)
      return 0;

   if(Event.HMass < 125 || Event.HMass > 130)
      return 0;
   if(Event.ZMass < 50 || Event.ZMass > 80)
      return 0;
   if(Event.Z2Mass < 20 || Event.Z2Mass > 50)
      return 0;

   return 1;
}
//----------------------------------------------------------------------------
double CalculateProductionTofu(LeptonVectors &Leptons)
{
   FourVector Total = Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22;

   double s = Total.GetMass2();
   double PT = Total.GetPT();
   double Y = Total.GetY();

   if(s < 100 * 100 || s > 140 * 140)
      return 0;
   if(PT > 100)
      return 0;
   if(Y < -4 || Y > 4)
      return 0;

   return 1;
}
//----------------------------------------------------------------------------
double CalculateTofuME_13443(LeptonVectors &Leptons)
{
   EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

   while(Event.Phi0 > 2 * PI)   Event.Phi0 = Event.Phi0 - 2 * PI;
   while(Event.Phi > 2 * PI)    Event.Phi = Event.Phi - 2 * PI;
   while(Event.Phi0 < 0)        Event.Phi0 = Event.Phi0 + 2 * PI;
   while(Event.Phi < 0)         Event.Phi = Event.Phi + 2 * PI;

   if(Event.Phi0 < 0.8 || Event.Phi0 > 5.2)
      return 0;
   if(cos(Event.Theta0) < -0.7 || cos(Event.Theta0) > 0.7)
      return 0;
   if(Event.Phi < 0.5 || Event.Phi > 5.5)
      return 0;
   if(cos(Event.Theta1) < -0.6 || cos(Event.Theta1) > 0.8)
      return 0;
   if(cos(Event.Theta2) < -0.6 || cos(Event.Theta2) > 0.8)
      return 0;

   if(Event.HMass < 120 || Event.HMass > 125)
      return 0;
   if(Event.ZMass < 50 || Event.ZMass > 80)
      return 0;
   if(Event.Z2Mass < 30 || Event.Z2Mass > 50)
      return 0;

   return 1;
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_ahR_ahR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZR_aZR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_aZI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdR_aZdR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdI_aZdI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAR_aZAR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAI_aZAI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdR_aZAdR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdI_aZAdI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AARA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aAR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AAIA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aAI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3AARA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_aAdR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3AAIA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aAdI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAR_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdR_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAR_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAI_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdR_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdI_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZdI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAI_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAR_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAR_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAI_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAI_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aZAI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aZAI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_aZAI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aZAI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aZAdI_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdR_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AARA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AARA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AARA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAR_aAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AAIA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AAIA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAI_aAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3AARA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   return GetGeneralScalar2e2mu_aAdI_aAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA1L1ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal2e2mu(Leptons) * (S1 + S2) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA1L1ZZISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal2e2mu(Leptons) * (S1 + S2) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA1LQZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal2e2mu(Leptons) * SH * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA1LQZZISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal2e2mu(Leptons) * SH * SH;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA1L1ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA1LQZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal2e2mu(Leptons) * (S1 + S2) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA1LQZZISignal2e2mu(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA1LQZZRSignal2e2mu(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA1LQZZISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal2e2mu(Leptons) * (S1 + S2) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA1LQZZISignal2e2mu(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1L1ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1L1ZZISignal2e2mu(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1LQZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1LQZZISignal2e2mu(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZRSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2ZZISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZRSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3ZZISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZARSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZAISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZARSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZAISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AARSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AAISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AARSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AAISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2ZZISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2ZZISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZRSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3ZZISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3ZZISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZRSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2ZAISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZARSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3ZAISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZARSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2AAISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AARSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3AAISignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AARSignal2e2mu(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZRSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2ZZISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZRSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3ZZISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZARSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZAISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZARSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZAISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AARSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AAISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AARSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AAISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2ZZISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2ZZISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZRSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3ZZRSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3ZZISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3ZZISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZRSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2ZARSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2ZAISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2ZAISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZARSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3ZARSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3ZAISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3ZAISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZARSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2AARSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2AAISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2AAISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AARSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3AARSignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3AAISignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3AAISignal2e2mu(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AARSignal2e2mu(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1ZZRSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_ahR_ahR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2ZZRSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_aZR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2ZZISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3ZZRSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdR_aZdR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3ZZISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdI_aZdI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAR_aZAR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA2ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAI_aZAI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdR_aZAdR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA3ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdI_aZAdI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AARA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aAR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AAIA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aAI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3AARA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_aAdR(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA3AAIA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aAdI(Leptons, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2ZZRSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2ZZISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3ZZRSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3ZZISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_ahR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2ZZISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3ZZRSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3ZZISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAR_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdR_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZRA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aZR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3ZZRSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3ZZISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAR_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAI_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdR_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdI_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZZIA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aZI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3ZZISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZdI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA2ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA2ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZRA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aZdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA2ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA2ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZZIA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aZdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAI_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAR_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAR_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aZAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA3ZARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAI_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA3ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAI_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aZAI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aZAI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_aZAI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2ZAIA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aZAI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3ZAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aZAdI_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aZAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA2AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdR_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aZAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AARA2AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aAR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AARA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AARA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAR_aAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AAIA3AARSignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA2AAIA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAI_aAdI(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA3AARA3AAISignal4e(LeptonVectors &Leptons)
{
   return GetGeneralScalar4e_aAdI_aAdR(Leptons, 1, 1);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA1L1ZZRSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal4e(Leptons) * (S1 + S2) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA1L1ZZISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal4e(Leptons) * (S1 + S2) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA1LQZZRSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal4e(Leptons) * SH * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA1LQZZISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal4e(Leptons) * SH * SH;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA1L1ZZISignal4e(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA1LQZZRSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal4e(Leptons) * (S1 + S2) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA1LQZZISignal4e(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA1LQZZRSignal4e(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA1LQZZISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal4e(Leptons) * (S1 + S2) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA1LQZZISignal4e(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1L1ZZRSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1L1ZZISignal4e(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1LQZZRSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA1ZZRSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1ZZRA1LQZZISignal4e(LeptonVectors &Leptons)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2ZZRSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZRSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2ZZISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3ZZRSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZRSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3ZZISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2ZARSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZARSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2ZAISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZAISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3ZARSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZARSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3ZAISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZAISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2AARSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AARSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA2AAISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AAISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3AARSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AARSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZRA3AAISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AAISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2ZZRSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2ZZISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2ZZISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZRSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3ZZRSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3ZZISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3ZZISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZRSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2ZARSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2ZAISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2ZAISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZARSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3ZARSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3ZAISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3ZAISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZARSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2AARSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2AAISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA2AAISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AARSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3AARSignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3AAISignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1L1ZZIA3AAISignal4e(LeptonVectors &Leptons)
{
   double S1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double S2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AARSignal4e(Leptons) * (S1 + S2);
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2ZZRSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZRSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2ZZISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3ZZRSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZRSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3ZZISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2ZARSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZARSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2ZAISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZAISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3ZARSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZARSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3ZAISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZAISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2AARSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AARSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA2AAISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AAISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3AARSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AARSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZRA3AAISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AAISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2ZZRSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2ZZISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2ZZISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZZRSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3ZZRSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3ZZISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3ZZISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZZRSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2ZARSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2ZAISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2ZAISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2ZARSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3ZARSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3ZAISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3ZAISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3ZARSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2AARSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA2AAISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA2AAISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA2AARSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3AARSignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return -CalculateA1ZZRA3AAISignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------
double CalculateA1LQZZIA3AAISignal4e(LeptonVectors &Leptons)
{
   double SH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass2();
   return CalculateA1ZZRA3AARSignal4e(Leptons) * SH;
}
//----------------------------------------------------------------------------









