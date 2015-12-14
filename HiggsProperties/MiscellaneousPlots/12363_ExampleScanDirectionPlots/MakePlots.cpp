#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TChain.h"

int main()
{
   TChain Tree("Tree", "Tree");
   Tree.AddFile("Meow.root");

   TH2D HDiagonal("HDiagonal", ";Grid-x index;Grid-y index", 200, 0, 200, 200, 0, 200);
   TH2D HNormal("HNormal", ";Grid-x index;Grid-y index", 200, 0, 200, 200, 0, 200);
   TH2D HDiagonalNo("HDiagonalNo", ";Grid-x index;Grid-y index", 200, 0, 200, 200, 0, 200);
   TH2D HNormalNo("HNormalNo", ";Grid-x index;Grid-y index", 200, 0, 200, 200, 0, 200);
   TH2D HDiagonalReboot("HDiagonalReboot", ";Grid-x index;Grid-y index", 200, 0, 200, 200, 0, 200);
   TH2D HNormalReboot("HNormalReboot", ";Grid-x index;Grid-y index", 200, 0, 200, 200, 0, 200);

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

   TCanvas Canvas("C", "C", 768, 1024);
   Canvas.Divide(2, 3);
   Canvas.cd(1);
   HNormalNo.Draw("colz");
   Canvas.cd(2);
   HDiagonalNo.Draw("colz");
   Canvas.cd(3);
   HNormal.Draw("colz");
   Canvas.cd(4);
   HDiagonal.Draw("colz");
   Canvas.cd(5);
   HNormalReboot.Draw("colz");
   Canvas.cd(6);
   HDiagonalReboot.Draw("colz");
   Canvas.SaveAs("SignalScanDirection.png");
   Canvas.SaveAs("SignalScanDirection.C");
   Canvas.SaveAs("SignalScanDirection.eps");
   Canvas.SaveAs("SignalScanDirection.pdf");
}





