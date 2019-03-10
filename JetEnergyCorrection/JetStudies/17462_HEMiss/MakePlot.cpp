#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TProfile.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TLatex.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void AddPlot2D(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection,
   string Title, int BinX, double MinX, double MaxX, int BinY, double MinY, double MaxY);
void AddPlot2D(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection,
   string Title, int BinX, double *Bins, int BinY, double MinY, double MaxY);
void AddStackedPlotPhi(PdfFileHelper &PdfFile, TTree *Tree, string Selection,
   string Title, int Bin, double Min, double Max);
void AddStackedPlotPT(PdfFileHelper &PdfFile, TTree *Tree, string Selection,
   string Title, int Bin, double *Bins);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFile = CL.Get("input");
   string OutputFile = CL.Get("output");
   string Algorithm = CL.Get("algorithm", "ak4pf");
   bool DoResponse = CL.GetBool("doresponse", false);
   bool DoResolution = CL.GetBool("doresolution", false);
   bool DoFraction = CL.GetBool("dofraction", false);
   bool DoStack = CL.GetBool("dostack", false);

   PdfFileHelper PdfFile(OutputFile);
   PdfFile.AddTextPage("Some plots for HEMiss (" + Algorithm + ")");

   TFile File(InputFile.c_str());

   TTree *Tree = (TTree *)File.Get(Form("%s/t", Algorithm.c_str()));
   
   Tree->SetAlias("PFMET", "(sqrt(Sum$(pfcand_px)**2+Sum$(pfcand_py)**2))");

   if(DoResponse == true)
   {
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 40",
         "Response (GenPT = 15-40);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 70",
         "Response (GenPT = 40-70);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt < 110",
         "Response (GenPT = 70-110);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt > 110",
         "Response (GenPT = 110-inf);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 30",
         "Response (GenPT = 15-30);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 30 && refpt < 45",
         "Response (GenPT = 30-45);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 45 && refpt < 70",
         "Response (GenPT = 45-70);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt < 90",
         "Response (GenPT = 70-90);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 90 && refpt < 110",
         "Response (GenPT = 90-110);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 110 && refpt < 140",
         "Response (GenPT = 110-140);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 140 && refpt < 180",
         "Response (GenPT = 140-180);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 180 && refpt < 250",
         "Response (GenPT = 180-250);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 250 && refpt < 10000",
         "Response (GenPT = 250-inf);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      
      /*
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 40 && PFMET < 50",
         "Response (GenPT = 15-40, raw PFMET < 50);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 70 && PFMET < 50",
         "Response (GenPT = 40-70, raw PFMET < 50);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt < 110 && PFMET < 50",
         "Response (GenPT = 70-110, raw PFMET < 50);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt > 110 && PFMET < 50",
         "Response (GenPT = 110-inf, raw PFMET < 50);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
  
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 40 && PFMET > 50",
         "Response (GenPT = 15-40, raw PFMET > 50);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 70 && PFMET > 50",
         "Response (GenPT = 40-70, raw PFMET > 50);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt < 110 && PFMET > 50",
         "Response (GenPT = 70-110, raw PFMET > 50);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt > 110 && PFMET > 50",
         "Response (GenPT = 110-inf, raw PFMET > 50);#phi;Response", 100, -3.14, 3.14, 100, 0, 2.5);
      */

      double Binning[] = {9.9, 25, 35, 45, 55, 70, 90, 120, 150, 200, 500, 1000};
      
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:refpt", "jteta > -2.8 && jteta < -1.5 && jtphi > -1.4 && jtphi < -1.0",
         "Response in bad region;p_{T}^{Gen};Response", 11, Binning, 100, 0, 2.5);
      AddPlot2D(PdfFile, Tree, "jtpt/refpt:refpt", "jteta > -2.8 && jteta < -1.5 && jtphi > 0",
         "Response in good region;p_{T}^{Gen};Response", 11, Binning, 100, 0, 2.5);
   }
  
   if(DoFraction == true)
   {
      AddPlot2D(PdfFile, Tree, "jtcef:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 40",
         "CEF (GenPT = 15-40);#phi;CEF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtnef:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 40",
         "NEF (GenPT = 15-40);#phi;NEF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtchf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 40",
         "CHF (GenPT = 15-40);#phi;CHF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtnhf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 40",
         "NHF (GenPT = 15-40);#phi;NHF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtmuf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 40",
         "MUF (GenPT = 15-40);#phi;MUF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtcef+jtnef+jtchf+jtnhf+jtmuf+jthfef:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 15 && refpt < 40",
         "Total fraction (GenPT = 15-40);#phi;Total fraction", 100, -3.14, 3.14, 100, 0, 1.05);
      
      AddPlot2D(PdfFile, Tree, "jtcef:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 70",
         "CEF (GenPT = 40-70);#phi;CEF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtnef:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 70",
         "NEF (GenPT = 40-70);#phi;NEF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtchf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 70",
         "CHF (GenPT = 40-70);#phi;CHF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtnhf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 70",
         "NHF (GenPT = 40-70);#phi;NHF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtmuf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 70",
         "MUF (GenPT = 40-70);#phi;MUF", 100, -3.14, 3.14, 100, 0, 1.05);
      
      AddPlot2D(PdfFile, Tree, "jtcef:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt < 110",
         "CEF (GenPT = 70-110);#phi;CEF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtnef:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt < 110",
         "NEF (GenPT = 70-110);#phi;NEF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtchf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt < 110",
         "CHF (GenPT = 70-110);#phi;CHF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtnhf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt < 110",
         "NHF (GenPT = 70-110);#phi;NHF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtmuf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt < 110",
         "MUF (GenPT = 70-110);#phi;MUF", 100, -3.14, 3.14, 100, 0, 1.05);

      AddPlot2D(PdfFile, Tree, "jtcef:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt > 110",
         "CEF (GenPT = 110-inf);#phi;CEF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtnef:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt > 110",
         "NEF (GenPT = 110-inf);#phi;NEF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtchf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt > 110",
         "CHF (GenPT = 110-inf);#phi;CHF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtnhf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt > 110",
         "NHF (GenPT = 110-inf);#phi;NHF", 100, -3.14, 3.14, 100, 0, 1.05);
      AddPlot2D(PdfFile, Tree, "jtmuf:jtphi", "jteta > -2.8 && jteta < -1.5 && refpt > 70 && refpt > 110",
         "MUF (GenPT = 110-inf);#phi;MUF", 100, -3.14, 3.14, 100, 0, 1.05);
   }

   if(DoStack == true)
   {
      PdfFile.AddTextPage("eta -1.5 to -2.8");

      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && refpt > 20 && refpt < 40",
         "GenPT = 20-40;#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 100",
         "GenPT = 40-100;#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && refpt > 100 && refpt > 100",
         "GenPT = 100-inf;#phi;PF Fractions", 75, -3.14, 3.14);
      
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && refpt > 20 && refpt < 40 && PFMET < 50",
         "GenPT = 20-40, raw PT MET < 50;#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 100 && PFMET < 50",
         "GenPT = 40-100, raw PF MET < 50;#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && refpt > 100 && refpt > 100 && PFMET < 50",
         "GenPT = 100-inf, raw PF MET < 50;#phi;PF Fractions", 75, -3.14, 3.14);
      
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && refpt > 20 && refpt < 40 && PFMET > 50",
         "GenPT = 20-40, raw PT MET > 50;#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && refpt > 40 && refpt < 100 && PFMET > 50",
         "GenPT = 40-100, raw PF MET > 50;#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && refpt > 100 && refpt > 100 && PFMET > 50",
         "GenPT = 100-inf, raw PF MET > 50;#phi;PF Fractions", 75, -3.14, 3.14);

      double Binning[] = {9.9, 25, 35, 45, 55, 70, 90, 120, 150, 200, 500, 1000};
      
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && jtphi > -1.4 && jtphi < -1",
         "Bad region;p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && jtphi > -1.4 && jtphi < -1 && PFMET < 50",
         "Bad region (raw PF MET < 50);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && jtphi > -1.4 && jtphi < -1 && PFMET > 50",
         "Bad region (raw PF MET > 50);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && jtphi > 0",
         "Good region (positive phi);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && jtphi > 0 && PFMET < 50",
         "Good region (raw PF MET < 50);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.8 && jteta < -1.5 && jtphi > 0 && PFMET > 50",
         "Good region (raw PF MET > 50);p_{T}^{Gen};PF Fractions", 11, Binning);

      PdfFile.AddTextPage("eta -1.5 to -2.5");

      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && refpt > 20 && refpt < 40",
         "GenPT = 20-40 (up to eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && refpt > 40 && refpt < 100",
         "GenPT = 40-100 (up to eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && refpt > 100 && refpt > 100",
         "GenPT = 100-inf (up to eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && refpt > 20 && refpt < 40 && PFMET < 50",
         "GenPT = 20-40, raw PT MET < 50 (up to eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && refpt > 40 && refpt < 100 && PFMET < 50",
         "GenPT = 40-100, raw PF MET < 50 (up to eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && refpt > 100 && refpt > 100 && PFMET < 50",
         "GenPT = 100-inf, raw PF MET < 50(up to eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && refpt > 20 && refpt < 40 && PFMET > 50",
         "GenPT = 20-40, raw PT MET > 50(up to eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && refpt > 40 && refpt < 100 && PFMET > 50",
         "GenPT = 40-100, raw PF MET > 50(up to eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && refpt > 100 && refpt > 100 && PFMET > 50",
         "GenPT = 100-inf, raw PF MET > 50(up to eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);

      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && jtphi > -1.4 && jtphi < -1",
         "Bad region(up to eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && jtphi > -1.4 && jtphi < -1 && PFMET < 50",
         "Bad region (raw PF MET < 50)(up to eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && jtphi > -1.4 && jtphi < -1 && PFMET > 50",
         "Bad region (raw PF MET > 50)(up to eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && jtphi > 0",
         "Good region (positive phi)(up to eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && jtphi > 0 && PFMET < 50",
         "Good region (raw PF MET < 50)(up to eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -2.5 && jteta < -1.5 && jtphi > 0 && PFMET > 50",
         "Good region (raw PF MET > 50)(up to eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);

      PdfFile.AddTextPage("eta -2.5 to -3.0");

      AddStackedPlotPhi(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && refpt > 20 && refpt < 40",
         "GenPT = 20-40(above eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && refpt > 40 && refpt < 100",
         "GenPT = 40-100(above eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && refpt > 100 && refpt > 100",
         "GenPT = 100-inf(above eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && refpt > 20 && refpt < 40 && PFMET < 50",
         "GenPT = 20-40, raw PT MET < 50(above eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && refpt > 40 && refpt < 100 && PFMET < 50",
         "GenPT = 40-100, raw PF MET < 50(above eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && refpt > 100 && refpt > 100 && PFMET < 50",
         "GenPT = 100-inf, raw PF MET < 50(above eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && refpt > 20 && refpt < 40 && PFMET > 50",
         "GenPT = 20-40, raw PT MET > 50(above eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && refpt > 40 && refpt < 100 && PFMET > 50",
         "GenPT = 40-100, raw PF MET > 50(above eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);
      AddStackedPlotPhi(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && refpt > 100 && refpt > 100 && PFMET > 50",
         "GenPT = 100-inf, raw PF MET > 50(above eta -2.5);#phi;PF Fractions", 75, -3.14, 3.14);

      AddStackedPlotPT(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && jtphi > -1.4 && jtphi < -1",
         "Bad region(above eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && jtphi > -1.4 && jtphi < -1 && PFMET < 50",
         "Bad region (raw PF MET < 50)(above eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && jtphi > -1.4 && jtphi < -1 && PFMET > 50",
         "Bad region (raw PF MET > 50)(above eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && jtphi > 0",
         "Good region (positive phi)(above eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && jtphi > 0 && PFMET < 50",
         "Good region (raw PF MET < 50)(above eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
      AddStackedPlotPT(PdfFile, Tree, "jteta > -3.0 && jteta < -2.5 && jtphi > 0 && PFMET > 50",
         "Good region (raw PF MET > 50)(above eta -2.5);p_{T}^{Gen};PF Fractions", 11, Binning);
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot2D(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection,
   string Title, int BinX, double MinX, double MaxX, int BinY, double MinY, double MaxY)
{
   if(Tree == NULL)
      return;

   TH2D H("H", Title.c_str(), BinX, MinX, MaxX, BinY, MinY, MaxY);
   TProfile P("P", "", BinX / 2, MinX, MaxX);

   P.SetMarkerColor(kMagenta);
   P.SetLineColor(kMagenta);
   P.SetMarkerSize(1.5);

   Tree->Draw(Form("%s>>H", ToPlot.c_str()), Selection.c_str(), "colz");
   Tree->Draw(Form("%s>>P", ToPlot.c_str()), Selection.c_str(), "prof same");

   TF1 Fit("Fit", "pol0", -3.14, 3.14);
   TF1 Fit2("Fit2", "pol0+[1]*exp(-(x+1.20947)*(x+1.20947)/(0.344785*0.344785*2))", -3.14, 3.14);

   P.Fit(&Fit, "", "", 0, 3.14);

   Fit2.FixParameter(0, Fit.GetParameter(0));
   Fit2.SetParameter(1, 0.1);
   P.Fit(&Fit2, "EW");

   H.SetStats(0);

   TLatex Latex;
   Latex.SetTextSize(0.020);
   Latex.SetTextFont(42);
   Latex.SetNDC();

   TCanvas Canvas;

   H.Draw("colz");
   P.Draw("same");
   Fit.Draw("same");
   Fit2.Draw("same");

   Latex.DrawLatex(0.10, 0.93, Form("Mean %.2f", Fit2.GetParameter(0)));
   Latex.DrawLatex(0.10, 0.91, Form("Deviation %.2f", Fit2.GetParameter(1)));

   PdfFile.AddCanvas(Canvas);

   P.SetErrorOption("S");

   TH1D HResolution("HResolution", Title.c_str(), BinX / 2, MinX, MaxX);
   HResolution.GetYaxis()->SetTitle("Resolution");

   for(int i = 1; i <= HResolution.GetNbinsX(); i++)
   {
      double Mean = P.GetBinContent(i);
      double Error = P.GetBinError(i);

      cout << i << " " << Mean << " " << Error << endl;

      HResolution.SetBinContent(i, Error / Mean);
   }

   TH2D HWorld("HWorld", Title.c_str(), BinX, MinX, MaxX, 100, 0, 0.5);
   HWorld.GetYaxis()->SetTitle("Resolution");
   HWorld.SetStats(0);
   
   HResolution.SetMarkerStyle(20);

   HWorld.Draw("axis");
   HResolution.Draw("same p");

   PdfFile.AddCanvas(Canvas);
}

void AddPlot2D(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection,
   string Title, int BinX, double *Bins, int BinY, double MinY, double MaxY)
{
   if(Tree == NULL)
      return;

   TH2D H("H", Title.c_str(), BinX, Bins, BinY, MinY, MaxY);
   TProfile P("P", "", BinX, Bins);

   P.SetMarkerColor(kMagenta);
   P.SetLineColor(kMagenta);
   P.SetMarkerSize(1.5);

   Tree->Draw(Form("%s>>H", ToPlot.c_str()), Selection.c_str(), "colz");
   Tree->Draw(Form("%s>>P", ToPlot.c_str()), Selection.c_str(), "prof same");

   H.SetStats(0);

   TLatex Latex;
   Latex.SetTextSize(0.020);
   Latex.SetTextFont(42);
   Latex.SetNDC();

   TCanvas Canvas;

   H.Draw("colz");
   P.Draw("same");

   Canvas.SetLogx();

   PdfFile.AddCanvas(Canvas);

   P.SetErrorOption("S");

   TH1D HResolution("HResolution", Title.c_str(), BinX, Bins);
   HResolution.GetYaxis()->SetTitle("Resolution");

   for(int i = 1; i <= HResolution.GetNbinsX(); i++)
   {
      double Mean = P.GetBinContent(i);
      double Error = P.GetBinError(i);

      cout << i << " " << Mean << " " << Error << endl;

      HResolution.SetBinContent(i, Error / Mean);
   }

   TH2D HWorld("HWorld", Title.c_str(), BinX, Bins, 100, 0, 0.5);
   HWorld.GetYaxis()->SetTitle("Resolution");
   HWorld.SetStats(0);

   HResolution.SetMarkerStyle(20);

   HWorld.Draw("axis");
   HResolution.Draw("same p");

   PdfFile.AddCanvas(Canvas);
}

void AddStackedPlotPhi(PdfFileHelper &PdfFile, TTree *Tree, string Selection,
   string Title, int Bin, double Min, double Max)
{
   if(Tree == NULL)
      return;

   TProfile P1("P1", Title.c_str(), Bin, Min, Max);
   TProfile P2("P2", Title.c_str(), Bin, Min, Max);
   TProfile P3("P3", Title.c_str(), Bin, Min, Max);
   TProfile P4("P4", Title.c_str(), Bin, Min, Max);
   TProfile P5("P5", Title.c_str(), Bin, Min, Max);

   Tree->Draw("jtnhf:jtphi>>P1", Selection.c_str(), "prof");
   Tree->Draw("jtnhf+jtnef:jtphi>>P2", Selection.c_str(), "prof");
   Tree->Draw("jtnhf+jtnef+jtcef:jtphi>>P3", Selection.c_str(), "prof");
   Tree->Draw("jtnhf+jtnef+jtcef+jtchf:jtphi>>P4", Selection.c_str(), "prof");
   Tree->Draw("jtnhf+jtnef+jtcef+jtchf+jtmuf+jthfef:jtphi>>P5", Selection.c_str(), "prof");

   P1.SetMarkerStyle(1);
   P2.SetMarkerStyle(1);
   P3.SetMarkerStyle(1);
   P4.SetMarkerStyle(1);
   P5.SetMarkerStyle(1);

   P1.SetFillColor(kBlack);
   P2.SetFillColor(kRed);
   P3.SetFillColor(kBlue);
   P4.SetFillColor(kGreen);
   P5.SetFillColor(kYellow + 3);
   
   P1.SetLineColor(kBlack);
   P2.SetLineColor(kRed);
   P3.SetLineColor(kBlue);
   P4.SetLineColor(kGreen);
   P5.SetLineColor(kYellow + 3);

   P1.SetMarkerColor(kBlack);
   P2.SetMarkerColor(kRed);
   P3.SetMarkerColor(kBlue);
   P4.SetMarkerColor(kGreen);
   P5.SetMarkerColor(kYellow + 3);

   TH2D H("H", Title.c_str(), Bin, Min, Max, 100, 0, 1.05);
   H.SetStats(0);

   TLatex Latex;
   Latex.SetTextSize(0.020);
   Latex.SetTextFont(42);
   Latex.SetNDC();

   TCanvas Canvas;

   H.Draw("colz");
   P5.Draw("same bar");
   P4.Draw("same bar");
   P3.Draw("same bar");
   P2.Draw("same bar");
   P1.Draw("same bar");
   H.Draw("axis same");

   TLegend Legend(0.6, 0.8, 0.8, 0.5);
   Legend.SetFillColor(kWhite);
   Legend.SetBorderSize(1);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&P1, "NHF", "plf");
   Legend.AddEntry(&P2, "NEF", "plf");
   Legend.AddEntry(&P3, "CEF", "plf");
   Legend.AddEntry(&P4, "CHF", "plf");
   Legend.AddEntry(&P5, "Others", "plf");
   Legend.Draw();

   static int Count = 0;
   Count = Count + 1;
   Canvas.SaveAs(Form("PhiPlot_%d.pdf", Count));

   PdfFile.AddCanvas(Canvas);
}

void AddStackedPlotPT(PdfFileHelper &PdfFile, TTree *Tree, string Selection,
   string Title, int Bin, double *Bins)
{
   if(Tree == NULL)
      return;

   TProfile P1("P1", Title.c_str(), Bin, Bins);
   TProfile P2("P2", Title.c_str(), Bin, Bins);
   TProfile P3("P3", Title.c_str(), Bin, Bins);
   TProfile P4("P4", Title.c_str(), Bin, Bins);
   TProfile P5("P5", Title.c_str(), Bin, Bins);

   Tree->Draw("jtnhf:refpt>>P1", Selection.c_str(), "prof");
   Tree->Draw("jtnhf+jtnef:refpt>>P2", Selection.c_str(), "prof");
   Tree->Draw("jtnhf+jtnef+jtcef:refpt>>P3", Selection.c_str(), "prof");
   Tree->Draw("jtnhf+jtnef+jtcef+jtchf:refpt>>P4", Selection.c_str(), "prof");
   Tree->Draw("jtnhf+jtnef+jtcef+jtchf+jtmuf+jthfef:refpt>>P5", Selection.c_str(), "prof");

   P1.SetMarkerStyle(1);
   P2.SetMarkerStyle(1);
   P3.SetMarkerStyle(1);
   P4.SetMarkerStyle(1);
   P5.SetMarkerStyle(1);

   P1.SetFillColor(kBlack);
   P2.SetFillColor(kRed);
   P3.SetFillColor(kBlue);
   P4.SetFillColor(kGreen);
   P5.SetFillColor(kYellow + 3);
   
   P1.SetLineColor(kBlack);
   P2.SetLineColor(kRed);
   P3.SetLineColor(kBlue);
   P4.SetLineColor(kGreen);
   P5.SetLineColor(kYellow + 3);

   P1.SetMarkerColor(kBlack);
   P2.SetMarkerColor(kRed);
   P3.SetMarkerColor(kBlue);
   P4.SetMarkerColor(kGreen);
   P5.SetMarkerColor(kYellow + 3);

   TH2D H("H", Title.c_str(), Bin, Bins, 100, 0, 1.05);
   H.SetStats(0);

   TLatex Latex;
   Latex.SetTextSize(0.020);
   Latex.SetTextFont(42);
   Latex.SetNDC();

   TCanvas Canvas;

   H.Draw("colz");
   P5.Draw("same bar");
   P4.Draw("same bar");
   P3.Draw("same bar");
   P2.Draw("same bar");
   P1.Draw("same bar");
   H.Draw("axis same");

   TLegend Legend(0.6, 0.8, 0.8, 0.5);
   Legend.SetFillColor(kWhite);
   Legend.SetBorderSize(1);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&P1, "NHF", "plf");
   Legend.AddEntry(&P2, "NEF", "plf");
   Legend.AddEntry(&P3, "CEF", "plf");
   Legend.AddEntry(&P4, "CHF", "plf");
   Legend.AddEntry(&P5, "Others", "plf");
   Legend.Draw();

   static int Count = 0;
   Count = Count + 1;
   Canvas.SaveAs(Form("PTPlot_%d_Linear.pdf", Count));

   PdfFile.AddCanvas(Canvas);

   Canvas.SetLogx();
   
   Canvas.SaveAs(Form("PTPlot_%d_Log.pdf", Count));
   
   PdfFile.AddCanvas(Canvas);
}




