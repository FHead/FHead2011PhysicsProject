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

   TH2D HNarrow("HNarrow", ";m_{1};m_{2}", 116, 88, 95, 42, 19.5, 22);
   TH2D HNormal("HNormal", ";m_{1};m_{2}", 116, 88, 95, 42, 19.5, 22);

   HNarrow.GetZaxis()->SetNdivisions(505);
   HNormal.GetZaxis()->SetNdivisions(505);

   HNarrow.SetStats(0);
   HNormal.SetStats(0);

   double Index, GridX, GridY, M1, M2, Integral;
   Tree.SetBranchAddress("B1", &Index);
   Tree.SetBranchAddress("B2", &GridX);
   Tree.SetBranchAddress("B3", &GridY);
   Tree.SetBranchAddress("B4", &M1);
   Tree.SetBranchAddress("B5", &M2);
   Tree.SetBranchAddress("B6", &Integral);

   int EntryCount = Tree.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree.GetEntry(iE);

      if(Index < 0.5)
         HNarrow.Fill(M1, M2, Integral);
      else if(Index > 0.5)
         HNormal.Fill(M1, M2, Integral);
   }

   for(int i = 1; i <= HNarrow.GetNbinsX(); i++)
      for(int j = 1; j <= HNarrow.GetNbinsY(); j++)
         if(HNarrow.GetBinContent(i, j) < 1e-30)
            HNarrow.SetBinContent(i, j, 1e-30);

   TCanvas Canvas;

   HNarrow.Draw("colz");
   Canvas.SaveAs("MultiDimensionalDetails-Signal-ElongationNarrow.png");
   Canvas.SaveAs("MultiDimensionalDetails-Signal-ElongationNarrow.C");
   Canvas.SaveAs("MultiDimensionalDetails-Signal-ElongationNarrow.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Signal-ElongationNarrow.pdf");

   HNormal.Draw("colz");
   Canvas.SaveAs("MultiDimensionalDetails-Signal-ElongationNormal.png");
   Canvas.SaveAs("MultiDimensionalDetails-Signal-ElongationNormal.C");
   Canvas.SaveAs("MultiDimensionalDetails-Signal-ElongationNormal.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Signal-ElongationNormal.pdf");

   return 0;
}





