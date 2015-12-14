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

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile("TTJets_TuneZ2_7TeV-madgraph-tauola_All.root");

   int WToENuCount, WToMuNuCount, WToTauNuCount;
   double MR8, R8;

   Tree.SetBranchAddress("WToENuCount", &WToENuCount);
   Tree.SetBranchAddress("WToMuNuCount", &WToMuNuCount);
   Tree.SetBranchAddress("WToTauNuCount", &WToTauNuCount);
   Tree.SetBranchAddress("MR8", &MR8);
   Tree.SetBranchAddress("R8", &R8);

   TH1D HMR8_R8R8010("HMR8_R8R8010", "M_{R}^{(8)}, R^{2 (8)} > 0.10;M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8020("HMR8_R8R8020", "M_{R}^{(8)}, R^{2 (8)} > 0.20;M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8030("HMR8_R8R8030", "M_{R}^{(8)}, R^{2 (8)} > 0.30;M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8040("HMR8_R8R8040", "M_{R}^{(8)}, R^{2 (8)} > 0.40;M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8050("HMR8_R8R8050", "M_{R}^{(8)}, R^{2 (8)} > 0.50;M_{R}^{(8)}", 100, 0, 1000);

   TH2D HMR8VsR8R8("HMR8VsR8R8", "M_{R}^{(8)} vs. R^{2 (8)};M_{R}^{(8)};R^{2 (8)}", 100, 0, 1000, 100, 0, 1);
   
   TH1D HMR8_R8R8010_LL("HMR8_R8R8010_LL", "M_{R}^{(8)}, R^{2 (8)} > 0.10 (LL);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8020_LL("HMR8_R8R8020_LL", "M_{R}^{(8)}, R^{2 (8)} > 0.20 (LL);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8030_LL("HMR8_R8R8030_LL", "M_{R}^{(8)}, R^{2 (8)} > 0.30 (LL);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8040_LL("HMR8_R8R8040_LL", "M_{R}^{(8)}, R^{2 (8)} > 0.40 (LL);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8050_LL("HMR8_R8R8050_LL", "M_{R}^{(8)}, R^{2 (8)} > 0.50 (LL);M_{R}^{(8)}", 100, 0, 1000);

   TH1D HMR8_R8R8010_L("HMR8_R8R8010_L", "M_{R}^{(8)}, R^{2 (8)} > 0.10 (L);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8020_L("HMR8_R8R8020_L", "M_{R}^{(8)}, R^{2 (8)} > 0.20 (L);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8030_L("HMR8_R8R8030_L", "M_{R}^{(8)}, R^{2 (8)} > 0.30 (L);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8040_L("HMR8_R8R8040_L", "M_{R}^{(8)}, R^{2 (8)} > 0.40 (L);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8050_L("HMR8_R8R8050_L", "M_{R}^{(8)}, R^{2 (8)} > 0.50 (L);M_{R}^{(8)}", 100, 0, 1000);

   TH1D HMR8_R8R8010_H("HMR8_R8R8010_H", "M_{R}^{(8)}, R^{2 (8)} > 0.10 (H);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8020_H("HMR8_R8R8020_H", "M_{R}^{(8)}, R^{2 (8)} > 0.20 (H);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8030_H("HMR8_R8R8030_H", "M_{R}^{(8)}, R^{2 (8)} > 0.30 (H);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8040_H("HMR8_R8R8040_H", "M_{R}^{(8)}, R^{2 (8)} > 0.40 (H);M_{R}^{(8)}", 100, 0, 1000);
   TH1D HMR8_R8R8050_H("HMR8_R8R8050_H", "M_{R}^{(8)}, R^{2 (8)} > 0.50 (H);M_{R}^{(8)}", 100, 0, 1000);

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
      
      if(R8 * R8 > 0.10 && WToENuCount + WToMuNuCount == 2)
         HMR8_R8R8010_LL.Fill(MR8);
      if(R8 * R8 > 0.20 && WToENuCount + WToMuNuCount == 2)
         HMR8_R8R8020_LL.Fill(MR8);
      if(R8 * R8 > 0.30 && WToENuCount + WToMuNuCount == 2)
         HMR8_R8R8030_LL.Fill(MR8);
      if(R8 * R8 > 0.40 && WToENuCount + WToMuNuCount == 2)
         HMR8_R8R8040_LL.Fill(MR8);
      if(R8 * R8 > 0.50 && WToENuCount + WToMuNuCount == 2)
         HMR8_R8R8050_LL.Fill(MR8);

      if(R8 * R8 > 0.10 && WToENuCount + WToMuNuCount == 1 && WToTauNuCount == 0)
         HMR8_R8R8010_L.Fill(MR8);
      if(R8 * R8 > 0.20 && WToENuCount + WToMuNuCount == 1 && WToTauNuCount == 0)
         HMR8_R8R8020_L.Fill(MR8);
      if(R8 * R8 > 0.30 && WToENuCount + WToMuNuCount == 1 && WToTauNuCount == 0)
         HMR8_R8R8030_L.Fill(MR8);
      if(R8 * R8 > 0.40 && WToENuCount + WToMuNuCount == 1 && WToTauNuCount == 0)
         HMR8_R8R8040_L.Fill(MR8);
      if(R8 * R8 > 0.50 && WToENuCount + WToMuNuCount == 1 && WToTauNuCount == 0)
         HMR8_R8R8050_L.Fill(MR8);

      if(R8 * R8 > 0.10 && WToENuCount + WToMuNuCount == 0 && WToTauNuCount == 0)
         HMR8_R8R8010_H.Fill(MR8);
      if(R8 * R8 > 0.20 && WToENuCount + WToMuNuCount == 0 && WToTauNuCount == 0)
         HMR8_R8R8020_H.Fill(MR8);
      if(R8 * R8 > 0.30 && WToENuCount + WToMuNuCount == 0 && WToTauNuCount == 0)
         HMR8_R8R8030_H.Fill(MR8);
      if(R8 * R8 > 0.40 && WToENuCount + WToMuNuCount == 0 && WToTauNuCount == 0)
         HMR8_R8R8040_H.Fill(MR8);
      if(R8 * R8 > 0.50 && WToENuCount + WToMuNuCount == 0 && WToTauNuCount == 0)
         HMR8_R8R8050_H.Fill(MR8);
   }

   PsFileHelper PsFile("Plots.ps");
   PsFile.AddTextPage("Razor(8) plots");

   PsFile.AddPlot(HMR8_R8R8010, "", true);
   PsFile.AddPlot(HMR8_R8R8020, "", true);
   PsFile.AddPlot(HMR8_R8R8030, "", true);
   PsFile.AddPlot(HMR8_R8R8040, "", true);
   PsFile.AddPlot(HMR8_R8R8050, "", true);
   PsFile.AddPlot(HMR8VsR8R8, "colz", false, true);
   
   PsFile.AddPlot(HMR8_R8R8010_LL, "", true);
   PsFile.AddPlot(HMR8_R8R8020_LL, "", true);
   PsFile.AddPlot(HMR8_R8R8030_LL, "", true);
   PsFile.AddPlot(HMR8_R8R8040_LL, "", true);
   PsFile.AddPlot(HMR8_R8R8050_LL, "", true);

   PsFile.AddPlot(HMR8_R8R8010_L, "", true);
   PsFile.AddPlot(HMR8_R8R8020_L, "", true);
   PsFile.AddPlot(HMR8_R8R8030_L, "", true);
   PsFile.AddPlot(HMR8_R8R8040_L, "", true);
   PsFile.AddPlot(HMR8_R8R8050_L, "", true);

   PsFile.AddPlot(HMR8_R8R8010_H, "", true);
   PsFile.AddPlot(HMR8_R8R8020_H, "", true);
   PsFile.AddPlot(HMR8_R8R8030_H, "", true);
   PsFile.AddPlot(HMR8_R8R8040_H, "", true);
   PsFile.AddPlot(HMR8_R8R8050_H, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   HMR8_R8R8010.SetLineColor(kBlack);
   HMR8_R8R8020.SetLineColor(kBlue);
   HMR8_R8R8030.SetLineColor(kGreen);
   HMR8_R8R8040.SetLineColor(kMagenta);
   HMR8_R8R8050.SetLineColor(kRed);
   HMR8_R8R8010_LL.SetLineColor(kBlack);
   HMR8_R8R8020_LL.SetLineColor(kBlue);
   HMR8_R8R8030_LL.SetLineColor(kGreen);
   HMR8_R8R8040_LL.SetLineColor(kMagenta);
   HMR8_R8R8050_LL.SetLineColor(kRed);
   HMR8_R8R8010_L.SetLineColor(kBlack);
   HMR8_R8R8020_L.SetLineColor(kBlue);
   HMR8_R8R8030_L.SetLineColor(kGreen);
   HMR8_R8R8040_L.SetLineColor(kMagenta);
   HMR8_R8R8050_L.SetLineColor(kRed);
   HMR8_R8R8010_H.SetLineColor(kBlack);
   HMR8_R8R8020_H.SetLineColor(kBlue);
   HMR8_R8R8030_H.SetLineColor(kGreen);
   HMR8_R8R8040_H.SetLineColor(kMagenta);
   HMR8_R8R8050_H.SetLineColor(kRed);

   HMR8_R8R8010.SetStats(0);
   HMR8_R8R8020.SetStats(0);
   HMR8_R8R8030.SetStats(0);
   HMR8_R8R8040.SetStats(0);
   HMR8_R8R8050.SetStats(0);
   HMR8_R8R8010_LL.SetStats(0);
   HMR8_R8R8020_LL.SetStats(0);
   HMR8_R8R8030_LL.SetStats(0);
   HMR8_R8R8040_LL.SetStats(0);
   HMR8_R8R8050_LL.SetStats(0);
   HMR8_R8R8010_L.SetStats(0);
   HMR8_R8R8020_L.SetStats(0);
   HMR8_R8R8030_L.SetStats(0);
   HMR8_R8R8040_L.SetStats(0);
   HMR8_R8R8050_L.SetStats(0);
   HMR8_R8R8010_H.SetStats(0);
   HMR8_R8R8020_H.SetStats(0);
   HMR8_R8R8030_H.SetStats(0);
   HMR8_R8R8040_H.SetStats(0);
   HMR8_R8R8050_H.SetStats(0);

   HMR8_R8R8010.SetTitle("M_{R}^{(8)} under different R^{(8)} cuts");
   HMR8_R8R8010_LL.SetTitle("M_{R}^{(8)} under different R^{(8)} cuts (fully leptonic)");
   HMR8_R8R8010_L.SetTitle("M_{R}^{(8)} under different R^{(8)} cuts (semi-leptonic)");
   HMR8_R8R8010_H.SetTitle("M_{R}^{(8)} under different R^{(8)} cuts (hadronic)");

   TLegend MRLegend(0.5, 0.8, 0.8, 0.5);
   MRLegend.SetBorderSize(0);
   MRLegend.SetFillStyle(0);
   MRLegend.SetTextFont(42);
   MRLegend.AddEntry(&HMR8_R8R8010, "R^{2 (8)} > 0.10", "l");
   MRLegend.AddEntry(&HMR8_R8R8020, "R^{2 (8)} > 0.20", "l");
   MRLegend.AddEntry(&HMR8_R8R8030, "R^{2 (8)} > 0.30", "l");
   MRLegend.AddEntry(&HMR8_R8R8040, "R^{2 (8)} > 0.40", "l");
   MRLegend.AddEntry(&HMR8_R8R8050, "R^{2 (8)} > 0.50", "l");

   TCanvas CanvasMR8("CanvasMR8", "CanvasMR8", 1024, 1024);

   HMR8_R8R8010.Draw();
   HMR8_R8R8020.Draw("same");
   HMR8_R8R8030.Draw("same");
   HMR8_R8R8040.Draw("same");
   HMR8_R8R8050.Draw("same");

   MRLegend.Draw();
   
   CanvasMR8.SetLogy();

   CanvasMR8.SaveAs("Plots/TTbarMR8Comparison.png");
   CanvasMR8.SaveAs("Plots/TTbarMR8Comparison.C");
   CanvasMR8.SaveAs("Plots/TTbarMR8Comparison.eps");
   CanvasMR8.SaveAs("Plots/TTbarMR8Comparison.pdf");

   TCanvas CanvasMR8_LL("CanvasMR8_LL", "CanvasMR8_LL", 1024, 1024);

   HMR8_R8R8010_LL.Draw();
   HMR8_R8R8020_LL.Draw("same");
   HMR8_R8R8030_LL.Draw("same");
   HMR8_R8R8040_LL.Draw("same");
   HMR8_R8R8050_LL.Draw("same");

   MRLegend.Draw();
   
   CanvasMR8_LL.SetLogy();

   CanvasMR8_LL.SaveAs("Plots/TTbarMR8Comparison_LL.png");
   CanvasMR8_LL.SaveAs("Plots/TTbarMR8Comparison_LL.C");
   CanvasMR8_LL.SaveAs("Plots/TTbarMR8Comparison_LL.eps");
   CanvasMR8_LL.SaveAs("Plots/TTbarMR8Comparison_LL.pdf");

   TCanvas CanvasMR8_L("CanvasMR8_L", "CanvasMR8_L", 1024, 1024);

   HMR8_R8R8010_L.Draw();
   HMR8_R8R8020_L.Draw("same");
   HMR8_R8R8030_L.Draw("same");
   HMR8_R8R8040_L.Draw("same");
   HMR8_R8R8050_L.Draw("same");

   MRLegend.Draw();
   
   CanvasMR8_L.SetLogy();

   CanvasMR8_L.SaveAs("Plots/TTbarMR8Comparison_L.png");
   CanvasMR8_L.SaveAs("Plots/TTbarMR8Comparison_L.C");
   CanvasMR8_L.SaveAs("Plots/TTbarMR8Comparison_L.eps");
   CanvasMR8_L.SaveAs("Plots/TTbarMR8Comparison_L.pdf");

   TCanvas CanvasMR8_H("CanvasMR8_H", "CanvasMR8_H", 1024, 1024);

   HMR8_R8R8010_H.Draw();
   HMR8_R8R8020_H.Draw("same");
   HMR8_R8R8030_H.Draw("same");
   HMR8_R8R8040_H.Draw("same");
   HMR8_R8R8050_H.Draw("same");

   MRLegend.Draw();
   
   CanvasMR8_H.SetLogy();

   CanvasMR8_H.SaveAs("Plots/TTbarMR8Comparison_H.png");
   CanvasMR8_H.SaveAs("Plots/TTbarMR8Comparison_H.C");
   CanvasMR8_H.SaveAs("Plots/TTbarMR8Comparison_H.eps");
   CanvasMR8_H.SaveAs("Plots/TTbarMR8Comparison_H.pdf");

   TCanvas CanvasPlane("CanvasPlane", "CanvasPlane", 1024, 1024);

   HMR8VsR8R8.SetStats(0);

   HMR8VsR8R8.Draw("colz");

   CanvasPlane.SetLogz();

   CanvasPlane.SaveAs("Plots/TTbarMR8R8Plane.png");
   CanvasPlane.SaveAs("Plots/TTbarMR8R8Plane.C");
   CanvasPlane.SaveAs("Plots/TTbarMR8R8Plane.eos");
   CanvasPlane.SaveAs("Plots/TTbarMR8R8Plane.pdf");

   return 0;
}



