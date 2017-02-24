#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TGraph.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile FPPData("ScaledResult/PPDataHighPTJet_NoCrossSection.root");
   TFile FPP6("ScaledResult/PP6Dijet.root");
   TFile FPP8("ScaledResult/PP8Dijet.root");
   TFile FAAData("ScaledResult/AAData_NoCrossSection.root");
   TFile FAA6("ScaledResult/AA6Dijet.root");
   TFile FAA8("ScaledResult/AA8Dijet.root");

   string CBin[5] = {"CBin0", "CBin1", "CBin2", "CBin3", "CBin4"};
   string PTBin[7] = {"PTBin0", "PTBin1", "PTBin2", "PTBin3", "PTBin4", "PTBin5", "PTBin6"};

   int CBinMin[5+1] = {0, 10, 30, 50, 80, 100};
   int PTBinMin[7+1] = {80, 100, 120, 140, 160, 200, 300, 500};

   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 7; j++)
      {
         TH1D *HPPData = (TH1D *)FPPData.Get(Form("HSDMass_%s_%s", CBin[i].c_str(), PTBin[j].c_str()));
         TH1D *HPP6 = (TH1D *)FPP6.Get(Form("HSDMass_%s_%s", CBin[i].c_str(), PTBin[j].c_str()));
         TH1D *HPP8 = (TH1D *)FPP8.Get(Form("HSDMass_%s_%s", CBin[i].c_str(), PTBin[j].c_str()));
         TH1D *HAAData = (TH1D *)FAAData.Get(Form("HSDMass_%s_%s", CBin[i].c_str(), PTBin[j].c_str()));
         TH1D *HAA6 = (TH1D *)FAA6.Get(Form("HSDMass_%s_%s", CBin[i].c_str(), PTBin[j].c_str()));
         TH1D *HAA8 = (TH1D *)FAA8.Get(Form("HSDMass_%s_%s", CBin[i].c_str(), PTBin[j].c_str()));

         HPPData->Rebin(4);
         HPP6->Rebin(4);
         HPP8->Rebin(4);
         HAAData->Rebin(4);
         HAA6->Rebin(4);
         HAA8->Rebin(4);

         HPPData->Scale(1.0 / HPPData->Integral());
         HPP6->Scale(1.0 / HPP6->Integral());
         HPP8->Scale(1.0 / HPP8->Integral());
         HAAData->Scale(1.0 / HAAData->Integral());
         HAA6->Scale(1.0 / HAA6->Integral());
         HAA8->Scale(1.0 / HAA8->Integral());

         HPP6->Divide(HPPData);
         HPP8->Divide(HPPData);
         HAA6->Divide(HAAData);
         HAA8->Divide(HAAData);

         HPP6->SetLineColor(kRed);
         HPP8->SetLineColor(kBlue);
         HAA6->SetLineColor(kBlack);
         HAA8->SetLineColor(kGreen);

         HPP6->SetMarkerColor(kRed);
         HPP8->SetMarkerColor(kBlue);
         HAA6->SetMarkerColor(kBlack);
         HAA8->SetMarkerColor(kGreen);

         HPP6->SetMarkerStyle(11);
         HPP8->SetMarkerStyle(11);
         HAA6->SetMarkerStyle(11);
         HAA8->SetMarkerStyle(11);

         TCanvas C;

         TH2D HWorld("HWorld", ";SD Mass;MC/Data", 100, 0, 100, 100, 0, 8);
         HWorld.SetStats(0);

         HWorld.Draw();
         if(i == 0)
         {
            HPP6->Draw("same x");
            HPP8->Draw("same x");
         }
         HAA6->Draw("same x");
         HAA8->Draw("same x");

         TLegend Legend(0.5, 0.8, 0.8, 0.6);
         Legend.SetTextFont(42);
         Legend.SetTextSize(0.035);
         Legend.SetBorderSize(0);
         Legend.SetFillStyle(0);
         if(i == 0)
         {
            Legend.AddEntry(HPP6, "PP6", "lp");
            Legend.AddEntry(HPP8, "PP8", "lp");
         }
         else
         {
            Legend.AddEntry("", "", "");
            Legend.AddEntry("", "", "");
         }
         Legend.AddEntry(HAA6, "AA6", "lp");
         Legend.AddEntry(HAA8, "AA8", "lp");
         Legend.Draw();

         TGraph G;
         G.SetPoint(0, 0, 1);
         G.SetPoint(1, 10000, 1);
         G.Draw("l");

         C.SaveAs(Form("Plots/MCDataRatio_%d%d.png", i, j));
         C.SaveAs(Form("Plots/MCDataRatio_%d%d.C", i, j));
         C.SaveAs(Form("Plots/MCDataRatio_%d%d.eps", i, j));
         C.SaveAs(Form("Plots/MCDataRatio_%d%d.pdf", i, j));
      }
   }

   FAA8.Close();
   FAA6.Close();
   FAAData.Close();
   FPP8.Close();
   FPP6.Close();
   FPPData.Close();

   return 0;
}





