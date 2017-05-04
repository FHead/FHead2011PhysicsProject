#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"

int main();
void MakePlot(TFile &F1, string Tag1, string Label1, TFile &F2, string Tag2, string Label2, double Max, string OutputBase);

int main()
{
   SetThesisStyle();

   TFile FTT("TurnOnCurvesTT.root");
   TFile FWENu("TurnOnCurvesWENu.root");

   MakePlot(FTT, "Jet75_140", "Jet 75 (PU140)",
      FTT, "Jet75_200", "Jet 75 (PU200)",
      250, "Plot/TTJet75");
   MakePlot(FTT, "Jet100_140", "Jet 100 (PU140)",
      FTT, "Jet100_200", "Jet 100 (PU200)",
      300, "Plot/TTJet100");
   MakePlot(FTT, "Jet150_140", "Jet 150 (PU140)",
      FTT, "Jet150_200", "Jet 150 (PU200)",
      350, "Plot/TTJet150");
   MakePlot(FTT, "Jet200_140", "Jet 200 (PU140)",
      FTT, "Jet200_200", "Jet 200 (PU200)",
      400, "Plot/TTJet200");
   MakePlot(FTT, "Jet250_140", "Jet 250 (PU140)",
      FTT, "Jet250_200", "Jet 250 (PU200)",
      500, "Plot/TTJet250");
   MakePlot(FTT, "Jet300_140", "Jet 300 (PU140)",
      FTT, "Jet300_200", "Jet 300 (PU200)",
      600, "Plot/TTJet300");
   
   MakePlot(FWENu, "EG20_200", "EG 20 (PU200)",
      FWENu, "IsoEG20_200", "IsoEG 20 (PU200)",
      50, "Plot/PU200EGIsoEG20");
   MakePlot(FWENu, "EG25_200", "EG 25 (PU200)",
      FWENu, "IsoEG25_200", "IsoEG 25 (PU200)",
      50, "Plot/PU200EGIsoEG25");
   MakePlot(FWENu, "EG30_200", "EG 30 (PU200)",
      FWENu, "IsoEG30_200", "IsoEG 30 (PU200)",
      50, "Plot/PU200EGIsoEG30");
   
   MakePlot(FWENu, "EG20_140", "EG 20 (PU140)",
      FWENu, "IsoEG20_140", "IsoEG 20 (PU140)",
      50, "Plot/PU140EGIsoEG20");
   MakePlot(FWENu, "EG25_140", "EG 25 (PU140)",
      FWENu, "IsoEG25_140", "IsoEG 25 (PU140)",
      50, "Plot/PU140EGIsoEG25");
   MakePlot(FWENu, "EG30_140", "EG 30 (PU140)",
      FWENu, "IsoEG30_140", "IsoEG 30 (PU140)",
      50, "Plot/PU140EGIsoEG30");
   
   MakePlot(FWENu, "EG20_140", "EG 20 (PU140)",
      FWENu, "EG20_200", "EG 20 (PU200)",
      50, "Plot/EG20");
   MakePlot(FWENu, "EG25_140", "EG 25 (PU140)",
      FWENu, "EG25_200", "EG 25 (PU200)",
      50, "Plot/EG25");
   MakePlot(FWENu, "EG30_140", "EG 30 (PU140)",
      FWENu, "EG30_200", "EG 30 (PU200)",
      50, "Plot/EG30");
   
   MakePlot(FWENu, "IsoEG20_140", "IsoEG 20 (PU140)",
      FWENu, "IsoEG20_200", "IsoEG 20 (PU200)",
      50, "Plot/IsoEG20");
   MakePlot(FWENu, "IsoEG25_140", "IsoEG 25 (PU140)",
      FWENu, "IsoEG25_200", "IsoEG 25 (PU200)",
      50, "Plot/IsoEG25");
   MakePlot(FWENu, "IsoEG30_140", "IsoEG 30 (PU140)",
      FWENu, "IsoEG30_200", "IsoEG 30 (PU200)",
      50, "Plot/IsoEG30");

   FWENu.Close();
   FTT.Close();

   return 0;
}

void MakePlot(TFile &F1, string Tag1, string Label1, TFile &F2, string Tag2, string Label2, double Max, string OutputBase)
{
   TGraphAsymmErrors *G1 = (TGraphAsymmErrors *)F1.Get(Form("%s_TurnOn", Tag1.c_str()));
   TGraphAsymmErrors *G2 = (TGraphAsymmErrors *)F2.Get(Form("%s_TurnOn", Tag2.c_str()));
   TH1F *Fit1 = (TH1F *)F1.Get(Form("%s_FitHistogram", Tag1.c_str()));
   TH1F *Fit2 = (TH1F *)F2.Get(Form("%s_FitHistogram", Tag2.c_str()));

   if(G1 == NULL || G2 == NULL || Fit1 == NULL || Fit2 == NULL)
      return;

   TH2D HWorld("HWorld", ";gen-particle pt;", 100, 0, Max, 100, 0, 1.2);
   HWorld.SetStats(0);

   TCanvas C;

   G1->SetLineColor(kBlack);
   G1->SetMarkerColor(kBlack);
   G1->SetLineWidth(2);
   G2->SetLineColor(kRed);
   G2->SetMarkerColor(kRed);
   G2->SetLineWidth(2);
   Fit1->SetLineColor(kBlack);
   Fit1->SetLineWidth(2);
   Fit2->SetLineColor(kRed);
   Fit2->SetLineWidth(2);

   HWorld.Draw();

   G1->Draw("p");
   G2->Draw("p");
   Fit1->Draw("same");
   Fit2->Draw("same");

   TGraph G;
   G.SetPoint(0, 0, 1);
   G.SetPoint(1, 10000, 1);
   G.Draw("l");

   TLegend Legend(0.52, 0.15, 0.8, 0.3);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(G1, Label1.c_str(), "pl");
   Legend.AddEntry(G2, Label2.c_str(), "pl");
   Legend.Draw();

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C"  , OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}





