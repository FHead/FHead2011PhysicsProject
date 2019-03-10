#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TLegend.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooArgList.h"
using namespace RooFit;

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   int N = 8;
   int PT[] = {50, 75, 100, 120, 140, 160, 180, 200};

   TGraphErrors GData, GMC, GRatio;
   TGraphErrors RData, RMC, RRatio;

   GData.SetTitle("Data");
   GMC.SetTitle("MC");
   RData.SetTitle("Data Width");
   RMC.SetTitle("MC Width");

   TFile File("ToyInput.root");

   for(int i = 0; i < N; i++)
   {
      TH1D *H = (TH1D *)File.Get(Form("MethodT_%d_0_Data", PT[i]));
      TF1 Fit("Fit", "gaus");
      H->Fit(&Fit);
      GData.SetPoint(i, PT[i], Fit.GetParameter(1));
      GData.SetPointError(i, 0, Fit.GetParError(1));
      RData.SetPoint(i, PT[i], Fit.GetParameter(2));
      RData.SetPointError(i, 0, Fit.GetParError(2));
   }
   for(int i = 0; i < N; i++)
   {
      TH1D *H = (TH1D *)File.Get(Form("MethodT_%d_0_MC", PT[i]));
      TF1 Fit("Fit", "gaus");
      H->Fit(&Fit);
      GMC.SetPoint(i, PT[i], Fit.GetParameter(1));
      GMC.SetPointError(i, 0, Fit.GetParError(1));
      RMC.SetPoint(i, PT[i], Fit.GetParameter(2));
      RMC.SetPointError(i, 0, Fit.GetParError(2));
   }
   for(int i = 0; i < N; i++)
   {
      double x, y1, y2, ey1, ey2;
      GData.GetPoint(i, x, y1);
      GMC.GetPoint(i, x, y2);
      ey1 = GData.GetErrorY(i);
      ey2 = GMC.GetErrorY(i);

      double r = y1 / y2;
      double er = r * sqrt(ey1 * ey1 / y1 / y1 + ey2 * ey2 / y2 / y2);

      GRatio.SetPoint(i, x, r);
      GRatio.SetPointError(i, 0, er);
   }
   for(int i = 0; i < N; i++)
   {
      double x, y1, y2, ey1, ey2;
      RData.GetPoint(i, x, y1);
      RMC.GetPoint(i, x, y2);
      ey1 = RData.GetErrorY(i);
      ey2 = RMC.GetErrorY(i);

      double r = y1 / y2;
      double er = r * sqrt(ey1 * ey1 / y1 / y1 + ey2 * ey2 / y2 / y2);

      RRatio.SetPoint(i, x, r);
      RRatio.SetPointError(i, 0, er);
   }

   GRatio.Fit("pol3");
   RRatio.Fit("pol3");

   File.Close();

   TH2D HScale("HScale", ";;", 1000, 30, 220, 1000, 0.0, 2.0);
   TH2D HWidth("HWidth", ";;", 1000, 30, 220, 1000, 0.0, 2.0);
   TH2D HP0R0("HP0R0", ";Scale;Resolution", 200, 0.5, 1.5, 200, 0.5, 2.0);
   TH2D HP1R1("HP1R1", ";Scale Slope;Resolution Slope", 200, -0.02, 0.02, 200, -0.02, 0.02);
   HScale.SetStats(0);
   HWidth.SetStats(0);
   HP0R0.SetStats(0);
   HP1R1.SetStats(0);

   TFile File2("multidimfit.root");
   RooFitResult *FitResult = (RooFitResult *)File2.Get("fit_mdf");

   for(int i = 0; i < 1000000; i++)
   {
      RooArgList L = FitResult->randomizePars();

      double P0 = ((RooRealVar *)L.at(16))->getVal();
      double P1 = ((RooRealVar *)L.at(17))->getVal();
      double P2 = ((RooRealVar *)L.at(18))->getVal();
      double P3 = ((RooRealVar *)L.at(19))->getVal();
      double R0 = ((RooRealVar *)L.at(20))->getVal();
      double R1 = ((RooRealVar *)L.at(21))->getVal();
      double R2 = ((RooRealVar *)L.at(22))->getVal();
      double R3 = ((RooRealVar *)L.at(23))->getVal();

      for(int j = 1; j <= HScale.GetNbinsX(); j++)
      {
         double PT = HScale.GetXaxis()->GetBinCenter(j);
         double R = P0 + P1 * PT + P2 * PT * PT + P3 * PT * PT * PT;
         HScale.Fill(PT, R);
      }
      for(int j = 1; j <= HWidth.GetNbinsX(); j++)
      {
         double PT = HWidth.GetXaxis()->GetBinCenter(j);
         double R = R0 + R1 * PT + R2 * PT * PT + R3 * PT * PT * PT;
         HWidth.Fill(PT, R);
      }

      HP0R0.Fill(P0, R0);
      HP1R1.Fill(P1, R1);
   }

   File2.Close();

   PdfFileHelper PdfFile("SimpleFit.pdf");
   PdfFile.AddTextPage("Test test test");

   PdfFile.AddPlot(GData, "ap");
   PdfFile.AddPlot(GMC, "ap");
   PdfFile.AddPlot(RData, "ap");
   PdfFile.AddPlot(RMC, "ap");

   TF1 Fit("yay", "pol3", 40, 220);
   Fit.SetParameters(0.98248, 2.5009e-3, -3.39e-5, 9.784e-8);
   Fit.SetLineColor(kBlue);
   TF1 FitR("yayR", "pol3", 40, 220);
   FitR.SetParameters(1.2706, -0.0069676, 6.4457e-5, -1.5446e-7);
   FitR.SetLineColor(kBlue);

   TF1 Dummy("Dummy", "pol1", 40, 220);
   
   TCanvas C;

   GRatio.Draw("ap");
   HScale.Draw("col same");
   GRatio.Draw("p");
   Fit.Draw("same");

   GRatio.GetXaxis()->SetTitle("Jet P_{T}");
   GRatio.GetYaxis()->SetTitle("Data / MC");
   GRatio.GetYaxis()->SetRangeUser(0.0, 1.5);

   TLegend Legend(0.15, 0.15, 0.45, 0.45);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&GRatio, "Ratio", "pl");
   Legend.AddEntry(&Dummy, "Simple pol3", "l");
   Legend.AddEntry(&Fit, "From combine", "l");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   RRatio.Draw("ap");
   HWidth.Draw("col same");
   RRatio.Draw("p");
   FitR.Draw("same");
   
   RRatio.GetXaxis()->SetTitle("Jet P_{T}");
   RRatio.GetYaxis()->SetTitle("Data / MC (width)");
   RRatio.GetYaxis()->SetRangeUser(0.0, 2.0);

   Legend.Draw();

   PdfFile.AddCanvas(C);

   PdfFile.AddPlot(HP0R0, "colz");
   PdfFile.AddPlot(HP1R1, "colz");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}









