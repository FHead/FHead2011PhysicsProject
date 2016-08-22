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
   if(argc > 2)
   {
      cerr << "Usage: " << argv[0] << " Suffix" << endl;
      return -1;
   }

   string Suffix = "";
   if(argc == 2)
      Suffix = argv[1];

   SetThesisStyle();

   TFile File("FigureGGraphs.root");

   TGraphAsymmErrors *G[8];

   G[0] = (TGraphAsymmErrors *)File.Get(("JobBothS_SMVV_A" + Suffix).c_str());
   G[1] = (TGraphAsymmErrors *)File.Get(("JobBothS_SMVV_J" + Suffix).c_str());
   G[2] = (TGraphAsymmErrors *)File.Get(("JobBothS_5plet_A" + Suffix).c_str());
   G[3] = (TGraphAsymmErrors *)File.Get(("JobBothS_5plet_J" + Suffix).c_str());
   G[4] = (TGraphAsymmErrors *)File.Get(("JobBoth_SMVV_A" + Suffix).c_str());
   G[5] = (TGraphAsymmErrors *)File.Get(("JobBoth_SMVV_J" + Suffix).c_str());
   G[6] = (TGraphAsymmErrors *)File.Get(("JobBoth_5plet_A" + Suffix).c_str());
   G[7] = (TGraphAsymmErrors *)File.Get(("JobBoth_5plet_J" + Suffix).c_str());

   string Labels[] =
   {
      "S, SM, A", "S, SM, J",
      "S, H5, A", "S, H5, J",
      "S+B, SM, A", "S+B, SM, J",
      "S+B, H5, A", "S+B, H5, J"
   };
   int Colors[] = {kBlack, kBlue, kRed, kMagenta, kGreen,
      kYellow, kCyan, kMagenta + 3};

   for(int i = 0; i < 8; i++)
   {
      if(G[i] == NULL)
         continue;

      G[i]->SetLineColor(Colors[i]);
      G[i]->SetMarkerColor(Colors[i]);
      G[i]->SetMarkerStyle(8);
   }

   int L[11] = {25, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
   double Bins[9] = {0};
   for(int i = 0; i < 9; i++)
      Bins[i] = log(L[i] / sqrt(2));

   TH2D HWorld("HWorld", ";Luminosity (fb^{-1});Effective #sigma", 8, Bins, 100, -2, 3);
   HWorld.SetStats(0);
   for(int i = 1; i <= 11 && i <= HWorld.GetNbinsX(); i++)
      HWorld.GetXaxis()->SetBinLabel(i, Form("%d", L[i-1]));
   HWorld.GetXaxis()->SetTickLength(0);

   TCanvas C;
   HWorld.Draw();

   for(int i = 0; i < 8; i++)
      if(G[i] != NULL)
         G[i]->Draw("p");

   TLegend Legend1(0.15, 0.85, 0.30, 0.60);
   TLegend Legend2(0.30, 0.85, 0.45, 0.60);
   Legend1.SetTextFont(42);
   Legend1.SetFillStyle(0);
   Legend1.SetTextSize(0.03);
   Legend2.SetTextFont(42);
   Legend2.SetFillStyle(0);
   Legend2.SetTextSize(0.03);
   for(int i = 0; i < 4; i++)
      Legend1.AddEntry(G[i], Labels[i].c_str(), "pl");
   for(int i = 4; i < 8; i++)
      Legend2.AddEntry(G[i], Labels[i].c_str(), "pl");
   Legend1.Draw();
   Legend2.Draw();

   TGraph G0;
   G0.SetPoint(0, 0, 0);
   G0.SetPoint(1, 100, 0);
   G0.Draw("l");

   C.SaveAs(("Plots/FigureG" + Suffix + ".png").c_str());
   C.SaveAs(("Plots/FigureG" + Suffix + ".C").c_str());
   C.SaveAs(("Plots/FigureG" + Suffix + ".eps").c_str());
   C.SaveAs(("Plots/FigureG" + Suffix + ".pdf").c_str());

   File.Close();

   return 0;
}








