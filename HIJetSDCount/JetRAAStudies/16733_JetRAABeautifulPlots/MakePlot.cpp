#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void Divide(TGraphAsymmErrors &Graph, string FileName1, string Name1, string FileName2, string Name2);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("JetRAAPlots.pdf");
   PdfFile.AddTextPage("Jewel Jet R_{AA} Plots");

   TGraphAsymmErrors SOff, SOffDR0, SOffDR1, SOffDR2, SOffDR3;
   TGraphAsymmErrors SOn, SOnDR0, SOnDR1, SOnDR2, SOnDR3;
   TGraphAsymmErrors SBOff, SBOffDR0, SBOffDR1, SBOffDR2, SBOffDR3;
   TGraphAsymmErrors SBOn, SBOnDR0, SBOnDR1, SBOnDR2, SBOnDR3;
   TGraphAsymmErrors Q1, Q1DR0, Q1DR1, Q1DR2, Q1DR3;
   TGraphAsymmErrors QB, QBDR0, QBDR1, QBDR2, QBDR3;
   TGraphAsymmErrors Q1M, Q1MDR0, Q1MDR1, Q1MDR2, Q1MDR3;
   TGraphAsymmErrors QBM, QBMDR0, QBMDR1, QBMDR2, QBMDR3;

   Divide(SOff,     "Plots_Off_S_N.root",  "HCS",       "Plots_Vac_S_N.root",  "HCS");
   Divide(SOffDR0,  "Plots_Off_S_N.root",  "HCSSD7DR0", "Plots_Vac_S_N.root",  "HCSSD7DR0");
   Divide(SOffDR1,  "Plots_Off_S_N.root",  "HCSSD7DR1", "Plots_Vac_S_N.root",  "HCSSD7DR1");
   Divide(SOffDR2,  "Plots_Off_S_N.root",  "HCSSD7DR2", "Plots_Vac_S_N.root",  "HCSSD7DR2");
   Divide(SOffDR3,  "Plots_Off_S_N.root",  "HCSSD7DR3", "Plots_Vac_S_N.root",  "HCSSD7DR3");
   Divide(SOn,      "Plots_On_S_Y.root",   "HCS",       "Plots_Vac_S_N.root",  "HCS");
   Divide(SOnDR0,   "Plots_On_S_Y.root",   "HCSSD7DR0", "Plots_Vac_S_N.root",  "HCSSD7DR0");
   Divide(SOnDR1,   "Plots_On_S_Y.root",   "HCSSD7DR1", "Plots_Vac_S_N.root",  "HCSSD7DR1");
   Divide(SOnDR2,   "Plots_On_S_Y.root",   "HCSSD7DR2", "Plots_Vac_S_N.root",  "HCSSD7DR2");
   Divide(SOnDR3,   "Plots_On_S_Y.root",   "HCSSD7DR3", "Plots_Vac_S_N.root",  "HCSSD7DR3");
   Divide(SBOff,    "Plots_Off_SB_N.root", "HCS",       "Plots_Vac_SB_N.root", "HCS");
   Divide(SBOffDR0, "Plots_Off_SB_N.root", "HCSSD7DR0", "Plots_Vac_SB_N.root", "HCSSD7DR0");
   Divide(SBOffDR1, "Plots_Off_SB_N.root", "HCSSD7DR1", "Plots_Vac_SB_N.root", "HCSSD7DR1");
   Divide(SBOffDR2, "Plots_Off_SB_N.root", "HCSSD7DR2", "Plots_Vac_SB_N.root", "HCSSD7DR2");
   Divide(SBOffDR3, "Plots_Off_SB_N.root", "HCSSD7DR3", "Plots_Vac_SB_N.root", "HCSSD7DR3");
   Divide(SBOn,     "Plots_On_SB_Y.root",  "HCS",       "Plots_Vac_SB_N.root", "HCS");
   Divide(SBOnDR0,  "Plots_On_SB_Y.root",  "HCSSD7DR0", "Plots_Vac_SB_N.root", "HCSSD7DR0");
   Divide(SBOnDR1,  "Plots_On_SB_Y.root",  "HCSSD7DR1", "Plots_Vac_SB_N.root", "HCSSD7DR1");
   Divide(SBOnDR2,  "Plots_On_SB_Y.root",  "HCSSD7DR2", "Plots_Vac_SB_N.root", "HCSSD7DR2");
   Divide(SBOnDR3,  "Plots_On_SB_Y.root",  "HCSSD7DR3", "Plots_Vac_SB_N.root", "HCSSD7DR3");
   Divide(Q1,       "Plots_Q1_S.root",     "HCS",       "Plots_QV_S.root",     "HCS");
   Divide(Q1DR0,    "Plots_Q1_S.root",     "HCSSD7DR0", "Plots_QV_S.root",     "HCSSD7DR0");
   Divide(Q1DR1,    "Plots_Q1_S.root",     "HCSSD7DR1", "Plots_QV_S.root",     "HCSSD7DR1");
   Divide(Q1DR2,    "Plots_Q1_S.root",     "HCSSD7DR2", "Plots_QV_S.root",     "HCSSD7DR2");
   Divide(Q1DR3,    "Plots_Q1_S.root",     "HCSSD7DR3", "Plots_QV_S.root",     "HCSSD7DR3");
   Divide(QB,       "Plots_Q1_SB.root",    "HCS",       "Plots_QV_SB.root",    "HCS");
   Divide(QBDR0,    "Plots_Q1_SB.root",    "HCSSD7DR0", "Plots_QV_SB.root",    "HCSSD7DR0");
   Divide(QBDR1,    "Plots_Q1_SB.root",    "HCSSD7DR1", "Plots_QV_SB.root",    "HCSSD7DR1");
   Divide(QBDR2,    "Plots_Q1_SB.root",    "HCSSD7DR2", "Plots_QV_SB.root",    "HCSSD7DR2");
   Divide(QBDR3,    "Plots_Q1_SB.root",    "HCSSD7DR3", "Plots_QV_SB.root",    "HCSSD7DR3");
   Divide(Q1M,      "Plots_Q1_S_Merged.root",     "HCS",       "Plots_QV_S_Merged.root",     "HCS");
   Divide(Q1MDR0,   "Plots_Q1_S_Merged.root",     "HCSSD7DR0", "Plots_QV_S_Merged.root",     "HCSSD7DR0");
   Divide(Q1MDR1,   "Plots_Q1_S_Merged.root",     "HCSSD7DR1", "Plots_QV_S_Merged.root",     "HCSSD7DR1");
   Divide(Q1MDR2,   "Plots_Q1_S_Merged.root",     "HCSSD7DR2", "Plots_QV_S_Merged.root",     "HCSSD7DR2");
   Divide(Q1MDR3,   "Plots_Q1_S_Merged.root",     "HCSSD7DR3", "Plots_QV_S_Merged.root",     "HCSSD7DR3");
   Divide(QBM,      "Plots_Q1_SB_Merged.root",    "HCS",       "Plots_QV_SB_Merged.root",    "HCS");
   Divide(QBMDR0,   "Plots_Q1_SB_Merged.root",    "HCSSD7DR0", "Plots_QV_SB_Merged.root",    "HCSSD7DR0");
   Divide(QBMDR1,   "Plots_Q1_SB_Merged.root",    "HCSSD7DR1", "Plots_QV_SB_Merged.root",    "HCSSD7DR1");
   Divide(QBMDR2,   "Plots_Q1_SB_Merged.root",    "HCSSD7DR2", "Plots_QV_SB_Merged.root",    "HCSSD7DR2");
   Divide(QBMDR3,   "Plots_Q1_SB_Merged.root",    "HCSSD7DR3", "Plots_QV_SB_Merged.root",    "HCSSD7DR3");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(13);

   TCanvas C;
   C.SetLogx();

   TH2D HWorld("HWorld", ";p_{T}^{jet} (GeV);R_{AA}", 100, 99.99, 1000, 100, 0.0, 1.5);
   HWorld.SetStats(0);
   TH2D HWorldHigh("HWorldHigh", ";p_{T}^{jet} (GeV);R_{AA}", 100, 99.99, 1000, 100, 0.0, 3.0);
   HWorldHigh.SetStats(0);
   
   HWorld.Draw("axis");

   SOff.SetLineColor(kBlack);
   SOffDR0.SetLineColor(kMagenta);
   SOffDR1.SetLineColor(kRed);
   SOffDR2.SetLineColor(kBlue);
   SOffDR3.SetLineColor(kGreen);
   SOff.SetMarkerColor(kBlack);
   SOffDR0.SetMarkerColor(kMagenta);
   SOffDR1.SetMarkerColor(kRed);
   SOffDR2.SetMarkerColor(kBlue);
   SOffDR3.SetMarkerColor(kGreen);

   SOff.Draw("p");
   SOffDR0.Draw("p");
   SOffDR1.Draw("p");
   SOffDR2.Draw("p");
   SOffDR3.Draw("p");

   TLegend Legend(0.55, 0.87, 0.85, 0.60);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&SOff, "No #DeltaR cut", "lp");
   Legend.AddEntry(&SOffDR0, "#DeltaR < 0.1", "lp");
   Legend.AddEntry(&SOffDR1, "#DeltaR = 0.1-0.2", "lp");
   Legend.AddEntry(&SOffDR2, "#DeltaR = 0.2-0.3", "lp");
   Legend.AddEntry(&SOffDR3, "#DeltaR > 0.3", "lp");
   Legend.Draw();

   Latex.DrawLatex(0.15, 0.85, "JEWEL 2.2.0");
   Latex.DrawLatex(0.15, 0.80, "Recoil off 0-10%");
   Latex.DrawLatex(0.15, 0.75, "Signal only");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   C.SaveAs("Plots/Plot1.pdf");
   PdfFile.AddCanvas(C);

   HWorldHigh.Draw("axis");

   SOn.SetLineColor(kBlack);
   SOnDR0.SetLineColor(kMagenta);
   SOnDR1.SetLineColor(kRed);
   SOnDR2.SetLineColor(kBlue);
   SOnDR3.SetLineColor(kGreen);
   SOn.SetMarkerColor(kBlack);
   SOnDR0.SetMarkerColor(kMagenta);
   SOnDR1.SetMarkerColor(kRed);
   SOnDR2.SetMarkerColor(kBlue);
   SOnDR3.SetMarkerColor(kGreen);

   SOn.Draw("p");
   SOnDR0.Draw("p");
   SOnDR1.Draw("p");
   SOnDR2.Draw("p");
   SOnDR3.Draw("p");

   Legend.Draw();
   
   Latex.DrawLatex(0.15, 0.85, "JEWEL 2.2.0");
   Latex.DrawLatex(0.15, 0.80, "Recoil on 0-10%");
   Latex.DrawLatex(0.15, 0.75, "Signal only");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   C.SaveAs("Plots/Plot2.pdf");
   PdfFile.AddCanvas(C);

   HWorld.Draw("axis");

   SBOff.SetLineColor(kBlack);
   SBOffDR0.SetLineColor(kMagenta);
   SBOffDR1.SetLineColor(kRed);
   SBOffDR2.SetLineColor(kBlue);
   SBOffDR3.SetLineColor(kGreen);
   SBOff.SetMarkerColor(kBlack);
   SBOffDR0.SetMarkerColor(kMagenta);
   SBOffDR1.SetMarkerColor(kRed);
   SBOffDR2.SetMarkerColor(kBlue);
   SBOffDR3.SetMarkerColor(kGreen);

   SBOff.Draw("p");
   SBOffDR0.Draw("p");
   SBOffDR1.Draw("p");
   SBOffDR2.Draw("p");
   SBOffDR3.Draw("p");

   Legend.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "JEWEL 2.2.0");
   Latex.DrawLatex(0.15, 0.80, "Recoil off 0-10%");
   Latex.DrawLatex(0.15, 0.75, "With background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   C.SaveAs("Plots/Plot3.pdf");
   // PdfFile.AddCanvas(C);

   HWorld.Draw("axis");

   SBOn.SetLineColor(kBlack);
   SBOnDR0.SetLineColor(kMagenta);
   SBOnDR1.SetLineColor(kRed);
   SBOnDR2.SetLineColor(kBlue);
   SBOnDR3.SetLineColor(kGreen);
   SBOn.SetMarkerColor(kBlack);
   SBOnDR0.SetMarkerColor(kMagenta);
   SBOnDR1.SetMarkerColor(kRed);
   SBOnDR2.SetMarkerColor(kBlue);
   SBOnDR3.SetMarkerColor(kGreen);

   SBOn.Draw("p");
   SBOnDR0.Draw("p");
   SBOnDR1.Draw("p");
   SBOnDR2.Draw("p");
   SBOnDR3.Draw("p");

   Legend.Draw();
   
   Latex.DrawLatex(0.15, 0.85, "JEWEL 2.2.0");
   Latex.DrawLatex(0.15, 0.80, "Recoil on 0-10%");
   Latex.DrawLatex(0.15, 0.75, "With background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");
   // Latex.DrawLatex(0.15, 0.60, "#DeltaR curves not good!");

   C.SaveAs("Plots/Plot4.pdf");
   // PdfFile.AddCanvas(C);

   SOff.SetLineColor(kBlack);
   SOn.SetLineColor(kGreen);
   SBOff.SetLineColor(kBlue);
   SBOn.SetLineColor(kRed);
   SOff.SetMarkerColor(kBlack);
   SOn.SetMarkerColor(kGreen);
   SBOff.SetMarkerColor(kBlue);
   SBOn.SetMarkerColor(kRed);
   
   HWorld.Draw("axis");

   SOff.Draw("p");
   SOn.Draw("p");
   SBOff.Draw("p");
   SBOn.Draw("p");
   
   Latex.DrawLatex(0.15, 0.85, "JEWEL 2.2.0");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   TLegend Legend2(0.55, 0.87, 0.85, 0.60);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(&SOff, "S, recoil off", "lp");
   Legend2.AddEntry(&SOn, "S, recoil on", "lp");
   Legend2.AddEntry(&SBOff, "S+B, recoil off", "lp");
   Legend2.AddEntry(&SBOn, "S+B, recoil on", "lp");
   Legend2.AddEntry("", "", "");
   Legend2.Draw();

   C.SaveAs("Plots/Plot5.pdf");
   // PdfFile.AddCanvas(C);

   HWorldHigh.Draw("axis");

   Q1.SetLineColor(kBlack);
   Q1DR0.SetLineColor(kMagenta);
   Q1DR1.SetLineColor(kRed);
   Q1DR2.SetLineColor(kBlue);
   Q1DR3.SetLineColor(kGreen);
   Q1.SetMarkerColor(kBlack);
   Q1DR0.SetMarkerColor(kMagenta);
   Q1DR1.SetMarkerColor(kRed);
   Q1DR2.SetMarkerColor(kBlue);
   Q1DR3.SetMarkerColor(kGreen);

   Q1.Draw("p");
   Q1DR0.Draw("p");
   Q1DR1.Draw("p");
   Q1DR2.Draw("p");
   Q1DR3.Draw("p");

   Legend.Draw();
   
   Latex.DrawLatex(0.15, 0.85, "QPythia");
   Latex.DrawLatex(0.15, 0.80, "0-10% (#hat{p}_{T} > 40)");
   Latex.DrawLatex(0.15, 0.75, "Signal only");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   C.SaveAs("Plots/Plot6.pdf");
   PdfFile.AddCanvas(C);

   HWorldHigh.Draw("axis");

   QB.SetLineColor(kBlack);
   QBDR0.SetLineColor(kMagenta);
   QBDR1.SetLineColor(kRed);
   QBDR2.SetLineColor(kBlue);
   QBDR3.SetLineColor(kGreen);
   QB.SetMarkerColor(kBlack);
   QBDR0.SetMarkerColor(kMagenta);
   QBDR1.SetMarkerColor(kRed);
   QBDR2.SetMarkerColor(kBlue);
   QBDR3.SetMarkerColor(kGreen);

   QB.Draw("p");
   QBDR0.Draw("p");
   QBDR1.Draw("p");
   QBDR2.Draw("p");
   QBDR3.Draw("p");

   Legend.Draw();
   
   Latex.DrawLatex(0.15, 0.85, "QPythia");
   Latex.DrawLatex(0.15, 0.80, "0-10% (#hat{p}_{T} > 40)");
   Latex.DrawLatex(0.15, 0.75, "Signal + background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   C.SaveAs("Plots/Plot7.pdf");
   PdfFile.AddCanvas(C);

   HWorldHigh.Draw("axis");

   Q1M.SetLineColor(kBlack);
   Q1MDR0.SetLineColor(kMagenta);
   Q1MDR1.SetLineColor(kRed);
   Q1MDR2.SetLineColor(kBlue);
   Q1MDR3.SetLineColor(kGreen);
   Q1M.SetMarkerColor(kBlack);
   Q1MDR0.SetMarkerColor(kMagenta);
   Q1MDR1.SetMarkerColor(kRed);
   Q1MDR2.SetMarkerColor(kBlue);
   Q1MDR3.SetMarkerColor(kGreen);

   Q1M.Draw("p");
   Q1MDR0.Draw("p");
   Q1MDR1.Draw("p");
   Q1MDR2.Draw("p");
   Q1MDR3.Draw("p");

   Legend.Draw();
   
   Latex.DrawLatex(0.15, 0.85, "QPythia");
   Latex.DrawLatex(0.15, 0.80, "0-10% (#hat{p}_{T} > 80)");
   Latex.DrawLatex(0.15, 0.75, "Signal only");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   C.SaveAs("Plots/Plot8.pdf");
   PdfFile.AddCanvas(C);

   HWorldHigh.Draw("axis");

   QBM.SetLineColor(kBlack);
   QBMDR0.SetLineColor(kMagenta);
   QBMDR1.SetLineColor(kRed);
   QBMDR2.SetLineColor(kBlue);
   QBMDR3.SetLineColor(kGreen);
   QBM.SetMarkerColor(kBlack);
   QBMDR0.SetMarkerColor(kMagenta);
   QBMDR1.SetMarkerColor(kRed);
   QBMDR2.SetMarkerColor(kBlue);
   QBMDR3.SetMarkerColor(kGreen);

   QBM.Draw("p");
   QBMDR0.Draw("p");
   QBMDR1.Draw("p");
   QBMDR2.Draw("p");
   QBMDR3.Draw("p");

   Legend.Draw();
   
   Latex.DrawLatex(0.15, 0.85, "QPythia");
   Latex.DrawLatex(0.15, 0.80, "0-10% (#hat{p}_{T} > 80)");
   Latex.DrawLatex(0.15, 0.75, "Signal + background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   C.SaveAs("Plots/Plot9.pdf");
   PdfFile.AddCanvas(C);


   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void Divide(TGraphAsymmErrors &Graph, string FileName1, string Name1, string FileName2, string Name2)
{
   Graph.SetLineWidth(2);
   Graph.SetMarkerStyle(20);
   Graph.SetMarkerSize(1.4);

   TFile F1(FileName1.c_str());
   TFile F2(FileName2.c_str());

   TH1D *H1 = (TH1D *)F1.Get(Name1.c_str());
   TH1D *H2 = (TH1D *)F2.Get(Name2.c_str());

   if(H1 != NULL && H2 != NULL)
   {
      int N = H1->GetNbinsX();
      for(int i = 1; i <= N; i++)
      {
         double L = H1->GetXaxis()->GetBinLowEdge(i);
         double R = H1->GetXaxis()->GetBinUpEdge(i);
         double C = (L + R) / 2;

         double B1 = H1->GetBinContent(i);
         double B2 = H2->GetBinContent(i);
         double E1 = H1->GetBinError(i);
         double E2 = H2->GetBinError(i);

         double B = 0;
         double E = 0;

         if(B2 > 0 && B1 > 0)
         {
            B = B1 / B2;
            E = B * sqrt((E1 / B1) * (E1 / B1) + (E2 / B2) * (E2 / B2));
         }

         Graph.SetPoint(i - 1, C, B);
         Graph.SetPointError(i - 1, C - L, R - C, E, E);
      }
   }

   F2.Close();
   F1.Close();
}


