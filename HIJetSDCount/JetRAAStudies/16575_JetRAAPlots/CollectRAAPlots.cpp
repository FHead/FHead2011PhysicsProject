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
   PdfFile.AddTextPage("Jewel & QPythia Jet R_{AA} Plots");

   TGraphAsymmErrors SOff, SOffDR0, SOffDR1, SOffDR2, SOffDR3;
   TGraphAsymmErrors SOn, SOnDR0, SOnDR1, SOnDR2, SOnDR3;
   TGraphAsymmErrors SBOff, SBOffDR0, SBOffDR1, SBOffDR2, SBOffDR3;
   TGraphAsymmErrors SBOn, SBOnDR0, SBOnDR1, SBOnDR2, SBOnDR3;
   TGraphAsymmErrors QS1, QS1DR0, QS1DR1, QS1DR2, QS1DR3;
   TGraphAsymmErrors QSB1, QSB1DR0, QSB1DR1, QSB1DR2, QSB1DR3;
   TGraphAsymmErrors QS2, QS2DR0, QS2DR1, QS2DR2, QS2DR3;
   TGraphAsymmErrors QSB2, QSB2DR0, QSB2DR1, QSB2DR2, QSB2DR3;
   TGraphAsymmErrors QS4, QS4DR0, QS4DR1, QS4DR2, QS4DR3;
   TGraphAsymmErrors QSB4, QSB4DR0, QSB4DR1, QSB4DR2, QSB4DR3;

   Divide(SOff,     "Plots_Off_S_N.root",       "HCS",       "Plots_Vac_S_N.root",        "HCS");
   Divide(SOffDR0,  "Plots_Off_S_N.root",       "HCSSD7DR0", "Plots_Vac_S_N.root",        "HCSSD7DR0");
   Divide(SOffDR1,  "Plots_Off_S_N.root",       "HCSSD7DR1", "Plots_Vac_S_N.root",        "HCSSD7DR1");
   Divide(SOffDR2,  "Plots_Off_S_N.root",       "HCSSD7DR2", "Plots_Vac_S_N.root",        "HCSSD7DR2");
   Divide(SOffDR3,  "Plots_Off_S_N.root",       "HCSSD7DR3", "Plots_Vac_S_N.root",        "HCSSD7DR3");
   Divide(SOn,      "Plots_On_S_Y.root",        "HCS",       "Plots_Vac_S_Y.root",        "HCS");
   Divide(SOnDR0,   "Plots_On_S_Y.root",        "HCSSD7DR0", "Plots_Vac_S_Y.root",        "HCSSD7DR0");
   Divide(SOnDR1,   "Plots_On_S_Y.root",        "HCSSD7DR1", "Plots_Vac_S_Y.root",        "HCSSD7DR1");
   Divide(SOnDR2,   "Plots_On_S_Y.root",        "HCSSD7DR2", "Plots_Vac_S_Y.root",        "HCSSD7DR2");
   Divide(SOnDR3,   "Plots_On_S_Y.root",        "HCSSD7DR3", "Plots_Vac_S_Y.root",        "HCSSD7DR3");
   Divide(SBOff,    "Plots_Off_SB_N.root",      "HCS",       "Plots_Vac_SB_N.root",       "HCS");
   Divide(SBOffDR0, "Plots_Off_SB_N.root",      "HCSSD7DR0", "Plots_Vac_SB_N.root",       "HCSSD7DR0");
   Divide(SBOffDR1, "Plots_Off_SB_N.root",      "HCSSD7DR1", "Plots_Vac_SB_N.root",       "HCSSD7DR1");
   Divide(SBOffDR2, "Plots_Off_SB_N.root",      "HCSSD7DR2", "Plots_Vac_SB_N.root",       "HCSSD7DR2");
   Divide(SBOffDR3, "Plots_Off_SB_N.root",      "HCSSD7DR3", "Plots_Vac_SB_N.root",       "HCSSD7DR3");
   Divide(SBOn,     "Plots_On_SB_Y.root",       "HCS",       "Plots_Vac_SB_Y.root",       "HCS");
   Divide(SBOnDR0,  "Plots_On_SB_Y.root",       "HCSSD7DR0", "Plots_Vac_SB_Y.root",       "HCSSD7DR0");
   Divide(SBOnDR1,  "Plots_On_SB_Y.root",       "HCSSD7DR1", "Plots_Vac_SB_Y.root",       "HCSSD7DR1");
   Divide(SBOnDR2,  "Plots_On_SB_Y.root",       "HCSSD7DR2", "Plots_Vac_SB_Y.root",       "HCSSD7DR2");
   Divide(SBOnDR3,  "Plots_On_SB_Y.root",       "HCSSD7DR3", "Plots_Vac_SB_Y.root",       "HCSSD7DR3");
   Divide(QS1,      "Plots_QPythia_Q1_N.root",  "HCS",       "Plots_QPythia_Vac_N.root",  "HCS");
   Divide(QS1DR0,   "Plots_QPythia_Q1_N.root",  "HCSSD7DR0", "Plots_QPythia_Vac_N.root",  "HCSSD7DR0");
   Divide(QS1DR1,   "Plots_QPythia_Q1_N.root",  "HCSSD7DR1", "Plots_QPythia_Vac_N.root",  "HCSSD7DR1");
   Divide(QS1DR2,   "Plots_QPythia_Q1_N.root",  "HCSSD7DR2", "Plots_QPythia_Vac_N.root",  "HCSSD7DR2");
   Divide(QS1DR3,   "Plots_QPythia_Q1_N.root",  "HCSSD7DR3", "Plots_QPythia_Vac_N.root",  "HCSSD7DR3");
   Divide(QSB1,     "Plots_QPythia_QB1_N.root", "HCS",       "Plots_QPythia_VacB_N.root", "HCS");
   Divide(QSB1DR0,  "Plots_QPythia_QB1_N.root", "HCSSD7DR0", "Plots_QPythia_VacB_N.root", "HCSSD7DR0");
   Divide(QSB1DR1,  "Plots_QPythia_QB1_N.root", "HCSSD7DR1", "Plots_QPythia_VacB_N.root", "HCSSD7DR1");
   Divide(QSB1DR2,  "Plots_QPythia_QB1_N.root", "HCSSD7DR2", "Plots_QPythia_VacB_N.root", "HCSSD7DR2");
   Divide(QSB1DR3,  "Plots_QPythia_QB1_N.root", "HCSSD7DR3", "Plots_QPythia_VacB_N.root", "HCSSD7DR3");
   Divide(QS2,      "Plots_QPythia_Q2_N.root",  "HCS",       "Plots_QPythia_Vac_N.root",  "HCS");
   Divide(QS2DR0,   "Plots_QPythia_Q2_N.root",  "HCSSD7DR0", "Plots_QPythia_Vac_N.root",  "HCSSD7DR0");
   Divide(QS2DR1,   "Plots_QPythia_Q2_N.root",  "HCSSD7DR1", "Plots_QPythia_Vac_N.root",  "HCSSD7DR1");
   Divide(QS2DR2,   "Plots_QPythia_Q2_N.root",  "HCSSD7DR2", "Plots_QPythia_Vac_N.root",  "HCSSD7DR2");
   Divide(QS2DR3,   "Plots_QPythia_Q2_N.root",  "HCSSD7DR3", "Plots_QPythia_Vac_N.root",  "HCSSD7DR3");
   Divide(QSB2,     "Plots_QPythia_QB2_N.root", "HCS",       "Plots_QPythia_VacB_N.root", "HCS");
   Divide(QSB2DR0,  "Plots_QPythia_QB2_N.root", "HCSSD7DR0", "Plots_QPythia_VacB_N.root", "HCSSD7DR0");
   Divide(QSB2DR1,  "Plots_QPythia_QB2_N.root", "HCSSD7DR1", "Plots_QPythia_VacB_N.root", "HCSSD7DR1");
   Divide(QSB2DR2,  "Plots_QPythia_QB2_N.root", "HCSSD7DR2", "Plots_QPythia_VacB_N.root", "HCSSD7DR2");
   Divide(QSB2DR3,  "Plots_QPythia_QB2_N.root", "HCSSD7DR3", "Plots_QPythia_VacB_N.root", "HCSSD7DR3");
   Divide(QS4,      "Plots_QPythia_Q4_N.root",  "HCS",       "Plots_QPythia_Vac_N.root",  "HCS");
   Divide(QS4DR0,   "Plots_QPythia_Q4_N.root",  "HCSSD7DR0", "Plots_QPythia_Vac_N.root",  "HCSSD7DR0");
   Divide(QS4DR1,   "Plots_QPythia_Q4_N.root",  "HCSSD7DR1", "Plots_QPythia_Vac_N.root",  "HCSSD7DR1");
   Divide(QS4DR2,   "Plots_QPythia_Q4_N.root",  "HCSSD7DR2", "Plots_QPythia_Vac_N.root",  "HCSSD7DR2");
   Divide(QS4DR3,   "Plots_QPythia_Q4_N.root",  "HCSSD7DR3", "Plots_QPythia_Vac_N.root",  "HCSSD7DR3");
   Divide(QSB4,     "Plots_QPythia_QB4_N.root", "HCS",       "Plots_QPythia_VacB_N.root", "HCS");
   Divide(QSB4DR0,  "Plots_QPythia_QB4_N.root", "HCSSD7DR0", "Plots_QPythia_VacB_N.root", "HCSSD7DR0");
   Divide(QSB4DR1,  "Plots_QPythia_QB4_N.root", "HCSSD7DR1", "Plots_QPythia_VacB_N.root", "HCSSD7DR1");
   Divide(QSB4DR2,  "Plots_QPythia_QB4_N.root", "HCSSD7DR2", "Plots_QPythia_VacB_N.root", "HCSSD7DR2");
   Divide(QSB4DR3,  "Plots_QPythia_QB4_N.root", "HCSSD7DR3", "Plots_QPythia_VacB_N.root", "HCSSD7DR3");

   // PdfFile.AddPlot(SOff, "apl");
   // PdfFile.AddPlot(SOffDR0, "apl");
   // PdfFile.AddPlot(SOffDR1, "apl");
   // PdfFile.AddPlot(SOffDR2, "apl");
   // PdfFile.AddPlot(SOffDR3, "apl");
   // PdfFile.AddPlot(SOn, "apl");
   // PdfFile.AddPlot(SOnDR0, "apl");
   // PdfFile.AddPlot(SOnDR1, "apl");
   // PdfFile.AddPlot(SOnDR2, "apl");
   // PdfFile.AddPlot(SOnDR3, "apl");
   // PdfFile.AddPlot(SBOff, "apl");
   // PdfFile.AddPlot(SBOffDR0, "apl");
   // PdfFile.AddPlot(SBOffDR1, "apl");
   // PdfFile.AddPlot(SBOffDR2, "apl");
   // PdfFile.AddPlot(SBOffDR3, "apl");
   // PdfFile.AddPlot(SBOn, "apl");
   // PdfFile.AddPlot(SBOnDR0, "apl");
   // PdfFile.AddPlot(SBOnDR1, "apl");
   // PdfFile.AddPlot(SBOnDR2, "apl");
   // PdfFile.AddPlot(SBOnDR3, "apl");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(13);

   TCanvas C;
   C.SetLogx();

   TH2D HWorld("HWorld", ";p_{T}^{jet} (GeV);R_{AA}", 100, 99.99, 1000, 100, 0.0, 1.5);
   HWorld.SetStats(0);
   HWorld.Draw("axis");
   TH2D HWorld2("HWorld2", ";p_{T}^{jet} (GeV);R_{AA}", 100, 99.99, 1000, 100, 0.0, 3.0);
   HWorld2.SetStats(0);
   HWorld2.Draw("axis");

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

   PdfFile.AddCanvas(C);

   HWorld.Draw("axis");

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

   PdfFile.AddCanvas(C);

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

   PdfFile.AddCanvas(C);

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

   PdfFile.AddCanvas(C);

   // QPythia QHat = 1
   
   QS1.SetLineColor(kBlack);
   QS1DR0.SetLineColor(kMagenta);
   QS1DR1.SetLineColor(kRed);
   QS1DR2.SetLineColor(kBlue);
   QS1DR3.SetLineColor(kGreen);
   QS1.SetMarkerColor(kBlack);
   QS1DR0.SetMarkerColor(kMagenta);
   QS1DR1.SetMarkerColor(kRed);
   QS1DR2.SetMarkerColor(kBlue);
   QS1DR3.SetMarkerColor(kGreen);

   HWorld2.Draw("axis");

   QS1.Draw("p");
   QS1DR0.Draw("p");
   QS1DR1.Draw("p");
   QS1DR2.Draw("p");
   QS1DR3.Draw("p");

   Legend.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 1)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "No background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   PdfFile.AddCanvas(C);

   QSB1.SetLineColor(kBlack);
   QSB1DR0.SetLineColor(kMagenta);
   QSB1DR1.SetLineColor(kRed);
   QSB1DR2.SetLineColor(kBlue);
   QSB1DR3.SetLineColor(kGreen);
   QSB1.SetMarkerColor(kBlack);
   QSB1DR0.SetMarkerColor(kMagenta);
   QSB1DR1.SetMarkerColor(kRed);
   QSB1DR2.SetMarkerColor(kBlue);
   QSB1DR3.SetMarkerColor(kGreen);

   HWorld2.Draw("axis");

   QSB1.Draw("p");
   QSB1DR0.Draw("p");
   QSB1DR1.Draw("p");
   QSB1DR2.Draw("p");
   QSB1DR3.Draw("p");

   Legend.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 1)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "With background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   PdfFile.AddCanvas(C);
   
   TLegend Legend3(0.55, 0.87, 0.85, 0.56);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.035);
   Legend3.SetFillStyle(0);
   Legend3.AddEntry(&QS1, "S", "lp");
   Legend3.AddEntry(&QS1DR0, "S, #DeltaR < 0.1", "lp");
   Legend3.AddEntry(&QS1DR1, "S, #DeltaR 0.1-0.2", "lp");
   Legend3.AddEntry(&QSB1, "S+B", "lp");
   Legend3.AddEntry(&QSB1DR0, "S+B, #DeltaR < 0.1", "lp");
   Legend3.AddEntry(&QSB1DR1, "S+B, #DeltaR 0.1-0.2", "lp");

   QS1.SetLineColor(kBlack);
   QS1DR0.SetLineColor(kGreen);
   QS1DR1.SetLineColor(kMagenta);
   QSB1.SetLineColor(kBlue);
   QSB1DR0.SetLineColor(kRed);
   QSB1DR1.SetLineColor(kYellow + 3);
   QS1.SetMarkerColor(kBlack);
   QS1DR0.SetMarkerColor(kGreen);
   QS1DR1.SetMarkerColor(kMagenta);
   QSB1.SetMarkerColor(kBlue);
   QSB1DR0.SetMarkerColor(kRed);
   QSB1DR1.SetMarkerColor(kYellow + 3);
   
   HWorld2.Draw("axis");

   QS1.Draw("p");
   QS1DR0.Draw("p");
   QS1DR1.Draw("p");
   QSB1.Draw("p");
   QSB1DR0.Draw("p");
   QSB1DR1.Draw("p");
   Legend3.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 1)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.70, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   // QPythia QHat = 2
   
   QS2.SetLineColor(kBlack);
   QS2DR0.SetLineColor(kMagenta);
   QS2DR1.SetLineColor(kRed);
   QS2DR2.SetLineColor(kBlue);
   QS2DR3.SetLineColor(kGreen);
   QS2.SetMarkerColor(kBlack);
   QS2DR0.SetMarkerColor(kMagenta);
   QS2DR1.SetMarkerColor(kRed);
   QS2DR2.SetMarkerColor(kBlue);
   QS2DR3.SetMarkerColor(kGreen);

   HWorld2.Draw("axis");

   QS2.Draw("p");
   QS2DR0.Draw("p");
   QS2DR1.Draw("p");
   QS2DR2.Draw("p");
   QS2DR3.Draw("p");

   Legend.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 2)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "No background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   PdfFile.AddCanvas(C);

   QSB2.SetLineColor(kBlack);
   QSB2DR0.SetLineColor(kMagenta);
   QSB2DR1.SetLineColor(kRed);
   QSB2DR2.SetLineColor(kBlue);
   QSB2DR3.SetLineColor(kGreen);
   QSB2.SetMarkerColor(kBlack);
   QSB2DR0.SetMarkerColor(kMagenta);
   QSB2DR1.SetMarkerColor(kRed);
   QSB2DR2.SetMarkerColor(kBlue);
   QSB2DR3.SetMarkerColor(kGreen);

   HWorld2.Draw("axis");

   QSB2.Draw("p");
   QSB2DR0.Draw("p");
   QSB2DR1.Draw("p");
   QSB2DR2.Draw("p");
   QSB2DR3.Draw("p");

   Legend.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 2)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "With background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   PdfFile.AddCanvas(C);
   
   QS2.SetLineColor(kBlack);
   QS2DR0.SetLineColor(kGreen);
   QS2DR1.SetLineColor(kMagenta);
   QSB2.SetLineColor(kBlue);
   QSB2DR0.SetLineColor(kRed);
   QSB2DR1.SetLineColor(kYellow + 3);
   QS2.SetMarkerColor(kBlack);
   QS2DR0.SetMarkerColor(kGreen);
   QS2DR1.SetMarkerColor(kMagenta);
   QSB2.SetMarkerColor(kBlue);
   QSB2DR0.SetMarkerColor(kRed);
   QSB2DR1.SetMarkerColor(kYellow + 3);
   
   HWorld2.Draw("axis");

   QS2.Draw("p");
   QS2DR0.Draw("p");
   QS2DR1.Draw("p");
   QSB2.Draw("p");
   QSB2DR0.Draw("p");
   QSB2DR1.Draw("p");
   Legend3.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 2)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.70, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   // QPythia QHat = 4
   
   QS4.SetLineColor(kBlack);
   QS4DR0.SetLineColor(kMagenta);
   QS4DR1.SetLineColor(kRed);
   QS4DR2.SetLineColor(kBlue);
   QS4DR3.SetLineColor(kGreen);
   QS4.SetMarkerColor(kBlack);
   QS4DR0.SetMarkerColor(kMagenta);
   QS4DR1.SetMarkerColor(kRed);
   QS4DR2.SetMarkerColor(kBlue);
   QS4DR3.SetMarkerColor(kGreen);

   HWorld2.Draw("axis");

   QS4.Draw("p");
   QS4DR0.Draw("p");
   QS4DR1.Draw("p");
   QS4DR2.Draw("p");
   QS4DR3.Draw("p");

   Legend.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 4)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "No background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   PdfFile.AddCanvas(C);

   QSB4.SetLineColor(kBlack);
   QSB4DR0.SetLineColor(kMagenta);
   QSB4DR1.SetLineColor(kRed);
   QSB4DR2.SetLineColor(kBlue);
   QSB4DR3.SetLineColor(kGreen);
   QSB4.SetMarkerColor(kBlack);
   QSB4DR0.SetMarkerColor(kMagenta);
   QSB4DR1.SetMarkerColor(kRed);
   QSB4DR2.SetMarkerColor(kBlue);
   QSB4DR3.SetMarkerColor(kGreen);

   HWorld2.Draw("axis");

   QSB4.Draw("p");
   QSB4DR0.Draw("p");
   QSB4DR1.Draw("p");
   QSB4DR2.Draw("p");
   QSB4DR3.Draw("p");

   Legend.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 4)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "With background");
   Latex.DrawLatex(0.15, 0.70, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.65, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   PdfFile.AddCanvas(C);
   
   QS4.SetLineColor(kBlack);
   QS4DR0.SetLineColor(kGreen);
   QS4DR1.SetLineColor(kMagenta);
   QSB4.SetLineColor(kBlue);
   QSB4DR0.SetLineColor(kRed);
   QSB4DR1.SetLineColor(kYellow + 3);
   QS4.SetMarkerColor(kBlack);
   QS4DR0.SetMarkerColor(kGreen);
   QS4DR1.SetMarkerColor(kMagenta);
   QSB4.SetMarkerColor(kBlue);
   QSB4DR0.SetMarkerColor(kRed);
   QSB4DR1.SetMarkerColor(kYellow + 3);
   
   HWorld2.Draw("axis");

   QS4.Draw("p");
   QS4DR0.Draw("p");
   QS4DR1.Draw("p");
   QSB4.Draw("p");
   QSB4DR0.Draw("p");
   QSB4DR1.Draw("p");
   Legend3.Draw();
 
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 4)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "Soft drop z_{cut} = 0.5, #beta = 1.5");
   Latex.DrawLatex(0.15, 0.70, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   PdfFile.AddCanvas(C);

   // qpythia many q-hats

   TLegend Legend4(0.55, 0.87, 0.85, 0.56);
   Legend4.SetTextFont(42);
   Legend4.SetTextSize(0.035);
   Legend4.SetFillStyle(0);
   Legend4.AddEntry(&QS1,  "#hat{q} = 1", "lp");
   Legend4.AddEntry(&QS2,  "#hat{q} = 2", "lp");
   Legend4.AddEntry(&QS4,  "#hat{q} = 4", "lp");
   Legend4.AddEntry("", "", "");
   Legend4.AddEntry("", "", "");
   Legend4.AddEntry("", "", "");

   HWorld.Draw("axis");

   QS1.SetLineColor(kBlack);
   QS2.SetLineColor(kRed);
   QS4.SetLineColor(kGreen + 2);
   QSB1.SetLineColor(kBlack);
   QSB2.SetLineColor(kRed);
   QSB4.SetLineColor(kGreen + 2);
   QS1.SetMarkerColor(kBlack);
   QS2.SetMarkerColor(kRed);
   QS4.SetMarkerColor(kGreen + 2);
   QSB1.SetMarkerColor(kBlack);
   QSB2.SetMarkerColor(kRed);
   QSB4.SetMarkerColor(kGreen + 2);

   QS1.Draw("p");
   QS2.Draw("p");
   QS4.Draw("p");
   Legend4.Draw();
   
   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 1, 2, 4)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "Signal only");
   Latex.DrawLatex(0.15, 0.70, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

   PdfFile.AddCanvas(C);
   
   HWorld.Draw("axis");
   
   QSB1.Draw("p");
   QSB2.Draw("p");
   QSB4.Draw("p");
   Legend4.Draw();

   Latex.DrawLatex(0.15, 0.85, "QPythia (#hat{q} = 1, 2, 4)");
   Latex.DrawLatex(0.15, 0.80, "0-10%");
   Latex.DrawLatex(0.15, 0.75, "Signal + background");
   Latex.DrawLatex(0.15, 0.70, "CS anti-k_{T} R = 0.4, |#eta^{jet}| < 1.3");

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


