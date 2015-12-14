#include <string>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TStyle.h"

#include "PlotHelper2.h"

int main()
{
   gROOT->SetStyle("Plain");
   gStyle->SetPalette(1);

   TFile InputFile("ReducedTreeJets.root");
   TTree *Tree = (TTree *)InputFile.Get("OutputTree");

   double MR;
   double R;
   bool PassDiJetAve150;
   bool PassDiJetAve190;
   bool PassDiJetAve240;
   bool PassDiJetAve300;
   bool PassR014MR450BTag;
   double MaxTCHE;
   double SecondMaxTCHE;
   double MaxTCHP;
   double SecondMaxTCHP;
   double MaxSSVHE;
   double SecondMaxSSVHE;
   double MaxSSVHP;
   double SecondMaxSSVHP;
   
   Tree->SetBranchAddress("MR", &MR);
   Tree->SetBranchAddress("R", &R);
   Tree->SetBranchAddress("PassDiJetAve150", &PassDiJetAve150);
   Tree->SetBranchAddress("PassDiJetAve190", &PassDiJetAve190);
   Tree->SetBranchAddress("PassDiJetAve240", &PassDiJetAve240);
   Tree->SetBranchAddress("PassDiJetAve300", &PassDiJetAve300);
   Tree->SetBranchAddress("PassR014MR450BTag", &PassR014MR450BTag);
   Tree->SetBranchAddress("MaxTCHE", &MaxTCHE);
   Tree->SetBranchAddress("SecondMaxTCHE", &SecondMaxTCHE);
   Tree->SetBranchAddress("MaxTCHP", &MaxTCHP);
   Tree->SetBranchAddress("SecondMaxTCHP", &SecondMaxTCHP);
   Tree->SetBranchAddress("MaxSSVHE", &MaxSSVHE);
   Tree->SetBranchAddress("SecondMaxSSVHE", &SecondMaxSSVHE);
   Tree->SetBranchAddress("MaxSSVHP", &MaxSSVHP);
   Tree->SetBranchAddress("SecondMaxSSVHP", &SecondMaxSSVHP);

   TH1D HTCHEPassDiJetAve150("HTCHEPassDiJetAve150",
      "TCHE distribution, pass di-jet average 150 (R > 0.2, MR > 500);TCHE", 15, 0, 15);
   TH1D HTCHEPassDiJetAve150AndR014MR450BTag("HTCHEPassDiJetAve150AndR014MR450BTag",
      "TCHE distribution, pass di-jet average 150 (R > 0.2, MR > 500);TCHE", 15, 0, 15);
   TH1D HTCHEPassDiJetAve190("HTCHEPassDiJetAve190",
      "TCHE distribution, pass di-jet average 190 (R > 0.2, MR > 500);TCHE", 15, 0, 15);
   TH1D HTCHEPassDiJetAve190AndR014MR450BTag("HTCHEPassDiJetAve190AndR014MR450BTag",
      "TCHE distribution, pass di-jet average 190 (R > 0.2, MR > 500);TCHE", 15, 0, 15);
   TH1D HTCHEPassDiJetAve240("HTCHEPassDiJetAve240",
      "TCHE distribution, pass di-jet average 240 (R > 0.2, MR > 500);TCHE", 15, 0, 15);
   TH1D HTCHEPassDiJetAve240AndR014MR450BTag("HTCHEPassDiJetAve240AndR014MR450BTag",
      "TCHE distribution, pass di-jet average 240 (R > 0.2, MR > 500);TCHE", 15, 0, 15);
   TH1D HTCHEPassDiJetAve300("HTCHEPassDiJetAve300",
      "TCHE distribution, pass di-jet average 300 (R > 0.2, MR > 500);TCHE", 15, 0, 15);
   TH1D HTCHEPassDiJetAve300AndR014MR450BTag("HTCHEPassDiJetAve300AndR014MR450BTag",
      "TCHE distribution, pass di-jet average 300 (R > 0.2, MR > 500);TCHE", 15, 0, 15);
   
   TH1D HTCHE2PassDiJetAve150("HTCHE2PassDiJetAve150",
      "TCHE2 distribution, pass di-jet average 150 (R > 0.2, MR > 500);TCHE2", 15, 0, 15);
   TH1D HTCHE2PassDiJetAve150AndR014MR450BTag("HTCHE2PassDiJetAve150AndR014MR450BTag",
      "TCHE2 distribution, pass di-jet average 150 (R > 0.2, MR > 500);TCHE2", 15, 0, 15);
   TH1D HTCHE2PassDiJetAve190("HTCHE2PassDiJetAve190",
      "TCHE2 distribution, pass di-jet average 190 (R > 0.2, MR > 500);TCHE2", 15, 0, 15);
   TH1D HTCHE2PassDiJetAve190AndR014MR450BTag("HTCHE2PassDiJetAve190AndR014MR450BTag",
      "TCHE2 distribution, pass di-jet average 190 (R > 0.2, MR > 500);TCHE2", 15, 0, 15);
   TH1D HTCHE2PassDiJetAve240("HTCHE2PassDiJetAve240",
      "TCHE2 distribution, pass di-jet average 240 (R > 0.2, MR > 500);TCHE2", 15, 0, 15);
   TH1D HTCHE2PassDiJetAve240AndR014MR450BTag("HTCHE2PassDiJetAve240AndR014MR450BTag",
      "TCHE2 distribution, pass di-jet average 240 (R > 0.2, MR > 500);TCHE2", 15, 0, 15);
   TH1D HTCHE2PassDiJetAve300("HTCHE2PassDiJetAve300",
      "TCHE2 distribution, pass di-jet average 300 (R > 0.2, MR > 500);TCHE2", 15, 0, 15);
   TH1D HTCHE2PassDiJetAve300AndR014MR450BTag("HTCHE2PassDiJetAve300AndR014MR450BTag",
      "TCHE2 distribution, pass di-jet average 300 (R > 0.2, MR > 500);TCHE2", 15, 0, 15);

   TH1D HTCHPPassDiJetAve150("HTCHPPassDiJetAve150",
      "TCHP distribution, pass di-jet average 150 (R > 0.2, MR > 500);TCHP", 15, 0, 15);
   TH1D HTCHPPassDiJetAve150AndR014MR450BTag("HTCHPPassDiJetAve150AndR014MR450BTag",
      "TCHP distribution, pass di-jet average 150 (R > 0.2, MR > 500);TCHP", 15, 0, 15);
   TH1D HTCHPPassDiJetAve190("HTCHPPassDiJetAve190",
      "TCHP distribution, pass di-jet average 190 (R > 0.2, MR > 500);TCHP", 15, 0, 15);
   TH1D HTCHPPassDiJetAve190AndR014MR450BTag("HTCHPPassDiJetAve190AndR014MR450BTag",
      "TCHP distribution, pass di-jet average 190 (R > 0.2, MR > 500);TCHP", 15, 0, 15);
   TH1D HTCHPPassDiJetAve240("HTCHPPassDiJetAve240",
      "TCHP distribution, pass di-jet average 240 (R > 0.2, MR > 500);TCHP", 15, 0, 15);
   TH1D HTCHPPassDiJetAve240AndR014MR450BTag("HTCHPPassDiJetAve240AndR014MR450BTag",
      "TCHP distribution, pass di-jet average 240 (R > 0.2, MR > 500);TCHP", 15, 0, 15);
   TH1D HTCHPPassDiJetAve300("HTCHPPassDiJetAve300",
      "TCHP distribution, pass di-jet average 300 (R > 0.2, MR > 500);TCHP", 15, 0, 15);
   TH1D HTCHPPassDiJetAve300AndR014MR450BTag("HTCHPPassDiJetAve300AndR014MR450BTag",
      "TCHP distribution, pass di-jet average 300 (R > 0.2, MR > 500);TCHP", 15, 0, 15);
   
   TH1D HTCHP2PassDiJetAve150("HTCHP2PassDiJetAve150",
      "TCHP2 distribution, pass di-jet average 150 (R > 0.2, MR > 500);TCHP2", 15, 0, 15);
   TH1D HTCHP2PassDiJetAve150AndR014MR450BTag("HTCHP2PassDiJetAve150AndR014MR450BTag",
      "TCHP2 distribution, pass di-jet average 150 (R > 0.2, MR > 500);TCHP2", 15, 0, 15);
   TH1D HTCHP2PassDiJetAve190("HTCHP2PassDiJetAve190",
      "TCHP2 distribution, pass di-jet average 190 (R > 0.2, MR > 500);TCHP2", 15, 0, 15);
   TH1D HTCHP2PassDiJetAve190AndR014MR450BTag("HTCHP2PassDiJetAve190AndR014MR450BTag",
      "TCHP2 distribution, pass di-jet average 190 (R > 0.2, MR > 500);TCHP2", 15, 0, 15);
   TH1D HTCHP2PassDiJetAve240("HTCHP2PassDiJetAve240",
      "TCHP2 distribution, pass di-jet average 240 (R > 0.2, MR > 500);TCHP2", 15, 0, 15);
   TH1D HTCHP2PassDiJetAve240AndR014MR450BTag("HTCHP2PassDiJetAve240AndR014MR450BTag",
      "TCHP2 distribution, pass di-jet average 240 (R > 0.2, MR > 500);TCHP2", 15, 0, 15);
   TH1D HTCHP2PassDiJetAve300("HTCHP2PassDiJetAve300",
      "TCHP2 distribution, pass di-jet average 300 (R > 0.2, MR > 500);TCHP2", 15, 0, 15);
   TH1D HTCHP2PassDiJetAve300AndR014MR450BTag("HTCHP2PassDiJetAve300AndR014MR450BTag",
      "TCHP2 distribution, pass di-jet average 300 (R > 0.2, MR > 500);TCHP2", 15, 0, 15);

   TH1D HSSVHEPassDiJetAve150("HSSVHEPassDiJetAve150",
      "SSVHE distribution, pass di-jet average 150 (R > 0.2, MR > 500);SSVHE", 15, 0, 5);
   TH1D HSSVHEPassDiJetAve150AndR014MR450BTag("HSSVHEPassDiJetAve150AndR014MR450BTag",
      "SSVHE distribution, pass di-jet average 150 (R > 0.2, MR > 500);SSVHE", 15, 0, 5);
   TH1D HSSVHEPassDiJetAve190("HSSVHEPassDiJetAve190",
      "SSVHE distribution, pass di-jet average 190 (R > 0.2, MR > 500);SSVHE", 15, 0, 5);
   TH1D HSSVHEPassDiJetAve190AndR014MR450BTag("HSSVHEPassDiJetAve190AndR014MR450BTag",
      "SSVHE distribution, pass di-jet average 190 (R > 0.2, MR > 500);SSVHE", 15, 0, 5);
   TH1D HSSVHEPassDiJetAve240("HSSVHEPassDiJetAve240",
      "SSVHE distribution, pass di-jet average 240 (R > 0.2, MR > 500);SSVHE", 15, 0, 5);
   TH1D HSSVHEPassDiJetAve240AndR014MR450BTag("HSSVHEPassDiJetAve240AndR014MR450BTag",
      "SSVHE distribution, pass di-jet average 240 (R > 0.2, MR > 500);SSVHE", 15, 0, 5);
   TH1D HSSVHEPassDiJetAve300("HSSVHEPassDiJetAve300",
      "SSVHE distribution, pass di-jet average 300 (R > 0.2, MR > 500);SSVHE", 15, 0, 5);
   TH1D HSSVHEPassDiJetAve300AndR014MR450BTag("HSSVHEPassDiJetAve300AndR014MR450BTag",
      "SSVHE distribution, pass di-jet average 300 (R > 0.2, MR > 500);SSVHE", 15, 0, 5);
   
   TH1D HSSVHE2PassDiJetAve150("HSSVHE2PassDiJetAve150",
      "SSVHE2 distribution, pass di-jet average 150 (R > 0.2, MR > 500);SSVHE2", 15, 0, 5);
   TH1D HSSVHE2PassDiJetAve150AndR014MR450BTag("HSSVHE2PassDiJetAve150AndR014MR450BTag",
      "SSVHE2 distribution, pass di-jet average 150 (R > 0.2, MR > 500);SSVHE2", 15, 0, 5);
   TH1D HSSVHE2PassDiJetAve190("HSSVHE2PassDiJetAve190",
      "SSVHE2 distribution, pass di-jet average 190 (R > 0.2, MR > 500);SSVHE2", 15, 0, 5);
   TH1D HSSVHE2PassDiJetAve190AndR014MR450BTag("HSSVHE2PassDiJetAve190AndR014MR450BTag",
      "SSVHE2 distribution, pass di-jet average 190 (R > 0.2, MR > 500);SSVHE2", 15, 0, 5);
   TH1D HSSVHE2PassDiJetAve240("HSSVHE2PassDiJetAve240",
      "SSVHE2 distribution, pass di-jet average 240 (R > 0.2, MR > 500);SSVHE2", 15, 0, 5);
   TH1D HSSVHE2PassDiJetAve240AndR014MR450BTag("HSSVHE2PassDiJetAve240AndR014MR450BTag",
      "SSVHE2 distribution, pass di-jet average 240 (R > 0.2, MR > 500);SSVHE2", 15, 0, 5);
   TH1D HSSVHE2PassDiJetAve300("HSSVHE2PassDiJetAve300",
      "SSVHE2 distribution, pass di-jet average 300 (R > 0.2, MR > 500);SSVHE2", 15, 0, 5);
   TH1D HSSVHE2PassDiJetAve300AndR014MR450BTag("HSSVHE2PassDiJetAve300AndR014MR450BTag",
      "SSVHE2 distribution, pass di-jet average 300 (R > 0.2, MR > 500);SSVHE2", 15, 0, 5);

   TH1D HSSVHPPassDiJetAve150("HSSVHPPassDiJetAve150",
      "SSVHP distribution, pass di-jet average 150 (R > 0.2, MR > 500);SSVHP", 15, 0, 5);
   TH1D HSSVHPPassDiJetAve150AndR014MR450BTag("HSSVHPPassDiJetAve150AndR014MR450BTag",
      "SSVHP distribution, pass di-jet average 150 (R > 0.2, MR > 500);SSVHP", 15, 0, 5);
   TH1D HSSVHPPassDiJetAve190("HSSVHPPassDiJetAve190",
      "SSVHP distribution, pass di-jet average 190 (R > 0.2, MR > 500);SSVHP", 15, 0, 5);
   TH1D HSSVHPPassDiJetAve190AndR014MR450BTag("HSSVHPPassDiJetAve190AndR014MR450BTag",
      "SSVHP distribution, pass di-jet average 190 (R > 0.2, MR > 500);SSVHP", 15, 0, 5);
   TH1D HSSVHPPassDiJetAve240("HSSVHPPassDiJetAve240",
      "SSVHP distribution, pass di-jet average 240 (R > 0.2, MR > 500);SSVHP", 15, 0, 5);
   TH1D HSSVHPPassDiJetAve240AndR014MR450BTag("HSSVHPPassDiJetAve240AndR014MR450BTag",
      "SSVHP distribution, pass di-jet average 240 (R > 0.2, MR > 500);SSVHP", 15, 0, 5);
   TH1D HSSVHPPassDiJetAve300("HSSVHPPassDiJetAve300",
      "SSVHP distribution, pass di-jet average 300 (R > 0.2, MR > 500);SSVHP", 15, 0, 5);
   TH1D HSSVHPPassDiJetAve300AndR014MR450BTag("HSSVHPPassDiJetAve300AndR014MR450BTag",
      "SSVHP distribution, pass di-jet average 300 (R > 0.2, MR > 500);SSVHP", 15, 0, 5);
   
   TH1D HSSVHP2PassDiJetAve150("HSSVHP2PassDiJetAve150",
      "SSVHP2 distribution, pass di-jet average 150 (R > 0.2, MR > 500);SSVHP2", 15, 0, 5);
   TH1D HSSVHP2PassDiJetAve150AndR014MR450BTag("HSSVHP2PassDiJetAve150AndR014MR450BTag",
      "SSVHP2 distribution, pass di-jet average 150 (R > 0.2, MR > 500);SSVHP2", 15, 0, 5);
   TH1D HSSVHP2PassDiJetAve190("HSSVHP2PassDiJetAve190",
      "SSVHP2 distribution, pass di-jet average 190 (R > 0.2, MR > 500);SSVHP2", 15, 0, 5);
   TH1D HSSVHP2PassDiJetAve190AndR014MR450BTag("HSSVHP2PassDiJetAve190AndR014MR450BTag",
      "SSVHP2 distribution, pass di-jet average 190 (R > 0.2, MR > 500);SSVHP2", 15, 0, 5);
   TH1D HSSVHP2PassDiJetAve240("HSSVHP2PassDiJetAve240",
      "SSVHP2 distribution, pass di-jet average 240 (R > 0.2, MR > 500);SSVHP2", 15, 0, 5);
   TH1D HSSVHP2PassDiJetAve240AndR014MR450BTag("HSSVHP2PassDiJetAve240AndR014MR450BTag",
      "SSVHP2 distribution, pass di-jet average 240 (R > 0.2, MR > 500);SSVHP2", 15, 0, 5);
   TH1D HSSVHP2PassDiJetAve300("HSSVHP2PassDiJetAve300",
      "SSVHP2 distribution, pass di-jet average 300 (R > 0.2, MR > 500);SSVHP2", 15, 0, 5);
   TH1D HSSVHP2PassDiJetAve300AndR014MR450BTag("HSSVHP2PassDiJetAve300AndR014MR450BTag",
      "SSVHP2 distribution, pass di-jet average 300 (R > 0.2, MR > 500);SSVHP2", 15, 0, 5);

   PsFileHelper PsFile("SimpleTurnOnCurve.ps");
   PsFile.AddTextPage("Simple turn-on curve from HT dataset on b-tagging");

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      if(PassDiJetAve150 == true && R > 0.20 && MR > 500)
         HTCHEPassDiJetAve150.Fill(MaxTCHE);
      if(PassDiJetAve150 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHEPassDiJetAve150AndR014MR450BTag.Fill(MaxTCHE);
      if(PassDiJetAve190 == true && R > 0.20 && MR > 500)
         HTCHEPassDiJetAve190.Fill(MaxTCHE);
      if(PassDiJetAve190 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHEPassDiJetAve190AndR014MR450BTag.Fill(MaxTCHE);
      if(PassDiJetAve240 == true && R > 0.20 && MR > 500)
         HTCHEPassDiJetAve240.Fill(MaxTCHE);
      if(PassDiJetAve240 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHEPassDiJetAve240AndR014MR450BTag.Fill(MaxTCHE);
      if(PassDiJetAve300 == true && R > 0.20 && MR > 500)
         HTCHEPassDiJetAve300.Fill(MaxTCHE);
      if(PassDiJetAve300 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHEPassDiJetAve300AndR014MR450BTag.Fill(MaxTCHE);
      
      if(PassDiJetAve150 == true && R > 0.20 && MR > 500)
         HTCHE2PassDiJetAve150.Fill(SecondMaxTCHE);
      if(PassDiJetAve150 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHE2PassDiJetAve150AndR014MR450BTag.Fill(SecondMaxTCHE);
      if(PassDiJetAve190 == true && R > 0.20 && MR > 500)
         HTCHE2PassDiJetAve190.Fill(SecondMaxTCHE);
      if(PassDiJetAve190 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHE2PassDiJetAve190AndR014MR450BTag.Fill(SecondMaxTCHE);
      if(PassDiJetAve240 == true && R > 0.20 && MR > 500)
         HTCHE2PassDiJetAve240.Fill(SecondMaxTCHE);
      if(PassDiJetAve240 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHE2PassDiJetAve240AndR014MR450BTag.Fill(SecondMaxTCHE);
      if(PassDiJetAve300 == true && R > 0.20 && MR > 500)
         HTCHE2PassDiJetAve300.Fill(SecondMaxTCHE);
      if(PassDiJetAve300 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHE2PassDiJetAve300AndR014MR450BTag.Fill(SecondMaxTCHE);
      
      if(PassDiJetAve150 == true && R > 0.20 && MR > 500)
         HTCHPPassDiJetAve150.Fill(MaxTCHP);
      if(PassDiJetAve150 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHPPassDiJetAve150AndR014MR450BTag.Fill(MaxTCHP);
      if(PassDiJetAve190 == true && R > 0.20 && MR > 500)
         HTCHPPassDiJetAve190.Fill(MaxTCHP);
      if(PassDiJetAve190 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHPPassDiJetAve190AndR014MR450BTag.Fill(MaxTCHP);
      if(PassDiJetAve240 == true && R > 0.20 && MR > 500)
         HTCHPPassDiJetAve240.Fill(MaxTCHP);
      if(PassDiJetAve240 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHPPassDiJetAve240AndR014MR450BTag.Fill(MaxTCHP);
      if(PassDiJetAve300 == true && R > 0.20 && MR > 500)
         HTCHPPassDiJetAve300.Fill(MaxTCHP);
      if(PassDiJetAve300 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHPPassDiJetAve300AndR014MR450BTag.Fill(MaxTCHP);
      
      if(PassDiJetAve150 == true && R > 0.20 && MR > 500)
         HTCHP2PassDiJetAve150.Fill(SecondMaxTCHP);
      if(PassDiJetAve150 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHP2PassDiJetAve150AndR014MR450BTag.Fill(SecondMaxTCHP);
      if(PassDiJetAve190 == true && R > 0.20 && MR > 500)
         HTCHP2PassDiJetAve190.Fill(SecondMaxTCHP);
      if(PassDiJetAve190 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHP2PassDiJetAve190AndR014MR450BTag.Fill(SecondMaxTCHP);
      if(PassDiJetAve240 == true && R > 0.20 && MR > 500)
         HTCHP2PassDiJetAve240.Fill(SecondMaxTCHP);
      if(PassDiJetAve240 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHP2PassDiJetAve240AndR014MR450BTag.Fill(SecondMaxTCHP);
      if(PassDiJetAve300 == true && R > 0.20 && MR > 500)
         HTCHP2PassDiJetAve300.Fill(SecondMaxTCHP);
      if(PassDiJetAve300 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HTCHP2PassDiJetAve300AndR014MR450BTag.Fill(SecondMaxTCHP);
      
      if(PassDiJetAve150 == true && R > 0.20 && MR > 500)
         HSSVHEPassDiJetAve150.Fill(MaxSSVHE);
      if(PassDiJetAve150 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHEPassDiJetAve150AndR014MR450BTag.Fill(MaxSSVHE);
      if(PassDiJetAve190 == true && R > 0.20 && MR > 500)
         HSSVHEPassDiJetAve190.Fill(MaxSSVHE);
      if(PassDiJetAve190 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHEPassDiJetAve190AndR014MR450BTag.Fill(MaxSSVHE);
      if(PassDiJetAve240 == true && R > 0.20 && MR > 500)
         HSSVHEPassDiJetAve240.Fill(MaxSSVHE);
      if(PassDiJetAve240 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHEPassDiJetAve240AndR014MR450BTag.Fill(MaxSSVHE);
      if(PassDiJetAve300 == true && R > 0.20 && MR > 500)
         HSSVHEPassDiJetAve300.Fill(MaxSSVHE);
      if(PassDiJetAve300 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHEPassDiJetAve300AndR014MR450BTag.Fill(MaxSSVHE);
      
      if(PassDiJetAve150 == true && R > 0.20 && MR > 500)
         HSSVHE2PassDiJetAve150.Fill(SecondMaxSSVHE);
      if(PassDiJetAve150 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHE2PassDiJetAve150AndR014MR450BTag.Fill(SecondMaxSSVHE);
      if(PassDiJetAve190 == true && R > 0.20 && MR > 500)
         HSSVHE2PassDiJetAve190.Fill(SecondMaxSSVHE);
      if(PassDiJetAve190 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHE2PassDiJetAve190AndR014MR450BTag.Fill(SecondMaxSSVHE);
      if(PassDiJetAve240 == true && R > 0.20 && MR > 500)
         HSSVHE2PassDiJetAve240.Fill(SecondMaxSSVHE);
      if(PassDiJetAve240 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHE2PassDiJetAve240AndR014MR450BTag.Fill(SecondMaxSSVHE);
      if(PassDiJetAve300 == true && R > 0.20 && MR > 500)
         HSSVHE2PassDiJetAve300.Fill(SecondMaxSSVHE);
      if(PassDiJetAve300 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHE2PassDiJetAve300AndR014MR450BTag.Fill(SecondMaxSSVHE);
      
      if(PassDiJetAve150 == true && R > 0.20 && MR > 500)
         HSSVHPPassDiJetAve150.Fill(MaxSSVHP);
      if(PassDiJetAve150 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHPPassDiJetAve150AndR014MR450BTag.Fill(MaxSSVHP);
      if(PassDiJetAve190 == true && R > 0.20 && MR > 500)
         HSSVHPPassDiJetAve190.Fill(MaxSSVHP);
      if(PassDiJetAve190 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHPPassDiJetAve190AndR014MR450BTag.Fill(MaxSSVHP);
      if(PassDiJetAve240 == true && R > 0.20 && MR > 500)
         HSSVHPPassDiJetAve240.Fill(MaxSSVHP);
      if(PassDiJetAve240 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHPPassDiJetAve240AndR014MR450BTag.Fill(MaxSSVHP);
      if(PassDiJetAve300 == true && R > 0.20 && MR > 500)
         HSSVHPPassDiJetAve300.Fill(MaxSSVHP);
      if(PassDiJetAve300 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHPPassDiJetAve300AndR014MR450BTag.Fill(MaxSSVHP);
      
      if(PassDiJetAve150 == true && R > 0.20 && MR > 500)
         HSSVHP2PassDiJetAve150.Fill(SecondMaxSSVHP);
      if(PassDiJetAve150 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHP2PassDiJetAve150AndR014MR450BTag.Fill(SecondMaxSSVHP);
      if(PassDiJetAve190 == true && R > 0.20 && MR > 500)
         HSSVHP2PassDiJetAve190.Fill(SecondMaxSSVHP);
      if(PassDiJetAve190 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHP2PassDiJetAve190AndR014MR450BTag.Fill(SecondMaxSSVHP);
      if(PassDiJetAve240 == true && R > 0.20 && MR > 500)
         HSSVHP2PassDiJetAve240.Fill(SecondMaxSSVHP);
      if(PassDiJetAve240 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHP2PassDiJetAve240AndR014MR450BTag.Fill(SecondMaxSSVHP);
      if(PassDiJetAve300 == true && R > 0.20 && MR > 500)
         HSSVHP2PassDiJetAve300.Fill(SecondMaxSSVHP);
      if(PassDiJetAve300 == true && PassR014MR450BTag == true && R > 0.20 && MR > 500)
         HSSVHP2PassDiJetAve300AndR014MR450BTag.Fill(SecondMaxSSVHP);
   }

   PsFile.AddPlot(HTCHEPassDiJetAve150);
   PsFile.AddPlot(HTCHEPassDiJetAve150AndR014MR450BTag);

   TGraphAsymmErrors HTCHETurnOnR014MR450BTag_150;
   HTCHETurnOnR014MR450BTag_150.BayesDivide(&HTCHEPassDiJetAve150AndR014MR450BTag, &HTCHEPassDiJetAve150);
   HTCHETurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 150;TCHE");
   PsFile.AddPlot(HTCHETurnOnR014MR450BTag_150, "ape");

   PsFile.AddPlot(HTCHEPassDiJetAve190);
   PsFile.AddPlot(HTCHEPassDiJetAve190AndR014MR450BTag);

   TGraphAsymmErrors HTCHETurnOnR014MR450BTag_190;
   HTCHETurnOnR014MR450BTag_190.BayesDivide(&HTCHEPassDiJetAve190AndR014MR450BTag, &HTCHEPassDiJetAve190);
   HTCHETurnOnR014MR450BTag_190.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 190;TCHE");
   PsFile.AddPlot(HTCHETurnOnR014MR450BTag_190, "ape");

   PsFile.AddPlot(HTCHEPassDiJetAve240);
   PsFile.AddPlot(HTCHEPassDiJetAve240AndR014MR450BTag);

   TGraphAsymmErrors HTCHETurnOnR014MR450BTag_240;
   HTCHETurnOnR014MR450BTag_240.BayesDivide(&HTCHEPassDiJetAve240AndR014MR450BTag, &HTCHEPassDiJetAve240);
   HTCHETurnOnR014MR450BTag_240.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 240;TCHE");
   PsFile.AddPlot(HTCHETurnOnR014MR450BTag_240, "ape");

   PsFile.AddPlot(HTCHEPassDiJetAve300);
   PsFile.AddPlot(HTCHEPassDiJetAve300AndR014MR450BTag);

   TGraphAsymmErrors HTCHETurnOnR014MR450BTag_300;
   HTCHETurnOnR014MR450BTag_300.BayesDivide(&HTCHEPassDiJetAve300AndR014MR450BTag, &HTCHEPassDiJetAve300);
   HTCHETurnOnR014MR450BTag_300.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 300;TCHE");
   PsFile.AddPlot(HTCHETurnOnR014MR450BTag_300, "ape");

   TCanvas CTCHE;
   HTCHETurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/BTag with respect to different dijet thresholds;TCHE");
   HTCHETurnOnR014MR450BTag_150.Draw("ape");
   HTCHETurnOnR014MR450BTag_190.SetLineColor(2);
   HTCHETurnOnR014MR450BTag_190.Draw("pe");
   HTCHETurnOnR014MR450BTag_240.SetLineColor(3);
   HTCHETurnOnR014MR450BTag_240.Draw("pe");
   HTCHETurnOnR014MR450BTag_300.SetLineColor(4);
   HTCHETurnOnR014MR450BTag_300.Draw("pe");
   CTCHE.SaveAs("TCHE1.png");
   CTCHE.SaveAs("TCHE1.C");
   CTCHE.SaveAs("TCHE1.eps");
   PsFile.AddCanvas(CTCHE);

   PsFile.AddPlot(HTCHE2PassDiJetAve150);
   PsFile.AddPlot(HTCHE2PassDiJetAve150AndR014MR450BTag);

   TGraphAsymmErrors HTCHE2TurnOnR014MR450BTag_150;
   HTCHE2TurnOnR014MR450BTag_150.BayesDivide(&HTCHE2PassDiJetAve150AndR014MR450BTag, &HTCHE2PassDiJetAve150);
   HTCHE2TurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 150;TCHE2");
   PsFile.AddPlot(HTCHE2TurnOnR014MR450BTag_150, "ape");

   PsFile.AddPlot(HTCHE2PassDiJetAve190);
   PsFile.AddPlot(HTCHE2PassDiJetAve190AndR014MR450BTag);

   TGraphAsymmErrors HTCHE2TurnOnR014MR450BTag_190;
   HTCHE2TurnOnR014MR450BTag_190.BayesDivide(&HTCHE2PassDiJetAve190AndR014MR450BTag, &HTCHE2PassDiJetAve190);
   HTCHE2TurnOnR014MR450BTag_190.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 190;TCHE2");
   PsFile.AddPlot(HTCHE2TurnOnR014MR450BTag_190, "ape");

   PsFile.AddPlot(HTCHE2PassDiJetAve240);
   PsFile.AddPlot(HTCHE2PassDiJetAve240AndR014MR450BTag);

   TGraphAsymmErrors HTCHE2TurnOnR014MR450BTag_240;
   HTCHE2TurnOnR014MR450BTag_240.BayesDivide(&HTCHE2PassDiJetAve240AndR014MR450BTag, &HTCHE2PassDiJetAve240);
   HTCHE2TurnOnR014MR450BTag_240.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 240;TCHE2");
   PsFile.AddPlot(HTCHE2TurnOnR014MR450BTag_240, "ape");

   PsFile.AddPlot(HTCHE2PassDiJetAve300);
   PsFile.AddPlot(HTCHE2PassDiJetAve300AndR014MR450BTag);

   TGraphAsymmErrors HTCHE2TurnOnR014MR450BTag_300;
   HTCHE2TurnOnR014MR450BTag_300.BayesDivide(&HTCHE2PassDiJetAve300AndR014MR450BTag, &HTCHE2PassDiJetAve300);
   HTCHE2TurnOnR014MR450BTag_300.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 300;TCHE2");
   PsFile.AddPlot(HTCHE2TurnOnR014MR450BTag_300, "ape");

   TCanvas CTCHE2;
   HTCHE2TurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/BTag with respect to different dijet thresholds;TCHE2");
   HTCHE2TurnOnR014MR450BTag_150.Draw("ape");
   HTCHE2TurnOnR014MR450BTag_190.SetLineColor(2);
   HTCHE2TurnOnR014MR450BTag_190.Draw("pe");
   HTCHE2TurnOnR014MR450BTag_240.SetLineColor(3);
   HTCHE2TurnOnR014MR450BTag_240.Draw("pe");
   HTCHE2TurnOnR014MR450BTag_300.SetLineColor(4);
   HTCHE2TurnOnR014MR450BTag_300.Draw("pe");
   CTCHE2.SaveAs("TCHE2.png");
   CTCHE2.SaveAs("TCHE2.C");
   CTCHE2.SaveAs("TCHE2.eps");
   PsFile.AddCanvas(CTCHE2);

   PsFile.AddPlot(HTCHPPassDiJetAve150);
   PsFile.AddPlot(HTCHPPassDiJetAve150AndR014MR450BTag);

   TGraphAsymmErrors HTCHPTurnOnR014MR450BTag_150;
   HTCHPTurnOnR014MR450BTag_150.BayesDivide(&HTCHPPassDiJetAve150AndR014MR450BTag, &HTCHPPassDiJetAve150);
   HTCHPTurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 150;TCHP");
   PsFile.AddPlot(HTCHPTurnOnR014MR450BTag_150, "ape");

   PsFile.AddPlot(HTCHPPassDiJetAve190);
   PsFile.AddPlot(HTCHPPassDiJetAve190AndR014MR450BTag);

   TGraphAsymmErrors HTCHPTurnOnR014MR450BTag_190;
   HTCHPTurnOnR014MR450BTag_190.BayesDivide(&HTCHPPassDiJetAve190AndR014MR450BTag, &HTCHPPassDiJetAve190);
   HTCHPTurnOnR014MR450BTag_190.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 190;TCHP");
   PsFile.AddPlot(HTCHPTurnOnR014MR450BTag_190, "ape");

   PsFile.AddPlot(HTCHPPassDiJetAve240);
   PsFile.AddPlot(HTCHPPassDiJetAve240AndR014MR450BTag);

   TGraphAsymmErrors HTCHPTurnOnR014MR450BTag_240;
   HTCHPTurnOnR014MR450BTag_240.BayesDivide(&HTCHPPassDiJetAve240AndR014MR450BTag, &HTCHPPassDiJetAve240);
   HTCHPTurnOnR014MR450BTag_240.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 240;TCHP");
   PsFile.AddPlot(HTCHPTurnOnR014MR450BTag_240, "ape");

   PsFile.AddPlot(HTCHPPassDiJetAve300);
   PsFile.AddPlot(HTCHPPassDiJetAve300AndR014MR450BTag);

   TGraphAsymmErrors HTCHPTurnOnR014MR450BTag_300;
   HTCHPTurnOnR014MR450BTag_300.BayesDivide(&HTCHPPassDiJetAve300AndR014MR450BTag, &HTCHPPassDiJetAve300);
   HTCHPTurnOnR014MR450BTag_300.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 300;TCHP");
   PsFile.AddPlot(HTCHPTurnOnR014MR450BTag_300, "ape");

   TCanvas CTCHP;
   HTCHPTurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/BTag with respect to different dijet thresholds;TCHP");
   HTCHPTurnOnR014MR450BTag_150.Draw("ape");
   HTCHPTurnOnR014MR450BTag_190.SetLineColor(2);
   HTCHPTurnOnR014MR450BTag_190.Draw("pe");
   HTCHPTurnOnR014MR450BTag_240.SetLineColor(3);
   HTCHPTurnOnR014MR450BTag_240.Draw("pe");
   HTCHPTurnOnR014MR450BTag_300.SetLineColor(4);
   HTCHPTurnOnR014MR450BTag_300.Draw("pe");
   CTCHP.SaveAs("TCHP1.png");
   CTCHP.SaveAs("TCHP1.C");
   CTCHP.SaveAs("TCHP1.eps");
   PsFile.AddCanvas(CTCHP);

   PsFile.AddPlot(HTCHP2PassDiJetAve150);
   PsFile.AddPlot(HTCHP2PassDiJetAve150AndR014MR450BTag);

   TGraphAsymmErrors HTCHP2TurnOnR014MR450BTag_150;
   HTCHP2TurnOnR014MR450BTag_150.BayesDivide(&HTCHP2PassDiJetAve150AndR014MR450BTag, &HTCHP2PassDiJetAve150);
   HTCHP2TurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 150;TCHP2");
   PsFile.AddPlot(HTCHP2TurnOnR014MR450BTag_150, "ape");

   PsFile.AddPlot(HTCHP2PassDiJetAve190);
   PsFile.AddPlot(HTCHP2PassDiJetAve190AndR014MR450BTag);

   TGraphAsymmErrors HTCHP2TurnOnR014MR450BTag_190;
   HTCHP2TurnOnR014MR450BTag_190.BayesDivide(&HTCHP2PassDiJetAve190AndR014MR450BTag, &HTCHP2PassDiJetAve190);
   HTCHP2TurnOnR014MR450BTag_190.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 190;TCHP2");
   PsFile.AddPlot(HTCHP2TurnOnR014MR450BTag_190, "ape");

   PsFile.AddPlot(HTCHP2PassDiJetAve240);
   PsFile.AddPlot(HTCHP2PassDiJetAve240AndR014MR450BTag);

   TGraphAsymmErrors HTCHP2TurnOnR014MR450BTag_240;
   HTCHP2TurnOnR014MR450BTag_240.BayesDivide(&HTCHP2PassDiJetAve240AndR014MR450BTag, &HTCHP2PassDiJetAve240);
   HTCHP2TurnOnR014MR450BTag_240.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 240;TCHP2");
   PsFile.AddPlot(HTCHP2TurnOnR014MR450BTag_240, "ape");

   PsFile.AddPlot(HTCHP2PassDiJetAve300);
   PsFile.AddPlot(HTCHP2PassDiJetAve300AndR014MR450BTag);

   TGraphAsymmErrors HTCHP2TurnOnR014MR450BTag_300;
   HTCHP2TurnOnR014MR450BTag_300.BayesDivide(&HTCHP2PassDiJetAve300AndR014MR450BTag, &HTCHP2PassDiJetAve300);
   HTCHP2TurnOnR014MR450BTag_300.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 300;TCHP2");
   PsFile.AddPlot(HTCHP2TurnOnR014MR450BTag_300, "ape");

   TCanvas CTCHP2;
   HTCHP2TurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/BTag with respect to different dijet thresholds;TCHP2");
   HTCHP2TurnOnR014MR450BTag_150.Draw("ape");
   HTCHP2TurnOnR014MR450BTag_190.SetLineColor(2);
   HTCHP2TurnOnR014MR450BTag_190.Draw("pe");
   HTCHP2TurnOnR014MR450BTag_240.SetLineColor(3);
   HTCHP2TurnOnR014MR450BTag_240.Draw("pe");
   HTCHP2TurnOnR014MR450BTag_300.SetLineColor(4);
   HTCHP2TurnOnR014MR450BTag_300.Draw("pe");
   CTCHP2.SaveAs("TCHP2.png");
   CTCHP2.SaveAs("TCHP2.C");
   CTCHP2.SaveAs("TCHP2.eps");
   PsFile.AddCanvas(CTCHP2);
   
   PsFile.AddPlot(HSSVHEPassDiJetAve150);
   PsFile.AddPlot(HSSVHEPassDiJetAve150AndR014MR450BTag);

   TGraphAsymmErrors HSSVHETurnOnR014MR450BTag_150;
   HSSVHETurnOnR014MR450BTag_150.BayesDivide(&HSSVHEPassDiJetAve150AndR014MR450BTag, &HSSVHEPassDiJetAve150);
   HSSVHETurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 150;SSVHE");
   PsFile.AddPlot(HSSVHETurnOnR014MR450BTag_150, "ape");

   PsFile.AddPlot(HSSVHEPassDiJetAve190);
   PsFile.AddPlot(HSSVHEPassDiJetAve190AndR014MR450BTag);

   TGraphAsymmErrors HSSVHETurnOnR014MR450BTag_190;
   HSSVHETurnOnR014MR450BTag_190.BayesDivide(&HSSVHEPassDiJetAve190AndR014MR450BTag, &HSSVHEPassDiJetAve190);
   HSSVHETurnOnR014MR450BTag_190.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 190;SSVHE");
   PsFile.AddPlot(HSSVHETurnOnR014MR450BTag_190, "ape");

   PsFile.AddPlot(HSSVHEPassDiJetAve240);
   PsFile.AddPlot(HSSVHEPassDiJetAve240AndR014MR450BTag);

   TGraphAsymmErrors HSSVHETurnOnR014MR450BTag_240;
   HSSVHETurnOnR014MR450BTag_240.BayesDivide(&HSSVHEPassDiJetAve240AndR014MR450BTag, &HSSVHEPassDiJetAve240);
   HSSVHETurnOnR014MR450BTag_240.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 240;SSVHE");
   PsFile.AddPlot(HSSVHETurnOnR014MR450BTag_240, "ape");

   PsFile.AddPlot(HSSVHEPassDiJetAve300);
   PsFile.AddPlot(HSSVHEPassDiJetAve300AndR014MR450BTag);

   TGraphAsymmErrors HSSVHETurnOnR014MR450BTag_300;
   HSSVHETurnOnR014MR450BTag_300.BayesDivide(&HSSVHEPassDiJetAve300AndR014MR450BTag, &HSSVHEPassDiJetAve300);
   HSSVHETurnOnR014MR450BTag_300.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 300;SSVHE");
   PsFile.AddPlot(HSSVHETurnOnR014MR450BTag_300, "ape");

   TCanvas CSSVHE;
   HSSVHETurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/BTag with respect to different dijet thresholds;SSVHE");
   HSSVHETurnOnR014MR450BTag_150.Draw("ape");
   HSSVHETurnOnR014MR450BTag_190.SetLineColor(2);
   HSSVHETurnOnR014MR450BTag_190.Draw("pe");
   HSSVHETurnOnR014MR450BTag_240.SetLineColor(3);
   HSSVHETurnOnR014MR450BTag_240.Draw("pe");
   HSSVHETurnOnR014MR450BTag_300.SetLineColor(4);
   HSSVHETurnOnR014MR450BTag_300.Draw("pe");
   CSSVHE.SaveAs("SSVHE1.png");
   CSSVHE.SaveAs("SSVHE1.C");
   CSSVHE.SaveAs("SSVHE1.eps");
   PsFile.AddCanvas(CSSVHE);

   PsFile.AddPlot(HSSVHE2PassDiJetAve150);
   PsFile.AddPlot(HSSVHE2PassDiJetAve150AndR014MR450BTag);

   TGraphAsymmErrors HSSVHE2TurnOnR014MR450BTag_150;
   HSSVHE2TurnOnR014MR450BTag_150.BayesDivide(&HSSVHE2PassDiJetAve150AndR014MR450BTag, &HSSVHE2PassDiJetAve150);
   HSSVHE2TurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 150;SSVHE2");
   PsFile.AddPlot(HSSVHE2TurnOnR014MR450BTag_150, "ape");

   PsFile.AddPlot(HSSVHE2PassDiJetAve190);
   PsFile.AddPlot(HSSVHE2PassDiJetAve190AndR014MR450BTag);

   TGraphAsymmErrors HSSVHE2TurnOnR014MR450BTag_190;
   HSSVHE2TurnOnR014MR450BTag_190.BayesDivide(&HSSVHE2PassDiJetAve190AndR014MR450BTag, &HSSVHE2PassDiJetAve190);
   HSSVHE2TurnOnR014MR450BTag_190.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 190;SSVHE2");
   PsFile.AddPlot(HSSVHE2TurnOnR014MR450BTag_190, "ape");

   PsFile.AddPlot(HSSVHE2PassDiJetAve240);
   PsFile.AddPlot(HSSVHE2PassDiJetAve240AndR014MR450BTag);

   TGraphAsymmErrors HSSVHE2TurnOnR014MR450BTag_240;
   HSSVHE2TurnOnR014MR450BTag_240.BayesDivide(&HSSVHE2PassDiJetAve240AndR014MR450BTag, &HSSVHE2PassDiJetAve240);
   HSSVHE2TurnOnR014MR450BTag_240.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 240;SSVHE2");
   PsFile.AddPlot(HSSVHE2TurnOnR014MR450BTag_240, "ape");

   PsFile.AddPlot(HSSVHE2PassDiJetAve300);
   PsFile.AddPlot(HSSVHE2PassDiJetAve300AndR014MR450BTag);

   TGraphAsymmErrors HSSVHE2TurnOnR014MR450BTag_300;
   HSSVHE2TurnOnR014MR450BTag_300.BayesDivide(&HSSVHE2PassDiJetAve300AndR014MR450BTag, &HSSVHE2PassDiJetAve300);
   HSSVHE2TurnOnR014MR450BTag_300.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 300;SSVHE2");
   PsFile.AddPlot(HSSVHE2TurnOnR014MR450BTag_300, "ape");

   TCanvas CSSVHE2;
   HSSVHE2TurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/BTag with respect to different dijet thresholds;SSVHE2");
   HSSVHE2TurnOnR014MR450BTag_150.Draw("ape");
   HSSVHE2TurnOnR014MR450BTag_190.SetLineColor(2);
   HSSVHE2TurnOnR014MR450BTag_190.Draw("pe");
   HSSVHE2TurnOnR014MR450BTag_240.SetLineColor(3);
   HSSVHE2TurnOnR014MR450BTag_240.Draw("pe");
   HSSVHE2TurnOnR014MR450BTag_300.SetLineColor(4);
   HSSVHE2TurnOnR014MR450BTag_300.Draw("pe");
   CSSVHE2.SaveAs("SSVHE2.png");
   CSSVHE2.SaveAs("SSVHE.C");
   CSSVHE2.SaveAs("SSVHE21.eps");
   PsFile.AddCanvas(CSSVHE2);

   PsFile.AddPlot(HSSVHPPassDiJetAve150);
   PsFile.AddPlot(HSSVHPPassDiJetAve150AndR014MR450BTag);

   TGraphAsymmErrors HSSVHPTurnOnR014MR450BTag_150;
   HSSVHPTurnOnR014MR450BTag_150.BayesDivide(&HSSVHPPassDiJetAve150AndR014MR450BTag, &HSSVHPPassDiJetAve150);
   HSSVHPTurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 150;SSVHP");
   PsFile.AddPlot(HSSVHPTurnOnR014MR450BTag_150, "ape");

   PsFile.AddPlot(HSSVHPPassDiJetAve190);
   PsFile.AddPlot(HSSVHPPassDiJetAve190AndR014MR450BTag);

   TGraphAsymmErrors HSSVHPTurnOnR014MR450BTag_190;
   HSSVHPTurnOnR014MR450BTag_190.BayesDivide(&HSSVHPPassDiJetAve190AndR014MR450BTag, &HSSVHPPassDiJetAve190);
   HSSVHPTurnOnR014MR450BTag_190.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 190;SSVHP");
   PsFile.AddPlot(HSSVHPTurnOnR014MR450BTag_190, "ape");

   PsFile.AddPlot(HSSVHPPassDiJetAve240);
   PsFile.AddPlot(HSSVHPPassDiJetAve240AndR014MR450BTag);

   TGraphAsymmErrors HSSVHPTurnOnR014MR450BTag_240;
   HSSVHPTurnOnR014MR450BTag_240.BayesDivide(&HSSVHPPassDiJetAve240AndR014MR450BTag, &HSSVHPPassDiJetAve240);
   HSSVHPTurnOnR014MR450BTag_240.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 240;SSVHP");
   PsFile.AddPlot(HSSVHPTurnOnR014MR450BTag_240, "ape");

   PsFile.AddPlot(HSSVHPPassDiJetAve300);
   PsFile.AddPlot(HSSVHPPassDiJetAve300AndR014MR450BTag);

   TGraphAsymmErrors HSSVHPTurnOnR014MR450BTag_300;
   HSSVHPTurnOnR014MR450BTag_300.BayesDivide(&HSSVHPPassDiJetAve300AndR014MR450BTag, &HSSVHPPassDiJetAve300);
   HSSVHPTurnOnR014MR450BTag_300.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 300;SSVHP");
   PsFile.AddPlot(HSSVHPTurnOnR014MR450BTag_300, "ape");

   TCanvas CSSVHP;
   HSSVHPTurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/BTag with respect to different dijet thresholds;SSVHP");
   HSSVHPTurnOnR014MR450BTag_150.Draw("ape");
   HSSVHPTurnOnR014MR450BTag_190.SetLineColor(2);
   HSSVHPTurnOnR014MR450BTag_190.Draw("pe");
   HSSVHPTurnOnR014MR450BTag_240.SetLineColor(3);
   HSSVHPTurnOnR014MR450BTag_240.Draw("pe");
   HSSVHPTurnOnR014MR450BTag_300.SetLineColor(4);
   HSSVHPTurnOnR014MR450BTag_300.Draw("pe");
   CSSVHP.SaveAs("SSVHP1.png");
   CSSVHP.SaveAs("SSVHP1.C");
   CSSVHP.SaveAs("SSVHP1.eps");
   PsFile.AddCanvas(CSSVHP);

   PsFile.AddPlot(HSSVHP2PassDiJetAve150);
   PsFile.AddPlot(HSSVHP2PassDiJetAve150AndR014MR450BTag);

   TGraphAsymmErrors HSSVHP2TurnOnR014MR450BTag_150;
   HSSVHP2TurnOnR014MR450BTag_150.BayesDivide(&HSSVHP2PassDiJetAve150AndR014MR450BTag, &HSSVHP2PassDiJetAve150);
   HSSVHP2TurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 150;SSVHP2");
   PsFile.AddPlot(HSSVHP2TurnOnR014MR450BTag_150, "ape");

   PsFile.AddPlot(HSSVHP2PassDiJetAve190);
   PsFile.AddPlot(HSSVHP2PassDiJetAve190AndR014MR450BTag);

   TGraphAsymmErrors HSSVHP2TurnOnR014MR450BTag_190;
   HSSVHP2TurnOnR014MR450BTag_190.BayesDivide(&HSSVHP2PassDiJetAve190AndR014MR450BTag, &HSSVHP2PassDiJetAve190);
   HSSVHP2TurnOnR014MR450BTag_190.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 190;SSVHP2");
   PsFile.AddPlot(HSSVHP2TurnOnR014MR450BTag_190, "ape");

   PsFile.AddPlot(HSSVHP2PassDiJetAve240);
   PsFile.AddPlot(HSSVHP2PassDiJetAve240AndR014MR450BTag);

   TGraphAsymmErrors HSSVHP2TurnOnR014MR450BTag_240;
   HSSVHP2TurnOnR014MR450BTag_240.BayesDivide(&HSSVHP2PassDiJetAve240AndR014MR450BTag, &HSSVHP2PassDiJetAve240);
   HSSVHP2TurnOnR014MR450BTag_240.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 240;SSVHP2");
   PsFile.AddPlot(HSSVHP2TurnOnR014MR450BTag_240, "ape");

   PsFile.AddPlot(HSSVHP2PassDiJetAve300);
   PsFile.AddPlot(HSSVHP2PassDiJetAve300AndR014MR450BTag);

   TGraphAsymmErrors HSSVHP2TurnOnR014MR450BTag_300;
   HSSVHP2TurnOnR014MR450BTag_300.BayesDivide(&HSSVHP2PassDiJetAve300AndR014MR450BTag, &HSSVHP2PassDiJetAve300);
   HSSVHP2TurnOnR014MR450BTag_300.SetTitle("Turn-on of R0.14/MR450/Btag with respect to dijet average 300;SSVHP2");
   PsFile.AddPlot(HSSVHP2TurnOnR014MR450BTag_300, "ape");

   TCanvas CSSVHP2;
   HSSVHP2TurnOnR014MR450BTag_150.SetTitle("Turn-on of R0.14/MR450/BTag with respect to different dijet thresholds;SSVHP2");
   HSSVHP2TurnOnR014MR450BTag_150.Draw("ape");
   HSSVHP2TurnOnR014MR450BTag_190.SetLineColor(2);
   HSSVHP2TurnOnR014MR450BTag_190.Draw("pe");
   HSSVHP2TurnOnR014MR450BTag_240.SetLineColor(3);
   HSSVHP2TurnOnR014MR450BTag_240.Draw("pe");
   HSSVHP2TurnOnR014MR450BTag_300.SetLineColor(4);
   HSSVHP2TurnOnR014MR450BTag_300.Draw("pe");
   CSSVHP2.SaveAs("SSVHP2.png");
   CSSVHP2.SaveAs("SSVHP2.C");
   CSSVHP2.SaveAs("SSVHP2.eps");
   PsFile.AddCanvas(CSSVHP2);

   InputFile.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}






