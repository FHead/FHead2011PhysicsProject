#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TGraph.h"
#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void AddPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix, bool LogY, double L, double R, double B, double T, string Title);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("ResultGenLevel.pdf");
   PdfFile.AddTextPage("Gen Level Quantities");

   TFile File("Histograms.root");

   AddPlot(PdfFile, File, "HPTHat",      true,  0, 600, 1, 1e9, ";PT Hat;");
   AddPlot(PdfFile, File, "HGenPT",      true,  0, 20,  1e6, 1e10, ";PT;");
   AddPlot(PdfFile, File, "HGenEta",     false, -2, 2, 0, 5e8, ";Eta;");
   AddPlot(PdfFile, File, "HGenPhi",     false, -M_PI, M_PI, 0, 5e8, ";Phi;");
   AddPlot(PdfFile, File, "HGenEta_PT5", false, -2, 2, 0, 5e7, "PT > 5;Eta;");
  
   ((TH1D *)File.Get("HGenEtaPhi_PT5_AA"))->SetMinimum(0);
   ((TH1D *)File.Get("HGenEtaPhi_PT5_PP"))->SetMinimum(0);
   ((TH1D *)File.Get("HGenEtaPhi_PT5_PPHIReco"))->SetMinimum(0);
   
   ((TH1D *)File.Get("HGenEtaPhi_PT5_AA"))->SetMaximum(450000);
   ((TH1D *)File.Get("HGenEtaPhi_PT5_PP"))->SetMaximum(450000);
   ((TH1D *)File.Get("HGenEtaPhi_PT5_PPHIReco"))->SetMaximum(450000);

   PdfFile.AddHistogramFromFile(File, "HGenEtaPhi_PT5_AA", "colz");
   PdfFile.AddHistogramFromFile(File, "HGenEtaPhi_PT5_PP", "colz");
   PdfFile.AddHistogramFromFile(File, "HGenEtaPhi_PT5_PPHIReco", "colz");
   
   AddPlot(PdfFile, File, "HType_PT5",   true, 0, 14, 1e6, 1e12, "PT > 5;Type;");

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix, bool LogY, double L, double R, double B, double T, string Title)
{
   TH1D *H1 = (TH1D *)File.Get((Prefix + "_AA").c_str());
   TH1D *H2 = (TH1D *)File.Get((Prefix + "_PP").c_str());
   TH1D *H3 = (TH1D *)File.Get((Prefix + "_PPHIReco").c_str());

   if(H1 == NULL && H2 == NULL && H3 == NULL)
      return;

   TH2D HWorld("HWorld", Title.c_str(), 14, L, R, 100, B, T);
   HWorld.SetStats(0);

   if(Prefix == "HType_PT5")
   {
      HWorld.GetXaxis()->SetBinLabel(1, "u");
      HWorld.GetXaxis()->SetBinLabel(2, "#bar{u}");
      HWorld.GetXaxis()->SetBinLabel(3, "d");
      HWorld.GetXaxis()->SetBinLabel(4, "#bar{d}");
      HWorld.GetXaxis()->SetBinLabel(5, "s");
      HWorld.GetXaxis()->SetBinLabel(6, "#bar{s}");
      HWorld.GetXaxis()->SetBinLabel(7, "c");
      HWorld.GetXaxis()->SetBinLabel(8, "#bar{c}");
      HWorld.GetXaxis()->SetBinLabel(9, "b");
      HWorld.GetXaxis()->SetBinLabel(10, "#bar{b}");
      HWorld.GetXaxis()->SetBinLabel(11, "Gluon");
      HWorld.GetXaxis()->SetBinLabel(12, "Photon");
      HWorld.GetXaxis()->SetBinLabel(13, "Lepton");
      HWorld.GetXaxis()->SetBinLabel(14, "Others");
   }

   TCanvas C;

   HWorld.Draw();

   if(H1)   H1->SetMarkerColor(kRed);
   if(H2)   H2->SetMarkerColor(kBlue);
   if(H3)   H3->SetMarkerColor(kGreen);

   if(H1)   H1->SetLineColor(kRed);
   if(H2)   H2->SetLineColor(kBlue);
   if(H3)   H3->SetLineColor(kGreen);

   if(H1)   H1->Draw("same");
   if(H2)   H2->Draw("same");
   if(H2)   H3->Draw("same");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   if(H1)   Legend.AddEntry(H1, "Embedded", "lp");
   if(H2)   Legend.AddEntry(H2, "pp", "lp");
   if(H3)   Legend.AddEntry(H3, "pp (HI Reco)", "lp");
   Legend.Draw();

   if(LogY == true)
      C.SetLogy();

   PdfFile.AddCanvas(C);
}






