#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLatex.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   vector<string> TriggerList = CL.GetStringVector("Trigger");

   TFile File(InputFileName.c_str());

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Plots: " + InputFileName);

   for(string Trigger : TriggerList)
   {
      PdfFile.AddTextPage(Trigger);
      PdfFile.AddHistogramFromFile(File, "HDR_" + Trigger);
      PdfFile.AddHistogramFromFile(File, "HMatchPT_" + Trigger);
      PdfFile.AddHistogramFromFile(File, "HMatchEta_" + Trigger);
      PdfFile.AddHistogramFromFile(File, "HResolution_" + Trigger);
      PdfFile.AddHistogramFromFile(File, "HResolutionC0_" + Trigger);
      PdfFile.AddHistogramFromFile(File, "HResolutionC1_" + Trigger);
      PdfFile.AddHistogramFromFile(File, "HResolutionC2_" + Trigger);
      PdfFile.AddHistogramFromFile(File, "HResolutionC3_" + Trigger);
      PdfFile.AddHistogramFromFile(File, "HResolutionC4_" + Trigger);
      PdfFile.AddHistogramFromFile(File, "HPTPT_" + Trigger, "colz");
      PdfFile.AddHistogramFromFile(File, "HResolutionEta_" + Trigger, "colz");
      PdfFile.AddHistogramFromFile(File, "HResolutionTrack_" + Trigger, "colz");

      TCanvas Canvas;

      TGraph GLine;
      GLine.SetPoint(0, 2505, 0);
      GLine.SetPoint(1, 2505, 1e6);
      GLine.SetPoint(2, 1028, 1e6);
      GLine.SetPoint(3, 1028, 0);
      GLine.SetPoint(4, 357.5, 0);
      GLine.SetPoint(5, 357.5, 1e6);
      GLine.SetPoint(6, 63.26, 1e6);
      GLine.SetPoint(7, 63.26, 0);

      ((TH2D *)File.Get(("HResolutionLogHF_" + Trigger).c_str()))->Draw("colz");
      Canvas.SetLogx();

      GLine.SetLineStyle(kDashed);
      GLine.Draw("l");

      TGraph GOne;
      GOne.SetPoint(0, -1e6, 1);
      GOne.SetPoint(1, +1e6, 1);
      GOne.Draw("l");

      TLatex Latex;
      Latex.SetTextFont(42);
      Latex.SetTextSize(0.02);
      Latex.SetTextAlign(12);

      Latex.DrawLatex(63.26, 0.08, "  80%");
      Latex.DrawLatex(357.5, 0.08, "  50%");
      Latex.DrawLatex(1028,  0.08, "  30%");
      Latex.DrawLatex(2505,  0.08, "  10%");

      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}





