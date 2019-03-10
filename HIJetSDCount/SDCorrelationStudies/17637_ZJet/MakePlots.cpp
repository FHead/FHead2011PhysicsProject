#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"

#include "SetStyle.h"
#include "PlotHelper3.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
void AddPlot(PdfFileHelper &PdfFile, int N, double Min, double Max, string Title,
   TTree *T1, string Plot1, string Selection1,
   TTree *T2, string Plot2, string Selection2,
   TTree *T3, string Plot3, string Selection3,
   double LogMin = -1);
void AddPlot2D(PdfFileHelper &PdfFile,
   int NX, double MinX, double MaxX, int NY, double MinY, double MaxY, string Title,
   TTree *T1, string Plot1, string Selection1,
   TTree *T2, string Plot2, string Selection2,
   TTree *T3, string Plot3, string Selection3,
   double ZMax = -1);
void SetAlias(TTree *T);
void SetAliasJewel(TTree *T);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string RecoilFileName = CL.Get("Recoil");
   string NoRecoilFileName = CL.Get("NoRecoil");
   string VacuumFileName = CL.Get("Vacuum");
   string OutputFileName = CL.Get("Output");

   bool DoRAA = CL.GetBool("DoRAA", false);
   bool DoScan = CL.GetBool("DoScan", false);
   bool DoCorrelation = CL.GetBool("DoCorrelation", true);

   bool DoPTHatCut = CL.GetBool("DoPTHatCut", false);
   bool DoPTReweighting = CL.GetBool("DoPTReweighting", false);
   bool DoZ = CL.GetBool("DoZ", false);

   TFile RecoilFile(RecoilFileName.c_str());
   TFile NoRecoilFile(NoRecoilFileName.c_str());
   TFile VacuumFile(VacuumFileName.c_str());

   TTree *T1 = (TTree *)RecoilFile.Get("jetTree");
   TTree *T2 = (TTree *)NoRecoilFile.Get("jetTree");
   TTree *T3 = (TTree *)VacuumFile.Get("jetTree");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Jewel plots");

   vector<string> Explanations(10);
   Explanations[0] = "Jewel samples from the jet workshop directory:";
   Explanations[1] = "   jewel_NR_2.1_5.02_testfeb8 and";
   Explanations[2] = "   jewel_R_2.1_5.02_testfeb8";
   Explanations[3] = "";
   Explanations[4] = "   Recoil = blue";
   Explanations[5] = "   No-Recoil = green";
   Explanations[6] = "   Vacuum = red";
   Explanations[7] = "";
   Explanations[8] = "";
   Explanations[9] = "";
   PdfFile.AddTextPage(Explanations);

   T1->SetAlias("PT", "sigJetJewelPt");
   T2->SetAlias("PT", "sigJetJewelPt");
   T3->SetAlias("PT", "sigJetPt");

   string WeightString = "eventWeight[0]";

   // Select PTHat > 80
   if(DoPTHatCut == true)
      WeightString = WeightString + " * (eventWeight[0] < exp(-7)";

   if(DoPTReweighting == true)
      WeightString = WeightString + " * (exp((PT - 100) * 0.003))";
   
   T1->SetAlias("W", ("(" + WeightString + ")").c_str());
   T2->SetAlias("W", ("(" + WeightString + ")").c_str());
   T3->SetAlias("W", ("(" + WeightString + ")").c_str());
   
   PdfFile.AddTextPage("Basic plots");
   AddPlot(PdfFile, 100, 0, 1000, "SigJet PT;PT",
      T1, "PT", "W",
      T2, "PT", "W",
      T3, "PT", "W",
      1e-15);
   AddPlot(PdfFile, 100, 0, 1000, "max SigJet PT;PT",
      T1, "Max$(PT)", "W",
      T2, "Max$(PT)", "W",
      T3, "Max$(PT)", "W",
      1e-15);
   AddPlot(PdfFile, 100, 200, 1000, "max SigJet PT;PT",
      T1, "Max$(PT)", "W",
      T2, "Max$(PT)", "W",
      T3, "Max$(PT)", "W",
      1e-7);
  
   if(DoRAA)
   {
      AddPlot(PdfFile, 20, 100, 600, "(0.5, 1.5)(No jewel) DR > 0.3;PT (No jewel)",
         T1, "sigJetPt", "W * (sig1JetSDdr12 > 0.3)",
         T2, "sigJetPt", "W * (sig1JetSDdr12 > 0.3)",
         T3, "sigJetPt", "W * (sig1JetSDdr12 > 0.3)");
      AddPlot(PdfFile, 20, 100, 600, "(0.5, 1.5) DR > 0.3;PT (No jewel)",
         T1, "sigJetPt", "W * (sig1JetSDJeweldr12 > 0.3)",
         T2, "sigJetPt", "W * (sig1JetSDJeweldr12 > 0.3)",
         T3, "sigJetPt", "W * (sig1JetSDdr12 > 0.3)");
      AddPlot(PdfFile, 20, 100, 600, "(0.5, 1.5) DR > 0.3;PT",
         T1, "sigJetJewelPt", "W * (sig1JetSDJeweldr12 > 0.3)",
         T2, "sigJetJewelPt", "W * (sig1JetSDJeweldr12 > 0.3)",
         T3, "sigJetPt", "W * (sig1JetSDdr12 > 0.3)");
      AddPlot(PdfFile, 20, 100, 600, "(0.5, 1.5) DR = 0.1-0.2;PT",
         T1, "sigJetJewelPt", "W * (sig1JetSDJeweldr12 > 0.1 && sig1JetSDJeweldr12 < 0.2)",
         T2, "sigJetJewelPt", "W * (sig1JetSDJeweldr12 > 0.1 && sig1JetSDJeweldr12 < 0.2)",
         T3, "sigJetPt", "W * (sig1JetSDdr12 > 0.1 && sig1JetSDdr12 < 0.2)");
   }

   SetAliasJewel(T1);
   SetAliasJewel(T2);
   SetAlias(T3);

   if(DoScan)
   {
      PdfFile.AddTextPage("SD (0.1, 0.0) plots");
      AddPlot(PdfFile, 2, 0, 2, "(0.1, 0.0) Completely killed percentage, PT > 200;(left) good (right) killed;%",
         T1, "DR0 <= 0", "W * (PT > 200)",
         T2, "DR0 <= 0", "W * (PT > 200)",
         T3, "DR0 <= 0", "W * (PT > 200)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.1, 0.0) ZG, PT > 200, DR > 0.1;zg",
         T1, "ZG0", "W * (PT > 200 && DR0 > 0.1)",
         T2, "ZG0", "W * (PT > 200 && DR0 > 0.1)",
         T3, "ZG0", "W * (PT > 200 && DR0 > 0.1)");
      AddPlot(PdfFile, 40, 0, 0.5, "(0.1, 0.0) DR, PT > 200, DR > 0.0;DR",
         T1, "DR0", "W * (PT > 200 && DR0 > 0.0)",
         T2, "DR0", "W * (PT > 200 && DR0 > 0.0)",
         T3, "DR0", "W * (PT > 200 && DR0 > 0.0)");
      AddPlot(PdfFile, 40, 0, 0.5, "(0.1, 0.0) DR, PT > 200, DR > 0.1;DR",
         T1, "DR0", "W * (PT > 200 && DR0 > 0.1)",
         T2, "DR0", "W * (PT > 200 && DR0 > 0.1)",
         T3, "DR0", "W * (PT > 200 && DR0 > 0.1)");
      AddPlot(PdfFile, 40, 0, 0.3, "(0.1, 0.0) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M0/PT", "W * (PT > 200 && DR0 > 0.1)",
         T2, "M0/PT", "W * (PT > 200 && DR0 > 0.1)",
         T3, "M0/PT", "W * (PT > 200 && DR0 > 0.1)");
      AddPlot(PdfFile, 40, 0, 0.3, "(0.1, 0.0) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M0/GuuPT0", "W * (PT > 200 && DR0 > 0.1)",
         T2, "M0/GuuPT0", "W * (PT > 200 && DR0 > 0.1)",
         T3, "M0/GuuPT0", "W * (PT > 200 && DR0 > 0.1)");

      PdfFile.AddTextPage("SD (0.5, 1.5) plots");
      AddPlot(PdfFile, 2, 0, 2, "(0.5, 1.5) Completely killed percentage, PT > 200;(left) good (right) killed;%",
         T1, "DR1 <= 0", "W * (PT > 200)",
         T2, "DR1 <= 0", "W * (PT > 200)",
         T3, "DR1 <= 0", "W * (PT > 200)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.5, 1.5) ZG, PT > 200, DR > 0.1;zg",
         T1, "ZG1", "W * (PT > 200 && DR1 > 0.1)",
         T2, "ZG1", "W * (PT > 200 && DR1 > 0.1)",
         T3, "ZG1", "W * (PT > 200 && DR1 > 0.1)");
      AddPlot(PdfFile, 40, 0, 0.5, "(0.5, 1.5) DR, PT > 200, DR > 0.0;DR",
         T1, "DR1", "W * (PT > 200 && DR1 > 0.0)",
         T2, "DR1", "W * (PT > 200 && DR1 > 0.0)",
         T3, "DR1", "W * (PT > 200 && DR1 > 0.0)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.5, 1.5) DR, PT > 200, DR > 0.1;DR",
         T1, "DR1", "W * (PT > 200 && DR1 > 0.1)",
         T2, "DR1", "W * (PT > 200 && DR1 > 0.1)",
         T3, "DR1", "W * (PT > 200 && DR1 > 0.1)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.3, "(0.5, 1.5) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M1/PT", "W * (PT > 200 && DR1 > 0.1)",
         T2, "M1/PT", "W * (PT > 200 && DR1 > 0.1)",
         T3, "M1/PT", "W * (PT > 200 && DR1 > 0.1)");
      AddPlot(PdfFile, 40, 0, 0.3, "(0.5, 1.5) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M1/GuuPT1", "W * (PT > 200 && DR1 > 0.1)",
         T2, "M1/GuuPT1", "W * (PT > 200 && DR1 > 0.1)",
         T3, "M1/GuuPT1", "W * (PT > 200 && DR1 > 0.1)");
      
      PdfFile.AddTextPage("SD (0.15, -2.0) plots");
      AddPlot(PdfFile, 2, 0, 2, "(0.15, -2.0) Completely killed percentage, PT > 200;(left) good (right) killed;%",
         T1, "DR2 <= 0", "W * (PT > 200)",
         T2, "DR2 <= 0", "W * (PT > 200)",
         T3, "DR2 <= 0", "W * (PT > 200)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.15, -2.0) ZG, PT > 200, DR > 0.1;zg",
         T1, "ZG2", "W * (PT > 200 && DR2 > 0.1)",
         T2, "ZG2", "W * (PT > 200 && DR2 > 0.1)",
         T3, "ZG2", "W * (PT > 200 && DR2 > 0.1)",
         1e-2);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.15, -2.0) DR, PT > 200, DR > 0.0;DR",
         T1, "DR2", "W * (PT > 200 && DR2 > 0.0)",
         T2, "DR2", "W * (PT > 200 && DR2 > 0.0)",
         T3, "DR2", "W * (PT > 200 && DR2 > 0.0)");
      AddPlot(PdfFile, 40, 0, 0.5, "(0.15, -2.0) DR, PT > 200, DR > 0.1;DR",
         T1, "DR2", "W * (PT > 200 && DR2 > 0.1)",
         T2, "DR2", "W * (PT > 200 && DR2 > 0.1)",
         T3, "DR2", "W * (PT > 200 && DR2 > 0.1)");
      AddPlot(PdfFile, 40, 0, 0.3, "(0.15, -2.0) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M2/PT", "W * (PT > 200 && DR2 > 0.1)",
         T2, "M2/PT", "W * (PT > 200 && DR2 > 0.1)",
         T3, "M2/PT", "W * (PT > 200 && DR2 > 0.1)",
         1e-2);
      AddPlot(PdfFile, 40, 0, 0.3, "(0.15, -2.0) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M2/GuuPT2", "W * (PT > 200 && DR2 > 0.1)",
         T2, "M2/GuuPT2", "W * (PT > 200 && DR2 > 0.1)",
         T3, "M2/GuuPT2", "W * (PT > 200 && DR2 > 0.1)",
         1e-2);
      
      PdfFile.AddTextPage("SD (100, 10) plots");
      AddPlot(PdfFile, 2, 0, 2, "(100, 10) Completely killed percentage, PT > 200;(left) good (right) killed;%",
         T1, "DR3 <= 0", "W * (PT > 200)",
         T2, "DR3 <= 0", "W * (PT > 200)",
         T3, "DR3 <= 0", "W * (PT > 200)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(100, 10) ZG, PT > 200, DR > 0.1;zg",
         T1, "ZG3", "W * (PT > 200 && DR3 > 0.1)",
         T2, "ZG3", "W * (PT > 200 && DR3 > 0.1)",
         T3, "ZG3", "W * (PT > 200 && DR3 > 0.1)");
      AddPlot(PdfFile, 40, 0, 0.5, "(100, 10) DR, PT > 200, DR > 0.0;DR",
         T1, "DR3", "W * (PT > 200 && DR3 > 0.0)",
         T2, "DR3", "W * (PT > 200 && DR3 > 0.0)",
         T3, "DR3", "W * (PT > 200 && DR3 > 0.0)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(100, 10) DR, PT > 200, DR > 0.1;DR",
         T1, "DR3", "W * (PT > 200 && DR3 > 0.1)",
         T2, "DR3", "W * (PT > 200 && DR3 > 0.1)",
         T3, "DR3", "W * (PT > 200 && DR3 > 0.1)",
         1e-2);
      AddPlot(PdfFile, 40, 0, 0.3, "(100, 10) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M3/PT", "W * (PT > 200 && DR3 > 0.1)",
         T2, "M3/PT", "W * (PT > 200 && DR3 > 0.1)",
         T3, "M3/PT", "W * (PT > 200 && DR3 > 0.1)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.3, "(100, 10) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M3/GuuPT3", "W * (PT > 200 && DR3 > 0.1)",
         T2, "M3/GuuPT3", "W * (PT > 200 && DR3 > 0.1)",
         T3, "M3/GuuPT3", "W * (PT > 200 && DR3 > 0.1)",
         1e-3);
   }
  
   if(DoScan == true || DoCorrelation == true)
   {
      PdfFile.AddTextPage("SD (0.25, 0.0) plots");
      AddPlot(PdfFile, 2, 0, 2, "(0.25, 0.0) Completely killed percentage, PT > 200;(left) good (right) killed;%",
         T1, "DR4 <= 0 || ZG4 < 0", "W * (PT > 200)",
         T2, "DR4 <= 0 || ZG4 < 0", "W * (PT > 200)",
         T3, "DR4 <= 0 || ZG4 < 0", "W * (PT > 200)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.25, 0.0) ZG, PT > 200, DR > 0.1;zg",
         T1, "ZG4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T2, "ZG4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T3, "ZG4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)");
      AddPlot(PdfFile, 40, 0, 0.5, "(0.25, 0.0) DR, PT > 200, DR > 0.0;DR",
         T1, "DR4", "W * (PT > 200 && DR4 > 0.0 && ZG4 > 0)",
         T2, "DR4", "W * (PT > 200 && DR4 > 0.0 && ZG4 > 0)",
         T3, "DR4", "W * (PT > 200 && DR4 > 0.0 && ZG4 > 0)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.25, 0.0) DR, PT > 200, DR > 0.1;DR",
         T1, "DR4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T2, "DR4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T3, "DR4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         1e-2);
      AddPlot(PdfFile, 40, 0, 0.3, "(0.25, 0.0) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M4/PT", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T2, "M4/PT", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T3, "M4/PT", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.3, "(0.25, 0.0) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M4/GuuPT4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T2, "M4/GuuPT4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T3, "M4/GuuPT4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         1e-3);
      AddPlot2D(PdfFile, 20, 0.1, 0.4, 20, 0.25, 0.5, "(0.25, 0.0) PT > 200, DR > 0.1;DR;ZG",
         T1, "ZG4:DR4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T2, "ZG4:DR4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         T3, "ZG4:DR4", "W * (PT > 200 && DR4 > 0.1 && ZG4 > 0)",
         120);
   }

   if(DoScan == true)
   {
      PdfFile.AddTextPage("SD (0.15, 0.00) plots");
      AddPlot(PdfFile, 2, 0, 2, "(0.15, 0.00) Completely killed percentage, PT > 200;(left) good (right) killed;%",
         T1, "DR5 <= 0 || ZG5 < 0", "W * (PT > 200)",
         T2, "DR5 <= 0 || ZG5 < 0", "W * (PT > 200)",
         T3, "DR5 <= 0 || ZG5 < 0", "W * (PT > 200)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.15, 0.00) ZG, PT > 200, DR > 0.1;zg",
         T1, "ZG5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T2, "ZG5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T3, "ZG5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)");
      AddPlot(PdfFile, 40, 0, 0.5, "(0.15, 0.00) DR, PT > 200, DR > 0.0;DR",
         T1, "DR5", "W * (PT > 200 && DR5 > 0.0 && ZG5 > 0)",
         T2, "DR5", "W * (PT > 200 && DR5 > 0.0 && ZG5 > 0)",
         T3, "DR5", "W * (PT > 200 && DR5 > 0.0 && ZG5 > 0)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.15, 0.00) DR, PT > 200, DR > 0.1;DR",
         T1, "DR5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T2, "DR5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T3, "DR5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         1e-2);
      AddPlot(PdfFile, 40, 0, 0.3, "(0.15, 0.00) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M5/PT", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T2, "M5/PT", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T3, "M5/PT", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.3, "(0.15, 0.00) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M5/GuuPT5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T2, "M5/GuuPT5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T3, "M5/GuuPT5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         1e-3);
      AddPlot2D(PdfFile, 20, 0.1, 0.4, 20, 0.25, 0.5, "(0.15, 0.00) PT > 200, DR > 0.1;DR;ZG",
         T1, "ZG5:DR5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T2, "ZG5:DR5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         T3, "ZG5:DR5", "W * (PT > 200 && DR5 > 0.1 && ZG5 > 0)",
         120);
   
      PdfFile.AddTextPage("SD (0.20, 0.00) plots");
      AddPlot(PdfFile, 2, 0, 2, "(0.20, 0.00) Completely killed percentage, PT > 200;(left) good (right) killed;%",
         T1, "DR6 <= 0 || ZG6 < 0", "W * (PT > 200)",
         T2, "DR6 <= 0 || ZG6 < 0", "W * (PT > 200)",
         T3, "DR6 <= 0 || ZG6 < 0", "W * (PT > 200)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.20, 0.00) ZG, PT > 200, DR > 0.1;zg",
         T1, "ZG6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T2, "ZG6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T3, "ZG6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)");
      AddPlot(PdfFile, 40, 0, 0.5, "(0.20, 0.00) DR, PT > 200, DR > 0.0;DR",
         T1, "DR6", "W * (PT > 200 && DR6 > 0.0 && ZG6 > 0)",
         T2, "DR6", "W * (PT > 200 && DR6 > 0.0 && ZG6 > 0)",
         T3, "DR6", "W * (PT > 200 && DR6 > 0.0 && ZG6 > 0)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.5, "(0.20, 0.00) DR, PT > 200, DR > 0.1;DR",
         T1, "DR6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T2, "DR6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T3, "DR6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         1e-2);
      AddPlot(PdfFile, 40, 0, 0.3, "(0.20, 0.00) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M6/PT", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T2, "M6/PT", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T3, "M6/PT", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         1e-3);
      AddPlot(PdfFile, 40, 0, 0.3, "(0.20, 0.00) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
         T1, "M6/GuuPT6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T2, "M6/GuuPT6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T3, "M6/GuuPT6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         1e-3);
      AddPlot2D(PdfFile, 20, 0.1, 0.4, 20, 0.25, 0.5, "(0.20, 0.00) PT > 200, DR > 0.1;DR;ZG",
         T1, "ZG6:DR6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T2, "ZG6:DR6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         T3, "ZG6:DR6", "W * (PT > 200 && DR6 > 0.1 && ZG6 > 0)",
         120);
   }

   if(DoCorrelation == true)
   {
      PdfFile.AddTextPage("Correlation Plots");
      
      AddPlot2D(PdfFile, 25, 0.10, 0.45, 25, 0.0, 0.5, "PT > 200;DR (0.25, 0.00);DR (0.10, 0.00)",
         T1, "DR0:DR4", "W * (PT > 200 && ZG4 > 0 && ZG0 > 0)",
         T2, "DR0:DR4", "W * (PT > 200 && ZG4 > 0 && ZG0 > 0)",
         T3, "DR0:DR4", "W * (PT > 200 && ZG4 > 0 && ZG0 > 0)",
         150);
      AddPlot2D(PdfFile, 25, 0.10, 0.45, 25, 0.7, 1.0, "PT > 200;DR (0.25, 0.00);PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT:DR4", "W * (PT > 200 && ZG4 > 0)",
         T2, "GuuPT0/PT:DR4", "W * (PT > 200 && ZG4 > 0)",
         T3, "GuuPT0/PT:DR4", "W * (PT > 200 && ZG4 > 0)",
         150);
      AddPlot(PdfFile, 50, 0.50, 1.0, "DR(0.25,0.00) = 0.1-0.2, PT > 200;PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.50, 1.0, "DR(0.25,0.00) = 0.2-0.3, PT > 200;PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.50, 1.0, "DR(0.25,0.00) = 0.3-0.4, PT > 200;PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      AddPlot2D(PdfFile, 25, 0.10, 0.45, 25, 0.0, 0.5, "PT > 200;DR (0.25, 0.00);ZG (0.10, 0.00)",
         T1, "ZG0:DR4", "W * (PT > 200 && ZG4 > 0)",
         T2, "ZG0:DR4", "W * (PT > 200 && ZG4 > 0)",
         T3, "ZG0:DR4", "W * (PT > 200 && ZG4 > 0)");
      AddPlot2D(PdfFile, 25, 0.10, 0.45, 25, 0.0, 0.5, "PT > 200;DR (0.25, 0.00);DR (0.50, 1.50)",
         T1, "DR1:DR4", "W * (PT > 200 && ZG4 > 0 && ZG1 > 0)",
         T2, "DR1:DR4", "W * (PT > 200 && ZG4 > 0 && ZG1 > 0)",
         T3, "DR1:DR4", "W * (PT > 200 && ZG4 > 0 && ZG1 > 0)",
         80);
      AddPlot2D(PdfFile, 25, 0.10, 0.45, 25, 0.4, 1.0, "PT > 200;DR (0.25, 0.00);PT/PT (0.50, 1.50)",
         T1, "GuuPT1/PT:DR4", "W * (PT > 200 && ZG4 > 0)",
         T2, "GuuPT1/PT:DR4", "W * (PT > 200 && ZG4 > 0)",
         T3, "GuuPT1/PT:DR4", "W * (PT > 200 && ZG4 > 0)");

      AddPlot2D(PdfFile, 25, 0.10, 0.50, 25, 0.7, 1.0, "PT > 200, DR(0.25,0.00) = 0.1-0.2;ZG (0.10, 0.00);PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT:ZG0", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T2, "GuuPT0/PT:ZG0", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T3, "GuuPT0/PT:ZG0", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)");
      AddPlot2D(PdfFile, 25, 0.10, 0.50, 25, 0.7, 1.0, "PT > 200, DR(0.25,0.00) = 0.1-0.2;ZG (0.25, 0.00);PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT:ZG4", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T2, "GuuPT0/PT:ZG4", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T3, "GuuPT0/PT:ZG4", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)");
      AddPlot2D(PdfFile, 25, 0.70, 1.00, 25, 0.10, 0.50, "PT > 200, DR(0.25,0.00) = 0.1-0.2;PT/PT (0.10, 0.00);ZG (0.25, 0.00)",
         T1, "ZG4:GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T2, "ZG4:GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T3, "ZG4:GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)");
      AddPlot2D(PdfFile, 25, 0.70, 1.00, 25, 0.10, 0.50, "PT > 200, DR(0.25,0.00) = 0.1-0.2;PT/PT (0.10, 0.00);DR (0.50, 1.50)",
         T1, "DR1:GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T2, "DR1:GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T3, "DR1:GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)");
      AddPlot2D(PdfFile, 25, 0.70, 1.00, 25, 0.10, 0.50, "PT > 200, DR(0.25,0.00) = 0.1-0.2;PT/PT (0.10, 0.00);ZG (0.50, 1.50)",
         T1, "ZG1:GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T2, "ZG1:GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)",
         T3, "ZG1:GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2)");
      
      AddPlot(PdfFile, 50, 0.50, 1.0, "(0.25,0.00) Fail, PT > 200;PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT", "W * (PT > 200 && ZG4 <= 0)",
         T2, "GuuPT0/PT", "W * (PT > 200 && ZG4 <= 0)",
         T3, "GuuPT0/PT", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.50, 1.0, "DR(0.25,0.00) < 0.1, PT > 200;PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "GuuPT0/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "GuuPT0/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.50, 1.0, "DR(0.25,0.00) = 0.1-0.2, PT > 200;PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.50, 1.0, "DR(0.25,0.00) = 0.2-0.3, PT > 200;PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.50, 1.0, "DR(0.25,0.00) > 0.3, PT > 200;PT/PT (0.10, 0.00)",
         T1, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "GuuPT0/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "(0.25,0.00) Fail, PT > 200;DR (0.10, 0.00)",
         T1, "DR0", "W * (PT > 200 && ZG4 <= 0)",
         T2, "DR0", "W * (PT > 200 && ZG4 <= 0)",
         T3, "DR0", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) < 0.1, PT > 200;DR (0.10, 0.00)",
         T1, "DR0", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "DR0", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "DR0", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) = 0.1-0.2, PT > 200;DR (0.10, 0.00)",
         T1, "DR0", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "DR0", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "DR0", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) = 0.2-0.3, PT > 200;DR (0.10, 0.00)",
         T1, "DR0", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "DR0", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "DR0", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) > 0.3, PT > 200;DR (0.10, 0.00)",
         T1, "DR0", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "DR0", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "DR0", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "(0.25,0.00) Fail, PT > 200;ZG (0.10, 0.00)",
         T1, "ZG0", "W * (PT > 200 && ZG4 <= 0)",
         T2, "ZG0", "W * (PT > 200 && ZG4 <= 0)",
         T3, "ZG0", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) < 0.1, PT > 200;ZG (0.10, 0.00)",
         T1, "ZG0", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "ZG0", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "ZG0", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) = 0.1-0.2, PT > 200;ZG (0.10, 0.00)",
         T1, "ZG0", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "ZG0", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "ZG0", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) = 0.2-0.3, PT > 200;ZG (0.10, 0.00)",
         T1, "ZG0", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "ZG0", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "ZG0", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) > 0.3, PT > 200;ZG (0.10, 0.00)",
         T1, "ZG0", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "ZG0", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "ZG0", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      
      AddPlot(PdfFile, 50, 0.00, 1.00, "(0.25,0.00) Fail, PT > 200;PT/PT (0.50, 1.50)",
         T1, "GuuPT1/PT", "W * (PT > 200 && ZG4 <= 0)",
         T2, "GuuPT1/PT", "W * (PT > 200 && ZG4 <= 0)",
         T3, "GuuPT1/PT", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) < 0.1, PT > 200;PT/PT (0.50, 1.50)",
         T1, "GuuPT1/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "GuuPT1/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "GuuPT1/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) = 0.1-0.2, PT > 200;PT/PT (0.50, 1.50)",
         T1, "GuuPT1/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "GuuPT1/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "GuuPT1/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) = 0.2-0.3, PT > 200;PT/PT (0.50, 1.50)",
         T1, "GuuPT1/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "GuuPT1/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "GuuPT1/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) > 0.3, PT > 200;PT/PT (0.50, 1.50)",
         T1, "GuuPT1/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "GuuPT1/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "GuuPT1/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "(0.25,0.00) Fail, PT > 200;DR (0.50, 1.50)",
         T1, "DR1", "W * (PT > 200 && ZG4 <= 0)",
         T2, "DR1", "W * (PT > 200 && ZG4 <= 0)",
         T3, "DR1", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) < 0.1, PT > 200;DR (0.50, 1.50)",
         T1, "DR1", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "DR1", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "DR1", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) = 0.1-0.2, PT > 200;DR (0.50, 1.50)",
         T1, "DR1", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "DR1", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "DR1", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) = 0.2-0.3, PT > 200;DR (0.50, 1.50)",
         T1, "DR1", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "DR1", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "DR1", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) > 0.3, PT > 200;DR (0.50, 1.50)",
         T1, "DR1", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "DR1", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "DR1", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "(0.25,0.00) Fail, PT > 200;ZG (0.50, 1.50)",
         T1, "ZG1", "W * (PT > 200 && ZG4 <= 0)",
         T2, "ZG1", "W * (PT > 200 && ZG4 <= 0)",
         T3, "ZG1", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) < 0.1, PT > 200;ZG (0.50, 1.50)",
         T1, "ZG1", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "ZG1", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "ZG1", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) = 0.1-0.2, PT > 200;ZG (0.50, 1.50)",
         T1, "ZG1", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "ZG1", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "ZG1", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) = 0.2-0.3, PT > 200;ZG (0.50, 1.50)",
         T1, "ZG1", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "ZG1", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "ZG1", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) > 0.3, PT > 200;ZG (0.50, 1.50)",
         T1, "ZG1", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "ZG1", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "ZG1", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      
      AddPlot(PdfFile, 50, 0.00, 1.00, "(0.25,0.00) Fail, PT > 200;PT/PT (0.15, -2.00)",
         T1, "GuuPT2/PT", "W * (PT > 200 && ZG4 <= 0)",
         T2, "GuuPT2/PT", "W * (PT > 200 && ZG4 <= 0)",
         T3, "GuuPT2/PT", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) < 0.1, PT > 200;PT/PT (0.15, -2.00)",
         T1, "GuuPT2/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "GuuPT2/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "GuuPT2/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) = 0.1-0.2, PT > 200;PT/PT (0.15, -2.00)",
         T1, "GuuPT2/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "GuuPT2/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "GuuPT2/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) = 0.2-0.3, PT > 200;PT/PT (0.15, -2.00)",
         T1, "GuuPT2/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "GuuPT2/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "GuuPT2/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) > 0.3, PT > 200;PT/PT (0.15, -2.00)",
         T1, "GuuPT2/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "GuuPT2/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "GuuPT2/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "(0.25,0.00) Fail, PT > 200;DR (0.15, -2.00)",
         T1, "DR2", "W * (PT > 200 && ZG4 <= 0)",
         T2, "DR2", "W * (PT > 200 && ZG4 <= 0)",
         T3, "DR2", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) < 0.1, PT > 200;DR (0.15, -2.00)",
         T1, "DR2", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "DR2", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "DR2", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) = 0.1-0.2, PT > 200;DR (0.15, -2.00)",
         T1, "DR2", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "DR2", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "DR2", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) = 0.2-0.3, PT > 200;DR (0.15, -2.00)",
         T1, "DR2", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "DR2", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "DR2", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) > 0.3, PT > 200;DR (0.15, -2.00)",
         T1, "DR2", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "DR2", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "DR2", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "(0.25,0.00) Fail, PT > 200;ZG (0.15, -2.00)",
         T1, "ZG2", "W * (PT > 200 && ZG4 <= 0)",
         T2, "ZG2", "W * (PT > 200 && ZG4 <= 0)",
         T3, "ZG2", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) < 0.1, PT > 200;ZG (0.15, -2.00)",
         T1, "ZG2", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "ZG2", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "ZG2", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) = 0.1-0.2, PT > 200;ZG (0.15, -2.00)",
         T1, "ZG2", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "ZG2", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "ZG2", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) = 0.2-0.3, PT > 200;ZG (0.15, -2.00)",
         T1, "ZG2", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "ZG2", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "ZG2", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) > 0.3, PT > 200;ZG (0.15, -2.00)",
         T1, "ZG2", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "ZG2", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "ZG2", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      
      AddPlot(PdfFile, 50, 0.00, 1.00, "(0.25,0.00) Fail, PT > 200;PT/PT (100, 10)",
         T1, "GuuPT3/PT", "W * (PT > 200 && ZG4 <= 0)",
         T2, "GuuPT3/PT", "W * (PT > 200 && ZG4 <= 0)",
         T3, "GuuPT3/PT", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) < 0.1, PT > 200;PT/PT (100, 10)",
         T1, "GuuPT3/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "GuuPT3/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "GuuPT3/PT", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) = 0.1-0.2, PT > 200;PT/PT (100, 10)",
         T1, "GuuPT3/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "GuuPT3/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "GuuPT3/PT", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) = 0.2-0.3, PT > 200;PT/PT (100, 10)",
         T1, "GuuPT3/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "GuuPT3/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "GuuPT3/PT", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 1.00, "DR(0.25,0.00) > 0.3, PT > 200;PT/PT (100, 10)",
         T1, "GuuPT3/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "GuuPT3/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "GuuPT3/PT", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "(0.25,0.00) Fail, PT > 200;DR (100, 10)",
         T1, "DR3", "W * (PT > 200 && ZG4 <= 0)",
         T2, "DR3", "W * (PT > 200 && ZG4 <= 0)",
         T3, "DR3", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) < 0.1, PT > 200;DR (100, 10)",
         T1, "DR3", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "DR3", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "DR3", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) = 0.1-0.2, PT > 200;DR (100, 10)",
         T1, "DR3", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "DR3", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "DR3", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) = 0.2-0.3, PT > 200;DR (100, 10)",
         T1, "DR3", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "DR3", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "DR3", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.45, "DR(0.25,0.00) > 0.3, PT > 200;DR (100, 10)",
         T1, "DR3", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "DR3", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "DR3", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "(0.25,0.00) Fail, PT > 200;ZG (100, 10)",
         T1, "ZG3", "W * (PT > 200 && ZG4 <= 0)",
         T2, "ZG3", "W * (PT > 200 && ZG4 <= 0)",
         T3, "ZG3", "W * (PT > 200 && ZG4 <= 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) < 0.1, PT > 200;ZG (100, 10)",
         T1, "ZG3", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "ZG3", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "ZG3", "W * (PT > 200 && DR4 < 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) = 0.1-0.2, PT > 200;ZG (100, 10)",
         T1, "ZG3", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T2, "ZG3", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)",
         T3, "ZG3", "W * (PT > 200 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) = 0.2-0.3, PT > 200;ZG (100, 10)",
         T1, "ZG3", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T2, "ZG3", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)",
         T3, "ZG3", "W * (PT > 200 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0)");
      AddPlot(PdfFile, 50, 0.00, 0.50, "DR(0.25,0.00) > 0.3, PT > 200;ZG (100, 10)",
         T1, "ZG3", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T2, "ZG3", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)",
         T3, "ZG3", "W * (PT > 200 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0)");
   }

   if(DoZ == true)
   {
      AddPlot(PdfFile, 25, 0.00, 1.50, "DR(0.25,0.00) < 0.1, ZPT > 80, JPT > 40;x_{JZ}",
         T1, "PT/ZPt", "W * (PT > 40 && DR4 > 0.0 && DR4 < 0.1 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T2, "PT/ZPt", "W * (PT > 40 && DR4 > 0.0 && DR4 < 0.1 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T3, "PT/ZPt", "W * (PT > 40 && DR4 > 0.0 && DR4 < 0.1 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)");
      AddPlot(PdfFile, 25, 0.00, 1.50, "DR(0.25,0.00) = 0.1-0.2 , ZPT > 80, JPT > 40;x_{JZ}",
         T1, "PT/ZPt", "W * (PT > 40 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T2, "PT/ZPt", "W * (PT > 40 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T3, "PT/ZPt", "W * (PT > 40 && DR4 > 0.1 && DR4 < 0.2 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)");
      AddPlot(PdfFile, 25, 0.00, 1.50, "DR(0.25,0.00) = 0.2-0.3, ZPT > 80, JPT > 40;x_{JZ}",
         T1, "PT/ZPt", "W * (PT > 40 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T2, "PT/ZPt", "W * (PT > 40 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T3, "PT/ZPt", "W * (PT > 40 && DR4 > 0.2 && DR4 < 0.3 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)");
      AddPlot(PdfFile, 25, 0.00, 1.50, "DR(0.25,0.00) > 0.3, ZPT > 80, JPT > 40;x_{JZ}",
         T1, "PT/ZPt", "W * (PT > 40 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T2, "PT/ZPt", "W * (PT > 40 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T3, "PT/ZPt", "W * (PT > 40 && DR4 > 0.3 && DR4 < 0.4 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)");
      AddPlot2D(PdfFile, 25, 0.00, 0.45, 50, 0.00, 1.50, "DR(0.25,0.00) > 0.3, ZPT > 80, JPT > 40;#DeltaR;x_{JZ}",
         T1, "PT/ZPt:DR4", "W * (PT > 40 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T2, "PT/ZPt:DR4", "W * (PT > 40 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)",
         T3, "PT/ZPt:DR4", "W * (PT > 40 && ZG4 > 0 && DPhi > 2.8 && ZPt > 80)");
      
      AddPlot(PdfFile, 50, 0.00, 1.50, "DR(0.10,0.00) < 0.1, ZPT > 80, JPT > 40;x_{JZ}",
         T1, "PT/ZPt", "W * (PT > 40 && DR0 > 0.0 && DR0 < 0.1 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)",
         T2, "PT/ZPt", "W * (PT > 40 && DR0 > 0.0 && DR0 < 0.1 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)",
         T3, "PT/ZPt", "W * (PT > 40 && DR0 > 0.0 && DR0 < 0.1 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)");
      AddPlot(PdfFile, 50, 0.00, 1.50, "DR(0.10,0.00) = 0.1-0.2 , ZPT > 80, JPT > 40;x_{JZ}",
         T1, "PT/ZPt", "W * (PT > 40 && DR0 > 0.1 && DR0 < 0.2 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)",
         T2, "PT/ZPt", "W * (PT > 40 && DR0 > 0.1 && DR0 < 0.2 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)",
         T3, "PT/ZPt", "W * (PT > 40 && DR0 > 0.1 && DR0 < 0.2 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)");
      AddPlot(PdfFile, 50, 0.00, 1.50, "DR(0.10,0.00) = 0.2-0.3, ZPT > 80, JPT > 40;x_{JZ}",
         T1, "PT/ZPt", "W * (PT > 40 && DR0 > 0.2 && DR0 < 0.3 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)",
         T2, "PT/ZPt", "W * (PT > 40 && DR0 > 0.2 && DR0 < 0.3 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)",
         T3, "PT/ZPt", "W * (PT > 40 && DR0 > 0.2 && DR0 < 0.3 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)");
      AddPlot(PdfFile, 50, 0.00, 1.50, "DR(0.10,0.00) > 0.3, ZPT > 80, JPT > 40;x_{JZ}",
         T1, "PT/ZPt", "W * (PT > 40 && DR0 > 0.3 && DR0 < 0.4 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)",
         T2, "PT/ZPt", "W * (PT > 40 && DR0 > 0.3 && DR0 < 0.4 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)",
         T3, "PT/ZPt", "W * (PT > 40 && DR0 > 0.3 && DR0 < 0.4 && ZG0 > 0 && DPhi > 2.8 && ZPt > 80)");
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   RecoilFile.Close();
   NoRecoilFile.Close();
   VacuumFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, int N, double Min, double Max, string Title,
   TTree *T1, string Plot1, string Selection1,
   TTree *T2, string Plot2, string Selection2,
   TTree *T3, string Plot3, string Selection3,
   double LogMin)
{
   TH1D H1("H1", Title.c_str(), N, Min, Max);
   TH1D H2("H2", Title.c_str(), N, Min, Max);
   TH1D H3("H3", Title.c_str(), N, Min, Max);

   PdfFile.SetPageNumber(true);
   PdfFile.AddTextPage(H1.GetTitle());
   PdfFile.SetPageNumber(false);
   H1.SetTitle("");

   H1.SetStats(0);
   H2.SetStats(0);
   H3.SetStats(0);

   H1.SetMarkerColor(kBlue);
   H2.SetMarkerColor(kGreen + 3);
   H3.SetMarkerColor(kRed);
   H1.SetLineColor(kBlue);
   H2.SetLineColor(kGreen + 3);
   H3.SetLineColor(kRed);

   T1->Draw(Form("%s>>H1", Plot1.c_str()), ("(" + Selection1 + ")").c_str());
   T2->Draw(Form("%s>>H2", Plot2.c_str()), ("(" + Selection2 + ")").c_str());
   T3->Draw(Form("%s>>H3", Plot3.c_str()), ("(" + Selection3 + ")").c_str());

   H1.Scale(1 / H1.Integral() / (Max - Min) * N);
   H2.Scale(1 / H2.Integral() / (Max - Min) * N);
   H3.Scale(1 / H3.Integral() / (Max - Min) * N);

   double YMax = 0;
   if(YMax < H1.GetMaximum())   YMax = H1.GetMaximum();
   if(YMax < H2.GetMaximum())   YMax = H2.GetMaximum();
   if(YMax < H3.GetMaximum())   YMax = H3.GetMaximum();

   H1.SetMaximum(YMax * 1.2);

   TCanvas Canvas;

   H1.Draw("");
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");
   H3.Draw("same");
   H3.Draw("hist same");

   PdfFile.AddCanvas(Canvas);
   
   Canvas.SetLogy();
   if(LogMin > 0)
      H1.SetMinimum(LogMin);
   
   H1.SetMaximum(YMax * 5);
   
   H1.Draw("");
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");
   H3.Draw("same");
   H3.Draw("hist same");

   PdfFile.AddCanvas(Canvas);

   H1.Divide(&H3);
   H2.Divide(&H3);

   Canvas.SetLogy(false);

   H1.GetYaxis()->SetTitle("Ratio to vacuum");
   H1.SetMinimum(0);
   H1.SetMaximum(3);

   H1.Draw("");
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");

   PdfFile.AddCanvas(Canvas);
}

void AddPlot2D(PdfFileHelper &PdfFile,
   int NX, double MinX, double MaxX, int NY, double MinY, double MaxY, string Title,
   TTree *T1, string Plot1, string Selection1,
   TTree *T2, string Plot2, string Selection2,
   TTree *T3, string Plot3, string Selection3,
   double ZMax)
{
   TH2D H1("H1H", Title.c_str(), NX, MinX, MaxX, NY, MinY, MaxY);
   TH2D H2("H2H", Title.c_str(), NX, MinX, MaxX, NY, MinY, MaxY);
   TH2D H3("H3H", Title.c_str(), NX, MinX, MaxX, NY, MinY, MaxY);
   
   TProfile P1("P1", Title.c_str(), NX, MinX, MaxX);
   TProfile P2("P2", Title.c_str(), NX, MinX, MaxX);
   TProfile P3("P3", Title.c_str(), NX, MinX, MaxX);

   PdfFile.SetPageNumber(true);
   PdfFile.AddTextPage(H1.GetTitle());
   PdfFile.SetPageNumber(false);
   H1.SetTitle("");
   H2.SetTitle("");
   H3.SetTitle("");

   H1.SetStats(0);
   H2.SetStats(0);
   H3.SetStats(0);

   T1->Draw(Form("%s>>H1H", Plot1.c_str()), ("(" + Selection1 + ")").c_str());
   T2->Draw(Form("%s>>H2H", Plot2.c_str()), ("(" + Selection2 + ")").c_str());
   T3->Draw(Form("%s>>H3H", Plot3.c_str()), ("(" + Selection3 + ")").c_str());
   
   T1->Draw(Form("%s>>P1", Plot1.c_str()), ("(" + Selection1 + ")").c_str());
   T2->Draw(Form("%s>>P2", Plot2.c_str()), ("(" + Selection2 + ")").c_str());
   T3->Draw(Form("%s>>P3", Plot3.c_str()), ("(" + Selection3 + ")").c_str());

   H1.Scale(1 / H1.Integral() / (MaxX - MinX) / (MaxY - MinY) * NX * NY);
   H2.Scale(1 / H2.Integral() / (MaxX - MinX) / (MaxY - MinY) * NX * NY);
   H3.Scale(1 / H3.Integral() / (MaxX - MinX) / (MaxY - MinY) * NX * NY);

   if(ZMax > 0)
   {
      H1.SetMaximum(ZMax);
      H2.SetMaximum(ZMax);
      H3.SetMaximum(ZMax);
   }

   P1.SetLineColor(kMagenta);
   P2.SetLineColor(kMagenta);
   P3.SetLineColor(kMagenta);
   P1.SetMarkerColor(kMagenta);
   P2.SetMarkerColor(kMagenta);
   P3.SetMarkerColor(kMagenta);
   P1.SetMarkerSize(1.5);
   P2.SetMarkerSize(1.5);
   P3.SetMarkerSize(1.5);

   TCanvas Canvas;
   Canvas.Divide(2, 2);

   Canvas.cd(1);
   H1.Draw("colz");
   P1.Draw("same");
   Canvas.cd(2);
   H2.Draw("colz");
   P2.Draw("same");
   Canvas.cd(3);
   H3.Draw("colz");
   P3.Draw("same");
   Canvas.cd(4);

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();
   Latex.DrawLatex(0.1, 0.8, "Upper left: R");
   Latex.DrawLatex(0.1, 0.7, "Upper right: NR");
   Latex.DrawLatex(0.1, 0.6, "Lower: V");

   PdfFile.AddCanvas(Canvas);

   TCanvas Canvas2;

   P1.SetMarkerSize(2.0);
   P2.SetMarkerSize(2.0);
   P3.SetMarkerSize(2.0);

   H1.Draw("colz");
   P1.Draw("same");
   PdfFile.AddCanvas(Canvas2);
   H2.Draw("colz");
   P2.Draw("same");
   PdfFile.AddCanvas(Canvas2);
   H3.Draw("colz");
   P3.Draw("same");
   PdfFile.AddCanvas(Canvas2);
}

void SetAlias(TTree *T)
{
   T->SetAlias("DR0",    "sigJetSDdr12");
   T->SetAlias("ZG0",    "sigJetSDZg");
   T->SetAlias("M0",     "sigJetSDM");
   T->SetAlias("GuuPT0", "sigJetSDPt");
   T->SetAlias("DR1",    "sig1JetSDdr12");
   T->SetAlias("ZG1",    "sig1JetSDZg");
   T->SetAlias("M1",     "sig1JetSDM");
   T->SetAlias("GuuPT1", "sig1JetSDPt");
   T->SetAlias("DR2",    "sig2JetSDdr12");
   T->SetAlias("ZG2",    "sig2JetSDZg");
   T->SetAlias("M2",     "sig2JetSDM");
   T->SetAlias("GuuPT2", "sig2JetSDPt");
   T->SetAlias("DR3",    "sig3JetSDdr12");
   T->SetAlias("ZG3",    "sig3JetSDZg");
   T->SetAlias("M3",     "sig3JetSDM");
   T->SetAlias("GuuPT3", "sig3JetSDPt");
   T->SetAlias("DR4",    "sig4JetSDdr12");
   T->SetAlias("ZG4",    "sig4JetSDZg");
   T->SetAlias("M4",     "sig4JetSDM");
   T->SetAlias("GuuPT4", "sig4JetSDPt");
   T->SetAlias("DR5",    "sig5JetSDdr12");
   T->SetAlias("ZG5",    "sig5JetSDZg");
   T->SetAlias("M5",     "sig5JetSDM");
   T->SetAlias("GuuPT5", "sig5JetSDPt");
   T->SetAlias("DR6",    "sig6JetSDdr12");
   T->SetAlias("ZG6",    "sig6JetSDZg");
   T->SetAlias("M6",     "sig6JetSDM");
   T->SetAlias("GuuPT6", "sig6JetSDPt");

   T->SetAlias("Mu1Px",  "(muonsPt[0]*cos(muonsPhi[0]))");
   T->SetAlias("Mu1Py",  "(muonsPt[0]*sin(muonsPhi[0]))");
   T->SetAlias("Mu1Pz",  "(muonsPt[0]*tanh(muonsEta[0]))");
   T->SetAlias("Mu2Px",  "(muonsPt[1]*cos(muonsPhi[1]))");
   T->SetAlias("Mu2Py",  "(muonsPt[1]*sin(muonsPhi[1]))");
   T->SetAlias("Mu2Pz",  "(muonsPt[1]*tanh(muonsEta[1]))");
   T->SetAlias("ZPx", "(Mu1Px+Mu2Px)");
   T->SetAlias("ZPy", "(Mu1Py+Mu2Py)");
   T->SetAlias("ZPz", "(Mu1Pz+Mu2Pz)");
   T->SetAlias("ZPt", "sqrt(ZPx*ZPx+ZPy*ZPy)");
   T->SetAlias("ZPhi", "(acos(ZPx/ZPt)*((ZPy>0)*2-1))");

   T->SetAlias("DPhi", "acos((ZPx*PT*cos(sigJetPhi)+ZPy*PT*sin(sigJetPhi))/ZPt/PT)");
}

void SetAliasJewel(TTree *T)
{
   T->SetAlias("DR0",    "sigJetSDJeweldr12");
   T->SetAlias("ZG0",    "sigJetSDJewelzg");
   T->SetAlias("M0",     "sigJetSDJewelM");
   T->SetAlias("GuuPT0", "sigJetSDJewelPt");
   T->SetAlias("DR1",    "sig1JetSDJeweldr12");
   T->SetAlias("ZG1",    "sig1JetSDJewelzg");
   T->SetAlias("M1",     "sig1JetSDJewelM");
   T->SetAlias("GuuPT1", "sig1JetSDJewelPt");
   T->SetAlias("DR2",    "sig2JetSDJeweldr12");
   T->SetAlias("ZG2",    "sig2JetSDJewelzg");
   T->SetAlias("M2",     "sig2JetSDJewelM");
   T->SetAlias("GuuPT2", "sig2JetSDJewelPt");
   T->SetAlias("DR3",    "sig3JetSDJeweldr12");
   T->SetAlias("ZG3",    "sig3JetSDJewelzg");
   T->SetAlias("M3",     "sig3JetSDJewelM");
   T->SetAlias("GuuPT3", "sig3JetSDJewelPt");
   T->SetAlias("DR4",    "sig4JetSDJeweldr12");
   T->SetAlias("ZG4",    "sig4JetSDJewelzg");
   T->SetAlias("M4",     "sig4JetSDJewelM");
   T->SetAlias("GuuPT4", "sig4JetSDJewelPt");
   T->SetAlias("DR5",    "sig5JetSDJeweldr12");
   T->SetAlias("ZG5",    "sig5JetSDJewelzg");
   T->SetAlias("M5",     "sig5JetSDJewelM");
   T->SetAlias("GuuPT5", "sig5JetSDJewelPt");
   T->SetAlias("DR6",    "sig6JetSDJeweldr12");
   T->SetAlias("ZG6",    "sig6JetSDJewelzg");
   T->SetAlias("M6",     "sig6JetSDJewelM");
   T->SetAlias("GuuPT6", "sig6JetSDJewelPt");

   T->SetAlias("Mu1Px",  "(muonsPt[0]*cos(muonsPhi[0]))");
   T->SetAlias("Mu1Py",  "(muonsPt[0]*sin(muonsPhi[0]))");
   T->SetAlias("Mu1Pz",  "(muonsPt[0]*tanh(muonsEta[0]))");
   T->SetAlias("Mu2Px",  "(muonsPt[1]*cos(muonsPhi[1]))");
   T->SetAlias("Mu2Py",  "(muonsPt[1]*sin(muonsPhi[1]))");
   T->SetAlias("Mu2Pz",  "(muonsPt[1]*tanh(muonsEta[1]))");
   T->SetAlias("ZPx", "(Mu1Px+Mu2Px)");
   T->SetAlias("ZPy", "(Mu1Py+Mu2Py)");
   T->SetAlias("ZPz", "(Mu1Pz+Mu2Pz)");
   T->SetAlias("ZPt", "sqrt(ZPx*ZPx+ZPy*ZPy)");
   T->SetAlias("ZPhi", "(acos(ZPx/ZPt)*((ZPy>0)*2-1))");

   T->SetAlias("DPhi", "acos((ZPx*PT*cos(sigJetJewelPhi)+ZPy*PT*sin(sigJetJewelPhi))/ZPt/PT)");
}



