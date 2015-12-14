#include <cstdio>
using namespace std;

#include "TFile.h"
#include "TH2D.h"

void MakeLatexTable()
{
   TFile FCalo("DataFitTightIsolation_Calo.root");
   TFile FUncorrectedCalo("DataFitTightIsolation_UncorrectedCalo.root");
   TFile FPF("DataFitTightIsolation_PF.root");
   TFile FTrack("DataFitTightIsolation_Track.root");

   TH2D *HCalo = (TH2D *)FCalo.Get("ResultSummary");
   TH2D *HUncorrectedCalo = (TH2D *)FUncorrectedCalo.Get("ResultSummary");
   TH2D *HPF = (TH2D *)FPF.Get("ResultSummary");
   TH2D *HTrack = (TH2D *)FTrack.Get("ResultSummary");

   printf("\\begin{table}\n");
   printf("\\caption{Shape parameters for different jet flavors fitting to data with tight isolation cut}\n");
   printf("\\centering\n");
   printf("   \\begin{tabular}{|c|c|c|c|c|c|}\n");
   printf("      \\hline\n");
   printf("      & CaloJet & Uncorrected CaloJet & PF Jet & Track jet \\\\\\hline\n");
   printf("      $m$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f \\\\\\hline\n",
      HCalo->GetBinContent(1, 1), HCalo->GetBinError(1, 1),
      HUncorrectedCalo->GetBinContent(1, 1), HUncorrectedCalo->GetBinError(1, 1),
      HPF->GetBinContent(1, 1), HPF->GetBinError(1, 1),
      HTrack->GetBinContent(1, 1), HTrack->GetBinError(1, 1));
   printf("      $\\alpha_L$ & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f \\\\\\hline\n",
      HCalo->GetBinContent(2, 1), HCalo->GetBinError(2, 1),
      HUncorrectedCalo->GetBinContent(2, 1), HUncorrectedCalo->GetBinError(2, 1),
      HPF->GetBinContent(2, 1), HPF->GetBinError(2, 1),
      HTrack->GetBinContent(2, 1), HTrack->GetBinError(2, 1));
   printf("      $\\alpha_R$ & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f \\\\\\hline\n",
      HCalo->GetBinContent(3, 1), HCalo->GetBinError(3, 1),
      HUncorrectedCalo->GetBinContent(3, 1), HUncorrectedCalo->GetBinError(3, 1),
      HPF->GetBinContent(3, 1), HPF->GetBinError(3, 1),
      HTrack->GetBinContent(3, 1), HTrack->GetBinError(3, 1));
   printf("      $\\sigma_L$ & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f \\\\\\hline\n",
      HCalo->GetBinContent(4, 1), HCalo->GetBinError(4, 1),
      HUncorrectedCalo->GetBinContent(4, 1), HUncorrectedCalo->GetBinError(4, 1),
      HPF->GetBinContent(4, 1), HPF->GetBinError(4, 1),
      HTrack->GetBinContent(4, 1), HTrack->GetBinError(4, 1));
   printf("      $\\sigma_R$ & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f \\\\\\hline\n",
      HCalo->GetBinContent(5, 1), HCalo->GetBinError(5, 1),
      HUncorrectedCalo->GetBinContent(5, 1), HUncorrectedCalo->GetBinError(5, 1),
      HPF->GetBinContent(5, 1), HPF->GetBinError(5, 1),
      HTrack->GetBinContent(5, 1), HTrack->GetBinError(5, 1));
   printf("   \\end{tabular}\n");
   printf("   \\label{Table_DataAlphaL}\n");
   printf("\\end{table}\n");
   printf("\n\n");

   FTrack.Close();
   FPF.Close();
   FUncorrectedCalo.Close();
   FCalo.Close();
}
