#include <iostream>
using namespace std;

#include "TSpline.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH2D.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TGaxis.h"
#include "TExec.h"
#include "TLatex.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
void Set2DHistogram(TH2D *H);
void SetGraph(TGraphErrors *G, bool Central);
void SetMedianGraph(TGraphErrors *G, bool Central);
void Transcribe(TSpline3 *L, TGraphErrors *G, double MinX, double MaxX);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName       = CL.Get("file");
   bool IsPrior          = CL.GetBool("prior", false);
   string OutputFileName = CL.Get("output");

   string Type = IsPrior ? "Prior" : "Posterior";
   string TypeString = IsPrior ? "Design" : "Posterior";

   TFile File(FileName.c_str());

   double PaddingLeft = 100;
   double PaddingRight = 50;
   double PaddingTop = 75;
   double PaddingBottom = 100;

   double PanelWidth = 500;
   double PanelHeight = 500;

   double CanvasWidth = PaddingLeft + PaddingRight + PanelWidth * 3;
   double CanvasHeight = PaddingTop + PaddingBottom + PanelHeight;

   double PadX0 = PaddingLeft / CanvasWidth;
   double PadX = PanelWidth / CanvasWidth;
   double PadY0 = PaddingBottom / CanvasHeight;
   double PadY = PanelHeight / CanvasHeight;
   double PadTop = PaddingTop / CanvasHeight;

   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TPad Pad1("Pad1", "", PadX0 + PadX * 0, PadY0, PadX0 + PadX * 1, PadY0 + PadY, 0);
   TPad Pad2("Pad1", "", PadX0 + PadX * 1, PadY0, PadX0 + PadX * 2, PadY0 + PadY, 0);
   TPad Pad3("Pad1", "", PadX0 + PadX * 2, PadY0, PadX0 + PadX * 3, PadY0 + PadY, 0);

   SetPad(Pad1);
   SetPad(Pad2);
   SetPad(Pad3);

   TH2D *H0 = (TH2D *)File.Get(Form("HRAA%s%d", Type.c_str(), 0));
   TH2D *H1 = (TH2D *)File.Get(Form("HRAA%s%d", Type.c_str(), 1));
   TH2D *H2 = (TH2D *)File.Get(Form("HRAA%s%d", Type.c_str(), 2));
   TH2D *H3 = (TH2D *)File.Get(Form("HRAA%s%d", Type.c_str(), 3));
   TH2D *H4 = (TH2D *)File.Get(Form("HRAA%s%d", Type.c_str(), 4));
   TH2D *H5 = (TH2D *)File.Get(Form("HRAA%s%d", Type.c_str(), 5));

   Set2DHistogram(H0);
   Set2DHistogram(H1);
   Set2DHistogram(H2);
   Set2DHistogram(H3);
   Set2DHistogram(H4);
   Set2DHistogram(H5);

   double MinX0 = H0->GetXaxis()->GetBinLowEdge(1) * 1.000;
   double MinX2 = H2->GetXaxis()->GetBinLowEdge(1) * 1.001;
   double MinX4 = H4->GetXaxis()->GetBinLowEdge(1) * 1.001;
   double MaxX0 = H0->GetXaxis()->GetBinUpEdge(H0->GetNbinsX()) * 0.999;
   double MaxX2 = H2->GetXaxis()->GetBinUpEdge(H0->GetNbinsX()) * 0.999;
   double MaxX4 = H4->GetXaxis()->GetBinUpEdge(H0->GetNbinsX()) * 1.000;
   double MinY = H0->GetYaxis()->GetBinLowEdge(1);
   double MaxY = H0->GetYaxis()->GetBinUpEdge(H0->GetNbinsY());

   TGaxis AxisY(PadX0, PadY0, PadX0, PadY0 + PadY, MinY, MaxY, 510, "S");
   TGaxis AxisX1(PadX0 + PadX * 0, PadY0, PadX0 + PadX * 1, PadY0, MinX0, MaxX0, 510, "S");
   TGaxis AxisX2(PadX0 + PadX * 1, PadY0, PadX0 + PadX * 2, PadY0, MinX2, MaxX2, 510, "S");
   TGaxis AxisX3(PadX0 + PadX * 2, PadY0, PadX0 + PadX * 3, PadY0, MinX4, MaxX4, 510, "S");

   SetAxis(AxisY);
   SetAxis(AxisX1);
   SetAxis(AxisX2);
   SetAxis(AxisX3);

   TGraphErrors *D0 = (TGraphErrors *)File.Get("Data0");
   TGraphErrors *D1 = (TGraphErrors *)File.Get("Data1");
   TGraphErrors *D2 = (TGraphErrors *)File.Get("Data2");
   TGraphErrors *D3 = (TGraphErrors *)File.Get("Data3");
   TGraphErrors *D4 = (TGraphErrors *)File.Get("Data4");
   TGraphErrors *D5 = (TGraphErrors *)File.Get("Data5");
   TGraphErrors *S0 = (TGraphErrors *)File.Get("DataS0");
   TGraphErrors *S1 = (TGraphErrors *)File.Get("DataS1");
   TGraphErrors *S2 = (TGraphErrors *)File.Get("DataS2");
   TGraphErrors *S3 = (TGraphErrors *)File.Get("DataS3");
   TGraphErrors *S4 = (TGraphErrors *)File.Get("DataS4");
   TGraphErrors *S5 = (TGraphErrors *)File.Get("DataS5");

   SetGraph(D0, true);
   SetGraph(D1, false);
   SetGraph(D2, true);
   SetGraph(D3, false);
   SetGraph(D4, true);
   SetGraph(D5, false);
   SetGraph(S0, true);
   SetGraph(S1, false);
   SetGraph(S2, true);
   SetGraph(S3, false);
   SetGraph(S4, true);
   SetGraph(S5, false);

   TSpline3 *MS0 = (TSpline3 *)File.Get("Median0");
   TSpline3 *MS1 = (TSpline3 *)File.Get("Median1");
   TSpline3 *MS2 = (TSpline3 *)File.Get("Median2");
   TSpline3 *MS3 = (TSpline3 *)File.Get("Median3");
   TSpline3 *MS4 = (TSpline3 *)File.Get("Median4");
   TSpline3 *MS5 = (TSpline3 *)File.Get("Median5");

   TGraphErrors M0;   Transcribe(MS0, &M0, MinX0, MaxX0);
   TGraphErrors M1;   Transcribe(MS1, &M1, MinX0, MaxX0);
   TGraphErrors M2;   Transcribe(MS2, &M2, MinX2, MaxX2);
   TGraphErrors M3;   Transcribe(MS3, &M3, MinX2, MaxX2);
   TGraphErrors M4;   Transcribe(MS4, &M4, MinX4, MaxX4);
   TGraphErrors M5;   Transcribe(MS5, &M5, MinX4, MaxX4);

   SetMedianGraph(&M0, true);
   SetMedianGraph(&M1, false);
   SetMedianGraph(&M2, true);
   SetMedianGraph(&M3, false);
   SetMedianGraph(&M4, true);
   SetMedianGraph(&M5, false);

   TGraphErrors ML;   // for legend
   SetMedianGraph(&ML, true);
   ML.SetLineColor(kBlack);

   TLegend Legend1(0.075, 0.575, 0.375, 0.775);
   Legend1.SetBorderSize(0);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.060);
   Legend1.SetFillStyle(0);
   Legend1.AddEntry(D0, "0-10% Centrality", "plf");
   Legend1.AddEntry(D1, "40-50% Centrality", "plf");
   if(IsPrior == false)   Legend1.AddEntry(&ML, "Median prediction", "l");
   else                   Legend1.AddEntry("", "", "");

   TLegend Legend2(0.075, 0.575, 0.375, 0.775);
   Legend2.SetBorderSize(0);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.060);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(D2, "0-5% Centrality", "plf");
   Legend2.AddEntry(D3, "30-40% Centrality", "plf");
   if(IsPrior == false)   Legend2.AddEntry(&ML, "Median prediction", "l");
   else                   Legend2.AddEntry("", "", "");

   TLegend Legend3(0.075, 0.575, 0.375, 0.775);
   Legend3.SetBorderSize(0);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.060);
   Legend3.SetFillStyle(0);
   Legend3.AddEntry(D4, "0-10% Centrality", "plf");
   Legend3.AddEntry(D5, "30-50% Centrality", "plf");
   if(IsPrior == false)   Legend3.AddEntry(&ML, "Median prediction", "l");
   else                   Legend3.AddEntry("", "", "");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextSize(0.060);
   Latex.SetTextFont(42);
   Latex.SetTextAlign(22);

   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.3, PadY0 + PadY * 0.5, "R_{AA}");
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadX * 0.5, PadY0 * 0.3, "p_{T} (GeV)");
   Latex.DrawLatex(PadX0 + PadX * 1.5, PadY0 * 0.3, "p_{T} (GeV)");
   Latex.DrawLatex(PadX0 + PadX * 2.5, PadY0 * 0.3, "p_{T} (GeV)");

   Latex.SetTextAlign(33);
   Latex.DrawLatex(PadX0 + PadX * 3, PadY0 + PadY + PadTop * 0.5, "#font[62]{JETSCAPE} Preliminary");

   TExec Exe1("Exe1", "double S1[2] = {0.000, 1.000}; double R1[2] = {1.000, 0.200}; double G1[2] = {1.000, 1.000}; double B1[2] = {1.000, 1.000}; TColor::CreateGradientColorTable(2, S1, R1, G1, B1, 99, 0.5);");
   TExec Exe2("Exe2", "double S2[2] = {0.000, 1.000}; double R2[2] = {1.000, 1.000}; double G2[2] = {1.000, 0.200}; double B2[2] = {1.000, 0.200}; TColor::CreateGradientColorTable(2, S2, R2, G2, B2, 99, 0.5);");

   Pad1.cd();
   H0->Draw("axis");
   Exe1.Draw();
   H0->Draw("col same");
   Exe2.Draw();
   H1->Draw("col same");
   if(IsPrior == false)   M0.Draw("l");
   if(IsPrior == false)   M1.Draw("l");
   D0->Draw("p");
   D1->Draw("p");
   S0->Draw("[]");
   S1->Draw("[]");
   H0->Draw("axis same");
   Legend1.Draw();

   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.075, 0.925, ("AuAu 200 GeV " + TypeString).c_str());
   Latex.DrawLatex(0.075, 0.850, "Data from PHENIX");

   Pad2.cd();
   H2->Draw("axis");
   Exe1.Draw();
   H2->Draw("col same");
   Exe2.Draw();
   H3->Draw("col same");
   if(IsPrior == false)   M2.Draw("l");
   if(IsPrior == false)   M3.Draw("l");
   D2->Draw("p");
   D3->Draw("p");
   S2->Draw("[]");
   S3->Draw("[]");
   H2->Draw("axis same");
   Legend2.Draw();
   
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.075, 0.925, ("PbPb 2.76 TeV " + TypeString).c_str());
   Latex.DrawLatex(0.075, 0.850, "Data from ATLAS");

   Pad3.cd();
   H4->Draw("axis");
   Exe1.Draw();
   H4->Draw("col same");
   Exe2.Draw();
   H5->Draw("col same");
   if(IsPrior == false)   M4.Draw("l");
   if(IsPrior == false)   M5.Draw("l");
   D4->Draw("p");
   D5->Draw("p");
   S4->Draw("[]");
   S5->Draw("[]");
   H4->Draw("axis same");
   Legend3.Draw();
   
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.075, 0.925, ("PbPb 5.02 TeV " + TypeString).c_str());
   Latex.DrawLatex(0.075, 0.850, "Data from CMS");

   Canvas.SaveAs(OutputFileName.c_str());
}

void SetPad(TPad &P)
{
   P.SetLeftMargin(0);
   P.SetTopMargin(0);
   P.SetRightMargin(0);
   P.SetBottomMargin(0);
   P.Draw();
}

void SetAxis(TGaxis &A)
{
   A.SetLabelFont(42);
   A.SetLabelSize(0.050);
   A.SetMaxDigits(6);
   A.SetTickLength(0);
   A.Draw();
}

void Set2DHistogram(TH2D *H)
{
   H->SetStats(0);
}

void SetGraph(TGraphErrors *G, bool Central)
{
   G->SetMarkerStyle(20);
   G->SetMarkerSize(1.5);
   G->SetLineWidth(2);

   if(Central)
   {
      G->SetLineColor(kBlue + 3);
      G->SetMarkerColor(kBlue + 3);
      G->SetFillColor(kCyan);
   }
   else
   {
      G->SetLineColor(kRed + 3);
      G->SetMarkerColor(kRed + 3);
      G->SetFillColor(kPink);
   }
}

void SetMedianGraph(TGraphErrors *G, bool Central)
{
   SetGraph(G, Central);
   G->SetLineStyle(kDashed);
}

void Transcribe(TSpline3 *L, TGraphErrors *G, double MinX, double MaxX)
{
   double DeltaX = MaxX - MinX;
   MinX = MinX - DeltaX * 0.1;
   MaxX = MaxX + DeltaX * 0.1;

   int N = 1000;

   for(int i = 0; i < N; i++)
   {
      double X = MinX + (MaxX - MinX) / N * (i + 0.5);
      double Y = L->Eval(X);
      G->SetPoint(i, X, Y);
   }
}


