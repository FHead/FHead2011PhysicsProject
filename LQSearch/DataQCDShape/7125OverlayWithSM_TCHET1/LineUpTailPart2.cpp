#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main();
void FixUpHistogram(TH1D &H, int Color);

int main()
{
   SetStyle();

   TChain InputTree("MRTree", "MRTree");
   InputTree.AddFile("JetReducedTree.root");

   double MR, R, MRStar, RStar, GammaMRStar, BetaR;
   bool PassDiJetAve15U, PassDiJetAve30U, PassDiJetAve50U, PassDiJetAve70U,
      PassDiJetAve100U, PassDiJetAve140U, PassDiJetAve180U, PassDiJetAve300U;
   bool PassDiJetAve30, PassDiJetAve60, PassDiJetAve80, PassDiJetAve110,
      PassDiJetAve150, PassDiJetAve190, PassDiJetAve240, PassDiJetAve300, PassDiJetAve370;

   InputTree.SetBranchAddress("MR", &MR);
   InputTree.SetBranchAddress("R", &R);
   InputTree.SetBranchAddress("MRStar", &MRStar);
   InputTree.SetBranchAddress("RStar", &RStar);
   InputTree.SetBranchAddress("GammaMRStar", &GammaMRStar);
   InputTree.SetBranchAddress("BetaR", &BetaR);
   InputTree.SetBranchAddress("PassDiJetAve30", &PassDiJetAve30);
   InputTree.SetBranchAddress("PassDiJetAve60", &PassDiJetAve60);
   InputTree.SetBranchAddress("PassDiJetAve80", &PassDiJetAve80);
   InputTree.SetBranchAddress("PassDiJetAve110", &PassDiJetAve110);
   InputTree.SetBranchAddress("PassDiJetAve150", &PassDiJetAve150);
   InputTree.SetBranchAddress("PassDiJetAve190", &PassDiJetAve190);
   InputTree.SetBranchAddress("PassDiJetAve240", &PassDiJetAve240);
   InputTree.SetBranchAddress("PassDiJetAve300", &PassDiJetAve300);
   InputTree.SetBranchAddress("PassDiJetAve370", &PassDiJetAve370);
   InputTree.SetBranchAddress("PassDiJetAve15U", &PassDiJetAve15U);
   InputTree.SetBranchAddress("PassDiJetAve30U", &PassDiJetAve30U);
   InputTree.SetBranchAddress("PassDiJetAve50U", &PassDiJetAve50U);
   InputTree.SetBranchAddress("PassDiJetAve70U", &PassDiJetAve70U);
   InputTree.SetBranchAddress("PassDiJetAve100U", &PassDiJetAve100U);
   InputTree.SetBranchAddress("PassDiJetAve140U", &PassDiJetAve140U);
   InputTree.SetBranchAddress("PassDiJetAve180U", &PassDiJetAve180U);
   InputTree.SetBranchAddress("PassDiJetAve300U", &PassDiJetAve300U);

   TH1D HGammaMRStar_RStar02_DiJetAve30("HGammaMRStar_RStar02_DiJetAve30",
      "MRStar (RStar > 0.2), passing dijet ave. 30;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve60("HGammaMRStar_RStar02_DiJetAve60",
      "MRStar (RStar > 0.2), passing dijet ave. 60;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve80("HGammaMRStar_RStar02_DiJetAve80",
      "MRStar (RStar > 0.2), passing dijet ave. 80;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve110("HGammaMRStar_RStar02_DiJetAve110",
      "MRStar (RStar > 0.2), passing dijet ave. 110;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve150("HGammaMRStar_RStar02_DiJetAve150",
      "MRStar (RStar > 0.2), passing dijet ave. 150;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve190("HGammaMRStar_RStar02_DiJetAve190",
      "MRStar (RStar > 0.2), passing dijet ave. 190;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve240("HGammaMRStar_RStar02_DiJetAve240",
      "MRStar (RStar > 0.2), passing dijet ave. 240;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve300("HGammaMRStar_RStar02_DiJetAve300",
      "MRStar (RStar > 0.2), passing dijet ave. 300;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve370("HGammaMRStar_RStar02_DiJetAve370",
      "MRStar (RStar > 0.2), passing dijet ave. 370;GammaMRStar", 40, 0, 2000);
   
   TH1D HGammaMRStar_RStar03_DiJetAve30("HGammaMRStar_RStar03_DiJetAve30",
      "MRStar (RStar > 0.3), passing dijet ave. 30;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve60("HGammaMRStar_RStar03_DiJetAve60",
      "MRStar (RStar > 0.3), passing dijet ave. 60;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve80("HGammaMRStar_RStar03_DiJetAve80",
      "MRStar (RStar > 0.3), passing dijet ave. 80;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve110("HGammaMRStar_RStar03_DiJetAve110",
      "MRStar (RStar > 0.3), passing dijet ave. 110;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve150("HGammaMRStar_RStar03_DiJetAve150",
      "MRStar (RStar > 0.3), passing dijet ave. 150;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve190("HGammaMRStar_RStar03_DiJetAve190",
      "MRStar (RStar > 0.3), passing dijet ave. 190;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve240("HGammaMRStar_RStar03_DiJetAve240",
      "MRStar (RStar > 0.3), passing dijet ave. 240;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve300("HGammaMRStar_RStar03_DiJetAve300",
      "MRStar (RStar > 0.3), passing dijet ave. 300;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve370("HGammaMRStar_RStar03_DiJetAve370",
      "MRStar (RStar > 0.3), passing dijet ave. 370;GammaMRStar", 40, 0, 2000);
   
   TH1D HGammaMRStar_RStar04_DiJetAve30("HGammaMRStar_RStar04_DiJetAve30",
      "MRStar (RStar > 0.4), passing dijet ave. 30;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve60("HGammaMRStar_RStar04_DiJetAve60",
      "MRStar (RStar > 0.4), passing dijet ave. 60;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve80("HGammaMRStar_RStar04_DiJetAve80",
      "MRStar (RStar > 0.4), passing dijet ave. 80;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve110("HGammaMRStar_RStar04_DiJetAve110",
      "MRStar (RStar > 0.4), passing dijet ave. 110;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve150("HGammaMRStar_RStar04_DiJetAve150",
      "MRStar (RStar > 0.4), passing dijet ave. 150;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve190("HGammaMRStar_RStar04_DiJetAve190",
      "MRStar (RStar > 0.4), passing dijet ave. 190;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve240("HGammaMRStar_RStar04_DiJetAve240",
      "MRStar (RStar > 0.4), passing dijet ave. 240;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve300("HGammaMRStar_RStar04_DiJetAve300",
      "MRStar (RStar > 0.4), passing dijet ave. 300;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve370("HGammaMRStar_RStar04_DiJetAve370",
      "MRStar (RStar > 0.4), passing dijet ave. 370;GammaMRStar", 40, 0, 2000);
   
   TH1D HGammaMRStar_RStar05_DiJetAve30("HGammaMRStar_RStar05_DiJetAve30",
      "MRStar (RStar > 0.5), passing dijet ave. 30;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve60("HGammaMRStar_RStar05_DiJetAve60",
      "MRStar (RStar > 0.5), passing dijet ave. 60;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve80("HGammaMRStar_RStar05_DiJetAve80",
      "MRStar (RStar > 0.5), passing dijet ave. 80;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve110("HGammaMRStar_RStar05_DiJetAve110",
      "MRStar (RStar > 0.5), passing dijet ave. 110;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve150("HGammaMRStar_RStar05_DiJetAve150",
      "MRStar (RStar > 0.5), passing dijet ave. 150;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve190("HGammaMRStar_RStar05_DiJetAve190",
      "MRStar (RStar > 0.5), passing dijet ave. 190;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve240("HGammaMRStar_RStar05_DiJetAve240",
      "MRStar (RStar > 0.5), passing dijet ave. 240;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve300("HGammaMRStar_RStar05_DiJetAve300",
      "MRStar (RStar > 0.5), passing dijet ave. 300;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve370("HGammaMRStar_RStar05_DiJetAve370",
      "MRStar (RStar > 0.5), passing dijet ave. 370;GammaMRStar", 40, 0, 2000);
   
   FixUpHistogram(HGammaMRStar_RStar02_DiJetAve30, 1);
   FixUpHistogram(HGammaMRStar_RStar02_DiJetAve60, 2);
   FixUpHistogram(HGammaMRStar_RStar02_DiJetAve80, 3);
   FixUpHistogram(HGammaMRStar_RStar02_DiJetAve110, 4);
   FixUpHistogram(HGammaMRStar_RStar02_DiJetAve150, 5);
   FixUpHistogram(HGammaMRStar_RStar02_DiJetAve190, 6);
   FixUpHistogram(HGammaMRStar_RStar02_DiJetAve240, 7);
   FixUpHistogram(HGammaMRStar_RStar02_DiJetAve300, 8);
   FixUpHistogram(HGammaMRStar_RStar02_DiJetAve370, 9);

   FixUpHistogram(HGammaMRStar_RStar03_DiJetAve30, 1);
   FixUpHistogram(HGammaMRStar_RStar03_DiJetAve60, 2);
   FixUpHistogram(HGammaMRStar_RStar03_DiJetAve80, 3);
   FixUpHistogram(HGammaMRStar_RStar03_DiJetAve110, 4);
   FixUpHistogram(HGammaMRStar_RStar03_DiJetAve150, 5);
   FixUpHistogram(HGammaMRStar_RStar03_DiJetAve190, 6);
   FixUpHistogram(HGammaMRStar_RStar03_DiJetAve240, 7);
   FixUpHistogram(HGammaMRStar_RStar03_DiJetAve300, 8);
   FixUpHistogram(HGammaMRStar_RStar03_DiJetAve370, 9);

   FixUpHistogram(HGammaMRStar_RStar04_DiJetAve30, 1);
   FixUpHistogram(HGammaMRStar_RStar04_DiJetAve60, 2);
   FixUpHistogram(HGammaMRStar_RStar04_DiJetAve80, 3);
   FixUpHistogram(HGammaMRStar_RStar04_DiJetAve110, 4);
   FixUpHistogram(HGammaMRStar_RStar04_DiJetAve150, 5);
   FixUpHistogram(HGammaMRStar_RStar04_DiJetAve190, 6);
   FixUpHistogram(HGammaMRStar_RStar04_DiJetAve240, 7);
   FixUpHistogram(HGammaMRStar_RStar04_DiJetAve300, 8);
   FixUpHistogram(HGammaMRStar_RStar04_DiJetAve370, 9);

   FixUpHistogram(HGammaMRStar_RStar05_DiJetAve30, 1);
   FixUpHistogram(HGammaMRStar_RStar05_DiJetAve60, 2);
   FixUpHistogram(HGammaMRStar_RStar05_DiJetAve80, 3);
   FixUpHistogram(HGammaMRStar_RStar05_DiJetAve110, 4);
   FixUpHistogram(HGammaMRStar_RStar05_DiJetAve150, 5);
   FixUpHistogram(HGammaMRStar_RStar05_DiJetAve190, 6);
   FixUpHistogram(HGammaMRStar_RStar05_DiJetAve240, 7);
   FixUpHistogram(HGammaMRStar_RStar05_DiJetAve300, 8);
   FixUpHistogram(HGammaMRStar_RStar05_DiJetAve370, 9);

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      InputTree.GetEntry(iEntry);

      if(RStar > 0.75)
         continue;

      if(RStar > 0.2 && PassDiJetAve30 == true)
         HGammaMRStar_RStar02_DiJetAve30.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve60 == true)
         HGammaMRStar_RStar02_DiJetAve60.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve80 == true)
         HGammaMRStar_RStar02_DiJetAve80.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve110 == true)
         HGammaMRStar_RStar02_DiJetAve110.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve150 == true)
         HGammaMRStar_RStar02_DiJetAve150.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve190 == true)
         HGammaMRStar_RStar02_DiJetAve190.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve240 == true)
         HGammaMRStar_RStar02_DiJetAve240.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve300 == true)
         HGammaMRStar_RStar02_DiJetAve300.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve370 == true)
         HGammaMRStar_RStar02_DiJetAve370.Fill(GammaMRStar);
      
      if(RStar > 0.3 && PassDiJetAve30 == true)
         HGammaMRStar_RStar03_DiJetAve30.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve60 == true)
         HGammaMRStar_RStar03_DiJetAve60.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve80 == true)
         HGammaMRStar_RStar03_DiJetAve80.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve110 == true)
         HGammaMRStar_RStar03_DiJetAve110.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve150 == true)
         HGammaMRStar_RStar03_DiJetAve150.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve190 == true)
         HGammaMRStar_RStar03_DiJetAve190.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve240 == true)
         HGammaMRStar_RStar03_DiJetAve240.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve300 == true)
         HGammaMRStar_RStar03_DiJetAve300.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve370 == true)
         HGammaMRStar_RStar03_DiJetAve370.Fill(GammaMRStar);
      
      if(RStar > 0.4 && PassDiJetAve30 == true)
         HGammaMRStar_RStar04_DiJetAve30.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve60 == true)
         HGammaMRStar_RStar04_DiJetAve60.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve80 == true)
         HGammaMRStar_RStar04_DiJetAve80.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve110 == true)
         HGammaMRStar_RStar04_DiJetAve110.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve150 == true)
         HGammaMRStar_RStar04_DiJetAve150.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve190 == true)
         HGammaMRStar_RStar04_DiJetAve190.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve240 == true)
         HGammaMRStar_RStar04_DiJetAve240.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve300 == true)
         HGammaMRStar_RStar04_DiJetAve300.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve370 == true)
         HGammaMRStar_RStar04_DiJetAve370.Fill(GammaMRStar);
      
      if(RStar > 0.5 && PassDiJetAve30 == true)
         HGammaMRStar_RStar05_DiJetAve30.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve60 == true)
         HGammaMRStar_RStar05_DiJetAve60.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve80 == true)
         HGammaMRStar_RStar05_DiJetAve80.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve110 == true)
         HGammaMRStar_RStar05_DiJetAve110.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve150 == true)
         HGammaMRStar_RStar05_DiJetAve150.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve190 == true)
         HGammaMRStar_RStar05_DiJetAve190.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve240 == true)
         HGammaMRStar_RStar05_DiJetAve240.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve300 == true)
         HGammaMRStar_RStar05_DiJetAve300.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve370 == true)
         HGammaMRStar_RStar05_DiJetAve370.Fill(GammaMRStar);
   }

   double Scale370 = 1;
   double Scale300 = 1;
   double Scale240 = 1;
   double Scale190 = 1;
   double Scale150 = 1;
   double Scale110 = 1;
   double Scale80 = 1;
   double Scale60 = 1;
   double Scale30 = 1;

   int BinAt850 = HGammaMRStar_RStar02_DiJetAve300.FindBin(850);
   int BinAt700 = HGammaMRStar_RStar02_DiJetAve300.FindBin(700);
   int BinAt600 = HGammaMRStar_RStar02_DiJetAve300.FindBin(600);
   int BinAt500 = HGammaMRStar_RStar02_DiJetAve300.FindBin(500);
   int BinAt400 = HGammaMRStar_RStar02_DiJetAve300.FindBin(400);
   int BinAt350 = HGammaMRStar_RStar02_DiJetAve300.FindBin(350);
   int BinAt300 = HGammaMRStar_RStar02_DiJetAve300.FindBin(300);
   int BinAt250 = HGammaMRStar_RStar02_DiJetAve300.FindBin(250);

   Scale240 = HGammaMRStar_RStar02_DiJetAve300.Integral(BinAt850, 9999)
      / HGammaMRStar_RStar02_DiJetAve240.Integral(BinAt850, 9999) * Scale300;
   Scale190 = HGammaMRStar_RStar02_DiJetAve240.Integral(BinAt700, 9999)
      / HGammaMRStar_RStar02_DiJetAve190.Integral(BinAt700, 9999) * Scale240;
   Scale150 = HGammaMRStar_RStar02_DiJetAve190.Integral(BinAt600, 9999)
      / HGammaMRStar_RStar02_DiJetAve150.Integral(BinAt600, 9999) * Scale190;
   Scale110 = HGammaMRStar_RStar02_DiJetAve150.Integral(BinAt500, 9999)
      / HGammaMRStar_RStar02_DiJetAve110.Integral(BinAt500, 9999) * Scale150;
   Scale80 = HGammaMRStar_RStar02_DiJetAve110.Integral(BinAt350, 9999)
      / HGammaMRStar_RStar02_DiJetAve80.Integral(BinAt350, 9999) * Scale110;
   Scale60 = HGammaMRStar_RStar02_DiJetAve80.Integral(BinAt300, 9999)
      / HGammaMRStar_RStar02_DiJetAve60.Integral(BinAt300, 9999) * Scale80;
   Scale30 = HGammaMRStar_RStar02_DiJetAve60.Integral(BinAt250, 9999)
      / HGammaMRStar_RStar02_DiJetAve30.Integral(BinAt250, 9999) * Scale60;

   TFile FTTbar("MC/TTbar.root");
   TFile FW("MC/W.root");
   TFile FWW("MC/WW.root");
   TFile FWZ("MC/WZ.root");
   TFile FZZ("MC/ZZ.root");
   TFile FGammaJet("MC/GammaVJet.root");
   TFile FDY10("MC/DY10.root");
   TFile FDY50("MC/DY50.root");

   TH1D *HTTbar_GammaMRStar_RStar02 = (TH1D *)FTTbar.Get("HPFJetGammaMRStar_RStar02");
   TH1D *HTTbar_GammaMRStar_RStar03 = (TH1D *)FTTbar.Get("HPFJetGammaMRStar_RStar03");
   TH1D *HTTbar_GammaMRStar_RStar04 = (TH1D *)FTTbar.Get("HPFJetGammaMRStar_RStar04");
   TH1D *HTTbar_GammaMRStar_RStar05 = (TH1D *)FTTbar.Get("HPFJetGammaMRStar_RStar05");
   HTTbar_GammaMRStar_RStar02->SetLineColor(kRed + 2);
   HTTbar_GammaMRStar_RStar03->SetLineColor(kRed + 2);
   HTTbar_GammaMRStar_RStar04->SetLineColor(kRed + 2);
   HTTbar_GammaMRStar_RStar05->SetLineColor(kRed + 2);
   HTTbar_GammaMRStar_RStar02->SetFillColor(kRed + 2);
   HTTbar_GammaMRStar_RStar03->SetFillColor(kRed + 2);
   HTTbar_GammaMRStar_RStar04->SetFillColor(kRed + 2);
   HTTbar_GammaMRStar_RStar05->SetFillColor(kRed + 2);

   TH1D *HW_GammaMRStar_RStar02 = (TH1D *)FW.Get("HPFJetGammaMRStar_RStar02");
   TH1D *HW_GammaMRStar_RStar03 = (TH1D *)FW.Get("HPFJetGammaMRStar_RStar03");
   TH1D *HW_GammaMRStar_RStar04 = (TH1D *)FW.Get("HPFJetGammaMRStar_RStar04");
   TH1D *HW_GammaMRStar_RStar05 = (TH1D *)FW.Get("HPFJetGammaMRStar_RStar05");
   HW_GammaMRStar_RStar02->Add(HTTbar_GammaMRStar_RStar02);
   HW_GammaMRStar_RStar03->Add(HTTbar_GammaMRStar_RStar03);
   HW_GammaMRStar_RStar04->Add(HTTbar_GammaMRStar_RStar04);
   HW_GammaMRStar_RStar05->Add(HTTbar_GammaMRStar_RStar05);
   HW_GammaMRStar_RStar02->SetLineColor(kGreen + 3);
   HW_GammaMRStar_RStar03->SetLineColor(kGreen + 3);
   HW_GammaMRStar_RStar04->SetLineColor(kGreen + 3);
   HW_GammaMRStar_RStar05->SetLineColor(kGreen + 3);
   HW_GammaMRStar_RStar02->SetFillColor(kGreen + 3);
   HW_GammaMRStar_RStar03->SetFillColor(kGreen + 3);
   HW_GammaMRStar_RStar04->SetFillColor(kGreen + 3);
   HW_GammaMRStar_RStar05->SetFillColor(kGreen + 3);

   TH1D *HWW_GammaMRStar_RStar02 = (TH1D *)FWW.Get("HPFJetGammaMRStar_RStar02");
   TH1D *HWW_GammaMRStar_RStar03 = (TH1D *)FWW.Get("HPFJetGammaMRStar_RStar03");
   TH1D *HWW_GammaMRStar_RStar04 = (TH1D *)FWW.Get("HPFJetGammaMRStar_RStar04");
   TH1D *HWW_GammaMRStar_RStar05 = (TH1D *)FWW.Get("HPFJetGammaMRStar_RStar05");
   HWW_GammaMRStar_RStar02->Add(HW_GammaMRStar_RStar02);
   HWW_GammaMRStar_RStar03->Add(HW_GammaMRStar_RStar03);
   HWW_GammaMRStar_RStar04->Add(HW_GammaMRStar_RStar04);
   HWW_GammaMRStar_RStar05->Add(HW_GammaMRStar_RStar05);

   TH1D *HWZ_GammaMRStar_RStar02 = (TH1D *)FWZ.Get("HPFJetGammaMRStar_RStar02");
   TH1D *HWZ_GammaMRStar_RStar03 = (TH1D *)FWZ.Get("HPFJetGammaMRStar_RStar03");
   TH1D *HWZ_GammaMRStar_RStar04 = (TH1D *)FWZ.Get("HPFJetGammaMRStar_RStar04");
   TH1D *HWZ_GammaMRStar_RStar05 = (TH1D *)FWZ.Get("HPFJetGammaMRStar_RStar05");
   HWZ_GammaMRStar_RStar02->Add(HWW_GammaMRStar_RStar02);
   HWZ_GammaMRStar_RStar03->Add(HWW_GammaMRStar_RStar03);
   HWZ_GammaMRStar_RStar04->Add(HWW_GammaMRStar_RStar04);
   HWZ_GammaMRStar_RStar05->Add(HWW_GammaMRStar_RStar05);

   TH1D *HZZ_GammaMRStar_RStar02 = (TH1D *)FZZ.Get("HPFJetGammaMRStar_RStar02");
   TH1D *HZZ_GammaMRStar_RStar03 = (TH1D *)FZZ.Get("HPFJetGammaMRStar_RStar03");
   TH1D *HZZ_GammaMRStar_RStar04 = (TH1D *)FZZ.Get("HPFJetGammaMRStar_RStar04");
   TH1D *HZZ_GammaMRStar_RStar05 = (TH1D *)FZZ.Get("HPFJetGammaMRStar_RStar05");
   HZZ_GammaMRStar_RStar02->Add(HWZ_GammaMRStar_RStar02);
   HZZ_GammaMRStar_RStar03->Add(HWZ_GammaMRStar_RStar03);
   HZZ_GammaMRStar_RStar04->Add(HWZ_GammaMRStar_RStar04);
   HZZ_GammaMRStar_RStar05->Add(HWZ_GammaMRStar_RStar05);
   HZZ_GammaMRStar_RStar02->SetLineColor(6);
   HZZ_GammaMRStar_RStar03->SetLineColor(6);
   HZZ_GammaMRStar_RStar04->SetLineColor(6);
   HZZ_GammaMRStar_RStar05->SetLineColor(6);
   HZZ_GammaMRStar_RStar02->SetFillColor(6);
   HZZ_GammaMRStar_RStar03->SetFillColor(6);
   HZZ_GammaMRStar_RStar04->SetFillColor(6);
   HZZ_GammaMRStar_RStar05->SetFillColor(6);

   TH1D *HGammaJet_GammaMRStar_RStar02 = (TH1D *)FGammaJet.Get("HPFJetGammaMRStar_RStar02");
   TH1D *HGammaJet_GammaMRStar_RStar03 = (TH1D *)FGammaJet.Get("HPFJetGammaMRStar_RStar03");
   TH1D *HGammaJet_GammaMRStar_RStar04 = (TH1D *)FGammaJet.Get("HPFJetGammaMRStar_RStar04");
   TH1D *HGammaJet_GammaMRStar_RStar05 = (TH1D *)FGammaJet.Get("HPFJetGammaMRStar_RStar05");
   HGammaJet_GammaMRStar_RStar02->Add(HZZ_GammaMRStar_RStar02);
   HGammaJet_GammaMRStar_RStar03->Add(HZZ_GammaMRStar_RStar03);
   HGammaJet_GammaMRStar_RStar04->Add(HZZ_GammaMRStar_RStar04);
   HGammaJet_GammaMRStar_RStar05->Add(HZZ_GammaMRStar_RStar05);
   HGammaJet_GammaMRStar_RStar02->SetLineColor(7);
   HGammaJet_GammaMRStar_RStar03->SetLineColor(7);
   HGammaJet_GammaMRStar_RStar04->SetLineColor(7);
   HGammaJet_GammaMRStar_RStar05->SetLineColor(7);
   HGammaJet_GammaMRStar_RStar02->SetFillColor(7);
   HGammaJet_GammaMRStar_RStar03->SetFillColor(7);
   HGammaJet_GammaMRStar_RStar04->SetFillColor(7);
   HGammaJet_GammaMRStar_RStar05->SetFillColor(7);

   TH1D *HDY10_GammaMRStar_RStar02 = (TH1D *)FDY10.Get("HPFJetGammaMRStar_RStar02");
   TH1D *HDY10_GammaMRStar_RStar03 = (TH1D *)FDY10.Get("HPFJetGammaMRStar_RStar03");
   TH1D *HDY10_GammaMRStar_RStar04 = (TH1D *)FDY10.Get("HPFJetGammaMRStar_RStar04");
   TH1D *HDY10_GammaMRStar_RStar05 = (TH1D *)FDY10.Get("HPFJetGammaMRStar_RStar05");
   HDY10_GammaMRStar_RStar02->Add(HGammaJet_GammaMRStar_RStar02);
   HDY10_GammaMRStar_RStar03->Add(HGammaJet_GammaMRStar_RStar03);
   HDY10_GammaMRStar_RStar04->Add(HGammaJet_GammaMRStar_RStar04);
   HDY10_GammaMRStar_RStar05->Add(HGammaJet_GammaMRStar_RStar05);

   TH1D *HDY50_GammaMRStar_RStar02 = (TH1D *)FDY50.Get("HPFJetGammaMRStar_RStar02");
   TH1D *HDY50_GammaMRStar_RStar03 = (TH1D *)FDY50.Get("HPFJetGammaMRStar_RStar03");
   TH1D *HDY50_GammaMRStar_RStar04 = (TH1D *)FDY50.Get("HPFJetGammaMRStar_RStar04");
   TH1D *HDY50_GammaMRStar_RStar05 = (TH1D *)FDY50.Get("HPFJetGammaMRStar_RStar05");
   HDY50_GammaMRStar_RStar02->Add(HDY10_GammaMRStar_RStar02);
   HDY50_GammaMRStar_RStar03->Add(HDY10_GammaMRStar_RStar03);
   HDY50_GammaMRStar_RStar04->Add(HDY10_GammaMRStar_RStar04);
   HDY50_GammaMRStar_RStar05->Add(HDY10_GammaMRStar_RStar05);
   HDY50_GammaMRStar_RStar02->SetLineColor(9);
   HDY50_GammaMRStar_RStar03->SetLineColor(9);
   HDY50_GammaMRStar_RStar04->SetLineColor(9);
   HDY50_GammaMRStar_RStar05->SetLineColor(9);
   HDY50_GammaMRStar_RStar02->SetFillColor(9);
   HDY50_GammaMRStar_RStar03->SetFillColor(9);
   HDY50_GammaMRStar_RStar04->SetFillColor(9);
   HDY50_GammaMRStar_RStar05->SetFillColor(9);

   PsFileHelper PsFile("Plots.ps");
   PsFile.AddTextPage("Attempt to line-up data to reconstruct QCD shape!");

   PsFile.AddTextPage("IndividualPlots");

   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve30, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve60, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve80, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve110, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve150, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve190, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve240, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve300, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve370, "", true);

   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve30, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve60, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve80, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve110, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve150, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve190, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve240, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve300, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve370, "", true);

   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve30, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve60, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve80, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve110, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve150, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve190, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve240, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve300, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve370, "", true);

   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve30, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve60, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve80, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve110, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve150, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve190, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve240, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve300, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve370, "", true);

   HGammaMRStar_RStar02_DiJetAve30.Scale(Scale30);
   HGammaMRStar_RStar02_DiJetAve60.Scale(Scale60);
   HGammaMRStar_RStar02_DiJetAve80.Scale(Scale80);
   HGammaMRStar_RStar02_DiJetAve110.Scale(Scale110);
   HGammaMRStar_RStar02_DiJetAve150.Scale(Scale150);
   HGammaMRStar_RStar02_DiJetAve190.Scale(Scale190);
   HGammaMRStar_RStar02_DiJetAve240.Scale(Scale240);
   HGammaMRStar_RStar02_DiJetAve300.Scale(Scale300);
   HGammaMRStar_RStar02_DiJetAve370.Scale(Scale370);

   HGammaMRStar_RStar03_DiJetAve30.Scale(Scale30);
   HGammaMRStar_RStar03_DiJetAve60.Scale(Scale60);
   HGammaMRStar_RStar03_DiJetAve80.Scale(Scale80);
   HGammaMRStar_RStar03_DiJetAve110.Scale(Scale110);
   HGammaMRStar_RStar03_DiJetAve150.Scale(Scale150);
   HGammaMRStar_RStar03_DiJetAve190.Scale(Scale190);
   HGammaMRStar_RStar03_DiJetAve240.Scale(Scale240);
   HGammaMRStar_RStar03_DiJetAve300.Scale(Scale300);
   HGammaMRStar_RStar03_DiJetAve370.Scale(Scale370);

   HGammaMRStar_RStar04_DiJetAve30.Scale(Scale30);
   HGammaMRStar_RStar04_DiJetAve60.Scale(Scale60);
   HGammaMRStar_RStar04_DiJetAve80.Scale(Scale80);
   HGammaMRStar_RStar04_DiJetAve110.Scale(Scale110);
   HGammaMRStar_RStar04_DiJetAve150.Scale(Scale150);
   HGammaMRStar_RStar04_DiJetAve190.Scale(Scale190);
   HGammaMRStar_RStar04_DiJetAve240.Scale(Scale240);
   HGammaMRStar_RStar04_DiJetAve300.Scale(Scale300);
   HGammaMRStar_RStar04_DiJetAve370.Scale(Scale370);

   HGammaMRStar_RStar05_DiJetAve30.Scale(Scale30);
   HGammaMRStar_RStar05_DiJetAve60.Scale(Scale60);
   HGammaMRStar_RStar05_DiJetAve80.Scale(Scale80);
   HGammaMRStar_RStar05_DiJetAve110.Scale(Scale110);
   HGammaMRStar_RStar05_DiJetAve150.Scale(Scale150);
   HGammaMRStar_RStar05_DiJetAve190.Scale(Scale190);
   HGammaMRStar_RStar05_DiJetAve240.Scale(Scale240);
   HGammaMRStar_RStar05_DiJetAve300.Scale(Scale300);
   HGammaMRStar_RStar05_DiJetAve370.Scale(Scale370);

   TLatex l;
   l.SetTextAlign(12);
   l.SetTextSize(0.035);
   l.SetNDC();

   double L = 173.6177725;
   int iL;
   int iL_dec;

   string unit;

   if(L < 1.)
   {
      iL = int(1000. * L);
      iL_dec = 0;
      unit = "nb^{-1}";
   }
   else if(L > 1000.)
   {
      iL = int(L/1000.);
      iL_dec = int(L) % 1000;
      unit = "fb^{-1}";
   }
   else
   {
      iL = int(L);
      iL_dec = int(L * 10) % 10;
      unit = "pb^{-1}";
   }

   char *s_latex = new char[100];
   sprintf(s_latex," #splitline{CMS Preliminary 2011}{#sqrt{s}=7 TeV}");

   char *s_lumi = new char[100];
   if(iL_dec == 0)
      sprintf(s_lumi," #int L dt = %d %s", iL, unit.c_str());
   else
      sprintf(s_lumi," #int L dt = %d.%d %s", iL, iL_dec, unit.c_str());

   PsFile.AddTextPage("Overlaid + scaled plots");

   vector<string> Explanations;
   Explanations.push_back("Take Jet dataset, inclusive, check R* and MR*** requiring different triggers");
   Explanations.push_back("Triggers looked at: HLT_DiJetAve_XXX, where XXX = ");
   Explanations.push_back("      30, 60, 80, 110, 150, 190, 240, 300, 370");
   Explanations.push_back("Require basic hcal noise filter and PF jet ID");
   Explanations.push_back("Stuff reconstructed with PF jet (AK5PFPUcorrJet in vecbos) and PF MET");
   Explanations.push_back("Jets selected within eta range 2.4, jet PT 30");
   Explanations.push_back("No two-jet-above-60-GeV yet, and no b-tagging for this first look");
   Explanations.push_back("");
   Explanations.push_back("Scaling factor computed using tail in RStar > 0.2 distribution");
   Explanations.push_back("Use the same scaling factor for other curves with the same trigger");
   Explanations.push_back("");
   Explanations.push_back("(ps. it's the May10ReReco)");
   PsFile.AddTextPage(Explanations);

   TCanvas C1;
   HGammaMRStar_RStar02_DiJetAve30.SetTitle("QCD shape as reconstructed from different triggers (RStar > 0.2)");
   HGammaMRStar_RStar02_DiJetAve30.GetYaxis()->SetTitle("Count / bin");
   HGammaMRStar_RStar02_DiJetAve30.SetMinimum(0.1);
   HGammaMRStar_RStar02_DiJetAve30.Draw("point error");
   HGammaMRStar_RStar02_DiJetAve60.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve80.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve110.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve150.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve190.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve240.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve300.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve370.Draw("point error same");
   HDY50_GammaMRStar_RStar02->Draw("same");
   HGammaJet_GammaMRStar_RStar02->Draw("same");
   HZZ_GammaMRStar_RStar02->Draw("same");
   HW_GammaMRStar_RStar02->Draw("same");
   HTTbar_GammaMRStar_RStar02->Draw("same");
   HGammaMRStar_RStar02_DiJetAve30.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve60.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve80.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve110.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve150.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve190.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve240.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve300.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve370.Draw("point error same");
   TLegend Legend(0.8, 0.95, 0.95, 0.6);
   Legend.SetFillColor(0);
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve30, "HLT_DiJetAve_30", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve60, "HLT_DiJetAve_60", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve80, "HLT_DiJetAve_80", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve110, "HLT_DiJetAve_110", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve150, "HLT_DiJetAve_150", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve190, "HLT_DiJetAve_190", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve240, "HLT_DiJetAve_240", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve300, "HLT_DiJetAve_300", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve370, "HLT_DiJetAve_370", "lp");
   Legend.AddEntry(HTTbar_GammaMRStar_RStar02, "TTbar MC", "lpf");
   Legend.AddEntry(HW_GammaMRStar_RStar02, "W MC", "lpf");
   Legend.AddEntry(HZZ_GammaMRStar_RStar02, "DiBoson MC", "lpf");
   Legend.AddEntry(HGammaJet_GammaMRStar_RStar02, "GammaJet MC", "lpf");
   Legend.AddEntry(HDY50_GammaMRStar_RStar02, "DY 10+ MC", "lpf");
   Legend.Draw();
   l.DrawLatex(0.47, 0.77, s_latex);
   l.DrawLatex(0.47, 0.64, s_lumi);
   C1.SetLogy();
   PsFile.AddCanvas(C1);
   
   TCanvas C2;
   HGammaMRStar_RStar03_DiJetAve30.SetTitle("QCD shape as reconstructed from different triggers (RStar > 0.3)");
   HGammaMRStar_RStar03_DiJetAve30.GetYaxis()->SetTitle("Count / bin");
   HGammaMRStar_RStar03_DiJetAve30.SetMinimum(0.1);
   HGammaMRStar_RStar03_DiJetAve30.Draw("point error");
   HGammaMRStar_RStar03_DiJetAve60.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve80.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve110.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve150.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve190.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve240.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve300.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve370.Draw("point error same");
   HDY50_GammaMRStar_RStar03->Draw("same");
   HGammaJet_GammaMRStar_RStar03->Draw("same");
   HZZ_GammaMRStar_RStar03->Draw("same");
   HW_GammaMRStar_RStar03->Draw("same");
   HTTbar_GammaMRStar_RStar03->Draw("same");
   HGammaMRStar_RStar03_DiJetAve30.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve60.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve80.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve110.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve150.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve190.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve240.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve300.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve370.Draw("point error same");
   Legend.Draw();
   l.DrawLatex(0.47, 0.77, s_latex);
   l.DrawLatex(0.47, 0.64, s_lumi);
   C2.SetLogy();
   PsFile.AddCanvas(C2);

   TCanvas C3;
   HGammaMRStar_RStar04_DiJetAve30.SetTitle("QCD shape as reconstructed from different triggers (RStar > 0.4)");
   HGammaMRStar_RStar04_DiJetAve30.GetYaxis()->SetTitle("Count / bin");
   HGammaMRStar_RStar04_DiJetAve30.SetMinimum(0.1);
   HGammaMRStar_RStar04_DiJetAve30.Draw("point error");
   HGammaMRStar_RStar04_DiJetAve60.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve80.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve110.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve150.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve190.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve240.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve300.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve370.Draw("point error same");
   HDY50_GammaMRStar_RStar04->Draw("same");
   HGammaJet_GammaMRStar_RStar04->Draw("same");
   HZZ_GammaMRStar_RStar04->Draw("same");
   HW_GammaMRStar_RStar04->Draw("same");
   HTTbar_GammaMRStar_RStar04->Draw("same");
   HGammaMRStar_RStar04_DiJetAve30.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve60.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve80.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve110.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve150.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve190.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve240.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve300.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve370.Draw("point error same");
   Legend.Draw();
   l.DrawLatex(0.47, 0.77, s_latex);
   l.DrawLatex(0.47, 0.64, s_lumi);
   C3.SetLogy();
   PsFile.AddCanvas(C3);

   TCanvas C4;
   HGammaMRStar_RStar05_DiJetAve30.SetTitle("QCD shape as reconstructed from different triggers (RStar > 0.5)");
   HGammaMRStar_RStar05_DiJetAve30.GetYaxis()->SetTitle("Count / bin");
   HGammaMRStar_RStar05_DiJetAve30.SetMinimum(0.1);
   HGammaMRStar_RStar05_DiJetAve30.Draw("point error");
   HGammaMRStar_RStar05_DiJetAve60.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve80.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve110.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve150.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve190.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve240.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve300.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve370.Draw("point error same");
   HDY50_GammaMRStar_RStar05->Draw("same");
   HGammaJet_GammaMRStar_RStar05->Draw("same");
   HZZ_GammaMRStar_RStar05->Draw("same");
   HW_GammaMRStar_RStar05->Draw("same");
   HTTbar_GammaMRStar_RStar05->Draw("same");
   HGammaMRStar_RStar05_DiJetAve30.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve60.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve80.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve110.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve150.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve190.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve240.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve300.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve370.Draw("point error same");
   Legend.Draw();
   l.DrawLatex(0.47, 0.77, s_latex);
   l.DrawLatex(0.47, 0.64, s_lumi);
   C4.SetLogy();
   PsFile.AddCanvas(C4);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   FTTbar.Close();

   return 0;
}

void FixUpHistogram(TH1D &H, int Color)
{
   H.Sumw2();
   H.SetStats(0);
   H.SetLineColor(Color);
   H.SetMarkerColor(Color);
   H.SetMarkerStyle(11);
}


