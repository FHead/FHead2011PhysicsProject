#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   TFile File("FullTree.root");

   TFile OutputFile("Histograms.root", "RECREATE");
   TDirectory *Directory = OutputFile.mkdir("Special");

   TH1D HAllTau ("Special_HAllTau",  ";;", 33, 0, 198);
   TH1D HCaloTau("Special_HCaloTau", ";;", 33, 0, 198);
   TH1D HTkEGTau("Special_HTkEGTau", ";;", 33, 0, 198);
   TH1D HNNPFTau("Special_HNNPFTau", ";;", 33, 0, 198);

   double Bins[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 45, 50, 55, 60, 65, 70, 75, 80, 90, 100, 120, 150, 250, 500};

   TH1D HAllDiTau  ("Special_HAllDiTau",   ";;", 23, Bins);
   TH1D HCaloDiTau ("Special_HCaloDiTau",  ";;", 23, Bins);
   TH1D HTkEGDiTau ("Special_HTkEGDiTau",  ";;", 23, Bins);
   TH1D HNNPFDiTau ("Special_HNNPFDiTau",  ";;", 23, Bins);
   TH1D HCaloDiTauZ("Special_HCaloDiTauZ", ";;", 23, Bins);
   TH1D HTkEGDiTauZ("Special_HTkEGDiTauZ", ";;", 23, Bins);
   TH1D HNNPFDiTauZ("Special_HNNPFDiTauZ", ";;", 23, Bins);

   TH2D HWorld("HWorld", ";;", 50, 0, 200, 100, 0, 1.1);
   HWorld.SetStats(0);

   TTree *Tree = (TTree *)File.Get("Tree");

   Tree->Draw("GenTau1PT>>Special_HAllTau",  "GenTau1PT > 0 && abs(GenTau1Eta) < 1.5");
   Tree->Draw("GenTau1PT>>Special_HCaloTau", "GenTau1PT > 0 && abs(GenTau1Eta) < 1.5 && CaloTau1PT > 58");
   Tree->Draw("GenTau1PT>>Special_HTkEGTau", "GenTau1PT > 0 && abs(GenTau1Eta) < 1.5 && TkEGTau1PT > 35");
   Tree->Draw("GenTau1PT>>Special_HNNPFTau", "GenTau1PT > 0 && abs(GenTau1Eta) < 1.5 && NNPFTau1PT > 36");

   Tree->Draw("GenTau2PT>>Special_HAllDiTau",   "GenTau1PT > 0 && GenTau2PT > 0 && GenTauDR > 0.5");
   Tree->Draw("GenTau2PT>>Special_HCaloDiTau",  "GenTau1PT > 0 && GenTau2PT > 0 && GenTauDR > 0.5 && CaloTau1PT > 90 && CaloTau2PT > 90 && CaloTauDR > 0.5");
   Tree->Draw("GenTau2PT>>Special_HTkEGDiTau",  "GenTau1PT > 0 && GenTau2PT > 0 && GenTauDR > 0.5 && TkEGTau1PT > 35 && TkEGTau2PT > 35 && TkEGTauDR > 0.5");
   Tree->Draw("GenTau2PT>>Special_HNNPFDiTau",  "GenTau1PT > 0 && GenTau2PT > 0 && GenTauDR > 0.5 && NNPFTau1PT > 36 && NNPFTau2PT > 36 && NNPFTauDR > 0.5");
   Tree->Draw("GenTau2PT>>Special_HTkEGDiTauZ", "GenTau1PT > 0 && GenTau2PT > 0 && GenTauDR > 0.5 && TkEGTau1PT > 33 && TkEGTau2PT > 33 && TkEGTauDR > 0.5 && abs(TkEGTau1VZ - TkEGTau2VZ) < 1");

   PdfFileHelper PdfFile("Meow.pdf");
   PdfFile.AddTextPage("Tau plots");

   TGraphAsymmErrors GCaloTau, GTkEGTau, GNNPFTau;
   GCaloTau.Divide(&HCaloTau, &HAllTau);
   GTkEGTau.Divide(&HTkEGTau, &HAllTau);
   GNNPFTau.Divide(&HNNPFTau, &HAllTau);
   
   TGraphAsymmErrors GCaloDiTau, GTkEGDiTau, GNNPFDiTau;
   TGraphAsymmErrors GCaloDiTauZ, GTkEGDiTauZ, GNNPFDiTauZ;
   GCaloDiTau.Divide(&HCaloDiTau, &HAllDiTau);
   GTkEGDiTau.Divide(&HTkEGDiTau, &HAllDiTau);
   GNNPFDiTau.Divide(&HNNPFDiTau, &HAllDiTau);
   GCaloDiTauZ.Divide(&HCaloDiTauZ, &HAllDiTau);
   GTkEGDiTauZ.Divide(&HTkEGDiTauZ, &HAllDiTau);
   GNNPFDiTauZ.Divide(&HNNPFDiTauZ, &HAllDiTau);

   PdfFile.AddPlot(HAllTau);
   PdfFile.AddPlot(HCaloTau);
   PdfFile.AddPlot(HTkEGTau);
   PdfFile.AddPlot(HNNPFTau);
   PdfFile.AddPlot(HAllDiTau);
   PdfFile.AddPlot(HCaloDiTau);
   PdfFile.AddPlot(HTkEGDiTau);
   PdfFile.AddPlot(HNNPFDiTau);
   PdfFile.AddPlot(HCaloDiTauZ);
   PdfFile.AddPlot(HTkEGDiTauZ);
   PdfFile.AddPlot(HNNPFDiTauZ);

   int Colors[4] = {0, 0, 0, 0};
   Colors[0] = TColor::GetColor("#2ECC71");
   Colors[1] = TColor::GetColor("#F1C40F");
   Colors[2] = TColor::GetColor("#3498DB");
   Colors[3] = TColor::GetColor("#E74C3C");

   GCaloTau.SetLineWidth(2);
   GCaloTau.SetMarkerSize(2);
   GCaloTau.SetLineColor(Colors[0]);
   GCaloTau.SetMarkerColor(Colors[0]);
   GTkEGTau.SetLineWidth(2);
   GTkEGTau.SetMarkerSize(2);
   GTkEGTau.SetLineColor(Colors[1]);
   GTkEGTau.SetMarkerColor(Colors[1]);
   GNNPFTau.SetLineWidth(2);
   GNNPFTau.SetMarkerSize(2);
   GNNPFTau.SetLineColor(Colors[2]);
   GNNPFTau.SetMarkerColor(Colors[2]);
   GCaloDiTau.SetLineWidth(2);
   GCaloDiTau.SetMarkerSize(2);
   GCaloDiTau.SetLineColor(Colors[0]);
   GCaloDiTau.SetMarkerColor(Colors[0]);
   GTkEGDiTau.SetLineWidth(2);
   GTkEGDiTau.SetMarkerSize(2);
   GTkEGDiTau.SetLineColor(Colors[1]);
   GTkEGDiTau.SetMarkerColor(Colors[1]);
   GNNPFDiTau.SetLineWidth(2);
   GNNPFDiTau.SetMarkerSize(2);
   GNNPFDiTau.SetLineColor(Colors[2]);
   GNNPFDiTau.SetMarkerColor(Colors[2]);
   GTkEGDiTauZ.SetLineWidth(2);
   GTkEGDiTauZ.SetMarkerSize(2);
   GTkEGDiTauZ.SetLineColor(Colors[3]);
   GTkEGDiTauZ.SetMarkerColor(Colors[3]);

   TCanvas Canvas;
   HWorld.Draw("axis");
   GCaloTau.Draw("pl");
   GTkEGTau.Draw("pl");
   GNNPFTau.Draw("pl");
   PdfFile.AddCanvas(Canvas);
   
   HWorld.Draw("axis");
   GCaloDiTau.Draw("pl");
   GTkEGDiTau.Draw("pl");
   GNNPFDiTau.Draw("pl");
   GTkEGDiTauZ.Draw("pl");
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   Directory->cd();

   HAllTau.Write();
   HCaloTau.Write();
   HTkEGTau.Write();
   HNNPFTau.Write();
   
   HAllDiTau.Write();
   HCaloDiTau.Write();
   HTkEGDiTau.Write();
   HNNPFDiTau.Write();
   HCaloDiTauZ.Write();
   HTkEGDiTauZ.Write();
   HNNPFDiTauZ.Write();

   OutputFile.Close();

   File.Close();

   return 0;
}



