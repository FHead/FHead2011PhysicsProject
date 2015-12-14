#include <string>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main();
void ExportPlot(TFile &F, string Name, string Tag);

int main()
{
   SetStyle();

   TFile F("Matrices.root");

   ExportPlot(F, "HMRStarRStar_LQ200", "LQ200");
   ExportPlot(F, "HMRStarRStar_LQ250", "LQ250");
   ExportPlot(F, "HMRStarRStar_LQ340", "LQ340");
   ExportPlot(F, "HMRStarRStar_LQ450", "LQ450");
   ExportPlot(F, "HMRStarRStar_LQ550", "LQ550");
   ExportPlot(F, "HMRStarRStar_TTbar", "TTbar");
   ExportPlot(F, "HMRStarRStar_W", "W");
   ExportPlot(F, "HMRStarRStar_GammaVJet", "GammaVJet");
   ExportPlot(F, "HMRStarRStar_DY_50", "DY50");
   ExportPlot(F, "HMRStarRStar_Znunu", "Znunu");
   ExportPlot(F, "HMRStarRStar_VV", "VV");

   TH2D *H1 = (TH2D *)F.Get("HMRStarRStar_QCD50");
   TH2D *H2 = (TH2D *)F.Get("HMRStarRStar_QCD100");
   TH2D *H3 = (TH2D *)F.Get("HMRStarRStar_QCD250");
   TH2D *H4 = (TH2D *)F.Get("HMRStarRStar_QCD500");
   TH2D *H5 = (TH2D *)F.Get("HMRStarRStar_QCD1000");

   H1->Add(H2);
   H1->Add(H3);
   H1->Add(H4);
   H1->Add(H5);

   H1->SetStats(0);
   H1->SetTitle("MR vs. R^{2} (QCD)");
   H1->GetXaxis()->SetTitle(TString(H1->GetXaxis()->GetTitle()).ReplaceAll(" (new)", "").ReplaceAll(" R,", " R^{2},"));
   H1->GetYaxis()->SetTitle(TString(H1->GetYaxis()->GetTitle()).ReplaceAll(" (new)", "").ReplaceAll(" R,", " R^{2},"));

   TCanvas C("C", "C", 1024, 1024);
   H1->Draw("colz");

   C.SaveAs("QCD.png");
   C.SaveAs("QCD.C");
   C.SaveAs("QCD.eps");
   C.SaveAs("QCD.pdf");

   return 0;
}

void ExportPlot(TFile &F, string Name, string Tag)
{
   TH2D *H = (TH2D *)F.Get(Name.c_str());

   TCanvas C("C", "C", 1024, 1024);

   H->SetStats(0);
   H->SetTitle(TString(H->GetTitle()).ReplaceAll(" (new)", "").ReplaceAll(" R,", " R^{2},"));
   H->GetXaxis()->SetTitle(TString(H->GetXaxis()->GetTitle()).ReplaceAll(" (new)", "").ReplaceAll(" R,", " R^{2},"));
   H->GetYaxis()->SetTitle(TString(H->GetYaxis()->GetTitle()).ReplaceAll(" (new)", "").ReplaceAll(" R,", " R^{2},"));
   H->Draw("colz");

   C.SaveAs((Tag + ".png").c_str());
   C.SaveAs((Tag + ".C").c_str());
   C.SaveAs((Tag + ".eps").c_str());
   C.SaveAs((Tag + ".pdf").c_str());
}


