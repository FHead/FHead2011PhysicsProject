#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TChain.h"

#include "SetStyle.h"

int main()
{
   SetThesisRegularStyle();

   TChain Tree("Tree", "Tree");
   Tree.AddFile("Meow.root");

   TH2D HDiagonal("HDiagonal", ";Grid-x index;Grid-y index", 70, 65, 135, 70, 65, 135);
   TH2D HNormal("HNormal", ";Grid-x index;Grid-y index", 70, 65, 135, 70, 65, 135);
   TH2D HDiagonalNo("HDiagonalNo", ";Grid-x index;Grid-y index", 70, 65, 135, 70, 65, 135);
   TH2D HNormalNo("HNormalNo", ";Grid-x index;Grid-y index", 70, 65, 135, 70, 65, 135);
   TH2D HDiagonalReboot("HDiagonalReboot", ";Grid-x index;Grid-y index", 70, 65, 135, 70, 65, 135);
   TH2D HNormalReboot("HNormalReboot", ";Grid-x index;Grid-y index", 70, 65, 135, 70, 65, 135);

   HDiagonal.SetStats(0);
   HNormal.SetStats(0);
   HDiagonalNo.SetStats(0);
   HNormalNo.SetStats(0);
   HDiagonalReboot.SetStats(0);
   HNormalReboot.SetStats(0);

   double B1, B2, B3, B4, B5, B6;
   Tree.SetBranchAddress("B1", &B1);
   Tree.SetBranchAddress("B2", &B2);
   Tree.SetBranchAddress("B3", &B3);
   Tree.SetBranchAddress("B4", &B4);
   Tree.SetBranchAddress("B5", &B5);
   Tree.SetBranchAddress("B6", &B6);

   int EntryCount = Tree.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree.GetEntry(iE);

      if(B1 == 1)
         HDiagonal.Fill(B2, B3, B6);
      else if(B1 == 2)
         HNormal.Fill(B2, B3, B6);
      else if(B1 == 3)
         HDiagonalNo.Fill(B2, B3, B6);
      else if(B1 == 4)
         HNormalNo.Fill(B2, B3, B6);
      else if(B1 == 5)
         HDiagonalReboot.Fill(B2, B3, B6);
      else if(B1 == 6)
         HNormalReboot.Fill(B2, B3, B6);
   }

   TCanvas Canvas;
   Canvas.SetLogz();

   HNormalNo.Draw("colz");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormalNo.png");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormalNo.C");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormalNo.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormalNo.pdf");

   HDiagonalNo.Draw("colz");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonalNo.png");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonalNo.C");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonalNo.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonalNo.pdf");

   HNormal.Draw("colz");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormal.png");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormal.C");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormal.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormal.pdf");

   HDiagonal.Draw("colz");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonal.png");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonal.C");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonal.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonal.pdf");

   HNormalReboot.Draw("colz");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormalReboot.png");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormalReboot.C");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormalReboot.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleNormalReboot.pdf");

   HDiagonalReboot.Draw("colz");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonalReboot.png");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonalReboot.C");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonalReboot.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Integral-AttractorExampleDiagonalReboot.pdf");

   return 0;
}





