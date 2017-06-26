#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void ProcessFile(PdfFileHelper &PdfFile, string FileName, bool IsEle);
void FillGraphFromHistogram(TGraph &G, TH1D *H);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("IsolationPlots.pdf");
   PdfFile.AddTextPage("Isolation Plots");

   ProcessFile(PdfFile, "Result/Combined/WToEnu140PU.root", true);
   ProcessFile(PdfFile, "Result/Combined/WToEnu140PU_NewRecipePlusTyler.root", true);
   ProcessFile(PdfFile, "Result/Combined/WToEnu140PU_NewRecipePlusTyler_NoIso.root", true);
   
   ProcessFile(PdfFile, "Result/Combined/WToEnu200PU.root", true);
   ProcessFile(PdfFile, "Result/Combined/WToEnu200PU_NewRecipePlusTyler.root", true);
   ProcessFile(PdfFile, "Result/Combined/WToEnu200PU_NewRecipePlusTyler_NoIso.root", true);
   
   ProcessFile(PdfFile, "Result/Combined/Hgaga140PU_NewRecipePlusTyler_NoIso.root", false);
   ProcessFile(PdfFile, "Result/Combined/Hgaga200PU_NewRecipePlusTyler_NoIso.root", false);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void ProcessFile(PdfFileHelper &PdfFile, string FileName, bool IsEle)
{
   PdfFile.AddTextPage("File " + FileName, 0.034);

   TFile File(FileName.c_str());

   TGraph GTkEG, GTkEG2, GTkIsoEG, GTkEM;
   TGraph GTkEGR, GTkEG2R, GTkIsoEGR, GTkEMR;
   TGraph GTkEGR2, GTkEG2R2, GTkIsoEGR2, GTkEMR2;

   if(File.Get("TkEG/TkEG_TkEGIso_000000") != NULL)
      FillGraphFromHistogram(GTkEG, (TH1D *)File.Get("TkEG/TkEG_TkEGIso_000000"));
   if(File.Get("TkEG2/TkEG2_TkEGIso_000000") != NULL)
      FillGraphFromHistogram(GTkEG2, (TH1D *)File.Get("TkEG2/TkEG2_TkEGIso_000000"));
   if(File.Get("TkIsoEG/TkIsoEG_TkEGIso_000000") != NULL)
      FillGraphFromHistogram(GTkIsoEG, (TH1D *)File.Get("TkIsoEG/TkIsoEG_TkEGIso_000000"));
   if(File.Get("TkEM/TkEM_TkEGIso_000000") != NULL)
      FillGraphFromHistogram(GTkEM, (TH1D *)File.Get("TkEM/TkEM_TkEGIso_000000"));

   if(File.Get("TkEG/TkEG_TkIso_000000") != NULL)
      FillGraphFromHistogram(GTkEG, (TH1D *)File.Get("TkEG/TkEG_TkIso_000000"));
   if(File.Get("TkEG2/TkEG2_TkIso_000000") != NULL)
      FillGraphFromHistogram(GTkEG2, (TH1D *)File.Get("TkEG2/TkEG2_TkIso_000000"));
   if(File.Get("TkIsoEG/TkIsoEG_TkIso_000000") != NULL)
      FillGraphFromHistogram(GTkIsoEG, (TH1D *)File.Get("TkIsoEG/TkIsoEG_TkIso_000000"));
   if(File.Get("TkEM/TkEM_TkIso_000000") != NULL)
      FillGraphFromHistogram(GTkEM, (TH1D *)File.Get("TkEM/TkEM_TkIso_000000"));

   if(File.Get("TkEG/TkEG_TkIsoRestricted_000000") != NULL)
      FillGraphFromHistogram(GTkEGR, (TH1D *)File.Get("TkEG/TkEG_TkIsoRestricted_000000"));
   if(File.Get("TkEG2/TkEG2_TkIsoRestricted_000000") != NULL)
      FillGraphFromHistogram(GTkEG2R, (TH1D *)File.Get("TkEG2/TkEG2_TkIsoRestricted_000000"));
   if(File.Get("TkIsoEG/TkIsoEG_TkIsoRestricted_000000") != NULL)
      FillGraphFromHistogram(GTkIsoEGR, (TH1D *)File.Get("TkIsoEG/TkIsoEG_TkIsoRestricted_000000"));
   if(File.Get("TkEM/TkEM_TkIsoRestricted_000000") != NULL)
      FillGraphFromHistogram(GTkEMR, (TH1D *)File.Get("TkEM/TkEM_TkIsoRestricted_000000"));

   if(File.Get("TkEG/TkEG_TkIsoRestricted2_000000") != NULL)
      FillGraphFromHistogram(GTkEGR2, (TH1D *)File.Get("TkEG/TkEG_TkIsoRestricted2_000000"));
   if(File.Get("TkEG2/TkEG2_TkIsoRestricted2_000000") != NULL)
      FillGraphFromHistogram(GTkEG2R2, (TH1D *)File.Get("TkEG2/TkEG2_TkIsoRestricted2_000000"));
   if(File.Get("TkIsoEG/TkIsoEG_TkIsoRestricted2_000000") != NULL)
      FillGraphFromHistogram(GTkIsoEGR2, (TH1D *)File.Get("TkIsoEG/TkIsoEG_TkIsoRestricted2_000000"));
   if(File.Get("TkEM/TkEM_TkIsoRestricted2_000000") != NULL)
      FillGraphFromHistogram(GTkEMR2, (TH1D *)File.Get("TkEM/TkEM_TkIsoRestricted2_000000"));

   GTkEG.SetMarkerColor(kBlack);
   GTkEG2.SetMarkerColor(kGreen);
   GTkIsoEG.SetMarkerColor(kYellow);
   GTkEM.SetMarkerColor(kRed);

   GTkEGR.SetMarkerColor(kBlack);
   GTkEG2R.SetMarkerColor(kGreen);
   GTkIsoEGR.SetMarkerColor(kYellow);
   GTkEMR.SetMarkerColor(kRed);

   GTkEGR2.SetMarkerColor(kBlack);
   GTkEG2R2.SetMarkerColor(kGreen);
   GTkIsoEGR2.SetMarkerColor(kYellow);
   GTkEMR2.SetMarkerColor(kRed);

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";Isolation Cut;Efficiency", 100, 0, 0.5, 100, 0.75, 1.01);
   HWorld.SetStats(0);

   HWorld.SetTitle("Full range (|eta| < 2.4, no PT cut)");
   HWorld.Draw("axis");
   if(IsEle == true)
   {
      GTkEG.Draw("p");
      GTkEG2.Draw("p");
      GTkIsoEG.Draw("p");
   }
   else
      GTkEM.Draw("p");

   GTkEG.SetMarkerSize(1.0);
   GTkEG2.SetMarkerSize(0.9);
   GTkIsoEG.SetMarkerSize(0.8);
   GTkEM.SetMarkerSize(0.7);

   TLegend Legend(0.6, 0.2, 0.8, 0.4);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   if(IsEle == true)
   {
      Legend.AddEntry(&GTkEG, "TkEG", "p");
      Legend.AddEntry(&GTkEG2, "TkEG2", "p");
      Legend.AddEntry(&GTkIsoEG, "TkIsoEG", "p");
   }
   else
      Legend.AddEntry(&GTkEM, "TkEM", "p");
   Legend.Draw();

   TGraph G1, G2, G3;
   G1.SetPoint(0, 0, 1);
   G1.SetPoint(1, 1, 1);
   G2.SetPoint(0, 0, 0.95);
   G2.SetPoint(1, 1, 0.95);
   G3.SetPoint(0, 0, 0.97);
   G3.SetPoint(1, 1, 0.97);

   G2.SetLineStyle(kDashed);
   G3.SetLineStyle(kDashed);

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   PdfFile.AddCanvas(Canvas);
   
   HWorld.SetTitle("Smaller range (|eta| < 1.5, gen-PT > 20)");
   HWorld.Draw("axis");
   if(IsEle == true)
   {
      GTkEGR.Draw("p");
      GTkEG2R.Draw("p");
      GTkIsoEGR.Draw("p");
   }
   else
      GTkEMR.Draw("p");
   
   GTkEGR.SetMarkerSize(1.0);
   GTkEG2R.SetMarkerSize(0.9);
   GTkIsoEGR.SetMarkerSize(0.8);
   GTkEMR.SetMarkerSize(0.7);

   Legend.Draw();
   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Smaller range (|eta| < 2.0, gen-PT > 20)");
   HWorld.Draw("axis");
   if(IsEle == true)
   {
      GTkEGR2.Draw("p");
      GTkEG2R2.Draw("p");
      GTkIsoEGR2.Draw("p");
   }
   else
      GTkEMR2.Draw("p");

   GTkEGR2.SetMarkerSize(1.0);
   GTkEG2R2.SetMarkerSize(0.9);
   GTkIsoEGR2.SetMarkerSize(0.8);
   GTkEMR2.SetMarkerSize(0.7);

   Legend.Draw();
   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   PdfFile.AddCanvas(Canvas);

   File.Close();
}

void FillGraphFromHistogram(TGraph &G, TH1D *H)
{
   G.Set(0);

   if(H == NULL)
      return;

   cout << H->GetName() << endl;

   int N = H->GetNbinsX();
   double Total = 0;
   double Integral = H->Integral();
   for(int i = 1; i <= N; i++)
   {
      G.SetPoint(G.GetN(), H->GetXaxis()->GetBinLowEdge(i), Total / Integral);
      Total = Total + H->GetBinContent(i);
   }
}





