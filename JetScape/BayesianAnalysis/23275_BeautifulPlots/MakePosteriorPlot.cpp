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
#include "TBox.h"
#include "TImage.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

#define NCOLOR 100

int main(int argc, char *argv[]);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
void Set2DHistogram(TH2D *H);
void SetGraph(TGraphErrors *G, bool Central);
void SetMedianGraph(TGraphErrors *G, bool Central);
void Transcribe(TSpline3 *L, TGraphErrors *G, double MinX, double MaxX);
void ColorPlot(TH2D *H1, TH2D *H2, int Colors[NCOLOR][NCOLOR]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName       = CL.Get("file");
   bool IsPrior          = CL.GetBool("prior", false);
   string Output         = CL.Get("output");
   vector<double> World  =
      CL.GetDoubleVector("world", vector<double>({0, 100, 0, 1.5, 0, 100, 0, 1.5, 0, 100, 0, 1.5}));

   for(int i = 0; i < 12; i++)
      cout << World[i] << endl;

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
   TPad PadL("PadL", "", PadX0 + PadX * 2.65, PadY0 + PadY * 0.75, PadX0 + PadX * 2.95, PadY0 + PadY * 0.95);

   SetPad(Pad1);
   SetPad(Pad2);
   SetPad(Pad3);
   SetPad(PadL);

   TH2D HWorld1("HWorld1", ";;", 100, World[0], World[1], 100, World[2], World[3]);
   TH2D HWorld2("HWorld2", ";;", 100, World[4], World[5], 100, World[6], World[7]);
   TH2D HWorld3("HWorld3", ";;", 100, World[8], World[9], 100, World[10], World[11]);

   HWorld1.SetStats(0);
   HWorld2.SetStats(0);
   HWorld3.SetStats(0);

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

   double HistMinX0 = H0->GetXaxis()->GetBinLowEdge(1) * 1.000;
   double HistMinX2 = H2->GetXaxis()->GetBinLowEdge(1) * 1.001;
   double HistMinX4 = H4->GetXaxis()->GetBinLowEdge(1) * 1.001;
   double HistMaxX0 = H0->GetXaxis()->GetBinUpEdge(H0->GetNbinsX()) * 0.999;
   double HistMaxX2 = H2->GetXaxis()->GetBinUpEdge(H0->GetNbinsX()) * 0.999;
   double HistMaxX4 = H4->GetXaxis()->GetBinUpEdge(H0->GetNbinsX()) * 1.000;
   double MinY = H0->GetYaxis()->GetBinLowEdge(1);
   double MaxY = H0->GetYaxis()->GetBinUpEdge(H0->GetNbinsY());
   double MinX0 = World[0] * 1.000; 
   double MinX2 = World[4] * 1.001;
   double MinX4 = World[8] * 1.001;
   double MaxX0 = World[1] * 0.999;
   double MaxX2 = World[5] * 0.999;
   double MaxX4 = World[9] * 0.999;

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

   TGraphErrors M0;   Transcribe(MS0, &M0, HistMinX0, HistMaxX0);
   TGraphErrors M1;   Transcribe(MS1, &M1, HistMinX0, HistMaxX0);
   TGraphErrors M2;   Transcribe(MS2, &M2, HistMinX2, HistMaxX2);
   TGraphErrors M3;   Transcribe(MS3, &M3, HistMinX2, HistMaxX2);
   TGraphErrors M4;   Transcribe(MS4, &M4, HistMinX4, HistMaxX4);
   TGraphErrors M5;   Transcribe(MS5, &M5, HistMinX4, HistMaxX4);

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
   if(IsPrior == false)   Legend1.AddEntry(&ML, "Median", "l");
   else                   Legend1.AddEntry("", "", "");

   TLegend Legend2(0.075, 0.575, 0.375, 0.775);
   Legend2.SetBorderSize(0);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.060);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(D2, "0-5% Centrality", "plf");
   Legend2.AddEntry(D3, "30-40% Centrality", "plf");
   if(IsPrior == false)   Legend2.AddEntry(&ML, "Median", "l");
   else                   Legend2.AddEntry("", "", "");

   TLegend Legend3(0.075, 0.575, 0.375, 0.775);
   Legend3.SetBorderSize(0);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.060);
   Legend3.SetFillStyle(0);
   Legend3.AddEntry(D4, "0-10% Centrality", "plf");
   Legend3.AddEntry(D5, "30-50% Centrality", "plf");
   if(IsPrior == false)   Legend3.AddEntry(&ML, "Median", "l");
   else                   Legend3.AddEntry("", "", "");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextSize(0.060);
   Latex.SetTextFont(42);
   Latex.SetTextAlign(22);

   Latex.SetTextAngle(90);
   Latex.DrawLatex(PadX0 * 0.3, PadY0 + PadY * 0.5, "R_{AA}");
   Latex.SetTextAngle(0);
   Latex.DrawLatex(PadX0 + PadX * 0.5, PadY0 * 0.3, "p_{T} (GeV/c)");
   Latex.DrawLatex(PadX0 + PadX * 1.5, PadY0 * 0.3, "p_{T} (GeV/c)");
   Latex.DrawLatex(PadX0 + PadX * 2.5, PadY0 * 0.3, "p_{T} (GeV/c)");

   Latex.SetTextAlign(33);
   Latex.DrawLatex(PadX0 + PadX * 3, PadY0 + PadY + PadTop * 0.5, "#font[62]{}");

   TExec Exe1("Exe1", "double S1[3] = {0.000, 0.200, 1.000}; double R1[3] = {1.000, 0.300, 0.200}; double G1[3] = {1.000, 1.000, 1.000}; double B1[3] = {1.000, 1.000, 1.000}; TColor::CreateGradientColorTable(3, S1, R1, G1, B1, 99, 1.0);");
   TExec Exe2("Exe2", "double S2[3] = {0.000, 0.200, 1.000}; double R2[3] = {1.000, 1.000, 1.000}; double G2[3] = {1.000, 0.300, 0.200}; double B2[3] = {1.000, 0.300, 0.200}; TColor::CreateGradientColorTable(3, S2, R2, G2, B2, 99, 0.4);");

   int Colors[NCOLOR][NCOLOR];
   for(int i = 0; i < NCOLOR; i++)
   {
      for(int j = 0; j < NCOLOR; j++)
      {
         Colors[i][j] = TColor::GetFreeColorIndex();
         new TColor(Colors[i][j], 1.0 - (double)i / NCOLOR, 1.0 - (double)j / NCOLOR, 1.0 - (double)j / NCOLOR);
      }
   }

   Pad1.cd();
   HWorld1.Draw("axis");
   ColorPlot(H0, H1, Colors);
   // Exe1.Draw();
   // H0->Draw("col same");
   // Exe2.Draw();
   // H1->Draw("col same");
   if(IsPrior == false)   M0.Draw("l");
   if(IsPrior == false)   M1.Draw("l");
   D0->Draw("p");
   D1->Draw("p");
   S0->Draw("[]");
   S1->Draw("[]");
   HWorld1.Draw("axis same");
   Legend1.Draw();

   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.075, 0.925, ("AuAu 200 GeV " + TypeString).c_str());
   Latex.DrawLatex(0.075, 0.850, "Data from PHENIX");

   Pad2.cd();
   HWorld2.Draw("axis");
   ColorPlot(H2, H3, Colors);
   // Exe1.Draw();
   // H2->Draw("col same");
   // Exe2.Draw();
   // H3->Draw("col same");
   if(IsPrior == false)   M2.Draw("l");
   if(IsPrior == false)   M3.Draw("l");
   D2->Draw("p");
   D3->Draw("p");
   S2->Draw("[]");
   S3->Draw("[]");
   HWorld2.Draw("axis same");
   Legend2.Draw();
   
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.075, 0.925, ("PbPb 2.76 TeV " + TypeString).c_str());
   Latex.DrawLatex(0.075, 0.850, "Data from ATLAS");

   Pad3.cd();
   HWorld3.Draw("axis");
   ColorPlot(H4, H5, Colors);
   // Exe1.Draw();
   // H4->Draw("col same");
   // Exe2.Draw();
   // H5->Draw("col same");
   if(IsPrior == false)   M4.Draw("l");
   if(IsPrior == false)   M5.Draw("l");
   D4->Draw("p");
   D5->Draw("p");
   S4->Draw("[]");
   S5->Draw("[]");
   HWorld3.Draw("axis same");
   Legend3.Draw();
   
   Latex.SetTextAlign(13);
   Latex.DrawLatex(0.075, 0.925, ("PbPb 5.02 TeV " + TypeString).c_str());
   Latex.DrawLatex(0.075, 0.850, "Data from CMS");

   PadL.cd();
   TImage *Logo = (TImage *)TImage::Open("JetscapeLogo.jpg");
   Logo->Draw("");

   Canvas.SaveAs((Output + ".eps").c_str());
   Canvas.SaveAs((Output + ".png").c_str());

   return 0;
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
   
   for(int iX = 1; iX <= H->GetNbinsX(); iX++)
      for(int iY = 1; iY <= H->GetNbinsX(); iY++)
         H->SetBinContent(iX, iY, H->GetBinContent(iX, iY) + 1e-10);
}

void SetGraph(TGraphErrors *G, bool Central)
{
   G->SetLineWidth(2);

   if(Central)
   {
      G->SetMarkerStyle(23);
      G->SetMarkerSize(2.0);
      G->SetLineColor(kBlue + 3);
      G->SetMarkerColor(kBlue + 3);
      G->SetFillColor(kCyan);
   }
   else
   {
      G->SetMarkerStyle(22);
      G->SetMarkerSize(2.0);
      G->SetLineColor(kRed + 3);
      G->SetMarkerColor(kRed + 3);
      G->SetFillColor(kPink);
   }

   for(int i = 0; i < G->GetN(); i++)
   {
      double X, Y;
      G->GetPoint(i, X, Y);

      if(Central == true)
         X = X * 1.0025;
      else
         X = X * 0.9975;

      G->SetPoint(i, X, Y);
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

void ColorPlot(TH2D *H1, TH2D *H2, int Colors[NCOLOR][NCOLOR])
{
   double H1Max = 0;
   double H2Max = 0;
   
   for(int iX = 1; iX <= (int)H1->GetNbinsX(); iX++)
      for(int iY = 1; iY <= (int)H1->GetNbinsY(); iY++)
         if(H1Max < H1->GetBinContent(iX, iY))
            H1Max = H1->GetBinContent(iX, iY);
   for(int iX = 1; iX <= (int)H2->GetNbinsX(); iX++)
      for(int iY = 1; iY <= (int)H2->GetNbinsY(); iY++)
         if(H2Max < H2->GetBinContent(iX, iY))
            H2Max = H2->GetBinContent(iX, iY);

   TBox Box;

   for(int iX = 1; iX <= (int)H1->GetNbinsX(); iX++)
   {
      double XL = H1->GetXaxis()->GetBinLowEdge(iX);
      double XH = H1->GetXaxis()->GetBinUpEdge(iX);

      for(int iY = 1; iY <= (int)H1->GetNbinsY(); iY++)
      {
         double YL = H1->GetYaxis()->GetBinLowEdge(iY);
         double YH = H1->GetYaxis()->GetBinUpEdge(iY);

         int c1 = H1->GetBinContent(iX, iY) / H1Max * NCOLOR;
         int c2 = H2->GetBinContent(iX, iY) / H2Max * NCOLOR;

         if(c1 >= NCOLOR)  c1 = NCOLOR - 1;
         if(c2 >= NCOLOR)  c2 = NCOLOR - 1;

         if(c1 == 0 && c2 == 0)   // no need to plot white block
            continue;

         // cout << iX << " " << iY << endl;
         // cout << H1->GetBinContent(iX, iY) << " " << H1Max << " " << c1 << endl;
         // cout << H2->GetBinContent(iX, iY) << " " << H2Max << " " << c2 << endl;

         Box.SetFillColor(Colors[c1][c2]);
         Box.SetLineWidth(0);
         Box.DrawBox(XL, YL, XH, YH);
      }
   }
}

