#include <iostream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"

#include "SetStyle.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Toy.pdf");
   PdfFile.AddTextPage("Toy");

   TFile File("Tree.root");

   TTree *Tree = (TTree *)File.Get("Tree");
   
   TH1D HPT0All("HPT0All", "All Gen PT;Gen Jet PT;", 100, 0, 100);
   TH1D HPT0("HPT0", "Gen PT with after PT1 > 30 and PT2 > 20;Gen Jet PT;", 100, 0, 100);
   TH1D HQT("HQT", ";QT;", 100, 0, 100);
   TH1D HPT("HPT", ";PT;", 100, 0, 100);
   TH2D HQTPT("HQTPT", ";QT;PT", 100, 0, 100, 100, 0, 100);
   TH1D HPhi("HPhi", ";#phi;", 100, -M_PI, M_PI);
   TProfile PCos2Phi("PCos2Phi", ";Q_{T};<cos(2#phi)>", 100, 0, 100);
   TProfile PCos2PhiZoom("PCos2PhiZoom", ";Q_{T};<cos(2#phi)>", 5, 0, 25);

   HPT0All.SetStats(0);
   HPT0.SetStats(0);
   HQT.SetStats(0);
   HPT.SetStats(0);
   HQTPT.SetStats(0);
   HPhi.SetStats(0);
   PCos2Phi.SetStats(0);
   PCos2PhiZoom.SetStats(0);

   char Weight[] = "exp(-PT0/30)";
   char Cut[] = "exp(-PT0/30) * (max(PT1,PT2) > 30 && min(PT1,PT2) > 20 && PT < 60 && QT < 25)";

   Tree->Draw("PT0>>HPT0All", Weight);
   Tree->Draw("PT0>>HPT0", Cut);
   Tree->Draw("QT>>HQT", Cut);
   Tree->Draw("PT>>HPT", Cut);
   Tree->Draw("PT:QT>>HQTPT", Cut);
   Tree->Draw("Phi>>HPhi", Cut);
   Tree->Draw("cos(2*Phi):QT>>PCos2Phi", Cut, "prof");
   Tree->Draw("cos(2*Phi):QT>>PCos2PhiZoom", Cut, "prof");

   PdfFile.AddPlot(HPT0All);
   PdfFile.AddPlot(HPT0);
   PdfFile.AddPlot(HQT);
   PdfFile.AddPlot(HPT);
   PdfFile.AddPlot(HPhi);
   PdfFile.AddPlot(HQTPT, "colz");
   PdfFile.AddPlot(PCos2Phi);
   PdfFile.AddPlot(PCos2PhiZoom, "hist");

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
}



