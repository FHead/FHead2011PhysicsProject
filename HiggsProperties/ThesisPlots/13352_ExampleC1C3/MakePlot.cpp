#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetThesisRegularStyle();

   TH2D H("H", ";c_{1};c_{3}", 100, 0.3, 2, 100, 0.5, 2);
   H.SetStats(0);
   // H.GetXaxis()->SetTitleOffset(1.1);
   // H.GetYaxis()->SetTitleOffset(1.2);
   H.GetXaxis()->SetTitle("c_{1}");
   H.GetYaxis()->SetTitle("c_{3}");

   TFile File("Meow.root");
   TTree *Tree = (TTree *)File.Get("Tree");

   TCanvas C;

   H.Draw();
   Tree->SetMarkerStyle(11);
   Tree->Draw("B5:B6", "B2 > 20.6 && B2 < 20.8 && B1 > 110.2 && B1 < 115", "same");

   C.SetLogx();
   C.SetLogy();
   C.SaveAs("MultiDimensionalDetails-Signal-C1C3Ellipse.png");
   C.SaveAs("MultiDimensionalDetails-Signal-C1C3Ellipse.C");
   C.SaveAs("MultiDimensionalDetails-Signal-C1C3Ellipse.eps");
   C.SaveAs("MultiDimensionalDetails-Signal-C1C3Ellipse.pdf");

   return 0;
}

