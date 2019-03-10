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

   Graphs Jet(File, "Jet/Jet", File, "Jet/JetNoMatching", "Jet", "TTbar V1b");
   Graphs Muon(File, "Muon/Muon", File, "Muon/MuonNoMatching", "Muon", "TTbar V1b");
   Graphs MuonKF(File, "MuonKF/MuonKF", File, "MuonKF/MuonKFNoMatching", "MuonKF", "TTbar V1b");
   Graphs EG(File, "EG/EG", File, "EG/EGNoMatching", "EG", "TTbar V1b");
   Graphs TkEG(File, "TkEG/TkEG", File, "TkEG/TkEGNoMatching", "TkEG", "TTbar V1b");
   Graphs TkEM(File, "TkEM/TkEM", File, "TkEM/TkEMNoMatching", "TkEM", "TTbar V1b");
   Graphs TkJet(File, "TkJet/TkJet", File, "TkJet/TkJetNoMatching", "TkJet", "TTbar V1b");
   Graphs TkCaloJet(File, "TkCaloJet/TkCaloJet", File, "TkCaloJet/TkCaloJetNoMatching", "TkCaloJet", "TTbar V1b");
   Graphs TkMuon(File, "TkMuon/TkMuon", File, "TkMuon/TkMuonNoMatching", "TkMuon", "TTbar V1b");
   Graphs PuppiJet(File, "PuppiJet/PuppiJet", File, "PuppiJet/PuppiJetNoMatching", "PuppiJet", "TTbar V1b");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Efficiency plots");
   
   PdfFileHelper PdfFile2(OutputFileNameFull);
   PdfFile2.AddTextPage("Individual efficiency plots");

   PdfFile.AddTextPage("Gen Spectra");

   AddSpectrum(PdfFile, File,   "EG/EGNoMatching_PT_000000",  "Gen EG");
   AddSpectrum(PdfFile, File,   "EG/EGNoMatching_Eta_000000",  "Gen EG");
   AddSpectrum(PdfFile, File,   "Jet/JetNoMatching_PT_000000",  "Gen Jet");
   AddSpectrum(PdfFile, File,   "Jet/JetNoMatching_Eta_000000",  "Gen Jet");
   AddSpectrum(PdfFile, File,   "Muon/MuonNoMatching_PT_000000",  "Gen Muon");
   AddSpectrum(PdfFile, File,   "Muon/MuonNoMatching_Eta_000000",  "Gen Muon");
   AddSpectrum(PdfFile, File,   "TkEM/TkEMNoMatching_PT_000000",  "Gen Photon");
   AddSpectrum(PdfFile, File,   "TkEM/TkEMNoMatching_Eta_000000",  "Gen Photon");
   AddSpectrum(PdfFile, File,   "EG/EGNoMatching_PT_000000",  "Gen EG");
   AddSpectrum(PdfFile, File,   "EG/EGNoMatching_Eta_000000",  "Gen EG");

   Jet.AddIndividualPlots(PdfFile2);
   Muon.AddIndividualPlots(PdfFile2);
   MuonKF.AddIndividualPlots(PdfFile2);
   EG.AddIndividualPlots(PdfFile2);
   TkEG.AddIndividualPlots(PdfFile2);
   TkEM.AddIndividualPlots(PdfFile2);
   TkJet.AddIndividualPlots(PdfFile2);
   TkCaloJet.AddIndividualPlots(PdfFile2);
   TkMuon.AddIndividualPlots(PdfFile2);
   PuppiJet.AddIndividualPlots(PdfFile2);
   
   PdfFile2.AddTimeStampPage();
   PdfFile2.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}


