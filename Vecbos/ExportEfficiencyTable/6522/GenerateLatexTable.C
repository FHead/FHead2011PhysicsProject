#include <string>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"

void GenerateLatexTable(string rootfile = "ResultTable.root")
{
   TFile F(rootfile.c_str());

   TH2D *RelativeYieldCalo = (TH2D *)F.Get("HYieldTable_Calo");
   TH2D *AbsoluteYieldCalo = (TH2D *)F.Get("HAbsoluteYieldTable_Calo");
   TH2D *AbsoluteYieldUncorrectedCalo = (TH2D *)F.Get("HAbsoluteYieldTable_UncorrectedCalo");
   TH2D *AbsoluteYieldPF = (TH2D *)F.Get("HAbsoluteYieldTable_PF");
   TH2D *AbsoluteYieldTrack = (TH2D *)F.Get("HAbsoluteYieldTable_Track");

   printf("\n\n");
   printf("\\begin{table}[htdp]\n");
   printf(" \\caption{Selection efficiency for signal and background for each\n");
   printf("    applied requirement. The values quoted are computed with respect\n");
   printf("    to the previously-applied selection.\\label{tab:effSel}}\n");
   printf(" \\centering\n");
   printf(" \\begin{tabular}{|c|c|c|c|c|}\n");
   printf("   \\hline\n");
   printf("   \\verb|Sample| & $Z+jets$ & $W+jets$ & $t \\bar t+jets$ & $QCD$ \\\\\n");
   printf("   \\hline\n");
   printf("   \\verb|HLT| & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 16) * 100, RelativeYieldCalo->GetBinError(1, 16) * 100,
      RelativeYieldCalo->GetBinContent(2, 16) * 100, RelativeYieldCalo->GetBinError(2, 16) * 100,
      RelativeYieldCalo->GetBinContent(3, 16) * 100, RelativeYieldCalo->GetBinError(3, 16) * 100,
      RelativeYieldCalo->GetBinContent(4, 16) * 100, RelativeYieldCalo->GetBinError(4, 16) * 100);
   printf("   \\verb|Two Muons|          & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 15) * 100, RelativeYieldCalo->GetBinError(1, 15) * 100,
      RelativeYieldCalo->GetBinContent(2, 15) * 100, RelativeYieldCalo->GetBinError(2, 15) * 100,
      RelativeYieldCalo->GetBinContent(3, 15) * 100, RelativeYieldCalo->GetBinError(3, 15) * 100,
      RelativeYieldCalo->GetBinContent(4, 15) * 100, RelativeYieldCalo->GetBinError(4, 15) * 100);
   printf("   \\verb|Two Global Muons|   & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 14) * 100, RelativeYieldCalo->GetBinError(1, 14) * 100,
      RelativeYieldCalo->GetBinContent(2, 14) * 100, RelativeYieldCalo->GetBinError(2, 14) * 100,
      RelativeYieldCalo->GetBinContent(3, 14) * 100, RelativeYieldCalo->GetBinError(3, 14) * 100,
      RelativeYieldCalo->GetBinContent(4, 14) * 100, RelativeYieldCalo->GetBinError(4, 14) * 100);
   printf("   \\verb|Pixel Hits|         & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 13) * 100, RelativeYieldCalo->GetBinError(1, 13) * 100,
      RelativeYieldCalo->GetBinContent(2, 13) * 100, RelativeYieldCalo->GetBinError(2, 13) * 100,
      RelativeYieldCalo->GetBinContent(3, 13) * 100, RelativeYieldCalo->GetBinError(3, 13) * 100,
      RelativeYieldCalo->GetBinContent(4, 13) * 100, RelativeYieldCalo->GetBinError(4, 13) * 100);
   printf("   \\verb|Tracking Hits|      & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f$ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 12) * 100, RelativeYieldCalo->GetBinError(1, 12) * 100,
      RelativeYieldCalo->GetBinContent(2, 12) * 100, RelativeYieldCalo->GetBinError(2, 12) * 100,
      RelativeYieldCalo->GetBinContent(3, 12) * 100, RelativeYieldCalo->GetBinError(3, 12) * 100,
      RelativeYieldCalo->GetBinContent(4, 12) * 100, RelativeYieldCalo->GetBinError(4, 12) * 100);
   printf("   \\verb|Valid Muon Hits|    & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 11) * 100, RelativeYieldCalo->GetBinError(1, 11) * 100,
      RelativeYieldCalo->GetBinContent(2, 11) * 100, RelativeYieldCalo->GetBinError(2, 11) * 100,
      RelativeYieldCalo->GetBinContent(3, 11) * 100, RelativeYieldCalo->GetBinError(3, 11) * 100,
      RelativeYieldCalo->GetBinContent(4, 11) * 100, RelativeYieldCalo->GetBinError(4, 11) * 100);
   printf("   \\verb|Muon |$\\chi^2$      & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 10) * 100, RelativeYieldCalo->GetBinError(1, 10) * 100,
      RelativeYieldCalo->GetBinContent(2, 10) * 100, RelativeYieldCalo->GetBinError(2, 10) * 100,
      RelativeYieldCalo->GetBinContent(3, 10) * 100, RelativeYieldCalo->GetBinError(3, 10) * 100,
      RelativeYieldCalo->GetBinContent(4, 10) * 100, RelativeYieldCalo->GetBinError(4, 10) * 100);
   printf("   \\verb|Isolation |         & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f$ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 9) * 100, RelativeYieldCalo->GetBinError(1, 9) * 100,
      RelativeYieldCalo->GetBinContent(2, 9) * 100, RelativeYieldCalo->GetBinError(2, 9) * 100,
      RelativeYieldCalo->GetBinContent(3, 9) * 100, RelativeYieldCalo->GetBinError(3, 9) * 100,
      RelativeYieldCalo->GetBinContent(4, 9) * 100, RelativeYieldCalo->GetBinError(4, 9) * 100);
   printf("   $p_T$ \\verb|and| $|\\eta|$ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 8) * 100, RelativeYieldCalo->GetBinError(1, 8) * 100,
      RelativeYieldCalo->GetBinContent(2, 8) * 100, RelativeYieldCalo->GetBinError(2, 8) * 100,
      RelativeYieldCalo->GetBinContent(3, 8) * 100, RelativeYieldCalo->GetBinError(3, 8) * 100,
      RelativeYieldCalo->GetBinContent(4, 8) * 100, RelativeYieldCalo->GetBinError(4, 8) * 100);
   printf("   \\hline\n");
   printf("   \\verb|Total|              & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 7) * 100, RelativeYieldCalo->GetBinError(1, 7) * 100,
      RelativeYieldCalo->GetBinContent(2, 7) * 100, RelativeYieldCalo->GetBinError(2, 7) * 100,
      RelativeYieldCalo->GetBinContent(3, 7) * 100, RelativeYieldCalo->GetBinError(3, 7) * 100,
      RelativeYieldCalo->GetBinContent(4, 7) * 100, RelativeYieldCalo->GetBinError(4, 7) * 100);
   printf("   \\hline\n");
   printf("   \\end{tabular}\n");
   printf("\\label{table}\n");
   printf("\\end{table}\n");

   printf("\n\n");
   printf("\\begin{table}[htdp]\n");
   printf("   \\caption{Expected number of events in (0$ pb$^{-1}$ for signal and\n");
   printf("       background Monte Carlo samples.\\label{tab:effSel}}\n");
   printf("       \\centering\n");
   printf("       \\begin{tabular}{|c|c|c|c|c|}\n");
   printf("       \\hline\n");
   printf("       \\verb|Jet Counting| & $Z+jets$ & $W+jets$ & $t \\bar t+jets$ & $QCD$ \\\\\n");
   printf("       \\hline\n");
   printf("       \\multicolumn{5}{|c|}{PFJets} \\\\\n");
   printf("       \\hline\n");
   printf("       $N(\\geq 0~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldPF->GetBinContent(1, 7), AbsoluteYieldPF->GetBinError(1, 7),
      AbsoluteYieldPF->GetBinContent(2, 7), AbsoluteYieldPF->GetBinError(2, 7),
      AbsoluteYieldPF->GetBinContent(3, 7), AbsoluteYieldPF->GetBinError(3, 7),
      AbsoluteYieldPF->GetBinContent(4, 7), AbsoluteYieldPF->GetBinError(4, 7));
   printf("       $N(\\geq 1~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldPF->GetBinContent(1, 6), AbsoluteYieldPF->GetBinError(1, 6),
      AbsoluteYieldPF->GetBinContent(2, 6), AbsoluteYieldPF->GetBinError(2, 6),
      AbsoluteYieldPF->GetBinContent(3, 6), AbsoluteYieldPF->GetBinError(3, 6),
      AbsoluteYieldPF->GetBinContent(4, 6), AbsoluteYieldPF->GetBinError(4, 6));
   printf("       $N(\\geq 2~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldPF->GetBinContent(1, 5), AbsoluteYieldPF->GetBinError(1, 5),
      AbsoluteYieldPF->GetBinContent(2, 5), AbsoluteYieldPF->GetBinError(2, 5),
      AbsoluteYieldPF->GetBinContent(3, 5), AbsoluteYieldPF->GetBinError(3, 5),
      AbsoluteYieldPF->GetBinContent(4, 5), AbsoluteYieldPF->GetBinError(4, 5));
   printf("       $N(\\geq 3~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldPF->GetBinContent(1, 4), AbsoluteYieldPF->GetBinError(1, 4),
      AbsoluteYieldPF->GetBinContent(2, 4), AbsoluteYieldPF->GetBinError(2, 4),
      AbsoluteYieldPF->GetBinContent(3, 4), AbsoluteYieldPF->GetBinError(3, 4),
      AbsoluteYieldPF->GetBinContent(4, 4), AbsoluteYieldPF->GetBinError(4, 4));
   printf("       $N(\\geq 4~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldPF->GetBinContent(1, 3), AbsoluteYieldPF->GetBinError(1, 3),
      AbsoluteYieldPF->GetBinContent(2, 3), AbsoluteYieldPF->GetBinError(2, 3),
      AbsoluteYieldPF->GetBinContent(3, 3), AbsoluteYieldPF->GetBinError(3, 3),
      AbsoluteYieldPF->GetBinContent(4, 3), AbsoluteYieldPF->GetBinError(4, 3));
   printf("       \\hline\n");
   printf("       \\multicolumn{5}{|c|}{TrackJets} \\\\\n");
   printf("       \\hline\n");
   printf("       $N(\\geq 0~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldTrack->GetBinContent(1, 7), AbsoluteYieldTrack->GetBinError(1, 7),
      AbsoluteYieldTrack->GetBinContent(2, 7), AbsoluteYieldTrack->GetBinError(2, 7),
      AbsoluteYieldTrack->GetBinContent(3, 7), AbsoluteYieldTrack->GetBinError(3, 7),
      AbsoluteYieldTrack->GetBinContent(4, 7), AbsoluteYieldTrack->GetBinError(4, 7));
   printf("       $N(\\geq 1~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldTrack->GetBinContent(1, 6), AbsoluteYieldTrack->GetBinError(1, 6),
      AbsoluteYieldTrack->GetBinContent(2, 6), AbsoluteYieldTrack->GetBinError(2, 6),
      AbsoluteYieldTrack->GetBinContent(3, 6), AbsoluteYieldTrack->GetBinError(3, 6),
      AbsoluteYieldTrack->GetBinContent(4, 6), AbsoluteYieldTrack->GetBinError(4, 6));
   printf("       $N(\\geq 2~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldTrack->GetBinContent(1, 5), AbsoluteYieldTrack->GetBinError(1, 5),
      AbsoluteYieldTrack->GetBinContent(2, 5), AbsoluteYieldTrack->GetBinError(2, 5),
      AbsoluteYieldTrack->GetBinContent(3, 5), AbsoluteYieldTrack->GetBinError(3, 5),
      AbsoluteYieldTrack->GetBinContent(4, 5), AbsoluteYieldTrack->GetBinError(4, 5));
   printf("       $N(\\geq 3~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldTrack->GetBinContent(1, 4), AbsoluteYieldTrack->GetBinError(1, 4),
      AbsoluteYieldTrack->GetBinContent(2, 4), AbsoluteYieldTrack->GetBinError(2, 4),
      AbsoluteYieldTrack->GetBinContent(3, 4), AbsoluteYieldTrack->GetBinError(3, 4),
      AbsoluteYieldTrack->GetBinContent(4, 4), AbsoluteYieldTrack->GetBinError(4, 4));
   printf("       $N(\\geq 4~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldTrack->GetBinContent(1, 3), AbsoluteYieldTrack->GetBinError(1, 3),
      AbsoluteYieldTrack->GetBinContent(2, 3), AbsoluteYieldTrack->GetBinError(2, 3),
      AbsoluteYieldTrack->GetBinContent(3, 3), AbsoluteYieldTrack->GetBinError(3, 3),
      AbsoluteYieldTrack->GetBinContent(4, 3), AbsoluteYieldTrack->GetBinError(4, 3));
   printf("       \\hline\n");
   printf("       \\multicolumn{5}{|c|}{CaloJets} \\\\\n");
   printf("       \\hline\n");
   printf("       $N(\\geq 0~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldCalo->GetBinContent(1, 7), AbsoluteYieldCalo->GetBinError(1, 7),
      AbsoluteYieldCalo->GetBinContent(2, 7), AbsoluteYieldCalo->GetBinError(2, 7),
      AbsoluteYieldCalo->GetBinContent(3, 7), AbsoluteYieldCalo->GetBinError(3, 7),
      AbsoluteYieldCalo->GetBinContent(4, 7), AbsoluteYieldCalo->GetBinError(4, 7));
   printf("       $N(\\geq 1~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldCalo->GetBinContent(1, 6), AbsoluteYieldCalo->GetBinError(1, 6),
      AbsoluteYieldCalo->GetBinContent(2, 6), AbsoluteYieldCalo->GetBinError(2, 6),
      AbsoluteYieldCalo->GetBinContent(3, 6), AbsoluteYieldCalo->GetBinError(3, 6),
      AbsoluteYieldCalo->GetBinContent(4, 6), AbsoluteYieldCalo->GetBinError(4, 6));
   printf("       $N(\\geq 2~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldCalo->GetBinContent(1, 5), AbsoluteYieldCalo->GetBinError(1, 5),
      AbsoluteYieldCalo->GetBinContent(2, 5), AbsoluteYieldCalo->GetBinError(2, 5),
      AbsoluteYieldCalo->GetBinContent(3, 5), AbsoluteYieldCalo->GetBinError(3, 5),
      AbsoluteYieldCalo->GetBinContent(4, 5), AbsoluteYieldCalo->GetBinError(4, 5));
   printf("       $N(\\geq 3~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldCalo->GetBinContent(1, 4), AbsoluteYieldCalo->GetBinError(1, 4),
      AbsoluteYieldCalo->GetBinContent(2, 4), AbsoluteYieldCalo->GetBinError(2, 4),
      AbsoluteYieldCalo->GetBinContent(3, 4), AbsoluteYieldCalo->GetBinError(3, 4),
      AbsoluteYieldCalo->GetBinContent(4, 4), AbsoluteYieldCalo->GetBinError(4, 4));
   printf("       $N(\\geq 4~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldCalo->GetBinContent(1, 3), AbsoluteYieldCalo->GetBinError(1, 3),
      AbsoluteYieldCalo->GetBinContent(2, 3), AbsoluteYieldCalo->GetBinError(2, 3),
      AbsoluteYieldCalo->GetBinContent(3, 3), AbsoluteYieldCalo->GetBinError(3, 3),
      AbsoluteYieldCalo->GetBinContent(4, 3), AbsoluteYieldCalo->GetBinError(4, 3));
   printf("       \\hline\n");
   printf("       \\multicolumn{5}{|c|}{UncorrectedCaloJets} \\\\\n");
   printf("       \\hline\n");
   printf("       $N(\\geq 0~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldUncorrectedCalo->GetBinContent(1, 7), AbsoluteYieldUncorrectedCalo->GetBinError(1, 7),
      AbsoluteYieldUncorrectedCalo->GetBinContent(2, 7), AbsoluteYieldUncorrectedCalo->GetBinError(2, 7),
      AbsoluteYieldUncorrectedCalo->GetBinContent(3, 7), AbsoluteYieldUncorrectedCalo->GetBinError(3, 7),
      AbsoluteYieldUncorrectedCalo->GetBinContent(4, 7), AbsoluteYieldUncorrectedCalo->GetBinError(4, 7));
   printf("       $N(\\geq 1~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldUncorrectedCalo->GetBinContent(1, 6), AbsoluteYieldUncorrectedCalo->GetBinError(1, 6),
      AbsoluteYieldUncorrectedCalo->GetBinContent(2, 6), AbsoluteYieldUncorrectedCalo->GetBinError(2, 6),
      AbsoluteYieldUncorrectedCalo->GetBinContent(3, 6), AbsoluteYieldUncorrectedCalo->GetBinError(3, 6),
      AbsoluteYieldUncorrectedCalo->GetBinContent(4, 6), AbsoluteYieldUncorrectedCalo->GetBinError(4, 6));
   printf("       $N(\\geq 2~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldUncorrectedCalo->GetBinContent(1, 5), AbsoluteYieldUncorrectedCalo->GetBinError(1, 5),
      AbsoluteYieldUncorrectedCalo->GetBinContent(2, 5), AbsoluteYieldUncorrectedCalo->GetBinError(2, 5),
      AbsoluteYieldUncorrectedCalo->GetBinContent(3, 5), AbsoluteYieldUncorrectedCalo->GetBinError(3, 5),
      AbsoluteYieldUncorrectedCalo->GetBinContent(4, 5), AbsoluteYieldUncorrectedCalo->GetBinError(4, 5));
   printf("       $N(\\geq 3~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldUncorrectedCalo->GetBinContent(1, 4), AbsoluteYieldUncorrectedCalo->GetBinError(1, 4),
      AbsoluteYieldUncorrectedCalo->GetBinContent(2, 4), AbsoluteYieldUncorrectedCalo->GetBinError(2, 4),
      AbsoluteYieldUncorrectedCalo->GetBinContent(3, 4), AbsoluteYieldUncorrectedCalo->GetBinError(3, 4),
      AbsoluteYieldUncorrectedCalo->GetBinContent(4, 4), AbsoluteYieldUncorrectedCalo->GetBinError(4, 4));
   printf("       $N(\\geq 4~jets)$       & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      AbsoluteYieldUncorrectedCalo->GetBinContent(1, 3), AbsoluteYieldUncorrectedCalo->GetBinError(1, 3),
      AbsoluteYieldUncorrectedCalo->GetBinContent(2, 3), AbsoluteYieldUncorrectedCalo->GetBinError(2, 3),
      AbsoluteYieldUncorrectedCalo->GetBinContent(3, 3), AbsoluteYieldUncorrectedCalo->GetBinError(3, 3),
      AbsoluteYieldUncorrectedCalo->GetBinContent(4, 3), AbsoluteYieldUncorrectedCalo->GetBinError(4, 3));
   printf("       \\hline\n");
   printf("       \\end{tabular}\n");
   printf("\\label{table}\n");
   printf("\\end{table}\n");

   printf("\n\n");

   F.Close();
}
