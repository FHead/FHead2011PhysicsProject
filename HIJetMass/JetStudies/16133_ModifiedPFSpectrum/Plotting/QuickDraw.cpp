#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
void QuickDraw(double PTMin, double PTMax, double CentralityMin, double CentralityMax);
void TidyHistogram(TH1D &H1, TH1D &H2, TH1D &H3, TH1D &H4, TH1D &H5, TH1D &H6);
void DoPlot(TTree *TA, TTree *TB, TTree *TC, TTree *TD, TTree *TE, TTree *TF, string Plot, string Cut,
   int Bin, double Min, double Max, string XAxis, string OutputBase);
void CommonAlias(TTree *T, double PTMin, double PTMax, double CentralityMin, double CentralityMax);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   if(argc != 5)
   {
      cerr << "Usage: " << argv[0] << " PTMin PTMax CentralityMin CentralityMax" << endl;
      return -1;
   }

   QuickDraw(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]));

   return 0;
}

void QuickDraw(double PTMin, double PTMax, double CentralityMin, double CentralityMax)
{
   string Tag = Form("C_%.0f_%.0f_PT_%.0f_%.0f", CentralityMin * 100, CentralityMax * 100, PTMin, PTMax);

   TCanvas Canvas;

   TFile FA("PTType0_PP6Dijet.root");
   TFile FB("PTType1_PP6Dijet.root");
   TFile FC("PTType2_PP6Dijet.root");
   TFile FD("PTType3_PP6Dijet.root");
   TFile FE("PTType4_PP6Dijet.root");
   TFile FF("PTType5_PP6Dijet.root");

   TTree *TA = (TTree *)FA.Get("OutputTree");
   TTree *TB = (TTree *)FB.Get("OutputTree");
   TTree *TC = (TTree *)FC.Get("OutputTree");
   TTree *TD = (TTree *)FD.Get("OutputTree");
   TTree *TE = (TTree *)FE.Get("OutputTree");
   TTree *TF = (TTree *)FF.Get("OutputTree");

   CommonAlias(TA, PTMin, PTMax, CentralityMin, CentralityMax);
   CommonAlias(TB, PTMin, PTMax, CentralityMin, CentralityMax);
   CommonAlias(TC, PTMin, PTMax, CentralityMin, CentralityMax);
   CommonAlias(TD, PTMin, PTMax, CentralityMin, CentralityMax);
   CommonAlias(TE, PTMin, PTMax, CentralityMin, CentralityMax);
   CommonAlias(TF, PTMin, PTMax, CentralityMin, CentralityMax);

   TA->SetAlias("RMS", "(exp(1.25391-27.2957*X)+exp(3.31530-3.53222*X))");
   TB->SetAlias("RMS", "(exp(1.31146-26.4782*X)+exp(3.33246-3.44030*X))");
   TC->SetAlias("RMS", "(exp(1.17638-30.6254*X)+exp(3.29809-3.64337*X))");
   TD->SetAlias("RMS", "(exp(1.41452-23.8596*X)+exp(3.31170-3.42480*X))");
   TE->SetAlias("RMS", "(exp(1.30743-29.9660*X)+exp(3.31752-3.48047*X))");
   TF->SetAlias("RMS", "(exp(1.46006-24.6905*X)+exp(3.33067-3.35312*X))");

   DoPlot(TA, TB, TC, TD, TE, TF, "BestJetDR",               "Baseline0", 50, 0, 0.5, "DR",         "DR_" + Tag);
   DoPlot(TA, TB, TC, TD, TE, TF, "BestJetSDMass/BestJetPT", "Baseline0", 30, 0, 0.3, "Mass/PT",    "SDMass_" + Tag);
   DoPlot(TA, TB, TC, TD, TE, TF, "BestJetZG",               "Baseline0", 25, 0, 0.5, "z_{g}",      "ZG_" + Tag);
   DoPlot(TA, TB, TC, TD, TE, TF, "BestJetDR2",              "Baseline7", 50, 0, 0.5, "DR",         "DR7_" + Tag);
   DoPlot(TA, TB, TC, TD, TE, TF, "BestJetSDMass2/BestJetPT","Baseline7", 20, 0, 0.3, "Mass/PT",    "SDMass7_" + Tag);
   DoPlot(TA, TB, TC, TD, TE, TF, "BestJetZG2",              "Baseline7", 25, 0, 0.5, "z_{g}",      "ZG7_" + Tag);
   DoPlot(TA, TB, TC, TD, TE, TF, "BestJetSDPT/BestJetPT",   "Baseline0", 50, 0.5, 1, "PT/PT",      "GroomedPTFraction_" + Tag);
   DoPlot(TA, TB, TC, TD, TE, TF, "Centrality/100",          "Baseline0", 20, 0, 0.8, "Centrality", "Centrality_" + Tag);
   DoPlot(TA, TB, TC, TD, TE, TF, "BestJetPT",               "Baseline0", 50, 0, 500, "PT",         "JetPT_" + Tag);
}

void TidyHistogram(TH1D &H1, TH1D &H2, TH1D &H3, TH1D &H4, TH1D &H5, TH1D &H6)
{
   double BinSize1 = (H1.GetXaxis()->GetBinUpEdge(H1.GetNbinsX()) - H1.GetXaxis()->GetBinLowEdge(1)) / H1.GetNbinsX();
   double BinSize2 = (H2.GetXaxis()->GetBinUpEdge(H2.GetNbinsX()) - H2.GetXaxis()->GetBinLowEdge(1)) / H2.GetNbinsX();
   double BinSize3 = (H3.GetXaxis()->GetBinUpEdge(H3.GetNbinsX()) - H3.GetXaxis()->GetBinLowEdge(1)) / H3.GetNbinsX();
   double BinSize4 = (H4.GetXaxis()->GetBinUpEdge(H4.GetNbinsX()) - H4.GetXaxis()->GetBinLowEdge(1)) / H4.GetNbinsX();
   double BinSize5 = (H5.GetXaxis()->GetBinUpEdge(H5.GetNbinsX()) - H5.GetXaxis()->GetBinLowEdge(1)) / H5.GetNbinsX();
   double BinSize6 = (H6.GetXaxis()->GetBinUpEdge(H6.GetNbinsX()) - H6.GetXaxis()->GetBinLowEdge(1)) / H6.GetNbinsX();

   H1.Scale(1 / H1.Integral() / BinSize1);
   H2.Scale(1 / H2.Integral() / BinSize2);
   H3.Scale(1 / H3.Integral() / BinSize3);
   H4.Scale(1 / H4.Integral() / BinSize4);
   H5.Scale(1 / H5.Integral() / BinSize5);
   H6.Scale(1 / H6.Integral() / BinSize6);
   
   H1.SetStats(0);
   H2.SetStats(0);
   H3.SetStats(0);
   H4.SetStats(0);
   H5.SetStats(0);
   H6.SetStats(0);

   H1.SetLineColor(kRed);
   H1.SetMarkerColor(kRed);
   H1.SetMinimum(0);
   
   H3.SetLineColor(kBlue);
   H3.SetMarkerColor(kBlue);
   
   H4.SetLineColor(kGreen + 3);
   H4.SetMarkerColor(kGreen + 3);
   
   H5.SetLineColor(kYellow + 3);
   H5.SetMarkerColor(kYellow + 3);
   
   H6.SetLineColor(kMagenta);
   H6.SetMarkerColor(kMagenta);

   double Maximum = max(max(H1.GetMaximum(), H2.GetMaximum()), max(H3.GetMaximum(), H4.GetMaximum()));
   H1.SetMaximum(Maximum * 1.1);

   H1.SetMarkerSize(1.4);
   H2.SetMarkerSize(1.3);
   H3.SetMarkerSize(1.2);
   H4.SetMarkerSize(1.1);
   H5.SetMarkerSize(1.0);
   H6.SetMarkerSize(0.9);
}

void DoPlot(TTree *TA, TTree *TB, TTree *TC, TTree *TD, TTree *TE, TTree *TF, string Plot, string Cut,
   int Bin, double Min, double Max, string XAxis, string OutputBase)
{
   TCanvas Canvas;
   
   if(TA == NULL)   return;
   if(TB == NULL)   return;
   if(TC == NULL)   return;
   if(TD == NULL)   return;
   if(TE == NULL)   return;
   if(TF == NULL)   return;

   TH1D HA("HA", Form(";%s;a.u.", XAxis.c_str()), Bin, Min, Max);   HA.Sumw2();
   TH1D HB("HB", Form(";%s;a.u.", XAxis.c_str()), Bin, Min, Max);   HB.Sumw2();
   TH1D HC("HC", Form(";%s;a.u.", XAxis.c_str()), Bin, Min, Max);   HC.Sumw2();
   TH1D HD("HD", Form(";%s;a.u.", XAxis.c_str()), Bin, Min, Max);   HD.Sumw2();
   TH1D HE("HE", Form(";%s;a.u.", XAxis.c_str()), Bin, Min, Max);   HE.Sumw2();
   TH1D HF("HF", Form(";%s;a.u.", XAxis.c_str()), Bin, Min, Max);   HF.Sumw2();

   TA->Draw(Form("%s>>HA", Plot.c_str()), Cut.c_str(), "hist");
   TB->Draw(Form("%s>>HB", Plot.c_str()), Cut.c_str(), "same");
   TC->Draw(Form("%s>>HC", Plot.c_str()), Cut.c_str(), "same");
   TD->Draw(Form("%s>>HD", Plot.c_str()), Cut.c_str(), "same");
   TE->Draw(Form("%s>>HE", Plot.c_str()), Cut.c_str(), "same");
   TF->Draw(Form("%s>>HF", Plot.c_str()), Cut.c_str(), "same");
   
   TidyHistogram(HA, HB, HC, HD, HE, HF);

   HA.Draw();
   HB.Draw("same");
   HC.Draw("same");
   HD.Draw("same");
   HE.Draw("same");
   HF.Draw("same");

   // Canvas.SaveAs(Form("Plots/%s.png", OutputBase.c_str()));
   // Canvas.SaveAs(Form("Plots/%s.C",   OutputBase.c_str()));
   // Canvas.SaveAs(Form("Plots/%s.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("Plots/%s.pdf", OutputBase.c_str()));
   
   HA.Draw();
   HD.Draw("same");
   HE.Draw("same");
   HF.Draw("same");

   // Canvas.SaveAs(Form("Plots/%s_Clean.png", OutputBase.c_str()));
   // Canvas.SaveAs(Form("Plots/%s_Clean.C",   OutputBase.c_str()));
   // Canvas.SaveAs(Form("Plots/%s_Clean.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("Plots/%s_Clean.pdf", OutputBase.c_str()));

   HB.Divide(&HA);
   HC.Divide(&HA);
   HD.Divide(&HA);
   HE.Divide(&HA);
   HF.Divide(&HA);

   HB.GetYaxis()->SetTitle("Ratio to nominal");
   HC.GetYaxis()->SetTitle("Ratio to nominal");
   HD.GetYaxis()->SetTitle("Ratio to nominal");
   HE.GetYaxis()->SetTitle("Ratio to nominal");
   HF.GetYaxis()->SetTitle("Ratio to nominal");

   HB.SetMaximum(2);
   HB.SetMinimum(0);
   HD.SetMaximum(2);
   HD.SetMinimum(0);

   TGraph G;
   G.SetPoint(0, 0, 1);
   G.SetPoint(1, 10000, 1);

   HB.Draw();
   HC.Draw("same");
   HD.Draw("same");
   HE.Draw("same");
   HF.Draw("same");
   G.Draw("l");
   
   // Canvas.SaveAs(Form("Plots/%s_Ratio.png", OutputBase.c_str()));
   // Canvas.SaveAs(Form("Plots/%s_Ratio.C",   OutputBase.c_str()));
   // Canvas.SaveAs(Form("Plots/%s_Ratio.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("Plots/%s_Ratio.pdf", OutputBase.c_str()));
   
   HD.Draw("");
   HE.Draw("same");
   HF.Draw("same");
   G.Draw("l");
   
   // Canvas.SaveAs(Form("Plots/%s_RatioClean.png", OutputBase.c_str()));
   // Canvas.SaveAs(Form("Plots/%s_RatioClean.C",   OutputBase.c_str()));
   // Canvas.SaveAs(Form("Plots/%s_RatioClean.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("Plots/%s_RatioClean.pdf", OutputBase.c_str()));
}

void CommonAlias(TTree *T, double PTMin, double PTMax, double CentralityMin, double CentralityMax)
{
   if(T == NULL)
      return;

   T->SetAlias("ExcessPT", "(TotalPTInJet-Rho*0.4*0.4*3.1415926535)");
   T->SetAlias("X", "(Centrality/100)");
   T->SetAlias("RMST", "(19.15-23.28*X+4.567e-7*X*X-467.4*X*X*X+2110*X*X*X*X-2993*X*X*X*X*X+227.9*X*X*X*X*X*X+2019*X*X*X*X*X*X*X+876.3*X*X*X*X*X*X*X*X-3027*X*X*X*X*X*X*X*X*X+1239*X*X*X*X*X*X*X*X*X*X)");   // target RMS
   T->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT/(2*RMST*RMST))/exp(-ExcessPT*ExcessPT/(2*RMS*RMS)))");

   T->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");
   
   T->SetAlias("CentralityCut", Form("(X >= %f && X < %f)", CentralityMin, CentralityMax));
   T->SetAlias("PTCut", Form("(BestJetPT >= %f && BestJetPT < %f)", PTMin, PTMax));
   T->SetAlias("CommonBaseline", "(CentralityCut && PTCut && abs(BestJetEta) < 1.3 && MatchedDR < 0.1)");

   T->SetAlias("Baseline0", "MCWeight * (CommonBaseline && BestJetDR > 0.1 && BestJetDR < 1.0 && BestJetZG > 0.00)");
   T->SetAlias("Baseline7", "MCWeight * (CommonBaseline && BestJetDR2 > 0.1 && BestJetDR2 < 1.0 && BestJetZG2 > 0.00)");
}


