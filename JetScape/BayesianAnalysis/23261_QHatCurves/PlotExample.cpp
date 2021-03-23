#include <iostream>
#include <vector>
using namespace std;

#include "TF1.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   int Colors[] = {kBlue, kGreen + 3, kCyan + 3, kRed, kMagenta};

   double B[] = {1, 2, 5, 10};
   double D[] = {1, 2, 5, 10};
   vector<TF1> F1;
   vector<TF1> F2;

   TLegend Legend1(0.5, 0.8, 0.8, 0.6);
   TLegend Legend2(0.5, 0.8, 0.8, 0.6);

   double L = 0.2;
   double E = 5;

   for(double b : B)
      F1.emplace_back(TF1(Form("F1%d", (int)F1.size()), Form("(log(x/%f)-log(%f))/(log(x/%f)*log(x/%f))", L, b, L, L), 2, 100));
   for(double d : D)
      F2.emplace_back(TF1(Form("F2%d", (int)F2.size()), Form("(log(%f/x)-log(%f))/(log(%f*x/%f/%f)*log(%f*x/%f/%f))", E, d, E, L, L, E, L, L), 0.01, 1));


   for(int i = 0; i < (int)F1.size(); i++)
   {
      F1[i].SetLineColor(Colors[i]);
      Legend1.AddEntry(&(F1[i]), Form("B = %.1f", B[i]), "l");
   }
   
   for(int i = 0; i < (int)F2.size(); i++)
   {
      F2[i].SetLineColor(Colors[i]);
      Legend2.AddEntry(&(F2[i]), Form("D = %.1f", D[i]), "l");
   }

   TCanvas Canvas1;

   TH2D HWorld1("HWorld1", "A-term;E (GeV);a.u.", 100, 0, 100, 100, 0.0, 0.5);
   HWorld1.SetStats(0);

   HWorld1.Draw("axis");
   for(TF1 &F : F1)
      F.Draw("same");
   Legend1.Draw();

   Canvas1.SaveAs("ATerm.pdf");

   TCanvas Canvas2;

   TH2D HWorld2("HWorld2", Form("C-term (E = %.0f GeV);T (GeV);a.u.", E), 100, 0.15, 0.50, 100, 0, 0.5);
   HWorld2.SetStats(0);

   HWorld2.Draw("axis");
   for(TF1 &F : F2)
      F.Draw("same");
   Legend2.Draw();

   Canvas2.SaveAs("CTerm.pdf");

   return 0;
}


