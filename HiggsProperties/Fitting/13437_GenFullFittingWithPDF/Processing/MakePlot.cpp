#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("MeowSM.root");
   TTree *Tree = (TTree *)File.Get("ResultTree");

   double Min = 30;
   double Max = 20000;
   int BinCount = 100;
   double Bins[101] = {0};
   for(int i = 0; i <= BinCount; i++)
      Bins[i] = exp((log(Max) - log(Min)) / BinCount * i + log(Min));

   TH2D HA2ZZ("HA2ZZ", ";N_{em};A_{2}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA3ZZ("HA3ZZ", ";N_{em};A_{3}^{ZZ}", BinCount, Bins, 100, -8, 8);
   TH2D HA4ZZ("HA4ZZ", ";N_{em};A_{4}^{ZZ}", BinCount, Bins, 100, -5, 8);
   TH2D HA2ZA("HA2ZA", ";N_{em};A_{2}^{ZA}", BinCount, Bins, 100, -0.5, 0.5);
   TH2D HA3ZA("HA3ZA", ";N_{em};A_{3}^{ZA}", BinCount, Bins, 100, -0.5, 0.5);
   TH2D HA2AA("HA2AA", ";N_{em};A_{2}^{AA}", BinCount, Bins, 100, -0.5, 0.5);
   TH2D HA3AA("HA3AA", ";N_{em};A_{3}^{AA}", BinCount, Bins, 100, -0.5, 0.5);
   TH2D HFraction("HFraction", ";N_{em};#Delta F_{em}", BinCount, Bins, 100, -0.1, 0.1);
   TH2D HFraction0("HFraction0", ";N_{em};#Delta F_{em}", BinCount, Bins, 100, -0.1, 0.1);

   HA2ZZ.SetStats(0);
   HA3ZZ.SetStats(0);
   HA4ZZ.SetStats(0);
   HA2ZA.SetStats(0);
   HA3ZA.SetStats(0);
   HA2AA.SetStats(0);
   HA3AA.SetStats(0);
   HFraction.SetStats(0);
   HFraction0.SetStats(0);

   Tree->Draw("A2ZZA1ZZ*2:Sem>>HA2ZZ", "A2ZZA1ZZError > 0", "colz");
   Tree->Draw("A3ZZA1ZZ*2:Sem>>HA3ZZ", "A2ZZA1ZZError > 0", "colz");
   Tree->Draw("A4ZZA1ZZ*2:Sem>>HA4ZZ", "A2ZZA1ZZError > 0", "colz");
   Tree->Draw("A2ZAA1ZZ*2:Sem>>HA2ZA", "A2ZZA1ZZError > 0", "colz");
   Tree->Draw("A3ZAA1ZZ*2:Sem>>HA3ZA", "A2ZZA1ZZError > 0", "colz");
   Tree->Draw("A2AAA1ZZ*2:Sem>>HA2AA", "A2ZZA1ZZError > 0", "colz");
   Tree->Draw("A3AAA1ZZ*2:Sem>>HA3AA", "A2ZZA1ZZError > 0", "colz");
   Tree->Draw("Fem-Bem/(Sem+Bem):Sem>>HFraction", "A2ZZA1ZZError > 0", "colz");
   Tree->Draw("Fem-Bem/(Sem+Bem):Sem>>HFraction0", "A2ZZA1ZZError == 0", "colz");

   TGraph GA2ZZ, GA3ZZ, GA4ZZ, GA2ZA, GA3ZA, GA2AA, GA3AA, GFraction;
   GA2ZZ.SetPoint(0, 0, 0);
   GA2ZZ.SetPoint(1, 100000, 0);
   GA3ZZ.SetPoint(0, 0, 0);
   GA3ZZ.SetPoint(1, 100000, 0);
   GA4ZZ.SetPoint(0, 0, 0);
   GA4ZZ.SetPoint(1, 100000, 0);
   GA2ZA.SetPoint(0, 0, 0.014);
   GA2ZA.SetPoint(1, 100000, 0.014);
   GA3ZA.SetPoint(0, 0, 0);
   GA3ZA.SetPoint(1, 100000, 0);
   GA2AA.SetPoint(0, 0, -0.008);
   GA2AA.SetPoint(1, 100000, -0.008);
   GA3AA.SetPoint(0, 0, 0);
   GA3AA.SetPoint(1, 100000, 0);
   GFraction.SetPoint(0, 0, 0);
   GFraction.SetPoint(1, 100000, 0);

   TCanvas C;

   HA2ZZ.Draw("colz");
   GA2ZZ.Draw("l");
   C.SetLogx();
   C.SetLogz();
   C.SaveAs("A2ZZNonZero.png");
   C.SaveAs("A2ZZNonZero.C");
   C.SaveAs("A2ZZNonZero.eps");
   C.SaveAs("A2ZZNonZero.pdf");

   HA3ZZ.Draw("colz");
   GA3ZZ.Draw("l");
   C.SetLogx();
   C.SetLogz();
   C.SaveAs("A3ZZNonZero.png");
   C.SaveAs("A3ZZNonZero.C");
   C.SaveAs("A3ZZNonZero.eps");
   C.SaveAs("A3ZZNonZero.pdf");

   HA4ZZ.Draw("colz");
   GA4ZZ.Draw("l");
   C.SetLogx();
   C.SetLogz();
   C.SaveAs("A4ZZNonZero.png");
   C.SaveAs("A4ZZNonZero.C");
   C.SaveAs("A4ZZNonZero.eps");
   C.SaveAs("A4ZZNonZero.pdf");

   HA2ZA.Draw("colz");
   GA2ZA.Draw("l");
   C.SetLogx();
   C.SetLogz();
   C.SaveAs("A2ZANonZero.png");
   C.SaveAs("A2ZANonZero.C");
   C.SaveAs("A2ZANonZero.eps");
   C.SaveAs("A2ZANonZero.pdf");

   HA3ZA.Draw("colz");
   GA3ZA.Draw("l");
   C.SetLogx();
   C.SetLogz();
   C.SaveAs("A3ZANonZero.png");
   C.SaveAs("A3ZANonZero.C");
   C.SaveAs("A3ZANonZero.eps");
   C.SaveAs("A3ZANonZero.pdf");

   HA2AA.Draw("colz");
   GA2AA.Draw("l");
   C.SetLogx();
   C.SetLogz();
   C.SaveAs("A2AANonZero.png");
   C.SaveAs("A2AANonZero.C");
   C.SaveAs("A2AANonZero.eps");
   C.SaveAs("A2AANonZero.pdf");

   HA3AA.Draw("colz");
   GA3AA.Draw("l");
   C.SetLogx();
   C.SetLogz();
   C.SaveAs("A3AANonZero.png");
   C.SaveAs("A3AANonZero.C");
   C.SaveAs("A3AANonZero.eps");
   C.SaveAs("A3AANonZero.pdf");

   HFraction.Draw("colz");
   GFraction.Draw("l");
   C.SetLogx();
   C.SetLogz();
   C.SaveAs("FractionNonZero.png");
   C.SaveAs("FractionNonZero.C");
   C.SaveAs("FractionNonZero.eps");
   C.SaveAs("FractionNonZero.pdf");

   HFraction0.Draw("colz");
   GFraction.Draw("l");
   C.SetLogx();
   C.SetLogz();
   C.SaveAs("Fraction0NonZero.png");
   C.SaveAs("Fraction0NonZero.C");
   C.SaveAs("Fraction0NonZero.eps");
   C.SaveAs("Fraction0NonZero.pdf");

   File.Close();

   return 0;
}




