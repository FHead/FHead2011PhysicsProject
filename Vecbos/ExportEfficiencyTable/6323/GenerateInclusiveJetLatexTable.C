#include <string>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"

void GenerateInclusiveJetLatexTable(string rootfile = "InclusiveJetResultTable.root")
{
   TFile F(rootfile.c_str());

   TH2D *RelativeYieldCalo = (TH2D *)F.Get("HYieldTable_Calo");
   TH2D *RelativeYieldUncorrectedCalo = (TH2D *)F.Get("HYieldTable_UncorrectedCalo");

   printf("\n\n");
   printf("\\begin{table}[htdp]\n");
   printf(" \\caption{Selection efficiency for signal in different calo jet bin for each\n");
   printf("    applied requirement. The values quoted are computed with respect\n");
   printf("    to the previously-applied selection.\\label{tab:effSel}}\n");
   printf(" \\centering\n");
   printf(" \\begin{tabular}{|c|c|c|c|c|c|}\n");
   printf("   \\hline\n");
   printf("   \\verb|Jet count| & $\\get 0 jets$ & $\\get 1 jet$ & $\\get 2 jets$ & $\\get 3 jets$ & $\\get 4 jets$ \\\\\n");
   printf("   \\hline\n");
   printf("   \\verb|HLT| & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $  & $ %.2f \\pm %.2f $\\\\\n",
      RelativeYieldCalo->GetBinContent(1, 16) * 100, RelativeYieldCalo->GetBinError(1, 16) * 100,
      RelativeYieldCalo->GetBinContent(2, 16) * 100, RelativeYieldCalo->GetBinError(2, 16) * 100,
      RelativeYieldCalo->GetBinContent(3, 16) * 100, RelativeYieldCalo->GetBinError(3, 16) * 100,
      RelativeYieldCalo->GetBinContent(4, 16) * 100, RelativeYieldCalo->GetBinError(4, 16) * 100,
      RelativeYieldCalo->GetBinContent(5, 16) * 100, RelativeYieldCalo->GetBinError(5, 16) * 100);
   printf("   \\verb|Two Muons|          & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 15) * 100, RelativeYieldCalo->GetBinError(1, 15) * 100,
      RelativeYieldCalo->GetBinContent(2, 15) * 100, RelativeYieldCalo->GetBinError(2, 15) * 100,
      RelativeYieldCalo->GetBinContent(3, 15) * 100, RelativeYieldCalo->GetBinError(3, 15) * 100,
      RelativeYieldCalo->GetBinContent(4, 15) * 100, RelativeYieldCalo->GetBinError(4, 15) * 100,
      RelativeYieldCalo->GetBinContent(5, 15) * 100, RelativeYieldCalo->GetBinError(5, 15) * 100);
   printf("   \\verb|Two Global Muons|   & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 14) * 100, RelativeYieldCalo->GetBinError(1, 14) * 100,
      RelativeYieldCalo->GetBinContent(2, 14) * 100, RelativeYieldCalo->GetBinError(2, 14) * 100,
      RelativeYieldCalo->GetBinContent(3, 14) * 100, RelativeYieldCalo->GetBinError(3, 14) * 100,
      RelativeYieldCalo->GetBinContent(4, 14) * 100, RelativeYieldCalo->GetBinError(4, 14) * 100,
      RelativeYieldCalo->GetBinContent(5, 14) * 100, RelativeYieldCalo->GetBinError(5, 14) * 100);
   printf("   \\verb|Pixel Hits|         & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 13) * 100, RelativeYieldCalo->GetBinError(1, 13) * 100,
      RelativeYieldCalo->GetBinContent(2, 13) * 100, RelativeYieldCalo->GetBinError(2, 13) * 100,
      RelativeYieldCalo->GetBinContent(3, 13) * 100, RelativeYieldCalo->GetBinError(3, 13) * 100,
      RelativeYieldCalo->GetBinContent(4, 13) * 100, RelativeYieldCalo->GetBinError(4, 13) * 100,
      RelativeYieldCalo->GetBinContent(5, 13) * 100, RelativeYieldCalo->GetBinError(5, 13) * 100);
   printf("   \\verb|Tracking Hits|      & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f$ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 12) * 100, RelativeYieldCalo->GetBinError(1, 12) * 100,
      RelativeYieldCalo->GetBinContent(2, 12) * 100, RelativeYieldCalo->GetBinError(2, 12) * 100,
      RelativeYieldCalo->GetBinContent(3, 12) * 100, RelativeYieldCalo->GetBinError(3, 12) * 100,
      RelativeYieldCalo->GetBinContent(4, 12) * 100, RelativeYieldCalo->GetBinError(4, 12) * 100,
      RelativeYieldCalo->GetBinContent(5, 12) * 100, RelativeYieldCalo->GetBinError(5, 12) * 100);
   printf("   \\verb|Valid Muon Hits|    & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 11) * 100, RelativeYieldCalo->GetBinError(1, 11) * 100,
      RelativeYieldCalo->GetBinContent(2, 11) * 100, RelativeYieldCalo->GetBinError(2, 11) * 100,
      RelativeYieldCalo->GetBinContent(3, 11) * 100, RelativeYieldCalo->GetBinError(3, 11) * 100,
      RelativeYieldCalo->GetBinContent(4, 11) * 100, RelativeYieldCalo->GetBinError(4, 11) * 100,
      RelativeYieldCalo->GetBinContent(5, 11) * 100, RelativeYieldCalo->GetBinError(5, 11) * 100);
   printf("   \\verb|Muon |$\\chi^2$      & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 10) * 100, RelativeYieldCalo->GetBinError(1, 10) * 100,
      RelativeYieldCalo->GetBinContent(2, 10) * 100, RelativeYieldCalo->GetBinError(2, 10) * 100,
      RelativeYieldCalo->GetBinContent(3, 10) * 100, RelativeYieldCalo->GetBinError(3, 10) * 100,
      RelativeYieldCalo->GetBinContent(4, 10) * 100, RelativeYieldCalo->GetBinError(4, 10) * 100,
      RelativeYieldCalo->GetBinContent(5, 10) * 100, RelativeYieldCalo->GetBinError(5, 10) * 100);
   printf("   \\verb|Isolation |         & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f$ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 9) * 100, RelativeYieldCalo->GetBinError(1, 9) * 100,
      RelativeYieldCalo->GetBinContent(2, 9) * 100, RelativeYieldCalo->GetBinError(2, 9) * 100,
      RelativeYieldCalo->GetBinContent(3, 9) * 100, RelativeYieldCalo->GetBinError(3, 9) * 100,
      RelativeYieldCalo->GetBinContent(4, 9) * 100, RelativeYieldCalo->GetBinError(4, 9) * 100,
      RelativeYieldCalo->GetBinContent(5, 9) * 100, RelativeYieldCalo->GetBinError(5, 9) * 100);
   printf("   $p_T$ \\verb|and| $|\\eta|$ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 8) * 100, RelativeYieldCalo->GetBinError(1, 8) * 100,
      RelativeYieldCalo->GetBinContent(2, 8) * 100, RelativeYieldCalo->GetBinError(2, 8) * 100,
      RelativeYieldCalo->GetBinContent(3, 8) * 100, RelativeYieldCalo->GetBinError(3, 8) * 100,
      RelativeYieldCalo->GetBinContent(4, 8) * 100, RelativeYieldCalo->GetBinError(4, 8) * 100,
      RelativeYieldCalo->GetBinContent(5, 8) * 100, RelativeYieldCalo->GetBinError(5, 8) * 100);
   printf("   \\hline\n");
   printf("   \\verb|Total|              & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldCalo->GetBinContent(1, 7) * 100, RelativeYieldCalo->GetBinError(1, 7) * 100,
      RelativeYieldCalo->GetBinContent(2, 7) * 100, RelativeYieldCalo->GetBinError(2, 7) * 100,
      RelativeYieldCalo->GetBinContent(3, 7) * 100, RelativeYieldCalo->GetBinError(3, 7) * 100,
      RelativeYieldCalo->GetBinContent(4, 7) * 100, RelativeYieldCalo->GetBinError(4, 7) * 100,
      RelativeYieldCalo->GetBinContent(5, 7) * 100, RelativeYieldCalo->GetBinError(5, 7) * 100);
   printf("   \\hline\n");
   printf("   \\end{tabular}\n");
   printf("\\label{table}\n");
   printf("\\end{table}\n");

   printf("\n\n");
   printf("\\begin{table}[htdp]\n");
   printf(" \\caption{Selection efficiency for signal in different uncorrected calo jet bin for each\n");
   printf("    applied requirement. The values quoted are computed with respect\n");
   printf("    to the previously-applied selection.\\label{tab:effSel}}\n");
   printf(" \\centering\n");
   printf(" \\begin{tabular}{|c|c|c|c|c|c|}\n");
   printf("   \\hline\n");
   printf("   \\verb|Jet count| & $\\get 0 jets$ & $\\get 1 jet$ & $\\get 2 jets$ & $\\get 3 jets$ & $\\get 4 jets$ \\\\\n");
   printf("   \\hline\n");
   printf("   \\verb|HLT| & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $  & $ %.2f \\pm %.2f $\\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 16) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 16) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 16) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 16) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 16) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 16) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 16) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 16) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 16) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 16) * 100);
   printf("   \\verb|Two Muons|          & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 15) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 15) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 15) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 15) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 15) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 15) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 15) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 15) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 15) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 15) * 100);
   printf("   \\verb|Two Global Muons|   & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 14) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 14) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 14) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 14) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 14) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 14) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 14) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 14) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 14) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 14) * 100);
   printf("   \\verb|Pixel Hits|         & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 13) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 13) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 13) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 13) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 13) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 13) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 13) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 13) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 13) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 13) * 100);
   printf("   \\verb|Tracking Hits|      & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f$ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 12) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 12) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 12) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 12) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 12) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 12) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 12) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 12) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 12) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 12) * 100);
   printf("   \\verb|Valid Muon Hits|    & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 11) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 11) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 11) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 11) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 11) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 11) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 11) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 11) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 11) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 11) * 100);
   printf("   \\verb|Muon |$\\chi^2$      & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 10) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 10) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 10) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 10) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 10) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 10) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 10) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 10) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 10) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 10) * 100);
   printf("   \\verb|Isolation |         & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f$ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 9) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 9) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 9) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 9) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 9) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 9) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 9) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 9) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 9) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 9) * 100);
   printf("   $p_T$ \\verb|and| $|\\eta|$ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 8) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 8) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 8) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 8) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 8) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 8) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 8) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 8) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 8) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 8) * 100);
   printf("   \\hline\n");
   printf("   \\verb|Total|              & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ & $ %.2f \\pm %.2f $ \\\\\n",
      RelativeYieldUncorrectedCalo->GetBinContent(1, 7) * 100, RelativeYieldUncorrectedCalo->GetBinError(1, 7) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(2, 7) * 100, RelativeYieldUncorrectedCalo->GetBinError(2, 7) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(3, 7) * 100, RelativeYieldUncorrectedCalo->GetBinError(3, 7) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(4, 7) * 100, RelativeYieldUncorrectedCalo->GetBinError(4, 7) * 100,
      RelativeYieldUncorrectedCalo->GetBinContent(5, 7) * 100, RelativeYieldUncorrectedCalo->GetBinError(5, 7) * 100);
   printf("   \\hline\n");
   printf("   \\end{tabular}\n");
   printf("\\label{table}\n");
   printf("\\end{table}\n");
   printf("\n\n");

   F.Close();
}
