#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile FAA6MC("ScaledResult/AA6Dijet.root");
   TFile FAA8MC("ScaledResult/AA8Dijet.root");
   TFile FAAData("ScaledResult/AAData_NoCrossSection.root");
   TFile FPP6MC("ScaledResult/PP6Dijet.root");
   TFile FPP8MC("ScaledResult/PP8Dijet.root");
   TFile FPPData("ScaledResult/PPDataHighPTJet_NoCrossSection.root");

   string CBin[5] = {"CBin0", "CBin1", "CBin2", "CBin3", "CBin4"};
   int CBinMin[5+1] = {0, 10, 30, 50, 80, 100};
   int JetBinMin[8+1] = {1, 11, 21, 31, 41, 51, 61, 81, 101};

   for(int iC = 0; iC < 5; iC++)
   {
      TH2D *H2AA6MC = (TH2D *)FAA6MC.Get(Form("HSDMassRecoJetPT_%s", CBin[iC].c_str()));
      TH2D *H2AA8MC = (TH2D *)FAA8MC.Get(Form("HSDMassRecoJetPT_%s", CBin[iC].c_str()));
      TH2D *H2AAData = (TH2D *)FAAData.Get(Form("HSDMassRecoJetPT_%s", CBin[iC].c_str()));
      TH2D *H2PP6MC = (TH2D *)FPP6MC.Get(Form("HSDMassRecoJetPT_%s", CBin[0].c_str()));
      TH2D *H2PP8MC = (TH2D *)FPP8MC.Get(Form("HSDMassRecoJetPT_%s", CBin[0].c_str()));
      TH2D *H2PPData = (TH2D *)FPPData.Get(Form("HSDMassRecoJetPT_%s", CBin[0].c_str()));

      for(int iJ = 0; iJ < 8; iJ++)
      {
         TH1D *HAA6MC = H2AA6MC->ProjectionY(Form("HAA6MC%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);
         TH1D *HAA8MC = H2AA8MC->ProjectionY(Form("HAA8MC%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);
         TH1D *HAAData = H2AAData->ProjectionY(Form("HAAData%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);
         TH1D *HPP6MC = H2PP6MC->ProjectionY(Form("HPP6MC%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);
         TH1D *HPP8MC = H2PP8MC->ProjectionY(Form("HPP8MC%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);
         TH1D *HPPData = H2PPData->ProjectionY(Form("HPPData%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);

         double PTMin = H2AA6MC->GetXaxis()->GetBinLowEdge(JetBinMin[iJ]);
         double PTMax = H2AA8MC->GetXaxis()->GetBinLowEdge(JetBinMin[iJ+1]);

         cout << PTMin << " " << PTMax << endl;

         HAA6MC->SetLineColor(kBlack);
         HAA8MC->SetLineColor(kCyan - 3);
         HAAData->SetLineColor(kBlue);
         HPP6MC->SetLineColor(kOrange);
         HPP8MC->SetLineColor(kRed);
         HPPData->SetLineColor(kGreen - 3);

         HAA6MC->Rebin(2);
         HAA8MC->Rebin(2);
         HAAData->Rebin(2);
         HPP6MC->Rebin(2);
         HPP8MC->Rebin(2);
         HPPData->Rebin(2);

         HAA6MC->Scale(1 / HAA6MC->Integral() / 2);
         HAA8MC->Scale(1 / HAA8MC->Integral() / 2);
         HAAData->Scale(1 / HAAData->Integral() / 2);
         HPP6MC->Scale(1 / HPP6MC->Integral() / 2);
         HPP8MC->Scale(1 / HPP8MC->Integral() / 2);
         HPPData->Scale(1 / HPPData->Integral() / 2);

         TH2D HWorld("HWorld",
            Form("Centrality %d-%d, Jet PT %.0f-%.0f;Jet Mass;a.u.", CBinMin[iC], CBinMin[iC+1], PTMin, PTMax),
            100, 0, 80, 100, 0, 0.1);
         HWorld.SetStats(0);

         TCanvas Canvas;

         HWorld.Draw();
         HAA6MC->Draw("same");
         HAA8MC->Draw("same");
         HAAData->Draw("same");
         HPP6MC->Draw("same");
         HPP8MC->Draw("same");
         HPPData->Draw("same");

         TLegend Legend(0.45, 0.8, 0.75, 0.5);
         Legend.SetBorderSize(0);
         Legend.SetFillStyle(0);
         Legend.SetTextFont(42);
         Legend.SetTextSize(0.035);
         Legend.AddEntry(HAA6MC, "PbPb MC (PYTHIA 6)", "l");
         Legend.AddEntry(HAA8MC, "PbPb MC (PYTHIA 8)", "l");
         Legend.AddEntry(HAAData, "PbPb Data", "l");
         Legend.AddEntry(HPP6MC, "pp MC (PYTHIA 6)", "l");
         Legend.AddEntry(HPP8MC, "pp MC (PYTHIA 8)", "l");
         Legend.AddEntry(HPPData, "pp Data", "l");
         Legend.Draw();

         Canvas.SaveAs(Form("Plots/MassProjectionPlots%d%d.png", iC, iJ));
         Canvas.SaveAs(Form("Plots/MassProjectionPlots%d%d.C", iC, iJ));
         Canvas.SaveAs(Form("Plots/MassProjectionPlots%d%d.eps", iC, iJ));
         Canvas.SaveAs(Form("Plots/MassProjectionPlots%d%d.pdf", iC, iJ));
      }
   }

   FPPData.Close();
   FPP8MC.Close();
   FPP6MC.Close();
   FAAData.Close();
   FAA8MC.Close();
   FAA6MC.Close();

   return 0;
}




