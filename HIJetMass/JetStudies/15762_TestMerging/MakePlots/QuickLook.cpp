#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main();
void SetAlias(TTree *T);
void MakePlots(vector<TTree *> T, string ToPlot, string Cut, string XAxis, string OutputBase, double Min, double Max);
void HistogramColoring(TH1D *H1, TH1D *H2, TH1D *H3, TH1D *H4);

int main()
{
   SetThesisStyle();

   TFile F1N("Baseline_000_N.root");
   TFile F1Y("Baseline_000_Y.root");
   TFile F2N("Baseline_002_N.root");
   TFile F2Y("Baseline_002_Y.root");
   TFile F3N("Baseline_005_N.root");
   TFile F3Y("Baseline_005_Y.root");
   TFile F4N("Baseline_010_N.root");
   TFile F4Y("Baseline_010_Y.root");

   vector<TTree *> T(8);

   T[0] = (TTree *)F1N.Get("OutputTree");
   T[1] = (TTree *)F1Y.Get("OutputTree");
   T[2] = (TTree *)F2N.Get("OutputTree");
   T[3] = (TTree *)F2Y.Get("OutputTree");
   T[4] = (TTree *)F3N.Get("OutputTree");
   T[5] = (TTree *)F3Y.Get("OutputTree");
   T[6] = (TTree *)F4N.Get("OutputTree");
   T[7] = (TTree *)F4Y.Get("OutputTree");

   for(int i = 0; i < 8; i++)
      SetAlias(T[i]);

   MakePlots(T, "BestJetDR", "Baseline0", "Sub-jet DR", "MergingDR0", 0.1, 0.45);
   MakePlots(T, "BestJetSDMass/BestJetPT", "Baseline0", "SD Mass / Jet PT", "MergingMass0", 0, 0.3);
   MakePlots(T, "BestJetDR2", "Baseline7", "Sub-jet DR", "MergingDR7", 0.1, 0.45);
   MakePlots(T, "BestJetSDMass2/BestJetPT", "Baseline7", "SD Mass / Jet PT", "MergingMass7", 0, 0.3);

   F4Y.Close();
   F4N.Close();
   F3Y.Close();
   F3N.Close();
   F2Y.Close();
   F2N.Close();
   F1Y.Close();
   F1N.Close();

   return 0;
}

void SetAlias(TTree *T)
{
   if(T == NULL)
      return;

   T->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");

   T->SetAlias("Baseline", "(BestJetPT > 100 && abs(BestJetEta) < 1.3 && MatchedDR < 0.2)");
   T->SetAlias("Baseline0", "(Baseline && BestJetDR > 0.1)");
   T->SetAlias("Baseline7", "(Baseline && BestJetDR2 > 0.1)");
}

void MakePlots(vector<TTree *> T, string ToPlot, string Cut, string XAxis, string OutputBase, double Min, double Max)
{
   if(T.size() != 8)   // Wut.
      return;

   vector<TH1D *> H(8);
   for(int i = 0; i < (int)T.size(); i++)
      H[i] = new TH1D(Form("H%d", i + 1), Form(";%s;a.u.", XAxis.c_str()), 25, Min, Max);

   for(int i = 0; i < (int)T.size(); i++)
      T[i]->Draw(Form("%s>>H%d", ToPlot.c_str(), i + 1), Cut.c_str());

   HistogramColoring(H[0], H[2], H[4], H[6]);
   HistogramColoring(H[1], H[3], H[5], H[7]);

   TLegend Legend(0.4, 0.8, 0.7, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(H[0], "No merging", "l");
   Legend.AddEntry(H[2], "Merging DR < 0.02", "l");
   Legend.AddEntry(H[4], "Merging DR < 0.05", "l");
   Legend.AddEntry(H[6], "Merging DR < 0.10", "l");

   H[0]->SetMaximum(H[0]->GetMaximum() * 1.5);
   H[1]->SetMaximum(H[1]->GetMaximum() * 1.5);

   TCanvas C;

   H[0]->Draw("hist");
   H[2]->Draw("same");
   H[4]->Draw("same");
   H[6]->Draw("same");
   Legend.Draw();

   C.SaveAs(Form("%s_N.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_N.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_N.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_N.pdf", OutputBase.c_str()));

   H[1]->Draw("hist");
   H[3]->Draw("same");
   H[5]->Draw("same");
   H[7]->Draw("same");
   Legend.Draw();

   C.SaveAs(Form("%s_Y.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_Y.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_Y.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_Y.pdf", OutputBase.c_str()));

   for(int i = 0; i < (int)T.size(); i++)
      delete H[i];
}

void HistogramColoring(TH1D *H1, TH1D *H2, TH1D *H3, TH1D *H4)
{
   H1->SetStats(0);
   H2->SetStats(0);
   H3->SetStats(0);
   H4->SetStats(0);
   
   H1->SetLineWidth(2);
   H2->SetLineWidth(2);
   H3->SetLineWidth(2);
   H4->SetLineWidth(2);
   
   H1->SetLineColor(kBlack);
   H2->SetLineColor(kBlue);
   H3->SetLineColor(kGreen + 3);
   H4->SetLineColor(kRed);
}








