#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TTree.h"

#include "PlotHelper4.h"
#include "SetStyle.h"

int main();
void AddPlot(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection,
   string Title, int XBin, double XMin, double XMax, double YMin, double YMax, bool Logy = false);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Output.pdf");

   TFile File("Test.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   if(Tree == nullptr)
      return -1;

   AddPlot(PdfFile, Tree, "MuonPT", "", "Muon p_{T};p_{T}", 60, 0, 120, 0, 0.025);
   AddPlot(PdfFile, Tree, "MuonEta", "", "Muon #eta;#eta", 60, -3.5, 3.5, 0, 0.3);
   AddPlot(PdfFile, Tree, "MuonDxy", "", "Muon D_{xy};D_{xy}", 60, 0, 110, 0, 0.02);
   AddPlot(PdfFile, Tree, "L1Dxy", "", "L1 D_{xy};D_{xy}", 5, 0, 5, 1e-4, 10, true);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection,
   string Title, int XBin, double XMin, double XMax, double YMin, double YMax, bool LogY)
{
   TH1D H("H", Title.c_str(), XBin, XMin, XMax);

   Tree->Draw((ToPlot + ">>H").c_str(), Selection.c_str());

   double BinSize = (XMax - XMin) / XBin;
   H.Scale(1 / H.Integral() / BinSize);

   TCanvas Canvas;

   TH2D HWorld("HWorld", Title.c_str(), 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   H.Draw("same");
   H.Draw("hist same");

   Canvas.SetLogy(LogY);

   PdfFile.AddCanvas(Canvas);
}



