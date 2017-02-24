#include <cmath>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TTree.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string Prefix = "JobBoth_";
   string Suffix = "_J.root";
   string Base = "JobBoth_J";

   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " Prefix Suffix Base" << endl;
      cerr << "Example: " << argv[0] << " JobBoth_ _J.root JobBoth_J" << endl;

      return -1;
   }

   Prefix = argv[1];
   Suffix = argv[2];
   Base = argv[3];

   int Lumi[11] = {25, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};

   double Bins[45] = {0}, WorldBins[12] = {0};
   for(int i = 0; i < 11; i++)
   {
      Bins[i*4+0] = log(Lumi[i]) - log(2) * 0.50;
      Bins[i*4+1] = log(Lumi[i]) - log(2) * 0.25;
      Bins[i*4+2] = log(Lumi[i]);
      Bins[i*4+3] = log(Lumi[i]) + log(2) * 0.25;
      Bins[i*4+4] = log(Lumi[i]) + log(2) * 0.50;

      WorldBins[i+0] = log(Lumi[i]) - log(2) * 0.50;
      WorldBins[i+1] = log(Lumi[i]) + log(2) * 0.50;
   }

   TH2D HWorldLarge("HWorldLarge", ";Luminosity (fb^{-1});Test statistic",
      11, WorldBins, 100, -100, 100);
   HWorldLarge.SetStats(0);
   HWorldLarge.GetXaxis()->SetTickLength(0);
   for(int i = 0; i < 11; i++)
      HWorldLarge.GetXaxis()->SetBinLabel(i + 1, Form("%d", Lumi[i]));

   TH2D HWorldSmall("HWorldSmall", ";Luminosity (fb^{-1});Test statistic",
      11, WorldBins, 100, -10, 10);
   HWorldSmall.SetStats(0);
   HWorldSmall.GetXaxis()->SetTickLength(0);
   for(int i = 0; i < 11; i++)
      HWorldSmall.GetXaxis()->SetBinLabel(i + 1, Form("%d", Lumi[i]));

   TH2D HLarge("HLarge", "Test statistics distribution", 44, Bins, 100, -100, 100);
   TH2D HSmall("HSmall", "Test statistics distribution", 44, Bins, 100, -10, 10);

   string Model[2] = {"SMVV", "5plet"};
   double Shift[2] = {-log(2) * 0.125, log(2) * 0.125};

   for(int iM = 0; iM < 2; iM++)
   {
      string FileName = Prefix + Model[iM] + Suffix;

      TFile File(FileName.c_str());
      TTree *Tree = (TTree *)File.Get("Tree");

      if(Tree == NULL)
         continue;

      double L, I2N, I5N, I2P, I5P, I2L, I5L;
      Tree->SetBranchAddress("L", &L);
      Tree->SetBranchAddress("I2N", &I2N);
      Tree->SetBranchAddress("I5N", &I5N);
      Tree->SetBranchAddress("I2P", &I2P);
      Tree->SetBranchAddress("I5P", &I5P);
      Tree->SetBranchAddress("I2L", &I2L);
      Tree->SetBranchAddress("I5L", &I5L);

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         HLarge.Fill(log(L) + Shift[iM], log(I5P) - log(I2P));
         HSmall.Fill(log(L) + Shift[iM], log(I5P) - log(I2P));
      }

      File.Close();
   }

   TGraph GZero;
   GZero.SetPoint(0, 0, 0);
   GZero.SetPoint(1, 100, 0);
   GZero.SetLineStyle(kDashed);

   TCanvas C;

   HWorldLarge.Draw();
   HLarge.Draw("colz same");
   GZero.Draw("l");

   C.SetLogz();

   C.SaveAs((Base + "_Large.png").c_str());
   C.SaveAs((Base + "_Large.C").c_str());
   C.SaveAs((Base + "_Large.eps").c_str());
   C.SaveAs((Base + "_Large.pdf").c_str());

   HWorldSmall.Draw();
   HSmall.Draw("colz same");
   GZero.Draw("l");

   C.SetLogz();

   C.SaveAs((Base + "_Small.png").c_str());
   C.SaveAs((Base + "_Small.C").c_str());
   C.SaveAs((Base + "_Small.eps").c_str());
   C.SaveAs((Base + "_Small.pdf").c_str());

   return 0;
}


