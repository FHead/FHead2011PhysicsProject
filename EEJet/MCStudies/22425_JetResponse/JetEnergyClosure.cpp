#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
void PlotPTClosure(PdfFileHelper &PdfFile, TTree *Tree,
   double ThetaPIMin, double ThetaPIMax, double PTMin, double PTMax);
void PlotThetaClosure(PdfFileHelper &PdfFile, TTree *Tree,
   double ThetaPIMin, double ThetaPIMax, double PTMin, double PTMax);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName = CL.Get("Name", "AllMatched.root");
   string OutputFileName = CL.Get("Output", "JECClosure.pdf");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Jet energy closure plots from MC");

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("MatchedTree");

   PlotPTClosure(PdfFile, Tree, 0.00, 0.10, 0, 15);
   PlotPTClosure(PdfFile, Tree, 0.10, 0.15, 0, 20);
   PlotPTClosure(PdfFile, Tree, 0.15, 0.20, 0, 30);
   PlotPTClosure(PdfFile, Tree, 0.20, 0.25, 0, 35);
   PlotPTClosure(PdfFile, Tree, 0.25, 0.30, 0, 40);
   PlotPTClosure(PdfFile, Tree, 0.30, 0.35, 0, 40);
   PlotPTClosure(PdfFile, Tree, 0.35, 0.40, 0, 45);
   PlotPTClosure(PdfFile, Tree, 0.40, 0.45, 0, 45);
   PlotPTClosure(PdfFile, Tree, 0.45, 0.50, 0, 50);
   PlotPTClosure(PdfFile, Tree, 0.50, 0.55, 0, 50);
   PlotPTClosure(PdfFile, Tree, 0.55, 0.60, 0, 45);
   PlotPTClosure(PdfFile, Tree, 0.60, 0.65, 0, 45);
   PlotPTClosure(PdfFile, Tree, 0.65, 0.70, 0, 40);
   PlotPTClosure(PdfFile, Tree, 0.70, 0.75, 0, 40);
   PlotPTClosure(PdfFile, Tree, 0.75, 0.80, 0, 35);
   PlotPTClosure(PdfFile, Tree, 0.80, 0.85, 0, 30);
   PlotPTClosure(PdfFile, Tree, 0.85, 0.90, 0, 20);
   PlotPTClosure(PdfFile, Tree, 0.90, 1.00, 0, 15);
   
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00,  5, 10);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 10, 15);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 15, 20);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 20, 25);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 25, 30);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 30, 35);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 35, 40);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 40, 45);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 45, 50);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PlotPTClosure(PdfFileHelper &PdfFile, TTree *Tree,
   double ThetaPIMin, double ThetaPIMax, double PTMin, double PTMax)
{
   double ThetaMin = ThetaPIMin * M_PI;
   double ThetaMax = ThetaPIMax * M_PI;

   TProfile P1("P1", ";Gen PT;Response", 50, PTMin, PTMax);
   TProfile P2("P2", ";Gen PT;Response", 50, PTMin, PTMax);

   Tree->Draw("RecoPT/GenPT:GenPT>>P1", Form("GenTheta > %f && GenTheta < %f", ThetaMin, ThetaMax));
   Tree->Draw("CorrectedPT/GenPT:GenPT>>P2", Form("GenTheta > %f && GenTheta < %f", ThetaMin, ThetaMax));

   P2.SetLineWidth(2);
   P2.SetLineColor(kBlack);
   P2.SetMarkerColor(kBlack);
   P1.SetLineWidth(2);
   P1.SetLineColor(kRed);
   P1.SetMarkerColor(kRed);

   for(int i = 1; i <= 50; i++)
   {
      if(P1.GetBinEntries(i) == 1)
         P1.SetBinContent(i, 0);
      if(P2.GetBinEntries(i) == 1)
         P2.SetBinContent(i, 0);
   }

   TGraph G1;
   G1.SetPoint(0, -1000, 1);
   G1.SetPoint(1, +1000, 1);

   TGraph G2;
   G2.SetPoint(0, -1000, 1.01);
   G2.SetPoint(1, +1000, 1.01);
   G2.SetPoint(2, +1000, 0.99);
   G2.SetPoint(3, -1000, 0.99);
   G2.SetLineStyle(kDashed);

   TH2D HWorld("HWorld", Form("Theta = %.2f#pi ~ %.2f#pi;Gen PT;Response", ThetaPIMin, ThetaPIMax),
      50, PTMin, PTMax, 50, 0.75, 1.25);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.Draw("axis");

   G1.Draw("l");
   G2.Draw("l");

   P1.Draw("same");
   P2.Draw("same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();
   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.12, 0.87, "#color[2]{Before} #color[1]{After}");

   PdfFile.AddCanvas(Canvas);
}

void PlotThetaClosure(PdfFileHelper &PdfFile, TTree *Tree,
   double ThetaPIMin, double ThetaPIMax, double PTMin, double PTMax)
{
   double ThetaMin = ThetaPIMin * M_PI;
   double ThetaMax = ThetaPIMax * M_PI;

   TProfile P1("P1", ";Gen Theta (#pi);Response", 50, ThetaPIMin, ThetaPIMax);
   TProfile P2("P2", ";Gen Theta (#pi);Response", 50, ThetaPIMin, ThetaPIMax);

   Tree->Draw("RecoPT/GenPT:GenTheta/3.1415926535>>P1", Form("GenPT > %f && GenPT < %f", PTMin, PTMax));
   Tree->Draw("CorrectedPT/GenPT:GenTheta/3.1415926535>>P2", Form("GenPT > %f && GenPT < %f", PTMin, PTMax));

   P2.SetLineWidth(2);
   P2.SetLineColor(kBlack);
   P2.SetMarkerColor(kBlack);
   P1.SetLineWidth(2);
   P1.SetLineColor(kRed);
   P1.SetMarkerColor(kRed);

   for(int i = 1; i <= 50; i++)
   {
      if(P1.GetBinEntries(i) == 1)
         P1.SetBinContent(i, 0);
      if(P2.GetBinEntries(i) == 1)
         P2.SetBinContent(i, 0);
   }

   TGraph G1;
   G1.SetPoint(0, -1000, 1);
   G1.SetPoint(1, +1000, 1);

   TGraph G2;
   G2.SetPoint(0, -1000, 1.01);
   G2.SetPoint(1, +1000, 1.01);
   G2.SetPoint(2, +1000, 0.99);
   G2.SetPoint(3, -1000, 0.99);
   G2.SetLineStyle(kDashed);
   
   TH2D HWorld("HWorld", Form("PT = %.1f ~ %.1f;Gen Theta (#pi);Response", PTMin, PTMax),
      50, ThetaPIMin, ThetaPIMax, 50, 0.75, 1.25);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.Draw("axis");

   G1.Draw("l");
   G2.Draw("l");

   P1.Draw("same");
   P2.Draw("same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();
   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.12, 0.87, "#color[2]{Before} #color[1]{After}");

   PdfFile.AddCanvas(Canvas);
}














