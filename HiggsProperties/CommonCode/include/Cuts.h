//---------------------------------------------------------------------------
#ifndef CUTS_H_12665_KASDJGKAJNSDKGHADSKGHASDKGHASDKG
#define CUTS_H_12665_KASDJGKAJNSDKGHADSKGHASDKGHASDKG
//---------------------------------------------------------------------------
#include "AngleConversion.h"
//---------------------------------------------------------------------------
bool PassCMSBaselineCut(LeptonVectors &Leptons, int L1ID, int L3ID);
bool PassCMSBaselineCutEM(LeptonVectors &Leptons);
bool PassCMSBaselineCutME(LeptonVectors &Leptons);
bool PassCMSBaselineCutEE(LeptonVectors &Leptons);
bool PassCMSBaselineCutMM(LeptonVectors &Leptons);
//---------------------------------------------------------------------------
// bool PassPaperBaselineCutVeryLoose(LeptonVectors &Leptons, int L1ID, int L3ID);
// bool PassPaperBaselineCutVeryLooseEM(LeptonVectors &Leptons);
// bool PassPaperBaselineCutVeryLooseME(LeptonVectors &Leptons);
// bool PassPaperBaselineCutVeryLooseEE(LeptonVectors &Leptons);
// bool PassPaperBaselineCutVeryLooseMM(LeptonVectors &Leptons);
// bool PassPaperBaselineCutLoose(LeptonVectors &Leptons, int L1ID, int L3ID);
// bool PassPaperBaselineCutLooseEM(LeptonVectors &Leptons);
// bool PassPaperBaselineCutLooseME(LeptonVectors &Leptons);
// bool PassPaperBaselineCutLooseEE(LeptonVectors &Leptons);
// bool PassPaperBaselineCutLooseMM(LeptonVectors &Leptons);
// bool PassPaperBaselineCutTight(LeptonVectors &Leptons, int L1ID, int L3ID);
// bool PassPaperBaselineCutTightEM(LeptonVectors &Leptons);
// bool PassPaperBaselineCutTightME(LeptonVectors &Leptons);
// bool PassPaperBaselineCutTightEE(LeptonVectors &Leptons);
// bool PassPaperBaselineCutTightMM(LeptonVectors &Leptons);
//---------------------------------------------------------------------------
bool PassPairingLeptonLoose(LeptonVectors &Leptons);
bool PassPairingLeptonTight(LeptonVectors &Leptons);
bool PassPairingLeptonTighter(LeptonVectors &Leptons);
bool PassPairingLeptonSmallEta(LeptonVectors &Leptons);
bool PassPairingTightA(LeptonVectors &Leptons);
bool PassPairingTightB(LeptonVectors &Leptons);
bool PassPairingTightC(LeptonVectors &Leptons);
bool PassPairingBase(LeptonVectors &Leptons);
bool PassPairingUpsilon(LeptonVectors &Leptons);
bool PassPairingLooseA(LeptonVectors &Leptons);
bool PassPairingSuperBaseA(LeptonVectors &Leptons);
bool PassPairingSuperBaseB(LeptonVectors &Leptons);
bool PassPairingLowerBase(LeptonVectors &Leptons);
bool PassPairingEvenLowerBase(LeptonVectors &Leptons);
bool PassPairingDRLL(LeptonVectors &Leptons);
bool PassPairingVeryLowBase(LeptonVectors &Leptons);
bool PassPairingDRLLTight(LeptonVectors &Leptons);
vector<bool> PassPairingCuts(LeptonVectors &Leptons);
//---------------------------------------------------------------------------
#endif
