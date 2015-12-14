//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <sstream>
using namespace std;
//---------------------------------------------------------------------------
#include "fastjet/ClusterSequence.hh"
using namespace fastjet;
//---------------------------------------------------------------------------
#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TChain.h"
//---------------------------------------------------------------------------
#include "ChainAll.h"
#include "PlotHelper2.h"
#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "ReadNTPTree.h"
#include "SetStyle.h"
//---------------------------------------------------------------------------
#define TCHECut 2.5
#define TCHPCut 1.5
#define JetProbabilityCut 0.55
#define JetBProbabilityCut 2.2
#define SSVHECut 2.5
#define SSVHPCut 3
#define CSVCut 0.75
#define CSVMCut 0.7
//---------------------------------------------------------------------------
int main(int argc, char *argv[]);
void BTaggingKinematics(string InputList);
int FindChildIndex(NTPTreeMessenger &M, int ChildPDGID, int ParentPDGID);
int TraceBHadron(NTPTreeMessenger &M, int StartIndex);
bool HasB(int PDGID);
int FindClosestJet(float *JetCollectionEta, float *JetCollectionPhi, int JetCount, double Eta, double Phi);
bool IsGoodMuon(NTPTreeMessenger &M, int MuonIndex);
void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, bool LogY = false);
void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, TH1D *H3, bool LogY = false);
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   SetStyle();

   BTaggingKinematics("TTJets.list");

   return 0;
}
//---------------------------------------------------------------------------
void BTaggingKinematics(string InputList)
{
   // Read inputs
   TChain *NTPTree = ChainAll(InputList, "ntp1");
   if(NTPTree == NULL)   // error!
      return;

   NTPTreeMessenger M;
   M.SetBranchAddress(NTPTree);

   // Output file header
   PsFileHelper PsFile("StudyOfBTaggingVsKinematics.ps");
   PsFile.AddTextPage("Study of kinematics effect of b-tagging");

   vector<string> ExplanationText;
   ExplanationText.push_back("B-tagging is important.  But we need to know if it can cause any");
   ExplanationText.push_back("bias in the kinematics before using it happily.");
   PsFile.AddTextPage(ExplanationText);

   vector<string> TableOfContentItems;
   TableOfContentItems.push_back("Basic Information");
   TableOfContentItems.push_back("Sanity checks of tracing b-hadron and match to jets");
   TableOfContentItems.push_back("B-Tagging distribution for matched jets");
   TableOfContentItems.push_back("MR and R distributions");
   
   vector<string> Destinations;
   Destinations.push_back("BasicInformation");
   Destinations.push_back("Tracing");
   Destinations.push_back("BTagging");
   Destinations.push_back("ChrisVariable");

   PsFile.AddTableOfContentPage(TableOfContentItems, Destinations);
   PsFile.InsertNamedDestination("HomePage");
   PsFile.SetAutomaticHomeButton(true, "HomePage", 50, 50, 75);

   // Basic information
   TH1D HBunchCrossing("HBunchCrossing", "Bunch crossing of triggers!", 3502, -1.5, 3500.5);
   TH1D HNPV("HNPV", "Number of (good) primary vertices", 10, -0.5, 9.5);
   TH2D HPVXVsPVY("HPVXVsPVY", "PV, x vs. y, best PV;X;Y", 100, 0.1, 0.4, 100, 0.2, 0.5);
   TH2D HPVTVsPVZ("HPVTVsPVZ", "PV, transverse vs. z, best PV;Transverse;Z", 100, 0.4, 0.5, 100, -40, 40);

   // Plots about tracing B-Meson
   TH1D HBHadronPT("HBHadronPT", "PT of \"final\" b hadron", 100, 0, 500);
   TH1D HClosestJetPT("HClosestJetPT", "PT of jet closest to \"final\" b hadron", 100, 0, 500);
   TH2D HBHadronPTVsClosestJetPT("HBHadronPTVsClosestJetPT", "PT of \"final\" b hadron vs. closest jet pt;B;Jet",
      100, 0, 500, 100, 0, 500);
   TH2D HBHadronVsClosestJetDEtaDPhi("HBHadronVsClosestJetDEtaDPhi",
      "deta-dphi between \"final\" b hadron vs. closest jet;deta;dphi", 100, -2, 2, 100, -2, 2);
   TH2D HBHadronPTVsClosestJetPTSelected("HBHadronPTVsClosestJetPTSelected",
      "PT of \"final\" b hadron vs. closest jet pt, selected;B;Jet", 100, 0, 500, 100, 0, 500);
   TH2D HBHadronVsClosestJetDEtaDPhiSelected("HBHadronVsClosestJetDEtaDPhiSelected",
      "deta-dphi between \"final\" b hadron vs. closest jet, selected;deta;dphi", 100, -2, 2, 100, -2, 2);

   // Basic b-tagging plots for the jets
   TH1D HJetTCHE("HJetTCHE", "TCHE tag", 100, -10, 30);
   TH1D HJetTCHP("HJetTCHP", "TCHP tag", 100, -10, 30);
   TH1D HJetProbability("HJetProbability", "Jet Probability tag", 100, 0, 2.5);
   TH1D HJetBProbability("HJetBProbability", "JetB Probability tag", 100, 0, 8);
   TH1D HJetSSVHE("HJetSSVHE", "SSVHE tag", 100, 0, 8);
   TH1D HJetSSVHP("HJetSSVHP", "SSVHP tag", 100, 0, 8);
   TH1D HJetCSV("HJetCSV", "HJetCSV", 100, 0, 1);
   TH1D HJetCSVM("HJetCSVM", "HJetCSVM", 100, 0, 1);

   TH2D HJetTCHEVsPT("HJetTCHEVsPT", "TCHE vs. PT;TCHE;PT", 100, -10, 30, 100, 0, 500);
   TH2D HJetTCHPVsPT("HJetTCHPVsPT", "TCHP vs. PT;TCHP;PT", 100, -10, 30, 100, 0, 500);
   TH2D HJetProbabilityVsPT("HJetProbabilityVsPT", "Jet probability vs. PT;Probability;PT", 100, 0, 2.5, 100, 0, 500);
   TH2D HJetBProbabilityVsPT("HJetBProbabilityVsPT", "JetB probability vs. PT;B Probability;PT", 100, 0, 8, 100, 0, 500);
   TH2D HJetSSVHEVsPT("HJetSSVHEVsPT", "SSVHE vs. PT;SSVHE;PT", 100, 0, 8, 100, 0, 500);
   TH2D HJetSSVHPVsPT("HJetSSVHPVsPT", "SSVHP vs. PT;SSVHP;PT", 100, 0, 8, 100, 0, 500);
   TH2D HJetCSVVsPT("HJetCSVVsPT", "CSV vs. PT;CSV;PT", 100, 0, 1, 100, 0, 500);
   TH2D HJetCSVMVsPT("HJetCSVMVsPT", "CSVM vs. PT;CSVM;PT", 100, 0, 1, 100, 0, 500);

   TH1D HPTLowTCHE("HPTLowTCHE", "PT distribution, low TCHE value", 100, 0, 500);
   TH1D HPTHighTCHE("HPTHighTCHE", "PT distribution, high TCHE value", 100, 0, 500);
   TH1D HPTLowTCHP("HPTLowTCHP", "PT distribution, low TCHP value", 100, 0, 500);
   TH1D HPTHighTCHP("HPTHighTCHP", "PT distribution, high TCHP value", 100, 0, 500);
   TH1D HPTLowJetProbability("HPTLowJetProbability", "PT distribution, low JetProbability value", 100, 0, 500);
   TH1D HPTHighJetProbability("HPTHighJetProbability", "PT distribution, high JetProbability value", 100, 0, 500);
   TH1D HPTLowJetBProbability("HPTLowJetBProbability", "PT distribution, low JetBProbability value", 100, 0, 500);
   TH1D HPTHighJetBProbability("HPTHighJetBProbability", "PT distribution, high JetBProbability value", 100, 0, 500);
   TH1D HPTLowSSVHE("HPTLowSSVHE", "PT distribution, low SSVHE value", 100, 0, 500);
   TH1D HPTHighSSVHE("HPTHighSSVHE", "PT distribution, high SSVHE value", 100, 0, 500);
   TH1D HPTLowSSVHP("HPTLowSSVHP", "PT distribution, low SSVHP value", 100, 0, 500);
   TH1D HPTHighSSVHP("HPTHighSSVHP", "PT distribution, high SSVHP value", 100, 0, 500);
   TH1D HPTLowCSV("HPTLowCSV", "PT distribution, low CSV value", 100, 0, 500);
   TH1D HPTHighCSV("HPTHighCSV", "PT distribution, high CSV value", 100, 0, 500);
   TH1D HPTLowCSVM("HPTLowCSVM", "PT distribution, low CSVM value", 100, 0, 500);
   TH1D HPTHighCSVM("HPTHighCSVM", "PT distribution, high CSVM value", 100, 0, 500);
   
   TH2D HJetTCHEVsEta("HJetTCHEVsEta", "TCHE vs. Eta;TCHE;Eta", 100, -10, 30, 100, -3, 3);
   TH2D HJetTCHPVsEta("HJetTCHPVsEta", "TCHP vs. Eta;TCHP;Eta", 100, -10, 30, 100, -3, 3);
   TH2D HJetProbabilityVsEta("HJetProbabilityVsEta", "Jet probability vs. Eta;Probability;Eta", 100, 0, 2.5, 100, -3, 3);
   TH2D HJetBProbabilityVsEta("HJetBProbabilityVsEta",
      "JetB probability vs. Eta;B Probability;Eta", 100, 0, 8, 100, -3, 3);
   TH2D HJetSSVHEVsEta("HJetSSVHEVsEta", "SSVHE vs. Eta;SSVHE;Eta", 100, 0, 8, 100, -3, 3);
   TH2D HJetSSVHPVsEta("HJetSSVHPVsEta", "SSVHP vs. Eta;SSVHP;Eta", 100, 0, 8, 100, -3, 3);
   TH2D HJetCSVVsEta("HJetCSVVsEta", "CSV vs. Eta;CSV;Eta", 100, 0, 1, 100, -3, 3);
   TH2D HJetCSVMVsEta("HJetCSVMVsEta", "CSVM vs. Eta;CSVM;Eta", 100, 0, 1, 100, -3, 3);
   
   TH1D HEtaLowTCHE("HEtaLowTCHE", "Eta distribution, low TCHE value", 100, -3, 3);
   TH1D HEtaHighTCHE("HEtaHighTCHE", "Eta distribution, high TCHE value", 100, -3, 3);
   TH1D HEtaLowTCHP("HEtaLowTCHP", "Eta distribution, low TCHP value", 100, -3, 3);
   TH1D HEtaHighTCHP("HEtaHighTCHP", "Eta distribution, high TCHP value", 100, -3, 3);
   TH1D HEtaLowJetProbability("HEtaLowJetProbability", "Eta distribution, low JetProbability value", 100, -3, 3);
   TH1D HEtaHighJetProbability("HEtaHighJetProbability", "Eta distribution, high JetProbability value", 100, -3, 3);
   TH1D HEtaLowJetBProbability("HEtaLowJetBProbability", "Eta distribution, low JetBProbability value", 100, -3, 3);
   TH1D HEtaHighJetBProbability("HEtaHighJetBProbability", "Eta distribution, high JetBProbability value", 100, -3, 3);
   TH1D HEtaLowSSVHE("HEtaLowSSVHE", "Eta distribution, low SSVHE value", 100, -3, 3);
   TH1D HEtaHighSSVHE("HEtaHighSSVHE", "Eta distribution, high SSVHE value", 100, -3, 3);
   TH1D HEtaLowSSVHP("HEtaLowSSVHP", "Eta distribution, low SSVHP value", 100, -3, 3);
   TH1D HEtaHighSSVHP("HEtaHighSSVHP", "Eta distribution, high SSVHP value", 100, -3, 3);
   TH1D HEtaLowCSV("HEtaLowCSV", "Eta distribution, low CSV value", 100, -3, 3);
   TH1D HEtaHighCSV("HEtaHighCSV", "Eta distribution, high CSV value", 100, -3, 3);
   TH1D HEtaLowCSVM("HEtaLowCSVM", "Eta distribution, low CSVM value", 100, -3, 3);
   TH1D HEtaHighCSVM("HEtaHighCSVM", "Eta distribution, high CSVM value", 100, -3, 3);

   TH2D HMRVsRAll("HMRVsRAll", "MR vs. R, no selection;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRSelected("HMRVsRSelected", "MR vs. R, selected;MR;R", 100, 0, 1500, 100, 0, 1.2);
   
   TH1D HMRLowTCHE("HMRLowTCHE", "MR, Low TCHE;MR", 100, 0, 1500);
   TH1D HMRMixTCHE("HMRMixTCHE", "MR, Mix TCHE;MR", 100, 0, 1500);
   TH1D HMRHighTCHE("HMRHighTCHE", "MR, High TCHE;MR", 100, 0, 1500);
   TH1D HMRLowTCHE_R03("HMRLowTCHE_R03", "MR, Low TCHE, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRMixTCHE_R03("HMRMixTCHE_R03", "MR, Mix TCHE, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRHighTCHE_R03("HMRHighTCHE_R03", "MR, High TCHE, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRLowTCHE_R05("HMRLowTCHE_R05", "MR, Low TCHE, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRMixTCHE_R05("HMRMixTCHE_R05", "MR, Mix TCHE, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRHighTCHE_R05("HMRHighTCHE_R05", "MR, High TCHE, R > 0.5;MR", 100, 0, 1500);
   TH1D HRLowTCHE("HRLowTCHE", "R, Low TCHE;R", 100, 0, 1.2);
   TH1D HRMixTCHE("HRMixTCHE", "R, Mix TCHE;R", 100, 0, 1.2);
   TH1D HRHighTCHE("HRHighTCHE", "R, High TCHE;R", 100, 0, 1.2);
   TH2D HMRVsRLowTCHE("HMRVsRLowTCHE", "MR vs. R, Low TCHE;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRMixTCHE("HMRVsRMixTCHE", "MR vs. R, Mix TCHE;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRHighTCHE("HMRVsRHighTCHE", "MR vs. R, High TCHE;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH1D HMRLowTCHP("HMRLowTCHP", "MR, Low TCHP;MR", 100, 0, 1500);
   TH1D HMRMixTCHP("HMRMixTCHP", "MR, Mix TCHP;MR", 100, 0, 1500);
   TH1D HMRHighTCHP("HMRHighTCHP", "MR, High TCHP;MR", 100, 0, 1500);
   TH1D HMRLowTCHP_R03("HMRLowTCHP_R03", "MR, Low TCHP, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRMixTCHP_R03("HMRMixTCHP_R03", "MR, Mix TCHP, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRHighTCHP_R03("HMRHighTCHP_R03", "MR, High TCHP, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRLowTCHP_R05("HMRLowTCHP_R05", "MR, Low TCHP, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRMixTCHP_R05("HMRMixTCHP_R05", "MR, Mix TCHP, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRHighTCHP_R05("HMRHighTCHP_R05", "MR, High TCHP, R > 0.5;MR", 100, 0, 1500);
   TH1D HRLowTCHP("HRLowTCHP", "R, Low TCHP;R", 100, 0, 1.2);
   TH1D HRMixTCHP("HRMixTCHP", "R, Mix TCHP;R", 100, 0, 1.2);
   TH1D HRHighTCHP("HRHighTCHP", "R, High TCHP;R", 100, 0, 1.2);
   TH2D HMRVsRLowTCHP("HMRVsRLowTCHP", "MR vs. R, Low TCHP;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRMixTCHP("HMRVsRMixTCHP", "MR vs. R, Mix TCHP;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRHighTCHP("HMRVsRHighTCHP", "MR vs. R, High TCHP;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH1D HMRLowJetProbability("HMRLowJetProbability", "MR, Low JetProbability;MR", 100, 0, 1500);
   TH1D HMRMixJetProbability("HMRMixJetProbability", "MR, Mix JetProbability;MR", 100, 0, 1500);
   TH1D HMRHighJetProbability("HMRHighJetProbability", "MR, High JetProbability;MR", 100, 0, 1500);
   TH1D HMRLowJetProbability_R03("HMRLowJetProbability_R03", "MR, Low JetProbability, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRMixJetProbability_R03("HMRMixJetProbability_R03", "MR, Mix JetProbability, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRHighJetProbability_R03("HMRHighJetProbability_R03", "MR, High JetProbability, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRLowJetProbability_R05("HMRLowJetProbability_R05", "MR, Low JetProbability, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRMixJetProbability_R05("HMRMixJetProbability_R05", "MR, Mix JetProbability, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRHighJetProbability_R05("HMRHighJetProbability_R05", "MR, High JetProbability, R > 0.5;MR", 100, 0, 1500);
   TH1D HRLowJetProbability("HRLowJetProbability", "R, Low JetProbability;R", 100, 0, 1.2);
   TH1D HRMixJetProbability("HRMixJetProbability", "R, Mix JetProbability;R", 100, 0, 1.2);
   TH1D HRHighJetProbability("HRHighJetProbability", "R, High JetProbability;R", 100, 0, 1.2);
   TH2D HMRVsRLowJetProbability("HMRVsRLowJetProbability",
      "MR vs. R, Low JetProbability;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRMixJetProbability("HMRVsRMixJetProbability",
      "MR vs. R, Mix JetProbability;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRHighJetProbability("HMRVsRHighJetProbability",
      "MR vs. R, High JetProbability;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH1D HMRLowJetBProbability("HMRLowJetBProbability", "MR, Low JetBProbability;MR", 100, 0, 1500);
   TH1D HMRMixJetBProbability("HMRMixJetBProbability", "MR, Mix JetBProbability;MR", 100, 0, 1500);
   TH1D HMRHighJetBProbability("HMRHighJetBProbability", "MR, High JetBProbability;MR", 100, 0, 1500);
   TH1D HMRLowJetBProbability_R03("HMRLowJetBProbability_R03", "MR, Low JetBProbability, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRMixJetBProbability_R03("HMRMixJetBProbability_R03", "MR, Mix JetBProbability, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRHighJetBProbability_R03("HMRHighJetBProbability_R03", "MR, High JetBProbability, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRLowJetBProbability_R05("HMRLowJetBProbability_R05", "MR, Low JetBProbability, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRMixJetBProbability_R05("HMRMixJetBProbability_R05", "MR, Mix JetBProbability, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRHighJetBProbability_R05("HMRHighJetBProbability_R05", "MR, High JetBProbability, R > 0.5;MR", 100, 0, 1500);
   TH1D HRLowJetBProbability("HRLowJetBProbability", "R, Low JetBProbability;R", 100, 0, 1.2);
   TH1D HRMixJetBProbability("HRMixJetBProbability", "R, Mix JetBProbability;R", 100, 0, 1.2);
   TH1D HRHighJetBProbability("HRHighJetBProbability", "R, High JetBProbability;R", 100, 0, 1.2);
   TH2D HMRVsRLowJetBProbability("HMRVsRLowJetBProbability",
      "MR vs. R, Low JetBProbability;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRMixJetBProbability("HMRVsRMixJetBProbability",
      "MR vs. R, Mix JetBProbability;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRHighJetBProbability("HMRVsRHighJetBProbability",
      "MR vs. R, High JetBProbability;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH1D HMRLowSSVHE("HMRLowSSVHE", "MR, Low SSVHE;MR", 100, 0, 1500);
   TH1D HMRMixSSVHE("HMRMixSSVHE", "MR, Mix SSVHE;MR", 100, 0, 1500);
   TH1D HMRHighSSVHE("HMRHighSSVHE", "MR, High SSVHE;MR", 100, 0, 1500);
   TH1D HMRLowSSVHE_R03("HMRLowSSVHE_R03", "MR, Low SSVHE, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRMixSSVHE_R03("HMRMixSSVHE_R03", "MR, Mix SSVHE, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRHighSSVHE_R03("HMRHighSSVHE_R03", "MR, High SSVHE, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRLowSSVHE_R05("HMRLowSSVHE_R05", "MR, Low SSVHE, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRMixSSVHE_R05("HMRMixSSVHE_R05", "MR, Mix SSVHE, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRHighSSVHE_R05("HMRHighSSVHE_R05", "MR, High SSVHE, R > 0.5;MR", 100, 0, 1500);
   TH1D HRLowSSVHE("HRLowSSVHE", "R, Low SSVHE;R", 100, 0, 1.2);
   TH1D HRMixSSVHE("HRMixSSVHE", "R, Mix SSVHE;R", 100, 0, 1.2);
   TH1D HRHighSSVHE("HRHighSSVHE", "R, High SSVHE;R", 100, 0, 1.2);
   TH2D HMRVsRLowSSVHE("HMRVsRLowSSVHE", "MR vs. R, Low SSVHE;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRMixSSVHE("HMRVsRMixSSVHE", "MR vs. R, Mix SSVHE;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRHighSSVHE("HMRVsRHighSSVHE", "MR vs. R, High SSVHE;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH1D HMRLowSSVHP("HMRLowSSVHP", "MR, Low SSVHP;MR", 100, 0, 1500);
   TH1D HMRMixSSVHP("HMRMixSSVHP", "MR, Mix SSVHP;MR", 100, 0, 1500);
   TH1D HMRHighSSVHP("HMRHighSSVHP", "MR, High SSVHP;MR", 100, 0, 1500);
   TH1D HMRLowSSVHP_R03("HMRLowSSVHP_R03", "MR, Low SSVHP, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRMixSSVHP_R03("HMRMixSSVHP_R03", "MR, Mix SSVHP, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRHighSSVHP_R03("HMRHighSSVHP_R03", "MR, High SSVHP, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRLowSSVHP_R05("HMRLowSSVHP_R05", "MR, Low SSVHP, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRMixSSVHP_R05("HMRMixSSVHP_R05", "MR, Mix SSVHP, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRHighSSVHP_R05("HMRHighSSVHP_R05", "MR, High SSVHP, R > 0.5;MR", 100, 0, 1500);
   TH1D HRLowSSVHP("HRLowSSVHP", "R, Low SSVHP;R", 100, 0, 1.2);
   TH1D HRMixSSVHP("HRMixSSVHP", "R, Mix SSVHP;R", 100, 0, 1.2);
   TH1D HRHighSSVHP("HRHighSSVHP", "R, High SSVHP;R", 100, 0, 1.2);
   TH2D HMRVsRLowSSVHP("HMRVsRLowSSVHP", "MR vs. R, Low SSVHP;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRMixSSVHP("HMRVsRMixSSVHP", "MR vs. R, Mix SSVHP;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRHighSSVHP("HMRVsRHighSSVHP", "MR vs. R, High SSVHP;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH1D HMRLowCSV("HMRLowCSV", "MR, Low CSV;MR", 100, 0, 1500);
   TH1D HMRMixCSV("HMRMixCSV", "MR, Mix CSV;MR", 100, 0, 1500);
   TH1D HMRHighCSV("HMRHighCSV", "MR, High CSV;MR", 100, 0, 1500);
   TH1D HMRLowCSV_R03("HMRLowCSV_R03", "MR, Low CSV, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRMixCSV_R03("HMRMixCSV_R03", "MR, Mix CSV, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRHighCSV_R03("HMRHighCSV_R03", "MR, High CSV, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRLowCSV_R05("HMRLowCSV_R05", "MR, Low CSV, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRMixCSV_R05("HMRMixCSV_R05", "MR, Mix CSV, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRHighCSV_R05("HMRHighCSV_R05", "MR, High CSV, R > 0.5;MR", 100, 0, 1500);
   TH1D HRLowCSV("HRLowCSV", "R, Low CSV;R", 100, 0, 1.2);
   TH1D HRMixCSV("HRMixCSV", "R, Mix CSV;R", 100, 0, 1.2);
   TH1D HRHighCSV("HRHighCSV", "R, High CSV;R", 100, 0, 1.2);
   TH2D HMRVsRLowCSV("HMRVsRLowCSV", "MR vs. R, Low CSV;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRMixCSV("HMRVsRMixCSV", "MR vs. R, Mix CSV;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRHighCSV("HMRVsRHighCSV", "MR vs. R, High CSV;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH1D HMRLowCSVM("HMRLowCSVM", "MR, Low CSVM;MR", 100, 0, 1500);
   TH1D HMRMixCSVM("HMRMixCSVM", "MR, Mix CSVM;MR", 100, 0, 1500);
   TH1D HMRHighCSVM("HMRHighCSVM", "MR, High CSVM;MR", 100, 0, 1500);
   TH1D HMRLowCSVM_R03("HMRLowCSVM_R03", "MR, Low CSVM, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRMixCSVM_R03("HMRMixCSVM_R03", "MR, Mix CSVM, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRHighCSVM_R03("HMRHighCSVM_R03", "MR, High CSVM, R > 0.3;MR", 100, 0, 1500);
   TH1D HMRLowCSVM_R05("HMRLowCSVM_R05", "MR, Low CSVM, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRMixCSVM_R05("HMRMixCSVM_R05", "MR, Mix CSVM, R > 0.5;MR", 100, 0, 1500);
   TH1D HMRHighCSVM_R05("HMRHighCSVM_R05", "MR, High CSVM, R > 0.5;MR", 100, 0, 1500);
   TH1D HRLowCSVM("HRLowCSVM", "R, Low CSVM;R", 100, 0, 1.2);
   TH1D HRMixCSVM("HRMixCSVM", "R, Mix CSVM;R", 100, 0, 1.2);
   TH1D HRHighCSVM("HRHighCSVM", "R, High CSVM;R", 100, 0, 1.2);
   TH2D HMRVsRLowCSVM("HMRVsRLowCSVM", "MR vs. R, Low CSVM;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRMixCSVM("HMRVsRMixCSVM", "MR vs. R, Mix CSVM;MR;R", 100, 0, 1500, 100, 0, 1.2);
   TH2D HMRVsRHighCSVM("HMRVsRHighCSVM", "MR vs. R, High CSVM;MR;R", 100, 0, 1500, 100, 0, 1.2);

   // Loop through events
   int NumberOfEvents = NTPTree->GetEntries();
   for(int iEvent = 0; iEvent < NumberOfEvents; iEvent++)
   {
      if((iEvent + 1) % 5000 == 0)
         cout << "Processing entry " << iEvent + 1 << "/" << NumberOfEvents << endl;

      NTPTree->GetEntry(iEvent);

      float *TCHE = M.trackCountingHighEffBJetTagsAK5PFJet;
      float *TCHP = M.trackCountingHighPurBJetTagsAK5PFJet;
      float *JetProbability = M.jetProbabilityBJetTagsAK5PFJet;
      float *JetBProbability = M.jetBProbabilityBJetTagsAK5PFJet;
      float *SSVHE = M.simpleSecondaryVertexHighEffBJetTagsAK5PFJet;
      float *SSVHP = M.simpleSecondaryVertexHighPurBJetTagsAK5PFJet;
      float *CSV = M.combinedSecondaryVertexBJetTagsAK5PFJet;
      float *CSVM = M.combinedSecondaryVertexMVABJetTagsAK5PFJet;

      // Basic information
      HBunchCrossing.Fill(M.bunchCrossing);

      int GoodPVCount = 0;
      int BestPVIndex = -1;
      for(int i = 0; i < M.nPV; i++)
      {
         if(M.ndofPV[i] <= 4)   continue;
         if(M.PVzPV[i] > 15)   continue;
         if(M.PVxPV[i] * M.PVxPV[i] + M.PVyPV[i] * M.PVyPV[i] > 2 * 2)   continue;
         
         GoodPVCount = GoodPVCount + 1;
         if(BestPVIndex < 0 || M.SumPtPV[i] > M.SumPtPV[BestPVIndex])
            BestPVIndex = i;
      }

      HNPV.Fill(GoodPVCount);
      if(BestPVIndex >= 0)
      {
         FourVector BestPVP(0, M.PVxPV[BestPVIndex], M.PVyPV[BestPVIndex], M.PVzPV[BestPVIndex]);
         HPVXVsPVY.Fill(BestPVP[1], BestPVP[2]);
         HPVTVsPVZ.Fill(BestPVP.GetPT(), BestPVP[3]);
      }

      // Trace b-mesons from MC information
      int BFromT = max(FindChildIndex(M, 5, 6), FindChildIndex(M, -5, 6));
      int BFromTBar = max(FindChildIndex(M, 5, -6), FindChildIndex(M, -5, -6));
      int FinalBHadronFromT = TraceBHadron(M, BFromT);
      int FinalBHadronFromTBar = TraceBHadron(M, BFromTBar);
      int ClosestPFJetToBHadronFromT = -1;
      int ClosestPFJetToBHadronFromTBar = -1;
      FourVector FinalBFromTP, FinalBFromTBarP;
      FourVector ClosestPFJetToBHadronFromTP, ClosestPFJetToBHadronFromTBarP;

      if(M.etaMc[FinalBHadronFromT] > 2.4 || M.etaMc[FinalBHadronFromT] < -2.4)
         FinalBHadronFromT = -1;
      if(M.etaMc[FinalBHadronFromTBar] > 2.4 || M.etaMc[FinalBHadronFromTBar] < -2.4)
         FinalBHadronFromTBar = -1;

      if(FinalBHadronFromT >= 0)
         FinalBFromTP.SetSizeEtaPhiEnergy(M.pMc[FinalBHadronFromT], M.etaMc[FinalBHadronFromT],
            M.phiMc[FinalBHadronFromT], M.energyMc[FinalBHadronFromT]);
      if(FinalBHadronFromTBar >= 0)
         FinalBFromTBarP.SetSizeEtaPhiEnergy(M.pMc[FinalBHadronFromTBar], M.etaMc[FinalBHadronFromTBar],
            M.phiMc[FinalBHadronFromTBar], M.energyMc[FinalBHadronFromTBar]);
      if(FinalBHadronFromT >= 0)
      {
         ClosestPFJetToBHadronFromT = FindClosestJet(M.etaAK5PFJet, M.phiAK5PFJet, M.nAK5PFJet,
            M.etaMc[FinalBHadronFromT], M.phiMc[FinalBHadronFromT]);
         if(ClosestPFJetToBHadronFromT >= 0)
            ClosestPFJetToBHadronFromTP = FourVector(M.energyAK5PFJet[ClosestPFJetToBHadronFromT],
               M.pxAK5PFJet[ClosestPFJetToBHadronFromT],
               M.pyAK5PFJet[ClosestPFJetToBHadronFromT],
               M.pzAK5PFJet[ClosestPFJetToBHadronFromT]);
      }
      if(FinalBHadronFromTBar >= 0)
      {
         ClosestPFJetToBHadronFromTBar = FindClosestJet(M.etaAK5PFJet, M.phiAK5PFJet, M.nAK5PFJet,
            M.etaMc[FinalBHadronFromTBar], M.phiMc[FinalBHadronFromTBar]);
         if(ClosestPFJetToBHadronFromTBar >= 0)
            ClosestPFJetToBHadronFromTBarP = FourVector(M.energyAK5PFJet[ClosestPFJetToBHadronFromTBar],
               M.pxAK5PFJet[ClosestPFJetToBHadronFromTBar],
               M.pyAK5PFJet[ClosestPFJetToBHadronFromTBar],
               M.pzAK5PFJet[ClosestPFJetToBHadronFromTBar]);
      }

      HBHadronPT.Fill(FinalBFromTP.GetPT());
      HBHadronPT.Fill(FinalBFromTBarP.GetPT());
      HClosestJetPT.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      HClosestJetPT.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      HBHadronPTVsClosestJetPT.Fill(FinalBFromTP.GetPT(), ClosestPFJetToBHadronFromTP.GetPT());
      HBHadronPTVsClosestJetPT.Fill(FinalBFromTBarP.GetPT(), ClosestPFJetToBHadronFromTBarP.GetPT());
      HBHadronVsClosestJetDEtaDPhi.Fill(FinalBFromTP.GetEta() - ClosestPFJetToBHadronFromTP.GetEta(),
         GetDPhi(FinalBFromTP, ClosestPFJetToBHadronFromTP));
      HBHadronVsClosestJetDEtaDPhi.Fill(FinalBFromTBarP.GetEta() - ClosestPFJetToBHadronFromTBarP.GetEta(),
         GetDPhi(FinalBFromTBarP, ClosestPFJetToBHadronFromTBarP));

      // Calculate MR, R
      vector<FourVector> GoodJets;
      for(int i = 0; i < M.nAK5PFJet; i++)
      {
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

         if(M.pxAK5PFJet[i] * M.pxAK5PFJet[i] + M.pyAK5PFJet[i] * M.pyAK5PFJet[i] < 30 * 30)
            continue;
         if(M.etaAK5PFJet[i] > 2.4 || M.etaAK5PFJet[i] < -2.4)
            continue;

         GoodJets.push_back(FourVector(M.energyAK5PFJet[i], M.pxAK5PFJet[i], M.pyAK5PFJet[i], M.pzAK5PFJet[i]));
      }

      vector<FourVector> Hemispheres = SplitIntoGroups(GoodJets);

      Hemispheres[0][0] = Hemispheres[0].GetP();
      Hemispheres[1][0] = Hemispheres[1].GetP();

      double EventMR = GetMR(Hemispheres[0], Hemispheres[1]);
      double EventR = GetR(Hemispheres[0], Hemispheres[1],
         FourVector(M.energyPFMet[0], M.pxPFMet[0], M.pyPFMet[0], M.pzPFMet[0]));

      HMRVsRAll.Fill(EventMR, EventR);

      // For now on, select only events with 2 good b's and 2 good matches - and some minimum energy
      if(FinalBHadronFromT < 0 || FinalBHadronFromTBar < 0)   continue;
      if(FinalBFromTP.GetPT() < 30 || FinalBFromTBarP.GetPT() < 30)   continue;
      if(ClosestPFJetToBHadronFromTP.GetPT() < 30 || ClosestPFJetToBHadronFromTBarP.GetPT() < 30)   continue;
      if(GetDR(FinalBFromTP, ClosestPFJetToBHadronFromTP) > 0.3)   continue;
      if(GetDR(FinalBFromTBarP, ClosestPFJetToBHadronFromTBarP) > 0.3)   continue;
      
      HBHadronPTVsClosestJetPTSelected.Fill(FinalBFromTP.GetPT(), ClosestPFJetToBHadronFromTP.GetPT());
      HBHadronPTVsClosestJetPTSelected.Fill(FinalBFromTBarP.GetPT(), ClosestPFJetToBHadronFromTBarP.GetPT());
      HBHadronVsClosestJetDEtaDPhiSelected.Fill(FinalBFromTP.GetEta() - ClosestPFJetToBHadronFromTP.GetEta(),
         GetDPhi(FinalBFromTP, ClosestPFJetToBHadronFromTP));
      HBHadronVsClosestJetDEtaDPhiSelected.Fill(FinalBFromTBarP.GetEta() - ClosestPFJetToBHadronFromTBarP.GetEta(),
         GetDPhi(FinalBFromTBarP, ClosestPFJetToBHadronFromTBarP));

      HMRVsRSelected.Fill(EventMR, EventR);

      // B-tagging discribution
      HJetTCHE.Fill(TCHE[ClosestPFJetToBHadronFromT]);
      HJetTCHE.Fill(TCHE[ClosestPFJetToBHadronFromTBar]);
      HJetTCHP.Fill(TCHP[ClosestPFJetToBHadronFromT]);
      HJetTCHP.Fill(TCHP[ClosestPFJetToBHadronFromTBar]);
      HJetProbability.Fill(JetProbability[ClosestPFJetToBHadronFromT]);
      HJetProbability.Fill(JetProbability[ClosestPFJetToBHadronFromTBar]);
      HJetBProbability.Fill(JetBProbability[ClosestPFJetToBHadronFromT]);
      HJetBProbability.Fill(JetBProbability[ClosestPFJetToBHadronFromTBar]);
      HJetSSVHE.Fill(SSVHE[ClosestPFJetToBHadronFromT]);
      HJetSSVHE.Fill(SSVHE[ClosestPFJetToBHadronFromTBar]);
      HJetSSVHP.Fill(SSVHP[ClosestPFJetToBHadronFromT]);
      HJetSSVHP.Fill(SSVHP[ClosestPFJetToBHadronFromTBar]);
      HJetCSV.Fill(CSV[ClosestPFJetToBHadronFromT]);
      HJetCSV.Fill(CSV[ClosestPFJetToBHadronFromTBar]);
      HJetCSVM.Fill(CSVM[ClosestPFJetToBHadronFromT]);
      HJetCSVM.Fill(CSVM[ClosestPFJetToBHadronFromTBar]);
      
      HJetTCHEVsPT.Fill(TCHE[ClosestPFJetToBHadronFromT],
         ClosestPFJetToBHadronFromTP.GetPT());
      HJetTCHEVsPT.Fill(TCHE[ClosestPFJetToBHadronFromTBar],
         ClosestPFJetToBHadronFromTBarP.GetPT());
      HJetTCHPVsPT.Fill(TCHP[ClosestPFJetToBHadronFromT],
         ClosestPFJetToBHadronFromTP.GetPT());
      HJetTCHPVsPT.Fill(TCHP[ClosestPFJetToBHadronFromTBar],
         ClosestPFJetToBHadronFromTBarP.GetPT());
      HJetProbabilityVsPT.Fill(JetProbability[ClosestPFJetToBHadronFromT],
         ClosestPFJetToBHadronFromTP.GetPT());
      HJetProbabilityVsPT.Fill(JetProbability[ClosestPFJetToBHadronFromTBar],
         ClosestPFJetToBHadronFromTBarP.GetPT());
      HJetBProbabilityVsPT.Fill(JetBProbability[ClosestPFJetToBHadronFromT],
         ClosestPFJetToBHadronFromTP.GetPT());
      HJetBProbabilityVsPT.Fill(JetBProbability[ClosestPFJetToBHadronFromTBar],
         ClosestPFJetToBHadronFromTBarP.GetPT());
      HJetSSVHEVsPT.Fill(SSVHE[ClosestPFJetToBHadronFromT],
         ClosestPFJetToBHadronFromTP.GetPT());
      HJetSSVHEVsPT.Fill(SSVHE[ClosestPFJetToBHadronFromTBar],
         ClosestPFJetToBHadronFromTBarP.GetPT());
      HJetSSVHPVsPT.Fill(SSVHP[ClosestPFJetToBHadronFromT],
         ClosestPFJetToBHadronFromTP.GetPT());
      HJetSSVHPVsPT.Fill(SSVHP[ClosestPFJetToBHadronFromTBar],
         ClosestPFJetToBHadronFromTBarP.GetPT());
      HJetCSVVsPT.Fill(CSV[ClosestPFJetToBHadronFromT],
         ClosestPFJetToBHadronFromTP.GetPT());
      HJetCSVVsPT.Fill(CSV[ClosestPFJetToBHadronFromTBar],
         ClosestPFJetToBHadronFromTBarP.GetPT());
      HJetCSVMVsPT.Fill(CSVM[ClosestPFJetToBHadronFromT],
         ClosestPFJetToBHadronFromTP.GetPT());
      HJetCSVMVsPT.Fill(CSVM[ClosestPFJetToBHadronFromTBar],
         ClosestPFJetToBHadronFromTBarP.GetPT());

      if(TCHE[ClosestPFJetToBHadronFromT] < TCHECut)
         HPTLowTCHE.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      else
         HPTHighTCHE.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      if(TCHE[ClosestPFJetToBHadronFromTBar] < TCHECut)
         HPTLowTCHE.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      else
         HPTHighTCHE.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      if(TCHP[ClosestPFJetToBHadronFromT] < TCHPCut)
         HPTLowTCHP.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      else
         HPTHighTCHP.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      if(TCHP[ClosestPFJetToBHadronFromTBar] < TCHPCut)
         HPTLowTCHP.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      else
         HPTHighTCHP.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      if(JetProbability[ClosestPFJetToBHadronFromT] < JetProbabilityCut)
         HPTLowJetProbability.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      else
         HPTHighJetProbability.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      if(JetProbability[ClosestPFJetToBHadronFromTBar] < JetProbabilityCut)
         HPTLowJetProbability.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      else
         HPTHighJetProbability.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      if(JetBProbability[ClosestPFJetToBHadronFromT] < JetBProbabilityCut)
         HPTLowJetBProbability.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      else
         HPTHighJetBProbability.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      if(JetBProbability[ClosestPFJetToBHadronFromTBar] < JetBProbabilityCut)
         HPTLowJetBProbability.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      else
         HPTHighJetBProbability.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      if(SSVHE[ClosestPFJetToBHadronFromT] < SSVHECut)
         HPTLowSSVHE.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      else
         HPTHighSSVHE.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      if(SSVHE[ClosestPFJetToBHadronFromTBar] < SSVHECut)
         HPTLowSSVHE.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      else
         HPTHighSSVHE.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      if(SSVHP[ClosestPFJetToBHadronFromT] < SSVHPCut)
         HPTLowSSVHP.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      else
         HPTHighSSVHP.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      if(SSVHP[ClosestPFJetToBHadronFromTBar] < SSVHPCut)
         HPTLowSSVHP.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      else
         HPTHighSSVHP.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      if(CSV[ClosestPFJetToBHadronFromT] < CSVCut)
         HPTLowCSV.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      else
         HPTHighCSV.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      if(CSV[ClosestPFJetToBHadronFromTBar] < CSVCut)
         HPTLowCSV.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      else
         HPTHighCSV.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      if(CSVM[ClosestPFJetToBHadronFromT] < CSVMCut)
         HPTLowCSVM.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      else
         HPTHighCSVM.Fill(ClosestPFJetToBHadronFromTP.GetPT());
      if(CSVM[ClosestPFJetToBHadronFromTBar] < CSVMCut)
         HPTLowCSVM.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      else
         HPTHighCSVM.Fill(ClosestPFJetToBHadronFromTBarP.GetPT());
      
      HJetTCHEVsEta.Fill(TCHE[ClosestPFJetToBHadronFromT], ClosestPFJetToBHadronFromTP.GetEta());
      HJetTCHEVsEta.Fill(TCHE[ClosestPFJetToBHadronFromTBar], ClosestPFJetToBHadronFromTBarP.GetEta());
      HJetTCHPVsEta.Fill(TCHP[ClosestPFJetToBHadronFromT], ClosestPFJetToBHadronFromTP.GetEta());
      HJetTCHPVsEta.Fill(TCHP[ClosestPFJetToBHadronFromTBar], ClosestPFJetToBHadronFromTBarP.GetEta());
      HJetProbabilityVsEta.Fill(JetProbability[ClosestPFJetToBHadronFromT], ClosestPFJetToBHadronFromTP.GetEta());
      HJetProbabilityVsEta.Fill(JetProbability[ClosestPFJetToBHadronFromTBar], ClosestPFJetToBHadronFromTBarP.GetEta());
      HJetBProbabilityVsEta.Fill(JetBProbability[ClosestPFJetToBHadronFromT], ClosestPFJetToBHadronFromTP.GetEta());
      HJetBProbabilityVsEta.Fill(JetBProbability[ClosestPFJetToBHadronFromTBar], ClosestPFJetToBHadronFromTBarP.GetEta());
      HJetSSVHEVsEta.Fill(SSVHE[ClosestPFJetToBHadronFromT], ClosestPFJetToBHadronFromTP.GetEta());
      HJetSSVHEVsEta.Fill(SSVHE[ClosestPFJetToBHadronFromTBar], ClosestPFJetToBHadronFromTBarP.GetEta());
      HJetSSVHPVsEta.Fill(SSVHP[ClosestPFJetToBHadronFromT], ClosestPFJetToBHadronFromTP.GetEta());
      HJetSSVHPVsEta.Fill(SSVHP[ClosestPFJetToBHadronFromTBar], ClosestPFJetToBHadronFromTBarP.GetEta());
      HJetCSVVsEta.Fill(CSV[ClosestPFJetToBHadronFromT], ClosestPFJetToBHadronFromTP.GetEta());
      HJetCSVVsEta.Fill(CSV[ClosestPFJetToBHadronFromTBar], ClosestPFJetToBHadronFromTBarP.GetEta());
      HJetCSVMVsEta.Fill(CSVM[ClosestPFJetToBHadronFromT], ClosestPFJetToBHadronFromTP.GetEta());
      HJetCSVMVsEta.Fill(CSVM[ClosestPFJetToBHadronFromTBar], ClosestPFJetToBHadronFromTBarP.GetEta());
      
      if(TCHE[ClosestPFJetToBHadronFromT] < TCHECut)
         HEtaLowTCHE.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      else
         HEtaHighTCHE.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      if(TCHE[ClosestPFJetToBHadronFromTBar] < TCHECut)
         HEtaLowTCHE.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      else
         HEtaHighTCHE.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      if(TCHP[ClosestPFJetToBHadronFromT] < TCHPCut)
         HEtaLowTCHP.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      else
         HEtaHighTCHP.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      if(TCHP[ClosestPFJetToBHadronFromTBar] < TCHPCut)
         HEtaLowTCHP.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      else
         HEtaHighTCHP.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      if(JetProbability[ClosestPFJetToBHadronFromT] < JetProbabilityCut)
         HEtaLowJetProbability.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      else
         HEtaHighJetProbability.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      if(JetProbability[ClosestPFJetToBHadronFromTBar] < JetProbabilityCut)
         HEtaLowJetProbability.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      else
         HEtaHighJetProbability.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      if(JetBProbability[ClosestPFJetToBHadronFromT] < JetBProbabilityCut)
         HEtaLowJetBProbability.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      else
         HEtaHighJetBProbability.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      if(JetBProbability[ClosestPFJetToBHadronFromTBar] < JetBProbabilityCut)
         HEtaLowJetBProbability.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      else
         HEtaHighJetBProbability.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      if(SSVHE[ClosestPFJetToBHadronFromT] < SSVHECut)
         HEtaLowSSVHE.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      else
         HEtaHighSSVHE.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      if(SSVHE[ClosestPFJetToBHadronFromTBar] < SSVHECut)
         HEtaLowSSVHE.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      else
         HEtaHighSSVHE.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      if(SSVHP[ClosestPFJetToBHadronFromT] < SSVHPCut)
         HEtaLowSSVHP.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      else
         HEtaHighSSVHP.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      if(SSVHP[ClosestPFJetToBHadronFromTBar] < SSVHPCut)
         HEtaLowSSVHP.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      else
         HEtaHighSSVHP.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      if(CSV[ClosestPFJetToBHadronFromT] < CSVCut)
         HEtaLowCSV.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      else
         HEtaHighCSV.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      if(CSV[ClosestPFJetToBHadronFromTBar] < CSVCut)
         HEtaLowCSV.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      else
         HEtaHighCSV.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      if(CSVM[ClosestPFJetToBHadronFromT] < CSVMCut)
         HEtaLowCSVM.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      else
         HEtaHighCSVM.Fill(ClosestPFJetToBHadronFromTP.GetEta());
      if(CSVM[ClosestPFJetToBHadronFromTBar] < CSVMCut)
         HEtaLowCSVM.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());
      else
         HEtaHighCSVM.Fill(ClosestPFJetToBHadronFromTBarP.GetEta());

      if(TCHE[ClosestPFJetToBHadronFromT] < TCHECut
         && TCHE[ClosestPFJetToBHadronFromTBar] < TCHECut)
      {
         HMRLowTCHE.Fill(EventMR);
         HRLowTCHE.Fill(EventR);
         HMRVsRLowTCHE.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRLowTCHE_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRLowTCHE_R05.Fill(EventMR);
      }
      else if(TCHE[ClosestPFJetToBHadronFromT] > TCHECut
         && TCHE[ClosestPFJetToBHadronFromTBar] > TCHECut)
      {
         HMRHighTCHE.Fill(EventMR);
         HRHighTCHE.Fill(EventR);
         HMRVsRHighTCHE.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRHighTCHE_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRHighTCHE_R05.Fill(EventMR);
      }
      else
      {
         HMRMixTCHE.Fill(EventMR);
         HRMixTCHE.Fill(EventR);
         HMRVsRMixTCHE.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRMixTCHE_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRMixTCHE_R05.Fill(EventMR);
      }
      if(TCHP[ClosestPFJetToBHadronFromT] < TCHPCut
         && TCHP[ClosestPFJetToBHadronFromTBar] < TCHPCut)
      {
         HMRLowTCHP.Fill(EventMR);
         HRLowTCHP.Fill(EventR);
         HMRVsRLowTCHP.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRLowTCHP_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRLowTCHP_R05.Fill(EventMR);
      }
      else if(TCHP[ClosestPFJetToBHadronFromT] > TCHPCut
         && TCHP[ClosestPFJetToBHadronFromTBar] > TCHPCut)
      {
         HMRHighTCHP.Fill(EventMR);
         HRHighTCHP.Fill(EventR);
         HMRVsRHighTCHP.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRHighTCHP_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRHighTCHP_R05.Fill(EventMR);
      }
      else
      {
         HMRMixTCHP.Fill(EventMR);
         HRMixTCHP.Fill(EventR);
         HMRVsRMixTCHP.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRMixTCHP_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRMixTCHP_R05.Fill(EventMR);
      }
      if(JetProbability[ClosestPFJetToBHadronFromT] < JetProbabilityCut
         && JetProbability[ClosestPFJetToBHadronFromTBar] < JetProbabilityCut)
      {
         HMRLowJetProbability.Fill(EventMR);
         HRLowJetProbability.Fill(EventR);
         HMRVsRLowJetProbability.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRLowJetProbability_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRLowJetProbability_R05.Fill(EventMR);
      }
      else if(JetProbability[ClosestPFJetToBHadronFromT] > JetProbabilityCut
         && JetProbability[ClosestPFJetToBHadronFromTBar] > JetProbabilityCut)
      {
         HMRHighJetProbability.Fill(EventMR);
         HRHighJetProbability.Fill(EventR);
         HMRVsRHighJetProbability.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRHighJetProbability_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRHighJetProbability_R05.Fill(EventMR);
      }
      else
      {
         HMRMixJetProbability.Fill(EventMR);
         HRMixJetProbability.Fill(EventR);
         HMRVsRMixJetProbability.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRMixJetProbability_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRMixJetProbability_R05.Fill(EventMR);
      }
      if(JetBProbability[ClosestPFJetToBHadronFromT] < JetBProbabilityCut
         && JetBProbability[ClosestPFJetToBHadronFromTBar] < JetBProbabilityCut)
      {
         HMRLowJetBProbability.Fill(EventMR);
         HRLowJetBProbability.Fill(EventR);
         HMRVsRLowJetBProbability.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRLowJetBProbability_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRLowJetBProbability_R05.Fill(EventMR);
      }
      else if(JetBProbability[ClosestPFJetToBHadronFromT] > JetBProbabilityCut
         && JetBProbability[ClosestPFJetToBHadronFromTBar] > JetBProbabilityCut)
      {
         HMRHighJetBProbability.Fill(EventMR);
         HRHighJetBProbability.Fill(EventR);
         HMRVsRHighJetBProbability.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRHighJetBProbability_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRHighJetBProbability_R05.Fill(EventMR);
      }
      else
      {
         HMRMixJetBProbability.Fill(EventMR);
         HRMixJetBProbability.Fill(EventR);
         HMRVsRMixJetBProbability.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRMixJetBProbability_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRMixJetBProbability_R05.Fill(EventMR);
      }
      if(SSVHE[ClosestPFJetToBHadronFromT] < SSVHECut
         && SSVHE[ClosestPFJetToBHadronFromTBar] < SSVHECut)
      {
         HMRLowSSVHE.Fill(EventMR);
         HRLowSSVHE.Fill(EventR);
         HMRVsRLowSSVHE.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRLowSSVHE_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRLowSSVHE_R05.Fill(EventMR);
      }
      else if(SSVHE[ClosestPFJetToBHadronFromT] > SSVHECut
         && SSVHE[ClosestPFJetToBHadronFromTBar] > SSVHECut)
      {
         HMRHighSSVHE.Fill(EventMR);
         HRHighSSVHE.Fill(EventR);
         HMRVsRHighSSVHE.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRHighSSVHE_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRHighSSVHE_R05.Fill(EventMR);
      }
      else
      {
         HMRMixSSVHE.Fill(EventMR);
         HRMixSSVHE.Fill(EventR);
         HMRVsRMixSSVHE.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRMixSSVHE_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRMixSSVHE_R05.Fill(EventMR);
      }
      if(SSVHP[ClosestPFJetToBHadronFromT] < SSVHPCut
         && SSVHP[ClosestPFJetToBHadronFromTBar] < SSVHPCut)
      {
         HMRLowSSVHP.Fill(EventMR);
         HRLowSSVHP.Fill(EventR);
         HMRVsRLowSSVHP.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRLowSSVHP_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRLowSSVHP_R05.Fill(EventMR);
      }
      else if(SSVHP[ClosestPFJetToBHadronFromT] > SSVHPCut
         && SSVHP[ClosestPFJetToBHadronFromTBar] > SSVHPCut)
      {
         HMRHighSSVHP.Fill(EventMR);
         HRHighSSVHP.Fill(EventR);
         HMRVsRHighSSVHP.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRHighSSVHP_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRHighSSVHP_R05.Fill(EventMR);
      }
      else
      {
         HMRMixSSVHP.Fill(EventMR);
         HRMixSSVHP.Fill(EventR);
         HMRVsRMixSSVHP.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRMixSSVHP_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRMixSSVHP_R05.Fill(EventMR);
      }
      if(CSV[ClosestPFJetToBHadronFromT] < CSVCut
         && CSV[ClosestPFJetToBHadronFromTBar] < CSVCut)
      {
         HMRLowCSV.Fill(EventMR);
         HRLowCSV.Fill(EventR);
         HMRVsRLowCSV.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRLowCSV_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRLowCSV_R05.Fill(EventMR);
      }
      else if(CSV[ClosestPFJetToBHadronFromT] > CSVCut
         && CSV[ClosestPFJetToBHadronFromTBar] > CSVCut)
      {
         HMRHighCSV.Fill(EventMR);
         HRHighCSV.Fill(EventR);
         HMRVsRHighCSV.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRHighCSV_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRHighCSV_R05.Fill(EventMR);
      }
      else
      {
         HMRMixCSV.Fill(EventMR);
         HRMixCSV.Fill(EventR);
         HMRVsRMixCSV.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRMixCSV_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRMixCSV_R05.Fill(EventMR);
      }
      if(CSVM[ClosestPFJetToBHadronFromT] < CSVMCut
         && CSVM[ClosestPFJetToBHadronFromTBar] < CSVMCut)
      {
         HMRLowCSVM.Fill(EventMR);
         HRLowCSVM.Fill(EventR);
         HMRVsRLowCSVM.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRLowCSVM_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRLowCSVM_R05.Fill(EventMR);
      }
      else if(CSVM[ClosestPFJetToBHadronFromT] > CSVMCut
         && CSVM[ClosestPFJetToBHadronFromTBar] > CSVMCut)
      {
         HMRHighCSVM.Fill(EventMR);
         HRHighCSVM.Fill(EventR);
         HMRVsRHighCSVM.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRHighCSVM_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRHighCSVM_R05.Fill(EventMR);
      }
      else
      {
         HMRMixCSVM.Fill(EventMR);
         HRMixCSVM.Fill(EventR);
         HMRVsRMixCSVM.Fill(EventMR, EventR);
         if(EventR > 0.3)   HMRMixCSVM_R03.Fill(EventMR);
         if(EventR > 0.5)   HMRMixCSVM_R05.Fill(EventMR);
      }
   }

   // Write to output
   PsFile.AddTextPage("Basic information");
   PsFile.InsertNamedDestination("BasicInformation");
   PsFile.AddPlot(HBunchCrossing, "", true);
   PsFile.AddPlot(HNPV, "hist text00", true);
   PsFile.AddPlot(HPVXVsPVY, "colz", false, true);
   PsFile.AddPlot(HPVTVsPVZ, "colz", false, true);

   PsFile.AddTextPage("Tracing b-hadron");
   PsFile.InsertNamedDestination("Tracing");
   PsFile.AddPlot(HBHadronPT, "", true);
   PsFile.AddPlot(HClosestJetPT, "", true);
   PsFile.AddPlot(HBHadronPTVsClosestJetPT, "colz", false, true);
   PsFile.AddPlot(HBHadronVsClosestJetDEtaDPhi, "colz", false, true);
   PsFile.AddPlot(HBHadronPTVsClosestJetPTSelected, "colz", false, true);
   PsFile.AddPlot(HBHadronVsClosestJetDEtaDPhiSelected, "colz", false, true);

   PsFile.AddTextPage("B-tagging distributions");
   PsFile.InsertNamedDestination("BTagging");

   PsFile.AddPlot(HJetTCHE, "", true);
   PsFile.AddPlot(HJetTCHEVsPT, "colz", false, true);
   PsFile.AddPlot(HJetTCHEVsEta, "colz", false, true);
   PsFile.AddPlot(HPTLowTCHE, "", true);
   PsFile.AddPlot(HPTHighTCHE, "", true);
   PsFile.AddPlot(HEtaLowTCHE, "", false);
   PsFile.AddPlot(HEtaHighTCHE, "", false);

   PsFile.AddPlot(HJetTCHP, "", true);
   PsFile.AddPlot(HJetTCHPVsPT, "colz", false, true);
   PsFile.AddPlot(HJetTCHPVsEta, "colz", false, true);
   PsFile.AddPlot(HPTLowTCHP, "", true);
   PsFile.AddPlot(HPTHighTCHP, "", true);
   PsFile.AddPlot(HEtaLowTCHP, "", false);
   PsFile.AddPlot(HEtaHighTCHP, "", false);

   PsFile.AddPlot(HJetProbability, "", true);
   PsFile.AddPlot(HJetProbabilityVsPT, "colz", false, true);
   PsFile.AddPlot(HJetProbabilityVsEta, "colz", false, true);
   PsFile.AddPlot(HPTLowJetProbability, "", true);
   PsFile.AddPlot(HPTHighJetProbability, "", true);
   PsFile.AddPlot(HEtaLowJetProbability, "", false);
   PsFile.AddPlot(HEtaHighJetProbability, "", false);

   PsFile.AddPlot(HJetBProbability, "", true);
   PsFile.AddPlot(HJetBProbabilityVsPT, "colz", false, true);
   PsFile.AddPlot(HJetBProbabilityVsEta, "colz", false, true);
   PsFile.AddPlot(HPTLowJetBProbability, "", true);
   PsFile.AddPlot(HPTHighJetBProbability, "", true);
   PsFile.AddPlot(HEtaLowJetBProbability, "", false);
   PsFile.AddPlot(HEtaHighJetBProbability, "", false);

   PsFile.AddPlot(HJetSSVHE, "", true);
   PsFile.AddPlot(HJetSSVHEVsPT, "colz", false, true);
   PsFile.AddPlot(HJetSSVHEVsEta, "colz", false, true);
   PsFile.AddPlot(HPTLowSSVHE, "", true);
   PsFile.AddPlot(HPTHighSSVHE, "", true);
   PsFile.AddPlot(HEtaLowSSVHE, "", false);
   PsFile.AddPlot(HEtaHighSSVHE, "", false);

   PsFile.AddPlot(HJetSSVHP, "", true);
   PsFile.AddPlot(HJetSSVHPVsPT, "colz", false, true);
   PsFile.AddPlot(HJetSSVHPVsEta, "colz", false, true);
   PsFile.AddPlot(HPTLowSSVHP, "", true);
   PsFile.AddPlot(HPTHighSSVHP, "", true);
   PsFile.AddPlot(HEtaLowSSVHP, "", false);
   PsFile.AddPlot(HEtaHighSSVHP, "", false);

   PsFile.AddPlot(HJetCSV, "", true);
   PsFile.AddPlot(HJetCSVVsPT, "colz", false, true);
   PsFile.AddPlot(HJetCSVVsEta, "colz", false, true);
   PsFile.AddPlot(HPTLowCSV, "", true);
   PsFile.AddPlot(HPTHighCSV, "", true);
   PsFile.AddPlot(HEtaLowCSV, "", false);
   PsFile.AddPlot(HEtaHighCSV, "", false);

   PsFile.AddPlot(HJetCSVM, "", true);
   PsFile.AddPlot(HJetCSVMVsPT, "colz", false, true);
   PsFile.AddPlot(HJetCSVMVsEta, "colz", false, true);
   PsFile.AddPlot(HPTLowCSVM, "", true);
   PsFile.AddPlot(HPTHighCSVM, "", true);
   PsFile.AddPlot(HEtaLowCSVM, "", false);
   PsFile.AddPlot(HEtaHighCSVM, "", false);

   PsFile.AddTextPage("MR and R distributions");
   PsFile.InsertNamedDestination("ChrisVariable");
   PsFile.AddPlot(HMRVsRAll, "colz", false, true);
   PsFile.AddPlot(HMRVsRSelected, "colz", false, true);
   OverlayHistograms(PsFile, &HMRLowTCHE, &HMRMixTCHE, &HMRHighTCHE, true);
   OverlayHistograms(PsFile, &HMRLowTCHE_R03, &HMRMixTCHE_R03, &HMRHighTCHE_R03, true);
   OverlayHistograms(PsFile, &HMRLowTCHE_R05, &HMRMixTCHE_R05, &HMRHighTCHE_R05, true);
   OverlayHistograms(PsFile, &HRLowTCHE, &HRMixTCHE, &HRHighTCHE, true);
   OverlayHistograms(PsFile, &HRLowTCHE, &HRMixTCHE, &HRHighTCHE, false);
   PsFile.AddPlot(HMRVsRLowTCHE, "colz", false, true);
   PsFile.AddPlot(HMRVsRMixTCHE, "colz", false, true);
   PsFile.AddPlot(HMRVsRHighTCHE, "colz", false, true);
   OverlayHistograms(PsFile, &HMRLowTCHP, &HMRMixTCHP, &HMRHighTCHP, true);
   OverlayHistograms(PsFile, &HMRLowTCHP_R03, &HMRMixTCHP_R03, &HMRHighTCHP_R03, true);
   OverlayHistograms(PsFile, &HMRLowTCHP_R05, &HMRMixTCHP_R05, &HMRHighTCHP_R05, true);
   OverlayHistograms(PsFile, &HRLowTCHP, &HRMixTCHP, &HRHighTCHP, true);
   OverlayHistograms(PsFile, &HRLowTCHP, &HRMixTCHP, &HRHighTCHP, false);
   PsFile.AddPlot(HMRVsRLowTCHP, "colz", false, true);
   PsFile.AddPlot(HMRVsRMixTCHP, "colz", false, true);
   PsFile.AddPlot(HMRVsRHighTCHP, "colz", false, true);
   OverlayHistograms(PsFile, &HMRLowJetProbability, &HMRMixJetProbability, &HMRHighJetProbability, true);
   OverlayHistograms(PsFile, &HMRLowJetProbability_R03, &HMRMixJetProbability_R03, &HMRHighJetProbability_R03, true);
   OverlayHistograms(PsFile, &HMRLowJetProbability_R05, &HMRMixJetProbability_R05, &HMRHighJetProbability_R05, true);
   OverlayHistograms(PsFile, &HRLowJetProbability, &HRMixJetProbability, &HRHighJetProbability, true);
   OverlayHistograms(PsFile, &HRLowJetProbability, &HRMixJetProbability, &HRHighJetProbability, false);
   PsFile.AddPlot(HMRVsRLowJetProbability, "colz", false, true);
   PsFile.AddPlot(HMRVsRMixJetProbability, "colz", false, true);
   PsFile.AddPlot(HMRVsRHighJetProbability, "colz", false, true);
   OverlayHistograms(PsFile, &HMRLowJetBProbability, &HMRMixJetBProbability, &HMRHighJetBProbability, true);
   OverlayHistograms(PsFile, &HMRLowJetBProbability_R03, &HMRMixJetBProbability_R03, &HMRHighJetBProbability_R03, true);
   OverlayHistograms(PsFile, &HMRLowJetBProbability_R05, &HMRMixJetBProbability_R05, &HMRHighJetBProbability_R05, true);
   OverlayHistograms(PsFile, &HRLowJetBProbability, &HRMixJetBProbability, &HRHighJetBProbability, true);
   OverlayHistograms(PsFile, &HRLowJetBProbability, &HRMixJetBProbability, &HRHighJetBProbability, false);
   PsFile.AddPlot(HMRVsRLowJetBProbability, "colz", false, true);
   PsFile.AddPlot(HMRVsRMixJetBProbability, "colz", false, true);
   PsFile.AddPlot(HMRVsRHighJetBProbability, "colz", false, true);
   OverlayHistograms(PsFile, &HMRLowSSVHE, &HMRMixSSVHE, &HMRHighSSVHE, true);
   OverlayHistograms(PsFile, &HMRLowSSVHE_R03, &HMRMixSSVHE_R03, &HMRHighSSVHE_R03, true);
   OverlayHistograms(PsFile, &HMRLowSSVHE_R05, &HMRMixSSVHE_R05, &HMRHighSSVHE_R05, true);
   OverlayHistograms(PsFile, &HRLowSSVHE, &HRMixSSVHE, &HRHighSSVHE, true);
   OverlayHistograms(PsFile, &HRLowSSVHE, &HRMixSSVHE, &HRHighSSVHE, false);
   PsFile.AddPlot(HMRVsRLowSSVHE, "colz", false, true);
   PsFile.AddPlot(HMRVsRMixSSVHE, "colz", false, true);
   PsFile.AddPlot(HMRVsRHighSSVHE, "colz", false, true);
   OverlayHistograms(PsFile, &HMRLowSSVHP, &HMRMixSSVHP, &HMRHighSSVHP, true);
   OverlayHistograms(PsFile, &HMRLowSSVHP_R03, &HMRMixSSVHP_R03, &HMRHighSSVHP_R03, true);
   OverlayHistograms(PsFile, &HMRLowSSVHP_R05, &HMRMixSSVHP_R05, &HMRHighSSVHP_R05, true);
   OverlayHistograms(PsFile, &HRLowSSVHP, &HRMixSSVHP, &HRHighSSVHP, true);
   OverlayHistograms(PsFile, &HRLowSSVHP, &HRMixSSVHP, &HRHighSSVHP, false);
   PsFile.AddPlot(HMRVsRLowSSVHP, "colz", false, true);
   PsFile.AddPlot(HMRVsRMixSSVHP, "colz", false, true);
   PsFile.AddPlot(HMRVsRHighSSVHP, "colz", false, true);
   OverlayHistograms(PsFile, &HMRLowCSV, &HMRMixCSV, &HMRHighCSV, true);
   OverlayHistograms(PsFile, &HMRLowCSV_R03, &HMRMixCSV_R03, &HMRHighCSV_R03, true);
   OverlayHistograms(PsFile, &HMRLowCSV_R05, &HMRMixCSV_R05, &HMRHighCSV_R05, true);
   OverlayHistograms(PsFile, &HRLowCSV, &HRMixCSV, &HRHighCSV, true);
   OverlayHistograms(PsFile, &HRLowCSV, &HRMixCSV, &HRHighCSV, false);
   PsFile.AddPlot(HMRVsRLowCSV, "colz", false, true);
   PsFile.AddPlot(HMRVsRMixCSV, "colz", false, true);
   PsFile.AddPlot(HMRVsRHighCSV, "colz", false, true);
   OverlayHistograms(PsFile, &HMRLowCSVM, &HMRMixCSVM, &HMRHighCSVM, true);
   OverlayHistograms(PsFile, &HMRLowCSVM_R03, &HMRMixCSVM_R03, &HMRHighCSVM_R03, true);
   OverlayHistograms(PsFile, &HMRLowCSVM_R05, &HMRMixCSVM_R05, &HMRHighCSVM_R05, true);
   OverlayHistograms(PsFile, &HRLowCSVM, &HRMixCSVM, &HRHighCSVM, true);
   OverlayHistograms(PsFile, &HRLowCSVM, &HRMixCSVM, &HRHighCSVM, false);
   PsFile.AddPlot(HMRVsRLowCSVM, "colz", false, true);
   PsFile.AddPlot(HMRVsRMixCSVM, "colz", false, true);
   PsFile.AddPlot(HMRVsRHighCSVM, "colz", false, true);

   TCanvas C("C", "C", 1024, 512);
   C.Divide(2);
   C.cd(1);
   HMRLowTCHE.SetStats(0);
   HMRMixTCHE.SetStats(0);
   HMRHighTCHE.SetStats(0);
   HMRLowTCHE.SetTitle("MR, different number of successful tags");
   HMRLowTCHE.GetXaxis()->SetTitle("MR");
   HMRLowTCHE.GetYaxis()->SetTitle("a.u.");
   HMRLowTCHE.DrawNormalized();
   HMRMixTCHE.DrawNormalized("same");
   HMRHighTCHE.DrawNormalized("same");
   C.cd(1)->SetLogy();
   C.cd(2);
   HRLowTCHE.SetStats(0);
   HRMixTCHE.SetStats(0);
   HRHighTCHE.SetStats(0);
   HRLowTCHE.SetTitle("R, different number of successful tags");
   HRLowTCHE.GetXaxis()->SetTitle("R");
   HRLowTCHE.GetYaxis()->SetTitle("a.u.");
   HRLowTCHE.DrawNormalized();
   HRMixTCHE.DrawNormalized("same");
   HRHighTCHE.DrawNormalized("same");
   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.AddEntry(&HMRLowTCHE, "No tag", "l");
   Legend.AddEntry(&HMRMixTCHE, "One tag", "l");
   Legend.AddEntry(&HMRHighTCHE, "Two tags", "l");
   Legend.SetFillColor(0);
   Legend.Draw();
   C.cd(2)->SetLogy();
   C.SaveAs("TCHETagging.png");
   C.SaveAs("TCHETagging.C");
   C.SaveAs("TCHETagging.eps");

   // Close things 
   PsFile.AddTimeStampPage();
   PsFile.Close();
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
bool IsGoodMuon(NTPTreeMessenger &M, int MuonIndex)
{
   if(MuonIndex >= M.nMuon)   // what!?
      return false;

   int TrackIndex = M.trackIndexMuon[MuonIndex];
   int GlobalTrackIndex = M.combinedTrackIndexMuon[MuonIndex];
   int MuonTrackIndex = M.standAloneTrackIndexMuon[MuonIndex];

   if(TrackIndex < 0 || TrackIndex >= M.nTrack)
      return false;
   if(GlobalTrackIndex < 0 || TrackIndex >= M.nGlobalMuonTrack)
      return false;
   if(MuonTrackIndex < 0 || MuonTrackIndex >= M.nSTAMuonTrack)
      return false;

   FourVector MuonP(M.energyMuon[MuonIndex], M.pxMuon[MuonIndex], M.pyMuon[MuonIndex], M.pzMuon[MuonIndex]);
   FourVector PV(1, M.PVxPV[0], M.PVyPV[0], M.PVzPV[0]);
   FourVector MuonV(1, M.vertexXMuon[MuonIndex], M.vertexYMuon[MuonIndex], M.vertexZMuon[MuonIndex]);
   FourVector DeltaV = MuonV - PV;

   double Dxy = (-DeltaV[1] * MuonP[2] + DeltaV[2] * MuonP[1]) / MuonP.GetPT();

   if((M.muonIdMuon[MuonIndex] >> 13) % 2 == 0)   // not global muon
      return false;
   if((M.muonIdMuon[MuonIndex] >> 11) % 2 == 0)   // not tracker muon
      return false;
   if(M.trackNormalizedChi2GlobalMuonTrack[GlobalTrackIndex] > 10)
      return false;
   if(M.numberOfValidPixelBarrelHitsTrack[TrackIndex] + M.numberOfValidPixelEndcapHitsTrack[TrackIndex]
      + M.numberOfValidStripTIBHitsTrack[TrackIndex] + M.numberOfValidStripTOBHitsTrack[TrackIndex]
      + M.numberOfValidStripTIDHitsTrack[TrackIndex] + M.numberOfValidStripTECHitsTrack[TrackIndex] < 10)
      return false;
   if(M.numberOfValidPixelBarrelHitsTrack[TrackIndex] + M.numberOfValidPixelEndcapHitsTrack[TrackIndex] < 1)
      return false;
   if(M.trackValidHitsSTAMuonTrack[MuonTrackIndex] < 1)
      return false;
   if(Dxy > 0.2)
      return false;
   if(M.sumPt03Muon[MuonIndex] + M.emEt03Muon[MuonIndex] + M.hadEt03Muon[MuonIndex] > 0.1 * MuonP.GetPT())
      return false;

   return true;
}
//---------------------------------------------------------------------------
void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, bool LogY)
{
   TCanvas Canvas;

   H1->SetLineColor(1);
   H1->DrawNormalized();

   H2->SetLineColor(2);
   H2->DrawNormalized("same");

   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.AddEntry(H1, "Low", "l");
   legend.AddEntry(H2, "High", "l");
   legend.SetFillColor(0);
   legend.Draw();

   if(LogY == true)
      Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
}
//---------------------------------------------------------------------------
void OverlayHistograms(PsFileHelper &PsFile, TH1D *H1, TH1D *H2, TH1D *H3, bool LogY)
{
   TCanvas Canvas;

   H1->SetLineColor(1);
   H1->DrawNormalized();

   H2->SetLineColor(2);
   H2->DrawNormalized("same");
   
   H3->SetLineColor(3);
   H3->DrawNormalized("same");

   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.AddEntry(H1, "Low", "l");
   legend.AddEntry(H2, "Mixed", "l");
   legend.AddEntry(H3, "High", "l");
   legend.SetFillColor(0);
   legend.Draw();

   if(LogY == true)
      Canvas.SetLogy();

   PsFile.AddCanvas(Canvas);
}
//---------------------------------------------------------------------------








