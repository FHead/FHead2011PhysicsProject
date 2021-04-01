#include <iostream>
#include <vector>
using namespace std;

#include "TF1.h"
#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveStats.h"

#include "PlotHelper4.h"
#include "DataHelper.h"
#include "SetStyle.h"
#include "CommandLine.h"

#include "HelperFunctions.h"

#define LINEAR 1
#define QUADRATIC 2

int main(int argc, char *argv[]);
void ProcessFile(PdfFileHelper &PdfFile, string FileName, string OutputFileName,
   string Prefix, vector<double> Thresholds,
   double Target, string Tag, string Name = "PT", int Type = TYPE_SMOOTH_SUPERTIGHT,
   int Scaling = LINEAR);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("input");
   string OutputFileName = CL.Get("output");
   string CurvesFileName = CL.Get("curves");
   double Reference      = CL.GetDouble("reference");
   string Prefix         = CL.Get("prefix", "");

   bool DoSTAMuon          = CL.GetBool("DoSTAMuon", false);
   bool DoSTADisplacedMuon = CL.GetBool("DoSTADisplacedMuon", false);
   bool DoTkMuon           = CL.GetBool("DoTkMuon", false);
   bool DoTkMuonStub       = CL.GetBool("DoTkMuonStub", false);
   bool DoTkMuonStubS12    = CL.GetBool("DoTkMuonStubS12", false);
   bool DoEG               = CL.GetBool("DoEG", false);
   bool DoEGExtended       = CL.GetBool("DoEGExtended", false);
   bool DoEGTrack          = CL.GetBool("DoEGTrack", false);
   bool DoElectron         = CL.GetBool("DoElectron", false);
   bool DoZElectron        = CL.GetBool("DoZElectron", false);
   bool DoIsoElectron      = CL.GetBool("DoIsoElectron", false);
   bool DoPhoton           = CL.GetBool("DoPhoton", false);
   bool DoPhotonPV         = CL.GetBool("DoPhotonPV", false);
   bool DoElectronPV       = CL.GetBool("DoElectronPV", false);
   bool DoPuppiJet         = CL.GetBool("DoPuppiJet", false);
   bool DoPuppiJetForMET   = CL.GetBool("DoPuppiJetForMET", false);
   bool DoPuppiJetMin25    = CL.GetBool("DoPuppiJetMin25", false);
   bool DoPuppiHT          = CL.GetBool("DoPuppiHT", false);
   bool DoPuppiMET         = CL.GetBool("DoPuppiMET", false);
   bool DoPFTau            = CL.GetBool("DoPFTau", false);
   bool DoPFIsoTau         = CL.GetBool("DoPFIsoTau", false);
   bool DoCaloJet          = CL.GetBool("DoCaloJet", false);
   bool DoCaloHT           = CL.GetBool("DoCaloHT", false);
   bool DoTrackerJet       = CL.GetBool("DoTrackerJet", false);
   bool DoTrackerHT        = CL.GetBool("DoTrackerHT", false);
   bool DoTrackerMHT       = CL.GetBool("DoTrackerMHT", false);
   bool DoTrackerMET       = CL.GetBool("DoTrackerMET", false);
   bool DoTkTau            = CL.GetBool("DoTkTau", false);
   bool DoCaloTkTau        = CL.GetBool("DoCaloTkTau", false);
   bool DoTkEGTau          = CL.GetBool("DoTkEGTau", false);
   bool DoNNTauLoose       = CL.GetBool("DoNNTauLoose", false);
   bool DoNNTauTight       = CL.GetBool("DoNNTauTight", false);
   bool DoCaloTau          = CL.GetBool("DoCaloTau", false);

   SetThesisStyle();

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Scaling plots :D");

   PdfFile.SetAutomaticHomeButton();
   
   vector<double> EGThresholds = {12, 15, 20, 25, 30};
   vector<double> MuonThresholds = {3, 5, 12, 15, 20, 25, 30};
   vector<double> TauThresholds = {20, 25, 27, 30, 40, 50, 60, 70};
   vector<double> TauThresholds2 = {30, 40, 50, 60, 70};
   vector<double> JetThresholds = {15, 20, 25, 30, 40, 50, 75, 100, 150, 200};
   vector<double> PuppiJetThresholds = {30, 40, 50, 75, 100, 125, 150};
   vector<double> ForwardPuppiJetThresholds = {30, 40, 50, 75, 100, 125};
   vector<double> TkJetThresholds = {15, 20, 25, 30, 40, 50, 75, 100};
   vector<double> CaloJetThresholds = {50, 75, 100, 125, 150};
   vector<double> HTThresholds = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
   vector<double> TkHTThresholds = {50, 100, 150, 200, 250, 300, 350};
   vector<double> LowMHTThresholds = {20, 30, 40, 50, 60, 70};
   vector<double> TkMHTThresholds = {20, 30, 40, 50, 60, 70, 100, 150};
   vector<double> MHTThresholds = {70, 80, 90, 100, 125, 150, 175};
   vector<double> LowMETThresholds = {20, 30, 40, 50, 60, 70};
   vector<double> METThresholds = {70, 80, 90, 100, 125, 150, 175};

   if(DoSTAMuon == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "StandaloneMuonIso", MuonThresholds, Reference,
         Prefix + "StandaloneMuonIsoSmooth", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "StandaloneMuonIso", MuonThresholds, Reference,
         Prefix + "StandaloneMuonIso", "PT", TYPE_FITFLOAT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "StandaloneMuonIso", MuonThresholds, Reference,
         Prefix + "StandaloneMuonIsoTanh", "PT", TYPE_FITTANH);
   }
   if(DoSTADisplacedMuon == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "StandaloneDisplacedMuonIso", MuonThresholds, Reference,
         Prefix + "StandaloneDisplacedMuonIsoSmooth", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "StandaloneDisplacedMuonIso", MuonThresholds, Reference,
         Prefix + "StandaloneDisplacedMuonIso", "PT", TYPE_FITFLOAT);
   }
   if(DoTkMuon == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkMuonIso", MuonThresholds, Reference,
         Prefix + "TkMuon", "PT", TYPE_SMOOTH_TIGHT);
   if(DoTkMuonStub == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkMuonStubIso", MuonThresholds, Reference,
         Prefix + "TkMuonStubIso", "PT", TYPE_SMOOTH_TIGHT);
   if(DoTkMuonStubS12 == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkMuonStubS12Iso", MuonThresholds, Reference,
         Prefix + "TkMuonStubS12Iso", "PT", TYPE_SMOOTH_TIGHT);
   if(DoEG == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EG", EGThresholds, Reference,
         Prefix + "EG", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EG", EGThresholds, Reference,
         Prefix + "EGBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EG", EGThresholds, Reference,
         Prefix + "EGEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
   }
   if(DoEGExtended == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGExtendedIso", EGThresholds, Reference,
         Prefix + "EGExtended", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGExtendedIso", EGThresholds, Reference,
         Prefix + "EGExtendedFit", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGExtendedIso", EGThresholds, Reference,
         Prefix + "EGExtendedFit2", "PT", TYPE_FITFIX2, QUADRATIC);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGExtendedIso", EGThresholds, Reference,
         Prefix + "EGExtendedBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGExtendedIso", EGThresholds, Reference,
         Prefix + "EGExtendedEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
   }
   if(DoEGTrack == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGTrackID", EGThresholds, Reference,
         Prefix + "EGTrackID", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGTrackID", EGThresholds, Reference,
         Prefix + "EGTrackIDBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGTrackID", EGThresholds, Reference,
         Prefix + "EGTrackIDEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGTrackIDExtendedIso", EGThresholds, Reference,
         Prefix + "EGTrackIDExtended", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGTrackIDExtendedIso", EGThresholds, Reference,
         Prefix + "EGTrackIDExtendedBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "EGTrackIDExtendedIso", EGThresholds, Reference,
         Prefix + "EGTrackIDExtendedEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
   }
   if(DoElectron == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkElectronTrackID", EGThresholds, Reference,
         Prefix + "TkElectronTrackID", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkElectronTrackID", EGThresholds, Reference,
         Prefix + "TkElectronTrackIDBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkElectronTrackID", EGThresholds, Reference,
         Prefix + "TkElectronTrackIDEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkElectronTrackIDExtendedIso", EGThresholds, Reference,
         Prefix + "TkElectronTrackIDExtended", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoZElectron == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkElectronTrackIDZ", EGThresholds, Reference,
         Prefix + "TkElectronTrackIDZ", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkElectronTrackIDZ", EGThresholds, Reference,
         Prefix + "TkElectronTrackIDZBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkElectronTrackIDZ", EGThresholds, Reference,
         Prefix + "TkElectronTrackIDZEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
   }
   if(DoIsoElectron == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoElectron", EGThresholds, Reference,
         Prefix + "TkIsoElectron", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoElectron", EGThresholds, Reference,
         Prefix + "TkIsoElectronBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoElectron", EGThresholds, Reference,
         Prefix + "TkIsoElectronEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoElectronExtended", EGThresholds, Reference,
         Prefix + "TkIsoElectronExtended", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoPhoton == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoPhotonTrackID", EGThresholds, Reference,
         Prefix + "TkIsoPhotonTrackID", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoPhotonTrackID", EGThresholds, Reference,
         Prefix + "TkIsoPhotonTrackIDBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoPhotonTrackID", EGThresholds, Reference,
         Prefix + "TkIsoPhotonTrackIDEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoPhotonTrackIDExtended", EGThresholds, Reference,
         Prefix + "TkIsoPhotonTrackIDExtended", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoPhotonPV == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoPhotonPVTrackID", EGThresholds, Reference,
         Prefix + "TkIsoPhotonPVTrackID", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoPhotonPVTrackID", EGThresholds, Reference,
         Prefix + "TkIsoPhotonPVTrackIDBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoPhotonPVTrackID", EGThresholds, Reference,
         Prefix + "TkIsoPhotonPVTrackIDEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
   }
   if(DoElectronPV == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoElectronPV", EGThresholds, Reference,
         Prefix + "TkIsoElectronPV", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoElectronPV", EGThresholds, Reference,
         Prefix + "TkIsoElectronPVBarrel", "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkIsoElectronPV", EGThresholds, Reference,
         Prefix + "TkIsoElectronPVEndcap", "PTEtaLarge", TYPE_SMOOTH_TIGHT);
   }
   if(DoPuppiJet == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJet", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetFitFix2", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJet", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetFitFix", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJet", PuppiJetThresholds, Reference,
         Prefix + "PuppiJet", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJetForward", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetForward", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoPuppiJetForMET == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJetForMET", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetForMETFitFix", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJet", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetForMET", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJetForMETForward", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetForMETForwardFitFix", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJetForMETForward", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetForMETForwardFitFix2", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJetForMETForward", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetForMETForwardFitFloat", "PT", TYPE_FITFLOAT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJetForMETForward", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetForMETForward", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoPuppiJetMin25 == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJet25", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetMin25FitFix2", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJet25", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetMin25FitFix", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJet25", PuppiJetThresholds, Reference,
         Prefix + "PuppiJetMin25", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJetForward25", ForwardPuppiJetThresholds, Reference,
         Prefix + "PuppiJetMin25ForwardFitFix2", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJetForward25", ForwardPuppiJetThresholds, Reference,
         Prefix + "PuppiJetMin25ForwardFitFix", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiJetForward25", ForwardPuppiJetThresholds, Reference,
         Prefix + "PuppiJetMin25Forward", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoPuppiHT == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiHT30", HTThresholds, Reference,
         Prefix + "PuppiHT30", "PT", TYPE_SMOOTH_TIGHT);
   if(DoPuppiMET == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiMET", METThresholds, Reference,
         Prefix + "PuppiMETFloat", "PT", TYPE_FITFLOAT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiMET", METThresholds, Reference,
         Prefix + "PuppiMETFit", "PT", TYPE_FIT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiMET", METThresholds, Reference,
         Prefix + "PuppiMETFitFix", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PuppiMET", METThresholds, Reference,
         Prefix + "PuppiMET", "PT", TYPE_FITFIX2);
   }
   if(DoPFTau == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PFTau", TauThresholds, Reference,
         Prefix + "PFTau", "PT", TYPE_SMOOTH_TIGHT);
   if(DoPFIsoTau == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "PFIsoTau", TauThresholds, Reference,
         Prefix + "PFIsoTau", "PT", TYPE_SMOOTH_TIGHT);
   if(DoCaloJet == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloJet", CaloJetThresholds, Reference,
         Prefix + "CaloJet", "PT", TYPE_FIT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloJet", CaloJetThresholds, Reference,
         Prefix + "CaloJet", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloJet", CaloJetThresholds, Reference,
         Prefix + "CaloJet", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloJet", CaloJetThresholds, Reference,
         Prefix + "CaloJet", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloJetBarrel", CaloJetThresholds, Reference,
         Prefix + "CaloJetBarrel", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloJetEndcap", CaloJetThresholds, Reference,
         Prefix + "CaloJetEndcap", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloJetEndcap", CaloJetThresholds, Reference,
         Prefix + "CaloJetEndcapStringterpolate", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloJetFoward", CaloJetThresholds, Reference,
         Prefix + "CaloJetFoward", "PT", TYPE_SMOOTH_TIGHT);
   }
   // if(DoCaloHT == true)
   //    ProcessFile(PdfFile, InputFileName, CurvesFileName, "", Thresholds, Reference,
   //       "", "PT", TYPE_SMOOTH_TIGHT);
   if(DoTrackerJet == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerJet", TkJetThresholds, Reference,
         Prefix + "TrackerJet", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerJet", TkJetThresholds, Reference,
         Prefix + "TrackerJetFit", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerJetCharged", TkJetThresholds, Reference,
         Prefix + "TrackerJetCharged", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerJetCharged", TkJetThresholds, Reference,
         Prefix + "TrackerJetChargedFit", "PT", TYPE_FITFIX);
   }
   if(DoTrackerHT == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerHT5", TkHTThresholds, Reference,
         Prefix + "TrackerHT5", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerHTCharged5", TkHTThresholds, Reference,
         Prefix + "TrackerHTCharged5", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoTrackerMHT == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerMHT5", TkMHTThresholds, Reference,
         Prefix + "TrackerMHT5", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerMHTCharged5", TkMHTThresholds, Reference,
         Prefix + "TrackerMHTCharged5", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerMHT5MET", TkMHTThresholds, Reference,
         Prefix + "TrackerMHT5MET", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerMHT5MET", TkMHTThresholds, Reference,
         Prefix + "TrackerMHT5METFit", "PT", TYPE_FITFIX, QUADRATIC);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerHTChargedMET5", TkMHTThresholds, Reference,
         Prefix + "TrackerMHTCharged5MET", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoTrackerMET == true)
   {
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerMET", METThresholds, Reference,
         Prefix + "TrackerMET", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TrackerMETCharged", METThresholds, Reference,
         Prefix + "TrackerMETCharged", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoTkTau == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkTau", TauThresholds, Reference,
         Prefix + "TkTau", "PT", TYPE_SMOOTH_TIGHT);
   if(DoCaloTkTau == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloTkTau", TauThresholds, Reference,
         Prefix + "CaloTkTau", "PT", TYPE_SMOOTH_TIGHT);
   if(DoTkEGTau == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "TkEGTau", TauThresholds, Reference,
         Prefix + "TkEGTau", "PT", TYPE_SMOOTH_TIGHT);
   if(DoNNTauLoose == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "NNTauLooseIso", TauThresholds, Reference,
         Prefix + "NNTauLoose", "PT", TYPE_SMOOTH_TIGHT);
   if(DoNNTauTight == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "NNTauIso", TauThresholds2, Reference,
         Prefix + "NNTauTight", "PT", TYPE_SMOOTH_TIGHT);
   if(DoCaloTau == true)
      ProcessFile(PdfFile, InputFileName, CurvesFileName, "CaloTauIso", TauThresholds, Reference,
         Prefix + "CaloTau", "PT", TYPE_SMOOTH_TIGHT);
   // if(Do == true)
   //    ProcessFile(PdfFile, InputFileName, CurvesFileName, "", Thresholds, Reference,
   //       "", "PT", TYPE_SMOOTH_TIGHT);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void ProcessFile(PdfFileHelper &PdfFile, string FileName, string OutputFileName,
   string Prefix, vector<double> Thresholds,
   double Target, string Tag, string Name, int Type, int Scaling)
{
   string TypeString = "UNKNOWN";
   if(Type == TYPE_FIT)
      TypeString = "Fit";
   if(Type == TYPE_FITFIX)
      TypeString = "Fit (plateau == 1)";
   if(Type == TYPE_FITFIX2)
      TypeString = "Fit (plateau == 1 && float baseline)";
   if(Type == TYPE_FITFLOAT)
      TypeString = "Fit (float plateau and baseline)";
   if(Type == TYPE_FITTANH)
      TypeString = "Fit (tanh)";
   if(Type == TYPE_SMOOTH_LOOSE)
      TypeString = "Stringterpolate (loose)";
   if(Type == TYPE_SMOOTH_TIGHT)
      TypeString = "Stringterpolate (tight)";
   if(Type == TYPE_SMOOTH_SUPERTIGHT)
      TypeString = "Stringterpolate (super tight)";
   if(Type == TYPE_SMOOTH_ULTRATIGHT)
      TypeString = "Stringterpolate (ultra tight)";

   vector<string> Text(11);
   Text[0] = "Plots for file";
   Text[1] = FileName;
   Text[2] = "";
   Text[3] = "...and object prefix";
   Text[4] = Prefix;
   Text[5] = "";
   Text[6] = "...and type";
   Text[7] = TypeString;
   Text[8] = "";
   Text[9] = "...and name";
   Text[10] = Name;
   PdfFile.AddTextPage(Text);

   Prefix = Prefix + "/" + Prefix;

   TFile File(FileName.c_str());

   vector<double> CrossOver(Thresholds.size());

   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      PdfFile.AddTextPage(Form("Threshold = %.1f", Thresholds[i]));
      if(Type == TYPE_SMOOTH_LOOSE || Type == TYPE_SMOOTH_TIGHT
         || Type == TYPE_SMOOTH_SUPERTIGHT || Type == TYPE_SMOOTH_ULTRATIGHT)
         CrossOver[i] = SmoothTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, Type);
      if(Type == TYPE_FIT)
         CrossOver[i] = FitTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, false, false, false, false);
      if(Type == TYPE_FITFLOAT)
         CrossOver[i] = FitTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, false, false, false, true);
      if(Type == TYPE_FITFIX)
         CrossOver[i] = FitTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, false, false, true, false);
      if(Type == TYPE_FITFIX2)
         CrossOver[i] = FitTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, false, false, true, true);
      if(Type == TYPE_FITTANH)
         CrossOver[i] = FitTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, true, false, true, true);
   }

   File.Close();
   
   PdfFile.AddTextPage("Scaling Curve for " + Prefix);
   
   TGraph G;
   G.SetNameTitle(Tag.c_str(), "");
   G.GetXaxis()->SetTitle("Threshold");
   G.GetYaxis()->SetTitle("95\% location");
   TGraph G2;
   G2.SetNameTitle(Tag.c_str(), "");
   G2.GetXaxis()->SetTitle("95\% location");
   G2.GetYaxis()->SetTitle("Threshold");

   double Min = 0;
   double Max = Thresholds[Thresholds.size()-1];
   double Difference = Max - Min;
   Max = Max + Difference * 0.2;

   double YMin = 0;
   double YMax = -10000;
   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      cout << Thresholds[i] << " " << CrossOver[i] << endl;
      if(CrossOver[i] != CrossOver[i])
         continue;
      if(CrossOver[i] < 0)
         continue;
      if(i == Thresholds.size() - 1 || CrossOver[i+1] > CrossOver[i])
      {
         G.SetPoint(G.GetN(), Thresholds[i], CrossOver[i]);
         G2.SetPoint(G2.GetN(), CrossOver[i], Thresholds[i]);
         if(YMin > CrossOver[i])
            YMin = CrossOver[i];
         if(YMax < CrossOver[i])
            YMax = CrossOver[i];
      }
   }
   Difference = YMax - YMin;
   YMax = YMax + Difference * 0.2;

   string FunctionString = "pol1";
   if(Scaling == QUADRATIC)
      FunctionString = "pol2";

   TF1 Function("Function", FunctionString.c_str(), Min, Max);
   TF1 Function2("Function2", "(-[1]+sqrt(max([1]*[1]-4*[0]*([2]-x),0.0)))/(2*[0])", Min, Max);

   if(Scaling == LINEAR)
      G.Fit(&Function, "N");
   else if(Scaling == QUADRATIC)
      G2.Fit(&Function, "N");

   TH2D HWorld("HWorld", Form(";Thresholds;%d%% location", int(Target * 100)), 100, Min, Max, 100, YMin, YMax);
   HWorld.SetStats(0);

   TCanvas Canvas;
   HWorld.Draw("axis");
   G.Draw("pl");
   if(Scaling == LINEAR)
      Function.Draw("same");
   else
   {
      Function2.SetParameter(0, Function.GetParameter(2));
      Function2.SetParameter(1, Function.GetParameter(1));
      Function2.SetParameter(2, Function.GetParameter(0));
      Function2.Draw("same");
   }

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextColor(kMagenta);
   if(Scaling == LINEAR)
   {
      Latex.DrawLatex(0.15, 0.80, Form("p0 = %.03f #pm %.03f", Function.GetParameter(0), Function.GetParError(0)));
      Latex.DrawLatex(0.15, 0.75, Form("p1 = %.03f #pm %.03f", Function.GetParameter(1), Function.GetParError(1)));
   }
   else
   {
      Latex.DrawLatex(0.15, 0.80, "x = p0 y^{2} + p1 y + p2");
      Latex.DrawLatex(0.15, 0.75, Form("p0 = %.05f #pm %.05f", Function.GetParameter(2), Function.GetParError(2)));
      Latex.DrawLatex(0.15, 0.70, Form("p1 = %.05f #pm %.05f", Function.GetParameter(1), Function.GetParError(1)));
      Latex.DrawLatex(0.15, 0.65, Form("p2 = %.05f #pm %.05f", Function.GetParameter(0), Function.GetParError(0)));
   }

   PdfFile.AddCanvas(Canvas);
   
   DataHelper DHFile(OutputFileName);

   DHFile.Erase(Tag);
   DHFile[Tag]["Percentage"] = Target;
   DHFile[Tag]["N"] = G.GetN();

   for(int i = 0; i < G.GetN(); i++)
   {
      double X, Y;
      G.GetPoint(i, X, Y);
      DHFile[Tag][Form("X%d",i)] = X;
      DHFile[Tag][Form("Y%d",i)] = Y;
   }

   DHFile.SaveToFile(OutputFileName);
}


