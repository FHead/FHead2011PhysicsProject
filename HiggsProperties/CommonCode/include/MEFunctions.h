//---------------------------------------------------------------------------
#include "AngleConversion.h"
#include "CalculateME.h"
//---------------------------------------------------------------------------
double CalculateA1RA1RSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2RA2RSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2IA2ISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3RA3RSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3IA3ISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1RA2RSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1RA2ISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1RA3RSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1RA3ISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2RA2ISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2RA3RSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2RA3ISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2IA3RSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2IA3ISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3RA3ISignal2e2mu(LeptonVectors &Leptons);
double CalculateBackground2e2muNoM4lCorrection(LeptonVectors &Leptons);
double CalculateBackground2e2mu_Roberto12253(LeptonVectors &Leptons);
double CalculateBackground2e2mu(LeptonVectors &Leptons);
double CalculateDDbarBackground2e2mu(LeptonVectors &Leptons);
double CalculateUUbarBackground2e2muDirectional(LeptonVectors &Leptons);
double CalculateUbarUBackground2e2muDirectional(LeptonVectors &Leptons);
double CalculateDDbarBackground2e2muDirectional(LeptonVectors &Leptons);
double CalculateDbarDBackground2e2muDirectional(LeptonVectors &Leptons);
double CalculateUUbarBackground2e2muDirectionalFlatS(LeptonVectors &Leptons);
double CalculateUbarUBackground2e2muDirectionalFlatS(LeptonVectors &Leptons);
double CalculateDDbarBackground2e2muDirectionalFlatS(LeptonVectors &Leptons);
double CalculateDbarDBackground2e2muDirectionalFlatS(LeptonVectors &Leptons);
double CalculateA1RA1RSignal4e(LeptonVectors &Leptons);
double CalculateA2RA2RSignal4e(LeptonVectors &Leptons);
double CalculateA2IA2ISignal4e(LeptonVectors &Leptons);
double CalculateA3RA3RSignal4e(LeptonVectors &Leptons);
double CalculateA3IA3ISignal4e(LeptonVectors &Leptons);
double CalculateA1RA2RSignal4e(LeptonVectors &Leptons);
double CalculateA1RA2ISignal4e(LeptonVectors &Leptons);
double CalculateA1RA3RSignal4e(LeptonVectors &Leptons);
double CalculateA1RA3ISignal4e(LeptonVectors &Leptons);
double CalculateA2RA2ISignal4e(LeptonVectors &Leptons);
double CalculateA2RA3RSignal4e(LeptonVectors &Leptons);
double CalculateA2RA3ISignal4e(LeptonVectors &Leptons);
double CalculateA2IA3RSignal4e(LeptonVectors &Leptons);
double CalculateA2IA3ISignal4e(LeptonVectors &Leptons);
double CalculateA3RA3ISignal4e(LeptonVectors &Leptons);
double CalculateBackground4eNoM4lCorrection(LeptonVectors &Leptons);
double CalculateBackground4e_Roberto12253(LeptonVectors &Leptons);
double CalculateBackground4e(LeptonVectors &Leptons);
double CalculateDDbarBackground4e(LeptonVectors &Leptons);
double CalculateUUbarBackground4eDirectional(LeptonVectors &Leptons);
double CalculateUbarUBackground4eDirectional(LeptonVectors &Leptons);
double CalculateDDbarBackground4eDirectional(LeptonVectors &Leptons);
double CalculateDbarDBackground4eDirectional(LeptonVectors &Leptons);
double CalculateUUbarBackground4eDirectionalFlatS(LeptonVectors &Leptons);
double CalculateUbarUBackground4eDirectionalFlatS(LeptonVectors &Leptons);
double CalculateDDbarBackground4eDirectionalFlatS(LeptonVectors &Leptons);
double CalculateDbarDBackground4eDirectionalFlatS(LeptonVectors &Leptons);
double CalculateFlatBackground(LeptonVectors &Leptons);
double CalculateTofuME(LeptonVectors &Leptons);
double CalculateProductionTofu(LeptonVectors &Leptons);
double CalculateTofuME_13443(LeptonVectors &Leptons);
//---------------------------------------------------------------------------
double CalculateA1ZZRA1ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA2ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA2ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZIA3ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZARA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZAIA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZARA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZAIA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2AARA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2AAIA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3AARA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3AAIA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA2ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA2ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA3ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA2ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA3ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZRA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA3ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA3ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZZIA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA3ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZRA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZIA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZIA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZIA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZIA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZIA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZIA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZIA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZZIA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZARA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZARA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZARA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZARA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZARA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZARA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZARA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZAIA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZAIA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZAIA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZAIA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZAIA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2ZAIA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZARA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZARA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZARA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZARA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZARA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZAIA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZAIA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZAIA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA3ZAIA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2AARA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2AARA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2AARA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA2AAIA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA2AAIA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA3AARA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA1L1ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA1L1ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA1LQZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA1LQZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA1L1ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA1LQZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA1LQZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA1LQZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA1LQZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA1LQZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA1L1ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA1L1ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA1LQZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1ZZRA1LQZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA2ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA2ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA3ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA3ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZRA3AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA2ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA2ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA3ZZRSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA3ZZISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA2ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA2ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA3ZARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA3ZAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA2AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA2AAISignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA3AARSignal2e2mu(LeptonVectors &Leptons);
double CalculateA1LQZZIA3AAISignal2e2mu(LeptonVectors &Leptons);
//---------------------------------------------------------------------------
double CalculateA1ZZRA1ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA2ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA2ZZISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA3ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA3ZZIA3ZZISignal4e(LeptonVectors &Leptons);
double CalculateA2ZARA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZAIA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZARA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZAIA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA2AARA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA2AAIA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA3AARA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA3AAIA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA2ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA2ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA3ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA3ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA2ZZISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA3ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA3ZZISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZRA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA3ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA3ZZISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZZIA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA3ZZISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZZRA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZIA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZZIA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZIA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZZIA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZIA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZZIA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZZIA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZZIA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZARA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZARA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZARA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZARA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZARA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZARA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZARA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZAIA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZAIA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZAIA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZAIA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA2ZAIA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA2ZAIA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZARA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZARA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZARA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZARA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZARA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZAIA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZAIA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA3ZAIA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA3ZAIA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA2AARA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA2AARA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA2AARA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA2AAIA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA2AAIA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA3AARA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA1L1ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA1L1ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA1LQZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA1LQZZISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA1L1ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA1LQZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA1LQZZISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA1LQZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA1LQZZISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA1LQZZISignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA1L1ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA1L1ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA1LQZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1ZZRA1LQZZISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZRA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA1L1ZZIA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA2ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA2ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA3ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA3ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZRA3AAISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA2ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA2ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA3ZZRSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA3ZZISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA2ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA2ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA3ZARSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA3ZAISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA2AARSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA2AAISignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA3AARSignal4e(LeptonVectors &Leptons);
double CalculateA1LQZZIA3AAISignal4e(LeptonVectors &Leptons);
//---------------------------------------------------------------------------



