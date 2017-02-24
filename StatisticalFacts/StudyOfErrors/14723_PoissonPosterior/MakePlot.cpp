#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("Result.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   double k, Min68, Max68, Min95, Max95;
   Tree->SetBranchAddress("k", &k);
   Tree->SetBranchAddress("Min68", &Min68);
   Tree->SetBranchAddress("Max68", &Max68);
   Tree->SetBranchAddress("Min95", &Min95);
   Tree->SetBranchAddress("Max95", &Max95);

   TGraphAsymmErrors G68, G95, GC68, GC95;

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      G68.SetPoint(i, k, k);
      GC68.SetPoint(i, k, 0);
      G95.SetPoint(i, k, k);
      GC95.SetPoint(i, k, 0);

      G68.SetPointError(i, 0, 0, k - Min68, Max68 - k);
      GC68.SetPointError(i, 0, 0, k - Min68, Max68 - k);
      G95.SetPointError(i, 0, 0, k - Min95, Max95 - k);
      GC95.SetPointError(i, 0, 0, k - Min95, Max95 - k);
   }

   G68.SetMarkerColor(kBlue);
   GC68.SetMarkerColor(kBlue);
   G95.SetMarkerColor(kBlue);
   GC95.SetMarkerColor(kBlue);

   G68.SetLineColor(kBlue);
   GC68.SetLineColor(kBlue);
   G95.SetLineColor(kBlue);
   GC95.SetLineColor(kBlue);

   TH2D HWorld("HWorld", ";k;Confidence Range", 100, 0, 100, 100, 0, 125);
   HWorld.SetStats(0);

   TCanvas Canvas;
   HWorld.Draw();
   Canvas.SetGridx();
   Canvas.SetGridy();
   G68.Draw("p");
   G95.Draw("p");
   Canvas.SaveAs("Plots/ConfidenceRange.png");
   Canvas.SaveAs("Plots/ConfidenceRange.C");
   Canvas.SaveAs("Plots/ConfidenceRange.eps");
   Canvas.SaveAs("Plots/ConfidenceRange.pdf");

   TH2D HWorld2("HWorld2", ";k;Uncertainty", 100, 0, 100, 100, -25, 25);
   HWorld2.SetStats(0);

   TCanvas Canvas2;
   HWorld2.Draw();
   Canvas2.SetGridx();
   Canvas2.SetGridy();
   GC68.Draw("p");
   GC95.Draw("p");
   Canvas2.SaveAs("Plots/Uncertainty.png");
   Canvas2.SaveAs("Plots/Uncertainty.C");
   Canvas2.SaveAs("Plots/Uncertainty.eps");
   Canvas2.SaveAs("Plots/Uncertainty.pdf");

   File.Close();

   return 0;
}



