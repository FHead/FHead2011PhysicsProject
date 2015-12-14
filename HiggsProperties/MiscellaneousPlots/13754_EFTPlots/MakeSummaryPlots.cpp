#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper2.h"

#define NONSENSE 999999

int main();
void AddPlot(PsFileHelper &PsFile, TFile &File, vector<string> Histograms, vector<string> Labels, string Title, string XAxis, string YAxis, double Level = NONSENSE);
vector<string> ToVector(string S1, string S2 = "", string S3 = "", string S4 = "", string S5 = "", string S6 = "", string S7 = "", string S8 = "");

int main()
{
   PsFileHelper PsFileA("SummaryPlotsPointA.ps");
   PsFileA.AddTextPage("Various plots for us to stare at!  Point A - SM");
   PsFileHelper PsFileO("SummaryPlotsPointO.ps");
   PsFileO.AddTextPage("Various plots for us to stare at!  Point O - all-0");
   PsFileHelper PsFile0("SummaryPlotsPoint0.ps");
   PsFile0.AddTextPage("Various plots for us to stare at!  Point O - all-0");
   PsFileHelper PsFileB("SummaryPlotsPointB.ps");
   PsFileB.AddTextPage("Various plots for us to stare at!  Point B - Exotic");
   PsFileHelper PsFileC("SummaryPlotsPointC.ps");
   PsFileC.AddTextPage("Various plots for us to stare at!  Point C - Exotic");

   vector<string> Items(13);
   vector<string> Labels(13);

   Items[0]  = "All couplings on same plot, S only";
   Items[1]  = "All couplings on same plot, S+B";
   Items[2]  = "Cut I vs. Cut J, S only";
   Items[3]  = "Cut I vs. Cut J, S+B";
   Items[4]  = "S vs. S+B, Cut J";
   Items[5]  = "S vs. S+B, Cut I";
   Items[6]  = "";
   Items[7]  = "";
   Items[8]  = "";
   Items[9]  = "";
   Items[10] = "";
   Items[11] = "";
   Items[12] = "";

   Labels[0]  = "AllS";
   Labels[1]  = "AllSB";
   Labels[2]  = "IJS";
   Labels[3]  = "IJSB";
   Labels[4]  = "SSBJ";
   Labels[5]  = "SSBI";
   Labels[6]  = "";
   Labels[7]  = "";
   Labels[8]  = "";
   Labels[9]  = "";
   Labels[10] = "";
   Labels[11] = "";
   Labels[12] = "";

   PsFileA.AddTableOfContentPage(Items, Labels);
   PsFileO.AddTableOfContentPage(Items, Labels);

   PsFileA.InsertNamedDestination("TableOfContent");
   PsFileO.InsertNamedDestination("TableOfContent");

   PsFileA.SetAutomaticHomeButton(true, "TableOfContent");
   PsFileO.SetAutomaticHomeButton(true, "TableOfContent");

   TFile File("AllGraphs.root");

   PsFileA.AddTextPage("Comparison of all couplings, signal only");
   PsFileA.InsertNamedDestination("AllS");

   AddPlot(PsFileA, File,
      ToVector("A2ZZ_BothS_I_Count_YYYYYYYY_PointA",
         "A3ZZ_BothS_I_Count_YYYYYYYY_PointA",
         "A4ZZ_BothS_I_Count_YYYYYYYY_PointA",
         "A2ZA_BothS_I_Count_YYYYYYYY_PointA",
         "A3ZA_BothS_I_Count_YYYYYYYY_PointA",
         "A4ZA_BothS_I_Count_YYYYYYYY_PointA",
         "A2AA_BothS_I_Count_YYYYYYYY_PointA",
         "A3AA_BothS_I_Count_YYYYYYYY_PointA"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_BothS_J_Count_YYYYYYYY_PointA",
         "A3ZZ_BothS_J_Count_YYYYYYYY_PointA",
         "A4ZZ_BothS_J_Count_YYYYYYYY_PointA",
         "A2ZA_BothS_J_Count_YYYYYYYY_PointA",
         "A3ZA_BothS_J_Count_YYYYYYYY_PointA",
         "A4ZA_BothS_J_Count_YYYYYYYY_PointA",
         "A2AA_BothS_J_Count_YYYYYYYY_PointA",
         "A3AA_BothS_J_Count_YYYYYYYY_PointA"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_BothS_I_Count_YNNNNNNN_PointA",
         "A3ZZ_BothS_I_Count_NYNNNNNN_PointA",
         "A4ZZ_BothS_I_Count_NNYNNNNN_PointA",
         "A2ZA_BothS_I_Count_NNNYNNNN_PointA",
         "A3ZA_BothS_I_Count_NNNNYNNN_PointA",
         "A4ZA_BothS_I_Count_NNNNNYNN_PointA",
         "A2AA_BothS_I_Count_NNNNNNYN_PointA",
         "A3AA_BothS_I_Count_NNNNNNNY_PointA"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_BothS_J_Count_YNNNNNNN_PointA",
         "A3ZZ_BothS_J_Count_NYNNNNNN_PointA",
         "A4ZZ_BothS_J_Count_NNYNNNNN_PointA",
         "A2ZA_BothS_J_Count_NNNYNNNN_PointA",
         "A3ZA_BothS_J_Count_NNNNYNNN_PointA",
         "A4ZA_BothS_J_Count_NNNNNYNN_PointA",
         "A2AA_BothS_J_Count_NNNNNNYN_PointA",
         "A3AA_BothS_J_Count_NNNNNNNY_PointA"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   
   PsFileA.AddTextPage("Comparison of all couplings, signal + background");
   PsFileA.InsertNamedDestination("AllSB");
   
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_Both_I_Count_YYYYYYYY_PointA",
         "A3ZZ_Both_I_Count_YYYYYYYY_PointA",
         "A4ZZ_Both_I_Count_YYYYYYYY_PointA",
         "A2ZA_Both_I_Count_YYYYYYYY_PointA",
         "A3ZA_Both_I_Count_YYYYYYYY_PointA",
         "A4ZA_Both_I_Count_YYYYYYYY_PointA",
         "A2AA_Both_I_Count_YYYYYYYY_PointA",
         "A3AA_Both_I_Count_YYYYYYYY_PointA"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float everything, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_Both_J_Count_YYYYYYYY_PointA",
         "A3ZZ_Both_J_Count_YYYYYYYY_PointA",
         "A4ZZ_Both_J_Count_YYYYYYYY_PointA",
         "A2ZA_Both_J_Count_YYYYYYYY_PointA",
         "A3ZA_Both_J_Count_YYYYYYYY_PointA",
         "A4ZA_Both_J_Count_YYYYYYYY_PointA",
         "A2AA_Both_J_Count_YYYYYYYY_PointA",
         "A3AA_Both_J_Count_YYYYYYYY_PointA"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float everything, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_Both_I_Count_YNNNNNNN_PointA",
         "A3ZZ_Both_I_Count_NYNNNNNN_PointA",
         "A4ZZ_Both_I_Count_NNYNNNNN_PointA",
         "A2ZA_Both_I_Count_NNNYNNNN_PointA",
         "A3ZA_Both_I_Count_NNNNYNNN_PointA",
         "A4ZA_Both_I_Count_NNNNNYNN_PointA",
         "A2AA_Both_I_Count_NNNNNNYN_PointA",
         "A3AA_Both_I_Count_NNNNNNNY_PointA"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float each of them separately, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_Both_J_Count_YNNNNNNN_PointA",
         "A3ZZ_Both_J_Count_NYNNNNNN_PointA",
         "A4ZZ_Both_J_Count_NNYNNNNN_PointA",
         "A2ZA_Both_J_Count_NNNYNNNN_PointA",
         "A3ZA_Both_J_Count_NNNNYNNN_PointA",
         "A4ZA_Both_J_Count_NNNNNYNN_PointA",
         "A2AA_Both_J_Count_NNNNNNYN_PointA",
         "A3AA_Both_J_Count_NNNNNNNY_PointA"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float each of them separately, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   
   PsFileA.AddTextPage("Comparison of cut I and cut J, signal only");
   PsFileA.InsertNamedDestination("IJS");
   
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_BothS_J_Lumi_YNNNNNNN_PointA", "A2ZZ_BothS_J_Lumi_YYYYYYYY_PointA",
         "A2ZZ_BothS_I_Lumi_YNNNNNNN_PointA", "A2ZZ_BothS_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A2ZZ (J)", "Float all (J)", "Float only A2ZZ (I)", "Float all (I)"),
      "Signal only, A2ZZ",
      "N_{S} / #epsilon", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A3ZZ_BothS_J_Lumi_NYNNNNNN_PointA", "A3ZZ_BothS_J_Lumi_YYYYYYYY_PointA",
         "A3ZZ_BothS_I_Lumi_NYNNNNNN_PointA", "A3ZZ_BothS_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A3ZZ (J)", "Float all (J)", "Float only A3ZZ (I)", "Float all (I)"),
      "Signal only, A3ZZ",
      "N_{S} / #epsilon", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A4ZZ_BothS_J_Lumi_NNYNNNNN_PointA", "A4ZZ_BothS_J_Lumi_YYYYYYYY_PointA",
         "A4ZZ_BothS_I_Lumi_NNYNNNNN_PointA", "A4ZZ_BothS_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A4ZZ (J)", "Float all (J)", "Float only A4ZZ (I)", "Float all (I)"),
      "Signal only, A4ZZ",
      "N_{S} / #epsilon", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A2ZA_BothS_J_Lumi_NNNYNNNN_PointA", "A2ZA_BothS_J_Lumi_YYYYYYYY_PointA",
         "A2ZA_BothS_I_Lumi_NNNYNNNN_PointA", "A2ZA_BothS_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A2ZA (J)", "Float all (J)", "Float only A2ZA (I)", "Float all (I)"),
      "Signal only, A2ZA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileA, File,
      ToVector("A3ZA_BothS_J_Lumi_NNNNYNNN_PointA", "A3ZA_BothS_J_Lumi_YYYYYYYY_PointA",
         "A3ZA_BothS_I_Lumi_NNNNYNNN_PointA", "A3ZA_BothS_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A3ZA (J)", "Float all (J)", "Float only A3ZA (I)", "Float all (I)"),
      "Signal only, A3ZA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileA, File,
      ToVector("A4ZA_BothS_J_Lumi_NNNNNYNN_PointA", "A4ZA_BothS_J_Lumi_YYYYYYYY_PointA",
         "A4ZA_BothS_I_Lumi_NNNNNYNN_PointA", "A4ZA_BothS_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A4ZA (J)", "Float all (J)", "Float only A4ZA (I)", "Float all (I)"),
      "Signal only, A4ZA",
      "N_{S} / #epsilon", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileA, File,
      ToVector("A2AA_BothS_J_Lumi_NNNNNNYN_PointA", "A2AA_BothS_J_Lumi_YYYYYYYY_PointA",
         "A2AA_BothS_I_Lumi_NNNNNNYN_PointA", "A2AA_BothS_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A2AA (J)", "Float all (J)", "Float only A2AA (I)", "Float all (I)"),
      "Signal only, A2AA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A3AA_BothS_J_Lumi_NNNNNNNY_PointA", "A3AA_BothS_J_Lumi_YYYYYYYY_PointA",
         "A3AA_BothS_I_Lumi_NNNNNNNY_PointA", "A3AA_BothS_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A3AA (J)", "Float all (J)", "Float only A3AA (I)", "Float all (I)"),
      "Signal only, A3AA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{#gamma#gamma})", 0);
   
   PsFileA.AddTextPage("Comparison of cut I and cut J, signal + background");
   PsFileA.InsertNamedDestination("IJSB");
   
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_Both_J_Lumi_YNNNNNNN_PointA", "A2ZZ_Both_J_Lumi_YYYYYYYY_PointA",
         "A2ZZ_Both_I_Lumi_YNNNNNNN_PointA", "A2ZZ_Both_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A2ZZ (J)", "Float all (J)", "Float only A2ZZ (I)", "Float all (I)"),
      "S+B, A2ZZ",
      "N_{S} / #epsilon", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A3ZZ_Both_J_Lumi_NYNNNNNN_PointA", "A3ZZ_Both_J_Lumi_YYYYYYYY_PointA",
         "A3ZZ_Both_I_Lumi_NYNNNNNN_PointA", "A3ZZ_Both_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A3ZZ (J)", "Float all (J)", "Float only A3ZZ (I)", "Float all (I)"),
      "S+B, A3ZZ",
      "N_{S} / #epsilon", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A4ZZ_Both_J_Lumi_NNYNNNNN_PointA", "A4ZZ_Both_J_Lumi_YYYYYYYY_PointA",
         "A4ZZ_Both_I_Lumi_NNYNNNNN_PointA", "A4ZZ_Both_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A4ZZ (J)", "Float all (J)", "Float only A4ZZ (I)", "Float all (I)"),
      "S+B, A4ZZ",
      "N_{S} / #epsilon", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A2ZA_Both_J_Lumi_NNNYNNNN_PointA", "A2ZA_Both_J_Lumi_YYYYYYYY_PointA",
         "A2ZA_Both_I_Lumi_NNNYNNNN_PointA", "A2ZA_Both_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A2ZA (J)", "Float all (J)", "Float only A2ZA (I)", "Float all (I)"),
      "S+B, A2ZA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileA, File,
      ToVector("A3ZA_Both_J_Lumi_NNNNYNNN_PointA", "A3ZA_Both_J_Lumi_YYYYYYYY_PointA",
         "A3ZA_Both_I_Lumi_NNNNYNNN_PointA", "A3ZA_Both_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A3ZA (J)", "Float all (J)", "Float only A3ZA (I)", "Float all (I)"),
      "S+B, A3ZA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileA, File,
      ToVector("A4ZA_Both_J_Lumi_NNNNNYNN_PointA", "A4ZA_Both_J_Lumi_YYYYYYYY_PointA",
         "A4ZA_Both_I_Lumi_NNNNNYNN_PointA", "A4ZA_Both_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A4ZA (J)", "Float all (J)", "Float only A4ZA (I)", "Float all (I)"),
      "S+B, A4ZA",
      "N_{S} / #epsilon", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileA, File,
      ToVector("A2AA_Both_J_Lumi_NNNNNNYN_PointA", "A2AA_Both_J_Lumi_YYYYYYYY_PointA",
         "A2AA_Both_I_Lumi_NNNNNNYN_PointA", "A2AA_Both_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A2AA (J)", "Float all (J)", "Float only A2AA (I)", "Float all (I)"),
      "S+B, A2AA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A3AA_Both_J_Lumi_NNNNNNNY_PointA", "A3AA_Both_J_Lumi_YYYYYYYY_PointA",
         "A3AA_Both_I_Lumi_NNNNNNNY_PointA", "A3AA_Both_I_Lumi_YYYYYYYY_PointA"),
      ToVector("Float only A3AA (J)", "Float all (J)", "Float only A3AA (I)", "Float all (I)"),
      "S+B, A3AA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{#gamma#gamma})", 0);
   AddPlot(PsFileA, File,
      ToVector("FEM_Both_I_Lumi_YYYYYYYY_PointA", "FEM_Both_J_Lumi_YYYYYYYY_PointA",
         "FEE_Both_I_Lumi_YYYYYYYY_PointA", "FEE_Both_J_Lumi_YYYYYYYY_PointA"),
      ToVector("F_{2e2#mu}, I", "F_{2e2#mu}, J", "F_{4e}, I", "F_{4e}, J"),
      "Background fractions, floating all couplings",
      "N_{S} / #epsilon", "Fraction", 0);
   
   PsFileA.AddTextPage("Comparison of signal only and signal + background (J)");
   PsFileA.InsertNamedDestination("SSBJ");
   
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_Both_J_Count_YNNNNNNN_PointA", "A2ZZ_Both_J_Count_YYYYYYYY_PointA",
         "A2ZZ_BothS_J_Count_YNNNNNNN_PointA", "A2ZZ_BothS_J_Count_YYYYYYYY_PointA"),
      ToVector("Float only A2ZZ (S+B)", "Float all (S+B)", "Float only A2ZZ (S)", "Float all (S)"),
      "J Cut, A2ZZ",
      "N_{S}", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A3ZZ_Both_J_Count_NYNNNNNN_PointA", "A3ZZ_Both_J_Count_YYYYYYYY_PointA",
         "A3ZZ_BothS_J_Count_NYNNNNNN_PointA", "A3ZZ_BothS_J_Count_YYYYYYYY_PointA"),
      ToVector("Float only A3ZZ (S+B)", "Float all (S+B)", "Float only A3ZZ (S)", "Float all (S)"),
      "J Cut, A3ZZ",
      "N_{S}", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A4ZZ_Both_J_Count_NNYNNNNN_PointA", "A4ZZ_Both_J_Count_YYYYYYYY_PointA",
         "A4ZZ_BothS_J_Count_NNYNNNNN_PointA", "A4ZZ_BothS_J_Count_YYYYYYYY_PointA"),
      ToVector("Float only A4ZZ (S+B)", "Float all (S+B)", "Float only A4ZZ (S)", "Float all (S)"),
      "J Cut, A4ZZ",
      "N_{S}", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A2ZA_Both_J_Count_NNNYNNNN_PointA", "A2ZA_Both_J_Count_YYYYYYYY_PointA",
         "A2ZA_BothS_J_Count_NNNYNNNN_PointA", "A2ZA_BothS_J_Count_YYYYYYYY_PointA"),
      ToVector("Float only A2ZA (S+B)", "Float all (S+B)", "Float only A2ZA (S)", "Float all (S)"),
      "J Cut, A2ZA",
      "N_{S}", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileA, File,
      ToVector("A3ZA_Both_J_Count_NNNNYNNN_PointA", "A3ZA_Both_J_Count_YYYYYYYY_PointA",
         "A3ZA_BothS_J_Count_NNNNYNNN_PointA", "A3ZA_BothS_J_Count_YYYYYYYY_PointA"),
      ToVector("Float only A3ZA (S+B)", "Float all (S+B)", "Float only A3ZA (S)", "Float all (S)"),
      "J Cut, A3ZA",
      "N_{S}", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileA, File,
      ToVector("A4ZA_Both_J_Count_NNNNNYNN_PointA", "A4ZA_Both_J_Count_YYYYYYYY_PointA",
         "A4ZA_BothS_J_Count_NNNNNYNN_PointA", "A4ZA_BothS_J_Count_YYYYYYYY_PointA"),
      ToVector("Float only A4ZA (S+B)", "Float all (S+B)", "Float only A4ZA (S)", "Float all (S)"),
      "J Cut, A4ZA",
      "N_{S}", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileA, File,
      ToVector("A2AA_Both_J_Count_NNNNNNYN_PointA", "A2AA_Both_J_Count_YYYYYYYY_PointA",
         "A2AA_BothS_J_Count_NNNNNNYN_PointA", "A2AA_BothS_J_Count_YYYYYYYY_PointA"),
      ToVector("Float only A2AA (S+B)", "Float all (S+B)", "Float only A2AA (S)", "Float all (S)"),
      "J Cut, A2AA",
      "N_{S}", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A3AA_Both_J_Count_NNNNNNNY_PointA", "A3AA_Both_J_Count_YYYYYYYY_PointA",
         "A3AA_BothS_J_Count_NNNNNNNY_PointA", "A3AA_BothS_J_Count_YYYYYYYY_PointA"),
      ToVector("Float only A3AA (S+B)", "Float all (S+B)", "Float only A3AA (S)", "Float all (S)"),
      "J Cut, A3AA",
      "N_{S}", "#sigma(A_{3}^{#gamma#gamma})", 0);
   
   PsFileA.AddTextPage("Comparison of signal only and signal + background (I)");
   PsFileA.InsertNamedDestination("SSBI");
   
   AddPlot(PsFileA, File,
      ToVector("A2ZZ_Both_I_Count_YNNNNNNN_PointA", "A2ZZ_Both_I_Count_YYYYYYYY_PointA",
         "A2ZZ_BothS_I_Count_YNNNNNNN_PointA", "A2ZZ_BothS_I_Count_YYYYYYYY_PointA"),
      ToVector("Float only A2ZZ (S+B)", "Float all (S+B)", "Float only A2ZZ (S)", "Float all (S)"),
      "I Cut, A2ZZ",
      "N_{S}", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A3ZZ_Both_I_Count_NYNNNNNN_PointA", "A3ZZ_Both_I_Count_YYYYYYYY_PointA",
         "A3ZZ_BothS_I_Count_NYNNNNNN_PointA", "A3ZZ_BothS_I_Count_YYYYYYYY_PointA"),
      ToVector("Float only A3ZZ (S+B)", "Float all (S+B)", "Float only A3ZZ (S)", "Float all (S)"),
      "I Cut, A3ZZ",
      "N_{S}", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A4ZZ_Both_I_Count_NNYNNNNN_PointA", "A4ZZ_Both_I_Count_YYYYYYYY_PointA",
         "A4ZZ_BothS_I_Count_NNYNNNNN_PointA", "A4ZZ_BothS_I_Count_YYYYYYYY_PointA"),
      ToVector("Float only A4ZZ (S+B)", "Float all (S+B)", "Float only A4ZZ (S)", "Float all (S)"),
      "I Cut, A4ZZ",
      "N_{S}", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileA, File,
      ToVector("A2ZA_Both_I_Count_NNNYNNNN_PointA", "A2ZA_Both_I_Count_YYYYYYYY_PointA",
         "A2ZA_BothS_I_Count_NNNYNNNN_PointA", "A2ZA_BothS_I_Count_YYYYYYYY_PointA"),
      ToVector("Float only A2ZA (S+B)", "Float all (S+B)", "Float only A2ZA (S)", "Float all (S)"),
      "I Cut, A2ZA",
      "N_{S}", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileA, File,
      ToVector("A3ZA_Both_I_Count_NNNNYNNN_PointA", "A3ZA_Both_I_Count_YYYYYYYY_PointA",
         "A3ZA_BothS_I_Count_NNNNYNNN_PointA", "A3ZA_BothS_I_Count_YYYYYYYY_PointA"),
      ToVector("Float only A3ZA (S+B)", "Float all (S+B)", "Float only A3ZA (S)", "Float all (S)"),
      "I Cut, A3ZA",
      "N_{S}", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileA, File,
      ToVector("A4ZA_Both_I_Count_NNNNNYNN_PointA", "A4ZA_Both_I_Count_YYYYYYYY_PointA",
         "A4ZA_BothS_I_Count_NNNNNYNN_PointA", "A4ZA_BothS_I_Count_YYYYYYYY_PointA"),
      ToVector("Float only A4ZA (S+B)", "Float all (S+B)", "Float only A4ZA (S)", "Float all (S)"),
      "I Cut, A4ZA",
      "N_{S}", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileA, File,
      ToVector("A2AA_Both_I_Count_NNNNNNYN_PointA", "A2AA_Both_I_Count_YYYYYYYY_PointA",
         "A2AA_BothS_I_Count_NNNNNNYN_PointA", "A2AA_BothS_I_Count_YYYYYYYY_PointA"),
      ToVector("Float only A2AA (S+B)", "Float all (S+B)", "Float only A2AA (S)", "Float all (S)"),
      "I Cut, A2AA",
      "N_{S}", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileA, File,
      ToVector("A3AA_Both_I_Count_NNNNNNNY_PointA", "A3AA_Both_I_Count_YYYYYYYY_PointA",
         "A3AA_BothS_I_Count_NNNNNNNY_PointA", "A3AA_BothS_I_Count_YYYYYYYY_PointA"),
      ToVector("Float only A3AA (S+B)", "Float all (S+B)", "Float only A3AA (S)", "Float all (S)"),
      "I Cut, A3AA",
      "N_{S}", "#sigma(A_{3}^{#gamma#gamma})", 0);

   PsFileO.AddTextPage("Comparison of all couplings, signal only");
   PsFileO.InsertNamedDestination("AllS");

   AddPlot(PsFileO, File,
      ToVector("A2ZZ_BothS_I_Count_YYYYYYYY_PointO",
         "A3ZZ_BothS_I_Count_YYYYYYYY_PointO",
         "A4ZZ_BothS_I_Count_YYYYYYYY_PointO",
         "A2ZA_BothS_I_Count_YYYYYYYY_PointO",
         "A3ZA_BothS_I_Count_YYYYYYYY_PointO",
         "A4ZA_BothS_I_Count_YYYYYYYY_PointO",
         "A2AA_BothS_I_Count_YYYYYYYY_PointO",
         "A3AA_BothS_I_Count_YYYYYYYY_PointO"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_BothS_J_Count_YYYYYYYY_PointO",
         "A3ZZ_BothS_J_Count_YYYYYYYY_PointO",
         "A4ZZ_BothS_J_Count_YYYYYYYY_PointO",
         "A2ZA_BothS_J_Count_YYYYYYYY_PointO",
         "A3ZA_BothS_J_Count_YYYYYYYY_PointO",
         "A4ZA_BothS_J_Count_YYYYYYYY_PointO",
         "A2AA_BothS_J_Count_YYYYYYYY_PointO",
         "A3AA_BothS_J_Count_YYYYYYYY_PointO"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_BothS_I_Count_YNNNNNNN_PointO",
         "A3ZZ_BothS_I_Count_NYNNNNNN_PointO",
         "A4ZZ_BothS_I_Count_NNYNNNNN_PointO",
         "A2ZA_BothS_I_Count_NNNYNNNN_PointO",
         "A3ZA_BothS_I_Count_NNNNYNNN_PointO",
         "A4ZA_BothS_I_Count_NNNNNYNN_PointO",
         "A2AA_BothS_I_Count_NNNNNNYN_PointO",
         "A3AA_BothS_I_Count_NNNNNNNY_PointO"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_BothS_J_Count_YNNNNNNN_PointO",
         "A3ZZ_BothS_J_Count_NYNNNNNN_PointO",
         "A4ZZ_BothS_J_Count_NNYNNNNN_PointO",
         "A2ZA_BothS_J_Count_NNNYNNNN_PointO",
         "A3ZA_BothS_J_Count_NNNNYNNN_PointO",
         "A4ZA_BothS_J_Count_NNNNNYNN_PointO",
         "A2AA_BothS_J_Count_NNNNNNYN_PointO",
         "A3AA_BothS_J_Count_NNNNNNNY_PointO"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   
   PsFileO.AddTextPage("Comparison of all couplings, signal + background");
   PsFileO.InsertNamedDestination("AllSB");
   
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_Both_I_Count_YYYYYYYY_PointO",
         "A3ZZ_Both_I_Count_YYYYYYYY_PointO",
         "A4ZZ_Both_I_Count_YYYYYYYY_PointO",
         "A2ZA_Both_I_Count_YYYYYYYY_PointO",
         "A3ZA_Both_I_Count_YYYYYYYY_PointO",
         "A4ZA_Both_I_Count_YYYYYYYY_PointO",
         "A2AA_Both_I_Count_YYYYYYYY_PointO",
         "A3AA_Both_I_Count_YYYYYYYY_PointO"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float everything, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_Both_J_Count_YYYYYYYY_PointO",
         "A3ZZ_Both_J_Count_YYYYYYYY_PointO",
         "A4ZZ_Both_J_Count_YYYYYYYY_PointO",
         "A2ZA_Both_J_Count_YYYYYYYY_PointO",
         "A3ZA_Both_J_Count_YYYYYYYY_PointO",
         "A4ZA_Both_J_Count_YYYYYYYY_PointO",
         "A2AA_Both_J_Count_YYYYYYYY_PointO",
         "A3AA_Both_J_Count_YYYYYYYY_PointO"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float everything, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_Both_I_Count_YNNNNNNN_PointO",
         "A3ZZ_Both_I_Count_NYNNNNNN_PointO",
         "A4ZZ_Both_I_Count_NNYNNNNN_PointO",
         "A2ZA_Both_I_Count_NNNYNNNN_PointO",
         "A3ZA_Both_I_Count_NNNNYNNN_PointO",
         "A4ZA_Both_I_Count_NNNNNYNN_PointO",
         "A2AA_Both_I_Count_NNNNNNYN_PointO",
         "A3AA_Both_I_Count_NNNNNNNY_PointO"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float each of them separately, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_Both_J_Count_YNNNNNNN_PointO",
         "A3ZZ_Both_J_Count_NYNNNNNN_PointO",
         "A4ZZ_Both_J_Count_NNYNNNNN_PointO",
         "A2ZA_Both_J_Count_NNNYNNNN_PointO",
         "A3ZA_Both_J_Count_NNNNYNNN_PointO",
         "A4ZA_Both_J_Count_NNNNNYNN_PointO",
         "A2AA_Both_J_Count_NNNNNNYN_PointO",
         "A3AA_Both_J_Count_NNNNNNNY_PointO"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float each of them separately, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   
   PsFileO.AddTextPage("Comparison of cut I and cut J, signal only");
   PsFileO.InsertNamedDestination("IJS");
   
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_BothS_J_Lumi_YNNNNNNN_PointO", "A2ZZ_BothS_J_Lumi_YYYYYYYY_PointO",
         "A2ZZ_BothS_I_Lumi_YNNNNNNN_PointO", "A2ZZ_BothS_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A2ZZ (J)", "Float all (J)", "Float only A2ZZ (I)", "Float all (I)"),
      "Signal only, A2ZZ",
      "N_{S} / #epsilon", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A3ZZ_BothS_J_Lumi_NYNNNNNN_PointO", "A3ZZ_BothS_J_Lumi_YYYYYYYY_PointO",
         "A3ZZ_BothS_I_Lumi_NYNNNNNN_PointO", "A3ZZ_BothS_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A3ZZ (J)", "Float all (J)", "Float only A3ZZ (I)", "Float all (I)"),
      "Signal only, A3ZZ",
      "N_{S} / #epsilon", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A4ZZ_BothS_J_Lumi_NNYNNNNN_PointO", "A4ZZ_BothS_J_Lumi_YYYYYYYY_PointO",
         "A4ZZ_BothS_I_Lumi_NNYNNNNN_PointO", "A4ZZ_BothS_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A4ZZ (J)", "Float all (J)", "Float only A4ZZ (I)", "Float all (I)"),
      "Signal only, A4ZZ",
      "N_{S} / #epsilon", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A2ZA_BothS_J_Lumi_NNNYNNNN_PointO", "A2ZA_BothS_J_Lumi_YYYYYYYY_PointO",
         "A2ZA_BothS_I_Lumi_NNNYNNNN_PointO", "A2ZA_BothS_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A2ZA (J)", "Float all (J)", "Float only A2ZA (I)", "Float all (I)"),
      "Signal only, A2ZA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileO, File,
      ToVector("A3ZA_BothS_J_Lumi_NNNNYNNN_PointO", "A3ZA_BothS_J_Lumi_YYYYYYYY_PointO",
         "A3ZA_BothS_I_Lumi_NNNNYNNN_PointO", "A3ZA_BothS_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A3ZA (J)", "Float all (J)", "Float only A3ZA (I)", "Float all (I)"),
      "Signal only, A3ZA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileO, File,
      ToVector("A4ZA_BothS_J_Lumi_NNNNNYNN_PointO", "A4ZA_BothS_J_Lumi_YYYYYYYY_PointO",
         "A4ZA_BothS_I_Lumi_NNNNNYNN_PointO", "A4ZA_BothS_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A4ZA (J)", "Float all (J)", "Float only A4ZA (I)", "Float all (I)"),
      "Signal only, A4ZA",
      "N_{S} / #epsilon", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileO, File,
      ToVector("A2AA_BothS_J_Lumi_NNNNNNYN_PointO", "A2AA_BothS_J_Lumi_YYYYYYYY_PointO",
         "A2AA_BothS_I_Lumi_NNNNNNYN_PointO", "A2AA_BothS_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A2AA (J)", "Float all (J)", "Float only A2AA (I)", "Float all (I)"),
      "Signal only, A2AA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A3AA_BothS_J_Lumi_NNNNNNNY_PointO", "A3AA_BothS_J_Lumi_YYYYYYYY_PointO",
         "A3AA_BothS_I_Lumi_NNNNNNNY_PointO", "A3AA_BothS_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A3AA (J)", "Float all (J)", "Float only A3AA (I)", "Float all (I)"),
      "Signal only, A3AA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{#gamma#gamma})", 0);
   
   PsFileO.AddTextPage("Comparison of cut I and cut J, signal + background");
   PsFileO.InsertNamedDestination("IJSB");
   
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_Both_J_Lumi_YNNNNNNN_PointO", "A2ZZ_Both_J_Lumi_YYYYYYYY_PointO",
         "A2ZZ_Both_I_Lumi_YNNNNNNN_PointO", "A2ZZ_Both_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A2ZZ (J)", "Float all (J)", "Float only A2ZZ (I)", "Float all (I)"),
      "S+B, A2ZZ",
      "N_{S} / #epsilon", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A3ZZ_Both_J_Lumi_NYNNNNNN_PointO", "A3ZZ_Both_J_Lumi_YYYYYYYY_PointO",
         "A3ZZ_Both_I_Lumi_NYNNNNNN_PointO", "A3ZZ_Both_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A3ZZ (J)", "Float all (J)", "Float only A3ZZ (I)", "Float all (I)"),
      "S+B, A3ZZ",
      "N_{S} / #epsilon", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A4ZZ_Both_J_Lumi_NNYNNNNN_PointO", "A4ZZ_Both_J_Lumi_YYYYYYYY_PointO",
         "A4ZZ_Both_I_Lumi_NNYNNNNN_PointO", "A4ZZ_Both_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A4ZZ (J)", "Float all (J)", "Float only A4ZZ (I)", "Float all (I)"),
      "S+B, A4ZZ",
      "N_{S} / #epsilon", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A2ZA_Both_J_Lumi_NNNYNNNN_PointO", "A2ZA_Both_J_Lumi_YYYYYYYY_PointO",
         "A2ZA_Both_I_Lumi_NNNYNNNN_PointO", "A2ZA_Both_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A2ZA (J)", "Float all (J)", "Float only A2ZA (I)", "Float all (I)"),
      "S+B, A2ZA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileO, File,
      ToVector("A3ZA_Both_J_Lumi_NNNNYNNN_PointO", "A3ZA_Both_J_Lumi_YYYYYYYY_PointO",
         "A3ZA_Both_I_Lumi_NNNNYNNN_PointO", "A3ZA_Both_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A3ZA (J)", "Float all (J)", "Float only A3ZA (I)", "Float all (I)"),
      "S+B, A3ZA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileO, File,
      ToVector("A4ZA_Both_J_Lumi_NNNNNYNN_PointO", "A4ZA_Both_J_Lumi_YYYYYYYY_PointO",
         "A4ZA_Both_I_Lumi_NNNNNYNN_PointO", "A4ZA_Both_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A4ZA (J)", "Float all (J)", "Float only A4ZA (I)", "Float all (I)"),
      "S+B, A4ZA",
      "N_{S} / #epsilon", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileO, File,
      ToVector("A2AA_Both_J_Lumi_NNNNNNYN_PointO", "A2AA_Both_J_Lumi_YYYYYYYY_PointO",
         "A2AA_Both_I_Lumi_NNNNNNYN_PointO", "A2AA_Both_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A2AA (J)", "Float all (J)", "Float only A2AA (I)", "Float all (I)"),
      "S+B, A2AA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A3AA_Both_J_Lumi_NNNNNNNY_PointO", "A3AA_Both_J_Lumi_YYYYYYYY_PointO",
         "A3AA_Both_I_Lumi_NNNNNNNY_PointO", "A3AA_Both_I_Lumi_YYYYYYYY_PointO"),
      ToVector("Float only A3AA (J)", "Float all (J)", "Float only A3AA (I)", "Float all (I)"),
      "S+B, A3AA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{#gamma#gamma})", 0);
   AddPlot(PsFileO, File,
      ToVector("FEM_Both_I_Lumi_YYYYYYYY_PointO", "FEM_Both_J_Lumi_YYYYYYYY_PointO",
         "FEE_Both_I_Lumi_YYYYYYYY_PointO", "FEE_Both_J_Lumi_YYYYYYYY_PointO"),
      ToVector("F_{2e2#mu}, I", "F_{2e2#mu}, J", "F_{4e}, I", "F_{4e}, J"),
      "Background fractions, floating all couplings",
      "N_{S} / #epsilon", "Fraction", 0);
   
   PsFileO.AddTextPage("Comparison of signal only and signal + background (J)");
   PsFileO.InsertNamedDestination("SSBJ");
   
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_Both_J_Count_YNNNNNNN_PointO", "A2ZZ_Both_J_Count_YYYYYYYY_PointO",
         "A2ZZ_BothS_J_Count_YNNNNNNN_PointO", "A2ZZ_BothS_J_Count_YYYYYYYY_PointO"),
      ToVector("Float only A2ZZ (S+B)", "Float all (S+B)", "Float only A2ZZ (S)", "Float all (S)"),
      "J Cut, A2ZZ",
      "N_{S}", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A3ZZ_Both_J_Count_NYNNNNNN_PointO", "A3ZZ_Both_J_Count_YYYYYYYY_PointO",
         "A3ZZ_BothS_J_Count_NYNNNNNN_PointO", "A3ZZ_BothS_J_Count_YYYYYYYY_PointO"),
      ToVector("Float only A3ZZ (S+B)", "Float all (S+B)", "Float only A3ZZ (S)", "Float all (S)"),
      "J Cut, A3ZZ",
      "N_{S}", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A4ZZ_Both_J_Count_NNYNNNNN_PointO", "A4ZZ_Both_J_Count_YYYYYYYY_PointO",
         "A4ZZ_BothS_J_Count_NNYNNNNN_PointO", "A4ZZ_BothS_J_Count_YYYYYYYY_PointO"),
      ToVector("Float only A4ZZ (S+B)", "Float all (S+B)", "Float only A4ZZ (S)", "Float all (S)"),
      "J Cut, A4ZZ",
      "N_{S}", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A2ZA_Both_J_Count_NNNYNNNN_PointO", "A2ZA_Both_J_Count_YYYYYYYY_PointO",
         "A2ZA_BothS_J_Count_NNNYNNNN_PointO", "A2ZA_BothS_J_Count_YYYYYYYY_PointO"),
      ToVector("Float only A2ZA (S+B)", "Float all (S+B)", "Float only A2ZA (S)", "Float all (S)"),
      "J Cut, A2ZA",
      "N_{S}", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileO, File,
      ToVector("A3ZA_Both_J_Count_NNNNYNNN_PointO", "A3ZA_Both_J_Count_YYYYYYYY_PointO",
         "A3ZA_BothS_J_Count_NNNNYNNN_PointO", "A3ZA_BothS_J_Count_YYYYYYYY_PointO"),
      ToVector("Float only A3ZA (S+B)", "Float all (S+B)", "Float only A3ZA (S)", "Float all (S)"),
      "J Cut, A3ZA",
      "N_{S}", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileO, File,
      ToVector("A4ZA_Both_J_Count_NNNNNYNN_PointO", "A4ZA_Both_J_Count_YYYYYYYY_PointO",
         "A4ZA_BothS_J_Count_NNNNNYNN_PointO", "A4ZA_BothS_J_Count_YYYYYYYY_PointO"),
      ToVector("Float only A4ZA (S+B)", "Float all (S+B)", "Float only A4ZA (S)", "Float all (S)"),
      "J Cut, A4ZA",
      "N_{S}", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileO, File,
      ToVector("A2AA_Both_J_Count_NNNNNNYN_PointO", "A2AA_Both_J_Count_YYYYYYYY_PointO",
         "A2AA_BothS_J_Count_NNNNNNYN_PointO", "A2AA_BothS_J_Count_YYYYYYYY_PointO"),
      ToVector("Float only A2AA (S+B)", "Float all (S+B)", "Float only A2AA (S)", "Float all (S)"),
      "J Cut, A2AA",
      "N_{S}", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A3AA_Both_J_Count_NNNNNNNY_PointO", "A3AA_Both_J_Count_YYYYYYYY_PointO",
         "A3AA_BothS_J_Count_NNNNNNNY_PointO", "A3AA_BothS_J_Count_YYYYYYYY_PointO"),
      ToVector("Float only A3AA (S+B)", "Float all (S+B)", "Float only A3AA (S)", "Float all (S)"),
      "J Cut, A3AA",
      "N_{S}", "#sigma(A_{3}^{#gamma#gamma})", 0);
   
   PsFileO.AddTextPage("Comparison of signal only and signal + background (I)");
   PsFileO.InsertNamedDestination("SSBI");
   
   AddPlot(PsFileO, File,
      ToVector("A2ZZ_Both_I_Count_YNNNNNNN_PointO", "A2ZZ_Both_I_Count_YYYYYYYY_PointO",
         "A2ZZ_BothS_I_Count_YNNNNNNN_PointO", "A2ZZ_BothS_I_Count_YYYYYYYY_PointO"),
      ToVector("Float only A2ZZ (S+B)", "Float all (S+B)", "Float only A2ZZ (S)", "Float all (S)"),
      "I Cut, A2ZZ",
      "N_{S}", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A3ZZ_Both_I_Count_NYNNNNNN_PointO", "A3ZZ_Both_I_Count_YYYYYYYY_PointO",
         "A3ZZ_BothS_I_Count_NYNNNNNN_PointO", "A3ZZ_BothS_I_Count_YYYYYYYY_PointO"),
      ToVector("Float only A3ZZ (S+B)", "Float all (S+B)", "Float only A3ZZ (S)", "Float all (S)"),
      "I Cut, A3ZZ",
      "N_{S}", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A4ZZ_Both_I_Count_NNYNNNNN_PointO", "A4ZZ_Both_I_Count_YYYYYYYY_PointO",
         "A4ZZ_BothS_I_Count_NNYNNNNN_PointO", "A4ZZ_BothS_I_Count_YYYYYYYY_PointO"),
      ToVector("Float only A4ZZ (S+B)", "Float all (S+B)", "Float only A4ZZ (S)", "Float all (S)"),
      "I Cut, A4ZZ",
      "N_{S}", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileO, File,
      ToVector("A2ZA_Both_I_Count_NNNYNNNN_PointO", "A2ZA_Both_I_Count_YYYYYYYY_PointO",
         "A2ZA_BothS_I_Count_NNNYNNNN_PointO", "A2ZA_BothS_I_Count_YYYYYYYY_PointO"),
      ToVector("Float only A2ZA (S+B)", "Float all (S+B)", "Float only A2ZA (S)", "Float all (S)"),
      "I Cut, A2ZA",
      "N_{S}", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileO, File,
      ToVector("A3ZA_Both_I_Count_NNNNYNNN_PointO", "A3ZA_Both_I_Count_YYYYYYYY_PointO",
         "A3ZA_BothS_I_Count_NNNNYNNN_PointO", "A3ZA_BothS_I_Count_YYYYYYYY_PointO"),
      ToVector("Float only A3ZA (S+B)", "Float all (S+B)", "Float only A3ZA (S)", "Float all (S)"),
      "I Cut, A3ZA",
      "N_{S}", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileO, File,
      ToVector("A4ZA_Both_I_Count_NNNNNYNN_PointO", "A4ZA_Both_I_Count_YYYYYYYY_PointO",
         "A4ZA_BothS_I_Count_NNNNNYNN_PointO", "A4ZA_BothS_I_Count_YYYYYYYY_PointO"),
      ToVector("Float only A4ZA (S+B)", "Float all (S+B)", "Float only A4ZA (S)", "Float all (S)"),
      "I Cut, A4ZA",
      "N_{S}", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileO, File,
      ToVector("A2AA_Both_I_Count_NNNNNNYN_PointO", "A2AA_Both_I_Count_YYYYYYYY_PointO",
         "A2AA_BothS_I_Count_NNNNNNYN_PointO", "A2AA_BothS_I_Count_YYYYYYYY_PointO"),
      ToVector("Float only A2AA (S+B)", "Float all (S+B)", "Float only A2AA (S)", "Float all (S)"),
      "I Cut, A2AA",
      "N_{S}", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileO, File,
      ToVector("A3AA_Both_I_Count_NNNNNNNY_PointO", "A3AA_Both_I_Count_YYYYYYYY_PointO",
         "A3AA_BothS_I_Count_NNNNNNNY_PointO", "A3AA_BothS_I_Count_YYYYYYYY_PointO"),
      ToVector("Float only A3AA (S+B)", "Float all (S+B)", "Float only A3AA (S)", "Float all (S)"),
      "I Cut, A3AA",
      "N_{S}", "#sigma(A_{3}^{#gamma#gamma})", 0);

   PsFile0.AddTextPage("Comparison of all couplings, signal only");
   PsFile0.InsertNamedDestination("AllS");

   AddPlot(PsFile0, File,
      ToVector("A2ZZ_BothS_I_Count_YYYYYYYY_Point0",
         "A3ZZ_BothS_I_Count_YYYYYYYY_Point0",
         "A4ZZ_BothS_I_Count_YYYYYYYY_Point0",
         "A2ZA_BothS_I_Count_YYYYYYYY_Point0",
         "A3ZA_BothS_I_Count_YYYYYYYY_Point0",
         "A4ZA_BothS_I_Count_YYYYYYYY_Point0",
         "A2AA_BothS_I_Count_YYYYYYYY_Point0",
         "A3AA_BothS_I_Count_YYYYYYYY_Point0"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_BothS_J_Count_YYYYYYYY_Point0",
         "A3ZZ_BothS_J_Count_YYYYYYYY_Point0",
         "A4ZZ_BothS_J_Count_YYYYYYYY_Point0",
         "A2ZA_BothS_J_Count_YYYYYYYY_Point0",
         "A3ZA_BothS_J_Count_YYYYYYYY_Point0",
         "A4ZA_BothS_J_Count_YYYYYYYY_Point0",
         "A2AA_BothS_J_Count_YYYYYYYY_Point0",
         "A3AA_BothS_J_Count_YYYYYYYY_Point0"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_BothS_I_Count_YNNNNNNN_Point0",
         "A3ZZ_BothS_I_Count_NYNNNNNN_Point0",
         "A4ZZ_BothS_I_Count_NNYNNNNN_Point0",
         "A2ZA_BothS_I_Count_NNNYNNNN_Point0",
         "A3ZA_BothS_I_Count_NNNNYNNN_Point0",
         "A4ZA_BothS_I_Count_NNNNNYNN_Point0",
         "A2AA_BothS_I_Count_NNNNNNYN_Point0",
         "A3AA_BothS_I_Count_NNNNNNNY_Point0"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_BothS_J_Count_YNNNNNNN_Point0",
         "A3ZZ_BothS_J_Count_NYNNNNNN_Point0",
         "A4ZZ_BothS_J_Count_NNYNNNNN_Point0",
         "A2ZA_BothS_J_Count_NNNYNNNN_Point0",
         "A3ZA_BothS_J_Count_NNNNYNNN_Point0",
         "A4ZA_BothS_J_Count_NNNNNYNN_Point0",
         "A2AA_BothS_J_Count_NNNNNNYN_Point0",
         "A3AA_BothS_J_Count_NNNNNNNY_Point0"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   
   PsFile0.AddTextPage("Comparison of all couplings, signal + background");
   PsFile0.InsertNamedDestination("AllSB");
   
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_Both_I_Count_YYYYYYYY_Point0",
         "A3ZZ_Both_I_Count_YYYYYYYY_Point0",
         "A4ZZ_Both_I_Count_YYYYYYYY_Point0",
         "A2ZA_Both_I_Count_YYYYYYYY_Point0",
         "A3ZA_Both_I_Count_YYYYYYYY_Point0",
         "A4ZA_Both_I_Count_YYYYYYYY_Point0",
         "A2AA_Both_I_Count_YYYYYYYY_Point0",
         "A3AA_Both_I_Count_YYYYYYYY_Point0"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float everything, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_Both_J_Count_YYYYYYYY_Point0",
         "A3ZZ_Both_J_Count_YYYYYYYY_Point0",
         "A4ZZ_Both_J_Count_YYYYYYYY_Point0",
         "A2ZA_Both_J_Count_YYYYYYYY_Point0",
         "A3ZA_Both_J_Count_YYYYYYYY_Point0",
         "A4ZA_Both_J_Count_YYYYYYYY_Point0",
         "A2AA_Both_J_Count_YYYYYYYY_Point0",
         "A3AA_Both_J_Count_YYYYYYYY_Point0"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float everything, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_Both_I_Count_YNNNNNNN_Point0",
         "A3ZZ_Both_I_Count_NYNNNNNN_Point0",
         "A4ZZ_Both_I_Count_NNYNNNNN_Point0",
         "A2ZA_Both_I_Count_NNNYNNNN_Point0",
         "A3ZA_Both_I_Count_NNNNYNNN_Point0",
         "A4ZA_Both_I_Count_NNNNNYNN_Point0",
         "A2AA_Both_I_Count_NNNNNNYN_Point0",
         "A3AA_Both_I_Count_NNNNNNNY_Point0"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float each of them separately, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_Both_J_Count_YNNNNNNN_Point0",
         "A3ZZ_Both_J_Count_NYNNNNNN_Point0",
         "A4ZZ_Both_J_Count_NNYNNNNN_Point0",
         "A2ZA_Both_J_Count_NNNYNNNN_Point0",
         "A3ZA_Both_J_Count_NNNNYNNN_Point0",
         "A4ZA_Both_J_Count_NNNNNYNN_Point0",
         "A2AA_Both_J_Count_NNNNNNYN_Point0",
         "A3AA_Both_J_Count_NNNNNNNY_Point0"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "S+B, float each of them separately, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   
   PsFile0.AddTextPage("Comparison of cut I and cut J, signal only");
   PsFile0.InsertNamedDestination("IJS");
   
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_BothS_J_Lumi_YNNNNNNN_Point0", "A2ZZ_BothS_J_Lumi_YYYYYYYY_Point0",
         "A2ZZ_BothS_I_Lumi_YNNNNNNN_Point0", "A2ZZ_BothS_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A2ZZ (J)", "Float all (J)", "Float only A2ZZ (I)", "Float all (I)"),
      "Signal only, A2ZZ",
      "N_{S} / #epsilon", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A3ZZ_BothS_J_Lumi_NYNNNNNN_Point0", "A3ZZ_BothS_J_Lumi_YYYYYYYY_Point0",
         "A3ZZ_BothS_I_Lumi_NYNNNNNN_Point0", "A3ZZ_BothS_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A3ZZ (J)", "Float all (J)", "Float only A3ZZ (I)", "Float all (I)"),
      "Signal only, A3ZZ",
      "N_{S} / #epsilon", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A4ZZ_BothS_J_Lumi_NNYNNNNN_Point0", "A4ZZ_BothS_J_Lumi_YYYYYYYY_Point0",
         "A4ZZ_BothS_I_Lumi_NNYNNNNN_Point0", "A4ZZ_BothS_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A4ZZ (J)", "Float all (J)", "Float only A4ZZ (I)", "Float all (I)"),
      "Signal only, A4ZZ",
      "N_{S} / #epsilon", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A2ZA_BothS_J_Lumi_NNNYNNNN_Point0", "A2ZA_BothS_J_Lumi_YYYYYYYY_Point0",
         "A2ZA_BothS_I_Lumi_NNNYNNNN_Point0", "A2ZA_BothS_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A2ZA (J)", "Float all (J)", "Float only A2ZA (I)", "Float all (I)"),
      "Signal only, A2ZA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFile0, File,
      ToVector("A3ZA_BothS_J_Lumi_NNNNYNNN_Point0", "A3ZA_BothS_J_Lumi_YYYYYYYY_Point0",
         "A3ZA_BothS_I_Lumi_NNNNYNNN_Point0", "A3ZA_BothS_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A3ZA (J)", "Float all (J)", "Float only A3ZA (I)", "Float all (I)"),
      "Signal only, A3ZA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFile0, File,
      ToVector("A4ZA_BothS_J_Lumi_NNNNNYNN_Point0", "A4ZA_BothS_J_Lumi_YYYYYYYY_Point0",
         "A4ZA_BothS_I_Lumi_NNNNNYNN_Point0", "A4ZA_BothS_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A4ZA (J)", "Float all (J)", "Float only A4ZA (I)", "Float all (I)"),
      "Signal only, A4ZA",
      "N_{S} / #epsilon", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFile0, File,
      ToVector("A2AA_BothS_J_Lumi_NNNNNNYN_Point0", "A2AA_BothS_J_Lumi_YYYYYYYY_Point0",
         "A2AA_BothS_I_Lumi_NNNNNNYN_Point0", "A2AA_BothS_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A2AA (J)", "Float all (J)", "Float only A2AA (I)", "Float all (I)"),
      "Signal only, A2AA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A3AA_BothS_J_Lumi_NNNNNNNY_Point0", "A3AA_BothS_J_Lumi_YYYYYYYY_Point0",
         "A3AA_BothS_I_Lumi_NNNNNNNY_Point0", "A3AA_BothS_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A3AA (J)", "Float all (J)", "Float only A3AA (I)", "Float all (I)"),
      "Signal only, A3AA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{#gamma#gamma})", 0);
   
   PsFile0.AddTextPage("Comparison of cut I and cut J, signal + background");
   PsFile0.InsertNamedDestination("IJSB");
   
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_Both_J_Lumi_YNNNNNNN_Point0", "A2ZZ_Both_J_Lumi_YYYYYYYY_Point0",
         "A2ZZ_Both_I_Lumi_YNNNNNNN_Point0", "A2ZZ_Both_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A2ZZ (J)", "Float all (J)", "Float only A2ZZ (I)", "Float all (I)"),
      "S+B, A2ZZ",
      "N_{S} / #epsilon", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A3ZZ_Both_J_Lumi_NYNNNNNN_Point0", "A3ZZ_Both_J_Lumi_YYYYYYYY_Point0",
         "A3ZZ_Both_I_Lumi_NYNNNNNN_Point0", "A3ZZ_Both_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A3ZZ (J)", "Float all (J)", "Float only A3ZZ (I)", "Float all (I)"),
      "S+B, A3ZZ",
      "N_{S} / #epsilon", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A4ZZ_Both_J_Lumi_NNYNNNNN_Point0", "A4ZZ_Both_J_Lumi_YYYYYYYY_Point0",
         "A4ZZ_Both_I_Lumi_NNYNNNNN_Point0", "A4ZZ_Both_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A4ZZ (J)", "Float all (J)", "Float only A4ZZ (I)", "Float all (I)"),
      "S+B, A4ZZ",
      "N_{S} / #epsilon", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A2ZA_Both_J_Lumi_NNNYNNNN_Point0", "A2ZA_Both_J_Lumi_YYYYYYYY_Point0",
         "A2ZA_Both_I_Lumi_NNNYNNNN_Point0", "A2ZA_Both_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A2ZA (J)", "Float all (J)", "Float only A2ZA (I)", "Float all (I)"),
      "S+B, A2ZA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFile0, File,
      ToVector("A3ZA_Both_J_Lumi_NNNNYNNN_Point0", "A3ZA_Both_J_Lumi_YYYYYYYY_Point0",
         "A3ZA_Both_I_Lumi_NNNNYNNN_Point0", "A3ZA_Both_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A3ZA (J)", "Float all (J)", "Float only A3ZA (I)", "Float all (I)"),
      "S+B, A3ZA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFile0, File,
      ToVector("A4ZA_Both_J_Lumi_NNNNNYNN_Point0", "A4ZA_Both_J_Lumi_YYYYYYYY_Point0",
         "A4ZA_Both_I_Lumi_NNNNNYNN_Point0", "A4ZA_Both_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A4ZA (J)", "Float all (J)", "Float only A4ZA (I)", "Float all (I)"),
      "S+B, A4ZA",
      "N_{S} / #epsilon", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFile0, File,
      ToVector("A2AA_Both_J_Lumi_NNNNNNYN_Point0", "A2AA_Both_J_Lumi_YYYYYYYY_Point0",
         "A2AA_Both_I_Lumi_NNNNNNYN_Point0", "A2AA_Both_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A2AA (J)", "Float all (J)", "Float only A2AA (I)", "Float all (I)"),
      "S+B, A2AA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A3AA_Both_J_Lumi_NNNNNNNY_Point0", "A3AA_Both_J_Lumi_YYYYYYYY_Point0",
         "A3AA_Both_I_Lumi_NNNNNNNY_Point0", "A3AA_Both_I_Lumi_YYYYYYYY_Point0"),
      ToVector("Float only A3AA (J)", "Float all (J)", "Float only A3AA (I)", "Float all (I)"),
      "S+B, A3AA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{#gamma#gamma})", 0);
   AddPlot(PsFile0, File,
      ToVector("FEM_Both_I_Lumi_YYYYYYYY_Point0", "FEM_Both_J_Lumi_YYYYYYYY_Point0",
         "FEE_Both_I_Lumi_YYYYYYYY_Point0", "FEE_Both_J_Lumi_YYYYYYYY_Point0"),
      ToVector("F_{2e2#mu}, I", "F_{2e2#mu}, J", "F_{4e}, I", "F_{4e}, J"),
      "Background fractions, floating all couplings",
      "N_{S} / #epsilon", "Fraction", 0);
   
   PsFile0.AddTextPage("Comparison of signal only and signal + background (J)");
   PsFile0.InsertNamedDestination("SSBJ");
   
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_Both_J_Count_YNNNNNNN_Point0", "A2ZZ_Both_J_Count_YYYYYYYY_Point0",
         "A2ZZ_BothS_J_Count_YNNNNNNN_Point0", "A2ZZ_BothS_J_Count_YYYYYYYY_Point0"),
      ToVector("Float only A2ZZ (S+B)", "Float all (S+B)", "Float only A2ZZ (S)", "Float all (S)"),
      "J Cut, A2ZZ",
      "N_{S}", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A3ZZ_Both_J_Count_NYNNNNNN_Point0", "A3ZZ_Both_J_Count_YYYYYYYY_Point0",
         "A3ZZ_BothS_J_Count_NYNNNNNN_Point0", "A3ZZ_BothS_J_Count_YYYYYYYY_Point0"),
      ToVector("Float only A3ZZ (S+B)", "Float all (S+B)", "Float only A3ZZ (S)", "Float all (S)"),
      "J Cut, A3ZZ",
      "N_{S}", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A4ZZ_Both_J_Count_NNYNNNNN_Point0", "A4ZZ_Both_J_Count_YYYYYYYY_Point0",
         "A4ZZ_BothS_J_Count_NNYNNNNN_Point0", "A4ZZ_BothS_J_Count_YYYYYYYY_Point0"),
      ToVector("Float only A4ZZ (S+B)", "Float all (S+B)", "Float only A4ZZ (S)", "Float all (S)"),
      "J Cut, A4ZZ",
      "N_{S}", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A2ZA_Both_J_Count_NNNYNNNN_Point0", "A2ZA_Both_J_Count_YYYYYYYY_Point0",
         "A2ZA_BothS_J_Count_NNNYNNNN_Point0", "A2ZA_BothS_J_Count_YYYYYYYY_Point0"),
      ToVector("Float only A2ZA (S+B)", "Float all (S+B)", "Float only A2ZA (S)", "Float all (S)"),
      "J Cut, A2ZA",
      "N_{S}", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFile0, File,
      ToVector("A3ZA_Both_J_Count_NNNNYNNN_Point0", "A3ZA_Both_J_Count_YYYYYYYY_Point0",
         "A3ZA_BothS_J_Count_NNNNYNNN_Point0", "A3ZA_BothS_J_Count_YYYYYYYY_Point0"),
      ToVector("Float only A3ZA (S+B)", "Float all (S+B)", "Float only A3ZA (S)", "Float all (S)"),
      "J Cut, A3ZA",
      "N_{S}", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFile0, File,
      ToVector("A4ZA_Both_J_Count_NNNNNYNN_Point0", "A4ZA_Both_J_Count_YYYYYYYY_Point0",
         "A4ZA_BothS_J_Count_NNNNNYNN_Point0", "A4ZA_BothS_J_Count_YYYYYYYY_Point0"),
      ToVector("Float only A4ZA (S+B)", "Float all (S+B)", "Float only A4ZA (S)", "Float all (S)"),
      "J Cut, A4ZA",
      "N_{S}", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFile0, File,
      ToVector("A2AA_Both_J_Count_NNNNNNYN_Point0", "A2AA_Both_J_Count_YYYYYYYY_Point0",
         "A2AA_BothS_J_Count_NNNNNNYN_Point0", "A2AA_BothS_J_Count_YYYYYYYY_Point0"),
      ToVector("Float only A2AA (S+B)", "Float all (S+B)", "Float only A2AA (S)", "Float all (S)"),
      "J Cut, A2AA",
      "N_{S}", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A3AA_Both_J_Count_NNNNNNNY_Point0", "A3AA_Both_J_Count_YYYYYYYY_Point0",
         "A3AA_BothS_J_Count_NNNNNNNY_Point0", "A3AA_BothS_J_Count_YYYYYYYY_Point0"),
      ToVector("Float only A3AA (S+B)", "Float all (S+B)", "Float only A3AA (S)", "Float all (S)"),
      "J Cut, A3AA",
      "N_{S}", "#sigma(A_{3}^{#gamma#gamma})", 0);
   
   PsFile0.AddTextPage("Comparison of signal only and signal + background (I)");
   PsFile0.InsertNamedDestination("SSBI");
   
   AddPlot(PsFile0, File,
      ToVector("A2ZZ_Both_I_Count_YNNNNNNN_Point0", "A2ZZ_Both_I_Count_YYYYYYYY_Point0",
         "A2ZZ_BothS_I_Count_YNNNNNNN_Point0", "A2ZZ_BothS_I_Count_YYYYYYYY_Point0"),
      ToVector("Float only A2ZZ (S+B)", "Float all (S+B)", "Float only A2ZZ (S)", "Float all (S)"),
      "I Cut, A2ZZ",
      "N_{S}", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A3ZZ_Both_I_Count_NYNNNNNN_Point0", "A3ZZ_Both_I_Count_YYYYYYYY_Point0",
         "A3ZZ_BothS_I_Count_NYNNNNNN_Point0", "A3ZZ_BothS_I_Count_YYYYYYYY_Point0"),
      ToVector("Float only A3ZZ (S+B)", "Float all (S+B)", "Float only A3ZZ (S)", "Float all (S)"),
      "I Cut, A3ZZ",
      "N_{S}", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A4ZZ_Both_I_Count_NNYNNNNN_Point0", "A4ZZ_Both_I_Count_YYYYYYYY_Point0",
         "A4ZZ_BothS_I_Count_NNYNNNNN_Point0", "A4ZZ_BothS_I_Count_YYYYYYYY_Point0"),
      ToVector("Float only A4ZZ (S+B)", "Float all (S+B)", "Float only A4ZZ (S)", "Float all (S)"),
      "I Cut, A4ZZ",
      "N_{S}", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFile0, File,
      ToVector("A2ZA_Both_I_Count_NNNYNNNN_Point0", "A2ZA_Both_I_Count_YYYYYYYY_Point0",
         "A2ZA_BothS_I_Count_NNNYNNNN_Point0", "A2ZA_BothS_I_Count_YYYYYYYY_Point0"),
      ToVector("Float only A2ZA (S+B)", "Float all (S+B)", "Float only A2ZA (S)", "Float all (S)"),
      "I Cut, A2ZA",
      "N_{S}", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFile0, File,
      ToVector("A3ZA_Both_I_Count_NNNNYNNN_Point0", "A3ZA_Both_I_Count_YYYYYYYY_Point0",
         "A3ZA_BothS_I_Count_NNNNYNNN_Point0", "A3ZA_BothS_I_Count_YYYYYYYY_Point0"),
      ToVector("Float only A3ZA (S+B)", "Float all (S+B)", "Float only A3ZA (S)", "Float all (S)"),
      "I Cut, A3ZA",
      "N_{S}", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFile0, File,
      ToVector("A4ZA_Both_I_Count_NNNNNYNN_Point0", "A4ZA_Both_I_Count_YYYYYYYY_Point0",
         "A4ZA_BothS_I_Count_NNNNNYNN_Point0", "A4ZA_BothS_I_Count_YYYYYYYY_Point0"),
      ToVector("Float only A4ZA (S+B)", "Float all (S+B)", "Float only A4ZA (S)", "Float all (S)"),
      "I Cut, A4ZA",
      "N_{S}", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFile0, File,
      ToVector("A2AA_Both_I_Count_NNNNNNYN_Point0", "A2AA_Both_I_Count_YYYYYYYY_Point0",
         "A2AA_BothS_I_Count_NNNNNNYN_Point0", "A2AA_BothS_I_Count_YYYYYYYY_Point0"),
      ToVector("Float only A2AA (S+B)", "Float all (S+B)", "Float only A2AA (S)", "Float all (S)"),
      "I Cut, A2AA",
      "N_{S}", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFile0, File,
      ToVector("A3AA_Both_I_Count_NNNNNNNY_Point0", "A3AA_Both_I_Count_YYYYYYYY_Point0",
         "A3AA_BothS_I_Count_NNNNNNNY_Point0", "A3AA_BothS_I_Count_YYYYYYYY_Point0"),
      ToVector("Float only A3AA (S+B)", "Float all (S+B)", "Float only A3AA (S)", "Float all (S)"),
      "I Cut, A3AA",
      "N_{S}", "#sigma(A_{3}^{#gamma#gamma})", 0);

   PsFileB.AddTextPage("Comparison of all couplings, signal only");

   AddPlot(PsFileB, File,
      ToVector("A2ZZ_BothS_I_Count_YYYYYYYY_PointB",
         "A3ZZ_BothS_I_Count_YYYYYYYY_PointB",
         "A4ZZ_BothS_I_Count_YYYYYYYY_PointB",
         "A2ZA_BothS_I_Count_YYYYYYYY_PointB",
         "A3ZA_BothS_I_Count_YYYYYYYY_PointB",
         "A4ZA_BothS_I_Count_YYYYYYYY_PointB",
         "A2AA_BothS_I_Count_YYYYYYYY_PointB",
         "A3AA_BothS_I_Count_YYYYYYYY_PointB"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileB, File,
      ToVector("A2ZZ_BothS_J_Count_YYYYYYYY_PointB",
         "A3ZZ_BothS_J_Count_YYYYYYYY_PointB",
         "A4ZZ_BothS_J_Count_YYYYYYYY_PointB",
         "A2ZA_BothS_J_Count_YYYYYYYY_PointB",
         "A3ZA_BothS_J_Count_YYYYYYYY_PointB",
         "A4ZA_BothS_J_Count_YYYYYYYY_PointB",
         "A2AA_BothS_J_Count_YYYYYYYY_PointB",
         "A3AA_BothS_J_Count_YYYYYYYY_PointB"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileB, File,
      ToVector("A2ZZ_BothS_I_Count_YNNNNNNN_PointB",
         "A3ZZ_BothS_I_Count_NYNNNNNN_PointB",
         "A4ZZ_BothS_I_Count_NNYNNNNN_PointB",
         "A2ZA_BothS_I_Count_NNNYNNNN_PointB",
         "A3ZA_BothS_I_Count_NNNNYNNN_PointB",
         "A4ZA_BothS_I_Count_NNNNNYNN_PointB",
         "A2AA_BothS_I_Count_NNNNNNYN_PointB",
         "A3AA_BothS_I_Count_NNNNNNNY_PointB"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileB, File,
      ToVector("A2ZZ_BothS_J_Count_YNNNNNNN_PointB",
         "A3ZZ_BothS_J_Count_NYNNNNNN_PointB",
         "A4ZZ_BothS_J_Count_NNYNNNNN_PointB",
         "A2ZA_BothS_J_Count_NNNYNNNN_PointB",
         "A3ZA_BothS_J_Count_NNNNYNNN_PointB",
         "A4ZA_BothS_J_Count_NNNNNYNN_PointB",
         "A2AA_BothS_J_Count_NNNNNNYN_PointB",
         "A3AA_BothS_J_Count_NNNNNNNY_PointB"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);

   AddPlot(PsFileB, File,
      ToVector("A2ZZ_BothS_J_Lumi_YNNNNNNN_PointB", "A2ZZ_BothS_J_Lumi_YYYYYYYY_PointB",
         "A2ZZ_BothS_I_Lumi_YNNNNNNN_PointB", "A2ZZ_BothS_I_Lumi_YYYYYYYY_PointB"),
      ToVector("Float only A2ZZ (J)", "Float all (J)", "Float only A2ZZ (I)", "Float all (I)"),
      "Signal only, A2ZZ",
      "N_{S} / #epsilon", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileB, File,
      ToVector("A3ZZ_BothS_J_Lumi_NYNNNNNN_PointB", "A3ZZ_BothS_J_Lumi_YYYYYYYY_PointB",
         "A3ZZ_BothS_I_Lumi_NYNNNNNN_PointB", "A3ZZ_BothS_I_Lumi_YYYYYYYY_PointB"),
      ToVector("Float only A3ZZ (J)", "Float all (J)", "Float only A3ZZ (I)", "Float all (I)"),
      "Signal only, A3ZZ",
      "N_{S} / #epsilon", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileB, File,
      ToVector("A4ZZ_BothS_J_Lumi_NNYNNNNN_PointB", "A4ZZ_BothS_J_Lumi_YYYYYYYY_PointB",
         "A4ZZ_BothS_I_Lumi_NNYNNNNN_PointB", "A4ZZ_BothS_I_Lumi_YYYYYYYY_PointB"),
      ToVector("Float only A4ZZ (J)", "Float all (J)", "Float only A4ZZ (I)", "Float all (I)"),
      "Signal only, A4ZZ",
      "N_{S} / #epsilon", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileB, File,
      ToVector("A2ZA_BothS_J_Lumi_NNNYNNNN_PointB", "A2ZA_BothS_J_Lumi_YYYYYYYY_PointB",
         "A2ZA_BothS_I_Lumi_NNNYNNNN_PointB", "A2ZA_BothS_I_Lumi_YYYYYYYY_PointB"),
      ToVector("Float only A2ZA (J)", "Float all (J)", "Float only A2ZA (I)", "Float all (I)"),
      "Signal only, A2ZA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileB, File,
      ToVector("A3ZA_BothS_J_Lumi_NNNNYNNN_PointB", "A3ZA_BothS_J_Lumi_YYYYYYYY_PointB",
         "A3ZA_BothS_I_Lumi_NNNNYNNN_PointB", "A3ZA_BothS_I_Lumi_YYYYYYYY_PointB"),
      ToVector("Float only A3ZA (J)", "Float all (J)", "Float only A3ZA (I)", "Float all (I)"),
      "Signal only, A3ZA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileB, File,
      ToVector("A4ZA_BothS_J_Lumi_NNNNNYNN_PointB", "A4ZA_BothS_J_Lumi_YYYYYYYY_PointB",
         "A4ZA_BothS_I_Lumi_NNNNNYNN_PointB", "A4ZA_BothS_I_Lumi_YYYYYYYY_PointB"),
      ToVector("Float only A4ZA (J)", "Float all (J)", "Float only A4ZA (I)", "Float all (I)"),
      "Signal only, A4ZA",
      "N_{S} / #epsilon", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileB, File,
      ToVector("A2AA_BothS_J_Lumi_NNNNNNYN_PointB", "A2AA_BothS_J_Lumi_YYYYYYYY_PointB",
         "A2AA_BothS_I_Lumi_NNNNNNYN_PointB", "A2AA_BothS_I_Lumi_YYYYYYYY_PointB"),
      ToVector("Float only A2AA (J)", "Float all (J)", "Float only A2AA (I)", "Float all (I)"),
      "Signal only, A2AA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileB, File,
      ToVector("A3AA_BothS_J_Lumi_NNNNNNNY_PointB", "A3AA_BothS_J_Lumi_YYYYYYYY_PointB",
         "A3AA_BothS_I_Lumi_NNNNNNNY_PointB", "A3AA_BothS_I_Lumi_YYYYYYYY_PointB"),
      ToVector("Float only A3AA (J)", "Float all (J)", "Float only A3AA (I)", "Float all (I)"),
      "Signal only, A3AA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{#gamma#gamma})", 0);

   PsFileC.AddTextPage("Comparison of all couplings, signal only");

   AddPlot(PsFileC, File,
      ToVector("A2ZZ_BothS_I_Count_YYYYYYYY_PointC",
         "A3ZZ_BothS_I_Count_YYYYYYYY_PointC",
         "A4ZZ_BothS_I_Count_YYYYYYYY_PointC",
         "A2ZA_BothS_I_Count_YYYYYYYY_PointC",
         "A3ZA_BothS_I_Count_YYYYYYYY_PointC",
         "A4ZA_BothS_I_Count_YYYYYYYY_PointC",
         "A2AA_BothS_I_Count_YYYYYYYY_PointC",
         "A3AA_BothS_I_Count_YYYYYYYY_PointC"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileC, File,
      ToVector("A2ZZ_BothS_J_Count_YYYYYYYY_PointC",
         "A3ZZ_BothS_J_Count_YYYYYYYY_PointC",
         "A4ZZ_BothS_J_Count_YYYYYYYY_PointC",
         "A2ZA_BothS_J_Count_YYYYYYYY_PointC",
         "A3ZA_BothS_J_Count_YYYYYYYY_PointC",
         "A4ZA_BothS_J_Count_YYYYYYYY_PointC",
         "A2AA_BothS_J_Count_YYYYYYYY_PointC",
         "A3AA_BothS_J_Count_YYYYYYYY_PointC"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float everything, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileC, File,
      ToVector("A2ZZ_BothS_I_Count_YNNNNNNN_PointC",
         "A3ZZ_BothS_I_Count_NYNNNNNN_PointC",
         "A4ZZ_BothS_I_Count_NNYNNNNN_PointC",
         "A2ZA_BothS_I_Count_NNNYNNNN_PointC",
         "A3ZA_BothS_I_Count_NNNNYNNN_PointC",
         "A4ZA_BothS_I_Count_NNNNNYNN_PointC",
         "A2AA_BothS_I_Count_NNNNNNYN_PointC",
         "A3AA_BothS_I_Count_NNNNNNNY_PointC"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, I Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);
   AddPlot(PsFileC, File,
      ToVector("A2ZZ_BothS_J_Count_YNNNNNNN_PointC",
         "A3ZZ_BothS_J_Count_NYNNNNNN_PointC",
         "A4ZZ_BothS_J_Count_NNYNNNNN_PointC",
         "A2ZA_BothS_J_Count_NNNYNNNN_PointC",
         "A3ZA_BothS_J_Count_NNNNYNNN_PointC",
         "A4ZA_BothS_J_Count_NNNNNYNN_PointC",
         "A2AA_BothS_J_Count_NNNNNNYN_PointC",
         "A3AA_BothS_J_Count_NNNNNNNY_PointC"),
      ToVector("A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA"),
      "Signal only, float each of them separately, J Cut",
      "N_{S}", "#sigma(A_{n}^{ij})", 0.008);

   AddPlot(PsFileC, File,
      ToVector("A2ZZ_BothS_J_Lumi_YNNNNNNN_PointC", "A2ZZ_BothS_J_Lumi_YYYYYYYY_PointC",
         "A2ZZ_BothS_I_Lumi_YNNNNNNN_PointC", "A2ZZ_BothS_I_Lumi_YYYYYYYY_PointC"),
      ToVector("Float only A2ZZ (J)", "Float all (J)", "Float only A2ZZ (I)", "Float all (I)"),
      "Signal only, A2ZZ",
      "N_{S} / #epsilon", "#sigma(A_{2}^{ZZ})", 0);
   AddPlot(PsFileC, File,
      ToVector("A3ZZ_BothS_J_Lumi_NYNNNNNN_PointC", "A3ZZ_BothS_J_Lumi_YYYYYYYY_PointC",
         "A3ZZ_BothS_I_Lumi_NYNNNNNN_PointC", "A3ZZ_BothS_I_Lumi_YYYYYYYY_PointC"),
      ToVector("Float only A3ZZ (J)", "Float all (J)", "Float only A3ZZ (I)", "Float all (I)"),
      "Signal only, A3ZZ",
      "N_{S} / #epsilon", "#sigma(A_{3}^{ZZ})", 0);
   AddPlot(PsFileC, File,
      ToVector("A4ZZ_BothS_J_Lumi_NNYNNNNN_PointC", "A4ZZ_BothS_J_Lumi_YYYYYYYY_PointC",
         "A4ZZ_BothS_I_Lumi_NNYNNNNN_PointC", "A4ZZ_BothS_I_Lumi_YYYYYYYY_PointC"),
      ToVector("Float only A4ZZ (J)", "Float all (J)", "Float only A4ZZ (I)", "Float all (I)"),
      "Signal only, A4ZZ",
      "N_{S} / #epsilon", "#sigma(A_{4}^{ZZ})", 0);
   AddPlot(PsFileC, File,
      ToVector("A2ZA_BothS_J_Lumi_NNNYNNNN_PointC", "A2ZA_BothS_J_Lumi_YYYYYYYY_PointC",
         "A2ZA_BothS_I_Lumi_NNNYNNNN_PointC", "A2ZA_BothS_I_Lumi_YYYYYYYY_PointC"),
      ToVector("Float only A2ZA (J)", "Float all (J)", "Float only A2ZA (I)", "Float all (I)"),
      "Signal only, A2ZA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{Z#gamma})", 0.014);
   AddPlot(PsFileC, File,
      ToVector("A3ZA_BothS_J_Lumi_NNNNYNNN_PointC", "A3ZA_BothS_J_Lumi_YYYYYYYY_PointC",
         "A3ZA_BothS_I_Lumi_NNNNYNNN_PointC", "A3ZA_BothS_I_Lumi_YYYYYYYY_PointC"),
      ToVector("Float only A3ZA (J)", "Float all (J)", "Float only A3ZA (I)", "Float all (I)"),
      "Signal only, A3ZA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{Z#gamma})", 0);
   AddPlot(PsFileC, File,
      ToVector("A4ZA_BothS_J_Lumi_NNNNNYNN_PointC", "A4ZA_BothS_J_Lumi_YYYYYYYY_PointC",
         "A4ZA_BothS_I_Lumi_NNNNNYNN_PointC", "A4ZA_BothS_I_Lumi_YYYYYYYY_PointC"),
      ToVector("Float only A4ZA (J)", "Float all (J)", "Float only A4ZA (I)", "Float all (I)"),
      "Signal only, A4ZA",
      "N_{S} / #epsilon", "#sigma(A_{4}^{Z#gamma})", 0);
   AddPlot(PsFileC, File,
      ToVector("A2AA_BothS_J_Lumi_NNNNNNYN_PointC", "A2AA_BothS_J_Lumi_YYYYYYYY_PointC",
         "A2AA_BothS_I_Lumi_NNNNNNYN_PointC", "A2AA_BothS_I_Lumi_YYYYYYYY_PointC"),
      ToVector("Float only A2AA (J)", "Float all (J)", "Float only A2AA (I)", "Float all (I)"),
      "Signal only, A2AA",
      "N_{S} / #epsilon", "#sigma(A_{2}^{#gamma#gamma})", 0.008);
   AddPlot(PsFileC, File,
      ToVector("A3AA_BothS_J_Lumi_NNNNNNNY_PointC", "A3AA_BothS_J_Lumi_YYYYYYYY_PointC",
         "A3AA_BothS_I_Lumi_NNNNNNNY_PointC", "A3AA_BothS_I_Lumi_YYYYYYYY_PointC"),
      ToVector("Float only A3AA (J)", "Float all (J)", "Float only A3AA (I)", "Float all (I)"),
      "Signal only, A3AA",
      "N_{S} / #epsilon", "#sigma(A_{3}^{#gamma#gamma})", 0);

   File.Close();

   PsFileA.AddTimeStampPage();
   PsFileA.Close();
   PsFileO.AddTimeStampPage();
   PsFileO.Close();
   PsFile0.AddTimeStampPage();
   PsFile0.Close();
   PsFileB.AddTimeStampPage();
   PsFileB.Close();
   PsFileC.AddTimeStampPage();
   PsFileC.Close();

   return 0;
}

void AddPlot(PsFileHelper &PsFile, TFile &File, vector<string> Histograms, vector<string> Labels, string Title, string XAxis, string YAxis, double Level)
{
   int GraphCount = 0;
   vector<TGraphErrors *> Graphs;

   for(int i = 0; i < (int)Histograms.size(); i++)
   {
      TGraphErrors *G = (TGraphErrors *)File.Get(Histograms[i].c_str());
      Graphs.push_back(G);
      if(G != NULL)
         GraphCount = GraphCount + 1;
   }

   cout << "Graph count = " << GraphCount << endl;

   if(GraphCount == 0)
   {
      vector<string> Explanations(8);

      Explanations[0] = "Requested plot with title " + Title + " is empty.";
      Explanations[1] = "";
      Explanations[2] = "";
      Explanations[3] = "";
      Explanations[4] = "";
      Explanations[5] = "";
      Explanations[6] = "";
      Explanations[7] = "";

      PsFile.AddTextPage(Explanations);

      return;
   }

   int Colors[8] = {kBlack, kRed, kBlue, kCyan - 3, kYellow - 3, kMagenta - 3, kGreen - 3, kRed - 3};

   TLegend Legend(0.6, 0.85, 0.85, 0.55);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);

   for(int i = 0; i < (int)Graphs.size(); i++)
   {
      if(Graphs[i] == NULL)
         continue;

      Graphs[i]->SetLineWidth(2);
      Graphs[i]->SetLineColor(Colors[i]);

      Legend.AddEntry(Graphs[i], Labels[i].c_str(), "l");
   }

   double XMax = -1, XMin = -1, YMax = -1, YMin = -1;

   for(int i = 0; i < (int)Graphs.size(); i++)
   {
      if(Graphs[i] == NULL)
         continue;

      for(int j = 0; j < Graphs[i]->GetN(); j++)
      {
         double x, y;
         Graphs[i]->GetPoint(j, x, y);

         if(XMin < 0 || XMin > x)   XMin = x;
         if(XMax < 0 || XMax < x)   XMax = x;
         if(YMin < 0 || YMin > y)   YMin = y;
         if(YMax < 0 || YMax < y)   YMax = y;
      }
   }

   double DeltaX = XMax / XMin;
   double DeltaY = YMax / YMin;

   TH2D HWorld("HWorld", Form("%s;%s;%s", Title.c_str(), XAxis.c_str(), YAxis.c_str()),
      100, XMin / pow(DeltaX, 0.1), XMax * pow(DeltaX, 0.1),
      100, YMin / pow(DeltaY, 0.1), YMax * pow(DeltaY, 0.6));
   HWorld.SetStats(0);

   TCanvas C;
   C.SetLogx();
   C.SetLogy();

   HWorld.Draw();
   Legend.Draw();

   for(int i = 0; i < (int)Graphs.size(); i++)
   {
      if(Graphs[i] == NULL)
         continue;

      Graphs[i]->Draw("pl");
   }

   TGraph GLine;
   if(Level != NONSENSE)
   {
      GLine.SetPoint(0, -99999, Level);
      GLine.SetPoint(1, +99999, Level);
      GLine.SetLineWidth(2);
      GLine.SetLineStyle(kDashed);
      GLine.Draw("l");
   }

   PsFile.AddCanvas(C);
}

vector<string> ToVector(string S1, string S2, string S3, string S4, string S5, string S6, string S7, string S8)
{
   vector<string> Result;

   Result.push_back(S1);

   if(S2 != "")   Result.push_back(S2);
   if(S3 != "")   Result.push_back(S3);
   if(S4 != "")   Result.push_back(S4);
   if(S5 != "")   Result.push_back(S5);
   if(S6 != "")   Result.push_back(S6);
   if(S7 != "")   Result.push_back(S7);
   if(S8 != "")   Result.push_back(S8);

   return Result;
}



