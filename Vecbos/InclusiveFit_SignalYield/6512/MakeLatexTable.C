#include <cstdio>
using namespace std;

#include "TFile.h"
#include "TH2D.h"

void MakeLatexTable()
{
   TFile FCalo("FitResult_Calo_30.root");
   TFile FUncorrectedCalo("FitResult_UncorrectedCalo_20.root");
   TFile FPF("FitResult_PF_30.root");
   TFile FTrack("FitResult_Track_20.root");

   TH2D *HCalo = (TH2D *)FCalo.Get("ResultSummary");
   TH2D *HUncorrectedCalo = (TH2D *)FUncorrectedCalo.Get("ResultSummary");
   TH2D *HPF = (TH2D *)FPF.Get("ResultSummary");
   TH2D *HTrack = (TH2D *)FTrack.Get("ResultSummary");

   printf("\\begin{table}\n");
   printf("\\caption{Data extracted yields}\n");
   printf("\\centering\n");
   printf("   \\begin{tabular}{|c|c|c|c|c|}\n");
   printf("      \\hline\n");
   printf("      & CaloJet & Uncorrected CaloJet & PF Jet & Track jet \\\\\\hline\n");
   printf("      $N \\ge 1$ & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f \\\\\\hline\n",
      HCalo->GetBinContent(1, 2), HCalo->GetBinError(1, 2),
      HUncorrectedCalo->GetBinContent(1, 2), HUncorrectedCalo->GetBinError(1, 2),
      HPF->GetBinContent(1, 2), HPF->GetBinError(1, 2),
      HTrack->GetBinContent(1, 2), HTrack->GetBinError(1, 2));
   printf("      $N \\ge 2$ & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f \\\\\\hline\n",
      HCalo->GetBinContent(2, 2), HCalo->GetBinError(2, 2),
      HUncorrectedCalo->GetBinContent(2, 2), HUncorrectedCalo->GetBinError(2, 2),
      HPF->GetBinContent(2, 2), HPF->GetBinError(2, 2),
      HTrack->GetBinContent(2, 2), HTrack->GetBinError(2, 2));
   printf("      $N \\ge 3$ & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f \\\\\\hline\n",
      HCalo->GetBinContent(3, 2), HCalo->GetBinError(3, 2),
      HUncorrectedCalo->GetBinContent(3, 2), HUncorrectedCalo->GetBinError(3, 2),
      HPF->GetBinContent(3, 2), HPF->GetBinError(3, 2),
      HTrack->GetBinContent(3, 2), HTrack->GetBinError(3, 2));
   printf("      $N \\ge 4$ & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f \\\\\\hline\n",
      HCalo->GetBinContent(4, 2), HCalo->GetBinError(4, 2),
      HUncorrectedCalo->GetBinContent(4, 2), HUncorrectedCalo->GetBinError(4, 2),
      HPF->GetBinContent(4, 2), HPF->GetBinError(4, 2),
      HTrack->GetBinContent(4, 2), HTrack->GetBinError(4, 2));
   printf("      $N \\ge 5$ & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f & %.0f $\\pm$ %.0f \\\\\\hline\n",
      HCalo->GetBinContent(5, 2), HCalo->GetBinError(5, 2),
      HUncorrectedCalo->GetBinContent(5, 2), HUncorrectedCalo->GetBinError(5, 2),
      HPF->GetBinContent(5, 2), HPF->GetBinError(5, 2),
      HTrack->GetBinContent(5, 2), HTrack->GetBinError(5, 2));
   printf("   \\end{tabular}\n");
   printf("   \\label{Table_DataExtractedYields}\n");
   printf("\\end{table}\n");
   printf("\n\n");

   FTrack.Close();
   FPF.Close();
   FUncorrectedCalo.Close();
   FCalo.Close();
}
