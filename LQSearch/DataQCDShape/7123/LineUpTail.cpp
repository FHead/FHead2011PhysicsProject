#include "TChain.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main()
{
   SetStyle();

   TChain InputTree("MRTree", "MRTree");
   InputTree.AddFile("JetReducedTree.root");

   double MR, R, MRStar, RStar, GammaMRStar, BetaR;
   bool PassDiJetAve15U, PassDiJetAve30U, PassDiJetAve50U, PassDiJetAve70U,
      PassDiJetAve100U, PassDiJetAve140U, PassDiJetAve180U, PassDiJetAve300U;
   bool PassDiJetAve30, PassDiJetAve60, PassDiJetAve80, PassDiJetAve110,
      PassDiJetAve150, PassDiJetAve190, PassDiJetAve240, PassDiJetAve300;

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
   InputTree.SetBranchAddress("PassDiJetAve15U", &PassDiJetAve15U);
   InputTree.SetBranchAddress("PassDiJetAve30U", &PassDiJetAve30U);
   InputTree.SetBranchAddress("PassDiJetAve50U", &PassDiJetAve50U);
   InputTree.SetBranchAddress("PassDiJetAve70U", &PassDiJetAve70U);
   InputTree.SetBranchAddress("PassDiJetAve100U", &PassDiJetAve100U);
   InputTree.SetBranchAddress("PassDiJetAve140U", &PassDiJetAve140U);
   InputTree.SetBranchAddress("PassDiJetAve180U", &PassDiJetAve180U);
   InputTree.SetBranchAddress("PassDiJetAve300U", &PassDiJetAve300U);

   TH1D HGammaMRStar_RStar02_DiJetAve70U("HGammaMRStar_RStar02_DiJetAve70U",
      "MRStar (RStar > 0.2), passing dijet ave. 70U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve100U("HGammaMRStar_RStar02_DiJetAve100U",
      "MRStar (RStar > 0.2), passing dijet ave. 100U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve140U("HGammaMRStar_RStar02_DiJetAve140U",
      "MRStar (RStar > 0.2), passing dijet ave. 140U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve180U("HGammaMRStar_RStar02_DiJetAve180U",
      "MRStar (RStar > 0.2), passing dijet ave. 180U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar02_DiJetAve300U("HGammaMRStar_RStar02_DiJetAve300U",
      "MRStar (RStar > 0.2), passing dijet ave. 300U;GammaMRStar", 40, 0, 2000);

   TH1D HGammaMRStar_RStar03_DiJetAve70U("HGammaMRStar_RStar03_DiJetAve70U",
      "MRStar (RStar > 0.3), passing dijet ave. 70U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve100U("HGammaMRStar_RStar03_DiJetAve100U",
      "MRStar (RStar > 0.3), passing dijet ave. 100U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve140U("HGammaMRStar_RStar03_DiJetAve140U",
      "MRStar (RStar > 0.3), passing dijet ave. 140U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve180U("HGammaMRStar_RStar03_DiJetAve180U",
      "MRStar (RStar > 0.3), passing dijet ave. 180U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar03_DiJetAve300U("HGammaMRStar_RStar03_DiJetAve300U",
      "MRStar (RStar > 0.3), passing dijet ave. 300U;GammaMRStar", 40, 0, 2000);

   TH1D HGammaMRStar_RStar04_DiJetAve70U("HGammaMRStar_RStar04_DiJetAve70U",
      "MRStar (RStar > 0.4), passing dijet ave. 70U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve100U("HGammaMRStar_RStar04_DiJetAve100U",
      "MRStar (RStar > 0.4), passing dijet ave. 100U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve140U("HGammaMRStar_RStar04_DiJetAve140U",
      "MRStar (RStar > 0.4), passing dijet ave. 140U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve180U("HGammaMRStar_RStar04_DiJetAve180U",
      "MRStar (RStar > 0.4), passing dijet ave. 180U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar04_DiJetAve300U("HGammaMRStar_RStar04_DiJetAve300U",
      "MRStar (RStar > 0.4), passing dijet ave. 300U;GammaMRStar", 40, 0, 2000);
   
   TH1D HGammaMRStar_RStar05_DiJetAve70U("HGammaMRStar_RStar05_DiJetAve70U",
      "MRStar (RStar > 0.5), passing dijet ave. 70U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve100U("HGammaMRStar_RStar05_DiJetAve100U",
      "MRStar (RStar > 0.5), passing dijet ave. 100U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve140U("HGammaMRStar_RStar05_DiJetAve140U",
      "MRStar (RStar > 0.5), passing dijet ave. 140U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve180U("HGammaMRStar_RStar05_DiJetAve180U",
      "MRStar (RStar > 0.5), passing dijet ave. 180U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar05_DiJetAve300U("HGammaMRStar_RStar05_DiJetAve300U",
      "MRStar (RStar > 0.5), passing dijet ave. 300U;GammaMRStar", 40, 0, 2000);
   
   TH1D HGammaMRStar_RStar06_DiJetAve70U("HGammaMRStar_RStar06_DiJetAve70U",
      "MRStar (RStar > 0.6), passing dijet ave. 70U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar06_DiJetAve100U("HGammaMRStar_RStar06_DiJetAve100U",
      "MRStar (RStar > 0.6), passing dijet ave. 100U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar06_DiJetAve140U("HGammaMRStar_RStar06_DiJetAve140U",
      "MRStar (RStar > 0.6), passing dijet ave. 140U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar06_DiJetAve180U("HGammaMRStar_RStar06_DiJetAve180U",
      "MRStar (RStar > 0.6), passing dijet ave. 180U;GammaMRStar", 40, 0, 2000);
   TH1D HGammaMRStar_RStar06_DiJetAve300U("HGammaMRStar_RStar06_DiJetAve300U",
      "MRStar (RStar > 0.6), passing dijet ave. 300U;GammaMRStar", 40, 0, 2000);
   
   HGammaMRStar_RStar02_DiJetAve70U.Sumw2();
   HGammaMRStar_RStar02_DiJetAve100U.Sumw2();
   HGammaMRStar_RStar02_DiJetAve140U.Sumw2();
   HGammaMRStar_RStar02_DiJetAve180U.Sumw2();
   HGammaMRStar_RStar02_DiJetAve300U.Sumw2();

   HGammaMRStar_RStar03_DiJetAve70U.Sumw2();
   HGammaMRStar_RStar03_DiJetAve100U.Sumw2();
   HGammaMRStar_RStar03_DiJetAve140U.Sumw2();
   HGammaMRStar_RStar03_DiJetAve180U.Sumw2();
   HGammaMRStar_RStar03_DiJetAve300U.Sumw2();

   HGammaMRStar_RStar04_DiJetAve70U.Sumw2();
   HGammaMRStar_RStar04_DiJetAve100U.Sumw2();
   HGammaMRStar_RStar04_DiJetAve140U.Sumw2();
   HGammaMRStar_RStar04_DiJetAve180U.Sumw2();
   HGammaMRStar_RStar04_DiJetAve300U.Sumw2();
   
   HGammaMRStar_RStar05_DiJetAve70U.Sumw2();
   HGammaMRStar_RStar05_DiJetAve100U.Sumw2();
   HGammaMRStar_RStar05_DiJetAve140U.Sumw2();
   HGammaMRStar_RStar05_DiJetAve180U.Sumw2();
   HGammaMRStar_RStar05_DiJetAve300U.Sumw2();

   HGammaMRStar_RStar06_DiJetAve70U.Sumw2();
   HGammaMRStar_RStar06_DiJetAve100U.Sumw2();
   HGammaMRStar_RStar06_DiJetAve140U.Sumw2();
   HGammaMRStar_RStar06_DiJetAve180U.Sumw2();
   HGammaMRStar_RStar06_DiJetAve300U.Sumw2();

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      InputTree.GetEntry(iEntry);

      if(RStar > 0.7)
         continue;

      if(RStar > 0.2 && PassDiJetAve70U == true)
         HGammaMRStar_RStar02_DiJetAve70U.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve100U == true)
         HGammaMRStar_RStar02_DiJetAve100U.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve140U == true)
         HGammaMRStar_RStar02_DiJetAve140U.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve180U == true)
         HGammaMRStar_RStar02_DiJetAve180U.Fill(GammaMRStar);
      if(RStar > 0.2 && PassDiJetAve300U == true)
         HGammaMRStar_RStar02_DiJetAve300U.Fill(GammaMRStar);
      
      if(RStar > 0.3 && PassDiJetAve70U == true)
         HGammaMRStar_RStar03_DiJetAve70U.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve100U == true)
         HGammaMRStar_RStar03_DiJetAve100U.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve140U == true)
         HGammaMRStar_RStar03_DiJetAve140U.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve180U == true)
         HGammaMRStar_RStar03_DiJetAve180U.Fill(GammaMRStar);
      if(RStar > 0.3 && PassDiJetAve300U == true)
         HGammaMRStar_RStar03_DiJetAve300U.Fill(GammaMRStar);
      
      if(RStar > 0.4 && PassDiJetAve70U == true)
         HGammaMRStar_RStar04_DiJetAve70U.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve100U == true)
         HGammaMRStar_RStar04_DiJetAve100U.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve140U == true)
         HGammaMRStar_RStar04_DiJetAve140U.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve180U == true)
         HGammaMRStar_RStar04_DiJetAve180U.Fill(GammaMRStar);
      if(RStar > 0.4 && PassDiJetAve300U == true)
         HGammaMRStar_RStar04_DiJetAve300U.Fill(GammaMRStar);
      
      if(RStar > 0.5 && PassDiJetAve70U == true)
         HGammaMRStar_RStar05_DiJetAve70U.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve100U == true)
         HGammaMRStar_RStar05_DiJetAve100U.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve140U == true)
         HGammaMRStar_RStar05_DiJetAve140U.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve180U == true)
         HGammaMRStar_RStar05_DiJetAve180U.Fill(GammaMRStar);
      if(RStar > 0.5 && PassDiJetAve300U == true)
         HGammaMRStar_RStar05_DiJetAve300U.Fill(GammaMRStar);
      
      if(RStar > 0.6 && PassDiJetAve70U == true)
         HGammaMRStar_RStar06_DiJetAve70U.Fill(GammaMRStar);
      if(RStar > 0.6 && PassDiJetAve100U == true)
         HGammaMRStar_RStar06_DiJetAve100U.Fill(GammaMRStar);
      if(RStar > 0.6 && PassDiJetAve140U == true)
         HGammaMRStar_RStar06_DiJetAve140U.Fill(GammaMRStar);
      if(RStar > 0.6 && PassDiJetAve180U == true)
         HGammaMRStar_RStar06_DiJetAve180U.Fill(GammaMRStar);
      if(RStar > 0.6 && PassDiJetAve300U == true)
         HGammaMRStar_RStar06_DiJetAve300U.Fill(GammaMRStar);
   }

   double Scale300 = 1;

   int BinAt700 = HGammaMRStar_RStar02_DiJetAve300U.FindBin(700);
   double Scale180 = HGammaMRStar_RStar02_DiJetAve300U.Integral(BinAt700, 9999)
      / HGammaMRStar_RStar02_DiJetAve180U.Integral(BinAt700, 9999) * Scale300;
   
   double Scale140 = HGammaMRStar_RStar02_DiJetAve180U.Integral(BinAt700, 9999)
      / HGammaMRStar_RStar02_DiJetAve140U.Integral(BinAt700, 9999) * Scale180;
   
   double Scale100 = HGammaMRStar_RStar02_DiJetAve140U.Integral(BinAt700, 9999)
      / HGammaMRStar_RStar02_DiJetAve100U.Integral(BinAt700, 9999) * Scale140;
   
   int BinAt550 = HGammaMRStar_RStar02_DiJetAve300U.FindBin(550);
   double Scale70 = HGammaMRStar_RStar02_DiJetAve100U.Integral(BinAt550, 9999)
      / HGammaMRStar_RStar02_DiJetAve70U.Integral(BinAt550, 9999) * Scale100;
   
   PsFileHelper PsFile("Plots.ps");
   PsFile.AddTextPage("Attempt to line-up data to reconstruct QCD shape!");

   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve70U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve100U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve140U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve180U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar02_DiJetAve300U, "", true);

   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve70U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve100U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve140U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve180U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar03_DiJetAve300U, "", true);

   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve70U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve100U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve140U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve180U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar04_DiJetAve300U, "", true);

   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve70U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve100U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve140U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve180U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar05_DiJetAve300U, "", true);

   PsFile.AddPlot(HGammaMRStar_RStar06_DiJetAve70U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar06_DiJetAve100U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar06_DiJetAve140U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar06_DiJetAve180U, "", true);
   PsFile.AddPlot(HGammaMRStar_RStar06_DiJetAve300U, "", true);

   HGammaMRStar_RStar02_DiJetAve70U.Scale(Scale70);
   HGammaMRStar_RStar02_DiJetAve100U.Scale(Scale100);
   HGammaMRStar_RStar02_DiJetAve140U.Scale(Scale140);
   HGammaMRStar_RStar02_DiJetAve180U.Scale(Scale180);
   HGammaMRStar_RStar02_DiJetAve300U.Scale(1);

   HGammaMRStar_RStar03_DiJetAve70U.Scale(Scale70);
   HGammaMRStar_RStar03_DiJetAve100U.Scale(Scale100);
   HGammaMRStar_RStar03_DiJetAve140U.Scale(Scale140);
   HGammaMRStar_RStar03_DiJetAve180U.Scale(Scale180);
   HGammaMRStar_RStar03_DiJetAve300U.Scale(1);

   HGammaMRStar_RStar04_DiJetAve70U.Scale(Scale70);
   HGammaMRStar_RStar04_DiJetAve100U.Scale(Scale100);
   HGammaMRStar_RStar04_DiJetAve140U.Scale(Scale140);
   HGammaMRStar_RStar04_DiJetAve180U.Scale(Scale180);
   HGammaMRStar_RStar04_DiJetAve300U.Scale(1);

   HGammaMRStar_RStar05_DiJetAve70U.Scale(Scale70);
   HGammaMRStar_RStar05_DiJetAve100U.Scale(Scale100);
   HGammaMRStar_RStar05_DiJetAve140U.Scale(Scale140);
   HGammaMRStar_RStar05_DiJetAve180U.Scale(Scale180);
   HGammaMRStar_RStar05_DiJetAve300U.Scale(1);

   HGammaMRStar_RStar06_DiJetAve70U.Scale(Scale70);
   HGammaMRStar_RStar06_DiJetAve100U.Scale(Scale100);
   HGammaMRStar_RStar06_DiJetAve140U.Scale(Scale140);
   HGammaMRStar_RStar06_DiJetAve180U.Scale(Scale180);
   HGammaMRStar_RStar06_DiJetAve300U.Scale(1);

   HGammaMRStar_RStar02_DiJetAve70U.SetStats(0);
   HGammaMRStar_RStar02_DiJetAve100U.SetStats(0);
   HGammaMRStar_RStar02_DiJetAve140U.SetStats(0);
   HGammaMRStar_RStar02_DiJetAve180U.SetStats(0);
   HGammaMRStar_RStar02_DiJetAve300U.SetStats(0);

   HGammaMRStar_RStar03_DiJetAve70U.SetStats(0);
   HGammaMRStar_RStar03_DiJetAve100U.SetStats(0);
   HGammaMRStar_RStar03_DiJetAve140U.SetStats(0);
   HGammaMRStar_RStar03_DiJetAve180U.SetStats(0);
   HGammaMRStar_RStar03_DiJetAve300U.SetStats(0);

   HGammaMRStar_RStar04_DiJetAve70U.SetStats(0);
   HGammaMRStar_RStar04_DiJetAve100U.SetStats(0);
   HGammaMRStar_RStar04_DiJetAve140U.SetStats(0);
   HGammaMRStar_RStar04_DiJetAve180U.SetStats(0);
   HGammaMRStar_RStar04_DiJetAve300U.SetStats(0);

   HGammaMRStar_RStar05_DiJetAve70U.SetStats(0);
   HGammaMRStar_RStar05_DiJetAve100U.SetStats(0);
   HGammaMRStar_RStar05_DiJetAve140U.SetStats(0);
   HGammaMRStar_RStar05_DiJetAve180U.SetStats(0);
   HGammaMRStar_RStar05_DiJetAve300U.SetStats(0);

   HGammaMRStar_RStar06_DiJetAve70U.SetStats(0);
   HGammaMRStar_RStar06_DiJetAve100U.SetStats(0);
   HGammaMRStar_RStar06_DiJetAve140U.SetStats(0);
   HGammaMRStar_RStar06_DiJetAve180U.SetStats(0);
   HGammaMRStar_RStar06_DiJetAve300U.SetStats(0);

   HGammaMRStar_RStar02_DiJetAve70U.SetLineColor(1);
   HGammaMRStar_RStar02_DiJetAve100U.SetLineColor(2);
   HGammaMRStar_RStar02_DiJetAve140U.SetLineColor(3);
   HGammaMRStar_RStar02_DiJetAve180U.SetLineColor(4);
   HGammaMRStar_RStar02_DiJetAve300U.SetLineColor(5);

   HGammaMRStar_RStar03_DiJetAve70U.SetLineColor(1);
   HGammaMRStar_RStar03_DiJetAve100U.SetLineColor(2);
   HGammaMRStar_RStar03_DiJetAve140U.SetLineColor(3);
   HGammaMRStar_RStar03_DiJetAve180U.SetLineColor(4);
   HGammaMRStar_RStar03_DiJetAve300U.SetLineColor(5);

   HGammaMRStar_RStar04_DiJetAve70U.SetLineColor(1);
   HGammaMRStar_RStar04_DiJetAve100U.SetLineColor(2);
   HGammaMRStar_RStar04_DiJetAve140U.SetLineColor(3);
   HGammaMRStar_RStar04_DiJetAve180U.SetLineColor(4);
   HGammaMRStar_RStar04_DiJetAve300U.SetLineColor(5);

   HGammaMRStar_RStar05_DiJetAve70U.SetLineColor(1);
   HGammaMRStar_RStar05_DiJetAve100U.SetLineColor(2);
   HGammaMRStar_RStar05_DiJetAve140U.SetLineColor(3);
   HGammaMRStar_RStar05_DiJetAve180U.SetLineColor(4);
   HGammaMRStar_RStar05_DiJetAve300U.SetLineColor(5);

   HGammaMRStar_RStar06_DiJetAve70U.SetLineColor(1);
   HGammaMRStar_RStar06_DiJetAve100U.SetLineColor(2);
   HGammaMRStar_RStar06_DiJetAve140U.SetLineColor(3);
   HGammaMRStar_RStar06_DiJetAve180U.SetLineColor(4);
   HGammaMRStar_RStar06_DiJetAve300U.SetLineColor(5);

   HGammaMRStar_RStar02_DiJetAve70U.SetMarkerColor(1);
   HGammaMRStar_RStar02_DiJetAve100U.SetMarkerColor(2);
   HGammaMRStar_RStar02_DiJetAve140U.SetMarkerColor(3);
   HGammaMRStar_RStar02_DiJetAve180U.SetMarkerColor(4);
   HGammaMRStar_RStar02_DiJetAve300U.SetMarkerColor(5);

   HGammaMRStar_RStar03_DiJetAve70U.SetMarkerColor(1);
   HGammaMRStar_RStar03_DiJetAve100U.SetMarkerColor(2);
   HGammaMRStar_RStar03_DiJetAve140U.SetMarkerColor(3);
   HGammaMRStar_RStar03_DiJetAve180U.SetMarkerColor(4);
   HGammaMRStar_RStar03_DiJetAve300U.SetMarkerColor(5);

   HGammaMRStar_RStar04_DiJetAve70U.SetMarkerColor(1);
   HGammaMRStar_RStar04_DiJetAve100U.SetMarkerColor(2);
   HGammaMRStar_RStar04_DiJetAve140U.SetMarkerColor(3);
   HGammaMRStar_RStar04_DiJetAve180U.SetMarkerColor(4);
   HGammaMRStar_RStar04_DiJetAve300U.SetMarkerColor(5);

   HGammaMRStar_RStar05_DiJetAve70U.SetMarkerColor(1);
   HGammaMRStar_RStar05_DiJetAve100U.SetMarkerColor(2);
   HGammaMRStar_RStar05_DiJetAve140U.SetMarkerColor(3);
   HGammaMRStar_RStar05_DiJetAve180U.SetMarkerColor(4);
   HGammaMRStar_RStar05_DiJetAve300U.SetMarkerColor(5);

   HGammaMRStar_RStar06_DiJetAve70U.SetMarkerColor(1);
   HGammaMRStar_RStar06_DiJetAve100U.SetMarkerColor(2);
   HGammaMRStar_RStar06_DiJetAve140U.SetMarkerColor(3);
   HGammaMRStar_RStar06_DiJetAve180U.SetMarkerColor(4);
   HGammaMRStar_RStar06_DiJetAve300U.SetMarkerColor(5);

   HGammaMRStar_RStar02_DiJetAve70U.SetMarkerStyle(11);
   HGammaMRStar_RStar02_DiJetAve100U.SetMarkerStyle(11);
   HGammaMRStar_RStar02_DiJetAve140U.SetMarkerStyle(11);
   HGammaMRStar_RStar02_DiJetAve180U.SetMarkerStyle(11);
   HGammaMRStar_RStar02_DiJetAve300U.SetMarkerStyle(11);

   HGammaMRStar_RStar03_DiJetAve70U.SetMarkerStyle(11);
   HGammaMRStar_RStar03_DiJetAve100U.SetMarkerStyle(11);
   HGammaMRStar_RStar03_DiJetAve140U.SetMarkerStyle(11);
   HGammaMRStar_RStar03_DiJetAve180U.SetMarkerStyle(11);
   HGammaMRStar_RStar03_DiJetAve300U.SetMarkerStyle(11);

   HGammaMRStar_RStar04_DiJetAve70U.SetMarkerStyle(11);
   HGammaMRStar_RStar04_DiJetAve100U.SetMarkerStyle(11);
   HGammaMRStar_RStar04_DiJetAve140U.SetMarkerStyle(11);
   HGammaMRStar_RStar04_DiJetAve180U.SetMarkerStyle(11);
   HGammaMRStar_RStar04_DiJetAve300U.SetMarkerStyle(11);

   HGammaMRStar_RStar05_DiJetAve70U.SetMarkerStyle(11);
   HGammaMRStar_RStar05_DiJetAve100U.SetMarkerStyle(11);
   HGammaMRStar_RStar05_DiJetAve140U.SetMarkerStyle(11);
   HGammaMRStar_RStar05_DiJetAve180U.SetMarkerStyle(11);
   HGammaMRStar_RStar05_DiJetAve300U.SetMarkerStyle(11);

   HGammaMRStar_RStar06_DiJetAve70U.SetMarkerStyle(11);
   HGammaMRStar_RStar06_DiJetAve100U.SetMarkerStyle(11);
   HGammaMRStar_RStar06_DiJetAve140U.SetMarkerStyle(11);
   HGammaMRStar_RStar06_DiJetAve180U.SetMarkerStyle(11);
   HGammaMRStar_RStar06_DiJetAve300U.SetMarkerStyle(11);

   TCanvas C1;
   HGammaMRStar_RStar02_DiJetAve70U.SetTitle("QCD shape as reconstructed from different triggers (RStar > 0.2)");
   HGammaMRStar_RStar02_DiJetAve70U.GetYaxis()->SetTitle("a.u.");
   HGammaMRStar_RStar02_DiJetAve70U.SetMinimum(0.1);
   HGammaMRStar_RStar02_DiJetAve70U.Draw("point error");
   HGammaMRStar_RStar02_DiJetAve100U.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve140U.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve180U.Draw("point error same");
   HGammaMRStar_RStar02_DiJetAve300U.Draw("point error same");
   TLegend Legend(0.8, 0.95, 0.95, 0.75);
   Legend.SetFillColor(0);
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve70U, "HLT_DiJetAve_70U", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve100U, "HLT_DiJetAve_100U", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve140U, "HLT_DiJetAve_140U", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve180U, "HLT_DiJetAve_180U", "lp");
   Legend.AddEntry(&HGammaMRStar_RStar02_DiJetAve300U, "HLT_DiJetAve_300U", "lp");
   Legend.Draw();
   C1.SetLogy();
   PsFile.AddCanvas(C1);

   TCanvas C2;
   HGammaMRStar_RStar03_DiJetAve70U.SetTitle("QCD shape as reconstructed from different triggers (RStar > 0.3)");
   HGammaMRStar_RStar03_DiJetAve70U.GetYaxis()->SetTitle("a.u.");
   HGammaMRStar_RStar03_DiJetAve70U.SetMinimum(0.1);
   HGammaMRStar_RStar03_DiJetAve70U.Draw("point error");
   HGammaMRStar_RStar03_DiJetAve100U.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve140U.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve180U.Draw("point error same");
   HGammaMRStar_RStar03_DiJetAve300U.Draw("point error same");
   Legend.Draw();
   C2.SetLogy();
   PsFile.AddCanvas(C2);
   
   TCanvas C3;
   HGammaMRStar_RStar04_DiJetAve70U.SetTitle("QCD shape as reconstructed from different triggers (RStar > 0.4)");
   HGammaMRStar_RStar04_DiJetAve70U.GetYaxis()->SetTitle("a.u.");
   HGammaMRStar_RStar04_DiJetAve70U.SetMinimum(0.1);
   HGammaMRStar_RStar04_DiJetAve70U.Draw("point error");
   HGammaMRStar_RStar04_DiJetAve100U.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve140U.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve180U.Draw("point error same");
   HGammaMRStar_RStar04_DiJetAve300U.Draw("point error same");
   Legend.Draw();
   C3.SetLogy();
   PsFile.AddCanvas(C3);

   TCanvas C4;
   HGammaMRStar_RStar05_DiJetAve70U.SetTitle("QCD shape as reconstructed from different triggers (RStar > 0.5)");
   HGammaMRStar_RStar05_DiJetAve70U.GetYaxis()->SetTitle("a.u.");
   HGammaMRStar_RStar05_DiJetAve70U.SetMinimum(0.1);
   HGammaMRStar_RStar05_DiJetAve70U.Draw("point error");
   HGammaMRStar_RStar05_DiJetAve100U.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve140U.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve180U.Draw("point error same");
   HGammaMRStar_RStar05_DiJetAve300U.Draw("point error same");
   Legend.Draw();
   C4.SetLogy();
   PsFile.AddCanvas(C4);
   
   TCanvas C5;
   HGammaMRStar_RStar06_DiJetAve70U.SetTitle("QCD shape as reconstructed from different triggers (RStar > 0.6)");
   HGammaMRStar_RStar06_DiJetAve70U.GetYaxis()->SetTitle("a.u.");
   HGammaMRStar_RStar06_DiJetAve70U.SetMinimum(0.1);
   HGammaMRStar_RStar06_DiJetAve70U.Draw("point error");
   HGammaMRStar_RStar06_DiJetAve100U.Draw("point error same");
   HGammaMRStar_RStar06_DiJetAve140U.Draw("point error same");
   HGammaMRStar_RStar06_DiJetAve180U.Draw("point error same");
   HGammaMRStar_RStar06_DiJetAve300U.Draw("point error same");
   Legend.Draw();
   C5.SetLogy();
   PsFile.AddCanvas(C5);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}




