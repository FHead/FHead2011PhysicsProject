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
#include "CommandLine.h"

#include "Graphs.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   string OutputFileNameFull = CL.Get("outputfull");

   SetThesisStyle();

   TFile File(InputFileName.c_str());

   Graphs EG(File, "EG/EG", File, "EG/EGNoMatching", "EG", "Test Sample");
   Graphs TkEG(File, "TkEG/TkEG", File, "TkEG/TkEGNoMatching", "TkEG", "Test Sample");
   Graphs TkEM(File, "TkEM/TkEM", File, "TkEM/TkEMNoMatching", "TkEM", "Test Sample");
   Graphs EGCrystal(File, "EGCrystal/EGCrystal", File, "EGCrystal/EGCrystalNoMatching", "EGCrystal", "Test Sample");
   Graphs TkEGCrystal(File, "TkEGCrystal/TkEGCrystal", File, "TkEGCrystal/TkEGCrystalNoMatching", "TkEGCrystal", "Test Sample");
   Graphs TkEMCrystal(File, "TkEMCrystal/TkEMCrystal", File, "TkEMCrystal/TkEMCrystalNoMatching", "TkEMCrystal", "Test Sample");
   Graphs Jet(File, "Jet/Jet", File, "Jet/JetNoMatching", "Jet", "Test Sample");
   Graphs TkJet(File, "TkJet/TkJet", File, "TkJet/TkJetNoMatching", "TkJet", "Test Sample");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Efficiency plots");
   
   PdfFileHelper PdfFile2(OutputFileNameFull);
   PdfFile2.AddTextPage("Individual efficiency plots");

   PdfFile.AddTextPage("Gen Spectra");

   AddSpectrum(PdfFile, File,   "EG/EGNoMatching_PT_000000",  "Gen EG");
   AddSpectrum(PdfFile, File,   "EG/EGNoMatching_Eta_000000",  "Gen EG");
   AddSpectrum(PdfFile, File,   "TkEG/TkEGNoMatching_PT_000000",  "Gen TkEG");
   AddSpectrum(PdfFile, File,   "TkEG/TkEGNoMatching_Eta_000000",  "Gen TkEG");
   AddSpectrum(PdfFile, File,   "TkEM/TkEMNoMatching_PT_000000",  "Gen TkEM");
   AddSpectrum(PdfFile, File,   "TkEM/TkEMNoMatching_Eta_000000",  "Gen TkEM");
   AddSpectrum(PdfFile, File,   "EGCrystal/EGCrystalNoMatching_PT_000000",  "Gen EGCrystal");
   AddSpectrum(PdfFile, File,   "EGCrystal/EGCrystalNoMatching_Eta_000000",  "Gen EGCrystal");
   AddSpectrum(PdfFile, File,   "TkEGCrystal/TkEGCrystalNoMatching_PT_000000",  "Gen TkEGCrystal");
   AddSpectrum(PdfFile, File,   "TkEGCrystal/TkEGCrystalNoMatching_Eta_000000",  "Gen TkEGCrystal");
   AddSpectrum(PdfFile, File,   "TkEMCrystal/TkEMCrystalNoMatching_PT_000000",  "Gen TkEMCrystal");
   AddSpectrum(PdfFile, File,   "TkEMCrystal/TkEMCrystalNoMatching_Eta_000000",  "Gen TkEMCrystal");
   AddSpectrum(PdfFile, File,   "TkJet/TkJetNoMatching_PT_000000",  "Gen Jets");
   AddSpectrum(PdfFile, File,   "TkJet/TkJetNoMatching_Eta_000000", "Gen Jets");

   EG.AddIndividualPlots(PdfFile2);
   TkEG.AddIndividualPlots(PdfFile2);
   TkEM.AddIndividualPlots(PdfFile2);
   EGCrystal.AddIndividualPlots(PdfFile2);
   TkEGCrystal.AddIndividualPlots(PdfFile2);
   TkEMCrystal.AddIndividualPlots(PdfFile2);
   Jet.AddIndividualPlots(PdfFile2);
   TkJet.AddIndividualPlots(PdfFile2);
   
   PdfFile2.AddTimeStampPage();
   PdfFile2.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}


