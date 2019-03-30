#include <iostream>
#include <vector>
using namespace std;

#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   PdfFileHelper PdfFile("DJetResult.pdf");
   PdfFile.AddTextPage("DJet plots");

   vector<string> Info(20);
   Info[0] = "Goal: add more gen-plots for DJet analysis";
   Info[1] = "";
   Info[2] = "Herwig";
   Info[3] = "   CH2 tune, NNPDF31_NNLO, alphas = 0.118";
   Info[4] = "";
   Info[5] = "Pythia8 (CM1)";
   Info[6] = "";
   Info[7] = "Herwig and Pythia8 (CM1) are pure gen-level";
   Info[8] = "   only stat error shown";
   Info[9] = "PbPb, pp and Pythia8 curves are eye-balled";
   Info[10] = "   no errors plotted";
   Info[11] = "";
   Info[12] = "No error on ratio plots";
   PdfFile.AddTextPage(Info);

   int BinCount = 4;
   double BinX[] = {0.00, 0.05, 0.10, 0.30, 0.50};
   double PbPb0[] = {3.22, 5.1, 2.9, 1.6};
   double PP0[] = {4.65, 6.2, 2.2, 0.87};
   double Pythia0[] = {3.68, 5.4, 2.7, 1.15};
   double PbPb1[] = {14.5, 3.2, 0.32, 0.043};
   double PP1[] = {15, 3, 0.28, 0.054};
   double Pythia1[] = {15, 2.8, 0.27, 0.047};

   TGraphErrors GPbPb0, GPP0, GPythia0, GHerwig0, GPythiaCM10, GQPythiaVac0, GQPythiaMed0;
   TGraphErrors GPbPb1, GPP1, GPythia1, GHerwig1, GPythiaCM11, GQPythiaVac1, GQPythiaMed1;
   TGraphErrors RPbPb0, RPP0, RPythia0, RHerwig0, RPythiaCM10, RQPythiaVac0, RQPythiaMed0;
   TGraphErrors RPbPb1, RPP1, RPythia1, RHerwig1, RPythiaCM11, RQPythiaVac1, RQPythiaMed1;

   TFile FHerwig("BigRun.root");
   TFile FPythiaCM1("BigPythiaRun.root");
   TFile FQPythiaVac("QPythiaVac.root");
   TFile FQPythiaMed("QPythiaQHat1.root");

   TH1D *HHerwig0 = (TH1D *)FHerwig.Get("HMatchedDRBin0Rebin");
   TH1D *HHerwig1 = (TH1D *)FHerwig.Get("HMatchedDRBin1Rebin");
   TH1D *HPythiaCM10 = (TH1D *)FPythiaCM1.Get("HMatchedDRBin0Rebin");
   TH1D *HPythiaCM11 = (TH1D *)FPythiaCM1.Get("HMatchedDRBin1Rebin");
   TH1D *HQPythiaVac0 = (TH1D *)FQPythiaVac.Get("HMatchedDRBin0Rebin");
   TH1D *HQPythiaVac1 = (TH1D *)FQPythiaVac.Get("HMatchedDRBin1Rebin");
   TH1D *HQPythiaMed0 = (TH1D *)FQPythiaMed.Get("HMatchedDRBin0Rebin");
   TH1D *HQPythiaMed1 = (TH1D *)FQPythiaMed.Get("HMatchedDRBin1Rebin");

   for(int i = 0; i < BinCount; i++)
   {
      GPbPb0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, PbPb0[i]);
      GPP0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, PP0[i]);
      GPythia0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, Pythia0[i]);
      GHerwig0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HHerwig0->GetBinContent(i + 1));
      GPythiaCM10.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HPythiaCM10->GetBinContent(i + 1));
      GQPythiaVac0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HQPythiaVac0->GetBinContent(i + 1));
      GQPythiaMed0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HQPythiaMed0->GetBinContent(i + 1));
      GPbPb1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, PbPb1[i]);
      GPP1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, PP1[i]);
      GPythia1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, Pythia1[i]);
      GHerwig1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HHerwig1->GetBinContent(i + 1));
      GPythiaCM11.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HPythiaCM11->GetBinContent(i + 1));
      GQPythiaVac1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HQPythiaVac1->GetBinContent(i + 1));
      GQPythiaMed1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HQPythiaMed1->GetBinContent(i + 1));
      
      RPbPb0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, PbPb0[i] / PP0[i]);
      RPP0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, PP0[i] / PP0[i]);
      RPythia0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, Pythia0[i] / PP0[i]);
      RHerwig0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HHerwig0->GetBinContent(i + 1) / PP0[i]);
      RPythiaCM10.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HPythiaCM10->GetBinContent(i + 1) / PP0[i]);
      RQPythiaVac0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HQPythiaVac0->GetBinContent(i + 1) / PP0[i]);
      RQPythiaMed0.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HQPythiaMed0->GetBinContent(i + 1) / PP0[i]);
      RPbPb1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, PbPb1[i] / PP1[i]);
      RPP1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, PP1[i] / PP1[i]);
      RPythia1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, Pythia1[i] / PP1[i]);
      RHerwig1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HHerwig1->GetBinContent(i + 1) / PP1[i]);
      RPythiaCM11.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HPythiaCM11->GetBinContent(i + 1) / PP1[i]);
      RQPythiaVac1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HQPythiaVac1->GetBinContent(i + 1) / PP1[i]);
      RQPythiaMed1.SetPoint(i, (BinX[i+1] + BinX[i]) / 2, HQPythiaMed1->GetBinContent(i + 1) / PP1[i]);

      GPbPb0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      GPP0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      GPythia0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      GHerwig0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, HHerwig0->GetBinError(i + 1));
      GPythiaCM10.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, HPythiaCM10->GetBinError(i + 1));
      GQPythiaVac0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, HQPythiaVac0->GetBinError(i + 1));
      GQPythiaMed0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, HQPythiaMed0->GetBinError(i + 1));
      GPbPb1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      GPP1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      GPythia1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      GHerwig1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, HHerwig1->GetBinError(i + 1));
      GPythiaCM11.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, HPythiaCM11->GetBinError(i + 1));
      GQPythiaVac1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, HQPythiaVac1->GetBinError(i + 1));
      GQPythiaMed1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, HQPythiaMed1->GetBinError(i + 1));

      RPbPb0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RPP0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RPythia0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RHerwig0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RPythiaCM10.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RQPythiaVac0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RQPythiaMed0.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RPbPb1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RPP1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RPythia1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RHerwig1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RPythiaCM11.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RQPythiaVac1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
      RQPythiaMed1.SetPointError(i, (BinX[i+1] - BinX[i]) / 2, 0);
   }

   FHerwig.Close();
   FPythiaCM1.Close();
   FQPythiaVac.Close();
   FQPythiaMed.Close();

   GPbPb0.SetMarkerColor(kRed + 1);
   GPbPb0.SetMarkerStyle(21);
   GPbPb0.SetMarkerSize(2);
   GPbPb0.SetLineColor(kRed + 1);
   GPbPb0.SetLineWidth(2);
   GPP0.SetMarkerColor(kAzure + 1);
   GPP0.SetMarkerStyle(20);
   GPP0.SetMarkerSize(2);
   GPP0.SetLineColor(kAzure + 1);
   GPP0.SetLineWidth(2);
   GPythia0.SetMarkerColor(kGreen + 2);
   GPythia0.SetMarkerStyle(34);
   GPythia0.SetMarkerSize(2);
   GPythia0.SetLineColor(kGreen + 2);
   GPythia0.SetLineWidth(2);
   GHerwig0.SetMarkerColor(kMagenta - 3);
   GHerwig0.SetMarkerStyle(33);
   GHerwig0.SetMarkerSize(2);
   GHerwig0.SetLineColor(kMagenta - 3);
   GHerwig0.SetLineWidth(2);
   GPythiaCM10.SetMarkerColor(kYellow + 1);
   GPythiaCM10.SetMarkerStyle(29);
   GPythiaCM10.SetMarkerSize(2);
   GPythiaCM10.SetLineColor(kYellow + 1);
   GPythiaCM10.SetLineWidth(2);
   GQPythiaVac0.SetMarkerColor(kCyan);
   GQPythiaVac0.SetMarkerStyle(29);
   GQPythiaVac0.SetMarkerSize(2);
   GQPythiaVac0.SetLineColor(kCyan);
   GQPythiaVac0.SetLineWidth(2);
   GQPythiaMed0.SetMarkerColor(kGreen);
   GQPythiaMed0.SetMarkerStyle(29);
   GQPythiaMed0.SetMarkerSize(2);
   GQPythiaMed0.SetLineColor(kGreen);
   GQPythiaMed0.SetLineWidth(2);
   GPbPb1.SetMarkerColor(kRed + 1);
   GPbPb1.SetMarkerStyle(21);
   GPbPb1.SetMarkerSize(2);
   GPbPb1.SetLineColor(kRed + 1);
   GPbPb1.SetLineWidth(2);
   GPP1.SetMarkerColor(kAzure + 1);
   GPP1.SetMarkerStyle(20);
   GPP1.SetMarkerSize(2);
   GPP1.SetLineColor(kAzure + 1);
   GPP1.SetLineWidth(2);
   GPythia1.SetMarkerColor(kGreen + 2);
   GPythia1.SetMarkerStyle(34);
   GPythia1.SetMarkerSize(2);
   GPythia1.SetLineColor(kGreen + 2);
   GPythia1.SetLineWidth(2);
   GHerwig1.SetMarkerColor(kMagenta - 3);
   GHerwig1.SetMarkerStyle(33);
   GHerwig1.SetMarkerSize(2);
   GHerwig1.SetLineColor(kMagenta - 3);
   GHerwig1.SetLineWidth(2);
   GPythiaCM11.SetMarkerColor(kYellow + 1);
   GPythiaCM11.SetMarkerStyle(29);
   GPythiaCM11.SetMarkerSize(2);
   GPythiaCM11.SetLineColor(kYellow + 1);
   GPythiaCM11.SetLineWidth(2);
   GQPythiaVac1.SetMarkerColor(kCyan);
   GQPythiaVac1.SetMarkerStyle(29);
   GQPythiaVac1.SetMarkerSize(2);
   GQPythiaVac1.SetLineColor(kCyan);
   GQPythiaVac1.SetLineWidth(2);
   GQPythiaMed1.SetMarkerColor(kGreen);
   GQPythiaMed1.SetMarkerStyle(29);
   GQPythiaMed1.SetMarkerSize(2);
   GQPythiaMed1.SetLineColor(kGreen);
   GQPythiaMed1.SetLineWidth(2);
   RPbPb0.SetMarkerColor(kRed + 1);
   RPbPb0.SetMarkerStyle(21);
   RPbPb0.SetMarkerSize(2);
   RPbPb0.SetLineColor(kRed + 1);
   RPbPb0.SetLineWidth(2);
   RPP0.SetMarkerColor(kAzure + 1);
   RPP0.SetMarkerStyle(20);
   RPP0.SetMarkerSize(2);
   RPP0.SetLineColor(kAzure + 1);
   RPP0.SetLineWidth(2);
   RPythia0.SetMarkerColor(kGreen + 2);
   RPythia0.SetMarkerStyle(34);
   RPythia0.SetMarkerSize(2);
   RPythia0.SetLineColor(kGreen + 2);
   RPythia0.SetLineWidth(2);
   RHerwig0.SetMarkerColor(kMagenta - 3);
   RHerwig0.SetMarkerStyle(33);
   RHerwig0.SetMarkerSize(2);
   RHerwig0.SetLineColor(kMagenta - 3);
   RHerwig0.SetLineWidth(2);
   RPythiaCM10.SetMarkerColor(kYellow + 1);
   RPythiaCM10.SetMarkerStyle(29);
   RPythiaCM10.SetMarkerSize(2);
   RPythiaCM10.SetLineColor(kYellow + 1);
   RPythiaCM10.SetLineWidth(2);
   RQPythiaVac0.SetMarkerColor(kCyan);
   RQPythiaVac0.SetMarkerStyle(29);
   RQPythiaVac0.SetMarkerSize(2);
   RQPythiaVac0.SetLineColor(kCyan);
   RQPythiaVac0.SetLineWidth(2);
   RQPythiaMed0.SetMarkerColor(kGreen);
   RQPythiaMed0.SetMarkerStyle(29);
   RQPythiaMed0.SetMarkerSize(2);
   RQPythiaMed0.SetLineColor(kGreen);
   RQPythiaMed0.SetLineWidth(2);
   RPbPb1.SetMarkerColor(kRed + 1);
   RPbPb1.SetMarkerStyle(21);
   RPbPb1.SetMarkerSize(2);
   RPbPb1.SetLineColor(kRed + 1);
   RPbPb1.SetLineWidth(2);
   RPP1.SetMarkerColor(kAzure + 1);
   RPP1.SetMarkerStyle(20);
   RPP1.SetMarkerSize(2);
   RPP1.SetLineColor(kAzure + 1);
   RPP1.SetLineWidth(2);
   RPythia1.SetMarkerColor(kGreen + 2);
   RPythia1.SetMarkerStyle(34);
   RPythia1.SetMarkerSize(2);
   RPythia1.SetLineColor(kGreen + 2);
   RPythia1.SetLineWidth(2);
   RHerwig1.SetMarkerColor(kMagenta - 3);
   RHerwig1.SetMarkerStyle(33);
   RHerwig1.SetMarkerSize(2);
   RHerwig1.SetLineColor(kMagenta - 3);
   RHerwig1.SetLineWidth(2);
   RPythiaCM11.SetMarkerColor(kYellow + 1);
   RPythiaCM11.SetMarkerStyle(29);
   RPythiaCM11.SetMarkerSize(2);
   RPythiaCM11.SetLineColor(kYellow + 1);
   RPythiaCM11.SetLineWidth(2);
   RQPythiaVac1.SetMarkerColor(kCyan);
   RQPythiaVac1.SetMarkerStyle(29);
   RQPythiaVac1.SetMarkerSize(2);
   RQPythiaVac1.SetLineColor(kCyan);
   RQPythiaVac1.SetLineWidth(2);
   RQPythiaMed1.SetMarkerColor(kGreen);
   RQPythiaMed1.SetMarkerStyle(29);
   RQPythiaMed1.SetMarkerSize(2);
   RQPythiaMed1.SetLineColor(kGreen);
   RQPythiaMed1.SetLineWidth(2);

   TCanvas Canvas;

   TH2D HWorld0("HWorld0", ";r;#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}", 100, 0.00, 0.50, 100, 0.008, 100);
   HWorld0.SetStats(0);
   HWorld0.GetXaxis()->CenterTitle();
   HWorld0.GetYaxis()->CenterTitle();

   HWorld0.Draw("axis");
   GPbPb0.Draw("p");
   GPP0.Draw("p");
   GPythia0.Draw("p");
   GHerwig0.Draw("p");
   GPythiaCM10.Draw("p");
   GQPythiaVac0.Draw("p");
   GQPythiaMed0.Draw("p");

   TLegend Legend0(0.15, 0.2, 0.45, 0.5);
   Legend0.SetTextFont(42);
   Legend0.SetTextSize(0.035);
   Legend0.SetBorderSize(0);
   Legend0.SetFillStyle(0);
   Legend0.AddEntry(&GPbPb0, "PbPb", "p");
   Legend0.AddEntry(&GPP0, "PP", "p");
   Legend0.AddEntry(&GPythia0, "PYTHIA8", "p");
   Legend0.AddEntry(&GHerwig0, "HERWIG (CH2)", "p");
   Legend0.AddEntry(&GPythiaCM10, "PYTHIA8 (CM1)", "p");
   Legend0.AddEntry(&GQPythiaVac0, "QPYTHIA (Vac)", "p");
   Legend0.AddEntry(&GQPythiaMed0, "QPYTHIA (Med)", "p");
   Legend0.Draw();

   Canvas.SetLogy();
   Canvas.SaveAs("Bin0.pdf");
   PdfFile.AddCanvas(Canvas);
   
   TH2D RWorld0("RWorld0", ";r;Ratio to pp", 100, 0.00, 0.50, 100, 0, 2);
   RWorld0.SetStats(0);
   RWorld0.GetXaxis()->CenterTitle();
   RWorld0.GetYaxis()->CenterTitle();

   RWorld0.Draw("axis");
   RPbPb0.Draw("p");
   RPP0.Draw("p");
   RPythia0.Draw("p");
   RHerwig0.Draw("p");
   RPythiaCM10.Draw("p");
   RQPythiaVac0.Draw("p");
   RQPythiaMed0.Draw("p");

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorld1("HWorld1", ";r;#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}", 100, 0.00, 0.50, 100, 0.002, 500);
   HWorld1.SetStats(0);
   HWorld1.GetXaxis()->CenterTitle();
   HWorld1.GetYaxis()->CenterTitle();

   HWorld1.Draw("axis");
   GPbPb1.Draw("p");
   GPP1.Draw("p");
   GPythia1.Draw("p");
   GHerwig1.Draw("p");
   GPythiaCM11.Draw("p");
   GQPythiaVac1.Draw("p");
   GQPythiaMed1.Draw("p");
   
   TLegend Legend1(0.45, 0.5, 0.75, 0.8);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetBorderSize(0);
   Legend1.SetFillStyle(0);
   Legend1.AddEntry(&GPbPb1, "PbPb", "p");
   Legend1.AddEntry(&GPP1, "PP", "p");
   Legend1.AddEntry(&GPythia1, "PYTHIA8", "p");
   Legend1.AddEntry(&GHerwig1, "HERWIG (CH2)", "p");
   Legend1.AddEntry(&GPythiaCM11, "PYTHIA8 (CM1)", "p");
   Legend1.AddEntry(&GQPythiaVac1, "QPYTHIA (Vac)", "p");
   Legend1.AddEntry(&GQPythiaMed1, "QPYTHIA (Med)", "p");
   Legend1.Draw();

   Canvas.SetLogy();
   Canvas.SaveAs("Bin1.pdf");
   PdfFile.AddCanvas(Canvas);

   TH2D RWorld1("RWorld1", ";r;Ratio to pp", 100, 0.00, 0.50, 100, 0, 2);
   RWorld1.SetStats(0);
   RWorld1.GetXaxis()->CenterTitle();
   RWorld1.GetYaxis()->CenterTitle();

   RWorld1.Draw("axis");
   RPbPb1.Draw("p");
   RPP1.Draw("p");
   RPythia1.Draw("p");
   RHerwig1.Draw("p");
   RPythiaCM11.Draw("p");
   RQPythiaVac1.Draw("p");
   RQPythiaMed1.Draw("p");

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




