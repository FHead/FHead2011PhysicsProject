#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH1D.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

#define PI 3.1415926535

int main();
void Add1DPlot(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string Plot, string Selection,
   int Bin, double Min, double Max, bool LogY);
void AddProfilePlot(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string Plot, string Selection,
   int Bin, double Min, double Max, bool LogY);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("FileComparison.pdf");
   PdfFile.AddTextPage("Compare files");

   vector<string> Explanation(10);
   Explanation[0] = "Compare old sample with new big sample";
   Explanation[1] = "";
   Explanation[2] = "Black = old sample";
   Explanation[3] = "Red = new sample";
   Explanation[4] = "";
   PdfFile.AddTextPage(Explanation);

   TFile F1("AA6Dijet120.root");
   TFile F2("AA6Dijet120CymbalLargePartial.root");

   TTree *T1 = (TTree *)F1.Get("T");
   TTree *T2 = (TTree *)F2.Get("T");

   T1->SetAlias("SDZG0", "(min(SubJet1PT0,SubJet2PT0)/(SubJet1PT0+SubJet2PT0))");
   T1->SetAlias("SDZG7", "(min(SubJet1PT7,SubJet2PT7)/(SubJet1PT7+SubJet2PT7))");
   T1->SetAlias("Baseline0", "(abs(JetEta) < 1.3 && MatchDR < 0.1 && SubJetDR0 > 0)");
   T1->SetAlias("Baseline7", "(abs(JetEta) < 1.3 && MatchDR < 0.1 && SubJetDR7 > 0)");
   T1->SetAlias("GroomedJetPTFraction0", "((SubJet1PT0 + SubJet2PT0) / MatchPT)");
   T1->SetAlias("GroomedJetPTFraction7", "((SubJet1PT7 + SubJet2PT7) / MatchPT)");
   
   T2->SetAlias("SDZG0", "(min(SubJet1PT0,SubJet2PT0)/(SubJet1PT0+SubJet2PT0))");
   T2->SetAlias("SDZG7", "(min(SubJet1PT7,SubJet2PT7)/(SubJet1PT7+SubJet2PT7))");
   T2->SetAlias("Baseline0", "(abs(JetEta) < 1.3 && MatchDR < 0.1 && SubJetDR0 > 0)");
   T2->SetAlias("Baseline7", "(abs(JetEta) < 1.3 && MatchDR < 0.1 && SubJetDR7 > 0)");
   T2->SetAlias("GroomedJetPTFraction0", "((SubJet1PT0 + SubJet2PT0) / MatchPT)");
   T2->SetAlias("GroomedJetPTFraction7", "((SubJet1PT7 + SubJet2PT7) / MatchPT)");

   T1->SetMarkerStyle(11);
   T1->SetMarkerColor(kBlack);
   T1->SetLineColor(kBlack);
   T2->SetMarkerStyle(11);
   T2->SetMarkerColor(kRed);
   T2->SetLineColor(kRed);

   PdfFile.AddTextPage("Centrality");
   
   AddProfilePlot(PdfFile, T1, T2, "Rho:Centrality", "", 100, 0, 1, false);
   Add1DPlot(PdfFile, T1, T2, "Centrality", "", 100, 0, 1, false);
   Add1DPlot(PdfFile, T1, T2, "Centrality", "abs(JetEta) < 1.3 && JetPT > 120", 100, 0, 1, false);
   Add1DPlot(PdfFile, T1, T2, "HF", "", 100, 0, 9000, false);
   Add1DPlot(PdfFile, T1, T2, "HFPlus", "", 100, 0, 4500, false);
   Add1DPlot(PdfFile, T1, T2, "HFMinus", "", 100, 0, 4500, false);
   Add1DPlot(PdfFile, T1, T2, "HFPlusEta4", "", 100, 0, 2000, false);
   Add1DPlot(PdfFile, T1, T2, "HFMinusEta4", "", 100, 0, 2000, false);
   Add1DPlot(PdfFile, T1, T2, "HFPlusEta4 + HFMinusEta4", "", 100, 0, 4000, false);
   AddProfilePlot(PdfFile, T1, T2, "HFPlus:HFMinus", "", 100, 0, 4500, false);
   AddProfilePlot(PdfFile, T1, T2, "HFPlusEta4:HFMinusEta4", "", 100, 0, 2000, false);
   AddProfilePlot(PdfFile, T1, T2, "HF:Centrality", "", 100, 0, 1, false);
   AddProfilePlot(PdfFile, T1, T2, "HF:Centrality", "", 100, 0, 1, true);
   
   PdfFile.AddTextPage("Jets");
   
   Add1DPlot(PdfFile, T1, T2, "JetPT", "abs(JetEta) < 1.3", 100, 0, 500, true);
   Add1DPlot(PdfFile, T1, T2, "JetEta", "", 20, -5, 5, true);
   Add1DPlot(PdfFile, T1, T2, "JetEta", "JetPT > 120", 20, -5, 5, true);
   Add1DPlot(PdfFile, T1, T2, "JetPhi", "", 20, -PI, PI, false);
   Add1DPlot(PdfFile, T1, T2, "JetPhi", "JetPT > 120", 20, -PI, PI, false);
   Add1DPlot(PdfFile, T1, T2, "MatchDR", "", 50, 0, 0.5, true);
   Add1DPlot(PdfFile, T1, T2, "MatchDR", "JetPT > 120", 50, 0, 0.5, true);
   
   PdfFile.AddTextPage("Grooming");
   
   Add1DPlot(PdfFile, T1, T2, "GroomedJetPTFraction0", "Baseline0 && JetPT > 120", 100, 0.5, 1.0, false);
   Add1DPlot(PdfFile, T1, T2, "GroomedJetPTFraction0", "Baseline0 && JetPT > 120", 100, 0.5, 1.0, true);
   Add1DPlot(PdfFile, T1, T2, "GroomedJetPTFraction7", "Baseline7 && JetPT > 120", 100, 0.0, 1.0, false);
   Add1DPlot(PdfFile, T1, T2, "GroomedJetPTFraction7", "Baseline7 && JetPT > 120", 100, 0.0, 1.0, true);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR0 > 0", "abs(JetEta) < 1.3 && MatchDR < 0.2 && JetPT > 120", 2, 0, 2, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR7 > 0", "abs(JetEta) < 1.3 && MatchDR < 0.2 && JetPT > 120", 2, 0, 2, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR0 > 0.1", "Baseline0 && JetPT > 120", 2, 0, 2, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR7 > 0.1", "Baseline0 && JetPT > 120", 2, 0, 2, false);

   PdfFile.AddTextPage("PT > 80");

   Add1DPlot(PdfFile, T1, T2, "SubJetDR0", "Baseline0 && JetPT > 80", 40, 0, 0.4, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR0", "Baseline0 && JetPT > 80", 40, 0, 0.4, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 80 && SubJetDR0 > 0", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 80 && SubJetDR0 > 0", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 80 && SubJetDR0 > 0.1", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 80 && SubJetDR0 > 0.1", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDZG0", "Baseline0 && JetPT > 80 && SubJetDR0 > 0.1", 40, 0, 0.5, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR7", "Baseline7 && JetPT > 80", 40, 0, 0.4, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR7", "Baseline7 && JetPT > 80", 40, 0, 0.4, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 80 && SubJetDR7 > 0", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 80 && SubJetDR7 > 0", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 80 && SubJetDR7 > 0.1", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 80 && SubJetDR7 > 0.1", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDZG7", "Baseline7 && JetPT > 80 && SubJetDR7 > 0.1", 40, 0, 0.5, false);
   
   PdfFile.AddTextPage("PT > 120");
   
   Add1DPlot(PdfFile, T1, T2, "SubJetDR0", "Baseline0 && JetPT > 120", 40, 0, 0.4, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR0", "Baseline0 && JetPT > 120", 40, 0, 0.4, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 120 && SubJetDR0 > 0", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 120 && SubJetDR0 > 0", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 120 && SubJetDR0 > 0.1", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 120 && SubJetDR0 > 0.1", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDZG0", "Baseline0 && JetPT > 120 && SubJetDR0 > 0.1", 40, 0, 0.5, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR7", "Baseline7 && JetPT > 120", 40, 0, 0.4, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR7", "Baseline7 && JetPT > 120", 40, 0, 0.4, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 120 && SubJetDR7 > 0", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 120 && SubJetDR7 > 0", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 120 && SubJetDR7 > 0.1", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 120 && SubJetDR7 > 0.1", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDZG7", "Baseline7 && JetPT > 120 && SubJetDR7 > 0.1", 40, 0, 0.5, false);
   
   PdfFile.AddTextPage("PT > 120 && Centrality < 0.1");
   
   Add1DPlot(PdfFile, T1, T2, "SubJetDR0", "Baseline0 && JetPT > 120 && Centrality < 0.1", 40, 0, 0.4, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR0", "Baseline0 && JetPT > 120 && Centrality < 0.1", 40, 0, 0.4, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 120 && SubJetDR0 > 0 && Centrality < 0.1", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 120 && SubJetDR0 > 0 && Centrality < 0.1", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 120 && SubJetDR0 > 0.1 && Centrality < 0.1", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass0 / JetPT", "Baseline0 && JetPT > 120 && SubJetDR0 > 0.1 && Centrality < 0.1", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDZG0", "Baseline0 && JetPT > 120 && SubJetDR0 > 0.1 && Centrality < 0.1", 40, 0, 0.5, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR7", "Baseline7 && JetPT > 120 && Centrality < 0.1", 40, 0, 0.4, false);
   Add1DPlot(PdfFile, T1, T2, "SubJetDR7", "Baseline7 && JetPT > 120 && Centrality < 0.1", 40, 0, 0.4, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 120 && SubJetDR7 > 0 && Centrality < 0.1", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 120 && SubJetDR7 > 0 && Centrality < 0.1", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 120 && SubJetDR7 > 0.1 && Centrality < 0.1", 40, 0, 0.3, false);
   Add1DPlot(PdfFile, T1, T2, "SDMass7 / JetPT", "Baseline7 && JetPT > 120 && SubJetDR7 > 0.1 && Centrality < 0.1", 40, 0, 0.3, true);
   Add1DPlot(PdfFile, T1, T2, "SDZG7", "Baseline7 && JetPT > 120 && SubJetDR7 > 0.1 && Centrality < 0.1", 40, 0, 0.5, false);

   F2.Close();
   F1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void Add1DPlot(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string Plot, string Selection,
   int Bin, double Min, double Max, bool LogY)
{
   if(T1 == NULL || T2 == NULL)
      return;

   TCanvas C;

   string Title = Plot;
   if(Selection != "")
      Title = Title + ", " + Selection;

   TH1D H1("H1", Title.c_str(), Bin, Min, Max);
   TH1D H2("H2", Title.c_str(), Bin, Min, Max);

   H1.SetStats(0);
   H2.SetStats(0);

   H1.SetMarkerColor(kBlack);
   H2.SetMarkerColor(kRed);
   
   H1.SetLineColor(kBlack);
   H2.SetLineColor(kRed);

   H1.Sumw2();
   H2.Sumw2();

   T1->Draw((Plot + ">>H1").c_str(), Selection.c_str(), "");
   T2->Draw((Plot + ">>H2").c_str(), Selection.c_str(), "");

   H1.Scale(1 / H1.Integral());
   H2.Scale(1 / H2.Integral());

   H1.Draw("error");
   H2.Draw("error same");
   H1.Draw("hist same");
   H2.Draw("hist same");

   if(LogY == true)
      C.SetLogy();

   PdfFile.AddCanvas(C);
}

void AddProfilePlot(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string Plot, string Selection,
   int Bin, double Min, double Max, bool LogY)
{
   if(T1 == NULL || T2 == NULL)
      return;

   TCanvas C;

   string Title = Plot;
   if(Selection != "")
      Title = Title + ", " + Selection;

   TProfile P1("P1", Title.c_str(), Bin, Min, Max);
   TProfile P2("P2", Title.c_str(), Bin, Min, Max);

   P1.SetStats(0);
   P2.SetStats(0);

   P1.SetMarkerColor(kBlack);
   P2.SetMarkerColor(kRed);

   T1->Draw((Plot + ">>P1").c_str(), Selection.c_str(), "prof");
   T2->Draw((Plot + ">>P2").c_str(), Selection.c_str(), "prof");

   P1.Draw();
   P2.Draw("same");
   
   if(LogY == true)
      C.SetLogy();

   PdfFile.AddCanvas(C);
}



