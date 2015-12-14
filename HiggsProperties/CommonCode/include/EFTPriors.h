#ifndef PRIORS_H_14117_KSJADKGJASDKJGASDKJG
#define PRIORS_H_14117_KSJADKGJASDKJGASDKJG

#include "EFTBases.h"

double GetRAA_AVV(const AVVBasis &A);
double GetRZA_AVV(const AVVBasis &A);
double GetRHto4l_NoSquare_AVV(const AVVBasis &A);
double GetRHto4l_NoSquare_Higgs(const HiggsBasis &H);
double GetRHto4l_NoSquare_Warsaw(const WarsawBasis &W);
double GetRHto4l_WithSquare_AVV(const AVVBasis &A);
double GetRHto4l_WithSquare_Higgs(const HiggsBasis &H);
double GetRHto4l_WithSquare_Warsaw(const WarsawBasis &W);
double GetRZZWW_NoSquare_AVV(const AVVBasis &A);
double GetRZZWW_NoSquare_Higgs(const HiggsBasis &H);
double GetRZZWW_NoSquare_Warsaw(const WarsawBasis &W);
double GetChi2_AllHiggs_WithSquare_AVV(const AVVBasis &A);
double GetChi2_AllHiggs_WithSquare_Higgs(const HiggsBasis &H);
double GetChi2_AllHiggs_WithSquare_Warsaw(const WarsawBasis &W);
double GetChi2_AllHiggs_Higgs_14252(const HiggsBasis &H);
double GetChi2_AllHiggs_Warsaw_14252(const WarsawBasis &W);
double GetChi2_LEP2WW_Higgs_14252(const HiggsBasis &H);
double GetChi2_LEP2WW_Warsaw_14252(const WarsawBasis &W);
double GetChi2_HiggsPlusLEP2WW_Higgs_14252(const HiggsBasis &H);
double GetChi2_HiggsPlusLEP2WW_Warsaw_14252(const WarsawBasis &W);

#endif
