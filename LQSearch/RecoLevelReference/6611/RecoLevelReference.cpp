#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <sstream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper.h"
#include "DrawRandom.h"
#include "TauHelperFunctions.h"
#include "ReadNTPTree.h"

int main(int argc, char *argv[]);
void RecoLevelReference(string InputLQMass = "250");
void AddThreeHistogramOverlayPlot(PsFileHelper &PsFile,
   TH1D *H1, TH1D *H2, TH1D *H3, string Title,
   string L1 = "Non-leading", string L2 = "Leading", string L3 = "Sub-leading",
   string Option = "", bool LogY = false);
int FindChildIndex(NTPTreeMessenger &M, int ChildPDGID, int ParentPDGID);
int TraceBHadron(NTPTreeMessenger &M, int StartIndex);
bool HasB(int PDGID);
int FindClosestJet(float *JetCollectionEta, float *JetCollectionPhi, int JetCount, double Eta, double Phi);

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   TStyle gStyle;
   
   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle.SetNumberContours(NCont);

   string InputLQMass = "350";
   if(argc > 1)
      InputLQMass = argv[1];
   RecoLevelReference(InputLQMass);

   return 0;
}

void RecoLevelReference(string InputLQMass)
{
   // Read inputs
   TFile F(("Samples/LQ" + InputLQMass + "_All.root").c_str());
   TTree *NTPTree = (TTree *)F.Get("ntp1");

   NTPTreeMessenger M;
   M.SetBranchAddress(NTPTree);

   // Output file header
   PsFileHelper PsFile("LQReconstructionLevelDistributions_" + InputLQMass + "GeV.ps");
   PsFile.AddTextPage("LQ3 Reconstruction Level Distributions");

   vector<string> ExplanationText;
   ExplanationText.push_back("Generate samples with CMSSW 3.8.7");
   ExplanationText.push_back("D6T tune, turning on LQ, force decay to b and nu_tau");
   ExplanationText.push_back("(Following recipe from Dinko and Francesco)");
   ExplanationText.push_back("Input mass: " + InputLQMass + " GeV/c");
   ExplanationText.push_back("Export with CMSSW 3.9.8 (does this matter?)");
   ExplanationText.push_back("      Code is the latest as of March 2, 2011 (HiggsToWW2e tag V18-3_9_X)");
   PsFile.AddTextPage(ExplanationText);

   // PU, PV histograms
   TH1D HNPU("HNPU", "Number of pileups", 31, -0.5, 30.5);
   TH1D HZPositionPU("HZPositionPU", "Z position of PU", 100, -100, 100);
   
   TH1D HNPV("HNPV", "Number of primary vertices", 31, -0.5, 30.5);
   TH1D HPVZ("HPVZ", "Z position of PV", 100, -100, 100);
   TH2D HPVXY("HPVXY", "X, Y position of PV;X;Y", 100, -10, 10, 100, -10, 10);
   TH1D HPVXYSignificance("HPVXYSignificance", "XY significance of PV", 100, 0, 20);
   TH1D HPVSumPT("HPVSumPT", "Sum PT of PV", 100, 0, 1000);
   TH1D HPVndof("HPVndof", "number of degree of freedom of PV", 100, 0, 200);
   TH1D HPVChi2("HPVChi2", "chi2 of PV", 100, 0, 100);
   
   TH2D HNPUVsNPV("HNPUVsNPV", "number of PU vs. number of PV;PU;PV", 31, -0.5, 30.5, 31, -0.5, 30.5);

   TH1D HBestPVZ("HBestPVZ", "Z position of best PV", 100, -100, 100);
   TH2D HBestPVXY("HBestPVXY", "X, Y position of best PV;X;Y", 100, -10, 10, 100, -10, 10);
   TH1D HBestPVXYSignificance("HBestPVXYSignificance", "XY significance of best PV", 100, 0, 20);
   TH1D HBestPVSumPT("HBestPVSumPT", "Sum PT of best PV", 100, 0, 1000);
   TH1D HBestPVndof("HBestPVndof", "number of degree of freedom of best PV", 100, 0, 200);
   TH1D HBestPVChi2("HBestPVChi2", "chi2 of best PV", 100, 0, 100);

   // Calo jet histograms
   TH1D HNRawAK5Jet("HNRawAK5Jet", "Number of all calo jets (no jet ID)", 31, -0.5, 30.5);
   TH1D HNAK5Jet("HNAK5Jet", "Number of calo jets", 31, -0.5, 30.5);
   TH1D HNAK5Jet15("HNAK5Jet15", "Number of calo jets > 15", 31, -0.5, 30.5);
   TH1D HNAK5Jet30("HNAK5Jet30", "Number of calo jets > 30", 31, -0.5, 30.5);
   TH1D HNAK5Jet50("HNAK5Jet50", "Number of calo jets > 50", 31, -0.5, 30.5);
   TH1D HNAK5Jet100("HNAK5Jet100", "Number of calo jets > 100", 31, -0.5, 30.5);
   TH1D HNAK5Jet150("HNAK5Jet150", "Number of calo jets > 150", 31, -0.5, 30.5);
   TH1D HEnergyAK5Jet("HEnergyAK5Jet", "Calo jet energy distribution", 100, 0, 1000);
   TH1D HPTAK5Jet("HPTAK5Jet", "Calo jet PT distribution", 100, 0, 1000);
   TH1D HEtaAK5Jet("HEtaAK5Jet", "Calo jet eta distribution", 100, -4, 4);
   TH1D HPhiAK5Jet("HPhiAK5Jet", "Calo jet phi distribution", 100, -3.2, 3.2);
   TH1D HLeadingAK5JetPT("HLeadingAK5JetPT", "Leading calo jet PT", 100, 0, 1000);
   TH1D HLeadingAK5JetEta("HLeadingAK5JetEta", "Leading calo jet eta", 100, -4, 4);
   TH1D HLeadingAK5JetPhi("HLeadingAK5JetPhi", "Leading calo jet phi", 100, -3.2, 3.2);
   TH1D HSubLeadingAK5JetPT("HSubLeadingAK5JetPT", "Sub-leading calo jet PT", 100, 0, 1000);
   TH1D HSubLeadingAK5JetEta("HSubLeadingAK5JetEta", "Sub-leading calo jet eta", 100, -4, 4);
   TH1D HSubLeadingAK5JetPhi("HSubLeadingAK5JetPhi", "Sub-leading calo jet phi", 100, -3.2, 3.2);
   TH2D HLeadingTwoAK5JetsPTVsPT("HLeadingTwoAK5JetsPTVsPT", "Leading two calo jets PT vs. PT;Leading;Sub-leading",
      100, 0, 1000, 100, 0, 1000);
   TH1D HLeadingTwoAK5JetsDPhi("HLeadingTwoAK5JetsDPhi", "Leading two calo jets dphi", 100, -3.2, 3.2);
   TH1D HLeadingTwoAK5JetsDR("HLeadingTwoAK5JetsDR", "Leading two calo jets dR", 100, 0, 3.2);

   // Calo jet b-tagging histograms
   TH1D HCombinedSecondaryVertexBTagNonLeadingCaloJet("HCombinedSecondaryVertexBTagNonLeadingCaloJet",
      "combined secondary vertex b tag for Calo jet", 100, 0, 1.5);
   TH1D HCombinedSecondaryVertexMVABTagNonLeadingCaloJet("HCombinedSecondaryVertexMVABTagNonLeadingCaloJet",
      "combined secondary vertex MVA b tag for Calo jet", 100, 0, 1.5);
   TH1D HJetBProbabilityBTagNonLeadingCaloJet("HJetBProbabilityBTagNonLeadingCaloJet",
      "jet b probability b tag for Calo jet", 100, 0, 2);
   TH1D HJetProbabilityBTagNonLeadingCaloJet("HJetProbabilityBTagNonLeadingCaloJet",
      "jet probability b tag for Calo jet", 100, 0, 2);
   TH1D HSimpleSecondaryVertexHighEffBTagNonLeadingCaloJet("HSimpleSecondaryVertexHighEffBTagNonLeadingCaloJet",
      "simple secondary vertex high eff. b tag for Calo jet", 100, 0, 6);
   TH1D HSimpleSecondaryVertexHighPurBTagNonLeadingCaloJet("HSimpleSecondaryVertexHighPurBTagNonLeadingCaloJet",
      "simple secondary vertex high pur. b tag for Calo jet", 100, 0, 6);
   TH1D HSoftMuonBTagNonLeadingCaloJet("HSoftMuonBTagNonLeadingCaloJet",
      "soft muon b tag for Calo jet", 100, 0, 1);
   TH1D HSoftMuonByIP3DBTagNonLeadingCaloJet("HSoftMuonByIP3DBTagNonLeadingCaloJet",
      "soft muon (IP3D) b tag for Calo jet", 100, 0, 100);
   TH1D HSoftMuonByPtBTagNonLeadingCaloJet("HSoftMuonByPtBTagNonLeadingCaloJet",
      "soft muon (PT) b tag for Calo jet", 100, 0, 40);
   TH1D HSoftElectronBTagNonLeadingCaloJet("HSoftElectronBTagNonLeadingCaloJet",
      "soft Electron b tag for Calo jet", 100, 0, 2);
   TH1D HSoftElectronByIP3DBTagNonLeadingCaloJet("HSoftElectronByIP3DBTagNonLeadingCaloJet",
      "soft Electron (IP3D) b tag for Calo jet", 100, 0, 100);
   TH1D HSoftElectronByPtBTagNonLeadingCaloJet("HSoftElectronByPtBTagNonLeadingCaloJet",
      "soft Electron (PT) b tag for Calo jet", 100, 0, 40);
   TH1D HTrackCountingHighPurBTagNonLeadingCaloJet("HTrackCountingHighPurBTagNonLeadingCaloJet",
      "track counting b tag (high pur.) for Calo jet", 100, 0, 100);
   TH1D HTrackCountingHighEffBTagNonLeadingCaloJet("HTrackCountingHighEffBTagNonLeadingCaloJet",
      "track counting b tag (high eff.) for Calo jet", 100, 0, 100);
   
   TH1D HCombinedSecondaryVertexBTagLeadingCaloJet("HCombinedSecondaryVertexBTagLeadingCaloJet",
      "combined secondary vertex b tag for leading Calo jet", 100, 0, 1.5);
   TH1D HCombinedSecondaryVertexMVABTagLeadingCaloJet("HCombinedSecondaryVertexMVABTagLeadingCaloJet",
      "combined secondary vertex MVA b tag for leading Calo jet", 100, 0, 1.5);
   TH1D HJetBProbabilityBTagLeadingCaloJet("HJetBProbabilityBTagLeadingCaloJet",
      "jet b probability b tag for leading Calo jet", 100, 0, 2);
   TH1D HJetProbabilityBTagLeadingCaloJet("HJetProbabilityBTagLeadingCaloJet",
      "jet probability b tag for leading Calo jet", 100, 0, 2);
   TH1D HSimpleSecondaryVertexHighEffBTagLeadingCaloJet("HSimpleSecondaryVertexHighEffBTagLeadingCaloJet",
      "simple secondary vertex high eff. b tag for leading Calo jet", 100, 0, 6);
   TH1D HSimpleSecondaryVertexHighPurBTagLeadingCaloJet("HSimpleSecondaryVertexHighPurBTagLeadingCaloJet",
      "simple secondary vertex high pur. b tag for leading Calo jet", 100, 0, 6);
   TH1D HSoftMuonBTagLeadingCaloJet("HSoftMuonBTagLeadingCaloJet",
      "soft muon b tag for leading Calo jet", 100, 0, 1);
   TH1D HSoftMuonByIP3DBTagLeadingCaloJet("HSoftMuonByIP3DBTagLeadingCaloJet",
      "soft muon (IP3D) b tag for leading Calo jet", 100, 0, 100);
   TH1D HSoftMuonByPtBTagLeadingCaloJet("HSoftMuonByPtBTagLeadingCaloJet",
      "soft muon (PT) b tag for leading Calo jet", 100, 0, 40);
   TH1D HSoftElectronBTagLeadingCaloJet("HSoftElectronBTagLeadingCaloJet",
      "soft Electron b tag for leading Calo jet", 100, 0, 2);
   TH1D HSoftElectronByIP3DBTagLeadingCaloJet("HSoftElectronByIP3DBTagLeadingCaloJet",
      "soft Electron (IP3D) b tag for leading Calo jet", 100, 0, 100);
   TH1D HSoftElectronByPtBTagLeadingCaloJet("HSoftElectronByPtBTagLeadingCaloJet",
      "soft Electron (PT) b tag for leading Calo jet", 100, 0, 40);
   TH1D HTrackCountingHighPurBTagLeadingCaloJet("HTrackCountingHighPurBTagLeadingCaloJet",
      "track counting b tag (high pur.) for leading Calo jet", 100, 0, 100);
   TH1D HTrackCountingHighEffBTagLeadingCaloJet("HTrackCountingHighEffBTagLeadingCaloJet",
      "track counting b tag (high eff.) for leading Calo jet", 100, 0, 100);
   
   TH1D HCombinedSecondaryVertexBTagSubLeadingCaloJet("HCombinedSecondaryVertexBTagSubLeadingCaloJet",
      "combined secondary vertex b tag for leading Calo jet", 100, 0, 1.5);
   TH1D HCombinedSecondaryVertexMVABTagSubLeadingCaloJet("HCombinedSecondaryVertexMVABTagSubLeadingCaloJet",
      "combined secondary vertex MVA b tag for leading Calo jet", 100, 0, 1.5);
   TH1D HJetBProbabilityBTagSubLeadingCaloJet("HJetBProbabilityBTagSubLeadingCaloJet",
      "jet b probability b tag for leading Calo jet", 100, 0, 2);
   TH1D HJetProbabilityBTagSubLeadingCaloJet("HJetProbabilityBTagSubLeadingCaloJet",
      "jet probability b tag for leading Calo jet", 100, 0, 2);
   TH1D HSimpleSecondaryVertexHighEffBTagSubLeadingCaloJet("HSimpleSecondaryVertexHighEffBTagSubLeadingCaloJet",
      "simple secondary vertex high eff. b tag for leading Calo jet", 100, 0, 6);
   TH1D HSimpleSecondaryVertexHighPurBTagSubLeadingCaloJet("HSimpleSecondaryVertexHighPurBTagSubLeadingCaloJet",
      "simple secondary vertex high pur. b tag for leading Calo jet", 100, 0, 6);
   TH1D HSoftMuonBTagSubLeadingCaloJet("HSoftMuonBTagSubLeadingCaloJet",
      "soft muon b tag for leading Calo jet", 100, 0, 1);
   TH1D HSoftMuonByIP3DBTagSubLeadingCaloJet("HSoftMuonByIP3DBTagSubLeadingCaloJet",
      "soft muon (IP3D) b tag for leading Calo jet", 100, 0, 100);
   TH1D HSoftMuonByPtBTagSubLeadingCaloJet("HSoftMuonByPtBTagSubLeadingCaloJet",
      "soft muon (PT) b tag for leading Calo jet", 100, 0, 40);
   TH1D HSoftElectronBTagSubLeadingCaloJet("HSoftElectronBTagSubLeadingCaloJet",
      "soft Electron b tag for leading Calo jet", 100, 0, 2);
   TH1D HSoftElectronByIP3DBTagSubLeadingCaloJet("HSoftElectronByIP3DBTagSubLeadingCaloJet",
      "soft Electron (IP3D) b tag for leading Calo jet", 100, 0, 100);
   TH1D HSoftElectronByPtBTagSubLeadingCaloJet("HSoftElectronByPtBTagSubLeadingCaloJet",
      "soft Electron (PT) b tag for leading Calo jet", 100, 0, 40);
   TH1D HTrackCountingHighPurBTagSubLeadingCaloJet("HTrackCountingHighPurBTagSubLeadingCaloJet",
      "track counting b tag (high pur.) for leading Calo jet", 100, 0, 100);
   TH1D HTrackCountingHighEffBTagSubLeadingCaloJet("HTrackCountingHighEffBTagSubLeadingCaloJet",
      "track counting b tag (high eff.) for leading Calo jet", 100, 0, 100);

   // PF jet histograms
   TH1D HNRawPFJet("HNRawPFJet", "Number of all PF jets (no Jet ID)", 31, -0.5, 30.5);
   TH1D HNPFJet("HNPFJet", "Number of PF jets", 31, -0.5, 30.5);
   TH1D HNPFJet15("HNPFJet15", "Number of PF jets > 15", 31, -0.5, 30.5);
   TH1D HNPFJet30("HNPFJet30", "Number of PF jets > 30", 31, -0.5, 30.5);
   TH1D HNPFJet50("HNPFJet50", "Number of PF jets > 50", 31, -0.5, 30.5);
   TH1D HNPFJet100("HNPFJet100", "Number of PF jets > 100", 31, -0.5, 30.5);
   TH1D HNPFJet150("HNPFJet150", "Number of PF jets > 150", 31, -0.5, 30.5);
   TH1D HEnergyPFJet("HEnergyPFJet", "PF jet energy distribution", 100, 0, 1000);
   TH1D HPTPFJet("HPTPFJet", "PF jet PT distribution", 100, 0, 1000);
   TH1D HEtaPFJet("HEtaPFJet", "PF jet eta distribution", 100, -4, 4);
   TH1D HPhiPFJet("HPhiPFJet", "PF jet phi distribution", 100, -3.2, 3.2);
   TH1D HLeadingPFJetPT("HLeadingPFJetPT", "Leading PF jet PT", 100, 0, 1000);
   TH1D HLeadingPFJetEta("HLeadingPFJetEta", "Leading PF jet eta", 100, -4, 4);
   TH1D HLeadingPFJetPhi("HLeadingPFJetPhi", "Leading PF jet phi", 100, -3.2, 3.2);
   TH1D HSubLeadingPFJetPT("HSubLeadingPFJetPT", "Sub-leading PF jet PT", 100, 0, 1000);
   TH1D HSubLeadingPFJetEta("HSubLeadingPFJetEta", "Sub-leading PF jet eta", 100, -4, 4);
   TH1D HSubLeadingPFJetPhi("HSubLeadingPFJetPhi", "Sub-leading PF jet phi", 100, -3.2, 3.2);
   TH2D HLeadingTwoPFJetsPTVsPT("HLeadingTwoPFJetsPTVsPT", "Leading two PF jets PT vs. PT;Leading;Sub-leading",
      100, 0, 1000, 100, 0, 1000);
   TH1D HLeadingTwoPFJetsDPhi("HLeadingTwoPFJetsDPhi", "Leading two PF jets dphi", 100, -3.2, 3.2);
   TH1D HLeadingTwoPFJetsDR("HLeadingTwoPFJetsDR", "Leading two PF jets dR", 100, 0, 3.2);
   
   // PF jet b-tagging histograms
   TH1D HCombinedSecondaryVertexBTagNonLeadingPFJet("HCombinedSecondaryVertexBTagNonLeadingPFJet",
      "combined secondary vertex b tag for PF jet", 100, 0, 1.5);
   TH1D HCombinedSecondaryVertexMVABTagNonLeadingPFJet("HCombinedSecondaryVertexMVABTagNonLeadingPFJet",
      "combined secondary vertex MVA b tag for PF jet", 100, 0, 1.5);
   TH1D HJetBProbabilityBTagNonLeadingPFJet("HJetBProbabilityBTagNonLeadingPFJet",
      "jet b probability b tag for PF jet", 100, 0, 2);
   TH1D HJetProbabilityBTagNonLeadingPFJet("HJetProbabilityBTagNonLeadingPFJet",
      "jet probability b tag for PF jet", 100, 0, 2);
   TH1D HSimpleSecondaryVertexHighEffBTagNonLeadingPFJet("HSimpleSecondaryVertexHighEffBTagNonLeadingPFJet",
      "simple secondary vertex high eff. b tag for PF jet", 100, 0, 6);
   TH1D HSimpleSecondaryVertexHighPurBTagNonLeadingPFJet("HSimpleSecondaryVertexHighPurBTagNonLeadingPFJet",
      "simple secondary vertex high pur. b tag for PF jet", 100, 0, 6);
   TH1D HSoftMuonBTagNonLeadingPFJet("HSoftMuonBTagNonLeadingPFJet",
      "soft muon b tag for PF jet", 100, 0, 1);
   TH1D HSoftMuonByIP3DBTagNonLeadingPFJet("HSoftMuonByIP3DBTagNonLeadingPFJet",
      "soft muon (IP3D) b tag for PF jet", 100, 0, 100);
   TH1D HSoftMuonByPtBTagNonLeadingPFJet("HSoftMuonByPtBTagNonLeadingPFJet",
      "soft muon (PT) b tag for PF jet", 100, 0, 40);
   TH1D HSoftElectronBTagNonLeadingPFJet("HSoftElectronBTagNonLeadingPFJet",
      "soft Electron b tag for PF jet", 100, 0, 2);
   TH1D HSoftElectronByIP3DBTagNonLeadingPFJet("HSoftElectronByIP3DBTagNonLeadingPFJet",
      "soft Electron (IP3D) b tag for PF jet", 100, 0, 100);
   TH1D HSoftElectronByPtBTagNonLeadingPFJet("HSoftElectronByPtBTagNonLeadingPFJet",
      "soft Electron (PT) b tag for PF jet", 100, 0, 40);
   TH1D HTrackCountingHighPurBTagNonLeadingPFJet("HTrackCountingHighPurBTagNonLeadingPFJet",
      "track counting b tag (high pur.) for PF jet", 100, 0, 100);
   TH1D HTrackCountingHighEffBTagNonLeadingPFJet("HTrackCountingHighEffBTagNonLeadingPFJet",
      "track counting b tag (high eff.) for PF jet", 100, 0, 100);
   
   TH1D HCombinedSecondaryVertexBTagLeadingPFJet("HCombinedSecondaryVertexBTagLeadingPFJet",
      "combined secondary vertex b tag for leading PF jet", 100, 0, 1.5);
   TH1D HCombinedSecondaryVertexMVABTagLeadingPFJet("HCombinedSecondaryVertexMVABTagLeadingPFJet",
      "combined secondary vertex MVA b tag for leading PF jet", 100, 0, 1.5);
   TH1D HJetBProbabilityBTagLeadingPFJet("HJetBProbabilityBTagLeadingPFJet",
      "jet b probability b tag for leading PF jet", 100, 0, 2);
   TH1D HJetProbabilityBTagLeadingPFJet("HJetProbabilityBTagLeadingPFJet",
      "jet probability b tag for leading PF jet", 100, 0, 2);
   TH1D HSimpleSecondaryVertexHighEffBTagLeadingPFJet("HSimpleSecondaryVertexHighEffBTagLeadingPFJet",
      "simple secondary vertex high eff. b tag for leading PF jet", 100, 0, 6);
   TH1D HSimpleSecondaryVertexHighPurBTagLeadingPFJet("HSimpleSecondaryVertexHighPurBTagLeadingPFJet",
      "simple secondary vertex high pur. b tag for leading PF jet", 100, 0, 6);
   TH1D HSoftMuonBTagLeadingPFJet("HSoftMuonBTagLeadingPFJet",
      "soft muon b tag for leading PF jet", 100, 0, 1);
   TH1D HSoftMuonByIP3DBTagLeadingPFJet("HSoftMuonByIP3DBTagLeadingPFJet",
      "soft muon (IP3D) b tag for leading PF jet", 100, 0, 100);
   TH1D HSoftMuonByPtBTagLeadingPFJet("HSoftMuonByPtBTagLeadingPFJet",
      "soft muon (PT) b tag for leading PF jet", 100, 0, 40);
   TH1D HSoftElectronBTagLeadingPFJet("HSoftElectronBTagLeadingPFJet",
      "soft Electron b tag for leading PF jet", 100, 0, 2);
   TH1D HSoftElectronByIP3DBTagLeadingPFJet("HSoftElectronByIP3DBTagLeadingPFJet",
      "soft Electron (IP3D) b tag for leading PF jet", 100, 0, 100);
   TH1D HSoftElectronByPtBTagLeadingPFJet("HSoftElectronByPtBTagLeadingPFJet",
      "soft Electron (PT) b tag for leading PF jet", 100, 0, 40);
   TH1D HTrackCountingHighPurBTagLeadingPFJet("HTrackCountingHighPurBTagLeadingPFJet",
      "track counting b tag (high pur.) for leading PF jet", 100, 0, 100);
   TH1D HTrackCountingHighEffBTagLeadingPFJet("HTrackCountingHighEffBTagLeadingPFJet",
      "track counting b tag (high eff.) for leading PF jet", 100, 0, 100);
   
   TH1D HCombinedSecondaryVertexBTagSubLeadingPFJet("HCombinedSecondaryVertexBTagSubLeadingPFJet",
      "combined secondary vertex b tag for leading PF jet", 100, 0, 1.5);
   TH1D HCombinedSecondaryVertexMVABTagSubLeadingPFJet("HCombinedSecondaryVertexMVABTagSubLeadingPFJet",
      "combined secondary vertex MVA b tag for leading PF jet", 100, 0, 1.5);
   TH1D HJetBProbabilityBTagSubLeadingPFJet("HJetBProbabilityBTagSubLeadingPFJet",
      "jet b probability b tag for leading PF jet", 100, 0, 2);
   TH1D HJetProbabilityBTagSubLeadingPFJet("HJetProbabilityBTagSubLeadingPFJet",
      "jet probability b tag for leading PF jet", 100, 0, 2);
   TH1D HSimpleSecondaryVertexHighEffBTagSubLeadingPFJet("HSimpleSecondaryVertexHighEffBTagSubLeadingPFJet",
      "simple secondary vertex high eff. b tag for leading PF jet", 100, 0, 6);
   TH1D HSimpleSecondaryVertexHighPurBTagSubLeadingPFJet("HSimpleSecondaryVertexHighPurBTagSubLeadingPFJet",
      "simple secondary vertex high pur. b tag for leading PF jet", 100, 0, 6);
   TH1D HSoftMuonBTagSubLeadingPFJet("HSoftMuonBTagSubLeadingPFJet",
      "soft muon b tag for leading PF jet", 100, 0, 1);
   TH1D HSoftMuonByIP3DBTagSubLeadingPFJet("HSoftMuonByIP3DBTagSubLeadingPFJet",
      "soft muon (IP3D) b tag for leading PF jet", 100, 0, 100);
   TH1D HSoftMuonByPtBTagSubLeadingPFJet("HSoftMuonByPtBTagSubLeadingPFJet",
      "soft muon (PT) b tag for leading PF jet", 100, 0, 40);
   TH1D HSoftElectronBTagSubLeadingPFJet("HSoftElectronBTagSubLeadingPFJet",
      "soft Electron b tag for leading PF jet", 100, 0, 2);
   TH1D HSoftElectronByIP3DBTagSubLeadingPFJet("HSoftElectronByIP3DBTagSubLeadingPFJet",
      "soft Electron (IP3D) b tag for leading PF jet", 100, 0, 100);
   TH1D HSoftElectronByPtBTagSubLeadingPFJet("HSoftElectronByPtBTagSubLeadingPFJet",
      "soft Electron (PT) b tag for leading PF jet", 100, 0, 40);
   TH1D HTrackCountingHighPurBTagSubLeadingPFJet("HTrackCountingHighPurBTagSubLeadingPFJet",
      "track counting b tag (high pur.) for leading PF jet", 100, 0, 100);
   TH1D HTrackCountingHighEffBTagSubLeadingPFJet("HTrackCountingHighEffBTagSubLeadingPFJet",
      "track counting b tag (high eff.) for leading PF jet", 100, 0, 100);

   // PF jet closest to "final" generated b hadron
   TH1D HGenBHadronClosestPFJetDR("HGenBHadronClosestPFJetDR", "DR of generated b-hadron to closest PF jet",
      100, 0, 1);
   TH2D HGenBHadronClosestPFJetDRVsJetPT("HGenBHadronClosestPFJetDRVsJetPT",
      "DR of generated b-hadron to closest PF jet vs. Jet PT;DR;PT", 100, 0, 1, 100, 0, 1000);
   TH2D HGenBHadronClosestPFJetPTVsPT("HGenBHadronClosestPFJetPTVsPT",
      "PT of generated b-hadron and closest PF jet;PF Jet PT;b-hadron PT", 100, 0, 1000, 100, 0, 1000);
   TH1D HGenBHadronClosestPFJetPTRatio("HGenBHadronClosestPFJetPTRatio",
      "PT ratio of generated b-hadron and closest PF jet;PF Jet PT/B PT", 100, 0, 5);
   TH1D HGenBHadronClosestPFJetPTRatio50GeV("HGenBHadronClosestPFJetPTRatio50GeV",
      "PT ratio of generated b-hadron and closest PF jet, b hadron > 50 GeV;PF Jet PT/B PT", 100, 0, 5);
   TH1D HGenBHadronClosestPFJetPTRatio100GeV("HGenBHadronClosestPFJetPTRatio100GeV",
      "PT ratio of generated b-hadron and closest PF jet, b hadron > 100 GeV;PF Jet PT/B PT", 100, 0, 5);

   // Calo MET histograms
   TH1D HCaloMET("HCaloMET", "Calo MET distribution", 100, 0, 1000);
   TH1D HCaloMETPhi("HCaloMETPhi", "Calo MET phi distribution", 100, -3.2, 3.2);
   TH1D HCaloMETLeadingJetDPhi("HCaloMETLeadingJetDPhi", "Calo MET vs. leading jet dphi", 100, -3.2, 3.2);
   TH1D HCaloMETLeadingTwoJetsDPhi("HCaloMETLeadingTwoJetsDPhi", "Calo MET vs. leading two jets dphi",
      100, -3.2, 3.2);
   TH2D HCaloMETVsLeadingTwoJetsPT("HCaloMETVsLeadingTwoJetsPT", "Calo MET vs. leading two jets PT;MET;Jets",
      100, 0, 1000, 100, 0, 1000);
   TH1D HCaloMETWithoutLeadingTwoJets("HCaloMETWithoutLeadingTwoJets", "Calo MET, taking out leading two jets",
      100, 0, 1000);
   
   // PF MET histograms
   TH1D HPFMET("HPFMET", "PF MET distribution", 100, 0, 1000);
   TH1D HPFMETPhi("HPFMETPhi", "PF MET phi distribution", 100, -3.2, 3.2);
   TH1D HPFMETLeadingJetDPhi("HPFMETLeadingJetDPhi", "PF MET vs. leading jet dphi", 100, -3.2, 3.2);
   TH1D HPFMETLeadingTwoJetsDPhi("HPFMETLeadingTwoJetsDPhi", "PF MET vs. leading two jets dphi",
      100, -3.2, 3.2);
   TH1D HPFMETWithoutLeadingTwoJets("HPFMETWithoutLeadingTwoJets", "PF MET, taking out leading two PF jets",
      100, 0, 1000);
   TH2D HPFMETVsLeadingTwoJetsPT("HPFMETVsLeadingTwoJetsPT", "PF MET vs. leading two jets PT;MET;Jets",
      100, 0, 1000, 100, 0, 1000);
   TH2D HCaloMETVsPFMET("HCaloMETVsPFMET", "Calo MET vs. PF MET;Calo;PF", 100, 0, 1000, 100, 0, 1000);

   // MR, R from Leading jets
   TH1D HCaloJetMR("HCaloJetMR", "MR from leading two calo jets", 100, 0, 1000);
   TH1D HCaloJetMRT("HCaloJetMRT", "MRT from calo jets and MET", 100, 0, 1000);
   TH1D HCaloJetR("HCaloJetR", "R from leading two calo jets (and calo MET)", 100, 0, 1.5);
   TH2D HCaloJetMRVsR("HCaloJetMRVsR", "MR vs. R from calo system;MR;R", 100, 0, 1000, 100, 0, 1.5);
   TH1D HCaloJetMR_R01("HCaloJetMR_R01", "MR distribution, R cut 0.1", 100, 0, 1000);
   TH1D HCaloJetMR_R02("HCaloJetMR_R02", "MR distribution, R cut 0.2", 100, 0, 1000);
   TH1D HCaloJetMR_R03("HCaloJetMR_R03", "MR distribution, R cut 0.3", 100, 0, 1000);
   TH1D HCaloJetMR_R04("HCaloJetMR_R04", "MR distribution, R cut 0.4", 100, 0, 1000);
   TH1D HCaloJetMR_R05("HCaloJetMR_R05", "MR distribution, R cut 0.5", 100, 0, 1000);
   TH1D HCaloJetMR_R06("HCaloJetMR_R06", "MR distribution, R cut 0.6", 100, 0, 1000);
   TH1D HCaloJetMR_R07("HCaloJetMR_R07", "MR distribution, R cut 0.7", 100, 0, 1000);
   TH1D HCaloJetMR_R08("HCaloJetMR_R08", "MR distribution, R cut 0.8", 100, 0, 1000);
   TH1D HCaloJetMR_R09("HCaloJetMR_R09", "MR distribution, R cut 0.9", 100, 0, 1000);
   TH1D HCaloJetMR_R10("HCaloJetMR_R10", "MR distribution, R cut 1.0", 100, 0, 1000);

   TH1D HCaloJetRCutEfficiency("HCaloJetRCutEfficiency", "Calo Jet R cut efficiency", 20, 0, 20);
   for(int i = 0; i < 20; i++)
      HCaloJetRCutEfficiency.GetXaxis()->SetBinLabel(i + 1, Form("%.02f", double(i) / 20));
   HCaloJetRCutEfficiency.GetXaxis()->SetTitle("Cut position");
   HCaloJetRCutEfficiency.GetYaxis()->SetTitle("Efficiency");

   // MR, R from Leading jets
   TH1D HPFJetMR("HPFJetMR", "MR from leading two PF jets", 100, 0, 1000);
   TH1D HPFJetMRT("HPFJetMRT", "MRT from PF jets and MET", 100, 0, 1000);
   TH1D HPFJetR("HPFJetR", "R from leading two PF jets (and PF MET)", 100, 0, 1.5);
   TH2D HPFJetMRVsR("HPFJetMRVsR", "MR vs. R from PF system;MR;R", 100, 0, 1000, 100, 0, 1.5);
   TH1D HPFJetMR_R01("HPFJetMR_R01", "MR distribution, R cut 0.1", 100, 0, 1000);
   TH1D HPFJetMR_R02("HPFJetMR_R02", "MR distribution, R cut 0.2", 100, 0, 1000);
   TH1D HPFJetMR_R03("HPFJetMR_R03", "MR distribution, R cut 0.3", 100, 0, 1000);
   TH1D HPFJetMR_R04("HPFJetMR_R04", "MR distribution, R cut 0.4", 100, 0, 1000);
   TH1D HPFJetMR_R05("HPFJetMR_R05", "MR distribution, R cut 0.5", 100, 0, 1000);
   TH1D HPFJetMR_R06("HPFJetMR_R06", "MR distribution, R cut 0.6", 100, 0, 1000);
   TH1D HPFJetMR_R07("HPFJetMR_R07", "MR distribution, R cut 0.7", 100, 0, 1000);
   TH1D HPFJetMR_R08("HPFJetMR_R08", "MR distribution, R cut 0.8", 100, 0, 1000);
   TH1D HPFJetMR_R09("HPFJetMR_R09", "MR distribution, R cut 0.9", 100, 0, 1000);
   TH1D HPFJetMR_R10("HPFJetMR_R10", "MR distribution, R cut 1.0", 100, 0, 1000);
   
   TH1D HPFJetRCutEfficiency("HPFJetRCutEfficiency", "PF Jet R cut efficiency", 20, 0, 20);
   for(int i = 0; i < 20; i++)
      HPFJetRCutEfficiency.GetXaxis()->SetBinLabel(i + 1, Form("%.02f", double(i) / 20));
   HPFJetRCutEfficiency.GetXaxis()->SetTitle("Cut position");
   HPFJetRCutEfficiency.GetYaxis()->SetTitle("Efficiency");
   
   // Loop through events
   int NumberOfEvents = NTPTree->GetEntries();
   for(int iEvent = 0; iEvent < NumberOfEvents; iEvent++)
   {
      if((iEvent + 1) % 5000 == 0)
         cout << "Processing entry " << iEvent + 1 << "/" << NumberOfEvents << endl;

      NTPTree->GetEntry(iEvent);

      // PU, PV
      HNPU.Fill(M.nPU);
      for(int i = 0; i < M.nPU; i++)
         HZPositionPU.Fill(M.zpositionPU[i]);

      int BestPVIndex = -1;
      HNPV.Fill(M.nPV);
      for(int i = 0; i < M.nPV; i++)
      {
         double Dxy = sqrt(M.PVxPV[i] * M.PVxPV[i] + M.PVyPV[i] * M.PVyPV[i]);
         double SigmaDxy = sqrt(M.PVErrxPV[i] * M.PVErrxPV[i] + M.PVErryPV[i] * M.PVErryPV[i]);

         HPVZ.Fill(M.PVzPV[i]);
         HPVXY.Fill(M.PVxPV[i], M.PVyPV[i]);
         HPVXYSignificance.Fill(Dxy / SigmaDxy);
         HPVSumPT.Fill(M.SumPtPV[i]);
         HPVndof.Fill(M.ndofPV[i]);
         HPVChi2.Fill(M.chi2PV[i]);

         if(BestPVIndex < 0 || M.SumPtPV[i] > M.SumPtPV[BestPVIndex])
            BestPVIndex = i;
      }

      HNPUVsNPV.Fill(M.nPU, M.nPV);

      if(BestPVIndex >= 0)
      {
         double Dxy = sqrt(M.PVxPV[BestPVIndex] * M.PVxPV[BestPVIndex]
            + M.PVyPV[BestPVIndex] * M.PVyPV[BestPVIndex]);
         double SigmaDxy = sqrt(M.PVErrxPV[BestPVIndex] * M.PVErrxPV[BestPVIndex]
            + M.PVErryPV[BestPVIndex] * M.PVErryPV[BestPVIndex]);
         
         HBestPVZ.Fill(M.PVzPV[BestPVIndex]);
         HBestPVXY.Fill(M.PVxPV[BestPVIndex], M.PVyPV[BestPVIndex]);
         HBestPVXYSignificance.Fill(Dxy / SigmaDxy);
         HBestPVSumPT.Fill(M.SumPtPV[BestPVIndex]);
         HBestPVndof.Fill(M.ndofPV[BestPVIndex]);
         HBestPVChi2.Fill(M.chi2PV[BestPVIndex]);
      }

      // AK5Jet (a.k.a. corrected calo jet)
      int LeadingAK5JetIndex = -1;
      int SubLeadingAK5JetIndex = -1;
      multimap<double, int, greater<double> > SortAK5Jet;
      double LeadingAK5JetP[4] = {0, 0, 0, 0};
      double SubLeadingAK5JetP[4] = {0, 0, 0, 0};
      int NAK5Jet15 = 0;
      int NAK5Jet30 = 0;
      int NAK5Jet50 = 0;
      int NAK5Jet100 = 0;
      int NAK5Jet150 = 0;

      HNRawAK5Jet.Fill(M.nAK5Jet);
      for(int i = 0; i < M.nAK5Jet; i++)
      {
         if(M.etaAK5Jet[i] < 3 && M.etaAK5Jet[i] > -3)   // Jet ID: pure09, loose
         {
            if(M.nHit90AK5Jet[i] <= 1)
               continue;
            if(M.emFracAK5Jet[i] <= 0.01)
               continue;
            if(M.fHPDAK5Jet[i] > 0.98)
               continue;
         }

         double JetP[4] = {M.energyAK5Jet[i], M.pxAK5Jet[i], M.pyAK5Jet[i], M.pzAK5Jet[i]};

         HEnergyAK5Jet.Fill(M.energyAK5Jet[i]);
         HPTAK5Jet.Fill(GetPT(JetP));
         HEtaAK5Jet.Fill(M.etaAK5Jet[i]);
         HPhiAK5Jet.Fill(M.phiAK5Jet[i]);

         if(GetPT(JetP) >= 15)   NAK5Jet15 = NAK5Jet15 + 1;
         if(GetPT(JetP) >= 30)   NAK5Jet30 = NAK5Jet30 + 1;
         if(GetPT(JetP) >= 50)   NAK5Jet50 = NAK5Jet50 + 1;
         if(GetPT(JetP) >= 100)   NAK5Jet100 = NAK5Jet100 + 1;
         if(GetPT(JetP) >= 150)   NAK5Jet150 = NAK5Jet150 + 1;

         SortAK5Jet.insert(pair<double, int>(GetPT(JetP), i));
      }

      HNAK5Jet.Fill(SortAK5Jet.size());
      HNAK5Jet15.Fill(NAK5Jet15);
      HNAK5Jet30.Fill(NAK5Jet30);
      HNAK5Jet50.Fill(NAK5Jet50);
      HNAK5Jet100.Fill(NAK5Jet100);
      HNAK5Jet150.Fill(NAK5Jet150);

      if(SortAK5Jet.size() > 0)
      {
         LeadingAK5JetIndex = SortAK5Jet.begin()->second;
         LeadingAK5JetP[0] = M.energyAK5Jet[LeadingAK5JetIndex];
         LeadingAK5JetP[1] = M.pxAK5Jet[LeadingAK5JetIndex];
         LeadingAK5JetP[2] = M.pyAK5Jet[LeadingAK5JetIndex];
         LeadingAK5JetP[3] = M.pzAK5Jet[LeadingAK5JetIndex];
      }
      if(SortAK5Jet.size() > 1)
      {
         multimap<double, int>::iterator iter = SortAK5Jet.begin();
         iter++;
         SubLeadingAK5JetIndex = iter->second;
         SubLeadingAK5JetP[0] = M.energyAK5Jet[SubLeadingAK5JetIndex];
         SubLeadingAK5JetP[1] = M.pxAK5Jet[SubLeadingAK5JetIndex];
         SubLeadingAK5JetP[2] = M.pyAK5Jet[SubLeadingAK5JetIndex];
         SubLeadingAK5JetP[3] = M.pzAK5Jet[SubLeadingAK5JetIndex];
      }

      if(LeadingAK5JetIndex >= 0)
      {
         HLeadingAK5JetPT.Fill(GetPT(LeadingAK5JetP));
         HLeadingAK5JetPhi.Fill(GetPhi(LeadingAK5JetP));
         HLeadingAK5JetEta.Fill(GetEta(LeadingAK5JetP));
         
         HCombinedSecondaryVertexBTagLeadingCaloJet.Fill(M.combinedSecondaryVertexBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HCombinedSecondaryVertexMVABTagLeadingCaloJet.Fill(M.combinedSecondaryVertexMVABJetTagsAK5Jet[LeadingAK5JetIndex]);
         HJetBProbabilityBTagLeadingCaloJet.Fill(M.jetBProbabilityBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HJetProbabilityBTagLeadingCaloJet.Fill(M.jetProbabilityBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HSimpleSecondaryVertexHighEffBTagLeadingCaloJet.Fill(M.simpleSecondaryVertexHighEffBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HSimpleSecondaryVertexHighPurBTagLeadingCaloJet.Fill(M.simpleSecondaryVertexHighPurBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HSoftMuonBTagLeadingCaloJet.Fill(M.softMuonBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HSoftMuonByIP3DBTagLeadingCaloJet.Fill(M.softMuonByIP3dBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HSoftMuonByPtBTagLeadingCaloJet.Fill(M.softMuonByPtBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HSoftElectronBTagLeadingCaloJet.Fill(M.softElectronBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HSoftElectronByIP3DBTagLeadingCaloJet.Fill(M.softElectronByIP3dBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HSoftElectronByPtBTagLeadingCaloJet.Fill(M.softElectronByPtBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HTrackCountingHighPurBTagLeadingCaloJet.Fill(M.trackCountingHighPurBJetTagsAK5Jet[LeadingAK5JetIndex]);
         HTrackCountingHighEffBTagLeadingCaloJet.Fill(M.trackCountingHighEffBJetTagsAK5Jet[LeadingAK5JetIndex]);
      }
      if(SubLeadingAK5JetIndex >= 0)
      {
         HSubLeadingAK5JetPT.Fill(GetPT(SubLeadingAK5JetP));
         HSubLeadingAK5JetPhi.Fill(GetPhi(SubLeadingAK5JetP));
         HSubLeadingAK5JetEta.Fill(GetEta(SubLeadingAK5JetP));
         
         HCombinedSecondaryVertexBTagSubLeadingCaloJet.Fill(M.combinedSecondaryVertexBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HCombinedSecondaryVertexMVABTagSubLeadingCaloJet.Fill(M.combinedSecondaryVertexMVABJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HJetBProbabilityBTagSubLeadingCaloJet.Fill(M.jetBProbabilityBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HJetProbabilityBTagSubLeadingCaloJet.Fill(M.jetProbabilityBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HSimpleSecondaryVertexHighEffBTagSubLeadingCaloJet.Fill(M.simpleSecondaryVertexHighEffBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HSimpleSecondaryVertexHighPurBTagSubLeadingCaloJet.Fill(M.simpleSecondaryVertexHighPurBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HSoftMuonBTagSubLeadingCaloJet.Fill(M.softMuonBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HSoftMuonByIP3DBTagSubLeadingCaloJet.Fill(M.softMuonByIP3dBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HSoftMuonByPtBTagSubLeadingCaloJet.Fill(M.softMuonByPtBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HSoftElectronBTagSubLeadingCaloJet.Fill(M.softElectronBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HSoftElectronByIP3DBTagSubLeadingCaloJet.Fill(M.softElectronByIP3dBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HSoftElectronByPtBTagSubLeadingCaloJet.Fill(M.softElectronByPtBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HTrackCountingHighPurBTagSubLeadingCaloJet.Fill(M.trackCountingHighPurBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
         HTrackCountingHighEffBTagSubLeadingCaloJet.Fill(M.trackCountingHighEffBJetTagsAK5Jet[SubLeadingAK5JetIndex]);
      }
      if(LeadingAK5JetIndex >= 0 && SubLeadingAK5JetIndex >= 0)
      {
         HLeadingTwoAK5JetsPTVsPT.Fill(GetPT(LeadingAK5JetP), GetPT(SubLeadingAK5JetP));
         HLeadingTwoAK5JetsDPhi.Fill(GetDPhi(LeadingAK5JetP, SubLeadingAK5JetP));
         HLeadingTwoAK5JetsDR.Fill(GetDR(LeadingAK5JetP, SubLeadingAK5JetP));
      }

      for(multimap<double, int>::iterator iter = SortAK5Jet.begin(); iter != SortAK5Jet.end(); iter++)
      {
         // loop over non-leading Calo jets
         if(iter->second == LeadingAK5JetIndex)
            continue;
         if(iter->second == SubLeadingAK5JetIndex)
            continue;

         int i = iter->second;
   
         HCombinedSecondaryVertexBTagNonLeadingCaloJet.Fill(M.combinedSecondaryVertexBJetTagsAK5PFJet[i]);
         HCombinedSecondaryVertexMVABTagNonLeadingCaloJet.Fill(M.combinedSecondaryVertexMVABJetTagsAK5PFJet[i]);
         HJetBProbabilityBTagNonLeadingCaloJet.Fill(M.jetBProbabilityBJetTagsAK5PFJet[i]);
         HJetProbabilityBTagNonLeadingCaloJet.Fill(M.jetProbabilityBJetTagsAK5PFJet[i]);
         HSimpleSecondaryVertexHighEffBTagNonLeadingCaloJet.Fill(M.simpleSecondaryVertexHighEffBJetTagsAK5PFJet[i]);
         HSimpleSecondaryVertexHighPurBTagNonLeadingCaloJet.Fill(M.simpleSecondaryVertexHighPurBJetTagsAK5PFJet[i]);
         HSoftMuonBTagNonLeadingCaloJet.Fill(M.softMuonBJetTagsAK5PFJet[i]);
         HSoftMuonByIP3DBTagNonLeadingCaloJet.Fill(M.softMuonByIP3dBJetTagsAK5PFJet[i]);
         HSoftMuonByPtBTagNonLeadingCaloJet.Fill(M.softMuonByPtBJetTagsAK5PFJet[i]);
         HSoftElectronBTagNonLeadingCaloJet.Fill(M.softElectronBJetTagsAK5PFJet[i]);
         HSoftElectronByIP3DBTagNonLeadingCaloJet.Fill(M.softElectronByIP3dBJetTagsAK5PFJet[i]);
         HSoftElectronByPtBTagNonLeadingCaloJet.Fill(M.softElectronByPtBJetTagsAK5PFJet[i]);
         HTrackCountingHighPurBTagNonLeadingCaloJet.Fill(M.trackCountingHighPurBJetTagsAK5PFJet[i]);
         HTrackCountingHighEffBTagNonLeadingCaloJet.Fill(M.trackCountingHighEffBJetTagsAK5PFJet[i]);
      }
      
      // PF Jets
      int LeadingPFJetIndex = -1;
      int SubLeadingPFJetIndex = -1;
      multimap<double, int, greater<double> > SortPFJet;
      double LeadingPFJetP[4] = {0, 0, 0, 0};
      double SubLeadingPFJetP[4] = {0, 0, 0, 0};
      int NPFJet15 = 0;
      int NPFJet30 = 0;
      int NPFJet50 = 0;
      int NPFJet100 = 0;
      int NPFJet150 = 0;

      HNRawPFJet.Fill(M.nAK5PFJet);
      for(int i = 0; i < M.nAK5PFJet; i++)
      {
         // apply loose jet ID
         if(M.neutralHadronEnergyAK5PFJet[i] / M.energyAK5PFJet[i] >= 0.99)
            continue;
         if(M.neutralEmEnergyAK5PFJet[i] / M.energyAK5PFJet[i] >= 0.99)
            continue;
         if(M.chargedHadronMultiplicityAK5PFJet[i]
            + M.neutralHadronMultiplicityAK5PFJet[i]
            + M.photonMultiplicityAK5PFJet[i]
            + M.electronMultiplicityAK5PFJet[i]
            + M.muonMultiplicityAK5PFJet[i]
            + M.HFHadronMultiplicityAK5PFJet[i]
            + M.HFEMMultiplicityAK5PFJet[i] <= 1)
            continue;
         if(M.etaAK5PFJet[i] < 2.4 && M.etaAK5PFJet[i] > -2.4)
         {
            if(M.chargedHadronEnergyAK5PFJet[i] / M.energyAK5PFJet[i] <= 0)
               continue;
            if(M.chargedHadronMultiplicityAK5PFJet[i] + M.electronMultiplicityAK5PFJet[i]
               + M.muonMultiplicityAK5PFJet[i] <= 0)
               continue;
            if(M.chargedEmEnergyAK5PFJet[i] / M.energyAK5PFJet[i] >= 0.99)
               continue;
         }

         double JetP[4] = {M.energyAK5PFJet[i], M.pxAK5PFJet[i], M.pyAK5PFJet[i], M.pzAK5PFJet[i]};

         HEnergyPFJet.Fill(M.energyAK5PFJet[i]);
         HPTPFJet.Fill(GetPT(JetP));
         HEtaPFJet.Fill(M.etaAK5PFJet[i]);
         HPhiPFJet.Fill(M.phiAK5PFJet[i]);
         
         if(GetPT(JetP) >= 15)   NPFJet15 = NPFJet15 + 1;
         if(GetPT(JetP) >= 30)   NPFJet30 = NPFJet30 + 1;
         if(GetPT(JetP) >= 50)   NPFJet50 = NPFJet50 + 1;
         if(GetPT(JetP) >= 100)   NPFJet100 = NPFJet100 + 1;
         if(GetPT(JetP) >= 150)   NPFJet150 = NPFJet150 + 1;

         SortPFJet.insert(pair<double, int>(GetPT(JetP), i));
      }
      
      HNPFJet.Fill(SortPFJet.size());
      HNPFJet15.Fill(NPFJet15);
      HNPFJet30.Fill(NPFJet30);
      HNPFJet50.Fill(NPFJet50);
      HNPFJet100.Fill(NPFJet100);
      HNPFJet150.Fill(NPFJet150);

      if(SortPFJet.size() > 0)
      {
         LeadingPFJetIndex = SortPFJet.begin()->second;
         LeadingPFJetP[0] = M.energyAK5PFJet[LeadingPFJetIndex];
         LeadingPFJetP[1] = M.pxAK5PFJet[LeadingPFJetIndex];
         LeadingPFJetP[2] = M.pyAK5PFJet[LeadingPFJetIndex];
         LeadingPFJetP[3] = M.pzAK5PFJet[LeadingPFJetIndex];
      }
      if(SortPFJet.size() > 1)
      {
         multimap<double, int>::iterator iter = SortPFJet.begin();
         iter++;
         SubLeadingPFJetIndex = iter->second;
         SubLeadingPFJetP[0] = M.energyAK5PFJet[SubLeadingPFJetIndex];
         SubLeadingPFJetP[1] = M.pxAK5PFJet[SubLeadingPFJetIndex];
         SubLeadingPFJetP[2] = M.pyAK5PFJet[SubLeadingPFJetIndex];
         SubLeadingPFJetP[3] = M.pzAK5PFJet[SubLeadingPFJetIndex];
      }

      if(LeadingPFJetIndex >= 0)
      {
         HLeadingPFJetPT.Fill(GetPT(LeadingPFJetP));
         HLeadingPFJetPhi.Fill(GetPhi(LeadingPFJetP));
         HLeadingPFJetEta.Fill(GetEta(LeadingPFJetP));
         
         HCombinedSecondaryVertexBTagLeadingPFJet.Fill(M.combinedSecondaryVertexBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HCombinedSecondaryVertexMVABTagLeadingPFJet.Fill(M.combinedSecondaryVertexMVABJetTagsAK5PFJet[LeadingPFJetIndex]);
         HJetBProbabilityBTagLeadingPFJet.Fill(M.jetBProbabilityBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HJetProbabilityBTagLeadingPFJet.Fill(M.jetProbabilityBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HSimpleSecondaryVertexHighEffBTagLeadingPFJet.Fill(M.simpleSecondaryVertexHighEffBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HSimpleSecondaryVertexHighPurBTagLeadingPFJet.Fill(M.simpleSecondaryVertexHighPurBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HSoftMuonBTagLeadingPFJet.Fill(M.softMuonBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HSoftMuonByIP3DBTagLeadingPFJet.Fill(M.softMuonByIP3dBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HSoftMuonByPtBTagLeadingPFJet.Fill(M.softMuonByPtBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HSoftElectronBTagLeadingPFJet.Fill(M.softElectronBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HSoftElectronByIP3DBTagLeadingPFJet.Fill(M.softElectronByIP3dBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HSoftElectronByPtBTagLeadingPFJet.Fill(M.softElectronByPtBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HTrackCountingHighPurBTagLeadingPFJet.Fill(M.trackCountingHighPurBJetTagsAK5PFJet[LeadingPFJetIndex]);
         HTrackCountingHighEffBTagLeadingPFJet.Fill(M.trackCountingHighEffBJetTagsAK5PFJet[LeadingPFJetIndex]);
      }
      if(SubLeadingPFJetIndex >= 0)
      {
         HSubLeadingPFJetPT.Fill(GetPT(SubLeadingPFJetP));
         HSubLeadingPFJetPhi.Fill(GetPhi(SubLeadingPFJetP));
         HSubLeadingPFJetEta.Fill(GetEta(SubLeadingPFJetP));
         
         HCombinedSecondaryVertexBTagSubLeadingPFJet.Fill(M.combinedSecondaryVertexBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HCombinedSecondaryVertexMVABTagSubLeadingPFJet.Fill(M.combinedSecondaryVertexMVABJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HJetBProbabilityBTagSubLeadingPFJet.Fill(M.jetBProbabilityBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HJetProbabilityBTagSubLeadingPFJet.Fill(M.jetProbabilityBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HSimpleSecondaryVertexHighEffBTagSubLeadingPFJet.Fill(M.simpleSecondaryVertexHighEffBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HSimpleSecondaryVertexHighPurBTagSubLeadingPFJet.Fill(M.simpleSecondaryVertexHighPurBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HSoftMuonBTagSubLeadingPFJet.Fill(M.softMuonBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HSoftMuonByIP3DBTagSubLeadingPFJet.Fill(M.softMuonByIP3dBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HSoftMuonByPtBTagSubLeadingPFJet.Fill(M.softMuonByPtBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HSoftElectronBTagSubLeadingPFJet.Fill(M.softElectronBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HSoftElectronByIP3DBTagSubLeadingPFJet.Fill(M.softElectronByIP3dBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HSoftElectronByPtBTagSubLeadingPFJet.Fill(M.softElectronByPtBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HTrackCountingHighPurBTagSubLeadingPFJet.Fill(M.trackCountingHighPurBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
         HTrackCountingHighEffBTagSubLeadingPFJet.Fill(M.trackCountingHighEffBJetTagsAK5PFJet[SubLeadingPFJetIndex]);
      }
      if(LeadingPFJetIndex >= 0 && SubLeadingPFJetIndex >= 0)
      {
         HLeadingTwoPFJetsPTVsPT.Fill(GetPT(LeadingPFJetP), GetPT(SubLeadingPFJetP));
         HLeadingTwoPFJetsDPhi.Fill(GetDPhi(LeadingPFJetP, SubLeadingPFJetP));
         HLeadingTwoPFJetsDR.Fill(GetDR(LeadingPFJetP, SubLeadingPFJetP));
      }

      for(multimap<double, int>::iterator iter = SortPFJet.begin(); iter != SortPFJet.end(); iter++)
      {
         // loop over non-leading PF jets
         if(iter->second == LeadingPFJetIndex)
            continue;
         if(iter->second == SubLeadingPFJetIndex)
            continue;

         int i = iter->second;
   
         HCombinedSecondaryVertexBTagNonLeadingPFJet.Fill(M.combinedSecondaryVertexBJetTagsAK5PFJet[i]);
         HCombinedSecondaryVertexMVABTagNonLeadingPFJet.Fill(M.combinedSecondaryVertexMVABJetTagsAK5PFJet[i]);
         HJetBProbabilityBTagNonLeadingPFJet.Fill(M.jetBProbabilityBJetTagsAK5PFJet[i]);
         HJetProbabilityBTagNonLeadingPFJet.Fill(M.jetProbabilityBJetTagsAK5PFJet[i]);
         HSimpleSecondaryVertexHighEffBTagNonLeadingPFJet.Fill(M.simpleSecondaryVertexHighEffBJetTagsAK5PFJet[i]);
         HSimpleSecondaryVertexHighPurBTagNonLeadingPFJet.Fill(M.simpleSecondaryVertexHighPurBJetTagsAK5PFJet[i]);
         HSoftMuonBTagNonLeadingPFJet.Fill(M.softMuonBJetTagsAK5PFJet[i]);
         HSoftMuonByIP3DBTagNonLeadingPFJet.Fill(M.softMuonByIP3dBJetTagsAK5PFJet[i]);
         HSoftMuonByPtBTagNonLeadingPFJet.Fill(M.softMuonByPtBJetTagsAK5PFJet[i]);
         HSoftElectronBTagNonLeadingPFJet.Fill(M.softElectronBJetTagsAK5PFJet[i]);
         HSoftElectronByIP3DBTagNonLeadingPFJet.Fill(M.softElectronByIP3dBJetTagsAK5PFJet[i]);
         HSoftElectronByPtBTagNonLeadingPFJet.Fill(M.softElectronByPtBJetTagsAK5PFJet[i]);
         HTrackCountingHighPurBTagNonLeadingPFJet.Fill(M.trackCountingHighPurBJetTagsAK5PFJet[i]);
         HTrackCountingHighEffBTagNonLeadingPFJet.Fill(M.trackCountingHighEffBJetTagsAK5PFJet[i]);
      }

      // Calo MET
      double CaloMETP[4] = {M.energyMet[0], M.pxMet[0], M.pyMet[0], M.pzMet[0]};
      HCaloMET.Fill(GetPT(CaloMETP));
      HCaloMETPhi.Fill(GetPhi(CaloMETP));
      if(LeadingAK5JetIndex >= 0)
         HCaloMETLeadingJetDPhi.Fill(GetDPhi(CaloMETP, LeadingAK5JetP));
      if(LeadingAK5JetIndex >= 0 && SubLeadingAK5JetIndex >= 0)
      {
         double LeadingTwoJetsP[4] = {0, 0, 0, 0};
         LeadingTwoJetsP[0] = LeadingAK5JetP[0] + SubLeadingAK5JetP[0];
         LeadingTwoJetsP[1] = LeadingAK5JetP[1] + SubLeadingAK5JetP[1];
         LeadingTwoJetsP[2] = LeadingAK5JetP[2] + SubLeadingAK5JetP[2];
         LeadingTwoJetsP[3] = LeadingAK5JetP[3] + SubLeadingAK5JetP[3];
         HCaloMETLeadingTwoJetsDPhi.Fill(GetDPhi(CaloMETP, LeadingTwoJetsP));
         HCaloMETVsLeadingTwoJetsPT.Fill(GetPT(CaloMETP), GetPT(LeadingTwoJetsP));

         double CaloMETWithoutLeadingTwoJetsP[4] = {0, 0, 0, 0};
         CaloMETWithoutLeadingTwoJetsP[0] = CaloMETP[0] + LeadingTwoJetsP[0];
         CaloMETWithoutLeadingTwoJetsP[1] = CaloMETP[1] + LeadingTwoJetsP[1];
         CaloMETWithoutLeadingTwoJetsP[2] = CaloMETP[2] + LeadingTwoJetsP[2];
         CaloMETWithoutLeadingTwoJetsP[3] = CaloMETP[3] + LeadingTwoJetsP[3];
         HCaloMETWithoutLeadingTwoJets.Fill(GetPT(CaloMETWithoutLeadingTwoJetsP));
      }

      // PF MET
      double PFMETP[4] = {M.energyPFMet[0], M.pxPFMet[0], M.pyPFMet[0], M.pzPFMet[0]};
      HPFMET.Fill(GetPT(PFMETP));
      HPFMETPhi.Fill(GetPhi(PFMETP));
      if(LeadingPFJetIndex >= 0)
         HPFMETLeadingJetDPhi.Fill(GetDPhi(PFMETP, LeadingPFJetP));
      if(LeadingPFJetIndex >= 0 && SubLeadingPFJetIndex >= 0)
      {
         double LeadingTwoJetsP[4] = {0, 0, 0, 0};
         LeadingTwoJetsP[0] = LeadingPFJetP[0] + SubLeadingPFJetP[0];
         LeadingTwoJetsP[1] = LeadingPFJetP[1] + SubLeadingPFJetP[1];
         LeadingTwoJetsP[2] = LeadingPFJetP[2] + SubLeadingPFJetP[2];
         LeadingTwoJetsP[3] = LeadingPFJetP[3] + SubLeadingPFJetP[3];
         HPFMETLeadingTwoJetsDPhi.Fill(GetDPhi(PFMETP, LeadingTwoJetsP));
         HPFMETVsLeadingTwoJetsPT.Fill(GetPT(PFMETP), GetPT(LeadingTwoJetsP));
         
         double PFMETWithoutLeadingTwoJetsP[4] = {0, 0, 0, 0};
         PFMETWithoutLeadingTwoJetsP[0] = PFMETP[0] + LeadingTwoJetsP[0];
         PFMETWithoutLeadingTwoJetsP[1] = PFMETP[1] + LeadingTwoJetsP[1];
         PFMETWithoutLeadingTwoJetsP[2] = PFMETP[2] + LeadingTwoJetsP[2];
         PFMETWithoutLeadingTwoJetsP[3] = PFMETP[3] + LeadingTwoJetsP[3];
         HPFMETWithoutLeadingTwoJets.Fill(GetPT(PFMETWithoutLeadingTwoJetsP));
      }
      HCaloMETVsPFMET.Fill(GetPT(CaloMETP), GetPT(PFMETP));

      // Calo MR and R
      if(LeadingAK5JetIndex >= 0 && SubLeadingAK5JetIndex >= 0)
      {
         double MR = GetMR(LeadingAK5JetP, SubLeadingAK5JetP);
         double MRT = GetMRT(LeadingAK5JetP, SubLeadingAK5JetP, CaloMETP);
         double R = GetR(LeadingAK5JetP, SubLeadingAK5JetP, CaloMETP);

         HCaloJetMR.Fill(MR);
         HCaloJetMRT.Fill(MRT);
         HCaloJetR.Fill(R);
         HCaloJetMRVsR.Fill(MR, R);

         if(R > 0.1)   HCaloJetMR_R01.Fill(MR);
         if(R > 0.2)   HCaloJetMR_R02.Fill(MR);
         if(R > 0.3)   HCaloJetMR_R03.Fill(MR);
         if(R > 0.4)   HCaloJetMR_R04.Fill(MR);
         if(R > 0.5)   HCaloJetMR_R05.Fill(MR);
         if(R > 0.6)   HCaloJetMR_R06.Fill(MR);
         if(R > 0.7)   HCaloJetMR_R07.Fill(MR);
         if(R > 0.8)   HCaloJetMR_R08.Fill(MR);
         if(R > 0.9)   HCaloJetMR_R09.Fill(MR);
         if(R > 1.0)   HCaloJetMR_R10.Fill(MR);

         int BinCount = HCaloJetRCutEfficiency.GetNbinsX();
         for(int i = 0; i < BinCount; i++)
            if(R > double(i) / BinCount)
               HCaloJetRCutEfficiency.Fill(i);
      }
      
      // PF MR and R
      if(LeadingAK5JetIndex >= 0 && SubLeadingAK5JetIndex >= 0)
      {
         double MR = GetMR(LeadingPFJetP, SubLeadingPFJetP);
         double MRT = GetMRT(LeadingPFJetP, SubLeadingPFJetP, PFMETP);
         double R = GetR(LeadingPFJetP, SubLeadingPFJetP, PFMETP);

         HPFJetMR.Fill(MR);
         HPFJetMRT.Fill(MRT);
         HPFJetR.Fill(R);
         HPFJetMRVsR.Fill(MR, R);

         if(R > 0.1)   HPFJetMR_R01.Fill(MR);
         if(R > 0.2)   HPFJetMR_R02.Fill(MR);
         if(R > 0.3)   HPFJetMR_R03.Fill(MR);
         if(R > 0.4)   HPFJetMR_R04.Fill(MR);
         if(R > 0.5)   HPFJetMR_R05.Fill(MR);
         if(R > 0.6)   HPFJetMR_R06.Fill(MR);
         if(R > 0.7)   HPFJetMR_R07.Fill(MR);
         if(R > 0.8)   HPFJetMR_R08.Fill(MR);
         if(R > 0.9)   HPFJetMR_R09.Fill(MR);
         if(R > 1.0)   HPFJetMR_R10.Fill(MR);
         
         int BinCount = HPFJetRCutEfficiency.GetNbinsX();
         for(int i = 0; i < 20; i++)
            if(R > double(i) / 20)
               HPFJetRCutEfficiency.Fill(i);
      }

      // Trace b-mesons from MC information
      int BFromLQ = max(FindChildIndex(M, 5, 42), FindChildIndex(M, -5, 42));
      int BFromLQbar = max(FindChildIndex(M, 5, -42), FindChildIndex(M, -5, -42));
      int FinalBHadronFromLQ = TraceBHadron(M, BFromLQ);
      int FinalBHadronFromLQbar = TraceBHadron(M, BFromLQbar);
      int ClosestPFJetToBHadronFromLQ = -1;
      int ClosestPFJetToBHadronFromLQbar = -1;
      double FinalBFromLQP[4] = {0, 0, 0, 0};
      double FinalBFromLQbarP[4] = {0, 0, 0, 0};
      double ClosestPFJetToBHadronFromLQP[4] = {0, 0, 0, 0};
      double ClosestPFJetToBHadronFromLQbarP[4] = {0, 0, 0, 0};

      if(M.etaMc[FinalBHadronFromLQ] > 2.4 || M.etaMc[FinalBHadronFromLQ] < -2.4)
         FinalBHadronFromLQ = -1;
      if(M.etaMc[FinalBHadronFromLQbar] > 2.4 || M.etaMc[FinalBHadronFromLQbar] < -2.4)
         FinalBHadronFromLQbar = -1;

      if(FinalBHadronFromLQ >= 0)
      {
         double EtaFinalBHadron = M.etaMc[FinalBHadronFromLQ];
         double PhiFinalBHadron = M.phiMc[FinalBHadronFromLQ];
         ClosestPFJetToBHadronFromLQ = FindClosestJet(M.etaAK5PFJet, M.phiAK5PFJet, M.nAK5PFJet,
            EtaFinalBHadron, PhiFinalBHadron);

         FinalBFromLQP[0] = M.energyMc[FinalBHadronFromLQ];
         FinalBFromLQP[1] = M.pMc[FinalBHadronFromLQ] / cosh(M.etaMc[FinalBHadronFromLQ])
            * cos(M.phiMc[FinalBHadronFromLQ]);
         FinalBFromLQP[2] = M.pMc[FinalBHadronFromLQ] / cosh(M.etaMc[FinalBHadronFromLQ])
            * sin(M.phiMc[FinalBHadronFromLQ]);
         FinalBFromLQP[3] = M.pMc[FinalBHadronFromLQ] * tanh(M.etaMc[FinalBHadronFromLQ]);

         if(ClosestPFJetToBHadronFromLQ >= 0)
         {
            ClosestPFJetToBHadronFromLQP[0] = M.energyAK5PFJet[ClosestPFJetToBHadronFromLQ];
            ClosestPFJetToBHadronFromLQP[1] = M.pxAK5PFJet[ClosestPFJetToBHadronFromLQ];
            ClosestPFJetToBHadronFromLQP[2] = M.pyAK5PFJet[ClosestPFJetToBHadronFromLQ];
            ClosestPFJetToBHadronFromLQP[3] = M.pzAK5PFJet[ClosestPFJetToBHadronFromLQ];
         }
      }
      if(FinalBHadronFromLQbar >= 0)
      {
         double EtaFinalBHadron = M.etaMc[FinalBHadronFromLQbar];
         double PhiFinalBHadron = M.phiMc[FinalBHadronFromLQbar];
         ClosestPFJetToBHadronFromLQbar = FindClosestJet(M.etaAK5PFJet, M.phiAK5PFJet, M.nAK5PFJet,
            EtaFinalBHadron, PhiFinalBHadron);
         
         FinalBFromLQbarP[0] = M.energyMc[FinalBHadronFromLQbar];
         FinalBFromLQbarP[1] = M.pMc[FinalBHadronFromLQbar] / cosh(M.etaMc[FinalBHadronFromLQbar])
            * cos(M.phiMc[FinalBHadronFromLQbar]);
         FinalBFromLQbarP[2] = M.pMc[FinalBHadronFromLQbar] / cosh(M.etaMc[FinalBHadronFromLQbar])
            * sin(M.phiMc[FinalBHadronFromLQbar]);
         FinalBFromLQbarP[3] = M.pMc[FinalBHadronFromLQbar] * tanh(M.etaMc[FinalBHadronFromLQbar]);
         
         if(ClosestPFJetToBHadronFromLQbar >= 0)
         {
            ClosestPFJetToBHadronFromLQbarP[0] = M.energyAK5PFJet[ClosestPFJetToBHadronFromLQbar];
            ClosestPFJetToBHadronFromLQbarP[1] = M.pxAK5PFJet[ClosestPFJetToBHadronFromLQbar];
            ClosestPFJetToBHadronFromLQbarP[2] = M.pyAK5PFJet[ClosestPFJetToBHadronFromLQbar];
            ClosestPFJetToBHadronFromLQbarP[3] = M.pzAK5PFJet[ClosestPFJetToBHadronFromLQbar];
         }
      }

      if(ClosestPFJetToBHadronFromLQ >= 0)
      {
         double DR = GetDR(ClosestPFJetToBHadronFromLQP, FinalBFromLQP);
         double JetPT = GetPT(ClosestPFJetToBHadronFromLQP);
         double BPT = GetPT(FinalBFromLQP);
         
         HGenBHadronClosestPFJetDR.Fill(DR);
         HGenBHadronClosestPFJetDRVsJetPT.Fill(DR, JetPT);
         HGenBHadronClosestPFJetPTVsPT.Fill(JetPT, BPT);

         HGenBHadronClosestPFJetPTRatio.Fill(JetPT / BPT);
         if(BPT > 50)
            HGenBHadronClosestPFJetPTRatio50GeV.Fill(JetPT / BPT);
         if(BPT > 100)
            HGenBHadronClosestPFJetPTRatio100GeV.Fill(JetPT / BPT);

         /*
         if(GetDR(ClosestPFJetToBHadronFromLQP, BFromLQP) > 4)
         {
            cout << ClosestPFJetToBHadronFromLQP[0] << " "
               << ClosestPFJetToBHadronFromLQP[1] << " "
               << ClosestPFJetToBHadronFromLQP[2] << " "
               << ClosestPFJetToBHadronFromLQP[3] << endl;
            cout << BFromLQP[0] << " " << BFromLQP[1] << " " << BFromLQP[2] << " " << BFromLQP[3] << endl;
            cout << GetDR(ClosestPFJetToBHadronFromLQP, BFromLQP) << endl;
         }
         */
      }
      if(ClosestPFJetToBHadronFromLQbar >= 0)
      {
         double DR = GetDR(ClosestPFJetToBHadronFromLQbarP, FinalBFromLQbarP);
         double JetPT = GetPT(ClosestPFJetToBHadronFromLQbarP);
         double BPT = GetPT(FinalBFromLQbarP);

         HGenBHadronClosestPFJetDR.Fill(DR);
         HGenBHadronClosestPFJetDRVsJetPT.Fill(DR, JetPT);
         HGenBHadronClosestPFJetPTVsPT.Fill(JetPT, BPT);

         HGenBHadronClosestPFJetPTRatio.Fill(JetPT / BPT);
         if(BPT > 50)
            HGenBHadronClosestPFJetPTRatio50GeV.Fill(JetPT / BPT);
         if(BPT > 100)
            HGenBHadronClosestPFJetPTRatio100GeV.Fill(JetPT / BPT);
      }
   }

   // normalize effiency plots
   double CaloJetRCutEffiencyNormalization = HCaloJetRCutEfficiency.GetBinContent(1);
   for(int i = 0; i < HCaloJetRCutEfficiency.GetNbinsX(); i++)
      HCaloJetRCutEfficiency.SetBinContent(i + 1,
         HCaloJetRCutEfficiency.GetBinContent(i + 1) / CaloJetRCutEffiencyNormalization);
   
   double PFJetRCutEffiencyNormalization = HPFJetRCutEfficiency.GetBinContent(1);
   for(int i = 0; i < HPFJetRCutEfficiency.GetNbinsX(); i++)
      HPFJetRCutEfficiency.SetBinContent(i + 1,
         HPFJetRCutEfficiency.GetBinContent(i + 1) / PFJetRCutEffiencyNormalization);

   // Add histograms to output
   PsFile.AddTextPage("Pileups, Primary vertices");
   PsFile.AddPlot(HNPU, "text0 hist", true);
   PsFile.AddPlot(HZPositionPU, "", false);
   PsFile.AddPlot(HNPV, "text0 hist", true);
   PsFile.AddPlot(HPVZ, "", true);
   PsFile.AddPlot(HPVXY, "colz", false, true);
   PsFile.AddPlot(HPVXYSignificance, "", true);
   PsFile.AddPlot(HPVSumPT, "", true);
   PsFile.AddPlot(HPVndof, "", true);
   PsFile.AddPlot(HPVChi2, "", true);
   PsFile.AddPlot(HNPUVsNPV, "colz text00", false);
   PsFile.AddPlot(HBestPVZ, "", true);
   PsFile.AddPlot(HBestPVXY, "colz", false, true);
   PsFile.AddPlot(HBestPVXYSignificance, "", false);
   PsFile.AddPlot(HBestPVSumPT, "", true);
   PsFile.AddPlot(HBestPVndof, "", true);
   PsFile.AddPlot(HBestPVChi2, "", true);

   PsFile.AddTextPage("Calo jet plots");
   PsFile.AddPlot(HNRawAK5Jet, "text0 hist", true);
   PsFile.AddPlot(HNAK5Jet, "text0 hist", true);
   PsFile.AddPlot(HNAK5Jet15, "text0 hist", true);
   PsFile.AddPlot(HNAK5Jet30, "text0 hist", true);
   PsFile.AddPlot(HNAK5Jet50, "text0 hist", true);
   PsFile.AddPlot(HNAK5Jet100, "text0 hist", true);
   PsFile.AddPlot(HNAK5Jet150, "text0 hist", true);
   PsFile.AddPlot(HEnergyAK5Jet, "", true);
   PsFile.AddPlot(HPTAK5Jet, "", true);
   PsFile.AddPlot(HEtaAK5Jet, "", false);
   PsFile.AddPlot(HPhiAK5Jet, "", false);
   PsFile.AddPlot(HLeadingAK5JetPT, "", true);
   PsFile.AddPlot(HLeadingAK5JetEta, "", false);
   PsFile.AddPlot(HLeadingAK5JetPhi, "", false);
   PsFile.AddPlot(HSubLeadingAK5JetPT, "", true);
   PsFile.AddPlot(HSubLeadingAK5JetEta, "", false);
   PsFile.AddPlot(HSubLeadingAK5JetPhi, "", false);
   PsFile.AddPlot(HLeadingTwoAK5JetsPTVsPT, "colz", false);
   PsFile.AddPlot(HLeadingTwoAK5JetsDPhi, "", false);
   PsFile.AddPlot(HLeadingTwoAK5JetsDR, "", false);
   
   PsFile.AddTextPage("Calo jet b-tagging plots");
   
   vector<string> CaloJetBTaggingExplanation;
   CaloJetBTaggingExplanation.push_back("Leading and sub-leading are the two largest jets in pt");
   CaloJetBTaggingExplanation.push_back("All the rest are included in the \"non-leading\" category");
   CaloJetBTaggingExplanation.push_back("");
   CaloJetBTaggingExplanation.push_back("Plots in this section are normalized to the same area");
   CaloJetBTaggingExplanation.push_back("      for ease of comparison");
   PsFile.AddTextPage(CaloJetBTaggingExplanation);

   AddThreeHistogramOverlayPlot(PsFile,
      &HCombinedSecondaryVertexBTagNonLeadingCaloJet,
      &HCombinedSecondaryVertexBTagLeadingCaloJet,
      &HCombinedSecondaryVertexBTagSubLeadingCaloJet,
      "combined secondary vertex b tag (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HCombinedSecondaryVertexMVABTagNonLeadingCaloJet,
      &HCombinedSecondaryVertexMVABTagLeadingCaloJet,
      &HCombinedSecondaryVertexMVABTagSubLeadingCaloJet,
      "combined secondary vertex MVA b tag (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HJetBProbabilityBTagNonLeadingCaloJet,
      &HJetBProbabilityBTagLeadingCaloJet,
      &HJetBProbabilityBTagSubLeadingCaloJet,
      "jet b probability b tag (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HJetProbabilityBTagNonLeadingCaloJet,
      &HJetProbabilityBTagLeadingCaloJet,
      &HJetProbabilityBTagSubLeadingCaloJet,
      "jet probability b tag (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSimpleSecondaryVertexHighEffBTagNonLeadingCaloJet,
      &HSimpleSecondaryVertexHighEffBTagLeadingCaloJet,
      &HSimpleSecondaryVertexHighEffBTagSubLeadingCaloJet,
      "simple secondary vertex b tag (high eff.) (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSimpleSecondaryVertexHighPurBTagNonLeadingCaloJet,
      &HSimpleSecondaryVertexHighPurBTagLeadingCaloJet,
      &HSimpleSecondaryVertexHighPurBTagSubLeadingCaloJet,
      "simple secondary vertex b tag (high pur.) (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftMuonBTagNonLeadingCaloJet,
      &HSoftMuonBTagLeadingCaloJet,
      &HSoftMuonBTagSubLeadingCaloJet,
      "soft muon b tag (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftMuonByIP3DBTagNonLeadingCaloJet,
      &HSoftMuonByIP3DBTagLeadingCaloJet,
      &HSoftMuonByIP3DBTagSubLeadingCaloJet,
      "soft muon b tag (by IP3D) (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftMuonByPtBTagNonLeadingCaloJet,
      &HSoftMuonByPtBTagLeadingCaloJet,
      &HSoftMuonByPtBTagSubLeadingCaloJet,
      "soft muon b tag (by PT) (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftElectronBTagNonLeadingCaloJet,
      &HSoftElectronBTagLeadingCaloJet,
      &HSoftElectronBTagSubLeadingCaloJet,
      "soft electron b tag (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftElectronByIP3DBTagNonLeadingCaloJet,
      &HSoftElectronByIP3DBTagLeadingCaloJet,
      &HSoftElectronByIP3DBTagSubLeadingCaloJet,
      "soft electron b tag (by IP3D) (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftElectronByPtBTagNonLeadingCaloJet,
      &HSoftElectronByPtBTagLeadingCaloJet,
      &HSoftElectronByPtBTagSubLeadingCaloJet,
      "soft electron b tag (by PT) (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HTrackCountingHighPurBTagNonLeadingCaloJet,
      &HTrackCountingHighPurBTagLeadingCaloJet,
      &HTrackCountingHighPurBTagSubLeadingCaloJet,
      "track counting b tag (high pur.) (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HTrackCountingHighEffBTagNonLeadingCaloJet,
      &HTrackCountingHighEffBTagLeadingCaloJet,
      &HTrackCountingHighEffBTagSubLeadingCaloJet,
      "track counting b tag (high eff.) (Calo Jet)", "non-leading", "leading", "sub-leading", "", true);

   PsFile.AddTextPage("PF jet plots");
   PsFile.AddPlot(HNRawPFJet, "text0 hist", true);
   PsFile.AddPlot(HNPFJet, "text0 hist", true);
   PsFile.AddPlot(HNPFJet15, "text0 hist", true);
   PsFile.AddPlot(HNPFJet30, "text0 hist", true);
   PsFile.AddPlot(HNPFJet50, "text0 hist", true);
   PsFile.AddPlot(HNPFJet100, "text0 hist", true);
   PsFile.AddPlot(HNPFJet150, "text0 hist", true);
   PsFile.AddPlot(HEnergyPFJet, "", true);
   PsFile.AddPlot(HPTPFJet, "", true);
   PsFile.AddPlot(HEtaPFJet, "", false);
   PsFile.AddPlot(HPhiPFJet, "", false);
   PsFile.AddPlot(HLeadingPFJetPT, "", true);
   PsFile.AddPlot(HLeadingPFJetEta, "", false);
   PsFile.AddPlot(HLeadingPFJetPhi, "", false);
   PsFile.AddPlot(HSubLeadingPFJetPT, "", true);
   PsFile.AddPlot(HSubLeadingPFJetEta, "", false);
   PsFile.AddPlot(HSubLeadingPFJetPhi, "", false);
   PsFile.AddPlot(HLeadingTwoPFJetsPTVsPT, "colz", false);
   PsFile.AddPlot(HLeadingTwoPFJetsDPhi, "", false);
   PsFile.AddPlot(HLeadingTwoPFJetsDR, "", false);

   PsFile.AddTextPage("PF Jet b-tagging plots");
   
   vector<string> PFJetBTaggingExplanation;
   PFJetBTaggingExplanation.push_back("Leading and sub-leading are the two largest jets in pt");
   PFJetBTaggingExplanation.push_back("All the rest are included in the \"non-leading\" category");
   PFJetBTaggingExplanation.push_back("");
   PFJetBTaggingExplanation.push_back("Plots in this section are normalized to the same area");
   PFJetBTaggingExplanation.push_back("      for ease of comparison");
   PsFile.AddTextPage(PFJetBTaggingExplanation);

   AddThreeHistogramOverlayPlot(PsFile,
      &HCombinedSecondaryVertexBTagNonLeadingPFJet,
      &HCombinedSecondaryVertexBTagLeadingPFJet,
      &HCombinedSecondaryVertexBTagSubLeadingPFJet,
      "combined secondary vertex b tag (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HCombinedSecondaryVertexMVABTagNonLeadingPFJet,
      &HCombinedSecondaryVertexMVABTagLeadingPFJet,
      &HCombinedSecondaryVertexMVABTagSubLeadingPFJet,
      "combined secondary vertex MVA b tag (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HJetBProbabilityBTagNonLeadingPFJet,
      &HJetBProbabilityBTagLeadingPFJet,
      &HJetBProbabilityBTagSubLeadingPFJet,
      "jet b probability b tag (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HJetProbabilityBTagNonLeadingPFJet,
      &HJetProbabilityBTagLeadingPFJet,
      &HJetProbabilityBTagSubLeadingPFJet,
      "jet probability b tag (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSimpleSecondaryVertexHighEffBTagNonLeadingPFJet,
      &HSimpleSecondaryVertexHighEffBTagLeadingPFJet,
      &HSimpleSecondaryVertexHighEffBTagSubLeadingPFJet,
      "simple secondary vertex b tag (high eff.) (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSimpleSecondaryVertexHighPurBTagNonLeadingPFJet,
      &HSimpleSecondaryVertexHighPurBTagLeadingPFJet,
      &HSimpleSecondaryVertexHighPurBTagSubLeadingPFJet,
      "simple secondary vertex b tag (high pur.) (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftMuonBTagNonLeadingPFJet,
      &HSoftMuonBTagLeadingPFJet,
      &HSoftMuonBTagSubLeadingPFJet,
      "soft muon b tag (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftMuonByIP3DBTagNonLeadingPFJet,
      &HSoftMuonByIP3DBTagLeadingPFJet,
      &HSoftMuonByIP3DBTagSubLeadingPFJet,
      "soft muon b tag (by IP3D) (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftMuonByPtBTagNonLeadingPFJet,
      &HSoftMuonByPtBTagLeadingPFJet,
      &HSoftMuonByPtBTagSubLeadingPFJet,
      "soft muon b tag (by PT) (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftElectronBTagNonLeadingPFJet,
      &HSoftElectronBTagLeadingPFJet,
      &HSoftElectronBTagSubLeadingPFJet,
      "soft electron b tag (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftElectronByIP3DBTagNonLeadingPFJet,
      &HSoftElectronByIP3DBTagLeadingPFJet,
      &HSoftElectronByIP3DBTagSubLeadingPFJet,
      "soft electron b tag (by IP3D) (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HSoftElectronByPtBTagNonLeadingPFJet,
      &HSoftElectronByPtBTagLeadingPFJet,
      &HSoftElectronByPtBTagSubLeadingPFJet,
      "soft electron b tag (by PT) (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HTrackCountingHighPurBTagNonLeadingPFJet,
      &HTrackCountingHighPurBTagLeadingPFJet,
      &HTrackCountingHighPurBTagSubLeadingPFJet,
      "track counting b tag (high pur.) (PF Jet)", "non-leading", "leading", "sub-leading", "", true);
   AddThreeHistogramOverlayPlot(PsFile,
      &HTrackCountingHighEffBTagNonLeadingPFJet,
      &HTrackCountingHighEffBTagLeadingPFJet,
      &HTrackCountingHighEffBTagSubLeadingPFJet,
      "track counting b tag (high eff.) (PF Jet)", "non-leading", "leading", "sub-leading", "", true);

   PsFile.AddTextPage("PF jet closest to generated b-hadron");
   PsFile.AddPlot(HGenBHadronClosestPFJetDR, "", true);
   PsFile.AddPlot(HGenBHadronClosestPFJetDRVsJetPT, "colz", false);
   PsFile.AddPlot(HGenBHadronClosestPFJetPTVsPT, "colz", false);
   AddThreeHistogramOverlayPlot(PsFile, &HGenBHadronClosestPFJetPTRatio, &HGenBHadronClosestPFJetPTRatio50GeV,
      &HGenBHadronClosestPFJetPTRatio100GeV, "PT ratio of generated b-hadron and closest PF jet",
      "All", "b-hadron PT > 50", "b-hadron PT > 100", "", true);

   PsFile.AddTextPage("Calo MET plots");
   PsFile.AddPlot(HCaloMET, "", true);
   PsFile.AddPlot(HCaloMETPhi, "", false);
   PsFile.AddPlot(HCaloMETLeadingJetDPhi, "", true);
   PsFile.AddPlot(HCaloMETLeadingTwoJetsDPhi, "", true);
   PsFile.AddPlot(HCaloMETVsLeadingTwoJetsPT, "colz", false);
   PsFile.AddPlot(HCaloMETWithoutLeadingTwoJets, "", true);
  
   PsFile.AddTextPage("PF MET plots");
   PsFile.AddPlot(HPFMET, "", true);
   PsFile.AddPlot(HPFMETPhi, "", false);
   PsFile.AddPlot(HPFMETLeadingJetDPhi, "", true);
   PsFile.AddPlot(HPFMETLeadingTwoJetsDPhi, "", true);
   PsFile.AddPlot(HPFMETVsLeadingTwoJetsPT, "colz", false);
   PsFile.AddPlot(HPFMETWithoutLeadingTwoJets, "", true);
   PsFile.AddPlot(HCaloMETVsPFMET, "colz", false);

   PsFile.AddTextPage("MR and R from calo jets");
   PsFile.AddPlot(HCaloJetMR, "", false);
   PsFile.AddPlot(HCaloJetMRT, "", true);
   PsFile.AddPlot(HCaloJetR, "", true);
   PsFile.AddPlot(HCaloJetMRVsR, "colz", false);
   PsFile.AddPlot(HCaloJetMR_R01, "", false);
   PsFile.AddPlot(HCaloJetMR_R02, "", false);
   PsFile.AddPlot(HCaloJetMR_R03, "", false);
   PsFile.AddPlot(HCaloJetMR_R04, "", false);
   PsFile.AddPlot(HCaloJetMR_R05, "", false);
   PsFile.AddPlot(HCaloJetMR_R06, "", false);
   PsFile.AddPlot(HCaloJetMR_R07, "", false);
   PsFile.AddPlot(HCaloJetMR_R08, "", false);
   PsFile.AddPlot(HCaloJetMR_R09, "", false);
   PsFile.AddPlot(HCaloJetMR_R10, "", false);
   PsFile.AddPlot(HCaloJetRCutEfficiency, "text00 hist", true);
  
   PsFile.AddTextPage("MR and R from PF jets");
   PsFile.AddPlot(HPFJetMR, "", false);
   PsFile.AddPlot(HPFJetMRT, "", true);
   PsFile.AddPlot(HPFJetR, "", true);
   PsFile.AddPlot(HPFJetMRVsR, "colz", false);
   PsFile.AddPlot(HPFJetMR_R01, "", false);
   PsFile.AddPlot(HPFJetMR_R02, "", false);
   PsFile.AddPlot(HPFJetMR_R03, "", false);
   PsFile.AddPlot(HPFJetMR_R04, "", false);
   PsFile.AddPlot(HPFJetMR_R05, "", false);
   PsFile.AddPlot(HPFJetMR_R06, "", false);
   PsFile.AddPlot(HPFJetMR_R07, "", false);
   PsFile.AddPlot(HPFJetMR_R08, "", false);
   PsFile.AddPlot(HPFJetMR_R09, "", false);
   PsFile.AddPlot(HPFJetMR_R10, "", false);
   PsFile.AddPlot(HPFJetRCutEfficiency, "text00 hist", true);
  
   // Close things 
   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

void AddThreeHistogramOverlayPlot(PsFileHelper &PsFile,
   TH1D *H1, TH1D *H2, TH1D *H3, string Title, string L1, string L2, string L3, string Option, bool LogY)
{
   TCanvas canvas;

   H1->SetLineColor(1);
   H2->SetLineColor(2);
   H3->SetLineColor(3);

   H1->SetStats(0);
   H2->SetStats(0);
   H3->SetStats(0);

   H1->SetTitle(Title.c_str());
   H2->SetTitle(Title.c_str());
   H3->SetTitle(Title.c_str());

   if(Option != "")
   {
      H1->DrawNormalized(Option.c_str());
      H2->DrawNormalized((Option + " same").c_str());
      H3->DrawNormalized((Option + " same").c_str());
   }
   else
   {
      H1->DrawNormalized("");
      H2->DrawNormalized("same");
      H3->DrawNormalized("same");
   }

   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.SetFillColor(0);
   legend.AddEntry(H1, L1.c_str(), "l");
   legend.AddEntry(H2, L2.c_str(), "l");
   legend.AddEntry(H3, L3.c_str(), "l");
   legend.Draw();

   if(LogY == true)
      canvas.SetLogy();

   PsFile.AddCanvas(canvas);
}

int FindChildIndex(NTPTreeMessenger &M, int ChildPDGID, int ParentPDGID)
{
   int MotherIndex = -1;

   for(int i = 0; i < M.nMc; i++)
   {
      if(M.idMc[i] == ParentPDGID)
      {
         MotherIndex = i;
         break;
      }
   }

   if(MotherIndex == -1)
      return -1;

   for(int i = 0; i < M.nMc; i++)
      if(M.idMc[i] == ChildPDGID && M.mothMc[i] == MotherIndex)
         return i;

   return -1;
}

int TraceBHadron(NTPTreeMessenger &M, int StartIndex)
{
   if(StartIndex < 0 || StartIndex >= M.nMc)
      return -1;
   if(HasB(M.idMc[StartIndex]) == false && M.idMc[StartIndex] != 92)
      return -1;

   int CurrentIndex = StartIndex;

   bool OK = false;
   while(OK == false)
   {
      // step 1: collect list of children that contain b (or is a string)
      vector<int> ChildrenIndex;
      for(int i = 0; i < M.nMc; i++)
      {
         if(M.mothMc[i] == CurrentIndex)
         {
            if(M.idMc[i] != 92 && HasB(M.idMc[i]) == false)
               continue;
            ChildrenIndex.push_back(i);
         }
      }

      // step 2: if there is more than one candidate, choose the one with highest pt
      if(ChildrenIndex.size() == 0)
         return CurrentIndex;
      else if(ChildrenIndex.size() == 1)
         CurrentIndex = ChildrenIndex[0];
      else
      {
         double BestCandidatePT = M.pMc[ChildrenIndex[0]] / cosh(M.etaMc[ChildrenIndex[0]]);
         int BestCandidate = 0;
         for(int i = 1; i < (int)ChildrenIndex.size(); i++)
         {
            double PT = M.pMc[ChildrenIndex[i]] / cosh(M.etaMc[ChildrenIndex[i]]);
            if(PT > BestCandidatePT)
            {
               BestCandidate = i;
               BestCandidatePT = PT;
            }
         }

         CurrentIndex = ChildrenIndex[BestCandidate];
      }
   }

   return -1;
}

bool HasB(int PDGID)
{
   // note:
   //    b quark: +-5
   //    meson code = 100i + 10j + 2s + 1, quark(i), anti-quark(-j)
   //    baryon code = 1000i + 100j + 10k + 2s + 1, quarks(ijk)

   if(PDGID < 0)
      PDGID = -PDGID;

   if(PDGID == 5)
      return true;
   if((PDGID % 100) / 10 == 5)
      return true;
   if((PDGID % 1000) / 100 == 5)
      return true;
   if((PDGID % 10000) / 1000 == 5)
      return true;

   return false;
}

int FindClosestJet(float *JetCollectionEta, float *JetCollectionPhi, int JetCount, double Eta, double Phi)
{
   double ClosestJetDR = 999999;
   int ClosestJetIndex = 0;
   for(int i = 0; i < JetCount; i++)
   {
      double EtaJet = JetCollectionEta[i];
      double PhiJet = JetCollectionPhi[i];

      double DEta = Eta - EtaJet;
      double DPhi = Phi - PhiJet;
      if(DPhi > PI)   DPhi = DPhi - 2 * PI;
      if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
      double DR = sqrt(DPhi * DPhi + DEta * DEta);

      if(ClosestJetDR > DR)
      {
         ClosestJetDR = DR;
         ClosestJetIndex = i;
      }
   }

   return ClosestJetIndex;
}








