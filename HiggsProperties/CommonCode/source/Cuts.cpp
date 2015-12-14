//---------------------------------------------------------------------------
#include <algorithm>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
#include "AngleConversion.h"
#include "Cuts.h"
//---------------------------------------------------------------------------
bool PassCMSBaselineCut(LeptonVectors &Leptons, int L1ID, int L3ID)
{
   if(L1ID < 0)   L1ID = -L1ID;
   if(L3ID < 0)   L3ID = -L3ID;

   if(L1ID == 11 && L3ID == 11)   return PassCMSBaselineCutEE(Leptons);
   if(L1ID == 11 && L3ID == 13)   return PassCMSBaselineCutEM(Leptons);
   if(L1ID == 13 && L3ID == 11)   return PassCMSBaselineCutME(Leptons);
   if(L1ID == 13 && L3ID == 13)   return PassCMSBaselineCutMM(Leptons);

   return false;
}
//---------------------------------------------------------------------------
bool PassCMSBaselineCutEM(LeptonVectors &Leptons)
{
   double MH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   // if(MH < 115 || MH > 135)
   //    return false;

   if(fabs(Leptons.Lepton11.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(Leptons.Lepton11.GetPT() < 7)   return false;
   if(Leptons.Lepton12.GetPT() < 7)   return false;
   if(Leptons.Lepton21.GetPT() < 5)   return false;
   if(Leptons.Lepton22.GetPT() < 5)   return false;

   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(max(M1, M2) < 40)    return false;
   if(min(M1, M2) < 12)    return false;

   double LPTs[4];
   LPTs[0] = Leptons.Lepton11.GetPT();
   LPTs[1] = Leptons.Lepton12.GetPT();
   LPTs[2] = Leptons.Lepton21.GetPT();
   LPTs[3] = Leptons.Lepton22.GetPT();
   sort(LPTs + 0, LPTs + 4);
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassCMSBaselineCutME(LeptonVectors &Leptons)
{
   double MH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   // if(MH < 115 || MH > 135)
   //    return false;

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.5)   return false;

   if(Leptons.Lepton11.GetPT() < 5)   return false;
   if(Leptons.Lepton12.GetPT() < 5)   return false;
   if(Leptons.Lepton21.GetPT() < 7)   return false;
   if(Leptons.Lepton22.GetPT() < 7)   return false;

   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(max(M1, M2) < 40)    return false;
   if(min(M1, M2) < 12)    return false;

   double LPTs[4];
   LPTs[0] = Leptons.Lepton11.GetPT();
   LPTs[1] = Leptons.Lepton12.GetPT();
   LPTs[2] = Leptons.Lepton21.GetPT();
   LPTs[3] = Leptons.Lepton22.GetPT();
   sort(LPTs + 0, LPTs + 4);
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassCMSBaselineCutEE(LeptonVectors &Leptons)
{
   double MH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   // if(MH < 115 || MH > 135)
   //    return false;

   if(fabs(Leptons.Lepton11.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.5)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.5)   return false;

   if(Leptons.Lepton11.GetPT() < 7)   return false;
   if(Leptons.Lepton12.GetPT() < 7)   return false;
   if(Leptons.Lepton21.GetPT() < 7)   return false;
   if(Leptons.Lepton22.GetPT() < 7)   return false;

   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(max(M1, M2) < 40)    return false;
   if(min(M1, M2) < 12)    return false;

   double LPTs[4];
   LPTs[0] = Leptons.Lepton11.GetPT();
   LPTs[1] = Leptons.Lepton12.GetPT();
   LPTs[2] = Leptons.Lepton21.GetPT();
   LPTs[3] = Leptons.Lepton22.GetPT();
   sort(LPTs + 0, LPTs + 4);
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;

   // if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   // if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   // if((Leptons.Lepton21 + Leptons.Lepton12).GetMass() < 4)   return false;
   // if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassCMSBaselineCutMM(LeptonVectors &Leptons)
{
   double MH = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   // if(MH < 115 || MH > 135)
   //    return false;

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(Leptons.Lepton11.GetPT() < 5)   return false;
   if(Leptons.Lepton12.GetPT() < 5)   return false;
   if(Leptons.Lepton21.GetPT() < 5)   return false;
   if(Leptons.Lepton22.GetPT() < 5)   return false;

   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(max(M1, M2) < 40)    return false;
   if(min(M1, M2) < 12)    return false;

   double LPTs[4];
   LPTs[0] = Leptons.Lepton11.GetPT();
   LPTs[1] = Leptons.Lepton12.GetPT();
   LPTs[2] = Leptons.Lepton21.GetPT();
   LPTs[3] = Leptons.Lepton22.GetPT();
   sort(LPTs + 0, LPTs + 4);
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;

   // if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   // if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   // if((Leptons.Lepton21 + Leptons.Lepton12).GetMass() < 4)   return false;
   // if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingLeptonLoose(LeptonVectors &Leptons)
{
   if(Leptons.Lepton11.GetPT() < 2)   return false;
   if(Leptons.Lepton12.GetPT() < 2)   return false;
   if(Leptons.Lepton21.GetPT() < 2)   return false;
   if(Leptons.Lepton22.GetPT() < 2)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingLeptonTight(LeptonVectors &Leptons)
{
   double PTs[4] = {0};
   PTs[0] = Leptons.Lepton11.GetPT();
   PTs[1] = Leptons.Lepton12.GetPT();
   PTs[2] = Leptons.Lepton21.GetPT();
   PTs[3] = Leptons.Lepton22.GetPT();
   sort(PTs, PTs + 4);
   if(PTs[0] < 5)    return false;
   if(PTs[1] < 5)    return false;
   if(PTs[2] < 10)   return false;
   if(PTs[3] < 20)   return false;

   if(Leptons.Lepton11.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton12.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton21.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton22.GetAbsEta() > 2.4)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingLeptonTighter(LeptonVectors &Leptons)
{
   double PTs[4] = {0};
   PTs[0] = Leptons.Lepton11.GetPT();
   PTs[1] = Leptons.Lepton12.GetPT();
   PTs[2] = Leptons.Lepton21.GetPT();
   PTs[3] = Leptons.Lepton22.GetPT();
   sort(PTs, PTs + 4);
   if(PTs[0] < 7)    return false;
   if(PTs[1] < 7)    return false;
   if(PTs[2] < 10)   return false;
   if(PTs[3] < 20)   return false;

   if(Leptons.Lepton11.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton12.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton21.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton22.GetAbsEta() > 2.4)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingLeptonSmallEta(LeptonVectors &Leptons)
{
   if(Leptons.Lepton11.GetAbsEta() > 2.0)   return false;
   if(Leptons.Lepton12.GetAbsEta() > 2.0)   return false;
   if(Leptons.Lepton21.GetAbsEta() > 2.0)   return false;
   if(Leptons.Lepton22.GetAbsEta() > 2.0)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingTightA(LeptonVectors &Leptons)
{
   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(max(M1, M2) < 40)   return false;
   if(min(M1, M2) < 12)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingTightB(LeptonVectors &Leptons)
{
   double M1 = (Leptons.Lepton11 + Leptons.Lepton22).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton12).GetMass();

   if(max(M1, M2) < 40)   return false;
   if(min(M1, M2) < 12)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingTightC(LeptonVectors &Leptons)
{
   double M1 = (Leptons.Lepton11 + Leptons.Lepton21).GetMass();
   double M2 = (Leptons.Lepton12 + Leptons.Lepton22).GetMass();

   if(max(M1, M2) < 40)   return false;
   if(min(M1, M2) < 12)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingBase(LeptonVectors &Leptons)
{
   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingUpsilon(LeptonVectors &Leptons)
{
   double M12 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M14 = (Leptons.Lepton11 + Leptons.Lepton22).GetMass();
   double M32 = (Leptons.Lepton21 + Leptons.Lepton12).GetMass();
   double M34 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(M12 > 8.8 && M12 < 10.8)   return false;
   if(M14 > 8.8 && M14 < 10.8)   return false;
   if(M32 > 8.8 && M32 < 10.8)   return false;
   if(M34 > 8.8 && M34 < 10.8)   return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingLooseA(LeptonVectors &Leptons)
{
   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(max(M1, M2) < 40)   return false;
   if(min(M1, M2) < 4)    return false;

   return true;
}
//---------------------------------------------------------------------------
bool PassPairingSuperBaseA(LeptonVectors &Leptons)
{
   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(M1 < 0.1)   return false;
   if(M2 < 0.1)   return false;
   
   return true;
}
//---------------------------------------------------------------------------
bool PassPairingSuperBaseB(LeptonVectors &Leptons)
{
   double M1 = (Leptons.Lepton11 + Leptons.Lepton22).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton12).GetMass();

   if(M1 < 0.1)   return false;
   if(M2 < 0.1)   return false;
   
   return true;
}
//---------------------------------------------------------------------------
vector<bool> PassPairingCuts(LeptonVectors &Leptons)
{
   bool LeptonLoose = PassPairingLeptonLoose(Leptons);
   bool LeptonTight = PassPairingLeptonTight(Leptons);
   bool LeptonTighter = PassPairingLeptonTighter(Leptons);
   bool TightA = PassPairingTightA(Leptons);
   bool TightB = PassPairingTightB(Leptons);
   bool TightC = PassPairingTightC(Leptons);
   bool Base = PassPairingBase(Leptons);
   bool Upsilon = PassPairingUpsilon(Leptons);
   bool LooseA = PassPairingLooseA(Leptons);
   bool SmallEta = PassPairingLeptonSmallEta(Leptons);
   bool SuperBaseA = PassPairingSuperBaseA(Leptons);
   bool SuperBaseB = PassPairingSuperBaseB(Leptons);

   vector<bool> Result;
   Result.push_back(LeptonTight && TightA && Base);
   Result.push_back(LeptonTight && TightB && Base);
   Result.push_back(LeptonTight && TightC && Base);
   Result.push_back(LeptonTight && (TightA || TightB || TightC) && Base);
   Result.push_back(LeptonTight && (TightA || TightB || TightC) && Base && Upsilon);
   Result.push_back(LeptonLoose && Base);
   Result.push_back(LeptonTight && LooseA && Base);
   Result.push_back(LeptonTight && Base);
   Result.push_back(LeptonTighter && TightA && Base);
   Result.push_back(LeptonTight && Base && Upsilon);
   Result.push_back(LeptonTight && Base && Upsilon && SmallEta);
   Result.push_back(SuperBaseA);
   Result.push_back(SuperBaseA && SuperBaseB);
   return Result;
}
//---------------------------------------------------------------------------















