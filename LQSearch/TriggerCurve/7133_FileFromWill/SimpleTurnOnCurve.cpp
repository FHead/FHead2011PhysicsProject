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
   bool PassR014MR150BTag;
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
   Tree->SetBranchAddress("PassR014MR150BTag", &PassR014MR150BTag);
   Tree->SetBranchAddress("MaxTCHE", &MaxTCHE);
   Tree->SetBranchAddress("SecondMaxTCHE", &SecondMaxTCHE);
   Tree->SetBranchAddress("MaxTCHP", &MaxTCHP);
   Tree->SetBranchAddress("SecondMaxTCHP", &SecondMaxTCHP);
   Tree->SetBranchAddress("MaxSSVHE", &MaxSSVHE);
   Tree->SetBranchAddress("SecondMaxSSVHE", &SecondMaxSSVHE);
   Tree->SetBranchAddress("MaxSSVHP", &MaxSSVHP);
   Tree->SetBranchAddress("SecondMaxSSVHP", &SecondMaxSSVHP);

   TH1D HTCHE("HTCHE", "TCHE distribution, R > 0.2, MR > 200;TCHE", 15, 0, 15);
   TH1D HTCHE2("HTCHE2", "TCHE2 distribution, R > 0.2, MR > 200;TCHE2", 15, 0, 15);
   TH1D HTCHP("HTCHP", "TCHP distribution, R > 0.2, MR > 200;TCHP", 15, 0, 15);
   TH1D HTCHP2("HTCHP2", "TCHP2 distribution, R > 0.2, MR > 200;TCHP2", 15, 0, 15);
   TH1D HSSVHE("HSSVHE", "SSVHE distribution, R > 0.2, MR > 200;SSVHE", 15, 0, 15);
   TH1D HSSVHE2("HSSVHE2", "SSVHE2 distribution, R > 0.2, MR > 200;SSVHE2", 15, 0, 15);
   TH1D HSSVHP("HSSVHP", "SSVHP distribution, R > 0.2, MR > 200;SSVHP", 15, 0, 15);
   TH1D HSSVHP2("HSSVHP2", "SSVHP2 distribution, R > 0.2, MR > 200;SSVHP2", 15, 0, 15);
   
   TH1D HTCHEPassR014MR150BTag("HTCHEPassR014MR150BTag",
      "TCHE distribution, pass trigger (R > 0.2, MR > 200);TCHE", 15, 0, 15);
   TH1D HTCHE2PassR014MR150BTag("HTCHE2PassR014MR150BTag",
      "TCHE2 distribution, pass trigger (R > 0.2, MR > 200);TCHE2", 15, 0, 15);
   TH1D HTCHPPassR014MR150BTag("HTCHPPassR014MR150BTag",
      "TCHP distribution, pass trigger (R > 0.2, MR > 200);TCHP", 15, 0, 15);
   TH1D HTCHP2PassR014MR150BTag("HTCHP2PassR014MR150BTag",
      "TCHP2 distribution, pass trigger (R > 0.2, MR > 200);TCHP2", 15, 0, 15);
   TH1D HSSVHEPassR014MR150BTag("HSSVHEPassR014MR150BTag",
      "SSVHE distribution, pass trigger (R > 0.2, MR > 200);SSVHE", 15, 0, 15);
   TH1D HSSVHE2PassR014MR150BTag("HSSVHE2PassR014MR150BTag",
      "SSVHE2 distribution, pass trigger (R > 0.2, MR > 200);SSVHE2", 15, 0, 15);
   TH1D HSSVHPPassR014MR150BTag("HSSVHPPassR014MR150BTag",
      "SSVHP distribution, pass trigger (R > 0.2, MR > 200);SSVHP", 15, 0, 15);
   TH1D HSSVHP2PassR014MR150BTag("HSSVHP2PassR014MR150BTag",
      "SSVHP2 distribution, pass trigger (R > 0.2, MR > 200);SSVHP2", 15, 0, 15);
   
   PsFileHelper PsFile("SimpleTurnOnCurve.ps");
   PsFile.AddTextPage("Simple turn-on curve from HT dataset on b-tagging");

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      if(R > 0.20 && MR > 200)
      {
         HTCHE.Fill(MaxTCHE);
         HTCHE2.Fill(SecondMaxTCHE);
         HTCHP.Fill(MaxTCHP);
         HTCHP2.Fill(SecondMaxTCHP);
         HSSVHE.Fill(MaxSSVHE);
         HSSVHE2.Fill(SecondMaxSSVHE);
         HSSVHP.Fill(MaxSSVHP);
         HSSVHP2.Fill(SecondMaxSSVHP);
      }

      if(PassR014MR150BTag == true && R > 0.20 && MR > 500)
      {
         HTCHEPassR014MR150BTag.Fill(MaxTCHE);
         HTCHE2PassR014MR150BTag.Fill(SecondMaxTCHE);
         HTCHPPassR014MR150BTag.Fill(MaxTCHP);
         HTCHP2PassR014MR150BTag.Fill(SecondMaxTCHP);
         HSSVHEPassR014MR150BTag.Fill(MaxSSVHE);
         HSSVHE2PassR014MR150BTag.Fill(SecondMaxSSVHE);
         HSSVHPPassR014MR150BTag.Fill(MaxSSVHP);
         HSSVHP2PassR014MR150BTag.Fill(SecondMaxSSVHP);
      }
   }

   PsFile.AddPlot(HTCHE);
   PsFile.AddPlot(HTCHEPassR014MR150BTag);

   TGraphAsymmErrors HTCHETurnOn;
   HTCHETurnOn.BayesDivide(&HTCHE, &HTCHEPassR014MR150BTag);
   HTCHETurnOn.SetTitle("Turn-on of R0.14/MR450/Btag (B-Tagging part);TCHE");
   PsFile.AddPlot(HTCHETurnOn, "ape");
   
   InputFile.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}






