#include <iostream>
#include <map>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
using namespace fastjet;

#include "TFile.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TH2D.h"

#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"
#include "ProgressBar.h"

#include "Messenger.h"

#define MAXJET 1000

int main(int argc, char *argv[])
{
   ClusterSequence::set_fastjet_banner_stream(NULL);

   // Read inputs from command line
   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input", "");
   string OutputFileName         = CL.Get("Output", "Result.root");
   string JetTreeName            = CL.Get("Tree", "akCs4PFJetAnalyzer/t");
   double MinPTForTrack         = CL.GetDouble("MinPTForTrack", 30);

   // Prepare output histograms and graphs
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   map<string, TH1D *> H1;
   map<string, TH2D *> H2;
   map<string, TProfile *> P1;

   H1["N"] = new TH1D("HN", ";;", 1, 0, 1);

   // Jet distributions
   H1["JetPT"] = new TH1D("HJetPT", ";Jet PT;", 100, 0, 200);
   
   H2["JetEtaPhiPT30"] = new TH2D("HJetEtaPhiPT30", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT50"] = new TH2D("HJetEtaPhiPT50", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT75"] = new TH2D("HJetEtaPhiPT75", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT100"] = new TH2D("HJetEtaPhiPT100", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT125"] = new TH2D("HJetEtaPhiPT125", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   H1["JetEtaPT30"] = new TH1D("HJetEtaPT30", ";#eta;", 100, -2.5, 2.5);
   H1["JetEtaPT50"] = new TH1D("HJetEtaPT50", ";#eta;", 100, -2.5, 2.5);
   H1["JetEtaPT75"] = new TH1D("HJetEtaPT75", ";#eta;", 100, -2.5, 2.5);
   H1["JetEtaPT100"] = new TH1D("HJetEtaPT100", ";#eta;", 100, -2.5, 2.5);
   H1["JetEtaPT125"] = new TH1D("HJetEtaPT125", ";#eta;", 100, -2.5, 2.5);
   
   H1["JetPTEtaN25N15"] = new TH1D("HJetPTEtaN25N15", ";Jet PT;", 100, 0, 200);
   H1["JetPTEtaN15N00"] = new TH1D("HJetPTEtaN15N00", ";Jet PT;", 100, 0, 200);
   H1["JetPTEtaP00P15"] = new TH1D("HJetPTEtaP00P15", ";Jet PT;", 100, 0, 200);
   H1["JetPTEtaP15P25"] = new TH1D("HJetPTEtaP15P25", ";Jet PT;", 100, 0, 200);

   H1["JetPhiPT30EtaN25N15"] = new TH1D("HJetPhiPT30EtaN25N15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT30EtaN15N00"] = new TH1D("HJetPhiPT30EtaN15N00", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT30EtaP00P15"] = new TH1D("HJetPhiPT30EtaP00P15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT30EtaP15P25"] = new TH1D("HJetPhiPT30EtaP15P25", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT50EtaN25N15"] = new TH1D("HJetPhiPT50EtaN25N15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT50EtaN15N00"] = new TH1D("HJetPhiPT50EtaN15N00", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT50EtaP00P15"] = new TH1D("HJetPhiPT50EtaP00P15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT50EtaP15P25"] = new TH1D("HJetPhiPT50EtaP15P25", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT75EtaN25N15"] = new TH1D("HJetPhiPT75EtaN25N15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT75EtaN15N00"] = new TH1D("HJetPhiPT75EtaN15N00", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT75EtaP00P15"] = new TH1D("HJetPhiPT75EtaP00P15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT75EtaP15P25"] = new TH1D("HJetPhiPT75EtaP15P25", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT100EtaN25N15"] = new TH1D("HJetPhiPT100EtaN25N15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT100EtaN15N00"] = new TH1D("HJetPhiPT100EtaN15N00", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT100EtaP00P15"] = new TH1D("HJetPhiPT100EtaP00P15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT100EtaP15P25"] = new TH1D("HJetPhiPT100EtaP15P25", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT125EtaN25N15"] = new TH1D("HJetPhiPT125EtaN25N15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT125EtaN15N00"] = new TH1D("HJetPhiPT125EtaN15N00", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT125EtaP00P15"] = new TH1D("HJetPhiPT125EtaP00P15", ";Jet #phi;", 100, -M_PI, M_PI);
   H1["JetPhiPT125EtaP15P25"] = new TH1D("HJetPhiPT125EtaP15P25", ";Jet #phi;", 100, -M_PI, M_PI);

   H2["RawPTVsJEC"] = new TH2D("HRawPTVsJEC", ";Raw PT;JEC", 100, 0, 200, 100, 0, 2.5);
   H2["RawPTVsJetPT"] = new TH2D("HRawPTVsJetPT", ";Raw PT;JEC", 100, 0, 200, 100, 0, 200);

   P1["JetEtaVsResponseGenPT30PT50"] = new TProfile("HJetEtaVsResponseGenPT30PT50", ";#eta;<r>", 100, -2.5, 2.5);
   P1["JetEtaVsResponseGenPT50PT75"] = new TProfile("HJetEtaVsResponseGenPT50PT75", ";#eta;<r>", 100, -2.5, 2.5);
   P1["JetEtaVsResponseGenPT75PT100"] = new TProfile("HJetEtaVsResponseGenPT75PT100", ";#eta;<r>", 100, -2.5, 2.5);
   P1["JetEtaVsResponseGenPT100PT125"] = new TProfile("HJetEtaVsResponseGenPT100PT125", ";#eta;<r>", 100, -2.5, 2.5);

   // Jet distribution with triggering
   H2["JetEtaPhiPT30FailL156"]
      = new TH2D("HJetEtaPhiPT30FailL156", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT50FailL156"]
      = new TH2D("HJetEtaPhiPT50FailL156", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT75FailL156"]
      = new TH2D("HJetEtaPhiPT75FailL156", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT100FailL156"]
      = new TH2D("HJetEtaPhiPT100FailL156", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT125FailL156"]
      = new TH2D("HJetEtaPhiPT125FailL156", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   // Jet fraction distributions
   H1["JetCHFPT50EtaN25N15"] = new TH1D("HJetCHFPT50EtaN25N15", ";CHF;", 35, 0, 1);
   H1["JetCHFPT50EtaN15N00"] = new TH1D("HJetCHFPT50EtaN15N00", ";CHF;", 35, 0, 1);
   H1["JetCHFPT50EtaP00P15"] = new TH1D("HJetCHFPT50EtaP00P15", ";CHF;", 35, 0, 1);
   H1["JetCHFPT50EtaP15P25"] = new TH1D("HJetCHFPT50EtaP15P25", ";CHF;", 35, 0, 1);
   H1["JetCEFPT50EtaN25N15"] = new TH1D("HJetCEFPT50EtaN25N15", ";CEF;", 35, 0, 1);
   H1["JetCEFPT50EtaN15N00"] = new TH1D("HJetCEFPT50EtaN15N00", ";CEF;", 35, 0, 1);
   H1["JetCEFPT50EtaP00P15"] = new TH1D("HJetCEFPT50EtaP00P15", ";CEF;", 35, 0, 1);
   H1["JetCEFPT50EtaP15P25"] = new TH1D("HJetCEFPT50EtaP15P25", ";CEF;", 35, 0, 1);
   H1["JetNHFPT50EtaN25N15"] = new TH1D("HJetNHFPT50EtaN25N15", ";NHF;", 35, 0, 1);
   H1["JetNHFPT50EtaN15N00"] = new TH1D("HJetNHFPT50EtaN15N00", ";NHF;", 35, 0, 1);
   H1["JetNHFPT50EtaP00P15"] = new TH1D("HJetNHFPT50EtaP00P15", ";NHF;", 35, 0, 1);
   H1["JetNHFPT50EtaP15P25"] = new TH1D("HJetNHFPT50EtaP15P25", ";NHF;", 35, 0, 1);
   H1["JetNEFPT50EtaN25N15"] = new TH1D("HJetNEFPT50EtaN25N15", ";NEF;", 35, 0, 1);
   H1["JetNEFPT50EtaN15N00"] = new TH1D("HJetNEFPT50EtaN15N00", ";NEF;", 35, 0, 1);
   H1["JetNEFPT50EtaP00P15"] = new TH1D("HJetNEFPT50EtaP00P15", ";NEF;", 35, 0, 1);
   H1["JetNEFPT50EtaP15P25"] = new TH1D("HJetNEFPT50EtaP15P25", ";NEF;", 35, 0, 1);
   H1["JetMUFPT50EtaN25N15"] = new TH1D("HJetMUFPT50EtaN25N15", ";MUF;", 35, 0, 1);
   H1["JetMUFPT50EtaN15N00"] = new TH1D("HJetMUFPT50EtaN15N00", ";MUF;", 35, 0, 1);
   H1["JetMUFPT50EtaP00P15"] = new TH1D("HJetMUFPT50EtaP00P15", ";MUF;", 35, 0, 1);
   H1["JetMUFPT50EtaP15P25"] = new TH1D("HJetMUFPT50EtaP15P25", ";MUF;", 35, 0, 1);
   H1["JetCHFPT70EtaN25N15"] = new TH1D("HJetCHFPT70EtaN25N15", ";CHF;", 35, 0, 1);
   H1["JetCHFPT70EtaN15N00"] = new TH1D("HJetCHFPT70EtaN15N00", ";CHF;", 35, 0, 1);
   H1["JetCHFPT70EtaP00P15"] = new TH1D("HJetCHFPT70EtaP00P15", ";CHF;", 35, 0, 1);
   H1["JetCHFPT70EtaP15P25"] = new TH1D("HJetCHFPT70EtaP15P25", ";CHF;", 35, 0, 1);
   H1["JetCEFPT70EtaN25N15"] = new TH1D("HJetCEFPT70EtaN25N15", ";CEF;", 35, 0, 1);
   H1["JetCEFPT70EtaN15N00"] = new TH1D("HJetCEFPT70EtaN15N00", ";CEF;", 35, 0, 1);
   H1["JetCEFPT70EtaP00P15"] = new TH1D("HJetCEFPT70EtaP00P15", ";CEF;", 35, 0, 1);
   H1["JetCEFPT70EtaP15P25"] = new TH1D("HJetCEFPT70EtaP15P25", ";CEF;", 35, 0, 1);
   H1["JetNHFPT70EtaN25N15"] = new TH1D("HJetNHFPT70EtaN25N15", ";NHF;", 35, 0, 1);
   H1["JetNHFPT70EtaN15N00"] = new TH1D("HJetNHFPT70EtaN15N00", ";NHF;", 35, 0, 1);
   H1["JetNHFPT70EtaP00P15"] = new TH1D("HJetNHFPT70EtaP00P15", ";NHF;", 35, 0, 1);
   H1["JetNHFPT70EtaP15P25"] = new TH1D("HJetNHFPT70EtaP15P25", ";NHF;", 35, 0, 1);
   H1["JetNEFPT70EtaN25N15"] = new TH1D("HJetNEFPT70EtaN25N15", ";NEF;", 35, 0, 1);
   H1["JetNEFPT70EtaN15N00"] = new TH1D("HJetNEFPT70EtaN15N00", ";NEF;", 35, 0, 1);
   H1["JetNEFPT70EtaP00P15"] = new TH1D("HJetNEFPT70EtaP00P15", ";NEF;", 35, 0, 1);
   H1["JetNEFPT70EtaP15P25"] = new TH1D("HJetNEFPT70EtaP15P25", ";NEF;", 35, 0, 1);
   H1["JetMUFPT70EtaN25N15"] = new TH1D("HJetMUFPT70EtaN25N15", ";MUF;", 35, 0, 1);
   H1["JetMUFPT70EtaN15N00"] = new TH1D("HJetMUFPT70EtaN15N00", ";MUF;", 35, 0, 1);
   H1["JetMUFPT70EtaP00P15"] = new TH1D("HJetMUFPT70EtaP00P15", ";MUF;", 35, 0, 1);
   H1["JetMUFPT70EtaP15P25"] = new TH1D("HJetMUFPT70EtaP15P25", ";MUF;", 35, 0, 1);

   // Jet ID distributions
   H1["JetAlgo6FractionPT30PassL156"] = new TH1D("HJetAlgo6FractionPT30PassL156", "", 40, 0, 1);
   H1["JetAlgo6FractionPT50PassL156"] = new TH1D("HJetAlgo6FractionPT50PassL156", "", 40, 0, 1);
   H1["JetAlgo6FractionPT70PassL156"] = new TH1D("HJetAlgo6FractionPT70PassL156", "", 40, 0, 1);
   H1["JetAlgo6FractionPT80PassL156"] = new TH1D("HJetAlgo6FractionPT80PassL156", "", 40, 0, 1);
   H1["JetAlgo6FractionPT100PassL156"] = new TH1D("HJetAlgo6FractionPT100PassL156", "", 40, 0, 1);
   H1["JetAlgo6FractionPT30FailL156"] = new TH1D("HJetAlgo6FractionPT30FailL156", "", 40, 0, 1);
   H1["JetAlgo6FractionPT50FailL156"] = new TH1D("HJetAlgo6FractionPT50FailL156", "", 40, 0, 1);
   H1["JetAlgo6FractionPT70FailL156"] = new TH1D("HJetAlgo6FractionPT70FailL156", "", 40, 0, 1);
   H1["JetAlgo6FractionPT80FailL156"] = new TH1D("HJetAlgo6FractionPT80FailL156", "", 40, 0, 1);
   H1["JetAlgo6FractionPT100FailL156"] = new TH1D("HJetAlgo6FractionPT100FailL156", "", 40, 0, 1);

   H2["JetEtaPhiPT50GoodID"] = new TH2D("HJetEtaPhiPT50GoodID", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT50BadID"] = new TH2D("HJetEtaPhiPT50BadID", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT70GoodID"] = new TH2D("HJetEtaPhiPT70GoodID", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["JetEtaPhiPT70BadID"] = new TH2D("HJetEtaPhiPT70BadID", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   // Track distributions
   H2["TrackEtaPhiID4PT1"] = new TH2D("HTrackEtaPhiID4PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID4PT2"] = new TH2D("HTrackEtaPhiID4PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID4PT5"] = new TH2D("HTrackEtaPhiID4PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID4PT10"] = new TH2D("HTrackEtaPhiID4PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID5PT1"] = new TH2D("HTrackEtaPhiID5PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID5PT2"] = new TH2D("HTrackEtaPhiID5PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID5PT5"] = new TH2D("HTrackEtaPhiID5PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID5PT10"] = new TH2D("HTrackEtaPhiID5PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID6PT1"] = new TH2D("HTrackEtaPhiID6PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID6PT2"] = new TH2D("HTrackEtaPhiID6PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID6PT5"] = new TH2D("HTrackEtaPhiID6PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID6PT10"] = new TH2D("HTrackEtaPhiID6PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID7PT1"] = new TH2D("HTrackEtaPhiID7PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID7PT2"] = new TH2D("HTrackEtaPhiID7PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID7PT5"] = new TH2D("HTrackEtaPhiID7PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID7PT10"] = new TH2D("HTrackEtaPhiID7PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID22PT1"] = new TH2D("HTrackEtaPhiID22PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID22PT2"] = new TH2D("HTrackEtaPhiID22PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID22PT5"] = new TH2D("HTrackEtaPhiID22PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID22PT10"] = new TH2D("HTrackEtaPhiID22PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID23PT1"] = new TH2D("HTrackEtaPhiID23PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID23PT2"] = new TH2D("HTrackEtaPhiID23PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID23PT5"] = new TH2D("HTrackEtaPhiID23PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackEtaPhiID23PT10"] = new TH2D("HTrackEtaPhiID23PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   H1["TrackMVAID4"] = new TH1D("HTrackMVAID4", ";MVA;", 200, 0.00, 1);
   H1["TrackMVAID5"] = new TH1D("HTrackMVAID5", ";MVA;", 200, 0.40, 1);
   H1["TrackMVAID6"] = new TH1D("HTrackMVAID6", ";MVA;", 200, 0.85, 1);
   H1["TrackMVAID7"] = new TH1D("HTrackMVAID7", ";MVA;", 200, 0.80, 1);
   H1["TrackMVAID22"] = new TH1D("HTrackMVAID22", ";MVA;", 200, 0.80, 1);
   H1["TrackMVAID23"] = new TH1D("HTrackMVAID23", ";MVA;", 200, 0.00, 1);

   H1["TrackMET"] = new TH1D("HTrackMET", ";MET;", 150, 0, 700);
   H1["TrackMETX"] = new TH1D("HTrackMETX", ";MET;", 150, -500, 500);
   H1["TrackMETY"] = new TH1D("HTrackMETY", ";MET;", 150, -500, 500);
   H1["PositiveTrackMET"] = new TH1D("HPositiveTrackMET", ";MET;", 150, 0, 700);
   H1["PositiveTrackMETX"] = new TH1D("HPositiveTrackMETX", ";MET;", 150, -500, 500);
   H1["PositiveTrackMETY"] = new TH1D("HPositiveTrackMETY", ";MET;", 150, -500, 500);

   // Track jet distributions
   H2["TrackJetEtaPhiPT30"] = new TH2D("HTrackJetEtaPhiPT30", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackJetEtaPhiPT50"] = new TH2D("HTrackJetEtaPhiPT50", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackJetEtaPhiPT75"] = new TH2D("HTrackJetEtaPhiPT75", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackJetEtaPhiPT100"] = new TH2D("HTrackJetEtaPhiPT100", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["TrackJetEtaPhiPT125"] = new TH2D("HTrackJetEtaPhiPT125", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   H1["TrackJetPTEtaN25N15"] = new TH1D("HTrackJetPTEtaN25N15", ";p_{T};", 100, 0, 200);
   H1["TrackJetPTEtaN15N00"] = new TH1D("HTrackJetPTEtaN15N00", ";p_{T};", 100, 0, 200);
   H1["TrackJetPTEtaP00P15"] = new TH1D("HTrackJetPTEtaP00P15", ";p_{T};", 100, 0, 200);
   H1["TrackJetPTEtaP15P25"] = new TH1D("HTrackJetPTEtaP15P25", ";p_{T};", 100, 0, 200);

   // PF distributions
   H1["PFPTID1EtaN25N15"] = new TH1D("HPFPTID1EtaN25N15", ";p_{T}", 100, 0, 75);
   H1["PFPTID1EtaN15N00"] = new TH1D("HPFPTID1EtaN15N00", ";p_{T}", 100, 0, 75);
   H1["PFPTID1EtaP00P15"] = new TH1D("HPFPTID1EtaP00P15", ";p_{T}", 100, 0, 75);
   H1["PFPTID1EtaP15P25"] = new TH1D("HPFPTID1EtaP15P25", ";p_{T}", 100, 0, 75);
   H1["PFPTID2EtaN25N15"] = new TH1D("HPFPTID2EtaN25N15", ";p_{T}", 100, 0, 75);
   H1["PFPTID2EtaN15N00"] = new TH1D("HPFPTID2EtaN15N00", ";p_{T}", 100, 0, 75);
   H1["PFPTID2EtaP00P15"] = new TH1D("HPFPTID2EtaP00P15", ";p_{T}", 100, 0, 75);
   H1["PFPTID2EtaP15P25"] = new TH1D("HPFPTID2EtaP15P25", ";p_{T}", 100, 0, 75);
   H1["PFPTID3EtaN25N15"] = new TH1D("HPFPTID3EtaN25N15", ";p_{T}", 100, 0, 75);
   H1["PFPTID3EtaN15N00"] = new TH1D("HPFPTID3EtaN15N00", ";p_{T}", 100, 0, 75);
   H1["PFPTID3EtaP00P15"] = new TH1D("HPFPTID3EtaP00P15", ";p_{T}", 100, 0, 75);
   H1["PFPTID3EtaP15P25"] = new TH1D("HPFPTID3EtaP15P25", ";p_{T}", 100, 0, 75);
   H1["PFPTID4EtaN25N15"] = new TH1D("HPFPTID4EtaN25N15", ";p_{T}", 100, 0, 75);
   H1["PFPTID4EtaN15N00"] = new TH1D("HPFPTID4EtaN15N00", ";p_{T}", 100, 0, 75);
   H1["PFPTID4EtaP00P15"] = new TH1D("HPFPTID4EtaP00P15", ";p_{T}", 100, 0, 75);
   H1["PFPTID4EtaP15P25"] = new TH1D("HPFPTID4EtaP15P25", ";p_{T}", 100, 0, 75);
   H1["PFPTID5EtaN25N15"] = new TH1D("HPFPTID5EtaN25N15", ";p_{T}", 100, 0, 75);
   H1["PFPTID5EtaN15N00"] = new TH1D("HPFPTID5EtaN15N00", ";p_{T}", 100, 0, 75);
   H1["PFPTID5EtaP00P15"] = new TH1D("HPFPTID5EtaP00P15", ";p_{T}", 100, 0, 75);
   H1["PFPTID5EtaP15P25"] = new TH1D("HPFPTID5EtaP15P25", ";p_{T}", 100, 0, 75);
   
   H2["PFEtaPhiID1PT05"] = new TH2D("HPFEtaPhiID1PT05", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID2PT05"] = new TH2D("HPFEtaPhiID2PT05", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID3PT05"] = new TH2D("HPFEtaPhiID3PT05", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID4PT05"] = new TH2D("HPFEtaPhiID4PT05", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID5PT05"] = new TH2D("HPFEtaPhiID5PT05", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID1PT1"] = new TH2D("HPFEtaPhiID1PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID2PT1"] = new TH2D("HPFEtaPhiID2PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID3PT1"] = new TH2D("HPFEtaPhiID3PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID4PT1"] = new TH2D("HPFEtaPhiID4PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID5PT1"] = new TH2D("HPFEtaPhiID5PT1", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID1PT2"] = new TH2D("HPFEtaPhiID1PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID2PT2"] = new TH2D("HPFEtaPhiID2PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID3PT2"] = new TH2D("HPFEtaPhiID3PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID4PT2"] = new TH2D("HPFEtaPhiID4PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID5PT2"] = new TH2D("HPFEtaPhiID5PT2", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID1PT5"] = new TH2D("HPFEtaPhiID1PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID2PT5"] = new TH2D("HPFEtaPhiID2PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID3PT5"] = new TH2D("HPFEtaPhiID3PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID4PT5"] = new TH2D("HPFEtaPhiID4PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID5PT5"] = new TH2D("HPFEtaPhiID5PT5", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID1PT10"] = new TH2D("HPFEtaPhiID1PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID2PT10"] = new TH2D("HPFEtaPhiID2PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID3PT10"] = new TH2D("HPFEtaPhiID3PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID4PT10"] = new TH2D("HPFEtaPhiID4PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   H2["PFEtaPhiID5PT10"] = new TH2D("HPFEtaPhiID5PT10", ";#eta;#phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   // Loop over files
   for(string FileName : InputFileName)
   {
      cout << "Processing file " << FileName << endl;

      TFile InputFile(FileName.c_str());

      // Setup messengers
      HiEventTreeMessenger MHiEvent(InputFile);
      TrackTreeMessenger MTrack(InputFile);
      JetTreeMessenger MJet(InputFile, JetTreeName);
      TriggerTreeMessenger MHLT(InputFile);
      PFTreeMessenger MPF(InputFile);
      SkimTreeMessenger MSkim(InputFile);

      if(MHiEvent.Tree == nullptr)
      {
         InputFile.Close();
         continue;
      }

      // Loop over events
      int EntryCount = MHiEvent.Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         if(iE < 200 || (iE % (EntryCount / 300)) == 0)
         {
            Bar.Update(iE);
            Bar.Print();
         }

         // Get entries
         MHiEvent.GetEntry(iE);
         MTrack.GetEntry(iE);
         MJet.GetEntry(iE);
         MHLT.GetEntry(iE);
         MPF.GetEntry(iE);
         MSkim.GetEntry(iE);

         // Fill the mandatory event count histogram
         H1["N"]->Fill(0);

         // Some bool's for triggering information
         bool PassL156 = (MHLT.CheckTrigger("L1SingleJet56BptxAND") > 0);

         // Calculate track-only quantities
         vector<PseudoJet> Tracks;
         FourVector TrackMET;
         FourVector PositiveTrackMET;
         for(int iT = 0; iT < MTrack.TrackCount; iT++)
         {
            if(MTrack.HighPurity[iT] == false)
               continue;

            FourVector P;
            P.SetPtEtaPhi(MTrack.TrackPT[iT], MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
            Tracks.push_back(PseudoJet(P[1], P[2], P[3], P[0]));

            TrackMET = TrackMET - P;
            if(P[3] > 0)
               PositiveTrackMET = PositiveTrackMET - P;
         }
         JetDefinition Definition(antikt_algorithm, 0.4);
         ClusterSequence Sequence(Tracks, Definition);
         vector<PseudoJet> FastJets = Sequence.inclusive_jets();

         vector<FourVector> TrackJets;
         for(PseudoJet J : FastJets)
            TrackJets.push_back(FourVector(J.e(), J.px(), J.py(), J.pz()));

         // Calculate auxiliary jet quantities
         double JetAlgo6Fraction[MAXJET] = {0};
         FourVector LeadingJet(-1, 0, 0, 0);
         for(int iJ = 0; iJ < MJet.JetCount; iJ++)
         {
            if(LeadingJet[0] < 0 || MJet.JetPT[iJ] > LeadingJet.GetPT())
               LeadingJet.SetPtEtaPhi(MJet.JetPT[iJ], MJet.JetEta[iJ], MJet.JetPhi[iJ]);

            if(MJet.JetPT[iJ] < MinPTForTrack)
               JetAlgo6Fraction[iJ] = -1;
            else
            {
               double AllPT = 0, Algo6PT = 0;
               for(int iT = 0; iT < MTrack.TrackCount; iT++)
               {
                  if(MTrack.HighPurity[iT] == false)
                     continue;

                  double DEta = MJet.JetEta[iJ] - MTrack.TrackEta[iT];
                  double DPhi = MJet.JetPhi[iJ] - MTrack.TrackPhi[iT];
                  if(DPhi > M_PI)    DPhi = DPhi - 2 * M_PI;
                  if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;

                  if(DEta * DEta + DPhi * DPhi < 0.4 * 0.4)
                  {
                     AllPT = AllPT + MTrack.TrackPT[iT];
                     if(MTrack.TrackAlgo[iT] == 6)
                        Algo6PT = Algo6PT + MTrack.TrackPT[iT];
                  }
               }

               if(AllPT > 0)
                  JetAlgo6Fraction[iJ] = Algo6PT / AllPT;
               else
                  JetAlgo6Fraction[iJ] = -1;
            }
         }

         // Fill basic jet distributions + trigger-correlated + PF fractions
         for(int iJ = 0; iJ < MJet.JetCount; iJ++)
         {
            double RefPT = MJet.RefPT[iJ];
            double RawPT = MJet.JetRawPT[iJ];
            double PT = MJet.JetPT[iJ];
            double Eta = MJet.JetEta[iJ];
            double Phi = MJet.JetPhi[iJ];

            // Basic jet distributions
            H1["JetPT"]->Fill(PT);

            if(Eta > -2.5 && Eta < 2.5)
            {
               H2["RawPTVsJEC"]->Fill(RawPT, PT / RawPT);
               H2["RawPTVsJetPT"]->Fill(RawPT, PT);
            }

            if(RefPT > 30 && RefPT < 50)     P1["JetEtaVsResponseGenPT30PT50"]->Fill(Eta, PT / RefPT);
            if(RefPT > 50 && RefPT < 75)     P1["JetEtaVsResponseGenPT50PT75"]->Fill(Eta, PT / RefPT);
            if(RefPT > 75 && RefPT < 100)    P1["JetEtaVsResponseGenPT75PT100"]->Fill(Eta, PT / RefPT);
            if(RefPT > 100 && RefPT < 125)   P1["JetEtaVsResponseGenPT100PT125"]->Fill(Eta, PT / RefPT);
            
            if(PT > 30)    H2["JetEtaPhiPT30"]->Fill(Eta, Phi);
            if(PT > 50)    H2["JetEtaPhiPT50"]->Fill(Eta, Phi);
            if(PT > 75)    H2["JetEtaPhiPT75"]->Fill(Eta, Phi);
            if(PT > 100)   H2["JetEtaPhiPT100"]->Fill(Eta, Phi);
            if(PT > 125)   H2["JetEtaPhiPT125"]->Fill(Eta, Phi);

            if(PT > 30)    H1["JetEtaPT30"]->Fill(Eta);
            if(PT > 50)    H1["JetEtaPT50"]->Fill(Eta);
            if(PT > 75)    H1["JetEtaPT75"]->Fill(Eta);
            if(PT > 100)   H1["JetEtaPT100"]->Fill(Eta);
            if(PT > 125)   H1["JetEtaPT125"]->Fill(Eta);

            if(Eta > -2.5 && Eta < -1.5)   H1["JetPTEtaN25N15"]->Fill(PT);
            if(Eta > -1.5 && Eta < 0.0)    H1["JetPTEtaN15N00"]->Fill(PT);
            if(Eta > 0.0 && Eta < 1.5)     H1["JetPTEtaP00P15"]->Fill(PT);
            if(Eta > 1.5 && Eta < 2.5)     H1["JetPTEtaP15P25"]->Fill(PT);

            if(Eta > -2.5 && Eta < -1.5 && PT > 30)    H1["JetPhiPT30EtaN25N15"]->Fill(Phi);
            if(Eta > -1.5 && Eta < 0.0 && PT > 30)     H1["JetPhiPT30EtaN15N00"]->Fill(Phi);
            if(Eta > 0.0 && Eta < 1.5 && PT > 30)      H1["JetPhiPT30EtaP00P15"]->Fill(Phi);
            if(Eta > 1.5 && Eta < 2.5 && PT > 30)      H1["JetPhiPT30EtaP15P25"]->Fill(Phi);
            if(Eta > -2.5 && Eta < -1.5 && PT > 50)    H1["JetPhiPT50EtaN25N15"]->Fill(Phi);
            if(Eta > -1.5 && Eta < 0.0 && PT > 50)     H1["JetPhiPT50EtaN15N00"]->Fill(Phi);
            if(Eta > 0.0 && Eta < 1.5 && PT > 50)      H1["JetPhiPT50EtaP00P15"]->Fill(Phi);
            if(Eta > 1.5 && Eta < 2.5 && PT > 50)      H1["JetPhiPT50EtaP15P25"]->Fill(Phi);
            if(Eta > -2.5 && Eta < -1.5 && PT > 75)    H1["JetPhiPT75EtaN25N15"]->Fill(Phi);
            if(Eta > -1.5 && Eta < 0.0 && PT > 75)     H1["JetPhiPT75EtaN15N00"]->Fill(Phi);
            if(Eta > 0.0 && Eta < 1.5 && PT > 75)      H1["JetPhiPT75EtaP00P15"]->Fill(Phi);
            if(Eta > 1.5 && Eta < 2.5 && PT > 75)      H1["JetPhiPT75EtaP15P25"]->Fill(Phi);
            if(Eta > -2.5 && Eta < -1.5 && PT > 100)   H1["JetPhiPT100EtaN25N15"]->Fill(Phi);
            if(Eta > -1.5 && Eta < 0.0 && PT > 100)    H1["JetPhiPT100EtaN15N00"]->Fill(Phi);
            if(Eta > 0.0 && Eta < 1.5 && PT > 100)     H1["JetPhiPT100EtaP00P15"]->Fill(Phi);
            if(Eta > 1.5 && Eta < 2.5 && PT > 100)     H1["JetPhiPT100EtaP15P25"]->Fill(Phi);
            if(Eta > -2.5 && Eta < -1.5 && PT > 125)   H1["JetPhiPT125EtaN25N15"]->Fill(Phi);
            if(Eta > -1.5 && Eta < 0.0 && PT > 125)    H1["JetPhiPT125EtaN15N00"]->Fill(Phi);
            if(Eta > 0.0 && Eta < 1.5 && PT > 125)     H1["JetPhiPT125EtaP00P15"]->Fill(Phi);
            if(Eta > 1.5 && Eta < 2.5 && PT > 125)     H1["JetPhiPT125EtaP15P25"]->Fill(Phi);
            
            // Trigger-related
            if(PassL156 == false)
            {
               if(LeadingJet.GetPT() > 30)    H2["JetEtaPhiPT30FailL156"]->Fill(LeadingJet.GetEta(), LeadingJet.GetPhi());
               if(LeadingJet.GetPT() > 50)    H2["JetEtaPhiPT50FailL156"]->Fill(LeadingJet.GetEta(), LeadingJet.GetPhi());
               if(LeadingJet.GetPT() > 75)    H2["JetEtaPhiPT75FailL156"]->Fill(LeadingJet.GetEta(), LeadingJet.GetPhi());
               if(LeadingJet.GetPT() > 100)   H2["JetEtaPhiPT100FailL156"]->Fill(LeadingJet.GetEta(), LeadingJet.GetPhi());
               if(LeadingJet.GetPT() > 125)   H2["JetEtaPhiPT125FailL156"]->Fill(LeadingJet.GetEta(), LeadingJet.GetPhi());
            }

            // Jet ID
            if(PassL156 == true)
            {
               if(PT > 30)    H1["JetAlgo6FractionPT30PassL156"]->Fill(JetAlgo6Fraction[iJ]);
               if(PT > 50)    H1["JetAlgo6FractionPT50PassL156"]->Fill(JetAlgo6Fraction[iJ]);
               if(PT > 70)    H1["JetAlgo6FractionPT70PassL156"]->Fill(JetAlgo6Fraction[iJ]);
               if(PT > 80)    H1["JetAlgo6FractionPT80PassL156"]->Fill(JetAlgo6Fraction[iJ]);
               if(PT > 100)   H1["JetAlgo6FractionPT100PassL156"]->Fill(JetAlgo6Fraction[iJ]);
            }
            else
            {
               if(PT > 30)    H1["JetAlgo6FractionPT30FailL156"]->Fill(JetAlgo6Fraction[iJ]);
               if(PT > 50)    H1["JetAlgo6FractionPT50FailL156"]->Fill(JetAlgo6Fraction[iJ]);
               if(PT > 70)    H1["JetAlgo6FractionPT70FailL156"]->Fill(JetAlgo6Fraction[iJ]);
               if(PT > 80)    H1["JetAlgo6FractionPT80FailL156"]->Fill(JetAlgo6Fraction[iJ]);
               if(PT > 100)   H1["JetAlgo6FractionPT100FailL156"]->Fill(JetAlgo6Fraction[iJ]);
            }
   
            if(PT > 50 && JetAlgo6Fraction[iJ] < 0.25)   H2["JetEtaPhiPT50GoodID"]->Fill(Eta, Phi);
            if(PT > 50 && JetAlgo6Fraction[iJ] > 0.25)   H2["JetEtaPhiPT50BadID"]->Fill(Eta, Phi);
            if(PT > 70 && JetAlgo6Fraction[iJ] < 0.25)   H2["JetEtaPhiPT70GoodID"]->Fill(Eta, Phi);
            if(PT > 70 && JetAlgo6Fraction[iJ] > 0.25)   H2["JetEtaPhiPT70BadID"]->Fill(Eta, Phi);

            // PF fractions
            if(PT > 50)
            {
               if(Eta > -2.5 && Eta < -1.5)
               {
                  H1["JetCHFPT50EtaN25N15"]->Fill(MJet.JetPFCHF[iJ]);
                  H1["JetCEFPT50EtaN25N15"]->Fill(MJet.JetPFCEF[iJ]);
                  H1["JetNHFPT50EtaN25N15"]->Fill(MJet.JetPFNHF[iJ]);
                  H1["JetNEFPT50EtaN25N15"]->Fill(MJet.JetPFNEF[iJ]);
                  H1["JetMUFPT50EtaN25N15"]->Fill(MJet.JetPFMUF[iJ]);
               }
               if(Eta > -1.5 && Eta < 0.0)
               {
                  H1["JetCHFPT50EtaN15N00"]->Fill(MJet.JetPFCHF[iJ]);
                  H1["JetCEFPT50EtaN15N00"]->Fill(MJet.JetPFCEF[iJ]);
                  H1["JetNHFPT50EtaN15N00"]->Fill(MJet.JetPFNHF[iJ]);
                  H1["JetNEFPT50EtaN15N00"]->Fill(MJet.JetPFNEF[iJ]);
                  H1["JetMUFPT50EtaN15N00"]->Fill(MJet.JetPFMUF[iJ]);
               }
               if(Eta > 0.0 && Eta < 1.5)
               {
                  H1["JetCHFPT50EtaP00P15"]->Fill(MJet.JetPFCHF[iJ]);
                  H1["JetCEFPT50EtaP00P15"]->Fill(MJet.JetPFCEF[iJ]);
                  H1["JetNHFPT50EtaP00P15"]->Fill(MJet.JetPFNHF[iJ]);
                  H1["JetNEFPT50EtaP00P15"]->Fill(MJet.JetPFNEF[iJ]);
                  H1["JetMUFPT50EtaP00P15"]->Fill(MJet.JetPFMUF[iJ]);
               }
               if(Eta > 1.5 && Eta < 2.5)
               {
                  H1["JetCHFPT50EtaP15P25"]->Fill(MJet.JetPFCHF[iJ]);
                  H1["JetCEFPT50EtaP15P25"]->Fill(MJet.JetPFCEF[iJ]);
                  H1["JetNHFPT50EtaP15P25"]->Fill(MJet.JetPFNHF[iJ]);
                  H1["JetNEFPT50EtaP15P25"]->Fill(MJet.JetPFNEF[iJ]);
                  H1["JetMUFPT50EtaP15P25"]->Fill(MJet.JetPFMUF[iJ]);
               }
            }
            if(PT > 70)
            {
               if(Eta > -2.5 && Eta < -1.5)
               {
                  H1["JetCHFPT70EtaN25N15"]->Fill(MJet.JetPFCHF[iJ]);
                  H1["JetCEFPT70EtaN25N15"]->Fill(MJet.JetPFCEF[iJ]);
                  H1["JetNHFPT70EtaN25N15"]->Fill(MJet.JetPFNHF[iJ]);
                  H1["JetNEFPT70EtaN25N15"]->Fill(MJet.JetPFNEF[iJ]);
                  H1["JetMUFPT70EtaN25N15"]->Fill(MJet.JetPFMUF[iJ]);
               }
               if(Eta > -1.5 && Eta < 0.0)
               {
                  H1["JetCHFPT70EtaN15N00"]->Fill(MJet.JetPFCHF[iJ]);
                  H1["JetCEFPT70EtaN15N00"]->Fill(MJet.JetPFCEF[iJ]);
                  H1["JetNHFPT70EtaN15N00"]->Fill(MJet.JetPFNHF[iJ]);
                  H1["JetNEFPT70EtaN15N00"]->Fill(MJet.JetPFNEF[iJ]);
                  H1["JetMUFPT70EtaN15N00"]->Fill(MJet.JetPFMUF[iJ]);
               }
               if(Eta > 0.0 && Eta < 1.5)
               {
                  H1["JetCHFPT70EtaP00P15"]->Fill(MJet.JetPFCHF[iJ]);
                  H1["JetCEFPT70EtaP00P15"]->Fill(MJet.JetPFCEF[iJ]);
                  H1["JetNHFPT70EtaP00P15"]->Fill(MJet.JetPFNHF[iJ]);
                  H1["JetNEFPT70EtaP00P15"]->Fill(MJet.JetPFNEF[iJ]);
                  H1["JetMUFPT70EtaP00P15"]->Fill(MJet.JetPFMUF[iJ]);
               }
               if(Eta > 1.5 && Eta < 2.5)
               {
                  H1["JetCHFPT70EtaP15P25"]->Fill(MJet.JetPFCHF[iJ]);
                  H1["JetCEFPT70EtaP15P25"]->Fill(MJet.JetPFCEF[iJ]);
                  H1["JetNHFPT70EtaP15P25"]->Fill(MJet.JetPFNHF[iJ]);
                  H1["JetNEFPT70EtaP15P25"]->Fill(MJet.JetPFNEF[iJ]);
                  H1["JetMUFPT70EtaP15P25"]->Fill(MJet.JetPFMUF[iJ]);
               }
            }
         }

         // Fill track distributions
         for(int iT = 0; iT < MTrack.TrackCount; iT++)
         {
            if(MTrack.HighPurity[iT] == false)
               continue;

            double PT = MTrack.TrackPT[iT];
            double Eta = MTrack.TrackEta[iT];
            double Phi = MTrack.TrackPhi[iT];

            if(MTrack.TrackAlgo[iT] == 4)
            {
               H1["TrackMVAID4"]->Fill(MTrack.TrackMVA[iT]);
               if(PT > 1)    H2["TrackEtaPhiID4PT1"]->Fill(Eta, Phi);
               if(PT > 2)    H2["TrackEtaPhiID4PT2"]->Fill(Eta, Phi);
               if(PT > 5)    H2["TrackEtaPhiID4PT5"]->Fill(Eta, Phi);
               if(PT > 10)   H2["TrackEtaPhiID4PT10"]->Fill(Eta, Phi);
            }
            if(MTrack.TrackAlgo[iT] == 5)
            {
               H1["TrackMVAID5"]->Fill(MTrack.TrackMVA[iT]);
               if(PT > 1)    H2["TrackEtaPhiID5PT1"]->Fill(Eta, Phi);
               if(PT > 2)    H2["TrackEtaPhiID5PT2"]->Fill(Eta, Phi);
               if(PT > 5)    H2["TrackEtaPhiID5PT5"]->Fill(Eta, Phi);
               if(PT > 10)   H2["TrackEtaPhiID5PT10"]->Fill(Eta, Phi);
            }
            if(MTrack.TrackAlgo[iT] == 6)
            {
               H1["TrackMVAID6"]->Fill(MTrack.TrackMVA[iT]);
               if(PT > 1)    H2["TrackEtaPhiID6PT1"]->Fill(Eta, Phi);
               if(PT > 2)    H2["TrackEtaPhiID6PT2"]->Fill(Eta, Phi);
               if(PT > 5)    H2["TrackEtaPhiID6PT5"]->Fill(Eta, Phi);
               if(PT > 10)   H2["TrackEtaPhiID6PT10"]->Fill(Eta, Phi);
            }
            if(MTrack.TrackAlgo[iT] == 7)
            {
               H1["TrackMVAID7"]->Fill(MTrack.TrackMVA[iT]);
               if(PT > 1)    H2["TrackEtaPhiID7PT1"]->Fill(Eta, Phi);
               if(PT > 2)    H2["TrackEtaPhiID7PT2"]->Fill(Eta, Phi);
               if(PT > 5)    H2["TrackEtaPhiID7PT5"]->Fill(Eta, Phi);
               if(PT > 10)   H2["TrackEtaPhiID7PT10"]->Fill(Eta, Phi);
            }
            if(MTrack.TrackAlgo[iT] == 22)
            {
               H1["TrackMVAID22"]->Fill(MTrack.TrackMVA[iT]);
               if(PT > 1)    H2["TrackEtaPhiID22PT1"]->Fill(Eta, Phi);
               if(PT > 2)    H2["TrackEtaPhiID22PT2"]->Fill(Eta, Phi);
               if(PT > 5)    H2["TrackEtaPhiID22PT5"]->Fill(Eta, Phi);
               if(PT > 10)   H2["TrackEtaPhiID22PT10"]->Fill(Eta, Phi);
            }
            if(MTrack.TrackAlgo[iT] == 23)
            {
               H1["TrackMVAID23"]->Fill(MTrack.TrackMVA[iT]);
               if(PT > 1)    H2["TrackEtaPhiID23PT1"]->Fill(Eta, Phi);
               if(PT > 2)    H2["TrackEtaPhiID23PT2"]->Fill(Eta, Phi);
               if(PT > 5)    H2["TrackEtaPhiID23PT5"]->Fill(Eta, Phi);
               if(PT > 10)   H2["TrackEtaPhiID23PT10"]->Fill(Eta, Phi);
            }
         }

         // Fill track MET distributions
         H1["TrackMET"]->Fill(TrackMET.GetPT());
         H1["TrackMETX"]->Fill((TrackMET[1] + TrackMET[2]) / sqrt(2));
         H1["TrackMETY"]->Fill((TrackMET[1] - TrackMET[2]) / sqrt(2));
         H1["PositiveTrackMET"]->Fill(PositiveTrackMET.GetPT());
         H1["PositiveTrackMETX"]->Fill((PositiveTrackMET[1] + PositiveTrackMET[2]) / sqrt(2));
         H1["PositiveTrackMETY"]->Fill((PositiveTrackMET[1] - PositiveTrackMET[2]) / sqrt(2));

         // Fill track jet distributions
         for(auto J : TrackJets)
         {
            if(J.GetPT() > 30)    H2["TrackJetEtaPhiPT30"]->Fill(J.GetEta(), J.GetPhi());
            if(J.GetPT() > 50)    H2["TrackJetEtaPhiPT50"]->Fill(J.GetEta(), J.GetPhi());
            if(J.GetPT() > 75)    H2["TrackJetEtaPhiPT75"]->Fill(J.GetEta(), J.GetPhi());
            if(J.GetPT() > 100)   H2["TrackJetEtaPhiPT100"]->Fill(J.GetEta(), J.GetPhi());
            if(J.GetPT() > 125)   H2["TrackJetEtaPhiPT125"]->Fill(J.GetEta(), J.GetPhi());

            if(J.GetEta() > -2.5 && J.GetEta() < -1.5)   H1["TrackJetPTEtaN25N15"]->Fill(J.GetPT());
            if(J.GetEta() > -1.5 && J.GetEta() < 0.0)    H1["TrackJetPTEtaN15N00"]->Fill(J.GetPT());
            if(J.GetEta() > 0.0 && J.GetEta() < 1.5)     H1["TrackJetPTEtaP00P15"]->Fill(J.GetPT());
            if(J.GetEta() > 1.5 && J.GetEta() < 2.5)     H1["TrackJetPTEtaP15P25"]->Fill(J.GetPT());
         }

         // Fill PF distributions
         for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
         {
            int ID = (*MPF.ID)[iPF];
            double PT = (*MPF.PT)[iPF];
            double Eta = (*MPF.Eta)[iPF];
            double Phi = (*MPF.Phi)[iPF];

            if(ID == 1)
            {
               if(Eta > -2.5 && Eta < -1.5)   H1["PFPTID1EtaN25N15"]->Fill(PT);
               if(Eta > -1.5 && Eta < 0.0)    H1["PFPTID1EtaN15N00"]->Fill(PT);
               if(Eta > 0.0 && Eta < 1.5)     H1["PFPTID1EtaP00P15"]->Fill(PT);
               if(Eta > 1.5 && Eta < 2.5)     H1["PFPTID1EtaP15P25"]->Fill(PT);
               
               if(PT > 0.5)    H2["PFEtaPhiID1PT05"]->Fill(Eta, Phi);
               if(PT > 1.0)    H2["PFEtaPhiID1PT1"]->Fill(Eta, Phi);
               if(PT > 2.0)    H2["PFEtaPhiID1PT2"]->Fill(Eta, Phi);
               if(PT > 5.0)    H2["PFEtaPhiID1PT5"]->Fill(Eta, Phi);
               if(PT > 10.0)   H2["PFEtaPhiID1PT10"]->Fill(Eta, Phi);
            }
            if(ID == 2)
            {
               if(Eta > -2.5 && Eta < -1.5)   H1["PFPTID2EtaN25N15"]->Fill(PT);
               if(Eta > -1.5 && Eta < 0.0)    H1["PFPTID2EtaN15N00"]->Fill(PT);
               if(Eta > 0.0 && Eta < 1.5)     H1["PFPTID2EtaP00P15"]->Fill(PT);
               if(Eta > 1.5 && Eta < 2.5)     H1["PFPTID2EtaP15P25"]->Fill(PT);
               
               if(PT > 0.5)    H2["PFEtaPhiID2PT05"]->Fill(Eta, Phi);
               if(PT > 1.0)    H2["PFEtaPhiID2PT1"]->Fill(Eta, Phi);
               if(PT > 2.0)    H2["PFEtaPhiID2PT2"]->Fill(Eta, Phi);
               if(PT > 5.0)    H2["PFEtaPhiID2PT5"]->Fill(Eta, Phi);
               if(PT > 10.0)   H2["PFEtaPhiID2PT10"]->Fill(Eta, Phi);
            }
            if(ID == 3)
            {
               if(Eta > -2.5 && Eta < -1.5)   H1["PFPTID3EtaN25N15"]->Fill(PT);
               if(Eta > -1.5 && Eta < 0.0)    H1["PFPTID3EtaN15N00"]->Fill(PT);
               if(Eta > 0.0 && Eta < 1.5)     H1["PFPTID3EtaP00P15"]->Fill(PT);
               if(Eta > 1.5 && Eta < 2.5)     H1["PFPTID3EtaP15P25"]->Fill(PT);
               
               if(PT > 0.5)    H2["PFEtaPhiID3PT05"]->Fill(Eta, Phi);
               if(PT > 1.0)    H2["PFEtaPhiID3PT1"]->Fill(Eta, Phi);
               if(PT > 2.0)    H2["PFEtaPhiID3PT2"]->Fill(Eta, Phi);
               if(PT > 5.0)    H2["PFEtaPhiID3PT5"]->Fill(Eta, Phi);
               if(PT > 10.0)   H2["PFEtaPhiID3PT10"]->Fill(Eta, Phi);
            }
            if(ID == 4)
            {
               if(Eta > -2.5 && Eta < -1.5)   H1["PFPTID4EtaN25N15"]->Fill(PT);
               if(Eta > -1.5 && Eta < 0.0)    H1["PFPTID4EtaN15N00"]->Fill(PT);
               if(Eta > 0.0 && Eta < 1.5)     H1["PFPTID4EtaP00P15"]->Fill(PT);
               if(Eta > 1.5 && Eta < 2.5)     H1["PFPTID4EtaP15P25"]->Fill(PT);
               
               if(PT > 0.5)    H2["PFEtaPhiID4PT05"]->Fill(Eta, Phi);
               if(PT > 1.0)    H2["PFEtaPhiID4PT1"]->Fill(Eta, Phi);
               if(PT > 2.0)    H2["PFEtaPhiID4PT2"]->Fill(Eta, Phi);
               if(PT > 5.0)    H2["PFEtaPhiID4PT5"]->Fill(Eta, Phi);
               if(PT > 10.0)   H2["PFEtaPhiID4PT10"]->Fill(Eta, Phi);
            }
            if(ID == 5)
            {
               if(Eta > -2.5 && Eta < -1.5)   H1["PFPTID5EtaN25N15"]->Fill(PT);
               if(Eta > -1.5 && Eta < 0.0)    H1["PFPTID5EtaN15N00"]->Fill(PT);
               if(Eta > 0.0 && Eta < 1.5)     H1["PFPTID5EtaP00P15"]->Fill(PT);
               if(Eta > 1.5 && Eta < 2.5)     H1["PFPTID5EtaP15P25"]->Fill(PT);
               
               if(PT > 0.5)    H2["PFEtaPhiID5PT05"]->Fill(Eta, Phi);
               if(PT > 1.0)    H2["PFEtaPhiID5PT1"]->Fill(Eta, Phi);
               if(PT > 2.0)    H2["PFEtaPhiID5PT2"]->Fill(Eta, Phi);
               if(PT > 5.0)    H2["PFEtaPhiID5PT5"]->Fill(Eta, Phi);
               if(PT > 10.0)   H2["PFEtaPhiID5PT10"]->Fill(Eta, Phi);
            }
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   OutputFile.cd();

   for(auto I : H1)   if(I.second != nullptr)   I.second->Write();
   for(auto I : H2)   if(I.second != nullptr)   I.second->Write();
   for(auto I : P1)   if(I.second != nullptr)   I.second->Write();

   OutputFile.Close();

   return 0;
}



