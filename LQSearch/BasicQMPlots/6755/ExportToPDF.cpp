#include <string>
using namespace std;

#include "TFile.h"
#include "TROOT.h"
#include "TColor.h"
#include "TStyle.h"

#include "PlotHelper2.h"

int main();
void ExportToPDF(string InputFile, string OutputBase);

int main()
{
   gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   ExportToPDF("LQ450_Output.root", "LQ450");
}

void ExportToPDF(string InputFile, string OutputBase)
{
   TFile F(InputFile.c_str());

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage("Basic plots!!!");

   PsFile.AddTextPage("Basic information and counting histograms");
   PsFile.AddHistogramFromFile(F, "HProcessedEvents", "text00", false);
   PsFile.AddHistogramFromFile(F, "HBunchCrossing", "", false);
   PsFile.AddHistogramFromFile(F, "HGoodPV", "hist text00", false);
   PsFile.AddHistogramFromFile(F, "HCountingHistogramCaloJet", "hist text", true);
   PsFile.AddHistogramFromFile(F, "HCountingHistogramCaloJetTCHEL", "hist text", true);
   PsFile.AddHistogramFromFile(F, "HCountingHistogramCaloJetTCHEL2", "hist text", true);
   PsFile.AddHistogramFromFile(F, "HCountingHistogramCaloJetSSVHEM", "hist text", true);
   PsFile.AddHistogramFromFile(F, "HCountingHistogramCaloJetSSVHEM2", "hist text", true);
   PsFile.AddHistogramFromFile(F, "HCountingHistogramPFJet", "hist text", true);

   PsFile.AddTextPage("Calo-jet plots");
   PsFile.AddHistogramFromFile(F, "HNumberOfGoodCaloJet30", "", true);
   PsFile.AddHistogramFromFile(F, "HNumberOfBadCaloJet30", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJetPT", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloJetEta", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJetPhi", "", false);

   PsFile.AddTextPage("PF-jet plots");
   PsFile.AddHistogramFromFile(F, "HNumberOfGoodPFJet30", "", true);
   PsFile.AddHistogramFromFile(F, "HNumberOfBadPFJet30", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJetPT", "", true);
   PsFile.AddHistogramFromFile(F, "HPFJetEta", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJetPhi", "", false);

   PsFile.AddTextPage("Calo-jet b-tagging plots");
   PsFile.AddHistogramFromFile(F, "HCaloTCHE", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloTCHP", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloSSVHE", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloSSVHP", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloTCHELCount", "hist text", false);
   PsFile.AddHistogramFromFile(F, "HCaloTCHEMCount", "hist text", false);
   PsFile.AddHistogramFromFile(F, "HCaloTCHETCount", "hist text", false);
   PsFile.AddHistogramFromFile(F, "HCaloTCHPLCount", "hist text", false);
   PsFile.AddHistogramFromFile(F, "HCaloTCHPMCount", "hist text", false);
   PsFile.AddHistogramFromFile(F, "HCaloTCHPTCount", "hist text", false);
   PsFile.AddHistogramFromFile(F, "HCaloSSVHEMCount", "hist text", false);
   PsFile.AddHistogramFromFile(F, "HCaloSSVHETCount", "hist text", false);
   PsFile.AddHistogramFromFile(F, "HCaloSSVHPTCount", "hist text", false);

   PsFile.AddTextPage("Calo-jet hemisphere plots");
   PsFile.AddHistogramFromFile(F, "HCaloHemispherePT", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloHemisphereMass", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloHemisphereEta", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloHemispherePhi", "", false);

   PsFile.AddTextPage("Calo-jet MR/R distributions");
   PsFile.AddHistogramFromFile(F, "HCaloMRStar", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarTCHEL", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarTCHEL2", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarSSVHEM", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarSSVHEM2", "", false);
   
   PsFile.AddHistogramFromFile(F, "HCaloRStar", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloRStarTCHEL", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloRStarTCHEL2", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloRStarSSVHEM", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloRStarSSVHEM2", "", false);

   PsFile.AddHistogramFromFile(F, "HCaloMRStarVsRStar", "colz", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarVsRStarWithMETCut", "colz", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarVsRStarWithHigherMETCut", "colz", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarVsRStarTCHEL", "colz", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarVsRStarTCHEL2", "colz", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarVsRStarSSVHEM", "colz", false);
   PsFile.AddHistogramFromFile(F, "HCaloMRStarVsRStarSSVHEM2", "colz", false);

   PsFile.AddHistogramFromFile(F, "HCaloGammaRStar", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloGammaRStarWithMETCut", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloGammaRStarWithHigherMETCut", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloGammaRStarTCHEL", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloGammaRStarTCHEL2", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloGammaRStarSSVHEM", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloGammaRStarSSVHEM2", "", true);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}





