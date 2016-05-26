#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("Result.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   double x, N, Min68, Max68, Min95, Max95;
   Tree->SetBranchAddress("x", &x);
   Tree->SetBranchAddress("N", &N);
   Tree->SetBranchAddress("Min68", &Min68);
   Tree->SetBranchAddress("Max68", &Max68);
   Tree->SetBranchAddress("Min95", &Min95);
   Tree->SetBranchAddress("Max95", &Max95);

   TGraph GX000Max68, GX000Max95;
   TGraph GX050Max68, GX050Max95;
   TGraph GX025Min68, GX025Max68, GX025Min95, GX025Max95;
   TGraph GX010Min68, GX010Max68, GX010Min95, GX010Max95;
   TGraph GX005Min68, GX005Max68, GX005Min95, GX005Max95;
   TGraph GX002Min68, GX002Max68, GX002Min95, GX002Max95;
   TGraph GX001Min68, GX001Max68, GX001Min95, GX001Max95;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(x == 0)
      {
         GX000Max68.SetPoint(GX000Max68.GetN(), N, Max68);
         GX000Max95.SetPoint(GX000Max95.GetN(), N, Max95);
      }
      if(x * 2 == N)
      {
         GX050Max68.SetPoint(GX050Max68.GetN(), N, Max68 - 0.5);
         GX050Max95.SetPoint(GX050Max95.GetN(), N, Max95 - 0.5);
      }
      if(x * 4 == N)
      {
         GX025Min68.SetPoint(GX025Max68.GetN(), N, 0.25 - Min68);
         GX025Max68.SetPoint(GX025Max68.GetN(), N, Max68 - 0.25);
         GX025Min95.SetPoint(GX025Max95.GetN(), N, 0.25 - Min95);
         GX025Max95.SetPoint(GX025Max95.GetN(), N, Max95 - 0.25);
      }
      if(x * 10 == N)
      {
         GX010Min68.SetPoint(GX010Max68.GetN(), N, 0.10 - Min68);
         GX010Max68.SetPoint(GX010Max68.GetN(), N, Max68 - 0.10);
         GX010Min95.SetPoint(GX010Max95.GetN(), N, 0.10 - Min95);
         GX010Max95.SetPoint(GX010Max95.GetN(), N, Max95 - 0.10);
      }
      if(x * 20 == N)
      {
         GX005Min68.SetPoint(GX005Max68.GetN(), N, 0.05 - Min68);
         GX005Max68.SetPoint(GX005Max68.GetN(), N, Max68 - 0.05);
         GX005Min95.SetPoint(GX005Max95.GetN(), N, 0.05 - Min95);
         GX005Max95.SetPoint(GX005Max95.GetN(), N, Max95 - 0.05);
      }
      if(x * 50 == N)
      {
         GX002Min68.SetPoint(GX002Max68.GetN(), N, 0.02 - Min68);
         GX002Max68.SetPoint(GX002Max68.GetN(), N, Max68 - 0.02);
         GX002Min95.SetPoint(GX002Max95.GetN(), N, 0.02 - Min95);
         GX002Max95.SetPoint(GX002Max95.GetN(), N, Max95 - 0.02);
      }
      if(x * 100 == N)
      {
         GX001Min68.SetPoint(GX001Max68.GetN(), N, 0.01 - Min68);
         GX001Max68.SetPoint(GX001Max68.GetN(), N, Max68 - 0.01);
         GX001Min95.SetPoint(GX001Max95.GetN(), N, 0.01 - Min95);
         GX001Max95.SetPoint(GX001Max95.GetN(), N, Max95 - 0.01);
      }
   }

   TH2D HX000World("HX000World", ";N;Uncertainty", 100, 0.5, 2000, 100, 0.001, 1);
   HX000World.SetStats(0);

   GX000Max68.SetMarkerColor(kGreen);
   GX000Max95.SetMarkerColor(kBlue);

   TLegend LegendX000(0.5, 0.8, 0.8, 0.6);
   LegendX000.SetFillStyle(0);
   LegendX000.SetTextFont(42);
   LegendX000.SetBorderSize(0);
   LegendX000.AddEntry(&GX000Max68, "68% Range", "p");
   LegendX000.AddEntry(&GX000Max95, "95% Range", "p");

   TCanvas CanvasX000;
   HX000World.Draw();
   CanvasX000.SetLogx();
   CanvasX000.SetLogy();
   CanvasX000.SetGridx();
   CanvasX000.SetGridy();
   GX000Max68.Draw("p");
   GX000Max95.Draw("p");
   LegendX000.Draw();
   CanvasX000.SaveAs("Plots/ErrorInX000.png");
   CanvasX000.SaveAs("Plots/ErrorInX000.C");
   CanvasX000.SaveAs("Plots/ErrorInX000.eps");
   CanvasX000.SaveAs("Plots/ErrorInX000.pdf");
 
   TH2D HX050World("HX050World", ";N;Uncertainty", 100, 1, 2000, 100, 0.01, 1);
   HX050World.SetStats(0);

   GX050Max68.SetMarkerColor(kGreen);
   GX050Max95.SetMarkerColor(kBlue);

   TLegend LegendX050(0.5, 0.8, 0.8, 0.6);
   LegendX050.SetFillStyle(0);
   LegendX050.SetTextFont(42);
   LegendX050.SetBorderSize(0);
   LegendX050.AddEntry(&GX050Max68, "68% Range", "p");
   LegendX050.AddEntry(&GX050Max95, "95% Range", "p");

   TCanvas CanvasX050;
   HX050World.Draw();
   CanvasX050.SetLogx();
   CanvasX050.SetLogy();
   CanvasX050.SetGridx();
   CanvasX050.SetGridy();
   GX050Max68.Draw("p");
   GX050Max95.Draw("p");
   LegendX050.Draw();
   CanvasX050.SaveAs("Plots/ErrorInX050.png");
   CanvasX050.SaveAs("Plots/ErrorInX050.C");
   CanvasX050.SaveAs("Plots/ErrorInX050.eps");
   CanvasX050.SaveAs("Plots/ErrorInX050.pdf");

   TH2D HX025World("HX025World", ";N;Uncertainty", 100, 2, 2000, 100, 0.01, 1);
   HX025World.SetStats(0);

   GX025Min68.SetMarkerStyle(21);
   GX025Min95.SetMarkerStyle(21);

   GX025Min68.SetMarkerColor(kGreen);
   GX025Max68.SetMarkerColor(kGreen);
   GX025Min95.SetMarkerColor(kBlue);
   GX025Max95.SetMarkerColor(kBlue);

   TLegend LegendX025(0.5, 0.8, 0.8, 0.6);
   LegendX025.SetFillStyle(0);
   LegendX025.SetTextFont(42);
   LegendX025.SetBorderSize(0);
   LegendX025.AddEntry(&GX025Min68, "68% Range (-)", "p");
   LegendX025.AddEntry(&GX025Max68, "68% Range (+)", "p");
   LegendX025.AddEntry(&GX025Min95, "95% Range (-)", "p");
   LegendX025.AddEntry(&GX025Max95, "95% Range (+)", "p");

   TCanvas CanvasX025;
   HX025World.Draw();
   CanvasX025.SetLogx();
   CanvasX025.SetLogy();
   CanvasX025.SetGridx();
   CanvasX025.SetGridy();
   GX025Min68.Draw("p");
   GX025Max68.Draw("p");
   GX025Min95.Draw("p");
   GX025Max95.Draw("p");
   LegendX025.Draw();
   CanvasX025.SaveAs("Plots/ErrorInX025.png");
   CanvasX025.SaveAs("Plots/ErrorInX025.C");
   CanvasX025.SaveAs("Plots/ErrorInX025.eps");
   CanvasX025.SaveAs("Plots/ErrorInX025.pdf");
 
   TH2D HX010World("HX010World", ";N;Uncertainty", 100, 8, 2000, 100, 0.008, 0.5);
   HX010World.SetStats(0);

   GX010Min68.SetMarkerStyle(21);
   GX010Min95.SetMarkerStyle(21);

   GX010Min68.SetMarkerColor(kGreen);
   GX010Max68.SetMarkerColor(kGreen);
   GX010Min95.SetMarkerColor(kBlue);
   GX010Max95.SetMarkerColor(kBlue);

   TLegend LegendX010(0.5, 0.8, 0.8, 0.6);
   LegendX010.SetFillStyle(0);
   LegendX010.SetTextFont(42);
   LegendX010.SetBorderSize(0);
   LegendX010.AddEntry(&GX010Min68, "68% Range (-)", "p");
   LegendX010.AddEntry(&GX010Max68, "68% Range (+)", "p");
   LegendX010.AddEntry(&GX010Min95, "95% Range (-)", "p");
   LegendX010.AddEntry(&GX010Max95, "95% Range (+)", "p");

   TCanvas CanvasX010;
   HX010World.Draw();
   CanvasX010.SetLogx();
   CanvasX010.SetLogy();
   CanvasX010.SetGridx();
   CanvasX010.SetGridy();
   GX010Min68.Draw("p");
   GX010Max68.Draw("p");
   GX010Min95.Draw("p");
   GX010Max95.Draw("p");
   LegendX010.Draw();
   CanvasX010.SaveAs("Plots/ErrorInX010.png");
   CanvasX010.SaveAs("Plots/ErrorInX010.C");
   CanvasX010.SaveAs("Plots/ErrorInX010.eps");
   CanvasX010.SaveAs("Plots/ErrorInX010.pdf");
 
   TH2D HX005World("HX005World", ";N;Uncertainty", 100, 12, 1400, 100, 0.005, 0.5);
   HX005World.SetStats(0);

   GX005Min68.SetMarkerStyle(21);
   GX005Min95.SetMarkerStyle(21);

   GX005Min68.SetMarkerColor(kGreen);
   GX005Max68.SetMarkerColor(kGreen);
   GX005Min95.SetMarkerColor(kBlue);
   GX005Max95.SetMarkerColor(kBlue);

   TLegend LegendX005(0.5, 0.8, 0.8, 0.6);
   LegendX005.SetFillStyle(0);
   LegendX005.SetTextFont(42);
   LegendX005.SetBorderSize(0);
   LegendX005.AddEntry(&GX005Min68, "68% Range (-)", "p");
   LegendX005.AddEntry(&GX005Max68, "68% Range (+)", "p");
   LegendX005.AddEntry(&GX005Min95, "95% Range (-)", "p");
   LegendX005.AddEntry(&GX005Max95, "95% Range (+)", "p");

   TCanvas CanvasX005;
   HX005World.Draw();
   CanvasX005.SetLogx();
   CanvasX005.SetLogy();
   CanvasX005.SetGridx();
   CanvasX005.SetGridy();
   GX005Min68.Draw("p");
   GX005Max68.Draw("p");
   GX005Min95.Draw("p");
   GX005Max95.Draw("p");
   LegendX005.Draw();
   CanvasX005.SaveAs("Plots/ErrorInX005.png");
   CanvasX005.SaveAs("Plots/ErrorInX005.C");
   CanvasX005.SaveAs("Plots/ErrorInX005.eps");
   CanvasX005.SaveAs("Plots/ErrorInX005.pdf");
 
   TH2D HX002World("HX002World", ";N;Uncertainty", 100, 25, 2000, 100, 0.003, 0.1);
   HX002World.SetStats(0);

   GX002Min68.SetMarkerStyle(21);
   GX002Min95.SetMarkerStyle(21);

   GX002Min68.SetMarkerColor(kGreen);
   GX002Max68.SetMarkerColor(kGreen);
   GX002Min95.SetMarkerColor(kBlue);
   GX002Max95.SetMarkerColor(kBlue);

   TLegend LegendX002(0.5, 0.8, 0.8, 0.6);
   LegendX002.SetFillStyle(0);
   LegendX002.SetTextFont(42);
   LegendX002.SetBorderSize(0);
   LegendX002.AddEntry(&GX002Min68, "68% Range (-)", "p");
   LegendX002.AddEntry(&GX002Max68, "68% Range (+)", "p");
   LegendX002.AddEntry(&GX002Min95, "95% Range (-)", "p");
   LegendX002.AddEntry(&GX002Max95, "95% Range (+)", "p");

   TCanvas CanvasX002;
   HX002World.Draw();
   CanvasX002.SetLogx();
   CanvasX002.SetLogy();
   CanvasX002.SetGridx();
   CanvasX002.SetGridy();
   GX002Min68.Draw("p");
   GX002Max68.Draw("p");
   GX002Min95.Draw("p");
   GX002Max95.Draw("p");
   LegendX002.Draw();
   CanvasX002.SaveAs("Plots/ErrorInX002.png");
   CanvasX002.SaveAs("Plots/ErrorInX002.C");
   CanvasX002.SaveAs("Plots/ErrorInX002.eps");
   CanvasX002.SaveAs("Plots/ErrorInX002.pdf");
 
   TH2D HX001World("HX001World", ";N;Uncertainty", 100, 80, 1400, 100, 0.002, 0.1);
   HX001World.SetStats(0);

   GX001Min68.SetMarkerStyle(21);
   GX001Min95.SetMarkerStyle(21);

   GX001Min68.SetMarkerColor(kGreen);
   GX001Max68.SetMarkerColor(kGreen);
   GX001Min95.SetMarkerColor(kBlue);
   GX001Max95.SetMarkerColor(kBlue);

   TLegend LegendX001(0.5, 0.8, 0.8, 0.6);
   LegendX001.SetFillStyle(0);
   LegendX001.SetTextFont(42);
   LegendX001.SetBorderSize(0);
   LegendX001.AddEntry(&GX001Min68, "68% Range (-)", "p");
   LegendX001.AddEntry(&GX001Max68, "68% Range (+)", "p");
   LegendX001.AddEntry(&GX001Min95, "95% Range (-)", "p");
   LegendX001.AddEntry(&GX001Max95, "95% Range (+)", "p");

   TCanvas CanvasX001;
   HX001World.Draw();
   CanvasX001.SetLogx();
   CanvasX001.SetLogy();
   CanvasX001.SetGridx();
   CanvasX001.SetGridy();
   GX001Min68.Draw("p");
   GX001Max68.Draw("p");
   GX001Min95.Draw("p");
   GX001Max95.Draw("p");
   LegendX001.Draw();
   CanvasX001.SaveAs("Plots/ErrorInX001.png");
   CanvasX001.SaveAs("Plots/ErrorInX001.C");
   CanvasX001.SaveAs("Plots/ErrorInX001.eps");
   CanvasX001.SaveAs("Plots/ErrorInX001.pdf");
 
   File.Close();

   return 0;
}







