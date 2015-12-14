#include <iostream>
using namespace std;

#include "SetStyle.h"
#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLatex.h"

int main();
void PrepareHistogram(TH2D *H);

int main()
{
   SetStyle();

   TFile F1("PlotsFromFirstData50ns6723/SingleMu_All.root");
   TFile F2("PlotsFromFirstData50ns6723/METBTag_All.root");
   TFile F3("PlotsFromFirstData50ns6723/HcalHPDNoise_All.root");
   TFile F4("PlotsFromFirstData50ns6723/HT_All.root");
   TFile F5("PlotsFromFirstData50ns6723/MinimumBias_All.root");
   TFile F6("PlotsFromFirstData50ns6723/Jet_All.root");
   TFile F7("PlotsFromFirstData50ns6723/MultiJet_All.root");

   TH2D *H1 = (TH2D *)F1.Get("HHBHEMETVsHBHEMETRound12");
   TH2D *H2 = (TH2D *)F2.Get("HHBHEMETVsHBHEMETRound12");
   TH2D *H3 = (TH2D *)F3.Get("HHBHEMETVsHBHEMETRound12");
   TH2D *H4 = (TH2D *)F4.Get("HHBHEMETVsHBHEMETRound12");
   TH2D *H5 = (TH2D *)F5.Get("HHBHEMETVsHBHEMETRound12");
   TH2D *H6 = (TH2D *)F6.Get("HHBHEMETVsHBHEMETRound12");
   TH2D *H7 = (TH2D *)F7.Get("HHBHEMETVsHBHEMETRound12");

   PrepareHistogram(H1);
   PrepareHistogram(H2);
   PrepareHistogram(H3);
   PrepareHistogram(H4);
   PrepareHistogram(H5);
   PrepareHistogram(H6);
   PrepareHistogram(H7);

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetNDC();
   Latex.SetTextAlign(13);
   Latex.SetTextSize(0.035);

   TCanvas C("C", "C", 1024, 1024);
   C.SetLogz();

   H1->Draw("colz");
   Latex.DrawLatex(0.15, 0.85, "SingleMu dataset");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance1.png");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance1.C");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance1.eps");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance1.pdf");

   H2->Draw("colz");
   Latex.DrawLatex(0.15, 0.85, "METBTag dataset");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance2.png");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance2.C");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance2.eps");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance2.pdf");

   H3->Draw("colz");
   Latex.DrawLatex(0.15, 0.85, "HcalHPDNoise dataset");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance3.png");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance3.C");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance3.eps");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance3.pdf");

   H4->Draw("colz");
   Latex.DrawLatex(0.15, 0.85, "HT dataset");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance4.png");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance4.C");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance4.eps");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance4.pdf");

   H5->Draw("colz");
   Latex.DrawLatex(0.15, 0.85, "MinimumBias dataset");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance5.png");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance5.C");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance5.eps");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance5.pdf");

   H6->Draw("colz");
   Latex.DrawLatex(0.15, 0.85, "Jet dataset");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance6.png");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance6.C");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance6.eps");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance6.pdf");

   H7->Draw("colz");
   Latex.DrawLatex(0.15, 0.85, "MultiJet dataset");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance7.png");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance7.C");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance7.eps");
   C.SaveAs("HcalNoise-FitBasedFilter-Performance7.pdf");

   F7.Close();
   F6.Close();
   F5.Close();
   F4.Close();
   F3.Close();
   F2.Close();
   F1.Close();

   return 0;
}

void PrepareHistogram(TH2D *H)
{
   if(H == NULL)
      return;

   H->SetTitle("");
   H->SetStats(0);
   H->GetXaxis()->SetTitle("MET Before Cleaning (GeV)");
   H->GetYaxis()->SetTitle("MET After Cleaning (GeV)");
   H->GetXaxis()->SetTitleOffset(1.1);
   H->GetYaxis()->SetTitleOffset(1.4);
   H->GetXaxis()->SetTitleSize(0.035);
   H->GetYaxis()->SetTitleSize(0.035);
   H->GetZaxis()->SetTitleSize(0.035);
   H->GetXaxis()->SetLabelSize(0.035);
   H->GetYaxis()->SetLabelSize(0.035);
   H->GetZaxis()->SetLabelSize(0.035);
   H->GetXaxis()->SetLabelFont(42);
   H->GetYaxis()->SetLabelFont(42);
   H->GetZaxis()->SetLabelFont(42);
   H->GetXaxis()->SetTitleFont(42);
   H->GetYaxis()->SetTitleFont(42);
   H->GetZaxis()->SetTitleFont(42);
}




