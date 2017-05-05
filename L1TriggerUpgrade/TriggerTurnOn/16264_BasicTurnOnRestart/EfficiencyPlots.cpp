#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
TGraphAsymmErrors *Divide(TFile &F1, string N1, TFile &F2, string N2, int Rebin = 1);
void AddFourPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEG140, TGraphAsymmErrors *TkEG200,
   TGraphAsymmErrors *TkIsoEG140, TGraphAsymmErrors *TkIsoEG200, string Title);
void AddTwoPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEM140, TGraphAsymmErrors *TkEM200, string Title);
void AddSpectrum(PdfFileHelper &PdfFile, TFile &F, string N, string Title);

int main()
{
   SetThesisStyle();

   TFile FWENu140("Result/Combined/WToEnu140PU.root");
   TFile FWENu200("Result/Combined/WToEnu200PU.root");
   TFile FHgg140("Result/Combined/Hgg140PU.root");
   TFile FHgg200("Result/Combined/Hgg200PU.root");

   TGraphAsymmErrors *TkEG_140_PT = Divide(FWENu140, "TkEG/TkEG_PT_000000",
      FWENu140, "TkEG/TkEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkEG_140_PT_Rebin = Divide(FWENu140, "TkEG/TkEG_PT_000000",
      FWENu140, "TkEG/TkEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkEG_140_PTEta10 = Divide(FWENu140, "TkEG/TkEG_PTEta10_000000",
      FWENu140, "TkEG/TkEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkEG_140_PTEta10_Rebin = Divide(FWENu140, "TkEG/TkEG_PTEta10_000000",
      FWENu140, "TkEG/TkEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkEG_140_PTEtaLarge = Divide(FWENu140, "TkEG/TkEG_PTEtaLarge_000000",
      FWENu140, "TkEG/TkEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkEG_140_PTEtaLarge_Rebin = Divide(FWENu140, "TkEG/TkEG_PTEtaLarge_000000",
      FWENu140, "TkEG/TkEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkEG_140_Eta = Divide(FWENu140, "TkEG/TkEG_Eta_000000",
      FWENu140, "TkEG/TkEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkEG_140_EtaPT20 = Divide(FWENu140, "TkEG/TkEG_EtaPT20_000000",
      FWENu140, "TkEG/TkEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkEG_140_EtaPT25 = Divide(FWENu140, "TkEG/TkEG_EtaPT25_000000",
      FWENu140, "TkEG/TkEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkEG_200_PT = Divide(FWENu200, "TkEG/TkEG_PT_000000",
      FWENu200, "TkEG/TkEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkEG_200_PT_Rebin = Divide(FWENu200, "TkEG/TkEG_PT_000000",
      FWENu200, "TkEG/TkEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkEG_200_PTEta10 = Divide(FWENu200, "TkEG/TkEG_PTEta10_000000",
      FWENu200, "TkEG/TkEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkEG_200_PTEta10_Rebin = Divide(FWENu200, "TkEG/TkEG_PTEta10_000000",
      FWENu200, "TkEG/TkEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkEG_200_PTEtaLarge = Divide(FWENu200, "TkEG/TkEG_PTEtaLarge_000000",
      FWENu200, "TkEG/TkEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkEG_200_PTEtaLarge_Rebin = Divide(FWENu200, "TkEG/TkEG_PTEtaLarge_000000",
      FWENu200, "TkEG/TkEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkEG_200_Eta = Divide(FWENu200, "TkEG/TkEG_Eta_000000",
      FWENu200, "TkEG/TkEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkEG_200_EtaPT20 = Divide(FWENu200, "TkEG/TkEG_EtaPT20_000000",
      FWENu200, "TkEG/TkEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkEG_200_EtaPT25 = Divide(FWENu200, "TkEG/TkEG_EtaPT25_000000",
      FWENu200, "TkEG/TkEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkIsoEG_140_PT = Divide(FWENu140, "TkIsoEG/TkIsoEG_PT_000000",
      FWENu140, "TkIsoEG/TkIsoEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkIsoEG_140_PT_Rebin = Divide(FWENu140, "TkIsoEG/TkIsoEG_PT_000000",
      FWENu140, "TkIsoEG/TkIsoEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkIsoEG_140_PTEta10 = Divide(FWENu140, "TkIsoEG/TkIsoEG_PTEta10_000000",
      FWENu140, "TkIsoEG/TkIsoEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkIsoEG_140_PTEta10_Rebin = Divide(FWENu140, "TkIsoEG/TkIsoEG_PTEta10_000000",
      FWENu140, "TkIsoEG/TkIsoEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkIsoEG_140_PTEtaLarge = Divide(FWENu140, "TkIsoEG/TkIsoEG_PTEtaLarge_000000",
      FWENu140, "TkIsoEG/TkIsoEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkIsoEG_140_PTEtaLarge_Rebin = Divide(FWENu140, "TkIsoEG/TkIsoEG_PTEtaLarge_000000",
      FWENu140, "TkIsoEG/TkIsoEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkIsoEG_140_Eta = Divide(FWENu140, "TkIsoEG/TkIsoEG_Eta_000000",
      FWENu140, "TkIsoEG/TkIsoEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkIsoEG_140_EtaPT20 = Divide(FWENu140, "TkIsoEG/TkIsoEG_EtaPT20_000000",
      FWENu140, "TkIsoEG/TkIsoEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkIsoEG_140_EtaPT25 = Divide(FWENu140, "TkIsoEG/TkIsoEG_EtaPT25_000000",
      FWENu140, "TkIsoEG/TkIsoEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkIsoEG_200_PT = Divide(FWENu200, "TkIsoEG/TkIsoEG_PT_000000",
      FWENu200, "TkIsoEG/TkIsoEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkIsoEG_200_PT_Rebin = Divide(FWENu200, "TkIsoEG/TkIsoEG_PT_000000",
      FWENu200, "TkIsoEG/TkIsoEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkIsoEG_200_PTEta10 = Divide(FWENu200, "TkIsoEG/TkIsoEG_PTEta10_000000",
      FWENu200, "TkIsoEG/TkIsoEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkIsoEG_200_PTEta10_Rebin = Divide(FWENu200, "TkIsoEG/TkIsoEG_PTEta10_000000",
      FWENu200, "TkIsoEG/TkIsoEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkIsoEG_200_PTEtaLarge = Divide(FWENu200, "TkIsoEG/TkIsoEG_PTEtaLarge_000000",
      FWENu200, "TkIsoEG/TkIsoEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkIsoEG_200_PTEtaLarge_Rebin = Divide(FWENu200, "TkIsoEG/TkIsoEG_PTEtaLarge_000000",
      FWENu200, "TkIsoEG/TkIsoEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkIsoEG_200_Eta = Divide(FWENu200, "TkIsoEG/TkIsoEG_Eta_000000",
      FWENu200, "TkIsoEG/TkIsoEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkIsoEG_200_EtaPT20 = Divide(FWENu200, "TkIsoEG/TkIsoEG_EtaPT20_000000",
      FWENu200, "TkIsoEG/TkIsoEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkIsoEG_200_EtaPT25 = Divide(FWENu200, "TkIsoEG/TkIsoEG_EtaPT25_000000",
      FWENu200, "TkIsoEG/TkIsoEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkEM_140_PT = Divide(FHgg140, "TkEM/TkEM_PT_000000",
      FHgg140, "TkEM/TkEMNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkEM_140_PT_Rebin = Divide(FHgg140, "TkEM/TkEM_PT_000000",
      FHgg140, "TkEM/TkEMNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkEM_140_PTEta10 = Divide(FHgg140, "TkEM/TkEM_PTEta10_000000",
      FHgg140, "TkEM/TkEMNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkEM_140_PTEta10_Rebin = Divide(FHgg140, "TkEM/TkEM_PTEta10_000000",
      FHgg140, "TkEM/TkEMNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkEM_140_PTEtaLarge = Divide(FHgg140, "TkEM/TkEM_PTEtaLarge_000000",
      FHgg140, "TkEM/TkEMNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkEM_140_PTEtaLarge_Rebin = Divide(FHgg140, "TkEM/TkEM_PTEtaLarge_000000",
      FHgg140, "TkEM/TkEMNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkEM_140_Eta = Divide(FHgg140, "TkEM/TkEM_Eta_000000",
      FHgg140, "TkEM/TkEMNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkEM_140_EtaPT20 = Divide(FHgg140, "TkEM/TkEM_EtaPT20_000000",
      FHgg140, "TkEM/TkEMNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkEM_140_EtaPT25 = Divide(FHgg140, "TkEM/TkEM_EtaPT25_000000",
      FHgg140, "TkEM/TkEMNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkEM_200_PT = Divide(FHgg200, "TkEM/TkEM_PT_000000",
      FHgg200, "TkEM/TkEMNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkEM_200_PT_Rebin = Divide(FHgg200, "TkEM/TkEM_PT_000000",
      FHgg200, "TkEM/TkEMNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkEM_200_PTEta10 = Divide(FHgg200, "TkEM/TkEM_PTEta10_000000",
      FHgg200, "TkEM/TkEMNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkEM_200_PTEta10_Rebin = Divide(FHgg200, "TkEM/TkEM_PTEta10_000000",
      FHgg200, "TkEM/TkEMNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkEM_200_PTEtaLarge = Divide(FHgg200, "TkEM/TkEM_PTEtaLarge_000000",
      FHgg200, "TkEM/TkEMNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkEM_200_PTEtaLarge_Rebin = Divide(FHgg200, "TkEM/TkEM_PTEtaLarge_000000",
      FHgg200, "TkEM/TkEMNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkEM_200_Eta = Divide(FHgg200, "TkEM/TkEM_Eta_000000",
      FHgg200, "TkEM/TkEMNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkEM_200_EtaPT20 = Divide(FHgg200, "TkEM/TkEM_EtaPT20_000000",
      FHgg200, "TkEM/TkEMNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkEM_200_EtaPT25 = Divide(FHgg200, "TkEM/TkEM_EtaPT25_000000",
      FHgg200, "TkEM/TkEMNoMatching_EtaPT25_000000", 2);

   TkEG_140_PT->SetTitle("TkEG, PT, PU140");
   TkEG_140_PT_Rebin->SetTitle("TkEG, PT, PU140");
   TkEG_140_PTEta10->SetTitle("TkEG, PT (|eta| > 1.0), PU140");
   TkEG_140_PTEta10_Rebin->SetTitle("TkEG, PT (|eta| > 1.0), PU140");
   TkEG_140_PTEtaLarge->SetTitle("TkEG, PT (|eta| < 1.0), PU140");
   TkEG_140_PTEtaLarge_Rebin->SetTitle("TkEG, PT (|eta| < 1.0), PU140");
   TkEG_140_Eta->SetTitle("TkEG, Eta, PU140");
   TkEG_140_EtaPT20->SetTitle("TkEG, eta (PT > 20), PU140");
   TkEG_140_EtaPT25->SetTitle("TkEG, eta (PT > 25), PU140");
   TkEG_200_PT->SetTitle("TkEG, PT, PU200");
   TkEG_200_PT_Rebin->SetTitle("TkEG, PT, PU200");
   TkEG_200_PTEta10->SetTitle("TkEG, PT (|eta| > 1.0), PU200");
   TkEG_200_PTEta10_Rebin->SetTitle("TkEG, PT (|eta| > 1.0), PU200");
   TkEG_200_PTEtaLarge->SetTitle("TkEG, PT (|eta| < 1.0), PU200");
   TkEG_200_PTEtaLarge_Rebin->SetTitle("TkEG, PT (|eta| < 1.0), PU200");
   TkEG_200_Eta->SetTitle("TkEG, Eta, PU200");
   TkEG_200_EtaPT20->SetTitle("TkEG, eta (PT > 20), PU200");
   TkEG_200_EtaPT25->SetTitle("TkEG, eta (PT > 25), PU200");
   TkIsoEG_140_PT->SetTitle("TkIsoEG, PT, PU140");
   TkIsoEG_140_PT_Rebin->SetTitle("TkIsoEG, PT, PU140");
   TkIsoEG_140_PTEta10->SetTitle("TkIsoEG, PT (|eta| > 1.0), PU140");
   TkIsoEG_140_PTEta10_Rebin->SetTitle("TkIsoEG, PT (|eta| > 1.0), PU140");
   TkIsoEG_140_PTEtaLarge->SetTitle("TkIsoEG, PT (|eta| < 1.0), PU140");
   TkIsoEG_140_PTEtaLarge_Rebin->SetTitle("TkIsoEG, PT (|eta| < 1.0), PU140");
   TkIsoEG_140_Eta->SetTitle("TkIsoEG, Eta, PU140");
   TkIsoEG_140_EtaPT20->SetTitle("TkIsoEG, eta (PT > 20), PU140");
   TkIsoEG_140_EtaPT25->SetTitle("TkIsoEG, eta (PT > 25), PU140");
   TkIsoEG_200_PT->SetTitle("TkIsoEG, PT, PU200");
   TkIsoEG_200_PT_Rebin->SetTitle("TkIsoEG, PT, PU200");
   TkIsoEG_200_PTEta10->SetTitle("TkIsoEG, PT (|eta| < 1.0), PU200");
   TkIsoEG_200_PTEta10_Rebin->SetTitle("TkIsoEG, PT (|eta| < 1.0), PU200");
   TkIsoEG_200_PTEtaLarge->SetTitle("TkIsoEG, PT (|eta| > 1.0), PU200");
   TkIsoEG_200_PTEtaLarge_Rebin->SetTitle("TkIsoEG, PT (|eta| > 1.0), PU200");
   TkIsoEG_200_Eta->SetTitle("TkIsoEG, Eta, PU200");
   TkIsoEG_200_EtaPT20->SetTitle("TkIsoEG, eta (PT > 20), PU200");
   TkIsoEG_200_EtaPT25->SetTitle("TkIsoEG, eta (PT > 25), PU200");
   TkEM_140_PT->SetTitle("TkEM, PT, PU140");
   TkEM_140_PT_Rebin->SetTitle("TkEM, PT, PU140");
   TkEM_140_PTEta10->SetTitle("TkEM, PT (|eta| > 1.0), PU140");
   TkEM_140_PTEta10_Rebin->SetTitle("TkEM, PT (|eta| > 1.0), PU140");
   TkEM_140_PTEtaLarge->SetTitle("TkEM, PT (|eta| < 1.0), PU140");
   TkEM_140_PTEtaLarge_Rebin->SetTitle("TkEM, PT (|eta| < 1.0), PU140");
   TkEM_140_Eta->SetTitle("TkEM, Eta, PU140");
   TkEM_140_EtaPT20->SetTitle("TkEM, eta (PT > 20), PU140");
   TkEM_140_EtaPT25->SetTitle("TkEM, eta (PT > 25), PU140");
   TkEM_200_PT->SetTitle("TkEM, PT, PU200");
   TkEM_200_PT_Rebin->SetTitle("TkEM, PT, PU200");
   TkEM_200_PTEta10->SetTitle("TkEM, PT (|eta| > 1.0), PU200");
   TkEM_200_PTEta10_Rebin->SetTitle("TkEM, PT (|eta| > 1.0), PU200");
   TkEM_200_PTEtaLarge->SetTitle("TkEM, PT (|eta| < 1.0), PU200");
   TkEM_200_PTEtaLarge_Rebin->SetTitle("TkEM, PT (|eta| < 1.0), PU200");
   TkEM_200_Eta->SetTitle("TkEM, Eta, PU200");
   TkEM_200_EtaPT20->SetTitle("TkEM, eta (PT > 20), PU200");
   TkEM_200_EtaPT25->SetTitle("TkEM, eta (PT > 25), PU200");

   TkEG_140_PT->GetXaxis()->SetTitle("PT");
   TkEG_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkEG_140_PTEta10->GetXaxis()->SetTitle("PT");
   TkEG_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkEG_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkEG_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkEG_140_Eta->GetXaxis()->SetTitle("Eta");
   TkEG_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkEG_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkEG_200_PT->GetXaxis()->SetTitle("PT");
   TkEG_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkEG_200_PTEta10->GetXaxis()->SetTitle("PT");
   TkEG_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkEG_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkEG_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkEG_200_Eta->GetXaxis()->SetTitle("Eta");
   TkEG_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkEG_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkIsoEG_140_PT->GetXaxis()->SetTitle("PT");
   TkIsoEG_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEG_140_PTEta10->GetXaxis()->SetTitle("PT");
   TkIsoEG_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEG_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkIsoEG_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEG_140_Eta->GetXaxis()->SetTitle("Eta");
   TkIsoEG_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkIsoEG_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkIsoEG_200_PT->GetXaxis()->SetTitle("PT");
   TkIsoEG_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEG_200_PTEta10->GetXaxis()->SetTitle("PT");
   TkIsoEG_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEG_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkIsoEG_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEG_200_Eta->GetXaxis()->SetTitle("Eta");
   TkIsoEG_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkIsoEG_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkEM_140_PT->GetXaxis()->SetTitle("PT");
   TkEM_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkEM_140_PTEta10->GetXaxis()->SetTitle("PT");
   TkEM_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkEM_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkEM_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkEM_140_Eta->GetXaxis()->SetTitle("Eta");
   TkEM_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkEM_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkEM_200_PT->GetXaxis()->SetTitle("PT");
   TkEM_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkEM_200_PTEta10->GetXaxis()->SetTitle("PT");
   TkEM_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkEM_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkEM_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkEM_200_Eta->GetXaxis()->SetTitle("Eta");
   TkEM_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkEM_200_EtaPT25->GetXaxis()->SetTitle("Eta");

   PdfFileHelper PdfFile("ResultEfficiencyPlots.pdf");
   PdfFile.AddTextPage("Efficiency plots");

   vector<string> Explanation(15);
   Explanation[0] = "Look at gen-electron pt/eta for those within acceptance";
   Explanation[1] = "";
   Explanation[2] = "Numerator = Gen-particle spectrum";
   Explanation[3] = "Denominator = Gen-particle spectrum & track";
   Explanation[4] = "      EG/IsoEG/EM object match";
   Explanation[5] = "";
   Explanation[6] = "Electron ones from W->e#nu sample";
   Explanation[7] = "EM ones from H->#gamma#gamma sample";
   Explanation[8] = "";
   Explanation[9] = "Watch out for PT spectrum!";
   PdfFile.AddTextPage(Explanation);

   PdfFile.AddTextPage("Gen-spectra");

   AddSpectrum(PdfFile, FWENu140, "TkEG/TkEGNoMatching_PT_000000",  "W->e#nu electrons (PU 140)");
   AddSpectrum(PdfFile, FWENu200, "TkEG/TkEGNoMatching_PT_000000",  "W->e#nu electrons (PU 200)");
   AddSpectrum(PdfFile, FWENu140, "TkEG/TkEGNoMatching_Eta_000000", "W->e#nu electrons (PU 140)");
   AddSpectrum(PdfFile, FWENu200, "TkEG/TkEGNoMatching_Eta_000000", "W->e#nu electrons (PU 200)");
   AddSpectrum(PdfFile, FHgg140,  "TkEM/TkEMNoMatching_PT_000000",  "H->#gamma#gamma photons (PU 140)");
   AddSpectrum(PdfFile, FHgg200,  "TkEM/TkEMNoMatching_PT_000000",  "H->#gamma#gamma photons (PU 200)");
   AddSpectrum(PdfFile, FHgg140,  "TkEM/TkEMNoMatching_Eta_000000", "H->#gamma#gamma photons (PU 140)");
   AddSpectrum(PdfFile, FHgg200,  "TkEM/TkEMNoMatching_Eta_000000", "H->#gamma#gamma photons (PU 200)");

   PdfFile.AddTextPage("Individual efficiency plots");

   PdfFile.AddPlot(TkEG_140_PT, "ap");
   PdfFile.AddPlot(TkEG_140_PT_Rebin, "ap");
   PdfFile.AddPlot(TkEG_140_PTEta10, "ap");
   PdfFile.AddPlot(TkEG_140_PTEta10_Rebin, "ap");
   PdfFile.AddPlot(TkEG_140_PTEtaLarge, "ap");
   PdfFile.AddPlot(TkEG_140_PTEtaLarge_Rebin, "ap");
   PdfFile.AddPlot(TkEG_140_Eta, "ap");
   PdfFile.AddPlot(TkEG_140_EtaPT20, "ap");
   PdfFile.AddPlot(TkEG_140_EtaPT25, "ap");
   PdfFile.AddPlot(TkEG_200_PT, "ap");
   PdfFile.AddPlot(TkEG_200_PT_Rebin, "ap");
   PdfFile.AddPlot(TkEG_200_PTEta10, "ap");
   PdfFile.AddPlot(TkEG_200_PTEta10_Rebin, "ap");
   PdfFile.AddPlot(TkEG_200_PTEtaLarge, "ap");
   PdfFile.AddPlot(TkEG_200_PTEtaLarge_Rebin, "ap");
   PdfFile.AddPlot(TkEG_200_Eta, "ap");
   PdfFile.AddPlot(TkEG_200_EtaPT20, "ap");
   PdfFile.AddPlot(TkEG_200_EtaPT25, "ap");
   PdfFile.AddPlot(TkIsoEG_140_PT, "ap");
   PdfFile.AddPlot(TkIsoEG_140_PT_Rebin, "ap");
   PdfFile.AddPlot(TkIsoEG_140_PTEta10, "ap");
   PdfFile.AddPlot(TkIsoEG_140_PTEta10_Rebin, "ap");
   PdfFile.AddPlot(TkIsoEG_140_PTEtaLarge, "ap");
   PdfFile.AddPlot(TkIsoEG_140_PTEtaLarge_Rebin, "ap");
   PdfFile.AddPlot(TkIsoEG_140_Eta, "ap");
   PdfFile.AddPlot(TkIsoEG_140_EtaPT20, "ap");
   PdfFile.AddPlot(TkIsoEG_140_EtaPT25, "ap");
   PdfFile.AddPlot(TkIsoEG_200_PT, "ap");
   PdfFile.AddPlot(TkIsoEG_200_PT_Rebin, "ap");
   PdfFile.AddPlot(TkIsoEG_200_PTEta10, "ap");
   PdfFile.AddPlot(TkIsoEG_200_PTEta10_Rebin, "ap");
   PdfFile.AddPlot(TkIsoEG_200_PTEtaLarge, "ap");
   PdfFile.AddPlot(TkIsoEG_200_PTEtaLarge_Rebin, "ap");
   PdfFile.AddPlot(TkIsoEG_200_Eta, "ap");
   PdfFile.AddPlot(TkIsoEG_200_EtaPT20, "ap");
   PdfFile.AddPlot(TkIsoEG_200_EtaPT25, "ap");
   PdfFile.AddPlot(TkEM_140_PT, "ap");
   PdfFile.AddPlot(TkEM_140_PT_Rebin, "ap");
   PdfFile.AddPlot(TkEM_140_PTEta10, "ap");
   PdfFile.AddPlot(TkEM_140_PTEta10_Rebin, "ap");
   PdfFile.AddPlot(TkEM_140_PTEtaLarge, "ap");
   PdfFile.AddPlot(TkEM_140_PTEtaLarge_Rebin, "ap");
   PdfFile.AddPlot(TkEM_140_Eta, "ap");
   PdfFile.AddPlot(TkEM_140_EtaPT20, "ap");
   PdfFile.AddPlot(TkEM_140_EtaPT25, "ap");
   PdfFile.AddPlot(TkEM_200_PT, "ap");
   PdfFile.AddPlot(TkEM_200_PT_Rebin, "ap");
   PdfFile.AddPlot(TkEM_200_PTEta10, "ap");
   PdfFile.AddPlot(TkEM_200_PTEta10_Rebin, "ap");
   PdfFile.AddPlot(TkEM_200_PTEtaLarge, "ap");
   PdfFile.AddPlot(TkEM_200_PTEtaLarge_Rebin, "ap");
   PdfFile.AddPlot(TkEM_200_Eta, "ap");
   PdfFile.AddPlot(TkEM_200_EtaPT20, "ap");
   PdfFile.AddPlot(TkEM_200_EtaPT25, "ap");
   
   PdfFile.AddTextPage("Summary plots");

   // AddFourPlots(PdfFile, TkEG_140_PT, TkEG_200_PT, TkIsoEG_140_PT, TkIsoEG_200_PT, "|eta| < 2.4");
   AddFourPlots(PdfFile, TkEG_140_PT_Rebin, TkEG_200_PT_Rebin, TkIsoEG_140_PT_Rebin, TkIsoEG_200_PT_Rebin, "|eta| < 2.4");
   // AddFourPlots(PdfFile, TkEG_140_PTEta10, TkEG_200_PTEta10, TkIsoEG_140_PTEta10, TkIsoEG_200_PTEta10, "|eta| < 1.0");
   AddFourPlots(PdfFile, TkEG_140_PTEta10_Rebin, TkEG_200_PTEta10_Rebin, TkIsoEG_140_PTEta10_Rebin, TkIsoEG_200_PTEta10_Rebin, "|eta| < 1.0");
   // AddFourPlots(PdfFile, TkEG_140_PTEtaLarge, TkEG_200_PTEtaLarge, TkIsoEG_140_PTEtaLarge, TkIsoEG_200_PTEtaLarge, "|eta| > 1.0");
   AddFourPlots(PdfFile, TkEG_140_PTEtaLarge_Rebin, TkEG_200_PTEtaLarge_Rebin, TkIsoEG_140_PTEtaLarge_Rebin, TkIsoEG_200_PTEtaLarge_Rebin, "|eta| > 1.0");
   AddFourPlots(PdfFile, TkEG_140_Eta, TkEG_200_Eta, TkIsoEG_140_Eta, TkIsoEG_200_Eta, "PT > 0");
   AddFourPlots(PdfFile, TkEG_140_EtaPT20, TkEG_200_EtaPT20, TkIsoEG_140_EtaPT20, TkIsoEG_200_EtaPT20, "PT > 20");
   AddFourPlots(PdfFile, TkEG_140_EtaPT25, TkEG_200_EtaPT25, TkIsoEG_140_EtaPT25, TkIsoEG_200_EtaPT25, "PT > 25");
   
   // AddTwoPlots(PdfFile, TkEM_140_PT, TkEM_200_PT, "|eta| < 2.4");
   AddTwoPlots(PdfFile, TkEM_140_PT_Rebin, TkEM_200_PT_Rebin, "|eta| < 2.4");
   // AddTwoPlots(PdfFile, TkEM_140_PTEta10, TkEM_200_PTEta10, "|eta| < 1.0");
   AddTwoPlots(PdfFile, TkEM_140_PTEta10_Rebin, TkIsoEG_200_PTEta10_Rebin, "|eta| < 1.0");
   // AddTwoPlots(PdfFile, TkEM_140_PTEtaLarge, TkEM_200_PTEtaLarge, "|eta| > 1.0");
   AddTwoPlots(PdfFile, TkEM_140_PTEtaLarge_Rebin, TkEM_200_PTEtaLarge_Rebin, "|eta| > 1.0");
   AddTwoPlots(PdfFile, TkEM_140_Eta, TkEM_200_Eta, "PT > 0");
   AddTwoPlots(PdfFile, TkEM_140_EtaPT20, TkEM_200_EtaPT20, "PT > 20");
   AddTwoPlots(PdfFile, TkEM_140_EtaPT25, TkEM_200_EtaPT25, "PT > 25");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   delete TkEG_140_PT;
   delete TkEG_140_PT_Rebin;
   delete TkEG_140_PTEta10;
   delete TkEG_140_PTEta10_Rebin;
   delete TkEG_140_PTEtaLarge;
   delete TkEG_140_PTEtaLarge_Rebin;
   delete TkEG_140_Eta;
   delete TkEG_140_EtaPT20;
   delete TkEG_140_EtaPT25;
   delete TkEG_200_PT;
   delete TkEG_200_PT_Rebin;
   delete TkEG_200_PTEta10;
   delete TkEG_200_PTEta10_Rebin;
   delete TkEG_200_PTEtaLarge;
   delete TkEG_200_PTEtaLarge_Rebin;
   delete TkEG_200_Eta;
   delete TkEG_200_EtaPT20;
   delete TkEG_200_EtaPT25;
   delete TkIsoEG_140_PT;
   delete TkIsoEG_140_PT_Rebin;
   delete TkIsoEG_140_PTEta10;
   delete TkIsoEG_140_PTEta10_Rebin;
   delete TkIsoEG_140_PTEtaLarge;
   delete TkIsoEG_140_PTEtaLarge_Rebin;
   delete TkIsoEG_140_Eta;
   delete TkIsoEG_140_EtaPT20;
   delete TkIsoEG_140_EtaPT25;
   delete TkIsoEG_200_PT;
   delete TkIsoEG_200_PT_Rebin;
   delete TkIsoEG_200_PTEta10;
   delete TkIsoEG_200_PTEta10_Rebin;
   delete TkIsoEG_200_PTEtaLarge;
   delete TkIsoEG_200_PTEtaLarge_Rebin;
   delete TkIsoEG_200_Eta;
   delete TkIsoEG_200_EtaPT20;
   delete TkIsoEG_200_EtaPT25;
   delete TkEM_140_PT;
   delete TkEM_140_PT_Rebin;
   delete TkEM_140_PTEta10;
   delete TkEM_140_PTEta10_Rebin;
   delete TkEM_140_PTEtaLarge;
   delete TkEM_140_PTEtaLarge_Rebin;
   delete TkEM_140_Eta;
   delete TkEM_140_EtaPT20;
   delete TkEM_140_EtaPT25;
   delete TkEM_200_PT;
   delete TkEM_200_PT_Rebin;
   delete TkEM_200_PTEta10;
   delete TkEM_200_PTEta10_Rebin;
   delete TkEM_200_PTEtaLarge;
   delete TkEM_200_PTEtaLarge_Rebin;
   delete TkEM_200_Eta;
   delete TkEM_200_EtaPT20;
   delete TkEM_200_EtaPT25;

   FWENu200.Close();
   FWENu140.Close();

   return 0;
}

TGraphAsymmErrors *Divide(TFile &F1, string N1, TFile &F2, string N2, int Rebin)
{
   TGraphAsymmErrors *Result = NULL;

   TH1D *H1 = (TH1D *)F1.Get(N1.c_str());
   TH1D *H2 = (TH1D *)F2.Get(N2.c_str());

   if(H1 == NULL || H2 == NULL)
      return NULL;

   TH1D *H1Temp = NULL;
   TH1D *H2Temp = NULL;

   if(Rebin >= 1)
   {
      H1Temp = (TH1D *)H1->Clone("H1Temp");
      H2Temp = (TH1D *)H2->Clone("H2Temp");

      H1Temp->Rebin(Rebin);
      H2Temp->Rebin(Rebin);
   }
   
   if(Rebin < 0)
   {
      // this is the PT case - let's make variable binned histograms
      double Binning[26] =
         {0, 2, 4, 6, 8, 10, 12, 14, 16, 18,
         20, 22, 24, 26, 28, 30, 34, 38, 42, 46,
         50, 60, 70, 90, 110, 150};

      H1Temp = new TH1D("H1Temp", "", 25, Binning);
      H2Temp = new TH1D("H2Temp", "", 25, Binning);

      H1Temp->Sumw2();
      H2Temp->Sumw2();

      int N = H1->GetNbinsX();
      for(int i = 1; i <= N; i++)
      {
         for(int j = 0; j < H1->GetBinContent(i); j++)
            H1Temp->Fill(H1->GetBinCenter(i));
         for(int j = 0; j < H2->GetBinContent(i); j++)
            H2Temp->Fill(H2->GetBinCenter(i));
      }
   }

   Result = new TGraphAsymmErrors;
   Result->Divide(H1Temp, H2Temp);

   if(H1Temp != NULL)
      delete H1Temp;
   if(H2Temp != NULL)
      delete H2Temp;

   return Result;
}

void AddFourPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEG140, TGraphAsymmErrors *TkEG200,
   TGraphAsymmErrors *TkIsoEG140, TGraphAsymmErrors *TkIsoEG200, string Title)
{
   if(TkEG140 == NULL)
      return;
   if(TkEG200 == NULL)
      return;
   if(TkIsoEG140 == NULL)
      return;
   if(TkIsoEG200 == NULL)
      return;

   TkEG140->SetTitle(Title.c_str());

   TkEG140->SetMarkerColor(kBlue);
   TkEG200->SetMarkerColor(kRed);
   TkIsoEG140->SetMarkerColor(kGreen - 3);
   TkIsoEG200->SetMarkerColor(kYellow + 3);
   
   TkEG140->SetLineColor(kBlue);
   TkEG200->SetLineColor(kRed);
   TkIsoEG140->SetLineColor(kGreen - 3);
   TkIsoEG200->SetLineColor(kYellow + 3);

   TCanvas C;

   TkEG140->Draw("ap");
   
   TH2D HWorld("HWorld", "", 100, TkEG140->GetXaxis()->GetXmin(), TkEG140->GetXaxis()->GetXmax(), 100, 0, 1.05);
   HWorld.SetTitle(Title.c_str());
   HWorld.GetXaxis()->SetTitle(TkEG140->GetXaxis()->GetTitle());
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   TkEG140->Draw("p");
   TkEG200->Draw("p");
   TkIsoEG140->Draw("p");
   TkIsoEG200->Draw("p");

   TLegend Legend(0.35, 0.15, 0.65, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(TkEG140, "TkEG, PU140", "pl");
   Legend.AddEntry(TkEG200, "TkEG, PU200", "pl");
   Legend.AddEntry(TkIsoEG140, "TkIsoEG, PU140", "pl");
   Legend.AddEntry(TkIsoEG200, "TkIsoEG, PU200", "pl");
   Legend.Draw();

   TGraph G1, G2, G3;
   G1.SetPoint(0, -999, 1);
   G1.SetPoint(1, +999, 1);
   G2.SetPoint(0, -999, 0.90);
   G2.SetPoint(1, +999, 0.90);
   G3.SetPoint(0, 25, 0);
   G3.SetPoint(1, 25, 5);
   G2.SetLineStyle(kDashed);
   G3.SetLineStyle(kDotted);

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   PdfFile.AddCanvas(C);
}

void AddTwoPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEM140, TGraphAsymmErrors *TkEM200, string Title)
{
   if(TkEM140 == NULL)
      return;
   if(TkEM200 == NULL)
      return;

   TkEM140->SetTitle(Title.c_str());

   TkEM140->SetMarkerColor(kBlue);
   TkEM200->SetMarkerColor(kRed);
   
   TkEM140->SetLineColor(kBlue);
   TkEM200->SetLineColor(kRed);

   TCanvas C;

   TkEM140->Draw("ap");

   TH2D HWorld("HWorld", "", 100, TkEM140->GetXaxis()->GetXmin(), TkEM140->GetXaxis()->GetXmax(), 100, 0, 1.05);
   HWorld.SetTitle(Title.c_str());
   HWorld.GetXaxis()->SetTitle(TkEM140->GetXaxis()->GetTitle());
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   TkEM140->Draw("p");
   TkEM200->Draw("p");

   TLegend Legend(0.35, 0.15, 0.65, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(TkEM140, "TkEM, PU140", "pl");
   Legend.AddEntry(TkEM200, "TkEM, PU200", "pl");
   Legend.Draw();

   TGraph G1, G2, G3;
   G1.SetPoint(0, -999, 1);
   G1.SetPoint(1, +999, 1);
   G2.SetPoint(0, -999, 0.90);
   G2.SetPoint(1, +999, 0.90);
   G3.SetPoint(0, 25, 0);
   G3.SetPoint(1, 25, 5);
   G2.SetLineStyle(kDashed);
   G3.SetLineStyle(kDotted);

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   PdfFile.AddCanvas(C);
}

void AddSpectrum(PdfFileHelper &PdfFile, TFile &F, string N, string Title)
{
   TH1D *H = (TH1D *)F.Get(N.c_str())->Clone("Yay");

   H->SetStats(0);
   H->SetTitle(Title.c_str());
   H->SetMinimum(0);

   PdfFile.AddPlot(H);

   delete H;
}


