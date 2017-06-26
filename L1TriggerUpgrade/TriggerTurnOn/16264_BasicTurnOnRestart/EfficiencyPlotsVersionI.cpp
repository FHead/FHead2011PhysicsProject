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
   TGraphAsymmErrors *TkIsoEG140, TGraphAsymmErrors *TkIsoEG200, string Title, string Tag1, string Tag2);
void AddTwoPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEM140, TGraphAsymmErrors *TkEM200, string Title, string Tag);
void AddSpectrum(PdfFileHelper &PdfFile, TFile &F, string N, string Title);

int main()
{
   SetThesisStyle();

   TFile FWENu140("Result/Combined/WToEnu140PU.root");
   TFile FWENu200("Result/Combined/WToEnu200PU.root");
   TFile FWENu140Tyler("Result/Combined/WToEnu140PU_NewRecipePlusTyler.root");
   TFile FWENu200Tyler("Result/Combined/WToEnu200PU_NewRecipePlusTyler.root");
   TFile FHgg140("Result/Combined/Hgg140PU.root");
   TFile FHgg200("Result/Combined/Hgg200PU.root");
   TFile FTT140("Result/Combined/TTBar140PU.root");
   TFile FTT200("Result/Combined/TTBar200PU.root");

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
   TGraphAsymmErrors *TkEGTyler_140_PT = Divide(FWENu140Tyler, "TkEG/TkEG_PT_000000",
      FWENu140Tyler, "TkEG/TkEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkEGTyler_140_PT_Rebin = Divide(FWENu140Tyler, "TkEG/TkEG_PT_000000",
      FWENu140Tyler, "TkEG/TkEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkEGTyler_140_PTEta10 = Divide(FWENu140Tyler, "TkEG/TkEG_PTEta10_000000",
      FWENu140Tyler, "TkEG/TkEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkEGTyler_140_PTEta10_Rebin = Divide(FWENu140Tyler, "TkEG/TkEG_PTEta10_000000",
      FWENu140Tyler, "TkEG/TkEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkEGTyler_140_PTEtaLarge = Divide(FWENu140Tyler, "TkEG/TkEG_PTEtaLarge_000000",
      FWENu140Tyler, "TkEG/TkEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkEGTyler_140_PTEtaLarge_Rebin = Divide(FWENu140Tyler, "TkEG/TkEG_PTEtaLarge_000000",
      FWENu140Tyler, "TkEG/TkEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkEGTyler_140_Eta = Divide(FWENu140Tyler, "TkEG/TkEG_Eta_000000",
      FWENu140Tyler, "TkEG/TkEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkEGTyler_140_EtaPT20 = Divide(FWENu140Tyler, "TkEG/TkEG_EtaPT20_000000",
      FWENu140Tyler, "TkEG/TkEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkEGTyler_140_EtaPT25 = Divide(FWENu140Tyler, "TkEG/TkEG_EtaPT25_000000",
      FWENu140Tyler, "TkEG/TkEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkEGTyler_200_PT = Divide(FWENu200Tyler, "TkEG/TkEG_PT_000000",
      FWENu200Tyler, "TkEG/TkEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkEGTyler_200_PT_Rebin = Divide(FWENu200Tyler, "TkEG/TkEG_PT_000000",
      FWENu200Tyler, "TkEG/TkEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkEGTyler_200_PTEta10 = Divide(FWENu200Tyler, "TkEG/TkEG_PTEta10_000000",
      FWENu200Tyler, "TkEG/TkEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkEGTyler_200_PTEta10_Rebin = Divide(FWENu200Tyler, "TkEG/TkEG_PTEta10_000000",
      FWENu200Tyler, "TkEG/TkEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkEGTyler_200_PTEtaLarge = Divide(FWENu200Tyler, "TkEG/TkEG_PTEtaLarge_000000",
      FWENu200Tyler, "TkEG/TkEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkEGTyler_200_PTEtaLarge_Rebin = Divide(FWENu200Tyler, "TkEG/TkEG_PTEtaLarge_000000",
      FWENu200Tyler, "TkEG/TkEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkEGTyler_200_Eta = Divide(FWENu200Tyler, "TkEG/TkEG_Eta_000000",
      FWENu200Tyler, "TkEG/TkEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkEGTyler_200_EtaPT20 = Divide(FWENu200Tyler, "TkEG/TkEG_EtaPT20_000000",
      FWENu200Tyler, "TkEG/TkEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkEGTyler_200_EtaPT25 = Divide(FWENu200Tyler, "TkEG/TkEG_EtaPT25_000000",
      FWENu200Tyler, "TkEG/TkEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkIsoEGTyler_140_PT = Divide(FWENu140Tyler, "TkIsoEG/TkIsoEG_PT_000000",
      FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkIsoEGTyler_140_PT_Rebin = Divide(FWENu140Tyler, "TkIsoEG/TkIsoEG_PT_000000",
      FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkIsoEGTyler_140_PTEta10 = Divide(FWENu140Tyler, "TkIsoEG/TkIsoEG_PTEta10_000000",
      FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkIsoEGTyler_140_PTEta10_Rebin = Divide(FWENu140Tyler, "TkIsoEG/TkIsoEG_PTEta10_000000",
      FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkIsoEGTyler_140_PTEtaLarge = Divide(FWENu140Tyler, "TkIsoEG/TkIsoEG_PTEtaLarge_000000",
      FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkIsoEGTyler_140_PTEtaLarge_Rebin = Divide(FWENu140Tyler, "TkIsoEG/TkIsoEG_PTEtaLarge_000000",
      FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkIsoEGTyler_140_Eta = Divide(FWENu140Tyler, "TkIsoEG/TkIsoEG_Eta_000000",
      FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkIsoEGTyler_140_EtaPT20 = Divide(FWENu140Tyler, "TkIsoEG/TkIsoEG_EtaPT20_000000",
      FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkIsoEGTyler_140_EtaPT25 = Divide(FWENu140Tyler, "TkIsoEG/TkIsoEG_EtaPT25_000000",
      FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkIsoEGTyler_200_PT = Divide(FWENu200Tyler, "TkIsoEG/TkIsoEG_PT_000000",
      FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkIsoEGTyler_200_PT_Rebin = Divide(FWENu200Tyler, "TkIsoEG/TkIsoEG_PT_000000",
      FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *TkIsoEGTyler_200_PTEta10 = Divide(FWENu200Tyler, "TkIsoEG/TkIsoEG_PTEta10_000000",
      FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkIsoEGTyler_200_PTEta10_Rebin = Divide(FWENu200Tyler, "TkIsoEG/TkIsoEG_PTEta10_000000",
      FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *TkIsoEGTyler_200_PTEtaLarge = Divide(FWENu200Tyler, "TkIsoEG/TkIsoEG_PTEtaLarge_000000",
      FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkIsoEGTyler_200_PTEtaLarge_Rebin = Divide(FWENu200Tyler, "TkIsoEG/TkIsoEG_PTEtaLarge_000000",
      FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkIsoEGTyler_200_Eta = Divide(FWENu200Tyler, "TkIsoEG/TkIsoEG_Eta_000000",
      FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkIsoEGTyler_200_EtaPT20 = Divide(FWENu200Tyler, "TkIsoEG/TkIsoEG_EtaPT20_000000",
      FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkIsoEGTyler_200_EtaPT25 = Divide(FWENu200Tyler, "TkIsoEG/TkIsoEG_EtaPT25_000000",
      FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching_EtaPT25_000000", 2);
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
   TGraphAsymmErrors *TkEMEG_140_PT = Divide(FHgg140, "TkEM/TkEM_PT_000000",
      FHgg140, "EG/EG_PT_000000", 5);
   TGraphAsymmErrors *TkEMEG_140_PT_Rebin = Divide(FHgg140, "TkEM/TkEM_PT_000000",
      FHgg140, "EG/EG_PT_000000", -1);
   TGraphAsymmErrors *TkEMEG_140_PTEta10 = Divide(FHgg140, "TkEM/TkEM_PTEta10_000000",
      FHgg140, "EG/EG_PTEta10_000000", 5);
   TGraphAsymmErrors *TkEMEG_140_PTEta10_Rebin = Divide(FHgg140, "TkEM/TkEM_PTEta10_000000",
      FHgg140, "EG/EG_PTEta10_000000", -1);
   TGraphAsymmErrors *TkEMEG_140_PTEtaLarge = Divide(FHgg140, "TkEM/TkEM_PTEtaLarge_000000",
      FHgg140, "EG/EG_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkEMEG_140_PTEtaLarge_Rebin = Divide(FHgg140, "TkEM/TkEM_PTEtaLarge_000000",
      FHgg140, "EG/EG_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkEMEG_140_Eta = Divide(FHgg140, "TkEM/TkEM_Eta_000000",
      FHgg140, "EG/EG_Eta_000000", 2);
   TGraphAsymmErrors *TkEMEG_140_EtaPT20 = Divide(FHgg140, "TkEM/TkEM_EtaPT20_000000",
      FHgg140, "EG/EG_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkEMEG_140_EtaPT25 = Divide(FHgg140, "TkEM/TkEM_EtaPT25_000000",
      FHgg140, "EG/EG_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkEMEG_200_PT = Divide(FHgg200, "TkEM/TkEM_PT_000000",
      FHgg200, "EG/EG_PT_000000", 5);
   TGraphAsymmErrors *TkEMEG_200_PT_Rebin = Divide(FHgg200, "TkEM/TkEM_PT_000000",
      FHgg200, "EG/EG_PT_000000", -1);
   TGraphAsymmErrors *TkEMEG_200_PTEta10 = Divide(FHgg200, "TkEM/TkEM_PTEta10_000000",
      FHgg200, "EG/EG_PTEta10_000000", 5);
   TGraphAsymmErrors *TkEMEG_200_PTEta10_Rebin = Divide(FHgg200, "TkEM/TkEM_PTEta10_000000",
      FHgg200, "EG/EG_PTEta10_000000", -1);
   TGraphAsymmErrors *TkEMEG_200_PTEtaLarge = Divide(FHgg200, "TkEM/TkEM_PTEtaLarge_000000",
      FHgg200, "EG/EG_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkEMEG_200_PTEtaLarge_Rebin = Divide(FHgg200, "TkEM/TkEM_PTEtaLarge_000000",
      FHgg200, "EG/EG_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *TkEMEG_200_Eta = Divide(FHgg200, "TkEM/TkEM_Eta_000000",
      FHgg200, "EG/EG_Eta_000000", 2);
   TGraphAsymmErrors *TkEMEG_200_EtaPT20 = Divide(FHgg200, "TkEM/TkEM_EtaPT20_000000",
      FHgg200, "EG/EG_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkEMEG_200_EtaPT25 = Divide(FHgg200, "TkEM/TkEM_EtaPT25_000000",
      FHgg200, "EG/EG_EtaPT25_000000", 2);
   TGraphAsymmErrors *EG_140_PT = Divide(FHgg140, "EG/EG_PT_000000",
      FHgg140, "EG/EGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *EG_140_PT_Rebin = Divide(FHgg140, "EG/EG_PT_000000",
      FHgg140, "EG/EGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *EG_140_PTEta10 = Divide(FHgg140, "EG/EG_PTEta10_000000",
      FHgg140, "EG/EGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *EG_140_PTEta10_Rebin = Divide(FHgg140, "EG/EG_PTEta10_000000",
      FHgg140, "EG/EGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *EG_140_PTEtaLarge = Divide(FHgg140, "EG/EG_PTEtaLarge_000000",
      FHgg140, "EG/EGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *EG_140_PTEtaLarge_Rebin = Divide(FHgg140, "EG/EG_PTEtaLarge_000000",
      FHgg140, "EG/EGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *EG_140_Eta = Divide(FHgg140, "EG/EG_Eta_000000",
      FHgg140, "EG/EGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *EG_140_EtaPT20 = Divide(FHgg140, "EG/EG_EtaPT20_000000",
      FHgg140, "EG/EGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *EG_140_EtaPT25 = Divide(FHgg140, "EG/EG_EtaPT25_000000",
      FHgg140, "EG/EGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *EG_200_PT = Divide(FHgg200, "EG/EG_PT_000000",
      FHgg200, "EG/EGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *EG_200_PT_Rebin = Divide(FHgg200, "EG/EG_PT_000000",
      FHgg200, "EG/EGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *EG_200_PTEta10 = Divide(FHgg200, "EG/EG_PTEta10_000000",
      FHgg200, "EG/EGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *EG_200_PTEta10_Rebin = Divide(FHgg200, "EG/EG_PTEta10_000000",
      FHgg200, "EG/EGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *EG_200_PTEtaLarge = Divide(FHgg200, "EG/EG_PTEtaLarge_000000",
      FHgg200, "EG/EGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *EG_200_PTEtaLarge_Rebin = Divide(FHgg200, "EG/EG_PTEtaLarge_000000",
      FHgg200, "EG/EGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *EG_200_Eta = Divide(FHgg200, "EG/EG_Eta_000000",
      FHgg200, "EG/EGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *EG_200_EtaPT20 = Divide(FHgg200, "EG/EG_EtaPT20_000000",
      FHgg200, "EG/EGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *EG_200_EtaPT25 = Divide(FHgg200, "EG/EG_EtaPT25_000000",
      FHgg200, "EG/EGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *IsoEG_140_PT = Divide(FHgg140, "IsoEG/IsoEG_PT_000000",
      FHgg140, "IsoEG/IsoEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *IsoEG_140_PT_Rebin = Divide(FHgg140, "IsoEG/IsoEG_PT_000000",
      FHgg140, "IsoEG/IsoEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *IsoEG_140_PTEta10 = Divide(FHgg140, "IsoEG/IsoEG_PTEta10_000000",
      FHgg140, "IsoEG/IsoEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *IsoEG_140_PTEta10_Rebin = Divide(FHgg140, "IsoEG/IsoEG_PTEta10_000000",
      FHgg140, "IsoEG/IsoEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *IsoEG_140_PTEtaLarge = Divide(FHgg140, "IsoEG/IsoEG_PTEtaLarge_000000",
      FHgg140, "IsoEG/IsoEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *IsoEG_140_PTEtaLarge_Rebin = Divide(FHgg140, "IsoEG/IsoEG_PTEtaLarge_000000",
      FHgg140, "IsoEG/IsoEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *IsoEG_140_Eta = Divide(FHgg140, "IsoEG/IsoEG_Eta_000000",
      FHgg140, "IsoEG/IsoEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *IsoEG_140_EtaPT20 = Divide(FHgg140, "IsoEG/IsoEG_EtaPT20_000000",
      FHgg140, "IsoEG/IsoEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *IsoEG_140_EtaPT25 = Divide(FHgg140, "IsoEG/IsoEG_EtaPT25_000000",
      FHgg140, "IsoEG/IsoEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *IsoEG_200_PT = Divide(FHgg200, "IsoEG/IsoEG_PT_000000",
      FHgg200, "IsoEG/IsoEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *IsoEG_200_PT_Rebin = Divide(FHgg200, "IsoEG/IsoEG_PT_000000",
      FHgg200, "IsoEG/IsoEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *IsoEG_200_PTEta10 = Divide(FHgg200, "IsoEG/IsoEG_PTEta10_000000",
      FHgg200, "IsoEG/IsoEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *IsoEG_200_PTEta10_Rebin = Divide(FHgg200, "IsoEG/IsoEG_PTEta10_000000",
      FHgg200, "IsoEG/IsoEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *IsoEG_200_PTEtaLarge = Divide(FHgg200, "IsoEG/IsoEG_PTEtaLarge_000000",
      FHgg200, "IsoEG/IsoEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *IsoEG_200_PTEtaLarge_Rebin = Divide(FHgg200, "IsoEG/IsoEG_PTEtaLarge_000000",
      FHgg200, "IsoEG/IsoEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *IsoEG_200_Eta = Divide(FHgg200, "IsoEG/IsoEG_Eta_000000",
      FHgg200, "IsoEG/IsoEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *IsoEG_200_EtaPT20 = Divide(FHgg200, "IsoEG/IsoEG_EtaPT20_000000",
      FHgg200, "IsoEG/IsoEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *IsoEG_200_EtaPT25 = Divide(FHgg200, "IsoEG/IsoEG_EtaPT25_000000",
      FHgg200, "IsoEG/IsoEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *EGTyler_140_PT = Divide(FWENu140Tyler, "EGEle/EGEle_PT_000000",
      FWENu140Tyler, "EGEle/EGEleNoMatching_PT_000000", 5);
   TGraphAsymmErrors *EGTyler_140_PT_Rebin = Divide(FWENu140Tyler, "EGEle/EGEle_PT_000000",
      FWENu140Tyler, "EGEle/EGEleNoMatching_PT_000000", -1);
   TGraphAsymmErrors *EGTyler_140_PTEta10 = Divide(FWENu140Tyler, "EGEle/EGEle_PTEta10_000000",
      FWENu140Tyler, "EGEle/EGEleNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *EGTyler_140_PTEta10_Rebin = Divide(FWENu140Tyler, "EGEle/EGEle_PTEta10_000000",
      FWENu140Tyler, "EGEle/EGEleNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *EGTyler_140_PTEtaLarge = Divide(FWENu140Tyler, "EGEle/EGEle_PTEtaLarge_000000",
      FWENu140Tyler, "EGEle/EGEleNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *EGTyler_140_PTEtaLarge_Rebin = Divide(FWENu140Tyler, "EGEle/EGEle_PTEtaLarge_000000",
      FWENu140Tyler, "EGEle/EGEleNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *EGTyler_140_Eta = Divide(FWENu140Tyler, "EGEle/EGEle_Eta_000000",
      FWENu140Tyler, "EGEle/EGEleNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *EGTyler_140_EtaPT20 = Divide(FWENu140Tyler, "EGEle/EGEle_EtaPT20_000000",
      FWENu140Tyler, "EGEle/EGEleNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *EGTyler_140_EtaPT25 = Divide(FWENu140Tyler, "EGEle/EGEle_EtaPT25_000000",
      FWENu140Tyler, "EGEle/EGEleNoMatching_EtaPT25_000000", 2);
   // TGraphAsymmErrors *EGTyler_200_PT = Divide(FWENu200Tyler, "EG/EG_PT_000000",
   //    FWENu200Tyler, "EG/EGNoMatching_PT_000000", 5);
   // TGraphAsymmErrors *EGTyler_200_PT_Rebin = Divide(FWENu200Tyler, "EG/EG_PT_000000",
   //    FWENu200Tyler, "EG/EGNoMatching_PT_000000", -1);
   // TGraphAsymmErrors *EGTyler_200_PTEta10 = Divide(FWENu200Tyler, "EG/EG_PTEta10_000000",
   //    FWENu200Tyler, "EG/EGNoMatching_PTEta10_000000", 5);
   // TGraphAsymmErrors *EGTyler_200_PTEta10_Rebin = Divide(FWENu200Tyler, "EG/EG_PTEta10_000000",
   //    FWENu200Tyler, "EG/EGNoMatching_PTEta10_000000", -1);
   // TGraphAsymmErrors *EGTyler_200_PTEtaLarge = Divide(FWENu200Tyler, "EG/EG_PTEtaLarge_000000",
   //    FWENu200Tyler, "EG/EGNoMatching_PTEtaLarge_000000", 5);
   // TGraphAsymmErrors *EGTyler_200_PTEtaLarge_Rebin = Divide(FWENu200Tyler, "EG/EG_PTEtaLarge_000000",
   //    FWENu200Tyler, "EG/EGNoMatching_PTEtaLarge_000000", -1);
   // TGraphAsymmErrors *EGTyler_200_Eta = Divide(FWENu200Tyler, "EG/EG_Eta_000000",
   //    FWENu200Tyler, "EG/EGNoMatching_Eta_000000", 2);
   // TGraphAsymmErrors *EGTyler_200_EtaPT20 = Divide(FWENu200Tyler, "EG/EG_EtaPT20_000000",
   //    FWENu200Tyler, "EG/EGNoMatching_EtaPT20_000000", 2);
   // TGraphAsymmErrors *EGTyler_200_EtaPT25 = Divide(FWENu200Tyler, "EG/EG_EtaPT25_000000",
   //    FWENu200Tyler, "EG/EGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *EGTyler_200_PT = Divide(FWENu200Tyler, "EGEle/EGEle_PT_000000",
      FWENu200Tyler, "EGEle/EGEleNoMatching_PT_000000", 5);
   TGraphAsymmErrors *EGTyler_200_PT_Rebin = Divide(FWENu200Tyler, "EGEle/EGEle_PT_000000",
      FWENu200Tyler, "EGEle/EGEleNoMatching_PT_000000", -1);
   TGraphAsymmErrors *EGTyler_200_PTEta10 = Divide(FWENu200Tyler, "EGEle/EGEle_PTEta10_000000",
      FWENu200Tyler, "EGEle/EGEleNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *EGTyler_200_PTEta10_Rebin = Divide(FWENu200Tyler, "EGEle/EGEle_PTEta10_000000",
      FWENu200Tyler, "EGEle/EGEleNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *EGTyler_200_PTEtaLarge = Divide(FWENu200Tyler, "EGEle/EGEle_PTEtaLarge_000000",
      FWENu200Tyler, "EGEle/EGEleNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *EGTyler_200_PTEtaLarge_Rebin = Divide(FWENu200Tyler, "EGEle/EGEle_PTEtaLarge_000000",
      FWENu200Tyler, "EGEle/EGEleNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *EGTyler_200_Eta = Divide(FWENu200Tyler, "EGEle/EGEle_Eta_000000",
      FWENu200Tyler, "EGEle/EGEleNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *EGTyler_200_EtaPT20 = Divide(FWENu200Tyler, "EGEle/EGEle_EtaPT20_000000",
      FWENu200Tyler, "EGEle/EGEleNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *EGTyler_200_EtaPT25 = Divide(FWENu200Tyler, "EGEle/EGEle_EtaPT25_000000",
      FWENu200Tyler, "EGEle/EGEleNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *IsoEGTyler_140_PT = Divide(FWENu140Tyler, "IsoEG/IsoEG_PT_000000",
      FWENu140Tyler, "IsoEG/IsoEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *IsoEGTyler_140_PT_Rebin = Divide(FWENu140Tyler, "IsoEG/IsoEG_PT_000000",
      FWENu140Tyler, "IsoEG/IsoEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *IsoEGTyler_140_PTEta10 = Divide(FWENu140Tyler, "IsoEG/IsoEG_PTEta10_000000",
      FWENu140Tyler, "IsoEG/IsoEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *IsoEGTyler_140_PTEta10_Rebin = Divide(FWENu140Tyler, "IsoEG/IsoEG_PTEta10_000000",
      FWENu140Tyler, "IsoEG/IsoEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *IsoEGTyler_140_PTEtaLarge = Divide(FWENu140Tyler, "IsoEG/IsoEG_PTEtaLarge_000000",
      FWENu140Tyler, "IsoEG/IsoEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *IsoEGTyler_140_PTEtaLarge_Rebin = Divide(FWENu140Tyler, "IsoEG/IsoEG_PTEtaLarge_000000",
      FWENu140Tyler, "IsoEG/IsoEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *IsoEGTyler_140_Eta = Divide(FWENu140Tyler, "IsoEG/IsoEG_Eta_000000",
      FWENu140Tyler, "IsoEG/IsoEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *IsoEGTyler_140_EtaPT20 = Divide(FWENu140Tyler, "IsoEG/IsoEG_EtaPT20_000000",
      FWENu140Tyler, "IsoEG/IsoEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *IsoEGTyler_140_EtaPT25 = Divide(FWENu140Tyler, "IsoEG/IsoEG_EtaPT25_000000",
      FWENu140Tyler, "IsoEG/IsoEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *IsoEGTyler_200_PT = Divide(FWENu200Tyler, "IsoEG/IsoEG_PT_000000",
      FWENu200Tyler, "IsoEG/IsoEGNoMatching_PT_000000", 5);
   TGraphAsymmErrors *IsoEGTyler_200_PT_Rebin = Divide(FWENu200Tyler, "IsoEG/IsoEG_PT_000000",
      FWENu200Tyler, "IsoEG/IsoEGNoMatching_PT_000000", -1);
   TGraphAsymmErrors *IsoEGTyler_200_PTEta10 = Divide(FWENu200Tyler, "IsoEG/IsoEG_PTEta10_000000",
      FWENu200Tyler, "IsoEG/IsoEGNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *IsoEGTyler_200_PTEta10_Rebin = Divide(FWENu200Tyler, "IsoEG/IsoEG_PTEta10_000000",
      FWENu200Tyler, "IsoEG/IsoEGNoMatching_PTEta10_000000", -1);
   TGraphAsymmErrors *IsoEGTyler_200_PTEtaLarge = Divide(FWENu200Tyler, "IsoEG/IsoEG_PTEtaLarge_000000",
      FWENu200Tyler, "IsoEG/IsoEGNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *IsoEGTyler_200_PTEtaLarge_Rebin = Divide(FWENu200Tyler, "IsoEG/IsoEG_PTEtaLarge_000000",
      FWENu200Tyler, "IsoEG/IsoEGNoMatching_PTEtaLarge_000000", -1);
   TGraphAsymmErrors *IsoEGTyler_200_Eta = Divide(FWENu200Tyler, "IsoEG/IsoEG_Eta_000000",
      FWENu200Tyler, "IsoEG/IsoEGNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *IsoEGTyler_200_EtaPT20 = Divide(FWENu200Tyler, "IsoEG/IsoEG_EtaPT20_000000",
      FWENu200Tyler, "IsoEG/IsoEGNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *IsoEGTyler_200_EtaPT25 = Divide(FWENu200Tyler, "IsoEG/IsoEG_EtaPT25_000000",
      FWENu200Tyler, "IsoEG/IsoEGNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *Jet_140_PT = Divide(FTT140, "Jet/Jet_PT_000000",
      FTT140, "Jet/JetNoMatching_PT_000000", 5);
   TGraphAsymmErrors *Jet_140_PT_Rebin = Divide(FTT140, "Jet/Jet_PT_000000",
      FTT140, "Jet/JetNoMatching_PT_000000", -2);
   TGraphAsymmErrors *Jet_140_PTEta10 = Divide(FTT140, "Jet/Jet_PTEta10_000000",
      FTT140, "Jet/JetNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *Jet_140_PTEta10_Rebin = Divide(FTT140, "Jet/Jet_PTEta10_000000",
      FTT140, "Jet/JetNoMatching_PTEta10_000000", -2);
   TGraphAsymmErrors *Jet_140_PTEtaLarge = Divide(FTT140, "Jet/Jet_PTEtaLarge_000000",
      FTT140, "Jet/JetNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *Jet_140_PTEtaLarge_Rebin = Divide(FTT140, "Jet/Jet_PTEtaLarge_000000",
      FTT140, "Jet/JetNoMatching_PTEtaLarge_000000", -2);
   TGraphAsymmErrors *Jet_140_Eta = Divide(FTT140, "Jet/Jet_Eta_000000",
      FTT140, "Jet/JetNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *Jet_140_EtaPT20 = Divide(FTT140, "Jet/Jet_EtaPT20_000000",
      FTT140, "Jet/JetNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *Jet_140_EtaPT25 = Divide(FTT140, "Jet/Jet_EtaPT25_000000",
      FTT140, "Jet/JetNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *Jet_140_EtaPT200 = Divide(FTT140, "Jet/Jet_EtaPT200_000000",
      FTT140, "Jet/JetNoMatching_EtaPT200_000000", 2);
   TGraphAsymmErrors *Jet_200_PT = Divide(FTT200, "Jet/Jet_PT_000000",
      FTT200, "Jet/JetNoMatching_PT_000000", 5);
   TGraphAsymmErrors *Jet_200_PT_Rebin = Divide(FTT200, "Jet/Jet_PT_000000",
      FTT200, "Jet/JetNoMatching_PT_000000", -2);
   TGraphAsymmErrors *Jet_200_PTEta10 = Divide(FTT200, "Jet/Jet_PTEta10_000000",
      FTT200, "Jet/JetNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *Jet_200_PTEta10_Rebin = Divide(FTT200, "Jet/Jet_PTEta10_000000",
      FTT200, "Jet/JetNoMatching_PTEta10_000000", -2);
   TGraphAsymmErrors *Jet_200_PTEtaLarge = Divide(FTT200, "Jet/Jet_PTEtaLarge_000000",
      FTT200, "Jet/JetNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *Jet_200_PTEtaLarge_Rebin = Divide(FTT200, "Jet/Jet_PTEtaLarge_000000",
      FTT200, "Jet/JetNoMatching_PTEtaLarge_000000", -2);
   TGraphAsymmErrors *Jet_200_Eta = Divide(FTT200, "Jet/Jet_Eta_000000",
      FTT200, "Jet/JetNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *Jet_200_EtaPT20 = Divide(FTT200, "Jet/Jet_EtaPT20_000000",
      FTT200, "Jet/JetNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *Jet_200_EtaPT25 = Divide(FTT200, "Jet/Jet_EtaPT25_000000",
      FTT200, "Jet/JetNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *Jet_200_EtaPT200 = Divide(FTT200, "Jet/Jet_EtaPT200_000000",
      FTT200, "Jet/JetNoMatching_EtaPT200_000000", 2);
   TGraphAsymmErrors *TkJet_140_PT = Divide(FTT140, "TkJet/TkJet_PT_000000",
      FTT140, "TkJet/TkJetNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkJet_140_PT_Rebin = Divide(FTT140, "TkJet/TkJet_PT_000000",
      FTT140, "TkJet/TkJetNoMatching_PT_000000", -2);
   TGraphAsymmErrors *TkJet_140_PTEta10 = Divide(FTT140, "TkJet/TkJet_PTEta10_000000",
      FTT140, "TkJet/TkJetNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkJet_140_PTEta10_Rebin = Divide(FTT140, "TkJet/TkJet_PTEta10_000000",
      FTT140, "TkJet/TkJetNoMatching_PTEta10_000000", -2);
   TGraphAsymmErrors *TkJet_140_PTEtaLarge = Divide(FTT140, "TkJet/TkJet_PTEtaLarge_000000",
      FTT140, "TkJet/TkJetNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkJet_140_PTEtaLarge_Rebin = Divide(FTT140, "TkJet/TkJet_PTEtaLarge_000000",
      FTT140, "TkJet/TkJetNoMatching_PTEtaLarge_000000", -2);
   TGraphAsymmErrors *TkJet_140_Eta = Divide(FTT140, "TkJet/TkJet_Eta_000000",
      FTT140, "TkJet/TkJetNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkJet_140_EtaPT20 = Divide(FTT140, "TkJet/TkJet_EtaPT20_000000",
      FTT140, "TkJet/TkJetNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkJet_140_EtaPT25 = Divide(FTT140, "TkJet/TkJet_EtaPT25_000000",
      FTT140, "TkJet/TkJetNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkJet_140_EtaPT200 = Divide(FTT140, "TkJet/TkJet_EtaPT200_000000",
      FTT140, "TkJet/TkJetNoMatching_EtaPT200_000000", 2);
   TGraphAsymmErrors *TkJet_200_PT = Divide(FTT200, "TkJet/TkJet_PT_000000",
      FTT200, "TkJet/TkJetNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkJet_200_PT_Rebin = Divide(FTT200, "TkJet/TkJet_PT_000000",
      FTT200, "TkJet/TkJetNoMatching_PT_000000", -2);
   TGraphAsymmErrors *TkJet_200_PTEta10 = Divide(FTT200, "TkJet/TkJet_PTEta10_000000",
      FTT200, "TkJet/TkJetNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkJet_200_PTEta10_Rebin = Divide(FTT200, "TkJet/TkJet_PTEta10_000000",
      FTT200, "TkJet/TkJetNoMatching_PTEta10_000000", -2);
   TGraphAsymmErrors *TkJet_200_PTEtaLarge = Divide(FTT200, "TkJet/TkJet_PTEtaLarge_000000",
      FTT200, "TkJet/TkJetNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkJet_200_PTEtaLarge_Rebin = Divide(FTT200, "TkJet/TkJet_PTEtaLarge_000000",
      FTT200, "TkJet/TkJetNoMatching_PTEtaLarge_000000", -2);
   TGraphAsymmErrors *TkJet_200_Eta = Divide(FTT200, "TkJet/TkJet_Eta_000000",
      FTT200, "TkJet/TkJetNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkJet_200_EtaPT20 = Divide(FTT200, "TkJet/TkJet_EtaPT20_000000",
      FTT200, "TkJet/TkJetNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkJet_200_EtaPT25 = Divide(FTT200, "TkJet/TkJet_EtaPT25_000000",
      FTT200, "TkJet/TkJetNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkJet_200_EtaPT200 = Divide(FTT200, "TkJet/TkJet_EtaPT200_000000",
      FTT200, "TkJet/TkJetNoMatching_EtaPT200_000000", 2);
   TGraphAsymmErrors *JetGen_140_PT = Divide(FTT140, "JetGen/JetGen_PT_000000",
      FTT140, "JetGen/JetGenNoMatching_PT_000000", 5);
   TGraphAsymmErrors *JetGen_140_PT_Rebin = Divide(FTT140, "JetGen/JetGen_PT_000000",
      FTT140, "JetGen/JetGenNoMatching_PT_000000", -2);
   TGraphAsymmErrors *JetGen_140_PTEta10 = Divide(FTT140, "JetGen/JetGen_PTEta10_000000",
      FTT140, "JetGen/JetGenNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *JetGen_140_PTEta10_Rebin = Divide(FTT140, "JetGen/JetGen_PTEta10_000000",
      FTT140, "JetGen/JetGenNoMatching_PTEta10_000000", -2);
   TGraphAsymmErrors *JetGen_140_PTEtaLarge = Divide(FTT140, "JetGen/JetGen_PTEtaLarge_000000",
      FTT140, "JetGen/JetGenNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *JetGen_140_PTEtaLarge_Rebin = Divide(FTT140, "JetGen/JetGen_PTEtaLarge_000000",
      FTT140, "JetGen/JetGenNoMatching_PTEtaLarge_000000", -2);
   TGraphAsymmErrors *JetGen_140_Eta = Divide(FTT140, "JetGen/JetGen_Eta_000000",
      FTT140, "JetGen/JetGenNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *JetGen_140_EtaPT20 = Divide(FTT140, "JetGen/JetGen_EtaPT20_000000",
      FTT140, "JetGen/JetGenNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *JetGen_140_EtaPT25 = Divide(FTT140, "JetGen/JetGen_EtaPT25_000000",
      FTT140, "JetGen/JetGenNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *JetGen_140_EtaPT200 = Divide(FTT140, "JetGen/JetGen_EtaPT200_000000",
      FTT140, "JetGen/JetGenNoMatching_EtaPT200_000000", 2);
   TGraphAsymmErrors *JetGen_200_PT = Divide(FTT200, "JetGen/JetGen_PT_000000",
      FTT200, "JetGen/JetGenNoMatching_PT_000000", 5);
   TGraphAsymmErrors *JetGen_200_PT_Rebin = Divide(FTT200, "JetGen/JetGen_PT_000000",
      FTT200, "JetGen/JetGenNoMatching_PT_000000", -2);
   TGraphAsymmErrors *JetGen_200_PTEta10 = Divide(FTT200, "JetGen/JetGen_PTEta10_000000",
      FTT200, "JetGen/JetGenNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *JetGen_200_PTEta10_Rebin = Divide(FTT200, "JetGen/JetGen_PTEta10_000000",
      FTT200, "JetGen/JetGenNoMatching_PTEta10_000000", -2);
   TGraphAsymmErrors *JetGen_200_PTEtaLarge = Divide(FTT200, "JetGen/JetGen_PTEtaLarge_000000",
      FTT200, "JetGen/JetGenNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *JetGen_200_PTEtaLarge_Rebin = Divide(FTT200, "JetGen/JetGen_PTEtaLarge_000000",
      FTT200, "JetGen/JetGenNoMatching_PTEtaLarge_000000", -2);
   TGraphAsymmErrors *JetGen_200_Eta = Divide(FTT200, "JetGen/JetGen_Eta_000000",
      FTT200, "JetGen/JetGenNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *JetGen_200_EtaPT20 = Divide(FTT200, "JetGen/JetGen_EtaPT20_000000",
      FTT200, "JetGen/JetGenNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *JetGen_200_EtaPT25 = Divide(FTT200, "JetGen/JetGen_EtaPT25_000000",
      FTT200, "JetGen/JetGenNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *JetGen_200_EtaPT200 = Divide(FTT200, "JetGen/JetGen_EtaPT200_000000",
      FTT200, "JetGen/JetGenNoMatching_EtaPT200_000000", 2);
   TGraphAsymmErrors *TkJetGen_140_PT = Divide(FTT140, "TkJetGen/TkJetGen_PT_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkJetGen_140_PT_Rebin = Divide(FTT140, "TkJetGen/TkJetGen_PT_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_PT_000000", -2);
   TGraphAsymmErrors *TkJetGen_140_PTEta10 = Divide(FTT140, "TkJetGen/TkJetGen_PTEta10_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkJetGen_140_PTEta10_Rebin = Divide(FTT140, "TkJetGen/TkJetGen_PTEta10_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_PTEta10_000000", -2);
   TGraphAsymmErrors *TkJetGen_140_PTEtaLarge = Divide(FTT140, "TkJetGen/TkJetGen_PTEtaLarge_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkJetGen_140_PTEtaLarge_Rebin = Divide(FTT140, "TkJetGen/TkJetGen_PTEtaLarge_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_PTEtaLarge_000000", -2);
   TGraphAsymmErrors *TkJetGen_140_Eta = Divide(FTT140, "TkJetGen/TkJetGen_Eta_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkJetGen_140_EtaPT20 = Divide(FTT140, "TkJetGen/TkJetGen_EtaPT20_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkJetGen_140_EtaPT25 = Divide(FTT140, "TkJetGen/TkJetGen_EtaPT25_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkJetGen_140_EtaPT200 = Divide(FTT140, "TkJetGen/TkJetGen_EtaPT200_000000",
      FTT140, "TkJetGen/TkJetGenNoMatching_EtaPT200_000000", 2);
   TGraphAsymmErrors *TkJetGen_200_PT = Divide(FTT200, "TkJetGen/TkJetGen_PT_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_PT_000000", 5);
   TGraphAsymmErrors *TkJetGen_200_PT_Rebin = Divide(FTT200, "TkJetGen/TkJetGen_PT_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_PT_000000", -2);
   TGraphAsymmErrors *TkJetGen_200_PTEta10 = Divide(FTT200, "TkJetGen/TkJetGen_PTEta10_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_PTEta10_000000", 5);
   TGraphAsymmErrors *TkJetGen_200_PTEta10_Rebin = Divide(FTT200, "TkJetGen/TkJetGen_PTEta10_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_PTEta10_000000", -2);
   TGraphAsymmErrors *TkJetGen_200_PTEtaLarge = Divide(FTT200, "TkJetGen/TkJetGen_PTEtaLarge_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_PTEtaLarge_000000", 5);
   TGraphAsymmErrors *TkJetGen_200_PTEtaLarge_Rebin = Divide(FTT200, "TkJetGen/TkJetGen_PTEtaLarge_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_PTEtaLarge_000000", -2);
   TGraphAsymmErrors *TkJetGen_200_Eta = Divide(FTT200, "TkJetGen/TkJetGen_Eta_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_Eta_000000", 2);
   TGraphAsymmErrors *TkJetGen_200_EtaPT20 = Divide(FTT200, "TkJetGen/TkJetGen_EtaPT20_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_EtaPT20_000000", 2);
   TGraphAsymmErrors *TkJetGen_200_EtaPT25 = Divide(FTT200, "TkJetGen/TkJetGen_EtaPT25_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_EtaPT25_000000", 2);
   TGraphAsymmErrors *TkJetGen_200_EtaPT200 = Divide(FTT200, "TkJetGen/TkJetGen_EtaPT200_000000",
      FTT200, "TkJetGen/TkJetGenNoMatching_EtaPT200_000000", 2);

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
   TkEGTyler_140_PT->SetTitle("TkEG, PT, PU140");
   TkEGTyler_140_PT_Rebin->SetTitle("TkEG, PT, PU140");
   TkEGTyler_140_PTEta10->SetTitle("TkEG, PT (|eta| > 1.0), PU140");
   TkEGTyler_140_PTEta10_Rebin->SetTitle("TkEG, PT (|eta| > 1.0), PU140");
   TkEGTyler_140_PTEtaLarge->SetTitle("TkEG, PT (|eta| < 1.0), PU140");
   TkEGTyler_140_PTEtaLarge_Rebin->SetTitle("TkEG, PT (|eta| < 1.0), PU140");
   TkEGTyler_140_Eta->SetTitle("TkEG, Eta, PU140");
   TkEGTyler_140_EtaPT20->SetTitle("TkEG, eta (PT > 20), PU140");
   TkEGTyler_140_EtaPT25->SetTitle("TkEG, eta (PT > 25), PU140");
   TkEGTyler_200_PT->SetTitle("TkEG, PT, PU200");
   TkEGTyler_200_PT_Rebin->SetTitle("TkEG, PT, PU200");
   TkEGTyler_200_PTEta10->SetTitle("TkEG, PT (|eta| > 1.0), PU200");
   TkEGTyler_200_PTEta10_Rebin->SetTitle("TkEG, PT (|eta| > 1.0), PU200");
   TkEGTyler_200_PTEtaLarge->SetTitle("TkEG, PT (|eta| < 1.0), PU200");
   TkEGTyler_200_PTEtaLarge_Rebin->SetTitle("TkEG, PT (|eta| < 1.0), PU200");
   TkEGTyler_200_Eta->SetTitle("TkEG, Eta, PU200");
   TkEGTyler_200_EtaPT20->SetTitle("TkEG, eta (PT > 20), PU200");
   TkEGTyler_200_EtaPT25->SetTitle("TkEG, eta (PT > 25), PU200");
   TkIsoEGTyler_140_PT->SetTitle("TkIsoEG, PT, PU140");
   TkIsoEGTyler_140_PT_Rebin->SetTitle("TkIsoEG, PT, PU140");
   TkIsoEGTyler_140_PTEta10->SetTitle("TkIsoEG, PT (|eta| > 1.0), PU140");
   TkIsoEGTyler_140_PTEta10_Rebin->SetTitle("TkIsoEG, PT (|eta| > 1.0), PU140");
   TkIsoEGTyler_140_PTEtaLarge->SetTitle("TkIsoEG, PT (|eta| < 1.0), PU140");
   TkIsoEGTyler_140_PTEtaLarge_Rebin->SetTitle("TkIsoEG, PT (|eta| < 1.0), PU140");
   TkIsoEGTyler_140_Eta->SetTitle("TkIsoEG, Eta, PU140");
   TkIsoEGTyler_140_EtaPT20->SetTitle("TkIsoEG, eta (PT > 20), PU140");
   TkIsoEGTyler_140_EtaPT25->SetTitle("TkIsoEG, eta (PT > 25), PU140");
   TkIsoEGTyler_200_PT->SetTitle("TkIsoEG, PT, PU200");
   TkIsoEGTyler_200_PT_Rebin->SetTitle("TkIsoEG, PT, PU200");
   TkIsoEGTyler_200_PTEta10->SetTitle("TkIsoEG, PT (|eta| < 1.0), PU200");
   TkIsoEGTyler_200_PTEta10_Rebin->SetTitle("TkIsoEG, PT (|eta| < 1.0), PU200");
   TkIsoEGTyler_200_PTEtaLarge->SetTitle("TkIsoEG, PT (|eta| > 1.0), PU200");
   TkIsoEGTyler_200_PTEtaLarge_Rebin->SetTitle("TkIsoEG, PT (|eta| > 1.0), PU200");
   TkIsoEGTyler_200_Eta->SetTitle("TkIsoEG, Eta, PU200");
   TkIsoEGTyler_200_EtaPT20->SetTitle("TkIsoEG, eta (PT > 20), PU200");
   TkIsoEGTyler_200_EtaPT25->SetTitle("TkIsoEG, eta (PT > 25), PU200");
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
   TkEMEG_140_PT->SetTitle("TkEM/EG, PT, PU140");
   TkEMEG_140_PT_Rebin->SetTitle("TkEM/EG, PT, PU140");
   TkEMEG_140_PTEta10->SetTitle("TkEM/EG, PT (|eta| > 1.0), PU140");
   TkEMEG_140_PTEta10_Rebin->SetTitle("TkEM/EG, PT (|eta| > 1.0), PU140");
   TkEMEG_140_PTEtaLarge->SetTitle("TkEM/EG, PT (|eta| < 1.0), PU140");
   TkEMEG_140_PTEtaLarge_Rebin->SetTitle("TkEM/EG, PT (|eta| < 1.0), PU140");
   TkEMEG_140_Eta->SetTitle("TkEM/EG, Eta, PU140");
   TkEMEG_140_EtaPT20->SetTitle("TkEM/EG, eta (PT > 20), PU140");
   TkEMEG_140_EtaPT25->SetTitle("TkEM/EG, eta (PT > 25), PU140");
   TkEMEG_200_PT->SetTitle("TkEM/EG, PT, PU200");
   TkEMEG_200_PT_Rebin->SetTitle("TkEM/EG, PT, PU200");
   TkEMEG_200_PTEta10->SetTitle("TkEM/EG, PT (|eta| > 1.0), PU200");
   TkEMEG_200_PTEta10_Rebin->SetTitle("TkEM/EG, PT (|eta| > 1.0), PU200");
   TkEMEG_200_PTEtaLarge->SetTitle("TkEM/EG, PT (|eta| < 1.0), PU200");
   TkEMEG_200_PTEtaLarge_Rebin->SetTitle("TkEM/EG, PT (|eta| < 1.0), PU200");
   TkEMEG_200_Eta->SetTitle("TkEM/EG, Eta, PU200");
   TkEMEG_200_EtaPT20->SetTitle("TkEM/EG, eta (PT > 20), PU200");
   TkEMEG_200_EtaPT25->SetTitle("TkEM/EG, eta (PT > 25), PU200");
   EG_140_PT->SetTitle("EG, PT, PU140");
   EG_140_PT_Rebin->SetTitle("EG, PT, PU140");
   EG_140_PTEta10->SetTitle("EG, PT (|eta| > 1.0), PU140");
   EG_140_PTEta10_Rebin->SetTitle("EG, PT (|eta| > 1.0), PU140");
   EG_140_PTEtaLarge->SetTitle("EG, PT (|eta| < 1.0), PU140");
   EG_140_PTEtaLarge_Rebin->SetTitle("EG, PT (|eta| < 1.0), PU140");
   EG_140_Eta->SetTitle("EG, Eta, PU140");
   EG_140_EtaPT20->SetTitle("EG, eta (PT > 20), PU140");
   EG_140_EtaPT25->SetTitle("EG, eta (PT > 25), PU140");
   EG_200_PT->SetTitle("EG, PT, PU200");
   EG_200_PT_Rebin->SetTitle("EG, PT, PU200");
   EG_200_PTEta10->SetTitle("EG, PT (|eta| > 1.0), PU200");
   EG_200_PTEta10_Rebin->SetTitle("EG, PT (|eta| > 1.0), PU200");
   EG_200_PTEtaLarge->SetTitle("EG, PT (|eta| < 1.0), PU200");
   EG_200_PTEtaLarge_Rebin->SetTitle("EG, PT (|eta| < 1.0), PU200");
   EG_200_Eta->SetTitle("EG, Eta, PU200");
   EG_200_EtaPT20->SetTitle("EG, eta (PT > 20), PU200");
   EG_200_EtaPT25->SetTitle("EG, eta (PT > 25), PU200");
   IsoEG_140_PT->SetTitle("IsoEG, PT, PU140");
   IsoEG_140_PT_Rebin->SetTitle("IsoEG, PT, PU140");
   IsoEG_140_PTEta10->SetTitle("IsoEG, PT (|eta| > 1.0), PU140");
   IsoEG_140_PTEta10_Rebin->SetTitle("IsoEG, PT (|eta| > 1.0), PU140");
   IsoEG_140_PTEtaLarge->SetTitle("IsoEG, PT (|eta| < 1.0), PU140");
   IsoEG_140_PTEtaLarge_Rebin->SetTitle("IsoEG, PT (|eta| < 1.0), PU140");
   IsoEG_140_Eta->SetTitle("IsoEG, Eta, PU140");
   IsoEG_140_EtaPT20->SetTitle("IsoEG, eta (PT > 20), PU140");
   IsoEG_140_EtaPT25->SetTitle("IsoEG, eta (PT > 25), PU140");
   IsoEG_200_PT->SetTitle("IsoEG, PT, PU200");
   IsoEG_200_PT_Rebin->SetTitle("IsoEG, PT, PU200");
   IsoEG_200_PTEta10->SetTitle("IsoEG, PT (|eta| > 1.0), PU200");
   IsoEG_200_PTEta10_Rebin->SetTitle("IsoEG, PT (|eta| > 1.0), PU200");
   IsoEG_200_PTEtaLarge->SetTitle("IsoEG, PT (|eta| < 1.0), PU200");
   IsoEG_200_PTEtaLarge_Rebin->SetTitle("IsoEG, PT (|eta| < 1.0), PU200");
   IsoEG_200_Eta->SetTitle("IsoEG, Eta, PU200");
   IsoEG_200_EtaPT20->SetTitle("IsoEG, eta (PT > 20), PU200");
   IsoEG_200_EtaPT25->SetTitle("IsoEG, eta (PT > 25), PU200");
   EGTyler_140_PT->SetTitle("EG, PT, PU140");
   EGTyler_140_PT_Rebin->SetTitle("EG, PT, PU140");
   EGTyler_140_PTEta10->SetTitle("EG, PT (|eta| > 1.0), PU140");
   EGTyler_140_PTEta10_Rebin->SetTitle("EG, PT (|eta| > 1.0), PU140");
   EGTyler_140_PTEtaLarge->SetTitle("EG, PT (|eta| < 1.0), PU140");
   EGTyler_140_PTEtaLarge_Rebin->SetTitle("EG, PT (|eta| < 1.0), PU140");
   EGTyler_140_Eta->SetTitle("EG, Eta, PU140");
   EGTyler_140_EtaPT20->SetTitle("EG, eta (PT > 20), PU140");
   EGTyler_140_EtaPT25->SetTitle("EG, eta (PT > 25), PU140");
   EGTyler_200_PT->SetTitle("EG, PT, PU200");
   EGTyler_200_PT_Rebin->SetTitle("EG, PT, PU200");
   EGTyler_200_PTEta10->SetTitle("EG, PT (|eta| > 1.0), PU200");
   EGTyler_200_PTEta10_Rebin->SetTitle("EG, PT (|eta| > 1.0), PU200");
   EGTyler_200_PTEtaLarge->SetTitle("EG, PT (|eta| < 1.0), PU200");
   EGTyler_200_PTEtaLarge_Rebin->SetTitle("EG, PT (|eta| < 1.0), PU200");
   EGTyler_200_Eta->SetTitle("EG, Eta, PU200");
   EGTyler_200_EtaPT20->SetTitle("EG, eta (PT > 20), PU200");
   EGTyler_200_EtaPT25->SetTitle("EG, eta (PT > 25), PU200");
   IsoEGTyler_140_PT->SetTitle("IsoEG, PT, PU140");
   IsoEGTyler_140_PT_Rebin->SetTitle("IsoEG, PT, PU140");
   IsoEGTyler_140_PTEta10->SetTitle("IsoEG, PT (|eta| > 1.0), PU140");
   IsoEGTyler_140_PTEta10_Rebin->SetTitle("IsoEG, PT (|eta| > 1.0), PU140");
   IsoEGTyler_140_PTEtaLarge->SetTitle("IsoEG, PT (|eta| < 1.0), PU140");
   IsoEGTyler_140_PTEtaLarge_Rebin->SetTitle("IsoEG, PT (|eta| < 1.0), PU140");
   IsoEGTyler_140_Eta->SetTitle("IsoEG, Eta, PU140");
   IsoEGTyler_140_EtaPT20->SetTitle("IsoEG, eta (PT > 20), PU140");
   IsoEGTyler_140_EtaPT25->SetTitle("IsoEG, eta (PT > 25), PU140");
   IsoEGTyler_200_PT->SetTitle("IsoEG, PT, PU200");
   IsoEGTyler_200_PT_Rebin->SetTitle("IsoEG, PT, PU200");
   IsoEGTyler_200_PTEta10->SetTitle("IsoEG, PT (|eta| > 1.0), PU200");
   IsoEGTyler_200_PTEta10_Rebin->SetTitle("IsoEG, PT (|eta| > 1.0), PU200");
   IsoEGTyler_200_PTEtaLarge->SetTitle("IsoEG, PT (|eta| < 1.0), PU200");
   IsoEGTyler_200_PTEtaLarge_Rebin->SetTitle("IsoEG, PT (|eta| < 1.0), PU200");
   IsoEGTyler_200_Eta->SetTitle("IsoEG, Eta, PU200");
   IsoEGTyler_200_EtaPT20->SetTitle("IsoEG, eta (PT > 20), PU200");
   IsoEGTyler_200_EtaPT25->SetTitle("IsoEG, eta (PT > 25), PU200");
   Jet_140_PT->SetTitle("Jet, PT, PU140");
   Jet_140_PT_Rebin->SetTitle("Jet, PT, PU140");
   Jet_140_PTEta10->SetTitle("Jet, PT (|eta| > 1.0), PU140");
   Jet_140_PTEta10_Rebin->SetTitle("Jet, PT (|eta| > 1.0), PU140");
   Jet_140_PTEtaLarge->SetTitle("Jet, PT (|eta| < 1.0), PU140");
   Jet_140_PTEtaLarge_Rebin->SetTitle("Jet, PT (|eta| < 1.0), PU140");
   Jet_140_Eta->SetTitle("Jet, Eta, PU140");
   Jet_140_EtaPT20->SetTitle("Jet, eta (PT > 20), PU140");
   Jet_140_EtaPT25->SetTitle("Jet, eta (PT > 25), PU140");
   Jet_140_EtaPT200->SetTitle("Jet, eta (PT > 200), PU140");
   Jet_200_PT->SetTitle("Jet, PT, PU200");
   Jet_200_PT_Rebin->SetTitle("Jet, PT, PU200");
   Jet_200_PTEta10->SetTitle("Jet, PT (|eta| > 1.0), PU200");
   Jet_200_PTEta10_Rebin->SetTitle("Jet, PT (|eta| > 1.0), PU200");
   Jet_200_PTEtaLarge->SetTitle("Jet, PT (|eta| < 1.0), PU200");
   Jet_200_PTEtaLarge_Rebin->SetTitle("Jet, PT (|eta| < 1.0), PU200");
   Jet_200_Eta->SetTitle("Jet, Eta, PU200");
   Jet_200_EtaPT20->SetTitle("Jet, eta (PT > 20), PU200");
   Jet_200_EtaPT25->SetTitle("Jet, eta (PT > 25), PU200");
   Jet_200_EtaPT200->SetTitle("Jet, eta (PT > 200), PU200");
   TkJet_140_PT->SetTitle("TkJet, PT, PU140");
   TkJet_140_PT_Rebin->SetTitle("TkJet, PT, PU140");
   TkJet_140_PTEta10->SetTitle("TkJet, PT (|eta| > 1.0), PU140");
   TkJet_140_PTEta10_Rebin->SetTitle("TkJet, PT (|eta| > 1.0), PU140");
   TkJet_140_PTEtaLarge->SetTitle("TkJet, PT (|eta| < 1.0), PU140");
   TkJet_140_PTEtaLarge_Rebin->SetTitle("TkJet, PT (|eta| < 1.0), PU140");
   TkJet_140_Eta->SetTitle("TkJet, Eta, PU140");
   TkJet_140_EtaPT20->SetTitle("TkJet, eta (PT > 20), PU140");
   TkJet_140_EtaPT25->SetTitle("TkJet, eta (PT > 25), PU140");
   TkJet_140_EtaPT200->SetTitle("TkJet, eta (PT > 200), PU140");
   TkJet_200_PT->SetTitle("TkJet, PT, PU200");
   TkJet_200_PT_Rebin->SetTitle("TkJet, PT, PU200");
   TkJet_200_PTEta10->SetTitle("TkJet, PT (|eta| > 1.0), PU200");
   TkJet_200_PTEta10_Rebin->SetTitle("TkJet, PT (|eta| > 1.0), PU200");
   TkJet_200_PTEtaLarge->SetTitle("TkJet, PT (|eta| < 1.0), PU200");
   TkJet_200_PTEtaLarge_Rebin->SetTitle("TkJet, PT (|eta| < 1.0), PU200");
   TkJet_200_Eta->SetTitle("TkJet, Eta, PU200");
   TkJet_200_EtaPT20->SetTitle("TkJet, eta (PT > 20), PU200");
   TkJet_200_EtaPT25->SetTitle("TkJet, eta (PT > 25), PU200");
   TkJet_200_EtaPT200->SetTitle("TkJet, eta (PT > 200), PU200");
   JetGen_140_PT->SetTitle("Jet, PT, PU140");
   JetGen_140_PT_Rebin->SetTitle("Jet, PT, PU140");
   JetGen_140_PTEta10->SetTitle("Jet, PT (|eta| > 1.0), PU140");
   JetGen_140_PTEta10_Rebin->SetTitle("Jet, PT (|eta| > 1.0), PU140");
   JetGen_140_PTEtaLarge->SetTitle("Jet, PT (|eta| < 1.0), PU140");
   JetGen_140_PTEtaLarge_Rebin->SetTitle("Jet, PT (|eta| < 1.0), PU140");
   JetGen_140_Eta->SetTitle("Jet, Eta, PU140");
   JetGen_140_EtaPT20->SetTitle("Jet, eta (PT > 20), PU140");
   JetGen_140_EtaPT25->SetTitle("Jet, eta (PT > 25), PU140");
   JetGen_140_EtaPT200->SetTitle("Jet, eta (PT > 200), PU140");
   JetGen_200_PT->SetTitle("Jet, PT, PU200");
   JetGen_200_PT_Rebin->SetTitle("Jet, PT, PU200");
   JetGen_200_PTEta10->SetTitle("Jet, PT (|eta| > 1.0), PU200");
   JetGen_200_PTEta10_Rebin->SetTitle("Jet, PT (|eta| > 1.0), PU200");
   JetGen_200_PTEtaLarge->SetTitle("Jet, PT (|eta| < 1.0), PU200");
   JetGen_200_PTEtaLarge_Rebin->SetTitle("Jet, PT (|eta| < 1.0), PU200");
   JetGen_200_Eta->SetTitle("Jet, Eta, PU200");
   JetGen_200_EtaPT20->SetTitle("Jet, eta (PT > 20), PU200");
   JetGen_200_EtaPT25->SetTitle("Jet, eta (PT > 25), PU200");
   JetGen_200_EtaPT200->SetTitle("Jet, eta (PT > 200), PU200");
   TkJetGen_140_PT->SetTitle("TkJet, PT, PU140");
   TkJetGen_140_PT_Rebin->SetTitle("TkJet, PT, PU140");
   TkJetGen_140_PTEta10->SetTitle("TkJet, PT (|eta| > 1.0), PU140");
   TkJetGen_140_PTEta10_Rebin->SetTitle("TkJet, PT (|eta| > 1.0), PU140");
   TkJetGen_140_PTEtaLarge->SetTitle("TkJet, PT (|eta| < 1.0), PU140");
   TkJetGen_140_PTEtaLarge_Rebin->SetTitle("TkJet, PT (|eta| < 1.0), PU140");
   TkJetGen_140_Eta->SetTitle("TkJet, Eta, PU140");
   TkJetGen_140_EtaPT20->SetTitle("TkJet, eta (PT > 20), PU140");
   TkJetGen_140_EtaPT25->SetTitle("TkJet, eta (PT > 25), PU140");
   TkJetGen_140_EtaPT200->SetTitle("TkJet, eta (PT > 200), PU140");
   TkJetGen_200_PT->SetTitle("TkJet, PT, PU200");
   TkJetGen_200_PT_Rebin->SetTitle("TkJet, PT, PU200");
   TkJetGen_200_PTEta10->SetTitle("TkJet, PT (|eta| > 1.0), PU200");
   TkJetGen_200_PTEta10_Rebin->SetTitle("TkJet, PT (|eta| > 1.0), PU200");
   TkJetGen_200_PTEtaLarge->SetTitle("TkJet, PT (|eta| < 1.0), PU200");
   TkJetGen_200_PTEtaLarge_Rebin->SetTitle("TkJet, PT (|eta| < 1.0), PU200");
   TkJetGen_200_Eta->SetTitle("TkJet, Eta, PU200");
   TkJetGen_200_EtaPT20->SetTitle("TkJet, eta (PT > 20), PU200");
   TkJetGen_200_EtaPT25->SetTitle("TkJet, eta (PT > 25), PU200");
   TkJetGen_200_EtaPT200->SetTitle("TkJet, eta (PT > 200), PU200");

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
   TkEGTyler_140_PT->GetXaxis()->SetTitle("PT");
   TkEGTyler_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkEGTyler_140_PTEta10->GetXaxis()->SetTitle("PT");
   TkEGTyler_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkEGTyler_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkEGTyler_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkEGTyler_140_Eta->GetXaxis()->SetTitle("Eta");
   TkEGTyler_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkEGTyler_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkEGTyler_200_PT->GetXaxis()->SetTitle("PT");
   TkEGTyler_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkEGTyler_200_PTEta10->GetXaxis()->SetTitle("PT");
   TkEGTyler_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkEGTyler_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkEGTyler_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkEGTyler_200_Eta->GetXaxis()->SetTitle("Eta");
   TkEGTyler_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkEGTyler_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkIsoEGTyler_140_PT->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_140_PTEta10->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_140_Eta->GetXaxis()->SetTitle("Eta");
   TkIsoEGTyler_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkIsoEGTyler_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkIsoEGTyler_200_PT->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_200_PTEta10->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkIsoEGTyler_200_Eta->GetXaxis()->SetTitle("Eta");
   TkIsoEGTyler_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkIsoEGTyler_200_EtaPT25->GetXaxis()->SetTitle("Eta");
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
   TkEMEG_140_PT->GetXaxis()->SetTitle("PT");
   TkEMEG_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkEMEG_140_PTEta10->GetXaxis()->SetTitle("PT");
   TkEMEG_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkEMEG_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkEMEG_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkEMEG_140_Eta->GetXaxis()->SetTitle("Eta");
   TkEMEG_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkEMEG_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkEMEG_200_PT->GetXaxis()->SetTitle("PT");
   TkEMEG_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkEMEG_200_PTEta10->GetXaxis()->SetTitle("PT");
   TkEMEG_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkEMEG_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkEMEG_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkEMEG_200_Eta->GetXaxis()->SetTitle("Eta");
   TkEMEG_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkEMEG_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   EG_140_PT->GetXaxis()->SetTitle("PT");
   EG_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   EG_140_PTEta10->GetXaxis()->SetTitle("PT");
   EG_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   EG_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   EG_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   EG_140_Eta->GetXaxis()->SetTitle("Eta");
   EG_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   EG_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   EG_200_PT->GetXaxis()->SetTitle("PT");
   EG_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   EG_200_PTEta10->GetXaxis()->SetTitle("PT");
   EG_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   EG_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   EG_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   EG_200_Eta->GetXaxis()->SetTitle("Eta");
   EG_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   EG_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   IsoEG_140_PT->GetXaxis()->SetTitle("PT");
   IsoEG_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   IsoEG_140_PTEta10->GetXaxis()->SetTitle("PT");
   IsoEG_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   IsoEG_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   IsoEG_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   IsoEG_140_Eta->GetXaxis()->SetTitle("Eta");
   IsoEG_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   IsoEG_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   IsoEG_200_PT->GetXaxis()->SetTitle("PT");
   IsoEG_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   IsoEG_200_PTEta10->GetXaxis()->SetTitle("PT");
   IsoEG_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   IsoEG_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   IsoEG_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   IsoEG_200_Eta->GetXaxis()->SetTitle("Eta");
   IsoEG_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   IsoEG_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   EGTyler_140_PT->GetXaxis()->SetTitle("PT");
   EGTyler_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   EGTyler_140_PTEta10->GetXaxis()->SetTitle("PT");
   EGTyler_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   EGTyler_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   EGTyler_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   EGTyler_140_Eta->GetXaxis()->SetTitle("Eta");
   EGTyler_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   EGTyler_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   EGTyler_200_PT->GetXaxis()->SetTitle("PT");
   EGTyler_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   EGTyler_200_PTEta10->GetXaxis()->SetTitle("PT");
   EGTyler_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   EGTyler_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   EGTyler_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   EGTyler_200_Eta->GetXaxis()->SetTitle("Eta");
   EGTyler_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   EGTyler_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   IsoEGTyler_140_PT->GetXaxis()->SetTitle("PT");
   IsoEGTyler_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   IsoEGTyler_140_PTEta10->GetXaxis()->SetTitle("PT");
   IsoEGTyler_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   IsoEGTyler_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   IsoEGTyler_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   IsoEGTyler_140_Eta->GetXaxis()->SetTitle("Eta");
   IsoEGTyler_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   IsoEGTyler_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   IsoEGTyler_200_PT->GetXaxis()->SetTitle("PT");
   IsoEGTyler_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   IsoEGTyler_200_PTEta10->GetXaxis()->SetTitle("PT");
   IsoEGTyler_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   IsoEGTyler_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   IsoEGTyler_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   IsoEGTyler_200_Eta->GetXaxis()->SetTitle("Eta");
   IsoEGTyler_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   IsoEGTyler_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   Jet_140_PT->GetXaxis()->SetTitle("PT");
   Jet_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   Jet_140_PTEta10->GetXaxis()->SetTitle("PT");
   Jet_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   Jet_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   Jet_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   Jet_140_Eta->GetXaxis()->SetTitle("Eta");
   Jet_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   Jet_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   Jet_140_EtaPT200->GetXaxis()->SetTitle("Eta");
   Jet_200_PT->GetXaxis()->SetTitle("PT");
   Jet_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   Jet_200_PTEta10->GetXaxis()->SetTitle("PT");
   Jet_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   Jet_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   Jet_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   Jet_200_Eta->GetXaxis()->SetTitle("Eta");
   Jet_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   Jet_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   Jet_200_EtaPT200->GetXaxis()->SetTitle("Eta");
   TkJet_140_PT->GetXaxis()->SetTitle("PT");
   TkJet_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkJet_140_PTEta10->GetXaxis()->SetTitle("PT");
   TkJet_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkJet_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkJet_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkJet_140_Eta->GetXaxis()->SetTitle("Eta");
   TkJet_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkJet_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkJet_140_EtaPT200->GetXaxis()->SetTitle("Eta");
   TkJet_200_PT->GetXaxis()->SetTitle("PT");
   TkJet_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkJet_200_PTEta10->GetXaxis()->SetTitle("PT");
   TkJet_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkJet_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkJet_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkJet_200_Eta->GetXaxis()->SetTitle("Eta");
   TkJet_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkJet_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkJet_200_EtaPT200->GetXaxis()->SetTitle("Eta");
   JetGen_140_PT->GetXaxis()->SetTitle("PT");
   JetGen_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   JetGen_140_PTEta10->GetXaxis()->SetTitle("PT");
   JetGen_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   JetGen_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   JetGen_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   JetGen_140_Eta->GetXaxis()->SetTitle("Eta");
   JetGen_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   JetGen_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   JetGen_140_EtaPT200->GetXaxis()->SetTitle("Eta");
   JetGen_200_PT->GetXaxis()->SetTitle("PT");
   JetGen_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   JetGen_200_PTEta10->GetXaxis()->SetTitle("PT");
   JetGen_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   JetGen_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   JetGen_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   JetGen_200_Eta->GetXaxis()->SetTitle("Eta");
   JetGen_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   JetGen_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   JetGen_200_EtaPT200->GetXaxis()->SetTitle("Eta");
   TkJetGen_140_PT->GetXaxis()->SetTitle("PT");
   TkJetGen_140_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkJetGen_140_PTEta10->GetXaxis()->SetTitle("PT");
   TkJetGen_140_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkJetGen_140_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkJetGen_140_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkJetGen_140_Eta->GetXaxis()->SetTitle("Eta");
   TkJetGen_140_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkJetGen_140_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkJetGen_140_EtaPT200->GetXaxis()->SetTitle("Eta");
   TkJetGen_200_PT->GetXaxis()->SetTitle("PT");
   TkJetGen_200_PT_Rebin->GetXaxis()->SetTitle("PT");
   TkJetGen_200_PTEta10->GetXaxis()->SetTitle("PT");
   TkJetGen_200_PTEta10_Rebin->GetXaxis()->SetTitle("PT");
   TkJetGen_200_PTEtaLarge->GetXaxis()->SetTitle("PT");
   TkJetGen_200_PTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   TkJetGen_200_Eta->GetXaxis()->SetTitle("Eta");
   TkJetGen_200_EtaPT20->GetXaxis()->SetTitle("Eta");
   TkJetGen_200_EtaPT25->GetXaxis()->SetTitle("Eta");
   TkJetGen_200_EtaPT200->GetXaxis()->SetTitle("Eta");

   PdfFileHelper PdfFile("ResultEfficiencyPlots.pdf");
   PdfFile.AddTextPage("Efficiency plots");
   
   PdfFileHelper PdfFile2("ResultIndividualEfficiencyPlots.pdf");
   PdfFile2.AddTextPage("Individual efficiency plots");

   vector<string> Explanation(15);
   Explanation[0] = "Look at gen-electron pt/eta for those within acceptance";
   Explanation[1] = "";
   Explanation[2] = "Numerator = Gen-particle spectrum";
   Explanation[3] = "Denominator = Gen-particle spectrum & track";
   Explanation[4] = "      EG/IsoEG/EM/jet object match";
   Explanation[5] = "";
   Explanation[6] = "Electron ones from W->e#nu sample";
   Explanation[7] = "EM ones from H->#gamma#gamma sample";
   Explanation[8] = "Jets are from ttbar sample";
   Explanation[9] = "   result with gen-jets are at the end";
   Explanation[10] = "";
   Explanation[11] = "Watch out for PT spectrum!";
   PdfFile.AddTextPage(Explanation);
   PdfFile2.AddTextPage(Explanation);

   PdfFile.AddTextPage("Gen-spectra");

   AddSpectrum(PdfFile, FWENu140, "TkEG/TkEGNoMatching_PT_000000",          "W->e#nu electrons (PU 140)");
   AddSpectrum(PdfFile, FWENu200, "TkEG/TkEGNoMatching_PT_000000",          "W->e#nu electrons (PU 200)");
   AddSpectrum(PdfFile, FWENu140, "TkEG/TkEGNoMatching_Eta_000000",         "W->e#nu electrons (PU 140)");
   AddSpectrum(PdfFile, FWENu200, "TkEG/TkEGNoMatching_Eta_000000",         "W->e#nu electrons (PU 200)");
   AddSpectrum(PdfFile, FHgg140,  "TkEM/TkEMNoMatching_PT_000000",          "H->#gamma#gamma photons (PU 140)");
   AddSpectrum(PdfFile, FHgg200,  "TkEM/TkEMNoMatching_PT_000000",          "H->#gamma#gamma photons (PU 200)");
   AddSpectrum(PdfFile, FHgg140,  "TkEM/TkEMNoMatching_Eta_000000",         "H->#gamma#gamma photons (PU 140)");
   AddSpectrum(PdfFile, FHgg200,  "TkEM/TkEMNoMatching_Eta_000000",         "H->#gamma#gamma photons (PU 200)");
   AddSpectrum(PdfFile, FTT140,   "TkJet/TkJetNoMatching_PT_000000",        "TTbar partons (PU 140)");
   AddSpectrum(PdfFile, FTT200,   "TkJet/TkJetNoMatching_PT_000000",        "TTbar partons (PU 200)");
   AddSpectrum(PdfFile, FTT140,   "TkJet/TkJetNoMatching_Eta_000000",       "TTbar partons (PU 140)");
   AddSpectrum(PdfFile, FTT200,   "TkJet/TkJetNoMatching_Eta_000000",       "TTbar partons (PU 200)");
   AddSpectrum(PdfFile, FTT140,   "TkJetGen/TkJetGenNoMatching_PT_000000",  "TTbar gen-jets (PU 140)");
   AddSpectrum(PdfFile, FTT200,   "TkJetGen/TkJetGenNoMatching_PT_000000",  "TTbar gen-jets (PU 200)");
   AddSpectrum(PdfFile, FTT140,   "TkJetGen/TkJetGenNoMatching_Eta_000000", "TTbar gen-jets (PU 140)");
   AddSpectrum(PdfFile, FTT200,   "TkJetGen/TkJetGenNoMatching_Eta_000000", "TTbar gen-jets (PU 200)");

   PdfFile2.AddPlot(TkEG_140_PT, "ap");
   PdfFile2.AddPlot(TkEG_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkEG_140_PTEta10, "ap");
   PdfFile2.AddPlot(TkEG_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkEG_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkEG_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkEG_140_Eta, "ap");
   PdfFile2.AddPlot(TkEG_140_EtaPT20, "ap");
   PdfFile2.AddPlot(TkEG_140_EtaPT25, "ap");
   PdfFile2.AddPlot(TkEG_200_PT, "ap");
   PdfFile2.AddPlot(TkEG_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkEG_200_PTEta10, "ap");
   PdfFile2.AddPlot(TkEG_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkEG_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkEG_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkEG_200_Eta, "ap");
   PdfFile2.AddPlot(TkEG_200_EtaPT20, "ap");
   PdfFile2.AddPlot(TkEG_200_EtaPT25, "ap");
   PdfFile2.AddPlot(TkIsoEG_140_PT, "ap");
   PdfFile2.AddPlot(TkIsoEG_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEG_140_PTEta10, "ap");
   PdfFile2.AddPlot(TkIsoEG_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEG_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkIsoEG_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEG_140_Eta, "ap");
   PdfFile2.AddPlot(TkIsoEG_140_EtaPT20, "ap");
   PdfFile2.AddPlot(TkIsoEG_140_EtaPT25, "ap");
   PdfFile2.AddPlot(TkIsoEG_200_PT, "ap");
   PdfFile2.AddPlot(TkIsoEG_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEG_200_PTEta10, "ap");
   PdfFile2.AddPlot(TkIsoEG_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEG_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkIsoEG_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEG_200_Eta, "ap");
   PdfFile2.AddPlot(TkIsoEG_200_EtaPT20, "ap");
   PdfFile2.AddPlot(TkIsoEG_200_EtaPT25, "ap");
   PdfFile2.AddPlot(TkEGTyler_140_PT, "ap");
   PdfFile2.AddPlot(TkEGTyler_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkEGTyler_140_PTEta10, "ap");
   PdfFile2.AddPlot(TkEGTyler_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkEGTyler_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkEGTyler_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkEGTyler_140_Eta, "ap");
   PdfFile2.AddPlot(TkEGTyler_140_EtaPT20, "ap");
   PdfFile2.AddPlot(TkEGTyler_140_EtaPT25, "ap");
   PdfFile2.AddPlot(TkEGTyler_200_PT, "ap");
   PdfFile2.AddPlot(TkEGTyler_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkEGTyler_200_PTEta10, "ap");
   PdfFile2.AddPlot(TkEGTyler_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkEGTyler_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkEGTyler_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkEGTyler_200_Eta, "ap");
   PdfFile2.AddPlot(TkEGTyler_200_EtaPT20, "ap");
   PdfFile2.AddPlot(TkEGTyler_200_EtaPT25, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_140_PT, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_140_PTEta10, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_140_Eta, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_140_EtaPT20, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_140_EtaPT25, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_200_PT, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_200_PTEta10, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_200_Eta, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_200_EtaPT20, "ap");
   PdfFile2.AddPlot(TkIsoEGTyler_200_EtaPT25, "ap");
   PdfFile2.AddPlot(TkEM_140_PT, "ap");
   PdfFile2.AddPlot(TkEM_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkEM_140_PTEta10, "ap");
   PdfFile2.AddPlot(TkEM_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkEM_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkEM_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkEM_140_Eta, "ap");
   PdfFile2.AddPlot(TkEM_140_EtaPT20, "ap");
   PdfFile2.AddPlot(TkEM_140_EtaPT25, "ap");
   PdfFile2.AddPlot(TkEM_200_PT, "ap");
   PdfFile2.AddPlot(TkEM_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkEM_200_PTEta10, "ap");
   PdfFile2.AddPlot(TkEM_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkEM_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkEM_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkEM_200_Eta, "ap");
   PdfFile2.AddPlot(TkEM_200_EtaPT20, "ap");
   PdfFile2.AddPlot(TkEM_200_EtaPT25, "ap");
   PdfFile2.AddPlot(TkEMEG_140_PT, "ap");
   PdfFile2.AddPlot(TkEMEG_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkEMEG_140_PTEta10, "ap");
   PdfFile2.AddPlot(TkEMEG_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkEMEG_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkEMEG_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkEMEG_140_Eta, "ap");
   PdfFile2.AddPlot(TkEMEG_140_EtaPT20, "ap");
   PdfFile2.AddPlot(TkEMEG_140_EtaPT25, "ap");
   PdfFile2.AddPlot(TkEMEG_200_PT, "ap");
   PdfFile2.AddPlot(TkEMEG_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkEMEG_200_PTEta10, "ap");
   PdfFile2.AddPlot(TkEMEG_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkEMEG_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkEMEG_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkEMEG_200_Eta, "ap");
   PdfFile2.AddPlot(TkEMEG_200_EtaPT20, "ap");
   PdfFile2.AddPlot(TkEMEG_200_EtaPT25, "ap");
   PdfFile2.AddPlot(EG_140_PT, "ap");
   PdfFile2.AddPlot(EG_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(EG_140_PTEta10, "ap");
   PdfFile2.AddPlot(EG_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(EG_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(EG_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(EG_140_Eta, "ap");
   PdfFile2.AddPlot(EG_140_EtaPT20, "ap");
   PdfFile2.AddPlot(EG_140_EtaPT25, "ap");
   PdfFile2.AddPlot(EG_200_PT, "ap");
   PdfFile2.AddPlot(EG_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(EG_200_PTEta10, "ap");
   PdfFile2.AddPlot(EG_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(EG_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(EG_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(EG_200_Eta, "ap");
   PdfFile2.AddPlot(EG_200_EtaPT20, "ap");
   PdfFile2.AddPlot(EG_200_EtaPT25, "ap");
   PdfFile2.AddPlot(IsoEG_140_PT, "ap");
   PdfFile2.AddPlot(IsoEG_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(IsoEG_140_PTEta10, "ap");
   PdfFile2.AddPlot(IsoEG_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(IsoEG_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(IsoEG_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(IsoEG_140_Eta, "ap");
   PdfFile2.AddPlot(IsoEG_140_EtaPT20, "ap");
   PdfFile2.AddPlot(IsoEG_140_EtaPT25, "ap");
   PdfFile2.AddPlot(IsoEG_200_PT, "ap");
   PdfFile2.AddPlot(IsoEG_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(IsoEG_200_PTEta10, "ap");
   PdfFile2.AddPlot(IsoEG_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(IsoEG_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(IsoEG_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(IsoEG_200_Eta, "ap");
   PdfFile2.AddPlot(IsoEG_200_EtaPT20, "ap");
   PdfFile2.AddPlot(IsoEG_200_EtaPT25, "ap");
   PdfFile2.AddPlot(EGTyler_140_PT, "ap");
   PdfFile2.AddPlot(EGTyler_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(EGTyler_140_PTEta10, "ap");
   PdfFile2.AddPlot(EGTyler_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(EGTyler_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(EGTyler_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(EGTyler_140_Eta, "ap");
   PdfFile2.AddPlot(EGTyler_140_EtaPT20, "ap");
   PdfFile2.AddPlot(EGTyler_140_EtaPT25, "ap");
   PdfFile2.AddPlot(EGTyler_200_PT, "ap");
   PdfFile2.AddPlot(EGTyler_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(EGTyler_200_PTEta10, "ap");
   PdfFile2.AddPlot(EGTyler_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(EGTyler_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(EGTyler_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(EGTyler_200_Eta, "ap");
   PdfFile2.AddPlot(EGTyler_200_EtaPT20, "ap");
   PdfFile2.AddPlot(EGTyler_200_EtaPT25, "ap");
   PdfFile2.AddPlot(IsoEGTyler_140_PT, "ap");
   PdfFile2.AddPlot(IsoEGTyler_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(IsoEGTyler_140_PTEta10, "ap");
   PdfFile2.AddPlot(IsoEGTyler_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(IsoEGTyler_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(IsoEGTyler_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(IsoEGTyler_140_Eta, "ap");
   PdfFile2.AddPlot(IsoEGTyler_140_EtaPT20, "ap");
   PdfFile2.AddPlot(IsoEGTyler_140_EtaPT25, "ap");
   PdfFile2.AddPlot(IsoEGTyler_200_PT, "ap");
   PdfFile2.AddPlot(IsoEGTyler_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(IsoEGTyler_200_PTEta10, "ap");
   PdfFile2.AddPlot(IsoEGTyler_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(IsoEGTyler_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(IsoEGTyler_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(IsoEGTyler_200_Eta, "ap");
   PdfFile2.AddPlot(IsoEGTyler_200_EtaPT20, "ap");
   PdfFile2.AddPlot(IsoEGTyler_200_EtaPT25, "ap");
   PdfFile2.AddPlot(Jet_140_PT, "ap");
   PdfFile2.AddPlot(Jet_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(Jet_140_PTEta10, "ap");
   PdfFile2.AddPlot(Jet_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(Jet_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(Jet_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(Jet_140_Eta, "ap");
   PdfFile2.AddPlot(Jet_140_EtaPT20, "ap");
   PdfFile2.AddPlot(Jet_140_EtaPT25, "ap");
   PdfFile2.AddPlot(Jet_140_EtaPT200, "ap");
   PdfFile2.AddPlot(Jet_200_PT, "ap");
   PdfFile2.AddPlot(Jet_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(Jet_200_PTEta10, "ap");
   PdfFile2.AddPlot(Jet_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(Jet_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(Jet_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(Jet_200_Eta, "ap");
   PdfFile2.AddPlot(Jet_200_EtaPT20, "ap");
   PdfFile2.AddPlot(Jet_200_EtaPT25, "ap");
   PdfFile2.AddPlot(Jet_200_EtaPT200, "ap");
   PdfFile2.AddPlot(TkJet_140_PT, "ap");
   PdfFile2.AddPlot(TkJet_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkJet_140_PTEta10, "ap");
   PdfFile2.AddPlot(TkJet_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkJet_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkJet_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkJet_140_Eta, "ap");
   PdfFile2.AddPlot(TkJet_140_EtaPT20, "ap");
   PdfFile2.AddPlot(TkJet_140_EtaPT25, "ap");
   PdfFile2.AddPlot(TkJet_140_EtaPT200, "ap");
   PdfFile2.AddPlot(TkJet_200_PT, "ap");
   PdfFile2.AddPlot(TkJet_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkJet_200_PTEta10, "ap");
   PdfFile2.AddPlot(TkJet_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkJet_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkJet_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkJet_200_Eta, "ap");
   PdfFile2.AddPlot(TkJet_200_EtaPT20, "ap");
   PdfFile2.AddPlot(TkJet_200_EtaPT25, "ap");
   PdfFile2.AddPlot(TkJet_200_EtaPT200, "ap");
   PdfFile2.AddPlot(JetGen_140_PT, "ap");
   PdfFile2.AddPlot(JetGen_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(JetGen_140_PTEta10, "ap");
   PdfFile2.AddPlot(JetGen_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(JetGen_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(JetGen_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(JetGen_140_Eta, "ap");
   PdfFile2.AddPlot(JetGen_140_EtaPT20, "ap");
   PdfFile2.AddPlot(JetGen_140_EtaPT25, "ap");
   PdfFile2.AddPlot(JetGen_140_EtaPT200, "ap");
   PdfFile2.AddPlot(JetGen_200_PT, "ap");
   PdfFile2.AddPlot(JetGen_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(JetGen_200_PTEta10, "ap");
   PdfFile2.AddPlot(JetGen_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(JetGen_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(JetGen_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(JetGen_200_Eta, "ap");
   PdfFile2.AddPlot(JetGen_200_EtaPT20, "ap");
   PdfFile2.AddPlot(JetGen_200_EtaPT25, "ap");
   PdfFile2.AddPlot(JetGen_200_EtaPT200, "ap");
   PdfFile2.AddPlot(TkJetGen_140_PT, "ap");
   PdfFile2.AddPlot(TkJetGen_140_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkJetGen_140_PTEta10, "ap");
   PdfFile2.AddPlot(TkJetGen_140_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkJetGen_140_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkJetGen_140_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkJetGen_140_Eta, "ap");
   PdfFile2.AddPlot(TkJetGen_140_EtaPT20, "ap");
   PdfFile2.AddPlot(TkJetGen_140_EtaPT25, "ap");
   PdfFile2.AddPlot(TkJetGen_140_EtaPT200, "ap");
   PdfFile2.AddPlot(TkJetGen_200_PT, "ap");
   PdfFile2.AddPlot(TkJetGen_200_PT_Rebin, "ap");
   PdfFile2.AddPlot(TkJetGen_200_PTEta10, "ap");
   PdfFile2.AddPlot(TkJetGen_200_PTEta10_Rebin, "ap");
   PdfFile2.AddPlot(TkJetGen_200_PTEtaLarge, "ap");
   PdfFile2.AddPlot(TkJetGen_200_PTEtaLarge_Rebin, "ap");
   PdfFile2.AddPlot(TkJetGen_200_Eta, "ap");
   PdfFile2.AddPlot(TkJetGen_200_EtaPT20, "ap");
   PdfFile2.AddPlot(TkJetGen_200_EtaPT25, "ap");
   PdfFile2.AddPlot(TkJetGen_200_EtaPT200, "ap");
   
   PdfFile.AddTextPage("Summary plots");

   AddFourPlots(PdfFile, TkEG_140_PT_Rebin, TkEG_200_PT_Rebin, TkIsoEG_140_PT_Rebin, TkIsoEG_200_PT_Rebin, "|eta| < 2.4", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG_140_PTEta10_Rebin, TkEG_200_PTEta10_Rebin, TkIsoEG_140_PTEta10_Rebin, TkIsoEG_200_PTEta10_Rebin, "|eta| < 1.0", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG_140_PTEtaLarge_Rebin, TkEG_200_PTEtaLarge_Rebin, TkIsoEG_140_PTEtaLarge_Rebin, TkIsoEG_200_PTEtaLarge_Rebin, "|eta| > 1.0", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG_140_Eta, TkEG_200_Eta, TkIsoEG_140_Eta, TkIsoEG_200_Eta, "PT > 0", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG_140_EtaPT20, TkEG_200_EtaPT20, TkIsoEG_140_EtaPT20, TkIsoEG_200_EtaPT20, "PT > 20", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG_140_EtaPT25, TkEG_200_EtaPT25, TkIsoEG_140_EtaPT25, TkIsoEG_200_EtaPT25, "PT > 25", "TkEG", "TkIsoEG");
   
   AddFourPlots(PdfFile, TkEGTyler_140_PT_Rebin, TkEGTyler_200_PT_Rebin, TkIsoEGTyler_140_PT_Rebin, TkIsoEGTyler_200_PT_Rebin, "|eta| < 2.4", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler_140_PTEta10_Rebin, TkEGTyler_200_PTEta10_Rebin, TkIsoEGTyler_140_PTEta10_Rebin, TkIsoEGTyler_200_PTEta10_Rebin, "|eta| < 1.0", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler_140_PTEtaLarge_Rebin, TkEGTyler_200_PTEtaLarge_Rebin, TkIsoEGTyler_140_PTEtaLarge_Rebin, TkIsoEGTyler_200_PTEtaLarge_Rebin, "|eta| > 1.0", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler_140_Eta, TkEGTyler_200_Eta, TkIsoEGTyler_140_Eta, TkIsoEGTyler_200_Eta, "PT > 0", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler_140_EtaPT20, TkEGTyler_200_EtaPT20, TkIsoEGTyler_140_EtaPT20, TkIsoEGTyler_200_EtaPT20, "PT > 20", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler_140_EtaPT25, TkEGTyler_200_EtaPT25, TkIsoEGTyler_140_EtaPT25, TkIsoEGTyler_200_EtaPT25, "PT > 25", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   
   AddTwoPlots(PdfFile, TkEM_140_PT_Rebin, TkEM_200_PT_Rebin, "|eta| < 2.4", "TkEM");
   AddTwoPlots(PdfFile, TkEM_140_PTEta10_Rebin, TkEM_200_PTEta10_Rebin, "|eta| < 1.0", "TkEM");
   AddTwoPlots(PdfFile, TkEM_140_PTEtaLarge_Rebin, TkEM_200_PTEtaLarge_Rebin, "|eta| > 1.0", "TkEM");
   AddTwoPlots(PdfFile, TkEM_140_Eta, TkEM_200_Eta, "PT > 0", "TkEM");
   AddTwoPlots(PdfFile, TkEM_140_EtaPT20, TkEM_200_EtaPT20, "PT > 20", "TkEM");
   AddTwoPlots(PdfFile, TkEM_140_EtaPT25, TkEM_200_EtaPT25, "PT > 25", "TkEM");
   
   AddTwoPlots(PdfFile, TkEMEG_140_PT_Rebin, TkEMEG_200_PT_Rebin, "|eta| < 2.4", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG_140_PTEta10_Rebin, TkEMEG_200_PTEta10_Rebin, "|eta| < 1.0", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG_140_PTEtaLarge_Rebin, TkEMEG_200_PTEtaLarge_Rebin, "|eta| > 1.0", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG_140_Eta, TkEMEG_200_Eta, "PT > 0", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG_140_EtaPT20, TkEMEG_200_EtaPT20, "PT > 20", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG_140_EtaPT25, TkEMEG_200_EtaPT25, "PT > 25", "TkEM/EG");

   AddFourPlots(PdfFile, EG_140_PT_Rebin, EG_200_PT_Rebin, IsoEG_140_PT_Rebin, IsoEG_200_PT_Rebin, "|eta| < 2.4", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG_140_PTEta10_Rebin, EG_200_PTEta10_Rebin, IsoEG_140_PTEta10_Rebin, IsoEG_200_PTEta10_Rebin, "|eta| < 1.0", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG_140_PTEtaLarge_Rebin, EG_200_PTEtaLarge_Rebin, IsoEG_140_PTEtaLarge_Rebin, IsoEG_200_PTEtaLarge_Rebin, "|eta| > 1.0", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG_140_Eta, EG_200_Eta, IsoEG_140_Eta, IsoEG_200_Eta, "PT > 0", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG_140_EtaPT20, EG_200_EtaPT20, IsoEG_140_EtaPT20, IsoEG_200_EtaPT20, "PT > 20", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG_140_EtaPT25, EG_200_EtaPT25, IsoEG_140_EtaPT25, IsoEG_200_EtaPT25, "PT > 25", "EG", "IsoEG");
   
   AddFourPlots(PdfFile, EGTyler_140_PT_Rebin, EGTyler_200_PT_Rebin, IsoEGTyler_140_PT_Rebin, IsoEGTyler_200_PT_Rebin, "|eta| < 2.4", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGTyler_140_PTEta10_Rebin, EGTyler_200_PTEta10_Rebin, IsoEGTyler_140_PTEta10_Rebin, IsoEGTyler_200_PTEta10_Rebin, "|eta| < 1.0", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGTyler_140_PTEtaLarge_Rebin, EGTyler_200_PTEtaLarge_Rebin, IsoEGTyler_140_PTEtaLarge_Rebin, IsoEGTyler_200_PTEtaLarge_Rebin, "|eta| > 1.0", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGTyler_140_Eta, EGTyler_200_Eta, IsoEGTyler_140_Eta, IsoEGTyler_200_Eta, "PT > 0", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGTyler_140_EtaPT20, EGTyler_200_EtaPT20, IsoEGTyler_140_EtaPT20, IsoEGTyler_200_EtaPT20, "PT > 20", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGTyler_140_EtaPT25, EGTyler_200_EtaPT25, IsoEGTyler_140_EtaPT25, IsoEGTyler_200_EtaPT25, "PT > 25", "EG (Tyler)", "IsoEG (Tyler)");
   
   AddFourPlots(PdfFile, EG_140_PT_Rebin, EG_200_PT_Rebin, EGTyler_140_PT_Rebin, EGTyler_200_PT_Rebin, "|eta| < 2.4", "EG", "EG (Tyler)");
   AddFourPlots(PdfFile, EG_140_PTEta10_Rebin, EG_200_PTEta10_Rebin, EGTyler_140_PTEta10_Rebin, EGTyler_200_PTEta10_Rebin, "|eta| < 1.0", "EG", "EG (Tyler)");
   AddFourPlots(PdfFile, EG_140_PTEtaLarge_Rebin, EG_200_PTEtaLarge_Rebin, EGTyler_140_PTEtaLarge_Rebin, EGTyler_200_PTEtaLarge_Rebin, "|eta| > 1.0", "EG", "EG (Tyler)");
   AddFourPlots(PdfFile, EG_140_EtaPT20, EG_200_EtaPT20, EGTyler_140_EtaPT20, EGTyler_200_EtaPT20, "PT > 20", "EG", "EG (Tyler)");
   AddFourPlots(PdfFile, EG_140_EtaPT25, EG_200_EtaPT25, EGTyler_140_EtaPT25, EGTyler_200_EtaPT25, "PT > 25", "EG", "EG (Tyler)");
   
   /*
   AddTwoPlots(PdfFile, Jet_140_PT_Rebin, Jet_200_PT_Rebin, "No |eta| cut", "Jet");
   AddTwoPlots(PdfFile, Jet_140_PTEta10_Rebin, Jet_200_PTEta10_Rebin, "|eta| < 1.0", "Jet");
   AddTwoPlots(PdfFile, Jet_140_PTEtaLarge_Rebin, Jet_200_PTEtaLarge_Rebin, "|eta| > 1.0", "Jet");
   AddTwoPlots(PdfFile, Jet_140_Eta, Jet_200_Eta, "PT > 0", "Jet");
   // AddTwoPlots(PdfFile, Jet_140_EtaPT20, Jet_200_EtaPT20, "PT > 20", "Jet");
   // AddTwoPlots(PdfFile, Jet_140_EtaPT25, Jet_200_EtaPT25, "PT > 25", "Jet");
   AddTwoPlots(PdfFile, Jet_140_EtaPT200, Jet_200_EtaPT200, "PT > 200", "Jet");
   */

   AddTwoPlots(PdfFile, TkJet_140_PT_Rebin, TkJet_200_PT_Rebin, "No |eta| cut", "TkJet");
   AddTwoPlots(PdfFile, TkJet_140_PTEta10_Rebin, TkJet_200_PTEta10_Rebin, "|eta| < 1.0", "TkJet");
   AddTwoPlots(PdfFile, TkJet_140_PTEtaLarge_Rebin, TkJet_200_PTEtaLarge_Rebin, "|eta| > 1.0", "TkJet");
   AddTwoPlots(PdfFile, TkJet_140_Eta, TkJet_200_Eta, "PT > 0", "TkJet");
   AddTwoPlots(PdfFile, TkJet_140_EtaPT200, TkJet_200_EtaPT200, "PT > 200", "TkJet");
   
   AddTwoPlots(PdfFile, TkJetGen_140_PT_Rebin, TkJetGen_200_PT_Rebin, "No |eta| cut", "TkJet (GenJet)");
   AddTwoPlots(PdfFile, TkJetGen_140_PTEta10_Rebin, TkJetGen_200_PTEta10_Rebin, "|eta| < 1.0", "TkJet (GenJet)");
   AddTwoPlots(PdfFile, TkJetGen_140_PTEtaLarge_Rebin, TkJetGen_200_PTEtaLarge_Rebin, "|eta| > 1.0", "TkJet (GenJet)");
   AddTwoPlots(PdfFile, TkJetGen_140_Eta, TkJetGen_200_Eta, "PT > 0", "TkJet (GenJet)");
   AddTwoPlots(PdfFile, TkJetGen_140_EtaPT200, TkJetGen_200_EtaPT200, "PT > 200", "TkJet (GenJet)");
   
   PdfFile2.AddTimeStampPage();
   PdfFile2.Close();

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
   delete TkEGTyler_140_PT;
   delete TkEGTyler_140_PT_Rebin;
   delete TkEGTyler_140_PTEta10;
   delete TkEGTyler_140_PTEta10_Rebin;
   delete TkEGTyler_140_PTEtaLarge;
   delete TkEGTyler_140_PTEtaLarge_Rebin;
   delete TkEGTyler_140_Eta;
   delete TkEGTyler_140_EtaPT20;
   delete TkEGTyler_140_EtaPT25;
   delete TkEGTyler_200_PT;
   delete TkEGTyler_200_PT_Rebin;
   delete TkEGTyler_200_PTEta10;
   delete TkEGTyler_200_PTEta10_Rebin;
   delete TkEGTyler_200_PTEtaLarge;
   delete TkEGTyler_200_PTEtaLarge_Rebin;
   delete TkEGTyler_200_Eta;
   delete TkEGTyler_200_EtaPT20;
   delete TkEGTyler_200_EtaPT25;
   delete TkIsoEGTyler_140_PT;
   delete TkIsoEGTyler_140_PT_Rebin;
   delete TkIsoEGTyler_140_PTEta10;
   delete TkIsoEGTyler_140_PTEta10_Rebin;
   delete TkIsoEGTyler_140_PTEtaLarge;
   delete TkIsoEGTyler_140_PTEtaLarge_Rebin;
   delete TkIsoEGTyler_140_Eta;
   delete TkIsoEGTyler_140_EtaPT20;
   delete TkIsoEGTyler_140_EtaPT25;
   delete TkIsoEGTyler_200_PT;
   delete TkIsoEGTyler_200_PT_Rebin;
   delete TkIsoEGTyler_200_PTEta10;
   delete TkIsoEGTyler_200_PTEta10_Rebin;
   delete TkIsoEGTyler_200_PTEtaLarge;
   delete TkIsoEGTyler_200_PTEtaLarge_Rebin;
   delete TkIsoEGTyler_200_Eta;
   delete TkIsoEGTyler_200_EtaPT20;
   delete TkIsoEGTyler_200_EtaPT25;
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
   delete TkEMEG_140_PT;
   delete TkEMEG_140_PT_Rebin;
   delete TkEMEG_140_PTEta10;
   delete TkEMEG_140_PTEta10_Rebin;
   delete TkEMEG_140_PTEtaLarge;
   delete TkEMEG_140_PTEtaLarge_Rebin;
   delete TkEMEG_140_Eta;
   delete TkEMEG_140_EtaPT20;
   delete TkEMEG_140_EtaPT25;
   delete TkEMEG_200_PT;
   delete TkEMEG_200_PT_Rebin;
   delete TkEMEG_200_PTEta10;
   delete TkEMEG_200_PTEta10_Rebin;
   delete TkEMEG_200_PTEtaLarge;
   delete TkEMEG_200_PTEtaLarge_Rebin;
   delete TkEMEG_200_Eta;
   delete TkEMEG_200_EtaPT20;
   delete TkEMEG_200_EtaPT25;
   delete EG_140_PT;
   delete EG_140_PT_Rebin;
   delete EG_140_PTEta10;
   delete EG_140_PTEta10_Rebin;
   delete EG_140_PTEtaLarge;
   delete EG_140_PTEtaLarge_Rebin;
   delete EG_140_Eta;
   delete EG_140_EtaPT20;
   delete EG_140_EtaPT25;
   delete EG_200_PT;
   delete EG_200_PT_Rebin;
   delete EG_200_PTEta10;
   delete EG_200_PTEta10_Rebin;
   delete EG_200_PTEtaLarge;
   delete EG_200_PTEtaLarge_Rebin;
   delete EG_200_Eta;
   delete EG_200_EtaPT20;
   delete EG_200_EtaPT25;
   delete IsoEG_140_PT;
   delete IsoEG_140_PT_Rebin;
   delete IsoEG_140_PTEta10;
   delete IsoEG_140_PTEta10_Rebin;
   delete IsoEG_140_PTEtaLarge;
   delete IsoEG_140_PTEtaLarge_Rebin;
   delete IsoEG_140_Eta;
   delete IsoEG_140_EtaPT20;
   delete IsoEG_140_EtaPT25;
   delete IsoEG_200_PT;
   delete IsoEG_200_PT_Rebin;
   delete IsoEG_200_PTEta10;
   delete IsoEG_200_PTEta10_Rebin;
   delete IsoEG_200_PTEtaLarge;
   delete IsoEG_200_PTEtaLarge_Rebin;
   delete IsoEG_200_Eta;
   delete IsoEG_200_EtaPT20;
   delete IsoEG_200_EtaPT25;
   delete EGTyler_140_PT;
   delete EGTyler_140_PT_Rebin;
   delete EGTyler_140_PTEta10;
   delete EGTyler_140_PTEta10_Rebin;
   delete EGTyler_140_PTEtaLarge;
   delete EGTyler_140_PTEtaLarge_Rebin;
   delete EGTyler_140_Eta;
   delete EGTyler_140_EtaPT20;
   delete EGTyler_140_EtaPT25;
   delete EGTyler_200_PT;
   delete EGTyler_200_PT_Rebin;
   delete EGTyler_200_PTEta10;
   delete EGTyler_200_PTEta10_Rebin;
   delete EGTyler_200_PTEtaLarge;
   delete EGTyler_200_PTEtaLarge_Rebin;
   delete EGTyler_200_Eta;
   delete EGTyler_200_EtaPT20;
   delete EGTyler_200_EtaPT25;
   delete IsoEGTyler_140_PT;
   delete IsoEGTyler_140_PT_Rebin;
   delete IsoEGTyler_140_PTEta10;
   delete IsoEGTyler_140_PTEta10_Rebin;
   delete IsoEGTyler_140_PTEtaLarge;
   delete IsoEGTyler_140_PTEtaLarge_Rebin;
   delete IsoEGTyler_140_Eta;
   delete IsoEGTyler_140_EtaPT20;
   delete IsoEGTyler_140_EtaPT25;
   delete IsoEGTyler_200_PT;
   delete IsoEGTyler_200_PT_Rebin;
   delete IsoEGTyler_200_PTEta10;
   delete IsoEGTyler_200_PTEta10_Rebin;
   delete IsoEGTyler_200_PTEtaLarge;
   delete IsoEGTyler_200_PTEtaLarge_Rebin;
   delete IsoEGTyler_200_Eta;
   delete IsoEGTyler_200_EtaPT20;
   delete IsoEGTyler_200_EtaPT25;
   delete Jet_140_PT;
   delete Jet_140_PT_Rebin;
   delete Jet_140_PTEta10;
   delete Jet_140_PTEta10_Rebin;
   delete Jet_140_PTEtaLarge;
   delete Jet_140_PTEtaLarge_Rebin;
   delete Jet_140_Eta;
   delete Jet_140_EtaPT20;
   delete Jet_140_EtaPT25;
   delete Jet_140_EtaPT200;
   delete Jet_200_PT;
   delete Jet_200_PT_Rebin;
   delete Jet_200_PTEta10;
   delete Jet_200_PTEta10_Rebin;
   delete Jet_200_PTEtaLarge;
   delete Jet_200_PTEtaLarge_Rebin;
   delete Jet_200_Eta;
   delete Jet_200_EtaPT20;
   delete Jet_200_EtaPT25;
   delete Jet_200_EtaPT200;
   delete TkJet_140_PT;
   delete TkJet_140_PT_Rebin;
   delete TkJet_140_PTEta10;
   delete TkJet_140_PTEta10_Rebin;
   delete TkJet_140_PTEtaLarge;
   delete TkJet_140_PTEtaLarge_Rebin;
   delete TkJet_140_Eta;
   delete TkJet_140_EtaPT20;
   delete TkJet_140_EtaPT25;
   delete TkJet_140_EtaPT200;
   delete TkJet_200_PT;
   delete TkJet_200_PT_Rebin;
   delete TkJet_200_PTEta10;
   delete TkJet_200_PTEta10_Rebin;
   delete TkJet_200_PTEtaLarge;
   delete TkJet_200_PTEtaLarge_Rebin;
   delete TkJet_200_Eta;
   delete TkJet_200_EtaPT20;
   delete TkJet_200_EtaPT25;
   delete TkJet_200_EtaPT200;
   delete JetGen_140_PT;
   delete JetGen_140_PT_Rebin;
   delete JetGen_140_PTEta10;
   delete JetGen_140_PTEta10_Rebin;
   delete JetGen_140_PTEtaLarge;
   delete JetGen_140_PTEtaLarge_Rebin;
   delete JetGen_140_Eta;
   delete JetGen_140_EtaPT20;
   delete JetGen_140_EtaPT25;
   delete JetGen_140_EtaPT200;
   delete JetGen_200_PT;
   delete JetGen_200_PT_Rebin;
   delete JetGen_200_PTEta10;
   delete JetGen_200_PTEta10_Rebin;
   delete JetGen_200_PTEtaLarge;
   delete JetGen_200_PTEtaLarge_Rebin;
   delete JetGen_200_Eta;
   delete JetGen_200_EtaPT20;
   delete JetGen_200_EtaPT25;
   delete JetGen_200_EtaPT200;
   delete TkJetGen_140_PT;
   delete TkJetGen_140_PT_Rebin;
   delete TkJetGen_140_PTEta10;
   delete TkJetGen_140_PTEta10_Rebin;
   delete TkJetGen_140_PTEtaLarge;
   delete TkJetGen_140_PTEtaLarge_Rebin;
   delete TkJetGen_140_Eta;
   delete TkJetGen_140_EtaPT20;
   delete TkJetGen_140_EtaPT25;
   delete TkJetGen_140_EtaPT200;
   delete TkJetGen_200_PT;
   delete TkJetGen_200_PT_Rebin;
   delete TkJetGen_200_PTEta10;
   delete TkJetGen_200_PTEta10_Rebin;
   delete TkJetGen_200_PTEtaLarge;
   delete TkJetGen_200_PTEtaLarge_Rebin;
   delete TkJetGen_200_Eta;
   delete TkJetGen_200_EtaPT20;
   delete TkJetGen_200_EtaPT25;
   delete TkJetGen_200_EtaPT200;

   FHgg200.Close();
   FHgg140.Close();
   FWENu200.Close();
   FWENu140.Close();
   FTT200.Close();
   FTT140.Close();

   return 0;
}

TGraphAsymmErrors *Divide(TFile &F1, string N1, TFile &F2, string N2, int Rebin)
{
   static PdfFileHelper Meow("Meow.pdf");
   Meow.AddTextPage("Divide " + N1 + " " + N2);

   cout << "Dividing " << N1 << " by " << N2 << endl;

   TGraphAsymmErrors *Result = NULL;

   TH1D *H1 = (TH1D *)F1.Get(N1.c_str());
   TH1D *H2 = (TH1D *)F2.Get(N2.c_str());

   cout << H1 << " " << H2 << endl;

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
      double Binning1[24] =
         {4, 6, 8, 10, 12, 14, 16, 18,
         20, 22, 24, 26, 28, 30, 34, 38, 42, 46,
         50, 60, 70, 90, 110, 150};
      double Binning2[24] =
         {14, 24, 32, 40, 48, 56, 64, 72,
         80, 88, 96, 104, 112, 120, 136, 152, 168, 184,
         200, 240, 280, 360, 440, 600};

      double Binning[24];

      if(Rebin == -2)
         for(int i = 0; i < 24; i++)
            Binning[i] = Binning2[i];
      else
         for(int i = 0; i < 24; i++)
            Binning[i] = Binning1[i];

      H1Temp = new TH1D("H1Temp", "", 23, Binning);
      H2Temp = new TH1D("H2Temp", "", 23, Binning);

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

      H1Temp->SetBinContent(0, 0);
      H1Temp->SetBinContent(H1Temp->GetNbinsX() + 1, 0);
      H2Temp->SetBinContent(0, 0);
      H2Temp->SetBinContent(H1Temp->GetNbinsX() + 1, 0);
   }

   Result = new TGraphAsymmErrors;
   Result->Divide(H1Temp, H2Temp);

   TCanvas C;
   H2Temp->SetLineColor(kRed);
   H2Temp->Draw("hist");
   H1Temp->Draw("hist same");
   C.SetLogy();
   Meow.AddCanvas(C);

   Meow.AddPlot(Result, "ap");

   if(H1Temp != NULL)
      delete H1Temp;
   if(H2Temp != NULL)
      delete H2Temp;

   cout << Result << endl;

   return Result;
}

void AddFourPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEG140, TGraphAsymmErrors *TkEG200,
   TGraphAsymmErrors *TkIsoEG140, TGraphAsymmErrors *TkIsoEG200, string Title, string Tag1, string Tag2)
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
   Legend.AddEntry(TkEG140,    Form("%s, PU140", Tag1.c_str()), "pl");
   Legend.AddEntry(TkEG200,    Form("%s, PU200", Tag1.c_str()), "pl");
   Legend.AddEntry(TkIsoEG140, Form("%s, PU140", Tag2.c_str()), "pl");
   Legend.AddEntry(TkIsoEG200, Form("%s, PU200", Tag2.c_str()), "pl");
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

void AddTwoPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEM140, TGraphAsymmErrors *TkEM200, string Title, string Tag)
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
   Legend.AddEntry(TkEM140, Form("%s, PU140", Tag.c_str()), "pl");
   Legend.AddEntry(TkEM200, Form("%s, PU200", Tag.c_str()), "pl");
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


