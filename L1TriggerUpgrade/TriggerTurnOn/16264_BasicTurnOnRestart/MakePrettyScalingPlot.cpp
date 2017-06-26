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
   TGraph *G200 = (TGraph *)File.Get("WENu200");
   TGraph *G140Tyler = (TGraph *)File.Get("WENu140TylerA");
   TGraph *G200Tyler = (TGraph *)File.Get("WENu200TylerA");

   if(Eyeball == true)
   {
      G140->SetPoint(0, 12, 15);
      G140->SetPoint(1, 15, 19);
      G140->SetPoint(2, 20, 22);
      G140->SetPoint(3, 25, 26);
      G140->SetPoint(4, 30, 32);

      G200->SetPoint(0, 12, 16);
      G200->SetPoint(1, 15, 20);
      G200->SetPoint(2, 20, 22);
      G200->SetPoint(3, 25, 26);
      G200->SetPoint(4, 30, 32);

      G140Tyler->SetPoint(0, 12, 17);
      G140Tyler->SetPoint(1, 15, 23);
      G140Tyler->SetPoint(2, 20, 30);
      G140Tyler->SetPoint(3, 25, 37);
      G140Tyler->SetPoint(4, 30, 45);

      G200Tyler->SetPoint(0, 12, 17);
      G200Tyler->SetPoint(1, 15, 23);
      G200Tyler->SetPoint(2, 20, 30);
      G200Tyler->SetPoint(3, 25, 36);
      G200Tyler->SetPoint(4, 30, 42);
   }
   
   TH2D HWorld("HWorld", ";online: L1 tkEG E_{T} (GeV);offline: p_{T} (GeV)", 100, 10, 32, 100, 0, 55);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.Draw("axis");

   G140->Draw("pl");
   // G200->Draw("pl");
   G140Tyler->Draw("pl");
   // G200Tyler->Draw("pl");

   G140->SetLineColor(kBlack);
   G200->SetLineColor(kRed);
   G140Tyler->SetLineColor(kBlue);
   G200Tyler->SetLineColor(kGreen);
   G140->SetMarkerColor(kBlack);
   G200->SetMarkerColor(kRed);
   G140Tyler->SetMarkerColor(kBlue);
   G200Tyler->SetMarkerColor(kGreen);

   TLegend Legend(0.5, 0.15, 0.8, 0.4);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(G140, "Old (PU140)", "pl");
   // Legend.AddEntry(G200, "Old (PU200)", "pl");
   Legend.AddEntry("", "", "");
   Legend.AddEntry(G140Tyler, "New (PU140)", "pl");
   // Legend.AddEntry(G200Tyler, "New (PU200)", "pl");
   Legend.AddEntry("", "", "");
   Legend.Draw();
  
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();

   G140->SetObjectStat(false);
   G200->SetObjectStat(false);
   G140Tyler->SetObjectStat(false);
   G200Tyler->SetObjectStat(false);
   
   TF1 FLine("FLine", "pol1");

   G140->Fit(&FLine, "0");
   Latex.SetTextColor(kBlack);
   Latex.DrawLatex(0.16, 0.80, Form("Old (PU140): %.2f + %.2f x", FLine.GetParameter(0), FLine.GetParameter(1)));
   
   // G200->Fit(&FLine, "0");
   // Latex.SetTextColor(kRed);
   // Latex.DrawLatex(0.16, 0.75, Form("Old (PU200): %.2f + %.2f x", FLine.GetParameter(0), FLine.GetParameter(1)));
   
   G140Tyler->Fit(&FLine, "0");
   Latex.SetTextColor(kBlue);
   Latex.DrawLatex(0.16, 0.70, Form("New (PU140): %.2f + %.2f x", FLine.GetParameter(0), FLine.GetParameter(1)));
   
   // G200Tyler->Fit(&FLine, "0");
   // Latex.SetTextColor(kGreen);
   // Latex.DrawLatex(0.16, 0.65, Form("New (PU200): %.2f + %.2f x", FLine.GetParameter(0), FLine.GetParameter(1)));

   if(Eyeball == false)
   {
      Canvas.SaveAs("PrettyScalingPlot.png");
      Canvas.SaveAs("PrettyScalingPlot.C");
      Canvas.SaveAs("PrettyScalingPlot.eps");
      Canvas.SaveAs("PrettyScalingPlot.pdf");
   }
   else
   {
      Canvas.SaveAs("PrettyScalingPlotEyeball.png");
      Canvas.SaveAs("PrettyScalingPlotEyeball.C");
      Canvas.SaveAs("PrettyScalingPlotEyeball.eps");
      Canvas.SaveAs("PrettyScalingPlotEyeball.pdf");
   }

   File.Close();

   return 0;
}






