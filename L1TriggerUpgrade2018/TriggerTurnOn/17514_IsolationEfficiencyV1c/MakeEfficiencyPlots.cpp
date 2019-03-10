#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

#include "CommandLine.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output", "Meow.pdf");

   TFile File(InputFileName.c_str());

   PdfFileHelper PdfFile(OutputFileName);

   PdfFile.AddTextPage("Gen-isolation check");
   PdfFile.AddPlot((TH1D *)File.Get("GenElectron/GenElectron_PT_000000"),                 "", false);
   PdfFile.AddPlot((TH1D *)File.Get("GenElectron/GenElectron_Eta_000000"),                "", false);
   PdfFile.AddPlot((TH1D *)File.Get("GenElectron/GenElectron_TkIso_000000"),              "", true);
   PdfFile.AddPlot((TH1D *)File.Get("GenElectron/GenElectron_ResponsePT10_000000"),       "", false);
   PdfFile.AddPlot((TH1D *)File.Get("GenPhoton/GenPhoton_PT_000000"),                     "", false);
   PdfFile.AddPlot((TH1D *)File.Get("GenPhoton/GenPhoton_Eta_000000"),                    "", false);
   PdfFile.AddPlot((TH1D *)File.Get("GenPhoton/GenPhoton_TkIso_000000"),                  "", true);
   PdfFile.AddPlot((TH1D *)File.Get("GenPhoton/GenPhoton_ResponsePT10_000000"),           "", false);
   PdfFile.AddPlot((TH1D *)File.Get("IsoGenElectron/IsoGenElectron_PT_000000"),           "", false);
   PdfFile.AddPlot((TH1D *)File.Get("IsoGenElectron/IsoGenElectron_Eta_000000"),          "", false);
   PdfFile.AddPlot((TH1D *)File.Get("IsoGenElectron/IsoGenElectron_TkIso_000000"),        "", true);
   PdfFile.AddPlot((TH1D *)File.Get("IsoGenElectron/IsoGenElectron_ResponsePT10_000000"), "", false);
   PdfFile.AddPlot((TH1D *)File.Get("IsoGenPhoton/IsoGenPhoton_PT_000000"),               "", false);
   PdfFile.AddPlot((TH1D *)File.Get("IsoGenPhoton/IsoGenPhoton_Eta_000000"),              "", false);
   PdfFile.AddPlot((TH1D *)File.Get("IsoGenPhoton/IsoGenPhoton_TkIso_000000"),            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("IsoGenPhoton/IsoGenPhoton_ResponsePT10_000000"),     "", false);
   
   PdfFile.AddTextPage("Tk object isolation check");
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_PT_000000"),                               "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_Eta_000000"),                              "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_TkIso_000000"),                            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_TkIsoPT10_000000"),                        "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_TkIsoPT20_000000"),                        "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_TkIsoPT30_000000"),                        "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_TkIsoPT40_000000"),                        "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_ResponsePT10_000000"),                     "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_ResponsePT10Eta15_000000"),                "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEG/TkEG_ResponsePT10EtaLarge_000000"),             "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_PT_000000"),                               "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_Eta_000000"),                              "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_TkIso_000000"),                            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_TkIsoPT10_000000"),                        "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_TkIsoPT20_000000"),                        "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_TkIsoPT30_000000"),                        "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_TkIsoPT40_000000"),                        "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_ResponsePT10_000000"),                     "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_ResponsePT10Eta15_000000"),                "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEM/TkEM_ResponsePT10EtaLarge_000000"),             "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_PT_000000"),                         "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_Eta_000000"),                        "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_TkIso_000000"),                      "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_TkIsoPT10_000000"),                  "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_TkIsoPT20_000000"),                  "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_TkIsoPT30_000000"),                  "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_TkIsoPT40_000000"),                  "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_ResponsePT10_000000"),               "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_ResponsePT10Eta15_000000"),          "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEGIso/TkEGIso_ResponsePT10EtaLarge_000000"),       "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_PT_000000"),                         "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_Eta_000000"),                        "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_TkIso_000000"),                      "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_TkIsoPT10_000000"),                  "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_TkIsoPT20_000000"),                  "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_TkIsoPT30_000000"),                  "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_TkIsoPT40_000000"),                  "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_ResponsePT10_000000"),               "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_ResponsePT10Eta15_000000"),          "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkEMIso/TkEMIso_ResponsePT10EtaLarge_000000"),       "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_PT_000000"),                   "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_Eta_000000"),                  "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_TkIso_000000"),                "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_TkIsoPT10_000000"),            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_TkIsoPT20_000000"),            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_TkIsoPT30_000000"),            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_TkIsoPT40_000000"),            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_ResponsePT10_000000"),         "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_ResponsePT10Eta15_000000"),    "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEGIso/TkIsoEGIso_ResponsePT10EtaLarge_000000"), "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_PT_000000"),                   "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_Eta_000000"),                  "", false);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_TkIso_000000"),                "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_TkIsoPT10_000000"),            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_TkIsoPT20_000000"),            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_TkIsoPT30_000000"),            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_TkIsoPT40_000000"),            "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_ResponsePT10_000000"),         "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_ResponsePT10Eta15_000000"),    "", true);
   PdfFile.AddPlot((TH1D *)File.Get("TkIsoEMIso/TkIsoEMIso_ResponsePT10EtaLarge_000000"), "", true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}




