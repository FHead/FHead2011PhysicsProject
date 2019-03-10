#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper3.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
void AttachIsolationPlot(PdfFileHelper &PdfFile, TFile &F, string HistogramName, double Level);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   bool DoE = CL.GetBool("doe", false);
   bool DoG = CL.GetBool("dog", false);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Isolation plots: " + InputFileName);

   TFile File(InputFileName.c_str());

   if(DoE == true)
   {
      AttachIsolationPlot(PdfFile, File, "GenElectron/GenElectron_TkIso_000000",         -1);
      AttachIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIso_000000",                 0.982);
      AttachIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT10_000000",             0.982);
      AttachIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT20_000000",             0.982);
      AttachIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT30_000000",             0.982);
      AttachIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT40_000000",             0.982);
      AttachIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoEta15_000000",            0.982);
      AttachIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoEtaLarge_000000",         0.982);
      AttachIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT10Eta15_000000",        0.982);
      AttachIsolationPlot(PdfFile, File, "TkEGIso/TkEGIso_TkIsoPT10EtaLarge_000000",     0.982);
   }
   if(DoG == true)
   {
      AttachIsolationPlot(PdfFile, File, "GenPhoton/GenPhoton_TkIso_000000",             -1);
      AttachIsolationPlot(PdfFile, File, "TkEMIso/TkEMIso_TkIso_000000",                 0.946);
      AttachIsolationPlot(PdfFile, File, "TkEMIso/TkEMIso_TkIsoPT10_000000",             0.946);
      AttachIsolationPlot(PdfFile, File, "TkEMIso/TkEMIso_TkIsoPT20_000000",             0.946);
      AttachIsolationPlot(PdfFile, File, "TkEMIso/TkEMIso_TkIsoPT30_000000",             0.946);
      AttachIsolationPlot(PdfFile, File, "TkEMIso/TkEMIso_TkIsoPT40_000000",             0.946);
      AttachIsolationPlot(PdfFile, File, "TkEMIso/TkEMIso_TkIsoEta15_000000",            0.946);
      AttachIsolationPlot(PdfFile, File, "TkEMIso/TkEMIso_TkIsoEtaLarge_000000",         0.946);
      AttachIsolationPlot(PdfFile, File, "TkEMIso/TkEMIso_TkIsoPT10Eta15_000000",        0.946);
      AttachIsolationPlot(PdfFile, File, "TkEMIso/TkEMIso_TkIsoPT10EtaLarge_000000",     0.946);
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AttachIsolationPlot(PdfFileHelper &PdfFile, TFile &F, string HistogramName, double Level)
{
   PdfFile.AddTextPage(HistogramName);

   TH1D *H = (TH1D *)F.Get(HistogramName.c_str());
   if(H == NULL)
      return;

   TH1D *HCumulative = (TH1D *)H->Clone("HCumulative");

   for(int i = 1; i <= HCumulative->GetNbinsX() + 1; i++)
      HCumulative->SetBinContent(i, HCumulative->GetBinContent(i) + HCumulative->GetBinContent(i - 1));
   HCumulative->Scale(1 / HCumulative->GetBinContent(HCumulative->GetNbinsX() + 1));

   H->SetTitle("");
   HCumulative->SetTitle("");

   HCumulative->GetYaxis()->SetTitle("Efficiency");

   H->SetStats(0);
   HCumulative->SetStats(0);

   PdfFile.AddPlot(H, "", false);
   PdfFile.AddPlot(H, "", true);

   TGraph Graph;
   Graph.SetPoint(0, 0, Level);
   Graph.SetPoint(1, 1000, Level);

   TCanvas Canvas;
   HCumulative->Draw();
   Graph.Draw("l");
   PdfFile.AddCanvas(Canvas);
}




