#include <iostream>
using namespace std;

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper2.h"

int main()
{
   SetStyle();

   TChain Tree("OutputTree", "OutputTree");
   Tree.AddFile("LQ150_backup_5.root");

   double MR8, R8;

   Tree.SetBranchAddress("MR8", &MR8);
   Tree.SetBranchAddress("R8", &R8);

   TH1D HMR8_R8R8010("HMR8_R8R8010", "M_{R}^{(8)}, R^{2 (8)} > 0.10;M_{R}^{(8)}", 100, 0, 1500);
   TH1D HMR8_R8R8020("HMR8_R8R8020", "M_{R}^{(8)}, R^{2 (8)} > 0.20;M_{R}^{(8)}", 100, 0, 1500);
   TH1D HMR8_R8R8030("HMR8_R8R8030", "M_{R}^{(8)}, R^{2 (8)} > 0.30;M_{R}^{(8)}", 100, 0, 1500);
   TH1D HMR8_R8R8040("HMR8_R8R8040", "M_{R}^{(8)}, R^{2 (8)} > 0.40;M_{R}^{(8)}", 100, 0, 1500);
   TH1D HMR8_R8R8050("HMR8_R8R8050", "M_{R}^{(8)}, R^{2 (8)} > 0.50;M_{R}^{(8)}", 100, 0, 1500);

   TH2D HMR8VsR8R8("HMR8VsR8R8", "M_{R}^{(8)} vs. R^{2 (8)};M_{R}^{(8)};R^{2 (8)}", 100, 0, 1500, 100, 0, 1);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree.GetEntry(iEntry);

      if(R8 * R8 > 0.10)
         HMR8_R8R8010.Fill(MR8);
      if(R8 * R8 > 0.20)
         HMR8_R8R8020.Fill(MR8);
      if(R8 * R8 > 0.30)
         HMR8_R8R8030.Fill(MR8);
      if(R8 * R8 > 0.40)
         HMR8_R8R8040.Fill(MR8);
      if(R8 * R8 > 0.50)
         HMR8_R8R8050.Fill(MR8);

      HMR8VsR8R8.Fill(MR8, R8 * R8);
   }

   PsFileHelper PsFile("Plots.ps");
   PsFile.AddTextPage("Razor(8) plots");

   PsFile.AddPlot(HMR8_R8R8010, "", true);
   PsFile.AddPlot(HMR8_R8R8020, "", true);
   PsFile.AddPlot(HMR8_R8R8030, "", true);
   PsFile.AddPlot(HMR8_R8R8040, "", true);
   PsFile.AddPlot(HMR8_R8R8050, "", true);
   PsFile.AddPlot(HMR8VsR8R8, "colz", false, true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   TCanvas CanvasMR8("CanvasMR8", "CanvasMR8", 1024, 1024);

   HMR8_R8R8010.SetLineColor(kBlack);
   HMR8_R8R8020.SetLineColor(kBlue);
   HMR8_R8R8030.SetLineColor(kGreen);
   HMR8_R8R8040.SetLineColor(kMagenta);
   HMR8_R8R8050.SetLineColor(kRed);

   HMR8_R8R8010.SetStats(0);
   HMR8_R8R8020.SetStats(0);
   HMR8_R8R8030.SetStats(0);
   HMR8_R8R8040.SetStats(0);
   HMR8_R8R8050.SetStats(0);

   HMR8_R8R8010.SetTitle("M_{R}^{(8)} under different R^{(8)} cuts");

   HMR8_R8R8010.Draw();
   HMR8_R8R8020.Draw("same");
   HMR8_R8R8030.Draw("same");
   HMR8_R8R8040.Draw("same");
   HMR8_R8R8050.Draw("same");

   TLegend MRLegend(0.5, 0.8, 0.8, 0.5);
   MRLegend.SetBorderSize(0);
   MRLegend.SetFillStyle(0);
   MRLegend.SetTextFont(42);
   MRLegend.AddEntry(&HMR8_R8R8010, "R^{2 (8)} > 0.10", "l");
   MRLegend.AddEntry(&HMR8_R8R8020, "R^{2 (8)} > 0.20", "l");
   MRLegend.AddEntry(&HMR8_R8R8030, "R^{2 (8)} > 0.30", "l");
   MRLegend.AddEntry(&HMR8_R8R8040, "R^{2 (8)} > 0.40", "l");
   MRLegend.AddEntry(&HMR8_R8R8050, "R^{2 (8)} > 0.50", "l");
   MRLegend.Draw();

   CanvasMR8.SetLogy();

   CanvasMR8.SaveAs("Plots/MR8Comparison.png");
   CanvasMR8.SaveAs("Plots/MR8Comparison.C");
   CanvasMR8.SaveAs("Plots/MR8Comparison.eps");
   CanvasMR8.SaveAs("Plots/MR8Comparison.pdf");

   TCanvas CanvasPlane("CanvasPlane", "CanvasPlane", 1024, 1024);

   HMR8VsR8R8.SetStats(0);

   HMR8VsR8R8.Draw("colz");

   CanvasPlane.SetLogz();

   CanvasPlane.SaveAs("Plots/MR8R8Plane.png");
   CanvasPlane.SaveAs("Plots/MR8R8Plane.C");
   CanvasPlane.SaveAs("Plots/MR8R8Plane.eos");
   CanvasPlane.SaveAs("Plots/MR8R8Plane.pdf");

   return 0;
}



