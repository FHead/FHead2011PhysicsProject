#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   int PWhat = 8;
   if(argc > 1 && argv[1][0] == 'Y')
      PWhat = 6;
   else
      PWhat = 8;

   SetThesisStyle();

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);

   TFile FPPMC0(Form("UnsmearedScaledResult/PP%dDijet.root", PWhat));
   TFile FPPMC(Form("ScaledResult/PP%dDijet.root", PWhat));
   TFile FPPData("ScaledResult/PPDataHighPTJet_NoCrossSection.root");

   string CBin[5] = {"CBin0", "CBin1", "CBin2", "CBin3", "CBin4"};
   int CBinMin[5+1] = {0, 10, 30, 50, 80, 100};
   int JetBinMin[8+1] = {1, 11, 21, 31, 41, 51, 61, 81, 101};

   for(int iC = 0; iC < 1; iC++)
   {
      TH2D *H2PPMC0 = (TH2D *)FPPMC0.Get(Form("HSDMassRecoJetPT_%s", CBin[0].c_str()));
      TH2D *H2PPMC = (TH2D *)FPPMC.Get(Form("HSDMassRecoJetPT_%s", CBin[0].c_str()));
      TH2D *H2PPData = (TH2D *)FPPData.Get(Form("HSDMassRecoJetPT_%s", CBin[0].c_str()));

      TH1D *HPPMC0X = H2PPMC0->ProjectionX(Form("HPPMC0X%d", iC), 1, 100);
      TH1D *HPPMCX = H2PPMC->ProjectionX(Form("HPPMCX%d", iC), 1, 100);
      TH1D *HPPDataX = H2PPData->ProjectionX(Form("HPPDataX%d", iC), 1, 100);

      TH2D *H2PPMC0Weighted = NULL;
      TH2D *H2PPMCWeighted = NULL;

      H2PPMC0Weighted = (TH2D *)H2PPMC0->Clone(Form("H2PPMC0_HSDMassRecoJetPT_%s_Weighted", CBin[0].c_str()));
      H2PPMCWeighted = (TH2D *)H2PPMC->Clone(Form("H2PPMC_HSDMassRecoJetPT_%s_Weighted", CBin[0].c_str()));

      for(int iX = 1; iX <= H2PPMC->GetNbinsX(); iX++)
      {
         for(int iY = 1; iY <= H2PPMC->GetNbinsY(); iY++)
         {
            H2PPMC0Weighted->SetBinContent(iX, iY, H2PPMC0->GetBinContent(iX, iY) * HPPDataX->GetBinContent(iX) / HPPMC0X->GetBinContent(iX));
            H2PPMCWeighted->SetBinContent(iX, iY, H2PPMC->GetBinContent(iX, iY) * HPPDataX->GetBinContent(iX) / HPPMCX->GetBinContent(iX));
         }
      }

      TH1D *HPPMC0WeightedX = H2PPMC0Weighted->ProjectionX(Form("HPPMC0WeightedX", iC), 1, 100);
      TH1D *HPPMCWeightedX = H2PPMCWeighted->ProjectionX(Form("HPPMCWeightedX", iC), 1, 100);

      HPPMC0X->SetLineColor(kYellow - 3);
      HPPMCX->SetLineColor(kRed);
      HPPMC0WeightedX->SetLineColor(kYellow + 3);
      HPPMCWeightedX->SetLineColor(kRed + 3);
      HPPDataX->SetLineColor(kGreen - 3);
      
      HPPMC0X->Scale(1 / HPPMC0X->Integral(1, 100));
      HPPMCX->Scale(1 / HPPMCX->Integral(1, 100));
      HPPDataX->Scale(1 / HPPDataX->Integral(1, 100));
      HPPMC0WeightedX->Scale(1 / HPPMC0WeightedX->Integral(1, 100));
      HPPMCWeightedX->Scale(1 / HPPMCWeightedX->Integral(1, 100));

      TH2D HPTWorld("HPTWorld", ";Jet PT;a.u.", 100, 80, 500, 100, 1e-6, 100);
      HPTWorld.SetStats(0);

      TCanvas PTCanvas;

      HPTWorld.Draw();
      HPPMC0X->Draw("same");
      HPPMCX->Draw("same");
      HPPDataX->Draw("same");
      HPPMC0WeightedX->Draw("same");
      HPPMCWeightedX->Draw("same");
         
      TLegend PTLegend(0.3, 0.8, 0.6, 0.5);
      PTLegend.SetBorderSize(0);
      PTLegend.SetFillStyle(0);
      PTLegend.SetTextFont(42);
      PTLegend.SetTextSize(0.035);
      PTLegend.AddEntry(HPPMC0X, "pp MC", "l");
      PTLegend.AddEntry(HPPMCX, "pp MC (smeared)", "l");
      PTLegend.AddEntry(HPPMC0WeightedX, "pp MC (weighted)", "l");
      PTLegend.AddEntry(HPPMCWeightedX, "pp MC (smeared, weighted)", "l");
      PTLegend.AddEntry(HPPDataX, "pp Data", "l");
      PTLegend.Draw();

      PTCanvas.SetLogy();

      Latex.DrawLatex(0.10, 0.92, Form("pp, Pythia%d", PWhat));

      PTCanvas.SaveAs(Form("Plots/Pythia%d_JetPTSpectrum%d.png", PWhat, iC));
      PTCanvas.SaveAs(Form("Plots/Pythia%d_JetPTSpectrum%d.C", PWhat, iC));
      PTCanvas.SaveAs(Form("Plots/Pythia%d_JetPTSpectrum%d.eps", PWhat, iC));
      PTCanvas.SaveAs(Form("Plots/Pythia%d_JetPTSpectrum%d.pdf", PWhat, iC));

      for(int iJ = 0; iJ < 8; iJ++)
      {
         TH1D *HPPMC0 = H2PPMC0->ProjectionY(Form("HPPMC0%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);
         TH1D *HPPMC = H2PPMC->ProjectionY(Form("HPPMC%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);
         TH1D *HPPMC0Weighted = H2PPMC0Weighted->ProjectionY(Form("HPPMC0Weighted%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);
         TH1D *HPPMCWeighted = H2PPMCWeighted->ProjectionY(Form("HPPMCWeighted%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);
         TH1D *HPPData = H2PPData->ProjectionY(Form("HPPData%d%d", iC, iJ), JetBinMin[iJ], JetBinMin[iJ+1] - 1);

         double PTMin = H2PPMC->GetXaxis()->GetBinLowEdge(JetBinMin[iJ]);
         double PTMax = H2PPMC->GetXaxis()->GetBinLowEdge(JetBinMin[iJ+1]);

         cout << PTMin << " " << PTMax << endl;

         HPPMC0->SetLineColor(kYellow - 3);
         HPPMC->SetLineColor(kRed);
         HPPMC0Weighted->SetLineColor(kYellow + 3);
         HPPMCWeighted->SetLineColor(kRed + 3);
         HPPData->SetLineColor(kGreen - 3);

         HPPMC0->Scale(1 / HPPMC0->Integral());
         HPPMC->Scale(1 / HPPMC->Integral());
         HPPMC0Weighted->Scale(1 / HPPMC0Weighted->Integral());
         HPPMCWeighted->Scale(1 / HPPMCWeighted->Integral());
         HPPData->Scale(1 / HPPData->Integral());

         TH2D HWorld("HWorld",
            Form("Jet PT %.0f-%.0f;Jet Mass;a.u.", PTMin, PTMax),
            100, 0, 80, 100, 0, 0.1);
         HWorld.SetStats(0);

         TCanvas Canvas;

         HWorld.Draw();
         HPPMC0->Draw("same");
         HPPMC->Draw("same");
         HPPMC0Weighted->Draw("same");
         HPPMCWeighted->Draw("same");
         HPPData->Draw("same");

         TLegend Legend(0.3, 0.8, 0.6, 0.5);
         Legend.SetBorderSize(0);
         Legend.SetFillStyle(0);
         Legend.SetTextFont(42);
         Legend.SetTextSize(0.035);
         Legend.AddEntry(HPPMC0, "pp MC", "l");
         Legend.AddEntry(HPPMC, "pp MC (smeared)", "l");
         Legend.AddEntry(HPPMC0Weighted, "pp MC (weighted)", "l");
         Legend.AddEntry(HPPMCWeighted, "pp MC (smeared, weighted)", "l");
         Legend.AddEntry(HPPData, "pp Data", "l");
         Legend.Draw();
      
         Latex.DrawLatex(0.10, 0.92, Form("pp, Pythia%d", PWhat));

         Canvas.SaveAs(Form("Plots/Pythia%d_MassProjectionPlots%d%d.png", PWhat, iC, iJ));
         Canvas.SaveAs(Form("Plots/Pythia%d_MassProjectionPlots%d%d.C"  , PWhat, iC, iJ));
         Canvas.SaveAs(Form("Plots/Pythia%d_MassProjectionPlots%d%d.eps", PWhat, iC, iJ));
         Canvas.SaveAs(Form("Plots/Pythia%d_MassProjectionPlots%d%d.pdf", PWhat, iC, iJ));
      }
      
      delete H2PPMC0Weighted;
      delete H2PPMCWeighted;
   }

   FPPData.Close();
   FPPMC.Close();
   FPPMC0.Close();

   return 0;
}




