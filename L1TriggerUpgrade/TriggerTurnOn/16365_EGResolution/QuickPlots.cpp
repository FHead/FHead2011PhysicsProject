#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TF1.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void PlotFile(string FileName, string OutputBase, bool IsTyler);
void FitResolution(PdfFileHelper &PdfFile, TTree *T, string Selection, string Title, bool IsTyler);

int main()
{
   SetThesisStyle();

   PlotFile("Result/Combined/WToENu140PU.root", "WToENu140", false);
   PlotFile("Result/Combined/WToEnu140PU_NewRecipePlusTyler.root", "WToENu140Tyler", true);

   return 0;
}

void PlotFile(string FileName, string OutputBase, bool IsTyler)
{
   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("File: " + FileName);

   TFile F(FileName.c_str());
   TTree *T = (TTree *)F.Get("T");

   PdfFile.AddTextPage("Some Basic 2D Plots");
   PdfFile.AddPlot2D(T, "L1PT:GenPT", "GenE > 0", "colz",
      ";GenPT;L1PT", 200, 0, 100, 200, 0, 100, false, true);
   PdfFile.AddPlot2D(T, "L1PT/GenPT:GenPT", "GenE > 0", "colz",
      ";GenPT;L1PT/GenPT", 200, 0, 100, 200, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PT/GenPT:GenPT", "GenE > 0 && abs(GenEta) < 1.5", "colz",
      "|Gen Eta| < 1.5;GenPT;L1PT/GenPT", 200, 0, 100, 200, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PT/GenPT:GenPT", "GenE > 0 && abs(GenEta) > 1.5", "colz",
      "|Gen Eta| > 1.5;GenPT;L1PT/GenPT", 200, 0, 100, 200, 0, 2, false, true);
   
   PdfFile.AddTextPage("Rate of fakes and no-matches (eta)");
   PdfFile.AddPlotProfile(T, "L1PT>0:GenEta", "GenE > 0 && GenPT > 10", "prof",
      "Gen PT > 10;GenEta;P(has an L1 object)", 100, -2.5, 2.5);
   PdfFile.AddPlotProfile(T, "L1PT>0:GenEta", "GenE > 0 && GenPT > 20", "prof",
      "Gen PT > 20;GenEta;P(has an L1 object)", 100, -2.5, 2.5);
   PdfFile.AddPlotProfile(T, "L1PT>0:GenEta", "GenE > 0 && GenPT > 30", "prof",
      "Gen PT > 30;GenEta;P(has an L1 object)", 100, -2.5, 2.5);
   PdfFile.AddPlotProfile(T, "L1PT>0:GenEta", "GenE > 0 && GenPT > 40", "prof",
      "Gen PT > 40;GenEta;P(has an L1 object)", 50, -2.5, 2.5);
   PdfFile.AddPlotProfile(T, "L1PT>0:GenEta", "GenE > 0 && GenPT > 50", "prof",
      "Gen PT > 50;GenEta;P(has an L1 object)", 25, -2.5, 2.5);
   
   PdfFile.AddPlotProfile(T, "L1PT/GenPT>0.5:GenEta", "GenE > 0 && GenPT > 10 && L1PT > 0", "prof",
      "Gen PT > 10;GenEta;P(L1PT > 0.5 GenPT  |  has an L1 object)", 100, -2.5, 2.5);
   PdfFile.AddPlotProfile(T, "L1PT/GenPT>0.5:GenEta", "GenE > 0 && GenPT > 20 && L1PT > 0", "prof",
      "Gen PT > 20;GenEta;P(L1PT > 0.5 GenPT  |  has an L1 object)", 100, -2.5, 2.5);
   PdfFile.AddPlotProfile(T, "L1PT/GenPT>0.5:GenEta", "GenE > 0 && GenPT > 30 && L1PT > 0", "prof",
      "Gen PT > 30;GenEta;P(L1PT > 0.5 GenPT  |  has an L1 object)", 100, -2.5, 2.5);
   PdfFile.AddPlotProfile(T, "L1PT/GenPT>0.5:GenEta", "GenE > 0 && GenPT > 40 && L1PT > 0", "prof",
      "Gen PT > 40;GenEta;P(L1PT > 0.5 GenPT  |  has an L1 object)", 50, -2.5, 2.5);
   PdfFile.AddPlotProfile(T, "L1PT/GenPT>0.5:GenEta", "GenE > 0 && GenPT > 50 && L1PT > 0", "prof",
      "Gen PT > 50;GenEta;P(L1PT > 0.5 GenPT  |  has an L1 object)", 25, -2.5, 2.5);
   
   PdfFile.AddTextPage("Rate of fakes and no-matches (pt)");
   PdfFile.AddPlotProfile(T, "L1PT>0:GenPT", "GenE > 0", "prof",
      ";GenPT;P(has an L1 object)", 50, 0, 100);
   PdfFile.AddPlotProfile(T, "L1PT>0:GenPT", "GenE > 0 && abs(GenEta) < 1.5", "prof",
      "Barrel;GenPT;P(has an L1 object)", 50, 0, 100);
   PdfFile.AddPlotProfile(T, "L1PT>0:GenPT", "GenE > 0 && abs(GenEta) > 1.5", "prof",
      "Endcap;GenPT;P(has an L1 object)", 50, 0, 100);
   
   PdfFile.AddPlotProfile(T, "L1PT/GenPT>0.5:GenPT", "GenE > 0 && L1PT > 0", "prof",
      ";GenPT;P(L1PT > 0.5 GenPT  |  has an L1 object)", 50, 0, 100);
   PdfFile.AddPlotProfile(T, "L1PT/GenPT>0.5:GenPT", "GenE > 0 && L1PT > 0 && abs(GenEta) < 1.5", "prof",
      "Barrel;GenPT;P(L1PT > 0.5 GenPT  |  has an L1 object)", 50, 0, 100);
   PdfFile.AddPlotProfile(T, "L1PT/GenPT>0.5:GenPT", "GenE > 0 && L1PT > 0 && abs(GenEta) > 1.5", "prof",
      "Endcap;GenPT;P(L1PT > 0.5 GenPT  |  has an L1 object)", 50, 0, 100);

   PdfFile.AddTextPage("Resolution plots");
   PdfFile.AddPlot(T, "L1PT/GenPT", "GenE > 0 && GenPT > 20 && GenPT < 30", "",
      "Gen PT = 20-30;L1PT/GenPT;", 100, 0, 2);
   PdfFile.AddPlot(T, "L1PT/GenPT", "GenE > 0 && GenPT > 30 && GenPT < 40", "",
      "Gen PT = 30-40;L1PT/GenPT;", 100, 0, 2);
   PdfFile.AddPlot(T, "L1PT/GenPT", "GenE > 0 && GenPT > 40 && GenPT < 50", "",
      "Gen PT = 40-50;L1PT/GenPT;", 100, 0, 2);
   PdfFile.AddPlot(T, "L1PT/GenPT", "GenE > 0 && GenPT > 50 && GenPT < 100", "",
      "Gen PT = 50-100;L1PT/GenPT;", 100, 0, 2);
   
   PdfFile.AddTextPage("Resolution plots, |eta| < 1.5");
   FitResolution(PdfFile, T, "GenE > 0 && GenPT > 20 && GenPT < 30 && abs(GenEta) < 1.5 && L1E > 0",
      "Gen PT = 20-30, barrel", IsTyler);
   FitResolution(PdfFile, T, "GenE > 0 && GenPT > 30 && GenPT < 40 && abs(GenEta) < 1.5 && L1E > 0",
      "Gen PT = 30-40, barrel", IsTyler);
   FitResolution(PdfFile, T, "GenE > 0 && GenPT > 40 && GenPT < 50 && abs(GenEta) < 1.5 && L1E > 0",
      "Gen PT = 40-50, barrel", IsTyler);
   FitResolution(PdfFile, T, "GenE > 0 && GenPT > 50 && GenPT < 70 && abs(GenEta) < 1.5 && L1E > 0",
      "Gen PT = 50-70, barrel", IsTyler);

   PdfFile.AddTextPage("Resolution plots, |eta| > 1.5");
   FitResolution(PdfFile, T, "GenE > 0 && GenPT > 20 && GenPT < 30 && abs(GenEta) > 1.5 && L1E > 0",
      "Gen PT = 20-30, endcap", IsTyler);
   FitResolution(PdfFile, T, "GenE > 0 && GenPT > 30 && GenPT < 40 && abs(GenEta) > 1.5 && L1E > 0",
      "Gen PT = 30-40, endcap", IsTyler);
   FitResolution(PdfFile, T, "GenE > 0 && GenPT > 40 && GenPT < 50 && abs(GenEta) > 1.5 && L1E > 0",
      "Gen PT = 40-50, endcap", IsTyler);
   FitResolution(PdfFile, T, "GenE > 0 && GenPT > 50 && GenPT < 70 && abs(GenEta) > 1.5 && L1E > 0",
      "Gen PT = 50-70, endcap", IsTyler);

   F.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
}

void FitResolution(PdfFileHelper &PdfFile, TTree *T, string Selection, string Title, bool IsTyler)
{
   if(T == NULL)
      return;

   TH1D HResolution("HResolution", Form("%s;L1PT/GenPT;", Title.c_str()), 100, 0, 2);

   T->Draw("L1PT/GenPT>>HResolution", Selection.c_str());

   string FitFunction;
   if(IsTyler == true)
      FitFunction = "gaus(0)+gaus(3)";
   else
      FitFunction = "gaus";

   TF1 Fit("Fit", FitFunction.c_str(), 0, 2);
   
   if(IsTyler == true)
      Fit.SetParameters(200, 0.97, 0.1, 10, 0.90, 0.2);
   else
      Fit.SetParameters(200, 1.1, 0.1);
   Fit.SetParNames("Core height", "Core mean", "Core sigma", "Secondary height", "Secondary mean", "Secondary sigma");

   for(int i = 0; i < 10; i++)
      HResolution.Fit(&Fit, "", "", 0.2, 2);

   TCanvas Canvas;

   HResolution.Draw();

   PdfFile.AddCanvas(Canvas);
}



