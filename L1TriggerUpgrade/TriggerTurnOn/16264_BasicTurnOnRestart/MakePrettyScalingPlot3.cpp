#include <iostream>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TPaveStats.h"

#include "SetStyle.h"

int main()
{
   bool Eyeball = false;

   SetThesisStyle();

   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);

   TFile File("ScalingCurves.root");

   TGraph *G140 = (TGraph *)File.Get("WENu140");
   TGraph *G140Tyler = (TGraph *)File.Get("WENu200TylerA");
   TGraph *G140TylerLow = (TGraph *)File.Get("WENu200TylerLowCalibratedB");
   TGraph *G140TylerHigh = (TGraph *)File.Get("WENu200TylerHighCalibratedB");

   TH2D HWorld("HWorld", ";online: L1 tkEG E_{T} (GeV);offline: p_{T} (GeV)", 100, 10, 32, 100, 0, 55);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.Draw("axis");

   G140->Draw("pl");
   G140Tyler->Draw("pl");
   G140TylerLow->Draw("pl");
   G140TylerHigh->Draw("pl");

   G140->SetLineColor(kBlack);
   G140Tyler->SetLineColor(kBlue);
   G140TylerLow->SetLineColor(kRed);
   G140TylerHigh->SetLineColor(kGreen);
   G140->SetMarkerColor(kBlack);
   G140Tyler->SetMarkerColor(kBlue);
   G140TylerLow->SetMarkerColor(kRed);
   G140TylerHigh->SetMarkerColor(kGreen);

   TLegend Legend(0.42, 0.15, 0.78, 0.40);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(G140, "Old", "pl");
   Legend.AddEntry(G140Tyler, "New", "pl");
   Legend.AddEntry(G140TylerLow, "New (|#eta| < 1.5, 10\% up)", "pl");
   Legend.AddEntry(G140TylerHigh, "New (|#eta| > 1.5, 35\% up)", "pl");
   Legend.Draw();
  
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();

   G140->SetObjectStat(false);
   G140Tyler->SetObjectStat(false);
   G140TylerLow->SetObjectStat(false);
   G140TylerHigh->SetObjectStat(false);

   TF1 FLine("FLine", "pol1");

   G140->Fit(&FLine, "0");
   Latex.SetTextColor(kBlack);
   Latex.DrawLatex(0.16, 0.80, Form("Old: %.2f + %.2f x", FLine.GetParameter(0), FLine.GetParameter(1)));
   
   G140Tyler->Fit(&FLine, "0");
   Latex.SetTextColor(kBlue);
   Latex.DrawLatex(0.16, 0.75, Form("New: %.2f + %.2f x", FLine.GetParameter(0), FLine.GetParameter(1)));
   
   G140TylerLow->Fit(&FLine, "0");
   Latex.SetTextColor(kRed);
   Latex.DrawLatex(0.16, 0.70, Form("New (|#eta| < 1.5): %.2f + %.2f x", FLine.GetParameter(0), FLine.GetParameter(1)));
   
   G140TylerHigh->Fit(&FLine, "0");
   Latex.SetTextColor(kGreen);
   Latex.DrawLatex(0.16, 0.65, Form("New (|#eta| > 1.5): %.2f + %.2f x", FLine.GetParameter(0), FLine.GetParameter(1)));
   // Latex.DrawLatex(0.16, 0.60, "  Evaluated with 85%");

   Canvas.SaveAs("PrettyScalingPlot3.png");
   Canvas.SaveAs("PrettyScalingPlot3.C");
   Canvas.SaveAs("PrettyScalingPlot3.eps");
   Canvas.SaveAs("PrettyScalingPlot3.pdf");

   File.Close();

   return 0;
}






