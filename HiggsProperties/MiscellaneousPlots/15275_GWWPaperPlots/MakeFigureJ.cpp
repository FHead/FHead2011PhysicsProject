#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   TFile FileH("FigureHGraphs.root");
   TFile FileF("FigureFGraphs.root");

   TGraphAsymmErrors *G[4];

   G[0] = (TGraphAsymmErrors *)FileH.Get("JobBoth_SMVV_J");
   G[1] = (TGraphAsymmErrors *)FileH.Get("JobBoth_5plet_J");
   G[2] = (TGraphAsymmErrors *)FileF.Get("JobBoth_SMVV_J_Prior");
   G[3] = (TGraphAsymmErrors *)FileF.Get("JobBoth_5plet_J_Prior");

   string Labels1[] = {"SM,", "5plet,", "SM,", "5plet,"};
   string Labels2[] =
   {
      "y_{t} fixed", "y_{t} fixed",
      "y_{t} integrated", "y_{t} integrated",
   };
   int BandColors[] = {kMagenta - 9, kGreen - 9, kMagenta + 2, kGreen + 2};
   int MarkerColors[] = {kViolet - 6, kSpring - 6, kViolet + 3, kGreen + 4};

   for(int i = 0; i < 4; i++)
   {
      if(G[i] == NULL)
         continue;

      G[i]->SetLineColor(BandColors[i]);
      G[i]->SetLineWidth(10);
      G[i]->SetMarkerColor(MarkerColors[i]);
      G[i]->SetMarkerStyle(8);
   }

   int L[11] = {25, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
   double Bins[9] = {0};
   for(int i = 0; i < 9; i++)
      Bins[i] = log(L[i] / sqrt(2));

   for(int i = 0; i < 8; i++)
   {
      double x, y;
      G[0]->GetPoint(i, x, y);
      x = log(L[i] / 1.1 / 1.1);
      G[0]->SetPoint(i, x, y);
      G[1]->GetPoint(i, x, y);
      x = log(L[i] / 1.1);
      G[1]->SetPoint(i, x, y);
      G[2]->GetPoint(i, x, y);
      x = log(L[i]);
      G[2]->SetPoint(i, x, y);
      G[3]->GetPoint(i, x, y);
      x = log(L[i] * 1.1);
      G[3]->SetPoint(i, x, y);
   }

   TH2D HWorld("HWorld", ";Luminosity (fb^{-1});p-value", 8, Bins, 100, 0, 1);
   HWorld.SetStats(0);
   for(int i = 1; i <= 11 && i <= HWorld.GetNbinsX(); i++)
      HWorld.GetXaxis()->SetBinLabel(i, Form("%d", L[i-1]));
   HWorld.GetXaxis()->SetTickLength(0);

   TCanvas C;
   HWorld.Draw();

   for(int i = 0; i < 4; i++)
      if(G[i] != NULL)
         G[i]->Draw("pz");

   TLegend Legend1(0.65, 0.23, 0.85, 0.40);
   TLegend Legend2(0.65, 0.40, 0.85, 0.57);
   Legend1.SetTextFont(42);
   Legend1.SetFillStyle(0);
   Legend1.SetTextSize(0.03);
   Legend2.SetTextFont(42);
   Legend2.SetFillStyle(0);
   Legend2.SetTextSize(0.03);
   for(int i = 0; i < 4; i++)
   {
      if(i % 2 == 0)
      {
         Legend1.AddEntry(G[i], Labels1[i].c_str(), "pl");
         Legend1.AddEntry("", Labels2[i].c_str(), "");
      }
      else
      {
         Legend2.AddEntry(G[i], Labels1[i].c_str(), "pl");
         Legend2.AddEntry("", Labels2[i].c_str(), "");
      }
   }
   Legend1.Draw();
   Legend2.Draw();

   TGraph G0;
   G0.SetPoint(0, 0, 0);
   G0.SetPoint(1, 100, 0);
   G0.Draw("l");

   C.SaveAs("Plots/FigureJ.png");
   C.SaveAs("Plots/FigureJ.C");
   C.SaveAs("Plots/FigureJ.eps");
   C.SaveAs("Plots/FigureJ.pdf");

   FileF.Close();
   FileH.Close();

   return 0;
}








