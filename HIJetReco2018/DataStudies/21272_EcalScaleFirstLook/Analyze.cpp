#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraphErrors.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "CustomAssert.h"

int main(int argc, char *argv[]);
void AnalyzeMeanResolution(PdfFileHelper &PdfFile, TFile &File, string HistogramName);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("OutputBase");

   PdfFileHelper PdfFile(OutputFileName + ".pdf");
   PdfFile.AddTextPage(OutputFileName + ".pdf");

   TFile File(InputFileName.c_str());
   TFile OutputFile((OutputFileName + ".root").c_str(), "RECREATE");

   AnalyzeMeanResolution(PdfFile, File, "HRVsEta_PT50_PT75");
   AnalyzeMeanResolution(PdfFile, File, "HCRVsEta_PT50_PT75");
   AnalyzeMeanResolution(PdfFile, File, "HRVsAbsEta_PT50_PT75");
   AnalyzeMeanResolution(PdfFile, File, "HCRVsAbsEta_PT50_PT75");
   AnalyzeMeanResolution(PdfFile, File, "HRVsEta_PT75_PT100");
   AnalyzeMeanResolution(PdfFile, File, "HCRVsEta_PT75_PT100");
   AnalyzeMeanResolution(PdfFile, File, "HRVsAbsEta_PT75_PT100");
   AnalyzeMeanResolution(PdfFile, File, "HCRVsAbsEta_PT75_PT100");
   AnalyzeMeanResolution(PdfFile, File, "HRVsEta_PT100_PT125");
   AnalyzeMeanResolution(PdfFile, File, "HCRVsEta_PT100_PT125");
   AnalyzeMeanResolution(PdfFile, File, "HRVsAbsEta_PT100_PT125");
   AnalyzeMeanResolution(PdfFile, File, "HCRVsAbsEta_PT100_PT125");

   OutputFile.Close();
   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AnalyzeMeanResolution(PdfFileHelper &PdfFile, TFile &File, string HistogramName)
{
   PdfFile.AddTextPage(HistogramName);

   TH2D *H = (TH2D *)File.Get(HistogramName.c_str());
   Assert(H != NULL, Form("Histogram \"%s\" not found!", HistogramName.c_str()));
   
   H->Rebin2D(5, 1);

   TGraphErrors GCenter;
   TGraphErrors GResolution;
   TGraphErrors GMean;
   TGraphErrors GRMS;

   GCenter.SetName(("Center_" + HistogramName).c_str());
   GResolution.SetName(("Resolution_" + HistogramName).c_str());
   GMean.SetName(("Mean_" + HistogramName).c_str());
   GRMS.SetName(("RMS_" + HistogramName).c_str());

   int N = H->GetNbinsX();
   for(int i = 1; i <= N; i++)
   {
      double Eta = H->GetXaxis()->GetBinCenter(i);

      TH1D *HProjection = (TH1D *)H->ProjectionY("_py", i, i);

      TF1 F("F", "gaus");

      HProjection->Fit(&F);

      PdfFile.AddPlot(HProjection);

      GCenter.SetPoint(i - 1, Eta, F.GetParameter(1));
      GCenter.SetPointError(i - 1, 0, F.GetParError(1));
      GResolution.SetPoint(i - 1, Eta, F.GetParameter(2));
      GResolution.SetPointError(i - 1, 0, F.GetParError(2));
      GMean.SetPoint(i - 1, Eta, HProjection->GetMean());
      GMean.SetPointError(i - 1, 0, HProjection->GetMeanError());
      GRMS.SetPoint(i - 1, Eta, HProjection->GetRMS());
      GRMS.SetPointError(i - 1, 0, HProjection->GetRMSError());
   }

   PdfFile.AddPlot(GCenter, "ap");
   PdfFile.AddPlot(GResolution, "ap");
   PdfFile.AddPlot(GMean, "ap");
   PdfFile.AddPlot(GRMS, "ap");

   GCenter.Write();
   GResolution.Write();
   GMean.Write();
   GRMS.Write();
}


