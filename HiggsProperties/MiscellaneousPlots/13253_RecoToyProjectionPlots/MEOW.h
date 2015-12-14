//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 15 15:17:05 2014 by ROOT version 5.34/18
// from TTree ReducedTree/ReducedTree
// found on file: BackgroundAll8TeV.root
//////////////////////////////////////////////////////////

#ifndef MEOW_h
#define MEOW_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class MEOW {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        MH;
   Double_t        M1;
   Double_t        M2;
   Double_t        Phi0;
   Double_t        Theta0;
   Double_t        Phi;
   Double_t        Theta1;
   Double_t        Theta2;
   Double_t        HPhi;
   Double_t        HPT;
   Double_t        HY;
   Double_t        PhiOffset;
   Double_t        L1PT;
   Double_t        L1Eta;
   Double_t        L1Phi;
   Int_t           L1ID;
   Double_t        L2PT;
   Double_t        L2Eta;
   Double_t        L2Phi;
   Int_t           L2ID;
   Double_t        L3PT;
   Double_t        L3Eta;
   Double_t        L3Phi;
   Int_t           L3ID;
   Double_t        L4PT;
   Double_t        L4Eta;
   Double_t        L4Phi;
   Int_t           L4ID;
   Double_t        B2;
   Double_t        Weight;
   Bool_t          PassEM;
   Bool_t          PassME;
   Bool_t          PassEE;
   Bool_t          PassMM;
   Double_t        B1_A1ZZRA1ZZR;
   Double_t        B1_A2ZZRA2ZZR;
   Double_t        B1_A2ZZIA2ZZI;
   Double_t        B1_A3ZZRA3ZZR;
   Double_t        B1_A3ZZIA3ZZI;
   Double_t        B1_A2ZARA2ZAR;
   Double_t        B1_A2ZAIA2ZAI;
   Double_t        B1_A3ZARA3ZAR;
   Double_t        B1_A3ZAIA3ZAI;
   Double_t        B1_A2AARA2AAR;
   Double_t        B1_A2AAIA2AAI;
   Double_t        B1_A3AARA3AAR;
   Double_t        B1_A3AAIA3AAI;
   Double_t        B1_A1ZZRA2ZZR;
   Double_t        B1_A1ZZRA2ZZI;
   Double_t        B1_A1ZZRA3ZZR;
   Double_t        B1_A1ZZRA3ZZI;
   Double_t        B1_A1ZZRA2ZAR;
   Double_t        B1_A1ZZRA2ZAI;
   Double_t        B1_A1ZZRA3ZAR;
   Double_t        B1_A1ZZRA3ZAI;
   Double_t        B1_A1ZZRA2AAR;
   Double_t        B1_A1ZZRA2AAI;
   Double_t        B1_A1ZZRA3AAR;
   Double_t        B1_A1ZZRA3AAI;
   Double_t        B1_A2ZZRA2ZZI;
   Double_t        B1_A2ZZRA3ZZR;
   Double_t        B1_A2ZZRA3ZZI;
   Double_t        B1_A2ZZRA2ZAR;
   Double_t        B1_A2ZZRA2ZAI;
   Double_t        B1_A2ZZRA3ZAR;
   Double_t        B1_A2ZZRA3ZAI;
   Double_t        B1_A2ZZRA2AAR;
   Double_t        B1_A2ZZRA2AAI;
   Double_t        B1_A2ZZRA3AAR;
   Double_t        B1_A2ZZRA3AAI;
   Double_t        B1_A2ZZIA3ZZR;
   Double_t        B1_A2ZZIA3ZZI;
   Double_t        B1_A2ZZIA2ZAR;
   Double_t        B1_A2ZZIA2ZAI;
   Double_t        B1_A2ZZIA3ZAR;
   Double_t        B1_A2ZZIA3ZAI;
   Double_t        B1_A2ZZIA2AAR;
   Double_t        B1_A2ZZIA2AAI;
   Double_t        B1_A2ZZIA3AAR;
   Double_t        B1_A2ZZIA3AAI;
   Double_t        B1_A3ZZRA3ZZI;
   Double_t        B1_A3ZZRA2ZAR;
   Double_t        B1_A3ZZRA2ZAI;
   Double_t        B1_A3ZZRA3ZAR;
   Double_t        B1_A3ZZRA3ZAI;
   Double_t        B1_A3ZZRA2AAR;
   Double_t        B1_A3ZZRA2AAI;
   Double_t        B1_A3ZZRA3AAR;
   Double_t        B1_A3ZZRA3AAI;
   Double_t        B1_A3ZZIA2ZAR;
   Double_t        B1_A3ZZIA2ZAI;
   Double_t        B1_A3ZZIA3ZAR;
   Double_t        B1_A3ZZIA3ZAI;
   Double_t        B1_A3ZZIA2AAR;
   Double_t        B1_A3ZZIA2AAI;
   Double_t        B1_A3ZZIA3AAR;
   Double_t        B1_A3ZZIA3AAI;
   Double_t        B1_A2ZARA2ZAI;
   Double_t        B1_A2ZARA3ZAR;
   Double_t        B1_A2ZARA3ZAI;
   Double_t        B1_A2ZARA2AAR;
   Double_t        B1_A2ZARA2AAI;
   Double_t        B1_A2ZARA3AAR;
   Double_t        B1_A2ZARA3AAI;
   Double_t        B1_A2ZAIA3ZAR;
   Double_t        B1_A2ZAIA3ZAI;
   Double_t        B1_A2ZAIA2AAR;
   Double_t        B1_A2ZAIA2AAI;
   Double_t        B1_A2ZAIA3AAR;
   Double_t        B1_A2ZAIA3AAI;
   Double_t        B1_A3ZARA3ZAI;
   Double_t        B1_A3ZARA2AAR;
   Double_t        B1_A3ZARA2AAI;
   Double_t        B1_A3ZARA3AAR;
   Double_t        B1_A3ZARA3AAI;
   Double_t        B1_A3ZAIA2AAR;
   Double_t        B1_A3ZAIA2AAI;
   Double_t        B1_A3ZAIA3AAR;
   Double_t        B1_A3ZAIA3AAI;
   Double_t        B1_A2AARA2AAI;
   Double_t        B1_A2AARA3AAR;
   Double_t        B1_A2AARA3AAI;
   Double_t        B1_A2AAIA3AAR;
   Double_t        B1_A2AAIA3AAI;
   Double_t        B1_A3AARA3AAI;
   Double_t        B1_A1L1ZZRA1L1ZZR;
   Double_t        B1_A1L1ZZIA1L1ZZI;
   Double_t        B1_A1LQZZRA1LQZZR;
   Double_t        B1_A1LQZZIA1LQZZI;
   Double_t        B1_A1ZZRA1L1ZZR;
   Double_t        B1_A1L1ZZRA2ZZR;
   Double_t        B1_A1L1ZZRA2ZZI;
   Double_t        B1_A1L1ZZRA3ZZR;
   Double_t        B1_A1L1ZZRA3ZZI;
   Double_t        B1_A1L1ZZRA2ZAR;
   Double_t        B1_A1L1ZZRA2ZAI;
   Double_t        B1_A1L1ZZRA3ZAR;
   Double_t        B1_A1L1ZZRA3ZAI;
   Double_t        B1_A1L1ZZRA2AAR;
   Double_t        B1_A1L1ZZRA2AAI;
   Double_t        B1_A1L1ZZRA3AAR;
   Double_t        B1_A1L1ZZRA3AAI;
   Double_t        B1_A1ZZRA1L1ZZI;
   Double_t        B1_A1L1ZZIA2ZZR;
   Double_t        B1_A1L1ZZIA2ZZI;
   Double_t        B1_A1L1ZZIA3ZZR;
   Double_t        B1_A1L1ZZIA3ZZI;
   Double_t        B1_A1L1ZZIA2ZAR;
   Double_t        B1_A1L1ZZIA2ZAI;
   Double_t        B1_A1L1ZZIA3ZAR;
   Double_t        B1_A1L1ZZIA3ZAI;
   Double_t        B1_A1L1ZZIA2AAR;
   Double_t        B1_A1L1ZZIA2AAI;
   Double_t        B1_A1L1ZZIA3AAR;
   Double_t        B1_A1L1ZZIA3AAI;
   Double_t        B1_A1L1ZZRA1L1ZZI;
   Double_t        B1_A1ZZRA1LQZZR;
   Double_t        B1_A1LQZZRA2ZZR;
   Double_t        B1_A1LQZZRA2ZZI;
   Double_t        B1_A1LQZZRA3ZZR;
   Double_t        B1_A1LQZZRA3ZZI;
   Double_t        B1_A1LQZZRA2ZAR;
   Double_t        B1_A1LQZZRA2ZAI;
   Double_t        B1_A1LQZZRA3ZAR;
   Double_t        B1_A1LQZZRA3ZAI;
   Double_t        B1_A1LQZZRA2AAR;
   Double_t        B1_A1LQZZRA2AAI;
   Double_t        B1_A1LQZZRA3AAR;
   Double_t        B1_A1LQZZRA3AAI;
   Double_t        B1_A1L1ZZRA1LQZZR;
   Double_t        B1_A1L1ZZIA1LQZZR;
   Double_t        B1_A1ZZRA1LQZZI;
   Double_t        B1_A1LQZZIA2ZZR;
   Double_t        B1_A1LQZZIA2ZZI;
   Double_t        B1_A1LQZZIA3ZZR;
   Double_t        B1_A1LQZZIA3ZZI;
   Double_t        B1_A1LQZZIA2ZAR;
   Double_t        B1_A1LQZZIA2ZAI;
   Double_t        B1_A1LQZZIA3ZAR;
   Double_t        B1_A1LQZZIA3ZAI;
   Double_t        B1_A1LQZZIA2AAR;
   Double_t        B1_A1LQZZIA2AAI;
   Double_t        B1_A1LQZZIA3AAR;
   Double_t        B1_A1LQZZIA3AAI;
   Double_t        B1_A1L1ZZRA1LQZZI;
   Double_t        B1_A1L1ZZIA1LQZZI;
   Double_t        B1_A1LQZZRA1LQZZI;
   Float_t         B19;
   Float_t         B20;

   // List of branches
   TBranch        *b_MH;   //!
   TBranch        *b_M1;   //!
   TBranch        *b_M2;   //!
   TBranch        *b_Phi0;   //!
   TBranch        *b_Theta0;   //!
   TBranch        *b_Phi;   //!
   TBranch        *b_Theta1;   //!
   TBranch        *b_Theta2;   //!
   TBranch        *b_HPhi;   //!
   TBranch        *b_HPT;   //!
   TBranch        *b_HY;   //!
   TBranch        *b_PhiOffset;   //!
   TBranch        *b_L1PT;   //!
   TBranch        *b_L1Eta;   //!
   TBranch        *b_L1Phi;   //!
   TBranch        *b_L1ID;   //!
   TBranch        *b_L2PT;   //!
   TBranch        *b_L2Eta;   //!
   TBranch        *b_L2Phi;   //!
   TBranch        *b_L2ID;   //!
   TBranch        *b_L3PT;   //!
   TBranch        *b_L3Eta;   //!
   TBranch        *b_L3Phi;   //!
   TBranch        *b_L3ID;   //!
   TBranch        *b_L4PT;   //!
   TBranch        *b_L4Eta;   //!
   TBranch        *b_L4Phi;   //!
   TBranch        *b_L4ID;   //!
   TBranch        *b_B2;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_PassEM;   //!
   TBranch        *b_PassME;   //!
   TBranch        *b_PassEE;   //!
   TBranch        *b_PassMM;   //!
   TBranch        *b_B1_A1ZZRA1ZZR;   //!
   TBranch        *b_B1_A2ZZRA2ZZR;   //!
   TBranch        *b_B1_A2ZZIA2ZZI;   //!
   TBranch        *b_B1_A3ZZRA3ZZR;   //!
   TBranch        *b_B1_A3ZZIA3ZZI;   //!
   TBranch        *b_B1_A2ZARA2ZAR;   //!
   TBranch        *b_B1_A2ZAIA2ZAI;   //!
   TBranch        *b_B1_A3ZARA3ZAR;   //!
   TBranch        *b_B1_A3ZAIA3ZAI;   //!
   TBranch        *b_B1_A2AARA2AAR;   //!
   TBranch        *b_B1_A2AAIA2AAI;   //!
   TBranch        *b_B1_A3AARA3AAR;   //!
   TBranch        *b_B1_A3AAIA3AAI;   //!
   TBranch        *b_B1_A1ZZRA2ZZR;   //!
   TBranch        *b_B1_A1ZZRA2ZZI;   //!
   TBranch        *b_B1_A1ZZRA3ZZR;   //!
   TBranch        *b_B1_A1ZZRA3ZZI;   //!
   TBranch        *b_B1_A1ZZRA2ZAR;   //!
   TBranch        *b_B1_A1ZZRA2ZAI;   //!
   TBranch        *b_B1_A1ZZRA3ZAR;   //!
   TBranch        *b_B1_A1ZZRA3ZAI;   //!
   TBranch        *b_B1_A1ZZRA2AAR;   //!
   TBranch        *b_B1_A1ZZRA2AAI;   //!
   TBranch        *b_B1_A1ZZRA3AAR;   //!
   TBranch        *b_B1_A1ZZRA3AAI;   //!
   TBranch        *b_B1_A2ZZRA2ZZI;   //!
   TBranch        *b_B1_A2ZZRA3ZZR;   //!
   TBranch        *b_B1_A2ZZRA3ZZI;   //!
   TBranch        *b_B1_A2ZZRA2ZAR;   //!
   TBranch        *b_B1_A2ZZRA2ZAI;   //!
   TBranch        *b_B1_A2ZZRA3ZAR;   //!
   TBranch        *b_B1_A2ZZRA3ZAI;   //!
   TBranch        *b_B1_A2ZZRA2AAR;   //!
   TBranch        *b_B1_A2ZZRA2AAI;   //!
   TBranch        *b_B1_A2ZZRA3AAR;   //!
   TBranch        *b_B1_A2ZZRA3AAI;   //!
   TBranch        *b_B1_A2ZZIA3ZZR;   //!
   TBranch        *b_B1_A2ZZIA3ZZI;   //!
   TBranch        *b_B1_A2ZZIA2ZAR;   //!
   TBranch        *b_B1_A2ZZIA2ZAI;   //!
   TBranch        *b_B1_A2ZZIA3ZAR;   //!
   TBranch        *b_B1_A2ZZIA3ZAI;   //!
   TBranch        *b_B1_A2ZZIA2AAR;   //!
   TBranch        *b_B1_A2ZZIA2AAI;   //!
   TBranch        *b_B1_A2ZZIA3AAR;   //!
   TBranch        *b_B1_A2ZZIA3AAI;   //!
   TBranch        *b_B1_A3ZZRA3ZZI;   //!
   TBranch        *b_B1_A3ZZRA2ZAR;   //!
   TBranch        *b_B1_A3ZZRA2ZAI;   //!
   TBranch        *b_B1_A3ZZRA3ZAR;   //!
   TBranch        *b_B1_A3ZZRA3ZAI;   //!
   TBranch        *b_B1_A3ZZRA2AAR;   //!
   TBranch        *b_B1_A3ZZRA2AAI;   //!
   TBranch        *b_B1_A3ZZRA3AAR;   //!
   TBranch        *b_B1_A3ZZRA3AAI;   //!
   TBranch        *b_B1_A3ZZIA2ZAR;   //!
   TBranch        *b_B1_A3ZZIA2ZAI;   //!
   TBranch        *b_B1_A3ZZIA3ZAR;   //!
   TBranch        *b_B1_A3ZZIA3ZAI;   //!
   TBranch        *b_B1_A3ZZIA2AAR;   //!
   TBranch        *b_B1_A3ZZIA2AAI;   //!
   TBranch        *b_B1_A3ZZIA3AAR;   //!
   TBranch        *b_B1_A3ZZIA3AAI;   //!
   TBranch        *b_B1_A2ZARA2ZAI;   //!
   TBranch        *b_B1_A2ZARA3ZAR;   //!
   TBranch        *b_B1_A2ZARA3ZAI;   //!
   TBranch        *b_B1_A2ZARA2AAR;   //!
   TBranch        *b_B1_A2ZARA2AAI;   //!
   TBranch        *b_B1_A2ZARA3AAR;   //!
   TBranch        *b_B1_A2ZARA3AAI;   //!
   TBranch        *b_B1_A2ZAIA3ZAR;   //!
   TBranch        *b_B1_A2ZAIA3ZAI;   //!
   TBranch        *b_B1_A2ZAIA2AAR;   //!
   TBranch        *b_B1_A2ZAIA2AAI;   //!
   TBranch        *b_B1_A2ZAIA3AAR;   //!
   TBranch        *b_B1_A2ZAIA3AAI;   //!
   TBranch        *b_B1_A3ZARA3ZAI;   //!
   TBranch        *b_B1_A3ZARA2AAR;   //!
   TBranch        *b_B1_A3ZARA2AAI;   //!
   TBranch        *b_B1_A3ZARA3AAR;   //!
   TBranch        *b_B1_A3ZARA3AAI;   //!
   TBranch        *b_B1_A3ZAIA2AAR;   //!
   TBranch        *b_B1_A3ZAIA2AAI;   //!
   TBranch        *b_B1_A3ZAIA3AAR;   //!
   TBranch        *b_B1_A3ZAIA3AAI;   //!
   TBranch        *b_B1_A2AARA2AAI;   //!
   TBranch        *b_B1_A2AARA3AAR;   //!
   TBranch        *b_B1_A2AARA3AAI;   //!
   TBranch        *b_B1_A2AAIA3AAR;   //!
   TBranch        *b_B1_A2AAIA3AAI;   //!
   TBranch        *b_B1_A3AARA3AAI;   //!
   TBranch        *b_B1_A1L1ZZRA1L1ZZR;   //!
   TBranch        *b_B1_A1L1ZZIA1L1ZZI;   //!
   TBranch        *b_B1_A1LQZZRA1LQZZR;   //!
   TBranch        *b_B1_A1LQZZIA1LQZZI;   //!
   TBranch        *b_B1_A1ZZRA1L1ZZR;   //!
   TBranch        *b_B1_A1L1ZZRA2ZZR;   //!
   TBranch        *b_B1_A1L1ZZRA2ZZI;   //!
   TBranch        *b_B1_A1L1ZZRA3ZZR;   //!
   TBranch        *b_B1_A1L1ZZRA3ZZI;   //!
   TBranch        *b_B1_A1L1ZZRA2ZAR;   //!
   TBranch        *b_B1_A1L1ZZRA2ZAI;   //!
   TBranch        *b_B1_A1L1ZZRA3ZAR;   //!
   TBranch        *b_B1_A1L1ZZRA3ZAI;   //!
   TBranch        *b_B1_A1L1ZZRA2AAR;   //!
   TBranch        *b_B1_A1L1ZZRA2AAI;   //!
   TBranch        *b_B1_A1L1ZZRA3AAR;   //!
   TBranch        *b_B1_A1L1ZZRA3AAI;   //!
   TBranch        *b_B1_A1ZZRA1L1ZZI;   //!
   TBranch        *b_B1_A1L1ZZIA2ZZR;   //!
   TBranch        *b_B1_A1L1ZZIA2ZZI;   //!
   TBranch        *b_B1_A1L1ZZIA3ZZR;   //!
   TBranch        *b_B1_A1L1ZZIA3ZZI;   //!
   TBranch        *b_B1_A1L1ZZIA2ZAR;   //!
   TBranch        *b_B1_A1L1ZZIA2ZAI;   //!
   TBranch        *b_B1_A1L1ZZIA3ZAR;   //!
   TBranch        *b_B1_A1L1ZZIA3ZAI;   //!
   TBranch        *b_B1_A1L1ZZIA2AAR;   //!
   TBranch        *b_B1_A1L1ZZIA2AAI;   //!
   TBranch        *b_B1_A1L1ZZIA3AAR;   //!
   TBranch        *b_B1_A1L1ZZIA3AAI;   //!
   TBranch        *b_B1_A1L1ZZRA1L1ZZI;   //!
   TBranch        *b_B1_A1ZZRA1LQZZR;   //!
   TBranch        *b_B1_A1LQZZRA2ZZR;   //!
   TBranch        *b_B1_A1LQZZRA2ZZI;   //!
   TBranch        *b_B1_A1LQZZRA3ZZR;   //!
   TBranch        *b_B1_A1LQZZRA3ZZI;   //!
   TBranch        *b_B1_A1LQZZRA2ZAR;   //!
   TBranch        *b_B1_A1LQZZRA2ZAI;   //!
   TBranch        *b_B1_A1LQZZRA3ZAR;   //!
   TBranch        *b_B1_A1LQZZRA3ZAI;   //!
   TBranch        *b_B1_A1LQZZRA2AAR;   //!
   TBranch        *b_B1_A1LQZZRA2AAI;   //!
   TBranch        *b_B1_A1LQZZRA3AAR;   //!
   TBranch        *b_B1_A1LQZZRA3AAI;   //!
   TBranch        *b_B1_A1L1ZZRA1LQZZR;   //!
   TBranch        *b_B1_A1L1ZZIA1LQZZR;   //!
   TBranch        *b_B1_A1ZZRA1LQZZI;   //!
   TBranch        *b_B1_A1LQZZIA2ZZR;   //!
   TBranch        *b_B1_A1LQZZIA2ZZI;   //!
   TBranch        *b_B1_A1LQZZIA3ZZR;   //!
   TBranch        *b_B1_A1LQZZIA3ZZI;   //!
   TBranch        *b_B1_A1LQZZIA2ZAR;   //!
   TBranch        *b_B1_A1LQZZIA2ZAI;   //!
   TBranch        *b_B1_A1LQZZIA3ZAR;   //!
   TBranch        *b_B1_A1LQZZIA3ZAI;   //!
   TBranch        *b_B1_A1LQZZIA2AAR;   //!
   TBranch        *b_B1_A1LQZZIA2AAI;   //!
   TBranch        *b_B1_A1LQZZIA3AAR;   //!
   TBranch        *b_B1_A1LQZZIA3AAI;   //!
   TBranch        *b_B1_A1L1ZZRA1LQZZI;   //!
   TBranch        *b_B1_A1L1ZZIA1LQZZI;   //!
   TBranch        *b_B1_A1LQZZRA1LQZZI;   //!
   TBranch        *b_B19;   //!
   TBranch        *b_B20;   //!

   MEOW(TTree *tree=0);
   virtual ~MEOW();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MEOW_cxx
MEOW::MEOW(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("BackgroundAll8TeV.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("BackgroundAll8TeV.root");
      }
      f->GetObject("ReducedTree",tree);

   }
   Init(tree);
}

MEOW::~MEOW()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MEOW::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MEOW::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MEOW::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("MH", &MH, &b_MH);
   fChain->SetBranchAddress("M1", &M1, &b_M1);
   fChain->SetBranchAddress("M2", &M2, &b_M2);
   fChain->SetBranchAddress("Phi0", &Phi0, &b_Phi0);
   fChain->SetBranchAddress("Theta0", &Theta0, &b_Theta0);
   fChain->SetBranchAddress("Phi", &Phi, &b_Phi);
   fChain->SetBranchAddress("Theta1", &Theta1, &b_Theta1);
   fChain->SetBranchAddress("Theta2", &Theta2, &b_Theta2);
   fChain->SetBranchAddress("HPhi", &HPhi, &b_HPhi);
   fChain->SetBranchAddress("HPT", &HPT, &b_HPT);
   fChain->SetBranchAddress("HY", &HY, &b_HY);
   fChain->SetBranchAddress("PhiOffset", &PhiOffset, &b_PhiOffset);
   fChain->SetBranchAddress("L1PT", &L1PT, &b_L1PT);
   fChain->SetBranchAddress("L1Eta", &L1Eta, &b_L1Eta);
   fChain->SetBranchAddress("L1Phi", &L1Phi, &b_L1Phi);
   fChain->SetBranchAddress("L1ID", &L1ID, &b_L1ID);
   fChain->SetBranchAddress("L2PT", &L2PT, &b_L2PT);
   fChain->SetBranchAddress("L2Eta", &L2Eta, &b_L2Eta);
   fChain->SetBranchAddress("L2Phi", &L2Phi, &b_L2Phi);
   fChain->SetBranchAddress("L2ID", &L2ID, &b_L2ID);
   fChain->SetBranchAddress("L3PT", &L3PT, &b_L3PT);
   fChain->SetBranchAddress("L3Eta", &L3Eta, &b_L3Eta);
   fChain->SetBranchAddress("L3Phi", &L3Phi, &b_L3Phi);
   fChain->SetBranchAddress("L3ID", &L3ID, &b_L3ID);
   fChain->SetBranchAddress("L4PT", &L4PT, &b_L4PT);
   fChain->SetBranchAddress("L4Eta", &L4Eta, &b_L4Eta);
   fChain->SetBranchAddress("L4Phi", &L4Phi, &b_L4Phi);
   fChain->SetBranchAddress("L4ID", &L4ID, &b_L4ID);
   fChain->SetBranchAddress("B2", &B2, &b_B2);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("PassEM", &PassEM, &b_PassEM);
   fChain->SetBranchAddress("PassME", &PassME, &b_PassME);
   fChain->SetBranchAddress("PassEE", &PassEE, &b_PassEE);
   fChain->SetBranchAddress("PassMM", &PassMM, &b_PassMM);
   fChain->SetBranchAddress("B1_A1ZZRA1ZZR", &B1_A1ZZRA1ZZR, &b_B1_A1ZZRA1ZZR);
   fChain->SetBranchAddress("B1_A2ZZRA2ZZR", &B1_A2ZZRA2ZZR, &b_B1_A2ZZRA2ZZR);
   fChain->SetBranchAddress("B1_A2ZZIA2ZZI", &B1_A2ZZIA2ZZI, &b_B1_A2ZZIA2ZZI);
   fChain->SetBranchAddress("B1_A3ZZRA3ZZR", &B1_A3ZZRA3ZZR, &b_B1_A3ZZRA3ZZR);
   fChain->SetBranchAddress("B1_A3ZZIA3ZZI", &B1_A3ZZIA3ZZI, &b_B1_A3ZZIA3ZZI);
   fChain->SetBranchAddress("B1_A2ZARA2ZAR", &B1_A2ZARA2ZAR, &b_B1_A2ZARA2ZAR);
   fChain->SetBranchAddress("B1_A2ZAIA2ZAI", &B1_A2ZAIA2ZAI, &b_B1_A2ZAIA2ZAI);
   fChain->SetBranchAddress("B1_A3ZARA3ZAR", &B1_A3ZARA3ZAR, &b_B1_A3ZARA3ZAR);
   fChain->SetBranchAddress("B1_A3ZAIA3ZAI", &B1_A3ZAIA3ZAI, &b_B1_A3ZAIA3ZAI);
   fChain->SetBranchAddress("B1_A2AARA2AAR", &B1_A2AARA2AAR, &b_B1_A2AARA2AAR);
   fChain->SetBranchAddress("B1_A2AAIA2AAI", &B1_A2AAIA2AAI, &b_B1_A2AAIA2AAI);
   fChain->SetBranchAddress("B1_A3AARA3AAR", &B1_A3AARA3AAR, &b_B1_A3AARA3AAR);
   fChain->SetBranchAddress("B1_A3AAIA3AAI", &B1_A3AAIA3AAI, &b_B1_A3AAIA3AAI);
   fChain->SetBranchAddress("B1_A1ZZRA2ZZR", &B1_A1ZZRA2ZZR, &b_B1_A1ZZRA2ZZR);
   fChain->SetBranchAddress("B1_A1ZZRA2ZZI", &B1_A1ZZRA2ZZI, &b_B1_A1ZZRA2ZZI);
   fChain->SetBranchAddress("B1_A1ZZRA3ZZR", &B1_A1ZZRA3ZZR, &b_B1_A1ZZRA3ZZR);
   fChain->SetBranchAddress("B1_A1ZZRA3ZZI", &B1_A1ZZRA3ZZI, &b_B1_A1ZZRA3ZZI);
   fChain->SetBranchAddress("B1_A1ZZRA2ZAR", &B1_A1ZZRA2ZAR, &b_B1_A1ZZRA2ZAR);
   fChain->SetBranchAddress("B1_A1ZZRA2ZAI", &B1_A1ZZRA2ZAI, &b_B1_A1ZZRA2ZAI);
   fChain->SetBranchAddress("B1_A1ZZRA3ZAR", &B1_A1ZZRA3ZAR, &b_B1_A1ZZRA3ZAR);
   fChain->SetBranchAddress("B1_A1ZZRA3ZAI", &B1_A1ZZRA3ZAI, &b_B1_A1ZZRA3ZAI);
   fChain->SetBranchAddress("B1_A1ZZRA2AAR", &B1_A1ZZRA2AAR, &b_B1_A1ZZRA2AAR);
   fChain->SetBranchAddress("B1_A1ZZRA2AAI", &B1_A1ZZRA2AAI, &b_B1_A1ZZRA2AAI);
   fChain->SetBranchAddress("B1_A1ZZRA3AAR", &B1_A1ZZRA3AAR, &b_B1_A1ZZRA3AAR);
   fChain->SetBranchAddress("B1_A1ZZRA3AAI", &B1_A1ZZRA3AAI, &b_B1_A1ZZRA3AAI);
   fChain->SetBranchAddress("B1_A2ZZRA2ZZI", &B1_A2ZZRA2ZZI, &b_B1_A2ZZRA2ZZI);
   fChain->SetBranchAddress("B1_A2ZZRA3ZZR", &B1_A2ZZRA3ZZR, &b_B1_A2ZZRA3ZZR);
   fChain->SetBranchAddress("B1_A2ZZRA3ZZI", &B1_A2ZZRA3ZZI, &b_B1_A2ZZRA3ZZI);
   fChain->SetBranchAddress("B1_A2ZZRA2ZAR", &B1_A2ZZRA2ZAR, &b_B1_A2ZZRA2ZAR);
   fChain->SetBranchAddress("B1_A2ZZRA2ZAI", &B1_A2ZZRA2ZAI, &b_B1_A2ZZRA2ZAI);
   fChain->SetBranchAddress("B1_A2ZZRA3ZAR", &B1_A2ZZRA3ZAR, &b_B1_A2ZZRA3ZAR);
   fChain->SetBranchAddress("B1_A2ZZRA3ZAI", &B1_A2ZZRA3ZAI, &b_B1_A2ZZRA3ZAI);
   fChain->SetBranchAddress("B1_A2ZZRA2AAR", &B1_A2ZZRA2AAR, &b_B1_A2ZZRA2AAR);
   fChain->SetBranchAddress("B1_A2ZZRA2AAI", &B1_A2ZZRA2AAI, &b_B1_A2ZZRA2AAI);
   fChain->SetBranchAddress("B1_A2ZZRA3AAR", &B1_A2ZZRA3AAR, &b_B1_A2ZZRA3AAR);
   fChain->SetBranchAddress("B1_A2ZZRA3AAI", &B1_A2ZZRA3AAI, &b_B1_A2ZZRA3AAI);
   fChain->SetBranchAddress("B1_A2ZZIA3ZZR", &B1_A2ZZIA3ZZR, &b_B1_A2ZZIA3ZZR);
   fChain->SetBranchAddress("B1_A2ZZIA3ZZI", &B1_A2ZZIA3ZZI, &b_B1_A2ZZIA3ZZI);
   fChain->SetBranchAddress("B1_A2ZZIA2ZAR", &B1_A2ZZIA2ZAR, &b_B1_A2ZZIA2ZAR);
   fChain->SetBranchAddress("B1_A2ZZIA2ZAI", &B1_A2ZZIA2ZAI, &b_B1_A2ZZIA2ZAI);
   fChain->SetBranchAddress("B1_A2ZZIA3ZAR", &B1_A2ZZIA3ZAR, &b_B1_A2ZZIA3ZAR);
   fChain->SetBranchAddress("B1_A2ZZIA3ZAI", &B1_A2ZZIA3ZAI, &b_B1_A2ZZIA3ZAI);
   fChain->SetBranchAddress("B1_A2ZZIA2AAR", &B1_A2ZZIA2AAR, &b_B1_A2ZZIA2AAR);
   fChain->SetBranchAddress("B1_A2ZZIA2AAI", &B1_A2ZZIA2AAI, &b_B1_A2ZZIA2AAI);
   fChain->SetBranchAddress("B1_A2ZZIA3AAR", &B1_A2ZZIA3AAR, &b_B1_A2ZZIA3AAR);
   fChain->SetBranchAddress("B1_A2ZZIA3AAI", &B1_A2ZZIA3AAI, &b_B1_A2ZZIA3AAI);
   fChain->SetBranchAddress("B1_A3ZZRA3ZZI", &B1_A3ZZRA3ZZI, &b_B1_A3ZZRA3ZZI);
   fChain->SetBranchAddress("B1_A3ZZRA2ZAR", &B1_A3ZZRA2ZAR, &b_B1_A3ZZRA2ZAR);
   fChain->SetBranchAddress("B1_A3ZZRA2ZAI", &B1_A3ZZRA2ZAI, &b_B1_A3ZZRA2ZAI);
   fChain->SetBranchAddress("B1_A3ZZRA3ZAR", &B1_A3ZZRA3ZAR, &b_B1_A3ZZRA3ZAR);
   fChain->SetBranchAddress("B1_A3ZZRA3ZAI", &B1_A3ZZRA3ZAI, &b_B1_A3ZZRA3ZAI);
   fChain->SetBranchAddress("B1_A3ZZRA2AAR", &B1_A3ZZRA2AAR, &b_B1_A3ZZRA2AAR);
   fChain->SetBranchAddress("B1_A3ZZRA2AAI", &B1_A3ZZRA2AAI, &b_B1_A3ZZRA2AAI);
   fChain->SetBranchAddress("B1_A3ZZRA3AAR", &B1_A3ZZRA3AAR, &b_B1_A3ZZRA3AAR);
   fChain->SetBranchAddress("B1_A3ZZRA3AAI", &B1_A3ZZRA3AAI, &b_B1_A3ZZRA3AAI);
   fChain->SetBranchAddress("B1_A3ZZIA2ZAR", &B1_A3ZZIA2ZAR, &b_B1_A3ZZIA2ZAR);
   fChain->SetBranchAddress("B1_A3ZZIA2ZAI", &B1_A3ZZIA2ZAI, &b_B1_A3ZZIA2ZAI);
   fChain->SetBranchAddress("B1_A3ZZIA3ZAR", &B1_A3ZZIA3ZAR, &b_B1_A3ZZIA3ZAR);
   fChain->SetBranchAddress("B1_A3ZZIA3ZAI", &B1_A3ZZIA3ZAI, &b_B1_A3ZZIA3ZAI);
   fChain->SetBranchAddress("B1_A3ZZIA2AAR", &B1_A3ZZIA2AAR, &b_B1_A3ZZIA2AAR);
   fChain->SetBranchAddress("B1_A3ZZIA2AAI", &B1_A3ZZIA2AAI, &b_B1_A3ZZIA2AAI);
   fChain->SetBranchAddress("B1_A3ZZIA3AAR", &B1_A3ZZIA3AAR, &b_B1_A3ZZIA3AAR);
   fChain->SetBranchAddress("B1_A3ZZIA3AAI", &B1_A3ZZIA3AAI, &b_B1_A3ZZIA3AAI);
   fChain->SetBranchAddress("B1_A2ZARA2ZAI", &B1_A2ZARA2ZAI, &b_B1_A2ZARA2ZAI);
   fChain->SetBranchAddress("B1_A2ZARA3ZAR", &B1_A2ZARA3ZAR, &b_B1_A2ZARA3ZAR);
   fChain->SetBranchAddress("B1_A2ZARA3ZAI", &B1_A2ZARA3ZAI, &b_B1_A2ZARA3ZAI);
   fChain->SetBranchAddress("B1_A2ZARA2AAR", &B1_A2ZARA2AAR, &b_B1_A2ZARA2AAR);
   fChain->SetBranchAddress("B1_A2ZARA2AAI", &B1_A2ZARA2AAI, &b_B1_A2ZARA2AAI);
   fChain->SetBranchAddress("B1_A2ZARA3AAR", &B1_A2ZARA3AAR, &b_B1_A2ZARA3AAR);
   fChain->SetBranchAddress("B1_A2ZARA3AAI", &B1_A2ZARA3AAI, &b_B1_A2ZARA3AAI);
   fChain->SetBranchAddress("B1_A2ZAIA3ZAR", &B1_A2ZAIA3ZAR, &b_B1_A2ZAIA3ZAR);
   fChain->SetBranchAddress("B1_A2ZAIA3ZAI", &B1_A2ZAIA3ZAI, &b_B1_A2ZAIA3ZAI);
   fChain->SetBranchAddress("B1_A2ZAIA2AAR", &B1_A2ZAIA2AAR, &b_B1_A2ZAIA2AAR);
   fChain->SetBranchAddress("B1_A2ZAIA2AAI", &B1_A2ZAIA2AAI, &b_B1_A2ZAIA2AAI);
   fChain->SetBranchAddress("B1_A2ZAIA3AAR", &B1_A2ZAIA3AAR, &b_B1_A2ZAIA3AAR);
   fChain->SetBranchAddress("B1_A2ZAIA3AAI", &B1_A2ZAIA3AAI, &b_B1_A2ZAIA3AAI);
   fChain->SetBranchAddress("B1_A3ZARA3ZAI", &B1_A3ZARA3ZAI, &b_B1_A3ZARA3ZAI);
   fChain->SetBranchAddress("B1_A3ZARA2AAR", &B1_A3ZARA2AAR, &b_B1_A3ZARA2AAR);
   fChain->SetBranchAddress("B1_A3ZARA2AAI", &B1_A3ZARA2AAI, &b_B1_A3ZARA2AAI);
   fChain->SetBranchAddress("B1_A3ZARA3AAR", &B1_A3ZARA3AAR, &b_B1_A3ZARA3AAR);
   fChain->SetBranchAddress("B1_A3ZARA3AAI", &B1_A3ZARA3AAI, &b_B1_A3ZARA3AAI);
   fChain->SetBranchAddress("B1_A3ZAIA2AAR", &B1_A3ZAIA2AAR, &b_B1_A3ZAIA2AAR);
   fChain->SetBranchAddress("B1_A3ZAIA2AAI", &B1_A3ZAIA2AAI, &b_B1_A3ZAIA2AAI);
   fChain->SetBranchAddress("B1_A3ZAIA3AAR", &B1_A3ZAIA3AAR, &b_B1_A3ZAIA3AAR);
   fChain->SetBranchAddress("B1_A3ZAIA3AAI", &B1_A3ZAIA3AAI, &b_B1_A3ZAIA3AAI);
   fChain->SetBranchAddress("B1_A2AARA2AAI", &B1_A2AARA2AAI, &b_B1_A2AARA2AAI);
   fChain->SetBranchAddress("B1_A2AARA3AAR", &B1_A2AARA3AAR, &b_B1_A2AARA3AAR);
   fChain->SetBranchAddress("B1_A2AARA3AAI", &B1_A2AARA3AAI, &b_B1_A2AARA3AAI);
   fChain->SetBranchAddress("B1_A2AAIA3AAR", &B1_A2AAIA3AAR, &b_B1_A2AAIA3AAR);
   fChain->SetBranchAddress("B1_A2AAIA3AAI", &B1_A2AAIA3AAI, &b_B1_A2AAIA3AAI);
   fChain->SetBranchAddress("B1_A3AARA3AAI", &B1_A3AARA3AAI, &b_B1_A3AARA3AAI);
   fChain->SetBranchAddress("B1_A1L1ZZRA1L1ZZR", &B1_A1L1ZZRA1L1ZZR, &b_B1_A1L1ZZRA1L1ZZR);
   fChain->SetBranchAddress("B1_A1L1ZZIA1L1ZZI", &B1_A1L1ZZIA1L1ZZI, &b_B1_A1L1ZZIA1L1ZZI);
   fChain->SetBranchAddress("B1_A1LQZZRA1LQZZR", &B1_A1LQZZRA1LQZZR, &b_B1_A1LQZZRA1LQZZR);
   fChain->SetBranchAddress("B1_A1LQZZIA1LQZZI", &B1_A1LQZZIA1LQZZI, &b_B1_A1LQZZIA1LQZZI);
   fChain->SetBranchAddress("B1_A1ZZRA1L1ZZR", &B1_A1ZZRA1L1ZZR, &b_B1_A1ZZRA1L1ZZR);
   fChain->SetBranchAddress("B1_A1L1ZZRA2ZZR", &B1_A1L1ZZRA2ZZR, &b_B1_A1L1ZZRA2ZZR);
   fChain->SetBranchAddress("B1_A1L1ZZRA2ZZI", &B1_A1L1ZZRA2ZZI, &b_B1_A1L1ZZRA2ZZI);
   fChain->SetBranchAddress("B1_A1L1ZZRA3ZZR", &B1_A1L1ZZRA3ZZR, &b_B1_A1L1ZZRA3ZZR);
   fChain->SetBranchAddress("B1_A1L1ZZRA3ZZI", &B1_A1L1ZZRA3ZZI, &b_B1_A1L1ZZRA3ZZI);
   fChain->SetBranchAddress("B1_A1L1ZZRA2ZAR", &B1_A1L1ZZRA2ZAR, &b_B1_A1L1ZZRA2ZAR);
   fChain->SetBranchAddress("B1_A1L1ZZRA2ZAI", &B1_A1L1ZZRA2ZAI, &b_B1_A1L1ZZRA2ZAI);
   fChain->SetBranchAddress("B1_A1L1ZZRA3ZAR", &B1_A1L1ZZRA3ZAR, &b_B1_A1L1ZZRA3ZAR);
   fChain->SetBranchAddress("B1_A1L1ZZRA3ZAI", &B1_A1L1ZZRA3ZAI, &b_B1_A1L1ZZRA3ZAI);
   fChain->SetBranchAddress("B1_A1L1ZZRA2AAR", &B1_A1L1ZZRA2AAR, &b_B1_A1L1ZZRA2AAR);
   fChain->SetBranchAddress("B1_A1L1ZZRA2AAI", &B1_A1L1ZZRA2AAI, &b_B1_A1L1ZZRA2AAI);
   fChain->SetBranchAddress("B1_A1L1ZZRA3AAR", &B1_A1L1ZZRA3AAR, &b_B1_A1L1ZZRA3AAR);
   fChain->SetBranchAddress("B1_A1L1ZZRA3AAI", &B1_A1L1ZZRA3AAI, &b_B1_A1L1ZZRA3AAI);
   fChain->SetBranchAddress("B1_A1ZZRA1L1ZZI", &B1_A1ZZRA1L1ZZI, &b_B1_A1ZZRA1L1ZZI);
   fChain->SetBranchAddress("B1_A1L1ZZIA2ZZR", &B1_A1L1ZZIA2ZZR, &b_B1_A1L1ZZIA2ZZR);
   fChain->SetBranchAddress("B1_A1L1ZZIA2ZZI", &B1_A1L1ZZIA2ZZI, &b_B1_A1L1ZZIA2ZZI);
   fChain->SetBranchAddress("B1_A1L1ZZIA3ZZR", &B1_A1L1ZZIA3ZZR, &b_B1_A1L1ZZIA3ZZR);
   fChain->SetBranchAddress("B1_A1L1ZZIA3ZZI", &B1_A1L1ZZIA3ZZI, &b_B1_A1L1ZZIA3ZZI);
   fChain->SetBranchAddress("B1_A1L1ZZIA2ZAR", &B1_A1L1ZZIA2ZAR, &b_B1_A1L1ZZIA2ZAR);
   fChain->SetBranchAddress("B1_A1L1ZZIA2ZAI", &B1_A1L1ZZIA2ZAI, &b_B1_A1L1ZZIA2ZAI);
   fChain->SetBranchAddress("B1_A1L1ZZIA3ZAR", &B1_A1L1ZZIA3ZAR, &b_B1_A1L1ZZIA3ZAR);
   fChain->SetBranchAddress("B1_A1L1ZZIA3ZAI", &B1_A1L1ZZIA3ZAI, &b_B1_A1L1ZZIA3ZAI);
   fChain->SetBranchAddress("B1_A1L1ZZIA2AAR", &B1_A1L1ZZIA2AAR, &b_B1_A1L1ZZIA2AAR);
   fChain->SetBranchAddress("B1_A1L1ZZIA2AAI", &B1_A1L1ZZIA2AAI, &b_B1_A1L1ZZIA2AAI);
   fChain->SetBranchAddress("B1_A1L1ZZIA3AAR", &B1_A1L1ZZIA3AAR, &b_B1_A1L1ZZIA3AAR);
   fChain->SetBranchAddress("B1_A1L1ZZIA3AAI", &B1_A1L1ZZIA3AAI, &b_B1_A1L1ZZIA3AAI);
   fChain->SetBranchAddress("B1_A1L1ZZRA1L1ZZI", &B1_A1L1ZZRA1L1ZZI, &b_B1_A1L1ZZRA1L1ZZI);
   fChain->SetBranchAddress("B1_A1ZZRA1LQZZR", &B1_A1ZZRA1LQZZR, &b_B1_A1ZZRA1LQZZR);
   fChain->SetBranchAddress("B1_A1LQZZRA2ZZR", &B1_A1LQZZRA2ZZR, &b_B1_A1LQZZRA2ZZR);
   fChain->SetBranchAddress("B1_A1LQZZRA2ZZI", &B1_A1LQZZRA2ZZI, &b_B1_A1LQZZRA2ZZI);
   fChain->SetBranchAddress("B1_A1LQZZRA3ZZR", &B1_A1LQZZRA3ZZR, &b_B1_A1LQZZRA3ZZR);
   fChain->SetBranchAddress("B1_A1LQZZRA3ZZI", &B1_A1LQZZRA3ZZI, &b_B1_A1LQZZRA3ZZI);
   fChain->SetBranchAddress("B1_A1LQZZRA2ZAR", &B1_A1LQZZRA2ZAR, &b_B1_A1LQZZRA2ZAR);
   fChain->SetBranchAddress("B1_A1LQZZRA2ZAI", &B1_A1LQZZRA2ZAI, &b_B1_A1LQZZRA2ZAI);
   fChain->SetBranchAddress("B1_A1LQZZRA3ZAR", &B1_A1LQZZRA3ZAR, &b_B1_A1LQZZRA3ZAR);
   fChain->SetBranchAddress("B1_A1LQZZRA3ZAI", &B1_A1LQZZRA3ZAI, &b_B1_A1LQZZRA3ZAI);
   fChain->SetBranchAddress("B1_A1LQZZRA2AAR", &B1_A1LQZZRA2AAR, &b_B1_A1LQZZRA2AAR);
   fChain->SetBranchAddress("B1_A1LQZZRA2AAI", &B1_A1LQZZRA2AAI, &b_B1_A1LQZZRA2AAI);
   fChain->SetBranchAddress("B1_A1LQZZRA3AAR", &B1_A1LQZZRA3AAR, &b_B1_A1LQZZRA3AAR);
   fChain->SetBranchAddress("B1_A1LQZZRA3AAI", &B1_A1LQZZRA3AAI, &b_B1_A1LQZZRA3AAI);
   fChain->SetBranchAddress("B1_A1L1ZZRA1LQZZR", &B1_A1L1ZZRA1LQZZR, &b_B1_A1L1ZZRA1LQZZR);
   fChain->SetBranchAddress("B1_A1L1ZZIA1LQZZR", &B1_A1L1ZZIA1LQZZR, &b_B1_A1L1ZZIA1LQZZR);
   fChain->SetBranchAddress("B1_A1ZZRA1LQZZI", &B1_A1ZZRA1LQZZI, &b_B1_A1ZZRA1LQZZI);
   fChain->SetBranchAddress("B1_A1LQZZIA2ZZR", &B1_A1LQZZIA2ZZR, &b_B1_A1LQZZIA2ZZR);
   fChain->SetBranchAddress("B1_A1LQZZIA2ZZI", &B1_A1LQZZIA2ZZI, &b_B1_A1LQZZIA2ZZI);
   fChain->SetBranchAddress("B1_A1LQZZIA3ZZR", &B1_A1LQZZIA3ZZR, &b_B1_A1LQZZIA3ZZR);
   fChain->SetBranchAddress("B1_A1LQZZIA3ZZI", &B1_A1LQZZIA3ZZI, &b_B1_A1LQZZIA3ZZI);
   fChain->SetBranchAddress("B1_A1LQZZIA2ZAR", &B1_A1LQZZIA2ZAR, &b_B1_A1LQZZIA2ZAR);
   fChain->SetBranchAddress("B1_A1LQZZIA2ZAI", &B1_A1LQZZIA2ZAI, &b_B1_A1LQZZIA2ZAI);
   fChain->SetBranchAddress("B1_A1LQZZIA3ZAR", &B1_A1LQZZIA3ZAR, &b_B1_A1LQZZIA3ZAR);
   fChain->SetBranchAddress("B1_A1LQZZIA3ZAI", &B1_A1LQZZIA3ZAI, &b_B1_A1LQZZIA3ZAI);
   fChain->SetBranchAddress("B1_A1LQZZIA2AAR", &B1_A1LQZZIA2AAR, &b_B1_A1LQZZIA2AAR);
   fChain->SetBranchAddress("B1_A1LQZZIA2AAI", &B1_A1LQZZIA2AAI, &b_B1_A1LQZZIA2AAI);
   fChain->SetBranchAddress("B1_A1LQZZIA3AAR", &B1_A1LQZZIA3AAR, &b_B1_A1LQZZIA3AAR);
   fChain->SetBranchAddress("B1_A1LQZZIA3AAI", &B1_A1LQZZIA3AAI, &b_B1_A1LQZZIA3AAI);
   fChain->SetBranchAddress("B1_A1L1ZZRA1LQZZI", &B1_A1L1ZZRA1LQZZI, &b_B1_A1L1ZZRA1LQZZI);
   fChain->SetBranchAddress("B1_A1L1ZZIA1LQZZI", &B1_A1L1ZZIA1LQZZI, &b_B1_A1L1ZZIA1LQZZI);
   fChain->SetBranchAddress("B1_A1LQZZRA1LQZZI", &B1_A1LQZZRA1LQZZI, &b_B1_A1LQZZRA1LQZZI);
   fChain->SetBranchAddress("B19", &B19, &b_B19);
   fChain->SetBranchAddress("B20", &B20, &b_B20);
   Notify();
}

Bool_t MEOW::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MEOW::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MEOW::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MEOW_cxx
