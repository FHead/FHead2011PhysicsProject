#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void ComparisonPlots(PdfFileHelper &PdfFile, TFile &F1, string N1, TFile &F2, string N2,
   string Title, string L1, string L2);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("RatePlots.pdf");
   PdfFile.AddTextPage("Rate plots");

   // TFile FileTrk("L1Menu_trk_Nu200.root");
   TFile FileTrk("L1Menu_trkL1TDREta_v3p4_Nu200.root");
   TFile FileStd("L1Menu_std_Nu200.root");

   ComparisonPlots(PdfFile, FileTrk, "L1_SingleTkJet_v_threshold1", FileStd, "L1_SingleJetC_v_threshold1",
      "Single Jet", "Track", "Standard");
   ComparisonPlots(PdfFile, FileTrk, "L1_DoubleTkJetVtx_v_allThresholdsScaled", FileStd, "L1_DoubleJet_v_allThresholdsScaled",
      "Double Jet (all)", "Track", "Standard");
   ComparisonPlots(PdfFile, FileTrk, "L1_DoubleTkJetVtx_v_threshold1", FileStd, "L1_DoubleJet_v_threshold1",
      "Double Jet (J1)", "Track", "Standard");
   ComparisonPlots(PdfFile, FileTrk, "L1_DoubleTkJetVtx_v_threshold2", FileStd, "L1_DoubleJet_v_threshold2",
      "Double Jet (J2)", "Track", "Standard");
   ComparisonPlots(PdfFile, FileTrk, "L1_QuadTkJetVtx_v_allThresholdsScaled", FileStd, "L1_QuadJetC_v_allThresholdsScaled",
      "Quad Jet (all)", "Track", "Standard");
   ComparisonPlots(PdfFile, FileTrk, "L1_QuadTkJetVtx_v_threshold1", FileStd, "L1_QuadJetC_v_threshold1",
      "Quad Jet (J1)", "Track", "Standard");
   ComparisonPlots(PdfFile, FileTrk, "L1_QuadTkJetVtx_v_threshold2", FileStd, "L1_QuadJetC_v_threshold2",
      "Quad Jet (J2)", "Track", "Standard");
   ComparisonPlots(PdfFile, FileTrk, "L1_QuadTkJetVtx_v_threshold3", FileStd, "L1_QuadJetC_v_threshold3",
      "Quad Jet (J3)", "Track", "Standard");
   ComparisonPlots(PdfFile, FileTrk, "L1_QuadTkJetVtx_v_threshold4", FileStd, "L1_QuadJetC_v_threshold4",
      "Quad Jet (J4)", "Track", "Standard");

   FileStd.Close();
   FileTrk.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void ComparisonPlots(PdfFileHelper &PdfFile, TFile &F1, string N1, TFile &F2, string N2,
   string Title, string L1, string L2)
{
   TH1F *H1 = (TH1F *)F1.Get(N1.c_str());
   TH1F *H2 = (TH1F *)F2.Get(N2.c_str());

   if(H1 == NULL || H2 == NULL)
      return;

   H1->SetLineWidth(2);
   
   H1->SetLineColor(kBlack);
   H2->SetLineColor(kRed);
   
   H1->SetMarkerColor(kBlack);
   H2->SetMarkerColor(kRed);

   TH2D HWorld("HWorld", ";Threshold;Rate (kHz)", 100, 0, 200, 100, 1, 100000);
   HWorld.SetStats(0);

   HWorld.SetTitle(Title.c_str());

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(H1, L1.c_str(), "lp");
   Legend.AddEntry(H2, L2.c_str(), "lp");

   TCanvas C;

   HWorld.Draw("axis");
   H1->Draw("same");
   H2->Draw("same");
   Legend.Draw();

   C.SetLogy();

   PdfFile.AddCanvas(C);
}











