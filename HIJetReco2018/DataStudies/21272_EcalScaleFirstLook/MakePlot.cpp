#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"

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
   PdfFile.AddTextPage(OutputFileName);

   TFile File(InputFileName.c_str());

   PdfFile.AddPlot((TH1D *)File.Get("HPTHat"));
   
   PdfFile.AddPlot((TH1D *)File.Get("HRefPT"));
   PdfFile.AddPlot((TH1D *)File.Get("HRefPT_EtaN25N15"));
   PdfFile.AddPlot((TH1D *)File.Get("HRefPT_EtaN15N00"));
   PdfFile.AddPlot((TH1D *)File.Get("HRefPT_EtaP00P15"));
   PdfFile.AddPlot((TH1D *)File.Get("HRefPT_EtaP15P25"));
   
   PdfFile.AddPlot((TH2D *)File.Get("HRefEtaPhi"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRefEtaPhi_PT30"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRefEtaPhi_PT50"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRefEtaPhi_PT75"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRefEtaPhi_PT100"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRefEtaPhi_PT125"), "colz");
   
   PdfFile.AddPlot((TH1D *)File.Get("HJetPT"));
   PdfFile.AddPlot((TH1D *)File.Get("HJetPT_EtaN25N15"));
   PdfFile.AddPlot((TH1D *)File.Get("HJetPT_EtaN15N00"));
   PdfFile.AddPlot((TH1D *)File.Get("HJetPT_EtaP00P15"));
   PdfFile.AddPlot((TH1D *)File.Get("HJetPT_EtaP15P25"));
   
   PdfFile.AddPlot((TH2D *)File.Get("HJetEtaPhi"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HJetEtaPhi_PT30"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HJetEtaPhi_PT50"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HJetEtaPhi_PT75"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HJetEtaPhi_PT100"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HJetEtaPhi_PT125"), "colz");

   PdfFile.AddPlot((TH2D *)File.Get("HRVsEta_PT30_PT50"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRVsEta_PT50_PT75"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRVsEta_PT75_PT100"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRVsEta_PT100_PT125"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRVsPT_EtaN25N15"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRVsPT_EtaN15N00"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRVsPT_EtaP00P15"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HRVsPT_EtaP15P25"), "colz");

   PdfFile.AddPlot((TH2D *)File.Get("HEtaVsFractionInEndcap"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HEtaVsFractionInEndcapZoomed"), "colz");

   PdfFile.AddPlot((TH2D *)File.Get("HJetPTVsJetCPT"), "colz");

   PdfFile.AddPlot((TH2D *)File.Get("HCRVsEta_PT30_PT50"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HCRVsEta_PT50_PT75"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HCRVsEta_PT75_PT100"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HCRVsEta_PT100_PT125"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HCRVsPT_EtaN25N15"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HCRVsPT_EtaN15N00"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HCRVsPT_EtaP00P15"), "colz");
   PdfFile.AddPlot((TH2D *)File.Get("HCRVsPT_EtaP15P25"), "colz");
   
   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}





