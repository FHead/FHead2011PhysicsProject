#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void Divide(TGraphAsymmErrors &Graph, string FileName1, string Name1, string FileName2, string Name2);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("JetRAAPlots.pdf");
   PdfFile.AddTextPage("Jet RAA Plots");

   TGraphAsymmErrors SOff, SOffDR0, SOffDR1, SOffDR2, SOffDR3;
   TGraphAsymmErrors SOn, SOnDR0, SOnDR1, SOnDR2, SOnDR3;
   TGraphAsymmErrors SBOff, SBOffDR0, SBOffDR1, SBOffDR2, SBOffDR3;
   TGraphAsymmErrors SBOn, SBOnDR0, SBOnDR1, SBOnDR2, SBOnDR3;

   Divide(SOff, "Plots_Off_S_N.root", "HCS", "Plots_Off_P_N.root", "HCS");
   Divide(SOffDR0, "Plots_Off_S_N.root", "HCSSD7DR0", "Plots_Off_P_N.root", "HCSSD7DR0");
   Divide(SOffDR1, "Plots_Off_S_N.root", "HCSSD7DR1", "Plots_Off_P_N.root", "HCSSD7DR1");
   Divide(SOffDR2, "Plots_Off_S_N.root", "HCSSD7DR2", "Plots_Off_P_N.root", "HCSSD7DR2");
   Divide(SOffDR3, "Plots_Off_S_N.root", "HCSSD7DR3", "Plots_Off_P_N.root", "HCSSD7DR3");
   Divide(SOn, "Plots_On_S_Y.root", "HCS", "Plots_On_P_Y.root", "HCS");
   Divide(SOnDR0, "Plots_On_S_Y.root", "HCSSD7DR0", "Plots_On_P_Y.root", "HCSSD7DR0");
   Divide(SOnDR1, "Plots_On_S_Y.root", "HCSSD7DR1", "Plots_On_P_Y.root", "HCSSD7DR1");
   Divide(SOnDR2, "Plots_On_S_Y.root", "HCSSD7DR2", "Plots_On_P_Y.root", "HCSSD7DR2");
   Divide(SOnDR3, "Plots_On_S_Y.root", "HCSSD7DR3", "Plots_On_P_Y.root", "HCSSD7DR3");
   Divide(SBOff, "Plots_Off_SB_N.root", "HCS", "Plots_Off_P_N.root", "HCS");
   Divide(SBOffDR0, "Plots_Off_SB_N.root", "HCSSD7DR0", "Plots_Off_P_N.root", "HCSSD7DR0");
   Divide(SBOffDR1, "Plots_Off_SB_N.root", "HCSSD7DR1", "Plots_Off_P_N.root", "HCSSD7DR1");
   Divide(SBOffDR2, "Plots_Off_SB_N.root", "HCSSD7DR2", "Plots_Off_P_N.root", "HCSSD7DR2");
   Divide(SBOffDR3, "Plots_Off_SB_N.root", "HCSSD7DR3", "Plots_Off_P_N.root", "HCSSD7DR3");
   Divide(SBOn, "Plots_On_SB_Y.root", "HCS", "Plots_On_P_Y.root", "HCS");
   Divide(SBOnDR0, "Plots_On_SB_Y.root", "HCSSD7DR0", "Plots_On_P_Y.root", "HCSSD7DR0");
   Divide(SBOnDR1, "Plots_On_SB_Y.root", "HCSSD7DR1", "Plots_On_P_Y.root", "HCSSD7DR1");
   Divide(SBOnDR2, "Plots_On_SB_Y.root", "HCSSD7DR2", "Plots_On_P_Y.root", "HCSSD7DR2");
   Divide(SBOnDR3, "Plots_On_SB_Y.root", "HCSSD7DR3", "Plots_On_P_Y.root", "HCSSD7DR3");

   PdfFile.AddPlot(SOff, "apl");
   PdfFile.AddPlot(SOffDR0, "apl");
   PdfFile.AddPlot(SOffDR1, "apl");
   PdfFile.AddPlot(SOffDR2, "apl");
   PdfFile.AddPlot(SOffDR3, "apl");
   PdfFile.AddPlot(SOn, "apl");
   PdfFile.AddPlot(SOnDR0, "apl");
   PdfFile.AddPlot(SOnDR1, "apl");
   PdfFile.AddPlot(SOnDR2, "apl");
   PdfFile.AddPlot(SOnDR3, "apl");
   PdfFile.AddPlot(SBOff, "apl");
   PdfFile.AddPlot(SBOffDR0, "apl");
   PdfFile.AddPlot(SBOffDR1, "apl");
   PdfFile.AddPlot(SBOffDR2, "apl");
   PdfFile.AddPlot(SBOffDR3, "apl");
   PdfFile.AddPlot(SBOn, "apl");
   PdfFile.AddPlot(SBOnDR0, "apl");
   PdfFile.AddPlot(SBOnDR1, "apl");
   PdfFile.AddPlot(SBOnDR2, "apl");
   PdfFile.AddPlot(SBOnDR3, "apl");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void Divide(TGraphAsymmErrors &Graph, string FileName1, string Name1, string FileName2, string Name2)
{
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


