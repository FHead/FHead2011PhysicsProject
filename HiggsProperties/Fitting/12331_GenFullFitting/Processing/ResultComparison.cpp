#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"

#include "PlotHelper2.h"

int main();
void PlotComparison(PsFileHelper &PsFile, TFile &F1, TFile &F2, string HistogramName, int Signal, string Label,
   double TrueValue);

int main()
{
   PsFileHelper PsFile("FitResultComparison.ps");
   PsFile.AddTextPage("Compare S vs. S+B");

   TFile F1("CoolPlot_8.root");
   TFile F2("CoolPlotSB_8.root");

   int SignalCount[] = {30, 40, 50, 70, 85, 100, 150, 200, 250, 300,
      400, 500, 600, 700, 850, 1000, 1500, 2000, 2500, 3000};
   
   vector<string> Items;
   vector<string> Destinations;
   for(int i = 0; i < 20; i++)
   {
      Items.push_back(Form("N_{S} = %d", SignalCount[i]));
      Destinations.push_back(Form("SignalCount%d", i));
   }
   PsFile.AddTableOfContentPage(Items, Destinations, 0.11, 0.8, 0.025);
   PsFile.InsertNamedDestination("HomePage");
   PsFile.SetAutomaticHomeButton();

   for(int i = 0; i < 20; i++)
   {
      PsFile.AddTextPage(Form("N_{S} = %d", SignalCount[i]));
      PsFile.InsertNamedDestination(Form("SignalCount%d", i));
      PlotComparison(PsFile, F1, F2, "HA1ZZ", SignalCount[i], "|R_{1}^{ZZ}|", 0.192);
      PlotComparison(PsFile, F1, F2, "HA2ZZ", SignalCount[i], "|R_{2}^{ZZ}|", 0.000);
      PlotComparison(PsFile, F1, F2, "HA3ZZ", SignalCount[i], "|R_{3}^{ZZ}|", 0.981);
      PlotComparison(PsFile, F1, F2, "HA2ZA", SignalCount[i], "|R_{2}^{ZA}|", 0.00912);
      PlotComparison(PsFile, F1, F2, "HA3ZA", SignalCount[i], "|R_{3}^{ZA}|", 0.0192);
      PlotComparison(PsFile, F1, F2, "HA2AA", SignalCount[i], "|R_{2}^{AA}|", 0.0135);
      PlotComparison(PsFile, F1, F2, "HA3AA", SignalCount[i], "|R_{3}^{AA}|", 0.0154);
      PlotComparison(PsFile, F1, F2, "HBackground", SignalCount[i], "Fraction", 0.2);

      TH2D *H = (TH2D *)F2.Get("HBackground");
      int Bin = H->GetNbinsY();
      double Min = H->GetYaxis()->GetBinLowEdge(1);
      double Max = H->GetYaxis()->GetBinUpEdge(Bin);

      int Index = H->GetXaxis()->FindBin(SignalCount[i]);

      TH1D HProjection("HProjection", "", Bin, Min, Max);
      for(int i = 1; i <= Bin; i++)
         HProjection.SetBinContent(i, H->GetBinContent(Index, i));

      HProjection.SetStats(0);
      HProjection.SetLineWidth(2);
      HProjection.SetLineColor(kRed);
      HProjection.GetXaxis()->SetTitle("Fraction");
      HProjection.Scale(1 / (HProjection.Integral() + 1e-10));

      TGraph G;
      G.SetPoint(0, 0.2, 0);
      G.SetPoint(1, 0.2, 10000);
      G.SetLineWidth(2);
      G.SetLineColor(kGreen);

      TCanvas C;
      HProjection.Draw();
      G.Draw("l");

      PsFile.AddCanvas(C);
   }

   F1.Close();
   F2.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void PlotComparison(PsFileHelper &PsFile, TFile &F1, TFile &F2, string HistogramName, int Signal, string Label,
   double TrueValue)
{
   TH2D *H1 = (TH2D *)F1.Get(HistogramName.c_str());
   TH2D *H2 = (TH2D *)F2.Get(HistogramName.c_str());

   if(H1 == NULL || H2 == NULL)
      return;

   int Bin = H1->GetNbinsY();
   double Min = H1->GetYaxis()->GetBinLowEdge(1);
   double Max = H1->GetYaxis()->GetBinUpEdge(Bin);

   int Index = H1->GetXaxis()->FindBin(Signal);

   TH1D HProjection1("HProjection1", "", Bin, Min, Max);
   TH1D HProjection2("HProjection2", "", Bin, Min, Max);

   for(int i = 1; i <= Bin; i++)
   {
      HProjection1.SetBinContent(i, H1->GetBinContent(Index, i));
      HProjection2.SetBinContent(i, H2->GetBinContent(Index, i));
   }

   HProjection1.SetStats(0);
   HProjection1.SetLineWidth(2);
   HProjection1.SetLineColor(kBlack);
   HProjection1.GetXaxis()->SetTitle(Label.c_str());
   HProjection2.SetStats(0);
   HProjection2.SetLineWidth(2);
   HProjection2.SetLineColor(kRed);
   HProjection2.GetXaxis()->SetTitle(Label.c_str());

   HProjection1.Scale(1 / (HProjection1.Integral() + 1e-10));
   HProjection2.Scale(1 / (HProjection2.Integral() + 1e-10));

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HProjection1, "No background", "l");
   Legend.AddEntry(&HProjection2, "With background", "l");

   TGraph G;
   G.SetPoint(0, TrueValue, 0);
   G.SetPoint(1, TrueValue, 100000);
   G.SetLineWidth(2);
   G.SetLineColor(kGreen);

   TCanvas C;
   HProjection1.Draw();
   HProjection2.Draw("same");
   G.Draw("l");
   Legend.Draw();
   PsFile.AddCanvas(C);
}




