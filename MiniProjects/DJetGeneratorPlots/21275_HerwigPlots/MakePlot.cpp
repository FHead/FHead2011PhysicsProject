#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage(InputFileName);

   TFile File(InputFileName.c_str());

   PdfFile.AddHistogramFromFile(File, "HPTHat", "", true);
   PdfFile.AddHistogramFromFile(File, "HJetCount", "", true);
   PdfFile.AddHistogramFromFile(File, "HJetCountPT30", "", true);
   PdfFile.AddHistogramFromFile(File, "HJetCountPT50", "", true);
   PdfFile.AddHistogramFromFile(File, "HJetCountPT75", "", true);
   PdfFile.AddHistogramFromFile(File, "HJetCountPT100", "", true);
   PdfFile.AddHistogramFromFile(File, "HJetCountPT125", "", true);
   PdfFile.AddHistogramFromFile(File, "HJetPT", "", true);

   {
      TCanvas Canvas;

      TH2D HWorld("HWorld", ";Number of D^{0};", 10, 0, 10, 100, 1e-6, 1000);
      HWorld.SetStats(0);

      TH1D *Ha = (TH1D *)File.Get("HD0aCount");
      TH1D *Hb = (TH1D *)File.Get("HD0bCount");
      TH1D *Hc = (TH1D *)File.Get("HD0cCount");

      Ha->Scale(0.0005);
      Hb->Scale(0.0005);
      Hc->Scale(0.0005);

      Ha->SetLineColor(kBlack);
      Hb->SetLineColor(kGreen);
      Hc->SetLineColor(kRed);
      Ha->SetMarkerColor(kBlack);
      Hb->SetMarkerColor(kGreen);
      Hc->SetMarkerColor(kRed);
      
      HWorld.Draw("axis");
      Ha->Draw("same");
      Hb->Draw("same");
      Hc->Draw("same");

      TLegend Legend(0.4, 0.8, 0.7, 0.6);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(Ha, "No selection", "pl");
      Legend.AddEntry(Hb, "Decay to K#pi", "pl");
      Legend.AddEntry(Hc, "K and #pi acceptance", "pl");
      Legend.Draw();

      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);
   }

   {
      TCanvas Canvas;

      TH2D HWorld("HWorld", ";D^{0} p_{T};", 10, 0, 100, 100, 1e-6, 100);
      HWorld.SetStats(0);

      TH1D *Ha = (TH1D *)File.Get("HD0aPT");
      TH1D *Hb = (TH1D *)File.Get("HD0bPT");
      TH1D *Hc = (TH1D *)File.Get("HD0cPT");

      Ha->Scale(0.0005);
      Hb->Scale(0.0005);
      Hc->Scale(0.0005);

      Ha->SetLineColor(kBlack);
      Hb->SetLineColor(kGreen);
      Hc->SetLineColor(kRed);
      Ha->SetMarkerColor(kBlack);
      Hb->SetMarkerColor(kGreen);
      Hc->SetMarkerColor(kRed);

      HWorld.Draw("axis");
      Ha->Draw("same");
      Hb->Draw("same");
      Hc->Draw("same");

      TLegend Legend(0.4, 0.8, 0.7, 0.6);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(Ha, "No selection", "pl");
      Legend.AddEntry(Hb, "Decay to K#pi", "pl");
      Legend.AddEntry(Hc, "K and #pi acceptance", "pl");
      Legend.Draw();

      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);
   }

   {
      TCanvas Canvas;

      TH2D HWorld("HWorld", ";D^{0} #eta;", 10, -4, 4, 100, 1e-6, 100);
      HWorld.SetStats(0);

      TH1D *Ha = (TH1D *)File.Get("HD0aEta");
      TH1D *Hb = (TH1D *)File.Get("HD0bEta");
      TH1D *Hc = (TH1D *)File.Get("HD0cEta");

      Ha->Scale(0.0005);
      Hb->Scale(0.0005);
      Hc->Scale(0.0005);

      Ha->SetLineColor(kBlack);
      Hb->SetLineColor(kGreen);
      Hc->SetLineColor(kRed);
      Ha->SetMarkerColor(kBlack);
      Hb->SetMarkerColor(kGreen);
      Hc->SetMarkerColor(kRed);

      HWorld.Draw("axis");
      Ha->Draw("same");
      Hb->Draw("same");
      Hc->Draw("same");

      TLegend Legend(0.4, 0.8, 0.7, 0.6);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(Ha, "No selection", "pl");
      Legend.AddEntry(Hb, "Decay to K#pi", "pl");
      Legend.AddEntry(Hc, "K and #pi acceptance", "pl");
      Legend.Draw();

      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);
   }


   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



